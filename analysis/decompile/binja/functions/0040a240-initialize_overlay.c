/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_overlay @ 0x40a240 */

0040a247        *(arg1 + 0x144) = 0
0040a253        *(arg1 + 0x148) = 0x39bf9cd0
0040a25d        set_matrix_identity(arg1 + 0x38)
0040a268        *(arg1 + 0x140) = 0x42180000
0040a272        set_matrix_identity(arg1 + 0xb8)
0040a27e        invert_matrix_from_source(arg1 + 0x100, arg1 + 0x38)
0040a285        return 0
