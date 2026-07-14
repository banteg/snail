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
            Vector3* base_a = &vertices[
                ((ObjectFaceQuad*)((char*)facequads + face_offset))->vertex_0];
            Vector3* base_b = &vertices[
                ((ObjectFaceQuad*)((char*)facequads + face_offset))->vertex_1];
            Vector3 lhs_value;
            lhs_value.x = base_b->x - base_a->x;
            lhs_value.y = base_b->y - base_a->y;
            lhs_value.z = base_b->z - base_a->z;
            Vector3 lhs = lhs_value;

            base_a = &vertices[
                ((ObjectFaceQuad*)((char*)facequads + face_offset))->vertex_0];
            Vector3* base_c = &vertices[
                ((ObjectFaceQuad*)((char*)facequads + face_offset))->vertex_2];
            Vector3 rhs_value;
            rhs_value.x = base_c->x - base_a->x;
            rhs_value.y = base_c->y - base_a->y;
            rhs_value.z = base_c->z - base_a->z;
            Vector3 rhs = rhs_value;

            Vector3 normal_a;
            normal_a.cross_vectors(&lhs, &rhs);
            normal_a.normalize_vector();

            *(Vector3*)((char*)facequad_normals + normal_offset) = normal_a;

            if ((((ObjectFaceQuad*)((char*)facequads + face_offset))->flags
                    & OBJECT_FACEQUAD_FLAG_TRIANGLE) == 0) {
                base_a = &vertices[
                    ((ObjectFaceQuad*)((char*)facequads + face_offset))->vertex_0];
                Vector3* base_d = &vertices[
                    ((ObjectFaceQuad*)((char*)facequads + face_offset))->vertex_3];
                Vector3 quad_rhs_value;
                quad_rhs_value.x = base_d->x - base_a->x;
                quad_rhs_value.y = base_d->y - base_a->y;
                quad_rhs_value.z = base_d->z - base_a->z;
                rhs = quad_rhs_value;

                Vector3 normal_b;
                normal_b.cross_vectors(&lhs, &rhs);
                normal_b.normalize_vector();

                *(Vector3*)((char*)facequad_normals + normal_offset + sizeof(Vector3)) =
                    normal_b;
            }

            result = index + 1;
            face_offset += sizeof(ObjectFaceQuad);
            normal_offset += sizeof(Vector3) * 2;
            ++index;
        } while (index < facequad_count);
    }

    return result;
}
