/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_jet_particles @ 0x43a690 */

0043a69a        if (*(arg1 + 0xc) != 1)
0043a69a        return 
0043a6a0        int32_t* eax = *(arg1 + 0x200)
0043a6b8        if (eax[0xefcf7] != *(eax[0xefd0f] + 0xbc))
0043a6b8        return 
0043a6da        float var_3c_1 = fconvert.s(float.t(next_math_random_value()) * fconvert.t(1.52587893e-06f) + fconvert.t(0.400000006f))
0043a6e7        int32_t esi_1 = 0
0043a6ed        int32_t var_50_1 = 0
0043a6fd        float var_40_1 = fconvert.s(float.t(next_math_random_value()) * fconvert.t(1.52587893e-06f) + fconvert.t(0.119999997f))
0043a70b        while (true)
0043a70b        int32_t i = 0
0043a70d        int32_t i_1 = 0
0043a717        float var_48_1 = fconvert.s(float.t(var_50_1) * fconvert.t(0.0714285746f))
0043a72f        float var_44_3 = fconvert.s((fconvert.t(1f) - fconvert.t(var_48_1)) * fconvert.t(var_40_1) * fconvert.t(*(arg1 + 0x210)))
0043a735        float var_34_1
0043a735        float var_30_1
0043a735        float var_2c_1
0043a735        if (i != 0)
0043a75e        int32_t* edx_5 = *(arg1 + 0x200) + 0x3bf940
0043a766        var_34_1 = *edx_5
0043a76d        var_30_1 = edx_5[1]
0043a774        var_2c_1 = edx_5[2]
0043a73d        int32_t* eax_4 = *(arg1 + 0x200) + 0x3bf934
0043a744        var_34_1 = *eax_4
0043a74b        var_30_1 = eax_4[1]
0043a752        var_2c_1 = eax_4[2]
0043a787        float* eax_9 = *(arg1 + 0x10) + 0x29dc
0043a792        long double x87_r7_16 = fneg(fconvert.t(var_48_1) * fconvert.t(var_3c_1) * fconvert.t(*(arg1 + 0x210)))
0043a7a5        long double x87_r7_17 = x87_r7_16 * fconvert.t(eax_9[2])
0043a7b7        void** eax_12 = ((i + (esi_1 << 1) + 2) << 4) + arg1
0043a7b9        float var_34_2 = fconvert.s(fconvert.t(var_34_1) + fconvert.t(fconvert.s(x87_r7_16 * fconvert.t(*eax_9))))
0043a7c3        long double x87_r6_8 = fconvert.t(var_30_1) + fconvert.t(fconvert.s(x87_r7_16 * fconvert.t(eax_9[1])))
0043a7c7        *(*eax_12 + 0x64) = var_44_3
0043a7cc        *(*eax_12 + 0x60) = var_44_3
0043a7d1        float var_30_2 = fconvert.s(x87_r6_8)
0043a7e1        eax = *eax_12 + 0x48
0043a7e9        *eax = var_34_2
0043a7eb        eax[1] = var_30_2
0043a7ee        float var_2c_2 = fconvert.s(fconvert.t(var_2c_1) + x87_r7_17)
0043a7f8        eax[2] = var_2c_2
0043a7fb        if (esi_1 == 0xe)
0043a80e        long double x87_r7_20 = float.t(next_math_random_value()) * fconvert.t(3.05175781e-05f)
0043a814        long double temp0_1 = fconvert.t(0.899999976f)
0043a814        x87_r7_20 - temp0_1
0043a81a        eax.w = (x87_r7_20 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp0_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp0_1 ? 1 : 0) << 0xe
0043a81f        if ((eax:1.b & 0x41) == 0)
0043a83d        int32_t* eax_15 = allocate_sprite(&data_790f30, *(*(arg1 + 0x200) + 0x3bbae4), 0x21, 0xffffffff, 0xffffffff)
0043a85b        int32_t eax_16
0043a85b        eax_16:1.b = eax_15[1]:1.b | 8
0043a862        eax_15[1] = eax_16
0043a867        eax_15[0x1a] = 0
0043a86a        eax_15[0x1b] = 0x3e0e38e4
0043a871        eax_15[0x1c] = 0
0043a874        eax_15[0x1d] = 0
0043a877        struct Color4f color
0043a877        struct Color4f* eax_17 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043a881        eax_15[0xb] = eax_17->r
0043a887        eax_15[0xc] = eax_17->g
0043a88d        eax_15[0xd] = eax_17->b
0043a890        float a = eax_17->a
0043a893        eax_15[0x18] = 0x3dcccccd
0043a89a        eax_15[0x19] = 0x3e99999a
0043a8a1        eax_15[0xe] = a
0043a8aa        float* eax_19 = *(arg1 + 0x200) + 0x3bbb74
0043a8bd        float var_28_1 = fconvert.s(fconvert.t(*eax_19) * fconvert.t(0.850000024f))
0043a8ce        float var_24_1 = fconvert.s(fconvert.t(eax_19[1]) * fconvert.t(0.850000024f))
0043a8d5        long double x87_r7_26 = fconvert.t(eax_19[2]) * fconvert.t(0.850000024f)
0043a8df        eax_15[0x1e] = 0x3a83126f
0043a8e6        eax_15[0x15] = var_28_1
0043a8e8        eax_15[0x12] = var_34_2
0043a8f2        eax_15[0x16] = var_24_1
0043a8f9        eax_15[0x13] = var_30_2
0043a8fc        eax_15[0x17] = fconvert.s(x87_r7_26)
0043a8ff        eax_15[0x14] = var_2c_2
0043a902        esi_1 = var_50_1
0043a906        i = i_1
0043a90a        i += 1
0043a90e        i_1 = i
0043a912        do while (i s< 2)
0043a91c        var_50_1 = esi_1 + 1
0043a920        if (esi_1 + 1 s>= 0xf)
0043a920        break
0043a703        esi_1 = var_50_1
0043a92d        return
