// ObjectProcLandScapeUpdate @ 0x41a360 (cdecl)

#include "smtracks.h"
#include "tga_image_view.h"

void __cdecl ObjectProcLandScapeUpdate(
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
        float column = 0.0f;
        if (column <= sample_count_float) {
            int y = (int)(row * y_step);
            int row_base = (image->height - y - 1) * image->width;
            do {
                int x = (int)(column * x_step);
                int pixel_index =
                    (row_base + x)
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
                column += 1.0f;
            } while (column <= sample_count_float);
        }
    }
}
