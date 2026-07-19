#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_user_var_updates,
    current_struct_fields_batch,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_STRUCT_FIELDS = {
    "BodNode": {
        0x04: ("list_flags", "uint32_t"),
        0x08: ("list_prev", "BodNode*"),
        0x0C: ("list_next", "BodNode*"),
    },
    "BodList": {
        0x04: ("first", "BodNode*"),
    },
    "GameRoot": {
        0x05A8: ("active_bod_list", "BodList"),
    },
}

# Both pickup allocators inline the same BodList::add_bod operation. The list
# head address and every reload borrow GameRoot::active_bod_list; the selected
# SubHealth or JetPack remains the owning actor at the zero-offset BodNode base.
# Keep these exact physical lifetimes separate from the allocator prototypes
# and pool cursors maintained by the broader path/runtime replays.
PICKUP_LIST_USER_VAR_UPDATES = (
    (
        "spawn_track_health_pickup",
        "RegisterVariableSourceType",
        168,
        67,
        "bod_list_first_ref",
        "BodNode**",
    ),
    (
        "spawn_track_health_pickup",
        "RegisterVariableSourceType",
        199,
        68,
        "old_first",
        "BodNode*",
    ),
    (
        "spawn_track_health_pickup",
        "RegisterVariableSourceType",
        201,
        71,
        "inserted_node",
        "BodNode*",
    ),
    (
        "spawn_track_health_pickup",
        "RegisterVariableSourceType",
        207,
        68,
        "old_first_reload",
        "BodNode*",
    ),
    (
        "spawn_track_health_pickup",
        "RegisterVariableSourceType",
        213,
        68,
        "inserted_node_reload",
        "BodNode*",
    ),
    (
        "spawn_track_health_pickup",
        "RegisterVariableSourceType",
        189,
        67,
        "installed_first",
        "BodNode*",
    ),
    (
        "spawn_track_jetpack_pickup",
        "RegisterVariableSourceType",
        233,
        66,
        "bod_list_first_ref",
        "BodNode**",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the exact intrusive-list head lifetimes in the "
            "health and jetpack pickup allocators."
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
        help="Header documenting the canonical BodNode/BodList/GameRoot layouts.",
    )
    return parser.parse_args()


def verify_owner_layouts(target: str) -> dict[str, object]:
    layouts = current_struct_fields_batch(
        REPO_ROOT,
        target=target,
        struct_names=EXPECTED_STRUCT_FIELDS,
    )
    mismatches: list[str] = []
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
            "canonical intrusive-list ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_pickup_list_owner_layouts",
        "status": "verified",
        "structs": tuple(EXPECTED_STRUCT_FIELDS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        verify_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=PICKUP_LIST_USER_VAR_UPDATES,
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
