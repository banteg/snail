/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_active_bod @ 0x4085e0 */

004085e3        initialize_bod_base(slot)
004085e8        slot->bod.bod.vtable = &g_active_bod_vtable
004085f1        return slot
