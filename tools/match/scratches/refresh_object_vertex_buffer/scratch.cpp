// refresh_object_vertex_buffer @ 0x412250 (cdecl)

#include "object_animation_types.h"
#include "object_render_types.h"

void refresh_object_vertex_buffer(Object* object)
{
    unsigned int flags = object->flags;
    if ((flags & OBJECT_FLAG_HAS_ANIMATION) != 0) {
        ObjectAnimation* animation = object->animation;
        int frame_index = (int)((float)animation->generated_frame_count * animation->progress);
        object->vertices = animation->frames[frame_index]->vertices;

        frame_index = (int)((float)animation->generated_frame_count * animation->progress);
        object->facequad_normals = animation->frames[frame_index]->facequad_normals;

        if ((flags & OBJECT_FLAG_DISTORT_ENABLED) != 0) {
            object->distort.apply_distort_to_object(object);
        }

        ObjectRenderVertex* vertices;
        object->render_buffers->vertex_buffer->vtbl->Lock(
            object->render_buffers->vertex_buffer, 0,
            object->grouped_vertex_count * sizeof(ObjectRenderVertex),
            (void**)&vertices, 0);

        for (int i = 0; i < object->grouped_vertex_count; ++i) {
            *(Vector3*)&vertices[i] = object->vertices[i];
        }

        object->render_buffers->vertex_buffer->vtbl->Unlock(object->render_buffers->vertex_buffer);
    } else if ((flags & OBJECT_FLAG_DYNAMIC_VERTICES) != 0) {
        ObjectRenderVertex* vertices;
        object->render_buffers->vertex_buffer->vtbl->Lock(
            object->render_buffers->vertex_buffer, 0,
            object->grouped_vertex_count * sizeof(ObjectRenderVertex),
            (void**)&vertices, 0);

        for (int i = 0; i < object->grouped_vertex_count; ++i) {
            *(Vector3*)&vertices[i] = object->vertices[i];
            vertices[i].u = object->facequads[i / 4].uv[i & 3].u;
            vertices[i].v = object->facequads[i / 4].uv[i & 3].v;
        }

        object->render_buffers->vertex_buffer->vtbl->Unlock(object->render_buffers->vertex_buffer);
    }
}
