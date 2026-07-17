/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_runtime_pools_and_path_template_bank @ 0x408060 */

0040807f        initialize_array_with_constructor(&game->segment_cache.slots, 0x3c, 0x2cb, initialize_active_bod)
00408097        initialize_array_with_constructor(&game->level_definition.segment_slots, 0x4220, 0x64, noop_runtime_slot_constructor)
004080af        initialize_array_with_constructor(&game->level_definition.first_segment.rows, 0x38, 0x100, noop_runtime_slot_constructor)
004080c7        initialize_array_with_constructor(&game->level_definition.last_segment.rows, 0x38, 0x100, noop_runtime_slot_constructor)
004080ea        initialize_array_with_constructor(&game->level_definition_scratch.segment_slots, 0x4220, 0x64, noop_runtime_slot_constructor)
00408102        initialize_array_with_constructor(&game->level_definition_scratch.first_segment.rows, 0x38, 0x100, noop_runtime_slot_constructor)
0040811a        initialize_array_with_constructor(&game->level_definition_scratch.last_segment.rows, 0x38, 0x100, noop_runtime_slot_constructor)
00408130        initialize_bod_base(&game->fringe_attachment_list_head)
0040813b        initialize_bod_base(&game->track_body_list_head)
00408146        initialize_bod_base(&game->barrier_sub_lazer_list_head)
00408151        initialize_bod_base(&game->salt_hazard_list_head)
0040815c        initialize_bod_base(&game->landscape_slice_list_head)
00408167        initialize_bod_base(&game->unknown_bod_355c7c)
00408172        initialize_bod_base(&game->special_track_cell_list_head)
0040817d        initialize_bod_base(&game->unknown_bod_355cec)
00408188        initialize_bod_base(&game->golb_vapour_list_head)
00408193        initialize_bod_base(&game->unknown_bod_355d5c)
0040819e        initialize_track_speedup_runtime(&game->speedup_pickup)
004081a9        initialize_track_jetpack_pickup_runtime(&game->jetpack_pickup)
004081ae        struct SubHealth (* pickup)[0x8] = &game->health_pickups
004081b4        int32_t i_8 = 8
004081c4        int32_t i
004081bb        initialize_track_health_pickup_runtime(pickup)
004081c0        pickup = &(*pickup)[1]
004081c3        i = i_8
004081c3        i_8 -= 1
004081c4        do while (i != 1)
004081c6        struct SlugPool* slug = &game->slug_hazards
004081cc        int32_t i_9 = 8
004081df        int32_t i_1
004081d3        initialize_slug_hazard_runtime(slug)
004081d8        slug = &slug->slots[1]
004081de        i_1 = i_9
004081de        i_9 -= 1
004081df        do while (i_1 != 1)
004081f4        initialize_array_with_constructor(&game->sub_lazers, 0xb0, 0x14, initialize_sub_lazer_runtime)
0040820c        initialize_array_with_constructor(&game->salt_hazards, 0x98, 0x28, initialize_salt_hazard_runtime)
00408211        struct BannerPool* bod = &game->banners
00408217        int32_t i_10 = 2
0040822d        int32_t i_2
0040821e        initialize_bod_base(bod)
00408223        bod->slots[0].bod.bod.vtable = &g_banner_callback_table
00408229        bod = &bod->slots[1]
0040822c        i_2 = i_10
0040822c        i_10 -= 1
0040822d        do while (i_2 != 1)
0040822f        struct SubGarbage (* sub_garbage)[0x32] = &game->garbage_hazards.slots
00408235        int32_t i_11 = 0x32
00408248        int32_t i_3
0040823c        initialize_garbage_hazard(sub_garbage)
00408241        sub_garbage = &(*sub_garbage)[1]
00408247        i_3 = i_11
00408247        i_11 -= 1
00408248        do while (i_3 != 1)
0040824a        struct SubRingPool* ring = &game->ring_effects
00408250        int32_t i_12 = 2
00408263        int32_t i_4
00408257        initialize_track_ring_or_special_effect_runtime(ring)
0040825c        ring = &ring->slots[1]
00408262        i_4 = i_12
00408262        i_12 -= 1
00408263        do while (i_4 != 1)
00408278        initialize_array_with_constructor(&game->fringe_manager, 0x38, 0x1b58, initialize_fringe_object)
00408285        initialize_renderable_bod(&game->player)
00408290        initialize_click_start_controller_runtime(&game->player.click_start)
004082be        initialize_array_with_constructor(&game->player.golb_shots, 0x2e8, 0xc, initialize_golb_shot)
004082c9        initialize_player_presentation_controller(&game->player.presentation)
004082ce        game->player.body.bod.bod.vtable = &g_subgoldy_callback_table
004082d4        struct TrackRowCell (* cell)[0xc80][0x8] = &game->runtime_cells
004082da        int32_t i_13 = 0x6400
004082ea        int32_t i_5
004082e1        initialize_sub_loc(cell)
004082e6        cell = &(*cell)[0][1]
004082e9        i_5 = i_13
004082e9        i_13 -= 1
004082ea        do while (i_5 != 1)
004082ec        struct SubRow* row = &game->runtime_rows
004082f2        int32_t i_14 = 0xc80
00408305        int32_t i_6
004082f9        initialize_track_row_runtime(row)
004082fe        row = &row[1]
00408304        i_6 = i_14
00408304        i_14 -= 1
00408305        do while (i_6 != 1)
00408307        struct PathPair (* edi_3)[0x3f] = &game->path_pairs
0040830d        int32_t i_15 = 0x7e
00408320        int32_t i_7
00408314        initialize_path_template_record_pair(edi_3)
00408319        edi_3 += 0xa8
0040831f        i_7 = i_15
0040831f        i_15 -= 1
00408320        do while (i_7 != 1)
0040832a        initialize_bod_base(&game->barrier)
0040832f        game->barrier.bod.bod.vtable = &g_barrier_actor_callback_table
00408348        initialize_array_with_constructor(&game->landscape_manager, 0x90, 0xa, initialize_active_landscape_entry)
00408363        initialize_array_with_constructor(&game->landscape_manager.scripts, 0x124, 0x80, initialize_landscape_script_record)
00408370        initialize_bod_base(&game->smtrack_heightfield)
00408378        initialize_object_constructor_thunk(&game->smtrack_heightfield.frame_sequence)
00408393        game->smtrack_heightfield.bod.bod.vtable = &g_smtracks_callback_table
00408399        initialize_array_with_constructor(&game->sm_tracks.entries, 0x4088, 0x96, noop_runtime_slot_constructor)
004083b1        initialize_array_with_constructor(&game->parcel_manager, 0x8c, 0x32, initialize_track_parcel_runtime)
004083c9        initialize_array_with_constructor(&game->galaxy.route_slots, 0x2a0, 0x65, noop_runtime_slot_constructor)
004083e1        initialize_array_with_constructor(&game->galaxy.route_names, 0xa0, 0xa, initialize_galaxy_route_name_record)
004083f9        initialize_array_with_constructor(&game->enemy_manager.entries, 0x18, 0x100, noop_runtime_slot_constructor)
00408403        return game
