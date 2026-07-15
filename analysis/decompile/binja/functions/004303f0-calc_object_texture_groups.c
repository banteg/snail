/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_texture_groups @ 0x4303f0 */

004303f6        int32_t i = 0
00430468        while (i s< 2)
004303f8        struct ObjectFaceQuad* facequads = object->facequads
004303fe        int32_t ebx_1 = 0
00430400        int32_t j = 0
00430402        struct TextureRef* texture_ref = facequads->texture_ref
00430407        if (object->facequad_count s> 0)
00430409        char* ecx_1 = nullptr
0043040f        if ((object->flags:1.b & 4) != 0)
00430411        *(ecx_1 + facequads) |= 2
00430418        int32_t* eax_2 = *(&object->facequads->texture_ref + ecx_1)
0043041c        *eax_2 |= 0x20
0043041f        facequads = object->facequads
0043042c        if (*(&facequads->texture_ref + ecx_1) != texture_ref || (*(ecx_1 + facequads) & 0x10) != 0)
00430431        if (i == 1)
00430436        object->texture_group_ends[ebx_1] = j
00430439        facequads = object->facequads
0043043c        ebx_1 += 1
0043043d        texture_ref = *(&facequads->texture_ref + ecx_1)
00430441        j += 1
00430442        ecx_1 = &ecx_1[0x30]
00430448        do while (j s< object->facequad_count)
0043044d        if (i == 1)
00430452        object->texture_group_ends[ebx_1] = j
00430459        if (i == 0)
0043045f        request_object_texture_groups(object, ebx_1 + 1)
00430464        i += 1
0043046e        return
