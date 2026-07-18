/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: cross_vectors @ 0x44cd40 */

0044cd43        char ecx = data_777f38
0044cd4d        if ((1 & ecx) == 0)
0044cd58        data_777f38 = ecx | 1
0044cd5e        atexit(destroy_cross_vectors_static_result)
0044cd7c        data_77ff80 = fconvert.s(fconvert.t(lhs->y) * fconvert.t(rhs->z) - fconvert.t(rhs->y) * fconvert.t(lhs->z))
0044cd8e        data_77ff84 = fconvert.s(fconvert.t(lhs->z) * fconvert.t(rhs->x) - fconvert.t(lhs->x) * fconvert.t(rhs->z))
0044cd9e        int32_t eax_1 = data_77ff80
0044cda5        data_77ff88 = fconvert.s(fconvert.t(rhs->y) * fconvert.t(lhs->x) - fconvert.t(lhs->y) * fconvert.t(rhs->x))
0044cdab        out->x = eax_1
0044cdb3        out->y = data_77ff84
0044cdbc        out->z = data_77ff88
0044cdc0        return
