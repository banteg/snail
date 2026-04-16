/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: multiply_vector_by_matrix @ 0x44cb90 */

0044cb95        float edx = *arg1
0044cb9b        float edx_1 = arg1[1]
0044cba2        float result = arg1[2]
0044cbc9        *arg1 = fconvert.s(fconvert.t(result) * fconvert.t(arg8) + fconvert.t(edx_1) * fconvert.t(arg5) + fconvert.t(edx) * fconvert.t(arg2) + fconvert.t(arg11))
0044cbeb        arg1[1] = fconvert.s(fconvert.t(arg9) * fconvert.t(result) + fconvert.t(arg6) * fconvert.t(edx_1) + fconvert.t(arg3) * fconvert.t(edx) + fconvert.t(arg12))
0044cc0e        arg1[2] = fconvert.s(fconvert.t(arg10) * fconvert.t(result) + fconvert.t(arg7) * fconvert.t(edx_1) + fconvert.t(arg4) * fconvert.t(edx) + fconvert.t(arg13))
0044cc14        return result
