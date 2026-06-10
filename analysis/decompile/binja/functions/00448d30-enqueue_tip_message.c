/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: enqueue_tip_message @ 0x448d30 */

00448d31        int32_t i = 0
00448d33        struct TipSlot (* edx)[0x3] = &manager->slots
00448d39        if ((edx - 0x38)->slots[0].active == 0)
00448d6a        initialize_tip(&manager->slots[i], definition, show_disable_button)
00448d72        return &manager->slots[i]
00448d3b        i += 1
00448d3c        edx = &(*edx)[1]
00448d42        do while (i s< 3)
00448d49        report_errorf("Run out of Tips")
00448d54        return 0
