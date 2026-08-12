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

2026-07-18 live-analysis lifecycle pass: the exact void screen-controller
receiver is now durable in both databases. The export resolves
the Splash record through `cRSubGame::landscape_manager.scripts`, then
owns the allocated `message_widget`, its `font_scale`, and all three initial
state/timer stores directly.

2026-08-12 cRSplash ownership recovery: Android `cRSplash::Init()` at
`0x6aba4` and iOS `cRSplash::Init()` at `0x63b8c` reproduce the complete
Windows lifecycle: hide the star field, start `INTROTEXT.OGG`, load the Splash
landscape (or full-version SplashPro variant), change the backdrop, center and
allocate the message widget, set its font scale to 1.2, and seed the message
state/progress fields. The iOS STABS catalog assigns the authored class to
`Splash.o`. Mobile's leading exit flag makes its owner 0x18 bytes with the game
link at +0x04; the exact Windows owner remains its independently recovered
0x14-byte layout with the game link at +0x00.
