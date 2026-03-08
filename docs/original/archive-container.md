# Archive Container

`SnailMail.dat` is a flat archive with:

- a decoded entry count at file offset `0x00`
- `entry_count` fixed-size records starting at `0x04`
- a NUL-terminated path string table immediately after the records
- encoded file payloads laid out sequentially after the string table

Each index record is 12 bytes:

```text
uint32 path_offset
uint32 data_offset
uint32 size
```

Observed values for the shipped bundle:

- `entry_count = 603`
- first payload `data_offset = 20789`
- the first payload offset is also the full decoded index size

## Decode Rule

The header and every payload are obfuscated with the same byte-wise XOR stream:

```text
decoded_byte = encoded_byte ^ (((absolute_offset * absolute_offset) & 0xff) ^ ((absolute_offset * 3) & 0xff))
```

Important detail:

- index bytes are decoded with `absolute_offset` starting at `0`
- payload bytes are decoded with `absolute_offset` starting at each member's `data_offset`

This matches the archive loader in the gameplay executable, which we now prefer to study through [`SnailMail_unwrapped.exe`](../../artifacts/bin/SnailMail_unwrapped.exe) even though the original shipped image is [`SnailMail.RWG`](../../artifacts/bin/SnailMail.RWG).

## Tooling

Use the repo CLI to inspect or extract the archive:

```bash
uv run snail archive manifest
uv run snail archive extract --output artifacts/extracted/SnailMail.dat
uv run snail archive extract --prefix OBJECTS/FONT3D --output artifacts/extracted/font3d
```

The extractor writes a decoded directory tree plus `manifest.json` into the output directory.
