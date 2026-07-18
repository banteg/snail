/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_track_fringe_supertramp_mesh @ 0x424ad0 */

00424ae7        set_bod_object(&self->fringe_mesh_bod, add_object_to_list(&g_object_list))
00424aec        struct Object* object = self->fringe_mesh_bod.object
00424af2        enum ObjectFlag flags = object->flags
00424af5        object->blend_mode = 5
00424b02        object->flags = flags | OBJECT_FLAG_DISABLE_CULLING
00424b12        request_object_vertices(object, (self->segment_count << 2) + 6)
00424b21        request_object_facequads(object, self->segment_count * 2 + 1)
00424b29        struct Vec3* vertices = object->vertices
00424b2c        struct ObjectFaceQuad* facequads = object->facequads
00424b2f        int32_t i = 0
00424b33        struct Vec3* vertices_1 = vertices
00424b37        if (self->segment_count s>= 0)
00424b3d        void* __offset(Vec3, 0x14) edi_1 = vertices + 0x14
00424b54        int32_t* edx_2 = &self->bod.object->vertices[(self->width_cells + 1) * i + 1]
00424b59        (edi_1 - 0x14)->x = *edx_2
00424b5e        (edi_1 - 0x14)->y = edx_2[1]
00424b64        (edi_1 - 0x14)->z = edx_2[2]
00424b7a        int32_t* eax_16 = &self->bod.object->vertices[(self->width_cells + 1) * i]
00424b7f        (edi_1 - 0x14)->__offset(0xc).d = *eax_16
00424b84        (edi_1 - 0x14)->__offset(0x10).d = eax_16[1]
00424b8a        (edi_1 - 0x14)->__offset(0x14).d = eax_16[2]
00424bae        struct Vec3 vector
00424bae        vector.x = fconvert.s(fconvert.t((edi_1 - 0x14)->__offset(0xc).d) - fconvert.t((edi_1 - 0x14)->x))
00424bb6        vector.y = fconvert.s(fconvert.t((edi_1 - 0x14)->__offset(0x10).d) - fconvert.t((edi_1 - 0x14)->y))
00424bc2        vector.z = fconvert.s(fconvert.t((edi_1 - 0x14)->__offset(0x14).d) - fconvert.t((edi_1 - 0x14)->z))
00424bc6        normalize_vector(&vector)
00424c05        float var_38_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.y) * fconvert.t(0.400000006f))) + fconvert.t((edi_1 - 0x14)->__offset(0x10).d))
00424c0d        long double x87_r7_15 = fconvert.t(fconvert.s(fconvert.t(vector.z) * fconvert.t(0.400000006f))) + fconvert.t((edi_1 - 0x14)->__offset(0x14).d)
00424c13        (edi_1 - 0x14)->x = fconvert.s(fconvert.t(vector.x) * fconvert.t(0.400000006f) + fconvert.t((edi_1 - 0x14)->__offset(0xc).d))
00424c16        (edi_1 - 0x14)->y = var_38_1
00424c24        (edi_1 - 0x14)->z = fconvert.s(x87_r7_15)
00424c27        uint32_t width_cells = self->width_cells
00424c3b        int32_t* ecx_10 = &self->bod.object->vertices[(width_cells + 1) * i + width_cells] - 0xc
00424c41        (edi_1 - 0x14)->__offset(0x18).d = *ecx_10
00424c46        (edi_1 - 0x14)->__offset(0x1c).d = ecx_10[1]
00424c4c        (edi_1 - 0x14)->__offset(0x20).d = ecx_10[2]
00424c4f        uint32_t width_cells_1 = self->width_cells
00424c66        int32_t* eax_31 = &self->bod.object->vertices[(width_cells_1 + 1) * i + width_cells_1]
00424c6b        (edi_1 - 0x14)->__offset(0x24).d = *eax_31
00424c70        (edi_1 - 0x14)->__offset(0x28).d = eax_31[1]
00424c76        (edi_1 - 0x14)->__offset(0x2c).d = eax_31[2]
00424c9b        vector.x = fconvert.s(fconvert.t((edi_1 - 0x14)->__offset(0x24).d) - fconvert.t((edi_1 - 0x14)->__offset(0x18).d))
00424ca3        vector.y = fconvert.s(fconvert.t((edi_1 - 0x14)->__offset(0x28).d) - fconvert.t((edi_1 - 0x14)->__offset(0x1c).d))
00424caf        vector.z = fconvert.s(fconvert.t((edi_1 - 0x14)->__offset(0x2c).d) - fconvert.t((edi_1 - 0x14)->__offset(0x20).d))
00424cb3        normalize_vector(&vector)
00424cce        i += 1
00424ccf        edi_1 += 0x30
00424cf6        float var_20_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.y) * fconvert.t(0.400000006f))) + fconvert.t((edi_1 - 0x14)->__offset(0xfffffffffffffff8).d))
00424cfe        long double x87_r7_30 = fconvert.t(fconvert.s(fconvert.t(vector.z) * fconvert.t(0.400000006f))) + fconvert.t((edi_1 - 0x14)->x:-4.d)
00424d05        (edi_1 - 0x14)->__offset(0xffffffffffffffe8).d = fconvert.s(fconvert.t(vector.x) * fconvert.t(0.400000006f) + fconvert.t((edi_1 - 0x14)->__offset(0xfffffffffffffff4).d))
00424d08        (edi_1 - 0x14)->__offset(0xffffffffffffffec).d = var_20_1
00424d13        (edi_1 - 0x14)->__offset(0xfffffffffffffff0).d = fconvert.s(x87_r7_30)
00424d1b        do while (i s<= self->segment_count)
00424d21        vertices = vertices_1
00424d28        int32_t ebp = 0
00424d2c        int32_t var_5c = 0
00424d30        if (self->segment_count s> 0)
00424d36        uint16_t* edi_2 = &facequads->vertex_0
00424d59        while (true)
00424d59        (edi_2 - 2)->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
00424d5c        int16_t ebp_1 = (ebp << 2).w
00424d5f        (edi_2 - 2)->vertex_0 = (ebp << 2).w + 4
00424d6c        (edi_2 - 2)->vertex_1 = ebp_1 + 5
00424d70        (edi_2 - 2)->vertex_2 = ebp_1 + 1
00424d79        (edi_2 - 2)->vertex_3 = ebp_1
00424d82        (edi_2 - 2)->uv[3].u = 0x3f000000
00424d85        (edi_2 - 2)->uv[3].v = 1f
00424d88        (edi_2 - 2)->uv[0].u = 0x3f000000
00424d8b        (edi_2 - 2)->uv[0].v = 1f
00424d90        (edi_2 - 2)->uv[1].u = 0x3f000000
00424d93        (edi_2 - 2)->uv[1].v = 0f
00424d96        (edi_2 - 2)->uv[2].u = 0x3f000000
00424d9a        (edi_2 - 2)->uv[2].v = 0f
00424da9        (edi_2 - 2)->__offset(0x3c).d = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
00424db2        (edi_2 - 2)->__offset(0x32).w = ebp_1 + 7
00424db9        (edi_2 - 2)->__offset(0x34).w = ebp_1 + 6
00424dc0        (edi_2 - 2)->__offset(0x36).w = ebp_1 + 2
00424dc9        (edi_2 - 2)->__offset(0x38).w = ebp_1 + 3
00424dd2        (edi_2 - 2)->__offset(0x5c).d = 0
00424dd5        (edi_2 - 2)->__offset(0x40).d = 0x3f000000
00424dd8        (edi_2 - 2)->__offset(0x44).d = 0
00424de0        __builtin_memcpy(&edi_2[0x23], "\x00\x00\x00\x3f\x00\x00\x80\x3f\x00\x00\x00\x3f\x00\x00\x80\x3f\x00\x00\x00\x3f", 0x14)
00424df4        edi_2 = &edi_2[0x30]
00424df7        bool cond:2_1 = var_5c + 1 s< self->segment_count
00424df9        var_5c += 1
00424dfd        if (not(cond:2_1))
00424dfd        break
00424d3b        ebp = var_5c
00424e03        vertices = vertices_1
00424e07        uint32_t segment_count_1 = self->segment_count
00424e14        float* eax_45 = &vertices[segment_count_1 * 4]
00424e24        float* ecx_25 = ((segment_count_1 * 3 + 3) << 4) + vertices
00424e67        float var_20_2 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(eax_45[1]) - fconvert.t(eax_45[-0xb]))) * fconvert.t(0.400000006f))) + fconvert.t(eax_45[1]))
00424e6f        long double x87_r7_38 = fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(eax_45[2]) - fconvert.t(eax_45[-0xa]))) * fconvert.t(0.400000006f))) + fconvert.t(eax_45[2])
00424e76        *ecx_25 = fconvert.s((fconvert.t(*eax_45) - fconvert.t(eax_45[-0xc])) * fconvert.t(0.400000006f) + fconvert.t(*eax_45))
00424e78        ecx_25[1] = var_20_2
00424e83        ecx_25[2] = fconvert.s(x87_r7_38)
00424e8f        void* eax_50 = &vertices[self->segment_count * 4]
00424ee2        float var_20_3 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(eax_50 + 0x1c)) - fconvert.t(*(eax_50 - 0x14)))) * fconvert.t(0.400000006f))) + fconvert.t(*(eax_50 + 0x1c)))
00424eea        long double x87_r7_46 = fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(eax_50 + 0x20)) - fconvert.t(*(eax_50 - 0x10)))) * fconvert.t(0.400000006f))) + fconvert.t(*(eax_50 + 0x20))
00424ef1        *(eax_50 + 0x3c) = fconvert.s((fconvert.t(*(eax_50 + 0x18)) - fconvert.t(*(eax_50 - 0x18))) * fconvert.t(0.400000006f) + fconvert.t(*(eax_50 + 0x18)))
00424ef3        *(eax_50 + 0x40) = var_20_3
00424efe        *(eax_50 + 0x44) = fconvert.s(x87_r7_46)
00424f01        uint32_t segment_count = self->segment_count
00424f0e        int32_t* edx_22 = ((segment_count * 3 + 3) << 4) + vertices
00424f15        int32_t* eax_54 = &vertices[segment_count * 4]
00424f17        *eax_54 = *edx_22
00424f1c        eax_54[1] = edx_22[1]
00424f24        eax_54[2] = edx_22[2]
00424f32        void* edi_3 = &vertices[self->segment_count * 4]
00424f3c        *(edi_3 + 0x18) = *(edi_3 + 0x3c)
00424f46        *(edi_3 + 0x1c) = *(edi_3 + 0x40)
00424f4c        *(edi_3 + 0x20) = *(edi_3 + 0x44)
00424f54        struct TextureRef* eax_59 = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
00424f5f        uint32_t ecx_34 = self->segment_count * 0x60
00424f62        *(&facequads->texture_ref + ecx_34) = eax_59
00424f78        facequads[self->segment_count * 2].vertex_0 = (self->segment_count.w << 2) + 1
00424f80        ecx_34.w = self->segment_count.w
00424f87        ecx_34.w <<= 2
00424f8e        int32_t ecx_35 = ecx_34 + 3
00424f91        facequads[self->segment_count * 2].vertex_1 = ecx_35.w
00424f99        ecx_35.w = self->segment_count.w
00424fa0        ecx_35.w <<= 2
00424fa7        int32_t ecx_36 = ecx_35 + 5
00424faa        facequads[self->segment_count * 2].vertex_2 = ecx_36.w
00424fb2        ecx_36.w = self->segment_count.w
00424fb9        ecx_36.w += 1
00424fc1        facequads[self->segment_count * 2].vertex_3 = (ecx_36 << 2).w
00424fd6        facequads[self->segment_count * 2].uv[0].u = 0x3f000000
00424fe3        facequads[self->segment_count * 2].uv[0].v = 0
00424ff0        facequads[self->segment_count * 2].uv[1].u = 0x3f000000
00424ffd        facequads[self->segment_count * 2].uv[1].v = 0
0042500a        facequads[self->segment_count * 2].uv[2].u = 0x3f000000
0042501c        facequads[self->segment_count * 2].uv[2].v = 0x3f800000
0042502a        facequads[self->segment_count * 2].uv[3].u = 0x3f000000
00425039        facequads[self->segment_count * 2].uv[3].v = 0x3f800000
00425041        return
