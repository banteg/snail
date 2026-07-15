/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_main_menu @ 0x419b30 */

00419b3b        kill_all_borders(&g_game_base->border_manager)
00419b45        return kill_game_sprites(&g_sprite_manager) __tailcall
