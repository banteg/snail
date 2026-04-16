/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_slug_voice @ 0x43f560 */

0043f560        void* result
0043f560        result.b = *(arg1 + 0xd8)
0043f568        if (result.b == 0)
0043f56a        result = data_4df904
0043f577        if (*(result + 0x3d0194) == 0)
0043f581        *(result + 0x3d0198) = *(result + 0x3d019c)
0043f594        *(data_4df904 + 0x3d0194) = 1
0043f59a        *(arg1 + 0xd8) = 1
0043f5aa        *(arg1 + 0xdc) = 0
0043f5b4        return play_voice_backend(arg2, 1f, -1f, 0f)
0043f5bc        return result
