/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_registered_sound_sample_from_bytes @ 0x449960 */

00449978        int32_t result = data_7537cc(1, arg1, 0, arg2, arg4, 0x20010)
00449984        *((arg3 << 2) + &data_7537e0) = result
0044998b        if (result == 0)
00449992        result = sub_449c00()
00449998        return result
