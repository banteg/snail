/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: firework_shoot @ 0x441dd0 */

00441dd0        float result
00441dd0        result.b = data_4df934
00441ddb        if ((result.b & 0x10) != 0)
00441de1        result = arg4
00441de9        if (result s> 0)
00441df0        float ebx_1 = arg3
00441df5        float ebp_1 = arg2
00441dfa        float result_1 = result
00441f46        bool cond:1_1
00441e09        int32_t* eax = allocate_sprite(&data_790f30, ebp_1, ebx_1, 0xffffffff, 0xffffffff)
00441e10        int32_t var_24_1 = 0
00441e16        int32_t ecx_1 = eax[1]
00441e19        eax[0xa] = 0xa
00441e26        eax[0x22] = 0x40800000
00441e30        eax[1] = ecx_1 | 0x802
00441e33        eax[0x1a] = 0
00441e3b        long double x87_r7_2 = random_float_below(0.5f) + fconvert.t(0.800000012f)
00441e41        int32_t var_2c_2 = 0
00441e47        eax[0x1c] = 0
00441e4a        eax[0x1d] = 0x3e8e38e4
00441e5d        eax[0x1b] = fconvert.s(fconvert.t(1f) / (x87_r7_2 * fconvert.t(60f)))
00441e60        int32_t ecx_3
00441e60        long double st0_2
00441e60        st0_2, ecx_3 = random_float_below(0.300000012f)
00441e6f        int32_t var_28_1 = ecx_3
00441e70        arg4 = fconvert.s(st0_2 + fconvert.t(0.699999988f))
00441e89        sub_44dbd0(&eax[0xb], arg4, fconvert.s(fconvert.t(arg4) * fconvert.t(0.5f)), 0)
00441e8e        eax[0x18] = 0x3f000000
00441e95        eax[0x19] = 0x3dcccccd
00441eb5        arg2 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(1.22070314e-05f))
00441ed8        arg3 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(1.83105476e-05f) + fconvert.t(0.100000001f))
00441efc        long double x87_r7_17 = float.t(next_math_random_value()) - fconvert.t(16384f)
00441f06        eax[0x25] = 0
00441f1a        eax[0x15] = fconvert.s(x87_r7_17 * fconvert.t(1.22070314e-05f))
00441f20        eax[0x16] = arg3
00441f23        eax[0x17] = arg2
00441f2f        eax[0x12] = *arg1
00441f38        result = result_1 i- 1
00441f38        cond:1_1 = result_1 != 1
00441f39        eax[0x13] = arg1[1]
00441f3c        result_1 = result
00441f43        eax[0x14] = arg1[2]
00441f46        do while (cond:1_1)
00441f53        return result
