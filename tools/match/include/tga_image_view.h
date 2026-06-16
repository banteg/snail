// Minimal TGA-like image view used by font atlas sampling.
#ifndef TGA_IMAGE_VIEW_H
#define TGA_IMAGE_VIEW_H

struct TgaImageView {
    char header[0x0c];
    unsigned short width;          // +0x0c
    unsigned short height;         // +0x0e
    unsigned char bits_per_pixel;  // +0x10
    unsigned char descriptor;      // +0x11
    unsigned char pixels[1];       // +0x12
};

#endif
