/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: compute_kind42_attachment_transform @ 0x42b920 */
/* selector: compute_kind42_attachment_transform */

// Computes the nonlinear temporary transform used by attachment kind 42 during projection, live follow, and constructor-side strip generation. Android's cRPath::HalfPipePos is a strong structural match, but the exact Windows public-path naming for this family remains open.
int32_t __stdcall compute_kind42_attachment_transform(
        float arg1,
        float arg2,
        float arg3,
        PathTemplateTransform *transform,
        float *out_angle)
{
  int32_t result; // eax
  float v6; // [esp+0h] [ebp-10h]
  float v7; // [esp+Ch] [ebp-4h]
  float arg2a; // [esp+18h] [ebp+8h]

  v6 = arg1 * arg1 - 16.0;
  v7 = square_root(v6);
  *out_angle = atan2_positive(4.0, v7) * arg2 * 0.25;
  set_matrix_rotation_identity(transform);
  rotate_matrix_world_z(transform, *out_angle);
  arg2a = arg1 - arg3;
  transform->position.x = sine(*out_angle) * arg2a;
  transform->position.y = arg1 - cosine(*out_angle) * arg2a;
  *out_angle = -*out_angle;
  return result;
}

