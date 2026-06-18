/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_backdrop_tile_quad @ 0x41a4d0 */

0041a4d0        int32_t ecx
0041a4d0        int32_t var_4_1 = ecx
0041a4e7        float var_4 = fconvert.s(float.t(arg4) * fconvert.t(0.400000006f))
0041a4f5        arg4 = fconvert.s(float.t(arg5) * fconvert.t(0.400000006f))
0041a4f9        request_object_vertices(arg1, 4)
0041a502        request_object_facequads(arg1, 1)
0041a507        struct Vec3* vertices = arg1->vertices
0041a50a        struct ObjectFaceQuad* facequads = arg1->facequads
0041a515        vertices->y = 0f
0041a518        vertices->__offset(0x10).d = 0
0041a51b        vertices->__offset(0x1c).d = 0
0041a51e        vertices->__offset(0x28).d = 0
0041a527        facequads->flags = 0
0041a52a        facequads->vertex_index_a = 0
0041a52e        facequads->vertex_index_b = 1
0041a534        facequads->vertex_index_c = 3
0041a53a        facequads->vertex_index_d = 2
0041a545        facequads->texture_ref = get_or_create_texture_ref(&g_texture_refs, arg6, 0, 0)
0041a553        float result = arg3
0041a564        __builtin_memcpy(&facequads->u0, "\xcd\xcc\x4c\x3f\x00\x00\x80\x3f\xcd\xcc\x4c\x3e\x00\x00\x80\x3f\xcd\xcc\x4c\x3e", 0x14)
0041a56d        facequads->v2 = 0f
0041a570        facequads->u3 = 0.800000012f
0041a573        facequads->v3 = 0f
0041a581        switch (result)
0041a592        case 0
0041a592        result = 0.899999976f
0041a597        vertices->__offset(0x18).d = 0x3f000000
0041a59a        __builtin_strncpy(&vertices->z, "fff?", 4)
0041a59d        __builtin_strncpy(vertices + 0x14, "fff?", 4)
0041a5a0        vertices->__offset(0x20).d = 0x3f000000
0041a5a3        vertices->__offset(0x24).d = 0xbf000000
0041a5aa        vertices->x = fconvert.s(fconvert.t(var_4) + fconvert.t(0.5f))
0041a5b6        vertices->__offset(0x2c).d = 0x3f000000
0041a5b9        vertices->__offset(0xc).d = fconvert.s(fconvert.t(-0.5f) - fconvert.t(arg4))
0041a5c3        case 1
0041a5c3        sub_430a30(facequads)
0041a5d2        result = 0.899999976f
0041a5d7        vertices->__offset(0xc).d = 0x3f000000
0041a5da        __builtin_strncpy(vertices, "fff?", 4)
0041a5dc        vertices->__offset(0x14).d = 0x3f000000
0041a5df        __builtin_strncpy(&vertices[2], "fff?", 4)
0041a5e2        vertices->__offset(0x24).d = 0x3f000000
0041a5e5        vertices->z = fconvert.s(fconvert.t(arg4) + fconvert.t(0.5f))
0041a5f2        vertices->__offset(0x2c).d = 0xbf000000
0041a5f9        vertices->__offset(0x20).d = fconvert.s(fconvert.t(-0.5f) - fconvert.t(var_4))
0041a603        case 2
0041a603        sub_430a30(facequads)
0041a60a        sub_430a30(facequads)
0041a611        sub_430a30(facequads)
0041a620        result = -0.5f
0041a62a        vertices->x = 0xbf000000
0041a62c        vertices->z = 0.5f
0041a62f        vertices->__offset(0xc).d = 0xbf666666
0041a632        vertices->__offset(0x18).d = 0xbf000000
0041a635        vertices->__offset(0x14).d = fconvert.s(fconvert.t(var_4) + fconvert.t(0.5f))
0041a642        vertices->__offset(0x20).d = 0xbf000000
0041a645        vertices->__offset(0x24).d = 0xbf666666
0041a648        vertices->__offset(0x2c).d = fconvert.s(fconvert.t(-0.5f) - fconvert.t(arg4))
0041a64f        case 3
0041a64f        sub_430a30(facequads)
0041a656        sub_430a30(facequads)
0041a665        result = -0.5f
0041a66f        vertices->x = 0x3f000000
0041a671        vertices->z = -0.5f
0041a674        vertices->__offset(0xc).d = 0xbf000000
0041a677        vertices->__offset(0x14).d = 0xbf000000
0041a67a        vertices->__offset(0x18).d = fconvert.s(fconvert.t(arg4) + fconvert.t(0.5f))
0041a687        vertices->__offset(0x20).d = 0xbf666666
0041a68a        vertices->__offset(0x2c).d = 0xbf666666
0041a68d        vertices->__offset(0x24).d = fconvert.s(fconvert.t(-0.5f) - fconvert.t(var_4))
0041a69a        float* ecx_10 = &vertices->z
0041a69d        int32_t i_1 = 4
0041a9ef        int32_t i
0041a6a5        if (arg2 - 1 u<= 6)
0041a6ab        switch (arg2)
0041a6b2        case 1
0041a6b2        long double x87_r7_20 = fconvert.t(ecx_10[-2])
0041a6b5        long double temp1_1 = fconvert.t(0f)
0041a6b5        x87_r7_20 - temp1_1
0041a6bb        result.w = (x87_r7_20 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp1_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp1_1 ? 1 : 0) << 0xe
0041a6c0        if ((result:1.b & 1) != 0)
0041a6c6        long double x87_r7_21 = fconvert.t(*ecx_10)
0041a6c8        long double temp8_1 = fconvert.t(0f)
0041a6c8        x87_r7_21 - temp8_1
0041a6ce        result.w = (x87_r7_21 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp8_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp8_1 ? 1 : 0) << 0xe
0041a6d3        if ((result:1.b & 1) != 0)
0041a6d9        long double x87_r7_22 = fconvert.t(ecx_10[-2])
0041a6dc        long double temp12_1 = fconvert.t(0f)
0041a6dc        x87_r7_22 - temp12_1
0041a6e2        result.w = (x87_r7_22 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_22, temp12_1) ? 1 : 0) << 0xa | (x87_r7_22 == temp12_1 ? 1 : 0) << 0xe
0041a6e7        if ((result:1.b & 1) == 0)
0041a6ef        long double x87_r7_23 = fconvert.t(ecx_10[-2])
0041a6f2        long double temp16_1 = fconvert.t(0f)
0041a6f2        x87_r7_23 - temp16_1
0041a6f8        arg4 = 0
0041a6fc        result.w = (x87_r7_23 < temp16_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp16_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp16_1 ? 1 : 0) << 0xe
0041a701        if ((result:1.b & 0x40) == 0)
0041a703        arg4 = 1
0041a6e9        arg4 = 0xffffffff
0041a718        ecx_10[-2] = fconvert.s(fconvert.t(ecx_10[-2]) - float.t(arg4) * fconvert.t(0.200000003f))
0041a71b        long double x87_r7_27 = fconvert.t(*ecx_10)
0041a71d        long double temp20_1 = fconvert.t(0f)
0041a71d        x87_r7_27 - temp20_1
0041a723        result.w = (x87_r7_27 < temp20_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_27, temp20_1) ? 1 : 0) << 0xa | (x87_r7_27 == temp20_1 ? 1 : 0) << 0xe
0041a728        if ((result:1.b & 1) == 0)
0041a741        long double x87_r7_31 = fconvert.t(*ecx_10)
0041a743        long double temp24_1 = fconvert.t(0f)
0041a743        x87_r7_31 - temp24_1
0041a749        arg4 = 0
0041a74d        result.w = (x87_r7_31 < temp24_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp24_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp24_1 ? 1 : 0) << 0xe
0041a752        if ((result:1.b & 0x40) == 0)
0041a754        arg4 = 1
0041a768        *ecx_10 = fconvert.s(fconvert.t(*ecx_10) - float.t(arg4) * fconvert.t(0.200000003f))
0041a73a        *ecx_10 = fconvert.s(fconvert.t(*ecx_10) - float.t(0xffffffff) * fconvert.t(0.200000003f))
0041a76f        case 2
0041a76f        long double x87_r7_35 = fconvert.t(ecx_10[-2])
0041a772        long double temp2_1 = fconvert.t(0f)
0041a772        x87_r7_35 - temp2_1
0041a778        result.w = (x87_r7_35 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_35, temp2_1) ? 1 : 0) << 0xa | (x87_r7_35 == temp2_1 ? 1 : 0) << 0xe
0041a77d        if ((result:1.b & 1) != 0)
0041a783        long double x87_r7_36 = fconvert.t(*ecx_10)
0041a785        long double temp9_1 = fconvert.t(0f)
0041a785        x87_r7_36 - temp9_1
0041a78b        result.w = (x87_r7_36 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_36, temp9_1) ? 1 : 0) << 0xa | (x87_r7_36 == temp9_1 ? 1 : 0) << 0xe
0041a790        if ((result:1.b & 0x41) == 0)
0041a796        long double x87_r7_37 = fconvert.t(ecx_10[-2])
0041a799        long double temp13_1 = fconvert.t(0f)
0041a799        x87_r7_37 - temp13_1
0041a79f        result.w = (x87_r7_37 < temp13_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_37, temp13_1) ? 1 : 0) << 0xa | (x87_r7_37 == temp13_1 ? 1 : 0) << 0xe
0041a7a4        if ((result:1.b & 1) == 0)
0041a7ac        long double x87_r7_38 = fconvert.t(ecx_10[-2])
0041a7af        long double temp17_1 = fconvert.t(0f)
0041a7af        x87_r7_38 - temp17_1
0041a7b5        arg4 = 0
0041a7b9        result.w = (x87_r7_38 < temp17_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_38, temp17_1) ? 1 : 0) << 0xa | (x87_r7_38 == temp17_1 ? 1 : 0) << 0xe
0041a7be        if ((result:1.b & 0x40) == 0)
0041a7c0        arg4 = 1
0041a7a6        arg4 = 0xffffffff
0041a7d5        ecx_10[-2] = fconvert.s(fconvert.t(ecx_10[-2]) - float.t(arg4) * fconvert.t(0.200000003f))
0041a7d8        long double x87_r7_42 = fconvert.t(*ecx_10)
0041a7da        long double temp21_1 = fconvert.t(0f)
0041a7da        x87_r7_42 - temp21_1
0041a7e0        result.w = (x87_r7_42 < temp21_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_42, temp21_1) ? 1 : 0) << 0xa | (x87_r7_42 == temp21_1 ? 1 : 0) << 0xe
0041a7e5        if ((result:1.b & 1) == 0)
0041a7fe        long double x87_r7_46 = fconvert.t(*ecx_10)
0041a800        long double temp25_1 = fconvert.t(0f)
0041a800        x87_r7_46 - temp25_1
0041a806        arg4 = 0
0041a80a        result.w = (x87_r7_46 < temp25_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_46, temp25_1) ? 1 : 0) << 0xa | (x87_r7_46 == temp25_1 ? 1 : 0) << 0xe
0041a80f        if ((result:1.b & 0x40) == 0)
0041a811        arg4 = 1
0041a825        *ecx_10 = fconvert.s(fconvert.t(*ecx_10) - float.t(arg4) * fconvert.t(0.200000003f))
0041a7f7        *ecx_10 = fconvert.s(fconvert.t(*ecx_10) - float.t(0xffffffff) * fconvert.t(0.200000003f))
0041a82c        case 3
0041a82c        long double x87_r7_50 = fconvert.t(ecx_10[-2])
0041a82f        long double temp3_1 = fconvert.t(0f)
0041a82f        x87_r7_50 - temp3_1
0041a835        result.w = (x87_r7_50 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_50, temp3_1) ? 1 : 0) << 0xa | (x87_r7_50 == temp3_1 ? 1 : 0) << 0xe
0041a83a        if ((result:1.b & 0x41) == 0)
0041a840        long double x87_r7_51 = fconvert.t(*ecx_10)
0041a842        long double temp10_1 = fconvert.t(0f)
0041a842        x87_r7_51 - temp10_1
0041a848        result.w = (x87_r7_51 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_51, temp10_1) ? 1 : 0) << 0xa | (x87_r7_51 == temp10_1 ? 1 : 0) << 0xe
0041a84d        if ((result:1.b & 1) != 0)
0041a853        long double x87_r7_52 = fconvert.t(ecx_10[-2])
0041a856        long double temp14_1 = fconvert.t(0f)
0041a856        x87_r7_52 - temp14_1
0041a85c        result.w = (x87_r7_52 < temp14_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_52, temp14_1) ? 1 : 0) << 0xa | (x87_r7_52 == temp14_1 ? 1 : 0) << 0xe
0041a861        if ((result:1.b & 1) == 0)
0041a869        long double x87_r7_53 = fconvert.t(ecx_10[-2])
0041a86c        long double temp18_1 = fconvert.t(0f)
0041a86c        x87_r7_53 - temp18_1
0041a872        arg4 = 0
0041a876        result.w = (x87_r7_53 < temp18_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_53, temp18_1) ? 1 : 0) << 0xa | (x87_r7_53 == temp18_1 ? 1 : 0) << 0xe
0041a87b        if ((result:1.b & 0x40) == 0)
0041a87d        arg4 = 1
0041a863        arg4 = 0xffffffff
0041a892        ecx_10[-2] = fconvert.s(fconvert.t(ecx_10[-2]) - float.t(arg4) * fconvert.t(0.200000003f))
0041a895        long double x87_r7_57 = fconvert.t(*ecx_10)
0041a897        long double temp22_1 = fconvert.t(0f)
0041a897        x87_r7_57 - temp22_1
0041a89d        result.w = (x87_r7_57 < temp22_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_57, temp22_1) ? 1 : 0) << 0xa | (x87_r7_57 == temp22_1 ? 1 : 0) << 0xe
0041a8a2        if ((result:1.b & 1) == 0)
0041a8bb        long double x87_r7_61 = fconvert.t(*ecx_10)
0041a8bd        long double temp26_1 = fconvert.t(0f)
0041a8bd        x87_r7_61 - temp26_1
0041a8c3        arg4 = 0
0041a8c7        result.w = (x87_r7_61 < temp26_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_61, temp26_1) ? 1 : 0) << 0xa | (x87_r7_61 == temp26_1 ? 1 : 0) << 0xe
0041a8cc        if ((result:1.b & 0x40) == 0)
0041a8ce        arg4 = 1
0041a8e2        *ecx_10 = fconvert.s(fconvert.t(*ecx_10) - float.t(arg4) * fconvert.t(0.200000003f))
0041a8b4        *ecx_10 = fconvert.s(fconvert.t(*ecx_10) - float.t(0xffffffff) * fconvert.t(0.200000003f))
0041a8e9        case 4
0041a8e9        long double x87_r7_65 = fconvert.t(ecx_10[-2])
0041a8ec        long double temp4_1 = fconvert.t(0f)
0041a8ec        x87_r7_65 - temp4_1
0041a8f2        result.w = (x87_r7_65 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_65, temp4_1) ? 1 : 0) << 0xa | (x87_r7_65 == temp4_1 ? 1 : 0) << 0xe
0041a8f7        if ((result:1.b & 0x41) == 0)
0041a8fd        long double x87_r7_66 = fconvert.t(*ecx_10)
0041a8ff        long double temp11_1 = fconvert.t(0f)
0041a8ff        x87_r7_66 - temp11_1
0041a905        result.w = (x87_r7_66 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_66, temp11_1) ? 1 : 0) << 0xa | (x87_r7_66 == temp11_1 ? 1 : 0) << 0xe
0041a90a        if ((result:1.b & 0x41) == 0)
0041a910        long double x87_r7_67 = fconvert.t(ecx_10[-2])
0041a913        long double temp15_1 = fconvert.t(0f)
0041a913        x87_r7_67 - temp15_1
0041a919        result.w = (x87_r7_67 < temp15_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_67, temp15_1) ? 1 : 0) << 0xa | (x87_r7_67 == temp15_1 ? 1 : 0) << 0xe
0041a91e        if ((result:1.b & 1) == 0)
0041a926        long double x87_r7_68 = fconvert.t(ecx_10[-2])
0041a929        long double temp19_1 = fconvert.t(0f)
0041a929        x87_r7_68 - temp19_1
0041a92f        arg4 = 0
0041a933        result.w = (x87_r7_68 < temp19_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_68, temp19_1) ? 1 : 0) << 0xa | (x87_r7_68 == temp19_1 ? 1 : 0) << 0xe
0041a938        if ((result:1.b & 0x40) == 0)
0041a93a        arg4 = 1
0041a920        arg4 = 0xffffffff
0041a94f        ecx_10[-2] = fconvert.s(fconvert.t(ecx_10[-2]) - float.t(arg4) * fconvert.t(0.200000003f))
0041a952        long double x87_r7_72 = fconvert.t(*ecx_10)
0041a954        long double temp23_1 = fconvert.t(0f)
0041a954        x87_r7_72 - temp23_1
0041a95a        result.w = (x87_r7_72 < temp23_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_72, temp23_1) ? 1 : 0) << 0xa | (x87_r7_72 == temp23_1 ? 1 : 0) << 0xe
0041a95f        if ((result:1.b & 1) == 0)
0041a975        long double x87_r7_76 = fconvert.t(*ecx_10)
0041a977        long double temp27_1 = fconvert.t(0f)
0041a977        x87_r7_76 - temp27_1
0041a97d        arg4 = 0
0041a981        result.w = (x87_r7_76 < temp27_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_76, temp27_1) ? 1 : 0) << 0xa | (x87_r7_76 == temp27_1 ? 1 : 0) << 0xe
0041a986        if ((result:1.b & 0x40) == 0)
0041a988        arg4 = 1
0041a99c        *ecx_10 = fconvert.s(fconvert.t(*ecx_10) - float.t(arg4) * fconvert.t(0.200000003f))
0041a971        *ecx_10 = fconvert.s(fconvert.t(*ecx_10) - float.t(0xffffffff) * fconvert.t(0.200000003f))
0041a9a0        case 5
0041a9a0        long double x87_r7_80 = fconvert.t(ecx_10[-2])
0041a9a3        long double temp5_1 = fconvert.t(0f)
0041a9a3        x87_r7_80 - temp5_1
0041a9a9        result.w = (x87_r7_80 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_80, temp5_1) ? 1 : 0) << 0xa | (x87_r7_80 == temp5_1 ? 1 : 0) << 0xe
0041a9ae        if ((result:1.b & 0x41) == 0)
0041a9ae        goto label_41a9c2
0041a9c2        case 6
0041a9c2        label_41a9c2:
0041a9c2        long double x87_r7_82 = fconvert.t(*ecx_10)
0041a9c4        long double temp7_1 = fconvert.t(0f)
0041a9c4        x87_r7_82 - temp7_1
0041a9ca        result.w = (x87_r7_82 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_82, temp7_1) ? 1 : 0) << 0xa | (x87_r7_82 == temp7_1 ? 1 : 0) << 0xe
0041a9cf        if ((result:1.b & 0x41) == 0)
0041a9d1        result = *ecx_10
0041a9d3        long double x87_r7_83 = fconvert.t(ecx_10[-1])
0041a9d8        long double x87_r7_84
0041a9d8        if (result != 0x3f000000)
0041a9e2        x87_r7_84 = x87_r7_83 + fconvert.t(0.600000024f)
0041a9da        x87_r7_84 = x87_r7_83 + fconvert.t(0.5f)
0041a9e8        ecx_10[-1] = fconvert.s(x87_r7_84)
0041a9b2        case 7
0041a9b2        long double x87_r7_81 = fconvert.t(ecx_10[-2])
0041a9b5        long double temp6_1 = fconvert.t(0f)
0041a9b5        x87_r7_81 - temp6_1
0041a9bb        result.w = (x87_r7_81 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_81, temp6_1) ? 1 : 0) << 0xa | (x87_r7_81 == temp6_1 ? 1 : 0) << 0xe
0041a9c0        if ((result:1.b & 1) != 0)
0041a9c0        goto label_41a9c2
0041a9eb        ecx_10 = &ecx_10[3]
0041a9ee        i = i_1
0041a9ee        i_1 -= 1
0041a9ef        do while (i != 1)
0041a9fa        return result
