/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_animation @ 0x430a70 */

00430a73        int32_t eax = 0
00430a76        struct XAnimationKeyframe* keyframes_2 = keyframes
00430a85        if (keyframe_count s> 0)
00430a8a        struct Object** ecx = &keyframes_2->object
00430a8d        struct Object* validation_object
00430a8d        validation_object.b = (ecx - 0x24)->object.b
00430a8d        validation_object:1.b = (ecx - 0x24)->object:1.b
00430a8d        validation_object:2.b = (ecx - 0x24)->object:2.b
00430a8d        validation_object:3.b = (ecx - 0x24)->object:3.b
00430a92        if (validation_object->vertex_count != object->vertex_count)
00430b41        report_errorf("Anim tween Vertices don't match Frame %i", keyframes_2[eax].frame_number)
00430b50        return
00430a98        eax += 1
00430a99        ecx = &ecx[0x20]
00430aa1        do while (eax s< keyframe_count)
00430aad        object->flags |= OBJECT_FLAG_HAS_ANIMATION
00430ab9        int16_t x87control
00430ab9        int32_t ebp_1 = ftol(x87control, fconvert.t(1f) / fconvert.t(progress_step))
00430ac2        int32_t var_34 = ebp_1
00430ac6        struct ObjectAnimation* eax_2 = allocate_tracked_memory(0x14, "Object Animation")
00430acb        int16_t edx_2 = flags.w
00430ad0        object->animation = eax_2
00430ad6        eax_2->generated_frame_count = ebp_1
00430ad9        struct ObjectAnimation* animation_1 = object->animation
00430ae4        animation_1->flags.b = edx_2.b
00430ae4        animation_1->flags:1.b = edx_2:1.b
00430af1        object->animation->progress = 0f
00430b06        object->animation->progress_step = progress_step
00430b09        struct ObjectAnimationFrame** eax_5 = allocate_tracked_memory(ebp_1 << 2, "Object Animation Frame array")
00430b0e        struct ObjectAnimation* animation_2 = object->animation
00430b1a        __builtin_memset(&keyframes, 0, 4)
00430b22        animation_2->frames = eax_5
00430b25        int32_t frame_number = keyframes_2->frame_number
00430b28        flags = frame_number
00430b2c        if (keyframe_count != 1)
00430b59        progress_step = keyframes_2->__offset(0xfc).d
00430b2e        progress_step = frame_number
00430b5d        int32_t edi_1 = 0
00430b61        if (ebp_1 s> 0)
00430b7a        struct Object** ebx = &keyframes_2->object
00430b86        int32_t var_50_1 = 8
00430b9b        object->animation->frames[edi_1] = allocate_tracked_memory(8, "Object Animation Frame")
00430ba8        struct Vec3* allocated_vertices = allocate_tracked_memory(object->vertex_count * 0xc, "Object Animation Frame Vertices")
00430bbb        struct ObjectAnimationFrame* frame_for_vertices = object->animation->frames[edi_1]
00430bbe        frame_for_vertices->vertices.b = allocated_vertices.b
00430bbe        frame_for_vertices->vertices:1.b = allocated_vertices:1.b
00430bbe        frame_for_vertices->vertices:2.b = allocated_vertices:2.b
00430bbe        frame_for_vertices->vertices:3.b = allocated_vertices:3.b
00430bca        struct Vec3* allocated_facequad_normals = allocate_tracked_memory(object->facequad_count * 0x18, "Object Animation Frame FaceQuad Normals")
00430bdb        struct ObjectAnimationFrame* frame_for_facequad_normals = object->animation->frames[edi_1]
00430be2        frame_for_facequad_normals->facequad_normals.b = allocated_facequad_normals.b
00430be2        frame_for_facequad_normals->facequad_normals:1.b = allocated_facequad_normals:1.b
00430be2        frame_for_facequad_normals->facequad_normals:2.b = allocated_facequad_normals:2.b
00430be2        frame_for_facequad_normals->facequad_normals:3.b = allocated_facequad_normals:3.b
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
00430cb1        float* ecx_15 = (ebx - 0x24)->__offset(0xa4).d->vertices + edx_14
00430cb3        struct Vec3* vertices = (ebx - 0x24)->object->vertices
00430cc2        float* eax_22 = vertices + edx_14
00430d01        float var_20_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(ecx_15[1]) - fconvert.t(*(&vertices->y + edx_14)))) * fconvert.t(var_38_2))) + fconvert.t(eax_22[1]))
00430d0f        struct ObjectAnimationFrame* output_frame = object->animation->frames[edi_1]
00430d12        float var_1c_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(ecx_15[2]) - fconvert.t(eax_22[2]))) * fconvert.t(var_38_2))) + fconvert.t(eax_22[2]))
00430d16        struct Vec3* output_vertices
00430d16        output_vertices.b = output_frame->vertices.b
00430d16        output_vertices:1.b = output_frame->vertices:1.b
00430d16        output_vertices:2.b = output_frame->vertices:2.b
00430d16        output_vertices:3.b = output_frame->vertices:3.b
00430d1c        int32_t* eax_24 = output_vertices + edx_14
00430d1e        *eax_24 = fconvert.s((fconvert.t(*ecx_15) - fconvert.t(*(vertices + edx_14))) * fconvert.t(var_38_2) + fconvert.t(*eax_22))
00430d24        eax_24[1] = var_20_1
00430d2b        eax_24[2] = var_1c_1
00430c81        char* ecx_13 = (ebx - 0x24)->object->vertices + edx_14
00430c86        int32_t ebp_2
00430c86        ebp_2.b = *ecx_13
00430c86        ebp_2:1.b = ecx_13[1]
00430c86        ebp_2:2.b = ecx_13[2]
00430c86        ebp_2:3.b = ecx_13[3]
00430c8d        int32_t* eax_20 = object->animation->frames[edi_1]->vertices + edx_14
00430c8f        *eax_20 = ebp_2
00430c91        int32_t ebp_3
00430c91        ebp_3.b = ecx_13[4]
00430c91        ebp_3:1.b = ecx_13[5]
00430c91        ebp_3:2.b = ecx_13[6]
00430c91        ebp_3:3.b = ecx_13[7]
00430c94        eax_20[1] = ebp_3
00430c9a        ebp_1 = var_34
00430c9e        eax_20[2] = *(ecx_13 + 8)
00430d36        edx_14 += 0xc
00430d39        cond:3_1 = var_30_3 + 1 s< object->vertex_count
00430d3b        var_30_3 += 1
00430d3f        do while (cond:3_1)
00430d45        struct ObjectAnimation* animation = object->animation
00430d4e        struct ObjectAnimationFrame* installed_frame_for_vertices = animation->frames[edi_1]
00430d51        struct Vec3* edx_16
00430d51        edx_16.b = installed_frame_for_vertices->vertices.b
00430d51        edx_16:1.b = installed_frame_for_vertices->vertices:1.b
00430d51        edx_16:2.b = installed_frame_for_vertices->vertices:2.b
00430d51        edx_16:3.b = installed_frame_for_vertices->vertices:3.b
00430d53        object->vertices = edx_16
00430d59        struct ObjectAnimationFrame* installed_frame_for_normals = animation->frames[edi_1]
00430d5c        struct Vec3* edx_17
00430d5c        edx_17.b = installed_frame_for_normals->facequad_normals.b
00430d5c        edx_17:1.b = installed_frame_for_normals->facequad_normals:1.b
00430d5c        edx_17:2.b = installed_frame_for_normals->facequad_normals:2.b
00430d5c        edx_17:3.b = installed_frame_for_normals->facequad_normals:3.b
00430d61        object->facequad_normals = edx_17
00430d64        calc_object_facequad_normals(object)
00430d69        edi_1 += 1
00430d6c        do while (edi_1 s< ebp_1)
00430d7b        object->animation->progress = 0f
00430d86        return
