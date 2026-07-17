/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_subgoldy @ 0x43b120 */

0043b134        if (player->game->subgame_pause_gate == 0)
0043b18a        if (player->follow_state.active != 1)
0043b1e1        struct Object* object = player->presentation.body.bod.object
0043b1fb        object->distort.z_wave = fconvert.s(fneg(fconvert.t(object->distort.z_wave)) * fconvert.t(0.100000001f) + fconvert.t(object->distort.z_wave))
0043b18c        struct Path* template_record = player->follow_state.template_record
0043b198        int32_t eax_2 = player->follow_state.sample_index + 3
0043b19b        uint32_t segment_count = template_record->segment_count
0043b1a0        if (eax_2 s>= segment_count)
0043b1a2        eax_2 = segment_count - 1
0043b1ac        struct Object* object_2 = player->presentation.body.bod.object
0043b1d9        object_2->distort.z_wave = fconvert.s((fconvert.t((&template_record->primary_samples->lateral_source)[eax_2 * 0x2a]) * fconvert.t(-3f) - fconvert.t(object_2->distort.z_wave)) * fconvert.t(0.100000001f) + fconvert.t(object_2->distort.z_wave))
0043b209        update_squidge(&player->squidge)
0043b216        player->presentation.body.bod.object->distort.y_squash = player->squidge.y_output
0043b21c        struct Object* object_1 = player->presentation.body.bod.object
0043b222        float z_output = player->squidge.z_output
0043b228        object_1->distort.xyz_scale.b = z_output.b
0043b228        object_1->distort.xyz_scale:1.b = z_output:1.b
0043b228        object_1->distort.xyz_scale:2.b = z_output:2.b
0043b228        object_1->distort.xyz_scale:3.b = z_output:3.b
0043b239        if (player->game->level_mode == 0)
0043b23d        show_subgoldy_lives(player)
0043b242        int32_t movement_mode_selector = player->movement_mode_selector
0043b258        if (movement_mode_selector != 0 && movement_mode_selector != 2)
0043b25e        struct SubgameRuntime* game = player->game
0043b275        if (game->replay_update_cursor s> 0x14 && game->track_state_latch == 0)
0043b277        game->track_state_latch = 1
0043b27e        struct SubgameRuntime* eax_8 = player->game
0043b291        struct Vec3* ebx_1
0043b291        long double st0_1
0043b291        int16_t top_1
0043b291        struct SubgameRuntime* game_2
0043b291        if (eax_8->selected_level_record_active == 0)
0043b360        label_43b360:
0043b360        int16_t eax_11
0043b360        eax_11.b = player->follow_state.flag_3c
0043b368        if (eax_11.b == 0)
0043b38a        label_43b38a:
0043b38a        eax_11.b = player->control_override_active
0043b392        if (eax_11.b == 0)
0043b403        resolve_uncaptured_cursor_sensitivity_scale(g_runtime_config.steering_sensitivity[player->steering_mode_selector])
0043b41c        long double x87_r7_21 = fconvert.t(player->control_source->steering_x) - fconvert.t(player->track_z_anchor) + fconvert.t(player->track_z_offset)
0043b422        long double temp3_1 = fconvert.t(0f)
0043b422        x87_r7_21 - temp3_1
0043b428        player->track_z_offset = fconvert.s(x87_r7_21)
0043b428        bool c1_1 = unknown  {fst dword [ebp+0x273c], st0}
0043b433        if ((((x87_r7_21 < temp3_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_21, temp3_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp3_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
0043b43f        long double temp5_1 = fconvert.t(639f)
0043b43f        x87_r7_21 - temp5_1
0043b44a        if ((((x87_r7_21 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp5_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp5_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0043b44e        x87_r7_21 = fconvert.t(639f)
0043b437        x87_r7_21 = fconvert.t(0f)
0043b454        player->track_z_offset = fconvert.s(x87_r7_21)
0043b463        player->track_z_anchor = player->control_source->steering_x
0043b472        if (player->steering_mode_selector == 1)
0043b47d        player->track_z_offset = fconvert.s(fconvert.t(player->control_source->steering_x))
0043b394        long double x87_r7_11 = fconvert.t(player->presentation.body.transform.basis_up.x)
0043b39c        long double x87_r7_13 = fconvert.t(player->track_z_offset) - (x87_r7_11 + x87_r7_11)
0043b3a2        player->track_z_offset = fconvert.s(x87_r7_13)
0043b3a8        player->track_z_anchor = fconvert.s(x87_r7_13)
0043b3ae        long double x87_r7_14 = fconvert.t(player->track_z_offset)
0043b3b4        long double temp4_1 = fconvert.t(0f)
0043b3b4        x87_r7_14 - temp4_1
0043b3ba        eax_11 = (x87_r7_14 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp4_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp4_1 ? 1 : 0) << 0xe
0043b3bf        long double x87_r7_15
0043b3bf        if ((eax_11:1.b & 1) == 0)
0043b3cc        long double x87_r7_16 = fconvert.t(player->track_z_offset)
0043b3d2        long double temp6_1 = fconvert.t(639f)
0043b3d2        x87_r7_16 - temp6_1
0043b3d8        eax_11 = (x87_r7_16 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_16, temp6_1) ? 1 : 0) << 0xa | (x87_r7_16 == temp6_1 ? 1 : 0) << 0xe
0043b3dd        if ((eax_11:1.b & 0x41) != 0)
0043b3ea        x87_r7_15 = fconvert.t(player->track_z_offset)
0043b3df        x87_r7_15 = fconvert.t(639f)
0043b3c1        x87_r7_15 = fconvert.t(0f)
0043b47d        player->track_z_offset = fconvert.s(x87_r7_15)
0043b36a        eax_11.b = player->completion_handoff_active
0043b372        if (eax_11.b == 0)
0043b372        goto label_43b38a
0043b379        player->track_z_offset = 320f
0043b37f        player->track_z_anchor = 320f
0043b483        eax_11.b = player->completion_handoff_active
0043b48b        if (eax_11.b == 0)
0043b499        long double x87_r7_26 = (fconvert.t(320f) - fconvert.t(player->track_z_offset)) * fconvert.t(0.0125000002f)
0043b49f        long double temp7_1 = fconvert.t(-3.70000005f)
0043b49f        x87_r7_26 - temp7_1
0043b4aa        if ((((x87_r7_26 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp7_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp7_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
0043b4b6        long double temp8_1 = fconvert.t(3.70000005f)
0043b4b6        x87_r7_26 - temp8_1
0043b4c1        if ((((x87_r7_26 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp8_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp8_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0043b4c5        x87_r7_26 = fconvert.t(3.70000005f)
0043b4ae        x87_r7_26 = fconvert.t(-3.70000005f)
0043b4d1        if (player->click_start.state != CLICK_START_STATE_WAITING_FOR_START)
0043b4ec        player->body.transform.position.x = fconvert.s(fconvert.t(player->game->subgame_rate) * fconvert.t(0.200000003f) * (x87_r7_26 - fconvert.t(player->body.transform.position.x)) + fconvert.t(player->body.transform.position.x))
0043b4f6        ebx_1 = &player->body.transform.position
0043b504        int16_t eax_17
0043b504        int80_t st0_3
0043b504        st0_3, eax_17 = convert_math_type32_to_16(player->body.transform.position.x, 16f)
0043b50d        long double st0_4 = convert_math_type16_to_32(eax_17, 16f)
0043b51f        ebx_1->x = fconvert.s(st0_4)
0043b521        struct SubgameRuntime* game_20 = player->game
0043b528        int16_t eax_19
0043b528        int80_t st0_5
0043b528        st0_5, eax_19 = convert_math_type32_to_16(fconvert.s(st0_4), 16f)
0043b536        int32_t ecx_25 = game_20->replay_update_cursor * 3
0043b53e        *(&game_20->current_high_score_record.run_records + (ecx_25 << 1)) = eax_19
0043b546        struct SubgameRuntime* game_18 = player->game
0043b556        long double x87_r4_1
0043b556        struct SubgameRuntime* game_10
0043b556        if (game_18->replay_update_cursor != 0)
0043b5a5        int32_t var_58_4 = ecx_25
0043b5a9        int16_t eax_25
0043b5a9        int80_t st0_7
0043b5a9        st0_7, eax_25 = convert_math_type32_to_16(fconvert.s(fconvert.t(player->body.transform.position.z) - fconvert.t(data_643194)), 32f)
0043b5c2        *(game_18 + (game_18->replay_update_cursor + 0x2a31eb) * 6) = eax_25
0043b5c6        game_10 = player->game
0043b5d2        int32_t eax_27 = game_10->replay_update_cursor + 0x2a31eb
0043b5da        eax_27.w = *(game_10 + eax_27 * 6)
0043b5df        st0_1 = convert_math_type16_to_32(eax_27.w, 32f)
0043b5e4        x87_r4_1 = st0_1 + fconvert.t(data_643194)
0043b55c        int16_t eax_22
0043b55c        int80_t st0_6
0043b55c        st0_6, eax_22 = convert_math_type32_to_16(player->body.transform.position.z, 32f)
0043b575        *(game_18 + (game_18->replay_update_cursor + 0x2a31eb) * 6) = eax_22
0043b579        game_10 = player->game
0043b585        int32_t eax_24 = game_10->replay_update_cursor + 0x2a31eb
0043b58d        eax_24.w = *(game_10 + eax_24 * 6)
0043b592        st0_1 = convert_math_type16_to_32(eax_24.w, 32f)
0043b592        x87_r4_1 = st0_1
0043b5ed        data_643194 = fconvert.s(x87_r4_1)
0043b5ed        top_1 = 0xfffd
0043b5f3        struct SubgameRuntime* game_3 = player->game
0043b601        if (game_3->track_state_latch != 0)
0043b60c        if ((*(player->control_source + 4) & 0x4000) != 0)
0043b614        int32_t edx_11 = game_3->replay_update_cursor * 3
0043b617        (&game_3->current_high_score_record.run_records[0].flags)[edx_11].b |= 1
0043b62f        if ((player->control_source->control_flags_b & 0x4000) != 0)
0043b631        struct SubgameRuntime* game_4 = player->game
0043b63d        int32_t ecx_35 = game_4->replay_update_cursor * 3
0043b640        (&game_4->current_high_score_record.run_records[0].flags)[ecx_35].b |= 2
0043b64f        struct PlayerControlSource* control_source = player->control_source
0043b65d        if ((control_source->control_flags_b & 0x4000) == 0 && (control_source->control_flags_a & 0x4000) == 0)
0043b665        player->game->track_state_latch = 1
0043b66c        game_2 = player->game
0043b67a        if (game_2->track_state_latch != 0)
0043b682        int32_t ecx_37 = game_2->replay_update_cursor * 3
0043b685        (&game_2->current_high_score_record.run_records[0].flags)[ecx_37].b |= 4
0043b297        struct SubSolution* selected_level_record = eax_8->selected_level_record
0043b29d        eax_8 = eax_8->replay_update_cursor
0043b2b2        if (eax_8 s>= selected_level_record->replay_sample_count || player->click_start.state == CLICK_START_STATE_WAITING_FOR_START)
0043b2a6        goto label_43b360
0043b2c0        ebx_1 = &player->body.transform.position
0043b2c3        eax_8.w = selected_level_record->run_records[eax_8].lateral_x
0043b2c9        st0_1 = convert_math_type16_to_32(eax_8.w, 16f)
0043b2ce        ebx_1->x = fconvert.s(st0_1)
0043b2ce        top_1 = 0
0043b2d0        struct SubgameRuntime* game_1 = player->game
0043b2ed        if ((game_1->selected_level_record->run_records[game_1->replay_update_cursor].flags.b & 4) == 0)
0043b2f8        game_1->track_state_latch = 0
0043b2ef        game_1->track_state_latch = 1
0043b2ff        game_2 = player->game
0043b319        if ((game_2->selected_level_record->run_records[game_2->replay_update_cursor].flags.b & 8) != 0)
0043b324        g_game_base->players[0].frontend_state = 0x1a
0043b334        g_game_base->players[0].saved_frontend_state = 0xa
0043b344        g_game_base->players[0].redispatch_requested = 1
0043b353        begin_frontend_fade_in(&g_game_base->fade)
0043b35f        return
0043b694        unimplemented  {fld st0, dword [ebx]}
0043b696        long double temp9_1 = fconvert.t(-4f)
0043b696        unimplemented  {fcomp st0, dword [0x497420]} f- temp9_1
0043b696        bool c0_7 = unimplemented  {fcomp st0, dword [0x497420]} f< temp9_1
0043b696        bool c2_7 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497420]}, temp9_1)
0043b696        bool c3_7 = unimplemented  {fcomp st0, dword [0x497420]} f== temp9_1
0043b696        unimplemented  {fcomp st0, dword [0x497420]}
0043b6a1        if ((((c0_7 ? 1 : 0) << 8 | (c2_7 ? 1 : 0) << 0xa | (c3_7 ? 1 : 0) << 0xe | (top_1 & 7) << 0xb):1.b & 1) != 0)
0043b6a3        ebx_1->x = 0xc0800000
0043b6a9        player->velocity.x = 0
0043b6b3        unimplemented  {fld st0, dword [ebx]}
0043b6b5        long double temp10_1 = fconvert.t(4f)
0043b6b5        unimplemented  {fcomp st0, dword [0x497210]} f- temp10_1
0043b6b5        bool c0_8 = unimplemented  {fcomp st0, dword [0x497210]} f< temp10_1
0043b6b5        bool c2_8 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497210]}, temp10_1)
0043b6b5        bool c3_8 = unimplemented  {fcomp st0, dword [0x497210]} f== temp10_1
0043b6b5        unimplemented  {fcomp st0, dword [0x497210]}
0043b6bb        int16_t eax_31 = (c0_8 ? 1 : 0) << 8 | (c2_8 ? 1 : 0) << 0xa | (c3_8 ? 1 : 0) << 0xe | (top_1 & 7) << 0xb
0043b6c0        if ((eax_31:1.b & 0x41) == 0)
0043b6c2        ebx_1->x = 0x40800000
0043b6c8        player->velocity.x = 0
0043b6d2        eax_31.b = player->resurrect_active.b
0043b6da        if (eax_31.b != 0)
0043b6de        update_subgoldy_resurrect(player)
0043b6ea        struct TrackRowCell* eax_32 = get_track_grid_cell_at_world_position(player->game, ebx_1)
0043b6ef        struct SubgameRuntime* game_21 = player->game
0043b706        int32_t eax_34 = get_track_cell_row_index(eax_32) * 0x3d
0043b710        int32_t row_event_id = (&game_21->runtime_rows[0].row_event_id)[eax_34]
0043b734        if (row_event_id s> 0 && row_event_id != player->row_event.id && row_event_id s< game_21->level_definition.segment_count + 1)
0043b73a        player->row_event.id = row_event_id
0043b764        if (*((&game_21->runtime_rows[0].row_event_id)[eax_34] * 0x4220 + player->game + 0xa670) != 0)
0043b76a        player->row_event.tip_definition.flags = 2
0043b796        player->row_event.tip_definition.text = &player->game[(&game_21->runtime_rows[0].row_event_id)[eax_34] * 0x4220 + 0xa670]
0043b79c        player->row_event.tip_definition.layout_y = 0f
0043b7a6        player->row_event.tip_definition.text_scale = 30f
0043b7d2        player->row_event.tip_definition.dismiss_seconds = *((&game_21->runtime_rows[0].row_event_id)[eax_34] * 0x4220 + player->game + 0xa870)
0043b7d8        int16_t eax_40
0043b7d8        eax_40.b = player->row_event_cutscene_started
0043b7e0        if (eax_40.b == 0)
0043b7e2        player->row_event_cutscene_started = 1
0043b7eb        unimplemented  {fld st0, dword [ebx]}
0043b7ed        long double temp15_1 = fconvert.t(0f)
0043b7ed        unimplemented  {fcomp st0, dword [0x497234]} f- temp15_1
0043b7ed        bool c0_9 = unimplemented  {fcomp st0, dword [0x497234]} f< temp15_1
0043b7ed        bool c2_9 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp15_1)
0043b7ed        bool c3_9 = unimplemented  {fcomp st0, dword [0x497234]} f== temp15_1
0043b7ed        unimplemented  {fcomp st0, dword [0x497234]}
0043b800        int32_t animation_id
0043b800        if ((((c0_9 ? 1 : 0) << 8 | (c2_9 ? 1 : 0) << 0xa | (c3_9 ? 1 : 0) << 0xe | (top_1 & 7) << 0xb):1.b & 0x41) != 0)
0043b806        animation_id = 3
0043b802        animation_id = 4
0043b80a        dispatch_cutscene_animation(&player->presentation, animation_id, 1, 0xffffffff)
0043b817        dispatch_cutscene_animation(&player->presentation, 1, 0, 0xffffffff)
0043b837        int32_t sample_override = *(&player->game->level_definition + (&game_21->runtime_rows[0].row_event_id)[eax_34] * 0x4220)
0043b841        if (sample_override != 0xffffffff)
0043b84d        play_voice_manager(0x751498, 0xd, 2, sample_override)
0043b866        enqueue_tip_message(&g_game_base->tip_manager, &player->row_event.tip_definition, 1)
0043b86b        int16_t eax_43
0043b86b        eax_43.b = player->attachment_exit_pending
0043b873        if (eax_43.b == 0)
0043b879        eax_43.b = eax_32->tile_id
0043b882        if (eax_43.b == 0x1d || eax_43.b == 0x1e)
0043b884        eax_43.b = player->follow_state.active
0043b88c        if (eax_43.b == 0)
0043b89b        begin_track_attachment_follow_state(&player->follow_state, eax_32, ebx_1, player)
0043b8aa        if (player->follow_state.template_record->kind == PATH_TEMPLATE_KIND_WORM)
0043b8b7        play_voice_manager(0x751498, 0xc, 0, 0xffffffff)
0043b8bc        eax_43.b = player->control_override_active
0043b8c4        int16_t top_13
0043b8c4        if (eax_43.b == 0)
0043b91b        unimplemented  {fild st0, dword [ecx+0x50]}
0043b91e        long double temp11_1 = fconvert.t(player->body.transform.position.z)
0043b91e        unimplemented  {fcomp st0, dword [ebp+0x70]} f- temp11_1
0043b91e        bool c0_12 = unimplemented  {fcomp st0, dword [ebp+0x70]} f< temp11_1
0043b91e        bool c2_12 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x70]}, temp11_1)
0043b91e        bool c3_12 = unimplemented  {fcomp st0, dword [ebp+0x70]} f== temp11_1
0043b91e        unimplemented  {fcomp st0, dword [ebp+0x70]}
0043b926        if ((((c0_12 ? 1 : 0) << 8 | (c2_12 ? 1 : 0) << 0xa | (c3_12 ? 1 : 0) << 0xe | (top_1 & 7) << 0xb):1.b & 0x41) == 0)
0043b928        unimplemented  {fld st0, dword [ecx+0x38]}
0043b92b        unimplemented  {fld st0, st0}
0043b92d        unimplemented  {fmul st0, st1}
0043b92f        unimplemented  {fmul st0, dword [0x4973bc]}
0043b935        unimplemented  {fadd dword [ebp+0x418]}
0043b93b        player->velocity.z = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043b93b        unimplemented  {fstp dword [ebp+0x418], st0}
0043b941        unimplemented  {fstp st0, st0}
0043b941        unimplemented  {fstp st0, st0}
0043b943        unimplemented  {fld st0, dword [ebp+0x418]}
0043b949        long double temp13_1 = fconvert.t(1f)
0043b949        unimplemented  {fcomp st0, dword [0x497220]} f- temp13_1
0043b949        bool c0_13 = unimplemented  {fcomp st0, dword [0x497220]} f< temp13_1
0043b949        bool c2_13 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp13_1)
0043b949        bool c3_13 = unimplemented  {fcomp st0, dword [0x497220]} f== temp13_1
0043b949        unimplemented  {fcomp st0, dword [0x497220]}
0043b949        top_13 = top_1
0043b94f        eax_43 = (c0_13 ? 1 : 0) << 8 | (c2_13 ? 1 : 0) << 0xa | (c3_13 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043b954        if ((eax_43:1.b & 0x41) == 0)
0043b956        player->velocity.z = 1f
0043b967        if (player->click_start.state == CLICK_START_STATE_WAITING_FOR_START)
0043b969        player->velocity.z = 0f
0043b8c6        unimplemented  {fld st0, dword [ebp+0x418]}
0043b8cc        long double temp12_1 = fconvert.t(0f)
0043b8cc        unimplemented  {fcomp st0, dword [0x497234]} f- temp12_1
0043b8cc        bool c0_10 = unimplemented  {fcomp st0, dword [0x497234]} f< temp12_1
0043b8cc        bool c2_10 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp12_1)
0043b8cc        bool c3_10 = unimplemented  {fcomp st0, dword [0x497234]} f== temp12_1
0043b8cc        unimplemented  {fcomp st0, dword [0x497234]}
0043b8d7        if ((((c0_10 ? 1 : 0) << 8 | (c2_10 ? 1 : 0) << 0xa | (c3_10 ? 1 : 0) << 0xe | (top_1 & 7) << 0xb):1.b & 1) != 0)
0043b8df        unimplemented  {fld st0, dword [ecx+0x38]}
0043b8e2        unimplemented  {fld st0, st0}
0043b8e4        unimplemented  {fmul st0, st1}
0043b8e6        unimplemented  {fmul st0, dword [0x4973bc]}
0043b8ec        unimplemented  {fmul st0, dword [0x49744c]}
0043b8f2        unimplemented  {fadd dword [ebp+0x418]}
0043b8f8        player->velocity.z = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043b8f8        unimplemented  {fstp dword [ebp+0x418], st0}
0043b8fe        unimplemented  {fstp st0, st0}
0043b8fe        unimplemented  {fstp st0, st0}
0043b900        unimplemented  {fld st0, dword [ebp+0x418]}
0043b906        long double temp14_1 = fconvert.t(0f)
0043b906        unimplemented  {fcomp st0, dword [0x497234]} f- temp14_1
0043b906        bool c0_11 = unimplemented  {fcomp st0, dword [0x497234]} f< temp14_1
0043b906        bool c2_11 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp14_1)
0043b906        bool c3_11 = unimplemented  {fcomp st0, dword [0x497234]} f== temp14_1
0043b906        unimplemented  {fcomp st0, dword [0x497234]}
0043b906        top_13 = top_1
0043b90c        eax_43 = (c0_11 ? 1 : 0) << 8 | (c2_11 ? 1 : 0) << 0xa | (c3_11 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043b911        if ((eax_43:1.b & 0x41) == 0)
0043b969        player->velocity.z = 0f
0043b973        eax_43.b = player->follow_state.active
0043b981        if (eax_43.b != 1)
0043bac4        unimplemented  {fld st0, dword [ebp+0x410]}
0043baca        unimplemented  {fadd dword [ebx]}
0043bacc        ebx_1->x = fconvert.s(unimplemented  {fstp dword [ebx], st0})
0043bacc        unimplemented  {fstp dword [ebx], st0}
0043bace        unimplemented  {fld st0, dword [ebp+0x414]}
0043bad4        unimplemented  {fadd dword [ebx+0x4]}
0043bad7        ebx_1->y = fconvert.s(unimplemented  {fstp dword [ebx+0x4], st0})
0043bad7        unimplemented  {fstp dword [ebx+0x4], st0}
0043bada        unimplemented  {fld st0, dword [ebp+0x418]}
0043bae0        unimplemented  {fadd dword [ebx+0x8]}
0043bae3        ebx_1->z = fconvert.s(unimplemented  {fstp dword [ebx+0x8], st0})
0043bae3        unimplemented  {fstp dword [ebx+0x8], st0}
0043bae6        unimplemented  {fld st0, dword [ebx]}
0043bae8        long double temp16_1 = fconvert.t(-4f)
0043bae8        unimplemented  {fcomp st0, dword [0x497420]} f- temp16_1
0043bae8        bool c0_16 = unimplemented  {fcomp st0, dword [0x497420]} f< temp16_1
0043bae8        bool c2_16 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497420]}, temp16_1)
0043bae8        bool c3_16 = unimplemented  {fcomp st0, dword [0x497420]} f== temp16_1
0043bae8        unimplemented  {fcomp st0, dword [0x497420]}
0043baf3        if ((((c0_16 ? 1 : 0) << 8 | (c2_16 ? 1 : 0) << 0xa | (c3_16 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 1) != 0)
0043baf5        ebx_1->x = 0xc0800000
0043bafb        player->velocity.x = 0
0043bb05        unimplemented  {fld st0, dword [ebx]}
0043bb07        long double temp17_1 = fconvert.t(4f)
0043bb07        unimplemented  {fcomp st0, dword [0x497210]} f- temp17_1
0043bb07        bool c0_17 = unimplemented  {fcomp st0, dword [0x497210]} f< temp17_1
0043bb07        bool c2_17 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497210]}, temp17_1)
0043bb07        bool c3_17 = unimplemented  {fcomp st0, dword [0x497210]} f== temp17_1
0043bb07        unimplemented  {fcomp st0, dword [0x497210]}
0043bb0d        eax_43 = (c0_17 ? 1 : 0) << 8 | (c2_17 ? 1 : 0) << 0xa | (c3_17 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043bb12        if ((eax_43:1.b & 0x41) == 0)
0043bb14        ebx_1->x = 0x40800000
0043bb1a        player->velocity.x = 0
0043bb24        eax_43.b = player->completion_handoff_active
0043bb2c        if (eax_43.b == 0)
0043bb42        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0xf)
0043bba0        label_43bba0:
0043bba0        unimplemented  {fld st0, dword [eax+0x38]}
0043bba3        unimplemented  {fld st0, st0}
0043bba5        unimplemented  {fmul st0, st1}
0043bba7        unimplemented  {fmul st0, dword [0x4973bc]}
0043bbad        unimplemented  {fadd st0, st0}
0043bbaf        unimplemented  {fadd dword [ebp+0x418]}
0043bbb5        player->velocity.z = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043bbb5        unimplemented  {fstp dword [ebp+0x418], st0}
0043bbc1        unimplemented  {fstp st0, st0}
0043bbc1        unimplemented  {fstp st0, st0}
0043bbc3        unimplemented  {fild st0, dword [ecx+0x50]}
0043bbc6        long double temp20_1 = fconvert.t(player->body.transform.position.z)
0043bbc6        unimplemented  {fcomp st0, dword [ebp+0x70]} f- temp20_1
0043bbc6        bool c0_18 = unimplemented  {fcomp st0, dword [ebp+0x70]} f< temp20_1
0043bbc6        bool c2_18 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x70]}, temp20_1)
0043bbc6        bool c3_18 = unimplemented  {fcomp st0, dword [ebp+0x70]} f== temp20_1
0043bbc6        unimplemented  {fcomp st0, dword [ebp+0x70]}
0043bbce        if ((((c0_18 ? 1 : 0) << 8 | (c2_18 ? 1 : 0) << 0xa | (c3_18 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 0x41) != 0)
0043bbd0        unimplemented  {fld st0, dword [ebp+0x70]}
0043bbd3        long double temp23_1 = fconvert.t(player->slide_extension_threshold_z)
0043bbd3        unimplemented  {fcomp st0, dword [ebp+0x2738]} f- temp23_1
0043bbd3        bool c0_19 = unimplemented  {fcomp st0, dword [ebp+0x2738]} f< temp23_1
0043bbd3        bool c2_19 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x2738]}, temp23_1)
0043bbd3        bool c3_19 = unimplemented  {fcomp st0, dword [ebp+0x2738]} f== temp23_1
0043bbd3        unimplemented  {fcomp st0, dword [ebp+0x2738]}
0043bbde        if ((((c0_19 ? 1 : 0) << 8 | (c2_19 ? 1 : 0) << 0xa | (c3_19 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 0x41) == 0)
0043bbe0        unimplemented  {fld st0, dword [ebp+0x70]}
0043bbe3        unimplemented  {fadd dword [0x497220]}
0043bbe9        player->slide_extension_threshold_z = fconvert.s(unimplemented  {fstp dword [ebp+0x2738], st0})
0043bbe9        unimplemented  {fstp dword [ebp+0x2738], st0}
0043bb54        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0x10)
0043bb54        goto label_43bba0
0043bb66        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0x12)
0043bb66        goto label_43bba0
0043bb78        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0x13)
0043bb78        goto label_43bba0
0043bb81        if (player->damage_gauge.state == DAMAGE_GUAGE_STATE_DRAINING && is_sub_loc_floor(get_track_grid_cell_at_world_position(player->game, ebx_1)) != 0)
0043bb98        goto label_43bba0
0043bbf6        if (player->sub_hover.state == SUB_HOVER_STATE_ACTIVE)
0043bbfe        unimplemented  {fld st0, dword [edx+0x38]}
0043bc01        unimplemented  {fld st0, st0}
0043bc03        unimplemented  {fmul st0, st1}
0043bc05        unimplemented  {fmul st0, dword [0x4973bc]}
0043bc0b        unimplemented  {fadd st0, st0}
0043bc0d        unimplemented  {fadd dword [ebp+0x418]}
0043bc13        player->velocity.z = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043bc13        unimplemented  {fstp dword [ebp+0x418], st0}
0043bc19        unimplemented  {fstp st0, st0}
0043bc19        unimplemented  {fstp st0, st0}
0043bc23        if (player->trampoline_bounce_active == 0)
0043bc2b        unimplemented  {fld st0, dword [eax+0x38]}
0043bc2e        unimplemented  {fmul st0, dword [0x4975d0]}
0043bc34        unimplemented  {fsubr st0, dword [0x497220]}
0043bc3a        unimplemented  {fmul st0, dword [ebp+0x418]}
0043bc40        player->velocity.z = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043bc40        unimplemented  {fstp dword [ebp+0x418], st0}
0043bc4c        unimplemented  {fld st0, dword [ecx+0x38]}
0043bc4f        unimplemented  {fmul st0, dword [0x4975d0]}
0043bc55        unimplemented  {fsubr st0, dword [0x497220]}
0043bc5b        unimplemented  {fmul st0, dword [ebp+0x414]}
0043bc61        player->velocity.y = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043bc61        unimplemented  {fstp dword [ebp+0x414], st0}
0043bc6d        unimplemented  {fld st0, dword [edx+0x38]}
0043bc70        unimplemented  {fmul st0, dword [0x497258]}
0043bc76        unimplemented  {fsubr st0, dword [0x497220]}
0043bc7c        unimplemented  {fmul st0, dword [ebp+0x410]}
0043bc82        player->velocity.x = fconvert.s(unimplemented  {fstp dword [ebp+0x410], st0})
0043bc82        unimplemented  {fstp dword [ebp+0x410], st0}
0043bc82        int16_t top_66 = top_13
0043bc90        if (player->boost_one_tick == 0)
0043bcc8        struct TrackRowCell* cell
0043bcc8        int16_t x87control_1
0043bcc8        cell, x87control_1 = get_track_grid_cell_at_world_position(player->game, ebx_1)
0043bcd7        if (player->attachment_exit_pending != 0)
0043bd11        if (((player->game->runtime_rows[get_track_cell_row_index(cell)].flags).w:1.b & 1) == 0 && player->sub_hover.state == SUB_HOVER_STATE_INACTIVE && player->control_override_active == 0)
0043bd13        unimplemented  {fld st0, dword [edi+0x38]}
0043bd16        unimplemented  {fmul st0, dword [0x497270]}
0043bd1c        unimplemented  {fsubr st0, dword [0x497220]}
0043bd22        unimplemented  {fmul st0, dword [ebp+0x418]}
0043bd28        player->velocity.z = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043bd28        unimplemented  {fstp dword [ebp+0x418], st0}
0043bd4c        if ((player->game->runtime_rows[get_track_cell_row_index(cell)].flags.b & 0x40) != 0)
0043bd52        unimplemented  {fld st0, dword [ebp+0x410]}
0043bd58        unimplemented  {fmul st0, dword [0x4975c8]}
0043bd60        float sweep_dx = fconvert.s(unimplemented  {fstp dword [esp+0x14], st0})
0043bd60        unimplemented  {fstp dword [esp+0x14], st0}
0043bd64        unimplemented  {fld st0, dword [ebp+0x414]}
0043bd6a        unimplemented  {fmul st0, dword [0x4975c8]}
0043bd70        float sweep_dy = fconvert.s(unimplemented  {fstp dword [esp+0x18], st0})
0043bd70        unimplemented  {fstp dword [esp+0x18], st0}
0043bd74        unimplemented  {fld st0, dword [ebp+0x418]}
0043bd7a        unimplemented  {fmul st0, dword [0x4975c8]}
0043bd80        float sweep_dz = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
0043bd80        unimplemented  {fstp dword [esp+0x1c], st0}
0043bd98        struct TrackRowCell* source_cell = (&player->game->runtime_rows[0].primary_attachment_cell)[get_track_cell_row_index(cell) * 0x3d]
0043bdf0        x87control_1 = try_enter_track_attachment_from_swept_motion((&player->game->runtime_rows[0].primary_attachment_cell)[get_track_cell_row_index(cell) * 0x3d]->attachment_template_record, ebx_1->x, ebx_1->y, ebx_1->z, sweep_dx, sweep_dy, sweep_dz, source_cell)
0043bdfd        if (player->attachment_exit_pending != 0 && (player->game->runtime_rows[get_track_cell_row_index(cell)].flags.b & 0x80) != 0)
0043be27        unimplemented  {fld st0, dword [ebp+0x410]}
0043be2d        unimplemented  {fmul st0, dword [0x4975c8]}
0043be35        float sweep_dx_1 = fconvert.s(unimplemented  {fstp dword [esp+0x14], st0})
0043be35        unimplemented  {fstp dword [esp+0x14], st0}
0043be39        unimplemented  {fld st0, dword [ebp+0x414]}
0043be3f        unimplemented  {fmul st0, dword [0x4975c8]}
0043be45        float sweep_dy_1 = fconvert.s(unimplemented  {fstp dword [esp+0x18], st0})
0043be45        unimplemented  {fstp dword [esp+0x18], st0}
0043be49        unimplemented  {fld st0, dword [ebp+0x418]}
0043be4f        unimplemented  {fmul st0, dword [0x4975c8]}
0043be55        float sweep_dz_1 = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
0043be55        unimplemented  {fstp dword [esp+0x1c], st0}
0043be6d        struct TrackRowCell* source_cell_1 = (&player->game->runtime_rows[0].secondary_attachment_cell)[get_track_cell_row_index(cell) * 0x3d]
0043bec5        int32_t eax_85
0043bec5        eax_85, x87control_1 = try_enter_track_attachment_from_swept_motion((&player->game->runtime_rows[0].secondary_attachment_cell)[get_track_cell_row_index(cell) * 0x3d]->attachment_template_record, ebx_1->x, ebx_1->y, ebx_1->z, sweep_dx_1, sweep_dy_1, sweep_dz_1, source_cell_1)
0043beca        int16_t eax_86
0043beca        eax_86.b = player->follow_state.active
0043bed2        if (eax_86.b == 0)
0043bed8        unimplemented  {fld st0, dword [ebp+0x6c]}
0043bedb        long double temp30_1 = fconvert.t(0.49000001f)
0043bedb        unimplemented  {fcomp st0, dword [0x4973e8]} f- temp30_1
0043bedb        bool c0_20 = unimplemented  {fcomp st0, dword [0x4973e8]} f< temp30_1
0043bedb        bool c2_20 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4973e8]}, temp30_1)
0043bedb        bool c3_20 = unimplemented  {fcomp st0, dword [0x4973e8]} f== temp30_1
0043bedb        unimplemented  {fcomp st0, dword [0x4973e8]}
0043bedb        int16_t top_82 = top_66
0043beeb        if ((((c0_20 ? 1 : 0) << 8 | (c2_20 ? 1 : 0) << 0xa | (c3_20 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb):1.b & 1) != 0)
0043bef1        unimplemented  {fld st0, dword [ebp+0x6c]}
0043bef4        long double temp32_1 = fconvert.t(-0.163333341f)
0043bef4        unimplemented  {fcomp st0, dword [0x4975c4]} f- temp32_1
0043bef4        bool c0_21 = unimplemented  {fcomp st0, dword [0x4975c4]} f< temp32_1
0043bef4        bool c2_21 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4975c4]}, temp32_1)
0043bef4        bool c3_21 = unimplemented  {fcomp st0, dword [0x4975c4]} f== temp32_1
0043bef4        unimplemented  {fcomp st0, dword [0x4975c4]}
0043beff        if ((((c0_21 ? 1 : 0) << 8 | (c2_21 ? 1 : 0) << 0xa | (c3_21 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb):1.b & 0x41) == 0 && is_sub_loc_empty(cell) == 0 && cell->tile_id != 0x16)
0043bf15        set_matrix_rotation_identity(&player->body.transform)
0043bf1a        player->trampoline_bounce_active = 0
0043bf21        unimplemented  {fld st0, dword [ebp+0x414]}
0043bf27        long double temp44_1 = fconvert.t(-0.0299999993f)
0043bf27        unimplemented  {fcomp st0, dword [0x4975c0]} f- temp44_1
0043bf27        bool c0_22 = unimplemented  {fcomp st0, dword [0x4975c0]} f< temp44_1
0043bf27        bool c2_22 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4975c0]}, temp44_1)
0043bf27        bool c3_22 = unimplemented  {fcomp st0, dword [0x4975c0]} f== temp44_1
0043bf27        unimplemented  {fcomp st0, dword [0x4975c0]}
0043bf32        if ((((c0_22 ? 1 : 0) << 8 | (c2_22 ? 1 : 0) << 0xa | (c3_22 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb):1.b & 1) != 0)
0043bf34        unimplemented  {fld st0, dword [ebp+0x414]}
0043bf3a        unimplemented  {fsub st0, dword [0x497548]}
0043bf40        struct TransformMatrix* var_54_14 = &player->body.transform
0043bf47        float value = fconvert.s(unimplemented  {fstp dword [esp], st0})
0043bf47        unimplemented  {fstp dword [esp], st0}
0043bf4a        start_squidge_y(&player->squidge, value)
0043bf4f        unimplemented  {fld st0, dword [ebp+0x414]}
0043bf55        long double temp49_1 = fconvert.t(0f)
0043bf55        unimplemented  {fcomp st0, dword [0x497234]} f- temp49_1
0043bf55        bool c0_23 = unimplemented  {fcomp st0, dword [0x497234]} f< temp49_1
0043bf55        bool c2_23 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp49_1)
0043bf55        bool c3_23 = unimplemented  {fcomp st0, dword [0x497234]} f== temp49_1
0043bf55        unimplemented  {fcomp st0, dword [0x497234]}
0043bf55        top_82 = top_82
0043bf60        if ((((c0_23 ? 1 : 0) << 8 | (c2_23 ? 1 : 0) << 0xa | (c3_23 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb):1.b & 0x41) != 0)
0043bf62        player->body.transform.position.y = 0.49000001f
0043bf65        player->velocity.y = 0f
0043bf6f        player->attachment_exit_pending = 0
0043bf76        int16_t eax_90
0043bf76        eax_90.b = cell->tile_id
0043bf7f        if (eax_90.b == 0 || eax_90.b == 0x23)
0043bf85        unimplemented  {fld st0, dword [ebp+0x6c]}
0043bf88        long double temp35_1 = fconvert.t(0.49000001f)
0043bf88        unimplemented  {fcomp st0, dword [0x4973e8]} f- temp35_1
0043bf88        bool c0_24 = unimplemented  {fcomp st0, dword [0x4973e8]} f< temp35_1
0043bf88        bool c2_24 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4973e8]}, temp35_1)
0043bf88        bool c3_24 = unimplemented  {fcomp st0, dword [0x4973e8]} f== temp35_1
0043bf88        unimplemented  {fcomp st0, dword [0x4973e8]}
0043bf93        if ((((c0_24 ? 1 : 0) << 8 | (c2_24 ? 1 : 0) << 0xa | (c3_24 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb):1.b & 1) != 0)
0043bf95        unimplemented  {fld st0, dword [ebp+0x414]}
0043bf9b        long double temp40_1 = fconvert.t(0f)
0043bf9b        unimplemented  {fcomp st0, dword [0x497234]} f- temp40_1
0043bf9b        bool c0_25 = unimplemented  {fcomp st0, dword [0x497234]} f< temp40_1
0043bf9b        bool c2_25 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp40_1)
0043bf9b        bool c3_25 = unimplemented  {fcomp st0, dword [0x497234]} f== temp40_1
0043bf9b        unimplemented  {fcomp st0, dword [0x497234]}
0043bfa6        if ((((c0_25 ? 1 : 0) << 8 | (c2_25 ? 1 : 0) << 0xa | (c3_25 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb):1.b & 0x41) != 0)
0043bfa8        unimplemented  {fld st0, dword [ebp+0x70]}
0043bfb0        int32_t var_40_3 = ftol(x87control_1, st0_1)
0043bfb4        int16_t eax_92
0043bfb4        eax_92.b = cell->open_edge_mask
0043bfb7        unimplemented  {fild st0, dword [esp+0x10]}
0043bfbd        unimplemented  {fsubr st0, dword [ebp+0x70]}
0043bfc0        int16_t top_93
0043bfc0        if ((eax_92.b & 2) != 0)
0043bfca        top_93 = top_82 - 2
0043bfca        unimplemented  {fld st0, dword [0x497250]}
0043bfc2        top_93 = top_82 - 2
0043bfc2        unimplemented  {fld st0, dword [0x497220]}
0043bfd2        float var_40_4 = 0f
0043bfda        if ((eax_92.b & 1) != 0)
0043bfdc        var_40_4 = 0.200000003f
0043bfe4        unimplemented  {fld st0, st1}
0043bfe6        unimplemented  {fcomp st0, st1} f- unimplemented  {fcomp st0, st1}
0043bfe6        bool c0_26 = unimplemented  {fcomp st0, st1} f< unimplemented  {fcomp st0, st1}
0043bfe6        bool c2_26 = is_unordered.t(unimplemented  {fcomp st0, st1}, unimplemented  {fcomp st0, st1})
0043bfe6        bool c3_26 = unimplemented  {fcomp st0, st1} f== unimplemented  {fcomp st0, st1}
0043bfe6        unimplemented  {fcomp st0, st1}
0043bfed        unimplemented  {fstp st0, st0}
0043bfed        unimplemented  {fstp st0, st0}
0043bfef        if ((((c0_26 ? 1 : 0) << 8 | (c2_26 ? 1 : 0) << 0xa | (c3_26 ? 1 : 0) << 0xe | (top_93 & 7) << 0xb):1.b & 1) == 0)
0043c00f        unimplemented  {fstp st0, st0}
0043c00f        unimplemented  {fstp st0, st0}
0043c00f        top_82 = top_93 + 2
0043bff1        long double temp56_1 = fconvert.t(var_40_4)
0043bff1        unimplemented  {fcomp st0, dword [esp+0x10]} f- temp56_1
0043bff1        bool c0_27 = unimplemented  {fcomp st0, dword [esp+0x10]} f< temp56_1
0043bff1        bool c2_27 = is_unordered.t(unimplemented  {fcomp st0, dword [esp+0x10]}, temp56_1)
0043bff1        bool c3_27 = unimplemented  {fcomp st0, dword [esp+0x10]} f== temp56_1
0043bff1        unimplemented  {fcomp st0, dword [esp+0x10]}
0043bff1        top_82 = top_93 + 2
0043bff5        eax_92 = (c0_27 ? 1 : 0) << 8 | (c2_27 ? 1 : 0) << 0xa | (c3_27 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb
0043bffa        if ((eax_92:1.b & 0x41) == 0)
0043bffc        eax_92.b = player->attachment_exit_pending
0043c004        if (eax_92.b == 0)
0043c008        begin_post_follow_carryover(player)
0043c011        struct SubgameRuntime* game_11 = player->game
0043c01b        if (game_11->level_mode == 3)
0043c01e        get_track_grid_cell_at_world_position(game_11, ebx_1)
0043c038        if (((player->game->runtime_flags).w:1.b & 4) == 0 || (data_4b2f40 & 2) != 0)
0043c03a        unimplemented  {fld st0, dword [ebp+0x6c]}
0043c03d        long double temp48_1 = fconvert.t(0.49000001f)
0043c03d        unimplemented  {fcomp st0, dword [0x4973e8]} f- temp48_1
0043c03d        bool c0_28 = unimplemented  {fcomp st0, dword [0x4973e8]} f< temp48_1
0043c03d        bool c2_28 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4973e8]}, temp48_1)
0043c03d        bool c3_28 = unimplemented  {fcomp st0, dword [0x4973e8]} f== temp48_1
0043c03d        unimplemented  {fcomp st0, dword [0x4973e8]}
0043c048        if ((((c0_28 ? 1 : 0) << 8 | (c2_28 ? 1 : 0) << 0xa | (c3_28 ? 1 : 0) << 0xe | (top_82 & 7) << 0xb):1.b & 1) != 0)
0043c057        start_squidge_y(&player->squidge, player->velocity.y)
0043c05c        player->trampoline_bounce_active = 0
0043c063        player->velocity.y = 0f
0043c06d        player->attachment_exit_pending = 0
0043c074        player->body.transform.position.y = 0.49000001f
0043c077        unimplemented  {fld st0, dword [ebp+0x6c]}
0043c07a        long double temp51_1 = fconvert.t(-7f)
0043c07a        unimplemented  {fcomp st0, dword [0x4975bc]} f- temp51_1
0043c07a        bool c0_29 = unimplemented  {fcomp st0, dword [0x4975bc]} f< temp51_1
0043c07a        bool c2_29 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4975bc]}, temp51_1)
0043c07a        bool c3_29 = unimplemented  {fcomp st0, dword [0x4975bc]} f== temp51_1
0043c07a        unimplemented  {fcomp st0, dword [0x4975bc]}
0043c07a        top_66 = top_82
0043c080        int16_t eax_94 = (c0_29 ? 1 : 0) << 8 | (c2_29 ? 1 : 0) << 0xa | (c3_29 ? 1 : 0) << 0xe | (top_66 & 7) << 0xb
0043c085        if ((eax_94:1.b & 1) != 0)
0043c087        eax_94.b = player->resurrect_active.b
0043c08f        if (eax_94.b == 0)
0043c093        initialize_subgoldy_death(player)
0043bc98        unimplemented  {fld st0, dword [eax+0x38]}
0043bc9b        unimplemented  {fld st0, st0}
0043bc9d        unimplemented  {fmul st0, st1}
0043bc9f        unimplemented  {fmul st0, dword [0x4973bc]}
0043bca5        unimplemented  {fadd st0, st0}
0043bca7        unimplemented  {fadd dword [ebp+0x418]}
0043bcad        player->velocity.z = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043bcad        unimplemented  {fstp dword [ebp+0x418], st0}
0043bcb3        player->attachment_exit_pending = 0
0043bcba        unimplemented  {fstp st0, st0}
0043bcba        unimplemented  {fstp st0, st0}
0043c098        unimplemented  {fld st0, dword [ebp+0x1dc]}
0043c09e        long double temp29_1 = fconvert.t(0f)
0043c09e        unimplemented  {fcomp st0, dword [0x497234]} f- temp29_1
0043c09e        bool c0_30 = unimplemented  {fcomp st0, dword [0x497234]} f< temp29_1
0043c09e        bool c2_30 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp29_1)
0043c09e        bool c3_30 = unimplemented  {fcomp st0, dword [0x497234]} f== temp29_1
0043c09e        unimplemented  {fcomp st0, dword [0x497234]}
0043c0a4        int16_t eax_95 = (c0_30 ? 1 : 0) << 8 | (c2_30 ? 1 : 0) << 0xa | (c3_30 ? 1 : 0) << 0xe | (top_66 & 7) << 0xb
0043c0a9        if ((eax_95:1.b & 0x40) == 0)
0043c0ab        unimplemented  {fld st0, dword [ebp+0x1e0]}
0043c0b1        unimplemented  {fadd dword [ebp+0x1dc]}
0043c0b7        player->surface_reaction_timer = fconvert.s(unimplemented  {fst dword [ebp+0x1dc], st0})
0043c0bd        long double temp31_1 = fconvert.t(1f)
0043c0bd        unimplemented  {fcomp st0, dword [0x497220]} f- temp31_1
0043c0bd        bool c0_31 = unimplemented  {fcomp st0, dword [0x497220]} f< temp31_1
0043c0bd        bool c2_31 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp31_1)
0043c0bd        bool c3_31 = unimplemented  {fcomp st0, dword [0x497220]} f== temp31_1
0043c0bd        unimplemented  {fcomp st0, dword [0x497220]}
0043c0c3        eax_95 = (c0_31 ? 1 : 0) << 8 | (c2_31 ? 1 : 0) << 0xa | (c3_31 ? 1 : 0) << 0xe | (top_66 & 7) << 0xb
0043c0c8        if ((eax_95:1.b & 0x41) == 0)
0043c0ca        player->surface_reaction_timer = 0f
0043c0d4        eax_95.b = player->attachment_exit_pending
0043c0dc        if (eax_95.b != 0)
0043c35c        unimplemented  {fld st0, dword [eax+0x38]}
0043c35f        unimplemented  {fld st0, st0}
0043c361        unimplemented  {fmul st0, st1}
0043c363        unimplemented  {fmul st0, dword [0x4975cc]}
0043c369        unimplemented  {fadd dword [ebp+0x414]}
0043c36f        player->velocity.y = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043c36f        unimplemented  {fstp dword [ebp+0x414], st0}
0043c37b        unimplemented  {fstp st0, st0}
0043c37b        unimplemented  {fstp st0, st0}
0043c37b        top_13 = top_66
0043c388        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0x16)
0043c38a        unimplemented  {fld st0, dword [esi+0x14]}
0043c38d        unimplemented  {fadd dword [0x4973e8]}
0043c393        long double temp36_1 = fconvert.t(player->body.transform.position.y)
0043c393        unimplemented  {fcomp st0, dword [ebp+0x6c]} f- temp36_1
0043c393        bool c0_38 = unimplemented  {fcomp st0, dword [ebp+0x6c]} f< temp36_1
0043c393        bool c2_38 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x6c]}, temp36_1)
0043c393        bool c3_38 = unimplemented  {fcomp st0, dword [ebp+0x6c]} f== temp36_1
0043c393        unimplemented  {fcomp st0, dword [ebp+0x6c]}
0043c39b        if ((((c0_38 ? 1 : 0) << 8 | (c2_38 ? 1 : 0) << 0xa | (c3_38 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 0x41) == 0)
0043c39d        unimplemented  {fld st0, dword [esi+0x14]}
0043c3a0        unimplemented  {fsub st0, dword [0x4973e8]}
0043c3a6        long double temp41_1 = fconvert.t(player->body.transform.position.y)
0043c3a6        unimplemented  {fcomp st0, dword [ebp+0x6c]} f- temp41_1
0043c3a6        bool c0_39 = unimplemented  {fcomp st0, dword [ebp+0x6c]} f< temp41_1
0043c3a6        bool c2_39 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x6c]}, temp41_1)
0043c3a6        bool c3_39 = unimplemented  {fcomp st0, dword [ebp+0x6c]} f== temp41_1
0043c3a6        unimplemented  {fcomp st0, dword [ebp+0x6c]}
0043c3ae        if ((((c0_39 ? 1 : 0) << 8 | (c2_39 ? 1 : 0) << 0xa | (c3_39 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 1) != 0)
0043c3bd        start_squidge_y(&player->squidge, player->velocity.y)
0043c3cf        unimplemented  {fld st0, dword [edx+0x38]}
0043c3d2        unimplemented  {fmul st0, dword [0x4973d8]}
0043c3d8        player->velocity.y = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043c3d8        unimplemented  {fstp dword [ebp+0x414], st0}
0043c3de        unimplemented  {fld st0, dword [esi+0x14]}
0043c3e1        unimplemented  {fadd dword [0x4973e8]}
0043c3e7        player->body.transform.position.y = fconvert.s(unimplemented  {fstp dword [ebp+0x6c], st0})
0043c3e7        unimplemented  {fstp dword [ebp+0x6c], st0}
0043c3ea        player->attachment_exit_pending = 0
0043c3f1        player->trampoline_bounce_active = 1
0043c3f8        play_sound_effect(0x29)
0043c0e9        st0_1 = sample_track_floor_height_at_position(player->game, ebx_1)
0043c0e9        unimplemented  {call 0x43d4d0}
0043c0ee        unimplemented  {fadd dword [0x4973e8]}
0043c0f4        long double temp33_1 = fconvert.t(player->body.transform.position.y)
0043c0f4        unimplemented  {fcom st0, dword [ebp+0x6c]} f- temp33_1
0043c0f4        bool c0_32 = unimplemented  {fcom st0, dword [ebp+0x6c]} f< temp33_1
0043c0f4        bool c2_32 = is_unordered.t(unimplemented  {fcom st0, dword [ebp+0x6c]}, temp33_1)
0043c0f4        bool c3_32 = unimplemented  {fcom st0, dword [ebp+0x6c]} f== temp33_1
0043c0fc        int16_t top_105
0043c0fc        if ((((c0_32 ? 1 : 0) << 8 | (c2_32 ? 1 : 0) << 0xa | (c3_32 ? 1 : 0) << 0xe | ((top_66 - 1) & 7) << 0xb):1.b & 0x41) != 0)
0043c301        unimplemented  {fstp st0, st0}
0043c301        unimplemented  {fstp st0, st0}
0043c303        unimplemented  {fld st0, dword [edx+0x38]}
0043c306        unimplemented  {fld st0, st0}
0043c308        unimplemented  {fmul st0, st1}
0043c30a        unimplemented  {fmul st0, dword [0x4975cc]}
0043c310        unimplemented  {fadd dword [ebp+0x414]}
0043c316        player->velocity.y = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043c316        unimplemented  {fstp dword [ebp+0x414], st0}
0043c31c        unimplemented  {fstp st0, st0}
0043c31c        unimplemented  {fstp st0, st0}
0043c31c        top_105 = top_66
0043c102        unimplemented  {fld st0, dword [ebp+0x414]}
0043c108        long double temp37_1 = fconvert.t(0f)
0043c108        unimplemented  {fcomp st0, dword [0x497234]} f- temp37_1
0043c108        bool c0_33 = unimplemented  {fcomp st0, dword [0x497234]} f< temp37_1
0043c108        bool c2_33 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp37_1)
0043c108        bool c3_33 = unimplemented  {fcomp st0, dword [0x497234]} f== temp37_1
0043c108        unimplemented  {fcomp st0, dword [0x497234]}
0043c113        if ((((c0_33 ? 1 : 0) << 8 | (c2_33 ? 1 : 0) << 0xa | (c3_33 ? 1 : 0) << 0xe | ((top_66 - 1) & 7) << 0xb):1.b & 0x41) == 0)
0043c11a        unimplemented  {fstp st0, st0}
0043c11a        unimplemented  {fstp st0, st0}
0043c11a        top_105 = top_66
0043c115        player->body.transform.position.y = fconvert.s(unimplemented  {fstp dword [ebp+0x6c], st0})
0043c115        unimplemented  {fstp dword [ebp+0x6c], st0}
0043c115        top_105 = top_66
0043c12c        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 8)
0043c2ea        label_43c2ea:
0043c2ea        unimplemented  {fld st0, dword [ecx+0x38]}
0043c2ed        unimplemented  {fmul st0, dword [0x4973d8]}
0043c2f3        player->velocity.y = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043c2f3        unimplemented  {fstp dword [ebp+0x414], st0}
0043c142        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 9)
0043c142        goto label_43c2ea
0043c158        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0xa)
0043c158        goto label_43c2ea
0043c16e        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0xb)
0043c16e        goto label_43c2ea
0043c184        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0xc)
0043c184        goto label_43c2ea
0043c19a        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0xd)
0043c19a        goto label_43c2ea
0043c1b0        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 2)
0043c271        label_43c271:
0043c271        unimplemented  {fld st0, dword [ebp+0x1dc]}
0043c277        long double temp58_1 = fconvert.t(0f)
0043c277        unimplemented  {fcomp st0, dword [0x497234]} f- temp58_1
0043c277        bool c0_34 = unimplemented  {fcomp st0, dword [0x497234]} f< temp58_1
0043c277        bool c2_34 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp58_1)
0043c277        bool c3_34 = unimplemented  {fcomp st0, dword [0x497234]} f== temp58_1
0043c277        unimplemented  {fcomp st0, dword [0x497234]}
0043c282        if ((((c0_34 ? 1 : 0) << 8 | (c2_34 ? 1 : 0) << 0xa | (c3_34 ? 1 : 0) << 0xe | (top_105 & 7) << 0xb):1.b & 0x40) != 0)
0043c28a        player->surface_reaction_timer = player->surface_reaction_step
0043c296        unimplemented  {fld st0, dword [eax+0x38]}
0043c299        unimplemented  {fmul st0, dword [0x497270]}
0043c29f        player->velocity.y = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043c29f        unimplemented  {fstp dword [ebp+0x414], st0}
0043c2a5        int16_t eax_105
0043c2a5        eax_105.b = player->control_override_active
0043c2ad        if (eax_105.b == 0)
0043c2af        unimplemented  {fld st0, dword [ebx]}
0043c2b1        long double temp62_1 = fconvert.t(0f)
0043c2b1        unimplemented  {fcomp st0, dword [0x497234]} f- temp62_1
0043c2b1        bool c0_35 = unimplemented  {fcomp st0, dword [0x497234]} f< temp62_1
0043c2b1        bool c2_35 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp62_1)
0043c2b1        bool c3_35 = unimplemented  {fcomp st0, dword [0x497234]} f== temp62_1
0043c2b1        unimplemented  {fcomp st0, dword [0x497234]}
0043c2c6        int32_t animation_id_1
0043c2c6        if ((((c0_35 ? 1 : 0) << 8 | (c2_35 ? 1 : 0) << 0xa | (c3_35 ? 1 : 0) << 0xe | (top_105 & 7) << 0xb):1.b & 0x41) != 0)
0043c2cc        animation_id_1 = 3
0043c2c8        animation_id_1 = 4
0043c2d0        dispatch_cutscene_animation(&player->presentation, animation_id_1, 1, 0xffffffff)
0043c2dd        dispatch_cutscene_animation(&player->presentation, 1, 0, 0xffffffff)
0043c1c6        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 3)
0043c1c6        goto label_43c271
0043c1dc        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 4)
0043c1dc        goto label_43c271
0043c1f2        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 5)
0043c1f2        goto label_43c271
0043c204        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 6)
0043c204        goto label_43c271
0043c216        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 7)
0043c216        goto label_43c271
0043c229        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id != 0 && get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id != 0x23 && get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id != 0x16)
0043c25b        player->trampoline_bounce_active = 0
0043c262        player->velocity.y = 0f
0043c31e        unimplemented  {fld st0, dword [ebp+0x6c]}
0043c321        long double temp42_1 = fconvert.t(0f)
0043c321        unimplemented  {fcomp st0, dword [0x497234]} f- temp42_1
0043c321        bool c0_36 = unimplemented  {fcomp st0, dword [0x497234]} f< temp42_1
0043c321        bool c2_36 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp42_1)
0043c321        bool c3_36 = unimplemented  {fcomp st0, dword [0x497234]} f== temp42_1
0043c321        unimplemented  {fcomp st0, dword [0x497234]}
0043c321        top_13 = top_105
0043c32c        if ((((c0_36 ? 1 : 0) << 8 | (c2_36 ? 1 : 0) << 0xa | (c3_36 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 1) != 0)
0043c332        unimplemented  {fld st0, dword [ebp+0x414]}
0043c338        long double temp45_1 = fconvert.t(0f)
0043c338        unimplemented  {fcomp st0, dword [0x497234]} f- temp45_1
0043c338        bool c0_37 = unimplemented  {fcomp st0, dword [0x497234]} f< temp45_1
0043c338        bool c2_37 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp45_1)
0043c338        bool c3_37 = unimplemented  {fcomp st0, dword [0x497234]} f== temp45_1
0043c338        unimplemented  {fcomp st0, dword [0x497234]}
0043c343        if ((((c0_37 ? 1 : 0) << 8 | (c2_37 ? 1 : 0) << 0xa | (c3_37 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 0x41) != 0)
0043c34b        begin_post_follow_carryover(player)
0043b9a6        switch (update_track_attachment_follow_state(&player->follow_state, player->velocity.z, ebx_1, &player->velocity))
0043b9cc        case 0
0043b9cc        if (player->follow_state.template_record->kind != PATH_TEMPLATE_KIND_DETOUR)
0043b9d4        unimplemented  {fld st0, dword [ecx+0x38]}
0043b9d7        unimplemented  {fld st0, st0}
0043b9d9        unimplemented  {fmul st0, st1}
0043b9db        unimplemented  {fmul st0, dword [0x4973bc]}
0043b9e1        unimplemented  {fadd st0, st0}
0043b9e3        unimplemented  {fadd dword [ebp+0x418]}
0043b9e9        player->velocity.z = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043b9e9        unimplemented  {fstp dword [ebp+0x418], st0}
0043b9ef        unimplemented  {fstp st0, st0}
0043b9ef        unimplemented  {fstp st0, st0}
0043b9cc        goto label_43b9f1
0043b9b0        case 1, 3
0043b9b0        if (player->follow_state.active == 1)
0043b9b8        begin_post_follow_carryover(player)
0043b9f1        case 2
0043b9f1        label_43b9f1:
0043b9f1        unimplemented  {fld st0, dword [ebx]}
0043b9f3        unimplemented  {fadd dword [esi]}
0043b9f5        ebx_1->x = fconvert.s(unimplemented  {fstp dword [ebx], st0})
0043b9f5        unimplemented  {fstp dword [ebx], st0}
0043b9f7        unimplemented  {fld st0, dword [esi+0x4]}
0043b9fa        unimplemented  {fadd dword [ebx+0x4]}
0043b9fd        ebx_1->y = fconvert.s(unimplemented  {fstp dword [ebx+0x4], st0})
0043b9fd        unimplemented  {fstp dword [ebx+0x4], st0}
0043ba00        unimplemented  {fld st0, dword [esi+0x8]}
0043ba03        unimplemented  {fadd dword [ebx+0x8]}
0043ba06        ebx_1->z = fconvert.s(unimplemented  {fstp dword [ebx+0x8], st0})
0043ba06        unimplemented  {fstp dword [ebx+0x8], st0}
0043ba0f        unimplemented  {fld st0, dword [edx+0x38]}
0043ba12        unimplemented  {fmul st0, dword [0x4975d0]}
0043ba18        unimplemented  {fsubr st0, dword [0x497220]}
0043ba1e        unimplemented  {fmul st0, dword [ebp+0x418]}
0043ba24        player->velocity.z = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043ba24        unimplemented  {fstp dword [ebp+0x418], st0}
0043ba30        unimplemented  {fld st0, dword [eax+0x38]}
0043ba33        unimplemented  {fmul st0, dword [0x4975d0]}
0043ba39        unimplemented  {fsubr st0, dword [0x497220]}
0043ba3f        unimplemented  {fmul st0, dword [ebp+0x414]}
0043ba45        player->velocity.y = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043ba45        unimplemented  {fstp dword [ebp+0x414], st0}
0043ba51        unimplemented  {fld st0, dword [ecx+0x38]}
0043ba54        unimplemented  {fmul st0, dword [0x497258]}
0043ba5a        unimplemented  {fsubr st0, dword [0x497220]}
0043ba60        unimplemented  {fmul st0, dword [esi]}
0043ba62        player->velocity.x = fconvert.s(unimplemented  {fstp dword [esi], st0})
0043ba62        unimplemented  {fstp dword [esi], st0}
0043ba6a        unimplemented  {fld st0, dword [edx+0x38]}
0043ba6d        unimplemented  {fld st0, st0}
0043ba6f        unimplemented  {fmul st0, st1}
0043ba71        unimplemented  {fmul st0, dword [0x4975cc]}
0043ba77        unimplemented  {fadd dword [ebp+0x414]}
0043ba7d        player->velocity.y = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043ba7d        unimplemented  {fstp dword [ebp+0x414], st0}
0043ba83        unimplemented  {fstp st0, st0}
0043ba83        unimplemented  {fstp st0, st0}
0043ba85        unimplemented  {fld st0, dword [ebx]}
0043ba87        long double temp18_1 = fconvert.t(-4f)
0043ba87        unimplemented  {fcomp st0, dword [0x497420]} f- temp18_1
0043ba87        bool c0_14 = unimplemented  {fcomp st0, dword [0x497420]} f< temp18_1
0043ba87        bool c2_14 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497420]}, temp18_1)
0043ba87        bool c3_14 = unimplemented  {fcomp st0, dword [0x497420]} f== temp18_1
0043ba87        unimplemented  {fcomp st0, dword [0x497420]}
0043ba92        int16_t top_38
0043ba92        if ((((c0_14 ? 1 : 0) << 8 | (c2_14 ? 1 : 0) << 0xa | (c3_14 ? 1 : 0) << 0xe | (top_38 & 7) << 0xb):1.b & 1) != 0)
0043ba94        ebx_1->x = 0xc0800000
0043ba9a        player->velocity.x = 0
0043baa0        unimplemented  {fld st0, dword [ebx]}
0043baa2        long double temp19_1 = fconvert.t(4f)
0043baa2        unimplemented  {fcomp st0, dword [0x497210]} f- temp19_1
0043baa2        bool c0_15 = unimplemented  {fcomp st0, dword [0x497210]} f< temp19_1
0043baa2        bool c2_15 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497210]}, temp19_1)
0043baa2        bool c3_15 = unimplemented  {fcomp st0, dword [0x497210]} f== temp19_1
0043baa2        unimplemented  {fcomp st0, dword [0x497210]}
0043baa2        top_13 = top_38
0043baad        if ((((c0_15 ? 1 : 0) << 8 | (c2_15 ? 1 : 0) << 0xa | (c3_15 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 0x41) == 0)
0043bab3        ebx_1->x = 0x40800000
0043bab9        player->velocity.x = 0
0043c403        update_warning(&player->warning)
0043c41e        struct Vec3 position
0043c41e        if (player->boost_one_tick != 0 || player->follow_state.active != 0)
0043c510        player->barrier_hold_progress = 0f
0043c424        unimplemented  {fld st0, dword [ebx+0x8]}
0043c427        unimplemented  {fadd dword [0x4973e8]}
0043c42d        float x = ebx_1->x
0043c42f        float y_1 = ebx_1->y
0043c432        float x_2 = x
0043c438        float y_2 = y_1
0043c43e        float var_34_1 = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
0043c43e        unimplemented  {fstp dword [esp+0x1c], st0}
0043c446        position.x = x
0043c44e        position.z = var_34_1
0043c459        position.y = y_1
0043c45d        struct TrackRowCell* eax_112
0043c45d        int16_t x87control_2
0043c45d        eax_112, x87control_2 = get_track_grid_cell_at_world_position(player->game, &position)
0043c466        if (eax_112->tile_id != 0xe)
0043c510        player->barrier_hold_progress = 0f
0043c46c        unimplemented  {fld st0, dword [ebp+0x6c]}
0043c46f        long double temp22_1 = fconvert.t(6.5f)
0043c46f        unimplemented  {fcomp st0, dword [0x4975b8]} f- temp22_1
0043c46f        bool c0_40 = unimplemented  {fcomp st0, dword [0x4975b8]} f< temp22_1
0043c46f        bool c2_40 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4975b8]}, temp22_1)
0043c46f        bool c3_40 = unimplemented  {fcomp st0, dword [0x4975b8]} f== temp22_1
0043c46f        unimplemented  {fcomp st0, dword [0x4975b8]}
0043c47a        if ((((c0_40 ? 1 : 0) << 8 | (c2_40 ? 1 : 0) << 0xa | (c3_40 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 1) == 0)
0043c510        player->barrier_hold_progress = 0f
0043c482        player->velocity.z = 0f
0043c488        unimplemented  {fld st0, dword [ebp+0x70]}
0043c48b        unimplemented  {fadd dword [0x4973e8]}
0043c496        int32_t var_40_5 = ftol(x87control_2, st0_1)
0043c49a        unimplemented  {fild st0, dword [esp+0x10]}
0043c49e        unimplemented  {fsub st0, dword [0x497228]}
0043c4a4        player->body.transform.position.z = fconvert.s(unimplemented  {fstp dword [ebp+0x70], st0})
0043c4a4        unimplemented  {fstp dword [ebp+0x70], st0}
0043c4a7        unimplemented  {fld st0, dword [ebp+0x4350]}
0043c4ad        long double temp26_1 = fconvert.t(0f)
0043c4ad        unimplemented  {fcomp st0, dword [0x497234]} f- temp26_1
0043c4ad        bool c0_41 = unimplemented  {fcomp st0, dword [0x497234]} f< temp26_1
0043c4ad        bool c2_41 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp26_1)
0043c4ad        bool c3_41 = unimplemented  {fcomp st0, dword [0x497234]} f== temp26_1
0043c4ad        unimplemented  {fcomp st0, dword [0x497234]}
0043c4b8        if ((((c0_41 ? 1 : 0) << 8 | (c2_41 ? 1 : 0) << 0xa | (c3_41 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 0x40) != 0)
0043c4c1        play_sound_effect(0x2f)
0043c4d1        start_squidge_z(&player->squidge, -0.330000013f)
0043c4d6        unimplemented  {fld st0, dword [ebp+0x32c]}
0043c4dc        unimplemented  {fadd dword [ebp+0x328]}
0043c4e2        player->barrier_hold_progress = fconvert.s(unimplemented  {fst dword [ebp+0x328], st0})
0043c4e8        long double temp28_1 = fconvert.t(1f)
0043c4e8        unimplemented  {fcomp st0, dword [0x497220]} f- temp28_1
0043c4e8        bool c0_42 = unimplemented  {fcomp st0, dword [0x497220]} f< temp28_1
0043c4e8        bool c2_42 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp28_1)
0043c4e8        bool c3_42 = unimplemented  {fcomp st0, dword [0x497220]} f== temp28_1
0043c4e8        unimplemented  {fcomp st0, dword [0x497220]}
0043c4ee        int16_t eax_117 = (c0_42 ? 1 : 0) << 8 | (c2_42 ? 1 : 0) << 0xa | (c3_42 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb
0043c4f3        if ((eax_117:1.b & 0x41) == 0)
0043c4f5        player->barrier_hold_progress = 0f
0043c4fb        eax_117.b = player->attachment_exit_pending
0043c503        if (eax_117.b == 0)
0043c507        begin_post_follow_carryover(player)
0043c51c        if (player->lane_lean_state == 0)
0043c532        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 2)
0043c5d0        label_43c5d0:
0043c5d0        int16_t eax_119
0043c5d0        eax_119.b = player->attachment_exit_pending
0043c5d8        if (eax_119.b == 0)
0043c5de        unimplemented  {fld st0, dword [ebp+0x6c]}
0043c5e1        long double temp27_1 = fconvert.t(0.980000019f)
0043c5e1        unimplemented  {fcomp st0, dword [0x49756c]} f- temp27_1
0043c5e1        bool c0_43 = unimplemented  {fcomp st0, dword [0x49756c]} f< temp27_1
0043c5e1        bool c2_43 = is_unordered.t(unimplemented  {fcomp st0, dword [0x49756c]}, temp27_1)
0043c5e1        bool c3_43 = unimplemented  {fcomp st0, dword [0x49756c]} f== temp27_1
0043c5e1        unimplemented  {fcomp st0, dword [0x49756c]}
0043c5ec        if ((((c0_43 ? 1 : 0) << 8 | (c2_43 ? 1 : 0) << 0xa | (c3_43 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 0x41) != 0)
0043c5f9        unimplemented  {fld st0, dword [eax+0x38]}
0043c5fc        unimplemented  {fmul st0, dword [0x4975b4]}
0043c602        player->lane_lean_progress_step = fconvert.s(unimplemented  {fstp dword [ebp+0x35c], st0})
0043c602        unimplemented  {fstp dword [ebp+0x35c], st0}
0043c617        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 2)
0043c665        player->lane_lean_state = 1
0043c66f        player->lane_lean_amplitude = 1f
0043c629        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 5)
0043c665        player->lane_lean_state = 1
0043c66f        player->lane_lean_amplitude = 1f
0043c63b        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 8)
0043c665        player->lane_lean_state = 1
0043c66f        player->lane_lean_amplitude = 1f
0043c64d        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0xb)
0043c665        player->lane_lean_state = 1
0043c66f        player->lane_lean_amplitude = 1f
0043c64f        player->lane_lean_state = 2
0043c659        player->lane_lean_amplitude = -1f
0043c548        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 4)
0043c548        goto label_43c5d0
0043c55e        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 5)
0043c55e        goto label_43c5d0
0043c570        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 7)
0043c570        goto label_43c5d0
0043c582        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0xa)
0043c582        goto label_43c5d0
0043c594        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 8)
0043c594        goto label_43c5d0
0043c5a6        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0xa)
0043c5a6        goto label_43c5d0
0043c5b8        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0xb)
0043c5b8        goto label_43c5d0
0043c5ca        if (get_track_grid_cell_at_world_position(player->game, ebx_1)->tile_id == 0xd)
0043c5ca        goto label_43c5d0
0043c679        unimplemented  {fld st0, dword [ebp+0x1d4]}
0043c67f        long double temp21_1 = fconvert.t(0f)
0043c67f        unimplemented  {fcomp st0, dword [0x497234]} f- temp21_1
0043c67f        bool c0_44 = unimplemented  {fcomp st0, dword [0x497234]} f< temp21_1
0043c67f        bool c2_44 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp21_1)
0043c67f        bool c3_44 = unimplemented  {fcomp st0, dword [0x497234]} f== temp21_1
0043c67f        unimplemented  {fcomp st0, dword [0x497234]}
0043c68a        if ((((c0_44 ? 1 : 0) << 8 | (c2_44 ? 1 : 0) << 0xa | (c3_44 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 0x40) == 0)
0043c68c        unimplemented  {fld st0, dword [ebp+0x1d8]}
0043c692        unimplemented  {fadd dword [ebp+0x1d4]}
0043c698        player->damage_retrigger_timer = fconvert.s(unimplemented  {fst dword [ebp+0x1d4], st0})
0043c69e        long double temp25_1 = fconvert.t(1f)
0043c69e        unimplemented  {fcomp st0, dword [0x497220]} f- temp25_1
0043c69e        bool c0_45 = unimplemented  {fcomp st0, dword [0x497220]} f< temp25_1
0043c69e        bool c2_45 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp25_1)
0043c69e        bool c3_45 = unimplemented  {fcomp st0, dword [0x497220]} f== temp25_1
0043c69e        unimplemented  {fcomp st0, dword [0x497220]}
0043c6a9        if ((((c0_45 ? 1 : 0) << 8 | (c2_45 ? 1 : 0) << 0xa | (c3_45 ? 1 : 0) << 0xe | (top_13 & 7) << 0xb):1.b & 0x41) == 0)
0043c6ab        player->damage_retrigger_timer = 0f
0043c6b1        struct SubgameRuntime* game_12 = player->game
0043c6b7        unimplemented  {fild st0, dword [ecx+0x58]}
0043c6ba        float var_40_6 = fconvert.s(unimplemented  {fstp dword [esp+0x10], st0})
0043c6ba        unimplemented  {fstp dword [esp+0x10], st0}
0043c6be        unimplemented  {fld st0, dword [ebp+0x70]}
0043c6c1        long double temp24_1 = fconvert.t(var_40_6)
0043c6c1        unimplemented  {fcomp st0, dword [esp+0x10]} f- temp24_1
0043c6c1        bool c0_46 = unimplemented  {fcomp st0, dword [esp+0x10]} f< temp24_1
0043c6c1        bool c2_46 = is_unordered.t(unimplemented  {fcomp st0, dword [esp+0x10]}, temp24_1)
0043c6c1        bool c3_46 = unimplemented  {fcomp st0, dword [esp+0x10]} f== temp24_1
0043c6c1        unimplemented  {fcomp st0, dword [esp+0x10]}
0043c6c1        int16_t top_142 = top_13
0043c6c5        int16_t eax_121 = (c0_46 ? 1 : 0) << 8 | (c2_46 ? 1 : 0) << 0xa | (c3_46 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb
0043c6ca        if ((eax_121:1.b & 1) != 0)
0043ca46        label_43ca46:
0043ca46        eax_121.b = player->boost_one_tick
0043ca4e        if (eax_121.b == 0)
0043ca50        eax_121.b = player->control_override_active
0043ca58        if (eax_121.b == 0)
0043ca5a        unimplemented  {fld st0, dword [ecx+0x38]}
0043ca5d        unimplemented  {fmul st0, dword [0x4975b0]}
0043ca63        unimplemented  {fld st0, dword [ebp+0x418]}
0043ca69        unimplemented  {fcomp st0, st1} f- unimplemented  {fcomp st0, st1}
0043ca69        bool c0_56 = unimplemented  {fcomp st0, st1} f< unimplemented  {fcomp st0, st1}
0043ca69        bool c2_56 = is_unordered.t(unimplemented  {fcomp st0, st1}, unimplemented  {fcomp st0, st1})
0043ca69        bool c3_56 = unimplemented  {fcomp st0, st1} f== unimplemented  {fcomp st0, st1}
0043ca69        unimplemented  {fcomp st0, st1}
0043ca69        int16_t top_170 = top_142 - 1
0043ca70        if ((((c0_56 ? 1 : 0) << 8 | (c2_56 ? 1 : 0) << 0xa | (c3_56 ? 1 : 0) << 0xe | (top_170 & 7) << 0xb):1.b & 1) == 0)
0043ca72        unimplemented  {fstp st0, st0}
0043ca72        unimplemented  {fstp st0, st0}
0043ca74        unimplemented  {fld st0, dword [ecx+0x38]}
0043ca77        unimplemented  {fmul st0, dword [0x497228]}
0043ca7d        unimplemented  {fld st0, dword [ebp+0x418]}
0043ca83        unimplemented  {fcomp st0, st1} f- unimplemented  {fcomp st0, st1}
0043ca83        bool c0_57 = unimplemented  {fcomp st0, st1} f< unimplemented  {fcomp st0, st1}
0043ca83        bool c2_57 = is_unordered.t(unimplemented  {fcomp st0, st1}, unimplemented  {fcomp st0, st1})
0043ca83        bool c3_57 = unimplemented  {fcomp st0, st1} f== unimplemented  {fcomp st0, st1}
0043ca83        unimplemented  {fcomp st0, st1}
0043ca8a        if ((((c0_57 ? 1 : 0) << 8 | (c2_57 ? 1 : 0) << 0xa | (c3_57 ? 1 : 0) << 0xe | (top_170 & 7) << 0xb):1.b & 0x41) != 0)
0043ca8c        unimplemented  {fstp st0, st0}
0043ca8c        unimplemented  {fstp st0, st0}
0043ca8e        unimplemented  {fld st0, dword [ebp+0x418]}
0043ca94        player->velocity.z = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043ca94        unimplemented  {fstp dword [ebp+0x418], st0}
0043c6d0        eax_121.b = player->attachment_exit_pending
0043c6d8        if (eax_121.b != 0)
0043c6d8        goto label_43ca46
0043c6de        eax_121.b = player->completion_handoff_active
0043c6e6        if (eax_121.b == 0)
0043c6f0        if (game_12->level_mode == 4)
0043c6f2        unimplemented  {fld st0, dword [ebp+0x70]}
0043c6f5        unimplemented  {fsub st0, dword [esp+0x10]}
0043c6f9        struct SubgameRuntime* game_22 = game_12
0043c700        unimplemented  {fdiv st0, dword [ebp+0x418]}
0043c706        unimplemented  {fsubr st0, dword [0x497220]}
0043c70c        unimplemented  {fmul st0, dword [0x4972c8]}
0043c712        float delta_ticks = fconvert.s(unimplemented  {fstp dword [esp], st0})
0043c712        unimplemented  {fstp dword [esp], st0}
0043c715        advance_timer_counters(&player->stopwatch, delta_ticks)
0043c720        player->completion_handoff_timer = 0f
0043c726        player->completion_handoff_timer_step = 0.0166666675f
0043c730        player->completion_handoff_voice_gate = 0
0043c737        unimplemented  {fld st0, dword [ecx+0x38]}
0043c73a        unimplemented  {fmul st0, dword [0x4975b0]}
0043c740        unimplemented  {fld st0, dword [ebp+0x418]}
0043c746        unimplemented  {fcomp st0, st1} f- unimplemented  {fcomp st0, st1}
0043c746        bool c0_47 = unimplemented  {fcomp st0, st1} f< unimplemented  {fcomp st0, st1}
0043c746        bool c2_47 = is_unordered.t(unimplemented  {fcomp st0, st1}, unimplemented  {fcomp st0, st1})
0043c746        bool c3_47 = unimplemented  {fcomp st0, st1} f== unimplemented  {fcomp st0, st1}
0043c746        unimplemented  {fcomp st0, st1}
0043c746        int16_t top_146 = top_142 - 1
0043c74d        if ((((c0_47 ? 1 : 0) << 8 | (c2_47 ? 1 : 0) << 0xa | (c3_47 ? 1 : 0) << 0xe | (top_146 & 7) << 0xb):1.b & 1) == 0)
0043c74f        unimplemented  {fstp st0, st0}
0043c74f        unimplemented  {fstp st0, st0}
0043c751        unimplemented  {fld st0, dword [ecx+0x38]}
0043c754        unimplemented  {fmul st0, dword [0x497228]}
0043c75a        unimplemented  {fld st0, dword [ebp+0x418]}
0043c760        unimplemented  {fcomp st0, st1} f- unimplemented  {fcomp st0, st1}
0043c760        bool c0_48 = unimplemented  {fcomp st0, st1} f< unimplemented  {fcomp st0, st1}
0043c760        bool c2_48 = is_unordered.t(unimplemented  {fcomp st0, st1}, unimplemented  {fcomp st0, st1})
0043c760        bool c3_48 = unimplemented  {fcomp st0, st1} f== unimplemented  {fcomp st0, st1}
0043c760        unimplemented  {fcomp st0, st1}
0043c767        if ((((c0_48 ? 1 : 0) << 8 | (c2_48 ? 1 : 0) << 0xa | (c3_48 ? 1 : 0) << 0xe | (top_146 & 7) << 0xb):1.b & 0x41) != 0)
0043c769        unimplemented  {fstp st0, st0}
0043c769        unimplemented  {fstp st0, st0}
0043c76b        unimplemented  {fld st0, dword [ebp+0x418]}
0043c771        player->velocity.z = fconvert.s(unimplemented  {fstp dword [ebp+0x418], st0})
0043c771        unimplemented  {fstp dword [ebp+0x418], st0}
0043c771        top_142 = top_146 + 1
0043c77c        reset_voice_manager(0x751498)
0043c787        end_jetpack_hover(&player->sub_hover)
0043c797        player->presentation.cutscene.state = CUT_SCENE_STATE_COMPLETION_PENDING
0043c79d        play_sound_effect(0)
0043c7a2        player->boost_one_tick = 0
0043c7b0        player->completion_handoff_active = 1
0043c7bd        unimplemented  {fild st0, dword [ecx+0x58]}
0043c7c0        unimplemented  {fadd dword [0x4973cc]}
0043c7c6        long double temp34_1 = fconvert.t(player->body.transform.position.z)
0043c7c6        unimplemented  {fcomp st0, dword [ebp+0x70]} f- temp34_1
0043c7c6        bool c0_49 = unimplemented  {fcomp st0, dword [ebp+0x70]} f< temp34_1
0043c7c6        bool c2_49 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x70]}, temp34_1)
0043c7c6        bool c3_49 = unimplemented  {fcomp st0, dword [ebp+0x70]} f== temp34_1
0043c7c6        unimplemented  {fcomp st0, dword [ebp+0x70]}
0043c7ce        if ((((c0_49 ? 1 : 0) << 8 | (c2_49 ? 1 : 0) << 0xa | (c3_49 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb):1.b & 1) != 0)
0043c7d0        unimplemented  {fld st0, dword [ecx+0x38]}
0043c7d3        unimplemented  {fld st0, st0}
0043c7d5        unimplemented  {fmulp st1, st0}
0043c7d5        unimplemented  {fmulp st1, st0}
0043c7d7        unimplemented  {fmul st0, dword [0x4973bc]}
0043c7dd        unimplemented  {fadd st0, st0}
0043c7df        unimplemented  {fsubr st0, dword [ebp+0x418]}
0043c7e5        player->velocity.z = fconvert.s(unimplemented  {fst dword [ebp+0x418], st0})
0043c7eb        long double temp39_1 = fconvert.t(0f)
0043c7eb        unimplemented  {fcomp st0, dword [0x497234]} f- temp39_1
0043c7eb        bool c0_50 = unimplemented  {fcomp st0, dword [0x497234]} f< temp39_1
0043c7eb        bool c2_50 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp39_1)
0043c7eb        bool c3_50 = unimplemented  {fcomp st0, dword [0x497234]} f== temp39_1
0043c7eb        unimplemented  {fcomp st0, dword [0x497234]}
0043c7f6        if ((((c0_50 ? 1 : 0) << 8 | (c2_50 ? 1 : 0) << 0xa | (c3_50 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb):1.b & 1) != 0)
0043c7f8        player->velocity.z = 0f
0043c7fe        unimplemented  {fld st0, dword [ebp+0x2748]}
0043c804        unimplemented  {fadd dword [ebp+0x2744]}
0043c80a        player->completion_handoff_cycle_progress = fconvert.s(unimplemented  {fst dword [ebp+0x2744], st0})
0043c810        long double temp38_1 = fconvert.t(1f)
0043c810        unimplemented  {fcomp st0, dword [0x497220]} f- temp38_1
0043c810        bool c0_51 = unimplemented  {fcomp st0, dword [0x497220]} f< temp38_1
0043c810        bool c2_51 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp38_1)
0043c810        bool c3_51 = unimplemented  {fcomp st0, dword [0x497220]} f== temp38_1
0043c810        unimplemented  {fcomp st0, dword [0x497220]}
0043c81b        if ((((c0_51 ? 1 : 0) << 8 | (c2_51 ? 1 : 0) << 0xa | (c3_51 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb):1.b & 0x41) == 0)
0043c81d        player->completion_handoff_cycle_progress = 0f
0043c823        unimplemented  {fld st0, dword [ebp+0x444]}
0043c829        unimplemented  {fadd dword [ebp+0x448]}
0043c82f        struct SubgameRuntime* game_13 = player->game
0043c835        player->completion_handoff_timer = fconvert.s(unimplemented  {fstp dword [ebp+0x444], st0})
0043c835        unimplemented  {fstp dword [ebp+0x444], st0}
0043c83b        game_13->subgame_rebuild_selector = 2
0043c845        unimplemented  {fld st0, dword [ebp+0x444]}
0043c84b        long double temp43_1 = fconvert.t(2f)
0043c84b        unimplemented  {fcomp st0, dword [0x4974a4]} f- temp43_1
0043c84b        bool c0_52 = unimplemented  {fcomp st0, dword [0x4974a4]} f< temp43_1
0043c84b        bool c2_52 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4974a4]}, temp43_1)
0043c84b        bool c3_52 = unimplemented  {fcomp st0, dword [0x4974a4]} f== temp43_1
0043c84b        unimplemented  {fcomp st0, dword [0x4974a4]}
0043c851        eax_121 = (c0_52 ? 1 : 0) << 8 | (c2_52 ? 1 : 0) << 0xa | (c3_52 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb
0043c856        if ((eax_121:1.b & 0x41) == 0)
0043c858        eax_121.b = player->completion_handoff_voice_gate
0043c860        if (eax_121.b == 0)
0043c86d        player->completion_handoff_voice_gate = 1
0043c874        play_voice_manager(0x751498, 8, 2, 0xffffffff)
0043c879        unimplemented  {fld st0, dword [ebp+0x444]}
0043c87f        long double temp47_1 = fconvert.t(2f)
0043c87f        unimplemented  {fcomp st0, dword [0x4974a4]} f- temp47_1
0043c87f        bool c0_53 = unimplemented  {fcomp st0, dword [0x4974a4]} f< temp47_1
0043c87f        bool c2_53 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4974a4]}, temp47_1)
0043c87f        bool c3_53 = unimplemented  {fcomp st0, dword [0x4974a4]} f== temp47_1
0043c87f        unimplemented  {fcomp st0, dword [0x4974a4]}
0043c88a        if ((((c0_53 ? 1 : 0) << 8 | (c2_53 ? 1 : 0) << 0xa | (c3_53 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb):1.b & 0x41) == 0)
0043c88c        struct SubgameRuntime* game_5 = player->game
0043c892        int32_t level_mode_1 = game_5->level_mode
0043c89c        if (level_mode_1 == 0 || level_mode_1 == 1)
0043c8b8        if (game_5->completion.gate_18 == 1 && (player->control_source->control_flags_a:1.b & 0x40) != 0)
0043c8ba        player->completion_handoff_timer = 5.0999999f
0043c8c6        if (game_5->completion.state == COMPLETION_STATE_CONTINUE_ACCEPTED)
0043c8c8        player->completion_handoff_timer = 5.0999999f
0043c8ce        unimplemented  {fld st0, dword [ebp+0x444]}
0043c8d4        long double temp50_1 = fconvert.t(5f)
0043c8d4        unimplemented  {fcomp st0, dword [0x497288]} f- temp50_1
0043c8d4        bool c0_54 = unimplemented  {fcomp st0, dword [0x497288]} f< temp50_1
0043c8d4        bool c2_54 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497288]}, temp50_1)
0043c8d4        bool c3_54 = unimplemented  {fcomp st0, dword [0x497288]} f== temp50_1
0043c8d4        unimplemented  {fcomp st0, dword [0x497288]}
0043c8df        if ((((c0_54 ? 1 : 0) << 8 | (c2_54 ? 1 : 0) << 0xa | (c3_54 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb):1.b & 0x41) == 0)
0043c8e1        struct SubgameRuntime* game_14 = player->game
0043c8e7        int32_t level_mode = game_14->level_mode
0043c8f9        if ((level_mode == 0 || level_mode == 1) && game_14->completion.state != COMPLETION_STATE_CONTINUE_ACCEPTED)
0043c8fb        unimplemented  {fld st0, dword [ebp+0x444]}
0043c901        unimplemented  {fsub st0, dword [ebp+0x448]}
0043c907        player->completion_handoff_timer = fconvert.s(unimplemented  {fstp dword [ebp+0x444], st0})
0043c907        unimplemented  {fstp dword [ebp+0x444], st0}
0043c90d        unimplemented  {fld st0, dword [ebp+0x444]}
0043c913        long double temp54_1 = fconvert.t(5f)
0043c913        unimplemented  {fcomp st0, dword [0x497288]} f- temp54_1
0043c913        bool c0_55 = unimplemented  {fcomp st0, dword [0x497288]} f< temp54_1
0043c913        bool c2_55 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497288]}, temp54_1)
0043c913        bool c3_55 = unimplemented  {fcomp st0, dword [0x497288]} f== temp54_1
0043c913        unimplemented  {fcomp st0, dword [0x497288]}
0043c91e        if ((((c0_55 ? 1 : 0) << 8 | (c2_55 ? 1 : 0) << 0xa | (c3_55 ? 1 : 0) << 0xe | (top_142 & 7) << 0xb):1.b & 0x41) == 0)
0043c924        struct GameRoot* game_base_1 = g_game_base
0043c92c        int32_t state = game_base_1->fade.state
0043c931        if (state == 0)
0043c934        begin_frontend_fade_out(&game_base_1->fade, 0)
0043c941        if (state == 4)
0043c947        struct SubgameRuntime* game_6 = player->game
0043c953        if (game_6->completion.state != COMPLETION_STATE_INACTIVE)
0043c95b        flush_row_event_display(&game_6->completion)
0043c960        struct SubgameRuntime* game_15 = player->game
0043c969        if (game_15->level_mode != 0)
0043c9c8        complete_subgame(game_15, 1)
0043c97d        if (game_15->level_mode_arg == g_game_base->subgame.galaxy.record_count - 1)
0043c981        complete_subgame(game_15, 1)
0043c98c        g_game_base->players[0].saved_frontend_state = 0x1d
0043c99c        g_game_base->players[0].frontend_state = 0x1a
0043c9ad        return
0043c9af        complete_subgame(game_15, 0)
0043c9ba        player->game->subgame_rebuild_selector = 1
0043c9cd        struct SubgameRuntime* game_19 = player->game
0043c9d7        if (game_19->level_mode == 7)
0043c9df        g_game_base->players[0].frontend_state = 0x1a
0043c9ef        g_game_base->players[0].saved_frontend_state = 2
0043ca00        return
0043ca09        struct GameRoot* game_base_2 = g_game_base
0043ca14        game_base_2->players[0].saved_frontend_state = game_base_2->players[0].frontend_state
0043ca1a        struct GameRoot* game_base_4 = g_game_base
0043ca20        if (game_19->selected_level_record_persistent == 0)
0043ca34        game_base_4->players[0].frontend_state = 0x1b
0043ca45        return
0043ca22        game_base_4->players[0].frontend_state = 0x1a
0043ca33        return
0043ca9c        float x_1 = ebx_1->x
0043caa5        float y = ebx_1->y
0043caac        float z = ebx_1->z
0043cab8        if (player->follow_state.active == 1)
0043cac4        ebx_1->x = player->follow_state.output_position.x
0043cac9        ebx_1->y = player->follow_state.output_position.y
0043cacf        ebx_1->z = player->follow_state.output_position.z
0043cad8        update_jetpack_gauge(&player->sub_hover)
0043cae5        if (player->completion_handoff_active != 0)
0043cae7        struct GameRoot* game_base_3 = g_game_base
0043cafd        __builtin_memcpy(&game_base_3->players[0].completion_handoff_transform, &game_base_3->players[0].body.transform, 0x40)
0043cb06        unimplemented  {fld st0, dword [eax+0x300]}
0043cb0c        unimplemented  {fsub st0, dword [0x497220]}
0043cb12        g_game_base->players[0].completion_handoff_transform.position.y = fconvert.s(unimplemented  {fstp dword [eax+0x300], st0})
0043cb12        unimplemented  {fstp dword [eax+0x300], st0}
0043cb1e        update_damage_gauge(&player->damage_gauge)
0043cb29        update_progress_bar(&player->progress_bar)
0043cb36        unimplemented  {fld st0, dword [ebp+0x276c]}
0043cb40        unimplemented  {fld st0, st0}
0043cb42        player->cached_camera_target_world.x = ebx_1->x
0043cb4a        player->cached_camera_target_world.y = ebx_1->y
0043cb4d        player->cached_camera_target_world.z = ebx_1->z
0043cb50        unimplemented  {fmul st0, dword [ebp+0x58]}
0043cb53        float var_18_1 = fconvert.s(unimplemented  {fstp dword [esp+0x38], st0})
0043cb53        unimplemented  {fstp dword [esp+0x38], st0}
0043cb57        unimplemented  {fld st0, st0}
0043cb59        unimplemented  {fmul st0, dword [ebp+0x5c]}
0043cb5c        float var_14_1 = fconvert.s(unimplemented  {fstp dword [esp+0x3c], st0})
0043cb5c        unimplemented  {fstp dword [esp+0x3c], st0}
0043cb60        unimplemented  {fmul st0, dword [ebp+0x60]}
0043cb63        unimplemented  {fld st0, dword [ebp+0x2768]}
0043cb69        unimplemented  {fld st0, st0}
0043cb6b        unimplemented  {fmul st0, dword [ebp+0x48]}
0043cb6e        float var_3c_1 = fconvert.s(unimplemented  {fstp dword [esp+0x14], st0})
0043cb6e        unimplemented  {fstp dword [esp+0x14], st0}
0043cb72        unimplemented  {fld st0, st0}
0043cb74        unimplemented  {fmul st0, dword [ebp+0x4c]}
0043cb77        float var_38_1 = fconvert.s(unimplemented  {fstp dword [esp+0x18], st0})
0043cb77        unimplemented  {fstp dword [esp+0x18], st0}
0043cb7b        unimplemented  {fmul st0, dword [ebp+0x50]}
0043cb7e        unimplemented  {fld st0, dword [ebp+0x2764]}
0043cb84        unimplemented  {fld st0, st0}
0043cb86        unimplemented  {fmul st0, dword [ebp+0x38]}
0043cb89        position.x = fconvert.s(unimplemented  {fstp dword [esp+0x20], st0})
0043cb89        unimplemented  {fstp dword [esp+0x20], st0}
0043cb8d        unimplemented  {fld st0, st0}
0043cb8f        unimplemented  {fmul st0, dword [ebp+0x3c]}
0043cb92        position.y = fconvert.s(unimplemented  {fstp dword [esp+0x24], st0})
0043cb92        unimplemented  {fstp dword [esp+0x24], st0}
0043cb96        unimplemented  {fmul st0, dword [ebp+0x40]}
0043cb99        unimplemented  {fld st0, dword [esp+0x20]}
0043cb9d        unimplemented  {fadd dword [esp+0x14]}
0043cba1        float var_24_1 = fconvert.s(unimplemented  {fstp dword [esp+0x2c], st0})
0043cba1        unimplemented  {fstp dword [esp+0x2c], st0}
0043cba5        unimplemented  {fld st0, dword [esp+0x24]}
0043cba9        unimplemented  {fadd dword [esp+0x18]}
0043cbad        float var_20_1 = fconvert.s(unimplemented  {fstp dword [esp+0x30], st0})
0043cbad        unimplemented  {fstp dword [esp+0x30], st0}
0043cbb1        unimplemented  {faddp st1, st0}
0043cbb1        unimplemented  {faddp st1, st0}
0043cbb3        unimplemented  {fld st0, dword [esp+0x2c]}
0043cbb7        unimplemented  {fadd dword [esp+0x38]}
0043cbbb        position.x = fconvert.s(unimplemented  {fstp dword [esp+0x20], st0})
0043cbbb        unimplemented  {fstp dword [esp+0x20], st0}
0043cbbf        unimplemented  {fld st0, dword [esp+0x30]}
0043cbc3        unimplemented  {fadd dword [esp+0x3c]}
0043cbc7        position.y = fconvert.s(unimplemented  {fstp dword [esp+0x24], st0})
0043cbc7        unimplemented  {fstp dword [esp+0x24], st0}
0043cbcb        unimplemented  {faddp st1, st0}
0043cbcb        unimplemented  {faddp st1, st0}
0043cbcd        unimplemented  {fld st0, dword [esp+0x20]}
0043cbd1        unimplemented  {fadd dword [eax]}
0043cbd3        player->cached_camera_target_world.x = fconvert.s(unimplemented  {fstp dword [eax], st0})
0043cbd3        unimplemented  {fstp dword [eax], st0}
0043cbd5        unimplemented  {fld st0, dword [esp+0x24]}
0043cbd9        unimplemented  {fadd dword [eax+0x4]}
0043cbdc        player->cached_camera_target_world.y = fconvert.s(unimplemented  {fstp dword [eax+0x4], st0})
0043cbdc        unimplemented  {fstp dword [eax+0x4], st0}
0043cbdf        unimplemented  {fadd dword [eax+0x8]}
0043cbe2        player->cached_camera_target_world.z = fconvert.s(unimplemented  {fstp dword [eax+0x8], st0})
0043cbe2        unimplemented  {fstp dword [eax+0x8], st0}
0043cbe5        float skin_hold_ticks = player->damage_gauge.skin_hold_ticks
0043cbed        if (skin_hold_ticks s> 0)
0043cbf0        player->damage_gauge.skin_hold_ticks = skin_hold_ticks i- 1
0043cbfd        if (player->follow_state.active == 1)
0043cc03        ebx_1->x = x_1
0043cc0b        unimplemented  {fld st0, dword [ecx+0x38]}
0043cc0e        unimplemented  {fmul st0, dword [0x4975b4]}
0043cc14        player->lane_lean_progress_step = fconvert.s(unimplemented  {fst dword [ebp+0x35c], st0})
0043cc20        int16_t top_207
0043cc20        int16_t top_191
0043cc20        if (player->lane_lean_state == 0)
0043cc49        unimplemented  {fstp st0, st0}
0043cc49        unimplemented  {fstp st0, st0}
0043cc49        top_207 = top_191 + 4
0043cc22        unimplemented  {fadd dword [ebp+0x358]}
0043cc28        player->lane_lean_progress = fconvert.s(unimplemented  {fst dword [ebp+0x358], st0})
0043cc2e        long double temp46_1 = fconvert.t(1f)
0043cc2e        unimplemented  {fcomp st0, dword [0x497220]} f- temp46_1
0043cc2e        bool c0_58 = unimplemented  {fcomp st0, dword [0x497220]} f< temp46_1
0043cc2e        bool c2_58 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp46_1)
0043cc2e        bool c3_58 = unimplemented  {fcomp st0, dword [0x497220]} f== temp46_1
0043cc2e        unimplemented  {fcomp st0, dword [0x497220]}
0043cc2e        top_207 = top_191 + 4
0043cc39        if ((((c0_58 ? 1 : 0) << 8 | (c2_58 ? 1 : 0) << 0xa | (c3_58 ? 1 : 0) << 0xe | (top_207 & 7) << 0xb):1.b & 0x41) == 0)
0043cc3b        player->lane_lean_progress = 0f
0043cc41        player->lane_lean_state = 0
0043cc51        if (player->timer_360_state != 0)
0043cc53        unimplemented  {fld st0, dword [ebp+0x36c]}
0043cc59        unimplemented  {fadd dword [ebp+0x368]}
0043cc5f        player->timer_360_progress = fconvert.s(unimplemented  {fst dword [ebp+0x368], st0})
0043cc65        long double temp53_1 = fconvert.t(1f)
0043cc65        unimplemented  {fcomp st0, dword [0x497220]} f- temp53_1
0043cc65        bool c0_59 = unimplemented  {fcomp st0, dword [0x497220]} f< temp53_1
0043cc65        bool c2_59 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp53_1)
0043cc65        bool c3_59 = unimplemented  {fcomp st0, dword [0x497220]} f== temp53_1
0043cc65        unimplemented  {fcomp st0, dword [0x497220]}
0043cc70        if ((((c0_59 ? 1 : 0) << 8 | (c2_59 ? 1 : 0) << 0xa | (c3_59 ? 1 : 0) << 0xe | (top_207 & 7) << 0xb):1.b & 0x41) == 0)
0043cc72        player->timer_360_progress = 0f
0043cc78        player->timer_360_state = 0
0043cc84        unimplemented  {fld st0, dword [edx+0x38]}
0043cc87        unimplemented  {fmul st0, dword [0x4975ac]}
0043cc8d        player->nuke_effect_progress_step = fconvert.s(unimplemented  {fst dword [ebp+0x378], st0})
0043cc93        unimplemented  {fld st0, dword [ebp+0x374]}
0043cc99        long double temp52_1 = fconvert.t(0f)
0043cc99        unimplemented  {fcomp st0, dword [0x497234]} f- temp52_1
0043cc99        bool c0_60 = unimplemented  {fcomp st0, dword [0x497234]} f< temp52_1
0043cc99        bool c2_60 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp52_1)
0043cc99        bool c3_60 = unimplemented  {fcomp st0, dword [0x497234]} f== temp52_1
0043cc99        unimplemented  {fcomp st0, dword [0x497234]}
0043cca4        int16_t top_212
0043cca4        if ((((c0_60 ? 1 : 0) << 8 | (c2_60 ? 1 : 0) << 0xa | (c3_60 ? 1 : 0) << 0xe | ((top_207 - 1) & 7) << 0xb):1.b & 0x41) != 0)
0043ccdf        unimplemented  {fstp st0, st0}
0043ccdf        unimplemented  {fstp st0, st0}
0043ccdf        top_212 = top_207
0043cca6        unimplemented  {fadd dword [ebp+0x374]}
0043ccac        player->nuke_effect_progress = fconvert.s(unimplemented  {fst dword [ebp+0x374], st0})
0043ccb2        long double temp55_1 = fconvert.t(1f)
0043ccb2        unimplemented  {fcomp st0, dword [0x497220]} f- temp55_1
0043ccb2        bool c0_61 = unimplemented  {fcomp st0, dword [0x497220]} f< temp55_1
0043ccb2        bool c2_61 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp55_1)
0043ccb2        bool c3_61 = unimplemented  {fcomp st0, dword [0x497220]} f== temp55_1
0043ccb2        unimplemented  {fcomp st0, dword [0x497220]}
0043ccb2        top_212 = top_207
0043ccbd        if ((((c0_61 ? 1 : 0) << 8 | (c2_61 ? 1 : 0) << 0xa | (c3_61 ? 1 : 0) << 0xe | (top_212 & 7) << 0xb):1.b & 0x41) != 0)
0043ccd8        update_nuke(&player->nuke)
0043ccc5        player->nuke_effect_progress = 0f
0043cccb        uninit_nuke(&player->nuke)
0043cce1        struct SubgameRuntime* game_16 = player->game
0043cceb        if (game_16->level_mode == 4)
0043cd07        void* eax_139 = game_16->level_mode_arg * 0x1fac0 + game_16
0043cd1e        if (*(eax_139 + 0x944150) == 1 && game_16->selected_level_record_active == 0)
0043cd24        int32_t replay_update_cursor = game_16->replay_update_cursor
0043cd2a        int32_t replay_update_cursor_1 = *(eax_139 + 0x9441bc)
0043cd32        if (replay_update_cursor s>= replay_update_cursor_1)
0043cd34        replay_update_cursor = replay_update_cursor_1
0043cd36        int32_t startup_track_index = player->startup_track_index
0043cd3e        int32_t edi_8
0043cd3e        int32_t replay_update_cursor_2
0043cd3e        if (startup_track_index != 0)
0043cd46        edi_8 = *(eax_139 + 0x944174) - startup_track_index
0043cd48        replay_update_cursor_2 = replay_update_cursor
0043cd48        replay_update_cursor += edi_8
0043cd4a        int16_t top_213
0043cd4a        if (startup_track_index != 0 && replay_update_cursor_2 != neg.d(edi_8))
0043cd6b        eax_139.w = *(eax_139 + replay_update_cursor * 6 + 0x9441c2)
0043cd74        top_213 = top_212 - 1
0043cd74        unimplemented  {call 0x44c8b0}
0043cd79        unimplemented  {fadd dword [0x643190]}
0043cd4c        replay_update_cursor.w = *(eax_139 + 0x9441c2)
0043cd59        top_213 = top_212 - 1
0043cd59        unimplemented  {call 0x44c8b0}
0043cd82        g_subgoldy_ghost_z = fconvert.s(unimplemented  {fstp dword [0x643190], st0})
0043cd82        unimplemented  {fstp dword [0x643190], st0}
0043cd8e        int16_t eax_141
0043cd8e        eax_141.b = player->game->selected_level_record_active
0043cd96        if (eax_141.b != 0)
0043cd9b        g_subgoldy_ghost_z = player->body.transform.position.z
0043cda1        unimplemented  {fld st0, dword [ebp+0x70]}
0043cda4        unimplemented  {fadd dword [0x497448]}
0043cdaa        unimplemented  {fld st0, dword [0x643190]}
0043cdb0        unimplemented  {fcomp st0, st1} f- unimplemented  {fcomp st0, st1}
0043cdb0        bool c0_62 = unimplemented  {fcomp st0, st1} f< unimplemented  {fcomp st0, st1}
0043cdb0        bool c2_62 = is_unordered.t(unimplemented  {fcomp st0, st1}, unimplemented  {fcomp st0, st1})
0043cdb0        bool c3_62 = unimplemented  {fcomp st0, st1} f== unimplemented  {fcomp st0, st1}
0043cdb0        unimplemented  {fcomp st0, st1}
0043cdb7        float subgoldy_ghost_z_1
0043cdb7        if ((((c0_62 ? 1 : 0) << 8 | (c2_62 ? 1 : 0) << 0xa | (c3_62 ? 1 : 0) << 0xe | (top_213 & 7) << 0xb):1.b & 1) == 0)
0043cdc6        subgoldy_ghost_z_1 = fconvert.s(unimplemented  {fstp dword [esp+0x10], st0})
0043cdc6        unimplemented  {fstp dword [esp+0x10], st0}
0043cdc6        top_212 = top_213 + 1
0043cdbe        unimplemented  {fstp st0, st0}
0043cdbe        unimplemented  {fstp st0, st0}
0043cdbe        top_212 = top_213 + 1
0043cdc0        subgoldy_ghost_z_1 = g_subgoldy_ghost_z
0043cdd1        game_16 = set_subgoldy_ghost_z(player, subgoldy_ghost_z_1)
0043cde1        struct SubgameRuntime* game_23 = game_16
0043cde2        unimplemented  {fild st0, dword [edx+0x54]}
0043cdeb        unimplemented  {fdivr st0, dword [ebp+0x70]}
0043cdee        float zoom = fconvert.s(unimplemented  {fstp dword [esp], st0})
0043cdee        unimplemented  {fstp dword [esp], st0}
0043cdf1        set_backdrop_progress_fraction(&g_game_base->backdrop, zoom)
0043cdfc        unimplemented  {fild st0, dword [ecx+0x58]}
0043cdff        unimplemented  {fsub st0, dword [0x4972c0]}
0043ce05        unimplemented  {fld st0, dword [ebp+0x70]}
0043ce08        unimplemented  {fsub st0, dword [0x49720c]}
0043ce0e        float var_40_7 = fconvert.s(unimplemented  {fstp dword [esp+0x10], st0})
0043ce0e        unimplemented  {fstp dword [esp+0x10], st0}
0043ce0e        int16_t top_222 = top_212 - 1
0043ce12        long double temp57_1 = fconvert.t(var_40_7)
0043ce12        unimplemented  {fcom st0, dword [esp+0x10]} f- temp57_1
0043ce12        bool c0_63 = unimplemented  {fcom st0, dword [esp+0x10]} f< temp57_1
0043ce12        bool c2_63 = is_unordered.t(unimplemented  {fcom st0, dword [esp+0x10]}, temp57_1)
0043ce12        bool c3_63 = unimplemented  {fcom st0, dword [esp+0x10]} f== temp57_1
0043ce1b        if ((((c0_63 ? 1 : 0) << 8 | (c2_63 ? 1 : 0) << 0xa | (c3_63 ? 1 : 0) << 0xe | (top_222 & 7) << 0xb):1.b & 1) == 0)
0043ce1d        unimplemented  {fstp st0, st0}
0043ce1d        unimplemented  {fstp st0, st0}
0043ce1f        unimplemented  {fld st0, dword [esp+0x10]}
0043ce23        enum SubHoverState state_1 = player->sub_hover.state
0043ce29        player->interaction_max_z = fconvert.s(unimplemented  {fstp dword [ebp+0x2980], st0})
0043ce29        unimplemented  {fstp dword [ebp+0x2980], st0}
0043ce29        int16_t top_224 = top_222 + 1
0043ce32        if (state_1 == SUB_HOVER_STATE_ACTIVE)
0043ce34        unimplemented  {fld st0, dword [ebp+0x6c]}
0043ce37        long double temp59_1 = fconvert.t(1f)
0043ce37        unimplemented  {fcomp st0, dword [0x497220]} f- temp59_1
0043ce37        bool c0_64 = unimplemented  {fcomp st0, dword [0x497220]} f< temp59_1
0043ce37        bool c2_64 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp59_1)
0043ce37        bool c3_64 = unimplemented  {fcomp st0, dword [0x497220]} f== temp59_1
0043ce37        unimplemented  {fcomp st0, dword [0x497220]}
0043ce42        if ((((c0_64 ? 1 : 0) << 8 | (c2_64 ? 1 : 0) << 0xa | (c3_64 ? 1 : 0) << 0xe | (top_224 & 7) << 0xb):1.b & 1) != 0)
0043ce44        unimplemented  {fld st0, dword [ebp+0x414]}
0043ce4a        unimplemented  {fmul st0, dword [0x49726c]}
0043ce50        player->velocity.y = fconvert.s(unimplemented  {fst dword [ebp+0x414], st0})
0043ce5c        unimplemented  {fld st0, dword [edx+0x38]}
0043ce5f        unimplemented  {fld st0, st0}
0043ce61        unimplemented  {fmul st0, st1}
0043ce63        unimplemented  {fmul st0, dword [0x4975cc]}
0043ce69        unimplemented  {fsubr st0, st2}
0043ce6b        player->velocity.y = fconvert.s(unimplemented  {fstp dword [ebp+0x414], st0})
0043ce6b        unimplemented  {fstp dword [ebp+0x414], st0}
0043ce71        unimplemented  {fstp st0, st0}
0043ce71        unimplemented  {fstp st0, st0}
0043ce73        unimplemented  {fstp st0, st0}
0043ce73        unimplemented  {fstp st0, st0}
0043ce75        player->attachment_exit_pending = 0
0043ce7c        int16_t eax_147
0043ce7c        eax_147.b = player->attachment_exit_pending
0043ce84        if (eax_147.b != 0)
0043ce8a        unimplemented  {fld st0, dword [ebp+0x438]}
0043ce90        unimplemented  {fadd dword [ebp+0x434]}
0043ce96        player->attachment_exit_progress = fconvert.s(unimplemented  {fst dword [ebp+0x434], st0})
0043ce9c        long double temp61_1 = fconvert.t(0.699999988f)
0043ce9c        unimplemented  {fcomp st0, dword [0x497200]} f- temp61_1
0043ce9c        bool c0_65 = unimplemented  {fcomp st0, dword [0x497200]} f< temp61_1
0043ce9c        bool c2_65 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497200]}, temp61_1)
0043ce9c        bool c3_65 = unimplemented  {fcomp st0, dword [0x497200]} f== temp61_1
0043ce9c        unimplemented  {fcomp st0, dword [0x497200]}
0043cea2        eax_147 = (c0_65 ? 1 : 0) << 8 | (c2_65 ? 1 : 0) << 0xa | (c3_65 ? 1 : 0) << 0xe | (top_224 & 7) << 0xb
0043cea7        if ((eax_147:1.b & 0x41) == 0)
0043cea9        eax_147.b = player->attachment_exit_gate_a
0043ceb1        if (eax_147.b == 0)
0043cebd        play_voice_manager(0x751498, 3, 0, 0xffffffff)
0043cec2        int16_t eax_149
0043cec2        eax_149.b = player->control_override_active
0043cec8        player->attachment_exit_gate_a = 1
0043ced1        if (eax_149.b == 0)
0043ced3        unimplemented  {fld st0, dword [ebp+0x6c]}
0043ced6        long double temp68_1 = fconvert.t(-6f)
0043ced6        unimplemented  {fcomp st0, dword [0x4975a8]} f- temp68_1
0043ced6        bool c0_66 = unimplemented  {fcomp st0, dword [0x4975a8]} f< temp68_1
0043ced6        bool c2_66 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4975a8]}, temp68_1)
0043ced6        bool c3_66 = unimplemented  {fcomp st0, dword [0x4975a8]} f== temp68_1
0043ced6        unimplemented  {fcomp st0, dword [0x4975a8]}
0043cee1        if ((((c0_66 ? 1 : 0) << 8 | (c2_66 ? 1 : 0) << 0xa | (c3_66 ? 1 : 0) << 0xe | (top_224 & 7) << 0xb):1.b & 1) != 0)
0043ceef        dispatch_cutscene_animation(&player->presentation, 5, 1, 0xffffffff)
0043cef4        unimplemented  {fld st0, dword [ebp+0x6c]}
0043cef7        long double temp65_1 = fconvert.t(-7f)
0043cef7        unimplemented  {fcomp st0, dword [0x4975bc]} f- temp65_1
0043cef7        bool c0_67 = unimplemented  {fcomp st0, dword [0x4975bc]} f< temp65_1
0043cef7        bool c2_67 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4975bc]}, temp65_1)
0043cef7        bool c3_67 = unimplemented  {fcomp st0, dword [0x4975bc]} f== temp65_1
0043cef7        unimplemented  {fcomp st0, dword [0x4975bc]}
0043cef7        top_224 = top_224
0043cefd        int16_t eax_150 = (c0_67 ? 1 : 0) << 8 | (c2_67 ? 1 : 0) << 0xa | (c3_67 ? 1 : 0) << 0xe | (top_224 & 7) << 0xb
0043cf02        if ((eax_150:1.b & 1) != 0)
0043cf04        eax_150.b = player->attachment_exit_gate_b
0043cf0c        if (eax_150.b == 0)
0043cf19        play_voice_manager(0x751498, 1, 2, 0xffffffff)
0043cf1e        player->attachment_exit_gate_b = 1
0043cf25        player->attachment_exit_gate_a = 1
0043cf2c        unimplemented  {fld st0, dword [ebp+0x330]}
0043cf32        long double temp60_1 = fconvert.t(0f)
0043cf32        unimplemented  {fcomp st0, dword [0x497234]} f- temp60_1
0043cf32        bool c0_68 = unimplemented  {fcomp st0, dword [0x497234]} f< temp60_1
0043cf32        bool c2_68 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp60_1)
0043cf32        bool c3_68 = unimplemented  {fcomp st0, dword [0x497234]} f== temp60_1
0043cf32        unimplemented  {fcomp st0, dword [0x497234]}
0043cf3d        if ((((c0_68 ? 1 : 0) << 8 | (c2_68 ? 1 : 0) << 0xa | (c3_68 ? 1 : 0) << 0xe | (top_224 & 7) << 0xb):1.b & 0x41) == 0)
0043cf3f        unimplemented  {fld st0, dword [ebp+0x334]}
0043cf45        unimplemented  {fadd dword [ebp+0x330]}
0043cf4b        player->startup_voice_timer = fconvert.s(unimplemented  {fst dword [ebp+0x330], st0})
0043cf51        long double temp64_1 = fconvert.t(1f)
0043cf51        unimplemented  {fcomp st0, dword [0x497220]} f- temp64_1
0043cf51        bool c0_69 = unimplemented  {fcomp st0, dword [0x497220]} f< temp64_1
0043cf51        bool c2_69 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp64_1)
0043cf51        bool c3_69 = unimplemented  {fcomp st0, dword [0x497220]} f== temp64_1
0043cf51        unimplemented  {fcomp st0, dword [0x497220]}
0043cf5c        if ((((c0_69 ? 1 : 0) << 8 | (c2_69 ? 1 : 0) << 0xa | (c3_69 ? 1 : 0) << 0xe | (top_224 & 7) << 0xb):1.b & 0x41) == 0)
0043cf69        play_voice_manager(0x751498, 7, 2, 0xffffffff)
0043cf6e        player->startup_voice_timer = 0f
0043cf7a        unimplemented  {fld st0, dword [eax+0x38]}
0043cf7d        unimplemented  {fmul st0, dword [0x4975b0]}
0043cf83        unimplemented  {fld st0, dword [eax+0x38]}
0043cf86        unimplemented  {fmul st0, dword [0x497228]}
0043cf8c        unimplemented  {fsub st0, st1}
0043cf8e        unimplemented  {fmul st0, dword [0x497258]}
0043cf94        unimplemented  {fadd st0, st1}
0043cf96        long double temp63_1 = fconvert.t(player->velocity.z)
0043cf96        unimplemented  {fcomp st0, dword [ebp+0x418]} f- temp63_1
0043cf96        bool c0_70 = unimplemented  {fcomp st0, dword [ebp+0x418]} f< temp63_1
0043cf96        bool c2_70 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x418]}, temp63_1)
0043cf96        bool c3_70 = unimplemented  {fcomp st0, dword [ebp+0x418]} f== temp63_1
0043cf96        unimplemented  {fcomp st0, dword [ebp+0x418]}
0043cfa1        int16_t top_241
0043cfa1        if ((((c0_70 ? 1 : 0) << 8 | (c2_70 ? 1 : 0) << 0xa | (c3_70 ? 1 : 0) << 0xe | ((top_224 - 1) & 7) << 0xb):1.b & 0x41) != 0)
0043cffa        unimplemented  {fstp st0, st0}
0043cffa        unimplemented  {fstp st0, st0}
0043cffa        top_241 = top_224
0043cffc        player->slow_commentary_timer = 0f
0043cfa3        long double temp67_1 = fconvert.t(player->velocity.z)
0043cfa3        unimplemented  {fcomp st0, dword [ebp+0x418]} f- temp67_1
0043cfa3        bool c0_71 = unimplemented  {fcomp st0, dword [ebp+0x418]} f< temp67_1
0043cfa3        bool c2_71 = is_unordered.t(unimplemented  {fcomp st0, dword [ebp+0x418]}, temp67_1)
0043cfa3        bool c3_71 = unimplemented  {fcomp st0, dword [ebp+0x418]} f== temp67_1
0043cfa3        unimplemented  {fcomp st0, dword [ebp+0x418]}
0043cfa3        top_241 = top_224
0043cfa9        int16_t eax_152 = (c0_71 ? 1 : 0) << 8 | (c2_71 ? 1 : 0) << 0xa | (c3_71 ? 1 : 0) << 0xe | (top_241 & 7) << 0xb
0043cfae        if ((eax_152:1.b & 1) == 0)
0043cffc        player->slow_commentary_timer = 0f
0043cfb0        eax_152.b = player->attachment_exit_pending
0043cfc1        if (eax_152.b != 0 || player->click_start.state == CLICK_START_STATE_WAITING_FOR_START)
0043cffc        player->slow_commentary_timer = 0f
0043cfc3        unimplemented  {fld st0, dword [ebp+0x4360]}
0043cfc9        unimplemented  {fadd dword [ebp+0x435c]}
0043cfcf        player->slow_commentary_timer = fconvert.s(unimplemented  {fst dword [ebp+0x435c], st0})
0043cfd5        long double temp69_1 = fconvert.t(1f)
0043cfd5        unimplemented  {fcomp st0, dword [0x497220]} f- temp69_1
0043cfd5        bool c0_72 = unimplemented  {fcomp st0, dword [0x497220]} f< temp69_1
0043cfd5        bool c2_72 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp69_1)
0043cfd5        bool c3_72 = unimplemented  {fcomp st0, dword [0x497220]} f== temp69_1
0043cfd5        unimplemented  {fcomp st0, dword [0x497220]}
0043cfe0        if ((((c0_72 ? 1 : 0) << 8 | (c2_72 ? 1 : 0) << 0xa | (c3_72 ? 1 : 0) << 0xe | (top_241 & 7) << 0xb):1.b & 0x41) == 0)
0043cfed        player->slow_commentary_timer = 0f
0043cff3        play_voice_manager(0x751498, 6, 1, 0xffffffff)
0043d004        handle_subgoldy_collisions(player)
0043d00f        update_anim_manager(&player->presentation.anim_manager)
0043d01a        update_anim_manager(&player->presentation.jetpack_channel.anim_manager)
0043d025        update_anim_manager(&player->presentation.weapon_channels[0].anim_manager)
0043d030        update_anim_manager(&player->presentation.weapon_channels[1].anim_manager)
0043d03b        update_anim_manager(&player->presentation.weapon_channels[2].anim_manager)
0043d04c        update_track_parcels(&player->game->parcel_manager)
0043d057        initialize_cutscene(&player->presentation)
0043d05e        update_player_movement_flags(player)
0043d06f        if (g_game_base->subgame.replay_update_cursor s< 0xa)
0043d077        player->movement_fire_progress = player->movement_fire_progress_step
0043d07d        struct SubgameRuntime* game_17 = player->game
0043d0a6        if ((game_17->runtime_flags & &__dos_header) != 0 && player->completion_handoff_active == 0 && player->control_override_active == 0)
0043d0ac        enum ClickStartState state_2 = player->click_start.state
0043d0b9        if (state_2 == CLICK_START_STATE_INACTIVE || state_2 == CLICK_START_STATE_TEARDOWN)
0043d0bf        unimplemented  {fld st0, dword [ebp+0x2730]}
0043d0c5        long double temp70_1 = fconvert.t(0f)
0043d0c5        unimplemented  {fcomp st0, dword [0x497234]} f- temp70_1
0043d0c5        bool c0_73 = unimplemented  {fcomp st0, dword [0x497234]} f< temp70_1
0043d0c5        bool c2_73 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp70_1)
0043d0c5        bool c3_73 = unimplemented  {fcomp st0, dword [0x497234]} f== temp70_1
0043d0c5        unimplemented  {fcomp st0, dword [0x497234]}
0043d0cb        int16_t eax_155 = (c0_73 ? 1 : 0) << 8 | (c2_73 ? 1 : 0) << 0xa | (c3_73 ? 1 : 0) << 0xe | (top_241 & 7) << 0xb
0043d0d0        if ((eax_155:1.b & 0x41) != 0)
0043d100        eax_155.b = game_17->track_state_latch
0043d108        if (eax_155.b != 0)
0043d10e        uint8_t selected_level_record_active = game_17->selected_level_record_active
0043d116        if (selected_level_record_active == 0)
0043d138        label_43d138:
0043d13f        if ((player->control_source->control_flags_a & 0x4000) != 0)
0043d13f        goto label_43d143
0043d166        if (selected_level_record_active != 0)
0043d166        goto label_43d168
0043d18b        label_43d18b:
0043d18e        if (((player->control_source->control_flags_b).w:1.b & 0x40) != 0)
0043d18e        goto label_43d198
0043d12c        if ((game_17->selected_level_record->run_records[game_17->replay_update_cursor].flags.b & 1) != 0)
0043d143        label_43d143:
0043d143        play_movement_state_sound(player)
0043d14b        update_movement_flag_emitters(player, player)
0043d150        unimplemented  {fld st0, dword [ebp+0x2734]}
0043d156        unimplemented  {fadd dword [0x4973d8]}
0043d15c        player->movement_fire_progress = fconvert.s(unimplemented  {fstp dword [ebp+0x2730], st0})
0043d15c        unimplemented  {fstp dword [ebp+0x2730], st0}
0043d130        if (selected_level_record_active == 0)
0043d130        goto label_43d138
0043d168        label_43d168:
0043d17c        if ((game_17->selected_level_record->run_records[game_17->replay_update_cursor].flags.b & 2) != 0)
0043d198        label_43d198:
0043d198        player->movement_fire_progress = player->movement_fire_progress_step
0043d19e        play_movement_state_sound(player)
0043d1a6        update_movement_flag_emitters(player, player)
0043d180        if (selected_level_record_active == 0)
0043d180        goto label_43d18b
0043d0d2        unimplemented  {fld st0, dword [ebp+0x2734]}
0043d0d8        unimplemented  {fadd dword [ebp+0x2730]}
0043d0de        player->movement_fire_progress = fconvert.s(unimplemented  {fst dword [ebp+0x2730], st0})
0043d0e4        long double temp71_1 = fconvert.t(1f)
0043d0e4        unimplemented  {fcomp st0, dword [0x497220]} f- temp71_1
0043d0e4        bool c0_74 = unimplemented  {fcomp st0, dword [0x497220]} f< temp71_1
0043d0e4        bool c2_74 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp71_1)
0043d0e4        bool c3_74 = unimplemented  {fcomp st0, dword [0x497220]} f== temp71_1
0043d0e4        unimplemented  {fcomp st0, dword [0x497220]}
0043d0ef        if ((((c0_74 ? 1 : 0) << 8 | (c2_74 ? 1 : 0) << 0xa | (c3_74 ? 1 : 0) << 0xe | (top_241 & 7) << 0xb):1.b & 0x41) == 0)
0043d0f5        player->movement_fire_progress = 0f
0043d1b7        update_row_event_display(&player->game->completion)
0043d1bc        struct SubgameRuntime* game_7 = player->game
0043d1c9        game_7->current_high_score_record.replay_sample_count += 1
0043d1cf        struct SubgameRuntime* game_8 = player->game
0043d1dc        game_8->replay_update_cursor += 1
0043d1e2        struct SubgameRuntime* game_9 = player->game
0043d1f2        if (game_9->replay_update_cursor == 0x5208)
0043d1fa        show_times_up_message(&game_9->times_up)
0043d20b        update_times_up(&player->game->times_up)
0043b143        if (g_game_base->players[0].frontend_state != 9)
0043b14f        update_damage_gauge(&player->damage_gauge)
0043b15a        update_progress_bar(&player->progress_bar)
0043b165        update_warning(&player->warning)
0043b176        update_row_event_display(&player->game->completion)
0043d217        return
