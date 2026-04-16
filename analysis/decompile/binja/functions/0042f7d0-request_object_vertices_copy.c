/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_vertices_copy @ 0x42f7d0 */

0042f7ec        *(arg1 + 0x3c) = allocate_tracked_memory(*(arg1 + 0x2c) * 0xc, "Object Vertex List")
0042f7f5        return copy_object_vertices(arg1)
