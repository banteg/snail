# update_border_manager @ 0x403fc0

Consumes the delayed frontend-widget flag lane armed by
`queue_frontend_widget_flag_after_delay`. While active, it advances the progress
timer by the fixed step, clamps progress to `1.0f` after expiry, and ORs the
queued flag mask into the target widget once either the widget does not require
the frontend fade bit or the shared fade state at `g_game_base + 0x24` has
reached state `4`.

Focused match: 100%, 28/28 instructions, with two clean masked operands.
