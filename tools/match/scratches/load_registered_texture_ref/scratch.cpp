// load_registered_texture_ref @ 0x412a70 (cdecl)

#include "texture_registry.h"
#include "tga_image_view.h"

extern Direct3DDevice8* g_d3d_device; // data_502fec

char archive_or_file_exists(char* path, char force_filesystem); // @ 0x430fd0
char* load_file_bytes(char* file_name, int* out_size); // @ 0x431520
char is_archive_index_loaded(); // @ 0x431a80
char* get_archive_data_base(); // @ 0x431a90
char* load_file_bytes_from_archive_or_fs(char* file_name, char* buffer, int* out_size);
char* load_file_bytes_fixed_size_from_archive_or_fs(char* path, char* out_buffer,
    int byte_count);
int report_warningf(char* format, ...); // @ 0x431d10
int report_errorf(char* format, ...); // @ 0x431cc0

extern "C" int __stdcall D3DXCreateTextureFromFileInMemoryEx(Direct3DDevice8* device,
    void* src_data, unsigned int src_data_size, unsigned int width, unsigned int height,
    unsigned int mip_levels, unsigned int usage, unsigned int format, unsigned int pool,
    unsigned int filter, unsigned int mip_filter, unsigned int color_key, void* src_info,
    void* palette, Direct3DTexture8** texture);
extern "C" int __stdcall D3DXCreateTextureFromFileExA(Direct3DDevice8* device, char* path,
    unsigned int width, unsigned int height, unsigned int mip_levels, unsigned int usage,
    unsigned int format, unsigned int pool, unsigned int filter, unsigned int mip_filter,
    unsigned int color_key, void* src_info, void* palette, Direct3DTexture8** texture);
extern "C" int __stdcall D3DXCreateTextureFromFileA(
    Direct3DDevice8* device, char* path, Direct3DTexture8** texture);

#define TEXTURE_FIELD(offset) ((char*)&g_texture_refs.entries[0] + texture_offset + (offset))

void load_registered_texture_ref(int texture_index, int unused_legacy_mode)
{
    int texture_offset = texture_index * sizeof(TextureRef);
    if ((*(unsigned int*)TEXTURE_FIELD(0) & 0x8000) != 0) {
        return;
    }

    char* path = TEXTURE_FIELD(0x0c);
    if (archive_or_file_exists(path, 0) == 0) {
        report_warningf("Texture File Missing using Debug.tga (%s)", path);
        D3DXCreateTextureFromFileA(
            g_d3d_device, "Sprites/Debug.tga", &g_d3d_texture_slots[texture_index]);
        return;
    }

    if ((*(unsigned int*)TEXTURE_FIELD(0) & 0x20) != 0) {
        *(void**)TEXTURE_FIELD(0x98) = load_file_bytes(path, 0);
    } else {
        *(void**)TEXTURE_FIELD(0x98) = 0;
    }

    TgaImageView tga_header;
    load_file_bytes_fixed_size_from_archive_or_fs(
        path, (char*)&tga_header, sizeof(tga_header));

    unsigned int color_key =
        (tga_header.bits_per_pixel == 0x20) ? 0x00ffffff : 0;
    int texture_result;
    if (is_archive_index_loaded() != 0) {
        char* archive_base = get_archive_data_base();
        int byte_count;
        load_file_bytes_from_archive_or_fs(path, archive_base, &byte_count);
        texture_result = D3DXCreateTextureFromFileInMemoryEx(g_d3d_device, archive_base,
            byte_count, 0, 0, *(int*)TEXTURE_FIELD(0xa0), 0, 21, 1, 3, 3, color_key, 0, 0,
            &g_d3d_texture_slots[texture_index]);
    } else {
        texture_result = D3DXCreateTextureFromFileExA(g_d3d_device, path, 0, 0,
            *(int*)TEXTURE_FIELD(0xa0), 0, 21, 1, 3, 3, color_key, 0, 0,
            &g_d3d_texture_slots[texture_index]);
    }

    if (texture_result < 0) {
        report_errorf("Failed to Create DirectX Texture %s", path);
        D3DXCreateTextureFromFileA(
            g_d3d_device, "Sprites/Debug.tga", &g_d3d_texture_slots[texture_index]);
        return;
    }

    g_d3d_device->vtbl->SetTexture(g_d3d_device, 0, g_d3d_texture_slots[texture_index]);
    g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 16, 3);
    g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 17, 3);

    if (tga_header.bits_per_pixel == 0x20) {
        *(unsigned int*)TEXTURE_FIELD(0) |= 0x10000;
        g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 1, 4);
        g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 2, 2);
        g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 3, 0);
        g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 4, 4);
        g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 5, 2);
        g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 6, 0);
    }

    int width = tga_header.width;
    int height = tga_header.height;
    *(int*)TEXTURE_FIELD(4) = width;
    *(int*)TEXTURE_FIELD(8) = height;
    g_estimated_texture_vram_bytes += width * height * sizeof(unsigned int);
}
