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
