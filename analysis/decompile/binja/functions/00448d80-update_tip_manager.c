/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_tip_manager @ 0x448d80 */

00448d82        struct TipSlot (* slot)[0x3] = &manager->slots
00448d85        int32_t i_1 = 3
00448d9a        int32_t i
00448d8d        if ((slot - 0x38)->slots[0].active == 1)
00448d91        update_tip(slot)
00448d96        slot = &(*slot)[1]
00448d99        i = i_1
00448d99        i_1 -= 1
00448d9a        do while (i != 1)
00448d9e        return
