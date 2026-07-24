/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_frontend_overlay_color_lerp @ 0x40ab00 */
/* selector: initialize_frontend_overlay_color_lerp */

// Exact void Windows projection of Android cRFlash::Init(int): stores the render-scene mask and seeds the owned target/current tColour pair to white with zero alpha inside player zero at GameRoot +0x2a8.
void __thiscall initialize_frontend_overlay_color_lerp(FrontendOverlayColorLerp *overlay, int32_t state)
{
  overlay->state = state;
  store_color4f(&overlay->target, 1.0, 1.0, 1.0, 0.0);
  store_color4f(&overlay->current, 1.0, 1.0, 1.0, 0.0);
}
