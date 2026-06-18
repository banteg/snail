/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: render_object @ 0x4126c0 */

004126cb        int32_t result = arg1->flags
004126de        if ((result & 0x80000) != 0 && (result & 0x40000) == 0)
004126e4        result = arg1->vertex_count
004126e9        if (result != 0)
004126f0        refresh_object_vertex_buffer(arg1)
004126f9        int32_t* eax = data_502fec
0041270e        void var_40
0041270e        __builtin_memcpy(&var_40, arg2, 0x40)
00412719        (*(*eax + 0x94))(eax, 0x100, &var_40)
00412726        char var_54_3
00412726        if ((arg1->flags & 0x100000) == 0)
0041272c        var_54_3 = 1
00412728        var_54_3 = 0
0041272e        set_cull_mode(var_54_3)
00412739        int32_t i = 0
0041273d        if (arg1->texture_group_count s> 0)
0041274b        char ecx_3 = data_503260
00412753        if (ecx_3 != 0)
00412789        if (ecx_3 != 1 || arg6 != ecx_3 || (arg1->group_texture_refs[i]->flags & 0x10000) != 0)
00412795        label_412795:
00412795        struct TextureRef* override_texture_ref_1 = arg1->group_texture_refs[i]
0041279a        if (override_texture_ref_1 != 0)
004127a4        struct TextureRef* override_texture_ref
004127a4        if ((arg1->flags.b & 8) == 0)
004127ac        override_texture_ref = override_texture_ref_1
004127a9        override_texture_ref = arg1->override_texture_ref
004127ad        bind_texture_ref(override_texture_ref)
004127ba        if ((arg1->flags.b & 0x80) == 0)
00412801        int32_t* eax_9 = data_502fec
0041280f        (*(*eax_9 + 0xfc))(eax_9, 0, 0x18, 0)
004127ca        int32_t* eax_7 = data_502fec
004127cf        g_object_texture_transform_matrix.basis_forward.x = arg3
004127dd        g_object_texture_transform_matrix.basis_forward.y = fconvert.s(fconvert.t(1f) - fconvert.t(arg4))
004127e5        (*(*eax_7 + 0x94))(eax_7, 0x10, &g_object_texture_transform_matrix)
004127eb        int32_t* eax_8 = data_502fec
004127f9        (*(*eax_8 + 0xfc))(eax_8, 0, 0x18, 2)
0041282d        if (arg5[3] == 0x3f800000 || (arg1->group_texture_refs[i]->flags & 0x10000) == 0)
0041286f        int32_t* eax_11 = data_502fec
0041287b        (*(*eax_11 + 0xc8))(eax_11, 0x1b, 0)
00412833        set_blend_mode(arg1->blend_mode)
00412838        uint32_t flags = arg1->flags
00412840        if ((flags.b & 0x50) != 0)
00412842        flags.b &= 0xbf
00412849        arg1->flags = flags
00412851        int32_t var_60_3 = *arg5
00412856        int32_t var_5c_5 = arg5[1]
0041285c        int32_t var_58_5 = arg5[2]
00412862        int32_t var_54_8 = arg5[3]
00412865        set_object_color(arg1)
00412887        int32_t* eax_12 = data_502fec
00412897        (*(*eax_12 + 0x14c))(eax_12, 0, arg1->render_buffers->vertex_buffer, 0x18)
0041289d        int32_t* eax_13 = data_502fec
004128aa        (*(*eax_13 + 0x130))(eax_13, 0x142)
004128b6        int32_t* eax_14 = data_502fec
004128c3        (*(*eax_14 + 0x154))(eax_14, arg1->index_buffer->buffer, 0)
004128cf        int32_t* eax_15 = data_502fec
004128f0        (*(*eax_15 + 0x11c))(eax_15, 4, 0, arg1->grouped_vertex_count, arg1->group_index_starts[i], arg1->group_primitive_counts[i])
0041290c        ecx_3 = data_503260
00412912        int32_t eax_18 = data_503170 + 1
00412913        data_4f7450 += arg1->group_primitive_counts[i]
00412919        data_503170 = eax_18
00412769        if (arg6 != 1 || (arg1->group_texture_refs[i]->flags & 0x10000) == 0)
00412758        goto label_412795
00412921        i += 1
00412924        do while (i s< arg1->texture_group_count)
00412930        return render_object_toon(arg1, arg2)
0041293f        return result
