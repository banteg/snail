/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_subgoldy @ 0x43a9c0 */

0043a9c4        int32_t ebx
0043a9c4        int32_t var_4 = ebx
0043a9c5        int32_t ebp
0043a9c5        int32_t var_8 = ebp
0043a9c6        int32_t esi
0043a9c6        int32_t var_c = esi
0043a9cb        int32_t edi
0043a9cb        int32_t var_10 = edi
0043a9cc        player->player_slot = player_slot
0043a9de        player->game = data_4df904 + 0x74618
0043a9e4        player->heading_roll = 0f
0043a9ea        player->row_event.id = 0
0043a9f0        player->control_override_active = 0
0043a9f6        player->nuke.owner_player = player
0043a9fc        player->nuke.state = 0
0043aa02        player->row_event_cutscene_started = 0
0043aa08        player->resurrect_progress = 0f
0043aa0e        player->completion_handoff_timer = 0f
0043aa14        player->movement_flags = 0
0043aa1a        player->previous_movement_flags = 0xffffffff
0043aa24        player->_pad_1e4[0] = 0
0043aa2a        player->presentation.invincible_shell._pad_90[0xc] = 0
0043aa36        player->game->row_event_display.state = 0
0043aa3c        player->presentation.jetpack_channel.selected_state = 0
0043aa42        player->presentation.weapon_channels[0].selected_state = 0
0043aa48        player->presentation.weapon_channels[1].selected_state = 0
0043aa4e        player->presentation.weapon_channels[2].selected_state = 0
0043aa54        player->cutscene_pitch_cycle = 0f
0043aa5a        player->cutscene_pitch_cycle_step = 0f
0043aa60        player->presentation
0043aa6c        sub_41aa30()
0043aa71        player->interaction_max_z = -19f
0043aa7b        player->movement_sound_variant_sample = 0
0043aa86        player->presentation.invincible_shell._pad_90[4] = 0
0043aa86        player->presentation.invincible_shell._pad_90[5] = 0
0043aa86        player->presentation.invincible_shell._pad_90[6] = 0
0043aa86        player->presentation.invincible_shell._pad_90[7] = 0
0043aa8c        player->presentation.invincible_shell._pad_90[8] = 0x89
0043aa8c        player->presentation.invincible_shell._pad_90[9] = 0x88
0043aa8c        player->presentation.invincible_shell._pad_90[0xa] = 0x88
0043aa8c        player->presentation.invincible_shell._pad_90[0xb] = 0x3c
0043aa92        player->slow_commentary_timer = 0f
0043aa9e        player->slow_commentary_step = 0.0166666675f
0043aaa4        initialize_score_stats()
0043aaaf        initialize_invincible_shell(&player->presentation.invincible_shell)
0043aabe        player->startup_voice_step = 0.0555555522f
0043aac4        player->startup_voice_timer = 0.0555555522f
0043aaca        player->attachment_exit_progress = 0f
0043aad0        player->attachment_exit_progress_step = 0.0166666675f
0043aadf        if ((player->presentation.visual_root->__offset(0x10).d & 0x200000) == 0)
0043ab31        initialize_anim_manager(&player->presentation.anim_manager)
0043ab36        player->presentation.anim_manager.active = 0
0043aaed        uint32_t eax_1
0043aaed        eax_1:1.b = player->presentation.visual_flags:1.b | 8
0043aaf2        player->presentation.visual_flags = eax_1
0043aaf8        player->presentation._pad_78[0] = (&player->presentation.anim_manager).b
0043aaf8        player->presentation._pad_78[1] = (&player->presentation.anim_manager):1.b
0043aaf8        player->presentation._pad_78[2] = (&player->presentation.anim_manager):2.b
0043aaf8        player->presentation._pad_78[3] = (&player->presentation.anim_manager):3.b
0043aafe        initialize_anim_manager(&player->presentation.anim_manager)
0043ab09        player->presentation.anim_manager.active = 1
0043ab15        player->presentation.anim_manager.self_ref = &player->presentation
0043ab1b        player->presentation.anim_manager.queue_sentinel = &player->presentation._pad_14c
0043ab21        player->presentation.anim_manager.queued_animation_count = 0
0043ab41        if ((player->presentation.jetpack_channel.visual_root->__offset(0x10).d & 0x200000) == 0)
0043ab9c        initialize_anim_manager(&player->presentation.jetpack_channel.anim_manager)
0043aba1        player->presentation.jetpack_channel.anim_manager.active = 0
0043ab52        uint32_t ecx_10
0043ab52        ecx_10:1.b = (player->presentation.jetpack_channel.visual_flags & 0xffffffdf):1.b | 8
0043ab55        player->presentation.jetpack_channel.visual_flags = ecx_10
0043ab5b        player->presentation.jetpack_channel.selected_state = 0
0043ab63        player->presentation.jetpack_channel.active_anim_manager = &player->presentation.jetpack_channel.anim_manager
0043ab69        initialize_anim_manager(&player->presentation.jetpack_channel.anim_manager)
0043ab74        player->presentation.jetpack_channel.anim_manager.active = 1
0043ab80        player->presentation.jetpack_channel.anim_manager.self_ref = &player->presentation.jetpack_channel
0043ab86        player->presentation.jetpack_channel.anim_manager.queue_sentinel = &player->presentation.jetpack_channel._pad_150
0043ab8c        player->presentation.jetpack_channel.anim_manager.queued_animation_count = 0
0043abac        if ((player->presentation.weapon_channels[0].visual_root->__offset(0x10).d & 0x200000) == 0)
0043ac07        initialize_anim_manager(&player->presentation.weapon_channels[0].anim_manager)
0043ac0c        player->presentation.weapon_channels[0].anim_manager.active = 0
0043abbf        uint32_t edx_4
0043abbf        edx_4:1.b = (player->presentation.weapon_channels[0].visual_flags & 0xffffffdf):1.b | 8
0043abc2        player->presentation.weapon_channels[0].visual_flags = edx_4
0043abc8        player->presentation.weapon_channels[0].selected_state = 0
0043abce        player->presentation.weapon_channels[0].active_anim_manager = &player->presentation.weapon_channels[0].anim_manager
0043abd4        initialize_anim_manager(&player->presentation.weapon_channels[0].anim_manager)
0043abdf        player->presentation.weapon_channels[0].anim_manager.active = 1
0043abeb        player->presentation.weapon_channels[0].anim_manager.self_ref = &player->presentation.weapon_channels
0043abf1        player->presentation.weapon_channels[0].anim_manager.queue_sentinel = &player->presentation.weapon_channels[0]._pad_150
0043abf7        player->presentation.weapon_channels[0].anim_manager.queued_animation_count = 0
0043ac17        if ((player->presentation.weapon_channels[1].visual_root->__offset(0x10).d & 0x200000) == 0)
0043ac71        initialize_anim_manager(&player->presentation.weapon_channels[1].anim_manager)
0043ac76        player->presentation.weapon_channels[1].anim_manager.active = 0
0043ac25        uint32_t eax_5
0043ac25        eax_5.b = player->presentation.weapon_channels[1].visual_flags.b & 0xdf
0043ac27        eax_5:1.b |= 8
0043ac2a        player->presentation.weapon_channels[1].visual_flags = eax_5
0043ac30        player->presentation.weapon_channels[1].selected_state = 0
0043ac38        player->presentation.weapon_channels[1].active_anim_manager = &player->presentation.weapon_channels[1].anim_manager
0043ac3e        initialize_anim_manager(&player->presentation.weapon_channels[1].anim_manager)
0043ac49        player->presentation.weapon_channels[1].anim_manager.active = 1
0043ac55        player->presentation.weapon_channels[1].anim_manager.self_ref = &player->presentation.weapon_channels[1]
0043ac5b        player->presentation.weapon_channels[1].anim_manager.queue_sentinel = &player->presentation.weapon_channels[1]._pad_150
0043ac61        player->presentation.weapon_channels[1].anim_manager.queued_animation_count = 0
0043ac81        if ((player->presentation.weapon_channels[2].visual_root->__offset(0x10).d & 0x200000) == 0)
0043acdc        initialize_anim_manager(&player->presentation.weapon_channels[2].anim_manager)
0043ace1        player->presentation.weapon_channels[2].anim_manager.active = 0
0043ac92        uint32_t ecx_21
0043ac92        ecx_21:1.b = (player->presentation.weapon_channels[2].visual_flags & 0xffffffdf):1.b | 8
0043ac95        player->presentation.weapon_channels[2].visual_flags = ecx_21
0043ac9b        player->presentation.weapon_channels[2].selected_state = 0
0043aca3        player->presentation.weapon_channels[2].active_anim_manager = &player->presentation.weapon_channels[2].anim_manager
0043aca9        initialize_anim_manager(&player->presentation.weapon_channels[2].anim_manager)
0043acb4        player->presentation.weapon_channels[2].anim_manager.active = 1
0043acc0        player->presentation.weapon_channels[2].anim_manager.self_ref = &player->presentation.weapon_channels[2]
0043acc6        player->presentation.weapon_channels[2].anim_manager.queue_sentinel = &player->presentation.weapon_channels[2]._pad_150
0043accc        player->presentation.weapon_channels[2].anim_manager.queued_animation_count = 0
0043ace9        initialize_snail_skin(&player->presentation.snail_skin_transition)
0043acf4        initialize_cutscene_ai(&player->presentation.cutscene_ai)
0043ad05        if (player->game->selected_level_record_active == 0)
0043ad07        player->presentation.cutscene_ai.state = 1
0043ad17        player->presentation.owner_player = player
0043ad1d        set_matrix_identity(&player->presentation.live_matrix)
0043ad28        set_matrix_identity(&player->presentation.cached_cutscene_matrix)
0043ad33        set_matrix_identity(&player->presentation.previous_live_matrix)
0043ad3f        player->presentation.cutscene_ai._pad_59[3] = 0
0043ad3f        player->presentation.cutscene_ai._pad_59[4] = 0
0043ad3f        player->presentation.cutscene_ai._pad_59[5] = 0
0043ad3f        player->presentation.cutscene_ai._pad_59[6] = 0
0043ad45        initialize_click_start(&player->_pad_a0, player)
0043ad50        initialize_cameraman(&player->cameraman)
0043ad5e        initialize_subgoldy_ghost(player, player->player_slot)
0043ad6a        player->damage_retrigger_step = 0.0505050495f
0043ad70        player->surface_reaction_step = 0.0505050495f
0043ad7e        player->live_matrix.position.x = 0
0043ad81        player->live_matrix.position.y = 0f
0043ad84        player->cached_camera_target_world.x = 0
0043ad86        player->live_matrix.position.z = 4f
0043ad8d        float z = player->live_matrix.position.z
0043ad90        player->_pad_37c[0] = 0
0043ad90        player->_pad_37c[1] = 0
0043ad90        player->_pad_37c[2] = 0
0043ad90        player->_pad_37c[3] = 0
0043ad96        player->cached_camera_target_world.y = 0f
0043ad99        player->barrier_hold_progress = 0f
0043ad9f        player->barrier_hold_step = 0.0166666675f
0043ada9        player->damage_retrigger_timer = 0f
0043adaf        player->surface_reaction_timer = 0f
0043adb5        player->presentation.wobble.roll_phase = 0
0043adbb        player->presentation.wobble.roll_phase_step = 0.00574712642f
0043adc5        player->presentation.wobble.lift_phase = 0f
0043adcb        player->presentation.wobble.lift_phase_step = 0.00677506765f
0043add5        player->flag84.b = 0
0043addb        player->cached_camera_target_world.z = z
0043adde        player->velocity.z = 0f
0043ade4        player->velocity.y = 0f
0043adea        player->velocity.x = 0
0043adf9        void* eax_10 = data_4df904
0043adfe        struct PlayerControlSource* eax_11
0043adfe        if (player->player_slot != 1)
0043ae14        if (eax_10 == 0xffffff4c)
0043ae1d        eax_11 = nullptr
0043ae16        eax_11 = eax_10 + 0xec
0043ae05        if (eax_10 == 0xffffffbc)
0043ae1d        eax_11 = nullptr
0043ae07        eax_11 = eax_10 + 0x7c
0043ae25        player->control_source = eax_11
0043ae2b        player->movement_progress = 0f
0043ae31        player->completion_handoff_active.b = 0
0043ae37        player->_pad_2738[0] = 0
0043ae37        player->_pad_2738[1] = 0
0043ae37        player->_pad_2738[2] = 0
0043ae37        player->_pad_2738[3] = 0
0043ae3d        initialize_damage_gauge(&player->damage_gauge)
0043ae4d        player->follow_state.active = 0
0043ae53        uint8_t* transform = &player->_pad_44f[0x1c5]
0043ae59        int32_t i_1 = 0xc
0043ae7e        int32_t i
0043ae60        (transform - 0x614)->_pad_44f[0x245] = 0
0043ae60        (transform - 0x614)->_pad_44f[0x246] = 0
0043ae60        (transform - 0x614)->_pad_44f[0x247] = 0
0043ae60        (transform - 0x614)->_pad_44f[0x248] = 0
0043ae66        set_matrix_identity(transform)
0043ae6b        struct Game* game = player->game
0043ae71        (transform - 0x614)->_pad_44f[0x271] = game.b
0043ae71        (transform - 0x614)->_pad_44f[0x272] = game:1.b
0043ae71        (transform - 0x614)->_pad_44f[0x273] = game:2.b
0043ae71        (transform - 0x614)->_pad_44f[0x274] = game:3.b
0043ae77        transform = &transform[0x2e8]
0043ae7d        i = i_1
0043ae7d        i_1 -= 1
0043ae7e        do while (i != 1)
0043ae89        int32_t edx_11 = player->_pad_00[4].d | 0x20
0043ae8c        int32_t player_slot_1 = player->player_slot
0043ae93        player->_pad_00[4] = edx_11.b
0043ae93        player->_pad_00[5] = edx_11:1.b
0043ae93        player->_pad_00[6] = edx_11:2.b
0043ae93        player->_pad_00[7] = edx_11:3.b
0043ae96        player->completion_handoff_cycle_progress = 0f
0043ae9c        __builtin_strncpy(&player->completion_handoff_cycle_step, "VUU>", 8)
0043aeac        initialize_jetpack_gauge(&player->jetpack_gauge)
0043aeb1        __builtin_memset(&player->lane_lean_state, 0, 0x20)
0043aee1        player->nuke_effect_progress = 0f
0043aee7        player->nuke_effect_progress_step = 0f
0043aeed        player->attachment_exit_pending = 0
0043aef3        player->_pad_41c = 0
0043aef9        player->_pad_3f0[0x14] = 0
0043aef9        player->_pad_3f0[0x15] = 0
0043aef9        player->_pad_3f0[0x16] = 0
0043aef9        player->_pad_3f0[0x17] = 0
0043af08        player->game->_pad_00[1] = 1
0043af0d        return 0
