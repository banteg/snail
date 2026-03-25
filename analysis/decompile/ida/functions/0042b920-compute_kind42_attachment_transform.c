/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: compute_kind42_attachment_transform @ 0x42b920 */
/* selector: compute_kind42_attachment_transform */

// Computes the nonlinear temporary transform used by attachment kind 42 during projection, live follow, and constructor-side strip generation. Android's cRPath::HalfPipePos is a strong structural match, but the exact Windows public-path naming for this family remains open.
void __stdcall sub_42B920(float a1, float a2, float a3, int a4, float *a5)
{
  float v5; // [esp+0h] [ebp-10h]
  float v6; // [esp+Ch] [ebp-4h]
  float v7; // [esp+18h] [ebp+8h]

  v5 = a1 * a1 - 16.0;
  v6 = square_root(v5);
  *a5 = atan2_positive(4.0, v6) * a2 * 0.25;
  set_matrix_rotation_identity((_DWORD *)a4);
  rotate_matrix_world_z((float *)a4, *a5);
  v7 = a1 - a3;
  *(float *)(a4 + 48) = sine(*a5) * v7;
  *(float *)(a4 + 52) = a1 - cosine(*a5) * v7;
  *a5 = -*a5;
}

