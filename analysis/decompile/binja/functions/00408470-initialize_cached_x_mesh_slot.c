/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_cached_x_mesh_slot @ 0x408470 */

00408471        void*** result = arg1
00408473        initialize_bod_base(arg1)
00408478        *result = &g_cached_x_mesh_slot_vtable
00408481        return result
