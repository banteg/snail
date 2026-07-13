// load_png_image @ 0x42f0a0 (cdecl)

#include <setjmp.h>

typedef unsigned char png_byte;
typedef unsigned short png_uint_16;
typedef unsigned long png_uint_32;
typedef png_byte* png_bytep;
typedef png_bytep* png_bytepp;

struct png_struct_def {
    jmp_buf jmpbuf;
};
struct png_info_struct;
struct _iobuf;

typedef png_struct_def* png_structp;
typedef png_structp* png_structpp;
typedef png_info_struct* png_infop;
typedef png_infop* png_infopp;
typedef _iobuf FILE;

struct png_color_16 {
    png_byte index;
    png_uint_16 red;
    png_uint_16 green;
    png_uint_16 blue;
    png_uint_16 gray;
};

typedef png_color_16* png_color_16p;

extern png_structp g_png_read_struct;
extern png_infop g_png_info_struct;

FILE* __cdecl fopen(char* path, char* mode);
int __cdecl fclose(FILE* stream);
int __cdecl fseek(FILE* stream, long offset, int origin);
unsigned int __cdecl fread(void* buffer, unsigned int size, unsigned int count, FILE* stream);
void* __cdecl malloc(unsigned int size);
void __cdecl free(void* pointer);

int __cdecl png_check_sig(png_bytep signature, int count);
png_structp __cdecl png_create_read_struct(char* version, void* error_ptr, void* error_fn, void* warning_fn);
png_infop __cdecl png_create_info_struct(png_structp png_ptr);
void __cdecl png_destroy_read_struct(png_structpp png_ptr, png_infopp info_ptr, png_infopp end_info_ptr);
void __cdecl png_init_io(png_structp png_ptr, FILE* stream);
void __cdecl png_set_sig_bytes(png_structp png_ptr, int count);
void __cdecl png_read_info(png_structp png_ptr, png_infop info_ptr);
png_uint_32 __cdecl png_get_IHDR(
    png_structp png_ptr,
    png_infop info_ptr,
    png_uint_32* width,
    png_uint_32* height,
    int* bit_depth,
    int* color_type,
    int* interlace_type,
    int* compression_type,
    int* filter_type);
void __cdecl png_set_strip_16(png_structp png_ptr);
void __cdecl png_set_expand(png_structp png_ptr);
png_uint_32 __cdecl png_get_valid(png_structp png_ptr, png_infop info_ptr, png_uint_32 flag);
void __cdecl png_set_gray_to_rgb(png_structp png_ptr);
png_uint_32 __cdecl png_get_bKGD(png_structp png_ptr, png_infop info_ptr, png_color_16p* background);
void __cdecl png_set_background(
    png_structp png_ptr,
    png_color_16p background,
    int background_gamma_code,
    int need_expand,
    double background_gamma);
png_uint_32 __cdecl png_get_gAMA(png_structp png_ptr, png_infop info_ptr, double* file_gamma);
void __cdecl png_set_gamma(png_structp png_ptr, double screen_gamma, double file_gamma);
void __cdecl png_read_update_info(png_structp png_ptr, png_infop info_ptr);
png_uint_32 __cdecl png_get_rowbytes(png_structp png_ptr, png_infop info_ptr);
png_byte __cdecl png_get_channels(png_structp png_ptr, png_infop info_ptr);
void __cdecl png_read_image(png_structp png_ptr, png_bytepp row_pointers);
void __cdecl png_read_end(png_structp png_ptr, png_infop info_ptr);

int __cdecl load_png_image(
    char* file_name,
    png_bytep* out_pixels,
    int* out_width,
    int* out_height,
    int* out_channels,
    png_bytep background_rgb,
    int file_offset)
{
    png_byte signature[8];
    FILE* stream;
    png_bytep image_data = *out_pixels;
    png_uint_32 row_bytes;
    png_bytepp row_pointers;
    int bit_depth;
    int color_type;
    png_color_16p image_background;
    double image_gamma;
    int row;

    if (file_name == 0) {
        *out_pixels = 0;
        return 0;
    }

    stream = fopen(file_name, "rb");
    if (stream == 0) {
        *out_pixels = 0;
        return 0;
    }

    if (file_offset != 0) {
        fseek(stream, file_offset, 0);
    }

    fread(signature, 1, 8, stream);
    if (png_check_sig(signature, 8) == 0) {
        *out_pixels = 0;
        return 0;
    }

    g_png_read_struct = png_create_read_struct("1.2.5", 0, 0, 0);
    if (g_png_read_struct == 0) {
        *out_pixels = 0;
        return 0;
    }

    g_png_info_struct = png_create_info_struct(g_png_read_struct);
    if (g_png_info_struct == 0) {
        png_destroy_read_struct(&g_png_read_struct, 0, 0);
        *out_pixels = 0;
        return 0;
    }

    if (setjmp(g_png_read_struct->jmpbuf) != 0) {
        png_destroy_read_struct(&g_png_read_struct, &g_png_info_struct, 0);
        *out_pixels = 0;
        return 0;
    }

    png_init_io(g_png_read_struct, stream);
    png_set_sig_bytes(g_png_read_struct, 8);
    png_read_info(g_png_read_struct, g_png_info_struct);

    png_get_IHDR(
        g_png_read_struct,
        g_png_info_struct,
        (png_uint_32*)out_width,
        (png_uint_32*)out_height,
        &bit_depth,
        &color_type,
        0,
        0,
        0);

    if (bit_depth == 16) {
        png_set_strip_16(g_png_read_struct);
    }
    if (color_type == 3) {
        png_set_expand(g_png_read_struct);
    }
    if (bit_depth < 8) {
        png_set_expand(g_png_read_struct);
    }
    if (png_get_valid(g_png_read_struct, g_png_info_struct, 0x10) != 0) {
        png_set_expand(g_png_read_struct);
    }
    if (color_type == 0 || color_type == 4) {
        png_set_gray_to_rgb(g_png_read_struct);
    }

    if (png_get_bKGD(g_png_read_struct, g_png_info_struct, &image_background) != 0) {
        png_set_background(g_png_read_struct, image_background, 2, 1, 1.0);
        background_rgb[0] = (png_byte)image_background->red;
        background_rgb[1] = (png_byte)image_background->green;
        background_rgb[2] = (png_byte)image_background->blue;
    } else {
        background_rgb = 0;
    }

    if (png_get_gAMA(g_png_read_struct, g_png_info_struct, &image_gamma) != 0) {
        png_set_gamma(g_png_read_struct, 2.2, image_gamma);
    }

    png_read_update_info(g_png_read_struct, g_png_info_struct);
    png_get_IHDR(
        g_png_read_struct,
        g_png_info_struct,
        (png_uint_32*)out_width,
        (png_uint_32*)out_height,
        &bit_depth,
        &color_type,
        0,
        0,
        0);

    row_bytes = png_get_rowbytes(g_png_read_struct, g_png_info_struct);
    *out_channels = png_get_channels(g_png_read_struct, g_png_info_struct);

    if (image_data != 0) {
        free(image_data);
        image_data = 0;
    }

    image_data = (png_bytep)malloc(*out_height * row_bytes);
    if (image_data == 0) {
        png_destroy_read_struct(&g_png_read_struct, &g_png_info_struct, 0);
        *out_pixels = 0;
        return 0;
    }

    *out_pixels = image_data;
    row_pointers = (png_bytepp)malloc(*out_height * sizeof(png_bytep));
    if (row_pointers == 0) {
        png_destroy_read_struct(&g_png_read_struct, &g_png_info_struct, 0);
        free(image_data);
        *out_pixels = 0;
        return 0;
    }

    for (row = 0; row < *out_height; ++row) {
        row_pointers[row] = image_data + row * row_bytes;
    }

    png_read_image(g_png_read_struct, row_pointers);
    png_read_end(g_png_read_struct, 0);
    free(row_pointers);
    fclose(stream);
    return 1;
}
