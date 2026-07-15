/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_segment_definitions @ 0x448160 */

00448165        int32_t* out_count = chkstk(0x114e0)
00448189        *out_count = 0
0044818b        EnumeratedEntryName names[0x200]
0044818b        enumerate_matching_archive_or_fs_entries("Segments", "*.txt", out_count, &names)
00448190        int32_t eax = *out_count
0044819a        if (eax s>= 0x96)
004481a1        report_errorf("Too many Segments increase RSMTRACK_SEGMENT_MAX")
004481b3        return
004481b4        int32_t ebp = 0
004481b8        int32_t arg_10 = 0
004481bc        if (eax s<= 0)
004481bc        return
004481c2        EnumeratedEntryName (* edi_1)[0x200] = &names
004481cf        int32_t arg_18 = 0
004481d3        int32_t arg_14 = 0
004481d7        EnumeratedEntryName (* arg_8)[0x200] = &names
004481db        int32_t* arg_4 = &out_count[0x22]
004481f3        while (true)
004481f3        void buffer
004481f3        void* var_14_1 = &buffer
004481f4        EnumeratedEntryName (* var_18_1)[0x200] = edi_1
004481fb        void path
004481fb        sprintf(&path, "Segments/%s")
00448211        load_file_bytes_from_archive_or_fs(&path, &buffer, nullptr)
00448223        char* eax_1 = find_case_insensitive_substring("ID:", &buffer)
0044822d        int32_t __saved_edi
0044822d        if (eax_1 == 0)
0044880e        report_errorf("Cannot find ID: in Segment %s\n", &(&__saved_edi)[ebp * 0x20 + 0x53c])
00448820        return
00448233        char i = eax_1[3]
00448236        char* eax_2 = &eax_1[3]
00448239        int32_t edx_1 = 0
0044823e        if (i s>= 0x30)
00448243        while (i s<= 0x39)
0044824b        eax_2 = &eax_2[1]
0044824c        edx_1 = sx.d(i) + edx_1 * 0xa - 0x30
00448250        i = *eax_2
00448255        if (i s< 0x30)
00448255        break
0044825b        EnumeratedEntryName (* var_14_2)[0x200] = edi_1
00448265        arg_4[-1] = edx_1
00448268        sprintf(&arg_4[-0x11], "%s")
0044827a        char* eax_4 = find_case_insensitive_substring("Name:'", &buffer)
00448284        if (eax_4 == 0)
00448831        report_errorf("Cannot find Name: in Segment %s\n", &(&__saved_edi)[ebp * 0x20 + 0x53c])
00448843        return
00448290        char* eax_5 = find_case_insensitive_substring("'", eax_4)
00448295        char i_1 = eax_5[1]
0044829b        void* eax_6 = &eax_5[1]
0044829f        if (i_1 != 0x27)
004482a3        char* edx_3 = &arg_4[-0x11] - eax_6 - 0x40
004482a6        *(edx_3 + eax_6) = i_1
004482a9        i_1 = *(eax_6 + 1)
004482ac        eax_6 += 1
004482b0        do while (i_1 != 0x27)
004482bf        char* eax_7 = find_case_insensitive_substring("Data:", &buffer)
004482c9        if (eax_7 == 0)
00448854        report_errorf("Cannot find Data: in Segment %s\n", &(&__saved_edi)[ebp * 0x20 + 0x53c])
00448866        return
004482d0        char* eax_8 = advance_to_next_crlf_line(eax_7)
004482da        void* var_14_31
004482da        if (eax_8 == 0)
00448871        var_14_31 = &(&__saved_edi)[ebp * 0x20 + 0x53c]
004482e6        char* edi_2 = advance_to_next_crlf_line(eax_8)
004482ed        void* eax_46
004482ed        if (edi_2 == 0)
00448877        eax_46 = &(&__saved_edi)[ebp * 0x20 + 0x53c]
004488d8        label_4488d8:
004488d8        var_14_31 = eax_46
004482f6        if (*edi_2 != 0x40)
00448890        report_errorf("Data line must start with '@' in Segment %s\n", &(&__saved_edi)[ebp * 0x20 + 0x53c])
004488a2        return
00448300        int32_t arg_1c = 0
00448304        *arg_4 = 0
00448315        while (true)
00448315        if (*edi_2 == 0x40 && edi_2[1] == 0x40 && edi_2[2] == 0x40)
004487be        ebp += 1
004487bf        arg_18 += 0x127
004487dd        arg_10 = ebp
004487e1        arg_14 += 0x811
004487e5        arg_4 = &arg_4[0x1022]
004487e9        arg_8 = &(*arg_8)[1]
004487ed        if (ebp s>= *out_count)
004487fd        return
004481e1        edi_1 = arg_8
004481e1        break
00448324        int32_t ebp_1 = sx.d(arg_1c.w) + arg_18
00448334        char* edi_3 = &edi_2[1]
00448335        void* esi_4 = &out_count[ebp_1 * 0xe]
00448338        int32_t i_2 = 0
0044833a        *(esi_4 + 0x88c) = 0
0044834c        char ebx_2 = *edi_3
0044834e        edi_3 = &edi_3[1]
0044834f        int32_t edx_8 = i_2 + ((*arg_4 + arg_14) << 3)
00448352        i_2 += 1
00448356        *(edx_8 + out_count + 0x8c) = ebx_2
0044835d        do while (i_2 s< 8)
00448362        if (*edi_3 != 0x40)
004488b7        report_errorf("Data line must end with '@' in Segment %s\n", &(&__saved_edi)[arg_10 * 0x20 + 0x53c])
004488c9        return
0044836f        char* edi_4 = &edi_3[1]
00448370        *arg_4 += 1
00448375        if (*edi_4 == 0x2a)
00448377        int32_t* eax_13 = *(esi_4 + 0x88c)
0044837d        eax_13.b |= 4
0044837f        *(esi_4 + 0x88c) = eax_13
00448385        char i_3 = *edi_4
00448387        void arg_60
00448387        char* ecx_5 = &arg_60
0044838d        while (i_3 != 0xd)
0044838f        *ecx_5 = i_3
00448391        i_3 = edi_4[1]
00448394        ecx_5 = &ecx_5[1]
00448395        edi_4 = &edi_4[1]
004483a6        *ecx_5 = 0
004483a8        char* __return_addr_1 = find_case_insensitive_substring("3DModel=", &arg_60)
004483b2        __return_addr = __return_addr_1
004483b6        if (__return_addr_1 != 0)
004483ca        char* __return_addr_2 = &find_case_insensitive_substring("=", __return_addr_1)[1]
004483cb        __return_addr = __return_addr_2
004483cf        char mesh_name[0x80]
004483cf        char (* ecx_6)[0x80] = &mesh_name
004483d6        char i_4 = *__return_addr_2
004483db        while (i_4 != 0x2e)
004483dd        *ecx_6 = i_4
004483df        ecx_6 = &(*ecx_6)[1]
004483e0        __return_addr_2 = &__return_addr_2[1]
004483e1        __return_addr = __return_addr_2
004483e5        i_4 = *__return_addr_2
004483ec        int32_t eax_15 = *(esi_4 + 0x88c)
004483f2        *ecx_6 = 0x2e
004483f6        eax_15.b |= 2
004483f8        *(esi_4 + 0x88c) = eax_15
004483fe        struct GameRoot* game_base_1 = g_game_base
00448404        (*ecx_6)[1] = 0x78
00448407        (*ecx_6)[2] = 0
0044841d        *(esi_4 + 0x8a0) = load_or_reuse_cached_x_mesh(&game_base_1->directx_loader, &mesh_name)
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
00448522        int32_t eax_24 = parse_next_signed_int(&__return_addr)
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
004485a1        char name[0x40]
004485a1        char (* edx_16)[0x40] = &name
004485a5        char i_5 = *__return_addr_6
004485aa        while (i_5 s>= 0x20)
004485ac        *edx_16 = i_5
004485ae        edx_16 = &(*edx_16)[1]
004485af        __return_addr_6 = &__return_addr_6[1]
004485b0        __return_addr = __return_addr_6
004485b4        i_5 = *__return_addr_6
004485cc        *edx_16 = 0
004485ce        int32_t eax_28 = find_segment_path_index_by_name(&g_game_base->subgame.path_manager, &name)
004485d6        *(esi_4 + 0x8bc) = eax_28
004485dc        if (eax_28 != 0xffffffff)
004485f7        int32_t eax_29 = *(esi_4 + 0x88c)
004485fd        eax_29.b |= 8
004485ff        *(esi_4 + 0x88c) = eax_29
004485ed        report_errorf("Unknown path %s in %s", &name, arg_8)
0044860f        char* __return_addr_7 = find_case_insensitive_substring("NoFall", &arg_60)
00448619        __return_addr = __return_addr_7
0044861d        if (__return_addr_7 != 0)
0044861f        int32_t eax_30 = *(esi_4 + 0x88c)
00448625        eax_30:1.b |= 1
00448628        *(esi_4 + 0x88c) = eax_30
00448638        char* __return_addr_8 = find_case_insensitive_substring("Ring=None", &arg_60)
00448642        __return_addr = __return_addr_8
00448646        if (__return_addr_8 != 0)
00448648        int32_t eax_31 = *(esi_4 + 0x88c)
0044864e        eax_31:1.b |= 2
00448651        *(esi_4 + 0x88c) = eax_31
00448661        char* __return_addr_9 = find_case_insensitive_substring("Ring=Normal", &arg_60)
0044866b        __return_addr = __return_addr_9
0044866f        if (__return_addr_9 != 0)
00448671        int32_t eax_32 = *(esi_4 + 0x88c)
00448677        eax_32:1.b |= 4
0044867a        *(esi_4 + 0x88c) = eax_32
0044868a        char* __return_addr_10 = find_case_insensitive_substring("Ring=PowerUp", &arg_60)
00448694        __return_addr = __return_addr_10
00448698        if (__return_addr_10 != 0)
0044869a        int32_t eax_33 = *(esi_4 + 0x88c)
004486a0        eax_33:1.b |= 0x20
004486a3        *(esi_4 + 0x88c) = eax_33
004486b3        char* __return_addr_11 = find_case_insensitive_substring("Ring=Explode", &arg_60)
004486bd        __return_addr = __return_addr_11
004486c1        if (__return_addr_11 != 0)
004486c3        int32_t eax_34 = *(esi_4 + 0x88c)
004486c9        eax_34:1.b |= 8
004486cc        *(esi_4 + 0x88c) = eax_34
004486dc        char* __return_addr_12 = find_case_insensitive_substring("Ring=Slow", &arg_60)
004486e6        __return_addr = __return_addr_12
004486ea        if (__return_addr_12 != 0)
004486ec        int32_t eax_35 = *(esi_4 + 0x88c)
004486f2        eax_35:1.b |= 0x10
004486f5        *(esi_4 + 0x88c) = eax_35
00448705        char* __return_addr_13 = find_case_insensitive_substring("RingSpeed=", &arg_60)
0044870f        __return_addr = __return_addr_13
00448713        if (__return_addr_13 == 0)
00448757        out_count[(ebp_1 + 0x28) * 0xe] = 0
00448726        __return_addr = &find_case_insensitive_substring("=", __return_addr_13)[1]
00448742        out_count[(ebp_1 + 0x28) * 0xe] = fconvert.s(parse_next_float32(&__return_addr))
00448764        char* __return_addr_14 = find_case_insensitive_substring("JetPack=Off", &arg_60)
0044876e        __return_addr = __return_addr_14
00448772        if (__return_addr_14 != 0)
00448774        int32_t eax_40 = *(esi_4 + 0x88c)
0044877a        eax_40:1.b |= 0x80
0044877d        *(esi_4 + 0x88c) = eax_40
00448789        edi_2 = advance_to_next_crlf_line(edi_4)
00448790        if (edi_2 == 0)
004488d1        eax_46 = &(&__saved_edi)[arg_10 * 0x20 + 0x53c]
004488d1        goto label_4488d8
0044879a        ebp = arg_10
0044879f        arg_1c += 1
0044833a        continue
004488de        report_errorf("Unexpected end of file in Segment %s\n", var_14_31)
004488e3        break
004488f0        return
