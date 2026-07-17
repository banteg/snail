# add_survival_high_score

`add_survival_high_score` @ 0x417780 records a completed Challenge/Survival
result into the ordered top-ten bank and prepares the high-score entry frontend.

Behavior:

- Tags the incoming record as survival (`high_score_mode_tag = 1`), clears its
  route/rank and replay cursor fields, then copies the full 0x1fac0 record into
  both `current_result_record` and `survival_pending_record`.
- Scans `survival_records[0..9]` by descending `score`. If the run does not
  place, exits after the rank cursor reaches `10`.
- If it places, shifts lower records into the spare eleventh storage slot,
  writes the new record at the selected rank, points the frontend
  `active_record_bank` at `survival_records`, and marks the pending entry as
  bank 1.

The extra `rank != -1` gate is source-shaped from native even though this local
rank search only produces non-negative ranks.

Honest match status: 89.41%, 86/84 candidate/target instructions, 36/84 exact
prefix, and six clean masked operands.

2026-07-16 void ABI recovery: the sole `complete_subgame` caller discards EAX,
and the native exits preserve incompatible incidental values: rank `10` on the
no-place path and the root pointer used by the final frontend store after an
insertion. Natural void exits keep the honest 89.41% source shape and leave the
caller unchanged; no return-value fakematch remains.

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
- 2026-06-21 result-local tail pass: carrying `int result = rank` through the
  redundant `rank != -1` guard and assigning it from the final `g_game_base`
  load inside the reachable frontend arm improves focused Wibo to 95.24% with
  matching 84/84 instruction counts. This removes the extra impossible-path
  global reload while preserving native's behavior if that guard were ever
  false; early-return and block-return forms still duplicate control flow and
  regress to roughly 82%.
- 2026-06-21 source-record scheduling retry: naming the incoming record before
  the volatile bank reload is codegen-neutral at 95.24% and does not move
  native's `mov esi, edx` before the rank-slot address arithmetic. Destination
  slot locals and raw slot-base views grow the candidate to 87 instructions and
  drop to 86.55%, while volatile record reloads perturb the prologue and fall to
  67.86%. Keep the current direct record copy after the volatile bank reload.

2026-07-10 barrier retirement and root-owner closure:

- The volatile self-reload before the inserted-record copy was solely forcing
  the native EBP spill/restore and has been removed. Clean index and pointer
  shift loops, early/late shift-rank lifetimes, direct `this` members, and a
  named source record do not reproduce that allocator decision; the readable
  direct-member source is retained at the honest 64.63% baseline.
- Root `+0x1b8/+0x30d/+0x310/+0x314` are now typed as fields of
  `GameRoot::players[0]`: frontend state, pending-entry byte, entry rank, and
  entry bank. The rank/bank words are unions with their selected-score
  rank/mode names because the front-end state machine reuses the same cRPlayer
  storage in a different state.
- The exact arcade insertion and high-score-screen destroy anchors remain
  70/70 and 11/11 after adopting the same `GamePlayer` fields.
- `active_record_bank` is now proven as the first field of this same
  `SubHighScore`, owned by `GameRoot::subgame`; the retained global-owner
  spelling preserves the honest 64.63% codegen baseline.

2026-07-11 ownership pass:

- Android and iOS preserve `cRSubHighScore::AddSurvival()`. Windows receives
  the working `SubSolution*` explicitly, then value-copies it into both the
  owner's result/pending storage and the ordered survival array.

2026-07-12 owned down-shift cursor recovery:

- A real `SubSolution*` cursor now starts at the spare eleventh survival slot,
  borrows the preceding owned record as its source, and walks backward while
  the insertion rank is shifted down. This is the source-level ownership that
  native's EBP cursor and `rep movsd` sequence were expressing; the direct
  two-index spelling hid it from VC6.
- The cursor lifetime naturally makes VC6 preserve the `SubHighScore*` owner
  across the shift loop. It recovers the native stack slot, EBP/EBX ownership,
  both initial value copies, score scan, and first 36 instructions without the
  former volatile self-reload or any other register barrier.
- Focused matching rises from the honest 64.63% baseline (`80/84`, prefix 0,
  five clean masks) to 89.41% (`86/84`, prefix 36, six clean masks). The
  remaining two instructions save and reload the destination handle across
  `rep movsd`; native instead addresses its rank field through the decremented
  cursor. That allocator choice remains visible rather than fakematched.

2026-07-17 inserted-record cursor and active-bank ownership:

- The native `bank + rank * sizeof(SubSolution)` lifetime is now replayed as
  `SubHighScoreSurvivalRankCursor *` in both decompilers. Its prefix aliases the
  bank through `survival_records`; `record` aliases `survival_records[rank]`.
  This is an analysis view, not a second bank or allocation.
- Binary Ninja pins the exact EBX identity at
  `RegisterVariableSourceType / 168 / 69`; IDA pins definition `0x417829`.
  Both now express the inserted copy, mode tag, and rank through `record`.
- IDA had separately mistaken native displacement `0x6ffae0` at `0x41787c`
  for an address inside the large `g_parcel_set_buckets` data item. The replay
  verifies the exact instruction bytes, clears only that false offset flag,
  and reads back the proved owner
  `GameRoot::subgame.sub_high_score.active_record_bank`.
- Matching source is unchanged. Focused matching remains honestly at 89.41%,
  86/84 candidate/target instructions, prefix 36/84, and six clean masks; the
  remaining allocator/scheduler residual stays visible.
