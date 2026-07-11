/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: release_mouse_input @ 0x44c2c0 */

0044c2c0        void* mouse_device_2 = g_mouse_device
0044c2c7        if (mouse_device_2 != 0)
0044c2cc        (*(*mouse_device_2 + 0x20))(mouse_device_2)
0044c2cf        void* mouse_device_1 = g_mouse_device
0044c2d6        if (mouse_device_1 != 0)
0044c2db        (*(*mouse_device_1 + 8))(mouse_device_1)
0044c2de        g_mouse_device = nullptr
0044c2e8        void* mouse_input_1 = g_mouse_input
0044c2ef        if (mouse_input_1 != 0)
0044c2f4        mouse_input_1 = (*(*mouse_input_1 + 8))(mouse_input_1)
0044c2f7        g_mouse_input = nullptr
0044c301        return mouse_input_1
