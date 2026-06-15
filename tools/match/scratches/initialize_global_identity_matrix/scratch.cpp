// initialize_global_identity_matrix @ 0x44c880 (cdecl)

#include "transform_matrix.h"

extern TransformMatrix g_identity_matrix; // 0x77ff40

TransformMatrix* initialize_global_identity_matrix()
{
    return g_identity_matrix.initialize_uniform_scale_matrix(1.0f);
}
