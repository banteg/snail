// rotate_matrix_world_y @ 0x44cec0 (thiscall)

#include "vector_types.h"

float cosine(float angle);
float sine(float angle);

struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;

    void rotate_matrix_world_y(float angle);
};

void TransformMatrix::rotate_matrix_world_y(float angle)
{
    float cos_angle = cosine(angle);
    float sin_angle = sine(angle);

    float new_forward_x = sin_angle * basis_right.x + cos_angle * basis_forward.x;
    basis_right.x = cos_angle * basis_right.x - sin_angle * basis_forward.x;
    basis_forward.x = new_forward_x;

    float new_forward_y = sin_angle * basis_right.y + cos_angle * basis_forward.y;
    basis_right.y = cos_angle * basis_right.y - sin_angle * basis_forward.y;
    basis_forward.y = new_forward_y;

    float new_right_z = cos_angle * basis_right.z - sin_angle * basis_forward.z;
    float new_forward_z = sin_angle * basis_right.z + cos_angle * basis_forward.z;
    basis_right.z = new_right_z;
    basis_forward.z = new_forward_z;
}
