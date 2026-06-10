/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_voice_manager @ 0x448ee0 */

00448ef0        char var_200 = 0
00448ef4        char* eax = get_archive_data_base()
00448f04        load_file_bytes_from_archive_or_fs("Voice/_Voice.txt", eax, nullptr)
00448f0c        int32_t ebp = 0
00448f0e        int32_t var_20c = 0
00448f22        char* cursor
00448f22        while (true)
00448f22        rstrcpy_checked_ascii(&var_200, "Set:")
00448f2d        if (ebp u<= 0xf)
00448f33        char* edi_1
00448f33        switch (ebp)
00448f3e        case 0
00448f3e        edi_1 = "Damage"
00448f4c        case 1
00448f4c        edi_1 = "Dying"
00448f5a        case 2
00448f5a        edi_1 = "Enemies"
00448f68        case 3
00448f68        edi_1 = "Fall"
00448f76        case 4
00448f76        edi_1 = "Misc"
00448f81        case 5
00448f81        edi_1 = "PowerUp"
00448f8c        case 6
00448f8c        edi_1 = "Slow"
00448f97        case 7
00448f97        edi_1 = "Start"
00448fa2        case 8
00448fa2        edi_1 = "Victory"
00448fad        case 9
00448fad        edi_1 = "Ouch"
00448fb8        case 0xa
00448fb8        edi_1 = "Package"
00448fc3        case 0xb
00448fc3        edi_1 = "Slugged"
00448fce        case 0xc
00448fce        edi_1 = "WormTunnel"
00448fd9        case 0xd
00448fd9        edi_1 = "Tutorial"
00448fe4        case 0xe
00448fe4        edi_1 = "Postal"
00448fef        case 0xf
00448fef        edi_1 = "SuperTramp"
00448ff4        int32_t i = 0xffffffff
00448ff9        while (i != 0)
00448ff9        bool cond:2_1 = 0 != *edi_1
00448ff9        edi_1 = &edi_1[1]
00448ff9        i -= 1
00448ff9        if (not(cond:2_1))
00448ff9        break
00448ffb        int32_t ecx = not.d(i)
00449001        char* edi_3 = &var_200
00449005        int32_t i_1 = 0xffffffff
00449008        while (i_1 != 0)
00449008        bool cond:3_1 = 0 != *edi_3
00449008        edi_3 = &edi_3[1]
00449008        i_1 -= 1
00449008        if (not(cond:3_1))
00449008        break
00449010        int32_t esi_2
00449010        int32_t edi_5
00449010        edi_5, esi_2 = __builtin_memcpy(edi_3 - 1, edi_1 - ecx, ecx & 0xfffffffc)
00449017        __builtin_memcpy(edi_5, esi_2, ecx & 3)
00449023        char* cursor_1 = find_case_insensitive_substring(&var_200, eax)
0044902d        cursor = cursor_1
00449031        if (cursor_1 == 0)
0044924b        report_errorf("Cannot find %s in _Voice.txt", &var_200)
0044925d        return 0
0044903d        char* cursor_2 = find_case_insensitive_substring("{", cursor_1)
00449048        cursor = cursor_2
0044904c        char* eax_2 = find_case_insensitive_substring("}", cursor_2)
00449058        char* i_2 = sub_44e690(cursor)
00449060        int32_t edi_6 = 0
00449064        cursor = i_2
00449068        while (i_2 u< eax_2)
0044906b        edi_6 += 1
0044906c        i_2 = sub_44e690(i_2)
00449081        struct VoiceSet* set = &manager->sets[ebp]
00449086        initialize_voice_set(set, edi_6)
0044908b        int32_t esi_4 = 0
0044908f        if (edi_6 s> 0)
00449099        while (true)
00449099        int32_t eax_4
00449099        eax_4.b = *cursor
004490a1        if (eax_4.b != 9 && eax_4.b != 0x20)
004490b6        char var_100
004490b6        rstrcpy_checked_ascii(&var_100, "Voice/")
004490bb        char* cursor_7 = cursor
004490c2        void var_fa
004490c2        char* eax_5 = &var_fa
004490c9        char i_3 = *cursor_7
004490ce        while (i_3 != 0x2e)
004490d0        *eax_5 = i_3
004490d2        eax_5 = &eax_5[1]
004490d3        cursor_7 = &cursor_7[1]
004490d4        cursor = cursor_7
004490d8        i_3 = *cursor_7
004490df        *eax_5 = 0x2e
004490e4        eax_5[1] = 0x6f
004490e8        eax_5[2] = 0x67
004490ec        eax_5[3] = 0x67
004490ef        eax_5[4] = 0
00449101        cursor = sub_44e690(cursor_7)
00449110        set->bites[esi_4] = register_sound_sample(&var_100, 1)
00449113        esi_4 += 1
00449116        if (esi_4 s>= edi_6)
00449116        break
00449116        continue
004490a3        cursor = &cursor[1]
00449121        bool cond:4_1 = var_20c + 1 s< 0x10
00449124        var_20c += 1
00449128        if (not(cond:4_1))
00449128        break
00448f14        ebp = var_20c
00449138        char* cursor_3 = find_case_insensitive_substring("NormalizeMusic:", eax)
00449143        cursor = cursor_3
00449150        cursor = find_case_insensitive_substring(":", cursor_3)
0044916e        float var_204 = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00999999978f))
00449172        char* cursor_4 = find_case_insensitive_substring("NormalizeSfx:", eax)
0044917d        cursor = cursor_4
0044918a        cursor = find_case_insensitive_substring(":", cursor_4)
004491a8        float var_20c_1 = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00999999978f))
004491ac        char* cursor_5 = find_case_insensitive_substring("NormalizeVoice:", eax)
004491b7        cursor = cursor_5
004491c0        cursor = find_case_insensitive_substring(":", cursor_5)
004491f7        set_audio_normalization_scales(0x753c58, var_204, var_20c_1, fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00999999978f)))
00449202        char* cursor_6 = find_case_insensitive_substring("Frequency:", eax)
0044920d        cursor = cursor_6
0044921a        cursor = find_case_insensitive_substring(":", cursor_6)
0044922b        manager->global_frequency_seconds = fconvert.s(parse_next_float32(&cursor))
00449240        return reset_voice_manager(manager)
