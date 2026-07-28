/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_supertramp_path_template_pair @ 0x423f10 */

00423f29        self->kind = PATH_TEMPLATE_KIND_SUPERTRAMP
00423f30        self->is_mirrored_x = 0
00423f34        self->side_exit_mode = 0
00423f37        self->width_cells = width_cells_
00423f3f        int16_t x87control
00423f3f        int32_t curve_count = ftol(x87control, fconvert.t(length) * fconvert.t(1.04615045f))
00423f56        self->width_or_scale = 1f
00423f59        self->segment_count = curve_count + 8
00423f5c        self->segment_count_f = fconvert.s(float.t(curve_count + 7))
00423f5f        long double x87_r7_3 = float.t(curve_count)
00423f6d        float curve_radius = fconvert.s(x87_r7_3 * fconvert.t(0.95588547f))
00423f71        get_path_nodes(self)
00423f76        uint32_t segment_count = self->segment_count
00423f79        self->has_entry_mesh_transition = 0
00423f81        int32_t lead_sample_index = 0
00423f85        self->segment_count = segment_count - 1
00423f88        int32_t lead_sample_offset = 0
00424045        while (lead_sample_offset s< 0x498)
00423f8d        *(&self->primary_samples->center_x + lead_sample_offset) = 0
00423f97        *(&self->primary_samples->rotation_scalar_98 + lead_sample_offset) = 0
00423fa1        *(&self->primary_samples->rotation_scalar_94 + lead_sample_offset) = 0
00423fab        *(&self->primary_samples->special_scalar + lead_sample_offset) = 0
00423fb7        *(&self->primary_samples->lateral_scale + lead_sample_offset) = 0x3f800000
00423fc3        set_matrix_identity(lead_sample_offset + self->primary_samples)
00423fcb        struct PathTemplateSample* primary_seed_sample = self->primary_samples + lead_sample_offset
00423fcd        long double x87_r7_5 = float.t(lead_sample_index)
00423fd7        primary_seed_sample->transform.position.x = primary_seed_sample->center_x
00423fe1        *(&self->primary_samples->transform.position.y + lead_sample_offset) = 0
00423fe8        *(&self->primary_samples->transform.position.z + lead_sample_offset) = fconvert.s(x87_r7_5)
00423fef        *(&self->primary_samples->delta_length + lead_sample_offset) = 0x3f800000
00423ffd        set_matrix_identity(lead_sample_offset + self->secondary_samples)
00424013        *(&self->secondary_samples->transform.position + lead_sample_offset) = *(&self->primary_samples->center_x + lead_sample_offset)
0042401a        *(&self->secondary_samples->transform.position.y + lead_sample_offset) = 0x3efae148
00424029        *(&self->secondary_samples->transform.position.z + lead_sample_offset) = fconvert.s(fconvert.t(fconvert.s(x87_r7_5)))
00424030        lead_sample_offset += 0xa8
0042403d        *(lead_sample_offset + self->secondary_samples - 0x1c) = 0x3f800000
00424041        lead_sample_index += 1
0042404f        int32_t curve_index = 0
00424055        if (curve_count s>= 0)
00424095        float secondary_radius = fconvert.s(fconvert.t(curve_radius) - fconvert.t(0.49000001f))
00424099        int32_t curve_sample_offset = 0x498
00424264        bool cond:1_1
004240b2        *(&self->primary_samples->center_x + curve_sample_offset) = 0
004240c0        *(&self->primary_samples->rotation_scalar_98 + curve_sample_offset) = 0
004240ca        *(&self->primary_samples->rotation_scalar_94 + curve_sample_offset) = 0
004240d6        *(&self->primary_samples->special_scalar + curve_sample_offset) = 0
004240e0        *(&self->primary_samples->lateral_scale + curve_sample_offset) = 0x3f800000
004240ec        float curve_phase = fconvert.s(float.t(curve_index) * fconvert.t(1.04615045f) / fconvert.t(fconvert.s(x87_r7_3)))
004240f0        set_matrix_identity(curve_sample_offset + self->primary_samples)
004240f5        struct PathTemplateSample* primary_samples = self->primary_samples
00424107        *(&primary_samples->transform.position + curve_sample_offset) = *(&primary_samples->center_x + curve_sample_offset)
0042411d        *(&self->primary_samples->transform.position.z + curve_sample_offset) = fconvert.s(sine(curve_phase) * fconvert.t(curve_radius) + fconvert.t(7f))
00424134        *(&self->primary_samples->transform.position.y + curve_sample_offset) = fconvert.s(fconvert.t(curve_radius) - cosine(curve_phase) * fconvert.t(curve_radius))
0042413f        set_matrix_identity(curve_sample_offset + self->secondary_samples)
00424152        *(&self->secondary_samples->transform.position + curve_sample_offset) = *(&self->primary_samples->center_x + curve_sample_offset)
00424169        *(&self->secondary_samples->transform.position.z + curve_sample_offset) = fconvert.s(sine(curve_phase) * fconvert.t(secondary_radius) + fconvert.t(7f))
00424186        *(&self->secondary_samples->transform.position.y + curve_sample_offset) = fconvert.s(fconvert.t(curve_radius) - cosine(curve_phase) * fconvert.t(secondary_radius))
004241a0        *(curve_sample_offset + self->primary_samples) = struct Vec3 {
    .x = 0x3f800000
    .y = 0f
    .z = 0f
}
004241a6        *(&self->primary_samples->transform.basis_up + curve_sample_offset) = 0
004241aa        struct PathTemplateSample* primary_samples_1 = self->primary_samples
004241b4        *(&primary_samples_1->transform.basis_up.y + curve_sample_offset) = fconvert.s(fconvert.t(curve_radius) - fconvert.t(*(&primary_samples_1->transform.position.y + curve_sample_offset)))
004241b7        struct PathTemplateSample* primary_samples_2 = self->primary_samples
004241c7        *(&primary_samples_2->transform.basis_up.z + curve_sample_offset) = fconvert.s(fconvert.t(7f) - fconvert.t(*(&primary_samples_2->transform.position.z + curve_sample_offset)))
004241d1        normalize_vector(&self->primary_samples->transform.basis_up + curve_sample_offset)
004241db        struct Vec3* lhs = curve_sample_offset + self->primary_samples
004241e6        cross_vectors(lhs + 0x20, lhs, lhs + 0x10)
00424207        *(curve_sample_offset + self->secondary_samples) = struct Vec3 {
    .x = 0x3f800000
    .y = 0f
    .z = 0f
}
0042420d        *(&self->secondary_samples->transform.basis_up + curve_sample_offset) = 0
00424214        struct PathTemplateSample* secondary_curve_sample = self->secondary_samples + curve_sample_offset
00424219        secondary_curve_sample->transform.basis_up.y = fconvert.s(fconvert.t(curve_radius) - fconvert.t(secondary_curve_sample->transform.position.y))
0042421c        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042422c        *(&secondary_samples->transform.basis_up.z + curve_sample_offset) = fconvert.s(fconvert.t(7f) - fconvert.t(*(&secondary_samples->transform.position.z + curve_sample_offset)))
00424236        normalize_vector(&self->secondary_samples->transform.basis_up + curve_sample_offset)
0042423e        struct Vec3* lhs_1 = self->secondary_samples + curve_sample_offset
0042424a        cross_vectors(lhs_1 + 0x20, lhs_1, lhs_1 + 0x10)
00424258        curve_sample_offset += 0xa8
0042425e        cond:1_1 = curve_index + 1 s<= curve_count
00424260        curve_index += 1
00424264        do while (cond:1_1)
0042426d        int32_t delta_index = 0
00424271        if (self->segment_count s> 0)
00424277        int32_t delta_sample_offset = 0
00424279        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042429d        float var_8_1 = fconvert.s(fconvert.t(*(delta_sample_offset + primary_samples_3 + 0xdc)) - fconvert.t(*(&primary_samples_3->transform.position.y + delta_sample_offset)))
004242a4        long double x87_r7_41 = fconvert.t(*(delta_sample_offset + primary_samples_3 + 0xe0)) - fconvert.t(*(&primary_samples_3->transform.position.z + delta_sample_offset))
004242ab        *(&primary_samples_3->delta_dir_to_next + delta_sample_offset) = fconvert.s(fconvert.t(*(delta_sample_offset + primary_samples_3 + 0xd8)) - fconvert.t(*(&primary_samples_3->transform.position + delta_sample_offset)))
004242ad        *(&primary_samples_3->delta_dir_to_next.y + delta_sample_offset) = var_8_1
004242b8        *(&primary_samples_3->delta_dir_to_next.z + delta_sample_offset) = fconvert.s(x87_r7_41)
004242cd        *(&self->primary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + delta_sample_offset))
004242d4        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
004242f8        float var_14_1 = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + delta_sample_offset)))
004242ff        long double x87_r7_48 = fconvert.t(*(delta_sample_offset + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + delta_sample_offset))
00424306        *(&secondary_samples_1->delta_dir_to_next + delta_sample_offset) = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + delta_sample_offset)))
00424308        *(&secondary_samples_1->delta_dir_to_next.y + delta_sample_offset) = var_14_1
00424313        *(&secondary_samples_1->delta_dir_to_next.z + delta_sample_offset) = fconvert.s(x87_r7_48)
00424328        delta_index += 1
00424329        *(&self->secondary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + delta_sample_offset))
00424333        delta_sample_offset += 0xa8
0042433b        do while (delta_index s< self->segment_count)
00424350        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
00424362        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
00424367        struct Object* object = self->bod.object
0042436a        int32_t i = 0
0042436c        width_cells_ = 0
00424370        struct Vec3* vertices = object->vertices
00424377        struct ObjectFaceQuad* facequads = object->facequads
0042437d        struct ObjectFaceQuad* facequads_1 = facequads
00424383        if (self->segment_count s>= 0)
00424389        int32_t var_28_1 = 0
0042438d        uint32_t width_cells = self->width_cells
00424390        float length_1 = 0f
00424394        length = 0f
00424398        uint32_t width_cells_1 = width_cells
0042439c        if (width_cells s>= 0)
004243b1        struct PathTemplateSample* primary_mesh_sample = self->primary_samples + var_28_1
004243b3        i = width_cells_
004243bd        long double x87_r7_51 = float.t(length) - float.t(width_cells_1) * fconvert.t(0.5f)
004243f6        int32_t eax_42 = (width_cells + 1) * i i+ length_1
004243f8        length_1 += 1
004243f9        length = length_1
00424418        vertices[eax_42].x.12 = struct Vec3 {
    .x = fconvert.s(fconvert.t(fconvert.s(x87_r7_51 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
    .y = fconvert.s(fconvert.t(fconvert.s(x87_r7_51 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
    .z = fconvert.s(x87_r7_51 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
}
0042441b        width_cells = self->width_cells
00424420        width_cells_1 = width_cells
00424424        do while (length_1 s<= width_cells)
00424431        i += 1
0042443a        width_cells_ = i
0042443e        var_28_1 += 0xa8
00424442        do while (i s<= self->segment_count)
0042444b        int32_t i_1 = 0
0042444f        if (self->segment_count s> 0)
00424458        int32_t j = 0
0042445c        length = 0f
00424460        if (self->width_cells s> 0)
00424468        int32_t eax_51 = i_1 & 0x80000007
0042446d        if (eax_51 s< 0)
00424473        eax_51 = ((eax_51 - 1) | 0xfffffff8) + 1
00424487        width_cells_ = fconvert.s(float.t(eax_51) * fconvert.t(0.125f))
00424495        float var_28_2 = fconvert.s(float.t(eax_51 + 1) * fconvert.t(0.125f))
004244a4        int32_t ecx_40 = 0
004244aa        int32_t var_24_1 = 0
004244b4        length = fconvert.s(float.t(length) * fconvert.t(0.125f))
004244c2        float var_2c_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
004244dc        while (true)
004244dc        int32_t eax_59 = ecx_40 + ((self->width_cells * i_1 + j) << 1)
004244df        if (ecx_40 != 0)
004245ab        int32_t eax_69 = eax_59 * 0x30
004245b0        struct ObjectFaceQuad* face_second = eax_69 + facequads
004245b3        __builtin_memset(face_second, 0, 2)
004245b9        ecx_40.w = self->width_cells.w
004245bd        ecx_40.w += 1
004245c6        face_second->vertex_0 = ecx_40.w * i_1.w + j.w + 1
004245ca        eax_69.w = self->width_cells.w
004245ce        eax_69.w += 1
004245d5        face_second->vertex_1 = eax_69.w * i_1.w + j.w
004245e7        face_second->vertex_2 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w
004245ff        face_second->vertex_3 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w + 1
00424603        char* texture_path_1
00424603        if (((j.b ^ i_1.b) & 1) != 0)
00424699        texture_path_1 = texture_b
0042460d        texture_path_1 = texture_b
00424620        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
00424627        face_second->uv[0].u = var_2c_1
0042462a        face_second->uv[0].v = width_cells_
0042462f        face_second->uv[1].u = length
00424638        face_second->uv[1].v = width_cells_
0042463f        face_second->uv[2].u = length
00424642        face_second->uv[2].v = var_28_2
00424647        face_second->uv[3].u = var_2c_1
0042464a        face_second->uv[3].v = var_28_2
004244eb        struct ObjectFaceQuad* face_first = &facequads[eax_59]
004244ee        __builtin_memset(face_first, 0, 2)
004244f4        facequads.w = self->width_cells.w
004244f8        facequads.w += 1
004244ff        face_first->vertex_0 = facequads.w * i_1.w + j.w
00424503        eax_59.w = self->width_cells.w
00424507        eax_59.w += 1
00424513        face_first->vertex_1 = eax_59.w * i_1.w + j.w + 1
00424524        face_first->vertex_2 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w + 1
00424533        face_first->vertex_3 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w
0042453d        char* texture_path
0042453d        if (i_1 != self->segment_count - 1)
0042458e        int32_t var_40_8 = 0
00424592        int32_t var_44_6 = 0
00424597        if (((j.b ^ i_1.b) & 1) != 0)
00424547        texture_path = texture_a
0042459d        texture_path = texture_a
00424543        int32_t var_40_7 = 0
00424545        int32_t var_44_5 = 0
00424547        texture_path = cap_texture
0042455a        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
00424561        face_first->uv[0].u = length
00424564        face_first->uv[0].v = width_cells_
00424569        face_first->uv[1].u = var_2c_1
00424572        face_first->uv[1].v = width_cells_
00424579        face_first->uv[2].u = var_2c_1
0042457c        face_first->uv[2].v = var_28_2
00424581        face_first->uv[3].u = length
00424584        face_first->uv[3].v = var_28_2
00424652        bool cond:9_1 = var_24_1 + 1 s< 2
00424655        var_24_1 += 1
00424659        if (not(cond:9_1))
00424659        break
004244c8        ecx_40 = var_24_1
004244cc        facequads = facequads_1
0042465f        j += 1
00424666        facequads = facequads_1
0042466c        length = j
00424670        do while (j s< self->width_cells)
0042467b        i_1 += 1
0042467e        do while (i_1 s< self->segment_count)
00424686        calc_path_length_z(self)
00424692        return
