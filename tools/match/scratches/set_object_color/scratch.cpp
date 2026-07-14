// set_object_color @ 0x4141d0 (cdecl)

#include "object_render_types.h"
#include "sprite.h"

extern int g_object_grouped_vertex_cursor; // data_5031bc

void set_object_color(Object* object, tColour color)
{
    tColourSmall out;
    ObjectRenderVertex* vertices;

    out.noop_this_constructor();
    out.pack_color_rgba_u8(&color);

    if ((object->flags & OBJECT_FLAG_RENDER_BUFFERS_READY) != 0) {
        object->render_buffers->vertex_buffer->vtbl->Lock(
            object->render_buffers->vertex_buffer, 0, g_object_grouped_vertex_cursor * 0x18,
            (void**)&vertices, 0);

        int i = 0;
        if (object->grouped_vertex_count > 0) {
            do {
                vertices[i].diffuse = *(unsigned int*)&out;
                ++i;
            } while (i < object->grouped_vertex_count);
        }

        object->render_buffers->vertex_buffer->vtbl->Unlock(
            object->render_buffers->vertex_buffer);
    }
}
