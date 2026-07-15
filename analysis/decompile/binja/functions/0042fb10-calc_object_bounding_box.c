/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_bounding_box @ 0x42fb10 */

0042fb25        struct Vec3* edi = &object->bounds_max
0042fb41        edi->x = 0xd01502f9
0042fb47        struct Vec3* ebx = &object->bounds_min
0042fb55        edi->y = -1e+10f
0042fb6a        edi->z = -1e+10f
0042fb75        ebx->x = 0x501502f9
0042fb7b        int32_t ebp = 0
0042fb7d        ebx->y = 1e+10f
0042fb80        object->bounding_radius = 0f
0042fb86        int32_t var_10 = 0
0042fb8a        ebx->z = 1e+10f
0042fb92        if (object->vertex_count s<= 0)
0042fb92        return
0042fc94        bool cond:0_1
0042fb9b        float* vector = object->vertices + ebp
0042fb9d        long double x87_r7_1 = fconvert.t(*vector)
0042fb9f        long double x87_r6_1 = fconvert.t(edi->x)
0042fba1        x87_r6_1 - x87_r7_1
0042fba8        long double x87_r7_2
0042fba8        if ((((x87_r6_1 < x87_r7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_1, x87_r7_1) ? 1 : 0) << 0xa | (x87_r6_1 == x87_r7_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0042fbb8        x87_r7_2 = fconvert.t(*vector)
0042fbaa        x87_r7_2 = fconvert.t(object->bounds_max.x)
0042fbb0        edi = &object->bounds_max
0042fbba        edi->x = fconvert.s(x87_r7_2)
0042fbbc        long double x87_r7_3 = fconvert.t(ebx->x)
0042fbbe        long double x87_r6_2 = fconvert.t(*vector)
0042fbc0        x87_r6_2 - x87_r7_3
0042fbc7        long double x87_r7_4
0042fbc7        if ((((x87_r6_2 < x87_r7_3 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_2, x87_r7_3) ? 1 : 0) << 0xa | (x87_r6_2 == x87_r7_3 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0042fbd7        x87_r7_4 = fconvert.t(*vector)
0042fbc9        x87_r7_4 = fconvert.t(object->bounds_min.x)
0042fbcf        ebx = &object->bounds_min
0042fbd9        ebx->x = fconvert.s(x87_r7_4)
0042fbdb        long double x87_r7_5 = fconvert.t(vector[1])
0042fbde        long double x87_r6_3 = fconvert.t(object->bounds_max.y)
0042fbe4        x87_r6_3 - x87_r7_5
0042fbeb        long double x87_r7_6
0042fbeb        if ((((x87_r6_3 < x87_r7_5 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_3, x87_r7_5) ? 1 : 0) << 0xa | (x87_r6_3 == x87_r7_5 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0042fbf5        x87_r7_6 = fconvert.t(vector[1])
0042fbed        x87_r7_6 = fconvert.t(object->bounds_max.y)
0042fbf8        object->bounds_max.y = fconvert.s(x87_r7_6)
0042fbfe        long double x87_r7_7 = fconvert.t(object->bounds_min.y)
0042fc04        long double x87_r6_4 = fconvert.t(vector[1])
0042fc07        x87_r6_4 - x87_r7_7
0042fc0e        long double x87_r7_8
0042fc0e        if ((((x87_r6_4 < x87_r7_7 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_4, x87_r7_7) ? 1 : 0) << 0xa | (x87_r6_4 == x87_r7_7 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0042fc18        x87_r7_8 = fconvert.t(vector[1])
0042fc10        x87_r7_8 = fconvert.t(object->bounds_min.y)
0042fc1b        object->bounds_min.y = fconvert.s(x87_r7_8)
0042fc21        long double x87_r7_9 = fconvert.t(vector[2])
0042fc24        long double x87_r6_5 = fconvert.t(object->bounds_max.z)
0042fc2a        x87_r6_5 - x87_r7_9
0042fc31        long double x87_r7_10
0042fc31        if ((((x87_r6_5 < x87_r7_9 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_5, x87_r7_9) ? 1 : 0) << 0xa | (x87_r6_5 == x87_r7_9 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0042fc3b        x87_r7_10 = fconvert.t(vector[2])
0042fc33        x87_r7_10 = fconvert.t(object->bounds_max.z)
0042fc3e        object->bounds_max.z = fconvert.s(x87_r7_10)
0042fc44        long double x87_r7_11 = fconvert.t(object->bounds_min.z)
0042fc4a        long double x87_r6_6 = fconvert.t(vector[2])
0042fc4d        x87_r6_6 - x87_r7_11
0042fc54        long double x87_r7_12
0042fc54        if ((((x87_r6_6 < x87_r7_11 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_6, x87_r7_11) ? 1 : 0) << 0xa | (x87_r6_6 == x87_r7_11 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0042fc5e        x87_r7_12 = fconvert.t(vector[2])
0042fc56        x87_r7_12 = fconvert.t(object->bounds_min.z)
0042fc61        object->bounds_min.z = fconvert.s(x87_r7_12)
0042fc67        long double st0_1 = vector_magnitude(vector)
0042fc6c        long double temp0_1 = fconvert.t(object->bounding_radius)
0042fc6c        st0_1 - temp0_1
0042fc77        if ((((st0_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp0_1) ? 1 : 0) << 0xa | (st0_1 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0042fc79        object->bounding_radius = fconvert.s(st0_1)
0042fc8b        ebp += 0xc
0042fc8e        cond:0_1 = var_10 + 1 s< object->vertex_count
0042fc90        var_10 += 1
0042fc94        do while (cond:0_1)
0042fca1        return
