/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_render_camera_slot @ 0x44e920 */
/* selector: initialize_render_camera_slot */

// Initializes one 0x28-byte runtime camera/render slot used by render_game_frame, seeding viewport lanes, draw-world state, and the default 0.8725f lane while leaving owner fields for later setup.
Viewport *__thiscall initialize_render_camera_slot(Viewport *viewport)
{
  viewport->flags = 0;
  viewport->viewport_x = 0.0;
  viewport->viewport_y = 0.0;
  viewport->draw_world = 1;
  viewport->viewport_width = 1.0;
  viewport->viewport_height = 1.0;
  viewport->unknown_1c = 0.87249994;
  return viewport;
}
