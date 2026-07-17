/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_backdrop_slice_quad @ 0x41a1c0 */

0041a1ca        request_object_vertices(object, 4)
0041a1d3        request_object_facequads(object, 1)
0041a1dc        enum ObjectFlag flags = object->flags
0041a1df        struct Vec3* vertices = object->vertices
0041a1e2        long double x87_r7_1 = fconvert.t(x_offset) + fconvert.t(0.5f)
0041a1e8        flags.b |= 0x80
0041a1ed        object->flags = flags
0041a1f0        struct ObjectFaceQuad* facequads = object->facequads
0041a1fd        vertices->x = fconvert.s(x87_r7_1)
0041a1ff        vertices->__offset(0x18).d = fconvert.s(x87_r7_1)
0041a202        vertices->y = 0f
0041a205        vertices->z = 0.5f
0041a208        vertices->__offset(0xc).d = 0xbf000000
0041a20b        vertices->__offset(0x10).d = 0
0041a20e        vertices->__offset(0x14).d = 0x3f000000
0041a211        vertices->__offset(0x1c).d = 0
0041a214        vertices->__offset(0x20).d = 0xbf000000
0041a217        vertices->__offset(0x24).d = 0xbf000000
0041a21a        vertices->__offset(0x28).d = 0
0041a21d        vertices->__offset(0x2c).d = 0xbf000000
0041a22c        facequads->.header_word = 0
0041a22f        facequads->vertex_0 = 0
0041a233        facequads->vertex_1 = 1
0041a239        facequads->vertex_2 = 3
0041a23f        facequads->vertex_3 = 2
0041a245        struct TextureRef* eax_1 = get_or_create_texture_ref(&g_texture_refs, texture_path, 0, 0)
0041a254        facequads->texture_ref = eax_1
0041a25c        long double x87_r7_4 = (fconvert.t(x_offset) + fconvert.t(1f)) * fconvert.t(-0.125f)
0041a262        eax_1->flags |= 0x2
0041a269        facequads->uv[1].u = 0
0041a26c        facequads->uv[2].u = 0
0041a26f        facequads->uv[2].v = 0f
0041a272        facequads->uv[3].v = 0f
0041a275        facequads->uv[0].u = fconvert.s(x87_r7_4)
0041a278        facequads->uv[3].u = fconvert.s(x87_r7_4)
0041a27b        facequads->uv[0].v = 0.125f
0041a27e        facequads->uv[1].v = 0.125f
0041a283        return
