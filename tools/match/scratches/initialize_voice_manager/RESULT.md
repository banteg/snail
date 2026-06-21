# `initialize_voice_manager` match result

## Score

| Metric | Final |
|---|---:|
| Match | **66.02%** |
| Target instructions | 269 |
| Candidate instructions | 249 |
| Common prefix | 4 / 269 |
| Masked operands | 58 clean, 0 unresolved, 0 mismatched |

The first remaining mismatch is early register allocation:

```text
target[4]    xor ebx, ebx
candidate[4] push edi
```

The native keeps `ebx` as an early zero register, uses `ebp` as the set index,
and spills the voice-file cursor to the stack. The candidate keeps the archive
base in `ebp`, uses `ebx` for the set index, and keeps the current voice-file
line cursor in `esi`.

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

## Rejected Trials

- Initializing `set_tag` with `""` caused VC6 to zero the whole stack buffer and
  dropped the prefix to one instruction.
- Assigning the loader return to `file_text` produced the wrong call ordering
  around `get_archive_data_base()` and a lower 54.93% match.
- `register` hints for the zero and set-index locals did not change codegen, so
  they were removed.
- Adding an explicit `case 15` or initializing the case-15 name through a
  default-local path was neutral or regressed masked operand cleanliness.
