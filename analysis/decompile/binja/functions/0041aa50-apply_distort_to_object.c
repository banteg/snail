/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: apply_distort_to_object @ 0x41aa50 */

0041aa57        float* edi = arg1
0041aa59        float esi = arg2
0041aa5d        arg1.b = 0
0041aa63        long double x87_r7 = fconvert.t(*edi)
0041aa65        long double temp1 = fconvert.t(0f)
0041aa65        x87_r7 - temp1
0041aa6b        void* ebx = *(esi i+ 0x38)
0041aa6e        int32_t result
0041aa6e        result.w = (x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe
0041aa73        if ((result:1.b & 0x40) == 0)
0041aa79        long double x87_r7_1 = fconvert.t(*(esi i+ 0xac))
0041aa7f        long double temp3_1 = fconvert.t(0f)
0041aa7f        x87_r7_1 - temp3_1
0041aa85        long double x87_r7_2 = fconvert.t(*(esi i+ 0xac))
0041aa8b        result.w = (x87_r7_1 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp3_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp3_1 ? 1 : 0) << 0xe | 0x3800
0041aa90        if ((result:1.b & 1) != 0)
0041aa92        x87_r7_2 = fneg(x87_r7_2)
0041aa94        long double x87_r6_1 = fconvert.t(*(esi i+ 0xb8))
0041aa9a        long double temp5_1 = fconvert.t(0f)
0041aa9a        x87_r6_1 - temp5_1
0041aaa0        long double x87_r6_2 = fconvert.t(*(esi i+ 0xb8))
0041aaa6        result.w = (x87_r6_1 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_1, temp5_1) ? 1 : 0) << 0xa | (x87_r6_1 == temp5_1 ? 1 : 0) << 0xe | 0x3000
0041aaab        if ((result:1.b & 1) != 0)
0041aaad        x87_r6_2 = fneg(x87_r6_2)
0041aab1        x87_r7_2 - x87_r6_2
0041aab3        result.w = (x87_r7_2 < x87_r6_2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, x87_r6_2) ? 1 : 0) << 0xa | (x87_r7_2 == x87_r6_2 ? 1 : 0) << 0xe | 0x3800
0041aaba        long double x87_r7_6
0041aaba        if ((result:1.b & 1) == 0)
0041aad7        long double x87_r7_7 = fconvert.t(*(esi i+ 0xac))
0041aadd        long double temp6_1 = fconvert.t(0f)
0041aadd        x87_r7_7 - temp6_1
0041aae3        x87_r7_6 = fconvert.t(*(esi i+ 0xac))
0041aae9        result.w = (x87_r7_7 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp6_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp6_1 ? 1 : 0) << 0xe | 0x3800
0041aaee        if ((result:1.b & 1) != 0)
0041aaf0        x87_r7_6 = fneg(x87_r7_6)
0041aabc        long double x87_r7_5 = fconvert.t(*(esi i+ 0xb8))
0041aac2        long double temp7_1 = fconvert.t(0f)
0041aac2        x87_r7_5 - temp7_1
0041aac8        x87_r7_6 = fconvert.t(*(esi i+ 0xb8))
0041aace        result.w = (x87_r7_5 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp7_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp7_1 ? 1 : 0) << 0xe | 0x3800
0041aad3        if ((result:1.b & 1) != 0)
0041aaf0        x87_r7_6 = fneg(x87_r7_6)
0041aaf5        int32_t i = 0
0041aafd        if (*(esi i+ 0x2c) s> 0)
0041aaff        int32_t edi_1 = 0
0041ab01        void* ebx_1 = ebx + 8
0041ab0a        *(*(esi i+ 0x3c) + edi_1) = *(ebx_1 - 8)
0041ab0d        int32_t edx_1 = *(esi i+ 0x38)
0041ab10        long double x87_r7_8 = fconvert.t(*(edi_1 + edx_1 + 8))
0041ab18        long double temp8_1 = fconvert.t(0f)
0041ab18        x87_r7_8 - temp8_1
0041ab1e        long double x87_r7_9 = fconvert.t(*(edi_1 + edx_1 + 8))
0041ab20        int32_t* eax
0041ab20        eax.w = (x87_r7_8 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp8_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp8_1 ? 1 : 0) << 0xe | 0x3800
0041ab25        if ((eax:1.b & 1) != 0)
0041ab27        x87_r7_9 = fneg(x87_r7_9)
0041ab2f        float* var_1c_1 = edi_1 + edx_1 + 8
0041ab52        i += 1
0041ab55        edi_1 += 0xc
0041ab58        ebx_1 += 0xc
0041ab5e        *(*(esi i+ 0x3c) + edi_1 - 8) = fconvert.s((sine(fconvert.s(x87_r7_9 * fconvert.t(1.57079637f) / fconvert.t(fconvert.s(x87_r7_6)) + fconvert.t(4.71238899f))) + fconvert.t(1f)) * fconvert.t(*edi) + fconvert.t(*(ebx_1 - 0x10)))
0041ab68        *(*(esi i+ 0x3c) + edi_1 - 4) = *(ebx_1 - 0xc)
0041ab71        do while (i s< *(esi i+ 0x2c))
0041ab77        ebx = *(esi i+ 0x3c)
0041ab7a        arg1.b = 1
0041ab7c        long double x87_r7_17 = fconvert.t(edi[1])
0041ab7f        long double temp2 = fconvert.t(0f)
0041ab7f        x87_r7_17 - temp2
0041ab85        result.w = (x87_r7_17 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_17, temp2) ? 1 : 0) << 0xa | (x87_r7_17 == temp2 ? 1 : 0) << 0xe
0041ab8a        if ((result:1.b & 0x40) == 0)
0041ab99        float* var_1c_3 = arg1
0041aba8        float var_8_1 = fconvert.s(sine(fconvert.s(fconvert.t(edi[1]) * fconvert.t(1.57079637f))) + fconvert.t(1f))
0041abbd        long double x87_r7_25 = fconvert.t(1f) - sine(fconvert.s(fconvert.t(edi[1]) * fconvert.t(1.57079637f)))
0041abcf        int32_t i_1 = 0
0041abd7        arg2 = *(esi i+ 0xa8)
0041abdb        if (*(esi i+ 0x2c) s> 0)
0041abdd        result = 0
0041abdf        arg1 = ebx + 8
0041abe6        long double x87_r7_27 = fconvert.t(var_8_1) * fconvert.t(arg1[-2])
0041abec        i_1 += 1
0041abed        result += 0xc
0041abf0        arg1 = &arg1[3]
0041abf3        *(*(esi i+ 0x3c) + result - 0xc) = fconvert.s(x87_r7_27)
0041ac09        *(*(esi i+ 0x3c) + result - 8) = fconvert.s((fconvert.t(arg1[-4]) - fconvert.t(arg2)) * fconvert.t(fconvert.s(x87_r7_25)) + fconvert.t(arg2))
0041ac13        *(*(esi i+ 0x3c) + result - 4) = arg1[-3]
0041ac1c        do while (i_1 s< *(esi i+ 0x2c))
0041ac1e        ebx = *(esi i+ 0x3c)
0041ac21        arg1.b = 1
0041ac23        long double x87_r7_32 = fconvert.t(edi[2])
0041ac26        long double temp4 = fconvert.t(0f)
0041ac26        x87_r7_32 - temp4
0041ac2c        result.w = (x87_r7_32 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_32, temp4) ? 1 : 0) << 0xa | (x87_r7_32 == temp4 ? 1 : 0) << 0xe
0041ac31        if ((result:1.b & 0x40) == 0)
0041ac40        float* var_1c_6 = arg1
0041ac55        arg2 = fconvert.s(sine(fconvert.s(fconvert.t(edi[2]) * fconvert.t(1.57079637f))) * fconvert.t(0.100000001f) + fconvert.t(1f))
0041ac6a        long double x87_r7_41 = fconvert.t(1f) - sine(fconvert.s(fconvert.t(edi[2]) * fconvert.t(1.57079637f)))
0041ac76        int32_t i_2 = 0
0041ac7e        if (*(esi i+ 0x2c) s> 0)
0041ac80        int32_t eax_4 = 0
0041ac82        void* ecx_2 = ebx + 8
0041ac89        long double x87_r7_43 = fconvert.t(arg2) * fconvert.t(*(ecx_2 - 8))
0041ac8f        i_2 += 1
0041ac90        eax_4 += 0xc
0041ac93        ecx_2 += 0xc
0041ac96        *(*(esi i+ 0x3c) + eax_4 - 0xc) = fconvert.s(x87_r7_43)
0041aca4        *(*(esi i+ 0x3c) + eax_4 - 8) = fconvert.s(fconvert.t(arg2) * fconvert.t(*(ecx_2 - 0x10)))
0041acb2        *(*(esi i+ 0x3c) + eax_4 - 4) = fconvert.s(fconvert.t(fconvert.s(x87_r7_41)) * fconvert.t(*(ecx_2 - 0xc)))
0041acb9        do while (i_2 s< *(esi i+ 0x2c))
0041acbf        if (arg1.b == 0)
0041acd5        return result
0041acc6        *(esi i+ 0x38) = *(esi i+ 0x3c)
0041acc9        return calc_object_facequad_normals_simple(esi)
