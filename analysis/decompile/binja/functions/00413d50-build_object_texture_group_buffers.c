/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_object_texture_group_buffers @ 0x413d50 */

00413d54        void* ebx = arg1
00413d5a        int32_t eax = *(ebx + 0x2c)
00413d5d        int32_t edi = 0
00413d61        if (eax == 0)
00413d63        *(ebx + 0xcc) = 0
00413d69        *(ebx + 0xd0) = 0
00413d6f        *(ebx + 0xd4) = 0
00413d75        *(ebx + 0xc0) = 0
00413d7b        *(ebx + 0xc8) = 0
00413d87        return eax
00413d96        *(ebx + 0x10) |= 0x80000
00413da0        void* eax_5 = allocate_tracked_memory(*(ebx + 0x64) << 2, "DX TextureGroups")
00413dad        int32_t ecx_1 = *(ebx + 0x64) << 2
00413db1        *(ebx + 0xcc) = eax_5
00413db7        void* eax_6 = allocate_tracked_memory(ecx_1, "DX TextureGroupsTexture Ref")
00413dc4        int32_t edx_1 = *(ebx + 0x64) << 2
00413dc8        *(ebx + 0xd0) = eax_6
00413dd6        *(ebx + 0xd4) = allocate_tracked_memory(edx_1, "DX TextureGroupsTexture Primcount")
00413de1        data_5031c4 = get_archive_data_base()
00413deb        int32_t var_8 = get_archive_data_end()
00413def        data_5031bc = 0
00413df5        int32_t eax_9
00413df5        eax_9.b = *(ebx + 0x10)
00413df8        int32_t ecx_2 = 0
00413dfa        void* ebp = nullptr
00413dfc        int32_t var_14 = 0
00413e02        arg1 = nullptr
00413e06        if ((eax_9.b & 4) != 0)
00413e0f        int32_t i = 0
00413e13        if (*(ebx + 0x2c) s> 0)
00413e1c        int32_t var_c_1 = 0
00413e22        if (*(ebx + 0x54) s> 0)
00413e94        bool cond:4_1
00413e29        char* eax_13 = *(ebx + 0x5c) + edi
00413e2b        int32_t ecx_3
00413e2b        ecx_3.w = *(eax_13 + 2)
00413e31        if (ecx_3 != i)
00413e3e        int32_t ecx_4
00413e3e        ecx_4.w = *(eax_13 + 4)
00413e44        if (ecx_4 != i)
00413e51        int32_t ecx_5
00413e51        ecx_5.w = *(eax_13 + 6)
00413e57        if (ecx_5 == i)
00413e7b        get_or_append_object_texture_group_vertex(ebx, i, *(eax_13 + 0x20), *(eax_13 + 0x24))
00413e65        if ((*eax_13 & 0x80) == 0)
00413e69        int32_t ecx_6
00413e69        ecx_6.w = *(eax_13 + 8)
00413e6f        if (ecx_6 == i)
00413e7b        get_or_append_object_texture_group_vertex(ebx, i, *(eax_13 + 0x28), *(eax_13 + 0x2c))
00413e7b        get_or_append_object_texture_group_vertex(ebx, i, *(eax_13 + 0x18), *(eax_13 + 0x1c))
00413e7b        get_or_append_object_texture_group_vertex(ebx, i, *(eax_13 + 0x10), *(eax_13 + 0x14))
00413e8b        edi += 0x30
00413e8e        cond:4_1 = var_c_1 + 1 s< *(ebx + 0x54)
00413e90        var_c_1 += 1
00413e94        do while (cond:4_1)
00413e96        ecx_2 = 0
00413e9a        edi = 0
00413e9f        i += 1
00413ea2        do while (i s< *(ebx + 0x2c))
00413eab        int32_t eax_18 = 0
00413eaf        int32_t var_c_2 = 0
00413eb3        if (*(ebx + 0x64) s> 0)
00413eca        while (true)
00413eca        int32_t var_1c_1 = 0
00413ed1        int32_t edi_2 = ecx_2 * 0x30
00413ed8        *(*(ebx + 0xd0) + (eax_18 << 2)) = *(edi_2 + *(ebx + 0x5c) + 0xc)
00413ee1        *(*(ebx + 0xcc) + (eax_18 << 2)) = ebp
00413eea        if (ecx_2 s< *(*(ebx + 0x6c) + (eax_18 << 2)))
00413ef8        int16_t* esi_2 = var_8 + (ebp << 1)
00413efb        int16_t* var_18_1 = var_8 + (ebp << 1) + 0xa
00413f03        int16_t* ebp_1 = var_8 + (ebp << 1) + 4
00413f0d        int16_t* var_20_1 = var_8 + (ebp << 1) + 8
00413f19        int16_t* var_24_1 = var_8 + (arg1 << 1) + 6
00413f1d        int16_t* var_28_1 = var_8 + (arg1 << 1) + 2
00414062        bool cond:3_1
00413f21        int32_t ecx_10 = *(ebx + 0x5c)
00413f28        void* eax_22 = edi_2 + ecx_10
00413f31        int32_t edx_14
00413f31        edx_14.w = *(eax_22 + 2)
00413f3d        *esi_2 = get_or_append_object_texture_group_vertex(ebx, edx_14, *(eax_22 + 0x10), *(edi_2 + ecx_10 + 0x14))
00413f43        void* eax_25 = *(ebx + 0x5c) + edi_2
00413f4e        int32_t ecx_13
00413f4e        ecx_13.w = *(eax_25 + 4)
00413f5e        *var_28_1 = get_or_append_object_texture_group_vertex(ebx, ecx_13, *(eax_25 + 0x18), *(eax_25 + 0x1c))
00413f64        void* eax_28 = *(ebx + 0x5c) + edi_2
00413f6f        int32_t ecx_15
00413f6f        ecx_15.w = *(eax_28 + 6)
00413f7b        *ebp_1 = get_or_append_object_texture_group_vertex(ebx, ecx_15, *(eax_28 + 0x20), *(eax_28 + 0x24))
00413f89        int32_t eax_36
00413f89        if ((*(edi_2 + *(ebx + 0x5c)) & 0x80) != 0)
00414016        arg1 += 3
00414021        esi_2 = &esi_2[3]
00414023        var_28_1 = &var_28_1[3]
0041402d        ebp_1 = &ebp_1[3]
0041402f        var_24_1 = &var_24_1[3]
0041403f        var_20_1 = &var_20_1[3]
00414043        var_18_1 = &var_18_1[3]
00414047        eax_36 = var_1c_1 + 1
00413f92        *var_24_1 = *esi_2
00413f99        int32_t edx_18
00413f99        edx_18.w = *ebp_1
00413f9d        *var_20_1 = edx_18.w
00413fa0        int32_t ecx_17 = *(ebx + 0x5c)
00413fa7        void* eax_31 = edi_2 + ecx_17
00413fb0        int32_t edx_20
00413fb0        edx_20.w = *(eax_31 + 8)
00413fc7        *var_18_1 = get_or_append_object_texture_group_vertex(ebx, edx_20, *(eax_31 + 0x28), *(edi_2 + ecx_17 + 0x2c))
00413fd1        arg1 += 6
00413fdc        esi_2 = &esi_2[6]
00413fde        var_28_1 = &var_28_1[6]
00413fe8        ebp_1 = &ebp_1[6]
00413fea        var_24_1 = &var_24_1[6]
00413ffa        var_20_1 = &var_20_1[6]
00413ffe        var_18_1 = &var_18_1[6]
00414002        eax_36 = var_1c_1 + 2
0041404f        var_1c_1 = eax_36
00414058        edi_2 += 0x30
0041405b        cond:3_1 = var_14 + 1 s< *(*(ebx + 0x6c) + (var_c_2 << 2))
0041405e        var_14 += 1
00414062        do while (cond:3_1)
00414068        ebp = arg1
0041406c        eax_18 = var_c_2
00414078        *(*(ebx + 0xd4) + (eax_18 << 2)) = var_1c_1
0041407e        eax_18 += 1
00414081        var_c_2 = eax_18
00414085        if (eax_18 s>= *(ebx + 0x64))
00414085        break
00413ebb        ecx_2 = var_14
00414097        *(ebx + 0xc4) = data_5031bc
004140b4        *(ebx + 0xc0) = sub_4114b0(0x4f7458, data_5031bc, 0x142)
004140ba        void* eax_44 = sub_4115d0(0x5000fc, ebp)
004140bf        void* edx_35 = *(ebx + 0xc0)
004140ca        *(ebx + 0xc8) = eax_44
004140d0        int32_t* eax_45 = *(edx_35 + 8)
004140e5        void* var_10
004140e5        (*(*eax_45 + 0x2c))(eax_45, 0, data_5031bc * 0x18, &var_10, 0)
004140ed        int32_t i_1 = 0
004140f1        if (data_5031bc s> 0)
004140f3        int32_t eax_47 = 0
004140f5        int32_t ecx_30 = 0
00414105        *(eax_47 + var_10 + 0xc) = *(ecx_30 + data_5031c4 + 0xc)
00414113        int32_t* esi_6 = ecx_30 + data_5031c4 + 0x10
00414119        *(eax_47 + var_10 + 0x10) = *esi_6
00414124        *(eax_47 + var_10 + 0x14) = esi_6[1]
00414132        int32_t* esi_9 = data_5031c4 + ecx_30
00414134        int32_t* edi_7 = var_10 + eax_47
00414136        i_1 += 1
00414139        ecx_30 += 0x1c
0041413c        *edi_7 = *esi_9
0041413e        eax_47 += 0x18
00414144        edi_7[1] = esi_9[1]
0041414a        edi_7[2] = esi_9[2]
00414155        do while (i_1 s< data_5031bc)
00414157        ebp = arg1
00414163        int32_t* eax_48 = *(*(ebx + 0xc0) + 8)
00414169        (*(*eax_48 + 0x30))(eax_48)
00414172        int32_t esi_12 = ebp * 2
00414177        int32_t* eax_49 = **(ebx + 0xc8)
00414183        int32_t var_4
00414183        (*(*eax_49 + 0x2c))(eax_49, 0, esi_12, &var_4, 0)
00414195        int32_t esi_14
00414195        int32_t edi_9
00414195        edi_9, esi_14 = __builtin_memcpy(var_4, var_8, esi_12 & 0xfffffffc)
0041419c        __builtin_memcpy(edi_9, esi_14, esi_12 & 3)
004141a4        int32_t* eax_51 = **(ebx + 0xc8)
004141a9        (*(*eax_51 + 0x30))(eax_51)
004141ac        void* eax_52 = *(ebx + 0x10)
004141b3        if ((eax_52:1.b & 0x40) != 0)
004141bb        eax_52 = sub_4115d0(0x5000fc, ebp)
004141c0        *(ebx + 0xd8) = eax_52
004141cc        return eax_52
