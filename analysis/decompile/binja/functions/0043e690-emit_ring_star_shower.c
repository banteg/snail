/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: emit_ring_star_shower @ 0x43e690 */

0043e69d        if ((data_4df934 & 0x10) == 0)
0043e69d        return
0043e6ca        struct Sprite* eax_2
0043e6ca        int32_t ecx_1
0043e6ca        eax_2, ecx_1 = allocate_sprite(&g_sprite_manager, owner->player_slot, particle->parent->star_sprite_id, 0xffffffff, 0xffffffff)
0043e6d1        int32_t var_24_1 = ecx_1
0043e6d2        int32_t eax_3 = eax_2->__offset(0x4).d
0043e6d5        eax_2->__offset(0x68).d = 0
0043e6dc        eax_3:1.b |= 8
0043e6df        eax_2->__offset(0x6c).d = 0x3de38e38
0043e6e6        eax_2->__offset(0x4).d = eax_3
0043e6e9        eax_2->__offset(0x60).d = 0x3ecccccd
0043e6f0        eax_2->__offset(0x64).d = 0x3e4ccccd
0043e70b        float var_c_1 = fconvert.s(sine(fconvert.s(fconvert.t(particle->phase) + fconvert.t(1.04719758f))) * fconvert.t(particle->radius))
0043e73b        long double x87_r7_9 = cosine(fconvert.s(fconvert.t(particle->phase) + fconvert.t(1.04719758f))) * fconvert.t(particle->radius) * fconvert.t(0.300000012f)
0043e741        eax_2->__offset(0x54).d = fconvert.s(fconvert.t(var_c_1) * fconvert.t(0.300000012f))
0043e74f        eax_2->__offset(0x58).d = fconvert.s(x87_r7_9)
0043e752        eax_2->__offset(0x5c).d = 0
0043e757        void* __offset(Sprite, 0x48) eax_6 = particle->sprite + 0x48
0043e75f        eax_2->__offset(0x48).d = (eax_6 - 0x48)->__offset(0x48).d
0043e764        eax_2->__offset(0x4c).d = (eax_6 - 0x48)->__offset(0x4c).d
0043e767        int32_t eax_7 = (eax_6 - 0x48)->__offset(0x50).d
0043e76a        eax_2->__offset(0x78).d = 0
0043e771        eax_2->__offset(0x50).d = eax_7
0043e779        return
