/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_active_bod @ 0x433e80 */

00433e83        long double x87_r7 = fconvert.t(slot->cache_row_base) + fconvert.t(24f)
00433e89        struct GameRoot* game_base_1 = g_game_base
00433e8f        long double temp0 = fconvert.t(game_base_1->subgame.player.interaction_max_z)
00433e8f        x87_r7 - temp0
00433e9a        if ((((x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe):1.b & 1) == 0)
00433e9a        return
00433e9c        uint16_t list_flags = (slot->bod.bod.list_flags).w
00433ea8        if ((list_flags:1.b & 2) == 0)
00433eaf        report_errorf("List remove")
00433eb7        return
00433eba        if ((list_flags.b & 0x40) != 0)
00433ec1        report_errorf("List remove NEXTBOD")
00433ec9        return
00433eca        struct BodNode* list_next = slot->bod.bod.list_next
00433ed0        if (list_next != 0)
00433ed5        list_next->list_prev = slot->bod.bod.list_prev
00433ed8        struct BodNode* list_prev = slot->bod.bod.list_prev
00433edd        if (list_prev != 0)
00433ee2        list_prev->list_next = slot->bod.bod.list_next
00433ee8        slot->bod.bod.list_next = game_base_1->active_bod_list.free_top
00433eeb        game_base_1->active_bod_list.free_top = slot
00433eee        uint32_t list_flags_1 = slot->bod.bod.list_flags
00433ef2        list_flags_1:1.b &= 0xfd
00433ef5        slot->bod.bod.list_flags = list_flags_1
00433ef8        return
00433efd        game_base_1->active_bod_list.first = slot->bod.bod.list_next
00433f03        slot->bod.bod.list_next = game_base_1->active_bod_list.free_top
00433f06        game_base_1->active_bod_list.free_top = slot
00433f09        uint32_t list_flags_2 = slot->bod.bod.list_flags
00433f0c        list_flags_2:1.b &= 0xfd
00433f0f        slot->bod.bod.list_flags = list_flags_2
00433f12        return
