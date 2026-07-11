/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: render_game_frame @ 0x40a490 */

0040a49a        struct GameRoot* game_1 = game
0040a49c        int32_t esi = 0
0040a49e        struct GameRoot* game_2 = game_1
0040a4a2        int32_t render_skip_count = game_1->render_skip_count
0040a4aa        if (render_skip_count s> 0)
0040a4ad        game_1->render_skip_count = render_skip_count - 1
0040a4bd        return
0040a4be        reset_render_counters()
0040a4c7        int32_t var_70 = 0
0040a4cb        struct TransformMatrix transform
0040a4cb        set_matrix_identity(&transform)
0040a4d0        int32_t ebx = 0
0040a4d5        int32_t i_7
0040a4d5        __builtin_memset(&i_7, 0xff, 0x14)
0040a4d9        int32_t var_74 = 0
0040a4e1        uint32_t* eax_1 = &game_1->render_camera_slots[0].flags
0040a4f3        int32_t i_8 = 5
0040a502        int32_t i
0040a4fb        if (((eax_1 - 0x5bc)->:0x5bc.b & 1) != 0)
0040a4fd        ebx += 1
0040a4fe        eax_1 = &eax_1[0xa]
0040a501        i = i_8
0040a501        i_8 -= 1
0040a502        do while (i != 1)
0040a50a        int32_t* eax_2 = &game_1->render_camera_slots[0].sort_key
0040a516        int32_t var_74_1 = ebx
0040a520        int32_t i_1 = 0
0040a522        game_1->render_camera_slots[1].flags = (game_1->render_camera_slots[1].flags & 0xffffff) | 0x2000000
0040a528        int32_t i_6 = 0
0040a52c        int32_t* var_80 = eax_2
0040a534        if (((eax_2 - 0x5b8)->:0x5bc.b & 1) != 0)
0040a538        if (esi != 0)
0040a545        int32_t edx_3 = 0
0040a549        if (esi s> 0)
0040a54b        int32_t sort_key = (eax_2 - 0x5b8)->render_camera_slots[0].sort_key
0040a54d        int32_t eax_3 = 0
0040a561        if (sort_key s> game_1->render_camera_slots[*(&i_7 + eax_3)].sort_key)
0040a566        if (eax_3 s<= 0xc)
0040a56d        int32_t var_44
0040a56d        int32_t* eax_4 = &var_44
0040a571        int32_t j_1 = 4 - edx_3
0040a57c        int32_t j
0040a576        *eax_4 = eax_4[-1]
0040a578        eax_4 = &eax_4[-1]
0040a57b        j = j_1
0040a57b        j_1 -= 1
0040a57c        do while (j != 1)
0040a582        esi += 1
0040a583        int32_t __saved_edi
0040a583        *(&__saved_edi + eax_3 + 0x3c) = i_6
0040a585        edx_3 = esi
0040a587        eax_3 = esi << 2
0040a58e        edx_3 += 1
0040a58f        eax_3 += 4
0040a594        do while (edx_3 s< esi)
0040a596        eax_2 = var_80
0040a59a        ebx = var_74_1
0040a59e        i_1 = i_6
0040a53a        i_7 = i_1
0040a53e        esi = 1
0040a5a2        i_1 += 1
0040a5a3        eax_2 = &eax_2[0xa]
0040a5a9        i_6 = i_1
0040a5ad        var_80 = eax_2
0040a5b1        do while (i_1 s< 5)
0040a5bb        int32_t i_10 = 0
0040a5bf        int32_t var_7c = 0
0040a5c3        if (ebx s<= 0)
0040a5c3        return
0040a5cd        int32_t var_68_1 = ebx
0040a5d1        int32_t* var_74_2 = &i_7
0040aa2e        bool cond:2_1
0040a5d5        int32_t* edx_5 = var_74_2
0040a5d9        int32_t ebx_2 = *edx_5
0040a5db        int32_t eax_6 = ebx_2 * 5
0040a5de        void* ebp_1 = &game_1->unknown_000000[eax_6 << 3]
0040a5ea        if (((&game_1->render_camera_slots[0].flags)[eax_6 * 2].b & 1) != 0)
0040a5f0        void* eax_8 = *(ebp_1 + 0x5d4)
0040a5f6        edx_5.b = *(ebp_1 + 0x5d8)
0040a609        int32_t* esi_1 = &game_1->unknown_000000[(ebx_2 * 5 + 0xb9) << 3]
0040a637        int16_t x87control_1 = render_camera(*(ebp_1 + 0x5c0), *(ebp_1 + 0x5c4), *esi_1, *(ebp_1 + 0x5cc), *(eax_8 + 0xc0), eax_8 + 0x38, eax_8 + 0x80, edx_5.b, 0)
0040a647        if ((*(ebp_1 + 0x5bc) & 2) == 0)
0040a64d        struct FrameBodBase* i_2 = game_1->active_bod_list.first
0040a653        i_10 = 0
0040a65d        if (i_2 != 0)
0040a663        struct FrameBodBase** edi = &data_4dfb10
0040a668        i_2->bod
0040a67b        uint32_t list_flags = i_2->bod.list_flags
0040a69c        if ((list_flags.b & 2) != 0 && (list_flags.b & 0x20) != 0 && (*(ebp_1 + 0x5bc) & list_flags & 0xff000000) != 0)
0040a6a4        if ((list_flags.b & 0x80) != 0)
0040a6aa        *edi = i_2
0040a6ad        edi = &edi[1]
0040a6b0        i_10 += 1
0040a6bf        var_7c += 1
0040a6c3        if (((i_2->bod.list_flags).w:1.b & 8) != 0)
0040a6c5        void* object = i_2->object
0040a6cb        void* edx_10
0040a6cb        edx_10.b = *(object + 0xbc)
0040a6cb        edx_10:1.b = *(object + 0xbd)
0040a6cb        edx_10:2.b = *(object + 0xbe)
0040a6cb        edx_10:3.b = *(object + 0xbf)
0040a6d4        *(edx_10 + 0xc) = *(i_2->__offset(0x78).d + 4)
0040a6dd        int32_t render_arg_1c
0040a6dd        float render_arg_20
0040a6dd        struct Color4f* color
0040a6dd        char after_sprites
0040a6dd        void* __offset(FrameBodBase, 0x38) matrix_1
0040a6dd        if (((i_2->bod.list_flags).w:1.b & 4) == 0)
0040a6fe        transform.position.x = i_2->position.x
0040a70a        transform.position.y = i_2->position.y
0040a714        transform.position.z = i_2->position.z
0040a726        after_sprites = is_bod_after_sprites(i_2)
0040a72a        color = &i_2->color
0040a72b        render_arg_20 = i_2->render_arg_20
0040a72c        render_arg_1c = i_2->render_arg_1c
0040a72d        matrix_1 = &transform
0040a6ec        after_sprites = is_bod_after_sprites(i_2)
0040a6f0        color = &i_2->color
0040a6f1        render_arg_20 = i_2->render_arg_20
0040a6f2        render_arg_1c = i_2->render_arg_1c
0040a6f3        matrix_1 = &i_2[1]
0040a736        x87control_1 = render_object(i_2->object, matrix_1, render_arg_1c, render_arg_20, color, after_sprites)
0040a73e        i_2 = i_2->bod.list_next
0040a743        do while (i_2 != 0)
0040a749        game_1 = game_2
0040a74d        void* i_3 = g_sprite_active_heads[ebx_2]
0040a754        struct SpriteDepthNode* var_6c_1 = &g_sprite_depth_nodes
0040a75c        begin_sprite_depth_render_state()
0040a763        while (i_3 != 0)
0040a774        var_70 += 1
0040a778        int32_t eax_25 = *(i_3 + 4)
0040a783        if ((*(ebp_1 + 0x5bc) & eax_25 & 0xff000000) == 0)
0040a8a4        report_errorf("Loose Sprite scene viewport")
0040a79c        if ((eax_25.b & 1) != 0 && (eax_25.b & 0x40) != 0 && (eax_25:1.b & 2) == 0)
0040a7ae        int32_t esi_3 = *(ebp_1 + 0x5d4) + 0x80
0040a7b8        float var_60 = *(i_3 + 0x48)
0040a7bc        int32_t ecx_18 = *(i_3 + 0x4c)
0040a7c8        float edx_16 = *(i_3 + 0x50)
0040a7cf        void var_d0
0040a7cf        __builtin_memcpy(&var_d0, esi_3, 0x40)
0040a7d5        multiply_vector_by_matrix(&var_60)
0040a7e0        var_60 = fconvert.s(fneg(fconvert.t(var_60)))
0040a7e8        long double x87_r7_4 = fneg(fconvert.t(edx_16))
0040a7ea        float var_58_2 = fconvert.s(x87_r7_4)
0040a7f6        long double x87_r7_7 = fneg(x87_r7_4) * fconvert.t(4.19672108f) + fconvert.t(*(i_3 + 0x98))
0040a7fe        int32_t eax_27
0040a7fe        eax_27, x87control_1 = ftol(x87control_1, x87_r7_7)
0040a803        int32_t esi_4 = eax_27
0040a80b        if (esi_4 s>= 0x100)
0040a80d        esi_4 = 0xff
0040a820        label_40a820:
0040a820        struct SpriteDepthNode** ecx_20 = g_sprite_depth_buckets[esi_4]
0040a827        struct SpriteDepthNode* edx_17 = var_6c_1
0040a82e        var_6c_1 = &var_6c_1[1]
0040a832        if (ecx_20 == 0)
0040a86d        g_sprite_depth_buckets[esi_4] = edx_17
0040a874        label_40a874:
0040a874        edx_17->next = 0
0040a834        struct SpriteDepthNode** edi_1 = nullptr
0040a838        if (ecx_20 == 0)
0040a854        label_40a854:
0040a854        *edi_1 = edx_17
0040a874        label_40a874_1:
0040a874        edx_17->next = 0
0040a83a        while (true)
0040a83a        long double temp4_1 = fconvert.t(ecx_20[4])
0040a83a        x87_r7_7 - temp4_1
0040a842        if ((((x87_r7_7 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp4_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp4_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
0040a842        break
0040a844        edi_1 = ecx_20
0040a846        ecx_20.b = *ecx_20
0040a846        ecx_20:1.b = *(ecx_20 + 1)
0040a846        ecx_20:2.b = *(ecx_20 + 2)
0040a846        ecx_20:3.b = *(ecx_20 + 3)
0040a84a        if (ecx_20 == 0)
0040a84c        *edi_1 = edx_17
0040a84e        goto label_40a874_1
0040a852        if (ecx_20 == 0)
0040a852        goto label_40a854
0040a85a        if (edi_1 == 0)
0040a862        edx_17->next = ecx_20
0040a864        g_sprite_depth_buckets[esi_4] = edx_17
0040a85c        *edi_1 = edx_17
0040a85e        edx_17->next = ecx_20
0040a87a        float ecx_21 = var_60
0040a881        edx_17->depth_key = fconvert.s(x87_r7_7)
0040a884        edx_17->position.x = ecx_21
0040a88a        edx_17->sprite = i_3
0040a88d        edx_17->position.y = ecx_18
0040a894        edx_17->position.z = var_58_2
0040a897        *(i_3 + 0x14) = esi_4
0040a89a        *(i_3 + 0x18) = fconvert.s(x87_r7_7)
0040a816        if (esi_4 s>= 0)
0040a816        goto label_40a820
0040a8b0        game_1 = game_2
0040a8b4        i_3 = *(i_3 + 0xc)
0040a8bf        struct SpriteDepthNode** i_4 = &g_sprite_depth_buckets[0xff]
0040a8c4        struct SpriteDepthNode* next = *i_4
0040a8c8        if (next != 0)
0040a8ca        struct Sprite* sprite = next->sprite
0040a8d1        if ((sprite->flags.b & 2) != 0)
0040a8e0        update_sprite_facing_angle(sprite, *(ebp_1 + 0x5d4) + 0x80)
0040a8ed        draw_sprite_quad(&next->position, next->sprite)
0040a8f2        next = next->next
0040a8f9        do while (next != 0)
0040a8fb        *i_4 = next
0040a8fd        i_4 -= 4
0040a906        do while (i_4 s>= &g_sprite_depth_buckets)
0040a908        end_sprite_depth_render_state()
0040a90d        begin_overlay_render_state()
0040a919        draw_font_text_queue(*(ebp_1 + 0x5bc))
0040a921        end_overlay_render_state()
0040a939        if ((*(ebp_1 + 0x5bc) & 2) == 0 && i_10 != 0)
0040a93f        void* eax_34 = *(ebp_1 + 0x5d4)
0040a971        float edx_23
0040a971        edx_23.b = *esi_1
0040a971        edx_23:1.b = *(esi_1 + 1)
0040a971        edx_23:2.b = *(esi_1 + 2)
0040a971        edx_23:3.b = *(esi_1 + 3)
0040a97c        render_camera(*(ebp_1 + 0x5c0), *(ebp_1 + 0x5c4), edx_23, *(ebp_1 + 0x5cc), *(eax_34 + 0xc0), eax_34 + 0x38, eax_34 + 0x80, *(ebp_1 + 0x5d8), 1)
0040a989        int32_t i_9 = i_10
0040a990        int32_t* edi_2 = (i_10 << 2) + &data_4dfb10
0040a997        i_10 = 0
0040a99f        var_7c += i_9
0040aa14        int32_t i_5
0040a9a3        void* eax_39 = edi_2[-1]
0040a9a6        edi_2 -= 4
0040a9af        int32_t texture_scroll_bits
0040a9af        float texture_v
0040a9af        struct Color4f* color_1
0040a9af        char after_sprites_1
0040a9af        struct TransformMatrix* matrix
0040a9af        void* esi_5
0040a9af        if (((*(eax_39 + 4)).w:1.b & 4) == 0)
0040a9cf        esi_5 = *edi_2
0040a9d3        transform.position.x = *(eax_39 + 0x10)
0040a9dd        transform.position.y = *(eax_39 + 0x14)
0040a9e9        transform.position.z = *(eax_39 + 0x18)
0040a9fb        after_sprites_1 = is_bod_after_sprites(esi_5)
0040a9ff        color_1 = esi_5 + 0x28
0040aa00        texture_v = *(esi_5 + 0x20)
0040aa01        texture_scroll_bits = *(esi_5 + 0x1c)
0040aa02        matrix = &transform
0040a9b1        esi_5 = eax_39
0040a9c0        after_sprites_1 = is_bod_after_sprites(esi_5)
0040a9c4        color_1 = esi_5 + 0x28
0040a9c5        texture_v = *(esi_5 + 0x20)
0040a9c6        texture_scroll_bits = *(esi_5 + 0x1c)
0040a9c7        matrix = esi_5 + 0x38
0040aa0b        render_object(*(esi_5 + 0x24), matrix, texture_scroll_bits, texture_v, color_1, after_sprites_1)
0040aa13        i_5 = i_9
0040aa13        i_9 -= 1
0040aa14        do while (i_5 != 1)
0040aa16        game_1 = game_2
0040aa25        cond:2_1 = var_68_1 != 1
0040aa26        var_74_2 = &var_74_2[1]
0040aa2a        var_68_1 -= 1
0040aa2e        do while (cond:2_1)
0040aa43        return
