# stop_registered_warning_sample @ 0x432de0

Warning-system adapter that binds the process `g_audio_backend` receiver and
forwards a live sample handle to its handle-stop method at `0x449a10`. The
explicit native `ECX = 0x753c58` load proves the callee's member ABI.

## 2026-07-16 authored owner closure

iOS and both Android ABIs preserve the public entry point as
`RShellSoundStopLooped(int)` in `RShell.o`. Each Android implementation is only
four bytes: a tail branch to `PfmAudioStopSample` with the incoming live handle.
Windows binds `g_audio_backend` and forwards the same handle contract. The exact
Windows scratch remains 5/5 with two masked operands.
