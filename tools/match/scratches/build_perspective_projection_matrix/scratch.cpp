// build_perspective_projection_matrix @ 0x450314 (stdcall)

extern "C" double __cdecl cos(double value);
extern "C" double __cdecl sin(double value);

float* __stdcall build_perspective_projection_matrix(
    float* matrix,
    float vertical_fov_radians,
    float aspect_ratio,
    float near_z,
    float far_z)
{
    float* cosine_out = &vertical_fov_radians;
    float sine;
    float* sine_out = &sine;
    float half_fov = vertical_fov_radians * 0.5f;
    *cosine_out = (float)cos(half_fov);
    *sine_out = (float)sin(half_fov);
    float y_scale = vertical_fov_radians / sine;
    float z_scale = far_z / (near_z - far_z);

    matrix[11] = -1.0f;
    matrix[0] = y_scale / aspect_ratio;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;
    matrix[4] = 0.0f;
    matrix[5] = y_scale;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;
    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = z_scale;
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = z_scale * near_z;
    matrix[15] = 0.0f;

    return matrix;
}
