/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: unhide_all_borders @ 0x403400 */

00403405        apply_all_border_visibility_mode(&manager->border_stack, 1)
0040340a        return
