# destroy_main_menu

Small main-menu teardown helper at 0x419b30. Both BN and IDA decompiles show it
killing all global border-manager widgets and then clearing game sprites.

Exact match: 100.00%, 5/5 instructions, with g_game_base, kill_all_borders,
g_sprite_manager, and kill_game_sprites operands resolved.
