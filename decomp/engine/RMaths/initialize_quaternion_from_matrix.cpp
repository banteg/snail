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

    int axis;
    if (matrix.basis_right.x >= matrix.basis_up.y) {
        if (matrix.basis_right.x > matrix.basis_forward.z) {
            axis = 0;
        } else if (matrix.basis_up.y > matrix.basis_forward.z) {
            axis = 1;
        } else {
            axis = 2;
        }
    } else {
        if (matrix.basis_up.y >= matrix.basis_forward.z) {
            axis = 1;
        } else if (matrix.basis_right.x > matrix.basis_forward.z) {
            axis = 0;
        } else {
            axis = 2;
        }
    }

    if (axis == 0) {
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
    } else if (axis == 1) {
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
    } else if (axis == 2) {
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
}
