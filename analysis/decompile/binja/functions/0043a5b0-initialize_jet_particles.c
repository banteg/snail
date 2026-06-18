/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_jet_particles @ 0x43a5b0 */

0043a5b7        struct JetParticleSlot (* esi)[0x1e] = &gauge->particle_slots
0043a5ba        int32_t var_14 = 0xf
0043a678        bool cond:1_1
0043a5c9        int32_t i_1 = 2
0043a669        int32_t i
0043a5de        struct Sprite* eax_1 = allocate_sprite(&data_790f30, 1, 0x9e, 0xffffffff, 0xffffffff)
0043a5e3        (esi - 0x20)->particle_slots[0].sprite = eax_1
0043a5e5        uint32_t flags = eax_1->flags
0043a5e8        flags:1.b |= 8
0043a5f0        eax_1->flags = flags
0043a5f3        (esi - 0x20)->particle_slots[0]
0043a602        (esi - 0x20)->particle_slots[0]
0043a60c        (esi - 0x20)->particle_slots[0]
0043a611        (esi - 0x20)->particle_slots[0]
0043a616        (esi - 0x20)->particle_slots[0]
0043a621        __builtin_memset(&(esi - 0x20)->particle_slots[0].sprite->size_start, 0, 0x1c)
0043a626        struct Vec3* eax_5 = &(esi - 0x20)->particle_slots[0].sprite->velocity
0043a629        eax_5->z = 0f
0043a62c        eax_5->y = 0f
0043a62f        eax_5->x = 0
0043a631        (esi - 0x20)->particle_slots[0]
0043a636        struct Color4f color
0043a636        int32_t* eax_7 = set_color_rgba(&color, 1f, 1f, 1f, 0.999000013f)
0043a63f        struct Color4f* ecx_4 = &(esi - 0x20)->particle_slots[0].sprite->color
0043a642        esi = &(*esi)[1]
0043a645        i = i_1
0043a645        i_1 -= 1
0043a646        ecx_4->r = *eax_7
0043a64b        ecx_4->g = eax_7[1]
0043a64e        int32_t edx_5 = eax_7[2]
0043a651        ecx_4->b.b = edx_5.b
0043a651        ecx_4->b:1.b = edx_5:1.b
0043a651        ecx_4->b:2.b = edx_5:2.b
0043a651        ecx_4->b:3.b = edx_5:3.b
0043a657        ecx_4->a = eax_7[3]
0043a65a        (esi - 0x20)->wobble_x = 0f
0043a65d        struct Player* player = (esi - 0x20)->player
0043a660        player->_pad_00[0x28] = 0
0043a660        player->_pad_00[0x29] = 0
0043a660        player->_pad_00[0x2a] = 0
0043a660        player->_pad_00[0x2b] = 0
0043a663        (esi - 0x20)->wobble_y = 0f
0043a666        (esi - 0x20)->wobble_alpha = 0.166666672f
0043a669        do while (i != 1)
0043a673        cond:1_1 = var_14 != 1
0043a674        var_14 -= 1
0043a678        do while (cond:1_1)
0043a685        return
