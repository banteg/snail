/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: convert_math_type32_to_16 @ 0x44c890 */

0044c89e        int16_t x87control
0044c89e        return __ftol(x87control, fconvert.t(65536f) / fconvert.t(arg2) * fconvert.t(arg1)) __tailcall
