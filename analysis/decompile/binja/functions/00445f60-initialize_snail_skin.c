/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_snail_skin @ 0x445f60 */

00445f60        struct GameRoot* game_base_1 = g_game_base
00445f65        snail_skin->selected_slot = 0
00445f70        snail_skin->active = 0
00445f77        snail_skin->owner_snail = &game_base_1->subgame.player.presentation
00445f7a        return
