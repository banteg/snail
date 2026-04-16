/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_jet_particles @ 0x43a5b0 */

0043a5b7        int32_t** esi = arg1 + 0x20
0043a5ba        int32_t result_1 = 0xf
0043a678        int32_t result
0043a678        bool cond:1_1
0043a5c9        int32_t i_1 = 2
0043a669        int32_t i
0043a5de        int32_t* eax_1 = allocate_sprite(&data_790f30, 1, 0x9e, 0xffffffff, 0xffffffff)
0043a5e3        *esi = eax_1
0043a5e8        int32_t edx_1
0043a5e8        edx_1:1.b = eax_1[1]:1.b | 8
0043a5f0        eax_1[1] = edx_1
0043a5f3        *esi
0043a602        *esi
0043a60c        *esi
0043a611        *esi
0043a616        *esi
0043a621        __builtin_memset(&(*esi)[0x18], 0, 0x1c)
0043a626        int32_t* eax_5 = &(*esi)[0x15]
0043a629        eax_5[2] = 0
0043a62c        eax_5[1] = 0
0043a62f        *eax_5 = 0
0043a631        *esi
0043a636        struct Color4f color
0043a636        struct Color4f* eax_7 = set_color_rgba(&color, 1f, 1f, 1f, 0.999000013f)
0043a63f        float* ecx_4 = &(*esi)[0xb]
0043a642        esi = &esi[4]
0043a645        i = i_1
0043a645        i_1 -= 1
0043a646        *ecx_4 = eax_7->r
0043a64b        ecx_4[1] = eax_7->g
0043a651        ecx_4[2] = eax_7->b
0043a657        ecx_4[3] = eax_7->a
0043a65a        esi[-3] = 0
0043a660        esi[-4][0xa] = 0
0043a663        esi[-2] = 0
0043a666        esi[-1] = 0x3e2aaaab
0043a669        do while (i != 1)
0043a673        result = result_1 - 1
0043a673        cond:1_1 = result_1 != 1
0043a674        result_1 = result
0043a678        do while (cond:1_1)
0043a685        return result
