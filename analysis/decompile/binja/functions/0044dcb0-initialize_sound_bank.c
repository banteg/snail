/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_sound_bank @ 0x44dcb0 */

0044dcb1        struct SoundBankEntry* entries_1 = entries
0044dcb5        char* path = entries_1->path
0044dcba        if (*path == 0)
0044dcba        return
0044dcbd        struct SoundBankEntry* entries_2 = entries_1
0044dcc9        entries_1 = &entries_1[1]
0044dccc        entries_2->sample_id = register_sound_sample(path, entries_2->normalization_class)
0044dcd2        entries_2 = entries_1
0044dcd4        path = entries_1->path
0044dcd9        do while (*path != 0)
0044dcdd        return
