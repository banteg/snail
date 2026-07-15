#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    current_struct_size,
    emit_summary,
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/font_system_types.h"

EXPECTED_PREREQUISITE_SIZES = {
    "BodBase": 0x38,
    "TextureRef": 0xA4,
    "tColour": 0x10,
}

EXPECTED_STRUCT_SIZES = {
    "FontSheet": 0x828,
    "cFontPrintBuffer": 0x84,
}

FONT_SHEET_FIELD_UPDATES = (
    ("0x000", "slot_count", "int32_t"),
    ("0x004", "texture_ref_a", "TextureRef*"),
    ("0x008", "texture_ref_b", "TextureRef*"),
    ("0x00c", "u0", "float[0x80]"),
    ("0x20c", "v0", "float[0x80]"),
    ("0x40c", "glyph_width", "float[0x80]"),
    ("0x60c", "texture_page", "int32_t[0x80]"),
    ("0x80c", "line_marker_y", "float"),
    ("0x810", "line_step", "float"),
    ("0x814", "line_marker_fraction", "float"),
    ("0x818", "spacing_scale", "float"),
    ("0x81c", "width_scale", "float"),
    ("0x820", "height_scale", "float"),
    ("0x824", "font_kind", "int32_t"),
)

FONT_PRINT_BUFFER_FIELD_UPDATES = (
    ("0x00", "flags", "uint32_t"),
    ("0x04", "x0", "float"),
    ("0x08", "y0", "float"),
    ("0x0c", "unknown_0c", "int32_t"),
    ("0x10", "x1", "float"),
    ("0x14", "y1", "float"),
    ("0x18", "unknown_18", "int32_t"),
    ("0x1c", "x2", "float"),
    ("0x20", "y2", "float"),
    ("0x24", "unknown_24", "int32_t"),
    ("0x28", "x3", "float"),
    ("0x2c", "y3", "float"),
    ("0x30", "unknown_30", "int32_t"),
    ("0x34", "text_wave_amplitude", "float"),
    ("0x38", "text_wave_enabled", "uint8_t"),
    ("0x39", "pad_39", "char[0x3]"),
    ("0x3c", "font_id", "int32_t"),
    ("0x40", "text_scale", "float"),
    ("0x44", "text", "char*"),
    ("0x48", "horizontal_align", "int32_t"),
    ("0x4c", "anchor_x", "float"),
    ("0x50", "texture_id", "int32_t"),
    ("0x54", "width", "float"),
    ("0x58", "height", "float"),
    ("0x5c", "u0", "float"),
    ("0x60", "v0", "float"),
    ("0x64", "u1", "float"),
    ("0x68", "v1", "float"),
    ("0x6c", "color", "tColour"),
    ("0x7c", "layer", "int32_t"),
    ("0x80", "blend", "int32_t"),
)

FUNCTION_SYMBOL_UPDATES = (
    ("0x449c10", "initialize_global_font3d_bods_thunk"),
    ("0x449c20", "initialize_global_font3d_bods"),
    ("0x449c40", "initialize_global_font_queue_colors_thunk"),
    ("0x449c50", "initialize_global_font_queue_colors"),
    ("0x449e90", "measure_font_text_width"),
    ("0x449f50", "register_font_texture_sheet"),
    ("0x44a360", "draw_font_text_instance"),
    ("0x44ae10", "initialize_font3d_objects"),
)

DATA_SYMBOL_UPDATES = (
    ("0x753ce8", "g_font_text_buffer"),
    ("0x7544e8", "g_font_queue"),
    ("0x7754e8", "g_font3d_bods"),
    ("0x7770e8", "g_font3d_scales"),
    ("0x7772e8", "g_font_wave_phase_a"),
    ("0x7772ec", "g_font_wave_phase_b"),
    ("0x7772f0", "g_font_text_cursor"),
    ("0x7772f4", "g_font_wave_step_b"),
    ("0x7772f8", "g_font_sheets"),
    ("0x777b20", "g_registered_font_count"),
    ("0x777b24", "g_font_queue_count"),
    ("0x777b28", "g_font_wave_step_a"),
)

DATA_VAR_UPDATES = (
    ("0x753ce8", "char[0x800]"),
    ("0x7544e8", "cFontPrintBuffer[0x400]"),
    ("0x7754e8", "BodBase[0x80]"),
    ("0x7770e8", "float[0x80]"),
    ("0x7772e8", "float"),
    ("0x7772ec", "float"),
    ("0x7772f0", "char*"),
    ("0x7772f4", "float"),
    ("0x7772f8", "FontSheet[0x1]"),
    ("0x777b20", "int32_t"),
    ("0x777b24", "int32_t"),
    ("0x777b28", "float"),
)

PROTO_UPDATES = (
    (
        "initialize_global_font3d_bods_thunk",
        "void __cdecl initialize_global_font3d_bods_thunk()",
    ),
    (
        "initialize_global_font3d_bods",
        "void __cdecl initialize_global_font3d_bods()",
    ),
    (
        "initialize_global_font_queue_colors_thunk",
        "void __cdecl initialize_global_font_queue_colors_thunk()",
    ),
    (
        "initialize_global_font_queue_colors",
        "void __cdecl initialize_global_font_queue_colors()",
    ),
    (
        "measure_font_text_width",
        "float __cdecl measure_font_text_width(char* text, int32_t font_id, float scale)",
    ),
    (
        "register_font_texture_sheet",
        "int32_t __cdecl register_font_texture_sheet(char* texture_path, int32_t font_kind, float width_scale, float height_scale)",
    ),
    (
        "draw_font_text_instance",
        "void __cdecl draw_font_text_instance(cFontPrintBuffer* entry)",
    ),
    (
        "initialize_font3d_objects",
        "void __cdecl initialize_font3d_objects(int16_t font_id)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply recovered font runtime owners to Binary Ninja."
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector.",
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Checked-in font-system type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"font-system type header not found: {header_path}")

    observed_prerequisites = {
        name: current_struct_size(REPO_ROOT, target=args.target, struct_name=name)
        for name in EXPECTED_PREREQUISITE_SIZES
    }
    bad_prerequisites = {
        name: observed_size
        for name, observed_size in observed_prerequisites.items()
        if observed_size != EXPECTED_PREREQUISITE_SIZES[name]
    }
    if bad_prerequisites:
        raise RuntimeError(f"font-system prerequisite layouts changed: {bad_prerequisites}")

    mismatched_types = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if current_struct_size(REPO_ROOT, target=args.target, struct_name=name)
        != expected_size
    )
    if mismatched_types:
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=mismatched_types,
            include_types=EXPECTED_STRUCT_SIZES,
        )
        type_operation["repaired_types"] = mismatched_types
        type_operation["expected_sizes"] = {
            name: EXPECTED_STRUCT_SIZES[name] for name in mismatched_types
        }
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "font-system owner sizes already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
        }

    operations: list[dict[str, object]] = [
        type_operation,
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("FontSheet", FONT_SHEET_FIELD_UPDATES),
                ("cFontPrintBuffer", FONT_PRINT_BUFFER_FIELD_UPDATES),
            ),
            proto_updates=PROTO_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_VAR_UPDATES,
        ),
    ]
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
