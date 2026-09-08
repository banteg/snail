// initialize_quaternion_from_matrix @ 0x44d5d0 (thiscall, ret 0x4)
// Builds a quaternion from the rotational basis rows of a transform matrix.

#include "quaternion.h"
#include "rdebug.h"
#include "transform_matrix.h"

float Sqrt(float value);

tQuaternian::tQuaternian(const tMatrix& matrix)
{
    float trace = matrix.basis_up.y + matrix.basis_right.x + matrix.basis_forward.z + 1.0f;
    if (trace > 0.000001f) {
        float scale = 0.5f / Sqrt(trace);
        w = 0.25f / scale;
        x = (matrix.basis_up.z - matrix.basis_forward.y) * scale;
        y = (matrix.basis_forward.x - matrix.basis_right.z) * scale;
        z = (matrix.basis_right.y - matrix.basis_up.x) * scale;
        return;
    }

    if (matrix.basis_right.x < matrix.basis_up.y) {
        goto right_less_than_up;
    }
    if (matrix.basis_right.x > matrix.basis_forward.z) {
        goto x_dominant;
    }
    if (matrix.basis_up.y > matrix.basis_forward.z) {
        goto y_dominant;
    }

z_dominant:
    {
        float radicand = matrix.basis_forward.z + 1.0f - matrix.basis_right.x - matrix.basis_up.y;
        if (radicand < 0.0f) {
            debug_report_stub("ERROR:sqt %f\n", radicand);
            radicand = 0.0f;
        }

        float doubled_root = Sqrt(radicand);
        doubled_root = doubled_root + doubled_root;
        x = (matrix.basis_forward.x + matrix.basis_right.z) / doubled_root;
        y = (matrix.basis_forward.y + matrix.basis_up.z) / doubled_root;
        z = doubled_root * 0.25f;
        w = (matrix.basis_up.x + matrix.basis_right.y) / doubled_root;
        return;
    }

right_less_than_up:
    if (matrix.basis_up.y >= matrix.basis_forward.z) {
        goto y_dominant;
    }
    if (matrix.basis_right.x <= matrix.basis_forward.z) {
        goto z_dominant;
    }

x_dominant:
    {
        float radicand = matrix.basis_right.x + 1.0f - matrix.basis_up.y - matrix.basis_forward.z;
        if (radicand < 0.0f) {
            debug_report_stub("ERROR:sqrt %f\n", radicand);
            radicand = 0.0f;
        }

        float doubled_root = Sqrt(radicand);
        doubled_root = doubled_root + doubled_root;
        x = doubled_root * 0.25f;
        y = (matrix.basis_up.x + matrix.basis_right.y) / doubled_root;
        z = (matrix.basis_forward.x + matrix.basis_right.z) / doubled_root;
        w = (matrix.basis_forward.y + matrix.basis_up.z) / doubled_root;
        return;
    }

y_dominant:
    {
        float radicand = matrix.basis_up.y + 1.0f - matrix.basis_right.x - matrix.basis_forward.z;
        if (radicand < 0.0f) {
            debug_report_stub("ERROR:sqt %f\n", radicand);
            radicand = 0.0f;
        }

        float doubled_root = Sqrt(radicand);
        doubled_root = doubled_root + doubled_root;
        x = (matrix.basis_up.x + matrix.basis_right.y) / doubled_root;
        y = doubled_root * 0.25f;
        z = (matrix.basis_forward.y + matrix.basis_up.z) / doubled_root;
        w = (matrix.basis_forward.x + matrix.basis_right.z) / doubled_root;
        return;
    }
}
