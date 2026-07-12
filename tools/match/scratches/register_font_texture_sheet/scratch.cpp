// register_font_texture_sheet @ 0x449f50 (cdecl)

#include "font_system.h"
#include "tga_image_view.h"

char* load_file_bytes(char* file_name, int* out_size);
void free_tracked_memory(void* pointer);
int sample_tga_pixel_rgb(TgaImageView* image, int x, int y);

int register_font_texture_sheet(
    char* texture_path,
    int font_kind,
    float width_scale,
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
        texture_path_1[i] = '.';
        texture_path_0[i] = '.';
        ++i;
        texture_path_1[i] = 't';
        texture_path_0[i] = 't';
        ++i;
        texture_path_1[i] = 'g';
        texture_path_0[i] = 'g';
        ++i;
        texture_path_1[i] = 'a';
        texture_path_0[i] = 'a';
        ++i;
        texture_path_1[i] = 0;
        texture_path_0[i] = 0;
    }

    int x = 0;
    int run_width = -1;
    int slot = 0;
    int last_x = 0;

    while (x < image->width) {
        int pixel = sample_tga_pixel_rgb(image, x, 0);
        if (pixel == 0xffffff) {
            float glyph_run_width = (float)run_width;
            int glyph_left = x - run_width;
            run_width = 0;
            g_font_sheets[g_registered_font_count].glyph_width[slot] =
                glyph_run_width;

            float centered_left = (float)glyph_left + 0.5f;
            float centered_last = (float)last_x + 0.5f;
            g_font_sheets[g_registered_font_count].u0[slot] =
                centered_left / (float)image->width;
            g_font_sheets[g_registered_font_count].v0[slot] =
                centered_last / (float)image->width;
            g_font_sheets[g_registered_font_count].texture_page[slot] = 0;

            if (image->width == 0x800) {
                if (glyph_left > split_x) {
                    g_font_sheets[g_registered_font_count].u0[slot] =
                        ((float)(glyph_left - split_x) + 0.5f)
                            * 0.0009765625f;
                    g_font_sheets[g_registered_font_count].v0[slot] =
                        ((float)(x - split_x) + 0.5f)
                            / (float)(image->width >> 1);
                    g_font_sheets[g_registered_font_count].texture_page[slot] =
                        1;
                } else {
                    g_font_sheets[g_registered_font_count].u0[slot] =
                        centered_left * 0.0009765625f;
                    g_font_sheets[g_registered_font_count].v0[slot] =
                        centered_last
                        / (float)(image->width >> 1);
                    g_font_sheets[g_registered_font_count].texture_page[slot] =
                        0;
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
        for (; line_marker_y < image->height; ++line_marker_y) {
            if (sample_tga_pixel_rgb(image, 0, line_marker_y) == 0xffffff) {
                g_font_sheets[g_registered_font_count].line_marker_y =
                    (float)line_marker_y;
                break;
            }
        }
    }

    g_font_sheets[g_registered_font_count].line_step =
        3.0f / (float)(image->height - 1);
    g_font_sheets[g_registered_font_count].line_marker_fraction =
        g_font_sheets[g_registered_font_count].line_marker_y
            / (float)(image->height - 1);
    g_font_sheets[g_registered_font_count].slot_count = slot;
    g_font_sheets[g_registered_font_count].font_kind = font_kind;

    if (image->width == 0x800) {
        TextureRef* texture_0 = g_texture_refs.get_or_create_texture_ref(texture_path_0, 0, 0);
        g_font_sheets[g_registered_font_count].texture_ref_a = texture_0;
        texture_0->flags |=
            TEXTURE_REF_REGISTERED | TEXTURE_REF_RETAIN_SOURCE_BYTES;

        TextureRef* texture_1 = g_texture_refs.get_or_create_texture_ref(texture_path_1, 0, 0);
        g_font_sheets[g_registered_font_count].texture_ref_b = texture_1;
        texture_1->flags |=
            TEXTURE_REF_REGISTERED | TEXTURE_REF_RETAIN_SOURCE_BYTES;
    } else {
        TextureRef* texture = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
        g_font_sheets[g_registered_font_count].texture_ref_a = texture;
        texture->flags |= TEXTURE_REF_REGISTERED;
    }

    g_font_sheets[g_registered_font_count].spacing_scale = 1.0f;
    g_font_sheets[g_registered_font_count].width_scale = width_scale;
    g_font_sheets[g_registered_font_count].height_scale = height_scale;
    g_font_sheets[g_registered_font_count].line_marker_y =
        height_scale * g_font_sheets[g_registered_font_count].line_marker_y;

    free_tracked_memory(image);

    return g_registered_font_count++;
}
