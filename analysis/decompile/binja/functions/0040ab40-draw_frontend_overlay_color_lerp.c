/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_frontend_overlay_color_lerp @ 0x40ab40 */

0040ab51        arg1[5] = fconvert.s((fconvert.t(arg1[1]) - fconvert.t(arg1[5])) * fconvert.t(0.144999996f) + fconvert.t(arg1[5]))
0040ab62        arg1[6] = fconvert.s((fconvert.t(arg1[2]) - fconvert.t(arg1[6])) * fconvert.t(0.144999996f) + fconvert.t(arg1[6]))
0040ab74        arg1[7] = fconvert.s((fconvert.t(arg1[3]) - fconvert.t(arg1[7])) * fconvert.t(0.144999996f) + fconvert.t(arg1[7]))
0040ab83        long double x87_r7_14 = (fconvert.t(arg1[4]) - fconvert.t(arg1[8])) * fconvert.t(0.144999996f) + fconvert.t(arg1[8])
0040ab86        arg1[8] = fconvert.s(x87_r7_14)
0040ab89        long double temp0 = fconvert.t(0.00999999978f)
0040ab89        x87_r7_14 - temp0
0040ab8f        int16_t result = (x87_r7_14 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp0) ? 1 : 0) << 0xa | (x87_r7_14 == temp0 ? 1 : 0) << 0xe
0040ab94        if ((result:1.b & 0x41) != 0)
0040abb9        return result
0040abb1        return queue_axis_aligned_textured_quad(2, 0, 0, 640f, 480f, *arg1 & 0xff000000, &arg1[5], 5)
