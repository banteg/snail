/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: allocate_fringe_object @ 0x4470a0 */

004470a0        int32_t count = manager->count
004470ac        if (count != 0x1b58)
004470c8        manager->count = count + 1
004470d1        return &manager->objects[count]
004470b3        report_errorf("Too many Fringes increase RFRINGEMANAGER_NUMBER")
004470bd        return 0
