/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: mark_current_track_pair_with_payload @ 0x43d3d0 */

0043d3d0        struct TrackRowCell* cached_track_pair_cell_a = player->cached_track_pair_cell_a
0043d3e1        cached_track_pair_cell_a->flags_a |= 0x40
0043d3e4        struct TrackRowCell* cached_track_pair_cell_b = player->cached_track_pair_cell_b
0043d3f3        cached_track_pair_cell_b->flags_a |= 0x40
0043d3fd        player->cached_track_pair_cell_a->lane_flags_or_payload = payload
0043d400        struct TrackRowCell* cached_track_pair_cell_b_1 = player->cached_track_pair_cell_b
0043d408        cached_track_pair_cell_b_1->lane_flags_or_payload = payload
0043d40b        return cached_track_pair_cell_b_1
