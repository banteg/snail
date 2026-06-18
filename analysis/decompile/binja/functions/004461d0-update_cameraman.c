/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_cameraman @ 0x4461d0 */

004461de        struct Player* player = cameraman->player
004461e4        cameraman->unresolved_cc = 0
00446201        struct CameramanState* cameraman_1 = cameraman
00446233        struct TransformMatrix var_40
00446233        struct TransformMatrix* eax = initialize_matrix_from_values(&var_40, 1f, 0f, 0f, 0f, 0f, 0.946000993f, 0.324162006f, 0f, 0f, -0.324162006f, 0.946000993f, 0f, fconvert.s(fconvert.t(player->cached_camera_target_world.x) * fconvert.t(0.400000006f)), 1.79999995f, -0.5f, 1f)
00446241        __builtin_memcpy(&cameraman->desired_matrix, eax, 0x40)
00446245        orthogonalize_matrix(&cameraman->desired_matrix)
00446250        struct Player* player_3 = cameraman->player
00446256        long double x87_r7_2 = float.t(cameraman->game->first_block_row_count)
00446259        long double temp1 = fconvert.t(player_3->cached_camera_target_world.z)
00446259        x87_r7_2 - temp1
0044625f        int32_t kind
0044625f        kind.w = (x87_r7_2 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1 ? 1 : 0) << 0xe | 0x3800
00446264        if ((kind:1.b & 0x41) != 0)
00446303        cameraman->desired_matrix.position.y = fconvert.s(fconvert.t(player_3->cached_camera_target_world.y) * fconvert.t(0.349999994f) + fconvert.t(cameraman->desired_matrix.position.y))
00446276        long double x87_r7_5 = fconvert.t(player_3->cached_camera_target_world.z) / x87_r7_2 * fconvert.t(1.39999998f) - fconvert.t(0.400000006f)
0044627c        long double temp2_1 = fconvert.t(0f)
0044627c        x87_r7_5 - temp2_1
00446282        kind.w = (x87_r7_5 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp2_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp2_1 ? 1 : 0) << 0xe | 0x3800
00446287        if ((kind:1.b & 1) == 0)
00446293        long double temp3_1 = fconvert.t(1f)
00446293        x87_r7_5 - temp3_1
00446299        kind.w = (x87_r7_5 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp3_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp3_1 ? 1 : 0) << 0xe | 0x3800
0044629e        if ((kind:1.b & 0x41) == 0)
004462a2        x87_r7_5 = fconvert.t(1f)
0044628b        x87_r7_5 = fconvert.t(0f)
004462ae        long double x87_r6_2 = fconvert.t(1f) - x87_r7_5
004462b0        struct Player* player_8 = player_3
004462c1        long double x87_r6_5 = x87_r6_2 * fconvert.t(player_3->cached_camera_target_world.y) * fconvert.t(1.14999998f) + fconvert.t(cameraman->desired_matrix.position.y)
004462c4        cameraman->desired_matrix.position.y = fconvert.s(x87_r6_5)
004462d9        cameraman->desired_matrix.position.y = fconvert.s(x87_r7_5 * fconvert.t(0.349999994f) * fconvert.t(player_3->cached_camera_target_world.y) + x87_r6_5)
004462eb        rotate_matrix_world_x(&cameraman->desired_matrix, fconvert.s(fconvert.t(fconvert.s(x87_r6_2)) * fconvert.t(0.872499943f)))
00446306        struct Player* player_4 = cameraman->player
00446313        struct PathTemplate* template_record_1
00446313        if (player_4->follow_state.active == 1)
00446319        template_record_1 = player_4->follow_state.template_record
0044631f        kind = template_record_1->kind
00446348        if (player_4->follow_state.active == 1 && (kind == 0x10 || kind == 8 || kind == 9 || kind == 0xa || kind == 0x2b || kind == 0x2d || kind == 0x24 || kind == 0xe))
00446356        long double x87_r7_18 = (fconvert.t(player_4->live_matrix.position.z) - fconvert.t(player_4->follow_state.source_cell->anchor_position.z)) / fconvert.t(template_record_1->segment_count_f)
00446359        long double temp5_1 = fconvert.t(0f)
00446359        x87_r7_18 - temp5_1
0044635f        struct TrackRowCell* eax_1
0044635f        eax_1.w = (x87_r7_18 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_18, temp5_1) ? 1 : 0) << 0xa | (x87_r7_18 == temp5_1 ? 1 : 0) << 0xe | 0x3800
00446364        if ((eax_1:1.b & 1) == 0)
00446370        long double temp7_1 = fconvert.t(1f)
00446370        x87_r7_18 - temp7_1
00446376        eax_1.w = (x87_r7_18 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_18, temp7_1) ? 1 : 0) << 0xa | (x87_r7_18 == temp7_1 ? 1 : 0) << 0xe | 0x3800
0044637b        if ((eax_1:1.b & 0x41) == 0)
0044637f        x87_r7_18 = fconvert.t(1f)
00446368        x87_r7_18 = fconvert.t(0f)
0044638b        struct Player* player_9 = player_4
0044638f        long double st0_1
0044638f        st0_1, kind = cosine(fconvert.s(x87_r7_18 * fconvert.t(6.28318548f)))
004463a9        cameraman->attachment_lift_envelope = fconvert.s((fconvert.t(0.5f) - st0_1 * fconvert.t(0.5f)) * fconvert.t(0.349999994f))
004463b1        cameraman->attachment_lift_envelope = 0f
004463bb        struct Player* player_5 = cameraman->player
004463c1        long double x87_r7_26 = fconvert.t(player_5->cutscene_pitch_cycle)
004463c7        long double temp4 = fconvert.t(0f)
004463c7        x87_r7_26 - temp4
004463cd        kind.w = (x87_r7_26 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp4) ? 1 : 0) << 0xa | (x87_r7_26 == temp4 ? 1 : 0) << 0xe
004463d2        if ((kind:1.b & 0x41) == 0)
004463e0        struct Player* player_10 = player_5
004463ea        long double st0_2
004463ea        st0_2, kind = cosine(fconvert.s(fconvert.t(player_5->cutscene_pitch_cycle) * fconvert.t(4.71238899f) + fconvert.t(1.57079637f)))
0044640a        cameraman->attachment_lift_envelope = fconvert.s((fconvert.t(0.5f) - st0_2 * fconvert.t(0.5f)) * fconvert.t(0.239999995f) + fconvert.t(cameraman->attachment_lift_envelope))
0044641c        struct Player* player_6 = cameraman->player
00446428        long double x87_r7_38 = (fconvert.t(cameraman->attachment_lift_envelope) - fconvert.t(cameraman->smoothed_attachment_lift_envelope)) * fconvert.t(0.100000001f) + fconvert.t(cameraman->smoothed_attachment_lift_envelope)
0044642e        cameraman->smoothed_attachment_lift_envelope = fconvert.s(x87_r7_38)
0044643d        cameraman->desired_matrix.position.y = fconvert.s(x87_r7_38 * fconvert.t(player_6->cached_camera_target_world.y) + fconvert.t(cameraman->desired_matrix.position.y))
0044644f        cameraman->desired_matrix.position.x = fconvert.s(fconvert.t(player_6->cached_camera_target_world.x) * fconvert.t(0.333333343f) + fconvert.t(cameraman->desired_matrix.position.x))
0044645b        long double x87_r7_46 = fconvert.t(player_6->cached_camera_target_world.z) + fconvert.t(cameraman->desired_matrix.position.z) + fconvert.t(0.400000006f)
00446461        cameraman->desired_matrix.position.z = fconvert.s(x87_r7_46)
00446466        long double x87_r6_11 = x87_r7_46 - fconvert.t(cameraman->previous_desired_matrix.position.z)
0044646c        long double temp6 = fconvert.t(3f)
0044646c        x87_r6_11 - temp6
00446472        kind.w = (x87_r6_11 < temp6 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_11, temp6) ? 1 : 0) << 0xa | (x87_r6_11 == temp6 ? 1 : 0) << 0xe | 0x3000
00446477        if ((kind:1.b & 0x41) != 0)
00446489        long double temp8_1 = fconvert.t(1.70000005f)
00446489        x87_r6_11 - temp8_1
0044648f        kind.w = (x87_r6_11 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_11, temp8_1) ? 1 : 0) << 0xa | (x87_r6_11 == temp8_1 ? 1 : 0) << 0xe | 0x3800
00446494        if ((kind:1.b & 1) != 0)
0044649c        cameraman->previous_desired_matrix.position.z = fconvert.s(x87_r7_46 - fconvert.t(1.70000005f))
00446481        cameraman->previous_desired_matrix.position.z = fconvert.s(x87_r7_46 - fconvert.t(3f))
004464be        long double x87_r7_54 = (fconvert.t(-2f) - (fconvert.t(player_6->cached_camera_target_world.y) - fconvert.t(0.49000001f)) * fconvert.t(5f)) * fconvert.t(0.0174499992f)
004464c4        float angle = fconvert.s(x87_r7_54)
004464c8        long double temp9 = fconvert.t(-1.22149992f)
004464c8        x87_r7_54 - temp9
004464ce        kind.w = (x87_r7_54 < temp9 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_54, temp9) ? 1 : 0) << 0xa | (x87_r7_54 == temp9 ? 1 : 0) << 0xe
004464d3        if ((kind:1.b & 1) == 0)
004464df        long double x87_r7_55 = fconvert.t(angle)
004464e3        long double temp10_1 = fconvert.t(1.22149992f)
004464e3        x87_r7_55 - temp10_1
004464e9        kind.w = (x87_r7_55 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_55, temp10_1) ? 1 : 0) << 0xa | (x87_r7_55 == temp10_1 ? 1 : 0) << 0xe
004464ee        if ((kind:1.b & 0x41) == 0)
004464f0        angle = 1.22149992f
004464d5        angle = -1.22149992f
004464ff        int32_t ecx_5 = rotate_matrix_world_x(&cameraman->desired_matrix, angle)
00446504        struct Player* player_7 = cameraman->player
0044650a        int32_t var_58_5 = ecx_5
00446535        long double x87_r7_62 = (fconvert.t(0.5f) - cosine(fconvert.s(fconvert.t(player_7->lane_lean_progress) * fconvert.t(3.14159274f))) * fconvert.t(0.5f)) * fconvert.t(player_7->lane_lean_amplitude) * fconvert.t(6.28318548f)
00446558        rotate_matrix_world_z(&cameraman->desired_matrix, fconvert.s(x87_r7_62 + fconvert.t(player_7->cached_camera_target_world.x) * fconvert.t(-8f) * fconvert.t(0.0174499992f) * fconvert.t(0.170000002f)))
0044656a        if (cameraman->player->follow_state.active == 1)
00446570        set_matrix_identity(&var_40)
00446586        rotate_matrix_world_z(&var_40, cameraman->player->follow_state.orientation_a)
00446592        multiply_matrix_in_place(&cameraman->desired_matrix, &var_40)
004465a6        rotate_matrix_world_z(&cameraman->desired_matrix, cameraman->player->follow_state.orientation_b)
004465ab        struct Player* player_1 = cameraman->player
004465b9        if (player_1->attachment_exit_pending != 0)
004465c4        rotate_matrix_world_z(&cameraman->desired_matrix, player_1->post_follow_exit_roll)
004465d8        struct PathTemplate* template_record = rotate_matrix_world_z(&cameraman->desired_matrix, cameraman->player->heading_roll)
004465dd        struct Player* player_2 = cameraman->player
004465ea        if (player_2->follow_state.active == 1)
004465f0        template_record = player_2->follow_state.template_record
004465fa        long double x87_r7_75
004465fa        if (player_2->follow_state.active != 1 || template_record->kind != PATH_TEMPLATE_KIND_WORM)
00446679        x87_r7_75 = fconvert.t(110f)
00446608        long double x87_r7_66 = (fconvert.t(player_2->live_matrix.position.z) - fconvert.t(player_2->follow_state.source_cell->anchor_position.z)) / fconvert.t(template_record->segment_count_f)
0044660b        long double temp11_1 = fconvert.t(0f)
0044660b        x87_r7_66 - temp11_1
00446611        player_2.w = (x87_r7_66 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_66, temp11_1) ? 1 : 0) << 0xa | (x87_r7_66 == temp11_1 ? 1 : 0) << 0xe | 0x3800
00446616        if ((player_2:1.b & 1) == 0)
00446622        long double temp12_1 = fconvert.t(1f)
00446622        x87_r7_66 - temp12_1
00446628        player_2.w = (x87_r7_66 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_66, temp12_1) ? 1 : 0) << 0xa | (x87_r7_66 == temp12_1 ? 1 : 0) << 0xe | 0x3800
0044662d        if ((player_2:1.b & 0x41) == 0)
00446631        x87_r7_66 = fconvert.t(1f)
0044661a        x87_r7_66 = fconvert.t(0f)
0044663d        struct PathTemplate* template_record_3 = template_record
00446641        long double st0_4
00446641        st0_4, template_record = cosine(fconvert.s(x87_r7_66 * fconvert.t(6.28318548f)))
0044664c        struct PathTemplate* template_record_2 = template_record
0044664d        long double x87_r7_72 = fconvert.t(0.5f) - st0_4 * fconvert.t(0.5f)
00446657        template_record_2.q = fconvert.d(x87_r7_72)
0044665a        char* var_60_1 = "Worm scale %f\n"
00446671        x87_r7_75 = fconvert.t(fconvert.s(x87_r7_72)) * fconvert.t(50f) + fconvert.t(110f)
00446685        struct Game* game = cameraman->game
0044668b        struct PathTemplate* template_record_4 = template_record
004466a0        cameraman->fov_degrees = fconvert.s((x87_r7_75 - fconvert.t(cameraman->fov_degrees)) * fconvert.t(0.300000012f) + fconvert.t(cameraman->fov_degrees))
004466b4        int32_t result
004466b4        int32_t ebx_1
004466b4        result, ebx_1 = linear_interpolate_matrix(cameraman, &cameraman->previous_desired_matrix, &cameraman->desired_matrix, fconvert.s(fconvert.t(game->subgame_rate) * fconvert.t(0.300000012f)))
004466c0        __builtin_memcpy(&cameraman->previous_desired_matrix, ebx_1, 0x40)
004466c9        return result
