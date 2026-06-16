# initialize_warning @ 0x446e80

Exact match: 100.00%, 32/32 instructions.

This allocates the warning border, initializes sprite `0x5e` with frontend
sprite-button flag word `0x400802`, clears the warning field, hides the border,
and resets the progress state.

2026-06-16 type consolidation: the warning border now uses the shared
`FrontendWidget` view from `frontend_widget.h`; `warning_field` is the
confirmed +0x178 widget slot. This scratch remains exact.
