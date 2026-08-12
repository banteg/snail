from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_data_var_updates,
    apply_int_display_updates,
    apply_proto_updates,
    apply_struct_field_updates,
    apply_symbol_removals,
    apply_symbol_updates,
    apply_type_renames,
    apply_user_var_updates,
    emit_summary,
    types_declare_if_changed,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/bn_input_state_types.h"

GAME_INPUT_DATA_SYMBOL_UPDATES = (
    ("0x4972f0", "g_game_input_callback_table"),
)

GAME_INPUT_DATA_VAR_UPDATES = (
    ("0x4972f0", "void*"),
)

GAME_INPUT_FUNCTION_SYMBOL_UPDATES = (
    ("0x40aa50", "initialize_input"),
    ("0x40aa80", "update_input"),
    ("0x40aab0", "update_game_input"),
)

INPUT_CONTROLLER_DATA_SYMBOL_UPDATES = (
    ("0x50333c", "g_input_controller_slot0"),
    ("0x503374", "g_input_controller_slot1"),
)

INPUT_CONTROLLER_INTERIOR_SYMBOL_REMOVALS = (
    ("0x503340", "g_input_slot0_axis_y"),
    ("0x503344", "g_input_slot0_buttons"),
    ("0x503348", "g_input_slot0_pointer_x"),
    ("0x50334c", "g_input_slot0_pointer_y"),
    ("0x503350", "g_input_slot0_authored_x"),
    ("0x503354", "g_input_slot0_authored_y"),
    ("0x503358", "g_input_slot0_pointer_value"),
)

INPUT_CONTROLLER_DATA_VAR_UPDATES = (
    ("0x50333c", "InputControllerSlot"),
    ("0x503374", "InputControllerSlot"),
)

RSHELL_INPUT_FUNCTION_SYMBOL_UPDATES = (
    ("0x431fd0", "set_input_controller_slot0_button_axes"),
    ("0x431ff0", "update_input_controller_slot_button_axes"),
    ("0x4320f0", "copy_active_input_controller_state"),
)

INPUT_POINTER_REGION_FUNCTION_SYMBOL_UPDATES = (
    ("0x4321c0", "update_input_controller_pointer_region"),
    ("0x4323a0", "set_input_controller_pointer_authored_xy"),
)

INPUT_POINTER_REGION_DATA_SYMBOL_UPDATES = (
    ("0x508890", "g_input_region_top"),
    ("0x508898", "g_input_region_bottom"),
    ("0x5088a0", "g_input_region_left"),
    ("0x5088a8", "g_input_region_right"),
)

INPUT_POINTER_REGION_DATA_VAR_UPDATES = (
    ("0x508890", "int32_t[2]"),
    ("0x508898", "int32_t[2]"),
    ("0x5088a0", "int32_t[2]"),
    ("0x5088a8", "int32_t[2]"),
)

TEXT_INPUT_DATA_SYMBOL_UPDATES = (
    ("0x50339c", "g_text_input_repeat_step"),
    ("0x5108b8", "g_text_input_repeat_accumulator"),
    ("0x53c7f5", "g_text_input_last_repeat_code"),
)

TEXT_INPUT_DATA_VAR_UPDATES = (
    ("0x50339c", "float"),
    ("0x5108b8", "float"),
    ("0x53c7f5", "uint8_t"),
)

TEXT_INPUT_FUNCTION_SYMBOL_UPDATES = (
    ("0x432440", "read_pressed_text_input_key_code"),
    ("0x4327e0", "read_repeating_text_input_key_code"),
)

MOUSE_DATA_SYMBOL_UPDATES = (
    ("0x777d58", "g_mouse_live_x"),
    ("0x777d60", "g_mouse_live_y"),
    ("0x777d68", "g_mouse_screen_to_authored_y_scale"),
    ("0x777d6c", "g_mouse_screen_to_authored_x_scale"),
    ("0x777d70", "g_hide_system_cursor_flag"),
    ("0x777d74", "g_mouse_screen_y"),
    ("0x777d7c", "g_mouse_screen_x"),
    ("0x777d88", "g_mouse_clip_rect"),
    ("0x777d98", "g_mouse_input"),
    ("0x777d9c", "g_mouse_device"),
)

MOUSE_DATA_VAR_UPDATES = (
    ("0x777d58", "float[2]"),
    ("0x777d60", "float[2]"),
    ("0x777d68", "float"),
    ("0x777d6c", "float"),
    ("0x777d70", "uint8_t"),
    ("0x777d74", "int32_t[2]"),
    ("0x777d7c", "int32_t[2]"),
    ("0x777d88", "MouseScreenRect"),
    ("0x777d98", "void*"),
    ("0x777d9c", "void*"),
)

MOUSE_FUNCTION_SYMBOL_UPDATES = (
    ("0x44bbb0", "initialize_mouse_authored_scale_from_clip_rect"),
    ("0x44bbd0", "update_mouse_authored_scale"),
    ("0x44bc20", "resolve_uncaptured_cursor_sensitivity_scale"),
    ("0x44bc50", "update_mouse"),
    ("0x44c050", "set_hide_system_cursor_flag"),
    ("0x44c060", "click_mouse_screen"),
    ("0x44c100", "convert_mouse_screen_xy"),
    ("0x44c2c0", "release_mouse_input"),
    ("0x44c310", "initialize_mouse_input"),
)

KEYBOARD_DATA_SYMBOL_UPDATES = (
    ("0x777b4c", "g_keyboard_previous_state"),
    ("0x777c4c", "g_keyboard_current_state"),
    ("0x777d4c", "g_keyboard_input"),
    ("0x777d50", "g_keyboard_device"),
)

KEYBOARD_DATA_VAR_UPDATES = (
    ("0x777b4c", "uint8_t[256]"),
    ("0x777c4c", "uint8_t[256]"),
    ("0x777d4c", "IDirectInput8A*"),
    ("0x777d50", "IDirectInputDevice8A*"),
)

KEYBOARD_FUNCTION_SYMBOL_UPDATES = (
    ("0x44b7d0", "initialize_keyboard_input"),
    ("0x44b870", "update_keyboard_input"),
    ("0x44bb10", "is_key_pressed_edge"),
    ("0x44bb40", "is_key_down"),
    ("0x44bb60", "release_keyboard_input"),
)

KEYBOARD_FLAG_INT_DISPLAY_UPDATES = (
    (
        "update_keyboard_input",
        "0x44ba7d",
        "81 ce 00 00 40 00",
        0x400000,
        0xFFFFFFFF,
        "UnsignedHexadecimalDisplayType",
        "buttons |= INPUT_BUTTON_UNRESOLVED_00400000",
        "buttons |= &__dos_header",
    ),
    (
        "update_keyboard_input",
        "0x44bab9",
        "81 ce 00 00 80 00",
        0x800000,
        0xFFFFFFFF,
        "UnsignedHexadecimalDisplayType",
        "buttons |= INPUT_BUTTON_UNRESOLVED_00800000",
        "buttons |= &data_800000",
    ),
)

CONTROLLER_DATA_SYMBOL_UPDATES = (
    ("0x777b2c", "g_joystick_count"),
    ("0x777b30", "g_joystick_input"),
    ("0x777b34", "g_joystick_devices"),
)

CONTROLLER_DATA_VAR_UPDATES = (
    ("0x777b2c", "int32_t"),
    ("0x777b30", "IDirectInput8A*"),
    ("0x777b34", "IDirectInputDevice8A*[4]"),
)

CONTROLLER_FUNCTION_SYMBOL_UPDATES = (
    ("0x44b3c0", "enumerate_input_controllers"),
    ("0x44b490", "append_enumerated_input_controller_callback"),
    ("0x44b4e0", "configure_input_controller_axis_range_callback"),
    ("0x44b570", "update_joystick_input"),
    ("0x44b770", "release_input_controllers"),
)

INPUT_STATE_FIELDS = (
    ("0x00", "controller_slot", "int32_t"),
    ("0x04", "pressed_buttons", "InputButtonFlag"),
    ("0x08", "released_buttons", "InputButtonFlag"),
    ("0x0c", "previous_buttons", "InputButtonFlag"),
    ("0x10", "inverse_current_buttons", "InputButtonFlag"),
    ("0x14", "axis_x", "float"),
    ("0x18", "axis_y", "float"),
    ("0x1c", "unknown_1c", "int32_t"),
    ("0x20", "pointer_x", "float"),
    ("0x24", "pointer_y", "float"),
    ("0x28", "authored_x", "float"),
    ("0x2c", "authored_y", "float"),
    ("0x30", "pointer_value", "float"),
    ("0x34", "current_buttons", "InputButtonFlag"),
)

INPUT_CONTROLLER_SLOT_FIELDS = (
    ("0x00", "axis_x", "float"),
    ("0x04", "axis_y", "float"),
    ("0x08", "buttons", "InputButtonFlag"),
    ("0x0c", "pointer_x", "float"),
    ("0x10", "pointer_y", "float"),
    ("0x14", "authored_x", "float"),
    ("0x18", "authored_y", "float"),
    ("0x1c", "pointer_value", "float"),
)

GAME_INPUT_FIELDS = (
    ("0x00", "bod", "GameInputBodBase"),
    ("0x38", "input", "cRInput"),
)

RSHELL_INPUT_PROTO_UPDATES = (
    (
        "set_input_controller_slot0_button_axes",
        "void __cdecl set_input_controller_slot0_button_axes(InputButtonFlag buttons, float axis_x, float axis_y)",
    ),
    (
        "update_input_controller_slot_button_axes",
        "void __cdecl update_input_controller_slot_button_axes(int32_t slot, InputButtonFlag buttons, float axis_x, float axis_y)",
    ),
    (
        "copy_active_input_controller_state",
        "void __cdecl copy_active_input_controller_state(int32_t controller_slot, InputButtonFlag* out_buttons, float* out_axis_x, float* out_axis_y, float* out_authored_x, float* out_authored_y, float* out_pointer_value, float* out_pointer_x, float* out_pointer_y)",
    ),
)

INPUT_POINTER_REGION_PROTO_UPDATES = (
    (
        "update_input_controller_pointer_region",
        "void __cdecl update_input_controller_pointer_region(int32_t slot, int32_t left, int32_t top, int32_t right, int32_t bottom, int32_t x, int32_t y, int32_t pointer_value, char button_a, char button_b, char button_c, char capture_when_outside, char force_clamp)",
    ),
    (
        "set_input_controller_pointer_authored_xy",
        "void __cdecl set_input_controller_pointer_authored_xy(int32_t slot, float authored_x, float authored_y)",
    ),
)

PROTO_UPDATES = (
    *RSHELL_INPUT_PROTO_UPDATES,
    *INPUT_POINTER_REGION_PROTO_UPDATES,
    (
        "0x432440",
        "char __cdecl read_pressed_text_input_key_code()",
    ),
    (
        "0x4327e0",
        "char __cdecl read_repeating_text_input_key_code()",
    ),
    ("initialize_input", "void __thiscall initialize_input(cRInput* state)"),
    ("update_input", "void __thiscall update_input(cRInput* state)"),
    ("update_game_input", "void __thiscall update_game_input(cRGameInput* game_input)"),
    ("0x44bbb0", "void __cdecl initialize_mouse_authored_scale_from_clip_rect()"),
    ("0x44bbd0", "void __cdecl update_mouse_authored_scale(float authored_width, float authored_height)"),
    ("0x44bc20", "float __cdecl resolve_uncaptured_cursor_sensitivity_scale(float scale)"),
    ("0x44bc50", "int32_t __cdecl update_mouse(int32_t window_handle)"),
    ("0x44c050", "void __cdecl set_hide_system_cursor_flag(bool hidden)"),
    ("0x44c060", "void __cdecl click_mouse_screen(int32_t slot, int32_t x, int32_t y)"),
    ("0x44c100", "void __cdecl convert_mouse_screen_xy(int32_t sensitivity_slot, float* x, float* y)"),
    ("0x44c2c0", "int32_t __cdecl release_mouse_input()"),
    ("0x44c310", "int32_t __cdecl initialize_mouse_input(int32_t window_handle)"),
    ("0x44bb10", "uint8_t __cdecl is_key_pressed_edge(uint8_t key_code)"),
    ("0x44bb40", "uint8_t __cdecl is_key_down(uint8_t key_code)"),
    ("0x44bb60", "void __cdecl release_keyboard_input()"),
    (
        "0x44b3c0",
        "int32_t __cdecl enumerate_input_controllers(int32_t window_handle, int32_t* out_count)",
    ),
    (
        "0x44b490",
        "int32_t __stdcall append_enumerated_input_controller_callback(DIDEVICEINSTANCEA* instance, void* context)",
    ),
    (
        "0x44b4e0",
        "int32_t __stdcall configure_input_controller_axis_range_callback(DIDEVICEOBJECTINSTANCEA* instance, void* context)",
    ),
    ("0x44b570", "int32_t __cdecl update_joystick_input()"),
    ("0x44b770", "int32_t __cdecl release_input_controllers()"),
)

CONTROLLER_USER_VAR_UPDATES = (
    (
        "configure_input_controller_axis_range_callback",
        "StackVariableSourceType",
        0,
        -24,
        "range",
        "DIPROPRANGE",
    ),
    (
        "update_joystick_input",
        "StackVariableSourceType",
        0,
        -272,
        "state",
        "DIJOYSTATE2",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Replay the recovered input-state ownership into Binary Ninja."
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector.",
    )
    return parser.parse_args()


def main() -> int:
    target = parse_args().target
    operations: list[dict[str, object]] = apply_type_renames(
        REPO_ROOT,
        target=target,
        renames=(
            ("InputState", "cRInput"),
            ("GameInput", "cRGameInput"),
        ),
    )
    operations.extend([
        types_declare_if_changed(
            REPO_ROOT,
            target=target,
            header_path=HEADER_PATH,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=target,
            struct_name="cRInput",
            updates=INPUT_STATE_FIELDS,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=target,
            struct_name="InputControllerSlot",
            updates=INPUT_CONTROLLER_SLOT_FIELDS,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=target,
            struct_name="cRGameInput",
            updates=GAME_INPUT_FIELDS,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=GAME_INPUT_DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=target,
            updates=GAME_INPUT_DATA_VAR_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=GAME_INPUT_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=INPUT_CONTROLLER_DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_symbol_removals(
            REPO_ROOT,
            target=target,
            removals=INPUT_CONTROLLER_INTERIOR_SYMBOL_REMOVALS,
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=target,
            updates=INPUT_CONTROLLER_DATA_VAR_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=RSHELL_INPUT_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=INPUT_POINTER_REGION_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=INPUT_POINTER_REGION_DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=target,
            updates=INPUT_POINTER_REGION_DATA_VAR_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=TEXT_INPUT_DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=target,
            updates=TEXT_INPUT_DATA_VAR_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=TEXT_INPUT_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=KEYBOARD_DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=target,
            updates=KEYBOARD_DATA_VAR_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=KEYBOARD_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_int_display_updates(
            REPO_ROOT,
            target=target,
            updates=KEYBOARD_FLAG_INT_DISPLAY_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=MOUSE_DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=target,
            updates=MOUSE_DATA_VAR_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=MOUSE_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=CONTROLLER_DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=target,
            updates=CONTROLLER_DATA_VAR_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=target,
            updates=CONTROLLER_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_proto_updates(REPO_ROOT, target=target, updates=PROTO_UPDATES),
        *apply_user_var_updates(
            REPO_ROOT,
            target=target,
            updates=CONTROLLER_USER_VAR_UPDATES,
        ),
    ])
    return emit_summary(
        repo_root=REPO_ROOT,
        target=target,
        header_path=HEADER_PATH,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
