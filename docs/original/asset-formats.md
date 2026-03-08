# Asset Formats Overview

This section documents the verified on-disk layout of [`SnailMail.dat`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.dat) and the major asset families inside it.

The original page grew into a single long reference. It is now split by format so the side nav can take you directly to the relevant part of the corpus.

## Pages

- [Archive container](archive-container.md): the archive index layout and decode rule
- [Asset families](asset-families.md): top-level groups and extension counts
- [X2 format](x2-format.md): mesh and animation-fragment layout
- [OBJECT format](object-format.md): `_OBJECT.TXT` structure
- [Segment format](segment-format.md): `SEGMENTS/*.TXT` grammar and authored metadata
- [Level format](level-format.md): `LEVELS/*.TXT` grammar and scalar fields

## Tooling

```bash
uv run snail archive manifest
uv run snail archive extract --output artifacts/extracted/SnailMail.dat
uv run snail format artifacts/extracted/SnailMail.dat/OBJECTS/FONT3D/_OBJECT.TXT
uv run snail format artifacts/extracted/SnailMail.dat/SEGMENTS/START.TXT
uv run snail format artifacts/extracted/SnailMail.dat/LEVELS/TUTORIAL.TXT
```
