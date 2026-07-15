/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_golb_smoke @ 0x415c60 */

00415c82        struct Sprite* eax_1 = allocate_sprite(&g_sprite_manager, shot->owner_player->player_slot, 0x80, 0xffffffff, 0xffffffff)
00415c98        enum SpriteFlag flags = eax_1->flags
00415c9b        eax_1->progress = 0f
00415ca2        flags:1.b |= 8
00415caa        eax_1->flags = flags
00415cba        long double x87_r7_1 = fconvert.t(shot->game->subgame_rate) * fconvert.t(0.166666672f)
00415cc0        eax_1->lifetime = 0f
00415cc7        eax_1->progress_step = fconvert.s(x87_r7_1)
00415cd9        eax_1->lifetime_step = fconvert.s(fconvert.t(shot->game->subgame_rate) * fconvert.t(0.416666687f))
00415cdc        struct tColour color
00415cdc        struct tColour* eax_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00415ce6        eax_1->color.r = eax_3->r
00415cec        eax_1->color.g = eax_3->g
00415cf2        eax_1->color.b = eax_3->b
00415cf5        float a = eax_3->a
00415cf8        eax_1->size_start = 0.100000001f
00415cff        eax_1->size_end = 0.5f
00415d06        eax_1->color.a = a
00415d1b        color.r = fconvert.s(fconvert.t(shot->velocity.x) * fconvert.t(0.400000006f))
00415d2f        color.g = fconvert.s(fconvert.t(shot->velocity.y) * fconvert.t(0.400000006f))
00415d43        eax_1->velocity.x = color.r
00415d45        eax_1->position.__offset(0x30).d = 0f
00415d4d        eax_1->velocity.y = color.g
00415d54        color.b = fconvert.s(fconvert.t(shot->velocity.z) * fconvert.t(0.400000006f))
00415d5c        eax_1->velocity.z = color.b
00415d61        eax_1->position.x = position->x
00415d66        eax_1->position.y = position->y
00415d6c        eax_1->position.z = position->z
00415d73        return
