/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_game_player @ 0x408000 */

00408004        initialize_renderable_bod(player)
00408011        initialize_renderable_bod(&player->camera)
0040801c        player->camera.unknown_00[0] = 0xb0
0040801c        player->camera.unknown_00[1] = 0x72
0040801c        player->camera.unknown_00[2] = 0x49
0040801c        player->camera.unknown_00[3] = 0
00408032        player->vtable = &data_4972f4
0040803c        return player
