/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rotate_matrix_world_x @ 0x44ce30 */

0044ce32        float angle_1 = angle
0044ce3e        angle = fconvert.s(cosine(angle_1))
0044ce43        long double st0_1 = sine(angle_1)
0044ce68        transform->basis_forward.x = fconvert.s(fconvert.t(angle) * fconvert.t(transform->basis_forward.x) - st0_1 * fconvert.t(transform->basis_up.x))
0044ce6b        transform->basis_up.x = fconvert.s(st0_1 * fconvert.t(transform->basis_forward.x) + fconvert.t(angle) * fconvert.t(transform->basis_up.x))
0044ce8a        transform->basis_forward.y = fconvert.s(fconvert.t(angle) * fconvert.t(transform->basis_forward.y) - st0_1 * fconvert.t(transform->basis_up.y))
0044ce8d        transform->basis_up.y = fconvert.s(st0_1 * fconvert.t(transform->basis_forward.y) + fconvert.t(angle) * fconvert.t(transform->basis_up.y))
0044ceae        transform->basis_forward.z = fconvert.s(fconvert.t(angle) * fconvert.t(transform->basis_forward.z) - st0_1 * fconvert.t(transform->basis_up.z))
0044ceb1        transform->basis_up.z = fconvert.s(st0_1 * fconvert.t(transform->basis_forward.z) + fconvert.t(angle) * fconvert.t(transform->basis_up.z))
0044ceb5        return
