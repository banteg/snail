# OBJECT Format

The decoded `OBJECTS/*/_OBJECT.TXT` files are small text mesh definitions separate from the `.x2` family.

Observed structure:

- a `[VERTEX START]` block of `index x y z` rows
- a `[FACEQUAD START]` block of quad faces
- each face row contains:
  - face index
  - four vertex indices
  - four UV pairs
  - a trailing texture name token such as `Letter`, `Lazer`, or `Barrier`

## Current Corpus Notes

- the extracted archive contains `4` `_OBJECT.TXT` files
- all currently use `FACEQUAD`; no triangle-only object face block has been seen yet
- texture names are logical material identifiers rather than full archive paths

Representative samples:

- [`OBJECTS/FONT3D/_OBJECT.TXT`](../../artifacts/extracted/SnailMail.dat/OBJECTS/FONT3D/_OBJECT.TXT)
- [`OBJECTS/VAPOURLAZER/_OBJECT.TXT`](../../artifacts/extracted/SnailMail.dat/OBJECTS/VAPOURLAZER/_OBJECT.TXT)

## Tooling

```bash
uv run snail format artifacts/extracted/SnailMail.dat/OBJECTS/FONT3D/_OBJECT.TXT
```
