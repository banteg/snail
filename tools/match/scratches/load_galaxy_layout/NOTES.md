# load_galaxy_layout @ 0x4088e0

First structural scratch for the galaxy route layout loader. The function rescales
the two authored point tables, loads `Galaxy/_Galaxy.txt`, copies galaxy names
and star counts into the route-name table, seeds placeholder level labels, and
initializes the first route record.

The loader now uses the shared `GalaxyRoute`, `GalaxyRouteSlot`,
`GalaxyRouteRecord`, and `GalaxyRouteNameRecord` views established with the
constructor, route initializer, opener, updater, and closer.

The authored route-point table at `0x4a1c50` is named as
`g_galaxy_route_point_table` with the one-past sentinel
`g_galaxy_route_point_table_end` at `0x4a1ca0`.

Current retained result: 78.37%, 234 candidate instructions for 233 target
instructions, 62-instruction common prefix, and 40 clean / 0 unresolved / 0
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

- Constructor iteration starts at `GalaxyRoute +0x10`, uses stride `0x2a0`,
  and covers 101 slots exactly through `+0x10930`.
- Each slot owns a four-byte prefix followed by a `0x29c` route record at
  `+0x04`; loader fields therefore remain at controller
  `+0x14/+0x1c/+0x20/+0x24/+0x30/+0xb0` for slot zero.
- Replacing 100 overlapping `0x2a0` records plus hidden padding with the real
  101-slot array preserves 78.37%, the 62-instruction prefix, and all 40 clean
  operands.
