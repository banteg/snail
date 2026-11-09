// rebuild_game_archive_if_needed @ 0x405370 (cdecl)

#include <stdlib.h>
#include <string.h>

#include "archive_index.h"
#include "datbuild.h"
#include "tga_image_view.h"

typedef unsigned char u8;

char* __cdecl toggle_archive_high_bit_in_place(char* data, int count);
ArchiveEntryExtensionClass __cdecl classify_archive_entry_extension(u8* path, u8* stem_out);

int __cdecl load_png_image(
    char* png_path,
    u8** out_pixels,
    int* out_width,
    int* out_height,
    int* out_channels,
    u8* background_rgb,
    int file_offset);

void __cdecl rebuild_game_archive_if_needed(void)
{
    if (file_exists("SnailMail.dat") || !file_exists("SnailMail.dam"))
        return;

    SerializedArchiveIndex* output = (SerializedArchiveIndex*)malloc(40000000);
    int dam_size;
    SerializedArchiveIndex* source =
        (SerializedArchiveIndex*)load_file_bytes_allocating("SnailMail.dam", &dam_size);
    toggle_archive_high_bit_in_place((char*)source, dam_size);

    SerializedArchiveEntry* source_entries = source->entries;
    SerializedArchiveEntry* output_entries = output->entries;
    memcpy(output, source, source_entries[0].data_offset);

    u8* png_pixels = 0;
    int width, height, channels;
    int background_rgb;
    char* payload = (char*)output + output->entries[0].data_offset;
    for (int i = 0; i < source->count; ++i) {
        const SerializedArchiveEntry& entry = source_entries[i];
        char* path = (char*)output + entry.path_offset;
        u8 stem[512];

        switch (classify_archive_entry_extension((u8*)path, stem)) {
        default:
            memcpy(payload, (char*)source + entry.data_offset, entry.byte_count);
            output_entries[i].data_offset = payload - (char*)output;
            output_entries[i].byte_count = entry.byte_count;
            payload += entry.byte_count;
            // The original adds the signed remainder of the end address.
            payload += (int)payload % 4;
            break;

        case ARCHIVE_ENTRY_EXTENSION_TGA: {
            save_file_bytes_with_optional_archive_scramble(
                "0.png", (char*)source + entry.data_offset, entry.byte_count, 0);
            load_png_image("0.png", &png_pixels, &width, &height, &channels,
                           (u8*)&background_rgb, 0);

            output_entries[i].data_offset = payload - (char*)output;
            TgaImageView* tga = (TgaImageView*)payload;
            tga->id_length = tga->color_map_type =
                tga->color_map_spec[0] = tga->color_map_spec[1] =
                tga->color_map_spec[2] = tga->color_map_spec[3] =
                tga->color_map_spec[4] = 0;
            tga->height = (unsigned short)height;
            tga->descriptor = 8;
            tga->image_type = 2;
            tga->bits_per_pixel = (u8)(channels * 8);
            tga->width = (unsigned short)width;
            tga->x_origin = 0;
            tga->y_origin = 0;

            for (int x = 0; x < width; ++x) {
                for (int y = 0; y < height; ++y) {
                    int src = (y * width + x) * channels;
                    int dst = ((height - y - 1) * width + x) * channels;
                    tga->pixels[dst + 2] = png_pixels[src];
                    tga->pixels[dst + 1] = png_pixels[src + 1];
                    tga->pixels[dst] = png_pixels[src + 2];
                    if (channels == 4)
                        tga->pixels[dst + 3] = png_pixels[src + 3];
                }
            }

            int converted_size = width * height * channels + sizeof(TgaImageView);
            output_entries[i].byte_count = converted_size;
            payload += converted_size;
            payload += (int)payload % 4;
            printf("extracting %s\n", path);
            break;
        }
        }
    }

    save_file_bytes_with_optional_archive_scramble("SnailMail.dat", output, payload - (char*)output, 1);
    delete_file_path("SnailMail.dam");
    delete_file_path("0.png");
    free(output);
}
