/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_camera_view_matrix @ 0x451ad9 */
/* selector: build_camera_view_matrix */

// DirectX 8 SDK `D3DXMatrixLookAtRH` static-library body built with VC7 build 9178. Retained as a semantic and extent reference for `render_camera`, but excluded from authored gameplay matching totals.
TransformMatrix *__stdcall build_camera_view_matrix(
        TransformMatrix *matrix,
        const Vec3 *eye,
        const Vec3 *target,
        const Vec3 *up)
{
  double v5; // st7
  double v6; // st6
  double v7; // st7
  double v8; // st6
  double v9; // st5
  float v10; // ecx
  double v11; // st4
  double v12; // st3
  float v13; // [esp+Ch] [ebp-24h]
  float v14; // [esp+10h] [ebp-20h]
  float v15; // [esp+14h] [ebp-1Ch]
  float v16; // [esp+18h] [ebp-18h] BYREF
  float v17; // [esp+1Ch] [ebp-14h]
  float v18; // [esp+20h] [ebp-10h]
  float v19; // [esp+24h] [ebp-Ch] BYREF
  float v20; // [esp+28h] [ebp-8h]
  float v21; // [esp+2Ch] [ebp-4h]

  v19 = eye->x - target->x;
  v20 = eye->y - target->y;
  v21 = eye->z - target->z;
  D3DXVec3Normalize(&v19, &v19);
  v13 = v21 * up->y - v20 * up->z;
  v14 = v19 * up->z - v21 * up->x;
  v15 = v20 * up->x - v19 * up->y;
  v16 = v13;
  v17 = v14;
  v18 = v15;
  D3DXVec3Normalize(&v16, &v16);
  v5 = v20 * v18;
  matrix->basis_up.x = v17;
  v6 = v21 * v17;
  matrix->basis_forward.x = v18;
  v7 = v5 - v6;
  v8 = v21 * v16 - v19 * v18;
  v9 = v19 * v17 - v20 * v16;
  matrix->basis_right.x = v16;
  matrix->position.x = -(v16 * eye->x + v17 * eye->y + v18 * eye->z);
  matrix->basis_right.y = v7;
  v10 = v19;
  matrix->basis_up.y = v8;
  matrix->basis_forward.y = v9;
  v11 = v7 * eye->x + v8 * eye->y;
  v12 = v9 * eye->z;
  matrix->basis_right.z = v10;
  matrix->basis_up.z = v20;
  matrix->basis_forward.z = v21;
  matrix->position.y = -(v11 + v12);
  matrix->position.z = -(v19 * eye->x + v20 * eye->y + v21 * eye->z);
  matrix->basis_right_w = 0.0;
  matrix->basis_up_w = 0.0;
  matrix->basis_forward_w = 0.0;
  matrix->position_w = 1.0;
  return matrix;
}
