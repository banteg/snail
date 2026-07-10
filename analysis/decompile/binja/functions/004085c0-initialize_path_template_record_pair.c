/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_path_template_record_pair @ 0x4085c0 */

004085c3        initialize_bod_base(arg1)
004085cb        initialize_bod_base(&arg1[0x18])
004085d0        *arg1 = &g_path_template_record_vtable
004085d9        return arg1
