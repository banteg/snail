# load_galaxy_layout @ 0x4088e0

First structural scratch for the galaxy route layout loader. The function rescales
the two authored point tables, loads `Galaxy/_Galaxy.txt`, copies galaxy names
and star counts into the route-name table, seeds placeholder level labels, and
initializes the first route record.

The loader now uses the shared `Galaxy`, `GalaxyRouteSlot`,
`GalaxyRouteRecord`, and `GalaxyRouteNameRecord` views established with the
constructor, route initializer, opener, updater, and closer.

The authored route-point table at `0x4a1c50` is named as
`g_galaxy_route_point_table` with the one-past sentinel
`g_galaxy_route_point_table_end` at `0x4a1ca0`.

Current retained result: 84.26%, 237 candidate instructions for 233 target
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
