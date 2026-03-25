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
004192f2        float var_16c = 0.200000003f
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
00419344        float var_164_1 = 0f
00419348        char* esi_2 = ecx_10
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
00419393        float var_170_1 = fconvert.s(parse_next_float32(&var_178))
004193a1        float var_174_1 = fconvert.s(parse_next_float32(&var_178))
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
004194b1        arg1[eax_21 * 0x24 + 0x20] = 0
004194b7        arg1[eax_21 * 0x24 + 0x21] = 0xc0800000
004194ba        float var_168_2 = fconvert.s(fconvert.t(var_174_1) * fconvert.t(0.5f))
004194c2        arg1[eax_21 * 0x24 + 0x22] = var_148_1
004194c5        arg1[5]
004194e0        arg1[arg1[5] * 0x24 + 0x22] = fconvert.s(fconvert.t(var_16c) - fconvert.t(var_168_2) + fconvert.t(arg1[arg1[5] * 0x24 + 0x22]))
004194ef        set_color_white()
00419501        long double x87_r7_9 = fconvert.t(var_170_1) * fconvert.t(0.5f)
00419507        arg1[arg1[5] * 0x24 + 0x13] = 0x3f7fbe77
00419518        arg1[arg1[5] * 0x24 + 0x29].b = 0xff
00419530        **(arg1[arg1[5] * 0x24 + 0xf] + 0x38) = fconvert.s(x87_r7_9)
0041953f        long double x87_r6_2 = fconvert.t(var_170_1) * fconvert.t(-0.5f)
00419550        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 8) = var_168_2
00419563        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 0xc) = fconvert.s(x87_r6_2)
0041957a        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 0x14) = var_168_2
0041958d        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 0x18) = fconvert.s(x87_r6_2)
00419597        long double x87_r6_4 = fconvert.t(var_174_1) * fconvert.t(-0.5f)
004195a7        float var_170_2 = fconvert.s(x87_r6_4)
004195ae        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 0x20) = fconvert.s(x87_r6_4)
004195c1        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 0x24) = fconvert.s(x87_r7_9)
004195d8        *(*(arg1[arg1[5] * 0x24 + 0xf] + 0x38) + 0x2c) = var_170_2
004195db        int32_t eax_54 = arg1[5]
004195eb        arg1[eax_54 * 0x24 + 0x28] = 0
004195ee        arg1[eax_54 * 0x24 + 0x27] = 0
004195f1        arg1[eax_54 * 0x24 + 0x26] = 0
00419604        eax_10, edx_4 = (*arg1[arg1[5] * 0x24 + 6])()
0041960a        ecx_10 = var_178
00419618        var_168_1 = &var_168_1[0x24]
00419620        arg1[5] += 1
00419623        eax_10.b = *ecx_10
00419625        var_16c = fconvert.s(fconvert.t(var_16c) - fconvert.t(var_174_1))
0041962b        if (eax_10.b != 0)
00419633        while (eax_10.b != 0xd)
00419639        ecx_10 = &ecx_10[1]
0041963a        var_178 = ecx_10
0041963e        eax_10.b = *ecx_10
00419642        if (eax_10.b == 0)
00419642        break
0041964b        if (eax_10.b != 0)
00419653        while (eax_10.b != 0xd)
00419666        long double x87_r7_13 = fconvert.t(var_164_1) + fconvert.t(*((font_slot_index_for_char(eax_10.b) << 2) + &data_7770e8))
0041966d        edi_1 = &edi_1[1]
0041966e        ecx_10 = &var_178[1]
0041966f        var_178 = ecx_10
00419673        eax_10.b = *ecx_10
00419675        var_164_1 = fconvert.s(x87_r7_13)
0041967b        if (eax_10.b == 0)
0041967b        break
0041967f        if (edi_1 s> 0)
0041968f        int32_t var_160_1 = 0
00419697        int32_t var_15c_1 = 0xc0800000
0041969f        int32_t var_158_1 = 0
004196a7        char* var_170_3 = edi_1
004196b1        float var_174_2 = fconvert.s(fconvert.t(var_164_1) * fconvert.t(0.5f) * fconvert.t(0.800000012f))
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
00419776        arg1[eax_68 * 0x24 + 0x20] = var_160_1
0041977c        arg1[eax_68 * 0x24 + 0x21] = var_15c_1
0041977f        arg1[eax_68 * 0x24 + 0x22] = var_158_1
00419782        arg1[5]
00419799        arg1[arg1[5] * 0x24 + 0x20] = fconvert.s(fconvert.t(var_174_2) + fconvert.t(arg1[arg1[5] * 0x24 + 0x20]))
0041979b        arg1[5]
004197b6        arg1[arg1[5] * 0x24 + 0x22] = fconvert.s(fconvert.t(var_16c) + fconvert.t(arg1[arg1[5] * 0x24 + 0x22]))
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
00419827        long double x87_r7_22 = fconvert.t(*((font_slot_index_for_char(*esi_2) << 2) + &data_7770e8)) * fconvert.t(0.800000012f)
00419833        esi_2 = &esi_2[1]
00419839        arg1[5] += 1
0041983c        var_174_2 = fconvert.s(fconvert.t(var_174_2) - x87_r7_22)
00419844        cond:3_1 = var_170_3 != 1
00419845        var_170_3 -= 1
00419849        do while (cond:3_1)
0041984f        ecx_10 = var_178
00419856        if (*ecx_10 == 0xd)
00419862        ecx_10 = &ecx_10[2]
00419865        var_178 = ecx_10
00419869        var_16c = fconvert.s(fconvert.t(var_16c) - fconvert.t(1f))
00419871        do while (ecx_10 u< var_144)
00419877        esi_1 = eax_4
00419881        char* eax_89 = find_case_insensitive_substring("Duration:", esi_1)
0041988c        var_178 = eax_89
00419899        var_178 = find_case_insensitive_substring(":", eax_89)
0041989e        long double st0_3 = parse_next_float32(&var_178)
004198a3        arg1[4] = fconvert.s(st0_3)
004198b4        int32_t var_160_2 = 0
004198d6        float var_158_2 = fconvert.s(fconvert.t(1f) / (st0_3 * fconvert.t(60f)) * (fconvert.t(3f) - fconvert.t(var_16c)))
004198da        if (arg1[5] s> 0)
004198e0        int32_t* eax_92 = &arg1[0x26]
004198ea        int32_t* edx_43 = eax_92
004198ec        i += 1
004198ed        eax_92 = &eax_92[0x24]
004198f2        *edx_43 = var_160_2
004198f8        edx_43[1] = 0
004198fb        edx_43[2] = var_158_2
00419903        do while (i s< arg1[5])
00419918        return free_tracked_memory(esi_1)
