/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_perspective_projection_matrix @ 0x450314 */
/* selector: build_perspective_projection_matrix */

// DirectX 8 SDK `D3DXMatrixPerspectiveFovRH` static-library body built with VC7 build 9178. Retained as a semantic and extent reference for `render_camera` and toon-outline callsites, but excluded from authored gameplay matching totals.
TransformMatrix *__stdcall build_perspective_projection_matrix(
        TransformMatrix *matrix,
        float vertical_fov_radians,
        float aspect_ratio,
        float near_z,
        float far_z)
{
  double v6; // st7
  double v7; // st7
  float v8; // [esp+8h] [ebp-8h]
  float v9; // [esp+Ch] [ebp-4h]
  float vertical_fov_radiansa; // [esp+1Ch] [ebp+Ch]

  v8 = vertical_fov_radians * 0.5;
  vertical_fov_radiansa = cos(v8);
  v9 = sin(v8);
  v6 = vertical_fov_radiansa / v9;
  matrix->basis_forward_w = -1.0;
  matrix->basis_right.x = v6 / aspect_ratio;
  matrix->basis_right.y = 0.0;
  matrix->basis_right.z = 0.0;
  matrix->basis_right_w = 0.0;
  matrix->basis_up.x = 0.0;
  matrix->basis_up.y = v6;
  matrix->basis_up.z = 0.0;
  matrix->basis_up_w = 0.0;
  matrix->basis_forward.x = 0.0;
  matrix->basis_forward.y = 0.0;
  v7 = far_z / (near_z - far_z);
  matrix->basis_forward.z = v7;
  matrix->position.x = 0.0;
  matrix->position.y = 0.0;
  matrix->position.z = v7 * near_z;
  matrix->position_w = 0.0;
  return matrix;
}
