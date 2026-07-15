/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: hide_star_field @ 0x434670 */

00434675        if (manager->state == 0)
00434675        return
0043467a        int32_t i = 0
0043467e        if (manager->count s<= 0)
0043467e        return
00434682        int32_t esi_1 = 0
00434687        esi_1 += 0x2c
0043468a        void* eax_2 = *(manager->entries + esi_1 - 0x10)
00434694        i += 1
00434695        *(eax_2 + 4) &= 0xffffffbf
0043469d        do while (i s< manager->count)
004346a1        return
