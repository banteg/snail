/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_facequad_normals @ 0x42f800 */

0042f808        if (object->vertex_normals == 0)
0042f821        object->vertex_normals = allocate_tracked_memory(object->vertex_count * 0xc, "Object Vertex Normals List")
0042f824        struct Vec3* facequad_normals = object->facequad_normals
0042f829        if (facequad_normals == 0)
0042f83a        facequad_normals = allocate_tracked_memory(object->facequad_count * 0x18, "Object FaceQuad Normals List")
0042f842        object->facequad_normals = facequad_normals
0042f846        return facequad_normals
