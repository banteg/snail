/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: prepare_music_stream_reload_if_path_changed @ 0x4497e0 */

004497e6        if (*arg1 != 0)
004497fc        if (sub_44e6c0(arg2, &data_7516a0) != 0)
004497fe        int32_t eax_2
004497fe        eax_2.b = 0
00449801        return eax_2
00449806        stop_music_stream(arg1)
0044980b        int32_t eax
0044980b        eax.b = 1
0044980e        return eax
