# draw_split_backdrop

- `draw_split_backdrop @ 0x410f90` queues two axis-aligned quads using
  `active_primary_texture_id` and `active_secondary_texture_id`.
- The second quad starts at x=512 and is 128 pixels wide, so this path is for
  the script-level split backdrop pair rather than the normal distorted 7x7
  grid renderer.

## 2026-07-17 receiver ownership

Binary Ninja now preserves the explicit `Backdrop*` thiscall receiver and
names both active texture ids through the enclosing controller. The Windows
`int32_t` tail result remains intact because `update_backdrop` can propagate
the second queue call's EAX; this slice does not infer a void contract from
discarding callers. The matcher remains exact at 50/50 instructions with four
clean operands.
