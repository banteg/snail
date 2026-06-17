/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: replace_object_group_texture_refs @ 0x4145c0 */

004145cb        if ((*(arg1 + 0x10) & 0x80000) == 0)
004145cb        return 
004145d0        int32_t i = 0
004145d4        if (*(arg1 + 0x64) s<= 0)
004145d4        return 
004145e1        int32_t eax_1 = *(arg1 + 0xd0)
004145ef        if (*(eax_1 + (i << 2)) == arg3)
004145f1        *(eax_1 + (i << 2)) = arg2
004145f6        i += 1
004145f9        do while (i s< *(arg1 + 0x64))
004145fe        return
