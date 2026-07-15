/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_direct3d_renderer_defaults @ 0x411630 */

0041163b        int32_t eax
0041163b        int16_t x87control
0041163b        int16_t x87control_1
0041163b        eax, x87control_1 = ftol(x87control, fconvert.t(data_4b7760))
00411640        long double x87_r7 = fconvert.t(data_4df85c)
0041164a        data_4b778c = eax
00411650        data_4b7784 = 0
00411656        data_4b7780 = 0
0041165c        int32_t eax_1 = ftol(x87control_1, x87_r7)
00411661        data_4b7788 = eax_1
00411666        data_4b7778 = eax_1
0041166b        enum WINDOW_STYLE dwStyle = data_4a16d8
00411678        data_4b777c = eax
0041167e        data_4b7774 = 0
00411684        data_4b7770 = 0
0041168a        AdjustWindowRectEx(&data_4b7780, dwStyle, 0, WS_EX_LEFT)
00411690        renderer->d3d = nullptr
00411696        renderer->device = nullptr
0041169c        renderer->requested_width = 0x280
004116a6        renderer->requested_height = 0x1e0
004116b0        renderer->unknown_bcb4 = 0x17
004116ba        renderer->depth_stencil_format = 0x50
004116c4        renderer->create_device_flags = 0x20
004116ce        renderer->multisample_type = 0
004116d4        renderer->unknown_bcb0 = 0
004116da        renderer->device_initialized = 0
004116e3        return
