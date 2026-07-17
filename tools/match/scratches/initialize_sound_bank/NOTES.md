# initialize_sound_bank @ 0x44dcb0

The exact Windows routine consumes a sentinel-terminated array of 12-byte
records. Each record owns a path pointer, the registered sample id written by
this initializer, and a normalization class. The shipped `g_sound_bank_entries`
table at `0x4a2140` has 51 live records followed by a record whose path points
at the shared empty string.

iOS symbols name the entry type `cRSoundBank` and the initializer
`cRSound::Init(cRSoundBank*)`; Android independently names its corresponding
global `gSFXBank` and uses the same 12-byte stride and field order. The shared
`SoundBankEntry` definition records that authored ownership while retaining the
repository's descriptive naming convention. `sample_id` is intentionally not
called a handle: `register_sound_sample` returns the registered table index,
which the cross-port `cRSound::Play` methods later read from `+0x04`.

Windows startup pushes `g_sound_bank_entries`, loads
`g_sound_effect_manager @ 0x78ff88` into `ecx`, and calls this helper. That
receiver setup proves the Windows ABI is also a `SoundEffectManager` member,
even though its body needs no receiver fields. Android additionally stores the
bank address in `gRSound` before walking it. Promoting the body and startup call
to the shared owner leaves this function exact at 21/21 instructions.

## 2026-07-14 live entries versus sentinel storage

The global declaration now distinguishes `SOUND_BANK_LIVE_ENTRY_COUNT` (51
registered samples) from `SOUND_BANK_ENTRY_COUNT` (those records plus the
terminating entry). Binary Ninja confirms the final 12-byte record begins at
`0x4a23a4`; its path pointer targets the shared empty string and its remaining
words are zero. The exact initializer deliberately remains sentinel-driven,
so the derived storage capacity documents ownership without manufacturing a
counted-loop contract that native does not have.

## 2026-07-17 void ABI and paired owner replay

- Windows leaves the sentinel path in EAX, while Android's retained
  `cRSound::Init(cRSoundBank*)` leaves a record offset after also binding the
  bank pointer into `gRSound`. Both startup callers discard the register, so
  the authored contract is `void`; treating either residue as a return value
  would be platform-specific fakematching.
- Removing the synthetic pointer return keeps the Windows scratch exact at
  `21/21` instructions with its single audited operand clean.
- Binary Ninja and IDA now replay the one-byte Windows
  `g_sound_effect_manager`, the `0x0c`-byte `SoundBankEntry`, all six manager
  method ABIs, and `g_sound_bank_entries[52]`. Readback proves the complete
  `0x270` data extent in both databases; the IDA replay explicitly repairs and
  guards against a stale four-byte item head.
