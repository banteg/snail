/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: health_collect_particles @ 0x43a010 */

0043a010        int32_t i
0043a010        i.b = data_4df934
0043a01d        if ((i.b & 0x10) != 0)
0043a026        int32_t i_1 = 0
0043a043        int32_t* eax_1 = allocate_sprite(&data_790f30, *(arg1 + 0x380), 0x80, 0xffffffff, 0xffffffff)
0043a06b        eax_1[1] |= 0x800
0043a06e        eax_1[0x1a] = 0
0043a075        eax_1[0x1b] = 0x3d2aaaab
0043a07c        eax_1[0x1e] = 0xb951b717
0043a083        void var_10
0043a083        int32_t* eax_2 = set_color_rgba(&var_10, 0x3f800000, 0x3f400000, 0x3f400000, 0x3f800000)
0043a091        eax_1[0xb] = *eax_2
0043a099        eax_1[0xc] = eax_2[1]
0043a0a5        eax_1[0xd] = eax_2[2]
0043a0a8        int32_t eax_3 = eax_2[3]
0043a0ab        eax_1[0x18] = 0x3dcccccd
0043a0b2        eax_1[0x19] = 0x3f000000
0043a0b9        eax_1[0xe] = eax_3
0043a0c5        int32_t* edx_5 = *(arg2 + 0x64) + 0x48
0043a0c8        float var_30_1 = fconvert.s(float.t(i_1) * fconvert.t(0.785398185f))
0043a0d2        eax_1[0x12] = *edx_5
0043a0d8        eax_1[0x13] = edx_5[1]
0043a0de        eax_1[0x14] = edx_5[2]
0043a0ed        float var_2c_1 = fconvert.s(fconvert.t(*(arg1 + 0x418)) * fconvert.t(0.400000006f))
0043a0fd        float var_30_2 = fconvert.s(cosine(var_30_1) * fconvert.t(0.0149999997f))
0043a122        float var_24_1 = var_30_2
0043a126        eax_1[0x15] = fconvert.s(sine(var_30_1) * fconvert.t(0.0149999997f))
0043a128        float var_20_1 = var_2c_1
0043a12c        eax_1[0x16] = var_30_2
0043a12f        eax_1[0x17] = var_2c_1
0043a14a        float var_18_1 = fconvert.s(fconvert.t(*(arg1 + 0x414)) * fconvert.t(3f))
0043a15a        float var_14_1 = fconvert.s(fconvert.t(*(arg1 + 0x418)) * fconvert.t(3f))
0043a160        eax_1[0x12] = fconvert.s(fconvert.t(*(arg1 + 0x410)) * fconvert.t(3f) + fconvert.t(eax_1[0x12]))
0043a169        eax_1[0x13] = fconvert.s(fconvert.t(var_18_1) + fconvert.t(eax_1[0x13]))
0043a177        i = i_1 + 1
0043a17b        i_1 = i
0043a17f        eax_1[0x14] = fconvert.s(fconvert.t(var_14_1) + fconvert.t(eax_1[0x14]))
0043a182        do while (i s< 8)
0043a18f        return i
