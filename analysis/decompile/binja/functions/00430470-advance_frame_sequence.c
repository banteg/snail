/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: advance_frame_sequence @ 0x430470 */

00430471        int32_t current_frame_index = movie->current_frame_index
00430478        struct ObjectFaceQuad* facequads = movie->object.facequads
00430485        movie->current_texture_ref = facequads[current_frame_index].texture_ref
0043048b        int32_t sequence_flags = movie->sequence_flags
00430494        if ((sequence_flags.b & 0x11) != 0)
00430494        return
004304a0        long double x87_r7_2 = fconvert.t(movie->phase_step) + fconvert.t(movie->phase)
004304a6        long double temp0_1 = fconvert.t(1f)
004304a6        x87_r7_2 - temp0_1
004304ac        movie->phase = fconvert.s(x87_r7_2)
004304ac        bool c1_1 = unknown  {fst dword [ecx+0xe4], st0}
004304b7        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
004304c6        movie->phase = fconvert.s(x87_r7_2 - fconvert.t(1f))
004304cc        if ((sequence_flags.b & 8) == 0)
0043050a        int32_t facequad_count = movie->object.facequad_count
0043050f        movie->current_frame_index = current_frame_index + 1
00430515        if (current_frame_index + 1 == facequad_count)
0043051a        if ((sequence_flags.b & 4) != 0)
00430522        movie->current_frame_index = facequad_count - 2
00430528        movie->sequence_flags = sequence_flags | 8
00430533        if ((sequence_flags.b & 2) != 0)
0043053e        movie->current_frame_index = 0
00430538        movie->sequence_flags = sequence_flags | 1
0043053e        movie->current_frame_index = 0
004304d4        movie->current_frame_index = current_frame_index - 1
004304da        if (current_frame_index == 0)
004304df        if ((sequence_flags.b & 4) != 0)
004304e4        movie->current_frame_index = 1
004304ee        movie->sequence_flags = sequence_flags & 0xfffffff7
004304f9        if ((sequence_flags.b & 2) == 0)
00430538        movie->sequence_flags = sequence_flags | 1
0043053e        movie->current_frame_index = 0
004304ff        movie->current_frame_index = movie->object.facequad_count - 1
0043055c        movie->current_texture_ref = facequads[movie->current_frame_index].texture_ref
00430564        return
