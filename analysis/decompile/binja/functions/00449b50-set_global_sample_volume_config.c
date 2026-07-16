/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_global_sample_volume_config @ 0x449b50 */

00449b68        int16_t x87control
00449b68        return data_753c1c(4, ftol(x87control, fconvert.t(volume) * fconvert.t(100f)))
