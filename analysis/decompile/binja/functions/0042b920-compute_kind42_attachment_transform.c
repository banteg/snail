/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: compute_kind42_attachment_transform @ 0x42b920 */

0042b920        int32_t ecx
0042b920        int32_t var_4_1 = ecx
0042b92b        int32_t var_10 = ecx
0042b964        *out_angle = fconvert.s(atan2_positive(4f, fconvert.s(square_root(fconvert.s(fconvert.t(arg1) * fconvert.t(arg1) - fconvert.t(16f))))) * fconvert.t(arg2) * fconvert.t(0.25f))
0042b966        set_matrix_rotation_identity(transform)
0042b970        rotate_matrix_world_z(transform, *out_angle)
0042b980        arg2 = fconvert.s(fconvert.t(arg1) - fconvert.t(arg3))
0042b98d        transform->position.x = fconvert.s(sine(*out_angle) * fconvert.t(arg2))
0042b993        int32_t result
0042b993        long double st0_3
0042b993        st0_3, result = cosine(*out_angle)
0042b9a3        transform->position.y = fconvert.s(fconvert.t(arg1) - st0_3 * fconvert.t(arg2))
0042b9aa        *out_angle = fconvert.s(fneg(fconvert.t(*out_angle)))
0042b9af        return result
