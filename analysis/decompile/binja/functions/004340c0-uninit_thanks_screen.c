/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninit_thanks_screen @ 0x4340c0 */

004340c3        data_4df904
004340d0        int32_t result = kill_border(*(arg1 + 4))
004340db        *(data_4df904 + 0x1b8) = 0xe
004340e5        return result
