/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* export: isolated copy with manifest symbols applied */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_png_image @ 0x42f0a0 */

0042f0ae        uint8_t* pointer = *out_pixels
0042f0b8        if (png_path == 0)
0042f0ba        *out_pixels = nullptr
0042f0c4        return 0
0042f0cb        struct File* stream = fopen(png_path, "rb")
0042f0da        if (stream == 0)
0042f0dc        *out_pixels = nullptr
0042f0e6        return 0
0042f0ec        if (file_offset != 0)
0042f0f1        fseek(stream, file_offset, 0)
0042f102        void bytes
0042f102        fread(&bytes, 1, 8, stream)
0042f10d        int32_t result = png_check_sig(&bytes, 8)
0042f117        if (result == 0)
0042f119        *out_pixels = nullptr
0042f121        return result
0042f12a        char* eax_4 = png_create_read_struct("1.2.5", 0, 0, 0)
0042f134        data_5032f4 = eax_4
0042f139        if (eax_4 == 0)
0042f13b        *out_pixels = nullptr
0042f145        return 0
0042f147        char* eax_6 = png_create_info_struct(eax_4)
0042f151        data_5032f8 = eax_6
0042f157        if (eax_6 == 0)
0042f15f        png_destroy_read_struct(&data_5032f4, nullptr, nullptr)
0042f167        *out_pixels = nullptr
0042f171        return 0
0042f178        int32_t __saved_ebp
0042f178        int32_t entry_esi
0042f178        struct _EXCEPTION_REGISTRATION_RECORD* entry_edi
0042f178        __setjmp3(&__saved_ebp, stream, out_pixels, data_5032f4, 0, entry_edi, entry_esi)
0042f1af        sub_482f3e(data_5032f4, stream)
0042f1bd        png_set_sig_bytes(data_5032f4, 8)
0042f1cf        png_read_info(data_5032f4, data_5032f8)
0042f1f4        uint32_t var_10
0042f1f4        int32_t var_c
0042f1f4        png_get_IHDR(data_5032f4, data_5032f8, out_width, out_height, &var_10, &var_c, nullptr, nullptr, nullptr)
0042f202        if (var_10 == 0x10)
0042f20b        sub_47ed41(data_5032f4)
0042f217        if (var_c == 3)
0042f21f        sub_47ed9b(data_5032f4)
0042f22b        if (var_10 s< 8)
0042f234        sub_47ed9b(data_5032f4)
0042f255        if (sub_47eb0b(data_5032f4, data_5032f8, 0x10) != 0)
0042f25e        sub_47ed9b(data_5032f4)
0042f266        int32_t eax_17 = var_c
0042f270        if (eax_17 == 0 || eax_17 == 4)
0042f279        sub_47eda4(data_5032f4)
0042f29d        char* var_8
0042f29d        if (png_get_bKGD(data_5032f4, data_5032f8, &var_8) == 0)
0042f2db        background_rgb = nullptr
0042f2a8        int32_t var_3c_9 = 0x3ff00000
0042f2b4        png_set_background(data_5032f4, var_8, 2, 1, 0f)
0042f2c5        *background_rgb = var_8[2]
0042f2cd        background_rgb[1] = var_8[4]
0042f2d6        background_rgb[2] = var_8[6]
0042f2f9        int32_t var_24
0042f2f9        if (png_get_gAMA(data_5032f4, data_5032f8, &var_24) != 0)
0042f2fe        int32_t eax_23 = var_24
0042f301        void* ecx_10 = data_5032f4
0042f307        int32_t var_20
0042f307        int32_t var_3c_11 = var_20
0042f309        int32_t var_44_5 = 0x40019999
0042f314        png_set_gamma(eax_23, var_20, ecx_10, ecx_10, -1.58818684e-23f, eax_23)
0042f329        png_read_update_info(data_5032f4, data_5032f8)
0042f348        png_get_IHDR(data_5032f4, data_5032f8, out_width, out_height, &var_10, &var_c, nullptr, nullptr, nullptr)
0042f35a        int32_t eax_27 = sub_47eb25(data_5032f4, data_5032f8)
0042f382        *out_channels = zx.d(d3dx8::png_get_channels(data_5032f4, data_5032f8))
0042f389        if (pointer != 0)
0042f38c        free(pointer)
0042f394        int32_t var_14_1 = 0
0042f39d        uint8_t* pointer_1 = malloc(*out_height * eax_27)
0042f3a9        uint8_t* pointer_3 = pointer_1
0042f3ac        if (pointer_1 == 0)
0042f3b9        png_destroy_read_struct(&data_5032f4, &data_5032f8, nullptr)
0042f3c4        *out_pixels = nullptr
0042f3ce        return 0
0042f3d2        *out_pixels = pointer_1
0042f3da        void** pointer_2 = malloc(*out_height << 2)
0042f3e6        if (pointer_2 == 0)
0042f3f3        png_destroy_read_struct(&data_5032f4, &data_5032f8, pointer_2)
0042f3f9        free(pointer_1)
0042f404        *out_pixels = pointer_2
0042f40e        return 0
0042f411        int32_t i = 0
0042f415        if (*out_height s> 0)
0042f417        void** pointer_5 = pointer_2
0042f419        uint8_t* pointer_4 = pointer_1
0042f41e        *pointer_5 = pointer_4
0042f420        pointer_4 = &pointer_4[eax_27]
0042f424        i += 1
0042f425        pointer_5 = &pointer_5[1]
0042f42a        do while (i s< *out_height)
0042f434        png_read_image(data_5032f4, pointer_2)
0042f442        png_read_end(data_5032f4, 0)
0042f448        free(pointer_2)
0042f451        fclose(stream)
0042f464        return 1
