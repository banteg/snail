/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: exit_high_score_screen @ 0x417b50 */

00417b50        void* result = data_4df904
00417b68        if (*(result + 0x74658) == 0)
00417b6a        *(result + 0x1b8) = 2
00417b75        *(data_4df904 + 0x12e55e0) = 2
00417b80        *(data_4df904 + 0x30c) = 1
00417b86        result = data_4df904
00417b94        if (*(result + 0x74658) == 1)
00417b96        *(result + 0x1b8) = 0xa
00417ba0        result = data_4df904
00417ba5        *(result + 0x12e55e0) = 2
00417bb1        *(data_4df904 + 0x30c) = 1
00417bb7        return result
