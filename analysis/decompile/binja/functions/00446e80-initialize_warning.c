/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_warning @ 0x446e80 */

00446eb2        warning->border = allocate_border(&g_game_base->border_manager)
00446eb5        struct tColour color
00446eb5        struct tColour* eax_1 = set_color_rgba(&color, 1f, 1f, 1f, 0.999000013f)
00446ecf        initialize_frontend_sprite_button(warning->border, 0x400802, 0x5e, 0x43900000, 0x42800000, eax_1, 0f, 4)
00446ed7        warning->border->sprite_shadow_offset = 0f
00446ee4        hide_border_init(warning->border)
00446ee9        warning->phase_step = 0.0833333358f
00446ef0        warning->phase = 0f
00446ef7        warning->state = 0
00446f01        return
