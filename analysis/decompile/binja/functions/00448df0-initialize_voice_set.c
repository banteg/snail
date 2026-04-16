/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_voice_set @ 0x448df0 */

00448dfc        set->sample_count = arg2
00448dfe        set->next_index = 0
00448e09        int32_t* eax_1 = allocate_tracked_memory(arg2 << 2, "Playlist")
00448e15        uint32_t ecx_1 = set->sample_count << 2
00448e19        set->playlist = eax_1
00448e1c        int32_t* eax_2 = allocate_tracked_memory(ecx_1, "VoiceBite")
00448e21        uint32_t sample_count = set->sample_count
00448e23        set->bites = eax_2
00448e29        int32_t i = 0
00448e2d        set->cooldown = 0f
00448e34        set->cooldown_step = 0.00416666688f
00448e3b        if (sample_count s> 0)
00448e40        set->playlist[i] = i
00448e45        i += 1
00448e48        do while (i s< set->sample_count)
00448e52        return shuffle_voice_set(set)
