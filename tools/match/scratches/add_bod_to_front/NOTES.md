# add_bod_to_front @ 0x4113b0

Out-of-line `BodList` front insertion used four times by the root asset/world
initializer. The receiver is consistently `GameRoot +0x5a8`; nodes include
input/runtime presentation objects, the tip manager, star field, and other
renderable bodies embedded in the same root owner.

The exact body confirms the existing intrusive layout: `BodList::first` at
`+0x04`, and `BodNode::list_flags/list_prev/list_next` at `+0x04/+0x08/+0x0c`.
`BOD_FLAG_LINKED` (`0x200`) is list ownership; duplicate insertion reports
`"List ADD"`.

## 2026-07-14 canonical list ownership

`BodListEndpointsView` represented no distinct allocation, base adjustment, or
lifetime. The exact receiver is the same `BodList` at `GameRoot +0x5a8` used by
inline insertion/removal and free-list recycling, so the method now belongs to
`BodList` directly. Focused output remains exact.

## 2026-07-18 analyzer ownership replay

Both analyzer databases now preserve the exact void method ABI on the complete
`BodList*` receiver and `BodNode*` argument. Replay is gated on the proven
`0x0c` list and `0x10` node extents before it can rename or type the helper.

## 2026-08-12 authored template ownership

Android retains one exported `cLinkedList<cRBod>::Add(cRBod&)` body at
`0x3f638`. It independently proves every semantic feature of this exact
Windows helper: the `List ADD` duplicate-owner diagnostic, linked bit `0x200`,
list head at `+0x04`, BOD links at `+0x08/+0x0c`, and the same empty/non-empty
head splice. The Android compiler sets the ownership bit before the splice
while VC6 sets it afterward; that scheduling difference does not change the
void operation or its error path.

The Android body lies in the recorded `Game.o` interval from `cRInput::Init()`
through `cROverlay::AI()`. Live Windows xrefs show exactly four calls, all from
`initialize_game_assets_and_world`. The mobile reference argument and Windows
pointer argument use the same address ABI, so the matcher keeps its stable
`BodList`/`BodNode*` spelling while recording the authored template owner.
There is no corresponding iOS body, and `append_bod_to_end` remains separate:
its `List ADDend` traversal has no exported mobile equivalent.
