/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: activate_landscape_entry @ 0x418870 */

00418878        int32_t level_mode = g_game_base->subgame.level_mode
00418886        char flip
00418886        if (level_mode == 7)
00418888        flip = 0
00418892        if (level_mode != 1)
004188cb        flip = g_runtime_config.landscape_backdrop_variant_selector.b & 1
004188a1        long double x87_r7_2 = float.t(next_math_random_value()) * fconvert.t(3.05175781e-05f)
004188a7        long double temp1_1 = fconvert.t(0.5f)
004188a7        x87_r7_2 - temp1_1
004188b2        if ((((x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
004188bb        flip = 1
004188b4        flip = 0
004188d3        int32_t i = 0
004188d5        int32_t i_1 = 0
004188df        void* edi = manager + script_index * 0x124
004188e2        uint32_t* esi_1 = &manager->active_entries[0].bod.bod.bod.list_flags
004188ec        if (*(edi + 0x6b0) != 0xffffffff)
0041890a        struct BodBase* eax_4 = &g_game_base->subgame.landscape_slice_list_head
00418915        if ((((esi_1 - 4)->active_entries[0].bod.bod.bod.list_flags).w:1.b & 2) == 0)
00418926        (esi_1 - 4)->active_entries[0].bod.bod.bod.list_prev = eax_4
0041892f        (esi_1 - 4)->active_entries[0].bod.bod.bod.list_next = eax_4->bod.list_next
00418932        eax_4->bod.list_next = &esi_1[-1]
00418935        struct BodNode* list_next = (esi_1 - 4)->active_entries[0].bod.bod.bod.list_next
0041893a        if (list_next != 0)
0041893c        list_next->list_prev = &esi_1[-1]
0041893f        uint32_t list_flags = (esi_1 - 4)->active_entries[0].bod.bod.bod.list_flags
00418941        list_flags:1.b |= 2
00418944        (esi_1 - 4)->active_entries[0].bod.bod.bod.list_flags = list_flags
0041891c        report_errorf("List ADDafter")
00418946        (esi_1 - 4)->active_entries[0].state = 1
0041894d        uint32_t list_flags_1 = (esi_1 - 4)->active_entries[0].bod.bod.bod.list_flags
0041894f        list_flags_1.b |= 0x20
00418951        (esi_1 - 4)->active_entries[0].bod.bod.bod.list_flags = list_flags_1
00418972        set_bod_object(&esi_1[-1], g_game_base->directx_loader.cached_x_mesh_slots[*(edi + 0x6b0)].object)
00418977        struct Object* object = (esi_1 - 4)->active_entries[0].bod.bod.object
00418989        (esi_1 - 4)->active_entries[0].repeat_z_span = fconvert.s(fconvert.t(object->bounds_max.z) - fconvert.t(object->bounds_min.z))
0041898f        set_matrix_identity(&esi_1[0xd])
004189a4        (esi_1 - 4)->active_entries[0].bod.transform.position.z = fconvert.s((float.t(i_1) - fconvert.t(0.5f)) * fconvert.t((esi_1 - 4)->active_entries[0].repeat_z_span))
004189b3        (esi_1 - 4)->active_entries[0].reference_bod = &g_game_base->subgame.player.body
004188f5        (esi_1 - 4)->active_entries[0].bod.bod.bod.list_flags &= 0xffffffdf
004188fa        set_bod_object(&esi_1[-1], nullptr)
004189b9        i += 1
004189ba        esi_1 = &esi_1[0x24]
004189c3        i_1 = i
004189c7        do while (i s< 0xa)
004189e5        change_backdrop(&g_game_base->backdrop, edi + 0x5a4, flip)
004189f8        set_border_justify_centre(&g_game_base->border_manager, 0f)
00418a08        struct FrameColor4f* eax_9 = &g_game_base->fog_color
00418a0d        eax_9->r = *(edi + 0x6b4)
00418a12        eax_9->g = *(edi + 0x6b8)
00418a18        eax_9->b = *(edi + 0x6bc)
00418a20        eax_9->a = *(edi + 0x6c0)
00418a27        return
