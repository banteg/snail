/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninitialize_input_devices @ 0x411d80 */

00411d80        release_global_direct3d_renderer_resources()
00411d85        release_input_controllers()
00411d8a        release_keyboard_input()
00411d8f        return release_mouse_input() __tailcall
