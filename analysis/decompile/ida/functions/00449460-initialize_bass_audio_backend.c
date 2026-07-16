/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_bass_audio_backend @ 0x449460 */
/* selector: initialize_bass_audio_backend */

// Extracts Bass.dll from game data into tBass.dll, loads the BASS 2.0 exports dynamically, and initializes the audio backend.
char __thiscall initialize_bass_audio_backend(_BYTE *this, int a2)
{
  void *v3; // esi
  int ElementCount; // [esp+Ch] [ebp-4h] BYREF

  g_cached_music_path[0] = 0;
  *(this + 24) = 0;
  v3 = load_file_bytes(aBassDll, &ElementCount);
  write_file_bytes((char *)LibFileName, v3, ElementCount);
  free_tracked_memory(v3);
  g_bass_module = ((int (__stdcall *)(ObjectFaceQuad *))LoadLibraryA)(LibFileName);
  g_bass_init = (int (__stdcall *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                                                             g_bass_module,
                                                                             ProcName);
  g_bass_set_config = (int (__stdcall *)(_DWORD, _DWORD))((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                                           g_bass_module,
                                                           aBassSetconfig);
  g_bass_free = (BassFreeFn)((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(g_bass_module, aBassFree);
  g_bass_update = ((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(g_bass_module, aBassUpdate);
  g_bass_stream_create_file = (int (__stdcall *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                                                                           g_bass_module,
                                                                                           aBassStreamcrea);
  g_bass_channel_play = (BassChannelPlayFn)((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                             g_bass_module,
                                             aBassStreamplay);
  g_bass_stream_prebuf = ((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(g_bass_module, aBassStreampreb);
  g_bass_channel_stop = (int (__stdcall *)(_DWORD))((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                                     g_bass_module,
                                                     aBassChannelsto);
  g_bass_stream_free = (int (__stdcall *)(_DWORD))((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                                    g_bass_module,
                                                    aBassStreamfree);
  g_bass_sample_load = (BassSampleLoadFn)((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                           g_bass_module,
                                           aBassSampleload);
  g_bass_sample_play_ex = (BassSamplePlayExFn)((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                                g_bass_module,
                                                aBassSampleplay);
  g_bass_sample_stop = (int (__stdcall *)(_DWORD))((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                                    g_bass_module,
                                                    aBassSamplestop);
  g_bass_set_config = (int (__stdcall *)(_DWORD, _DWORD))((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                                           g_bass_module,
                                                           aBassSetconfig);
  g_bass_stop = (int (*)(void))((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(g_bass_module, aBassStop);
  g_bass_start = (int (*)(void))((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(g_bass_module, aBassStart);
  g_bass_pause = (int (*)(void))((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(g_bass_module, aBassPause);
  g_bass_channel_bytes2_seconds = ((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                    g_bass_module,
                                    aBassChannelbyt);
  g_bass_channel_get_level = ((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                               g_bass_module,
                               aBassChannelget);
  g_bass_channel_get_data = ((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                              g_bass_module,
                              aBassChannelget_0);
  g_bass_channel_set_sync = ((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                              g_bass_module,
                              aBassChannelset);
  g_bass_channel_get_position = ((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                  g_bass_module,
                                  aBassChannelget_1);
  g_bass_error_get_code = ((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(g_bass_module, aBassErrorgetco);
  g_bass_channel_remove_sync = (int (__stdcall *)(_DWORD, _DWORD))((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                                                    g_bass_module,
                                                                    aBassChannelrem);
  g_bass_sample_is_active = (int (__stdcall *)(_DWORD))((int (__stdcall *)(_DWORD, ObjectFaceQuad *))GetProcAddress)(
                                                         g_bass_module,
                                                         aBassChannelisa);
  *((_DWORD *)this + 1) = 0;
  *((_DWORD *)this + 2) = 1028443341;
  *this = 0;
  if ( g_bass_init(1, 44100, 0, a2, 0) )
  {
    g_bass_set_config(1, 50);
    g_active_music_stream = 0;
    g_active_music_stream_sync = 0;
    return 1;
  }
  else
  {
    report_errorf(aCanTInitialize);
    return 0;
  }
}
