# initialize_thanks_for_playing_screen @ 0x433fd0

Initializes the thanks screen by hiding the shared star field, loading the intro
text music/backdrop, allocating the centered message widget, and resetting the
screen fade/timer fields.

Exact match: 100.00%, 55/55 instructions, 17/17 masked references resolved.

The post-widget write uses `FrontendWidget::font_scale` at `+0x6f0`; the same
field is populated by the galaxy screen's title and description widgets.

2026-07-13 root-owner cleanup: the star field, landscape bank, backdrop,
border pool, and message allocation now use canonical `GameRoot` members. The
screen-local `ThanksBorderManager` pseudo-type is removed; exact output remains
55/55 with all 17 operands clean.

2026-07-14 widget-field ownership: the final message scale write now names the
shared `FrontendWidget::font_scale` field rather than repeating its byte offset.

2026-07-18 live-analysis lifecycle pass: the exact void
`ThanksScreen*` receiver is now durable in both databases. The export resolves
the Splash record through `SubgameRuntime::landscape_manager.scripts`, then
owns the allocated `message_widget`, its `font_scale`, and all three initial
state/timer stores directly. The focused Binary Ninja replay checks the full
0x14-byte owner and all three ThanksScreen method ABIs.
