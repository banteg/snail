/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_tracked_allocation_size @ 0x431ab0 */

00431ab1        int32_t esi = *arg1
00431ab3        int32_t eax = 0
00431ab8        if (esi s> 0)
00431abe        int32_t* edx_1 = &arg1[3]
00431ac3        if (*edx_1 == arg2)
00431aea        return arg1[eax * 3 + 4]
00431ac5        eax += 1
00431ac6        edx_1 = &edx_1[3]
00431acb        do while (eax s< esi)
00431ad2        report_errorf("Cannot find Memory Size")
00431ade        return 0
