/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: compute_kind42_attachment_transform @ 0x42b920 */
/* selector: compute_kind42_attachment_transform */

// Computes the nonlinear temporary transform used by attachment kind 42 during projection, live follow, and constructor-side strip generation. Android's cRPath::HalfPipePos is a strong structural match, but the exact Windows public-path naming for this family remains open.
void __thiscall compute_kind42_attachment_transform(
        PathTemplate *self,
        float radius,
        float x,
        float y,
        TransformMatrix *transform,
        float *out_angle)
{
  float v6; // [esp+0h] [ebp-10h]
  float v7; // [esp+Ch] [ebp-4h]
  float arg2; // [esp+18h] [ebp+8h]

  v6 = radius * radius - 16.0;
  v7 = square_root(v6);
  *out_angle = atan2_positive(4.0, v7) * x * 0.25;
  set_matrix_rotation_identity(transform);
  rotate_matrix_world_z(transform, *out_angle);
  arg2 = radius - y;
  transform->position.x = sine(*out_angle) * arg2;
  transform->position.y = radius - cosine(*out_angle) * arg2;
  *out_angle = -*out_angle;
}

