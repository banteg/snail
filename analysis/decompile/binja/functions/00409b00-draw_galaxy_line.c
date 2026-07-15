/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_galaxy_line @ 0x409b00 */

00409b0f        struct Vec3 vector
00409b0f        vector.z = 0
00409b17        vector.x = fconvert.s(fconvert.t(x1) - fconvert.t(x0))
00409b23        vector.y = fconvert.s(fconvert.t(y1) - fconvert.t(y0))
00409b27        int32_t ecx_1
00409b27        int80_t st0
00409b27        st0, ecx_1 = normalize_vector(&vector)
00409b43        long double x87_r7_8 = fconvert.t(vector.y) * fconvert.t(width) * fconvert.t(-0.5f)
00409b5b        long double x87_r6_2 = fconvert.t(vector.x) * fconvert.t(width) * fconvert.t(0.5f)
00409b6a        int32_t var_38 = ecx_1
00409b7a        int32_t var_3c = ecx_1
00409b7e        int32_t var_40 = ecx_1
00409b8e        int32_t var_44 = ecx_1
00409b98        int32_t var_48 = ecx_1
00409ba2        int32_t var_4c = ecx_1
00409bac        int32_t var_50 = ecx_1
00409bb0        int32_t var_54 = ecx_1
00409bc3        int32_t result = queue_textured_quad_corners(texture_id, fconvert.s(fconvert.t(x0) - x87_r7_8), fconvert.s(fconvert.t(y0) - x87_r6_2), fconvert.s(fconvert.t(x1) - x87_r7_8), fconvert.s(fconvert.t(y1) - x87_r6_2), fconvert.s(x87_r7_8 + fconvert.t(x1)), fconvert.s(x87_r6_2 + fconvert.t(y1)), fconvert.s(x87_r7_8 + fconvert.t(x0)), fconvert.s(x87_r6_2 + fconvert.t(y0)), 0, 0, 0x1000000, color, 0f, 0f, 1f, 1f, 0xf, 0f)
00409bcb        return result
