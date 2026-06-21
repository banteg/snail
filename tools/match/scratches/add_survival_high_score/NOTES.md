# add_survival_high_score

`add_survival_high_score` @ 0x417780 records a completed Challenge/Survival
result into the ordered top-ten bank and prepares the high-score entry frontend.

Behavior:

- Tags the incoming record as survival (`high_score_mode_tag = 1`), clears its
  route/rank and replay cursor fields, then copies the full 0x1fac0 record into
  both `current_result_record` and `survival_pending_record`.
- Scans `survival_records[0..9]` by descending `score`. If the run does not
  place, returns the rank cursor (`10`).
- If it places, shifts lower records into the spare eleventh storage slot,
  writes the new record at the selected rank, points the frontend
  `active_record_bank` at `survival_records`, and marks the pending entry as
  bank 1.

The extra `rank != -1` gate is source-shaped from native even though this local
rank search only produces non-negative ranks.

Match status: 93.49%, 84/84 target instructions, 36/84 exact prefix, six masked
operands resolved.

Residual:

- Native keeps the bank owner in `ebp`, spills it before the rank scan, saves
  `ebx` in the prologue, scans scores through the `score` field address, and
  keeps a redundant guarded insertion block after the no-place return. The
  current scratch mirrors that shape.
- The high-score frontend arm is semantically aligned, including the native
  `rank != -1` gate, but one impossible-path global reload and a small
  post-shift reload scheduling difference remain.
- 2026-06-20 high-score insertion pass: the arcade helper improved when its
  down-shift loop was spelled as a pre-tested `while`, but applying the same
  source shape here regressed survival to 55.95%. MSVC then kept constant `1`
  in `ebp` and left the bank in `ebx`, moving further away from native, so the
  survival scratch keeps the existing `do while` shift loop.
- 2026-06-20 follow-up pass: mirroring arcade's bounded rank scan did improve
  survival when the score comparison exits through `goto insert_record` and the
  no-place path falls through to `return rank`. This raised the match from
  66.67% to 82.14% and restored native-style bank ownership in `ebp`.
- Keeping the original in-loop no-place return while changing only `break` to a
  label was neutral at 66.67%, so the bounded scan and out-of-loop return are
  the important parts of the accepted shape.
- Rewriting the score scan as an `int*` cursor or adding an explicit shift guard
  alone regressed or stayed neutral in older shapes, but the two combined with
  the bounded `goto insert_record` scan match native prologue ownership and the
  redundant post-scan compare, raising the scratch from 82.14% to 93.49%.
  Switching the shift loop to `while`, forcing a shared `shift_rank` limit in
  the older cursor shape, and reshaping the impossible `rank == -1` return path
  all regressed. A late active-bank local and an explicit saved-bank alias were
  codegen-neutral.
- 2026-06-20 larger high-score audit: combining the `int*` score cursor with a
  raw late active-bank pointer regressed to 65.03% by changing the prologue and
  moving bank ownership into `ebx`. A narrower raw late active-bank local stayed
  codegen-neutral at 82.14%, so the retained typed `bank->survival_records`
  spelling remains the best source shape.
- 2026-06-20 guard/cursor pass: `goto` + `int*` score cursor + redundant
  `rank >= shift_rank` guard is the accepted source shape. Break-plus-guard
  variants reached only 88.34% or worse, and result-view/impossible-return tail
  locals regressed by changing argument setup and callee-save ownership.
- 2026-06-21 post-shift owner reload: a narrow volatile reload of the saved
  `bank` local before writing `survival_records[rank]` moves the post-shift
  owner restore ahead of the rank-slot address arithmetic like native, raising
  the focused match from 93.49% to 94.67% with six clean masks. Plain
  `bank = this`, normal `insert_bank`/slot/source locals, and address/reference
  aliases all compile back to the previous schedule; volatile source-record
  reloads regress the prologue.
- 2026-06-21 guarded-return tail probe: moving the final return into the
  `rank != -1` frontend block looked like it could reuse native's last
  `g_game_base` load and remove the scratch's impossible-path reload. VC6
  instead duplicates the guarded control flow, grows the candidate to 91/92
  instructions, and drops focused Wibo to roughly 82%. Keep the current
  impossible-path reload; the reachable frontend body remains the better
  source-shaped tradeoff.
