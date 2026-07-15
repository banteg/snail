/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_garbage_hazard @ 0x43f200 */

0043f213        if (slot->owner_game->subgame_pause_gate != 0)
0043f213        return
0043f219        int32_t state = slot->state
0043f222        if (state u> 3)
0043f4de        label_43f4de:
0043f4de        slot->sprite->facing_angle = fconvert.s(fconvert.t(slot->owner_player->heading_roll) + fconvert.t(slot->attachment_facing_angle))
0043f4e1        struct Player* owner_player = slot->owner_player
0043f4ee        if (owner_player->follow_state.active == 1)
0043f4f0        struct Sprite* sprite = slot->sprite
0043f4ff        sprite->facing_angle = fconvert.s(fconvert.t(owner_player->follow_state.orientation_b) + fconvert.t(sprite->facing_angle))
0043f228        switch (state)
0043f23a        case 1
0043f23a        struct Vec3* ecx_1 = &slot->sprite->position
0043f23f        ecx_1->x = slot->world_position.x
0043f244        ecx_1->y = slot->world_position.y
0043f24a        ecx_1->z = slot->world_position.z
0043f24d        struct Player* owner_player_1 = slot->owner_player
0043f253        long double x87_r7_1 = fconvert.t(slot->world_position.z)
0043f256        long double temp1_1 = fconvert.t(owner_player_1->interaction_max_z)
0043f256        x87_r7_1 - temp1_1
0043f261        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0043f265        destroy_garbage_hazard(slot)
0043f270        return
0043f271        long double x87_r7_2 = fconvert.t(owner_player_1->nuke_effect_progress)
0043f277        long double temp3_1 = fconvert.t(0f)
0043f277        x87_r7_2 - temp3_1
0043f282        if ((((x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043f284        long double x87_r7_3 = fconvert.t(slot->world_position.x)
0043f286        long double temp6_1 = fconvert.t(0f)
0043f286        x87_r7_3 - temp6_1
0043f291        slot->state = 2
0043f29c        if ((((x87_r7_3 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp6_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043f2aa        slot->collision_side = 2
0043f29e        slot->collision_side = 1
0043f2b2        add_subgoldy_score(owner_player_1, 0, 0)
0043f2cd        append_subgame_contact_target(&slot->owner_game->enemy_manager, &slot->world_position, slot->radius, 0, slot)
0043f2d2        goto label_43f4de
0043f2d7        case 2
0043f2d7        void* __saved_ebp_2 = &data_4a4e6c
0043f2e1        slot->state = 3
0043f2f0        float var_c_1 = fconvert.s(random_signed_float_below(0.100000001f))
0043f2f4        int32_t var_34_2 = 0
0043f305        int32_t var_3c_1 = 0
0043f30b        float var_8_1 = fconvert.s(random_float_below(0.200000003f) + fconvert.t(0.100000001f))
0043f30f        long double st0_3 = random_float_below(0.300000012f)
0043f314        struct SubgameRuntime* owner_game = slot->owner_game
0043f325        long double x87_r6_1 = fconvert.t(owner_game->subgame_rate)
0043f33c        slot->velocity.x = fconvert.s(x87_r6_1 * fconvert.t(var_c_1))
0043f34a        slot->velocity.y = fconvert.s(fconvert.t(var_8_1) * x87_r6_1)
0043f355        slot->velocity.z = fconvert.s(st0_3 * x87_r6_1)
0043f358        int32_t collision_side = slot->collision_side
0043f363        if (collision_side == 1)
0043f365        long double x87_r7_10 = fconvert.t(slot->velocity.x)
0043f367        long double temp4_1 = fconvert.t(0f)
0043f367        x87_r7_10 - temp4_1
0043f36d        long double x87_r7_11 = fconvert.t(slot->velocity.x)
0043f374        if ((((x87_r7_10 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp4_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp4_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0043f376        x87_r7_11 = fneg(x87_r7_11)
0043f394        slot->velocity.x = fconvert.s(x87_r7_11)
0043f37d        if (collision_side == 2)
0043f37f        long double x87_r7_12 = fconvert.t(slot->velocity.x)
0043f381        long double temp8_1 = fconvert.t(0f)
0043f381        x87_r7_12 - temp8_1
0043f387        long double x87_r7_13 = fconvert.t(slot->velocity.x)
0043f38e        if ((((x87_r7_12 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp8_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp8_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0043f390        x87_r7_13 = fneg(x87_r7_13)
0043f394        slot->velocity.x = fconvert.s(fneg(x87_r7_13))
0043f396        long double x87_r7_14 = fconvert.t(slot->velocity.x)
0043f398        long double temp7_1 = fconvert.t(0f)
0043f398        x87_r7_14 - temp7_1
0043f3a3        int32_t var_1c_1
0043f3a3        if ((((x87_r7_14 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp7_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp7_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043f3af        long double x87_r7_15 = fconvert.t(slot->velocity.x)
0043f3b1        long double temp10_1 = fconvert.t(0f)
0043f3b1        x87_r7_15 - temp10_1
0043f3b7        var_1c_1 = 0
0043f3c0        if ((((x87_r7_15 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp10_1) ? 1 : 0) << 0xa | (x87_r7_15 == temp10_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
0043f3c2        var_1c_1 = 1
0043f3a5        var_1c_1 = 0xffffffff
0043f3d4        long double x87_r7_18 = float.t(var_1c_1) * fconvert.t(0.200000003f) * fconvert.t(owner_game->subgame_rate)
0043f3d7        slot->unknown_a4 = 0
0043f3df        slot->velocity.x = fconvert.s(x87_r7_18 + fconvert.t(slot->velocity.x))
0043f3e4        long double x87_r7_21 = fconvert.t(owner_game->subgame_rate) * fconvert.t(0.00833333377f)
0043f3ea        slot->smoke_timer = 0f
0043f3f0        slot->burst_rate_step = fconvert.s(x87_r7_21)
0043f3ff        slot->smoke_timer_step = fconvert.s(fconvert.t(owner_game->subgame_rate) * fconvert.t(0.277777791f))
0043f3a3        goto label_43f41a
0043f41a        case 3
0043f41a        label_43f41a:
0043f41a        slot->world_position.x = fconvert.s(fconvert.t(slot->velocity.x) + fconvert.t(slot->world_position.x))
0043f422        slot->world_position.y = fconvert.s(fconvert.t(slot->velocity.y) + fconvert.t(slot->world_position.y))
0043f42b        slot->world_position.z = fconvert.s(fconvert.t(slot->velocity.z) + fconvert.t(slot->world_position.z))
0043f436        float* eax_10 = &slot->sprite->position
0043f439        *eax_10 = slot->world_position.x
0043f43e        eax_10[1] = slot->world_position.y
0043f445        eax_10[2] = slot->world_position.z
0043f44e        long double x87_r7_30 = fconvert.t(slot->owner_game->subgame_rate)
0043f461        slot->velocity.y = fconvert.s(x87_r7_30 * x87_r7_30 * fconvert.t(-0.00999999978f) + fconvert.t(slot->velocity.y))
0043f469        long double x87_r7_32 = fconvert.t(slot->world_position.y)
0043f46c        long double temp2_1 = fconvert.t(-10f)
0043f46c        x87_r7_32 - temp2_1
0043f477        if ((((x87_r7_32 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_32, temp2_1) ? 1 : 0) << 0xa | (x87_r7_32 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0043f265        destroy_garbage_hazard(slot)
0043f270        return
0043f47d        struct Player* owner_player_2 = slot->owner_player
0043f483        long double x87_r7_33 = fconvert.t(slot->world_position.z)
0043f486        long double temp5_1 = fconvert.t(owner_player_2->interaction_max_z)
0043f486        x87_r7_33 - temp5_1
0043f491        if ((((x87_r7_33 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_33, temp5_1) ? 1 : 0) << 0xa | (x87_r7_33 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0043f265        destroy_garbage_hazard(slot)
0043f270        return
0043f49d        long double x87_r7_35 = fconvert.t(slot->smoke_timer_step) + fconvert.t(slot->smoke_timer)
0043f4a3        slot->smoke_timer = fconvert.s(x87_r7_35)
0043f4a9        long double temp9_1 = fconvert.t(1f)
0043f4a9        x87_r7_35 - temp9_1
0043f4b4        if ((((x87_r7_35 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_35, temp9_1) ? 1 : 0) << 0xa | (x87_r7_35 == temp9_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043f4bb        slot->smoke_timer = 0f
0043f4c1        spawn_garbage_smoke_particle(slot, &slot->world_position, &slot->velocity, owner_player_2)
0043f4b4        goto label_43f4de
0043f508        return
