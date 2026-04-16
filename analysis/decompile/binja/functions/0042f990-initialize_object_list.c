/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_object_list @ 0x42f990 */

0042f991        int32_t i_1 = arg2
0042f9a0        *arg1 = 0
0042f9a6        arg1[1] = i_1
0042f9b3        void* result = allocate_tracked_memory(i_1 * 0xdc, "Object List")
0042f9bb        arg1[2] = result
0042f9c0        if (i_1 s> 0)
0042f9c3        void* ebx_1 = nullptr
0042f9d8        int32_t i
0042f9cc        result = initialize_object(ebx_1 + arg1[2])
0042f9d1        ebx_1 += 0xdc
0042f9d7        i = i_1
0042f9d7        i_1 -= 1
0042f9d8        do while (i != 1)
0042f9dd        return result
