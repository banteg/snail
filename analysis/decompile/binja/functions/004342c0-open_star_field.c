/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: open_star_field @ 0x4342c0 */

004342dc        manager->entries = allocate_tracked_memory(star_count * 0x2c, "StarField")
004342df        manager->count = star_count
004342ec        if ((data_4df934 & 4) == 0)
00434301        manager->state = 0
0043430a        return
004342f0        manager->state = 1
004342f7        initialize_star_field(manager)
004342fe        return
