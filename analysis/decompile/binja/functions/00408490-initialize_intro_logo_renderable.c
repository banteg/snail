/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_intro_logo_renderable @ 0x408490 */

00408493        initialize_renderable_bod(letter)
00408498        letter->renderable.bod.bod.vtable = &g_logo_letter_vtable
004084a1        return letter
