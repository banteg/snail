/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_level_definition_file @ 0x447480 */

00447495        char* var_724 = arg2
0044749e        data_74ec74 = arg2
004474a4        char var_700[0x200]
004474a4        sub_48b32c(&var_700, "Levels/%s")
004474bf        if (load_file_bytes_from_archive_or_fs(&var_700, 0x74ec78, nullptr) == 0)
004474c5        char (* var_724_1)[0x200] = &var_700
004474cb        report_errorf("Cannot find %s reverting to default.txt")
004474da        sub_48b32c(&var_700, "Levels/Default.txt")
004474eb        load_file_bytes_from_archive_or_fs(&var_700, 0x74ec78, nullptr)
004474fd        char* i_10 = find_case_insensitive_substring("Name:'", 0x74ec78)
00447505        char* i_9 = i_10
0044750b        if (i_10 == 0)
00447511        char (* var_724_2)[0x200] = &var_700
00447517        report_errorf("Cannot find Name:' in %s")
0044751c        i_10 = i_9
00447531        char* i_11 = &find_case_insensitive_substring("'", i_10)[1]
00447532        i_9 = i_11
0044753c        char i = *i_11
0044753e        char* edx = &arg1[0x69637]
00447543        if (i != 0x27)
00447548        while (i s>= 0x20)
0044754a        *edx = i
0044754c        edx = &edx[1]
0044754d        i_11 = &i_11[1]
0044754e        i_9 = i_11
00447552        i = *i_11
00447557        if (i == 0x27)
00447557        break
00447559        *edx = 0
00447569        if (*(data_4df904 + 0x12d4638) == 0)
00447575        char* i_12 = find_case_insensitive_substring("Arcade", arg2)
0044757d        i_9 = i_12
00447583        if (i_12 != 0)
0044759a        i_9 = &find_case_insensitive_substring("e", i_12)[1]
004475b2        char* var_730_2 = &arg1[0x69637]
004475bb        int32_t edi_2 = sub_44e710(&i_9) * 0x2a0
004475c6        sub_48b32c(edi_2 + data_4df904 + 0x12d4668, "%s")
004475d5        char* i_13 = find_case_insensitive_substring("GalaxyText:", 0x74ec78)
004475dd        i_9 = i_13
004475e3        if (i_13 != 0)
00447616        char* i_14 = find_case_insensitive_substring("{", i_13)
0044761e        i_9 = i_14
00447624        if (i_14 != 0)
00447651        char* i_15 = sub_44e690(i_14)
0044765c        i_9 = i_15
00447660        char* eax_8 = find_case_insensitive_substring("}", i_15)
0044766a        if (eax_8 != 0)
0044769d        char* edx_4 = edi_2 + data_4df904 + 0x12d46e8
004476a4        char* i_1 = i_9
004476aa        while (i_1 u< eax_8 - 2)
004476af        if (*i_1 s< 0x20)
004476b1        *edx_4 = 0x3e
004476b4        i_1 = i_9
004476b8        edx_4 = &edx_4[1]
004476bc        while (*i_1 s< 0x20)
004476be        i_1 = &i_1[1]
004476bf        i_9 = i_1
004476c8        i_1.b = *i_1
004476ca        *edx_4 = i_1.b
004476d0        edx_4 = &edx_4[1]
004476d1        i_1 = &i_9[1]
004476d4        i_9 = i_1
004476da        *edx_4 = 0
0044766c        char* var_724_10 = arg2
00447672        report_warningf("Cannot find } for GalaxyText: in %s")
0044768a        sub_44e5b0(edi_2 + data_4df904 + 0x12d46e8, "TEXT ERROR } MISSING")
00447626        char* var_724_8 = arg2
0044762c        report_warningf("Cannot find { for GalaxyText: in %s")
00447643        sub_44e5b0(edi_2 + data_4df904 + 0x12d46e8, "TEXT ERROR { MISSING")
004475e5        char* var_724_6 = arg2
004475eb        report_warningf("Cannot find GalaxyText: in %s")
00447603        sub_44e5b0(edi_2 + data_4df904 + 0x12d46e8, "TEXT MISSING")
004476e7        char* i_16 = find_case_insensitive_substring("Random:yes", 0x74ec78)
004476f3        i_9 = i_16
004476fc        if (i_16 == 0)
00447794        arg1[0x69632].b = 0
0044779b        arg1[0x69631] = 0
0044770c        arg1[0x69632].b = 1
00447712        char* i_17 = find_case_insensitive_substring("Length:", 0x74ec78)
0044771c        i_9 = i_17
00447720        if (i_17 == 0)
00447726        char (* var_724_11)[0x200] = &var_700
0044772c        report_errorf("Cannot Length: in %s")
0044773e        return 0
00447747        char* eax_11
00447747        int32_t ecx_6
00447747        eax_11, ecx_6 = find_case_insensitive_substring(":", i_17)
0044774f        char* i_18 = &eax_11[1]
00447750        i_9 = i_18
00447754        arg1[0x69631] = 0
0044775a        ecx_6.b = *i_18
00447769        if (ecx_6.b != 0x61 && ecx_6.b != 0x41 && ecx_6.b s>= 0x30)
0044776e        while (ecx_6.b s<= 0x39)
00447770        int32_t edx_5 = arg1[0x69631]
00447776        i_18 = &i_18[1]
0044777d        i_9 = i_18
00447785        arg1[0x69631] = sx.d(ecx_6.b) + edx_5 * 0xa - 0x30
0044778b        ecx_6.b = *i_18
00447790        if (ecx_6.b s< 0x30)
00447790        break
004477ab        char* i_19 = find_case_insensitive_substring("Background:", 0x74ec78)
004477b5        i_9 = i_19
004477b9        if (i_19 == 0)
004477bf        char (* var_724_13)[0x200] = &var_700
004477c5        report_errorf("No Background: in %s")
004477d7        return 0
004477e8        char* i_20 = &find_case_insensitive_substring(":", i_19)[1]
004477e9        i_9 = i_20
004477ed        void var_200
004477ed        char* ecx_7 = &var_200
004477f4        char i_2 = *i_20
004477f9        while (i_2 != 0x2e)
004477fb        *ecx_7 = i_2
004477fd        ecx_7 = &ecx_7[1]
004477fe        i_20 = &i_20[1]
004477ff        i_9 = i_20
00447803        i_2 = *i_20
0044780a        *ecx_7 = 0x2e
0044780e        void* edx_8 = data_4df904
00447814        ecx_7[1] = 0x74
00447818        ecx_7[2] = 0x78
0044781c        ecx_7[3] = 0x74
0044781f        ecx_7[4] = 0
00447840        arg1[0x6965a] = load_landscape_script_by_name(edx_8 + 0x106c218, &var_200)
00447846        char* i_21 = find_case_insensitive_substring("Fringe:", 0x74ec78)
00447850        i_9 = i_21
00447854        if (i_21 != 0)
0044789a        i_9 = &find_case_insensitive_substring(":", i_21)[1]
004478b6        arg1[0x69633] = fconvert.s(float.t(sub_44e710(&i_9)) * fconvert.t(0.00392156886f))
004478d4        arg1[0x69634] = fconvert.s(float.t(sub_44e710(&i_9)) * fconvert.t(0.00392156886f))
004478f0        arg1[0x69635] = fconvert.s(float.t(sub_44e710(&i_9)) * fconvert.t(0.00392156886f))
0044785a        char (* var_724_16)[0x200] = &var_700
00447860        report_errorf("No Fringe: in %s using white")
00447882        store_color4f(&arg1[0x69633], 1f, 1f, 1f, 1f)
00447900        char* i_22 = find_case_insensitive_substring("Track:", 0x74ec78)
0044790a        i_9 = i_22
0044790e        if (i_22 != 0)
00447938        char* i_23 = &find_case_insensitive_substring(":", i_22)[1]
00447939        i_9 = i_23
0044793d        i_23.b = *i_23
00447941        if (i_23.b == 0x30)
00447943        arg1[0x6965c] = 0
0044794d        if (i_23.b == 0x31)
0044794f        arg1[0x6965c] = 1
00447959        if (i_23.b == 0x32)
0044795b        arg1[0x6965c] = 2
00447969        if (i_23.b == 0x33)
0044796b        arg1[0x6965c] = 3
00447979        if (i_23.b == 0x72)
0044797b        arg1[0x6965c] = 5
00447914        char (* var_724_18)[0x200] = &var_700
0044791a        report_errorf("No Track: in %s using Track0.tga")
00447922        arg1[0x6965c] = 0
0044798f        char* i_24 = find_case_insensitive_substring("Parcels:", 0x74ec78)
00447999        i_9 = i_24
0044799d        if (i_24 == 0)
004479a3        arg1[0x6965b] = 0
004479a9        char (* var_724_20)[0x200] = &var_700
004479af        report_errorf("No Parcel: in %s")
004479c1        return 0
004479cf        i_9 = find_case_insensitive_substring(":", i_24)
004479e7        arg1[0x6965b] = sub_44e710(&i_9)
004479ed        char* i_25 = find_case_insensitive_substring("Quota:", 0x74ec78)
004479f7        i_9 = i_25
004479fb        if (i_25 == 0)
00447a01        arg1[0x6965d] = 0
00447a07        char (* var_724_22)[0x200] = &var_700
00447a0d        report_errorf("No Quota: in %s")
00447a1f        return 0
00447a31        i_9 = find_case_insensitive_substring(":", i_25)
00447a45        arg1[0x6965d] = sub_44e710(&i_9)
00447a4b        char* i_26 = find_case_insensitive_substring("Speed:select", 0x74ec78)
00447a55        i_9 = i_26
00447a5e        if (i_26 == 0)
00447a72        char* i_27 = find_case_insensitive_substring("Speed:", 0x74ec78)
00447a7c        i_9 = i_27
00447a80        if (i_27 != 0)
00447ab1        i_9 = &find_case_insensitive_substring(":", i_27)[1]
00447ab5        parse_next_float32(&i_9)
00447ab5        unimplemented  {call 0x431f20}
00447aba        arg1[0x69657] = fconvert.s(unimplemented  {fstp dword [esi+0x1a595c], st0})
00447aba        unimplemented  {fstp dword [esi+0x1a595c], st0}
00447a86        char (* var_724_24)[0x200] = &var_700
00447a8c        report_errorf("Cannot find Speed: in Segment %s\n")
00447a94        arg1[0x69657] = 0x42c80000
00447a60        arg1[0x69657] = 0xbf800000
00447acd        char* i_28 = find_case_insensitive_substring("Garbage:", 0x74ec78)
00447ad7        i_9 = i_28
00447adb        if (i_28 != 0)
00447aea        parse_next_float32(&i_9)
00447aea        unimplemented  {call 0x431f20}
00447aef        arg1[0x69658] = fconvert.s(unimplemented  {fstp dword [esi+0x1a5960], st0})
00447aef        unimplemented  {fstp dword [esi+0x1a5960], st0}
00447add        arg1[0x69658] = 0xbf800000
00447b02        char* i_29 = find_case_insensitive_substring("Salt:", 0x74ec78)
00447b0c        i_9 = i_29
00447b10        if (i_29 != 0)
00447b1f        parse_next_float32(&i_9)
00447b1f        unimplemented  {call 0x431f20}
00447b24        arg1[0x69659] = fconvert.s(unimplemented  {fstp dword [esi+0x1a5964], st0})
00447b24        unimplemented  {fstp dword [esi+0x1a5964], st0}
00447b12        arg1[0x69659] = 0xbf800000
00447b37        *arg1 = 0
00447b39        char* i_30 = find_case_insensitive_substring("Segments Begin:", 0x74ec78)
00447b43        i_9 = i_30
00447b47        if (i_30 == 0)
00447b4d        char (* var_724_28)[0x200] = &var_700
00447b53        report_errorf("Cannot find Segments Begin: in %s")
00447b65        return 0
00447b72        char* eax_26 = find_case_insensitive_substring("Segments End:", 0x74ec78)
00447b82        if (eax_26 == 0)
00447b88        char (* var_724_29)[0x200] = &var_700
00447b8e        report_errorf("Cannot find Segments End: in %s")
00447ba0        return 0
00447ba8        char* i_31 = sub_44e690(i_9)
00447bb2        i_9 = i_31
00447bb6        if (i_31 != 0)
00447bbe        void var_400
00447bbe        while (i_31 u< eax_26)
00447bc9        char i_3 = *i_31
00447bcb        char* ecx_13 = &var_400
00447bd5        while (i_3 != 0x2e)
00447bd7        *ecx_13 = i_3
00447bd9        ecx_13 = &ecx_13[1]
00447bda        i_31 = &i_31[1]
00447bdb        i_9 = i_31
00447bdf        i_3 = *i_31
00447be6        int32_t eax_28 = *arg1
00447be8        *ecx_13 = 0x2e
00447bf1        ecx_13[1] = 0x74
00447bfa        ecx_13[2] = 0x78
00447c03        ecx_13[3] = 0x74
00447c06        ecx_13[4] = 0
00447c19        copy_segment_definition_to_level_slot(&var_400, &arg1[eax_28 * 0x1088 + 1])
00447c22        char* ecx_18 = &i_9[3]
00447c25        void var_500
00447c25        char* edx_16 = &var_500
00447c2c        char* var_70c = ecx_18
00447c30        char i_4 = *ecx_18
00447c34        while (i_4 s>= 0x20)
00447c36        *edx_16 = i_4
00447c38        edx_16 = &edx_16[1]
00447c39        ecx_18 = &ecx_18[1]
00447c3a        var_70c = ecx_18
00447c3e        i_4 = *ecx_18
00447c4b        *edx_16 = 0
00447c54        char* eax_30 = find_case_insensitive_substring("Angle=", &var_500)
00447c5e        var_70c = eax_30
00447c62        if (eax_30 == 0)
00447cb9        arg1[*arg1 * 0x1088 + 0x1006] = 0
00447c73        var_70c = find_case_insensitive_substring("=", eax_30)
00447c7d        int32_t var_708_4 = sub_44e710(&var_70c)
00447c83        unimplemented  {fild st0, dword [esp+0x24]}
00447c8f        unimplemented  {fmul st0, dword [0x4973b8]}
00447c9f        arg1[*arg1 * 0x1088 + 0x1006] = fconvert.s(unimplemented  {fstp dword [edx+esi+0x4018], st0})
00447c9f        unimplemented  {fstp dword [edx+esi+0x4018], st0}
00447cde        arg1[*arg1 * 0x1088 + 0x1007].b = 0
00447ce6        char* eax_36 = find_case_insensitive_substring("Message=", &var_500)
00447cf0        var_70c = eax_36
00447cf4        if (eax_36 != 0)
00447d08        char* eax_38 = &find_case_insensitive_substring("=", eax_36)[1]
00447d09        var_70c = eax_38
00447d10        if (*eax_38 != 0x22)
00447ef6        report_errorf("Need " after Message=")
00447f08        return 0
00447d16        char* eax_39 = &eax_38[1]
00447d17        var_70c = eax_39
00447d1b        char* edx_29 = eax_39
00447d20        if (*eax_39 != 0x22)
00447d29        char i_5
00447d22        i_5 = edx_29[1]
00447d25        edx_29 = &edx_29[1]
00447d29        do while (i_5 != 0x22)
00447d3e        char* ecx_26 = &arg1[*arg1 * 0x1088 + 0x1007]
00447d45        while (eax_39 u< edx_29)
00447d47        eax_39.b = *eax_39
00447d49        *ecx_26 = eax_39.b
00447d4f        ecx_26 = &ecx_26[1]
00447d50        eax_39 = &var_70c[1]
00447d53        var_70c = eax_39
00447d59        *ecx_26 = 0
00447d6e        var_70c = find_case_insensitive_substring("Duration=", &var_500)
00447d86        arg1[*arg1 * 0x1088 + 0x1087] = 0x40800000
00447d8d        char* eax_43 = var_70c
00447d93        if (eax_43 != 0)
00447da1        var_70c = &find_case_insensitive_substring("=", eax_43)[1]
00447daa        parse_next_float32(&var_70c)
00447daa        unimplemented  {call 0x431f20}
00447dc3        arg1[*arg1 * 0x1088 + 0x1087] = fconvert.s(unimplemented  {fstp dword [ecx+esi+0x421c], st0})
00447dc3        unimplemented  {fstp dword [ecx+esi+0x421c], st0}
00447ddc        var_70c = find_case_insensitive_substring("Sample=", &var_500)
00447df5        *((*arg1 + 1) * 0x4220 + arg1) = 0xffffffff
00447dfc        char* eax_50 = var_70c
00447e02        if (eax_50 != 0)
00447e13        char* eax_52 = &find_case_insensitive_substring("=", eax_50)[2]
00447e19        var_70c = eax_52
00447e1d        void var_480
00447e1d        char* edx_36 = &var_480
00447e24        char i_6 = *eax_52
00447e29        while (i_6 != 0x22)
00447e2b        *edx_36 = i_6
00447e2d        edx_36 = &edx_36[1]
00447e2e        eax_52 = &eax_52[1]
00447e2f        var_70c = eax_52
00447e33        i_6 = *eax_52
00447e3a        *edx_36 = 0
00447e5f        *((*arg1 + 1) * 0x4220 + arg1) = sub_432fc0(&var_480)
00447e78        if (*((*arg1 + 1) * 0x4220 + arg1) == 0xffffffff)
00447e85        char (* var_724_41)[0x200] = &var_700
00447e86        void* var_728_3 = &var_480
00447e8c        report_errorf("Cannot find sample %s in %s")
00447e96        char* i_36 = i_9
00447e9c        *arg1 += 1
00447e9e        i_31 = sub_44e690(i_36)
00447ea8        i_9 = i_31
00447eac        if (i_31 == 0)
00447f12        char* var_724_44 = arg2
00447f18        report_errorf("Unexpected end of file in %s")
00447f2a        return 0
00447ec2        char* i_32 = find_case_insensitive_substring("First:", 0x74ec78)
00447ecc        i_9 = i_32
00447ed0        if (i_32 == 0)
00447ed6        char (* var_724_43)[0x200] = &var_700
00447edc        report_errorf("Cannot find 'First:' in %s")
00447eee        return 0
00447f2e        char* i_33 = sub_44e690(i_32)
00447f38        i_9 = i_33
00447f3c        if (i_33 != 0)
00447f5d        char i_7 = *i_33
00447f5f        char* ecx_47 = &var_400
00447f69        while (i_7 != 0x2e)
00447f6b        *ecx_47 = i_7
00447f6d        ecx_47 = &ecx_47[1]
00447f6e        i_33 = &i_33[1]
00447f6f        i_9 = i_33
00447f73        i_7 = *i_33
00447f7a        *ecx_47 = 0x2e
00447f8b        ecx_47[1] = 0x74
00447f91        ecx_47[2] = 0x78
00447f95        ecx_47[3] = 0x74
00447f98        ecx_47[4] = 0
00447f9e        copy_segment_definition_to_level_slot(&var_400, &arg1[0x67521])
00447fad        char* i_34 = find_case_insensitive_substring("Last:", 0x74ec78)
00447fb7        i_9 = i_34
00447fbb        if (i_34 == 0)
00447fc1        char (* var_724_48)[0x200] = &var_700
00447fc7        report_errorf("Cannot find 'Last:' in %s")
00447fd9        return 0
00447fdd        char* i_35 = sub_44e690(i_34)
00447fe7        i_9 = i_35
00447feb        if (i_35 == 0)
00447ff1        char (* var_724_50)[0x200] = &var_700
00447ff7        report_errorf("Unexpected end of file in %s")
00448009        return 0
0044800c        char i_8 = *i_35
0044800e        char* ecx_52 = &var_400
00448018        while (i_8 != 0x2e)
0044801a        *ecx_52 = i_8
0044801c        ecx_52 = &ecx_52[1]
0044801d        i_35 = &i_35[1]
0044801e        i_9 = i_35
00448022        i_8 = *i_35
00448029        *ecx_52 = 0x2e
00448033        ecx_52[1] = 0x74
00448038        ecx_52[2] = 0x78
0044803c        ecx_52[3] = 0x74
0044803f        ecx_52[4] = 0
0044805c        return copy_segment_definition_to_level_slot(&var_400, &arg1[0x685a9])
00447f42        char (* var_724_46)[0x200] = &var_700
00447f48        report_errorf("Unexpected end of file in %s")
00447f5a        return 0
