// apply_bod_position @ 0x42f680 (thiscall, ret 0x4)

#include "bod_types.h"

struct Vec3 {
    float x;
    float y;
    float z;

    Vec3* multiply_vector_by_matrix_copy(Vec3* out, TransformMatrix* matrix);
};

struct ObjectGeometry {
    char unknown_00[0x2c];
    int vertex_count; // +0x2c
    char unknown_30[0x38 - 0x30];
    Vec3* vertices; // +0x38
};

ObjectGeometry* BodBase::apply_bod_position(TransformMatrix* matrix)
{
    int index = 0;
    ObjectGeometry* result = (ObjectGeometry*)object;
    if (result->vertex_count > 0) {
        int offset = 0;
        do {
            Vec3 transformed;
            Vec3* copied =
                ((Vec3*)((char*)result->vertices + offset))
                    ->multiply_vector_by_matrix_copy(&transformed, matrix);
            ObjectGeometry* destination_object = (ObjectGeometry*)object;
            Vec3* destination = (Vec3*)((char*)destination_object->vertices + offset);
            ++index;
            offset += sizeof(Vec3);
            destination->x = copied->x;
            destination->y = copied->y;
            destination->z = copied->z;
            result = (ObjectGeometry*)object;
        } while (index < result->vertex_count);
    }
    return result;
}
