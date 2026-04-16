/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: ascii_upper_if_lowercase @ 0x44e5a0 */

0044e5a0        int32_t result
0044e5a0        result.b = arg1
0044e5aa        if (result.b s>= 0x61 && result.b s<= 0x7a)
0044e5ac        return result - 0x20
0044e5af        return result
