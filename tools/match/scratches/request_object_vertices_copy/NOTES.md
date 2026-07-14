# request_object_vertices_copy @ 0x42f7d0

Allocates the Object-owned backup vertex array and copies the live `Vector3`
bank into it. The allocation now uses `vertex_count * sizeof(Vector3)` rather
than duplicating the 0xc-byte representation. Matching remains exact at 14/14
instructions with all three operands clean.
