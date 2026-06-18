// render_object_toon @ 0x4123e0 (cdecl)

#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"
#include "vector3.h"

struct ToonVector3 {
    float x;
    float y;
    float z;

    double dot_vector(ToonVector3* rhs); // @ 0x44cb70
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

int render_object_toon(Object* object, TransformMatrix* matrix)
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
