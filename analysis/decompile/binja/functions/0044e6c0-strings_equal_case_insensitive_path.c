/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: strings_equal_case_insensitive_path @ 0x44e6c0 */

0044e6c0        char* left_1 = left
0044e6c5        char* right_1 = right
0044e6c9        while (true)
0044e6c9        char eax_1 = *left_1
0044e6cb        char ecx_1 = *right_1
0044e6cd        left_1 = &left_1[1]
0044e6ce        right_1 = &right_1[1]
0044e6d5        if (eax_1 s>= 0x61 && eax_1 s<= 0x7a)
0044e6d7        eax_1 -= 0x20
0044e6e1        if (ecx_1 s>= 0x61 && ecx_1 s<= 0x7a)
0044e6e3        ecx_1 -= 0x20
0044e6e8        if (eax_1 != 0)
0044e6f0        if (ecx_1 != 0 && eax_1 == ecx_1)
0044e6f0        continue
0044e6f4        if (eax_1 != 0)
0044e6f4        break
0044e6f8        if (ecx_1 != 0)
0044e6f8        break
0044e700        return 1
0044e704        return 0
