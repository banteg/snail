/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: cross_vectors @ 0x44cd40 */

0044cd41        struct Vec3* out_1 = out
0044cd43        out.b = data_777f38
0044cd4d        if ((1 & out.b) == 0)
0044cd58        data_777f38 = out.b | 1
0044cd5e        sub_48c7ba(sub_44cdd0)
0044cd7c        data_77ff80 = fconvert.s(fconvert.t(lhs->y) * fconvert.t(rhs->z) - fconvert.t(rhs->y) * fconvert.t(lhs->z))
0044cd8e        data_77ff84 = fconvert.s(fconvert.t(lhs->z) * fconvert.t(rhs->x) - fconvert.t(lhs->x) * fconvert.t(rhs->z))
0044cd9e        int32_t result = data_77ff80
0044cda5        data_77ff88 = fconvert.s(fconvert.t(rhs->y) * fconvert.t(lhs->x) - fconvert.t(lhs->y) * fconvert.t(rhs->x))
0044cdab        out_1->x = result
0044cdb3        out_1->y = data_77ff84
0044cdbc        out_1->z = data_77ff88
0044cdc0        return result
