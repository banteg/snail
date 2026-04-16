/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_frontend_widget_shortcut_key @ 0x402790 */

00402794        widget->shortcut_key_code = shortcut_key_code
004027a0        uint32_t result = widget->widget_flags | 0x80000
004027a5        widget->widget_flags = result
004027ab        return result
