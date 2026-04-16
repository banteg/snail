/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: apply_object_toon @ 0x42fa80 */

0042fa96        int32_t eax_1 = *(arg1 + 0x2c)
0042fa99        *(arg1 + 0x10) |= arg2 | 0x4001
0042faa8        *(arg1 + 8) = allocate_tracked_memory(eax_1 * 0xc, "Object Toon Vertices")
0042faba        void* result = allocate_tracked_memory(*(arg1 + 0x54) * 0x18, "Object Toon FaceQuadNormals")
0042fac2        *(arg1 + 0xc) = result
0042fac6        return result
