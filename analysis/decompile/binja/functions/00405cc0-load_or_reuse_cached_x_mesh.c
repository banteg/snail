/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_or_reuse_cached_x_mesh @ 0x405cc0 */

00405cca        int32_t i = 0
00405cd1        if (*(arg1 + 4) s> 0)
00405cd3        char* ebx_1 = arg1 + 0x44
00405ce2        if (sub_44e6c0(arg2, ebx_1) != 0)
00405d5a        return i
00405ce7        i += 1
00405ce8        ebx_1 = &ebx_1[0xbc]
00405cf0        do while (i s< *(arg1 + 4))
00405d03        sub_44e5b0(arg1 + *(arg1 + 4) * 0xbc + 0x44, arg2)
00405d10        void* eax_4 = add_object_to_list(0x4b7648)
00405d25        set_bod_object(arg1 + *(arg1 + 4) * 0xbc + 8, eax_4)
00405d3c        load_x_mesh(arg2, *(arg1 + i * 0xbc + 0x2c), 1)
00405d45        int32_t eax_8 = *(arg1 + 4) + 1
00405d46        *(arg1 + 4) = eax_8
00405d51        return eax_8 - 1
