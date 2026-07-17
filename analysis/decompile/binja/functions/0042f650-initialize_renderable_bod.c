/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_renderable_bod @ 0x42f650 */

0042f653        initialize_bod_base(body)
0042f65b        body->bod.bod.vtable = &g_renderable_bod_vtable
0042f661        body->bod.bod.list_flags = 0x2000420
0042f668        set_matrix_identity(&body->transform)
0042f670        return body
