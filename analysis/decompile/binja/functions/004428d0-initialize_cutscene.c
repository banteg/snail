/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_cutscene @ 0x4428d0 */

004428e6        if (g_game_base->subgame.subgame_pause_gate != 0)
004428e6        return
004428f5        update_snail_skin_transition(&snail->snail_skin)
004428fa        struct Player* owner_player_2 = snail->owner_player
00442900        long double x87_r7_1 = fconvert.t(owner_player_2->cutscene_pitch_cycle)
00442906        long double temp0_1 = fconvert.t(0f)
00442906        x87_r7_1 - temp0_1
0044290c        int16_t eax_1 = (x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe
00442911        struct TransformMatrix var_140
00442911        void to
00442911        if ((eax_1:1.b & 0x41) != 0)
004429ce        eax_1.b = owner_player_2->attachment_exit_pending
004429d6        if (eax_1.b != 0)
004429e6        __builtin_memcpy(&var_140, &owner_player_2->body.transform, 0x40)
004429f3        __builtin_memcpy(&to, &owner_player_2->body.transform, 0x40)
004429f9        set_matrix_rotation_identity(&var_140)
00442a16        linear_interpolate_matrix(&snail->owner_player->body.transform, &var_140, &to, 0.970000029f)
00442923        owner_player_2->cutscene_pitch_cycle = fconvert.s(fconvert.t(owner_player_2->cutscene_pitch_cycle_step) + fconvert.t(owner_player_2->cutscene_pitch_cycle))
00442929        struct Player* owner_player_3 = snail->owner_player
0044292f        long double x87_r7_4 = fconvert.t(owner_player_3->cutscene_pitch_cycle)
00442935        long double temp1_1 = fconvert.t(1f)
00442935        x87_r7_4 - temp1_1
00442940        if ((((x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00442942        owner_player_3->cutscene_pitch_cycle = 0f
00442957        struct TransformMatrix* eax_3 = &snail->owner_player->body.transform
00442960        __builtin_memcpy(&var_140, eax_3, 0x40)
0044296d        __builtin_memcpy(&to, eax_3, 0x40)
00442973        set_matrix_rotation_identity(&var_140)
00442990        long double x87_r7_8 = (fconvert.t(-0.785398185f) - fconvert.t(snail->owner_player->cutscene_pitch_cycle) * fconvert.t(6.28318548f)) * fconvert.t(1.39999998f)
00442996        float angle = fconvert.s(x87_r7_8)
0044299a        long double temp3_1 = fconvert.t(-6.28318548f)
0044299a        x87_r7_8 - temp3_1
004429a5        if ((((x87_r7_8 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp3_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004429a7        angle = -6.28318548f
004429b8        rotate_matrix_local_x(&var_140, angle)
00442a16        linear_interpolate_matrix(&snail->owner_player->body.transform, &var_140, &to, 0.939999998f)
00442a1b        struct Player* owner_player = snail->owner_player
00442a33        __builtin_memcpy(&snail->body.transform, &owner_player->body.transform, 0x40)
00442a40        snail->body.transform.position.x = owner_player->cached_camera_target_world.x
00442a45        float alpha
00442a45        __builtin_strncpy(&alpha, "333?", 4)
00442a4a        snail->body.transform.position.y = owner_player->cached_camera_target_world.y
00442a50        snail->body.transform.position.z = owner_player->cached_camera_target_world.z
00442a58        __builtin_memcpy(&var_140, &snail->body.transform, 0x40)
00442a68        linear_interpolate_matrix(&snail->body.transform, &var_140, &snail->cached_cutscene_matrix, alpha)
00442a74        long double x87_r7_9 = fconvert.t(snail->body.transform.basis_up.y)
00442a77        long double temp2_1 = fconvert.t(0f)
00442a77        x87_r7_9 - temp2_1
00442a7f        snail->body.transform.position.x = var_140.position.x
00442a85        snail->body.transform.position.y = var_140.position.y
00442a8c        snail->body.transform.position.z = var_140.position.z
00442a94        if ((((x87_r7_9 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp2_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00442a9e        struct Vec3* var_170_3 = &snail->body.transform.position
00442aaa        rotate_matrix_local_y(&snail->body.transform, fconvert.s((fconvert.t(snail->body.transform.position.x) - fconvert.t(snail->cached_cutscene_matrix.position.x)) * fconvert.t(0.800000012f)))
00442ab5        long double x87_r7_14 = fconvert.t(snail->wobble.roll_phase_step) + fconvert.t(snail->wobble.roll_phase)
00442abb        long double temp4_1 = fconvert.t(1f)
00442abb        x87_r7_14 - temp4_1
00442ac1        snail->wobble.roll_phase = fconvert.s(x87_r7_14)
00442ac1        bool c1_1 = unknown  {fst dword [ebx+0x15bc], st0}
00442acc        if ((((x87_r7_14 < temp4_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_14, temp4_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp4_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00442ad4        snail->wobble.roll_phase = fconvert.s(x87_r7_14 - fconvert.t(1f))
00442ae4        long double x87_r7_18 = fconvert.t(snail->wobble.lift_phase_step) + fconvert.t(snail->wobble.lift_phase)
00442aea        long double temp5_1 = fconvert.t(1f)
00442aea        x87_r7_18 - temp5_1
00442af0        snail->wobble.lift_phase = fconvert.s(x87_r7_18)
00442af0        bool c1_2 = unknown  {fst dword [ebx+0x15c4], st0}
00442afb        if ((((x87_r7_18 < temp5_1 ? 1 : 0) << 8 | (c1_2 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_18, temp5_1) ? 1 : 0) << 0xa | (x87_r7_18 == temp5_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00442b03        snail->wobble.lift_phase = fconvert.s(x87_r7_18 - fconvert.t(1f))
00442b1b        struct TransformMatrix rhs
00442b1b        __builtin_memcpy(&rhs, &snail->body.transform, 0x40)
00442b24        struct TransformMatrix var_c0
00442b24        set_matrix_identity(&var_c0)
00442b35        struct TransformMatrix* var_170_5 = &var_c0
00442b4e        rotate_matrix_local_z(&var_c0, fconvert.s(sine(fconvert.s(fconvert.t(snail->wobble.roll_phase) * fconvert.t(6.28318548f))) * fconvert.t(0.0174499992f)))
00442b5b        struct TransformMatrix var_80
00442b5b        invert_matrix_from_source(&var_80, &snail->body.transform)
00442b6a        multiply_matrix(&snail->body.transform, &var_80)
00442b82        snail->body.transform.position.y = fconvert.s(fconvert.t(snail->body.transform.position.y) + fconvert.t(1.29999995f))
00442b85        multiply_matrix(&snail->body.transform, &var_c0)
00442b9d        snail->body.transform.position.y = fconvert.s(fconvert.t(snail->body.transform.position.y) - fconvert.t(1.29999995f))
00442ba0        multiply_matrix(&snail->body.transform, &rhs)
00442bb1        struct TransformMatrix* var_170_12 = &snail->body.transform
00442bb5        long double st0_2 = sine(fconvert.s(fconvert.t(snail->wobble.lift_phase) * fconvert.t(6.28318548f)))
00442c08        snail->body.transform.position.x = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(st0_2 * fconvert.t(snail->body.transform.basis_up.x))) * fconvert.t(0.0299999993f))) + fconvert.t(snail->body.transform.position.x))
00442c12        snail->body.transform.position.y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(st0_2 * fconvert.t(snail->body.transform.basis_up.y))) * fconvert.t(0.0299999993f))) + fconvert.t(snail->body.transform.position.y))
00442c18        snail->body.transform.position.z = fconvert.s(st0_2 * fconvert.t(snail->body.transform.basis_up.z) * fconvert.t(0.0299999993f) + fconvert.t(snail->body.transform.position.z))
00442c1b        long double x87_r7_35 = fconvert.t(snail->invincible_shell.cutscene_roll_progress)
00442c21        long double temp6_1 = fconvert.t(0f)
00442c21        x87_r7_35 - temp6_1
00442c27        int32_t ecx_18 = __builtin_memcpy(&snail->cached_cutscene_matrix, &snail->body.transform, 0x40)
00442c2e        if ((((x87_r7_35 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_35, temp6_1) ? 1 : 0) << 0xa | (x87_r7_35 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00442c3c        int32_t var_170_14 = ecx_18
00442c42        rotate_matrix_local_y(&snail->body.transform, fconvert.s(fconvert.t(snail->invincible_shell.cutscene_roll_progress) * fconvert.t(-2.09439516f)))
00442c4d        long double x87_r7_39 = fconvert.t(snail->invincible_shell.cutscene_roll_step) + fconvert.t(snail->invincible_shell.cutscene_roll_progress)
00442c53        snail->invincible_shell.cutscene_roll_progress = fconvert.s(x87_r7_39)
00442c59        long double temp7_1 = fconvert.t(1f)
00442c59        x87_r7_39 - temp7_1
00442c64        if ((((x87_r7_39 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_39, temp7_1) ? 1 : 0) << 0xa | (x87_r7_39 == temp7_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00442c66        snail->invincible_shell.cutscene_roll_progress = 1f
00442c78        if (snail->invincible_shell.channel_release_steps_active == 0)
00442d65        __builtin_memcpy(&snail->jetpack_channel.body.transform, &snail->body.transform, 0x40)
00442d74        __builtin_memcpy(&snail->weapon_channels[0].body.transform, &snail->body.transform, 0x40)
00442d83        __builtin_memcpy(&snail->weapon_channels[2].body.transform, &snail->body.transform, 0x40)
00442d92        __builtin_memcpy(&snail->weapon_channels[1].body.transform, &snail->body.transform, 0x40)
00442c8a        snail->jetpack_channel.body.transform.position.x = fconvert.s(fconvert.t(snail->jetpack_channel.release_step.x) + fconvert.t(snail->jetpack_channel.body.transform.position.x))
00442c9c        snail->jetpack_channel.body.transform.position.y = fconvert.s(fconvert.t(snail->jetpack_channel.release_step.y) + fconvert.t(snail->jetpack_channel.body.transform.position.y))
00442cae        snail->jetpack_channel.body.transform.position.z = fconvert.s(fconvert.t(snail->jetpack_channel.release_step.z) + fconvert.t(snail->jetpack_channel.body.transform.position.z))
00442cc0        snail->weapon_channels[0].body.transform.position.x = fconvert.s(fconvert.t(snail->weapon_channels[0].release_step.x) + fconvert.t(snail->weapon_channels[0].body.transform.position.x))
00442cd2        snail->weapon_channels[0].body.transform.position.y = fconvert.s(fconvert.t(snail->weapon_channels[0].release_step.y) + fconvert.t(snail->weapon_channels[0].body.transform.position.y))
00442ce4        snail->weapon_channels[0].body.transform.position.z = fconvert.s(fconvert.t(snail->weapon_channels[0].release_step.z) + fconvert.t(snail->weapon_channels[0].body.transform.position.z))
00442cf6        snail->weapon_channels[2].body.transform.position.x = fconvert.s(fconvert.t(snail->weapon_channels[2].release_step.x) + fconvert.t(snail->weapon_channels[2].body.transform.position.x))
00442d08        snail->weapon_channels[2].body.transform.position.y = fconvert.s(fconvert.t(snail->weapon_channels[2].release_step.y) + fconvert.t(snail->weapon_channels[2].body.transform.position.y))
00442d1a        snail->weapon_channels[2].body.transform.position.z = fconvert.s(fconvert.t(snail->weapon_channels[2].release_step.z) + fconvert.t(snail->weapon_channels[2].body.transform.position.z))
00442d2c        snail->weapon_channels[1].body.transform.position.x = fconvert.s(fconvert.t(snail->weapon_channels[1].release_step.x) + fconvert.t(snail->weapon_channels[1].body.transform.position.x))
00442d3e        snail->weapon_channels[1].body.transform.position.y = fconvert.s(fconvert.t(snail->weapon_channels[1].release_step.y) + fconvert.t(snail->weapon_channels[1].body.transform.position.y))
00442d50        snail->weapon_channels[1].body.transform.position.z = fconvert.s(fconvert.t(snail->weapon_channels[1].release_step.z) + fconvert.t(snail->weapon_channels[1].body.transform.position.z))
00442d94        struct Player* owner_player_1 = snail->owner_player
00442da7        __builtin_memcpy(&snail->snail_hotspot_source_body.transform, &snail->body.transform, 0x40)
00442dbc        __builtin_memcpy(&snail->snail_hotspot_body.transform, &owner_player_1->body.transform, 0x40)
00442dc6        snail->snail_hotspot_body.transform.position.x = owner_player_1->cached_camera_target_world.x
00442dcf        snail->snail_hotspot_body.transform.position.y = owner_player_1->cached_camera_target_world.y
00442dd5        snail->snail_hotspot_body.transform.position.z = owner_player_1->cached_camera_target_world.z
00442dda        update_snail_skin(snail)
00442dea        if (snail->cutscene.state != CUT_SCENE_STATE_INACTIVE)
00442df2        update_cutscene(&snail->cutscene)
00442e11        if (snail->anim_manager.queue_count == 0 && snail->owner_player->control_override_active == 0)
00442e1b        dispatch_cutscene_animation(snail, 1, 0, 0xffffffff)
00442e2c        update_jet_particles(&snail->owner_player->sub_hover)
00442e38        return
