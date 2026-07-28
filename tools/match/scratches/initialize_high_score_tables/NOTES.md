# initialize_high_score_tables

Seeds the persistent high-score banks after startup/default-table load:

- postal/top-ten storage records: mode tag `0`, route/rank index `0..10`
- survival/challenge storage records: mode tag `1`, route/rank index `0..10`
- time-trial route records: mode tag `2`, route index `0..50`
- current result scratch record: mode tag/index `0`

This scratch depends on the promoted `SubSolution` stride and confirms the
three bank windows and the `current_result_record` offset in `SubHighScore`.

2026-07-11 ownership pass:

- The 8-byte active-window prefix plus 75 embedded `SubSolution` values totals
  `0x947648`, exactly matching all three Windows `Size of cRSubHighScore` /
  `Solutions` ledger prints. The enclosing type is now the authored
  `SubHighScore`, not the provisional `HighScoreBank` alias.

Focused Wibo matches 100.00%, 58/58 instructions, with four clean masked
operands.

2026-07-13 analysis propagation:

- The path-template Binary Ninja/IDA campaign now declares the same exact
  `SubHighScore` owner and embeds it at `cRSubGame +0x68b4c8`.
- Its 11 postal, 11 survival, 51 time-trial, current-result, and pending-record
  values end exactly at the working `SubSolution +0xfd2b10`; the former
  0x947648-byte anonymous runtime pad is gone.
- Binary Ninja declaration preview verifies both `SubHighScore == 0x947648`
  and the enclosing `cRSubGame == 0x1272838`, then reverts. Focused Wibo
  remains exact at 58/58 with all four operands clean.

## 2026-07-25 embedded record cursor ownership

The three initializer loops borrow one `SubSolution` element at a time from
the `SubHighScore`-owned postal, survival, and time-trial arrays. Native keeps
each current record in EDI and advances it by exactly `0x1fac0`, the proven
`sizeof(SubSolution)`. Binary Ninja had instead promoted those values to
pointers to the complete 11- or 51-element arrays.

The exact SSA identities now replay as `SubSolution*` element cursors:
`RegisterVariableSourceType` indices `7`, `45`, and `86`, all in storage `73`.
The tracked decompile exposes direct calls on each current record and
one-element cursor increments. IDA independently renders the same three
borrows as `SubSolution*` post-increment loops.

The focused replay fails closed unless `SubSolution == 0x1fac0`,
`SubHighScore == 0x947648`, and the enclosing `cRSubGame == 0x1272838`.
This is analysis-only ownership recovery; the exact matcher source and all
58/58 instructions remain unchanged.

## 2026-07-27 mobile authored lifecycle

Android and iOS preserve the boundary as `cRSubHighScore::Init()` from
`HighScore.o`. In both mobile `cRGame::Init4()` bodies it appears immediately
after player initialization and immediately before
`cRSubHighScore::MiniInit()`, then TipManager initialization. Windows reaches
the same phase after its player loop, calls this function, loads `ScoreA.dat`,
`ScoreB.dat`, and `ScoreC.dat`, and then initializes TipManager.

The mobile `Init()` bodies are empty because their separate `MiniInit()` owns
85 compact 0x38-byte records and calls one mobile mini-data loader. Windows
instead seeds 75 full 0x1fac0-byte `cRSubSolution` records here before three
desktop bank overlays are loaded. `MiniInit()` and the Windows
`load_high_scores_from_file` helper are therefore explicitly not cross-mapped;
the evidence recovers the common `Init()` owner and phase, not a false shared
record layout or function boundary.
