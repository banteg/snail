// sample_smtrack_heightmap @ 0x41a360 (cdecl)

#include "smtracks.h"
#include "tga_image_view.h"

void __cdecl sample_smtrack_heightmap(
    Object* source,
    float base,
    float scale,
    cRTexture* replacement,
    bool cubic)
{
    TgaImageView* image = (TgaImageView*)replacement->texture_ref;
    float sample_count_float = (float)source->heightmap_sample_count;
    int row_count =
        (int)(sample_count_float * source->heightmap_sample_scale /
            source->heightmap_sample_divisor);
    float row_count_float = (float)row_count;
    float x_step = (float)image->width / (sample_count_float + 1.0f);
    float y_step = (float)image->height / (row_count_float + 1.0f);
    Vector3* sample = source->vertices;

    for (float row = 0.0f; row <= row_count_float; row += 1.0f) {
        for (float column = 0.0f; column <= sample_count_float; column += 1.0f) {
            int y = (int)(row * y_step);
            int x = (int)(column * x_step);
            int pixel_index =
                ((image->height - y - 1) * image->width + x)
                * (image->bits_per_pixel >> 3);
            unsigned char* pixel = image->pixels + pixel_index;
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

            ++sample;
            sample[-1].y = value * scale + base;
        }
    }
}
