// AddEdge @ 0x4305a0 (thiscall)

#include "object_render_types.h"

extern "C" void* memcpy(void* destination, const void* source, unsigned int count);

void cRObject::AddEdge(int vertex_a, int vertex_b, int normal_index)
{
    Vector3 direction;
    if (facequad_normals[normal_index].Magnitude() < 0.89999998f) {
        return;
    }

    int build_count = g_object_edge_build_count;
    int index = 0;
    bool found_edge = false;
    if (build_count > 0) {
        Vector3* vertex_b_position = &vertices[vertex_b];
        int* edge_vertex_b = &g_object_edge_build_edges[0].vertex_b;
        do {
            Vector3* edge_a_position = &vertices[edge_vertex_b[-1]];
            if (edge_a_position->x == vertex_b_position->x
                && edge_a_position->y == vertex_b_position->y
                && edge_a_position->z == vertex_b_position->z) {
                Vector3* edge_b_position = &vertices[*edge_vertex_b];
                Vector3* vertex_a_position = &vertices[vertex_a];
                if (edge_b_position->x == vertex_a_position->x
                    && edge_b_position->y == vertex_a_position->y
                    && edge_b_position->z == vertex_a_position->z) {
                    found_edge = true;
                    break;
                }
            }

            ++index;
            edge_vertex_b += sizeof(ObjectToonEdge) / sizeof(int);
        } while (index < build_count);
    }

    if (found_edge == 0) {
        g_object_edge_build_edges[g_object_edge_build_count].flags =
            OBJECT_TOON_EDGE_FLAG_BOUNDARY;
        g_object_edge_build_edges[g_object_edge_build_count].vertex_a = vertex_a;
        g_object_edge_build_edges[g_object_edge_build_count].vertex_b = vertex_b;
        g_object_edge_build_edges[g_object_edge_build_count].normal_a = normal_index;
        g_object_edge_build_edges[g_object_edge_build_count].normal_b = 0;

        Vector3* start = &vertices[vertex_a];
        Vector3* end = &vertices[vertex_b];
        Vector3 edge_delta;
        edge_delta.x = end->x - start->x;
        edge_delta.y = end->y - start->y;
        edge_delta.z = end->z - start->z;
        direction = edge_delta;
        g_object_edge_build_edges[g_object_edge_build_count].length =
            direction.Normalize();
        g_object_edge_build_edges[g_object_edge_build_count].direction = direction;
        ++g_object_edge_build_count;
        return;
    }

    if ((g_object_edge_build_edges[index].flags
            & OBJECT_TOON_EDGE_FLAG_BOUNDARY) != 0) {
        g_object_edge_build_edges[index].flags &=
            ~OBJECT_TOON_EDGE_FLAG_BOUNDARY;
        g_object_edge_build_edges[index].flags |= OBJECT_TOON_EDGE_FLAG_SHARED;
        g_object_edge_build_edges[index].normal_b = normal_index;

        if ((flags & OBJECT_FLAG_DYNAMIC_VERTICES) == 0) {
            Vector3 lhs = facequad_normals[g_object_edge_build_edges[index].normal_a];
            Vector3 rhs = facequad_normals[g_object_edge_build_edges[index].normal_b];
            Vector3 cross;
            cross.Cross(lhs, rhs);
            float cross_length = cross.Magnitude();
            if (cross_length <= 0.050000001f
                || cross.Dot(g_object_edge_build_edges[index].direction)
                    > 0.0020000001f) {
                for (; index < g_object_edge_build_count - 1; ++index) {
                    g_object_edge_build_edges[index] =
                        g_object_edge_build_edges[index + 1];
                }
                --g_object_edge_build_count;
            }
        }
    }
}
