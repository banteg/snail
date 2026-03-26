/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_cutscene @ 0x4428d0 */

004428d0        void* result = data_4df904
004428dc        struct PlayerPresentationController* presentation_1 = presentation
004428de        presentation.b = *(result + 0x74621)
004428e6        if (presentation.b != 0)
00442e38        return result
004428f5        update_snail_skin_transition(&presentation_1->snail_skin_transition)
004428fa        struct Player* owner_player_2 = presentation_1->owner_player
00442900        long double x87_r7_1 = fconvert.t(owner_player_2->cutscene_pitch_cycle)
00442906        long double temp0_1 = fconvert.t(0f)
00442906        x87_r7_1 - temp0_1
00442911        struct TransformMatrix var_140
00442911        void to
00442911        if ((((x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
004429ce        int16_t eax
004429ce        eax.b = owner_player_2->attachment_exit_pending
004429d6        if (eax.b != 0)
004429e6        __builtin_memcpy(&var_140, &owner_player_2->live_matrix, 0x40)
004429f3        __builtin_memcpy(&to, &owner_player_2->live_matrix, 0x40)
004429f9        set_matrix_rotation_identity(&var_140)
00442a16        linear_interpolate_matrix(&presentation_1->owner_player->live_matrix, &var_140, &to, 0.970000029f)
00442923        owner_player_2->cutscene_pitch_cycle = fconvert.s(fconvert.t(owner_player_2->cutscene_pitch_cycle_step) + fconvert.t(owner_player_2->cutscene_pitch_cycle))
00442929        struct Player* owner_player_3 = presentation_1->owner_player
0044292f        long double x87_r7_4 = fconvert.t(owner_player_3->cutscene_pitch_cycle)
00442935        long double temp1_1 = fconvert.t(1f)
00442935        x87_r7_4 - temp1_1
00442940        if ((((x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00442942        owner_player_3->cutscene_pitch_cycle = 0f
00442957        struct TransformMatrix* eax_2 = &presentation_1->owner_player->live_matrix
00442960        __builtin_memcpy(&var_140, eax_2, 0x40)
0044296d        __builtin_memcpy(&to, eax_2, 0x40)
00442973        set_matrix_rotation_identity(&var_140)
00442990        long double x87_r7_8 = (fconvert.t(-0.785398185f) - fconvert.t(presentation_1->owner_player->cutscene_pitch_cycle) * fconvert.t(6.28318548f)) * fconvert.t(1.39999998f)
00442996        float angle = fconvert.s(x87_r7_8)
0044299a        long double temp3_1 = fconvert.t(-6.28318548f)
0044299a        x87_r7_8 - temp3_1
004429a5        if ((((x87_r7_8 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp3_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004429a7        angle = -6.28318548f
004429b8        rotate_matrix_world_x(&var_140, angle)
00442a16        linear_interpolate_matrix(&presentation_1->owner_player->live_matrix, &var_140, &to, 0.939999998f)
00442a1b        struct Player* owner_player = presentation_1->owner_player
00442a33        __builtin_memcpy(&presentation_1->live_matrix, &owner_player->live_matrix, 0x40)
00442a40        presentation_1->live_matrix.position.x = owner_player->cached_camera_target_world.x
00442a45        float alpha
00442a45        __builtin_strncpy(&alpha, "333?", 4)
00442a4a        presentation_1->live_matrix.position.y = owner_player->cached_camera_target_world.y
00442a50        presentation_1->live_matrix.position.z = owner_player->cached_camera_target_world.z
00442a58        __builtin_memcpy(&var_140, &presentation_1->live_matrix, 0x40)
00442a68        linear_interpolate_matrix(&presentation_1->live_matrix, &var_140, &presentation_1->_pad_c0, alpha)
00442a74        long double x87_r7_9 = fconvert.t(presentation_1->live_matrix.basis_up.y)
00442a77        long double temp2_1 = fconvert.t(0f)
00442a77        x87_r7_9 - temp2_1
00442a7f        presentation_1->live_matrix.position.x = var_140.position.x
00442a85        presentation_1->live_matrix.position.y = var_140.position.y
00442a8c        presentation_1->live_matrix.position.z = var_140.position.z
00442a8f        float eax_10
00442a8f        eax_10.w = (x87_r7_9 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp2_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp2_1 ? 1 : 0) << 0xe
00442a94        if ((eax_10:1.b & 0x41) == 0)
00442a9e        struct Vec4* var_170_3 = &presentation_1->live_matrix.position
00442aaa        rotate_matrix_world_y(&presentation_1->live_matrix, fconvert.s((fconvert.t(presentation_1->live_matrix.position.x) - fconvert.t(presentation_1->_pad_c0[0x30].d)) * fconvert.t(0.800000012f)))
00442ab5        long double x87_r7_14 = fconvert.t(presentation_1->wobble.roll_phase_step) + fconvert.t(presentation_1->wobble.roll_phase)
00442abb        long double temp4_1 = fconvert.t(1f)
00442abb        x87_r7_14 - temp4_1
00442ac1        presentation_1->wobble.roll_phase = fconvert.s(x87_r7_14)
00442ac1        bool c1_1 = unimplemented  {fst dword [ebx+0x15bc], st0}
00442ac7        eax_10.w = (x87_r7_14 < temp4_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_14, temp4_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp4_1 ? 1 : 0) << 0xe | 0x3800
00442acc        if ((eax_10:1.b & 0x41) == 0)
00442ad4        presentation_1->wobble.roll_phase = fconvert.s(x87_r7_14 - fconvert.t(1f))
00442ae4        long double x87_r7_18 = fconvert.t(presentation_1->wobble.lift_phase_step) + fconvert.t(presentation_1->wobble.lift_phase)
00442aea        long double temp5_1 = fconvert.t(1f)
00442aea        x87_r7_18 - temp5_1
00442af0        presentation_1->wobble.lift_phase = fconvert.s(x87_r7_18)
00442af0        bool c1_2 = unimplemented  {fst dword [ebx+0x15c4], st0}
00442af6        eax_10.w = (x87_r7_18 < temp5_1 ? 1 : 0) << 8 | (c1_2 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_18, temp5_1) ? 1 : 0) << 0xa | (x87_r7_18 == temp5_1 ? 1 : 0) << 0xe | 0x3800
00442afb        if ((eax_10:1.b & 0x41) == 0)
00442b03        presentation_1->wobble.lift_phase = fconvert.s(x87_r7_18 - fconvert.t(1f))
00442b1b        float var_40[0x10]
00442b1b        __builtin_memcpy(&var_40, &presentation_1->live_matrix, 0x40)
00442b24        void transform
00442b24        set_matrix_identity(&transform)
00442b35        void* var_170_5 = &transform
00442b4e        rotate_matrix_world_z(&transform, fconvert.s(sine(fconvert.s(fconvert.t(presentation_1->wobble.roll_phase) * fconvert.t(6.28318548f))) * fconvert.t(0.0174499992f)))
00442b5b        float var_80[0x10]
00442b5b        invert_matrix_from_source(&var_80, &presentation_1->live_matrix)
00442b6a        multiply_matrix_in_place(&presentation_1->live_matrix.basis_right.x, &var_80)
00442b82        presentation_1->live_matrix.position.y = fconvert.s(fconvert.t(presentation_1->live_matrix.position.y) + fconvert.t(1.29999995f))
00442b85        multiply_matrix_in_place(&presentation_1->live_matrix, &transform)
00442b9d        presentation_1->live_matrix.position.y = fconvert.s(fconvert.t(presentation_1->live_matrix.position.y) - fconvert.t(1.29999995f))
00442ba0        multiply_matrix_in_place(&presentation_1->live_matrix, &var_40)
00442bb1        struct TransformMatrix* var_170_12 = &presentation_1->live_matrix
00442bb5        long double st0_2 = sine(fconvert.s(fconvert.t(presentation_1->wobble.lift_phase) * fconvert.t(6.28318548f)))
00442c08        presentation_1->live_matrix.position.x = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(st0_2 * fconvert.t(presentation_1->live_matrix.basis_up.x))) * fconvert.t(0.0299999993f))) + fconvert.t(presentation_1->live_matrix.position.x))
00442c12        presentation_1->live_matrix.position.y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(st0_2 * fconvert.t(presentation_1->live_matrix.basis_up.y))) * fconvert.t(0.0299999993f))) + fconvert.t(presentation_1->live_matrix.position.y))
00442c18        presentation_1->live_matrix.position.z = fconvert.s(st0_2 * fconvert.t(presentation_1->live_matrix.basis_up.z) * fconvert.t(0.0299999993f) + fconvert.t(presentation_1->live_matrix.position.z))
00442c1b        long double x87_r7_35 = fconvert.t(presentation_1->invincible_shell._pad_90[4].d)
00442c21        long double temp6_1 = fconvert.t(0f)
00442c21        x87_r7_35 - temp6_1
00442c27        int32_t ecx_17 = __builtin_memcpy(&presentation_1->_pad_c0, &presentation_1->live_matrix, 0x40)
00442c2e        if ((((x87_r7_35 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_35, temp6_1) ? 1 : 0) << 0xa | (x87_r7_35 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00442c3c        int32_t var_170_14 = ecx_17
00442c42        rotate_matrix_world_y(&presentation_1->live_matrix, fconvert.s(fconvert.t(presentation_1->invincible_shell._pad_90[4].d) * fconvert.t(-2.09439516f)))
00442c4d        long double x87_r7_39 = fconvert.t(presentation_1->invincible_shell._pad_90[8].d) + fconvert.t(presentation_1->invincible_shell._pad_90[4].d)
00442c53        presentation_1->invincible_shell._pad_90[4].d = fconvert.s(x87_r7_39)
00442c59        long double temp7_1 = fconvert.t(1f)
00442c59        x87_r7_39 - temp7_1
00442c64        if ((((x87_r7_39 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_39, temp7_1) ? 1 : 0) << 0xa | (x87_r7_39 == temp7_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00442c66        presentation_1->invincible_shell._pad_90[4] = 0
00442c66        presentation_1->invincible_shell._pad_90[5] = 0
00442c66        presentation_1->invincible_shell._pad_90[6] = 0x80
00442c66        presentation_1->invincible_shell._pad_90[7] = 0x3f
00442c70        int16_t eax_11
00442c70        eax_11.b = presentation_1->invincible_shell._pad_90[0xc]
00442c78        if (eax_11.b == 0)
00442d65        __builtin_memcpy(&presentation_1->jetpack_channel.live_matrix, &presentation_1->live_matrix, 0x40)
00442d74        __builtin_memcpy(&presentation_1->weapon_channels[0].live_matrix, &presentation_1->live_matrix, 0x40)
00442d83        __builtin_memcpy(&presentation_1->weapon_channels[2].live_matrix, &presentation_1->live_matrix, 0x40)
00442d92        __builtin_memcpy(&presentation_1->weapon_channels[1].live_matrix, &presentation_1->live_matrix, 0x40)
00442c8a        presentation_1->jetpack_channel.live_matrix.position.x = fconvert.s(fconvert.t(presentation_1->jetpack_channel.release_step.x) + fconvert.t(presentation_1->jetpack_channel.live_matrix.position.x))
00442c9c        presentation_1->jetpack_channel.live_matrix.position.y = fconvert.s(fconvert.t(presentation_1->jetpack_channel.release_step.y) + fconvert.t(presentation_1->jetpack_channel.live_matrix.position.y))
00442cae        presentation_1->jetpack_channel.live_matrix.position.z = fconvert.s(fconvert.t(presentation_1->jetpack_channel.release_step.z) + fconvert.t(presentation_1->jetpack_channel.live_matrix.position.z))
00442cc0        presentation_1->weapon_channels[0].live_matrix.position.x = fconvert.s(fconvert.t(presentation_1->weapon_channels[0].release_step.x) + fconvert.t(presentation_1->weapon_channels[0].live_matrix.position.x))
00442cd2        presentation_1->weapon_channels[0].live_matrix.position.y = fconvert.s(fconvert.t(presentation_1->weapon_channels[0].release_step.y) + fconvert.t(presentation_1->weapon_channels[0].live_matrix.position.y))
00442ce4        presentation_1->weapon_channels[0].live_matrix.position.z = fconvert.s(fconvert.t(presentation_1->weapon_channels[0].release_step.z) + fconvert.t(presentation_1->weapon_channels[0].live_matrix.position.z))
00442cf6        presentation_1->weapon_channels[2].live_matrix.position.x = fconvert.s(fconvert.t(presentation_1->weapon_channels[2].release_step.x) + fconvert.t(presentation_1->weapon_channels[2].live_matrix.position.x))
00442d08        presentation_1->weapon_channels[2].live_matrix.position.y = fconvert.s(fconvert.t(presentation_1->weapon_channels[2].release_step.y) + fconvert.t(presentation_1->weapon_channels[2].live_matrix.position.y))
00442d1a        presentation_1->weapon_channels[2].live_matrix.position.z = fconvert.s(fconvert.t(presentation_1->weapon_channels[2].release_step.z) + fconvert.t(presentation_1->weapon_channels[2].live_matrix.position.z))
00442d2c        presentation_1->weapon_channels[1].live_matrix.position.x = fconvert.s(fconvert.t(presentation_1->weapon_channels[1].release_step.x) + fconvert.t(presentation_1->weapon_channels[1].live_matrix.position.x))
00442d3e        presentation_1->weapon_channels[1].live_matrix.position.y = fconvert.s(fconvert.t(presentation_1->weapon_channels[1].release_step.y) + fconvert.t(presentation_1->weapon_channels[1].live_matrix.position.y))
00442d50        presentation_1->weapon_channels[1].live_matrix.position.z = fconvert.s(fconvert.t(presentation_1->weapon_channels[1].release_step.z) + fconvert.t(presentation_1->weapon_channels[1].live_matrix.position.z))
00442d94        struct Player* owner_player_1 = presentation_1->owner_player
00442da7        __builtin_memcpy(&presentation_1->snail_hotspot_source_matrix_a, &presentation_1->live_matrix, 0x40)
00442dbc        __builtin_memcpy(&presentation_1->snail_hotspot_source_matrix_b, &owner_player_1->live_matrix, 0x40)
00442dc6        presentation_1->snail_hotspot_source_matrix_b.position.x = owner_player_1->cached_camera_target_world.x
00442dcf        presentation_1->snail_hotspot_source_matrix_b.position.y = owner_player_1->cached_camera_target_world.y
00442dd5        presentation_1->snail_hotspot_source_matrix_b.position.z = owner_player_1->cached_camera_target_world.z
00442dda        update_snail_skin(presentation_1)
00442dea        if (presentation_1->cutscene_ai.state != 0)
00442df2        update_cutscene(&presentation_1->cutscene_ai)
00442e01        if (presentation_1->anim_manager.queued_animation_count == 0)
00442e09        int32_t eax_15
00442e09        eax_15.b = presentation_1->owner_player->control_override_active
00442e11        if (eax_15.b == 0)
00442e1b        dispatch_cutscene_animation(presentation_1, 1, 0, 0xffffffff)
00442e2c        return update_jet_particles(&presentation_1->owner_player->_pad_2744[0xc])
