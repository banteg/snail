# commit_high_score_entry_into_top_ten

Commits the edited high-score display rows into the active persistent top-ten
bank after name entry.

This helper is a member of the front-end record view at `game+0x6ffae0`, not a
free function taking a raw `HighScoreRecord*`. The first two fields are the
active persistent bank pointer and row count; the native copy source begins at
view offset `+0x17c108`.

Match status: 84.85% (33/33 instructions, 15/33 exact prefix).

2026-06-20 high-score commit pass:

- Rewriting the source row cursor as a byte post-increment improves focused Wibo
  from 81.82% to 84.85%. MSVC now schedules the source cursor increment before
  the `rep movsd`, closer to native's `add ebx, 0x1fac0` before the copy.
- The remaining residual is address folding/register ownership: native keeps
  the source base as `this + offset + 0x17c108` and increments `ebx` after
  copying it to `esi`, while the candidate folds the same address as
  `this + offset + 0x15c648` plus an early `add ebx, 0x1fac0`.
- Rejected probes: a destination cursor rewrite regressed to 35.29% by changing
  the prologue and loop ownership; a decompiler-style `(int)active_record_bank`
  expression was codegen-neutral at 81.82%; and a typed `source + 1`
  post-increment collapsed back to the old 81.82% schedule.

2026-06-20 larger high-score audit:

- Focused matcher still verifies the retained byte post-increment source at
  84.85%, 33/33 instructions, 15/33 prefix, and no masked operands.
- Spelling the copied source directly as `source_cursor` recovers the native
  `+0x17c108` source-base displacement, but regresses to 81.82% because VC6
  moves the source increment after `rep movsd` and changes destination register
  ownership (`mov edi, [edx]; add edi, eax` instead of native `mov edi, eax;
  add edi, [edx]`).
- Adding an explicit `next_source_cursor` local and writing destination as
  `offset + (char*)active_record_bank` are codegen-neutral on top of that
  regressed shape. Keep the current `source_cursor += stride; source =
  source_cursor - stride` spelling; it is less pretty but better matches the
  native memcpy schedule.
