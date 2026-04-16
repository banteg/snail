/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_animation @ 0x430a70 */

00430a73        int32_t eax = 0
00430a76        void* ebx = arg3
00430a85        if (arg2 s> 0)
00430a8a        int32_t* ecx = ebx + 0x24
00430a92        if (*(*ecx + 0x2c) != *(arg1 + 0x2c))
00430b3b        int32_t var_4c = *((eax << 7) + ebx + 0x7c)
00430b41        report_errorf("Anim tween Vertices don't match Frame %i")
00430b50        return 0
00430a98        eax += 1
00430a99        ecx = &ecx[0x20]
00430aa1        do while (eax s< arg2)
00430aad        *(arg1 + 0x10) |= 0x200000
00430ab9        int16_t x87control
00430ab9        int32_t ebp_2 = __ftol(x87control, fconvert.t(1f) / fconvert.t(arg4))
00430ac2        int32_t var_34 = ebp_2
00430ac6        void* eax_2 = allocate_tracked_memory(0x14, "Object Animation")
00430ad0        *(arg1 + 0xbc) = eax_2
00430ad6        *(eax_2 + 4) = ebp_2
00430ae4        **(arg1 + 0xbc) = arg5
00430af1        *(*(arg1 + 0xbc) + 0xc) = 0
00430b06        *(*(arg1 + 0xbc) + 0x10) = arg4
00430b1a        arg3 = nullptr
00430b22        *(*(arg1 + 0xbc) + 8) = allocate_tracked_memory(ebp_2 << 2, "Object Animation Frame array")
00430b25        float eax_6 = *(ebx + 0x7c)
00430b28        arg5.d = eax_6
00430b2c        if (arg2 != 1)
00430b59        arg4 = *(ebx + 0xfc)
00430b2e        arg4 = eax_6
00430b5d        int32_t edi_1 = 0
00430b61        if (ebp_2 s> 0)
00430b7a        int32_t* ebx_1 = ebx + 0x24
00430b86        int32_t var_50_1 = 8
00430b9b        *(*(*(arg1 + 0xbc) + 8) + (edi_1 << 2)) = allocate_tracked_memory(8, "Object Animation Frame")
00430bbe        **(*(*(arg1 + 0xbc) + 8) + (edi_1 << 2)) = allocate_tracked_memory(*(arg1 + 0x2c) * 0xc, "Object Animation Frame Vertices")
00430be2        *(*(*(*(arg1 + 0xbc) + 8) + (edi_1 << 2)) + 4) = allocate_tracked_memory(*(arg1 + 0x54) * 0x18, "Object Animation Frame FaceQuad Normals")
00430bf2        long double x87_r7_4 = float.t(*((arg2 << 7) + ebx - 4) * edi_1) / fconvert.t(fconvert.s(float.t(var_34)))
00430bfa        var_50_1.q = fconvert.d(x87_r7_4)
00430bfd        int16_t x87control_1
00430bfd        long double st0_1
00430bfd        st0_1, x87control_1 = sub_48c0bc(var_50_1)
00430c1b        if (__ftol(x87control_1, st0_1) s>= arg4 && arg3 s< arg2 - 1)
00430c1d        int32_t edx_13 = ebx_1[0x36]
00430c25        float eax_20 = ebx_1[0x56]
00430c2c        ebx_1 = &ebx_1[0x20]
00430c32        arg3 += 1
00430c36        arg5.d = edx_13
00430c3a        arg4 = eax_20
00430c53        int32_t edx_15 = 0
00430c5f        int32_t var_30_3 = 0
00430c65        float var_38_2 = fconvert.s((fconvert.t(fconvert.s(x87_r7_4)) - float.t(arg5.d)) / float.t(arg4 i- arg5.d))
00430c69        if (*(arg1 + 0x2c) s> 0)
00430d3f        bool cond:3_1
00430c74        if (arg2 != 1)
00430cb1        float* ecx_20 = *(ebx_1[0x20] + 0x38) + edx_15
00430cb3        float* eax_30 = *(*ebx_1 + 0x38)
00430cc2        float* eax_31 = eax_30 + edx_15
00430d01        float var_20_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(ecx_20[1]) - fconvert.t(*(eax_30 + edx_15 + 4)))) * fconvert.t(var_38_2))) + fconvert.t(eax_31[1]))
00430d12        float var_1c_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(ecx_20[2]) - fconvert.t(eax_31[2]))) * fconvert.t(var_38_2))) + fconvert.t(eax_31[2]))
00430d1c        int32_t* eax_34 = **(*(*(arg1 + 0xbc) + 8) + (edi_1 << 2)) + edx_15
00430d1e        *eax_34 = fconvert.s((fconvert.t(*ecx_20) - fconvert.t(*(eax_30 + edx_15))) * fconvert.t(var_38_2) + fconvert.t(*eax_31))
00430d24        eax_34[1] = var_20_1
00430d2b        eax_34[2] = var_1c_1
00430c81        int32_t* ecx_17 = *(*ebx_1 + 0x38) + edx_15
00430c8d        int32_t* eax_27 = **(*(*(arg1 + 0xbc) + 8) + (edi_1 << 2)) + edx_15
00430c8f        *eax_27 = *ecx_17
00430c94        eax_27[1] = ecx_17[1]
00430c9a        ebp_2 = var_34
00430c9e        eax_27[2] = ecx_17[2]
00430d36        edx_15 += 0xc
00430d39        cond:3_1 = var_30_3 + 1 s< *(arg1 + 0x2c)
00430d3b        var_30_3 += 1
00430d3f        do while (cond:3_1)
00430d45        void* eax_37 = *(arg1 + 0xbc)
00430d53        *(arg1 + 0x38) = **(*(eax_37 + 8) + (edi_1 << 2))
00430d61        *(arg1 + 0x60) = *(*(*(eax_37 + 8) + (edi_1 << 2)) + 4)
00430d64        calc_object_facequad_normals(arg1)
00430d69        edi_1 += 1
00430d6c        do while (edi_1 s< ebp_2)
00430d72        void* result = *(arg1 + 0xbc)
00430d7b        *(result + 0xc) = 0
00430d86        return result
