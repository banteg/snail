/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_bass_audio_backend @ 0x449460 */
/* selector: initialize_bass_audio_backend */

// Extracts Bass.dll from game data into tBass.dll, loads the BASS 2.0 exports dynamically, and initializes the audio backend.
char __thiscall initialize_bass_audio_backend(AudioBackend *backend, void *hwnd)
{
  void *v3; // esi
  int ElementCount; // [esp+Ch] [ebp-4h] BYREF

  g_cached_music_path[0] = 0;
  backend->is_paused = 0;
  v3 = load_file_bytes(aBassDll, &ElementCount);
  write_file_bytes((char *)LibFileName, v3, ElementCount);
  free_tracked_memory(v3);
  g_bass_module = LoadLibraryA((const char *)LibFileName);
  g_bass_init = (BassInitFn)GetProcAddress(g_bass_module, (const char *)ProcName);
  g_bass_set_config = (BassSetConfigFn)GetProcAddress(g_bass_module, (const char *)aBassSetconfig);
  g_bass_free = (BassFreeFn)GetProcAddress(g_bass_module, (const char *)aBassFree);
  g_bass_update = (BassUpdateFn)GetProcAddress(g_bass_module, (const char *)aBassUpdate);
  g_bass_stream_create_file = (BassStreamCreateFileFn)GetProcAddress(g_bass_module, (const char *)aBassStreamcrea);
  g_bass_stream_play = (BassStreamPlayFn)GetProcAddress(g_bass_module, (const char *)aBassStreamplay);
  g_bass_stream_prebuf = (BassStreamPreBufFn)GetProcAddress(g_bass_module, (const char *)aBassStreampreb);
  g_bass_channel_stop = (BassChannelStopFn)GetProcAddress(g_bass_module, (const char *)aBassChannelsto);
  g_bass_stream_free = (BassStreamFreeFn)GetProcAddress(g_bass_module, (const char *)aBassStreamfree);
  g_bass_sample_load = (BassSampleLoadFn)GetProcAddress(g_bass_module, (const char *)aBassSampleload);
  g_bass_sample_play_ex = (BassSamplePlayExFn)GetProcAddress(g_bass_module, (const char *)aBassSampleplay);
  g_bass_sample_stop = (BassSampleStopFn)GetProcAddress(g_bass_module, (const char *)aBassSamplestop);
  g_bass_set_config = (BassSetConfigFn)GetProcAddress(g_bass_module, (const char *)aBassSetconfig);
  g_bass_stop = (BassStopFn)GetProcAddress(g_bass_module, (const char *)aBassStop);
  g_bass_start = (BassStartFn)GetProcAddress(g_bass_module, (const char *)aBassStart);
  g_bass_pause = (BassPauseFn)GetProcAddress(g_bass_module, (const char *)aBassPause);
  g_bass_channel_bytes2_seconds = (BassChannelBytes2SecondsFn)GetProcAddress(
                                                                g_bass_module,
                                                                (const char *)aBassChannelbyt);
  g_bass_channel_get_level = (BassChannelGetLevelFn)GetProcAddress(g_bass_module, (const char *)aBassChannelget);
  g_bass_channel_get_data = (BassChannelGetDataFn)GetProcAddress(g_bass_module, (const char *)aBassChannelget_0);
  g_bass_channel_set_sync = (BassChannelSetSyncFn)GetProcAddress(g_bass_module, (const char *)aBassChannelset);
  g_bass_channel_get_position = (BassChannelGetPositionFn)GetProcAddress(g_bass_module, (const char *)aBassChannelget_1);
  g_bass_error_get_code = (BassErrorGetCodeFn)GetProcAddress(g_bass_module, (const char *)aBassErrorgetco);
  g_bass_channel_remove_sync = (BassChannelRemoveSyncFn)GetProcAddress(g_bass_module, (const char *)aBassChannelrem);
  g_bass_channel_is_active = (BassChannelIsActiveFn)GetProcAddress(g_bass_module, (const char *)aBassChannelisa);
  backend->unknown_04 = 0;
  backend->unknown_08 = 0.050000001;
  backend->music_stream_active = 0;
  if ( g_bass_init(1u, 0xAC44u, 0, hwnd, nullptr) )
  {
    g_bass_set_config(1u, 0x32u);
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
