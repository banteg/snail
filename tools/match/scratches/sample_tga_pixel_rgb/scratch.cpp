// sample_tga_pixel_rgb @ 0x44e780 (cdecl)

struct TgaImageView {
    char header[0x0c];
    unsigned short width;          // +0x0c
    unsigned short height;         // +0x0e
    unsigned char bits_per_pixel;  // +0x10
    unsigned char descriptor;      // +0x11
    unsigned char pixels[1];       // +0x12
};

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
