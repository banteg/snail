/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: find_case_insensitive_substring @ 0x44e600 */

0044e600        char* eax = searched
0044e604        int32_t ebx
0044e604        int32_t var_4 = ebx
0044e60c        char* result = eax
0044e60e        if (*eax != 0)
0044e610        eax.b = *result
0044e613        char* pattern_1 = pattern
0044e618        char eax_1 = ascii_upper_if_lowercase(eax.b)
0044e622        eax = ascii_upper_if_lowercase(*pattern_1)
0044e62c        if (eax.b == eax_1)
0044e632        char* edi_2 = result - pattern_1
0044e665        char i
0044e634        char eax_2 = *(edi_2 + pattern_1 + 1)
0044e638        pattern_1 = &pattern_1[1]
0044e63b        if (eax_2 == 0)
0044e63d        char ecx = *pattern_1
0044e641        if (ecx != 0)
0044e67a        return 0
0044e64b        if (eax_2 == 0 && ecx == 0)
0044e681        return result
0044e655        i = ascii_upper_if_lowercase(*pattern_1)
0044e65b        eax = ascii_upper_if_lowercase(*(edi_2 + pattern_1))
0044e665        do while (i == eax.b)
0044e66a        if (*pattern_1 == 0)
0044e681        return result
0044e66c        eax.b = result[1]
0044e66f        result = &result[1]
0044e672        do while (eax.b != 0)
0044e67a        return 0
