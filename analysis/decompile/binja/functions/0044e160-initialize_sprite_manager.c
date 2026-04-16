/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_sprite_manager @ 0x44e160 */

0044e169        *arg1 = 0
0044e16b        __builtin_memset(&arg1[0x83d64], 0, 0x14)
0044e187        int32_t i = 0
0044e18f        *(arg1 + 0x83d78) = &arg1[4]
0044e1ed        void* result
0044e19b        void* ebp_1 = &arg1[i * 0xb4]
0044e1a1        result = initialize_sprite(ebp_1 + 4)
0044e1a1        int16_t top = top - 1
0044e1a8        if (i == 0)
0044e1aa        result = &arg1[0xb8]
0044e1b0        *(arg1 + 0x14) = 0
0044e1b3        *(arg1 + 0x10) = result
0044e1be        if (i != 0xbb7)
0044e1da        result = ebp_1 + 0xb8
0044e1e0        *(ebp_1 + 0x14) = ebp_1 - 0xb0
0044e1e3        *(ebp_1 + 0x10) = result
0044e1c6        *(arg1 + 0x83cc0) = &arg1[0x83bfc]
0044e1cc        *(arg1 + 0x83cbc) = 0
0044e1e6        i += 1
0044e1ed        do while (i s< 0xbb8)
0044e1f3        return result
