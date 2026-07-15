/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_edges @ 0x430570 */

00430578        if (object->edge_count == 0)
00430583        object->edge_count = edge_count
00430595        object->edges = allocate_tracked_memory(edge_count * 0x24, "Object Edges")
00430599        return
