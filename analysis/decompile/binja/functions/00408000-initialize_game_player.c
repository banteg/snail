/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_game_player @ 0x408000 */

00408004        initialize_renderable_bod(player)
00408011        initialize_renderable_bod(&player->camera)
0040801c        player->camera.body.bod.bod.vtable = &g_noop_runtime_callback_table
00408032        player->body.bod.bod.vtable = &g_game_player_callback_table
0040803c        return player
