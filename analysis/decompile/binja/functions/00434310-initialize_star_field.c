/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_star_field @ 0x434310 */

0043431e        int32_t i = 0
00434322        if (manager->count s> 0)
00434324        int32_t ebx_1 = 0
0043433b        i += 1
0043433c        *(&manager->entries->sprite + ebx_1) = allocate_sprite(&g_sprite_manager, 2, 0x20, 0xffffffff, 0xffffffff)
00434343        ebx_1 += 0x2c
00434348        do while (i s< manager->count)
0043434d        int32_t i_1 = 0
0043434f        bool cond:0 = manager->count s<= 0
00434351        manager->fade = 1f
00434358        if (not(cond:0))
0043436b        int32_t* edi_1 = i_1 * 0x2c
00434370        *(edi_1 + manager->entries) = 1
00434377        if (i_1 != 0)
004343a7        *(&manager->entries->alpha_scale + edi_1) = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351572e-06f) + fconvert.t(0.400000006f))
0043437c        manager->entries->alpha_scale = 0.400000006f
004343ab        char* game_base_1 = g_game_base
004343f4        float var_54_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(game_base_1 + 0x6d8)) * fconvert.t(50f))) + fconvert.t(*(game_base_1 + 0x6e8)))
00434405        float* ecx_2 = &manager->entries->position + edi_1
0043440d        float var_50_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(game_base_1 + 0x6dc)) * fconvert.t(50f))) + fconvert.t(*(game_base_1 + 0x6ec)))
00434411        *ecx_2 = fconvert.s(fconvert.t(*(game_base_1 + 0x6d4)) * fconvert.t(50f) + fconvert.t(*(game_base_1 + 0x6e4)))
00434417        ecx_2[1] = var_54_1
0043441a        ecx_2[2] = var_50_1
00434436        float var_5c_1 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
0043443a        int32_t eax_9 = next_math_random_value()
0043444e        float* edx_5 = &manager->entries->velocity + edi_1
0043446e        *edx_5 = fconvert.s((float.t(eax_9) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
00434474        edx_5[1] = var_5c_1
00434477        edx_5[2] = 0
00434481        normalize_vector(&manager->entries->velocity + edi_1)
00434488        int32_t eax_12 = next_math_random_value()
00434498        float* eax_13 = &manager->entries->velocity + edi_1
004344a2        long double x87_r7_22 = float.t(eax_12) * fconvert.t(1.83105476e-05f) + fconvert.t(0.300000012f)
004344ac        *eax_13 = fconvert.s(x87_r7_22 * fconvert.t(*eax_13))
004344b3        eax_13[1] = fconvert.s(x87_r7_22 * fconvert.t(eax_13[1]))
004344b9        eax_13[2] = fconvert.s(x87_r7_22 * fconvert.t(eax_13[2]))
004344bf        *(&manager->entries->velocity.z + edi_1) = 0
004344d2        *(&manager->entries->speed + edi_1) = fconvert.s(vector_magnitude(&manager->entries->velocity + edi_1))
00434500        *(&manager->entries->travel_distance + edi_1) = fconvert.s(float.t(next_math_random_value()) * fconvert.t(0.00106811523f))
00434504        struct StarManagerEntry* entries = manager->entries
00434507        long double x87_r7_27 = fconvert.t(*(&entries->travel_distance + edi_1))
0043450b        void* eax_17 = edi_1 + entries
00434526        long double x87_r6_13 = fconvert.t(*(eax_17 + 0x20))
0043455a        float var_3c_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(x87_r7_27 * fconvert.t(*(eax_17 + 0x14)))) / x87_r6_13)) + fconvert.t(*(eax_17 + 8)))
00434562        long double x87_r7_31 = x87_r7_27 * fconvert.t(*(eax_17 + 0x18)) / x87_r6_13 + fconvert.t(*(eax_17 + 0xc))
00434565        *(eax_17 + 4) = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(x87_r7_27 * fconvert.t(*(eax_17 + 0x10)))) / x87_r6_13)) + fconvert.t(*(eax_17 + 4)))
00434567        *(eax_17 + 8) = var_3c_1
00434572        *(eax_17 + 0xc) = fconvert.s(x87_r7_31)
00434578        void* eax_20 = *(&manager->entries->sprite + edi_1)
00434585        *(eax_20 + 4) |= 0x402
0043458f        *(*(&manager->entries->sprite + edi_1) + 0x68) = 0
00434599        *(*(&manager->entries->sprite + edi_1) + 0x6c) = 0
004345a7        *(*(&manager->entries->sprite + edi_1) + 0x78) = 0
004345aa        struct tColour color
004345aa        struct tColour* eax_23 = set_color_rgba(&color, 0.800000012f, 0.800000012f, 1f, 0.400000006f)
004345b8        float* edx_13 = *(&manager->entries->sprite + edi_1) + 0x2c
004345bb        *edx_13 = eax_23->r
004345c0        edx_13[1] = eax_23->g
004345c6        edx_13[2] = eax_23->b
004345cc        edx_13[3] = eax_23->a
004345d6        *(*(&manager->entries->sprite + edi_1) + 0x60) = 0x3f4ccccd
004345e0        void* eax_26 = *(&manager->entries->sprite + edi_1)
004345e7        *(eax_26 + 0x64) = *(eax_26 + 0x60)
004345ea        struct StarManagerEntry* entries_1 = manager->entries
00434603        *(*(&entries_1->sprite + edi_1) + 0x88) = fconvert.s((fconvert.t(*(&entries_1->speed + edi_1)) + fconvert.t(1f)) * fconvert.t(4f))
0043460c        void* eax_29 = edi_1 + manager->entries
00434615        int32_t* eax_31 = *(eax_29 + 0x1c) + 0x54
0043461a        *eax_31 = *(eax_29 + 0x10)
0043461f        eax_31[1] = *(eax_29 + 0x14)
00434625        eax_31[2] = *(eax_29 + 0x18)
0043462b        void* eax_33 = manager->entries + edi_1
00434633        int32_t* edx_18 = *(eax_33 + 0x1c) + 0x48
00434636        i_1 += 1
00434639        *edx_18 = *(eax_33 + 4)
0043463e        edx_18[1] = *(eax_33 + 8)
00434644        edx_18[2] = *(eax_33 + 0xc)
0043464e        *(*(&manager->entries->sprite + edi_1) + 0x8c) = 0
00434659        do while (i_1 s< manager->count)
0043466c        return (*manager->bod.bod.vtable)()
