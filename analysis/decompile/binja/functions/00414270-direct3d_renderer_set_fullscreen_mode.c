/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: direct3d_renderer_set_fullscreen_mode @ 0x414270 */

0041427b        if (renderer->device_initialized == 0)
0041427b        return
00414282        char ebx_1 = enabled.b
00414286        int32_t eax_1 = 0
0041428a        eax_1.b = ebx_1 == 0
0041428f        renderer->present.windowed = eax_1
00414295        if (ebx_1 == 0)
004142d8        renderer->present.fullscreen_refresh_rate_hz = 0
004142de        renderer->present.fullscreen_presentation_interval = 0
004142e4        renderer->present.back_buffer_format = renderer->display_format
004142a3        GetWindowRect(g_main_window, &data_503268)
004142a9        data_503278 = 1
004142b0        renderer->present.fullscreen_refresh_rate_hz = 0
004142ba        renderer->present.fullscreen_presentation_interval = 1
004142c4        renderer->present.back_buffer_format = 0x16
004142f4        struct Direct3DDevice8* device = renderer->device
00414307        device->vtbl->Reset(device, &renderer->present)
0041430c        restore_texture_ref_stage_states(renderer)
00414313        reset_direct3d_render_state(renderer)
00414324        if (ebx_1 != 0 || data_503278 != 1)
00414359        ShowCursor(0)
0041432c        int32_t Y = data_50326c
0041433c        int32_t X = data_503268
0041434f        SetWindowPos(g_main_window, nullptr, X, Y, data_503270 - X, data_503274 - Y, SWP_SHOWWINDOW)
00414368        ShowWindow(g_main_window, SW_SHOW)
00414375        SetForegroundWindow(g_main_window)
00414381        SetFocus(g_main_window)
00414393        int32_t Y_1
00414393        int16_t x87control
00414393        int16_t x87control_1
00414393        Y_1, x87control_1 = ftol(x87control, fconvert.t(data_4b7760) * fconvert.t(0.5f))
004143ab        SetCursorPos(ftol(x87control_1, fconvert.t(data_4df85c) * fconvert.t(0.5f)), Y_1)
004143b2        return
