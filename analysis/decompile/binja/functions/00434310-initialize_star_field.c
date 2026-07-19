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
004343ab        struct GameRoot* game_base_1 = g_game_base
004343f4        float var_54_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(game_base_1->overlay_0.bod.transform.basis_forward.y) * fconvert.t(50f))) + fconvert.t(game_base_1->overlay_0.bod.transform.position.y))
00434405        struct Vec3* entry_position = &manager->entries->position + edi_1
0043440d        float var_50_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(game_base_1->overlay_0.bod.transform.basis_forward.z) * fconvert.t(50f))) + fconvert.t(game_base_1->overlay_0.bod.transform.position.z))
00434411        entry_position->x = fconvert.s(fconvert.t(game_base_1->overlay_0.bod.transform.basis_forward.x) * fconvert.t(50f) + fconvert.t(game_base_1->overlay_0.bod.transform.position.x))
00434417        entry_position->y = var_54_1
0043441a        entry_position->z = var_50_1
00434436        float var_5c_1 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
0043443a        int32_t eax_9 = next_math_random_value()
0043444e        struct Vec3* entry_velocity = &manager->entries->velocity + edi_1
0043446e        entry_velocity->x = fconvert.s((float.t(eax_9) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
00434474        entry_velocity->y = var_5c_1
00434477        entry_velocity->z = 0f
00434481        normalize_vector(&manager->entries->velocity + edi_1)
00434488        int32_t eax_12 = next_math_random_value()
00434498        struct Vec3* scaled_velocity = &manager->entries->velocity + edi_1
004344a2        long double x87_r7_22 = float.t(eax_12) * fconvert.t(1.83105476e-05f) + fconvert.t(0.300000012f)
004344ac        scaled_velocity->x = fconvert.s(x87_r7_22 * fconvert.t(scaled_velocity->x))
004344b3        scaled_velocity->y = fconvert.s(x87_r7_22 * fconvert.t(scaled_velocity->y))
004344b9        scaled_velocity->z = fconvert.s(x87_r7_22 * fconvert.t(scaled_velocity->z))
004344bf        *(&manager->entries->velocity.z + edi_1) = 0
004344d2        *(&manager->entries->speed + edi_1) = fconvert.s(vector_magnitude(&manager->entries->velocity + edi_1))
00434500        *(&manager->entries->travel_distance + edi_1) = fconvert.s(float.t(next_math_random_value()) * fconvert.t(0.00106811523f))
00434504        struct StarManagerEntry* entries = manager->entries
00434507        long double x87_r7_27 = fconvert.t(*(&entries->travel_distance + edi_1))
0043450b        struct StarManagerEntry* motion_entry = edi_1 + entries
00434526        long double x87_r6_13 = fconvert.t(motion_entry->speed)
00434565        motion_entry->position.x = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(x87_r7_27 * fconvert.t(motion_entry->velocity.x))) / x87_r6_13)) + fconvert.t(motion_entry->position.x))
00434567        motion_entry->position.y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(x87_r7_27 * fconvert.t(motion_entry->velocity.y))) / x87_r6_13)) + fconvert.t(motion_entry->position.y))
00434572        motion_entry->position.z = fconvert.s(x87_r7_27 * fconvert.t(motion_entry->velocity.z) / x87_r6_13 + fconvert.t(motion_entry->position.z))
00434578        struct Sprite* sprite = *(&manager->entries->sprite + edi_1)
00434585        sprite->flags |= SPRITE_FLAG_ORIENT_TO_MOTION | SPRITE_FLAG_THROTTLE_FACING_REFRESH
0043458f        *(*(&manager->entries->sprite + edi_1) + 0x68) = 0
00434599        *(*(&manager->entries->sprite + edi_1) + 0x6c) = 0
004345a7        *(*(&manager->entries->sprite + edi_1) + 0x78) = 0
004345aa        struct tColour color
004345aa        struct tColour* eax_20 = set_color_rgba(&color, 0.800000012f, 0.800000012f, 1f, 0.400000006f)
004345b8        struct tColour* sprite_color = *(&manager->entries->sprite + edi_1) + 0x2c
004345bb        sprite_color->r = eax_20->r
004345c0        sprite_color->g = eax_20->g
004345c6        sprite_color->b = eax_20->b
004345cc        sprite_color->a = eax_20->a
004345d6        *(*(&manager->entries->sprite + edi_1) + 0x60) = 0x3f4ccccd
004345e0        struct Sprite* size_sprite = *(&manager->entries->sprite + edi_1)
004345e7        size_sprite->size_end = size_sprite->size_start
004345ea        struct StarManagerEntry* entries_1 = manager->entries
00434603        *(*(&entries_1->sprite + edi_1) + 0x88) = fconvert.s((fconvert.t(*(&entries_1->speed + edi_1)) + fconvert.t(1f)) * fconvert.t(4f))
0043460c        struct StarManagerEntry* velocity_entry = edi_1 + manager->entries
00434615        struct Vec3* sprite_velocity = &velocity_entry->sprite->velocity
0043461a        sprite_velocity->x = velocity_entry->velocity.x
0043461f        sprite_velocity->y = velocity_entry->velocity.y
00434625        sprite_velocity->z = velocity_entry->velocity.z
0043462b        struct StarManagerEntry* position_entry = manager->entries + edi_1
00434633        struct Vec3* sprite_position = &position_entry->sprite->position
00434636        i_1 += 1
00434639        sprite_position->x = position_entry->position.x
0043463e        sprite_position->y = position_entry->position.y
00434644        sprite_position->z = position_entry->position.z
0043464e        *(*(&manager->entries->sprite + edi_1) + 0x8c) = 0
00434659        do while (i_1 s< manager->count)
00434663        (*manager->bod.bod.vtable)()
0043466c        return
