/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: allocate_fringe_object @ 0x4470a0 */

004470a0        int32_t edx_1 = *(arg1 + 0x5fb40)
004470ac        if (edx_1 != 0x1b58)
004470c8        *(arg1 + 0x5fb40) = edx_1 + 1
004470d1        return arg1 + edx_1 * 0x38
004470b3        report_errorf("Too many Fringes increase RFRINGEMANAGER_NUMBER")
004470bd        return 0
