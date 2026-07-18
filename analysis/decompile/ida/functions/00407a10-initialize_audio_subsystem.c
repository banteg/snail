/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_audio_subsystem @ 0x407a10 */
/* selector: initialize_audio_subsystem */

char initialize_audio_subsystem()
{
  void *v0; // eax
  _DWORD WndClass[10]; // [esp+4h] [ebp-28h] BYREF

  WndClass[0] = 0;
  WndClass[1] = bass_audio_window_proc;
  WndClass[2] = 0;
  WndClass[3] = 0;
  WndClass[4] = g_application_instance;
  memset(&WndClass[5], 0, 16);
  WndClass[9] = ClassName;
  if ( !(unsigned __int16)((int (__stdcall *)(_DWORD *))RegisterClassA)(WndClass) )
    abort_startup_with_3d_error();
  v0 = (void *)((int (__stdcall *)(_DWORD, ObjectFaceQuad *, ObjectFaceQuad *, int, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, void *, _DWORD))CreateWindowExA)(
                 0,
                 ClassName,
                 g_blank_text,
                 -2046820352,
                 0,
                 0,
                 0,
                 0,
                 0,
                 0,
                 g_application_instance,
                 0);
  g_bass_window = v0;
  if ( !v0 )
  {
    shutdown_bass_audio_window();
    abort_startup_with_3d_error();
  }
  if ( !initialize_bass_audio_backend(&g_audio_backend, v0) )
    abort_startup_with_3d_error();
  set_global_sample_volume_config(&g_audio_backend, g_runtime_config.sample_volume);
  set_global_stream_volume_config(&g_audio_backend, g_runtime_config.stream_volume);
  return 1;
}
