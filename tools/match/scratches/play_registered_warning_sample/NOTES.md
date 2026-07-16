# play_registered_warning_sample @ 0x432dd0

Warning-system adapter that binds the process `g_audio_backend` receiver and
forwards a registered sample id to its default playback method at `0x449a60`.
The explicit native `ECX = 0x753c58` load proves the callee's member ABI.

## 2026-07-16 authored owner closure

iOS preserves the public entry point as `RShellSoundPlayLooped(int)` in
`RShell.o`. The Windows backend call uses `BASS_SamplePlayEx` with its loop flag
set and returns the resulting live playback handle, which the Warning owner
stores for the matching stop call. That semantic and ABI evidence distinguishes
this adapter from the neighboring one-shot sound wrapper. The exact Windows
scratch remains 5/5 with two masked operands.
