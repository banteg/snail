/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_warning @ 0x446e80 */

00446eb2        arg1[3] = allocate_border(data_4df904 + 0xb4c)
00446eb5        struct Color4f color
00446eb5        struct Color4f* eax_1 = set_color_rgba(&color, 1f, 1f, 1f, 0.999000013f)
00446ecf        initialize_frontend_sprite_button(arg1[3], 0x400802, 0x5e, 0x43900000, 0x42800000, eax_1, 0f, 4)
00446ed7        *(arg1[3] + 0x178) = 0
00446ee4        int32_t result = hide_border_init(arg1[3])
00446ee9        arg1[2] = 0x3daaaaab
00446ef0        arg1[1] = 0
00446ef7        *arg1 = 0
00446f01        return result
