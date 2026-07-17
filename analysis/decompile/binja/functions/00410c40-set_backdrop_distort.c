/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_backdrop_distort @ 0x410c40 */

00410c40        struct Backdrop* backdrop_1 = backdrop
00410c49        int32_t i = 0
00410d37        while (i s< 0x40)
00410c4b        int32_t j = 0
00410d2b        while (j s< 8)
00410c69        if (j == 0 || i == 0 || j == 7 || i == 0x38)
00410d16        void* eax_10 = &backdrop->bod_base[(i + j) * 0x18]
00410d1a        *(eax_10 + 0x58) = 0
00410d1d        *(eax_10 + 0x5c) = 0
00410d20        *(backdrop + (i + j + 4) * 0x18) = 0
00410d24        *(eax_10 + 0x64) = 0
00410c75        void* ebx_1 = &backdrop->bod_base[(i + j) * 0x18]
00410c8c        *(ebx_1 + 0x58) = fconvert.s(float.t(next_math_random_value()) * fconvert.t(0.000191747604f))
00410cba        *(ebx_1 + 0x5c) = fconvert.s(fconvert.t(1f) / ((float.t(next_math_random_value()) * fconvert.t(6.10351562e-05f) + fconvert.t(3f)) * fconvert.t(60f)) * fconvert.t(6.28318548f))
00410ce1        *(backdrop + (i + j + 4) * 0x18) = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(distort) * fconvert.t(6.10351562e-05f))
00410d04        *(ebx_1 + 0x64) = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(distort) * fconvert.t(6.10351562e-05f))
00410d27        j += 1
00410d31        i += 8
00410d42        return
