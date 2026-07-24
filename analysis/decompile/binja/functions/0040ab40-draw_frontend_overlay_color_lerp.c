/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_frontend_overlay_color_lerp @ 0x40ab40 */

0040ab51        overlay->current.r = fconvert.s((fconvert.t(overlay->target.r) - fconvert.t(overlay->current.r)) * fconvert.t(0.144999996f) + fconvert.t(overlay->current.r))
0040ab62        overlay->current.g = fconvert.s((fconvert.t(overlay->target.g) - fconvert.t(overlay->current.g)) * fconvert.t(0.144999996f) + fconvert.t(overlay->current.g))
0040ab74        overlay->current.b = fconvert.s((fconvert.t(overlay->target.b) - fconvert.t(overlay->current.b)) * fconvert.t(0.144999996f) + fconvert.t(overlay->current.b))
0040ab83        long double x87_r7_14 = (fconvert.t(overlay->target.a) - fconvert.t(overlay->current.a)) * fconvert.t(0.144999996f) + fconvert.t(overlay->current.a)
0040ab86        overlay->current.a = fconvert.s(x87_r7_14)
0040ab89        long double temp0 = fconvert.t(0.00999999978f)
0040ab89        x87_r7_14 - temp0
0040ab94        if ((((x87_r7_14 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp0) ? 1 : 0) << 0xa | (x87_r7_14 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0040abb1        queue_axis_aligned_textured_quad(2, 0f, 0f, 640f, 480f, overlay->state & 0xff000000, &overlay->current, 5)
0040abb9        return
