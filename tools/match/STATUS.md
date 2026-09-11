# Matching Status

Regenerate with `uv run snail match status --write tools/match/STATUS.md`.

**604/662** port-relevant functions matched, **662/662** port-relevant functions have a scratch, **159337/299952** bytes (**53.12%**) are proof-grade, and overall fuzzy is **93.50%**.

**113/120** platform helpers matched, **120/120** have a scratch, **17576/23008** bytes (**76.39%**) are proof-grade, and overall fuzzy is **96.83%**. Platform progress is tracked separately from port-relevant totals.

**3** third-party functions (**8104** curated-extent bytes) remain visible for context and are excluded from both progress totals.

## Residual frontier

**58** non-exact scratch-backed functions hold **14059 fuzzy-gap bytes**. The top 5 hold **51.7%** of that gap; the top 10 hold **66.8%**.

Current-baseline experiments cover **16 functions / 4202 gap bytes**; **42 / 9856** are historical-only; **0 / 0** have no recorded experiments.

Evidence labels are baseline-epoch aware. `historical-only` means no recorded experiment has a verified current baseline: records may have different input hashes or lack baseline identity. Unversioned records do not prove that the source or generated code changed. Inspect their hypotheses before replaying or dismissing them. Experiment counts never label a lane stalled or exhausted. Recovery and residual labels remain manual source assessments, not stopping rules.

| rank | function | fuzzy gap | recovery | residual | evidence | current/all | flags |
|---:|---|---:|---|---|---|---:|---|
| 1 | initialize_game_assets_and_world | 3750 | semantic-complete | analysis,references | historical-only | 0/19 | repeated-variants,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 2 | update_subgoldy | 1408 | semantic-complete | analysis,references | historical-only | 0/14 | repeated-variants,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 3 | update_subgame | 781 | semantic-complete | analysis | historical-only | 0/14 | historical-only,stale-dependencies |
| 4 | populate_runtime_track_cells_from_segments | 714 | semantic-complete | analysis | current-active | 1/148 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,stale-dependencies |
| 5 | load_segment_definitions | 616 | semantic-complete | analysis | historical-only | 0/12 | metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 6 | initialize_worm_path_template_pair | 521 | semantic-complete | analysis | current-active | 1/12 | repeated-variants,metric-tradeoffs,variant-errors,stale-dependencies |
| 7 | render_game_frame | 445 | semantic-complete | analysis | historical-only | 0/22 | repeated-variants,repeated-specs,metric-tradeoffs,historical-only,stale-dependencies |
| 8 | initialize_cage2_path_template_pair | 414 | semantic-complete | analysis | current-active | 1/20 | repeated-variants,metric-tradeoffs,variant-errors,stale-dependencies |
| 9 | border_input_text | 392 | semantic-complete | analysis | historical-only | 0/13 | metric-tradeoffs,historical-only,stale-dependencies |
| 10 | initialize_halfpipe_path_template_pair | 355 | semantic-complete | analysis | current-active | 1/24 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,stale-dependencies |
| 11 | initialize_dip_path_template_pair | 341 | semantic-complete | analysis | current-active | 1/50 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,stale-dependencies |
| 12 | initialize_invert_path_template_pair | 341 | semantic-complete | analysis | current-active | 1/32 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,stale-dependencies |
| 13 | initialize_screw_path_template_pair | 326 | semantic-complete | analysis | current-active | 1/41 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,stale-dependencies |
| 14 | build_subgame_level | 296 | semantic-complete | analysis | historical-only | 0/21 | metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 15 | initialize_wibble_path_template_pair | 241 | semantic-complete | analysis | historical-only | 0/29 | repeated-variants,repeated-specs,metric-tradeoffs,historical-only,stale-dependencies |
| 16 | initialize_loopbow_path_template_pair | 204 | semantic-complete | analysis | current-active | 1/17 | repeated-variants,metric-tradeoffs,variant-errors,stale-dependencies |
| 17 | initialize_looptheloopw_path_template_pair | 199 | semantic-complete | analysis | current-active | 2/14 | repeated-variants,metric-tradeoffs,stale-dependencies |
| 18 | initialize_hump_path_template_pair | 183 | semantic-complete | analysis | historical-only | 0/30 | repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 19 | initialize_p_path_template_pair | 178 | semantic-complete | analysis | historical-only | 0/24 | repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 20 | set_snail_weapon | 155 | semantic-complete | analysis | current-active | 1/11 | repeated-variants,stale-dependencies |
| 21 | initialize_supertramp_path_template_pair | 155 | semantic-complete | analysis | current-active | 1/21 | repeated-variants,repeated-specs,metric-tradeoffs,stale-dependencies |
| 22 | initialize_looptheloop_path_template_pair | 147 | semantic-complete | analysis | current-active | 2/14 | repeated-variants,metric-tradeoffs,stale-dependencies |
| 23 | initialize_turnoverdouble_path_template_pair | 141 | semantic-complete | analysis | historical-only | 0/56 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 24 | initialize_dump_path_template_pair | 140 | semantic-complete | analysis | historical-only | 0/28 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 25 | initialize_loading_screen | 131 | semantic-complete | analysis | historical-only | 0/8 | variant-errors,historical-only,stale-dependencies |
| 26 | initialize_intro_screen | 123 | semantic-complete | analysis | historical-only | 0/13 | repeated-variants,variant-errors,historical-only,stale-dependencies |
| 27 | register_font_texture_sheet | 121 | semantic-complete | analysis | historical-only | 0/26 | repeated-variants,metric-tradeoffs,historical-only,stale-dependencies |
| 28 | place_challenge_parcels_on_track | 116 | semantic-complete | analysis,references | historical-only | 0/9 | historical-only,stale-dependencies |
| 29 | update_frontend_widget_interaction | 112 | semantic-complete | analysis,references | historical-only | 0/16 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 30 | initialize_toad_path_template_pair | 110 | semantic-complete | analysis | current-active | 1/67 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,stale-dependencies |
| 31 | initialize_turnunder_path_template_pair | 104 | semantic-complete | analysis | current-active | 1/36 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,stale-dependencies |
| 32 | initialize_start_path_template_pair | 88 | incomplete | analysis | current-active | 1/70 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,stale-dependencies |
| 33 | sample_smtrack_heightmap | 76 | semantic-complete | analysis | historical-only | 0/7 | repeated-variants,historical-only,stale-dependencies |
| 34 | update_track_attachment_follow_state | 76 | semantic-complete | analysis | historical-only | 0/24 | repeated-variants,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 35 | add_object_edge | 66 | semantic-complete | analysis,references | historical-only | 0/16 | metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 36 | initialize_tip | 63 | semantic-complete | analysis | historical-only | 0/12 | repeated-variants,historical-only,stale-dependencies |
| 37 | initialize_hill_valley_path_template_pair | 59 | semantic-complete | analysis | historical-only | 0/39 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 38 | release_snail_weapons | 40 | semantic-complete | analysis | historical-only | 0/13 | variant-errors,historical-only,stale-dependencies |
| 39 | select_level_track_texture_set | 39 | semantic-complete | analysis,references | historical-only | 0/9 | variant-errors,historical-only,stale-dependencies |
| 40 | refresh_object_vertex_buffer | 38 | semantic-complete | analysis | historical-only | 0/10 | historical-only,stale-dependencies |
| 41 | try_enter_track_attachment_from_swept_motion | 34 | semantic-complete | analysis | historical-only | 0/12 | historical-only,stale-dependencies |
| 42 | initialize_loopout_path_template_pair | 29 | semantic-complete | analysis | current-active | 1/24 | metric-tradeoffs,variant-errors,stale-dependencies |
| 43 | set_snail_jetpack | 27 | semantic-complete | analysis | historical-only | 0/9 | repeated-variants,historical-only,stale-dependencies |
| 44 | create_golb | 20 | semantic-complete | analysis | historical-only | 0/24 | variant-errors,historical-only,stale-dependencies |
| 45 | firework_shoot | 19 | semantic-complete | analysis | historical-only | 0/11 | repeated-variants,historical-only,stale-dependencies |
| 46 | initialize_sweep_path_template_pair | 15 | semantic-complete | analysis | historical-only | 0/44 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 47 | initialize_star_field | 14 | semantic-complete | analysis | historical-only | 0/21 | repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 48 | update_golb_ai | 13 | semantic-complete | analysis | historical-only | 0/34 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 49 | explode_slug_hazard | 11 | semantic-complete | analysis | historical-only | 0/20 | repeated-variants,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 50 | traverse_path_follow_golb | 11 | semantic-complete | analysis | historical-only | 0/34 | repeated-variants,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 51 | read_repeating_text_input_key_code | 9 | semantic-complete | analysis | historical-only | 0/15 | variant-errors,historical-only,stale-dependencies |
| 52 | initialize_slalomdouble_path_template_pair | 7 | semantic-complete | analysis | historical-only | 0/31 | repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 53 | initialize_slalom_path_template_pair | 7 | semantic-complete | analysis | historical-only | 0/61 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 54 | initialize_slalombig_path_template_pair | 7 | semantic-complete | analysis | historical-only | 0/57 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 55 | border_mouse_test | 7 | semantic-complete | analysis | historical-only | 0/14 | variant-errors,historical-only,stale-dependencies |
| 56 | switch_track_mirror | 7 | semantic-complete | analysis | historical-only | 0/6 | historical-only,stale-dependencies |
| 57 | load_galaxy_layout | 7 | semantic-complete | analysis | historical-only | 0/33 | repeated-variants,repeated-specs,metric-tradeoffs,variant-errors,historical-only,stale-dependencies |
| 58 | draw_frontend_widget | 7 | semantic-complete | analysis | historical-only | 0/21 | historical-only,stale-dependencies |


## Proof Grade (604)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| ✅ | initialize_array_with_constructor | 0x401000 | 48 | 21/21 | 100.00% | 21/21 | - |  | core |
| ✅ | border_add_text_number | 0x401030 | 176 | 68/68 | 100.00% | 68/68 | - |  | core |
| ✅ | hide_border_init | 0x4010e0 | 48 | 9/9 | 100.00% | 9/9 | 1 ok |  | core |
| ✅ | unhide_border_init | 0x401110 | 32 | 5/5 | 100.00% | 5/5 | - |  | core |
| ✅ | initialize_frontend_sprite_button | 0x401a70 | 704 | 157/157 | 100.00% | 157/157 | 10 ok |  | core |
| ✅ | initialize_frontend_widget | 0x401d30 | 1904 | 430/430 | 100.00% | 430/430 | 50 ok |  | core |
| ✅ | layout_frontend_widget | 0x4024a0 | 752 | 177/177 | 100.00% | 177/177 | 20 ok |  | core |
| ✅ | set_frontend_widget_shortcut_key | 0x402790 | 32 | 6/6 | 100.00% | 6/6 | - |  | core |
| ✅ | stack_widget_below | 0x4027b0 | 48 | 9/9 | 100.00% | 9/9 | 1 ok |  | core |
| ✅ | unhighlight_border | 0x4027e0 | 32 | 4/4 | 100.00% | 4/4 | - |  | core |
| ✅ | highlight_border | 0x402800 | 32 | 4/4 | 100.00% | 4/4 | - |  | core |
| ✅ | allocate_border | 0x4032a0 | 96 | 23/23 | 100.00% | 23/23 | 3 ok |  | core |
| ✅ | activate_all_borders | 0x403300 | 96 | 19/19 | 100.00% | 19/19 | - |  | core |
| ✅ | kill_border | 0x403360 | 96 | 30/30 | 100.00% | 30/30 | - |  | core |
| ✅ | kill_all_borders | 0x4033c0 | 48 | 14/14 | 100.00% | 14/14 | - |  | core |
| ✅ | hide_all_borders | 0x4033f0 | 16 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | unhide_all_borders | 0x403400 | 16 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | border_input_text_init | 0x403410 | 192 | 46/46 | 100.00% | 46/46 | 3 ok |  | core |
| ✅ | update_input_ok | 0x4034d0 | 144 | 32/32 | 100.00% | 32/32 | - |  | core |
| ✅ | initialize_input_ok | 0x403560 | 80 | 23/23 | 100.00% | 23/23 | 5 ok |  | core |
| ✅ | reset_tooltip | 0x403be0 | 64 | 16/16 | 100.00% | 16/16 | 2 ok |  | core |
| ✅ | update_tooltip | 0x403c20 | 832 | 218/218 | 100.00% | 218/218 | 23 ok |  | core |
| ✅ | queue_frontend_widget_flag_after_delay | 0x403f60 | 96 | 22/22 | 100.00% | 22/22 | 2 ok |  | core |
| ✅ | update_border_manager | 0x403fc0 | 112 | 28/28 | 100.00% | 28/28 | 2 ok |  | core |
| ✅ | update_twinkle_manager | 0x404030 | 64 | 23/23 | 100.00% | 23/23 | 1 ok |  | core |
| ✅ | draw_twinkle | 0x404070 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  | core |
| ✅ | update_twinkle | 0x404080 | 720 | 181/181 | 100.00% | 181/181 | 48 ok |  | core |
| ✅ | initialize_border_stack | 0x404350 | 16 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | apply_all_border_visibility_mode | 0x404360 | 480 | 138/138 | 100.00% | 138/138 | 1 ok |  | core |
| ✅ | border_sprite_extend | 0x404540 | 64 | 14/14 | 100.00% | 14/14 | - |  | core |
| ✅ | set_border_justify_centre | 0x404730 | 16 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | initialize_cheat | 0x404740 | 16 | 5/5 | 100.00% | 5/5 | - |  | core |
| ✅ | update_cheat | 0x404750 | 128 | 52/52 | 100.00% | 52/52 | 7 ok |  | core |
| ✅ | match_cheat_text | 0x4047d0 | 96 | 42/42 | 100.00% | 42/42 | 2 ok |  | core |
| ✅ | flush_row_event_display | 0x404830 | 240 | 67/67 | 100.00% | 67/67 | 19 ok |  | core |
| ✅ | initialize_completion_screen | 0x404920 | 976 | 278/278 | 100.00% | 278/278 | 46 ok |  | core |
| ✅ | update_row_event_display | 0x404cf0 | 848 | 214/214 | 100.00% | 214/214 | 38 ok |  | core |
| ✅ | register_parcel_delivery | 0x405040 | 128 | 36/36 | 100.00% | 36/36 | 10 ok |  | core |
| ✅ | file_exists | 0x405140 | 48 | 14/14 | 100.00% | 14/14 | 3 ok |  | boundary |
| ✅ | get_stream_length_preserve_position | 0x405170 | 64 | 24/24 | 100.00% | 24/24 | 4 ok |  | boundary |
| ✅ | load_file_bytes_allocating | 0x4051b0 | 32 | 8/8 | 100.00% | 8/8 | 1 ok |  | boundary |
| ✅ | load_file_bytes_into_optional_buffer | 0x4051d0 | 160 | 56/56 | 100.00% | 56/56 | 9 ok | msvc6.5 /O2 /G5 /W3 /TC | boundary |
| ✅ | load_x_mesh | 0x405640 | 1616 | 492/492 | 100.00% | 492/492 | 94 ok |  | boundary |
| ✅ | initialize_directx_loader | 0x405c90 | 48 | 13/13 | 100.00% | 13/13 | 3 ok |  | boundary |
| ✅ | load_or_reuse_cached_x_mesh | 0x405cc0 | 160 | 65/65 | 100.00% | 65/65 | 6 ok |  | boundary |
| ✅ | load_x_animation_clip | 0x405d60 | 768 | 228/228 | 100.00% | 228/228 | 50 ok |  | boundary |
| ✅ | destroy_completion_screen | 0x406060 | 112 | 25/25 | 100.00% | 25/25 | 9 ok |  | core |
| ✅ | initialize_exit_prompt | 0x4060d0 | 1808 | 442/442 | 100.00% | 442/442 | 109 ok |  | core |
| ✅ | update_completion_screen | 0x4067e0 | 992 | 208/208 | 100.00% | 208/208 | 69 ok |  | core |
| ✅ | initialize_global_noop_renderable_bods_thunk | 0x406bc0 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_noop_renderable_bods | 0x406bd0 | 64 | 10/10 | 100.00% | 10/10 | 9 ok |  | core |
| ✅ | initialize_default_runtime_config_thunk | 0x406c10 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_default_runtime_config | 0x406c20 | 240 | 36/36 | 100.00% | 36/36 | 32 ok |  | core |
| ✅ | initialize_global_trivial_object_thunk | 0x406d10 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_trivial_object | 0x406d20 | 16 | 2/2 | 100.00% | 2/2 | 2 ok |  | core |
| ✅ | initialize_main_loop_display_state | 0x406d70 | 48 | 8/8 | 100.00% | 8/8 | 7 ok |  | boundary |
| ✅ | initialize_main_loop_timing_state | 0x406da0 | 32 | 4/4 | 100.00% | 4/4 | 3 ok |  | core |
| ✅ | consume_mouse_wheel_delta | 0x4077f0 | 32 | 4/4 | 100.00% | 4/4 | 2 ok |  | boundary |
| ✅ | read_left_mouse_button_state | 0x407810 | 32 | 4/4 | 100.00% | 4/4 | 2 ok |  | boundary |
| ✅ | read_right_mouse_button_state | 0x407830 | 32 | 4/4 | 100.00% | 4/4 | 2 ok |  | boundary |
| ✅ | noop_runtime_ai | 0x407b50 | 16 | 1/1 | 100.00% | 1/1 | - |  | core |
| ✅ | construct_game_runtime | 0x407b60 | 1184 | 268/268 | 100.00% | 268/268 | 120 ok | msvc6.5 /O2 /G5 /W3 /GX | core |
| ✅ | initialize_game_player | 0x408000 | 64 | 17/17 | 100.00% | 17/17 | 6 ok |  | core |
| ✅ | initialize_noop_renderable_bod | 0x408040 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_runtime_pools_and_path_template_bank | 0x408060 | 944 | 227/227 | 100.00% | 227/227 | 72 ok |  | core |
| ✅ | initialize_border_record | 0x408410 | 96 | 21/21 | 100.00% | 21/21 | 9 ok |  | core |
| ✅ | initialize_cached_x_mesh_slot | 0x408470 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_intro_logo_renderable | 0x408490 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_track_speedup_runtime | 0x4084b0 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_track_jetpack_pickup_runtime | 0x4084d0 | 64 | 17/17 | 100.00% | 17/17 | 6 ok |  | core |
| ✅ | initialize_track_health_pickup_runtime | 0x408510 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_slug_hazard_runtime | 0x408530 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_garbage_hazard | 0x408550 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_track_ring_or_special_effect_runtime | 0x408570 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_track_row_runtime | 0x408590 | 48 | 13/13 | 100.00% | 13/13 | 3 ok |  | core |
| ✅ | initialize_path_template_record_pair | 0x4085c0 | 32 | 9/9 | 100.00% | 9/9 | 3 ok |  | core |
| ✅ | initialize_active_bod | 0x4085e0 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | noop_runtime_slot_constructor | 0x408600 | 16 | 2/2 | 100.00% | 2/2 | - |  | core |
| ✅ | initialize_sub_lazer_runtime | 0x408610 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_salt_hazard_runtime | 0x408630 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_fringe_object | 0x408650 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_click_start_controller_runtime | 0x408670 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_golb_shot | 0x408690 | 64 | 17/17 | 100.00% | 17/17 | 6 ok |  | core |
| ✅ | initialize_player_presentation_controller | 0x4086d0 | 336 | 79/79 | 100.00% | 79/79 | 27 ok |  | core |
| ✅ | initialize_active_landscape_entry | 0x408820 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_landscape_script_record | 0x408840 | 32 | 7/7 | 100.00% | 7/7 | 1 ok |  | core |
| ✅ | initialize_track_parcel_runtime | 0x408860 | 18 | 7/7 | 100.00% | 7/7 | 2 ok |  | core |
| ✅ | initialize_galaxy_route_name_record | 0x408880 | 32 | 7/7 | 100.00% | 7/7 | 1 ok |  | core |
| ✅ | initialize_sub_loc | 0x4088c0 | 32 | 10/10 | 100.00% | 10/10 | 4 ok |  | core |
| ✅ | destroy_galaxy | 0x408c10 | 224 | 49/49 | 100.00% | 49/49 | 18 ok |  | core |
| ✅ | initialize_galaxy | 0x408cf0 | 1536 | 338/338 | 100.00% | 338/338 | 74 ok |  | core |
| ✅ | update_galaxy | 0x4092f0 | 2064 | 566/566 | 100.00% | 566/566 | 55 ok |  | core |
| ✅ | draw_galaxy_line | 0x409b00 | 208 | 67/67 | 100.00% | 67/67 | 4 ok |  | core |
| ✅ | update_galaxy_route_record | 0x409bd0 | 32 | 6/6 | 100.00% | 6/6 | 1 ok |  | core |
| ✅ | close_galaxy_route | 0x409bf0 | 96 | 18/18 | 100.00% | 18/18 | 6 ok |  | core |
| ✅ | open_galaxy_route | 0x409c50 | 1136 | 266/266 | 100.00% | 266/266 | 41 ok |  | core |
| ✅ | galaxy_border_bound | 0x40a0c0 | 208 | 63/63 | 100.00% | 63/63 | 2 ok |  | core |
| ✅ | update_overlay | 0x40a1b0 | 144 | 42/42 | 100.00% | 42/42 | 7 ok |  | core |
| ✅ | initialize_overlay | 0x40a240 | 80 | 17/17 | 100.00% | 17/17 | 3 ok |  | core |
| ✅ | noop_runtime_callback | 0x40a290 | 16 | 1/1 | 100.00% | 1/1 | - |  | core |
| ✅ | run_frame_update | 0x40a2a0 | 496 | 135/135 | 100.00% | 135/135 | 23 ok |  | core |
| ✅ | initialize_input | 0x40aa50 | 48 | 12/12 | 100.00% | 12/12 | - |  | boundary |
| ✅ | update_input | 0x40aa80 | 48 | 19/19 | 100.00% | 19/19 | - |  | boundary |
| ✅ | update_game_input | 0x40aab0 | 80 | 30/30 | 100.00% | 30/30 | 3 ok |  | boundary |
| ✅ | initialize_frontend_overlay_color_lerp | 0x40ab00 | 64 | 18/18 | 100.00% | 18/18 | 2 ok |  | core |
| ✅ | draw_frontend_overlay_color_lerp | 0x40ab40 | 128 | 38/38 | 100.00% | 38/38 | 6 ok |  | core |
| ✅ | begin_frontend_fade_out | 0x40abc0 | 32 | 5/5 | 100.00% | 5/5 | - |  | core |
| ✅ | begin_frontend_fade_in | 0x40abe0 | 16 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | update_frontend_transition_overlay | 0x40abf0 | 256 | 63/63 | 100.00% | 63/63 | 9 ok |  | core |
| ✅ | zero_vector3 | 0x410710 | 16 | 5/5 | 100.00% | 5/5 | - |  | core |
| ✅ | initialize_game_last | 0x410720 | 16 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | update_frontend_state_machine | 0x4107d0 | 1072 | 181/181 | 100.00% | 181/181 | 69 ok |  | core |
| ✅ | initialize_global_color4f_bank_32_thunk | 0x410c00 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_color4f_bank_32 | 0x410c10 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | set_backdrop_zoom | 0x410c30 | 16 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | set_backdrop_distort | 0x410c40 | 272 | 73/73 | 100.00% | 73/73 | 14 ok |  | core |
| ✅ | change_backdrop | 0x410d50 | 112 | 34/34 | 100.00% | 34/34 | - |  | core |
| ✅ | change_backdrop_real | 0x410dc0 | 96 | 30/30 | 100.00% | 30/30 | 1 ok |  | core |
| ✅ | initialize_backdrop | 0x410e20 | 288 | 55/55 | 100.00% | 55/55 | 4 ok |  | core |
| ✅ | set_backdrop_texture_target | 0x410f40 | 80 | 14/14 | 100.00% | 14/14 | 2 ok |  | core |
| ✅ | draw_split_backdrop | 0x410f90 | 176 | 50/50 | 100.00% | 50/50 | 4 ok |  | core |
| ✅ | render_backdrop | 0x411040 | 688 | 192/192 | 100.00% | 192/192 | 29 ok |  | core |
| ✅ | update_backdrop | 0x4112f0 | 192 | 67/67 | 100.00% | 67/67 | 7 ok |  | core |
| ✅ | add_bod_to_front | 0x4113b0 | 112 | 33/33 | 100.00% | 33/33 | 2 ok |  | core |
| ✅ | append_bod_to_end | 0x411420 | 112 | 33/33 | 100.00% | 33/33 | 2 ok |  | core |
| ✅ | render_camera | 0x411fa0 | 688 | 180/180 | 100.00% | 180/180 | 37 ok |  | boundary |
| ✅ | render_object_toon | 0x4123e0 | 736 | 219/219 | 100.00% | 219/219 | 31 ok |  | boundary |
| ✅ | render_object | 0x4126c0 | 640 | 196/196 | 100.00% | 196/196 | 25 ok |  | boundary |
| ✅ | set_cull_mode | 0x4129f0 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  | boundary |
| ✅ | load_registered_texture_refs | 0x412a00 | 108 | 35/35 | 100.00% | 35/35 | 11 ok |  | boundary |
| ✅ | load_registered_texture_ref | 0x412a70 | 647 | 216/216 | 100.00% | 216/216 | 47 ok |  | boundary |
| ✅ | draw_sprite_quad | 0x4137f0 | 960 | 259/259 | 100.00% | 259/259 | 29 ok |  | boundary |
| ✅ | get_or_append_object_texture_group_vertex | 0x413bb0 | 416 | 127/127 | 100.00% | 127/127 | 18 ok |  | boundary |
| ✅ | build_object_texture_group_buffers | 0x413d50 | 1152 | 373/373 | 100.00% | 373/373 | 29 ok |  | boundary |
| ✅ | set_object_color | 0x4141d0 | 144 | 47/47 | 100.00% | 47/47 | 3 ok |  | boundary |
| ✅ | set_fullscreen_mode | 0x414260 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  | boundary |
| ✅ | bind_texture_ref | 0x414500 | 192 | 62/62 | 100.00% | 62/62 | 11 ok |  | boundary |
| ✅ | replace_object_group_texture_refs | 0x4145c0 | 64 | 26/26 | 100.00% | 26/26 | - |  | boundary |
| ✅ | reset_render_counters | 0x414650 | 32 | 5/5 | 100.00% | 5/5 | 3 ok |  | boundary |
| ✅ | kill_golb | 0x414670 | 432 | 132/132 | 100.00% | 132/132 | 16 ok |  | core |
| ✅ | spawn_golb_trail_sprite | 0x415bb0 | 176 | 47/47 | 100.00% | 47/47 | 2 ok |  | core |
| ✅ | spawn_golb_smoke | 0x415c60 | 288 | 72/72 | 100.00% | 72/72 | 8 ok |  | core |
| ✅ | spawn_golb_impact_sprite | 0x415d80 | 160 | 45/45 | 100.00% | 45/45 | 3 ok |  | core |
| ✅ | initialize_enemy_manager | 0x415e20 | 16 | 2/2 | 100.00% | 2/2 | - |  | core |
| ✅ | search_path_for_golb | 0x415e30 | 192 | 63/63 | 100.00% | 63/63 | 3 ok |  | core |
| ✅ | append_subgame_contact_target | 0x415ef0 | 96 | 34/34 | 100.00% | 34/34 | - |  | core |
| ✅ | initialize_challenge_setup_screen | 0x415f50 | 672 | 167/167 | 100.00% | 167/167 | 37 ok |  | core |
| ✅ | destroy_challenge_setup_screen | 0x4161f0 | 384 | 96/96 | 100.00% | 96/96 | 32 ok |  | core |
| ✅ | update_challenge_setup_screen | 0x416370 | 1168 | 355/355 | 100.00% | 355/355 | 38 ok |  | core |
| ✅ | initialize_help_screen | 0x416800 | 192 | 47/47 | 100.00% | 47/47 | 15 ok |  | core |
| ✅ | destroy_help_screen | 0x4168c0 | 16 | 3/3 | 100.00% | 3/3 | 2 ok |  | core |
| ✅ | update_help_screen | 0x4168d0 | 64 | 12/12 | 100.00% | 12/12 | 3 ok |  | core |
| ✅ | initialize_high_score_screen | 0x416910 | 2320 | 600/600 | 100.00% | 600/600 | 137 ok |  | core |
| ✅ | destroy_high_score_screen | 0x417220 | 64 | 11/11 | 100.00% | 11/11 | 5 ok |  | core |
| ✅ | update_high_score_screen | 0x417260 | 736 | 205/205 | 100.00% | 205/205 | 40 ok |  | core |
| ✅ | initialize_high_score_tables | 0x417540 | 160 | 58/58 | 100.00% | 58/58 | 4 ok |  | core |
| ✅ | load_high_scores_from_file | 0x4175e0 | 192 | 71/71 | 100.00% | 71/71 | 4 ok |  | core |
| ✅ | add_arcade_high_score | 0x4176a0 | 224 | 70/70 | 100.00% | 70/70 | 4 ok |  | core |
| ✅ | add_survival_high_score | 0x417780 | 304 | 84/84 | 100.00% | 84/84 | 6 ok |  | core |
| ✅ | add_time_trial_high_score | 0x4178b0 | 144 | 49/49 | 100.00% | 49/49 | 1 ok |  | core |
| ✅ | save_high_scores_and_config | 0x417940 | 304 | 101/101 | 100.00% | 101/101 | 19 ok |  | core |
| ✅ | initialize_high_score_entry | 0x417a70 | 128 | 40/40 | 100.00% | 40/40 | 3 ok |  | core |
| ✅ | mini_delete_high_score_entry | 0x417af0 | 96 | 33/33 | 100.00% | 33/33 | - |  | core |
| ✅ | exit_high_score_screen | 0x417b50 | 112 | 23/23 | 100.00% | 23/23 | 6 ok |  | core |
| ✅ | initialize_new_game_menu | 0x417bc0 | 752 | 182/182 | 100.00% | 182/182 | 48 ok |  | core |
| ✅ | update_new_game_menu | 0x417eb0 | 1072 | 273/273 | 100.00% | 273/273 | 62 ok |  | core |
| ✅ | reset_landscape_manager | 0x4182e0 | 16 | 2/2 | 100.00% | 2/2 | - |  | core |
| ✅ | load_landscape_script_by_name | 0x4182f0 | 1408 | 386/386 | 100.00% | 386/386 | 63 ok |  | core |
| ✅ | activate_landscape_entry | 0x418870 | 448 | 123/123 | 100.00% | 123/123 | 20 ok |  | core |
| ✅ | clear_active_landscape_entries | 0x418a30 | 144 | 49/49 | 100.00% | 49/49 | 5 ok |  | core |
| ✅ | update_active_landscape_entry | 0x418ac0 | 144 | 41/41 | 100.00% | 41/41 | 4 ok |  | core |
| ✅ | destroy_loading_screen | 0x418e50 | 48 | 15/15 | 100.00% | 15/15 | 3 ok |  | core |
| ✅ | update_loading_screen | 0x418e80 | 656 | 204/204 | 100.00% | 204/204 | 26 ok |  | core |
| ✅ | open_logo | 0x419110 | 208 | 60/60 | 100.00% | 60/60 | 13 ok |  | core |
| ✅ | destroy_intro_screen | 0x419920 | 192 | 61/61 | 100.00% | 61/61 | 7 ok |  | core |
| ✅ | update_intro_screen | 0x4199e0 | 176 | 51/51 | 100.00% | 51/51 | 11 ok |  | core |
| ✅ | update_intro_logo_renderable | 0x419a90 | 160 | 42/42 | 100.00% | 42/42 | 7 ok |  | core |
| ✅ | destroy_main_menu | 0x419b30 | 32 | 5/5 | 100.00% | 5/5 | 4 ok |  | core |
| ✅ | initialize_main_menu | 0x419b50 | 688 | 172/172 | 100.00% | 172/172 | 48 ok |  | core |
| ✅ | update_main_menu | 0x419e00 | 336 | 68/68 | 100.00% | 68/68 | 16 ok |  | core |
| ✅ | initialize_duplicate_vertices | 0x419f50 | 48 | 13/13 | 100.00% | 13/13 | 2 ok |  | core |
| ✅ | clean_duplicate_vertices | 0x419f80 | 80 | 33/33 | 100.00% | 33/33 | - |  | core |
| ✅ | sort_object_faces_by_texture_group | 0x419fd0 | 208 | 75/75 | 100.00% | 75/75 | - |  | core |
| ✅ | disable_object_rendering | 0x41a0a0 | 16 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | initialize_textured_backdrop_quad | 0x41a0b0 | 192 | 57/57 | 100.00% | 57/57 | 6 ok |  | core |
| ✅ | raise_backdrop_quad_edge_pair | 0x41a170 | 80 | 19/19 | 100.00% | 19/19 | 4 ok |  | core |
| ✅ | initialize_backdrop_slice_quad | 0x41a1c0 | 208 | 61/61 | 100.00% | 61/61 | 7 ok |  | core |
| ✅ | initialize_backdrop_corner_quad | 0x41a290 | 208 | 55/55 | 100.00% | 55/55 | 10 ok |  | core |
| ✅ | initialize_backdrop_tile_quad | 0x41a4d0 | 1376 | 368/368 | 100.00% | 368/368 | 63 ok |  | core |
| ✅ | initialize_object_distort | 0x41aa30 | 32 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | apply_distort_to_object | 0x41aa50 | 656 | 197/197 | 100.00% | 197/197 | 26 ok |  | core |
| ✅ | initialize_options_menu | 0x41ace0 | 512 | 127/127 | 100.00% | 127/127 | 32 ok |  | core |
| ✅ | destroy_options_menu | 0x41aee0 | 128 | 32/32 | 100.00% | 32/32 | 13 ok |  | core |
| ✅ | update_options_menu | 0x41af60 | 272 | 73/73 | 100.00% | 73/73 | 19 ok |  | core |
| ✅ | apply_audio_config_volumes | 0x41b070 | 48 | 11/11 | 100.00% | 11/11 | 7 ok |  | boundary |
| ✅ | get_path_nodes | 0x41b0a0 | 80 | 23/23 | 100.00% | 23/23 | 4 ok |  | core |
| ✅ | begin_track_attachment_follow_state | 0x420c40 | 112 | 27/27 | 100.00% | 27/27 | 4 ok |  | core |
| ✅ | initialize_path_follow_golb | 0x421770 | 64 | 16/16 | 100.00% | 16/16 | 1 ok |  | core |
| ✅ | mirror_path | 0x421dc0 | 1072 | 314/314 | 100.00% | 314/314 | 15 ok |  | core |
| ✅ | initialize_snake_path_template_pair | 0x423580 | 2448 | 652/652 | 100.00% | 652/652 | 40 ok |  | core |
| ✅ | build_track_fringe_mesh | 0x4246a0 | 1072 | 318/318 | 100.00% | 318/318 | 23 ok |  | core |
| ✅ | build_track_fringe_supertramp_mesh | 0x424ad0 | 1408 | 421/421 | 100.00% | 421/421 | 25 ok |  | core |
| ✅ | initialize_turnover_path_template_pair | 0x426cb0 | 2448 | 671/671 | 100.00% | 671/671 | 41 ok |  | core |
| ✅ | find_segment_path_index_by_name | 0x429ae0 | 64 | 27/27 | 100.00% | 27/27 | 3 ok |  | core |
| ✅ | initialize_twister_path_template_pair | 0x42a540 | 2544 | 677/677 | 100.00% | 677/677 | 49 ok |  | core |
| ✅ | initialize_twister2_path_template_pair | 0x42af30 | 2544 | 677/677 | 100.00% | 677/677 | 49 ok |  | core |
| ✅ | compute_kind42_attachment_transform | 0x42b920 | 160 | 48/48 | 100.00% | 48/48 | 8 ok |  | core |
| ✅ | get_path_position_at_node | 0x42b9c0 | 192 | 56/56 | 100.00% | 56/56 | - |  | core |
| ✅ | calc_path_length_z | 0x42c600 | 368 | 113/113 | 100.00% | 113/113 | 9 ok |  | core |
| ✅ | is_point_inside_track_attachment | 0x42ca90 | 352 | 111/111 | 100.00% | 111/111 | 6 ok |  | core |
| ✅ | initialize_sbend_path_template_pair | 0x42df00 | 2080 | 579/579 | 100.00% | 579/579 | 39 ok |  | core |
| ✅ | load_config_file | 0x42f470 | 32 | 9/9 | 100.00% | 9/9 | 1 ok |  | core |
| ✅ | load_file_bytes_from_path | 0x42f490 | 176 | 59/59 | 100.00% | 59/59 | 9 ok | msvc6.5 /O2 /G5 /W3 /TC | boundary |
| ✅ | save_config_file | 0x42f540 | 112 | 31/31 | 100.00% | 31/31 | 5 ok |  | boundary |
| ✅ | validate_config_tail_stub | 0x42f5b0 | 16 | 2/2 | 100.00% | 2/2 | - |  | core |
| ✅ | is_bod_after_sprites | 0x42f5c0 | 16 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | set_bod_object | 0x42f5d0 | 32 | 6/6 | 100.00% | 6/6 | - |  | core |
| ✅ | initialize_bod_base | 0x42f5f0 | 96 | 27/27 | 100.00% | 27/27 | 5 ok |  | core |
| ✅ | initialize_renderable_bod | 0x42f650 | 48 | 10/10 | 100.00% | 10/10 | 3 ok |  | core |
| ✅ | apply_bod_position | 0x42f680 | 89 | 39/39 | 100.00% | 39/39 | 1 ok |  | core |
| ✅ | initialize_object_constructor_thunk | 0x42f6e0 | 16 | 6/6 | 100.00% | 6/6 | 1 ok |  | core |
| ✅ | initialize_object | 0x42f6f0 | 32 | 9/9 | 100.00% | 9/9 | - |  | core |
| ✅ | request_object_vertices | 0x42f710 | 128 | 37/37 | 100.00% | 37/37 | 8 ok |  | core |
| ✅ | copy_object_vertices | 0x42f790 | 64 | 28/28 | 100.00% | 28/28 | - |  | core |
| ✅ | request_object_vertices_copy | 0x42f7d0 | 48 | 14/14 | 100.00% | 14/14 | 3 ok |  | core |
| ✅ | request_object_facequad_normals | 0x42f800 | 80 | 26/26 | 100.00% | 26/26 | 4 ok |  | core |
| ✅ | request_object_vertex_colours | 0x42f850 | 77 | 30/30 | 100.00% | 30/30 | 2 ok |  | core |
| ✅ | initialize_global_temp_colour_thunk | 0x42f8a0 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_temp_colour | 0x42f8b0 | 16 | 2/2 | 100.00% | 2/2 | 2 ok |  | core |
| ✅ | request_object_facequads | 0x42f8c0 | 112 | 40/40 | 100.00% | 40/40 | 5 ok |  | core |
| ✅ | request_object_texture_groups | 0x42f930 | 96 | 29/29 | 100.00% | 29/29 | 4 ok |  | core |
| ✅ | initialize_object_list | 0x42f990 | 80 | 30/30 | 100.00% | 30/30 | 3 ok |  | core |
| ✅ | build_all_objects | 0x42f9e0 | 160 | 54/54 | 100.00% | 54/54 | 8 ok |  | core |
| ✅ | apply_object_toon | 0x42fa80 | 80 | 24/24 | 100.00% | 24/24 | 4 ok |  | core |
| ✅ | add_object_to_list | 0x42fad0 | 64 | 24/24 | 100.00% | 24/24 | 3 ok |  | core |
| ✅ | calc_object_bounding_box | 0x42fb10 | 416 | 119/119 | 100.00% | 119/119 | 1 ok | msvc6.5 /O2 /G5 /W3 /Ow | core |
| ✅ | calc_object_facequad_normals | 0x42fcb0 | 1408 | 437/437 | 100.00% | 437/437 | 22 ok |  | core |
| ✅ | calc_object_facequad_normals_simple | 0x430230 | 448 | 139/139 | 100.00% | 139/139 | 5 ok |  | core |
| ✅ | calc_object_texture_groups | 0x4303f0 | 128 | 55/55 | 100.00% | 55/55 | 1 ok |  | core |
| ✅ | advance_frame_sequence | 0x430470 | 256 | 65/65 | 100.00% | 65/65 | 2 ok |  | core |
| ✅ | request_object_edges | 0x430570 | 48 | 16/16 | 100.00% | 16/16 | 2 ok |  | core |
| ✅ | calc_object_edges | 0x4308b0 | 384 | 141/141 | 100.00% | 141/141 | 17 ok |  | core |
| ✅ | rotate_object_facequad_uv_pairs | 0x430a30 | 64 | 17/17 | 100.00% | 17/17 | - |  | core |
| ✅ | request_object_animation | 0x430a70 | 800 | 231/231 | 100.00% | 231/231 | 17 ok |  | core |
| ✅ | replace_object_list_texture_refs | 0x430d90 | 144 | 53/53 | 100.00% | 53/53 | 1 ok |  | core |
| ✅ | copy_c_string | 0x431da0 | 32 | 10/10 | 100.00% | 10/10 | - |  | core |
| ✅ | strings_equal_case_insensitive | 0x431dc0 | 104 | 50/50 | 100.00% | 50/50 | - |  | core |
| ✅ | skip_to_next_line | 0x431e30 | 32 | 13/13 | 100.00% | 13/13 | - |  | core |
| ✅ | append_c_string | 0x431e50 | 48 | 19/19 | 100.00% | 19/19 | - |  | core |
| ✅ | parse_next_space_delimited_token | 0x431e80 | 64 | 27/27 | 100.00% | 27/27 | - |  | core |
| ✅ | parse_next_int32 | 0x431ec0 | 96 | 39/39 | 100.00% | 39/39 | - |  | core |
| ✅ | parse_next_float32 | 0x431f20 | 176 | 64/64 | 100.00% | 64/64 | 9 ok |  | core |
| ✅ | set_input_controller_slot0_button_axes | 0x431fd0 | 32 | 7/7 | 100.00% | 7/7 | 3 ok |  | boundary |
| ✅ | update_input_controller_slot_button_axes | 0x431ff0 | 256 | 61/61 | 100.00% | 61/61 | 25 ok |  | boundary |
| ✅ | copy_active_input_controller_state | 0x4320f0 | 208 | 52/52 | 100.00% | 52/52 | 16 ok |  | boundary |
| ✅ | update_input_controller_pointer_region | 0x4321c0 | 480 | 134/134 | 100.00% | 134/134 | 32 ok |  | boundary |
| ✅ | set_input_controller_pointer_authored_xy | 0x4323a0 | 160 | 40/40 | 100.00% | 40/40 | 11 ok |  | boundary |
| ✅ | read_pressed_text_input_key_code | 0x432440 | 928 | 338/338 | 100.00% | 338/338 | 55 ok |  | boundary |
| ✅ | register_font_texture_sheet_wrapper | 0x432d20 | 32 | 11/11 | 100.00% | 11/11 | 1 ok |  | boundary |
| ✅ | reset_registered_sound_sample_count | 0x432d40 | 16 | 2/2 | 100.00% | 2/2 | 1 ok |  | boundary |
| ✅ | cache_music_file | 0x432d50 | 128 | 42/42 | 100.00% | 42/42 | 11 ok |  | boundary |
| ✅ | play_registered_warning_sample | 0x432dd0 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  | boundary |
| ✅ | stop_registered_warning_sample | 0x432de0 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  | boundary |
| ✅ | play_sound_effect_backend | 0x432df0 | 144 | 42/42 | 100.00% | 42/42 | 11 ok |  | boundary |
| ✅ | play_voice_backend | 0x432e80 | 144 | 42/42 | 100.00% | 42/42 | 11 ok |  | boundary |
| ✅ | register_sound_sample | 0x432f10 | 176 | 51/51 | 100.00% | 51/51 | 19 ok |  | boundary |
| ✅ | find_registered_sound_sample_id_by_name | 0x432fc0 | 80 | 34/34 | 100.00% | 34/34 | 6 ok |  | boundary |
| ✅ | xor_decode_buffer_with_index | 0x433010 | 32 | 15/15 | 100.00% | 15/15 | - |  | boundary |
| ✅ | get_authored_view_width | 0x433030 | 7 | 2/2 | 100.00% | 2/2 | 1 ok |  | core |
| ✅ | get_authored_view_height | 0x433040 | 7 | 2/2 | 100.00% | 2/2 | 1 ok |  | core |
| ✅ | initialize_track_render_cache_manager | 0x433060 | 448 | 122/122 | 100.00% | 122/122 | 18 ok |  | core |
| ✅ | build_track_render_caches | 0x433220 | 1552 | 476/476 | 100.00% | 476/476 | 20 ok |  | core |
| ✅ | add_track_cache_vertex | 0x433830 | 304 | 103/103 | 100.00% | 103/103 | 7 ok |  | core |
| ✅ | append_track_cache_object | 0x433960 | 464 | 167/167 | 100.00% | 167/167 | 6 ok |  | core |
| ✅ | update_track_render_cache_rows | 0x433b30 | 848 | 227/227 | 100.00% | 227/227 | 27 ok |  | core |
| ✅ | update_active_bod | 0x433e80 | 160 | 50/50 | 100.00% | 50/50 | 7 ok |  | core |
| ✅ | remove_track_render_cache_bods | 0x433f20 | 160 | 58/58 | 100.00% | 58/58 | 5 ok |  | core |
| ✅ | bind_subgame_owner | 0x433fc0 | 16 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | initialize_thanks_for_playing_screen | 0x433fd0 | 240 | 55/55 | 100.00% | 55/55 | 17 ok |  | core |
| ✅ | uninit_thanks_screen | 0x4340c0 | 48 | 8/8 | 100.00% | 8/8 | 3 ok |  | core |
| ✅ | update_thanks_for_playing_screen | 0x4340f0 | 384 | 88/88 | 100.00% | 88/88 | 19 ok |  | core |
| ✅ | destroy_star_field | 0x434270 | 80 | 28/28 | 100.00% | 28/28 | 1 ok |  | core |
| ✅ | open_star_field | 0x4342c0 | 80 | 26/26 | 100.00% | 26/26 | 4 ok |  | core |
| ✅ | hide_star_field | 0x434670 | 64 | 23/23 | 100.00% | 23/23 | - |  | core |
| ✅ | unhide_star_field | 0x4346b0 | 64 | 23/23 | 100.00% | 23/23 | - |  | core |
| ✅ | update_star_field | 0x4346f0 | 272 | 67/67 | 100.00% | 67/67 | 13 ok |  | core |
| ✅ | update_star_positions | 0x434800 | 384 | 106/106 | 100.00% | 106/106 | 11 ok |  | core |
| ✅ | initialize_track_colour_bank_a_thunk | 0x434980 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_a | 0x434990 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_banks_b_c_thunk | 0x4349b0 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_banks_b_c | 0x4349c0 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_d_thunk | 0x4349e0 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_d | 0x4349f0 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_e_thunk | 0x434a10 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_e | 0x434a20 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_f_thunk | 0x434a40 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_f | 0x434a50 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_g_thunk | 0x434a70 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_g | 0x434a80 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_h_thunk | 0x434aa0 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_h | 0x434ab0 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_i_thunk | 0x434ad0 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_i | 0x434ae0 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_j_thunk | 0x434b00 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_j | 0x434b10 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_track_colour_bank_k_thunk | 0x434b30 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_track_colour_bank_k | 0x434b40 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | is_neighbor_cell_solid | 0x434b60 | 128 | 47/47 | 100.00% | 47/47 | 2 ok |  | core |
| ✅ | build_track_fringe_objects | 0x434be0 | 1440 | 495/495 | 100.00% | 495/495 | 53 ok |  | core |
| ✅ | merge_track_tile_runs | 0x435180 | 880 | 276/276 | 100.00% | 276/276 | 12 ok |  | core |
| ✅ | mark_track_warning_zones | 0x4354f0 | 256 | 99/99 | 100.00% | 99/99 | - |  | core |
| ✅ | promote_track_tiles_to_fringe_variants | 0x4355f0 | 256 | 75/75 | 100.00% | 75/75 | 6 ok |  | core |
| ✅ | harmonize_center_lane_floor_slide_variants | 0x4356f0 | 912 | 226/226 | 100.00% | 226/226 | 28 ok |  | core |
| ✅ | select_track_tile_edge_variants | 0x435a80 | 704 | 220/220 | 100.00% | 220/220 | 18 ok |  | core |
| ✅ | build_track_colours | 0x435d40 | 176 | 37/37 | 100.00% | 37/37 | 24 ok |  | core |
| ✅ | set_subgame_features | 0x435df0 | 112 | 19/19 | 100.00% | 19/19 | 3 ok |  | core |
| ✅ | normalize_segment_glyph_for_track_flags | 0x437270 | 576 | 160/160 | 100.00% | 160/160 | 2 ok |  | core |
| ✅ | initialize_subgame | 0x4374b0 | 1632 | 397/397 | 100.00% | 397/397 | 85 ok |  | core |
| ✅ | reset_subgame | 0x437b10 | 304 | 75/75 | 100.00% | 75/75 | 2 ok |  | core |
| ✅ | update_progress_bar | 0x437c40 | 416 | 110/110 | 100.00% | 110/110 | 19 ok |  | core |
| ✅ | rebuild_track_runtime_from_segments | 0x437de0 | 160 | 44/44 | 100.00% | 44/44 | 13 ok |  | core |
| ✅ | calc_slider_to_rate | 0x437e80 | 48 | 11/11 | 100.00% | 11/11 | 4 ok |  | core |
| ✅ | complete_subgame | 0x438700 | 336 | 88/88 | 100.00% | 88/88 | 8 ok |  | core |
| ✅ | destroy_subgame | 0x438850 | 832 | 246/246 | 100.00% | 246/246 | 41 ok |  | core |
| ✅ | is_sub_loc_floor | 0x439a40 | 48 | 17/17 | 100.00% | 17/17 | - |  | core |
| ✅ | is_sub_loc_ramp | 0x439a70 | 64 | 29/29 | 100.00% | 29/29 | - |  | core |
| ✅ | is_sub_loc_empty | 0x439ab0 | 32 | 15/15 | 100.00% | 15/15 | - |  | core |
| ✅ | is_sub_loc_slide | 0x439ad0 | 48 | 21/21 | 100.00% | 21/21 | - |  | core |
| ✅ | refresh_fringe_object_draw_list | 0x439b00 | 192 | 63/63 | 100.00% | 63/63 | 8 ok |  | core |
| ✅ | remove_sub_loc | 0x439bc0 | 400 | 131/131 | 100.00% | 131/131 | 18 ok |  | core |
| ✅ | update_sub_loc | 0x439d50 | 704 | 187/187 | 100.00% | 187/187 | 39 ok |  | core |
| ✅ | health_collect_particles | 0x43a010 | 400 | 104/104 | 100.00% | 104/104 | 13 ok |  | core |
| ✅ | set_subgoldy_shoot_flags | 0x43a1a0 | 352 | 50/50 | 100.00% | 50/50 | 2 ok |  | core |
| ✅ | shoot_subgoldy | 0x43a300 | 112 | 39/39 | 100.00% | 39/39 | 1 ok |  | core |
| ✅ | end_jetpack_hover | 0x43a370 | 32 | 9/9 | 100.00% | 9/9 | 1 ok |  | core |
| ✅ | update_jetpack_gauge | 0x43a390 | 496 | 131/131 | 100.00% | 131/131 | 34 ok |  | core |
| ✅ | uninit_jet_particles | 0x43a580 | 48 | 17/17 | 100.00% | 17/17 | 1 ok |  | core |
| ✅ | initialize_jet_particles | 0x43a5b0 | 224 | 73/73 | 100.00% | 73/73 | 3 ok |  | core |
| ✅ | update_jet_particles | 0x43a690 | 672 | 181/181 | 100.00% | 181/181 | 17 ok |  | core |
| ✅ | initialize_jetpack_gauge | 0x43a930 | 80 | 15/15 | 100.00% | 15/15 | 3 ok |  | core |
| ✅ | arm_jetpack_gauge | 0x43a980 | 64 | 18/18 | 100.00% | 18/18 | 4 ok |  | core |
| ✅ | initialize_subgoldy | 0x43a9c0 | 1360 | 279/279 | 100.00% | 279/279 | 27 ok |  | core |
| ✅ | show_subgoldy_lives | 0x43af10 | 80 | 23/23 | 100.00% | 23/23 | 2 ok |  | core |
| ✅ | begin_post_follow_carryover | 0x43af60 | 112 | 20/20 | 100.00% | 20/20 | - |  | core |
| ✅ | play_subgoldy_shoot_sfx | 0x43afd0 | 336 | 88/88 | 100.00% | 88/88 | 19 ok |  | core |
| ✅ | initialize_subgoldy_ghost | 0x43d230 | 416 | 108/108 | 100.00% | 108/108 | 6 ok |  | core |
| ✅ | set_subgoldy_ghost_z | 0x43d3d0 | 64 | 18/18 | 100.00% | 18/18 | - |  | core |
| ✅ | get_track_grid_cell_at_world_position | 0x43d410 | 112 | 34/34 | 100.00% | 34/34 | 3 ok |  | core |
| ✅ | get_track_runtime_cell_at_world_z | 0x43d480 | 80 | 23/23 | 100.00% | 23/23 | 3 ok |  | core |
| ✅ | sample_track_floor_height_at_position | 0x43d4d0 | 208 | 63/63 | 100.00% | 63/63 | 8 ok |  | core |
| ✅ | spawn_garbage_smoke_particle | 0x43d5a0 | 288 | 76/76 | 100.00% | 76/76 | 9 ok |  | core |
| ✅ | spawn_track_health_pickup | 0x43d6c0 | 448 | 122/122 | 100.00% | 122/122 | 7 ok |  | core |
| ✅ | spawn_track_speedup | 0x43d880 | 16 | 1/1 | 100.00% | 1/1 | - |  | core |
| ✅ | spawn_track_jetpack_pickup | 0x43d890 | 496 | 144/144 | 100.00% | 144/144 | 9 ok |  | core |
| ✅ | spawn_track_garbage_hazard | 0x43da80 | 512 | 143/143 | 100.00% | 143/143 | 16 ok |  | core |
| ✅ | spawn_slug_hazard | 0x43dc80 | 656 | 160/160 | 100.00% | 160/160 | 18 ok |  | core |
| ✅ | spawn_track_ring_or_special_effect | 0x43df10 | 1376 | 347/347 | 100.00% | 347/347 | 75 ok |  | core |
| ✅ | initialize_ring_or_special_effect_particles | 0x43e470 | 544 | 153/153 | 100.00% | 153/153 | 10 ok |  | core |
| ✅ | emit_ring_star_shower | 0x43e690 | 240 | 65/65 | 100.00% | 65/65 | 9 ok |  | core |
| ✅ | update_ring_or_special_effect_particle | 0x43e780 | 176 | 55/55 | 100.00% | 55/55 | 5 ok |  | core |
| ✅ | update_ring_or_special_effect_parent | 0x43e830 | 1168 | 337/337 | 100.00% | 337/337 | 38 ok |  | core |
| ✅ | update_track_health_pickup | 0x43ecc0 | 400 | 128/128 | 100.00% | 128/128 | 21 ok |  | core |
| ✅ | update_track_speedup | 0x43ee50 | 352 | 103/103 | 100.00% | 103/103 | 15 ok |  | core |
| ✅ | update_track_jetpack_pickup | 0x43efb0 | 384 | 127/127 | 100.00% | 127/127 | 20 ok |  | core |
| ✅ | destroy_garbage_hazard | 0x43f130 | 208 | 62/62 | 100.00% | 62/62 | 6 ok |  | core |
| ✅ | update_garbage_hazard | 0x43f200 | 800 | 218/218 | 100.00% | 218/218 | 22 ok |  | core |
| ✅ | update_slug_voice_ai | 0x43f520 | 64 | 14/14 | 100.00% | 14/14 | 1 ok |  | core |
| ✅ | play_slug_voice | 0x43f560 | 96 | 22/22 | 100.00% | 22/22 | 3 ok |  | core |
| ✅ | initialize_slug_voice_manager | 0x43f5c0 | 32 | 4/4 | 100.00% | 4/4 | - |  | core |
| ✅ | update_slug_voice_manager | 0x43f5e0 | 64 | 15/15 | 100.00% | 15/15 | 2 ok |  | core |
| ✅ | hit_slug_hazard | 0x43f620 | 96 | 25/25 | 100.00% | 25/25 | 5 ok |  | core |
| ✅ | kill_slug_hazard | 0x43f8b0 | 128 | 35/35 | 100.00% | 35/35 | 7 ok |  | core |
| ✅ | update_slug_hazard_ai | 0x43f930 | 1776 | 465/465 | 100.00% | 465/465 | 71 ok |  | core |
| ✅ | deserialize_compact_high_score_record | 0x440020 | 336 | 114/114 | 100.00% | 114/114 | 1 ok |  | core |
| ✅ | serialize_compact_high_score_record | 0x440170 | 336 | 109/109 | 100.00% | 109/109 | 1 ok |  | core |
| ✅ | add_subgoldy_score | 0x4402c0 | 224 | 59/59 | 100.00% | 59/59 | 6 ok |  | core |
| ✅ | clear_subgoldy_score_buckets | 0x4403a0 | 32 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | display_score_stats | 0x4403c0 | 256 | 67/67 | 100.00% | 67/67 | 16 ok |  | core |
| ✅ | set_subgame_rate | 0x4404c0 | 16 | 5/5 | 100.00% | 5/5 | - |  | core |
| ✅ | calc_subgame_rate | 0x4404d0 | 304 | 84/84 | 100.00% | 84/84 | 16 ok |  | core |
| ✅ | uninit_pause_menu | 0x440600 | 96 | 22/22 | 100.00% | 22/22 | 8 ok |  | core |
| ✅ | initialize_pause_menu | 0x440660 | 320 | 88/88 | 100.00% | 88/88 | 23 ok |  | core |
| ✅ | update_pause_menu | 0x4407a0 | 256 | 55/55 | 100.00% | 55/55 | 10 ok |  | core |
| ✅ | advance_blink_random | 0x4408a0 | 32 | 10/10 | 100.00% | 10/10 | - |  | core |
| ✅ | initialize_blink_random | 0x4408c0 | 80 | 21/21 | 100.00% | 21/21 | 5 ok |  | core |
| ✅ | remove_subgame_bods | 0x440910 | 1648 | 501/501 | 100.00% | 501/501 | 70 ok |  | core |
| ✅ | update_barrier_ai | 0x440f80 | 32 | 5/5 | 100.00% | 5/5 | - |  | core |
| ✅ | initialize_damage_gauge | 0x440fa0 | 48 | 12/12 | 100.00% | 12/12 | - |  | core |
| ✅ | update_damage_gauge | 0x440fd0 | 1056 | 268/268 | 100.00% | 268/268 | 65 ok |  | core |
| ✅ | apply_damage_gauge_delta | 0x4413f0 | 336 | 94/94 | 100.00% | 94/94 | 24 ok |  | core |
| ✅ | initialize_salt_hazard_pool | 0x441540 | 32 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | spawn_salt_hazard | 0x441560 | 236 | 67/67 | 100.00% | 67/67 | 10 ok |  | core |
| ✅ | initialize_sub_lazer_pool | 0x441650 | 32 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | spawn_sub_lazer_projectile | 0x441670 | 208 | 63/63 | 100.00% | 63/63 | 6 ok |  | core |
| ✅ | deactivate_sub_lazer_projectile | 0x441740 | 144 | 43/43 | 100.00% | 43/43 | 5 ok |  | core |
| ✅ | update_sub_lazer_projectile | 0x4417d0 | 768 | 218/218 | 100.00% | 218/218 | 24 ok |  | core |
| ✅ | shoot_sub_lazer_pool | 0x441ad0 | 160 | 48/48 | 100.00% | 48/48 | 4 ok |  | core |
| ✅ | zero_timer_counters | 0x441b70 | 32 | 8/8 | 100.00% | 8/8 | - |  | core |
| ✅ | advance_timer_counters | 0x441b90 | 128 | 38/38 | 100.00% | 38/38 | 7 ok |  | core |
| ✅ | update_salt_hazard | 0x441c10 | 304 | 83/83 | 100.00% | 83/83 | 12 ok |  | core |
| ✅ | update_banner | 0x441d40 | 144 | 44/44 | 100.00% | 44/44 | 7 ok |  | core |
| ✅ | update_smtracks | 0x441f60 | 64 | 19/19 | 100.00% | 19/19 | 2 ok |  | core |
| ✅ | initialize_subgoldy_resurrect | 0x441fa0 | 48 | 6/6 | 100.00% | 6/6 | - |  | core |
| ✅ | update_subgoldy_resurrect | 0x441fd0 | 336 | 76/76 | 100.00% | 76/76 | 13 ok |  | core |
| ✅ | get_track_skirt_color | 0x442120 | 80 | 25/25 | 100.00% | 25/25 | 1 ok |  | core |
| ✅ | initialize_click_start | 0x442170 | 288 | 79/79 | 100.00% | 79/79 | 13 ok |  | core |
| ✅ | update_click_start | 0x442290 | 624 | 138/138 | 100.00% | 138/138 | 24 ok |  | core |
| ✅ | initialize_vapour | 0x442500 | 64 | 19/19 | 100.00% | 19/19 | 3 ok |  | core |
| ✅ | reset_vapour | 0x442540 | 32 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | add_vapour_point | 0x442560 | 144 | 47/47 | 100.00% | 47/47 | - |  | core |
| ✅ | update_vapour | 0x4425f0 | 736 | 227/227 | 100.00% | 227/227 | - |  | core |
| ✅ | update_snail_presentation | 0x4428d0 | 1392 | 339/339 | 100.00% | 339/339 | 44 ok |  | core |
| ✅ | update_row_model | 0x443070 | 192 | 60/60 | 100.00% | 60/60 | 6 ok |  | core |
| ✅ | update_track_parcels | 0x443130 | 48 | 16/16 | 100.00% | 16/16 | - |  | core |
| ✅ | initialize_track_parcel_slots | 0x443160 | 48 | 13/13 | 100.00% | 13/13 | 1 ok |  | core |
| ✅ | allocate_track_parcel_slot | 0x443190 | 64 | 18/18 | 100.00% | 18/18 | 2 ok |  | core |
| ✅ | update_track_parcel | 0x4431d0 | 1152 | 313/313 | 100.00% | 313/313 | 35 ok |  | core |
| ✅ | load_frontend_level_by_mode_and_index | 0x443650 | 224 | 58/58 | 100.00% | 58/58 | 12 ok |  | core |
| ✅ | spawn_track_parcel | 0x443730 | 292 | 96/96 | 100.00% | 96/96 | 5 ok |  | core |
| ✅ | initialize_parcel_set_bucket_pool_thunk | 0x443860 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_parcel_set_bucket_pool | 0x443870 | 39 | 15/15 | 100.00% | 15/15 | 3 ok |  | core |
| ✅ | initialize_zero_parcel_bucket_pool_thunk | 0x4438a0 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_zero_parcel_bucket_pool | 0x4438b0 | 48 | 15/15 | 100.00% | 15/15 | 3 ok |  | core |
| ✅ | place_parcels_on_track | 0x4438e0 | 2400 | 639/639 | 100.00% | 639/639 | 98 ok |  | core |
| ✅ | project_position_onto_track_attachment | 0x4444b0 | 336 | 106/106 | 100.00% | 106/106 | 5 ok |  | core |
| ✅ | dispatch_cutscene_animation | 0x444600 | 224 | 55/55 | 100.00% | 55/55 | 3 ok |  | core |
| ✅ | set_weapon_animation | 0x4446e0 | 224 | 55/55 | 100.00% | 55/55 | 3 ok |  | core |
| ✅ | initialize_anim_manager | 0x4447c0 | 16 | 6/6 | 100.00% | 6/6 | - |  | core |
| ✅ | update_anim_manager | 0x4447d0 | 400 | 134/134 | 100.00% | 134/134 | 13 ok |  | core |
| ✅ | initialize_squidge | 0x444960 | 32 | 8/8 | 100.00% | 8/8 | - |  | core |
| ✅ | start_squidge_y | 0x444980 | 32 | 5/5 | 100.00% | 5/5 | 1 ok |  | core |
| ✅ | start_squidge_z | 0x4449a0 | 32 | 6/6 | 100.00% | 6/6 | 1 ok |  | core |
| ✅ | update_squidge | 0x4449c0 | 256 | 80/80 | 100.00% | 80/80 | 14 ok |  | core |
| ✅ | initialize_invincible_shell | 0x444ac0 | 32 | 7/7 | 100.00% | 7/7 | 3 ok |  | core |
| ✅ | start_invincible_shell | 0x444ae0 | 112 | 21/21 | 100.00% | 21/21 | 4 ok |  | core |
| ✅ | update_invincible_shell | 0x444b50 | 416 | 99/99 | 100.00% | 99/99 | 28 ok |  | core |
| ✅ | handle_subgoldy_collisions | 0x444cf0 | 2896 | 673/673 | 100.00% | 673/673 | 89 ok |  | core |
| ✅ | kill_subgoldy | 0x445840 | 32 | 6/6 | 100.00% | 6/6 | 1 ok |  | core |
| ✅ | build_snail_world_hotspots | 0x445cd0 | 128 | 44/44 | 100.00% | 44/44 | 1 ok |  | core |
| ✅ | extract_snail_local_hotspots | 0x445d50 | 208 | 74/74 | 100.00% | 74/74 | 7 ok |  | core |
| ✅ | update_times_up | 0x445e20 | 80 | 26/26 | 100.00% | 26/26 | 5 ok |  | core |
| ✅ | uninit_times_up | 0x445e70 | 32 | 8/8 | 100.00% | 8/8 | 2 ok |  | core |
| ✅ | show_times_up_message | 0x445e90 | 128 | 31/31 | 100.00% | 31/31 | 6 ok |  | core |
| ✅ | hide_gameplay_scores | 0x445f10 | 48 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | unhide_gameplay_scores | 0x445f40 | 32 | 8/8 | 100.00% | 8/8 | 2 ok |  | core |
| ✅ | initialize_snail_skin | 0x445f60 | 32 | 6/6 | 100.00% | 6/6 | 2 ok |  | core |
| ✅ | update_snail_skin_transition | 0x445f80 | 80 | 25/25 | 100.00% | 25/25 | 1 ok |  | core |
| ✅ | change_snail_skin | 0x445fd0 | 80 | 19/19 | 100.00% | 19/19 | 3 ok |  | core |
| ✅ | update_subgame_camera | 0x446020 | 272 | 70/70 | 100.00% | 70/70 | 9 ok |  | core |
| ✅ | initialize_cutscene_ai | 0x446130 | 48 | 8/8 | 100.00% | 8/8 | 4 ok |  | core |
| ✅ | initialize_cameraman | 0x446160 | 112 | 20/20 | 100.00% | 20/20 | 6 ok |  | core |
| ✅ | update_cameraman | 0x4461d0 | 1280 | 322/322 | 100.00% | 322/322 | 76 ok |  | core |
| ✅ | update_cutscene | 0x4466d0 | 1888 | 506/506 | 100.00% | 506/506 | 58 ok |  | core |
| ✅ | initialize_subgoldy_death | 0x446e30 | 80 | 15/15 | 100.00% | 15/15 | 3 ok |  | core |
| ✅ | initialize_warning | 0x446e80 | 144 | 32/32 | 100.00% | 32/32 | 6 ok |  | core |
| ✅ | uninit_warning | 0x446f10 | 32 | 6/6 | 100.00% | 6/6 | 2 ok |  | core |
| ✅ | start_warning | 0x446f30 | 32 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | stop_warning | 0x446f50 | 16 | 3/3 | 100.00% | 3/3 | 1 ok |  | core |
| ✅ | stop_warning_sample | 0x446f60 | 32 | 7/7 | 100.00% | 7/7 | 4 ok |  | core |
| ✅ | update_warning | 0x446f80 | 192 | 52/52 | 100.00% | 52/52 | 7 ok |  | core |
| ✅ | get_track_cell_row_index | 0x447040 | 80 | 22/22 | 100.00% | 22/22 | 2 ok |  | core |
| ✅ | initialize_fringe_manager | 0x447090 | 16 | 2/2 | 100.00% | 2/2 | - |  | core |
| ✅ | allocate_fringe_object | 0x4470a0 | 64 | 14/14 | 100.00% | 14/14 | 2 ok |  | core |
| ✅ | uninit_nuke | 0x4470e0 | 48 | 18/18 | 100.00% | 18/18 | 1 ok |  | core |
| ✅ | initialize_nuke | 0x447110 | 208 | 64/64 | 100.00% | 64/64 | 5 ok |  | core |
| ✅ | update_nuke | 0x4471e0 | 176 | 59/59 | 100.00% | 59/59 | 8 ok |  | core |
| ✅ | recycle_bod_to_free_list | 0x447290 | 112 | 36/36 | 100.00% | 36/36 | 4 ok |  | core |
| ✅ | copy_segment_definition_to_level_slot | 0x447300 | 384 | 125/125 | 100.00% | 125/125 | 5 ok | msvc6.0 /O2 /G5 /W3 | core |
| ✅ | load_level_definition_file | 0x447480 | 3040 | 926/926 | 100.00% | 926/926 | 183 ok | msvc6.0 /O2 /G5 /W3 | core |
| ✅ | load_builtin_segment_definitions | 0x448060 | 256 | 92/92 | 100.00% | 92/92 | - |  | core |
| ✅ | load_level_definitions | 0x448900 | 96 | 30/30 | 100.00% | 30/30 | 6 ok |  | core |
| ✅ | format_time_trial_string | 0x448960 | 128 | 36/36 | 100.00% | 36/36 | 12 ok | msvc6.5 /O2 /G5 /W3 /TC | core |
| ✅ | kill_tip_widgets | 0x4489e0 | 96 | 24/24 | 100.00% | 24/24 | 6 ok |  | core |
| ✅ | update_tip | 0x448c40 | 176 | 51/51 | 100.00% | 51/51 | 9 ok |  | core |
| ✅ | initialize_tip_manager | 0x448cf0 | 32 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | uninit_tips | 0x448d10 | 32 | 14/14 | 100.00% | 14/14 | 1 ok |  | core |
| ✅ | enqueue_tip_message | 0x448d30 | 80 | 26/26 | 100.00% | 26/26 | 3 ok |  | core |
| ✅ | update_tip_manager | 0x448d80 | 32 | 14/14 | 100.00% | 14/14 | 1 ok |  | core |
| ✅ | initialize_tutorial | 0x448da0 | 48 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | uninit_tutorial | 0x448dd0 | 16 | 3/3 | 100.00% | 3/3 | 2 ok |  | core |
| ✅ | update_tutorial | 0x448de0 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  | core |
| ✅ | initialize_voice_set | 0x448df0 | 112 | 33/33 | 100.00% | 33/33 | 5 ok |  | core |
| ✅ | shuffle_voice_set | 0x448e60 | 96 | 34/34 | 100.00% | 34/34 | 6 ok |  | core |
| ✅ | reset_voice_manager | 0x448ec0 | 32 | 8/8 | 100.00% | 8/8 | - |  | core |
| ✅ | initialize_voice_manager | 0x448ee0 | 960 | 270/270 | 100.00% | 270/270 | 62 ok |  | core |
| ✅ | update_voice_manager | 0x4492a0 | 48 | 18/18 | 100.00% | 18/18 | 2 ok |  | core |
| ✅ | play_voice_manager | 0x4492d0 | 144 | 51/51 | 100.00% | 51/51 | 5 ok |  | core |
| ✅ | update_voice_set | 0x449360 | 48 | 14/14 | 100.00% | 14/14 | 2 ok |  | core |
| ✅ | play_voice_set | 0x449390 | 128 | 43/43 | 100.00% | 43/43 | 3 ok |  | core |
| ✅ | is_voice_playing | 0x449410 | 80 | 40/40 | 100.00% | 40/40 | 2 ok |  | core |
| ✅ | set_audio_normalization_scales | 0x449be0 | 24 | 7/7 | 100.00% | 7/7 | - |  | boundary |
| ✅ | initialize_global_font3d_bods_thunk | 0x449c10 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_font3d_bods | 0x449c20 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_global_font_queue_colors_thunk | 0x449c40 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_font_queue_colors | 0x449c50 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_font_wave_state | 0x449c70 | 48 | 5/5 | 100.00% | 5/5 | 4 ok |  | core |
| ✅ | update_font_wave_state | 0x449ca0 | 128 | 25/25 | 100.00% | 25/25 | 17 ok |  | core |
| ✅ | font_slot_index_for_char | 0x449d20 | 368 | 145/145 | 100.00% | 145/145 | - |  | core |
| ✅ | measure_font_text_width | 0x449e90 | 192 | 60/60 | 100.00% | 60/60 | 9 ok |  | core |
| ✅ | draw_font_text_instance | 0x44a360 | 880 | 272/272 | 100.00% | 272/272 | 41 ok |  | boundary |
| ✅ | draw_queued_font_quad_instance | 0x44a6d0 | 96 | 41/41 | 100.00% | 41/41 | 2 ok |  | boundary |
| ✅ | draw_font_text_queue | 0x44a730 | 96 | 31/31 | 100.00% | 31/31 | 4 ok |  | boundary |
| ✅ | queue_font_text_instance | 0x44a790 | 288 | 73/73 | 100.00% | 73/73 | 24 ok |  | boundary |
| ✅ | queue_axis_aligned_textured_quad | 0x44a8b0 | 256 | 65/65 | 100.00% | 65/65 | 20 ok |  | boundary |
| ✅ | queue_axis_aligned_textured_quad_uv | 0x44a9b0 | 272 | 66/66 | 100.00% | 66/66 | 20 ok |  | boundary |
| ✅ | queue_textured_quad_corners | 0x44aac0 | 288 | 69/69 | 100.00% | 69/69 | 24 ok |  | boundary |
| ✅ | layout_and_queue_wrapped_font_text | 0x44abe0 | 560 | 155/155 | 100.00% | 155/155 | 12 ok |  | boundary |
| ✅ | initialize_font3d_objects | 0x44ae10 | 432 | 126/126 | 100.00% | 126/126 | 20 ok |  | boundary |
| ✅ | is_key_pressed_edge | 0x44bb10 | 48 | 11/11 | 100.00% | 11/11 | 2 ok |  | boundary |
| ✅ | is_key_down | 0x44bb40 | 32 | 5/5 | 100.00% | 5/5 | 1 ok |  | boundary |
| ✅ | is_mouse_captured | 0x44c3b0 | 16 | 2/2 | 100.00% | 2/2 | - |  | boundary |
| ✅ | capture_mouse_cursor | 0x44c3c0 | 64 | 19/19 | 100.00% | 19/19 | 3 ok |  | boundary |
| ✅ | release_mouse_cursor | 0x44c400 | 32 | 8/8 | 100.00% | 8/8 | - |  | boundary |
| ✅ | load_object_definition | 0x44c420 | 1104 | 316/316 | 100.00% | 316/316 | 59 ok |  | core |
| ✅ | initialize_global_identity_matrix_thunk | 0x44c870 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_identity_matrix | 0x44c880 | 16 | 4/4 | 100.00% | 4/4 | 2 ok |  | core |
| ✅ | convert_math_type32_to_16 | 0x44c890 | 32 | 4/4 | 100.00% | 4/4 | 2 ok |  | core |
| ✅ | convert_math_type16_to_32 | 0x44c8b0 | 32 | 6/6 | 100.00% | 6/6 | 1 ok |  | core |
| ✅ | initialize_math_random_table | 0x44c8d0 | 48 | 10/10 | 100.00% | 10/10 | 4 ok |  | core |
| ✅ | next_math_random_value | 0x44c900 | 28 | 8/8 | 100.00% | 8/8 | 3 ok |  | core |
| ✅ | j_rand | 0x44c920 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_trigonometry_tables | 0x44c930 | 64 | 18/18 | 100.00% | 18/18 | 5 ok |  | core |
| ✅ | set_math_random_seed | 0x44c970 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  | core |
| ✅ | cosine | 0x44c980 | 80 | 21/21 | 100.00% | 21/21 | 7 ok |  | core |
| ✅ | sine | 0x44c9d0 | 48 | 7/7 | 100.00% | 7/7 | 4 ok |  | core |
| ✅ | arccosine | 0x44ca00 | 16 | 3/3 | 100.00% | 3/3 | 1 ok |  | core |
| ✅ | atan2_positive | 0x44ca10 | 160 | 48/48 | 100.00% | 48/48 | 7 ok |  | core |
| ✅ | square_root | 0x44cab0 | 16 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | multiply_vector_by_matrix_copy | 0x44cac0 | 144 | 49/49 | 100.00% | 49/49 | - |  | core |
| ✅ | dot_vectors | 0x44cb50 | 32 | 11/11 | 100.00% | 11/11 | - |  | core |
| ✅ | dot_vector | 0x44cb70 | 32 | 10/10 | 100.00% | 10/10 | - |  | core |
| ✅ | multiply_vector_by_matrix | 0x44cb90 | 144 | 40/40 | 100.00% | 40/40 | - |  | core |
| ✅ | rotate_vector_by_matrix | 0x44cc20 | 128 | 38/38 | 100.00% | 38/38 | - |  | core |
| ✅ | normalize_vector | 0x44cca0 | 80 | 29/29 | 100.00% | 29/29 | 5 ok |  | core |
| ✅ | vector_magnitude | 0x44ccf0 | 48 | 19/19 | 100.00% | 19/19 | 1 ok |  | core |
| ✅ | normalize_vector_from_source | 0x44cd20 | 32 | 12/12 | 100.00% | 12/12 | 1 ok |  | core |
| ✅ | cross_vectors | 0x44cd40 | 131 | 40/40 | 100.00% | 40/40 | 10 ok |  | core |
| ✅ | destroy_cross_vectors_static_result | 0x44cdd0 | 16 | 1/1 | 100.00% | 1/1 | - |  | core |
| ✅ | initialize_uniform_scale_matrix | 0x44cde0 | 80 | 21/21 | 100.00% | 21/21 | - |  | core |
| ✅ | rotate_matrix_world_x | 0x44ce30 | 144 | 50/50 | 100.00% | 50/50 | 2 ok |  | core |
| ✅ | rotate_matrix_world_y | 0x44cec0 | 144 | 50/50 | 100.00% | 50/50 | 2 ok |  | core |
| ✅ | rotate_matrix_world_z | 0x44cf50 | 144 | 50/50 | 100.00% | 50/50 | 2 ok |  | core |
| ✅ | initialize_matrix_from_values | 0x44cfe0 | 128 | 34/34 | 100.00% | 34/34 | - |  | core |
| ✅ | multiply_matrices | 0x44d060 | 320 | 114/114 | 100.00% | 114/114 | - |  | core |
| ✅ | multiply_matrix_assign | 0x44d1a0 | 45 | 18/18 | 100.00% | 18/18 | 1 ok |  | core |
| ✅ | multiply_matrix | 0x44d1d0 | 16 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | premultiply_matrix_in_place | 0x44d1e0 | 48 | 18/18 | 100.00% | 18/18 | 1 ok |  | core |
| ✅ | set_matrix_identity | 0x44d210 | 64 | 19/19 | 100.00% | 19/19 | - |  | core |
| ✅ | set_matrix_rotation_identity | 0x44d250 | 48 | 16/16 | 100.00% | 16/16 | - |  | core |
| ✅ | invert_matrix_in_place | 0x44d280 | 176 | 54/54 | 100.00% | 54/54 | - |  | core |
| ✅ | invert_matrix_from_source | 0x44d330 | 160 | 55/55 | 100.00% | 55/55 | - |  | core |
| ✅ | orthogonalize_matrix | 0x44d3d0 | 64 | 26/26 | 100.00% | 26/26 | 5 ok |  | core |
| ✅ | set_matrix_z_direction | 0x44d410 | 208 | 57/57 | 100.00% | 57/57 | 6 ok |  | core |
| ✅ | look_at_point | 0x44d4e0 | 80 | 22/22 | 100.00% | 22/22 | 1 ok |  | core |
| ✅ | initialize_quaternion_from_axis | 0x44d530 | 80 | 26/26 | 100.00% | 26/26 | 4 ok |  | core |
| ✅ | initialize_axis_from_quaternion | 0x44d580 | 80 | 30/30 | 100.00% | 30/30 | 4 ok |  | core |
| ✅ | initialize_quaternion_from_matrix | 0x44d5d0 | 592 | 186/186 | 100.00% | 186/186 | 23 ok |  | core |
| ✅ | initialize_matrix_from_quaternion | 0x44d820 | 256 | 82/82 | 100.00% | 82/82 | 3 ok |  | core |
| ✅ | interpolate_matrix_rotation | 0x44d920 | 368 | 105/105 | 100.00% | 105/105 | 17 ok |  | core |
| ✅ | linear_interpolate_matrix | 0x44da90 | 192 | 61/61 | 100.00% | 61/61 | 6 ok |  | core |
| ✅ | noop_this_constructor | 0x44db50 | 16 | 2/2 | 100.00% | 2/2 | - |  | core |
| ✅ | set_color_rgba | 0x44db60 | 32 | 10/10 | 100.00% | 10/10 | - |  | core |
| ✅ | set_color_alpha | 0x44db80 | 16 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | set_color_grayscale | 0x44db90 | 32 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | store_color4f | 0x44dbb0 | 32 | 9/9 | 100.00% | 9/9 | - |  | core |
| ✅ | set_color_rgb | 0x44dbd0 | 32 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | pack_color_rgba_u8 | 0x44dbf0 | 96 | 24/24 | 100.00% | 24/24 | 8 ok |  | core |
| ✅ | set_color_white | 0x44dc50 | 16 | 3/3 | 100.00% | 3/3 | 1 ok |  | core |
| ✅ | set_color_black | 0x44dc60 | 16 | 3/3 | 100.00% | 3/3 | 1 ok |  | core |
| ✅ | random_signed_float_below | 0x44dc70 | 32 | 9/9 | 100.00% | 9/9 | 3 ok |  | core |
| ✅ | random_float_below | 0x44dc90 | 32 | 8/8 | 100.00% | 8/8 | 2 ok |  | core |
| ✅ | initialize_sound_bank | 0x44dcb0 | 48 | 21/21 | 100.00% | 21/21 | 1 ok |  | boundary |
| ✅ | play_sound_effect_at_position | 0x44dce0 | 256 | 66/66 | 100.00% | 66/66 | 11 ok |  | boundary |
| ✅ | play_sound_effect | 0x44dde0 | 32 | 8/8 | 100.00% | 8/8 | 1 ok |  | boundary |
| ✅ | play_sound_effect_scaled | 0x44de00 | 32 | 9/9 | 100.00% | 9/9 | 1 ok |  | boundary |
| ✅ | play_warning_sample_backend | 0x44de20 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  | boundary |
| ✅ | stop_warning_sample_handle | 0x44de30 | 14 | 5/5 | 100.00% | 5/5 | 1 ok |  | boundary |
| ✅ | initialize_global_sprite_pool_colors_thunk | 0x44de40 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_sprite_pool_colors | 0x44de50 | 32 | 12/12 | 100.00% | 12/12 | 2 ok |  | core |
| ✅ | initialize_global_sprite_sentinel_color_thunk | 0x44de70 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | core |
| ✅ | initialize_global_sprite_sentinel_color | 0x44de80 | 16 | 2/2 | 100.00% | 2/2 | 2 ok |  | core |
| ✅ | initialize_sprite | 0x44de90 | 160 | 33/33 | 100.00% | 33/33 | 1 ok |  | core |
| ✅ | update_sprite | 0x44df30 | 448 | 125/125 | 100.00% | 125/125 | 10 ok |  | core |
| ✅ | register_sprite_texture | 0x44e0f0 | 112 | 35/35 | 100.00% | 35/35 | 6 ok |  | core |
| ✅ | initialize_sprite_manager | 0x44e160 | 160 | 45/45 | 100.00% | 45/45 | 1 ok |  | core |
| ✅ | kill_sprite | 0x44e200 | 160 | 45/45 | 100.00% | 45/45 | 9 ok |  | core |
| ✅ | allocate_sprite | 0x44e2a0 | 304 | 81/81 | 100.00% | 81/81 | 10 ok |  | core |
| ✅ | kill_game_sprites | 0x44e3d0 | 64 | 23/23 | 100.00% | 23/23 | 3 ok |  | core |
| ✅ | build_sprite_tail | 0x44e410 | 304 | 86/86 | 100.00% | 86/86 | 8 ok |  | core |
| ✅ | set_sprite_manager_paused | 0x44e540 | 16 | 3/3 | 100.00% | 3/3 | - |  | core |
| ✅ | set_sprite_texture_ref | 0x44e550 | 32 | 8/8 | 100.00% | 8/8 | 1 ok |  | core |
| ✅ | get_sprite_texture | 0x44e570 | 16 | 3/3 | 100.00% | 3/3 | 1 ok |  | core |
| ✅ | get_sprite_tga | 0x44e580 | 32 | 4/4 | 100.00% | 4/4 | 1 ok |  | core |
| ✅ | ascii_upper_if_lowercase | 0x44e5a0 | 16 | 7/7 | 100.00% | 7/7 | - |  | core |
| ✅ | rstrcpy_checked_ascii | 0x44e5b0 | 72 | 31/31 | 100.00% | 31/31 | 2 ok |  | core |
| ✅ | find_case_insensitive_substring | 0x44e600 | 130 | 63/63 | 100.00% | 63/63 | 4 ok |  | core |
| ✅ | advance_to_next_crlf_line | 0x44e690 | 48 | 22/22 | 100.00% | 22/22 | - |  | core |
| ✅ | strings_equal_case_insensitive_path | 0x44e6c0 | 80 | 33/33 | 100.00% | 33/33 | - |  | core |
| ✅ | parse_next_signed_int | 0x44e710 | 107 | 47/47 | 100.00% | 47/47 | - |  | core |
| ✅ | sample_tga_pixel_rgb | 0x44e780 | 128 | 49/49 | 100.00% | 49/49 | - |  | core |
| ✅ | initialize_texture_list | 0x44e800 | 16 | 4/4 | 100.00% | 4/4 | - |  | boundary |
| ✅ | get_or_create_texture_ref | 0x44e810 | 240 | 79/79 | 100.00% | 79/79 | 4 ok |  | core |
| ✅ | attach_render_camera_source | 0x44e900 | 32 | 6/6 | 100.00% | 6/6 | - |  | boundary |
| ✅ | initialize_render_camera_slot | 0x44e920 | 36 | 11/11 | 100.00% | 11/11 | - |  | boundary |

## Near Match (95-99.99%) (22)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| 🚧 | draw_frontend_widget | 0x401130 | 2368 | 712/712 | 99.72% | 253/712 | 68 ok |  | core |
| 🚧 | update_frontend_widget_interaction | 0x402820 | 2688 | 649/647 | 95.83% | 127/647 | 2 unaudited, 96 ok |  | core |
| 🚧 | border_mouse_test | 0x404580 | 432 | 117/117 | 98.29% | 73/117 | 5 ok |  | core |
| 🚧 | load_galaxy_layout | 0x4088e0 | 816 | 233/233 | 99.14% | 194/233 | 42 ok |  | core |
| 🚧 | update_golb_ai | 0x414820 | 2656 | 695/694 | 99.50% | 417/694 | 71 ok |  | core |
| 🚧 | create_golb | 0x415280 | 2352 | 582/582 | 99.14% | 156/582 | 48 ok |  | core |
| 🚧 | initialize_loopout_path_template_pair | 0x41c5f0 | 2624 | 718/718 | 98.89% | 17/718 | 52 ok |  | core |
| 🚧 | initialize_slalom_path_template_pair | 0x41f760 | 2576 | 696/696 | 99.71% | 560/696 | 40 ok |  | core |
| 🚧 | update_track_attachment_follow_state | 0x420cb0 | 2752 | 726/726 | 97.25% | 194/726 | 65 ok |  | core |
| 🚧 | traverse_path_follow_golb | 0x4217b0 | 1552 | 425/425 | 99.29% | 96/425 | 7 ok |  | core |
| 🚧 | initialize_slalombig_path_template_pair | 0x4221f0 | 2576 | 696/696 | 99.71% | 560/696 | 40 ok |  | core |
| 🚧 | initialize_sweep_path_template_pair | 0x422c00 | 2432 | 652/652 | 99.39% | 45/652 | 37 ok |  | core |
| 🚧 | initialize_slalomdouble_path_template_pair | 0x425050 | 2544 | 683/683 | 99.71% | 84/683 | 45 ok |  | core |
| 🚧 | initialize_start_path_template_pair | 0x426400 | 2224 | 610/610 | 96.07% | 148/610 | 35 ok |  | core |
| 🚧 | initialize_turnunder_path_template_pair | 0x427fe0 | 2496 | 686/687 | 95.85% | 80/687 | 45 ok |  | core |
| 🚧 | try_enter_track_attachment_from_swept_motion | 0x42c770 | 800 | 199/204 | 95.78% | 16/204 | 47 ok |  | core |
| 🚧 | initialize_toad_path_template_pair | 0x42cbf0 | 2432 | 661/663 | 95.47% | 89/663 | 33 ok |  | core |
| 🚧 | initialize_hill_valley_path_template_pair | 0x42d570 | 2448 | 668/668 | 97.60% | 21/668 | 41 ok |  | core |
| 🚧 | read_repeating_text_input_key_code | 0x4327e0 | 1344 | 440/440 | 99.32% | 408/440 | 74 ok |  | boundary |
| 🚧 | initialize_star_field | 0x434310 | 864 | 247/247 | 98.38% | 126/247 | 26 ok |  | core |
| 🚧 | explode_slug_hazard | 0x43f680 | 560 | 147/147 | 97.96% | 79/147 | 32 ok |  | core |
| 🚧 | firework_shoot | 0x441dd0 | 400 | 103/103 | 95.15% | 78/103 | 21 ok |  | core |

## High Progress (80-94.99%) (30)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| 🚧 | initialize_game_assets_and_world | 0x40acf0 | 23072 | 5405/5411 | 83.75% | 43/5411 | 2 unaudited, 1880 ok |  | core |
| 🚧 | refresh_object_vertex_buffer | 0x412250 | 400 | 137/139 | 90.58% | 7/139 | 4 ok |  | boundary |
| 🚧 | initialize_loading_screen | 0x418b50 | 768 | 253/253 | 83.00% | 5/253 | 54 ok |  | core |
| 🚧 | initialize_intro_screen | 0x4191e0 | 1856 | 522/521 | 93.38% | 88/521 | 66 ok | msvc6.0 /O2 /G5 /W3 | core |
| 🚧 | initialize_looptheloop_path_template_pair | 0x41b0f0 | 2640 | 719/721 | 94.44% | 159/721 | 49 ok |  | core |
| 🚧 | initialize_looptheloopw_path_template_pair | 0x41bb40 | 2736 | 737/745 | 92.71% | 118/745 | 55 ok |  | core |
| 🚧 | initialize_hump_path_template_pair | 0x41d030 | 2560 | 687/685 | 92.86% | 44/685 | 43 ok |  | core |
| 🚧 | initialize_dump_path_template_pair | 0x41da30 | 2576 | 689/690 | 94.56% | 51/690 | 43 ok |  | core |
| 🚧 | initialize_dip_path_template_pair | 0x41e440 | 2400 | 646/655 | 85.78% | 8/655 | 37 ok |  | core |
| 🚧 | initialize_screw_path_template_pair | 0x41eda0 | 2496 | 686/685 | 86.94% | 58/685 | 40 ok |  | core |
| 🚧 | initialize_worm_path_template_pair | 0x420170 | 2768 | 725/736 | 81.18% | 0/736 | 37 ok |  | core |
| 🚧 | initialize_supertramp_path_template_pair | 0x423f10 | 1936 | 550/552 | 92.01% | 45/552 | 36 ok |  | core |
| 🚧 | initialize_p_path_template_pair | 0x425a40 | 2496 | 678/679 | 92.85% | 6/679 | 41 ok |  | core |
| 🚧 | initialize_turnoverdouble_path_template_pair | 0x427640 | 2464 | 682/680 | 94.27% | 80/680 | 46 ok |  | core |
| 🚧 | initialize_wibble_path_template_pair | 0x4289a0 | 2224 | 608/608 | 89.14% | 85/608 | 39 ok |  | core |
| 🚧 | initialize_invert_path_template_pair | 0x429250 | 2192 | 603/600 | 84.46% | 120/600 | 35 ok |  | core |
| 🚧 | initialize_halfpipe_path_template_pair | 0x429b20 | 2592 | 704/707 | 86.32% | 137/707 | 55 ok |  | core |
| 🚧 | initialize_loopbow_path_template_pair | 0x42ba80 | 2944 | 792/796 | 93.07% | 22/796 | 63 ok |  | core |
| 🚧 | initialize_cage2_path_template_pair | 0x42e720 | 2432 | 649/648 | 82.96% | 10/648 | 46 ok |  | core |
| 🚧 | add_object_edge | 0x4305a0 | 784 | 225/227 | 91.59% | 15/227 | 3 unaudited, 34 ok |  | core |
| 🚧 | switch_track_mirror | 0x435e60 | 80 | 27/30 | 91.23% | 20/30 | 3 ok |  | core |
| 🚧 | populate_runtime_track_cells_from_segments | 0x435eb0 | 5056 | 1244/1246 | 85.88% | 76/1246 | 165 ok |  | core |
| 🚧 | build_subgame_level | 0x437eb0 | 2128 | 556/555 | 86.09% | 177/555 | 108 ok |  | core |
| 🚧 | update_subgoldy | 0x43b120 | 8464 | 2094/2087 | 83.36% | 12/2087 | 1 unaudited, 315 ok |  | core |
| 🚧 | release_snail_weapons | 0x442e40 | 560 | 125/125 | 92.80% | 13/125 | 33 ok |  | core |
| 🚧 | place_challenge_parcels_on_track | 0x444240 | 624 | 173/171 | 81.40% | 0/171 | 2 unaudited, 33 ok |  | core |
| 🚧 | set_snail_jetpack | 0x445860 | 192 | 61/62 | 86.18% | 0/62 | 8 ok |  | core |
| 🚧 | set_snail_weapon | 0x445920 | 944 | 246/249 | 83.54% | 1/249 | 24 ok |  | core |
| 🚧 | initialize_tip | 0x448a40 | 512 | 154/154 | 87.66% | 23/154 | 27 ok |  | core |
| 🚧 | register_font_texture_sheet | 0x449f50 | 1040 | 274/274 | 88.32% | 55/274 | 57 ok |  | boundary |

## Mid Progress (50-79.99%) (6)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| 🚧 | border_input_text | 0x4035b0 | 1584 | 439/446 | 75.25% | 6/446 | 8 ok |  | core |
| 🚧 | render_game_frame | 0x40a490 | 1472 | 441/439 | 69.77% | 6/439 | 34 ok |  | boundary |
| 🚧 | select_level_track_texture_set | 0x410730 | 160 | 42/44 | 75.51% | 0/44 | 1 mismatch, 6 ok |  | core |
| 🚧 | sample_smtrack_heightmap | 0x41a360 | 368 | 108/109 | 79.26% | 37/109 | 13 ok |  | core |
| 🚧 | update_subgame | 0x438b90 | 3760 | 1037/1034 | 79.22% | 9/1034 | 129 ok |  | core |
| 🚧 | load_segment_definitions | 0x448160 | 1952 | 560/571 | 68.44% | 7/571 | 91 ok |  | core |

## Platform Helpers (120)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| 🖥 | classify_archive_entry_extension | 0x4050c0 | 128 | 46/46 | 100.00% | 46/46 | - |  | replaceable-platform |
| 🖥 | scramble_archive_bytes_in_place | 0x405270 | 48 | 25/25 | 100.00% | 25/25 | - |  | replaceable-platform |
| 🖥 | save_file_bytes_with_optional_archive_scramble | 0x4052a0 | 160 | 56/56 | 100.00% | 56/56 | 10 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | delete_file_path | 0x405340 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  | replaceable-platform |
| 🖥 | toggle_archive_high_bit_in_place | 0x405350 | 32 | 11/11 | 100.00% | 11/11 | - |  | replaceable-platform |
| 🖥 | rebuild_game_archive_if_needed | 0x405370 | 720 | 232/232 | 66.38% | 5/232 | 22 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | log_startup_timestamp | 0x406d30 | 64 | 19/19 | 100.00% | 19/19 | 4 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | game_startup_and_main_loop | 0x406dc0 | 1328 | 323/325 | 93.83% | 176/325 | 1 unaudited, 162 ok |  | replaceable-platform |
| 🖥 | handle_game_window_activate | 0x4072f0 | 192 | 44/44 | 100.00% | 44/44 | 26 ok |  | replaceable-platform |
| 🖥 | show_and_focus_game_window | 0x4073b0 | 144 | 33/33 | 100.00% | 33/33 | 19 ok |  | replaceable-platform |
| 🖥 | handle_game_window_deactivate | 0x407440 | 80 | 18/18 | 100.00% | 18/18 | 9 ok |  | replaceable-platform |
| 🖥 | minimize_game_window | 0x407490 | 32 | 10/10 | 100.00% | 10/10 | 4 ok |  | replaceable-platform |
| 🖥 | game_window_proc | 0x4074b0 | 832 | 142/142 | 100.00% | 142/142 | 39 ok |  | replaceable-platform |
| 🖥 | snapshot_current_display_mode | 0x407850 | 16 | 5/5 | 100.00% | 5/5 | 2 ok |  | replaceable-platform |
| 🖥 | restore_desktop_display_mode | 0x407860 | 32 | 6/6 | 100.00% | 6/6 | 2 ok |  | replaceable-platform |
| 🖥 | probe_display_mode_count | 0x407880 | 48 | 17/17 | 100.00% | 17/17 | 1 ok |  | replaceable-platform |
| 🖥 | read_current_display_resolution | 0x4078b0 | 96 | 22/22 | 100.00% | 22/22 | 1 ok |  | replaceable-platform |
| 🖥 | clear_display_mode_state | 0x407910 | 14 | 3/3 | 100.00% | 3/3 | - |  | replaceable-platform |
| 🖥 | reset_display_mode_probe_count | 0x407920 | 9 | 2/2 | 100.00% | 2/2 | - |  | replaceable-platform |
| 🖥 | read_next_display_mode_view_sample | 0x407930 | 167 | 55/55 | 100.00% | 55/55 | - |  | replaceable-platform |
| 🖥 | bass_audio_window_proc | 0x4079e0 | 48 | 16/16 | 100.00% | 16/16 | 2 ok |  | replaceable-platform |
| 🖥 | initialize_audio_subsystem | 0x407a10 | 240 | 73/73 | 100.00% | 73/73 | 23 ok |  | replaceable-platform |
| 🖥 | shutdown_bass_audio_window | 0x407b00 | 80 | 19/19 | 100.00% | 19/19 | 10 ok |  | replaceable-platform |
| 🖥 | abort_startup_with_3d_error | 0x4088a0 | 32 | 12/12 | 100.00% | 12/12 | 4 ok |  | replaceable-platform |
| 🖥 | create_vertex_buffer | 0x4114b0 | 288 | 101/101 | 100.00% | 101/101 | 11 ok |  | replaceable-platform |
| 🖥 | create_index_buffer | 0x4115d0 | 96 | 36/36 | 100.00% | 36/36 | 5 ok |  | replaceable-platform |
| 🖥 | initialize_direct3d_renderer_defaults | 0x411630 | 192 | 38/38 | 100.00% | 38/38 | 15 ok |  | replaceable-platform |
| 🖥 | release_direct3d_renderer_resources | 0x4116f0 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | replaceable-platform |
| 🖥 | direct3d_renderer_set_cull_mode | 0x411700 | 48 | 16/16 | 100.00% | 16/16 | - |  | replaceable-platform |
| 🖥 | initialize_d3d8_device | 0x411730 | 378 | 106/106 | 100.00% | 106/106 | 12 ok |  | replaceable-platform |
| 🖥 | reset_direct3d_render_state | 0x4118b0 | 176 | 52/52 | 100.00% | 52/52 | 3 ok |  | replaceable-platform |
| 🖥 | release_direct3d_device_interfaces | 0x411960 | 96 | 18/38 | 64.29% | 18/38 | - |  | replaceable-platform |
| 🖥 | initialize_game_window_and_input_wrapper | 0x4119c0 | 16 | 5/5 | 100.00% | 5/5 | 1 ok |  | replaceable-platform |
| 🖥 | initialize_game_window_and_input | 0x4119d0 | 928 | 267/267 | 90.81% | 6/267 | 57 ok |  | replaceable-platform |
| 🖥 | release_global_direct3d_renderer_resources | 0x411d70 | 16 | 2/2 | 100.00% | 2/2 | 2 ok |  | replaceable-platform |
| 🖥 | uninitialize_input_devices | 0x411d80 | 20 | 4/4 | 100.00% | 4/4 | 4 ok |  | replaceable-platform |
| 🖥 | end_overlay_render_state | 0x411de0 | 48 | 13/13 | 100.00% | 13/13 | 4 ok |  | replaceable-platform |
| 🖥 | begin_overlay_render_state | 0x411e10 | 400 | 97/97 | 100.00% | 97/97 | 14 ok |  | replaceable-platform |
| 🖥 | update_display_mode_view_state | 0x412940 | 120 | 46/46 | 100.00% | 46/46 | 4 ok |  | replaceable-platform |
| 🖥 | initialize_direct3d_renderer | 0x4129c0 | 48 | 12/12 | 100.00% | 12/12 | 7 ok |  | replaceable-platform |
| 🖥 | set_blend_mode | 0x412d00 | 336 | 92/92 | 100.00% | 92/92 | 16 ok |  | replaceable-platform |
| 🖥 | set_immediate_blend_mode | 0x412e50 | 480 | 136/137 | 81.97% | 2/137 | 1 mismatch, 1 unaudited, 21 ok |  | replaceable-platform |
| 🖥 | draw_textured_quad_immediate | 0x413030 | 1168 | 331/332 | 98.34% | 111/332 | 26 ok |  | replaceable-platform |
| 🖥 | render_game_frame_scene | 0x4134c0 | 92 | 24/24 | 100.00% | 24/24 | 8 ok |  | replaceable-platform |
| 🖥 | present_backbuffer | 0x413520 | 20 | 9/9 | 100.00% | 9/9 | 1 ok |  | replaceable-platform |
| 🖥 | begin_sprite_depth_render_state | 0x413540 | 272 | 60/60 | 100.00% | 60/60 | 7 ok |  | replaceable-platform |
| 🖥 | end_sprite_depth_render_state | 0x413650 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | replaceable-platform |
| 🖥 | configure_sprite_render_state | 0x413670 | 384 | 110/110 | 100.00% | 110/110 | 18 ok |  | replaceable-platform |
| 🖥 | direct3d_renderer_set_fullscreen_mode | 0x414270 | 336 | 84/84 | 100.00% | 84/84 | 29 ok |  | replaceable-platform |
| 🖥 | restore_texture_ref_stage_states | 0x4143c0 | 320 | 110/110 | 100.00% | 110/110 | 15 ok |  | replaceable-platform |
| 🖥 | query_direct3d_device_caps | 0x414600 | 80 | 21/21 | 100.00% | 21/21 | 4 ok |  | replaceable-platform |
| 🖥 | load_png_image | 0x42f0a0 | 976 | 371/371 | 100.00% | 371/371 | 78 ok |  | replaceable-platform |
| 🖥 | initialize_tracked_allocation_depth_thunk | 0x430e20 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | replaceable-platform |
| 🖥 | initialize_tracked_allocation_depth | 0x430e30 | 16 | 2/2 | 100.00% | 2/2 | 1 ok |  | replaceable-platform |
| 🖥 | initialize_game_data_archive | 0x430e40 | 176 | 47/47 | 100.00% | 47/47 | 20 ok |  | replaceable-platform |
| 🖥 | uninitialize_game_data_archive | 0x430ef0 | 64 | 13/13 | 100.00% | 13/13 | 6 ok |  | replaceable-platform |
| 🖥 | set_current_directory_with_drive_fallback | 0x430f30 | 160 | 48/48 | 100.00% | 48/48 | 6 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | archive_or_file_exists | 0x430fd0 | 96 | 36/36 | 100.00% | 36/36 | 7 ok |  | replaceable-platform |
| 🖥 | load_file_bytes_fixed_size_from_archive_or_fs | 0x431030 | 544 | 188/188 | 100.00% | 188/188 | 32 ok | msvc6.0 /O2 /G5 /W3 | replaceable-platform |
| 🖥 | find_archive_entry | 0x431250 | 128 | 60/60 | 100.00% | 60/60 | 2 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | load_file_bytes_from_archive_or_fs | 0x4312d0 | 592 | 206/206 | 100.00% | 206/206 | 36 ok | msvc6.0 /O2 /G5 /W3 | replaceable-platform |
| 🖥 | load_file_bytes | 0x431520 | 32 | 8/8 | 100.00% | 8/8 | 1 ok |  | replaceable-platform |
| 🖥 | delete_file_path_with_directory_walk | 0x431540 | 272 | 84/84 | 100.00% | 84/84 | 14 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | write_file_bytes | 0x431650 | 240 | 74/74 | 100.00% | 74/74 | 10 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | enumerate_matching_archive_or_fs_entries | 0x431740 | 576 | 182/182 | 92.31% | 9/182 | 26 ok |  | replaceable-platform |
| 🖥 | xor_archive_bytes_in_place | 0x431980 | 64 | 27/27 | 100.00% | 27/27 | - |  | replaceable-platform |
| 🖥 | load_archive_index | 0x4319c0 | 192 | 67/67 | 100.00% | 67/67 | 14 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | is_archive_index_loaded | 0x431a80 | 16 | 4/4 | 100.00% | 4/4 | 1 ok |  | replaceable-platform |
| 🖥 | get_archive_data_base | 0x431a90 | 16 | 2/2 | 100.00% | 2/2 | 1 ok |  | replaceable-platform |
| 🖥 | get_archive_data_end | 0x431aa0 | 16 | 3/3 | 100.00% | 3/3 | 1 ok |  | replaceable-platform |
| 🖥 | get_tracked_allocation_size | 0x431ab0 | 64 | 26/26 | 100.00% | 26/26 | 2 ok |  | replaceable-platform |
| 🖥 | push_tracked_allocation | 0x431af0 | 64 | 19/19 | 100.00% | 19/19 | 2 ok |  | replaceable-platform |
| 🖥 | pop_tracked_allocation | 0x431b30 | 48 | 20/20 | 100.00% | 20/20 | - |  | replaceable-platform |
| 🖥 | allocate_tracked_memory | 0x431b60 | 144 | 48/48 | 100.00% | 48/48 | 7 ok |  | replaceable-platform |
| 🖥 | free_tracked_memory | 0x431bf0 | 128 | 43/43 | 100.00% | 43/43 | 9 ok |  | replaceable-platform |
| 🖥 | free_tracked_allocations_to_mark | 0x431c70 | 64 | 15/15 | 100.00% | 15/15 | 6 ok |  | replaceable-platform |
| 🖥 | set_tracked_allocation_mark | 0x431cb0 | 16 | 3/3 | 100.00% | 3/3 | 2 ok |  | replaceable-platform |
| 🖥 | report_errorf | 0x431cc0 | 80 | 19/19 | 100.00% | 19/19 | 8 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | report_warningf | 0x431d10 | 80 | 19/19 | 100.00% | 19/19 | 8 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | report_messagef | 0x431d60 | 64 | 15/15 | 100.00% | 15/15 | 4 ok | msvc6.5 /O2 /G5 /W3 /TC | replaceable-platform |
| 🖥 | launch_alpha72_url | 0x433050 | 16 | 3/3 | 100.00% | 3/3 | 2 ok |  | replaceable-platform |
| 🖥 | initialize_bass_audio_backend | 0x449460 | 624 | 176/176 | 100.00% | 176/176 | 87 ok |  | replaceable-platform |
| 🖥 | uninitialize_bass_audio_backend | 0x4496d0 | 80 | 19/19 | 100.00% | 19/19 | 10 ok |  | replaceable-platform |
| 🖥 | ensure_music_stream_from_path | 0x449720 | 192 | 70/70 | 100.00% | 70/70 | 14 ok |  | replaceable-platform |
| 🖥 | prepare_music_stream_reload_if_path_changed | 0x4497e0 | 64 | 19/19 | 100.00% | 19/19 | 3 ok |  | replaceable-platform |
| 🖥 | play_music_stream_from_bytes | 0x449820 | 176 | 68/68 | 100.00% | 68/68 | 11 ok |  | replaceable-platform |
| 🖥 | stop_music_stream | 0x4498d0 | 80 | 21/21 | 100.00% | 21/21 | 8 ok |  | replaceable-platform |
| 🖥 | load_registered_sound_sample_from_path | 0x449920 | 64 | 20/20 | 100.00% | 20/20 | 4 ok |  | replaceable-platform |
| 🖥 | load_registered_sound_sample_from_bytes | 0x449960 | 64 | 18/18 | 100.00% | 18/18 | 4 ok |  | replaceable-platform |
| 🖥 | play_registered_sound_sample_scaled | 0x4499a0 | 112 | 30/30 | 100.00% | 30/30 | 7 ok |  | replaceable-platform |
| 🖥 | stop_sound_sample_handle | 0x449a10 | 16 | 4/4 | 100.00% | 4/4 | 1 ok |  | replaceable-platform |
| 🖥 | stop_registered_sound_sample | 0x449a20 | 32 | 5/5 | 100.00% | 5/5 | 2 ok |  | replaceable-platform |
| 🖥 | is_registered_sound_sample_playing | 0x449a40 | 32 | 7/7 | 100.00% | 7/7 | 2 ok |  | replaceable-platform |
| 🖥 | play_registered_sound_sample_default | 0x449a60 | 32 | 10/10 | 100.00% | 10/10 | 2 ok |  | replaceable-platform |
| 🖥 | play_registered_sound_sample_backend | 0x449a80 | 96 | 27/27 | 100.00% | 27/27 | 6 ok |  | replaceable-platform |
| 🖥 | play_registered_sound_sample_scaled_panned | 0x449ae0 | 112 | 29/29 | 100.00% | 29/29 | 7 ok |  | replaceable-platform |
| 🖥 | set_global_sample_volume_config | 0x449b50 | 32 | 7/7 | 100.00% | 7/7 | 3 ok |  | replaceable-platform |
| 🖥 | set_global_stream_volume_config | 0x449b70 | 32 | 7/7 | 100.00% | 7/7 | 3 ok |  | replaceable-platform |
| 🖥 | stop_audio_backend | 0x449b90 | 16 | 1/1 | 100.00% | 1/1 | 1 ok |  | replaceable-platform |
| 🖥 | resume_audio_backend_if_paused | 0x449ba0 | 32 | 8/8 | 100.00% | 8/8 | 1 ok |  | replaceable-platform |
| 🖥 | pause_audio_backend_if_running | 0x449bc0 | 32 | 9/9 | 100.00% | 9/9 | 1 ok |  | replaceable-platform |
| 🖥 | debug_report_stub | 0x449c00 | 16 | 2/2 | 100.00% | 2/2 | - |  | replaceable-platform |
| 🖥 | query_directx_runtime_version | 0x44afc0 | 1012 | 370/370 | 100.00% | 370/370 | 57 ok |  | replaceable-platform |
| 🖥 | enumerate_input_controllers | 0x44b3c0 | 208 | 71/71 | 100.00% | 71/71 | 14 ok |  | replaceable-platform |
| 🖥 | append_enumerated_input_controller_callback | 0x44b490 | 80 | 22/22 | 100.00% | 22/22 | 5 ok |  | replaceable-platform |
| 🖥 | configure_input_controller_axis_range_callback | 0x44b4e0 | 144 | 42/42 | 100.00% | 42/42 | 3 ok |  | replaceable-platform |
| 🖥 | update_joystick_input | 0x44b570 | 512 | 150/150 | 100.00% | 150/150 | 13 ok |  | replaceable-platform |
| 🖥 | release_input_controllers | 0x44b770 | 96 | 35/35 | 100.00% | 35/35 | 5 ok |  | replaceable-platform |
| 🖥 | initialize_keyboard_input | 0x44b7d0 | 160 | 55/55 | 100.00% | 55/55 | 15 ok |  | replaceable-platform |
| 🖥 | update_keyboard_input | 0x44b870 | 672 | 199/199 | 100.00% | 199/199 | 34 ok |  | replaceable-platform |
| 🖥 | release_keyboard_input | 0x44bb60 | 80 | 21/21 | 100.00% | 21/21 | 5 ok |  | replaceable-platform |
| 🖥 | initialize_mouse_authored_scale_from_clip_rect | 0x44bbb0 | 32 | 7/7 | 100.00% | 7/7 | 3 ok |  | replaceable-platform |
| 🖥 | update_mouse_authored_scale | 0x44bbd0 | 80 | 17/17 | 100.00% | 17/17 | 6 ok |  | replaceable-platform |
| 🖥 | resolve_uncaptured_cursor_sensitivity_scale | 0x44bc20 | 48 | 11/11 | 100.00% | 11/11 | 5 ok |  | replaceable-platform |
| 🖥 | update_mouse | 0x44bc50 | 1024 | 295/295 | 100.00% | 295/295 | 81 ok |  | replaceable-platform |
| 🖥 | set_hide_system_cursor_flag | 0x44c050 | 16 | 3/3 | 100.00% | 3/3 | 1 ok |  | replaceable-platform |
| 🖥 | click_mouse_screen | 0x44c060 | 160 | 43/43 | 100.00% | 43/43 | 13 ok |  | replaceable-platform |
| 🖥 | convert_mouse_screen_xy | 0x44c100 | 448 | 115/115 | 100.00% | 115/115 | 35 ok |  | replaceable-platform |
| 🖥 | release_mouse_input | 0x44c2c0 | 80 | 21/21 | 100.00% | 21/21 | 5 ok |  | replaceable-platform |
| 🖥 | initialize_mouse_input | 0x44c310 | 160 | 46/46 | 100.00% | 46/46 | 18 ok |  | replaceable-platform |

## Excluded: Third-party (3)

| | function | address | bytes | insns | match | prefix | masked | build | scope |
|---|---|---|---|---|---|---|---|---|---|
| 📚 | initialize_translation_matrix | 0x44fd90 | 92 | 23/34 | 7.02% | 1/34 | - |  | third-party |
| 📚 | build_perspective_projection_matrix | 0x450314 | 148 | 38/54 | 26.09% | 2/54 | 1 ok | msvc6.5 /O2 /Oy- /G5 /W3 | third-party |
| 📚 | build_camera_view_matrix | 0x451ad9 | 328 | 119/130 | 28.11% | 0/130 | 2 ok |  | third-party |

## Type Consolidation

This is generated as part of `uv run snail match status --write tools/match/STATUS.md`. Keep types scratch-local until multiple scratches agree, then promote deliberately; divergent or conflicting names are semantic debt, not merge candidates.
Run `uv run snail match types --paths` for the full path-level report.

No consolidation candidates at the current threshold.
