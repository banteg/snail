/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: find_case_insensitive_substring @ 0x44e600 */

0044e604        int32_t ebx
0044e604        int32_t var_4 = ebx
0044e60c        char* result = arg2
0044e60e        if (*arg2 != 0)
0044e672        char* eax
0044e610        eax.b = *result
0044e613        char* esi_1 = arg1
0044e61f        ebx.b = ascii_upper_if_lowercase(eax.b)
0044e62c        if (ascii_upper_if_lowercase(*esi_1).b == ebx.b)
0044e632        char* edi_2 = result - esi_1
0044e634        eax.b = *(edi_2 + esi_1 + 1)
0044e638        esi_1 = &esi_1[1]
0044e63b        if (eax.b == 0)
0044e63d        char ecx = *esi_1
0044e641        if (ecx != 0)
0044e67a        return 0
0044e645        if (eax.b == 0)
0044e647        eax.b = ecx
0044e64b        if (eax.b == 0)
0044e681        return result
0044e655        ebx.b = ascii_upper_if_lowercase(*esi_1)
0044e65b        eax = ascii_upper_if_lowercase(*(edi_2 + esi_1))
0044e665        do while (ebx.b == eax.b)
0044e66a        if (*esi_1 == 0)
0044e681        return result
0044e66c        eax.b = result[1]
0044e66f        result = &result[1]
0044e672        do while (eax.b != 0)
0044e67a        return 0
