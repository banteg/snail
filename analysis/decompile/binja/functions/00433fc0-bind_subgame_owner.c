/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: bind_subgame_owner @ 0x433fc0 */

00433fc5        struct SubgameOwnerLink result = g_game_base + 0x74618
00433fca        owner->game = result
00433fcc        return result
