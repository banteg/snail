// Headless renderer: a null Direct3D 8 device for the recovered code that still
// talks to the device directly (the loading screen, track render caches), and
// null G0 entry points. Stage 4 replaces these with SDL3 GPU rendering.

#include <stdlib.h>
#include <string.h>

#include "direct3d_device8_view.h"
#include "direct3d_renderer.h"
#include "display_mode_state.h"
#include "font_system.h"
#include "object_render_types.h"
#include "render_buffer_factories.h"
#include "sprite.h"
#include "transform_matrix.h"
#include "vector3.h"
#include "vertex_buffer_view.h"

namespace {

// Device methods the compiled code calls; every one succeeds and does nothing.
int __stdcall device_release(Direct3DDevice8*) { return 0; }
int __stdcall device_begin_scene(Direct3DDevice8*) { return 0; }
int __stdcall device_end_scene(Direct3DDevice8*) { return 0; }
int __stdcall device_clear(Direct3DDevice8*, unsigned int, void*, unsigned int, unsigned int, float, unsigned int) { return 0; }
int __stdcall device_set_texture(Direct3DDevice8*, unsigned int, Direct3DTexture8*) { return 0; }
int __stdcall device_set_texture_stage_state(Direct3DDevice8*, unsigned int, unsigned int, unsigned int) { return 0; }
int __stdcall device_draw_primitive(Direct3DDevice8*, unsigned int, unsigned int, unsigned int) { return 0; }
int __stdcall device_set_vertex_shader(Direct3DDevice8*, unsigned int) { return 0; }
int __stdcall device_set_stream_source(Direct3DDevice8*, unsigned int, VertexBuffer*, unsigned int) { return 0; }
int __stdcall device_set_render_state(Direct3DDevice8*, int, int) { return 0; }

Direct3DDevice8Vtbl make_device_vtable()
{
    Direct3DDevice8Vtbl vtable;
    memset(&vtable, 0, sizeof(vtable));
    vtable.Release = device_release;
    vtable.BeginScene = device_begin_scene;
    vtable.EndScene = device_end_scene;
    vtable.Clear = device_clear;
    vtable.SetTexture = device_set_texture;
    vtable.SetTextureStageState = device_set_texture_stage_state;
    vtable.DrawPrimitive = device_draw_primitive;
    vtable.SetVertexShader = device_set_vertex_shader;
    vtable.SetStreamSource = device_set_stream_source;
    vtable.SetRenderState = device_set_render_state;
    return vtable;
}

Direct3DDevice8Vtbl g_null_device_vtable = make_device_vtable();
Direct3DDevice8 g_null_device = {&g_null_device_vtable};

int __stdcall texture_release(Direct3DTexture8*) { return 0; }
Direct3DTexture8Vtbl g_null_texture_vtable = {{0}, texture_release};
Direct3DTexture8 g_null_texture;

// A vertex buffer whose Lock hands out real memory, as the loading screen fills it.
struct NullVertexBuffer {
    Direct3DVertexBuffer8 buffer;
    void* memory;
};

int __stdcall vertex_buffer_lock(Direct3DVertexBuffer8* self, unsigned int offset, unsigned int, void** data, unsigned int)
{
    *data = (char*)((NullVertexBuffer*)self)->memory + offset;
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

Direct3DVertexBuffer8Vtbl g_null_vertex_buffer_vtable = make_vertex_buffer_vtable();

// Bytes per vertex for a Direct3D 8 flexible vertex format.
unsigned int fvf_stride(unsigned int fvf)
{
    unsigned int stride = 0;
    switch (fvf & 0x0e) {
    case 0x02: stride += 12; break;  // XYZ
    case 0x04: stride += 16; break;  // XYZRHW
    default: break;
    }
    if (fvf & 0x10) stride += 12;  // NORMAL
    if (fvf & 0x40) stride += 4;   // DIFFUSE
    if (fvf & 0x80) stride += 4;   // SPECULAR
    stride += ((fvf >> 8) & 0x0f) * 8;  // TEXn, two floats each
    return stride;
}

// An index buffer of 16-bit indices whose Lock hands out real memory, as the
// track render caches fill it.
struct NullIndexBuffer {
    ObjectIndexBufferResource buffer;
    void* memory;
};

int __stdcall index_buffer_lock(ObjectIndexBufferResource* self, int offset, int, void** data, int)
{
    *data = (char*)((NullIndexBuffer*)self)->memory + offset;
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

ObjectIndexBufferResourceVtbl g_null_index_buffer_vtable = make_index_buffer_vtable();

struct NullDeviceInstaller {
    NullDeviceInstaller()
    {
        g_null_texture.vtbl = &g_null_texture_vtable;
        g_d3d_device = &g_null_device;
    }
} g_null_device_installer;

}  // namespace

ObjectRenderBuffers* VertexBufferFactory::create_vertex_buffer(int vertex_count, int fvf)
{
    ObjectRenderBuffers* entry = &buffers[count++];
    NullVertexBuffer* buffer = (NullVertexBuffer*)calloc(1, sizeof(NullVertexBuffer));
    buffer->buffer.vtbl = &g_null_vertex_buffer_vtable;
    buffer->memory = calloc(vertex_count ? vertex_count : 1, fvf_stride(fvf));
    entry->fvf = fvf;
    entry->vertex_buffer = &buffer->buffer;
    return entry;
}

ObjectIndexBuffer* IndexBufferFactory::create_index_buffer(int index_count)
{
    ObjectIndexBuffer* entry = &buffers[count++];
    NullIndexBuffer* buffer = (NullIndexBuffer*)calloc(1, sizeof(NullIndexBuffer));
    buffer->buffer.vtbl = &g_null_index_buffer_vtable;
    buffer->memory = calloc(index_count ? index_count : 1, sizeof(unsigned short));
    entry->buffer = &buffer->buffer;
    return entry;
}

int Direct3DRenderer::direct3d_renderer_set_cull_mode(char) { return 0; }
void Direct3DRenderer::direct3d_renderer_set_fullscreen_mode(char) {}
void DisplayModeState::clear_display_mode_state() {}
char DisplayModeState::update_display_mode_view_state() { return 0; }  // no display mode headless

extern "C" int __stdcall D3DXCreateTextureFromFileA(Direct3DDevice8*, char*, Direct3DTexture8** texture)
{
    *texture = &g_null_texture;
    return 0;
}

extern "C" int __stdcall D3DXCreateTextureFromFileExA(Direct3DDevice8*, char*, unsigned int, unsigned int,
    unsigned int, unsigned int, int, int, unsigned int, unsigned int, unsigned int, void*, void*,
    Direct3DTexture8** texture)
{
    *texture = &g_null_texture;
    return 0;
}

extern "C" int __stdcall D3DXCreateTextureFromFileInMemoryEx(Direct3DDevice8*, void*, unsigned int, unsigned int,
    unsigned int, unsigned int, unsigned int, int, int, unsigned int, unsigned int, unsigned int, void*, void*,
    Direct3DTexture8** texture)
{
    *texture = &g_null_texture;
    return 0;
}

// G0 entry points (port/replaced.txt): nothing to draw headless.
void render_camera(float, float, float, float, float, tMatrix*, tMatrix*, char, char) {}
void render_object(cRObject*, tMatrix*, float, float, tColour*, char) {}
int draw_sprite_quad(tVector*, cRSprite*) { return 0; }
void set_object_color(cRObject*, tColour) {}
void build_object_texture_group_buffers(cRObject*) {}
void set_fullscreen_mode(char) {}
void load_registered_texture_refs(int) {}
int present_backbuffer() { return 0; }
int begin_overlay_render_state() { return 0; }
void end_overlay_render_state() {}
void begin_sprite_depth_render_state() {}
void end_sprite_depth_render_state() {}
void draw_textured_quad_immediate(cRTexture*, float, float, float, float, float, float, float, float, float,
    float, float, float, float, float, tColour*, int, float)
{
}
