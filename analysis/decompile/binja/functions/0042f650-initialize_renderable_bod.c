/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_renderable_bod @ 0x42f650 */

0042f651        void*** result = arg1
0042f653        initialize_bod_base(arg1)
0042f65b        *result = &data_497500
0042f661        result[1] = 0x2000420
0042f668        set_matrix_identity(&result[0xe])
0042f670        return result
