// build_object_texture_group_buffers @ 0x413d50 (cdecl)

#include "sprite.h"
#include "object_render_types.h"
#include "render_buffer_factories.h"
#include "vector3.h"

void* allocate_tracked_memory(int size, char* name);
int get_archive_data_base();
int get_archive_data_end();
extern "C" void* memcpy(void* destination, const void* source, unsigned int count);
#pragma intrinsic(memcpy)

int get_or_append_object_texture_group_vertex(Object* object, int vertex_index, float u, float v);

extern int g_object_grouped_vertex_cursor; // data_5031bc
extern ObjectGroupedVertex* g_object_grouped_vertex_scratch; // data_5031c4

void build_object_texture_group_buffers(Object* object)
{
    if (object->vertex_count == 0) {
        object->group_index_starts = 0;
        object->group_texture_refs = 0;
        object->group_primitive_counts = 0;
        object->render_buffers = 0;
        object->index_buffer = 0;
        return;
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

    unsigned char flags_byte = (unsigned char)object->flags;
    int face_index = 0;
    int index_count = 0;

    if ((flags_byte & 4) != 0) {
        for (int vertex_index = 0; vertex_index < object->vertex_count; ++vertex_index) {
            for (int scan_face_index = 0; scan_face_index < object->facequad_count; ++scan_face_index) {
                if (object->facequads[scan_face_index].vertex_0 == vertex_index)
                    get_or_append_object_texture_group_vertex(
                        object, vertex_index, object->facequads[scan_face_index].uv[0].u,
                        object->facequads[scan_face_index].uv[0].v);
                else if (object->facequads[scan_face_index].vertex_1 == vertex_index)
                    get_or_append_object_texture_group_vertex(
                        object, vertex_index, object->facequads[scan_face_index].uv[1].u,
                        object->facequads[scan_face_index].uv[1].v);
                else if (object->facequads[scan_face_index].vertex_2 == vertex_index)
                    get_or_append_object_texture_group_vertex(
                        object, vertex_index, object->facequads[scan_face_index].uv[2].u,
                        object->facequads[scan_face_index].uv[2].v);
                else if ((object->facequads[scan_face_index].flags & 0x80) == 0
                    && object->facequads[scan_face_index].vertex_3 == vertex_index)
                    get_or_append_object_texture_group_vertex(
                        object, vertex_index, object->facequads[scan_face_index].uv[3].u,
                        object->facequads[scan_face_index].uv[3].v);
            }
        }
    }

    for (int group = 0; group < object->texture_group_count; ++group) {
        int primitive_count = 0;
        object->group_texture_refs[group] = object->facequads[face_index].texture_ref;
        object->group_index_starts[group] = index_count;

        if (face_index < object->texture_group_ends[group]) {
            int face_offset = face_index * sizeof(ObjectFaceQuad);
            unsigned short* index_5 = index_scratch + index_count + 5;
            unsigned short* index_0 = index_scratch + index_count;
            unsigned short* index_4 = index_scratch + index_count + 4;
            unsigned short* index_2 = index_scratch + index_count + 2;
            unsigned short* index_3 = index_scratch + index_count + 3;
            unsigned short* index_1 = index_scratch + index_count + 1;

            do {
                *index_0 = (unsigned short)get_or_append_object_texture_group_vertex(
                    object,
                    ((ObjectFaceQuad*)((char*)object->facequads + face_offset))->vertex_0,
                    ((ObjectFaceQuad*)((char*)object->facequads + face_offset))->uv[0].u,
                    ((ObjectFaceQuad*)((char*)object->facequads + face_offset))->uv[0].v);
                *index_1 = (unsigned short)get_or_append_object_texture_group_vertex(
                    object,
                    ((ObjectFaceQuad*)((char*)object->facequads + face_offset))->vertex_1,
                    ((ObjectFaceQuad*)((char*)object->facequads + face_offset))->uv[1].u,
                    ((ObjectFaceQuad*)((char*)object->facequads + face_offset))->uv[1].v);
                *index_2 = (unsigned short)get_or_append_object_texture_group_vertex(
                    object,
                    ((ObjectFaceQuad*)((char*)object->facequads + face_offset))->vertex_2,
                    ((ObjectFaceQuad*)((char*)object->facequads + face_offset))->uv[2].u,
                    ((ObjectFaceQuad*)((char*)object->facequads + face_offset))->uv[2].v);

                if ((((ObjectFaceQuad*)((char*)object->facequads + face_offset))->flags
                        & 0x80) == 0) {
                    *index_3 = *index_0;
                    *index_4 = *index_2;
                    *index_5 = (unsigned short)get_or_append_object_texture_group_vertex(
                        object,
                        ((ObjectFaceQuad*)((char*)object->facequads + face_offset))->vertex_3,
                        ((ObjectFaceQuad*)((char*)object->facequads + face_offset))->uv[3].u,
                        ((ObjectFaceQuad*)((char*)object->facequads + face_offset))->uv[3].v);
                    index_count += 6;
                    index_0 += 6;
                    index_1 += 6;
                    index_2 += 6;
                    index_3 += 6;
                    index_4 += 6;
                    index_5 += 6;
                    primitive_count += 2;
                } else {
                    index_count += 3;
                    index_1 += 3;
                    index_0 += 3;
                    index_3 += 3;
                    index_2 += 3;
                    index_4 += 3;
                    index_5 += 3;
                    primitive_count += 1;
                }

                ++face_index;
                face_offset += sizeof(ObjectFaceQuad);
            } while (face_index < object->texture_group_ends[group]);
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
        *(ObjectUv*)&locked_vertices[i].u =
            *(ObjectUv*)&g_object_grouped_vertex_scratch[i].u;
        *(Vector3*)&locked_vertices[i].x =
            *(Vector3*)&g_object_grouped_vertex_scratch[i].x;
    }

    object->render_buffers->vertex_buffer->vtbl->Unlock(object->render_buffers->vertex_buffer);

    void* locked_indices;
    object->index_buffer->buffer->vtbl->Lock(
        object->index_buffer->buffer, 0, index_count * 2, &locked_indices, 0);
    memcpy(locked_indices, index_scratch, index_count * 2);
    object->index_buffer->buffer->vtbl->Unlock(object->index_buffer->buffer);

    if ((object->flags & 0x4000) != 0) {
        object->toon_index_buffer = g_object_index_buffer_factory.create_index_buffer(index_count);
    }
}
