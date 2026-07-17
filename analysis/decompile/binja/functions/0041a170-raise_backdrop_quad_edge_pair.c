/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: raise_backdrop_quad_edge_pair @ 0x41a170 */

0041a17a        struct Vec3* vertices = object->vertices
0041a17d        if (selector s> 0)
0041a199        label_41a199:
0041a19e        int32_t edx_1 = g_backdrop_raise_second_vertex_index * 3
0041a1af        (&vertices->y)[edx_1] = fconvert.s(fconvert.t((&vertices->y)[edx_1]) + fconvert.t(0.5f))
0041a1af        return
0041a184        int32_t eax_1 = g_backdrop_raise_first_vertex_index * 3
0041a195        (&vertices->y)[eax_1] = fconvert.s(fconvert.t((&vertices->y)[eax_1]) + fconvert.t(0.5f))
0041a197        if (selector s>= 0)
0041a197        goto label_41a199
0041a1b1        return
