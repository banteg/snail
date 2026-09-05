// CalcEdges @ 0x4308b0 (thiscall)

#include "object_render_types.h"

extern "C" void* memcpy(void* destination, const void* source, unsigned int count);

void* get_archive_data_base();

void cRObject::CalcEdges()
{
    if ((flags & OBJECT_FLAG_BUILD_TOON_EDGES) == 0) {
        return;
    }

    cRFaceQuad* face = facequads;
    g_object_edge_build_edges = (ObjectToonEdge*)get_archive_data_base();
    g_object_edge_build_count = 0;

    int face_index = 0;
    if (facequad_count > 0) {
        int normal_index = 0;
        do {
            AddEdge(face->vertex_0, face->vertex_1, normal_index);
            AddEdge(face->vertex_2, face->vertex_0, normal_index);
            AddEdge(face->vertex_1, face->vertex_2, normal_index);

            if ((face->flags & OBJECT_FACEQUAD_FLAG_TRIANGLE) == 0) {
                AddEdge(face->vertex_0, face->vertex_2, normal_index + 1);
                AddEdge(face->vertex_3, face->vertex_0, normal_index + 1);
                AddEdge(face->vertex_2, face->vertex_3, normal_index + 1);
            }

            ++face;
            ++face_index;
            normal_index += 2;
        } while (face_index < facequad_count);
    }

    if ((flags & 0x8000) != 0) {
        int index = 0;
        if (g_object_edge_build_count > 0) {
            do {
                if ((g_object_edge_build_edges[index].flags
                        & OBJECT_TOON_EDGE_FLAG_BOUNDARY) != 0) {
                    int shift_index = index;
                    if (index < g_object_edge_build_count - 1) {
                        do {
                            g_object_edge_build_edges[shift_index] =
                                g_object_edge_build_edges[shift_index + 1];
                            ++shift_index;
                        } while (shift_index < g_object_edge_build_count - 1);
                    }
                    --g_object_edge_build_count;
                    --index;
                }
                ++index;
            } while (index < g_object_edge_build_count);
        }
    }

    RequestEdges(g_object_edge_build_count);
    memcpy(edges, g_object_edge_build_edges,
        sizeof(ObjectToonEdge) * g_object_edge_build_count);
}
