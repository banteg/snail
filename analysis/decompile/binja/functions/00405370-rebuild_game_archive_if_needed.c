/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rebuild_game_archive_if_needed @ 0x405370 */

00405385        if (file_exists("SnailMail.dat") != 0 || file_exists("SnailMail.dam") == 0)
0040539a        return
004053ae        struct SerializedArchiveIndex* rebuilt_index = malloc(0x2625a00)
004053be        int32_t dam_size
004053be        struct SerializedArchiveIndex* source_index = load_file_bytes_allocating("SnailMail.dam", &dam_size)
004053cf        toggle_archive_high_bit_in_place(source_index, dam_size)
004053d4        int32_t data_offset = source_index->entries[0].data_offset
004053e1        int32_t esi_2
004053e1        int32_t edi_2
004053e1        edi_2, esi_2 = __builtin_memcpy(rebuilt_index, source_index, data_offset & 0xfffffffc)
004053ed        __builtin_memcpy(edi_2, esi_2, data_offset & 3)
004053f3        int32_t initial_payload_offset = rebuilt_index->entries[0].data_offset
004053f9        uint8_t* png_pixels = nullptr
004053ff        char* payload_cursor = initial_payload_offset + rebuilt_index
00405403        int32_t entry_index = 0
00405407        if (source_index->count s> 0)
0040540d        int32_t* rebuilt_data_offset_cursor = &rebuilt_index->entries[0].data_offset
00405418        int32_t* source_byte_count_cursor = &source_index->entries[0].byte_count
0040541b        int32_t source_to_rebuilt_delta = &rebuilt_index->entries - &source_index->entries
004055f9        int32_t i
0040542c        char* entry_path = source_byte_count_cursor[-2] + rebuilt_index
0040543d        uint8_t entry_stem[0x200]
0040543d        if (classify_archive_entry_extension(entry_path, &entry_stem) == ARCHIVE_ENTRY_EXTENSION_TGA)
0040549b        save_file_bytes_with_optional_archive_scramble("0.png", source_byte_count_cursor[-1] + source_index, *source_byte_count_cursor, 0)
004054c0        int32_t png_channels
004054c0        int32_t png_width
004054c0        int32_t png_height
004054c0        uint32_t png_background_rgb
004054c0        load_png_image("0.png", &png_pixels, &png_width, &png_height, &png_channels, &png_background_rgb, 0)
004054d0        *rebuilt_data_offset_cursor = payload_cursor - rebuilt_index
004054e2        __builtin_memset(&payload_cursor[3], 0, 5)
004054e6        payload_cursor[1] = 0
004054ea        *payload_cursor = 0
004054ee        int16_t eax_10 = png_height.w
004054f3        payload_cursor[0x11] = 8
004054f7        *(payload_cursor + 0xe) = eax_10
004054fb        payload_cursor[2] = 2
00405508        payload_cursor[0x10] = png_channels.b << 3
00405510        *(payload_cursor + 0xc) = png_width.w
00405514        *(payload_cursor + 8) = 0
00405518        *(payload_cursor + 0xa) = 0
0040551c        int32_t png_width_1 = png_width
00405520        int32_t png_channels_1 = png_channels
00405524        int32_t x = 0
0040552a        int32_t png_height_1 = png_height
0040552e        if (png_width_1 s> 0)
004055a5        bool cond:3_1
00405530        int32_t y = 0
00405534        if (png_height_1 s> 0)
00405541        int32_t source_pixel_offset = (y * png_width_1 + x) * png_channels_1
00405552        int32_t destination_pixel_offset = ((png_height_1 - y - 1) * png_width_1 + x) * png_channels_1
00405558        payload_cursor[destination_pixel_offset + 0x14] = png_pixels[source_pixel_offset]
00405564        payload_cursor[destination_pixel_offset + 0x13] = png_pixels[source_pixel_offset + 1]
00405570        payload_cursor[destination_pixel_offset + 0x12] = png_pixels[source_pixel_offset + 2]
00405574        png_channels_1 = png_channels
0040557b        if (png_channels_1 == 4)
00405585        payload_cursor[destination_pixel_offset + 0x15] = png_pixels[source_pixel_offset + 3]
00405589        png_channels_1 = png_channels
0040558d        png_height_1 = png_height
00405591        png_width_1 = png_width
00405595        y += 1
00405598        do while (y s< png_height_1)
0040559f        cond:3_1 = x + 1 s< png_width_1
004055a1        x += 1
004055a5        do while (cond:3_1)
004055b8        char* payload_end = &payload_cursor[png_width_1 * png_height_1 * png_channels_1 + 0x14]
004055bc        *(source_to_rebuilt_delta + source_byte_count_cursor) = png_width_1 * png_height_1 * png_channels_1 + 0x14
004055bf        int32_t alignment_remainder = payload_end & 0x80000003
004055c5        if (alignment_remainder s< 0)
004055cb        alignment_remainder = ((alignment_remainder - 1) | 0xfffffffc) + 1
004055d2        payload_cursor = &payload_end[alignment_remainder]
004055d4        printf("extracting %s\n", entry_path)
0040543f        int32_t ecx_8 = *source_byte_count_cursor
00405451        int32_t esi_7
00405451        int32_t edi_7
00405451        edi_7, esi_7 = __builtin_memcpy(payload_cursor, source_byte_count_cursor[-1] + source_index, ecx_8 & 0xfffffffc)
0040545c        __builtin_memcpy(edi_7, esi_7, ecx_8 & 3)
00405466        *rebuilt_data_offset_cursor = payload_cursor - rebuilt_index
00405468        int32_t eax_7 = *source_byte_count_cursor
0040546e        void* ebp_1 = &payload_cursor[eax_7]
00405472        void* edx_5 = ebp_1 & 0x80000003
00405478        *(source_to_rebuilt_delta + source_byte_count_cursor) = eax_7
0040547b        if (edx_5 s< 0)
00405481        edx_5 = ((edx_5 - 1) | 0xfffffffc) + 1
00405482        payload_cursor = ebp_1 + edx_5
004055e7        i = entry_index + 1
004055e8        rebuilt_data_offset_cursor = &rebuilt_data_offset_cursor[3]
004055f0        source_byte_count_cursor = &source_byte_count_cursor[3]
004055f3        entry_index = i
004055f9        do while (i s< source_index->count)
0040560e        save_file_bytes_with_optional_archive_scramble("SnailMail.dat", rebuilt_index, payload_cursor - rebuilt_index, 1)
00405618        delete_file_path("SnailMail.dam")
00405622        delete_file_path("0.png")
00405628        free(rebuilt_index)
0040563a        return
