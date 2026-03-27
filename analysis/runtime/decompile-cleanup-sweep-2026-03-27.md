# Decompile Cleanup Sweep 2026-03-27

This pass intentionally parked the current `update_subgoldy` and `update_cameraman` hotspots and scanned for other decompile-cleanup targets across the tracked BN/IDA exports.

## Ranked targets

### 1. Frontend widget runtime slice

Completed in the follow-up widget typing pass.

Why:
- [`update_frontend_widget_interaction`](../decompile/binja/functions/00402820-update_frontend_widget_interaction.c) is still driving a large raw owner blob despite strong recovered semantics already present in the Zig port.
- [`initialize_frontend_widget`](../decompile/binja/functions/00401d30-initialize_frontend_widget.c) and [`update_tooltip`](../decompile/binja/functions/00403c20-update_tooltip.c) converge on the same state layout:
  - widget flags and previous flags
  - authored and live rects
  - hover/activation interpolation scalars
  - tooltip controller
  - shortcut key code
  - secondary child widgets used by the slider-style path

Observed payoff:
- `initialize_frontend_widget` now exposes the shared widget flags, color banks, render-inset fields, font/layout anchors, and slider child widgets through a checked-in widget type lane
- `update_tooltip` now cleanly reads against `FrontendWidgetTooltip*` with `state`, `mode_flags`, `delay_progress`, `delay_step`, `owner_widget`, and `tooltip_widget`
- the tracked BN/IDA exports for the five widget helpers are refreshed and no longer depend on ephemeral GUI typing

### 2. `parse_next_float32` prototype drift

Most interesting helper/prototype target.

Evidence:
- tracked BN currently reads [`parse_next_float32`](../decompile/binja/functions/00431f20-parse_next_float32.c) as `long double(char* arg1)`.
- previewed BN prototype correction to `float __cdecl parse_next_float32(char** cursor)` verifies cleanly and improves the helper body naming.
- live BN verification snaps back to the old signature, so this is not yet a safe committed mutation.
- the drift likely affects callers such as [`initialize_intro_screen`](../decompile/binja/functions/004191e0-initialize_intro_screen.c), where `parse_next_float32(...)` is still followed by x87 spill noise.

Current read:
- this is a real cleanup opportunity
- it needs a tool-aware fix, not just another repo-side header edit

### 3. Track fringe / render-cache owner typing

Best gameplay-render target outside the parked subgoldy work.

Hot files:
- [`build_track_fringe_mesh`](../decompile/binja/functions/004246a0-build_track_fringe_mesh.c)
- [`build_track_render_caches`](../decompile/binja/functions/00433220-build_track_render_caches.c)

Why:
- both still have high `__offset(...)` density
- the noise is concentrated in owner/runtime slabs, not just x87 arithmetic
- this looks like a missing typed owner slice rather than a missing symbol name

Expected payoff:
- improved readability for cache tile family routing
- cleaner link from path-template strip meshes into runtime render caches

### 4. Front-end controller wording that is already closed

Safe persistence/docs cleanup targets that should stay aligned with the tracked decompile:
- [`exit_high_score_screen`](../decompile/binja/functions/00417b50-exit_high_score_screen.c)
- [`open_star_field`](../decompile/binja/functions/004342c0-open_star_field.c)
- [`update_star_field`](../decompile/binja/functions/004346f0-update_star_field.c)
- [`update_row_event_display`](../decompile/binja/functions/00404cf0-update_row_event_display.c)

These are no longer blocked on missing native structure; they are mainly wording/ownership consistency work.

## Hotspot census

Tracked BN `__offset(` density outside the parked `update_subgoldy`/camera work is currently led by:
- `handle_subgoldy_collisions`
- `build_track_fringe_mesh`
- `build_track_render_caches`
- `build_track_fringe_supertramp_mesh`
- `update_track_attachment_follow_state`

Tracked BN `unimplemented` density outside the parked `update_subgoldy`/camera work is currently led by:
- `initialize_worm_path_template_pair`
- `explode_slug_hazard`
- `update_galaxy`
- `initialize_intro_screen`
- `populate_runtime_track_cells_from_segments`

The frontier split is therefore:
- widget/controller typing for front-end readability
- owner-slice typing for gameplay render/cache readability
- helper/prototype repair for parser-driven x87 callers

## Recommendation

Take the track fringe / render-cache owner slices next, with `parse_next_*` prototype cleanup as the helper-side follow-up.
