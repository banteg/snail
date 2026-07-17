# shuffle_voice_set @ 0x448e60

Performs 100 in-place swaps over the `VoiceSet` playlist. The recovered
`0x18`-byte owner exposes `sample_count` and `playlist` directly in both Binary
Ninja and IDA.

## 2026-07-17 void ABI and owner replay

- Windows naturally leaves the second random index in EAX, while Android's
  retained `cRVoiceSet::Shuffle()` leaves different incidental register
  residue. Its only caller, `cRVoiceSet::Init(int)`, discards the result on both
  platforms, proving that the authored member is `void`.
- The matcher therefore removes the synthetic integer return without
  register-forcing or dead expressions. The focused result remains exact at
  `34/34` instructions with all six audited operands clean.
- The paired replay keeps the shuffle on `VoiceSet*`, so playlist indexing no
  longer degrades into anonymous dword arithmetic in either tracked decompile.
