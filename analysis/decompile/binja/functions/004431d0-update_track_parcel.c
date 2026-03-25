/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_parcel @ 0x4431d0 */

004431da        struct Game* game_3 = parcel->game
004431e0        if (game_3->_pad_00[9] != 0)
004431e0        return 
004431f2        float var_24
004431f2        switch (parcel->state)
004431ff        case 1
004431ff        long double x87_r7_2 = fconvert.t(game_3->__offset(0x3be0e4).d) - fconvert.t(10f)
00443205        long double temp0_1 = fconvert.t(parcel->world_position.z)
00443205        x87_r7_2 - temp0_1
00443208        uint32_t eax_1
00443208        eax_1.w = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe
0044320d        if ((eax_1:1.b & 0x41) == 0)
00443212        kill_sprite(parcel->sprite)
00443217        parcel->state = 0
0044321d        long double x87_r7_4 = fconvert.t(parcel->bob_phase_step) + fconvert.t(parcel->bob_phase)
00443220        long double temp3_1 = fconvert.t(1f)
00443220        x87_r7_4 - temp3_1
00443226        parcel->bob_phase = fconvert.s(x87_r7_4)
00443226        bool c1_1 = unimplemented  {fst dword [esi+0x5c], st0}
00443229        eax_1.w = (x87_r7_4 < temp3_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_4, temp3_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp3_1 ? 1 : 0) << 0xe | 0x3800
0044322e        if ((eax_1:1.b & 0x41) == 0)
00443236        parcel->bob_phase = fconvert.s(x87_r7_4 - fconvert.t(1f))
00443243        float* ecx_2 = parcel->sprite + 0x48
00443248        *ecx_2 = parcel->world_position.x
0044324d        ecx_2[1] = parcel->world_position.y
00443253        float* var_38_1 = ecx_2
00443254        ecx_2[2] = parcel->world_position.z
00443257        void* sprite_5 = parcel->sprite
00443277        *(sprite_5 + 0x4c) = fconvert.s(sine(fconvert.s(fconvert.t(parcel->bob_phase) * fconvert.t(6.28318548f))) * fconvert.t(0.300000012f) + fconvert.t(*(sprite_5 + 0x4c)))
00443286        *(parcel->sprite + 0x7c) = *(parcel->owner + 0x370)
00443289        void* owner = parcel->owner
00443293        if (*(owner + 0x384) == 1)
00443299        void* sprite_4 = parcel->sprite
004432a6        *(sprite_4 + 0x7c) = fconvert.s(fconvert.t(*(owner + 0x3a0)) + fconvert.t(*(sprite_4 + 0x7c)))
004432b8        case 4
004432b8        struct Game* game_4 = game_3
004432c1        long double x87_r7_17 = sine(fconvert.s(fconvert.t(parcel->bob_phase) * fconvert.t(6.28318548f))) * fconvert.t(0.300000012f)
004432c7        struct Game* game = parcel->game
004432ca        parcel->progress = 0f
004432d2        parcel->progress_step = 0.0416666679f
004432df        parcel->world_position.y = fconvert.s(x87_r7_17 + fconvert.t(parcel->world_position.y))
004432f5        float var_14_1 = fconvert.s(fconvert.t(game->__offset(0x3bf920).d) - fconvert.t(parcel->world_position.y))
004432fc        long double x87_r7_24 = fconvert.t(game->__offset(0x3bf924).d) - fconvert.t(parcel->world_position.z)
00443303        var_24 = fconvert.s(fconvert.t(game->__offset(0x3bf91c).d) - fconvert.t(parcel->world_position.x))
0044330b        float var_20_1 = var_14_1
00443317        float var_1c_1 = fconvert.s(x87_r7_24)
0044331b        long double st0_3 = vector_magnitude(&var_24)
00443320        struct Game* game_1 = parcel->game
00443323        parcel->state = 5
0044332a        parcel->target_distance = fconvert.s(st0_3)
0044334a        float var_14_2 = fconvert.s(fconvert.t(parcel->world_position.y) - fconvert.t(game_1->__offset(0x3bf920).d))
00443351        long double x87_r7_31 = fconvert.t(parcel->world_position.z) - fconvert.t(game_1->__offset(0x3bf924).d)
00443358        parcel->travel_dir_x = fconvert.s(fconvert.t(parcel->world_position.x) - fconvert.t(game_1->__offset(0x3bf91c).d))
0044335e        float var_10_2 = fconvert.s(x87_r7_31)
00443362        parcel->travel_dir_y = var_14_2
00443369        parcel->travel_dir_z = var_10_2
0044336c        normalize_vector(&parcel->travel_dir_x)
00443379        label_443379:
00443379        long double x87_r7_35 = fconvert.t(1f) - fconvert.t(parcel->progress)
00443382        void* __offset(Game, 0x3bf91c) eax_12 = &parcel->game->__offset(0x3bf91c).d
0044338b        long double x87_r6_2 = x87_r7_35 * fconvert.t(parcel->target_distance)
004433c3        parcel->world_position.x = fconvert.s(fconvert.t(fconvert.s(x87_r6_2 * fconvert.t(parcel->travel_dir_x))) + fconvert.t((eax_12 - 0x3bf91c)->__offset(0x3bf91c).d))
004433c5        parcel->world_position.y = fconvert.s(fconvert.t(fconvert.s(x87_r6_2 * fconvert.t(parcel->travel_dir_y))) + fconvert.t((eax_12 - 0x3bf91c)->__offset(0x3bf920).d))
004433d9        parcel->world_position.z = fconvert.s(x87_r6_2 * fconvert.t(parcel->travel_dir_z) + fconvert.t((eax_12 - 0x3bf91c)->__offset(0x3bf924).d))
004433e2        *(parcel->sprite + 0x64) = fconvert.s(x87_r7_35 * fconvert.t(0.600000024f) + fconvert.t(0.400000006f))
004433e5        void* sprite = parcel->sprite
004433e8        int32_t ecx_8 = *(sprite + 0x64)
004433eb        *(sprite + 0x60) = ecx_8
004433ee        int32_t var_38_4 = ecx_8
00443400        long double x87_r7_41 = sine(fconvert.s(fconvert.t(parcel->progress) * fconvert.t(3.14159274f))) * fconvert.t(0.5f)
0044340c        void* __offset(Game, 0x3be130) eax_16 = &parcel->game->__offset(0x3be130).d
00443411        int32_t* edx_9 = parcel->sprite + 0x48
00443440        float var_14_4 = fconvert.s(fconvert.t(fconvert.s(x87_r7_41 * fconvert.t((eax_16 - 0x3be130)->__offset(0x3be134).d))) + fconvert.t(parcel->world_position.y))
00443448        long double x87_r7_43 = x87_r7_41 * fconvert.t((eax_16 - 0x3be130)->__offset(0x3be138).d) + fconvert.t(parcel->world_position.z)
0044344b        *edx_9 = fconvert.s(fconvert.t(fconvert.s(x87_r7_41 * fconvert.t((eax_16 - 0x3be130)->__offset(0x3be130).d))) + fconvert.t(parcel->world_position.x))
0044344d        edx_9[1] = var_14_4
00443458        edx_9[2] = fconvert.s(x87_r7_43)
0044345e        long double x87_r7_45 = fconvert.t(parcel->progress_step) + fconvert.t(parcel->progress)
00443461        parcel->progress = fconvert.s(x87_r7_45)
00443464        long double temp1_1 = fconvert.t(1f)
00443464        x87_r7_45 - temp1_1
0044346a        float eax_18
0044346a        eax_18.w = (x87_r7_45 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_45, temp1_1) ? 1 : 0) << 0xa | (x87_r7_45 == temp1_1 ? 1 : 0) << 0xe
0044346f        if ((eax_18:1.b & 0x41) == 0)
00443475        void* sprite_2 = parcel->sprite
00443478        parcel->state = 0
0044347b        kill_sprite(sprite_2)
004431f2        case 5
004431f2        goto label_443379
00443487        case 6
00443487        parcel->progress = 0f
0044348a        parcel->progress_step = 0.0166666675f
00443491        parcel->state = 7
004434b1        parcel->delivery_offset_x = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
004434b7        int32_t eax_20 = next_math_random_value()
004434c0        parcel->delivery_offset_z = 0f
004434dc        parcel->delivery_offset_y = fconvert.s((float.t(eax_20) - fconvert.t(16384f)) * fconvert.t(9.15527344e-05f) + fconvert.t(1f))
004434e2        label_4434e2:
004434e2        struct Game* game_2 = parcel->game
00443505        float var_14_5 = fconvert.s(fconvert.t(game_2->row_event_display.widget_world_y) - fconvert.t(game_2->__offset(0x3bf920).d))
0044350f        long double x87_r7_58 = fconvert.t(game_2->row_event_display.widget_world_z) - fconvert.t(game_2->__offset(0x3bf924).d)
00443519        var_24 = fconvert.s(fconvert.t(game_2->row_event_display.widget_world_x) - fconvert.t(game_2->__offset(0x3bf91c).d))
00443524        float var_10_5 = fconvert.s(x87_r7_58)
0044353f        *(parcel->sprite + 0x64) = fconvert.s(fconvert.t(parcel->progress) * fconvert.t(0.600000024f) + fconvert.t(0.400000006f))
00443542        void* sprite_1 = parcel->sprite
00443548        *(sprite_1 + 0x60) = *(sprite_1 + 0x64)
0044354e        long double x87_r7_62 = fconvert.t(parcel->progress)
00443557        void* __offset(Game, 0x3bf91c) eax_23 = &parcel->game->__offset(0x3bf91c).d
00443583        float var_14_6 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(var_14_5) * x87_r7_62)) + fconvert.t((eax_23 - 0x3bf91c)->__offset(0x3bf920).d))
00443591        float* eax_25 = parcel->sprite + 0x48
00443594        float var_10_6 = fconvert.s(x87_r7_62 * fconvert.t(var_10_5) + fconvert.t((eax_23 - 0x3bf91c)->__offset(0x3bf924).d))
00443598        *eax_25 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(var_24) * x87_r7_62)) + fconvert.t((eax_23 - 0x3bf91c)->__offset(0x3bf91c).d))
0044359e        float var_38_6 = var_10_6
0044359f        eax_25[1] = var_14_6
004435a2        eax_25[2] = var_10_6
004435b1        long double st0_6 = sine(fconvert.s(fconvert.t(parcel->progress) * fconvert.t(3.14159274f)))
004435c4        float* eax_27 = parcel->sprite + 0x48
004435d3        float var_8_4 = fconvert.s(st0_6 * fconvert.t(parcel->delivery_offset_y))
004435d7        long double x87_r7_68 = st0_6 * fconvert.t(parcel->delivery_offset_z)
004435e3        *eax_27 = fconvert.s(fconvert.t(fconvert.s(st0_6 * fconvert.t(parcel->delivery_offset_x))) + fconvert.t(*eax_27))
004435ec        eax_27[1] = fconvert.s(fconvert.t(var_8_4) + fconvert.t(eax_27[1]))
004435f2        eax_27[2] = fconvert.s(x87_r7_68 + fconvert.t(eax_27[2]))
004435f8        long double x87_r7_71 = fconvert.t(parcel->progress_step) + fconvert.t(parcel->progress)
004435fb        parcel->progress = fconvert.s(x87_r7_71)
004435fe        long double temp2_1 = fconvert.t(1f)
004435fe        x87_r7_71 - temp2_1
00443604        eax_27.w = (x87_r7_71 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_71, temp2_1) ? 1 : 0) << 0xa | (x87_r7_71 == temp2_1 ? 1 : 0) << 0xe
00443609        if ((eax_27:1.b & 0x41) == 0)
00443614        register_parcel_delivery(&parcel->game->row_event_display)
00443619        void* sprite_3 = parcel->sprite
0044361c        parcel->state = 0
0044361f        kill_sprite(sprite_3)
004431f2        case 7
004431f2        goto label_4434e2
0044362a        return
