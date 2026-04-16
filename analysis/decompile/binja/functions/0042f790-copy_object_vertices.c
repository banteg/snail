/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: copy_object_vertices @ 0x42f790 */

0042f790        void* result = *(arg1 + 0x2c)
0042f793        int32_t i = 0
0042f797        if (result s> 0)
0042f79c        result = nullptr
0042f7a3        int32_t* esi_2 = result + *(arg1 + 0x38)
0042f7a8        int32_t* edi_3 = *(arg1 + 0x3c) + result
0042f7aa        i += 1
0042f7ad        result += 0xc
0042f7b0        *edi_3 = *esi_2
0042f7b5        edi_3[1] = esi_2[1]
0042f7bb        edi_3[2] = esi_2[2]
0042f7c3        do while (i s< *(arg1 + 0x2c))
0042f7c8        return result
