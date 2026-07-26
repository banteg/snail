# is_voice_playing @ 0x449410

Android exports the authored owner and name
`cRVoiceManager::IsPlaying()`, but its platform body is an eight-byte stub
returning `-1`. Windows retains the richer implementation: it walks all 16
inline `VoiceSet` records, queries each registered sample, and returns the
first active sample ID or `-1`.

This is owner and contract evidence only, not body equivalence. Focused
Windows matching remains exact at 40/40 instructions with two clean masked
operands.
