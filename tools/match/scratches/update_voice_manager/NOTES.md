# update_voice_manager @ 0x4492a0

The exact Windows member advances all 16 inline voice-set cooldowns and the
manager-wide frequency timer. Android and iOS preserve the authored owner and
name as `cRVoiceManager::AI()`; the mobile layouts and backend work remain
platform-specific.

The matcher now binds `?AI@cRVoiceManager@@QAEXXZ` while retaining the stable
`update_voice_manager` function directory. Its calls use the primary
`cRVoiceSet::AI()` spelling. Focused matching remains exact at 18/18
instructions with two audited operands.
