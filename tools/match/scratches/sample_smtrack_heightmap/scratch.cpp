// sample_smtrack_heightmap @ 0x41a360 (cdecl)

#include "smtracks.h"
#include "tga_image_view.h"

void __cdecl sample_smtrack_heightmap(
    Object* source,
    float base,
    float scale,
    TextureRef* replacement,
    char cubic)
{
    TgaImageView* image = (TgaImageView*)replacement->texture_ref;
    float sample_count_float = (float)source->heightmap_sample_count;
    int row_count =
        (int)(sample_count_float * source->heightmap_sample_scale /
            source->heightmap_sample_divisor);
    float row_count_float = (float)row_count;
    int image_width = image->width;
    int image_height = image->height;
    float x_step = (float)image_width / (sample_count_float + 1.0f);
    float y_step = (float)image_height / (row_count_float + 1.0f);
    Vector3* sample = source->vertices;

    for (float row = 0.0f; row <= row_count_float; row += 1.0f) {
        for (float column = 0.0f; column <= sample_count_float; column += 1.0f) {
            int y = (int)(row * y_step);
            int x = (int)(column * x_step);
            int pixel_index = x;
            int row_index = image->height;
            row_index -= y;
            --row_index;
            row_index *= image->width;
            pixel_index += row_index;
            int bytes_per_pixel = image->bits_per_pixel >> 3;
            unsigned char* pixel = image->pixels + pixel_index * bytes_per_pixel;
            float red = (float)pixel[2];
            float green = (float)pixel[1];
            float blue = (float)pixel[0];
            float value = red;
            value += green;
            value += blue;
            value *= 0.00392156886f;
            value *= 0.333333343f;

            if (cubic)
                value = value * value * value;

            sample->y = value * scale + base;
            ++sample;
        }
    }
}
