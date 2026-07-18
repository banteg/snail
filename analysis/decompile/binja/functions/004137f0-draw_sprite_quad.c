/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_sprite_quad @ 0x4137f0 */

004137f3        struct Vec3* position_1 = position
00413801        float z = position_1->z
00413804        float y = position_1->y
00413807        float x = position_1->x
00413819        struct TransformMatrix matrix
00413819        __builtin_memset(&matrix.position, 0, 0xc)
00413821        matrix.basis_forward_w = 0
00413829        matrix.basis_forward.y = 0
00413831        matrix.basis_forward.x = 0
00413839        matrix.basis_up_w = 0
00413841        matrix.basis_up.z = 0
00413849        matrix.basis_up.x = 0
00413851        matrix.basis_right_w = 0
00413859        matrix.basis_right.z = 0
00413861        matrix.basis_right.y = 0
00413869        matrix.position_w = 0x3f800000
00413871        matrix.basis_forward.z = 0x3f800000
00413879        matrix.basis_up.y = 0x3f800000
00413881        matrix.basis_right.x = 0x3f800000
00413889        D3DXMatrixTranslation(&matrix, x, y, z)
0041388e        struct Direct3DDevice8* device = g_direct3d_renderer.device
0041389d        device->vtbl->SetTransform(device, 2, &matrix)
004138a3        struct Sprite* sprite_1 = sprite
004138bf        sprite = fconvert.s((fconvert.t(1f) - fconvert.t(sprite_1->progress)) * fconvert.t(sprite_1->size_start) + fconvert.t(sprite_1->size_end) * fconvert.t(sprite_1->progress))
004138c3        bind_texture_ref(sprite_1->texture_ref)
004138c9        configure_sprite_render_state(sprite_1)
004138d7        float var_44
004138d7        if (((sprite_1->flags).w:1.b & 0x10) == 0)
004138ef        var_44 = fconvert.s((fconvert.t(1f) - fconvert.t(sprite_1->progress)) * fconvert.t(sprite_1->color.a))
004138d9        var_44 = 1f
0041391e        struct ColorBGRA8 out
0041391e        out.a = ftol(pack_color_rgba_u8(&out, &sprite_1->color), fconvert.t(var_44) * fconvert.t(255f))
00413924        struct ObjectVertexBuffer* vertex_buffer = g_direct3d_renderer.renderer_state->vertex_buffer
00413933        int32_t ecx_3 = vertex_buffer->vtbl->Lock(vertex_buffer, 0, 0x60, &position, 0)
00413936        long double x87_r7_9 = fconvert.t(sprite_1->facing_angle)
00413939        long double temp0 = fconvert.t(0f)
00413939        x87_r7_9 - temp0
00413944        long double x87_r7_11
00413944        if ((((x87_r7_9 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp0) ? 1 : 0) << 0xa | (x87_r7_9 == temp0 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
00413a09        int32_t var_54_4 = ecx_3
00413a1c        float var_44_1 = fconvert.s(cosine(fconvert.s(fconvert.t(sprite_1->facing_angle) + fconvert.t(0.785398185f))) * fconvert.t(sprite) * fconvert.t(1.41400003f))
00413a3c        long double x87_r7_21 = sine(fconvert.s(fconvert.t(sprite_1->facing_angle) + fconvert.t(0.785398185f))) * fconvert.t(sprite) * fconvert.t(1.41400003f)
00413a46        position->x = fconvert.s(fneg(x87_r7_21))
00413a50        position->y = fconvert.s(fconvert.t(var_44_1))
00413a5b        position->z = 0f
00413a62        position->__offset(0x10).d = 0
00413a69        position->__offset(0x14).d = 0
00413a70        int32_t edx_15
00413a70        edx_15.b = out.b
00413a70        edx_15:1.b = out.g
00413a70        edx_15:2.b = out.r
00413a70        edx_15:3.b = out.a
00413a74        position->__offset(0xc).d = edx_15
00413a7b        position->__offset(0x18).d = fconvert.s(fconvert.t(var_44_1))
00413a89        position->__offset(0x1c).d = fconvert.s(x87_r7_21)
00413a92        position->__offset(0x20).d = 0
00413a99        position->__offset(0x28).d = 0x3f800000
00413aa0        position->__offset(0x2c).d = 0
00413aa7        int32_t edx_18
00413aa7        edx_18.b = out.b
00413aa7        edx_18:1.b = out.g
00413aa7        edx_18:2.b = out.r
00413aa7        edx_18:3.b = out.a
00413aab        position->__offset(0x24).d = edx_18
00413ab2        position->__offset(0x30).d = fconvert.s(x87_r7_21)
00413abf        position->__offset(0x34).d = fconvert.s(fneg(fconvert.t(var_44_1)))
00413aca        position->__offset(0x38).d = 0
00413ad1        position->__offset(0x40).d = 0x3f800000
00413ad8        position->__offset(0x44).d = 0x3f800000
00413adf        int32_t ecx_21
00413adf        ecx_21.b = out.b
00413adf        ecx_21:1.b = out.g
00413adf        ecx_21:2.b = out.r
00413adf        ecx_21:3.b = out.a
00413ae3        position->__offset(0x3c).d = ecx_21
00413af2        position->__offset(0x48).d = fconvert.s(fneg(fconvert.t(var_44_1) * fconvert.t(sprite_1->corner_scale)))
00413afb        x87_r7_11 = fneg(x87_r7_21 * fconvert.t(sprite_1->corner_scale))
00413952        x87_r7_11 = fneg(fconvert.t(sprite))
00413956        position->x = fconvert.s(x87_r7_11)
00413960        position->y = fconvert.s(fconvert.t(sprite))
0041396b        position->z = 0f
00413972        position->__offset(0x10).d = 0
00413979        position->__offset(0x14).d = 0
00413980        int32_t edx_5
00413980        edx_5.b = out.b
00413980        edx_5:1.b = out.g
00413980        edx_5:2.b = out.r
00413980        edx_5:3.b = out.a
00413984        position->__offset(0xc).d = edx_5
0041398b        position->__offset(0x18).d = fconvert.s(fconvert.t(sprite))
0041399b        position->__offset(0x1c).d = fconvert.s(fconvert.t(sprite))
004139a6        position->__offset(0x20).d = 0
004139ad        position->__offset(0x28).d = 0x3f800000
004139b4        position->__offset(0x2c).d = 0
004139bb        int32_t edx_8
004139bb        edx_8.b = out.b
004139bb        edx_8:1.b = out.g
004139bb        edx_8:2.b = out.r
004139bb        edx_8:3.b = out.a
004139bf        position->__offset(0x24).d = edx_8
004139c6        position->__offset(0x30).d = fconvert.s(fconvert.t(sprite))
004139cf        position->__offset(0x34).d = fconvert.s(x87_r7_11)
004139d8        position->__offset(0x38).d = 0
004139df        position->__offset(0x40).d = 0x3f800000
004139e6        position->__offset(0x44).d = 0x3f800000
004139ed        int32_t ecx_12
004139ed        ecx_12.b = out.b
004139ed        ecx_12:1.b = out.g
004139ed        ecx_12:2.b = out.r
004139ed        ecx_12:3.b = out.a
004139f1        position->__offset(0x3c).d = ecx_12
004139f8        position->__offset(0x48).d = fconvert.s(x87_r7_11)
00413b01        position->__offset(0x4c).d = fconvert.s(x87_r7_11)
00413b08        position->__offset(0x50).d = 0
00413b0f        position->__offset(0x58).d = 0
00413b16        position->__offset(0x5c).d = 0x3f800000
00413b1d        int32_t eax_11
00413b1d        eax_11.b = out.b
00413b1d        eax_11:1.b = out.g
00413b1d        eax_11:2.b = out.r
00413b1d        eax_11:3.b = out.a
00413b21        position->__offset(0x54).d = eax_11
00413b2a        struct ObjectVertexBuffer* vertex_buffer_1 = g_direct3d_renderer.renderer_state->vertex_buffer
00413b30        vertex_buffer_1->vtbl->Unlock(vertex_buffer_1)
00413b39        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
00413b48        device_1->vtbl->SetStreamSource(device_1, 0, g_direct3d_renderer.renderer_state->vertex_buffer, 0x18)
00413b4e        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
00413b5b        device_2->vtbl->SetVertexShader(device_2, 0x142)
00413b61        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
00413b6e        int32_t result = device_3->vtbl->DrawPrimitive(device_3, 6, 0, 2)
00413b83        int32_t edx_29 = g_draw_primitive_call_count + 1
00413b86        g_render_triangle_count += 2
00413b8d        g_draw_primitive_call_count = edx_29
00413b94        if (result == 0)
00413ba6        return result
00413b9b        return report_errorf("Draw Primitive Failed")
