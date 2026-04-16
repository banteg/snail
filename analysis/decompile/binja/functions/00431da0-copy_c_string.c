/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: copy_c_string @ 0x431da0 */

00431da0        char* result = arg2
00431da4        char* ecx = arg1
00431db2        char i
00431daa        *ecx = *result
00431dac        i = *result
00431dae        ecx = &ecx[1]
00431daf        result = &result[1]
00431db2        do while (i != 0)
00431db4        return result
