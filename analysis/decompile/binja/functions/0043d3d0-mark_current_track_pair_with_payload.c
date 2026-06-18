/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: mark_current_track_pair_with_payload @ 0x43d3d0 */

0043d3d0        struct Sprite* ghost_sprite_a = player->ghost_sprite_a
0043d3e1        ghost_sprite_a->flags |= 0x40
0043d3e4        struct Sprite* ghost_sprite_b = player->ghost_sprite_b
0043d3f3        ghost_sprite_b->flags |= 0x40
0043d3fd        player->ghost_sprite_a->position.z = payload
0043d400        struct Sprite* ghost_sprite_b_1 = player->ghost_sprite_b
0043d408        ghost_sprite_b_1->position.z = payload
0043d40b        return ghost_sprite_b_1
