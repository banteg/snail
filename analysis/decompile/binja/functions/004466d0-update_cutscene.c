/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_cutscene @ 0x4466d0 */

004466dc        int32_t state = cutscene_ai->state
004466df        cutscene_ai->unresolved_58 = 0
004466e3        int32_t eax = state - 1
004466fa        struct TransformMatrix* to
004466fa        struct TransformMatrix var_c0
004466fa        struct TransformMatrix transform
004466fa        switch (eax)
00446701        case 0
00446701        struct PlayerPresentationController* presentation_6 = cutscene_ai->presentation
00446704        int32_t initial_frame = 0xffffffff
00446706        to = 1
00446709        cutscene_ai->state = 2
00446710        cutscene_ai->progress = 0f
00446717        cutscene_ai->progress_step = 0.00833333377f
0044671a        cutscene_ai->unresolved_58 = 1
0044671d        dispatch_cutscene_animation(presentation_6, 9, to.b, initial_frame)
00446722        struct PlayerPresentationController* presentation_7 = cutscene_ai->presentation
00446725        int32_t initial_frame_1 = 0xffffffff
00446727        to = nullptr
0044672b        dispatch_cutscene_animation(presentation_7, 9, to.b, initial_frame_1)
00446730        struct PlayerPresentationController* presentation_8 = cutscene_ai->presentation
00446733        int32_t initial_frame_2 = 0xffffffff
00446735        to = nullptr
00446738        dispatch_cutscene_animation(presentation_8, 1, to.b, initial_frame_2)
00446740        label_446740:
00446740        cutscene_ai->unresolved_08 = 1
00446745        set_matrix_identity(&cutscene_ai->live_matrix)
0044674a        struct PlayerPresentationController* presentation = cutscene_ai->presentation
0044675c        cutscene_ai->live_matrix.position.x = presentation->snail_hotspots_world[0x12].x
00446761        cutscene_ai->live_matrix.position.y = presentation->snail_hotspots_world[0x12].y
00446767        cutscene_ai->live_matrix.position.z = presentation->snail_hotspots_world[0x12].z
0044676c        look_at_point(&cutscene_ai->live_matrix, &presentation->live_matrix.position)
00446774        long double x87_r7_2 = fconvert.t(cutscene_ai->progress) + fconvert.t(cutscene_ai->progress_step)
00446777        cutscene_ai->progress = fconvert.s(x87_r7_2)
0044677a        long double temp0_1 = fconvert.t(1f)
0044677a        x87_r7_2 - temp0_1
00446780        eax.w = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe
00446785        if ((eax:1.b & 0x41) == 0)
0044678b        cutscene_ai->progress_step = 0.00833333377f
0044678f        cutscene_ai->state = 8
00446796        cutscene_ai->progress = 0f
004466fa        case 1
004466fa        goto label_446740
00446b50        case 4
00446b50        struct PlayerPresentationController* presentation_11 = cutscene_ai->presentation
00446b58        int32_t initial_frame_4 = 0xffffffff
00446b59        to = 1
00446b5c        cutscene_ai->state = 7
00446b63        cutscene_ai->unresolved_08 = 0xffffffff
00446b66        dispatch_cutscene_animation(presentation_11, 8, to.b, initial_frame_4)
00446b6b        struct PlayerPresentationController* presentation_12 = cutscene_ai->presentation
00446b6e        int32_t initial_frame_5 = 0xffffffff
00446b6f        to = nullptr
00446b73        dispatch_cutscene_animation(presentation_12, 9, to.b, initial_frame_5)
00446b78        struct PlayerPresentationController* presentation_13 = cutscene_ai->presentation
00446b7b        int32_t initial_frame_6 = 0xffffffff
00446b7c        to = nullptr
00446b80        dispatch_cutscene_animation(presentation_13, 9, to.b, initial_frame_6)
00446b85        struct PlayerPresentationController* presentation_2 = cutscene_ai->presentation
00446b88        cutscene_ai->state = 6
00446b8f        cutscene_ai->progress = 0f
00446b96        cutscene_ai->progress_step = 0.00833333377f
00446b9d        presentation_2->invincible_shell._pad_90[8] = 0x89
00446b9d        presentation_2->invincible_shell._pad_90[9] = 0x88
00446b9d        presentation_2->invincible_shell._pad_90[0xa] = 0x88
00446b9d        presentation_2->invincible_shell._pad_90[0xb] = 0x3c
00446ba7        struct PlayerPresentationController* presentation_3 = cutscene_ai->presentation
00446baa        int32_t ecx_23 = presentation_3->invincible_shell._pad_90[8].d
00446bb0        presentation_3->invincible_shell._pad_90[4] = ecx_23.b
00446bb0        presentation_3->invincible_shell._pad_90[5] = ecx_23:1.b
00446bb0        presentation_3->invincible_shell._pad_90[6] = ecx_23:2.b
00446bb0        presentation_3->invincible_shell._pad_90[7] = ecx_23:3.b
00446bb6        cutscene_ai->unresolved_58 = 1
00446bb9        void* ecx_24 = data_4df904
00446bbf        int32_t eax_14 = *(ecx_24 + 0x74658)
00446bc7        if (eax_14 == 0)
00446bd2        struct TransformMatrix* to_1 = cutscene_ai->player->__offset(0x4338).d
00446bda        struct Player* edx_13
00446bda        edx_13.b = to_1 == *(ecx_24 + 0x2247f8)
00446bdd        int32_t var_dc
00446bdd        var_dc.b = edx_13.b
00446be6        to = to_1
00446bfe        initialize_completion_screen(ecx_24 + 0x12e6df0, to, var_dc)
00446beb        if (eax_14 == 1)
00446bf0        int32_t var_fc_13 = 1
00446bf7        to = cutscene_ai->player->__offset(0x4338).d
00446bfe        initialize_completion_screen(ecx_24 + 0x12e6df0, to, var_fc_13)
00446c0a        play_sound_effect(0x2e)
00446c0a        goto label_446c13
00446c13        case 5
00446c13        label_446c13:
00446c13        cutscene_ai->unresolved_08 = 0xffffffff
00446c16        set_matrix_identity(&transform)
00446c1b        struct PlayerPresentationController* presentation_4 = cutscene_ai->presentation
00446c2b        var_c0.position.x = presentation_4->snail_hotspots_world[0xc].x
00446c32        var_c0.position.y = presentation_4->snail_hotspots_world[0xc].y
00446c39        var_c0.position.z = presentation_4->snail_hotspots_world[0xc].z
00446c69        float progress = cutscene_ai->progress
00446caa        float var_e8_3 = fconvert.s((fconvert.t(presentation_4->snail_hotspots_world[0x12].x) - fconvert.t(var_c0.position.x)) * fconvert.t(progress) + fconvert.t(var_c0.position.x))
00446cba        float var_fc_15 = var_e8_3
00446cbb        transform.position.x = var_e8_3
00446cd2        transform.position.y = fconvert.s(fconvert.t(var_c0.position.y) + fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(presentation_4->snail_hotspots_world[0x12].y) - fconvert.t(var_c0.position.y))) * fconvert.t(progress))))
00446cea        transform.position.z = fconvert.s(fconvert.t(var_c0.position.z) + fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(presentation_4->snail_hotspots_world[0x12].z) - fconvert.t(var_c0.position.z))) * fconvert.t(progress))))
00446cf9        long double x87_r7_49 = sine(fconvert.s(fconvert.t(cutscene_ai->progress) * fconvert.t(3.14159274f))) * fconvert.t(0.5f)
00446d14        transform.position.x = fconvert.s(fconvert.t(transform.position.x) - x87_r7_49)
00446d1b        look_at_point(&transform, &cutscene_ai->presentation->live_matrix.position)
00446d43        int32_t var_fc_18 = __builtin_memcpy(&var_c0, cutscene_ai->presentation->owner_player + 0x200, 0x40)
00446d4c        float alpha_2 = fconvert.s(sine(fconvert.s(fconvert.t(cutscene_ai->progress) * fconvert.t(1.57079637f))))
00446d57        to = &transform
00446d5c        linear_interpolate_matrix(&cutscene_ai->live_matrix, &var_c0, to, alpha_2)
00446d64        long double x87_r7_55 = fconvert.t(cutscene_ai->progress) + fconvert.t(cutscene_ai->progress_step)
00446d67        cutscene_ai->progress = fconvert.s(x87_r7_55)
00446d6a        long double temp4_1 = fconvert.t(1f)
00446d6a        x87_r7_55 - temp4_1
00446d70        eax.w = (x87_r7_55 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_55, temp4_1) ? 1 : 0) << 0xa | (x87_r7_55 == temp4_1 ? 1 : 0) << 0xe
00446d75        if ((eax:1.b & 0x41) == 0)
00446d78        cutscene_ai->state = 7
00446d7f        cutscene_ai->progress = 0f
00446d86        cutscene_ai->progress_step = 0.0166666675f
00446d9a        case 6
00446d9a        cutscene_ai->unresolved_08 = 0xffffffff
00446da3        cutscene_ai->unresolved_58 = 1
00446da7        set_matrix_identity(&cutscene_ai->live_matrix)
00446dac        struct PlayerPresentationController* presentation_5 = cutscene_ai->presentation
00446dbe        cutscene_ai->live_matrix.position.x = presentation_5->snail_hotspots_world[0x12].x
00446dc3        cutscene_ai->live_matrix.position.y = presentation_5->snail_hotspots_world[0x12].y
00446dc9        cutscene_ai->live_matrix.position.z = presentation_5->snail_hotspots_world[0x12].z
00446dce        look_at_point(&cutscene_ai->live_matrix, &presentation_5->live_matrix.position)
00446dd3        struct PlayerPresentationController* presentation_14 = cutscene_ai->presentation
00446dd6        eax = presentation_14->anim_manager.queued_animation_count
00446dde        if (eax == 0)
00446de0        int32_t initial_frame_7 = 0xffffffff
00446de2        to = nullptr
00446de6        eax = dispatch_cutscene_animation(presentation_14, 9, to.b, initial_frame_7)
00446df1        cutscene_ai->progress = fconvert.s(fconvert.t(cutscene_ai->progress_step) + fconvert.t(cutscene_ai->progress))
004467b1        case 7
004467b1        *(data_4df904 + 0x42fec4) = 0
004467b8        cutscene_ai->unresolved_08 = 1
004467bf        set_matrix_identity(&var_c0)
004467d0        struct Vec3* eax_3 = &cutscene_ai->presentation->snail_hotspots_world[0x12]
004467d5        float x = eax_3->x
004467d7        var_c0.position.x = x
004467db        float x_1 = x
004467e2        var_c0.position.y = eax_3->y
004467e9        var_c0.position.z = eax_3->z
004467ed        long double st0_1 = sine(fconvert.s(fconvert.t(cutscene_ai->progress) * fconvert.t(3.14159274f)))
00446806        var_c0.position.x = fconvert.s(st0_1 + st0_1 + fconvert.t(var_c0.position.x))
0044680a        look_at_point(&var_c0, &cutscene_ai->presentation->live_matrix.position)
00446832        int32_t var_fc_4 = __builtin_memcpy(&transform, cutscene_ai->presentation->owner_player + 0x200, 0x40)
0044683b        float alpha = fconvert.s(sine(fconvert.s(fconvert.t(cutscene_ai->progress) * fconvert.t(1.57079637f))))
00446846        to = &transform
0044684b        linear_interpolate_matrix(&cutscene_ai->live_matrix, &var_c0, to, alpha)
00446850        struct PlayerPresentationController* presentation_1 = cutscene_ai->presentation
00446878        struct Vec3 vector
00446878        vector.x = fconvert.s(fconvert.t(cutscene_ai->live_matrix.position.x) - fconvert.t(presentation_1->live_matrix.position.x))
0044687c        vector.y = fconvert.s(fconvert.t(cutscene_ai->live_matrix.position.y) - fconvert.t(presentation_1->live_matrix.position.y))
00446888        vector.z = fconvert.s(fconvert.t(cutscene_ai->live_matrix.position.z) - fconvert.t(presentation_1->live_matrix.position.z))
00446890        long double st0_3
00446890        st0_3, eax = normalize_vector(&vector)
00446895        long double temp3_1 = fconvert.t(1.5f)
00446895        st0_3 - temp3_1
0044689b        eax.w = (st0_3 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(st0_3, temp3_1) ? 1 : 0) << 0xa | (st0_3 == temp3_1 ? 1 : 0) << 0xe | 0x3800
004468a0        if ((eax:1.b & 1) != 0)
004468a2        long double x87_r7_18 = fconvert.t(1.5f) - st0_3
004468c7        cutscene_ai->live_matrix.position.x = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.x) * x87_r7_18)) + fconvert.t(cutscene_ai->live_matrix.position.x))
004468d1        cutscene_ai->live_matrix.position.y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.y) * x87_r7_18)) + fconvert.t(cutscene_ai->live_matrix.position.y))
004468d7        cutscene_ai->live_matrix.position.z = fconvert.s(x87_r7_18 * fconvert.t(vector.z) + fconvert.t(cutscene_ai->live_matrix.position.z))
004468e1        long double x87_r7_23 = fconvert.t(cutscene_ai->progress) + fconvert.t(cutscene_ai->progress_step)
004468e4        cutscene_ai->progress = fconvert.s(x87_r7_23)
004468e7        long double temp6_1 = fconvert.t(1f)
004468e7        x87_r7_23 - temp6_1
004468ed        eax.w = (x87_r7_23 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp6_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp6_1 ? 1 : 0) << 0xe
004468f2        if ((eax:1.b & 0x41) == 0)
004468f9        cutscene_ai->state = 9
00446900        cutscene_ai->progress = 0f
00446907        cutscene_ai->progress_step = 0.00833333377f
00446929        case 8
0044692f        __builtin_memcpy(&cutscene_ai->live_matrix, cutscene_ai->presentation->owner_player + 0x200, 0x40)
00446932        cutscene_ai->state = 0
00446943        case 9
00446943        struct PlayerPresentationController* presentation_9 = cutscene_ai->presentation
0044694e        int32_t initial_frame_3 = 0xffffffff
0044694f        to = 1
00446952        cutscene_ai->unresolved_08 = 0xffffffff
00446955        dispatch_cutscene_animation(presentation_9, 7, to.b, initial_frame_3)
0044695a        int32_t var_fc_6 = 0xffffffff
0044695b        to = 2
00446964        cutscene_ai->state = 0xb
0044696b        cutscene_ai->progress = 0f
00446972        cutscene_ai->progress_step = 0.00833333377f
00446979        cutscene_ai->unresolved_58 = 1
0044697c        play_voice_manager(0x751498, 3, to, var_fc_6)
0044698a        cutscene_ai->presentation->owner_player->__offset(0x44c).b = 1
00446993        release_snail_weapons(cutscene_ai->presentation)
0044699c        label_44699c:
0044699c        cutscene_ai->unresolved_08 = 0xffffffff
0044699f        set_matrix_identity(&transform)
004469b0        struct Vec3* edx_8 = &cutscene_ai->presentation->snail_hotspots_world[0x12]
004469b8        transform.position.x = edx_8->x
004469bf        float y = edx_8->y
004469c2        float y_1 = y
004469c3        transform.position.y = y
004469d0        transform.position.z = edx_8->z
004469d7        long double st0_4 = sine(fconvert.s(fconvert.t(cutscene_ai->progress) * fconvert.t(3.14159274f)))
004469e8        transform.position.x = fconvert.s(st0_4 + st0_4 + fconvert.t(transform.position.x))
004469ef        long double x87_r7_29 = fconvert.t(transform.position.y)
004469f6        long double temp1_1 = fconvert.t(0f)
004469f6        x87_r7_29 - temp1_1
00446a01        if ((((x87_r7_29 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_29, temp1_1) ? 1 : 0) << 0xa | (x87_r7_29 == temp1_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00446a03        transform.position.y = 0
00446a19        look_at_point(&transform, &cutscene_ai->presentation->live_matrix.position.x)
00446a25        long double x87_r7_30 = fconvert.t(cutscene_ai->progress)
00446a41        int32_t var_fc_9 = __builtin_memcpy(&var_c0, cutscene_ai->presentation->owner_player + 0x200, 0x40)
00446a4a        float alpha_1 = fconvert.s(sine(fconvert.s(x87_r7_30 * fconvert.t(1.57079637f))))
00446a55        to = &transform
00446a5a        linear_interpolate_matrix(&cutscene_ai->live_matrix, &var_c0, to, alpha_1)
00446a62        long double x87_r7_34 = fconvert.t(cutscene_ai->progress) + fconvert.t(cutscene_ai->progress_step)
00446a65        cutscene_ai->progress = fconvert.s(x87_r7_34)
00446a68        long double temp5_1 = fconvert.t(1f)
00446a68        x87_r7_34 - temp5_1
00446a6e        eax.w = (x87_r7_34 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_34, temp5_1) ? 1 : 0) << 0xa | (x87_r7_34 == temp5_1 ? 1 : 0) << 0xe
00446a73        if ((eax:1.b & 0x41) == 0)
00446a7a        cutscene_ai->state = 0xc
00446a81        cutscene_ai->progress = 0f
00446a88        cutscene_ai->progress_step = 0.0166666675f
004466fa        case 0xa
004466fa        goto label_44699c
00446aa3        case 0xb
00446aa3        cutscene_ai->unresolved_08 = 0xffffffff
00446aaa        cutscene_ai->unresolved_58 = 1
00446aad        set_matrix_identity(&cutscene_ai->live_matrix)
00446ab2        struct PlayerPresentationController* presentation_10 = cutscene_ai->presentation
00446ac4        cutscene_ai->live_matrix.position.x = presentation_10->snail_hotspots_world[0x12].x
00446ac9        cutscene_ai->live_matrix.position.y = presentation_10->snail_hotspots_world[0x12].y
00446acf        cutscene_ai->live_matrix.position.z = presentation_10->snail_hotspots_world[0x12].z
00446ad2        long double x87_r7_35 = fconvert.t(cutscene_ai->live_matrix.position.y)
00446ad5        long double temp2_1 = fconvert.t(0f)
00446ad5        x87_r7_35 - temp2_1
00446adb        struct Vec4* eax_12
00446adb        eax_12.w = (x87_r7_35 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_35, temp2_1) ? 1 : 0) << 0xa | (x87_r7_35 == temp2_1 ? 1 : 0) << 0xe
00446adf        if ((1 & eax_12:1.b) != 0)
00446ae1        cutscene_ai->live_matrix.position.y = 0f
00446aee        look_at_point(&cutscene_ai->live_matrix, &presentation_10->live_matrix.position.x)
00446af3        struct Player* player = cutscene_ai->player
00446af6        eax.b = player->__offset(0x84).b
00446afe        if (eax.b == 0)
00446b04        initialize_subgoldy_death(player)
00446b09        eax = cutscene_ai->player
00446b0c        player.b = *(eax + 0x44d)
00446b14        if (player.b == 0)
00446b1a        int32_t var_fc_12 = 0xffffffff
00446b1c        to = 2
00446b25        int32_t eax_13 = play_voice_manager(0x751498, 0xb, to, var_fc_12)
00446b2f        cutscene_ai->player->__offset(0x44d).b = 1
00446b38        cutscene_ai->player->__offset(0x44c).b = 1
00446b44        cutscene_ai->progress = fconvert.s(fconvert.t(cutscene_ai->progress_step) + fconvert.t(cutscene_ai->progress))
00446b4f        return eax_13
00446df1        cutscene_ai->progress = fconvert.s(fconvert.t(cutscene_ai->progress_step) + fconvert.t(cutscene_ai->progress))
00446dfe        return eax
