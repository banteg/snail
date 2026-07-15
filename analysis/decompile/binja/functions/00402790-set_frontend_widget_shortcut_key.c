/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_frontend_widget_shortcut_key @ 0x402790 */

00402794        widget->shortcut_key_code = shortcut_key_code
004027a5        widget->widget_flags |= FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED
004027ab        return
