/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: populate_runtime_track_cells_from_segments @ 0x435eb0 */

00435ec7        int32_t runtime_build_seed
00435ec7        if (game->selected_level_record_active == 0)
00435ed4        int32_t level_mode = game->level_mode
00435edf        if (level_mode == 4 || level_mode == 7)
00435efc        runtime_build_seed = 0
00435ee1        char* var_58_1 = "Seed"
00435ef8        int16_t x87control
00435ef8        runtime_build_seed = ftol(x87control, random_float_below(32768f))
00435ecf        runtime_build_seed = game->selected_level_record->runtime_build_seed
00435efe        int32_t level_mode_1 = game->level_mode
00435f08        int32_t level_mode_arg
00435f08        if (level_mode_1 == 0)
00435f21        level_mode_arg = game->level_mode_arg
00435f36        initialize_high_score_entry(&game->current_high_score_record, runtime_build_seed, level_mode_arg, game->rate_or_level_arg.base_rate, game->runtime_flags, 0, level_mode_arg)
00435f0b        if (level_mode_1 == 1)
00435f19        level_mode_arg = game->level_mode_arg
00435f36        initialize_high_score_entry(&game->current_high_score_record, runtime_build_seed, level_mode_arg, game->rate_or_level_arg.base_rate, game->runtime_flags, 1, level_mode_arg)
00435f0f        if (level_mode_1 == 4)
00435f11        level_mode_arg = game->level_mode_arg
00435f36        initialize_high_score_entry(&game->current_high_score_record, runtime_build_seed, level_mode_arg, game->rate_or_level_arg.base_rate, game->runtime_flags, 2, level_mode_arg)
00435f3b        int32_t subgame_rebuild_selector = game->subgame_rebuild_selector
00435f41        game->replay_update_cursor = 0
00435f49        if (subgame_rebuild_selector == 3)
00435f51        game->subgame_rebuild_selector = 1
00435f5b        game->player.total_score = 0
00435f61        clear_subgoldy_score_buckets(&game->player)
00435f66        game->player.visible_life_stock = 3
00435f72        zero_timer_counters(&game->player.stopwatch)
00435f78        game->player.score_tail = 0
00435f7e        game->player.movement_flag_selector = 0
00435f84        set_math_random_seed(runtime_build_seed)
00435f9f        int16_t x87control_1 = select_level_track_texture_set(&g_game_base->track, game->level_definition.track_texture_set)
00435fa4        int32_t level_mode_2 = game->level_mode
00435fb8        int32_t segment_cursor
00435fb8        int32_t random_length_1
00435fb8        if (level_mode_2 == 0 || level_mode_2 == 7 || level_mode_2 == 4 || level_mode_2 == 1)
0043601e        game->first_block_row_count = game->level_definition.first_segment.row_count
00436021        int32_t random_length = game->level_definition.random_length
00436027        random_length_1 = random_length
0043602b        game->runtime_row_count = random_length
0043602e        if (level_mode_2 == 1)
00436043        level_mode_2, x87control_1 = ftol(x87control_1, (fconvert.t(game->challenge_difficulty_scalar) * fconvert.t(0.649999976f) + fconvert.t(0.349999994f)) * float.t(random_length_1))
00436048        game->runtime_row_count = level_mode_2
00436053        if (game->level_definition.random_enabled == 0)
00436063        int32_t segment_slot_index = 0
00436065        game->runtime_row_count = game->level_definition.last_segment.row_count + game->level_definition.first_segment.row_count
00436070        if (game->level_definition.segment_count s> 0)
00436072        int32_t* segment_row_count_cursor = &game->level_definition.segment_slots[0].row_count
00436078        int32_t segment_row_count
00436078        segment_row_count.b = *segment_row_count_cursor
00436078        segment_row_count:1.b = *(segment_row_count_cursor + 1)
00436078        segment_row_count:2.b = *(segment_row_count_cursor + 2)
00436078        segment_row_count:3.b = *(segment_row_count_cursor + 3)
0043607f        segment_slot_index += 1
00436080        game->runtime_row_count += segment_row_count
00436089        segment_row_count_cursor = &segment_row_count_cursor[0x1088]
00436091        do while (segment_slot_index s< game->level_definition.segment_count)
00436093        segment_cursor = 0
004360a2        game->completion_row_start = game->runtime_row_count - game->level_definition.last_segment.row_count
004360ad        if (game->runtime_row_count s>= 0xc1c)
004360c0        report_errorf("Track (%s) too long, Maximum Length %i", &game->level_definition.level_display_name, 0xc1c)
00435fbc        if (level_mode_2 == 3)
00435fc8        game->first_block_row_count = game->level_definition.first_segment.row_count
00435fd9        int32_t i_5 = 0x10
00435fde        game->runtime_row_count = game->level_definition.last_segment.row_count + game->level_definition.first_segment.row_count
00435ff2        int32_t esi_1
00435ff2        int32_t i
00435fea        esi_1 = game->runtime_row_count + game->level_definition.segment_slots[0].row_count
00435fec        i = i_5
00435fec        i_5 -= 1
00435fed        game->runtime_row_count = esi_1
00435ff2        do while (i != 1)
00435ffa        segment_cursor = 0
00436000        game->completion_row_start = esi_1 - game->level_definition.last_segment.row_count
0043600d        game->completion_row_start = esi_1 - game->level_definition.last_segment.row_count
004360ce        game->track_mirror_enabled = 0
004360d2        game->track_mirror_repeat_count = 0
004360d5        int32_t trampoline_counter = 0
004360d9        char first_or_last_row = 0
004360de        int32_t row_event_owner = 0
004360e2        game->player.follow_state.flag_3c = 0
004360e9        struct Fringe** row_fringe_front_cursor = &game->runtime_cells[0][0].fringe_front
004360ed        int32_t* row_projection_y_cursor = &game->runtime_rows[0].projection_payload.y
004360f3        int32_t rows_remaining = 0xc80
00436192        bool cond:3_1
004360fd        int32_t cell_lanes_remaining = 8
00436102        row_projection_y_cursor[-0x25] = 0
00436108        row_projection_y_cursor[6] = 0
0043610e        __builtin_memset(&row_projection_y_cursor[0x15], 0, 0xc)
00436114        __builtin_memset(&row_projection_y_cursor[1], 0, 0x10)
00436117        *row_projection_y_cursor = 0
00436119        row_projection_y_cursor[-1] = 0
00436129        uint32_t* lane_and_flags_cursor = &row_fringe_front_cursor[-1]
0043615f        int32_t i_1
0043612c        uint32_t cell_lane_and_flags = *lane_and_flags_cursor
0043612e        cell_lane_and_flags:1.b &= 0x5f
00436131        *lane_and_flags_cursor = cell_lane_and_flags
00436133        *(lane_and_flags_cursor - 3) = 0
00436137        *lane_and_flags_cursor = 0
00436146        *lane_and_flags_cursor &= 0xffffafa7
00436148        *lane_and_flags_cursor = 0
0043614d        uint32_t cell_list_flags = lane_and_flags_cursor[-0xf]
00436150        cell_list_flags.b &= 0x7f
00436153        lane_and_flags_cursor[-0xf] = cell_list_flags
00436156        set_color_white(&lane_and_flags_cursor[-6])
0043615b        lane_and_flags_cursor = &lane_and_flags_cursor[0x15]
0043615e        i_1 = cell_lanes_remaining
0043615e        cell_lanes_remaining -= 1
0043615f        do while (i_1 != 1)
00436161        struct Fringe** next_row_fringe_front_cursor = row_fringe_front_cursor
00436165        int32_t remaining_cell_lanes = 8
0043617d        int32_t i_2
0043616a        struct Fringe** cell_fringe_front_cursor = next_row_fringe_front_cursor
0043616e        next_row_fringe_front_cursor = &next_row_fringe_front_cursor[0x15]
00436171        i_2 = remaining_cell_lanes
00436171        remaining_cell_lanes -= 1
00436172        *cell_fringe_front_cursor = nullptr
00436174        cell_fringe_front_cursor[1] = 0
00436177        cell_fringe_front_cursor[2] = 0
0043617a        cell_fringe_front_cursor[3] = 0
0043617d        do while (i_2 != 1)
0043617f        row_fringe_front_cursor = next_row_fringe_front_cursor
00436187        row_projection_y_cursor = &row_projection_y_cursor[0x3d]
0043618d        cond:3_1 = rows_remaining != 1
0043618e        rows_remaining -= 1
00436192        do while (cond:3_1)
0043619f        if (game->level_definition.random_enabled == 1)
004361a7        int32_t i_3 = 0
004361ab        if (game->level_definition.segment_count s> 0)
004361ad        uint8_t* visited_cursor = &game->level_definition.segment_slots[0].visited
004361b3        *visited_cursor = 0
004361bc        i_3 += 1
004361bd        visited_cursor = &visited_cursor[0x4220]
004361c5        do while (i_3 s< game->level_definition.segment_count)
004361ca        int32_t build_row = 0
004361d4        if (game->runtime_row_count s<= 0)
004361d4        return
004361da        int32_t i_4 = 0
004361de        struct SubgameRuntime* runtime = game
004361e4        struct SubSegment* active_segment
004361e4        int32_t segment_row_index_1
004361e4        struct SubSegment* active_segment_4
004361e4        if (i_4 == 0)
004361e6        active_segment_4 = &runtime->level_definition.first_segment
004361ec        first_or_last_row = 1
004361f1        active_segment = active_segment_4
004361f5        active_segment_4->row_base = i_4
00436209        if (i_4 != runtime->completion_row_start || runtime->level_definition.random_enabled != 0)
00436221        runtime->base_subgame_rate = 1f
00436230        if (runtime->level_definition.random_enabled != 1)
004362a4        int32_t segment_cursor_1 = segment_cursor
004362a9        segment_cursor += 1
004362ba        active_segment_4 = &runtime->level_definition.segment_slots[segment_cursor_1]
004362c1        active_segment = active_segment_4
00436236        long double x87_r7_9
00436236        if (runtime->level_mode != 1)
00436254        x87_r7_9 = float.t(runtime->level_definition.segment_count)
0043625a        char* var_58_6 = "Segtra"
00436241        char* var_58_5 = "Segdif"
0043624c        x87_r7_9 = (fconvert.t(runtime->challenge_difficulty_scalar) * fconvert.t(0.899999976f) + fconvert.t(0.100000001f)) * float.t(runtime->level_definition.segment_count)
0043625f        int32_t segment_row_index_2 = segment_row_index_1
0043626b        int32_t eax_26
0043626b        int16_t x87control_2
0043626b        eax_26, x87control_2 = ftol(x87control_1, random_float_below(fconvert.s(x87_r7_9)))
0043627b        int32_t eax_27
0043627b        eax_27, x87control_1 = ftol(x87control_2, float.t(eax_26) * fconvert.t(runtime->base_subgame_rate))
0043628f        active_segment_4 = &runtime->level_definition.segment_slots[eax_27]
00436296        active_segment = active_segment_4
0043629a        active_segment_4->visited = 1
0043620b        active_segment_4 = &runtime->level_definition.last_segment
00436211        first_or_last_row = 1
00436216        active_segment = active_segment_4
0043621a        active_segment_4->row_base = i_4
004362c7        segment_row_index_1 = switch_track_mirror(runtime)
004362cc        int32_t row_count = active_segment_4->row_count
004362cf        active_segment_4->row_base = i_4
004362d3        if (row_count s< 0)
004362da        segment_row_index_1 = report_errorf("Negative Segment Length")
004362e5        int32_t segment_row_index = 0
004362ef        if (i_4 s< runtime->runtime_row_count)
00437168        int32_t j
004362f9        segment_row_index_1 = segment_row_index
00436300        if (segment_row_index_1 s>= *(active_segment + 4))
00436300        break
00436306        int32_t level_mode_3 = runtime->level_mode
0043630c        if (level_mode_3 != 2)
0043630e        j = runtime->completion_row_start
00436313        struct SubSegment* active_segment_1
00436313        if (level_mode_3 == 2 || i_4 s< j)
0043634b        active_segment_1 = active_segment
00436326        if (level_mode_3 != 0 && level_mode_3 != 4 && level_mode_3 != 1 && level_mode_3 != 7)
0043632b        active_segment_1 = &runtime->level_definition_scratch.segment_slots[1]
00436331        if (level_mode_3 == 0 || level_mode_3 == 4 || level_mode_3 == 1 || level_mode_3 == 7 || level_mode_3 == 3)
00436333        active_segment_1 = &runtime->level_definition.last_segment
0043633b        active_segment = active_segment_1
0043633f        if (i_4 == j)
00436341        segment_row_index = 0
00436352        if (level_mode_3 != 2)
00436354        j = active_segment_1->row_count
0043635b        int32_t completion_row_start = runtime->completion_row_start
00436366        if (j - segment_row_index + i_4 s<= completion_row_start)
004363c5        active_segment_1 = active_segment
00436368        active_segment_1 = active_segment
004363a0        if (active_segment_1 != &runtime->level_definition_scratch.segment_slots[1] && active_segment_1 != &runtime->level_definition_scratch.segment_slots[3] && active_segment_1 != &runtime->level_definition_scratch.segment_slots[4] && (level_mode_3 == 0 || level_mode_3 == 4 || level_mode_3 == 1 || level_mode_3 == 7 || level_mode_3 == 3) && active_segment_1 != &runtime->level_definition.last_segment)
004363b7        j = j - completion_row_start - segment_row_index + i_4
004363bb        int32_t ecx_25 = runtime->runtime_row_count + j
004363bd        runtime->completion_row_start = completion_row_start + j
004363c0        runtime->runtime_row_count = ecx_25
004363ce        if (runtime->track_mirror_enabled != 0)
004363d6        int32_t ecx_26 = i_4 * 0x3d
004363ea        *(&runtime->runtime_rows + (ecx_26 << 2)) |= 0x20
004363f7        int32_t ecx_30 = segment_row_index * 7
00436403        struct SubSegmentRowStrideAnchor* segment_row_anchor = active_segment_1 + (ecx_30 << 3)
00436406        if (((*(&active_segment_1->rows + (ecx_30 << 3))).w:1.b & 1) != 0)
0043640e        int32_t ecx_31 = i_4 * 0x3d
00436418        int32_t ecx_32 = *(&runtime->runtime_rows + (ecx_31 << 2))
0043641f        ecx_32:1.b |= 1
00436422        *(&runtime->runtime_rows + (ecx_31 << 2)) = ecx_32
0043642d        if (((segment_row_anchor->row.flags).w:1.b & 0x80) != 0)
00436435        int32_t ecx_33 = i_4 * 0x3d
0043643f        int32_t ecx_34 = *(&runtime->runtime_rows + (ecx_33 << 2))
00436446        ecx_34:1.b |= 0x80
00436449        *(&runtime->runtime_rows + (ecx_33 << 2)) = ecx_34
00436458        struct RuntimeRowStrideAnchor* runtime_row_anchor = runtime + i_4 * 0xf4
0043645c        runtime_row_anchor->row.source_segment = active_segment_1
00436462        runtime_row_anchor->row.row_event_id = row_event_owner
0043646f        if ((segment_row_anchor->row.flags.b & 2) != 0)
00436475        uint32_t flags = runtime_row_anchor->row.flags
0043647b        flags.b |= 2
0043647d        runtime_row_anchor->row.flags = flags
004364a5        set_bod_object(&runtime_row_anchor->row.row_model, g_game_base->directx_loader.cached_x_mesh_slots[segment_row_anchor->row.object_id].object)
004364b0        set_matrix_identity(&runtime_row_anchor->row.row_model.body.transform)
004364c5        int32_t eax_48
004364c5        eax_48.b = segment_row_anchor->row.object_position.x.b
004364c5        eax_48:1.b = segment_row_anchor->row.object_position.x:1.b
004364c5        eax_48:2.b = segment_row_anchor->row.object_position.x:2.b
004364c5        eax_48:3.b = segment_row_anchor->row.object_position.x:3.b
004364c7        runtime_row_anchor->row.row_model.body.transform.position.x = eax_48
004364cc        runtime_row_anchor->row.row_model.body.transform.position.y = segment_row_anchor->row.object_position.y
004364cf        float ecx_42
004364cf        ecx_42.b = segment_row_anchor->row.object_position.z.b
004364cf        ecx_42:1.b = segment_row_anchor->row.object_position.z:1.b
004364d2        runtime_row_anchor->row.row_model.body.transform.position.z = ecx_42
004364db        runtime_row_anchor->row.row_model.body.transform.position.z = fconvert.s(float.t(build_row) + fconvert.t(runtime_row_anchor->row.row_model.body.transform.position.z))
004364e8        if ((segment_row_anchor->row.flags.b & 8) == 0)
0043651c        runtime_row_anchor->row.row_model.velocity.z = 0f
00436522        runtime_row_anchor->row.row_model.velocity.y = 0f
00436528        runtime_row_anchor->row.row_model.velocity.x = 0
004364ea        uint32_t flags_1 = runtime_row_anchor->row.flags
004364f6        flags_1.b |= 8
004364f8        runtime_row_anchor->row.flags = flags_1
00436506        runtime_row_anchor->row.row_model.velocity.x = segment_row_anchor->row.object_velocity.x
0043650f        runtime_row_anchor->row.row_model.velocity.y = segment_row_anchor->row.object_velocity.y
00436515        runtime_row_anchor->row.row_model.velocity.z = segment_row_anchor->row.object_velocity.z
0043652e        active_segment_1 = active_segment
00436539        if ((segment_row_anchor->row.flags.b & 1) != 0)
00436546        runtime_row_anchor->row.flags |= 0x4001
0043656b        runtime_row_anchor->row.parcel_set_id = *(active_segment_1 + (segment_row_index + 0x25) * 0x38)
00436571        float x = segment_row_anchor->row.local_position.x
00436573        runtime_row_anchor->row.projection_payload.x.b = x.b
00436573        *(&runtime_row_anchor->row.projection_payload.x + 1) = x:1.b
00436573        *(&runtime_row_anchor->row.projection_payload.x + 2) = x:2.b
00436573        *(&runtime_row_anchor->row.projection_payload.x + 3) = x:3.b
00436578        runtime_row_anchor->row.projection_payload.y = segment_row_anchor->row.local_position.y
0043657b        int16_t z = (segment_row_anchor->row.local_position.z).w
0043657e        runtime_row_anchor->row.projection_payload.z.b = z.b
0043657e        *(&runtime_row_anchor->row.projection_payload.z + 1) = z:1.b
00436588        if ((segment_row_anchor->row.flags.b & 8) != 0)
0043658a        uint32_t flags_2 = runtime_row_anchor->row.flags
00436590        flags_2.b |= 8
00436592        runtime_row_anchor->row.flags = flags_2
0043659e        runtime_row_anchor->row.attachment_template_index = segment_row_anchor->row.path_template_index
004365ab        if ((segment_row_anchor->row.flags.b & 4) != 0)
004365ad        uint32_t flags_3 = runtime_row_anchor->row.flags
004365b3        flags_3.b |= 4
004365b5        runtime_row_anchor->row.flags = flags_3
004365c8        if ((0x200 & segment_row_anchor->row.flags) != 0)
004365ca        runtime_row_anchor->row.flags |= 0x200
004365dd        if ((0x400 & segment_row_anchor->row.flags) != 0)
004365df        runtime_row_anchor->row.flags |= 0x400
004365f2        if ((0x2000 & segment_row_anchor->row.flags) != 0)
004365f4        runtime_row_anchor->row.flags |= 0x2000
00436607        if ((0x800 & segment_row_anchor->row.flags) != 0)
00436609        runtime_row_anchor->row.flags |= 0x800
0043661c        if ((0x1000 & segment_row_anchor->row.flags) != 0)
0043661e        runtime_row_anchor->row.flags |= 0x1000
00436631        char attachment_entry_installed = 0
00436636        int32_t lane = 0
00436648        *(runtime + ((i_4 + (i_4 * 3 + 0x12414) * 0x14 + 0x615c) << 2)) = segment_row_anchor->row.ring_speed.bits
00437143        bool cond:12_1
00436655        int32_t lane_1
00436655        int32_t lane_2
00436655        if (game->track_mirror_enabled == 0)
00436664        lane_1 = lane
00436668        lane_2 = lane_1
00436657        lane_1 = lane
00436660        lane_2 = 7 - lane_1
00436682        struct RuntimeCellStrideAnchor* runtime_cell_anchor = game + (lane_1 + (build_row << 3)) * 0x54
00436685        uint32_t lane_and_flags = runtime_cell_anchor->cell.lane_and_flags
0043668b        lane_and_flags.b &= 0xe0
0043668f        runtime_cell_anchor->cell.lane_and_flags = lane_and_flags ^ (lane_1 & 7)
0043669f        runtime_cell_anchor->cell.fringe_front = nullptr
004366a1        runtime_cell_anchor->cell.fringe_right = nullptr
004366a4        runtime_cell_anchor->cell.fringe_left = nullptr
004366a7        runtime_cell_anchor->cell.fringe_back = nullptr
004366b1        if (build_row s>= game->first_block_row_count)
004366b6        random_length_1.b = 0
004366bd        if (build_row s< game->first_block_row_count || build_row s>= game->completion_row_start)
004366bf        random_length_1.b = 1
004366ce        set_bod_object(&runtime_cell_anchor->cell, nullptr)
004366e4        struct SubSegment* active_segment_2 = active_segment
004366ee        char* ebp_3 = &active_segment_2->glyph_rows[0][(lane_2 << 8) + segment_row_index]
004366f2        active_segment_2.b = *ebp_3
004366f6        char eax_66 = normalize_segment_glyph_for_track_flags(game, active_segment_2.b, build_row, random_length_1.b)
00436704        if (sx.d(eax_66) - 0x20 u> 0x5d)
00436eb5        label_436eb5:
00436eb5        struct SubSegment* active_segment_3 = active_segment
00436ebd        active_segment_3->source_name
00436ec0        active_segment_3.b = *ebp_3
0043670a        int32_t edx_28 = 0
0043670c        edx_28.b = *(sx.d(eax_66) + &populate_runtime_track_cells_glyph_jump_table[0x14])
00436712        switch (edx_28)
00436719        case 0
00436719        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_EMPTY
00436720        uint32_t list_flags = runtime_cell_anchor->cell.bod.list_flags
00436726        list_flags.b &= 0xdf
00436728        runtime_cell_anchor->cell.bod.list_flags = list_flags
0043674d        case 1
0043674d        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_FLOOR_HASH_MARKER
00436754        uint32_t list_flags_2 = runtime_cell_anchor->cell.bod.list_flags
0043675a        list_flags_2.b &= 0xdf
0043675c        runtime_cell_anchor->cell.bod.list_flags = list_flags_2
004367e5        case 2
004367e5        struct GameRoot* game_base_1 = g_game_base
004367eb        struct Object* object
004367eb        object.b = game_base_1->root_bod_catalog.slide_slices.storage[0].object.b
004367eb        object:1.b = game_base_1->root_bod_catalog.slide_slices.storage[0].object:1.b
004367eb        object:2.b = game_base_1->root_bod_catalog.slide_slices.storage[0].object:2.b
004367eb        object:3.b = game_base_1->root_bod_catalog.slide_slices.storage[0].object:3.b
004367f4        set_bod_object(&runtime_cell_anchor->cell, object)
004367f9        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_HEALTH_PICKUP
00436800        uint32_t list_flags_6 = runtime_cell_anchor->cell.bod.list_flags
00436806        list_flags_6.b |= 0x20
00436808        runtime_cell_anchor->cell.bod.list_flags = list_flags_6
004368f7        case 3
004368f7        struct GameRoot* game_base_3 = g_game_base
004368fd        struct Object* object_2
004368fd        object_2.b = game_base_3->root_bod_catalog.floor_slices.storage[0].object.b
004368fd        object_2:1.b = game_base_3->root_bod_catalog.floor_slices.storage[0].object:1.b
004368fd        object_2:2.b = game_base_3->root_bod_catalog.floor_slices.storage[0].object:2.b
004368fd        object_2:3.b = game_base_3->root_bod_catalog.floor_slices.storage[0].object:3.b
00436906        set_bod_object(&runtime_cell_anchor->cell, object_2)
0043690b        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SALT_HAZARD
00436912        uint32_t list_flags_12 = runtime_cell_anchor->cell.bod.list_flags
00436918        list_flags_12.b |= 0x20
0043691a        runtime_cell_anchor->cell.bod.list_flags = list_flags_12
00436a13        case 4
00436a13        int32_t trampoline_counter_1 = trampoline_counter + 1
00436a14        uint32_t ebp_5 = runtime_cell_anchor->cell.bod.list_flags & 0xffffffdf
00436a1a        trampoline_counter = trampoline_counter_1
00436a1e        runtime_cell_anchor->cell.bod.list_flags = ebp_5
00436a24        uint32_t eax_77 = ebp_5
00436a26        if (trampoline_counter_1 == 0xf)
00436a28        trampoline_counter = 0
00436a30        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_TRAMPOLINE
00436a3f        if (trampoline_counter_1 != 8)
00436aab        eax_77.b &= 0xdf
00436aad        runtime_cell_anchor->cell.bod.list_flags = eax_77
00436ab3        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_TRAMPOLINE
00436a41        struct GameRoot* game_base_5 = g_game_base
00436a47        struct Object* object_4
00436a47        object_4.b = game_base_5->root_bod_catalog.trampoline.object.b
00436a47        object_4:1.b = game_base_5->root_bod_catalog.trampoline.object:1.b
00436a47        object_4:2.b = game_base_5->root_bod_catalog.trampoline.object:2.b
00436a47        object_4:3.b = game_base_5->root_bod_catalog.trampoline.object:3.b
00436a50        set_bod_object(&runtime_cell_anchor->cell, object_4)
00436a72        runtime_cell_anchor->cell.bod.list_flags |= 0x20
00436a9a        store_color4f(game + (lane + (build_row << 3) + 0xb6cc) * 0x54, 1f, 1f, 1f, 0.999000013f)
00436a9f        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_TRAMPOLINE
00436961        case 5
00436961        set_bod_object(&runtime_cell_anchor->cell, g_game_base->root_bod_catalog.slide_slices.storage[0].object)
00436966        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SPEEDUP_PICKUP
0043696d        uint32_t list_flags_14 = runtime_cell_anchor->cell.bod.list_flags
00436973        list_flags_14.b |= 0x20
00436975        runtime_cell_anchor->cell.bod.list_flags = list_flags_14
00436933        case 6
00436933        set_bod_object(&runtime_cell_anchor->cell.bod.vtable, g_game_base->root_bod_catalog.universe_hole.object)
00436938        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_UNIVERSE_HOLE
0043693f        uint32_t list_flags_13 = runtime_cell_anchor->cell.bod.list_flags
00436945        list_flags_13.b |= 0x20
00436947        runtime_cell_anchor->cell.bod.list_flags = list_flags_13
004369bc        case 7
004369bc        set_bod_object(&runtime_cell_anchor->cell.bod.vtable, g_game_base->root_bod_catalog.floor_slices.storage[0].object)
004369c1        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_FLOOR_DASH
004369c8        uint32_t list_flags_16 = runtime_cell_anchor->cell.bod.list_flags
004369ce        list_flags_16.b |= 0x20
004369d0        runtime_cell_anchor->cell.bod.list_flags = list_flags_16
004368aa        case 8
004368aa        set_bod_object(&runtime_cell_anchor->cell.bod.vtable, g_game_base->root_bod_catalog.floor_slices.storage[0].object)
004368af        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_FLOOR_DOT
004368b6        uint32_t list_flags_10 = runtime_cell_anchor->cell.bod.list_flags
004368bc        list_flags_10.b |= 0x20
004368be        runtime_cell_anchor->cell.bod.list_flags = list_flags_10
00436e02        case 9
00436e02        if (game->level_mode == 1)
00436e08        uint32_t flags_4 = runtime_row_anchor->row.flags
00436e0e        flags_4:1.b &= 0xbf
00436e1a        runtime_row_anchor->row.flags = flags_4 | 1
00436e20        runtime_row_anchor->row.parcel_set_id = 0
00436e30        runtime_row_anchor->row.projection_payload.x = fconvert.s(float.t(lane) - fconvert.t(4f) + fconvert.t(0.5f))
00436e40        runtime_row_anchor->row.projection_payload.y = runtime_cell_anchor->cell.anchor_position.y
00436e4c        runtime_row_anchor->row.projection_payload.z = fconvert.s(float.t(build_row) + fconvert.t(0.5f))
00436e57        if (game->track_mirror_enabled != 0)
00436e65        runtime_row_anchor->row.projection_payload.x = fconvert.s(fconvert.t(runtime_row_anchor->row.projection_payload.x) * fconvert.t(-1f))
00436e02        goto label_436e6b
00436e6b        case 0xa
00436e6b        label_436e6b:
00436e72        if ((runtime_row_anchor->row.flags.b & 0xc0) != 0)
00436e9e        uint32_t list_flags_27 = runtime_cell_anchor->cell.bod.list_flags
00436ea4        list_flags_27.b &= 0xdf
00436ea6        runtime_cell_anchor->cell.bod.list_flags = list_flags_27
00436eac        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_EMPTY
00436e82        set_bod_object(&runtime_cell_anchor->cell, g_game_base->root_bod_catalog.slide_slices.storage[0].object)
00436e87        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SLIDE_UNDERSCORE
00436e8e        uint32_t list_flags_26 = runtime_cell_anchor->cell.bod.list_flags
00436e94        list_flags_26.b |= 0x20
00436e96        runtime_cell_anchor->cell.bod.list_flags = list_flags_26
00436c67        case 0xb
00436c67        struct GameRoot* game_base_8 = g_game_base
00436c6d        struct Object* object_7
00436c6d        object_7.b = game_base_8->root_bod_catalog.ramp_edges[1].object.b
00436c6d        object_7:1.b = game_base_8->root_bod_catalog.ramp_edges[1].object:1.b
00436c6d        object_7:2.b = game_base_8->root_bod_catalog.ramp_edges[1].object:2.b
00436c6d        object_7:3.b = game_base_8->root_bod_catalog.ramp_edges[1].object:3.b
00436c76        set_bod_object(&runtime_cell_anchor->cell, object_7)
00436c7d        runtime_cell_anchor->cell.render_arg_1c = 0
00436c83        runtime_cell_anchor->cell.render_arg_20 = 0f
00436c89        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_LESS
00436c90        uint32_t list_flags_24 = runtime_cell_anchor->cell.bod.list_flags
00436c96        list_flags_24.b |= 0x20
00436c98        runtime_cell_anchor->cell.bod.list_flags = list_flags_24
004369ea        case 0xc
004369ea        set_bod_object(&runtime_cell_anchor->cell, g_game_base->root_bod_catalog.pillars[0].object)
004369ef        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_WALL2
004369f6        uint32_t list_flags_17 = runtime_cell_anchor->cell.bod.list_flags
004369fc        list_flags_17.b |= 0x20
004369fe        runtime_cell_anchor->cell.bod.list_flags = list_flags_17
00436ad0        case 0xd
00436ad0        if (build_row s<= 0 || runtime_cell_anchor->previous_row_same_lane.tile_id != SUBLOC_TILE_RAMP_GREATER)
00436b21        set_bod_object(&runtime_cell_anchor->cell.bod.vtable, g_game_base->root_bod_catalog.ramp_edges[1].object)
00436b26        runtime_cell_anchor->cell.render_arg_1c = 0
00436b2c        runtime_cell_anchor->cell.render_arg_20 = 0f
00436b32        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_GREATER
00436b39        uint32_t list_flags_19 = runtime_cell_anchor->cell.bod.list_flags
00436b3f        list_flags_19.b |= 0x20
00436b41        runtime_cell_anchor->cell.bod.list_flags = list_flags_19
00436ad2        struct GameRoot* game_base_6 = g_game_base
00436ad8        struct Object* object_5
00436ad8        object_5.b = game_base_6->root_bod_catalog.ramp_edges[1].object.b
00436ad8        object_5:1.b = game_base_6->root_bod_catalog.ramp_edges[1].object:1.b
00436ad8        object_5:2.b = game_base_6->root_bod_catalog.ramp_edges[1].object:2.b
00436ad8        object_5:3.b = game_base_6->root_bod_catalog.ramp_edges[1].object:3.b
00436ae1        set_bod_object(&runtime_cell_anchor->cell, object_5)
00436ae6        runtime_cell_anchor->cell.render_arg_1c = 0
00436aec        runtime_cell_anchor->cell.render_arg_20 = 0f
00436af2        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_GREATER_RAISED
00436af9        uint32_t list_flags_18 = runtime_cell_anchor->cell.bod.list_flags
00436aff        list_flags_18.b |= 0x20
00436b01        runtime_cell_anchor->cell.bod.list_flags = list_flags_18
00436b07        runtime_cell_anchor->previous_row_same_lane.tile_id = SUBLOC_TILE_RAMP_GREATER_BACKPATCH
0043676b        case 0xe
0043676b        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_EMPTY
00436772        uint32_t list_flags_3 = runtime_cell_anchor->cell.bod.list_flags
00436778        list_flags_3.b &= 0xdf
0043677a        runtime_cell_anchor->cell.bod.list_flags = list_flags_3
00436780        switch_track_mirror(game)
0043686e        case 0xf
0043686e        struct GameRoot* game_base_2 = g_game_base
00436874        struct Object* object_1
00436874        object_1.b = game_base_2->root_bod_catalog.slide_slices.storage[0].object.b
00436874        object_1:1.b = game_base_2->root_bod_catalog.slide_slices.storage[0].object:1.b
00436874        object_1:2.b = game_base_2->root_bod_catalog.slide_slices.storage[0].object:2.b
00436874        object_1:3.b = game_base_2->root_bod_catalog.slide_slices.storage[0].object:3.b
0043687d        set_bod_object(&runtime_cell_anchor->cell, object_1)
00436882        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SLIDE_F
00436889        uint32_t list_flags_9 = runtime_cell_anchor->cell.bod.list_flags
0043688f        list_flags_9.b |= 0x20
00436891        runtime_cell_anchor->cell.bod.list_flags = list_flags_9
00436798        case 0x10
00436798        set_bod_object(&runtime_cell_anchor->cell.bod.vtable, g_game_base->root_bod_catalog.slide_slices.storage[0].object)
0043679d        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_GLYPH_G
004367a4        uint32_t list_flags_4 = runtime_cell_anchor->cell.bod.list_flags
004367aa        list_flags_4.b |= 0x20
004367ac        runtime_cell_anchor->cell.bod.list_flags = list_flags_4
00436980        case 0x11
00436980        struct GameRoot* game_base_4 = g_game_base
00436986        struct Object* object_3
00436986        object_3.b = game_base_4->root_bod_catalog.slide_slices.storage[0].object.b
00436986        object_3:1.b = game_base_4->root_bod_catalog.slide_slices.storage[0].object:1.b
00436986        object_3:2.b = game_base_4->root_bod_catalog.slide_slices.storage[0].object:2.b
00436986        object_3:3.b = game_base_4->root_bod_catalog.slide_slices.storage[0].object:3.b
0043698f        set_bod_object(&runtime_cell_anchor->cell, object_3)
00436994        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_JETPACK_PICKUP
0043699b        uint32_t list_flags_15 = runtime_cell_anchor->cell.bod.list_flags
004369a1        list_flags_15.b |= 0x20
004369a3        runtime_cell_anchor->cell.bod.list_flags = list_flags_15
0043684f        case 0x12
0043684f        set_bod_object(&runtime_cell_anchor->cell, g_game_base->root_bod_catalog.slide_slices.storage[0].object)
00436854        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SLUG_HAZARD
0043685b        uint32_t list_flags_8 = runtime_cell_anchor->cell.bod.list_flags
00436861        list_flags_8.b |= 0x20
00436863        runtime_cell_anchor->cell.bod.list_flags = list_flags_8
00436ce0        case 0x13
00436ce0        if (eax_66 == 0x50)
00436ce2        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_PATH_ENTRY_UPPERCASE
00436ced        if (eax_66 == 0x70)
00436cef        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_PATH_ENTRY_LOWERCASE
00436cfa        int32_t attachment_template_index = runtime_row_anchor->row.attachment_template_index
00436d05        int32_t eax_91 = attachment_template_index << 3
00436d0c        struct Path* ecx_98
00436d0c        if (game->track_mirror_enabled == 0)
00436d27        ecx_98 = &game->path_pairs + (eax_91 - attachment_template_index) * 0x30
00436d16        ecx_98 = &game->path_pairs[0].secondary + (eax_91 - attachment_template_index) * 0x30
00436d32        runtime_cell_anchor->cell.attachment_template_record = ecx_98
00436d43        runtime_cell_anchor->cell.bod.list_flags &= 0xffffffdf
00436d49        if (attachment_entry_installed == 0)
00436d57        attachment_entry_installed = 1
00436d60        set_bod_object(&runtime_cell_anchor->cell, runtime_cell_anchor->cell.attachment_template_record->bod.object)
00436d72        runtime_cell_anchor->cell.bod.list_flags |= 0x20
00436d8b        set_bod_object(&runtime_row_anchor->row.attachment_body, runtime_cell_anchor->cell.attachment_template_record->fringe_mesh_bod.object)
00436d9c        runtime_row_anchor->row.attachment_body.bod.list_flags |= 0x20
00436da8        runtime_row_anchor->row.installed_heading_delta = active_segment->angle_radians.bits
00436db4        int32_t k = 0
00436dbb        if (runtime_cell_anchor->cell.attachment_template_record->row_span_count s> 0)
00436dc1        struct SubRow* stamped_row = &runtime_row_anchor->row
00436dc7        int32_t eax_100
00436dc7        eax_100.b = stamped_row->flags.b
00436dc7        eax_100:1.b = stamped_row->flags:1.b
00436dc7        eax_100:2.b = stamped_row->flags:2.b
00436dc7        eax_100:3.b = stamped_row->flags:3.b
00436dcb        if ((eax_100.b & 0x40) == 0)
00436dd9        eax_100.b |= 0x40
00436ddb        stamped_row->flags.b = eax_100.b
00436ddb        stamped_row->flags:1.b = eax_100:1.b
00436ddb        stamped_row->flags:2.b = eax_100:2.b
00436ddb        stamped_row->flags:3.b = eax_100:3.b
00436ddd        stamped_row->primary_attachment_cell = &runtime_cell_anchor->cell
00436dcd        eax_100.b |= 0x80
00436dcf        stamped_row->flags.b = eax_100.b
00436dcf        stamped_row->flags:1.b = eax_100:1.b
00436dcf        stamped_row->flags:2.b = eax_100:2.b
00436dcf        stamped_row->flags:3.b = eax_100:3.b
00436dd1        stamped_row->secondary_attachment_cell = &runtime_cell_anchor->cell
00436de9        k += 1
00436dea        stamped_row = &stamped_row[1]
00436df3        do while (k s< runtime_cell_anchor->cell.attachment_template_record->row_span_count)
00436733        case 0x14
00436733        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RING_MARKER
0043673a        uint32_t list_flags_1 = runtime_cell_anchor->cell.bod.list_flags
00436740        list_flags_1.b &= 0xdf
00436742        runtime_cell_anchor->cell.bod.list_flags = list_flags_1
00436cb1        case 0x15
00436cb1        set_bod_object(&runtime_cell_anchor->cell.bod.vtable, g_game_base->root_bod_catalog.ramp_edges[0].object)
00436cb8        runtime_cell_anchor->cell.render_arg_1c = 0
00436cbe        runtime_cell_anchor->cell.render_arg_20 = 0f
00436cc4        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_LEFT_BRACKET
00436ccb        uint32_t list_flags_25 = runtime_cell_anchor->cell.bod.list_flags
00436cd1        list_flags_25.b |= 0x20
00436cd3        runtime_cell_anchor->cell.bod.list_flags = list_flags_25
004367c6        case 0x16
004367c6        set_bod_object(&runtime_cell_anchor->cell, g_game_base->root_bod_catalog.slide_slices.storage[0].object)
004367cb        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SLIDE_UNDERSCORE
004367d2        uint32_t list_flags_5 = runtime_cell_anchor->cell.bod.list_flags
004367d8        list_flags_5.b |= 0x20
004367da        runtime_cell_anchor->cell.bod.list_flags = list_flags_5
00436821        case 0x17
00436821        set_bod_object(&runtime_cell_anchor->cell.bod.vtable, g_game_base->root_bod_catalog.slide_slices.storage[0].object)
00436826        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_SLIDE_O
0043682d        uint32_t list_flags_7 = runtime_cell_anchor->cell.bod.list_flags
00436833        list_flags_7.b |= 0x20
00436835        runtime_cell_anchor->cell.bod.list_flags = list_flags_7
004368d8        case 0x18
004368d8        set_bod_object(&runtime_cell_anchor->cell, g_game_base->root_bod_catalog.floor_slices.storage[0].object)
004368dd        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_GARBAGE_HAZARD
004368e4        uint32_t list_flags_11 = runtime_cell_anchor->cell.bod.list_flags
004368ea        list_flags_11.b |= 0x20
004368ec        runtime_cell_anchor->cell.bod.list_flags = list_flags_11
00436beb        case 0x19
00436beb        if (build_row s<= 0 || runtime_cell_anchor->previous_row_same_lane.tile_id != SUBLOC_TILE_RAMP_GREATER)
00436c3c        set_bod_object(&runtime_cell_anchor->cell, g_game_base->root_bod_catalog.ramp_edges[0].object)
00436c41        runtime_cell_anchor->cell.render_arg_1c = 0
00436c47        runtime_cell_anchor->cell.render_arg_20 = 0f
00436c4d        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_LEFT_BRACE
00436c54        uint32_t list_flags_23 = runtime_cell_anchor->cell.bod.list_flags
00436c5a        list_flags_23.b |= 0x20
00436c5c        runtime_cell_anchor->cell.bod.list_flags = list_flags_23
00436bfb        set_bod_object(&runtime_cell_anchor->cell, g_game_base->root_bod_catalog.ramp_edges[0].object)
00436c00        runtime_cell_anchor->cell.render_arg_1c = 0
00436c06        runtime_cell_anchor->cell.render_arg_20 = 0f
00436c0c        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED
00436c13        uint32_t list_flags_22 = runtime_cell_anchor->cell.bod.list_flags
00436c19        list_flags_22.b |= 0x20
00436c1b        runtime_cell_anchor->cell.bod.list_flags = list_flags_22
00436c21        runtime_cell_anchor->previous_row_same_lane.tile_id = SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH
00436b5d        case 0x1a
00436b5d        if (build_row s<= 0 || runtime_cell_anchor->previous_row_same_lane.tile_id != SUBLOC_TILE_RAMP_GREATER)
00436ba0        struct GameRoot* game_base_7 = g_game_base
00436ba6        struct Object* object_6
00436ba6        object_6.b = game_base_7->root_bod_catalog.ramp_edges[2].object.b
00436ba6        object_6:1.b = game_base_7->root_bod_catalog.ramp_edges[2].object:1.b
00436ba6        object_6:2.b = game_base_7->root_bod_catalog.ramp_edges[2].object:2.b
00436ba6        object_6:3.b = game_base_7->root_bod_catalog.ramp_edges[2].object:3.b
00436baf        set_bod_object(&runtime_cell_anchor->cell, object_6)
00436bb4        runtime_cell_anchor->cell.render_arg_1c = 0
00436bba        runtime_cell_anchor->cell.render_arg_20 = 0f
00436bc0        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_RIGHT_BRACE
00436bc7        uint32_t list_flags_21 = runtime_cell_anchor->cell.bod.list_flags
00436bcd        list_flags_21.b |= 0x20
00436bcf        runtime_cell_anchor->cell.bod.list_flags = list_flags_21
00436b6e        set_bod_object(&runtime_cell_anchor->cell, g_game_base->root_bod_catalog.ramp_edges[2].object)
00436b73        runtime_cell_anchor->cell.render_arg_1c = 0
00436b79        runtime_cell_anchor->cell.render_arg_20 = 0f
00436b7f        runtime_cell_anchor->cell.tile_id = SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED
00436b86        uint32_t list_flags_20 = runtime_cell_anchor->cell.bod.list_flags
00436b8c        list_flags_20.b |= 0x20
00436b8e        runtime_cell_anchor->cell.bod.list_flags = list_flags_20
00436b94        runtime_cell_anchor->previous_row_same_lane.tile_id = SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH
00436712        case 0x1b
00436712        goto label_436eb5
00436eea        runtime_cell_anchor->cell.anchor_position.z = 0f
00436eed        runtime_cell_anchor->cell.anchor_position.y = 0f
00436ef0        runtime_cell_anchor->cell.anchor_position.x = 0
00436ef2        runtime_row_anchor->row.attachment_body.position.z = 0f
00436ef8        runtime_row_anchor->row.attachment_body.position.y = 0f
00436efe        runtime_row_anchor->row.attachment_body.position.x = 0
00436f04        enum SubLocTileId tile_id = runtime_cell_anchor->cell.tile_id
00436f10        float var_28_1
00436f10        if (tile_id == SUBLOC_TILE_PATH_ENTRY_LOWERCASE || tile_id == SUBLOC_TILE_PATH_ENTRY_UPPERCASE)
00436f67        runtime_cell_anchor->cell.anchor_position.x = 0
00436f69        long double x87_r7_28 = float.t(build_row) + fconvert.t(0.5f)
00436f6f        var_28_1 = fconvert.s(x87_r7_28)
00436f73        long double x87_r7_29 = x87_r7_28 - fconvert.t(0.5f)
00436f79        runtime_cell_anchor->cell.anchor_position.z = fconvert.s(x87_r7_29)
00436f86        if ((g_runtime_config.render_flags.b & 0x20) == 0)
00436ff3        uint32_t list_flags_28 = runtime_row_anchor->row.attachment_body.bod.list_flags
00436ff9        list_flags_28.b &= 0xdf
00436ffd        runtime_row_anchor->row.attachment_body.bod.list_flags = list_flags_28
00436f88        runtime_row_anchor->row.attachment_body.position.x = 0
00436f92        runtime_row_anchor->row.attachment_body.position.z = fconvert.s(x87_r7_29)
00436fa4        struct tColour out
00436fa4        struct tColour* eax_109 = get_track_skirt_color(&g_game_base->subgame, &out)
00436fb4        float r = eax_109->r
00436fb6        runtime_row_anchor->row.attachment_body.color.r.b = r.b
00436fb6        runtime_row_anchor->row.attachment_body.color.r:1.b = r:1.b
00436fb6        runtime_row_anchor->row.attachment_body.color.r:2.b = r:2.b
00436fb6        runtime_row_anchor->row.attachment_body.color.r:3.b = r:3.b
00436fbb        runtime_row_anchor->row.attachment_body.color.g = eax_109->g
00436fbe        int16_t b_1 = (eax_109->b).w
00436fc1        runtime_row_anchor->row.attachment_body.color.b.b = b_1.b
00436fc1        runtime_row_anchor->row.attachment_body.color.b:1.b = b_1:1.b
00436fc7        runtime_row_anchor->row.attachment_body.color.a = eax_109->a
00436fd3        float g = eax_109->g
00436fdc        float b = eax_109->b
00436fdf        float a = eax_109->a
00436fe9        x87control_1 = set_object_color(runtime_row_anchor->row.attachment_body.object, eax_109->r)
00436f22        runtime_cell_anchor->cell.anchor_position.x = fconvert.s(float.t(lane) - fconvert.t(4f) + fconvert.t(0.5f))
00436f24        runtime_cell_anchor->cell.anchor_position.y = 0f
00436f2a        tile_id = runtime_cell_anchor->cell.tile_id
00436f3a        if (tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED || tile_id == SUBLOC_TILE_RAMP_GREATER_RAISED || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED)
00436f3c        runtime_cell_anchor->cell.anchor_position.y = 0.5f
00436f50        var_28_1 = fconvert.s(float.t(build_row) + fconvert.t(0.5f))
00436f58        runtime_cell_anchor->cell.anchor_position.z = var_28_1
00437014        if (build_row s< 4 && game->level_mode != 2)
0043701f        runtime_cell_anchor->cell.anchor_position.y = game->path_pairs[0x24].primary.primary_samples->transform.position.y
0043702c        if (runtime_cell_anchor->cell.tile_id == SUBLOC_TILE_UNIVERSE_HOLE)
0043703a        runtime_cell_anchor->cell.anchor_position.y = fconvert.s(fconvert.t(runtime_cell_anchor->cell.anchor_position.y) - fconvert.t(0.0299999993f))
00437040        tile_id = runtime_cell_anchor->cell.tile_id
00437080        if (tile_id == SUBLOC_TILE_FLOOR_DOT || tile_id == SUBLOC_TILE_FLOOR_DASH || tile_id == SUBLOC_TILE_FLOOR_VARIANT_14 || tile_id == SUBLOC_TILE_GARBAGE_HAZARD || tile_id == SUBLOC_TILE_SALT_HAZARD || tile_id == SUBLOC_TILE_SLIDE_UNDERSCORE || tile_id == SUBLOC_TILE_SLIDE_O || tile_id == SUBLOC_TILE_HEALTH_PICKUP || tile_id == SUBLOC_TILE_SPEEDUP_PICKUP || tile_id == SUBLOC_TILE_JETPACK_PICKUP || tile_id == SUBLOC_TILE_SLIDE_VARIANT_1A || tile_id == SUBLOC_TILE_FLOOR_VARIANT_1B || tile_id == SUBLOC_TILE_SLUG_HAZARD || tile_id == SUBLOC_TILE_SLIDE_F || tile_id == SUBLOC_TILE_GLYPH_G)
0043708d        int32_t ecx_119 = build_row & 0x80000007
004370a1        runtime_cell_anchor->cell.render_arg_1c = fconvert.s(float.t(8 - lane) * fconvert.t(0.125f))
004370a7        if (ecx_119 s< 0)
004370ad        ecx_119 = ((ecx_119 - 1) | 0xfffffff8) + 1
004370bc        runtime_cell_anchor->cell.render_arg_20 = fconvert.s(float.t(ecx_119) * fconvert.t(0.125f))
004370c9        if (runtime_cell_anchor->cell.tile_id == SUBLOC_TILE_WIDE_VARIANT_1F)
004370d3        runtime_cell_anchor->cell.anchor_position.x = fconvert.s(fconvert.t(runtime_cell_anchor->cell.anchor_position.x) * fconvert.t(1.10000002f))
004370dc        if (runtime_cell_anchor->cell.tile_id == SUBLOC_TILE_TRAMPOLINE)
004370ea        if (game->level_mode != 3 || ((game->runtime_flags).w:1.b & 4) != 0)
004370ec        runtime_cell_anchor->cell.anchor_position.y = -3f
004370fa        runtime_cell_anchor->cell.anchor_position.z = var_28_1
00437100        struct Fringe** fringe_slot = &runtime_cell_anchor->cell.fringe_front
00437104        int32_t remaining_fringe_slots = 4
00437135        int32_t k_1
00437109        struct Fringe* fringe_object
00437109        fringe_object.b = *fringe_slot
00437109        fringe_object:1.b = *(fringe_slot + 1)
00437109        fringe_object:2.b = *(fringe_slot + 2)
00437109        fringe_object:3.b = *(fringe_slot + 3)
0043710f        if (fringe_object != 0)
00437111        fringe_object->bod.position.z = 0f
00437114        fringe_object->bod.position.y = 0f
00437117        fringe_object->bod.position.x = 0
0043711a        struct Fringe* fringe_object_reloaded
0043711a        fringe_object_reloaded.b = *fringe_slot
0043711a        fringe_object_reloaded:1.b = *(fringe_slot + 1)
0043711a        fringe_object_reloaded:2.b = *(fringe_slot + 2)
0043711a        fringe_object_reloaded:3.b = *(fringe_slot + 3)
00437123        fringe_object_reloaded->bod.position.x = runtime_cell_anchor->cell.anchor_position.x
00437128        fringe_object_reloaded->bod.position.y = runtime_cell_anchor->cell.anchor_position.y
0043712e        fringe_object_reloaded->bod.position.z = runtime_cell_anchor->cell.anchor_position.z
00437131        fringe_slot = &fringe_slot[1]
00437134        k_1 = remaining_fringe_slots
00437134        remaining_fringe_slots -= 1
00437135        do while (k_1 != 1)
0043713c        cond:12_1 = lane + 1 s< 8
0043713f        lane += 1
00437143        do while (cond:12_1)
00437159        j = build_row + 1
0043715a        segment_row_index += 1
00437160        build_row = j
00437164        i_4 = j
00437166        runtime = game
00437168        do while (j s< game->runtime_row_count)
0043717a        if (runtime->level_mode != 3 || first_or_last_row == 0)
0043717c        row_event_owner += 1
00437183        do while (i_4 s< runtime->runtime_row_count)
00437190        return
