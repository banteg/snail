/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: register_font_texture_sheet @ 0x449f50 */

00449f5d        int32_t split_x = 0
00449f64        if (g_registered_font_count == 1)
00449f6b        report_errorf("Too many Fonts RFONT_FONT_MAX in font.h")
00449f7d        struct TgaImageView* image = load_file_bytes(texture_path, nullptr)
00449f8d        char texture_path_0[0x100]
00449f8d        char texture_path_1[0x100]
00449f8d        if (image->width == 0x800)
00449f8f        char path_char = *texture_path
00449f93        int32_t path_index = 0
00449f97        while (path_char != 0x2e)
00449f99        texture_path_0[path_index] = path_char
00449f9d        texture_path_1[path_index] = path_char
00449fa4        path_char = texture_path[path_index + 1]
00449fa8        path_index += 1
00449fad        texture_path_0[path_index] = 0x30
00449fb2        texture_path_1[path_index] = 0x31
00449fbd        split_x = 0x3c0
00449fc2        texture_path_1[path_index + 1] = 0x2e
00449fc9        texture_path_0[path_index + 1] = 0x2e
00449fce        texture_path_1[path_index + 2] = 0x74
00449fd5        texture_path_0[path_index + 2] = 0x74
00449fdc        texture_path_1[path_index + 3] = 0x67
00449fe3        texture_path_0[path_index + 3] = 0x67
00449fea        texture_path_1[path_index + 4] = 0x61
00449ff1        texture_path_0[path_index + 4] = 0x61
00449ff6        texture_path_1[path_index + 5] = 0
00449ffe        texture_path_0[path_index + 5] = 0
0044a003        int32_t x = 0
0044a005        int32_t run_width = 0xffffffff
0044a00c        int32_t glyph_slot = 0
0044a014        int32_t glyph_run_width = 0xffffffff
0044a018        int32_t last_x = 0
0044a01c        int32_t registered_font_count_2
0044a01c        if (image->width u<= 0)
0044a190        registered_font_count_2 = g_registered_font_count
0044a188        int32_t eax_13
0044a026        int32_t pixel_color = sample_tga_pixel_rgb(image, x, 0)
0044a02b        registered_font_count_2 = g_registered_font_count
0044a039        if (pixel_color == 0xffffff)
0044a059        int32_t glyph_left = x - run_width
0044a05b        int32_t ebp = 0
0044a05d        g_font_sheets[0].glyph_width[glyph_slot + registered_font_count_2 * 0x20a] = fconvert.s(float.t(glyph_run_width))
0044a067        ebp.w = image->width
0044a073        int32_t ebp_1 = 0
0044a07b        float centered_left = fconvert.s(float.t(glyph_left) + fconvert.t(0.5f))
0044a087        g_font_sheets[0].u0[glyph_slot + registered_font_count_2 * 0x20a] = fconvert.s(fconvert.t(centered_left) / float.t(ebp))
0044a091        ebp_1.w = image->width
0044a099        run_width = 0
0044a0a1        float centered_last = fconvert.s(float.t(last_x) + fconvert.t(0.5f))
0044a0ad        g_font_sheets[0].v0[glyph_slot + registered_font_count_2 * 0x20a] = fconvert.s(fconvert.t(centered_last) / float.t(ebp_1))
0044a0b3        g_font_sheets[0].texture_page[glyph_slot + registered_font_count_2 * 0x20a] = 0
0044a0bf        if (image->width == 0x800)
0044a0c7        if (glyph_left s<= split_x)
0044a128        g_font_sheets[0].u0[glyph_slot + registered_font_count_2 * 0x20a] = fconvert.s(fconvert.t(centered_left) * fconvert.t(0.0009765625f))
0044a147        g_font_sheets[0].v0[glyph_slot + registered_font_count_2 * 0x20a] = fconvert.s(fconvert.t(centered_last) / float.t(zx.d(image->width u>> 1)))
0044a14d        g_font_sheets[0].texture_page[glyph_slot + registered_font_count_2 * 0x20a] = 0
0044a0e7        g_font_sheets[0].u0[glyph_slot + registered_font_count_2 * 0x20a] = fconvert.s((float.t(glyph_left - split_x) + fconvert.t(0.5f)) * fconvert.t(0.0009765625f))
0044a10c        g_font_sheets[0].v0[glyph_slot + registered_font_count_2 * 0x20a] = fconvert.s((float.t(x - split_x) + fconvert.t(0.5f)) / float.t(zx.d(image->width u>> 1)))
0044a112        g_font_sheets[0].texture_page[glyph_slot + registered_font_count_2 * 0x20a] = 1
0044a158        bool cond:3_1 = glyph_slot != 0x7f
0044a15d        glyph_slot += 1
0044a161        if (not(cond:3_1))
0044a168        report_errorf("Too many Font letters increase RFONT_LETTERS_MAX in font.h")
0044a16d        registered_font_count_2 = g_registered_font_count
0044a176        eax_13 = 0
0044a178        run_width += 1
0044a179        eax_13.w = image->width
0044a17d        x += 1
0044a180        glyph_run_width = run_width
0044a184        last_x = x
0044a188        do while (x s< eax_13)
0044a196        int32_t line_marker_y = 1
0044a19f        int32_t var_208_1 = 1
0044a1a3        if (image->height u> 1)
0044a1a9        while (true)
0044a1b6        if (sample_tga_pixel_rgb(image, 0, line_marker_y) == 0xffffff)
0044a1cf        registered_font_count_2 = g_registered_font_count
0044a1e7        g_font_sheets[registered_font_count_2].line_marker_y = fconvert.s(float.t(line_marker_y))
0044a1e7        break
0044a1b8        int32_t ecx_10 = 0
0044a1ba        line_marker_y += 1
0044a1bb        ecx_10.w = image->height
0044a1c1        if (line_marker_y s>= ecx_10)
0044a1c3        registered_font_count_2 = g_registered_font_count
0044a1c9        int32_t line_marker_y_1 = line_marker_y
0044a1cd        break
0044a1f0        int32_t ecx_12 = 0
0044a1f2        ecx_12.w = image->height
0044a202        int32_t edx_2 = 0
0044a21a        g_font_sheets[registered_font_count_2].line_step = fconvert.s(fconvert.t(3f) / float.t(ecx_12 - 1))
0044a220        edx_2.w = image->height
0044a23a        g_font_sheets[registered_font_count_2].line_marker_fraction = fconvert.s(fconvert.t(g_font_sheets[registered_font_count_2].line_marker_y) / float.t(edx_2 - 1))
0044a240        (&g_font_sheets)[registered_font_count_2][0].slot_count = glyph_slot
0044a246        g_font_sheets[registered_font_count_2].font_kind = font_kind
0044a252        struct TextureRef* flagged_texture_ref
0044a252        enum TextureRefFlags flags
0044a252        if (image->width != 0x800)
0044a2c8        flagged_texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0044a2dd        g_font_sheets[g_registered_font_count].texture_ref_a = flagged_texture_ref
0044a2e4        flags = flagged_texture_ref->flags
0044a2e6        flags:1.b |= 4
0044a25e        struct TextureRef* page0_texture_ref = get_or_create_texture_ref(&g_texture_refs, &texture_path_0, nullptr, 0)
0044a277        g_font_sheets[g_registered_font_count].texture_ref_a = page0_texture_ref
0044a28b        page0_texture_ref->flags |= TEXTURE_REF_RETAIN_SOURCE_BYTES | TEXTURE_REF_REGISTERED
0044a295        flagged_texture_ref = get_or_create_texture_ref(&g_texture_refs, &texture_path_1, nullptr, 0)
0044a2aa        g_font_sheets[g_registered_font_count].texture_ref_b = flagged_texture_ref
0044a2b3        flags = flagged_texture_ref->flags | TEXTURE_REF_RETAIN_SOURCE_BYTES | TEXTURE_REF_REGISTERED
0044a2e9        flagged_texture_ref->flags = flags
0044a2eb        g_registered_font_count
0044a313        g_font_sheets[g_registered_font_count].spacing_scale = 0x3f800000
0044a31d        g_font_sheets[g_registered_font_count].width_scale = width_scale
0044a323        g_font_sheets[g_registered_font_count].height_scale = height_scale
0044a32f        g_font_sheets[g_registered_font_count].line_marker_y = fconvert.s(fconvert.t(height_scale) * fconvert.t(g_font_sheets[g_registered_font_count].line_marker_y))
0044a335        free_tracked_memory(image)
0044a33a        int32_t registered_font_count_1 = g_registered_font_count
0044a349        g_registered_font_count = registered_font_count_1 + 1
0044a356        return registered_font_count_1
