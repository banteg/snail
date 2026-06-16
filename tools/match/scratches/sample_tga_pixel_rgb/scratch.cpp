// sample_tga_pixel_rgb @ 0x44e780 (cdecl)

#include "tga_image_view.h"

int __cdecl sample_tga_pixel_rgb(TgaImageView* image, int x, int y)
{
    int offset = ((image->height - y - 1) * image->width + x) *
        (image->bits_per_pixel >> 3);
    unsigned char* pixel = image->pixels + offset;

    if (image->bits_per_pixel == 8) {
        int value = pixel[0];
        return (value << 8 | value) << 8 | value;
    }

    int red = pixel[0];
    int green = pixel[1];
    int blue = pixel[2];
    return (red << 8 | green) << 8 | blue;
}
