# initialize_voice_manager

`VoiceManager::initialize_voice_manager` parses `Voice/_Voice.txt`, builds the
16 named `VoiceSet` buckets, registers each listed `.ogg`, applies music/SFX/
voice normalization scales, reads the global voice frequency, and then resets
the manager cooldown state.

The native function is a `void` thiscall despite decompiler return noise. The
fall-through return leaves whatever helper result is in `eax`; the only real
API behavior is field initialization plus the final `reset_voice_manager()`.

Source-shape details retained:

- The `Voice/_Voice.txt` load keeps the `get_archive_data_base()` buffer as the
  text cursor and ignores the loader return, matching the native pre-call store.
- Set tag construction uses `rstrcpy_checked_ascii(set_tag, "Set:")` followed by
  CRT `strcat`, which VC6 expands into the observed `rep movsd`/`rep movsb`
  append block.
- Case 13 reuses the existing `g_tutorial_text` data string at `0x4a38e4`;
  emitting a fresh `"Tutorial"` literal creates a real masked operand mismatch.
- The voice-set sweep is spelled as a header-increment `for` loop starting from
  the local zero value. Equivalent while/do-while spellings keep the same
  behavior, but the `for` shape moves the loop cursor closer to native and
  improves the retained match from 61.78% to 66.02%.
- The scratch avoids register-forcing tricks. The main retained differences are
  register allocation around `ebx`/`ebp` and the line cursor, plus the placement
  of the missing-set error tail.

## 2026-07-12 parser and ownership recovery

- The native frame has one function-lifetime parser cursor at `esp+0x10`. It is
  reused for set lookup, the opening brace and first voice entry, normalization
  keys, and the final frequency parse. Removing the synthetic `open_brace`
  local and retaining this cursor moves the exact prefix from 4 to 99 target
  instructions.
- The native switch covers all 16 inline `VoiceSet` owners. Each case appends
  its authored set name directly; `SuperTramp` is case 15, not a synthetic
  default. The iOS `cRVoiceManager::Init()` independently retains the same
  `0..15` jump table, names, `0x18`-byte stride, and parsing flow.
- These source-shape recoveries move the scratch from 66.02% (249 candidate
  instructions for 269 target instructions) to 88.68% (270/269), with 61 clean
  masked operands, one unresolved local jump-table relocation, and no masked
  operand mismatches.
- A probe that merged the local zero sentinel with `set_index` scored slightly
  better in isolation, but it contradicted the native lifetime: the native
  preserves a separate zero value and initializes the loop index only after the
  file load. It was rejected rather than retained as a score-only match.
- The honest residual starts in the whitespace loop: native increments the
  spilled cursor in place, while VC6 currently chooses an `inc ecx` plus store.
  The remaining tail differences are register rotation and local scheduling;
  the scratch does not force either.
- The iOS `Voice.o` family maps the Windows owner to authored
  `cRVoiceManager::{ReSet, Init, AI, Play}` and `gVoiceManager`. Its `Init`
  epilogue returns without establishing a value, independently confirming the
  recovered `void` contract.

## 2026-07-13 voice-set table proof

- The 16-entry Windows table at `0x449260` is now named
  `initialize_voice_manager_set_jump_table`. Its destination offsets relative
  to the function are `0x5a, 0x68, 0x76, 0x84, 0x92, 0x9d, 0xa8, 0xb3,
  0xbe, 0xc9, 0xd4, 0xdf, 0xea, 0xf5, 0x100, 0x10b`.
- COFF places candidate `$L816` at object `+0x380`; its 16 relocations resolve
  to exactly the same function-relative offsets. Registering that bounded
  alias converts the sole unresolved operand into a clean content-audited
  jump-table reference.
- Focused matching remains the honest 88.68% (`270/269`, prefix `99/269`), but
  the proof audit improves from 61 clean plus one unresolved operand to 62
  clean, zero unresolved, and zero mismatched operands.

## 2026-07-17 paired owner replay

- The exact global at `0x751498` is now typed and named `g_voice_manager` in
  both Binary Ninja and IDA. Its `0x188` extent is 16 inline `VoiceSet` records
  plus `global_progress` and `global_frequency_seconds`.
- All nine `cRVoiceSet`/`cRVoiceManager` method ABIs are replayed together, so
  the initializer now indexes `manager->sets`, registers through `set->bites`,
  assigns `manager->global_frequency_seconds`, and ends with the void
  `reset_voice_manager(manager)` call in both tracked decompiles.
- The focused scratch remains the honest 88.68% result above. The replay only
  recovers ownership and ABI propagation; it does not claim away the residual
  scheduling differences.
