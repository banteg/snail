/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_bass_audio_backend @ 0x449460 */

00449460        uint32_t var_4 = arg1
00449468        char* edi = arg1
0044946d        data_7516a0 = 0
00449478        edi[0x18] = 0
0044947b        char* eax = load_file_bytes("Bass.dll", &var_4)
0044948d        write_file_bytes("tBass.dll", eax, var_4)
00449493        free_tracked_memory(eax)
004494a0        HMODULE hModule = LoadLibraryA("tBass.dll")
004494b2        data_753c90 = hModule
004494b7        int32_t eax_1 = GetProcAddress(hModule, "BASS_Init")
004494b9        HMODULE hModule_8 = data_753c90
004494c5        data_753c08 = eax_1
004494cc        data_753c1c = GetProcAddress(hModule_8, "BASS_SetConfig")
004494dc        int32_t eax_4 = GetProcAddress(data_753c90, "BASS_Free")
004494de        HMODULE hModule_1 = data_753c90
004494ea        data_7537d8 = eax_4
004494ef        int32_t eax_5 = GetProcAddress(hModule_1, "BASS_Update")
004494f1        HMODULE hModule_9 = data_753c90
004494fd        data_751698 = eax_5
00449504        data_753bf8 = GetProcAddress(hModule_9, "BASS_StreamCreateFile")
00449514        int32_t eax_8 = GetProcAddress(data_753c90, "BASS_StreamPlay")
00449516        HMODULE hModule_2 = data_753c90
00449522        data_7517a0 = eax_8
00449527        int32_t eax_9 = GetProcAddress(hModule_2, "BASS_StreamPreBuf")
00449529        HMODULE hModule_10 = data_753c90
00449535        data_751670 = eax_9
0044953c        data_753be4 = GetProcAddress(hModule_10, "BASS_ChannelStop")
0044954c        int32_t eax_12 = GetProcAddress(data_753c90, "BASS_StreamFree")
0044954e        HMODULE hModule_3 = data_753c90
0044955a        data_753cb0 = eax_12
0044955f        int32_t eax_13 = GetProcAddress(hModule_3, "BASS_SampleLoad")
00449561        HMODULE hModule_11 = data_753c90
0044956d        data_7537cc = eax_13
00449574        data_7527b4 = GetProcAddress(hModule_11, "BASS_SamplePlayEx")
00449584        int32_t eax_16 = GetProcAddress(data_753c90, "BASS_SampleStop")
00449586        HMODULE hModule_4 = data_753c90
00449592        data_753c94 = eax_16
00449597        int32_t eax_17 = GetProcAddress(hModule_4, "BASS_SetConfig")
00449599        HMODULE hModule_12 = data_753c90
004495a5        data_753c1c = eax_17
004495ac        data_753bfc = GetProcAddress(hModule_12, "BASS_Stop")
004495bc        int32_t eax_20 = GetProcAddress(data_753c90, "BASS_Start")
004495be        HMODULE hModule_5 = data_753c90
004495ca        data_751660 = eax_20
004495cf        int32_t eax_21 = GetProcAddress(hModule_5, "BASS_Pause")
004495d1        HMODULE hModule_13 = data_753c90
004495dd        data_753cc0 = eax_21
004495e4        data_75162c = GetProcAddress(hModule_13, "BASS_ChannelBytes2Seconds")
004495f4        int32_t eax_24 = GetProcAddress(data_753c90, "BASS_ChannelGetLevel")
004495f6        HMODULE hModule_6 = data_753c90
00449602        data_753cbc = eax_24
00449607        int32_t eax_25 = GetProcAddress(hModule_6, "BASS_ChannelGetData")
00449609        HMODULE hModule_14 = data_753c90
00449615        data_753c18 = eax_25
0044961c        data_753cc4 = GetProcAddress(hModule_14, "BASS_ChannelSetSync")
0044962c        int32_t eax_28 = GetProcAddress(data_753c90, "BASS_ChannelGetPosition")
0044962e        HMODULE hModule_7 = data_753c90
0044963a        data_753c98 = eax_28
0044963f        int32_t eax_29 = GetProcAddress(hModule_7, "BASS_ErrorGetCode")
00449641        HMODULE hModule_15 = data_753c90
0044964d        data_751674 = eax_29
00449654        data_75165c = GetProcAddress(hModule_15, "BASS_ChannelRemoveSync")
00449672        data_753ca8 = GetProcAddress(data_753c90, "BASS_ChannelIsActive")
00449679        *(edi + 4) = 0
0044967c        *(edi + 8) = 0x3d4ccccd
00449683        *edi = 0
0044968d        if (data_753c08(1, 0xac44, 0, arg2, 0) == 0)
00449694        report_errorf("Can't initialize digital sound system")
0044969c        int32_t eax_34
0044969c        eax_34.b = 0
004496a2        return 0
004496a9        data_753c1c(1, 0x32)
004496b0        data_753c20 = 0
004496b6        data_751680 = 0
004496bd        int32_t result
004496bd        result.b = 1
004496c1        return result
