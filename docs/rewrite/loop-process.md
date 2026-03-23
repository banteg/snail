# Decompile/Port Loop Process

This is the operating policy for the automated decompile-guided port loop.

## Phases

- `re`
  - recover native behavior only
  - update one focused RE packet or note
  - do not patch Zig when the question is still runtime-blocked
- `replace`
  - replace one scaffolded subsystem slice with recovered behavior
  - delete or bypass existing scaffold instead of layering new guards on it
- `verify`
  - validate the replacement against runtime evidence first and local tests second

## Classifications

- `static-closable`
  - code is allowed only when writer, consumer, guard, and lifetime are already known from BN, IDA, or existing captures
- `runtime-blocked`
  - no Zig edits
  - produce or update one focused Windows capture packet only
- `scaffold-removal`
  - remove or isolate fake behavior
  - do not replace one proxy with another unless directly evidenced

## Loop Discipline

- The active gate lives in `analysis/runtime/codex-loop-gate.json`.
- The gate packet is the active working dossier unless the operator overrides it with `--prompt-file`.
- The runner state lives in `artifacts/codex-loop/state.json`.
- The visible human handoff lives in `artifacts/codex-loop/next-action.md`.
- `LOOP.md` is policy only. Do not use it as the sole repeated task prompt.
- The loop stops when:
  - the current target is `runtime-blocked`
  - the same unresolved blocker appears again without fresh BN, IDA, or Frida evidence
  - required evidence artifacts are missing or stale
- Only the gate's `freshness_artifacts` can unblock a repeated blocker. Context docs may stay required without counting as fresh evidence by themselves.

## Prompt Shape

- Keep default context thin:
  - policy file
  - active gate
  - active dossier or packet
  - only the smallest supporting notes or source files the dossier cites
- Do not reread the full worklog, giant symbol manifests, or broad status ledgers by default.
- Treat the dossier as the current unit of work:
  - one owner, controller, or state machine
  - one explicit safe-to-code boundary
  - one scaffold kill-list
- Use three distinct pass types even if the tooling stays lightweight:
  - analysis pass: refresh the dossier, no Zig edits
  - implementation pass: replace or delete scaffold within the dossier boundary
  - review pass: check that scaffold shrank and native evidence got stronger

## Logging And Docs

- Use compact batch logging instead of a mandatory per-iteration template.
- Update the top-level status ledgers only when shipped behavior changes or the subsystem model materially changes.
- Keep transient narrowing inside one focused RE note or packet.
- Record overturned models in `docs/rewrite/invalidation-ledger.md` so old workarounds do not stay sticky as repo memory.

## Test Triage

- `parity`
  - confirmed native behavior
  - durable
- `safety`
  - crash or integrity guards
  - durable
- `scaffold`
  - temporary tests that are expected to change or disappear during replacement

Do not add new durable tests for unconfirmed Zig-local proxy behavior.

## Extraction Policy

Extract code from `zig/src/main.zig` only along recovered subsystem boundaries:
- outer bridge and state machine
- frontend owners and screens
- HUD, pause, and high-score flows

Avoid pure architecture cleanups that are not attached to an evidence-backed replacement.

Current structural forcing function:
- if the next replacement target is the outer bridge, extract that owner/state-machine logic from `zig/src/main.zig` as part of the replacement
- if the next replacement target is attachment-exit carryover, extract that controller boundary from `zig/src/gameplay.zig` as part of the replacement
- when a replacement lands, the boundary scaffold must shrink in the same patch instead of gaining new Zig-side enums, flags, or dispatch cases

## Metrics

Track these as health checks for the loop:
- fresh runtime captures or debugger-backed notes landed
- blind spots closed
- scaffold-test count
- scaffold markers in `zig/src`

Do not use commit count as the primary success metric.

## Current Freeze

- Freeze further attachment-exit micro-narrowing Zig changes until fresh Windows evidence lands.
- Freeze further outer-bridge micro-narrowing Zig changes until fresh Windows evidence lands.
- The active batch packet is `analysis/runtime/windows-re-batch-2026-03-24.md`.
