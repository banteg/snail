/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_intro_logo_renderable @ 0x408490 */

00408491        void*** result = arg1
00408493        initialize_renderable_bod(arg1)
00408498        *result = &g_intro_logo_renderable_vtable
004084a1        return result
