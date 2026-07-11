/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_star_positions @ 0x434800 */

00434807        int32_t i = 0
0043480b        if (manager->count s<= 0)
0043480b        return
00434813        int32_t edx_1 = 0
00434818        void* eax_1 = manager->entries + edx_1
00434820        *(eax_1 + 0x24) = fconvert.s(fconvert.t(*(eax_1 + 0x20)) + fconvert.t(*(eax_1 + 0x24)))
00434823        struct StarManagerEntry* entries = manager->entries
00434826        long double x87_r7_3 = fconvert.t(*(&entries->travel_distance + edx_1))
0043482a        long double temp1_1 = fconvert.t(35f)
0043482a        x87_r7_3 - temp1_1
00434839        if ((((x87_r7_3 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp1_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043483f        *(&entries->travel_distance + edx_1) = 0
0043484c        *(*(&manager->entries->sprite + edx_1) + 0x8c) = 0
00434856        char* game_base_1 = g_game_base
0043489f        float var_20_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(game_base_1 + 0x6d8)) * fconvert.t(50f))) + fconvert.t(*(game_base_1 + 0x6e8)))
004348b4        float var_1c_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(game_base_1 + 0x6dc)) * fconvert.t(50f))) + fconvert.t(*(game_base_1 + 0x6ec)))
004348b8        float* eax_7 = *(&manager->entries->sprite + edx_1) + 0x48
004348bb        *eax_7 = fconvert.s(fconvert.t(*(game_base_1 + 0x6d4)) * fconvert.t(50f) + fconvert.t(*(game_base_1 + 0x6e4)))
004348c1        eax_7[1] = var_20_1
004348c8        eax_7[2] = var_1c_1
004348ce        void* eax_9 = manager->entries + edx_1
004348d6        int32_t* eax_11 = *(eax_9 + 0x1c) + 0x54
004348db        *eax_11 = *(eax_9 + 0x10)
004348e0        eax_11[1] = *(eax_9 + 0x14)
004348e6        eax_11[2] = *(eax_9 + 0x18)
004348ec        void* eax_13 = manager->entries + edx_1
00434900        float var_8_1 = fconvert.s(fconvert.t(*(eax_13 + 0x14)) * fconvert.t(10f))
00434910        float* eax_15 = *(eax_13 + 0x1c) + 0x48
00434913        float var_4_1 = fconvert.s(fconvert.t(*(eax_13 + 0x18)) * fconvert.t(10f))
00434919        *eax_15 = fconvert.s(fconvert.t(*(eax_13 + 0x10)) * fconvert.t(10f) + fconvert.t(*eax_15))
00434922        eax_15[1] = fconvert.s(fconvert.t(var_8_1) + fconvert.t(eax_15[1]))
0043492c        eax_15[2] = fconvert.s(fconvert.t(var_4_1) + fconvert.t(eax_15[2]))
00434932        void* eax_17 = manager->entries + edx_1
00434940        *(eax_17 + 0x24) = fconvert.s(fconvert.t(*(eax_17 + 0x20)) * fconvert.t(10f) + fconvert.t(*(eax_17 + 0x24)))
00434946        void* eax_19 = manager->entries + edx_1
00434948        i += 1
00434949        edx_1 += 0x2c
00434965        *(*(eax_19 + 0x1c) + 0x38) = fconvert.s((fconvert.t(*(eax_19 + 0x24)) - fconvert.t(2f)) * fconvert.t(*(eax_19 + 0x28)) * fconvert.t(0.0114285713f) * fconvert.t(fade_alpha))
0043496b        do while (i s< manager->count)
00434977        return
