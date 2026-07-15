/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_track_fringe_mesh @ 0x4246a0 */

004246b7        set_bod_object(&self->fringe_mesh_bod, add_object_to_list(&g_object_list))
004246cd        struct tColour out
004246cd        struct tColour* eax_1 = get_track_skirt_color(&g_game_base->subgame, &out)
004246da        struct Object* object = self->fringe_mesh_bod.object
004246e0        self->fringe_mesh_bod.color.r = eax_1->r
004246e5        self->fringe_mesh_bod.color.g = eax_1->g
004246eb        self->fringe_mesh_bod.color.b = eax_1->b
004246f1        self->fringe_mesh_bod.color.a = eax_1->a
004246f7        enum ObjectFlag ebp_1 = object->flags | OBJECT_FLAG_DISABLE_CULLING | 0x40
004246fd        object->blend_mode = 5
00424704        object->flags = ebp_1
00424714        request_object_vertices(object, (self->segment_count << 2) + 4)
00424721        request_object_facequads(object, self->segment_count << 1)
00424729        struct ObjectFaceQuad* facequads = object->facequads
00424735        uint32_t var_68 = 0
0042473d        if (self->segment_count s>= 0)
00424743        void* __offset(Vec3, 0x14) esi_1 = object->vertices + 0x14
004249da        bool cond:2_1
0042474b        int32_t var_64_1
0042474b        uint32_t width_cells_1
0042474b        uint32_t width_cells
0042474b        uint32_t width_cells_2
0042474b        int32_t edx_2
0042474b        if (self->is_mirrored_x == 0)
00424767        width_cells = self->width_cells
0042476a        width_cells_2 = 0
0042476c        edx_2 = 1
00424771        width_cells_1 = width_cells
00424778        var_64_1 = width_cells - 1
0042474d        width_cells = self->width_cells
00424750        var_64_1 = 1
00424758        width_cells_2 = width_cells
0042475a        width_cells_1 = 0
00424762        edx_2 = width_cells - 1
0042477d        struct Vec3* ebx_1 = esi_1 - 0x14
00424790        int32_t* edx_4 = &self->bod.object->vertices[(width_cells + 1) * var_68 + edx_2]
00424797        ebx_1->x = *edx_4
0042479c        ebx_1->y = edx_4[1]
004247a5        ebx_1->z = edx_4[2]
004247be        int32_t* eax_18 = &self->bod.object->vertices[(self->width_cells + 1) * var_68 + width_cells_2]
004247c3        (esi_1 - 0x14)->__offset(0xc).d = *eax_18
004247c8        (esi_1 - 0x14)->__offset(0x10).d = eax_18[1]
004247ce        (esi_1 - 0x14)->__offset(0x14).d = eax_18[2]
004247f1        struct Vec3 vector
004247f1        vector.x = fconvert.s(fconvert.t((esi_1 - 0x14)->__offset(0xc).d) - fconvert.t(ebx_1->x))
004247f9        vector.y = fconvert.s(fconvert.t((esi_1 - 0x14)->__offset(0x10).d) - fconvert.t((esi_1 - 0x14)->y))
00424805        vector.z = fconvert.s(fconvert.t((esi_1 - 0x14)->__offset(0x14).d) - fconvert.t((esi_1 - 0x14)->z))
00424809        normalize_vector(&vector)
0042484d        float var_3c_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.y) * fconvert.t(0.400000006f))) + fconvert.t((esi_1 - 0x14)->__offset(0x10).d))
00424855        long double x87_r7_15 = fconvert.t(fconvert.s(fconvert.t(vector.z) * fconvert.t(0.400000006f))) + fconvert.t((esi_1 - 0x14)->__offset(0x14).d)
0042485b        ebx_1->x = fconvert.s(fconvert.t(vector.x) * fconvert.t(0.400000006f) + fconvert.t((esi_1 - 0x14)->__offset(0xc).d))
0042485d        ebx_1->y = var_3c_1
00424868        ebx_1->z = fconvert.s(x87_r7_15)
00424883        int32_t* eax_27 = &self->bod.object->vertices[(self->width_cells + 1) * var_68 + var_64_1]
0042488a        *(esi_1 + 4) = *eax_27
0042488f        *(esi_1 + 8) = eax_27[1]
00424899        *(esi_1 + 0xc) = eax_27[2]
004248b3        int32_t* edx_17 = &self->bod.object->vertices[(self->width_cells + 1) * var_68 + width_cells_1]
004248b8        (esi_1 - 0x14)->__offset(0x24).d = *edx_17
004248bd        (esi_1 - 0x14)->__offset(0x28).d = edx_17[1]
004248c3        (esi_1 - 0x14)->__offset(0x2c).d = edx_17[2]
004248e8        vector.x = fconvert.s(fconvert.t((esi_1 - 0x14)->__offset(0x24).d) - fconvert.t(*(esi_1 + 4)))
004248ec        vector.y = fconvert.s(fconvert.t((esi_1 - 0x14)->__offset(0x28).d) - fconvert.t((esi_1 - 0x14)->__offset(0x1c).d))
004248fc        vector.z = fconvert.s(fconvert.t((esi_1 - 0x14)->__offset(0x2c).d) - fconvert.t((esi_1 - 0x14)->__offset(0x20).d))
00424900        normalize_vector(&vector)
0042491b        out.g = fconvert.s(fconvert.t(vector.y) * fconvert.t(0.400000006f))
00424929        out.b = fconvert.s(fconvert.t(vector.z) * fconvert.t(0.400000006f))
0042493f        float var_24_1 = fconvert.s(fconvert.t(out.g) + fconvert.t((esi_1 - 0x14)->__offset(0x28).d))
00424947        long double x87_r7_30 = fconvert.t(out.b) + fconvert.t((esi_1 - 0x14)->__offset(0x2c).d)
0042494e        *(esi_1 + 4) = fconvert.s(fconvert.t(vector.x) * fconvert.t(0.400000006f) + fconvert.t((esi_1 - 0x14)->__offset(0x24).d))
00424951        *(esi_1 + 8) = var_24_1
00424958        long double x87_r7_31 = fconvert.t(clamp_side)
0042495f        long double temp1_1 = fconvert.t(-1f)
0042495f        x87_r7_31 - temp1_1
00424969        *(esi_1 + 0xc) = fconvert.s(x87_r7_30)
00424971        if ((((x87_r7_31 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp1_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
00424995        long double x87_r7_33 = fconvert.t(clamp_side)
0042499c        long double temp2_1 = fconvert.t(1f)
0042499c        x87_r7_33 - temp2_1
004249a7        if ((((x87_r7_33 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_33, temp2_1) ? 1 : 0) << 0xa | (x87_r7_33 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
004249a9        int32_t i_3 = 4
004249c7        int32_t i
004249ae        long double x87_r7_34 = fconvert.t(ebx_1->x)
004249b0        long double temp4_1 = fconvert.t(0f)
004249b0        x87_r7_34 - temp4_1
004249bb        if ((((x87_r7_34 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_34, temp4_1) ? 1 : 0) << 0xa | (x87_r7_34 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004249bd        ebx_1->x = 0
004249c3        ebx_1 = &ebx_1[1]
004249c6        i = i_3
004249c6        i_3 -= 1
004249c7        do while (i != 1)
00424973        int32_t i_2 = 4
00424991        int32_t i_1
00424978        long double x87_r7_32 = fconvert.t(ebx_1->x)
0042497a        long double temp3_1 = fconvert.t(0f)
0042497a        x87_r7_32 - temp3_1
00424985        if ((((x87_r7_32 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_32, temp3_1) ? 1 : 0) << 0xa | (x87_r7_32 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00424987        ebx_1->x = 0
0042498d        ebx_1 = &ebx_1[1]
00424990        i_1 = i_2
00424990        i_2 -= 1
00424991        do while (i_1 != 1)
004249d1        esi_1 += 0x30
004249d4        cond:2_1 = var_68 + 1 s<= self->segment_count
004249d6        var_68 += 1
004249da        do while (cond:2_1)
004249e3        int32_t var_68_1 = 0
004249ed        if (self->segment_count s<= 0)
004249ed        return
004249fc        uint16_t* esi_2 = &facequads->vertex_0
00424abd        bool cond:1_1
00424a16        (esi_2 - 2)->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, 0, 0)
00424a1b        int16_t ebp_6 = (var_68_1 << 2).w
00424a31        (esi_2 - 2)->vertex_0 = ebp_6 + 5
00424a34        (esi_2 - 2)->vertex_1 = (var_68_1 << 2).w + 4
00424a3b        (esi_2 - 2)->vertex_2 = ebp_6
00424a3f        (esi_2 - 2)->vertex_3 = ebp_6 + 1
00424a48        (esi_2 - 2)->uv[3].v = 0f
00424a4b        (esi_2 - 2)->uv[0].u = 0x3f000000
00424a4e        (esi_2 - 2)->uv[0].v = 0f
00424a51        __builtin_memcpy(&esi_2[0xb], "\x00\x00\x00\x3f\x00\x00\x80\x3f\x00\x00\x00\x3f\x00\x00\x80\x3f\x00\x00\x00\x3f", 0x14)
00424a6e        (esi_2 - 2)->__offset(0x3c).d = get_or_create_texture_ref(&g_texture_refs, texture_path, 0, 0)
00424a77        (esi_2 - 2)->__offset(0x32).w = ebp_6 + 6
00424a7e        (esi_2 - 2)->__offset(0x34).w = ebp_6 + 7
00424a85        (esi_2 - 2)->__offset(0x36).w = ebp_6 + 3
00424a89        (esi_2 - 2)->__offset(0x38).w = ebp_6 + 2
00424a92        (esi_2 - 2)->__offset(0x58).d = 0x3f000000
00424a95        (esi_2 - 2)->__offset(0x5c).d = 0x3f800000
00424a98        (esi_2 - 2)->__offset(0x40).d = 0x3f000000
00424a9b        (esi_2 - 2)->__offset(0x44).d = 0x3f800000
00424aa0        (esi_2 - 2)->__offset(0x48).d = 0x3f000000
00424aa3        (esi_2 - 2)->__offset(0x4c).d = 0
00424aa6        (esi_2 - 2)->__offset(0x50).d = 0x3f000000
00424aa9        (esi_2 - 2)->__offset(0x54).d = 0
00424ab4        esi_2 = &esi_2[0x30]
00424ab7        cond:1_1 = var_68_1 + 1 s< self->segment_count
00424ab9        var_68_1 += 1
00424abd        do while (cond:1_1)
00424aca        return
