// render_object_toon @ 0x4123e0 (cdecl)

#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"
#include "vector3.h"

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

    Vector3 camera_delta;
    camera_delta.x = g_render_camera_source_matrix->position.x - matrix->position.x;
    camera_delta.y = g_render_camera_source_matrix->position.y - matrix->position.y;
    camera_delta.z = g_render_camera_source_matrix->position.z - matrix->position.z;
    Vector3 view_vector = camera_delta;

    TransformMatrix inverse = *matrix;
    inverse.invert_matrix_in_place();
    view_vector.rotate_vector_by_matrix(&inverse);
    view_vector.vector_magnitude();

    g_d3d_device->vtbl->SetIndices(g_d3d_device, object->toon_index_buffer->buffer, 0);
    g_d3d_device->vtbl->SetStreamSource(
        g_d3d_device, 0, object->render_buffers->vertex_buffer,
        sizeof(ObjectRenderVertex));

    int edge_index = 0;
    if (object->edge_count > 0) {
        int edge_offset = 0;
        do {
            int emitted = 0;
            unsigned short* indices;
            object->toon_index_buffer->buffer->vtbl->Lock(
                object->toon_index_buffer->buffer, 0,
                object->vertex_count * sizeof(unsigned short),
                (void**)&indices, 0);

            if ((((ObjectToonEdge*)((char*)object->edges + edge_offset))->flags & 1) != 0) {
                indices[0] = ((ObjectToonEdge*)((char*)object->edges + edge_offset))->vertex_a;
                indices[1] = ((ObjectToonEdge*)((char*)object->edges + edge_offset))->vertex_b;
                emitted = 2;
            } else {
                Vector3* normal_a = &object->facequad_normals[
                    ((ObjectToonEdge*)((char*)object->edges + edge_offset))->normal_a];
                Vector3* normal_b = &object->facequad_normals[
                    ((ObjectToonEdge*)((char*)object->edges + edge_offset))->normal_b];
                Vector3* vertex = &object->vertices[
                    ((ObjectToonEdge*)((char*)object->edges + edge_offset))->vertex_a];
                Vector3 vertex_delta;
                vertex_delta.x = view_vector.x - vertex->x;
                vertex_delta.y = view_vector.y - vertex->y;
                vertex_delta.z = view_vector.z - vertex->z;
                Vector3 delta = vertex_delta;

                float side_b = delta.dot_vector(normal_b);
                if (delta.dot_vector(normal_a) * side_b <
                    0.00999999978f) {
                    indices[0] =
                        ((ObjectToonEdge*)((char*)object->edges + edge_offset))->vertex_a;
                    indices[1] =
                        ((ObjectToonEdge*)((char*)object->edges + edge_offset))->vertex_b;
                    emitted = 2;
                }
            }

            object->toon_index_buffer->buffer->vtbl->Unlock(object->toon_index_buffer->buffer);

            if (emitted > 0) {
                bind_texture_ref(g_sprite_manager.get_sprite_texture(0x5d));
                Direct3DDevice8* device = g_d3d_device;
                int primitive_count = emitted / 2;
                device->vtbl->DrawIndexedPrimitive(
                    device, 2, 0, object->grouped_vertex_count, 0, primitive_count);
                g_render_triangle_count += primitive_count;
                ++g_draw_primitive_call_count;
            }

            ++edge_index;
            edge_offset += sizeof(ObjectToonEdge);
        } while (edge_index < object->edge_count);
    }

    build_perspective_projection_matrix(
        &projection,
        g_render_projection_param_a,
        g_render_projection_param_b,
        g_render_projection_near_z,
        g_render_projection_far_z);
    return g_d3d_device->vtbl->SetTransform(g_d3d_device, 3, &projection);
}
