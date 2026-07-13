# launch_alpha72_url @ 0x433050

Tiny completion-screen outbound-link adapter. Its sole caller pushes the
`"Alpha72.url"` resource path, but this stripped body does not read the
argument: it calls `minimize_game_window` and raises
`g_pending_window_deactivate` at `0x4df860`.

The latch is owned by the process window lifecycle: initialization clears it,
and `handle_game_window_deactivate` consumes it after any fullscreen pause/hide
work. The function is `void`; its apparent return is the minimize helper's
live `EAX`, which the caller ignores.
