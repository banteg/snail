// add_track_cache_vertex @ 0x433830 (thiscall, ret 0x2c)

#include "object_render_types.h"
#include "segment_cache.h"

int report_errorf(const char* format, ...);

int SegmentCache::add_track_cache_vertex(
    Object* source,
    Vector3* position,
    int source_index,
    float u,
    float v,
    ObjectRenderVertex* vertices,
    int* vertex_count,
    int max_vertices,
    int unused_max_indices,
    unsigned int color,
    unsigned char project_uv)
{
    Vector3 transformed;
    float transformed_x = source->vertices[source_index].x;
    transformed_x += position->x;
    transformed.x = transformed_x;
    transformed.y = source->vertices[source_index].y + position->y;
    transformed.z = source->vertices[source_index].z + position->z;

    if (project_uv) {
        u = (transformed.x + 4.0f) * 0.125f;
        v = (transformed.z - build_cache_row_base) * 0.125f;
    }

    int i = 0;
    while (i < *vertex_count) {
        ObjectRenderVertex* vertex = &vertices[i];
        if (vertex->x == transformed.x
            && vertex->y == transformed.y
            && vertex->z == transformed.z
            && vertex->u == u
            && vertex->v == 1.0f - v) {
            return i;
        }
        ++i;
    }

    float flipped_v = 1.0f - v;
    ObjectRenderVertex* vertex = &vertices[i];
    vertex->x = transformed.x;
    vertex->y = transformed.y;
    vertex->z = transformed.z;
    float* vertex_uv = &vertex->u;
    *vertex_uv++ = u;
    *vertex_uv = flipped_v;
    vertex->diffuse = color;

    ++*vertex_count;
    if (*vertex_count > max_vertices)
        report_errorf("Vertex Cache overflow increase RSEGMENTCACHE_VERTEX_MAX");

    return *vertex_count - 1;
}
