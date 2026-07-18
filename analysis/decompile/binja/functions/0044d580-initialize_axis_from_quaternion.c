/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_axis_from_quaternion @ 0x44d580 */

0044d583        struct Quaternion* quaternion_1 = quaternion
0044d592        quaternion = fconvert.s(arccosine(quaternion_1->w))
0044d59b        long double st0_1 = sine(quaternion)
0044d5a3        out->x = fconvert.s(fconvert.t(quaternion_1->x) / st0_1)
0044d5a5        long double st0_2 = sine(quaternion)
0044d5ae        out->y = fconvert.s(fconvert.t(quaternion_1->y) / st0_2)
0044d5b1        long double st0_3 = sine(quaternion)
0044d5bd        out->z = fconvert.s(fconvert.t(quaternion_1->z) / st0_3)
0044d5c0        long double x87_r0_7 = fconvert.t(quaternion)
0044d5c6        out->angle = fconvert.s(x87_r0_7 + x87_r0_7)
0044d5cb        return
