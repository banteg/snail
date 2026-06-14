// initialize_global_identity_matrix @ 0x44c880 (cdecl)

#include "vector_types.h"

struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;

    TransformMatrix* initialize_uniform_scale_matrix(float scale);
};

extern TransformMatrix g_identity_matrix; // 0x77ff40

TransformMatrix* initialize_global_identity_matrix()
{
    return g_identity_matrix.initialize_uniform_scale_matrix(1.0f);
}
