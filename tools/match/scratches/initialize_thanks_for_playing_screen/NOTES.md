# initialize_thanks_for_playing_screen @ 0x433fd0

Initializes the thanks screen by hiding the shared star field, loading the intro
text music/backdrop, allocating the centered message widget, and resetting the
screen fade/timer fields.

Exact match: 100.00%, 55/55 instructions, 17/17 masked references resolved.

The post-widget write at `message_widget + 0x6f0` is not named in the shared
`FrontendWidget` header yet; keep it as a raw recovered slot until another
frontend widget path proves the field semantics.

2026-07-13 root-owner cleanup: the star field, landscape bank, backdrop,
border pool, and message allocation now use canonical `GameRoot` members. The
screen-local `ThanksBorderManager` pseudo-type is removed; exact output remains
55/55 with all 17 operands clean.
