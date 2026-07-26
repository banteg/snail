/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: border_add_text_number @ 0x401030 */

00401030        uint32_t eax
00401030        eax.b = border->text_buffer.raw[0]
00401036        struct FrontendWidgetTextBuffer* ecx = &border->text_buffer
0040103e        while (eax.b != 0)
00401040        eax.b = ecx->raw[1]
00401043        ecx = &ecx->raw[1]
00401049        int32_t value_1 = value
0040104f        if (value_1 == 0)
00401051        ecx->raw[0] = 0x30
00401054        ecx->raw[1] = value_1.b
00401058        return
0040105b        eax.b = 0
0040105e        int32_t esi = 0x989680
00401063        value.b = 0
0040107c        while (true)
0040107c        if (eax.b != 0 && (esi == 0x64 || esi == 0x186a0))
0040107e        ecx->raw[0] = 0x2c
00401081        ecx = &ecx->raw[1]
00401088        if (value_1 s>= esi || eax.b != 0)
0040108d        if (esi != 1)
00401096        eax = divs.dp.d(sx.q(value_1), esi)
0040109a        if (eax != 0)
004010a9        value.b = 1
004010a9        goto label_4010ae
004010a2        if (value.b != 0)
004010a4        ecx->raw[0] = 0x30
004010b2        ecx = &ecx->raw[1]
0040108f        eax.b = value_1.b
004010ae        label_4010ae:
004010ae        eax.b += 0x30
004010b0        ecx->raw[0] = eax.b
004010b2        ecx = &ecx->raw[1]
004010bd        value_1 = mods.dp.d(sx.q(value_1), esi)
004010bf        int32_t eax_6
004010bf        int32_t edx_5
004010bf        edx_5:eax_6 = muls.dp.d(0x66666667, esi)
004010c1        int32_t edx_6 = edx_5 s>> 2
004010cb        esi s/= 0xa
004010cd        if (edx_6 == neg.d(edx_6 u>> 0x1f))
004010cd        break
00401069        eax.b = value.b
004010d0        ecx->raw[0] = 0
004010d4        return
