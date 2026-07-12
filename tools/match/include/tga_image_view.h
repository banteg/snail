// TGA header plus the first byte of its inline pixel payload.
#ifndef TGA_IMAGE_VIEW_H
#define TGA_IMAGE_VIEW_H

typedef struct TgaImageView {
    unsigned char id_length;       // +0x00
    unsigned char color_map_type;  // +0x01
    unsigned char image_type;      // +0x02
    unsigned char color_map_spec[5]; // +0x03
    unsigned short x_origin;       // +0x08
    unsigned short y_origin;       // +0x0a
    unsigned short width;          // +0x0c
    unsigned short height;         // +0x0e
    unsigned char bits_per_pixel;  // +0x10
    unsigned char descriptor;      // +0x11
    unsigned char pixels[1];       // +0x12
} TgaImageView;

typedef char TgaImageView_must_be_0x14[
    (sizeof(TgaImageView) == 0x14) ? 1 : -1];

#endif
