// update_loading_screen @ 0x418e80 (thiscall, ret)

#include "loading_vertex.h"
#include "vertex_buffer_view.h"

class Direct3DDevice8;
class Direct3DTexture8;

struct RendererVertexBufferResource {
    char unknown_00[0x08];
    VertexBuffer* vertex_buffer; // +0x08
};

struct Direct3DDevice8Vtbl {
    char unknown_000[0x88];
    int (__stdcall* BeginScene)(Direct3DDevice8* self);
    int (__stdcall* EndScene)(Direct3DDevice8* self);
    int (__stdcall* Clear)(Direct3DDevice8* self, unsigned int count, void* rects,
        unsigned int flags, unsigned int color, float z, unsigned int stencil);
    char unknown_094[0xf4 - 0x94];
    int (__stdcall* SetTexture)(Direct3DDevice8* self, unsigned int stage,
        Direct3DTexture8* texture);
    char unknown_0f8[0xfc - 0xf8];
    int (__stdcall* SetTextureStageState)(Direct3DDevice8* self, unsigned int stage,
        unsigned int type, unsigned int value);
    char unknown_100[0x118 - 0x100];
    int (__stdcall* DrawPrimitive)(Direct3DDevice8* self, unsigned int primitive_type,
        unsigned int start_vertex, unsigned int primitive_count);
    char unknown_11c[0x130 - 0x11c];
    int (__stdcall* SetVertexShader)(Direct3DDevice8* self, unsigned int shader);
    char unknown_134[0x14c - 0x134];
    int (__stdcall* SetStreamSource)(Direct3DDevice8* self, unsigned int stream,
        VertexBuffer* buffer, unsigned int stride);
};

class Direct3DDevice8 {
public:
    Direct3DDevice8Vtbl* vtbl;
};

class LoadingScreen {
public:
    int update_loading_screen();

    int active;           // +0x00
    int previous_percent; // +0x04
    int last_loading_budget; // +0x08
};

extern int g_last_loading_budget; // data_4df9c4
extern Direct3DDevice8* g_d3d_device; // data_502fec
extern Direct3DTexture8* g_loading_background_texture; // data_503288
extern RendererVertexBufferResource* g_loading_background_vertex_buffer; // data_503284
extern Direct3DTexture8* g_loading_bar_on_texture; // data_503280
extern RendererVertexBufferResource* g_loading_bar_vertex_buffer; // data_5032a4

int present_backbuffer(); // sub_413520

int LoadingScreen::update_loading_screen()
{
    int result = active;
    if (active != 0) {
        ++last_loading_budget;

        int budget = g_last_loading_budget;
        if (budget == 0) {
            budget = 1;
            g_last_loading_budget = 1;
        }

        int percent = (last_loading_budget * 100) / budget;
        int clamped_percent = percent;
        if (percent < 0) {
            clamped_percent = 0;
        } else if (percent > 100) {
            clamped_percent = 100;
        }

        result = clamped_percent - previous_percent;
        if (result >= 1) {
            float bar_percent = (float)clamped_percent * 0.92000002f;
            if (clamped_percent > 98) {
                bar_percent = 100.0f;
            }

            g_d3d_device->vtbl->Clear(g_d3d_device, 0, 0, 2, 0xff000000, 1.0f, 0);
            g_d3d_device->vtbl->BeginScene(g_d3d_device);
            g_d3d_device->vtbl->SetTexture(g_d3d_device, 0, g_loading_background_texture);
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 13, 3);
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 14, 3);
            g_d3d_device->vtbl->SetStreamSource(
                g_d3d_device, 0, g_loading_background_vertex_buffer->vertex_buffer,
                sizeof(LoadingVertex));
            g_d3d_device->vtbl->SetVertexShader(g_d3d_device, 0x102);
            g_d3d_device->vtbl->DrawPrimitive(g_d3d_device, 6, 0, 2);

            LoadingVertex* vertices;
            g_loading_bar_vertex_buffer->vertex_buffer->vtbl->Lock(
                g_loading_bar_vertex_buffer->vertex_buffer, 0, sizeof(LoadingVertex) * 4,
                (void**)&vertices, 0);

            float x_end = bar_percent * 2.5599999f + 192.0f;

            vertices[0].x = 192.0f;
            vertices[0].y = 289.0f;
            vertices[0].z = 0.0f;
            vertices[0].u = 0.0f;
            vertices[0].v = 0.0f;

            vertices[1].x = x_end;
            float u_end = bar_percent * 0.0099999998f;
            vertices[1].y = 289.0f;
            vertices[1].z = 0.0f;
            vertices[1].u = u_end;
            vertices[1].v = 0.0f;

            vertices[2].x = x_end;
            vertices[2].y = 321.0f;
            vertices[2].z = 0.0f;
            vertices[2].u = u_end;
            vertices[2].v = 1.0f;

            vertices[3].x = 192.0f;
            vertices[3].y = 321.0f;
            vertices[3].z = 0.0f;
            vertices[3].u = 0.0f;
            vertices[3].v = 1.0f;

            g_loading_bar_vertex_buffer->vertex_buffer->vtbl->Unlock(
                g_loading_bar_vertex_buffer->vertex_buffer);
            g_d3d_device->vtbl->SetTexture(g_d3d_device, 0, g_loading_bar_on_texture);
            g_d3d_device->vtbl->SetStreamSource(
                g_d3d_device, 0, g_loading_bar_vertex_buffer->vertex_buffer,
                sizeof(LoadingVertex));
            g_d3d_device->vtbl->SetVertexShader(g_d3d_device, 0x102);
            g_d3d_device->vtbl->DrawPrimitive(g_d3d_device, 6, 0, 2);
            g_d3d_device->vtbl->EndScene(g_d3d_device);
            result = present_backbuffer();
            previous_percent = clamped_percent;
        }
    }
    return result;
}
