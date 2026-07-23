/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: replace_object_list_texture_refs @ 0x430d90 */

00430d96        int32_t object_byte_offset = 0
00430d9a        int32_t object_index = 0
00430da0        if (object_list->count s<= 0)
00430da0        return
00430dad        int32_t object_byte_offset_spill = 0
00430e05        bool cond:0_1
00430db1        struct Object* current_object = &object_list->objects->_pad_00[object_byte_offset]
00430db9        if (current_object->vertex_count != 0)
00430dbe        int32_t face_index = 0
00430dc2        if (current_object->facequad_count s> 0)
00430dc4        int32_t face_byte_offset = 0
00430dc6        struct ObjectFaceQuad* facequads = current_object->facequads
00430dd1        if (*(&facequads->texture_ref + face_byte_offset) == old_texture)
00430dd3        *(&facequads->texture_ref + face_byte_offset) = new_texture
00430dd8        face_index += 1
00430dd9        face_byte_offset += 0x30
00430dde        do while (face_index s< current_object->facequad_count)
00430de3        replace_object_group_texture_refs(current_object, new_texture, old_texture)
00430df6        object_byte_offset = object_byte_offset_spill + 0xdc
00430dfb        cond:0_1 = object_index + 1 s< object_list->count
00430dfd        object_index += 1
00430e01        object_byte_offset_spill = object_byte_offset
00430e05        do while (cond:0_1)
00430e0e        return
