/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_level_definition_file @ 0x447480 */

00447495        char* filename_1 = filename
0044749e        data_74ec74 = filename
004474a4        void path
004474a4        sprintf(&path, "Levels/%s")
004474bf        if (load_file_bytes_from_archive_or_fs(&path, 0x74ec78, nullptr) == 0)
004474cb        report_errorf("Cannot find %s reverting to default.txt", &path)
004474da        sprintf(&path, "Levels/Default.txt")
004474eb        load_file_bytes_from_archive_or_fs(&path, 0x74ec78, nullptr)
004474fd        char* cursor_2 = find_case_insensitive_substring("Name:'", 0x74ec78)
00447505        char* cursor = cursor_2
0044750b        if (cursor_2 == 0)
00447517        report_errorf("Cannot find Name:' in %s", &path)
0044751c        cursor_2 = cursor
00447531        char* cursor_3 = &find_case_insensitive_substring("'", cursor_2)[1]
00447532        cursor = cursor_3
0044753c        char i = *cursor_3
0044753e        char (* edx)[0x80] = &tracks->level_display_name
00447543        if (i != 0x27)
00447548        while (i s>= 0x20)
0044754a        (edx - 0x1a58dc)->:0x1a58dc.b = i
0044754c        edx = &(*edx)[1]
0044754d        cursor_3 = &cursor_3[1]
0044754e        cursor = cursor_3
00447552        i = *cursor_3
00447557        if (i == 0x27)
00447557        break
00447559        (edx - 0x1a58dc)->:0x1a58dc.b = 0
00447569        if (g_game_base[0x12d4638] == 0)
00447575        char* cursor_4 = find_case_insensitive_substring("Arcade", filename)
0044757d        cursor = cursor_4
00447583        if (cursor_4 != 0)
0044759a        cursor = &find_case_insensitive_substring("e", cursor_4)[1]
004475b0        int32_t ecx_2 = parse_next_signed_int(&cursor) * 7
004475b2        char (* var_730_2)[0x80] = &tracks->level_display_name
004475bb        int32_t edi_2 = ecx_2 * 0x60
004475c6        sprintf(&g_game_base[edi_2 + 0x12d4668], "%s")
004475d5        char* cursor_5 = find_case_insensitive_substring("GalaxyText:", 0x74ec78)
004475dd        cursor = cursor_5
004475e3        if (cursor_5 != 0)
00447616        char* cursor_6 = find_case_insensitive_substring("{", cursor_5)
0044761e        cursor = cursor_6
00447624        if (cursor_6 != 0)
00447651        char* cursor_7 = advance_to_next_crlf_line(cursor_6)
0044765c        cursor = cursor_7
00447660        char* eax_8 = find_case_insensitive_substring("}", cursor_7)
0044766a        if (eax_8 != 0)
0044769d        char* edx_4 = &g_game_base[edi_2 + 0x12d46e8]
004476a4        char* i_1 = cursor
004476aa        while (i_1 u< eax_8 - 2)
004476af        if (*i_1 s< 0x20)
004476b1        *edx_4 = 0x3e
004476b4        i_1 = cursor
004476b8        edx_4 = &edx_4[1]
004476bc        while (*i_1 s< 0x20)
004476be        i_1 = &i_1[1]
004476bf        cursor = i_1
004476ca        *edx_4 = *i_1
004476d0        edx_4 = &edx_4[1]
004476d1        i_1 = &cursor[1]
004476d4        cursor = i_1
004476da        *edx_4 = 0
00447672        report_warningf("Cannot find } for GalaxyText: in %s", filename)
0044768a        rstrcpy_checked_ascii(&g_game_base[edi_2 + 0x12d46e8], "TEXT ERROR } MISSING")
0044762c        report_warningf("Cannot find { for GalaxyText: in %s", filename)
00447643        rstrcpy_checked_ascii(&g_game_base[edi_2 + 0x12d46e8], "TEXT ERROR { MISSING")
004475eb        report_warningf("Cannot find GalaxyText: in %s", filename)
00447603        rstrcpy_checked_ascii(&g_game_base[edi_2 + 0x12d46e8], "TEXT MISSING")
004476e7        char* cursor_8 = find_case_insensitive_substring("Random:yes", 0x74ec78)
004476f3        cursor = cursor_8
004476fc        if (cursor_8 == 0)
00447794        tracks->random_enabled = 0
0044779b        tracks->random_length = 0
0044770c        tracks->random_enabled = 1
00447712        char* cursor_9 = find_case_insensitive_substring("Length:", 0x74ec78)
0044771c        cursor = cursor_9
00447720        if (cursor_9 == 0)
0044772c        report_errorf("Cannot Length: in %s", &path)
0044773e        return
0044774f        char* cursor_10 = &find_case_insensitive_substring(":", cursor_9)[1]
00447750        cursor = cursor_10
00447754        tracks->random_length = 0
0044775a        char i_2 = *cursor_10
00447769        if (i_2 != 0x61 && i_2 != 0x41 && i_2 s>= 0x30)
0044776e        while (i_2 s<= 0x39)
00447770        int32_t random_length = tracks->random_length
00447776        cursor_10 = &cursor_10[1]
0044777d        cursor = cursor_10
00447785        tracks->random_length = sx.d(i_2) + random_length * 0xa - 0x30
0044778b        i_2 = *cursor_10
00447790        if (i_2 s< 0x30)
00447790        break
004477ab        char* cursor_11 = find_case_insensitive_substring("Background:", 0x74ec78)
004477b5        cursor = cursor_11
004477b9        if (cursor_11 == 0)
004477c5        report_errorf("No Background: in %s", &path)
004477d7        return
004477e8        char* cursor_12 = &find_case_insensitive_substring(":", cursor_11)[1]
004477e9        cursor = cursor_12
004477ed        void var_200
004477ed        char* ecx_10 = &var_200
004477f4        char i_3 = *cursor_12
004477f9        while (i_3 != 0x2e)
004477fb        *ecx_10 = i_3
004477fd        ecx_10 = &ecx_10[1]
004477fe        cursor_12 = &cursor_12[1]
004477ff        cursor = cursor_12
00447803        i_3 = *cursor_12
0044780a        *ecx_10 = 0x2e
0044780e        char* game_base_1 = g_game_base
00447814        ecx_10[1] = 0x74
00447818        ecx_10[2] = 0x78
0044781c        ecx_10[3] = 0x74
0044781f        ecx_10[4] = 0
00447840        tracks->landscape_script_index = load_landscape_script_by_name(&game_base_1[0x106c218], &var_200)
00447846        char* cursor_13 = find_case_insensitive_substring("Fringe:", 0x74ec78)
00447850        cursor = cursor_13
00447854        if (cursor_13 != 0)
0044789a        cursor = &find_case_insensitive_substring(":", cursor_13)[1]
004478b6        tracks->fringe_color.r = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
004478d4        tracks->fringe_color.g = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
004478f0        tracks->fringe_color.b = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
00447860        report_errorf("No Fringe: in %s using white", &path)
00447882        store_color4f(&tracks->fringe_color, 1f, 1f, 1f, 1f)
00447900        char* cursor_14 = find_case_insensitive_substring("Track:", 0x74ec78)
0044790a        cursor = cursor_14
0044790e        if (cursor_14 != 0)
00447938        char* cursor_15 = &find_case_insensitive_substring(":", cursor_14)[1]
00447939        cursor = cursor_15
0044793d        char eax_20 = *cursor_15
00447941        if (eax_20 == 0x30)
00447943        tracks->track_texture_set = 0
0044794d        if (eax_20 == 0x31)
0044794f        tracks->track_texture_set = 1
00447959        if (eax_20 == 0x32)
0044795b        tracks->track_texture_set = 2
00447969        if (eax_20 == 0x33)
0044796b        tracks->track_texture_set = 3
00447979        if (eax_20 == 0x72)
0044797b        tracks->track_texture_set = 5
0044791a        report_errorf("No Track: in %s using Track0.tga", &path)
00447922        tracks->track_texture_set = 0
0044798f        char* cursor_16 = find_case_insensitive_substring("Parcels:", 0x74ec78)
00447999        cursor = cursor_16
0044799d        if (cursor_16 == 0)
004479a3        tracks->parcel_count = 0
004479af        report_errorf("No Parcel: in %s", &path)
004479c1        return
004479cf        cursor = find_case_insensitive_substring(":", cursor_16)
004479e7        tracks->parcel_count = parse_next_signed_int(&cursor)
004479ed        char* cursor_17 = find_case_insensitive_substring("Quota:", 0x74ec78)
004479f7        cursor = cursor_17
004479fb        if (cursor_17 == 0)
00447a01        tracks->parcel_quota = 0
00447a0d        report_errorf("No Quota: in %s", &path)
00447a1f        return
00447a31        cursor = find_case_insensitive_substring(":", cursor_17)
00447a45        tracks->parcel_quota = parse_next_signed_int(&cursor)
00447a4b        char* cursor_18 = find_case_insensitive_substring("Speed:select", 0x74ec78)
00447a55        cursor = cursor_18
00447a5e        if (cursor_18 == 0)
00447a72        char* cursor_19 = find_case_insensitive_substring("Speed:", 0x74ec78)
00447a7c        cursor = cursor_19
00447a80        if (cursor_19 != 0)
00447ab1        cursor = &find_case_insensitive_substring(":", cursor_19)[1]
00447ab5        parse_next_float32(&cursor)
00447ab5        unimplemented  {call 0x431f20}
00447aba        tracks->selected_speed = fconvert.s(unimplemented  {fstp dword [esi+0x1a595c], st0})
00447aba        unimplemented  {fstp dword [esi+0x1a595c], st0}
00447a8c        report_errorf("Cannot find Speed: in Segment %s\n", &path)
00447a94        tracks->selected_speed = 100f
00447a60        tracks->selected_speed = -1f
00447acd        char* cursor_20 = find_case_insensitive_substring("Garbage:", 0x74ec78)
00447ad7        cursor = cursor_20
00447adb        if (cursor_20 != 0)
00447aea        parse_next_float32(&cursor)
00447aea        unimplemented  {call 0x431f20}
00447aef        tracks->garbage_frequency = fconvert.s(unimplemented  {fstp dword [esi+0x1a5960], st0})
00447aef        unimplemented  {fstp dword [esi+0x1a5960], st0}
00447add        tracks->garbage_frequency = -1f
00447b02        char* cursor_21 = find_case_insensitive_substring("Salt:", 0x74ec78)
00447b0c        cursor = cursor_21
00447b10        if (cursor_21 != 0)
00447b1f        parse_next_float32(&cursor)
00447b1f        unimplemented  {call 0x431f20}
00447b24        tracks->salt_frequency = fconvert.s(unimplemented  {fstp dword [esi+0x1a5964], st0})
00447b24        unimplemented  {fstp dword [esi+0x1a5964], st0}
00447b12        tracks->salt_frequency = -1f
00447b37        tracks->segment_count = 0
00447b39        char* cursor_22 = find_case_insensitive_substring("Segments Begin:", 0x74ec78)
00447b43        cursor = cursor_22
00447b47        if (cursor_22 == 0)
00447b53        report_errorf("Cannot find Segments Begin: in %s", &path)
00447b65        return
00447b72        char* eax_27 = find_case_insensitive_substring("Segments End:", 0x74ec78)
00447b82        if (eax_27 == 0)
00447b8e        report_errorf("Cannot find Segments End: in %s", &path)
00447ba0        return
00447ba8        char* cursor_23 = advance_to_next_crlf_line(cursor)
00447bb2        cursor = cursor_23
00447bb6        if (cursor_23 != 0)
00447bbe        char segment_name[0x200]
00447bbe        while (cursor_23 u< eax_27)
00447bc9        char i_4 = *cursor_23
00447bcb        char (* ecx_16)[0x200] = &segment_name
00447bd5        while (i_4 != 0x2e)
00447bd7        *ecx_16 = i_4
00447bd9        ecx_16 = &(*ecx_16)[1]
00447bda        cursor_23 = &cursor_23[1]
00447bdb        cursor = cursor_23
00447bdf        i_4 = *cursor_23
00447be6        int32_t segment_count = tracks->segment_count
00447be8        *ecx_16 = 0x2e
00447bf1        (*ecx_16)[1] = 0x74
00447bfa        (*ecx_16)[2] = 0x78
00447c03        (*ecx_16)[3] = 0x74
00447c06        (*ecx_16)[4] = 0
00447c19        copy_segment_definition_to_level_slot(&segment_name, &tracks->segment_slots[segment_count])
00447c22        char* cursor_35 = &cursor[3]
00447c25        void var_500
00447c25        char* edx_16 = &var_500
00447c2c        char* cursor_1 = cursor_35
00447c30        char i_5 = *cursor_35
00447c34        while (i_5 s>= 0x20)
00447c36        *edx_16 = i_5
00447c38        edx_16 = &edx_16[1]
00447c39        cursor_35 = &cursor_35[1]
00447c3a        cursor_1 = cursor_35
00447c3e        i_5 = *cursor_35
00447c4b        *edx_16 = 0
00447c54        char* cursor_24 = find_case_insensitive_substring("Angle=", &var_500)
00447c5e        cursor_1 = cursor_24
00447c62        if (cursor_24 == 0)
00447cb9        tracks->segment_slots[tracks->segment_count].angle_radians.bits = 0
00447c73        cursor_1 = find_case_insensitive_substring("=", cursor_24)
00447c7d        int32_t var_708_4 = parse_next_signed_int(&cursor_1)
00447c83        unimplemented  {fild st0, dword [esp+0x24]}
00447c8f        unimplemented  {fmul st0, dword [0x4973b8]}
00447c9f        tracks->segment_slots[tracks->segment_count].angle_radians.bits = fconvert.s(unimplemented  {fstp dword [edx+esi+0x4018], st0})
00447c9f        unimplemented  {fstp dword [edx+esi+0x4018], st0}
00447cde        tracks->segment_slots[tracks->segment_count].message_text[0] = 0
00447ce6        char* cursor_25 = find_case_insensitive_substring("Message=", &var_500)
00447cf0        cursor_1 = cursor_25
00447cf4        if (cursor_25 != 0)
00447d08        char* cursor_26 = &find_case_insensitive_substring("=", cursor_25)[1]
00447d09        cursor_1 = cursor_26
00447d10        if (*cursor_26 != 0x22)
00447ef6        report_errorf("Need " after Message=")
00447f08        return
00447d16        char* cursor_27 = &cursor_26[1]
00447d17        cursor_1 = cursor_27
00447d1b        char* cursor_37 = cursor_27
00447d20        if (*cursor_27 != 0x22)
00447d29        char i_6
00447d22        i_6 = cursor_37[1]
00447d25        cursor_37 = &cursor_37[1]
00447d29        do while (i_6 != 0x22)
00447d3e        char* ecx_28 = &tracks->segment_slots[tracks->segment_count].message_text
00447d45        while (cursor_27 u< cursor_37)
00447d49        *ecx_28 = *cursor_27
00447d4f        ecx_28 = &ecx_28[1]
00447d50        cursor_27 = &cursor_1[1]
00447d53        cursor_1 = cursor_27
00447d59        *ecx_28 = 0
00447d6e        cursor_1 = find_case_insensitive_substring("Duration=", &var_500)
00447d86        tracks->segment_slots[tracks->segment_count].message_duration.bits = 0x40800000
00447d8d        char* cursor_28 = cursor_1
00447d93        if (cursor_28 != 0)
00447da1        cursor_1 = &find_case_insensitive_substring("=", cursor_28)[1]
00447daa        parse_next_float32(&cursor_1)
00447daa        unimplemented  {call 0x431f20}
00447dc3        tracks->segment_slots[tracks->segment_count].message_duration.bits = fconvert.s(unimplemented  {fstp dword [ecx+esi+0x421c], st0})
00447dc3        unimplemented  {fstp dword [ecx+esi+0x421c], st0}
00447ddc        cursor_1 = find_case_insensitive_substring("Sample=", &var_500)
00447df5        *((tracks->segment_count + 1) * 0x4220 + tracks) = 0xffffffff
00447dfc        char* cursor_29 = cursor_1
00447e02        if (cursor_29 != 0)
00447e13        char* cursor_30 = &find_case_insensitive_substring("=", cursor_29)[2]
00447e19        cursor_1 = cursor_30
00447e1d        void var_480
00447e1d        char* edx_35 = &var_480
00447e24        char i_7 = *cursor_30
00447e29        while (i_7 != 0x22)
00447e2b        *edx_35 = i_7
00447e2d        edx_35 = &edx_35[1]
00447e2e        cursor_30 = &cursor_30[1]
00447e2f        cursor_1 = cursor_30
00447e33        i_7 = *cursor_30
00447e3a        *edx_35 = 0
00447e5f        *((tracks->segment_count + 1) * 0x4220 + tracks) = find_registered_sound_sample_id_by_name(&var_480)
00447e78        if (*((tracks->segment_count + 1) * 0x4220 + tracks) == 0xffffffff)
00447e8c        report_errorf("Cannot find sample %s in %s", &var_480, &path)
00447e96        char* cursor_36 = cursor
00447e9c        tracks->segment_count += 1
00447e9e        cursor_23 = advance_to_next_crlf_line(cursor_36)
00447ea8        cursor = cursor_23
00447eac        if (cursor_23 == 0)
00447f18        report_errorf("Unexpected end of file in %s", filename)
00447f2a        return
00447ec2        char* cursor_31 = find_case_insensitive_substring("First:", 0x74ec78)
00447ecc        cursor = cursor_31
00447ed0        if (cursor_31 == 0)
00447edc        report_errorf("Cannot find 'First:' in %s", &path)
00447eee        return
00447f2e        char* cursor_32 = advance_to_next_crlf_line(cursor_31)
00447f38        cursor = cursor_32
00447f3c        if (cursor_32 != 0)
00447f5d        char i_8 = *cursor_32
00447f5f        char (* ecx_50)[0x200] = &segment_name
00447f69        while (i_8 != 0x2e)
00447f6b        *ecx_50 = i_8
00447f6d        ecx_50 = &(*ecx_50)[1]
00447f6e        cursor_32 = &cursor_32[1]
00447f6f        cursor = cursor_32
00447f73        i_8 = *cursor_32
00447f7a        *ecx_50 = 0x2e
00447f8b        (*ecx_50)[1] = 0x74
00447f91        (*ecx_50)[2] = 0x78
00447f95        (*ecx_50)[3] = 0x74
00447f98        (*ecx_50)[4] = 0
00447f9e        copy_segment_definition_to_level_slot(&segment_name, &tracks->first_segment)
00447fad        char* cursor_33 = find_case_insensitive_substring("Last:", 0x74ec78)
00447fb7        cursor = cursor_33
00447fbb        if (cursor_33 == 0)
00447fc7        report_errorf("Cannot find 'Last:' in %s", &path)
00447fd9        return
00447fdd        char* cursor_34 = advance_to_next_crlf_line(cursor_33)
00447fe7        cursor = cursor_34
00447feb        if (cursor_34 == 0)
00447ff7        report_errorf("Unexpected end of file in %s", &path)
00448009        return
0044800c        char i_9 = *cursor_34
0044800e        char (* ecx_55)[0x200] = &segment_name
00448018        while (i_9 != 0x2e)
0044801a        *ecx_55 = i_9
0044801c        ecx_55 = &(*ecx_55)[1]
0044801d        cursor_34 = &cursor_34[1]
0044801e        cursor = cursor_34
00448022        i_9 = *cursor_34
00448029        *ecx_55 = 0x2e
00448033        (*ecx_55)[1] = 0x74
00448038        (*ecx_55)[2] = 0x78
0044803c        (*ecx_55)[3] = 0x74
0044803f        (*ecx_55)[4] = 0
0044804d        copy_segment_definition_to_level_slot(&segment_name, &tracks->last_segment)
0044805c        return
00447f48        report_errorf("Unexpected end of file in %s", &path)
00447f5a        return
