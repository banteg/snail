// sample_smtrack_heightmap @ 0x41a360 (cdecl)

struct HeightmapImage {
    char unknown_00[0x0c];
    unsigned short width;          // +0x0c
    unsigned short height;         // +0x0e
    unsigned char bits_per_pixel;  // +0x10
    char unknown_11[0x12 - 0x11];
    unsigned char pixels[1];       // +0x12
};

struct HeightmapReplacement {
    char unknown_00[0x98];
    HeightmapImage* image; // +0x98
};

struct SampleOutput {
    float x;
    float y;
    float z;
};

struct SmtrackHeightmapSource {
    char unknown_00[0x1c];
    int sample_count;        // +0x1c
    char unknown_20[0x24 - 0x20];
    float sample_divisor;    // +0x24
    float sample_scale;      // +0x28
    char unknown_2c[0x38 - 0x2c];
    SampleOutput* samples;   // +0x38
};

void __cdecl sample_smtrack_heightmap(
    SmtrackHeightmapSource* source,
    float base,
    float scale,
    HeightmapReplacement* replacement,
    char cubic)
{
    HeightmapImage* image = replacement->image;
    float sample_count_float = (float)source->sample_count;
    int row_count =
        (int)(sample_count_float * source->sample_scale / source->sample_divisor);
    float row_count_float = (float)row_count;
    int image_width = image->width;
    int image_height = image->height;
    float x_step = (float)image_width / (sample_count_float + 1.0f);
    float y_step = (float)image_height / (row_count_float + 1.0f);
    SampleOutput* sample = source->samples;

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
            int red = pixel[2];
            int green = pixel[1];
            int blue = pixel[0];
            float value = (float)red;
            value += (float)green;
            value += (float)blue;
            value *= 0.00392156886f;
            value *= 0.333333343f;

            if (cubic)
                value = value * value * value;

            sample->y = value * scale + base;
            ++sample;
        }
    }
}
