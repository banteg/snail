/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_salt_hazard_runtime @ 0x408630 */

00408633        initialize_renderable_bod(salt)
00408638        salt->body.bod.bod.vtable = &data_497340
00408641        return salt
