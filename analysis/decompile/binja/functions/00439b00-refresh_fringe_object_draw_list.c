/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: refresh_fringe_object_draw_list @ 0x439b00 */

00439b17        struct tColour out
00439b17        struct tColour* eax = get_track_skirt_color(&g_game_base->subgame, &out)
00439b21        long double x87_r7 = fconvert.t(fringe->bod.position.z)
00439b24        fringe->bod.color.r = eax->r
00439b29        fringe->bod.color.g = eax->g
00439b2f        fringe->bod.color.b = eax->b
00439b35        fringe->bod.color.a = eax->a
00439b38        struct GameRoot* game_base_1 = g_game_base
00439b3e        long double temp0 = fconvert.t(game_base_1->subgame.player.interaction_max_z)
00439b3e        x87_r7 - temp0
00439b49        if ((((x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe):1.b & 1) == 0)
00439b49        return
00439b4b        uint16_t list_flags = (fringe->bod.bod.list_flags).w
00439b57        if ((list_flags:1.b & 2) == 0)
00439b5e        report_errorf("List remove")
00439b6a        return
00439b6d        if ((list_flags.b & 0x40) != 0)
00439b74        report_errorf("List remove NEXTBOD")
00439b80        return
00439b81        struct BodNode* list_next = fringe->bod.bod.list_next
00439b86        if (list_next != 0)
00439b8b        list_next->list_prev = fringe->bod.bod.list_prev
00439b8e        struct BodNode* list_prev = fringe->bod.bod.list_prev
00439b93        if (list_prev == 0)
00439ba0        game_base_1->active_bod_list.first = fringe->bod.bod.list_next
00439b98        list_prev->list_next = fringe->bod.bod.list_next
00439ba6        fringe->bod.bod.list_next = game_base_1->active_bod_list.free_top
00439ba9        game_base_1->active_bod_list.free_top = fringe
00439bac        uint32_t list_flags_1 = fringe->bod.bod.list_flags
00439baf        list_flags_1:1.b &= 0xfd
00439bb2        fringe->bod.bod.list_flags = list_flags_1
00439bb9        return
