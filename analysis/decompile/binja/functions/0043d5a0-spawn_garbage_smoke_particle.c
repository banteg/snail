/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_garbage_smoke_particle @ 0x43d5a0 */

0043d5ad        if ((g_runtime_config.render_flags.b & 0x10) == 0)
0043d5ad        return
0043d5ca        struct Sprite* smoke_sprite = allocate_sprite(&g_sprite_manager, owner_player->player_slot, 0x21, 0xffffffff, 0xffffffff)
0043d5e0        enum SpriteFlag flags = smoke_sprite->flags
0043d5e3        smoke_sprite->progress = 0f
0043d5ea        flags:1.b |= 8
0043d5f2        smoke_sprite->flags = flags
0043d602        long double x87_r7_2 = fconvert.t(sub_garbage->owner_game->subgame_rate) * fconvert.t(0.0333333351f)
0043d608        smoke_sprite->lifetime = 0f
0043d60f        smoke_sprite->progress_step = fconvert.s(x87_r7_2)
0043d621        smoke_sprite->lifetime_step = fconvert.s(fconvert.t(sub_garbage->owner_game->subgame_rate) * fconvert.t(0.416666687f))
0043d624        struct tColour color
0043d624        struct tColour* eax_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043d62e        smoke_sprite->color.r = eax_2->r
0043d634        smoke_sprite->color.g = eax_2->g
0043d63a        smoke_sprite->color.b = eax_2->b
0043d63d        float a = eax_2->a
0043d640        smoke_sprite->size_start = 0.300000012f
0043d647        smoke_sprite->size_end = 1.29999995f
0043d64e        smoke_sprite->color.a = a
0043d663        color.r = fconvert.s(fconvert.t(velocity->x) * fconvert.t(0.200000003f))
0043d674        color.g = fconvert.s(fconvert.t(velocity->y) * fconvert.t(0.200000003f))
0043d67b        long double x87_r7_10 = fconvert.t(velocity->z) * fconvert.t(0.200000003f)
0043d681        float g = color.g
0043d685        smoke_sprite->velocity.x = color.r
0043d687        smoke_sprite->gravity_step = 0
0043d68e        smoke_sprite->velocity.y = g
0043d695        color.b = fconvert.s(x87_r7_10)
0043d69d        smoke_sprite->velocity.z = color.b
0043d6a2        smoke_sprite->position.x = position->x
0043d6a7        smoke_sprite->position.y = position->y
0043d6ad        smoke_sprite->position.z = position->z
0043d6b5        return
