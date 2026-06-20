# initialize_frontend_widget @ 0x401d30

Starter scratch for the shell-font front-end widget constructor.

Models list insertion, tooltip owner reset, border style presets 20-23, text
copy/layout anchors, highlight state, slider child creation, and the final
layout call. It uses the shared frontend widget header for the list prefix and
call surface, with raw offsets still used where the constructor's local
scheduling is not yet source-shaped.

Expected residuals:
- stack-local color ordering is still decompiler-shaped;
- color lane names and a few padding fields need cross-checking against
  `draw_frontend_widget` and `update_frontend_widget_interaction`;
- slider child calls are semantic but not scheduled to match.

2026-06-20 frontend type pass: `initialize_frontend_widget` and
`layout_frontend_widget` are modeled as returning the same word result, not a
widget pointer. This matches the exact `layout_frontend_widget` helper and the
exact `initialize_exit_prompt` branches that return the initializer result in
`eax`. Focused matcher evidence for this scratch stayed unchanged at `45.21%`,
`270/429` candidate/target instructions, with the same `38 ok / 1 unresolved /
1 mismatch` masked audit.

2026-06-20 shared frontend header pass: the local `FrontendWidget` list-prefix
view was removed in favor of `include/frontend_widget.h`. Focused matcher
evidence stayed unchanged at `45.21%`, `270/429` candidate/target
instructions, with the same `38 ok / 1 unresolved / 1 mismatch` masked audit.

2026-06-20 BorderManager ABI pass: the scratch now uses
`include/border_manager.h` for slider-child `allocate_border()` calls. The
shared allocator returns a `FrontendWidget*` view over `BorderRecord` storage,
so no local manager stub is needed. Focused matcher remains unchanged.

2026-06-20 constructor layout pass: focused matcher improved from `45.21%`
(`270/429`, `38 ok / 1 unresolved / 1 mismatch`) to `62.18%` (`433/429`,
`32 ok / 1 unresolved / 0 mismatch`). Accepted evidence-backed offsets:
`widget_type` stores at `+0x7c`, style font fields are `+0x6ec/+0x6f0`,
slider children are `more +0x71c`, `less +0x718`, and `value +0x720`, and the
constructor color lanes use `+0x1fc/+0x1cc` for the initial whites with style
presets flowing through `+0x1ec/+0x1fc/+0x1bc/+0x1cc`. Restoring the native
`0x104` color-temporary frame was the key source-shape change; making
`copy_color` inline before that frame rewrite regressed to `47.55%`, but after
the frame rewrite it improved the scratch to the final `62.18%`.
