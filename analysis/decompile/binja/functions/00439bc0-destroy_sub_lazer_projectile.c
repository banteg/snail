/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_sub_lazer_projectile @ 0x439bc0 */

00439bc6        int32_t eax = get_track_cell_row_index(arg1)
00439bcb        uint8_t tile_id = arg1->tile_id
00439bdb        if (tile_id == 0x1d || tile_id == 0x1e)
00439be1        void* edx_1 = data_4df904
00439bed        int32_t eax_1 = eax * 0x3d
00439bfa        void* eax_2 = edx_1 + (eax_1 << 2)
00439c08        if ((*(edx_1 + (eax_1 << 2) + 0x6410e0) & 8) != 0 && ((*(eax_2 + 0x641194)).w:1.b & 2) != 0)
00439c0a        int16_t ecx_5 = (*(eax_2 + 0x641194)).w
00439c1e        if ((ecx_5:1.b & 2) == 0)
00439c25        report_errorf("List remove")
00439c32        if ((ecx_5.b & 0x40) == 0)
00439c43        void* ecx_6 = *(eax_2 + 0x64119c)
00439c48        if (ecx_6 != 0)
00439c4d        *(ecx_6 + 8) = *(eax_2 + 0x641198)
00439c50        void* ecx_7 = *(eax_2 + 0x641198)
00439c55        if (ecx_7 == 0)
00439c62        *(edx_1 + 0x5ac) = *(eax_2 + 0x64119c)
00439c5a        *(ecx_7 + 0xc) = *(eax_2 + 0x64119c)
00439c68        *(eax_2 + 0x64119c) = *(edx_1 + 0x5b0)
00439c6b        *(edx_1 + 0x5b0) = eax_2 + 0x641190
00439c6e        *(eax_2 + 0x641194) &= 0xfffffdff
00439c39        report_errorf("List remove NEXTBOD")
00439c71        int16_t list_flags = (arg1->bod.list_flags).w
00439c77        if ((list_flags:1.b & 2) != 0)
00439c81        void* ecx_10 = data_4df904 + 0x5a8
00439c87        if ((list_flags.b & 0x40) == 0)
00439c98        struct BodNode* list_next = arg1->bod.list_next
00439c9d        if (list_next != 0)
00439ca2        list_next->list_prev = arg1->bod.list_prev
00439ca5        struct BodNode* list_prev = arg1->bod.list_prev
00439caa        if (list_prev == 0)
00439cb7        *(ecx_10 + 4) = arg1->bod.list_next
00439caf        list_prev->list_next = arg1->bod.list_next
00439cbd        arg1->bod.list_next = *(ecx_10 + 8)
00439cc0        *(ecx_10 + 8) = arg1
00439cc3        arg1->bod.list_flags &= 0xfffffdff
00439c8e        report_errorf("List remove NEXTBOD")
00439cc6        int32_t* esi_1 = &arg1->fringe_front
00439cc9        int32_t i_1 = 4
00439d45        void* result
00439d45        int32_t i
00439cce        result = *esi_1
00439cda        if (result != 0 && ((*(result + 4)).w:1.b & 2) != 0)
00439ce2        void* edx_7 = data_4df904 + 0x5a8
00439ce8        int16_t ecx_13 = (*(result + 4)).w
00439cee        if ((ecx_13:1.b & 2) == 0)
00439cf5        result = report_errorf("List remove")
00439d02        if ((ecx_13.b & 0x40) == 0)
00439d13        void* ecx_14 = *(result + 0xc)
00439d18        if (ecx_14 != 0)
00439d1d        *(ecx_14 + 8) = *(result + 8)
00439d20        void* ecx_15 = *(result + 8)
00439d25        if (ecx_15 == 0)
00439d32        *(edx_7 + 4) = *(result + 0xc)
00439d2a        *(ecx_15 + 0xc) = *(result + 0xc)
00439d38        *(result + 0xc) = *(edx_7 + 8)
00439d3b        *(edx_7 + 8) = result
00439d3e        *(result + 4) &= 0xfffffdff
00439d09        result = report_errorf("List remove NEXTBOD")
00439d41        esi_1 = &esi_1[1]
00439d44        i = i_1
00439d44        i_1 -= 1
00439d45        do while (i != 1)
00439d4b        return result
