/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: invert_matrix_from_source @ 0x44d330 */

0044d34b        float* arg_4
0044d34b        out->position.x = fconvert.s(fneg(fconvert.t(arg_4[0xd]) * fconvert.t(arg_4[1]) + fconvert.t(arg_4[2]) * fconvert.t(arg_4[0xe]) + fconvert.t(arg_4[0xc]) * fconvert.t(*arg_4)))
0044d366        out->position.y = fconvert.s(fneg(fconvert.t(arg_4[0xd]) * fconvert.t(arg_4[5]) + fconvert.t(arg_4[6]) * fconvert.t(arg_4[0xe]) + fconvert.t(arg_4[0xc]) * fconvert.t(arg_4[4])))
0044d381        out->position.z = fconvert.s(fneg(fconvert.t(arg_4[0xd]) * fconvert.t(arg_4[9]) + fconvert.t(arg_4[0xc]) * fconvert.t(arg_4[8]) + fconvert.t(arg_4[0xe]) * fconvert.t(arg_4[0xa])))
0044d386        out->basis_right.x = *arg_4
0044d38b        out->basis_right.y = arg_4[4]
0044d391        out->basis_right.z = arg_4[8]
0044d397        out->basis_up.x = arg_4[1]
0044d39d        out->basis_up.y = arg_4[5]
0044d3a3        out->basis_up.z = arg_4[9]
0044d3a9        out->basis_forward.x = arg_4[2]
0044d3af        out->basis_forward.y = arg_4[6]
0044d3b5        out->basis_forward.z = arg_4[0xa]
0044d3ba        out->basis_forward.w = 0f
0044d3bd        out->basis_up.w = 0f
0044d3c0        out->basis_right.w = 0f
0044d3c3        out->position.w = 1f
0044d3ca        return 0
