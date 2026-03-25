/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_golb_smoke @ 0x415c60 */

00415c82        int32_t* eax_1 = allocate_sprite(&data_790f30, *(*(arg1 + 0x278) + 0x380), 0x80, 0xffffffff, 0xffffffff)
00415c98        int32_t ecx_1 = eax_1[1]
00415c9b        eax_1[0x1a] = 0
00415ca2        ecx_1:1.b |= 8
00415caa        eax_1[1] = ecx_1
00415cba        long double x87_r7_1 = fconvert.t(*(*(arg1 + 0x270) + 0x38)) * fconvert.t(0.166666672f)
00415cc0        eax_1[0x1c] = 0
00415cc7        eax_1[0x1b] = fconvert.s(x87_r7_1)
00415cd9        eax_1[0x1d] = fconvert.s(fconvert.t(*(*(arg1 + 0x270) + 0x38)) * fconvert.t(0.416666687f))
00415cdc        float var_10
00415cdc        int32_t* eax_3 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00415ce6        eax_1[0xb] = *eax_3
00415cec        eax_1[0xc] = eax_3[1]
00415cf2        eax_1[0xd] = eax_3[2]
00415cf5        int32_t eax_4 = eax_3[3]
00415cf8        eax_1[0x18] = 0x3dcccccd
00415cff        eax_1[0x19] = 0x3f000000
00415d06        eax_1[0xe] = eax_4
00415d1b        var_10 = fconvert.s(fconvert.t(*(arg1 + 0x24c)) * fconvert.t(0.400000006f))
00415d2f        float var_c = fconvert.s(fconvert.t(*(arg1 + 0x250)) * fconvert.t(0.400000006f))
00415d39        long double x87_r7_9 = fconvert.t(*(arg1 + 0x254)) * fconvert.t(0.400000006f)
00415d43        eax_1[0x15] = var_10
00415d45        eax_1[0x1e] = 0
00415d4d        eax_1[0x16] = var_c
00415d5c        eax_1[0x17] = fconvert.s(x87_r7_9)
00415d61        eax_1[0x12] = *arg2
00415d66        eax_1[0x13] = arg2[1]
00415d69        int32_t result = arg2[2]
00415d6c        eax_1[0x14] = result
00415d73        return result
