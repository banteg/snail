/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_subgoldy_death @ 0x446e30 */

00446e3e        switch (player->game->level_mode)
00446e4d        case 0
00446e4d        if (player->_pad_4340 s<= 0)
00446e51        initialize_subgoldy_resurrect(player, 1)
00446e56        return 
00446e59        initialize_subgoldy_resurrect(player, 0)
00446e51        case 1, 4
00446e51        initialize_subgoldy_resurrect(player, 1)
00446e59        case 7
00446e59        initialize_subgoldy_resurrect(player, 0)
00446e5e        return
