# initialize_warning @ 0x446e80

Exact match: 100.00%, 32/32 instructions.

This allocates the warning border, initializes sprite `0x5e` with frontend
sprite-button flag word `0x400802`, clears the warning field, hides the border,
and resets the progress state.

2026-06-16 type consolidation: the warning border now uses the shared
`FrontendWidget` view from `frontend_widget.h`; `warning_field` is the
confirmed +0x178 widget slot. This scratch remains exact.

2026-06-16 warning actor consolidation: the 16-byte controller now uses the
shared `WarningActor` view from `warning_actor.h`; the phase fields are
+0x04/+0x08 and the frontend border pointer is +0x0c. This scratch remains
exact.
