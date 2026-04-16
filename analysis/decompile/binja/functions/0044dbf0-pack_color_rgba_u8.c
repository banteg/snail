/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: pack_color_rgba_u8 @ 0x44dbf0 */

0044dc00        uint8_t eax
0044dc00        int16_t x87control
0044dc00        int16_t x87control_1
0044dc00        eax, x87control_1 = __ftol(x87control, fconvert.t(color->r) * fconvert.t(255f))
0044dc05        out->r = eax
0044dc11        uint8_t eax_1
0044dc11        int16_t x87control_2
0044dc11        eax_1, x87control_2 = __ftol(x87control_1, fconvert.t(color->g) * fconvert.t(255f))
0044dc16        out->g = eax_1
0044dc22        char eax_2
0044dc22        int16_t x87control_3
0044dc22        eax_2, x87control_3 = __ftol(x87control_2, fconvert.t(color->b) * fconvert.t(255f))
0044dc27        out->b = eax_2
0044dc37        out->a = __ftol(x87control_3, fconvert.t(color->a) * fconvert.t(255f))
0044dc3e        return out
