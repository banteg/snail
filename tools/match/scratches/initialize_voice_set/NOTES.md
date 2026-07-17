# initialize_voice_set @ 0x448df0

Initializes the VoiceSet-owned playlist and bite-index arrays. Both tracked
allocations now derive their four-byte stride from the destination `int`
members rather than shift literals. Matching remains exact at 33/33
instructions with all five operands clean.

## 2026-07-17 void ABI and owner replay

- Windows has one caller, `initialize_voice_manager`, which discards EAX after
  the call. Android's retained `cRVoiceSet::Init(int)` leaves unrelated pointer
  residue instead, and its caller also discards the register. There is no
  stable cross-platform return value, so the matcher now carries the evidenced
  `void` contract instead of interpreting residue as an integer result.
- `VoiceSet` is replayed into Binary Ninja and IDA as one exact `0x18`-byte
  owner: sample count, playlist cursor, playlist and sample arrays, cooldown,
  and cooldown step. Both decompilers now show the final shuffle as a statement
  followed by a void return.
- The focused Windows match remains exact at `33/33` instructions with all five
  audited operands clean; this is ABI closure with no byte-shape concession.
