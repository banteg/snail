// ObjectProcLandScapeUpdate @ 0x41a360 (cdecl)

#include "smtracks.h"
#include "tga_image_view.h"

static inline unsigned char SampleTgaChannel(
    const TgaImageView* image, int x, int y, int channel)
{
    int row = image->height - y - 1;
    int offset = (row * image->width + x) * (image->bits_per_pixel >> 3);
    return image->pixels[offset + channel];
}

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
        for (float column = 0.0f; column <= sample_count_float; column += 1.0f) {
            int x = (int)(column * x_step);
            int y = (int)(row * y_step);
            float red = SampleTgaChannel(image, x, y, 2);
            float green = SampleTgaChannel(image, x, y, 1);
            float blue = SampleTgaChannel(image, x, y, 0);
            float value = red + green + blue;
            value *= (1.0f / 255.0f);
            value *= (1.0f / 3.0f);

            if (cubic)
                value = value * value * value;

            sample->y = value * scale + base;
            ++sample;
        }
    }
}
