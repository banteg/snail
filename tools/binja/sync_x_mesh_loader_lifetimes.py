#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_direct_proto_update,
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"

X_MESH_LOADER_PROTOTYPE = (
    "void __thiscall load_x_mesh("
    "DirectXLoader* loader, char* mesh_path, Object* object, "
    "int32_t options_flags)"
)
DIRECTX_LOADER_INIT_PROTOTYPE = (
    "void __thiscall initialize_directx_loader(DirectXLoader* loader)"
)
CACHED_X_MESH_LOADER_PROTOTYPE = (
    "int32_t __thiscall load_or_reuse_cached_x_mesh("
    "DirectXLoader* loader, char* mesh_name)"
)

EXPECTED_TYPE_WIDTHS = {
    "ObjectUv": 0x08,
    "ObjectFaceQuad": 0x30,
    "TextureRef": 0xA4,
    "Object": 0xDC,
    "CachedXMeshSlot": 0xBC,
    "DuplicateVertices": 0x08,
    "DirectXLoader": 0x5E10,
}

EXPECTED_STRUCT_FIELDS = {
    "ObjectFaceQuad": {
        0x02: ("vertex_0", "uint16_t"),
        0x08: ("vertex_3", "uint16_t"),
        0x0C: ("texture_ref", "TextureRef*"),
        0x10: ("uv", "ObjectUv[4]"),
    },
    "TextureRef": {
        0x00: ("flags", "TextureRefFlags"),
    },
    "Object": {
        0x10: ("flags", "ObjectFlag"),
        0x38: ("vertices", "Vec3*"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
    },
    "CachedXMeshSlot": {
        0x24: ("object", "Object*"),
        0x3C: ("name", "char[128]"),
    },
    "DirectXLoader": {
        0x00: ("animation_bytes", "char*"),
        0x04: ("cached_x_mesh_count", "int32_t"),
        0x08: ("cached_x_mesh_slots", "CachedXMeshSlot[128]"),
        0x5E08: ("duplicate_vertices", "DuplicateVertices"),
    },
}

# The native 0x25c-byte frame owns two adjacent 0x100-byte path buffers. The
# first holds the selected archive path; the second is rewritten for each
# material texture. Five independent char* cursors borrow interior positions
# from the shared archive buffer and advance through disjoint X-file sections.
# They never own or free that storage. The temporary UV, remap, and material
# banks are heap owners already recovered from typed allocation/call flows, so
# this replay deliberately leaves their SSA-scoped registers inferred.
#
# The cache wrapper's EBX lifetime is likewise a borrowed cursor: native starts
# it at CachedXMeshSlot::name and advances it by the exact 0xbc slot stride.
# EDI carries the corresponding slot index, while the miss path allocates one
# Object into the selected slot and retains the incremented cache count in EAX.
X_MESH_LOADER_USER_VAR_UPDATES = (
    (
        "load_x_mesh",
        "StackVariableSourceType",
        0,
        -564,
        "mesh_cursor",
        "char*",
    ),
    (
        "load_x_mesh",
        "StackVariableSourceType",
        0,
        -556,
        "material_cursor",
        "char*",
    ),
    (
        "load_x_mesh",
        "StackVariableSourceType",
        0,
        -548,
        "texcoord_cursor",
        "char*",
    ),
    (
        "load_x_mesh",
        "StackVariableSourceType",
        0,
        -540,
        "material_header_cursor",
        "char*",
    ),
    (
        "load_x_mesh",
        "StackVariableSourceType",
        0,
        -536,
        "duplicate_cursor",
        "char*",
    ),
    (
        "load_x_mesh",
        "StackVariableSourceType",
        0,
        -516,
        "byte_count",
        "int32_t",
    ),
    (
        "load_x_mesh",
        "StackVariableSourceType",
        0,
        -512,
        "mesh_file_path",
        "char[0x100]",
    ),
    (
        "load_x_mesh",
        "StackVariableSourceType",
        0,
        -256,
        "texture_path",
        "char[0x100]",
    ),
    (
        "load_or_reuse_cached_x_mesh",
        "RegisterVariableSourceType",
        10,
        73,
        "cached_slot_index",
        "int32_t",
    ),
    (
        "load_or_reuse_cached_x_mesh",
        "RegisterVariableSourceType",
        19,
        69,
        "cached_name_cursor",
        "char*",
    ),
    (
        "load_or_reuse_cached_x_mesh",
        "RegisterVariableSourceType",
        80,
        66,
        "new_object",
        "Object*",
    ),
    (
        "load_or_reuse_cached_x_mesh",
        "RegisterVariableSourceType",
        133,
        66,
        "new_cached_x_mesh_count",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the DirectX X-mesh loader family's authored member ABIs, "
            "borrowed parser/cache cursors, and retained object lifetimes."
        )
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
        help="Header documenting the canonical DirectXLoader/Object owners.",
    )
    return parser.parse_args()


def verify_owner_layouts(target: str) -> dict[str, object]:
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
            "canonical X-mesh loader ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_x_mesh_loader_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        verify_owner_layouts(args.target),
        apply_direct_proto_update(
            REPO_ROOT,
            target=args.target,
            identifier="load_x_mesh",
            prototype=X_MESH_LOADER_PROTOTYPE,
        ),
        apply_direct_proto_update(
            REPO_ROOT,
            target=args.target,
            identifier="initialize_directx_loader",
            prototype=DIRECTX_LOADER_INIT_PROTOTYPE,
        ),
        apply_direct_proto_update(
            REPO_ROOT,
            target=args.target,
            identifier="load_or_reuse_cached_x_mesh",
            prototype=CACHED_X_MESH_LOADER_PROTOTYPE,
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=X_MESH_LOADER_USER_VAR_UPDATES,
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
