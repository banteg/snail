# Matching Status

Regenerate with `uv run snail match status --write tools/match/STATUS.md`.

**444/687** mapped gameplay functions matched, **647/687** mapped gameplay functions have a scratch, **51427/325882** bytes (**15.78%**) are proof-grade, and overall fuzzy is **44.32%**.

## Proof Grade (444)

| | function | address | bytes | insns | match | prefix | masked | build |
|---|---|---|---|---|---|---|---|---|
| ✅ | initialize_array_with_constructor | 0x401000 | 42 | 21/21 | 100.00% | 21/21 | - |  |
| ✅ | border_add_text_number | 0x401030 | 167 | 68/68 | 100.00% | 68/68 | - |  |
| ✅ | hide_border_init | 0x4010e0 | 39 | 9/9 | 100.00% | 9/9 | 1 ok |  |
| ✅ | unhide_border_init | 0x401110 | 23 | 5/5 | 100.00% | 5/5 | - |  |
| ✅ | set_frontend_widget_shortcut_key | 0x402790 | 30 | 6/6 | 100.00% | 6/6 | - |  |
| ✅ | stack_widget_below | 0x4027b0 | 48 | 9/9 | 100.00% | 9/9 | 1 ok |  |
| ✅ | unhighlight_border | 0x4027e0 | 23 | 4/4 | 100.00% | 4/4 | - |  |
| ✅ | highlight_border | 0x402800 | 23 | 4/4 | 100.00% | 4/4 | - |  |
| ✅ | allocate_border | 0x4032a0 | 82 | 23/23 | 100.00% | 23/23 | 3 ok |  |
| ✅ | activate_all_borders | 0x403300 | 83 | 19/19 | 100.00% | 19/19 | - |  |
| ✅ | kill_all_borders | 0x4033c0 | 41 | 14/14 | 100.00% | 14/14 | - |  |
| ✅ | hide_all_borders | 0x4033f0 | 11 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| ✅ | unhide_all_borders | 0x403400 | 11 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| ✅ | border_input_text_init | 0x403410 | 184 | 46/46 | 100.00% | 46/46 | 3 ok |  |
| ✅ | update_input_ok | 0x4034d0 | 137 | 32/32 | 100.00% | 32/32 | - |  |
| ✅ | initialize_input_ok | 0x403560 | 67 | 23/23 | 100.00% | 23/23 | 5 ok |  |
| ✅ | reset_tooltip | 0x403be0 | 51 | 16/16 | 100.00% | 16/16 | 2 ok |  |
| ✅ | queue_frontend_widget_flag_after_delay | 0x403f60 | 93 | 22/22 | 100.00% | 22/22 | 2 ok |  |
| ✅ | update_border_manager | 0x403fc0 | 111 | 28/28 | 100.00% | 28/28 | 2 ok |  |
| ✅ | update_twinkle_manager | 0x404030 | 53 | 23/23 | 100.00% | 23/23 | 1 ok |  |
| ✅ | draw_twinkle | 0x404070 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  |
| ✅ | update_twinkle | 0x404080 | 1208 | 181/181 | 100.00% | 181/181 | 48 ok |  |
| ✅ | border_sprite_extend | 0x404540 | 55 | 14/14 | 100.00% | 14/14 | - |  |
| ✅ | set_border_justify_centre | 0x404730 | 13 | 3/3 | 100.00% | 3/3 | - |  |
| ✅ | initialize_cheat | 0x404740 | 11 | 5/5 | 100.00% | 5/5 | - |  |
| ✅ | flush_row_event_display | 0x404830 | 233 | 67/67 | 100.00% | 67/67 | 19 ok |  |
| ✅ | register_parcel_delivery | 0x405040 | 114 | 36/36 | 100.00% | 36/36 | 10 ok |  |
| ✅ | file_exists | 0x405140 | 37 | 14/14 | 100.00% | 14/14 | 3 ok |  |
| ✅ | get_stream_length_preserve_position | 0x405170 | 51 | 24/24 | 100.00% | 24/24 | 4 ok |  |
| ✅ | load_file_bytes_allocating | 0x4051b0 | 21 | 8/8 | 100.00% | 8/8 | 1 ok |  |
| ✅ | load_file_bytes_into_optional_buffer | 0x4051d0 | 158 | 56/56 | 100.00% | 56/56 | 9 ok | msvc6.5 /O2 /G5 /W3 /TC |
| ✅ | scramble_archive_bytes_in_place | 0x405270 | 48 | 25/25 | 100.00% | 25/25 | - |  |
| ✅ | save_file_bytes_with_optional_archive_scramble | 0x4052a0 | 156 | 56/56 | 100.00% | 56/56 | 10 ok | msvc6.5 /O2 /G5 /W3 /TC |
| ✅ | delete_file_path | 0x405340 | 12 | 5/5 | 100.00% | 5/5 | 1 ok |  |
| ✅ | toggle_archive_high_bit_in_place | 0x405350 | 24 | 11/11 | 100.00% | 11/11 | - |  |
| ✅ | initialize_directx_loader | 0x405c90 | 45 | 13/13 | 100.00% | 13/13 | 3 ok |  |
| ✅ | load_or_reuse_cached_x_mesh | 0x405cc0 | 157 | 65/65 | 100.00% | 65/65 | 6 ok |  |
| ✅ | destroy_completion_screen | 0x406060 | 98 | 25/25 | 100.00% | 25/25 | 9 ok |  |
| ✅ | update_completion_screen | 0x4067e0 | 1069 | 207/207 | 100.00% | 207/207 | 69 ok |  |
| ✅ | log_startup_timestamp | 0x406d30 | 143 | 19/19 | 100.00% | 19/19 | 4 ok | msvc6.5 /O2 /G5 /W3 /TC |
| ✅ | handle_game_window_activate | 0x4072f0 | 187 | 44/44 | 100.00% | 44/44 | 26 ok |  |
| ✅ | show_and_focus_game_window | 0x4073b0 | 141 | 33/33 | 100.00% | 33/33 | 19 ok |  |
| ✅ | handle_game_window_deactivate | 0x407440 | 112 | 18/18 | 100.00% | 18/18 | 9 ok |  |
| ✅ | consume_mouse_wheel_delta | 0x4077f0 | 23 | 4/4 | 100.00% | 4/4 | 2 ok |  |
| ✅ | read_left_mouse_button_state | 0x407810 | 18 | 4/4 | 100.00% | 4/4 | 2 ok |  |
| ✅ | read_right_mouse_button_state | 0x407830 | 18 | 4/4 | 100.00% | 4/4 | 2 ok |  |
| ✅ | snapshot_current_display_mode | 0x407850 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  |
| ✅ | restore_desktop_display_mode | 0x407860 | 19 | 6/6 | 100.00% | 6/6 | 2 ok |  |
| ✅ | probe_display_mode_count | 0x407880 | 40 | 17/17 | 100.00% | 17/17 | 1 ok |  |
| ✅ | read_current_display_resolution | 0x4078b0 | 351 | 22/22 | 100.00% | 22/22 | 1 ok |  |
| ✅ | initialize_audio_subsystem | 0x407a10 | 230 | 73/73 | 100.00% | 73/73 | 23 ok |  |
| ✅ | noop_runtime_ai | 0x407b50 | 1 | 1/1 | 100.00% | 1/1 | - |  |
| ✅ | initialize_runtime_pools_and_path_template_bank | 0x408060 | 932 | 227/227 | 100.00% | 227/227 | 72 ok |  |
| ✅ | initialize_border_record | 0x408410 | 92 | 21/21 | 100.00% | 21/21 | 9 ok |  |
| ✅ | initialize_cached_x_mesh_slot | 0x408470 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_intro_logo_renderable | 0x408490 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_track_speedup_runtime | 0x4084b0 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_track_jetpack_pickup_runtime | 0x4084d0 | 55 | 17/17 | 100.00% | 17/17 | 6 ok |  |
| ✅ | initialize_track_health_pickup_runtime | 0x408510 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_slug_hazard_runtime | 0x408530 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_garbage_hazard | 0x408550 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_track_ring_or_special_effect_runtime | 0x408570 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_track_row_runtime | 0x408590 | 36 | 13/13 | 100.00% | 13/13 | 3 ok |  |
| ✅ | initialize_path_template_record_pair | 0x4085c0 | 26 | 9/9 | 100.00% | 9/9 | 3 ok |  |
| ✅ | initialize_active_bod | 0x4085e0 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | noop_runtime_slot_constructor | 0x408600 | 3 | 2/2 | 100.00% | 2/2 | - |  |
| ✅ | initialize_sub_lazer_runtime | 0x408610 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_salt_hazard_runtime | 0x408630 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_fringe_object | 0x408650 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_click_start_controller_runtime | 0x408670 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_golb_shot | 0x408690 | 58 | 17/17 | 100.00% | 17/17 | 6 ok |  |
| ✅ | initialize_enemy_manager_runtime | 0x4086d0 | 322 | 79/79 | 100.00% | 79/79 | 27 ok |  |
| ✅ | initialize_active_landscape_entry | 0x408820 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_landscape_script_record | 0x408840 | 18 | 7/7 | 100.00% | 7/7 | 1 ok |  |
| ✅ | initialize_track_parcel_runtime | 0x408860 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | abort_startup_with_3d_error | 0x4088a0 | 27 | 7/7 | 100.00% | 7/7 | 4 ok |  |
| ✅ | initialize_bod | 0x4088c0 | 29 | 10/10 | 100.00% | 10/10 | 4 ok |  |
| ✅ | destroy_galaxy | 0x408c10 | 218 | 49/49 | 100.00% | 49/49 | 18 ok |  |
| ✅ | draw_galaxy_line | 0x409b00 | 227 | 67/67 | 100.00% | 67/67 | 4 ok |  |
| ✅ | close_galaxy_route | 0x409bf0 | 88 | 18/18 | 100.00% | 18/18 | 6 ok |  |
| ✅ | open_galaxy_route | 0x409c50 | 1128 | 266/266 | 100.00% | 266/266 | 41 ok |  |
| ✅ | galaxy_border_bound | 0x40a0c0 | 225 | 63/63 | 100.00% | 63/63 | 2 ok |  |
| ✅ | update_overlay | 0x40a1b0 | 136 | 42/42 | 100.00% | 42/42 | 7 ok |  |
| ✅ | initialize_overlay | 0x40a240 | 70 | 17/17 | 100.00% | 17/17 | 3 ok |  |
| ✅ | noop_runtime_callback | 0x40a290 | 3 | 1/1 | 100.00% | 1/1 | - |  |
| ✅ | initialize_input | 0x40aa50 | 45 | 12/12 | 100.00% | 12/12 | - |  |
| ✅ | initialize_frontend_overlay_color_lerp | 0x40ab00 | 63 | 18/18 | 100.00% | 18/18 | 2 ok |  |
| ✅ | draw_frontend_overlay_color_lerp | 0x40ab40 | 122 | 38/38 | 100.00% | 38/38 | 6 ok |  |
| ✅ | begin_frontend_fade_out | 0x40abc0 | 23 | 5/5 | 100.00% | 5/5 | - |  |
| ✅ | begin_frontend_fade_in | 0x40abe0 | 14 | 3/3 | 100.00% | 3/3 | - |  |
| ✅ | update_frontend_transition_overlay | 0x40abf0 | 248 | 62/62 | 100.00% | 62/62 | 9 ok |  |
| ✅ | initialize_distort | 0x410710 | 11 | 5/5 | 100.00% | 5/5 | - |  |
| ✅ | initialize_game_last | 0x410720 | 14 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| ✅ | set_backdrop_progress_fraction | 0x410c30 | 13 | 3/3 | 100.00% | 3/3 | - |  |
| ✅ | change_backdrop_real | 0x410dc0 | 87 | 30/30 | 100.00% | 30/30 | 1 ok |  |
| ✅ | initialize_backdrop | 0x410e20 | 279 | 55/55 | 100.00% | 55/55 | 4 ok |  |
| ✅ | set_backdrop_texture_target | 0x410f40 | 79 | 14/14 | 100.00% | 14/14 | 2 ok |  |
| ✅ | draw_split_backdrop | 0x410f90 | 172 | 50/50 | 100.00% | 50/50 | 4 ok |  |
| ✅ | direct3d_renderer_set_cull_mode | 0x411700 | 46 | 16/16 | 100.00% | 16/16 | - |  |
| ✅ | uninitialize_input_devices | 0x411d80 | 20 | 4/4 | 100.00% | 4/4 | 4 ok |  |
| ✅ | end_overlay_render_state | 0x411de0 | 43 | 13/13 | 100.00% | 13/13 | 4 ok |  |
| ✅ | begin_overlay_render_state | 0x411e10 | 395 | 97/97 | 100.00% | 97/97 | 14 ok |  |
| ✅ | set_cull_mode | 0x4129f0 | 775 | 5/5 | 100.00% | 5/5 | 2 ok |  |
| ✅ | begin_sprite_depth_render_state | 0x413540 | 261 | 60/60 | 100.00% | 60/60 | 7 ok |  |
| ✅ | end_sprite_depth_render_state | 0x413650 | 22 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | configure_sprite_render_state | 0x413670 | 370 | 109/109 | 100.00% | 109/109 | 18 ok |  |
| ✅ | draw_sprite_quad | 0x4137f0 | 951 | 259/259 | 100.00% | 259/259 | 29 ok |  |
| ✅ | set_object_color | 0x4141d0 | 139 | 47/47 | 100.00% | 47/47 | 3 ok |  |
| ✅ | set_fullscreen_mode | 0x414260 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  |
| ✅ | bind_texture_ref | 0x414500 | 178 | 62/62 | 100.00% | 62/62 | 11 ok |  |
| ✅ | replace_object_group_texture_refs | 0x4145c0 | 129 | 26/26 | 100.00% | 26/26 | - |  |
| ✅ | reset_render_counters | 0x414650 | 18 | 5/5 | 100.00% | 5/5 | 3 ok |  |
| ✅ | kill_golb | 0x414670 | 418 | 132/132 | 100.00% | 132/132 | 16 ok |  |
| ✅ | spawn_golb_trail_sprite | 0x415bb0 | 161 | 47/47 | 100.00% | 47/47 | 2 ok |  |
| ✅ | initialize_enemy_manager | 0x415e20 | 7 | 2/2 | 100.00% | 2/2 | - |  |
| ✅ | search_path_for_golb | 0x415e30 | 192 | 63/63 | 100.00% | 63/63 | 3 ok |  |
| ✅ | append_subgame_contact_target | 0x415ef0 | 88 | 34/34 | 100.00% | 34/34 | - |  |
| ✅ | initialize_challenge_setup_screen | 0x415f50 | 662 | 167/167 | 100.00% | 167/167 | 37 ok |  |
| ✅ | destroy_challenge_setup_screen | 0x4161f0 | 370 | 96/96 | 100.00% | 96/96 | 32 ok |  |
| ✅ | initialize_help_screen | 0x416800 | 181 | 47/47 | 100.00% | 47/47 | 15 ok |  |
| ✅ | destroy_help_screen | 0x4168c0 | 16 | 3/3 | 100.00% | 3/3 | 2 ok |  |
| ✅ | update_help_screen | 0x4168d0 | 54 | 12/12 | 100.00% | 12/12 | 3 ok |  |
| ✅ | destroy_high_score_screen | 0x417220 | 52 | 11/11 | 100.00% | 11/11 | 5 ok |  |
| ✅ | initialize_high_score_tables | 0x417540 | 155 | 58/58 | 100.00% | 58/58 | 4 ok |  |
| ✅ | load_high_scores_from_file | 0x4175e0 | 184 | 71/71 | 100.00% | 71/71 | 4 ok |  |
| ✅ | save_high_scores_and_config | 0x417940 | 297 | 101/101 | 100.00% | 101/101 | 19 ok |  |
| ✅ | exit_high_score_screen | 0x417b50 | 104 | 23/23 | 100.00% | 23/23 | 6 ok |  |
| ✅ | initialize_new_game_menu | 0x417bc0 | 739 | 182/182 | 100.00% | 182/182 | 48 ok |  |
| ✅ | reset_landscape_manager | 0x4182e0 | 11 | 2/2 | 100.00% | 2/2 | - |  |
| ✅ | activate_landscape_entry | 0x418870 | 442 | 123/123 | 100.00% | 123/123 | 20 ok |  |
| ✅ | clear_active_landscape_entries | 0x418a30 | 141 | 49/49 | 100.00% | 49/49 | 5 ok |  |
| ✅ | update_active_landscape_entry | 0x418ac0 | 130 | 41/41 | 100.00% | 41/41 | 4 ok |  |
| ✅ | destroy_loading_screen | 0x418e50 | 41 | 15/15 | 100.00% | 15/15 | 3 ok |  |
| ✅ | update_intro_screen | 0x4199e0 | 161 | 51/51 | 100.00% | 51/51 | 11 ok |  |
| ✅ | destroy_main_menu | 0x419b30 | 26 | 5/5 | 100.00% | 5/5 | 4 ok |  |
| ✅ | initialize_main_menu | 0x419b50 | 682 | 172/172 | 100.00% | 172/172 | 48 ok |  |
| ✅ | update_main_menu | 0x419e00 | 326 | 68/68 | 100.00% | 68/68 | 16 ok |  |
| ✅ | initialize_duplicate_vertices | 0x419f50 | 39 | 13/13 | 100.00% | 13/13 | 2 ok |  |
| ✅ | clean_duplicate_vertices | 0x419f80 | 70 | 33/33 | 100.00% | 33/33 | - |  |
| ✅ | initialize_textured_backdrop_quad | 0x41a0b0 | 181 | 57/57 | 100.00% | 57/57 | 6 ok |  |
| ✅ | raise_backdrop_quad_edge_pair | 0x41a170 | 66 | 19/19 | 100.00% | 19/19 | 4 ok |  |
| ✅ | initialize_backdrop_slice_quad | 0x41a1c0 | 196 | 61/61 | 100.00% | 61/61 | 7 ok |  |
| ✅ | initialize_backdrop_corner_quad | 0x41a290 | 207 | 55/55 | 100.00% | 55/55 | 10 ok |  |
| ✅ | initialize_options_menu | 0x41ace0 | 506 | 127/127 | 100.00% | 127/127 | 32 ok |  |
| ✅ | destroy_options_menu | 0x41aee0 | 127 | 32/32 | 100.00% | 32/32 | 13 ok |  |
| ✅ | update_options_menu | 0x41af60 | 267 | 73/73 | 100.00% | 73/73 | 19 ok |  |
| ✅ | apply_audio_config_volumes | 0x41b070 | 43 | 11/11 | 100.00% | 11/11 | 7 ok |  |
| ✅ | allocate_path_template_samples | 0x41b0a0 | 72 | 23/23 | 100.00% | 23/23 | 4 ok |  |
| ✅ | initialize_path_follow_golb | 0x421770 | 58 | 16/16 | 100.00% | 16/16 | 1 ok |  |
| ✅ | find_segment_path_index_by_name | 0x429ae0 | 59 | 27/27 | 100.00% | 27/27 | 3 ok |  |
| ✅ | compute_kind42_attachment_transform | 0x42b920 | 146 | 48/48 | 100.00% | 48/48 | 8 ok |  |
| ✅ | load_config_file | 0x42f470 | 23 | 9/9 | 100.00% | 9/9 | 1 ok |  |
| ✅ | load_file_bytes_from_path | 0x42f490 | 169 | 59/59 | 100.00% | 59/59 | 9 ok | msvc6.5 /O2 /G5 /W3 /TC |
| ✅ | save_config_file | 0x42f540 | 115 | 31/31 | 100.00% | 31/31 | 5 ok |  |
| ✅ | is_bod_after_sprites | 0x42f5c0 | 8 | 3/3 | 100.00% | 3/3 | - |  |
| ✅ | set_bod_object | 0x42f5d0 | 18 | 6/6 | 100.00% | 6/6 | - |  |
| ✅ | initialize_bod_base | 0x42f5f0 | 87 | 27/27 | 100.00% | 27/27 | 5 ok |  |
| ✅ | initialize_renderable_bod | 0x42f650 | 33 | 10/10 | 100.00% | 10/10 | 3 ok |  |
| ✅ | apply_bod_position | 0x42f680 | 89 | 39/39 | 100.00% | 39/39 | 1 ok |  |
| ✅ | initialize_object | 0x42f6f0 | 24 | 9/9 | 100.00% | 9/9 | - |  |
| ✅ | request_object_vertices | 0x42f710 | 114 | 37/37 | 100.00% | 37/37 | 8 ok |  |
| ✅ | copy_object_vertices | 0x42f790 | 57 | 28/28 | 100.00% | 28/28 | - |  |
| ✅ | request_object_vertices_copy | 0x42f7d0 | 38 | 14/14 | 100.00% | 14/14 | 3 ok |  |
| ✅ | request_object_facequad_normals | 0x42f800 | 71 | 26/26 | 100.00% | 26/26 | 4 ok |  |
| ✅ | request_object_vertex_colours | 0x42f850 | 77 | 30/30 | 100.00% | 30/30 | 2 ok |  |
| ✅ | request_object_facequads | 0x42f8c0 | 108 | 40/40 | 100.00% | 40/40 | 5 ok |  |
| ✅ | request_object_texture_groups | 0x42f930 | 82 | 29/29 | 100.00% | 29/29 | 4 ok |  |
| ✅ | initialize_object_list | 0x42f990 | 80 | 30/30 | 100.00% | 30/30 | 3 ok |  |
| ✅ | build_all_objects | 0x42f9e0 | 146 | 54/54 | 100.00% | 54/54 | 8 ok |  |
| ✅ | apply_object_toon | 0x42fa80 | 73 | 24/24 | 100.00% | 24/24 | 4 ok |  |
| ✅ | advance_frame_sequence | 0x430470 | 245 | 65/65 | 100.00% | 65/65 | 2 ok |  |
| ✅ | request_object_edges | 0x430570 | 44 | 16/16 | 100.00% | 16/16 | 2 ok |  |
| ✅ | uninitialize_game_data_archive | 0x430ef0 | 49 | 13/13 | 100.00% | 13/13 | 6 ok |  |
| ✅ | set_current_directory_with_drive_fallback | 0x430f30 | 151 | 48/48 | 100.00% | 48/48 | 6 ok | msvc6.5 /O2 /G5 /W3 /TC |
| ✅ | archive_or_file_exists | 0x430fd0 | 92 | 36/36 | 100.00% | 36/36 | 7 ok |  |
| ✅ | load_file_bytes | 0x431520 | 21 | 8/8 | 100.00% | 8/8 | 1 ok |  |
| ✅ | delete_file_path_with_directory_walk | 0x431540 | 264 | 84/84 | 100.00% | 84/84 | 14 ok | msvc6.5 /O2 /G5 /W3 /TC |
| ✅ | write_file_bytes | 0x431650 | 229 | 74/74 | 100.00% | 74/74 | 10 ok | msvc6.5 /O2 /G5 /W3 /TC |
| ✅ | xor_archive_bytes_in_place | 0x431980 | 55 | 27/27 | 100.00% | 27/27 | - |  |
| ✅ | is_archive_index_loaded | 0x431a80 | 11 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| ✅ | get_archive_data_base | 0x431a90 | 6 | 2/2 | 100.00% | 2/2 | 1 ok |  |
| ✅ | get_archive_data_end | 0x431aa0 | 11 | 3/3 | 100.00% | 3/3 | 1 ok |  |
| ✅ | get_tracked_allocation_size | 0x431ab0 | 61 | 26/26 | 100.00% | 26/26 | 2 ok |  |
| ✅ | push_tracked_allocation | 0x431af0 | 54 | 19/19 | 100.00% | 19/19 | 2 ok |  |
| ✅ | pop_tracked_allocation | 0x431b30 | 44 | 20/20 | 100.00% | 20/20 | - |  |
| ✅ | allocate_tracked_memory | 0x431b60 | 129 | 48/48 | 100.00% | 48/48 | 7 ok |  |
| ✅ | free_tracked_memory | 0x431bf0 | 127 | 43/43 | 100.00% | 43/43 | 9 ok |  |
| ✅ | free_tracked_allocations_to_mark | 0x431c70 | 53 | 15/15 | 100.00% | 15/15 | 6 ok |  |
| ✅ | set_tracked_allocation_mark | 0x431cb0 | 11 | 3/3 | 100.00% | 3/3 | 2 ok |  |
| ✅ | report_errorf | 0x431cc0 | 78 | 19/19 | 100.00% | 19/19 | 8 ok | msvc6.5 /O2 /G5 /W3 /TC |
| ✅ | report_warningf | 0x431d10 | 78 | 19/19 | 100.00% | 19/19 | 8 ok | msvc6.5 /O2 /G5 /W3 /TC |
| ✅ | report_messagef | 0x431d60 | 58 | 15/15 | 100.00% | 15/15 | 4 ok | msvc6.5 /O2 /G5 /W3 /TC |
| ✅ | copy_c_string | 0x431da0 | 21 | 10/10 | 100.00% | 10/10 | - |  |
| ✅ | skip_to_next_line | 0x431e30 | 29 | 13/13 | 100.00% | 13/13 | - |  |
| ✅ | append_c_string | 0x431e50 | 42 | 19/19 | 100.00% | 19/19 | - |  |
| ✅ | parse_next_space_delimited_token | 0x431e80 | 60 | 27/27 | 100.00% | 27/27 | - |  |
| ✅ | parse_next_int32 | 0x431ec0 | 89 | 39/39 | 100.00% | 39/39 | - |  |
| ✅ | set_input_controller_slot0_button_axes | 0x431fd0 | 30 | 7/7 | 100.00% | 7/7 | 3 ok |  |
| ✅ | update_input_controller_slot_button_axes | 0x431ff0 | 247 | 61/61 | 100.00% | 61/61 | 25 ok |  |
| ✅ | copy_active_input_controller_state | 0x4320f0 | 198 | 52/52 | 100.00% | 52/52 | 16 ok |  |
| ✅ | set_input_controller_pointer_authored_xy | 0x4323a0 | 152 | 40/40 | 100.00% | 40/40 | 11 ok |  |
| ✅ | cache_music_file | 0x432d50 | 160 | 42/42 | 100.00% | 42/42 | 11 ok |  |
| ✅ | play_sound_effect_backend | 0x432df0 | 136 | 42/42 | 100.00% | 42/42 | 11 ok |  |
| ✅ | play_voice_backend | 0x432e80 | 136 | 42/42 | 100.00% | 42/42 | 11 ok |  |
| ✅ | find_registered_sound_sample_id_by_name | 0x432fc0 | 79 | 34/34 | 100.00% | 34/34 | 6 ok |  |
| ✅ | xor_decode_buffer_with_index | 0x433010 | 80 | 15/15 | 100.00% | 15/15 | - |  |
| ✅ | update_track_render_cache_rows | 0x433b30 | 848 | 227/227 | 100.00% | 227/227 | 27 ok |  |
| ✅ | update_active_bod | 0x433e80 | 147 | 50/50 | 100.00% | 50/50 | 7 ok |  |
| ✅ | open_thanks_screen | 0x433fc0 | 13 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| ✅ | initialize_thanks_for_playing_screen | 0x433fd0 | 234 | 55/55 | 100.00% | 55/55 | 17 ok |  |
| ✅ | uninit_thanks_screen | 0x4340c0 | 38 | 8/8 | 100.00% | 8/8 | 3 ok |  |
| ✅ | update_thanks_for_playing_screen | 0x4340f0 | 376 | 88/88 | 100.00% | 88/88 | 19 ok |  |
| ✅ | destroy_star_field | 0x434270 | 70 | 28/28 | 100.00% | 28/28 | 1 ok |  |
| ✅ | open_star_field | 0x4342c0 | 77 | 26/26 | 100.00% | 26/26 | 4 ok |  |
| ✅ | hide_star_field | 0x434670 | 50 | 23/23 | 100.00% | 23/23 | - |  |
| ✅ | unhide_star_field | 0x4346b0 | 50 | 23/23 | 100.00% | 23/23 | - |  |
| ✅ | update_star_field | 0x4346f0 | 264 | 66/66 | 100.00% | 66/66 | 13 ok |  |
| ✅ | is_neighbor_cell_solid | 0x434b60 | 127 | 47/47 | 100.00% | 47/47 | 2 ok |  |
| ✅ | build_track_colours | 0x435d40 | 161 | 37/37 | 100.00% | 37/37 | 24 ok |  |
| ✅ | set_subgame_features | 0x435df0 | 76 | 19/19 | 100.00% | 19/19 | 3 ok |  |
| ✅ | normalize_segment_glyph_for_track_flags | 0x437270 | 570 | 160/160 | 100.00% | 160/160 | 2 ok |  |
| ✅ | reset_subgame | 0x437b10 | 291 | 75/75 | 100.00% | 75/75 | 2 ok |  |
| ✅ | update_progress_bar | 0x437c40 | 413 | 110/110 | 100.00% | 110/110 | 19 ok |  |
| ✅ | rebuild_track_runtime_from_segments | 0x437de0 | 145 | 44/44 | 100.00% | 44/44 | 13 ok |  |
| ✅ | calc_slider_to_rate | 0x437e80 | 45 | 11/11 | 100.00% | 11/11 | 4 ok |  |
| ✅ | destroy_subgame | 0x438850 | 830 | 246/246 | 100.00% | 246/246 | 41 ok |  |
| ✅ | is_slide_cache_tile_family | 0x439a40 | 33 | 17/17 | 100.00% | 17/17 | - |  |
| ✅ | is_ramp_cache_tile_family | 0x439a70 | 57 | 29/29 | 100.00% | 29/29 | - |  |
| ✅ | is_open_neighbor_tile_family | 0x439ab0 | 29 | 15/15 | 100.00% | 15/15 | - |  |
| ✅ | is_floor_cache_tile_family | 0x439ad0 | 41 | 21/21 | 100.00% | 21/21 | - |  |
| ✅ | refresh_fringe_object_draw_list | 0x439b00 | 186 | 63/63 | 100.00% | 63/63 | 8 ok |  |
| ✅ | update_movement_flag_emitters | 0x43a300 | 97 | 39/39 | 100.00% | 39/39 | 1 ok |  |
| ✅ | end_jetpack_hover | 0x43a370 | 28 | 9/9 | 100.00% | 9/9 | 1 ok |  |
| ✅ | uninit_jet_particles | 0x43a580 | 36 | 17/17 | 100.00% | 17/17 | 1 ok |  |
| ✅ | initialize_jet_particles | 0x43a5b0 | 214 | 73/73 | 100.00% | 73/73 | 3 ok |  |
| ✅ | initialize_jetpack_gauge | 0x43a930 | 65 | 15/15 | 100.00% | 15/15 | 3 ok |  |
| ✅ | arm_jetpack_gauge | 0x43a980 | 55 | 18/18 | 100.00% | 18/18 | 4 ok |  |
| ✅ | show_subgoldy_lives | 0x43af10 | 66 | 23/23 | 100.00% | 23/23 | 2 ok |  |
| ✅ | begin_post_follow_carryover | 0x43af60 | 97 | 20/20 | 100.00% | 20/20 | - |  |
| ✅ | initialize_subgoldy_ghost | 0x43d230 | 413 | 108/108 | 100.00% | 108/108 | 6 ok |  |
| ✅ | set_subgoldy_ghost_z | 0x43d3d0 | 62 | 18/18 | 100.00% | 18/18 | - |  |
| ✅ | get_track_grid_cell_at_world_position | 0x43d410 | 98 | 34/34 | 100.00% | 34/34 | 3 ok |  |
| ✅ | get_track_runtime_cell_at_world_z | 0x43d480 | 73 | 23/23 | 100.00% | 23/23 | 3 ok |  |
| ✅ | sample_track_floor_height_at_position | 0x43d4d0 | 197 | 63/63 | 100.00% | 63/63 | 8 ok |  |
| ✅ | spawn_track_speedup | 0x43d880 | 3 | 1/1 | 100.00% | 1/1 | - |  |
| ✅ | initialize_ring_or_special_effect_particles | 0x43e470 | 535 | 153/153 | 100.00% | 153/153 | 10 ok |  |
| ✅ | update_track_speedup | 0x43ee50 | 340 | 103/103 | 100.00% | 103/103 | 15 ok |  |
| ✅ | destroy_garbage_hazard | 0x43f130 | 205 | 62/62 | 100.00% | 62/62 | 6 ok |  |
| ✅ | update_slug_voice_ai | 0x43f520 | 56 | 14/14 | 100.00% | 14/14 | 1 ok |  |
| ✅ | play_slug_voice | 0x43f560 | 95 | 22/22 | 100.00% | 22/22 | 3 ok |  |
| ✅ | initialize_slug_voice_manager | 0x43f5c0 | 18 | 4/4 | 100.00% | 4/4 | - |  |
| ✅ | update_slug_voice_manager | 0x43f5e0 | 49 | 15/15 | 100.00% | 15/15 | 2 ok |  |
| ✅ | hit_slug_hazard | 0x43f620 | 94 | 25/25 | 100.00% | 25/25 | 5 ok |  |
| ✅ | kill_slug_hazard | 0x43f8b0 | 128 | 35/35 | 100.00% | 35/35 | 7 ok |  |
| ✅ | clear_subgoldy_score_buckets | 0x4403a0 | 18 | 7/7 | 100.00% | 7/7 | - |  |
| ✅ | set_subgame_rate | 0x4404c0 | 15 | 5/5 | 100.00% | 5/5 | - |  |
| ✅ | calc_subgame_rate | 0x4404d0 | 297 | 84/84 | 100.00% | 84/84 | 16 ok |  |
| ✅ | uninit_pause_menu | 0x440600 | 82 | 22/22 | 100.00% | 22/22 | 8 ok |  |
| ✅ | initialize_pause_menu | 0x440660 | 316 | 88/88 | 100.00% | 88/88 | 23 ok |  |
| ✅ | update_pause_menu | 0x4407a0 | 249 | 55/55 | 100.00% | 55/55 | 10 ok |  |
| ✅ | advance_blink_random | 0x4408a0 | 31 | 10/10 | 100.00% | 10/10 | - |  |
| ✅ | initialize_blink_random | 0x4408c0 | 74 | 21/21 | 100.00% | 21/21 | 5 ok |  |
| ✅ | update_barrier_ai | 0x440f80 | 17 | 5/5 | 100.00% | 5/5 | - |  |
| ✅ | initialize_damage_gauge | 0x440fa0 | 40 | 12/12 | 100.00% | 12/12 | - |  |
| ✅ | initialize_salt_hazard_pool | 0x441540 | 26 | 7/7 | 100.00% | 7/7 | - |  |
| ✅ | initialize_sub_lazer_pool | 0x441650 | 26 | 7/7 | 100.00% | 7/7 | - |  |
| ✅ | spawn_sub_lazer_projectile | 0x441670 | 195 | 63/63 | 100.00% | 63/63 | 6 ok |  |
| ✅ | zero_timer_counters | 0x441b70 | 20 | 8/8 | 100.00% | 8/8 | - |  |
| ✅ | advance_timer_counters | 0x441b90 | 116 | 38/38 | 100.00% | 38/38 | 7 ok |  |
| ✅ | update_banner | 0x441d40 | 129 | 44/44 | 100.00% | 44/44 | 7 ok |  |
| ✅ | update_smtracks | 0x441f60 | 56 | 19/19 | 100.00% | 19/19 | 2 ok |  |
| ✅ | initialize_subgoldy_resurrect | 0x441fa0 | 40 | 6/6 | 100.00% | 6/6 | - |  |
| ✅ | update_subgoldy_resurrect | 0x441fd0 | 332 | 76/76 | 100.00% | 76/76 | 13 ok |  |
| ✅ | get_track_skirt_color | 0x442120 | 76 | 25/25 | 100.00% | 25/25 | 1 ok |  |
| ✅ | initialize_click_start | 0x442170 | 277 | 79/79 | 100.00% | 79/79 | 13 ok |  |
| ✅ | initialize_vapour | 0x442500 | 62 | 19/19 | 100.00% | 19/19 | 3 ok |  |
| ✅ | reset_vapour | 0x442540 | 31 | 7/7 | 100.00% | 7/7 | - |  |
| ✅ | update_row_model | 0x443070 | 186 | 60/60 | 100.00% | 60/60 | 6 ok |  |
| ✅ | update_track_parcels | 0x443130 | 34 | 16/16 | 100.00% | 16/16 | - |  |
| ✅ | initialize_track_parcel_slots | 0x443160 | 38 | 13/13 | 100.00% | 13/13 | 1 ok |  |
| ✅ | allocate_track_parcel_slot | 0x443190 | 54 | 18/18 | 100.00% | 18/18 | 2 ok |  |
| ✅ | spawn_track_parcel | 0x443730 | 292 | 96/96 | 100.00% | 96/96 | 5 ok |  |
| ✅ | initialize_parcel_set_bucket_pool | 0x443870 | 39 | 15/15 | 100.00% | 15/15 | 3 ok |  |
| ✅ | initialize_zero_parcel_bucket_pool | 0x4438b0 | 39 | 15/15 | 100.00% | 15/15 | 3 ok |  |
| ✅ | initialize_anim_manager | 0x4447c0 | 14 | 6/6 | 100.00% | 6/6 | - |  |
| ✅ | initialize_score_stats | 0x444960 | 20 | 8/8 | 100.00% | 8/8 | - |  |
| ✅ | start_squidge_y | 0x444980 | 23 | 5/5 | 100.00% | 5/5 | 1 ok |  |
| ✅ | start_squidge_z | 0x4449a0 | 23 | 6/6 | 100.00% | 6/6 | 1 ok |  |
| ✅ | initialize_invincible_shell | 0x444ac0 | 31 | 7/7 | 100.00% | 7/7 | 3 ok |  |
| ✅ | start_invincible_shell | 0x444ae0 | 97 | 21/21 | 100.00% | 21/21 | 4 ok |  |
| ✅ | update_invincible_shell | 0x444b50 | 416 | 98/98 | 100.00% | 98/98 | 28 ok |  |
| ✅ | kill_subgoldy | 0x445840 | 17 | 6/6 | 100.00% | 6/6 | 1 ok |  |
| ✅ | update_times_up | 0x445e20 | 75 | 26/26 | 100.00% | 26/26 | 5 ok |  |
| ✅ | uninit_times_up | 0x445e70 | 27 | 8/8 | 100.00% | 8/8 | 2 ok |  |
| ✅ | show_times_up_message | 0x445e90 | 116 | 31/31 | 100.00% | 31/31 | 6 ok |  |
| ✅ | hide_gameplay_scores | 0x445f10 | 35 | 12/12 | 100.00% | 12/12 | 2 ok |  |
| ✅ | unhide_gameplay_scores | 0x445f40 | 27 | 8/8 | 100.00% | 8/8 | 2 ok |  |
| ✅ | initialize_snail_skin | 0x445f60 | 27 | 6/6 | 100.00% | 6/6 | 2 ok |  |
| ✅ | update_snail_skin_transition | 0x445f80 | 69 | 25/25 | 100.00% | 25/25 | 1 ok |  |
| ✅ | change_snail_skin | 0x445fd0 | 69 | 19/19 | 100.00% | 19/19 | 3 ok |  |
| ✅ | update_subgame_camera | 0x446020 | 269 | 70/70 | 100.00% | 70/70 | 9 ok |  |
| ✅ | initialize_cutscene_ai | 0x446130 | 35 | 8/8 | 100.00% | 8/8 | 4 ok |  |
| ✅ | initialize_cameraman | 0x446160 | 102 | 20/20 | 100.00% | 20/20 | 6 ok |  |
| ✅ | initialize_subgoldy_death | 0x446e30 | 47 | 14/14 | 100.00% | 14/14 | 3 ok |  |
| ✅ | initialize_warning | 0x446e80 | 130 | 32/32 | 100.00% | 32/32 | 6 ok |  |
| ✅ | uninit_warning | 0x446f10 | 22 | 6/6 | 100.00% | 6/6 | 2 ok |  |
| ✅ | start_warning | 0x446f30 | 21 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| ✅ | stop_warning | 0x446f50 | 14 | 3/3 | 100.00% | 3/3 | 1 ok |  |
| ✅ | stop_warning_sample | 0x446f60 | 24 | 7/7 | 100.00% | 7/7 | 4 ok |  |
| ✅ | get_track_cell_row_index | 0x447040 | 65 | 22/22 | 100.00% | 22/22 | 2 ok |  |
| ✅ | initialize_fringe_manager | 0x447090 | 11 | 2/2 | 100.00% | 2/2 | - |  |
| ✅ | allocate_fringe_object | 0x4470a0 | 50 | 14/14 | 100.00% | 14/14 | 2 ok |  |
| ✅ | uninit_nuke | 0x4470e0 | 41 | 18/18 | 100.00% | 18/18 | 1 ok |  |
| ✅ | recycle_bod_to_free_list | 0x447290 | 106 | 36/36 | 100.00% | 36/36 | 4 ok |  |
| ✅ | load_level_definitions | 0x448900 | 96 | 30/30 | 100.00% | 30/30 | 6 ok |  |
| ✅ | format_time_trial_string | 0x448960 | 113 | 36/36 | 100.00% | 36/36 | 12 ok | msvc6.5 /O2 /G5 /W3 /TC |
| ✅ | kill_tip_widgets | 0x4489e0 | 81 | 24/24 | 100.00% | 24/24 | 6 ok |  |
| ✅ | initialize_tip_manager | 0x448cf0 | 21 | 7/7 | 100.00% | 7/7 | - |  |
| ✅ | uninit_tips | 0x448d10 | 31 | 14/14 | 100.00% | 14/14 | 1 ok |  |
| ✅ | enqueue_tip_message | 0x448d30 | 69 | 26/26 | 100.00% | 26/26 | 3 ok |  |
| ✅ | update_tip_manager | 0x448d80 | 31 | 14/14 | 100.00% | 14/14 | 1 ok |  |
| ✅ | initialize_tutorial | 0x448da0 | 43 | 12/12 | 100.00% | 12/12 | 2 ok |  |
| ✅ | uninit_tutorial | 0x448dd0 | 16 | 3/3 | 100.00% | 3/3 | 2 ok |  |
| ✅ | update_tutorial | 0x448de0 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  |
| ✅ | initialize_voice_set | 0x448df0 | 101 | 33/33 | 100.00% | 33/33 | 5 ok |  |
| ✅ | shuffle_voice_set | 0x448e60 | 93 | 34/34 | 100.00% | 34/34 | 6 ok |  |
| ✅ | reset_voice_manager | 0x448ec0 | 31 | 8/8 | 100.00% | 8/8 | - |  |
| ✅ | update_voice_manager | 0x4492a0 | 47 | 18/18 | 100.00% | 18/18 | 2 ok |  |
| ✅ | play_voice_manager | 0x4492d0 | 142 | 51/51 | 100.00% | 51/51 | 5 ok |  |
| ✅ | update_voice_set | 0x449360 | 46 | 14/14 | 100.00% | 14/14 | 2 ok |  |
| ✅ | play_voice_set | 0x449390 | 119 | 43/43 | 100.00% | 43/43 | 3 ok |  |
| ✅ | is_voice_playing | 0x449410 | 78 | 40/40 | 100.00% | 40/40 | 2 ok |  |
| ✅ | initialize_bass_audio_backend | 0x449460 | 612 | 176/176 | 100.00% | 176/176 | 87 ok |  |
| ✅ | uninitialize_bass_audio_backend | 0x4496d0 | 70 | 19/19 | 100.00% | 19/19 | 10 ok |  |
| ✅ | ensure_music_stream_from_path | 0x449720 | 192 | 70/70 | 100.00% | 70/70 | 14 ok |  |
| ✅ | prepare_music_stream_reload_if_path_changed | 0x4497e0 | 49 | 19/19 | 100.00% | 19/19 | 3 ok |  |
| ✅ | play_music_stream_from_bytes | 0x449820 | 173 | 68/68 | 100.00% | 68/68 | 11 ok |  |
| ✅ | stop_music_stream | 0x4498d0 | 71 | 21/21 | 100.00% | 21/21 | 8 ok |  |
| ✅ | load_registered_sound_sample_from_path | 0x449920 | 61 | 20/20 | 100.00% | 20/20 | 4 ok |  |
| ✅ | play_registered_sound_sample_scaled | 0x4499a0 | 106 | 30/30 | 100.00% | 30/30 | 7 ok |  |
| ✅ | stop_sound_sample_handle | 0x449a10 | 14 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| ✅ | stop_registered_sound_sample | 0x449a20 | 21 | 5/5 | 100.00% | 5/5 | 2 ok |  |
| ✅ | is_registered_sound_sample_playing | 0x449a40 | 27 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | play_registered_sound_sample_default | 0x449a60 | 31 | 10/10 | 100.00% | 10/10 | 2 ok |  |
| ✅ | play_registered_sound_sample_backend | 0x449a80 | 90 | 27/27 | 100.00% | 27/27 | 6 ok |  |
| ✅ | play_registered_sound_sample_scaled_panned | 0x449ae0 | 98 | 29/29 | 100.00% | 29/29 | 7 ok |  |
| ✅ | set_global_sample_volume_config | 0x449b50 | 27 | 7/7 | 100.00% | 7/7 | 3 ok |  |
| ✅ | set_global_stream_volume_config | 0x449b70 | 27 | 7/7 | 100.00% | 7/7 | 3 ok |  |
| ✅ | stop_audio_backend | 0x449b90 | 6 | 1/1 | 100.00% | 1/1 | 1 ok |  |
| ✅ | resume_audio_backend_if_paused | 0x449ba0 | 21 | 8/8 | 100.00% | 8/8 | 1 ok |  |
| ✅ | pause_audio_backend_if_running | 0x449bc0 | 22 | 9/9 | 100.00% | 9/9 | 1 ok |  |
| ✅ | set_audio_normalization_scales | 0x449be0 | 24 | 7/7 | 100.00% | 7/7 | - |  |
| ✅ | initialize_font_wave_state | 0x449c70 | 41 | 5/5 | 100.00% | 5/5 | 4 ok |  |
| ✅ | update_font_wave_state | 0x449ca0 | 121 | 25/25 | 100.00% | 25/25 | 17 ok |  |
| ✅ | font_slot_index_for_char | 0x449d20 | 358 | 145/145 | 100.00% | 145/145 | - |  |
| ✅ | draw_queued_font_quad_instance | 0x44a6d0 | 95 | 41/41 | 100.00% | 41/41 | 2 ok |  |
| ✅ | draw_font_text_queue | 0x44a730 | 83 | 31/31 | 100.00% | 31/31 | 4 ok |  |
| ✅ | enumerate_input_controllers | 0x44b3c0 | 196 | 71/71 | 100.00% | 71/71 | 14 ok |  |
| ✅ | append_enumerated_input_controller_callback | 0x44b490 | 69 | 22/22 | 100.00% | 22/22 | 5 ok |  |
| ✅ | configure_input_controller_axis_range_callback | 0x44b4e0 | 131 | 42/42 | 100.00% | 42/42 | 3 ok |  |
| ✅ | update_joystick_input | 0x44b570 | 501 | 150/150 | 100.00% | 150/150 | 13 ok |  |
| ✅ | release_input_controllers | 0x44b770 | 89 | 35/35 | 100.00% | 35/35 | 5 ok |  |
| ✅ | initialize_keyboard_input | 0x44b7d0 | 160 | 55/55 | 100.00% | 55/55 | 15 ok |  |
| ✅ | update_keyboard_input | 0x44b870 | 658 | 199/199 | 100.00% | 199/199 | 34 ok |  |
| ✅ | is_key_pressed_edge | 0x44bb10 | 34 | 11/11 | 100.00% | 11/11 | 2 ok |  |
| ✅ | is_key_down | 0x44bb40 | 20 | 5/5 | 100.00% | 5/5 | 1 ok |  |
| ✅ | release_keyboard_input | 0x44bb60 | 66 | 21/21 | 100.00% | 21/21 | 5 ok |  |
| ✅ | initialize_mouse_authored_scale_from_clip_rect | 0x44bbb0 | 30 | 7/7 | 100.00% | 7/7 | 3 ok |  |
| ✅ | update_mouse_authored_scale | 0x44bbd0 | 65 | 17/17 | 100.00% | 17/17 | 6 ok |  |
| ✅ | resolve_uncaptured_cursor_sensitivity_scale | 0x44bc20 | 44 | 11/11 | 100.00% | 11/11 | 5 ok |  |
| ✅ | set_hide_system_cursor_flag | 0x44c050 | 10 | 3/3 | 100.00% | 3/3 | 1 ok |  |
| ✅ | click_mouse_screen | 0x44c060 | 156 | 43/43 | 100.00% | 43/43 | 13 ok |  |
| ✅ | release_mouse_input | 0x44c2c0 | 66 | 21/21 | 100.00% | 21/21 | 5 ok |  |
| ✅ | initialize_mouse_input | 0x44c310 | 157 | 46/46 | 100.00% | 46/46 | 18 ok |  |
| ✅ | is_mouse_captured | 0x44c3b0 | 3 | 2/2 | 100.00% | 2/2 | - |  |
| ✅ | capture_mouse_cursor | 0x44c3c0 | 51 | 19/19 | 100.00% | 19/19 | 3 ok |  |
| ✅ | release_mouse_cursor | 0x44c400 | 21 | 8/8 | 100.00% | 8/8 | - |  |
| ✅ | initialize_global_identity_matrix | 0x44c880 | 16 | 4/4 | 100.00% | 4/4 | 2 ok |  |
| ✅ | convert_math_type32_to_16 | 0x44c890 | 19 | 4/4 | 100.00% | 4/4 | 2 ok |  |
| ✅ | convert_math_type16_to_32 | 0x44c8b0 | 24 | 6/6 | 100.00% | 6/6 | 1 ok |  |
| ✅ | initialize_math_random_table | 0x44c8d0 | 36 | 10/10 | 100.00% | 10/10 | 4 ok |  |
| ✅ | next_math_random_value | 0x44c900 | 28 | 8/8 | 100.00% | 8/8 | 3 ok |  |
| ✅ | initialize_trigonometry_tables | 0x44c930 | 62 | 18/18 | 100.00% | 18/18 | 5 ok |  |
| ✅ | set_math_random_seed | 0x44c970 | 12 | 5/5 | 100.00% | 5/5 | 1 ok |  |
| ✅ | cosine | 0x44c980 | 80 | 21/21 | 100.00% | 21/21 | 7 ok |  |
| ✅ | sine | 0x44c9d0 | 34 | 7/7 | 100.00% | 7/7 | 4 ok |  |
| ✅ | arccosine | 0x44ca00 | 10 | 3/3 | 100.00% | 3/3 | 1 ok |  |
| ✅ | atan2_positive | 0x44ca10 | 148 | 48/48 | 100.00% | 48/48 | 7 ok |  |
| ✅ | square_root | 0x44cab0 | 7 | 3/3 | 100.00% | 3/3 | - |  |
| ✅ | multiply_vector_by_matrix_copy | 0x44cac0 | 144 | 49/49 | 100.00% | 49/49 | - |  |
| ✅ | dot_vectors | 0x44cb50 | 31 | 11/11 | 100.00% | 11/11 | - |  |
| ✅ | dot_vector | 0x44cb70 | 27 | 10/10 | 100.00% | 10/10 | - |  |
| ✅ | rotate_vector_by_matrix | 0x44cc20 | 117 | 38/38 | 100.00% | 38/38 | - |  |
| ✅ | normalize_vector | 0x44cca0 | 75 | 29/29 | 100.00% | 29/29 | 5 ok |  |
| ✅ | vector_magnitude | 0x44ccf0 | 43 | 19/19 | 100.00% | 19/19 | 1 ok |  |
| ✅ | normalize_vector_from_source | 0x44cd20 | 32 | 12/12 | 100.00% | 12/12 | 1 ok |  |
| ✅ | cross_vectors | 0x44cd40 | 131 | 40/40 | 100.00% | 40/40 | 10 ok |  |
| ✅ | initialize_uniform_scale_matrix | 0x44cde0 | 66 | 21/21 | 100.00% | 21/21 | - |  |
| ✅ | rotate_matrix_world_x | 0x44ce30 | 136 | 50/50 | 100.00% | 50/50 | 2 ok |  |
| ✅ | rotate_matrix_world_y | 0x44cec0 | 133 | 50/50 | 100.00% | 50/50 | 2 ok |  |
| ✅ | rotate_matrix_world_z | 0x44cf50 | 133 | 50/50 | 100.00% | 50/50 | 2 ok |  |
| ✅ | initialize_matrix_from_values | 0x44cfe0 | 116 | 34/34 | 100.00% | 34/34 | - |  |
| ✅ | multiply_matrices | 0x44d060 | 312 | 114/114 | 100.00% | 114/114 | - |  |
| ✅ | multiply_matrix_in_place | 0x44d1a0 | 45 | 18/18 | 100.00% | 18/18 | 1 ok |  |
| ✅ | premultiply_matrix_in_place | 0x44d1e0 | 45 | 18/18 | 100.00% | 18/18 | 1 ok |  |
| ✅ | set_matrix_identity | 0x44d210 | 55 | 19/19 | 100.00% | 19/19 | - |  |
| ✅ | set_matrix_rotation_identity | 0x44d250 | 46 | 16/16 | 100.00% | 16/16 | - |  |
| ✅ | invert_matrix_in_place | 0x44d280 | 164 | 54/54 | 100.00% | 54/54 | - |  |
| ✅ | invert_matrix_from_source | 0x44d330 | 157 | 55/55 | 100.00% | 55/55 | - |  |
| ✅ | orthogonalize_matrix | 0x44d3d0 | 58 | 26/26 | 100.00% | 26/26 | 5 ok |  |
| ✅ | set_matrix_z_direction | 0x44d410 | 196 | 57/57 | 100.00% | 57/57 | 6 ok |  |
| ✅ | look_at_point | 0x44d4e0 | 76 | 22/22 | 100.00% | 22/22 | 1 ok |  |
| ✅ | initialize_axis_from_quaternion | 0x44d580 | 78 | 30/30 | 100.00% | 30/30 | 4 ok |  |
| ✅ | set_color_rgba | 0x44db60 | 32 | 10/10 | 100.00% | 10/10 | - |  |
| ✅ | set_color_alpha | 0x44db80 | 10 | 3/3 | 100.00% | 3/3 | - |  |
| ✅ | set_color_grayscale | 0x44db90 | 24 | 7/7 | 100.00% | 7/7 | - |  |
| ✅ | store_color4f | 0x44dbb0 | 30 | 9/9 | 100.00% | 9/9 | - |  |
| ✅ | pack_color_rgba_u8 | 0x44dbf0 | 81 | 24/24 | 100.00% | 24/24 | 8 ok |  |
| ✅ | set_color_white | 0x44dc50 | 11 | 3/3 | 100.00% | 3/3 | 1 ok |  |
| ✅ | set_color_black | 0x44dc60 | 8 | 3/3 | 100.00% | 3/3 | 1 ok |  |
| ✅ | random_signed_float_below | 0x44dc70 | 32 | 9/9 | 100.00% | 9/9 | 3 ok |  |
| ✅ | random_float_below | 0x44dc90 | 26 | 8/8 | 100.00% | 8/8 | 2 ok |  |
| ✅ | initialize_sound_bank | 0x44dcb0 | 48 | 21/21 | 100.00% | 21/21 | 1 ok |  |
| ✅ | play_sound_effect | 0x44dde0 | 28 | 8/8 | 100.00% | 8/8 | 1 ok |  |
| ✅ | play_sound_effect_scaled | 0x44de00 | 28 | 9/9 | 100.00% | 9/9 | 1 ok |  |
| ✅ | play_warning_sample_backend | 0x44de20 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  |
| ✅ | stop_warning_sample_handle | 0x44de30 | 14 | 5/5 | 100.00% | 5/5 | 1 ok |  |
| ✅ | initialize_sprite | 0x44de90 | 155 | 33/33 | 100.00% | 33/33 | 1 ok |  |
| ✅ | update_sprite | 0x44df30 | 434 | 125/125 | 100.00% | 125/125 | 10 ok |  |
| ✅ | register_sprite_texture | 0x44e0f0 | 109 | 35/35 | 100.00% | 35/35 | 6 ok |  |
| ✅ | kill_sprite | 0x44e200 | 145 | 45/45 | 100.00% | 45/45 | 9 ok |  |
| ✅ | allocate_sprite | 0x44e2a0 | 295 | 81/81 | 100.00% | 81/81 | 10 ok |  |
| ✅ | kill_game_sprites | 0x44e3d0 | 55 | 23/23 | 100.00% | 23/23 | 3 ok |  |
| ✅ | set_sprite_manager_paused | 0x44e540 | 9 | 3/3 | 100.00% | 3/3 | - |  |
| ✅ | set_sprite_texture_ref | 0x44e550 | 30 | 8/8 | 100.00% | 8/8 | 1 ok |  |
| ✅ | get_sprite_texture | 0x44e570 | 14 | 3/3 | 100.00% | 3/3 | 1 ok |  |
| ✅ | get_sprite_texture_ref | 0x44e580 | 20 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| ✅ | ascii_upper_if_lowercase | 0x44e5a0 | 16 | 7/7 | 100.00% | 7/7 | - |  |
| ✅ | rstrcpy_checked_ascii | 0x44e5b0 | 72 | 31/31 | 100.00% | 31/31 | 2 ok |  |
| ✅ | advance_to_next_crlf_line | 0x44e690 | 47 | 22/22 | 100.00% | 22/22 | - |  |
| ✅ | strings_equal_case_insensitive_path | 0x44e6c0 | 69 | 33/33 | 100.00% | 33/33 | - |  |
| ✅ | initialize_texture_list | 0x44e800 | 16 | 4/4 | 100.00% | 4/4 | - |  |
| ✅ | attach_render_camera_source | 0x44e900 | 18 | 6/6 | 100.00% | 6/6 | - |  |
| ✅ | initialize_render_camera_slot | 0x44e920 | 36 | 11/11 | 100.00% | 11/11 | - |  |

## Near Match (95-99.99%) (11)

| | function | address | bytes | insns | match | prefix | masked | build |
|---|---|---|---|---|---|---|---|---|
| 🚧 | border_mouse_test | 0x404580 | 421 | 117/117 | 98.29% | 73/117 | 5 ok |  |
| 🚧 | update_row_event_display | 0x404cf0 | 836 | 213/213 | 99.53% | 102/213 | 37 ok |  |
| 🚧 | initialize_galaxy | 0x408cf0 | 1523 | 336/338 | 97.92% | 113/338 | 74 ok |  |
| 🚧 | run_frame_update | 0x40a2a0 | 485 | 135/135 | 97.78% | 18/135 | 23 ok |  |
| 🚧 | draw_textured_quad_immediate | 0x413030 | 1284 | 334/332 | 97.60% | 111/332 | 1 unresolved, 24 ok |  |
| 🚧 | initialize_high_score_entry | 0x417a70 | 120 | 40/40 | 97.50% | 26/40 | 3 ok |  |
| 🚧 | read_pressed_text_input_key_code | 0x432440 | 915 | 336/338 | 99.41% | 326/338 | 55 ok |  |
| 🚧 | read_repeating_text_input_key_code | 0x4327e0 | 1387 | 440/440 | 98.86% | 386/440 | 73 ok |  |
| 🚧 | spawn_track_garbage_hazard | 0x43da80 | 505 | 143/143 | 99.30% | 48/143 | 16 ok |  |
| 🚧 | update_ring_or_special_effect_particle | 0x43e780 | 174 | 55/55 | 96.36% | 28/55 | 5 ok |  |
| 🚧 | update_sprite_facing_angle | 0x44e410 | 304 | 86/86 | 97.67% | 36/86 | 8 ok |  |

## High Progress (80-94.99%) (51)

| | function | address | bytes | insns | match | prefix | masked | build |
|---|---|---|---|---|---|---|---|---|
| 🚧 | kill_border | 0x403360 | 90 | 31/30 | 88.52% | 18/30 | - |  |
| 🚧 | update_tooltip | 0x403c20 | 821 | 219/218 | 87.87% | 5/218 | 23 ok |  |
| 🚧 | initialize_default_runtime_config | 0x406c10 | 282 | 36/48 | 85.71% | 0/48 | 3 mismatch, 17 unresolved, 12 ok |  |
| 🚧 | game_window_proc | 0x4074b0 | 828 | 137/141 | 89.21% | 4/141 | 1 mismatch, 2 unresolved, 36 ok |  |
| 🚧 | construct_game_runtime | 0x407b60 | 1266 | 287/310 | 80.40% | 0/310 | 4 unresolved, 111 ok |  |
| 🚧 | render_backdrop | 0x411040 | 680 | 189/192 | 85.56% | 12/192 | 2 mismatch, 24 ok |  |
| 🚧 | initialize_d3d8_device | 0x411730 | 378 | 106/106 | 86.79% | 38/106 | 9 ok |  |
| 🚧 | set_blend_mode | 0x412d00 | 808 | 92/92 | 81.52% | 14/92 | 1 mismatch, 14 ok |  |
| 🚧 | spawn_golb_smoke | 0x415c60 | 278 | 69/72 | 82.27% | 34/72 | 8 ok |  |
| 🚧 | update_challenge_setup_screen | 0x416370 | 1166 | 354/355 | 80.68% | 8/355 | 2 unresolved, 33 ok |  |
| 🚧 | add_time_trial_high_score | 0x4178b0 | 143 | 49/49 | 83.67% | 20/49 | 1 ok |  |
| 🚧 | commit_high_score_entry_into_top_ten | 0x417af0 | 92 | 33/33 | 81.82% | 16/33 | - |  |
| 🚧 | initialize_loading_screen | 0x418b50 | 758 | 253/253 | 83.00% | 5/253 | 47 ok |  |
| 🚧 | update_loading_screen | 0x418e80 | 656 | 205/204 | 88.02% | 2/204 | 24 ok |  |
| 🚧 | destroy_intro_screen | 0x419920 | 184 | 59/61 | 80.00% | 14/61 | 4 ok |  |
| 🚧 | update_intro_logo_renderable | 0x419a90 | 148 | 41/42 | 81.93% | 8/42 | 6 ok |  |
| 🚧 | begin_track_attachment_follow_state | 0x420c40 | 98 | 28/27 | 94.55% | 23/27 | 3 ok |  |
| 🚧 | is_point_inside_track_attachment | 0x42ca90 | 348 | 112/111 | 87.89% | 15/111 | 6 ok |  |
| 🚧 | initialize_game_data_archive | 0x430e40 | 176 | 50/47 | 82.47% | 18/47 | 1 mismatch, 18 ok |  |
| 🚧 | load_file_bytes_fixed_size_from_archive_or_fs | 0x431030 | 536 | 192/188 | 81.05% | 9/188 | 32 ok |  |
| 🚧 | load_archive_index | 0x4319c0 | 187 | 67/67 | 92.54% | 40/67 | 13 ok | msvc6.5 /O2 /G5 /W3 /TC |
| 🚧 | register_sound_sample | 0x432f10 | 171 | 50/51 | 93.07% | 2/51 | 19 ok |  |
| 🚧 | initialize_track_render_cache_manager | 0x433060 | 436 | 122/122 | 93.44% | 3/122 | 18 ok |  |
| 🚧 | promote_track_tiles_to_fringe_variants | 0x4355f0 | 251 | 75/75 | 81.33% | 11/75 | 6 ok |  |
| 🚧 | select_track_tile_edge_variants | 0x435a80 | 692 | 220/220 | 94.55% | 14/220 | 18 ok |  |
| 🚧 | switch_track_mirror | 0x435e60 | 79 | 27/30 | 91.23% | 20/30 | 3 ok |  |
| 🚧 | destroy_sub_lazer_projectile | 0x439bc0 | 396 | 130/131 | 91.19% | 87/131 | 17 ok |  |
| 🚧 | update_player_movement_flags | 0x43a1a0 | 344 | 46/50 | 93.75% | 38/50 | 2 ok |  |
| 🚧 | update_jetpack_gauge | 0x43a390 | 490 | 130/131 | 85.82% | 4/131 | 34 ok |  |
| 🚧 | initialize_subgoldy | 0x43a9c0 | 1360 | 276/279 | 92.25% | 190/279 | 1 unresolved, 26 ok |  |
| 🚧 | play_movement_state_sound | 0x43afd0 | 335 | 96/88 | 89.13% | 26/88 | 19 ok |  |
| 🚧 | spawn_garbage_smoke_particle | 0x43d5a0 | 280 | 73/76 | 84.56% | 5/76 | 9 ok |  |
| 🚧 | spawn_slug_hazard | 0x43dc80 | 642 | 159/160 | 86.52% | 23/160 | 15 ok |  |
| 🚧 | update_ring_or_special_effect_parent | 0x43e830 | 1156 | 338/336 | 86.35% | 9/336 | 36 ok |  |
| 🚧 | update_garbage_hazard | 0x43f200 | 777 | 218/217 | 80.00% | 0/217 | 20 ok |  |
| 🚧 | deserialize_compact_high_score_record | 0x440020 | 335 | 114/114 | 92.98% | 80/114 | 1 ok |  |
| 🚧 | serialize_compact_high_score_record | 0x440170 | 326 | 109/109 | 85.32% | 60/109 | 1 ok |  |
| 🚧 | add_subgoldy_score | 0x4402c0 | 190 | 58/58 | 89.66% | 39/58 | 6 ok |  |
| 🚧 | display_score_stats | 0x4403c0 | 241 | 77/67 | 90.28% | 4/67 | 16 ok |  |
| 🚧 | update_damage_gauge | 0x440fd0 | 1043 | 268/268 | 80.60% | 6/268 | 58 ok |  |
| 🚧 | load_frontend_level_by_mode_and_index | 0x443650 | 220 | 61/57 | 81.36% | 5/57 | 1 mismatch, 11 ok |  |
| 🚧 | project_position_onto_track_attachment | 0x4444b0 | 333 | 101/106 | 81.16% | 15/106 | 5 ok |  |
| 🚧 | dispatch_cutscene_animation | 0x444600 | 221 | 54/55 | 88.07% | 2/55 | 3 ok |  |
| 🚧 | set_weapon_animation | 0x4446e0 | 221 | 54/55 | 88.07% | 2/55 | 3 ok |  |
| 🚧 | update_squidge | 0x4449c0 | 253 | 84/80 | 84.15% | 6/80 | 14 ok |  |
| 🚧 | update_cameraman | 0x4461d0 | 1274 | 322/322 | 92.55% | 36/322 | 1 mismatch, 72 ok |  |
| 🚧 | initialize_nuke | 0x447110 | 193 | 64/64 | 93.75% | 30/64 | 5 ok |  |
| 🚧 | update_nuke | 0x4471e0 | 169 | 59/59 | 89.83% | 4/59 | 8 ok |  |
| 🚧 | load_registered_sound_sample_from_bytes | 0x449960 | 59 | 18/18 | 88.89% | 13/18 | 4 ok |  |
| 🚧 | multiply_vector_by_matrix | 0x44cb90 | 135 | 40/40 | 85.00% | 2/40 | - |  |
| 🚧 | initialize_quaternion_from_matrix | 0x44d5d0 | 579 | 186/186 | 92.47% | 42/186 | 23 ok |  |

## Mid Progress (50-79.99%) (90)

| | function | address | bytes | insns | match | prefix | masked | build |
|---|---|---|---|---|---|---|---|---|
| 🚧 | initialize_frontend_sprite_button | 0x401a70 | 699 | 156/157 | 69.01% | 35/157 | 7 ok |  |
| 🚧 | layout_frontend_widget | 0x4024a0 | 741 | 174/177 | 78.06% | 21/177 | 20 ok |  |
| 🚧 | update_cheat | 0x404750 | 124 | 46/52 | 67.35% | 9/52 | 7 ok |  |
| 🚧 | match_cheat_text | 0x4047d0 | 85 | 43/42 | 68.24% | 12/42 | 2 ok |  |
| 🚧 | initialize_completion_screen | 0x404920 | 972 | 268/278 | 64.10% | 0/278 | 34 ok |  |
| 🚧 | rebuild_game_archive_if_needed | 0x405370 | 715 | 227/232 | 50.54% | 0/232 | 1 mismatch, 19 ok | msvc6.5 /O2 /G5 /W3 /TC |
| 🚧 | load_x_animation_clip | 0x405d60 | 754 | 225/228 | 69.32% | 3/228 | 3 unresolved, 42 ok |  |
| 🚧 | load_galaxy_layout | 0x4088e0 | 803 | 234/233 | 77.94% | 38/233 | 7 unresolved, 33 ok |  |
| 🚧 | update_galaxy | 0x4092f0 | 2051 | 550/566 | 61.11% | 6/566 | 9 unresolved, 34 ok |  |
| 🚧 | update_game_input | 0x40aab0 | 71 | 30/30 | 63.33% | 4/30 | 3 ok |  |
| 🚧 | select_level_track_texture_set | 0x410730 | 156 | 41/43 | 76.19% | 0/43 | 6 ok |  |
| 🚧 | update_frontend_state_machine | 0x4107d0 | 1116 | 176/180 | 71.35% | 12/180 | 1 mismatch, 53 ok |  |
| 🚧 | set_backdrop_distort | 0x410c40 | 261 | 69/73 | 50.70% | 3/73 | 14 ok |  |
| 🚧 | change_backdrop | 0x410d50 | 111 | 38/34 | 63.89% | 2/34 | - |  |
| 🚧 | update_backdrop | 0x4112f0 | 1029 | 66/67 | 72.18% | 0/67 | 6 ok |  |
| 🚧 | render_camera | 0x411fa0 | 685 | 182/180 | 70.17% | 0/180 | 1 mismatch, 34 ok |  |
| 🚧 | refresh_object_vertex_buffer | 0x412250 | 393 | 135/139 | 59.85% | 7/139 | 4 ok |  |
| 🚧 | render_object_toon | 0x4123e0 | 721 | 200/219 | 57.76% | 0/219 | 28 ok |  |
| 🚧 | render_object | 0x4126c0 | 815 | 197/196 | 69.72% | 8/196 | 21 ok |  |
| 🚧 | spawn_golb_impact_sprite | 0x415d80 | 159 | 43/45 | 63.64% | 3/45 | 3 ok |  |
| 🚧 | update_high_score_screen | 0x417260 | 731 | 203/205 | 67.65% | 0/205 | 29 ok |  |
| 🚧 | add_arcade_high_score | 0x4176a0 | 222 | 67/70 | 65.69% | 15/70 | 1 ok |  |
| 🚧 | add_survival_high_score | 0x417780 | 289 | 81/84 | 66.67% | 3/84 | 5 ok |  |
| 🚧 | update_new_game_menu | 0x417eb0 | 1064 | 265/273 | 63.94% | 41/273 | 32 ok |  |
| 🚧 | open_logo | 0x419110 | 195 | 64/60 | 69.35% | 2/60 | 13 ok |  |
| 🚧 | sample_smtrack_heightmap | 0x41a360 | 364 | 111/109 | 59.09% | 0/109 | 12 ok |  |
| 🚧 | initialize_backdrop_tile_quad | 0x41a4d0 | 1393 | 339/367 | 79.32% | 91/367 | 7 unresolved, 51 ok |  |
| 🚧 | apply_distort_to_object | 0x41aa50 | 648 | 198/197 | 52.15% | 3/197 | 23 ok |  |
| 🚧 | update_track_attachment_follow_state | 0x420cb0 | 2750 | 672/726 | 69.38% | 122/726 | 53 ok |  |
| 🚧 | calc_path_length_z | 0x4217b0 | 1551 | 398/425 | 55.41% | 0/425 | 7 ok |  |
| 🚧 | mirror_path_template_pair_x | 0x421dc0 | 1058 | 310/314 | 79.17% | 31/314 | 15 ok |  |
| 🚧 | finalize_path_template | 0x42c600 | 363 | 106/113 | 69.41% | 24/113 | 1 mismatch, 7 ok |  |
| 🚧 | try_enter_track_attachment_from_swept_motion | 0x42c770 | 800 | 202/204 | 79.80% | 16/204 | 36 ok |  |
| 🚧 | add_object_to_list | 0x42fad0 | 58 | 22/24 | 73.91% | 2/24 | 3 ok |  |
| 🚧 | calc_object_bounding_box | 0x42fb10 | 402 | 115/119 | 52.14% | 15/119 | 1 ok |  |
| 🚧 | calc_object_edges | 0x4308b0 | 433 | 141/141 | 71.63% | 0/141 | 3 mismatch, 10 ok |  |
| 🚧 | replace_object_list_texture_refs | 0x430d90 | 171 | 55/53 | 51.85% | 5/53 | 1 ok |  |
| 🚧 | find_archive_entry | 0x431250 | 122 | 61/60 | 66.12% | 7/60 | 2 ok | msvc6.5 /O2 /G5 /W3 /TC |
| 🚧 | load_file_bytes_from_archive_or_fs | 0x4312d0 | 577 | 211/206 | 65.71% | 10/206 | 31 ok |  |
| 🚧 | update_input_controller_pointer_region | 0x4321c0 | 466 | 141/134 | 53.09% | 0/134 | 26 ok |  |
| 🚧 | build_track_render_caches | 0x433220 | 2310 | 475/763 | 75.77% | 90/763 | 1 unresolved, 14 ok |  |
| 🚧 | remove_track_render_cache_bods | 0x433f20 | 156 | 57/58 | 52.17% | 7/58 | 4 ok |  |
| 🚧 | build_track_fringe_objects | 0x434be0 | 1428 | 476/495 | 53.76% | 3/495 | 47 ok |  |
| 🚧 | harmonize_center_lane_floor_slide_variants | 0x4356f0 | 911 | 225/226 | 58.98% | 9/226 | 4 mismatch, 20 ok |  |
| 🚧 | initialize_subgame | 0x4374b0 | 1632 | 385/396 | 63.25% | 1/396 | 6 mismatch, 5 unresolved, 63 ok |  |
| 🚧 | build_subgame_level | 0x437eb0 | 2128 | 555/555 | 79.82% | 177/555 | 2 unresolved, 100 ok |  |
| 🚧 | complete_subgame | 0x438700 | 323 | 90/88 | 75.28% | 7/88 | 8 ok |  |
| 🚧 | update_subgame | 0x438b90 | 3748 | 1046/1033 | 67.53% | 9/1033 | 2 unresolved, 108 ok |  |
| 🚧 | health_collect_particles | 0x43a010 | 386 | 98/104 | 66.34% | 1/104 | 11 ok |  |
| 🚧 | update_subgoldy | 0x43b120 | 8456 | 2067/2087 | 72.51% | 0/2087 | 291 ok |  |
| 🚧 | spawn_track_health_pickup | 0x43d6c0 | 441 | 122/122 | 72.95% | 16/122 | 7 ok |  |
| 🚧 | spawn_track_jetpack_pickup | 0x43d890 | 491 | 141/144 | 79.30% | 44/144 | 9 ok |  |
| 🚧 | spawn_track_ring_or_special_effect | 0x43df10 | 1376 | 223/347 | 51.23% | 22/347 | 8 mismatch, 34 ok |  |
| 🚧 | emit_ring_star_shower | 0x43e690 | 236 | 64/65 | 74.42% | 1/65 | 9 ok |  |
| 🚧 | update_track_health_pickup | 0x43ecc0 | 390 | 128/128 | 71.88% | 6/128 | 15 ok |  |
| 🚧 | update_track_jetpack_pickup | 0x43efb0 | 384 | 127/127 | 72.44% | 6/127 | 15 ok |  |
| 🚧 | explode_slug_hazard | 0x43f680 | 556 | 148/147 | 73.22% | 0/147 | 32 ok |  |
| 🚧 | update_slug_hazard_ai | 0x43f930 | 1772 | 434/464 | 66.15% | 0/464 | 1 mismatch, 1 unresolved, 47 ok |  |
| 🚧 | remove_subgame_bods | 0x440910 | 1644 | 494/501 | 59.90% | 6/501 | 2 mismatch, 58 ok |  |
| 🚧 | apply_damage_gauge_delta | 0x4413f0 | 322 | 95/94 | 60.32% | 0/94 | 1 mismatch, 13 ok |  |
| 🚧 | spawn_salt_hazard | 0x441560 | 236 | 68/67 | 74.07% | 0/67 | 8 ok |  |
| 🚧 | deactivate_sub_lazer_projectile | 0x441740 | 140 | 43/43 | 62.79% | 0/43 | 4 ok |  |
| 🚧 | update_salt_hazard | 0x441c10 | 301 | 79/83 | 62.96% | 5/83 | 1 mismatch, 9 ok |  |
| 🚧 | firework_shoot | 0x441dd0 | 390 | 99/103 | 78.22% | 4/103 | 21 ok |  |
| 🚧 | add_vapour_point | 0x442560 | 141 | 47/47 | 63.83% | 3/47 | - |  |
| 🚧 | initialize_cutscene | 0x4428d0 | 1385 | 329/339 | 73.95% | 1/339 | 42 ok |  |
| 🚧 | update_track_parcel | 0x4431d0 | 1148 | 260/312 | 60.14% | 0/312 | 1 mismatch, 32 ok |  |
| 🚧 | set_snail_jetpack | 0x445860 | 185 | 59/62 | 54.55% | 0/62 | 8 ok |  |
| 🚧 | update_snail_skin | 0x445cd0 | 128 | 43/44 | 57.47% | 6/44 | 1 ok |  |
| 🚧 | build_snail_hotspots | 0x445d50 | 208 | 72/74 | 60.27% | 9/74 | 2 mismatch, 5 ok |  |
| 🚧 | update_warning | 0x446f80 | 179 | 52/52 | 78.85% | 0/52 | 7 ok |  |
| 🚧 | copy_segment_definition_to_level_slot | 0x447300 | 379 | 119/125 | 54.10% | 42/125 | 5 ok |  |
| 🚧 | load_level_definition_file | 0x447480 | 3039 | 939/926 | 75.17% | 20/926 | 165 ok |  |
| 🚧 | load_builtin_segment_definitions | 0x448060 | 256 | 93/92 | 52.97% | 0/92 | - |  |
| 🚧 | initialize_tip | 0x448a40 | 511 | 158/154 | 75.00% | 16/154 | 24 ok |  |
| 🚧 | update_tip | 0x448c40 | 166 | 53/51 | 73.08% | 11/51 | 9 ok |  |
| 🚧 | initialize_voice_manager | 0x448ee0 | 960 | 249/269 | 61.78% | 4/269 | 56 ok |  |
| 🚧 | queue_font_text_instance | 0x44a790 | 277 | 79/73 | 61.84% | 1/73 | 19 ok |  |
| 🚧 | queue_axis_aligned_textured_quad | 0x44a8b0 | 249 | 67/65 | 69.70% | 3/65 | 13 ok |  |
| 🚧 | queue_axis_aligned_textured_quad_uv | 0x44a9b0 | 260 | 68/66 | 76.12% | 2/66 | 4 mismatch, 11 ok |  |
| 🚧 | queue_textured_quad_corners | 0x44aac0 | 274 | 71/69 | 64.29% | 3/69 | 2 mismatch, 11 ok |  |
| 🚧 | update_mouse | 0x44bc50 | 1012 | 294/295 | 73.68% | 5/295 | 1 mismatch, 9 unresolved, 61 ok |  |
| 🚧 | convert_mouse_screen_xy | 0x44c100 | 440 | 116/115 | 74.46% | 3/115 | 32 ok |  |
| 🚧 | initialize_quaternion_from_axis | 0x44d530 | 74 | 28/26 | 77.78% | 9/26 | 4 ok |  |
| 🚧 | initialize_matrix_from_quaternion | 0x44d820 | 247 | 85/82 | 73.05% | 10/82 | 3 ok |  |
| 🚧 | interpolate_matrix_rotation | 0x44d920 | 367 | 112/105 | 71.89% | 30/105 | 2 mismatch, 12 ok |  |
| 🚧 | linear_interpolate_matrix | 0x44da90 | 195 | 51/61 | 51.79% | 0/61 | 6 ok |  |
| 🚧 | play_sound_effect_at_position | 0x44dce0 | 251 | 57/66 | 61.79% | 0/66 | 10 ok |  |
| 🚧 | initialize_sprite_manager | 0x44e160 | 148 | 46/45 | 50.55% | 6/45 | 1 ok |  |
| 🚧 | get_or_create_texture_ref | 0x44e810 | 227 | 85/78 | 76.07% | 16/78 | 4 ok |  |

## Early Progress (>0-49.99%) (51)

| | function | address | bytes | insns | match | prefix | masked | build |
|---|---|---|---|---|---|---|---|---|
| 🚧 | classify_archive_entry_extension | 0x4050c0 | 114 | 45/46 | 26.37% | 0/46 | - |  |
| 🚧 | load_x_mesh | 0x405640 | 1603 | 475/492 | 46.74% | 10/492 | 4 mismatch, 67 ok |  |
| 🚧 | render_game_frame | 0x40a490 | 1460 | 422/439 | 35.31% | 3/439 | 21 ok |  |
| 🚧 | update_input | 0x40aa80 | 44 | 16/19 | 34.29% | 1/19 | - |  |
| 🚧 | get_or_append_object_texture_group_vertex | 0x413bb0 | 411 | 126/127 | 45.85% | 16/127 | 8 ok |  |
| 🚧 | build_object_texture_group_buffers | 0x413d50 | 1149 | 330/373 | 20.20% | 0/373 | 21 ok |  |
| 🚧 | update_golb_ai | 0x414820 | 2656 | 646/694 | 49.85% | 9/694 | 1 mismatch, 52 ok |  |
| 🚧 | create_golb | 0x415280 | 2349 | 445/582 | 30.96% | 3/582 | 1 mismatch, 31 ok |  |
| 🚧 | sort_object_faces_by_texture_group | 0x419fd0 | 220 | 74/75 | 41.61% | 1/75 | - |  |
| 🚧 | build_track_fringe_mesh | 0x4246a0 | 1069 | 281/318 | 42.07% | 0/318 | 17 ok |  |
| 🚧 | build_track_fringe_supertramp_mesh | 0x424ad0 | 1396 | 303/421 | 17.13% | 0/421 | 17 ok |  |
| 🚧 | get_path_position_at_node | 0x42b9c0 | 185 | 51/56 | 41.12% | 8/56 | - |  |
| 🚧 | calc_object_facequad_normals | 0x42fcb0 | 1397 | 392/437 | 17.13% | 0/437 | 1 mismatch, 11 ok |  |
| 🚧 | calc_object_facequad_normals_simple | 0x430230 | 441 | 131/139 | 10.37% | 0/139 | 2 mismatch |  |
| 🚧 | calc_object_texture_groups | 0x4303f0 | 127 | 56/55 | 28.83% | 5/55 | - |  |
| 🚧 | add_object_edge | 0x4305a0 | 772 | 201/227 | 39.72% | 0/227 | 1 mismatch, 11 ok |  |
| 🚧 | request_object_animation | 0x430a70 | 793 | 220/231 | 41.24% | 0/231 | 1 mismatch, 1 unresolved, 13 ok |  |
| 🚧 | enumerate_matching_archive_or_fs_entries | 0x431740 | 570 | 189/182 | 49.60% | 0/182 | 23 ok | msvc6.5 /O2 /G5 /W3 /TC |
| 🚧 | strings_equal_case_insensitive | 0x431dc0 | 104 | 53/50 | 29.13% | 5/50 | - |  |
| 🚧 | parse_next_float32 | 0x431f20 | 173 | 72/64 | 44.12% | 0/64 | 9 ok |  |
| 🚧 | initialize_star_field | 0x434310 | 861 | 179/247 | 34.74% | 0/247 | 25 ok |  |
| 🚧 | update_star_positions | 0x434800 | 860 | 101/106 | 32.85% | 1/106 | 11 ok |  |
| 🚧 | merge_track_tile_runs | 0x435180 | 873 | 275/276 | 21.78% | 0/276 | 8 ok |  |
| 🚧 | mark_track_warning_zones | 0x4354f0 | 251 | 105/99 | 36.27% | 0/99 | - |  |
| 🚧 | populate_runtime_track_cells_from_segments | 0x435eb0 | 5042 | 1190/1245 | 28.25% | 0/1245 | 1 unresolved, 57 ok |  |
| 🚧 | wall2_emitter_maybe_fire_sub_lazer | 0x439d50 | 702 | 172/187 | 42.34% | 0/187 | 26 ok |  |
| 🚧 | update_jet_particles | 0x43a690 | 670 | 169/181 | 45.14% | 0/181 | 1 mismatch, 12 ok |  |
| 🚧 | update_sub_lazer_projectile | 0x4417d0 | 768 | 216/218 | 48.39% | 0/218 | 17 ok |  |
| 🚧 | shoot_subgoldy | 0x441ad0 | 154 | 45/48 | 49.46% | 0/48 | 3 ok |  |
| 🚧 | update_click_start | 0x442290 | 624 | 149/138 | 27.18% | 1/138 | 13 ok |  |
| 🚧 | update_vapour | 0x4425f0 | 726 | 180/227 | 28.50% | 0/227 | - |  |
| 🚧 | release_snail_weapons | 0x442e40 | 554 | 97/125 | 49.55% | 0/125 | 28 ok |  |
| 🚧 | place_parcels_on_track | 0x4438e0 | 2396 | 646/639 | 26.30% | 0/639 | 5 mismatch, 26 ok |  |
| 🚧 | place_challenge_parcels_on_track | 0x444240 | 617 | 178/171 | 44.70% | 0/171 | 1 unresolved, 18 ok |  |
| 🚧 | update_anim_manager | 0x4447d0 | 399 | 129/134 | 47.91% | 2/134 | 13 ok |  |
| 🚧 | handle_subgoldy_collisions | 0x444cf0 | 2887 | 648/673 | 47.99% | 0/673 | 1 mismatch, 77 ok |  |
| 🚧 | set_snail_weapon | 0x445920 | 940 | 244/248 | 39.43% | 1/248 | 2 mismatch, 1 unresolved, 14 ok |  |
| 🚧 | update_cutscene | 0x4466d0 | 1888 | 480/505 | 46.29% | 0/505 | 1 mismatch, 2 unresolved, 33 ok |  |
| 🚧 | load_segment_definitions | 0x448160 | 1937 | 531/571 | 45.01% | 5/571 | 8 mismatch, 65 ok |  |
| 🚧 | measure_font_text_width | 0x449e90 | 182 | 45/60 | 22.86% | 0/60 | 1 ok |  |
| 🚧 | register_font_texture_sheet | 0x449f50 | 1031 | 230/274 | 27.78% | 0/274 | 18 ok |  |
| 🚧 | draw_font_text_instance | 0x44a360 | 867 | 224/272 | 32.66% | 0/272 | 18 ok |  |
| 🚧 | layout_and_queue_wrapped_font_text | 0x44abe0 | 548 | 146/155 | 39.87% | 0/155 | 8 ok |  |
| 🚧 | initialize_font3d_objects | 0x44ae10 | 1444 | 94/126 | 40.00% | 3/126 | 1 unresolved, 8 ok |  |
| 🚧 | load_object_definition | 0x44c420 | 1109 | 300/325 | 44.80% | 0/325 | 5 mismatch, 36 ok |  |
| 🚧 | find_case_insensitive_substring | 0x44e600 | 130 | 77/63 | 25.71% | 0/63 | 2 ok |  |
| 🚧 | parse_next_signed_int | 0x44e710 | 107 | 50/47 | 28.87% | 0/47 | - |  |
| 🚧 | sample_tga_pixel_rgb | 0x44e780 | 119 | 38/49 | 25.29% | 0/49 | - |  |
| 🚧 | initialize_translation_matrix | 0x44fd90 | 92 | 23/34 | 7.02% | 1/34 | - |  |
| 🚧 | build_perspective_projection_matrix | 0x450314 | 6085 | 38/54 | 26.09% | 2/54 | 1 ok | msvc6.5 /O2 /Oy- /G5 /W3 |
| 🚧 | build_camera_view_matrix | 0x451ad9 | 328 | 119/130 | 28.11% | 0/130 | 2 ok |  |

## No Scratch (0%) (40)

| | function | address | bytes | insns | match | prefix | masked | build |
|---|---|---|---|---|---|---|---|---|
| ⬜ | draw_frontend_widget | 0x401130 | 2353 | 0/712 | 0.00% | 0/712 | - |  |
| ⬜ | initialize_frontend_widget | 0x401d30 | 1892 | 0/429 | 0.00% | 0/429 | - |  |
| ⬜ | update_frontend_widget_interaction | 0x402820 | 2677 | 0/647 | 0.00% | 0/647 | - |  |
| ⬜ | border_input_text | 0x4035b0 | 1581 | 0/446 | 0.00% | 0/446 | - |  |
| ⬜ | initialize_exit_prompt | 0x4060d0 | 1804 | 0/441 | 0.00% | 0/441 | - |  |
| ⬜ | game_startup_and_main_loop | 0x406dc0 | 1316 | 0/325 | 0.00% | 0/325 | - |  |
| ⬜ | initialize_game_assets_and_world | 0x40acf0 | 23070 | 0/5411 | 0.00% | 0/5411 | - |  |
| ⬜ | initialize_game_window_and_input | 0x4119d0 | 938 | 0/287 | 0.00% | 0/287 | - |  |
| ⬜ | initialize_high_score_screen | 0x416910 | 2311 | 0/600 | 0.00% | 0/600 | - |  |
| ⬜ | load_landscape_script_by_name | 0x4182f0 | 1404 | 0/386 | 0.00% | 0/386 | - |  |
| ⬜ | initialize_intro_screen | 0x4191e0 | 1851 | 0/521 | 0.00% | 0/521 | - |  |
| ⬜ | initialize_looptheloop_path_template_pair | 0x41b0f0 | 2630 | 0/721 | 0.00% | 0/721 | - |  |
| ⬜ | initialize_looptheloopw_path_template_pair | 0x41bb40 | 2725 | 0/745 | 0.00% | 0/745 | - |  |
| ⬜ | initialize_loopout_path_template_pair | 0x41c5f0 | 2615 | 0/718 | 0.00% | 0/718 | - |  |
| ⬜ | initialize_hump_path_template_pair | 0x41d030 | 2553 | 0/685 | 0.00% | 0/685 | - |  |
| ⬜ | initialize_dump_path_template_pair | 0x41da30 | 2563 | 0/690 | 0.00% | 0/690 | - |  |
| ⬜ | initialize_dip_path_template_pair | 0x41e440 | 2390 | 0/655 | 0.00% | 0/655 | - |  |
| ⬜ | initialize_screw_path_template_pair | 0x41eda0 | 2495 | 0/685 | 0.00% | 0/685 | - |  |
| ⬜ | initialize_slalom_path_template_pair | 0x41f760 | 2564 | 0/696 | 0.00% | 0/696 | - |  |
| ⬜ | initialize_worm_path_template_pair | 0x420170 | 2759 | 0/736 | 0.00% | 0/736 | - |  |
| ⬜ | initialize_slalombig_path_template_pair | 0x4221f0 | 2564 | 0/696 | 0.00% | 0/696 | - |  |
| ⬜ | initialize_sweep_path_template_pair | 0x422c00 | 2428 | 0/652 | 0.00% | 0/652 | - |  |
| ⬜ | initialize_snake_path_template_pair | 0x423580 | 2436 | 0/652 | 0.00% | 0/652 | - |  |
| ⬜ | initialize_supertramp_path_template_pair | 0x423f10 | 1935 | 0/552 | 0.00% | 0/552 | - |  |
| ⬜ | initialize_slalomdouble_path_template_pair | 0x425050 | 2536 | 0/683 | 0.00% | 0/683 | - |  |
| ⬜ | initialize_p_path_template_pair | 0x425a40 | 2482 | 0/679 | 0.00% | 0/679 | - |  |
| ⬜ | initialize_start_path_template_pair | 0x426400 | 2223 | 0/610 | 0.00% | 0/610 | - |  |
| ⬜ | initialize_turnover_path_template_pair | 0x426cb0 | 2433 | 0/671 | 0.00% | 0/671 | - |  |
| ⬜ | initialize_turnoverdouble_path_template_pair | 0x427640 | 2458 | 0/680 | 0.00% | 0/680 | - |  |
| ⬜ | initialize_turnunder_path_template_pair | 0x427fe0 | 2487 | 0/687 | 0.00% | 0/687 | - |  |
| ⬜ | initialize_wibble_path_template_pair | 0x4289a0 | 2213 | 0/608 | 0.00% | 0/608 | - |  |
| ⬜ | initialize_invert_path_template_pair | 0x429250 | 2182 | 0/600 | 0.00% | 0/600 | - |  |
| ⬜ | initialize_kind42_path_template_pair | 0x429b20 | 2592 | 0/707 | 0.00% | 0/707 | - |  |
| ⬜ | initialize_twister_path_template_pair | 0x42a540 | 2540 | 0/677 | 0.00% | 0/677 | - |  |
| ⬜ | initialize_twister2_path_template_pair | 0x42af30 | 2540 | 0/677 | 0.00% | 0/677 | - |  |
| ⬜ | initialize_loopbow_path_template_pair | 0x42ba80 | 2939 | 0/796 | 0.00% | 0/796 | - |  |
| ⬜ | initialize_toad_path_template_pair | 0x42cbf0 | 2419 | 0/663 | 0.00% | 0/663 | - |  |
| ⬜ | initialize_hill_valley_path_template_pair | 0x42d570 | 2447 | 0/668 | 0.00% | 0/668 | - |  |
| ⬜ | initialize_sbend_path_template_pair | 0x42df00 | 2068 | 0/579 | 0.00% | 0/579 | - |  |
| ⬜ | initialize_cage2_path_template_pair | 0x42e720 | 3397 | 0/1029 | 0.00% | 0/1029 | - |  |

## Type Consolidation

This is generated as part of `uv run snail match status --write tools/match/STATUS.md`. Keep types scratch-local until multiple scratches agree, then promote deliberately; divergent names are semantic debt, not merge candidates.
Run `uv run snail match types --paths` for the full path-level report.

- ready: 9 type name(s)
- covered: 40 type name(s) with a header plus scratch-local copies
- divergent: 26 type name(s) with multiple scratch-local shapes

| status | type | scratch | header | signatures | recommendation |
|---|---|---:|---:|---:|---|
| divergent | Vec3 | 10 | 0 | 9 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | Direct3DDevice8Vtbl | 8 | 0 | 7 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | LoadingScreen | 6 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | SelectedLevelRecord | 5 | 0 | 5 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | TrackedAllocationStack | 5 | 0 | 5 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | Quaternion | 5 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | ObjectVertexBufferVtbl | 5 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | Direct3DRenderer | 4 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | GalaxyRouteRecord | 4 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | GameRoot | 4 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | RuntimeSlot | 4 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | SlugVoiceManager | 4 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | RuntimeCallback | 4 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | BlinkRandomTable | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | VertexBufferVtbl | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | BorderRuntime | 3 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | GalaxyRouteNameRecord | 3 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | ActiveBod | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | AppShell | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | Axis | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | CachedXMeshBank | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | GameRuntime | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | LevelSegmentSlotStore | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | ProgressBar | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | ScoreStats | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | Twinkle | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| covered | Game | 42 | 1 | 42 | header exists; consider replacing matching scratch-local copies with includes |
| covered | GalaxyRoute | 8 | 1 | 8 | header exists; consider replacing matching scratch-local copies with includes |
| covered | Player | 7 | 1 | 7 | header exists; consider replacing matching scratch-local copies with includes |
| covered | BorderManager | 6 | 3 | 4 | header exists; consider replacing matching scratch-local copies with includes |
| covered | FrontendWidget | 4 | 1 | 4 | header exists; consider replacing matching scratch-local copies with includes |
| covered | Direct3DDevice8 | 4 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | MouseCursorState | 3 | 1 | 3 | header exists; consider replacing matching scratch-local copies with includes |
| covered | VoiceManager | 3 | 1 | 3 | header exists; consider replacing matching scratch-local copies with includes |
| covered | PlayerPresentationController | 3 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | SoundEffectManager | 3 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | AttachmentPathTemplate | 2 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | FollowState | 2 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | FrontendFade | 2 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | GolbShot | 2 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | HighScoreScreen | 2 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | LevelDefinitionLoader | 2 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | TimerCounters | 2 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | TrackRowCell | 2 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | TutorialController | 2 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | AttachmentSample | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | Backdrop | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | BodList | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | CutsceneAI | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | DamageGaugeController | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | GolbPathBank | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | HelpScreen | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | LandscapeScriptBank | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | MainMenu | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | NewGameMenu | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | OptionsMenu | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | PauseMenu | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | PlayerControlSource | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | SaltHazardPool | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | Sprite | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | StarField | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | SubLazerPool | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | TipManager | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | TooltipState | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | TrackParcelPool | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | WarningActor | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| ready | ArchiveEntry | 5 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | ArchiveIndex | 5 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | TimeTrialStringFormatter | 3 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | VertexBuffer | 3 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | IntroRenderableSlot | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | IntroScreenRuntime | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | LoadingVertex | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | Rect | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | RendererState | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
