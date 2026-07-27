# cRBass::PlaySampleLooped @ 0x449a60

The exact Windows body resolves one registered sample id through the shared
handle bank and calls `BASS_SamplePlayEx` with looping enabled. Its only caller
is the exact `RShellSoundPlayLooped(int)` adapter at `0x432dd0`, and its return
value is the live handle later consumed by StopSampleLooped.

## 2026-07-27 mobile owner recovery

iOS `BassPlay.o` names this method `cRBass::PlaySampleLooped(int)`. Its
`RShellSoundPlayLooped` wrapper moves the registered id into `r1`, loads the
global `gBass` receiver into `r0`, and calls the method. Both iOS versions
compile the body to `mov r0, 0; bx lr`, disabling loop playback on that backend
while preserving the authored owner and one-id ABI.
