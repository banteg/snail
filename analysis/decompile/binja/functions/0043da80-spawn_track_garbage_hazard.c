/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_track_garbage_hazard @ 0x43da80 */

0043da83        int32_t eax = 0
0043da88        uint32_t* ecx = &game->garbage_hazards[0].state
0043da91        while ((ecx - 0x3591c8)->garbage_hazards[0].state != 0)
0043da93        eax += 1
0043da94        ecx = &ecx[0x31]
0043da9d        if (eax s>= 0x32)
0043daa4        report_warningf("Run Out of Garbage Slots")
0043dab0        return 0
0043dac4        void* esi = &game->_pad_00[eax * 0xc4]
0043dad0        char* var_24 = "Gadd"
0043dad5        *(esi + 0x3591c4) = game->active_garbage_hazards
0043dae9        game->active_garbage_hazards = esi + 0x359144
0043daf4        float* ebx = &game->_pad_00[(eax + 0x45f8) * 0xc4]
0043daf7        *(esi + 0x359204) = player
0043db1b        *ebx = fconvert.s((random_float_below(0.400000006f) + fconvert.t(1f)) * fconvert.t(0.600000024f))
0043db1d        *(esi + 0x3591c8) = 1
0043db27        set_matrix_identity(esi + 0x35917c)
0043db35        float world_x = cell->world_x
0043db38        float world_z = cell->world_z
0043db47        float world_x_1 = world_x
0043db4b        float var_8 = fconvert.s(fconvert.t(*ebx) + fconvert.t(cell->floor_height))
0043db53        *(esi + 0x3591ac) = world_x
0043db59        *(esi + 0x3591b0) = var_8
0043db64        *(esi + 0x3591b4) = world_z
0043db69        int16_t x87control = project_position_onto_track_attachment(game, esi + 0x3591ac, esi + 0x3591e4)
0043db81        void* eax_5 = data_4df904 + 0x5a8
0043db88        if ((0x200 & (esi + 0x359144)->_pad_00[4].d) == 0)
0043db9b        (esi + 0x359144)->_pad_00[0xc] = (&game->__offset(0x3bb764).d).b
0043db9b        (esi + 0x359144)->_pad_00[0xd] = (&game->__offset(0x3bb764).d):1.b
0043db9b        (esi + 0x359144)->_pad_00[0xe] = (&game->__offset(0x3bb764).d):2.b
0043db9b        (esi + 0x359144)->_pad_00[0xf] = (&game->__offset(0x3bb764).d):3.b
0043dba3        if (*(eax_5 + 4) != &game->__offset(0x3bb764).d)
0043dbb2        int32_t edx_8 = game->__offset(0x3bb76c).d
0043dbb5        (esi + 0x359144)->_pad_00[8] = edx_8.b
0043dbb5        (esi + 0x359144)->_pad_00[9] = edx_8:1.b
0043dbb5        (esi + 0x359144)->_pad_00[0xa] = edx_8:2.b
0043dbb5        (esi + 0x359144)->_pad_00[0xb] = edx_8:3.b
0043dbb8        game->__offset(0x3bb76c).d = esi + 0x359144
0043dbc0        *((esi + 0x359144)->_pad_00[8].d + 0xc) = esi + 0x359144
0043dba5        game->__offset(0x3bb76c).d = esi + 0x359144
0043dbaa        *(eax_5 + 4) = esi + 0x359144
0043dbad        (esi + 0x359144)->_pad_00[8] = 0
0043dbad        (esi + 0x359144)->_pad_00[9] = 0
0043dbad        (esi + 0x359144)->_pad_00[0xa] = 0
0043dbad        (esi + 0x359144)->_pad_00[0xb] = 0
0043dbc3        (esi + 0x359144)->_pad_00[4].d |= 0x200
0043db8f        report_errorf("List ADDbefore")
0043dbdd        int32_t eax_8 = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-0.000122070312f))
0043dbfc        int32_t* eax_10 = allocate_sprite(&data_790f30, *(*(esi + 0x359204) + 0x380), 0x72 - eax_8, 0xffffffff, 0xffffffff)
0043dc01        *(esi + 0x3591f8) = eax_10
0043dc0a        int32_t edx_10
0043dc0a        edx_10:1.b = eax_10[1]:1.b | 8
0043dc0d        eax_10[1] = edx_10
0043dc16        *(*(esi + 0x3591f8) + 0x78) = 0
0043dc1f        *(*(esi + 0x3591f8) + 0x68) = 0
0043dc28        *(*(esi + 0x3591f8) + 0x6c) = 0
0043dc37        *(*(esi + 0x3591f8) + 0x60) = *ebx
0043dc42        *(*(esi + 0x3591f8) + 0x64) = *ebx
0043dc4d        float* result = *(esi + 0x3591f8) + 0x48
0043dc50        *result = *(esi + 0x3591ac)
0043dc55        result[1] = *(esi + 0x3591b0)
0043dc5f        result[2] = *(esi + 0x3591b4)
0043dc62        *(esi + 0x3591fc) = cell
0043dc68        *(esi + 0x359200) = 0
0043dc76        return result
