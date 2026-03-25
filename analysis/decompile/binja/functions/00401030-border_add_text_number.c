/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: border_add_text_number @ 0x401030 */

00401030        uint32_t result
00401030        result.b = *(arg1 + 0x2cc)
00401036        char* ecx = arg1 + 0x2cc
0040103e        while (result.b != 0)
00401040        result.b = ecx[1]
00401043        ecx = &ecx[1]
00401049        int32_t ebx = arg2
0040104f        if (ebx == 0)
00401051        *ecx = 0x30
00401054        ecx[1] = ebx.b
00401058        return result
0040105b        result.b = 0
0040105e        int32_t esi = 0x989680
00401063        arg2.b = 0
0040107c        while (true)
0040107c        if (result.b != 0 && (esi == 0x64 || esi == 0x186a0))
0040107e        *ecx = 0x2c
00401081        ecx = &ecx[1]
00401088        if (ebx s>= esi || result.b != 0)
0040108d        if (esi != 1)
00401096        result = divs.dp.d(sx.q(ebx), esi)
0040109a        if (result != 0)
004010a9        arg2.b = 1
004010a9        goto label_4010ae
0040109c        result.b = arg2.b
004010a2        if (result.b != 0)
004010a4        *ecx = 0x30
004010b2        ecx = &ecx[1]
0040108f        result.b = ebx.b
004010ae        label_4010ae:
004010ae        result.b += 0x30
004010b0        *ecx = result.b
004010b2        ecx = &ecx[1]
004010bd        ebx = mods.dp.d(sx.q(ebx), esi)
004010bf        int32_t eax_4
004010bf        int32_t edx_5
004010bf        edx_5:eax_4 = muls.dp.d(0x66666667, esi)
004010c1        int32_t edx_6 = edx_5 s>> 2
004010c6        result = edx_6 u>> 0x1f
004010cb        esi s/= 0xa
004010cd        if (edx_6 == neg.d(result))
004010cd        break
00401069        result.b = arg2.b
004010d0        *ecx = 0
004010d4        return result
