/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_facequad_normals @ 0x42f800 */

0042f808        if (*(arg1 + 0x44) == 0)
0042f821        *(arg1 + 0x44) = allocate_tracked_memory(*(arg1 + 0x2c) * 0xc, "Object Vertex Normals List")
0042f824        void* result = *(arg1 + 0x60)
0042f829        if (result == 0)
0042f83a        result = allocate_tracked_memory(*(arg1 + 0x54) * 0x18, "Object FaceQuad Normals List")
0042f842        *(arg1 + 0x60) = result
0042f846        return result
