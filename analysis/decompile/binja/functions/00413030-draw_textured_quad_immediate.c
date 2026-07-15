/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_textured_quad_immediate @ 0x413030 */

00413030        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
00413041        device_3->vtbl->SetRenderState(device_3, 0x16, 1)
0041304c        bind_texture_ref(texture)
00413056        set_immediate_blend_mode(blend_mode)
00413070        struct ColorBGRA8 out
00413070        pack_color_rgba_u8(&out, color)
0041307e        struct ObjectVertexBuffer* vertex_buffer = g_direct3d_renderer.renderer_state->vertex_buffer
0041308c        float* data
0041308c        int32_t ecx_5 = vertex_buffer->vtbl->Lock(vertex_buffer, 0, 0x60, &data, 0)
0041308f        long double x87_r7 = fconvert.t(rotation)
00413093        long double temp0 = fconvert.t(0f)
00413093        x87_r7 - temp0
00413099        long double x87_r7_1 = fconvert.t(width)
004130a2        if ((((x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) == 0)
004132b1        long double x87_r7_27 = x87_r7_1 * fconvert.t(0.5f)
004132b7        int32_t var_14_2 = ecx_5
004132be        x0 = fconvert.s(x87_r7_27 + fconvert.t(x0))
004132c6        long double x87_r6_12 = fconvert.t(height) * fconvert.t(0.5f)
004132d4        y0 = fconvert.s(x87_r6_12 + fconvert.t(y0))
004132d8        long double x87_r6_14 = fconvert.t(fconvert.s(x87_r6_12))
004132fd        height = fconvert.s(square_root(fconvert.s(x87_r6_14 * x87_r6_14 + x87_r7_27 * x87_r7_27)) * fconvert.t(1.41400003f))
0041330b        width = fconvert.s(sine(rotation) * fconvert.t(height))
00413314        long double x87_r7_34 = cosine(rotation) * fconvert.t(height)
00413327        *data = fconvert.s(fconvert.t(width) + fconvert.t(x0))
00413333        data[1] = fconvert.s(x87_r7_34 + fconvert.t(y0))
0041333e        data[2] = 0
00413345        data[4] = fconvert.s(fconvert.t(u0))
00413350        data[5] = fconvert.s(fconvert.t(v0))
00413357        int32_t edx_22
00413357        edx_22.b = out.b
00413357        edx_22:1.b = out.g
00413357        edx_22:2.b = out.r
00413357        edx_22:3.b = out.a
00413361        data[3] = edx_22
00413368        data[6] = fconvert.s(fconvert.t(x0) - x87_r7_34)
00413377        data[7] = fconvert.s(fconvert.t(width) + fconvert.t(y0))
00413382        data[8] = 0
00413389        data[0xa] = fconvert.s(fconvert.t(u1))
00413394        data[0xb] = fconvert.s(fconvert.t(v0))
0041339b        int32_t eax_26
0041339b        eax_26.b = out.b
0041339b        eax_26:1.b = out.g
0041339b        eax_26:2.b = out.r
0041339b        eax_26:3.b = out.a
004133a7        data[9] = eax_26
004133ae        data[0xc] = fconvert.s(fconvert.t(x0) - fconvert.t(width))
004133bb        data[0xd] = fconvert.s(fconvert.t(y0) - x87_r7_34)
004133c2        data[0xe] = 0
004133cd        data[0x10] = fconvert.s(fconvert.t(u1))
004133d8        data[0x11] = fconvert.s(fconvert.t(v1))
004133df        int32_t ecx_31
004133df        ecx_31.b = out.b
004133df        ecx_31:1.b = out.g
004133df        ecx_31:2.b = out.r
004133df        ecx_31:3.b = out.a
004133e7        data[0xf] = ecx_31
004133ee        data[0x12] = fconvert.s(x87_r7_34 + fconvert.t(x0))
004133fd        data[0x13] = fconvert.s(fconvert.t(y0) - fconvert.t(width))
00413408        data[0x14] = 0
0041340f        data[0x16] = fconvert.s(fconvert.t(u0))
0041341a        data[0x17] = fconvert.s(fconvert.t(v1))
00413421        int32_t ecx_33
00413421        ecx_33.b = out.b
00413421        ecx_33:1.b = out.g
00413421        ecx_33:2.b = out.r
00413421        ecx_33:3.b = out.a
00413425        data[0x15] = ecx_33
004130a8        long double temp1_1 = fconvert.t(0f)
004130a8        x87_r7_1 - temp1_1
004130ae        long double x87_r7_2 = fconvert.t(x0)
004130b7        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) == 0)
004131b9        *data = fconvert.s(x87_r7_2)
004131c3        data[1] = fconvert.s(fconvert.t(y0))
004131ce        data[2] = 0
004131d5        data[4] = fconvert.s(fconvert.t(u0))
004131e0        data[5] = fconvert.s(fconvert.t(v0))
004131eb        int32_t ecx_17
004131eb        ecx_17.b = out.b
004131eb        ecx_17:1.b = out.g
004131eb        ecx_17:2.b = out.r
004131eb        ecx_17:3.b = out.a
004131ef        long double x87_r7_22 = fconvert.t(x0) + fconvert.t(width)
004131f3        data[3] = ecx_17
004131fc        data[6] = fconvert.s(x87_r7_22)
00413207        data[7] = fconvert.s(fconvert.t(y0))
00413212        data[8] = 0
00413219        data[0xa] = fconvert.s(fconvert.t(u1))
00413224        data[0xb] = fconvert.s(fconvert.t(v0))
0041322b        int32_t edx_15
0041322b        edx_15.b = out.b
0041322b        edx_15:1.b = out.g
0041322b        edx_15:2.b = out.r
0041322b        edx_15:3.b = out.a
0041322f        data[9] = edx_15
00413236        data[0xc] = fconvert.s(x87_r7_22)
0041323d        long double x87_r7_24 = fconvert.t(y0) + fconvert.t(height)
00413247        data[0xd] = fconvert.s(x87_r7_24)
00413252        data[0xe] = 0
00413259        data[0x10] = fconvert.s(fconvert.t(u1))
00413264        data[0x11] = fconvert.s(fconvert.t(v1))
0041326b        int32_t eax_19
0041326b        eax_19.b = out.b
0041326b        eax_19:1.b = out.g
0041326b        eax_19:2.b = out.r
0041326b        eax_19:3.b = out.a
00413273        data[0xf] = eax_19
0041327a        data[0x12] = fconvert.s(fconvert.t(x0))
00413281        data[0x13] = fconvert.s(x87_r7_24)
0041328c        data[0x14] = 0
00413293        data[0x16] = fconvert.s(fconvert.t(u0))
0041329e        data[0x17] = fconvert.s(fconvert.t(v1))
004132a5        int32_t eax_21
004132a5        eax_21.b = out.b
004132a5        eax_21:1.b = out.g
004132a5        eax_21:2.b = out.r
004132a5        eax_21:3.b = out.a
004132a9        data[0x15] = eax_21
004130c1        *data = fconvert.s(x87_r7_2)
004130cb        data[1] = fconvert.s(fconvert.t(y0))
004130d6        data[2] = 0
004130dd        data[4] = fconvert.s(fconvert.t(u0))
004130e8        data[5] = fconvert.s(fconvert.t(v0))
004130ef        int32_t eax_5
004130ef        eax_5.b = out.b
004130ef        eax_5:1.b = out.g
004130ef        eax_5:2.b = out.r
004130ef        eax_5:3.b = out.a
004130f7        data[3] = eax_5
004130fe        data[6] = fconvert.s(fconvert.t(x1))
00413109        data[7] = fconvert.s(fconvert.t(y1))
00413114        data[8] = 0
0041311b        data[0xa] = fconvert.s(fconvert.t(u1))
00413126        data[0xb] = fconvert.s(fconvert.t(v0))
0041312d        int32_t ecx_10
0041312d        ecx_10.b = out.b
0041312d        ecx_10:1.b = out.g
0041312d        ecx_10:2.b = out.r
0041312d        ecx_10:3.b = out.a
00413135        data[9] = ecx_10
0041313c        data[0xc] = fconvert.s(fconvert.t(x2))
00413147        data[0xd] = fconvert.s(fconvert.t(y2))
00413152        data[0xe] = 0
00413159        data[0x10] = fconvert.s(fconvert.t(u1))
00413164        data[0x11] = fconvert.s(fconvert.t(v1))
0041316b        int32_t edx_8
0041316b        edx_8.b = out.b
0041316b        edx_8:1.b = out.g
0041316b        edx_8:2.b = out.r
0041316b        edx_8:3.b = out.a
00413173        data[0xf] = edx_8
0041317a        data[0x12] = fconvert.s(fconvert.t(x3))
00413185        data[0x13] = fconvert.s(fconvert.t(y3))
00413190        data[0x14] = 0
00413197        data[0x16] = fconvert.s(fconvert.t(u0))
004131a2        data[0x17] = fconvert.s(fconvert.t(v1))
004131a9        int32_t edx_10
004131a9        edx_10.b = out.b
004131a9        edx_10:1.b = out.g
004131a9        edx_10:2.b = out.r
004131a9        edx_10:3.b = out.a
004131ad        data[0x15] = edx_10
0041342d        struct ObjectVertexBuffer* vertex_buffer_1 = g_direct3d_renderer.renderer_state->vertex_buffer
00413433        vertex_buffer_1->vtbl->Unlock(vertex_buffer_1)
0041343c        struct Direct3DDevice8* device = g_direct3d_renderer.device
0041344b        device->vtbl->SetStreamSource(device, 0, g_direct3d_renderer.renderer_state->vertex_buffer, 0x18)
00413451        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
0041345e        device_1->vtbl->SetVertexShader(device_1, 0x142)
00413464        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
00413471        int32_t eax_32 = device_2->vtbl->DrawPrimitive(device_2, 6, 0, 2)
00413486        int32_t edx_33 = g_draw_primitive_call_count + 1
00413487        g_render_triangle_count += 2
00413490        g_draw_primitive_call_count = edx_33
00413497        if (eax_32 == 0)
004134aa        g_render_successful_primitive_count += 1
004134b3        return
0041349e        report_errorf("Draw Primitive Failed")
004134a9        return
