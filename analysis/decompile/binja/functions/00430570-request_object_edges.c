/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_edges @ 0x430570 */

00430573        void* result = *(arg1 + 0x70)
00430578        if (result == 0)
00430583        *(arg1 + 0x70) = arg2
0043058d        result = allocate_tracked_memory(arg2 * 0x24, "Object Edges")
00430595        *(arg1 + 0x74) = result
00430599        return result
