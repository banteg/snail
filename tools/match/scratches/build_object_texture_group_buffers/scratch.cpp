// build_object_texture_group_buffers @ 0x413d50 (cdecl)

#include "sprite.h"
#include "object_render_types.h"
#include "render_buffer_factories.h"
#include "vector3.h"

void* allocate_tracked_memory(int size, char* name);
int get_archive_data_base();
int get_archive_data_end();
void* memcpy(void* destination, const void* source, unsigned int count);

int get_or_append_object_texture_group_vertex(Object* object, int vertex_index, float u, float v);

struct ObjectVertexBufferVtbl {
    char unknown_00[0x2c];
    int (__stdcall* Lock)(ObjectVertexBuffer* self, int offset, int size,
        void** data, int flags);
    int (__stdcall* Unlock)(ObjectVertexBuffer* self);
};

extern int g_object_grouped_vertex_cursor; // data_5031bc
extern ObjectGroupedVertex* g_object_grouped_vertex_scratch; // data_5031c4

void* build_object_texture_group_buffers(Object* object)
{
    if (object->vertex_count == 0) {
        object->group_index_starts = 0;
        object->group_texture_refs = 0;
        object->group_primitive_counts = 0;
        object->render_buffers = 0;
        object->index_buffer = 0;
        return 0;
    }

    object->flags |= 0x80000;
    object->group_index_starts =
        (int*)allocate_tracked_memory(object->texture_group_count << 2, "DX TextureGroups");
    object->group_texture_refs =
        (TextureRef**)allocate_tracked_memory(object->texture_group_count << 2,
            "DX TextureGroupsTexture Ref");
    object->group_primitive_counts =
        (int*)allocate_tracked_memory(object->texture_group_count << 2,
            "DX TextureGroupsTexture Primcount");

    g_object_grouped_vertex_scratch = (ObjectGroupedVertex*)get_archive_data_base();
    unsigned short* index_scratch = (unsigned short*)get_archive_data_end();
    g_object_grouped_vertex_cursor = 0;

    if ((object->flags & 4) != 0) {
        for (int vertex_index = 0; vertex_index < object->vertex_count; ++vertex_index) {
            for (int face_index = 0; face_index < object->facequad_count; ++face_index) {
                ObjectFaceQuad* quad = &object->facequads[face_index];
                if (quad->vertex_0 == vertex_index)
                    get_or_append_object_texture_group_vertex(
                        object, vertex_index, quad->uv[0].u, quad->uv[0].v);
                if (quad->vertex_1 == vertex_index)
                    get_or_append_object_texture_group_vertex(
                        object, vertex_index, quad->uv[1].u, quad->uv[1].v);
                if (quad->vertex_2 == vertex_index)
                    get_or_append_object_texture_group_vertex(
                        object, vertex_index, quad->uv[2].u, quad->uv[2].v);
                if ((quad->flags & 0x80) == 0 && quad->vertex_3 == vertex_index)
                    get_or_append_object_texture_group_vertex(
                        object, vertex_index, quad->uv[3].u, quad->uv[3].v);
            }
        }
    }

    int face_index = 0;
    int index_count = 0;
    for (int group = 0; group < object->texture_group_count; ++group) {
        int primitive_count = 0;
        object->group_texture_refs[group] = object->facequads[face_index].texture_ref;
        object->group_index_starts[group] = index_count;

        while (face_index < object->texture_group_ends[group]) {
            ObjectFaceQuad* quad = &object->facequads[face_index];
            unsigned short* out = &index_scratch[index_count];

            out[0] = (unsigned short)get_or_append_object_texture_group_vertex(
                object, quad->vertex_0, quad->uv[0].u, quad->uv[0].v);
            out[1] = (unsigned short)get_or_append_object_texture_group_vertex(
                object, quad->vertex_1, quad->uv[1].u, quad->uv[1].v);
            out[2] = (unsigned short)get_or_append_object_texture_group_vertex(
                object, quad->vertex_2, quad->uv[2].u, quad->uv[2].v);

            if ((quad->flags & 0x80) != 0) {
                index_count += 3;
                primitive_count += 1;
            } else {
                out[3] = out[0];
                out[4] = out[2];
                out[5] = (unsigned short)get_or_append_object_texture_group_vertex(
                    object, quad->vertex_3, quad->uv[3].u, quad->uv[3].v);
                index_count += 6;
                primitive_count += 2;
            }

            ++face_index;
        }

        object->group_primitive_counts[group] = primitive_count;
    }

    object->grouped_vertex_count = g_object_grouped_vertex_cursor;
    object->render_buffers =
        g_direct3d_renderer.create_vertex_buffer(g_object_grouped_vertex_cursor, 0x142);
    object->index_buffer = g_object_index_buffer_factory.create_index_buffer(index_count);

    ObjectRenderVertex* locked_vertices;
    object->render_buffers->vertex_buffer->vtbl->Lock(
        object->render_buffers->vertex_buffer, 0, g_object_grouped_vertex_cursor * 0x18,
        (void**)&locked_vertices, 0);

    for (int i = 0; i < g_object_grouped_vertex_cursor; ++i) {
        locked_vertices[i].diffuse = g_object_grouped_vertex_scratch[i].diffuse;
        locked_vertices[i].u = g_object_grouped_vertex_scratch[i].u;
        locked_vertices[i].v = g_object_grouped_vertex_scratch[i].v;
        locked_vertices[i].x = g_object_grouped_vertex_scratch[i].x;
        locked_vertices[i].y = g_object_grouped_vertex_scratch[i].y;
        locked_vertices[i].z = g_object_grouped_vertex_scratch[i].z;
    }

    object->render_buffers->vertex_buffer->vtbl->Unlock(object->render_buffers->vertex_buffer);

    void* locked_indices;
    object->index_buffer->buffer->vtbl->Lock(
        object->index_buffer->buffer, 0, index_count * 2, &locked_indices, 0);
    memcpy(locked_indices, index_scratch, index_count * 2);
    object->index_buffer->buffer->vtbl->Unlock(object->index_buffer->buffer);

    void* result = (void*)object->flags;
    if ((object->flags & 0x4000) != 0) {
        result = g_object_index_buffer_factory.create_index_buffer(index_count);
        object->toon_index_buffer = (ObjectIndexBuffer*)result;
    }

    return result;
}
