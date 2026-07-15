/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_vertices_copy @ 0x42f7d0 */

0042f7ec        object->copied_vertices = allocate_tracked_memory(object->vertex_count * 0xc, "Object Vertex List")
0042f7ef        copy_object_vertices(object)
0042f7f5        return
