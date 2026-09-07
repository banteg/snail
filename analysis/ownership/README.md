# Native library and ownership attribution

The 2026-09-08 pass identifies **248,394 of the 287,268 code bytes previously
outside Game & Engine** as library code. Five omitted no-op startup initializers
add another **30 bytes** to Game & Engine. **38,844 bytes remain unclassified**.
These are the existing public inventory's disjoint owned bytes, not sums of
possibly overlapping analyzer bodies or archive symbol extents.

| Public category | Function owners | Owned code bytes |
| --- | ---: | ---: |
| Game & Engine | 787 | 309,585 |
| D3DX8 | 685 | 170,078 |
| MSVC runtime | 181 | 22,829 |
| Standalone libpng 1.2.5 | 125 | 39,360 |
| Standalone zlib 1.2.1 | 37 | 16,127 |
| Unclassified | 446 functions + 5 unassigned units | 38,844 |
| Full executable | 2,261 functions + 5 unassigned units | 596,823 |

The identity map contains 1,036 native functions: 1,031 library identities and
five startup wrappers. Three D3DX function bodies have no separate public owner
because the existing disjoint partition assigns their shared bytes elsewhere.
**1,002 placeholder names were replaced in the live Snail Mail Binary Ninja
database**, with provenance comments, verified readback and a saved snapshot.
The other existing meaningful names were preserved. No prototypes were changed.

## What was found

- **DirectX 8.1's D3DX8 static library** accounts for most of the former unknown
  region. Its identifiable members include texture/image loading, pixel codecs,
  blitting, scalar/SSE/3DNow math, and embedded PNG, zlib and IJG JPEG code.
- **There are two PNG/zlib families.** D3DX8's namespaced copy has the older
  PNG 1.0.5 / zlib 1.1.3 version leads. The game's `load_png_image` uses separate
  libpng 1.2.5 / zlib 1.2.1 code. Whole-body candidates and relocation targets
  distinguish them; a few routines have identical bodies across versions.
- **MSVC runtime identities** were established against a pinned VC6 SP6
  `libcmt.lib`. This proves compatibility of individual function bodies, not
  that SP6 was necessarily the game's original runtime release: unchanged
  functions can occur in multiple releases. Startup, exception, formatting,
  allocation and floating-point support explain many non-game callees.
- **No substantial missed game subsystem was found in this pass.** Across the
  three-analyzer union, the uncurated entries before the D3DX8 cluster consist
  of five no-op initializer pairs and three padding-only starts. The known
  game's outward call graph leads into the identified library/runtime families.
  This does not prove that all residual code or indirect callbacks have been
  understood.

The initializer thunks at `0x40a190`, `0x411490`, `0x4119a0`, `0x411da0` and
`0x411dc0` each jump to a bare return. Slots 4, 6, 7, 8 and 9 in the C++ initializer
array beginning at `0x4a1000` reference them, alongside the already curated game
initializers. Their names describe that verified role; their original object
owners remain unknown. The separate IDA return entries do not add bytes twice.
The NOP-only starts `0x410bf8`, `0x43a2f8` and `0x43d228` remain excluded alignment;
they were not promoted, deleted or given invented semantic owners.

## Evidence and acceptance

`library-attribution.json` records target/body hashes, archived or compiled
symbols, compatible COFF members, consistent references, and unresolved
references. It is an identity map, **not a matching-progress attestation**.
`remaining-code.json` retains every unclassified public unit, including
ambiguous body candidates and named incoming-reference hints for further work.
Three recognizable import thunks (`Direct3DCreate8`, `DirectInput8Create`,
`RtlUnwind`) remain in that ungrouped remainder.

The probe compares the complete BN function extent against complete COFF
functions, requiring equality of every byte other than recorded relocation
slots. It eliminates candidates contradicted by available function-symbol,
import or immutable-data evidence. A unique body of at least 32 bytes, or a
unique body with a consistent reference, can seed attribution. Smaller or
ambiguous bodies require a named reference from an accepted body or the
independently reviewed PNG initialization anchor. Conflicting/folded identities
remain unresolved. The cluster ranges only restrict candidate eligibility;
functions are never attributed merely because their addresses fall inside one.

The PNG `png_create_read_struct_2` anchor at `0x47d91e` was independently checked
against `pngread.c`: allocation with memory callbacks, version diagnostics,
PNG allocator installation, `inflateInit` with version 1.2.1 and a 56-byte stream,
read callback installation and the final setjmp. That sequence also resolves
otherwise ambiguous small helper candidates.

Reference consistency is weaker than a completed reference audit. Unresolved
references are explicit, and a compatible archive member is not automatically
the proven original source object. Nine identities retain more than one
compatible member. Repeated static names and shared/folded implementations must
not be used to invent object ownership. There is no transfer of archive or
reference-source scores into the public matched/fuzzy/linked measures.

The inspected residuals include vectorized D3DX functions, runtime exception and
stdio internals, small ambiguous helpers and analyzer-boundary cases. Named
incoming references give useful next targets—for example the large
`x3d_D3DXQuaternionSquadSetup` candidate at `0x4689b1`—but were not enough alone
to rename those functions. Data/BSS reconstruction, complete global ownership,
and integrated linking remain separate gaps.

## Sources and reproduction

The Microsoft archives are the same hash-pinned inputs already used by Crimson:

- [DirectX 8.1 SDK, archived Microsoft download](https://web.archive.org/web/20040108202259id_/http://download.microsoft.com/download/whistler/dx/8.1/W982KMeXP/EN-US/DX81SDK_FULL.exe),
  member `DXF/DXSDK/lib/d3dx8.lib`, SHA-256
  `39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`.
- [Visual C++ 6 SP6 media](https://archive.org/download/vs6.iso/vs6sp6.iso.zip),
  member `vs6sp6.iso/VS6sp61.cab/vc98/lib/libcmt.lib`, SHA-256
  `a541c95e5ffdd6d5573d1976f5e5d0038f2c4fb0bcb02975c68948bf1d6e452a`.
- Official [libpng v1.2.5](https://github.com/pnggroup/libpng/tree/v1.2.5) and
  [zlib v1.2.1](https://github.com/madler/zlib/tree/v1.2.1) source tags.
  Their downloaded archive hashes are in the identity map.

`reference-build.json` pins all C/header inputs, compiler-bundle files, Wibo,
flags and resulting objects. The historical sources were built with the
repository's `msvc6.5` bundle under `/O1 /MD`, `/O2 /MD` and `/O1 /MT`; `/O1`
produced the useful matches. No proprietary archives, game bytes or compiled
objects are committed here.

With extracted source tags in a temporary directory and the sibling Crimson
checkout's pinned provider archives and environment available:

```sh
uv run tools/ownership/build_reference_sources.py /path/to/source-root
uv run --no-project --python ../crimson/.venv/bin/python \
  tools/ownership/probe_libraries.py /path/to/source-root
uv run tools/ownership/resolve_candidates.py
bn --target SnailMail_unwrapped.exe.bndb py \
  --script tools/binja/export_ownership_context.py --format json
uv run tools/ownership/write_attribution.py \
  --demangled artifacts/ownership/demangled.json --source-root /path/to/source-root
uv run tools/ownership/summarize_remaining.py
```

The probe deliberately reuses Crimson's COFF reader and records its exact source
hashes. Raw candidates, rejected alternatives, native inspection bundles and the
BN update receipt live under ignored `artifacts/ownership/`. The committed
identity map is the reviewed result; new candidates still require review before
names are applied. `write_attribution.py` rebuilds that map using a BN demangling
export, the saved initial call graph and the explicit native anchors.

To preview the reviewed map against the live DB:

```sh
bn --target SnailMail_unwrapped.exe.bndb py \
  --script tools/binja/sync_library_attribution.py --format json
```

The sync script verifies every live body hash and existing name before editing,
uses one undo transaction, preserves comments, and verifies all changes before
saving a snapshot. An explicit `APPLY=True` in the `bn py` scope applies it.

Public report categories consume only the committed identity map; the original
native inventory remains the historical denominator evidence. The map and
reference-build attestation are pinned by `snail match report --refresh` and CI.
The default **All** view and full-executable matching totals remain unchanged.
