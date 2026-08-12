# append_bod_to_end @ 0x411420

Out-of-line tail insertion on the same `BodList` owner at `GameRoot +0x5a8`.
The root initializer uses it for the border/UI node at `GameRoot +0xb4c`, while
other startup nodes are inserted at the front by `add_bod_to_front`.

The function walks `list_next` to the tail, installs both directional links,
clears the new tail's `list_next`, and marks `list_flags & 0x200`. Duplicate
ownership reports the distinct `"List ADDend"` diagnostic.

The source now spells that membership bit as `BOD_FLAG_LINKED`; focused output
remains exact at 33/33 instructions.

## 2026-07-14 canonical list ownership

The tail insertion is another operation on the complete root-owned `BodList`,
not a method of a derived endpoint shell. Moving it onto `BodList` removes the
cast-only `BodListEndpointsView` without changing receiver identity or object
extent. Focused output remains exact.

## 2026-07-18 analyzer ownership replay

The canonical analyzer ABI is now `void __thiscall(BodList*, BodNode*)`, shared
with the front insertion helper rather than a synthetic tail view. The replay
fails closed unless the complete list and intrusive-node sizes remain exact.

## 2026-08-12 dual-mobile inline provenance

Android and iOS independently inline this complete tail insertion inside
`cRGame::Init4()`. Both bodies test linked bit `0x200`, use the root list head,
walk `list_next` until null, install the new node's backward link, clear its
forward link, set ownership, and report the distinctive `List ADDend` error.
The iOS symbol is directly assigned to `Game.o`; the Android body lies inside
the independently bounded Game.o symbol run.

Live Windows xrefs show one call, from `initialize_game_assets_and_world`, on
the same root cRGame list. The helper also ends immediately before the desktop
Direct3D allocation block. Together these facts recover its Windows `Game.o`
emission unit. They do not justify mapping the helper to the much larger
mobile Init4 body or guessing an unexported template method name, so the
crosswalk remains unverified and records only
`dual-mobile-inline-source-object` provenance.
