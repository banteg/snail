# Snail Mail Asset Formats

This page documents the verified on-disk layout of [`SnailMail.dat`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.dat) and the main asset families inside it.

## Archive Container

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

### Decode Rule

The header and every payload are obfuscated with the same byte-wise XOR stream:

```text
decoded_byte = encoded_byte ^ (((absolute_offset * absolute_offset) & 0xff) ^ ((absolute_offset * 3) & 0xff))
```

Important detail:

- index bytes are decoded with `absolute_offset` starting at `0`
- payload bytes are decoded with `absolute_offset` starting at each member's `data_offset`

This matches the archive loader in [`SnailMail.RWG`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.RWG).

## Asset Families

The current archive manifest shows these top-level groups:

- `X` (`144` files): plaintext `.X2` mesh and animation fragments in a DirectX `.x`-style text format
- `SEGMENTS` (`133` files): plaintext track or segment descriptions in `.TXT`
- `VOICE` (`112` files): voice-over scripts and `.OGG` clips
- `SPRITES` (`54` files): sprite textures and related text descriptors
- `LEVELS` (`53` files): plaintext level scripts
- `SFX2` (`36` files): sound effects, mainly `.OGG`
- `OBJECTS` (`25` files): object definitions and textures
- `BACKGROUNDS` (`19` files): background scripts and textures
- `GALAXY` (`18` files): skybox or galaxy art assets
- `MUSIC` (`6` files): background music and intro/menu tracks
- `INTRO` (`2` files): intro data
- `BASS.DLL` (`1` file): embedded Windows DLL payload

Extension counts from the decoded index:

- `.txt`: `204`
- `.ogg`: `153`
- `.x2`: `124`
- `.tga`: `121`
- `.dll`: `1`

## Verified Member Formats

- `.OGG`: standard Ogg Vorbis payloads, for example `MUSIC/1.OGG` starts with `OggS`
- `.TGA`: standard TGA images, for example `OBJECTS/FONT/FONT-MENU-HOVER.TGA` starts with an uncompressed true-color TGA header
- `.TXT`: plaintext scripts and object definitions, for example:
  - `VOICE/_VOICE.TXT` starts with `/* Voice Script */`
  - `BACKGROUNDS/MENUBG.TXT` is a small background script with keys like `Fog`, `Picture`, and `Landscape`
  - `OBJECTS/FONT3D/_OBJECT.TXT` is a text-based object or mesh definition with explicit vertex lists
- `.X2`: plaintext mesh fragments, for example `X/BLASTERLEFT-BASE-000.X2` begins with `Frame MeshMaterialList {`
- `.DLL`: `BASS.DLL` decodes to a normal PE payload beginning with `MZ`

## .X2 Observations

The current Zig parser and corpus scan show that the shipped `.x2` files are text-based mesh assets with a stripped-down DirectX `.x`-style layout.

Observed structure in representative files:

- `Frame <name> { ... }`
- one or more nested `Material <name> { ... TextureFilename { "foo.tga"; } }` blocks
- `MeshTextureCoords { ... }`
- `Mesh <name> { ... }`
- a per-face material index list at the start of the `Frame` block

Observed quirks:

- files end with a trailing NUL byte
- the final `Mesh` block appears to terminate at EOF rather than with a closing brace in the shipped samples we tested
- animation sequencing is handled separately by `X/_ANIMATION.TXT`, not embedded directly in the `.x2` payloads

Loader notes verified against the original RWG decompile:

- `TextureFilename` values are resolved to `X/<basename>.tga`
- face material indices are applied after parsing the mesh faces
- faces with four indices are quads and require a fourth vertex read
- faces with other counts are treated as triangles in the original loader
- animation clips are assembled from `.x2` families listed in `X/_ANIMATION.TXT`
- `Duration:` and `Mode:` are used for playback timing
- numbered filename suffixes such as `000`, `001`, and `004` determine keyframe sample positions for interpolation

Current implementation note:

- the Zig runtime already plays these interpolated `.x2` animations directly from the archive
- `Trigger:` lists from `_ANIMATION.TXT` are still under investigation and are not yet applied during playback

## Tooling

Use the repo CLI to inspect or extract the archive:

```bash
uv run snail archive manifest
uv run snail archive extract --output artifacts/extracted/SnailMail.dat
uv run snail archive extract --prefix OBJECTS/FONT3D --output artifacts/extracted/font3d
```

The extractor writes a decoded directory tree plus `manifest.json` into the output directory.
