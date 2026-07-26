/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_overlay @ 0x40a240 */
/* selector: initialize_overlay */

// Exact void Windows `cROverlay::Init()`: initializes the parent transform, embedded camera, 38-degree FOV, zero rotation, and fixed rotation step. Android preserves the same owner, constants, and lifecycle role.
void __thiscall initialize_overlay(FrameOverlay *overlay)
{
  FrameTransformMatrix *p_transform; // edi

  p_transform = &overlay->bod.transform;
  overlay->camera.render_mask = 0;
  overlay->rotation_step = 0.00036547193;
  set_matrix_identity((TransformMatrix *)&overlay->bod.transform);
  overlay->camera.fov_degrees = 38.0;
  set_matrix_identity((TransformMatrix *)&overlay->camera.body.transform);
  invert_matrix_from_source((TransformMatrix *)&overlay->camera.view_matrix, (const TransformMatrix *)p_transform);
}
