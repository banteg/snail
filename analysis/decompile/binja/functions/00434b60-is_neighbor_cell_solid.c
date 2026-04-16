/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_neighbor_cell_solid @ 0x434b60 */

00434b6a        int32_t result = get_track_cell_row_index(arg2)
00434b76        int32_t ecx_2 = arg2->__offset(0x40).d & 7
00434b7f        if (ecx_2 + arg3 u< 8)
00434b85        result += arg4
00434b8e        if (result s>= 0 && result s< *(arg1 + 0x54))
00434b9e        int32_t eax_2 = (ecx_2 + (result << 3) + arg3) * 0x15
00434ba3        int32_t ecx_5
00434ba3        ecx_5.b = *(arg1 + (eax_2 << 2) + 0x3bfb04)
00434bcf        if (is_open_neighbor_tile_family(arg1 + (eax_2 << 2) + 0x3bfac8).b == 0 && ecx_5 != 0 && ecx_5 != 0x23 && ecx_5 != 0x1c && ecx_5 != 0x16)
00434bd2        result.b = 1
00434bd5        return result
00434bd9        result.b = 0
00434bdc        return result
