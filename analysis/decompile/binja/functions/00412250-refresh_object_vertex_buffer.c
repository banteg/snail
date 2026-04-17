/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: refresh_object_vertex_buffer @ 0x412250 */

00412253        float esi = arg1
00412258        int32_t ebx = *(esi i+ 0x10)
00412261        if ((ebx & 0x200000) == 0)
00412328        if ((ebx.b & 4) != 0)
00412341        int32_t* eax_8 = *(*(esi i+ 0xc0) + 8)
00412350        (*(*eax_8 + 0x2c))(eax_8, 0, *(esi i+ 0xc4) * 0x18, &arg1, 0)
00412359        int32_t i = 0
0041235d        if (*(esi i+ 0xc4) s> 0)
0041235f        int32_t edi_6 = 0
00412361        void* ebx_4 = nullptr
00412368        int32_t* edx_9 = ebx_4 + *(esi i+ 0x38)
0041236e        int32_t* eax_12 = arg1 i+ edi_6
00412370        ebx_4 += 0xc
00412375        edi_6 += 0x18
00412378        *eax_12 = *edx_9
0041237d        eax_12[1] = edx_9[1]
00412383        eax_12[2] = edx_9[2]
00412388        int32_t eax_14
00412388        int32_t edx_11
00412388        edx_11:eax_14 = sx.q(i)
00412397        int32_t edx_14 = i & 3
0041239a        i += 1
0041239e        int32_t eax_18 = edx_14 + ((eax_14 + (edx_11 & 3)) s>> 2) * 6
004123a8        *(edi_6 i+ arg1 - 8) = *(*(esi i+ 0x5c) + (eax_18 << 3) + 0x10)
004123b7        *(edi_6 i+ arg1 - 4) = *(*(esi i+ 0x5c) + (eax_18 << 3) + 0x14)
004123c3        do while (i s< *(esi i+ 0xc4))
004123cb        int32_t* eax_22 = *(*(esi i+ 0xc0) + 8)
004123d1        (*(*eax_22 + 0x30))(eax_22)
004123d8        return 
00412267        void* edi_1 = *(esi i+ 0xbc)
00412273        int32_t eax_1
00412273        int16_t x87control
00412273        int16_t x87control_1
00412273        eax_1, x87control_1 = __ftol(x87control, float.t(*(edi_1 + 4)) * fconvert.t(*(edi_1 + 0xc)))
00412280        *(esi i+ 0x38) = **(*(edi_1 + 8) + (eax_1 << 2))
00412289        int32_t eax_3 = __ftol(x87control_1, float.t(*(edi_1 + 4)) * fconvert.t(*(edi_1 + 0xc)))
0041229d        *(esi i+ 0x60) = *(*(*(edi_1 + 8) + (eax_3 << 2)) + 4)
004122a0        if ((ebx & 0x800000) != 0)
004122a9        apply_distort_to_object(esi i+ 0x80, esi)
004122b6        int32_t* eax_5 = *(*(esi i+ 0xc0) + 8)
004122d0        (*(*eax_5 + 0x2c))(eax_5, 0, *(esi i+ 0xc4) * 0x18, &arg1, 0)
004122d9        int32_t i_1 = 0
004122dd        if (*(esi i+ 0xc4) s> 0)
004122df        int32_t edx_4 = 0
004122e1        void* ecx_9 = nullptr
004122e8        int32_t* edi_3 = ecx_9 + *(esi i+ 0x38)
004122ee        int32_t* ebx_3 = arg1 i+ edx_4
004122f0        i_1 += 1
004122f3        ecx_9 += 0xc
004122f6        *ebx_3 = *edi_3
004122f8        edx_4 += 0x18
004122fe        ebx_3[1] = edi_3[1]
00412304        ebx_3[2] = edi_3[2]
0041230f        do while (i_1 s< *(esi i+ 0xc4))
00412317        int32_t* eax_6 = *(*(esi i+ 0xc0) + 8)
0041231d        (*(*eax_6 + 0x30))(eax_6)
00412324        return
