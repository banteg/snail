/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_track_jetpack_pickup_runtime @ 0x4084d0 */

004084d4        initialize_bod_base(arg1)
004084de        initialize_renderable_bod(&arg1[0x1d])
004084e3        arg1[0x1d] = &data_49731c
004084f1        initialize_renderable_bod(&arg1[0x42])
004084f6        arg1[0x42] = &data_49731c
004084fc        *arg1 = &data_497318
00408506        return arg1
