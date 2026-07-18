/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_tutorial @ 0x448da0 */

00448da0        tutorial->state = 0
00448dab        struct SubgameRuntime* eax_1 = &g_game_base->subgame
00448db0        tutorial->game = eax_1
00448dbc        eax_1->runtime_flags |= 0x600000
00448dbf        struct SubgameRuntime* game = tutorial->game
00448dc2        uint32_t runtime_flags = game->runtime_flags
00448dc5        runtime_flags.b &= 0xfd
00448dc7        game->runtime_flags = runtime_flags
00448dca        return
