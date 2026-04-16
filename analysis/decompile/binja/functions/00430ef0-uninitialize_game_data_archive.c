/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninitialize_game_data_archive @ 0x430ef0 */

00430ef6        free_tracked_memory(data_53c7ec)
00430efb        int32_t result = data_53c7f8
00430f05        if (result != 0)
00430f0e        result = sub_48b3a7(data_53c7f0)
00430f16        data_53c7f8 = 0
00430f20        return result
