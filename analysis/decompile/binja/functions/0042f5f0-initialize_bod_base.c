/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_bod_base @ 0x42f5f0 */

0042f614        *arg1 = "P{@"
0042f61a        arg1[1] = 0x2000020
0042f621        store_color4f(&arg1[0xa], 1f, 1f, 1f, 1f)
0042f62d        data_50331c += 1
0042f63a        __builtin_memset(&arg1[4], 0, 0x14)
0042f646        return arg1
