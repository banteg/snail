# Exact match

`build_track_colours` @ 0x435d40 initializes the global track colour banks
used by the runtime track builder and render-cache refresh path.

The exact source shape has two useful idioms:

- `tColour::set_color_white` is a void mutator at callsites. Declaring it as a
  float-returning helper made VC6 pop the ignored x87 return after each call,
  which native does not do.
- The loop cursor is a byte offset across one 51-entry bank, advanced by one
  `tColour`. Those constants now derive from the declared bank extent and
  `sizeof(tColour)`; an element-index loop emitted the right calls but kept the
  wrong `inc/cmp` loop shape.

Native intentionally calls bank J twice and bank K twice for each slot. Keep
those duplicate mutator calls; removing either breaks the exact call sequence.

The CRT initializer at `0x4349c0` runs one 102-element constructor loop from
bank B through bank C. That independently proves these are two 51-entry views
of one contiguous `0x660`-byte allocation rather than unrelated globals; the
shared `track_colour_banks.h` now records that owner without changing this
function's exact instruction stream.

2026-06-21 subgame-header consolidation: the helper now uses
`SubgameRuntime::build_track_colours` instead of a scratch-local `Game` owner.
Focused Wibo remains exact at `100.00%`, `37/37` instructions, with `24` clean
masked operands.

2026-07-14 bank-extent ownership: both the loop bound and the B-to-C bank
boundary derive from `sizeof(g_track_colour_bank_a)`, while the byte cursor
step derives from `sizeof(tColour)`. The compiler retains the native byte-loop
shape, so the function remains exact at 37/37 with all 24 operands clean.
