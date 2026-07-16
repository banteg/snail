/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: apply_object_toon @ 0x42fa80 */

0042fa96        int32_t vertex_count = object->vertex_count
0042fa99        object->flags |= toon_flags | 0x4001
0042faa8        object->toon_vertices = allocate_tracked_memory(vertex_count * 0xc, "Object Toon Vertices")
0042fac2        object->toon_facequad_normals = allocate_tracked_memory(object->facequad_count * 0x18, "Object Toon FaceQuadNormals")
0042fac6        return
