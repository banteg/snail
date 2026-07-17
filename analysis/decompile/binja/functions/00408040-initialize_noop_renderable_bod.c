/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_noop_renderable_bod @ 0x408040 */

00408043        initialize_renderable_bod(body)
00408048        body->bod.bod.vtable = &g_noop_runtime_callback_table
00408051        return body
