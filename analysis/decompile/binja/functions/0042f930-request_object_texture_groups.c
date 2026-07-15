/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_texture_groups @ 0x42f930 */

0042f939        if (object->texture_group_count == 0)
0042f94c        int32_t* eax_2 = allocate_tracked_memory(group_count << 2, "Object FaceQuad Texture Groups")
0042f954        object->texture_group_capacity = group_count
0042f957        object->texture_group_count = group_count
0042f95a        object->texture_group_ends = eax_2
0042f95f        return
0042f96b        if (group_count s> object->texture_group_capacity)
0042f972        report_errorf("Fixed FaceQuadTextureGroupsNumber too small")
0042f97a        object->texture_group_count = group_count
0042f97f        return
