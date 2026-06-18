/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_nuke @ 0x447110 */

00447118        if (nuke->state == 0)
00447123        Sprite** sprite_slots = nuke->sprite_slots
0044712f        int32_t i_1 = 0x19
00447134        nuke->orbit_center_z = fconvert.s(fconvert.t(nuke->owner_player->position.z) - fconvert.t(5f))
0044713d        long double x87_r7_3 = fconvert.t(*(data_4df904 + 0x74650))
00447145        nuke->orbit_phase = 0
00447148        nuke->orbit_phase_step = 0x3dd67750
0044714f        nuke->state = 1
00447155        nuke->orbit_center_z_step = fconvert.s(x87_r7_3 + x87_r7_3)
004471c3        int32_t i
00447170        Sprite* sprite = allocate_sprite(&g_sprite_manager, nuke->owner_player->player_slot, 0x83, 0xffffffff, 0xffffffff)
00447175        *sprite_slots = sprite
0044717a        int32_t edx_2
0044717a        edx_2:1.b = sprite->flags:1.b | 8
0044717d        sprite_slots = &sprite_slots[1]
00447180        sprite->flags = edx_2
0044718b        sprite_slots[-1]->progress = 0
00447191        sprite_slots[-1]->progress_step = 0
00447197        sprite_slots[-1]->size_start = 0x40400000
0044719d        sprite_slots[-1]->size_end = 0x40400000
004471a3        int32_t* velocity = &sprite_slots[-1]->velocity
004471a6        velocity[2] = 0
004471a9        velocity[1] = 0
004471ac        *velocity = 0
004471b1        int32_t* position = &sprite_slots[-1]->position
004471b4        i = i_1
004471b4        i_1 -= 1
004471b5        position[2] = 0
004471b8        position[1] = 0
004471bb        *position = 0
004471c0        sprite_slots[-1]->gravity_step = 0
004471c3        do while (i != 1)
004471d0        return update_nuke(nuke)
