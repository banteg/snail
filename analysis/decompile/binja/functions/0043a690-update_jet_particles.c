/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_jet_particles @ 0x43a690 */

0043a69a        if (sub_hover->state != SUB_HOVER_STATE_ACTIVE)
0043a69a        return
0043a6a0        struct SubgameRuntime* game = sub_hover->game
0043a6b8        if (game->player.presentation.jetpack_channel.anim_manager.active_animation != game->player.presentation.jetpack_channel.animation_slots[0].body.bod.object->animation)
0043a6b8        return
0043a6da        float random_back_seed = fconvert.s(float.t(next_math_random_value()) * fconvert.t(1.52587893e-06f) + fconvert.t(0.400000006f))
0043a6e7        int32_t trail_index = 0
0043a6ed        int32_t trail_index_latch = 0
0043a6fd        float random_width_seed = fconvert.s(float.t(next_math_random_value()) * fconvert.t(1.52587893e-06f) + fconvert.t(0.119999997f))
0043a70b        while (true)
0043a70b        int32_t nozzle_index = 0
0043a70d        int32_t nozzle_index_latch = 0
0043a717        float trail_fraction = fconvert.s(float.t(trail_index_latch) * fconvert.t(0.0714285746f))
0043a72f        float particle_size = fconvert.s((fconvert.t(1f) - fconvert.t(trail_fraction)) * fconvert.t(random_width_seed) * fconvert.t(sub_hover->warning_intensity))
0043a735        float nozzle_position_x
0043a735        float nozzle_position_y
0043a735        float nozzle_position_z
0043a735        if (nozzle_index != 0)
0043a75e        struct Vec3* right_nozzle_position = &sub_hover->game->player.presentation.snail_hotspots_world[0xe]
0043a766        nozzle_position_x = right_nozzle_position->x
0043a76d        nozzle_position_y = right_nozzle_position->y
0043a774        nozzle_position_z = right_nozzle_position->z
0043a73d        struct Vec3* left_nozzle_position = &sub_hover->game->player.presentation.snail_hotspots_world[0xd]
0043a744        nozzle_position_x = left_nozzle_position->x
0043a74b        nozzle_position_y = left_nozzle_position->y
0043a752        nozzle_position_z = left_nozzle_position->z
0043a787        struct Vec3* player_forward_basis = &sub_hover->player->presentation.body.transform.basis_forward
0043a792        long double x87_r7_16 = fneg(fconvert.t(trail_fraction) * fconvert.t(random_back_seed) * fconvert.t(sub_hover->warning_intensity))
0043a7a5        long double x87_r7_17 = x87_r7_16 * fconvert.t(player_forward_basis->z)
0043a7b7        struct JetParticleSlot* particle_slot = ((nozzle_index + (trail_index << 1) + 2) << 4) + sub_hover
0043a7b9        float particle_position_x = fconvert.s(fconvert.t(nozzle_position_x) + fconvert.t(fconvert.s(x87_r7_16 * fconvert.t(player_forward_basis->x))))
0043a7c3        long double x87_r6_8 = fconvert.t(nozzle_position_y) + fconvert.t(fconvert.s(x87_r7_16 * fconvert.t(player_forward_basis->y)))
0043a7c7        particle_slot->sprite->size_end = particle_size
0043a7cc        particle_slot->sprite->size_start = particle_size
0043a7d1        float particle_position_y = fconvert.s(x87_r6_8)
0043a7e1        struct Vec3* particle_position = &particle_slot->sprite->position
0043a7e9        particle_position->x = particle_position_x
0043a7eb        particle_position->y = particle_position_y
0043a7ee        float particle_position_z = fconvert.s(fconvert.t(nozzle_position_z) + x87_r7_17)
0043a7f8        particle_position->z = particle_position_z
0043a7fb        if (trail_index == 0xe)
0043a80e        long double x87_r7_20 = float.t(next_math_random_value()) * fconvert.t(3.05175781e-05f)
0043a814        long double temp0_1 = fconvert.t(0.899999976f)
0043a814        x87_r7_20 - temp0_1
0043a81f        if ((((x87_r7_20 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp0_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043a83d        struct Sprite* trail_puff = allocate_sprite(&g_sprite_manager, sub_hover->game->player.player_slot, 0x21, 0xffffffff, 0xffffffff)
0043a853        enum SpriteFlag flags = trail_puff->flags
0043a85b        flags:1.b |= 8
0043a862        trail_puff->flags = flags
0043a867        trail_puff->progress = 0f
0043a86a        trail_puff->progress_step = 0.138888896f
0043a871        trail_puff->lifetime = 0f
0043a874        trail_puff->lifetime_step = 0f
0043a877        struct tColour color
0043a877        struct tColour* white_color = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043a881        trail_puff->color.r = white_color->r
0043a887        trail_puff->color.g = white_color->g
0043a88d        trail_puff->color.b = white_color->b
0043a890        float a = white_color->a
0043a893        trail_puff->size_start = 0.100000001f
0043a89a        trail_puff->size_end = 0.300000012f
0043a8a1        trail_puff->color.a = a
0043a8aa        struct Vec3* player_velocity = &sub_hover->game->player.velocity
0043a8bd        float trail_velocity_x = fconvert.s(fconvert.t(player_velocity->x) * fconvert.t(0.850000024f))
0043a8ce        float trail_velocity_y = fconvert.s(fconvert.t(player_velocity->y) * fconvert.t(0.850000024f))
0043a8d5        long double x87_r7_26 = fconvert.t(player_velocity->z) * fconvert.t(0.850000024f)
0043a8df        trail_puff->gravity_step = 0x3a83126f
0043a8e6        trail_puff->velocity.x = trail_velocity_x
0043a8e8        trail_puff->position.x = particle_position_x
0043a8ea        float trail_velocity_z = fconvert.s(x87_r7_26)
0043a8f2        trail_puff->velocity.y = trail_velocity_y
0043a8f9        trail_puff->position.y = particle_position_y
0043a8fc        trail_puff->velocity.z.b = trail_velocity_z.b
0043a8fc        trail_puff->velocity.z:1.b = trail_velocity_z:1.b
0043a8fc        trail_puff->velocity.z:2.b = trail_velocity_z:2.b
0043a8fc        trail_puff->velocity.z:3.b = trail_velocity_z:3.b
0043a8ff        trail_puff->position.z = particle_position_z
0043a902        trail_index = trail_index_latch
0043a906        nozzle_index = nozzle_index_latch
0043a90a        nozzle_index += 1
0043a90e        nozzle_index_latch = nozzle_index
0043a912        do while (nozzle_index s< 2)
0043a91c        trail_index_latch = trail_index + 1
0043a920        if (trail_index + 1 s>= 0xf)
0043a920        break
0043a703        trail_index = trail_index_latch
0043a92d        return
