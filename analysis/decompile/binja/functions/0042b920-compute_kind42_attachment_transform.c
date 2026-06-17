/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: compute_kind42_attachment_transform @ 0x42b920 */

0042b920        struct PathTemplate* self_2 = self
0042b92b        struct PathTemplate* self_1 = self
0042b964        *out_angle = fconvert.s(atan2_positive(4f, fconvert.s(square_root(fconvert.s(fconvert.t(radius) * fconvert.t(radius) - fconvert.t(16f))))) * fconvert.t(x) * fconvert.t(0.25f))
0042b966        set_matrix_rotation_identity(transform)
0042b970        rotate_matrix_world_z(transform, *out_angle)
0042b980        x = fconvert.s(fconvert.t(radius) - fconvert.t(y))
0042b98d        transform->position.x = fconvert.s(sine(*out_angle) * fconvert.t(x))
0042b9a3        transform->position.y = fconvert.s(fconvert.t(radius) - cosine(*out_angle) * fconvert.t(x))
0042b9aa        *out_angle = fconvert.s(fneg(fconvert.t(*out_angle)))
0042b9af        return
