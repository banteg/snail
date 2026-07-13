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

        for (int i = 0; i < object->grouped_vertex_count; ++i) {
            *(Vector3*)&vertices[i] = object->vertices[i];
        }

        object->render_buffers->vertex_buffer->vtbl->Unlock(object->render_buffers->vertex_buffer);
    } else if ((flags & 4) != 0) {
        ObjectRenderVertex* vertices;
        object->render_buffers->vertex_buffer->vtbl->Lock(
            object->render_buffers->vertex_buffer, 0, object->grouped_vertex_count * 0x18,
            (void**)&vertices, 0);

        for (int i = 0; i < object->grouped_vertex_count; ++i) {
            *(Vector3*)&vertices[i] = object->vertices[i];
            vertices[i].u = object->facequads[i / 4].uv[i & 3].u;
            vertices[i].v = object->facequads[i / 4].uv[i & 3].v;
        }

        object->render_buffers->vertex_buffer->vtbl->Unlock(object->render_buffers->vertex_buffer);
    }
}
