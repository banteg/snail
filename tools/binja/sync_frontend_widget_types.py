from __future__ import annotations

from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_proto_updates,
    apply_struct_field_updates,
    apply_symbol_updates,
    current_prototypes,
    emit_summary,
    types_declare,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/bn_frontend_widget_types.h"
TARGET = DEFAULT_TARGET

FRONTEND_WIDGET_FIELDS = (
    ("0x00", "list_kind", "uint32_t"),
    ("0x04", "list_flags", "uint32_t"),
    ("0x08", "list_prev", "FrontendWidget*"),
    ("0x0c", "list_next", "FrontendWidget*"),
    ("0x44", "hide_blend", "float"),
    ("0x48", "border_texture_id", "int32_t"),
    ("0x4c", "authored_left", "float"),
    ("0x50", "authored_top", "float"),
    ("0x54", "authored_width", "float"),
    ("0x58", "authored_height", "float"),
    ("0x5c", "texture_hit_test_enabled", "uint8_t"),
    ("0x5d", "sprite_wobble_positive", "uint8_t"),
    ("0x60", "background_texture_id", "int32_t"),
    ("0x64", "texture_hit_test_sprite", "int32_t"),
    ("0x68", "sprite_extend_texture_c", "int32_t"),
    ("0x7c", "widget_type", "int32_t"),
    ("0x80", "twinkle_manager", "TwinkleManager"),
    ("0x178", "sprite_shadow_offset", "float"),
    ("0x17c", "slider_position_target", "float"),
    ("0x180", "slider_position_current", "float"),
    ("0x184", "slider_hit_left", "float"),
    ("0x188", "slider_hit_right", "float"),
    ("0x18c", "slider_hit_top", "float"),
    ("0x190", "slider_hit_bottom", "float"),
    ("0x194", "shortcut_key_code", "int32_t"),
    ("0x1a0", "widget_flags", "uint32_t"),
    ("0x1a4", "previous_widget_flags", "uint32_t"),
    ("0x1ac", "current_fill_color", "Color4f"),
    ("0x1bc", "idle_fill_color", "Color4f"),
    ("0x1cc", "hot_fill_color", "Color4f"),
    ("0x1dc", "current_text_color", "Color4f"),
    ("0x1ec", "idle_text_color", "Color4f"),
    ("0x1fc", "hot_text_color", "Color4f"),
    ("0x20c", "hover_blend_target", "float"),
    ("0x210", "hover_blend_current", "float"),
    ("0x214", "idle_padding", "float"),
    ("0x218", "hot_padding", "float"),
    ("0x21c", "target_padding", "float"),
    ("0x220", "current_padding", "float"),
    ("0x224", "text_effect_target", "float"),
    ("0x228", "text_effect_current", "float"),
    ("0x22c", "render_inset_delta", "float"),
    ("0x230", "render_inset_base", "float"),
    ("0x234", "render_inset_dynamic", "uint8_t"),
    ("0x238", "layout_left", "float"),
    ("0x23c", "layout_top", "float"),
    ("0x240", "texture_hit_x", "float"),
    ("0x244", "texture_hit_y", "float"),
    ("0x248", "layout_width", "float"),
    ("0x24c", "layout_height", "float"),
    ("0x250", "texture_hit_width", "float"),
    ("0x254", "texture_hit_height", "float"),
    ("0x258", "border_edge", "float"),
    ("0x25c", "text_alignment", "int32_t"),
    ("0x260", "anchor_x", "float"),
    ("0x264", "teardown_progress", "float"),
    ("0x268", "teardown_progress_step", "float"),
    ("0x26c", "stack_gap", "float"),
    ("0x270", "texture_id", "int32_t"),
    ("0x274", "texture_layer", "int32_t"),
    ("0x278", "mouse_history_warmup_frames", "int32_t"),
    ("0x27c", "previous_mouse_x", "float"),
    ("0x280", "previous_mouse_y", "float"),
    ("0x28c", "tooltip", "FrontendWidgetTooltip"),
    ("0x2cc", "text_buffer", "FrontendWidgetTextBuffer"),
    ("0x6ec", "font_id", "int32_t"),
    ("0x6f0", "font_scale", "float"),
    ("0x6f4", "layout_anchor_x", "float"),
    ("0x6f8", "layout_anchor_y", "float"),
    ("0x6fc", "input_cursor", "int32_t"),
    ("0x700", "input_cursor_visible", "int32_t"),
    ("0x704", "input_cursor_blink_progress", "float"),
    ("0x708", "input_cursor_blink_step", "float"),
    ("0x70c", "input_flags", "uint32_t"),
    ("0x710", "input_length", "int32_t"),
    ("0x714", "input_capacity", "int32_t"),
    ("0x718", "slider_less_widget", "FrontendWidget*"),
    ("0x71c", "slider_more_widget", "FrontendWidget*"),
    ("0x720", "slider_value_widget", "FrontendWidget*"),
)

FRONTEND_WIDGET_TOOLTIP_FIELDS = (
    ("0x04", "state", "int32_t"),
    ("0x08", "mode_flags", "uint32_t"),
    ("0x0c", "owner_widget", "FrontendWidget*"),
    ("0x10", "delay_progress", "float"),
    ("0x14", "delay_step", "float"),
    ("0x18", "tooltip_widget", "FrontendWidget*"),
    ("0x38", "owner_widget_38", "FrontendWidget*"),
)

DEFERRED_PROTO_UPDATES = (
    (
        "initialize_frontend_widget",
        "void __thiscall initialize_frontend_widget(FrontendWidget* widget, uint32_t widget_flags, char* text, int32_t widget_type, float x, float y, Color4f* color, int32_t text_alignment, float anchor_x)",
    ),
    (
        "layout_frontend_widget",
        "void __thiscall layout_frontend_widget(FrontendWidget* widget)",
    ),
    (
        "0x402790",
        "void __thiscall set_frontend_widget_shortcut_key(FrontendWidget* widget, int32_t shortcut_key_code)",
    ),
    (
        "stack_widget_below",
        "void __thiscall stack_widget_below(FrontendWidget* widget, FrontendWidget* previous_widget)",
    ),
    (
        "initialize_exit_prompt",
        "void __thiscall initialize_exit_prompt(Exit* exit_prompt)",
    ),
    ("hide_border_init", "void __thiscall hide_border_init(FrontendWidget* widget)"),
    ("unhide_border_init", "void __thiscall unhide_border_init(FrontendWidget* widget)"),
    ("unhighlight_border", "void __thiscall unhighlight_border(FrontendWidget* widget)"),
    ("highlight_border", "void __thiscall highlight_border(FrontendWidget* widget)"),
    (
        "border_sprite_extend",
        "void __thiscall border_sprite_extend(FrontendWidget* widget, int32_t sprite_a, int32_t sprite_c, int32_t sprite_b, uint8_t wobble_positive)",
    ),
    (
        "border_input_text_init",
        "void __thiscall border_input_text_init(FrontendWidget* widget, int32_t capacity, char* text, int32_t flags)",
    ),
)

PROTO_UPDATES = (
    (
        "border_mouse_test",
        "uint8_t __thiscall border_mouse_test(FrontendWidget* widget)",
    ),
    ("update_frontend_widget_interaction", "void __thiscall update_frontend_widget_interaction(FrontendWidget* widget)"),
    ("reset_tooltip", "int32_t __fastcall reset_tooltip(FrontendWidgetTooltip* tooltip)"),
    ("update_tooltip", "int32_t __thiscall update_tooltip(FrontendWidgetTooltip* tooltip)"),
    ("0x433050", "int32_t __cdecl launch_alpha72_url(char* url)"),
)

SYMBOL_UPDATES = (
    ("0x433050", "launch_alpha72_url"),
)


def report_deferred_prototypes(*, target: str) -> list[dict[str, object]]:
    observed_prototypes = current_prototypes(
        REPO_ROOT,
        target=target,
        identifiers=(
            identifier for identifier, _prototype in DEFERRED_PROTO_UPDATES
        ),
    )
    return [
        {
            "op": "proto_owner_deferred",
            "status": "deferred",
            "reason": "Binary Ninja restores the stale scalar prototype during live verification",
            "identifier": identifier,
            "desired_prototype": prototype,
            "observed_prototype": observed_prototypes.get(identifier),
        }
        for identifier, prototype in DEFERRED_PROTO_UPDATES
    ]


def main() -> int:
    operations = [
        types_declare(REPO_ROOT, target=TARGET, header_path=HEADER_PATH),
        *apply_struct_field_updates(REPO_ROOT, target=TARGET, struct_name="FrontendWidget", updates=FRONTEND_WIDGET_FIELDS),
        *apply_struct_field_updates(REPO_ROOT, target=TARGET, struct_name="FrontendWidgetTooltip", updates=FRONTEND_WIDGET_TOOLTIP_FIELDS),
        *apply_proto_updates(REPO_ROOT, target=TARGET, updates=PROTO_UPDATES),
        *report_deferred_prototypes(target=TARGET),
        *apply_symbol_updates(REPO_ROOT, target=TARGET, updates=SYMBOL_UPDATES, kind="function"),
    ]
    return emit_summary(repo_root=REPO_ROOT, target=TARGET, header_path=HEADER_PATH, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
