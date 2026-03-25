/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: start_invincible_shell @ 0x444ae0 */

00444ae0        int32_t result = *(arg1 + 0x80)
00444aea        if (result != 0)
00444aef        if (result != 3)
00444b40        return result
00444af1        *(arg1 + 0x80) = 1
00444afb        return result
00444b01        *(arg1 + 0x80) = 1
00444b0b        *(arg1 + 0x84) = 0
00444b11        *(arg1 + 0x88) = 0x3d088889
00444b17        *(arg1 + 0x8c) = 0
00444b1d        *(arg1 + 0x90) = 0x3d088889
00444b23        void* eax = data_4df904
00444b34        *(eax + 0x433f98) |= 0x20
00444b3b        return play_registered_sound_sample_scaled(0x30, 1f)
