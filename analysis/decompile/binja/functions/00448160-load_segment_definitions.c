/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_segment_definitions @ 0x448160 */

00448165        int32_t* ecx = sub_48bf30(0x114e0)
00448189        *ecx = 0
0044818b        void arg_14e0
0044818b        enumerate_matching_archive_or_fs_entries("Segments", "*.txt", ecx, &arg_14e0)
00448190        int32_t eax = *ecx
0044819a        if (eax s>= 0x96)
004481a1        report_errorf("Too many Segments increase RSMTRACK_SEGMENT_MAX")
004481b3        return 0
004481b4        int32_t ebp = 0
004481b8        int32_t arg_10 = 0
004481bc        if (eax s<= 0)
004488f0        return eax
004481c2        void* edi_1 = &arg_14e0
004481cf        int32_t arg_18 = 0
004481d3        int32_t arg_14 = 0
004481d7        void* arg_8 = &arg_14e0
004481db        int32_t* arg_4 = &ecx[0x22]
004481f3        int32_t __saved_edi
004481f3        while (true)
004481f3        char arg_4e0[0x1000]
004481f3        char (* var_14_1)[0x1000] = &arg_4e0
004481f4        void* var_18_1 = edi_1
004481fb        char arg_2e0[0x200]
004481fb        sub_48b32c(&arg_2e0, "Segments/%s")
00448211        load_file_bytes_from_archive_or_fs(&arg_2e0, &arg_4e0, nullptr)
00448223        char* eax_1
00448223        int32_t ecx_1
00448223        eax_1, ecx_1 = find_case_insensitive_substring("ID:", &arg_4e0)
0044822d        if (eax_1 == 0)
00448808        void* var_14_28 = &(&__saved_edi)[ebp * 0x20 + 0x53c]
0044880e        report_errorf("Cannot find ID: in Segment %s\n")
00448820        return 0
00448233        ecx_1.b = eax_1[3]
00448236        char* eax_2 = &eax_1[3]
00448239        int32_t edx_1 = 0
0044823e        if (ecx_1.b s>= 0x30)
00448243        while (ecx_1.b s<= 0x39)
0044824b        eax_2 = &eax_2[1]
0044824c        edx_1 = sx.d(ecx_1.b) + edx_1 * 0xa - 0x30
00448250        ecx_1.b = *eax_2
00448255        if (ecx_1.b s< 0x30)
00448255        break
0044825b        void* var_14_2 = edi_1
00448265        arg_4[-1] = edx_1
00448268        sub_48b32c(&arg_4[-0x11], "%s")
0044827a        char* eax_4 = find_case_insensitive_substring("Name:'", &arg_4e0)
00448284        if (eax_4 == 0)
0044882b        void* var_14_29 = &(&__saved_edi)[ebp * 0x20 + 0x53c]
00448831        report_errorf("Cannot find Name: in Segment %s\n")
00448843        return 0
00448290        char* eax_5 = find_case_insensitive_substring("'", eax_4)
00448295        char i = eax_5[1]
0044829b        void* eax_6 = &eax_5[1]
0044829f        if (i != 0x27)
004482a3        char* edx_3 = &arg_4[-0x11] - eax_6 - 0x40
004482a6        *(edx_3 + eax_6) = i
004482a9        i = *(eax_6 + 1)
004482ac        eax_6 += 1
004482b0        do while (i != 0x27)
004482bf        char* eax_7 = find_case_insensitive_substring("Data:", &arg_4e0)
004482c9        if (eax_7 == 0)
0044884e        void* var_14_30 = &(&__saved_edi)[ebp * 0x20 + 0x53c]
00448854        report_errorf("Cannot find Data: in Segment %s\n")
00448866        return 0
004482d0        char* eax_8 = sub_44e690(eax_7)
004482da        if (eax_8 == 0)
00448871        void* var_14_31 = &(&__saved_edi)[ebp * 0x20 + 0x53c]
004488de        return report_errorf("Unexpected end of file in Segment %s\n")
004482e6        char* edi_2 = sub_44e690(eax_8)
004482ed        void* eax_46
004482ed        if (edi_2 == 0)
00448877        eax_46 = &(&__saved_edi)[ebp * 0x20 + 0x53c]
004488d8        label_4488d8:
004488d8        void* var_14_34 = eax_46
004488de        return report_errorf("Unexpected end of file in Segment %s\n")
004482f6        if (*edi_2 != 0x40)
004482f6        break
00448300        int32_t arg_1c = 0
00448304        *arg_4 = 0
00448315        while (true)
00448315        if (*edi_2 == 0x40 && edi_2[1] == 0x40 && edi_2[2] == 0x40)
004487be        ebp += 1
004487bf        arg_18 += 0x127
004487d3        int32_t eax_44 = *ecx
004487dd        arg_10 = ebp
004487e1        arg_14 += 0x811
004487e5        arg_4 = &arg_4[0x1022]
004487e9        arg_8 += 0x80
004487ed        if (ebp s>= eax_44)
004487fd        return eax_44
004481e1        edi_1 = arg_8
004481e1        break
00448324        int32_t ebp_1 = sx.d(arg_1c.w) + arg_18
00448334        char* edi_3 = &edi_2[1]
00448335        void* esi_4 = &ecx[ebp_1 * 0xe]
00448338        int32_t i_1 = 0
0044833a        *(esi_4 + 0x88c) = 0
0044834c        int32_t ebx_1
0044834c        ebx_1.b = *edi_3
0044834e        edi_3 = &edi_3[1]
0044834f        int32_t edx_8 = i_1 + ((*arg_4 + arg_14) << 3)
00448352        i_1 += 1
00448356        *(edx_8 + ecx + 0x8c) = ebx_1.b
0044835d        do while (i_1 s< 8)
00448362        if (*edi_3 != 0x40)
004488b1        void* var_14_33 = &(&__saved_edi)[arg_10 * 0x20 + 0x53c]
004488b7        report_errorf("Data line must end with '@' in Segment %s\n")
004488c9        return 0
0044836f        char* edi_4 = &edi_3[1]
00448370        *arg_4 += 1
00448375        int32_t* eax_13
00448375        if (*edi_4 == 0x2a)
0044837d        eax_13.b = (*(esi_4 + 0x88c)).b | 4
0044837f        *(esi_4 + 0x88c) = eax_13
00448385        eax_13.b = *edi_4
00448387        void arg_60
00448387        char* ecx_4 = &arg_60
0044838d        while (eax_13.b != 0xd)
0044838f        *ecx_4 = eax_13.b
00448391        eax_13.b = edi_4[1]
00448394        ecx_4 = &ecx_4[1]
00448395        edi_4 = &edi_4[1]
004483a6        *ecx_4 = 0
004483a8        char* __return_addr_1 = find_case_insensitive_substring("3DModel=", &arg_60)
004483b2        __return_addr = __return_addr_1
004483b6        if (__return_addr_1 != 0)
004483ca        char* __return_addr_2 = &find_case_insensitive_substring("=", __return_addr_1)[1]
004483cb        __return_addr = __return_addr_2
004483cf        void arg_260
004483cf        char* ecx_5 = &arg_260
004483d6        char i_2 = *__return_addr_2
004483db        while (i_2 != 0x2e)
004483dd        *ecx_5 = i_2
004483df        ecx_5 = &ecx_5[1]
004483e0        __return_addr_2 = &__return_addr_2[1]
004483e1        __return_addr = __return_addr_2
004483e5        i_2 = *__return_addr_2
004483ec        int32_t eax_15 = *(esi_4 + 0x88c)
004483f2        *ecx_5 = 0x2e
004483f6        eax_15.b |= 2
004483f8        *(esi_4 + 0x88c) = eax_15
004483fe        void* edx_11 = data_4df904
00448404        ecx_5[1] = 0x78
00448407        ecx_5[2] = 0
0044841d        *(esi_4 + 0x8a0) = load_or_reuse_cached_x_mesh(edx_11 + 0x48e00, &arg_260)
00448436        __return_addr = find_case_insensitive_substring("(", __return_addr)
00448440        *(esi_4 + 0x8a4) = fconvert.s(parse_next_float32(&__return_addr))
00448450        *(esi_4 + 0x8a8) = fconvert.s(parse_next_float32(&__return_addr))
00448460        *(esi_4 + 0x8ac) = fconvert.s(parse_next_float32(&__return_addr))
00448473        char* __return_addr_3 = find_case_insensitive_substring("Velocity=", &arg_60)
0044847d        __return_addr = __return_addr_3
00448481        if (__return_addr_3 != 0)
00448489        char* eax_19 = find_case_insensitive_substring("=", __return_addr_3)
00448495        int32_t edx_13 = *(esi_4 + 0x88c) | 8
0044849e        __return_addr = &eax_19[1]
004484a2        *(esi_4 + 0x88c) = edx_13
004484b1        __return_addr = find_case_insensitive_substring("(", &eax_19[1])
004484bb        *(esi_4 + 0x8b0) = fconvert.s(parse_next_float32(&__return_addr))
004484cb        *(esi_4 + 0x8b4) = fconvert.s(parse_next_float32(&__return_addr))
004484db        *(esi_4 + 0x8b8) = fconvert.s(parse_next_float32(&__return_addr))
004484ee        char* __return_addr_4 = find_case_insensitive_substring("Parcel=", &arg_60)
004484f8        __return_addr = __return_addr_4
004484fc        if (__return_addr_4 != 0)
0044850d        *(esi_4 + 0x88c) |= 1
00448519        __return_addr = &find_case_insensitive_substring("=", __return_addr_4)[1]
00448522        int32_t eax_24 = sub_44e710(&__return_addr)
00448527        void* const __return_addr_15 = __return_addr
0044852b        *(esi_4 + 0x890) = eax_24
00448542        __return_addr = &find_case_insensitive_substring("(", __return_addr_15)[1]
0044854b        *(esi_4 + 0x894) = fconvert.s(parse_next_float32(&__return_addr))
0044855b        *(esi_4 + 0x898) = fconvert.s(parse_next_float32(&__return_addr))
0044856b        *(esi_4 + 0x89c) = fconvert.s(parse_next_float32(&__return_addr))
0044857e        char* __return_addr_5 = find_case_insensitive_substring("Path=", &arg_60)
00448588        __return_addr = __return_addr_5
0044858c        if (__return_addr_5 != 0)
0044859c        char* __return_addr_6 = &find_case_insensitive_substring("=", __return_addr_5)[1]
0044859d        __return_addr = __return_addr_6
004485a1        void arg_20
004485a1        char* edx_16 = &arg_20
004485a5        char i_3 = *__return_addr_6
004485aa        while (i_3 s>= 0x20)
004485ac        *edx_16 = i_3
004485ae        edx_16 = &edx_16[1]
004485af        __return_addr_6 = &__return_addr_6[1]
004485b0        __return_addr = __return_addr_6
004485b4        i_3 = *__return_addr_6
004485bb        data_4df904
004485cc        *edx_16 = 0
004485ce        int32_t eax_28 = find_segment_path_index_by_name(&arg_20)
004485d6        *(esi_4 + 0x8bc) = eax_28
004485dc        if (eax_28 != 0xffffffff)
004485fd        int32_t eax_29
004485fd        eax_29.b = (*(esi_4 + 0x88c)).b | 8
004485ff        *(esi_4 + 0x88c) = eax_29
004485e6        void* var_14_17 = arg_8
004485e7        void* var_18_2 = &arg_20
004485ed        report_errorf("Unknown path %s in %s")
0044860f        char* __return_addr_7 = find_case_insensitive_substring("NoFall", &arg_60)
00448619        __return_addr = __return_addr_7
0044861d        if (__return_addr_7 != 0)
00448625        int32_t eax_30
00448625        eax_30:1.b = (*(esi_4 + 0x88c)):1.b | 1
00448628        *(esi_4 + 0x88c) = eax_30
00448638        char* __return_addr_8 = find_case_insensitive_substring("Ring=None", &arg_60)
00448642        __return_addr = __return_addr_8
00448646        if (__return_addr_8 != 0)
0044864e        int32_t eax_31
0044864e        eax_31:1.b = (*(esi_4 + 0x88c)):1.b | 2
00448651        *(esi_4 + 0x88c) = eax_31
00448661        char* __return_addr_9 = find_case_insensitive_substring("Ring=Normal", &arg_60)
0044866b        __return_addr = __return_addr_9
0044866f        if (__return_addr_9 != 0)
00448677        int32_t eax_32
00448677        eax_32:1.b = (*(esi_4 + 0x88c)):1.b | 4
0044867a        *(esi_4 + 0x88c) = eax_32
0044868a        char* __return_addr_10 = find_case_insensitive_substring("Ring=PowerUp", &arg_60)
00448694        __return_addr = __return_addr_10
00448698        if (__return_addr_10 != 0)
004486a0        int32_t eax_33
004486a0        eax_33:1.b = (*(esi_4 + 0x88c)):1.b | 0x20
004486a3        *(esi_4 + 0x88c) = eax_33
004486b3        char* __return_addr_11 = find_case_insensitive_substring("Ring=Explode", &arg_60)
004486bd        __return_addr = __return_addr_11
004486c1        if (__return_addr_11 != 0)
004486c9        int32_t eax_34
004486c9        eax_34:1.b = (*(esi_4 + 0x88c)):1.b | 8
004486cc        *(esi_4 + 0x88c) = eax_34
004486dc        char* __return_addr_12 = find_case_insensitive_substring("Ring=Slow", &arg_60)
004486e6        __return_addr = __return_addr_12
004486ea        if (__return_addr_12 != 0)
004486f2        int32_t eax_35
004486f2        eax_35:1.b = (*(esi_4 + 0x88c)):1.b | 0x10
004486f5        *(esi_4 + 0x88c) = eax_35
00448705        char* __return_addr_13 = find_case_insensitive_substring("RingSpeed=", &arg_60)
0044870f        __return_addr = __return_addr_13
00448713        if (__return_addr_13 == 0)
00448757        ecx[(ebp_1 + 0x28) * 0xe] = 0
00448726        __return_addr = &find_case_insensitive_substring("=", __return_addr_13)[1]
00448742        ecx[(ebp_1 + 0x28) * 0xe] = fconvert.s(parse_next_float32(&__return_addr))
00448764        char* __return_addr_14 = find_case_insensitive_substring("JetPack=Off", &arg_60)
0044876e        __return_addr = __return_addr_14
00448772        if (__return_addr_14 != 0)
0044877a        int32_t eax_40
0044877a        eax_40:1.b = (*(esi_4 + 0x88c)):1.b | 0x80
0044877d        *(esi_4 + 0x88c) = eax_40
00448789        edi_2 = sub_44e690(edi_4)
00448790        if (edi_2 == 0)
004488d1        eax_46 = &(&__saved_edi)[arg_10 * 0x20 + 0x53c]
004488d1        goto label_4488d8
0044879a        ebp = arg_10
0044879f        arg_1c += 1
0044888a        void* var_14_32 = &(&__saved_edi)[ebp * 0x20 + 0x53c]
00448890        report_errorf("Data line must start with '@' in Segment %s\n")
004488a2        return 0
