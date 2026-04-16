/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_object_to_list @ 0x42fad0 */

0042fadb        if (*arg1 == arg1[1])
0042fae2        report_errorf("Too many Objects - Increase ObjectList.Init(MAX) in G0.cpp")
0042faea        int32_t eax_1 = *arg1
0042faf3        *arg1 = eax_1 + 1
0042fafb        void* result = arg1[2] + eax_1 * 0xdc
0042fb00        initialize_object(result)
0042fb09        return result
