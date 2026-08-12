# update_twinkle_manager @ 0x404030

Stable scratch identity for the authored `void cRTwinkleManager::AI()` member.
Its sole Windows caller loads `ECX = cRBorder + 0x80`, proving the embedded
manager receiver. When `active_state - 1 == 0`, it advances `twinkle_count`
inline 0x30-byte `cRTwinkle` records through their `AI()` member.

Android preserves `cRTwinkleManager::AI()` and the same state/count-gated
walk. The Windows source selects `?AI@cRTwinkleManager@@QAEXXZ` and matches
exactly at 23/23 instructions with its masked operand clean. The broader
`cRBorder` caller retains its 95.83% baseline, 649/647 instruction shape,
96 clean operands, and two honestly unaudited constants.
