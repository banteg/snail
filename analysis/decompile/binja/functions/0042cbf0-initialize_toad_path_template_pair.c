/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_toad_path_template_pair @ 0x42cbf0 */

0042cc01        self->kind = PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY
0042cc08        self->is_mirrored_x = 0
0042cc0c        self->side_exit_mode = 0
0042cc0f        self->width_cells = 4
0042cc16        struct PathTemplateSample* primary_samples_5
0042cc16        float var_50
0042cc16        int32_t var_4c
0042cc16        float var_48
0042cc16        struct PathTemplateSample* primary_samples_6
0042cc16        if (turn_left == 0)
0042cc3b        primary_samples_5 = 2
0042cc43        var_50 = 2f
0042cc4b        primary_samples_6 = 2
0042cc4f        var_48 = 1f
0042cc57        var_4c = 1
0042cc18        primary_samples_6 = 1
0042cc1d        var_50 = -2f
0042cc25        var_48 = -1f
0042cc2d        primary_samples_5 = 1
0042cc31        var_4c = 3
0042cc6a        self->width_or_scale = 1f
0042cc71        turn_left.d = var_4c + primary_samples_6 + 0x1a
0042cc75        self->segment_count = var_4c + primary_samples_6 + 0x1a
0042cc7c        self->segment_count_f = fconvert.s(float.t(turn_left.d))
0042cc7f        struct PathTemplateSample* primary_samples_1 = allocate_path_template_samples(self)
0042cc86        self->has_entry_mesh_transition = 0
0042cc8d        turn_left.d = 0
0042cc91        if (primary_samples_6 s> 0)
0042cc97        int32_t esi = 0
0042cd57        bool cond:2_1
0042cca0        *(&self->primary_samples->center_x + esi) = fconvert.s(fconvert.t(var_50))
0042ccaa        *(&self->primary_samples->rotation_scalar_98 + esi) = 0
0042ccb4        *(&self->primary_samples->rotation_scalar_94 + esi) = 0
0042ccbe        *(&self->primary_samples->special_scalar + esi) = 0
0042ccc8        *(&self->primary_samples->lateral_scale + esi) = 0x3f800000
0042ccd4        set_matrix_identity(self->primary_samples + esi)
0042ccdc        void* eax_4 = self->primary_samples + esi
0042ccde        long double x87_r7_2 = float.t(turn_left.d)
0042cce8        *(eax_4 + 0x30) = *(eax_4 + 0x90)
0042ccf2        *(&self->primary_samples->transform.position.y + esi) = 0
0042ccf9        *(&self->primary_samples->transform.position.z + esi) = fconvert.s(x87_r7_2)
0042cd00        *(&self->primary_samples->delta_length + esi) = 0x3f800000
0042cd0c        set_matrix_identity(self->secondary_samples + esi)
0042cd22        *(&self->secondary_samples->transform.position + esi) = *(&self->primary_samples->center_x + esi)
0042cd29        *(&self->secondary_samples->transform.position.y + esi) = 0x3efae148
0042cd34        *(&self->secondary_samples->transform.position.z + esi) = fconvert.s(fconvert.t(fconvert.s(x87_r7_2)))
0042cd40        *(&self->secondary_samples->delta_length + esi) = 0x3f800000
0042cd47        primary_samples_1 = primary_samples_5
0042cd4b        esi += 0xa8
0042cd51        cond:2_1 = turn_left.d + 1 s< primary_samples_1
0042cd53        turn_left.d += 1
0042cd57        do while (cond:2_1)
0042cd5d        primary_samples_6 = primary_samples_1
0042cd63        if (var_4c s> 0)
0042cd70        turn_left.d = &primary_samples_6->transform.basis_up.z + 2
0042cd85        int32_t esi_4 = (&primary_samples_6->transform.basis_up.z + 2) * 0xa8
0042cd95        *(&self->primary_samples->center_x + esi_4) = fconvert.s(fconvert.t(var_50))
0042cd9f        *(&self->primary_samples->rotation_scalar_98 + esi_4) = 0
0042cda9        *(&self->primary_samples->rotation_scalar_94 + esi_4) = 0
0042cdb3        *(&self->primary_samples->special_scalar + esi_4) = 0
0042cdbd        *(&self->primary_samples->lateral_scale + esi_4) = 0x3f800000
0042cdc9        set_matrix_identity(self->primary_samples + esi_4)
0042cdce        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042cdd1        long double x87_r7_5 = float.t(turn_left.d)
0042cde3        *(&primary_samples_2->transform.position + esi_4) = *(&primary_samples_2->center_x + esi_4)
0042cde9        *(&self->primary_samples->transform.position.y + esi_4) = 0
0042cdf0        *(&self->primary_samples->transform.position.z + esi_4) = fconvert.s(x87_r7_5)
0042cdf7        *(&self->primary_samples->delta_length + esi_4) = 0x3f800000
0042ce03        set_matrix_identity(self->secondary_samples + esi_4)
0042ce19        *(&self->secondary_samples->transform.position + esi_4) = *(&self->primary_samples->center_x + esi_4)
0042ce20        *(&self->secondary_samples->transform.position.y + esi_4) = 0x3efae148
0042ce2f        *(&self->secondary_samples->transform.position.z + esi_4) = fconvert.s(fconvert.t(fconvert.s(x87_r7_5)))
0042ce3a        *(&self->secondary_samples->delta_length + esi_4) = 0x3f800000
0042ce41        esi_4 += 0xa8
0042ce47        int32_t eax_19 = turn_left.d + 1
0042ce48        turn_left.d = eax_19
0042ce4c        primary_samples_1 = 0xffffffe6 - primary_samples_5 + eax_19
0042ce52        do while (primary_samples_1 s< var_4c)
0042ce58        primary_samples_6 = primary_samples_5
0042ce63        turn_left.d = 0
0042ce84        int32_t ebx_3 = primary_samples_6 * 0xa8
0042d02e        bool cond:3_1
0042ce8f        struct PathTemplateSample* primary_samples_4 = primary_samples_1
0042ceba        float angle = fconvert.s((fconvert.t(1f) - cosine(fconvert.s(float.t(turn_left.d) * fconvert.t(0.241660982f)))) * fconvert.t(0.5f) * fconvert.t(var_48) * fconvert.t(1.57079637f))
0042cec2        *(&self->primary_samples->center_x + ebx_3) = fconvert.s(fconvert.t(var_50))
0042cecc        *(&self->primary_samples->rotation_scalar_98 + ebx_3) = 0
0042ced6        *(&self->primary_samples->rotation_scalar_94 + ebx_3) = 0
0042cee0        *(&self->primary_samples->special_scalar + ebx_3) = 0
0042ceea        *(&self->primary_samples->lateral_scale + ebx_3) = 0x3f800000
0042cefa        set_matrix_identity(self->primary_samples + ebx_3)
0042cf04        long double st0_2 = sine(angle)
0042cf23        *(&self->primary_samples->transform.position + ebx_3) = fconvert.s(st0_2 + st0_2 + fconvert.t(var_50))
0042cf2e        *(&self->primary_samples->transform.position.z + ebx_3) = fconvert.s(float.t(turn_left.d + primary_samples_5))
0042cf35        *(&self->primary_samples->transform.position.y + ebx_3) = 0
0042cf40        int32_t* ecx_26 = &self->primary_samples->transform.basis_up + ebx_3
0042cf48        *ecx_26 = 0
0042cf4e        ecx_26[1] = 0x3f800000
0042cf51        ecx_26[2] = 0
0042cf57        void* eax_26 = self->primary_samples + ebx_3
0042cf73        float var_2c_1 = fconvert.s(fconvert.t(*(eax_26 + 0x34)) - fconvert.t(*(eax_26 - 0x74)))
0042cf7a        long double x87_r7_24 = fconvert.t(*(eax_26 + 0x38)) - fconvert.t(*(eax_26 - 0x70))
0042cf84        *(eax_26 + 0x20) = fconvert.s(fconvert.t(*(eax_26 + 0x30)) - fconvert.t(*(eax_26 - 0x78)))
0042cf86        *(eax_26 + 0x24) = var_2c_1
0042cf91        *(eax_26 + 0x28) = fconvert.s(x87_r7_24)
0042cf9b        normalize_vector(&self->primary_samples->transform.basis_forward + ebx_3)
0042cfa5        struct Vec3* primary_right = self->primary_samples + ebx_3
0042cfb0        cross_vectors(primary_right, primary_right + 0x10, primary_right + 0x20)
0042cfbb        rotate_matrix_local_z(self->primary_samples + ebx_3, angle)
0042cfcf        __builtin_memcpy(self->secondary_samples + ebx_3, self->primary_samples + ebx_3, 0x40)
0042cfd1        primary_samples_1 = self->primary_samples
0042cfdb        long double x87_r7_28 = fconvert.t(*(&primary_samples_1->transform.basis_up + ebx_3)) * fconvert.t(0.49000001f)
0042cfef        float var_20_1 = fconvert.s(fconvert.t(*(&primary_samples_1->transform.basis_up.y + ebx_3)) * fconvert.t(0.49000001f))
0042cff6        long double x87_r6_4 = fconvert.t(*(&primary_samples_1->transform.basis_up.z + ebx_3)) * fconvert.t(0.49000001f)
0042cffc        struct Vec3* secondary_position = &self->secondary_samples->transform.position + ebx_3
0042d000        ebx_3 += 0xa8
0042d00c        secondary_position->x = fconvert.s(x87_r7_28 + fconvert.t(secondary_position->x))
0042d015        secondary_position->y = fconvert.s(fconvert.t(var_20_1) + fconvert.t(secondary_position->y))
0042d01f        secondary_position->z = fconvert.s(fconvert.t(fconvert.s(x87_r6_4)) + fconvert.t(secondary_position->z))
0042d027        cond:3_1 = turn_left.d + 1 s< 0x1a
0042d02a        turn_left.d += 1
0042d02e        do while (cond:3_1)
0042d037        int32_t i = 0
0042d03c        if (self->segment_count - 1 s> 0)
0042d042        int32_t esi_8 = 0
0042d044        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042d068        float var_2c_2 = fconvert.s(fconvert.t(*(primary_samples_3 + esi_8 + 0xdc)) - fconvert.t(*(&primary_samples_3->transform.position.y + esi_8)))
0042d06f        long double x87_r7_39 = fconvert.t(*(primary_samples_3 + esi_8 + 0xe0)) - fconvert.t(*(&primary_samples_3->transform.position.z + esi_8))
0042d076        *(&primary_samples_3->delta_dir_to_next + esi_8) = fconvert.s(fconvert.t(*(primary_samples_3 + esi_8 + 0xd8)) - fconvert.t(*(&primary_samples_3->transform.position + esi_8)))
0042d078        *(&primary_samples_3->delta_dir_to_next.y + esi_8) = var_2c_2
0042d083        *(&primary_samples_3->delta_dir_to_next.z + esi_8) = fconvert.s(x87_r7_39)
0042d098        *(&self->primary_samples->delta_length + esi_8) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + esi_8))
0042d09f        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042d0c3        float var_38_1 = fconvert.s(fconvert.t(*(secondary_samples + esi_8 + 0xdc)) - fconvert.t(*(&secondary_samples->transform.position.y + esi_8)))
0042d0ca        long double x87_r7_46 = fconvert.t(*(secondary_samples + esi_8 + 0xe0)) - fconvert.t(*(&secondary_samples->transform.position.z + esi_8))
0042d0d1        *(&secondary_samples->delta_dir_to_next + esi_8) = fconvert.s(fconvert.t(*(secondary_samples + esi_8 + 0xd8)) - fconvert.t(*(&secondary_samples->transform.position + esi_8)))
0042d0d3        *(&secondary_samples->delta_dir_to_next.y + esi_8) = var_38_1
0042d0de        *(&secondary_samples->delta_dir_to_next.z + esi_8) = fconvert.s(x87_r7_46)
0042d0f3        i += 1
0042d0f4        *(&self->secondary_samples->delta_length + esi_8) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + esi_8))
0042d0fe        esi_8 += 0xa8
0042d107        do while (i s< self->segment_count - 1)
0042d137        struct Vec3* primary_terminal_delta = &self->primary_samples[self->segment_count] - 0x28
0042d14b        primary_terminal_delta->x = 0
0042d159        primary_terminal_delta->y = 0f
0042d15c        primary_terminal_delta->z = 1f
0042d16e        int32_t var_28_3 = 0x3f800000
0042d17a        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042d190        struct Vec3* secondary_terminal_delta = &self->secondary_samples[self->segment_count] - 0x28
0042d198        secondary_terminal_delta->x = 0
0042d19e        secondary_terminal_delta->y = 0f
0042d1a3        secondary_terminal_delta->z = 1f
0042d1b8        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042d1cb        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0042d1dd        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0042d1e2        struct Object* object = self->bod.object
0042d1e5        struct ObjectFaceQuad* facequads = object->facequads
0042d1e8        struct Vec3* vertices = object->vertices
0042d1f2        int32_t i_1 = 0
0042d1f4        struct Vec3* vertices_1 = vertices
0042d1fa        if (self->segment_count s>= 0)
0042d200        int32_t ebx_4 = 0
0042d202        uint32_t width_cells = self->width_cells
0042d205        int32_t esi_9 = 0
0042d209        turn_left.d = 0
0042d20d        uint32_t width_cells_1 = width_cells
0042d211        if (width_cells s>= 0)
0042d224        struct PathTemplateSample* primary_samples = self->primary_samples
0042d22d        long double x87_r7_49 = float.t(turn_left.d) - float.t(width_cells_1) * fconvert.t(0.5f)
0042d22f        struct Vec3* vertex
0042d22f        float ecx_55
0042d22f        if (i_1 == self->segment_count)
0042d285        void* eax_60 = primary_samples + ebx_4
0042d296        vertices = vertices_1
0042d2db        float var_38_2 = fconvert.s(fconvert.t(*(eax_60 - 0x74)) + fconvert.t(fconvert.s(x87_r7_49 * fconvert.t(*(eax_60 - 0xa4)))))
0042d2e3        long double x87_r6_24 = fconvert.t(fconvert.s(fconvert.t(*(eax_60 - 0x70)) + fconvert.t(1f))) + x87_r7_49 * fconvert.t(*(eax_60 - 0xa0))
0042d2e5        vertex = &vertices[(width_cells + 1) * i_1 + esi_9]
0042d2ec        vertex->x = fconvert.s(fconvert.t(*(eax_60 - 0x78)) + fconvert.t(fconvert.s(x87_r7_49 * fconvert.t(*(eax_60 - 0xa8)))))
0042d2f6        vertex->y = var_38_2
0042d2f9        ecx_55 = fconvert.s(x87_r6_24)
0042d231        struct PathTemplateSample* primary_mesh_sample = primary_samples + ebx_4
0042d259        float var_2c_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_49 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
0042d266        float var_28_4 = fconvert.s(x87_r7_49 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
0042d26f        vertex = &vertices[(width_cells + 1) * i_1 + esi_9]
0042d276        vertex->x = fconvert.s(fconvert.t(fconvert.s(x87_r7_49 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
0042d27c        vertex->y = var_2c_3
0042d27f        ecx_55 = var_28_4
0042d2ff        vertex->z = ecx_55
0042d302        width_cells = self->width_cells
0042d305        esi_9 += 1
0042d306        width_cells_1 = width_cells
0042d30c        turn_left.d = esi_9
0042d310        do while (esi_9 s<= width_cells)
0042d319        i_1 += 1
0042d31a        ebx_4 += 0xa8
0042d322        do while (i_1 s<= self->segment_count)
0042d32b        int32_t i_2 = 0
0042d32f        if (self->segment_count s> 0)
0042d338        int32_t j = 0
0042d33c        turn_left.d = 0
0042d340        if (self->width_cells s> 0)
0042d348        int32_t eax_68 = i_2 & 0x80000007
0042d34d        if (eax_68 s< 0)
0042d353        eax_68 = ((eax_68 - 1) | 0xfffffff8) + 1
0042d367        float var_4c_1 = fconvert.s(float.t(eax_68) * fconvert.t(0.125f))
0042d375        float var_54 = fconvert.s(float.t(eax_68 + 1) * fconvert.t(0.125f))
0042d380        int32_t ecx_59 = 0
0042d386        int32_t var_48_1 = 0
0042d390        turn_left.d = fconvert.s(float.t(turn_left.d) * fconvert.t(0.125f))
0042d39e        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042d3b2        while (true)
0042d3b2        int32_t eax_75 = ecx_59 + ((self->width_cells * i_2 + j) << 1)
0042d3b5        if (ecx_59 != 0)
0042d470        struct ObjectFaceQuad* facequads_1 = facequads
0042d47b        struct ObjectFaceQuad* face_second = &facequads_1[eax_75]
0042d47e        __builtin_memset(face_second, 0, 2)
0042d483        ecx_59.w = self->width_cells.w
0042d487        ecx_59.w += 1
0042d490        face_second->vertex_0 = ecx_59.w * i_2.w + j.w + 1
0042d494        facequads_1.w = self->width_cells.w
0042d498        facequads_1.w += 1
0042d49f        face_second->vertex_1 = facequads_1.w * i_2.w + j.w
0042d4b1        face_second->vertex_2 = (self->width_cells.w + 1) * (i_2.w + 1) + j.w
0042d4c9        face_second->vertex_3 = (self->width_cells.w + 1) * (i_2.w + 1) + j.w + 1
0042d4cd        char* texture_path_1
0042d4cd        if (((j.b ^ i_2.b) & 1) != 0)
0042d55d        texture_path_1 = texture_b
0042d4d7        texture_path_1 = texture_b
0042d4e6        int32_t edx_42 = turn_left.d
0042d4ea        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
0042d4f1        face_second->uv[0].u = var_50_1
0042d4f4        face_second->uv[0].v = var_4c_1
0042d4f9        face_second->uv[1].u = edx_42
0042d502        face_second->uv[1].v = var_4c_1
0042d509        face_second->uv[2].u = edx_42
0042d50c        face_second->uv[2].v = var_54
0042d511        face_second->uv[3].u = var_50_1
0042d514        face_second->uv[3].v = var_54
0042d3c2        int32_t ecx_61 = eax_75 * 0x30
0042d3c9        struct ObjectFaceQuad* face_first = ecx_61 + facequads
0042d3cc        __builtin_memset(face_first, 0, 2)
0042d3d1        eax_75.w = self->width_cells.w
0042d3d5        eax_75.w += 1
0042d3dc        face_first->vertex_0 = eax_75.w * i_2.w + j.w
0042d3e0        ecx_61.w = self->width_cells.w
0042d3e4        ecx_61.w += 1
0042d3f0        face_first->vertex_1 = ecx_61.w * i_2.w + j.w + 1
0042d401        face_first->vertex_2 = (self->width_cells.w + 1) * (i_2.w + 1) + j.w + 1
0042d417        face_first->vertex_3 = (self->width_cells.w + 1) * (i_2.w + 1) + j.w
0042d41b        char* texture_path
0042d41b        if (((j.b ^ i_2.b) & 1) != 0)
0042d46a        texture_path = texture_a
0042d421        texture_path = texture_a
0042d434        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0042d43b        face_first->uv[0].u = turn_left.d
0042d43e        face_first->uv[0].v = var_4c_1
0042d443        face_first->uv[1].u = var_50_1
0042d44c        face_first->uv[1].v = var_4c_1
0042d453        face_first->uv[2].u = var_50_1
0042d456        face_first->uv[2].v = var_54
0042d45b        face_first->uv[3].u = turn_left.d
0042d45e        face_first->uv[3].v = var_54
0042d51c        bool cond:12_1 = var_48_1 + 1 s< 2
0042d51f        var_48_1 += 1
0042d523        if (not(cond:12_1))
0042d523        break
0042d3a4        ecx_59 = var_48_1
0042d529        j += 1
0042d532        turn_left.d = j
0042d536        do while (j s< self->width_cells)
0042d53f        i_2 += 1
0042d542        do while (i_2 s< self->segment_count)
0042d54a        finalize_path_template(self)
0042d556        return
