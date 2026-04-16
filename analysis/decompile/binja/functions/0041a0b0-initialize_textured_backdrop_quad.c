/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_textured_backdrop_quad @ 0x41a0b0 */

0041a0ba        request_object_vertices(arg1, 4)
0041a0c3        request_object_facequads(arg1, 1)
0041a0cc        long double x87_r7_1 = fconvert.t(arg3) + fconvert.t(0.5f)
0041a0d2        struct Vec3* vertices = arg1->vertices
0041a0d5        struct ObjectFaceQuad* facequads = arg1->facequads
0041a0e4        vertices->y = 0f
0041a0e7        vertices->x = fconvert.s(x87_r7_1)
0041a0e9        vertices->__offset(0x18).d = fconvert.s(x87_r7_1)
0041a0ec        vertices->z = 0.5f
0041a0ef        vertices->__offset(0xc).d = 0xbf000000
0041a0f2        vertices->__offset(0x10).d = 0
0041a0f5        vertices->__offset(0x14).d = 0x3f000000
0041a0f8        vertices->__offset(0x1c).d = 0
0041a0fb        vertices->__offset(0x20).d = 0xbf000000
0041a0fe        vertices->__offset(0x24).d = 0xbf000000
0041a101        vertices->__offset(0x28).d = 0
0041a104        vertices->__offset(0x2c).d = 0xbf000000
0041a113        facequads->flags = 0
0041a116        facequads->vertex_index_a = 0
0041a11a        facequads->vertex_index_b = 1
0041a120        facequads->vertex_index_c = 3
0041a126        facequads->vertex_index_d = 2
0041a12c        struct TextureRef* eax_1 = get_or_create_texture_ref(&data_4b7790, arg2, 0, 0)
0041a135        long double x87_r7_3 = fconvert.t(arg3) + fconvert.t(1f)
0041a13b        facequads->texture_ref = eax_1
0041a143        eax_1->__offset(0x0).d |= 2
0041a14a        facequads->u1 = fconvert.s(x87_r7_3)
0041a14d        facequads->u2 = fconvert.s(x87_r7_3)
0041a150        facequads->u0 = 0f
0041a153        facequads->v2 = 0f
0041a156        facequads->u3 = 0f
0041a159        facequads->v3 = 0f
0041a15c        facequads->v0 = 1f
0041a15f        facequads->v1 = 1f
0041a164        return 0x3f800000
