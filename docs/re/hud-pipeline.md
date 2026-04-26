# Gameplay HUD Pipeline

Native HUD element inventory for the `.level` phase, recovered from
`initialize_subgame`, `update_subgoldy`, `update_damage_gauge`,
`update_progress_bar`, and the sprite registry in
`initialize_game_assets_and_world`.

All coordinates are authored 640×480.

## Widget-backed HUD (frontend widget system)

Allocated once in `initialize_subgame` (0x4374b0). Shown/hidden per frame.
Stored on `Game` at fixed offsets.

| Storage | Ctor | Params | Mode gating | Semantics |
|---|---|---|---|---|
| `game+0x35bb88` | `initialize_frontend_widget` | widget_type=0x14, text="0", x=400, y=14, align=right(3), anchor_x=300 | shown in Postal/Challenge/Time Trial; hidden in Tutorial and transitional modes 2/3 | **Current score** text, top-right |
| `game+0x35bb8c` | `initialize_frontend_widget` | widget_type=0x14, text="0", x=40, y=14, align=right(3), anchor_x=-71 | shown in Postal/Challenge/Time Trial with per-mode content; hidden in Tutorial and transitional modes 2/3 | **Reference best score** (Postal best / Time Trial best / Challenge best) — top-left |
| `game+0x35bb90` | `initialize_frontend_sprite_button` | sprite=0x7a (`Sprites/ParcelIcon.tga`), x=0, y=58 | created only in Postal (`level_mode == 0`), initially hidden | **Parcel icon** (32×64 sprite) |
| `game+0x35bb94` | `initialize_frontend_widget` | widget_type=0x14, text="0", x=47, y=80, align=absolute(0) | created only in Postal, initially hidden | **Parcel count** number |
| `game+0x35bb98 … +0x35bbbc` (9 slots) | `initialize_frontend_sprite_button` | sprite=0x7b (`Sprites/Life.tga`), x=13+i·24, y=430 | created only in Postal; shown up to `visible_life_stock`, driven by `show_subgoldy_lives` | **Life eggs** (32×32 each) |

`widget_type=0x14` (20) is the menu_button shell. For Postal the score widget
starts with `border_add_text_number(widget_A, 0)` (live score) and the
reference widget starts with `border_add_text_number(widget_D, best_score)`.
For Time Trial (`level_mode == 4`), widget D is fed by `format_time_trial_string`.

`show_subgoldy_lives` (0x43af10) iterates the 9 Postal life slots at
`game+0x35bb98..+0x35bbbc` and toggles the `0x10` hidden bit based on
`player->visible_life_stock`. Gated to Postal (`level_mode == 0`) at
`update_subgoldy` 0x43b239.

## Programmatic HUD (direct quad queue)

Called each frame from `update_subgoldy` or nearby. These bypass the widget
system and push `queue_axis_aligned_textured_quad_uv` directly.

### Progress bar (`update_progress_bar` @ 0x437c40)

Three quads on the left column at authored x=13:

| Sprite | ID | Asset | Authored rect | UV | Role |
|---|---|---|---|---|---|
| cursor | 0x9d | `Sprites/Progress-Cursor.tga` (64×64) | x=12, y=`var_1c+111`, 64×64 | full | follows fill boundary |
| empty bar | 0x9b | `Sprites/Progress-Bar.tga` (64×256) | x=13, y=150, 64×`var_1c` | top `var_1c/256` of source | top (not-yet-traversed) portion |
| lit bar | 0x9c | `Sprites/Progress-Bar-lit.tga` (64×256) | x=13, y=150+`var_1c`, 64×(256−`var_1c`) | bottom (256−`var_1c`)/256 of source | bottom (traversed) portion |

`var_1c = (1 − progress) · 232 + 12` where `progress = (current − min)/(max − min)`.

**Port bug (gameplay/hud.zig:68-104):** The sprite assignment is swapped.
Our code puts `progress_bar_lit` on top and `progress_bar` on bottom; the
native draw puts the empty bar (`progress_bar`) on top and the lit bar
(`progress_bar_lit`) on bottom.

### Damage gauge (`update_damage_gauge` @ 0x440fd0)

Three quads on the right column at authored x=560:

| Sprite | ID | Asset | Authored rect | Role |
|---|---|---|---|---|
| bright overlay | 0x5b | `Sprites/DamageGuageBright.tga` (64×512) | x=560, y=70, 64×396 | full-area flash overlay |
| empty | 0x59 | `Sprites/DamageGuage.tga` (64×512) | x=560, y=70, 64×`var_14` | top (not-yet-damaged) |
| full | 0x5a | `Sprites/DamageGuageFull.tga` (64×512) | x=560, y=70+`var_14`, 64×(396−`var_14`) | bottom (damaged) |

UV y offsets use `var_14 / 432` (factor `0x3f460000`=0.77345… suggests source
scaling to 432 logical source pixels within the 512-tall texture).

**Port bug (gameplay/hud.zig:237-302):** Draws at authored `(586, 108, 28, 224)`
— wrong origin and **roughly 2× too narrow / 1.8× too short**.

### Warning actor (`update_warning` @ 0x446f80)

Fires `WARNING.TGA` flash when damage hits critical. Called from
`update_subgoldy` at 0x43b165. Position TODO (need to decode).

### Row event display (`update_row_event_display` @ 0x404cf0)

Mid-track parcel counter widget. Called from `update_subgoldy` at
0x43d1b7 and 0x43b182. Position TODO.

### Times up (`update_times_up` @ 0x445e20)

"Times Up" message triggered when `runtime_track_index == 0x5208`. Called
from `update_subgoldy` at 0x43d20b.

## Sprite registry entries (from `initialize_game_assets_and_world`)

Relevant sprite IDs confirmed via disasm of the `register_sprite_texture`
pushes near 0x40b150..0x40b700:

| ID | Asset | Use |
|---|---|---|
| 0x59 | `Sprites/DamageGuage.tga` | damage empty |
| 0x5a | `Sprites/DamageGuageFull.tga` | damage full |
| 0x5b | `Sprites/DamageGuageBright.tga` | damage bright overlay |
| 0x7a | `Sprites/ParcelIcon.tga` | parcel icon widget |
| 0x7b | `Sprites/Life.tga` | life egg slots |
| 0x9b | `Sprites/Progress-Bar.tga` | progress empty |
| 0x9c | `Sprites/Progress-Bar-lit.tga` | progress lit |
| 0x9d | `Sprites/Progress-Cursor.tga` | progress cursor |

## Level mode encoding

See `zig/src/frontend.zig` (`FrontendLevelMode`) for the canonical mapping and
per-mode `runtime_flags` masks recovered from `set_subgame_features` (0x435df0).
In short:

| `level_mode` | Name | Native anchor |
|---|---|---|
| 0 | Postal | `update_subgame` 0x438ce3 → `update_galaxy`; `update_subgoldy` 0x43b239 gates Postal life row |
| 1 | Challenge | `update_subgame` 0x438d9b → `update_challenge_setup_screen` |
| 4 | Time Trial | `update_subgame` 0x438d3e → `update_galaxy` with selector=2 (watch-best) |
| 7 | Tutorial | `update_subgame` 0x438eb2 → `update_tutorial`; `initialize_tutorial` 0x448da0 sets `runtime_flags \|= 0x600000` |
| 2, 3, 5, 6 | transitional engine states | fall through in `update_subgame` switch; 0x40ad2e writes `level_mode=2` at process init; mode 3 gets a slightly different hourglass tint at 0x438e33 |

HUD visibility rules observed in `initialize_subgame` 0x4378c2..0x4395c and
`update_subgoldy`:

- Score (widget A) + reference (widget D): shown in Postal / Challenge / Time Trial (0/1/4); hidden in Tutorial (7) and transitional modes 2/3. `initialize_subgame` hides both widgets for Tutorial, and `build_subgame_level` repeats the Tutorial-only `hide_gameplay_scores` gate.
- Parcel icon + count (widgets B/C): created only in Postal (`level_mode == 0`).
- Life eggs: allocated only for Postal and `show_subgoldy_lives` is gated to Postal (`level_mode == 0`).
- Stopwatch/elapsed text: Time Trial (`level_mode == 4`) uses `format_time_trial_string` for widget D; Challenge (`level_mode == 1`) and Postal don't run the stopwatch as HUD text.

## Zig port divergence summary

| # | Element | Native | Port status |
|---|---|---|---|
| 1 | Progress bar sprite assignment | empty top, lit bottom | **FIXED** (fed52e9): drawProgressBar swaps lit/empty to match native 0x437d72 / 0x437ddc |
| 2 | Damage gauge authored rect | `(560, 70, 64, 396)` | **FIXED** (fed52e9): authored rect moved to native coords |
| 3 | Damage gauge sprite triple | bright overlay + empty top + full bottom | **FIXED** (fed52e9 + 8571a2d): three-layer draw implemented; programmatic fallback removed |
| 4 | Life egg spacing | `x=13+i·24, y=430`, mode 0 only | **FIXED**: Postal-only allocation/update gate and native spacing |
| 5 | Score position | widget-backed right-aligned near x=400 | **FIXED** (fed52e9, a1158e7): right-aligned at x=628 |
| 6 | Reference best score (widget D) | top-left, mode-dependent content | **FIXED** (fed52e9, a1158e7) |
| 7 | Running timer | none in Postal; Time Trial only | **FIXED** (fed52e9): mode-gated to `.time_trial`, shown in widget D slot |
| 8 | Parcel icon | separate sprite 0x7a at (0, 58) + number at (47, 80) | **FIXED** (fed52e9, a1158e7): native sprite path + separate count text |
| 9 | Jetpack gauge bar | does not exist (particles only) | **REMOVED** (8571a2d): port invention deleted |
| 10 | "Click to Start" prompt text | menu_button widget at (0, 200) centered | uses `menu_button` at anchor_y=116 (tutorial) / 330 (standard); anchor_y differs from native 200 (see gameplay/prompt_overlay.zig:8-10) |
| 11 | `update_row_event_display` | native draws through 5 allocated borders per frame | port uses custom NineSliceFrame + icon + text (drawRowEventWidget); same data, different shell |
| 12 | `update_times_up` | at stop-track marker | not wired |
| 13 | `update_warning` | flash WARNING.TGA on crit | **FIXED** (8571a2d): drawn from inside drawDamageGauge with correct authored (288, 64, 64, 64) |

### Remaining

- (10) `drawStaticWidget` prompt anchor_y — re-check against native `initialize_click_start` (y=200).
- (11) `drawRowEventWidget` could be ported to the native 5-widget allocated-border approach with `allocate_border` / `kill_border` lifecycle. Current implementation produces the same content but bypasses the widget system.
- (12) `update_times_up` / `show_times_up_message` — wire "Time's Up" prompt for the stop-track marker (trigger: `runtime_track_index == 0x5208` per `update_subgoldy` 0x43d1f2).

## Replay HUD

Replay playback (persistent high-score replay, Time Trial watch-best) uses
the same HUD as normal gameplay. The key gates are `selected_level_record_persistent`
(1 for high-score replay, 0 for transient) and `selected_level_record_active`.
The score widget continues to tick from the captured replay stream; the
reference widget shows the record being replayed. No extra HUD chrome is
added for replay — no "REPLAY" banner or ghost indicator in the native HUD
layer. Widget D's content is still driven by mode.

## Next work

1. Fix concrete divergences 1–4 (authored coords and sprite assignments) in
   `gameplay/hud.zig`. Each fix cites this doc.
2. Add widgets D, parcel-icon sprite, reference best-score, and mode-gated
   running timer.
3. Remove the port-invented jetpack gauge bar or relabel it as non-canonical.
4. Decode remaining helpers (`update_warning`, `update_row_event_display`,
   `update_times_up`) and port.
