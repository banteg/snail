/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_overlay @ 0x40a1b0 */
/* selector: update_overlay */

// Exact void Windows `cROverlay::AI()`: wraps the owned camera rotation, rebuilds the parent local-Z transform, copies it into the embedded camera, and refreshes the inverse view. Android and iOS preserve the same owner and operation.
void __thiscall update_overlay(FrameOverlay *overlay)
{
  double v2; // st7
  unsigned __int8 v4; // c0
  unsigned __int8 v5; // c3
  FrameTransformMatrix *p_transform; // ebp

  v2 = overlay->rotation_step + overlay->camera.overlay_rotation_angle;
  overlay->camera.overlay_rotation_angle = v2;
  if ( (v4 | v5) != 0 )
  {
    if ( v2 < 0.0 )
      overlay->camera.overlay_rotation_angle = v2 + 6.2831855;
  }
  else
  {
    overlay->camera.overlay_rotation_angle = v2 - 6.2831855;
  }
  p_transform = &overlay->bod.transform;
  set_matrix_identity((TransformMatrix *)&overlay->bod.transform);
  rotate_matrix_local_z((TransformMatrix *)&overlay->bod.transform, overlay->camera.overlay_rotation_angle);
  qmemcpy(&overlay->camera.body.transform, p_transform, sizeof(overlay->camera.body.transform));
  invert_matrix_from_source(
    (TransformMatrix *)&overlay->camera.view_matrix,
    (const TransformMatrix *)&overlay->bod.transform);
}
