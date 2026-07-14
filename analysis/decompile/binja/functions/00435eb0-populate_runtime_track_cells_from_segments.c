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
00435f36        initialize_high_score_entry(&game->current_high_score_record.active, runtime_build_seed, level_mode_arg, game->rate_or_level_arg.base_rate, game->runtime_flags, 0, level_mode_arg)
00435f0b        if (level_mode_1 == 1)
00435f19        level_mode_arg = game->level_mode_arg
00435f36        initialize_high_score_entry(&game->current_high_score_record.active, runtime_build_seed, level_mode_arg, game->rate_or_level_arg.base_rate, game->runtime_flags, 1, level_mode_arg)
00435f0f        if (level_mode_1 == 4)
00435f11        level_mode_arg = game->level_mode_arg
00435f36        initialize_high_score_entry(&game->current_high_score_record.active, runtime_build_seed, level_mode_arg, game->rate_or_level_arg.base_rate, game->runtime_flags, 2, level_mode_arg)
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
00435f9f        int16_t x87control_1 = select_level_track_texture_set(&g_game_base[0xb24], game->level_definition.track_texture_set)
00435fa4        int32_t level_mode_2 = game->level_mode
00435fb8        int32_t var_24
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
00436063        int32_t i = 0
00436065        game->runtime_row_count = game->level_definition.last_segment.row_count + game->level_definition.first_segment.row_count
00436070        if (game->level_definition.segment_count s> 0)
00436072        int32_t* ecx_10 = &game->level_definition.segment_slots[0].row_count
00436078        int32_t edx_7
00436078        edx_7.b = (ecx_10 - 0xa87c)->:0xa87c.b
00436078        edx_7:1.b = (ecx_10 - 0xa87c)->:0xa87d.b
00436078        edx_7:2.b = (ecx_10 - 0xa87c)->:0xa87e.b
00436078        edx_7:3.b = (ecx_10 - 0xa87c)->:0xa87f.b
0043607f        i += 1
00436080        game->runtime_row_count += edx_7
00436089        ecx_10 = &ecx_10[0x1088]
00436091        do while (i s< game->level_definition.segment_count)
00436093        var_24 = 0
004360a2        game->completion_row_start = game->runtime_row_count - game->level_definition.last_segment.row_count
004360ad        if (game->runtime_row_count s>= 0xc1c)
004360c0        report_errorf("Track (%s) too long, Maximum Length %i", &game->level_definition.level_display_name, 0xc1c)
00435fbc        if (level_mode_2 == 3)
00435fc8        game->first_block_row_count = game->level_definition.first_segment.row_count
00435fd9        int32_t i_6 = 0x10
00435fde        game->runtime_row_count = game->level_definition.last_segment.row_count + game->level_definition.first_segment.row_count
00435ff2        int32_t esi_1
00435ff2        int32_t i_1
00435fea        esi_1 = game->runtime_row_count + game->level_definition.segment_slots[0].row_count
00435fec        i_1 = i_6
00435fec        i_6 -= 1
00435fed        game->runtime_row_count = esi_1
00435ff2        do while (i_1 != 1)
00435ffa        var_24 = 0
00436000        game->completion_row_start = esi_1 - game->level_definition.last_segment.row_count
0043600d        game->completion_row_start = esi_1 - game->level_definition.last_segment.row_count
004360ce        game->track_mirror_enabled = 0
004360d2        game->track_mirror_repeat_count = 0
004360d5        int32_t var_20 = 0
004360d9        char var_42 = 0
004360de        int32_t var_2c = 0
004360e2        game->player.follow_state._pad_3c[0] = 0
004360e9        struct FringeObject** var_28 = &game->runtime_cells[0][0].fringe_front
004360ed        float* edi = &game->runtime_rows[0].projection_payload.y
004360f3        int32_t var_30 = 0xc80
00436192        struct SubgameRuntime* segment_count
00436192        bool cond:3_1
004360fd        int32_t i_7 = 8
00436102        (edi - 0x5ccb5c)->runtime_rows[0].flags = 0
00436108        (edi - 0x5ccb5c)->runtime_rows[0].installed_heading_delta = 0f
0043610b        (edi - 0x5ccb5c)->runtime_rows[0].attachment_template_index = 0
0043610e        (edi - 0x5ccb5c)->runtime_rows[0].ring_speed = 0f
00436111        (edi - 0x5ccb5c)->runtime_rows[0].primary_attachment_cell = nullptr
00436114        (edi - 0x5ccb5c)->runtime_rows[0].projection_payload.z = 0f
00436117        (edi - 0x5ccb5c)->runtime_rows[0].projection_payload.y = 0f
00436119        (edi - 0x5ccb5c)->runtime_rows[0].projection_payload.x = 0
0043611c        (edi - 0x5ccb5c)->runtime_rows[0].parcel_set_id = 0
0043611f        (edi - 0x5ccb5c)->runtime_rows[0].source_segment = nullptr
00436122        (edi - 0x5ccb5c)->runtime_rows[0].row_event_id = 0
00436129        uint32_t* esi_5 = &var_28[-1]
0043615f        int32_t i_2
0043612c        uint32_t lane_and_flags = (esi_5 - 0x3bfb08)->runtime_cells[0][0].lane_and_flags
0043612e        lane_and_flags:1.b &= 0x5f
00436131        (esi_5 - 0x3bfb08)->runtime_cells[0][0].lane_and_flags = lane_and_flags
00436133        (esi_5 - 0x3bfb08)->:0x3bfb05.b = 0
00436137        (esi_5 - 0x3bfb08)->:0x3bfb08.w = 0
00436146        (esi_5 - 0x3bfb08)->runtime_cells[0][0].lane_and_flags &= 0xffffafa7
00436148        (esi_5 - 0x3bfb08)->:0x3bfb08.w = 0
0043614d        uint32_t list_flags = (esi_5 - 0x3bfb08)->runtime_cells[0][0].bod.list_flags
00436150        list_flags.b &= 0x7f
00436153        (esi_5 - 0x3bfb08)->runtime_cells[0][0].bod.list_flags = list_flags
00436156        set_color_white(&esi_5[-6])
0043615b        esi_5 = &esi_5[0x15]
0043615e        i_2 = i_7
0043615e        i_7 -= 1
0043615f        do while (i_2 != 1)
00436161        struct FringeObject** eax_20 = var_28
00436165        segment_count = 8
0043617d        struct SubgameRuntime* i_3
0043616a        struct FringeObject** esi_6 = eax_20
0043616e        eax_20 = &eax_20[0x15]
00436171        i_3 = segment_count
00436171        segment_count -= 1
00436172        (esi_6 - 0x3bfb0c)->runtime_cells[0][0].fringe_front = nullptr
00436174        (esi_6 - 0x3bfb0c)->runtime_cells[0][0].fringe_right = nullptr
00436177        (esi_6 - 0x3bfb0c)->runtime_cells[0][0].fringe_left = nullptr
0043617a        (esi_6 - 0x3bfb0c)->runtime_cells[0][0].fringe_back = nullptr
0043617d        do while (i_3 != 1)
0043617f        var_28 = eax_20
00436187        edi = &edi[0x3d]
0043618d        cond:3_1 = var_30 != 1
0043618e        var_30 -= 1
00436192        do while (cond:3_1)
0043619f        if (game->level_definition.random_enabled == 1)
004361a1        segment_count = game->level_definition.segment_count
004361a7        int32_t i_4 = 0
004361ab        if (segment_count s> 0)
004361ad        segment_count = &game->level_definition.segment_slots[0].visited
004361b3        segment_count->unknown_000000[0] = 0
004361bc        i_4 += 1
004361bd        segment_count = &segment_count->__offset(0x4220).d
004361c5        do while (i_4 s< game->level_definition.segment_count)
004361ca        int32_t j_1 = 0
004361d4        if (game->runtime_row_count s<= 0)
004361d4        return
004361da        int32_t i_5 = 0
004361de        struct SubgameRuntime* runtime = game
004361e4        struct SubSegment* var_3c_1
004361e4        struct SubSegment* esi_7
004361e4        if (i_5 == 0)
004361e6        esi_7 = &runtime->level_definition.first_segment
004361ec        var_42 = 1
004361f1        var_3c_1 = esi_7
004361f5        esi_7->row_base = i_5
00436209        if (i_5 != runtime->completion_row_start || runtime->level_definition.random_enabled != 0)
00436221        runtime->base_subgame_rate = 1f
00436230        if (runtime->level_definition.random_enabled != 1)
004362a4        int32_t eax_29 = var_24
004362a9        var_24 += 1
004362ba        esi_7 = &runtime->level_definition.segment_slots[eax_29]
004362c1        var_3c_1 = esi_7
00436236        long double x87_r7_9
00436236        if (runtime->level_mode != 1)
00436254        x87_r7_9 = float.t(runtime->level_definition.segment_count)
0043625a        char* var_58_6 = "Segtra"
00436241        char* var_58_5 = "Segdif"
0043624c        x87_r7_9 = (fconvert.t(runtime->challenge_difficulty_scalar) * fconvert.t(0.899999976f) + fconvert.t(0.100000001f)) * float.t(runtime->level_definition.segment_count)
0043625f        struct SubgameRuntime* segment_count_1 = segment_count
0043626b        int32_t eax_27
0043626b        int16_t x87control_2
0043626b        eax_27, x87control_2 = ftol(x87control_1, random_float_below(fconvert.s(x87_r7_9)))
0043627b        int32_t eax_28
0043627b        eax_28, x87control_1 = ftol(x87control_2, float.t(eax_27) * fconvert.t(runtime->base_subgame_rate))
0043628f        esi_7 = &runtime->level_definition.segment_slots[eax_28]
00436296        var_3c_1 = esi_7
0043629a        esi_7->visited = 1
0043620b        esi_7 = &runtime->level_definition.last_segment
00436211        var_42 = 1
00436216        var_3c_1 = esi_7
0043621a        esi_7->row_base = i_5
004362c7        segment_count = switch_track_mirror(runtime)
004362cc        int32_t row_count = esi_7->row_count
004362cf        esi_7->row_base = i_5
004362d3        if (row_count s< 0)
004362da        segment_count = report_errorf("Negative Segment Length")
004362e5        struct SubgameRuntime* segment_count_2 = nullptr
004362ef        if (i_5 s< runtime->runtime_row_count)
00437168        int32_t j
004362f9        segment_count = segment_count_2
00436300        if (segment_count s>= *(var_3c_1 + 4))
00436300        break
00436306        int32_t level_mode_3 = runtime->level_mode
0043630c        if (level_mode_3 != 2)
0043630e        j = runtime->completion_row_start
00436313        struct SubSegment* edx_17
00436313        if (level_mode_3 == 2 || i_5 s< j)
0043634b        edx_17 = var_3c_1
00436326        if (level_mode_3 != 0 && level_mode_3 != 4 && level_mode_3 != 1 && level_mode_3 != 7)
0043632b        edx_17 = &runtime->level_definition_scratch.segment_slots[1]
00436331        if (level_mode_3 == 0 || level_mode_3 == 4 || level_mode_3 == 1 || level_mode_3 == 7 || level_mode_3 == 3)
00436333        edx_17 = &runtime->level_definition.last_segment
0043633b        var_3c_1 = edx_17
0043633f        if (i_5 == j)
00436341        segment_count_2 = nullptr
00436352        if (level_mode_3 != 2)
00436354        j = edx_17->row_count
0043635b        int32_t completion_row_start = runtime->completion_row_start
00436366        if (j - segment_count_2 + i_5 s<= completion_row_start)
004363c5        edx_17 = var_3c_1
00436368        edx_17 = var_3c_1
004363a0        if (edx_17 != &runtime->level_definition_scratch.segment_slots[1] && edx_17 != &runtime->level_definition_scratch.segment_slots[3] && edx_17 != &runtime->level_definition_scratch.segment_slots[4] && (level_mode_3 == 0 || level_mode_3 == 4 || level_mode_3 == 1 || level_mode_3 == 7 || level_mode_3 == 3) && edx_17 != &runtime->level_definition.last_segment)
004363b7        j = j - completion_row_start - segment_count_2 + i_5
004363bb        int32_t ecx_26 = runtime->runtime_row_count + j
004363bd        runtime->completion_row_start = completion_row_start + j
004363c0        runtime->runtime_row_count = ecx_26
004363ce        if (runtime->track_mirror_enabled != 0)
004363d6        int32_t ecx_27 = i_5 * 0x3d
004363ea        *(&runtime->runtime_rows + (ecx_27 << 2)) |= 0x20
004363f7        void* ecx_31 = segment_count_2 * 7
00436403        void* esi_9 = edx_17 + (ecx_31 << 3)
00436406        if (((*(&edx_17->rows + (ecx_31 << 3))).w:1.b & 1) != 0)
0043640e        int32_t ecx_32 = i_5 * 0x3d
00436418        int32_t ecx_33 = *(&runtime->runtime_rows + (ecx_32 << 2))
0043641f        ecx_33:1.b |= 1
00436422        *(&runtime->runtime_rows + (ecx_32 << 2)) = ecx_33
0043642d        if (((*(esi_9 + 0x814)).w:1.b & 0x80) != 0)
00436435        int32_t ecx_34 = i_5 * 0x3d
0043643f        int32_t ecx_35 = *(&runtime->runtime_rows + (ecx_34 << 2))
00436446        ecx_35:1.b |= 0x80
00436449        *(&runtime->runtime_rows + (ecx_34 << 2)) = ecx_35
00436458        void* ebx_5 = &runtime->unknown_000000[i_5 * 0xf4]
0043645c        *(ebx_5 + 0x5ccbb4) = edx_17
00436462        *(ebx_5 + 0x5ccbb8) = var_2c
0043646f        if ((*(esi_9 + 0x814) & 2) != 0)
00436475        int32_t eax_48 = *(ebx_5 + 0x5ccac8)
0043647b        eax_48.b |= 2
0043647d        *(ebx_5 + 0x5ccac8) = eax_48
004364a5        set_bod_object(ebx_5 + 0x5ccacc, *(g_game_base + *(esi_9 + 0x828) * 0xbc + 0x48e2c))
004364b0        set_matrix_identity(ebx_5 + 0x5ccb04)
004364c5        int32_t eax_51
004364c5        eax_51.b = *(esi_9 + 0x82c)
004364c5        eax_51:1.b = *(esi_9 + 0x82d)
004364c5        eax_51:2.b = *(esi_9 + 0x82e)
004364c5        eax_51:3.b = *(esi_9 + 0x82f)
004364c7        *(ebx_5 + 0x5ccb34) = eax_51
004364cc        *(ebx_5 + 0x5ccb38) = *(esi_9 + 0x830)
004364cf        int32_t ecx_43
004364cf        ecx_43.b = *(esi_9 + 0x834)
004364cf        ecx_43:1.b = *(esi_9 + 0x835)
004364d2        *(ebx_5 + 0x5ccb3c) = ecx_43
004364db        *(ebx_5 + 0x5ccb3c) = fconvert.s(float.t(j_1) + fconvert.t(*(ebx_5 + 0x5ccb3c)))
004364e8        if ((*(esi_9 + 0x814) & 8) == 0)
0043651c        *(ebx_5 + 0x5ccb54) = 0
00436522        *(ebx_5 + 0x5ccb50) = 0
00436528        *(ebx_5 + 0x5ccb4c) = 0
004364ea        int32_t eax_53 = *(ebx_5 + 0x5ccac8)
004364f6        eax_53.b |= 8
004364f8        *(ebx_5 + 0x5ccac8) = eax_53
00436506        *(ebx_5 + 0x5ccb4c) = *(esi_9 + 0x838)
0043650f        *(ebx_5 + 0x5ccb50) = *(esi_9 + 0x83c)
00436515        *(ebx_5 + 0x5ccb54) = *(esi_9 + 0x840)
0043652e        edx_17 = var_3c_1
00436539        if ((*(esi_9 + 0x814) & 1) != 0)
00436546        *(ebx_5 + 0x5ccac8) |= 0x4001
0043656b        *(ebx_5 + 0x5ccb64) = *(edx_17 + &segment_count_2->__offset(0x25).d * 0x38)
00436571        int32_t edx_26 = *(esi_9 + 0x81c)
00436573        *(ebx_5 + 0x5ccb58) = edx_26.b
00436573        *(ebx_5 + 0x5ccb59) = edx_26:1.b
00436573        *(ebx_5 + 0x5ccb5a) = edx_26:2.b
00436573        *(ebx_5 + 0x5ccb5b) = edx_26:3.b
00436578        *(ebx_5 + 0x5ccb5c) = *(esi_9 + 0x820)
0043657b        int16_t eax_60 = (*(esi_9 + 0x824)).w
0043657e        *(ebx_5 + 0x5ccb60) = eax_60.b
0043657e        *(ebx_5 + 0x5ccb61) = eax_60:1.b
00436588        if ((*(esi_9 + 0x814) & 8) != 0)
0043658a        int32_t eax_61 = *(ebx_5 + 0x5ccac8)
00436590        eax_61.b |= 8
00436592        *(ebx_5 + 0x5ccac8) = eax_61
0043659e        *(ebx_5 + 0x5ccb68) = *(esi_9 + 0x844)
004365ab        if ((*(esi_9 + 0x814) & 4) != 0)
004365ad        int32_t eax_62 = *(ebx_5 + 0x5ccac8)
004365b3        eax_62.b |= 4
004365b5        *(ebx_5 + 0x5ccac8) = eax_62
004365c8        if ((0x200 & *(esi_9 + 0x814)) != 0)
004365ca        *(ebx_5 + 0x5ccac8) |= 0x200
004365dd        if ((0x400 & *(esi_9 + 0x814)) != 0)
004365df        *(ebx_5 + 0x5ccac8) |= 0x400
004365f2        if ((0x2000 & *(esi_9 + 0x814)) != 0)
004365f4        *(ebx_5 + 0x5ccac8) |= 0x2000
00436607        if ((0x800 & *(esi_9 + 0x814)) != 0)
00436609        *(ebx_5 + 0x5ccac8) |= 0x800
0043661c        if ((0x1000 & *(esi_9 + 0x814)) != 0)
0043661e        *(ebx_5 + 0x5ccac8) |= 0x1000
00436631        char var_41_1 = 0
00436636        int32_t var_30_1 = 0
00436648        *(runtime + ((i_5 + (i_5 * 3 + 0x12414) * 0x14 + 0x615c) << 2)) = *(esi_9 + 0x848)
00437143        bool cond:12_1
00436655        int32_t edx_29
00436655        int32_t ebp_1
00436655        if (game->track_mirror_enabled == 0)
00436664        edx_29 = var_30_1
00436668        ebp_1 = edx_29
00436657        edx_29 = var_30_1
00436660        ebp_1 = 7 - edx_29
00436682        void* esi_11 = &game->unknown_000000[(edx_29 + (j_1 << 3)) * 0x54]
00436685        int32_t eax_69 = *(esi_11 + 0x3bfb08)
0043668b        eax_69.b &= 0xe0
0043668f        *(esi_11 + 0x3bfb08) = eax_69 ^ (edx_29 & 7)
0043669f        *(esi_11 + 0x3bfb0c) = 0
004366a1        *(esi_11 + 0x3bfb10) = 0
004366a4        *(esi_11 + 0x3bfb14) = 0
004366a7        *(esi_11 + 0x3bfb18) = 0
004366b1        if (j_1 s>= game->first_block_row_count)
004366b6        random_length_1.b = 0
004366bd        if (j_1 s< game->first_block_row_count || j_1 s>= game->completion_row_start)
004366bf        random_length_1.b = 1
004366ce        set_bod_object(esi_11 + 0x3bfac8, 0)
004366e4        struct SubSegment* edx_32 = var_3c_1
004366ee        char* ebp_4 = &edx_32->glyph_rows + &segment_count_2->unknown_000000[ebp_1 << 8]
004366f2        edx_32.b = *ebp_4
004366f6        char eax_74 = normalize_segment_glyph_for_track_flags(game, edx_32.b, j_1, random_length_1.b)
00436704        if (sx.d(eax_74) - 0x20 u> 0x5d)
00436eb5        label_436eb5:
00436eb5        struct SubSegment* edx_58 = var_3c_1
00436ebd        edx_58->source_name
00436ec0        edx_58.b = *ebp_4
0043670a        int32_t edx_33 = 0
0043670c        edx_33.b = *(sx.d(eax_74) + &jump_table_437194[0x14])
00436712        switch (edx_33)
00436719        case 0
00436719        *(esi_11 + 0x3bfb04) = 0
00436720        int32_t eax_75 = *(esi_11 + 0x3bfacc)
00436726        eax_75.b &= 0xdf
00436728        *(esi_11 + 0x3bfacc) = eax_75
0043674d        case 1
0043674d        *(esi_11 + 0x3bfb04) = 0x20
00436754        int32_t eax_77 = *(esi_11 + 0x3bfacc)
0043675a        eax_77.b &= 0xdf
0043675c        *(esi_11 + 0x3bfacc) = eax_77
004367e5        case 2
004367e5        char* game_base_1 = g_game_base
004367eb        int32_t edx_35
004367eb        edx_35.b = game_base_1[0x44b34]
004367eb        edx_35:1.b = game_base_1[0x44b35]
004367eb        edx_35:2.b = game_base_1[0x44b36]
004367eb        edx_35:3.b = game_base_1[0x44b37]
004367f4        set_bod_object(esi_11 + 0x3bfac8, edx_35)
004367f9        *(esi_11 + 0x3bfb04) = 0x17
00436800        int32_t eax_83 = *(esi_11 + 0x3bfacc)
00436806        eax_83.b |= 0x20
00436808        *(esi_11 + 0x3bfacc) = eax_83
004368f7        case 3
004368f7        char* game_base_3 = g_game_base
004368fd        int32_t edx_39
004368fd        edx_39.b = game_base_3[0x447b4]
004368fd        edx_39:1.b = game_base_3[0x447b5]
004368fd        edx_39:2.b = game_base_3[0x447b6]
004368fd        edx_39:3.b = game_base_3[0x447b7]
00436906        set_bod_object(esi_11 + 0x3bfac8, edx_39)
0043690b        *(esi_11 + 0x3bfb04) = 0x22
00436912        int32_t eax_93 = *(esi_11 + 0x3bfacc)
00436918        eax_93.b |= 0x20
0043691a        *(esi_11 + 0x3bfacc) = eax_93
00436a13        case 4
00436a13        int32_t ecx_84 = var_20 + 1
00436a14        int32_t ebp_6 = *(esi_11 + 0x3bfacc) & 0xffffffdf
00436a1a        var_20 = ecx_84
00436a1e        *(esi_11 + 0x3bfacc) = ebp_6
00436a24        int32_t eax_103 = ebp_6
00436a26        if (ecx_84 == 0xf)
00436a28        var_20 = 0
00436a30        *(esi_11 + 0x3bfb04) = 0x16
00436a3f        if (ecx_84 != 8)
00436aab        eax_103.b &= 0xdf
00436aad        *(esi_11 + 0x3bfacc) = eax_103
00436ab3        *(esi_11 + 0x3bfb04) = 0x16
00436a41        char* game_base_5 = g_game_base
00436a47        int32_t edx_43
00436a47        edx_43.b = game_base_5[0x444dc]
00436a47        edx_43:1.b = game_base_5[0x444dd]
00436a47        edx_43:2.b = game_base_5[0x444de]
00436a47        edx_43:3.b = game_base_5[0x444df]
00436a50        set_bod_object(esi_11 + 0x3bfac8, edx_43)
00436a72        *(esi_11 + 0x3bfacc) |= 0x20
00436a9a        store_color4f(&game->unknown_000000[(var_30_1 + (j_1 << 3) + 0xb6cc) * 0x54], 1f, 1f, 1f, 0.999000013f)
00436a9f        *(esi_11 + 0x3bfb04) = 0x16
00436961        case 5
00436961        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x44b34))
00436966        *(esi_11 + 0x3bfb04) = 0x18
0043696d        int32_t eax_97 = *(esi_11 + 0x3bfacc)
00436973        eax_97.b |= 0x20
00436975        *(esi_11 + 0x3bfacc) = eax_97
00436933        case 6
00436933        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x44124))
00436938        *(esi_11 + 0x3bfb04) = 0x1c
0043693f        int32_t eax_95 = *(esi_11 + 0x3bfacc)
00436945        eax_95.b |= 0x20
00436947        *(esi_11 + 0x3bfacc) = eax_95
004369bc        case 7
004369bc        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x447b4))
004369c1        *(esi_11 + 0x3bfb04) = 0x15
004369c8        int32_t eax_100 = *(esi_11 + 0x3bfacc)
004369ce        eax_100.b |= 0x20
004369d0        *(esi_11 + 0x3bfacc) = eax_100
004368aa        case 8
004368aa        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x447b4))
004368af        *(esi_11 + 0x3bfb04) = 1
004368b6        int32_t eax_90 = *(esi_11 + 0x3bfacc)
004368bc        eax_90.b |= 0x20
004368be        *(esi_11 + 0x3bfacc) = eax_90
00436e02        case 9
00436e02        if (game->level_mode == 1)
00436e08        int32_t ecx_112 = *(ebx_5 + 0x5ccac8)
00436e0e        ecx_112:1.b &= 0xbf
00436e1a        *(ebx_5 + 0x5ccac8) = ecx_112 | 1
00436e20        *(ebx_5 + 0x5ccb64) = 0
00436e30        *(ebx_5 + 0x5ccb58) = fconvert.s(float.t(var_30_1) - fconvert.t(4f) + fconvert.t(0.5f))
00436e40        *(ebx_5 + 0x5ccb5c) = *(esi_11 + 0x3bfadc)
00436e4c        *(ebx_5 + 0x5ccb60) = fconvert.s(float.t(j_1) + fconvert.t(0.5f))
00436e57        if (game->track_mirror_enabled != 0)
00436e65        *(ebx_5 + 0x5ccb58) = fconvert.s(fconvert.t(*(ebx_5 + 0x5ccb58)) * fconvert.t(-1f))
00436e02        goto label_436e6b
00436e6b        case 0xa
00436e6b        label_436e6b:
00436e72        if ((*(ebx_5 + 0x5ccac8) & 0xc0) != 0)
00436e9e        int32_t eax_139 = *(esi_11 + 0x3bfacc)
00436ea4        eax_139.b &= 0xdf
00436ea6        *(esi_11 + 0x3bfacc) = eax_139
00436eac        *(esi_11 + 0x3bfb04) = 0
00436e82        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x44b34))
00436e87        *(esi_11 + 0x3bfb04) = 0xf
00436e8e        int32_t eax_138 = *(esi_11 + 0x3bfacc)
00436e94        eax_138.b |= 0x20
00436e96        *(esi_11 + 0x3bfacc) = eax_138
00436c67        case 0xb
00436c67        char* game_base_8 = g_game_base
00436c6d        int32_t edx_51
00436c6d        edx_51.b = game_base_8[0x44d2c]
00436c6d        edx_51:1.b = game_base_8[0x44d2d]
00436c6d        edx_51:2.b = game_base_8[0x44d2e]
00436c6d        edx_51:3.b = game_base_8[0x44d2f]
00436c76        set_bod_object(esi_11 + 0x3bfac8, edx_51)
00436c7d        *(esi_11 + 0x3bfae4) = 0
00436c83        *(esi_11 + 0x3bfae8) = 0
00436c89        *(esi_11 + 0x3bfb04) = 6
00436c90        int32_t eax_121 = *(esi_11 + 0x3bfacc)
00436c96        eax_121.b |= 0x20
00436c98        *(esi_11 + 0x3bfacc) = eax_121
004369ea        case 0xc
004369ea        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x445f4))
004369ef        *(esi_11 + 0x3bfb04) = 0xe
004369f6        int32_t eax_102 = *(esi_11 + 0x3bfacc)
004369fc        eax_102.b |= 0x20
004369fe        *(esi_11 + 0x3bfacc) = eax_102
00436ad0        case 0xd
00436ad0        if (j_1 s<= 0 || *(esi_11 + 0x3bf864) != 3)
00436b21        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x44d2c))
00436b26        *(esi_11 + 0x3bfae4) = 0
00436b2c        *(esi_11 + 0x3bfae8) = 0
00436b32        *(esi_11 + 0x3bfb04) = 3
00436b39        int32_t eax_111 = *(esi_11 + 0x3bfacc)
00436b3f        eax_111.b |= 0x20
00436b41        *(esi_11 + 0x3bfacc) = eax_111
00436ad2        char* game_base_6 = g_game_base
00436ad8        int32_t edx_47
00436ad8        edx_47.b = game_base_6[0x44d2c]
00436ad8        edx_47:1.b = game_base_6[0x44d2d]
00436ad8        edx_47:2.b = game_base_6[0x44d2e]
00436ad8        edx_47:3.b = game_base_6[0x44d2f]
00436ae1        set_bod_object(esi_11 + 0x3bfac8, edx_47)
00436ae6        *(esi_11 + 0x3bfae4) = 0
00436aec        *(esi_11 + 0x3bfae8) = 0
00436af2        *(esi_11 + 0x3bfb04) = 9
00436af9        int32_t eax_109 = *(esi_11 + 0x3bfacc)
00436aff        eax_109.b |= 0x20
00436b01        *(esi_11 + 0x3bfacc) = eax_109
00436b07        *(esi_11 + 0x3bf864) = 0xc
0043676b        case 0xe
0043676b        *(esi_11 + 0x3bfb04) = 0
00436772        int32_t eax_78 = *(esi_11 + 0x3bfacc)
00436778        eax_78.b &= 0xdf
0043677a        *(esi_11 + 0x3bfacc) = eax_78
00436780        switch_track_mirror(game)
0043686e        case 0xf
0043686e        char* game_base_2 = g_game_base
00436874        int32_t edx_37
00436874        edx_37.b = game_base_2[0x44b34]
00436874        edx_37:1.b = game_base_2[0x44b35]
00436874        edx_37:2.b = game_base_2[0x44b36]
00436874        edx_37:3.b = game_base_2[0x44b37]
0043687d        set_bod_object(esi_11 + 0x3bfac8, edx_37)
00436882        *(esi_11 + 0x3bfb04) = 0x13
00436889        int32_t eax_88 = *(esi_11 + 0x3bfacc)
0043688f        eax_88.b |= 0x20
00436891        *(esi_11 + 0x3bfacc) = eax_88
00436798        case 0x10
00436798        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x44b34))
0043679d        *(esi_11 + 0x3bfb04) = 0x11
004367a4        int32_t eax_80 = *(esi_11 + 0x3bfacc)
004367aa        eax_80.b |= 0x20
004367ac        *(esi_11 + 0x3bfacc) = eax_80
00436980        case 0x11
00436980        char* game_base_4 = g_game_base
00436986        int32_t edx_41
00436986        edx_41.b = game_base_4[0x44b34]
00436986        edx_41:1.b = game_base_4[0x44b35]
00436986        edx_41:2.b = game_base_4[0x44b36]
00436986        edx_41:3.b = game_base_4[0x44b37]
0043698f        set_bod_object(esi_11 + 0x3bfac8, edx_41)
00436994        *(esi_11 + 0x3bfb04) = 0x19
0043699b        int32_t eax_98 = *(esi_11 + 0x3bfacc)
004369a1        eax_98.b |= 0x20
004369a3        *(esi_11 + 0x3bfacc) = eax_98
0043684f        case 0x12
0043684f        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x44b34))
00436854        *(esi_11 + 0x3bfb04) = 0x12
0043685b        int32_t eax_87 = *(esi_11 + 0x3bfacc)
00436861        eax_87.b |= 0x20
00436863        *(esi_11 + 0x3bfacc) = eax_87
00436ce0        case 0x13
00436ce0        if (eax_74 == 0x50)
00436ce2        *(esi_11 + 0x3bfb04) = 0x1e
00436ced        if (eax_74 == 0x70)
00436cef        *(esi_11 + 0x3bfb04) = 0x1d
00436cfa        int32_t ecx_100 = *(ebx_5 + 0x5ccb68)
00436d05        int32_t eax_125 = ecx_100 << 3
00436d0c        void* ecx_101
00436d0c        if (game->track_mirror_enabled == 0)
00436d27        ecx_101 = &game->path_pairs + (eax_125 - ecx_100) * 0x30
00436d16        ecx_101 = &game->path_pairs[0].secondary + (eax_125 - ecx_100) * 0x30
00436d32        *(esi_11 + 0x3bfb00) = ecx_101
00436d43        *(esi_11 + 0x3bfacc) &= 0xffffffdf
00436d49        if (var_41_1 == 0)
00436d57        var_41_1 = 1
00436d60        set_bod_object(esi_11 + 0x3bfac8, *(*(esi_11 + 0x3bfb00) + 0x24))
00436d72        *(esi_11 + 0x3bfacc) |= 0x20
00436d8b        set_bod_object(ebx_5 + 0x5ccb78, *(*(esi_11 + 0x3bfb00) + 0x84))
00436d9c        *(ebx_5 + 0x5ccb7c) |= 0x20
00436da8        *(ebx_5 + 0x5ccb74) = var_3c_1->angle_radians.bits
00436db4        int32_t k = 0
00436dbb        if (*(*(esi_11 + 0x3bfb00) + 0x48) s> 0)
00436dc1        char* ecx_111 = ebx_5 + 0x5ccac8
00436dc7        int32_t eax_134
00436dc7        eax_134.b = *ecx_111
00436dc7        eax_134:1.b = ecx_111[1]
00436dc7        eax_134:2.b = ecx_111[2]
00436dc7        eax_134:3.b = ecx_111[3]
00436dcb        if ((eax_134.b & 0x40) == 0)
00436dd9        eax_134.b |= 0x40
00436ddb        *ecx_111 = eax_134.b
00436ddb        ecx_111[1] = eax_134:1.b
00436ddb        ecx_111[2] = eax_134:2.b
00436ddb        ecx_111[3] = eax_134:3.b
00436ddd        *(ecx_111 + 0xa4) = esi_11 + 0x3bfac8
00436dcd        eax_134.b |= 0x80
00436dcf        *ecx_111 = eax_134.b
00436dcf        ecx_111[1] = eax_134:1.b
00436dcf        ecx_111[2] = eax_134:2.b
00436dcf        ecx_111[3] = eax_134:3.b
00436dd1        *(ecx_111 + 0xa8) = esi_11 + 0x3bfac8
00436de9        k += 1
00436dea        ecx_111 = &ecx_111[0xf4]
00436df3        do while (k s< *(*(esi_11 + 0x3bfb00) + 0x48))
00436733        case 0x14
00436733        *(esi_11 + 0x3bfb04) = 0x23
0043673a        int32_t eax_76 = *(esi_11 + 0x3bfacc)
00436740        eax_76.b &= 0xdf
00436742        *(esi_11 + 0x3bfacc) = eax_76
00436cb1        case 0x15
00436cb1        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x44cf4))
00436cb8        *(esi_11 + 0x3bfae4) = 0
00436cbe        *(esi_11 + 0x3bfae8) = 0
00436cc4        *(esi_11 + 0x3bfb04) = 5
00436ccb        int32_t eax_123 = *(esi_11 + 0x3bfacc)
00436cd1        eax_123.b |= 0x20
00436cd3        *(esi_11 + 0x3bfacc) = eax_123
004367c6        case 0x16
004367c6        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x44b34))
004367cb        *(esi_11 + 0x3bfb04) = 0xf
004367d2        int32_t eax_82 = *(esi_11 + 0x3bfacc)
004367d8        eax_82.b |= 0x20
004367da        *(esi_11 + 0x3bfacc) = eax_82
00436821        case 0x17
00436821        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x44b34))
00436826        *(esi_11 + 0x3bfb04) = 0x10
0043682d        int32_t eax_85 = *(esi_11 + 0x3bfacc)
00436833        eax_85.b |= 0x20
00436835        *(esi_11 + 0x3bfacc) = eax_85
004368d8        case 0x18
004368d8        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x447b4))
004368dd        *(esi_11 + 0x3bfb04) = 0x21
004368e4        int32_t eax_92 = *(esi_11 + 0x3bfacc)
004368ea        eax_92.b |= 0x20
004368ec        *(esi_11 + 0x3bfacc) = eax_92
00436beb        case 0x19
00436beb        if (j_1 s<= 0 || *(esi_11 + 0x3bf864) != 3)
00436c3c        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x44cf4))
00436c41        *(esi_11 + 0x3bfae4) = 0
00436c47        *(esi_11 + 0x3bfae8) = 0
00436c4d        *(esi_11 + 0x3bfb04) = 2
00436c54        int32_t eax_120 = *(esi_11 + 0x3bfacc)
00436c5a        eax_120.b |= 0x20
00436c5c        *(esi_11 + 0x3bfacc) = eax_120
00436bfb        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x44cf4))
00436c00        *(esi_11 + 0x3bfae4) = 0
00436c06        *(esi_11 + 0x3bfae8) = 0
00436c0c        *(esi_11 + 0x3bfb04) = 8
00436c13        int32_t eax_118 = *(esi_11 + 0x3bfacc)
00436c19        eax_118.b |= 0x20
00436c1b        *(esi_11 + 0x3bfacc) = eax_118
00436c21        *(esi_11 + 0x3bf864) = 0xb
00436b5d        case 0x1a
00436b5d        if (j_1 s<= 0 || *(esi_11 + 0x3bf864) != 3)
00436ba0        char* game_base_7 = g_game_base
00436ba6        int32_t edx_49
00436ba6        edx_49.b = game_base_7[0x44d64]
00436ba6        edx_49:1.b = game_base_7[0x44d65]
00436ba6        edx_49:2.b = game_base_7[0x44d66]
00436ba6        edx_49:3.b = game_base_7[0x44d67]
00436baf        set_bod_object(esi_11 + 0x3bfac8, edx_49)
00436bb4        *(esi_11 + 0x3bfae4) = 0
00436bba        *(esi_11 + 0x3bfae8) = 0
00436bc0        *(esi_11 + 0x3bfb04) = 4
00436bc7        int32_t eax_115 = *(esi_11 + 0x3bfacc)
00436bcd        eax_115.b |= 0x20
00436bcf        *(esi_11 + 0x3bfacc) = eax_115
00436b6e        set_bod_object(esi_11 + 0x3bfac8, *(g_game_base + 0x44d64))
00436b73        *(esi_11 + 0x3bfae4) = 0
00436b79        *(esi_11 + 0x3bfae8) = 0
00436b7f        *(esi_11 + 0x3bfb04) = 0xa
00436b86        int32_t eax_114 = *(esi_11 + 0x3bfacc)
00436b8c        eax_114.b |= 0x20
00436b8e        *(esi_11 + 0x3bfacc) = eax_114
00436b94        *(esi_11 + 0x3bf864) = 0xd
00436712        case 0x1b
00436712        goto label_436eb5
00436eea        *(esi_11 + 0x3bfae0) = 0
00436eed        *(esi_11 + 0x3bfadc) = 0
00436ef0        *(esi_11 + 0x3bfad8) = 0
00436ef2        *(ebx_5 + 0x5ccb90) = 0
00436ef8        *(ebx_5 + 0x5ccb8c) = 0
00436efe        *(ebx_5 + 0x5ccb88) = 0
00436f04        char eax_144 = *(esi_11 + 0x3bfb04)
00436f10        float var_28_2
00436f10        if (eax_144 == 0x1d || eax_144 == 0x1e)
00436f67        *(esi_11 + 0x3bfad8) = 0
00436f69        long double x87_r7_28 = float.t(j_1) + fconvert.t(0.5f)
00436f6f        var_28_2 = fconvert.s(x87_r7_28)
00436f73        long double x87_r7_29 = x87_r7_28 - fconvert.t(0.5f)
00436f79        *(esi_11 + 0x3bfae0) = fconvert.s(x87_r7_29)
00436f86        if ((data_4df934 & 0x20) == 0)
00436ff3        int32_t eax_148 = *(ebx_5 + 0x5ccb7c)
00436ff9        eax_148.b &= 0xdf
00436ffd        *(ebx_5 + 0x5ccb7c) = eax_148
00436f88        *(ebx_5 + 0x5ccb88) = 0
00436f92        *(ebx_5 + 0x5ccb90) = fconvert.s(x87_r7_29)
00436fa4        struct tColour out
00436fa4        struct tColour* eax_146 = get_track_skirt_color(&g_game_base[0x74618], &out)
00436fb4        float r = eax_146->r
00436fb6        *(ebx_5 + 0x5ccba0) = r.b
00436fb6        *(ebx_5 + 0x5ccba1) = r:1.b
00436fb6        *(ebx_5 + 0x5ccba2) = r:2.b
00436fb6        *(ebx_5 + 0x5ccba3) = r:3.b
00436fbb        *(ebx_5 + 0x5ccba4) = eax_146->g
00436fbe        int16_t b_1 = (eax_146->b).w
00436fc1        *(ebx_5 + 0x5ccba8) = b_1.b
00436fc1        *(ebx_5 + 0x5ccba9) = b_1:1.b
00436fc7        *(ebx_5 + 0x5ccbac) = eax_146->a
00436fd3        float g = eax_146->g
00436fdc        float b = eax_146->b
00436fdf        float a = eax_146->a
00436fe9        x87control_1 = set_object_color(*(ebx_5 + 0x5ccb9c), eax_146->r)
00436f22        *(esi_11 + 0x3bfad8) = fconvert.s(float.t(var_30_1) - fconvert.t(4f) + fconvert.t(0.5f))
00436f24        *(esi_11 + 0x3bfadc) = 0
00436f2a        eax_144 = *(esi_11 + 0x3bfb04)
00436f3a        if (eax_144 == 8 || eax_144 == 9 || eax_144 == 0xa)
00436f3c        *(esi_11 + 0x3bfadc) = 0x3f000000
00436f50        var_28_2 = fconvert.s(float.t(j_1) + fconvert.t(0.5f))
00436f58        *(esi_11 + 0x3bfae0) = var_28_2
00437014        if (j_1 s< 4 && game->level_mode != 2)
0043701f        *(esi_11 + 0x3bfadc) = game->path_pairs[0x24].primary.primary_samples->transform.position.y
0043702c        if (*(esi_11 + 0x3bfb04) == 0x1c)
0043703a        *(esi_11 + 0x3bfadc) = fconvert.s(fconvert.t(*(esi_11 + 0x3bfadc)) - fconvert.t(0.0299999993f))
00437040        eax_144 = *(esi_11 + 0x3bfb04)
00437080        if (eax_144 == 1 || eax_144 == 0x15 || eax_144 == 0x14 || eax_144 == 0x21 || eax_144 == 0x22 || eax_144 == 0xf || eax_144 == 0x10 || eax_144 == 0x17 || eax_144 == 0x18 || eax_144 == 0x19 || eax_144 == 0x1a || eax_144 == 0x1b || eax_144 == 0x12 || eax_144 == 0x13 || eax_144 == 0x11)
0043708d        int32_t ecx_124 = j_1 & 0x80000007
004370a1        *(esi_11 + 0x3bfae4) = fconvert.s(float.t(8 - var_30_1) * fconvert.t(0.125f))
004370a7        if (ecx_124 s< 0)
004370ad        ecx_124 = ((ecx_124 - 1) | 0xfffffff8) + 1
004370bc        *(esi_11 + 0x3bfae8) = fconvert.s(float.t(ecx_124) * fconvert.t(0.125f))
004370c9        if (*(esi_11 + 0x3bfb04) == 0x1f)
004370d3        *(esi_11 + 0x3bfad8) = fconvert.s(fconvert.t(*(esi_11 + 0x3bfad8)) * fconvert.t(1.10000002f))
004370dc        if (*(esi_11 + 0x3bfb04) == 0x16)
004370ea        if (game->level_mode != 3 || ((game->runtime_flags).w:1.b & 4) != 0)
004370ec        *(esi_11 + 0x3bfadc) = 0xc0400000
004370fa        *(esi_11 + 0x3bfae0) = var_28_2
00437100        int32_t* ecx_128 = esi_11 + 0x3bfb0c
00437104        int32_t k_2 = 4
00437135        int32_t k_1
00437109        void* eax_153
00437109        eax_153.b = *ecx_128
00437109        eax_153:1.b = *(ecx_128 + 1)
00437109        eax_153:2.b = *(ecx_128 + 2)
00437109        eax_153:3.b = *(ecx_128 + 3)
0043710f        if (eax_153 != 0)
00437111        *(eax_153 + 0x18) = 0
00437114        *(eax_153 + 0x14) = 0
00437117        *(eax_153 + 0x10) = 0
0043711a        void* eax_154
0043711a        eax_154.b = *ecx_128
0043711a        eax_154:1.b = *(ecx_128 + 1)
0043711a        eax_154:2.b = *(ecx_128 + 2)
0043711a        eax_154:3.b = *(ecx_128 + 3)
00437123        *(eax_154 + 0x10) = *(esi_11 + 0x3bfad8)
00437128        *(eax_154 + 0x14) = *(esi_11 + 0x3bfadc)
0043712e        *(eax_154 + 0x18) = *(esi_11 + 0x3bfae0)
00437131        ecx_128 = &ecx_128[1]
00437134        k_1 = k_2
00437134        k_2 -= 1
00437135        do while (k_1 != 1)
0043713c        cond:12_1 = var_30_1 + 1 s< 8
0043713f        var_30_1 += 1
00437143        do while (cond:12_1)
0043714d        segment_count = game
00437159        j = j_1 + 1
0043715a        segment_count_2 = &segment_count_2->unknown_000000[1]
00437160        j_1 = j
00437164        i_5 = j
00437166        runtime = segment_count
00437168        do while (j s< segment_count->runtime_row_count)
0043717a        if (runtime->level_mode != 3 || var_42 == 0)
0043717c        var_2c += 1
00437183        do while (i_5 s< runtime->runtime_row_count)
00437190        return
