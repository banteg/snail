/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_golb_smoke @ 0x415c60 */

00415c82        struct Sprite* smoke_sprite = allocate_sprite(&g_sprite_manager, shot->owner_player->player_slot, 0x80, 0xffffffff, 0xffffffff)
00415c98        enum SpriteFlag flags = smoke_sprite->flags
00415c9b        smoke_sprite->progress = 0f
00415ca2        flags:1.b |= 8
00415caa        smoke_sprite->flags = flags
00415cba        long double x87_r7_1 = fconvert.t(shot->game->subgame_rate) * fconvert.t(0.166666672f)
00415cc0        smoke_sprite->lifetime = 0f
00415cc7        smoke_sprite->progress_step = fconvert.s(x87_r7_1)
00415cd9        smoke_sprite->lifetime_step = fconvert.s(fconvert.t(shot->game->subgame_rate) * fconvert.t(0.416666687f))
00415cdc        struct tColour color
00415cdc        struct tColour* eax_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00415ce6        smoke_sprite->color.r = eax_2->r
00415cec        smoke_sprite->color.g = eax_2->g
00415cf2        smoke_sprite->color.b = eax_2->b
00415cf5        float a = eax_2->a
00415cf8        smoke_sprite->size_start = 0.100000001f
00415cff        smoke_sprite->size_end = 0.5f
00415d06        smoke_sprite->color.a = a
00415d1b        color.r = fconvert.s(fconvert.t(shot->velocity.x) * fconvert.t(0.400000006f))
00415d2f        color.g = fconvert.s(fconvert.t(shot->velocity.y) * fconvert.t(0.400000006f))
00415d39        long double x87_r7_9 = fconvert.t(shot->velocity.z) * fconvert.t(0.400000006f)
00415d3f        float g = color.g
00415d43        smoke_sprite->velocity.x = color.r
00415d45        smoke_sprite->gravity_step = 0
00415d4d        smoke_sprite->velocity.y = g
00415d54        color.b = fconvert.s(x87_r7_9)
00415d5c        smoke_sprite->velocity.z = color.b
00415d61        smoke_sprite->position.x = position->x
00415d66        smoke_sprite->position.y = position->y
00415d6c        smoke_sprite->position.z = position->z
00415d73        return
