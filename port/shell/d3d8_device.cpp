// The Direct3D 8 subset the recovered renderer uses, emulated on the CPU:
// Direct3DCreate8, one device, vertex and index buffers, and textures. The
// recovered G0/GDX code (device creation, render states, object, sprite and
// overlay drawing) compiles unchanged against it.
//
// The device keeps Direct3D's fixed-function state and does the vertex stage
// itself: world, view and projection transforms, the texture transform and
// linear vertex fog. Each draw goes to the presenter (render_backend.h) as
// clip-space triangles or lines with a snapshot of the pixel state. Lighting
// stays off (reset_direct3d_render_state), and the game uses two vertex
// formats, XYZ|DIFFUSE|TEX1 and XYZ|TEX1.

#include <stdlib.h>
#include <string.h>

#include "d3d8_device.h"
#include "direct3d_device8_view.h"
#include "direct3d_renderer.h"
#include "draw_distance.h"
#include "object_render_types.h"
#include "render_backend.h"
#include "vertex_buffer_view.h"

namespace {

// Direct3D 8 enumerants the device interprets.
enum {
    D3DTS_VIEW = 2,
    D3DTS_PROJECTION = 3,
    D3DTS_TEXTURE0 = 16,
    D3DTS_WORLD = 256,

    D3DRS_ZENABLE = 7,
    D3DRS_ZWRITEENABLE = 14,
    D3DRS_ALPHATESTENABLE = 15,
    D3DRS_SRCBLEND = 19,
    D3DRS_DESTBLEND = 20,
    D3DRS_CULLMODE = 22,
    D3DRS_ZFUNC = 23,
    D3DRS_ALPHAREF = 24,
    D3DRS_ALPHAFUNC = 25,
    D3DRS_ALPHABLENDENABLE = 27,
    D3DRS_FOGENABLE = 28,
    D3DRS_FOGCOLOR = 34,
    D3DRS_FOGSTART = 36,
    D3DRS_FOGEND = 37,
    D3DRS_TEXTUREFACTOR = 60,
    D3DRS_LIGHTING = 137,
    D3DRS_COUNT = 256,

    D3DTSS_COLOROP = 1,
    D3DTSS_COLORARG1 = 2,
    D3DTSS_COLORARG2 = 3,
    D3DTSS_ALPHAOP = 4,
    D3DTSS_ALPHAARG1 = 5,
    D3DTSS_ALPHAARG2 = 6,
    D3DTSS_ADDRESSU = 13,
    D3DTSS_ADDRESSV = 14,
    D3DTSS_TEXTURETRANSFORMFLAGS = 24,
    D3DTSS_COUNT = 32,

    D3DPT_LINELIST = 2,
    D3DPT_TRIANGLELIST = 4,
    D3DPT_TRIANGLESTRIP = 5,
    D3DPT_TRIANGLEFAN = 6,

    D3DFVF_XYZ = 0x002,
    D3DFVF_DIFFUSE = 0x040,
    D3DFVF_TEXCOUNT_SHIFT = 8,

    D3DTTFF_COUNT2 = 2,
    D3DFMT_X8R8G8B8 = 22,
};

typedef float Matrix[16];  // row-major, row vectors (D3DMATRIX)

void multiply(const float* a, const float* b, float* out)
{
    for (int row = 0; row < 4; ++row)
        for (int column = 0; column < 4; ++column) {
            float sum = 0;
            for (int k = 0; k < 4; ++k)
                sum += a[row * 4 + k] * b[k * 4 + column];
            out[row * 4 + column] = sum;
        }
}

void transform(const float* m, float x, float y, float z, float w, float* out)
{
    for (int column = 0; column < 4; ++column)
        out[column] = x * m[column] + y * m[4 + column] + z * m[8 + column] + w * m[12 + column];
}

void identity(float* m)
{
    memset(m, 0, sizeof(Matrix));
    m[0] = m[5] = m[10] = m[15] = 1;
}

float as_float(int bits)
{
    float value;
    memcpy(&value, &bits, sizeof(value));
    return value;
}

struct EmuTexture {
    Direct3DTexture8 base;
    int refs;
    int id;
};

struct EmuVertexBuffer {
    Direct3DVertexBuffer8 base;
    unsigned char* data;
    unsigned int size;
};

struct EmuIndexBuffer {
    ObjectIndexBufferResource base;
    unsigned short* data;
    unsigned int size;
};

struct Device {
    Direct3DDevice8 base;
    int render_states[D3DRS_COUNT];
    int stage_states[D3DTSS_COUNT];
    Matrix world, view, projection, texture0;
    D3DViewport8 viewport;
    EmuTexture* texture;
    EmuVertexBuffer* stream;
    unsigned int stream_stride;
    EmuIndexBuffer* indices;
    unsigned int base_vertex;
    unsigned int fvf;
    RenderVertex* scratch;
    int scratch_capacity;
};

Device g_device;
int g_next_texture_id = 1;

RenderState snapshot()
{
    const int* rs = g_device.render_states;
    const int* ts = g_device.stage_states;
    RenderState state;
    state.texture = g_device.texture ? g_device.texture->id : 0;
    state.color_op = ts[D3DTSS_COLOROP];
    state.color_arg1 = ts[D3DTSS_COLORARG1];
    state.color_arg2 = ts[D3DTSS_COLORARG2];
    state.alpha_op = ts[D3DTSS_ALPHAOP];
    state.alpha_arg1 = ts[D3DTSS_ALPHAARG1];
    state.alpha_arg2 = ts[D3DTSS_ALPHAARG2];
    state.texture_factor = (unsigned int)rs[D3DRS_TEXTUREFACTOR];
    state.address_u = ts[D3DTSS_ADDRESSU];
    state.address_v = ts[D3DTSS_ADDRESSV];
    state.alpha_blend = rs[D3DRS_ALPHABLENDENABLE];
    state.src_blend = rs[D3DRS_SRCBLEND];
    state.dest_blend = rs[D3DRS_DESTBLEND];
    state.alpha_test = rs[D3DRS_ALPHATESTENABLE];
    state.alpha_func = rs[D3DRS_ALPHAFUNC];
    state.alpha_ref = rs[D3DRS_ALPHAREF];
    state.z_enable = rs[D3DRS_ZENABLE];
    state.z_write = rs[D3DRS_ZWRITEENABLE];
    state.z_func = rs[D3DRS_ZFUNC];
    state.cull = rs[D3DRS_CULLMODE];
    state.fog = rs[D3DRS_FOGENABLE];
    state.fog_color = (unsigned int)rs[D3DRS_FOGCOLOR];
    state.viewport_x = (int)g_device.viewport.x;
    state.viewport_y = (int)g_device.viewport.y;
    state.viewport_width = (int)g_device.viewport.width;
    state.viewport_height = (int)g_device.viewport.height;
    state.viewport_min_z = g_device.viewport.min_z;
    state.viewport_max_z = g_device.viewport.max_z;
    return state;
}

RenderVertex* reserve(int count)
{
    if (count > g_device.scratch_capacity) {
        g_device.scratch_capacity = count * 2;
        g_device.scratch = (RenderVertex*)realloc(g_device.scratch, g_device.scratch_capacity * sizeof(RenderVertex));
    }
    return g_device.scratch;
}

// The fixed-function vertex stage for one stream vertex.
struct VertexStage {
    Matrix world_view, clip;
    bool fog, texture_transform;
    float fog_start, fog_end;
    unsigned int diffuse_offset, texture_offset;
    bool has_diffuse, has_texture;

    VertexStage()
    {
        const int* rs = g_device.render_states;
        Matrix projection;
        draw_distance_projection(g_device.projection, projection);
        multiply(g_device.world, g_device.view, world_view);
        multiply(world_view, projection, clip);
        fog = rs[D3DRS_FOGENABLE] != 0;
        fog_start = as_float(rs[D3DRS_FOGSTART]) * draw_distance_scale();
        fog_end = as_float(rs[D3DRS_FOGEND]) * draw_distance_scale();
        texture_transform = g_device.stage_states[D3DTSS_TEXTURETRANSFORMFLAGS] == D3DTTFF_COUNT2;
        has_diffuse = (g_device.fvf & D3DFVF_DIFFUSE) != 0;
        has_texture = ((g_device.fvf >> D3DFVF_TEXCOUNT_SHIFT) & 0xf) != 0;
        diffuse_offset = 12;
        texture_offset = has_diffuse ? 16 : 12;
    }

    void run(unsigned int index, RenderVertex* out) const
    {
        const unsigned char* source = g_device.stream->data + index * g_device.stream_stride;
        const float* position = (const float*)source;
        float clip_position[4];
        transform(clip, position[0], position[1], position[2], 1, clip_position);
        out->x = clip_position[0];
        out->y = clip_position[1];
        out->z = clip_position[2];
        out->w = clip_position[3];
        out->color = has_diffuse ? *(const unsigned int*)(source + diffuse_offset) : 0xffffffffu;
        float u = 0, v = 0;
        if (has_texture) {
            u = ((const float*)(source + texture_offset))[0];
            v = ((const float*)(source + texture_offset))[1];
        }
        if (texture_transform) {
            float coordinates[4];
            transform(g_device.texture0, u, v, 1, 0, coordinates);
            u = coordinates[0];
            v = coordinates[1];
        }
        out->u = u;
        out->v = v;
        out->fog = 1;
        if (fog) {
            // Fog depth is the eye-space z's magnitude: Direct3D drivers take
            // abs(z) for vertex fog on every GPU (Wine's d3d9 visual tests,
            // test_negative_fixedfunction_fog), and the game's right-handed
            // view puts everything ahead at negative z.
            float eye[4];
            transform(world_view, position[0], position[1], position[2], 1, eye);
            float depth = eye[2] < 0 ? -eye[2] : eye[2];
            float factor = fog_end != fog_start ? (fog_end - depth) / (fog_end - fog_start) : 1;
            out->fog = factor < 0 ? 0 : factor > 1 ? 1 : factor;
        }
    }
};

// Expands a primitive range into the backend's lists. `index` maps a
// primitive-relative vertex number to a stream vertex.
template <typename IndexOf>
int draw(unsigned int type, unsigned int count, IndexOf index)
{
    if (!g_device.stream || count == 0)
        return 0;
    int primitive = type == D3DPT_LINELIST ? RENDER_LINES : RENDER_TRIANGLES;
    int vertex_count = type == D3DPT_LINELIST ? count * 2 : count * 3;
    RenderVertex* out = reserve(vertex_count);
    VertexStage stage;
    for (unsigned int i = 0; i < count; ++i) {
        switch (type) {
        case D3DPT_LINELIST:
            stage.run(index(i * 2), &out[i * 2]);
            stage.run(index(i * 2 + 1), &out[i * 2 + 1]);
            break;
        case D3DPT_TRIANGLELIST:
            for (int k = 0; k < 3; ++k)
                stage.run(index(i * 3 + k), &out[i * 3 + k]);
            break;
        case D3DPT_TRIANGLESTRIP:  // keep the winding of odd triangles
            stage.run(index(i), &out[i * 3]);
            stage.run(index(i + 1 + (i & 1)), &out[i * 3 + 1]);
            stage.run(index(i + 2 - (i & 1)), &out[i * 3 + 2]);
            break;
        case D3DPT_TRIANGLEFAN:
            stage.run(index(0), &out[i * 3]);
            stage.run(index(i + 1), &out[i * 3 + 1]);
            stage.run(index(i + 2), &out[i * 3 + 2]);
            break;
        default:
            return -1;
        }
    }
    RenderState state = snapshot();
    backend_draw(primitive, out, vertex_count, &state);
    return 0;
}

// --- textures, buffers ------------------------------------------------------

int __stdcall texture_release(Direct3DTexture8* self)
{
    EmuTexture* texture = (EmuTexture*)self;
    if (--texture->refs > 0)
        return texture->refs;
    if (g_device.texture == texture)
        g_device.texture = 0;
    backend_destroy_texture(texture->id);
    free(texture);
    return 0;
}

Direct3DTexture8Vtbl g_texture_vtable = {{0}, texture_release};

int __stdcall vertex_buffer_lock(Direct3DVertexBuffer8* self, unsigned int offset, unsigned int, void** data, unsigned int)
{
    *data = ((EmuVertexBuffer*)self)->data + offset;
    return 0;
}
int __stdcall vertex_buffer_unlock(Direct3DVertexBuffer8*) { return 0; }

Direct3DVertexBuffer8Vtbl make_vertex_buffer_vtable()
{
    Direct3DVertexBuffer8Vtbl vtable;
    memset(&vtable, 0, sizeof(vtable));
    vtable.Lock = vertex_buffer_lock;
    vtable.Unlock = vertex_buffer_unlock;
    return vtable;
}
Direct3DVertexBuffer8Vtbl g_vertex_buffer_vtable = make_vertex_buffer_vtable();

int __stdcall index_buffer_lock(ObjectIndexBufferResource* self, int offset, int, void** data, int)
{
    *data = (char*)((EmuIndexBuffer*)self)->data + offset;
    return 0;
}
int __stdcall index_buffer_unlock(ObjectIndexBufferResource*) { return 0; }

ObjectIndexBufferResourceVtbl make_index_buffer_vtable()
{
    ObjectIndexBufferResourceVtbl vtable;
    memset(&vtable, 0, sizeof(vtable));
    vtable.Lock = index_buffer_lock;
    vtable.Unlock = index_buffer_unlock;
    return vtable;
}
ObjectIndexBufferResourceVtbl g_index_buffer_vtable = make_index_buffer_vtable();

// --- device -------------------------------------------------------------------

int __stdcall device_release(Direct3DDevice8*) { return 0; }
int __stdcall device_reset(Direct3DDevice8*, D3DPresentParameters*) { return 0; }

int __stdcall device_present(Direct3DDevice8*, void*, void*, int, void*)
{
    backend_present();
    return 0;
}

int __stdcall device_create_vertex_buffer(Direct3DDevice8*, unsigned int length, unsigned int, unsigned int,
    unsigned int, Direct3DVertexBuffer8** out)
{
    EmuVertexBuffer* buffer = (EmuVertexBuffer*)calloc(1, sizeof(EmuVertexBuffer));
    buffer->base.vtbl = &g_vertex_buffer_vtable;
    buffer->data = (unsigned char*)calloc(length ? length : 1, 1);
    buffer->size = length;
    *out = &buffer->base;
    return 0;
}

int __stdcall device_create_index_buffer(Direct3DDevice8*, unsigned int length, unsigned int, unsigned int,
    unsigned int, ObjectIndexBufferResource** out)
{
    EmuIndexBuffer* buffer = (EmuIndexBuffer*)calloc(1, sizeof(EmuIndexBuffer));
    buffer->base.vtbl = &g_index_buffer_vtable;
    buffer->data = (unsigned short*)calloc(length ? length : 2, 1);
    buffer->size = length;
    *out = &buffer->base;
    return 0;
}

int __stdcall device_begin_scene(Direct3DDevice8*) { return 0; }
int __stdcall device_end_scene(Direct3DDevice8*) { return 0; }

int __stdcall device_clear(Direct3DDevice8*, unsigned int, void*, unsigned int flags, unsigned int color, float z,
    unsigned int)
{
    RenderState state = snapshot();
    backend_clear((int)flags & (RENDER_CLEAR_TARGET | RENDER_CLEAR_Z), color, z, &state);
    return 0;
}

float* transform_slot(int state)
{
    switch (state) {
    case D3DTS_VIEW: return g_device.view;
    case D3DTS_PROJECTION: return g_device.projection;
    case D3DTS_TEXTURE0: return g_device.texture0;
    case D3DTS_WORLD: return g_device.world;
    default: return 0;
    }
}

int __stdcall device_set_transform(Direct3DDevice8*, int state, TransformMatrix* matrix)
{
    float* slot = transform_slot(state);
    if (!slot)
        return -1;
    memcpy(slot, matrix, sizeof(Matrix));
    return 0;
}

int __stdcall device_get_transform(Direct3DDevice8*, int state, TransformMatrix* matrix)
{
    float* slot = transform_slot(state);
    if (!slot)
        return -1;
    memcpy(matrix, slot, sizeof(Matrix));
    return 0;
}

int __stdcall device_multiply_transform(Direct3DDevice8*, int state, TransformMatrix* matrix)
{
    float* slot = transform_slot(state);
    if (!slot)
        return -1;
    Matrix product;
    multiply(slot, (const float*)matrix, product);
    memcpy(slot, product, sizeof(Matrix));
    return 0;
}

int __stdcall device_set_viewport(Direct3DDevice8*, D3DViewport8* viewport)
{
    g_device.viewport = *viewport;
    return 0;
}

int __stdcall device_get_viewport(Direct3DDevice8*, D3DViewport8* viewport)
{
    *viewport = g_device.viewport;
    return 0;
}

int __stdcall device_set_render_state(Direct3DDevice8*, int state, int value)
{
    if (state < 0 || state >= D3DRS_COUNT)
        return -1;
    g_device.render_states[state] = value;
    return 0;
}

int __stdcall device_set_texture(Direct3DDevice8*, unsigned int stage, Direct3DTexture8* texture)
{
    if (stage != 0)
        return 0;
    g_device.texture = (EmuTexture*)texture;
    return 0;
}

int __stdcall device_set_texture_stage_state(Direct3DDevice8*, unsigned int stage, unsigned int type, unsigned int value)
{
    if (stage == 0 && type < D3DTSS_COUNT)
        g_device.stage_states[type] = (int)value;
    return 0;
}

int __stdcall device_draw_primitive(Direct3DDevice8*, unsigned int type, unsigned int start, unsigned int count)
{
    return draw(type, count, [start](unsigned int i) { return start + i; });
}

int __stdcall device_draw_indexed_primitive(Direct3DDevice8*, unsigned int type, unsigned int, unsigned int,
    unsigned int start_index, unsigned int count)
{
    if (!g_device.indices)
        return -1;
    const unsigned short* indices = g_device.indices->data + start_index;
    unsigned int base = g_device.base_vertex;
    return draw(type, count, [indices, base](unsigned int i) { return base + indices[i]; });
}

int __stdcall device_set_vertex_shader(Direct3DDevice8*, unsigned int fvf)
{
    g_device.fvf = fvf;
    return 0;
}

int __stdcall device_set_stream_source(Direct3DDevice8*, unsigned int stream, VertexBuffer* buffer, unsigned int stride)
{
    if (stream == 0) {
        g_device.stream = (EmuVertexBuffer*)buffer;
        g_device.stream_stride = stride;
    }
    return 0;
}

int __stdcall device_set_indices(Direct3DDevice8*, void* buffer, unsigned int base_vertex)
{
    g_device.indices = (EmuIndexBuffer*)buffer;
    g_device.base_vertex = base_vertex;
    return 0;
}

Direct3DDevice8Vtbl make_device_vtable()
{
    Direct3DDevice8Vtbl vtable;
    memset(&vtable, 0, sizeof(vtable));
    vtable.Release = device_release;
    vtable.Reset = device_reset;
    vtable.Present = device_present;
    vtable.CreateVertexBuffer = device_create_vertex_buffer;
    vtable.CreateIndexBuffer = device_create_index_buffer;
    vtable.BeginScene = device_begin_scene;
    vtable.EndScene = device_end_scene;
    vtable.Clear = device_clear;
    vtable.SetTransform = device_set_transform;
    vtable.GetTransform = device_get_transform;
    vtable.MultiplyTransform = device_multiply_transform;
    vtable.SetViewport = device_set_viewport;
    vtable.GetViewport = device_get_viewport;
    vtable.SetRenderState = device_set_render_state;
    vtable.SetTexture = device_set_texture;
    vtable.SetTextureStageState = device_set_texture_stage_state;
    vtable.DrawPrimitive = device_draw_primitive;
    vtable.DrawIndexedPrimitive = device_draw_indexed_primitive;
    vtable.SetVertexShader = device_set_vertex_shader;
    vtable.SetStreamSource = device_set_stream_source;
    vtable.SetIndices = device_set_indices;
    return vtable;
}
Direct3DDevice8Vtbl g_device_vtable = make_device_vtable();

// Direct3D 8 device defaults for the states the device interprets.
void reset_device(unsigned int width, unsigned int height)
{
    memset(g_device.render_states, 0, sizeof(g_device.render_states));
    memset(g_device.stage_states, 0, sizeof(g_device.stage_states));
    int* rs = g_device.render_states;
    rs[D3DRS_ZENABLE] = 1;  // an auto depth-stencil buffer was requested
    rs[D3DRS_ZWRITEENABLE] = 1;
    rs[D3DRS_SRCBLEND] = 2;   // ONE
    rs[D3DRS_DESTBLEND] = 1;  // ZERO
    rs[D3DRS_CULLMODE] = 3;   // CCW
    rs[D3DRS_ZFUNC] = 4;      // LESSEQUAL
    rs[D3DRS_ALPHAFUNC] = 8;  // ALWAYS
    rs[D3DRS_TEXTUREFACTOR] = (int)0xffffffff;
    rs[D3DRS_FOGEND] = 0x3f800000;  // 1.0f
    rs[D3DRS_LIGHTING] = 1;
    int* ts = g_device.stage_states;
    ts[D3DTSS_COLOROP] = 4;    // MODULATE
    ts[D3DTSS_COLORARG1] = 2;  // TEXTURE
    ts[D3DTSS_COLORARG2] = 1;  // CURRENT
    ts[D3DTSS_ALPHAOP] = 2;    // SELECTARG1
    ts[D3DTSS_ALPHAARG1] = 2;  // TEXTURE
    ts[D3DTSS_ALPHAARG2] = 1;  // CURRENT
    ts[D3DTSS_ADDRESSU] = 1;   // WRAP
    ts[D3DTSS_ADDRESSV] = 1;
    identity(g_device.world);
    identity(g_device.view);
    identity(g_device.projection);
    identity(g_device.texture0);
    g_device.viewport.x = g_device.viewport.y = 0;
    g_device.viewport.width = width;
    g_device.viewport.height = height;
    g_device.viewport.min_z = 0;
    g_device.viewport.max_z = 1;
    g_device.texture = 0;
    g_device.stream = 0;
    g_device.indices = 0;
}

// --- Direct3D 8 ---------------------------------------------------------------

int __stdcall d3d8_release(Direct3D8*) { return 0; }

int __stdcall d3d8_get_adapter_display_mode(Direct3D8*, unsigned int, D3DDisplayMode* mode)
{
    mode->width = 640;
    mode->height = 480;
    mode->refresh_rate = 60;
    mode->format = D3DFMT_X8R8G8B8;
    return 0;
}

int __stdcall d3d8_get_device_caps(Direct3D8*, unsigned int, unsigned int, D3DDeviceCaps8* caps)
{
    memset(caps, 0, sizeof(*caps));
    caps->max_texture_width = 2048;
    caps->max_texture_height = 2048;
    return 0;
}

int __stdcall d3d8_create_device(Direct3D8*, unsigned int, unsigned int, int, unsigned int,
    D3DPresentParameters* parameters, Direct3DDevice8** out)
{
    g_device.base.vtbl = &g_device_vtable;
    reset_device(parameters->back_buffer_width, parameters->back_buffer_height);
    *out = &g_device.base;
    return 0;
}

Direct3D8Vtbl make_d3d8_vtable()
{
    Direct3D8Vtbl vtable;
    memset(&vtable, 0, sizeof(vtable));
    vtable.Release = d3d8_release;
    vtable.GetAdapterDisplayMode = d3d8_get_adapter_display_mode;
    vtable.GetDeviceCaps = d3d8_get_device_caps;
    vtable.CreateDevice = d3d8_create_device;
    return vtable;
}
Direct3D8Vtbl g_d3d8_vtable = make_d3d8_vtable();
Direct3D8 g_d3d8 = {&g_d3d8_vtable};

}  // namespace

Direct3D8* __stdcall Direct3DCreate8(unsigned int)
{
    return &g_d3d8;
}

Direct3DTexture8* create_emulated_texture(int width, int height, const unsigned char* rgba)
{
    EmuTexture* texture = (EmuTexture*)calloc(1, sizeof(EmuTexture));
    texture->base.vtbl = &g_texture_vtable;
    texture->refs = 1;
    texture->id = g_next_texture_id++;
    backend_create_texture(texture->id, width, height, rgba);
    return &texture->base;
}
