/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_perspective_projection_matrix @ 0x450314 */

0045033b        long double st0
0045033b        long double st1
0045033b        bool c1
0045033b        bool c2
0045033b        st1, st0, c1, c2 = __fsincos(fconvert.t(fconvert.s(fconvert.t(arg2) * fconvert.t(0.5f))))
0045033d        arg2 = fconvert.s(st0)
0045033f        float var_8 = fconvert.s(st1)
00450347        long double x87_r7_5 = fconvert.t(arg2) / fconvert.t(var_8)
0045034a        arg1[0xb] = 0xbf800000
00450356        *arg1 = fconvert.s(x87_r7_5 / fconvert.t(arg3))
0045035a        arg1[1] = fconvert.s(float.t(0))
0045035f        arg1[2] = fconvert.s(float.t(0))
00450364        arg1[3] = fconvert.s(float.t(0))
00450369        arg1[4] = fconvert.s(float.t(0))
0045036c        arg1[5] = fconvert.s(x87_r7_5)
00450371        arg1[6] = fconvert.s(float.t(0))
00450376        arg1[7] = fconvert.s(float.t(0))
0045037b        arg1[8] = fconvert.s(float.t(0))
00450380        arg1[9] = fconvert.s(float.t(0))
00450389        long double x87_r7_12 = fconvert.t(arg5) / (fconvert.t(arg4) - fconvert.t(arg5))
0045038c        arg1[0xa] = fconvert.s(x87_r7_12)
00450391        arg1[0xc] = fconvert.s(float.t(0))
00450396        arg1[0xd] = fconvert.s(float.t(0))
0045039c        arg1[0xe] = fconvert.s(x87_r7_12 * fconvert.t(arg4))
004503a1        arg1[0xf] = fconvert.s(float.t(0))
004503a5        return arg1
