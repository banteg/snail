/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_slug_hazard_ai @ 0x43f930 */

0043f943        if (slug->owner_game->subgame_pause_gate != 0)
0043f943        return
0043f949        enum SubSlugState state = slug->state
0043f952        struct BodList* ecx_16
0043f952        if (state u> SUB_SLUG_STATE_LATERAL_ACTIVE)
0043fcd9        label_43fcd9:
0043fcd9        slug->sprite->facing_angle = fconvert.s(fconvert.t(slug->owner_player->heading_roll) + fconvert.t(slug->attachment_facing_angle))
0043fcdc        struct Player* owner_player_2 = slug->owner_player
0043fce9        if (owner_player_2->follow_state.active == 1)
0043fceb        struct Sprite* sprite = slug->sprite
0043fcfa        sprite->facing_angle = fconvert.s(fconvert.t(owner_player_2->follow_state.orientation_b) + fconvert.t(sprite->facing_angle))
0043fcff        update_slug_voice_ai(slug)
0043f958        switch (state)
0043f96d        case SUB_SLUG_STATE_ACTIVE
0043f96d        if (slug->hit_flash_pending != 0 && g_render_queue_active != 0)
0043f96f        float hit_flash_progress_step = slug->hit_flash_progress_step
0043f975        slug->hit_flash_pending = 0
0043f97b        slug->hit_flash_progress = hit_flash_progress_step
0043f981        long double x87_r7_1 = fconvert.t(slug->hit_flash_progress)
0043f987        long double temp1_1 = fconvert.t(0f)
0043f987        x87_r7_1 - temp1_1
0043f992        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0043fa56        slug->blink_progress = fconvert.s(fconvert.t(slug->blink_step) + fconvert.t(slug->blink_progress))
0043fa5c        long double x87_r7_6 = fconvert.t(slug->blink_step)
0043fa62        long double temp3_1 = fconvert.t(0f)
0043fa62        x87_r7_6 - temp3_1
0043fa6d        if ((((x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043fa8f        set_sprite_texture_ref(slug->sprite, 0x77, 0)
0043fa9a        slug->sprite->draw_mode = 0
0043fa77        set_sprite_texture_ref(slug->sprite, 0x76, 0)
0043fa82        slug->sprite->draw_mode = 0
0043faba        store_color4f(&slug->sprite->color, 1f, 1f, 1f, 1f)
0043fabf        long double x87_r7_7 = fconvert.t(slug->blink_progress)
0043fac5        long double temp10_1 = fconvert.t(0f)
0043fac5        x87_r7_7 - temp10_1
0043fad0        if ((((x87_r7_7 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp10_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp10_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043faf0        long double x87_r7_9 = fconvert.t(slug->blink_progress)
0043faf6        long double temp13_1 = fconvert.t(1f)
0043faf6        x87_r7_9 - temp13_1
0043fb01        if ((((x87_r7_9 < temp13_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp13_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp13_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043fb03        slug->blink_progress = 1f
0043fb0d        slug->blink_step = -0.166666672f
0043fad2        slug->blink_progress = 0f
0043fae8        slug->blink_step = fconvert.s(advance_blink_random(&g_game_base->subgame))
0043f99e        long double x87_r7_3 = fconvert.t(slug->hit_flash_progress_step) + fconvert.t(slug->hit_flash_progress)
0043f9a4        slug->hit_flash_progress = fconvert.s(x87_r7_3)
0043f9aa        long double temp4_1 = fconvert.t(1f)
0043f9aa        x87_r7_3 - temp4_1
0043f9b5        if ((((x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043fa18        slug->sprite->draw_mode = 5
0043fa25        set_sprite_texture_ref(slug->sprite, 0x78, 0)
0043fa3f        store_color4f(&slug->sprite->color, 1f, 0f, 0f, 0.99000001f)
0043f9b7        struct Sprite* sprite_1 = slug->sprite
0043f9bd        slug->hit_flash_progress = 0f
0043f9c3        slug->blink_progress = 1f
0043f9cd        slug->blink_step = -0.166666672f
0043f9d7        sprite_1->draw_mode = 0
0043f9f7        store_color4f(&slug->sprite->color, 1f, 1f, 1f, 1f)
0043fa05        set_sprite_texture_ref(slug->sprite, 0x77, 0)
0043fb20        long double x87_r7_11 = fconvert.t(slug->owner_player->body.transform.position.z) + fconvert.t(1f)
0043fb26        long double temp11_1 = fconvert.t(slug->body.transform.position.z)
0043fb26        x87_r7_11 - temp11_1
0043fb36        if ((((x87_r7_11 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp11_1) ? 1 : 0) << 0xa | (x87_r7_11 == temp11_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 && slug->player_encounter_latched == 0)
0043fb38        slug->player_encounter_latched = 1
0043fb4c        long double x87_r7_13 = float.t(next_math_random_value()) * fconvert.t(3.05175781e-05f)
0043fb52        long double temp15_1 = fconvert.t(0.600000024f)
0043fb52        x87_r7_13 - temp15_1
0043fb5d        int16_t x87control
0043fb5d        if ((((x87_r7_13 < temp15_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp15_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp15_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043fb81        play_slug_voice(slug, 0x1e - ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-0.000122070312f)))
0043fb86        struct Player* owner_player = slug->owner_player
0043fb8c        long double x87_r7_16 = fconvert.t(slug->body.transform.position.z)
0043fb8f        long double temp14_1 = fconvert.t(owner_player->body.transform.position.z)
0043fb8f        x87_r7_16 - temp14_1
0043fb9f        if ((((x87_r7_16 < temp14_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_16, temp14_1) ? 1 : 0) << 0xa | (x87_r7_16 == temp14_1 ? 1 : 0) << 0xe):1.b & 1) != 0 && slug->passed_player == 0)
0043fba1        slug->passed_player = 1
0043fbaf        if (slug->engagement_voice_gate == 1)
0043fbb4        long double x87_r7_18 = fconvert.t(owner_player->body.transform.position.z) + fconvert.t(16f)
0043fbba        long double temp17_1 = fconvert.t(slug->body.transform.position.z)
0043fbba        x87_r7_18 - temp17_1
0043fbc2        if ((((x87_r7_18 < temp17_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_18, temp17_1) ? 1 : 0) << 0xa | (x87_r7_18 == temp17_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043fbcf        slug->engagement_voice_gate = 0
0043fbd5        play_voice_manager(&g_voice_manager, 2, 1, 0xffffffff)
0043fbe5        int32_t* eax_12 = &slug->sprite->position
0043fbea        *eax_12 = slug->body.transform.position.x
0043fbef        *&eax_12[1] = slug->body.transform.position.y
0043fbf5        *&eax_12[2] = slug->body.transform.position.z
0043fbf8        struct Player* owner_player_1 = slug->owner_player
0043fbfe        long double x87_r7_19 = fconvert.t(slug->body.transform.position.z)
0043fc01        long double temp16_1 = fconvert.t(owner_player_1->interaction_max_z)
0043fc01        x87_r7_19 - temp16_1
0043fc0c        if ((((x87_r7_19 < temp16_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_19, temp16_1) ? 1 : 0) << 0xa | (x87_r7_19 == temp16_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043fc8d        long double x87_r7_20 = fconvert.t(owner_player_1->nuke_effect_progress)
0043fc93        long double temp18_1 = fconvert.t(0f)
0043fc93        x87_r7_20 - temp18_1
0043fc9e        if ((((x87_r7_20 < temp18_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp18_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp18_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043fca2        kill_slug_hazard(slug)
0043fcbc        append_subgame_contact_target(&slug->owner_game->enemy_manager, &slug->body.transform.position, 2f, 1, slug)
0043fcbc        goto label_43fcd9
0043fc0e        uint16_t list_flags = (slug->body.bod.bod.list_flags).w
0043fc11        slug->state = SUB_SLUG_STATE_INACTIVE
0043fc20        ecx_16 = &g_game_base->active_bod_list
0043fc26        if ((list_flags:1.b & 2) == 0)
0043fc2d        report_errorf("List remove")
0043fc3b        kill_sprite(slug->sprite)
0043fc46        return
0043fc49        if ((list_flags.b & 0x40) != 0)
0043fc50        report_errorf("List remove NEXTBOD")
0043fc5e        kill_sprite(slug->sprite)
0043fc69        return
0043fc6a        struct BodNode* list_next = slug->body.bod.bod.list_next
0043fc6f        if (list_next != 0)
0043fc74        list_next->list_prev = slug->body.bod.bod.list_prev
0043fc77        struct BodNode* list_prev = slug->body.bod.bod.list_prev
0043fc7c        if (list_prev == 0)
0043fc7c        goto label_43ffdf
0043fc85        list_prev->list_next = slug->body.bod.bod.list_next
0043fc88        goto label_43ffe5
0043fe46        case SUB_SLUG_STATE_DEATH_TOSS_PENDING
0043fe46        int32_t var_24_4 = 0
0043fe4c        slug->state = SUB_SLUG_STATE_TEARDOWN_PENDING
0043fe5b        float var_10_1 = fconvert.s(random_float_below(0.300000012f))
0043fe5f        int32_t var_2c_1 = 0
0043fe70        void* var_34_1 = &data_4a4e70
0043fe7a        float var_14_3 = fconvert.s(random_float_below(0.200000003f) + fconvert.t(0.100000001f))
0043fea6        slug->velocity.x = fconvert.s(random_signed_float_below(0.100000001f))
0043feac        slug->velocity.y = var_14_3
0043feb3        slug->velocity.z = var_10_1
0043feb6        enum SubSlugDeathTossDirection death_toss_direction = slug->death_toss_direction
0043febf        if (death_toss_direction == SUB_SLUG_DEATH_TOSS_RIGHT)
0043fec1        long double x87_r7_38 = fconvert.t(slug->velocity.x)
0043fec3        long double temp2_1 = fconvert.t(0f)
0043fec3        x87_r7_38 - temp2_1
0043fec9        long double x87_r7_39 = fconvert.t(slug->velocity.x)
0043fed0        if ((((x87_r7_38 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_38, temp2_1) ? 1 : 0) << 0xa | (x87_r7_38 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0043fed2        x87_r7_39 = fneg(x87_r7_39)
0043fef0        slug->velocity.x = fconvert.s(x87_r7_39)
0043fed9        if (death_toss_direction == SUB_SLUG_DEATH_TOSS_LEFT)
0043fedb        long double x87_r7_40 = fconvert.t(slug->velocity.x)
0043fedd        long double temp7_1 = fconvert.t(0f)
0043fedd        x87_r7_40 - temp7_1
0043fee3        long double x87_r7_41 = fconvert.t(slug->velocity.x)
0043feea        if ((((x87_r7_40 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_40, temp7_1) ? 1 : 0) << 0xa | (x87_r7_40 == temp7_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0043feec        x87_r7_41 = fneg(x87_r7_41)
0043fef0        slug->velocity.x = fconvert.s(fneg(x87_r7_41))
0043fef2        long double x87_r7_42 = fconvert.t(slug->velocity.x)
0043fef4        long double temp6_1 = fconvert.t(0f)
0043fef4        x87_r7_42 - temp6_1
0043feff        int32_t var_14_4
0043feff        if ((((x87_r7_42 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_42, temp6_1) ? 1 : 0) << 0xa | (x87_r7_42 == temp6_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043ff0b        long double x87_r7_43 = fconvert.t(slug->velocity.x)
0043ff0d        long double temp9_1 = fconvert.t(0f)
0043ff0d        x87_r7_43 - temp9_1
0043ff13        var_14_4 = 0
0043ff1c        if ((((x87_r7_43 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_43, temp9_1) ? 1 : 0) << 0xa | (x87_r7_43 == temp9_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
0043ff1e        var_14_4 = 1
0043ff01        var_14_4 = 0xffffffff
0043ff2a        struct SubgameRuntime* owner_game = slug->owner_game
0043ff30        slug->unknown_9c[0] = 0
0043ff30        slug->unknown_9c[1] = 0
0043ff30        slug->unknown_9c[2] = 0
0043ff30        slug->unknown_9c[3] = 0
0043ff3e        slug->velocity.x = fconvert.s(float.t(var_14_4) * fconvert.t(0.200000003f) + fconvert.t(slug->velocity.x))
0043ff43        long double x87_r7_48 = fconvert.t(owner_game->subgame_rate) * fconvert.t(0.00833333377f)
0043ff49        slug->unknown_9c[8] = 0
0043ff49        slug->unknown_9c[9] = 0
0043ff49        slug->unknown_9c[0xa] = 0
0043ff49        slug->unknown_9c[0xb] = 0
0043ff4f        slug->unknown_9c[4].d = fconvert.s(x87_r7_48)
0043ff5e        slug->unknown_9c[0xc].d = fconvert.s(fconvert.t(owner_game->subgame_rate) * fconvert.t(0.166666672f))
0043feff        goto label_43ff64
0043ff64        case SUB_SLUG_STATE_TEARDOWN_PENDING
0043ff64        label_43ff64:
0043ff64        uint16_t list_flags_2 = (slug->body.bod.bod.list_flags).w
0043ff67        slug->state = SUB_SLUG_STATE_INACTIVE
0043ff73        ecx_16 = &g_game_base->active_bod_list
0043ff7c        if ((list_flags_2:1.b & 2) == 0)
0043ff83        report_errorf("List remove")
0043ff91        kill_sprite(slug->sprite)
0043ff9c        return
0043ff9f        if ((list_flags_2.b & 0x40) != 0)
0043ffa6        report_errorf("List remove NEXTBOD")
0043ffb4        kill_sprite(slug->sprite)
0043ffbf        return
0043ffc0        struct BodNode* list_next_2 = slug->body.bod.bod.list_next
0043ffc5        if (list_next_2 != 0)
0043ffca        list_next_2->list_prev = slug->body.bod.bod.list_prev
0043ffcd        struct BodNode* list_prev_2 = slug->body.bod.bod.list_prev
0043ffd2        if (list_prev_2 == 0)
0043ffdf        label_43ffdf:
0043ffdf        ecx_16->first = slug->body.bod.bod.list_next
0043ffdf        goto label_43ffe5
0043ffd7        list_prev_2->list_next = slug->body.bod.bod.list_next
0043ffe5        label_43ffe5:
0043ffe5        slug->body.bod.bod.list_next = ecx_16->free_top
0043ffe8        ecx_16->free_top = slug
0043ffeb        uint32_t list_flags_3 = slug->body.bod.bod.list_flags
0043fff4        list_flags_3:1.b &= 0xfd
0043fff7        slug->body.bod.bod.list_flags = list_flags_3
0043fffa        kill_sprite(slug->sprite)
0043fd11        case SUB_SLUG_STATE_LATERAL_ACTIVE
0043fd11        long double x87_r7_26 = fconvert.t(slug->lateral_phase_step) + fconvert.t(slug->lateral_phase)
0043fd17        long double temp0_1 = fconvert.t(6.28318548f)
0043fd17        x87_r7_26 - temp0_1
0043fd1d        slug->lateral_phase = fconvert.s(x87_r7_26)
0043fd1d        bool c1_1 = unknown  {fst dword [esi+0xb8], st0}
0043fd28        if ((((x87_r7_26 < temp0_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_26, temp0_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0043fd30        slug->lateral_phase = fconvert.s(x87_r7_26 - fconvert.t(6.28318548f))
0043fd55        slug->body.transform.position.x = fconvert.s(sine(slug->lateral_phase) * fconvert.t(3f))
0043fd58        long double x87_r7_31 = fconvert.t(slug->body.transform.position.z)
0043fd5b        long double temp5_1 = fconvert.t(slug->owner_player->body.transform.position.z)
0043fd5b        x87_r7_31 - temp5_1
0043fd6b        if ((((x87_r7_31 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp5_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) != 0 && slug->passed_player == 0)
0043fd6d        slug->passed_player = 1
0043fd7d        struct Vec3* edx_9 = &slug->sprite->position
0043fd80        edx_9->x = slug->body.transform.position.x
0043fd85        edx_9->y = slug->body.transform.position.y
0043fd8b        edx_9->z = slug->body.transform.position.z
0043fd8e        struct Player* owner_player_3 = slug->owner_player
0043fd94        long double x87_r7_32 = fconvert.t(slug->body.transform.position.z)
0043fd97        long double temp8_1 = fconvert.t(owner_player_3->interaction_max_z)
0043fd97        x87_r7_32 - temp8_1
0043fda2        if ((((x87_r7_32 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_32, temp8_1) ? 1 : 0) << 0xa | (x87_r7_32 == temp8_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043fe23        long double x87_r7_33 = fconvert.t(owner_player_3->nuke_effect_progress)
0043fe29        long double temp12_1 = fconvert.t(0f)
0043fe29        x87_r7_33 - temp12_1
0043fe34        if ((((x87_r7_33 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_33, temp12_1) ? 1 : 0) << 0xa | (x87_r7_33 == temp12_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043fe3c        kill_slug_hazard(slug)
0043fe34        goto label_43fcd9
0043fda4        uint16_t list_flags_1 = (slug->body.bod.bod.list_flags).w
0043fda7        slug->state = SUB_SLUG_STATE_INACTIVE
0043fdb3        ecx_16 = &g_game_base->active_bod_list
0043fdbc        if ((list_flags_1:1.b & 2) == 0)
0043fdc3        report_errorf("List remove")
0043fdd1        kill_sprite(slug->sprite)
0043fddc        return
0043fddf        if ((list_flags_1.b & 0x40) != 0)
0043fde6        report_errorf("List remove NEXTBOD")
0043fdf4        kill_sprite(slug->sprite)
0043fdff        return
0043fe00        struct BodNode* list_next_1 = slug->body.bod.bod.list_next
0043fe05        if (list_next_1 != 0)
0043fe0a        list_next_1->list_prev = slug->body.bod.bod.list_prev
0043fe0d        struct BodNode* list_prev_1 = slug->body.bod.bod.list_prev
0043fe12        if (list_prev_1 == 0)
0043fe12        goto label_43ffdf
0043fe1b        list_prev_1->list_next = slug->body.bod.bod.list_next
0043fe1e        goto label_43ffe5
0043fd0a        return
