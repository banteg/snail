/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_high_score_screen @ 0x417220 */

00417229        void* ecx_1 = data_4df904 + 0xb4c
0041722f        data_4df9c0 = *(arg1 + 8)
00417234        kill_all_borders(ecx_1)
00417241        *(data_4df904 + 0x30d) = 0
0041724d        *(data_4df904 + 0x310) = 0
00417253        return 0
