/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_jetpack_gauge @ 0x43a930 */

0043a932        gauge->progress = 0
0043a93a        struct Game* edx_1 = data_4df904 + 0x74618
0043a940        gauge->progress_step = 0.00166666671f
0043a947        gauge->game = edx_1
0043a953        struct Player* edx_3 = data_4df904 + 0x42fd7c
0043a959        gauge->state = 0
0043a95c        gauge->player = edx_3
0043a95f        gauge->wobble_alpha = 0f
0043a962        gauge->wobble_y = 0f
0043a965        gauge->wobble_x = 0f
0043a968        gauge->warning_intensity_latch = 0f
0043a96e        return 0
