/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: unhide_star_field @ 0x4346b0 */

004346b5        if (manager->state == 0)
004346b5        return
004346ba        int32_t i = 0
004346be        if (manager->count s<= 0)
004346be        return
004346c2        int32_t esi_1 = 0
004346c7        esi_1 += 0x2c
004346ca        void* eax_2 = *(manager->entries + esi_1 - 0x10)
004346d4        i += 1
004346d5        *(eax_2 + 4) |= 0x40
004346dd        do while (i s< manager->count)
004346e1        return
