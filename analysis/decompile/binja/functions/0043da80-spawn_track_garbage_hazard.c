/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_track_garbage_hazard @ 0x43da80 */

0043da83        int32_t eax = 0
0043da88        enum SubGarbageState* ecx = &game->garbage_hazards.slots[0].state
0043da91        while ((ecx - 0x3591c8)->garbage_hazards.slots[0].state != SUB_GARBAGE_STATE_INACTIVE)
0043da93        eax += 1
0043da94        ecx = &ecx[0x31]
0043da9d        if (eax s>= 0x32)
0043daa4        report_warningf("Run Out of Garbage Slots")
0043dab0        return
0043dac4        void* esi = game + eax * 0xc4
0043dad0        char* var_24 = "Gadd"
0043dad5        *(esi + 0x3591c4) = game->garbage_hazards.active_head
0043dae9        game->garbage_hazards.active_head = esi + 0x359144
0043daf4        float* ebx = game + (eax + 0x45f8) * 0xc4
0043daf7        *(esi + 0x359204) = player
0043db1b        *ebx = fconvert.s((random_float_below(0.400000006f) + fconvert.t(1f)) * fconvert.t(0.600000024f))
0043db1d        *(esi + 0x3591c8) = 1
0043db27        set_matrix_identity(esi + 0x35917c)
0043db35        float x = cell->anchor_position.x
0043db38        float z = cell->anchor_position.z
0043db47        float x_1 = x
0043db4b        float var_8 = fconvert.s(fconvert.t(*ebx) + fconvert.t(cell->anchor_position.y))
0043db53        *(esi + 0x3591ac) = x
0043db59        *(esi + 0x3591b0) = var_8
0043db64        *(esi + 0x3591b4) = z
0043db69        int16_t x87control = project_position_onto_track_attachment(game, esi + 0x3591ac, esi + 0x3591e4)
0043db81        struct BodList* eax_5 = &g_game_base->active_bod_list
0043db88        if ((0x200 & (esi + 0x359144)->list_flags) == 0)
0043db9b        (esi + 0x359144)->list_next = &game->player
0043dba3        if (eax_5->first != &game->player)
0043dbb5        (esi + 0x359144)->list_prev = game->player.body.bod.bod.list_prev
0043dbb8        game->player.body.bod.bod.list_prev = esi + 0x359144
0043dbc0        (esi + 0x359144)->list_prev->list_next = esi + 0x359144
0043dba5        game->player.body.bod.bod.list_prev = esi + 0x359144
0043dbaa        eax_5->first = esi + 0x359144
0043dbad        (esi + 0x359144)->list_prev = nullptr
0043dbc3        (esi + 0x359144)->list_flags |= 0x200
0043db8f        report_errorf("List ADDbefore")
0043dbdd        int32_t eax_8 = ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-0.000122070312f))
0043dbfc        struct Sprite* eax_10 = allocate_sprite(&g_sprite_manager, *(*(esi + 0x359204) + 0x380), 0x72 - eax_8, 0xffffffff, 0xffffffff)
0043dc01        *(esi + 0x3591f8) = eax_10
0043dc07        enum SpriteFlag flags = eax_10->flags
0043dc0a        flags:1.b |= 8
0043dc0d        eax_10->flags = flags
0043dc16        *(*(esi + 0x3591f8) + 0x78) = 0
0043dc1f        *(*(esi + 0x3591f8) + 0x68) = 0
0043dc28        *(*(esi + 0x3591f8) + 0x6c) = 0
0043dc37        *(*(esi + 0x3591f8) + 0x60) = *ebx
0043dc42        *(*(esi + 0x3591f8) + 0x64) = *ebx
0043dc4d        float* eax_14 = *(esi + 0x3591f8) + 0x48
0043dc50        *eax_14 = *(esi + 0x3591ac)
0043dc55        eax_14[1] = *(esi + 0x3591b0)
0043dc5f        eax_14[2] = *(esi + 0x3591b4)
0043dc62        *(esi + 0x3591fc) = cell
0043dc68        *(esi + 0x359200) = 0
0043dc76        return
