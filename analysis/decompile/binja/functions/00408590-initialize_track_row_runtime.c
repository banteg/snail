/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_track_row_runtime @ 0x408590 */

00408599        initialize_renderable_bod(arg1 + 4)
004085a4        *(arg1 + 4) = &data_497330
004085aa        initialize_bod_base(arg1 + 0xb0)
004085b3        return arg1
