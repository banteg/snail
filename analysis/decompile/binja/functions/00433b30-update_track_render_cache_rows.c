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
00433b98        (&manager->slots[0][4] + (eax_4 << 2))->list_prev = &game_base_1->subgame.fringe_attachment_list_head
00433b9e        (&manager->slots[0][4] + (eax_4 << 2))->list_next = game_base_1->subgame.fringe_attachment_list_head.bod.list_next
00433ba1        game_base_1->subgame.fringe_attachment_list_head.bod.list_next = &manager->slots[0][4] + (eax_4 << 2)
00433ba4        struct BodNode* list_next = (&manager->slots[0][4] + (eax_4 << 2))->list_next
00433ba9        if (list_next != 0)
00433bab        list_next->list_prev = &manager->slots[0][4] + (eax_4 << 2)
00433bae        (&manager->slots[0][4] + (eax_4 << 2))->list_flags |= 0x200
00433b8e        report_errorf("List ADDafter")
00433bbf        int32_t eax_8 = manager->next_cache_row_index * 0xf
00433bcc        (&manager->slots[0][4].bod.position.z)[eax_8 * 5] = 0
00433bcf        (&manager->slots[0][4].bod.position.y)[eax_8 * 5] = 0
00433bd2        *(&manager->slots[0][4].bod.position + eax_8 * 0x14) = 0
00433be0        struct tColour out
00433be0        struct tColour* eax_11 = get_track_skirt_color(&g_game_base->subgame, &out)
00433bee        int32_t ecx_4 = manager->next_cache_row_index * 0xf
00433bfd        *(&manager->slots[0][4].bod.color + ecx_4 * 0x14) = eax_11->r
00433c02        (&manager->slots[0][4].bod.color.g)[ecx_4 * 5] = eax_11->g
00433c08        (&manager->slots[0][4].bod.color.b)[ecx_4 * 5] = eax_11->b
00433c0e        (&manager->slots[0][4].bod.color.a)[ecx_4 * 5] = eax_11->a
00433c20        struct BodBase* ecx_10 = &g_game_base->subgame.track_body_list_head
00433c29        int32_t edx_5 = manager->next_cache_row_index * 0x4b
00433c36        if ((0x200 & (&manager->slots[0][0].bod.bod.list_flags)[edx_5]) == 0)
00433c47        (&manager->slots + (edx_5 << 2))->list_prev = ecx_10
00433c4d        (&manager->slots + (edx_5 << 2))->list_next = ecx_10->bod.list_next
00433c50        ecx_10->bod.list_next = &manager->slots + (edx_5 << 2)
00433c53        struct BodNode* list_next_1 = (&manager->slots + (edx_5 << 2))->list_next
00433c58        if (list_next_1 != 0)
00433c5a        list_next_1->list_prev = &manager->slots + (edx_5 << 2)
00433c5d        (&manager->slots + (edx_5 << 2))->list_flags |= 0x200
00433c3d        report_errorf("List ADDafter")
00433c69        int32_t eax_19 = manager->next_cache_row_index * 0xf
00433c73        (&manager->slots[0][0].bod.position.z)[eax_19 * 5] = 0
00433c76        (&manager->slots[0][0].bod.position.y)[eax_19 * 5] = 0
00433c79        *(&manager->slots[0][0].bod.position + eax_19 * 0x14) = 0
00433c91        set_color_white(&manager->slots[manager->next_cache_row_index][0].bod.color)
00433ca5        struct BodBase* ecx_13 = &g_game_base->subgame.track_body_list_head
00433cae        int32_t eax_28 = manager->next_cache_row_index * 0x4b
00433cc1        if ((0x200 & (&manager->slots[0][1].bod.bod.list_flags)[eax_28]) == 0)
00433cd2        (&manager->slots[0][1] + (eax_28 << 2))->list_prev = ecx_13
00433cd8        (&manager->slots[0][1] + (eax_28 << 2))->list_next = ecx_13->bod.list_next
00433cdb        ecx_13->bod.list_next = &manager->slots[0][1] + (eax_28 << 2)
00433cde        struct BodNode* list_next_2 = (&manager->slots[0][1] + (eax_28 << 2))->list_next
00433ce3        if (list_next_2 != 0)
00433ce5        list_next_2->list_prev = &manager->slots[0][1] + (eax_28 << 2)
00433ce8        (&manager->slots[0][1] + (eax_28 << 2))->list_flags |= 0x200
00433cc8        report_errorf("List ADDafter")
00433cf4        int32_t eax_32 = manager->next_cache_row_index * 0xf
00433d01        (&manager->slots[0][1].bod.position.z)[eax_32 * 5] = 0
00433d04        (&manager->slots[0][1].bod.position.y)[eax_32 * 5] = 0
00433d07        *(&manager->slots[0][1].bod.position + eax_32 * 0x14) = 0
00433d1f        set_color_white(&manager->slots[manager->next_cache_row_index][1].bod.color)
00433d33        struct BodBase* ecx_16 = &g_game_base->subgame.track_body_list_head
00433d3c        int32_t eax_41 = manager->next_cache_row_index * 0x4b
00433d4f        if ((0x200 & (&manager->slots[0][3].bod.bod.list_flags)[eax_41]) == 0)
00433d60        (&manager->slots[0][3] + (eax_41 << 2))->list_prev = ecx_16
00433d66        (&manager->slots[0][3] + (eax_41 << 2))->list_next = ecx_16->bod.list_next
00433d69        ecx_16->bod.list_next = &manager->slots[0][3] + (eax_41 << 2)
00433d6c        struct BodNode* list_next_3 = (&manager->slots[0][3] + (eax_41 << 2))->list_next
00433d71        if (list_next_3 != 0)
00433d73        list_next_3->list_prev = &manager->slots[0][3] + (eax_41 << 2)
00433d76        (&manager->slots[0][3] + (eax_41 << 2))->list_flags |= 0x200
00433d56        report_errorf("List ADDafter")
00433d82        int32_t eax_45 = manager->next_cache_row_index * 0xf
00433d8f        (&manager->slots[0][3].bod.position.z)[eax_45 * 5] = 0
00433d92        (&manager->slots[0][3].bod.position.y)[eax_45 * 5] = 0
00433d95        *(&manager->slots[0][3].bod.position + eax_45 * 0x14) = 0
00433dad        set_color_white(&manager->slots[manager->next_cache_row_index][3].bod.color)
00433dc1        struct BodBase* ecx_19 = &g_game_base->subgame.track_body_list_head
00433dca        int32_t eax_54 = manager->next_cache_row_index * 0x4b
00433ddd        if ((0x200 & (&manager->slots[0][2].bod.bod.list_flags)[eax_54]) == 0)
00433dee        (&manager->slots[0][2] + (eax_54 << 2))->list_prev = ecx_19
00433df4        (&manager->slots[0][2] + (eax_54 << 2))->list_next = ecx_19->bod.list_next
00433df7        ecx_19->bod.list_next = &manager->slots[0][2] + (eax_54 << 2)
00433dfa        struct BodNode* list_next_4 = (&manager->slots[0][2] + (eax_54 << 2))->list_next
00433dff        if (list_next_4 != 0)
00433e01        list_next_4->list_prev = &manager->slots[0][2] + (eax_54 << 2)
00433e04        (&manager->slots[0][2] + (eax_54 << 2))->list_flags |= 0x200
00433de4        report_errorf("List ADDafter")
00433e10        int32_t eax_58 = manager->next_cache_row_index * 0xf
00433e1d        (&manager->slots[0][2].bod.position.z)[eax_58 * 5] = 0
00433e20        (&manager->slots[0][2].bod.position.y)[eax_58 * 5] = 0
00433e23        *(&manager->slots[0][2].bod.position + eax_58 * 0x14) = 0
00433e3b        set_color_white(&manager->slots[manager->next_cache_row_index][2].bod.color)
00433e46        x87_r7_3 = fconvert.t(manager->next_cache_row_z) + fconvert.t(24f)
00433e4c        manager->next_cache_row_index += 1
00433e52        manager->next_cache_row_z = fconvert.s(x87_r7_3)
00433e58        game_base_1 = g_game_base
00433e64        x87_r6_2 = fconvert.t(game_base_1->subgame.player.body.transform.position.z) + fconvert.t(46f)
00433e6a        x87_r6_2 - x87_r7_3
00433e73        do while ((((x87_r6_2 < x87_r7_3 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_2, x87_r7_3) ? 1 : 0) << 0xa | (x87_r6_2 == x87_r7_3 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00433e7f        return
