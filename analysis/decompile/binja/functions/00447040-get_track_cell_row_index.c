/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_track_cell_row_index @ 0x447040 */

00447069        int32_t eax_4
00447069        int32_t edx_2
00447069        edx_2:eax_4 = muls.dp.d(0x30c30c31, cell - (cell->lane_bits & 7) * 0x54 - data_4df904 - 0x4340e0)
0044706d        int32_t eax_6 = edx_2 s>> 4
00447077        int32_t eax_8
00447077        int32_t edx_3
00447077        edx_3:eax_8 = sx.q(eax_6 + (eax_6 u>> 0x1f))
00447080        return (eax_8 + (edx_3 & 7)) s>> 3
