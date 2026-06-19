// calc_object_facequad_normals @ 0x42fcb0 (thiscall)

#include "object_render_types.h"
#include "vector3.h"

extern "C" void* memset(void* destination, int value, unsigned int count);

void* allocate_tracked_memory(int size, char* name);
void free_tracked_memory(void* pointer);
int report_errorf(char* format, ...);

#define ACCUM_VERTEX_NORMAL(index_value, normal_value, weight_value) \
    do { \
        Vector3* normal_slot = &vertex_normals[(index_value)]; \
        normal_slot->x += (normal_value).x; \
        normal_slot->y += (normal_value).y; \
        normal_slot->z += (normal_value).z; \
        normal_tally[(index_value)] += (weight_value); \
    } while (0)

void Object::calc_object_facequad_normals()
{
    request_object_facequad_normals();

    float* normal_tally = (float*)allocate_tracked_memory(vertex_count * 4, "Normal Tally");
    memset(normal_tally, 0, vertex_count * 4);

    int face_offset = 0;
    int normal_offset = 0;
    int face_index = 0;
    if (facequad_count > 0) {
        do {
            Vector3* vertex_base = vertices;
            ObjectFaceQuad* face = (ObjectFaceQuad*)((char*)facequads + face_offset);

            Vector3* base_a = &vertex_base[face->vertex_0];
            Vector3* base_b = &vertex_base[face->vertex_1];
            float lhs_x = base_b->x - base_a->x;
            float lhs_y = base_b->y - base_a->y;
            float lhs_z = base_b->z - base_a->z;

            Vector3 lhs;
            lhs.x = lhs_x;
            lhs.y = lhs_y;
            lhs.z = lhs_z;

            base_a = &vertex_base[face->vertex_0];
            Vector3* base_c = &vertex_base[face->vertex_2];
            float rhs_x = base_c->x - base_a->x;
            float rhs_y = base_c->y - base_a->y;
            float rhs_z = base_c->z - base_a->z;

            Vector3 rhs;
            rhs.x = rhs_x;
            rhs.y = rhs_y;
            rhs.z = rhs_z;

            Vector3 normal_a;
            normal_a.cross_vectors(&lhs, &rhs);
            normal_a.normalize_vector();

            Vector3* out = (Vector3*)((char*)facequad_normals + normal_offset);
            out[0] = normal_a;

            if ((face->flags & 0x80) == 0) {
                base_a = &vertex_base[face->vertex_0];
                Vector3* base_d = &vertex_base[face->vertex_2];
                lhs_x = base_d->x - base_a->x;
                lhs_y = base_d->y - base_a->y;
                lhs_z = base_d->z - base_a->z;
                lhs.x = lhs_x;
                lhs.y = lhs_y;
                lhs.z = lhs_z;

                base_a = &vertex_base[face->vertex_0];
                Vector3* base_e = &vertex_base[face->vertex_3];
                rhs_x = base_e->x - base_a->x;
                rhs_y = base_e->y - base_a->y;
                rhs_z = base_e->z - base_a->z;
                rhs.x = rhs_x;
                rhs.y = rhs_y;
                rhs.z = rhs_z;

                Vector3 normal_b;
                normal_b.cross_vectors(&lhs, &rhs);
                normal_b.normalize_vector();

                out[1] = normal_b;

                ACCUM_VERTEX_NORMAL(face->vertex_0, normal_b, 1.0f);
                ACCUM_VERTEX_NORMAL(face->vertex_1, normal_b, 1.0f);
                ACCUM_VERTEX_NORMAL(face->vertex_2, normal_b, 1.0f);
                ACCUM_VERTEX_NORMAL(face->vertex_3, normal_b, 1.0f);
            }

            ACCUM_VERTEX_NORMAL(face->vertex_0, normal_a, 2.0999999f);
            ACCUM_VERTEX_NORMAL(face->vertex_1, normal_a, 2.0999999f);
            ACCUM_VERTEX_NORMAL(face->vertex_2, normal_a, 2.0999999f);
            ACCUM_VERTEX_NORMAL(face->vertex_3, normal_a, 2.0999999f);

            if (face->vertex_0 > vertex_count || face->vertex_1 > vertex_count ||
                face->vertex_2 > vertex_count || face->vertex_3 > vertex_count) {
                report_errorf("Invalid Face Vertex Index");
            }

            face_offset += sizeof(ObjectFaceQuad);
            normal_offset += sizeof(Vector3) * 2;
            ++face_index;
        } while (face_index < facequad_count);
    }

    int vertex_offset = 0;
    int vertex_index = 0;
    if (vertex_count > 0) {
        float* tally_cursor = normal_tally;
        do {
            float tally = *tally_cursor;
            Vector3* normal = (Vector3*)((char*)vertex_normals + vertex_offset);
            normal->x = normal->x / tally;
            normal->y = normal->y / tally;
            normal->z = normal->z / tally;
            normal->normalize_vector();
            ++tally_cursor;

            Vector3* inverted = (Vector3*)((char*)vertex_normals + vertex_offset);
            vertex_offset += sizeof(Vector3);
            inverted->x = inverted->x * -1.0f;
            inverted->y = inverted->y * -1.0f;
            inverted->z = inverted->z * -1.0f;
            ++vertex_index;
        } while (vertex_index < vertex_count);
    }

    free_tracked_memory(normal_tally);
}

#undef ACCUM_VERTEX_NORMAL
