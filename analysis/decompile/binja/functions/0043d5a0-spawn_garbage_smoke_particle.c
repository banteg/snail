/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_garbage_smoke_particle @ 0x43d5a0 */

0043d5ad        if ((g_runtime_config.render_flags.b & 0x10) == 0)
0043d5ad        return
0043d5ca        struct Sprite* eax_1 = allocate_sprite(&g_sprite_manager, owner_player->player_slot, 0x21, 0xffffffff, 0xffffffff)
0043d5e0        enum SpriteFlag flags = eax_1->flags
0043d5e3        eax_1->progress = 0f
0043d5ea        flags:1.b |= 8
0043d5f2        eax_1->flags = flags
0043d602        long double x87_r7_2 = fconvert.t(sub_garbage->owner_game->subgame_rate) * fconvert.t(0.0333333351f)
0043d608        eax_1->lifetime = 0f
0043d60f        eax_1->progress_step = fconvert.s(x87_r7_2)
0043d621        eax_1->lifetime_step = fconvert.s(fconvert.t(sub_garbage->owner_game->subgame_rate) * fconvert.t(0.416666687f))
0043d624        struct tColour color
0043d624        struct tColour* eax_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043d62e        eax_1->color.r = eax_3->r
0043d634        eax_1->color.g = eax_3->g
0043d63a        eax_1->color.b = eax_3->b
0043d63d        float a = eax_3->a
0043d640        eax_1->size_start = 0.300000012f
0043d647        eax_1->size_end = 1.29999995f
0043d64e        eax_1->color.a = a
0043d663        color.r = fconvert.s(fconvert.t(velocity->x) * fconvert.t(0.200000003f))
0043d674        color.g = fconvert.s(fconvert.t(velocity->y) * fconvert.t(0.200000003f))
0043d685        eax_1->velocity.x = color.r
0043d687        eax_1->position.__offset(0x30).d = 0f
0043d68e        eax_1->velocity.y = color.g
0043d691        int32_t* position_1 = position
0043d695        color.b = fconvert.s(fconvert.t(velocity->z) * fconvert.t(0.200000003f))
0043d69d        eax_1->velocity.z = color.b
0043d6a2        eax_1->position.x = *position_1
0043d6a7        eax_1->position.y = position_1[1]
0043d6ad        eax_1->position.z = position_1[2]
0043d6b5        return
