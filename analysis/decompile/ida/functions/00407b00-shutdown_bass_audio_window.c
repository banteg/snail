/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: shutdown_bass_audio_window @ 0x407b00 */
/* selector: shutdown_bass_audio_window */

// Uninitializes the audio backend, destroys the hidden BASS window, and unregisters the BASS window class; its handle-zeroing store is confined to the fatal destroy-failure path.
int __cdecl shutdown_bass_audio_window()
{
  int result; // eax

  uninitialize_bass_audio_backend((AudioBackend *)g_audio_backend);
  if ( g_bass_window && !((int (__stdcall *)(_DWORD))DestroyWindow)(g_bass_window) )
    abort_startup_with_3d_error();
  result = ((int (__stdcall *)(ObjectFaceQuad *, int))UnregisterClassA)(ClassName, g_mouse_wheel_delta[2]);
  if ( !result )
    abort_startup_with_3d_error();
  return result;
}
