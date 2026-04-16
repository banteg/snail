/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rotate_matrix_world_y @ 0x44cec0 */

0044cec2        float angle_1 = angle
0044cece        angle = fconvert.s(cosine(angle_1))
0044ced3        long double st0_1 = sine(angle_1)
0044cef6        transform->basis_right.x = fconvert.s(fconvert.t(angle) * fconvert.t(transform->basis_right.x) - st0_1 * fconvert.t(transform->basis_forward.x))
0044cef8        transform->basis_forward.x = fconvert.s(st0_1 * fconvert.t(transform->basis_right.x) + fconvert.t(angle) * fconvert.t(transform->basis_forward.x))
0044cf17        transform->basis_right.y = fconvert.s(fconvert.t(angle) * fconvert.t(transform->basis_right.y) - st0_1 * fconvert.t(transform->basis_forward.y))
0044cf1a        transform->basis_forward.y = fconvert.s(st0_1 * fconvert.t(transform->basis_right.y) + fconvert.t(angle) * fconvert.t(transform->basis_forward.y))
0044cf3b        transform->basis_right.z = fconvert.s(fconvert.t(angle) * fconvert.t(transform->basis_right.z) - st0_1 * fconvert.t(transform->basis_forward.z))
0044cf3e        transform->basis_forward.z = fconvert.s(st0_1 * fconvert.t(transform->basis_right.z) + fconvert.t(angle) * fconvert.t(transform->basis_forward.z))
0044cf42        return
