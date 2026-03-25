/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: mark_current_track_pair_with_payload @ 0x43d3d0 */

0043d3d0        void* eax_2 = player->__offset(0x98).d
0043d3e1        *(eax_2 + 4) |= 0x40
0043d3e4        void* eax = player->__offset(0x9c).d
0043d3f3        *(eax + 4) |= 0x40
0043d3fd        *(player->__offset(0x98).d + 0x50) = payload
0043d400        void* result = player->__offset(0x9c).d
0043d408        *(result + 0x50) = payload
0043d40b        return result
