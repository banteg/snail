/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_sub_lazer_projectile @ 0x439bc0 */

00439bc6        int32_t eax = get_track_cell_row_index(cell)
00439bcb        uint8_t tile_id = cell->tile_id
00439bdb        if (tile_id == 0x1d || tile_id == 0x1e)
00439be1        char* game_base_1 = g_game_base
00439bed        int32_t eax_1 = eax * 0x3d
00439bfa        void* eax_2 = &game_base_1[eax_1 << 2]
00439c08        if ((game_base_1[(eax_1 << 2) + 0x6410e0] & 8) != 0 && ((*(eax_2 + 0x641194)).w:1.b & 2) != 0)
00439c0a        int16_t ecx_5 = (*(eax_2 + 0x641194)).w
00439c1e        if ((ecx_5:1.b & 2) == 0)
00439c25        report_errorf("List remove")
00439c32        if ((ecx_5.b & 0x40) == 0)
00439c43        void* ecx_6 = *(eax_2 + 0x64119c)
00439c48        if (ecx_6 != 0)
00439c4d        *(ecx_6 + 8) = *(eax_2 + 0x641198)
00439c50        void* ecx_7 = *(eax_2 + 0x641198)
00439c55        if (ecx_7 == 0)
00439c62        *(game_base_1 + 0x5ac) = *(eax_2 + 0x64119c)
00439c5a        *(ecx_7 + 0xc) = *(eax_2 + 0x64119c)
00439c68        *(eax_2 + 0x64119c) = *(game_base_1 + 0x5b0)
00439c6b        *(game_base_1 + 0x5b0) = eax_2 + 0x641190
00439c6e        *(eax_2 + 0x641194) &= 0xfffffdff
00439c39        report_errorf("List remove NEXTBOD")
00439c71        uint16_t list_flags = (cell->bod.list_flags).w
00439c77        if ((list_flags:1.b & 2) != 0)
00439c81        void* ecx_10 = &g_game_base[0x5a8]
00439c87        if ((list_flags.b & 0x40) == 0)
00439c98        struct BodNode* list_next = cell->bod.list_next
00439c9d        if (list_next != 0)
00439ca2        list_next->list_prev = cell->bod.list_prev
00439ca5        struct BodNode* list_prev = cell->bod.list_prev
00439caa        if (list_prev == 0)
00439cb7        *(ecx_10 + 4) = cell->bod.list_next
00439caf        list_prev->list_next = cell->bod.list_next
00439cbd        cell->bod.list_next = *(ecx_10 + 8)
00439cc0        *(ecx_10 + 8) = cell
00439cc3        cell->bod.list_flags &= 0xfffffdff
00439c8e        report_errorf("List remove NEXTBOD")
00439cc6        struct FringeObject** esi_1 = &cell->fringe_front
00439cc9        int32_t i_1 = 4
00439d45        int32_t i
00439cce        struct FringeObject* fringe_front = (esi_1 - 0x44)->fringe_front
00439cda        if (fringe_front != 0 && ((fringe_front->bod.list_flags).w:1.b & 2) != 0)
00439ce2        void* edx_6 = &g_game_base[0x5a8]
00439ce8        uint16_t list_flags_1 = (fringe_front->bod.list_flags).w
00439cee        if ((list_flags_1:1.b & 2) == 0)
00439cf5        report_errorf("List remove")
00439d02        if ((list_flags_1.b & 0x40) == 0)
00439d13        struct BodNode* list_next_1 = fringe_front->bod.list_next
00439d18        if (list_next_1 != 0)
00439d1d        list_next_1->list_prev = fringe_front->bod.list_prev
00439d20        struct BodNode* list_prev_1 = fringe_front->bod.list_prev
00439d25        if (list_prev_1 == 0)
00439d32        *(edx_6 + 4) = fringe_front->bod.list_next
00439d2a        list_prev_1->list_next = fringe_front->bod.list_next
00439d38        fringe_front->bod.list_next = *(edx_6 + 8)
00439d3b        *(edx_6 + 8) = fringe_front
00439d3e        fringe_front->bod.list_flags &= 0xfffffdff
00439d09        report_errorf("List remove NEXTBOD")
00439d41        esi_1 = &esi_1[1]
00439d44        i = i_1
00439d44        i_1 -= 1
00439d45        do while (i != 1)
00439d4b        return
