/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: render_backdrop @ 0x411040 */

00411046        struct Backdrop* backdrop_9 = backdrop
00411048        float var_38 = 0f
004112db        long double x87_r7_43
004112db        long double temp1_1
00411050        long double x87_r7_1 = fconvert.t(0f)
0041105a        int32_t eax_1
0041105a        int16_t x87control
0041105a        eax_1, x87control = ftol(x87control, fconvert.t(var_38))
004112ba        long double temp0_1
00411063        int32_t eax_2
00411063        eax_2, x87control = ftol(x87control, x87_r7_1)
00411068        backdrop.b = backdrop_9->active_flip
0041106b        int32_t eax_3 = eax_1 + (eax_2 << 3)
00411078        float var_34_1 = fconvert.s(x87_r7_1 + fconvert.t(1f))
00411080        long double x87_r6_6 = fconvert.t(var_38) + fconvert.t(1f)
00411086        int32_t active_primary_texture_id
00411086        float x0
00411086        float y0
00411086        float x1
00411086        float y1
00411086        float x2
00411086        float y2
00411086        float x3
00411086        float y3
00411086        struct tColour* color
00411086        float u0
00411086        float v0
00411086        float u1
00411086        float v1
00411086        if (backdrop.b != 0)
0041119e        int32_t var_48_2 = 0
004111a0        int32_t var_4c_2 = 0
004111a2        struct Backdrop* backdrop_8 = backdrop
004111a6        float var_30_2 = fconvert.s(fconvert.t(var_34_1) * fconvert.t(68.5714264f))
004111b4        void* esi_2 = &backdrop_9->bod_base[eax_3 * 0x18]
004111b7        float var_24_2 = fconvert.s(fconvert.t(var_38) * fconvert.t(91.4285736f))
004111c3        float var_2c_2 = fconvert.s(x87_r6_6 * fconvert.t(91.4285736f))
004111cf        float var_28_2 = fconvert.s(x87_r7_1 * fconvert.t(68.5714264f))
004111dd        v1 = fconvert.s(fconvert.t(var_34_1) * fconvert.t(0.133928567f))
004111e0        struct Backdrop* backdrop_6 = backdrop
004111ed        u1 = fconvert.s(fconvert.t(0.800000012f) - x87_r6_6 * fconvert.t(0.0892857164f))
004111f0        struct Backdrop* backdrop_4 = backdrop
004111f7        v0 = fconvert.s(x87_r7_1 * fconvert.t(0.133928567f))
00411204        struct Backdrop* backdrop_2 = backdrop
0041120f        u0 = fconvert.s(fconvert.t(0.800000012f) - fconvert.t(var_38) * fconvert.t(0.0892857164f))
00411226        struct tColour color_2
00411226        struct tColour* color_4
00411226        int32_t ecx_4
00411226        color_4, ecx_4 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00411235        color = color_4
00411236        int32_t var_64_2 = 0x8000000
0041123b        int32_t var_68_2 = 0
0041123d        int32_t var_6c_2 = 0
0041123f        int32_t var_70_2 = ecx_4
00411243        y3 = fconvert.s(fconvert.t(var_30_2) + fconvert.t(*(esi_2 + 0x12c)))
00411250        int32_t var_74_2 = ecx_4
00411251        x3 = fconvert.s(fconvert.t(var_24_2) + fconvert.t(*(esi_2 + 0x128)))
0041125e        int32_t var_78_2 = ecx_4
0041125f        y2 = fconvert.s(fconvert.t(var_30_2) + fconvert.t(*(esi_2 + 0x144)))
0041126c        int32_t var_7c_2 = ecx_4
0041126d        x2 = fconvert.s(fconvert.t(var_2c_2) + fconvert.t(*(esi_2 + 0x140)))
0041127a        int32_t var_80_2 = ecx_4
0041127b        y1 = fconvert.s(fconvert.t(var_28_2) + fconvert.t(*(esi_2 + 0x84)))
00411288        int32_t var_84_2 = ecx_4
00411289        x1 = fconvert.s(fconvert.t(var_2c_2) + fconvert.t(*(esi_2 + 0x80)))
00411293        int32_t var_88_2 = ecx_4
00411294        y0 = fconvert.s(fconvert.t(var_28_2) + fconvert.t(*(esi_2 + 0x6c)))
0041129e        int32_t var_8c_2 = ecx_4
0041129f        x0 = fconvert.s(fconvert.t(var_24_2) + fconvert.t(*(esi_2 + 0x68)))
004112a2        active_primary_texture_id = backdrop_9->active_primary_texture_id
00411096        int32_t var_48_1 = 0
00411098        int32_t var_4c_1 = 0
0041109a        struct Backdrop* backdrop_7 = backdrop
0041109e        float var_30_1 = fconvert.s(fconvert.t(var_34_1) * fconvert.t(68.5714264f))
004110ac        void* esi_1 = &backdrop_9->bod_base[eax_3 * 0x18]
004110af        float var_24_1 = fconvert.s(fconvert.t(var_38) * fconvert.t(91.4285736f))
004110bb        float var_2c_1 = fconvert.s(x87_r6_6 * fconvert.t(91.4285736f))
004110c7        float var_28_1 = fconvert.s(x87_r7_1 * fconvert.t(68.5714264f))
004110d5        v1 = fconvert.s(fconvert.t(var_34_1) * fconvert.t(0.133928567f))
004110d8        struct Backdrop* backdrop_5 = backdrop
004110df        u1 = fconvert.s(x87_r6_6 * fconvert.t(0.0892857164f))
004110e2        struct Backdrop* backdrop_3 = backdrop
004110e9        v0 = fconvert.s(x87_r7_1 * fconvert.t(0.133928567f))
004110f6        struct Backdrop* backdrop_1 = backdrop
004110fb        u0 = fconvert.s(fconvert.t(var_38) * fconvert.t(0.0892857164f))
00411112        struct tColour color_1
00411112        struct tColour* color_3
00411112        int32_t ecx_1
00411112        color_3, ecx_1 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
00411121        color = color_3
00411122        int32_t var_64_1 = 0x8000000
00411127        int32_t var_68_1 = 0
00411129        int32_t var_6c_1 = 0
0041112b        int32_t var_70_1 = ecx_1
0041112c        y3 = fconvert.s(fconvert.t(var_30_1) + fconvert.t(*(esi_1 + 0x12c)))
00411139        int32_t var_74_1 = ecx_1
0041113a        x3 = fconvert.s(fconvert.t(var_24_1) + fconvert.t(*(esi_1 + 0x128)))
00411147        int32_t var_78_1 = ecx_1
00411148        y2 = fconvert.s(fconvert.t(var_30_1) + fconvert.t(*(esi_1 + 0x144)))
00411155        int32_t var_7c_1 = ecx_1
00411156        x2 = fconvert.s(fconvert.t(var_2c_1) + fconvert.t(*(esi_1 + 0x140)))
00411163        int32_t var_80_1 = ecx_1
00411164        y1 = fconvert.s(fconvert.t(var_28_1) + fconvert.t(*(esi_1 + 0x84)))
00411171        int32_t var_84_1 = ecx_1
00411172        x1 = fconvert.s(fconvert.t(var_2c_1) + fconvert.t(*(esi_1 + 0x80)))
0041117c        int32_t var_88_1 = ecx_1
0041117d        y0 = fconvert.s(fconvert.t(var_28_1) + fconvert.t(*(esi_1 + 0x6c)))
00411187        int32_t var_8c_1 = ecx_1
0041118b        x0 = fconvert.s(fconvert.t(var_24_1) + fconvert.t(*(esi_1 + 0x68)))
0041118e        active_primary_texture_id = backdrop_9->active_primary_texture_id
004112a3        backdrop = queue_textured_quad_corners(active_primary_texture_id, x0, y0, x1, y1, x2, y2, x3, y3, 0, 0, 0x8000000, color, u0, v0, u1, v1, 0, 0f)
004112a8        x87_r7_1 = fconvert.t(var_34_1)
004112ac        temp0_1 = fconvert.t(7f)
004112ac        x87_r7_1 - temp0_1
004112ba        do while ((((x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
004112c6        x87_r7_43 = fconvert.t(var_38) + fconvert.t(1f)
004112cc        var_38 = fconvert.s(x87_r7_43)
004112d0        temp1_1 = fconvert.t(7f)
004112d0        x87_r7_43 - temp1_1
004112db        do while ((((x87_r7_43 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_43, temp1_1) ? 1 : 0) << 0xa | (x87_r7_43 == temp1_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004112e7        return
