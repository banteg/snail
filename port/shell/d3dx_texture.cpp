// The three D3DX texture loaders the game calls, for the TGA files it ships:
// uncompressed or run-length true-colour and greyscale, 8, 24 or 32 bits.
// Textures become A8R8G8B8 (opaque without an alpha channel), with D3DX's
// colour key: a source pixel equal to the key becomes transparent black.
// The file-path variants read the file system only, as D3DX did; the game
// itself reads archived textures and passes them in memory.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "d3d8_device.h"

namespace {

const int kD3DXErrInvalidData = (int)0x88760b59;

struct Image {
    int width, height;
    unsigned char* rgba;  // rows top first
};

// One source pixel as 0xAARRGGBB.
unsigned int read_pixel(const unsigned char* p, int bits)
{
    switch (bits) {
    case 8: return 0xff000000u | (p[0] << 16) | (p[0] << 8) | p[0];
    case 24: return 0xff000000u | (p[2] << 16) | (p[1] << 8) | p[0];
    default: return ((unsigned int)p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];
    }
}

bool decode_tga(const unsigned char* data, unsigned int size, unsigned int color_key, Image* image)
{
    if (size < 18)
        return false;
    int id_length = data[0], color_map_type = data[1], type = data[2];
    int width = data[12] | (data[13] << 8), height = data[14] | (data[15] << 8);
    int bits = data[16], descriptor = data[17];
    bool rle = type == 10 || type == 11;
    bool true_color = type == 2 || type == 10, grey = type == 3 || type == 11;
    if (color_map_type != 0 || !(true_color || grey) || width <= 0 || height <= 0)
        return false;
    if ((true_color && bits != 24 && bits != 32) || (grey && bits != 8))
        return false;
    int stride = bits / 8;
    const unsigned char* cursor = data + 18 + id_length;
    const unsigned char* end = data + size;

    int count = width * height;
    unsigned int* pixels = (unsigned int*)malloc(count * sizeof(unsigned int));
    for (int i = 0; i < count;) {
        int run = 1;
        bool repeat = false;
        if (rle) {
            if (cursor >= end)
                break;
            int header = *cursor++;
            run = (header & 0x7f) + 1;
            repeat = (header & 0x80) != 0;
        }
        for (int k = 0; k < run && i < count; ++k, ++i) {
            if (cursor + stride > end) {
                free(pixels);
                return false;
            }
            pixels[i] = read_pixel(cursor, bits);
            if (!repeat || k == run - 1)
                cursor += stride;
        }
    }

    bool top_first = (descriptor & 0x20) != 0, right_first = (descriptor & 0x10) != 0;
    image->width = width;
    image->height = height;
    image->rgba = (unsigned char*)malloc(count * 4);
    for (int y = 0; y < height; ++y) {
        int source_y = top_first ? y : height - 1 - y;
        for (int x = 0; x < width; ++x) {
            int source_x = right_first ? width - 1 - x : x;
            unsigned int argb = pixels[source_y * width + source_x];
            if (color_key != 0 && argb == color_key)
                argb = 0;
            unsigned char* out = image->rgba + (y * width + x) * 4;
            out[0] = (unsigned char)(argb >> 16);
            out[1] = (unsigned char)(argb >> 8);
            out[2] = (unsigned char)argb;
            out[3] = (unsigned char)(argb >> 24);
        }
    }
    free(pixels);
    return true;
}

int create_from_memory(const void* data, unsigned int size, unsigned int color_key, Direct3DTexture8** texture)
{
    Image image;
    if (!decode_tga((const unsigned char*)data, size, color_key, &image))
        return kD3DXErrInvalidData;
    *texture = create_emulated_texture(image.width, image.height, image.rgba);
    free(image.rgba);
    return 0;
}

int create_from_file(const char* path, unsigned int color_key, Direct3DTexture8** texture)
{
    FILE* file = fopen(path, "rb");
    if (!file)
        return kD3DXErrInvalidData;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    unsigned char* data = (unsigned char*)malloc(size > 0 ? size : 1);
    size_t read = fread(data, 1, size, file);
    fclose(file);
    int result = create_from_memory(data, (unsigned int)read, color_key, texture);
    free(data);
    return result;
}

}  // namespace

extern "C" int __stdcall D3DXCreateTextureFromFileInMemoryEx(Direct3DDevice8*, void* data, unsigned int size,
    unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
    unsigned int color_key, void*, void*, Direct3DTexture8** texture)
{
    return create_from_memory(data, size, color_key, texture);
}

extern "C" int __stdcall D3DXCreateTextureFromFileExA(Direct3DDevice8*, char* path, unsigned int, unsigned int,
    unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int color_key, void*,
    void*, Direct3DTexture8** texture)
{
    return create_from_file(path, color_key, texture);
}

extern "C" int __stdcall D3DXCreateTextureFromFileA(Direct3DDevice8*, char* path, Direct3DTexture8** texture)
{
    return create_from_file(path, 0, texture);
}
