// calc_object_edges @ 0x4308b0 (thiscall)

#include "object_render_types.h"

extern "C" void* memcpy(void* destination, const void* source, unsigned int count);

void* get_archive_data_base();

void Object::calc_object_edges()
{
    if ((flags & 1) == 0) {
        return;
    }

    ObjectFaceQuad* face = facequads;
    ObjectToonEdge* build_edges = (ObjectToonEdge*)get_archive_data_base();
    g_object_edge_build_edges = build_edges;
    g_object_edge_build_count = 0;

    int face_index = 0;
    if (facequad_count > 0) {
        int normal_index = 0;
        do {
            add_object_edge(face->vertex_0, face->vertex_1, normal_index);
            add_object_edge(face->vertex_2, face->vertex_0, normal_index);
            add_object_edge(face->vertex_1, face->vertex_2, normal_index);

            if ((face->flags & 0x80) == 0) {
                add_object_edge(face->vertex_0, face->vertex_2, normal_index + 1);
                add_object_edge(face->vertex_3, face->vertex_0, normal_index + 1);
                add_object_edge(face->vertex_2, face->vertex_3, normal_index + 1);
            }

            ++face_index;
            normal_index += 2;
            ++face;
        } while (face_index < facequad_count);
    }

    int edge_count = g_object_edge_build_count;
    ObjectToonEdge* scratch_edges = g_object_edge_build_edges;
    if ((flags & 0x8000) != 0) {
        int index = 0;
        int edge_offset = 0;
        if (edge_count > 0) {
            do {
                ObjectToonEdge* edge = (ObjectToonEdge*)((char*)scratch_edges + edge_offset);
                if ((edge->flags & 1) != 0) {
                    int shift_index = index;
                    if (index < edge_count - 1) {
                        int shift_offset = edge_offset;
                        do {
                            ++shift_index;
                            memcpy((char*)scratch_edges + shift_offset,
                                (char*)scratch_edges + shift_offset + sizeof(ObjectToonEdge),
                                sizeof(ObjectToonEdge));
                            edge_count = g_object_edge_build_count;
                            scratch_edges = g_object_edge_build_edges;
                            shift_offset += sizeof(ObjectToonEdge);
                        } while (shift_index < g_object_edge_build_count - 1);
                    }
                    --edge_count;
                    --index;
                    g_object_edge_build_count = edge_count;
                    edge_offset -= sizeof(ObjectToonEdge);
                }
                ++index;
                edge_offset += sizeof(ObjectToonEdge);
            } while (index < edge_count);
        }
    }

    request_object_edges(edge_count);
    memcpy(edges, g_object_edge_build_edges,
        sizeof(ObjectToonEdge) * g_object_edge_build_count);
}
