from __future__ import annotations

from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_proto_updates,
    apply_struct_field_updates,
    apply_symbol_updates,
    apply_user_var_updates,
    emit_summary,
    types_declare,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/bn_input_state_types.h"
TARGET = DEFAULT_TARGET

GAME_INPUT_DATA_SYMBOL_UPDATES = (
    ("0x4972f0", "g_game_input_callback_table"),
)

GAME_INPUT_DATA_VAR_UPDATES = (
    ("0x4972f0", "void*"),
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
    ("0x04", "pressed_buttons", "int32_t"),
    ("0x08", "released_buttons", "int32_t"),
    ("0x0c", "previous_buttons", "int32_t"),
    ("0x10", "inverse_current_buttons", "int32_t"),
    ("0x14", "axis_x", "float"),
    ("0x18", "axis_y", "float"),
    ("0x1c", "unknown_1c", "int32_t"),
    ("0x20", "pointer_x", "float"),
    ("0x24", "pointer_y", "float"),
    ("0x28", "authored_x", "float"),
    ("0x2c", "authored_y", "float"),
    ("0x30", "pointer_value", "float"),
    ("0x34", "current_buttons", "int32_t"),
)

GAME_INPUT_FIELDS = (
    ("0x00", "bod", "GameInputBodBase"),
    ("0x38", "input", "InputState"),
)

PROTO_UPDATES = (
    (
        "0x432440",
        "char __cdecl read_pressed_text_input_key_code()",
    ),
    (
        "0x4327e0",
        "char __cdecl read_repeating_text_input_key_code()",
    ),
    ("initialize_input", "int32_t __thiscall initialize_input(InputState* state)"),
    ("update_input", "void __thiscall update_input(InputState* state)"),
    ("update_game_input", "void __thiscall update_game_input(GameInput* game_input)"),
    (
        "copy_active_input_controller_state",
        "float* __cdecl copy_active_input_controller_state(int32_t controller_slot, int32_t* out_buttons, float* out_axis_x, float* out_axis_y, float* out_authored_x, float* out_authored_y, float* out_pointer_value, float* out_pointer_x, float* out_pointer_y)",
    ),
    ("0x44bbb0", "int32_t __cdecl initialize_mouse_authored_scale_from_clip_rect()"),
    ("0x44bbd0", "int32_t __cdecl update_mouse_authored_scale(float authored_width, float authored_height)"),
    ("0x44bc20", "float __cdecl resolve_uncaptured_cursor_sensitivity_scale(float scale)"),
    ("0x44bc50", "int32_t __cdecl update_mouse(int32_t window_handle)"),
    ("0x44c050", "char __cdecl set_hide_system_cursor_flag(char hidden)"),
    ("0x44c060", "void* __cdecl click_mouse_screen(int32_t slot, int32_t x, int32_t y)"),
    ("0x44c100", "void __cdecl convert_mouse_screen_xy(int32_t sensitivity_slot, float* x, float* y)"),
    ("0x44c2c0", "int32_t __cdecl release_mouse_input()"),
    ("0x44c310", "int32_t __cdecl initialize_mouse_input(int32_t window_handle)"),
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


def main() -> int:
    operations = [
        types_declare(REPO_ROOT, target=TARGET, header_path=HEADER_PATH),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="InputState",
            updates=INPUT_STATE_FIELDS,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="GameInput",
            updates=GAME_INPUT_FIELDS,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=TARGET,
            updates=GAME_INPUT_DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=TARGET,
            updates=GAME_INPUT_DATA_VAR_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=TARGET,
            updates=TEXT_INPUT_DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=TARGET,
            updates=TEXT_INPUT_DATA_VAR_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=TARGET,
            updates=TEXT_INPUT_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=TARGET,
            updates=MOUSE_DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=TARGET,
            updates=MOUSE_DATA_VAR_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=TARGET,
            updates=MOUSE_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=TARGET,
            updates=CONTROLLER_DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=TARGET,
            updates=CONTROLLER_DATA_VAR_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=TARGET,
            updates=CONTROLLER_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_proto_updates(REPO_ROOT, target=TARGET, updates=PROTO_UPDATES),
        *apply_user_var_updates(
            REPO_ROOT,
            target=TARGET,
            updates=CONTROLLER_USER_VAR_UPDATES,
        ),
    ]
    return emit_summary(
        repo_root=REPO_ROOT,
        target=TARGET,
        header_path=HEADER_PATH,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
