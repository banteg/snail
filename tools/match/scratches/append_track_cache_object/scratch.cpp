// append_track_cache_object @ 0x433960 (thiscall, ret 0x2c)

#include "object_render_types.h"
#include "track_render_cache.h"

int report_errorf(const char* format, ...);

int TrackRenderCacheManager::append_track_cache_object(
    int row_index,
    Object* source,
    Vector3* position,
    ObjectRenderVertex* vertices,
    int* vertex_count,
    unsigned short* indices,
    int* index_count,
    int max_vertices,
    int max_indices,
    unsigned int color,
    unsigned char project_uv)
{
    Vector3 local_position;
    int face_index = 0;

    if (source->facequad_count > 0) {
        do {
            local_position = *position;

            indices[*index_count] = (unsigned short)add_track_cache_vertex(
                source, &local_position, source->facequads[face_index].vertex_0,
                source->facequads[face_index].uv[0].u,
                source->facequads[face_index].uv[0].v,
                vertices, vertex_count, max_vertices, max_indices, color, project_uv);
            indices[*index_count + 1] = (unsigned short)add_track_cache_vertex(
                source, &local_position, source->facequads[face_index].vertex_1,
                source->facequads[face_index].uv[1].u,
                source->facequads[face_index].uv[1].v,
                vertices, vertex_count, max_vertices, max_indices, color, project_uv);
            indices[*index_count + 2] = (unsigned short)add_track_cache_vertex(
                source, &local_position, source->facequads[face_index].vertex_2,
                source->facequads[face_index].uv[2].u,
                source->facequads[face_index].uv[2].v,
                vertices, vertex_count, max_vertices, max_indices, color, project_uv);

            if ((source->facequads[face_index].flags & 0x80) == 0) {
                indices[*index_count + 3] = indices[*index_count];
                indices[*index_count + 4] = indices[*index_count + 2];
                indices[*index_count + 5] = (unsigned short)add_track_cache_vertex(
                    source, &local_position, source->facequads[face_index].vertex_3,
                    source->facequads[face_index].uv[3].u,
                    source->facequads[face_index].uv[3].v,
                    vertices, vertex_count, max_vertices, max_indices, color, project_uv);
                *index_count += 6;
            } else {
                *index_count += 3;
            }

            ++face_index;
        } while (face_index < source->facequad_count);
    }

    int result = *index_count;
    if (result > max_indices)
        return report_errorf("Index Cache overflow increase RSEGMENTCACHE_INDEX_MAX");
    return result;
}
