/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_golb_shot @ 0x408690 */

00408694        initialize_renderable_bod(shot)
004086a1        initialize_renderable_bod(&shot->vapour)
004086a6        shot->vapour.body.bod.bod.vtable = &g_vapour_vtable
004086b4        initialize_renderable_bod(&shot->tertiary_body)
004086b9        shot->tertiary_body.bod.bod.vtable = &g_golb_noop_body_vtable
004086bf        shot->primary_body.bod.bod.vtable = &g_golb_shot_vtable
004086c9        return shot
