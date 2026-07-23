/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_texture_groups @ 0x4303f0 */

004303f6        int32_t pass_index = 0
00430468        while (pass_index s< 2)
004303f8        struct ObjectFaceQuad* facequads = object->facequads
004303fe        int32_t group_index = 0
00430400        int32_t face_index = 0
00430402        struct TextureRef* current_texture = facequads->texture_ref
00430407        if (object->facequad_count s> 0)
00430409        int32_t face_byte_offset = 0
0043040f        if ((object->flags:1.b & 4) != 0)
00430411        *(face_byte_offset + facequads) |= 2
00430418        struct TextureRef* active_texture = *(&object->facequads->texture_ref + face_byte_offset)
0043041c        active_texture->flags |= 0x20
0043041f        facequads = object->facequads
0043042c        if (*(&facequads->texture_ref + face_byte_offset) != current_texture || (*(face_byte_offset + facequads) & 0x10) != 0)
00430431        if (pass_index == 1)
00430436        object->texture_group_ends[group_index] = face_index
00430439        facequads = object->facequads
0043043c        group_index += 1
0043043d        current_texture = *(&facequads->texture_ref + face_byte_offset)
00430441        face_index += 1
00430442        face_byte_offset += 0x30
00430448        do while (face_index s< object->facequad_count)
0043044d        if (pass_index == 1)
00430452        object->texture_group_ends[group_index] = face_index
00430459        if (pass_index == 0)
0043045f        request_object_texture_groups(object, group_index + 1)
00430464        pass_index += 1
0043046e        return
