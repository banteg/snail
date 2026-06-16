// register_font_texture_sheet @ 0x449f50 (cdecl)

#include "font_system.h"
#include "tga_image_view.h"

char* load_file_bytes(char* file_name, int* out_size);
void free_tracked_memory(void* pointer);
int sample_tga_pixel_rgb(TgaImageView* image, int x, int y);

int register_font_texture_sheet(
    char* texture_path,
    int font_kind,
    int width_scale_bits,
    float height_scale)
{
    int split_x = 0;
    if (g_registered_font_count == 1)
        report_errorf("Too many Fonts RFONT_FONT_MAX in font.h");

    TgaImageView* image = (TgaImageView*)load_file_bytes(texture_path, 0);

    char texture_path_0[0x100];
    char texture_path_1[0x100];
    if (image->width == 0x800) {
        char value = *texture_path;
        int i = 0;
        while (value != '.') {
            texture_path_0[i] = value;
            texture_path_1[i] = value;
            value = texture_path[i + 1];
            ++i;
        }
        texture_path_0[i] = '0';
        texture_path_1[i] = '1';
        split_x = 0x3c0;
        ++i;
        texture_path_0[i] = '.';
        texture_path_1[i] = '.';
        ++i;
        texture_path_0[i] = 't';
        texture_path_1[i] = 't';
        ++i;
        texture_path_0[i] = 'g';
        texture_path_1[i] = 'g';
        ++i;
        texture_path_0[i] = 'a';
        texture_path_1[i] = 'a';
        ++i;
        texture_path_0[i] = 0;
        texture_path_1[i] = 0;
    }

    int x = 0;
    int run_width = -1;
    int slot = 0;
    int last_x = 0;
    FontSheet* sheet = &g_font_sheets[g_registered_font_count];

    while (x < image->width) {
        int pixel = sample_tga_pixel_rgb(image, x, 0);
        if (pixel == 0xffffff) {
            int glyph_left = x - run_width;
            sheet->glyph_width[slot] = (float)run_width;

            float centered_left = (float)glyph_left + 0.5f;
            float centered_last = (float)last_x + 0.5f;
            sheet->u0[slot] = centered_left / (float)image->width;
            sheet->v0[slot] = centered_last / (float)image->width;
            sheet->texture_page[slot] = 0;

            if (image->width == 0x800) {
                if (glyph_left > split_x) {
                    sheet->u0[slot] = ((float)(glyph_left - split_x) + 0.5f)
                        * 0.0009765625f;
                    sheet->v0[slot] = ((float)(x - split_x) + 0.5f)
                        / (float)(image->width >> 1);
                    sheet->texture_page[slot] = 1;
                } else {
                    sheet->u0[slot] = centered_left * 0.0009765625f;
                    sheet->v0[slot] = centered_last
                        / (float)(image->width >> 1);
                    sheet->texture_page[slot] = 0;
                }
            }

            ++slot;
            if (slot == 0x80)
                report_errorf("Too many Font letters increase RFONT_LETTERS_MAX in font.h");
        }

        ++run_width;
        ++x;
        last_x = x;
    }

    int line_marker_y = 1;
    if (image->height > 1) {
        while (1) {
            if (sample_tga_pixel_rgb(image, 0, line_marker_y) == 0xffffff) {
                sheet->line_marker_y = (float)line_marker_y;
                break;
            }
            ++line_marker_y;
            if (line_marker_y >= image->height) {
                sheet->line_marker_y = (float)line_marker_y;
                break;
            }
        }
    }

    sheet->line_step = 3.0f / (float)(image->height - 1);
    sheet->line_marker_fraction = sheet->line_marker_y / (float)(image->height - 1);
    sheet->slot_count = slot;
    sheet->font_kind = font_kind;

    if (image->width == 0x800) {
        TextureRef* texture_0 = g_texture_refs.get_or_create_texture_ref(texture_path_0, 0, 0);
        sheet->texture_ref_a = texture_0;
        texture_0->flags |= 0x420;

        TextureRef* texture_1 = g_texture_refs.get_or_create_texture_ref(texture_path_1, 0, 0);
        sheet->texture_ref_b = texture_1;
        texture_1->flags |= 0x420;
    } else {
        TextureRef* texture = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
        sheet->texture_ref_a = texture;
        texture->flags |= 0x400;
    }

    sheet->spacing_scale = 1.0f;
    *(int*)&sheet->width_scale = width_scale_bits;
    sheet->height_scale = height_scale;
    sheet->line_marker_y = height_scale * sheet->line_marker_y;

    free_tracked_memory(image);

    int result = g_registered_font_count;
    g_registered_font_count = result + 1;
    return result;
}
