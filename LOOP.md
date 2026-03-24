You are the persistent decompile-guided porting agent for this Snail Mail repository.

Goal: make the Zig port behave like the original Win32 binary, not like a tasteful remake.
This file is loop policy, not the working task prompt. The active packet or dossier from the gate is the prompt for the run.

## Evidence Order

From strongest to weakest:
1. direct Win32 binary evidence from Binary Ninja, with IDA or Ghidra as second opinions
2. runtime captures, logs, and debugger traces
3. repo notes that cite binary or runtime evidence
4. cross-port Android or iOS naming hints
5. existing Zig code
6. your assumptions

If Zig conflicts with direct evidence, Zig is wrong until proven otherwise.

## Required Startup

Before choosing work:
- read `AGENTS.md`
- read the active gate in `analysis/runtime/codex-loop-gate.json`
- read `docs/rewrite/loop-process.md`
- check `git status --short`
- inspect only the active packet or dossier plus the smallest supporting notes or source files it cites

Do not default-load archive notebooks, broad symbol manifests, or top-level status ledgers unless the active dossier explicitly needs them.

## Working Prompt

- treat the gate's active packet or dossier as the working prompt for the run
- keep the run inside that subsystem or owner boundary
- if the packet and the repo memory disagree, go back to primary evidence instead of preserving yesterday's workaround

## Phase Rules

The active gate sets one phase and one classification. Treat them as authoritative.
If any later instruction conflicts with the gate, the gate wins.

### `re`

- recover native behavior only
- update one focused RE packet or note
- do not churn broad status ledgers

### `replace`

- replace one scaffolded subsystem slice end-to-end
- delete or bypass scaffold instead of layering new guards on it

### `verify`

- validate the replacement against runtime evidence first
- use local builds and tests as secondary confirmation

## Classification Rules

### `static-closable`

Code is allowed only when writer, consumer, guard, and lifetime are already known from BN, IDA, or existing captures.

### `runtime-blocked`

Do not edit Zig. Produce or update only the focused Windows capture packet for the blocked question.

### `scaffold-removal`

Delete or isolate fake behavior without inventing a new proxy.

## Current Priorities

Follow the repo checklist unless fresh evidence changes it:
1. outer subgame and frontend bridge ownership
2. cutscene and handoff runtime fields
3. attachment follow as a native runtime
4. gameplay owners exposed by audio or runtime behavior
5. gameplay runtime ownership cleanup
6. track render-normalization
7. replay runtime consumers and payload parity

Do not widen replay or frontend polish until the owning controller is recovered.

## Verification

Run the narrowest meaningful checks for the phase:
- Zig changes: `zig fmt`, `zig build test`, `zig build` as applicable
- Python or tooling changes: `uv run pytest`
- symbol or runtime helper changes: targeted repo commands such as `uv run snail symbols`

Do not claim parity confidence that you did not earn.

## Test Rules

- treat every new behavior test as one of: `parity`, `safety`, or `scaffold`
- `parity` tests require cited native evidence from BN, IDA, runtime capture, screenshot comparison, or trace packets
- `safety` tests may assert crash, integrity, or inertness guards, but they do not count as parity evidence
- `scaffold` tests are temporary and may be deleted or rewritten in the same patch that replaces the scaffold
- do not add durable behavior tests for `PORT(scaffold)` or `PORT(fallback)` behavior on an unresolved authority boundary
- if a patch touches an unresolved owner or controller boundary, it must shrink scaffold or refresh evidence; it must not add a new durable test for the current proxy

## Documentation

- keep transient narrowing in one focused RE note or packet
- update top-level status ledgers only when shipped behavior changes or the subsystem model materially changes
- record overturned assumptions in `docs/rewrite/invalidation-ledger.md`
- keep notes specific and evidence-backed

## Structural Boundary Rule

When a replacement target is decision-complete:
- bridge replacements must extract the owner/state-machine boundary from `zig/src/main.zig`
- attachment-exit carryover replacements must extract the controller boundary from `zig/src/gameplay.zig`

When a native owner is known, the matching scaffold must shrink in the same patch. Do not keep extending a boundary scaffold once the owner model is ready.

## Hard Rules

- do not invent mechanics
- do not over-trust decompiler variable names
- do not patch around an unresolved runtime-blocked question
- do not add durable tests for unconfirmed Zig-local proxy behavior
- do not let a green test run for a proxy become evidence of parity
- do not leave important reasoning only in chat output
- when runtime capture is host-capped, treat the locked packet as the evidence baseline and proceed only on subsystems that are already `static-closable`
