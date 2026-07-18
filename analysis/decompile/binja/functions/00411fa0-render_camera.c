/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: render_camera @ 0x411fa0 */

00411fae        int32_t eax
00411fae        int16_t x87control
00411fae        int16_t x87control_1
00411fae        eax, x87control_1 = ftol(x87control, fconvert.t(viewport_x))
00411fba        struct D3DViewport8 viewport
00411fba        viewport.x = eax
00411fbe        int32_t eax_1
00411fbe        int16_t x87control_2
00411fbe        eax_1, x87control_2 = ftol(x87control_1, fconvert.t(viewport_y))
00411fca        long double x87_r7_3 = fconvert.t(viewport_width) * fconvert.t(640f)
00411fd0        viewport.y = eax_1
00411fd4        struct ColorBGRA8 out = fconvert.s(x87_r7_3)
00411fd8        int32_t eax_2
00411fd8        int16_t x87control_3
00411fd8        eax_2, x87control_3 = ftol(x87control_2, x87_r7_3)
00411fe4        long double x87_r7_5 = fconvert.t(viewport_height) * fconvert.t(480f)
00411fea        viewport.width = eax_2
00411fee        float var_c4 = fconvert.s(x87_r7_5)
00411ff7        viewport.height = ftol(x87control_3, x87_r7_5)
00411ffb        struct Direct3DDevice8* device = g_direct3d_renderer.device
00412004        viewport.min_z = 0
0041200c        viewport.max_z = 0x3f800000
00412018        device->vtbl->SetViewport(device, &viewport)
00412039        g_render_projection_near_z = 0.300000012f
00412043        g_render_projection_far_z = 52f
0041204d        g_render_projection_param_a = fconvert.s(fconvert.t(fov_degrees) * fconvert.t(0.0174532924f))
0041205b        float render_projection_param_a_1 = g_render_projection_param_a
00412061        g_render_projection_param_b = fconvert.s(fconvert.t(out) / fconvert.t(var_c4))
0041206f        struct TransformMatrix matrix
0041206f        build_perspective_projection_matrix(&matrix, render_projection_param_a_1, g_render_projection_param_b, 0.300000012f, 52f)
00412074        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
00412083        device_1->vtbl->SetTransform(device_1, 3, &matrix)
00412097        g_object_render_pass_filter = post_sprite_pass
004120ab        struct Vec3 eye
004120ab        eye.x = camera_matrix->position.x
004120b2        eye.y = camera_matrix->position.y
004120b6        struct Vec3 target
004120b6        target.x = fconvert.s(fconvert.t(camera_matrix->basis_forward.x) + fconvert.t(camera_matrix->position.x))
004120c3        eye.z = camera_matrix->position.z
004120ca        struct Vec3 up
004120ca        up.x = camera_matrix->basis_up.x
004120ce        up.y = camera_matrix->basis_up.y
004120d6        target.y = fconvert.s(fconvert.t(camera_matrix->basis_forward.y) + fconvert.t(camera_matrix->position.y))
004120e0        up.z = camera_matrix->basis_up.z
004120f5        target.z = fconvert.s(fconvert.t(camera_matrix->basis_forward.z) + fconvert.t(camera_matrix->position.z))
004120fb        struct TransformMatrix matrix_1
004120fb        build_camera_view_matrix(&matrix_1, &eye, &target, &up)
00412100        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
00412112        device_2->vtbl->SetTransform(device_2, 2, &matrix_1)
00412118        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
00412124        device_3->vtbl->SetRenderState(device_3, 7, 1)
0041212a        struct Direct3DDevice8* device_4 = g_direct3d_renderer.device
00412136        device_4->vtbl->SetRenderState(device_4, 0xe, 1)
0041213c        struct Direct3DDevice8* device_5 = g_direct3d_renderer.device
00412148        device_5->vtbl->SetRenderState(device_5, 0x17, 4)
00412157        struct GameRoot* game_base_1
00412157        if (draw_world != 0)
0041215d        game_base_1 = g_game_base
00412167        int32_t state
00412167        int32_t fog_density
00412167        struct Direct3DDevice8* device_11
00412167        struct Direct3DDevice8Vtbl* vtbl
00412167        if (draw_world == 0 || game_base_1->fog_enabled == 0)
00412217        device_11 = g_direct3d_renderer.device
0041221c        fog_density = 0
0041221e        state = 0x1c
00412220        vtbl = device_11->vtbl
0041216d        float fog_start = game_base_1->fog_start
00412170        float fog_end = game_base_1->fog_end
00412173        struct Direct3DDevice8* device_6 = g_direct3d_renderer.device
00412187        device_6->vtbl->SetRenderState(device_6, 0x1c, 1)
004121a4        pack_color_rgba_u8(&out, &g_game_base->fog_color)
004121a9        struct Direct3DDevice8* device_7 = g_direct3d_renderer.device
004121ae        out.a = 0
004121b3        int32_t value
004121b3        value.b = out.b
004121b3        value:1.b = out.g
004121b3        value:2.b = out.r
004121b3        value:3.b = out.a
004121bd        device_7->vtbl->SetRenderState(device_7, 0x22, value)
004121c3        struct Direct3DDevice8* device_8 = g_direct3d_renderer.device
004121d2        device_8->vtbl->SetRenderState(device_8, 0x8c, 3)
004121d8        struct Direct3DDevice8* device_9 = g_direct3d_renderer.device
004121e7        device_9->vtbl->SetRenderState(device_9, 0x24, fog_start)
004121ed        struct Direct3DDevice8* device_10 = g_direct3d_renderer.device
004121fc        device_10->vtbl->SetRenderState(device_10, 0x25, fog_end)
00412208        device_11 = g_direct3d_renderer.device
00412210        vtbl = device_11->vtbl
00412212        fog_density = g_game_base->fog_density
00412213        state = 0x26
00412223        vtbl->SetRenderState(device_11, state, fog_density)
00412230        g_render_camera_source_matrix = camera_matrix
00412236        g_render_camera_view_matrix = view_matrix
0041223b        g_current_texture_ref = nullptr
0041224c        return view_matrix
