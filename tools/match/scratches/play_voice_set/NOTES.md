# play_voice_set @ 0x449390

Android retains this exact owner and method contract as
`bool cRVoiceSet::Play(int)`: both ports gate on the per-set cooldown, accept a
sample override or select the next shuffled playlist entry, advance and wrap
the cursor, and return whether playback started.

The payload storage is platform-specific. Windows `bites` is an array of
registered sample IDs, while Android indexes 0x8c-byte `VoiceBite` records.
Only the owner and control-flow transfer across ports; no mobile stride or
offset is transplanted into the Windows 0x18-byte `VoiceSet`.

Focused Windows matching remains exact at 43/43 instructions with three clean
masked operands.
