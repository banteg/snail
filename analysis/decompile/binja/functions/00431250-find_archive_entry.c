/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: find_archive_entry @ 0x431250 */

00431250        int32_t ecx
00431250        int32_t var_4 = ecx
00431255        int32_t* edi = data_53c7f8
0043125d        if (edi != 0)
0043125f        int32_t eax_1 = *edi
00431261        int32_t ebx_1 = 0
00431265        var_4 = eax_1
00431269        if (eax_1 s> 0)
0043126f        int32_t* edi_1 = &edi[1]
00431272        char* edx_1 = *edi_1
00431274        char* esi_1 = arg1
00431276        ecx.b = *edx_1
0043127a        if (ecx.b != 0)
0043127c        eax_1.b = *esi_1
00431280        if (eax_1.b == 0)
00431280        break
00431288        if (eax_1.b s>= 0x61 && eax_1.b s<= 0x7a)
0043128a        eax_1.b -= 0x20
0043128e        if (ecx.b != eax_1.b)
0043128e        break
00431290        ecx.b = edx_1[1]
00431293        esi_1 = &esi_1[1]
00431294        edx_1 = &edx_1[1]
00431297        do while (ecx.b != 0)
00431299        eax_1 = var_4
004312a5        if (*edx_1 == 0 && *esi_1 == 0)
004312c9        return data_53c7f8 + ebx_1 * 0xc + 4
004312a7        ebx_1 += 1
004312a8        edi_1 = &edi_1[3]
004312ad        do while (ebx_1 s< eax_1)
004312b6        return 0
