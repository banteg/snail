/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_track_fringe_objects @ 0x434be0 */

00434bea        void* ebp = arg1
00434bf2        void* var_50 = ebp
00434bf6        initialize_fringe_manager(data_4df904 + 0x3d01d4)
00434bfe        int32_t ebx = 0
00434c02        int32_t var_48 = 0
00434c06        if (*(ebp + 0x54) s> 0)
00434c0c        char* edx_1 = ebp + 0x5ccac8
00434c14        struct TrackRowCell* esi_1 = ebp + 0x3bfac8
00434c1a        char* var_44_1 = edx_1
0043514c        bool cond:2_1
00434c1e        int32_t var_4c_1 = 8
0043512e        bool cond:1_1
00434c26        void* const ecx
00434c26        ecx.b = esi_1->__offset(0x3d).b
00434c29        int32_t edi_1 = 0
00434c2e        if (ecx.b == 9)
00434c30        edi_1 = 1
00434c3a        if (ecx.b == 5)
00434c3c        edi_1 = 3
00434c46        if (ecx.b == 0xa)
00434c48        edi_1 = 2
00434c52        if (ecx.b == 6)
00434c54        edi_1 = 4
00434c59        int32_t eax_1
00434c59        eax_1.b = esi_1->__offset(0x3c).b
00434c66        if (eax_1.b == 2 || eax_1.b == 8 || eax_1.b == 5)
00434c68        edi_1 = 5
00434c83        if (eax_1.b == 3 || eax_1.b == 9 || eax_1.b == 0xb || eax_1.b == 0xc || eax_1.b == 0xd || eax_1.b == 6)
00434c85        edi_1 = 6
00434c94        if (eax_1.b == 4 || eax_1.b == 0xa || eax_1.b == 7)
00434c96        edi_1 = 7
00434cbb        if ((*edx_1 & 4) != 0 || ecx.b == 0 || eax_1.b == 0x20 || (data_4df934 & 0x20) == 0)
004350e0        esi_1->__offset(0x44).d = 0
004350e3        esi_1->__offset(0x48).d = 0
004350e6        esi_1->__offset(0x4c).d = 0
004350e9        esi_1->__offset(0x50).d = 0
00434cc6        char eax_2
00434cc6        eax_2, ecx = is_neighbor_cell_solid(ebp, esi_1, 0, 0)
00434ccd        if (eax_2 == 1)
00434ce0        if (is_neighbor_cell_solid(ebp, esi_1, 0, 1) != 0)
00434dd4        esi_1->__offset(0x44).d = 0
00434cf4        if (is_neighbor_cell_solid(ebp, esi_1, 1, 1) != 1)
00434d01        int32_t eax_5
00434d01        eax_5.b = is_neighbor_cell_solid(ebp, esi_1, 1, 0).b - 1
00434d03        char temp1_1 = eax_5.b
00434d03        eax_5.b = neg.b(eax_5.b)
00434d0a        ebx = neg.d(sbb.d(eax_5, eax_5, temp1_1 != 0)) + 1
00434d1a        int32_t ebp_1
00434d1a        if (is_neighbor_cell_solid(ebp, esi_1, 0xffffffff, 1) != 1)
00434d2c        int32_t eax_10
00434d2c        eax_10.b = is_neighbor_cell_solid(ebp, esi_1, 0xffffffff, 0).b - 1
00434d2e        char temp2_1 = eax_10.b
00434d2e        eax_10.b = neg.b(eax_10.b)
00434d35        ebp_1 = neg.d(sbb.d(eax_10, eax_10, temp2_1 != 0)) + 1
00434d1c        ebp_1 = 0
00434d43        void* eax_14 = allocate_fringe_object(data_4df904 + 0x3d01d4)
00434d4b        esi_1->__offset(0x44).d = eax_14
00434d70        set_bod_object(eax_14, *(data_4df904 + ((ebx + edi_1 * 0xc) * 3 + ebp_1) * 0x38 + 0x44dd4))
00434d75        void* eax_15 = esi_1->__offset(0x44).d
00434d81        *(eax_15 + 4) |= 0x20
00434d89        int32_t* eax_17 = esi_1->__offset(0x44).d + 0x10
00434d8c        *eax_17 = esi_1->__offset(0x10).d
00434d91        eax_17[1] = esi_1->__offset(0x14).d
00434d97        eax_17[2] = esi_1->__offset(0x18).d
00434dab        float var_40[0x4]
00434dab        float* eax_18 = get_track_skirt_color(data_4df904 + 0x74618, &var_40)
00434db5        float* edx_9 = esi_1->__offset(0x44).d + 0x28
00434db8        ebp = var_50
00434dbc        ebx = 0
00434dbe        *edx_9 = *eax_18
00434dc3        edx_9[1] = eax_18[1]
00434dc9        edx_9[2] = eax_18[2]
00434dcf        edx_9[3] = eax_18[3]
00434de4        if (is_neighbor_cell_solid(ebp, esi_1, 1, 0) != 0)
00434ed8        esi_1->__offset(0x48).d = 0
00434df8        if (is_neighbor_cell_solid(ebp, esi_1, 1, 0xffffffff) != 1)
00434e05        int32_t eax_22
00434e05        eax_22.b = is_neighbor_cell_solid(ebp, esi_1, 0, 0xffffffff).b - 1
00434e07        char temp3_1 = eax_22.b
00434e07        eax_22.b = neg.b(eax_22.b)
00434e0e        ebx = neg.d(sbb.d(eax_22, eax_22, temp3_1 != 0)) + 1
00434e1e        int32_t ebp_4
00434e1e        if (is_neighbor_cell_solid(ebp, esi_1, 1, 1) != 1)
00434e30        int32_t eax_27
00434e30        eax_27.b = is_neighbor_cell_solid(ebp, esi_1, 0, 1).b - 1
00434e32        char temp4_1 = eax_27.b
00434e32        eax_27.b = neg.b(eax_27.b)
00434e39        ebp_4 = neg.d(sbb.d(eax_27, eax_27, temp4_1 != 0)) + 1
00434e20        ebp_4 = 0
00434e47        void* eax_31 = allocate_fringe_object(data_4df904 + 0x3d01d4)
00434e4f        esi_1->__offset(0x48).d = eax_31
00434e74        set_bod_object(eax_31, *(data_4df904 + ((ebx + edi_1 * 0xc) * 3 + ebp_4) * 0x38 + 0x44fcc))
00434e79        void* eax_32 = esi_1->__offset(0x48).d
00434e85        *(eax_32 + 4) |= 0x20
00434e8d        int32_t* eax_34 = esi_1->__offset(0x48).d + 0x10
00434e90        *eax_34 = esi_1->__offset(0x10).d
00434e95        eax_34[1] = esi_1->__offset(0x14).d
00434e9b        eax_34[2] = esi_1->__offset(0x18).d
00434eaf        float var_30[0x4]
00434eaf        float* eax_35 = get_track_skirt_color(data_4df904 + 0x74618, &var_30)
00434eb9        float* edx_17 = esi_1->__offset(0x48).d + 0x28
00434ebc        ebp = var_50
00434ec0        ebx = 0
00434ec2        *edx_17 = *eax_35
00434ec7        edx_17[1] = eax_35[1]
00434ecd        edx_17[2] = eax_35[2]
00434ed3        edx_17[3] = eax_35[3]
00434ee8        if (is_neighbor_cell_solid(ebp, esi_1, 0xffffffff, 0) != 0)
00434fdc        esi_1->__offset(0x4c).d = 0
00434efc        if (is_neighbor_cell_solid(ebp, esi_1, 0xffffffff, 1) != 1)
00434f09        int32_t eax_39
00434f09        eax_39.b = is_neighbor_cell_solid(ebp, esi_1, 0, 1).b - 1
00434f0b        char temp5_1 = eax_39.b
00434f0b        eax_39.b = neg.b(eax_39.b)
00434f12        ebx = neg.d(sbb.d(eax_39, eax_39, temp5_1 != 0)) + 1
00434f22        int32_t ebp_7
00434f22        if (is_neighbor_cell_solid(ebp, esi_1, 0xffffffff, 0xffffffff) != 1)
00434f34        int32_t eax_44
00434f34        eax_44.b = is_neighbor_cell_solid(ebp, esi_1, 0, 0xffffffff).b - 1
00434f36        char temp6_1 = eax_44.b
00434f36        eax_44.b = neg.b(eax_44.b)
00434f3d        ebp_7 = neg.d(sbb.d(eax_44, eax_44, temp6_1 != 0)) + 1
00434f24        ebp_7 = 0
00434f4b        void* eax_48 = allocate_fringe_object(data_4df904 + 0x3d01d4)
00434f53        esi_1->__offset(0x4c).d = eax_48
00434f78        set_bod_object(eax_48, *(data_4df904 + ((ebx + edi_1 * 0xc) * 3 + ebp_7) * 0x38 + 0x451c4))
00434f7d        void* eax_49 = esi_1->__offset(0x4c).d
00434f89        *(eax_49 + 4) |= 0x20
00434f91        int32_t* eax_51 = esi_1->__offset(0x4c).d + 0x10
00434f94        *eax_51 = esi_1->__offset(0x10).d
00434f99        eax_51[1] = esi_1->__offset(0x14).d
00434f9f        eax_51[2] = esi_1->__offset(0x18).d
00434fb3        float var_20[0x4]
00434fb3        float* eax_52 = get_track_skirt_color(data_4df904 + 0x74618, &var_20)
00434fbd        float* edx_25 = esi_1->__offset(0x4c).d + 0x28
00434fc0        ebp = var_50
00434fc4        ebx = 0
00434fc6        *edx_25 = *eax_52
00434fcb        edx_25[1] = eax_52[1]
00434fd1        edx_25[2] = eax_52[2]
00434fd7        edx_25[3] = eax_52[3]
00434fe5        char eax_54
00434fe5        eax_54, ecx = is_neighbor_cell_solid(ebp, esi_1, 0, 0xffffffff)
00434fec        if (eax_54 != 0)
004350e9        esi_1->__offset(0x50).d = 0
00435000        if (is_neighbor_cell_solid(ebp, esi_1, 0xffffffff, 0xffffffff) != 1)
0043500d        int32_t eax_56
0043500d        eax_56.b = is_neighbor_cell_solid(ebp, esi_1, 0xffffffff, 0).b - 1
0043500f        char temp7_1 = eax_56.b
0043500f        eax_56.b = neg.b(eax_56.b)
00435016        ebx = neg.d(sbb.d(eax_56, eax_56, temp7_1 != 0)) + 1
00435026        int32_t ebp_10
00435026        if (is_neighbor_cell_solid(ebp, esi_1, 1, 0xffffffff) != 1)
00435038        int32_t eax_61
00435038        eax_61.b = is_neighbor_cell_solid(ebp, esi_1, 1, 0).b - 1
0043503a        char temp8_1 = eax_61.b
0043503a        eax_61.b = neg.b(eax_61.b)
00435041        ebp_10 = neg.d(sbb.d(eax_61, eax_61, temp8_1 != 0)) + 1
00435028        ebp_10 = 0
0043504f        void* eax_65 = allocate_fringe_object(data_4df904 + 0x3d01d4)
00435057        esi_1->__offset(0x50).d = eax_65
0043507c        set_bod_object(eax_65, *(data_4df904 + ((ebx + edi_1 * 0xc) * 3 + ebp_10) * 0x38 + 0x453bc))
00435081        void* eax_66 = esi_1->__offset(0x50).d
0043508d        *(eax_66 + 4) |= 0x20
00435095        int32_t* eax_68 = esi_1->__offset(0x50).d + 0x10
00435098        *eax_68 = *(esi_1 + 0x10)
0043509d        eax_68[1] = *(esi_1 + 0x14)
004350a3        eax_68[2] = *(esi_1 + 0x18)
004350b7        float var_10[0x4]
004350b7        float* eax_69 = get_track_skirt_color(data_4df904 + 0x74618, &var_10)
004350c1        float* edx_33 = esi_1->__offset(0x50).d + 0x28
004350c4        ebp = var_50
004350c8        ebx = 0
004350ca        *edx_33 = *eax_69
004350cf        edx_33[1] = eax_69[1]
004350d5        edx_33[2] = eax_69[2]
004350db        edx_33[3] = eax_69[3]
004350ec        edx_1 = var_44_1
004350f3        if ((*edx_1 & 4) != 0)
004350f5        void* eax_71 = esi_1->__offset(0x44).d
004350ff        if (eax_71 != 0)
00435101        *(eax_71 + 4) &= 0xffffffdf
00435104        void* eax_72 = esi_1->__offset(0x50).d
00435109        if (eax_72 != 0)
0043510b        *(eax_72 + 4) &= 0xffffffdf
0043510e        void* eax_73 = esi_1->__offset(0x48).d
00435113        if (eax_73 != 0)
00435115        *(eax_73 + 4) &= 0xffffffdf
00435118        void* eax_74 = esi_1->__offset(0x4c).d
0043511d        if (eax_74 != 0)
0043511f        *(eax_74 + 4) &= 0xffffffdf
00435126        esi_1 += 0x54
00435129        cond:1_1 = var_4c_1 != 1
0043512a        var_4c_1 -= 1
0043512e        do while (cond:1_1)
0043513c        edx_1 = &edx_1[0xf4]
00435142        cond:2_1 = var_48 + 1 s< *(ebp + 0x54)
00435144        var_48 += 1
00435148        var_44_1 = edx_1
0043514c        do while (cond:2_1)
00435160        int32_t __saved_esi = *(data_4df904 + 0x42fd14)
00435161        char* __saved_edi = "Used %i fringe bods\n"
00435173        return 0
