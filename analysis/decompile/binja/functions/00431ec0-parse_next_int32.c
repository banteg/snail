/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: parse_next_int32 @ 0x431ec0 */

00431ecb        if (**cursor == 0x20)
00431ed7        char* esi_2
00431ecf        esi_2 = &(*cursor)[1]
00431ed2        *cursor = esi_2
00431ed7        do while (*esi_2 == 0x20)
00431ed9        char* eax_2 = *cursor
00431ede        int32_t edi
00431ede        if (*eax_2 != 0x2d)
00431ee8        edi = 1
00431ee0        edi = 0xffffffff
00431ee4        *cursor = &eax_2[1]
00431eef        int32_t eax_4 = 0
00431ef4        if (**cursor s>= 0x30)
00431f11        char* esi_3
00431ef6        esi_3 = *cursor
00431ef8        char* edx
00431ef8        edx.b = *esi_3
00431efd        if (edx.b s> 0x39)
00431efd        break
00431f05        eax_4 = sx.d(edx.b) + eax_4 * 0xa - 0x30
00431f0c        *cursor = &esi_3[1]
00431f11        do while (esi_3[1] s>= 0x30)
00431f18        return eax_4 * edi
