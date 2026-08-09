# reset_voice_manager @ 0x448ec0

The exact Windows member clears manager-wide voice progress and all 16 inline
set cooldowns. Android and iOS independently retain its authored identity as
`cRVoiceManager::ReSet()`.

The matcher now uses that primary spelling and binds
`?ReSet@cRVoiceManager@@QAEXXZ`, while the stable function directory remains
`reset_voice_manager`. Focused matching is exact at 8/8 instructions with no
masked operands.
