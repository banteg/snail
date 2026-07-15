/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: refresh_object_vertex_buffer @ 0x412250 */

00412253        struct Object* object_1 = object
00412258        enum ObjectFlag flags = object_1->flags
00412261        if ((flags & OBJECT_FLAG_HAS_ANIMATION) == 0)
00412328        if ((flags.b & 4) != 0)
00412341        struct ObjectVertexBuffer* vertex_buffer_2 = object_1->render_buffers->vertex_buffer
00412350        vertex_buffer_2->vtbl->Lock(vertex_buffer_2, 0, object_1->grouped_vertex_count * 0x18, &object, 0)
00412359        int32_t i = 0
0041235d        if (object_1->grouped_vertex_count s> 0)
0041235f        int32_t edi_5 = 0
00412361        void* ebx_3 = nullptr
00412368        int32_t* edx_9 = ebx_3 + object_1->vertices
0041236e        int32_t* eax_8 = &object->_pad_00[edi_5]
00412370        ebx_3 += 0xc
00412375        edi_5 += 0x18
00412378        *eax_8 = *edx_9
0041237d        eax_8[1] = edx_9[1]
00412383        eax_8[2] = edx_9[2]
00412388        int32_t eax_10
00412388        int32_t edx_11
00412388        edx_11:eax_10 = sx.q(i)
00412397        int32_t edx_14 = i & 3
0041239a        i += 1
0041239e        int32_t eax_14 = edx_14 + ((eax_10 + (edx_11 & 3)) s>> 2) * 6
004123a8        *(edi_5 + object - 8) = object_1->facequads->uv[eax_14].u
004123b7        *(edi_5 + object - 4) = object_1->facequads->uv[eax_14].v
004123c3        do while (i s< object_1->grouped_vertex_count)
004123cb        struct ObjectVertexBuffer* vertex_buffer_3 = object_1->render_buffers->vertex_buffer
004123d1        vertex_buffer_3->vtbl->Unlock(vertex_buffer_3)
004123d8        return
00412267        struct ObjectAnimation* animation = object_1->animation
00412273        int32_t eax_1
00412273        int16_t x87control
00412273        int16_t x87control_1
00412273        eax_1, x87control_1 = ftol(x87control, float.t(animation->generated_frame_count) * fconvert.t(animation->progress))
00412280        object_1->vertices = animation->frames[eax_1]->vertices
0041229d        object_1->facequad_normals = animation->frames[ftol(x87control_1, float.t(animation->generated_frame_count) * fconvert.t(animation->progress))]->facequad_normals
004122a0        if ((flags & &data_800000) != 0)
004122a9        apply_distort_to_object(&object_1->distort, object_1)
004122b6        struct ObjectVertexBuffer* vertex_buffer = object_1->render_buffers->vertex_buffer
004122d0        vertex_buffer->vtbl->Lock(vertex_buffer, 0, object_1->grouped_vertex_count * 0x18, &object, 0)
004122d9        int32_t i_1 = 0
004122dd        if (object_1->grouped_vertex_count s> 0)
004122df        int32_t edx_4 = 0
004122e1        void* ecx_9 = nullptr
004122e8        int32_t* edi_2 = ecx_9 + object_1->vertices
004122ee        int32_t* ebx_2 = &object->_pad_00[edx_4]
004122f0        i_1 += 1
004122f3        ecx_9 += 0xc
004122f6        *ebx_2 = *edi_2
004122f8        edx_4 += 0x18
004122fe        ebx_2[1] = edi_2[1]
00412304        ebx_2[2] = edi_2[2]
0041230f        do while (i_1 s< object_1->grouped_vertex_count)
00412317        struct ObjectVertexBuffer* vertex_buffer_1 = object_1->render_buffers->vertex_buffer
0041231d        vertex_buffer_1->vtbl->Unlock(vertex_buffer_1)
00412324        return
