/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: archive_or_file_exists @ 0x430fd0 */

00430fd8        int32_t eax
00430fd8        if (data_53c7f8 != 0)
00430fda        eax.b = arg2
00430fe0        if (data_53c7f8 == 0 || eax.b != 0)
0043100f        int32_t* eax_4 = sub_48b41d(arg1, "rb")
00431019        if (eax_4 == 0)
0043101b        eax_4.b = 0
0043101e        return eax_4
00431020        sub_48b3a7(eax_4)
00430ff1        if (find_archive_entry(arg1) == 0)
00430ff9        report_warningf("Missing Dat File %s", arg1)
00431001        int32_t eax_2
00431001        eax_2.b = 0
00431004        return 0
00431028        int32_t eax_1
00431028        eax_1.b = 1
0043102b        return eax_1
