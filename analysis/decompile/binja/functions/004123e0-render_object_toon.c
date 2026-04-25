/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: render_object_toon @ 0x4123e0 */

004123ee        int16_t result = (*(arg1 + 0x10)).w
004123f4        if ((result:1.b & 0x40) == 0)
004126b0        return result
00412408        int32_t __saved_ebp_7
00412408        int32_t __saved_ebp_1 = __saved_ebp_7
00412421        int32_t __saved_ebp_8 = __saved_ebp_7
0041242e        float var_80[0x10]
0041242e        build_perspective_projection_matrix(&var_80, data_5031d4, data_50316c, fconvert.s(fconvert.t(data_5031cc) + fconvert.t(0.00400000019f)), fconvert.s(fconvert.t(data_5031d0) + fconvert.t(30f)))
00412433        int32_t* eax_1 = data_502fec
00412442        (*(*eax_1 + 0x94))(eax_1, 3, &var_80)
00412448        void* eax_2 = data_5031b8
0041245e        float var_ac_1 = fconvert.s(fconvert.t(*(eax_2 + 0x30)) - fconvert.t(*(arg2 + 0x30)))
00412468        float var_a8_1 = fconvert.s(fconvert.t(*(eax_2 + 0x34)) - fconvert.t(*(arg2 + 0x34)))
0041246f        long double x87_r7_10 = fconvert.t(*(eax_2 + 0x38)) - fconvert.t(*(arg2 + 0x38))
00412483        float var_40[0x10]
00412483        __builtin_memcpy(&var_40, arg2, 0x40)
00412485        float var_a4_1 = fconvert.s(x87_r7_10)
00412491        float var_9c = var_ac_1
00412499        invert_matrix_in_place(&var_40)
004124a7        rotate_vector_by_matrix(&var_9c, &var_40)
004124b0        vector_magnitude(&var_9c)
004124bb        int32_t* eax_4 = data_502fec
004124ca        (*(*eax_4 + 0x154))(eax_4, **(arg1 + 0xd8), 0)
004124d6        int32_t* eax_5 = data_502fec
004124e6        (*(*eax_5 + 0x14c))(eax_5, 0, *(*(arg1 + 0xc0) + 8), 0x18)
004124ef        int32_t var_a0_1 = 0
004124f9        if (*(arg1 + 0x70) s> 0)
00412500        int32_t ebp_1 = 0
00412667        bool cond:0_1
00412508        int32_t esi_2 = 0
0041250f        int32_t* eax_8 = **(arg1 + 0xd8)
0041251c        int16_t* var_b0
0041251c        (*(*eax_8 + 0x2c))(eax_8, 0, *(arg1 + 0x2c) << 1, &var_b0, 0)
00412522        char* eax_10 = *(arg1 + 0x74) + ebp_1
00412527        if ((*eax_10 & 1) == 0)
00412549        int32_t edx_10 = *(eax_10 + 0xc)
0041254c        int32_t ecx_10 = *(arg1 + 0x60)
00412559        int32_t edx_12 = *(eax_10 + 0x10)
00412562        int32_t eax_13 = *(eax_10 + 4) * 3
00412568        int32_t edx_14 = *(arg1 + 0x38)
00412573        void* eax_14 = edx_14 + (eax_13 << 2)
00412581        float var_a8_2 = fconvert.s(fconvert.t(var_a8_1) - fconvert.t(*(eax_14 + 4)))
00412589        long double x87_r7_18 = fconvert.t(var_a4_1) - fconvert.t(*(eax_14 + 8))
00412594        float var_8c = fconvert.s(fconvert.t(var_9c) - fconvert.t(*(edx_14 + (eax_13 << 2))))
00412598        float var_88_1 = var_a8_2
004125a4        float var_84_1 = fconvert.s(x87_r7_18)
004125ad        float var_90_1 = fconvert.s(dot_vector(&var_8c, ecx_10 + edx_12 * 0xc))
004125bb        long double x87_r7_21 = dot_vector(&var_8c, ecx_10 + edx_10 * 0xc) * fconvert.t(var_90_1)
004125bf        long double temp0_1 = fconvert.t(0.00999999978f)
004125bf        x87_r7_21 - temp0_1
004125ca        if ((((x87_r7_21 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp0_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp0_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004125d3        float edx_15
004125d3        edx_15.w = *(*(arg1 + 0x74) + ebp_1 + 4)
004125d8        *var_b0 = edx_15.w
004125e2        edx_15.w = *(*(arg1 + 0x74) + ebp_1 + 8)
004125e7        var_b0[1] = edx_15.w
004125eb        esi_2 = 2
00412531        *var_b0 = *(eax_10 + 4)
00412540        var_b0[1] = *(*(arg1 + 0x74) + ebp_1 + 8)
004125eb        esi_2 = 2
004125f6        int32_t* eax_20 = **(arg1 + 0xd8)
004125fb        (*(*eax_20 + 0x30))(eax_20)
00412600        if (esi_2 s> 0)
0041260f        bind_texture_ref(get_sprite_texture(0x5d))
00412616        int32_t* ecx_18 = data_502fec
0041261c        int32_t eax_23
0041261c        int32_t edx_17
0041261c        edx_17:eax_23 = sx.q(esi_2)
0041262c        int32_t esi_4 = (eax_23 - edx_17) s>> 1
00412637        (*(*ecx_18 + 0x11c))(ecx_18, 2, 0, *(arg1 + 0xc4), 0, esi_4)
0041264a        int32_t eax_27 = data_503170 + 1
0041264b        data_4f7450 += esi_4
00412651        data_503170 = eax_27
0041265e        ebp_1 += 0x24
00412661        cond:0_1 = var_a0_1 + 1 s< *(arg1 + 0x70)
00412663        var_a0_1 += 1
00412667        do while (cond:0_1)
0041268d        build_perspective_projection_matrix(&var_80, data_5031d4, data_50316c, data_5031cc, data_5031d0)
00412692        int32_t* eax_32 = data_502fec
004126a1        return (*(*eax_32 + 0x94))(eax_32, 3, &var_80)
