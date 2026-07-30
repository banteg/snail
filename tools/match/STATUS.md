# Matching Status

Regenerate with `uv run snail match status --write tools/match/STATUS.md`.

**544/662** port-relevant functions matched, **662/662** port-relevant functions have a scratch, **101084/294937** bytes (**34.27%**) are proof-grade, and overall fuzzy is **82.62%**.

**120** replaceable-platform functions (**22103** curated-extent bytes) and **3** third-party functions (**8104** curated-extent bytes) remain visible for contract, semantic, and extent context but are excluded from port-relevant totals.

## Proof Grade (544)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| ✅ | initialize_array_with_constructor | 0x401000 | 42 | 21/21 | 100.00% | 21/21 | - |  | core |
| ✅ | border_add_text_number | 0x401030 | 167 | 68/68 | 100.00% | 68/68 | - |  | core |
| ✅ | hide_border_init | 0x4010e0 | 39 | 9/9 | 100.00% | 9/9 | 1 ok |  | core |
| ✅ | unhide_border_init | 0x401110 | 23 | 5/5 | 100.00% | 5/5 | - |  | core |
| ✅ | initialize_frontend_sprite_button | 0x401a70 | 699 | 157/157 | 100.00% | 157/157 | 10 ok |  | core |
| ✅ | set_frontend_widget_shortcut_key | 0x402790 | 30 | 6/6 | 100.00% | 6/6 | - |  | core |
| ✅ | stack_widget_below | 0x4027b0 | 48 | 9/9 | 100.00% | 9/9 | 1 ok |  | core |
| ✅ | unhighlight_border | 0x4027e0 | 23 | 4/4 | 100.00% | 4/4 | - |  | core |
| ✅ | highlight_border | 0x402800 | 23 | 4/4 | 100.00% | 4/4 | - |  | core |
| ✅ | allocate_border | 0x4032a0 | 82 | 23/23 | 100.00% | 23/23 | 3 ok |  | core |
| ✅ | activate_all_borders | 0x403300 | 83 | 19/19 | 100.00% | 19/19 | - |  | core |
| ✅ | kill_border | 0x403360 | 90 | 30/30 | 100.00% | 30/30 | - |  | core |
| ✅ | kill_all_borders | 0x4033c0 | 41 | 14/14 | 100.00% | 14/14 | - |  | core |
| ✅ | hide_all_borders | 0x4033f0 | 11 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | unhide_all_borders | 0x403400 | 11 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | border_input_text_init | 0x403410 | 184 | 46/46 | 100.00% | 46/46 | 3 ok |  | core |
| ✅ | update_input_ok | 0x4034d0 | 137 | 32/32 | 100.00% | 32/32 | - |  | core |
| ✅ | initialize_input_ok | 0x403560 | 67 | 23/23 | 100.00% | 23/23 | 5 ok |  | core |
| ✅ | reset_tooltip | 0x403be0 | 51 | 16/16 | 100.00% | 16/16 | 2 ok |  | core |
| ✅ | update_tooltip | 0x403c20 | 821 | 218/218 | 100.00% | 218/218 | 23 ok |  | core |
| ✅ | queue_frontend_widget_flag_after_delay | 0x403f60 | 93 | 22/22 | 100.00% | 22/22 | 2 ok |  | core |
| ✅ | update_border_manager | 0x403fc0 | 111 | 28/28 | 100.00% | 28/28 | 2 ok |  | core |
| ✅ | update_twinkle_manager | 0x404030 | 53 | 23/23 | 100.00% | 23/23 | 1 ok |  | core |
| ✅ | draw_twinkle | 0x404070 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  | core |
| ✅ | update_twinkle | 0x404080 | 709 | 181/181 | 100.00% | 181/181 | 48 ok |  | core |
| ✅ | initialize_border_stack | 0x404350 | 14 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | apply_all_border_visibility_mode | 0x404360 | 472 | 137/137 | 100.00% | 137/137 | 1 ok |  | core |
| ✅ | border_sprite_extend | 0x404540 | 55 | 14/14 | 100.00% | 14/14 | - |  | core |
| ✅ | set_border_justify_centre | 0x404730 | 13 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | initialize_cheat | 0x404740 | 11 | 5/5 | 100.00% | 5/5 | - |  | core |
| ✅ | update_cheat | 0x404750 | 124 | 52/52 | 100.00% | 52/52 | 7 ok |  | core |
| ✅ | match_cheat_text | 0x4047d0 | 85 | 42/42 | 100.00% | 42/42 | 2 ok |  | core |
| ✅ | flush_row_event_display | 0x404830 | 233 | 67/67 | 100.00% | 67/67 | 19 ok |  | core |
| ✅ | update_row_event_display | 0x404cf0 | 836 | 213/213 | 100.00% | 213/213 | 38 ok |  | core |
| ✅ | register_parcel_delivery | 0x405040 | 114 | 36/36 | 100.00% | 36/36 | 10 ok |  | core |
| ✅ | file_exists | 0x405140 | 37 | 14/14 | 100.00% | 14/14 | 3 ok |  | boundary |
| ✅ | get_stream_length_preserve_position | 0x405170 | 51 | 24/24 | 100.00% | 24/24 | 4 ok |  | boundary |
| ✅ | load_file_bytes_allocating | 0x4051b0 | 21 | 8/8 | 100.00% | 8/8 | 1 ok |  | boundary |
| ✅ | load_file_bytes_into_optional_buffer | 0x4051d0 | 158 | 56/56 | 100.00% | 56/56 | 9 ok | msvc6.5 /O2 /G5 /W3 /TC | boundary |
| ✅ | load_x_mesh | 0x405640 | 1603 | 492/492 | 100.00% | 492/492 | 94 ok |  | boundary |
| ✅ | initialize_directx_loader | 0x405c90 | 45 | 13/13 | 100.00% | 13/13 | 3 ok |  | boundary |
| ✅ | load_or_reuse_cached_x_mesh | 0x405cc0 | 157 | 65/65 | 100.00% | 65/65 | 6 ok |  | boundary |
| ✅ | load_x_animation_clip | 0x405d60 | 754 | 228/228 | 100.00% | 228/228 | 50 ok |  | boundary |
| ✅ | destroy_completion_screen | 0x406060 | 98 | 25/25 | 100.00% | 25/25 | 9 ok |  | core |
| ✅ | initialize_exit_prompt | 0x4060d0 | 1804 | 441/441 | 100.00% | 441/441 | 109 ok |  | core |
| ✅ | update_completion_screen | 0x4067e0 | 984 | 207/207 | 100.00% | 207/207 | 69 ok |  | core |
| ✅ | initialize_global_noop_renderable_bods_thunk | 0x406bc0 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_noop_renderable_bods | 0x406bd0 | 61 | 10/10 | 100.00% | 10/10 | 9 ok |  | core |
| ✅ | initialize_default_runtime_config_thunk | 0x406c10 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_default_runtime_config | 0x406c20 | 231 | 36/36 | 100.00% | 36/36 | 32 ok |  | core |
| ✅ | initialize_global_trivial_object_thunk | 0x406d10 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_trivial_object | 0x406d20 | 10 | 2/2 | 100.00% | 2/2 | 2 ok |  | core |
| ✅ | initialize_main_loop_display_state | 0x406d70 | 37 | 8/8 | 100.00% | 8/8 | 7 ok |  | boundary |
| ✅ | initialize_main_loop_timing_state | 0x406da0 | 31 | 4/4 | 100.00% | 4/4 | 3 ok |  | core |
| ✅ | consume_mouse_wheel_delta | 0x4077f0 | 23 | 4/4 | 100.00% | 4/4 | 2 ok |  | boundary |
| ✅ | read_left_mouse_button_state | 0x407810 | 18 | 4/4 | 100.00% | 4/4 | 2 ok |  | boundary |
| ✅ | read_right_mouse_button_state | 0x407830 | 18 | 4/4 | 100.00% | 4/4 | 2 ok |  | boundary |
| ✅ | noop_runtime_ai | 0x407b50 | 1 | 1/1 | 100.00% | 1/1 | - |  | core |
| ✅ | construct_game_runtime | 0x407b60 | 1169 | 268/268 | 100.00% | 268/268 | 120 ok | msvc6.5 /O2 /G5 /W3 /GX | core |
| ✅ | initialize_game_player | 0x408000 | 61 | 17/17 | 100.00% | 17/17 | 6 ok |  | core |
| ✅ | initialize_noop_renderable_bod | 0x408040 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_runtime_pools_and_path_template_bank | 0x408060 | 932 | 227/227 | 100.00% | 227/227 | 72 ok |  | core |
| ✅ | initialize_border_record | 0x408410 | 92 | 21/21 | 100.00% | 21/21 | 9 ok |  | core |
| ✅ | initialize_cached_x_mesh_slot | 0x408470 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_intro_logo_renderable | 0x408490 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_track_speedup_runtime | 0x4084b0 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_track_jetpack_pickup_runtime | 0x4084d0 | 55 | 17/17 | 100.00% | 17/17 | 6 ok |  | core |
| ✅ | initialize_track_health_pickup_runtime | 0x408510 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_slug_hazard_runtime | 0x408530 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_garbage_hazard | 0x408550 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_track_ring_or_special_effect_runtime | 0x408570 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_track_row_runtime | 0x408590 | 36 | 13/13 | 100.00% | 13/13 | 3 ok |  | core |
| ✅ | initialize_path_template_record_pair | 0x4085c0 | 26 | 9/9 | 100.00% | 9/9 | 3 ok |  | core |
| ✅ | initialize_active_bod | 0x4085e0 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | noop_runtime_slot_constructor | 0x408600 | 3 | 2/2 | 100.00% | 2/2 | - |  | core |
| ✅ | initialize_sub_lazer_runtime | 0x408610 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_salt_hazard_runtime | 0x408630 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_fringe_object | 0x408650 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_click_start_controller_runtime | 0x408670 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_golb_shot | 0x408690 | 58 | 17/17 | 100.00% | 17/17 | 6 ok |  | core |
| ✅ | initialize_player_presentation_controller | 0x4086d0 | 322 | 79/79 | 100.00% | 79/79 | 27 ok |  | core |
| ✅ | initialize_active_landscape_entry | 0x408820 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_landscape_script_record | 0x408840 | 18 | 7/7 | 100.00% | 7/7 | 1 ok |  | core |
| ✅ | initialize_track_parcel_runtime | 0x408860 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_galaxy_route_name_record | 0x408880 | 18 | 7/7 | 100.00% | 7/7 | 1 ok |  | core |
| ✅ | initialize_sub_loc | 0x4088c0 | 29 | 10/10 | 100.00% | 10/10 | 4 ok |  | core |
| ✅ | destroy_galaxy | 0x408c10 | 218 | 49/49 | 100.00% | 49/49 | 18 ok |  | core |
| ✅ | initialize_galaxy | 0x408cf0 | 1523 | 338/338 | 100.00% | 338/338 | 74 ok |  | core |
| ✅ | draw_galaxy_line | 0x409b00 | 206 | 67/67 | 100.00% | 67/67 | 4 ok |  | core |
| ✅ | update_galaxy_route_record | 0x409bd0 | 19 | 6/6 | 100.00% | 6/6 | 1 ok |  | core |
| ✅ | close_galaxy_route | 0x409bf0 | 88 | 18/18 | 100.00% | 18/18 | 6 ok |  | core |
| ✅ | open_galaxy_route | 0x409c50 | 1128 | 266/266 | 100.00% | 266/266 | 41 ok |  | core |
| ✅ | galaxy_border_bound | 0x40a0c0 | 225 | 63/63 | 100.00% | 63/63 | 2 ok |  | core |
| ✅ | update_overlay | 0x40a1b0 | 136 | 42/42 | 100.00% | 42/42 | 7 ok |  | core |
| ✅ | initialize_overlay | 0x40a240 | 70 | 17/17 | 100.00% | 17/17 | 3 ok |  | core |
| ✅ | noop_runtime_callback | 0x40a290 | 3 | 1/1 | 100.00% | 1/1 | - |  | core |
| ✅ | run_frame_update | 0x40a2a0 | 485 | 135/135 | 100.00% | 135/135 | 23 ok |  | core |
| ✅ | initialize_input | 0x40aa50 | 45 | 12/12 | 100.00% | 12/12 | - |  | boundary |
| ✅ | update_game_input | 0x40aab0 | 71 | 30/30 | 100.00% | 30/30 | 3 ok |  | boundary |
| ✅ | initialize_frontend_overlay_color_lerp | 0x40ab00 | 63 | 18/18 | 100.00% | 18/18 | 2 ok |  | core |
| ✅ | draw_frontend_overlay_color_lerp | 0x40ab40 | 122 | 38/38 | 100.00% | 38/38 | 6 ok |  | core |
| ✅ | begin_frontend_fade_out | 0x40abc0 | 23 | 5/5 | 100.00% | 5/5 | - |  | core |
| ✅ | begin_frontend_fade_in | 0x40abe0 | 14 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | update_frontend_transition_overlay | 0x40abf0 | 248 | 62/62 | 100.00% | 62/62 | 9 ok |  | core |
| ✅ | zero_vector3 | 0x410710 | 11 | 5/5 | 100.00% | 5/5 | - |  | core |
| ✅ | initialize_game_last | 0x410720 | 14 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | update_frontend_state_machine | 0x4107d0 | 1064 | 180/180 | 100.00% | 180/180 | 69 ok |  | core |
| ✅ | initialize_global_color4f_bank_32_thunk | 0x410c00 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_color4f_bank_32 | 0x410c10 | 28 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | set_backdrop_zoom | 0x410c30 | 13 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | set_backdrop_distort | 0x410c40 | 261 | 73/73 | 100.00% | 73/73 | 14 ok |  | core |
| ✅ | change_backdrop | 0x410d50 | 111 | 34/34 | 100.00% | 34/34 | - |  | core |
| ✅ | change_backdrop_real | 0x410dc0 | 87 | 30/30 | 100.00% | 30/30 | 1 ok |  | core |
| ✅ | initialize_backdrop | 0x410e20 | 279 | 55/55 | 100.00% | 55/55 | 4 ok |  | core |
| ✅ | set_backdrop_texture_target | 0x410f40 | 79 | 14/14 | 100.00% | 14/14 | 2 ok |  | core |
| ✅ | draw_split_backdrop | 0x410f90 | 172 | 50/50 | 100.00% | 50/50 | 4 ok |  | core |
| ✅ | add_bod_to_front | 0x4113b0 | 105 | 33/33 | 100.00% | 33/33 | 2 ok |  | core |
| ✅ | append_bod_to_end | 0x411420 | 129 | 33/33 | 100.00% | 33/33 | 2 ok |  | core |
| ✅ | render_camera | 0x411fa0 | 685 | 180/180 | 100.00% | 180/180 | 37 ok |  | boundary |
| ✅ | render_object_toon | 0x4123e0 | 721 | 219/219 | 100.00% | 219/219 | 31 ok |  | boundary |
| ✅ | render_object | 0x4126c0 | 640 | 196/196 | 100.00% | 196/196 | 25 ok |  | boundary |
| ✅ | set_cull_mode | 0x4129f0 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  | boundary |
| ✅ | load_registered_texture_refs | 0x412a00 | 108 | 35/35 | 100.00% | 35/35 | 11 ok |  | boundary |
| ✅ | load_registered_texture_ref | 0x412a70 | 647 | 216/216 | 100.00% | 216/216 | 47 ok |  | boundary |
| ✅ | draw_sprite_quad | 0x4137f0 | 951 | 259/259 | 100.00% | 259/259 | 29 ok |  | boundary |
| ✅ | build_object_texture_group_buffers | 0x413d50 | 1149 | 373/373 | 100.00% | 373/373 | 29 ok |  | boundary |
| ✅ | set_object_color | 0x4141d0 | 139 | 47/47 | 100.00% | 47/47 | 3 ok |  | boundary |
| ✅ | set_fullscreen_mode | 0x414260 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  | boundary |
| ✅ | bind_texture_ref | 0x414500 | 178 | 62/62 | 100.00% | 62/62 | 11 ok |  | boundary |
| ✅ | replace_object_group_texture_refs | 0x4145c0 | 63 | 26/26 | 100.00% | 26/26 | - |  | boundary |
| ✅ | reset_render_counters | 0x414650 | 18 | 5/5 | 100.00% | 5/5 | 3 ok |  | boundary |
| ✅ | kill_golb | 0x414670 | 418 | 132/132 | 100.00% | 132/132 | 16 ok |  | core |
| ✅ | spawn_golb_trail_sprite | 0x415bb0 | 161 | 47/47 | 100.00% | 47/47 | 2 ok |  | core |
| ✅ | spawn_golb_smoke | 0x415c60 | 278 | 72/72 | 100.00% | 72/72 | 8 ok |  | core |
| ✅ | initialize_enemy_manager | 0x415e20 | 7 | 2/2 | 100.00% | 2/2 | - |  | core |
| ✅ | search_path_for_golb | 0x415e30 | 192 | 63/63 | 100.00% | 63/63 | 3 ok |  | core |
| ✅ | append_subgame_contact_target | 0x415ef0 | 88 | 34/34 | 100.00% | 34/34 | - |  | core |
| ✅ | initialize_challenge_setup_screen | 0x415f50 | 662 | 167/167 | 100.00% | 167/167 | 37 ok |  | core |
| ✅ | destroy_challenge_setup_screen | 0x4161f0 | 370 | 96/96 | 100.00% | 96/96 | 32 ok |  | core |
| ✅ | update_challenge_setup_screen | 0x416370 | 1166 | 355/355 | 100.00% | 355/355 | 38 ok |  | core |
| ✅ | initialize_help_screen | 0x416800 | 181 | 47/47 | 100.00% | 47/47 | 15 ok |  | core |
| ✅ | destroy_help_screen | 0x4168c0 | 16 | 3/3 | 100.00% | 3/3 | 2 ok |  | core |
| ✅ | update_help_screen | 0x4168d0 | 54 | 12/12 | 100.00% | 12/12 | 3 ok |  | core |
| ✅ | destroy_high_score_screen | 0x417220 | 52 | 11/11 | 100.00% | 11/11 | 5 ok |  | core |
| ✅ | update_high_score_screen | 0x417260 | 731 | 205/205 | 100.00% | 205/205 | 40 ok |  | core |
| ✅ | initialize_high_score_tables | 0x417540 | 155 | 58/58 | 100.00% | 58/58 | 4 ok |  | core |
| ✅ | load_high_scores_from_file | 0x4175e0 | 184 | 71/71 | 100.00% | 71/71 | 4 ok |  | core |
| ✅ | add_arcade_high_score | 0x4176a0 | 222 | 70/70 | 100.00% | 70/70 | 4 ok |  | core |
| ✅ | add_survival_high_score | 0x417780 | 289 | 84/84 | 100.00% | 84/84 | 6 ok |  | core |
| ✅ | save_high_scores_and_config | 0x417940 | 297 | 101/101 | 100.00% | 101/101 | 19 ok |  | core |
| ✅ | initialize_high_score_entry | 0x417a70 | 120 | 40/40 | 100.00% | 40/40 | 3 ok |  | core |
| ✅ | exit_high_score_screen | 0x417b50 | 104 | 23/23 | 100.00% | 23/23 | 6 ok |  | core |
| ✅ | initialize_new_game_menu | 0x417bc0 | 739 | 182/182 | 100.00% | 182/182 | 48 ok |  | core |
| ✅ | update_new_game_menu | 0x417eb0 | 1064 | 273/273 | 100.00% | 273/273 | 62 ok |  | core |
| ✅ | reset_landscape_manager | 0x4182e0 | 11 | 2/2 | 100.00% | 2/2 | - |  | core |
| ✅ | load_landscape_script_by_name | 0x4182f0 | 1404 | 386/386 | 100.00% | 386/386 | 63 ok |  | core |
| ✅ | activate_landscape_entry | 0x418870 | 442 | 123/123 | 100.00% | 123/123 | 20 ok |  | core |
| ✅ | clear_active_landscape_entries | 0x418a30 | 141 | 49/49 | 100.00% | 49/49 | 5 ok |  | core |
| ✅ | update_active_landscape_entry | 0x418ac0 | 130 | 41/41 | 100.00% | 41/41 | 4 ok |  | core |
| ✅ | destroy_loading_screen | 0x418e50 | 41 | 15/15 | 100.00% | 15/15 | 3 ok |  | core |
| ✅ | update_loading_screen | 0x418e80 | 656 | 204/204 | 100.00% | 204/204 | 26 ok |  | core |
| ✅ | open_logo | 0x419110 | 195 | 60/60 | 100.00% | 60/60 | 13 ok |  | core |
| ✅ | destroy_intro_screen | 0x419920 | 184 | 61/61 | 100.00% | 61/61 | 7 ok |  | core |
| ✅ | update_intro_screen | 0x4199e0 | 161 | 51/51 | 100.00% | 51/51 | 11 ok |  | core |
| ✅ | update_intro_logo_renderable | 0x419a90 | 148 | 42/42 | 100.00% | 42/42 | 7 ok |  | core |
| ✅ | destroy_main_menu | 0x419b30 | 26 | 5/5 | 100.00% | 5/5 | 4 ok |  | core |
| ✅ | initialize_main_menu | 0x419b50 | 682 | 172/172 | 100.00% | 172/172 | 48 ok |  | core |
| ✅ | update_main_menu | 0x419e00 | 326 | 68/68 | 100.00% | 68/68 | 16 ok |  | core |
| ✅ | initialize_duplicate_vertices | 0x419f50 | 39 | 13/13 | 100.00% | 13/13 | 2 ok |  | core |
| ✅ | clean_duplicate_vertices | 0x419f80 | 70 | 33/33 | 100.00% | 33/33 | - |  | core |
| ✅ | sort_object_faces_by_texture_group | 0x419fd0 | 203 | 75/75 | 100.00% | 75/75 | - |  | core |
| ✅ | disable_object_rendering | 0x41a0a0 | 12 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | initialize_textured_backdrop_quad | 0x41a0b0 | 181 | 57/57 | 100.00% | 57/57 | 6 ok |  | core |
| ✅ | raise_backdrop_quad_edge_pair | 0x41a170 | 66 | 19/19 | 100.00% | 19/19 | 4 ok |  | core |
| ✅ | initialize_backdrop_slice_quad | 0x41a1c0 | 196 | 61/61 | 100.00% | 61/61 | 7 ok |  | core |
| ✅ | initialize_backdrop_corner_quad | 0x41a290 | 207 | 55/55 | 100.00% | 55/55 | 10 ok |  | core |
| ✅ | initialize_backdrop_tile_quad | 0x41a4d0 | 1368 | 367/367 | 100.00% | 367/367 | 63 ok |  | core |
| ✅ | initialize_object_distort | 0x41aa30 | 17 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | initialize_options_menu | 0x41ace0 | 506 | 127/127 | 100.00% | 127/127 | 32 ok |  | core |
| ✅ | destroy_options_menu | 0x41aee0 | 127 | 32/32 | 100.00% | 32/32 | 13 ok |  | core |
| ✅ | update_options_menu | 0x41af60 | 267 | 73/73 | 100.00% | 73/73 | 19 ok |  | core |
| ✅ | apply_audio_config_volumes | 0x41b070 | 43 | 11/11 | 100.00% | 11/11 | 7 ok |  | boundary |
| ✅ | get_path_nodes | 0x41b0a0 | 72 | 23/23 | 100.00% | 23/23 | 4 ok |  | core |
| ✅ | begin_track_attachment_follow_state | 0x420c40 | 98 | 27/27 | 100.00% | 27/27 | 4 ok |  | core |
| ✅ | initialize_path_follow_golb | 0x421770 | 58 | 16/16 | 100.00% | 16/16 | 1 ok |  | core |
| ✅ | mirror_path | 0x421dc0 | 1058 | 314/314 | 100.00% | 314/314 | 15 ok |  | core |
| ✅ | find_segment_path_index_by_name | 0x429ae0 | 59 | 27/27 | 100.00% | 27/27 | 3 ok |  | core |
| ✅ | compute_kind42_attachment_transform | 0x42b920 | 146 | 48/48 | 100.00% | 48/48 | 8 ok |  | core |
| ✅ | get_path_position_at_node | 0x42b9c0 | 185 | 56/56 | 100.00% | 56/56 | - |  | core |
| ✅ | calc_path_length_z | 0x42c600 | 363 | 113/113 | 100.00% | 113/113 | 9 ok |  | core |
| ✅ | is_point_inside_track_attachment | 0x42ca90 | 348 | 111/111 | 100.00% | 111/111 | 6 ok |  | core |
| ✅ | load_config_file | 0x42f470 | 23 | 9/9 | 100.00% | 9/9 | 1 ok |  | core |
| ✅ | load_file_bytes_from_path | 0x42f490 | 169 | 59/59 | 100.00% | 59/59 | 9 ok | msvc6.5 /O2 /G5 /W3 /TC | boundary |
| ✅ | save_config_file | 0x42f540 | 98 | 31/31 | 100.00% | 31/31 | 5 ok |  | boundary |
| ✅ | validate_config_tail_stub | 0x42f5b0 | 3 | 2/2 | 100.00% | 2/2 | - |  | core |
| ✅ | is_bod_after_sprites | 0x42f5c0 | 8 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | set_bod_object | 0x42f5d0 | 18 | 6/6 | 100.00% | 6/6 | - |  | core |
| ✅ | initialize_bod_base | 0x42f5f0 | 87 | 27/27 | 100.00% | 27/27 | 5 ok |  | core |
| ✅ | initialize_renderable_bod | 0x42f650 | 33 | 10/10 | 100.00% | 10/10 | 3 ok |  | core |
| ✅ | apply_bod_position | 0x42f680 | 89 | 39/39 | 100.00% | 39/39 | 1 ok |  | core |
| ✅ | initialize_object_constructor_thunk | 0x42f6e0 | 12 | 6/6 | 100.00% | 6/6 | 1 ok |  | core |
| ✅ | initialize_object | 0x42f6f0 | 24 | 9/9 | 100.00% | 9/9 | - |  | core |
| ✅ | request_object_vertices | 0x42f710 | 114 | 37/37 | 100.00% | 37/37 | 8 ok |  | core |
| ✅ | copy_object_vertices | 0x42f790 | 57 | 28/28 | 100.00% | 28/28 | - |  | core |
| ✅ | request_object_vertices_copy | 0x42f7d0 | 38 | 14/14 | 100.00% | 14/14 | 3 ok |  | core |
| ✅ | request_object_facequad_normals | 0x42f800 | 71 | 26/26 | 100.00% | 26/26 | 4 ok |  | core |
| ✅ | request_object_vertex_colours | 0x42f850 | 77 | 30/30 | 100.00% | 30/30 | 2 ok |  | core |
| ✅ | initialize_global_temp_colour_thunk | 0x42f8a0 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_temp_colour | 0x42f8b0 | 10 | 2/2 | 100.00% | 2/2 | 2 ok |  | core |
| ✅ | request_object_facequads | 0x42f8c0 | 108 | 40/40 | 100.00% | 40/40 | 5 ok |  | core |
| ✅ | request_object_texture_groups | 0x42f930 | 82 | 29/29 | 100.00% | 29/29 | 4 ok |  | core |
| ✅ | initialize_object_list | 0x42f990 | 80 | 30/30 | 100.00% | 30/30 | 3 ok |  | core |
| ✅ | build_all_objects | 0x42f9e0 | 146 | 54/54 | 100.00% | 54/54 | 8 ok |  | core |
| ✅ | apply_object_toon | 0x42fa80 | 73 | 24/24 | 100.00% | 24/24 | 4 ok |  | core |
| ✅ | add_object_to_list | 0x42fad0 | 58 | 24/24 | 100.00% | 24/24 | 3 ok |  | core |
| ✅ | calc_object_facequad_normals_simple | 0x430230 | 441 | 139/139 | 100.00% | 139/139 | 5 ok |  | core |
| ✅ | advance_frame_sequence | 0x430470 | 245 | 65/65 | 100.00% | 65/65 | 2 ok |  | core |
| ✅ | request_object_edges | 0x430570 | 44 | 16/16 | 100.00% | 16/16 | 2 ok |  | core |
| ✅ | rotate_object_facequad_uv_pairs | 0x430a30 | 49 | 17/17 | 100.00% | 17/17 | - |  | core |
| ✅ | request_object_animation | 0x430a70 | 793 | 231/231 | 100.00% | 231/231 | 17 ok |  | core |
| ✅ | copy_c_string | 0x431da0 | 21 | 10/10 | 100.00% | 10/10 | - |  | core |
| ✅ | strings_equal_case_insensitive | 0x431dc0 | 104 | 50/50 | 100.00% | 50/50 | - |  | core |
| ✅ | skip_to_next_line | 0x431e30 | 29 | 13/13 | 100.00% | 13/13 | - |  | core |
| ✅ | append_c_string | 0x431e50 | 42 | 19/19 | 100.00% | 19/19 | - |  | core |
| ✅ | parse_next_space_delimited_token | 0x431e80 | 60 | 27/27 | 100.00% | 27/27 | - |  | core |
| ✅ | parse_next_int32 | 0x431ec0 | 89 | 39/39 | 100.00% | 39/39 | - |  | core |
| ✅ | parse_next_float32 | 0x431f20 | 173 | 64/64 | 100.00% | 64/64 | 9 ok |  | core |
| ✅ | set_input_controller_slot0_button_axes | 0x431fd0 | 30 | 7/7 | 100.00% | 7/7 | 3 ok |  | boundary |
| ✅ | update_input_controller_slot_button_axes | 0x431ff0 | 247 | 61/61 | 100.00% | 61/61 | 25 ok |  | boundary |
| ✅ | copy_active_input_controller_state | 0x4320f0 | 198 | 52/52 | 100.00% | 52/52 | 16 ok |  | boundary |
| ✅ | set_input_controller_pointer_authored_xy | 0x4323a0 | 152 | 40/40 | 100.00% | 40/40 | 11 ok |  | boundary |
| ✅ | read_pressed_text_input_key_code | 0x432440 | 915 | 338/338 | 100.00% | 338/338 | 55 ok |  | boundary |
| ✅ | register_font_texture_sheet_wrapper | 0x432d20 | 29 | 11/11 | 100.00% | 11/11 | 1 ok |  | core |
| ✅ | reset_registered_sound_sample_count | 0x432d40 | 11 | 2/2 | 100.00% | 2/2 | 1 ok |  | boundary |
| ✅ | cache_music_file | 0x432d50 | 118 | 42/42 | 100.00% | 42/42 | 11 ok |  | boundary |
| ✅ | play_registered_warning_sample | 0x432dd0 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  | boundary |
| ✅ | stop_registered_warning_sample | 0x432de0 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  | boundary |
| ✅ | play_sound_effect_backend | 0x432df0 | 136 | 42/42 | 100.00% | 42/42 | 11 ok |  | boundary |
| ✅ | play_voice_backend | 0x432e80 | 136 | 42/42 | 100.00% | 42/42 | 11 ok |  | boundary |
| ✅ | register_sound_sample | 0x432f10 | 171 | 51/51 | 100.00% | 51/51 | 19 ok |  | boundary |
| ✅ | find_registered_sound_sample_id_by_name | 0x432fc0 | 79 | 34/34 | 100.00% | 34/34 | 6 ok |  | boundary |
| ✅ | xor_decode_buffer_with_index | 0x433010 | 29 | 15/15 | 100.00% | 15/15 | - |  | core |
| ✅ | get_authored_view_width | 0x433030 | 7 | 2/2 | 100.00% | 2/2 | 1 ok |  | core |
| ✅ | get_authored_view_height | 0x433040 | 7 | 2/2 | 100.00% | 2/2 | 1 ok |  | core |
| ✅ | add_track_cache_vertex | 0x433830 | 299 | 103/103 | 100.00% | 103/103 | 7 ok |  | core |
| ✅ | update_track_render_cache_rows | 0x433b30 | 848 | 227/227 | 100.00% | 227/227 | 27 ok |  | core |
| ✅ | update_active_bod | 0x433e80 | 147 | 50/50 | 100.00% | 50/50 | 7 ok |  | core |
| ✅ | bind_subgame_owner | 0x433fc0 | 13 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | initialize_thanks_for_playing_screen | 0x433fd0 | 234 | 55/55 | 100.00% | 55/55 | 17 ok |  | core |
| ✅ | uninit_thanks_screen | 0x4340c0 | 38 | 8/8 | 100.00% | 8/8 | 3 ok |  | core |
| ✅ | update_thanks_for_playing_screen | 0x4340f0 | 376 | 88/88 | 100.00% | 88/88 | 19 ok |  | core |
| ✅ | destroy_star_field | 0x434270 | 70 | 28/28 | 100.00% | 28/28 | 1 ok |  | core |
| ✅ | open_star_field | 0x4342c0 | 77 | 26/26 | 100.00% | 26/26 | 4 ok |  | core |
| ✅ | hide_star_field | 0x434670 | 50 | 23/23 | 100.00% | 23/23 | - |  | core |
| ✅ | unhide_star_field | 0x4346b0 | 50 | 23/23 | 100.00% | 23/23 | - |  | core |
| ✅ | update_star_field | 0x4346f0 | 264 | 66/66 | 100.00% | 66/66 | 13 ok |  | core |
| ✅ | update_star_positions | 0x434800 | 378 | 106/106 | 100.00% | 106/106 | 11 ok |  | core |
| ✅ | initialize_track_colour_bank_a_thunk | 0x434980 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_a | 0x434990 | 28 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_banks_b_c_thunk | 0x4349b0 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_banks_b_c | 0x4349c0 | 28 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_d_thunk | 0x4349e0 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_d | 0x4349f0 | 28 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_e_thunk | 0x434a10 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_e | 0x434a20 | 28 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_f_thunk | 0x434a40 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_f | 0x434a50 | 28 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_g_thunk | 0x434a70 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_g | 0x434a80 | 28 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_h_thunk | 0x434aa0 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_h | 0x434ab0 | 28 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_i_thunk | 0x434ad0 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_i | 0x434ae0 | 28 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_j_thunk | 0x434b00 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_j | 0x434b10 | 28 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_k_thunk | 0x434b30 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_k | 0x434b40 | 28 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | is_neighbor_cell_solid | 0x434b60 | 127 | 47/47 | 100.00% | 47/47 | 2 ok |  | core |
| ✅ | harmonize_center_lane_floor_slide_variants | 0x4356f0 | 911 | 226/226 | 100.00% | 226/226 | 28 ok |  | core |
| ✅ | select_track_tile_edge_variants | 0x435a80 | 692 | 220/220 | 100.00% | 220/220 | 18 ok |  | core |
| ✅ | build_track_colours | 0x435d40 | 161 | 37/37 | 100.00% | 37/37 | 24 ok |  | core |
| ✅ | set_subgame_features | 0x435df0 | 76 | 19/19 | 100.00% | 19/19 | 3 ok |  | core |
| ✅ | normalize_segment_glyph_for_track_flags | 0x437270 | 570 | 160/160 | 100.00% | 160/160 | 2 ok |  | core |
| ✅ | initialize_subgame | 0x4374b0 | 1632 | 396/396 | 100.00% | 396/396 | 85 ok |  | core |
| ✅ | reset_subgame | 0x437b10 | 291 | 75/75 | 100.00% | 75/75 | 2 ok |  | core |
| ✅ | update_progress_bar | 0x437c40 | 413 | 110/110 | 100.00% | 110/110 | 19 ok |  | core |
| ✅ | rebuild_track_runtime_from_segments | 0x437de0 | 145 | 44/44 | 100.00% | 44/44 | 13 ok |  | core |
| ✅ | calc_slider_to_rate | 0x437e80 | 45 | 11/11 | 100.00% | 11/11 | 4 ok |  | core |
| ✅ | complete_subgame | 0x438700 | 323 | 88/88 | 100.00% | 88/88 | 8 ok |  | core |
| ✅ | destroy_subgame | 0x438850 | 830 | 246/246 | 100.00% | 246/246 | 41 ok |  | core |
| ✅ | is_sub_loc_floor | 0x439a40 | 33 | 17/17 | 100.00% | 17/17 | - |  | core |
| ✅ | is_sub_loc_ramp | 0x439a70 | 57 | 29/29 | 100.00% | 29/29 | - |  | core |
| ✅ | is_sub_loc_empty | 0x439ab0 | 29 | 15/15 | 100.00% | 15/15 | - |  | core |
| ✅ | is_sub_loc_slide | 0x439ad0 | 41 | 21/21 | 100.00% | 21/21 | - |  | core |
| ✅ | refresh_fringe_object_draw_list | 0x439b00 | 186 | 63/63 | 100.00% | 63/63 | 8 ok |  | core |
| ✅ | update_sub_loc | 0x439d50 | 702 | 187/187 | 100.00% | 187/187 | 39 ok |  | core |
| ✅ | health_collect_particles | 0x43a010 | 386 | 104/104 | 100.00% | 104/104 | 13 ok |  | core |
| ✅ | set_subgoldy_shoot_flags | 0x43a1a0 | 344 | 50/50 | 100.00% | 50/50 | 2 ok |  | core |
| ✅ | shoot_subgoldy | 0x43a300 | 97 | 39/39 | 100.00% | 39/39 | 1 ok |  | core |
| ✅ | end_jetpack_hover | 0x43a370 | 28 | 9/9 | 100.00% | 9/9 | 1 ok |  | core |
| ✅ | uninit_jet_particles | 0x43a580 | 36 | 17/17 | 100.00% | 17/17 | 1 ok |  | core |
| ✅ | initialize_jet_particles | 0x43a5b0 | 214 | 73/73 | 100.00% | 73/73 | 3 ok |  | core |
| ✅ | update_jet_particles | 0x43a690 | 670 | 181/181 | 100.00% | 181/181 | 17 ok |  | core |
| ✅ | initialize_jetpack_gauge | 0x43a930 | 65 | 15/15 | 100.00% | 15/15 | 3 ok |  | core |
| ✅ | arm_jetpack_gauge | 0x43a980 | 55 | 18/18 | 100.00% | 18/18 | 4 ok |  | core |
| ✅ | initialize_subgoldy | 0x43a9c0 | 1360 | 279/279 | 100.00% | 279/279 | 27 ok |  | core |
| ✅ | show_subgoldy_lives | 0x43af10 | 66 | 23/23 | 100.00% | 23/23 | 2 ok |  | core |
| ✅ | begin_post_follow_carryover | 0x43af60 | 97 | 20/20 | 100.00% | 20/20 | - |  | core |
| ✅ | initialize_subgoldy_ghost | 0x43d230 | 413 | 108/108 | 100.00% | 108/108 | 6 ok |  | core |
| ✅ | set_subgoldy_ghost_z | 0x43d3d0 | 62 | 18/18 | 100.00% | 18/18 | - |  | core |
| ✅ | get_track_grid_cell_at_world_position | 0x43d410 | 98 | 34/34 | 100.00% | 34/34 | 3 ok |  | core |
| ✅ | get_track_runtime_cell_at_world_z | 0x43d480 | 73 | 23/23 | 100.00% | 23/23 | 3 ok |  | core |
| ✅ | sample_track_floor_height_at_position | 0x43d4d0 | 197 | 63/63 | 100.00% | 63/63 | 8 ok |  | core |
| ✅ | spawn_garbage_smoke_particle | 0x43d5a0 | 280 | 76/76 | 100.00% | 76/76 | 9 ok |  | core |
| ✅ | spawn_track_speedup | 0x43d880 | 3 | 1/1 | 100.00% | 1/1 | - |  | core |
| ✅ | spawn_track_garbage_hazard | 0x43da80 | 505 | 143/143 | 100.00% | 143/143 | 16 ok |  | core |
| ✅ | spawn_slug_hazard | 0x43dc80 | 642 | 160/160 | 100.00% | 160/160 | 18 ok |  | core |
| ✅ | spawn_track_ring_or_special_effect | 0x43df10 | 1376 | 347/347 | 100.00% | 347/347 | 75 ok |  | core |
| ✅ | initialize_ring_or_special_effect_particles | 0x43e470 | 535 | 153/153 | 100.00% | 153/153 | 10 ok |  | core |
| ✅ | emit_ring_star_shower | 0x43e690 | 236 | 65/65 | 100.00% | 65/65 | 9 ok |  | core |
| ✅ | update_ring_or_special_effect_parent | 0x43e830 | 1156 | 336/336 | 100.00% | 336/336 | 38 ok |  | core |
| ✅ | update_track_health_pickup | 0x43ecc0 | 390 | 128/128 | 100.00% | 128/128 | 21 ok |  | core |
| ✅ | update_track_speedup | 0x43ee50 | 340 | 103/103 | 100.00% | 103/103 | 15 ok |  | core |
| ✅ | update_track_jetpack_pickup | 0x43efb0 | 384 | 127/127 | 100.00% | 127/127 | 20 ok |  | core |
| ✅ | destroy_garbage_hazard | 0x43f130 | 205 | 62/62 | 100.00% | 62/62 | 6 ok |  | core |
| ✅ | update_garbage_hazard | 0x43f200 | 777 | 217/217 | 100.00% | 217/217 | 22 ok |  | core |
| ✅ | update_slug_voice_ai | 0x43f520 | 56 | 14/14 | 100.00% | 14/14 | 1 ok |  | core |
| ✅ | play_slug_voice | 0x43f560 | 95 | 22/22 | 100.00% | 22/22 | 3 ok |  | core |
| ✅ | initialize_slug_voice_manager | 0x43f5c0 | 18 | 4/4 | 100.00% | 4/4 | - |  | core |
| ✅ | update_slug_voice_manager | 0x43f5e0 | 49 | 15/15 | 100.00% | 15/15 | 2 ok |  | core |
| ✅ | hit_slug_hazard | 0x43f620 | 94 | 25/25 | 100.00% | 25/25 | 5 ok |  | core |
| ✅ | kill_slug_hazard | 0x43f8b0 | 128 | 35/35 | 100.00% | 35/35 | 7 ok |  | core |
| ✅ | update_slug_hazard_ai | 0x43f930 | 1772 | 464/464 | 100.00% | 464/464 | 71 ok |  | core |
| ✅ | deserialize_compact_high_score_record | 0x440020 | 335 | 114/114 | 100.00% | 114/114 | 1 ok |  | core |
| ✅ | serialize_compact_high_score_record | 0x440170 | 326 | 109/109 | 100.00% | 109/109 | 1 ok |  | core |
| ✅ | add_subgoldy_score | 0x4402c0 | 190 | 58/58 | 100.00% | 58/58 | 6 ok |  | core |
| ✅ | clear_subgoldy_score_buckets | 0x4403a0 | 18 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | display_score_stats | 0x4403c0 | 241 | 67/67 | 100.00% | 67/67 | 16 ok |  | core |
| ✅ | set_subgame_rate | 0x4404c0 | 15 | 5/5 | 100.00% | 5/5 | - |  | core |
| ✅ | calc_subgame_rate | 0x4404d0 | 297 | 84/84 | 100.00% | 84/84 | 16 ok |  | core |
| ✅ | uninit_pause_menu | 0x440600 | 82 | 22/22 | 100.00% | 22/22 | 8 ok |  | core |
| ✅ | initialize_pause_menu | 0x440660 | 316 | 88/88 | 100.00% | 88/88 | 23 ok |  | core |
| ✅ | update_pause_menu | 0x4407a0 | 249 | 55/55 | 100.00% | 55/55 | 10 ok |  | core |
| ✅ | advance_blink_random | 0x4408a0 | 31 | 10/10 | 100.00% | 10/10 | - |  | core |
| ✅ | initialize_blink_random | 0x4408c0 | 74 | 21/21 | 100.00% | 21/21 | 5 ok |  | core |
| ✅ | update_barrier_ai | 0x440f80 | 17 | 5/5 | 100.00% | 5/5 | - |  | core |
| ✅ | initialize_damage_gauge | 0x440fa0 | 40 | 12/12 | 100.00% | 12/12 | - |  | core |
| ✅ | apply_damage_gauge_delta | 0x4413f0 | 322 | 94/94 | 100.00% | 94/94 | 24 ok |  | core |
| ✅ | initialize_salt_hazard_pool | 0x441540 | 26 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | spawn_salt_hazard | 0x441560 | 236 | 67/67 | 100.00% | 67/67 | 10 ok |  | core |
| ✅ | initialize_sub_lazer_pool | 0x441650 | 26 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | spawn_sub_lazer_projectile | 0x441670 | 195 | 63/63 | 100.00% | 63/63 | 6 ok |  | core |
| ✅ | deactivate_sub_lazer_projectile | 0x441740 | 140 | 43/43 | 100.00% | 43/43 | 5 ok |  | core |
| ✅ | shoot_sub_lazer_pool | 0x441ad0 | 154 | 48/48 | 100.00% | 48/48 | 4 ok |  | core |
| ✅ | zero_timer_counters | 0x441b70 | 20 | 8/8 | 100.00% | 8/8 | - |  | core |
| ✅ | advance_timer_counters | 0x441b90 | 116 | 38/38 | 100.00% | 38/38 | 7 ok |  | core |
| ✅ | update_salt_hazard | 0x441c10 | 301 | 83/83 | 100.00% | 83/83 | 12 ok |  | core |
| ✅ | update_banner | 0x441d40 | 129 | 44/44 | 100.00% | 44/44 | 7 ok |  | core |
| ✅ | update_smtracks | 0x441f60 | 56 | 19/19 | 100.00% | 19/19 | 2 ok |  | core |
| ✅ | initialize_subgoldy_resurrect | 0x441fa0 | 40 | 6/6 | 100.00% | 6/6 | - |  | core |
| ✅ | update_subgoldy_resurrect | 0x441fd0 | 332 | 76/76 | 100.00% | 76/76 | 13 ok |  | core |
| ✅ | get_track_skirt_color | 0x442120 | 76 | 25/25 | 100.00% | 25/25 | 1 ok |  | core |
| ✅ | initialize_click_start | 0x442170 | 277 | 79/79 | 100.00% | 79/79 | 13 ok |  | core |
| ✅ | update_click_start | 0x442290 | 624 | 138/138 | 100.00% | 138/138 | 24 ok |  | core |
| ✅ | initialize_vapour | 0x442500 | 62 | 19/19 | 100.00% | 19/19 | 3 ok |  | core |
| ✅ | reset_vapour | 0x442540 | 31 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | add_vapour_point | 0x442560 | 141 | 47/47 | 100.00% | 47/47 | - |  | core |
| ✅ | update_vapour | 0x4425f0 | 726 | 227/227 | 100.00% | 227/227 | - |  | core |
| ✅ | update_snail_presentation | 0x4428d0 | 1385 | 339/339 | 100.00% | 339/339 | 44 ok |  | core |
| ✅ | update_row_model | 0x443070 | 186 | 60/60 | 100.00% | 60/60 | 6 ok |  | core |
| ✅ | update_track_parcels | 0x443130 | 34 | 16/16 | 100.00% | 16/16 | - |  | core |
| ✅ | initialize_track_parcel_slots | 0x443160 | 38 | 13/13 | 100.00% | 13/13 | 1 ok |  | core |
| ✅ | allocate_track_parcel_slot | 0x443190 | 54 | 18/18 | 100.00% | 18/18 | 2 ok |  | core |
| ✅ | update_track_parcel | 0x4431d0 | 1148 | 312/312 | 100.00% | 312/312 | 35 ok |  | core |
| ✅ | spawn_track_parcel | 0x443730 | 292 | 96/96 | 100.00% | 96/96 | 5 ok |  | core |
| ✅ | initialize_parcel_set_bucket_pool_thunk | 0x443860 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_parcel_set_bucket_pool | 0x443870 | 39 | 15/15 | 100.00% | 15/15 | 3 ok |  | core |
| ✅ | initialize_zero_parcel_bucket_pool_thunk | 0x4438a0 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_zero_parcel_bucket_pool | 0x4438b0 | 39 | 15/15 | 100.00% | 15/15 | 3 ok |  | core |
| ✅ | project_position_onto_track_attachment | 0x4444b0 | 333 | 106/106 | 100.00% | 106/106 | 5 ok |  | core |
| ✅ | initialize_anim_manager | 0x4447c0 | 14 | 6/6 | 100.00% | 6/6 | - |  | core |
| ✅ | update_anim_manager | 0x4447d0 | 399 | 134/134 | 100.00% | 134/134 | 13 ok |  | core |
| ✅ | initialize_squidge | 0x444960 | 20 | 8/8 | 100.00% | 8/8 | - |  | core |
| ✅ | start_squidge_y | 0x444980 | 23 | 5/5 | 100.00% | 5/5 | 1 ok |  | core |
| ✅ | start_squidge_z | 0x4449a0 | 23 | 6/6 | 100.00% | 6/6 | 1 ok |  | core |
| ✅ | update_squidge | 0x4449c0 | 253 | 80/80 | 100.00% | 80/80 | 14 ok |  | core |
| ✅ | initialize_invincible_shell | 0x444ac0 | 31 | 7/7 | 100.00% | 7/7 | 3 ok |  | core |
| ✅ | start_invincible_shell | 0x444ae0 | 97 | 21/21 | 100.00% | 21/21 | 4 ok |  | core |
| ✅ | update_invincible_shell | 0x444b50 | 416 | 98/98 | 100.00% | 98/98 | 28 ok |  | core |
| ✅ | kill_subgoldy | 0x445840 | 17 | 6/6 | 100.00% | 6/6 | 1 ok |  | core |
| ✅ | build_snail_world_hotspots | 0x445cd0 | 128 | 44/44 | 100.00% | 44/44 | 1 ok |  | core |
| ✅ | update_times_up | 0x445e20 | 75 | 26/26 | 100.00% | 26/26 | 5 ok |  | core |
| ✅ | uninit_times_up | 0x445e70 | 27 | 8/8 | 100.00% | 8/8 | 2 ok |  | core |
| ✅ | show_times_up_message | 0x445e90 | 116 | 31/31 | 100.00% | 31/31 | 6 ok |  | core |
| ✅ | hide_gameplay_scores | 0x445f10 | 35 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | unhide_gameplay_scores | 0x445f40 | 27 | 8/8 | 100.00% | 8/8 | 2 ok |  | core |
| ✅ | initialize_snail_skin | 0x445f60 | 27 | 6/6 | 100.00% | 6/6 | 2 ok |  | core |
| ✅ | update_snail_skin_transition | 0x445f80 | 69 | 25/25 | 100.00% | 25/25 | 1 ok |  | core |
| ✅ | change_snail_skin | 0x445fd0 | 69 | 19/19 | 100.00% | 19/19 | 3 ok |  | core |
| ✅ | update_subgame_camera | 0x446020 | 269 | 70/70 | 100.00% | 70/70 | 9 ok |  | core |
| ✅ | initialize_cutscene_ai | 0x446130 | 35 | 8/8 | 100.00% | 8/8 | 4 ok |  | core |
| ✅ | initialize_cameraman | 0x446160 | 102 | 20/20 | 100.00% | 20/20 | 6 ok |  | core |
| ✅ | initialize_subgoldy_death | 0x446e30 | 47 | 14/14 | 100.00% | 14/14 | 3 ok |  | core |
| ✅ | initialize_warning | 0x446e80 | 130 | 32/32 | 100.00% | 32/32 | 6 ok |  | core |
| ✅ | uninit_warning | 0x446f10 | 22 | 6/6 | 100.00% | 6/6 | 2 ok |  | core |
| ✅ | start_warning | 0x446f30 | 21 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | stop_warning | 0x446f50 | 14 | 3/3 | 100.00% | 3/3 | 1 ok |  | core |
| ✅ | stop_warning_sample | 0x446f60 | 24 | 7/7 | 100.00% | 7/7 | 4 ok |  | core |
| ✅ | update_warning | 0x446f80 | 179 | 52/52 | 100.00% | 52/52 | 7 ok |  | core |
| ✅ | get_track_cell_row_index | 0x447040 | 65 | 22/22 | 100.00% | 22/22 | 2 ok |  | core |
| ✅ | initialize_fringe_manager | 0x447090 | 11 | 2/2 | 100.00% | 2/2 | - |  | core |
| ✅ | allocate_fringe_object | 0x4470a0 | 50 | 14/14 | 100.00% | 14/14 | 2 ok |  | core |
| ✅ | uninit_nuke | 0x4470e0 | 41 | 18/18 | 100.00% | 18/18 | 1 ok |  | core |
| ✅ | update_nuke | 0x4471e0 | 169 | 59/59 | 100.00% | 59/59 | 8 ok |  | core |
| ✅ | recycle_bod_to_free_list | 0x447290 | 106 | 36/36 | 100.00% | 36/36 | 4 ok |  | core |
| ✅ | copy_segment_definition_to_level_slot | 0x447300 | 379 | 125/125 | 100.00% | 125/125 | 5 ok |  | core |
| ✅ | load_level_definitions | 0x448900 | 96 | 30/30 | 100.00% | 30/30 | 6 ok |  | core |
| ✅ | format_time_trial_string | 0x448960 | 113 | 36/36 | 100.00% | 36/36 | 12 ok | msvc6.5 /O2 /G5 /W3 /TC | core |
| ✅ | kill_tip_widgets | 0x4489e0 | 81 | 24/24 | 100.00% | 24/24 | 6 ok |  | core |
| ✅ | update_tip | 0x448c40 | 166 | 51/51 | 100.00% | 51/51 | 9 ok |  | core |
| ✅ | initialize_tip_manager | 0x448cf0 | 21 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | uninit_tips | 0x448d10 | 31 | 14/14 | 100.00% | 14/14 | 1 ok |  | core |
| ✅ | enqueue_tip_message | 0x448d30 | 69 | 26/26 | 100.00% | 26/26 | 3 ok |  | core |
| ✅ | update_tip_manager | 0x448d80 | 31 | 14/14 | 100.00% | 14/14 | 1 ok |  | core |
| ✅ | initialize_tutorial | 0x448da0 | 43 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | uninit_tutorial | 0x448dd0 | 16 | 3/3 | 100.00% | 3/3 | 2 ok |  | core |
| ✅ | update_tutorial | 0x448de0 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  | core |
| ✅ | initialize_voice_set | 0x448df0 | 101 | 33/33 | 100.00% | 33/33 | 5 ok |  | core |
| ✅ | shuffle_voice_set | 0x448e60 | 93 | 34/34 | 100.00% | 34/34 | 6 ok |  | core |
| ✅ | reset_voice_manager | 0x448ec0 | 31 | 8/8 | 100.00% | 8/8 | - |  | core |
| ✅ | initialize_voice_manager | 0x448ee0 | 960 | 269/269 | 100.00% | 269/269 | 62 ok |  | core |
| ✅ | update_voice_manager | 0x4492a0 | 47 | 18/18 | 100.00% | 18/18 | 2 ok |  | core |
| ✅ | play_voice_manager | 0x4492d0 | 142 | 51/51 | 100.00% | 51/51 | 5 ok |  | core |
| ✅ | update_voice_set | 0x449360 | 46 | 14/14 | 100.00% | 14/14 | 2 ok |  | core |
| ✅ | play_voice_set | 0x449390 | 119 | 43/43 | 100.00% | 43/43 | 3 ok |  | core |
| ✅ | is_voice_playing | 0x449410 | 78 | 40/40 | 100.00% | 40/40 | 2 ok |  | core |
| ✅ | set_audio_normalization_scales | 0x449be0 | 24 | 7/7 | 100.00% | 7/7 | - |  | boundary |
| ✅ | initialize_global_font3d_bods_thunk | 0x449c10 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_font3d_bods | 0x449c20 | 28 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_global_font_queue_colors_thunk | 0x449c40 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_font_queue_colors | 0x449c50 | 31 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_font_wave_state | 0x449c70 | 41 | 5/5 | 100.00% | 5/5 | 4 ok |  | core |
| ✅ | update_font_wave_state | 0x449ca0 | 121 | 25/25 | 100.00% | 25/25 | 17 ok |  | core |
| ✅ | font_slot_index_for_char | 0x449d20 | 358 | 145/145 | 100.00% | 145/145 | - |  | core |
| ✅ | measure_font_text_width | 0x449e90 | 182 | 60/60 | 100.00% | 60/60 | 9 ok |  | core |
| ✅ | draw_font_text_instance | 0x44a360 | 867 | 272/272 | 100.00% | 272/272 | 41 ok |  | boundary |
| ✅ | draw_queued_font_quad_instance | 0x44a6d0 | 95 | 41/41 | 100.00% | 41/41 | 2 ok |  | boundary |
| ✅ | draw_font_text_queue | 0x44a730 | 83 | 31/31 | 100.00% | 31/31 | 4 ok |  | boundary |
| ✅ | queue_font_text_instance | 0x44a790 | 277 | 73/73 | 100.00% | 73/73 | 24 ok |  | boundary |
| ✅ | layout_and_queue_wrapped_font_text | 0x44abe0 | 548 | 155/155 | 100.00% | 155/155 | 12 ok |  | boundary |
| ✅ | is_key_pressed_edge | 0x44bb10 | 34 | 11/11 | 100.00% | 11/11 | 2 ok |  | boundary |
| ✅ | is_key_down | 0x44bb40 | 20 | 5/5 | 100.00% | 5/5 | 1 ok |  | boundary |
| ✅ | is_mouse_captured | 0x44c3b0 | 3 | 2/2 | 100.00% | 2/2 | - |  | boundary |
| ✅ | capture_mouse_cursor | 0x44c3c0 | 51 | 19/19 | 100.00% | 19/19 | 3 ok |  | boundary |
| ✅ | release_mouse_cursor | 0x44c400 | 21 | 8/8 | 100.00% | 8/8 | - |  | boundary |
| ✅ | load_object_definition | 0x44c420 | 1096 | 316/316 | 100.00% | 316/316 | 59 ok |  | core |
| ✅ | initialize_global_identity_matrix_thunk | 0x44c870 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_identity_matrix | 0x44c880 | 16 | 4/4 | 100.00% | 4/4 | 2 ok |  | core |
| ✅ | convert_math_type32_to_16 | 0x44c890 | 19 | 4/4 | 100.00% | 4/4 | 2 ok |  | core |
| ✅ | convert_math_type16_to_32 | 0x44c8b0 | 24 | 6/6 | 100.00% | 6/6 | 1 ok |  | core |
| ✅ | initialize_math_random_table | 0x44c8d0 | 36 | 10/10 | 100.00% | 10/10 | 4 ok |  | core |
| ✅ | next_math_random_value | 0x44c900 | 28 | 8/8 | 100.00% | 8/8 | 3 ok |  | core |
| ✅ | j_rand | 0x44c920 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_trigonometry_tables | 0x44c930 | 62 | 18/18 | 100.00% | 18/18 | 5 ok |  | core |
| ✅ | set_math_random_seed | 0x44c970 | 12 | 5/5 | 100.00% | 5/5 | 1 ok |  | core |
| ✅ | cosine | 0x44c980 | 80 | 21/21 | 100.00% | 21/21 | 7 ok |  | core |
| ✅ | sine | 0x44c9d0 | 34 | 7/7 | 100.00% | 7/7 | 4 ok |  | core |
| ✅ | arccosine | 0x44ca00 | 10 | 3/3 | 100.00% | 3/3 | 1 ok |  | core |
| ✅ | atan2_positive | 0x44ca10 | 148 | 48/48 | 100.00% | 48/48 | 7 ok |  | core |
| ✅ | square_root | 0x44cab0 | 7 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | multiply_vector_by_matrix_copy | 0x44cac0 | 144 | 49/49 | 100.00% | 49/49 | - |  | core |
| ✅ | dot_vectors | 0x44cb50 | 31 | 11/11 | 100.00% | 11/11 | - |  | core |
| ✅ | dot_vector | 0x44cb70 | 27 | 10/10 | 100.00% | 10/10 | - |  | core |
| ✅ | multiply_vector_by_matrix | 0x44cb90 | 135 | 40/40 | 100.00% | 40/40 | - |  | core |
| ✅ | rotate_vector_by_matrix | 0x44cc20 | 117 | 38/38 | 100.00% | 38/38 | - |  | core |
| ✅ | normalize_vector | 0x44cca0 | 75 | 29/29 | 100.00% | 29/29 | 5 ok |  | core |
| ✅ | vector_magnitude | 0x44ccf0 | 43 | 19/19 | 100.00% | 19/19 | 1 ok |  | core |
| ✅ | normalize_vector_from_source | 0x44cd20 | 32 | 12/12 | 100.00% | 12/12 | 1 ok |  | core |
| ✅ | cross_vectors | 0x44cd40 | 131 | 40/40 | 100.00% | 40/40 | 10 ok |  | core |
| ✅ | destroy_cross_vectors_static_result | 0x44cdd0 | 1 | 1/1 | 100.00% | 1/1 | - |  | core |
| ✅ | initialize_uniform_scale_matrix | 0x44cde0 | 66 | 21/21 | 100.00% | 21/21 | - |  | core |
| ✅ | rotate_matrix_world_x | 0x44ce30 | 136 | 50/50 | 100.00% | 50/50 | 2 ok |  | core |
| ✅ | rotate_matrix_world_y | 0x44cec0 | 133 | 50/50 | 100.00% | 50/50 | 2 ok |  | core |
| ✅ | rotate_matrix_world_z | 0x44cf50 | 133 | 50/50 | 100.00% | 50/50 | 2 ok |  | core |
| ✅ | initialize_matrix_from_values | 0x44cfe0 | 116 | 34/34 | 100.00% | 34/34 | - |  | core |
| ✅ | multiply_matrices | 0x44d060 | 312 | 114/114 | 100.00% | 114/114 | - |  | core |
| ✅ | multiply_matrix_assign | 0x44d1a0 | 45 | 18/18 | 100.00% | 18/18 | 1 ok |  | core |
| ✅ | multiply_matrix | 0x44d1d0 | 13 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | premultiply_matrix_in_place | 0x44d1e0 | 45 | 18/18 | 100.00% | 18/18 | 1 ok |  | core |
| ✅ | set_matrix_identity | 0x44d210 | 55 | 19/19 | 100.00% | 19/19 | - |  | core |
| ✅ | set_matrix_rotation_identity | 0x44d250 | 46 | 16/16 | 100.00% | 16/16 | - |  | core |
| ✅ | invert_matrix_in_place | 0x44d280 | 164 | 54/54 | 100.00% | 54/54 | - |  | core |
| ✅ | invert_matrix_from_source | 0x44d330 | 157 | 55/55 | 100.00% | 55/55 | - |  | core |
| ✅ | orthogonalize_matrix | 0x44d3d0 | 58 | 26/26 | 100.00% | 26/26 | 5 ok |  | core |
| ✅ | set_matrix_z_direction | 0x44d410 | 196 | 57/57 | 100.00% | 57/57 | 6 ok |  | core |
| ✅ | look_at_point | 0x44d4e0 | 76 | 22/22 | 100.00% | 22/22 | 1 ok |  | core |
| ✅ | initialize_quaternion_from_axis | 0x44d530 | 74 | 26/26 | 100.00% | 26/26 | 4 ok |  | core |
| ✅ | initialize_axis_from_quaternion | 0x44d580 | 78 | 30/30 | 100.00% | 30/30 | 4 ok |  | core |
| ✅ | initialize_matrix_from_quaternion | 0x44d820 | 247 | 82/82 | 100.00% | 82/82 | 3 ok |  | core |
| ✅ | interpolate_matrix_rotation | 0x44d920 | 367 | 105/105 | 100.00% | 105/105 | 17 ok |  | core |
| ✅ | linear_interpolate_matrix | 0x44da90 | 189 | 61/61 | 100.00% | 61/61 | 6 ok |  | core |
| ✅ | noop_this_constructor | 0x44db50 | 3 | 2/2 | 100.00% | 2/2 | - |  | core |
| ✅ | set_color_rgba | 0x44db60 | 32 | 10/10 | 100.00% | 10/10 | - |  | core |
| ✅ | set_color_alpha | 0x44db80 | 10 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | set_color_grayscale | 0x44db90 | 24 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | store_color4f | 0x44dbb0 | 30 | 9/9 | 100.00% | 9/9 | - |  | core |
| ✅ | set_color_rgb | 0x44dbd0 | 23 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | pack_color_rgba_u8 | 0x44dbf0 | 81 | 24/24 | 100.00% | 24/24 | 8 ok |  | core |
| ✅ | set_color_white | 0x44dc50 | 11 | 3/3 | 100.00% | 3/3 | 1 ok |  | core |
| ✅ | set_color_black | 0x44dc60 | 8 | 3/3 | 100.00% | 3/3 | 1 ok |  | core |
| ✅ | random_signed_float_below | 0x44dc70 | 32 | 9/9 | 100.00% | 9/9 | 3 ok |  | core |
| ✅ | random_float_below | 0x44dc90 | 26 | 8/8 | 100.00% | 8/8 | 2 ok |  | core |
| ✅ | initialize_sound_bank | 0x44dcb0 | 48 | 21/21 | 100.00% | 21/21 | 1 ok |  | boundary |
| ✅ | play_sound_effect_at_position | 0x44dce0 | 251 | 66/66 | 100.00% | 66/66 | 11 ok |  | boundary |
| ✅ | play_sound_effect | 0x44dde0 | 28 | 8/8 | 100.00% | 8/8 | 1 ok |  | boundary |
| ✅ | play_sound_effect_scaled | 0x44de00 | 28 | 9/9 | 100.00% | 9/9 | 1 ok |  | boundary |
| ✅ | play_warning_sample_backend | 0x44de20 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  | boundary |
| ✅ | stop_warning_sample_handle | 0x44de30 | 14 | 5/5 | 100.00% | 5/5 | 1 ok |  | boundary |
| ✅ | initialize_global_sprite_pool_colors_thunk | 0x44de40 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_sprite_pool_colors | 0x44de50 | 31 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_global_sprite_sentinel_color_thunk | 0x44de70 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_sprite_sentinel_color | 0x44de80 | 10 | 2/2 | 100.00% | 2/2 | 2 ok |  | core |
| ✅ | initialize_sprite | 0x44de90 | 155 | 33/33 | 100.00% | 33/33 | 1 ok |  | core |
| ✅ | update_sprite | 0x44df30 | 434 | 125/125 | 100.00% | 125/125 | 10 ok |  | core |
| ✅ | register_sprite_texture | 0x44e0f0 | 109 | 35/35 | 100.00% | 35/35 | 6 ok |  | core |
| ✅ | initialize_sprite_manager | 0x44e160 | 148 | 45/45 | 100.00% | 45/45 | 1 ok |  | core |
| ✅ | kill_sprite | 0x44e200 | 145 | 45/45 | 100.00% | 45/45 | 9 ok |  | core |
| ✅ | allocate_sprite | 0x44e2a0 | 295 | 81/81 | 100.00% | 81/81 | 10 ok |  | core |
| ✅ | kill_game_sprites | 0x44e3d0 | 55 | 23/23 | 100.00% | 23/23 | 3 ok |  | core |
| ✅ | set_sprite_manager_paused | 0x44e540 | 9 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | set_sprite_texture_ref | 0x44e550 | 30 | 8/8 | 100.00% | 8/8 | 1 ok |  | core |
| ✅ | get_sprite_texture | 0x44e570 | 14 | 3/3 | 100.00% | 3/3 | 1 ok |  | core |
| ✅ | get_sprite_tga | 0x44e580 | 20 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | ascii_upper_if_lowercase | 0x44e5a0 | 16 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | rstrcpy_checked_ascii | 0x44e5b0 | 72 | 31/31 | 100.00% | 31/31 | 2 ok |  | core |
| ✅ | find_case_insensitive_substring | 0x44e600 | 130 | 63/63 | 100.00% | 63/63 | 4 ok |  | core |
| ✅ | advance_to_next_crlf_line | 0x44e690 | 47 | 22/22 | 100.00% | 22/22 | - |  | core |
| ✅ | strings_equal_case_insensitive_path | 0x44e6c0 | 69 | 33/33 | 100.00% | 33/33 | - |  | core |
| ✅ | parse_next_signed_int | 0x44e710 | 107 | 47/47 | 100.00% | 47/47 | - |  | core |
| ✅ | sample_tga_pixel_rgb | 0x44e780 | 119 | 49/49 | 100.00% | 49/49 | - |  | core |
| ✅ | initialize_texture_list | 0x44e800 | 16 | 4/4 | 100.00% | 4/4 | - |  | boundary |
| ✅ | get_or_create_texture_ref | 0x44e810 | 228 | 79/79 | 100.00% | 79/79 | 4 ok |  | core |
| ✅ | attach_render_camera_source | 0x44e900 | 18 | 6/6 | 100.00% | 6/6 | - |  | boundary |
| ✅ | initialize_render_camera_slot | 0x44e920 | 36 | 11/11 | 100.00% | 11/11 | - |  | boundary |

## Near Match (95-99.99%) (27)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| 🚧 | initialize_frontend_widget | 0x401d30 | 1892 | 429/429 | 99.53% | 74/429 | 50 ok |  | core |
| 🚧 | layout_frontend_widget | 0x4024a0 | 741 | 177/177 | 99.44% | 66/177 | 20 ok |  | core |
| 🚧 | border_mouse_test | 0x404580 | 421 | 117/117 | 98.29% | 73/117 | 5 ok |  | core |
| 🚧 | render_backdrop | 0x411040 | 680 | 193/192 | 99.22% | 174/192 | 29 ok |  | core |
| 🚧 | initialize_high_score_screen | 0x416910 | 2311 | 600/600 | 98.00% | 80/600 | 137 ok |  | core |
| 🚧 | apply_distort_to_object | 0x41aa50 | 648 | 197/197 | 95.43% | 58/197 | 26 ok |  | core |
| 🚧 | try_enter_track_attachment_from_swept_motion | 0x42c770 | 800 | 199/204 | 95.78% | 16/204 | 47 ok |  | core |
| 🚧 | calc_object_bounding_box | 0x42fb10 | 402 | 119/119 | 99.16% | 28/119 | 1 ok |  | core |
| 🚧 | calc_object_texture_groups | 0x4303f0 | 127 | 55/55 | 98.18% | 18/55 | 1 ok |  | core |
| 🚧 | replace_object_list_texture_refs | 0x430d90 | 129 | 53/53 | 96.23% | 24/53 | 1 ok |  | core |
| 🚧 | update_input_controller_pointer_region | 0x4321c0 | 466 | 134/134 | 98.51% | 131/134 | 32 ok |  | boundary |
| 🚧 | read_repeating_text_input_key_code | 0x4327e0 | 1337 | 440/440 | 99.32% | 408/440 | 74 ok |  | boundary |
| 🚧 | initialize_track_render_cache_manager | 0x433060 | 436 | 122/122 | 99.18% | 29/122 | 18 ok |  | core |
| 🚧 | build_track_render_caches | 0x433220 | 1552 | 475/475 | 99.79% | 90/475 | 20 ok |  | core |
| 🚧 | append_track_cache_object | 0x433960 | 454 | 167/167 | 98.80% | 155/167 | 6 ok |  | core |
| 🚧 | initialize_star_field | 0x434310 | 861 | 247/247 | 97.57% | 126/247 | 26 ok |  | core |
| 🚧 | mark_track_warning_zones | 0x4354f0 | 251 | 99/99 | 98.99% | 79/99 | - |  | core |
| 🚧 | spawn_track_health_pickup | 0x43d6c0 | 441 | 122/122 | 99.18% | 16/122 | 7 ok |  | core |
| 🚧 | update_ring_or_special_effect_particle | 0x43e780 | 174 | 55/55 | 96.36% | 28/55 | 5 ok |  | core |
| 🚧 | explode_slug_hazard | 0x43f680 | 556 | 146/147 | 97.61% | 79/147 | 32 ok |  | core |
| 🚧 | update_sub_lazer_projectile | 0x4417d0 | 768 | 218/218 | 99.08% | 86/218 | 24 ok |  | core |
| 🚧 | update_cutscene | 0x4466d0 | 1888 | 503/505 | 97.62% | 10/505 | 58 ok |  | core |
| 🚧 | load_builtin_segment_definitions | 0x448060 | 256 | 92/92 | 98.91% | 18/92 | - |  | core |
| 🚧 | queue_axis_aligned_textured_quad | 0x44a8b0 | 249 | 65/65 | 98.46% | 43/65 | 20 ok |  | boundary |
| 🚧 | queue_axis_aligned_textured_quad_uv | 0x44a9b0 | 260 | 66/66 | 98.48% | 42/66 | 20 ok |  | boundary |
| 🚧 | initialize_font3d_objects | 0x44ae10 | 419 | 126/126 | 99.21% | 106/126 | 20 ok |  | boundary |
| 🚧 | build_sprite_tail | 0x44e410 | 304 | 86/86 | 97.67% | 36/86 | 8 ok |  | core |

## High Progress (80-94.99%) (42)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| 🚧 | draw_frontend_widget | 0x401130 | 2353 | 707/712 | 85.13% | 16/712 | 68 ok |  | core |
| 🚧 | initialize_completion_screen | 0x404920 | 972 | 278/278 | 92.81% | 23/278 | 46 ok |  | core |
| 🚧 | load_galaxy_layout | 0x4088e0 | 803 | 236/233 | 88.27% | 62/233 | 42 ok |  | core |
| 🚧 | initialize_game_assets_and_world | 0x40acf0 | 23070 | 5405/5411 | 81.34% | 0/5411 | 2 unaudited, 1880 ok |  | core |
| 🚧 | update_backdrop | 0x4112f0 | 189 | 69/67 | 89.71% | 17/67 | 7 ok |  | core |
| 🚧 | refresh_object_vertex_buffer | 0x412250 | 393 | 137/139 | 90.58% | 7/139 | 4 ok |  | boundary |
| 🚧 | get_or_append_object_texture_group_vertex | 0x413bb0 | 411 | 128/127 | 83.14% | 25/127 | 18 ok |  | boundary |
| 🚧 | update_golb_ai | 0x414820 | 2656 | 693/694 | 91.56% | 9/694 | 71 ok |  | core |
| 🚧 | add_time_trial_high_score | 0x4178b0 | 143 | 49/49 | 89.80% | 29/49 | 1 ok |  | core |
| 🚧 | mini_delete_high_score_entry | 0x417af0 | 92 | 33/33 | 84.85% | 15/33 | - |  | core |
| 🚧 | initialize_loading_screen | 0x418b50 | 758 | 253/253 | 83.00% | 5/253 | 54 ok |  | core |
| 🚧 | initialize_intro_screen | 0x4191e0 | 1851 | 523/521 | 88.89% | 88/521 | 66 ok |  | core |
| 🚧 | traverse_path_follow_golb | 0x4217b0 | 1551 | 421/425 | 85.82% | 32/425 | 7 ok |  | core |
| 🚧 | build_track_fringe_mesh | 0x4246a0 | 1069 | 318/318 | 92.77% | 100/318 | 23 ok |  | core |
| 🚧 | build_track_fringe_supertramp_mesh | 0x424ad0 | 1396 | 421/421 | 94.54% | 69/421 | 25 ok |  | core |
| 🚧 | calc_object_facequad_normals | 0x42fcb0 | 1397 | 433/437 | 93.56% | 98/437 | 22 ok |  | core |
| 🚧 | add_object_edge | 0x4305a0 | 772 | 226/227 | 86.53% | 15/227 | 3 unaudited, 34 ok |  | core |
| 🚧 | promote_track_tiles_to_fringe_variants | 0x4355f0 | 251 | 75/75 | 81.33% | 11/75 | 6 ok |  | core |
| 🚧 | switch_track_mirror | 0x435e60 | 79 | 27/30 | 91.23% | 20/30 | 3 ok |  | core |
| 🚧 | build_subgame_level | 0x437eb0 | 2128 | 555/555 | 84.68% | 177/555 | 108 ok |  | core |
| 🚧 | remove_sub_loc | 0x439bc0 | 396 | 130/131 | 91.19% | 87/131 | 18 ok |  | core |
| 🚧 | update_jetpack_gauge | 0x43a390 | 490 | 131/131 | 94.66% | 6/131 | 34 ok |  | core |
| 🚧 | play_subgoldy_shoot_sfx | 0x43afd0 | 335 | 96/88 | 89.13% | 26/88 | 2 unaudited, 19 ok |  | core |
| 🚧 | update_subgoldy | 0x43b120 | 8456 | 2087/2087 | 82.75% | 12/2087 | 1 unaudited, 315 ok |  | core |
| 🚧 | spawn_track_jetpack_pickup | 0x43d890 | 491 | 147/144 | 87.29% | 44/144 | 9 ok |  | core |
| 🚧 | update_damage_gauge | 0x440fd0 | 1043 | 268/268 | 94.03% | 122/268 | 65 ok |  | core |
| 🚧 | firework_shoot | 0x441dd0 | 390 | 103/103 | 94.17% | 78/103 | 21 ok |  | core |
| 🚧 | release_snail_weapons | 0x442e40 | 554 | 125/125 | 92.80% | 13/125 | 33 ok |  | core |
| 🚧 | load_frontend_level_by_mode_and_index | 0x443650 | 220 | 61/57 | 81.36% | 5/57 | 1 unaudited, 12 ok |  | core |
| 🚧 | place_parcels_on_track | 0x4438e0 | 2396 | 637/639 | 87.77% | 7/639 | 98 ok |  | core |
| 🚧 | place_challenge_parcels_on_track | 0x444240 | 617 | 173/171 | 81.40% | 0/171 | 2 unaudited, 33 ok |  | core |
| 🚧 | dispatch_cutscene_animation | 0x444600 | 221 | 55/55 | 94.55% | 48/55 | 3 ok |  | core |
| 🚧 | set_weapon_animation | 0x4446e0 | 221 | 55/55 | 94.55% | 48/55 | 3 ok |  | core |
| 🚧 | handle_subgoldy_collisions | 0x444cf0 | 2887 | 673/673 | 85.88% | 18/673 | 89 ok |  | core |
| 🚧 | set_snail_jetpack | 0x445860 | 185 | 61/62 | 86.18% | 0/62 | 8 ok |  | core |
| 🚧 | extract_snail_local_hotspots | 0x445d50 | 208 | 68/74 | 91.55% | 31/74 | 7 ok |  | core |
| 🚧 | update_cameraman | 0x4461d0 | 1274 | 322/322 | 92.86% | 36/322 | 76 ok |  | core |
| 🚧 | initialize_nuke | 0x447110 | 193 | 64/64 | 93.75% | 30/64 | 5 ok |  | core |
| 🚧 | load_level_definition_file | 0x447480 | 3039 | 941/926 | 84.63% | 20/926 | 2 unaudited, 183 ok |  | core |
| 🚧 | initialize_tip | 0x448a40 | 511 | 154/154 | 84.42% | 19/154 | 27 ok |  | core |
| 🚧 | queue_textured_quad_corners | 0x44aac0 | 274 | 69/69 | 89.86% | 33/69 | 24 ok |  | boundary |
| 🚧 | initialize_quaternion_from_matrix | 0x44d5d0 | 579 | 186/186 | 92.47% | 42/186 | 23 ok |  | core |

## Mid Progress (50-79.99%) (48)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| 🚧 | update_frontend_widget_interaction | 0x402820 | 2677 | 648/647 | 77.07% | 1/647 | 96 ok |  | core |
| 🚧 | border_input_text | 0x4035b0 | 1581 | 439/446 | 74.80% | 6/446 | 8 ok |  | core |
| 🚧 | update_galaxy | 0x4092f0 | 2051 | 569/566 | 71.01% | 48/566 | 55 ok |  | core |
| 🚧 | render_game_frame | 0x40a490 | 1460 | 430/439 | 56.16% | 6/439 | 34 ok |  | boundary |
| 🚧 | update_input | 0x40aa80 | 44 | 15/19 | 52.94% | 5/19 | - |  | boundary |
| 🚧 | select_level_track_texture_set | 0x410730 | 156 | 41/43 | 76.19% | 0/43 | 1 mismatch, 6 ok |  | core |
| 🚧 | create_golb | 0x415280 | 2349 | 549/582 | 77.98% | 81/582 | 1 unaudited, 47 ok |  | core |
| 🚧 | spawn_golb_impact_sprite | 0x415d80 | 159 | 43/45 | 63.64% | 3/45 | 3 ok |  | core |
| 🚧 | sample_smtrack_heightmap | 0x41a360 | 364 | 113/109 | 60.36% | 0/109 | 13 ok |  | core |
| 🚧 | initialize_looptheloop_path_template_pair | 0x41b0f0 | 2630 | 716/721 | 72.09% | 22/721 | 49 ok |  | core |
| 🚧 | initialize_looptheloopw_path_template_pair | 0x41bb40 | 2725 | 738/745 | 70.94% | 10/745 | 55 ok |  | core |
| 🚧 | initialize_loopout_path_template_pair | 0x41c5f0 | 2615 | 727/718 | 66.44% | 0/718 | 52 ok |  | core |
| 🚧 | initialize_hump_path_template_pair | 0x41d030 | 2553 | 691/685 | 67.59% | 20/685 | 43 ok |  | core |
| 🚧 | initialize_dump_path_template_pair | 0x41da30 | 2563 | 697/690 | 62.87% | 8/690 | 43 ok |  | core |
| 🚧 | initialize_dip_path_template_pair | 0x41e440 | 2390 | 642/655 | 52.27% | 22/655 | 37 ok |  | core |
| 🚧 | initialize_screw_path_template_pair | 0x41eda0 | 2495 | 675/685 | 62.21% | 26/685 | 2 unaudited, 38 ok |  | core |
| 🚧 | initialize_slalom_path_template_pair | 0x41f760 | 2564 | 690/696 | 58.87% | 6/696 | 40 ok |  | core |
| 🚧 | initialize_worm_path_template_pair | 0x420170 | 2759 | 728/736 | 72.81% | 0/736 | 37 ok |  | core |
| 🚧 | update_track_attachment_follow_state | 0x420cb0 | 2750 | 712/726 | 75.66% | 122/726 | 65 ok |  | core |
| 🚧 | initialize_slalombig_path_template_pair | 0x4221f0 | 2564 | 695/696 | 52.77% | 6/696 | 40 ok |  | core |
| 🚧 | initialize_sweep_path_template_pair | 0x422c00 | 2428 | 663/652 | 61.44% | 6/652 | 37 ok |  | core |
| 🚧 | initialize_snake_path_template_pair | 0x423580 | 2436 | 645/652 | 54.28% | 21/652 | 40 ok |  | core |
| 🚧 | initialize_supertramp_path_template_pair | 0x423f10 | 1935 | 541/552 | 55.08% | 17/552 | 36 ok |  | core |
| 🚧 | initialize_slalomdouble_path_template_pair | 0x425050 | 2536 | 648/683 | 51.84% | 5/683 | 2 unaudited, 44 ok |  | core |
| 🚧 | initialize_p_path_template_pair | 0x425a40 | 2482 | 677/679 | 56.64% | 6/679 | 41 ok |  | core |
| 🚧 | initialize_start_path_template_pair | 0x426400 | 2223 | 605/610 | 63.70% | 0/610 | 35 ok |  | core |
| 🚧 | initialize_turnover_path_template_pair | 0x426cb0 | 2433 | 644/671 | 59.77% | 54/671 | 41 ok |  | core |
| 🚧 | initialize_turnoverdouble_path_template_pair | 0x427640 | 2458 | 653/680 | 58.81% | 54/680 | 46 ok |  | core |
| 🚧 | initialize_turnunder_path_template_pair | 0x427fe0 | 2487 | 662/687 | 56.49% | 6/687 | 45 ok |  | core |
| 🚧 | initialize_wibble_path_template_pair | 0x4289a0 | 2213 | 612/608 | 70.33% | 85/608 | 39 ok |  | core |
| 🚧 | initialize_invert_path_template_pair | 0x429250 | 2182 | 611/600 | 70.69% | 109/600 | 35 ok |  | core |
| 🚧 | initialize_halfpipe_path_template_pair | 0x429b20 | 2592 | 692/707 | 64.19% | 18/707 | 55 ok |  | core |
| 🚧 | initialize_twister_path_template_pair | 0x42a540 | 2540 | 682/677 | 71.38% | 94/677 | 49 ok |  | core |
| 🚧 | initialize_twister2_path_template_pair | 0x42af30 | 2540 | 682/677 | 71.38% | 94/677 | 49 ok |  | core |
| 🚧 | initialize_loopbow_path_template_pair | 0x42ba80 | 2939 | 796/796 | 72.49% | 10/796 | 63 ok |  | core |
| 🚧 | initialize_toad_path_template_pair | 0x42cbf0 | 2419 | 633/663 | 58.18% | 15/663 | 33 ok |  | core |
| 🚧 | initialize_hill_valley_path_template_pair | 0x42d570 | 2447 | 672/668 | 70.15% | 21/668 | 41 ok |  | core |
| 🚧 | initialize_sbend_path_template_pair | 0x42df00 | 2068 | 574/579 | 68.34% | 67/579 | 39 ok |  | core |
| 🚧 | initialize_cage2_path_template_pair | 0x42e720 | 2422 | 654/648 | 68.20% | 10/648 | 46 ok |  | core |
| 🚧 | calc_object_edges | 0x4308b0 | 382 | 142/141 | 77.74% | 0/141 | 17 ok |  | core |
| 🚧 | remove_track_render_cache_bods | 0x433f20 | 156 | 61/58 | 70.59% | 5/58 | 5 ok |  | core |
| 🚧 | build_track_fringe_objects | 0x434be0 | 1428 | 492/495 | 60.39% | 3/495 | 4 unaudited, 49 ok |  | core |
| 🚧 | merge_track_tile_runs | 0x435180 | 873 | 284/276 | 67.50% | 0/276 | 12 ok |  | core |
| 🚧 | update_subgame | 0x438b90 | 3748 | 1036/1033 | 79.94% | 9/1033 | 129 ok |  | core |
| 🚧 | remove_subgame_bods | 0x440910 | 1644 | 505/501 | 71.77% | 6/501 | 70 ok |  | core |
| 🚧 | set_snail_weapon | 0x445920 | 940 | 245/248 | 73.02% | 1/248 | 24 ok |  | core |
| 🚧 | load_segment_definitions | 0x448160 | 1937 | 560/571 | 68.26% | 7/571 | 91 ok |  | core |
| 🚧 | register_font_texture_sheet | 0x449f50 | 1031 | 275/274 | 75.41% | 0/274 | 57 ok |  | boundary |

## Early Progress (>0-49.99%) (1)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| 🚧 | populate_runtime_track_cells_from_segments | 0x435eb0 | 5042 | 1240/1245 | 45.47% | 9/1245 | 1 mismatch, 60 unaudited, 108 ok |  | core |

## Excluded: Replaceable Platform (120)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| 🖥 | classify_archive_entry_extension | 0x4050c0 | 114 | 45/46 | 70.33% | 4/46 | - |  | replaceable-platform |
| 🖥 | scramble_archive_bytes_in_place | 0x405270 | 48 | 25/25 | 100.00% | 25/25 | - |  | replaceable-platform |
| 🖥 | save_file_bytes_with_optional_archive_scramble | 0x4052a0 | 156 | 56/56 | 100.00% | 56/56 | 10 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | delete_file_path | 0x405340 | 12 | 5/5 | 100.00% | 5/5 | 1 ok |  | replaceable-platform |
| 🖥 | toggle_archive_high_bit_in_place | 0x405350 | 24 | 11/11 | 100.00% | 11/11 | - |  | replaceable-platform |
| 🖥 | rebuild_game_archive_if_needed | 0x405370 | 715 | 232/232 | 66.38% | 5/232 | 22 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | log_startup_timestamp | 0x406d30 | 58 | 19/19 | 100.00% | 19/19 | 4 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | game_startup_and_main_loop | 0x406dc0 | 1316 | 327/325 | 70.86% | 1/325 | 23 unaudited, 151 ok |  | replaceable-platform |
| 🖥 | handle_game_window_activate | 0x4072f0 | 187 | 44/44 | 100.00% | 44/44 | 26 ok |  | replaceable-platform |
| 🖥 | show_and_focus_game_window | 0x4073b0 | 141 | 33/33 | 100.00% | 33/33 | 19 ok |  | replaceable-platform |
| 🖥 | handle_game_window_deactivate | 0x407440 | 69 | 18/18 | 100.00% | 18/18 | 9 ok |  | replaceable-platform |
| 🖥 | minimize_game_window | 0x407490 | 32 | 10/10 | 100.00% | 10/10 | 4 ok |  | replaceable-platform |
| 🖥 | game_window_proc | 0x4074b0 | 828 | 141/141 | 94.33% | 4/141 | 1 mismatch, 38 ok |  | replaceable-platform |
| 🖥 | snapshot_current_display_mode | 0x407850 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  | replaceable-platform |
| 🖥 | restore_desktop_display_mode | 0x407860 | 19 | 6/6 | 100.00% | 6/6 | 2 ok |  | replaceable-platform |
| 🖥 | probe_display_mode_count | 0x407880 | 40 | 17/17 | 100.00% | 17/17 | 1 ok |  | replaceable-platform |
| 🖥 | read_current_display_resolution | 0x4078b0 | 91 | 22/22 | 100.00% | 22/22 | 1 ok |  | replaceable-platform |
| 🖥 | clear_display_mode_state | 0x407910 | 14 | 3/3 | 100.00% | 3/3 | - |  | replaceable-platform |
| 🖥 | reset_display_mode_probe_count | 0x407920 | 8 | 2/2 | 100.00% | 2/2 | - |  | replaceable-platform |
| 🖥 | read_next_display_mode_view_sample | 0x407930 | 167 | 55/55 | 100.00% | 55/55 | - |  | replaceable-platform |
| 🖥 | bass_audio_window_proc | 0x4079e0 | 47 | 16/16 | 100.00% | 16/16 | 2 ok |  | replaceable-platform |
| 🖥 | initialize_audio_subsystem | 0x407a10 | 230 | 73/73 | 100.00% | 73/73 | 23 ok |  | replaceable-platform |
| 🖥 | shutdown_bass_audio_window | 0x407b00 | 72 | 19/19 | 100.00% | 19/19 | 10 ok |  | replaceable-platform |
| 🖥 | abort_startup_with_3d_error | 0x4088a0 | 27 | 7/7 | 100.00% | 7/7 | 4 ok |  | replaceable-platform |
| 🖥 | create_vertex_buffer | 0x4114b0 | 286 | 92/101 | 76.68% | 8/101 | 11 ok |  | replaceable-platform |
| 🖥 | create_index_buffer | 0x4115d0 | 91 | 36/36 | 100.00% | 36/36 | 5 ok |  | replaceable-platform |
| 🖥 | initialize_direct3d_renderer_defaults | 0x411630 | 180 | 38/38 | 100.00% | 38/38 | 15 ok |  | replaceable-platform |
| 🖥 | release_direct3d_renderer_resources | 0x4116f0 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | replaceable-platform |
| 🖥 | direct3d_renderer_set_cull_mode | 0x411700 | 46 | 16/16 | 100.00% | 16/16 | - |  | replaceable-platform |
| 🖥 | initialize_d3d8_device | 0x411730 | 378 | 106/106 | 100.00% | 106/106 | 12 ok |  | replaceable-platform |
| 🖥 | reset_direct3d_render_state | 0x4118b0 | 163 | 52/52 | 100.00% | 52/52 | 3 ok |  | replaceable-platform |
| 🖥 | release_direct3d_device_interfaces | 0x411960 | 81 | 18/18 | 100.00% | 18/18 | - |  | replaceable-platform |
| 🖥 | initialize_game_window_and_input_wrapper | 0x4119c0 | 14 | 5/5 | 100.00% | 5/5 | 1 ok |  | replaceable-platform |
| 🖥 | initialize_game_window_and_input | 0x4119d0 | 920 | 266/266 | 92.48% | 6/266 | 57 ok |  | replaceable-platform |
| 🖥 | release_global_direct3d_renderer_resources | 0x411d70 | 10 | 2/2 | 100.00% | 2/2 | 2 ok |  | replaceable-platform |
| 🖥 | uninitialize_input_devices | 0x411d80 | 20 | 4/4 | 100.00% | 4/4 | 4 ok |  | replaceable-platform |
| 🖥 | end_overlay_render_state | 0x411de0 | 43 | 13/13 | 100.00% | 13/13 | 4 ok |  | replaceable-platform |
| 🖥 | begin_overlay_render_state | 0x411e10 | 395 | 97/97 | 100.00% | 97/97 | 14 ok |  | replaceable-platform |
| 🖥 | update_display_mode_view_state | 0x412940 | 120 | 46/46 | 100.00% | 46/46 | 4 ok |  | replaceable-platform |
| 🖥 | initialize_direct3d_renderer | 0x4129c0 | 47 | 12/12 | 100.00% | 12/12 | 7 ok |  | replaceable-platform |
| 🖥 | set_blend_mode | 0x412d00 | 325 | 92/92 | 92.39% | 2/92 | 16 ok |  | replaceable-platform |
| 🖥 | set_immediate_blend_mode | 0x412e50 | 472 | 126/136 | 85.50% | 2/136 | 1 mismatch, 2 unaudited, 20 ok |  | replaceable-platform |
| 🖥 | draw_textured_quad_immediate | 0x413030 | 1156 | 331/332 | 98.34% | 111/332 | 26 ok |  | replaceable-platform |
| 🖥 | render_game_frame_scene | 0x4134c0 | 92 | 24/24 | 100.00% | 24/24 | 8 ok |  | replaceable-platform |
| 🖥 | present_backbuffer | 0x413520 | 20 | 9/9 | 100.00% | 9/9 | 1 ok |  | replaceable-platform |
| 🖥 | begin_sprite_depth_render_state | 0x413540 | 261 | 60/60 | 100.00% | 60/60 | 7 ok |  | replaceable-platform |
| 🖥 | end_sprite_depth_render_state | 0x413650 | 22 | 7/7 | 100.00% | 7/7 | 2 ok |  | replaceable-platform |
| 🖥 | configure_sprite_render_state | 0x413670 | 370 | 109/109 | 100.00% | 109/109 | 18 ok |  | replaceable-platform |
| 🖥 | direct3d_renderer_set_fullscreen_mode | 0x414270 | 325 | 84/84 | 100.00% | 84/84 | 29 ok |  | replaceable-platform |
| 🖥 | restore_texture_ref_stage_states | 0x4143c0 | 315 | 110/110 | 100.00% | 110/110 | 15 ok |  | replaceable-platform |
| 🖥 | query_direct3d_device_caps | 0x414600 | 65 | 21/21 | 100.00% | 21/21 | 4 ok |  | replaceable-platform |
| 🖥 | load_png_image | 0x42f0a0 | 965 | 371/371 | 100.00% | 371/371 | 78 ok |  | replaceable-platform |
| 🖥 | initialize_tracked_allocation_depth_thunk | 0x430e20 | 5 | 1/1 | 100.00% | 1/1 | 1 ok |  | replaceable-platform |
| 🖥 | initialize_tracked_allocation_depth | 0x430e30 | 11 | 2/2 | 100.00% | 2/2 | 1 ok |  | replaceable-platform |
| 🖥 | initialize_game_data_archive | 0x430e40 | 176 | 48/47 | 94.74% | 27/47 | 2 unaudited, 19 ok |  | replaceable-platform |
| 🖥 | uninitialize_game_data_archive | 0x430ef0 | 49 | 13/13 | 100.00% | 13/13 | 6 ok |  | replaceable-platform |
| 🖥 | set_current_directory_with_drive_fallback | 0x430f30 | 151 | 48/48 | 100.00% | 48/48 | 6 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | archive_or_file_exists | 0x430fd0 | 92 | 36/36 | 100.00% | 36/36 | 7 ok |  | replaceable-platform |
| 🖥 | load_file_bytes_fixed_size_from_archive_or_fs | 0x431030 | 536 | 189/188 | 92.84% | 9/188 | 32 ok |  | replaceable-platform |
| 🖥 | find_archive_entry | 0x431250 | 122 | 61/60 | 79.34% | 7/60 | 2 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | load_file_bytes_from_archive_or_fs | 0x4312d0 | 577 | 208/206 | 79.23% | 10/206 | 36 ok |  | replaceable-platform |
| 🖥 | load_file_bytes | 0x431520 | 21 | 8/8 | 100.00% | 8/8 | 1 ok |  | replaceable-platform |
| 🖥 | delete_file_path_with_directory_walk | 0x431540 | 264 | 84/84 | 100.00% | 84/84 | 14 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | write_file_bytes | 0x431650 | 229 | 74/74 | 100.00% | 74/74 | 10 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | enumerate_matching_archive_or_fs_entries | 0x431740 | 570 | 186/182 | 81.52% | 7/182 | 26 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | xor_archive_bytes_in_place | 0x431980 | 55 | 27/27 | 100.00% | 27/27 | - |  | replaceable-platform |
| 🖥 | load_archive_index | 0x4319c0 | 187 | 67/67 | 92.54% | 40/67 | 14 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | is_archive_index_loaded | 0x431a80 | 11 | 4/4 | 100.00% | 4/4 | 1 ok |  | replaceable-platform |
| 🖥 | get_archive_data_base | 0x431a90 | 6 | 2/2 | 100.00% | 2/2 | 1 ok |  | replaceable-platform |
| 🖥 | get_archive_data_end | 0x431aa0 | 11 | 3/3 | 100.00% | 3/3 | 1 ok |  | replaceable-platform |
| 🖥 | get_tracked_allocation_size | 0x431ab0 | 61 | 26/26 | 100.00% | 26/26 | 2 ok |  | replaceable-platform |
| 🖥 | push_tracked_allocation | 0x431af0 | 54 | 19/19 | 100.00% | 19/19 | 2 ok |  | replaceable-platform |
| 🖥 | pop_tracked_allocation | 0x431b30 | 44 | 20/20 | 100.00% | 20/20 | - |  | replaceable-platform |
| 🖥 | allocate_tracked_memory | 0x431b60 | 129 | 48/48 | 100.00% | 48/48 | 7 ok |  | replaceable-platform |
| 🖥 | free_tracked_memory | 0x431bf0 | 127 | 43/43 | 100.00% | 43/43 | 9 ok |  | replaceable-platform |
| 🖥 | free_tracked_allocations_to_mark | 0x431c70 | 53 | 15/15 | 100.00% | 15/15 | 6 ok |  | replaceable-platform |
| 🖥 | set_tracked_allocation_mark | 0x431cb0 | 11 | 3/3 | 100.00% | 3/3 | 2 ok |  | replaceable-platform |
| 🖥 | report_errorf | 0x431cc0 | 78 | 19/19 | 100.00% | 19/19 | 8 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | report_warningf | 0x431d10 | 78 | 19/19 | 100.00% | 19/19 | 8 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | report_messagef | 0x431d60 | 58 | 15/15 | 100.00% | 15/15 | 4 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | launch_alpha72_url | 0x433050 | 16 | 3/3 | 100.00% | 3/3 | 2 ok |  | replaceable-platform |
| 🖥 | initialize_bass_audio_backend | 0x449460 | 612 | 176/176 | 100.00% | 176/176 | 87 ok |  | replaceable-platform |
| 🖥 | uninitialize_bass_audio_backend | 0x4496d0 | 70 | 19/19 | 100.00% | 19/19 | 10 ok |  | replaceable-platform |
| 🖥 | ensure_music_stream_from_path | 0x449720 | 192 | 70/70 | 100.00% | 70/70 | 14 ok |  | replaceable-platform |
| 🖥 | prepare_music_stream_reload_if_path_changed | 0x4497e0 | 49 | 19/19 | 100.00% | 19/19 | 3 ok |  | replaceable-platform |
| 🖥 | play_music_stream_from_bytes | 0x449820 | 173 | 68/68 | 100.00% | 68/68 | 11 ok |  | replaceable-platform |
| 🖥 | stop_music_stream | 0x4498d0 | 71 | 21/21 | 100.00% | 21/21 | 8 ok |  | replaceable-platform |
| 🖥 | load_registered_sound_sample_from_path | 0x449920 | 61 | 20/20 | 100.00% | 20/20 | 4 ok |  | replaceable-platform |
| 🖥 | load_registered_sound_sample_from_bytes | 0x449960 | 59 | 18/18 | 100.00% | 18/18 | 4 ok |  | replaceable-platform |
| 🖥 | play_registered_sound_sample_scaled | 0x4499a0 | 106 | 30/30 | 100.00% | 30/30 | 7 ok |  | replaceable-platform |
| 🖥 | stop_sound_sample_handle | 0x449a10 | 14 | 4/4 | 100.00% | 4/4 | 1 ok |  | replaceable-platform |
| 🖥 | stop_registered_sound_sample | 0x449a20 | 21 | 5/5 | 100.00% | 5/5 | 2 ok |  | replaceable-platform |
| 🖥 | is_registered_sound_sample_playing | 0x449a40 | 27 | 7/7 | 100.00% | 7/7 | 2 ok |  | replaceable-platform |
| 🖥 | play_registered_sound_sample_default | 0x449a60 | 31 | 10/10 | 100.00% | 10/10 | 2 ok |  | replaceable-platform |
| 🖥 | play_registered_sound_sample_backend | 0x449a80 | 90 | 27/27 | 100.00% | 27/27 | 6 ok |  | replaceable-platform |
| 🖥 | play_registered_sound_sample_scaled_panned | 0x449ae0 | 98 | 29/29 | 100.00% | 29/29 | 7 ok |  | replaceable-platform |
| 🖥 | set_global_sample_volume_config | 0x449b50 | 27 | 7/7 | 100.00% | 7/7 | 3 ok |  | replaceable-platform |
| 🖥 | set_global_stream_volume_config | 0x449b70 | 27 | 7/7 | 100.00% | 7/7 | 3 ok |  | replaceable-platform |
| 🖥 | stop_audio_backend | 0x449b90 | 6 | 1/1 | 100.00% | 1/1 | 1 ok |  | replaceable-platform |
| 🖥 | resume_audio_backend_if_paused | 0x449ba0 | 21 | 8/8 | 100.00% | 8/8 | 1 ok |  | replaceable-platform |
| 🖥 | pause_audio_backend_if_running | 0x449bc0 | 22 | 9/9 | 100.00% | 9/9 | 1 ok |  | replaceable-platform |
| 🖥 | debug_report_stub | 0x449c00 | 3 | 2/2 | 100.00% | 2/2 | - |  | replaceable-platform |
| 🖥 | query_directx_runtime_version | 0x44afc0 | 1012 | 370/370 | 100.00% | 370/370 | 57 ok |  | replaceable-platform |
| 🖥 | enumerate_input_controllers | 0x44b3c0 | 196 | 71/71 | 100.00% | 71/71 | 14 ok |  | replaceable-platform |
| 🖥 | append_enumerated_input_controller_callback | 0x44b490 | 69 | 22/22 | 100.00% | 22/22 | 5 ok |  | replaceable-platform |
| 🖥 | configure_input_controller_axis_range_callback | 0x44b4e0 | 131 | 42/42 | 100.00% | 42/42 | 3 ok |  | replaceable-platform |
| 🖥 | update_joystick_input | 0x44b570 | 501 | 150/150 | 100.00% | 150/150 | 13 ok |  | replaceable-platform |
| 🖥 | release_input_controllers | 0x44b770 | 89 | 35/35 | 100.00% | 35/35 | 5 ok |  | replaceable-platform |
| 🖥 | initialize_keyboard_input | 0x44b7d0 | 160 | 55/55 | 100.00% | 55/55 | 15 ok |  | replaceable-platform |
| 🖥 | update_keyboard_input | 0x44b870 | 658 | 199/199 | 100.00% | 199/199 | 34 ok |  | replaceable-platform |
| 🖥 | release_keyboard_input | 0x44bb60 | 66 | 21/21 | 100.00% | 21/21 | 5 ok |  | replaceable-platform |
| 🖥 | initialize_mouse_authored_scale_from_clip_rect | 0x44bbb0 | 30 | 7/7 | 100.00% | 7/7 | 3 ok |  | replaceable-platform |
| 🖥 | update_mouse_authored_scale | 0x44bbd0 | 65 | 17/17 | 100.00% | 17/17 | 6 ok |  | replaceable-platform |
| 🖥 | resolve_uncaptured_cursor_sensitivity_scale | 0x44bc20 | 44 | 11/11 | 100.00% | 11/11 | 5 ok |  | replaceable-platform |
| 🖥 | update_mouse | 0x44bc50 | 1012 | 295/295 | 100.00% | 295/295 | 81 ok |  | replaceable-platform |
| 🖥 | set_hide_system_cursor_flag | 0x44c050 | 10 | 3/3 | 100.00% | 3/3 | 1 ok |  | replaceable-platform |
| 🖥 | click_mouse_screen | 0x44c060 | 156 | 43/43 | 100.00% | 43/43 | 13 ok |  | replaceable-platform |
| 🖥 | convert_mouse_screen_xy | 0x44c100 | 440 | 115/115 | 100.00% | 115/115 | 35 ok |  | replaceable-platform |
| 🖥 | release_mouse_input | 0x44c2c0 | 66 | 21/21 | 100.00% | 21/21 | 5 ok |  | replaceable-platform |
| 🖥 | initialize_mouse_input | 0x44c310 | 157 | 46/46 | 100.00% | 46/46 | 18 ok |  | replaceable-platform |

## Excluded: Third-party (3)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| 📚 | initialize_translation_matrix | 0x44fd90 | 92 | 23/34 | 7.02% | 1/34 | - |  | third-party |
| 📚 | build_perspective_projection_matrix | 0x450314 | 6085 | 38/54 | 26.09% | 2/54 | 1 ok | msvc6.5 /O2 /Oy- /G5 /W3 | third-party |
| 📚 | build_camera_view_matrix | 0x451ad9 | 328 | 119/130 | 28.11% | 0/130 | 2 ok |  | third-party |

## Type Consolidation

This is generated as part of `uv run snail match status --write tools/match/STATUS.md`. Keep types scratch-local until multiple scratches agree, then promote deliberately; divergent or conflicting names are semantic debt, not merge candidates.
Run `uv run snail match types --paths` for the full path-level report.

No consolidation candidates at the current threshold.
