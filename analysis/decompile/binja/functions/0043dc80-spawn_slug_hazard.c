/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_slug_hazard @ 0x43dc80 */

0043dc83        int32_t eax = 0
0043dc88        struct SlugStateStrideCursor* slug_state_cursor = &game->slug_hazards.slots[0].state
0043dc91        while (slug_state_cursor->state != SUB_SLUG_STATE_INACTIVE)
0043dc93        eax += 1
0043dc94        slug_state_cursor = &slug_state_cursor[1]
0043dc9d        if (eax s>= 8)
0043dca3        return eax
0043dcbc        struct SlugSlotCursor* slug_slot_cursor = game + eax * 0xec
0043dcbf        slug_slot_cursor->slug.state = SUB_SLUG_STATE_ACTIVE
0043dcc9        slug_slot_cursor->slug.owner_player = owner_player
0043dcd5        set_matrix_identity(&slug_slot_cursor->slug.body.transform)
0043dcef        float x = cell->anchor_position.x
0043dcf2        int16_t z = (cell->anchor_position.z).w
0043dcf9        slug_slot_cursor->slug.body.transform.position.x.b = x.b
0043dcf9        slug_slot_cursor->slug.body.transform.position.x:1.b = x:1.b
0043dcf9        slug_slot_cursor->slug.body.transform.position.x:2.b = x:2.b
0043dcf9        slug_slot_cursor->slug.body.transform.position.x:3.b = x:3.b
0043dcfb        float x_1 = x
0043dd0b        slug_slot_cursor->slug.body.transform.position.y = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(1.70000005f))
0043dd16        slug_slot_cursor->slug.body.transform.position.z.b = z.b
0043dd16        slug_slot_cursor->slug.body.transform.position.z:1.b = z:1.b
0043dd1b        project_position_onto_track_attachment(game, &slug_slot_cursor->slug.body.transform.position, &slug_slot_cursor->slug.attachment_facing_angle)
0043dd23        long double x87_r6 = fconvert.t(0f)
0043dd2f        float var_c = fconvert.s(x87_r6)
0043dd45        slug_slot_cursor->slug.velocity.x.b = var_c.b
0043dd45        slug_slot_cursor->slug.velocity.x:1.b = var_c:1.b
0043dd45        slug_slot_cursor->slug.velocity.x:2.b = var_c:2.b
0043dd45        slug_slot_cursor->slug.velocity.x:3.b = var_c:3.b
0043dd47        slug_slot_cursor->slug.velocity.y = fconvert.s(x87_r6)
0043dd50        int16_t var_4_1 = (fconvert.s(fconvert.t(game->subgame_rate) * fconvert.t(-0.200000003f))).w
0043dd58        slug_slot_cursor->slug.velocity.z.b = var_4_1.b
0043dd58        slug_slot_cursor->slug.velocity.z:1.b = var_4_1:1.b
0043dd61        struct BodList* edx_5 = &g_game_base->active_bod_list
0043dd71        if ((slug_slot_cursor->slug.body.bod.bod.list_flags:1.b & 2) == 0)
0043dd82        slug_slot_cursor->slug.body.bod.bod.list_next = &game->player
0043dd88        if (edx_5->first != &game->player)
0043dd99        struct BodNode* edx_6
0043dd99        edx_6.b = game->player.body.bod.bod.list_prev.b
0043dd99        edx_6:1.b = game->player.body.bod.bod.list_prev:1.b
0043dd9c        slug_slot_cursor->slug.body.bod.bod.list_prev = edx_6
0043dd9f        game->player.body.bod.bod.list_prev.b = (&slug_slot_cursor->slug).b
0043dd9f        game->player.body.bod.bod.list_prev:1.b = (&slug_slot_cursor->slug):1.b
0043dda5        slug_slot_cursor->slug.body.bod.bod.list_prev->list_next = &slug_slot_cursor->slug
0043dd8a        game->player.body.bod.bod.list_prev.b = (&slug_slot_cursor->slug).b
0043dd8a        game->player.body.bod.bod.list_prev:1.b = (&slug_slot_cursor->slug):1.b
0043dd8d        edx_5->first = &slug_slot_cursor->slug
0043dd90        slug_slot_cursor->slug.body.bod.bod.list_prev = nullptr
0043dda8        uint32_t list_flags_1 = slug_slot_cursor->slug.body.bod.bod.list_flags
0043ddab        list_flags_1:1.b |= 2
0043ddae        slug_slot_cursor->slug.body.bod.bod.list_flags = list_flags_1
0043dd78        report_errorf("List ADDbefore")
0043ddc7        struct Sprite* eax_7 = allocate_sprite(&g_sprite_manager, owner_player->player_slot, 0x76, 0xffffffff, 0xffffffff)
0043ddcc        slug_slot_cursor->slug.sprite = eax_7
0043ddd2        enum SpriteFlag flags = eax_7->flags
0043ddd5        flags:1.b |= 8
0043ddd8        eax_7->flags = flags
0043dde4        set_color_white(&slug_slot_cursor->slug.sprite->color)
0043ddf1        slug_slot_cursor->slug.sprite->gravity_step = 0f
0043ddfa        slug_slot_cursor->slug.sprite->progress = 0f
0043de08        slug_slot_cursor->slug.sprite->progress_step = 0f
0043de11        slug_slot_cursor->slug.sprite->size_start = 2f
0043de1a        slug_slot_cursor->slug.sprite->size_end = 2f
0043de26        struct Vec3* eax_10 = &slug_slot_cursor->slug.sprite->position
0043de29        eax_10->x = slug_slot_cursor->slug.body.transform.position.x
0043de2e        eax_10->y = slug_slot_cursor->slug.body.transform.position.y
0043de34        eax_10->z = slug_slot_cursor->slug.body.transform.position.z
0043de37        slug_slot_cursor->slug.source_cell = cell
0043de3d        slug_slot_cursor->slug.passed_player = 0
0043de43        slug_slot_cursor->slug.hit_flash_pending = 0
0043de49        slug_slot_cursor->slug.hit_flash_progress = 0f
0043de60        slug_slot_cursor->slug.hit_flash_progress_step = fconvert.s(fconvert.t(g_game_base->subgame.subgame_rate) * fconvert.t(0.166666672f))
0043de66        slug_slot_cursor->slug.hit_points = 7
0043de70        uint32_t list_flags = slug_slot_cursor->slug.body.bod.bod.list_flags
0043de76        list_flags:1.b &= 0xef
0043de79        slug_slot_cursor->slug.body.bod.bod.list_flags = list_flags
0043de7f        slug_slot_cursor->slug.voice_active = 0
0043de85        slug_slot_cursor->slug.player_encounter_latched = 0
0043de8b        slug_slot_cursor->slug.voice_progress = 0f
0043de91        slug_slot_cursor->slug.voice_progress_step = 0.0333333351f
0043de9b        long double x87_r7_6 = fconvert.t(cell->anchor_position.z)
0043de9e        long double temp1 = fconvert.t(game->next_slug_voice_trigger_z)
0043de9e        x87_r7_6 - temp1
0043dea9        if ((((x87_r7_6 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp1) ? 1 : 0) << 0xa | (x87_r7_6 == temp1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043deab        slug_slot_cursor->slug.engagement_voice_gate = 1
0043dec1        game->next_slug_voice_trigger_z = fconvert.s(fconvert.t(game->slug_voice_trigger_spacing_z) + fconvert.t(game->next_slug_voice_trigger_z))
0043dec7        slug_slot_cursor->slug.blink_progress = 0f
0043decd        int32_t blink_random_value = next_math_random_value()
0043def2        slug_slot_cursor->slug.blink_step = fconvert.s(fconvert.t(1f) / ((float.t(blink_random_value) * fconvert.t(3.05175781e-05f) + fconvert.t(1f)) * fconvert.t(60f)))
0043deff        return blink_random_value
