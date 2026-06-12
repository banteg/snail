# Matching Status

Regenerate with `uv run snail match status --write tools/match/STATUS.md`.

**36/45** functions matched, **2080/5199** bytes.

| | function | address | bytes | insns | match | build |
|---|---|---|---|---|---|---|
| 🚧 | update_row_event_display | 0x404cf0 | 836 | 219/214 | 78.52% | msvc6.5 /O2 /G5 /W3 |
| ✅ | initialize_track_speedup_runtime | 0x4084b0 | 18 | 7/7 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | initialize_track_jetpack_pickup_runtime | 0x4084d0 | 55 | 17/17 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | initialize_track_health_pickup_runtime | 0x408510 | 18 | 7/7 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | initialize_slug_hazard_runtime | 0x408530 | 18 | 7/7 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | initialize_garbage_hazard | 0x408550 | 18 | 7/7 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| 🚧 | search_path_for_golb | 0x415e30 | 192 | 63/63 | 92.06% | msvc6.5 /O2 /G5 /W3 |
| 🚧 | begin_track_attachment_follow_state | 0x420c40 | 98 | 27/27 | 88.89% | msvc6.5 /O2 /G5 /W3 |
| ✅ | initialize_path_follow_golb | 0x421770 | 58 | 16/16 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| 🚧 | try_enter_track_attachment_from_swept_motion | 0x42c770 | 800 | 205/204 | 37.16% | msvc6.5 /O2 /G5 /W3 /Op |
| 🚧 | mark_track_warning_zones | 0x4354f0 | 251 | 104/99 | 32.51% | msvc6.5 /O2 /G5 /W3 |
| 🚧 | switch_track_mirror | 0x435e60 | 79 | 27/30 | 91.23% | msvc6.5 /O2 /G5 /W3 |
| ✅ | is_slide_cache_tile_family | 0x439a40 | 33 | 17/17 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | is_ramp_cache_tile_family | 0x439a70 | 57 | 29/29 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | is_open_neighbor_tile_family | 0x439ab0 | 29 | 15/15 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | is_floor_cache_tile_family | 0x439ad0 | 41 | 21/21 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | end_jetpack_hover | 0x43a370 | 28 | 9/9 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | uninit_jet_particles | 0x43a580 | 36 | 17/17 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | initialize_jetpack_gauge | 0x43a930 | 65 | 15/15 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | arm_jetpack_gauge | 0x43a980 | 55 | 18/18 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | show_subgoldy_lives | 0x43af10 | 66 | 23/23 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | begin_post_follow_carryover | 0x43af60 | 97 | 20/20 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| 🚧 | play_movement_state_sound | 0x43afd0 | 335 | 90/88 | 80.90% | msvc6.5 /O2 /G5 /W3 |
| ✅ | spawn_track_speedup | 0x43d880 | 3 | 1/1 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | update_track_jetpack_pickup | 0x43ee50 | 340 | 103/103 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| 🚧 | spawn_sub_lazer_projectile | 0x441670 | 195 | 63/63 | 98.41% | msvc6.5 /O2 /G5 /W3 |
| 🚧 | project_position_onto_track_attachment | 0x4444b0 | 333 | 94/106 | 56.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | initialize_invincible_shell | 0x444ac0 | 31 | 7/7 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | start_invincible_shell | 0x444ae0 | 97 | 21/21 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | kill_subgoldy | 0x445840 | 17 | 6/6 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | update_times_up | 0x445e20 | 75 | 26/26 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | uninit_times_up | 0x445e70 | 27 | 8/8 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | show_times_up_message | 0x445e90 | 116 | 31/31 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | hide_gameplay_scores | 0x445f10 | 35 | 12/12 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | unhide_gameplay_scores | 0x445f40 | 27 | 8/8 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | initialize_snail_skin | 0x445f60 | 27 | 6/6 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | update_snail_skin_transition | 0x445f80 | 69 | 25/25 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | change_snail_skin | 0x445fd0 | 69 | 19/19 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | initialize_warning | 0x446e80 | 130 | 32/32 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | uninit_warning | 0x446f10 | 22 | 6/6 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | start_warning | 0x446f30 | 21 | 4/4 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | stop_warning | 0x446f50 | 14 | 3/3 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | stop_warning_sample | 0x446f60 | 24 | 7/7 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | update_warning | 0x446f80 | 179 | 52/52 | 100.00% | msvc6.5 /O2 /G5 /W3 |
| ✅ | get_track_cell_row_index | 0x447040 | 65 | 22/22 | 100.00% | msvc6.5 /O2 /G5 /W3 |
