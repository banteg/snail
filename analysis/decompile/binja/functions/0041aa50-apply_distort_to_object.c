/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: apply_distort_to_object @ 0x41aa50 */

0041aa57        struct ObjectDistort* distort_3 = distort
0041aa59        struct Object* object_1 = object
0041aa5d        distort.b = 0
0041aa63        long double x87_r7 = fconvert.t(distort_3->z_wave)
0041aa65        long double temp1 = fconvert.t(0f)
0041aa65        x87_r7 - temp1
0041aa6b        struct Vec3* ebx = object_1->vertices
0041aa73        if ((((x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
0041aa79        long double x87_r7_1 = fconvert.t(object_1->bounds_min.z)
0041aa7f        long double temp3_1 = fconvert.t(0f)
0041aa7f        x87_r7_1 - temp3_1
0041aa85        long double x87_r7_2 = fconvert.t(object_1->bounds_min.z)
0041aa90        if ((((x87_r7_1 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp3_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp3_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0041aa92        x87_r7_2 = fneg(x87_r7_2)
0041aa94        long double x87_r6_1 = fconvert.t(object_1->bounds_max.z)
0041aa9a        long double temp5_1 = fconvert.t(0f)
0041aa9a        x87_r6_1 - temp5_1
0041aaa0        long double x87_r6_2 = fconvert.t(object_1->bounds_max.z)
0041aaab        if ((((x87_r6_1 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_1, temp5_1) ? 1 : 0) << 0xa | (x87_r6_1 == temp5_1 ? 1 : 0) << 0xe | 0x3000):1.b & 1) != 0)
0041aaad        x87_r6_2 = fneg(x87_r6_2)
0041aab1        x87_r7_2 - x87_r6_2
0041aaba        long double x87_r7_6
0041aaba        if ((((x87_r7_2 < x87_r6_2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, x87_r6_2) ? 1 : 0) << 0xa | (x87_r7_2 == x87_r6_2 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
0041aad7        long double x87_r7_7 = fconvert.t(object_1->bounds_min.z)
0041aadd        long double temp6_1 = fconvert.t(0f)
0041aadd        x87_r7_7 - temp6_1
0041aae3        x87_r7_6 = fconvert.t(object_1->bounds_min.z)
0041aaee        if ((((x87_r7_7 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp6_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp6_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0041aaf0        x87_r7_6 = fneg(x87_r7_6)
0041aabc        long double x87_r7_5 = fconvert.t(object_1->bounds_max.z)
0041aac2        long double temp7_1 = fconvert.t(0f)
0041aac2        x87_r7_5 - temp7_1
0041aac8        x87_r7_6 = fconvert.t(object_1->bounds_max.z)
0041aad3        if ((((x87_r7_5 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp7_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp7_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0041aaf0        x87_r7_6 = fneg(x87_r7_6)
0041aaf5        int32_t i = 0
0041aafd        if (object_1->vertex_count s> 0)
0041aaff        int32_t edi = 0
0041ab01        float* ebx_1 = &ebx->z
0041ab0a        *(object_1->copied_vertices + edi) = (ebx_1 - 8)->x
0041ab0d        struct Vec3* vertices = object_1->vertices
0041ab10        long double x87_r7_8 = fconvert.t(*(&vertices->z + edi))
0041ab18        long double temp8_1 = fconvert.t(0f)
0041ab18        x87_r7_8 - temp8_1
0041ab1e        long double x87_r7_9 = fconvert.t(*(&vertices->z + edi))
0041ab25        if ((((x87_r7_8 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp8_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp8_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0041ab27        x87_r7_9 = fneg(x87_r7_9)
0041ab2f        float* var_1c_1 = &vertices->z + edi
0041ab42        long double x87_r7_14 = sine(fconvert.s(x87_r7_9 * fconvert.t(1.57079637f) / fconvert.t(fconvert.s(x87_r7_6)) + fconvert.t(4.71238899f))) + fconvert.t(1f)
0041ab4c        distort = object_1->copied_vertices
0041ab52        i += 1
0041ab55        edi += 0xc
0041ab58        ebx_1 = &ebx_1[3]
0041ab5e        *(distort + edi - 8) = fconvert.s(x87_r7_14 * fconvert.t(distort_3->z_wave) + fconvert.t((ebx_1 - 8)->__offset(0xfffffffffffffff8).d))
0041ab68        *(object_1->copied_vertices + edi - 4) = (ebx_1 - 8)->x:-4.d
0041ab71        do while (i s< object_1->vertex_count)
0041ab77        ebx = object_1->copied_vertices
0041ab7a        distort.b = 1
0041ab7c        long double x87_r7_17 = fconvert.t(distort_3->y_squash)
0041ab7f        long double temp2 = fconvert.t(0f)
0041ab7f        x87_r7_17 - temp2
0041ab8a        if ((((x87_r7_17 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_17, temp2) ? 1 : 0) << 0xa | (x87_r7_17 == temp2 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
0041ab99        struct ObjectDistort* distort_1 = distort
0041aba8        float var_8_1 = fconvert.s(sine(fconvert.s(fconvert.t(distort_3->y_squash) * fconvert.t(1.57079637f))) + fconvert.t(1f))
0041abbd        long double x87_r7_25 = fconvert.t(1f) - sine(fconvert.s(fconvert.t(distort_3->y_squash) * fconvert.t(1.57079637f)))
0041abc6        distort = object_1->bounds_min.y
0041abcf        int32_t i_1 = 0
0041abd7        object = distort
0041abdb        if (object_1->vertex_count s> 0)
0041abdd        int32_t eax_6 = 0
0041abdf        distort = &ebx->z
0041abe6        long double x87_r7_27 = fconvert.t(var_8_1) * fconvert.t(distort->__offset(0xfffffffffffffff8).d)
0041abec        i_1 += 1
0041abed        eax_6 += 0xc
0041abf0        distort = &distort->unknown_0c
0041abf3        *(object_1->copied_vertices + eax_6 - 0xc) = fconvert.s(x87_r7_27)
0041ac09        *(object_1->copied_vertices + eax_6 - 8) = fconvert.s((fconvert.t(distort->__offset(0xfffffffffffffff0).d) - fconvert.t(object)) * fconvert.t(fconvert.s(x87_r7_25)) + fconvert.t(object))
0041ac13        *(object_1->copied_vertices + eax_6 - 4) = distort->__offset(0xfffffffffffffff4).d
0041ac1c        do while (i_1 s< object_1->vertex_count)
0041ac1e        ebx = object_1->copied_vertices
0041ac21        distort.b = 1
0041ac23        long double x87_r7_32 = fconvert.t(distort_3->xyz_scale)
0041ac26        long double temp4 = fconvert.t(0f)
0041ac26        x87_r7_32 - temp4
0041ac31        if ((((x87_r7_32 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_32, temp4) ? 1 : 0) << 0xa | (x87_r7_32 == temp4 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
0041ac40        struct ObjectDistort* distort_2 = distort
0041ac55        object = fconvert.s(sine(fconvert.s(fconvert.t(distort_3->xyz_scale) * fconvert.t(1.57079637f))) * fconvert.t(0.100000001f) + fconvert.t(1f))
0041ac6a        long double x87_r7_41 = fconvert.t(1f) - sine(fconvert.s(fconvert.t(distort_3->xyz_scale) * fconvert.t(1.57079637f)))
0041ac76        int32_t i_2 = 0
0041ac7e        if (object_1->vertex_count s> 0)
0041ac80        int32_t eax_8 = 0
0041ac82        float* ecx_2 = &ebx->z
0041ac89        long double x87_r7_43 = fconvert.t(object) * fconvert.t((ecx_2 - 8)->x)
0041ac8f        i_2 += 1
0041ac90        eax_8 += 0xc
0041ac93        ecx_2 = &ecx_2[3]
0041ac96        *(object_1->copied_vertices + eax_8 - 0xc) = fconvert.s(x87_r7_43)
0041aca4        *(object_1->copied_vertices + eax_8 - 8) = fconvert.s(fconvert.t(object) * fconvert.t((ecx_2 - 8)->__offset(0xfffffffffffffff8).d))
0041acb2        *(object_1->copied_vertices + eax_8 - 4) = fconvert.s(fconvert.t(fconvert.s(x87_r7_41)) * fconvert.t((ecx_2 - 8)->x:-4.d))
0041acb9        do while (i_2 s< object_1->vertex_count)
0041acc6        object_1->vertices = object_1->copied_vertices
0041acc9        calc_object_facequad_normals_simple(object_1)
0041acbf        if (distort.b != 0)
0041acc6        object_1->vertices = object_1->copied_vertices
0041acc9        calc_object_facequad_normals_simple(object_1)
0041acd5        return
