# Decompile Audit 2026-03-25

This note audits the current bridge and attachment models against the checked-in
Windows decompile plus the Android-backed symbol matches.

The goal is not to reopen settled runtime facts. The goal is to identify where
the current port shape may still be overfitting those facts into the wrong
abstraction.

## Scope

- Windows decompile and symbol descriptions:
  - `update_main_menu`
  - `update_high_score_screen`
  - `exit_high_score_screen`
  - `initialize_subgame`
  - `build_subgame_level`
  - `update_subgame`
  - `initialize_subgoldy_fall_state`
  - `update_subgoldy`
- Android-backed symbol matches already checked into:
  - `cRMainMenu::AI`
  - `cRHighScore::AI`
  - `cRHighScore::Exit`
  - `cRGalaxy::AI`
  - `cRHelp::AI`
  - `cRCompletion::AI`
  - `cRSubGame::AI`
  - `cRSubGoldy::AI`

## Findings

### 1. The bridge is still more screen-local than our current global model suggests

The Android symbol map keeps distinct frontend controllers instead of one shared
generic bridge object:

- `cRMainMenu::Init/AI/UnInit`
- `cRHighScore::Init/AI/UnInit/Exit`
- `cRGalaxy::Init/AI/UnInit/Open/BoxOff`
- `cRHelp::Init/AI`
- `cRCompletion::Init/AI/UnInit`
- `cRSubGame::Init/BuildLevel/AI/Complete/UnInit`

Windows matches the same split.

Practical consequence:
- the current owner-driven bridge state on `AppState` is directionally better than
  the old request dispatcher
- but it is still too easy to centralize screen-local exit logic into a single
  bridge story
- future bridge work should prefer dedicated per-screen handoff helpers over new
  global owner abstractions

### 2. `exit_high_score_screen` is not just a return-target decoder

Cross-port Android keeps a dedicated `cRHighScore::Exit`, and the Windows side
matches that helper directly.

That suggests the important native shape is:
- the high-score controller owns its own exit path
- the controller restores the owning frontend state
- replay launch and browse-back are screen-local actions first, bridge effects second

Practical consequence:
- our recent change to model browse-back as an owner mapping is good
- but the next cleanup should not pull more high-score-specific behavior into the
  generic bridge transition layer
- if we keep refining this area, the right move is extracting high-score and
  completion handoff helpers from `main.zig`, not expanding bridge-global enums

### 3. The replay-attract gap is narrower and more local than a generic bridge gap

The Windows and Android notes agree that the New Game random replay path is
owned by `update_new_game_menu`.

What is already solid:
- replay-attract is menu-local
- it rotates a local cursor
- it probes only a subset of replay banks
- it seeds persistent replay scratch and saved replay return owner `2`

What remains open:
- the menu-local timer-step writer
- the secondary suppressor lane
- whether any other frontend helper seeds a different saved owner before `26/27/28`

Practical consequence:
- the missing piece here is not “the bridge” in the abstract
- it is a bounded `update_new_game_menu` controller problem
- future RE on this topic should stay local to the menu controller and its scratch,
  not fan back out into a whole-bridge narrative

### 4. Attachment exit is not a standalone controller in the native shape

Cross-port Android only points the relevant fixed-point and carryover helpers back
into `cRSubGoldy::AI()`, and Windows still shows:

- `initialize_subgoldy_fall_state` seeds the post-follow fall state inline
- `update_subgoldy` owns the pending window, gate updates, and the clear sites
- `cRPathFollowGoldy::Traverse` is effectively inline, not a separate exported owner

Practical consequence:
- attachment exit should stay modeled as an embedded post-follow fall family inside
  player or runner logic
- we should avoid growing it into a higher-level synthetic controller
- the unresolved question is the remaining consumer and family split, not the
  existence of a missing standalone owner object

### 5. Some of our remaining “bridge” complexity may really be missing extraction work

The Android class structure suggests that a lot of the remaining complexity is not
missing semantics so much as missing boundaries in the Zig port.

Likely extraction boundaries:
- high-score controller
- completion controller
- main-menu / new-game replay-attract controller
- route-map controller

That would align the port more closely with the cross-port class split and reduce
the temptation to keep encoding frontend-local rules into one `AppState` bridge hub.

## What This Changes

### Safe conclusions

- do not reintroduce a generic bridge dispatcher
- do not treat attachment exit as evidence for a missing standalone attachment-exit object
- prefer screen-local helper extraction over new bridge-global cases
- keep replay-attract RE local to `update_new_game_menu`

### Remaining high-risk unknowns

- the full writer set behind non-startup saved-owner producers before `26/27/28`
- the New Game replay-attract timer and suppressor fields
- the direct static consumer set for `post_follow_value_b`
- the remaining attachment-retirement family split outside the already bounded clear sites

## Next RE Targets

If we keep working without new runtime evidence, the best bounded targets are:

1. `update_new_game_menu`
   - timer-step writer
   - suppressor or reseed path
   - exact replay-attract launch gating

2. `exit_high_score_screen`
   - preserved selection state
   - exact mode-owned restore fields beyond the already confirmed owner writes

3. `update_subgoldy`
   - direct xrefs to `post_follow_value_b`
   - whether any helper outside the bounded player or cameraman set reads it
