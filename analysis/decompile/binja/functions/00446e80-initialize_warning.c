/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_warning @ 0x446e80 */

00446eb2        actor->border = allocate_border(data_4df904 + 0xb4c)
00446eb5        struct Color4f color
00446eb5        struct Color4f* eax_1 = set_color_rgba(&color, 1f, 1f, 1f, 0.999000013f)
00446ecf        initialize_frontend_sprite_button(actor->border, 0x400802, 0x5e, 0x43900000, 0x42800000, eax_1, 0f, 4)
00446ed7        actor->border->__offset(0x178).d = 0
00446ee4        hide_border_init(actor->border)
00446ee9        actor->progress_step = 0.0833333358f
00446ef0        actor->progress = 0f
00446ef7        actor->state = 0
00446f01        return
