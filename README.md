# Snail Mail

[![Game & Engine progress](https://decomp.dev/banteg/snail.svg?mode=shield&category=game&label=Game%20%26%20Engine)](https://decomp.dev/banteg/snail?category=game)
[![Port core progress](https://decomp.dev/banteg/snail.svg?mode=shield&category=game.port-core&label=Port%20core)](https://decomp.dev/banteg/snail?category=game.port-core)
[![Full-executable progress](https://decomp.dev/banteg/snail.svg?mode=shield&label=Full%20executable)](https://decomp.dev/banteg/snail)

[Public reporting policy](analysis/progress/README.md) ·
[Library and ownership findings](analysis/ownership/README.md)

Reverse-engineering workspace for the original Windows version of Snail Mail.

The active focus is matching decompilation against the original gameplay
executable: recover plausible C/C++ source shapes, prove them against the
native bytes, and make the portable game core understandable before writing a
new runtime. There is no port code yet; the [port plan](docs/port/README.md)
builds one from the recovered source on SDL3.

## Current Focus

- Match gameplay functions from
  [the canonical executable](#important-artifacts) with the
  harness under [`tools/match`](tools/match).
- Keep recovered names, types, decompiles, and runtime notes synchronized under
  [`analysis`](analysis) and [`docs/re`](docs/re).
- Build the modern port from the recovered source, replacing only the
  original's platform layer; see the [port plan](docs/port/README.md). The
  platform layer stays small and explicit.
- Preserve honest partials. A near match with clear notes is more useful than
  byte-shaped source that cannot explain the original program.

## Start Here

- [Matching challenges](https://github.com/banteg/snail/issues/24) - pick a
  function to work on; partial improvements and new findings are welcome
- [DEVELOPING.md](DEVELOPING.md) - local setup, daily workflow, validation
  commands, and contribution rules
- [tools/match/README.md](tools/match/README.md) - matching decompilation
  harness, toolchain setup, and no-fakematching rules
- [tools/match/STATUS.md](tools/match/STATUS.md) - generated matching dashboard
- [docs/index.md](docs/index.md) - original-format and reverse-engineering
  documentation index

## Important Artifacts

The executable is hosted publicly and is not included in Git. From a fresh
checkout, download and verify it with:

```sh
uv run tools/match/fetch_target.py
```

This saves the SHA-256-verified matching target to
`artifacts/bin/SnailMail_unwrapped.exe`. No game installation or login is needed.
See [matching setup](tools/match/README.md#setup) for the compiler and runner.

- [Download `SnailMail_unwrapped.exe`](https://reflexive.banteg.xyz/snail/d365acf3db5335dded4dfd944e876ee2f23156595503693e0bf1baee1c8c83e5/SnailMail_unwrapped.exe)
  (724 KiB) — the canonical gameplay reversing and matching target.

Wrapper and asset analysis additionally use these files from the original game
installation. They are not included in Git or in the matching-target download;
place them in `artifacts/bin/` if needed:

- `SnailMail.RWG` — the wrapped gameplay image kept for provenance.
- `SnailMail.exe` — the Reflexive launcher/wrapper layer.
- `SnailMail.dat` — the original asset archive consumed by the inspection tools.

## Quick Commands

```sh
uv run tools/match/fetch_target.py
uv run snail match status --write tools/match/STATUS.md
tools/match/match.sh tools/match/scratches/<function>
uv run pytest
```

Use [DEVELOPING.md](DEVELOPING.md) for the fuller matching workflow.
