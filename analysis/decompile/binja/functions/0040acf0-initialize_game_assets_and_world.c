/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_game_assets_and_world @ 0x40acf0 */

0040ad11        store_color4f(&game->fog_color, 1f, 1f, 1f, 1f)
0040ad16        game->fog_density = 1f
0040ad19        game->fog_start = 30f
0040ad20        game->fog_end = 50f
0040ad27        game->fog_enabled = 1
0040ad2e        game->player_count = 2
0040ad35        MemBlock::`default constructor closure'(&game->fade)
0040ad41        game->frontend_link_latch = 0
0040ad47        game->subgame.subgame_pause_gate = 0
0040ad4d        initialize_cheat(&g_cheat_state)
0040ad58        game->intro.hide_for_replay_latch = 0
0040ad60        initialize_blink_random(&game->subgame)
0040ad6c        set_subgame_rate(&game->subgame, 1.10000002f)
0040ad71        game->render_skip_count = 2
0040ad85        game->fixed_update_count = 1
0040ad8c        initialize_texture_list(&g_texture_refs, 0x1f4)
0040ad9b        initialize_object_list(&g_object_list, 0xbb8)
0040ada0        game->unknown_000514 = 0
0040adac        game->fixed_update_accumulator = 0f
0040adb2        game->frame_counter = 0
0040adb8        game->inactive_bod_sentinel.bod.list_next = nullptr
0040adbb        game->active_bod_list.free_top = &game->inactive_bod_sentinel
0040adc1        game->active_bod_list.first = nullptr
0040add3        game->unknown_000b48 = 0
0040add9        __builtin_memset(&g_sprite_depth_buckets, 0, 0x400)
0040addb        game->render_camera_slots[0].sort_key = 0
0040ade7        game->render_camera_slots[0].flags = 0x1000003
0040adf1        game->render_camera_slots[0].source = &game->overlay_0.camera
0040adf7        game->render_camera_slots[0].viewport_x = 0f
0040adfd        game->render_camera_slots[0].viewport_y = 0f
0040ae03        game->render_camera_slots[0].viewport_width = 1f
0040ae09        game->render_camera_slots[0].viewport_height = 1f
0040ae15        game->render_camera_slots[2].draw_world = 0
0040ae26        if (((game->overlay_0.bod.bod.bod.list_flags).w:1.b & 2) == 0)
0040ae3d        struct BodNode** ecx_7 = &g_game_base->active_bod_list.first
0040ae43        struct BodNode* first_5 = (ecx_7 - 0x5ac)->active_bod_list.first
0040ae47        if (first_5 != 0)
0040ae55        first_5->list_prev = &game->overlay_0
0040ae58        struct BodNode* first = (ecx_7 - 0x5ac)->active_bod_list.first
0040ae5d        first->list_prev->list_next = first
0040ae62        struct BodNode* list_prev = (ecx_7 - 0x5ac)->active_bod_list.first->list_prev
0040ae65        (ecx_7 - 0x5ac)->active_bod_list.first = list_prev
0040ae67        list_prev->list_prev = nullptr
0040ae49        (ecx_7 - 0x5ac)->active_bod_list.first = &game->overlay_0
0040ae4b        game->overlay_0.bod.bod.bod.list_prev = nullptr
0040ae50        (ecx_7 - 0x5ac)->active_bod_list.first->list_next = nullptr
0040ae6a        uint32_t list_flags = (&game->overlay_0 - 0x67c)->overlay_0.bod.bod.bod.list_flags
0040ae6c        list_flags:1.b |= 2
0040ae6f        (&game->overlay_0 - 0x67c)->overlay_0.bod.bod.bod.list_flags = list_flags
0040ae2d        report_errorf("List ADD")
0040ae73        initialize_overlay(&game->overlay_0)
0040ae8a        __builtin_memset(0x74eb18, 0, 0x15c)
0040ae8e        initialize_directx_loader(&game->directx_loader)
0040ae9b        reset_landscape_manager(&game->subgame.landscape_manager)
0040aea6        load_segment_definitions(&game->subgame.sm_tracks)
0040aeb2        load_landscape_script_by_name(&game->subgame.landscape_manager, "Starmap.txt")
0040aebe        load_landscape_script_by_name(&game->subgame.landscape_manager, "Splash.txt")
0040aeca        load_landscape_script_by_name(&game->subgame.landscape_manager, "Help.txt")
0040aed5        game->subgame.level_mode_arg = g_runtime_config.landscape_backdrop_variant_selector
0040aee1        bind_subgame_owner(&game->subgame.gui)
0040aeec        bind_subgame_owner(&game->subgame.thanks_screen)
0040aef7        load_galaxy_layout(&game->subgame.galaxy)
0040af02        initialize_cameraman(&game->subgame.player.cameraman)
0040af0d        open_logo(&game->logo)
0040af1c        initialize_sound_bank(&g_sound_effect_manager, &g_sound_bank_entries)
0040af26        initialize_voice_manager(&g_voice_manager)
0040af31        int16_t x87control = apply_audio_config_volumes(&game->options)
0040af3c        load_level_definitions(&game->subgame.sm_tracks)
0040af52        load_landscape_script_by_name(&g_game_base->subgame.landscape_manager, "Menubg.txt")
0040af62        load_builtin_segment_definitions(&game->subgame.level_definition_scratch, &data_4a63d0)
0040af72        game->render_camera_slots[1].sort_key = 1
0040af7f        game->render_camera_slots[1].flags = 0x2000001
0040af89        attach_render_camera_source(&game->render_camera_slots[1], &game->players[0].camera)
0040af94        game->players[0].camera.render_mask = 0x2000000
0040af9f        game->render_camera_slots[4].sort_key = 1
0040afab        game->render_camera_slots[4].flags = 0x10000003
0040afb5        attach_render_camera_source(&game->render_camera_slots[4], &game->players[1].camera)
0040afba        game->players[1].camera.render_mask = 0x10000000
0040afc4        game->render_camera_slots[3].sort_key = 3
0040afd4        game->render_camera_slots[3].flags = 0x8000003
0040afde        game->render_camera_slots[3].source = &game->overlay_2.camera
0040afe4        game->render_camera_slots[3].viewport_x = 0f
0040afef        game->render_camera_slots[3].viewport_y = 0f
0040aff5        game->render_camera_slots[3].viewport_width = 1f
0040b001        game->render_camera_slots[3].viewport_height = 1f
0040b016        if (((game->overlay_2.bod.bod.bod.list_flags).w:1.b & 2) == 0)
0040b02d        struct Overlay** ecx_30 = &g_game_base->active_bod_list.first
0040b033        struct Overlay* edx_4 = *ecx_30
0040b037        if (edx_4 != 0)
0040b045        edx_4->bod.bod.bod.list_prev = &game->overlay_2
0040b048        struct Overlay* eax_7 = *ecx_30
0040b04d        eax_7->bod.bod.bod.list_prev->list_next = eax_7
0040b052        struct Overlay* list_prev_1 = (*ecx_30)->bod.bod.bod.list_prev
0040b055        *ecx_30 = list_prev_1
0040b057        list_prev_1->bod.bod.bod.list_prev = nullptr
0040b039        *ecx_30 = &game->overlay_2
0040b03b        game->overlay_2.bod.bod.bod.list_prev = nullptr
0040b040        (*ecx_30)->bod.bod.bod.list_next = nullptr
0040b05e        uint32_t list_flags_10 = (&game->overlay_2 - 0x914)->overlay_2.bod.bod.bod.list_flags
0040b060        list_flags_10:1.b |= 2
0040b063        (&game->overlay_2 - 0x914)->overlay_2.bod.bod.bod.list_flags = list_flags_10
0040b01d        report_errorf("List ADD")
0040b067        initialize_overlay(&game->overlay_2)
0040b06c        game->render_camera_slots[2].sort_key = 2
0040b07c        game->render_camera_slots[2].flags = 0x4000003
0040b086        game->render_camera_slots[2].source = &game->overlay_1.camera
0040b092        game->render_camera_slots[2].viewport_x = 0f
0040b09d        game->render_camera_slots[2].viewport_y = 0f
0040b0a5        game->render_camera_slots[2].viewport_width = 1f
0040b0ab        game->render_camera_slots[2].viewport_height = 1f
0040b0be        if (((game->overlay_1.bod.bod.bod.list_flags).w:1.b & 2) == 0)
0040b0cf        struct GameRoot* game_base_1 = g_game_base
0040b0db        struct BodNode* first_4 = game_base_1->active_bod_list.first
0040b0e3        if (first_4 != 0)
0040b0f1        first_4->list_prev = &game->overlay_1
0040b0f4        struct Overlay* first_1 = game_base_1->active_bod_list.first
0040b0f9        first_1->bod.bod.bod.list_prev->list_next = first_1
0040b0fe        struct Overlay* list_prev_2 = game_base_1->active_bod_list.first->vtable.128.bod.bod.list_prev
0040b101        game_base_1->active_bod_list.first = list_prev_2
0040b103        list_prev_2->bod.bod.bod.list_prev = nullptr
0040b0e5        game_base_1->active_bod_list.first = &game->overlay_1
0040b0e7        game->overlay_1.bod.bod.bod.list_prev = nullptr
0040b0ec        game_base_1->active_bod_list.first->vtable.128.bod.bod.list_next = nullptr
0040b10a        uint32_t list_flags_11 = (&game->overlay_1 - 0x7c8)->overlay_1.bod.bod.bod.list_flags
0040b10c        list_flags_11:1.b |= 2
0040b10f        (&game->overlay_1 - 0x7c8)->overlay_1.bod.bod.bod.list_flags = list_flags_11
0040b0c5        report_errorf("List ADD")
0040b113        initialize_overlay(&game->overlay_1)
0040b129        sub_432d20("Objects/Font/Font-menu-hover.tga", 2, 0.75f, 1f)
0040b12f        initialize_font3d_objects(0)
0040b137        initialize_font_wave_state()
0040b141        initialize_sprite_manager(&g_sprite_manager)
0040b153        register_sprite_texture(&g_sprite_manager, "Sprites/Debug.tga", 1, 0)
0040b165        register_sprite_texture(&g_sprite_manager, "Sprites/Overlay.tga", 2, 0)
0040b17b        register_sprite_texture(&g_sprite_manager, "Sprites/Border.tga", 5, 0x400)
0040b191        register_sprite_texture(&g_sprite_manager, "Sprites/Mouse.tga", 0x16, 0x400)
0040b1a7        register_sprite_texture(&g_sprite_manager, "Sprites/Warning.tga", 0x5e, 0x400)
0040b1bd        register_sprite_texture(&g_sprite_manager, "Sprites/Play.tga", 0x1b, 0x400)
0040b1d3        register_sprite_texture(&g_sprite_manager, "Sprites/StarTail.tga", 0x20, 0x400)
0040b1e9        register_sprite_texture(&g_sprite_manager, "Sprites/Jet.tga", 0x21, 0x400)
0040b1ff        register_sprite_texture(&g_sprite_manager, "Sprites/Health.tga", 0x39, 0x400)
0040b215        register_sprite_texture(&g_sprite_manager, "Sprites/DamageGuage.tga", 0x59, 0x400)
0040b22b        register_sprite_texture(&g_sprite_manager, "Sprites/DamageGuageFull.tga", 0x5a, 0x400)
0040b241        register_sprite_texture(&g_sprite_manager, "Sprites/DamageGuageBright.tga", 0x5b, 0x400)
0040b257        register_sprite_texture(&g_sprite_manager, "Sprites/Spark.tga", 0x5c, 0x400)
0040b26d        register_sprite_texture(&g_sprite_manager, "Sprites/Black.tga", 0x5d, 0x400)
0040b283        register_sprite_texture(&g_sprite_manager, "Sprites/BorderGlow.tga", 0x63, 0x400)
0040b299        register_sprite_texture(&g_sprite_manager, "Sprites/Slug000.tga", 0x76, 0x400)
0040b2af        register_sprite_texture(&g_sprite_manager, "Sprites/Slug001.tga", 0x77, 0x400)
0040b2c5        register_sprite_texture(&g_sprite_manager, "Sprites/SlugMask.tga", 0x78, 0x400)
0040b2db        register_sprite_texture(&g_sprite_manager, "Sprites/Parcel000.tga", 0x79, 0x400)
0040b2f1        register_sprite_texture(&g_sprite_manager, "Sprites/ParcelIcon.tga", 0x7a, 0x400)
0040b307        register_sprite_texture(&g_sprite_manager, "Sprites/GarbageA.tga", 0x72, 0x400)
0040b31d        register_sprite_texture(&g_sprite_manager, "Sprites/GarbageB.tga", 0x73, 0x400)
0040b333        register_sprite_texture(&g_sprite_manager, "Sprites/GarbageC.tga", 0x74, 0x400)
0040b349        register_sprite_texture(&g_sprite_manager, "Sprites/GarbageD.tga", 0x75, 0x400)
0040b35f        register_sprite_texture(&g_sprite_manager, "Sprites/Life.tga", 0x7b, 0x400)
0040b375        register_sprite_texture(&g_sprite_manager, "Sprites/JetPack000.tga", 0x7c, 0x400)
0040b38e        register_sprite_texture(&g_sprite_manager, "Sprites/Smoke.tga", 0x80, 0x400)
0040b3a7        register_sprite_texture(&g_sprite_manager, "Sprites/SlugGoo.tga", 0x81, 0x400)
0040b3bd        register_sprite_texture(&g_sprite_manager, "Sprites/SliderBar.tga", 0x24, 0x400)
0040b3d3        register_sprite_texture(&g_sprite_manager, "Sprites/SliderBarFull.tga", 0x25, 0x400)
0040b3e9        register_sprite_texture(&g_sprite_manager, "Sprites/Less.tga", 0x26, 0x400)
0040b3ff        register_sprite_texture(&g_sprite_manager, "Sprites/LessHover.tga", 0x28, 0x400)
0040b415        register_sprite_texture(&g_sprite_manager, "Sprites/LessMask.tga", 0x29, 0x420)
0040b42b        register_sprite_texture(&g_sprite_manager, "Sprites/More.tga", 0x2a, 0x400)
0040b441        register_sprite_texture(&g_sprite_manager, "Sprites/MoreHover.tga", 0x2c, 0x400)
0040b457        register_sprite_texture(&g_sprite_manager, "Sprites/MoreMask.tga", 0x2d, 0x420)
0040b470        register_sprite_texture(&g_sprite_manager, "Sprites/ParticleBlasters.tga", 0x82, 0x400)
0040b489        register_sprite_texture(&g_sprite_manager, "Sprites/ParticleExplode-big.tga", 0x83, 0x400)
0040b4a2        register_sprite_texture(&g_sprite_manager, "Sprites/ParticleExplode-small.tga", 0x84, 0x400)
0040b4bb        register_sprite_texture(&g_sprite_manager, "Sprites/ParticleSlow-big.tga", 0x85, 0x400)
0040b4d4        register_sprite_texture(&g_sprite_manager, "Sprites/ParticleSlow-small.tga", 0x86, 0x400)
0040b4ed        register_sprite_texture(&g_sprite_manager, "Sprites/ParticleRing-big.tga", 0x87, 0x400)
0040b506        register_sprite_texture(&g_sprite_manager, "Sprites/ParticleRing-small.tga", 0x88, 0x400)
0040b51f        register_sprite_texture(&g_sprite_manager, "Sprites/Collision.tga", 0x89, 0x400)
0040b538        register_sprite_texture(&g_sprite_manager, "Galaxy/SpaceMapLogo.tga", 0x8a, 0x400)
0040b551        register_sprite_texture(&g_sprite_manager, "Galaxy/Galaxy000.tga", 0x8b, 0x400)
0040b56a        register_sprite_texture(&g_sprite_manager, "Galaxy/Galaxy001.tga", 0x8c, 0x400)
0040b583        register_sprite_texture(&g_sprite_manager, "Galaxy/Galaxy002.tga", 0x8d, 0x400)
0040b59c        register_sprite_texture(&g_sprite_manager, "Galaxy/Galaxy003.tga", 0x8e, 0x400)
0040b5b5        register_sprite_texture(&g_sprite_manager, "Galaxy/Galaxy004.tga", 0x8f, 0x400)
0040b5ce        register_sprite_texture(&g_sprite_manager, "Galaxy/Galaxy005.tga", 0x90, 0x400)
0040b5e7        register_sprite_texture(&g_sprite_manager, "Galaxy/Galaxy006.tga", 0x91, 0x400)
0040b600        register_sprite_texture(&g_sprite_manager, "Galaxy/Galaxy007.tga", 0x92, 0x400)
0040b619        register_sprite_texture(&g_sprite_manager, "Galaxy/Galaxy008.tga", 0x93, 0x400)
0040b632        register_sprite_texture(&g_sprite_manager, "Galaxy/Galaxy009.tga", 0x94, 0x400)
0040b64b        register_sprite_texture(&g_sprite_manager, "Galaxy/GalaxySelect.tga", 0x95, 0x400)
0040b664        register_sprite_texture(&g_sprite_manager, "Galaxy/LevelSelect.tga", 0x96, 0x400)
0040b67d        register_sprite_texture(&g_sprite_manager, "Galaxy/LevelStar.tga", 0x97, 0x400)
0040b696        register_sprite_texture(&g_sprite_manager, "Galaxy/BorderSpacemap.tga", 0x98, 0x400)
0040b6af        register_sprite_texture(&g_sprite_manager, "Galaxy/Line.tga", 0x99, 0x400)
0040b6c8        register_sprite_texture(&g_sprite_manager, "Galaxy/LineStar.tga", 0x9a, 0x400)
0040b6e1        register_sprite_texture(&g_sprite_manager, "Sprites/Progress-Bar.tga", 0x9b, 0x400)
0040b6fa        register_sprite_texture(&g_sprite_manager, "Sprites/Progress-Bar-lit.tga", 0x9c, 0x400)
0040b713        register_sprite_texture(&g_sprite_manager, "Sprites/Progress-Cursor.tga", 0x9d, 0x400)
0040b72c        register_sprite_texture(&g_sprite_manager, "Sprites/JetPackThrust.tga", 0x9e, 0x400)
0040b745        register_sprite_texture(&g_sprite_manager, "Sprites/Ghost.tga", 0x9f, 0x400)
0040b74a        float x_offset = 0f
0040b80e        long double x87_r7_3
0040b80e        long double temp0_1
0040b756        int32_t eax_14
0040b756        eax_14, x87control = ftol(x87control, fconvert.t(x_offset))
0040b769        void* edi_5 = game + eax_14 * 0x38
0040b779        set_bod_object(edi_5 + 0x44790, add_object_to_list(&g_object_list))
0040b78f        initialize_backdrop_slice_quad(*(edi_5 + 0x447b4), "Objects/World00/Track0.tga", x_offset)
0040b7a8        set_bod_object(edi_5 + 0x44950, add_object_to_list(&g_object_list))
0040b7be        initialize_backdrop_slice_quad(*(edi_5 + 0x44974), "Objects/World00/TrackWarn.tga", x_offset)
0040b7d7        set_bod_object(edi_5 + 0x44b10, add_object_to_list(&g_object_list))
0040b7ed        initialize_backdrop_slice_quad(*(edi_5 + 0x44b34), "Objects/World00/Slide0.tga", x_offset)
0040b7f6        x87_r7_3 = fconvert.t(x_offset) + fconvert.t(1f)
0040b7ff        x_offset = fconvert.s(x87_r7_3)
0040b803        temp0_1 = fconvert.t(8f)
0040b803        x87_r7_3 - temp0_1
0040b80e        do while ((((x87_r7_3 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp0_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0040b818        struct TransformMatrix var_110
0040b818        set_matrix_identity(&var_110)
0040b830        set_bod_object(&game->root_bod_catalog.pillars, add_object_to_list(&g_object_list))
0040b845        load_x_mesh(&game->directx_loader, "pillar1.x", game->root_bod_catalog.pillars[0].object, 1)
0040b84e        var_110.position.x = 0
0040b859        apply_bod_position(&game->root_bod_catalog.pillars, &var_110)
0040b871        set_bod_object(&game->root_bod_catalog.pillars[1].vtable, add_object_to_list(&g_object_list))
0040b886        load_x_mesh(&game->directx_loader, "pillar2.x", game->root_bod_catalog.pillars[1].object, 1)
0040b892        var_110.position.x = 0x3f000000
0040b89a        apply_bod_position(&game->root_bod_catalog.pillars[1], &var_110)
0040b8b2        set_bod_object(&game->root_bod_catalog.pillars[2].vtable, add_object_to_list(&g_object_list))
0040b8c7        load_x_mesh(&game->directx_loader, "pillar3.x", game->root_bod_catalog.pillars[2].object, 1)
0040b8d3        var_110.position.x = 0x3f800000
0040b8db        apply_bod_position(&game->root_bod_catalog.pillars[2], &var_110)
0040b8f3        set_bod_object(&game->root_bod_catalog.pillars[3].vtable, add_object_to_list(&g_object_list))
0040b908        load_x_mesh(&game->directx_loader, "pillar4.x", game->root_bod_catalog.pillars[3].object, 1)
0040b911        var_110.position.x = 0x3fc00000
0040b91c        apply_bod_position(&game->root_bod_catalog.pillars[3], &var_110)
0040b934        set_bod_object(&game->root_bod_catalog.pillars[4].vtable, add_object_to_list(&g_object_list))
0040b949        load_x_mesh(&game->directx_loader, "pillar5.x", game->root_bod_catalog.pillars[4].object, 1)
0040b955        var_110.position.x = 0x40000000
0040b95d        apply_bod_position(&game->root_bod_catalog.pillars[4], &var_110)
0040b975        set_bod_object(&game->root_bod_catalog.pillars[5].vtable, add_object_to_list(&g_object_list))
0040b98a        load_x_mesh(&game->directx_loader, "pillar6.x", game->root_bod_catalog.pillars[5].object, 1)
0040b996        var_110.position.x = 0x40200000
0040b99e        apply_bod_position(&game->root_bod_catalog.pillars[5], &var_110)
0040b9b6        set_bod_object(&game->root_bod_catalog.pillars[6].vtable, add_object_to_list(&g_object_list))
0040b9cb        load_x_mesh(&game->directx_loader, "pillar7.x", game->root_bod_catalog.pillars[6].object, 1)
0040b9d4        var_110.position.x = 0x40400000
0040b9df        apply_bod_position(&game->root_bod_catalog.pillars[6], &var_110)
0040b9f7        set_bod_object(&game->root_bod_catalog.pillars[7].vtable, add_object_to_list(&g_object_list))
0040ba0c        load_x_mesh(&game->directx_loader, "pillar8.x", game->root_bod_catalog.pillars[7].object, 1)
0040ba18        var_110.position.x = 0x40600000
0040ba20        apply_bod_position(&game->root_bod_catalog.pillars[7], &var_110)
0040ba36        set_bod_object(&game->root_bod_catalog.ramp_edges, add_object_to_list(&g_object_list))
0040ba48        initialize_textured_backdrop_quad(game->root_bod_catalog.ramp_edges[0].object, "Objects/Universe/Ramp.tga", 0f)
0040ba56        raise_backdrop_quad_edge_pair(0xffffffff, game->root_bod_catalog.ramp_edges[0].object)
0040ba6f        set_bod_object(&game->root_bod_catalog.ramp_edges[1].vtable, add_object_to_list(&g_object_list))
0040ba81        initialize_textured_backdrop_quad(game->root_bod_catalog.ramp_edges[1].object, "Objects/Universe/Ramp.tga", 0f)
0040ba8e        raise_backdrop_quad_edge_pair(0, game->root_bod_catalog.ramp_edges[1].object)
0040baa7        set_bod_object(&game->root_bod_catalog.ramp_edges[2].vtable, add_object_to_list(&g_object_list))
0040bab9        initialize_textured_backdrop_quad(game->root_bod_catalog.ramp_edges[2].object, "Objects/Universe/Ramp.tga", 0f)
0040bac7        raise_backdrop_quad_edge_pair(1, game->root_bod_catalog.ramp_edges[2].object)
0040bae0        set_bod_object(&game->root_bod_catalog.floor_corners.storage, add_object_to_list(&g_object_list))
0040baf2        initialize_backdrop_corner_quad(0, game->root_bod_catalog.floor_corners.storage[0].object, "Objects/World00/Track0.tga")
0040bb0b        set_bod_object(&game->root_bod_catalog.floor_corners.storage[1].vtable, add_object_to_list(&g_object_list))
0040bb1e        initialize_backdrop_corner_quad(1, game->root_bod_catalog.floor_corners.storage[1].object, "Objects/World00/Track0.tga")
0040bb37        set_bod_object(&game->root_bod_catalog.floor_corners.storage[3].vtable, add_object_to_list(&g_object_list))
0040bb4a        initialize_backdrop_corner_quad(2, game->root_bod_catalog.floor_corners.storage[3].object, "Objects/World00/Track0.tga")
0040bb63        set_bod_object(&game->root_bod_catalog.floor_corners.storage[2].vtable, add_object_to_list(&g_object_list))
0040bb76        initialize_backdrop_corner_quad(3, game->root_bod_catalog.floor_corners.storage[2].object, "Objects/World00/Track0.tga")
0040bb8f        set_bod_object(&game->root_bod_catalog.warning_corners.storage, add_object_to_list(&g_object_list))
0040bba1        initialize_backdrop_corner_quad(0, game->root_bod_catalog.warning_corners.storage[0].object, "Objects/World00/TrackWarn.tga")
0040bbba        set_bod_object(&game->root_bod_catalog.warning_corners.storage[1].vtable, add_object_to_list(&g_object_list))
0040bbcd        initialize_backdrop_corner_quad(1, game->root_bod_catalog.warning_corners.storage[1].object, "Objects/World00/TrackWarn.tga")
0040bbe6        set_bod_object(&game->root_bod_catalog.warning_corners.storage[3].vtable, add_object_to_list(&g_object_list))
0040bbf9        initialize_backdrop_corner_quad(2, game->root_bod_catalog.warning_corners.storage[3].object, "Objects/World00/TrackWarn.tga")
0040bc12        set_bod_object(&game->root_bod_catalog.warning_corners.storage[2].vtable, add_object_to_list(&g_object_list))
0040bc25        initialize_backdrop_corner_quad(3, game->root_bod_catalog.warning_corners.storage[2].object, "Objects/World00/TrackWarn.tga")
0040bc3e        set_bod_object(&game->root_bod_catalog.slide_corners.storage, add_object_to_list(&g_object_list))
0040bc50        initialize_backdrop_corner_quad(0, game->root_bod_catalog.slide_corners.storage[0].object, "Objects/World00/Slide0.tga")
0040bc69        set_bod_object(&game->root_bod_catalog.slide_corners.storage[1].vtable, add_object_to_list(&g_object_list))
0040bc7c        initialize_backdrop_corner_quad(1, game->root_bod_catalog.slide_corners.storage[1].object, "Objects/World00/Slide0.tga")
0040bc95        set_bod_object(&game->root_bod_catalog.slide_corners.storage[3].vtable, add_object_to_list(&g_object_list))
0040bca8        initialize_backdrop_corner_quad(2, game->root_bod_catalog.slide_corners.storage[3].object, "Objects/World00/Slide0.tga")
0040bcc1        set_bod_object(&game->root_bod_catalog.slide_corners.storage[2].vtable, add_object_to_list(&g_object_list))
0040bcd4        initialize_backdrop_corner_quad(3, game->root_bod_catalog.slide_corners.storage[2].object, "Objects/World00/Slide0.tga")
0040bced        set_bod_object(&game->root_bod_catalog.trampoline.vtable, add_object_to_list(&g_object_list))
0040bd02        load_x_mesh(&game->directx_loader, "Tramp.x", game->root_bod_catalog.trampoline.object, 1)
0040bd0d        game->root_bod_catalog.trampoline.object->blend_mode = 6
0040bd1d        struct TextureRef* texture_ref = game->root_bod_catalog.trampoline.object->facequads->texture_ref
0040bd25        texture_ref->flags |= 0x400
0040bd37        set_bod_object(&game->root_bod_catalog.universe_hole.vtable, add_object_to_list(&g_object_list))
0040bd49        initialize_textured_backdrop_quad(game->root_bod_catalog.universe_hole.object, "Objects/Universe/Hole.tga", 0f)
0040bd57        game->root_bod_catalog.universe_hole.object->blend_mode = 5
0040bd67        struct TextureRef* texture_ref_1 = game->root_bod_catalog.universe_hole.object->facequads->texture_ref
0040bd6a        enum TextureRefFlags flags = texture_ref_1->flags
0040bd6c        flags:1.b |= 4
0040bd6f        texture_ref_1->flags = flags
0040bd82        set_bod_object(&game->root_bod_catalog.lazer_model.vtable, add_object_to_list(&g_object_list))
0040bd93        load_object_definition("Objects/Lazer", game->root_bod_catalog.lazer_model.object)
0040bd9b        struct Object** edi_14 = &game->subgame.sub_lazers.slots[0].body.bod.object
0040bda1        int32_t var_128_2 = 0x14
0040be04        bool cond:1_1
0040bdb3        set_bod_object(&edi_14[-9], game->root_bod_catalog.lazer_model.object)
0040bdd1        struct TextureRef* texture_ref_2 = (edi_14 - 0x3cb13c)->subgame.sub_lazers.slots[0].body.bod.object->facequads->texture_ref
0040bdd4        enum TextureRefFlags flags_1 = texture_ref_2->flags
0040bdd6        flags_1:1.b |= 4
0040bdd9        texture_ref_2->flags = flags_1
0040bde4        (edi_14 - 0x3cb13c)->subgame.sub_lazers.slots[0].owner_game = &game->subgame
0040bde7        store_color4f(&edi_14[1], 1f, 1f, 1f, 0.699999988f)
0040bdec        struct Object* object_13 = (edi_14 - 0x3cb13c)->subgame.sub_lazers.slots[0].body.bod.object
0040bdf2        edi_14 = &edi_14[0x2c]
0040bdf8        cond:1_1 = var_128_2 != 1
0040bdf9        object_13->blend_mode = 9
0040be00        var_128_2 -= 1
0040be04        do while (cond:1_1)
0040be17        set_bod_object(&game->root_bod_catalog.salt_model.vtable, add_object_to_list(&g_object_list))
0040be2c        load_x_mesh(&game->directx_loader, "salt.x", game->root_bod_catalog.salt_model.object, 1)
0040be31        struct SubgameRuntime** edi_15 = &game->subgame.salt_hazards.slots[0].owner_game
0040be37        int32_t var_128_3 = 0x28
0040be96        bool cond:2_1
0040be4c        set_bod_object(&edi_15[-0x22], game->root_bod_catalog.salt_model.object)
0040be6e        (edi_15 - 0x3cbf60)->subgame.salt_hazards.slots[0].owner_game = &game->subgame
0040be70        store_color4f(&edi_15[-0x18], 1f, 1f, 1f, 0.899999976f)
0040be78        (edi_15 - 0x3cbf60)->subgame.salt_hazards.slots[0].body.bod.object->blend_mode = 0xc
0040be82        set_matrix_identity(&edi_15[-0x14])
0040be8b        edi_15 = &edi_15[0x26]
0040be91        cond:2_1 = var_128_3 != 1
0040be92        var_128_3 -= 1
0040be96        do while (cond:2_1)
0040be98        int32_t options_flags = 0
0040bf2b        while (options_flags s< 2)
0040bea5        void* edx_29 = options_flags * 0x60 + game
0040bebb        set_bod_object(edx_29 + 0x3cd698, add_object_to_list(&g_object_list))
0040bec2        if (options_flags == 0)
0040bee3        load_x_mesh(&game->directx_loader, "postofficestop.x", game->subgame.banners.slots[0].bod.object, 1)
0040bed2        if (options_flags == 1)
0040bee3        load_x_mesh(&game->directx_loader, "postofficestop.x", game->subgame.banners.slots[1].bod.object, options_flags)
0040befc        *(edx_29 + 0x3cd6b0) = 0
0040bf02        *(edx_29 + 0x3cd6ac) = 0
0040bf08        *(edx_29 + 0x3cd6a8) = 0
0040bf0e        *(((options_flags * 3 + 0x1e6b7) << 5) + game) = &game->subgame
0040bf11        *(edx_29 + 0x3cd6d0) = options_flags
0040bf17        options_flags += 1
0040bf18        *(edx_29 + 0x3cd6f0) = 0
0040bf21        *(edx_29 + 0x3cd6f4) = 0x3be38e38
0040bf40        if (((game->subgame.track_body_list_head.bod.list_flags).w:1.b & 2) == 0)
0040bf51        struct BodNode* first_2 = game->active_bod_list.first
0040bf5f        if (first_2 != 0)
0040bf6d        first_2->list_prev = &game->subgame.track_body_list_head
0040bf70        struct BodBase* first_3 = game->active_bod_list.first
0040bf75        first_3->bod.list_prev->list_next = first_3
0040bf7a        struct BodBase* list_prev_3 = game->active_bod_list.first->vtable.o.list_prev
0040bf7d        game->active_bod_list.first = list_prev_3
0040bf7f        list_prev_3->bod.list_prev = nullptr
0040bf61        game->active_bod_list.first = &game->subgame.track_body_list_head
0040bf63        game->subgame.track_body_list_head.bod.list_prev = nullptr
0040bf68        game->active_bod_list.first->vtable.o.list_next = nullptr
0040bf82        uint32_t list_flags_1 = game->subgame.track_body_list_head.bod.list_flags
0040bf85        list_flags_1:1.b |= 2
0040bf88        game->subgame.track_body_list_head.bod.list_flags = list_flags_1
0040bf47        report_errorf("List ADD")
0040bf9a        if (((game->subgame.barrier_sub_lazer_list_head.bod.list_flags).w:1.b & 2) == 0)
0040bfab        game->subgame.barrier_sub_lazer_list_head.bod.list_prev = &game->subgame.track_body_list_head
0040bfb1        game->subgame.barrier_sub_lazer_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next
0040bfb4        game->subgame.track_body_list_head.bod.list_next = &game->subgame.barrier_sub_lazer_list_head
0040bfb7        struct BodNode* list_next_7 = game->subgame.barrier_sub_lazer_list_head.bod.list_next
0040bfbc        if (list_next_7 != 0)
0040bfbe        list_next_7->list_prev = &game->subgame.barrier_sub_lazer_list_head
0040bfc1        uint32_t list_flags_2 = (&game->subgame.barrier_sub_lazer_list_head - 0x3ca1ec)->subgame.barrier_sub_lazer_list_head.bod.list_flags
0040bfc3        list_flags_2:1.b |= 2
0040bfc6        (&game->subgame.barrier_sub_lazer_list_head - 0x3ca1ec)->subgame.barrier_sub_lazer_list_head.bod.list_flags = list_flags_2
0040bfa1        report_errorf("List ADDafter")
0040bfd7        if (((game->subgame.salt_hazard_list_head.bod.list_flags).w:1.b & 2) == 0)
0040bfe8        game->subgame.salt_hazard_list_head.bod.list_prev = &game->subgame.track_body_list_head
0040bfee        game->subgame.salt_hazard_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next
0040bff1        game->subgame.track_body_list_head.bod.list_next = &game->subgame.salt_hazard_list_head
0040bff4        struct BodNode* list_next = game->subgame.salt_hazard_list_head.bod.list_next
0040bff9        if (list_next != 0)
0040bffb        list_next->list_prev = &game->subgame.salt_hazard_list_head
0040bffe        uint32_t list_flags_3 = (&game->subgame.salt_hazard_list_head - 0x3ca224)->subgame.salt_hazard_list_head.bod.list_flags
0040c000        list_flags_3:1.b |= 2
0040c003        (&game->subgame.salt_hazard_list_head - 0x3ca224)->subgame.salt_hazard_list_head.bod.list_flags = list_flags_3
0040bfde        report_errorf("List ADDafter")
0040c014        if (((game->subgame.golb_vapour_list_head.bod.list_flags).w:1.b & 2) == 0)
0040c025        game->subgame.golb_vapour_list_head.bod.list_prev = &game->subgame.track_body_list_head
0040c02b        game->subgame.golb_vapour_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next
0040c02e        game->subgame.track_body_list_head.bod.list_next = &game->subgame.golb_vapour_list_head
0040c031        struct BodNode* list_next_1 = game->subgame.golb_vapour_list_head.bod.list_next
0040c036        if (list_next_1 != 0)
0040c038        list_next_1->list_prev = &game->subgame.golb_vapour_list_head
0040c03b        uint32_t list_flags_4 = (&game->subgame.golb_vapour_list_head - 0x3ca33c)->subgame.golb_vapour_list_head.bod.list_flags
0040c03d        list_flags_4:1.b |= 2
0040c040        (&game->subgame.golb_vapour_list_head - 0x3ca33c)->subgame.golb_vapour_list_head.bod.list_flags = list_flags_4
0040c01b        report_errorf("List ADDafter")
0040c051        if (((game->subgame.fringe_attachment_list_head.bod.list_flags).w:1.b & 2) == 0)
0040c062        game->subgame.fringe_attachment_list_head.bod.list_prev = &game->subgame.track_body_list_head
0040c068        game->subgame.fringe_attachment_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next
0040c06b        game->subgame.track_body_list_head.bod.list_next = &game->subgame.fringe_attachment_list_head
0040c06e        struct BodNode* list_next_2 = game->subgame.fringe_attachment_list_head.bod.list_next
0040c073        if (list_next_2 != 0)
0040c075        list_next_2->list_prev = &game->subgame.fringe_attachment_list_head
0040c078        uint32_t list_flags_5 = (&game->subgame.fringe_attachment_list_head - 0x3ca17c)->subgame.fringe_attachment_list_head.bod.list_flags
0040c07a        list_flags_5:1.b |= 2
0040c07d        (&game->subgame.fringe_attachment_list_head - 0x3ca17c)->subgame.fringe_attachment_list_head.bod.list_flags = list_flags_5
0040c058        report_errorf("List ADDafter")
0040c08e        if (((game->subgame.special_track_cell_list_head.bod.list_flags).w:1.b & 2) == 0)
0040c09f        game->subgame.special_track_cell_list_head.bod.list_prev = &game->subgame.track_body_list_head
0040c0a5        game->subgame.special_track_cell_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next
0040c0a8        game->subgame.track_body_list_head.bod.list_next = &game->subgame.special_track_cell_list_head
0040c0ab        struct BodNode* list_next_3 = game->subgame.special_track_cell_list_head.bod.list_next
0040c0b0        if (list_next_3 != 0)
0040c0b2        list_next_3->list_prev = &game->subgame.special_track_cell_list_head
0040c0b5        uint32_t list_flags_6 = (&game->subgame.special_track_cell_list_head - 0x3ca2cc)->subgame.special_track_cell_list_head.bod.list_flags
0040c0b7        list_flags_6:1.b |= 2
0040c0ba        (&game->subgame.special_track_cell_list_head - 0x3ca2cc)->subgame.special_track_cell_list_head.bod.list_flags = list_flags_6
0040c095        report_errorf("List ADDafter")
0040c0cb        if (((game->subgame.unknown_bod_355cec.bod.list_flags).w:1.b & 2) == 0)
0040c0dc        game->subgame.unknown_bod_355cec.bod.list_prev = &game->subgame.track_body_list_head
0040c0e2        game->subgame.unknown_bod_355cec.bod.list_next = game->subgame.track_body_list_head.bod.list_next
0040c0e5        game->subgame.track_body_list_head.bod.list_next = &game->subgame.unknown_bod_355cec
0040c0e8        struct BodNode* list_next_4 = game->subgame.unknown_bod_355cec.bod.list_next
0040c0ed        if (list_next_4 != 0)
0040c0ef        list_next_4->list_prev = &game->subgame.unknown_bod_355cec
0040c0f2        uint32_t list_flags_7 = (&game->subgame.unknown_bod_355cec - 0x3ca304)->subgame.unknown_bod_355cec.bod.list_flags
0040c0f4        list_flags_7:1.b |= 2
0040c0f7        (&game->subgame.unknown_bod_355cec - 0x3ca304)->subgame.unknown_bod_355cec.bod.list_flags = list_flags_7
0040c0d2        report_errorf("List ADDafter")
0040c108        if (((game->subgame.landscape_slice_list_head.bod.list_flags).w:1.b & 2) == 0)
0040c119        game->subgame.landscape_slice_list_head.bod.list_prev = &game->subgame.track_body_list_head
0040c11f        game->subgame.landscape_slice_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next
0040c122        game->subgame.track_body_list_head.bod.list_next = &game->subgame.landscape_slice_list_head
0040c125        struct BodNode* list_next_5 = game->subgame.landscape_slice_list_head.bod.list_next
0040c12a        if (list_next_5 != 0)
0040c12c        list_next_5->list_prev = &game->subgame.landscape_slice_list_head
0040c12f        uint32_t list_flags_8 = (&game->subgame.landscape_slice_list_head - 0x3ca25c)->subgame.landscape_slice_list_head.bod.list_flags
0040c131        list_flags_8:1.b |= 2
0040c134        (&game->subgame.landscape_slice_list_head - 0x3ca25c)->subgame.landscape_slice_list_head.bod.list_flags = list_flags_8
0040c10f        report_errorf("List ADDafter")
0040c145        if (((game->subgame.unknown_bod_355c7c.bod.list_flags).w:1.b & 2) == 0)
0040c156        game->subgame.unknown_bod_355c7c.bod.list_prev = &game->subgame.track_body_list_head
0040c15c        game->subgame.unknown_bod_355c7c.bod.list_next = game->subgame.track_body_list_head.bod.list_next
0040c15f        game->subgame.track_body_list_head.bod.list_next = &game->subgame.unknown_bod_355c7c.bod
0040c162        struct BodNode* list_next_6 = game->subgame.unknown_bod_355c7c.bod.list_next
0040c167        if (list_next_6 != 0)
0040c169        list_next_6->list_prev = &game->subgame.unknown_bod_355c7c.bod
0040c16c        uint32_t list_flags_9 = game->subgame.unknown_bod_355c7c.bod.list_flags
0040c16e        list_flags_9:1.b |= 2
0040c171        game->subgame.unknown_bod_355c7c.bod.list_flags = list_flags_9
0040c14c        report_errorf("List ADDafter")
0040c193        set_bod_object(&game->subgame.path_pairs, add_object_to_list(&g_object_list))
0040c1b2        initialize_looptheloop_path_template_pair(&game->subgame.path_pairs, 6f, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040c1bc        game->subgame.path_pairs[0].primary.bod.position.z = 0f
0040c1c2        game->subgame.path_pairs[0].primary.bod.position.y = 0f
0040c1c8        game->subgame.path_pairs[0].primary.bod.position.x = 0
0040c1da        set_bod_object(&game->subgame.path_pairs[0].secondary.bod, add_object_to_list(&g_object_list))
0040c1e6        mirror_path_template_pair_x(&game->subgame.path_pairs[0].secondary, &game->subgame.path_pairs)
0040c1f3        game->subgame.path_pairs[0].secondary.bod.position.z = 0f
0040c1f9        game->subgame.path_pairs[0].secondary.bod.position.y = 0f
0040c1ff        game->subgame.path_pairs[0].secondary.bod.position.x = 0
0040c205        build_track_fringe_mesh(&game->subgame.path_pairs, "Objects/Universe/Fringe.tga", 0f)
0040c216        game->subgame.path_pairs[0].primary.fringe_mesh_bod.position.z = 0f
0040c21c        game->subgame.path_pairs[0].primary.fringe_mesh_bod.position.y = 0f
0040c222        game->subgame.path_pairs[0].primary.fringe_mesh_bod.position.x = 0
0040c228        build_track_fringe_mesh(&game->subgame.path_pairs[0].secondary, "Objects/Universe/Fringe.tga", 0f)
0040c232        game->subgame.path_pairs[0].secondary.fringe_mesh_bod.position.z = 0f
0040c238        game->subgame.path_pairs[0].secondary.fringe_mesh_bod.position.y = 0f
0040c23e        game->subgame.path_pairs[0].secondary.fringe_mesh_bod.position.x = 0
0040c252        set_bod_object(&game->subgame.path_pairs[1].primary.bod, add_object_to_list(&g_object_list))
0040c271        initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[1], 6f, 2, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040c27b        game->subgame.path_pairs[1].primary.bod.position.z = 0f
0040c281        game->subgame.path_pairs[1].primary.bod.position.y = 0f
0040c287        game->subgame.path_pairs[1].primary.bod.position.x = 0
0040c299        set_bod_object(&game->subgame.path_pairs[1].secondary.bod, add_object_to_list(&g_object_list))
0040c2a5        mirror_path_template_pair_x(&game->subgame.path_pairs[1].secondary, &game->subgame.path_pairs[1])
0040c2b2        game->subgame.path_pairs[1].secondary.bod.position.z = 0f
0040c2b8        game->subgame.path_pairs[1].secondary.bod.position.y = 0f
0040c2be        game->subgame.path_pairs[1].secondary.bod.position.x = 0
0040c2c4        build_track_fringe_mesh(&game->subgame.path_pairs[1], "Objects/Universe/Fringe.tga", 0f)
0040c2c9        game->subgame.path_pairs[1].primary.fringe_mesh_bod.position.z = 0f
0040c2cf        game->subgame.path_pairs[1].primary.fringe_mesh_bod.position.y = 0f
0040c2d5        game->subgame.path_pairs[1].primary.fringe_mesh_bod.position.x = 0
0040c2e7        build_track_fringe_mesh(&game->subgame.path_pairs[1].secondary, "Objects/Universe/Fringe.tga", 0f)
0040c2f1        game->subgame.path_pairs[1].secondary.fringe_mesh_bod.position.z = 0f
0040c2f7        game->subgame.path_pairs[1].secondary.fringe_mesh_bod.position.y = 0f
0040c2fd        game->subgame.path_pairs[1].secondary.fringe_mesh_bod.position.x = 0
0040c311        set_bod_object(&game->subgame.path_pairs[2].primary.bod, add_object_to_list(&g_object_list))
0040c330        initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[2], 8f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040c33a        game->subgame.path_pairs[2].primary.bod.position.z = 0f
0040c340        game->subgame.path_pairs[2].primary.bod.position.y = 0f
0040c346        game->subgame.path_pairs[2].primary.bod.position.x = 0
0040c358        set_bod_object(&game->subgame.path_pairs[2].secondary.bod, add_object_to_list(&g_object_list))
0040c364        mirror_path_template_pair_x(&game->subgame.path_pairs[2].secondary, &game->subgame.path_pairs[2])
0040c371        game->subgame.path_pairs[2].secondary.bod.position.z = 0f
0040c377        game->subgame.path_pairs[2].secondary.bod.position.y = 0f
0040c37d        game->subgame.path_pairs[2].secondary.bod.position.x = 0
0040c383        build_track_fringe_mesh(&game->subgame.path_pairs[2], "Objects/Universe/Fringe.tga", 0f)
0040c394        game->subgame.path_pairs[2].primary.fringe_mesh_bod.position.z = 0f
0040c39a        game->subgame.path_pairs[2].primary.fringe_mesh_bod.position.y = 0f
0040c3a0        game->subgame.path_pairs[2].primary.fringe_mesh_bod.position.x = 0
0040c3a6        build_track_fringe_mesh(&game->subgame.path_pairs[2].secondary, "Objects/Universe/Fringe.tga", 0f)
0040c3b0        game->subgame.path_pairs[2].secondary.fringe_mesh_bod.position.z = 0f
0040c3b6        game->subgame.path_pairs[2].secondary.fringe_mesh_bod.position.y = 0f
0040c3bc        game->subgame.path_pairs[2].secondary.fringe_mesh_bod.position.x = 0
0040c3d0        set_bod_object(&game->subgame.path_pairs[6].primary.bod, add_object_to_list(&g_object_list))
0040c3ef        initialize_looptheloopw_path_template_pair(&game->subgame.path_pairs[6], 8f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040c3f9        game->subgame.path_pairs[6].primary.bod.position.z = 0f
0040c3ff        game->subgame.path_pairs[6].primary.bod.position.y = 0f
0040c405        game->subgame.path_pairs[6].primary.bod.position.x = 0
0040c417        set_bod_object(&game->subgame.path_pairs[6].secondary.bod, add_object_to_list(&g_object_list))
0040c423        mirror_path_template_pair_x(&game->subgame.path_pairs[6].secondary, &game->subgame.path_pairs[6])
0040c430        game->subgame.path_pairs[6].secondary.bod.position.z = 0f
0040c436        game->subgame.path_pairs[6].secondary.bod.position.y = 0f
0040c43c        game->subgame.path_pairs[6].secondary.bod.position.x = 0
0040c442        build_track_fringe_mesh(&game->subgame.path_pairs[6], "Objects/Universe/Fringe.tga", 0f)
0040c447        game->subgame.path_pairs[6].primary.fringe_mesh_bod.position.z = 0f
0040c459        game->subgame.path_pairs[6].primary.fringe_mesh_bod.position.y = 0f
0040c45f        game->subgame.path_pairs[6].primary.fringe_mesh_bod.position.x = 0
0040c465        build_track_fringe_mesh(&game->subgame.path_pairs[6].secondary, "Objects/Universe/Fringe.tga", 0f)
0040c46f        game->subgame.path_pairs[6].secondary.fringe_mesh_bod.position.z = 0f
0040c475        game->subgame.path_pairs[6].secondary.fringe_mesh_bod.position.y = 0f
0040c47b        game->subgame.path_pairs[6].secondary.fringe_mesh_bod.position.x = 0
0040c48f        set_bod_object(&game->subgame.path_pairs[3].primary.bod, add_object_to_list(&g_object_list))
0040c4ae        initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[3], 3f, 2, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040c4b8        game->subgame.path_pairs[3].primary.bod.position.z = 0f
0040c4be        game->subgame.path_pairs[3].primary.bod.position.y = 0f
0040c4c4        game->subgame.path_pairs[3].primary.bod.position.x = 0
0040c4d6        set_bod_object(&game->subgame.path_pairs[3].secondary.bod, add_object_to_list(&g_object_list))
0040c4e2        mirror_path_template_pair_x(&game->subgame.path_pairs[3].secondary, &game->subgame.path_pairs[3])
0040c4ef        game->subgame.path_pairs[3].secondary.bod.position.z = 0f
0040c4f5        game->subgame.path_pairs[3].secondary.bod.position.y = 0f
0040c4fb        game->subgame.path_pairs[3].secondary.bod.position.x = 0
0040c501        build_track_fringe_mesh(&game->subgame.path_pairs[3], "Objects/Universe/Fringe.tga", 0f)
0040c512        game->subgame.path_pairs[3].primary.fringe_mesh_bod.position.z = 0f
0040c518        game->subgame.path_pairs[3].primary.fringe_mesh_bod.position.y = 0f
0040c51e        game->subgame.path_pairs[3].primary.fringe_mesh_bod.position.x = 0
0040c524        build_track_fringe_mesh(&game->subgame.path_pairs[3].secondary, "Objects/Universe/Fringe.tga", 0f)
0040c52e        game->subgame.path_pairs[3].secondary.fringe_mesh_bod.position.z = 0f
0040c534        game->subgame.path_pairs[3].secondary.fringe_mesh_bod.position.y = 0f
0040c53a        game->subgame.path_pairs[3].secondary.fringe_mesh_bod.position.x = 0
0040c54e        set_bod_object(&game->subgame.path_pairs[4].primary.bod, add_object_to_list(&g_object_list))
0040c56d        initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[4], 3f, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040c577        game->subgame.path_pairs[4].primary.bod.position.z = 0f
0040c57d        game->subgame.path_pairs[4].primary.bod.position.y = 0f
0040c583        game->subgame.path_pairs[4].primary.bod.position.x = 0
0040c595        set_bod_object(&game->subgame.path_pairs[4].secondary.bod, add_object_to_list(&g_object_list))
0040c5a1        mirror_path_template_pair_x(&game->subgame.path_pairs[4].secondary, &game->subgame.path_pairs[4])
0040c5a7        game->subgame.path_pairs[4].secondary.bod.position.z = 0f
0040c5ad        game->subgame.path_pairs[4].secondary.bod.position.y = 0f
0040c5b3        game->subgame.path_pairs[4].secondary.bod.position.x = 0
0040c5c0        build_track_fringe_mesh(&game->subgame.path_pairs[4], "Objects/Universe/Fringe.tga", 0f)
0040c5d1        game->subgame.path_pairs[4].primary.fringe_mesh_bod.position.z = 0f
0040c5d7        game->subgame.path_pairs[4].primary.fringe_mesh_bod.position.y = 0f
0040c5dd        game->subgame.path_pairs[4].primary.fringe_mesh_bod.position.x = 0
0040c5e3        build_track_fringe_mesh(&game->subgame.path_pairs[4].secondary, "Objects/Universe/Fringe.tga", 0f)
0040c5ed        game->subgame.path_pairs[4].secondary.fringe_mesh_bod.position.z = 0f
0040c5f3        game->subgame.path_pairs[4].secondary.fringe_mesh_bod.position.y = 0f
0040c5f9        game->subgame.path_pairs[4].secondary.fringe_mesh_bod.position.x = 0
0040c60d        set_bod_object(&game->subgame.path_pairs[5].primary.bod, add_object_to_list(&g_object_list))
0040c62c        initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[5], 3f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040c636        game->subgame.path_pairs[5].primary.bod.position.z = 0f
0040c63c        game->subgame.path_pairs[5].primary.bod.position.y = 0f
0040c642        game->subgame.path_pairs[5].primary.bod.position.x = 0
0040c654        set_bod_object(&game->subgame.path_pairs[5].secondary.bod, add_object_to_list(&g_object_list))
0040c660        mirror_path_template_pair_x(&game->subgame.path_pairs[5].secondary, &game->subgame.path_pairs[5])
0040c66d        game->subgame.path_pairs[5].secondary.bod.position.z = 0f
0040c673        game->subgame.path_pairs[5].secondary.bod.position.y = 0f
0040c679        game->subgame.path_pairs[5].secondary.bod.position.x = 0
0040c67f        build_track_fringe_mesh(&game->subgame.path_pairs[5], "Objects/Universe/Fringe.tga", 0f)
0040c690        game->subgame.path_pairs[5].primary.fringe_mesh_bod.position.z = 0f
0040c696        game->subgame.path_pairs[5].primary.fringe_mesh_bod.position.y = 0f
0040c69c        game->subgame.path_pairs[5].primary.fringe_mesh_bod.position.x = 0
0040c6a2        build_track_fringe_mesh(&game->subgame.path_pairs[5].secondary, "Objects/Universe/Fringe.tga", 0f)
0040c6ac        game->subgame.path_pairs[5].secondary.fringe_mesh_bod.position.z = 0f
0040c6b2        game->subgame.path_pairs[5].secondary.fringe_mesh_bod.position.y = 0f
0040c6b8        game->subgame.path_pairs[5].secondary.fringe_mesh_bod.position.x = 0
0040c6cc        set_bod_object(&game->subgame.path_pairs[7].primary.bod, add_object_to_list(&g_object_list))
0040c6eb        initialize_loopbow_path_template_pair(&game->subgame.path_pairs[7], 6f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040c6f5        game->subgame.path_pairs[7].primary.bod.position.z = 0f
0040c6fb        game->subgame.path_pairs[7].primary.bod.position.y = 0f
0040c701        game->subgame.path_pairs[7].primary.bod.position.x = 0
0040c713        set_bod_object(&game->subgame.path_pairs[7].secondary.bod, add_object_to_list(&g_object_list))
0040c71f        mirror_path_template_pair_x(&game->subgame.path_pairs[7].secondary, &game->subgame.path_pairs[7])
0040c724        game->subgame.path_pairs[7].secondary.bod.position.z = 0f
0040c72a        game->subgame.path_pairs[7].secondary.bod.position.y = 0f
0040c738        game->subgame.path_pairs[7].secondary.bod.position.x = 0
0040c73e        build_track_fringe_mesh(&game->subgame.path_pairs[7], "Objects/Universe/Fringe.tga", 0f)
0040c74f        game->subgame.path_pairs[7].primary.fringe_mesh_bod.position.z = 0f
0040c755        game->subgame.path_pairs[7].primary.fringe_mesh_bod.position.y = 0f
0040c75b        game->subgame.path_pairs[7].primary.fringe_mesh_bod.position.x = 0
0040c761        build_track_fringe_mesh(&game->subgame.path_pairs[7].secondary, "Objects/Universe/Fringe.tga", 0f)
0040c76b        game->subgame.path_pairs[7].secondary.fringe_mesh_bod.position.z = 0f
0040c771        game->subgame.path_pairs[7].secondary.fringe_mesh_bod.position.y = 0f
0040c777        game->subgame.path_pairs[7].secondary.fringe_mesh_bod.position.x = 0
0040c78b        set_bod_object(&game->subgame.path_pairs[0x25].primary.bod, add_object_to_list(&g_object_list))
0040c7aa        initialize_turnover_path_template_pair(&game->subgame.path_pairs[0x25], 6f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040c7b4        game->subgame.path_pairs[0x25].primary.bod.position.z = 0f
0040c7ba        game->subgame.path_pairs[0x25].primary.bod.position.y = 0f
0040c7c0        game->subgame.path_pairs[0x25].primary.bod.position.x = 0
0040c7d2        set_bod_object(&game->subgame.path_pairs[0x25].secondary.bod, add_object_to_list(&g_object_list))
0040c7de        mirror_path_template_pair_x(&game->subgame.path_pairs[0x25].secondary, &game->subgame.path_pairs[0x25])
0040c7eb        game->subgame.path_pairs[0x25].secondary.bod.position.z = 0f
0040c7f1        game->subgame.path_pairs[0x25].secondary.bod.position.y = 0f
0040c7f7        game->subgame.path_pairs[0x25].secondary.bod.position.x = 0
0040c7fd        build_track_fringe_mesh(&game->subgame.path_pairs[0x25], "Objects/Universe/Fringe.tga", 0f)
0040c80e        game->subgame.path_pairs[0x25].primary.fringe_mesh_bod.position.z = 0f
0040c814        game->subgame.path_pairs[0x25].primary.fringe_mesh_bod.position.y = 0f
0040c81a        game->subgame.path_pairs[0x25].primary.fringe_mesh_bod.position.x = 0
0040c820        build_track_fringe_mesh(&game->subgame.path_pairs[0x25].secondary, "Objects/Universe/Fringe.tga", 0f)
0040c82a        game->subgame.path_pairs[0x25].secondary.fringe_mesh_bod.position.z = 0f
0040c830        game->subgame.path_pairs[0x25].secondary.fringe_mesh_bod.position.y = 0f
0040c836        game->subgame.path_pairs[0x25].secondary.fringe_mesh_bod.position.x = 0
0040c84a        set_bod_object(&game->subgame.path_pairs[0x26].primary.bod, add_object_to_list(&g_object_list))
0040c869        initialize_turnoverdouble_path_template_pair(&game->subgame.path_pairs[0x26], 6f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040c873        game->subgame.path_pairs[0x26].primary.bod.position.z = 0f
0040c879        game->subgame.path_pairs[0x26].primary.bod.position.y = 0f
0040c87f        game->subgame.path_pairs[0x26].primary.bod.position.x = 0
0040c891        set_bod_object(&game->subgame.path_pairs[0x26].secondary.bod, add_object_to_list(&g_object_list))
0040c89d        mirror_path_template_pair_x(&game->subgame.path_pairs[0x26].secondary, &game->subgame.path_pairs[0x26])
0040c8aa        game->subgame.path_pairs[0x26].secondary.bod.position.z = 0f
0040c8b0        game->subgame.path_pairs[0x26].secondary.bod.position.y = 0f
0040c8b6        game->subgame.path_pairs[0x26].secondary.bod.position.x = 0
0040c8bc        build_track_fringe_mesh(&game->subgame.path_pairs[0x26], "Objects/Universe/Fringe.tga", 0f)
0040c8cd        game->subgame.path_pairs[0x26].primary.fringe_mesh_bod.position.z = 0f
0040c8d3        game->subgame.path_pairs[0x26].primary.fringe_mesh_bod.position.y = 0f
0040c8d9        game->subgame.path_pairs[0x26].primary.fringe_mesh_bod.position.x = 0
0040c8df        build_track_fringe_mesh(&game->subgame.path_pairs[0x26].secondary, "Objects/Universe/Fringe.tga", 0f)
0040c8e9        game->subgame.path_pairs[0x26].secondary.fringe_mesh_bod.position.z = 0f
0040c8ef        game->subgame.path_pairs[0x26].secondary.fringe_mesh_bod.position.y = 0f
0040c8f5        game->subgame.path_pairs[0x26].secondary.fringe_mesh_bod.position.x = 0
0040c909        set_bod_object(&game->subgame.path_pairs[0x2b].primary.bod, add_object_to_list(&g_object_list))
0040c928        initialize_twister_path_template_pair(&game->subgame.path_pairs[0x2b], 2.5f, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040c932        game->subgame.path_pairs[0x2b].primary.bod.position.z = 0f
0040c938        game->subgame.path_pairs[0x2b].primary.bod.position.y = 0f
0040c93e        game->subgame.path_pairs[0x2b].primary.bod.position.x = 0
0040c950        set_bod_object(&game->subgame.path_pairs[0x2b].secondary.bod, add_object_to_list(&g_object_list))
0040c95c        mirror_path_template_pair_x(&game->subgame.path_pairs[0x2b].secondary, &game->subgame.path_pairs[0x2b])
0040c969        game->subgame.path_pairs[0x2b].secondary.bod.position.z = 0f
0040c96f        game->subgame.path_pairs[0x2b].secondary.bod.position.y = 0f
0040c975        game->subgame.path_pairs[0x2b].secondary.bod.position.x = 0
0040c97b        build_track_fringe_mesh(&game->subgame.path_pairs[0x2b], "Objects/Universe/Fringe.tga", 0f)
0040c98c        game->subgame.path_pairs[0x2b].primary.fringe_mesh_bod.position.z = 0f
0040c992        game->subgame.path_pairs[0x2b].primary.fringe_mesh_bod.position.y = 0f
0040c998        game->subgame.path_pairs[0x2b].primary.fringe_mesh_bod.position.x = 0
0040c99e        build_track_fringe_mesh(&game->subgame.path_pairs[0x2b].secondary, "Objects/Universe/Fringe.tga", 0f)
0040c9a8        game->subgame.path_pairs[0x2b].secondary.fringe_mesh_bod.position.z = 0f
0040c9ae        game->subgame.path_pairs[0x2b].secondary.fringe_mesh_bod.position.y = 0f
0040c9b4        game->subgame.path_pairs[0x2b].secondary.fringe_mesh_bod.position.x = 0
0040c9c8        set_bod_object(&game->subgame.path_pairs[0x2c].primary.bod, add_object_to_list(&g_object_list))
0040c9e6        initialize_twister_path_template_pair(&game->subgame.path_pairs[0x2c], 2.5f, 3, 0, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040c9f0        game->subgame.path_pairs[0x2c].primary.bod.position.z = 0f
0040c9f6        game->subgame.path_pairs[0x2c].primary.bod.position.y = 0f
0040c9fc        game->subgame.path_pairs[0x2c].primary.bod.position.x = 0
0040ca0e        set_bod_object(&game->subgame.path_pairs[0x2c].secondary.bod, add_object_to_list(&g_object_list))
0040ca1a        mirror_path_template_pair_x(&game->subgame.path_pairs[0x2c].secondary, &game->subgame.path_pairs[0x2c])
0040ca27        game->subgame.path_pairs[0x2c].secondary.bod.position.z = 0f
0040ca2d        game->subgame.path_pairs[0x2c].secondary.bod.position.y = 0f
0040ca33        game->subgame.path_pairs[0x2c].secondary.bod.position.x = 0
0040ca39        build_track_fringe_mesh(&game->subgame.path_pairs[0x2c], "Objects/Universe/Fringe.tga", 0f)
0040ca4a        game->subgame.path_pairs[0x2c].primary.fringe_mesh_bod.position.z = 0f
0040ca50        game->subgame.path_pairs[0x2c].primary.fringe_mesh_bod.position.y = 0f
0040ca56        game->subgame.path_pairs[0x2c].primary.fringe_mesh_bod.position.x = 0
0040ca5c        build_track_fringe_mesh(&game->subgame.path_pairs[0x2c].secondary, "Objects/Universe/Fringe.tga", 0f)
0040ca66        game->subgame.path_pairs[0x2c].secondary.fringe_mesh_bod.position.z = 0f
0040ca6c        game->subgame.path_pairs[0x2c].secondary.fringe_mesh_bod.position.y = 0f
0040ca72        game->subgame.path_pairs[0x2c].secondary.fringe_mesh_bod.position.x = 0
0040ca86        set_bod_object(&game->subgame.path_pairs[0x2d].primary.bod, add_object_to_list(&g_object_list))
0040caa5        initialize_twister2_path_template_pair(&game->subgame.path_pairs[0x2d], 2.5f, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040caaf        game->subgame.path_pairs[0x2d].primary.bod.position.z = 0f
0040cab5        game->subgame.path_pairs[0x2d].primary.bod.position.y = 0f
0040cabb        game->subgame.path_pairs[0x2d].primary.bod.position.x = 0
0040cacd        set_bod_object(&game->subgame.path_pairs[0x2d].secondary.bod, add_object_to_list(&g_object_list))
0040cad9        mirror_path_template_pair_x(&game->subgame.path_pairs[0x2d].secondary, &game->subgame.path_pairs[0x2d])
0040cae6        game->subgame.path_pairs[0x2d].secondary.bod.position.z = 0f
0040caec        game->subgame.path_pairs[0x2d].secondary.bod.position.y = 0f
0040caf2        game->subgame.path_pairs[0x2d].secondary.bod.position.x = 0
0040caf8        build_track_fringe_mesh(&game->subgame.path_pairs[0x2d], "Objects/Universe/Fringe.tga", 0f)
0040cb09        game->subgame.path_pairs[0x2d].primary.fringe_mesh_bod.position.z = 0f
0040cb0f        game->subgame.path_pairs[0x2d].primary.fringe_mesh_bod.position.y = 0f
0040cb15        game->subgame.path_pairs[0x2d].primary.fringe_mesh_bod.position.x = 0
0040cb1b        build_track_fringe_mesh(&game->subgame.path_pairs[0x2d].secondary, "Objects/Universe/Fringe.tga", 0f)
0040cb25        game->subgame.path_pairs[0x2d].secondary.fringe_mesh_bod.position.z = 0f
0040cb2b        game->subgame.path_pairs[0x2d].secondary.fringe_mesh_bod.position.y = 0f
0040cb31        game->subgame.path_pairs[0x2d].secondary.fringe_mesh_bod.position.x = 0
0040cb45        set_bod_object(&game->subgame.path_pairs[0x2e].primary.bod, add_object_to_list(&g_object_list))
0040cb63        initialize_twister2_path_template_pair(&game->subgame.path_pairs[0x2e], 2.5f, 3, 0, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040cb68        game->subgame.path_pairs[0x2e].primary.bod.position.z = 0f
0040cb6e        game->subgame.path_pairs[0x2e].primary.bod.position.y = 0f
0040cb74        game->subgame.path_pairs[0x2e].primary.bod.position.x = 0
0040cb8b        set_bod_object(&game->subgame.path_pairs[0x2e].secondary.bod, add_object_to_list(&g_object_list))
0040cb97        mirror_path_template_pair_x(&game->subgame.path_pairs[0x2e].secondary, &game->subgame.path_pairs[0x2e])
0040cba4        game->subgame.path_pairs[0x2e].secondary.bod.position.z = 0f
0040cbaa        game->subgame.path_pairs[0x2e].secondary.bod.position.y = 0f
0040cbb0        game->subgame.path_pairs[0x2e].secondary.bod.position.x = 0
0040cbb6        build_track_fringe_mesh(&game->subgame.path_pairs[0x2e], "Objects/Universe/Fringe.tga", 0f)
0040cbc7        game->subgame.path_pairs[0x2e].primary.fringe_mesh_bod.position.z = 0f
0040cbcd        game->subgame.path_pairs[0x2e].primary.fringe_mesh_bod.position.y = 0f
0040cbd3        game->subgame.path_pairs[0x2e].primary.fringe_mesh_bod.position.x = 0
0040cbd9        build_track_fringe_mesh(&game->subgame.path_pairs[0x2e].secondary, "Objects/Universe/Fringe.tga", 0f)
0040cbe3        game->subgame.path_pairs[0x2e].secondary.fringe_mesh_bod.position.z = 0f
0040cbe9        game->subgame.path_pairs[0x2e].secondary.fringe_mesh_bod.position.y = 0f
0040cbef        game->subgame.path_pairs[0x2e].secondary.fringe_mesh_bod.position.x = 0
0040cc03        set_bod_object(&game->subgame.path_pairs[0x27].primary.bod, add_object_to_list(&g_object_list))
0040cc22        initialize_turnunder_path_template_pair(&game->subgame.path_pairs[0x27], 6f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040cc2c        game->subgame.path_pairs[0x27].primary.bod.position.z = 0f
0040cc32        game->subgame.path_pairs[0x27].primary.bod.position.y = 0f
0040cc38        game->subgame.path_pairs[0x27].primary.bod.position.x = 0
0040cc4a        set_bod_object(&game->subgame.path_pairs[0x27].secondary.bod, add_object_to_list(&g_object_list))
0040cc56        mirror_path_template_pair_x(&game->subgame.path_pairs[0x27].secondary, &game->subgame.path_pairs[0x27])
0040cc63        game->subgame.path_pairs[0x27].secondary.bod.position.z = 0f
0040cc69        game->subgame.path_pairs[0x27].secondary.bod.position.y = 0f
0040cc6f        game->subgame.path_pairs[0x27].secondary.bod.position.x = 0
0040cc75        build_track_fringe_mesh(&game->subgame.path_pairs[0x27], "Objects/Universe/Fringe.tga", 0f)
0040cc86        game->subgame.path_pairs[0x27].primary.fringe_mesh_bod.position.z = 0f
0040cc8c        game->subgame.path_pairs[0x27].primary.fringe_mesh_bod.position.y = 0f
0040cc92        game->subgame.path_pairs[0x27].primary.fringe_mesh_bod.position.x = 0
0040cc98        build_track_fringe_mesh(&game->subgame.path_pairs[0x27].secondary, "Objects/Universe/Fringe.tga", 0f)
0040cca2        game->subgame.path_pairs[0x27].secondary.fringe_mesh_bod.position.z = 0f
0040cca8        game->subgame.path_pairs[0x27].secondary.fringe_mesh_bod.position.y = 0f
0040ccae        game->subgame.path_pairs[0x27].secondary.fringe_mesh_bod.position.x = 0
0040ccc2        set_bod_object(&game->subgame.path_pairs[0x29].primary.bod, add_object_to_list(&g_object_list))
0040cce1        initialize_invert_path_template_pair(&game->subgame.path_pairs[0x29], 6f, 8, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040cce6        game->subgame.path_pairs[0x29].primary.bod.position.z = 0f
0040ccf1        game->subgame.path_pairs[0x29].primary.bod.position.y = 0f
0040ccf7        game->subgame.path_pairs[0x29].primary.bod.position.x = 0
0040cd09        set_bod_object(&game->subgame.path_pairs[0x29].secondary.bod, add_object_to_list(&g_object_list))
0040cd15        mirror_path_template_pair_x(&game->subgame.path_pairs[0x29].secondary, &game->subgame.path_pairs[0x29])
0040cd22        game->subgame.path_pairs[0x29].secondary.bod.position.z = 0f
0040cd28        game->subgame.path_pairs[0x29].secondary.bod.position.y = 0f
0040cd2e        game->subgame.path_pairs[0x29].secondary.bod.position.x = 0
0040cd34        build_track_fringe_mesh(&game->subgame.path_pairs[0x29], "Objects/Universe/Fringe.tga", 0f)
0040cd45        game->subgame.path_pairs[0x29].primary.fringe_mesh_bod.position.z = 0f
0040cd4b        game->subgame.path_pairs[0x29].primary.fringe_mesh_bod.position.y = 0f
0040cd51        game->subgame.path_pairs[0x29].primary.fringe_mesh_bod.position.x = 0
0040cd57        build_track_fringe_mesh(&game->subgame.path_pairs[0x29].secondary, "Objects/Universe/Fringe.tga", 0f)
0040cd61        game->subgame.path_pairs[0x29].secondary.fringe_mesh_bod.position.z = 0f
0040cd67        game->subgame.path_pairs[0x29].secondary.fringe_mesh_bod.position.y = 0f
0040cd6d        game->subgame.path_pairs[0x29].secondary.fringe_mesh_bod.position.x = 0
0040cd81        set_bod_object(&game->subgame.path_pairs[0x2a].primary.bod, add_object_to_list(&g_object_list))
0040cda0        initialize_halfpipe_path_template_pair(&game->subgame.path_pairs[0x2a], 6f, 8, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040cdaa        game->subgame.path_pairs[0x2a].primary.bod.position.z = 0f
0040cdb0        game->subgame.path_pairs[0x2a].primary.bod.position.y = 0f
0040cdb6        game->subgame.path_pairs[0x2a].primary.bod.position.x = 0
0040cdc8        set_bod_object(&game->subgame.path_pairs[0x2a].secondary.bod, add_object_to_list(&g_object_list))
0040cdd4        mirror_path_template_pair_x(&game->subgame.path_pairs[0x2a].secondary, &game->subgame.path_pairs[0x2a])
0040cde1        game->subgame.path_pairs[0x2a].secondary.bod.position.z = 0f
0040cde7        game->subgame.path_pairs[0x2a].secondary.bod.position.y = 0f
0040cded        game->subgame.path_pairs[0x2a].secondary.bod.position.x = 0
0040cdf3        build_track_fringe_mesh(&game->subgame.path_pairs[0x2a], "Objects/Universe/Fringe.tga", 0f)
0040ce04        game->subgame.path_pairs[0x2a].primary.fringe_mesh_bod.position.z = 0f
0040ce0a        game->subgame.path_pairs[0x2a].primary.fringe_mesh_bod.position.y = 0f
0040ce10        game->subgame.path_pairs[0x2a].primary.fringe_mesh_bod.position.x = 0
0040ce16        build_track_fringe_mesh(&game->subgame.path_pairs[0x2a].secondary, "Objects/Universe/Fringe.tga", 0f)
0040ce20        game->subgame.path_pairs[0x2a].secondary.fringe_mesh_bod.position.z = 0f
0040ce26        game->subgame.path_pairs[0x2a].secondary.fringe_mesh_bod.position.y = 0f
0040ce2c        game->subgame.path_pairs[0x2a].secondary.fringe_mesh_bod.position.x = 0
0040ce40        set_bod_object(&game->subgame.path_pairs[0x28].primary.bod, add_object_to_list(&g_object_list))
0040ce5f        initialize_wibble_path_template_pair(&game->subgame.path_pairs[0x28], 6f, 8, 1, "Objects/World00/Slide0.tga", "Objects/World00/Slide0.tga", "Objects/Path/VeryDark.tga")
0040ce69        game->subgame.path_pairs[0x28].primary.bod.position.z = 0f
0040ce6f        game->subgame.path_pairs[0x28].primary.bod.position.y = 0f
0040ce75        game->subgame.path_pairs[0x28].primary.bod.position.x = 0
0040ce87        set_bod_object(&game->subgame.path_pairs[0x28].secondary.bod, add_object_to_list(&g_object_list))
0040ce93        mirror_path_template_pair_x(&game->subgame.path_pairs[0x28].secondary, &game->subgame.path_pairs[0x28])
0040cea0        game->subgame.path_pairs[0x28].secondary.bod.position.z = 0f
0040cea6        game->subgame.path_pairs[0x28].secondary.bod.position.y = 0f
0040ceac        game->subgame.path_pairs[0x28].secondary.bod.position.x = 0
0040ceb2        build_track_fringe_mesh(&game->subgame.path_pairs[0x28], "Objects/Universe/Fringe.tga", 0f)
0040cec3        game->subgame.path_pairs[0x28].primary.fringe_mesh_bod.position.z = 0f
0040cec9        game->subgame.path_pairs[0x28].primary.fringe_mesh_bod.position.y = 0f
0040cecf        game->subgame.path_pairs[0x28].primary.fringe_mesh_bod.position.x = 0
0040ced5        build_track_fringe_mesh(&game->subgame.path_pairs[0x28].secondary, "Objects/Universe/Fringe.tga", 0f)
0040cedf        game->subgame.path_pairs[0x28].secondary.fringe_mesh_bod.position.z = 0f
0040cee5        game->subgame.path_pairs[0x28].secondary.fringe_mesh_bod.position.y = 0f
0040ceeb        game->subgame.path_pairs[0x28].secondary.fringe_mesh_bod.position.x = 0
0040ceff        set_bod_object(&game->subgame.path_pairs[0x1f].primary.bod, add_object_to_list(&g_object_list))
0040cf23        initialize_supertramp_path_template_pair(&game->subgame.path_pairs[0x1f], 6f, 2, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga", "Objects/World00/TrackWarn.tga")
0040cf2f        game->subgame.path_pairs[0x1f].primary.bod.position.z = 0f
0040cf35        game->subgame.path_pairs[0x1f].primary.bod.position.y = 0f
0040cf3b        game->subgame.path_pairs[0x1f].primary.bod.position.x = 0
0040cf41        build_track_fringe_supertramp_mesh(&game->subgame.path_pairs[0x1f], "Objects/Universe/Fringe.tga")
0040cf4b        game->subgame.path_pairs[0x1f].primary.fringe_mesh_bod.position.z = 0f
0040cf51        game->subgame.path_pairs[0x1f].primary.fringe_mesh_bod.position.y = 0f
0040cf57        game->subgame.path_pairs[0x1f].primary.fringe_mesh_bod.position.x = 0
0040cf6b        set_bod_object(&game->subgame.path_pairs[0x1f].secondary.bod, add_object_to_list(&g_object_list))
0040cf8f        initialize_supertramp_path_template_pair(&game->subgame.path_pairs[0x1f].secondary, 6f, 2, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga", "Objects/World00/TrackWarn.tga")
0040cf9b        game->subgame.path_pairs[0x1f].secondary.bod.position.z = 0f
0040cfa1        game->subgame.path_pairs[0x1f].secondary.bod.position.y = 0f
0040cfa7        game->subgame.path_pairs[0x1f].secondary.bod.position.x = 0
0040cfad        build_track_fringe_supertramp_mesh(&game->subgame.path_pairs[0x1f].secondary, "Objects/Universe/Fringe.tga")
0040cfb7        game->subgame.path_pairs[0x1f].secondary.fringe_mesh_bod.position.z = 0f
0040cfbd        game->subgame.path_pairs[0x1f].secondary.fringe_mesh_bod.position.y = 0f
0040cfc3        game->subgame.path_pairs[0x1f].secondary.fringe_mesh_bod.position.x = 0
0040cfd7        set_bod_object(&game->subgame.path_pairs[0x24].primary.bod, add_object_to_list(&g_object_list))
0040cff6        initialize_start_path_template_pair(&game->subgame.path_pairs[0x24], 4f, 8, 1, "Objects/World00/Slide0.tga", "Objects/World00/Slide0.tga", "Objects/Path/VeryDark.tga")
0040d003        game->subgame.path_pairs[0x24].primary.bod.position.z = 0f
0040d009        game->subgame.path_pairs[0x24].primary.bod.position.y = 0f
0040d00f        game->subgame.path_pairs[0x24].primary.bod.position.x = 0
0040d015        build_track_fringe_mesh(&game->subgame.path_pairs[0x24], "Objects/Universe/Fringe.tga", 0f)
0040d01f        game->subgame.path_pairs[0x24].primary.fringe_mesh_bod.position.z = 0f
0040d025        game->subgame.path_pairs[0x24].primary.fringe_mesh_bod.position.y = 0f
0040d02b        game->subgame.path_pairs[0x24].primary.fringe_mesh_bod.position.x = 0
0040d03f        set_bod_object(&game->subgame.path_pairs[0x24].secondary.bod, add_object_to_list(&g_object_list))
0040d05e        initialize_start_path_template_pair(&game->subgame.path_pairs[0x24].secondary, 4f, 8, 1, "Objects/World00/Slide0.tga", "Objects/World00/Slidex.tga", "Objects/Path/VeryDark.tga")
0040d06b        game->subgame.path_pairs[0x24].secondary.bod.position.z = 0f
0040d071        game->subgame.path_pairs[0x24].secondary.bod.position.y = 0f
0040d077        game->subgame.path_pairs[0x24].secondary.bod.position.x = 0
0040d07d        build_track_fringe_mesh(&game->subgame.path_pairs[0x24].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d087        game->subgame.path_pairs[0x24].secondary.fringe_mesh_bod.position.z = 0f
0040d08d        game->subgame.path_pairs[0x24].secondary.fringe_mesh_bod.position.y = 0f
0040d093        game->subgame.path_pairs[0x24].secondary.fringe_mesh_bod.position.x = 0
0040d0a7        set_bod_object(&game->subgame.path_pairs[0x19].primary.bod, add_object_to_list(&g_object_list))
0040d0c6        initialize_loopout_path_template_pair(&game->subgame.path_pairs[0x19], 3f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040d0d0        game->subgame.path_pairs[0x19].primary.bod.position.z = 0f
0040d0d6        game->subgame.path_pairs[0x19].primary.bod.position.y = 0f
0040d0dc        game->subgame.path_pairs[0x19].primary.bod.position.x = 0
0040d0ee        set_bod_object(&game->subgame.path_pairs[0x19].secondary.bod, add_object_to_list(&g_object_list))
0040d0fa        mirror_path_template_pair_x(&game->subgame.path_pairs[0x19].secondary, &game->subgame.path_pairs[0x19])
0040d107        game->subgame.path_pairs[0x19].secondary.bod.position.z = 0f
0040d10d        game->subgame.path_pairs[0x19].secondary.bod.position.y = 0f
0040d113        game->subgame.path_pairs[0x19].secondary.bod.position.x = 0
0040d119        build_track_fringe_mesh(&game->subgame.path_pairs[0x19], "Objects/Universe/Fringe.tga", 0f)
0040d11e        game->subgame.path_pairs[0x19].primary.fringe_mesh_bod.position.z = 0f
0040d124        game->subgame.path_pairs[0x19].primary.fringe_mesh_bod.position.y = 0f
0040d12a        game->subgame.path_pairs[0x19].primary.fringe_mesh_bod.position.x = 0
0040d13c        build_track_fringe_mesh(&game->subgame.path_pairs[0x19].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d146        game->subgame.path_pairs[0x19].secondary.fringe_mesh_bod.position.z = 0f
0040d14c        game->subgame.path_pairs[0x19].secondary.fringe_mesh_bod.position.y = 0f
0040d152        game->subgame.path_pairs[0x19].secondary.fringe_mesh_bod.position.x = 0
0040d166        set_bod_object(&game->subgame.path_pairs[0x1b].primary.bod, add_object_to_list(&g_object_list))
0040d185        initialize_loopout_path_template_pair(&game->subgame.path_pairs[0x1b], 5f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040d18f        game->subgame.path_pairs[0x1b].primary.bod.position.z = 0f
0040d195        game->subgame.path_pairs[0x1b].primary.bod.position.y = 0f
0040d19b        game->subgame.path_pairs[0x1b].primary.bod.position.x = 0
0040d1ad        set_bod_object(&game->subgame.path_pairs[0x1b].secondary.bod, add_object_to_list(&g_object_list))
0040d1b9        mirror_path_template_pair_x(&game->subgame.path_pairs[0x1b].secondary, &game->subgame.path_pairs[0x1b])
0040d1c6        game->subgame.path_pairs[0x1b].secondary.bod.position.z = 0f
0040d1cc        game->subgame.path_pairs[0x1b].secondary.bod.position.y = 0f
0040d1d2        game->subgame.path_pairs[0x1b].secondary.bod.position.x = 0
0040d1d8        build_track_fringe_mesh(&game->subgame.path_pairs[0x1b], "Objects/Universe/Fringe.tga", 0f)
0040d1e9        game->subgame.path_pairs[0x1b].primary.fringe_mesh_bod.position.z = 0f
0040d1ef        game->subgame.path_pairs[0x1b].primary.fringe_mesh_bod.position.y = 0f
0040d1f5        game->subgame.path_pairs[0x1b].primary.fringe_mesh_bod.position.x = 0
0040d1fb        build_track_fringe_mesh(&game->subgame.path_pairs[0x1b].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d205        game->subgame.path_pairs[0x1b].secondary.fringe_mesh_bod.position.z = 0f
0040d20b        game->subgame.path_pairs[0x1b].secondary.fringe_mesh_bod.position.y = 0f
0040d211        game->subgame.path_pairs[0x1b].secondary.fringe_mesh_bod.position.x = 0
0040d225        set_bod_object(&game->subgame.path_pairs[0x1a].primary.bod, add_object_to_list(&g_object_list))
0040d244        initialize_loopout_path_template_pair(&game->subgame.path_pairs[0x1a], 3f, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040d24e        game->subgame.path_pairs[0x1a].primary.bod.position.z = 0f
0040d254        game->subgame.path_pairs[0x1a].primary.bod.position.y = 0f
0040d25a        game->subgame.path_pairs[0x1a].primary.bod.position.x = 0
0040d26c        set_bod_object(&game->subgame.path_pairs[0x1a].secondary.bod, add_object_to_list(&g_object_list))
0040d278        mirror_path_template_pair_x(&game->subgame.path_pairs[0x1a].secondary, &game->subgame.path_pairs[0x1a])
0040d285        game->subgame.path_pairs[0x1a].secondary.bod.position.z = 0f
0040d28b        game->subgame.path_pairs[0x1a].secondary.bod.position.y = 0f
0040d291        game->subgame.path_pairs[0x1a].secondary.bod.position.x = 0
0040d297        build_track_fringe_mesh(&game->subgame.path_pairs[0x1a], "Objects/Universe/Fringe.tga", 0f)
0040d29c        game->subgame.path_pairs[0x1a].primary.fringe_mesh_bod.position.z = 0f
0040d2ae        game->subgame.path_pairs[0x1a].primary.fringe_mesh_bod.position.y = 0f
0040d2b4        game->subgame.path_pairs[0x1a].primary.fringe_mesh_bod.position.x = 0
0040d2ba        build_track_fringe_mesh(&game->subgame.path_pairs[0x1a].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d2c4        game->subgame.path_pairs[0x1a].secondary.fringe_mesh_bod.position.z = 0f
0040d2ca        game->subgame.path_pairs[0x1a].secondary.fringe_mesh_bod.position.y = 0f
0040d2d0        game->subgame.path_pairs[0x1a].secondary.fringe_mesh_bod.position.x = 0
0040d2e4        set_bod_object(&game->subgame.path_pairs[0x10].primary.bod, add_object_to_list(&g_object_list))
0040d308        initialize_hump_path_template_pair(&game->subgame.path_pairs[0x10], 4f, 1f, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040d312        game->subgame.path_pairs[0x10].primary.bod.position.z = 0f
0040d318        game->subgame.path_pairs[0x10].primary.bod.position.y = 0f
0040d31e        game->subgame.path_pairs[0x10].primary.bod.position.x = 0
0040d330        set_bod_object(&game->subgame.path_pairs[0x10].secondary.bod, add_object_to_list(&g_object_list))
0040d33c        mirror_path_template_pair_x(&game->subgame.path_pairs[0x10].secondary, &game->subgame.path_pairs[0x10])
0040d349        game->subgame.path_pairs[0x10].secondary.bod.position.z = 0f
0040d34f        game->subgame.path_pairs[0x10].secondary.bod.position.y = 0f
0040d355        game->subgame.path_pairs[0x10].secondary.bod.position.x = 0
0040d35b        build_track_fringe_mesh(&game->subgame.path_pairs[0x10], "Objects/Universe/Fringe.tga", 0f)
0040d36c        game->subgame.path_pairs[0x10].primary.fringe_mesh_bod.position.z = 0f
0040d372        game->subgame.path_pairs[0x10].primary.fringe_mesh_bod.position.y = 0f
0040d378        game->subgame.path_pairs[0x10].primary.fringe_mesh_bod.position.x = 0
0040d37e        build_track_fringe_mesh(&game->subgame.path_pairs[0x10].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d388        game->subgame.path_pairs[0x10].secondary.fringe_mesh_bod.position.z = 0f
0040d38e        game->subgame.path_pairs[0x10].secondary.fringe_mesh_bod.position.y = 0f
0040d394        game->subgame.path_pairs[0x10].secondary.fringe_mesh_bod.position.x = 0
0040d3a8        set_bod_object(&game->subgame.path_pairs[0x11].primary.bod, add_object_to_list(&g_object_list))
0040d3cc        initialize_dump_path_template_pair(&game->subgame.path_pairs[0x11], 4f, 1f, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040d3d6        game->subgame.path_pairs[0x11].primary.bod.position.z = 0f
0040d3dc        game->subgame.path_pairs[0x11].primary.bod.position.y = 0f
0040d3e2        game->subgame.path_pairs[0x11].primary.bod.position.x = 0
0040d3f4        set_bod_object(&game->subgame.path_pairs[0x11].secondary.bod, add_object_to_list(&g_object_list))
0040d400        mirror_path_template_pair_x(&game->subgame.path_pairs[0x11].secondary, &game->subgame.path_pairs[0x11])
0040d405        game->subgame.path_pairs[0x11].secondary.bod.position.z = 0f
0040d40b        game->subgame.path_pairs[0x11].secondary.bod.position.y = 0f
0040d411        game->subgame.path_pairs[0x11].secondary.bod.position.x = 0
0040d41f        build_track_fringe_mesh(&game->subgame.path_pairs[0x11], "Objects/Universe/Fringe.tga", 0f)
0040d430        game->subgame.path_pairs[0x11].primary.fringe_mesh_bod.position.z = 0f
0040d436        game->subgame.path_pairs[0x11].primary.fringe_mesh_bod.position.y = 0f
0040d43c        game->subgame.path_pairs[0x11].primary.fringe_mesh_bod.position.x = 0
0040d442        build_track_fringe_mesh(&game->subgame.path_pairs[0x11].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d44c        game->subgame.path_pairs[0x11].secondary.fringe_mesh_bod.position.z = 0f
0040d452        game->subgame.path_pairs[0x11].secondary.fringe_mesh_bod.position.y = 0f
0040d458        game->subgame.path_pairs[0x11].secondary.fringe_mesh_bod.position.x = 0
0040d46c        set_bod_object(&game->subgame.path_pairs[0x12].primary.bod, add_object_to_list(&g_object_list))
0040d490        initialize_hump_path_template_pair(&game->subgame.path_pairs[0x12], 4f, 0.300000012f, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040d49a        game->subgame.path_pairs[0x12].primary.bod.position.z = 0f
0040d4a0        game->subgame.path_pairs[0x12].primary.bod.position.y = 0f
0040d4a6        game->subgame.path_pairs[0x12].primary.bod.position.x = 0
0040d4b8        set_bod_object(&game->subgame.path_pairs[0x12].secondary.bod, add_object_to_list(&g_object_list))
0040d4c4        mirror_path_template_pair_x(&game->subgame.path_pairs[0x12].secondary, &game->subgame.path_pairs[0x12])
0040d4d1        game->subgame.path_pairs[0x12].secondary.bod.position.z = 0f
0040d4d7        game->subgame.path_pairs[0x12].secondary.bod.position.y = 0f
0040d4dd        game->subgame.path_pairs[0x12].secondary.bod.position.x = 0
0040d4e3        build_track_fringe_mesh(&game->subgame.path_pairs[0x12], "Objects/Universe/Fringe.tga", 0f)
0040d4f4        game->subgame.path_pairs[0x12].primary.fringe_mesh_bod.position.z = 0f
0040d4fa        game->subgame.path_pairs[0x12].primary.fringe_mesh_bod.position.y = 0f
0040d500        game->subgame.path_pairs[0x12].primary.fringe_mesh_bod.position.x = 0
0040d506        build_track_fringe_mesh(&game->subgame.path_pairs[0x12].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d510        game->subgame.path_pairs[0x12].secondary.fringe_mesh_bod.position.z = 0f
0040d516        game->subgame.path_pairs[0x12].secondary.fringe_mesh_bod.position.y = 0f
0040d51c        game->subgame.path_pairs[0x12].secondary.fringe_mesh_bod.position.x = 0
0040d530        set_bod_object(&game->subgame.path_pairs[0x13].primary.bod, add_object_to_list(&g_object_list))
0040d554        initialize_dump_path_template_pair(&game->subgame.path_pairs[0x13], 4f, 0.300000012f, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040d55e        game->subgame.path_pairs[0x13].primary.bod.position.z = 0f
0040d564        game->subgame.path_pairs[0x13].primary.bod.position.y = 0f
0040d56a        game->subgame.path_pairs[0x13].primary.bod.position.x = 0
0040d57c        set_bod_object(&game->subgame.path_pairs[0x13].secondary.bod, add_object_to_list(&g_object_list))
0040d588        mirror_path_template_pair_x(&game->subgame.path_pairs[0x13].secondary, &game->subgame.path_pairs[0x13])
0040d595        game->subgame.path_pairs[0x13].secondary.bod.position.z = 0f
0040d59b        game->subgame.path_pairs[0x13].secondary.bod.position.y = 0f
0040d5a1        game->subgame.path_pairs[0x13].secondary.bod.position.x = 0
0040d5a7        build_track_fringe_mesh(&game->subgame.path_pairs[0x13], "Objects/Universe/Fringe.tga", 0f)
0040d5b8        game->subgame.path_pairs[0x13].primary.fringe_mesh_bod.position.z = 0f
0040d5be        game->subgame.path_pairs[0x13].primary.fringe_mesh_bod.position.y = 0f
0040d5c4        game->subgame.path_pairs[0x13].primary.fringe_mesh_bod.position.x = 0
0040d5ca        build_track_fringe_mesh(&game->subgame.path_pairs[0x13].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d5d4        game->subgame.path_pairs[0x13].secondary.fringe_mesh_bod.position.z = 0f
0040d5da        game->subgame.path_pairs[0x13].secondary.fringe_mesh_bod.position.y = 0f
0040d5e0        game->subgame.path_pairs[0x13].secondary.fringe_mesh_bod.position.x = 0
0040d5f4        set_bod_object(&game->subgame.path_pairs[8].primary.bod, add_object_to_list(&g_object_list))
0040d618        initialize_hill_valley_path_template_pair(&game->subgame.path_pairs[8], 8, 4f, 20f, 1, "Objects/World00/Slide0.tga", "Objects/World00/Slide0.tga", "Objects/Path/VeryDark.tga")
0040d622        game->subgame.path_pairs[8].primary.bod.position.z = 0f
0040d628        game->subgame.path_pairs[8].primary.bod.position.y = 0f
0040d62e        game->subgame.path_pairs[8].primary.bod.position.x = 0
0040d640        set_bod_object(&game->subgame.path_pairs[8].secondary.bod, add_object_to_list(&g_object_list))
0040d64c        mirror_path_template_pair_x(&game->subgame.path_pairs[8].secondary, &game->subgame.path_pairs[8])
0040d659        game->subgame.path_pairs[8].secondary.bod.position.z = 0f
0040d65f        game->subgame.path_pairs[8].secondary.bod.position.y = 0f
0040d665        game->subgame.path_pairs[8].secondary.bod.position.x = 0
0040d66b        build_track_fringe_mesh(&game->subgame.path_pairs[8], "Objects/Universe/Fringe.tga", 0f)
0040d67c        game->subgame.path_pairs[8].primary.fringe_mesh_bod.position.z = 0f
0040d682        game->subgame.path_pairs[8].primary.fringe_mesh_bod.position.y = 0f
0040d688        game->subgame.path_pairs[8].primary.fringe_mesh_bod.position.x = 0
0040d68e        build_track_fringe_mesh(&game->subgame.path_pairs[8].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d698        game->subgame.path_pairs[8].secondary.fringe_mesh_bod.position.z = 0f
0040d69e        game->subgame.path_pairs[8].secondary.fringe_mesh_bod.position.y = 0f
0040d6a4        game->subgame.path_pairs[8].secondary.fringe_mesh_bod.position.x = 0
0040d6b8        set_bod_object(&game->subgame.path_pairs[0xa].primary.bod, add_object_to_list(&g_object_list))
0040d6db        initialize_hill_valley_path_template_pair(&game->subgame.path_pairs[0xa], 4, 4f, 20f, 0, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040d6e0        game->subgame.path_pairs[0xa].primary.bod.position.z = 0f
0040d6e6        game->subgame.path_pairs[0xa].primary.bod.position.y = 0f
0040d6ec        game->subgame.path_pairs[0xa].primary.bod.position.x = 0
0040d703        set_bod_object(&game->subgame.path_pairs[0xa].secondary.bod, add_object_to_list(&g_object_list))
0040d70f        mirror_path_template_pair_x(&game->subgame.path_pairs[0xa].secondary, &game->subgame.path_pairs[0xa])
0040d71c        game->subgame.path_pairs[0xa].secondary.bod.position.z = 0f
0040d722        game->subgame.path_pairs[0xa].secondary.bod.position.y = 0f
0040d728        game->subgame.path_pairs[0xa].secondary.bod.position.x = 0
0040d72e        build_track_fringe_mesh(&game->subgame.path_pairs[0xa], "Objects/Universe/Fringe.tga", 0f)
0040d73f        game->subgame.path_pairs[0xa].primary.fringe_mesh_bod.position.z = 0f
0040d745        game->subgame.path_pairs[0xa].primary.fringe_mesh_bod.position.y = 0f
0040d74b        game->subgame.path_pairs[0xa].primary.fringe_mesh_bod.position.x = 0
0040d751        build_track_fringe_mesh(&game->subgame.path_pairs[0xa].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d75b        game->subgame.path_pairs[0xa].secondary.fringe_mesh_bod.position.z = 0f
0040d761        game->subgame.path_pairs[0xa].secondary.fringe_mesh_bod.position.y = 0f
0040d767        game->subgame.path_pairs[0xa].secondary.fringe_mesh_bod.position.x = 0
0040d77b        set_bod_object(&game->subgame.path_pairs[9].primary.bod, add_object_to_list(&g_object_list))
0040d79f        initialize_hill_valley_path_template_pair(&game->subgame.path_pairs[9], 4, 4f, 20f, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040d7a9        game->subgame.path_pairs[9].primary.bod.position.z = 0f
0040d7af        game->subgame.path_pairs[9].primary.bod.position.y = 0f
0040d7b5        game->subgame.path_pairs[9].primary.bod.position.x = 0
0040d7c7        set_bod_object(&game->subgame.path_pairs[9].secondary.bod, add_object_to_list(&g_object_list))
0040d7d3        mirror_path_template_pair_x(&game->subgame.path_pairs[9].secondary, &game->subgame.path_pairs[9])
0040d7e0        game->subgame.path_pairs[9].secondary.bod.position.z = 0f
0040d7e6        game->subgame.path_pairs[9].secondary.bod.position.y = 0f
0040d7ec        game->subgame.path_pairs[9].secondary.bod.position.x = 0
0040d7f2        build_track_fringe_mesh(&game->subgame.path_pairs[9], "Objects/Universe/Fringe.tga", 0f)
0040d803        game->subgame.path_pairs[9].primary.fringe_mesh_bod.position.z = 0f
0040d809        game->subgame.path_pairs[9].primary.fringe_mesh_bod.position.y = 0f
0040d80f        game->subgame.path_pairs[9].primary.fringe_mesh_bod.position.x = 0
0040d815        build_track_fringe_mesh(&game->subgame.path_pairs[9].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d81f        game->subgame.path_pairs[9].secondary.fringe_mesh_bod.position.z = 0f
0040d825        game->subgame.path_pairs[9].secondary.fringe_mesh_bod.position.y = 0f
0040d82b        game->subgame.path_pairs[9].secondary.fringe_mesh_bod.position.x = 0
0040d83f        set_bod_object(&game->subgame.path_pairs[0xe].primary.bod, add_object_to_list(&g_object_list))
0040d863        initialize_sbend_path_template_pair(&game->subgame.path_pairs[0xe], 8, 8f, 14f, 1, "Objects/World00/Track0.tga", "Objects/World00/Track0.tga", "Objects/Path/VeryDark.tga")
0040d86d        game->subgame.path_pairs[0xe].primary.bod.position.z = 0f
0040d873        game->subgame.path_pairs[0xe].primary.bod.position.y = 0f
0040d879        game->subgame.path_pairs[0xe].primary.bod.position.x = 0
0040d88b        set_bod_object(&game->subgame.path_pairs[0xe].secondary.bod, add_object_to_list(&g_object_list))
0040d897        mirror_path_template_pair_x(&game->subgame.path_pairs[0xe].secondary, &game->subgame.path_pairs[0xe])
0040d8a4        game->subgame.path_pairs[0xe].secondary.bod.position.z = 0f
0040d8aa        game->subgame.path_pairs[0xe].secondary.bod.position.y = 0f
0040d8b0        game->subgame.path_pairs[0xe].secondary.bod.position.x = 0
0040d8b6        build_track_fringe_mesh(&game->subgame.path_pairs[0xe], "Objects/Universe/Fringe.tga", 0f)
0040d8c7        game->subgame.path_pairs[0xe].primary.fringe_mesh_bod.position.z = 0f
0040d8cd        game->subgame.path_pairs[0xe].primary.fringe_mesh_bod.position.y = 0f
0040d8d3        game->subgame.path_pairs[0xe].primary.fringe_mesh_bod.position.x = 0
0040d8d9        build_track_fringe_mesh(&game->subgame.path_pairs[0xe].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d8e3        game->subgame.path_pairs[0xe].secondary.fringe_mesh_bod.position.z = 0f
0040d8e9        game->subgame.path_pairs[0xe].secondary.fringe_mesh_bod.position.y = 0f
0040d8ef        game->subgame.path_pairs[0xe].secondary.fringe_mesh_bod.position.x = 0
0040d903        set_bod_object(&game->subgame.path_pairs[0xb].primary.bod, add_object_to_list(&g_object_list))
0040d927        initialize_hill_valley_path_template_pair(&game->subgame.path_pairs[0xb], 8, -4f, 20f, 1, "Objects/World00/Slide0.tga", "Objects/World00/Slide0.tga", "Objects/Path/VeryDark.tga")
0040d931        game->subgame.path_pairs[0xb].primary.bod.position.z = 0f
0040d937        game->subgame.path_pairs[0xb].primary.bod.position.y = 0f
0040d93d        game->subgame.path_pairs[0xb].primary.bod.position.x = 0
0040d94f        set_bod_object(&game->subgame.path_pairs[0xb].secondary.bod, add_object_to_list(&g_object_list))
0040d95b        mirror_path_template_pair_x(&game->subgame.path_pairs[0xb].secondary, &game->subgame.path_pairs[0xb])
0040d968        game->subgame.path_pairs[0xb].secondary.bod.position.z = 0f
0040d96e        game->subgame.path_pairs[0xb].secondary.bod.position.y = 0f
0040d974        game->subgame.path_pairs[0xb].secondary.bod.position.x = 0
0040d97a        build_track_fringe_mesh(&game->subgame.path_pairs[0xb], "Objects/Universe/Fringe.tga", 0f)
0040d98b        game->subgame.path_pairs[0xb].primary.fringe_mesh_bod.position.z = 0f
0040d991        game->subgame.path_pairs[0xb].primary.fringe_mesh_bod.position.y = 0f
0040d997        game->subgame.path_pairs[0xb].primary.fringe_mesh_bod.position.x = 0
0040d99d        build_track_fringe_mesh(&game->subgame.path_pairs[0xb].secondary, "Objects/Universe/Fringe.tga", 0f)
0040d9a7        game->subgame.path_pairs[0xb].secondary.fringe_mesh_bod.position.z = 0f
0040d9ad        game->subgame.path_pairs[0xb].secondary.fringe_mesh_bod.position.y = 0f
0040d9b3        game->subgame.path_pairs[0xb].secondary.fringe_mesh_bod.position.x = 0
0040d9c7        set_bod_object(&game->subgame.path_pairs[0xd].primary.bod, add_object_to_list(&g_object_list))
0040d9ea        initialize_hill_valley_path_template_pair(&game->subgame.path_pairs[0xd], 4, -4f, 20f, 0, "Objects/World00/Slide0.tga", "Objects/World00/Slide0.tga", "Objects/Path/VeryDark.tga")
0040d9f4        game->subgame.path_pairs[0xd].primary.bod.position.z = 0f
0040d9fa        game->subgame.path_pairs[0xd].primary.bod.position.y = 0f
0040da00        game->subgame.path_pairs[0xd].primary.bod.position.x = 0
0040da12        set_bod_object(&game->subgame.path_pairs[0xd].secondary.bod, add_object_to_list(&g_object_list))
0040da1e        mirror_path_template_pair_x(&game->subgame.path_pairs[0xd].secondary, &game->subgame.path_pairs[0xd])
0040da2b        game->subgame.path_pairs[0xd].secondary.bod.position.z = 0f
0040da31        game->subgame.path_pairs[0xd].secondary.bod.position.y = 0f
0040da37        game->subgame.path_pairs[0xd].secondary.bod.position.x = 0
0040da3d        build_track_fringe_mesh(&game->subgame.path_pairs[0xd], "Objects/Universe/Fringe.tga", 0f)
0040da4e        game->subgame.path_pairs[0xd].primary.fringe_mesh_bod.position.z = 0f
0040da54        game->subgame.path_pairs[0xd].primary.fringe_mesh_bod.position.y = 0f
0040da5a        game->subgame.path_pairs[0xd].primary.fringe_mesh_bod.position.x = 0
0040da60        build_track_fringe_mesh(&game->subgame.path_pairs[0xd].secondary, "Objects/Universe/Fringe.tga", 0f)
0040da6a        game->subgame.path_pairs[0xd].secondary.fringe_mesh_bod.position.z = 0f
0040da70        game->subgame.path_pairs[0xd].secondary.fringe_mesh_bod.position.y = 0f
0040da76        game->subgame.path_pairs[0xd].secondary.fringe_mesh_bod.position.x = 0
0040da8a        set_bod_object(&game->subgame.path_pairs[0xc].primary.bod, add_object_to_list(&g_object_list))
0040daae        initialize_hill_valley_path_template_pair(&game->subgame.path_pairs[0xc], 4, -4f, 20f, 1, "Objects/World00/Slide0.tga", "Objects/World00/Slide0.tga", "Objects/Path/VeryDark.tga")
0040dab8        game->subgame.path_pairs[0xc].primary.bod.position.z = 0f
0040dabe        game->subgame.path_pairs[0xc].primary.bod.position.y = 0f
0040dac4        game->subgame.path_pairs[0xc].primary.bod.position.x = 0
0040dad6        set_bod_object(&game->subgame.path_pairs[0xc].secondary.bod, add_object_to_list(&g_object_list))
0040dae2        mirror_path_template_pair_x(&game->subgame.path_pairs[0xc].secondary, &game->subgame.path_pairs[0xc])
0040daef        game->subgame.path_pairs[0xc].secondary.bod.position.z = 0f
0040daf5        game->subgame.path_pairs[0xc].secondary.bod.position.y = 0f
0040dafb        game->subgame.path_pairs[0xc].secondary.bod.position.x = 0
0040db01        build_track_fringe_mesh(&game->subgame.path_pairs[0xc], "Objects/Universe/Fringe.tga", 0f)
0040db12        game->subgame.path_pairs[0xc].primary.fringe_mesh_bod.position.z = 0f
0040db18        game->subgame.path_pairs[0xc].primary.fringe_mesh_bod.position.y = 0f
0040db1e        game->subgame.path_pairs[0xc].primary.fringe_mesh_bod.position.x = 0
0040db24        build_track_fringe_mesh(&game->subgame.path_pairs[0xc].secondary, "Objects/Universe/Fringe.tga", 0f)
0040db2e        game->subgame.path_pairs[0xc].secondary.fringe_mesh_bod.position.z = 0f
0040db34        game->subgame.path_pairs[0xc].secondary.fringe_mesh_bod.position.y = 0f
0040db3a        game->subgame.path_pairs[0xc].secondary.fringe_mesh_bod.position.x = 0
0040db4e        set_bod_object(&game->subgame.path_pairs[0x14].primary.bod, add_object_to_list(&g_object_list))
0040db6d        initialize_dip_path_template_pair(&game->subgame.path_pairs[0x14], 4f, 2, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040db77        game->subgame.path_pairs[0x14].primary.bod.position.z = 0f
0040db7d        game->subgame.path_pairs[0x14].primary.bod.position.y = 0f
0040db83        game->subgame.path_pairs[0x14].primary.bod.position.x = 0
0040db95        set_bod_object(&game->subgame.path_pairs[0x14].secondary.bod, add_object_to_list(&g_object_list))
0040dba1        mirror_path_template_pair_x(&game->subgame.path_pairs[0x14].secondary, &game->subgame.path_pairs[0x14])
0040dbae        game->subgame.path_pairs[0x14].secondary.bod.position.z = 0f
0040dbb4        game->subgame.path_pairs[0x14].secondary.bod.position.y = 0f
0040dbba        game->subgame.path_pairs[0x14].secondary.bod.position.x = 0
0040dbc0        build_track_fringe_mesh(&game->subgame.path_pairs[0x14], "Objects/Universe/Fringe.tga", 0f)
0040dbd1        game->subgame.path_pairs[0x14].primary.fringe_mesh_bod.position.z = 0f
0040dbd7        game->subgame.path_pairs[0x14].primary.fringe_mesh_bod.position.y = 0f
0040dbdd        game->subgame.path_pairs[0x14].primary.fringe_mesh_bod.position.x = 0
0040dbe3        build_track_fringe_mesh(&game->subgame.path_pairs[0x14].secondary, "Objects/Universe/Fringe.tga", 0f)
0040dbed        game->subgame.path_pairs[0x14].secondary.fringe_mesh_bod.position.z = 0f
0040dbf3        game->subgame.path_pairs[0x14].secondary.fringe_mesh_bod.position.y = 0f
0040dbf9        game->subgame.path_pairs[0x14].secondary.fringe_mesh_bod.position.x = 0
0040dc0d        set_bod_object(&game->subgame.path_pairs[0x15].primary.bod, add_object_to_list(&g_object_list))
0040dc29        initialize_screw_path_template_pair(&game->subgame.path_pairs[0x15], 0x18, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Slide0.tga", "Objects/Path/VeryDark.tga")
0040dc33        game->subgame.path_pairs[0x15].primary.bod.position.z = 0f
0040dc39        game->subgame.path_pairs[0x15].primary.bod.position.y = 0f
0040dc3f        game->subgame.path_pairs[0x15].primary.bod.position.x = 0
0040dc51        set_bod_object(&game->subgame.path_pairs[0x15].secondary.bod, add_object_to_list(&g_object_list))
0040dc5d        mirror_path_template_pair_x(&game->subgame.path_pairs[0x15].secondary, &game->subgame.path_pairs[0x15])
0040dc6a        game->subgame.path_pairs[0x15].secondary.bod.position.z = 0f
0040dc70        game->subgame.path_pairs[0x15].secondary.bod.position.y = 0f
0040dc76        game->subgame.path_pairs[0x15].secondary.bod.position.x = 0
0040dc7c        build_track_fringe_mesh(&game->subgame.path_pairs[0x15], "Objects/Universe/Fringe.tga", 0f)
0040dc8d        game->subgame.path_pairs[0x15].primary.fringe_mesh_bod.position.z = 0f
0040dc93        game->subgame.path_pairs[0x15].primary.fringe_mesh_bod.position.y = 0f
0040dc99        game->subgame.path_pairs[0x15].primary.fringe_mesh_bod.position.x = 0
0040dc9f        build_track_fringe_mesh(&game->subgame.path_pairs[0x15].secondary, "Objects/Universe/Fringe.tga", 0f)
0040dca4        game->subgame.path_pairs[0x15].secondary.fringe_mesh_bod.position.z = 0f
0040dcaa        game->subgame.path_pairs[0x15].secondary.fringe_mesh_bod.position.y = 0f
0040dcb0        game->subgame.path_pairs[0x15].secondary.fringe_mesh_bod.position.x = 0
0040dcc9        set_bod_object(&game->subgame.path_pairs[0x16].primary.bod, add_object_to_list(&g_object_list))
0040dce5        initialize_slalom_path_template_pair(&game->subgame.path_pairs[0x16], 0x20, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040dcef        game->subgame.path_pairs[0x16].primary.bod.position.z = 0f
0040dcf5        game->subgame.path_pairs[0x16].primary.bod.position.y = 0f
0040dcfb        game->subgame.path_pairs[0x16].primary.bod.position.x = 0
0040dd0d        set_bod_object(&game->subgame.path_pairs[0x16].secondary.bod, add_object_to_list(&g_object_list))
0040dd19        mirror_path_template_pair_x(&game->subgame.path_pairs[0x16].secondary, &game->subgame.path_pairs[0x16])
0040dd26        game->subgame.path_pairs[0x16].secondary.bod.position.z = 0f
0040dd2c        game->subgame.path_pairs[0x16].secondary.bod.position.y = 0f
0040dd32        game->subgame.path_pairs[0x16].secondary.bod.position.x = 0
0040dd38        build_track_fringe_mesh(&game->subgame.path_pairs[0x16], "Objects/Universe/Fringe.tga", 0f)
0040dd49        game->subgame.path_pairs[0x16].primary.fringe_mesh_bod.position.z = 0f
0040dd4f        game->subgame.path_pairs[0x16].primary.fringe_mesh_bod.position.y = 0f
0040dd55        game->subgame.path_pairs[0x16].primary.fringe_mesh_bod.position.x = 0
0040dd5b        build_track_fringe_mesh(&game->subgame.path_pairs[0x16].secondary, "Objects/Universe/Fringe.tga", 0f)
0040dd65        game->subgame.path_pairs[0x16].secondary.fringe_mesh_bod.position.z = 0f
0040dd6b        game->subgame.path_pairs[0x16].secondary.fringe_mesh_bod.position.y = 0f
0040dd71        game->subgame.path_pairs[0x16].secondary.fringe_mesh_bod.position.x = 0
0040dd85        set_bod_object(&game->subgame.path_pairs[0x17].primary.bod, add_object_to_list(&g_object_list))
0040dda1        initialize_slalombig_path_template_pair(&game->subgame.path_pairs[0x17], 0x20, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040ddab        game->subgame.path_pairs[0x17].primary.bod.position.z = 0f
0040ddb1        game->subgame.path_pairs[0x17].primary.bod.position.y = 0f
0040ddb7        game->subgame.path_pairs[0x17].primary.bod.position.x = 0
0040ddc9        set_bod_object(&game->subgame.path_pairs[0x17].secondary.bod, add_object_to_list(&g_object_list))
0040ddd5        mirror_path_template_pair_x(&game->subgame.path_pairs[0x17].secondary, &game->subgame.path_pairs[0x17])
0040dde2        game->subgame.path_pairs[0x17].secondary.bod.position.z = 0f
0040dde8        game->subgame.path_pairs[0x17].secondary.bod.position.y = 0f
0040ddee        game->subgame.path_pairs[0x17].secondary.bod.position.x = 0
0040ddf4        build_track_fringe_mesh(&game->subgame.path_pairs[0x17], "Objects/Universe/Fringe.tga", 0f)
0040de05        game->subgame.path_pairs[0x17].primary.fringe_mesh_bod.position.z = 0f
0040de0b        game->subgame.path_pairs[0x17].primary.fringe_mesh_bod.position.y = 0f
0040de11        game->subgame.path_pairs[0x17].primary.fringe_mesh_bod.position.x = 0
0040de17        build_track_fringe_mesh(&game->subgame.path_pairs[0x17].secondary, "Objects/Universe/Fringe.tga", 0f)
0040de1c        game->subgame.path_pairs[0x17].secondary.fringe_mesh_bod.position.z = 0f
0040de27        game->subgame.path_pairs[0x17].secondary.fringe_mesh_bod.position.y = 0f
0040de2d        game->subgame.path_pairs[0x17].secondary.fringe_mesh_bod.position.x = 0
0040de41        set_bod_object(&game->subgame.path_pairs[0x20].primary.bod, add_object_to_list(&g_object_list))
0040de5d        initialize_slalomdouble_path_template_pair(&game->subgame.path_pairs[0x20], 0x20, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040de67        game->subgame.path_pairs[0x20].primary.bod.position.z = 0f
0040de6d        game->subgame.path_pairs[0x20].primary.bod.position.y = 0f
0040de73        game->subgame.path_pairs[0x20].primary.bod.position.x = 0
0040de85        set_bod_object(&game->subgame.path_pairs[0x20].secondary.bod, add_object_to_list(&g_object_list))
0040de91        mirror_path_template_pair_x(&game->subgame.path_pairs[0x20].secondary, &game->subgame.path_pairs[0x20])
0040de9e        game->subgame.path_pairs[0x20].secondary.bod.position.z = 0f
0040dea4        game->subgame.path_pairs[0x20].secondary.bod.position.y = 0f
0040deaa        game->subgame.path_pairs[0x20].secondary.bod.position.x = 0
0040deb0        build_track_fringe_mesh(&game->subgame.path_pairs[0x20], "Objects/Universe/Fringe.tga", 0f)
0040dec1        game->subgame.path_pairs[0x20].primary.fringe_mesh_bod.position.z = 0f
0040dec7        game->subgame.path_pairs[0x20].primary.fringe_mesh_bod.position.y = 0f
0040decd        game->subgame.path_pairs[0x20].primary.fringe_mesh_bod.position.x = 0
0040ded3        build_track_fringe_mesh(&game->subgame.path_pairs[0x20].secondary, "Objects/Universe/Fringe.tga", 0f)
0040dedd        game->subgame.path_pairs[0x20].secondary.fringe_mesh_bod.position.z = 0f
0040dee3        game->subgame.path_pairs[0x20].secondary.fringe_mesh_bod.position.y = 0f
0040dee9        game->subgame.path_pairs[0x20].secondary.fringe_mesh_bod.position.x = 0
0040defd        set_bod_object(&game->subgame.path_pairs[0x18].primary.bod, add_object_to_list(&g_object_list))
0040df09        initialize_worm_path_template_pair(&game->subgame.path_pairs[0x18], "Objects/World00/Worm.tga")
0040df13        game->subgame.path_pairs[0x18].primary.bod.position.z = 0f
0040df19        game->subgame.path_pairs[0x18].primary.bod.position.y = 0f
0040df1f        game->subgame.path_pairs[0x18].primary.bod.position.x = 0
0040df31        set_bod_object(&game->subgame.path_pairs[0x18].secondary.bod, add_object_to_list(&g_object_list))
0040df3d        mirror_path_template_pair_x(&game->subgame.path_pairs[0x18].secondary, &game->subgame.path_pairs[0x18])
0040df47        game->subgame.path_pairs[0x18].secondary.bod.position.z = 0f
0040df4d        game->subgame.path_pairs[0x18].secondary.bod.position.y = 0f
0040df53        game->subgame.path_pairs[0x18].secondary.bod.position.x = 0
0040df65        set_bod_object(&game->subgame.path_pairs[0x18].primary.fringe_mesh_bod, add_object_to_list(&g_object_list))
0040df71        disable_object_rendering(game->subgame.path_pairs[0x18].primary.fringe_mesh_bod.object)
0040df8a        set_bod_object(&game->subgame.path_pairs[0x18].secondary.fringe_mesh_bod, add_object_to_list(&g_object_list))
0040df96        disable_object_rendering(game->subgame.path_pairs[0x18].secondary.fringe_mesh_bod.object)
0040dfaf        game->subgame.path_pairs[0x18].primary.bod.object->blend_mode = 8
0040dfbd        game->subgame.path_pairs[0x18].secondary.bod.object->blend_mode = 8
0040dfc8        set_bod_object(&game->subgame.path_pairs[0x1c].primary.bod, add_object_to_list(&g_object_list))
0040dfe7        initialize_sweep_path_template_pair(&game->subgame.path_pairs[0x1c], 4f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040dff1        game->subgame.path_pairs[0x1c].primary.bod.position.z = 0f
0040dff7        game->subgame.path_pairs[0x1c].primary.bod.position.y = 0f
0040dffd        game->subgame.path_pairs[0x1c].primary.bod.position.x = 0
0040e00f        set_bod_object(&game->subgame.path_pairs[0x1c].secondary.bod, add_object_to_list(&g_object_list))
0040e01b        mirror_path_template_pair_x(&game->subgame.path_pairs[0x1c].secondary, &game->subgame.path_pairs[0x1c])
0040e028        game->subgame.path_pairs[0x1c].secondary.bod.position.z = 0f
0040e02e        game->subgame.path_pairs[0x1c].secondary.bod.position.y = 0f
0040e034        game->subgame.path_pairs[0x1c].secondary.bod.position.x = 0
0040e03a        build_track_fringe_mesh(&game->subgame.path_pairs[0x1c], "Objects/Universe/Fringe.tga", 0f)
0040e04b        game->subgame.path_pairs[0x1c].primary.fringe_mesh_bod.position.z = 0f
0040e051        game->subgame.path_pairs[0x1c].primary.fringe_mesh_bod.position.y = 0f
0040e057        game->subgame.path_pairs[0x1c].primary.fringe_mesh_bod.position.x = 0
0040e05d        build_track_fringe_mesh(&game->subgame.path_pairs[0x1c].secondary, "Objects/Universe/Fringe.tga", 0f)
0040e067        game->subgame.path_pairs[0x1c].secondary.fringe_mesh_bod.position.z = 0f
0040e06d        game->subgame.path_pairs[0x1c].secondary.fringe_mesh_bod.position.y = 0f
0040e073        game->subgame.path_pairs[0x1c].secondary.fringe_mesh_bod.position.x = 0
0040e087        set_bod_object(&game->subgame.path_pairs[0xf].primary.bod, add_object_to_list(&g_object_list))
0040e09f        initialize_cage2_path_template_pair(&game->subgame.path_pairs[0xf], 3, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040e0a9        game->subgame.path_pairs[0xf].primary.bod.position.z = 0f
0040e0af        game->subgame.path_pairs[0xf].primary.bod.position.y = 0f
0040e0b5        game->subgame.path_pairs[0xf].primary.bod.position.x = 0
0040e0c7        set_bod_object(&game->subgame.path_pairs[0xf].secondary.bod, add_object_to_list(&g_object_list))
0040e0d3        mirror_path_template_pair_x(&game->subgame.path_pairs[0xf].secondary, &game->subgame.path_pairs[0xf])
0040e0e0        game->subgame.path_pairs[0xf].secondary.bod.position.z = 0f
0040e0e6        game->subgame.path_pairs[0xf].secondary.bod.position.y = 0f
0040e0ec        game->subgame.path_pairs[0xf].secondary.bod.position.x = 0
0040e0f2        build_track_fringe_mesh(&game->subgame.path_pairs[0xf], "Objects/Universe/Fringe.tga", 0f)
0040e103        game->subgame.path_pairs[0xf].primary.fringe_mesh_bod.position.z = 0f
0040e109        game->subgame.path_pairs[0xf].primary.fringe_mesh_bod.position.y = 0f
0040e10f        game->subgame.path_pairs[0xf].primary.fringe_mesh_bod.position.x = 0
0040e115        build_track_fringe_mesh(&game->subgame.path_pairs[0xf].secondary, "Objects/Universe/Fringe.tga", 0f)
0040e11f        game->subgame.path_pairs[0xf].secondary.fringe_mesh_bod.position.z = 0f
0040e125        game->subgame.path_pairs[0xf].secondary.fringe_mesh_bod.position.y = 0f
0040e12b        game->subgame.path_pairs[0xf].secondary.fringe_mesh_bod.position.x = 0
0040e13f        set_bod_object(&game->subgame.path_pairs[0x21].primary.bod, add_object_to_list(&g_object_list))
0040e169        initialize_p_path_template_pair(&game->subgame.path_pairs[0x21], 0, 4f, 3, 0.5f, -2.5f, 0xe, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040e173        game->subgame.path_pairs[0x21].primary.bod.position.z = 0f
0040e179        game->subgame.path_pairs[0x21].primary.bod.position.y = 0f
0040e17f        game->subgame.path_pairs[0x21].primary.bod.position.x = 0
0040e191        set_bod_object(&game->subgame.path_pairs[0x21].secondary.bod, add_object_to_list(&g_object_list))
0040e19d        mirror_path_template_pair_x(&game->subgame.path_pairs[0x21].secondary, &game->subgame.path_pairs[0x21])
0040e1aa        game->subgame.path_pairs[0x21].secondary.bod.position.z = 0f
0040e1b0        game->subgame.path_pairs[0x21].secondary.bod.position.y = 0f
0040e1b6        game->subgame.path_pairs[0x21].secondary.bod.position.x = 0
0040e1bc        build_track_fringe_mesh(&game->subgame.path_pairs[0x21], "Objects/Universe/Fringe.tga", 0f)
0040e1cd        game->subgame.path_pairs[0x21].primary.fringe_mesh_bod.position.z = 0f
0040e1d3        game->subgame.path_pairs[0x21].primary.fringe_mesh_bod.position.y = 0f
0040e1d9        game->subgame.path_pairs[0x21].primary.fringe_mesh_bod.position.x = 0
0040e1df        build_track_fringe_mesh(&game->subgame.path_pairs[0x21].secondary, "Objects/Universe/Fringe.tga", 0f)
0040e1e9        game->subgame.path_pairs[0x21].secondary.fringe_mesh_bod.position.z = 0f
0040e1ef        game->subgame.path_pairs[0x21].secondary.fringe_mesh_bod.position.y = 0f
0040e1f5        game->subgame.path_pairs[0x21].secondary.fringe_mesh_bod.position.x = 0
0040e209        set_bod_object(&game->subgame.path_pairs[0x22].primary.bod, add_object_to_list(&g_object_list))
0040e234        initialize_p_path_template_pair(&game->subgame.path_pairs[0x22], 1, 4f, 3, -2.5f, 2.5f, 0xe, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040e23e        game->subgame.path_pairs[0x22].primary.bod.position.z = 0f
0040e244        game->subgame.path_pairs[0x22].primary.bod.position.y = 0f
0040e24a        game->subgame.path_pairs[0x22].primary.bod.position.x = 0
0040e25c        set_bod_object(&game->subgame.path_pairs[0x22].secondary.bod, add_object_to_list(&g_object_list))
0040e268        mirror_path_template_pair_x(&game->subgame.path_pairs[0x22].secondary, &game->subgame.path_pairs[0x22])
0040e275        game->subgame.path_pairs[0x22].secondary.bod.position.z = 0f
0040e27b        game->subgame.path_pairs[0x22].secondary.bod.position.y = 0f
0040e281        game->subgame.path_pairs[0x22].secondary.bod.position.x = 0
0040e287        build_track_fringe_mesh(&game->subgame.path_pairs[0x22], "Objects/Universe/Fringe.tga", 0f)
0040e298        game->subgame.path_pairs[0x22].primary.fringe_mesh_bod.position.z = 0f
0040e29e        game->subgame.path_pairs[0x22].primary.fringe_mesh_bod.position.y = 0f
0040e2a4        game->subgame.path_pairs[0x22].primary.fringe_mesh_bod.position.x = 0
0040e2aa        build_track_fringe_mesh(&game->subgame.path_pairs[0x22].secondary, "Objects/Universe/Fringe.tga", 0f)
0040e2b4        game->subgame.path_pairs[0x22].secondary.fringe_mesh_bod.position.z = 0f
0040e2ba        game->subgame.path_pairs[0x22].secondary.fringe_mesh_bod.position.y = 0f
0040e2c0        game->subgame.path_pairs[0x22].secondary.fringe_mesh_bod.position.x = 0
0040e2d4        set_bod_object(&game->subgame.path_pairs[0x23].primary.bod, add_object_to_list(&g_object_list))
0040e2ff        initialize_p_path_template_pair(&game->subgame.path_pairs[0x23], 2, 4f, 3, 2.5f, 0.5f, 0xe, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040e309        game->subgame.path_pairs[0x23].primary.bod.position.z = 0f
0040e30f        game->subgame.path_pairs[0x23].primary.bod.position.y = 0f
0040e315        game->subgame.path_pairs[0x23].primary.bod.position.x = 0
0040e327        set_bod_object(&game->subgame.path_pairs[0x23].secondary.bod, add_object_to_list(&g_object_list))
0040e333        mirror_path_template_pair_x(&game->subgame.path_pairs[0x23].secondary, &game->subgame.path_pairs[0x23])
0040e340        game->subgame.path_pairs[0x23].secondary.bod.position.z = 0f
0040e346        game->subgame.path_pairs[0x23].secondary.bod.position.y = 0f
0040e34c        game->subgame.path_pairs[0x23].secondary.bod.position.x = 0
0040e352        build_track_fringe_mesh(&game->subgame.path_pairs[0x23], "Objects/Universe/Fringe.tga", 0f)
0040e363        game->subgame.path_pairs[0x23].primary.fringe_mesh_bod.position.z = 0f
0040e369        game->subgame.path_pairs[0x23].primary.fringe_mesh_bod.position.y = 0f
0040e36f        game->subgame.path_pairs[0x23].primary.fringe_mesh_bod.position.x = 0
0040e375        build_track_fringe_mesh(&game->subgame.path_pairs[0x23].secondary, "Objects/Universe/Fringe.tga", 0f)
0040e37f        game->subgame.path_pairs[0x23].secondary.fringe_mesh_bod.position.z = 0f
0040e385        game->subgame.path_pairs[0x23].secondary.fringe_mesh_bod.position.y = 0f
0040e38b        game->subgame.path_pairs[0x23].secondary.fringe_mesh_bod.position.x = 0
0040e39f        set_bod_object(&game->subgame.path_pairs[0x1d].primary.bod, add_object_to_list(&g_object_list))
0040e3be        initialize_snake_path_template_pair(&game->subgame.path_pairs[0x1d], 2f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Track0.tga", "Objects/Path/VeryDark.tga")
0040e3c3        game->subgame.path_pairs[0x1d].primary.bod.position.z = 0f
0040e3c9        game->subgame.path_pairs[0x1d].primary.bod.position.y = 0f
0040e3cf        game->subgame.path_pairs[0x1d].primary.bod.position.x = 0
0040e3e6        set_bod_object(&game->subgame.path_pairs[0x1d].secondary.bod, add_object_to_list(&g_object_list))
0040e3f2        mirror_path_template_pair_x(&game->subgame.path_pairs[0x1d].secondary, &game->subgame.path_pairs[0x1d])
0040e3ff        game->subgame.path_pairs[0x1d].secondary.bod.position.z = 0f
0040e405        game->subgame.path_pairs[0x1d].secondary.bod.position.y = 0f
0040e40b        game->subgame.path_pairs[0x1d].secondary.bod.position.x = 0
0040e411        build_track_fringe_mesh(&game->subgame.path_pairs[0x1d], "Objects/Universe/Fringe.tga", 0f)
0040e422        game->subgame.path_pairs[0x1d].primary.fringe_mesh_bod.position.z = 0f
0040e428        game->subgame.path_pairs[0x1d].primary.fringe_mesh_bod.position.y = 0f
0040e42e        game->subgame.path_pairs[0x1d].primary.fringe_mesh_bod.position.x = 0
0040e434        build_track_fringe_mesh(&game->subgame.path_pairs[0x1d].secondary, "Objects/Universe/Fringe.tga", 0f)
0040e43e        game->subgame.path_pairs[0x1d].secondary.fringe_mesh_bod.position.z = 0f
0040e444        game->subgame.path_pairs[0x1d].secondary.fringe_mesh_bod.position.y = 0f
0040e44a        game->subgame.path_pairs[0x1d].secondary.fringe_mesh_bod.position.x = 0
0040e45e        set_bod_object(&game->subgame.path_pairs[0x2f].primary.bod, add_object_to_list(&g_object_list))
0040e476        initialize_toad_path_template_pair(&game->subgame.path_pairs[0x2f], 1, "Objects/World00/Slide0.tga", "Objects/World00/Track0.tga", "Objects/Path/VeryDark.tga")
0040e480        game->subgame.path_pairs[0x2f].primary.bod.position.z = 0f
0040e486        game->subgame.path_pairs[0x2f].primary.bod.position.y = 0f
0040e48c        game->subgame.path_pairs[0x2f].primary.bod.position.x = 0
0040e49e        set_bod_object(&game->subgame.path_pairs[0x2f].secondary.bod, add_object_to_list(&g_object_list))
0040e4aa        mirror_path_template_pair_x(&game->subgame.path_pairs[0x2f].secondary, &game->subgame.path_pairs[0x2f])
0040e4b7        game->subgame.path_pairs[0x2f].secondary.bod.position.z = 0f
0040e4bd        game->subgame.path_pairs[0x2f].secondary.bod.position.y = 0f
0040e4c3        game->subgame.path_pairs[0x2f].secondary.bod.position.x = 0
0040e4c9        build_track_fringe_mesh(&game->subgame.path_pairs[0x2f], "Objects/Universe/Fringe.tga", 0f)
0040e4da        game->subgame.path_pairs[0x2f].primary.fringe_mesh_bod.position.z = 0f
0040e4e0        game->subgame.path_pairs[0x2f].primary.fringe_mesh_bod.position.y = 0f
0040e4e6        game->subgame.path_pairs[0x2f].primary.fringe_mesh_bod.position.x = 0
0040e4ec        build_track_fringe_mesh(&game->subgame.path_pairs[0x2f].secondary, "Objects/Universe/Fringe.tga", 0f)
0040e4f6        game->subgame.path_pairs[0x2f].secondary.fringe_mesh_bod.position.z = 0f
0040e4fc        game->subgame.path_pairs[0x2f].secondary.fringe_mesh_bod.position.y = 0f
0040e502        game->subgame.path_pairs[0x2f].secondary.fringe_mesh_bod.position.x = 0
0040e516        set_bod_object(&game->subgame.path_pairs[0x30].primary.bod, add_object_to_list(&g_object_list))
0040e52d        initialize_toad_path_template_pair(&game->subgame.path_pairs[0x30], 0, "Objects/World00/Slide0.tga", "Objects/World00/Track0.tga", "Objects/Path/VeryDark.tga")
0040e532        game->subgame.path_pairs[0x30].primary.bod.position.z = 0f
0040e538        game->subgame.path_pairs[0x30].primary.bod.position.y = 0f
0040e53e        game->subgame.path_pairs[0x30].primary.bod.position.x = 0
0040e555        set_bod_object(&game->subgame.path_pairs[0x30].secondary.bod, add_object_to_list(&g_object_list))
0040e561        mirror_path_template_pair_x(&game->subgame.path_pairs[0x30].secondary, &game->subgame.path_pairs[0x30])
0040e56e        game->subgame.path_pairs[0x30].secondary.bod.position.z = 0f
0040e574        game->subgame.path_pairs[0x30].secondary.bod.position.y = 0f
0040e57a        game->subgame.path_pairs[0x30].secondary.bod.position.x = 0
0040e580        build_track_fringe_mesh(&game->subgame.path_pairs[0x30], "Objects/Universe/Fringe.tga", 0f)
0040e591        game->subgame.path_pairs[0x30].primary.fringe_mesh_bod.position.z = 0f
0040e597        game->subgame.path_pairs[0x30].primary.fringe_mesh_bod.position.y = 0f
0040e59d        game->subgame.path_pairs[0x30].primary.fringe_mesh_bod.position.x = 0
0040e5a3        build_track_fringe_mesh(&game->subgame.path_pairs[0x30].secondary, "Objects/Universe/Fringe.tga", 0f)
0040e5ad        game->subgame.path_pairs[0x30].secondary.fringe_mesh_bod.position.z = 0f
0040e5b3        game->subgame.path_pairs[0x30].secondary.fringe_mesh_bod.position.y = 0f
0040e5b9        game->subgame.path_pairs[0x30].secondary.fringe_mesh_bod.position.x = 0
0040e5cd        set_bod_object(&game->subgame.path_pairs[0x31].primary.bod, add_object_to_list(&g_object_list))
0040e5e5        initialize_toad_path_template_pair(&game->subgame.path_pairs[0x31], 1, "Objects/World00/Slide0.tga", "Objects/World00/Track0.tga", "Objects/Path/VeryDark.tga")
0040e5ef        game->subgame.path_pairs[0x31].primary.bod.position.z = 0f
0040e5f5        game->subgame.path_pairs[0x31].primary.bod.position.y = 0f
0040e5fb        game->subgame.path_pairs[0x31].primary.bod.position.x = 0
0040e60d        set_bod_object(&game->subgame.path_pairs[0x31].secondary.bod, add_object_to_list(&g_object_list))
0040e619        mirror_path_template_pair_x(&game->subgame.path_pairs[0x31].secondary, &game->subgame.path_pairs[0x31])
0040e62a        game->subgame.path_pairs[0x31].secondary.bod.position.z = 0f
0040e630        game->subgame.path_pairs[0x31].secondary.bod.position.y = 0f
0040e636        game->subgame.path_pairs[0x31].secondary.bod.position.x = 0
0040e63c        build_track_fringe_mesh(&game->subgame.path_pairs[0x31], "Objects/Universe/Fringe.tga", -1f)
0040e651        game->subgame.path_pairs[0x31].primary.fringe_mesh_bod.position.z = 0f
0040e657        game->subgame.path_pairs[0x31].primary.fringe_mesh_bod.position.y = 0f
0040e65d        game->subgame.path_pairs[0x31].primary.fringe_mesh_bod.position.x = 0
0040e663        build_track_fringe_mesh(&game->subgame.path_pairs[0x31].secondary, "Objects/Universe/Fringe.tga", 1f)
0040e66d        game->subgame.path_pairs[0x31].secondary.fringe_mesh_bod.position.z = 0f
0040e673        game->subgame.path_pairs[0x31].secondary.fringe_mesh_bod.position.y = 0f
0040e679        game->subgame.path_pairs[0x31].secondary.fringe_mesh_bod.position.x = 0
0040e68d        set_bod_object(&game->subgame.path_pairs[0x32].primary.bod, add_object_to_list(&g_object_list))
0040e6a4        initialize_toad_path_template_pair(&game->subgame.path_pairs[0x32], 0, "Objects/World00/Slide0.tga", "Objects/World00/Track0.tga", "Objects/Path/VeryDark.tga")
0040e6ae        game->subgame.path_pairs[0x32].primary.bod.position.z = 0f
0040e6b4        game->subgame.path_pairs[0x32].primary.bod.position.y = 0f
0040e6ba        game->subgame.path_pairs[0x32].primary.bod.position.x = 0
0040e6cc        set_bod_object(&game->subgame.path_pairs[0x32].secondary.bod, add_object_to_list(&g_object_list))
0040e6d8        mirror_path_template_pair_x(&game->subgame.path_pairs[0x32].secondary, &game->subgame.path_pairs[0x32])
0040e6e9        game->subgame.path_pairs[0x32].secondary.bod.position.z = 0f
0040e6ef        game->subgame.path_pairs[0x32].secondary.bod.position.y = 0f
0040e6f5        game->subgame.path_pairs[0x32].secondary.bod.position.x = 0
0040e6fb        build_track_fringe_mesh(&game->subgame.path_pairs[0x32], "Objects/Universe/Fringe.tga", 1f)
0040e710        game->subgame.path_pairs[0x32].primary.fringe_mesh_bod.position.z = 0f
0040e716        game->subgame.path_pairs[0x32].primary.fringe_mesh_bod.position.y = 0f
0040e71c        game->subgame.path_pairs[0x32].primary.fringe_mesh_bod.position.x = 0
0040e722        build_track_fringe_mesh(&game->subgame.path_pairs[0x32].secondary, "Objects/Universe/Fringe.tga", -1f)
0040e72b        game->subgame.path_pairs[0x32].secondary.fringe_mesh_bod.position.z = 0f
0040e731        game->subgame.path_pairs[0x32].secondary.fringe_mesh_bod.position.y = 0f
0040e737        game->subgame.path_pairs[0x32].secondary.fringe_mesh_bod.position.x = 0
0040e75a        struct tColour color
0040e75a        store_color4f(&color, 1f, 1f, 1f, 0.600000024f)
0040e772        set_bod_object(&game->subgame.path_pairs[0x33].primary.bod, add_object_to_list(&g_object_list))
0040e791        initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[0x33], 6f, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040e79b        game->subgame.path_pairs[0x33].primary.bod.position.z = 0f
0040e7a1        game->subgame.path_pairs[0x33].primary.bod.position.y = 0f
0040e7a7        game->subgame.path_pairs[0x33].primary.bod.position.x = 0
0040e7b9        set_bod_object(&game->subgame.path_pairs[0x33].secondary.bod, add_object_to_list(&g_object_list))
0040e7c5        mirror_path_template_pair_x(&game->subgame.path_pairs[0x33].secondary, &game->subgame.path_pairs[0x33])
0040e7d2        game->subgame.path_pairs[0x33].secondary.bod.position.z = 0f
0040e7d8        game->subgame.path_pairs[0x33].secondary.bod.position.y = 0f
0040e7de        game->subgame.path_pairs[0x33].secondary.bod.position.x = 0
0040e7e4        build_track_fringe_mesh(&game->subgame.path_pairs[0x33], "Objects/Universe/Fringe.tga", 0f)
0040e7f5        game->subgame.path_pairs[0x33].primary.fringe_mesh_bod.position.z = 0f
0040e7fb        game->subgame.path_pairs[0x33].primary.fringe_mesh_bod.position.y = 0f
0040e801        game->subgame.path_pairs[0x33].primary.fringe_mesh_bod.position.x = 0
0040e807        build_track_fringe_mesh(&game->subgame.path_pairs[0x33].secondary, "Objects/Universe/Fringe.tga", 0f)
0040e80c        game->subgame.path_pairs[0x33].secondary.fringe_mesh_bod.position.z = 0f
0040e812        game->subgame.path_pairs[0x33].secondary.fringe_mesh_bod.position.y = 0f
0040e818        game->subgame.path_pairs[0x33].secondary.fringe_mesh_bod.position.x = 0
0040e830        game->subgame.path_pairs[0].primary.entry_transition_strip_mesh = game->subgame.path_pairs[0x33].primary.bod.object
0040e83c        game->subgame.path_pairs[0].primary.entry_base_strip_mesh = game->subgame.path_pairs[0].primary.bod.object
0040e842        game->subgame.path_pairs[0].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[0x33].secondary.bod.object
0040e848        game->subgame.path_pairs[0].secondary.entry_base_strip_mesh = game->subgame.path_pairs[0].secondary.bod.object
0040e861        set_bod_object(&game->subgame.path_pairs[0x34].primary.bod, add_object_to_list(&g_object_list))
0040e880        initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[0x34], 6f, 2, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040e88a        game->subgame.path_pairs[0x34].primary.bod.position.z = 0f
0040e890        game->subgame.path_pairs[0x34].primary.bod.position.y = 0f
0040e896        game->subgame.path_pairs[0x34].primary.bod.position.x = 0
0040e8a8        set_bod_object(&game->subgame.path_pairs[0x34].secondary.bod, add_object_to_list(&g_object_list))
0040e8b4        mirror_path_template_pair_x(&game->subgame.path_pairs[0x34].secondary, &game->subgame.path_pairs[0x34])
0040e8c1        game->subgame.path_pairs[0x34].secondary.bod.position.z = 0f
0040e8c7        game->subgame.path_pairs[0x34].secondary.bod.position.y = 0f
0040e8cd        game->subgame.path_pairs[0x34].secondary.bod.position.x = 0
0040e8d3        build_track_fringe_mesh(&game->subgame.path_pairs[0x34], "Objects/Universe/Fringe.tga", 0f)
0040e8e4        game->subgame.path_pairs[0x34].primary.fringe_mesh_bod.position.z = 0f
0040e8ea        game->subgame.path_pairs[0x34].primary.fringe_mesh_bod.position.y = 0f
0040e8f0        game->subgame.path_pairs[0x34].primary.fringe_mesh_bod.position.x = 0
0040e8f6        build_track_fringe_mesh(&game->subgame.path_pairs[0x34].secondary, "Objects/Universe/Fringe.tga", 0f)
0040e8fb        game->subgame.path_pairs[0x34].secondary.fringe_mesh_bod.position.z = 0f
0040e901        game->subgame.path_pairs[0x34].secondary.fringe_mesh_bod.position.y = 0f
0040e907        game->subgame.path_pairs[0x34].secondary.fringe_mesh_bod.position.x = 0
0040e91f        game->subgame.path_pairs[1].primary.entry_transition_strip_mesh = game->subgame.path_pairs[0x34].primary.bod.object
0040e92b        game->subgame.path_pairs[1].secondary.entry_base_strip_mesh = game->subgame.path_pairs[1].secondary.bod.object
0040e936        game->subgame.path_pairs[1].primary.entry_base_strip_mesh = game->subgame.path_pairs[1].primary.bod.object
0040e93c        game->subgame.path_pairs[1].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[0x34].secondary.bod.object
0040e950        set_bod_object(&game->subgame.path_pairs[0x35].primary.bod, add_object_to_list(&g_object_list))
0040e96f        initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[0x35], 8f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040e979        game->subgame.path_pairs[0x35].primary.bod.position.z = 0f
0040e97f        game->subgame.path_pairs[0x35].primary.bod.position.y = 0f
0040e985        game->subgame.path_pairs[0x35].primary.bod.position.x = 0
0040e997        set_bod_object(&game->subgame.path_pairs[0x35].secondary.bod, add_object_to_list(&g_object_list))
0040e9a3        mirror_path_template_pair_x(&game->subgame.path_pairs[0x35].secondary, &game->subgame.path_pairs[0x35])
0040e9a9        game->subgame.path_pairs[0x35].secondary.bod.position.z = 0f
0040e9af        game->subgame.path_pairs[0x35].secondary.bod.position.y = 0f
0040e9b5        game->subgame.path_pairs[0x35].secondary.bod.position.x = 0
0040e9c2        build_track_fringe_mesh(&game->subgame.path_pairs[0x35], "Objects/Universe/Fringe.tga", 0f)
0040e9d3        game->subgame.path_pairs[0x35].primary.fringe_mesh_bod.position.z = 0f
0040e9d9        game->subgame.path_pairs[0x35].primary.fringe_mesh_bod.position.y = 0f
0040e9df        game->subgame.path_pairs[0x35].primary.fringe_mesh_bod.position.x = 0
0040e9e5        build_track_fringe_mesh(&game->subgame.path_pairs[0x35].secondary, "Objects/Universe/Fringe.tga", 0f)
0040e9ea        game->subgame.path_pairs[0x35].secondary.fringe_mesh_bod.position.z = 0f
0040e9f0        game->subgame.path_pairs[0x35].secondary.fringe_mesh_bod.position.y = 0f
0040e9f6        game->subgame.path_pairs[0x35].secondary.fringe_mesh_bod.position.x = 0
0040ea0e        game->subgame.path_pairs[2].primary.entry_transition_strip_mesh = game->subgame.path_pairs[0x35].primary.bod.object
0040ea14        game->subgame.path_pairs[2].primary.entry_base_strip_mesh = game->subgame.path_pairs[2].primary.bod.object
0040ea1a        game->subgame.path_pairs[2].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[0x35].secondary.bod.object
0040ea2b        game->subgame.path_pairs[2].secondary.entry_base_strip_mesh = game->subgame.path_pairs[2].secondary.bod.object
0040ea3f        set_bod_object(&game->subgame.path_pairs[0x39].primary.bod, add_object_to_list(&g_object_list))
0040ea5e        initialize_looptheloopw_path_template_pair(&game->subgame.path_pairs[0x39], 8f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040ea68        game->subgame.path_pairs[0x39].primary.bod.position.z = 0f
0040ea6e        game->subgame.path_pairs[0x39].primary.bod.position.y = 0f
0040ea74        game->subgame.path_pairs[0x39].primary.bod.position.x = 0
0040ea86        set_bod_object(&game->subgame.path_pairs[0x39].secondary.bod, add_object_to_list(&g_object_list))
0040ea92        mirror_path_template_pair_x(&game->subgame.path_pairs[0x39].secondary, &game->subgame.path_pairs[0x39])
0040ea9f        game->subgame.path_pairs[0x39].secondary.bod.position.z = 0f
0040eaa5        game->subgame.path_pairs[0x39].secondary.bod.position.y = 0f
0040eaab        game->subgame.path_pairs[0x39].secondary.bod.position.x = 0
0040eab1        build_track_fringe_mesh(&game->subgame.path_pairs[0x39], "Objects/Universe/Fringe.tga", 0f)
0040eac2        game->subgame.path_pairs[0x39].primary.fringe_mesh_bod.position.z = 0f
0040eac8        game->subgame.path_pairs[0x39].primary.fringe_mesh_bod.position.y = 0f
0040eace        game->subgame.path_pairs[0x39].primary.fringe_mesh_bod.position.x = 0
0040ead4        build_track_fringe_mesh(&game->subgame.path_pairs[0x39].secondary, "Objects/Universe/Fringe.tga", 0f)
0040ead9        game->subgame.path_pairs[0x39].secondary.fringe_mesh_bod.position.z = 0f
0040eadf        game->subgame.path_pairs[0x39].secondary.fringe_mesh_bod.position.y = 0f
0040eae5        game->subgame.path_pairs[0x39].secondary.fringe_mesh_bod.position.x = 0
0040eaf1        game->subgame.path_pairs[6].primary.entry_transition_strip_mesh = game->subgame.path_pairs[0x39].primary.bod.object
0040eafd        game->subgame.path_pairs[6].primary.entry_base_strip_mesh = game->subgame.path_pairs[6].primary.bod.object
0040eb09        game->subgame.path_pairs[6].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[0x39].secondary.bod.object
0040eb1a        game->subgame.path_pairs[6].secondary.entry_base_strip_mesh = game->subgame.path_pairs[6].secondary.bod.object
0040eb2e        set_bod_object(&game->subgame.path_pairs[0x36].primary.bod, add_object_to_list(&g_object_list))
0040eb4d        initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[0x36], 3f, 2, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040eb57        game->subgame.path_pairs[0x36].primary.bod.position.z = 0f
0040eb5d        game->subgame.path_pairs[0x36].primary.bod.position.y = 0f
0040eb63        game->subgame.path_pairs[0x36].primary.bod.position.x = 0
0040eb75        set_bod_object(&game->subgame.path_pairs[0x36].secondary.bod, add_object_to_list(&g_object_list))
0040eb81        mirror_path_template_pair_x(&game->subgame.path_pairs[0x36].secondary, &game->subgame.path_pairs[0x36])
0040eb8e        game->subgame.path_pairs[0x36].secondary.bod.position.z = 0f
0040eb94        game->subgame.path_pairs[0x36].secondary.bod.position.y = 0f
0040eb9a        game->subgame.path_pairs[0x36].secondary.bod.position.x = 0
0040eba0        build_track_fringe_mesh(&game->subgame.path_pairs[0x36], "Objects/Universe/Fringe.tga", 0f)
0040ebb1        game->subgame.path_pairs[0x36].primary.fringe_mesh_bod.position.z = 0f
0040ebb7        game->subgame.path_pairs[0x36].primary.fringe_mesh_bod.position.y = 0f
0040ebbd        game->subgame.path_pairs[0x36].primary.fringe_mesh_bod.position.x = 0
0040ebc3        build_track_fringe_mesh(&game->subgame.path_pairs[0x36].secondary, "Objects/Universe/Fringe.tga", 0f)
0040ebc8        game->subgame.path_pairs[0x36].secondary.fringe_mesh_bod.position.z = 0f
0040ebce        game->subgame.path_pairs[0x36].secondary.fringe_mesh_bod.position.y = 0f
0040ebd4        game->subgame.path_pairs[0x36].secondary.fringe_mesh_bod.position.x = 0
0040ebe0        game->subgame.path_pairs[3].primary.entry_transition_strip_mesh = game->subgame.path_pairs[0x36].primary.bod.object
0040ebec        game->subgame.path_pairs[3].primary.entry_base_strip_mesh = game->subgame.path_pairs[3].primary.bod.object
0040ebf8        game->subgame.path_pairs[3].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[0x36].secondary.bod.object
0040ec04        game->subgame.path_pairs[3].secondary.entry_base_strip_mesh = game->subgame.path_pairs[3].secondary.bod.object
0040ec1d        set_bod_object(&game->subgame.path_pairs[0x37].primary.bod, add_object_to_list(&g_object_list))
0040ec3c        initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[0x37], 3f, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040ec46        game->subgame.path_pairs[0x37].primary.bod.position.z = 0f
0040ec4c        game->subgame.path_pairs[0x37].primary.bod.position.y = 0f
0040ec52        game->subgame.path_pairs[0x37].primary.bod.position.x = 0
0040ec64        set_bod_object(&game->subgame.path_pairs[0x37].secondary.bod, add_object_to_list(&g_object_list))
0040ec70        mirror_path_template_pair_x(&game->subgame.path_pairs[0x37].secondary, &game->subgame.path_pairs[0x37])
0040ec7d        game->subgame.path_pairs[0x37].secondary.bod.position.z = 0f
0040ec83        game->subgame.path_pairs[0x37].secondary.bod.position.y = 0f
0040ec89        game->subgame.path_pairs[0x37].secondary.bod.position.x = 0
0040ec8f        build_track_fringe_mesh(&game->subgame.path_pairs[0x37], "Objects/Universe/Fringe.tga", 0f)
0040eca0        game->subgame.path_pairs[0x37].primary.fringe_mesh_bod.position.z = 0f
0040eca6        game->subgame.path_pairs[0x37].primary.fringe_mesh_bod.position.y = 0f
0040ecac        game->subgame.path_pairs[0x37].primary.fringe_mesh_bod.position.x = 0
0040ecb2        build_track_fringe_mesh(&game->subgame.path_pairs[0x37].secondary, "Objects/Universe/Fringe.tga", 0f)
0040ecb7        game->subgame.path_pairs[0x37].secondary.fringe_mesh_bod.position.z = 0f
0040ecbd        game->subgame.path_pairs[0x37].secondary.fringe_mesh_bod.position.y = 0f
0040ecc3        game->subgame.path_pairs[0x37].secondary.fringe_mesh_bod.position.x = 0
0040eccf        game->subgame.path_pairs[4].primary.entry_transition_strip_mesh = game->subgame.path_pairs[0x37].primary.bod.object
0040ecdb        game->subgame.path_pairs[4].primary.entry_base_strip_mesh = game->subgame.path_pairs[4].primary.bod.object
0040ece7        game->subgame.path_pairs[4].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[0x37].secondary.bod.object
0040ecf8        game->subgame.path_pairs[4].secondary.entry_base_strip_mesh = game->subgame.path_pairs[4].secondary.bod.object
0040ed0c        set_bod_object(&game->subgame.path_pairs[0x38].primary.bod, add_object_to_list(&g_object_list))
0040ed2b        initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[0x38], 3f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040ed35        game->subgame.path_pairs[0x38].primary.bod.position.z = 0f
0040ed3b        game->subgame.path_pairs[0x38].primary.bod.position.y = 0f
0040ed41        game->subgame.path_pairs[0x38].primary.bod.position.x = 0
0040ed53        set_bod_object(&game->subgame.path_pairs[0x38].secondary.bod, add_object_to_list(&g_object_list))
0040ed5f        mirror_path_template_pair_x(&game->subgame.path_pairs[0x38].secondary, &game->subgame.path_pairs[0x38])
0040ed6c        game->subgame.path_pairs[0x38].secondary.bod.position.z = 0f
0040ed72        game->subgame.path_pairs[0x38].secondary.bod.position.y = 0f
0040ed78        game->subgame.path_pairs[0x38].secondary.bod.position.x = 0
0040ed7e        build_track_fringe_mesh(&game->subgame.path_pairs[0x38], "Objects/Universe/Fringe.tga", 0f)
0040ed8f        game->subgame.path_pairs[0x38].primary.fringe_mesh_bod.position.z = 0f
0040ed95        game->subgame.path_pairs[0x38].primary.fringe_mesh_bod.position.y = 0f
0040ed9b        game->subgame.path_pairs[0x38].primary.fringe_mesh_bod.position.x = 0
0040eda1        build_track_fringe_mesh(&game->subgame.path_pairs[0x38].secondary, "Objects/Universe/Fringe.tga", 0f)
0040eda6        game->subgame.path_pairs[0x38].secondary.fringe_mesh_bod.position.z = 0f
0040edac        game->subgame.path_pairs[0x38].secondary.fringe_mesh_bod.position.y = 0f
0040edb2        game->subgame.path_pairs[0x38].secondary.fringe_mesh_bod.position.x = 0
0040edbe        game->subgame.path_pairs[5].primary.entry_transition_strip_mesh = game->subgame.path_pairs[0x38].primary.bod.object
0040edca        game->subgame.path_pairs[5].primary.entry_base_strip_mesh = game->subgame.path_pairs[5].primary.bod.object
0040edd6        game->subgame.path_pairs[5].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[0x38].secondary.bod.object
0040ede7        game->subgame.path_pairs[5].secondary.entry_base_strip_mesh = game->subgame.path_pairs[5].secondary.bod.object
0040edfb        set_bod_object(&game->subgame.path_pairs[0x3a].primary.bod, add_object_to_list(&g_object_list))
0040ee1a        initialize_loopbow_path_template_pair(&game->subgame.path_pairs[0x3a], 6f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040ee24        game->subgame.path_pairs[0x3a].primary.bod.position.z = 0f
0040ee2a        game->subgame.path_pairs[0x3a].primary.bod.position.y = 0f
0040ee30        game->subgame.path_pairs[0x3a].primary.bod.position.x = 0
0040ee42        set_bod_object(&game->subgame.path_pairs[0x3a].secondary.bod, add_object_to_list(&g_object_list))
0040ee4e        mirror_path_template_pair_x(&game->subgame.path_pairs[0x3a].secondary, &game->subgame.path_pairs[0x3a])
0040ee5b        game->subgame.path_pairs[0x3a].secondary.bod.position.z = 0f
0040ee61        game->subgame.path_pairs[0x3a].secondary.bod.position.y = 0f
0040ee67        game->subgame.path_pairs[0x3a].secondary.bod.position.x = 0
0040ee6d        build_track_fringe_mesh(&game->subgame.path_pairs[0x3a], "Objects/Universe/Fringe.tga", 0f)
0040ee7e        game->subgame.path_pairs[0x3a].primary.fringe_mesh_bod.position.z = 0f
0040ee84        game->subgame.path_pairs[0x3a].primary.fringe_mesh_bod.position.y = 0f
0040ee8a        game->subgame.path_pairs[0x3a].primary.fringe_mesh_bod.position.x = 0
0040ee90        build_track_fringe_mesh(&game->subgame.path_pairs[0x3a].secondary, "Objects/Universe/Fringe.tga", 0f)
0040ee95        game->subgame.path_pairs[0x3a].secondary.fringe_mesh_bod.position.z = 0f
0040ee9b        game->subgame.path_pairs[0x3a].secondary.fringe_mesh_bod.position.y = 0f
0040eea1        game->subgame.path_pairs[0x3a].secondary.fringe_mesh_bod.position.x = 0
0040eead        game->subgame.path_pairs[7].primary.entry_transition_strip_mesh = game->subgame.path_pairs[0x3a].primary.bod.object
0040eeb9        game->subgame.path_pairs[7].primary.entry_base_strip_mesh = game->subgame.path_pairs[7].primary.bod.object
0040eec5        game->subgame.path_pairs[7].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[0x3a].secondary.bod.object
0040eed1        game->subgame.path_pairs[7].secondary.entry_base_strip_mesh = game->subgame.path_pairs[7].secondary.bod.object
0040eeea        set_bod_object(&game->subgame.path_pairs[0x3e].primary.bod, add_object_to_list(&g_object_list))
0040ef09        initialize_invert_path_template_pair(&game->subgame.path_pairs[0x3e], 6f, 8, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040ef13        game->subgame.path_pairs[0x3e].primary.bod.position.z = 0f
0040ef19        game->subgame.path_pairs[0x3e].primary.bod.position.y = 0f
0040ef1f        game->subgame.path_pairs[0x3e].primary.bod.position.x = 0
0040ef31        set_bod_object(&game->subgame.path_pairs[0x3e].secondary.bod, add_object_to_list(&g_object_list))
0040ef3d        mirror_path_template_pair_x(&game->subgame.path_pairs[0x3e].secondary, &game->subgame.path_pairs[0x3e])
0040ef4a        game->subgame.path_pairs[0x3e].secondary.bod.position.z = 0f
0040ef50        game->subgame.path_pairs[0x3e].secondary.bod.position.y = 0f
0040ef56        game->subgame.path_pairs[0x3e].secondary.bod.position.x = 0
0040ef5c        build_track_fringe_mesh(&game->subgame.path_pairs[0x3e], "Objects/Universe/Fringe.tga", 0f)
0040ef6d        game->subgame.path_pairs[0x3e].primary.fringe_mesh_bod.position.z = 0f
0040ef73        game->subgame.path_pairs[0x3e].primary.fringe_mesh_bod.position.y = 0f
0040ef79        game->subgame.path_pairs[0x3e].primary.fringe_mesh_bod.position.x = 0
0040ef7f        build_track_fringe_mesh(&game->subgame.path_pairs[0x3e].secondary, "Objects/Universe/Fringe.tga", 0f)
0040ef84        game->subgame.path_pairs[0x3e].secondary.fringe_mesh_bod.position.z = 0f
0040ef8a        game->subgame.path_pairs[0x3e].secondary.fringe_mesh_bod.position.y = 0f
0040ef90        game->subgame.path_pairs[0x3e].secondary.fringe_mesh_bod.position.x = 0
0040ef9c        game->subgame.path_pairs[0x29].primary.entry_transition_strip_mesh = game->subgame.path_pairs[0x3e].primary.bod.object
0040efa8        game->subgame.path_pairs[0x29].primary.entry_base_strip_mesh = game->subgame.path_pairs[0x29].primary.bod.object
0040efb4        game->subgame.path_pairs[0x29].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[0x3e].secondary.bod.object
0040efc5        game->subgame.path_pairs[0x29].secondary.entry_base_strip_mesh = game->subgame.path_pairs[0x29].secondary.bod.object
0040efd9        set_bod_object(&game->subgame.path_pairs[0x3b].primary.bod, add_object_to_list(&g_object_list))
0040eff8        initialize_loopout_path_template_pair(&game->subgame.path_pairs[0x3b], 3f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040f002        game->subgame.path_pairs[0x3b].primary.bod.position.z = 0f
0040f008        game->subgame.path_pairs[0x3b].primary.bod.position.y = 0f
0040f00e        game->subgame.path_pairs[0x3b].primary.bod.position.x = 0
0040f020        set_bod_object(&game->subgame.path_pairs[0x3b].secondary.bod, add_object_to_list(&g_object_list))
0040f02c        mirror_path_template_pair_x(&game->subgame.path_pairs[0x3b].secondary, &game->subgame.path_pairs[0x3b])
0040f039        game->subgame.path_pairs[0x3b].secondary.bod.position.z = 0f
0040f03f        game->subgame.path_pairs[0x3b].secondary.bod.position.y = 0f
0040f045        game->subgame.path_pairs[0x3b].secondary.bod.position.x = 0
0040f04b        build_track_fringe_mesh(&game->subgame.path_pairs[0x3b], "Objects/Universe/Fringe.tga", 0f)
0040f05c        game->subgame.path_pairs[0x3b].primary.fringe_mesh_bod.position.z = 0f
0040f062        game->subgame.path_pairs[0x3b].primary.fringe_mesh_bod.position.y = 0f
0040f068        game->subgame.path_pairs[0x3b].primary.fringe_mesh_bod.position.x = 0
0040f06e        build_track_fringe_mesh(&game->subgame.path_pairs[0x3b].secondary, "Objects/Universe/Fringe.tga", 0f)
0040f073        game->subgame.path_pairs[0x3b].secondary.fringe_mesh_bod.position.z = 0f
0040f079        game->subgame.path_pairs[0x3b].secondary.fringe_mesh_bod.position.y = 0f
0040f07f        game->subgame.path_pairs[0x3b].secondary.fringe_mesh_bod.position.x = 0
0040f08b        game->subgame.path_pairs[0x19].primary.entry_transition_strip_mesh = game->subgame.path_pairs[0x3b].primary.bod.object
0040f097        game->subgame.path_pairs[0x19].primary.entry_base_strip_mesh = game->subgame.path_pairs[0x19].primary.bod.object
0040f0a3        game->subgame.path_pairs[0x19].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[0x3b].secondary.bod.object
0040f0b4        game->subgame.path_pairs[0x19].secondary.entry_base_strip_mesh = game->subgame.path_pairs[0x19].secondary.bod.object
0040f0c8        set_bod_object(&game->subgame.path_pairs[0x3d].primary.bod, add_object_to_list(&g_object_list))
0040f0e7        initialize_loopout_path_template_pair(&game->subgame.path_pairs[0x3d], 5f, 4, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040f0f1        game->subgame.path_pairs[0x3d].primary.bod.position.z = 0f
0040f0f7        game->subgame.path_pairs[0x3d].primary.bod.position.y = 0f
0040f0fd        game->subgame.path_pairs[0x3d].primary.bod.position.x = 0
0040f10f        set_bod_object(&game->subgame.path_pairs[0x3d].secondary.bod, add_object_to_list(&g_object_list))
0040f11b        mirror_path_template_pair_x(&game->subgame.path_pairs[0x3d].secondary, &game->subgame.path_pairs[0x3d])
0040f128        game->subgame.path_pairs[0x3d].secondary.bod.position.z = 0f
0040f12e        game->subgame.path_pairs[0x3d].secondary.bod.position.y = 0f
0040f134        game->subgame.path_pairs[0x3d].secondary.bod.position.x = 0
0040f13a        build_track_fringe_mesh(&game->subgame.path_pairs[0x3d], "Objects/Universe/Fringe.tga", 0f)
0040f13f        game->subgame.path_pairs[0x3d].primary.fringe_mesh_bod.position.z = 0f
0040f145        game->subgame.path_pairs[0x3d].primary.fringe_mesh_bod.position.y = 0f
0040f14b        game->subgame.path_pairs[0x3d].primary.fringe_mesh_bod.position.x = 0
0040f15d        build_track_fringe_mesh(&game->subgame.path_pairs[0x3d].secondary, "Objects/Universe/Fringe.tga", 0f)
0040f162        game->subgame.path_pairs[0x3d].secondary.fringe_mesh_bod.position.z = 0f
0040f168        game->subgame.path_pairs[0x3d].secondary.fringe_mesh_bod.position.y = 0f
0040f16e        game->subgame.path_pairs[0x3d].secondary.fringe_mesh_bod.position.x = 0
0040f17a        game->subgame.path_pairs[0x1b].primary.entry_transition_strip_mesh = game->subgame.path_pairs[0x3d].primary.bod.object
0040f186        game->subgame.path_pairs[0x1b].primary.entry_base_strip_mesh = game->subgame.path_pairs[0x1b].primary.bod.object
0040f192        game->subgame.path_pairs[0x1b].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[0x3d].secondary.bod.object
0040f19e        game->subgame.path_pairs[0x1b].secondary.entry_base_strip_mesh = game->subgame.path_pairs[0x1b].secondary.bod.object
0040f1b7        set_bod_object(&game->subgame.path_pairs[0x3c].primary.bod, add_object_to_list(&g_object_list))
0040f1d6        initialize_loopout_path_template_pair(&game->subgame.path_pairs[0x3c], 3f, 3, 1, "Objects/World00/Slide0.tga", "Objects/World00/Back.tga", "Objects/Path/VeryDark.tga")
0040f1e1        zero_vector3(&game->subgame.path_pairs[0x3c].primary.bod.position)
0040f1f7        set_bod_object(&game->subgame.path_pairs[0x3c].secondary.bod, add_object_to_list(&g_object_list))
0040f203        mirror_path_template_pair_x(&game->subgame.path_pairs[0x3c].secondary, &game->subgame.path_pairs[0x3c])
0040f20e        zero_vector3(&game->subgame.path_pairs[0x3c].secondary.bod.position)
0040f21b        build_track_fringe_mesh(&game->subgame.path_pairs[0x3c], "Objects/Universe/Fringe.tga", 0f)
0040f226        zero_vector3(&game->subgame.path_pairs[0x3c].primary.fringe_mesh_bod.position)
0040f237        build_track_fringe_mesh(&game->subgame.path_pairs[0x3c].secondary, "Objects/Universe/Fringe.tga", 0f)
0040f242        zero_vector3(&game->subgame.path_pairs[0x3c].secondary.fringe_mesh_bod.position)
0040f252        game->subgame.path_pairs[0x1a].primary.entry_transition_strip_mesh = game->subgame.path_pairs[0x3c].primary.bod.object
0040f25e        game->subgame.path_pairs[0x1a].primary.entry_base_strip_mesh = game->subgame.path_pairs[0x1a].primary.bod.object
0040f26a        game->subgame.path_pairs[0x1a].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[0x3c].secondary.bod.object
0040f276        game->subgame.path_pairs[0x1a].secondary.entry_base_strip_mesh = game->subgame.path_pairs[0x1a].secondary.bod.object
0040f295        set_bod_object(&game->subgame.player.presentation.cutscene_animation_slots, add_object_to_list(&g_object_list))
0040f2a2        char* eax_228 = find_case_insensitive_substring("Test:", game->directx_loader.animation_bytes)
0040f2ac        void mesh_name
0040f2ac        if (eax_228 == 0)
0040f2f3        rstrcpy_checked_ascii(&mesh_name, "turbo-base-000.x")
0040f2b4        char* eax_229 = find_case_insensitive_substring(":", eax_228)
0040f2b9        char i = eax_229[1]
0040f2c5        char* eax_230 = &mesh_name
0040f2c9        while (i != 0x2e)
0040f2d1        *eax_230 = i
0040f2d3        i = eax_230[&eax_229[1] - &mesh_name + 1]
0040f2d7        eax_230 = &eax_230[1]
0040f2dd        *eax_230 = 0x2e
0040f2e1        eax_230[1] = 0x78
0040f2e4        eax_230[2] = 0
0040f309        load_x_animation_clip(&game->directx_loader, &mesh_name, game->subgame.player.presentation.cutscene_animation_slots[0].body.bod.object)
0040f321        set_bod_object(&game->subgame.player.presentation.body.bod, add_object_to_list(&g_object_list))
0040f334        load_x_animation_clip(&game->directx_loader, &mesh_name, game->subgame.player.presentation.body.bod.object)
0040f34a        set_bod_object(&game->subgame.player.presentation.cutscene_animation_slots[1].body.bod, add_object_to_list(&g_object_list))
0040f35d        load_x_animation_clip(&game->directx_loader, "turbo-move-000.x", game->subgame.player.presentation.cutscene_animation_slots[1].body.bod.object)
0040f373        set_bod_object(&game->subgame.player.presentation.cutscene_animation_slots[2].body.bod, add_object_to_list(&g_object_list))
0040f386        load_x_animation_clip(&game->directx_loader, "turbo-bobalong-000.x", game->subgame.player.presentation.cutscene_animation_slots[2].body.bod.object)
0040f39c        set_bod_object(&game->subgame.player.presentation.cutscene_animation_slots[3].body.bod, add_object_to_list(&g_object_list))
0040f3af        load_x_animation_clip(&game->directx_loader, "turbo-lookbackleft-000.x", game->subgame.player.presentation.cutscene_animation_slots[3].body.bod.object)
0040f3c5        set_bod_object(&game->subgame.player.presentation.cutscene_animation_slots[4].body.bod, add_object_to_list(&g_object_list))
0040f3d8        load_x_animation_clip(&game->directx_loader, "turbo-lookbackright-000.x", game->subgame.player.presentation.cutscene_animation_slots[4].body.bod.object)
0040f3ee        set_bod_object(&game->subgame.player.presentation.cutscene_animation_slots[5].body.bod, add_object_to_list(&g_object_list))
0040f401        load_x_animation_clip(&game->directx_loader, "turbo-fall-000.x", game->subgame.player.presentation.cutscene_animation_slots[5].body.bod.object)
0040f417        set_bod_object(&game->subgame.player.presentation.cutscene_animation_slots[6].body.bod, add_object_to_list(&g_object_list))
0040f42a        load_x_animation_clip(&game->directx_loader, "turbo-damaged-000.x", game->subgame.player.presentation.cutscene_animation_slots[6].body.bod.object)
0040f440        set_bod_object(&game->subgame.player.presentation.cutscene_animation_slots[7].body.bod, add_object_to_list(&g_object_list))
0040f453        load_x_animation_clip(&game->directx_loader, "turbo-intoshell-000.x", game->subgame.player.presentation.cutscene_animation_slots[7].body.bod.object)
0040f469        set_bod_object(&game->subgame.player.presentation.cutscene_animation_slots[8].body.bod, add_object_to_list(&g_object_list))
0040f47c        load_x_animation_clip(&game->directx_loader, "turbo-skidstop-000.x", game->subgame.player.presentation.cutscene_animation_slots[8].body.bod.object)
0040f492        set_bod_object(&game->subgame.player.presentation.cutscene_animation_slots[9].body.bod, add_object_to_list(&g_object_list))
0040f4a5        load_x_animation_clip(&game->directx_loader, "turbo-talk-000.x", game->subgame.player.presentation.cutscene_animation_slots[9].body.bod.object)
0040f4bb        set_bod_object(&game->subgame.player.presentation.snail_hotspot_body.bod, add_object_to_list(&g_object_list))
0040f4d4        load_x_mesh(&game->directx_loader, "TurboHotSpots.x", game->subgame.player.presentation.snail_hotspot_body.bod.object, 2)
0040f4df        build_snail_hotspots(&game->subgame.player.presentation)
0040f4ea        int32_t var_128_5 = 0xa
0040f4f2        struct Object** var_12c = &game->subgame.player.presentation.cutscene_animation_slots[0].body.bod.object
0040f53d        bool cond:5_1
0040f4fb        struct Object* object = (var_12c - 0x432870)->subgame.player.presentation.cutscene_animation_slots[0].body.bod.object
0040f503        object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES
0040f508        apply_object_toon((var_12c - 0x432870)->subgame.player.presentation.cutscene_animation_slots[0].body.bod.object, 0)
0040f511        struct Object* object_14 = (var_12c - 0x432870)->subgame.player.presentation.cutscene_animation_slots[0].body.bod.object
0040f513        struct Object** eax_249 = &var_12c[0x20]
0040f518        var_12c = eax_249
0040f51c        object_14->distort.z_wave = 0
0040f525        (eax_249 - 0x4328f0)->subgame.player.presentation.cutscene_animation_slots[0].body.bod.object->distort.y_squash = 0f
0040f532        cond:5_1 = var_128_5 != 1
0040f533        (eax_249 - 0x4328f0)->subgame.player.presentation.cutscene_animation_slots[0].body.bod.object->distort.xyz_scale = 0f
0040f539        var_128_5 -= 1
0040f53d        do while (cond:5_1)
0040f53f        struct Object* object_1 = game->subgame.player.presentation.body.bod.object
0040f54c        object_1->flags |= OBJECT_FLAG_DYNAMIC_VERTICES
0040f555        apply_object_toon(game->subgame.player.presentation.body.bod.object, 0)
0040f560        game->subgame.player.presentation.body.bod.object->distort.z_wave = 0
0040f56c        game->subgame.player.presentation.body.bod.object->distort.y_squash = 0f
0040f578        game->subgame.player.presentation.body.bod.object->distort.xyz_scale = 0f
0040f58f        set_bod_object(&game->subgame.player.presentation.jetpack_channel.body.bod, add_object_to_list(&g_object_list))
0040f5a2        load_x_animation_clip(&game->directx_loader, "jetpack-base-000.x", game->subgame.player.presentation.jetpack_channel.body.bod.object)
0040f5b8        set_bod_object(&game->subgame.player.presentation.jetpack_channel.animation_slots, add_object_to_list(&g_object_list))
0040f5cb        load_x_animation_clip(&game->directx_loader, "jetpack-base-000.x", game->subgame.player.presentation.jetpack_channel.animation_slots[0].body.bod.object)
0040f5e1        set_bod_object(&game->subgame.player.presentation.jetpack_channel.animation_slots[1].body.bod, add_object_to_list(&g_object_list))
0040f5f4        load_x_animation_clip(&game->directx_loader, "jetpack-draw-000.x", game->subgame.player.presentation.jetpack_channel.animation_slots[1].body.bod.object)
0040f5ff        int32_t var_128_6 = 2
0040f603        struct Object** var_12c_1 = &game->subgame.player.presentation.jetpack_channel.animation_slots[0].body.bod.object
0040f64e        bool cond:6_1
0040f60c        struct Object* object_2 = (var_12c_1 - 0x433a54)->subgame.player.presentation.jetpack_channel.animation_slots[0].body.bod.object
0040f614        object_2->flags |= OBJECT_FLAG_DYNAMIC_VERTICES
0040f619        apply_object_toon((var_12c_1 - 0x433a54)->subgame.player.presentation.jetpack_channel.animation_slots[0].body.bod.object, 0)
0040f622        struct Object* object_17 = (var_12c_1 - 0x433a54)->subgame.player.presentation.jetpack_channel.animation_slots[0].body.bod.object
0040f624        struct Object** eax_259 = &var_12c_1[0x20]
0040f629        var_12c_1 = eax_259
0040f62d        object_17->distort.z_wave = 0
0040f636        (eax_259 - 0x433ad4)->subgame.player.presentation.jetpack_channel.animation_slots[0].body.bod.object->distort.y_squash = 0f
0040f643        cond:6_1 = var_128_6 != 1
0040f644        (eax_259 - 0x433ad4)->subgame.player.presentation.jetpack_channel.animation_slots[0].body.bod.object->distort.xyz_scale = 0f
0040f64a        var_128_6 -= 1
0040f64e        do while (cond:6_1)
0040f650        struct Object* object_3 = game->subgame.player.presentation.jetpack_channel.body.bod.object
0040f65d        object_3->flags |= OBJECT_FLAG_DYNAMIC_VERTICES
0040f666        apply_object_toon(game->subgame.player.presentation.jetpack_channel.body.bod.object, 0)
0040f671        game->subgame.player.presentation.jetpack_channel.body.bod.object->distort.z_wave = 0
0040f67d        game->subgame.player.presentation.jetpack_channel.body.bod.object->distort.y_squash = 0f
0040f68e        game->subgame.player.presentation.jetpack_channel.body.bod.object->distort.xyz_scale = 0f
0040f6a0        set_bod_object(&game->subgame.player.presentation.weapon_channels, add_object_to_list(&g_object_list))
0040f6b3        load_x_animation_clip(&game->directx_loader, "blasterleft-base-000.x", game->subgame.player.presentation.weapon_channels[0].body.bod.object)
0040f6c9        set_bod_object(&game->subgame.player.presentation.weapon_channels[0].animation_slots, add_object_to_list(&g_object_list))
0040f6dc        load_x_animation_clip(&game->directx_loader, "blasterleft-base-000.x", game->subgame.player.presentation.weapon_channels[0].animation_slots[0].body.bod.object)
0040f6f2        set_bod_object(&game->subgame.player.presentation.weapon_channels[0].animation_slots[1].body.bod, add_object_to_list(&g_object_list))
0040f705        load_x_animation_clip(&game->directx_loader, "blasterleft-draw-000.x", game->subgame.player.presentation.weapon_channels[0].animation_slots[1].body.bod.object)
0040f71b        set_bod_object(&game->subgame.player.presentation.weapon_channels[0].animation_slots[2].body.bod, add_object_to_list(&g_object_list))
0040f72e        load_x_animation_clip(&game->directx_loader, "blasterleft-fire-000.x", game->subgame.player.presentation.weapon_channels[0].animation_slots[2].body.bod.object)
0040f744        set_bod_object(&game->subgame.player.presentation.weapon_channels[0].animation_slots[3].body.bod, add_object_to_list(&g_object_list))
0040f757        load_x_animation_clip(&game->directx_loader, "Laserleft-base-000.x", game->subgame.player.presentation.weapon_channels[0].animation_slots[3].body.bod.object)
0040f76d        set_bod_object(&game->subgame.player.presentation.weapon_channels[0].animation_slots[4].body.bod, add_object_to_list(&g_object_list))
0040f780        load_x_animation_clip(&game->directx_loader, "Laserleft-draw-000.x", game->subgame.player.presentation.weapon_channels[0].animation_slots[4].body.bod.object)
0040f78b        int32_t var_128_7 = 5
0040f793        struct Object** var_12c_2 = &game->subgame.player.presentation.weapon_channels[0].animation_slots[0].body.bod.object
0040f7de        bool cond:7_1
0040f79c        struct Object* object_4 = (var_12c_2 - 0x432ec0)->subgame.player.presentation.weapon_channels[0].animation_slots[0].body.bod.object
0040f7a4        object_4->flags |= OBJECT_FLAG_DYNAMIC_VERTICES
0040f7a9        apply_object_toon((var_12c_2 - 0x432ec0)->subgame.player.presentation.weapon_channels[0].animation_slots[0].body.bod.object, 0)
0040f7b2        struct Object* object_15 = (var_12c_2 - 0x432ec0)->subgame.player.presentation.weapon_channels[0].animation_slots[0].body.bod.object
0040f7b4        struct Object** eax_273 = &var_12c_2[0x20]
0040f7b9        var_12c_2 = eax_273
0040f7bd        object_15->distort.z_wave = 0
0040f7c6        (eax_273 - 0x432f40)->subgame.player.presentation.weapon_channels[0].animation_slots[0].body.bod.object->distort.y_squash = 0f
0040f7d3        cond:7_1 = var_128_7 != 1
0040f7d4        (eax_273 - 0x432f40)->subgame.player.presentation.weapon_channels[0].animation_slots[0].body.bod.object->distort.xyz_scale = 0f
0040f7da        var_128_7 -= 1
0040f7de        do while (cond:7_1)
0040f7e0        struct Object* object_5 = game->subgame.player.presentation.weapon_channels[0].body.bod.object
0040f7ed        object_5->flags |= OBJECT_FLAG_DYNAMIC_VERTICES
0040f7f6        apply_object_toon(game->subgame.player.presentation.weapon_channels[0].body.bod.object, 0)
0040f801        game->subgame.player.presentation.weapon_channels[0].body.bod.object->distort.z_wave = 0
0040f80d        game->subgame.player.presentation.weapon_channels[0].body.bod.object->distort.y_squash = 0f
0040f819        game->subgame.player.presentation.weapon_channels[0].body.bod.object->distort.xyz_scale = 0f
0040f830        set_bod_object(&game->subgame.player.presentation.weapon_channels[1].body.bod, add_object_to_list(&g_object_list))
0040f843        load_x_animation_clip(&game->directx_loader, "blasterRight-base-000.x", game->subgame.player.presentation.weapon_channels[1].body.bod.object)
0040f859        set_bod_object(&game->subgame.player.presentation.weapon_channels[1].animation_slots, add_object_to_list(&g_object_list))
0040f86c        load_x_animation_clip(&game->directx_loader, "blasterRight-base-000.x", game->subgame.player.presentation.weapon_channels[1].animation_slots[0].body.bod.object)
0040f882        set_bod_object(&game->subgame.player.presentation.weapon_channels[1].animation_slots[1].body.bod, add_object_to_list(&g_object_list))
0040f895        load_x_animation_clip(&game->directx_loader, "blasterRight-draw-000.x", game->subgame.player.presentation.weapon_channels[1].animation_slots[1].body.bod.object)
0040f8ab        set_bod_object(&game->subgame.player.presentation.weapon_channels[1].animation_slots[2].body.bod, add_object_to_list(&g_object_list))
0040f8be        load_x_animation_clip(&game->directx_loader, "blasterRight-fire-000.x", game->subgame.player.presentation.weapon_channels[1].animation_slots[2].body.bod.object)
0040f8d4        set_bod_object(&game->subgame.player.presentation.weapon_channels[1].animation_slots[3].body.bod, add_object_to_list(&g_object_list))
0040f8e7        load_x_animation_clip(&game->directx_loader, "Laserright-base-000.x", game->subgame.player.presentation.weapon_channels[1].animation_slots[3].body.bod.object)
0040f8fd        set_bod_object(&game->subgame.player.presentation.weapon_channels[1].animation_slots[4].body.bod, add_object_to_list(&g_object_list))
0040f910        load_x_animation_clip(&game->directx_loader, "Laserright-draw-000.x", game->subgame.player.presentation.weapon_channels[1].animation_slots[4].body.bod.object)
0040f91b        int32_t var_128_8 = 5
0040f923        struct Object** var_12c_3 = &game->subgame.player.presentation.weapon_channels[1].animation_slots[0].body.bod.object
0040f96e        bool cond:8_1
0040f92c        struct Object* object_6 = (var_12c_3 - 0x43329c)->subgame.player.presentation.weapon_channels[1].animation_slots[0].body.bod.object
0040f934        object_6->flags |= OBJECT_FLAG_DYNAMIC_VERTICES
0040f939        apply_object_toon((var_12c_3 - 0x43329c)->subgame.player.presentation.weapon_channels[1].animation_slots[0].body.bod.object, 0)
0040f942        struct Object* object_18 = (var_12c_3 - 0x43329c)->subgame.player.presentation.weapon_channels[1].animation_slots[0].body.bod.object
0040f944        struct Object** eax_287 = &var_12c_3[0x20]
0040f949        var_12c_3 = eax_287
0040f94d        object_18->distort.z_wave = 0
0040f956        (eax_287 - 0x43331c)->subgame.player.presentation.weapon_channels[1].animation_slots[0].body.bod.object->distort.y_squash = 0f
0040f963        cond:8_1 = var_128_8 != 1
0040f964        (eax_287 - 0x43331c)->subgame.player.presentation.weapon_channels[1].animation_slots[0].body.bod.object->distort.xyz_scale = 0f
0040f96a        var_128_8 -= 1
0040f96e        do while (cond:8_1)
0040f970        struct Object* object_7 = game->subgame.player.presentation.weapon_channels[1].body.bod.object
0040f97d        object_7->flags |= OBJECT_FLAG_DYNAMIC_VERTICES
0040f986        apply_object_toon(game->subgame.player.presentation.weapon_channels[1].body.bod.object, 0)
0040f991        game->subgame.player.presentation.weapon_channels[1].body.bod.object->distort.z_wave = 0
0040f99d        game->subgame.player.presentation.weapon_channels[1].body.bod.object->distort.y_squash = 0f
0040f9ae        game->subgame.player.presentation.weapon_channels[1].body.bod.object->distort.xyz_scale = 0f
0040f9c0        set_bod_object(&game->subgame.player.presentation.weapon_channels[2].body.bod, add_object_to_list(&g_object_list))
0040f9d3        load_x_animation_clip(&game->directx_loader, "blasterTop-base-000.x", game->subgame.player.presentation.weapon_channels[2].body.bod.object)
0040f9e9        set_bod_object(&game->subgame.player.presentation.weapon_channels[2].animation_slots, add_object_to_list(&g_object_list))
0040f9fc        load_x_animation_clip(&game->directx_loader, "blasterTop-base-000.x", game->subgame.player.presentation.weapon_channels[2].animation_slots[0].body.bod.object)
0040fa12        set_bod_object(&game->subgame.player.presentation.weapon_channels[2].animation_slots[1].body.bod, add_object_to_list(&g_object_list))
0040fa25        load_x_animation_clip(&game->directx_loader, "blasterTop-draw-000.x", game->subgame.player.presentation.weapon_channels[2].animation_slots[1].body.bod.object)
0040fa3b        set_bod_object(&game->subgame.player.presentation.weapon_channels[2].animation_slots[2].body.bod, add_object_to_list(&g_object_list))
0040fa4e        load_x_animation_clip(&game->directx_loader, "blasterTop-fire-000.x", game->subgame.player.presentation.weapon_channels[2].animation_slots[2].body.bod.object)
0040fa64        set_bod_object(&game->subgame.player.presentation.weapon_channels[2].animation_slots[3].body.bod, add_object_to_list(&g_object_list))
0040fa77        load_x_animation_clip(&game->directx_loader, "rocketlauncher-base-000.x", game->subgame.player.presentation.weapon_channels[2].animation_slots[3].body.bod.object)
0040fa8d        set_bod_object(&game->subgame.player.presentation.weapon_channels[2].animation_slots[4].body.bod, add_object_to_list(&g_object_list))
0040faa0        load_x_animation_clip(&game->directx_loader, "rocketlauncher-draw-000.x", game->subgame.player.presentation.weapon_channels[2].animation_slots[4].body.bod.object)
0040faab        int32_t var_128_9 = 5
0040fab3        struct Object** var_12c_4 = &game->subgame.player.presentation.weapon_channels[2].animation_slots[0].body.bod.object
0040fafe        bool cond:9_1
0040fabc        struct Object* object_8 = (var_12c_4 - 0x433678)->subgame.player.presentation.weapon_channels[2].animation_slots[0].body.bod.object
0040fac4        object_8->flags |= OBJECT_FLAG_DYNAMIC_VERTICES
0040fac9        apply_object_toon((var_12c_4 - 0x433678)->subgame.player.presentation.weapon_channels[2].animation_slots[0].body.bod.object, 0)
0040fad2        struct Object* object_16 = (var_12c_4 - 0x433678)->subgame.player.presentation.weapon_channels[2].animation_slots[0].body.bod.object
0040fad4        struct Object** eax_301 = &var_12c_4[0x20]
0040fad9        var_12c_4 = eax_301
0040fadd        object_16->distort.z_wave = 0
0040fae6        (eax_301 - 0x4336f8)->subgame.player.presentation.weapon_channels[2].animation_slots[0].body.bod.object->distort.y_squash = 0f
0040faf3        cond:9_1 = var_128_9 != 1
0040faf4        (eax_301 - 0x4336f8)->subgame.player.presentation.weapon_channels[2].animation_slots[0].body.bod.object->distort.xyz_scale = 0f
0040fafa        var_128_9 -= 1
0040fafe        do while (cond:9_1)
0040fb00        struct Object* object_9 = game->subgame.player.presentation.weapon_channels[2].body.bod.object
0040fb0d        object_9->flags |= OBJECT_FLAG_DYNAMIC_VERTICES
0040fb16        apply_object_toon(game->subgame.player.presentation.weapon_channels[2].body.bod.object, 0)
0040fb28        game->subgame.player.presentation.weapon_channels[2].body.bod.object->distort.z_wave = 0
0040fb34        game->subgame.player.presentation.weapon_channels[2].body.bod.object->distort.y_squash = 0f
0040fb40        game->subgame.player.presentation.weapon_channels[2].body.bod.object->distort.xyz_scale = 0f
0040fb5c        game->subgame.player.presentation.snail_skin.material_overrides[0] = get_or_create_texture_ref(&g_texture_refs, "x/snail-turbo.tga", 0, 0)
0040fb73        game->subgame.player.presentation.snail_skin.material_overrides[1] = get_or_create_texture_ref(&g_texture_refs, "x/snail-turbo-damage.tga", 0, 0)
0040fb83        game->subgame.player.presentation.snail_skin.material_overrides[2] = get_or_create_texture_ref(&g_texture_refs, "x/snail-turbo-invincible.tga", 0, 0)
0040fb95        set_bod_object(&game->subgame.player.presentation.invincible_shell.body.bod, add_object_to_list(&g_object_list))
0040fbaa        load_x_mesh(&game->directx_loader, "invincible-base-000.x", game->subgame.player.presentation.invincible_shell.body.bod.object, 1)
0040fbaf        struct Object* object_10 = game->subgame.player.presentation.invincible_shell.body.bod.object
0040fbba        object_10->flags &= ~OBJECT_FLAG_DISABLE_CULLING
0040fbcd        set_bod_object(&game->subgame.player.golb_shots[0].tertiary_body.bod, add_object_to_list(&g_object_list))
0040fbe2        load_x_mesh(&game->directx_loader, "rocket-base-000.x", game->subgame.player.golb_shots[0].tertiary_body.bod.object, 1)
0040fbe7        struct Object** esi_2 = &game->subgame.player.golb_shots[0].vapour.body.bod.object
0040fbed        int32_t var_128_10 = 0xc
0040fc5d        bool cond:10_1
0040fc03        set_bod_object(&esi_2[-9], add_object_to_list(&g_object_list))
0040fc08        struct Object* object_11 = (esi_2 - 0x430270)->subgame.player.golb_shots[0].vapour.body.bod.object
0040fc13        object_11->flags |= OBJECT_FLAG_DYNAMIC_VERTICES | OBJECT_FLAG_DISABLE_CULLING
0040fc18        (esi_2 - 0x430270)->subgame.player.golb_shots[0].vapour.body.bod.object->blend_mode = 9
0040fc27        load_object_definition("Objects/VapourLazer", (esi_2 - 0x430270)->subgame.player.golb_shots[0].vapour.body.bod.object)
0040fc3a        initialize_vapour(&esi_2[-9], (esi_2 - 0x430270)->subgame.player.golb_shots[0].vapour.body.bod.object, 0.159999996f)
0040fc49        set_bod_object(&esi_2[0x1d], game->subgame.player.golb_shots[0].tertiary_body.bod.object)
0040fc52        esi_2 = &esi_2[0xba]
0040fc58        cond:10_1 = var_128_10 != 1
0040fc59        var_128_10 -= 1
0040fc5d        do while (cond:10_1)
0040fc6b        struct TextureRef* eax_315 = get_or_create_texture_ref(&g_texture_refs, "Objects/VapourLazer/Lazer.tga", 0, 0)
0040fc70        enum TextureRefFlags flags_2 = eax_315->flags
0040fc73        flags_2:1.b |= 4
0040fc77        eax_315->flags = flags_2
0040fc83        struct TextureRef* eax_316 = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Worm.tga", 0, 0)
0040fc92        eax_316->flags |= TEXTURE_REF_REGISTERED | TEXTURE_REF_WRAP_ADDRESSING | 0x3
0040fc9e        struct TextureRef* eax_317 = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Back.tga", 0, 0)
0040fcad        eax_317->flags |= TEXTURE_REF_REGISTERED | TEXTURE_REF_WRAP_ADDRESSING | 0x2
0040fcca        get_or_create_texture_ref(&g_texture_refs, "Objects/World00/TrackWarn.tga", 0, 0)->flags = 0x1000
0040fcd0        struct TextureRef* eax_319 = get_or_create_texture_ref(&g_texture_refs, "Objects/Universe/Ramp.tga", 0, 0)
0040fcd5        enum TextureRefFlags flags_3 = eax_319->flags
0040fcd8        flags_3:1.b |= 0x10
0040fcdc        eax_319->flags = flags_3
0040fce8        struct TextureRef* eax_320 = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Track0.tga", 0, 0)
0040fcf7        eax_320->flags |= TEXTURE_REF_WRAP_ADDRESSING | 0x2
0040fd03        struct TextureRef* eax_321 = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Slide0.tga", 0, 0)
0040fd12        eax_321->flags |= TEXTURE_REF_WRAP_ADDRESSING | 0x2
0040fd1e        struct TextureRef* eax_322 = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Track1.tga", 0, 0)
0040fd2d        eax_322->flags |= TEXTURE_REF_WRAP_ADDRESSING | 0x2
0040fd39        struct TextureRef* eax_323 = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Slide1.tga", 0, 0)
0040fd48        eax_323->flags |= TEXTURE_REF_WRAP_ADDRESSING | 0x2
0040fd54        struct TextureRef* eax_324 = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Track2.tga", 0, 0)
0040fd63        eax_324->flags |= TEXTURE_REF_WRAP_ADDRESSING | 0x2
0040fd6f        struct TextureRef* eax_325 = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Slide2.tga", 0, 0)
0040fd7e        eax_325->flags |= TEXTURE_REF_WRAP_ADDRESSING | 0x2
0040fd8a        struct TextureRef* eax_326 = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Track3.tga", 0, 0)
0040fd99        eax_326->flags |= TEXTURE_REF_WRAP_ADDRESSING | 0x2
0040fda5        struct TextureRef* eax_327 = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Slide3.tga", 0, 0)
0040fdb4        eax_327->flags |= TEXTURE_REF_WRAP_ADDRESSING | 0x2
0040fdd1        game->track.track_textures[0] = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Track0.tga", 0, 0)
0040fde8        game->track.slide_textures[0] = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Slide0.tga", 0, 0)
0040fdff        game->track.track_textures[1] = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Track1.tga", 0, 0)
0040fe16        game->track.slide_textures[1] = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Slide1.tga", 0, 0)
0040fe2d        game->track.track_textures[2] = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Track2.tga", 0, 0)
0040fe44        game->track.slide_textures[2] = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Slide2.tga", 0, 0)
0040fe5b        game->track.track_textures[3] = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Track3.tga", 0, 0)
0040fe68        game->track.slide_textures[3] = get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Slide3.tga", 0, 0)
0040fe78        game->track.current_texture_set = 0
0040fe8f        get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Back.tga", 0, 0)->mip_levels = 2
0040fea6        get_or_create_texture_ref(&g_texture_refs, "Objects/World00/TrackWarn.tga", 0, 0)->mip_levels = 2
0040febd        get_or_create_texture_ref(&g_texture_refs, "Objects/Universe/Ramp.tga", 0, 0)->mip_levels = 2
0040fed4        get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Track0.tga", 0, 0)->mip_levels = 2
0040feeb        get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Slide0.tga", 0, 0)->mip_levels = 2
0040ff02        get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Track1.tga", 0, 0)->mip_levels = 2
0040ff19        get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Slide1.tga", 0, 0)->mip_levels = 2
0040ff30        get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Track2.tga", 0, 0)->mip_levels = 2
0040ff47        get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Slide2.tga", 0, 0)->mip_levels = 2
0040ff5e        get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Track3.tga", 0, 0)->mip_levels = 2
0040ff6e        get_or_create_texture_ref(&g_texture_refs, "Objects/World00/Slide3.tga", 0, 0)->mip_levels = 2
0040ff80        set_bod_object(&game->subgame.barrier.bod, add_object_to_list(&g_object_list))
0040ff91        load_object_definition("Objects/Barrier", game->subgame.barrier.bod.object)
0040ff9f        zero_vector3(&game->subgame.barrier.bod.position)
0040ffbe        store_color4f(&game->subgame.barrier.bod.color, 1f, 1f, 1f, 0.800000012f)
0040ffcf        game->subgame.barrier.bod.object->blend_mode = 7
0040ffd6        initialize_track_render_cache_manager(&game->subgame.segment_cache)
0040ffdb        int32_t edge_selector = 0
0040ffdf        struct Object** eax_349 = &game->root_bod_catalog.fringe_catalog.entries[0][0][0][0].object
00410066        bool cond:14_1
0040ffe5        int32_t orientation = 0
00410058        bool cond:13_1
0040ffe9        int32_t var_12c_5 = 0
0040ffed        struct Object** esi_3 = eax_349
00410048        bool cond:12_1
0040ffef        int32_t i_1 = 0
0041003a        while (i_1 s< 3)
0040ffff        set_bod_object(&esi_3[-9], add_object_to_list(&g_object_list))
00410022        initialize_backdrop_tile_quad((esi_3 - 0x44dd4)->root_bod_catalog.fringe_catalog.entries[0][0][0][0].object, edge_selector, orientation, var_12c_5 - 1, i_1 - 1, "Objects/Universe/Fringe.tga")
00410027        struct Object* object_12 = (esi_3 - 0x44dd4)->root_bod_catalog.fringe_catalog.entries[0][0][0][0].object
0041002c        i_1 += 1
0041002d        esi_3 = &esi_3[0xe]
00410033        object_12->blend_mode = 5
00410041        cond:12_1 = var_12c_5 + 1 s< 3
00410044        var_12c_5 += 1
00410048        do while (cond:12_1)
0041004e        eax_349 = esi_3
00410051        cond:13_1 = orientation + 1 s< 4
00410054        orientation += 1
00410058        do while (cond:13_1)
0041005f        cond:14_1 = edge_selector + 1 s< 8
00410062        edge_selector += 1
00410066        do while (cond:14_1)
00410078        struct TextureRef* eax_355 = get_or_create_texture_ref(&g_texture_refs, "Objects/Universe/Fringe.tga", 0, 0)
0041007d        enum TextureRefFlags flags_4 = eax_355->flags
0041007f        struct InputState* state = &game->game_inputs[0].input
00410082        flags_4:1.b |= 4
00410085        int32_t i_2 = 0
00410087        eax_355->flags = flags_4
00410093        sub_4113b0(&game->active_bod_list, state - 0x38)
0041009a        state->controller_slot = i_2
0041009c        initialize_input(state)
004100a1        i_2 += 1
004100a2        state = &state[2]
004100a8        do while (i_2 s< 2)
004100ad        int32_t var_12c_6 = 0
004100b3        if (game->player_count s> 0)
004101c5        bool cond:15_1
004100c4        void* esi_4 = game + var_12c_6 * 0x1f8
004100d4        set_matrix_identity(esi_4 + 0x15c)
004100df        set_matrix_identity(esi_4 + 0x1fc)
00410133        *(esi_4 + 0x284) = 0x42dc0000
00410149        *(esi_4 + 0x28c) = &game->game_inputs[var_12c_6]
0041015b        struct TransformMatrix transform
0041015b        __builtin_memcpy(esi_4 + 0x15c, initialize_matrix_from_values(&transform, 0.0733430013f, 0f, -0.997310996f, 0f, 0.152129993f, 0.988296986f, 0.0111880004f, 0f, 0.985638976f, -0.152539998f, 0.0724840015f, 0f, -8.62666702f, 3.11352801f, 4.47740698f, 1f), 0x40)
0041016c        initialize_frontend_overlay_color_lerp(esi_4 + 0x2a8, 0x1000000)
00410177        release_mouse_cursor(esi_4 + 0x290)
00410180        *(esi_4 + 0x2a4) = 0
00410188        if (var_12c_6 == 0)
0041018a        game->players[0].frontend_state = 0xc
0041019d        *(esi_4 + 0x30d) = 0
004101a3        *(esi_4 + 0x310) = 0
004101af        rstrcpy_checked_ascii(esi_4 + 0x1a4, &g_runtime_config.last_entered_player_name)
004101bf        cond:15_1 = var_12c_6 + 1 s< game->player_count
004101c1        var_12c_6 += 1
004101c5        do while (cond:15_1)
004101d3        initialize_high_score_tables(&game->subgame.sub_high_score)
004101df        load_high_scores_from_file(&game->subgame.sub_high_score, "ScoreA.dat")
004101eb        load_high_scores_from_file(&game->subgame.sub_high_score, "ScoreB.dat")
004101f7        load_high_scores_from_file(&game->subgame.sub_high_score, "ScoreC.dat")
00410202        game->subgame.selected_level_record_persistent = 0
0041020a        game->subgame.selected_level_record_active = 0
00410210        initialize_tip_manager(&game->tip_manager)
0041021e        sub_4113b0(&game->active_bod_list, &game->tip_manager)
00410235        sub_4113b0(&g_game_base->active_bod_list, &game->star_manager)
0041023e        open_star_field(&game->star_manager, 0x24)
00410249        game->subgame.bottom_score_widget = nullptr
00410252        game->subgame.top_score_widget = nullptr
00410258        sub_4113b0(&game->active_bod_list, &game->backdrop)
00410266        game->backdrop.backdrop_render_enabled = 0
0041026c        sub_411420(&game->active_bod_list, &game->border_manager)
00410277        MemBlock::`default constructor closure'(&game->border_manager.border_stack)
0041027c        game->border_manager.border_stack.owner = &game->border_manager
00410289        game->border_manager.delayed_widget_active = 0
0041028f        set_border_justify_centre(&game->border_manager, 25f)
00410294        int32_t* eax_366 = &game->border_manager.borders[0].flags
0041029a        int32_t i_4 = 0x96
004102a7        int32_t i_3
0041029f        (eax_366 - 0x1370)->border_manager.borders[0].flags = 0
004102a1        eax_366 = &eax_366[0x1c9]
004102a6        i_3 = i_4
004102a6        i_4 -= 1
004102a7        do while (i_3 != 1)
004102ae        build_all_objects(&g_object_list)
004102c6        float g = color.g
004102cd        float b = color.b
004102d0        float a = color.a
004102da        set_object_color(game->subgame.path_pairs[0x33].primary.bod.object, color.r)
004102f2        float g_1 = color.g
004102f9        float b_1 = color.b
004102fc        float a_1 = color.a
00410306        set_object_color(game->subgame.path_pairs[0x33].secondary.bod.object, color.r)
0041031e        float g_2 = color.g
00410325        float b_2 = color.b
00410328        float a_2 = color.a
00410332        set_object_color(game->subgame.path_pairs[0x34].primary.bod.object, color.r)
0041034a        float g_3 = color.g
00410351        float b_3 = color.b
00410354        float a_3 = color.a
0041035e        set_object_color(game->subgame.path_pairs[0x34].secondary.bod.object, color.r)
00410376        float g_4 = color.g
0041037d        float b_4 = color.b
00410380        float a_4 = color.a
0041038a        set_object_color(game->subgame.path_pairs[0x35].primary.bod.object, color.r)
004103a2        float g_5 = color.g
004103a9        float b_5 = color.b
004103ac        float a_5 = color.a
004103b6        set_object_color(game->subgame.path_pairs[0x35].secondary.bod.object, color.r)
004103ce        float g_6 = color.g
004103d5        float b_6 = color.b
004103d8        float a_6 = color.a
004103e2        set_object_color(game->subgame.path_pairs[0x39].primary.bod.object, color.r)
004103fa        float g_7 = color.g
00410401        float b_7 = color.b
00410404        float a_7 = color.a
0041040e        set_object_color(game->subgame.path_pairs[0x39].secondary.bod.object, color.r)
00410426        float g_8 = color.g
0041042d        float b_8 = color.b
00410430        float a_8 = color.a
0041043a        set_object_color(game->subgame.path_pairs[0x36].primary.bod.object, color.r)
00410452        float g_9 = color.g
00410459        float b_9 = color.b
0041045c        float a_9 = color.a
00410466        set_object_color(game->subgame.path_pairs[0x36].secondary.bod.object, color.r)
0041047e        float g_10 = color.g
00410485        float b_10 = color.b
00410488        float a_10 = color.a
00410492        set_object_color(game->subgame.path_pairs[0x37].primary.bod.object, color.r)
004104aa        float g_11 = color.g
004104b1        float b_11 = color.b
004104b4        float a_11 = color.a
004104be        set_object_color(game->subgame.path_pairs[0x37].secondary.bod.object, color.r)
004104d6        float g_12 = color.g
004104dd        float b_12 = color.b
004104e0        float a_12 = color.a
004104ea        set_object_color(game->subgame.path_pairs[0x38].primary.bod.object, color.r)
00410502        float g_13 = color.g
00410509        float b_13 = color.b
0041050c        float a_13 = color.a
00410516        set_object_color(game->subgame.path_pairs[0x38].secondary.bod.object, color.r)
0041052e        float g_14 = color.g
00410535        float b_14 = color.b
00410538        float a_14 = color.a
00410542        set_object_color(game->subgame.path_pairs[0x3a].primary.bod.object, color.r)
0041055a        float g_15 = color.g
00410561        float b_15 = color.b
00410564        float a_15 = color.a
0041056e        set_object_color(game->subgame.path_pairs[0x3a].secondary.bod.object, color.r)
00410586        float g_16 = color.g
0041058d        float b_16 = color.b
00410590        float a_16 = color.a
0041059a        set_object_color(game->subgame.path_pairs[0x3e].primary.bod.object, color.r)
004105b2        float g_17 = color.g
004105b9        float b_17 = color.b
004105bc        float a_17 = color.a
004105c6        set_object_color(game->subgame.path_pairs[0x3e].secondary.bod.object, color.r)
004105de        float g_18 = color.g
004105e5        float b_18 = color.b
004105e8        float a_18 = color.a
004105f2        set_object_color(game->subgame.path_pairs[0x3b].primary.bod.object, color.r)
0041060a        float g_19 = color.g
00410611        float b_19 = color.b
00410614        float a_19 = color.a
0041061e        set_object_color(game->subgame.path_pairs[0x3b].secondary.bod.object, color.r)
00410636        float g_20 = color.g
0041063d        float b_20 = color.b
00410640        float a_20 = color.a
0041064a        set_object_color(game->subgame.path_pairs[0x3d].primary.bod.object, color.r)
00410662        float g_21 = color.g
00410669        float b_21 = color.b
0041066c        float a_21 = color.a
00410676        set_object_color(game->subgame.path_pairs[0x3d].secondary.bod.object, color.r)
0041068e        float g_22 = color.g
00410695        float b_22 = color.b
00410698        float a_22 = color.a
004106a2        set_object_color(game->subgame.path_pairs[0x3c].primary.bod.object, color.r)
004106ba        float g_23 = color.g
004106c1        float b_23 = color.b
004106c4        float a_23 = color.a
004106ce        set_object_color(game->subgame.path_pairs[0x3c].secondary.bod.object, color.r)
004106de        set_input_controller_pointer_authored_xy(0, 320f, 240f)
004106ef        set_input_controller_pointer_authored_xy(1, 320f, 240f)
004106f7        game->subgame.subgame_rebuild_selector = 2
00410704        void* eax_408
00410704        eax_408.b = 1
0041070d        return 1
