// update_loading_screen @ 0x418e80 (thiscall)

#include "direct3d_device8_view.h"
#include "loading_bar.h"
#include "loading_vertex.h"
#include "object_render_types.h"
#include "runtime_config.h"

int present_backbuffer(); // @ 0x413520

void LoadingBar::update_loading_screen()
{
    int result = active;
    if (active != 0) {
        ++last_loading_budget;

        int budget = g_runtime_config.last_loading_budget;
        if (budget == 0) {
            budget = 1;
            g_runtime_config.last_loading_budget = 1;
        }

        int percent = (last_loading_budget * 100) / budget;
        if (percent < 0) {
            percent = 0;
        } else if (percent > 100) {
            percent = 100;
        }
        int clamped_percent = percent;

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

            vertices[0].x = 192.0f;
            vertices[0].y = 289.0f;
            vertices[0].z = 0.0f;
            vertices[0].u = 0.0f;
            vertices[0].v = 0.0f;

            float x_end = bar_percent * 2.5599999f + 192.0f;
            vertices[1].x = x_end;
            vertices[1].y = 289.0f;
            vertices[1].z = 0.0f;
            float u_end;
            vertices[1].u = u_end = bar_percent * 0.0099999998f;
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
}
