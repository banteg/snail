/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_ring_or_special_effect_particles @ 0x43e470 */

0043e47b        int32_t i_1 = 0
0043e47f        ring->state = 1
0043e489        ring->star_shower_counter = 0
0043e492        struct SubRingStar (* particle)[0xa] = &ring->particles
0043e677        int32_t i
0043e4a9        (particle + 8)->__offset(0xc).d = fconvert.s(float.t(i_1) * fconvert.t(0.628318548f))
0043e4bb        (particle + 8)->__offset(0x10).d = fconvert.s(fconvert.t(ring->rate_source->subgame_rate) * fconvert.t(0.104719758f))
0043e4be        (particle - 0x90)->particles[0].parent = ring
0043e4c3        (particle + 8)->x = ring->world_position.x
0043e4c8        (particle + 8)->y = ring->world_position.y
0043e4ce        (particle + 8)->z = ring->world_position.z
0043e4d1        (particle + 8)->__offset(0x14).d = 1.20000005f
0043e4d8        int32_t kind = ring->kind
0043e4f3        if (kind == 4 || kind == 5 || kind == 8)
0043e59f        (particle - 0x90)->particles[0].sprite = allocate_sprite(&g_sprite_manager, ring->owner_player->player_slot, 0x87, 0xffffffff, 0xffffffff)
0043e5a1        ring->star_sprite_id = 0x88
0043e5ad        (particle - 0x90)->particles[0].sprite->__offset(0x28).d = 9
0043e501        if (kind == 2 || kind == 6)
0043e568        (particle - 0x90)->particles[0].sprite = allocate_sprite(&g_sprite_manager, ring->owner_player->player_slot, 0x83, 0xffffffff, 0xffffffff)
0043e56a        ring->star_sprite_id = 0x84
0043e576        (particle - 0x90)->particles[0].sprite->__offset(0x28).d = 0xd
0043e50b        if (kind == 3 || kind == 7)
0043e531        (particle - 0x90)->particles[0].sprite = allocate_sprite(&g_sprite_manager, ring->owner_player->player_slot, 0x85, 0xffffffff, 0xffffffff)
0043e533        ring->star_sprite_id = 0x86
0043e53f        (particle - 0x90)->particles[0].sprite->__offset(0x28).d = 0xd
0043e5cc        struct Color4f color
0043e5cc        struct Color4f* eax_10 = set_color_rgba(&color, 1f, 1f, 1f, 0.800000012f)
0043e5d5        void* __offset(Sprite, 0x2c) edx_6 = (particle - 0x90)->particles[0].sprite + 0x2c
0043e5d8        (edx_6 - 0x2c)->__offset(0x2c).d = eax_10->r
0043e5dd        (edx_6 - 0x2c)->__offset(0x30).d = eax_10->g
0043e5e3        (edx_6 - 0x2c)->__offset(0x34).d = eax_10->b
0043e5e9        (edx_6 - 0x2c)->__offset(0x38).d = eax_10->a
0043e5ec        struct Sprite* sprite = (particle - 0x90)->particles[0].sprite
0043e5ee        int32_t ecx_9 = sprite->__offset(0x4).d
0043e5f1        ecx_9:1.b |= 8
0043e5f4        sprite->__offset(0x4).d = ecx_9
0043e5fb        (particle - 0x90)->particles[0].sprite->__offset(0x68).d = 0
0043e600        (particle - 0x90)->particles[0].sprite->__offset(0x6c).d = 0
0043e605        (particle - 0x90)->particles[0].sprite->__offset(0x78).d = 0
0043e60f        (particle - 0x90)->particles[0].sprite->__offset(0x60).d = 0x3f3851ec
0043e614        (particle - 0x90)->particles[0].sprite->__offset(0x64).d = 0x3f3851ec
0043e61b        void* __offset(Sprite, 0x48) edx_10 = (particle - 0x90)->particles[0].sprite + 0x48
0043e620        (edx_10 - 0x48)->__offset(0x48).d = ring->world_position.x
0043e625        (edx_10 - 0x48)->__offset(0x4c).d = ring->world_position.y
0043e62b        (edx_10 - 0x48)->__offset(0x50).d = ring->world_position.z
0043e633        (particle - 0x90)->particles[0].sprite->__offset(0x7c).d = (particle - 0x90)->particles[0].phase
0043e636        int32_t kind_1 = ring->kind
0043e644        if (kind_1 == 3 || kind_1 == 6)
0043e657        (particle - 0x90)->particles[0].sprite->__offset(0x80).d = 0
0043e64d        (particle - 0x90)->particles[0].sprite->__offset(0x80).d = fconvert.s(fneg(fconvert.t((particle - 0x90)->particles[0].phase_step)))
0043e663        update_ring_or_special_effect_particle(particle)
0043e66c        particle = &(*particle)[1]
0043e66f        i = i_1 + 1
0043e673        i_1 = i
0043e677        do while (i s< 0xa)
0043e684        return i
