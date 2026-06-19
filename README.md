# Snail Mail

Reverse-engineering workspace for Snail Mail and the original Windows artifacts
in [`artifacts/bin`](artifacts/bin).

This is not a finished playable port yet. The active focus is matching
decompilation against the original gameplay executable: recover plausible C/C++
source shapes, prove them against the native bytes, and use those matches as
the foundation for an eventual Zig rewrite/port.

## Current Focus

- Match gameplay functions from
  [`SnailMail_unwrapped.exe`](artifacts/bin/SnailMail_unwrapped.exe) with the
  harness under [`tools/match`](tools/match).
- Keep recovered names, types, decompiles, and runtime notes synchronized under
  [`analysis`](analysis) and [`docs/re`](docs/re).
- Treat the Zig runtime under [`zig/src`](zig/src) as a porting scaffold and
  parity probe, not the final product.
- Preserve honest partials. A near match with clear notes is more useful than
  byte-shaped source that cannot explain the original program.

## Start Here

- [DEVELOPING.md](DEVELOPING.md) - local setup, daily workflow, validation
  commands, and contribution rules
- [tools/match/README.md](tools/match/README.md) - matching decompilation
  harness, toolchain setup, and no-fakematching rules
- [tools/match/STATUS.md](tools/match/STATUS.md) - generated matching dashboard
- [docs/index.md](docs/index.md) - documentation index
- [docs/rewrite/index.md](docs/rewrite/index.md) - rewrite notes and current
  parity backlog

## Important Artifacts

- [`artifacts/bin/SnailMail_unwrapped.exe`](artifacts/bin/SnailMail_unwrapped.exe)
  is the canonical gameplay reversing and matching target.
- [`artifacts/bin/SnailMail.RWG`](artifacts/bin/SnailMail.RWG) is the shipped
  wrapped gameplay image kept for provenance.
- [`artifacts/bin/SnailMail.exe`](artifacts/bin/SnailMail.exe) is the Reflexive
  launcher/wrapper layer.
- [`artifacts/bin/SnailMail.dat`](artifacts/bin/SnailMail.dat) is the original
  asset archive loaded by both the tools and the Zig runtime scaffold.

## Quick Commands

```sh
uv run snail match status --write tools/match/STATUS.md
tools/match/match.sh tools/match/scratches/<function>
uv run pytest
zig build test
```

Use [DEVELOPING.md](DEVELOPING.md) for the fuller workflow before starting new
matching or rewrite work.
