/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: attach_render_camera_source @ 0x44e900 */

0044e904        viewport->camera = camera
0044e907        uint32_t flags = viewport->flags
0044e90a        flags.b |= 1
0044e90c        viewport->flags = flags
0044e90f        return flags
