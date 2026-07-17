/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: shuffle_voice_set @ 0x448e60 */

00448e60        struct VoiceSet* set_1 = set
00448e67        int32_t i_1 = 0x64
00448eb5        int32_t i
00448e81        int32_t eax_2
00448e81        int16_t x87control
00448e81        int16_t x87control_1
00448e81        eax_2, x87control_1 = ftol(x87control, float.t(next_math_random_value()) * float.t(set->sample_count) * fconvert.t(3.05175781e-05f))
00448e9d        int32_t eax_4
00448e9d        eax_4, x87control = ftol(x87control_1, float.t(next_math_random_value()) * float.t(set->sample_count) * fconvert.t(3.05175781e-05f))
00448ea2        int32_t* playlist = set->playlist
00448ea5        i = i_1
00448ea5        i_1 -= 1
00448ea9        int32_t edx_1 = playlist[eax_2]
00448eac        playlist[eax_2] = playlist[eax_4]
00448eb2        set->playlist[eax_4] = edx_1
00448eb5        do while (i != 1)
00448ebc        return
