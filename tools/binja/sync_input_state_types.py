from __future__ import annotations

from pathlib import Path
import sys

from _narrow_sync import (
    apply_proto_updates,
    apply_struct_field_updates,
    emit_summary,
    types_declare,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/bn_input_state_types.h"
TARGET = "active"

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

GAME_INPUT_OWNER_FIELDS = (
    ("0x38", "input", "InputState"),
)

PROTO_UPDATES = (
    ("initialize_input", "int32_t __thiscall initialize_input(InputState* state)"),
    ("update_input", "int32_t __thiscall update_input(InputState* state)"),
    ("update_game_input", "void* __thiscall update_game_input(GameInputOwner* owner)"),
    (
        "copy_active_input_controller_state",
        "float* __cdecl copy_active_input_controller_state(int32_t controller_slot, int32_t* out_buttons, float* out_axis_x, float* out_axis_y, float* out_authored_x, float* out_authored_y, float* out_pointer_value, float* out_pointer_x, float* out_pointer_y)",
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
            struct_name="GameInputOwner",
            updates=GAME_INPUT_OWNER_FIELDS,
        ),
        *apply_proto_updates(REPO_ROOT, target=TARGET, updates=PROTO_UPDATES),
    ]
    return emit_summary(
        repo_root=REPO_ROOT,
        target=TARGET,
        header_path=HEADER_PATH,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
