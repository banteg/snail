/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* export: isolated copy with manifest symbols applied */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: begin_overlay_render_state @ 0x411e10 */

00411e16        struct Direct3DDevice8* device = g_direct3d_renderer.device
00411e25        device->vtbl->GetTransform(device, 3, &data_503220)
00411e2b        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
00411e3a        device_1->vtbl->GetTransform(device_1, 2, &data_503178)
00411e40        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
00411e4e        device_2->vtbl->SetTextureStageState(device_2, 0, 0xd, 3)
00411e54        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
00411e62        device_3->vtbl->SetTextureStageState(device_3, 0, 0xe, 3)
00411e7e        void matrix_1
00411e7e        build_orthographic_projection_matrix(&matrix_1, 640f, -480f, 0f, 1f)
00411e83        struct Direct3DDevice8* device_4 = g_direct3d_renderer.device
00411e9c        struct TransformMatrix matrix
00411e9c        __builtin_memset(&matrix.position, 0, 0xc)
00411ea4        matrix.basis_forward_w = 0
00411eac        matrix.basis_forward.y = 0
00411eb4        matrix.basis_forward.x = 0
00411ebc        matrix.basis_up_w = 0
00411ec4        matrix.basis_up.z = 0
00411ecc        matrix.basis_up.x = 0
00411ed4        matrix.basis_right_w = 0
00411edc        matrix.basis_right.z = 0
00411ee4        matrix.basis_right.y = 0
00411eec        matrix.position_w = 0x3f800000
00411ef4        matrix.basis_forward.z = 0x3f800000
00411efc        matrix.basis_up.y = 0x3f800000
00411f04        matrix.basis_right.x = 0x3f800000
00411f12        device_4->vtbl->SetTransform(device_4, 3, &matrix_1)
00411f18        struct Direct3DDevice8* device_5 = g_direct3d_renderer.device
00411f2a        device_5->vtbl->SetTransform(device_5, 0x100, &matrix)
00411f41        D3DXMatrixTranslation(&matrix, 0xc3a04ccd, 0xc370999a, 0)
00411f46        struct Direct3DDevice8* device_6 = g_direct3d_renderer.device
00411f55        device_6->vtbl->SetTransform(device_6, 2, &matrix)
00411f5b        struct Direct3DDevice8* device_7 = g_direct3d_renderer.device
00411f67        device_7->vtbl->SetRenderState(device_7, 7, 0)
00411f6d        struct Direct3DDevice8* device_8 = g_direct3d_renderer.device
00411f79        device_8->vtbl->SetRenderState(device_8, 0xe, 0)
00411f7f        struct Direct3DDevice8* device_9 = g_direct3d_renderer.device
00411f9a        return device_9->vtbl->SetRenderState(device_9, 0x89, 0)
