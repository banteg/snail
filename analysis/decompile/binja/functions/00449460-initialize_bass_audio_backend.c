/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_bass_audio_backend @ 0x449460 */

00449460        int32_t backend_1 = backend
0044946d        g_cached_music_path[0] = 0
00449478        backend->is_paused = 0
0044947b        void* eax = load_file_bytes("Bass.dll", &backend_1)
0044948d        write_file_bytes("tBass.dll", eax, backend_1)
00449493        free_tracked_memory(eax)
004494a0        void* eax_1 = LoadLibraryA("tBass.dll")
004494b2        g_bass_module = eax_1
004494b7        BassInitFn eax_2 = GetProcAddress(eax_1, "BASS_Init")
004494b9        void* bass_module_8 = g_bass_module
004494c5        g_bass_init = eax_2
004494cc        g_bass_set_config = GetProcAddress(bass_module_8, "BASS_SetConfig")
004494dc        BassFreeFn eax_5 = GetProcAddress(g_bass_module, "BASS_Free")
004494de        void* bass_module_1 = g_bass_module
004494ea        g_bass_free = eax_5
004494ef        BassUpdateFn eax_6 = GetProcAddress(bass_module_1, "BASS_Update")
004494f1        void* bass_module_9 = g_bass_module
004494fd        g_bass_update = eax_6
00449504        g_bass_stream_create_file = GetProcAddress(bass_module_9, "BASS_StreamCreateFile")
00449514        BassStreamPlayFn eax_9 = GetProcAddress(g_bass_module, "BASS_StreamPlay")
00449516        void* bass_module_2 = g_bass_module
00449522        g_bass_stream_play = eax_9
00449527        BassStreamPreBufFn eax_10 = GetProcAddress(bass_module_2, "BASS_StreamPreBuf")
00449529        void* bass_module_10 = g_bass_module
00449535        g_bass_stream_prebuf = eax_10
0044953c        g_bass_channel_stop = GetProcAddress(bass_module_10, "BASS_ChannelStop")
0044954c        BassStreamFreeFn eax_13 = GetProcAddress(g_bass_module, "BASS_StreamFree")
0044954e        void* bass_module_3 = g_bass_module
0044955a        g_bass_stream_free = eax_13
0044955f        BassSampleLoadFn eax_14 = GetProcAddress(bass_module_3, "BASS_SampleLoad")
00449561        void* bass_module_11 = g_bass_module
0044956d        g_bass_sample_load = eax_14
00449574        g_bass_sample_play_ex = GetProcAddress(bass_module_11, "BASS_SamplePlayEx")
00449584        BassSampleStopFn eax_17 = GetProcAddress(g_bass_module, "BASS_SampleStop")
00449586        void* bass_module_4 = g_bass_module
00449592        g_bass_sample_stop = eax_17
00449597        BassSetConfigFn eax_18 = GetProcAddress(bass_module_4, "BASS_SetConfig")
00449599        void* bass_module_12 = g_bass_module
004495a5        g_bass_set_config = eax_18
004495ac        g_bass_stop = GetProcAddress(bass_module_12, "BASS_Stop")
004495bc        BassStartFn eax_21 = GetProcAddress(g_bass_module, "BASS_Start")
004495be        void* bass_module_5 = g_bass_module
004495ca        g_bass_start = eax_21
004495cf        BassPauseFn eax_22 = GetProcAddress(bass_module_5, "BASS_Pause")
004495d1        void* bass_module_13 = g_bass_module
004495dd        g_bass_pause = eax_22
004495e4        g_bass_channel_bytes2_seconds = GetProcAddress(bass_module_13, "BASS_ChannelBytes2Seconds")
004495f4        BassChannelGetLevelFn eax_25 = GetProcAddress(g_bass_module, "BASS_ChannelGetLevel")
004495f6        void* bass_module_6 = g_bass_module
00449602        g_bass_channel_get_level = eax_25
00449607        BassChannelGetDataFn eax_26 = GetProcAddress(bass_module_6, "BASS_ChannelGetData")
00449609        void* bass_module_14 = g_bass_module
00449615        g_bass_channel_get_data = eax_26
0044961c        g_bass_channel_set_sync = GetProcAddress(bass_module_14, "BASS_ChannelSetSync")
0044962c        BassChannelGetPositionFn eax_29 = GetProcAddress(g_bass_module, "BASS_ChannelGetPosition")
0044962e        void* bass_module_7 = g_bass_module
0044963a        g_bass_channel_get_position = eax_29
0044963f        BassErrorGetCodeFn eax_30 = GetProcAddress(bass_module_7, "BASS_ErrorGetCode")
00449641        void* bass_module_15 = g_bass_module
0044964d        g_bass_error_get_code = eax_30
00449654        g_bass_channel_remove_sync = GetProcAddress(bass_module_15, "BASS_ChannelRemoveSync")
00449672        g_bass_channel_is_active = GetProcAddress(g_bass_module, "BASS_ChannelIsActive")
00449679        backend->unknown_04 = 0
0044967c        backend->unknown_08 = 0.0500000007f
00449683        backend->music_stream_active = 0
0044968d        if (g_bass_init(1, 0xac44, 0, hwnd, nullptr) == 0)
00449694        report_errorf("Can't initialize digital sound system")
0044969c        int32_t eax_36
0044969c        eax_36.b = 0
004496a2        return 0
004496a9        g_bass_set_config(1, 0x32)
004496b0        g_active_music_stream = 0
004496b6        g_active_music_stream_sync = 0
004496bd        uint32_t eax_38
004496bd        eax_38.b = 1
004496c1        return 1
