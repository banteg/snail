/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_slug_hazard_ai @ 0x43f930 */

0043f943        if (slot->owner_game->subgame_pause_gate != 0)
0043f943        return
0043f949        int32_t state = slot->state
0043f952        struct FrameBodList* ecx_15
0043f952        if (state u> 4)
0043fcd9        label_43fcd9:
0043fcd9        slot->sprite->facing_angle = fconvert.s(fconvert.t(slot->owner_player->heading_roll) + fconvert.t(slot->attachment_facing_angle))
0043fcdc        struct Player* owner_player_2 = slot->owner_player
0043fce9        if (owner_player_2->follow_state.active == 1)
0043fceb        struct Sprite* sprite = slot->sprite
0043fcfa        sprite->facing_angle = fconvert.s(fconvert.t(owner_player_2->follow_state.orientation_b) + fconvert.t(sprite->facing_angle))
0043fcff        update_slug_voice_ai(slot)
0043f958        switch (state)
0043f96d        case 1
0043f96d        if (slot->hit_flash_pending != 0 && g_render_queue_active != 0)
0043f96f        float hit_flash_progress_step = slot->hit_flash_progress_step
0043f975        slot->hit_flash_pending = 0
0043f97b        slot->hit_flash_progress = hit_flash_progress_step
0043f981        long double x87_r7_1 = fconvert.t(slot->hit_flash_progress)
0043f987        long double temp1_1 = fconvert.t(0f)
0043f987        x87_r7_1 - temp1_1
0043f992        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0043fa56        slot->blink_progress = fconvert.s(fconvert.t(slot->blink_step) + fconvert.t(slot->blink_progress))
0043fa5c        long double x87_r7_6 = fconvert.t(slot->blink_step)
0043fa62        long double temp3_1 = fconvert.t(0f)
0043fa62        x87_r7_6 - temp3_1
0043fa6d        if ((((x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043fa8f        set_sprite_texture_ref(slot->sprite, 0x77, 0)
0043fa9a        slot->sprite->draw_mode = 0
0043fa77        set_sprite_texture_ref(slot->sprite, 0x76, 0)
0043fa7c        struct Sprite* sprite_1 = slot->sprite
0043fa82        sprite_1->draw_mode.b = 0
0043fa82        sprite_1->draw_mode:1.b = 0
0043fa82        sprite_1->draw_mode:2.b = 0
0043fa82        sprite_1->draw_mode:3.b = 0
0043faba        store_color4f(&slot->sprite->color, 1f, 1f, 1f, 1f)
0043fabf        long double x87_r7_7 = fconvert.t(slot->blink_progress)
0043fac5        long double temp10_1 = fconvert.t(0f)
0043fac5        x87_r7_7 - temp10_1
0043fad0        if ((((x87_r7_7 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp10_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp10_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043faf0        long double x87_r7_9 = fconvert.t(slot->blink_progress)
0043faf6        long double temp13_1 = fconvert.t(1f)
0043faf6        x87_r7_9 - temp13_1
0043fb01        if ((((x87_r7_9 < temp13_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp13_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp13_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043fb03        slot->blink_progress = 1f
0043fb0d        slot->blink_step = -0.166666672f
0043fad2        slot->blink_progress = 0f
0043fae3        int32_t edx_5
0043fae3        long double st0_1
0043fae3        st0_1, edx_5 = advance_blink_random(&g_game_base->subgame.scan_reset)
0043fae8        slot->blink_step = fconvert.s(st0_1)
0043f99e        long double x87_r7_3 = fconvert.t(slot->hit_flash_progress_step) + fconvert.t(slot->hit_flash_progress)
0043f9a4        slot->hit_flash_progress = fconvert.s(x87_r7_3)
0043f9aa        long double temp4_1 = fconvert.t(1f)
0043f9aa        x87_r7_3 - temp4_1
0043f9b5        if ((((x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043fa18        slot->sprite->draw_mode = 5
0043fa25        set_sprite_texture_ref(slot->sprite, 0x78, 0)
0043fa3f        store_color4f(&slot->sprite->color, 1f, 0f, 0f, 0.99000001f)
0043f9b7        struct Sprite* sprite_3 = slot->sprite
0043f9bd        slot->hit_flash_progress = 0f
0043f9c3        slot->blink_progress = 1f
0043f9cd        slot->blink_step = -0.166666672f
0043f9d7        sprite_3->draw_mode = 0
0043f9f7        store_color4f(&slot->sprite->color, 1f, 1f, 1f, 1f)
0043fa05        set_sprite_texture_ref(slot->sprite, 0x77, 0)
0043fb20        long double x87_r7_11 = fconvert.t(slot->owner_player->body.transform.position.z) + fconvert.t(1f)
0043fb26        long double temp11_1 = fconvert.t(slot->world_position.z)
0043fb26        x87_r7_11 - temp11_1
0043fb36        if ((((x87_r7_11 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp11_1) ? 1 : 0) << 0xa | (x87_r7_11 == temp11_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 && slot->player_encounter_latched == 0)
0043fb38        slot->player_encounter_latched = 1
0043fb3f        int32_t eax_6
0043fb3f        int32_t edx_6
0043fb3f        eax_6, edx_6 = next_math_random_value()
0043fb4c        long double x87_r7_13 = float.t(eax_6) * fconvert.t(3.05175781e-05f)
0043fb52        long double temp15_1 = fconvert.t(0.600000024f)
0043fb52        x87_r7_13 - temp15_1
0043fb5d        int16_t x87control
0043fb5d        if ((((x87_r7_13 < temp15_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp15_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp15_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043fb81        play_slug_voice(slot, 0x1e - ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-0.000122070312f)))
0043fb86        struct Player* owner_player = slot->owner_player
0043fb8c        long double x87_r7_16 = fconvert.t(slot->world_position.z)
0043fb8f        long double temp14_1 = fconvert.t(owner_player->body.transform.position.z)
0043fb8f        x87_r7_16 - temp14_1
0043fb9f        if ((((x87_r7_16 < temp14_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_16, temp14_1) ? 1 : 0) << 0xa | (x87_r7_16 == temp14_1 ? 1 : 0) << 0xe):1.b & 1) != 0 && slot->passed_player == 0)
0043fba1        slot->passed_player = 1
0043fbaf        if (slot->engagement_voice_gate == 1)
0043fbb4        long double x87_r7_18 = fconvert.t(owner_player->body.transform.position.z) + fconvert.t(16f)
0043fbba        long double temp17_1 = fconvert.t(slot->world_position.z)
0043fbba        x87_r7_18 - temp17_1
0043fbc2        if ((((x87_r7_18 < temp17_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_18, temp17_1) ? 1 : 0) << 0xa | (x87_r7_18 == temp17_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043fbcf        slot->engagement_voice_gate = 0
0043fbd5        play_voice_manager(0x751498, 2, 1, 0xffffffff)
0043fbe5        struct Vec3* eax_12 = &slot->sprite->position
0043fbe8        int32_t edx_10
0043fbe8        edx_10.b = slot->world_position.x.b
0043fbe8        edx_10:1.b = slot->world_position.x:1.b
0043fbe8        edx_10:2.b = slot->world_position.x:2.b
0043fbe8        edx_10:3.b = slot->world_position.x:3.b
0043fbea        eax_12->x = edx_10
0043fbec        float edx_11
0043fbec        edx_11.b = slot->world_position.y.b
0043fbec        edx_11:1.b = slot->world_position.y:1.b
0043fbec        edx_11:2.b = slot->world_position.y:2.b
0043fbec        edx_11:3.b = slot->world_position.y:3.b
0043fbef        eax_12->y = edx_11
0043fbf2        float ecx_14
0043fbf2        ecx_14.b = slot->world_position.z.b
0043fbf2        ecx_14:1.b = slot->world_position.z:1.b
0043fbf2        ecx_14:2.b = slot->world_position.z:2.b
0043fbf2        ecx_14:3.b = slot->world_position.z:3.b
0043fbf5        eax_12->z = ecx_14
0043fbf8        struct Player* owner_player_1 = slot->owner_player
0043fbfe        long double x87_r7_19 = fconvert.t(slot->world_position.z)
0043fc01        long double temp16_1 = fconvert.t(owner_player_1->interaction_max_z)
0043fc01        x87_r7_19 - temp16_1
0043fc0c        if ((((x87_r7_19 < temp16_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_19, temp16_1) ? 1 : 0) << 0xa | (x87_r7_19 == temp16_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043fc8d        long double x87_r7_20 = fconvert.t(owner_player_1->nuke_effect_progress)
0043fc93        long double temp18_1 = fconvert.t(0f)
0043fc93        x87_r7_20 - temp18_1
0043fc9e        if ((((x87_r7_20 < temp18_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp18_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp18_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043fca2        kill_slug_hazard(slot)
0043fcbc        append_subgame_contact_target(&slot->owner_game->enemy_manager, &slot->world_position, 2f, 1, slot)
0043fcbc        goto label_43fcd9
0043fc0e        int16_t eax_14 = (slot->unknown_00[4].d).w
0043fc11        slot->state = 0
0043fc20        ecx_15 = &g_game_base->active_bod_list
0043fc26        if ((eax_14:1.b & 2) == 0)
0043fc2d        report_errorf("List remove")
0043fc3b        kill_sprite(slot->sprite)
0043fc46        return
0043fc49        if ((eax_14.b & 0x40) != 0)
0043fc50        report_errorf("List remove NEXTBOD")
0043fc5e        kill_sprite(slot->sprite)
0043fc69        return
0043fc6a        void* eax_15
0043fc6a        eax_15.b = slot->unknown_00[0xc]
0043fc6a        eax_15:1.b = slot->unknown_00[0xd]
0043fc6a        eax_15:2.b = slot->unknown_00[0xe]
0043fc6a        eax_15:3.b = slot->unknown_00[0xf]
0043fc6f        if (eax_15 != 0)
0043fc71        int32_t edx_13
0043fc71        edx_13.b = slot->unknown_00[8]
0043fc71        edx_13:1.b = slot->unknown_00[9]
0043fc71        edx_13:2.b = slot->unknown_00[0xa]
0043fc71        edx_13:3.b = slot->unknown_00[0xb]
0043fc74        *(eax_15 + 8) = edx_13
0043fc77        void* eax_16
0043fc77        eax_16.b = slot->unknown_00[8]
0043fc77        eax_16:1.b = slot->unknown_00[9]
0043fc77        eax_16:2.b = slot->unknown_00[0xa]
0043fc77        eax_16:3.b = slot->unknown_00[0xb]
0043fc7c        if (eax_16 == 0)
0043fc7c        goto label_43ffdc
0043fc82        int32_t edx_14
0043fc82        edx_14.b = slot->unknown_00[0xc]
0043fc82        edx_14:1.b = slot->unknown_00[0xd]
0043fc82        edx_14:2.b = slot->unknown_00[0xe]
0043fc82        edx_14:3.b = slot->unknown_00[0xf]
0043fc85        *(eax_16 + 0xc) = edx_14
0043fc88        goto label_43ffe2
0043fe46        case 2
0043fe46        int32_t var_24_4 = 0
0043fe4c        slot->state = 3
0043fe5b        float var_10_1 = fconvert.s(random_float_below(0.300000012f))
0043fe5f        int32_t var_2c_1 = 0
0043fe70        void* var_34_1 = &data_4a4e70
0043fe7a        float var_14_3 = fconvert.s(random_float_below(0.200000003f) + fconvert.t(0.100000001f))
0043fea6        slot->velocity.x = fconvert.s(random_signed_float_below(0.100000001f))
0043feac        slot->velocity.y = var_14_3
0043feb3        slot->velocity.z = var_10_1
0043feb6        int32_t death_toss_direction = slot->death_toss_direction
0043febf        if (death_toss_direction == 1)
0043fec1        long double x87_r7_38 = fconvert.t(slot->velocity.x)
0043fec3        long double temp2_1 = fconvert.t(0f)
0043fec3        x87_r7_38 - temp2_1
0043fec9        long double x87_r7_39 = fconvert.t(slot->velocity.x)
0043fed0        if ((((x87_r7_38 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_38, temp2_1) ? 1 : 0) << 0xa | (x87_r7_38 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0043fed2        x87_r7_39 = fneg(x87_r7_39)
0043fef0        slot->velocity.x = fconvert.s(x87_r7_39)
0043fed9        if (death_toss_direction == 2)
0043fedb        long double x87_r7_40 = fconvert.t(slot->velocity.x)
0043fedd        long double temp7_1 = fconvert.t(0f)
0043fedd        x87_r7_40 - temp7_1
0043fee3        long double x87_r7_41 = fconvert.t(slot->velocity.x)
0043feea        if ((((x87_r7_40 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_40, temp7_1) ? 1 : 0) << 0xa | (x87_r7_40 == temp7_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0043feec        x87_r7_41 = fneg(x87_r7_41)
0043fef0        slot->velocity.x = fconvert.s(fneg(x87_r7_41))
0043fef2        long double x87_r7_42 = fconvert.t(slot->velocity.x)
0043fef4        long double temp6_1 = fconvert.t(0f)
0043fef4        x87_r7_42 - temp6_1
0043feff        int32_t var_14_4
0043feff        if ((((x87_r7_42 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_42, temp6_1) ? 1 : 0) << 0xa | (x87_r7_42 == temp6_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043ff0b        long double x87_r7_43 = fconvert.t(slot->velocity.x)
0043ff0d        long double temp9_1 = fconvert.t(0f)
0043ff0d        x87_r7_43 - temp9_1
0043ff13        var_14_4 = 0
0043ff1c        if ((((x87_r7_43 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_43, temp9_1) ? 1 : 0) << 0xa | (x87_r7_43 == temp9_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
0043ff1e        var_14_4 = 1
0043ff01        var_14_4 = 0xffffffff
0043ff2a        struct SubgameRuntime* owner_game = slot->owner_game
0043ff30        slot->unknown_9c[0] = 0
0043ff30        slot->unknown_9c[1] = 0
0043ff30        slot->unknown_9c[2] = 0
0043ff30        slot->unknown_9c[3] = 0
0043ff3e        slot->velocity.x = fconvert.s(float.t(var_14_4) * fconvert.t(0.200000003f) + fconvert.t(slot->velocity.x))
0043ff43        long double x87_r7_48 = fconvert.t(owner_game->subgame_rate) * fconvert.t(0.00833333377f)
0043ff49        slot->unknown_9c[8] = 0
0043ff49        slot->unknown_9c[9] = 0
0043ff49        slot->unknown_9c[0xa] = 0
0043ff49        slot->unknown_9c[0xb] = 0
0043ff4f        slot->unknown_9c[4].d = fconvert.s(x87_r7_48)
0043ff5e        slot->unknown_9c[0xc].d = fconvert.s(fconvert.t(owner_game->subgame_rate) * fconvert.t(0.166666672f))
0043feff        goto label_43ff64
0043ff64        case 3
0043ff64        label_43ff64:
0043ff64        int16_t eax_35 = (slot->unknown_00[4].d).w
0043ff67        slot->state = 0
0043ff73        ecx_15 = &g_game_base->active_bod_list
0043ff7c        if ((eax_35:1.b & 2) == 0)
0043ff83        report_errorf("List remove")
0043ff91        kill_sprite(slot->sprite)
0043ff9c        return
0043ff9f        if ((eax_35.b & 0x40) != 0)
0043ffa6        report_errorf("List remove NEXTBOD")
0043ffb4        kill_sprite(slot->sprite)
0043ffbf        return
0043ffc0        void* eax_36
0043ffc0        eax_36.b = slot->unknown_00[0xc]
0043ffc0        eax_36:1.b = slot->unknown_00[0xd]
0043ffc0        eax_36:2.b = slot->unknown_00[0xe]
0043ffc0        eax_36:3.b = slot->unknown_00[0xf]
0043ffc5        if (eax_36 != 0)
0043ffc7        int32_t edx_20
0043ffc7        edx_20.b = slot->unknown_00[8]
0043ffc7        edx_20:1.b = slot->unknown_00[9]
0043ffc7        edx_20:2.b = slot->unknown_00[0xa]
0043ffc7        edx_20:3.b = slot->unknown_00[0xb]
0043ffca        *(eax_36 + 8) = edx_20
0043ffcd        void* eax_37
0043ffcd        eax_37.b = slot->unknown_00[8]
0043ffcd        eax_37:1.b = slot->unknown_00[9]
0043ffcd        eax_37:2.b = slot->unknown_00[0xa]
0043ffcd        eax_37:3.b = slot->unknown_00[0xb]
0043ffd2        if (eax_37 == 0)
0043ffdc        label_43ffdc:
0043ffdc        int32_t eax_38
0043ffdc        eax_38.b = slot->unknown_00[0xc]
0043ffdc        eax_38:1.b = slot->unknown_00[0xd]
0043ffdc        eax_38:2.b = slot->unknown_00[0xe]
0043ffdc        eax_38:3.b = slot->unknown_00[0xf]
0043ffdf        ecx_15->first.b = eax_38.b
0043ffdf        ecx_15->first:1.b = eax_38:1.b
0043ffdf        ecx_15->first:2.b = eax_38:2.b
0043ffdf        ecx_15->first:3.b = eax_38:3.b
0043ffdf        goto label_43ffe2
0043ffd4        int32_t edx_21
0043ffd4        edx_21.b = slot->unknown_00[0xc]
0043ffd4        edx_21:1.b = slot->unknown_00[0xd]
0043ffd4        edx_21:2.b = slot->unknown_00[0xe]
0043ffd4        edx_21:3.b = slot->unknown_00[0xf]
0043ffd7        *(eax_37 + 0xc) = edx_21
0043ffe2        label_43ffe2:
0043ffe2        int32_t edx_22
0043ffe2        edx_22.b = ecx_15->free_top.b
0043ffe2        edx_22:1.b = ecx_15->free_top:1.b
0043ffe2        edx_22:2.b = ecx_15->free_top:2.b
0043ffe2        edx_22:3.b = ecx_15->free_top:3.b
0043ffe5        slot->unknown_00[0xc] = edx_22.b
0043ffe5        slot->unknown_00[0xd] = edx_22:1.b
0043ffe5        slot->unknown_00[0xe] = edx_22:2.b
0043ffe5        slot->unknown_00[0xf] = edx_22:3.b
0043ffe8        ecx_15->free_top.b = slot.b
0043ffe8        ecx_15->free_top:1.b = slot:1.b
0043ffe8        ecx_15->free_top:2.b = slot:2.b
0043ffe8        ecx_15->free_top:3.b = slot:3.b
0043ffeb        int32_t eax_39
0043ffeb        eax_39.b = slot->unknown_00[4]
0043ffeb        eax_39:1.b = slot->unknown_00[5]
0043ffeb        eax_39:2.b = slot->unknown_00[6]
0043ffeb        eax_39:3.b = slot->unknown_00[7]
0043ffee        struct Sprite* sprite_2 = slot->sprite
0043fff4        eax_39:1.b &= 0xfd
0043fff7        slot->unknown_00[4] = eax_39.b
0043fff7        slot->unknown_00[5] = eax_39:1.b
0043fff7        slot->unknown_00[6] = eax_39:2.b
0043fff7        slot->unknown_00[7] = eax_39:3.b
0043fffa        kill_sprite(sprite_2)
0043fd11        case 4
0043fd11        long double x87_r7_26 = fconvert.t(slot->lateral_phase_step) + fconvert.t(slot->lateral_phase)
0043fd17        long double temp0_1 = fconvert.t(6.28318548f)
0043fd17        x87_r7_26 - temp0_1
0043fd1d        slot->lateral_phase = fconvert.s(x87_r7_26)
0043fd1d        bool c1_1 = unknown  {fst dword [esi+0xb8], st0}
0043fd28        if ((((x87_r7_26 < temp0_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_26, temp0_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0043fd30        slot->lateral_phase = fconvert.s(x87_r7_26 - fconvert.t(6.28318548f))
0043fd55        slot->world_position.x = fconvert.s(sine(slot->lateral_phase) * fconvert.t(3f))
0043fd58        long double x87_r7_31 = fconvert.t(slot->world_position.z)
0043fd5b        long double temp5_1 = fconvert.t(slot->owner_player->body.transform.position.z)
0043fd5b        x87_r7_31 - temp5_1
0043fd6b        if ((((x87_r7_31 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp5_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) != 0 && slot->passed_player == 0)
0043fd6d        slot->passed_player = 1
0043fd7d        struct Vec3* edx_16 = &slot->sprite->position
0043fd80        edx_16->x = slot->world_position.x
0043fd85        edx_16->y = slot->world_position.y
0043fd8b        edx_16->z = slot->world_position.z
0043fd8e        struct Player* owner_player_3 = slot->owner_player
0043fd94        long double x87_r7_32 = fconvert.t(slot->world_position.z)
0043fd97        long double temp8_1 = fconvert.t(owner_player_3->interaction_max_z)
0043fd97        x87_r7_32 - temp8_1
0043fda2        if ((((x87_r7_32 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_32, temp8_1) ? 1 : 0) << 0xa | (x87_r7_32 == temp8_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043fe23        long double x87_r7_33 = fconvert.t(owner_player_3->nuke_effect_progress)
0043fe29        long double temp12_1 = fconvert.t(0f)
0043fe29        x87_r7_33 - temp12_1
0043fe34        if ((((x87_r7_33 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_33, temp12_1) ? 1 : 0) << 0xa | (x87_r7_33 == temp12_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043fe3c        kill_slug_hazard(slot)
0043fe34        goto label_43fcd9
0043fda4        int16_t eax_25 = (slot->unknown_00[4].d).w
0043fda7        slot->state = 0
0043fdb3        ecx_15 = &g_game_base->active_bod_list
0043fdbc        if ((eax_25:1.b & 2) == 0)
0043fdc3        report_errorf("List remove")
0043fdd1        kill_sprite(slot->sprite)
0043fddc        return
0043fddf        if ((eax_25.b & 0x40) != 0)
0043fde6        report_errorf("List remove NEXTBOD")
0043fdf4        kill_sprite(slot->sprite)
0043fdff        return
0043fe00        void* eax_26
0043fe00        eax_26.b = slot->unknown_00[0xc]
0043fe00        eax_26:1.b = slot->unknown_00[0xd]
0043fe00        eax_26:2.b = slot->unknown_00[0xe]
0043fe00        eax_26:3.b = slot->unknown_00[0xf]
0043fe05        if (eax_26 != 0)
0043fe07        int32_t edx_17
0043fe07        edx_17.b = slot->unknown_00[8]
0043fe07        edx_17:1.b = slot->unknown_00[9]
0043fe07        edx_17:2.b = slot->unknown_00[0xa]
0043fe07        edx_17:3.b = slot->unknown_00[0xb]
0043fe0a        *(eax_26 + 8) = edx_17
0043fe0d        void* eax_27
0043fe0d        eax_27.b = slot->unknown_00[8]
0043fe0d        eax_27:1.b = slot->unknown_00[9]
0043fe0d        eax_27:2.b = slot->unknown_00[0xa]
0043fe0d        eax_27:3.b = slot->unknown_00[0xb]
0043fe12        if (eax_27 == 0)
0043fe12        goto label_43ffdc
0043fe18        int32_t edx_18
0043fe18        edx_18.b = slot->unknown_00[0xc]
0043fe18        edx_18:1.b = slot->unknown_00[0xd]
0043fe18        edx_18:2.b = slot->unknown_00[0xe]
0043fe18        edx_18:3.b = slot->unknown_00[0xf]
0043fe1b        *(eax_27 + 0xc) = edx_18
0043fe1e        goto label_43ffe2
0043fd0a        return
