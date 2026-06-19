// calc_object_facequad_normals_simple @ 0x430230 (thiscall)

#include "object_render_types.h"
#include "vector3.h"

int Object::calc_object_facequad_normals_simple()
{
    request_object_facequad_normals();

    int result = facequad_count;
    int normal_offset = 0;
    int index = 0;
    if (result > 0) {
        int face_offset = 0;
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
                Vector3* base_d = &vertex_base[face->vertex_3];
                rhs_x = base_d->x - base_a->x;
                rhs_y = base_d->y - base_a->y;
                rhs_z = base_d->z - base_a->z;
                rhs.x = rhs_x;
                rhs.y = rhs_y;
                rhs.z = rhs_z;

                Vector3 normal_b;
                normal_b.cross_vectors(&lhs, &rhs);
                normal_b.normalize_vector();

                out[1] = normal_b;
            }

            result = index + 1;
            face_offset += sizeof(ObjectFaceQuad);
            normal_offset += sizeof(Vector3) * 2;
            ++index;
        } while (index < facequad_count);
    }

    return result;
}
