/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_cutscene @ 0x4466d0 */

004466dc        enum CutSceneState state = cutscene->state
004466df        cutscene->force_camera_update = 0
004466e7        if (state - 1 u> 0xb)
004466e7        return
004466e7        struct TransformMatrix* parcels_collected
004466e7        struct TransformMatrix var_c0
004466e7        struct TransformMatrix transform
004466e7        switch (state)
00446701        case CUT_SCENE_STATE_INTRO_PENDING
00446701        struct Snail* presentation_6 = cutscene->presentation
00446704        int32_t mode_flags = 0xffffffff
00446706        parcels_collected = 1
00446709        cutscene->state = CUT_SCENE_STATE_INTRO_ACTIVE
00446710        cutscene->progress = 0f
00446717        cutscene->progress_step = 0.00833333377f
0044671a        cutscene->force_camera_update = 1
0044671d        dispatch_cutscene_animation(presentation_6, 9, parcels_collected.b, mode_flags)
00446722        struct Snail* presentation_7 = cutscene->presentation
00446725        int32_t mode_flags_1 = 0xffffffff
00446727        parcels_collected = nullptr
0044672b        dispatch_cutscene_animation(presentation_7, 9, parcels_collected.b, mode_flags_1)
00446730        struct Snail* presentation_8 = cutscene->presentation
00446733        int32_t mode_flags_2 = 0xffffffff
00446735        parcels_collected = nullptr
00446738        dispatch_cutscene_animation(presentation_8, 1, parcels_collected.b, mode_flags_2)
00446740        label_446740:
00446740        cutscene->camera_mode = 1
00446745        set_matrix_identity(&cutscene->live_matrix)
0044674a        struct Snail* presentation = cutscene->presentation
0044675c        cutscene->live_matrix.position.x = presentation->snail_hotspots_world[0x12].x
00446761        cutscene->live_matrix.position.y = presentation->snail_hotspots_world[0x12].y
00446767        cutscene->live_matrix.position.z = presentation->snail_hotspots_world[0x12].z
0044676c        look_at_point(&cutscene->live_matrix, &presentation->body.transform.position)
00446774        long double x87_r7_2 = fconvert.t(cutscene->progress) + fconvert.t(cutscene->progress_step)
00446777        cutscene->progress = fconvert.s(x87_r7_2)
0044677a        long double temp0_1 = fconvert.t(1f)
0044677a        x87_r7_2 - temp0_1
00446785        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044678b        cutscene->progress_step = 0.00833333377f
0044678f        cutscene->state = CUT_SCENE_STATE_INTRO_RETURN_BLEND
00446796        cutscene->progress = 0f
004466fa        case CUT_SCENE_STATE_INTRO_ACTIVE
004466fa        goto label_446740
00446b50        case CUT_SCENE_STATE_COMPLETION_PENDING
00446b50        struct Snail* presentation_11 = cutscene->presentation
00446b58        int32_t mode_flags_4 = 0xffffffff
00446b59        parcels_collected = 1
00446b5c        cutscene->state = CUT_SCENE_STATE_COMPLETION_HOLD
00446b63        cutscene->camera_mode = 0xffffffff
00446b66        dispatch_cutscene_animation(presentation_11, 8, parcels_collected.b, mode_flags_4)
00446b6b        struct Snail* presentation_12 = cutscene->presentation
00446b6e        int32_t mode_flags_5 = 0xffffffff
00446b6f        parcels_collected = nullptr
00446b73        dispatch_cutscene_animation(presentation_12, 9, parcels_collected.b, mode_flags_5)
00446b78        struct Snail* presentation_13 = cutscene->presentation
00446b7b        int32_t mode_flags_6 = 0xffffffff
00446b7c        parcels_collected = nullptr
00446b80        dispatch_cutscene_animation(presentation_13, 9, parcels_collected.b, mode_flags_6)
00446b85        struct Snail* presentation_2 = cutscene->presentation
00446b88        cutscene->state = CUT_SCENE_STATE_COMPLETION_BLEND
00446b8f        cutscene->progress = 0f
00446b96        cutscene->progress_step = 0.00833333377f
00446b9d        presentation_2->invincible_shell.cutscene_roll_step = 0.0166666675f
00446ba7        struct Snail* presentation_3 = cutscene->presentation
00446bb0        presentation_3->invincible_shell.cutscene_roll_progress = presentation_3->invincible_shell.cutscene_roll_step
00446bb6        cutscene->force_camera_update = 1
00446bb9        struct GameRoot* game_base_1 = g_game_base
00446bbf        int32_t level_mode = game_base_1->subgame.level_mode
00446bc7        bool perfect_delivery
00446bc7        if (level_mode == 0)
00446bd2        int32_t parcels_collected_1 = cutscene->player->parcels_collected
00446be5        perfect_delivery = parcels_collected_1 == game_base_1->subgame.level_definition.parcel_count
00446be6        parcels_collected = parcels_collected_1
00446bfe        initialize_completion_screen(&game_base_1->subgame.completion, parcels_collected, perfect_delivery)
00446beb        if (level_mode == 1)
00446bf0        perfect_delivery = true
00446bf7        parcels_collected = cutscene->player->parcels_collected
00446bfe        initialize_completion_screen(&game_base_1->subgame.completion, parcels_collected, perfect_delivery)
00446c0a        play_sound_effect(0x2e)
00446c0a        goto label_446c13
00446c13        case CUT_SCENE_STATE_COMPLETION_BLEND
00446c13        label_446c13:
00446c13        cutscene->camera_mode = 0xffffffff
00446c16        set_matrix_identity(&transform)
00446c1b        struct Snail* presentation_4 = cutscene->presentation
00446c2b        var_c0.position.x = presentation_4->snail_hotspots_world[0xc].x
00446c32        var_c0.position.y = presentation_4->snail_hotspots_world[0xc].y
00446c39        var_c0.position.z = presentation_4->snail_hotspots_world[0xc].z
00446c69        float progress = cutscene->progress
00446caa        float var_e8_3 = fconvert.s((fconvert.t(presentation_4->snail_hotspots_world[0x12].x) - fconvert.t(var_c0.position.x)) * fconvert.t(progress) + fconvert.t(var_c0.position.x))
00446cba        float var_fc_12 = var_e8_3
00446cbb        transform.position.x = var_e8_3
00446cd2        transform.position.y = fconvert.s(fconvert.t(var_c0.position.y) + fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(presentation_4->snail_hotspots_world[0x12].y) - fconvert.t(var_c0.position.y))) * fconvert.t(progress))))
00446cea        transform.position.z = fconvert.s(fconvert.t(var_c0.position.z) + fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(presentation_4->snail_hotspots_world[0x12].z) - fconvert.t(var_c0.position.z))) * fconvert.t(progress))))
00446cf9        long double x87_r7_49 = sine(fconvert.s(fconvert.t(cutscene->progress) * fconvert.t(3.14159274f))) * fconvert.t(0.5f)
00446d14        transform.position.x = fconvert.s(fconvert.t(transform.position.x) - x87_r7_49)
00446d1b        look_at_point(&transform, &cutscene->presentation->body.transform.position)
00446d43        int32_t var_fc_15 = __builtin_memcpy(&var_c0, &cutscene->presentation->owner_player->cameraman, 0x40)
00446d4c        float alpha_2 = fconvert.s(sine(fconvert.s(fconvert.t(cutscene->progress) * fconvert.t(1.57079637f))))
00446d57        parcels_collected = &transform
00446d5c        linear_interpolate_matrix(&cutscene->live_matrix, &var_c0, parcels_collected, alpha_2)
00446d64        long double x87_r7_55 = fconvert.t(cutscene->progress) + fconvert.t(cutscene->progress_step)
00446d67        cutscene->progress = fconvert.s(x87_r7_55)
00446d6a        long double temp4_1 = fconvert.t(1f)
00446d6a        x87_r7_55 - temp4_1
00446d75        if ((((x87_r7_55 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_55, temp4_1) ? 1 : 0) << 0xa | (x87_r7_55 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00446d78        cutscene->state = CUT_SCENE_STATE_COMPLETION_HOLD
00446d7f        cutscene->progress = 0f
00446d86        cutscene->progress_step = 0.0166666675f
00446d9a        case CUT_SCENE_STATE_COMPLETION_HOLD
00446d9a        cutscene->camera_mode = 0xffffffff
00446da3        cutscene->force_camera_update = 1
00446da7        set_matrix_identity(&cutscene->live_matrix)
00446dac        struct Snail* presentation_5 = cutscene->presentation
00446dbe        cutscene->live_matrix.position.x = presentation_5->snail_hotspots_world[0x12].x
00446dc3        cutscene->live_matrix.position.y = presentation_5->snail_hotspots_world[0x12].y
00446dc9        cutscene->live_matrix.position.z = presentation_5->snail_hotspots_world[0x12].z
00446dce        look_at_point(&cutscene->live_matrix, &presentation_5->body.transform.position)
00446dd3        struct Snail* presentation_14 = cutscene->presentation
00446dde        if (presentation_14->anim_manager.queue_count == 0)
00446de0        int32_t mode_flags_7 = 0xffffffff
00446de2        parcels_collected = nullptr
00446de6        dispatch_cutscene_animation(presentation_14, 9, parcels_collected.b, mode_flags_7)
00446df1        cutscene->progress = fconvert.s(fconvert.t(cutscene->progress_step) + fconvert.t(cutscene->progress))
004467b1        case CUT_SCENE_STATE_INTRO_RETURN_BLEND
004467b1        g_game_base->subgame.player.click_start.hide_prompt = 0
004467b8        cutscene->camera_mode = 1
004467bf        set_matrix_identity(&var_c0)
004467d0        struct Vec3* eax_5 = &cutscene->presentation->snail_hotspots_world[0x12]
004467d5        float x = eax_5->x
004467d7        var_c0.position.x = x
004467db        float x_1 = x
004467e2        var_c0.position.y = eax_5->y
004467e9        var_c0.position.z = eax_5->z
004467ed        long double st0_1 = sine(fconvert.s(fconvert.t(cutscene->progress) * fconvert.t(3.14159274f)))
00446806        var_c0.position.x = fconvert.s(st0_1 + st0_1 + fconvert.t(var_c0.position.x))
0044680a        look_at_point(&var_c0, &cutscene->presentation->body.transform.position)
00446832        int32_t var_fc_4 = __builtin_memcpy(&transform, &cutscene->presentation->owner_player->cameraman, 0x40)
0044683b        float alpha = fconvert.s(sine(fconvert.s(fconvert.t(cutscene->progress) * fconvert.t(1.57079637f))))
00446846        parcels_collected = &transform
0044684b        linear_interpolate_matrix(&cutscene->live_matrix, &var_c0, parcels_collected, alpha)
00446850        struct Snail* presentation_1 = cutscene->presentation
00446878        struct Vec3 vector
00446878        vector.x = fconvert.s(fconvert.t(cutscene->live_matrix.position.x) - fconvert.t(presentation_1->body.transform.position.x))
0044687c        vector.y = fconvert.s(fconvert.t(cutscene->live_matrix.position.y) - fconvert.t(presentation_1->body.transform.position.y))
00446888        vector.z = fconvert.s(fconvert.t(cutscene->live_matrix.position.z) - fconvert.t(presentation_1->body.transform.position.z))
00446890        long double st0_3 = normalize_vector(&vector)
00446895        long double temp3_1 = fconvert.t(1.5f)
00446895        st0_3 - temp3_1
004468a0        if ((((st0_3 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(st0_3, temp3_1) ? 1 : 0) << 0xa | (st0_3 == temp3_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
004468a2        long double x87_r7_18 = fconvert.t(1.5f) - st0_3
004468c7        cutscene->live_matrix.position.x = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.x) * x87_r7_18)) + fconvert.t(cutscene->live_matrix.position.x))
004468d1        cutscene->live_matrix.position.y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.y) * x87_r7_18)) + fconvert.t(cutscene->live_matrix.position.y))
004468d7        cutscene->live_matrix.position.z = fconvert.s(x87_r7_18 * fconvert.t(vector.z) + fconvert.t(cutscene->live_matrix.position.z))
004468e1        long double x87_r7_23 = fconvert.t(cutscene->progress) + fconvert.t(cutscene->progress_step)
004468e4        cutscene->progress = fconvert.s(x87_r7_23)
004468e7        long double temp6_1 = fconvert.t(1f)
004468e7        x87_r7_23 - temp6_1
004468f2        if ((((x87_r7_23 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp6_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
004468f9        cutscene->state = CUT_SCENE_STATE_INTRO_FINISH
00446900        cutscene->progress = 0f
00446907        cutscene->progress_step = 0.00833333377f
00446929        case CUT_SCENE_STATE_INTRO_FINISH
0044692f        __builtin_memcpy(&cutscene->live_matrix, &cutscene->presentation->owner_player->cameraman, 0x40)
00446932        cutscene->state = CUT_SCENE_STATE_INACTIVE
00446943        case CUT_SCENE_STATE_DEATH_PENDING
00446943        struct Snail* presentation_9 = cutscene->presentation
0044694e        int32_t mode_flags_3 = 0xffffffff
0044694f        parcels_collected = 1
00446952        cutscene->camera_mode = 0xffffffff
00446955        dispatch_cutscene_animation(presentation_9, 7, parcels_collected.b, mode_flags_3)
0044695a        int32_t sample_override = 0xffffffff
0044695b        parcels_collected = 2
00446964        cutscene->state = CUT_SCENE_STATE_DEATH_BLEND
0044696b        cutscene->progress = 0f
00446972        cutscene->progress_step = 0.00833333377f
00446979        cutscene->force_camera_update = 1
0044697c        play_voice_manager(0x751498, 3, parcels_collected, sample_override)
0044698a        cutscene->presentation->owner_player->attachment_exit_gate_a = 1
00446993        release_snail_weapons(cutscene->presentation)
0044699c        label_44699c:
0044699c        cutscene->camera_mode = 0xffffffff
0044699f        set_matrix_identity(&transform)
004469b0        struct Vec3* edx_8 = &cutscene->presentation->snail_hotspots_world[0x12]
004469b8        transform.position.x = edx_8->x
004469bf        float y = edx_8->y
004469c2        float y_1 = y
004469c3        transform.position.y = y
004469d0        transform.position.z = edx_8->z
004469d7        long double st0_4 = sine(fconvert.s(fconvert.t(cutscene->progress) * fconvert.t(3.14159274f)))
004469e8        transform.position.x = fconvert.s(st0_4 + st0_4 + fconvert.t(transform.position.x))
004469ef        long double x87_r7_29 = fconvert.t(transform.position.y)
004469f6        long double temp1_1 = fconvert.t(0f)
004469f6        x87_r7_29 - temp1_1
00446a01        if ((((x87_r7_29 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_29, temp1_1) ? 1 : 0) << 0xa | (x87_r7_29 == temp1_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00446a03        transform.position.y = 0
00446a19        look_at_point(&transform, &cutscene->presentation->body.transform.position)
00446a25        long double x87_r7_30 = fconvert.t(cutscene->progress)
00446a41        int32_t var_fc_8 = __builtin_memcpy(&var_c0, &cutscene->presentation->owner_player->cameraman, 0x40)
00446a4a        float alpha_1 = fconvert.s(sine(fconvert.s(x87_r7_30 * fconvert.t(1.57079637f))))
00446a55        parcels_collected = &transform
00446a5a        linear_interpolate_matrix(&cutscene->live_matrix, &var_c0, parcels_collected, alpha_1)
00446a62        long double x87_r7_34 = fconvert.t(cutscene->progress) + fconvert.t(cutscene->progress_step)
00446a65        cutscene->progress = fconvert.s(x87_r7_34)
00446a68        long double temp5_1 = fconvert.t(1f)
00446a68        x87_r7_34 - temp5_1
00446a73        if ((((x87_r7_34 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_34, temp5_1) ? 1 : 0) << 0xa | (x87_r7_34 == temp5_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00446a7a        cutscene->state = CUT_SCENE_STATE_DEATH_HOLD
00446a81        cutscene->progress = 0f
00446a88        cutscene->progress_step = 0.0166666675f
004466fa        case CUT_SCENE_STATE_DEATH_BLEND
004466fa        goto label_44699c
00446aa3        case CUT_SCENE_STATE_DEATH_HOLD
00446aa3        cutscene->camera_mode = 0xffffffff
00446aaa        cutscene->force_camera_update = 1
00446aad        set_matrix_identity(&cutscene->live_matrix)
00446ab2        struct Snail* presentation_10 = cutscene->presentation
00446ac4        cutscene->live_matrix.position.x = presentation_10->snail_hotspots_world[0x12].x
00446ac9        cutscene->live_matrix.position.y = presentation_10->snail_hotspots_world[0x12].y
00446acf        cutscene->live_matrix.position.z = presentation_10->snail_hotspots_world[0x12].z
00446ad2        long double x87_r7_35 = fconvert.t(cutscene->live_matrix.position.y)
00446ad5        long double temp2_1 = fconvert.t(0f)
00446ad5        x87_r7_35 - temp2_1
00446adf        if ((1 & ((x87_r7_35 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_35, temp2_1) ? 1 : 0) << 0xa | (x87_r7_35 == temp2_1 ? 1 : 0) << 0xe):1.b) != 0)
00446ae1        cutscene->live_matrix.position.y = 0f
00446aee        look_at_point(&cutscene->live_matrix, &presentation_10->body.transform.position)
00446af3        struct Player* player = cutscene->player
00446afe        if (player->resurrect_active.b == 0)
00446b04        initialize_subgoldy_death(player)
00446b14        if (cutscene->player->attachment_exit_gate_b == 0)
00446b1a        int32_t sample_override_1 = 0xffffffff
00446b1c        parcels_collected = 2
00446b25        play_voice_manager(0x751498, 0xb, parcels_collected, sample_override_1)
00446b2f        cutscene->player->attachment_exit_gate_b = 1
00446b38        cutscene->player->attachment_exit_gate_a = 1
00446b44        cutscene->progress = fconvert.s(fconvert.t(cutscene->progress_step) + fconvert.t(cutscene->progress))
00446b4f        return
00446df1        cutscene->progress = fconvert.s(fconvert.t(cutscene->progress_step) + fconvert.t(cutscene->progress))
00446dfe        return
