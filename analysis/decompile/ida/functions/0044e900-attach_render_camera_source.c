/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: attach_render_camera_source @ 0x44e900 */
/* selector: attach_render_camera_source */

// Attaches a source render object to one runtime camera/render slot and marks the slot active through flag bit 0.
int32_t __thiscall attach_render_camera_source(Viewport *viewport, FrameRenderCamera *camera)
{
  int32_t result; // eax

  viewport->camera = camera;
  result = viewport->flags;
  LOBYTE(result) = result | 1;
  viewport->flags = result;
  return result;
}
