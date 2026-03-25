/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_worm_path_template_pair @ 0x420170 */

00420180        int32_t i_3 = 0
00420183        self->kind = PATH_TEMPLATE_KIND_WORM
00420186        self->is_mirrored_x = 0
0042018a        self->side_exit_mode = 0
0042018d        self->width_cells = 0x10
00420194        self->width_or_scale = 4f
0042019b        self->segment_count = 0x18
0042019e        self->segment_count_f = 96f
004201a5        allocate_path_template_samples(self)
004201aa        self->special_runtime_flag_9c = 0
004201b1        int32_t var_80 = 0
004201b5        void* i = nullptr
0042026c        while (i s< 0x2a0)
004201ba        *(&self->primary_samples->center_x + i) = 0
004201c4        *(&self->primary_samples->rotation_scalar_98 + i) = 0
004201ce        *(&self->primary_samples->rotation_scalar_94 + i) = 0
004201d8        *(&self->primary_samples->special_scalar + i) = 0
004201e2        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
004201f4        set_matrix_identity(i + self->primary_samples)
004201f9        struct PathTemplateSample* primary_samples_1 = self->primary_samples
00420201        long double x87_r7_1 = float.t(var_80)
00420213        *(&primary_samples_1->transform.position + i) = *(&primary_samples_1->center_x + i)
00420219        *(&self->primary_samples->transform.position.y + i) = 0x3efae148
00420223        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_1 * fconvert.t(self->width_or_scale))
0042022c        set_matrix_identity(self->secondary_samples + i)
00420242        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
00420249        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
00420253        i += 0xa8
00420259        *(self->secondary_samples + i - 0x70) = fconvert.s(fconvert.t(fconvert.s(x87_r7_1)) * fconvert.t(self->width_or_scale))
00420268        var_80 += 1
00420272        int32_t ebx = 0x14
00420277        void* edi = 0xd20
0042027c        int32_t var_70_2 = 0x14
00420283        *(&self->primary_samples->center_x + edi) = 0
0042028d        *(&self->primary_samples->rotation_scalar_98 + edi) = 0
00420297        *(&self->primary_samples->rotation_scalar_94 + edi) = 0
004202a1        *(&self->primary_samples->special_scalar + edi) = 0
004202ab        *(&self->primary_samples->lateral_scale + edi) = 0x3f800000
004202bd        set_matrix_identity(edi + self->primary_samples)
004202c2        struct PathTemplateSample* primary_samples_2 = self->primary_samples
004202c5        long double x87_r7_5 = float.t(var_70_2)
004202d7        *(&primary_samples_2->transform.position + edi) = *(&primary_samples_2->center_x + edi)
004202dd        *(&self->primary_samples->transform.position.y + edi) = 0x3efae148
004202eb        *(&self->primary_samples->transform.position.z + edi) = fconvert.s(x87_r7_5 * fconvert.t(self->width_or_scale))
004202f4        set_matrix_identity(self->secondary_samples + edi)
0042030a        *(&self->secondary_samples->transform.position + edi) = *(&self->primary_samples->center_x + edi)
00420311        *(&self->secondary_samples->transform.position.y + edi) = 0x3efae148
0042031f        edi += 0xa8
00420325        ebx += 1
00420326        var_70_2 = ebx
0042032d        *(self->secondary_samples + edi - 0x70) = fconvert.s(fconvert.t(fconvert.s(x87_r7_5)) * fconvert.t(self->width_or_scale))
00420334        do while (ebx - 0x14 s< 4)
0042033a        int32_t ebx_1 = 0
004205b1        int16_t top_1
0042033c        void* i_1 = 0x2a0
004205b1        while (i_1 s< 0xd20)
00420344        *(&self->primary_samples->center_x + i_1) = 0
0042034e        *(&self->primary_samples->rotation_scalar_98 + i_1) = 0
00420358        *(&self->primary_samples->rotation_scalar_94 + i_1) = 0
00420362        *(&self->primary_samples->special_scalar + i_1) = 0
0042036e        *(&self->primary_samples->lateral_scale + i_1) = 0x3f800000
0042037e        set_matrix_identity(i_1 + self->primary_samples)
00420386        void* eax_16 = self->primary_samples + i_1
0042038e        *(eax_16 + 0x30) = *(eax_16 + 0x90)
0042039b        *(&self->primary_samples->transform.position.y + i_1) = 0x3efae148
004203a3        long double x87_r7_9 = float.t(ebx_1 + 4)
004203b1        *(&self->primary_samples->transform.position.z + i_1) = fconvert.s(x87_r7_9 * fconvert.t(self->width_or_scale))
004203ba        set_matrix_identity(self->secondary_samples + i_1)
004203d6        *(&self->secondary_samples->transform.position + i_1) = *(&self->primary_samples->center_x + i_1)
004203dd        *(&self->secondary_samples->transform.position.y + i_1) = 0x3efae148
004203eb        *(&self->secondary_samples->transform.position.z + i_1) = fconvert.s(fconvert.t(fconvert.s(x87_r7_9)) * fconvert.t(self->width_or_scale))
004203eb        top_1 = 0
004203ef        if (i_1 s<= 0x2a0)
00420590        set_matrix_rotation_identity(i_1 + self->primary_samples - 0xa8)
0042059f        set_matrix_rotation_identity(self->secondary_samples + i_1 - 0xa8)
0042040c        int32_t* edx_17 = i_1 + self->primary_samples - 0x98
0042041f        *edx_17 = 0
00420425        edx_17[1] = 0x3f800000
00420428        edx_17[2] = 0
0042042b        struct PathTemplateSample* primary_samples = self->primary_samples
0042044f        float var_50_1 = fconvert.s(fconvert.t(*(&primary_samples->transform.position.y + i_1)) - fconvert.t(*(i_1 + primary_samples - 0x74)))
00420459        long double x87_r7_18 = fconvert.t(*(&primary_samples->transform.position.z + i_1)) - fconvert.t(*(i_1 + primary_samples - 0x70))
00420460        *(i_1 + primary_samples - 0x88) = fconvert.s(fconvert.t(*(&primary_samples->transform.position + i_1)) - fconvert.t(*(i_1 + primary_samples - 0x78)))
00420462        *(i_1 + primary_samples - 0x84) = var_50_1
0042046d        *(i_1 + primary_samples - 0x80) = fconvert.s(x87_r7_18)
0042047a        normalize_vector(i_1 + self->primary_samples - 0x88)
00420484        void* eax_23 = i_1 + self->primary_samples
0042049b        cross_vectors(eax_23 - 0xa8, eax_23 - 0x98, eax_23 - 0x88)
004204a3        void* eax_24 = i_1 + self->primary_samples
004204ba        cross_vectors(eax_24 - 0x98, eax_24 - 0x88, eax_24 - 0xa8)
004204d6        int32_t* ecx_35 = self->secondary_samples + i_1 - 0x98
004204e9        *ecx_35 = 0
004204ef        ecx_35[1] = 0x3f800000
004204f2        ecx_35[2] = 0
004204f8        void* eax_27 = self->secondary_samples + i_1
00420516        float var_38_1 = fconvert.s(fconvert.t(*(eax_27 + 0x34)) - fconvert.t(*(eax_27 - 0x74)))
00420520        long double x87_r7_26 = fconvert.t(*(eax_27 + 0x38)) - fconvert.t(*(eax_27 - 0x70))
00420527        *(eax_27 - 0x88) = fconvert.s(fconvert.t(*(eax_27 + 0x30)) - fconvert.t(*(eax_27 - 0x78)))
00420529        *(eax_27 - 0x84) = var_38_1
00420534        *(eax_27 - 0x80) = fconvert.s(x87_r7_26)
00420541        normalize_vector(self->secondary_samples + i_1 - 0x88)
00420549        void* eax_30 = self->secondary_samples + i_1
0042054b        top_1 = 0
00420561        cross_vectors(eax_30 - 0xa8, eax_30 - 0x98, eax_30 - 0x88)
00420569        void* eax_32 = self->secondary_samples + i_1
0042057f        cross_vectors(eax_32 - 0x98, eax_32 - 0x88, eax_32 - 0xa8)
004205a4        i_1 += 0xa8
004205aa        ebx_1 += 1
004205ba        int32_t i_2 = 0
004205bf        if (self->segment_count - 1 s> 0)
004205c5        void* edi_1 = nullptr
004205ca        void* eax_35 = self->primary_samples + edi_1
004205e8        float var_38_2 = fconvert.s(fconvert.t(*(eax_35 + 0xdc)) - fconvert.t(*(eax_35 + 0x34)))
004205ef        long double x87_r7_34 = fconvert.t(*(eax_35 + 0xe0)) - fconvert.t(*(eax_35 + 0x38))
004205f6        *(eax_35 + 0x80) = fconvert.s(fconvert.t(*(eax_35 + 0xd8)) - fconvert.t(*(eax_35 + 0x30)))
004205f8        *(eax_35 + 0x84) = var_38_2
00420603        *(eax_35 + 0x88) = fconvert.s(x87_r7_34)
00420618        *(&self->primary_samples->delta_length + edi_1) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_1))
0042061f        struct PathTemplateSample* secondary_samples = self->secondary_samples
00420643        float var_44_1 = fconvert.s(fconvert.t(*(edi_1 + secondary_samples + 0xdc)) - fconvert.t(*(&secondary_samples->transform.position.y + edi_1)))
0042064a        long double x87_r7_41 = fconvert.t(*(edi_1 + secondary_samples + 0xe0)) - fconvert.t(*(&secondary_samples->transform.position.z + edi_1))
00420651        *(&secondary_samples->delta_dir_to_next + edi_1) = fconvert.s(fconvert.t(*(edi_1 + secondary_samples + 0xd8)) - fconvert.t(*(&secondary_samples->transform.position + edi_1)))
00420653        *(&secondary_samples->delta_dir_to_next.y + edi_1) = var_44_1
0042065e        *(&secondary_samples->delta_dir_to_next.z + edi_1) = fconvert.s(x87_r7_41)
00420673        i_2 += 1
00420674        *(&self->secondary_samples->delta_length + edi_1) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_1))
00420674        top_1 = 0
0042067e        edi_1 += 0xa8
00420687        do while (i_2 s< self->segment_count - 1)
004206b7        int32_t* edx_35 = &self->primary_samples[self->segment_count] - 0x28
004206cb        *edx_35 = 0
004206e1        edx_35[1] = 0
004206e4        edx_35[2] = 0x3f800000
004206fc        *(&self->primary_samples[self->segment_count] - 0x1c) = self->width_or_scale
00420712        int32_t* eax_49 = &self->secondary_samples[self->segment_count] - 0x28
0042071e        *eax_49 = 0
00420724        eax_49[1] = 0
00420727        eax_49[2] = 0x3f800000
0042073f        *(&self->secondary_samples[self->segment_count] - 0x1c) = self->width_or_scale
00420743        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
00420749        enum PathTemplateStripMeshFlags edx_39
00420749        edx_39.b = strip_mesh->flags.b | 0x80
0042074c        strip_mesh->flags = edx_39
0042075b        request_object_vertices(self->strip_mesh, (self->segment_count + 1) * self->width_cells)
0042076d        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
00420775        request_object_vertex_colours(self->strip_mesh)
0042077a        struct PathTemplateStripMesh* strip_mesh_1 = self->strip_mesh
0042077d        int32_t edi_2 = 0
0042077f        int32_t var_80_1 = 0
0042078c        strip_mesh_1->flags |= PATH_TEMPLATE_STRIP_MESH_FLAG_HAS_VERTEX_COLOURS
0042078f        struct PathTemplateStripMesh* strip_mesh_2 = self->strip_mesh
00420792        struct Vec3* vertices = strip_mesh_2->vertices
00420795        struct ObjectFaceQuad* facequads = strip_mesh_2->facequads
00420798        struct Color4f* vertex_colours = strip_mesh_2->vertex_colours
0042079b        uint32_t segment_count = self->segment_count
004207a8        uint32_t segment_count_2 = segment_count
004207ac        if (segment_count s>= 0)
004207b2        int32_t var_7c_1 = 0
004207ba        while (true)
004207ba        unimplemented  {fild st0, dword [esp+0x10]}
004207be        uint32_t width_cells = self->width_cells
004207c1        int32_t var_78_1 = 0
004207c7        unimplemented  {fmul st0, dword [0x4972a0]}
004207cd        unimplemented  {fidiv st0, dword [esp+0x1c]}
004207d1        uint32_t width_cells_1 = width_cells
004207d5        float var_6c_2 = fconvert.s(unimplemented  {fstp dword [esp+0x24], st0})
004207d5        unimplemented  {fstp dword [esp+0x24], st0}
004207d9        if (width_cells s> 0)
004207e2        float r
004207e2        float g
004207e2        float b
004207e2        float a
004207e2        int16_t top_46
004207e2        if (edi_2 s>= self->segment_count)
00420983        a = 0f
0042098f        b = 0f
00420991        g = 0f
00420999        r = 0f
0042099b        int32_t* eax_64 = &vertices[(edi_2 - 1) * width_cells + i_3]
0042099e        int32_t* edx_49 = &vertices[width_cells * edi_2 + i_3]
004209a3        *edx_49 = *eax_64
004209a8        edx_49[1] = eax_64[1]
004209ae        edx_49[2] = eax_64[2]
004209bc        unimplemented  {fld st0, dword [ebx+ecx*4+0x8]}
004209c0        unimplemented  {fadd dword [esi+0x50]}
004209c7        vertices[self->width_cells * edi_2 + i_3].z = fconvert.s(unimplemented  {fstp dword [eax], st0})
004209c7        unimplemented  {fstp dword [eax], st0}
004209c7        top_46 = top_1
004207f1        int32_t var_94_7 = var_7c_1
004207f2        unimplemented  {fld st0, dword [eax+0x9c]}
004207f8        unimplemented  {fmul st0, dword [0x497210]}
004207fe        float var_80_2 = fconvert.s(unimplemented  {fst dword [esp+0x14], st0})
00420802        unimplemented  {fmul st0, dword [eax+0x10]}
00420805        float var_3c_3 = fconvert.s(unimplemented  {fstp dword [esp+0x58], st0})
00420805        unimplemented  {fstp dword [esp+0x58], st0}
00420809        unimplemented  {fld st0, dword [esp+0x14]}
0042080d        unimplemented  {fmul st0, dword [eax+0x14]}
00420810        float var_38_3 = fconvert.s(unimplemented  {fstp dword [esp+0x5c], st0})
00420810        unimplemented  {fstp dword [esp+0x5c], st0}
00420814        unimplemented  {fld st0, dword [esp+0x14]}
00420818        unimplemented  {fmul st0, dword [eax+0x18]}
0042081b        float var_34_3 = fconvert.s(unimplemented  {fstp dword [esp+0x60], st0})
0042081b        unimplemented  {fstp dword [esp+0x60], st0}
0042081f        unimplemented  {fild st0, dword [esp+0x1c]}
00420823        float var_78_2 = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
00420823        unimplemented  {fstp dword [esp+0x1c], st0}
00420827        unimplemented  {fild st0, dword [esp+0x20]}
0042082b        unimplemented  {fdivr st0, dword [esp+0x1c]}
0042082f        unimplemented  {fmul st0, dword [0x4972a0]}
00420835        float var_94_8 = fconvert.s(unimplemented  {fstp dword [esp], st0})
00420835        unimplemented  {fstp dword [esp], st0}
00420838        cosine(var_94_8)
00420838        unimplemented  {call 0x44c980}
0042083d        unimplemented  {fld st0, dword [esp+0x58]}
00420841        unimplemented  {fmul st0, st1}
0042084c        float var_54_2 = fconvert.s(unimplemented  {fstp dword [esp+0x40], st0})
0042084c        unimplemented  {fstp dword [esp+0x40], st0}
00420850        unimplemented  {fld st0, dword [esp+0x5c]}
00420854        unimplemented  {fmul st0, st1}
00420856        float var_50_2 = fconvert.s(unimplemented  {fstp dword [esp+0x44], st0})
00420856        unimplemented  {fstp dword [esp+0x44], st0}
0042085a        unimplemented  {fld st0, dword [esp+0x60]}
0042085e        unimplemented  {fmul st0, st1}
00420860        float var_4c_2 = fconvert.s(unimplemented  {fstp dword [esp+0x48], st0})
00420860        unimplemented  {fstp dword [esp+0x48], st0}
00420864        unimplemented  {fstp st0, st0}
00420864        unimplemented  {fstp st0, st0}
00420866        unimplemented  {fld st0, dword [esp+0x14]}
0042086a        unimplemented  {fmul st0, dword [eax]}
0042086c        float var_48_2 = fconvert.s(unimplemented  {fstp dword [esp+0x4c], st0})
0042086c        unimplemented  {fstp dword [esp+0x4c], st0}
00420870        unimplemented  {fld st0, dword [esp+0x14]}
00420874        unimplemented  {fmul st0, dword [eax+0x4]}
00420877        float var_44_2 = fconvert.s(unimplemented  {fstp dword [esp+0x50], st0})
00420877        unimplemented  {fstp dword [esp+0x50], st0}
0042087b        unimplemented  {fld st0, dword [esp+0x14]}
0042087f        unimplemented  {fmul st0, dword [eax+0x8]}
00420882        float var_40_2 = fconvert.s(unimplemented  {fstp dword [esp+0x54], st0})
00420882        unimplemented  {fstp dword [esp+0x54], st0}
00420886        unimplemented  {fild st0, dword [esi+0x54]}
00420889        unimplemented  {fdivr st0, dword [esp+0x1c]}
0042088d        unimplemented  {fmul st0, dword [0x4972a0]}
00420893        float var_94_9 = fconvert.s(unimplemented  {fstp dword [esp], st0})
00420893        unimplemented  {fstp dword [esp], st0}
00420896        sine(var_94_9)
00420896        unimplemented  {call 0x44c9d0}
0042089b        unimplemented  {fld st0, dword [esp+0x4c]}
0042089f        unimplemented  {fmul st0, st1}
004208ac        float var_30_1 = fconvert.s(unimplemented  {fstp dword [esp+0x64], st0})
004208ac        unimplemented  {fstp dword [esp+0x64], st0}
004208b0        unimplemented  {fld st0, dword [esp+0x50]}
004208b4        unimplemented  {fmul st0, st1}
004208b6        float var_2c_1 = fconvert.s(unimplemented  {fstp dword [esp+0x68], st0})
004208b6        unimplemented  {fstp dword [esp+0x68], st0}
004208ba        unimplemented  {fmul st0, dword [esp+0x54]}
004208be        unimplemented  {fld st0, dword [esp+0x64]}
004208c2        unimplemented  {fadd dword [eax]}
004208c4        unimplemented  {fld st0, dword [esp+0x68]}
004208c8        unimplemented  {fadd dword [eax+0x4]}
004208cb        float var_20_1 = fconvert.s(unimplemented  {fstp dword [esp+0x74], st0})
004208cb        unimplemented  {fstp dword [esp+0x74], st0}
004208cf        unimplemented  {fxch st0, st1}
004208cf        unimplemented  {fxch st0, st1}
004208d1        unimplemented  {fadd dword [eax+0x8]}
004208d8        float var_14_1 = var_20_1
004208df        float var_1c_1 = fconvert.s(unimplemented  {fstp dword [esp+0x78], st0})
004208df        unimplemented  {fstp dword [esp+0x78], st0}
004208e7        unimplemented  {fadd dword [esp+0x40]}
004208eb        unimplemented  {fld st0, dword [esp+0x80]}
004208f2        unimplemented  {fadd dword [esp+0x44]}
004208f6        float var_10_1 = var_1c_1
004208fd        float var_8_1 = fconvert.s(unimplemented  {fstp dword [esp+0x8c], st0})
004208fd        unimplemented  {fstp dword [esp+0x8c], st0}
00420904        unimplemented  {fld st0, dword [esp+0x84]}
0042090b        unimplemented  {fadd dword [esp+0x48]}
0042090f        float var_4_1 = fconvert.s(unimplemented  {fstp dword [esp+0x90], st0})
0042090f        unimplemented  {fstp dword [esp+0x90], st0}
00420916        float var_60_1 = fconvert.s(unimplemented  {fstp dword [esp+0x34], st0})
00420916        unimplemented  {fstp dword [esp+0x34], st0}
00420932        unimplemented  {fld st0, dword [esp+0x28]}
00420936        unimplemented  {fadd st0, st0}
00420938        float var_94_10 = fconvert.s(unimplemented  {fstp dword [esp], st0})
00420938        unimplemented  {fstp dword [esp], st0}
00420948        float* eax_60 = &vertices[self->width_cells * edi_2 + i_3]
0042094f        *eax_60 = var_60_1
00420955        eax_60[1] = var_8_1
00420958        eax_60[2] = var_4_1
0042095b        cosine(var_94_10)
0042095b        unimplemented  {call 0x44c980}
00420960        unimplemented  {fmul st0, dword [0x497228]}
00420966        unimplemented  {fsubr st0, dword [0x497228]}
0042096c        a = fconvert.s(unimplemented  {fstp dword [esp], st0})
0042096c        unimplemented  {fstp dword [esp], st0}
0042096c        int16_t top_34
0042096c        top_46 = top_34 + 2
0042096f        b = 1f
00420974        g = 1f
00420979        r = 1f
004209da        store_color4f(&vertex_colours[self->width_cells * edi_2 + i_3], r, g, b, a)
004209ea        unimplemented  {fld st0, dword [ebx+edx*4+0x4]}
004209ee        long double temp2_1 = fconvert.t(0f)
004209ee        unimplemented  {fcomp st0, dword [0x497234]} f- temp2_1
004209ee        bool c0_1 = unimplemented  {fcomp st0, dword [0x497234]} f< temp2_1
004209ee        bool c2_1 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp2_1)
004209ee        bool c3_1 = unimplemented  {fcomp st0, dword [0x497234]} f== temp2_1
004209ee        unimplemented  {fcomp st0, dword [0x497234]}
004209ee        top_1 = top_46 - 1
004209f8        int32_t eax_73
004209f8        eax_73.w = (c0_1 ? 1 : 0) << 8 | (c2_1 ? 1 : 0) << 0xa | (c3_1 ? 1 : 0) << 0xe | (top_1 & 7) << 0xb
004209fd        if ((eax_73:1.b & 1) != 0)
004209ff        unimplemented  {fld st0, dword [ecx]}
00420a01        unimplemented  {fmul st0, dword [0x4973d8]}
00420a07        vertices[self->width_cells * edi_2 + i_3].y = fconvert.s(unimplemented  {fstp dword [ecx], st0})
00420a07        unimplemented  {fstp dword [ecx], st0}
00420a09        width_cells = self->width_cells
00420a0c        i_3 += 1
00420a0f        int32_t i_5 = i_3
00420a13        uint32_t width_cells_2 = width_cells
00420a17        do while (i_3 s< width_cells)
00420a21        uint32_t segment_count_1 = self->segment_count
00420a24        edi_2 += 1
00420a2d        int32_t var_80_3 = edi_2
00420a31        var_7c_1 += 0xa8
00420a35        uint32_t segment_count_3 = segment_count_1
00420a39        if (edi_2 s> segment_count_1)
00420a39        break
004207b8        i_3 = 0
00420a3f        i_3 = 0
00420a44        int32_t var_80_4 = 0
00420a4a        if (self->segment_count s> 0)
00420a53        int32_t j = 0
00420a57        int32_t var_78_3 = 0
00420a5b        if (self->width_cells s> 0)
00420a61        unimplemented  {fild st0, dword [esp+0x10]}
00420a68        int32_t var_6c_3 = i_3 + 1
00420a6c        unimplemented  {fmul st0, dword [0x497428]}
00420a72        float var_80_5 = fconvert.s(unimplemented  {fstp dword [esp+0x10], st0})
00420a72        unimplemented  {fstp dword [esp+0x10], st0}
00420a76        unimplemented  {fild st0, dword [esp+0x24]}
00420a7a        unimplemented  {fmul st0, dword [0x497428]}
00420a80        float var_74 = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
00420a80        unimplemented  {fstp dword [esp+0x1c], st0}
00420a84        unimplemented  {fild st0, dword [esp+0x18]}
00420a88        int32_t j_3 = j + 1
00420a8b        int32_t edx_53 = 0
00420a8d        int32_t j_1 = j_3
00420a91        int32_t var_70_6 = 0
00420a95        float var_78_4 = fconvert.s(unimplemented  {fstp dword [esp+0x18], st0})
00420a95        unimplemented  {fstp dword [esp+0x18], st0}
00420a99        unimplemented  {fild st0, dword [esp+0x14]}
00420a9d        float var_64_1 = fconvert.s(unimplemented  {fstp dword [esp+0x2c], st0})
00420a9d        unimplemented  {fstp dword [esp+0x2c], st0}
00420ab7        while (true)
00420ac0        int16_t* edi_4 = facequads + (edx_53 + ((self->width_cells * i_3 + j) << 1)) * 0x30
00420ac4        *edi_4 = 0
00420ac9        if (edx_53 != 0)
00420b15        int32_t ecx_85
00420b15        ecx_85.w = i_3.w
00420b18        ecx_85.w *= self->width_cells.w
00420b22        edi_4[1] = (mods.dp.d(sx.q(j_3), self->width_cells)).w + ecx_85.w
00420b33        edi_4[2] = i_3.w * self->width_cells.w + j.w
00420b3e        edi_4[3] = (i_3.w + 1) * self->width_cells.w + j.w
00420b4c        self->width_cells
00420b51        edi_4[4] = (mods.dp.d(sx.q(j_1), self->width_cells)).w + (i_3.w + 1) * self->width_cells.w
00420acb        edx_53.w = i_3.w
00420ad1        edx_53.w *= self->width_cells.w
00420ad8        edi_4[1] = edx_53.w + j.w
00420aee        edi_4[2] = (mods.dp.d(sx.q(j_3), self->width_cells)).w + i_3.w * self->width_cells.w
00420b00        edi_4[3] = (mods.dp.d(sx.q(j_1), self->width_cells)).w + (i_3.w + 1) * self->width_cells.w
00420b0b        edi_4[4] = (i_3.w + 1) * self->width_cells.w + j.w
00420b60        char* texture_path_1
00420b60        if (((j.b ^ i_3.b) & 1) != 0)
00420b73        texture_path_1 = texture_path
00420b69        texture_path_1 = texture_path
00420b7e        *(edi_4 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
00420b85        unimplemented  {fild st0, dword [esi+0x54]}
00420b8a        float var_6c_4 = fconvert.s(unimplemented  {fstp dword [esp+0x24], st0})
00420b8a        unimplemented  {fstp dword [esp+0x24], st0}
00420b8e        unimplemented  {fld st0, dword [esp+0x18]}
00420b92        unimplemented  {fdiv st0, dword [esp+0x24]}
00420b96        unimplemented  {fld st0, dword [esp+0x2c]}
00420b9a        unimplemented  {fdiv st0, dword [esp+0x24]}
00420b9e        float var_6c_5 = fconvert.s(unimplemented  {fst dword [esp+0x24], st0})
00420ba2        if (var_70_6 != 0)
00420bcc        *(edi_4 + 0x10) = fconvert.s(unimplemented  {fstp dword [edi+0x10], st0})
00420bcc        unimplemented  {fstp dword [edi+0x10], st0}
00420bd3        *(edi_4 + 0x14) = var_80_5
00420bd8        *(edi_4 + 0x18) = fconvert.s(unimplemented  {fst dword [edi+0x18], st0})
00420bdf        *(edi_4 + 0x1c) = var_80_5
00420be2        *(edi_4 + 0x20) = fconvert.s(unimplemented  {fstp dword [edi+0x20], st0})
00420be2        unimplemented  {fstp dword [edi+0x20], st0}
00420be9        *(edi_4 + 0x24) = var_74
00420bec        *(edi_4 + 0x28) = var_6c_5
00420bef        *(edi_4 + 0x2c) = var_74
00420ba8        unimplemented  {fld st0, st1}
00420bac        *(edi_4 + 0x10) = fconvert.s(unimplemented  {fstp dword [edi+0x10], st0})
00420bac        unimplemented  {fstp dword [edi+0x10], st0}
00420baf        *(edi_4 + 0x14) = var_80_5
00420bb6        *(edi_4 + 0x18) = fconvert.s(unimplemented  {fst dword [edi+0x18], st0})
00420bb9        *(edi_4 + 0x1c) = var_80_5
00420bbe        *(edi_4 + 0x20) = fconvert.s(unimplemented  {fstp dword [edi+0x20], st0})
00420bbe        unimplemented  {fstp dword [edi+0x20], st0}
00420bc1        *(edi_4 + 0x24) = var_74
00420bc4        *(edi_4 + 0x28) = fconvert.s(unimplemented  {fstp dword [edi+0x28], st0})
00420bc4        unimplemented  {fstp dword [edi+0x28], st0}
00420bc7        *(edi_4 + 0x2c) = var_74
00420bf3        bool cond:11_1 = var_70_6 + 1 s< 2
00420bf6        var_70_6 += 1
00420bfa        if (not(cond:11_1))
00420bfa        break
00420aa3        edx_53 = var_70_6
00420aa7        j_3 = j_1
00420c00        j = j_1
00420c09        int32_t j_2 = j
00420c0d        do while (j s< self->width_cells)
00420c16        i_3 += 1
00420c19        int32_t i_4 = i_3
00420c1d        do while (i_3 s< self->segment_count)
00420c34        return finalize_path_template(self)
