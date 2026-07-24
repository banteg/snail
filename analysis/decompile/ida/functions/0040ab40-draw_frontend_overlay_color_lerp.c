/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_frontend_overlay_color_lerp @ 0x40ab40 */
/* selector: draw_frontend_overlay_color_lerp */

// Exact void Windows cRFlash::AI() projection: moves each current tColour channel 14.5% toward its target and draws the player-owned full-screen overlay while alpha exceeds 0.01. Android preserves the same 0x24-byte owner and body.
void __thiscall draw_frontend_overlay_color_lerp(FrontendOverlayColorLerp *overlay)
{
  double v1; // st7

  overlay->current.r = (overlay->target.r - overlay->current.r) * 0.145 + overlay->current.r;
  overlay->current.g = (overlay->target.g - overlay->current.g) * 0.145 + overlay->current.g;
  overlay->current.b = (overlay->target.b - overlay->current.b) * 0.145 + overlay->current.b;
  v1 = (overlay->target.a - overlay->current.a) * 0.145 + overlay->current.a;
  overlay->current.a = v1;
  if ( v1 > 0.0099999998 )
    queue_axis_aligned_textured_quad(2, 0.0, 0.0, 640.0, 480.0, overlay->state & 0xFF000000, &overlay->current, 5);
}
