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
- `find_case_insensitive_substring` is the generic metadata matcher in the RWG parser, so tag matching is case-insensitive and substring-based rather than exact
- that matcher explains why shipped text like `Ring=Powerup` and `Ring=Explosive` still matches the RWG parser's canonical probes `Ring=PowerUp` and `Ring=Explode`
- RWG first normalizes some glyph classes through `normalize_segment_glyph_for_track_flags` and `lookup_table_43744c[char - 0x20]`, then classifies the normalized glyph alphabet through `lookup_table_437204[char - 0x20]` before assigning runtime tile ids
- after the glyph-to-tile pass, RWG runs a renderer-facing cleanup pipeline with named cache buckets `Floor`, `Slide`, `Warn`, `Ramp`, and `Fringe`
- that renderer pipeline uses helper families now recovered in the Binary Ninja database:
  - `is_floor_cache_tile_family`
  - `is_slide_cache_tile_family`
  - `is_ramp_cache_tile_family`
  - `is_open_neighbor_tile_family`
- `P` and `p` path cells later consume the copied row `Path=` index and select one of the hardcoded path-template pairs rooted at runtime offsets `0xff2914` and `0xff29bc`
- each path-template step is `0x150` bytes, which corresponds to two `0xa8`-byte template records per path id
- most named path ids build the first `0xa8` record with a constructor family and then build the second record by mirroring it across X
- `SUPERTRAMP` and `START` are the clearest exceptions: both halves are constructed explicitly instead of through the generic mirror helper
- `WARP` still has no clean recovered constructor site, and no shipped extracted segment or level text currently references it by name
- the per-row dword at segment offset `+0x88c` is a generic metadata flag byte, not a clean ring-only enum
- observed ring bits in that byte are:
  - `Ring=None` -> `0x02`
  - `Ring=Normal` -> `0x04`
  - `Ring=Explode` -> `0x08`
  - `Ring=Slow` -> `0x10`
  - `Ring=PowerUp` -> `0x20`
- the runtime ring or special-effect builder in `populate_track_runtime_entities` checks `if ((row_flags & 0x02) == 0)` before it considers any of the other ring bits, so `Ring=None` suppresses the helper entirely on `R` rows
- on the authored `R` tile path, the later helper mode selection is:
  - default or `Ring=Normal` -> mode `5`
  - `Ring=PowerUp` -> mode `8`
  - `Ring=Explode` -> mode `6`
  - `Ring=Slow` -> mode `7`
- the ring-effect particle initializer groups those modes into three visible sprite families:
  - modes `4`, `5`, and `8` -> `Sprites/ParticleRing-big.tga` and `Sprites/ParticleRing-small.tga`
  - modes `2` and `6` -> `Sprites/ParticleExplode-big.tga` and `Sprites/ParticleExplode-small.tga`
  - modes `3` and `7` -> `Sprites/ParticleSlow-big.tga` and `Sprites/ParticleSlow-small.tga`
- `RingSpeed=` stores a per-row float, and the helper's authored ring modes `5` through `8` are the path that uses the row float argument to derive the orbit angular speed
- those bits live in a packed row-flags dword rather than one flat byte:
  - low byte:
    - `Parcel` sets `0x01`
    - `3DModel` also sets `0x02`
    - `Path` and `Velocity` also set `0x08`
  - second byte:
    - `NoFall` sets `0x01` and becomes runtime mask `0x100`
    - `Ring=None` sets `0x02`
    - `Ring=Normal` sets `0x04`
    - `Ring=Explode` sets `0x08`
    - `Ring=Slow` sets `0x10`
    - `Ring=PowerUp` sets `0x20`
    - `JetPack=Off` sets `0x80` and becomes runtime mask `0x8000`
- deeper runtime caution:
  - the rebuilt track cell flags are a merged bitfield, not a clean one-tag-to-one-bit map
  - `rebuild_track_runtime_from_segments` copies `Parcel` rows into runtime low-byte `0x01` plus `0x4000`, and fills `parcel_id` plus parcel offsets at `+0x5ccb64` and `+0x5ccb58/+0x5ccb5c/+0x5ccb60`
  - `rebuild_track_runtime_from_segments` copies `NoFall` rows into runtime mask `0x100`
  - `rebuild_track_runtime_from_segments` copies authored `JetPack=Off` rows into runtime mask `0x8000`
  - `select_track_tile_edge_variants` later also sets runtime mask `0x8000` on certain adjacency-mask cases while choosing edge or corner art, so that lane is not JetPack-only by the end of the full build
  - `build_track_render_caches` and `build_track_fringe_objects` then consume the same rebuilt cells through render-side helpers, so bits like `0x4000`, `0x20`, and low-byte `0x40` should not be treated as parser-level authored tags
  - `normalize_segment_glyph_for_track_flags` already consumes `NoFall` at runtime mask `0x100`, where it suppresses at least the `=` and `|` glyph remaps on flagged rows
  - a player jetpack update path later samples the current runtime cell and treats `BYTE1(cell_flags) & 0x80` as `Auto Shutoff Jetpack`
  - path-template propagation separately uses low-byte `0x40` and `0x80` as the primary and secondary attachment-follow lanes, with live pointers at `+0x5ccb6c` and `+0x5ccb70`
  - so the secondary path-attachment lane is still separate at the full runtime-mask level, but runtime `0x8000` itself is shared between authored `JetPack=Off` and later edge-variant selection
  - `allocate_challenge_parcels_on_track` treats `(cell_flags & 0x01) != 0` plus `parcel_id == 0` as a random parcel candidate, which confirms `Parcel` is live gameplay state rather than dead parser residue
- in the shipped corpus, ring-tagged segment files are isolated from `Path=` and `Parcel=` usage, which avoids the most obvious flag collisions
- `RingSpeed=` exists in parser code but is unused in shipped extracted segments
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

Current corpus notes:

- the extracted archive currently has `53` level files
- shipped `Mode:` values are `arcade`, `challenge`, and `tutorial`
- shipped `Flags:` appears as an empty marker in `52/53` files and is absent only in [`LEVELS/CHALLENGE000.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/CHALLENGE000.TXT)
- shipped `Track:` is missing only from [`LEVELS/ARCADE000.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/ARCADE000.TXT)
- shipped hazard-field spellings are mostly `Garbage:`, with lowercase `garbage:` in tutorial and challenge files, and legacy `Slug:` only in [`LEVELS/ARCADE000.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/ARCADE000.TXT) and [`LEVELS/ARCADE003.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/ARCADE003.TXT)
- shipped segment-entry metadata only uses three forms:
  - bare filename
  - `Angle=<degrees>`
  - tutorial-only `Duration=<seconds> Sample="<voice clip>" Message="<tutorial text>"`

Current tooling parser behavior:

- normalizes `Slug`, `Garbage`, and `garbage` into one `garbage` field
- preserves tutorial messages exactly, including in-string marker characters like `>` and `{`
- keeps per-segment metadata as structured attributes in addition to common convenience fields

Current RWG level-parser behavior:

- RWG uses the same `find_case_insensitive_substring` helper here as in the segment parser, so field matching is case-insensitive and prefix-friendly
- `Random:yes` sets a real random flag and enables a mandatory `Length:` integer; when `Random:yes` is absent, the runtime clears both the random flag and the stored length
- `Background:` is required and is resolved to a `.txt` asset handle, not kept as a raw filename string
- `Fringe:` parses three integer color components and normalizes them to `0..1` floats; if missing, RWG logs a warning and uses white
- `Track:` maps the first character to an internal track id:
  - `0`, `1`, `2`, `3` -> `0`, `1`, `2`, `3`
  - `r` -> `5`
  - missing -> `0` with a warning
- `Parcels:` and `Quota:` are required integers
- `Speed:select` maps to a stored `-1.0` sentinel
- plain `Speed:` stores a parsed float, and a missing speed falls back to `100.0` with a warning
- `Garbage:` and `Salt:` are optional floats that default to `-1.0`
- `Segments Begin:` entries are resolved through the already-parsed segment catalog and copied into per-level segment slots, not left as filename strings
- per-segment entry defaults in RWG are:
  - `Angle=` default `0` radians
  - `Duration=` default `4.0`
  - `Sample=` default `-1` when no voice clip is resolved
  - `Message=` default empty string
- `First:` and `Last:` also resolve named segment definitions and copy them into dedicated level slots
- `GalaxyText:` is extracted from the `{ ... }` block; if the block is missing or malformed, RWG substitutes literal fallback text such as `TEXT MISSING` or `TEXT ERROR } MISSING`
- no `Mode:` or `Flags:` probe has been recovered in the current `load_level_definition_file` path
- the only confirmed `Mode:*` text probes in current RWG are animation-side `Mode:Loop`, `Mode:Once`, and `Mode:Pingpong` inside `X/_Animation.txt`
- the only recovered hazard probe in the current level parser is `Garbage:`; lowercase `garbage:` still matches because lookup is case-insensitive, but no separate `Slug:` alias has been recovered yet

Current runtime use of parsed level fields:

- `Random:` and `Length:` feed the later track-build path and determine whether the course uses authored segment order or randomized composition to a target length
- `Track:` selects the active track texture set, and `Track:r` additionally randomizes the `Space*.txt` backdrop choice at level start
- `Garbage:` is normalized to a `0..1` runtime scalar and later gates calls into the garbage-hazard spawner, which uses `Sprites/GarbageA-D.tga`
- `Salt:` is normalized to a second `0..1` runtime scalar and later gates `spawn_salt_hazard`, which manages a live `40`-slot `salt.x` runtime pool
- deeper runtime notes for track build, path attachments, and level-field consumers now live in [`docs/reverse/path-system.md`](/Users/banteg/dev/banteg/snail-mail/docs/reverse/path-system.md)

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
