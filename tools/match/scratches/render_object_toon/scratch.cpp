// render_object_toon @ 0x4123e0 (cdecl)

#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"
#include "vector3.h"

struct ObjectIndexBufferResource;

struct ObjectIndexBufferResourceVtbl {
    char unknown_00[0x2c];
    int (__stdcall* Lock)(ObjectIndexBufferResource* self, int offset, int size,
        void** data, int flags);
    int (__stdcall* Unlock)(ObjectIndexBufferResource* self);
};

struct ObjectIndexBufferResource {
    ObjectIndexBufferResourceVtbl* vtbl;
};

struct ObjectIndexBuffer {
    ObjectIndexBufferResource* buffer; // +0x00
};

struct RenderObjectDeviceVtbl {
    char unknown_000[0x94];
    int (__stdcall* SetTransform)(RenderObjectDevice* self, int state, TransformMatrix* matrix);
    char unknown_098[0x11c - 0x98];
    int (__stdcall* DrawIndexedPrimitive)(RenderObjectDevice* self, int primitive_type,
        int min_vertex_index, int vertex_count, int start_index, int primitive_count);
    char unknown_120[0x14c - 0x120];
    int (__stdcall* SetStreamSource)(RenderObjectDevice* self, int stream,
        ObjectVertexBuffer* vertex_buffer, int stride);
    char unknown_150[0x154 - 0x150];
    int (__stdcall* SetIndices)(RenderObjectDevice* self,
        ObjectIndexBufferResource* index_buffer, int base_vertex_index);
};

struct ToonVector3 {
    float x;
    float y;
    float z;

    double dot_vector(ToonVector3* rhs); // @ 0x44cb70
};

struct ObjectToonEdge {
    unsigned char flags; // +0x00, bit 0 enables silhouette-normal test
    char unknown_01[0x04 - 0x01];
    unsigned short vertex_a; // +0x04
    char unknown_06[0x08 - 0x06];
    unsigned short vertex_b; // +0x08
    char unknown_0a[0x0c - 0x0a];
    int normal_a; // +0x0c
    int normal_b; // +0x10
    char unknown_14[0x24 - 0x14];
};

struct ObjectToonRenderView {
    char unknown_00[0x10];
    unsigned int flags; // +0x10
    char unknown_14[0x2c - 0x14];
    int vertex_count; // +0x2c
    char unknown_30[0x38 - 0x30];
    Vector3* vertices; // +0x38
    char unknown_3c[0x60 - 0x3c];
    Vector3* facequad_normals; // +0x60
    char unknown_64[0x70 - 0x64];
    int edge_count; // +0x70
    ObjectToonEdge* edges; // +0x74
    char unknown_78[0xc0 - 0x78];
    ObjectRenderBuffers* render_buffers; // +0xc0
    int grouped_vertex_count; // +0xc4
    char unknown_c8[0xd8 - 0xc8];
    ObjectIndexBuffer* toon_index_buffer; // +0xd8
};

extern RenderObjectDevice* g_d3d_device; // data_502fec
extern int g_render_triangle_count; // data_4f7450
extern int g_draw_primitive_call_count; // data_503170
extern TransformMatrix* g_render_camera_source_matrix; // data_5031b8
extern float g_render_projection_param_a; // data_5031d4
extern float g_render_projection_param_b; // data_50316c
extern float g_render_projection_near_z; // data_5031cc
extern float g_render_projection_far_z; // data_5031d0

TransformMatrix* __stdcall build_perspective_projection_matrix(
    TransformMatrix* matrix, float arg2, float arg3, float near_z, float far_z); // @ 0x450314
void bind_texture_ref(TextureRef* texture); // @ 0x414500
TextureRef* __stdcall get_sprite_texture(int texture_id); // @ 0x44e570

int render_object_toon(ObjectToonRenderView* object, TransformMatrix* matrix)
{
    unsigned int flags = object->flags;
    if ((flags & 0x4000) == 0) {
        return flags;
    }

    TransformMatrix projection;
    build_perspective_projection_matrix(
        &projection,
        g_render_projection_param_a,
        g_render_projection_param_b,
        g_render_projection_near_z + 0.00400000019f,
        g_render_projection_far_z + 30.0f);
    g_d3d_device->vtbl->SetTransform(g_d3d_device, 3, &projection);

    Vector3 view_vector;
    view_vector.x = g_render_camera_source_matrix->position.x - matrix->position.x;
    view_vector.y = g_render_camera_source_matrix->position.y - matrix->position.y;
    view_vector.z = g_render_camera_source_matrix->position.z - matrix->position.z;

    TransformMatrix inverse = *matrix;
    inverse.invert_matrix_in_place();
    view_vector.rotate_vector_by_matrix(&inverse);
    view_vector.vector_magnitude();

    g_d3d_device->vtbl->SetIndices(g_d3d_device, object->toon_index_buffer->buffer, 0);
    g_d3d_device->vtbl->SetStreamSource(
        g_d3d_device, 0, object->render_buffers->vertex_buffer, 0x18);

    for (int i = 0; i < object->edge_count; ++i) {
        ObjectToonEdge* edge = &object->edges[i];

        unsigned short* indices;
        object->toon_index_buffer->buffer->vtbl->Lock(
            object->toon_index_buffer->buffer, 0, object->vertex_count << 1,
            (void**)&indices, 0);

        int emitted = 0;
        if ((edge->flags & 1) != 0) {
            indices[0] = edge->vertex_a;
            indices[1] = edge->vertex_b;
            emitted = 2;
        } else {
            Vector3* vertex = &object->vertices[edge->vertex_a];
            ToonVector3 delta;
            delta.x = view_vector.x - vertex->x;
            delta.y = view_vector.y - vertex->y;
            delta.z = view_vector.z - vertex->z;

            double side_b =
                ((ToonVector3*)&delta)->dot_vector((ToonVector3*)&object->facequad_normals[edge->normal_b]);
            double side_a =
                ((ToonVector3*)&delta)->dot_vector((ToonVector3*)&object->facequad_normals[edge->normal_a]);
            if (side_a * side_b < 0.00999999978f) {
                indices[0] = edge->vertex_a;
                indices[1] = edge->vertex_b;
                emitted = 2;
            }
        }

        object->toon_index_buffer->buffer->vtbl->Unlock(object->toon_index_buffer->buffer);

        if (emitted > 0) {
            bind_texture_ref(get_sprite_texture(0x5d));
            int primitive_count = emitted / 2;
            g_d3d_device->vtbl->DrawIndexedPrimitive(
                g_d3d_device, 2, 0, object->grouped_vertex_count, 0, primitive_count);
            g_render_triangle_count += primitive_count;
            ++g_draw_primitive_call_count;
        }
    }

    build_perspective_projection_matrix(
        &projection,
        g_render_projection_param_a,
        g_render_projection_param_b,
        g_render_projection_near_z,
        g_render_projection_far_z);
    return g_d3d_device->vtbl->SetTransform(g_d3d_device, 3, &projection);
}
