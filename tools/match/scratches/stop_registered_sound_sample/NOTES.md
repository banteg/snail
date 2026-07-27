# cRBass::StopSample @ 0x449a20

The native voice-manager caller loads `ECX = 0x753c58` immediately before the
call, proving the `AudioBackend` member ABI. Its BASS return value is discarded;
the recovered public method therefore keeps the shared `void` declaration while
preserving the native tail call result in `EAX` incidentally.

## 2026-07-27 mobile owner recovery

iOS `BassPlay.o` names this sample-id method `cRBass::StopSample(int)`.
`cRVoiceManager::Play()` loads a registered id from a VoiceSet bite bank into
`r1`, loads `gBass` into `r0`, and calls it. Windows takes the same voice-bank
id and resolves it through `g_registered_sound_sample_handles` before calling
BASS. Both iOS versions retain a four-byte `bx lr` stub, so only authored
ownership and the sample-id ABI transfer across the platform boundary.
