# play_sound_effect

Exact eight-instruction Windows `SoundEffectManager::play_sound_effect(int)` at
`0x44dde0`. It forwards the effect id to the shared backend with gain `1.0`,
default pitch `-1.0`, and centered pan `0.0`.

Native callers consistently load `g_sound_effect_manager @ 0x78ff88` into
`ecx`; iOS and Android name the same surface `cRSound::Play(int)`. Defining the
body on that owner is byte-identical at 8/8 instructions with its backend call
resolved, despite the receiver being unused inside this thin overload.

The 2026-07-17 paired replay now makes that hidden receiver explicit in Binary
Ninja and IDA, while preserving the genuine void wrapper and the exact matcher.
The adjacent scaled and warning wrappers share the same replayed owner; only
the warning play edge retains an integer result because its caller immediately
passes the returned live handle to the stop edge.

## 2026-08-12 authored source surface

Both mobile ports independently retain the exact `cRSound::Play(int)` symbol
and forwarding body. The matcher definition and all source-facing callers now
use `Play`, emitting the recovered VC6 `?Play@cRSound@@QAEXH@Z` symbol while
keeping `play_sound_effect` as the stable function ID and decompiler label. The
wrapper remains exact at 8/8 and its broad native call graph remains clean.
