# Exact match

`build_track_colours` @ 0x435d40 initializes the global track colour banks
used by the runtime track builder and render-cache refresh path. Android and
iOS identify the authored member as `cRSubGame::BuildColours()` and preserve
the ten original global names.

The shared 13-call order recovers the Windows owners without guessing:

| Call | Windows owner | Mobile owner |
| ---: | --- | --- |
| 1 | `g_loc_colour_lookup_check_black` | `gLocColourLookupCheckBlack` |
| 2 | `g_loc_colour_lookup_floor_slide_0.floor` | `gLocColourLookupFloor` |
| 3 | `g_loc_colour_lookup_floor_slide_0.slide_0` | `gLocColourLookupSlide` |
| 4 | `g_loc_colour_lookup_slide_1` | `gLocColourLookupSlide` |
| 5 | `g_loc_colour_lookup_wall` | `gLocColourLookupWall` |
| 6 | `g_loc_colour_lookup_trampoline` | `gLocColourLookupTrampoline` |
| 7 | `g_loc_colour_lookup_ramp` | `gLocColourLookupRamp` |
| 8 | `g_loc_colour_lookup_empty` | `gLocColourLookupEmpty` |
| 9 | `g_loc_colour_lookup_path` | `gLocColourLookupPath` |
| 10-11 | `g_loc_colour_lookup_path_worm` | `gLocColourLookupPathWorm` |
| 12-13 | `g_loc_colour_lookup_path_warp` | `gLocColourLookupPathWarp` |

Android and iOS use 53-entry (`0x350`-byte) banks and alias calls 3 and 4 to
one physical `gLocColourLookupSlide` owner. Windows uses 51-entry (`0x330`-byte)
banks and has distinct storage for those two calls. The matcher therefore
records the semantic relationship while preserving both Windows addresses; it
does not collapse the platform-specific split.

The exact source shape has two useful idioms:

- `tColour::set_color_white` is a void mutator at callsites. Declaring it as a
  float-returning helper made VC6 pop the ignored x87 return after each call,
  which native does not do.
- The loop cursor is a byte offset across one 51-entry bank, advanced by one
  `tColour`. Those constants now derive from the declared bank extent and
  `sizeof(tColour)`; an element-index loop emitted the right calls but kept the
  wrong `inc/cmp` loop shape.

Native intentionally calls PathWorm twice and PathWarp twice for each slot.
Keep those duplicate mutator calls; the mobile ports independently preserve the
same duplicates, and removing either breaks the exact Windows call sequence.

The CRT initializer at `0x4349c0` runs one 102-element constructor loop from
Floor through Slide-0. That independently proves these are two 51-entry views
of one contiguous `0x660`-byte allocation rather than unrelated globals; the
shared `track_colour_banks.h` records that owner without changing this
function's exact instruction stream.

2026-06-21 subgame-header consolidation: the helper now uses
`SubgameRuntime::build_track_colours` instead of a scratch-local `Game` owner.
Focused Wibo remains exact at `100.00%`, `37/37` instructions, with `24` clean
masked operands.

2026-07-14 bank-extent ownership: both the loop bound and the Floor-to-Slide-0
boundary derive from `sizeof(g_loc_colour_lookup_check_black)`, while the byte
cursor step derives from `sizeof(tColour)`. The compiler retains the native
byte-loop shape, so the function remains exact at 37/37 with all 24 operands
clean.

2026-07-16 cross-port global recovery: the anonymous A-K storage names were
replaced with the ownership mapping above. All ten CRT constructor bodies remain
exact at 12/12 instructions, and this member remains exact at 37/37 with all 24
masked operands clean.
