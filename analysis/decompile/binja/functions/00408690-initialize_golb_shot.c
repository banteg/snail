/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_golb_shot @ 0x408690 */

00408694        initialize_renderable_bod(arg1)
004086a1        initialize_renderable_bod(&arg1[0x20])
004086a6        arg1[0x20] = &g_vapour_vtable
004086b4        initialize_renderable_bod(&arg1[0x46])
004086b9        arg1[0x46] = &g_golb_noop_body_vtable
004086bf        *arg1 = &g_golb_shot_vtable
004086c9        return arg1
