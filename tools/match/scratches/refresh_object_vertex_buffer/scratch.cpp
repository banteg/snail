// refresh_object_vertex_buffer @ 0x412250 (cdecl)

#include "object_animation_types.h"
#include "object_render_types.h"

void refresh_object_vertex_buffer(Object* object)
{
    unsigned int flags = object->flags;
    if ((flags & 0x200000) != 0) {
        ObjectAnimation* animation = object->animation;
        int frame_index = (int)((float)animation->generated_frame_count * animation->progress);
        object->vertices = animation->frames[frame_index]->vertices;

        frame_index = (int)((float)animation->generated_frame_count * animation->progress);
        object->facequad_normals = animation->frames[frame_index]->facequad_normals;

        if ((flags & 0x800000) != 0) {
            ((ObjectDistort*)((char*)object + 0x80))->apply_distort_to_object((Object*)object);
        }

        ObjectRenderVertex* vertices;
        object->render_buffers->vertex_buffer->vtbl->Lock(
            object->render_buffers->vertex_buffer, 0, object->grouped_vertex_count * 0x18,
            (void**)&vertices, 0);

        int count = object->grouped_vertex_count;
        int i = 0;
        if (count > 0) {
            int destination_offset = 0;
            int source_offset = 0;
            Vector3* source_vertices = object->vertices;
            do {
                int* source = (int*)((char*)source_vertices + source_offset);
                int* destination = (int*)((char*)vertices + destination_offset);
                ++i;

                int x = source[0];
                source_offset += 0xc;
                destination[0] = x;

                destination_offset += 0x18;
                int y = source[1];
                destination[1] = y;

                int z = source[2];
                destination[2] = z;
            } while (i < object->grouped_vertex_count);
        }

        object->render_buffers->vertex_buffer->vtbl->Unlock(object->render_buffers->vertex_buffer);
    } else if ((flags & 4) != 0) {
        ObjectRenderVertex* vertices;
        object->render_buffers->vertex_buffer->vtbl->Lock(
            object->render_buffers->vertex_buffer, 0, object->grouped_vertex_count * 0x18,
            (void**)&vertices, 0);

        int count = object->grouped_vertex_count;
        int i = 0;
        if (count > 0) {
            int destination_offset = 0;
            int source_offset = 0;
            do {
                int* source = (int*)((char*)object->vertices + source_offset);
                int* destination = (int*)((char*)vertices + destination_offset);
                source_offset += 0xc;

                int x = source[0];
                destination_offset += 0x18;
                destination[0] = x;

                int y = source[1];
                destination[1] = y;

                int z = source[2];
                destination[2] = z;

                int quad_index = i / 4;
                int corner_index = i & 3;
                ++i;

                destination[4] = *(int*)&object->facequads[quad_index].uv[corner_index].u;
                destination[5] = *(int*)&object->facequads[quad_index].uv[corner_index].v;
            } while (i < object->grouped_vertex_count);
        }

        object->render_buffers->vertex_buffer->vtbl->Unlock(object->render_buffers->vertex_buffer);
    }
}
