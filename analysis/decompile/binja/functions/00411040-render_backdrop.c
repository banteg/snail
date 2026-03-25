/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: render_backdrop @ 0x411040 */

00411046        void* edi = arg1
00411048        float var_38 = 0f
004112db        int16_t result
00411050        long double x87_r7_1 = fconvert.t(0f)
0041105a        int32_t eax_1
0041105a        int16_t x87control
0041105a        eax_1, x87control = __ftol(x87control, fconvert.t(var_38))
004112ba        long double temp0_1
00411063        int32_t eax_2
00411063        eax_2, x87control = __ftol(x87control, x87_r7_1)
00411068        arg1.b = *(edi + 0x55)
0041106b        int32_t eax_3 = eax_1 + (eax_2 << 3)
00411078        float var_34_1 = fconvert.s(x87_r7_1 + fconvert.t(1f))
00411080        long double x87_r6_6 = fconvert.t(var_38) + fconvert.t(1f)
00411086        int32_t var_90_1
00411086        float var_8c_2
00411086        float var_88_2
00411086        float var_84_2
00411086        float var_80_2
00411086        float var_7c_2
00411086        float var_78_2
00411086        float var_74_2
00411086        float var_70_2
00411086        struct Color4f* var_60_1
00411086        float var_5c_2
00411086        float var_58_2
00411086        float var_54_2
00411086        float var_50_2
00411086        if (arg1.b != 0)
0041119e        int32_t var_48_2 = 0
004111a0        int32_t var_4c_2 = 0
004111a2        void* var_50_3 = arg1
004111a6        float var_30_2 = fconvert.s(fconvert.t(var_34_1) * fconvert.t(68.5714264f))
004111b4        void* esi_2 = edi + eax_3 * 0x18
004111b7        float var_24_2 = fconvert.s(fconvert.t(var_38) * fconvert.t(91.4285736f))
004111c3        float var_2c_2 = fconvert.s(x87_r6_6 * fconvert.t(91.4285736f))
004111cf        float var_28_2 = fconvert.s(x87_r7_1 * fconvert.t(68.5714264f))
004111dd        var_50_2 = fconvert.s(fconvert.t(var_34_1) * fconvert.t(0.133928567f))
004111e0        void* var_54_3 = arg1
004111ed        var_54_2 = fconvert.s(fconvert.t(0.800000012f) - x87_r6_6 * fconvert.t(0.0892857164f))
004111f0        void* var_58_3 = arg1
004111f7        var_58_2 = fconvert.s(x87_r7_1 * fconvert.t(0.133928567f))
00411204        void* var_5c_3 = arg1
0041120f        var_5c_2 = fconvert.s(fconvert.t(0.800000012f) - fconvert.t(var_38) * fconvert.t(0.0892857164f))
00411226        struct Color4f color_1
00411226        struct Color4f* eax_6
00411226        int32_t ecx_4
00411226        eax_6, ecx_4 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
00411235        var_60_1 = eax_6
00411236        int32_t var_64_2 = 0x8000000
0041123b        int32_t var_68_2 = 0
0041123d        int32_t var_6c_2 = 0
0041123f        int32_t var_70_3 = ecx_4
00411243        var_70_2 = fconvert.s(fconvert.t(var_30_2) + fconvert.t(*(esi_2 + 0x12c)))
00411250        int32_t var_74_3 = ecx_4
00411251        var_74_2 = fconvert.s(fconvert.t(var_24_2) + fconvert.t(*(esi_2 + 0x128)))
0041125e        int32_t var_78_3 = ecx_4
0041125f        var_78_2 = fconvert.s(fconvert.t(var_30_2) + fconvert.t(*(esi_2 + 0x144)))
0041126c        int32_t var_7c_3 = ecx_4
0041126d        var_7c_2 = fconvert.s(fconvert.t(var_2c_2) + fconvert.t(*(esi_2 + 0x140)))
0041127a        int32_t var_80_3 = ecx_4
0041127b        var_80_2 = fconvert.s(fconvert.t(var_28_2) + fconvert.t(*(esi_2 + 0x84)))
00411288        int32_t var_84_3 = ecx_4
00411289        var_84_2 = fconvert.s(fconvert.t(var_2c_2) + fconvert.t(*(esi_2 + 0x80)))
00411293        int32_t var_88_3 = ecx_4
00411294        var_88_2 = fconvert.s(fconvert.t(var_28_2) + fconvert.t(*(esi_2 + 0x6c)))
0041129e        int32_t var_8c_3 = ecx_4
0041129f        var_8c_2 = fconvert.s(fconvert.t(var_24_2) + fconvert.t(*(esi_2 + 0x68)))
004112a2        var_90_1 = *(edi + 0x3c)
00411096        int32_t var_48_1 = 0
00411098        int32_t var_4c_1 = 0
0041109a        void* var_50_1 = arg1
0041109e        float var_30_1 = fconvert.s(fconvert.t(var_34_1) * fconvert.t(68.5714264f))
004110ac        void* esi_1 = edi + eax_3 * 0x18
004110af        float var_24_1 = fconvert.s(fconvert.t(var_38) * fconvert.t(91.4285736f))
004110bb        float var_2c_1 = fconvert.s(x87_r6_6 * fconvert.t(91.4285736f))
004110c7        float var_28_1 = fconvert.s(x87_r7_1 * fconvert.t(68.5714264f))
004110d5        var_50_2 = fconvert.s(fconvert.t(var_34_1) * fconvert.t(0.133928567f))
004110d8        void* var_54_1 = arg1
004110df        var_54_2 = fconvert.s(x87_r6_6 * fconvert.t(0.0892857164f))
004110e2        void* var_58_1 = arg1
004110e9        var_58_2 = fconvert.s(x87_r7_1 * fconvert.t(0.133928567f))
004110f6        void* var_5c_1 = arg1
004110fb        var_5c_2 = fconvert.s(fconvert.t(var_38) * fconvert.t(0.0892857164f))
00411112        struct Color4f color
00411112        struct Color4f* eax_5
00411112        int32_t ecx_1
00411112        eax_5, ecx_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00411121        var_60_1 = eax_5
00411122        int32_t var_64_1 = 0x8000000
00411127        int32_t var_68_1 = 0
00411129        int32_t var_6c_1 = 0
0041112b        int32_t var_70_1 = ecx_1
0041112c        var_70_2 = fconvert.s(fconvert.t(var_30_1) + fconvert.t(*(esi_1 + 0x12c)))
00411139        int32_t var_74_1 = ecx_1
0041113a        var_74_2 = fconvert.s(fconvert.t(var_24_1) + fconvert.t(*(esi_1 + 0x128)))
00411147        int32_t var_78_1 = ecx_1
00411148        var_78_2 = fconvert.s(fconvert.t(var_30_1) + fconvert.t(*(esi_1 + 0x144)))
00411155        int32_t var_7c_1 = ecx_1
00411156        var_7c_2 = fconvert.s(fconvert.t(var_2c_1) + fconvert.t(*(esi_1 + 0x140)))
00411163        int32_t var_80_1 = ecx_1
00411164        var_80_2 = fconvert.s(fconvert.t(var_28_1) + fconvert.t(*(esi_1 + 0x84)))
00411171        int32_t var_84_1 = ecx_1
00411172        var_84_2 = fconvert.s(fconvert.t(var_2c_1) + fconvert.t(*(esi_1 + 0x80)))
0041117c        int32_t var_88_1 = ecx_1
0041117d        var_88_2 = fconvert.s(fconvert.t(var_28_1) + fconvert.t(*(esi_1 + 0x6c)))
00411187        int32_t var_8c_1 = ecx_1
0041118b        var_8c_2 = fconvert.s(fconvert.t(var_24_1) + fconvert.t(*(esi_1 + 0x68)))
0041118e        var_90_1 = *(edi + 0x3c)
004112a3        queue_textured_quad_corners(var_90_1, var_8c_2, var_88_2, var_84_2, var_80_2, var_7c_2, var_78_2, var_74_2, var_70_2, 0, nullptr, 0x8000000, var_60_1, var_5c_2, var_58_2, var_54_2, var_50_2)
004112a8        x87_r7_1 = fconvert.t(var_34_1)
004112ac        temp0_1 = fconvert.t(7f)
004112ac        x87_r7_1 - temp0_1
004112ba        do while ((((x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
004112c6        long double x87_r7_43 = fconvert.t(var_38) + fconvert.t(1f)
004112cc        var_38 = fconvert.s(x87_r7_43)
004112d0        long double temp1_1 = fconvert.t(7f)
004112d0        x87_r7_43 - temp1_1
004112d6        result = (x87_r7_43 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_43, temp1_1) ? 1 : 0) << 0xa | (x87_r7_43 == temp1_1 ? 1 : 0) << 0xe
004112db        do while ((result:1.b & 1) != 0)
004112e7        return result
