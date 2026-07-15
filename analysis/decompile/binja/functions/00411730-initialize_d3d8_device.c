/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_d3d8_device @ 0x411730 */

0041173c        struct Direct3D8* eax = Direct3DCreate8(0xdc)
00411743        renderer->d3d = eax
0041174b        if (eax == 0)
0041174d        abort_startup_with_3d_error()
00411752        renderer->device_initialized = 0
00411758        struct Direct3D8* d3d = renderer->d3d
0041176c        struct D3DDisplayMode mode
0041176c        if (d3d->vtbl->GetAdapterDisplayMode(d3d, 0, &mode) s< 0)
0041176e        abort_startup_with_3d_error()
00411773        renderer->device_initialized = 0
0041177e        return
00411781        uint32_t format = mode.format
00411796        renderer->display_format = format
0041179c        __builtin_memset(&renderer->present, 0, 0x34)
004117a9        renderer->present.windowed = 1
004117af        renderer->present.swap_effect = 4
004117b9        renderer->present.enable_auto_depth_stencil = 1
004117bf        renderer->present.auto_depth_stencil_format = renderer->depth_stencil_format
004117cb        renderer->present.back_buffer_format = format
004117d1        renderer->present.device_window = g_main_window
004117e3        renderer->present.back_buffer_width = renderer->requested_width
004117ec        renderer->present.multisample_type = renderer->multisample_type
004117f2        renderer->present.back_buffer_height = renderer->requested_height
004117fe        renderer->present.fullscreen_refresh_rate_hz = 0
00411804        if (use_present_interval_one == 0)
0041180e        renderer->present.fullscreen_presentation_interval = 0
00411806        renderer->present.fullscreen_presentation_interval = 1
00411814        struct Direct3D8* d3d_1 = renderer->d3d
00411820        renderer->create_device_flags = 0x40
00411840        if (d3d_1->vtbl->CreateDevice(d3d_1, 0, 1, g_main_window, 0x40, &renderer->present, &renderer->device) s>= 0)
0041187e        char* var_24_3 = "Using Hardware Vertex Processing\n"
00411842        struct Direct3D8* d3d_2 = renderer->d3d
00411848        renderer->create_device_flags = 0x20
00411868        if (d3d_2->vtbl->CreateDevice(d3d_2, 0, 1, g_main_window, 0x20, &renderer->present, &renderer->device) s>= 0)
00411877        var_24_3 = "Using Software Vertex Processing\n"
0041186a        abort_startup_with_3d_error()
0041186f        renderer->device_initialized = 0
0041188d        reset_direct3d_render_state(renderer)
00411894        query_direct3d_device_caps(renderer)
0041189a        renderer->device_initialized = 1
004118a7        return
