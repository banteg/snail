// add_object_edge @ 0x4305a0 (thiscall)

#include "object_render_types.h"

extern "C" void* memcpy(void* destination, const void* source, unsigned int count);

void Object::add_object_edge(int vertex_a, int vertex_b, int normal_index)
{
    if (facequad_normals[normal_index].vector_magnitude() < 0.89999998f) {
        return;
    }

    int build_count = g_object_edge_build_count;
    int index = 0;
    ObjectToonEdge* found_edge = 0;
    if (build_count > 0) {
        ObjectToonEdge* edge = g_object_edge_build_edges;
        Vector3* vertex_b_position = &vertices[vertex_b];
        do {
            Vector3* edge_a_position = &vertices[edge->vertex_a];
            if (edge_a_position->x == vertex_b_position->x
                && edge_a_position->y == vertex_b_position->y
                && edge_a_position->z == vertex_b_position->z) {
                Vector3* edge_b_position = &vertices[edge->vertex_b];
                Vector3* vertex_a_position = &vertices[vertex_a];
                if (edge_b_position->x == vertex_a_position->x
                    && edge_b_position->y == vertex_a_position->y
                    && edge_b_position->z == vertex_a_position->z) {
                    found_edge = edge;
                    break;
                }
            }

            ++index;
            ++edge;
        } while (index < build_count);
    }

    if (found_edge != 0) {
        ObjectToonEdge* edge = found_edge;
        if ((edge->flags & 1) != 0) {
            edge->flags &= ~1u;
            edge->flags |= 2u;
            edge->normal_b = normal_index;

            if ((flags & 4) == 0) {
                Vector3 lhs = facequad_normals[edge->normal_a];
                Vector3 rhs = facequad_normals[edge->normal_b];
                Vector3 cross;
                cross.cross_vectors(&lhs, &rhs);
                float cross_length = cross.vector_magnitude();
                if (cross_length <= 0.050000001f
                    || cross.dot_vector(&edge->direction) > 0.0020000001f) {
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
        return;
    }

    ObjectToonEdge* edge = &g_object_edge_build_edges[g_object_edge_build_count];
    edge->flags = 1;
    edge->vertex_a = (unsigned short)vertex_a;
    edge->vertex_b = (unsigned short)vertex_b;
    edge->normal_a = normal_index;
    edge->normal_b = 0;

    Vector3* start = &vertices[vertex_a];
    Vector3* end = &vertices[vertex_b];
    Vector3 direction;
    direction.x = end->x - start->x;
    direction.y = end->y - start->y;
    direction.z = end->z - start->z;
    edge->direction = direction;
    edge->length = edge->direction.normalize_vector();
    ++g_object_edge_build_count;
}
