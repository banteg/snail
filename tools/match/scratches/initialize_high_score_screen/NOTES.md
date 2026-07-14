# initialize_high_score_screen @ 0x416910

Starter scratch for the high-score front-end screen.

Models the main-menu backdrop setup, selected bank pointer/count, optional name
entry mode, the ten row widgets, replay buttons, row strip tinting, and footer
buttons/shortcuts. It follows both decompiler exports plus the existing
`update_high_score_screen` scratch.

Expected residuals:
- row allocation is still consolidated through helper-shaped local control
  flow, so VC6 scheduling will differ;
- string literals are semantic and may need curated reference aliases if this
  later approaches an exact masked score;
- mode fallthrough for unexpected banks is intentionally left honest.

2026-07-10 owner closure:

- The active pointer/count live at the start of
  `GameRoot::subgame.sub_high_score`; mode 0 selects `postal_records` at bank
  `+0x08`, and mode 1 selects `survival_records` at bank `+0x15c648`.
- This corrects the prior synthetic-view spelling that accidentally selected
  the MiniDelete source window for mode 0. Focused matching is honestly 43.24%
  (436/600 instructions, prefix 1, 57 masks resolved and 14 mismatched); the
  lower sequence score is accepted because the native pointer targets and
  ownership are now correct.
- Footer ownership also confirms `+0x24` as Cancel/Escape and `+0x28` as
  Submit/Enter.

2026-07-11 cRHighScore ownership:

- Android and iOS preserve `cRHighScore::Init(int, int)`, `AI()`, and the
  surrounding `UnInit()`/`Exit()` lifecycle on this same controller.
- Windows embeds the owner at `GameRoot +0x12e6e50`. The ten-row initializer
  proves five consecutive widget banks: backgrounds at `+0x2c`, ranks at
  `+0x54`, names at `+0x7c`, scores at `+0xa4`, and replay actions at `+0xcc`.
  The last replay handle at `+0xf0` proves storage through `+0xf4`; the
  following `0x14` root bytes remain unassigned before TipManager at `+0x108`.
- The shared type is therefore `HighScore`, distinct from the embedded
  0x947648-byte persistent `SubHighScore` bank. The ownership rename is
  codegen-neutral and does not hide the initializer's existing residuals.

2026-07-12 title and per-bank source recovery:

- Native stores the heading at `HighScore +0x18`; `+0x1c` is only the footer
  Back button. Promoting `title_widget` removes the former false overwrite and
  closes the controller prefix through the five footer handles.
- The ten-row body is genuinely duplicated by selected bank. Postal rows use
  the wider fill, score anchor `160`, replay anchor `125`, and always hide the
  Replay action. Challenge rows use score anchor `125`, replay anchor `170`,
  and hide Replay only while a name is being entered. The prior consolidated
  helper both obscured that ownership and inverted the visibility condition.
- The native loop advances the persistent-record byte offset to
  `10 * 0x1fac0`, reloads the borrowed active-bank pointer after widget
  callbacks, and keeps five parallel ten-handle banks through one advancing
  name-row cursor. The footer reuses the row `y` lifetime, while unsupported
  bank values intentionally fall through the original non-returning switch.
- Restoring that source shape raises the focused match from 43.24%
  (`436/600`, prefix 1, 57 clean masks and 14 mismatches) to 98.00%
  (`600/600`, prefix 80, 137 clean masks and no relocation mismatches).
  The only residuals are twelve `tColour` temporary stack-slot permutations;
  no artificial padding, volatile aliases, or other fakematching is used.
- `bn_high_score_screen_types.h` and its narrow sync helper apply the exact
  0xf4-byte owner plus all four lifecycle prototypes without replacing the
  independently recovered `FrontendWidget` or high-score bank types. The live
  Binary Ninja replay verified `title_widget` at `+0x18`, Back at `+0x1c`, the
  four footer prototypes, and all five row banks through `+0xf4`.

2026-07-13 root-owner graph cleanup:

- The initializer now reaches the root-owned `StarManager`, `SubgameRuntime`,
  `LandscapeManager`, `Backdrop`, `BorderManager`, and player-zero
  `MouseCursorState` through `GameRoot` members instead of reconstructing each
  owner from a raw `char* + offset` cast.
- The active score-bank pointer/count and every widget allocation use the same
  typed root graph. The remaining byte cursor is intentional: native advances
  through the borrowed `SubSolution` bank by the authored `0x1fac0` record
  stride and reloads that pointer after widget callbacks.
- This removes the false global-blob ownership view without changing codegen:
  focused Wibo remains 98.00%, 600/600 instructions, prefix 80, with all 137
  masked operands clean. The twelve honest `tColour` stack-slot permutations
  remain the only residuals.

## 2026-07-14 displayed-rank ownership

The controller's five ten-handle row banks, its two active-record count stores,
and the `10 * sizeof(SubSolution)` traversal all describe the displayed top-ten
window borrowed from `SubHighScore`. They now derive from
`SUB_HIGH_SCORE_TOP_TEN_COUNT`; the persistent postal and survival owners still
retain eleven records because their extra insertion slot is storage, not a
displayed row.

The initializer and all six other `high_score.h` consumers remain
byte-identical. Their normalized hashes are:

- screen initializer: `0bd39df55b25c241ad994edecd5954938f282ed8556f066717dd0a6e55cc1f5e`
- screen update: `6e0cd1a0d6d6d15df6961385f03773f5bed35411db0fa5290b6d65143c4985a6`
- screen teardown: `c03b27ab14b4b1ce8adf08e13231c6b0de84dd3ba6ebf412d9c84e5293e51b71`
- screen exit: `1a66ead55fa149798bec6e6f9975f7c82b6098b498364f67c5c945eee70b2b2f`
- entry initializer: `a75572ab1c999e728b3bf9356515c35b99667c5991e253bcb5826e50e91b3b5d`
- compact serializer: `42e7a54dd829b5591e8c6fbad3179da8ad3ec37584c975207a0fdb73cd1d8445`
- compact deserializer: `61da5c69624b6c1ceacbaf10df68a57e4605bed0c22aa580090a32b06fe52f93`

## 2026-07-14 lifecycle return contract

Android `cRHighScore::Init(int, int)` shares a void lifecycle with `AI()`,
`UnInit()`, and `Exit()`; the Android AI body directly tail-branches among all
three peers. All three external Windows initializer callers discard EAX.
Removing the synthetic return preserves this initializer at 98.00%, 600/600,
prefix 80, with all 137 operands clean. Binary Ninja accepts the void preview
but restores the stale scalar form during live verification, so the narrow
sync reports it as deferred.
