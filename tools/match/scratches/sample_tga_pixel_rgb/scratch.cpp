// sample_tga_pixel_rgb @ 0x44e780 (cdecl)

#include "tga_image_view.h"

int __cdecl sample_tga_pixel_rgb(TgaImageView* image, int x, int y)
{
    int row = image->height;
    row -= y;
    int width = image->width;
    --row;
    row *= width;
    row += x;
    row *= image->bits_per_pixel >> 3;

    int red;
    int green;
    int blue;
    if (image->bits_per_pixel == 8) {
        int value = image->pixels[row];
        blue = value;
        green = value;
        red = value;
    } else {
        red = image->pixels[row];
        green = image->pixels[row + 1];
        blue = image->pixels[row + 2];
    }

    return (red << 16) | (green << 8) | blue;
}
