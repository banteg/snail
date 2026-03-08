# Segment Format

The `SEGMENTS` files are grid-based track segment definitions.

Observed structure:

- `ID:<number>`
- `Name:'<display name>'`
- `Data:`
- a fixed-width row grid after `Data:`

Current corpus notes:

- rows are `10` characters wide in the shipped files
- segment heights vary by file
- any text after column `10` is metadata attached to that row
- a literal `*` immediately after column `10` is a real per-row flag used by shipped segments

## Observed Row Metadata

- `Path=<name>`
- `Ring=<name>`
- `RingSpeed=<float>` appears in RWG parser code, though no shipped segment currently uses it
- `Parcel=<id>,(<x>,<y>,<z>)`
- `JetPack=Off`
- `3DModel=<mesh> (<x>,<y>,<z>)`
- `Velocity=(<x>,<y>,<z>)` appears in RWG parser code, though no shipped segment currently uses it
- `No Fall` / `NoFall`

Representative samples:

- [`SEGMENTS/START.TXT`](../../artifacts/extracted/SnailMail.dat/SEGMENTS/START.TXT)
- [`SEGMENTS/BIG JUMP.TXT`](../../artifacts/extracted/SnailMail.dat/SEGMENTS/BIG%20JUMP.TXT)

## Practical Notes

- `Path=<name>` resolves through a hardcoded string table in the gameplay executable, not through a path-definition file in the archive
- tag matching in the original parser is case-insensitive and substring-based, which explains spellings like `Ring=Powerup` and `Ring=Explosive`
- deeper runtime notes for path templates, runtime flags, and entity dispatch now live under [RE](../re/index.md)

## Tooling

```bash
uv run snail format artifacts/extracted/SnailMail.dat/SEGMENTS/START.TXT
```
