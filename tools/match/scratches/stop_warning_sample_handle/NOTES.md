# stop_warning_sample_handle

Exact five-instruction `SoundEffectManager` method at `0x44de30`. Exact
`cRWarning::StopSample()` passes the handle returned by the adjacent warning
play wrapper, reloads `g_sound_effect_manager @ 0x78ff88` into `ecx`, and calls
this stop edge.

The body forwards to the registered-sample backend and does not dereference
the receiver, but the callsite establishes its ownership. The member spelling
remains exact at 5/5 instructions with the backend call resolved.

## 2026-08-12 authored method recovery

Android and iOS retain this exact source method as
`cRSound::StopLooped(int)`; iOS places it in `RSound.o`. Both bodies forward
the incoming live playback handle to `RShellSoundStopLooped(int)`, preserving
the Windows contract and the direct pairing with `PlayLooped`. The
source-facing scratch now emits the recovered VC6
`?StopLooped@cRSound@@QAEXH@Z` symbol; the stable matcher ID is retained.
