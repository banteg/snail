/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_object_color @ 0x4141d0 */

004141e6        struct ColorBGRA8 out
004141e6        pack_color_rgba_u8(&out, &color)
004141f6        if ((object->flags & 0x80000) == 0)
004141f6        return
00414200        struct ObjectVertexBuffer* vertex_buffer = object->render_buffers->vertex_buffer
0041421a        void* data
0041421a        vertex_buffer->vtbl->Lock(vertex_buffer, 0, g_object_grouped_vertex_cursor * 0x18, &data, 0)
00414223        int32_t i = 0
00414227        if (object->grouped_vertex_count s> 0)
0041422a        int32_t ecx_7 = 0
00414230        int32_t edx_3
00414230        edx_3.b = out.b
00414230        edx_3:1.b = out.g
00414230        edx_3:2.b = out.r
00414230        edx_3:3.b = out.a
00414234        i += 1
00414235        *(ecx_7 + data + 0xc) = edx_3
0041423f        ecx_7 += 0x18
00414244        do while (i s< object->grouped_vertex_count)
0041424d        struct ObjectVertexBuffer* vertex_buffer_1 = object->render_buffers->vertex_buffer
00414253        vertex_buffer_1->vtbl->Unlock(vertex_buffer_1)
0041425a        return
