/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninitialize_input_devices @ 0x411d80 */
/* selector: uninitialize_input_devices */

// Shuts down the live DirectInput stack by releasing the enumerated controllers, keyboard input, mouse device, and shared DirectInput interface handles.
int uninitialize_input_devices()
{
  release_global_direct3d_renderer_resources();
  release_input_controllers();
  release_keyboard_input();
  return release_mouse_input();
}
