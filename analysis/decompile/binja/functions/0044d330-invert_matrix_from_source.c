/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: invert_matrix_from_source @ 0x44d330 */

0044d34b        arg1[0xc] = fconvert.s(fneg(fconvert.t(arg2[0xd]) * fconvert.t(arg2[1]) + fconvert.t(arg2[2]) * fconvert.t(arg2[0xe]) + fconvert.t(arg2[0xc]) * fconvert.t(*arg2)))
0044d366        arg1[0xd] = fconvert.s(fneg(fconvert.t(arg2[0xd]) * fconvert.t(arg2[5]) + fconvert.t(arg2[6]) * fconvert.t(arg2[0xe]) + fconvert.t(arg2[0xc]) * fconvert.t(arg2[4])))
0044d381        arg1[0xe] = fconvert.s(fneg(fconvert.t(arg2[0xd]) * fconvert.t(arg2[9]) + fconvert.t(arg2[0xc]) * fconvert.t(arg2[8]) + fconvert.t(arg2[0xe]) * fconvert.t(arg2[0xa])))
0044d386        *arg1 = *arg2
0044d38b        arg1[1] = arg2[4]
0044d391        arg1[2] = arg2[8]
0044d397        arg1[4] = arg2[1]
0044d39d        arg1[5] = arg2[5]
0044d3a3        arg1[6] = arg2[9]
0044d3a9        arg1[8] = arg2[2]
0044d3af        arg1[9] = arg2[6]
0044d3b5        arg1[0xa] = arg2[0xa]
0044d3ba        arg1[0xb] = 0
0044d3bd        arg1[7] = 0
0044d3c0        arg1[3] = 0
0044d3c3        arg1[0xf] = 0x3f800000
0044d3ca        return 0
