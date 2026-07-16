/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: game_window_proc @ 0x4074b0 */

004074bd        if (arg2 u<= 0x200)
004074c3        if (arg2 == 0x200)
004075fd        label_4075fd:
004075fd        uint16_t eax_11 = (arg3 u>> 0x10).w
00407603        if (eax_11 s> 0)
00407605        data_4dfad0 = 1
00407615        return 0
00407618        if (eax_11 s< 0)
0040761a        data_4dfad0 = 0xffffffff
0040762a        return 0
004074d2        if (arg2 - 2 u<= 0xfe)
004074d8        int32_t edx_1 = 0
004074da        edx_1.b = *(arg2 + &game_window_proc_low_message_jump_table[5]:2)
004074e0        switch (edx_1)
004074f5        case 0
004074f5        return 0
0040756d        case 1
0040756d        if (arg3 == 1)
00407581        pause_audio_backend_if_running(&g_audio_backend)
00407586        g_window_deactivated = 1
0040758c        restore_desktop_display_mode()
00407597        return 0
0040759e        if (arg3 == 0)
004075a5        resume_audio_backend_if_paused(&g_audio_backend)
004075aa        g_window_deactivated = 0
004075ba        int32_t var_4_1 = 0
004075cd        data_4dfb00 = fconvert.s(float.t(timeGetTime().q) * fconvert.t(0.00100000005f))
004075d3        pdb_internal::Array<struct PortablePDB::MethodInfo>::reset(0x4df9e0)
004075de        return 0
0040750c        case 2
0040750c        uint32_t eax_3 = zx.d(arg3.w)
00407511        if (eax_3 == 0)
00407518        pause_audio_backend_if_running(&g_audio_backend)
0040752a        handle_game_window_deactivate()
00407535        return 0
0040753b        if (eax_3 == 1)
00407542        resume_audio_backend_if_paused(&g_audio_backend)
00407554        handle_game_window_activate()
0040755f        return 0
004074e9        case 3
004074e9        PostQuitMessage(0)
004074f5        return 0
004074fd        case 4
004074fd        if (arg3 != 0x1b)
00407505        return 0
004074e9        PostQuitMessage(0)
004074f5        return 0
004076a9        return DefWindowProcA(arg1, arg2, arg3, arg4)
004075ea        if (arg2 - 0x201 u> 9)
004076a9        return DefWindowProcA(arg1, arg2, arg3, arg4)
004075f0        switch (arg2)
00407634        case 0x201
00407634        data_4b7764 = 1
0040763a        data_4b7234 = 1
00407644        return 0
0040764b        case 0x202
0040764b        data_4b7764 = 0
00407651        data_4b7234 = 0
0040765b        return 0
004076a9        case 0x203, 0x206, 0x207, 0x208, 0x209
004076a9        return DefWindowProcA(arg1, arg2, arg3, arg4)
00407665        case 0x204
00407665        data_4b7230 = 1
0040766b        data_4b7640 = 1
00407675        return 0
0040767c        case 0x205
0040767c        data_4b7230 = 0
00407682        data_4b7640 = 0
0040768c        return 0
004075f0        case 0x20a
004075f0        goto label_4075fd
