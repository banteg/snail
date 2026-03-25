/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: orthogonalize_matrix @ 0x44d3d0 */

0044d3db        normalize_vector(arg1)
0044d3e4        normalize_vector(arg1 + 0x10)
0044d3ed        normalize_vector(arg1 + 0x20)
0044d3f8        cross_vectors(arg1, arg1 + 0x10, arg1 + 0x20)
0044d409        return cross_vectors(arg1 + 0x20, arg1, arg1 + 0x10)
