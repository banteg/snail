# cRBass::StopSampleLooped @ 0x449a10

The exact Windows body forwards one live sample handle directly to
`BASS_SampleStop`. Its only caller is the exact
`RShellSoundStopLooped(int)` adapter at `0x432de0`, which binds
`g_audio_backend` in `ECX` and passes the incoming handle unchanged.

## 2026-07-27 mobile owner recovery

iOS `BassPlay.o` names this method `cRBass::StopSampleLooped(int)`. Its
`RShellSoundStopLooped` wrapper moves the incoming live handle into `r1`,
loads the global `gBass` receiver into `r0`, and calls the method. Both iOS
versions retain a four-byte `bx lr` platform stub, but the wrapper edge proves
the authored owner and raw-handle ABI. This is intentionally distinct from
`cRBass::StopSample(int)`, whose argument is a registered sample id.
