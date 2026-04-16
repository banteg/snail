/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_frontend_widget_shortcut_key @ 0x402790 */

00402794        widget->__offset(0x194).d = shortcut_key_code
004027a0        int32_t result = widget->__offset(0x1a0).d | 0x80000
004027a5        widget->__offset(0x1a0).d = result
004027ab        return result
