/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_overlay @ 0x40a240 */

0040a240        int32_t esi
0040a240        int32_t var_4 = esi
0040a243        int32_t edi
0040a243        int32_t var_8 = edi
0040a247        *(arg1 + 0x144) = 0
0040a253        *(arg1 + 0x148) = 0x39bf9cd0
0040a25d        set_matrix_identity(arg1 + 0x38)
0040a268        *(arg1 + 0x140) = 0x42180000
0040a272        set_matrix_identity(arg1 + 0xb8)
0040a277        struct TransformMatrix* var_c = arg1 + 0x38
0040a27e        struct TransformMatrix* source
0040a27e        invert_matrix_from_source(arg1 + 0x100, source)
0040a285        return 0
