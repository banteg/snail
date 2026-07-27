# cRBass::PlaySample @ 0x4499a0

All three native callers load `ECX = 0x753c58` immediately before the call,
proving that this exact helper is an `AudioBackend` method on
`g_audio_backend`, not a standalone stdcall function. The receiver is unused;
the method resolves a sample id through the registered-handle table and applies
the normalized volume to the BASS backend.

## 2026-07-27 mobile owner recovery

iOS `BassPlay.o` names this exact owner and ABI
`cRBass::PlaySample(int, float)` and names the process global `gBass`.
`cRInvincible::AI()` loads that receiver, passes a registered sample id plus
`1.0f`, and calls the method. Both retained iOS versions compile the method to
a four-byte `bx lr` because their public sound path uses `MacAudioPlaySample`;
that platform stub transfers ownership and signature, not Windows BASS
behavior. The Windows scratch remains the behavioral source and exact match.
