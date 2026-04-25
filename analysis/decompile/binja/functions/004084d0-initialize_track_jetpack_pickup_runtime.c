/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_track_jetpack_pickup_runtime @ 0x4084d0 */

004084d4        initialize_bod_base(slot)
004084de        initialize_renderable_bod(&slot[1])
004084e3        slot->__offset(0x74).d = &data_49731c
004084f1        initialize_renderable_bod(&slot->_pad_00[0x108])
004084f6        slot->__offset(0x108).d = &data_49731c
004084fc        slot->_pad_00[0] = 0x18
004084fc        slot->_pad_00[1] = 0x73
004084fc        slot->_pad_00[2] = 0x49
004084fc        slot->_pad_00[3] = 0
00408506        return slot
