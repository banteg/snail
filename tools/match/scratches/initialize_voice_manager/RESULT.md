# `initialize_voice_manager` match result

## Score

| Metric | Final |
|---|---:|
| Match | **100.00%** |
| Target instructions | 269 |
| Candidate instructions | 269 |
| Common prefix | 269 / 269 |
| Masked operands | 62 clean, 0 unresolved, 0 mismatched |

The candidate is instruction-for-instruction exact. All calls, data
references, strings, and the 16-entry set-name jump table audit cleanly.

## Accepted Source Shape

- Recovered all 16 voice set names and the `Set:` tag lookup loop.
- Counts lines between `{` and `}`, initializes each `VoiceSet`, and registers
  each listed file as `Voice/<name>.ogg` with normalization class `1`.
- Parses `NormalizeMusic:`, `NormalizeSfx:`, `NormalizeVoice:`, and
  `Frequency:`, then calls `g_audio_backend.set_audio_normalization_scales()`
  and stores `global_frequency_seconds`.
- Uses the real `g_tutorial_text` data symbol for the Tutorial set name.
- Uses a header-increment `for` loop for the 16-set sweep. Other loop-bound
  spellings compile equivalently after the improvement, while the original
  do-while spelling leaves the lower 61.78% shape.
- Uses a header-increment `for` loop for the per-entry whitespace skip. The
  Android and iOS `cRVoiceManager::Init()` bodies independently preserve this
  parser stage and a single mutable cursor. This source shape emits the native
  in-place cursor increment and removes the final scheduling residual.
- Recovers one function-lifetime parser cursor and all 16 explicit voice-set
  switch cases, moving the exact prefix from 4 to 99 instructions.
- Content-audits target table `0x449260` against candidate `$L816`; all 16
  function-relative destinations match exactly.

## Rejected Trials

- Initializing `set_tag` with `""` caused VC6 to zero the whole stack buffer and
  dropped the prefix to one instruction.
- Assigning the loader return to `file_text` produced the wrong call ordering
  around `get_archive_data_base()` and a lower 54.93% match.
- `register` hints for the zero and set-index locals did not change codegen, so
  they were removed.
- Adding an explicit `case 15` or initializing the case-15 name through a
  default-local path was neutral or regressed masked operand cleanliness.
