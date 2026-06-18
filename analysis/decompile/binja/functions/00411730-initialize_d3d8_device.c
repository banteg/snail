/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_d3d8_device @ 0x411730 */

0041173c        int32_t eax = Direct3DCreate8(0xdc)
00411743        *(arg1 + 0xbb90) = eax
0041174b        if (eax == 0)
0041174d        abort_startup_with_3d_error()
00411752        *(arg1 + 0xbb8c) = 0
00411758        int32_t* eax_1 = *(arg1 + 0xbb90)
0041176c        void var_10
0041176c        if ((*(*eax_1 + 0x20))(eax_1, 0, &var_10) s< 0)
0041176e        int32_t result = abort_startup_with_3d_error()
00411773        *(arg1 + 0xbb8c) = 0
0041177e        return result
00411796        int32_t var_4
00411796        *(arg1 + 0xbca0) = var_4
0041179c        __builtin_memset(arg1 + 0xbb98, 0, 0x34)
0041179e        int32_t ecx_1 = *(arg1 + 0xbcb8)
004117a9        *(arg1 + 0xbbb4) = 1
004117af        *(arg1 + 0xbbac) = 4
004117b9        *(arg1 + 0xbbb8) = 1
004117bf        *(arg1 + 0xbbbc) = ecx_1
004117c5        int32_t main_window_1 = g_main_window
004117cb        *(arg1 + 0xbba0) = var_4
004117d1        *(arg1 + 0xbbb0) = main_window_1
004117dd        int32_t edx_1 = *(arg1 + 0xbcbc)
004117e3        *(arg1 + 0xbb98) = *(arg1 + 0xbca4)
004117e6        int32_t ecx_3 = *(arg1 + 0xbca8)
004117ec        *(arg1 + 0xbba8) = edx_1
004117f2        *(arg1 + 0xbb9c) = ecx_3
004117fe        *(arg1 + 0xbbc4) = 0
00411804        if (arg2 == 0)
0041180e        *(arg1 + 0xbbc8) = 0
00411806        *(arg1 + 0xbbc8) = 1
00411814        int32_t* eax_3 = *(arg1 + 0xbb90)
00411820        *(arg1 + 0xbcac) = 0x40
00411840        if ((*(*eax_3 + 0x3c))(eax_3, 0, 1, g_main_window, 0x40, arg1 + 0xbb98, arg1 + 0xbb94) s>= 0)
0041187e        char* var_24_4 = "Using Hardware Vertex Processing\n"
00411842        int32_t* eax_5 = *(arg1 + 0xbb90)
00411848        *(arg1 + 0xbcac) = 0x20
00411868        if ((*(*eax_5 + 0x3c))(eax_5, 0, 1, g_main_window, 0x20, arg1 + 0xbb98, arg1 + 0xbb94) s>= 0)
00411877        char* var_24_3 = "Using Software Vertex Processing\n"
0041186a        abort_startup_with_3d_error()
0041186f        *(arg1 + 0xbb8c) = 0
0041188d        reset_direct3d_render_state(arg1)
00411894        query_direct3d_device_caps(arg1)
0041189a        *(arg1 + 0xbb8c) = 1
004118a7        return 0
