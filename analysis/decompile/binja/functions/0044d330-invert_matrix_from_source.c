/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: invert_matrix_from_source @ 0x44d330 */

0044d34b        out->position.x = fconvert.s(fneg(fconvert.t(source->position.y) * fconvert.t(source->basis_right.y) + fconvert.t(source->basis_right.z) * fconvert.t(source->position.z) + fconvert.t(source->position.x) * fconvert.t(source->basis_right.x)))
0044d366        out->position.y = fconvert.s(fneg(fconvert.t(source->position.y) * fconvert.t(source->basis_up.y) + fconvert.t(source->basis_up.z) * fconvert.t(source->position.z) + fconvert.t(source->position.x) * fconvert.t(source->basis_up.x)))
0044d381        out->position.z = fconvert.s(fneg(fconvert.t(source->position.y) * fconvert.t(source->basis_forward.y) + fconvert.t(source->position.x) * fconvert.t(source->basis_forward.x) + fconvert.t(source->position.z) * fconvert.t(source->basis_forward.z)))
0044d386        out->basis_right.x = source->basis_right.x
0044d38b        out->basis_right.y = source->basis_up.x
0044d391        out->basis_right.z = source->basis_forward.x
0044d397        out->basis_up.x = source->basis_right.y
0044d39d        out->basis_up.y = source->basis_up.y
0044d3a3        out->basis_up.z = source->basis_forward.y
0044d3a9        out->basis_forward.x = source->basis_right.z
0044d3af        out->basis_forward.y = source->basis_up.z
0044d3b5        out->basis_forward.z = source->basis_forward.z
0044d3ba        out->basis_forward_w = 0f
0044d3bd        out->basis_up_w = 0f
0044d3c0        out->basis_right_w = 0f
0044d3c3        out->position_w = 1f
0044d3ca        return
