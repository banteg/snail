/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninitialize_bass_audio_backend @ 0x4496d0 */

004496d0        data_753bfc()
004496de        if (data_7537d8() == 0)
004496e5        report_errorf("Cannot Free BASS_Free()")
004496fb        if (FreeLibrary(data_753c90) == 0)
00449702        report_errorf("Cannot Free bass.dll library")
00449715        return sub_431540("tBass.dll")
