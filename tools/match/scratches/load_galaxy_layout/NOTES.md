# load_galaxy_layout @ 0x4088e0

First structural scratch for the galaxy route layout loader. The function rescales
the two authored point tables, loads `Galaxy/_Galaxy.txt`, copies galaxy names
and star counts into the route-name table, seeds placeholder level labels, and
initializes the first route record.

The loader now uses the shared `Galaxy`, `GalaxyRouteSlot`,
`GalaxyRouteRecord`, and `GalaxyRouteNameRecord` views established with the
constructor, route initializer, opener, updater, and closer.

The authored point banks are now owned as exact `GalaxyPoint { x, y }` arrays:

- ten galaxy-group anchors occupy `0x4a1c4c..0x4a1c9c`; native retains a
  cursor to each point's `y` field starting at `0x4a1c50` and compares the
  advanced cursor against `0x4a1ca0`;
- 101 route points occupy `0x4a1d14..0x4a203c`; route zero uses entry zero,
  generated missing-level slots consume entries one onward, and the rescale
  loop's `y`-field cursor stops at `0x4a2040`.

This replaces the old false split into an unrelated 0x50-byte route table plus
four scalar X/Y globals. The checked-in reference manifest now describes the
two complete banks and the group `y`-cursor sentinel.

Current retained result: 88.27%, 236 candidate instructions for 233 target
instructions, 62-instruction common prefix, and 39 clean / 0 unresolved / 0
mismatched masked operands. The source keeps literals as literals so the matcher
verifies the real `_Galaxy.txt` path, markers, errors, and missing-level string.

2026-06-20 local-order correction: passing literal zero to the `_Galaxy.txt`
load and declaring `star_group_offset` before `star_index` makes VC6 keep the
inner star index in `ebx` and the group offset on the stack, matching the
native ownership through the file-load setup. Rewriting the later null check or
the loop-tail finalization branch was neutral, so those spellings stay honest.

2026-06-21 cursor-spill retry: spelling the galaxy marker search as an
assignment inside the null-check condition is codegen-neutral at 78.37%. VC6
still stores the `find_case_insensitive_substring` result to the cursor local
before testing it, while native compares against zero before the spill.

2026-06-21 local-owner retry: swapping the declarations of `star_index` and
`star_group_offset`, comparing the marker cursor against `star_index` instead
of literal null, and adding a `star_count` temporary did not recover native's
`ebx` star-index lifetime. The declaration/compare forms are neutral at 78.37%,
while the `star_count` temporary grows the frame and regresses to 55.36% with
masked call mismatches. Keep the current local order.

2026-07-11 slot ownership correction:

- Constructor iteration starts at `Galaxy +0x10`, uses stride `0x2a0`,
  and covers 101 slots exactly through `+0x10930`.
- Each slot owns a four-byte prefix followed by a `0x29c` route record at
  `+0x04`; loader fields therefore remain at controller
  `+0x14/+0x1c/+0x20/+0x24/+0x30/+0xb0` for slot zero.
- Replacing 100 overlapping `0x2a0` records plus hidden padding with the real
  101-slot array preserves 78.37%, the 62-instruction prefix, and all 40 clean
  operands.

2026-07-11 authored parent: Android identifies this layout pass as
`cRGalaxy::Init2()`. Promoting the parent from the semantic `GalaxyRoute` name
to `Galaxy` and absorbing its native-ledger tail keeps the honest 78.37%,
234/233 result with all 40 operands clean.

2026-07-12 route-star loop ownership recovery:

- The per-galaxy star expansion does not need a separate positive-count guard:
  its direct `while (star_index < star_count)` naturally handles empty groups.
  Resetting `star_index` after that loop also applies to the empty case and is
  semantically equivalent to the older guarded `do/while` spelling.
- That simpler lifetime recovers native register ownership: `ebx` is the live
  star ordinal, `ebp` is the ten-unit placement step, and the outer
  `star_group_offset` remains spilled. The focused match rises from `78.37%`
  (`234/233`) to `84.26%` (`237/233`) with the 62-instruction prefix intact and
  39 clean operands.
- The retained `level_progress_base` backlink now explicitly borrows the
  root-owned `SubgameRuntime`; it is not a separately allocated progress
  table. Naming that owner is codegen-neutral.

2026-07-12 contract and cross-port split recovery:

- The sole Windows caller discards the result. The successful path reaches its
  epilogue without establishing `eax`, while the two error paths merely leave
  `report_errorf`'s incidental value. The authored contract is therefore
  `void`; removing the invented `dword_4a1d18[0]` return eliminates one
  candidate instruction.
- iOS `cRGalaxy::Open(int)` at `0x687c8` and Android
  `cRGalaxy::Open(int)` at `0x500b4` retain the same universe-point rescaling,
  `_Galaxy.txt`/`_GalaxyPro.txt` parsing, `Galaxy%i:` and `StarNumber=` keys,
  missing-level labels, route/star bank, and enclosing-subgame backlink. The
  mobile `cRGalaxy::Init2()` bodies initialize widgets instead; the previous
  Init2 provenance was stale.
- Windows split the mobile Open responsibilities: this startup member owns the
  parser/bootstrap, while exact `open_galaxy_route` owns the interactive card
  behavior retained on mobile as `cRGalaxy::BoxOn(int)`.
- Explicit parser error tails, native `record_count`-before-`star_index`
  advancement, and the point/index/group/widget-cursor update order improve the
  scratch from 84.26% (237/233) to 88.27% (236/233), preserving the
  62-instruction prefix and all 39 clean operands.
- A guarded inner `do/while` reached 234 candidate instructions but regressed
  register/dataflow agreement to 84.37%; a function-lifetime outer `do/while`
  duplicated the parser header and fell to 72.46%. Neither is retained.
- Binary Ninja previewed the void prototype correctly, removing all synthetic
  returns, but the live session rejected both persisted prototype spellings on
  readback and rolled them back. The checked-in source/header correction is
  retained; the database artifact remains honestly unsynchronized.

## 2026-07-13 point-bank ownership closure

Using the two exact `GalaxyPoint` owners while retaining native's interior
`y`-field cursor is codegen-neutral at 88.27%, 236/233 candidate/target
instructions, prefix 62/233, and 39 clean masked operands. A scoped marker
match temporary regressed to 87.85%, while direct terminal error returns
regressed to 86.14%; both were reverted. The retained out-of-line error tails
and cursor assignment remain the best evidence-backed Windows source shape.

## 2026-07-14 route-name cursor ownership

The retained interior cursor now starts at `route_names[0].color`, and every
backward/forward lane plus its record stride is derived with `offsetof` and
`sizeof(GalaxyRouteNameRecord)`. This removes the raw `route_names +0x84`,
`-33`-dword name recovery, and literal 40-dword stride while preserving the
native cursor lifetime. Focused Wibo remains byte-shape neutral at 88.27%,
236/233 instructions, prefix 62, with all 39 masked operands clean.

Binary Ninja independently shows `0x4a2040` as both the sole code-referenced
route-point y-cursor terminus and the start of a 25-byte string. A derived
`g_galaxy_route_points +0x32c` relocation is byte-identical but becomes
audit-ambiguous against that real string owner, so the overlapping terminal
literal is intentionally retained rather than inventing a second global.
