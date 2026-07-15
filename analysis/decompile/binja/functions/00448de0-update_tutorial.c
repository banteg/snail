/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_tutorial @ 0x448de0 */

00448de0        struct SubgameRuntime* game = tutorial->game
00448dea        get_track_grid_cell_at_world_position(game, &game->player.body.transform.position)
00448def        return
