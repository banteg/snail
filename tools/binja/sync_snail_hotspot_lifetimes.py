#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_user_var_updates,
    current_header_type_equivalence,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_TYPE_WIDTHS = {
    "Vec3": 0x0C,
    "SnailHotspotLocalZCursorView": 0x0C,
    "TransformMatrix": 0x40,
    "ObjectFaceQuad": 0x30,
    "ObjectFaceQuadTextureCursorView": 0x30,
    "Object": 0xDC,
    "RenderableBod": 0x80,
    "Snail": 0x19B4,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "ObjectFaceQuad": {
        0x02: ("vertex_0", "uint16_t"),
        0x0C: ("texture_ref", "TextureRef*"),
    },
    "Object": {
        0x38: ("vertices", "Vec3*"),
        0x54: ("facequad_count", "int32_t"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
    },
    "RenderableBod": {
        0x38: ("transform", "TransformMatrix"),
    },
    "Snail": {
        0x15CC: ("snail_hotspot_source_body", "RenderableBod"),
        0x164C: ("snail_hotspot_body", "RenderableBod"),
        0x16CC: ("snail_hotspots_local", "Vec3[19]"),
        0x17B0: ("snail_hotspots_world", "Vec3[19]"),
    },
}

# build_snail_hotspots keeps five physical borrows: EBP on the hotspot Object,
# EBX on the 19-name table, ESI at each local Vec3::z, EDI at each facequad's
# texture_ref, and EAX on the selected source vertex. The two field-first views
# preserve the carried addresses without moving either bank under a new owner.
#
# update_snail_skin then walks the 19-entry world bank. EAX borrows the
# corresponding local slot exactly 19 Vec3 records behind it, while ECX retains
# the pre-increment world destination. EBX is the shared local/world index and
# ESI borrows one of the two complete RenderableBod transforms populated by
# initialize_cutscene. All are element or transform borrows from Snail-owned
# arrays/bodies or Object-owned mesh banks.
SNAIL_HOTSPOT_CURSOR_USER_VAR_UPDATES = (
    (
        "build_snail_hotspots",
        "RegisterVariableSourceType",
        3,
        71,
        "hotspot_model",
        "Object*",
    ),
    (
        "build_snail_hotspots",
        "RegisterVariableSourceType",
        15,
        69,
        "hotspot_name_cursor",
        "char**",
    ),
    (
        "build_snail_hotspots",
        "RegisterVariableSourceType",
        20,
        72,
        "hotspot_local_z_cursor",
        "SnailHotspotLocalZCursorView*",
    ),
    (
        "build_snail_hotspots",
        "RegisterVariableSourceType",
        63,
        73,
        "hotspot_face_texture_cursor",
        "ObjectFaceQuadTextureCursorView*",
    ),
    (
        "build_snail_hotspots",
        "RegisterVariableSourceType",
        124,
        66,
        "hotspot_source_vertex",
        "Vec3*",
    ),
    (
        "update_snail_skin",
        "RegisterVariableSourceType",
        11,
        69,
        "hotspot_index",
        "int32_t",
    ),
    (
        "update_snail_skin",
        "RegisterVariableSourceType",
        13,
        71,
        "hotspot_world_cursor",
        "Vec3*",
    ),
    (
        "update_snail_skin",
        "RegisterVariableSourceType",
        25,
        66,
        "hotspot_local_slot",
        "Vec3*",
    ),
    (
        "update_snail_skin",
        "RegisterVariableSourceType",
        34,
        72,
        "hotspot_transform",
        "TransformMatrix*",
    ),
    (
        "update_snail_skin",
        "RegisterVariableSourceType",
        97,
        67,
        "hotspot_world_slot",
        "Vec3*",
    ),
)

HOTSPOT_ANALYSIS_VIEWS = (
    "SnailHotspotLocalZCursorView",
    "ObjectFaceQuadTextureCursorView",
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Replay the borrowed Snail local/world hotspot cursors."
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector. Defaults to the Snail Mail database.",
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Header documenting the canonical Snail hotspot owners.",
    )
    return parser.parse_args()


def verify_snail_hotspot_owner_layout(target: str) -> dict[str, object]:
    widths = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=EXPECTED_TYPE_WIDTHS,
    )
    layouts = current_struct_fields_batch(
        REPO_ROOT,
        target=target,
        struct_names=EXPECTED_STRUCT_FIELDS,
    )
    mismatches: list[str] = []
    for type_name, expected_width in EXPECTED_TYPE_WIDTHS.items():
        observed_width = widths[type_name]
        if observed_width != expected_width:
            mismatches.append(
                f"{type_name}: expected width {expected_width:#x}, "
                f"observed {observed_width!r}"
            )
    for struct_name, expected_fields in EXPECTED_STRUCT_FIELDS.items():
        observed_fields = layouts[struct_name]
        for offset, expected in expected_fields.items():
            observed = observed_fields.get(offset)
            if observed != expected:
                mismatches.append(
                    f"{struct_name}+{offset:#x}: expected {expected!r}, "
                    f"observed {observed!r}"
                )
    if mismatches:
        raise RuntimeError(
            "canonical Snail hotspot ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_snail_hotspot_owner_layout",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def ensure_hotspot_analysis_views(
    *, target: str, header_path: Path
) -> dict[str, object]:
    equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=target,
        header_path=header_path,
    )
    stale_types = tuple(
        type_name
        for type_name in HOTSPOT_ANALYSIS_VIEWS
        if not equivalence.get(type_name, False)
    )
    if not stale_types:
        return {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "hotspot analysis views already match the header",
            "header": str(header_path),
            "replace_types": (),
            "include_types": HOTSPOT_ANALYSIS_VIEWS,
        }
    return types_declare_missing_only(
        REPO_ROOT,
        target=target,
        header_path=header_path,
        replace_types=stale_types,
        include_types=HOTSPOT_ANALYSIS_VIEWS,
    )


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        ensure_hotspot_analysis_views(
            target=args.target,
            header_path=header_path,
        ),
        verify_snail_hotspot_owner_layout(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=SNAIL_HOTSPOT_CURSOR_USER_VAR_UPDATES,
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
