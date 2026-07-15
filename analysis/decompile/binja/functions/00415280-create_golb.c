/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: create_golb @ 0x415280 */

0041528f        shot->skip_one_tick = 0
00415295        shot->slug_bounce_armed = 0
0041529e        if ((shot->..__offset(0x4).d & 0x200) == 0)
004152b4        struct FrameBodBase** eax_2 = &g_game_base->active_bod_list.first
004152b9        struct FrameBodBase* first = (eax_2 - 0x5ac)->active_bod_list.first
004152bd        if (first != 0)
004152cb        first->bod.list_prev = shot
004152ce        struct FrameBodBase* first_1 = (eax_2 - 0x5ac)->active_bod_list.first
004152d3        first_1->bod.list_prev->bod.list_next = first_1
004152d8        struct FrameBodBase* list_prev = (eax_2 - 0x5ac)->active_bod_list.first->bod.list_prev
004152db        (eax_2 - 0x5ac)->active_bod_list.first = list_prev
004152dd        list_prev->bod.list_prev = nullptr
004152bf        (eax_2 - 0x5ac)->active_bod_list.first = shot
004152c1        shot->..__offset(0x8).d = 0
004152c6        (eax_2 - 0x5ac)->active_bod_list.first->bod.list_next = nullptr
004152e0        shot->..__offset(0x4).d |= 0x200
004152a5        report_errorf("List ADD")
004152e7        shot->owner_player = player
004152ed        uint8_t movement_flags = (player->movement_flags).b
004152f5        if ((movement_flags & 7) != 0)
004152f7        shot->kind = 0
00415301        if ((movement_flags & 0x18) != 0)
00415303        shot->kind = 1
00415311        if ((movement_flags & 0x60) != 0)
00415313        shot->kind = 2
00415324        set_matrix_identity(&shot->source_matrix)
00415329        struct Player* owner_player = shot->owner_player
00415335        shot->state = 1
00415347        shot->flight_transform.position.x = owner_player->body.transform.position.x
0041534c        shot->flight_transform.position.y = owner_player->body.transform.position.y
00415352        shot->flight_transform.position.z = owner_player->body.transform.position.z
00415367        struct tColour color
00415367        color.g = fconvert.s(fconvert.t(owner_player->body.transform.basis_forward.y) * fconvert.t(0.5f))
00415374        color.b = fconvert.s(fconvert.t(owner_player->body.transform.basis_forward.z) * fconvert.t(0.5f))
0041537a        shot->flight_transform.position.x = fconvert.s(fconvert.t(owner_player->body.transform.basis_forward.x) * fconvert.t(0.5f) + fconvert.t(shot->flight_transform.position.x))
00415383        shot->flight_transform.position.y = fconvert.s(fconvert.t(color.g) + fconvert.t(shot->flight_transform.position.y))
0041538d        shot->flight_transform.position.z = fconvert.s(fconvert.t(color.b) + fconvert.t(shot->flight_transform.position.z))
00415390        struct Player* owner_player_1 = shot->owner_player
00415396        uint8_t movement_flags_1 = (owner_player_1->movement_flags).b
0041539e        float* eax_8
0041539e        float b
0041539e        if ((movement_flags_1 & 5) != 0)
00415606        struct Vec3 (* edx_15)[0x13]
00415606        if (spawn_selector != 3)
00415613        if (spawn_selector == 2)
00415615        edx_15 = &owner_player_1->presentation.snail_hotspots_world[2]
0041561b        goto label_41562c
00415620        if (spawn_selector == 1)
00415622        edx_15 = &owner_player_1->presentation.snail_hotspots_world[4]
00415622        goto label_41562c
00415608        edx_15 = &owner_player_1->presentation.snail_hotspots_world
0041562c        label_41562c:
0041562c        shot->flight_transform.position.x = (edx_15 - 0x4134)->presentation.snail_hotspots_world[0].x
00415631        shot->flight_transform.position.y = (edx_15 - 0x4134)->presentation.snail_hotspots_world[0].y
00415637        shot->flight_transform.position.z = (edx_15 - 0x4134)->presentation.snail_hotspots_world[0].z
00415643        if ((owner_player_1->movement_flags.b & 4) == 0)
00415724        long double x87_r7_34 = fconvert.t(owner_player_1->velocity.z) + fconvert.t(1f)
0041572a        color.r = 0
00415736        eax_8 = &shot->velocity
0041573c        color.g = 0
00415748        *eax_8 = color.r
0041574a        color.b = fconvert.s(x87_r7_34)
0041574e        b = color.b
00415752        eax_8[1] = 0
00415755        eax_8[2] = b
0041564c        if (spawn_selector == 3)
0041565a        color.r = 0x3dcccccd
0041566c        color.g = 0
00415678        color.b = fconvert.s(fconvert.t(owner_player_1->velocity.z) + fconvert.t(1f))
00415684        shot->velocity.x = color.r
0041568a        shot->velocity.y = 0
0041568d        shot->flight_transform.position.x = fconvert.s(fconvert.t(shot->flight_transform.position.x) + fconvert.t(0.5f))
0041568f        shot->velocity.z = color.b
0041569a        if (spawn_selector != 2)
004156ee        color.r = 0
00415700        color.g = 0
0041570c        shot->velocity.x = color.r
0041570e        color.b = fconvert.s(fconvert.t(owner_player_1->velocity.z) + fconvert.t(1f))
00415716        shot->velocity.y = 0
00415719        shot->velocity.z = color.b
004156a8        color.r = 0xbdcccccd
004156ba        color.g = 0
004156c6        shot->velocity.x = color.r
004156c8        color.b = fconvert.s(fconvert.t(owner_player_1->velocity.z) + fconvert.t(1f))
004156d0        shot->velocity.y = 0
004156d5        shot->velocity.z = color.b
004156de        shot->flight_transform.position.x = fconvert.s(fconvert.t(shot->flight_transform.position.x) - fconvert.t(0.5f))
004153a6        if ((movement_flags_1 & 2) != 0)
004153b3        if (spawn_selector == 2)
004153bf        shot->flight_transform.position.x = owner_player_1->presentation.snail_hotspots_world[0].x
004153c4        shot->flight_transform.position.y = owner_player_1->presentation.snail_hotspots_world[0].y
004153ca        shot->flight_transform.position.z = owner_player_1->presentation.snail_hotspots_world[0].z
004153fc        shot->flight_transform.position.x = fconvert.s(fconvert.t(shot->flight_transform.position.x) + fconvert.t(0.5f))
004153da        if (spawn_selector == 1)
004153e6        shot->flight_transform.position.x = owner_player_1->presentation.snail_hotspots_world[2].x
004153eb        shot->flight_transform.position.y = owner_player_1->presentation.snail_hotspots_world[2].y
004153f1        shot->flight_transform.position.z = owner_player_1->presentation.snail_hotspots_world[2].z
004153fc        shot->flight_transform.position.x = fconvert.s(fconvert.t(shot->flight_transform.position.x) - fconvert.t(0.5f))
00415404        long double x87_r7_11 = fconvert.t(owner_player_1->velocity.z) + fconvert.t(1f)
0041540a        color.r = 0
00415416        eax_8 = &shot->velocity
0041541c        color.g = 0
00415428        *eax_8 = color.r
0041542a        color.b = fconvert.s(x87_r7_11)
0041542e        b = color.b
00415432        eax_8[1] = 0
00415755        eax_8[2] = b
0041543c        if ((movement_flags_1 & 0x18) != 0)
0041554b        if (spawn_selector != 2)
0041558b        shot->flight_transform.position.x = owner_player_1->presentation.snail_hotspots_world[7].x
00415590        shot->flight_transform.position.y = owner_player_1->presentation.snail_hotspots_world[7].y
00415596        shot->flight_transform.position.z = owner_player_1->presentation.snail_hotspots_world[7].z
00415599        long double x87_r7_21 = fconvert.t(owner_player_1->body.transform.basis_forward.z)
0041559c        long double temp1_1 = fconvert.t(0f)
0041559c        x87_r7_21 - temp1_1
004155a7        if ((((x87_r7_21 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp1_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
004155b5        spawn_selector = 0
004155af        spawn_selector = &owner_player_1->presentation.snail_hotspots_world[6].z
00415557        shot->flight_transform.position.x = owner_player_1->presentation.snail_hotspots_world[6].x
0041555c        shot->flight_transform.position.y = owner_player_1->presentation.snail_hotspots_world[6].y
00415562        shot->flight_transform.position.z = owner_player_1->presentation.snail_hotspots_world[6].z
00415565        long double x87_r7_20 = fconvert.t(owner_player_1->body.transform.basis_forward.z)
00415568        long double temp2_1 = fconvert.t(0f)
00415568        x87_r7_20 - temp2_1
00415573        if ((((x87_r7_20 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp2_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
004155b5        spawn_selector = 0
0041557b        spawn_selector = &owner_player_1->presentation.snail_hotspots_world[6].z
004155bf        long double x87_r7_23 = fconvert.t(owner_player_1->velocity.z) + fconvert.t(1f)
004155c5        color.r = 0
004155cd        float r = color.r
004155d7        color.g = 0
004155e3        shot->skip_one_tick = 1
004155ea        shot->velocity.x = r
004155ec        color.b = fconvert.s(x87_r7_23)
004155f4        shot->velocity.y = 0
004155f7        shot->velocity.z = color.b
00415444        if ((movement_flags_1 & 0x60) != 0)
004154f3        color.r = 0
004154fb        color.g = 0
00415505        shot->flight_transform.position.x = owner_player_1->presentation.snail_hotspots_world[0xa].x
0041550a        shot->flight_transform.position.y = owner_player_1->presentation.snail_hotspots_world[0xa].y
00415510        shot->flight_transform.position.z = owner_player_1->presentation.snail_hotspots_world[0xa].z
0041552d        shot->velocity.x = color.r
00415533        color.b = fconvert.s(fconvert.t(owner_player_1->velocity.z) + fconvert.t(0.600000024f))
0041553b        shot->velocity.y = color.g
0041553e        shot->velocity.z = color.b
0041544c        if ((movement_flags_1 & 0x29) != 0)
0041545a        color.r = 0
0041546c        color.g = 0
00415478        shot->velocity.x = color.r
0041547a        color.b = fconvert.s(fconvert.t(owner_player_1->velocity.z) + fconvert.t(1f))
00415482        shot->velocity.y = 0
00415485        shot->velocity.z = color.b
0041548f        if ((movement_flags_1 & 0x52) != 0)
004154a1        color.r = 0
004154b3        color.g = 0
004154bf        shot->velocity.x = color.r
004154c1        color.b = fconvert.s(fconvert.t(owner_player_1->velocity.z) + fconvert.t(1f))
004154c9        shot->velocity.y = 0
004154d0        long double x87_r7_16 = fconvert.t(shot->flight_transform.position.x)
004154d5        shot->velocity.z = color.b
004154d8        if (spawn_selector != 2)
004156de        shot->flight_transform.position.x = fconvert.s(x87_r7_16 - fconvert.t(0.5f))
004154e4        shot->flight_transform.position.x = fconvert.s(x87_r7_16 + fconvert.t(0.5f))
0041575f        if (shot->kind == 1)
00415761        long double x87_r7_35 = fconvert.t(shot->velocity.x)
00415769        shot->velocity.x = fconvert.s(x87_r7_35 + x87_r7_35)
0041576f        long double x87_r7_37 = fconvert.t(shot->velocity.y)
00415777        shot->velocity.y = fconvert.s(x87_r7_37 + x87_r7_37)
0041577d        long double x87_r7_39 = fconvert.t(shot->velocity.z)
00415785        shot->velocity.z = fconvert.s(x87_r7_39 + x87_r7_39)
00415792        if (shot->kind == 2)
004157a0        shot->velocity.x = fconvert.s(fconvert.t(shot->velocity.x) * fconvert.t(0.800000012f))
004157b2        shot->velocity.y = fconvert.s(fconvert.t(shot->velocity.y) * fconvert.t(0.800000012f))
004157c4        shot->velocity.z = fconvert.s(fconvert.t(shot->velocity.z) * fconvert.t(0.800000012f))
004157d8        shot->direction.x = shot->velocity.x
004157dd        shot->direction.y = shot->velocity.y
004157e3        shot->direction.z = shot->velocity.z
004157e6        int32_t kind = shot->kind
004157ee        if (kind == 0)
004159b6        struct SubgameRuntime* game_2 = shot->game
004159bc        struct Player* owner_player_3 = shot->owner_player
004159c2        shot->lifetime = 0f
004159df        shot->lifetime_step = fconvert.s(fconvert.t(game_2->subgame_rate) * fconvert.t(0.0416666679f))
004159ec        struct Sprite* eax_42 = allocate_sprite(&g_sprite_manager, owner_player_3->player_slot, 0x82, 0xffffffff, 0xffffffff)
004159f1        shot->render_body_owner = eax_42
00415a05        eax_42->flags |= SPRITE_FLAG_GAMEPLAY_OWNED
00415a18        *(shot->render_body_owner + 0x68) = 0
00415a2a        *(shot->render_body_owner + 0x6c) = 0
00415a33        *(shot->render_body_owner + 0x78) = 0
00415a36        struct tColour* eax_44 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00415a43        float* ecx_27 = shot->render_body_owner + 0x2c
00415a46        *ecx_27 = eax_44->r
00415a4b        ecx_27[1] = eax_44->g
00415a51        ecx_27[2] = eax_44->b
00415a57        ecx_27[3] = eax_44->a
00415a65        *(shot->render_body_owner + 0x60) = 0x3efae148
00415a70        *(shot->render_body_owner + 0x64) = 0x3efae148
00415a7b        float* eax_47 = shot->render_body_owner + 0x48
00415a7e        *eax_47 = shot->flight_transform.position.x
00415a83        eax_47[1] = shot->flight_transform.position.y
00415a89        eax_47[2] = shot->flight_transform.position.z
00415aab        *(shot->render_body_owner + 0x7c) = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(0.000191747604f))
00415ac7        *(shot->render_body_owner + 0x80) = fconvert.s(fconvert.t(*(shot->game i+ 0x38)) * fconvert.t(0.58177644f))
00415acd        shot->object_ref = emitter_index
004157f5        if (kind == 1)
00415900        struct SubgameRuntime* game_1 = shot->game
00415906        shot->lifetime = 0f
0041591b        shot->..__offset(0x114).d = shot
00415926        shot->lifetime_step = fconvert.s(fconvert.t(game_1->subgame_rate) * fconvert.t(0.0416666679f))
00415932        struct BodBase* eax_37 = &g_game_base->subgame.golb_vapour_list_head
0041593d        if ((0x200 & shot->..__offset(0x84).d) == 0)
0041594e        shot->..__offset(0x88).d = eax_37
00415954        shot->..__offset(0x8c).d = eax_37->bod.list_next
00415957        eax_37->bod.list_next = &shot->..secondary_body.bod.bod.vtable
0041595a        void* eax_38 = shot->..__offset(0x8c).d
0041595f        if (eax_38 != 0)
00415961        *(eax_38 + 8) = &shot->..secondary_body.bod.bod.vtable
00415964        shot->..__offset(0x84).d |= 0x200
00415944        report_errorf("List ADDafter")
0041596e        reset_vapour(&shot->..secondary_body.bod.bod.vtable, spawn_selector)
0041598d        store_color4f(&shot->..secondary_body.bod.color.r, 1f, 1f, 1f, 0.99000001f)
0041599c        shot->object_ref = emitter_index
004159a5        add_vapour_point(&shot->..secondary_body.bod.bod.vtable, &shot->flight_transform)
004159af        (*shot->..__offset(0x80).d)()
004157fc        if (kind == 2)
00415802        struct SubgameRuntime* game = shot->game
00415808        shot->lifetime = 0f
00415811        long double x87_r7_48 = fconvert.t(game->subgame_rate) * fconvert.t(0.0277777761f)
0041581d        shot->rocket_owner_shot = shot
00415823        shot->spin = 0f
00415829        __builtin_strncpy(&shot->spin_step, "PwV>", 4)
00415833        shot->homing_target_object = nullptr
00415839        shot->lifetime_step = fconvert.s(x87_r7_48)
00415845        if (((shot->..__offset(0x11c).d).w:1.b & 2) == 0)
00415856        struct GameRoot* game_base_1 = g_game_base
00415862        struct FrameBodBase* first_2 = game_base_1->active_bod_list.first
0041586a        if (first_2 != 0)
00415878        first_2->bod.list_prev = &shot->..tertiary_body.bod.bod.vtable
0041587b        void* __offset(GolbShot, 0x118) first_3 = game_base_1->active_bod_list.first
00415880        *((first_3 - 0x118)->..__offset(0x120).d + 0xc) = first_3
00415885        void* __offset(GolbShot, 0x118) edx_22 = (game_base_1->active_bod_list.first - 0x118)->..__offset(0x120).d
00415888        game_base_1->active_bod_list.first = edx_22
0041588a        (edx_22 - 0x118)->..__offset(0x120).d = 0
0041586c        game_base_1->active_bod_list.first = &shot->..tertiary_body.bod.bod.vtable
0041586e        shot->..__offset(0x120).d = 0
00415873        (game_base_1->active_bod_list.first - 0x118)->..__offset(0x124).d = 0
0041588d        int32_t eax_34 = shot->..__offset(0x11c).d
00415890        eax_34:1.b |= 2
00415893        shot->..__offset(0x11c).d = eax_34
0041584c        report_errorf("List ADD")
004158a7        shot->object_ref = emitter_index
004158ad        float eax_30 = search_path_for_golb(&shot->game->enemy_manager, &shot->flight_transform.position)
004158b4        if (eax_30 != 0)
004158ba        struct ContactTargetObject* ecx_17 = *(eax_30 i+ 0x14)
004158bd        shot->homing_target_object = ecx_17
004158c7        if (*eax_30 == 0)
004158c9        int32_t list_flags = ecx_17->list_flags
004158cc        list_flags:1.b |= 0x10
004158cf        ecx_17->list_flags = list_flags
004158dd        shot->homing_target.x = *(eax_30 i+ 4)
004158e2        shot->homing_target.y = *(eax_30 i+ 8)
004158e5        eax_30 = *(eax_30 i+ 0xc)
004158e8        shot->homing_blend = 0f
004158ee        shot->homing_target.z = eax_30
004158f1        shot->homing_blend_step = 0.0333333351f
00415ad3        struct Player* owner_player_2 = shot->owner_player
00415ae1        long double x87_r7_58
00415ae1        long double temp6_1
00415ae1        if (owner_player_2->follow_state.active == 1)
00415ae7        x87_r7_58 = fconvert.t(owner_player_2->follow_state.vertical_offset)
00415aed        temp6_1 = fconvert.t(0.5f)
00415aed        x87_r7_58 - temp6_1
00415af8        if (owner_player_2->follow_state.active != 1 || (((x87_r7_58 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_58, temp6_1) ? 1 : 0) << 0xa | (x87_r7_58 == temp6_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00415b67        shot->path_follow.active = 0
00415b6d        shot->path_entry_z_latch = -1f
00415afa        shot->path_follow.active = 1
00415b07        shot->path_follow.template_record = owner_player_2->follow_state.template_record
00415b13        shot->path_follow.source_cell = owner_player_2->follow_state.source_cell
00415b1f        shot->path_follow.sample_index = owner_player_2->follow_state.sample_index
00415b31        shot->path_follow.progress = owner_player_2->follow_state.progress
00415b37        shot->path_follow.vertical_offset = 0f
00415b45        shot->path_follow.output_position.x = owner_player_2->follow_state.output_position.x
00415b4a        shot->path_follow.output_position.y = owner_player_2->follow_state.output_position.y
00415b50        shot->path_follow.shot = shot
00415b56        shot->path_follow.output_position.z = owner_player_2->follow_state.output_position.z
00415b5f        shot->path_entry_z_latch = owner_player_2->follow_state.output_position.z
00415b8d        shot->path_factor = fconvert.s(vector_magnitude(&shot->velocity))
00415b93        shot->previous_flight_transform.position.x = shot->flight_transform.position.x
00415b98        shot->previous_flight_transform.position.y = shot->flight_transform.position.y
00415b9d        shot->previous_flight_transform.position.z = shot->flight_transform.position.z
00415ba2        (*shot->..d)()
00415baa        return
