/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: sort_object_faces_by_texture_group @ 0x419fd0 */

00419fd5        struct Object* retained_object = object
00419fd9        int32_t base_index = 0
00419fdb        int32_t grouped_swaps = 0
00419fdf        int32_t facequad_count = retained_object->facequad_count
00419fe2        struct ObjectFaceQuad* facequads = retained_object->facequads
00419fe7        struct ObjectFaceQuad* retained_facequads = facequads
00419feb        if (facequad_count s<= 0)
00419feb        return
00419ff7        int32_t scan_index = base_index + 1
00419fff        struct TextureRef* texture_ref = facequads[base_index].texture_ref
0041a007        if (scan_index s< facequad_count)
0041a015        struct ObjectFaceQuad* scan_face = &facequads[scan_index]
0041a017        int32_t insert_index = scan_index
0041a01b        struct ObjectFaceQuad* insert_face = &facequads[scan_index]
0041a024        if (scan_face->texture_ref == texture_ref)
0041a02c        if (scan_index != insert_index)
0041a044        base_index += 1
0041a045        struct ObjectFaceQuad swap_face
0041a045        __builtin_memcpy(&swap_face, insert_face, 0x30)
0041a04e        struct ObjectFaceQuad* insert_copy_destination = insert_face
0041a050        insert_face = &insert_face[1]
0041a053        __builtin_memcpy(insert_copy_destination, scan_face, 0x30)
0041a060        __builtin_memcpy(scan_face, &swap_face, 0x30)
0041a06c        insert_index += 1
0041a070        retained_object = object
0041a074        grouped_swaps += 1
0041a078        facequads = retained_facequads
0041a02e        base_index += 1
0041a02f        insert_face = &insert_face[1]
0041a033        insert_index += 1
0041a07f        scan_index += 1
0041a080        scan_face = &scan_face[1]
0041a085        do while (scan_index s< retained_object->facequad_count)
0041a087        facequad_count = retained_object->facequad_count
0041a08a        base_index += 1
0041a08d        do while (base_index s< facequad_count)
0041a09a        return
