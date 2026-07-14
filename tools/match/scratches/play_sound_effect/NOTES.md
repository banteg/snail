# play_sound_effect

Exact eight-instruction Windows `SoundEffectManager::play_sound_effect(int)` at
`0x44dde0`. It forwards the effect id to the shared backend with gain `1.0`,
default pitch `-1.0`, and centered pan `0.0`.

Native callers consistently load `g_sound_effect_manager @ 0x78ff88` into
`ecx`; iOS and Android name the same surface `cRSound::Play(int)`. Defining the
body on that owner is byte-identical at 8/8 instructions with its backend call
resolved, despite the receiver being unused inside this thin overload.
