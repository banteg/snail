// render_camera @ 0x411fa0 (cdecl)

#include "direct3d_device8_view.h"
#include "game_root.h"
#include "render_pipeline_state.h"
#include "sprite.h"
#include "texture_registry.h"
#include "transform_matrix.h"
#include "vector3.h"

extern GameRoot* g_game; // data_4df904

TransformMatrix* __stdcall build_perspective_projection_matrix(
    TransformMatrix* matrix,
    float vertical_fov_radians,
    float aspect_ratio,
    float near_z,
    float far_z); // @ 0x450314
TransformMatrix* __stdcall build_camera_view_matrix(
    TransformMatrix* matrix,
    const Vector3* eye,
    const Vector3* target,
    const Vector3* up); // @ 0x451ad9

TransformMatrix* render_camera(
    float viewport_x,
    float viewport_y,
    float viewport_width,
    float viewport_height,
    float fov_degrees,
    TransformMatrix* camera_matrix,
    TransformMatrix* view_matrix,
    char draw_world,
    char post_sprite_pass)
{
    D3DViewport8 viewport;
    viewport.x = (unsigned int)viewport_x;
    viewport.y = (unsigned int)viewport_y;

    float pixel_width = viewport_width * 640.0f;
    viewport.width = (unsigned int)pixel_width;
    float pixel_height = viewport_height * 480.0f;
    viewport.height = (unsigned int)pixel_height;
    viewport.min_z = 0.0f;
    viewport.max_z = 1.0f;
    g_d3d_device->vtbl->SetViewport(g_d3d_device, &viewport);

    g_render_projection_near_z = 0.30000001f;
    g_render_projection_far_z = 52.0f;
    g_render_projection_param_a = fov_degrees * 0.017453292f;
    g_render_projection_param_b = pixel_width / pixel_height;

    TransformMatrix projection;
    build_perspective_projection_matrix(
        &projection,
        g_render_projection_param_a,
        g_render_projection_param_b,
        0.30000001f,
        52.0f);
    g_d3d_device->vtbl->SetTransform(g_d3d_device, 3, &projection);

    g_object_render_pass_filter = post_sprite_pass;

    Vector3 eye;
    Vector3 target;
    Vector3 up;
    eye.x = camera_matrix->position.x;
    eye.y = camera_matrix->position.y;
    eye.z = camera_matrix->position.z;
    target.x = camera_matrix->basis_forward.x + camera_matrix->position.x;
    target.y = camera_matrix->basis_forward.y + camera_matrix->position.y;
    target.z = camera_matrix->basis_forward.z + camera_matrix->position.z;
    up.x = camera_matrix->basis_up.x;
    up.y = camera_matrix->basis_up.y;
    up.z = camera_matrix->basis_up.z;

    TransformMatrix view;
    build_camera_view_matrix(&view, &eye, &target, &up);
    g_d3d_device->vtbl->SetTransform(g_d3d_device, 2, &view);

    g_d3d_device->vtbl->SetRenderState(g_d3d_device, 7, 1);
    g_d3d_device->vtbl->SetRenderState(g_d3d_device, 14, 1);
    g_d3d_device->vtbl->SetRenderState(g_d3d_device, 23, 4);

    if (draw_world != 0 && g_game->fog_enabled != 0) {
        float fog_start = g_game->fog_start;
        float fog_end = g_game->fog_end;
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 28, 1);

        tColourSmall packed_fog;
        packed_fog.noop_this_constructor();
        packed_fog.pack_color_rgba_u8(&g_game->fog_color);
        packed_fog.a = 0;
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 34, *(int*)&packed_fog);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 140, 3);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 36, *(int*)&fog_start);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 37, *(int*)&fog_end);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 38, *(int*)&g_game->fog_density);
    } else {
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 28, 0);
    }

    g_render_camera_source_matrix = camera_matrix;
    g_render_camera_view_matrix = view_matrix;
    g_current_texture_ref = 0;
    return view_matrix;
}
