/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_parcel @ 0x4431d0 */

004431da        struct SubgameRuntime* owner_subgame_3 = parcel->owner_subgame
004431e0        if (owner_subgame_3->subgame_pause_gate != 0)
004431e0        return
004431f2        struct Vec3 vector
004431f2        switch (parcel->state)
004431ff        case PARCEL_STATE_TRACK_ACTIVE
004431ff        long double x87_r7_2 = fconvert.t(owner_subgame_3->player.interaction_max_z) - fconvert.t(10f)
00443205        long double temp0_1 = fconvert.t(parcel->position.z)
00443205        x87_r7_2 - temp0_1
0044320d        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00443212        kill_sprite(parcel->sprite)
00443217        parcel->state = PARCEL_STATE_INACTIVE
0044321d        long double x87_r7_4 = fconvert.t(parcel->bob_phase_step) + fconvert.t(parcel->bob_phase)
00443220        long double temp3_1 = fconvert.t(1f)
00443220        x87_r7_4 - temp3_1
00443226        parcel->bob_phase = fconvert.s(x87_r7_4)
00443226        bool c1_1 = unknown  {fst dword [esi+0x5c], st0}
0044322e        if ((((x87_r7_4 < temp3_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_4, temp3_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp3_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00443236        parcel->bob_phase = fconvert.s(x87_r7_4 - fconvert.t(1f))
00443243        struct Vec3* ecx_2 = &parcel->sprite->position
00443248        ecx_2->x = parcel->position.x
0044324d        ecx_2->y = parcel->position.y
00443253        struct Vec3* var_38_1 = ecx_2
00443254        ecx_2->z = parcel->position.z
00443257        struct Sprite* sprite_5 = parcel->sprite
00443277        sprite_5->position.y = fconvert.s(sine(fconvert.s(fconvert.t(parcel->bob_phase) * fconvert.t(6.28318548f))) * fconvert.t(0.300000012f) + fconvert.t(sprite_5->position.y))
00443286        parcel->sprite->facing_angle = parcel->owner_player->heading_roll
00443289        struct Player* owner_player = parcel->owner_player
00443293        if (owner_player->follow_state.active == 1)
00443299        struct Sprite* sprite_4 = parcel->sprite
004432a6        sprite_4->facing_angle = fconvert.s(fconvert.t(owner_player->follow_state.orientation_b) + fconvert.t(sprite_4->facing_angle))
004432b8        case PARCEL_STATE_COLLECT_PENDING
004432b8        struct SubgameRuntime* owner_subgame_4 = owner_subgame_3
004432c1        long double x87_r7_17 = sine(fconvert.s(fconvert.t(parcel->bob_phase) * fconvert.t(6.28318548f))) * fconvert.t(0.300000012f)
004432c7        struct SubgameRuntime* owner_subgame = parcel->owner_subgame
004432ca        parcel->progress = 0f
004432d2        parcel->progress_step = 0.0416666679f
004432df        parcel->position.y = fconvert.s(x87_r7_17 + fconvert.t(parcel->position.y))
00443303        vector.x = fconvert.s(fconvert.t(owner_subgame->player.presentation.snail_hotspots_world[0xb].x) - fconvert.t(parcel->position.x))
0044330b        vector.y = fconvert.s(fconvert.t(owner_subgame->player.presentation.snail_hotspots_world[0xb].y) - fconvert.t(parcel->position.y))
00443317        vector.z = fconvert.s(fconvert.t(owner_subgame->player.presentation.snail_hotspots_world[0xb].z) - fconvert.t(parcel->position.z))
0044331b        long double st0_3 = vector_magnitude(&vector)
00443320        struct SubgameRuntime* owner_subgame_1 = parcel->owner_subgame
00443323        parcel->state = PARCEL_STATE_COLLECTING
0044332a        parcel->target_distance = fconvert.s(st0_3)
00443358        parcel->travel_dir.x = fconvert.s(fconvert.t(parcel->position.x) - fconvert.t(owner_subgame_1->player.presentation.snail_hotspots_world[0xb].x))
00443362        parcel->travel_dir.y = fconvert.s(fconvert.t(parcel->position.y) - fconvert.t(owner_subgame_1->player.presentation.snail_hotspots_world[0xb].y))
00443369        parcel->travel_dir.z = fconvert.s(fconvert.t(parcel->position.z) - fconvert.t(owner_subgame_1->player.presentation.snail_hotspots_world[0xb].z))
0044336c        normalize_vector(&parcel->travel_dir)
00443379        label_443379:
00443379        long double x87_r7_35 = fconvert.t(1f) - fconvert.t(parcel->progress)
00443382        struct Vec3* eax_13 = &parcel->owner_subgame->player.presentation.snail_hotspots_world[0xb]
0044338b        long double x87_r6_2 = x87_r7_35 * fconvert.t(parcel->target_distance)
004433c3        parcel->position.x = fconvert.s(fconvert.t(fconvert.s(x87_r6_2 * fconvert.t(parcel->travel_dir.x))) + fconvert.t(eax_13->x))
004433c5        parcel->position.y = fconvert.s(fconvert.t(fconvert.s(x87_r6_2 * fconvert.t(parcel->travel_dir.y))) + fconvert.t(eax_13->y))
004433d9        parcel->position.z = fconvert.s(x87_r6_2 * fconvert.t(parcel->travel_dir.z) + fconvert.t(eax_13->z))
004433e2        parcel->sprite->size_end = fconvert.s(x87_r7_35 * fconvert.t(0.600000024f) + fconvert.t(0.400000006f))
004433e5        struct Sprite* sprite = parcel->sprite
004433e8        float size_end = sprite->size_end
004433eb        sprite->size_start = size_end
004433ee        float size_end_1 = size_end
00443400        long double x87_r7_41 = sine(fconvert.s(fconvert.t(parcel->progress) * fconvert.t(3.14159274f))) * fconvert.t(0.5f)
0044340c        struct Vec3* eax_17 = &parcel->owner_subgame->player.presentation.body.transform.basis_up
00443411        struct Vec3* edx_9 = &parcel->sprite->position
00443440        float var_14_4 = fconvert.s(fconvert.t(fconvert.s(x87_r7_41 * fconvert.t(eax_17->y))) + fconvert.t(parcel->position.y))
00443448        long double x87_r7_43 = x87_r7_41 * fconvert.t(eax_17->z) + fconvert.t(parcel->position.z)
0044344b        edx_9->x = fconvert.s(fconvert.t(fconvert.s(x87_r7_41 * fconvert.t(eax_17->x))) + fconvert.t(parcel->position.x))
0044344d        edx_9->y = var_14_4
00443458        edx_9->z = fconvert.s(x87_r7_43)
0044345e        long double x87_r7_45 = fconvert.t(parcel->progress_step) + fconvert.t(parcel->progress)
00443461        parcel->progress = fconvert.s(x87_r7_45)
00443464        long double temp1_1 = fconvert.t(1f)
00443464        x87_r7_45 - temp1_1
0044346f        if ((((x87_r7_45 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_45, temp1_1) ? 1 : 0) << 0xa | (x87_r7_45 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00443475        struct Sprite* sprite_2 = parcel->sprite
00443478        parcel->state = PARCEL_STATE_INACTIVE
0044347b        kill_sprite(sprite_2)
004431f2        case PARCEL_STATE_COLLECTING
004431f2        goto label_443379
00443487        case PARCEL_STATE_DELIVERY_PENDING
00443487        parcel->progress = 0f
0044348a        parcel->progress_step = 0.0166666675f
00443491        parcel->state = PARCEL_STATE_DELIVERING
004434b1        parcel->delivery_offset.x = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
004434b7        int32_t eax_22 = next_math_random_value()
004434c0        parcel->delivery_offset.z = 0f
004434dc        parcel->delivery_offset.y = fconvert.s((float.t(eax_22) - fconvert.t(16384f)) * fconvert.t(9.15527344e-05f) + fconvert.t(1f))
004434e2        label_4434e2:
004434e2        struct SubgameRuntime* owner_subgame_2 = parcel->owner_subgame
00443519        vector.x = fconvert.s(fconvert.t(owner_subgame_2->completion.widget_world.x) - fconvert.t(owner_subgame_2->player.presentation.snail_hotspots_world[0xb].x))
00443520        vector.y = fconvert.s(fconvert.t(owner_subgame_2->completion.widget_world.y) - fconvert.t(owner_subgame_2->player.presentation.snail_hotspots_world[0xb].y))
00443535        vector.z = fconvert.s(fconvert.t(owner_subgame_2->completion.widget_world.z) - fconvert.t(owner_subgame_2->player.presentation.snail_hotspots_world[0xb].z))
0044353f        parcel->sprite->size_end = fconvert.s(fconvert.t(parcel->progress) * fconvert.t(0.600000024f) + fconvert.t(0.400000006f))
00443542        struct Sprite* sprite_1 = parcel->sprite
00443548        sprite_1->size_start = sprite_1->size_end
0044354e        long double x87_r7_62 = fconvert.t(parcel->progress)
00443557        struct Vec3* eax_25 = &parcel->owner_subgame->player.presentation.snail_hotspots_world[0xb]
00443583        float var_14_6 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.y) * x87_r7_62)) + fconvert.t(eax_25->y))
00443591        float* eax_27 = &parcel->sprite->position
00443594        float var_10_6 = fconvert.s(x87_r7_62 * fconvert.t(vector.z) + fconvert.t(eax_25->z))
00443598        *eax_27 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.x) * x87_r7_62)) + fconvert.t(eax_25->x))
0044359e        float var_38_5 = var_10_6
0044359f        *&eax_27[1] = var_14_6
004435a2        *&eax_27[2] = var_10_6
004435b1        long double st0_6 = sine(fconvert.s(fconvert.t(parcel->progress) * fconvert.t(3.14159274f)))
004435c4        struct Vec3* eax_29 = &parcel->sprite->position
004435d3        float var_8_4 = fconvert.s(st0_6 * fconvert.t(parcel->delivery_offset.y))
004435d7        long double x87_r7_68 = st0_6 * fconvert.t(parcel->delivery_offset.z)
004435e3        eax_29->x = fconvert.s(fconvert.t(fconvert.s(st0_6 * fconvert.t(parcel->delivery_offset.x))) + fconvert.t(eax_29->x))
004435ec        eax_29->y = fconvert.s(fconvert.t(var_8_4) + fconvert.t(eax_29->y))
004435f2        eax_29->z = fconvert.s(x87_r7_68 + fconvert.t(eax_29->z))
004435f8        long double x87_r7_71 = fconvert.t(parcel->progress_step) + fconvert.t(parcel->progress)
004435fb        parcel->progress = fconvert.s(x87_r7_71)
004435fe        long double temp2_1 = fconvert.t(1f)
004435fe        x87_r7_71 - temp2_1
00443609        if ((((x87_r7_71 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_71, temp2_1) ? 1 : 0) << 0xa | (x87_r7_71 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00443614        register_parcel_delivery(&parcel->owner_subgame->completion)
00443619        struct Sprite* sprite_3 = parcel->sprite
0044361c        parcel->state = PARCEL_STATE_INACTIVE
0044361f        kill_sprite(sprite_3)
004431f2        case PARCEL_STATE_DELIVERING
004431f2        goto label_4434e2
0044362a        return
