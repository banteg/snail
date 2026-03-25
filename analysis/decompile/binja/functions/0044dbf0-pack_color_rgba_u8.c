/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: pack_color_rgba_u8 @ 0x44dbf0 */

0044dc00        char eax
0044dc00        int16_t x87control
0044dc00        int16_t x87control_1
0044dc00        eax, x87control_1 = __ftol(x87control, fconvert.t(*arg2) * fconvert.t(255f))
0044dc05        arg1[2] = eax
0044dc11        char eax_1
0044dc11        int16_t x87control_2
0044dc11        eax_1, x87control_2 = __ftol(x87control_1, fconvert.t(arg2[1]) * fconvert.t(255f))
0044dc16        arg1[1] = eax_1
0044dc22        char eax_2
0044dc22        int16_t x87control_3
0044dc22        eax_2, x87control_3 = __ftol(x87control_2, fconvert.t(arg2[2]) * fconvert.t(255f))
0044dc27        *arg1 = eax_2
0044dc37        arg1[3] = __ftol(x87control_3, fconvert.t(arg2[3]) * fconvert.t(255f))
0044dc3e        return arg1
