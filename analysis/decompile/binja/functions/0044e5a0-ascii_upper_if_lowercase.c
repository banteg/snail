/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: ascii_upper_if_lowercase @ 0x44e5a0 */

0044e5a0        int32_t eax
0044e5a0        eax.b = value
0044e5aa        if (eax.b s>= 0x61 && eax.b s<= 0x7a)
0044e5ac        eax -= 0x20
0044e5af        return eax.b
