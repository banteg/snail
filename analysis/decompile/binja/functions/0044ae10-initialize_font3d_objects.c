/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_font3d_objects @ 0x44ae10 */

0044ae13        int32_t font_id_1 = sx.d(font_id)
0044ae20        int32_t var_8 = 0
0044ae36        if ((&g_font_sheets)[font_id_1][0].slot_count s<= 0)
0044ae36        return
0044ae46        float* ebp_1 = &g_font3d_scales
0044ae4e        struct Object** esi_1 = &g_font3d_bods[0].object
0044ae53        int32_t eax_1 = font_id_1 * 0x20a
0044ae59        int32_t* edi_1 = &g_font_sheets[0].v0[eax_1]
0044afa5        bool cond:0_1
0044ae71        font_id.d = fconvert.s(fconvert.t(edi_1[0x80]) / fconvert.t(g_font_sheets[font_id_1].line_marker_y))
0044ae7e        set_bod_object(&esi_1[-9], add_object_to_list(&g_object_list))
0044ae8b        load_object_definition("Objects/Font3D", *esi_1)
0044ae96        esi_1[-2] = 0
0044ae99        esi_1[-1] = 0
0044aeb9        (*esi_1)->facequads->texture_ref = (&g_font_sheets[0].texture_ref_a)[eax_1 + edi_1[0x100]]
0044aec7        (*esi_1)->facequads->uv[0].u = edi_1[-0x80]
0044aed5        (*esi_1)->facequads->uv[0].v = fconvert.s(fconvert.t(1f) - fconvert.t(g_font_sheets[font_id_1].line_step))
0044aee5        (*esi_1)->facequads->uv[1].u = *edi_1
0044aef3        (*esi_1)->facequads->uv[1].v = fconvert.s(fconvert.t(1f) - fconvert.t(g_font_sheets[font_id_1].line_step))
0044af03        (*esi_1)->facequads->uv[2].u = *edi_1
0044af11        (*esi_1)->facequads->uv[2].v = fconvert.s(fconvert.t(1f) - fconvert.t(g_font_sheets[font_id_1].line_marker_fraction))
0044af25        (*esi_1)->facequads->uv[3].u = edi_1[-0x80]
0044af33        (*esi_1)->facequads->uv[3].v = fconvert.s(fconvert.t(1f) - fconvert.t(g_font_sheets[font_id_1].line_marker_fraction))
0044af3c        struct Vec3* vertices = (*esi_1)->vertices
0044af41        vertices->x = fconvert.s(fconvert.t(font_id.d) * fconvert.t(vertices->x))
0044af49        struct Vec3* vertices_1 = (*esi_1)->vertices
0044af4f        vertices_1->__offset(0xc).d = fconvert.s(fconvert.t(font_id.d) * fconvert.t(vertices_1->__offset(0xc).d))
0044af58        struct Vec3* vertices_2 = (*esi_1)->vertices
0044af5e        vertices_2->__offset(0x18).d = fconvert.s(fconvert.t(font_id.d) * fconvert.t(vertices_2->__offset(0x18).d))
0044af67        struct Vec3* vertices_3 = (*esi_1)->vertices
0044af6d        vertices_3->__offset(0x24).d = fconvert.s(fconvert.t(font_id.d) * fconvert.t(vertices_3->__offset(0x24).d))
0044af72        (*esi_1)->blend_mode = 1
0044af79        struct Object* eax_14 = *esi_1
0044af7b        esi_1 = &esi_1[0xe]
0044af7e        edi_1 = &edi_1[1]
0044af81        ebp_1 = &ebp_1[1]
0044af8a        eax_14->flags |= OBJECT_FLAG_REFRESH_TINT_EACH_DRAW
0044af91        int32_t slot_count = (&g_font_sheets)[font_id_1][0].slot_count
0044af97        ebp_1[-1] = font_id.d
0044af9f        cond:0_1 = var_8 + 1 s< slot_count
0044afa1        var_8 += 1
0044afa5        do while (cond:0_1)
0044afb2        return
