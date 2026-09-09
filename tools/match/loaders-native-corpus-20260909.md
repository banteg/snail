# Loader behavior against original code, 2026-09-09

The recovered segment importer, level-file loader and segment-slot copier agree
with their original Windows routines on every shipped segment and level file.
The test compares complete parsed objects and resource-request logs, not fuzzy
instruction scores. No parser correction or additional exact function results
from this pass. The [tracked receipt](loaders-native-corpus-20260909.json)
records the input identities, coverage and results.

## Shipped corpus

The test decodes the local `SnailMail.dat` archive without changing its member
bytes or enumeration order. It contains **133 segment files**, representing
**9,570 authored rows**, and **53 level files**, producing **1,050 ordinary
level slots** in one pass, plus each level's first/last segments.

Each level runs with zero and `0xa5` initial object memory, and with galaxy
metadata enabled and disabled: **212 level executions per executable**. There
are four executables: all recovered source, then three controls replacing one
loader at a time with its original machine code. Both catalog imports and all
212 level outputs agree in every control. All file, model, path, landscape,
sound, error/warning and current-level-name events agree as well.

`ARCADE000.TXT` has no `Track:` field. Both implementations report the same
fallback to track zero, accounting for the four diagnostics in each complete
shipped-corpus run. That diagnostic is observed original behavior, not a harness
failure or a silently skipped fixture.

## Controlled inputs

An optional synthetic segment and three synthetic level files exercise behavior
not covered by the shipped corpus alone:

- model position and velocity, parcel position, combined row flags, and path
  name resolution;
- explicit ring speed and the existing `+2.5 -> 0` float-parser quirk;
- message text, duration, sample name, angle, automatic length and selected speed;
- missing optional fields and a missing `Segments End:` marker.

With these controls, all four executables complete **224 level executions** and
produce identical object bytes and event logs. There are 20 expected diagnostics
per run. Independent assertions check the synthetic row flags, velocity and
ring-speed values, in addition to comparing with the original routines.

## Compared state

The comparison covers the entire `cRSMTracks` catalog, each complete
`cRSubTracks` object, and the complete `cRGalaxy` metadata owner. It includes
inactive arrays, padding and fields left at their initial values. Nonzero
initial memory distinguishes omitted writes from explicit zero initialization.

`SubSegment::source_name` borrows a filename inside the catalog. These pointers
are serialized as catalog-relative offsets; other bytes remain unchanged.
Outputs use a lossless sparse representation relative to each fixture's fill
byte. The decoder reconstructs every region byte and rejects invalid extents,
overlapping spans and truncated data. Comparisons use reconstructed bytes,
not only hashes. The shipped run covers 426 regions; the controlled run covers
450. The tool also checks the complete ordered region list and every catalog
entry's filename and row count.

The source-only corruption control flips one byte of the first serialized
catalog ID, then restores the live catalog before any consumer runs. It must
produce exactly one differing byte at catalog offset `0x84`, in exactly one
region, with an unchanged event log. Both corpus modes reject that control.

## Native-code and source integrity

| Routine | Native address | Body bytes | Relocated native operands | Source match |
| --- | --- | ---: | ---: | ---: |
| Segment importer | `0x448160` | 1,937 | 91 | 68.44% |
| Level-file loader | `0x447480` | 3,039 | 183 | 88.12% |
| Segment-slot copier | `0x447300` | 379 | 5 | 100% |

The existing oracle extractor verifies the original image, copies constants
from that image, rejects unrelocated image addresses, and round-trips each
oracle through the matcher at 100%. The linked native body, each relocation
and copied constant are checked again. Recovered source functions are also
verified against their linked instruction bytes and relocation destinations.
All eight shared parsing/color helpers must be proof-grade exact.

The level source has two candidate-only unaudited instructions. A new explicit
oracle option records and omits only entries with no native index, offset or
reference. It does not permit any unaudited native address, mismatch or
unresolved target. The default remains strict. Tests cover the opt-in boundary
and reject attempts to remove native reference debt. The source's matching
status and its two unaudited entries remain unchanged.

## Scope

These are isolated original-routine executions under Wibo, not the original
game process. Both sides share the exact recovered text helpers and harness
CRT. File callbacks supply the decoded bytes with a deterministic zero tail;
the original archive reader does not itself append that terminator. Therefore
this test does not validate archive IO or arbitrary uninitialized input tails.

Model, landscape and sound loading stop at logged harness callbacks returning
deterministic identifiers. Path resolution uses the original image's 51 populated
table slots. The harness does not claim to validate resource loading, rendering,
sound availability, constructor lifetimes or malformed inputs beyond the stated
controls. It contains explicit ABI bridges for historical C++ declarations of
`sprintf`, file loading and the error reporter. No original executable code or
shipped asset payload is added to the source tree, and no linked-game or new
native matching credit is awarded.

## Reproduction and validation

```sh
uv run tools/match/compare_loaders_native.py \
  --runtime-library /path/to/vc6/vc98/lib/msvcrt.lib \
  --out artifacts/match/loader-comparison
uv run tools/match/compare_loaders_native.py --include-synthetic \
  --runtime-library /path/to/vc6/vc98/lib/msvcrt.lib \
  --out artifacts/match/loader-controls
```

The archive defaults to `artifacts/bin/SnailMail.dat`; `--archive` selects a
different local archive. Detailed fixtures, executables, maps, traces and
receipts stay under ignored `artifacts/`. The full Python suite passes **911
tests**, including 16 new oracle/serialization integrity cases. Ruff, native
status, strict experiment/spec checks and whitespace checks pass. The port
board remains **593/662 exact functions**.
