/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_golb_impact_sprite @ 0x415d80 */

00415d80        int32_t* result
00415d80        result.b = data_4df934
00415d8a        if ((result.b & 0x10) != 0)
00415da9        int32_t* eax_1 = allocate_sprite(&data_790f30, *(*(arg1 + 0x278) + 0x380), 0x21, 0xffffffff, 0xffffffff)
00415db4        int32_t ecx_1
00415db4        ecx_1:1.b = eax_1[1]:1.b | 8
00415dbf        eax_1[1] = ecx_1
00415dc6        eax_1[0x1a] = 0
00415dc9        eax_1[0x15] = 0
00415dcf        eax_1[0x1c] = 0
00415dd2        int32_t var_c_1 = 0
00415dd6        eax_1[0x16] = 0x3d4ccccd
00415dd9        int32_t var_4_1 = 0
00415de6        eax_1[0x1b] = 0x3d638e38
00415ded        __builtin_strncpy(&eax_1[0x1d], "VUU?", 8)
00415df4        eax_1[0x18] = 0x3f000000
00415dfb        eax_1[0x19] = 0x3f800000
00415e02        eax_1[0x17] = 0
00415e07        result = &eax_1[0x12]
00415e0b        *result = *arg2
00415e10        result[1] = arg2[1]
00415e16        result[2] = arg2[2]
00415e1c        return result
