/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_garbage_hazard @ 0x43f130 */

0043f133        slot->state = 0
0043f142        struct FrameBodList* ecx = &g_game_base->active_bod_list
0043f148        uint16_t list_flags = (slot->list_flags).w
0043f14e        if ((list_flags:1.b & 2) == 0)
0043f155        report_errorf("List remove")
0043f161        if ((list_flags.b & 0x40) == 0)
0043f172        struct GarbageHazardSlot* list_next = slot->list_next
0043f177        if (list_next != 0)
0043f17c        list_next->list_prev = slot->list_prev
0043f17f        struct GarbageHazardSlot* list_prev = slot->list_prev
0043f184        if (list_prev == 0)
0043f191        ecx->first = slot->list_next
0043f189        list_prev->list_next = slot->list_next
0043f197        slot->list_next = ecx->free_top
0043f19a        ecx->free_top = slot
0043f19d        uint32_t list_flags_1 = slot->list_flags
0043f1a0        list_flags_1:1.b &= 0xfd
0043f1a3        slot->list_flags = list_flags_1
0043f168        report_errorf("List remove NEXTBOD")
0043f1ac        kill_sprite(slot->sprite)
0043f1b1        struct SubgameRuntime* owner_game = slot->owner_game
0043f1b7        struct GarbageHazardSlot* active_head = owner_game->garbage_hazards.active_head
0043f1bf        if (active_head == slot)
0043f1c1        struct GarbageHazardSlot* next_active = slot->next_active
0043f1c8        owner_game->garbage_hazards.active_head = next_active
0043f1ce        return next_active
0043f1d1        if (active_head != 0)
0043f1d3        while (true)
0043f1d3        struct GarbageHazardSlot* next_active_1 = active_head->next_active
0043f1db        if (next_active_1 == slot)
0043f1eb        active_head->next_active = slot->next_active
0043f1f1        slot->next_active = nullptr
0043f1f1        break
0043f1dd        active_head = next_active_1
0043f1e1        if (active_head == 0)
0043f1e4        return active_head
0043f1fc        return active_head
