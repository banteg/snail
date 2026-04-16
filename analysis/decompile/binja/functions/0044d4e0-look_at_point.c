/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: look_at_point @ 0x44d4e0 */

0044d508        struct Vec3 direction
0044d508        direction.y = fconvert.s(fconvert.t(target->y) - fconvert.t(transform->position.y))
0044d50c        direction.x = fconvert.s(fconvert.t(target->x) - fconvert.t(transform->position.x))
0044d51d        direction.z = fconvert.s(fconvert.t(target->z) - fconvert.t(transform->position.z))
0044d521        set_matrix_z_direction(transform, &direction)
0044d529        return
