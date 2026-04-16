/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_smtracks @ 0x441f60 */

00441f66        advance_frame_sequence(arg1 + 0x38)
00441f79        *(*(*(arg1 + 0x24) + 0x5c) + 0xc) = *(arg1 + 0x124)
00441f97        return sample_smtrack_heightmap(*(arg1 + 0x24), 0f, 5f, *(arg1 + 0x124), 0)
