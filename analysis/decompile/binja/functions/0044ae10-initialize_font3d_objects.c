/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_font3d_objects @ 0x44ae10 */

0044ae13        int32_t font_id_1 = sx.d(font_id)
0044ae20        int32_t glyph_index = 0
0044ae36        if ((&g_font_sheets)[font_id_1][0].slot_count s<= 0)
0044ae36        return
0044ae46        float* scale_cursor = &g_font3d_scales
0044ae4e        struct Object** bod_object_cursor = &g_font3d_bods[0].object
0044ae53        int32_t font_sheet_dword_offset = font_id_1 * 0x20a
0044ae59        struct FontGlyphAtlasCursor* glyph_atlas_cursor = &g_font_sheets[0].glyph_u1[font_sheet_dword_offset]
0044afa5        bool cond:0_1
0044ae71        float glyph_scale = fconvert.s(fconvert.t(glyph_atlas_cursor->glyph_width) / fconvert.t(g_font_sheets[font_id_1].line_marker_y))
0044ae7e        set_bod_object(&bod_object_cursor[-9], add_object_to_list(&g_object_list))
0044ae8b        load_object_definition("Objects/Font3D", *bod_object_cursor)
0044ae96        __builtin_memset(&bod_object_cursor[-2], 0, 8)
0044aeb9        (*bod_object_cursor)->facequads->texture_ref = (&g_font_sheets[0].texture_ref_a)[font_sheet_dword_offset + glyph_atlas_cursor->texture_page]
0044aec7        (*bod_object_cursor)->facequads->uv[0].u = glyph_atlas_cursor->__offset(0xfffffffffffffe00).d
0044aed5        (*bod_object_cursor)->facequads->uv[0].v = fconvert.s(fconvert.t(1f) - fconvert.t(g_font_sheets[font_id_1].glyph_v0))
0044aee5        (*bod_object_cursor)->facequads->uv[1].u = glyph_atlas_cursor->glyph_u1
0044aef3        (*bod_object_cursor)->facequads->uv[1].v = fconvert.s(fconvert.t(1f) - fconvert.t(g_font_sheets[font_id_1].glyph_v0))
0044af03        (*bod_object_cursor)->facequads->uv[2].u = glyph_atlas_cursor->glyph_u1
0044af11        (*bod_object_cursor)->facequads->uv[2].v = fconvert.s(fconvert.t(1f) - fconvert.t(g_font_sheets[font_id_1].glyph_v1))
0044af25        (*bod_object_cursor)->facequads->uv[3].u = glyph_atlas_cursor->__offset(0xfffffffffffffe00).d
0044af33        (*bod_object_cursor)->facequads->uv[3].v = fconvert.s(fconvert.t(1f) - fconvert.t(g_font_sheets[font_id_1].glyph_v1))
0044af3c        struct Vec3* vertices = (*bod_object_cursor)->vertices
0044af41        vertices->x = fconvert.s(fconvert.t(glyph_scale) * fconvert.t(vertices->x))
0044af49        struct Vec3* vertices_1 = (*bod_object_cursor)->vertices
0044af4f        vertices_1->__offset(0xc).d = fconvert.s(fconvert.t(glyph_scale) * fconvert.t(vertices_1->__offset(0xc).d))
0044af58        struct Vec3* vertices_2 = (*bod_object_cursor)->vertices
0044af5e        vertices_2->__offset(0x18).d = fconvert.s(fconvert.t(glyph_scale) * fconvert.t(vertices_2->__offset(0x18).d))
0044af67        struct Vec3* vertices_3 = (*bod_object_cursor)->vertices
0044af6d        vertices_3->__offset(0x24).d = fconvert.s(fconvert.t(glyph_scale) * fconvert.t(vertices_3->__offset(0x24).d))
0044af72        (*bod_object_cursor)->blend_mode = 1
0044af79        struct Object* eax_13 = *bod_object_cursor
0044af7b        bod_object_cursor = &bod_object_cursor[0xe]
0044af7e        glyph_atlas_cursor = &glyph_atlas_cursor->next_glyph_u1
0044af81        scale_cursor = &scale_cursor[1]
0044af8a        eax_13->flags |= OBJECT_FLAG_REFRESH_TINT_EACH_DRAW
0044af91        int32_t slot_count = (&g_font_sheets)[font_id_1][0].slot_count
0044af97        scale_cursor[-1] = glyph_scale
0044af9f        cond:0_1 = glyph_index + 1 s< slot_count
0044afa1        glyph_index += 1
0044afa5        do while (cond:0_1)
0044afb2        return
