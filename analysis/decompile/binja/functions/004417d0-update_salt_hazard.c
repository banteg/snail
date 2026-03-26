/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_salt_hazard @ 0x4417d0 */

004417d6        void* esi = arg1
004417d9        int32_t eax = *(esi + 0x88)
004417df        arg1.b = *(eax + 9)
004417e4        if (arg1.b == 0)
004417ea        int32_t eax_1 = *(esi + 0x80)
004417f1        if (eax_1 == 1)
004418a0        long double x87_r7_2 = fconvert.t(*(esi + 0x9c)) + fconvert.t(*(esi + 0x98))
004418a6        *(esi + 0x98) = fconvert.s(x87_r7_2)
004418ac        long double temp1_1 = fconvert.t(1f)
004418ac        x87_r7_2 - temp1_1
004418b2        int32_t eax_2
004418b2        eax_2.w = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
004418b7        if ((eax_2:1.b & 0x41) == 0)
004418b9        *(esi + 0x80) = 2
004418ca        return eax_2
004418d7        (esi + 0x68)->x = fconvert.s(fconvert.t(*(esi + 0x8c)) + fconvert.t(*(esi + 0x68)))
004418e2        (esi + 0x68)->y = fconvert.s(fconvert.t(*(esi + 0x90)) + fconvert.t((esi + 0x68)->y))
004418ee        (esi + 0x68)->z = fconvert.s(fconvert.t(*(esi + 0x94)) + fconvert.t((esi + 0x68)->z))
004418f1        long double x87_r7_9 = fconvert.t(*(esi + 0x6c))
004418f4        long double temp3_1 = fconvert.t(0f)
004418f4        x87_r7_9 - temp3_1
004418fa        eax_2.w = (x87_r7_9 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp3_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp3_1 ? 1 : 0) << 0xe
004418ff        if ((eax_2:1.b & 1) != 0)
00441ac3        return deactivate_salt_hazard(esi)
0044190b        long double x87_r7_10 = fconvert.t(*(esi + 0x70))
0044190e        long double temp4_1 = fconvert.t(*(*(esi + 0x88) + 0x3be0e4))
0044190e        x87_r7_10 - temp4_1
00441914        void* eax_8
00441914        eax_8.w = (x87_r7_10 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp4_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp4_1 ? 1 : 0) << 0xe
00441919        if ((eax_8:1.b & 1) != 0)
00441ac3        return deactivate_salt_hazard(esi)
0044192c        struct TrackRowCell* eax_9 = get_track_grid_cell_at_world_position(data_4df904 + 0x74618, esi + 0x68)
00441945        int32_t ebx_1 = get_track_runtime_cell_at_world_z(data_4df904 + 0x74618, esi + 0x68)
00441947        eax.b = eax_9->tile_id
0044194c        if (eax.b == 0xe)
0044194e        long double x87_r7_11 = fconvert.t(*(esi + 0x6c))
00441951        long double temp5_1 = fconvert.t(7f)
00441951        x87_r7_11 - temp5_1
00441957        eax.w = (x87_r7_11 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp5_1) ? 1 : 0) << 0xa | (x87_r7_11 == temp5_1 ? 1 : 0) << 0xe
0044195c        if ((eax:1.b & 1) != 0)
00441ac3        return deactivate_salt_hazard(esi)
00441965        if ((*ebx_1 & 0x40) != 0)
00441977        void* eax_10 = *(ebx_1 + 0xa4)
0044197d        void* var_2c_3 = eax_10
004419b0        float var_34_1 = fconvert.s(fconvert.t(*(esi + 0x90)) * fconvert.t(1.04999995f))
004419c3        float var_30_1 = fconvert.s(fconvert.t(*(esi + 0x94)) * fconvert.t(1.04999995f))
004419fd        eax = is_point_inside_track_attachment(*(eax_10 + 0x38), fconvert.s(fconvert.t(*(esi + 0x8c)) + fconvert.t((esi + 0x68)->x)), fconvert.s(fconvert.t(*(esi + 0x90)) + fconvert.t((esi + 0x68)->y)), fconvert.s(fconvert.t(*(esi + 0x94)) + fconvert.t((esi + 0x68)->z)), fconvert.s(fconvert.t(*(esi + 0x8c)) * fconvert.t(1.04999995f)))
00441a04        if ((*ebx_1 & 0x40) != 0 && eax.b != 0)
00441a06        char* var_2c_4 = "lazer path kill\n"
00441ac3        return deactivate_salt_hazard(esi)
00441a13        if ((*ebx_1 & 0x80) != 0)
00441a25        void* ebx_2 = *(ebx_1 + 0xa8)
00441a2b        void* var_2c_5 = ebx_2
00441a5e        float var_34_2 = fconvert.s(fconvert.t(*(esi + 0x90)) * fconvert.t(1.04999995f))
00441a73        float var_30_2 = fconvert.s(fconvert.t(*(esi + 0x94)) * fconvert.t(1.04999995f))
00441aab        eax = is_point_inside_track_attachment(*(ebx_2 + 0x38), fconvert.s(fconvert.t(*(esi + 0x8c)) + fconvert.t((esi + 0x68)->x)), fconvert.s(fconvert.t(*(esi + 0x90)) + fconvert.t((esi + 0x68)->y)), fconvert.s(fconvert.t(*(esi + 0x94)) + fconvert.t((esi + 0x68)->z)), fconvert.s(fconvert.t(*(esi + 0x8c)) * fconvert.t(1.04999995f)))
00441ab2        if (eax.b != 0)
00441ab4        char* var_2c_6 = "lazer path2 kill\n"
00441ac3        return deactivate_salt_hazard(esi)
004417f7        eax = eax_1 - 2
004417f8        if (eax_1 == 2)
00441804        int16_t eax_3 = (*(esi + 4)).w
00441807        void* ecx_1 = data_4df904 + 0x5a8
00441810        if ((eax_3:1.b & 2) == 0)
00441817        report_errorf("List remove")
0044181f        *(esi + 0x80) = 0
00441830        return 0
00441833        if ((eax_3.b & 0x40) != 0)
0044183a        report_errorf("List remove NEXTBOD")
00441842        *(esi + 0x80) = 0
00441853        return 0
00441854        void* eax_4 = *(esi + 0xc)
00441859        if (eax_4 != 0)
0044185e        *(eax_4 + 8) = *(esi + 8)
00441861        void* eax_5 = *(esi + 8)
00441866        if (eax_5 == 0)
00441873        *(ecx_1 + 4) = *(esi + 0xc)
0044186b        *(eax_5 + 0xc) = *(esi + 0xc)
00441879        *(esi + 0xc) = *(ecx_1 + 8)
0044187c        *(ecx_1 + 8) = esi
0044187f        int32_t eax_7 = *(esi + 4)
00441882        *(esi + 0x80) = 0
0044188c        eax_7:1.b &= 0xfd
0044188f        *(esi + 4) = eax_7
00441899        return eax_7
00441acf        return eax
