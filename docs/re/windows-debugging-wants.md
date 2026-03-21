# Windows Debugging Wants

This handoff is the current prioritized wish list for a focused Windows runtime-debugging session against the original game.

Use it together with:

- [Windows Frida handoff](windows-frida-handoff.md)
- [Frida runtime trace](frida-runtime-trace.md)
- [Runtime structures](runtime-structures.md)
- [Attachment follow state](attachment-follow.md)
- [artifacts/gpt-pro-packages/answers/14-gpt-pro.md](../../artifacts/gpt-pro-packages/answers/14-gpt-pro.md)
- [artifacts/gpt-pro-packages/answers/15-gpt-pro.md](../../artifacts/gpt-pro-packages/answers/15-gpt-pro.md)

## Goal

Static RE is now good enough that the highest-value unknowns are no longer broad "what does this subsystem do?" questions.

The remaining Windows-side value is in:

- confirming the remaining source-matrix and hotspot-bank ownership behind the cutscene camera fields
- proving the real handoff timing for completion, death, respawn, and final loss
- replacing the last Zig-side fallback values with directly observed runtime fields
- capturing the real cutscene camera construction path instead of inferring it from offsets and state labels

## Session Order

Run the session in this order unless blocked:

1. Cutscene anchor writers
2. Failure handoff and death path
3. Completion handoff controller
4. Attachment-exit field consumers
5. Outer subgame startup and fresh-start flags
6. Full cutscene matrix capture

That order is intentional:

- the hotspot-bank source matrices unblock the last remaining intro/completion/death shot geometry questions
- the failure and completion handoffs unblock the last major app-side timing fallbacks
- the attachment-exit consumers settle the remaining camera layering ambiguity

## 1. Cutscene Hotspot Source Matrices

### Why this matters

The old `player + 6208` / `+6280` mystery is no longer a pair of isolated writer-less cutscene fields. Later RE and the March 15 CDB session now explain those reads as `snail_hotspots_world[12]` and `snail_hotspots_world[18]`, maintained by `update_snail_skin`.

What is still unresolved is upstream of that:

- why hotspot slots `0..10` use one cached source matrix while `11..18` use another
- which exact live player or animation/controller lanes publish those source matrices
- whether completion and death reuse hotspot `18` for an authored reason or because another camera-target source is still missing

### What to do

- Put write watchpoints on the two cached source matrices that feed the hotspot world bank:
  - `player + 0x1604`
  - `player + 0x1684`
- Trigger:
  - fresh start intro
  - normal course completion
  - hazard death
  - floor-gap fall
- For each write, record:
  - EIP / function
  - call stack if available
  - cutscene state before and after
  - the full written vector or matrix payload
  - whether the write happens once on entry or continuously each frame

### Questions to answer

- Which function writes each source matrix?
- Do intro, completion, and death all reuse the same matrix writers?
- Are the two matrices driven by player pose, snail-skin animation, cameraman state, or a separate controller?
- Does hotspot `18` stay active in completion/death because of authored hotspot choice or because another target lane is still unresolved?

### Done when

- the source-matrix writer functions are named or at least uniquely identified
- one capture shows the matrix inputs for intro
- one capture shows the matrix inputs for completion
- one capture shows the matrix inputs for death

## 2. Failure Handoff And Death Path

### Why this matters

The Zig port still uses a provisional in-fall `world_y <= -7` boundary as the final respawn or final-loss handoff. Bundle 14 and bundle 15 both argue the real failure selector still lives in `initialize_subgoldy_death`, the player cutscene controller, and the resurrect path.

### What to do

- Break on:
  - `initialize_subgoldy_death`
  - `update_cutscene`
  - `update_subgoldy`
  - `update_subgoldy_resurrect`
- Watch:
  - `player + 0x41d` `attachment_exit_pending`
  - `player + 0x424` `attachment_exit_anchor_z`
  - `player + 0x42c` `post_follow_value_a`
  - `player + 0x430` `post_follow_value_b`
  - `player + 0x434` `attachment_exit_progress`
  - `player + 0x438` `attachment_exit_progress_step`
  - visible lives
  - current cutscene state
- Trigger three cases separately:
  - a hazard death with spare lives in Postal mode
  - a hazard death with no spare lives in Postal mode
  - a Challenge or Time Trial death

### Questions to answer

- What exact condition calls `initialize_subgoldy_death()`?
- Is `world_y < -7` only an in-fall threshold, or is there a later gate before respawn/final loss?
- Where does "respawn vs final loss" get selected?
- When is the visible-life decrement actually committed?
- Does the death path differ between hazard death and floor-gap fall?

### Done when

- the final respawn or failure selector is captured once with spare lives
- the final-loss selector is captured once with no spare lives
- the commit point for visible-life decrement is known

## 3. Completion Handoff Controller

### Why this matters

The completion path is now typed more clearly in static RE:

- `player + 0x440` `completion_handoff_active`
- `player + 0x444` `completion_handoff_timer`
- `player + 0x448` `completion_handoff_timer_step`
- `player + 0x44e` `completion_handoff_voice_gate`

The port still waits too long before entering the completion screen. Windows appears to initialize the completion screen at cutscene state `5`, not only after a delayed app-side handoff.

### What to do

- Break on:
  - `update_subgoldy`
  - `update_cutscene`
  - `initialize_completion_screen`
  - `complete_subgame`
- Watch:
  - `player + 0x440`
  - `player + 0x444`
  - `player + 0x448`
  - `player + 0x44e`
- Trigger:
  - normal level completion
  - completion with the fast-forward condition if you can reproduce the `row_event_display + 0x18` gate

### Questions to answer

- At what exact cutscene state does `initialize_completion_screen()` fire?
- Is state `5` only a one-shot initializer, with states `6/7` being pure blend/hold?
- Which function owns the `2.0s` voice gate and `5.0s` fade path?
- What exactly fast-forwards the handoff timer to `5.1`?

### Done when

- one capture shows the first frame where `completion_handoff_active` becomes true
- one capture shows the first call to `initialize_completion_screen`
- one capture shows the first call to `complete_subgame`

## 4. Attachment-Exit Field Consumers

### Why this matters

The broad shape is now known:

- `post_follow_value_a` feeds `RotWorldZ` in the live cameraman
- `post_follow_value_b` is written from the attachment-follow/template handoff
- `attachment_exit_progress` advances during fall
- the two follow-effect gates flip during the in-flight transition

What is still missing is the exact consumer set for `post_follow_value_b` and the precise semantics of the two gate bytes.

### What to do

- Break on:
  - `end_track_attachment_follow_state`
  - `update_subgoldy`
  - `update_cameraman`
- Watch:
  - `player + 0x42c`
  - `player + 0x430`
  - `player + 0x434`
  - `player + 0x44c`
  - `player + 0x44d`
- Capture one clean sequence:
  - active attachment follow
  - attachment exit
  - in-fall transition
  - respawn or death handoff

### Questions to answer

- Is `post_follow_value_b` ever read directly after the handoff write?
- Are `+0x44c` and `+0x44d` purely visual or do they gate gameplay state transitions?
- Does `attachment_exit_pending` clear only when progress reaches `1`, or can another controller clear it early?
- Does `post_follow_value_a` get integrated in player space, world space, or mixed space before the camera call?

### Done when

- every read of `player + 0x430` in the captured window is accounted for
- the clear site for `attachment_exit_pending` is identified
- one note explains what each of the two gate bytes seems to control

## 5. Outer Subgame Startup And Fresh-Start Flags

### Why this matters

The port now seeds intro cutscene ownership into the runner, but the exact meanings of:

- `subgame + 16721360`
- `subgame + 16721361`
- `subgame + 16721364`

are still unresolved. Bundle 14 only narrowed the startup cutscene condition enough to reject tutorial-only ownership.

### What to do

- Break on:
  - `initialize_subgoldy`
  - `initialize_subgame`
  - `build_subgame_level`
  - `update_subgame`
- Also watch the front-end bridge controller's active-state and preserved-owner slots while those breaks fire:
  - `update_frontend_state_machine` reads active state from `[controller + 0x94]`
  - `update_frontend_state_machine` reads the `26/27/28` bridge jump target from `[controller + 0x98]`
  - a static BN sweep did not find a shallow store to `[controller + 0x98]`, so the likely writer is outside the obvious front-end state-machine cluster
- Watch the three flag bytes or dwords above during:
  - fresh level start
  - respawn rebuild
  - completion
  - return to frontend shell

### Questions to answer

- Which one is the real "fresh start" or "continuation" gate?
- Which one survives respawn rebuilds?
- Which one distinguishes frontend shell from active gameplay rebuild?
- Are any of them replay or route-mode flags rather than pure lifecycle state?
- Which function writes the preserved-owner bridge slot consumed by `26/27/28`?

### Done when

- each field has at least one observed writer and one observed read site
- the fresh-start cutscene condition can be named more narrowly than "not tutorial-only"

## 6. Full Cutscene Matrix Capture

### Why this matters

The port has moved cutscene ownership toward the runner, but the real missing piece is still cutscene camera construction. The cleanest way to settle that is to record the actual matrices or their anchor inputs over time.

### What to do

- For intro, completion, and death:
  - capture per-frame cutscene state
  - capture the shared subgame camera matrix
  - capture the live cameraman matrix
  - capture the override matrix if separate
  - capture the anchor fields when available
- Record at least:
  - the first frame of the cutscene
  - the midpoint of the blend
  - the final held frame
  - the handoff frame back to gameplay or frontend flow

### Questions to answer

- Is the current inferred state machine `1 -> 2 -> 8 -> 9`, `5 -> 6 -> 7`, and `10 -> 11 -> 12` correct in runtime order?
- Are completion and death built from the same anchor pair with different offsets, or from different anchor sources?
- Does the live cameraman continue updating underneath the override every frame?
- Is there any additional snap or interpolation state not captured in the current Zig controller?

### Done when

- one intro capture has enough data to reconstruct the exact blend path
- one completion capture has enough data to reconstruct the exact blend and hold path
- one death capture has enough data to reconstruct the exact blend and hold path

## Tooling Preference By Target

Prefer the broad Frida trace when:

- you need many frames of lightweight field capture
- you need to correlate player state, attachment state, and track state over time
- you need operator-friendly NDJSON artifacts

Prefer debugger breakpoints or hardware watchpoints when:

- you need the first writer of an unresolved field
- you need to catch a rare one-shot initializer
- you need call stacks or exact instruction provenance

In practice, the best flow is usually:

1. Reproduce with Frida and identify the exact frame window.
2. Re-run with debugger breakpoints or watchpoints only over that window.
3. Save both the trace artifact and a short text note naming the writer or reader.

## Deliverables

For each successful session, hand back:

- the raw trace path
- a short markdown or text note naming the target
- the exact function addresses or names hit
- the specific question answered
- any new unresolved question that appeared during the run

Good examples:

- "writer for hotspot source matrix `player + 0x1604` found"
- "respawn vs final-loss selector captured"
- "first `initialize_completion_screen` call frame captured"
- "all reads of `player + 0x430` accounted for"

## If There Is Only Time For One Thing

Do the hotspot-source-matrix watchpoint pass first.

That one result would remove the biggest remaining geometry guess from intro, completion, and death all at once, and it would make every later camera comparison more concrete.
