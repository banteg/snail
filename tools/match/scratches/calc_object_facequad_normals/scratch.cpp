// calc_object_facequad_normals @ 0x42fcb0 (thiscall)

#include "object_render_types.h"
#include "vector3.h"

extern "C" void* memset(void* destination, int value, unsigned int count);

void* allocate_tracked_memory(int size, char* name);
void free_tracked_memory(void* pointer);
int report_errorf(char* format, ...);

#define ACCUM_VERTEX_NORMAL(index_value, normal_value) \
    do { \
        Vector3* normal_slot = &vertex_normals[(index_value)]; \
        normal_slot->x += (normal_value).x; \
        normal_slot->y += (normal_value).y; \
        normal_slot->z += (normal_value).z; \
    } while (0)

#define ACCUM_NORMAL_TALLY(index_value, weight_value) \
    normal_tally[(index_value)] += (weight_value)

#define CURRENT_FACE \
    ((ObjectFaceQuad*)((char*)facequads + face_offset))

void Object::calc_object_facequad_normals()
{
    request_object_facequad_normals();

    float* normal_tally = (float*)allocate_tracked_memory(vertex_count * 4, "Normal Tally");
    memset(normal_tally, 0, vertex_count * 4);

    int face_offset = 0;
    int index = 0;
    int normal_offset;
    if (facequad_count > 0) {
        normal_offset = 0;
        do {
            Vector3* base_a = &vertices[CURRENT_FACE->vertex_0];
            Vector3* base_b = &vertices[CURRENT_FACE->vertex_1];
            Vector3 lhs_value;
            lhs_value.x = base_b->x - base_a->x;
            lhs_value.y = base_b->y - base_a->y;
            lhs_value.z = base_b->z - base_a->z;
            Vector3 lhs = lhs_value;

            base_a = &vertices[CURRENT_FACE->vertex_0];
            Vector3* base_c = &vertices[CURRENT_FACE->vertex_2];
            Vector3 rhs_value;
            rhs_value.x = base_c->x - base_a->x;
            rhs_value.y = base_c->y - base_a->y;
            rhs_value.z = base_c->z - base_a->z;
            Vector3 rhs = rhs_value;

            Vector3 normal_a;
            normal_a.cross_vectors(&lhs, &rhs);
            normal_a.normalize_vector();

            *(Vector3*)((char*)facequad_normals + normal_offset) = normal_a;

            Vector3 normal_b;
            if ((CURRENT_FACE->flags & 0x80) == 0) {
                base_a = &vertices[CURRENT_FACE->vertex_0];
                Vector3* base_d = &vertices[CURRENT_FACE->vertex_2];
                Vector3 quad_lhs_value;
                quad_lhs_value.x = base_d->x - base_a->x;
                quad_lhs_value.y = base_d->y - base_a->y;
                quad_lhs_value.z = base_d->z - base_a->z;
                lhs = quad_lhs_value;

                base_a = &vertices[CURRENT_FACE->vertex_0];
                Vector3* base_e = &vertices[CURRENT_FACE->vertex_3];
                Vector3 quad_rhs_value;
                quad_rhs_value.x = base_e->x - base_a->x;
                quad_rhs_value.y = base_e->y - base_a->y;
                quad_rhs_value.z = base_e->z - base_a->z;
                rhs = quad_rhs_value;

                normal_b.cross_vectors(&lhs, &rhs);
                normal_b.normalize_vector();

                *(Vector3*)((char*)facequad_normals + normal_offset + sizeof(Vector3)) =
                    normal_b;
            }

            if ((CURRENT_FACE->flags & 0x80) == 0) {
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
            face_offset += sizeof(ObjectFaceQuad);
        } while (index < facequad_count);
    }

    int vertex_offset = 0;
    index = 0;
    if (vertex_count > 0) {
        do {
            float tally = normal_tally[index];
            {
                Vector3* normal = (Vector3*)((char*)vertex_normals + vertex_offset);
                normal->x = normal->x / tally;
                normal->y = normal->y / tally;
                normal->z = normal->z / tally;
            }
            ((Vector3*)((char*)vertex_normals + vertex_offset))->normalize_vector();

            Vector3* inverted = (Vector3*)((char*)vertex_normals + vertex_offset);
            vertex_offset += sizeof(Vector3);
            Vector3 inverted_value;
            inverted_value.x = inverted->x * -1.0f;
            inverted_value.y = inverted->y * -1.0f;
            inverted_value.z = inverted->z * -1.0f;
            *inverted = inverted_value;
            ++index;
        } while (index < vertex_count);
    }

    free_tracked_memory(normal_tally);
}

#undef CURRENT_FACE
#undef ACCUM_NORMAL_TALLY
#undef ACCUM_VERTEX_NORMAL
