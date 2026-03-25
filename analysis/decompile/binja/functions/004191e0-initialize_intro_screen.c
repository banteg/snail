/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_intro_screen @ 0x4191e0 */

004191ea        int32_t i = 0
004191ec        void* var_18c = &data_4dfb08
004191f1        int32_t var_190 = 0
004191f9        cache_music_file("music/introtext.ogg")
00419211        int32_t eax_1 = load_landscape_script_by_name(data_4df904 + 0x106c218, "SpaceRed.txt")
0041921d        void* eax_2 = data_4df904
00419230        change_backdrop(eax_2 + 0x4ec10, eax_2 + eax_1 * 0x124 + 0x106c7bc, 0)
00419242        set_border_justify_centre(data_4df904 + 0xb4c, 0)
00419252        unhide_star_field(data_4df904 + 0x4f33c)
00419260        char* eax_4 = load_file_bytes(arg2, nullptr)
0041929e        arg1[3] = data_4df934.d
004192a1        void var_140
004192a1        int32_t* eax_5 = initialize_matrix_from_values(&var_140, 0x3f800000, 0, 0, 0, 0, 0x3f226794, 0x3f45e3fc, 0, 0, 0xbf45e3fc, 0x3f226794, 0, 0, 0, 0, 0x3f800000)
004192b9        __builtin_memcpy(data_4df904 + 0x15c, eax_5, 0x40)
004192c1        *(data_4df904 + 0x284) = 0x42c80000
004192cb        *arg1 = 0
004192ce        arg1[1] = 0x3ada740e
004192e0        release_mouse_cursor(data_4df904 + 0x290)
004192e5        char* esi_1 = eax_4
004192e9        arg1[2] = 0
004192f2        int32_t var_16c = 0x3e4ccccd
004192fa        arg1[5] = 0
004192fd        char* eax_7 = find_case_insensitive_substring("Text Start:", esi_1)
00419308        char* var_178 = eax_7
00419312        var_178 = &find_case_insensitive_substring(":", eax_7)[1]
0041931c        char* eax_10 = find_case_insensitive_substring("Text End:", esi_1)
00419321        char* ecx_10 = var_178
0041932a        char* var_144 = eax_10
0041932e        if (ecx_10 u< eax_10)
0041933a        int32_t* var_168_1 = &arg1[0x900f]
0041933e        eax_10.b = *ecx_10
00419340        char* edi_1 = nullptr
00419344        int32_t var_164_1 = 0
00419348        char* esi_2 = ecx_10
0041934a        int16_t top
0041934a        if (eax_10.b == 0x2a)
00419350        char* ecx_11 = &ecx_10[1]
00419351        void var_100
00419351        char* eax_11 = &var_100
00419358        var_178 = ecx_11
0041935c        int32_t* edx_4
0041935c        edx_4.b = *ecx_11
00419361        while (edx_4.b != 0x2e)
00419363        *eax_11 = edx_4.b
00419365        eax_11 = &eax_11[1]
00419366        ecx_11 = &ecx_11[1]
00419367        var_178 = ecx_11
0041936b        edx_4.b = *ecx_11
00419372        *eax_11 = 0x2e
00419376        eax_11[1] = 0x74
0041937a        eax_11[2] = 0x67
0041937f        eax_11[3] = 0x61
00419382        eax_11[4] = 0
00419389        var_178 = &ecx_11[1]
0041938e        parse_next_float32(&var_178)
0041938e        unimplemented  {call 0x431f20}
00419393        float var_170_1 = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
00419393        unimplemented  {fstp dword [esp+0x1c], st0}
0041939c        parse_next_float32(&var_178)
0041939c        unimplemented  {call 0x431f20}
004193a1        float var_174_1 = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
004193a1        unimplemented  {fstp dword [esp+0x1c], st0}
004193b3        void* var_194_1 = &var_100
004193ba        void texture_path
004193ba        sub_48b32c(&texture_path, "Intro/%s")
004193bf        arg1[5]
004193da        if ((0x200 & arg1[arg1[5] * 0x24 + 7]) == 0)
004193eb        void* edx_5 = data_4df904
004193f7        void* edx_6 = *(edx_5 + 0x5ac)
004193ff        if (edx_6 != 0)
0041940d        *(edx_6 + 8) = &arg1[arg1[5] * 0x24 + 6]
00419410        void* edx_7 = *(edx_5 + 0x5ac)
00419415        *(*(edx_7 + 8) + 0xc) = edx_7
0041941a        void* edx_9 = *(*(edx_5 + 0x5ac) + 8)
0041941d        *(edx_5 + 0x5ac) = edx_9
0041941f        *(edx_9 + 8) = 0
00419401        *(edx_5 + 0x5ac) = &arg1[arg1[5] * 0x24 + 6]
00419403        arg1[arg1[5] * 0x24 + 8] = 0
00419408        *(*(edx_5 + 0x5ac) + 0xc) = 0
00419422        arg1[arg1[5] * 0x24 + 7] |= 0x200
004193e1        report_errorf("List ADD")
00419439        set_bod_object(&arg1[arg1[5] * 0x24 + 6], *var_168_1)
00419462        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x5c) + 0xc) = get_or_create_texture_ref(&data_4b7790, &texture_path, 0, 0)
00419472        set_matrix_identity(&arg1[arg1[5] * 0x24 + 0x14])
00419477        int32_t eax_21 = arg1[5]
00419491        int32_t var_148_1 = 0
0041949c        unimplemented  {fld st0, dword [esp+0x14]}
004194ab        unimplemented  {fmul st0, dword [0x497228]}
004194b1        arg1[eax_21 * 0x24 + 0x20] = 0
004194b7        arg1[eax_21 * 0x24 + 0x21] = 0xc0800000
004194ba        float var_168_2 = fconvert.s(unimplemented  {fstp dword [esp+0x20], st0})
004194ba        unimplemented  {fstp dword [esp+0x20], st0}
004194be        unimplemented  {fld st0, dword [esp+0x1c]}
004194c2        arg1[eax_21 * 0x24 + 0x22] = var_148_1
004194c8        unimplemented  {fsub st0, dword [esp+0x20]}
004194d2        unimplemented  {fadd dword [eax+ebp+0x88]}
004194e0        arg1[arg1[5] * 0x24 + 0x22] = fconvert.s(unimplemented  {fstp dword [eax], st0})
004194e0        unimplemented  {fstp dword [eax], st0}
004194ef        set_color_white()
004194f7        unimplemented  {fld st0, dword [esp+0x18]}
00419501        unimplemented  {fmul st0, dword [0x497228]}
00419507        arg1[arg1[5] * 0x24 + 0x13] = 0x3f7fbe77
00419518        arg1[arg1[5] * 0x24 + 0x29].b = 0xff
00419530        **(arg1[arg1[5] * 0x24 + 0xf] + 0x38) = fconvert.s(unimplemented  {fst dword [eax], st0})
00419535        unimplemented  {fld st0, dword [esp+0x18]}
0041953f        unimplemented  {fmul st0, dword [0x497380]}
00419550        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 8) = var_168_2
00419563        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 0xc) = fconvert.s(unimplemented  {fst dword [ecx+0xc], st0})
0041957a        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 0x14) = var_168_2
0041958d        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 0x18) = fconvert.s(unimplemented  {fstp dword [edx+0x18], st0})
0041958d        unimplemented  {fstp dword [edx+0x18], st0}
00419593        unimplemented  {fld st0, dword [esp+0x14]}
00419597        unimplemented  {fmul st0, dword [0x497380]}
004195a7        float var_170_2 = fconvert.s(unimplemented  {fst dword [esp+0x18], st0})
004195ae        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 0x20) = fconvert.s(unimplemented  {fstp dword [edx+0x20], st0})
004195ae        unimplemented  {fstp dword [edx+0x20], st0}
004195c1        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 0x24) = fconvert.s(unimplemented  {fstp dword [edx+0x24], st0})
004195c1        unimplemented  {fstp dword [edx+0x24], st0}
004195d8        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 0x2c) = var_170_2
004195db        int32_t eax_54 = arg1[5]
004195eb        arg1[eax_54 * 0x24 + 0x28] = 0
004195ee        arg1[eax_54 * 0x24 + 0x27] = 0
004195f1        arg1[eax_54 * 0x24 + 0x26] = 0
00419604        eax_10, edx_4 = (*arg1[arg1[5] * 0x24 + 6])()
00419606        unimplemented  {fld st0, dword [esp+0x1c]}
0041960a        ecx_10 = var_178
00419614        unimplemented  {fsub st0, dword [esp+0x14]}
00419618        var_168_1 = &var_168_1[0x24]
00419620        arg1[5] += 1
00419623        eax_10.b = *ecx_10
00419625        float var_16c_1 = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
00419625        unimplemented  {fstp dword [esp+0x1c], st0}
00419625        top -= 1
0041962b        if (eax_10.b != 0)
00419633        while (eax_10.b != 0xd)
00419639        ecx_10 = &ecx_10[1]
0041963a        var_178 = ecx_10
0041963e        eax_10.b = *ecx_10
00419642        if (eax_10.b == 0)
00419642        break
0041964b        if (eax_10.b != 0)
00419653        while (eax_10.b != 0xd)
00419662        unimplemented  {fld st0, dword [esp+0x24]}
00419666        unimplemented  {fadd dword [eax*4+0x7770e8]}
0041966d        edi_1 = &edi_1[1]
0041966e        ecx_10 = &var_178[1]
0041966f        var_178 = ecx_10
00419673        eax_10.b = *ecx_10
00419675        float var_164_2 = fconvert.s(unimplemented  {fstp dword [esp+0x24], st0})
00419675        unimplemented  {fstp dword [esp+0x24], st0}
0041967b        if (eax_10.b == 0)
0041967b        break
0041967f        if (edi_1 s> 0)
00419685        unimplemented  {fld st0, dword [esp+0x24]}
00419689        unimplemented  {fmul st0, dword [0x497228]}
0041968f        int32_t var_160_1 = 0
00419697        int32_t var_15c_1 = 0xc0800000
0041969f        int32_t var_158_1 = 0
004196a7        char* var_170_3 = edi_1
004196ab        unimplemented  {fmul st0, dword [0x497250]}
004196b1        float var_174_2 = fconvert.s(unimplemented  {fstp dword [esp+0x14], st0})
004196b1        unimplemented  {fstp dword [esp+0x14], st0}
00419849        bool cond:3_1
004196b5        arg1[5]
004196c9        int32_t eax_60
004196c9        if (((arg1[arg1[5] * 0x24 + 7]).w:1.b & 2) == 0)
004196da        void* edx_29 = data_4df904
004196e6        void* edx_30 = *(edx_29 + 0x5ac)
004196ee        if (edx_30 != 0)
004196fc        *(edx_30 + 8) = &arg1[arg1[5] * 0x24 + 6]
004196ff        void* edx_31 = *(edx_29 + 0x5ac)
00419704        *(*(edx_31 + 8) + 0xc) = edx_31
00419709        void* edx_33 = *(*(edx_29 + 0x5ac) + 8)
0041970c        *(edx_29 + 0x5ac) = edx_33
0041970e        *(edx_33 + 8) = 0
004196f0        *(edx_29 + 0x5ac) = &arg1[arg1[5] * 0x24 + 6]
004196f2        arg1[arg1[5] * 0x24 + 8] = 0
004196f7        *(*(edx_29 + 0x5ac) + 0xc) = 0
00419714        eax_60:1.b = arg1[arg1[5] * 0x24 + 7]:1.b | 2
00419717        arg1[arg1[5] * 0x24 + 7] = eax_60
004196d0        report_errorf("List ADD")
0041971a        eax_60.b = *esi_2
0041971d        int32_t eax_63 = font_slot_index_for_char(eax_60.b)
00419743        set_bod_object(&arg1[arg1[5] * 0x24 + 6], *(eax_63 * 0x38 + &data_77550c))
00419755        set_matrix_identity(&arg1[arg1[5] * 0x24 + 0x14])
0041975a        int32_t eax_68 = arg1[5]
00419761        unimplemented  {fld st0, dword [esp+0x14]}
00419776        arg1[eax_68 * 0x24 + 0x20] = var_160_1
0041977c        arg1[eax_68 * 0x24 + 0x21] = var_15c_1
0041977f        arg1[eax_68 * 0x24 + 0x22] = var_158_1
0041978b        unimplemented  {fadd dword [edx+ebp+0x80]}
00419799        arg1[arg1[5] * 0x24 + 0x20] = fconvert.s(unimplemented  {fstp dword [eax], st0})
00419799        unimplemented  {fstp dword [eax], st0}
0041979e        unimplemented  {fld st0, dword [esp+0x1c]}
004197a8        unimplemented  {fadd dword [eax+ebp+0x88]}
004197b6        arg1[arg1[5] * 0x24 + 0x22] = fconvert.s(unimplemented  {fstp dword [eax], st0})
004197b6        unimplemented  {fstp dword [eax], st0}
004197c5        set_color_white()
004197d3        arg1[arg1[5] * 0x24 + 0x13] = 0x3f7fbe77
004197db        int32_t eax_78 = arg1[5]
004197eb        arg1[eax_78 * 0x24 + 0x28] = 0
004197ee        arg1[eax_78 * 0x24 + 0x27] = 0
004197f1        arg1[eax_78 * 0x24 + 0x26] = 0
004197f6        int32_t edx_41
004197f6        edx_41.b = *esi_2
004197fe        arg1[arg1[5] * 0x24 + 0x29].b = edx_41.b
00419816        (*arg1[arg1[5] * 0x24 + 6])()
00419820        unimplemented  {fld st0, dword [eax*4+0x7770e8]}
00419827        unimplemented  {fmul st0, dword [0x497250]}
00419833        esi_2 = &esi_2[1]
00419835        unimplemented  {fsubr st0, dword [esp+0x14]}
00419839        arg1[5] += 1
0041983c        float var_174_3 = fconvert.s(unimplemented  {fstp dword [esp+0x14], st0})
0041983c        unimplemented  {fstp dword [esp+0x14], st0}
0041983c        top -= 1
00419844        cond:3_1 = var_170_3 != 1
00419845        var_170_3 -= 1
00419849        do while (cond:3_1)
0041984f        ecx_10 = var_178
00419856        if (*ecx_10 == 0xd)
00419858        unimplemented  {fld st0, dword [esp+0x1c]}
0041985c        unimplemented  {fsub st0, dword [0x497220]}
00419862        ecx_10 = &ecx_10[2]
00419865        var_178 = ecx_10
00419869        float var_16c_2 = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
00419869        unimplemented  {fstp dword [esp+0x1c], st0}
00419871        do while (ecx_10 u< var_144)
00419877        esi_1 = eax_4
00419881        char* eax_88 = find_case_insensitive_substring("Duration:", esi_1)
0041988c        var_178 = eax_88
00419899        var_178 = find_case_insensitive_substring(":", eax_88)
0041989e        parse_next_float32(&var_178)
0041989e        unimplemented  {call 0x431f20}
004198a3        arg1[4] = fconvert.s(unimplemented  {fst dword [ebp+0x10], st0})
004198a6        unimplemented  {fmul st0, dword [0x497298]}
004198b4        int32_t var_160_2 = 0
004198bc        unimplemented  {fdivr st0, dword [0x497220]}
004198ca        unimplemented  {fld st0, dword [0x497218]}
004198d0        unimplemented  {fsub st0, dword [esp+0x1c]}
004198d4        unimplemented  {fmulp st1, st0}
004198d4        unimplemented  {fmulp st1, st0}
004198d6        float var_158_2 = fconvert.s(unimplemented  {fstp dword [esp+0x30], st0})
004198d6        unimplemented  {fstp dword [esp+0x30], st0}
004198da        if (arg1[5] s> 0)
004198e0        int32_t* eax_91 = &arg1[0x26]
004198ea        int32_t* edx_43 = eax_91
004198ec        i += 1
004198ed        eax_91 = &eax_91[0x24]
004198f2        *edx_43 = var_160_2
004198f8        edx_43[1] = 0
004198fb        edx_43[2] = var_158_2
00419903        do while (i s< arg1[5])
00419918        return free_tracked_memory(esi_1)
