// apply_bod_position @ 0x42f680 (thiscall, ret 0x4)

#include "bod_types.h"
#include "object_render_types.h"

Object* BodBase::apply_bod_position(TransformMatrix* matrix)
{
    int index = 0;
    Object* result = object;
    if (result->vertex_count > 0) {
        int offset = 0;
        do {
            Vector3 transformed;
            Vector3* copied =
                ((Vector3*)((char*)result->vertices + offset))
                    ->multiply_vector_by_matrix_copy(&transformed, matrix);
            Object* destination_object = object;
            Vector3* destination = (Vector3*)((char*)destination_object->vertices + offset);
            ++index;
            offset += sizeof(Vector3);
            destination->x = copied->x;
            destination->y = copied->y;
            destination->z = copied->z;
            result = object;
        } while (index < result->vertex_count);
    }
    return result;
}
