/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_ring_or_special_effect_parent @ 0x43e830 */

// *(arg1 + 0x1d0) is rate_source; byte +0x09 is subgame_pause_gate.
0043e839        float* eax = *(arg1 + 0x1d0)
0043e844        if (*(eax + 9) == 0)
0043e850        int32_t edi_2 = *(arg1 + 0x1e8) + 1
0043e853        *(arg1 + 0x1e8) = edi_2
0043e85c        if (edi_2 == 3)
0043e860        *(arg1 + 0x1e8) = 0
0043e879        switch (*(arg1 + 0x80))
0043e880        case 1
0043e880        int16_t eax_1
0043e880        eax_1.b = *(arg1 + 0x1dc)
0043e888        if (eax_1.b != 0)
0043e890        long double x87_r7_2 = fconvert.t(*(arg1 + 0x1e4)) + fconvert.t(*(arg1 + 0x1e0))
0043e896        long double temp0_1 = fconvert.t(6.28318548f)
0043e896        x87_r7_2 - temp0_1
0043e89c        *(arg1 + 0x1e0) = fconvert.s(x87_r7_2)
0043e89c        bool c1_1 = unimplemented  {fst dword [esi+0x1e0], st0}
0043e8a7        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
0043e8b7        long double temp4_1 = fconvert.t(0f)
0043e8b7        x87_r7_2 - temp4_1
0043e8c2        if ((((x87_r7_2 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp4_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp4_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0043e8ca        *(arg1 + 0x1e0) = fconvert.s(x87_r7_2 + fconvert.t(6.28318548f))
0043e8af        *(arg1 + 0x1e0) = fconvert.s(x87_r7_2 - fconvert.t(6.28318548f))
0043e8e9        *(arg1 + 0x68) = fconvert.s(sine(*(arg1 + 0x1e0)) * fconvert.t(3f))
0043e8f2        int32_t i_10 = 0xa
0043e8f7        struct RingOrSpecialEffectParticle* particle = arg1 + 0x90
0043e904        int32_t i
0043e8fb        update_ring_or_special_effect_particle(particle)
0043e900        particle = &particle[1]
0043e903        i = i_10
0043e903        i_10 -= 1
0043e904        do while (i != 1)
0043e906        void* ecx_4 = *(arg1 + 0x84)
0043e90c        long double x87_r7_8 = fconvert.t(*(arg1 + 0x70))
0043e90f        long double temp7_1 = fconvert.t(*(ecx_4 + 0x2980))
0043e90f        x87_r7_8 - temp7_1
0043e91a        if ((((x87_r7_8 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp7_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp7_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0043e920        int16_t eax_5 = (*(arg1 + 4)).w
0043e923        *(arg1 + 0x80) = 0
0043e933        void* ecx_6 = data_4df904 + 0x5a8
0043e93c        if ((eax_5:1.b & 2) == 0)
0043e943        report_errorf("List remove")
0043e94f        if ((eax_5.b & 0x40) == 0)
0043e960        void* eax_6 = *(arg1 + 0xc)
0043e965        if (eax_6 != 0)
0043e96a        *(eax_6 + 8) = *(arg1 + 8)
0043e96d        void* eax_7 = *(arg1 + 8)
0043e972        if (eax_7 == 0)
0043e97f        *(ecx_6 + 4) = *(arg1 + 0xc)
0043e977        *(eax_7 + 0xc) = *(arg1 + 0xc)
0043e985        *(arg1 + 0xc) = *(ecx_6 + 8)
0043e988        *(ecx_6 + 8) = arg1
0043e98b        int32_t eax_9 = *(arg1 + 4)
0043e98e        eax_9:1.b &= 0xfd
0043e991        *(arg1 + 4) = eax_9
0043e956        report_errorf("List remove NEXTBOD")
0043e994        struct RingOrSpecialEffectParticle* esi_1 = arg1 + 0x90
0043e996        int32_t i_13 = 0xa
0043e9a6        int32_t eax_10
0043e9a6        int32_t i_1
0043e99d        eax_10 = kill_sprite(esi_1->sprite)
0043e9a2        esi_1 = &esi_1[1]
0043e9a5        i_1 = i_13
0043e9a5        i_13 -= 1
0043e9a6        do while (i_1 != 1)
0043e9af        return eax_10
0043e9b0        eax = *(ecx_4 + 0x404)
0043e9be        if (eax s< *(arg1 + 0x8c))
0043e9c4        *(arg1 + 0x80) = 4
0043e9d6        case 2
0043e9d6        *(arg1 + 0x80) = 3
0043e9e0        *(arg1 + 0x1d4) = 0
0043e9ef        *(arg1 + 0x1d8) = fconvert.s(fconvert.t(eax[0xe]) * fconvert.t(0.0694444478f))
0043e9fb        label_43e9fb:
0043e9fb        int32_t i_11 = 0xa
0043ea00        struct RingOrSpecialEffectParticle* particle_1 = arg1 + 0x90
0043ea0d        int32_t i_2
0043ea04        update_ring_or_special_effect_particle(particle_1)
0043ea09        particle_1 = &particle_1[1]
0043ea0c        i_2 = i_11
0043ea0c        i_11 -= 1
0043ea0d        do while (i_2 != 1)
0043ea15        long double x87_r7_12 = fconvert.t(*(arg1 + 0x1d8)) + fconvert.t(*(arg1 + 0x1d4))
0043ea1b        *(arg1 + 0x1d4) = fconvert.s(x87_r7_12)
0043ea21        long double temp5 = fconvert.t(1f)
0043ea21        x87_r7_12 - temp5
0043ea2c        if ((((x87_r7_12 < temp5 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp5) ? 1 : 0) << 0xa | (x87_r7_12 == temp5 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043eac8        int32_t i_9 = 0xa
0043eacd        float* eax_20 = *(arg1 + 0x84) + 0x2964
0043eae7        float* ecx_14 = arg1 + 0xac
0043eb19        float var_14_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(eax_20[1]) - fconvert.t(*(arg1 + 0x6c)))) * fconvert.t(0.939999998f))
0043eb27        float var_10_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(eax_20[2]) + fconvert.t(0.200000003f))) - fconvert.t(*(arg1 + 0x70)))) * fconvert.t(0.939999998f))
0043eb2d        *(arg1 + 0x68) = fconvert.s((fconvert.t(*eax_20) - fconvert.t(*(arg1 + 0x68))) * fconvert.t(0.939999998f) + fconvert.t(*(arg1 + 0x68)))
0043eb36        *(arg1 + 0x6c) = fconvert.s(fconvert.t(var_14_1) + fconvert.t(*(arg1 + 0x6c)))
0043eb40        *(arg1 + 0x70) = fconvert.s(fconvert.t(var_10_1) + fconvert.t(*(arg1 + 0x70)))
0043eb67        int32_t i_3
0043eb45        long double x87_r7_22 = fconvert.t(*ecx_14) * fconvert.t(0.939999998f)
0043eb4d        float* esi_3 = &ecx_14[-5]
0043eb50        ecx_14 = &ecx_14[8]
0043eb53        i_3 = i_9
0043eb53        i_9 -= 1
0043eb54        ecx_14[-8] = fconvert.s(x87_r7_22)
0043eb59        *esi_3 = *(arg1 + 0x68)
0043eb5e        esi_3[1] = *(arg1 + 0x6c)
0043eb64        esi_3[2] = *(arg1 + 0x70)
0043eb67        do while (i_3 != 1)
0043eb70        return arg1 + 0x68
0043ea32        int16_t eax_13 = (*(arg1 + 4)).w
0043ea35        *(arg1 + 0x80) = 0
0043ea45        void* ecx_11 = data_4df904 + 0x5a8
0043ea4e        if ((eax_13:1.b & 2) == 0)
0043ea55        report_errorf("List remove")
0043ea61        if ((eax_13.b & 0x40) == 0)
0043ea72        void* eax_14 = *(arg1 + 0xc)
0043ea77        if (eax_14 != 0)
0043ea7c        *(eax_14 + 8) = *(arg1 + 8)
0043ea7f        void* eax_15 = *(arg1 + 8)
0043ea84        if (eax_15 == 0)
0043ea91        *(ecx_11 + 4) = *(arg1 + 0xc)
0043ea89        *(eax_15 + 0xc) = *(arg1 + 0xc)
0043ea97        *(arg1 + 0xc) = *(ecx_11 + 8)
0043ea9a        *(ecx_11 + 8) = arg1
0043ea9d        int32_t eax_17 = *(arg1 + 4)
0043eaa0        eax_17:1.b &= 0xfd
0043eaa3        *(arg1 + 4) = eax_17
0043ea68        report_errorf("List remove NEXTBOD")
0043eaa6        struct RingOrSpecialEffectParticle* esi_2 = arg1 + 0x90
0043eaa8        int32_t i_14 = 0xa
0043eab8        int32_t eax_18
0043eab8        int32_t i_4
0043eaaf        eax_18 = kill_sprite(esi_2->sprite)
0043eab4        esi_2 = &esi_2[1]
0043eab7        i_4 = i_14
0043eab7        i_14 -= 1
0043eab8        do while (i_4 != 1)
0043eac1        return eax_18
0043e879        case 3
0043e879        goto label_43e9fb
0043eb71        case 4
0043eb71        *(arg1 + 0x80) = 5
0043eb7b        *(arg1 + 0x1d4) = 0
0043eb8a        *(arg1 + 0x1d8) = fconvert.s(fconvert.t(eax[0xe]) * fconvert.t(0.0694444478f))
0043eb96        label_43eb96:
0043eb96        int32_t i_12 = 0xa
0043eb9b        struct RingOrSpecialEffectParticle* particle_2 = arg1 + 0x90
0043eba8        int32_t i_5
0043eb9f        update_ring_or_special_effect_particle(particle_2)
0043eba4        particle_2 = &particle_2[1]
0043eba7        i_5 = i_12
0043eba7        i_12 -= 1
0043eba8        do while (i_5 != 1)
0043ebb0        long double x87_r7_26 = fconvert.t(*(arg1 + 0x1d8)) + fconvert.t(*(arg1 + 0x1d4))
0043ebb6        *(arg1 + 0x1d4) = fconvert.s(x87_r7_26)
0043ebbc        long double temp6_1 = fconvert.t(1f)
0043ebbc        x87_r7_26 - temp6_1
0043ebc7        if ((((x87_r7_26 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp6_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043ebcd        int16_t eax_24 = (*(arg1 + 4)).w
0043ebd0        *(arg1 + 0x80) = 0
0043ebe3        void* ecx_16 = data_4df904 + 0x5a8
0043ebe9        if ((eax_24:1.b & 2) == 0)
0043ebf0        report_errorf("List remove")
0043ebfc        if ((eax_24.b & 0x40) == 0)
0043ec0d        void* eax_25 = *(arg1 + 0xc)
0043ec12        if (eax_25 != 0)
0043ec17        *(eax_25 + 8) = *(arg1 + 8)
0043ec1a        void* eax_26 = *(arg1 + 8)
0043ec1f        if (eax_26 == 0)
0043ec2c        *(ecx_16 + 4) = *(arg1 + 0xc)
0043ec24        *(eax_26 + 0xc) = *(arg1 + 0xc)
0043ec32        *(arg1 + 0xc) = *(ecx_16 + 8)
0043ec35        *(ecx_16 + 8) = arg1
0043ec38        int32_t eax_28 = *(arg1 + 4)
0043ec3b        eax_28:1.b &= 0xfd
0043ec3e        *(arg1 + 4) = eax_28
0043ec03        report_errorf("List remove NEXTBOD")
0043ec41        struct RingOrSpecialEffectParticle* esi_4 = arg1 + 0x90
0043ec43        int32_t i_15 = 0xa
0043ec53        int32_t eax_29
0043ec53        int32_t i_6
0043ec4a        eax_29 = kill_sprite(esi_4->sprite)
0043ec4f        esi_4 = &esi_4[1]
0043ec52        i_6 = i_15
0043ec52        i_15 -= 1
0043ec53        do while (i_6 != 1)
0043ec5c        return eax_29
0043ec60        eax = arg1 + 0xac
0043ec66        int32_t i_8 = 0xa
0043ec8f        int32_t i_7
0043ec6d        long double x87_r7_28 = fconvert.t(*eax) * fconvert.t(1.10000002f)
0043ec75        int32_t* esi_5 = &eax[-5]
0043ec78        eax = &eax[8]
0043ec7b        i_7 = i_8
0043ec7b        i_8 -= 1
0043ec7c        eax[-8] = fconvert.s(x87_r7_28)
0043ec81        *esi_5 = *(arg1 + 0x68)
0043ec86        esi_5[1] = *(arg1 + 0x6c)
0043ec8c        esi_5[2] = *(arg1 + 0x70)
0043ec8f        do while (i_7 != 1)
0043e879        case 5
0043e879        goto label_43eb96
0043ec98        return eax
