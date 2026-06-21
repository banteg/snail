# display_score_stats @ 0x4403c0

`display_score_stats` reports the six run score buckets on the score block
view at `game+0x3bb764` before `complete_subgame` snapshots the final result.
The bucket offsets mirror the producer fields used by `add_subgoldy_score`,
but the callsites pass the run score block, not the `Player`; keep this on
the shared `RunScoreStats` pointer view.

The six bucket indexes are shared through `score_stats.h`:
garbage, slug, ring/special-effect, parcel collect, parcel deliver, and bonus.

The function is source-shaped:

- return `0` immediately when the total score bucket at `+0x2e4` is zero
- print the total score header through the stripped release `debug_report_stub`
- print each score bucket as `(bucket * 100) / total`
- finish with the shared newline string at `data_4a44cc`

`data_4a44cc` is the literal `"\n"` in the executable data section, also used
by the warning/error report helpers, so the scratch keeps the real literal
instead of inventing a placeholder global.

Match status: proof-grade.

2026-06-16 type split: a probe promoted this as `Player::display_score_stats`
because the score offsets match the player producer window. BN xrefs and
callsite decompilation corrected that assumption: `complete_subgame` calls
`display_score_stats(&game[0x3bb764])`, while `add_subgoldy_score` is the
player-facing producer. The scratch now includes `score_stats.h` and keeps the
same 90.28% match.

Residual:

- Native coalesces the cdecl cleanup for all eight report calls into one
  `add esp, 0x3c` at the end of the non-zero path. The standard
  `msvc6.5 /O2 /G5 /W3` source shape emits `add esp, 0x8` after each formatted
  call and `add esp, 0x4` after the final newline call.
- Because of that cleanup split, the compiler also duplicates the zero-return
  epilogue instead of sharing the native `pop esi; ret` tail. The value in
  `eax` is still the tested zero score.

2026-06-21 report-prototype pass: the stripped report helper compiles closer
when viewed as a fixed two-argument cdecl function for the seven formatted
integer reports. Casting the final newline call back to a one-argument cdecl
view preserves the real single-argument call while letting VC6 coalesce the
non-zero path cleanup into the native `add esp, 0x3c`. Focused Wibo improves
from 90.28% (77/67 candidate/target instructions) to 96.35% (70/67), with all
16 masks still clean. A default-argument prototype left an extra zero push for
the newline and only reached 94.20%; explicit shared-result returns changed
register ownership and regressed to 70.00%; omitting the zero-path return hit
the current Wibo missing-`lstrcpynA` path. The remaining residual is only the
extra explicit zero-return epilogue.

2026-06-21 zero-guard pass: rewriting the zero-score case as an early
`return total_score` removes the extra `xor eax, eax` zero epilogue and
improves focused Wibo from 96.35% to 97.06% (69/67 candidate/target
instructions, 16 clean masks). The native still uses a forward zero branch to
the shared tail, so the first mismatch remains the conditional branch direction;
the retained early guard is the best tested source shape for suppressing the
spurious zero materialization. A `score` local, an `else` return, and a `goto`
spelling are either codegen-neutral with the old epilogue or compile to the
same early-zero shape.

2026-06-21 guarded-result pass: keeping `result = total_score`, guarding the
report body with `if (total_score != 0)`, and assigning the final newline report
result into that local matches native exactly. This recovers the forward
zero-score branch to the shared epilogue, preserves the batched `add esp, 0x3c`
cleanup for the stripped report calls, and keeps zero-score returns as the
already-loaded total score. Focused Wibo is now 100.00%, 67/67 instructions,
full prefix, and 16 clean masked operands.
