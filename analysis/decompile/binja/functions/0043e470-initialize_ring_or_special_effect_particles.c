/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_ring_or_special_effect_particles @ 0x43e470 */

0043e47b        int32_t i_1 = 0
0043e47f        ring->state = SUB_RING_STATE_ACTIVE
0043e489        ring->star_shower_counter = 0
0043e492        struct SubRingStar* particle = &ring->particles
0043e677        int32_t i
0043e4a9        particle->base_position.__offset(0xc).d = fconvert.s(float.t(i_1) * fconvert.t(0.628318548f))
0043e4bb        particle->base_position.__offset(0x10).d = fconvert.s(fconvert.t(ring->rate_source->subgame_rate) * fconvert.t(0.104719758f))
0043e4be        particle->parent = ring
0043e4c3        particle->base_position.x = ring->world_position.x
0043e4c8        particle->base_position.y = ring->world_position.y
0043e4ce        particle->base_position.z = ring->world_position.z
0043e4d1        particle->base_position.__offset(0x14).d = 1.20000005f
0043e4d8        enum SubRingKind kind = ring->kind
0043e4f3        if (kind == SUB_RING_KIND_NORMAL_DEFAULT || kind == SUB_RING_KIND_NORMAL_AUTHORED || kind == SUB_RING_KIND_POWER_UP_AUTHORED)
0043e59f        particle->sprite = allocate_sprite(&g_sprite_manager, ring->owner_player->player_slot, 0x87, 0xffffffff, 0xffffffff)
0043e5a1        ring->star_sprite_id = 0x88
0043e5ad        particle->sprite->draw_mode = 9
0043e501        if (kind == SUB_RING_KIND_EXPLODE_RAMP || kind == SUB_RING_KIND_EXPLODE_AUTHORED)
0043e568        particle->sprite = allocate_sprite(&g_sprite_manager, ring->owner_player->player_slot, 0x83, 0xffffffff, 0xffffffff)
0043e56a        ring->star_sprite_id = 0x84
0043e576        particle->sprite->draw_mode = 0xd
0043e50b        if (kind == SUB_RING_KIND_SLOW_DEFAULT || kind == SUB_RING_KIND_SLOW_AUTHORED)
0043e531        particle->sprite = allocate_sprite(&g_sprite_manager, ring->owner_player->player_slot, 0x85, 0xffffffff, 0xffffffff)
0043e533        ring->star_sprite_id = 0x86
0043e53f        particle->sprite->draw_mode = 0xd
0043e5cc        struct tColour color
0043e5cc        struct tColour* eax_10 = set_color_rgba(&color, 1f, 1f, 1f, 0.800000012f)
0043e5d5        struct tColour* edx_6 = &particle->sprite->color
0043e5d8        edx_6->r = eax_10->r
0043e5dd        edx_6->g = eax_10->g
0043e5e3        edx_6->b = eax_10->b
0043e5e9        edx_6->a = eax_10->a
0043e5ec        struct Sprite* sprite = particle->sprite
0043e5ee        enum SpriteFlag flags = sprite->flags
0043e5f1        flags:1.b |= 8
0043e5f4        sprite->flags = flags
0043e5fb        particle->sprite->progress = 0f
0043e600        particle->sprite->progress_step = 0f
0043e605        particle->sprite->gravity_step = 0f
0043e60f        particle->sprite->size_start = 0.720000029f
0043e614        particle->sprite->size_end = 0.720000029f
0043e61b        int32_t* edx_10 = &particle->sprite->position
0043e620        *edx_10 = ring->world_position.x
0043e625        edx_10[1] = ring->world_position.y
0043e62b        edx_10[2] = ring->world_position.z
0043e62e        struct Sprite* sprite_1 = particle->sprite
0043e630        float phase = particle->phase
0043e633        sprite_1->facing_angle.b = phase.b
0043e633        sprite_1->facing_angle:1.b = phase:1.b
0043e633        sprite_1->facing_angle:2.b = phase:2.b
0043e633        sprite_1->facing_angle:3.b = phase:3.b
0043e636        enum SubRingKind kind_1 = ring->kind
0043e644        if (kind_1 == SUB_RING_KIND_SLOW_DEFAULT || kind_1 == SUB_RING_KIND_EXPLODE_AUTHORED)
0043e657        particle->sprite->facing_angle_step = 0f
0043e64d        particle->sprite->facing_angle_step = fconvert.s(fneg(fconvert.t(particle->phase_step)))
0043e663        update_ring_or_special_effect_particle(particle)
0043e66c        particle = &particle[1]
0043e66f        i = i_1 + 1
0043e673        i_1 = i
0043e677        do while (i s< 0xa)
0043e684        return i
