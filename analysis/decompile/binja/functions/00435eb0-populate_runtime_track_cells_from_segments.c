/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: populate_runtime_track_cells_from_segments @ 0x435eb0 */

00435ec7        uint32_t runtime_build_seed
00435ec7        int16_t top
00435ec7        if (game->selected_level_record_active == 0)
00435ed4        int32_t level_mode = game->level_mode
00435edf        if (level_mode == 4 || level_mode == 7)
00435efc        runtime_build_seed = 0
00435ee1        char* var_58_1 = "Seed"
00435ef3        top = 0
00435ef8        int16_t x87control
00435ef8        runtime_build_seed = __ftol(x87control, random_float_below(32768f))
00435ecf        runtime_build_seed = game->selected_level_record->runtime_build_seed
00435efe        int32_t level_mode_1 = game->level_mode
00435f08        int32_t var_5c_1
00435f08        int32_t level_mode_arg_1
00435f08        int32_t level_mode_arg
00435f08        if (level_mode_1 == 0)
00435f21        level_mode_arg = game->level_mode_arg
00435f24        level_mode_arg_1 = level_mode_arg
00435f25        var_5c_1 = 0
00435f29        label_435f29:
00435f29        int32_t edx
00435f29        edx.b = game->_pad_00[0x30]
00435f29        edx:1.b = game->_pad_00[0x31]
00435f29        edx:2.b = game->_pad_00[0x32]
00435f29        edx:3.b = game->_pad_00[0x33]
00435f36        initialize_high_score_entry(&game->__offset(0xfd2b10).d, runtime_build_seed, level_mode_arg, edx, game->runtime_flags, var_5c_1, level_mode_arg_1)
00435f0b        if (level_mode_1 == 1)
00435f19        level_mode_arg = game->level_mode_arg
00435f1c        level_mode_arg_1 = level_mode_arg
00435f1d        var_5c_1 = 1
00435f1f        goto label_435f29
00435f0f        if (level_mode_1 == 4)
00435f11        level_mode_arg = game->level_mode_arg
00435f14        level_mode_arg_1 = level_mode_arg
00435f15        var_5c_1 = 2
00435f17        goto label_435f29
00435f3b        int32_t subgame_rebuild_selector = game->subgame_rebuild_selector
00435f41        game->replay_update_cursor = 0
00435f49        if (subgame_rebuild_selector == 3)
00435f51        game->subgame_rebuild_selector = 1
00435f5b        game->__offset(0x3bba48).d = 0
00435f61        clear_subgoldy_score_buckets(&game->__offset(0x3bb764).d)
00435f66        game->__offset(0x3bfaa4).d = 3
00435f72        zero_timer_counters()
00435f78        game->__offset(0x3bba64).d = 0
00435f7e        game->__offset(0x3bba6c).d = 0
00435f84        set_math_random_seed(runtime_build_seed)
00435f9f        int16_t x87control_1 = select_level_track_texture_set(data_4df904 + 0xb24, game->__offset(0x1b01e4).d)
00435fa4        int32_t level_mode_2 = game->level_mode
00435fb8        int32_t var_24
00435fb8        int32_t var_1c
00435fb8        if (level_mode_2 == 0 || level_mode_2 == 7 || level_mode_2 == 4 || level_mode_2 == 1)
0043601e        game->first_block_row_count = game->__offset(0x1a7cfc).d
00436021        int32_t ecx_9 = game->__offset(0x1b0138).d
00436027        var_1c = ecx_9
0043602b        game->runtime_row_count = ecx_9
0043602e        if (level_mode_2 == 1)
00436043        level_mode_2, x87control_1 = __ftol(x87control_1, (fconvert.t(game->challenge_difficulty_scalar) * fconvert.t(0.649999976f) + fconvert.t(0.349999994f)) * float.t(var_1c))
00436043        top = 0
00436048        game->runtime_row_count = level_mode_2
00436053        if (game->__offset(0x1b013c).b == 0)
00436063        int32_t i = 0
00436065        game->runtime_row_count = game->__offset(0x1abf1c).d + game->__offset(0x1a7cfc).d
00436070        if (game->level_segment_count s> 0)
00436072        uint8_t* ecx_11 = &game->_pad_a878[4]
00436078        int32_t edx_6
00436078        edx_6.b = (ecx_11 - 0xa87c)->:0xa87c.b
00436078        edx_6:1.b = (ecx_11 - 0xa87c)->:0xa87d.b
00436078        edx_6:2.b = (ecx_11 - 0xa87c)->:0xa87e.b
00436078        edx_6:3.b = (ecx_11 - 0xa87c)->:0xa87f.b
0043607f        i += 1
00436080        game->runtime_row_count += edx_6
00436089        ecx_11 = &ecx_11[0x4220]
00436091        do while (i s< game->level_segment_count)
00436093        var_24 = 0
004360a2        game->completion_row_start = game->runtime_row_count - game->__offset(0x1abf1c).d
004360ad        if (game->runtime_row_count s>= 0xc1c)
004360c0        report_errorf("Track (%s) too long, Maximum Length %i", &game->__offset(0x1b0150).d, 0xc1c)
00435fbc        if (level_mode_2 == 3)
00435fc8        game->first_block_row_count = game->__offset(0x1a7cfc).d
00435fd9        int32_t i_6 = 0x10
00435fde        game->runtime_row_count = game->__offset(0x1abf1c).d + game->__offset(0x1a7cfc).d
00435ff2        int32_t esi_1
00435ff2        int32_t i_1
00435fe1        int32_t edx_2
00435fe1        edx_2.b = game->_pad_a878[4]
00435fe1        edx_2:1.b = game->_pad_a878[5]
00435fe1        edx_2:2.b = game->_pad_a878[6]
00435fe1        edx_2:3.b = game->_pad_a878[7]
00435fea        esi_1 = game->runtime_row_count + edx_2
00435fec        i_1 = i_6
00435fec        i_6 -= 1
00435fed        game->runtime_row_count = esi_1
00435ff2        do while (i_1 != 1)
00435ffa        var_24 = 0
00436000        game->completion_row_start = esi_1 - game->__offset(0x1abf1c).d
0043600d        game->completion_row_start = esi_1 - game->__offset(0x1abf1c).d
004360ce        game->_pad_00[2] = 0
004360d2        game->_pad_00[4] = 0
004360d2        game->_pad_00[5] = 0
004360d2        game->_pad_00[6] = 0
004360d2        game->_pad_00[7] = 0
004360d5        int32_t var_20 = 0
004360d9        char var_42 = 0
004360de        int32_t var_2c = 0
004360e2        game->__offset(0x3bbb24).b = 0
004360e9        void* __offset(Game, 0x3bfb0c) var_28 = &game->__offset(0x3bfb0c).d
004360ed        void* __offset(Game, 0x5ccb5c) edi = &game->__offset(0x5ccb5c).d
004360f3        int32_t var_30 = 0xc80
00436192        struct Game* level_segment_count
00436192        bool cond:3_1
004360fd        int32_t i_7 = 8
00436102        (edi - 0x5ccb5c)->__offset(0x5ccac8).d = 0
00436108        (edi - 0x5ccb5c)->__offset(0x5ccb74).d = 0
0043610b        (edi - 0x5ccb5c)->__offset(0x5ccb68).d = 0
0043610e        (edi - 0x5ccb5c)->__offset(0x5ccbb0).d = 0
00436111        (edi - 0x5ccb5c)->__offset(0x5ccb6c).d = 0
00436114        (edi - 0x5ccb5c)->__offset(0x5ccb60).d = 0
00436117        (edi - 0x5ccb5c)->__offset(0x5ccb5c).d = 0
00436119        (edi - 0x5ccb5c)->__offset(0x5ccb58).d = 0
0043611c        (edi - 0x5ccb5c)->__offset(0x5ccb64).d = 0
0043611f        (edi - 0x5ccb5c)->__offset(0x5ccbb4).d = 0
00436122        (edi - 0x5ccb5c)->__offset(0x5ccbb8).d = 0
00436129        void* __offset(Game, 0x3bfb08) esi_5 = var_28 - 4
0043615f        int32_t i_2
0043612c        int32_t ecx_14 = (esi_5 - 0x3bfb08)->__offset(0x3bfb08).d
0043612e        ecx_14:1.b &= 0x5f
00436131        (esi_5 - 0x3bfb08)->__offset(0x3bfb08).d = ecx_14
00436133        (esi_5 - 0x3bfb08)->:0x3bfb05.b = 0
00436137        (esi_5 - 0x3bfb08)->:0x3bfb08.w = 0
00436146        (esi_5 - 0x3bfb08)->__offset(0x3bfb08).d &= 0xffffafa7
00436148        (esi_5 - 0x3bfb08)->:0x3bfb08.w = 0
0043614d        int32_t edx_9 = (esi_5 - 0x3bfb08)->__offset(0x3bfacc).d
00436150        edx_9.b &= 0x7f
00436153        (esi_5 - 0x3bfb08)->__offset(0x3bfacc).d = edx_9
00436156        set_color_white()
00436156        top -= 1
0043615b        esi_5 += 0x54
0043615e        i_2 = i_7
0043615e        i_7 -= 1
0043615f        do while (i_2 != 1)
00436161        void* __offset(Game, 0x3bfb0c) eax_20 = var_28
00436165        level_segment_count = 8
0043617d        struct Game* i_3
0043616a        void* __offset(Game, 0x3bfb0c) esi_6 = eax_20
0043616e        eax_20 += 0x54
00436171        i_3 = level_segment_count
00436171        level_segment_count -= 1
00436172        (esi_6 - 0x3bfb0c)->__offset(0x3bfb0c).d = 0
00436174        (esi_6 - 0x3bfb0c)->__offset(0x3bfb10).d = 0
00436177        (esi_6 - 0x3bfb0c)->__offset(0x3bfb14).d = 0
0043617a        (esi_6 - 0x3bfb0c)->__offset(0x3bfb18).d = 0
0043617d        do while (i_3 != 1)
0043617f        var_28 = eax_20
00436187        edi += 0xf4
0043618d        cond:3_1 = var_30 != 1
0043618e        var_30 -= 1
00436192        do while (cond:3_1)
0043619f        if (game->__offset(0x1b013c).b == 1)
004361a1        level_segment_count = game->level_segment_count
004361a7        int32_t i_4 = 0
004361ab        if (level_segment_count s> 0)
004361ad        level_segment_count = &game->_pad_a878[8]
004361b3        level_segment_count->_pad_00[0] = 0
004361bc        i_4 += 1
004361bd        level_segment_count = &level_segment_count->_pad_5c[0x41c4]
004361c5        do while (i_4 s< game->level_segment_count)
004361ca        int32_t completion_row_start_2 = 0
004361d4        if (game->runtime_row_count s<= 0)
004361d4        return 
004361da        int32_t i_5 = 0
004361de        struct Game* ebp_1 = game
004361e4        void* __offset(Game, 0x1a7cf8) var_3c_1
004361e4        void* __offset(Game, 0x1a7cf8) esi_7
004361e4        if (i_5 == 0)
004361e6        esi_7 = &ebp_1->__offset(0x1a7cf8).d
004361ec        var_42 = 1
004361f1        var_3c_1 = esi_7
004361f5        (esi_7 - 0x1a7cf8)->__offset(0x1a7cf8).d = i_5
00436209        if (i_5 != ebp_1->completion_row_start || ebp_1->__offset(0x1b013c).b != 0)
00436221        ebp_1->base_subgame_rate = 1f
00436230        if (ebp_1->__offset(0x1b013c).b != 1)
004362a4        int32_t eax_29 = var_24
004362a9        var_24 += 1
004362ba        esi_7 = &ebp_1->_pad_a878[eax_29 * 0x4220]
004362c1        var_3c_1 = esi_7
00436236        int16_t top_1
00436236        if (ebp_1->level_mode != 1)
00436254        top_1 = top - 1
00436254        unimplemented  {fild st0, dword [ebp+0xa874]}
0043625a        char* var_58_5 = "Segtra"
00436238        top_1 = top - 1
00436238        unimplemented  {fld st0, dword [ebp+0x34]}
0043623b        unimplemented  {fmul st0, dword [0x49726c]}
00436241        char* var_58_4 = "Segdif"
00436246        unimplemented  {fadd dword [0x497258]}
0043624c        unimplemented  {fimul st0, dword [ebp+0xa874]}
0043625f        struct Game* level_segment_count_1 = level_segment_count
00436260        float var_5c_3 = fconvert.s(unimplemented  {fstp dword [esp], st0})
00436260        unimplemented  {fstp dword [esp], st0}
00436263        long double st0_2 = random_float_below(var_5c_3)
00436263        unimplemented  {call 0x44dc90}
0043626b        int32_t eax_27
0043626b        int16_t x87control_2
0043626b        eax_27, x87control_2 = __ftol(x87control_1, st0_2)
00436270        int32_t var_28_1 = eax_27
00436274        unimplemented  {fild st0, dword [esp+0x2c]}
00436278        unimplemented  {fmul st0, dword [ebp+0x48]}
0043627b        int32_t eax_28
0043627b        eax_28, x87control_1 = __ftol(x87control_2, st0_2)
0043627b        top = top_1 + 1
0043628f        esi_7 = &ebp_1->_pad_a878[eax_28 * 0x4220]
00436296        var_3c_1 = esi_7
0043629a        (esi_7 - 0x1a7cf8)->:0x1a7d00.b = 1
0043620b        esi_7 = &ebp_1->__offset(0x1abf18).d
00436211        var_42 = 1
00436216        var_3c_1 = esi_7
0043621a        (esi_7 - 0x1a7cf8)->__offset(0x1a7cf8).d = i_5
004362c7        level_segment_count = switch_track_mirror(ebp_1)
004362cc        int32_t eax_30 = (esi_7 - 0x1a7cf8)->__offset(0x1a7cfc).d
004362cf        (esi_7 - 0x1a7cf8)->__offset(0x1a7cf8).d = i_5
004362d3        if (eax_30 s< 0)
004362da        level_segment_count = report_errorf("Negative Segment Length")
004362e5        struct Game* level_segment_count_2 = nullptr
004362ef        if (i_5 s< ebp_1->runtime_row_count)
00437168        int32_t completion_row_start
004362f9        level_segment_count = level_segment_count_2
00436300        if (level_segment_count s>= *(var_3c_1 + 4))
00436300        break
00436306        int32_t level_mode_3 = ebp_1->level_mode
0043630c        if (level_mode_3 != 2)
0043630e        completion_row_start = ebp_1->completion_row_start
00436313        void* __offset(Game, 0x1b4410) edx_17
00436313        if (level_mode_3 == 2 || i_5 s< completion_row_start)
0043634b        edx_17 = var_3c_1
00436326        if (level_mode_3 != 0 && level_mode_3 != 4 && level_mode_3 != 1 && level_mode_3 != 7)
0043632b        edx_17 = &ebp_1->__offset(0x1b4410).d
00436331        if (level_mode_3 == 0 || level_mode_3 == 4 || level_mode_3 == 1 || level_mode_3 == 7 || level_mode_3 == 3)
00436333        edx_17 = &ebp_1->__offset(0x1abf18).d
0043633b        var_3c_1 = edx_17
0043633f        if (i_5 == completion_row_start)
00436341        level_segment_count_2 = nullptr
00436352        if (level_mode_3 != 2)
00436354        completion_row_start = (edx_17 - 0x1b4410)->__offset(0x1b4414).d
0043635b        int32_t completion_row_start_1 = ebp_1->completion_row_start
00436366        if (completion_row_start - level_segment_count_2 + i_5 s<= completion_row_start_1)
004363c5        edx_17 = var_3c_1
00436368        edx_17 = var_3c_1
004363a0        if (edx_17 != &ebp_1->__offset(0x1b4410).d && edx_17 != &ebp_1->__offset(0x1bc850).d && edx_17 != &ebp_1->__offset(0x1c0a70).d && (level_mode_3 == 0 || level_mode_3 == 4 || level_mode_3 == 1 || level_mode_3 == 7 || level_mode_3 == 3) && edx_17 != &ebp_1->__offset(0x1abf18).d)
004363b7        completion_row_start = completion_row_start - completion_row_start_1 - level_segment_count_2 + i_5
004363bb        int32_t ecx_28 = ebp_1->runtime_row_count + completion_row_start
004363bd        ebp_1->completion_row_start = completion_row_start_1 + completion_row_start
004363c0        ebp_1->runtime_row_count = ecx_28
004363ce        if (ebp_1->_pad_00[2] != 0)
004363d6        int32_t ecx_29 = i_5 * 0x3d
004363ea        *(ebp_1 + (ecx_29 << 2) + 0x5ccac8) |= 0x20
004363f7        void* ecx_33 = level_segment_count_2 * 7
00436403        void* esi_9 = edx_17 + (ecx_33 << 3)
00436406        if (((*(edx_17 + (ecx_33 << 3) + 0x814)).w:1.b & 1) != 0)
0043640e        int32_t ecx_34 = i_5 * 0x3d
00436418        int32_t ecx_35 = *(ebp_1 + (ecx_34 << 2) + 0x5ccac8)
0043641f        ecx_35:1.b |= 1
00436422        *(ebp_1 + (ecx_34 << 2) + 0x5ccac8) = ecx_35
0043642d        if (((*(esi_9 + 0x814)).w:1.b & 0x80) != 0)
00436435        int32_t ecx_36 = i_5 * 0x3d
0043643f        int32_t ecx_37 = *(ebp_1 + (ecx_36 << 2) + 0x5ccac8)
00436446        ecx_37:1.b |= 0x80
00436449        *(ebp_1 + (ecx_36 << 2) + 0x5ccac8) = ecx_37
00436458        void* ebx_5 = &ebp_1->_pad_00[i_5 * 0xf4]
0043645c        *(ebx_5 + 0x5ccbb4) = edx_17
00436462        *(ebx_5 + 0x5ccbb8) = var_2c
0043646f        if ((*(esi_9 + 0x814) & 2) != 0)
00436475        int32_t eax_49 = *(ebx_5 + 0x5ccac8)
0043647b        eax_49.b |= 2
0043647d        *(ebx_5 + 0x5ccac8) = eax_49
004364a5        set_bod_object(ebx_5 + 0x5ccacc, *(data_4df904 + *(esi_9 + 0x828) * 0xbc + 0x48e2c))
004364b0        set_matrix_identity(ebx_5 + 0x5ccb04)
004364c1        unimplemented  {fild st0, dword [esp+0x14]}
004364c5        int32_t eax_52
004364c5        eax_52.b = *(esi_9 + 0x82c)
004364c5        eax_52:1.b = *(esi_9 + 0x82d)
004364c5        eax_52:2.b = *(esi_9 + 0x82e)
004364c5        eax_52:3.b = *(esi_9 + 0x82f)
004364c7        *(ebx_5 + 0x5ccb34) = eax_52
004364c9        int32_t eax_53
004364c9        eax_53.b = *(esi_9 + 0x830)
004364c9        eax_53:1.b = *(esi_9 + 0x831)
004364c9        eax_53:2.b = *(esi_9 + 0x832)
004364c9        eax_53:3.b = *(esi_9 + 0x833)
004364cc        *(ebx_5 + 0x5ccb38) = eax_53
004364cf        int32_t ecx_45
004364cf        ecx_45.b = *(esi_9 + 0x834)
004364cf        ecx_45:1.b = *(esi_9 + 0x835)
004364cf        ecx_45:2.b = *(esi_9 + 0x836)
004364cf        ecx_45:3.b = *(esi_9 + 0x837)
004364d2        *(ebx_5 + 0x5ccb3c) = ecx_45
004364d5        unimplemented  {fadd dword [ebx+0x5ccb3c]}
004364db        *(ebx_5 + 0x5ccb3c) = fconvert.s(unimplemented  {fstp dword [ebx+0x5ccb3c], st0})
004364db        unimplemented  {fstp dword [ebx+0x5ccb3c], st0}
004364e8        if ((*(esi_9 + 0x814) & 8) == 0)
0043651c        *(ebx_5 + 0x5ccb54) = 0
00436522        *(ebx_5 + 0x5ccb50) = 0
00436528        *(ebx_5 + 0x5ccb4c) = 0
004364ea        int32_t eax_54 = *(ebx_5 + 0x5ccac8)
004364f6        eax_54.b |= 8
004364f8        *(ebx_5 + 0x5ccac8) = eax_54
00436506        *(ebx_5 + 0x5ccb4c) = *(esi_9 + 0x838)
0043650f        *(ebx_5 + 0x5ccb50) = *(esi_9 + 0x83c)
00436515        *(ebx_5 + 0x5ccb54) = *(esi_9 + 0x840)
0043652e        edx_17 = var_3c_1
00436539        if ((*(esi_9 + 0x814) & 1) != 0)
00436546        *(ebx_5 + 0x5ccac8) |= 0x4001
0043656b        *(ebx_5 + 0x5ccb64) = *(edx_17 + &level_segment_count_2->_pad_00[0x25] * 0x38)
00436571        int32_t edx_26 = *(esi_9 + 0x81c)
00436573        *(ebx_5 + 0x5ccb58) = edx_26.b
00436573        *(ebx_5 + 0x5ccb59) = edx_26:1.b
00436573        *(ebx_5 + 0x5ccb5a) = edx_26:2.b
00436573        *(ebx_5 + 0x5ccb5b) = edx_26:3.b
00436575        int32_t edx_27 = *(esi_9 + 0x820)
00436578        *(ebx_5 + 0x5ccb5c) = edx_27.b
00436578        *(ebx_5 + 0x5ccb5d) = edx_27:1.b
00436578        *(ebx_5 + 0x5ccb5e) = edx_27:2.b
00436578        *(ebx_5 + 0x5ccb5f) = edx_27:3.b
0043657b        int32_t eax_61 = *(esi_9 + 0x824)
0043657e        *(ebx_5 + 0x5ccb60) = eax_61.b
0043657e        *(ebx_5 + 0x5ccb61) = eax_61:1.b
0043657e        *(ebx_5 + 0x5ccb62) = eax_61:2.b
0043657e        *(ebx_5 + 0x5ccb63) = eax_61:3.b
00436588        if ((*(esi_9 + 0x814) & 8) != 0)
0043658a        int32_t eax_62 = *(ebx_5 + 0x5ccac8)
00436590        eax_62.b |= 8
00436592        *(ebx_5 + 0x5ccac8) = eax_62
0043659e        *(ebx_5 + 0x5ccb68) = *(esi_9 + 0x844)
004365ab        if ((*(esi_9 + 0x814) & 4) != 0)
004365ad        int32_t eax_63 = *(ebx_5 + 0x5ccac8)
004365b3        eax_63.b |= 4
004365b5        *(ebx_5 + 0x5ccac8) = eax_63
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
00436648        *(ebp_1 + ((i_5 + (i_5 * 3 + 0x12414) * 0x14 + 0x615c) << 2)) = *(esi_9 + 0x848)
00437143        bool cond:12_1
00436655        int32_t edx_29
00436655        int32_t ebp_2
00436655        if (game->_pad_00[2] == 0)
00436664        edx_29 = var_30_1
00436668        ebp_2 = edx_29
00436657        edx_29 = var_30_1
00436660        ebp_2 = 7 - edx_29
00436682        void* esi_11 = &game->_pad_00[(edx_29 + (completion_row_start_2 << 3)) * 0x54]
00436685        int32_t eax_70 = *(esi_11 + 0x3bfb08)
0043668b        eax_70.b &= 0xe0
0043668f        *(esi_11 + 0x3bfb08) = eax_70 ^ (edx_29 & 7)
0043669f        *(esi_11 + 0x3bfb0c) = 0
004366a1        *(esi_11 + 0x3bfb10) = 0
004366a4        *(esi_11 + 0x3bfb14) = 0
004366a7        *(esi_11 + 0x3bfb18) = 0
004366b1        if (completion_row_start_2 s>= game->first_block_row_count)
004366b6        var_1c.b = 0
004366bd        if (completion_row_start_2 s< game->first_block_row_count || completion_row_start_2 s>= game->completion_row_start)
004366bf        var_1c.b = 1
004366ce        set_bod_object(esi_11 + 0x3bfac8, 0)
004366e4        void* __offset(Game, 0x1a7cf8) edx_32 = var_3c_1
004366ee        char* ebp_5 = edx_32 + &level_segment_count_2->_pad_00[ebp_2 << 8] + 0x14
004366f2        edx_32.b = *ebp_5
004366f6        char eax_75 = normalize_segment_glyph_for_track_flags(game, edx_32.b, completion_row_start_2, var_1c.b)
00436704        if (sx.d(eax_75) - 0x20 u> 0x5d)
00436eb5        label_436eb5:
00436eb5        void* __offset(Game, 0x1a7cf8) edx_58 = var_3c_1
00436ebd        int32_t eax_141 = (edx_58 - 0x1a7cf8)->__offset(0x1a7d08).d
00436ec0        edx_58.b = *ebp_5
00436ec3        int32_t var_58_34 = eax_141
00436ed4        int32_t var_5c_5 = sx.d(normalize_segment_glyph_for_track_flags(game, edx_58.b, completion_row_start_2, 1))
00436ed5        char* var_60_4 = "TrackError:%c in Segment %s\n"
0043670a        int32_t edx_33 = 0
0043670c        edx_33.b = *(sx.d(eax_75) + &jump_table_437194[0x14])
00436712        switch (edx_33)
00436719        case 0
00436719        *(esi_11 + 0x3bfb04) = 0
00436720        int32_t eax_76 = *(esi_11 + 0x3bfacc)
00436726        eax_76.b &= 0xdf
00436728        *(esi_11 + 0x3bfacc) = eax_76
0043674d        case 1
0043674d        *(esi_11 + 0x3bfb04) = 0x20
00436754        int32_t eax_78 = *(esi_11 + 0x3bfacc)
0043675a        eax_78.b &= 0xdf
0043675c        *(esi_11 + 0x3bfacc) = eax_78
004367e5        case 2
004367e5        void* ecx_69 = data_4df904
004367eb        int32_t edx_35
004367eb        edx_35.b = *(ecx_69 + 0x44b34)
004367eb        edx_35:1.b = *(ecx_69 + 0x44b35)
004367eb        edx_35:2.b = *(ecx_69 + 0x44b36)
004367eb        edx_35:3.b = *(ecx_69 + 0x44b37)
004367f4        set_bod_object(esi_11 + 0x3bfac8, edx_35)
004367f9        *(esi_11 + 0x3bfb04) = 0x17
00436800        int32_t eax_84 = *(esi_11 + 0x3bfacc)
00436806        eax_84.b |= 0x20
00436808        *(esi_11 + 0x3bfacc) = eax_84
004368f7        case 3
004368f7        void* ecx_79 = data_4df904
004368fd        int32_t edx_39
004368fd        edx_39.b = *(ecx_79 + 0x447b4)
004368fd        edx_39:1.b = *(ecx_79 + 0x447b5)
004368fd        edx_39:2.b = *(ecx_79 + 0x447b6)
004368fd        edx_39:3.b = *(ecx_79 + 0x447b7)
00436906        set_bod_object(esi_11 + 0x3bfac8, edx_39)
0043690b        *(esi_11 + 0x3bfb04) = 0x22
00436912        int32_t eax_94 = *(esi_11 + 0x3bfacc)
00436918        eax_94.b |= 0x20
0043691a        *(esi_11 + 0x3bfacc) = eax_94
00436a13        case 4
00436a13        int32_t ecx_90 = var_20 + 1
00436a14        int32_t ebp_7 = *(esi_11 + 0x3bfacc) & 0xffffffdf
00436a1a        var_20 = ecx_90
00436a1e        *(esi_11 + 0x3bfacc) = ebp_7
00436a24        int32_t eax_104 = ebp_7
00436a26        if (ecx_90 == 0xf)
00436a28        var_20 = 0
00436a30        *(esi_11 + 0x3bfb04) = 0x16
00436a3f        if (ecx_90 != 8)
00436aab        eax_104.b &= 0xdf
00436aad        *(esi_11 + 0x3bfacc) = eax_104
00436ab3        *(esi_11 + 0x3bfb04) = 0x16
00436a41        void* ecx_91 = data_4df904
00436a47        int32_t edx_43
00436a47        edx_43.b = *(ecx_91 + 0x444dc)
00436a47        edx_43:1.b = *(ecx_91 + 0x444dd)
00436a47        edx_43:2.b = *(ecx_91 + 0x444de)
00436a47        edx_43:3.b = *(ecx_91 + 0x444df)
00436a50        set_bod_object(esi_11 + 0x3bfac8, edx_43)
00436a72        *(esi_11 + 0x3bfacc) |= 0x20
00436a9a        store_color4f(&game->_pad_00[(var_30_1 + (completion_row_start_2 << 3) + 0xb6cc) * 0x54], 1f, 1f, 1f, 0.999000013f)
00436a9a        top -= 1
00436a9f        *(esi_11 + 0x3bfb04) = 0x16
00436961        case 5
00436961        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x44b34))
00436966        *(esi_11 + 0x3bfb04) = 0x18
0043696d        int32_t eax_98 = *(esi_11 + 0x3bfacc)
00436973        eax_98.b |= 0x20
00436975        *(esi_11 + 0x3bfacc) = eax_98
00436933        case 6
00436933        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x44124))
00436938        *(esi_11 + 0x3bfb04) = 0x1c
0043693f        int32_t eax_96 = *(esi_11 + 0x3bfacc)
00436945        eax_96.b |= 0x20
00436947        *(esi_11 + 0x3bfacc) = eax_96
004369bc        case 7
004369bc        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x447b4))
004369c1        *(esi_11 + 0x3bfb04) = 0x15
004369c8        int32_t eax_101 = *(esi_11 + 0x3bfacc)
004369ce        eax_101.b |= 0x20
004369d0        *(esi_11 + 0x3bfacc) = eax_101
004368aa        case 8
004368aa        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x447b4))
004368af        *(esi_11 + 0x3bfb04) = 1
004368b6        int32_t eax_91 = *(esi_11 + 0x3bfacc)
004368bc        eax_91.b |= 0x20
004368be        *(esi_11 + 0x3bfacc) = eax_91
00436e02        case 9
00436e02        if (game->level_mode == 1)
00436e04        unimplemented  {fild st0, dword [esp+0x24]}
00436e08        int32_t ecx_122 = *(ebx_5 + 0x5ccac8)
00436e0e        ecx_122:1.b &= 0xbf
00436e11        unimplemented  {fsub st0, dword [0x497210]}
00436e1a        *(ebx_5 + 0x5ccac8) = ecx_122 | 1
00436e20        *(ebx_5 + 0x5ccb64) = 0
00436e2a        unimplemented  {fadd dword [0x497228]}
00436e30        *(ebx_5 + 0x5ccb58) = fconvert.s(unimplemented  {fstp dword [ebx+0x5ccb58], st0})
00436e30        unimplemented  {fstp dword [ebx+0x5ccb58], st0}
00436e36        unimplemented  {fild st0, dword [esp+0x14]}
00436e40        *(ebx_5 + 0x5ccb5c) = *(esi_11 + 0x3bfadc)
00436e46        unimplemented  {fadd dword [0x497228]}
00436e4c        *(ebx_5 + 0x5ccb60) = fconvert.s(unimplemented  {fstp dword [ebx+0x5ccb60], st0})
00436e4c        unimplemented  {fstp dword [ebx+0x5ccb60], st0}
00436e57        if (game->_pad_00[2] != 0)
00436e59        unimplemented  {fld st0, dword [ebx+0x5ccb58]}
00436e5f        unimplemented  {fmul st0, dword [0x497214]}
00436e65        *(ebx_5 + 0x5ccb58) = fconvert.s(unimplemented  {fstp dword [ebx+0x5ccb58], st0})
00436e65        unimplemented  {fstp dword [ebx+0x5ccb58], st0}
00436e02        goto label_436e6b
00436e6b        case 0xa
00436e6b        label_436e6b:
00436e72        if ((*(ebx_5 + 0x5ccac8) & 0xc0) != 0)
00436e9e        int32_t eax_140 = *(esi_11 + 0x3bfacc)
00436ea4        eax_140.b &= 0xdf
00436ea6        *(esi_11 + 0x3bfacc) = eax_140
00436eac        *(esi_11 + 0x3bfb04) = 0
00436e82        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x44b34))
00436e87        *(esi_11 + 0x3bfb04) = 0xf
00436e8e        int32_t eax_139 = *(esi_11 + 0x3bfacc)
00436e94        eax_139.b |= 0x20
00436e96        *(esi_11 + 0x3bfacc) = eax_139
00436c67        case 0xb
00436c67        void* ecx_106 = data_4df904
00436c6d        int32_t edx_51
00436c6d        edx_51.b = *(ecx_106 + 0x44d2c)
00436c6d        edx_51:1.b = *(ecx_106 + 0x44d2d)
00436c6d        edx_51:2.b = *(ecx_106 + 0x44d2e)
00436c6d        edx_51:3.b = *(ecx_106 + 0x44d2f)
00436c76        set_bod_object(esi_11 + 0x3bfac8, edx_51)
00436c7d        *(esi_11 + 0x3bfae4) = 0
00436c83        *(esi_11 + 0x3bfae8) = 0
00436c89        *(esi_11 + 0x3bfb04) = 6
00436c90        int32_t eax_122 = *(esi_11 + 0x3bfacc)
00436c96        eax_122.b |= 0x20
00436c98        *(esi_11 + 0x3bfacc) = eax_122
004369ea        case 0xc
004369ea        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x445f4))
004369ef        *(esi_11 + 0x3bfb04) = 0xe
004369f6        int32_t eax_103 = *(esi_11 + 0x3bfacc)
004369fc        eax_103.b |= 0x20
004369fe        *(esi_11 + 0x3bfacc) = eax_103
00436ad0        case 0xd
00436ad0        if (completion_row_start_2 s<= 0 || *(esi_11 + 0x3bf864) != 3)
00436b21        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x44d2c))
00436b26        *(esi_11 + 0x3bfae4) = 0
00436b2c        *(esi_11 + 0x3bfae8) = 0
00436b32        *(esi_11 + 0x3bfb04) = 3
00436b39        int32_t eax_112 = *(esi_11 + 0x3bfacc)
00436b3f        eax_112.b |= 0x20
00436b41        *(esi_11 + 0x3bfacc) = eax_112
00436ad2        void* ecx_96 = data_4df904
00436ad8        int32_t edx_47
00436ad8        edx_47.b = *(ecx_96 + 0x44d2c)
00436ad8        edx_47:1.b = *(ecx_96 + 0x44d2d)
00436ad8        edx_47:2.b = *(ecx_96 + 0x44d2e)
00436ad8        edx_47:3.b = *(ecx_96 + 0x44d2f)
00436ae1        set_bod_object(esi_11 + 0x3bfac8, edx_47)
00436ae6        *(esi_11 + 0x3bfae4) = 0
00436aec        *(esi_11 + 0x3bfae8) = 0
00436af2        *(esi_11 + 0x3bfb04) = 9
00436af9        int32_t eax_110 = *(esi_11 + 0x3bfacc)
00436aff        eax_110.b |= 0x20
00436b01        *(esi_11 + 0x3bfacc) = eax_110
00436b07        *(esi_11 + 0x3bf864) = 0xc
0043676b        case 0xe
0043676b        *(esi_11 + 0x3bfb04) = 0
00436772        int32_t eax_79 = *(esi_11 + 0x3bfacc)
00436778        eax_79.b &= 0xdf
0043677a        *(esi_11 + 0x3bfacc) = eax_79
00436780        switch_track_mirror(game)
0043686e        case 0xf
0043686e        void* ecx_74 = data_4df904
00436874        int32_t edx_37
00436874        edx_37.b = *(ecx_74 + 0x44b34)
00436874        edx_37:1.b = *(ecx_74 + 0x44b35)
00436874        edx_37:2.b = *(ecx_74 + 0x44b36)
00436874        edx_37:3.b = *(ecx_74 + 0x44b37)
0043687d        set_bod_object(esi_11 + 0x3bfac8, edx_37)
00436882        *(esi_11 + 0x3bfb04) = 0x13
00436889        int32_t eax_89 = *(esi_11 + 0x3bfacc)
0043688f        eax_89.b |= 0x20
00436891        *(esi_11 + 0x3bfacc) = eax_89
00436798        case 0x10
00436798        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x44b34))
0043679d        *(esi_11 + 0x3bfb04) = 0x11
004367a4        int32_t eax_81 = *(esi_11 + 0x3bfacc)
004367aa        eax_81.b |= 0x20
004367ac        *(esi_11 + 0x3bfacc) = eax_81
00436980        case 0x11
00436980        void* ecx_84 = data_4df904
00436986        int32_t edx_41
00436986        edx_41.b = *(ecx_84 + 0x44b34)
00436986        edx_41:1.b = *(ecx_84 + 0x44b35)
00436986        edx_41:2.b = *(ecx_84 + 0x44b36)
00436986        edx_41:3.b = *(ecx_84 + 0x44b37)
0043698f        set_bod_object(esi_11 + 0x3bfac8, edx_41)
00436994        *(esi_11 + 0x3bfb04) = 0x19
0043699b        int32_t eax_99 = *(esi_11 + 0x3bfacc)
004369a1        eax_99.b |= 0x20
004369a3        *(esi_11 + 0x3bfacc) = eax_99
0043684f        case 0x12
0043684f        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x44b34))
00436854        *(esi_11 + 0x3bfb04) = 0x12
0043685b        int32_t eax_88 = *(esi_11 + 0x3bfacc)
00436861        eax_88.b |= 0x20
00436863        *(esi_11 + 0x3bfacc) = eax_88
00436ce0        case 0x13
00436ce0        if (eax_75 == 0x50)
00436ce2        *(esi_11 + 0x3bfb04) = 0x1e
00436ced        if (eax_75 == 0x70)
00436cef        *(esi_11 + 0x3bfb04) = 0x1d
00436cfa        int32_t ecx_110 = *(ebx_5 + 0x5ccb68)
00436d05        int32_t eax_126 = ecx_110 << 3
00436d0c        void* ecx_111
00436d0c        if (game->_pad_00[2] == 0)
00436d27        ecx_111 = &game->_pad_00[(eax_126 - ecx_110) * 0x30 + 0xff2914]
00436d16        ecx_111 = &game->_pad_00[(eax_126 - ecx_110) * 0x30 + 0xff29bc]
00436d32        *(esi_11 + 0x3bfb00) = ecx_111
00436d43        *(esi_11 + 0x3bfacc) &= 0xffffffdf
00436d49        if (var_41_1 == 0)
00436d57        var_41_1 = 1
00436d60        set_bod_object(esi_11 + 0x3bfac8, *(*(esi_11 + 0x3bfb00) + 0x24))
00436d72        *(esi_11 + 0x3bfacc) |= 0x20
00436d78        void* ecx_117 = *(esi_11 + 0x3bfb00)
00436d7e        int32_t edx_54
00436d7e        edx_54.b = *(ecx_117 + 0x84)
00436d7e        edx_54:1.b = *(ecx_117 + 0x85)
00436d7e        edx_54:2.b = *(ecx_117 + 0x86)
00436d7e        edx_54:3.b = *(ecx_117 + 0x87)
00436d8b        set_bod_object(ebx_5 + 0x5ccb78, edx_54)
00436d9c        *(ebx_5 + 0x5ccb7c) |= 0x20
00436da8        *(ebx_5 + 0x5ccb74) = (var_3c_1 - 0x1a7cf8)->__offset(0x1abd0c).d
00436db4        int32_t k = 0
00436dbb        if (*(*(esi_11 + 0x3bfb00) + 0x48) s> 0)
00436dc1        char* ecx_121 = ebx_5 + 0x5ccac8
00436dc7        int32_t eax_135
00436dc7        eax_135.b = *ecx_121
00436dc7        eax_135:1.b = ecx_121[1]
00436dc7        eax_135:2.b = ecx_121[2]
00436dc7        eax_135:3.b = ecx_121[3]
00436dcb        if ((eax_135.b & 0x40) == 0)
00436dd9        eax_135.b |= 0x40
00436ddb        *ecx_121 = eax_135.b
00436ddb        ecx_121[1] = eax_135:1.b
00436ddb        ecx_121[2] = eax_135:2.b
00436ddb        ecx_121[3] = eax_135:3.b
00436ddd        ecx_121[0xa4] = (esi_11 + 0x3bfac8).b
00436ddd        ecx_121[0xa5] = (esi_11 + 0x3bfac8):1.b
00436ddd        ecx_121[0xa6] = (esi_11 + 0x3bfac8):2.b
00436ddd        ecx_121[0xa7] = (esi_11 + 0x3bfac8):3.b
00436dcd        eax_135.b |= 0x80
00436dcf        *ecx_121 = eax_135.b
00436dcf        ecx_121[1] = eax_135:1.b
00436dcf        ecx_121[2] = eax_135:2.b
00436dcf        ecx_121[3] = eax_135:3.b
00436dd1        ecx_121[0xa8] = (esi_11 + 0x3bfac8).b
00436dd1        ecx_121[0xa9] = (esi_11 + 0x3bfac8):1.b
00436dd1        ecx_121[0xaa] = (esi_11 + 0x3bfac8):2.b
00436dd1        ecx_121[0xab] = (esi_11 + 0x3bfac8):3.b
00436de9        k += 1
00436dea        ecx_121 = &ecx_121[0xf4]
00436df3        do while (k s< *(*(esi_11 + 0x3bfb00) + 0x48))
00436733        case 0x14
00436733        *(esi_11 + 0x3bfb04) = 0x23
0043673a        int32_t eax_77 = *(esi_11 + 0x3bfacc)
00436740        eax_77.b &= 0xdf
00436742        *(esi_11 + 0x3bfacc) = eax_77
00436cb1        case 0x15
00436cb1        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x44cf4))
00436cb8        *(esi_11 + 0x3bfae4) = 0
00436cbe        *(esi_11 + 0x3bfae8) = 0
00436cc4        *(esi_11 + 0x3bfb04) = 5
00436ccb        int32_t eax_124 = *(esi_11 + 0x3bfacc)
00436cd1        eax_124.b |= 0x20
00436cd3        *(esi_11 + 0x3bfacc) = eax_124
004367c6        case 0x16
004367c6        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x44b34))
004367cb        *(esi_11 + 0x3bfb04) = 0xf
004367d2        int32_t eax_83 = *(esi_11 + 0x3bfacc)
004367d8        eax_83.b |= 0x20
004367da        *(esi_11 + 0x3bfacc) = eax_83
00436821        case 0x17
00436821        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x44b34))
00436826        *(esi_11 + 0x3bfb04) = 0x10
0043682d        int32_t eax_86 = *(esi_11 + 0x3bfacc)
00436833        eax_86.b |= 0x20
00436835        *(esi_11 + 0x3bfacc) = eax_86
004368d8        case 0x18
004368d8        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x447b4))
004368dd        *(esi_11 + 0x3bfb04) = 0x21
004368e4        int32_t eax_93 = *(esi_11 + 0x3bfacc)
004368ea        eax_93.b |= 0x20
004368ec        *(esi_11 + 0x3bfacc) = eax_93
00436beb        case 0x19
00436beb        if (completion_row_start_2 s<= 0 || *(esi_11 + 0x3bf864) != 3)
00436c3c        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x44cf4))
00436c41        *(esi_11 + 0x3bfae4) = 0
00436c47        *(esi_11 + 0x3bfae8) = 0
00436c4d        *(esi_11 + 0x3bfb04) = 2
00436c54        int32_t eax_121 = *(esi_11 + 0x3bfacc)
00436c5a        eax_121.b |= 0x20
00436c5c        *(esi_11 + 0x3bfacc) = eax_121
00436bfb        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x44cf4))
00436c00        *(esi_11 + 0x3bfae4) = 0
00436c06        *(esi_11 + 0x3bfae8) = 0
00436c0c        *(esi_11 + 0x3bfb04) = 8
00436c13        int32_t eax_119 = *(esi_11 + 0x3bfacc)
00436c19        eax_119.b |= 0x20
00436c1b        *(esi_11 + 0x3bfacc) = eax_119
00436c21        *(esi_11 + 0x3bf864) = 0xb
00436b5d        case 0x1a
00436b5d        if (completion_row_start_2 s<= 0 || *(esi_11 + 0x3bf864) != 3)
00436ba0        void* ecx_101 = data_4df904
00436ba6        int32_t edx_49
00436ba6        edx_49.b = *(ecx_101 + 0x44d64)
00436ba6        edx_49:1.b = *(ecx_101 + 0x44d65)
00436ba6        edx_49:2.b = *(ecx_101 + 0x44d66)
00436ba6        edx_49:3.b = *(ecx_101 + 0x44d67)
00436baf        set_bod_object(esi_11 + 0x3bfac8, edx_49)
00436bb4        *(esi_11 + 0x3bfae4) = 0
00436bba        *(esi_11 + 0x3bfae8) = 0
00436bc0        *(esi_11 + 0x3bfb04) = 4
00436bc7        int32_t eax_116 = *(esi_11 + 0x3bfacc)
00436bcd        eax_116.b |= 0x20
00436bcf        *(esi_11 + 0x3bfacc) = eax_116
00436b6e        set_bod_object(esi_11 + 0x3bfac8, *(data_4df904 + 0x44d64))
00436b73        *(esi_11 + 0x3bfae4) = 0
00436b79        *(esi_11 + 0x3bfae8) = 0
00436b7f        *(esi_11 + 0x3bfb04) = 0xa
00436b86        int32_t eax_115 = *(esi_11 + 0x3bfacc)
00436b8c        eax_115.b |= 0x20
00436b8e        *(esi_11 + 0x3bfacc) = eax_115
00436b94        *(esi_11 + 0x3bf864) = 0xd
00436712        case 0x1b
00436712        goto label_436eb5
00436eea        *(esi_11 + 0x3bfae0) = 0
00436eed        *(esi_11 + 0x3bfadc) = 0
00436ef0        *(esi_11 + 0x3bfad8) = 0
00436ef2        *(ebx_5 + 0x5ccb90) = 0
00436ef8        *(ebx_5 + 0x5ccb8c) = 0
00436efe        *(ebx_5 + 0x5ccb88) = 0
00436f04        char eax_145 = *(esi_11 + 0x3bfb04)
00436f10        float var_28_2
00436f10        if (eax_145 == 0x1d || eax_145 == 0x1e)
00436f63        unimplemented  {fild st0, dword [esp+0x14]}
00436f67        *(esi_11 + 0x3bfad8) = 0
00436f69        unimplemented  {fadd dword [0x497228]}
00436f6f        var_28_2 = fconvert.s(unimplemented  {fst dword [esp+0x2c], st0})
00436f73        unimplemented  {fsub st0, dword [0x497228]}
00436f79        *(esi_11 + 0x3bfae0) = fconvert.s(unimplemented  {fst dword [esi+0x3bfae0], st0})
00436f86        if ((data_4df934 & 0x20) == 0)
00436ff3        int32_t eax_149 = *(ebx_5 + 0x5ccb7c)
00436ff9        eax_149.b &= 0xdf
00436ffb        unimplemented  {fstp st0, st0}
00436ffb        unimplemented  {fstp st0, st0}
00436ffd        *(ebx_5 + 0x5ccb7c) = eax_149
00436f88        *(ebx_5 + 0x5ccb88) = 0
00436f92        *(ebx_5 + 0x5ccb90) = fconvert.s(unimplemented  {fstp dword [ebx+0x5ccb90], st0})
00436f92        unimplemented  {fstp dword [ebx+0x5ccb90], st0}
00436fa4        float var_10[0x4]
00436fa4        float* eax_147 = get_track_skirt_color(data_4df904 + 0x74618, &var_10)
00436fb4        float ebp_8 = *eax_147
00436fb6        *(ebx_5 + 0x5ccba0) = ebp_8.b
00436fb6        *(ebx_5 + 0x5ccba1) = ebp_8:1.b
00436fb6        *(ebx_5 + 0x5ccba2) = ebp_8:2.b
00436fb6        *(ebx_5 + 0x5ccba3) = ebp_8:3.b
00436fb8        int32_t ebp_9 = eax_147[1]
00436fbb        *(ebx_5 + 0x5ccba4) = ebp_9.b
00436fbb        *(ebx_5 + 0x5ccba5) = ebp_9:1.b
00436fbb        *(ebx_5 + 0x5ccba6) = ebp_9:2.b
00436fbb        *(ebx_5 + 0x5ccba7) = ebp_9:3.b
00436fbe        int32_t ebp_10 = eax_147[2]
00436fc1        *(ebx_5 + 0x5ccba8) = ebp_10.b
00436fc1        *(ebx_5 + 0x5ccba9) = ebp_10:1.b
00436fc1        *(ebx_5 + 0x5ccbaa) = ebp_10:2.b
00436fc1        *(ebx_5 + 0x5ccbab) = ebp_10:3.b
00436fc4        int32_t edx_60 = eax_147[3]
00436fc7        *(ebx_5 + 0x5ccbac) = edx_60.b
00436fc7        *(ebx_5 + 0x5ccbad) = edx_60:1.b
00436fc7        *(ebx_5 + 0x5ccbae) = edx_60:2.b
00436fc7        *(ebx_5 + 0x5ccbaf) = edx_60:3.b
00436fce        float var_64_3 = *eax_147
00436fd3        int32_t var_60_5 = eax_147[1]
00436fdc        int32_t var_5c_6 = eax_147[2]
00436fdf        int32_t var_58_36 = eax_147[3]
00436fe9        x87control_1 = set_object_color(*(ebx_5 + 0x5ccb9c))
00436f12        unimplemented  {fild st0, dword [esp+0x24]}
00436f16        unimplemented  {fsub st0, dword [0x497210]}
00436f1c        unimplemented  {fadd dword [0x497228]}
00436f22        *(esi_11 + 0x3bfad8) = fconvert.s(unimplemented  {fstp dword [edi], st0})
00436f22        unimplemented  {fstp dword [edi], st0}
00436f24        *(esi_11 + 0x3bfadc) = 0
00436f2a        eax_145 = *(esi_11 + 0x3bfb04)
00436f3a        if (eax_145 == 8 || eax_145 == 9 || eax_145 == 0xa)
00436f3c        *(esi_11 + 0x3bfadc) = 0x3f000000
00436f46        unimplemented  {fild st0, dword [esp+0x14]}
00436f4a        unimplemented  {fadd dword [0x497228]}
00436f50        var_28_2 = fconvert.s(unimplemented  {fstp dword [esp+0x2c], st0})
00436f50        unimplemented  {fstp dword [esp+0x2c], st0}
00436f58        *(esi_11 + 0x3bfae0) = var_28_2
00437014        if (completion_row_start_2 s< 4 && game->level_mode != 2)
0043701f        *(esi_11 + 0x3bfadc) = *(game->__offset(0xff58ac).d + 0x34)
0043702c        if (*(esi_11 + 0x3bfb04) == 0x1c)
0043702e        unimplemented  {fld st0, dword [esi+0x3bfadc]}
00437034        unimplemented  {fsub st0, dword [0x497548]}
0043703a        *(esi_11 + 0x3bfadc) = fconvert.s(unimplemented  {fstp dword [esi+0x3bfadc], st0})
0043703a        unimplemented  {fstp dword [esi+0x3bfadc], st0}
00437040        eax_145 = *(esi_11 + 0x3bfb04)
00437080        if (eax_145 == 1 || eax_145 == 0x15 || eax_145 == 0x14 || eax_145 == 0x21 || eax_145 == 0x22 || eax_145 == 0xf || eax_145 == 0x10 || eax_145 == 0x17 || eax_145 == 0x18 || eax_145 == 0x19 || eax_145 == 0x1a || eax_145 == 0x1b || eax_145 == 0x12 || eax_145 == 0x13 || eax_145 == 0x11)
0043708d        int32_t ecx_134 = completion_row_start_2 & 0x80000007
00437093        int32_t var_18_1 = 8 - var_30_1
00437097        unimplemented  {fild st0, dword [esp+0x3c]}
0043709b        unimplemented  {fmul st0, dword [0x497428]}
004370a1        *(esi_11 + 0x3bfae4) = fconvert.s(unimplemented  {fstp dword [esi+0x3bfae4], st0})
004370a1        unimplemented  {fstp dword [esi+0x3bfae4], st0}
004370a7        if (ecx_134 s< 0)
004370ad        ecx_134 = ((ecx_134 - 1) | 0xfffffff8) + 1
004370ae        int32_t var_18_2 = ecx_134
004370b2        unimplemented  {fild st0, dword [esp+0x3c]}
004370b6        unimplemented  {fmul st0, dword [0x497428]}
004370bc        *(esi_11 + 0x3bfae8) = fconvert.s(unimplemented  {fstp dword [esi+0x3bfae8], st0})
004370bc        unimplemented  {fstp dword [esi+0x3bfae8], st0}
004370c9        if (*(esi_11 + 0x3bfb04) == 0x1f)
004370cb        unimplemented  {fld st0, dword [edi]}
004370cd        unimplemented  {fmul st0, dword [0x497434]}
004370d3        *(esi_11 + 0x3bfad8) = fconvert.s(unimplemented  {fstp dword [edi], st0})
004370d3        unimplemented  {fstp dword [edi], st0}
004370dc        if (*(esi_11 + 0x3bfb04) == 0x16)
004370ea        if (game->level_mode != 3 || ((game->runtime_flags).w:1.b & 4) != 0)
004370ec        *(esi_11 + 0x3bfadc) = 0xc0400000
004370fa        *(esi_11 + 0x3bfae0) = var_28_2
00437100        int32_t* ecx_138 = esi_11 + 0x3bfb0c
00437104        int32_t k_2 = 4
00437135        int32_t k_1
00437109        void* eax_154
00437109        eax_154.b = *ecx_138
00437109        eax_154:1.b = *(ecx_138 + 1)
00437109        eax_154:2.b = *(ecx_138 + 2)
00437109        eax_154:3.b = *(ecx_138 + 3)
0043710f        if (eax_154 != 0)
00437111        *(eax_154 + 0x18) = 0
00437114        *(eax_154 + 0x14) = 0
00437117        *(eax_154 + 0x10) = 0
0043711a        void* eax_155
0043711a        eax_155.b = *ecx_138
0043711a        eax_155:1.b = *(ecx_138 + 1)
0043711a        eax_155:2.b = *(ecx_138 + 2)
0043711a        eax_155:3.b = *(ecx_138 + 3)
00437123        *(eax_155 + 0x10) = *(esi_11 + 0x3bfad8)
00437128        *(eax_155 + 0x14) = *(esi_11 + 0x3bfadc)
0043712e        *(eax_155 + 0x18) = *(esi_11 + 0x3bfae0)
00437131        ecx_138 = &ecx_138[1]
00437134        k_1 = k_2
00437134        k_2 -= 1
00437135        do while (k_1 != 1)
0043713c        cond:12_1 = var_30_1 + 1 s< 8
0043713f        var_30_1 += 1
00437143        do while (cond:12_1)
0043714d        level_segment_count = game
00437159        completion_row_start = completion_row_start_2 + 1
0043715a        level_segment_count_2 = &level_segment_count_2->_pad_00[1]
00437160        completion_row_start_2 = completion_row_start
00437164        i_5 = completion_row_start
00437166        ebp_1 = level_segment_count
00437168        do while (completion_row_start s< level_segment_count->runtime_row_count)
0043717a        if (ebp_1->level_mode != 3 || var_42 == 0)
0043717c        var_2c += 1
00437183        do while (i_5 s< ebp_1->runtime_row_count)
00437190        return
