/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: allocate_tracked_memory @ 0x431b60 */

00431b6b        char* eax = sub_48b72d(arg1 + 8)
00431b77        if (eax == 0)
00431b7e        report_errorf("Not enough memory\n\n")
00431b8a        int32_t* var_10_1 = arg1 + 8
00431b92        push_tracked_allocation(&data_5108c0, arg2, eax)
00431bab        __builtin_memset(__builtin_memset(eax, 0, (arg1 + 8) & 0xfffffffc), 0, (arg1 + 8) & 3)
00431bb1        *eax = 0xde
00431bb4        eax[1] = 0xad
00431bb7        eax[2] = 0xba
00431bba        eax[3] = 0xbe
00431bbd        *(eax + arg1 + 8 - 4) = 0xde
00431bc2        *(eax + arg1 + 8 - 3) = 0xad
00431bc6        *(eax + arg1 + 8 - 2) = 0xba
00431bca        *(eax + arg1 + 8 - 1) = 0xbe
00431bd6        data_5108b4 += arg1 + 8
00431be0        return &eax[4]
