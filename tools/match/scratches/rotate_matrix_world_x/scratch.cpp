// rotate_matrix_world_x @ 0x44ce30 (thiscall)

#include "transform_matrix.h"

float cosine(float angle);
float sine(float angle);

void TransformMatrix::rotate_matrix_world_x(float angle)
{
    float cos_angle = cosine(angle);
    float sin_angle = sine(angle);

    float new_up_x = sin_angle * basis_forward.x + cos_angle * basis_up.x;
    basis_forward.x = cos_angle * basis_forward.x - sin_angle * basis_up.x;
    basis_up.x = new_up_x;

    float new_up_y = sin_angle * basis_forward.y + cos_angle * basis_up.y;
    basis_forward.y = cos_angle * basis_forward.y - sin_angle * basis_up.y;
    basis_up.y = new_up_y;

    float new_forward_z = cos_angle * basis_forward.z - sin_angle * basis_up.z;
    float new_up_z = sin_angle * basis_forward.z + cos_angle * basis_up.z;
    basis_forward.z = new_forward_z;
    basis_up.z = new_up_z;
}
