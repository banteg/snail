# mini_delete_high_score_entry

Deletes a canceled pending top-ten entry by shifting later records over its
row. The iOS symbol corpus independently names this owner method
`cRSubHighScore::MiniDelete(int)`.

This is a `SubHighScore` member. The bank is owned by `SubgameRuntime` at
`game+0x74618+0x68b4c8 = game+0x6ffae0`; its first two fields are the borrowed
active-bank pointer and row count. Native uses the overlapping source window at
bank `+0x17c108`, exactly `survival_records[1]`. The
`mini_delete_source_records` member documents that alias without inventing a
second owner.

Match status: 84.85% (33/33 instructions, 15/33 exact prefix).

2026-07-11 ownership verification:

- The narrow Binary Ninja sync renamed `0x417af0`, applied
  `void __thiscall(SubHighScore*, int)`, and re-decompiled the fixed source as
  `&bank->survival_records[1]`; the only code xref is the Cancel path at
  `update_high_score_screen+0x11d`.
- The checked-in BN export and cross-port `HighScore.o` symbol now agree on the
  `cRSubHighScore` receiver. The old commit-style name and duplicate
  `HighScoreRecordView` have been retired.

2026-06-20 high-score delete pass:

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
- A second explicit `source = source_cursor; source_cursor += stride` probe in
  the larger high-score audit reproduced that tradeoff: it recovers the native
  `+0x17c108` source displacement and raises the exact prefix to 16, but drops
  focused Wibo to 81.82% because VC6 emits the `rep movsd` before both cursor
  increments. Keep the retained byte post-increment shape.
- 2026-06-21 cursor-lifetime retry: source-old/cursor-next variants that
  increment both the byte source cursor and the byte offset before the copy still
  score only 81.82%. They recover the native `+0x17c108` displacement but keep
  destination ownership as `mov edi, [edx]` instead of native `mov edi, eax; add
  edi, [edx]`. Rank writes through the destination pointer, row-indexed typed
  records, and reordered source/destination declarations regress much further.
  The retained post-increment/subtract source remains the best available copy
  schedule.
