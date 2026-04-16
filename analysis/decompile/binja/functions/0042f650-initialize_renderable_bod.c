/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_renderable_bod @ 0x42f650 */

0042f653        initialize_bod_base(arg1)
0042f65b        *arg1 = &data_497500
0042f661        arg1[1] = 0x2000420
0042f668        set_matrix_identity(&arg1[0xe])
0042f670        return arg1
