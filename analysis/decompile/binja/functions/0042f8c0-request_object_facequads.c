/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_facequads @ 0x42f8c0 */

0042f8ca        if (facequad_count == 0)
0042f8cc        object->facequad_count = facequad_count
0042f8d1        return
0042f8d4        int32_t facequad_capacity = object->facequad_capacity
0042f8dd        if (facequad_capacity s> 0 && facequad_capacity s< facequad_count)
0042f8e4        report_errorf("Reallocation of FaceQuads impending\n")
0042f8ed        free_tracked_memory(object->facequads)
0042f8f5        object->facequad_count = 0
0042f901        if (object->facequad_count == 0)
0042f914        object->facequads = allocate_tracked_memory(facequad_count * 0x30, "Object FaceQuad List")
0042f91f        if (facequad_count s> object->facequad_capacity)
0042f921        object->facequad_capacity = facequad_count
0042f924        object->facequad_count = facequad_count
0042f929        return
