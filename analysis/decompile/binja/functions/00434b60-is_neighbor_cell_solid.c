/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_neighbor_cell_solid @ 0x434b60 */

00434b6a        int32_t eax = get_track_cell_row_index(cell)
00434b76        int32_t ecx_2 = cell->lane_and_flags & 7
00434b7f        if (ecx_2 + lane_offset u< 8)
00434b85        eax += row_offset
00434b8e        if (eax s>= 0 && eax s< game->runtime_row_count)
00434b9e        int32_t eax_3 = (ecx_2 + (eax << 3) + lane_offset) * 0x15
00434ba1        int32_t ecx_5 = 0
00434ba3        ecx_5.b = (&game->runtime_cells[0][0].tile_id)[eax_3 << 2]
00434bcf        if (is_sub_loc_empty(&game->runtime_cells + (eax_3 << 2)).b == 0 && ecx_5 != 0 && ecx_5 != 0x23 && ecx_5 != 0x1c && ecx_5 != 0x16)
00434bd2        int32_t eax_5
00434bd2        eax_5.b = 1
00434bd5        return 1
00434bd9        int32_t eax_6
00434bd9        eax_6.b = 0
00434bdc        return 0
