# promote_track_tiles_to_fringe_variants

- Promotes runtime track-cell BOD objects to fringe variants when the same-lane
  cell in the next row is open.
- Current retained shape is 81.33%: same instruction count as native, same
  frame/register loop skeleton, 6 clean masked operands, no unresolved operands.
- Native keeps its row cursor at `TrackRowCell +0x24` (`BodBase::object`) and
  accesses flags at cursor `+0x1c`; the retained source uses the shared
  `TrackRowCell*` cursor because that recovers the native stack/register
  allocation. The remaining diffs are the expected `+0x24` base displacement
  shifts.
- A raw object-slot cursor recovered the native `esi = this + 0x3bfaec` base,
  but VC6 hoisted `cell_marker - 0x24` into `ebx`, spilled the lane counter,
  and fell to 66.67%. `register`, integer-cast, inline-helper, and
  marker-struct variants produced the same hoist and were rejected.
