/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: health_collect_particles @ 0x43a010 */

0043a01d        if ((g_runtime_config.render_flags.b & 0x10) == 0)
0043a01d        return
0043a026        int32_t var_34_1 = 0
0043a182        bool cond:1_1
0043a043        struct Sprite* eax_1 = allocate_sprite(&g_sprite_manager, player->player_slot, 0x80, 0xffffffff, 0xffffffff)
0043a06b        eax_1->flags |= SPRITE_FLAG_GAMEPLAY_OWNED
0043a06e        eax_1->progress = 0f
0043a075        eax_1->progress_step = 0.0416666679f
0043a07c        eax_1->gravity_step = -0.000199999995f
0043a083        struct tColour color
0043a083        struct tColour* eax_2 = set_color_rgba(&color, 1f, 0.75f, 0.75f, 1f)
0043a091        eax_1->color.r = eax_2->r
0043a099        eax_1->color.g = eax_2->g
0043a0a5        eax_1->color.b = eax_2->b
0043a0a8        float a = eax_2->a
0043a0ab        eax_1->size_start = 0.100000001f
0043a0b2        eax_1->size_end = 0.5f
0043a0b9        eax_1->color.a = a
0043a0c5        struct Vec3* edx_5 = &pickup->sprite->position
0043a0c8        float var_30_1 = fconvert.s(float.t(var_34_1) * fconvert.t(0.785398185f))
0043a0d2        eax_1->position.x = edx_5->x
0043a0d8        eax_1->position.y = edx_5->y
0043a0de        eax_1->position.z = edx_5->z
0043a0ed        float var_2c_1 = fconvert.s(fconvert.t(player->velocity.z) * fconvert.t(0.400000006f))
0043a0fd        float var_30_2 = fconvert.s(cosine(var_30_1) * fconvert.t(0.0149999997f))
0043a122        float var_24_1 = var_30_2
0043a126        eax_1->velocity.x = fconvert.s(sine(var_30_1) * fconvert.t(0.0149999997f))
0043a128        float var_20_1 = var_2c_1
0043a12c        eax_1->velocity.y = var_30_2
0043a12f        eax_1->velocity.z = var_2c_1
0043a160        eax_1->position.x = fconvert.s(fconvert.t(player->velocity.x) * fconvert.t(3f) + fconvert.t(eax_1->position.x))
0043a169        eax_1->position.y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(player->velocity.y) * fconvert.t(3f))) + fconvert.t(eax_1->position.y))
0043a178        cond:1_1 = var_34_1 + 1 s< 8
0043a17b        var_34_1 += 1
0043a17f        eax_1->position.z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(player->velocity.z) * fconvert.t(3f))) + fconvert.t(eax_1->position.z))
0043a182        do while (cond:1_1)
0043a18f        return
