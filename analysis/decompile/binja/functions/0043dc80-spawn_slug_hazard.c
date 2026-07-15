/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_slug_hazard @ 0x43dc80 */

0043dc83        int32_t eax = 0
0043dc88        int32_t* ecx = &game->slug_hazards.slots[0].state
0043dc91        while ((ecx - 0x356420)->slug_hazards.slots[0].state != 0)
0043dc93        eax += 1
0043dc94        ecx = &ecx[0x3b]
0043dc9d        if (eax s>= 8)
0043dca3        return eax
0043dcbc        void* esi = game + eax * 0xec
0043dcbf        *(esi + 0x356420) = 1
0043dcc9        *(esi + 0x356460) = owner_player
0043dcd5        set_matrix_identity(esi + 0x3563d8)
0043dce9        long double x87_r7_1 = fconvert.t(cell->anchor_position.y) + fconvert.t(1.70000005f)
0043dcef        float x = cell->anchor_position.x
0043dcf2        int16_t z = (cell->anchor_position.z).w
0043dcf9        *(esi + 0x356408) = x.b
0043dcf9        *(esi + 0x356409) = x:1.b
0043dcf9        *(esi + 0x35640a) = x:2.b
0043dcf9        *(esi + 0x35640b) = x:3.b
0043dcfb        float x_1 = x
0043dd0b        *(esi + 0x35640c) = fconvert.s(x87_r7_1)
0043dd16        *(esi + 0x356410) = z.b
0043dd16        *(esi + 0x356411) = z:1.b
0043dd1b        project_position_onto_track_attachment(game, esi + 0x356408, esi + 0x356438)
0043dd23        long double x87_r6 = fconvert.t(0f)
0043dd2f        float var_c = fconvert.s(x87_r6)
0043dd3f        long double x87_r7_3 = fconvert.t(game->subgame_rate) * fconvert.t(-0.200000003f)
0043dd45        *(esi + 0x35642c) = var_c.b
0043dd45        *(esi + 0x35642d) = var_c:1.b
0043dd45        *(esi + 0x35642e) = var_c:2.b
0043dd45        *(esi + 0x35642f) = var_c:3.b
0043dd47        *(esi + 0x356430) = fconvert.s(x87_r6)
0043dd50        int16_t var_4_1 = (fconvert.s(x87_r7_3)).w
0043dd58        *(esi + 0x356434) = var_4_1.b
0043dd58        *(esi + 0x356435) = var_4_1:1.b
0043dd61        struct FrameBodList* edx_5 = &g_game_base->active_bod_list
0043dd71        if (((esi + 0x3563a0)->bod.list_flags:1.b & 2) == 0)
0043dd82        (esi + 0x3563a0)->bod.list_next = &game->player
0043dd88        if (edx_5->first != &game->player)
0043dd99        struct FrameBodBase* edx_6
0043dd99        edx_6.b = game->player.body.bod.bod.list_prev.b
0043dd99        edx_6:1.b = game->player.body.bod.bod.list_prev:1.b
0043dd9c        (esi + 0x3563a0)->bod.list_prev = edx_6
0043dd9f        game->player.body.bod.bod.list_prev.b = (esi + 0x3563a0).b
0043dd9f        game->player.body.bod.bod.list_prev:1.b = (esi + 0x3563a0):1.b
0043dda5        (esi + 0x3563a0)->bod.list_prev->bod.list_next = esi + 0x3563a0
0043dd8a        game->player.body.bod.bod.list_prev.b = (esi + 0x3563a0).b
0043dd8a        game->player.body.bod.bod.list_prev:1.b = (esi + 0x3563a0):1.b
0043dd8d        edx_5->first = esi + 0x3563a0
0043dd90        (esi + 0x3563a0)->bod.list_prev = nullptr
0043dda8        uint32_t list_flags = (esi + 0x3563a0)->bod.list_flags
0043ddab        list_flags:1.b |= 2
0043ddae        (esi + 0x3563a0)->bod.list_flags = list_flags
0043dd78        report_errorf("List ADDbefore")
0043ddc7        struct Sprite* eax_7 = allocate_sprite(&g_sprite_manager, owner_player->player_slot, 0x76, 0xffffffff, 0xffffffff)
0043ddcc        *(esi + 0x35644c) = eax_7
0043ddd2        enum SpriteFlag flags = eax_7->flags
0043ddd5        flags:1.b |= 8
0043ddd8        eax_7->flags = flags
0043dde4        set_color_white(*(esi + 0x35644c) + 0x2c)
0043ddf1        *(*(esi + 0x35644c) + 0x78) = 0
0043ddfa        *(*(esi + 0x35644c) + 0x68) = 0
0043de08        *(*(esi + 0x35644c) + 0x6c) = 0
0043de11        *(*(esi + 0x35644c) + 0x60) = 0x40000000
0043de1a        *(*(esi + 0x35644c) + 0x64) = 0x40000000
0043de26        int32_t* eax_10 = *(esi + 0x35644c) + 0x48
0043de29        *eax_10 = *(esi + 0x356408)
0043de2e        eax_10[1] = *(esi + 0x35640c)
0043de34        eax_10[2] = *(esi + 0x356410)
0043de37        *(esi + 0x356450) = cell
0043de3d        *(esi + 0x356454) = 0
0043de43        *(esi + 0x35646c) = 0
0043de49        *(esi + 0x356470) = 0
0043de60        *(esi + 0x356474) = fconvert.s(fconvert.t(g_game_base->subgame.subgame_rate) * fconvert.t(0.166666672f))
0043de66        *(esi + 0x356468) = 7
0043de70        int32_t eax_12 = *(esi + 0x3563a4)
0043de76        eax_12:1.b &= 0xef
0043de79        *(esi + 0x3563a4) = eax_12
0043de7f        *(esi + 0x356478) = 0
0043de85        *(esi + 0x356479) = 0
0043de8b        *(esi + 0x35647c) = 0
0043de91        *(esi + 0x356480) = 0x3d088889
0043de9b        long double x87_r7_6 = fconvert.t(cell->anchor_position.z)
0043de9e        long double temp1 = fconvert.t(game->next_slug_voice_trigger_z)
0043de9e        x87_r7_6 - temp1
0043dea9        if ((((x87_r7_6 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp1) ? 1 : 0) << 0xa | (x87_r7_6 == temp1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043deab        *(esi + 0x356464) = 1
0043dec1        game->next_slug_voice_trigger_z = fconvert.s(fconvert.t(game->slug_voice_trigger_spacing_z) + fconvert.t(game->next_slug_voice_trigger_z))
0043dec7        *(esi + 0x356484) = 0
0043decd        struct Player* eax_14 = next_math_random_value()
0043def2        *(esi + 0x356488) = fconvert.s(fconvert.t(1f) / ((float.t(eax_14) * fconvert.t(3.05175781e-05f) + fconvert.t(1f)) * fconvert.t(60f)))
0043deff        return eax_14
