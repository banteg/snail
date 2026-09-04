// CalcFaceQuadNormals @ 0x42fcb0 (thiscall)

#include "object_render_types.h"
#include "vector3.h"

extern "C" void* memset(void* destination, int value, unsigned int count);

void* allocate_tracked_memory(int size, char* name);
void free_tracked_memory(void* pointer);
int report_errorf(char* format, ...);

#define ACCUM_VERTEX_NORMAL(index_value, normal_value) \
    vertex_normals[(index_value)] += (normal_value)

#define ACCUM_NORMAL_TALLY(index_value, weight_value) \
    normal_tally[(index_value)] += (weight_value)

#define CURRENT_FACE \
    ((cRFaceQuad*)((char*)facequads + face_offset))

void cRObject::CalcFaceQuadNormals()
{
    RequestFaceQuadNormals();

    float* normal_tally = (float*)allocate_tracked_memory(vertex_count * 4, "Normal Tally");
    memset(normal_tally, 0, vertex_count * 4);

    int face_offset = 0;
    int index = 0;
    int normal_offset;
    if (facequad_count > 0) {
        normal_offset = 0;
        do {
            Vector3 lhs = vertices[CURRENT_FACE->vertex_1] - vertices[CURRENT_FACE->vertex_0];
            Vector3 rhs = vertices[CURRENT_FACE->vertex_2] - vertices[CURRENT_FACE->vertex_0];

            Vector3 normal_a;
            normal_a.cross_vectors(&lhs, &rhs);
            normal_a.Normalize();

            *(Vector3*)((char*)facequad_normals + normal_offset) = normal_a;

            Vector3 normal_b;
            if ((CURRENT_FACE->flags & OBJECT_FACEQUAD_FLAG_TRIANGLE) == 0) {
                lhs = vertices[CURRENT_FACE->vertex_2] - vertices[CURRENT_FACE->vertex_0];
                rhs = vertices[CURRENT_FACE->vertex_3] - vertices[CURRENT_FACE->vertex_0];

                normal_b.cross_vectors(&lhs, &rhs);
                normal_b.Normalize();

                *(Vector3*)((char*)facequad_normals + normal_offset + sizeof(Vector3)) =
                    normal_b;
            }

            if ((CURRENT_FACE->flags & OBJECT_FACEQUAD_FLAG_TRIANGLE) == 0) {
                ACCUM_VERTEX_NORMAL(CURRENT_FACE->vertex_0, normal_b);
                ACCUM_VERTEX_NORMAL(CURRENT_FACE->vertex_1, normal_b);
                ACCUM_VERTEX_NORMAL(CURRENT_FACE->vertex_2, normal_b);
                ACCUM_VERTEX_NORMAL(CURRENT_FACE->vertex_3, normal_b);
                ACCUM_NORMAL_TALLY(CURRENT_FACE->vertex_0, 1.0f);
                ACCUM_NORMAL_TALLY(CURRENT_FACE->vertex_1, 1.0f);
                ACCUM_NORMAL_TALLY(CURRENT_FACE->vertex_2, 1.0f);
                ACCUM_NORMAL_TALLY(CURRENT_FACE->vertex_3, 1.0f);
            }

            ACCUM_VERTEX_NORMAL(CURRENT_FACE->vertex_0, normal_a);
            ACCUM_VERTEX_NORMAL(CURRENT_FACE->vertex_1, normal_a);
            ACCUM_VERTEX_NORMAL(CURRENT_FACE->vertex_2, normal_a);
            ACCUM_VERTEX_NORMAL(CURRENT_FACE->vertex_3, normal_a);
            ACCUM_NORMAL_TALLY(CURRENT_FACE->vertex_0, 2.0999999f);
            ACCUM_NORMAL_TALLY(CURRENT_FACE->vertex_1, 2.0999999f);
            ACCUM_NORMAL_TALLY(CURRENT_FACE->vertex_2, 2.0999999f);
            ACCUM_NORMAL_TALLY(CURRENT_FACE->vertex_3, 2.0999999f);

            if (CURRENT_FACE->vertex_0 > vertex_count ||
                CURRENT_FACE->vertex_1 > vertex_count ||
                CURRENT_FACE->vertex_2 > vertex_count ||
                CURRENT_FACE->vertex_3 > vertex_count) {
                report_errorf("Invalid Face Vertex Index");
            }

            ++index;
            normal_offset += sizeof(Vector3) * 2;
            face_offset += sizeof(cRFaceQuad);
        } while (index < facequad_count);
    }

    index = 0;
    if (vertex_count > 0) {
        do {
            float tally = normal_tally[index];
            {
                Vector3* normal = &vertex_normals[index];
                normal->x = normal->x / tally;
                normal->y = normal->y / tally;
                normal->z = normal->z / tally;
            }
            vertex_normals[index].Normalize();

            vertex_normals[index] = vertex_normals[index] * -1.0f;
            ++index;
        } while (index < vertex_count);
    }

    free_tracked_memory(normal_tally);
}

#undef CURRENT_FACE
#undef ACCUM_NORMAL_TALLY
#undef ACCUM_VERTEX_NORMAL
