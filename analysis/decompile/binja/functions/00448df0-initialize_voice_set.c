/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_voice_set @ 0x448df0 */

00448dfc        *arg1 = arg2
00448dfe        arg1[1] = 0
00448e09        void* eax_1 = allocate_tracked_memory(arg2 << 2, "Playlist")
00448e15        int32_t ecx_1 = *arg1 << 2
00448e19        arg1[2] = eax_1
00448e1c        void* eax_2 = allocate_tracked_memory(ecx_1, "VoiceBite")
00448e21        int32_t ecx_2 = *arg1
00448e23        arg1[3] = eax_2
00448e29        int32_t i = 0
00448e2d        arg1[4] = 0
00448e34        arg1[5] = 0x3b888889
00448e3b        if (ecx_2 s> 0)
00448e40        *(arg1[2] + (i << 2)) = i
00448e45        i += 1
00448e48        do while (i s< *arg1)
00448e52        return shuffle_voice_set(arg1)
