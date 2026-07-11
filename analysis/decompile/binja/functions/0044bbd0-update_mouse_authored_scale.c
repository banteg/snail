/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_mouse_authored_scale @ 0x44bbd0 */

0044bbd0        int32_t ecx
0044bbd0        int32_t var_4_1 = ecx
0044bbe8        int32_t top = g_mouse_clip_rect.top
0044bbf3        long double x87_r7_1 = fconvert.t(authored_width) / float.t(g_mouse_clip_rect.right - g_mouse_clip_rect.left)
0044bbf7        authored_width = g_mouse_clip_rect.bottom - top
0044bbfb        g_mouse_screen_to_authored_x_scale = fconvert.s(x87_r7_1)
0044bc09        g_mouse_screen_to_authored_y_scale = fconvert.s(fconvert.t(authored_height) / float.t(authored_width))
0044bc10        return top
