/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_nuke @ 0x447110 */

00447118        if (nuke->state == NUKE_STATE_INACTIVE)
00447123        struct Sprite** sprite_slots = &nuke->sprite_slots
0044712f        int32_t i_1 = 0x19
00447134        nuke->orbit_center_z = fconvert.s(fconvert.t(nuke->owner_player->body.transform.position.z) - fconvert.t(5f))
0044713d        long double x87_r7_3 = fconvert.t(g_game_base->subgame.subgame_rate)
00447145        nuke->orbit_phase = 0f
00447148        nuke->orbit_phase_step = 0.104719758f
0044714f        nuke->state = 1
00447155        nuke->orbit_center_z_step = fconvert.s(x87_r7_3 + x87_r7_3)
004471c3        int32_t i
00447170        struct Sprite* eax_3 = allocate_sprite(&g_sprite_manager, nuke->owner_player->player_slot, 0x83, 0xffffffff, 0xffffffff)
00447175        *sprite_slots = eax_3
00447177        enum SpriteFlag flags = eax_3->flags
0044717a        flags:1.b |= 8
0044717d        sprite_slots = &sprite_slots[1]
00447180        eax_3->flags = flags
0044718b        sprite_slots[-1]->progress = 0
00447191        sprite_slots[-1]->progress_step = 0
00447197        sprite_slots[-1]->size_start = 0x40400000
0044719d        sprite_slots[-1]->size_end = 0x40400000
004471a3        int32_t* eax_5 = &sprite_slots[-1]->velocity.x
004471a6        eax_5[2] = 0
004471a9        eax_5[1] = 0
004471ac        *eax_5 = 0
004471b1        int32_t* eax_7 = &sprite_slots[-1]->position.x
004471b4        i = i_1
004471b4        i_1 -= 1
004471b5        eax_7[2] = 0
004471b8        eax_7[1] = 0
004471bb        *eax_7 = 0
004471c0        sprite_slots[-1]->gravity_step = 0
004471c3        do while (i != 1)
004471c9        update_nuke(nuke)
004471d0        return
