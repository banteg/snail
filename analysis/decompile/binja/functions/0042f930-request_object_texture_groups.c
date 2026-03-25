/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_texture_groups @ 0x42f930 */

0042f939        if (*(arg1 + 0x64) == 0)
0042f94c        void* eax_2 = allocate_tracked_memory(arg2 << 2, "Object FaceQuad Texture Groups")
0042f954        *(arg1 + 0x68) = arg2
0042f957        *(arg1 + 0x64) = arg2
0042f95a        *(arg1 + 0x6c) = eax_2
0042f95f        return eax_2
0042f966        int32_t eax_3 = *(arg1 + 0x68)
0042f96b        if (arg2 s> eax_3)
0042f972        eax_3 = report_errorf("Fixed FaceQuadTextureGroupsNumber too small")
0042f97a        *(arg1 + 0x64) = arg2
0042f97f        return eax_3
