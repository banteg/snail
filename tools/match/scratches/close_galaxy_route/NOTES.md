# close_galaxy_route

`close_galaxy_route` @ 0x409bf0 tears down a galaxy-route selection: it clears
the route-state word at `+0x08`, resets the selected-index sentinel at
`+0x10f80` to `-1`, and reinitializes the six cached `FrontendWidget` border
slots at `+0x10f8c..+0x10fa0` via `FrontendWidget::hide_border_init`
(@ 0x4010e0).

Match status: 100%, 18/18 target instructions, 6 clean masked operands (the six
`hide_border_init` calls). The six border calls are spelled explicitly rather
than as a loop so VC6 emits the native unrolled `mov ecx, [esi+off]; call`
sequence; a `for` loop lowers to a counted loop with a cursor and does not
match. The two field clears precede the calls in source; VC6 hoists the first
`borders[0]` load above them exactly as native does.

Type layout recovered for this call: `+0x08` route-state word, `+0x10f80`
selected index with a `-1` sentinel, `+0x10f8c` a six-entry `FrontendWidget*`
border array. The parent now uses the shared `GalaxyRoute` header also used by
`open_galaxy_route` (@ 0x409c50) and `update_galaxy` (@ 0x4092f0).
