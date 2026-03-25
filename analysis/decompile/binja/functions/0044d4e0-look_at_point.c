/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: look_at_point @ 0x44d4e0 */

0044d508        struct Vec3 direction
0044d508        direction.y = fconvert.s(fconvert.t(arg2[1]) - fconvert.t(arg1->position.y))
0044d50c        direction.x = fconvert.s(fconvert.t(*arg2) - fconvert.t(arg1->position.x))
0044d51d        direction.z = fconvert.s(fconvert.t(arg2[2]) - fconvert.t(arg1->position.z))
0044d529        return set_matrix_z_direction(arg1, &direction)
