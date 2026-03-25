/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: compute_kind42_attachment_transform @ 0x42b920 */

0042b920        int32_t ecx
0042b920        int32_t var_4_1 = ecx
0042b92b        int32_t var_10 = ecx
0042b964        *arg5 = fconvert.s(atan2_positive(4f, fconvert.s(square_root(fconvert.s(fconvert.t(arg1) * fconvert.t(arg1) - fconvert.t(16f))))) * fconvert.t(arg2) * fconvert.t(0.25f))
0042b966        set_matrix_rotation_identity(arg4)
0042b970        rotate_matrix_world_z(arg4, *arg5)
0042b980        arg2 = fconvert.s(fconvert.t(arg1) - fconvert.t(arg3))
0042b98d        arg4[0xc] = fconvert.s(sine(*arg5) * fconvert.t(arg2))
0042b993        int32_t result
0042b993        long double st0_3
0042b993        st0_3, result = cosine(*arg5)
0042b9a3        arg4[0xd] = fconvert.s(fconvert.t(arg1) - st0_3 * fconvert.t(arg2))
0042b9aa        *arg5 = fconvert.s(fneg(fconvert.t(*arg5)))
0042b9af        return result
