/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_render_cache_rows @ 0x433b30 */

00433b36        struct GameRoot* game_base_1 = g_game_base
00433b42        long double x87_r7_1 = fconvert.t(game_base_1->subgame.player.body.transform.position.z) + fconvert.t(46f)
00433b48        long double temp0 = fconvert.t(manager->next_cache_row_z)
00433b48        x87_r7_1 - temp0
00433b53        if ((((x87_r7_1 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00433b53        return
00433e73        long double x87_r6_2
00433e73        long double x87_r7_3
00433b74        int32_t eax_4 = manager->next_cache_row_index * 0x4b
00433b87        if ((0x200 & (&manager->slots[0][4].bod.bod.list_flags)[eax_4]) == 0)
00433b98        (&manager->slots[0][4] + (eax_4 << 2))->bod.bod.list_prev = &game_base_1->subgame.fringe_attachment_list_head.bod
00433b9e        (&manager->slots[0][4] + (eax_4 << 2))->bod.bod.list_next = game_base_1->subgame.fringe_attachment_list_head.bod.list_next
00433ba1        game_base_1->subgame.fringe_attachment_list_head.bod.list_next = &manager->slots[0][4] + (eax_4 << 2)
00433ba4        struct BodNode* list_next = (&manager->slots[0][4] + (eax_4 << 2))->bod.bod.list_next
00433ba9        if (list_next != 0)
00433bab        list_next->list_prev = &manager->slots[0][4] + (eax_4 << 2)
00433bae        (&manager->slots[0][4] + (eax_4 << 2))->bod.bod.list_flags |= 0x200
00433b8e        report_errorf("List ADDafter")
00433bd2        __builtin_memset(&manager->slots[manager->next_cache_row_index][4].bod.position, 0, 0xc)
00433be0        struct tColour skirt_color_out
00433be0        struct tColour* skirt_color = get_track_skirt_color(&g_game_base->subgame, &skirt_color_out)
00433bee        int32_t ecx_3 = manager->next_cache_row_index * 0xf
00433bfd        (&manager->slots[0][4].bod.color + ecx_3 * 0x14)->r = skirt_color->r
00433c02        (&manager->slots[0][4].bod.color + ecx_3 * 0x14)->g = skirt_color->g
00433c08        (&manager->slots[0][4].bod.color + ecx_3 * 0x14)->b = skirt_color->b
00433c0e        (&manager->slots[0][4].bod.color + ecx_3 * 0x14)->a = skirt_color->a
00433c20        struct BodNode* floor_active_list = &g_game_base->subgame.track_body_list_head
00433c29        int32_t edx_4 = manager->next_cache_row_index * 0x4b
00433c36        if ((0x200 & (&manager->slots[0][0].bod.bod.list_flags)[edx_4]) == 0)
00433c47        (&manager->slots + (edx_4 << 2))->bod.bod.list_prev = floor_active_list
00433c4d        (&manager->slots + (edx_4 << 2))->bod.bod.list_next = floor_active_list->list_next
00433c50        floor_active_list->list_next = &manager->slots + (edx_4 << 2)
00433c53        struct BodNode* list_next_1 = (&manager->slots + (edx_4 << 2))->bod.bod.list_next
00433c58        if (list_next_1 != 0)
00433c5a        list_next_1->list_prev = &manager->slots + (edx_4 << 2)
00433c5d        (&manager->slots + (edx_4 << 2))->bod.bod.list_flags |= 0x200
00433c3d        report_errorf("List ADDafter")
00433c79        __builtin_memset(&manager->slots[manager->next_cache_row_index][0].bod.position, 0, 0xc)
00433c91        set_color_white(&manager->slots[manager->next_cache_row_index][0].bod.color)
00433ca5        struct BodNode* slide_active_list = &g_game_base->subgame.track_body_list_head
00433cae        int32_t eax_23 = manager->next_cache_row_index * 0x4b
00433cc1        if ((0x200 & (&manager->slots[0][1].bod.bod.list_flags)[eax_23]) == 0)
00433cd2        (&manager->slots[0][1] + (eax_23 << 2))->bod.bod.list_prev = slide_active_list
00433cd8        (&manager->slots[0][1] + (eax_23 << 2))->bod.bod.list_next = slide_active_list->list_next
00433cdb        slide_active_list->list_next = &manager->slots[0][1] + (eax_23 << 2)
00433cde        struct BodNode* list_next_2 = (&manager->slots[0][1] + (eax_23 << 2))->bod.bod.list_next
00433ce3        if (list_next_2 != 0)
00433ce5        list_next_2->list_prev = &manager->slots[0][1] + (eax_23 << 2)
00433ce8        (&manager->slots[0][1] + (eax_23 << 2))->bod.bod.list_flags |= 0x200
00433cc8        report_errorf("List ADDafter")
00433d07        __builtin_memset(&manager->slots[manager->next_cache_row_index][1].bod.position, 0, 0xc)
00433d1f        set_color_white(&manager->slots[manager->next_cache_row_index][1].bod.color)
00433d33        struct BodNode* ramp_active_list = &g_game_base->subgame.track_body_list_head
00433d3c        int32_t eax_34 = manager->next_cache_row_index * 0x4b
00433d4f        if ((0x200 & (&manager->slots[0][3].bod.bod.list_flags)[eax_34]) == 0)
00433d60        (&manager->slots[0][3] + (eax_34 << 2))->bod.bod.list_prev = ramp_active_list
00433d66        (&manager->slots[0][3] + (eax_34 << 2))->bod.bod.list_next = ramp_active_list->list_next
00433d69        ramp_active_list->list_next = &manager->slots[0][3] + (eax_34 << 2)
00433d6c        struct BodNode* list_next_3 = (&manager->slots[0][3] + (eax_34 << 2))->bod.bod.list_next
00433d71        if (list_next_3 != 0)
00433d73        list_next_3->list_prev = &manager->slots[0][3] + (eax_34 << 2)
00433d76        (&manager->slots[0][3] + (eax_34 << 2))->bod.bod.list_flags |= 0x200
00433d56        report_errorf("List ADDafter")
00433d95        __builtin_memset(&manager->slots[manager->next_cache_row_index][3].bod.position, 0, 0xc)
00433dad        set_color_white(&manager->slots[manager->next_cache_row_index][3].bod.color)
00433dc1        struct BodNode* warning_active_list = &g_game_base->subgame.track_body_list_head
00433dca        int32_t eax_45 = manager->next_cache_row_index * 0x4b
00433ddd        if ((0x200 & (&manager->slots[0][2].bod.bod.list_flags)[eax_45]) == 0)
00433dee        (&manager->slots[0][2] + (eax_45 << 2))->bod.bod.list_prev = warning_active_list
00433df4        (&manager->slots[0][2] + (eax_45 << 2))->bod.bod.list_next = warning_active_list->list_next
00433df7        warning_active_list->list_next = &manager->slots[0][2] + (eax_45 << 2)
00433dfa        struct BodNode* list_next_4 = (&manager->slots[0][2] + (eax_45 << 2))->bod.bod.list_next
00433dff        if (list_next_4 != 0)
00433e01        list_next_4->list_prev = &manager->slots[0][2] + (eax_45 << 2)
00433e04        (&manager->slots[0][2] + (eax_45 << 2))->bod.bod.list_flags |= 0x200
00433de4        report_errorf("List ADDafter")
00433e23        __builtin_memset(&manager->slots[manager->next_cache_row_index][2].bod.position, 0, 0xc)
00433e3b        set_color_white(&manager->slots[manager->next_cache_row_index][2].bod.color)
00433e46        x87_r7_3 = fconvert.t(manager->next_cache_row_z) + fconvert.t(24f)
00433e4c        manager->next_cache_row_index += 1
00433e52        manager->next_cache_row_z = fconvert.s(x87_r7_3)
00433e58        game_base_1 = g_game_base
00433e64        x87_r6_2 = fconvert.t(game_base_1->subgame.player.body.transform.position.z) + fconvert.t(46f)
00433e6a        x87_r6_2 - x87_r7_3
00433e73        do while ((((x87_r6_2 < x87_r7_3 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_2, x87_r7_3) ? 1 : 0) << 0xa | (x87_r6_2 == x87_r7_3 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00433e7f        return
