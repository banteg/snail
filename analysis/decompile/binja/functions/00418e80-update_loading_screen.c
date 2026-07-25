/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_loading_screen @ 0x418e80 */

00418e8e        if (loading_bar->active == 0)
00418e8e        return
00418e98        loading_bar->last_loading_budget += 1
00418e9b        int32_t last_loading_budget = g_runtime_config.last_loading_budget
00418ea3        if (last_loading_budget == 0)
00418ea5        last_loading_budget = 1
00418eaa        g_runtime_config.last_loading_budget = 1
00418ebf        int32_t data_1 = divs.dp.d(sx.q(loading_bar->last_loading_budget * 0x64), last_loading_budget)
00418ec3        int32_t data = data_1
00418ec7        if (data_1 s< 0)
00418ec9        data_1 = 0
00418ed7        data = data_1
00418ed0        if (data_1 s> 0x64)
00418ed2        data_1 = 0x64
00418ed7        data = data_1
00418ee5        if (data_1 - loading_bar->previous_percent s< 1)
00418ee5        return
00418ef8        float var_4_1 = fconvert.s(float.t(data) * fconvert.t(0.920000017f))
00418efc        if (data_1 s> 0x62)
00418efe        var_4_1 = 100f
00418f06        struct Direct3DDevice8* device = g_direct3d_renderer.device
00418f1d        device->vtbl->Clear(device, 0, nullptr, 2, 0xff000000, 1f, 0)
00418f23        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
00418f2b        device_1->vtbl->BeginScene(device_1)
00418f31        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
00418f41        device_2->vtbl->SetTexture(device_2, 0, g_loading_background_texture)
00418f47        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
00418f54        device_3->vtbl->SetTextureStageState(device_3, 0, 0xd, 3)
00418f5a        struct Direct3DDevice8* device_4 = g_direct3d_renderer.device
00418f67        device_4->vtbl->SetTextureStageState(device_4, 0, 0xe, 3)
00418f73        struct Direct3DDevice8* device_5 = g_direct3d_renderer.device
00418f82        device_5->vtbl->SetStreamSource(device_5, 0, g_loading_background_vertex_buffer->vertex_buffer, 0x14)
00418f88        struct Direct3DDevice8* device_6 = g_direct3d_renderer.device
00418f95        device_6->vtbl->SetVertexShader(device_6, 0x102)
00418f9b        struct Direct3DDevice8* device_7 = g_direct3d_renderer.device
00418fa8        device_7->vtbl->DrawPrimitive(device_7, 6, 0, 2)
00418fb9        struct ObjectVertexBuffer* vertex_buffer = g_loading_bar_vertex_buffer->vertex_buffer
00418fc2        vertex_buffer->vtbl->Lock(vertex_buffer, 0, 0x50, &data, 0)
00418fcd        *data = 0x43400000
00418fe2        *(data + 4) = 0x43908000
00418fe9        long double x87_r7_5 = fconvert.t(var_4_1) * fconvert.t(2.55999994f) + fconvert.t(192f)
00418fef        *(data + 8) = 0
00418ff6        *(data + 0xc) = 0
00418fff        *(data + 0x10) = 0
00419006        *(data + 0x14) = fconvert.s(x87_r7_5)
00419011        long double x87_r6_3 = fconvert.t(var_4_1) * fconvert.t(0.00999999978f)
00419017        *(data + 0x18) = 0x43908000
0041901e        *(data + 0x1c) = 0
00419025        float var_4_2 = fconvert.s(x87_r6_3)
00419029        *(data + 0x20) = fconvert.s(x87_r6_3)
00419030        *(data + 0x24) = 0
00419037        *(data + 0x28) = fconvert.s(x87_r7_5)
00419047        *(data + 0x2c) = 0x43a08000
0041904e        *(data + 0x30) = 0
00419055        *(data + 0x34) = fconvert.s(fconvert.t(var_4_2))
0041905c        *(data + 0x38) = 0x3f800000
00419067        *(data + 0x3c) = 0x43400000
00419072        *(data + 0x40) = 0x43a08000
00419079        *(data + 0x44) = 0
00419080        *(data + 0x48) = 0
00419087        *(data + 0x4c) = 0x3f800000
00419093        struct ObjectVertexBuffer* vertex_buffer_1 = g_loading_bar_vertex_buffer->vertex_buffer
00419099        vertex_buffer_1->vtbl->Unlock(vertex_buffer_1)
0041909c        struct Direct3DDevice8* device_8 = g_direct3d_renderer.device
004190ac        device_8->vtbl->SetTexture(device_8, 0, g_loading_bar_on_texture)
004190b8        struct Direct3DDevice8* device_9 = g_direct3d_renderer.device
004190c7        device_9->vtbl->SetStreamSource(device_9, 0, g_loading_bar_vertex_buffer->vertex_buffer, 0x14)
004190cd        struct Direct3DDevice8* device_10 = g_direct3d_renderer.device
004190da        device_10->vtbl->SetVertexShader(device_10, 0x102)
004190e0        struct Direct3DDevice8* device_11 = g_direct3d_renderer.device
004190ed        device_11->vtbl->DrawPrimitive(device_11, 6, 0, 2)
004190f3        struct Direct3DDevice8* device_12 = g_direct3d_renderer.device
004190fb        device_12->vtbl->EndScene(device_12)
00419101        present_backbuffer()
00419106        loading_bar->previous_percent = data_1
0041910f        return
