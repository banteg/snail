/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: mark_current_track_pair_with_payload @ 0x43d3d0 */

0043d3d0        struct TrackRowCell* cached_track_pair_cell_a = player->cached_track_pair_cell_a
0043d3dc        int32_t esi
0043d3dc        esi.b = cached_track_pair_cell_a->_pad_00[4]
0043d3dc        esi:1.b = cached_track_pair_cell_a->_pad_00[5]
0043d3dc        esi:2.b = cached_track_pair_cell_a->_pad_00[6]
0043d3dc        esi:3.b = cached_track_pair_cell_a->_pad_00[7]
0043d3df        int32_t esi_1 = esi | 0x40
0043d3e1        cached_track_pair_cell_a->_pad_00[4] = esi_1.b
0043d3e1        cached_track_pair_cell_a->_pad_00[5] = esi_1:1.b
0043d3e1        cached_track_pair_cell_a->_pad_00[6] = esi_1:2.b
0043d3e1        cached_track_pair_cell_a->_pad_00[7] = esi_1:3.b
0043d3e4        struct TrackRowCell* cached_track_pair_cell_b = player->cached_track_pair_cell_b
0043d3ea        int32_t esi_2
0043d3ea        esi_2.b = cached_track_pair_cell_b->_pad_00[4]
0043d3ea        esi_2:1.b = cached_track_pair_cell_b->_pad_00[5]
0043d3ea        esi_2:2.b = cached_track_pair_cell_b->_pad_00[6]
0043d3ea        esi_2:3.b = cached_track_pair_cell_b->_pad_00[7]
0043d3ed        int32_t esi_3 = esi_2 | 0x40
0043d3f3        cached_track_pair_cell_b->_pad_00[4] = esi_3.b
0043d3f3        cached_track_pair_cell_b->_pad_00[5] = esi_3:1.b
0043d3f3        cached_track_pair_cell_b->_pad_00[6] = esi_3:2.b
0043d3f3        cached_track_pair_cell_b->_pad_00[7] = esi_3:3.b
0043d3fd        player->cached_track_pair_cell_a->__offset(0x50).d = payload
0043d400        struct TrackRowCell* cached_track_pair_cell_b_1 = player->cached_track_pair_cell_b
0043d408        cached_track_pair_cell_b_1->__offset(0x50).d = payload
0043d40b        return cached_track_pair_cell_b_1
