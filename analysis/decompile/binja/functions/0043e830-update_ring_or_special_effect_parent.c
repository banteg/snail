/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_ring_or_special_effect_parent @ 0x43e830 */

0043e836        void* esi = arg1
0043e839        float* eax = *(esi + 0x1d0)
0043e83f        arg1.b = *(eax + 9)
0043e844        if (arg1.b == 0)
0043e850        int32_t edi_2 = *(esi + 0x1e8) + 1
0043e853        *(esi + 0x1e8) = edi_2
0043e85c        if (edi_2 == 3)
0043e860        *(esi + 0x1e8) = 0
0043e879        switch (*(esi + 0x80))
0043e880        case 1
0043e880        eax.b = *(esi + 0x1dc)
0043e888        if (eax.b != 0)
0043e890        long double x87_r7_2 = fconvert.t(*(esi + 0x1e4)) + fconvert.t(*(esi + 0x1e0))
0043e896        long double temp0_1 = fconvert.t(6.28318548f)
0043e896        x87_r7_2 - temp0_1
0043e89c        *(esi + 0x1e0) = fconvert.s(x87_r7_2)
0043e89c        bool c1_1 = unimplemented  {fst dword [esi+0x1e0], st0}
0043e8a2        eax.w = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800
0043e8a7        if ((eax:1.b & 0x41) != 0)
0043e8b7        long double temp4_1 = fconvert.t(0f)
0043e8b7        x87_r7_2 - temp4_1
0043e8bd        eax.w = (x87_r7_2 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp4_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp4_1 ? 1 : 0) << 0xe | 0x3800
0043e8c2        if ((eax:1.b & 1) != 0)
0043e8ca        *(esi + 0x1e0) = fconvert.s(x87_r7_2 + fconvert.t(6.28318548f))
0043e8af        *(esi + 0x1e0) = fconvert.s(x87_r7_2 - fconvert.t(6.28318548f))
0043e8e9        *(esi + 0x68) = fconvert.s(sine(*(esi + 0x1e0)) * fconvert.t(3f))
0043e8f2        int32_t i_10 = 0xa
0043e8f7        int32_t* edi_3 = esi + 0x90
0043e904        int32_t i
0043e8fb        update_ring_or_special_effect_particle(edi_3)
0043e900        edi_3 = &edi_3[8]
0043e903        i = i_10
0043e903        i_10 -= 1
0043e904        do while (i != 1)
0043e906        void* ecx_3 = *(esi + 0x84)
0043e90c        long double x87_r7_8 = fconvert.t(*(esi + 0x70))
0043e90f        long double temp7_1 = fconvert.t(*(ecx_3 + 0x2980))
0043e90f        x87_r7_8 - temp7_1
0043e91a        if ((((x87_r7_8 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp7_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp7_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0043e920        int16_t eax_3 = (*(esi + 4)).w
0043e923        *(esi + 0x80) = 0
0043e933        void* ecx_5 = data_4df904 + 0x5a8
0043e93c        if ((eax_3:1.b & 2) == 0)
0043e943        report_errorf("List remove")
0043e94f        if ((eax_3.b & 0x40) == 0)
0043e960        void* eax_4 = *(esi + 0xc)
0043e965        if (eax_4 != 0)
0043e96a        *(eax_4 + 8) = *(esi + 8)
0043e96d        void* eax_5 = *(esi + 8)
0043e972        if (eax_5 == 0)
0043e97f        *(ecx_5 + 4) = *(esi + 0xc)
0043e977        *(eax_5 + 0xc) = *(esi + 0xc)
0043e985        *(esi + 0xc) = *(ecx_5 + 8)
0043e988        *(ecx_5 + 8) = esi
0043e98e        int32_t eax_7
0043e98e        eax_7:1.b = (*(esi + 4)):1.b & 0xfd
0043e991        *(esi + 4) = eax_7
0043e956        report_errorf("List remove NEXTBOD")
0043e994        int32_t* esi_1 = esi + 0x90
0043e996        int32_t i_13 = 0xa
0043e9a6        int32_t eax_8
0043e9a6        int32_t i_1
0043e99d        eax_8 = kill_sprite(*esi_1)
0043e9a2        esi_1 = &esi_1[8]
0043e9a5        i_1 = i_13
0043e9a5        i_13 -= 1
0043e9a6        do while (i_1 != 1)
0043e9af        return eax_8
0043e9b0        eax = *(ecx_3 + 0x404)
0043e9be        if (eax s< *(esi + 0x8c))
0043e9c4        *(esi + 0x80) = 4
0043e9d6        case 2
0043e9d6        *(esi + 0x80) = 3
0043e9e0        *(esi + 0x1d4) = 0
0043e9ef        *(esi + 0x1d8) = fconvert.s(fconvert.t(eax[0xe]) * fconvert.t(0.0694444478f))
0043e9fb        label_43e9fb:
0043e9fb        int32_t i_11 = 0xa
0043ea00        int32_t* edi_4 = esi + 0x90
0043ea0d        int32_t i_2
0043ea04        update_ring_or_special_effect_particle(edi_4)
0043ea09        edi_4 = &edi_4[8]
0043ea0c        i_2 = i_11
0043ea0c        i_11 -= 1
0043ea0d        do while (i_2 != 1)
0043ea15        long double x87_r7_12 = fconvert.t(*(esi + 0x1d8)) + fconvert.t(*(esi + 0x1d4))
0043ea1b        *(esi + 0x1d4) = fconvert.s(x87_r7_12)
0043ea21        long double temp5 = fconvert.t(1f)
0043ea21        x87_r7_12 - temp5
0043ea2c        if ((((x87_r7_12 < temp5 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp5) ? 1 : 0) << 0xa | (x87_r7_12 == temp5 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043eac8        int32_t i_9 = 0xa
0043eacd        float* eax_17 = *(esi + 0x84) + 0x2964
0043eae7        float* ecx_13 = esi + 0xac
0043eb19        float var_14_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(eax_17[1]) - fconvert.t(*(esi + 0x6c)))) * fconvert.t(0.939999998f))
0043eb27        float var_10_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(eax_17[2]) + fconvert.t(0.200000003f))) - fconvert.t(*(esi + 0x70)))) * fconvert.t(0.939999998f))
0043eb2d        *(esi + 0x68) = fconvert.s((fconvert.t(*eax_17) - fconvert.t(*(esi + 0x68))) * fconvert.t(0.939999998f) + fconvert.t(*(esi + 0x68)))
0043eb36        *(esi + 0x6c) = fconvert.s(fconvert.t(var_14_1) + fconvert.t(*(esi + 0x6c)))
0043eb40        *(esi + 0x70) = fconvert.s(fconvert.t(var_10_1) + fconvert.t(*(esi + 0x70)))
0043eb67        int32_t i_3
0043eb45        long double x87_r7_22 = fconvert.t(*ecx_13) * fconvert.t(0.939999998f)
0043eb4d        float* esi_3 = &ecx_13[-5]
0043eb50        ecx_13 = &ecx_13[8]
0043eb53        i_3 = i_9
0043eb53        i_9 -= 1
0043eb54        ecx_13[-8] = fconvert.s(x87_r7_22)
0043eb59        *esi_3 = *(esi + 0x68)
0043eb5e        esi_3[1] = *(esi + 0x6c)
0043eb64        esi_3[2] = *(esi + 0x70)
0043eb67        do while (i_3 != 1)
0043eb70        return esi + 0x68
0043ea32        int16_t eax_10 = (*(esi + 4)).w
0043ea35        *(esi + 0x80) = 0
0043ea45        void* ecx_10 = data_4df904 + 0x5a8
0043ea4e        if ((eax_10:1.b & 2) == 0)
0043ea55        report_errorf("List remove")
0043ea61        if ((eax_10.b & 0x40) == 0)
0043ea72        void* eax_11 = *(esi + 0xc)
0043ea77        if (eax_11 != 0)
0043ea7c        *(eax_11 + 8) = *(esi + 8)
0043ea7f        void* eax_12 = *(esi + 8)
0043ea84        if (eax_12 == 0)
0043ea91        *(ecx_10 + 4) = *(esi + 0xc)
0043ea89        *(eax_12 + 0xc) = *(esi + 0xc)
0043ea97        *(esi + 0xc) = *(ecx_10 + 8)
0043ea9a        *(ecx_10 + 8) = esi
0043eaa0        int32_t eax_14
0043eaa0        eax_14:1.b = (*(esi + 4)):1.b & 0xfd
0043eaa3        *(esi + 4) = eax_14
0043ea68        report_errorf("List remove NEXTBOD")
0043eaa6        int32_t* esi_2 = esi + 0x90
0043eaa8        int32_t i_14 = 0xa
0043eab8        int32_t eax_15
0043eab8        int32_t i_4
0043eaaf        eax_15 = kill_sprite(*esi_2)
0043eab4        esi_2 = &esi_2[8]
0043eab7        i_4 = i_14
0043eab7        i_14 -= 1
0043eab8        do while (i_4 != 1)
0043eac1        return eax_15
0043e879        case 3
0043e879        goto label_43e9fb
0043eb71        case 4
0043eb71        *(esi + 0x80) = 5
0043eb7b        *(esi + 0x1d4) = 0
0043eb8a        *(esi + 0x1d8) = fconvert.s(fconvert.t(eax[0xe]) * fconvert.t(0.0694444478f))
0043eb96        label_43eb96:
0043eb96        int32_t i_12 = 0xa
0043eb9b        int32_t* edi_7 = esi + 0x90
0043eba8        int32_t i_5
0043eb9f        update_ring_or_special_effect_particle(edi_7)
0043eba4        edi_7 = &edi_7[8]
0043eba7        i_5 = i_12
0043eba7        i_12 -= 1
0043eba8        do while (i_5 != 1)
0043ebb0        long double x87_r7_26 = fconvert.t(*(esi + 0x1d8)) + fconvert.t(*(esi + 0x1d4))
0043ebb6        *(esi + 0x1d4) = fconvert.s(x87_r7_26)
0043ebbc        long double temp6_1 = fconvert.t(1f)
0043ebbc        x87_r7_26 - temp6_1
0043ebc7        if ((((x87_r7_26 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp6_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043ebcd        int16_t eax_20 = (*(esi + 4)).w
0043ebd0        *(esi + 0x80) = 0
0043ebe3        void* ecx_15 = data_4df904 + 0x5a8
0043ebe9        if ((eax_20:1.b & 2) == 0)
0043ebf0        report_errorf("List remove")
0043ebfc        if ((eax_20.b & 0x40) == 0)
0043ec0d        void* eax_21 = *(esi + 0xc)
0043ec12        if (eax_21 != 0)
0043ec17        *(eax_21 + 8) = *(esi + 8)
0043ec1a        void* eax_22 = *(esi + 8)
0043ec1f        if (eax_22 == 0)
0043ec2c        *(ecx_15 + 4) = *(esi + 0xc)
0043ec24        *(eax_22 + 0xc) = *(esi + 0xc)
0043ec32        *(esi + 0xc) = *(ecx_15 + 8)
0043ec35        *(ecx_15 + 8) = esi
0043ec3b        int32_t eax_24
0043ec3b        eax_24:1.b = (*(esi + 4)):1.b & 0xfd
0043ec3e        *(esi + 4) = eax_24
0043ec03        report_errorf("List remove NEXTBOD")
0043ec41        int32_t* esi_4 = esi + 0x90
0043ec43        int32_t i_15 = 0xa
0043ec53        int32_t eax_25
0043ec53        int32_t i_6
0043ec4a        eax_25 = kill_sprite(*esi_4)
0043ec4f        esi_4 = &esi_4[8]
0043ec52        i_6 = i_15
0043ec52        i_15 -= 1
0043ec53        do while (i_6 != 1)
0043ec5c        return eax_25
0043ec60        eax = esi + 0xac
0043ec66        int32_t i_8 = 0xa
0043ec8f        int32_t i_7
0043ec6d        long double x87_r7_28 = fconvert.t(*eax) * fconvert.t(1.10000002f)
0043ec75        int32_t* esi_5 = &eax[-5]
0043ec78        eax = &eax[8]
0043ec7b        i_7 = i_8
0043ec7b        i_8 -= 1
0043ec7c        eax[-8] = fconvert.s(x87_r7_28)
0043ec81        *esi_5 = *(esi + 0x68)
0043ec86        esi_5[1] = *(esi + 0x6c)
0043ec8c        esi_5[2] = *(esi + 0x70)
0043ec8f        do while (i_7 != 1)
0043e879        case 5
0043e879        goto label_43eb96
0043ec98        return eax
