/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_perspective_projection_matrix @ 0x450314 */

00450326        float* var_10 = &vertical_fov_radians
0045032c        float var_8
0045032c        int32_t* var_14 = &var_8
0045033b        long double st0
0045033b        long double st1
0045033b        bool c1
0045033b        bool c2
0045033b        st1, st0, c1, c2 = __fsincos(fconvert.t(fconvert.s(fconvert.t(vertical_fov_radians) * fconvert.t(0.5f))))
0045033d        vertical_fov_radians = fconvert.s(st0)
0045033f        var_8 = fconvert.s(st1)
00450347        long double x87_r7_5 = fconvert.t(vertical_fov_radians) / fconvert.t(var_8)
0045034a        matrix->basis_forward_w = -1f
00450356        matrix->basis_right.x = fconvert.s(x87_r7_5 / fconvert.t(aspect_ratio))
0045035a        matrix->basis_right.y = fconvert.s(float.t(0))
0045035f        matrix->basis_right.z = fconvert.s(float.t(0))
00450364        matrix->basis_right_w = fconvert.s(float.t(0))
00450369        matrix->basis_up.x = fconvert.s(float.t(0))
0045036c        matrix->basis_up.y = fconvert.s(x87_r7_5)
00450371        matrix->basis_up.z = fconvert.s(float.t(0))
00450376        matrix->basis_up_w = fconvert.s(float.t(0))
0045037b        matrix->basis_forward.x = fconvert.s(float.t(0))
00450380        matrix->basis_forward.y = fconvert.s(float.t(0))
00450389        long double x87_r7_12 = fconvert.t(far_z) / (fconvert.t(near_z) - fconvert.t(far_z))
0045038c        matrix->basis_forward.z = fconvert.s(x87_r7_12)
00450391        matrix->position.x = fconvert.s(float.t(0))
00450396        matrix->position.y = fconvert.s(float.t(0))
0045039c        matrix->position.z = fconvert.s(x87_r7_12 * fconvert.t(near_z))
004503a1        matrix->position_w = fconvert.s(float.t(0))
004503a5        return matrix
