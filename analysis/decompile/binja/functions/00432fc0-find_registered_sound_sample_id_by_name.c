/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: find_registered_sound_sample_id_by_name @ 0x432fc0 */

00432fcb        int32_t i = 0
00432fd0        if (g_registered_sound_sample_count s> 0)
00432fd2        RegisteredSoundSampleName* edi_1 = &g_registered_sound_sample_names
00432fe3        if (find_case_insensitive_substring(sample_name, edi_1) != 0)
0043300e        return i
00432fea        i += 1
00432feb        edi_1 = &edi_1[1]
00432ff3        do while (i s< g_registered_sound_sample_count)
00432ffb        report_errorf("Cannot Find Sample %s", sample_name)
00433008        return 0
