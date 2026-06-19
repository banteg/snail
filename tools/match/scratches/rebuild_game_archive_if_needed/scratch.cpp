// rebuild_game_archive_if_needed @ 0x405370 (cdecl)

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct ArchiveEntryWriteCursor {
    int data_offset;
    int byte_count;
    int next_path_offset;
} ArchiveEntryWriteCursor;

void* __cdecl malloc(unsigned int size);
void __cdecl free(void* pointer);
void* __cdecl memcpy(void* dest, const void* src, unsigned int count);
int printf(char* format, ...);

char __cdecl file_exists(char* path);
void* __cdecl load_file_bytes_allocating(char* file_name, int* out_size);
void __cdecl toggle_archive_high_bit_in_place(void* bytes, int byte_count);
int __cdecl classify_archive_entry_extension(u8* path, u8* stem_out);
int __cdecl save_file_bytes_with_optional_archive_scramble(char* file_name, void* bytes, int byte_count, char should_scramble);
void __cdecl delete_file_path(char* path);

int __cdecl load_png_image(
    char* png_path,
    u8** out_pixels,
    int* out_width,
    int* out_height,
    int* out_channels,
    u8* palette_rgb,
    void* file_offset);

void __cdecl rebuild_game_archive_if_needed(void)
{
    int png_channels;
    u8* png_pixels;
    ArchiveEntryWriteCursor* output_entry;
    char* rebuilt;
    int png_width;
    unsigned int* dam_words;
    int png_height;
    int x;
    int source_to_output_delta;
    int entry_index;
    int dam_size;
    char* entry_path;
    int palette_rgb;
    u8 stem[512];
    char* payload_cursor;
    unsigned int* source_byte_count;
    int* rebuilt_words;

    if (file_exists("SnailMail.dat") != 0) {
        return;
    }

    if (file_exists("SnailMail.dam") == 0) {
        return;
    }

    rebuilt_words = (int*)malloc(40000000);
    rebuilt = (char*)rebuilt_words;
    dam_words = (unsigned int*)load_file_bytes_allocating("SnailMail.dam", &dam_size);
    toggle_archive_high_bit_in_place(dam_words, dam_size);

    memcpy(rebuilt_words, dam_words, dam_words[2]);

    png_pixels = 0;
    payload_cursor = rebuilt + rebuilt_words[2];
    entry_index = 0;

    if ((int)dam_words[0] > 0) {
        output_entry = (ArchiveEntryWriteCursor*)(rebuilt + 8);
        source_byte_count = dam_words + 3;
        source_to_output_delta = rebuilt - (char*)dam_words;

        do {
            entry_path = rebuilt + source_byte_count[-2];

            if (classify_archive_entry_extension((u8*)entry_path, stem) != 1) {
                char* payload_end;
                memcpy(payload_cursor, (char*)dam_words + source_byte_count[-1], *source_byte_count);
                output_entry->data_offset = payload_cursor - rebuilt;
                payload_end = payload_cursor + *source_byte_count;
                *(int*)((char*)source_byte_count + source_to_output_delta) = *source_byte_count;
                {
                    int remainder = (int)payload_end & 0x80000003;
                    if (remainder < 0) {
                        remainder = ((remainder - 1) | 0xfffffffc) + 1;
                    }
                    payload_cursor = payload_end + remainder;
                }
            } else {
                int y;
                int converted_size;
                char* payload_end;

                save_file_bytes_with_optional_archive_scramble(
                    "0.png",
                    (char*)dam_words + source_byte_count[-1],
                    *source_byte_count,
                    0);
                load_png_image(
                    "0.png",
                    &png_pixels,
                    &png_width,
                    &png_height,
                    &png_channels,
                    (u8*)&palette_rgb,
                    0);

                output_entry->data_offset = payload_cursor - rebuilt;
                payload_cursor[0] = 0;
                payload_cursor[1] = 0;
                payload_cursor[2] = 2;
                payload_cursor[3] = 0;
                payload_cursor[4] = 0;
                payload_cursor[5] = 0;
                payload_cursor[6] = 0;
                payload_cursor[7] = 0;
                *(u16*)(payload_cursor + 8) = 0;
                *(u16*)(payload_cursor + 10) = 0;
                *(u16*)(payload_cursor + 12) = png_width;
                *(u16*)(payload_cursor + 14) = (u16)png_height;
                payload_cursor[16] = (u8)(png_channels << 3);
                payload_cursor[17] = 8;

                x = 0;
                if (png_width > 0) {
                    do {
                        y = 0;
                        if (png_height > 0) {
                            do {
                                int source_index = (y * png_width + x) * png_channels;
                                int dest_index = ((png_height - y - 1) * png_width + x) * png_channels;
                                payload_cursor[dest_index + 20] = png_pixels[source_index];
                                payload_cursor[dest_index + 19] = png_pixels[source_index + 1];
                                payload_cursor[dest_index + 18] = png_pixels[source_index + 2];
                                if (png_channels == 4) {
                                    payload_cursor[dest_index + 21] = png_pixels[source_index + 3];
                                }
                                ++y;
                            } while (y < png_height);
                        }
                        ++x;
                    } while (x < png_width);
                }

                converted_size = png_width * png_height * png_channels + 20;
                *(int*)((char*)source_byte_count + source_to_output_delta) = converted_size;
                payload_end = payload_cursor + converted_size;
                {
                    int remainder = (int)payload_end & 0x80000003;
                    if (remainder < 0) {
                        remainder = ((remainder - 1) | 0xfffffffc) + 1;
                    }
                    payload_cursor = payload_end + remainder;
                }
                printf("extracting %s\n", entry_path);
            }

            output_entry += 1;
            source_byte_count += 3;
            ++entry_index;
        } while (entry_index < (int)dam_words[0]);
    }

    save_file_bytes_with_optional_archive_scramble("SnailMail.dat", rebuilt_words, payload_cursor - rebuilt, 1);
    delete_file_path("SnailMail.dam");
    delete_file_path("0.png");
    free(rebuilt_words);
}
