/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: register_font_texture_sheet @ 0x449f50 */

00449f5d        int32_t ebx = 0
00449f64        if (g_registered_font_count == 1)
00449f6b        report_errorf("Too many Fonts RFONT_FONT_MAX in font.h")
00449f7d        struct TgaImageView* image = load_file_bytes(texture_path, nullptr)
00449f8d        char texture_path_1[0x100]
00449f8d        char texture_path_2[0x100]
00449f8d        if (image->width == 0x800)
00449f8f        char i = *texture_path
00449f93        int32_t eax = 0
00449f97        while (i != 0x2e)
00449f99        texture_path_1[eax] = i
00449f9d        texture_path_2[eax] = i
00449fa4        i = texture_path[eax + 1]
00449fa8        eax += 1
00449fad        texture_path_1[eax] = 0x30
00449fb2        texture_path_2[eax] = 0x31
00449fbd        ebx = 0x3c0
00449fc2        texture_path_2[eax + 1] = 0x2e
00449fc9        texture_path_1[eax + 1] = 0x2e
00449fce        texture_path_2[eax + 2] = 0x74
00449fd5        texture_path_1[eax + 2] = 0x74
00449fdc        texture_path_2[eax + 3] = 0x67
00449fe3        texture_path_1[eax + 3] = 0x67
00449fea        texture_path_2[eax + 4] = 0x61
00449ff1        texture_path_1[eax + 4] = 0x61
00449ff6        texture_path_2[eax + 5] = 0
00449ffe        texture_path_1[eax + 5] = 0
0044a003        int32_t x = 0
0044a005        int32_t ebp = 0xffffffff
0044a00c        int32_t var_204 = 0
0044a014        int32_t var_20c = 0xffffffff
0044a018        int32_t x_1 = 0
0044a01c        int32_t registered_font_count_2
0044a01c        if (image->width u<= 0)
0044a190        registered_font_count_2 = g_registered_font_count
0044a188        int32_t eax_15
0044a026        int32_t eax_6 = sample_tga_pixel_rgb(image, x, 0)
0044a02b        registered_font_count_2 = g_registered_font_count
0044a039        if (eax_6 == 0xffffff)
0044a059        int32_t ecx_3 = x - ebp
0044a05b        int32_t ebp_1 = 0
0044a05d        g_font_sheets[0].glyph_width[var_204 + registered_font_count_2 * 0x20a] = fconvert.s(float.t(var_20c))
0044a067        ebp_1.w = image->width
0044a073        int32_t ebp_2 = 0
0044a07b        float var_208_1 = fconvert.s(float.t(ecx_3) + fconvert.t(0.5f))
0044a087        g_font_sheets[0].u0[var_204 + registered_font_count_2 * 0x20a] = fconvert.s(fconvert.t(var_208_1) / float.t(ebp_1))
0044a091        ebp_2.w = image->width
0044a099        ebp = 0
0044a0a1        float var_20c_3 = fconvert.s(float.t(x_1) + fconvert.t(0.5f))
0044a0ad        g_font_sheets[0].v0[var_204 + registered_font_count_2 * 0x20a] = fconvert.s(fconvert.t(var_20c_3) / float.t(ebp_2))
0044a0b3        g_font_sheets[0].texture_page[var_204 + registered_font_count_2 * 0x20a] = 0
0044a0bf        if (image->width == 0x800)
0044a0c7        if (ecx_3 s<= ebx)
0044a128        g_font_sheets[0].u0[var_204 + registered_font_count_2 * 0x20a] = fconvert.s(fconvert.t(var_208_1) * fconvert.t(0.0009765625f))
0044a147        g_font_sheets[0].v0[var_204 + registered_font_count_2 * 0x20a] = fconvert.s(fconvert.t(var_20c_3) / float.t(zx.d(image->width u>> 1)))
0044a14d        g_font_sheets[0].texture_page[var_204 + registered_font_count_2 * 0x20a] = 0
0044a0e7        g_font_sheets[0].u0[var_204 + registered_font_count_2 * 0x20a] = fconvert.s((float.t(ecx_3 - ebx) + fconvert.t(0.5f)) * fconvert.t(0.0009765625f))
0044a10c        g_font_sheets[0].v0[var_204 + registered_font_count_2 * 0x20a] = fconvert.s((float.t(x - ebx) + fconvert.t(0.5f)) / float.t(zx.d(image->width u>> 1)))
0044a112        g_font_sheets[0].texture_page[var_204 + registered_font_count_2 * 0x20a] = 1
0044a158        bool cond:3_1 = var_204 != 0x7f
0044a15d        var_204 += 1
0044a161        if (not(cond:3_1))
0044a168        report_errorf("Too many Font letters increase RFONT_LETTERS_MAX in font.h")
0044a16d        registered_font_count_2 = g_registered_font_count
0044a176        eax_15 = 0
0044a178        ebp += 1
0044a179        eax_15.w = image->width
0044a17d        x += 1
0044a180        var_20c = ebp
0044a184        x_1 = x
0044a188        do while (x s< eax_15)
0044a196        int32_t y = 1
0044a19f        int32_t var_208_2 = 1
0044a1a3        if (image->height u> 1)
0044a1a9        while (true)
0044a1b6        if (sample_tga_pixel_rgb(image, 0, y) == 0xffffff)
0044a1cf        registered_font_count_2 = g_registered_font_count
0044a1e7        g_font_sheets[registered_font_count_2].line_marker_y = fconvert.s(float.t(y))
0044a1e7        break
0044a1b8        int32_t ecx_11 = 0
0044a1ba        y += 1
0044a1bb        ecx_11.w = image->height
0044a1c1        if (y s>= ecx_11)
0044a1c3        registered_font_count_2 = g_registered_font_count
0044a1c9        int32_t y_1 = y
0044a1cd        break
0044a1f0        int32_t ecx_13 = 0
0044a1f2        ecx_13.w = image->height
0044a202        int32_t edx_2 = 0
0044a21a        g_font_sheets[registered_font_count_2].line_step = fconvert.s(fconvert.t(3f) / float.t(ecx_13 - 1))
0044a220        edx_2.w = image->height
0044a23a        g_font_sheets[registered_font_count_2].line_marker_fraction = fconvert.s(fconvert.t(g_font_sheets[registered_font_count_2].line_marker_y) / float.t(edx_2 - 1))
0044a240        (&g_font_sheets)[registered_font_count_2][0].slot_count = var_204
0044a246        g_font_sheets[registered_font_count_2].font_kind = font_kind
0044a252        struct TextureRef* eax_26
0044a252        enum TextureRefFlags flags
0044a252        if (image->width != 0x800)
0044a2c8        eax_26 = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0044a2dd        g_font_sheets[g_registered_font_count].texture_ref_a = eax_26
0044a2e4        flags = eax_26->flags
0044a2e6        flags:1.b |= 4
0044a25e        struct TextureRef* eax_25 = get_or_create_texture_ref(&g_texture_refs, &texture_path_1, nullptr, 0)
0044a277        g_font_sheets[g_registered_font_count].texture_ref_a = eax_25
0044a28b        eax_25->flags |= TEXTURE_REF_RETAIN_SOURCE_BYTES | TEXTURE_REF_REGISTERED
0044a295        eax_26 = get_or_create_texture_ref(&g_texture_refs, &texture_path_2, nullptr, 0)
0044a2aa        g_font_sheets[g_registered_font_count].texture_ref_b = eax_26
0044a2b3        flags = eax_26->flags | TEXTURE_REF_RETAIN_SOURCE_BYTES | TEXTURE_REF_REGISTERED
0044a2e9        eax_26->flags = flags
0044a2eb        g_registered_font_count
0044a313        g_font_sheets[g_registered_font_count].spacing_scale = 0x3f800000
0044a31d        g_font_sheets[g_registered_font_count].width_scale = width_scale
0044a323        g_font_sheets[g_registered_font_count].height_scale = height_scale
0044a32f        g_font_sheets[g_registered_font_count].line_marker_y = fconvert.s(fconvert.t(height_scale) * fconvert.t(g_font_sheets[g_registered_font_count].line_marker_y))
0044a335        free_tracked_memory(image)
0044a33a        int32_t registered_font_count_1 = g_registered_font_count
0044a349        g_registered_font_count = registered_font_count_1 + 1
0044a356        return registered_font_count_1
