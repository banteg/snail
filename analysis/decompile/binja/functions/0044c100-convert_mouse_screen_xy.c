/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: convert_mouse_screen_xy @ 0x44c100 */

0044c10a        POINT point
0044c10a        if (g_fullscreen_active == 0 && is_mouse_captured(&g_game_base->players[0].mouse_cursor) != 0)
0044c12d        if (GetCursorPos(&point) == 0)
0044c14f        *x = 0f
0044c155        *y = 0f
0044c15e        return
0044c13b        *x = fconvert.s(float.t(point.x))
0044c141        *y = fconvert.s(float.t(point.y))
0044c146        return
0044c171        int32_t Y
0044c171        int16_t x87control
0044c171        int16_t x87control_1
0044c171        if (is_mouse_captured(&g_game_base->players[0].mouse_cursor) != 0)
0044c224        if (GetCursorPos(&point) == 0)
0044c270        *x = 0f
0044c276        *y = 0f
0044c244        *x = fconvert.s((float.t(point.x) - fconvert.t(g_authored_view_width) * fconvert.t(0.5f)) * fconvert.t(g_mouse_screen_to_authored_x_scale) + fconvert.t(*x))
0044c264        *y = fconvert.s((float.t(point.y) - fconvert.t(g_authored_view_height) * fconvert.t(0.5f)) * fconvert.t(g_mouse_screen_to_authored_y_scale) + fconvert.t(*y))
0044c288        if (GetActiveWindow() == g_main_window)
0044c296        Y, x87control_1 = ftol(x87control, fconvert.t(g_authored_view_height) * fconvert.t(0.5f))
0044c2ae        SetCursorPos(ftol(x87control_1, fconvert.t(g_authored_view_width) * fconvert.t(0.5f)), Y)
0044c184        if (GetCursorPos(&point) == 0)
0044c1f7        *x = 0f
0044c1fd        *y = 0f
0044c1b8        *x = fconvert.s(resolve_uncaptured_cursor_sensitivity_scale(g_runtime_config.steering_sensitivity[sensitivity_slot]) * (float.t(point.x) - fconvert.t(g_authored_view_width) * fconvert.t(0.5f)) * fconvert.t(g_mouse_screen_to_authored_x_scale) + fconvert.t(*x))
0044c1eb        *y = fconvert.s(resolve_uncaptured_cursor_sensitivity_scale(g_runtime_config.steering_sensitivity[sensitivity_slot]) * (float.t(point.y) - fconvert.t(g_authored_view_height) * fconvert.t(0.5f)) * fconvert.t(g_mouse_screen_to_authored_y_scale) + fconvert.t(*y))
0044c20f        if (GetActiveWindow() == g_main_window)
0044c296        Y, x87control_1 = ftol(x87control, fconvert.t(g_authored_view_height) * fconvert.t(0.5f))
0044c2ae        SetCursorPos(ftol(x87control_1, fconvert.t(g_authored_view_width) * fconvert.t(0.5f)), Y)
0044c2b7        return
