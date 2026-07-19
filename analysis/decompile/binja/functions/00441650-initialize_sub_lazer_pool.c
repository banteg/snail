/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_sub_lazer_pool @ 0x441650 */

00441650        enum SubLazerState* eax = &manager->slots[0].state
00441656        int32_t i_1 = 0x14
00441667        int32_t i
0044165b        (eax - 0x80)->slots[0].state = SUB_LAZER_STATE_INACTIVE
00441661        eax = &eax[0x2c]
00441666        i = i_1
00441666        i_1 -= 1
00441667        do while (i != 1)
00441669        return
