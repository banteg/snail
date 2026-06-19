// initialize_loading_screen @ 0x418b50 (thiscall, ret)

#include "loading_screen.h"
#include "loading_vertex.h"
#include "object_render_types.h"
#include "render_buffer_factories.h"

class Direct3DDevice8;
class Direct3DTexture8;

struct Direct3DDevice8Vtbl {
    char unknown_000[0xf4];
    int (__stdcall* SetTexture)(Direct3DDevice8* self, unsigned int stage,
        Direct3DTexture8* texture);
    char unknown_0f8[0xfc - 0xf8];
    int (__stdcall* SetTextureStageState)(Direct3DDevice8* self, unsigned int stage,
        unsigned int type, unsigned int value);
};

class Direct3DDevice8 {
public:
    Direct3DDevice8Vtbl* vtbl;
};

extern int g_last_loading_budget; // data_4df9c4
extern Direct3DDevice8* g_d3d_device; // data_502fec
extern Direct3DTexture8* g_loading_background_texture; // data_503288
extern ObjectRenderBuffers* g_loading_background_vertex_buffer; // data_503284
extern Direct3DTexture8* g_loading_bar_on_texture; // data_503280
extern ObjectRenderBuffers* g_loading_bar_vertex_buffer; // data_5032a4

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

char is_archive_index_loaded(); // @ 0x431a80
char* get_archive_data_base(); // @ 0x431a90
char* load_file_bytes_from_archive_or_fs(char* file_name, char* buffer, int* out_size);
int report_errorf(char* format, ...);
int begin_overlay_render_state();

int LoadingScreen::initialize_loading_screen()
{
    g_last_loading_budget = 1276;

    int texture_result;
    int byte_count;
    if (is_archive_index_loaded() != 0) {
        char* archive_base = get_archive_data_base();
        load_file_bytes_from_archive_or_fs("Sprites/Loading.tga", archive_base, &byte_count);
        texture_result = D3DXCreateTextureFromFileInMemoryEx(g_d3d_device, archive_base,
            byte_count, 0, 0, 1, 0, 21, 1, 3, 3, 0xff00ff00, 0, 0,
            &g_loading_background_texture);
    } else {
        texture_result = D3DXCreateTextureFromFileExA(g_d3d_device, "Sprites/Loading.tga",
            0, 0, 1, 0, 21, 1, 3, 3, 0xff00ff00, 0, 0, &g_loading_background_texture);
    }

    if (texture_result < 0) {
        report_errorf("Failed to Create DirectX Texture Sprites/Loading.tga");
        D3DXCreateTextureFromFileA(g_d3d_device, "Sprites/Debug.tga",
            &g_loading_background_texture);
    }

    g_d3d_device->vtbl->SetTexture(g_d3d_device, 0, g_loading_background_texture);
    g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 16, 3);
    g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 17, 3);
    g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 13, 3);
    g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 14, 3);

    if (is_archive_index_loaded() != 0) {
        char* archive_base = get_archive_data_base();
        load_file_bytes_from_archive_or_fs(
            "Sprites/LoadingBarOn.tga", archive_base, &byte_count);
        texture_result = D3DXCreateTextureFromFileInMemoryEx(g_d3d_device, archive_base,
            byte_count, 0, 0, 1, 0, 21, 1, 3, 3, 0xff00ff00, 0, 0,
            &g_loading_bar_on_texture);
    } else {
        texture_result = D3DXCreateTextureFromFileExA(g_d3d_device,
            "Sprites/LoadingBarOn.tga", 0, 0, 1, 0, 21, 1, 3, 3, 0xff00ff00, 0, 0,
            &g_loading_bar_on_texture);
    }

    if (texture_result < 0) {
        report_errorf("Failed to Create DirectX Texture Sprites/LoadingBarOn.tga");
        D3DXCreateTextureFromFileA(g_d3d_device, "Sprites/Debug.tga",
            &g_loading_bar_on_texture);
    }

    g_d3d_device->vtbl->SetTexture(g_d3d_device, 0, g_loading_bar_on_texture);
    g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 16, 3);
    g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 17, 3);

    g_loading_background_vertex_buffer =
        g_direct3d_renderer.create_vertex_buffer(4, 0x102);
    g_loading_bar_vertex_buffer = g_direct3d_renderer.create_vertex_buffer(4, 0x102);

    LoadingVertex* vertices;
    g_loading_background_vertex_buffer->vertex_buffer->vtbl->Lock(
        g_loading_background_vertex_buffer->vertex_buffer, 0, sizeof(LoadingVertex) * 4,
        (void**)&vertices, 0);

    vertices[0].x = 0.0f;
    vertices[0].y = 0.0f;
    vertices[0].z = 0.0f;
    vertices[0].u = 0.0f;
    vertices[0].v = 0.0f;

    vertices[1].x = 640.0f;
    vertices[1].y = 0.0f;
    vertices[1].z = 0.0f;
    vertices[1].u = 1.0f;
    vertices[1].v = 0.0f;

    vertices[2].x = 640.0f;
    vertices[2].y = 480.0f;
    vertices[2].z = 0.0f;
    vertices[2].u = 1.0f;
    vertices[2].v = 1.0f;

    vertices[3].x = 0.0f;
    vertices[3].y = 480.0f;
    vertices[3].z = 0.0f;
    vertices[3].u = 0.0f;
    vertices[3].v = 1.0f;

    g_loading_bar_vertex_buffer->vertex_buffer->vtbl->Unlock(
        g_loading_bar_vertex_buffer->vertex_buffer);
    int result = begin_overlay_render_state();
    last_loading_budget = 0;
    previous_percent = 0;
    active = 1;
    return result;
}
