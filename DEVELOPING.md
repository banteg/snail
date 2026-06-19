# Developing

This repo is evidence-first. The current goal is to recover the original game
well enough to make a future rewrite boring: matching decompilation establishes
proof-grade behavior, runtime captures fill gaps, and the Zig code follows only
where the evidence is strong.

## Ground Rules

- The primary work surface is matching decompilation against
  `artifacts/bin/SnailMail_unwrapped.exe`.
- A 100% scratch with a clean masked-operand audit is the strongest porting
  reference. Link or cite it when moving behavior into Zig.
- Do not fakematch: no inline asm, dummy externs, flag shopping, or
  byte-shaped source that does not read like plausible original code.
- Keep partials visible. Record residual diffs and hypotheses in the scratch
  `NOTES.md` instead of hiding mismatch debt.
- Prefer generated status and primary evidence over old narrative docs. When
  `analysis/runtime/*.md`, decompile exports, or `tools/match/STATUS.md`
  contradict older prose, update the stale prose after the fix lands.
- Use conventional commits. Preserve unrelated dirty work.

## Setup

Python work should run through `uv`:

```sh
uv run snail --help
uv run pytest
```

The matching harness also needs `wibo` and the decomp.me MSVC bundles. Follow
the setup in [tools/match/README.md](tools/match/README.md); the compiler and
scratch build outputs are local tooling artifacts and should stay untracked.

Zig is used for the native rewrite scaffold and parity probes:

```sh
zig build
zig build test
zig build run -- smoke
```

Docs can be previewed locally with:

```sh
zensical serve
```

## Daily Matching Workflow

1. Refresh the board:

   ```sh
   uv run snail match status --write tools/match/STATUS.md
   ```

2. Pick a target from [tools/match/STATUS.md](tools/match/STATUS.md), then read
   the nearby evidence before editing:
   - `analysis/decompile/binja/functions/*.c`
   - `analysis/symbols/gameplay-functions.json`
   - `analysis/symbols/gameplay-references.json`
   - `tools/match/include/*.h`
   - relevant `docs/re/*.md` and `analysis/runtime/*.md`

3. Create or update `tools/match/scratches/<function>/`:
   - `scratch.cpp` for the candidate source
   - `scratch.conf` with `FUNCTION=<manifest name>` plus only necessary `END`
     or `SYMBOL` overrides
   - `NOTES.md` for residual diffs, source-shape rationale, and evidence links

4. Iterate with the harness:

   ```sh
   tools/match/match.sh tools/match/scratches/<function>
   tools/match/match.sh tools/match/scratches/<function> --full
   uv run snail match diff tools/match/scratches/<function>/build/scratch.obj <function> --regions
   uv run snail match dump tools/match/scratches/<function>/build/scratch.obj <function> --side target
   ```

5. When a slice is coherent, regenerate status and run focused tests:

   ```sh
   uv run snail match status --write tools/match/STATUS.md
   uv run pytest tests/test_match.py
   ```

6. Commit the scratch, shared headers, manifest/reference changes, notes, and
   regenerated status together when they describe one recovery step.

## Symbols, Types, And Decompile Exports

Tracked function names live in
`analysis/symbols/gameplay-functions.json`. Recovered globals, constants, and
other references live in `analysis/symbols/gameplay-references.json`.

Useful maintenance commands:

```sh
uv run snail symbols --manifest analysis/symbols/gameplay-functions.json
uv run snail match audit --exact-only
uv run snail match types --paths
```

When synchronizing tool databases, prefer the documented paths in
[docs/re/symbols.md](docs/re/symbols.md). Keep new rename work in the canonical
unwrapped gameplay target and avoid wholesale generated churn when a narrow
manifest or decompile export is enough.

## Rewrite And Port Work

The Zig runtime is currently a validation surface, not the product. It should
consume original assets directly and move toward native gameplay only when the
matching, decompile, or runtime-trace evidence is strong enough.

Current rewrite references:

- [docs/rewrite/remaining-work-checklist.md](docs/rewrite/remaining-work-checklist.md)
  for active parity work and blind spots
- [docs/rewrite/native-mirror-campaign.md](docs/rewrite/native-mirror-campaign.md)
  for the native-mirror strategy
- [docs/rewrite/subsystem-status.md](docs/rewrite/subsystem-status.md) for
  subsystem notes
- `analysis/runtime/*.md` for dated parity audits and runtime captures

Useful runtime probes:

```sh
zig build run -- smoke
zig build run -- debug
zig build run -- --start-phase main_menu
zig build run -- --hidden-window --timeout-seconds 10 --screenshot-at intro:120
```

If a porting change is driven by a matched scratch, cite the scratch in the Zig
comment or adjacent note. If it is driven by runtime observation instead, cite
the capture or dated analysis note and keep the uncertainty explicit.

## Other Repo Tools

The `snail` CLI contains repeatable helpers for archive, format, trace, symbol,
and screenshot work:

```sh
uv run snail inspect
uv run snail inspect artifacts/bin/SnailMail.dat
uv run snail archive manifest
uv run snail archive extract --output artifacts/extracted/SnailMail.dat
uv run snail format artifacts/extracted/SnailMail.dat/LEVELS/TUTORIAL.TXT
uv run snail trace summary /path/to/snailmail-trace.ndjson
uv run snail trace plan
uv run snail screenshots compare <render.png> <reference.png> --search-offset 8 --search-scale 0.95:1.05:0.01
```

Use these commands instead of ad hoc scripts when the repo already has a
structured path for the evidence.
