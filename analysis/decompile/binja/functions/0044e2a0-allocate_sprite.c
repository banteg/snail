/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: allocate_sprite @ 0x44e2a0 */

0044e2a2        int32_t* result = *(arg1 + 0x83d78)
0044e2ac        if (result == 0)
0044e2b5        return 0x814cb0
0044e2c0        *(arg1 + 0x83d78) = result[3]
0044e2c6        result[2] = arg2
0044e2c9        void* eax_2 = *(arg1 + (arg2 << 2) + 0x83d64)
0044e2d2        if (eax_2 != 0)
0044e2d4        *(eax_2 + 0x10) = result
0044e2d7        result[4] = 0
0044e2e1        result[3] = *(arg1 + (arg2 << 2) + 0x83d64)
0044e2e4        *(arg1 + (arg2 << 2) + 0x83d64) = result
0044e2ed        initialize_sprite(result)
0044e2ff        int32_t ecx_3 = result[1] | 1 << (arg2.b + 0x18)
0044e305        result[1] = ecx_3
0044e30f        result[7] = *((arg3 << 2) + &data_78ff90)
0044e319        if (arg5 != 0xffffffff)
0044e31e        result[1] = ecx_3 | 0x20
0044e32c        result[8] = *((arg4 << 2) + &data_78ff90)
0044e336        result[9] = *((arg5 << 2) + &data_78ff90)
0044e342        if (arg4 != 0xffffffff)
0044e347        result[1] = ecx_3 | 0x10
0044e351        result[8] = *((arg4 << 2) + &data_78ff90)
0044e354        result[0x19] = 0
0044e357        result[0x27] = arg3
0044e35d        result[0x2b] = 0
0044e363        result[0x2c] = 0
0044e376        result[0x28] = *(*((arg3 << 2) + &data_78ff90) + 0x90)
0044e388        if (((**((arg3 << 2) + &data_78ff90)).w:1.b & 0x20) != 0)
0044e38d        int32_t edi_2 = result[1] | 0x2000
0044e393        result[1] = edi_2
0044e3a5        result[0x2c] = *(*((arg3 << 2) + &data_78ff90) + 0x94)
0044e3b7        if (((**((arg3 << 2) + &data_78ff90)).w:1.b & 0x40) != 0)
0044e3b9        int32_t ecx_11
0044e3b9        ecx_11:1.b = edi_2:1.b | 0x40
0044e3bc        result[1] = ecx_11
0044e3c4        return result
