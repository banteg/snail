/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_mouse_authored_scale_from_clip_rect @ 0x44bbb0 */
/* selector: initialize_mouse_authored_scale_from_clip_rect */

// Caches the current clipped screen rectangle and initializes the shared mouse screen-to-authored scaling for the default 640x480 authored coordinate space.
int __cdecl initialize_mouse_authored_scale_from_clip_rect()
{
  ((void (__stdcall *)(MouseScreenRect *))GetClipCursor)(&g_mouse_clip_rect);
  return update_mouse_authored_scale(640.0, 480.0);
}

