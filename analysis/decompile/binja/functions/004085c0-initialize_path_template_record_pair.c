/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_path_template_record_pair @ 0x4085c0 */

004085c1        void*** result = arg1
004085c3        initialize_bod_base(arg1)
004085cb        initialize_bod_base(&result[0x18])
004085d0        *result = &data_497334
004085d9        return result
