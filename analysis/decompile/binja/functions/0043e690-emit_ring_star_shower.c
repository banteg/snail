/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: emit_ring_star_shower @ 0x43e690 */

0043e69d        if ((data_4df934 & 0x10) == 0)
0043e69d        return
0043e6ca        struct Sprite* eax_2
0043e6ca        int32_t ecx_1
0043e6ca        eax_2, ecx_1 = allocate_sprite(&data_790f30, owner->player_slot, particle->parent->star_sprite_id, 0xffffffff, 0xffffffff)
0043e6d1        int32_t var_24_1 = ecx_1
0043e6d2        uint32_t flags = eax_2->flags
0043e6d5        eax_2->progress = 0f
0043e6dc        flags:1.b |= 8
0043e6df        eax_2->progress_step = 0.111111104f
0043e6e6        eax_2->flags = flags
0043e6e9        eax_2->size_start = 0.400000006f
0043e6f0        eax_2->size_end = 0.200000003f
0043e70b        float var_c_1 = fconvert.s(sine(fconvert.s(fconvert.t(particle->phase) + fconvert.t(1.04719758f))) * fconvert.t(particle->radius))
0043e73b        long double x87_r7_9 = cosine(fconvert.s(fconvert.t(particle->phase) + fconvert.t(1.04719758f))) * fconvert.t(particle->radius) * fconvert.t(0.300000012f)
0043e741        eax_2->velocity.x = fconvert.s(fconvert.t(var_c_1) * fconvert.t(0.300000012f))
0043e74f        eax_2->velocity.y = fconvert.s(x87_r7_9)
0043e752        eax_2->velocity.z = 0f
0043e757        struct Vec3* eax_5 = &particle->sprite->position
0043e75f        eax_2->position.x = eax_5->x
0043e764        eax_2->position.y = eax_5->y
0043e767        float z = eax_5->z
0043e76a        eax_2->gravity_step = 0f
0043e771        eax_2->position.z = z
0043e779        return
