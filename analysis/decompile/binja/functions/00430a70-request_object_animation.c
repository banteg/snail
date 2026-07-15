/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_animation @ 0x430a70 */

00430a73        int32_t eax = 0
00430a76        struct XAnimationKeyframe* keyframes_2 = keyframes
00430a85        if (keyframe_count s> 0)
00430a8a        struct Object** ecx = &keyframes_2->object
00430a8d        void* ebp_1
00430a8d        ebp_1.b = (ecx - 0x24)->object.b
00430a8d        ebp_1:1.b = (ecx - 0x24)->object:1.b
00430a8d        ebp_1:2.b = (ecx - 0x24)->object:2.b
00430a8d        ebp_1:3.b = (ecx - 0x24)->object:3.b
00430a92        if (*(ebp_1 + 0x2c) != object->vertex_count)
00430b41        report_errorf("Anim tween Vertices don't match Frame %i", keyframes_2[eax].frame_number)
00430b50        return
00430a98        eax += 1
00430a99        ecx = &ecx[0x20]
00430aa1        do while (eax s< keyframe_count)
00430aad        object->flags |= OBJECT_FLAG_HAS_ANIMATION
00430ab9        int16_t x87control
00430ab9        int32_t ebp_2 = ftol(x87control, fconvert.t(1f) / fconvert.t(progress_step))
00430ac2        int32_t var_34 = ebp_2
00430ac6        struct ObjectAnimation* eax_2 = allocate_tracked_memory(0x14, "Object Animation")
00430acb        int16_t edx_2 = flags.w
00430ad0        object->animation = eax_2
00430ad6        eax_2->generated_frame_count = ebp_2
00430ad9        struct ObjectAnimation* animation_1 = object->animation
00430ae4        animation_1->flags.b = edx_2.b
00430ae4        animation_1->flags:1.b = edx_2:1.b
00430af1        object->animation->progress = 0f
00430b06        object->animation->progress_step = progress_step
00430b09        struct ObjectAnimationFrame** eax_5 = allocate_tracked_memory(ebp_2 << 2, "Object Animation Frame array")
00430b0e        struct ObjectAnimation* animation_2 = object->animation
00430b1a        __builtin_memset(&keyframes, 0, 4)
00430b22        animation_2->frames = eax_5
00430b25        int32_t frame_number = keyframes_2->frame_number
00430b28        flags = frame_number
00430b2c        if (keyframe_count != 1)
00430b59        progress_step = keyframes_2->__offset(0xfc).d
00430b2e        progress_step = frame_number
00430b5d        int32_t edi_1 = 0
00430b61        if (ebp_2 s> 0)
00430b7a        struct Object** ebx = &keyframes_2->object
00430b86        int32_t var_50_1 = 8
00430b9b        object->animation->frames[edi_1] = allocate_tracked_memory(8, "Object Animation Frame")
00430ba8        void* eax_12 = allocate_tracked_memory(object->vertex_count * 0xc, "Object Animation Frame Vertices")
00430bbb        char* ecx_5 = object->animation->frames[edi_1]
00430bbe        *ecx_5 = eax_12.b
00430bbe        ecx_5[1] = eax_12:1.b
00430bbe        ecx_5[2] = eax_12:2.b
00430bbe        ecx_5[3] = eax_12:3.b
00430bca        void* eax_14 = allocate_tracked_memory(object->facequad_count * 0x18, "Object Animation Frame FaceQuad Normals")
00430bdb        void* ecx_7 = object->animation->frames[edi_1]
00430be2        *(ecx_7 + 4) = eax_14.b
00430be2        *(ecx_7 + 5) = eax_14:1.b
00430be2        *(ecx_7 + 6) = eax_14:2.b
00430be2        *(ecx_7 + 7) = eax_14:3.b
00430bf2        long double x87_r7_4 = float.t(*(&keyframes_2[keyframe_count] - 4) * edi_1) / fconvert.t(fconvert.s(float.t(var_34)))
00430bfa        var_50_1.q = fconvert.d(x87_r7_4)
00430bfd        int16_t x87control_1
00430bfd        long double st0_1
00430bfd        st0_1, x87control_1 = sub_48c0bc(var_50_1)
00430c0e        if (ftol(x87control_1, st0_1) s>= progress_step)
00430c14        struct XAnimationKeyframe* keyframes_1 = keyframes
00430c1b        if (keyframes_1 s< keyframe_count - 1)
00430c1d        int32_t flags_1 = (ebx - 0x24)->__offset(0xfc).d
00430c25        float progress_step_1 = (ebx - 0x24)->__offset(0x17c).d
00430c2c        ebx = &ebx[0x20]
00430c32        keyframes = &keyframes_1->_pad_00[1]
00430c36        flags = flags_1
00430c3a        progress_step = progress_step_1
00430c53        int32_t edx_14 = 0
00430c5f        int32_t var_30_3 = 0
00430c65        float var_38_2 = fconvert.s((fconvert.t(fconvert.s(x87_r7_4)) - float.t(flags)) / float.t(progress_step i- flags))
00430c69        if (object->vertex_count s> 0)
00430d3f        bool cond:3_1
00430c74        if (keyframe_count != 1)
00430cb1        float* ecx_18 = *((ebx - 0x24)->__offset(0xa4).d + 0x38) + edx_14
00430cb3        struct Vec3* vertices = (ebx - 0x24)->object->vertices
00430cc2        float* eax_27 = vertices + edx_14
00430d01        float var_20_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(ecx_18[1]) - fconvert.t(*(&vertices->y + edx_14)))) * fconvert.t(var_38_2))) + fconvert.t(eax_27[1]))
00430d0f        char* ecx_20 = object->animation->frames[edi_1]
00430d12        float var_1c_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(ecx_18[2]) - fconvert.t(eax_27[2]))) * fconvert.t(var_38_2))) + fconvert.t(eax_27[2]))
00430d16        void* eax_29
00430d16        eax_29.b = *ecx_20
00430d16        eax_29:1.b = ecx_20[1]
00430d16        eax_29:2.b = ecx_20[2]
00430d16        eax_29:3.b = ecx_20[3]
00430d1c        int32_t* eax_30 = eax_29 + edx_14
00430d1e        *eax_30 = fconvert.s((fconvert.t(*ecx_18) - fconvert.t(*(vertices + edx_14))) * fconvert.t(var_38_2) + fconvert.t(*eax_27))
00430d24        eax_30[1] = var_20_1
00430d2b        eax_30[2] = var_1c_1
00430c81        char* ecx_15 = (ebx - 0x24)->object->vertices + edx_14
00430c86        int32_t ebp_3
00430c86        ebp_3.b = *ecx_15
00430c86        ebp_3:1.b = ecx_15[1]
00430c86        ebp_3:2.b = ecx_15[2]
00430c86        ebp_3:3.b = ecx_15[3]
00430c8d        int32_t* eax_24 = object->animation->frames[edi_1]->vertices + edx_14
00430c8f        *eax_24 = ebp_3
00430c91        int32_t ebp_4
00430c91        ebp_4.b = ecx_15[4]
00430c91        ebp_4:1.b = ecx_15[5]
00430c91        ebp_4:2.b = ecx_15[6]
00430c91        ebp_4:3.b = ecx_15[7]
00430c94        eax_24[1] = ebp_4
00430c9a        ebp_2 = var_34
00430c9e        eax_24[2] = *(ecx_15 + 8)
00430d36        edx_14 += 0xc
00430d39        cond:3_1 = var_30_3 + 1 s< object->vertex_count
00430d3b        var_30_3 += 1
00430d3f        do while (cond:3_1)
00430d45        struct ObjectAnimation* animation = object->animation
00430d4e        char* ecx_25 = animation->frames[edi_1]
00430d51        struct Vec3* edx_16
00430d51        edx_16.b = *ecx_25
00430d51        edx_16:1.b = ecx_25[1]
00430d51        edx_16:2.b = ecx_25[2]
00430d51        edx_16:3.b = ecx_25[3]
00430d53        object->vertices = edx_16
00430d59        void* ecx_26 = animation->frames[edi_1]
00430d5c        struct Vec3* edx_17
00430d5c        edx_17.b = *(ecx_26 + 4)
00430d5c        edx_17:1.b = *(ecx_26 + 5)
00430d5c        edx_17:2.b = *(ecx_26 + 6)
00430d5c        edx_17:3.b = *(ecx_26 + 7)
00430d61        object->facequad_normals = edx_17
00430d64        calc_object_facequad_normals(object)
00430d69        edi_1 += 1
00430d6c        do while (edi_1 s< ebp_2)
00430d7b        object->animation->progress = 0f
00430d86        return
