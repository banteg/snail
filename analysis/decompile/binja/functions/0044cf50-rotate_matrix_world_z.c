/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rotate_matrix_world_z @ 0x44cf50 */

0044cf52        float angle_1 = angle
0044cf5e        angle = fconvert.s(cosine(angle_1))
0044cf63        int32_t result
0044cf63        long double st0_1
0044cf63        st0_1, result = sine(angle_1)
0044cf86        transform->basis_up.x = fconvert.s(fconvert.t(angle) * fconvert.t(transform->basis_up.x) - st0_1 * fconvert.t(transform->basis_right.x))
0044cf89        transform->basis_right.x = fconvert.s(fconvert.t(angle) * fconvert.t(transform->basis_right.x) + st0_1 * fconvert.t(transform->basis_up.x))
0044cfa7        transform->basis_up.y = fconvert.s(fconvert.t(angle) * fconvert.t(transform->basis_up.y) - st0_1 * fconvert.t(transform->basis_right.y))
0044cfaa        transform->basis_right.y = fconvert.s(st0_1 * fconvert.t(transform->basis_up.y) + fconvert.t(angle) * fconvert.t(transform->basis_right.y))
0044cfcb        transform->basis_up.z = fconvert.s(fconvert.t(angle) * fconvert.t(transform->basis_up.z) - st0_1 * fconvert.t(transform->basis_right.z))
0044cfce        transform->basis_right.z = fconvert.s(st0_1 * fconvert.t(transform->basis_up.z) + fconvert.t(angle) * fconvert.t(transform->basis_right.z))
0044cfd2        return result
