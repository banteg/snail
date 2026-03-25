/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_garbage_smoke_particle @ 0x43d5a0 */

0043d5a0        int32_t result
0043d5a0        result.b = data_4df934
0043d5ad        if ((result.b & 0x10) != 0)
0043d5ca        int32_t* eax_1 = allocate_sprite(&data_790f30, *(arg4 + 0x380), 0x21, 0xffffffff, 0xffffffff)
0043d5e0        int32_t eax_2 = eax_1[1]
0043d5e3        eax_1[0x1a] = 0
0043d5ea        eax_2:1.b |= 8
0043d5f2        eax_1[1] = eax_2
0043d602        long double x87_r7_2 = fconvert.t(*(*(arg1 + 0x8c) + 0x38)) * fconvert.t(0.0333333351f)
0043d608        eax_1[0x1c] = 0
0043d60f        eax_1[0x1b] = fconvert.s(x87_r7_2)
0043d621        eax_1[0x1d] = fconvert.s(fconvert.t(*(*(arg1 + 0x8c) + 0x38)) * fconvert.t(0.416666687f))
0043d624        struct Color4f color
0043d624        struct Color4f* eax_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043d62e        eax_1[0xb] = eax_4->r
0043d634        eax_1[0xc] = eax_4->g
0043d63a        eax_1[0xd] = eax_4->b
0043d63d        float a = eax_4->a
0043d640        eax_1[0x18] = 0x3e99999a
0043d647        eax_1[0x19] = 0x3fa66666
0043d64e        eax_1[0xe] = a
0043d663        color.r = fconvert.s(fconvert.t(*arg3) * fconvert.t(0.200000003f))
0043d674        color.g = fconvert.s(fconvert.t(arg3[1]) * fconvert.t(0.200000003f))
0043d67b        long double x87_r7_10 = fconvert.t(arg3[2]) * fconvert.t(0.200000003f)
0043d681        float g = color.g
0043d685        eax_1[0x15] = color.r
0043d687        eax_1[0x1e] = 0
0043d68e        eax_1[0x16] = g
0043d695        color.b = fconvert.s(x87_r7_10)
0043d69d        eax_1[0x17] = color.b
0043d6a2        eax_1[0x12] = *arg2
0043d6a7        eax_1[0x13] = arg2[1]
0043d6aa        result = arg2[2]
0043d6ad        eax_1[0x14] = result
0043d6b5        return result
