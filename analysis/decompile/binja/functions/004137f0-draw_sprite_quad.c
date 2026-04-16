/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_sprite_quad @ 0x4137f0 */

004137f3        int32_t* eax = arg1
004137f9        int32_t var_8 = 0
00413801        int32_t ecx = eax[2]
00413804        int32_t edx = eax[1]
00413807        int32_t eax_1 = *eax
00413811        int32_t var_c = 0
00413819        int32_t var_10 = 0
00413821        int32_t var_14 = 0
00413829        int32_t var_1c = 0
00413831        int32_t var_20 = 0
00413839        int32_t var_24 = 0
00413841        int32_t var_28 = 0
00413849        int32_t var_30 = 0
00413851        int32_t var_34 = 0
00413859        int32_t var_38 = 0
00413861        int32_t var_3c = 0
00413869        int32_t var_4 = 0x3f800000
00413871        int32_t var_18 = 0x3f800000
00413879        int32_t var_2c = 0x3f800000
00413881        int32_t var_40 = 0x3f800000
00413889        j_sub_44fd5c(&var_40, eax_1, edx, ecx)
0041388e        int32_t* eax_2 = data_502fec
0041389d        (*(*eax_2 + 0x94))(eax_2, 2, &var_40)
004138a3        float esi = arg2
004138bf        arg2 = fconvert.s((fconvert.t(1f) - fconvert.t(*(esi i+ 0x68))) * fconvert.t(*(esi i+ 0x60)) + fconvert.t(*(esi i+ 0x64)) * fconvert.t(*(esi i+ 0x68)))
004138c3        sub_414500(*(esi i+ 0x1c))
004138c9        sub_413670(esi)
004138d7        float var_44
004138d7        if (((*(esi i+ 4)).w:1.b & 0x10) == 0)
004138ef        var_44 = fconvert.s((fconvert.t(1f) - fconvert.t(*(esi i+ 0x68))) * fconvert.t(*(esi i+ 0x38)))
004138d9        var_44 = 1f
0041391e        struct ColorBGRA8 out
0041391e        out.a = __ftol(pack_color_rgba_u8(&out, esi i+ 0x2c), fconvert.t(var_44) * fconvert.t(255f))
00413924        int32_t* eax_6 = *(data_502fe0 + 8)
00413933        int32_t ecx_4 = (*(*eax_6 + 0x2c))(eax_6, 0, 0x60, &arg1, 0)
00413936        long double x87_r7_9 = fconvert.t(*(esi i+ 0x7c))
00413939        long double temp0 = fconvert.t(0f)
00413939        x87_r7_9 - temp0
00413944        long double x87_r7_11
00413944        if ((((x87_r7_9 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp0) ? 1 : 0) << 0xa | (x87_r7_9 == temp0 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
00413a09        int32_t var_54_4 = ecx_4
00413a1c        float var_44_1 = fconvert.s(cosine(fconvert.s(fconvert.t(*(esi i+ 0x7c)) + fconvert.t(0.785398185f))) * fconvert.t(arg2) * fconvert.t(1.41400003f))
00413a3c        long double x87_r7_21 = sine(fconvert.s(fconvert.t(*(esi i+ 0x7c)) + fconvert.t(0.785398185f))) * fconvert.t(arg2) * fconvert.t(1.41400003f)
00413a46        *arg1 = fconvert.s(fneg(x87_r7_21))
00413a50        arg1[1] = fconvert.s(fconvert.t(var_44_1))
00413a5b        arg1[2] = 0
00413a62        arg1[4] = 0
00413a69        arg1[5] = 0
00413a70        int32_t edx_16
00413a70        edx_16.b = out.b
00413a70        edx_16:1.b = out.g
00413a70        edx_16:2.b = out.r
00413a70        edx_16:3.b = out.a
00413a74        arg1[3] = edx_16
00413a7b        arg1[6] = fconvert.s(fconvert.t(var_44_1))
00413a89        arg1[7] = fconvert.s(x87_r7_21)
00413a92        arg1[8] = 0
00413a99        arg1[0xa] = 0x3f800000
00413aa0        arg1[0xb] = 0
00413aa7        int32_t edx_19
00413aa7        edx_19.b = out.b
00413aa7        edx_19:1.b = out.g
00413aa7        edx_19:2.b = out.r
00413aa7        edx_19:3.b = out.a
00413aab        arg1[9] = edx_19
00413ab2        arg1[0xc] = fconvert.s(x87_r7_21)
00413abf        arg1[0xd] = fconvert.s(fneg(fconvert.t(var_44_1)))
00413aca        arg1[0xe] = 0
00413ad1        arg1[0x10] = 0x3f800000
00413ad8        arg1[0x11] = 0x3f800000
00413adf        int32_t ecx_22
00413adf        ecx_22.b = out.b
00413adf        ecx_22:1.b = out.g
00413adf        ecx_22:2.b = out.r
00413adf        ecx_22:3.b = out.a
00413ae3        arg1[0xf] = ecx_22
00413af2        arg1[0x12] = fconvert.s(fneg(fconvert.t(var_44_1) * fconvert.t(*(esi i+ 0x88))))
00413afb        x87_r7_11 = fneg(x87_r7_21 * fconvert.t(*(esi i+ 0x88)))
00413952        x87_r7_11 = fneg(fconvert.t(arg2))
00413956        *arg1 = fconvert.s(x87_r7_11)
00413960        arg1[1] = fconvert.s(fconvert.t(arg2))
0041396b        arg1[2] = 0
00413972        arg1[4] = 0
00413979        arg1[5] = 0
00413980        int32_t edx_6
00413980        edx_6.b = out.b
00413980        edx_6:1.b = out.g
00413980        edx_6:2.b = out.r
00413980        edx_6:3.b = out.a
00413984        arg1[3] = edx_6
0041398b        arg1[6] = fconvert.s(fconvert.t(arg2))
0041399b        arg1[7] = fconvert.s(fconvert.t(arg2))
004139a6        arg1[8] = 0
004139ad        arg1[0xa] = 0x3f800000
004139b4        arg1[0xb] = 0
004139bb        int32_t edx_9
004139bb        edx_9.b = out.b
004139bb        edx_9:1.b = out.g
004139bb        edx_9:2.b = out.r
004139bb        edx_9:3.b = out.a
004139bf        arg1[9] = edx_9
004139c6        arg1[0xc] = fconvert.s(fconvert.t(arg2))
004139cf        arg1[0xd] = fconvert.s(x87_r7_11)
004139d8        arg1[0xe] = 0
004139df        arg1[0x10] = 0x3f800000
004139e6        arg1[0x11] = 0x3f800000
004139ed        int32_t ecx_13
004139ed        ecx_13.b = out.b
004139ed        ecx_13:1.b = out.g
004139ed        ecx_13:2.b = out.r
004139ed        ecx_13:3.b = out.a
004139f1        arg1[0xf] = ecx_13
004139f8        arg1[0x12] = fconvert.s(x87_r7_11)
00413b01        arg1[0x13] = fconvert.s(x87_r7_11)
00413b08        arg1[0x14] = 0
00413b0f        arg1[0x16] = 0
00413b16        arg1[0x17] = 0x3f800000
00413b1d        int32_t eax_14
00413b1d        eax_14.b = out.b
00413b1d        eax_14:1.b = out.g
00413b1d        eax_14:2.b = out.r
00413b1d        eax_14:3.b = out.a
00413b21        arg1[0x15] = eax_14
00413b2a        int32_t* eax_15 = *(data_502fe0 + 8)
00413b30        (*(*eax_15 + 0x30))(eax_15)
00413b39        int32_t* eax_16 = data_502fec
00413b48        (*(*eax_16 + 0x14c))(eax_16, 0, *(data_502fe0 + 8), 0x18)
00413b4e        int32_t* eax_17 = data_502fec
00413b5b        (*(*eax_17 + 0x130))(eax_17, 0x142)
00413b61        int32_t* eax_18 = data_502fec
00413b6e        int32_t result = (*(*eax_18 + 0x118))(eax_18, 6, 0, 2)
00413b83        int32_t edx_30 = data_503170 + 1
00413b86        data_4f7450 += 2
00413b8d        data_503170 = edx_30
00413b94        if (result == 0)
00413ba6        return result
00413b9b        return report_errorf("Draw Primitive Failed")
