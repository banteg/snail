# Windows-first cross-port recovery

Windows is the sole primary matching target. Android, iPhone, and Wii supply
source leads; iPad is inventoried and deferred. Each executable/ABI has its own
identity. Existing Windows sources and the canonical matcher remain in place.

```sh
uv run snail ports --check
uv run snail match leads extract_snail_local_hotspots
uv run snail match leads initialize_quaternion_from_matrix --json
```

## Where evidence belongs

- [builds.json](builds.json): binary hashes, archive/slice selection, roles,
  compiler evidence, symbol indexes, and decompiler address conventions.
- [symbols/](symbols/): original mobile C++ names and link-time addresses tied
  to individual binary hashes. Unknown extents stay unknown.
- [functions.json](functions.json): additional explicit relationships and
  shared source constraints, keyed by the existing Windows function ID.
- [lineage-20260910/](lineage-20260910/README.md): raw-binary lineage, RTTI,
  complete-extent comparisons, and Android ABI diagnosis.
- Existing [mobile crosswalk](../symbols/windows-mobile-gameplay-crosswalk.json)
  and [corpora](../decompile/README.md): reused for their original Android ARMv7
  and iPhone 1.5 builds. A verified mapping is not silently transferred to a
  different release. The command labels those additions `same-symbol-only`.

The build check verifies all eight selected executable hashes, including each
individual iPhone 1.9 slice, and checks that symbol/corpus indexes refer to the
same build. It also validates additional Windows relationships and their
evidence files. `match leads` checks index identities and address rebasing;
it does not compile functions or award matching credit.

## Working on a Windows blocker

1. Capture a current Windows baseline with `snail match scratch` and `dump`.
2. Gather its leads with `snail match leads`. Confirm body correspondence in
   the selected releases; names alone are discovery evidence. Use native code
   to check questionable decompiler output and argument storage.
3. Record useful constraints in `functions.json`: expression grouping,
   comparisons, owner/inheritance, constants, and call relationships. Attach
   concrete listings/receipts. Record version differences alongside agreements.
4. Write plausible C++ and probe it with the existing Windows compiler profile.
   Keep offsets, layouts, ABI, and compiler settings specific to each build.
   A source mapping may be split, merged, or inlined; do not force one-to-one
   correspondence or common headers.
5. Promote only after native instructions, positional references, and complete
   byte accounting pass. Run the affected checks, update the Windows board,
   and commit the source and evidence together. Cross-port agreement itself
   adds no matching percentage.

New reference bodies/listings can be stored under a dated investigation in
this directory or an existing per-build corpus. Put compiler experiments and
their receipts under the existing `tools/match` workflow. A full Wii compiler
target can be added later when it answers a concrete source question.

## Refresh mobile names

From the repository root:

```sh
uv run analysis/ports/lineage-20260910/raw_inventory.py
uv run tools/ports/index_mobile_symbols.py --check
```

Omit `--check` to regenerate the compact indexes. The importer refuses an
inventory from a different binary hash. It does not infer function sizes from
neighboring symbols when the binary lacks an explicit size record.

Known limitations: the default Android Ghidra ABI misplaces `Sqrt(float)` in
s0; the native helper uses r0. m2c may omit paired-single stores. The detailed
reports retain controls for both issues. Independent code generators constrain
shared source, but neither decompiler consensus nor a matching name establishes
the original C++ or equality across game revisions.

## First result after organizing

The [hotspot extraction investigation](../../tools/match/hotspot-wii-normalization-20260910.md)
uses the mobile names to identify the routine and Wii's preserved count-and-normalize
operation to explain six Windows copy instructions. The recovered C++ matches
74/74 Windows instructions and all seven references, advancing coverage to
598/662. Its scoped relationship and source constraint are registered in
`functions.json` and displayed by `snail match leads extract_snail_local_hotspots`.
