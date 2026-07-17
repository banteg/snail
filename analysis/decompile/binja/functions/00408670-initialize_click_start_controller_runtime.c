/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_click_start_controller_runtime @ 0x408670 */

00408673        initialize_renderable_bod(click_start)
00408678        click_start->bod.bod.bod.vtable = &g_click_start_controller_vtable
00408681        return click_start
