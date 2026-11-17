# Level Format

The `LEVELS` files define level rules and compose segment sequences.

Observed scalar fields:

- `Name`
- `Mode`
- `Track`
- `Background`
- `Fringe`
- `Parcels`
- `Quota`
- `Speed`
- `Slug` or `Garbage`
- `Salt`
- `Flags`
- `Random`
- `Length`

Observed block fields:

- `GalaxyText: { ... }`
- `Segments Begin:` ... `Segments End:`
- `First:`
- `Last:`

Segment entry lines inside `Segments Begin:` can be:

- just a segment filename such as `Wibble.txt`
- a filename plus metadata such as:
  - `Angle=<degrees>`
  - `Duration=<seconds>`
  - `Sample="<voice clip>"`
  - `Message="<tutorial text>"`

## Current Corpus Notes

- the extracted archive currently has `53` level files
- shipped `Mode:` values are `arcade`, `challenge`, and `tutorial`
- shipped `Flags:` appears as an empty marker in `52/53` files and is absent only in [`LEVELS/CHALLENGE000.TXT`](../../artifacts/extracted/SnailMail.dat/LEVELS/CHALLENGE000.TXT)
- shipped `Track:` is missing only from [`LEVELS/ARCADE000.TXT`](../../artifacts/extracted/SnailMail.dat/LEVELS/ARCADE000.TXT)
- shipped segment-entry metadata only uses three forms:
  - bare filename
  - `Angle=<degrees>`
  - tutorial-only `Duration=<seconds> Sample="<voice clip>" Message="<tutorial text>"`

## Practical Notes

- the repo parser normalizes `Slug`, `Garbage`, and `garbage` into one `garbage` field. Windows looks for `Garbage:` case-insensitively, so Postal III's `Slug:10` goes unread.
- Windows reads segment filenames starting on the line after `Segments Begin:`. Postal VI–IX put their first filename on the header line and lose that segment. See the [Windows course reproductions](../port/original-bugs.md#other-verified-windows-bugs).
- `Random:` and `Length:` feed the runtime track builder
- the PC game never reads `Mode:`; Android's loader lays Padding before every
  listed segment unless it says `Mode:Challenge` (see
  [Gameplay profiles](../port/README.md#gameplay-profiles))
- `Track:` selects the active track texture set
- `Garbage:` and `Salt:` become runtime scalars used by later entity-spawn logic
- deeper runtime-field notes now live under [RE](../re/index.md)

Representative samples:

- [`LEVELS/ARCADE000.TXT`](../../artifacts/extracted/SnailMail.dat/LEVELS/ARCADE000.TXT)
- [`LEVELS/TUTORIAL.TXT`](../../artifacts/extracted/SnailMail.dat/LEVELS/TUTORIAL.TXT)

## Tooling

```bash
uv run snail format artifacts/extracted/SnailMail.dat/LEVELS/TUTORIAL.TXT
```
