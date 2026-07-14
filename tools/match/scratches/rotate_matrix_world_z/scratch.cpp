// rotate_matrix_world_z @ 0x44cf50 (thiscall)

#include "transform_matrix.h"

float cosine(float angle);
float sine(float angle);

void TransformMatrix::rotate_matrix_local_z(float angle)
{
    float cos_angle = cosine(angle);
    float sin_angle = sine(angle);

    float new_right_x = cos_angle * basis_right.x + sin_angle * basis_up.x;
    basis_up.x = cos_angle * basis_up.x - sin_angle * basis_right.x;
    basis_right.x = new_right_x;

    float new_right_y = sin_angle * basis_up.y + cos_angle * basis_right.y;
    basis_up.y = cos_angle * basis_up.y - sin_angle * basis_right.y;
    basis_right.y = new_right_y;

    float new_up_z = cos_angle * basis_up.z - sin_angle * basis_right.z;
    float new_right_z = sin_angle * basis_up.z + cos_angle * basis_right.z;
    basis_up.z = new_up_z;
    basis_right.z = new_right_z;
}
