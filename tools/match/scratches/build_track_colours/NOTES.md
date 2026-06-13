# Exact match

`build_track_colours` @ 0x435d40 initializes the global track colour banks
used by the runtime track builder and render-cache refresh path.

The exact source shape has two useful idioms:

- `Color4f::set_color_white` is a void mutator at callsites. Declaring it as a
  float-returning helper made VC6 pop the ignored x87 return after each call,
  which native does not do.
- The loop cursor is a byte offset from `0` to `0x330`, advanced by `0x10`.
  An element-index loop emitted the right calls but kept the wrong `inc/cmp`
  loop shape.

Native intentionally calls bank J twice and bank K twice for each slot. Keep
those duplicate mutator calls; removing either breaks the exact call sequence.
