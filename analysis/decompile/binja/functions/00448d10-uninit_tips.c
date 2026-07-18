/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninit_tips @ 0x448d10 */

00448d12        struct Tip* tip = &manager->tips
00448d15        int32_t i_1 = 3
00448d2a        int32_t i
00448d1d        if (tip->active == 1)
00448d21        kill_tip_widgets(tip)
00448d26        tip = &tip[1]
00448d29        i = i_1
00448d29        i_1 -= 1
00448d2a        do while (i != 1)
00448d2e        return
