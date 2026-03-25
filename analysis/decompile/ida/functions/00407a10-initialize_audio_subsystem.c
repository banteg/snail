/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_audio_subsystem @ 0x407a10 */
/* selector: initialize_audio_subsystem */

char initialize_audio_subsystem()
{
  int v0; // eax
  _DWORD WndClass[10]; // [esp+4h] [ebp-28h] BYREF

  WndClass[0] = 0;
  WndClass[1] = sub_4079E0;
  WndClass[2] = 0;
  WndClass[3] = 0;
  WndClass[4] = MEMORY[0x4DFAD8];
  memset(&WndClass[5], 0, 16);
  WndClass[9] = ClassName;
  if ( !(unsigned __int16)((int (__stdcall *)(_DWORD *))RegisterClassA)(WndClass) )
    abort_startup_with_3d_error();
  v0 = ((int (__stdcall *)(_DWORD, char *, float *, int, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))CreateWindowExA)(
         0,
         ClassName,
         &flt_4DFAFC[3],
         -2046820352,
         0,
         0,
         0,
         0,
         0,
         0,
         MEMORY[0x4DFAD8],
         0);
  MEMORY[0x4DFAF8] = v0;
  if ( !v0 )
  {
    sub_407B00();
    abort_startup_with_3d_error();
  }
  if ( !initialize_bass_audio_backend(unk_753C58, v0) )
    abort_startup_with_3d_error();
  set_global_sample_volume_config(unk_4DF918);
  set_global_stream_volume_config(unk_4DF91C);
  return 1;
}

