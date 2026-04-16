/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: orthogonalize_matrix @ 0x44d3d0 */

0044d3db        normalize_vector(transform)
0044d3e4        normalize_vector(&transform->basis_up)
0044d3ed        normalize_vector(&transform->basis_forward)
0044d3f8        cross_vectors(transform, &transform->basis_up.x, &transform->basis_forward)
0044d409        return cross_vectors(&transform->basis_forward.x, transform, &transform->basis_up.x)
