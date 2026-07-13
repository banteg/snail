/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: deactivate_sub_lazer_projectile @ 0x441740 */

00441748        void* ecx = &g_game_base[0x5a8]
0044174e        uint16_t list_flags = (slot->bod.list_flags).w
00441754        if ((list_flags:1.b & 2) == 0)
0044175b        report_errorf("List remove")
00441763        slot->state = 0
0044176e        return 0
00441771        if ((list_flags.b & 0x40) != 0)
00441778        report_errorf("List remove NEXTBOD")
00441780        slot->state = 0
0044178b        return 0
0044178c        struct BodNode* list_next = slot->bod.list_next
00441791        if (list_next != 0)
00441796        list_next->list_prev = slot->bod.list_prev
00441799        struct BodNode* list_prev = slot->bod.list_prev
0044179e        if (list_prev == 0)
004417ab        *(ecx + 4) = slot->bod.list_next
004417a3        list_prev->list_next = slot->bod.list_next
004417b1        slot->bod.list_next = *(ecx + 8)
004417b4        *(ecx + 8) = slot
004417b7        uint32_t list_flags_1 = slot->bod.list_flags
004417ba        slot->state = 0
004417c4        list_flags_1:1.b &= 0xfd
004417c7        slot->bod.list_flags = list_flags_1
004417cb        return list_flags_1
