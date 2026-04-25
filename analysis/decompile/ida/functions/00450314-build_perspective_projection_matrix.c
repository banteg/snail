/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_perspective_projection_matrix @ 0x450314 */
/* selector: build_perspective_projection_matrix */

// Builds the renderer's D3D-style perspective projection matrix from vertical FOV in radians, viewport aspect ratio, near plane, and far plane. Called by both `render_camera` and toon-outline setup.
int __stdcall sub_450314(int a1, float a2, float a3, float a4, float a5)
{
  double v6; // st7
  double v7; // st7
  float v8; // [esp+8h] [ebp-8h]
  float v9; // [esp+Ch] [ebp-4h]
  float v10; // [esp+1Ch] [ebp+Ch]

  v8 = a2 * 0.5;
  v10 = cos(v8);
  v9 = sin(v8);
  v6 = v10 / v9;
  *(_DWORD *)(a1 + 44) = -1082130432;
  *(float *)a1 = v6 / a3;
  *(float *)(a1 + 4) = 0.0;
  *(float *)(a1 + 8) = 0.0;
  *(float *)(a1 + 12) = 0.0;
  *(float *)(a1 + 16) = 0.0;
  *(float *)(a1 + 20) = v6;
  *(float *)(a1 + 24) = 0.0;
  *(float *)(a1 + 28) = 0.0;
  *(float *)(a1 + 32) = 0.0;
  *(float *)(a1 + 36) = 0.0;
  v7 = a5 / (a4 - a5);
  *(float *)(a1 + 40) = v7;
  *(float *)(a1 + 48) = 0.0;
  *(float *)(a1 + 52) = 0.0;
  *(float *)(a1 + 56) = v7 * a4;
  *(float *)(a1 + 60) = 0.0;
  return a1;
}

