# update_border_manager @ 0x403fc0

Consumes the delayed frontend-widget flag lane armed by
`queue_frontend_widget_flag_after_delay`. While active, it advances the progress
timer by the fixed step, clamps progress to `1.0f` after expiry, and ORs the
queued flag mask into the target widget once either the widget does not require
the frontend fade bit or the root-owned `GameRoot::fade.state` has
reached state `4`.

Focused match: 100%, 28/28 instructions, with two clean masked operands.

2026-07-12 ownership closure: the former sparse delayed-lane view is absorbed
into `BorderManager`. This exact member and its exact arming helper jointly
prove the post-pool tail through `+0x435af`; the following center-justify
scalar closes the manager at `+0x435b4`.

2026-07-14 root-client consolidation: the transition gate now names
`GameRoot::fade.state` instead of reconstructing the root +0x24 owner. Focused
matching remains exact at 28/28 instructions with two clean operands.
