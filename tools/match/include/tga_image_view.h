// Minimal TGA-like image view used by font sampling and texture header probes.
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

typedef char TgaImageView_must_be_0x14[
    (sizeof(TgaImageView) == 0x14) ? 1 : -1];

#endif
