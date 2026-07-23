/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: replace_object_group_texture_refs @ 0x4145c0 */

004145cb        if ((object->flags & OBJECT_FLAG_RENDER_BUFFERS_READY) == 0)
004145cb        return
004145d0        int32_t group_index = 0
004145d4        if (object->texture_group_count s<= 0)
004145d4        return
004145e1        struct TextureRef** group_texture_refs = object->group_texture_refs
004145ef        if (group_texture_refs[group_index] == old_texture)
004145f1        group_texture_refs[group_index] = new_texture
004145f6        group_index += 1
004145f9        do while (group_index s< object->texture_group_count)
004145fe        return
