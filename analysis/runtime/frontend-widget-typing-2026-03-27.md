# Frontend Widget Typing 2026-03-27

## Scope

Bounded decompile readability pass for the shared front-end widget runtime:

- `initialize_frontend_widget`
- `layout_frontend_widget`
- `update_frontend_widget_interaction`
- `reset_tooltip`
- `update_tooltip`

The goal is to recover the safe widget/tooltip owner slices without overcommitting the text-input tail or delayed-action semantics.

## Safe Fields

### `FrontendWidgetTooltip`

- `+0x04 state`
- `+0x08 mode_flags`
- `+0x0c owner_widget`
- `+0x10 delay_progress`
- `+0x14 delay_step`
- `+0x18 tooltip_widget`
- `+0x38 owner_widget_38`

`update_tooltip` is a small state machine over `state`, accumulates `delay_progress += delay_step` in the active path, and owns/kills `tooltip_widget`.

### `FrontendWidget`

- list ownership:
  - `+0x04 list_flags`
  - `+0x08 list_prev`
  - `+0x0c list_next`
- authored geometry:
  - `+0x4c authored_left`
  - `+0x50 authored_top`
  - `+0x54 authored_width`
  - `+0x58 authored_height`
- authored/runtime style:
  - `+0x5c state_5c`
  - `+0x60 background_texture_id`
  - `+0x7c widget_type`
- slider runtime:
  - `+0x17c slider_position_target`
  - `+0x180 slider_position_current`
  - `+0x184 slider_hit_left`
  - `+0x188 slider_hit_right`
  - `+0x18c slider_hit_top`
  - `+0x190 slider_hit_bottom`
- shortcut and flags:
  - `+0x194 shortcut_key_code`
  - `+0x1a0 widget_flags`
  - `+0x1a4 previous_widget_flags`
- live/idle/hot colors:
  - `+0x1a8 current_fill_color`
  - `+0x1b8 idle_fill_color`
  - `+0x1c8 hot_fill_color`
  - `+0x1d8 current_text_color`
  - `+0x1e8 idle_text_color`
  - `+0x1f8 hot_text_color`
- hover/padding/text-effect:
  - `+0x208 hover_blend_target`
  - `+0x20c hover_blend_current`
  - `+0x210 idle_padding`
  - `+0x214 hot_padding`
  - `+0x218 target_padding`
  - `+0x21c current_padding`
  - `+0x220 text_effect_target`
  - `+0x224 text_effect_current`
- draw inset controls:
  - `+0x228 render_inset_delta`
  - `+0x22c render_inset_base`
  - `+0x230 render_inset_dynamic`
- layout/clamp:
  - `+0x234 layout_left`
  - `+0x238 layout_top`
  - `+0x23c clamped_left`
  - `+0x240 clamped_top`
  - `+0x244 layout_width`
  - `+0x248 layout_height`
  - `+0x254 border_edge`
  - `+0x258 text_alignment`
  - `+0x25c anchor_x`
- conservative progress/spacing:
  - `+0x260 aux_progress`
  - `+0x264 aux_step`
  - `+0x268 stack_gap`
- rendering/mouse settle:
  - `+0x26c texture_id_270`
  - `+0x274 mouse_settle_frames`
  - `+0x278 previous_mouse_x`
  - `+0x27c previous_mouse_y`
- nested controllers:
  - `+0x288 tooltip`
  - `+0x2c8 text_buffer`
- font/layout anchors:
  - `+0x6e8 font_id`
  - `+0x6ec font_scale`
  - `+0x6f0 layout_anchor_x`
  - `+0x6f4 layout_anchor_y`
- slider child widgets:
  - `+0x718 slider_less_widget`
  - `+0x71c slider_more_widget`
  - `+0x720 slider_value_widget`

## Avoid

- Do not claim `+0x714` as a slider child. `border_input_text_init` uses that slot for text-input-specific state.
- Do not claim the `+0x260/+0x264` pair as a dedicated delayed-click controller yet. They are only a generic progress accumulator in the bounded widget/runtime helpers.
- Do not treat `text_buffer` as a plain C string. The full `0x420` block is consumed by widget text helpers and text-input init as an opaque text/runtime buffer.
- Do not assign strong semantics to `owner_widget_38` or the draw helper slot at `+0x270` yet.

## Prototype Notes

Safe helper prototypes for readability:

- `initialize_frontend_widget(FrontendWidget* widget, uint32_t widget_flags, char* text, int32_t widget_type, float x, float y, Color4f* color, int32_t text_alignment, float anchor_x)`
- `layout_frontend_widget(FrontendWidget* widget)`
- `set_frontend_widget_shortcut_key(FrontendWidget* widget, int32_t shortcut_key_code)`
- `unhighlight_border(FrontendWidget* widget)`
- `highlight_border(FrontendWidget* widget)`
- `update_frontend_widget_interaction(FrontendWidget* widget)`
- `reset_tooltip(FrontendWidgetTooltip* tooltip)`
- `update_tooltip(FrontendWidgetTooltip* tooltip)`
