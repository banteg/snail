/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_subgoldy_ghost @ 0x43d230 */

0043d24c        struct Sprite* eax = allocate_sprite(&g_sprite_manager, owner, 0x9f, 0xffffffff, 0xffffffff)
0043d251        player->ghost_sprite_a = eax
0043d257        enum SpriteFlag flags = eax->flags
0043d25a        flags:1.b |= 8
0043d25f        eax->flags = flags
0043d272        player->ghost_sprite_a->progress = 0f
0043d285        player->ghost_sprite_a->progress_step = 0f
0043d292        player->ghost_sprite_a->gravity_step = 0f
0043d295        struct tColour color
0043d295        struct tColour* eax_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043d2a2        struct tColour* ecx_3 = &player->ghost_sprite_a->color
0043d2ae        ecx_3->r = eax_2->r
0043d2b9        ecx_3->g = eax_2->g
0043d2bf        ecx_3->b = eax_2->b
0043d2c5        ecx_3->a = eax_2->a
0043d2ce        player->ghost_sprite_a->size_start = 0.5f
0043d2d7        player->ghost_sprite_a->size_end = 0.5f
0043d2e0        player->ghost_sprite_a->position.x = 0x40900000
0043d2ed        player->ghost_sprite_a->position.y = 1f
0043d2ff        player->ghost_sprite_a->position.z = 0f
0043d302        struct Sprite* eax_5 = allocate_sprite(&g_sprite_manager, owner, 0x9f, 0xffffffff, 0xffffffff)
0043d307        player->ghost_sprite_b = eax_5
0043d30d        enum SpriteFlag flags_1 = eax_5->flags
0043d310        flags_1:1.b |= 8
0043d318        eax_5->flags = flags_1
0043d32b        player->ghost_sprite_b->progress = 0f
0043d339        player->ghost_sprite_b->progress_step = 0f
0043d346        player->ghost_sprite_b->gravity_step = 0f
0043d349        struct tColour* eax_7 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043d356        struct tColour* ecx_9 = &player->ghost_sprite_b->color
0043d359        ecx_9->r = eax_7->r
0043d35e        ecx_9->g = eax_7->g
0043d364        ecx_9->b = eax_7->b
0043d36a        ecx_9->a = eax_7->a
0043d373        player->ghost_sprite_b->size_start = 0.5f
0043d37c        player->ghost_sprite_b->size_end = 0.5f
0043d385        player->ghost_sprite_b->position.x = 0xc0900000
0043d392        player->ghost_sprite_b->position.y = 1f
0043d3a4        player->ghost_sprite_b->position.z = 0f
0043d3a7        struct Sprite* ghost_sprite_a = player->ghost_sprite_a
0043d3b3        ghost_sprite_a->flags &= ~SPRITE_FLAG_RENDER_ENABLED
0043d3b6        struct Sprite* ghost_sprite_b = player->ghost_sprite_b
0043d3c1        ghost_sprite_b->flags &= ~SPRITE_FLAG_RENDER_ENABLED
0043d3ca        return
