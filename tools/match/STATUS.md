# Matching Status

Regenerate with `uv run snail match status --write tools/match/STATUS.md`.

**284/665** mapped gameplay functions matched, **18512/326119** bytes (**5.7%**). Byte totals are curated-extent upper bounds: uncurated code between manifest functions counts toward the preceding extent.

| | function | address | bytes | insns | match | prefix | masked | build |
|---|---|---|---|---|---|---|---|---|
| ✅ | initialize_array_with_constructor | 0x401000 | 42 | 21/21 | 100.00% | 21/21 | - |  |
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
| ✅ | reset_tooltip | 0x403be0 | 51 | 16/16 | 100.00% | 16/16 | 2 ok |  |
| ✅ | update_twinkle_manager | 0x404030 | 53 | 23/23 | 100.00% | 23/23 | 1 ok |  |
| ✅ | draw_twinkle | 0x404070 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  |
| ✅ | border_sprite_extend | 0x404540 | 55 | 14/14 | 100.00% | 14/14 | - |  |
| ✅ | set_border_justify_centre | 0x404730 | 13 | 3/3 | 100.00% | 3/3 | - |  |
| ✅ | initialize_cheat | 0x404740 | 11 | 5/5 | 100.00% | 5/5 | - |  |
| 🚧 | flush_row_event_display | 0x404830 | 233 | 65/67 | 89.39% | 4/67 | 18 ok |  |
| 🚧 | update_row_event_display | 0x404cf0 | 836 | 213/213 | 99.53% | 102/213 | 1 mismatch, 36 ok |  |
| ✅ | register_parcel_delivery | 0x405040 | 114 | 36/36 | 100.00% | 36/36 | 10 ok |  |
| ✅ | file_exists | 0x405140 | 37 | 14/14 | 100.00% | 14/14 | 3 ok |  |
| ✅ | get_stream_length_preserve_position | 0x405170 | 51 | 24/24 | 100.00% | 24/24 | 4 ok |  |
| ✅ | load_file_bytes_allocating | 0x4051b0 | 21 | 8/8 | 100.00% | 8/8 | 1 ok |  |
| ✅ | scramble_archive_bytes_in_place | 0x405270 | 48 | 25/25 | 100.00% | 25/25 | - |  |
| ✅ | delete_file_path | 0x405340 | 12 | 5/5 | 100.00% | 5/5 | 1 ok |  |
| ✅ | toggle_archive_high_bit_in_place | 0x405350 | 24 | 11/11 | 100.00% | 11/11 | - |  |
| ✅ | initialize_directx_loader | 0x405c90 | 45 | 13/13 | 100.00% | 13/13 | 3 ok |  |
| ✅ | destroy_completion_screen | 0x406060 | 98 | 25/25 | 100.00% | 25/25 | 9 ok |  |
| ✅ | consume_mouse_wheel_delta | 0x4077f0 | 23 | 4/4 | 100.00% | 4/4 | 2 ok |  |
| ✅ | read_left_mouse_button_state | 0x407810 | 18 | 4/4 | 100.00% | 4/4 | 2 ok |  |
| ✅ | read_right_mouse_button_state | 0x407830 | 18 | 4/4 | 100.00% | 4/4 | 2 ok |  |
| ✅ | snapshot_current_display_mode | 0x407850 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  |
| ✅ | restore_desktop_display_mode | 0x407860 | 19 | 6/6 | 100.00% | 6/6 | 2 ok |  |
| ✅ | probe_display_mode_count | 0x407880 | 40 | 17/17 | 100.00% | 17/17 | 1 ok |  |
| ✅ | read_current_display_resolution | 0x4078b0 | 351 | 22/22 | 100.00% | 22/22 | 1 ok |  |
| ✅ | noop_runtime_ai | 0x407b50 | 1 | 1/1 | 100.00% | 1/1 | - |  |
| ✅ | initialize_track_speedup_runtime | 0x4084b0 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_track_jetpack_pickup_runtime | 0x4084d0 | 55 | 17/17 | 100.00% | 17/17 | 6 ok |  |
| ✅ | initialize_track_health_pickup_runtime | 0x408510 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_slug_hazard_runtime | 0x408530 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_garbage_hazard | 0x408550 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_track_ring_or_special_effect_runtime | 0x408570 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_track_row_runtime | 0x408590 | 36 | 13/13 | 100.00% | 13/13 | 3 ok |  |
| ✅ | initialize_path_template_record_pair | 0x4085c0 | 26 | 9/9 | 100.00% | 9/9 | 3 ok |  |
| ✅ | initialize_active_bod | 0x4085e0 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_sub_lazer_runtime | 0x408610 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_salt_hazard_runtime | 0x408630 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_fringe_object | 0x408650 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_enemy_manager_runtime | 0x4086d0 | 322 | 79/79 | 100.00% | 79/79 | 27 ok |  |
| ✅ | initialize_active_landscape_entry | 0x408820 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_track_parcel_runtime | 0x408860 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  |
| ✅ | initialize_bod | 0x4088c0 | 29 | 10/10 | 100.00% | 10/10 | 4 ok |  |
| ✅ | initialize_overlay | 0x40a240 | 70 | 17/17 | 100.00% | 17/17 | 3 ok |  |
| ✅ | noop_runtime_callback | 0x40a290 | 3 | 1/1 | 100.00% | 1/1 | - |  |
| 🚧 | run_frame_update | 0x40a2a0 | 485 | 135/135 | 97.78% | 18/135 | 23 ok |  |
| ✅ | initialize_input | 0x40aa50 | 45 | 12/12 | 100.00% | 12/12 | - |  |
| ✅ | initialize_frontend_overlay_color_lerp | 0x40ab00 | 63 | 18/18 | 100.00% | 18/18 | 2 ok |  |
| ✅ | begin_frontend_fade_out | 0x40abc0 | 23 | 5/5 | 100.00% | 5/5 | - |  |
| ✅ | begin_frontend_fade_in | 0x40abe0 | 14 | 3/3 | 100.00% | 3/3 | - |  |
| ✅ | initialize_distort | 0x410710 | 11 | 5/5 | 100.00% | 5/5 | - |  |
| ✅ | initialize_game_last | 0x410720 | 14 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| 🚧 | update_frontend_state_machine | 0x4107d0 | 1116 | 176/180 | 71.35% | 12/180 | 1 mismatch, 53 ok |  |
| ✅ | set_backdrop_progress_fraction | 0x410c30 | 13 | 3/3 | 100.00% | 3/3 | - |  |
| ✅ | set_backdrop_texture_target | 0x410f40 | 79 | 14/14 | 100.00% | 14/14 | 2 ok |  |
| ✅ | configure_sprite_render_state | 0x413670 | 370 | 109/109 | 100.00% | 109/109 | 18 ok |  |
| ✅ | draw_sprite_quad | 0x4137f0 | 951 | 259/259 | 100.00% | 259/259 | 29 ok |  |
| ✅ | kill_golb | 0x414670 | 418 | 132/132 | 100.00% | 132/132 | 16 ok |  |
| 🚧 | update_golb_ai | 0x414820 | 2656 | 646/694 | 49.85% | 9/694 | 1 mismatch, 52 ok |  |
| 🚧 | create_golb | 0x415280 | 2349 | 445/582 | 28.63% | 3/582 | 1 mismatch, 31 ok |  |
| ✅ | spawn_golb_trail_sprite | 0x415bb0 | 161 | 47/47 | 100.00% | 47/47 | 2 ok |  |
| 🚧 | spawn_golb_smoke | 0x415c60 | 278 | 69/72 | 82.27% | 34/72 | 8 ok |  |
| 🚧 | spawn_golb_impact_sprite | 0x415d80 | 159 | 43/45 | 54.55% | 3/45 | 3 ok |  |
| ✅ | initialize_enemy_manager | 0x415e20 | 7 | 2/2 | 100.00% | 2/2 | - |  |
| ✅ | search_path_for_golb | 0x415e30 | 192 | 63/63 | 100.00% | 63/63 | 3 ok |  |
| ✅ | append_subgame_contact_target | 0x415ef0 | 88 | 34/34 | 100.00% | 34/34 | - |  |
| ✅ | destroy_help_screen | 0x4168c0 | 16 | 3/3 | 100.00% | 3/3 | 2 ok |  |
| ✅ | destroy_high_score_screen | 0x417220 | 52 | 11/11 | 100.00% | 11/11 | 5 ok |  |
| 🚧 | add_time_trial_high_score | 0x4178b0 | 143 | 49/49 | 83.67% | 20/49 | 1 ok |  |
| ✅ | reset_landscape_manager | 0x4182e0 | 11 | 2/2 | 100.00% | 2/2 | - |  |
| ✅ | destroy_main_menu | 0x419b30 | 26 | 5/5 | 100.00% | 5/5 | 4 ok |  |
| ✅ | initialize_duplicate_vertices | 0x419f50 | 39 | 13/13 | 100.00% | 13/13 | 2 ok |  |
| ✅ | apply_audio_config_volumes | 0x41b070 | 43 | 11/11 | 100.00% | 11/11 | 7 ok |  |
| ✅ | allocate_path_template_samples | 0x41b0a0 | 72 | 23/23 | 100.00% | 23/23 | 4 ok |  |
| 🚧 | begin_track_attachment_follow_state | 0x420c40 | 98 | 28/27 | 94.55% | 23/27 | 3 ok |  |
| 🚧 | update_track_attachment_follow_state | 0x420cb0 | 2750 | 678/726 | 46.44% | 0/726 | 45 ok |  |
| ✅ | initialize_path_follow_golb | 0x421770 | 58 | 16/16 | 100.00% | 16/16 | 1 ok |  |
| 🚧 | calc_path_length_z | 0x4217b0 | 1551 | 408/425 | 40.58% | 0/425 | 7 ok |  |
| ✅ | find_segment_path_index_by_name | 0x429ae0 | 59 | 27/27 | 100.00% | 27/27 | 3 ok |  |
| ✅ | compute_kind42_attachment_transform | 0x42b920 | 146 | 48/48 | 100.00% | 48/48 | 8 ok |  |
| 🚧 | get_path_position_at_node | 0x42b9c0 | 185 | 51/56 | 41.12% | 8/56 | - |  |
| 🚧 | try_enter_track_attachment_from_swept_motion | 0x42c770 | 800 | 202/204 | 79.80% | 16/204 | 36 ok |  |
| ✅ | load_config_file | 0x42f470 | 23 | 9/9 | 100.00% | 9/9 | 1 ok |  |
| ✅ | set_bod_object | 0x42f5d0 | 18 | 6/6 | 100.00% | 6/6 | - |  |
| ✅ | initialize_bod_base | 0x42f5f0 | 87 | 27/27 | 100.00% | 27/27 | 5 ok |  |
| ✅ | initialize_renderable_bod | 0x42f650 | 33 | 10/10 | 100.00% | 10/10 | 3 ok |  |
| ✅ | apply_bod_position | 0x42f680 | 89 | 39/39 | 100.00% | 39/39 | 1 ok |  |
| ✅ | initialize_object | 0x42f6f0 | 24 | 9/9 | 100.00% | 9/9 | - |  |
| ✅ | request_object_vertices | 0x42f710 | 114 | 37/37 | 100.00% | 37/37 | 8 ok |  |
| ✅ | request_object_vertices_copy | 0x42f7d0 | 38 | 14/14 | 100.00% | 14/14 | 3 ok |  |
| ✅ | request_object_facequad_normals | 0x42f800 | 71 | 26/26 | 100.00% | 26/26 | 4 ok |  |
| ✅ | request_object_vertex_colours | 0x42f850 | 77 | 30/30 | 100.00% | 30/30 | 2 ok |  |
| ✅ | request_object_facequads | 0x42f8c0 | 108 | 40/40 | 100.00% | 40/40 | 5 ok |  |
| 🚧 | request_object_texture_groups | 0x42f930 | 82 | 29/29 | 96.55% | 18/29 | 4 ok |  |
| ✅ | request_object_edges | 0x430570 | 44 | 16/16 | 100.00% | 16/16 | 2 ok |  |
| ✅ | uninitialize_game_data_archive | 0x430ef0 | 49 | 13/13 | 100.00% | 13/13 | 6 ok |  |
| ✅ | load_file_bytes | 0x431520 | 21 | 8/8 | 100.00% | 8/8 | 1 ok |  |
| ✅ | is_archive_index_loaded | 0x431a80 | 11 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| ✅ | get_archive_data_base | 0x431a90 | 6 | 2/2 | 100.00% | 2/2 | 1 ok |  |
| ✅ | get_archive_data_end | 0x431aa0 | 11 | 3/3 | 100.00% | 3/3 | 1 ok |  |
| ✅ | get_tracked_allocation_size | 0x431ab0 | 61 | 26/26 | 100.00% | 26/26 | 2 ok |  |
| ✅ | free_tracked_allocations_to_mark | 0x431c70 | 53 | 15/15 | 100.00% | 15/15 | 6 ok |  |
| ✅ | set_tracked_allocation_mark | 0x431cb0 | 11 | 3/3 | 100.00% | 3/3 | 2 ok |  |
| ✅ | copy_c_string | 0x431da0 | 21 | 10/10 | 100.00% | 10/10 | - |  |
| ✅ | skip_to_next_line | 0x431e30 | 29 | 13/13 | 100.00% | 13/13 | - |  |
| ✅ | append_c_string | 0x431e50 | 42 | 19/19 | 100.00% | 19/19 | - |  |
| ✅ | parse_next_space_delimited_token | 0x431e80 | 60 | 27/27 | 100.00% | 27/27 | - |  |
| ✅ | parse_next_int32 | 0x431ec0 | 89 | 39/39 | 100.00% | 39/39 | - |  |
| ✅ | set_input_controller_slot0_button_axes | 0x431fd0 | 30 | 7/7 | 100.00% | 7/7 | 3 ok |  |
| ✅ | update_active_bod | 0x433e80 | 147 | 50/50 | 100.00% | 50/50 | 7 ok |  |
| ✅ | open_thanks_screen | 0x433fc0 | 13 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| ✅ | uninit_thanks_screen | 0x4340c0 | 38 | 8/8 | 100.00% | 8/8 | 3 ok |  |
| ✅ | hide_star_field | 0x434670 | 50 | 23/23 | 100.00% | 23/23 | - |  |
| ✅ | unhide_star_field | 0x4346b0 | 50 | 23/23 | 100.00% | 23/23 | - |  |
| 🚧 | is_neighbor_cell_solid | 0x434b60 | 127 | 46/47 | 68.82% | 11/47 | 2 ok |  |
| 🚧 | build_track_fringe_objects | 0x434be0 | 1428 | 484/495 | 49.44% | 3/495 | 47 ok |  |
| 🚧 | mark_track_warning_zones | 0x4354f0 | 251 | 104/99 | 32.51% | 0/99 | - |  |
| ✅ | build_track_colours | 0x435d40 | 161 | 37/37 | 100.00% | 37/37 | 24 ok |  |
| ✅ | set_subgame_features | 0x435df0 | 76 | 19/19 | 100.00% | 19/19 | 3 ok |  |
| 🚧 | switch_track_mirror | 0x435e60 | 79 | 27/30 | 91.23% | 20/30 | 3 ok |  |
| 🚧 | populate_runtime_track_cells_from_segments | 0x435eb0 | 5042 | 935/1245 | 18.90% | 0/1245 | 1 unresolved, 46 ok |  |
| ✅ | rebuild_track_runtime_from_segments | 0x437de0 | 145 | 44/44 | 100.00% | 44/44 | 13 ok |  |
| ✅ | calc_slider_to_rate | 0x437e80 | 45 | 11/11 | 100.00% | 11/11 | 4 ok |  |
| 🚧 | complete_subgame | 0x438700 | 323 | 90/88 | 75.28% | 7/88 | 8 ok |  |
| ✅ | is_slide_cache_tile_family | 0x439a40 | 33 | 17/17 | 100.00% | 17/17 | - |  |
| ✅ | is_ramp_cache_tile_family | 0x439a70 | 57 | 29/29 | 100.00% | 29/29 | - |  |
| ✅ | is_open_neighbor_tile_family | 0x439ab0 | 29 | 15/15 | 100.00% | 15/15 | - |  |
| ✅ | is_floor_cache_tile_family | 0x439ad0 | 41 | 21/21 | 100.00% | 21/21 | - |  |
| ✅ | refresh_fringe_object_draw_list | 0x439b00 | 186 | 63/63 | 100.00% | 63/63 | 8 ok |  |
| 🚧 | wall2_emitter_maybe_fire_sub_lazer | 0x439d50 | 702 | 172/187 | 42.34% | 0/187 | 26 ok |  |
| 🚧 | update_player_movement_flags | 0x43a1a0 | 344 | 46/50 | 93.75% | 38/50 | 2 ok |  |
| ✅ | update_movement_flag_emitters | 0x43a300 | 97 | 39/39 | 100.00% | 39/39 | 1 ok |  |
| ✅ | end_jetpack_hover | 0x43a370 | 28 | 9/9 | 100.00% | 9/9 | 1 ok |  |
| ✅ | uninit_jet_particles | 0x43a580 | 36 | 17/17 | 100.00% | 17/17 | 1 ok |  |
| ✅ | initialize_jetpack_gauge | 0x43a930 | 65 | 15/15 | 100.00% | 15/15 | 3 ok |  |
| ✅ | arm_jetpack_gauge | 0x43a980 | 55 | 18/18 | 100.00% | 18/18 | 4 ok |  |
| ✅ | show_subgoldy_lives | 0x43af10 | 66 | 23/23 | 100.00% | 23/23 | 2 ok |  |
| ✅ | begin_post_follow_carryover | 0x43af60 | 97 | 20/20 | 100.00% | 20/20 | - |  |
| 🚧 | play_movement_state_sound | 0x43afd0 | 335 | 96/88 | 89.13% | 26/88 | 19 ok |  |
| 🚧 | update_subgoldy | 0x43b120 | 8456 | 2067/2087 | 72.51% | 0/2087 | 291 ok |  |
| ✅ | initialize_subgoldy_ghost | 0x43d230 | 413 | 108/108 | 100.00% | 108/108 | 6 ok |  |
| 🚧 | mark_current_track_pair_with_payload | 0x43d3d0 | 62 | 17/18 | 91.43% | 15/18 | - |  |
| ✅ | get_track_grid_cell_at_world_position | 0x43d410 | 98 | 34/34 | 100.00% | 34/34 | 3 ok |  |
| ✅ | get_track_runtime_cell_at_world_z | 0x43d480 | 73 | 23/23 | 100.00% | 23/23 | 3 ok |  |
| ✅ | sample_track_floor_height_at_position | 0x43d4d0 | 197 | 63/63 | 100.00% | 63/63 | 8 ok |  |
| 🚧 | spawn_garbage_smoke_particle | 0x43d5a0 | 280 | 75/76 | 76.82% | 5/76 | 9 ok |  |
| ✅ | spawn_track_speedup | 0x43d880 | 3 | 1/1 | 100.00% | 1/1 | - |  |
| 🚧 | spawn_track_garbage_hazard | 0x43da80 | 505 | 140/143 | 92.58% | 48/143 | 16 ok |  |
| 🚧 | update_ring_or_special_effect_particle | 0x43e780 | 174 | 55/55 | 96.36% | 28/55 | 5 ok |  |
| 🚧 | update_track_health_pickup | 0x43ecc0 | 390 | 128/128 | 71.88% | 6/128 | 15 ok |  |
| ✅ | update_track_jetpack_pickup | 0x43ee50 | 340 | 103/103 | 100.00% | 103/103 | 15 ok |  |
| 🚧 | update_sub_lazer_projectile | 0x43efb0 | 384 | 127/127 | 72.44% | 6/127 | 15 ok |  |
| ✅ | destroy_garbage_hazard | 0x43f130 | 205 | 62/62 | 100.00% | 62/62 | 6 ok |  |
| 🚧 | update_garbage_hazard | 0x43f200 | 777 | 218/217 | 80.00% | 0/217 | 1 mismatch, 19 ok |  |
| ✅ | update_slug_voice_ai | 0x43f520 | 56 | 14/14 | 100.00% | 14/14 | 1 ok |  |
| ✅ | play_slug_voice | 0x43f560 | 95 | 22/22 | 100.00% | 22/22 | 3 ok |  |
| ✅ | initialize_slug_voice_manager | 0x43f5c0 | 18 | 4/4 | 100.00% | 4/4 | - |  |
| ✅ | update_slug_voice_manager | 0x43f5e0 | 49 | 15/15 | 100.00% | 15/15 | 2 ok |  |
| ✅ | hit_slug_hazard | 0x43f620 | 94 | 25/25 | 100.00% | 25/25 | 5 ok |  |
| 🚧 | explode_slug_hazard | 0x43f680 | 556 | 148/147 | 73.22% | 0/147 | 32 ok |  |
| ✅ | kill_slug_hazard | 0x43f8b0 | 128 | 35/35 | 100.00% | 35/35 | 7 ok |  |
| 🚧 | add_subgoldy_score | 0x4402c0 | 190 | 58/58 | 89.66% | 39/58 | 6 ok |  |
| ✅ | clear_subgoldy_score_buckets | 0x4403a0 | 18 | 7/7 | 100.00% | 7/7 | - |  |
| 🚧 | display_score_stats | 0x4403c0 | 241 | 77/67 | 90.28% | 4/67 | 16 ok |  |
| ✅ | set_subgame_rate | 0x4404c0 | 15 | 5/5 | 100.00% | 5/5 | - |  |
| ✅ | uninit_pause_menu | 0x440600 | 82 | 22/22 | 100.00% | 22/22 | 8 ok |  |
| ✅ | advance_blink_random | 0x4408a0 | 31 | 10/10 | 100.00% | 10/10 | - |  |
| ✅ | initialize_blink_random | 0x4408c0 | 74 | 21/21 | 100.00% | 21/21 | 5 ok |  |
| ✅ | update_barrier_ai | 0x440f80 | 17 | 5/5 | 100.00% | 5/5 | - |  |
| ✅ | initialize_damage_gauge | 0x440fa0 | 40 | 12/12 | 100.00% | 12/12 | - |  |
| 🚧 | update_damage_gauge | 0x440fd0 | 1043 | 268/268 | 80.60% | 6/268 | 58 ok |  |
| 🚧 | apply_damage_gauge_delta | 0x4413f0 | 322 | 95/94 | 58.20% | 0/94 | 1 mismatch, 13 ok |  |
| ✅ | initialize_salt_hazard_pool | 0x441540 | 26 | 7/7 | 100.00% | 7/7 | - |  |
| 🚧 | spawn_salt_hazard | 0x441560 | 236 | 68/67 | 74.07% | 0/67 | 8 ok |  |
| ✅ | initialize_sub_lazer_pool | 0x441650 | 26 | 7/7 | 100.00% | 7/7 | - |  |
| 🚧 | spawn_sub_lazer_projectile | 0x441670 | 195 | 63/63 | 98.41% | 24/63 | 6 ok |  |
| 🚧 | deactivate_salt_hazard | 0x441740 | 140 | 43/43 | 62.79% | 0/43 | 4 ok |  |
| 🚧 | update_salt_hazard | 0x4417d0 | 768 | 215/218 | 48.04% | 0/218 | 17 ok |  |
| 🚧 | shoot_subgoldy | 0x441ad0 | 154 | 45/48 | 49.46% | 0/48 | 3 ok |  |
| ✅ | zero_timer_counters | 0x441b70 | 20 | 8/8 | 100.00% | 8/8 | - |  |
| ✅ | advance_timer_counters | 0x441b90 | 116 | 38/38 | 100.00% | 38/38 | 7 ok |  |
| ✅ | update_smtracks | 0x441f60 | 56 | 19/19 | 100.00% | 19/19 | 2 ok |  |
| ✅ | initialize_subgoldy_resurrect | 0x441fa0 | 40 | 6/6 | 100.00% | 6/6 | - |  |
| ✅ | update_subgoldy_resurrect | 0x441fd0 | 332 | 76/76 | 100.00% | 76/76 | 13 ok |  |
| ✅ | get_track_skirt_color | 0x442120 | 76 | 25/25 | 100.00% | 25/25 | 1 ok |  |
| ✅ | initialize_vapour | 0x442500 | 62 | 19/19 | 100.00% | 19/19 | 3 ok |  |
| ✅ | reset_vapour | 0x442540 | 31 | 7/7 | 100.00% | 7/7 | - |  |
| ✅ | update_track_parcels | 0x443130 | 34 | 16/16 | 100.00% | 16/16 | - |  |
| ✅ | initialize_track_parcel_slots | 0x443160 | 38 | 13/13 | 100.00% | 13/13 | 1 ok |  |
| ✅ | allocate_track_parcel_slot | 0x443190 | 54 | 18/18 | 100.00% | 18/18 | 2 ok |  |
| ✅ | spawn_track_parcel | 0x443730 | 292 | 96/96 | 100.00% | 96/96 | 5 ok |  |
| ✅ | initialize_parcel_set_bucket_pool | 0x443870 | 39 | 15/15 | 100.00% | 15/15 | 3 ok |  |
| ✅ | initialize_zero_parcel_bucket_pool | 0x4438b0 | 39 | 15/15 | 100.00% | 15/15 | 3 ok |  |
| 🚧 | place_parcels_on_track | 0x4438e0 | 2396 | 643/639 | 23.40% | 0/639 | 5 mismatch, 25 ok |  |
| 🚧 | project_position_onto_track_attachment | 0x4444b0 | 333 | 101/106 | 81.16% | 15/106 | 5 ok |  |
| ✅ | initialize_anim_manager | 0x4447c0 | 14 | 6/6 | 100.00% | 6/6 | - |  |
| ✅ | initialize_score_stats | 0x444960 | 20 | 8/8 | 100.00% | 8/8 | - |  |
| ✅ | start_squidge_y | 0x444980 | 23 | 5/5 | 100.00% | 5/5 | 1 ok |  |
| ✅ | start_squidge_z | 0x4449a0 | 23 | 6/6 | 100.00% | 6/6 | 1 ok |  |
| 🚧 | update_squidge | 0x4449c0 | 253 | 84/80 | 84.15% | 6/80 | 14 ok |  |
| ✅ | initialize_invincible_shell | 0x444ac0 | 31 | 7/7 | 100.00% | 7/7 | 3 ok |  |
| ✅ | start_invincible_shell | 0x444ae0 | 97 | 21/21 | 100.00% | 21/21 | 4 ok |  |
| 🚧 | handle_subgoldy_collisions | 0x444cf0 | 2887 | 657/673 | 45.71% | 0/673 | 64 ok |  |
| ✅ | kill_subgoldy | 0x445840 | 17 | 6/6 | 100.00% | 6/6 | 1 ok |  |
| ✅ | update_times_up | 0x445e20 | 75 | 26/26 | 100.00% | 26/26 | 5 ok |  |
| ✅ | uninit_times_up | 0x445e70 | 27 | 8/8 | 100.00% | 8/8 | 2 ok |  |
| ✅ | show_times_up_message | 0x445e90 | 116 | 31/31 | 100.00% | 31/31 | 6 ok |  |
| ✅ | hide_gameplay_scores | 0x445f10 | 35 | 12/12 | 100.00% | 12/12 | 2 ok |  |
| ✅ | unhide_gameplay_scores | 0x445f40 | 27 | 8/8 | 100.00% | 8/8 | 2 ok |  |
| ✅ | initialize_snail_skin | 0x445f60 | 27 | 6/6 | 100.00% | 6/6 | 2 ok |  |
| ✅ | update_snail_skin_transition | 0x445f80 | 69 | 25/25 | 100.00% | 25/25 | 1 ok |  |
| ✅ | change_snail_skin | 0x445fd0 | 69 | 19/19 | 100.00% | 19/19 | 3 ok |  |
| ✅ | initialize_cutscene_ai | 0x446130 | 35 | 8/8 | 100.00% | 8/8 | 4 ok |  |
| ✅ | initialize_cameraman | 0x446160 | 102 | 20/20 | 100.00% | 20/20 | 6 ok |  |
| 🚧 | update_cameraman | 0x4461d0 | 1274 | 322/322 | 92.55% | 36/322 | 1 mismatch, 72 ok |  |
| ✅ | initialize_subgoldy_death | 0x446e30 | 47 | 14/14 | 100.00% | 14/14 | 3 ok |  |
| ✅ | initialize_warning | 0x446e80 | 130 | 32/32 | 100.00% | 32/32 | 6 ok |  |
| ✅ | uninit_warning | 0x446f10 | 22 | 6/6 | 100.00% | 6/6 | 2 ok |  |
| ✅ | start_warning | 0x446f30 | 21 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| ✅ | stop_warning | 0x446f50 | 14 | 3/3 | 100.00% | 3/3 | 1 ok |  |
| ✅ | stop_warning_sample | 0x446f60 | 24 | 7/7 | 100.00% | 7/7 | 4 ok |  |
| 🚧 | update_warning | 0x446f80 | 179 | 52/52 | 57.69% | 0/52 | 6 ok |  |
| ✅ | get_track_cell_row_index | 0x447040 | 65 | 22/22 | 100.00% | 22/22 | 2 ok |  |
| ✅ | initialize_fringe_manager | 0x447090 | 11 | 2/2 | 100.00% | 2/2 | - |  |
| ✅ | allocate_fringe_object | 0x4470a0 | 50 | 14/14 | 100.00% | 14/14 | 2 ok |  |
| ✅ | uninit_nuke | 0x4470e0 | 41 | 18/18 | 100.00% | 18/18 | 1 ok |  |
| 🚧 | initialize_nuke | 0x447110 | 193 | 64/64 | 93.75% | 30/64 | 5 ok |  |
| 🚧 | update_nuke | 0x4471e0 | 169 | 59/59 | 88.14% | 4/59 | 8 ok |  |
| ✅ | recycle_bod_to_free_list | 0x447290 | 106 | 36/36 | 100.00% | 36/36 | 4 ok |  |
| 🚧 | format_time_trial_string | 0x448960 | 113 | 37/36 | 95.89% | 26/36 | 12 ok |  |
| ✅ | kill_tip_widgets | 0x4489e0 | 81 | 24/24 | 100.00% | 24/24 | 6 ok |  |
| 🚧 | update_tip | 0x448c40 | 166 | 53/51 | 73.08% | 11/51 | 9 ok |  |
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
| ✅ | uninitialize_bass_audio_backend | 0x4496d0 | 70 | 19/19 | 100.00% | 19/19 | 10 ok |  |
| ✅ | stop_music_stream | 0x4498d0 | 71 | 21/21 | 100.00% | 21/21 | 8 ok |  |
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
| ✅ | is_key_pressed_edge | 0x44bb10 | 34 | 11/11 | 100.00% | 11/11 | 2 ok |  |
| ✅ | initialize_mouse_authored_scale_from_clip_rect | 0x44bbb0 | 30 | 7/7 | 100.00% | 7/7 | 3 ok |  |
| ✅ | resolve_uncaptured_cursor_sensitivity_scale | 0x44bc20 | 44 | 11/11 | 100.00% | 11/11 | 5 ok |  |
| ✅ | set_hide_system_cursor_flag | 0x44c050 | 10 | 3/3 | 100.00% | 3/3 | 1 ok |  |
| ✅ | is_mouse_captured | 0x44c3b0 | 3 | 2/2 | 100.00% | 2/2 | - |  |
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
| 🚧 | multiply_vector_by_matrix | 0x44cb90 | 135 | 40/40 | 85.00% | 2/40 | - |  |
| ✅ | rotate_vector_by_matrix | 0x44cc20 | 117 | 38/38 | 100.00% | 38/38 | - |  |
| ✅ | normalize_vector | 0x44cca0 | 75 | 29/29 | 100.00% | 29/29 | 5 ok |  |
| 🚧 | vector_magnitude | 0x44ccf0 | 43 | 19/19 | 94.74% | 17/19 | 1 ok |  |
| ✅ | normalize_vector_from_source | 0x44cd20 | 32 | 12/12 | 100.00% | 12/12 | 1 ok |  |
| ✅ | cross_vectors | 0x44cd40 | 131 | 40/40 | 100.00% | 40/40 | 10 ok |  |
| ✅ | initialize_uniform_scale_matrix | 0x44cde0 | 66 | 21/21 | 100.00% | 21/21 | - |  |
| ✅ | rotate_matrix_world_x | 0x44ce30 | 136 | 50/50 | 100.00% | 50/50 | 2 ok |  |
| ✅ | rotate_matrix_world_y | 0x44cec0 | 133 | 50/50 | 100.00% | 50/50 | 2 ok |  |
| ✅ | rotate_matrix_world_z | 0x44cf50 | 133 | 50/50 | 100.00% | 50/50 | 2 ok |  |
| ✅ | initialize_matrix_from_values | 0x44cfe0 | 116 | 34/34 | 100.00% | 34/34 | - |  |
| ✅ | multiply_matrix_in_place | 0x44d1a0 | 45 | 18/18 | 100.00% | 18/18 | 1 ok |  |
| ✅ | premultiply_matrix_in_place | 0x44d1e0 | 45 | 18/18 | 100.00% | 18/18 | 1 ok |  |
| ✅ | set_matrix_identity | 0x44d210 | 55 | 19/19 | 100.00% | 19/19 | - |  |
| ✅ | set_matrix_rotation_identity | 0x44d250 | 46 | 16/16 | 100.00% | 16/16 | - |  |
| ✅ | invert_matrix_in_place | 0x44d280 | 164 | 54/54 | 100.00% | 54/54 | - |  |
| ✅ | invert_matrix_from_source | 0x44d330 | 157 | 55/55 | 100.00% | 55/55 | - |  |
| 🚧 | orthogonalize_matrix | 0x44d3d0 | 58 | 26/26 | 92.31% | 13/26 | 5 ok |  |
| ✅ | set_matrix_z_direction | 0x44d410 | 196 | 57/57 | 100.00% | 57/57 | 6 ok |  |
| 🚧 | initialize_quaternion_from_axis | 0x44d530 | 74 | 28/26 | 77.78% | 9/26 | 4 ok |  |
| ✅ | initialize_axis_from_quaternion | 0x44d580 | 78 | 30/30 | 100.00% | 30/30 | 4 ok |  |
| 🚧 | initialize_matrix_from_quaternion | 0x44d820 | 247 | 85/82 | 73.05% | 10/82 | 3 ok |  |
| 🚧 | interpolate_matrix_rotation | 0x44d920 | 367 | 112/105 | 71.89% | 30/105 | 2 mismatch, 12 ok |  |
| 🚧 | linear_interpolate_matrix | 0x44da90 | 195 | 51/61 | 51.79% | 0/61 | 6 ok |  |
| ✅ | set_color_rgba | 0x44db60 | 32 | 10/10 | 100.00% | 10/10 | - |  |
| ✅ | set_color_alpha | 0x44db80 | 10 | 3/3 | 100.00% | 3/3 | - |  |
| ✅ | set_color_grayscale | 0x44db90 | 24 | 7/7 | 100.00% | 7/7 | - |  |
| ✅ | store_color4f | 0x44dbb0 | 30 | 9/9 | 100.00% | 9/9 | - |  |
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
| 🚧 | initialize_sprite_manager | 0x44e160 | 148 | 46/45 | 50.55% | 6/45 | 1 ok |  |
| ✅ | kill_sprite | 0x44e200 | 145 | 45/45 | 100.00% | 45/45 | 9 ok |  |
| ✅ | allocate_sprite | 0x44e2a0 | 295 | 81/81 | 100.00% | 81/81 | 10 ok |  |
| ✅ | kill_game_sprites | 0x44e3d0 | 55 | 23/23 | 100.00% | 23/23 | 3 ok |  |
| 🚧 | update_sprite_facing_angle | 0x44e410 | 304 | 86/86 | 97.67% | 36/86 | 8 ok |  |
| ✅ | set_sprite_manager_paused | 0x44e540 | 9 | 3/3 | 100.00% | 3/3 | - |  |
| ✅ | set_sprite_texture_ref | 0x44e550 | 30 | 8/8 | 100.00% | 8/8 | 1 ok |  |
| ✅ | get_sprite_texture | 0x44e570 | 14 | 3/3 | 100.00% | 3/3 | 1 ok |  |
| ✅ | get_sprite_texture_ref | 0x44e580 | 20 | 4/4 | 100.00% | 4/4 | 1 ok |  |
| ✅ | ascii_upper_if_lowercase | 0x44e5a0 | 16 | 7/7 | 100.00% | 7/7 | - |  |
| ✅ | initialize_texture_list | 0x44e800 | 16 | 4/4 | 100.00% | 4/4 | - |  |

## Type Consolidation

This is generated as part of `uv run snail match status --write tools/match/STATUS.md`. Keep types scratch-local until multiple scratches agree, then promote deliberately; divergent names are semantic debt, not merge candidates.
Run `uv run snail match types --paths` for the full path-level report.

- ready: 9 type name(s)
- covered: 11 type name(s) with a header plus scratch-local copies
- divergent: 70 type name(s) with multiple scratch-local shapes

| status | type | scratch | header | signatures | recommendation |
|---|---|---:|---:|---:|---|
| divergent | Game | 37 | 0 | 35 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | TransformMatrix | 37 | 0 | 26 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | BorderManager | 19 | 0 | 14 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | Vec3 | 19 | 0 | 11 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | FrontendWidget | 15 | 0 | 13 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | BodBase | 12 | 0 | 6 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | AudioBackend | 11 | 0 | 11 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | VoiceManager | 9 | 0 | 9 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | Object | 8 | 0 | 8 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | VoiceSet | 8 | 0 | 8 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | RenderableBod | 8 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | PathTemplate | 7 | 0 | 7 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | WarningActor | 7 | 0 | 7 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | TipManager | 6 | 0 | 6 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | TipSlot | 6 | 0 | 6 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | MouseCursorState | 6 | 0 | 5 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | SoundEffectManager | 6 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | JetpackGaugeController | 5 | 0 | 5 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | PathTemplateSample | 5 | 0 | 5 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | SlugHazardRuntime | 5 | 0 | 5 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | TimerCounters | 5 | 0 | 5 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | BodList | 4 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | FringeObject | 4 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | FrontendFade | 4 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | GolbProjectile | 4 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | GolbShot | 4 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | ScoreStats | 4 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | SubgameRuntime | 4 | 0 | 4 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | Quaternion | 4 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | Backdrop | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | BorderRecord | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | DamageGaugeController | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | FringeManager | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | GameRoot | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | GarbageHazardSlot | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | NukeController | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | RowEventDisplayController | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | SaltHazardSlot | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | SelectedLevelRecord | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | SubLazerSlot | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | TimesUpController | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | TrackParcelSlot | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | VapourTrail | 3 | 0 | 3 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | ActiveBod | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | AppShell | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | Axis | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | BlinkRandomTable | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | CameramanState | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | CheatState | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | CompletionScreen | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | ContactTargetRegistry | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | Direct3DDevice8Vtbl | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | DuplicateVertexBuffer | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | FrontendOverlayColorLerp | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | GameRuntime | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | HighScoreBank | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | HighScoreScreen | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | InputState | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | InvincibleShellController | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | RuntimeTrackCell | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | SaltHazardPool | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | SlugVoiceManager | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | StarField | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | Subgame | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | SubLazerPool | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | TooltipState | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | TrackParcelRuntime | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | TrackParcelSlots | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | TrackRuntimeRow | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| divergent | TutorialController | 2 | 0 | 2 | same name has multiple scratch-local shapes; do not consolidate yet |
| covered | Player | 31 | 1 | 26 | header exists; consider replacing matching scratch-local copies with includes |
| covered | TrackRowCell | 14 | 1 | 10 | header exists; consider replacing matching scratch-local copies with includes |
| covered | Vector3 | 13 | 2 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | Color4f | 7 | 1 | 7 | header exists; consider replacing matching scratch-local copies with includes |
| covered | SquidgeState | 3 | 1 | 3 | header exists; consider replacing matching scratch-local copies with includes |
| covered | AttachmentPathTemplate | 2 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | AttachmentSample | 2 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | FollowState | 2 | 1 | 2 | header exists; consider replacing matching scratch-local copies with includes |
| covered | Vec4 | 2 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | GolbPathFollowState | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| covered | SnailSkinTransition | 1 | 1 | 1 | header exists; consider replacing matching scratch-local copies with includes |
| ready | BodNode | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | BorderBatchState | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | Direct3DDevice8 | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | ListHead | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | ParcelBucket | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | ParcelBucketSlot | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | SaltListAnchor | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | StarFieldEntry | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
| ready | TrackRuntimeCell | 2 | 0 | 1 | same scratch-local definition appears repeatedly; consider a header |
