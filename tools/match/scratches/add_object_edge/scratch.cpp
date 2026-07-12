// add_object_edge @ 0x4305a0 (thiscall)

#include "object_render_types.h"

extern "C" void* memcpy(void* destination, const void* source, unsigned int count);

void Object::add_object_edge(int vertex_a, int vertex_b, int normal_index)
{
    Vector3 direction;
    if (facequad_normals[normal_index].vector_magnitude() < 0.89999998f) {
        return;
    }

    int build_count = g_object_edge_build_count;
    int index = 0;
    ObjectToonEdge* found_edge = 0;
    if (build_count > 0) {
        int* edge_vertex_b = &g_object_edge_build_edges[0].vertex_b;
        Vector3* vertex_b_position = &vertices[vertex_b];
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
                    found_edge = (ObjectToonEdge*)(edge_vertex_b - 2);
                    break;
                }
            }

            ++index;
            edge_vertex_b += sizeof(ObjectToonEdge) / sizeof(int);
        } while (index < build_count);
    }

    if (found_edge == 0) {
        g_object_edge_build_edges[g_object_edge_build_count].flags = 1;
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
            direction.normalize_vector();
        g_object_edge_build_edges[g_object_edge_build_count].direction = direction;
        ++g_object_edge_build_count;
        return;
    }

    if ((g_object_edge_build_edges[index].flags & 1) != 0) {
        g_object_edge_build_edges[index].flags &= ~1u;
        g_object_edge_build_edges[index].flags |= 2u;
        g_object_edge_build_edges[index].normal_b = normal_index;

        if ((flags & 4) == 0) {
            Vector3 lhs = facequad_normals[g_object_edge_build_edges[index].normal_a];
            Vector3 rhs = facequad_normals[g_object_edge_build_edges[index].normal_b];
            Vector3 cross;
            cross.cross_vectors(&lhs, &rhs);
            float cross_length = cross.vector_magnitude();
            if (cross_length <= 0.050000001f
                || cross.dot_vector(&g_object_edge_build_edges[index].direction)
                    > 0.0020000001f) {
                int shift_index = index;
                if (index < g_object_edge_build_count - 1) {
                    do {
                        memcpy(&g_object_edge_build_edges[shift_index],
                            &g_object_edge_build_edges[shift_index + 1],
                            sizeof(ObjectToonEdge));
                        ++shift_index;
                    } while (shift_index < g_object_edge_build_count - 1);
                }
                --g_object_edge_build_count;
            }
        }
    }
}
