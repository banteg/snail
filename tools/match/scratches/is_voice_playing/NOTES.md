# is_voice_playing @ 0x449410

Android exports the authored owner and name
`cRVoiceManager::IsPlaying()`, but its platform body is an eight-byte stub
returning `-1`. Windows retains the richer implementation: it walks all 16
inline `VoiceSet` records, queries each registered sample, and returns the
first active sample ID or `-1`.

This is owner and contract evidence only, not body equivalence. Focused
Windows matching remains exact at 40/40 instructions with two clean masked
operands.

## 2026-08-09 authored source promotion

The matcher source now uses `cRVoiceManager::IsPlaying()` and binds
`?IsPlaying@cRVoiceManager@@QAEHXZ`. Android's stub proves the authored name
and integer contract without replacing the richer Windows body. The stable
function directory remains `is_voice_playing`; focused matching stays exact at
40/40 instructions with two clean operands.
