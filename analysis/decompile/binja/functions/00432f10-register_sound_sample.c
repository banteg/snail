/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: register_sound_sample @ 0x432f10 */

00432f18        char* esi
00432f18        if (data_53c7f8 == 0)
00432f60        esi = arg1
00432f6c        load_registered_sound_sample_from_path(esi, data_5108b0, arg2)
00432f20        esi = arg1
00432f2b        load_file_bytes_from_archive_or_fs(esi, data_53c7e8, &arg1)
00432f4f        load_registered_sound_sample_from_bytes(data_53c7e8, arg1, data_5108b0, arg2)
00432f82        rstrcpy_checked_ascii((data_5108b0 << 7) + &data_5088b0, esi)
00432f8f        int32_t eax_3 = data_5108b0 + 1
00432f95        data_5108b0 = eax_3
00432f9b        if (eax_3 == 0x100)
00432fa2        data_5108b0 = 0xff
00432fac        report_errorf("Run out of Sound slots increase RSHELL_SOUND_MAX in RShell.h")
00432fb1        eax_3 = data_5108b0
00432fba        return eax_3 - 1
