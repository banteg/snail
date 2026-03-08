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

## OBJECTS/_OBJECT.TXT

The decoded `OBJECTS/*/_OBJECT.TXT` files are small text mesh definitions separate from the `.x2` family.

Observed structure:

- a `[VERTEX START]` block of `index x y z` rows
- a `[FACEQUAD START]` block of quad faces
- each face row contains:
  - face index
  - four vertex indices
  - four UV pairs
  - a trailing texture name token such as `Letter`, `Lazer`, or `Barrier`

Current corpus notes:

- the extracted archive contains `4` `_OBJECT.TXT` files
- all currently use `FACEQUAD`; no triangle-only object face block has been seen yet
- texture names are logical material identifiers rather than full archive paths

Representative samples:

- [`OBJECTS/FONT3D/_OBJECT.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/OBJECTS/FONT3D/_OBJECT.TXT)
- [`OBJECTS/VAPOURLAZER/_OBJECT.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/OBJECTS/VAPOURLAZER/_OBJECT.TXT)

## SEGMENTS/*.TXT

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

Observed row metadata forms include:

- `Path=<name>`
- `Ring=<name>`
- `RingSpeed=<float>` appears in RWG parser code, though no shipped segment currently uses it
- `Parcel=<id>,(<x>,<y>,<z>)`
- `JetPack=Off`
- `3DModel=<mesh> (<x>,<y>,<z>)`
- `Velocity=(<x>,<y>,<z>)` appears in RWG parser code, though no shipped segment currently uses it
- `No Fall` / `NoFall`

Representative samples:

- [`SEGMENTS/START.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/SEGMENTS/START.TXT)
- [`SEGMENTS/BIG JUMP.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/SEGMENTS/BIG%20JUMP.TXT)

Current RWG understanding:

- `Path=<name>` resolves through a hardcoded string table inside `SnailMail.RWG`, not through a separate path-definition file in the archive
- the recovered hardcoded table currently has `51` names, including `START`, `HALFPIPE`, `TWISTER*`, and `TOAD*` variants
- RWG first normalizes some glyph classes through `normalize_segment_glyph_for_track_flags` and `lookup_table_43744c[char - 0x20]`, then classifies the normalized glyph alphabet through `lookup_table_437204[char - 0x20]` before assigning runtime tile ids
- `P` and `p` path cells later consume the copied row `Path=` index and select one of the hardcoded path-template pairs rooted at runtime offsets `0xff2914` and `0xff29bc`
- each path-template step is `0x150` bytes, which corresponds to two `0xa8`-byte template records per path id
- the selected `P/p` template also installs live attachment pointers on neighboring runtime cells, and player movement later enters a dedicated follow state when swept motion intersects those sampled path records
- `Ring=Explosive` appears in shipped text, but the RWG parser path matches the `Explode` behavior
- `3DModel=<mesh>.x` rows line up with archive meshes like `X/SIGNBANG.X2`, `X/SIGNSTOP.X2`, and `X/SIGNCONSTRUCTION.X2`
- deeper static notes for the path table and track-runtime builder now live in [`docs/reverse/path-system.md`](/Users/banteg/dev/banteg/snail-mail/docs/reverse/path-system.md)

## LEVELS/*.TXT

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

Current parser behavior:

- normalizes `Slug`, `Garbage`, and `garbage` into one `garbage` field
- preserves tutorial messages exactly, including in-string marker characters like `>` and `{`
- keeps per-segment metadata as structured attributes in addition to common convenience fields

Representative samples:

- [`LEVELS/ARCADE000.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/ARCADE000.TXT)
- [`LEVELS/TUTORIAL.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/TUTORIAL.TXT)

## Tooling

Use the repo CLI to inspect or extract the archive:

```bash
uv run snail archive manifest
uv run snail archive extract --output artifacts/extracted/SnailMail.dat
uv run snail archive extract --prefix OBJECTS/FONT3D --output artifacts/extracted/font3d
uv run snail format artifacts/extracted/SnailMail.dat/OBJECTS/FONT3D/_OBJECT.TXT
uv run snail format artifacts/extracted/SnailMail.dat/SEGMENTS/START.TXT
uv run snail format artifacts/extracted/SnailMail.dat/LEVELS/TUTORIAL.TXT
```

The extractor writes a decoded directory tree plus `manifest.json` into the output directory.
