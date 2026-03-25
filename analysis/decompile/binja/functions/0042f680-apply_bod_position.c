/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: apply_bod_position @ 0x42f680 */

0042f687        int32_t i = 0
0042f689        void* result = *(arg1 + 0x24)
0042f691        if (*(result + 0x2c) s> 0)
0042f699        int32_t esi_1 = 0
0042f6a6        float var_c
0042f6a6        float* eax = multiply_vector_by_matrix_copy(*(result + 0x38) + esi_1, &var_c, arg2)
0042f6b3        float* ecx_4 = *(*(arg1 + 0x24) + 0x38) + esi_1
0042f6b5        i += 1
0042f6b6        esi_1 += 0xc
0042f6b9        *ecx_4 = *eax
0042f6be        ecx_4[1] = eax[1]
0042f6c4        ecx_4[2] = eax[2]
0042f6c7        result = *(arg1 + 0x24)
0042f6cd        do while (i s< *(result + 0x2c))
0042f6d6        return result
