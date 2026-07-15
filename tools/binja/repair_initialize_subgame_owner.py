#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys

from _narrow_sync import run_bn
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
SUBGAME_RUNTIME_SIZE = 0x1272838

FUNCTION_SPECS = {
    "initialize_subgame": {
        "address": 0x4374B0,
        "expected_prototype": "void __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "void __fastcall(struct Game* game)",
        "declaration": "void __thiscall initialize_subgame(SubgameRuntime* game)",
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": -24,
                "name": "color",
                "type": "struct tColour",
            },
        ),
    },
    "build_subgame_level": {
        "address": 0x437EB0,
        "expected_prototype": (
            "void __thiscall(struct SubgameRuntime* game, int32_t level_index)"
        ),
        "stale_prototype": "void __thiscall(struct Game* game, int32_t level_index)",
        "declaration": (
            "void __thiscall build_subgame_level(SubgameRuntime* game, "
            "int32_t level_index)"
        ),
        "parameter_count": 2,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 4,
                "name": "level_index",
                "type": "int32_t",
            },
        ),
    },
    "destroy_subgame": {
        "address": 0x438850,
        "expected_prototype": "void __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "void __fastcall(struct Game* game)",
        "declaration": "void __thiscall destroy_subgame(SubgameRuntime* game)",
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "update_subgame": {
        "address": 0x438B90,
        "expected_prototype": "void __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "void __fastcall(struct Game* game)",
        "declaration": "void __thiscall update_subgame(SubgameRuntime* game)",
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "remove_subgame_bods": {
        "address": 0x440910,
        "expected_prototype": "void __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "void __fastcall(struct Game* game)",
        "declaration": "void __thiscall remove_subgame_bods(SubgameRuntime* game)",
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "merge_track_tile_runs": {
        "address": 0x435180,
        "expected_prototype": "int32_t __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "int32_t __thiscall(struct Game* game)",
        "declaration": (
            "int32_t __thiscall merge_track_tile_runs(SubgameRuntime* game)"
        ),
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "build_track_fringe_objects": {
        "address": 0x434BE0,
        "expected_prototype": "int32_t __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "int32_t __thiscall(struct Game* game)",
        # Binary Ninja derives this address tag from the function's mismatched
        # incoming stack states. It is analyzer-owned evidence, not a user
        # annotation. The guarded recreation preserves it through mutation so
        # fresh analysis, rather than the repair itself, decides whether it remains.
        "allowed_auto_tag_types": ("Unresolved Stack Pointer Value",),
        "declaration": (
            "int32_t __thiscall build_track_fringe_objects(SubgameRuntime* game)"
        ),
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "promote_track_tiles_to_fringe_variants": {
        "address": 0x4355F0,
        "expected_prototype": "int32_t __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "int32_t __thiscall(struct Game* game)",
        "declaration": (
            "int32_t __thiscall promote_track_tiles_to_fringe_variants("
            "SubgameRuntime* game)"
        ),
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "harmonize_center_lane_floor_slide_variants": {
        "address": 0x4356F0,
        "expected_prototype": "int32_t __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "int32_t __thiscall(struct Game* game)",
        "declaration": (
            "int32_t __thiscall harmonize_center_lane_floor_slide_variants("
            "SubgameRuntime* game)"
        ),
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "select_track_tile_edge_variants": {
        "address": 0x435A80,
        "expected_prototype": "int32_t __thiscall(struct SubgameRuntime* game)",
        "stale_prototype": "int32_t __thiscall(struct Game* game)",
        "declaration": (
            "int32_t __thiscall select_track_tile_edge_variants("
            "SubgameRuntime* game)"
        ),
        "parameter_count": 1,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
        ),
    },
    "get_track_grid_cell_at_world_position": {
        "address": 0x43D410,
        "expected_prototype": (
            "struct TrackRowCell* __thiscall("
            "struct SubgameRuntime* game, struct Vec3* position)"
        ),
        "stale_prototype": (
            "struct TrackRowCell* __thiscall("
            "struct Game* game, struct Vec3* position)"
        ),
        "declaration": (
            "TrackRowCell* __thiscall get_track_grid_cell_at_world_position("
            "SubgameRuntime* game, Vec3* position)"
        ),
        "parameter_count": 2,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 4,
                "name": "position",
                "type": "struct Vec3*",
            },
        ),
    },
    "sample_track_floor_height_at_position": {
        "address": 0x43D4D0,
        "expected_prototype": (
            "double __thiscall(struct SubgameRuntime* game, struct Vec3* position)"
        ),
        "stale_prototype": (
            "double __thiscall(struct Game* game, struct Vec3* position)"
        ),
        "declaration": (
            "double __thiscall sample_track_floor_height_at_position("
            "SubgameRuntime* game, Vec3* position)"
        ),
        "parameter_count": 2,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 4,
                "name": "position",
                "type": "struct Vec3*",
            },
        ),
    },
    "spawn_track_health_pickup": {
        "address": 0x43D6C0,
        "expected_prototype": (
            "void __thiscall(struct SubgameRuntime* game, "
            "struct TrackRowCell* cell, struct Player* player)"
        ),
        "stale_prototype": (
            "struct TrackPickupRuntime* __thiscall(struct Game* game, "
            "struct TrackRowCell* cell, struct Player* player)"
        ),
        "declaration": (
            "void __thiscall spawn_track_health_pickup("
            "SubgameRuntime* game, TrackRowCell* cell, Player* player)"
        ),
        "parameter_count": 3,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 4,
                "name": "cell",
                "type": "struct TrackRowCell*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 8,
                "name": "player",
                "type": "struct Player*",
            },
        ),
    },
    "spawn_track_jetpack_pickup": {
        "address": 0x43D890,
        "expected_prototype": (
            "void __thiscall(struct SubgameRuntime* game, "
            "struct TrackRowCell* cell, struct Player* player)"
        ),
        "stale_prototype": (
            "struct TrackPickupRuntime* __thiscall(struct Game* game, "
            "struct TrackRowCell* cell, struct Player* player)"
        ),
        "declaration": (
            "void __thiscall spawn_track_jetpack_pickup("
            "SubgameRuntime* game, TrackRowCell* cell, Player* player)"
        ),
        "parameter_count": 3,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 4,
                "name": "cell",
                "type": "struct TrackRowCell*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 8,
                "name": "player",
                "type": "struct Player*",
            },
        ),
    },
    "get_track_runtime_cell_at_world_z": {
        "address": 0x43D480,
        "expected_prototype": (
            "struct SubRow* __thiscall("
            "struct SubgameRuntime* game, struct Vec3* position)"
        ),
        "stale_prototype": (
            "struct TrackAttachmentRuntimeRow* __thiscall("
            "struct Game* game, struct Vec3* position)"
        ),
        "legacy_prototypes": (
            "struct TrackAttachmentRuntimeRow* __thiscall("
            "struct SubgameRuntime* game, struct Vec3* position)",
        ),
        "declaration": (
            "SubRow* __thiscall "
            "get_track_runtime_cell_at_world_z(SubgameRuntime* game, Vec3* position)"
        ),
        "parameter_count": 2,
        "variables": (
            {
                "source_type": "VariableSourceType.RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "name": "game",
                "type": "struct SubgameRuntime*",
            },
            {
                "source_type": "VariableSourceType.StackVariableSourceType",
                "index": 0,
                "storage": 4,
                "name": "position",
                "type": "struct Vec3*",
            },
        ),
    },
}


def _repair_code(
    *, function_name: str, spec: dict[str, object], apply: bool
) -> str:
    template = r'''
SPEC = __SPEC__
ADDRESS = SPEC["address"]
NAME = SPEC["name"]
EXPECTED_PROTOTYPE = SPEC["expected_prototype"]
STALE_PROTOTYPE = SPEC["stale_prototype"]
STALE_PROTOTYPES = {STALE_PROTOTYPE, *SPEC.get("legacy_prototypes", ())}
DECLARATION = SPEC["declaration"]
EXPECTED_PARAMETER_COUNT = SPEC["parameter_count"]
EXPECTED_VARIABLES = SPEC["variables"]
ALLOWED_AUTO_TAG_TYPES = set(SPEC.get("allowed_auto_tag_types", ()))
SUBGAME_RUNTIME_SIZE = __SUBGAME_RUNTIME_SIZE__
APPLY = __APPLY__


def variable_record(fn, var):
    return {
        "name": str(var.name),
        "type": str(var.type),
        "source_type": str(var.source_type),
        "index": int(var.index),
        "storage": int(var.storage),
        "user_defined": bool(fn.is_var_user_defined(var)),
    }


def tag_record(fn, entry):
    arch, address, tag = entry
    auto_tags = fn.get_tags_at(address, arch, auto=True)
    return {
        "architecture": str(arch.name),
        "address": hex(int(address)),
        "type": str(tag.type.name),
        "data": str(tag.data),
        "auto": any(candidate.id == tag.id for candidate in auto_tags),
    }


def restore_preserved_auto_tags(fn, entries):
    if not entries:
        return

    for arch, address, tag in entries:
        current = fn.get_tags_at(address, arch, auto=True)
        if any(
            str(candidate.type.name) == str(tag.type.name)
            and str(candidate.data) == str(tag.data)
            for candidate in current
        ):
            continue
        fn.add_tag(
            str(tag.type.name),
            str(tag.data),
            int(address),
            auto=True,
            arch=arch,
        )
    bv.update_analysis_and_wait()

    missing = []
    for arch, address, tag in entries:
        current = fn.get_tags_at(address, arch, auto=True)
        if not any(
            str(candidate.type.name) == str(tag.type.name)
            and str(candidate.data) == str(tag.data)
            for candidate in current
        ):
            missing.append(
                {
                    "address": hex(int(address)),
                    "type": str(tag.type.name),
                    "data": str(tag.data),
                }
            )
    if missing:
        raise RuntimeError(f"failed to preserve auto tags: {missing!r}")


def find_variable(fn, record):
    candidates = [
        var
        for var in fn.vars
        if str(var.source_type) == record["source_type"]
        and int(var.index) == record["index"]
        and int(var.storage) == record["storage"]
    ]
    if len(candidates) != 1:
        raise RuntimeError(
            f"expected one variable for {record!r}, found {len(candidates)}"
        )
    return candidates[0]


def annotations(fn):
    parameters = list(fn.parameter_vars)
    variables = []
    for expected in EXPECTED_VARIABLES:
        candidates = [
            var
            for var in fn.vars
            if str(var.source_type) == expected["source_type"]
            and int(var.index) == expected["index"]
            and int(var.storage) == expected["storage"]
        ]
        variables.append(
            {
                "expected": expected,
                "candidate_count": len(candidates),
                "observed": (
                    variable_record(fn, candidates[0]) if len(candidates) == 1 else None
                ),
            }
        )
    return {
        "parameter_count": len(parameters),
        "variables": variables,
    }


def annotations_are_current(value):
    return (
        value["parameter_count"] == EXPECTED_PARAMETER_COUNT
        and all(
            entry["candidate_count"] == 1
            and entry["observed"] is not None
            and entry["observed"]["name"] == entry["expected"]["name"]
            and entry["observed"]["type"] == entry["expected"]["type"]
            for entry in value["variables"]
        )
    )


def apply_annotations(fn):
    value = annotations(fn)
    if value["parameter_count"] != EXPECTED_PARAMETER_COUNT:
        raise RuntimeError(f"unexpected parameter count: {value!r}")
    if any(entry["candidate_count"] != 1 for entry in value["variables"]):
        raise RuntimeError(f"unexpected variable candidates: {value!r}")

    for entry in value["variables"]:
        expected = entry["expected"]
        var = find_variable(fn, expected)
        var_type, _ = bv.parse_type_string(expected["type"])
        fn.create_user_var(var, var_type, expected["name"])
    bv.update_analysis_and_wait()


fn = bv.get_function_at(ADDRESS)
if fn is None:
    result = {
        "status": "conflict",
        "reason": "missing_function",
        "address": hex(ADDRESS),
    }
else:
    owner_type = bv.get_type_by_name("SubgameRuntime")
    comments = {hex(int(address)): str(text) for address, text in fn.comments.items()}
    tag_entries = list(fn.tags)
    tags = [tag_record(fn, entry) for entry in tag_entries]
    preserved_auto_tags = [
        entry
        for entry, record in zip(tag_entries, tags)
        if record["auto"] and record["type"] in ALLOWED_AUTO_TAG_TYPES
    ]
    user_vars = [variable_record(fn, var) for var in fn.vars if fn.is_var_user_defined(var)]
    before_annotations = annotations(fn)
    observed_prototype = str(fn.type)
    observed = {
        "address": hex(int(fn.start)),
        "name": str(fn.name),
        "prototype": observed_prototype,
        "comments": comments,
        "tags": tags,
        "user_vars": user_vars,
        "annotations": before_annotations,
    }

    conflicts = []
    if int(fn.start) != ADDRESS:
        conflicts.append("function_start_changed")
    if str(fn.name) != NAME:
        conflicts.append("function_name_changed")
    if owner_type is None or int(owner_type.width) != SUBGAME_RUNTIME_SIZE:
        conflicts.append("SubgameRuntime_layout_changed")
    if observed_prototype != EXPECTED_PROTOTYPE and observed_prototype not in STALE_PROTOTYPES:
        conflicts.append("unexpected_prototype")

    stale = observed_prototype in STALE_PROTOTYPES
    allowed_user_var_keys = {
        (record["source_type"], record["index"], record["storage"])
        for record in EXPECTED_VARIABLES
    }
    unexpected_user_vars = [
        record
        for record in user_vars
        if (record["source_type"], record["index"], record["storage"])
        not in allowed_user_var_keys
    ]
    if stale and comments:
        conflicts.append("function_has_comments")
    if stale and tags:
        unexpected_tags = [
            record
            for record in tags
            if not (
                record["auto"] and record["type"] in ALLOWED_AUTO_TAG_TYPES
            )
        ]
        if unexpected_tags:
            conflicts.append("function_has_tags")
    if stale and unexpected_user_vars:
        conflicts.append("function_has_unpreserved_user_vars")
    if before_annotations["parameter_count"] != EXPECTED_PARAMETER_COUNT:
        conflicts.append("unexpected_parameter_count")
    if any(
        entry["candidate_count"] != 1
        for entry in before_annotations["variables"]
    ):
        conflicts.append("unexpected_variable_candidates")

    if conflicts:
        result = {
            "status": "conflict",
            "reason": "guard_failed",
            "conflicts": conflicts,
            "observed": observed,
        }
    elif not APPLY:
        current = (
            observed_prototype == EXPECTED_PROTOTYPE
            and annotations_are_current(before_annotations)
        )
        result = {
            "status": "current" if current else "planned",
            "operation": (
                "none" if current else "recreate_function" if stale else "repair_annotations"
            ),
            "observed": observed,
            "expected_prototype": EXPECTED_PROTOTYPE,
            "dry_run": True,
        }
    elif observed_prototype == EXPECTED_PROTOTYPE:
        if annotations_are_current(before_annotations):
            result = {
                "status": "current",
                "operation": "none",
                "observed": observed,
                "snapshot_saved": False,
                "dry_run": False,
            }
        else:
            undo = bv.begin_undo_actions()
            undo_closed = False
            try:
                apply_annotations(fn)
                after_annotations = annotations(fn)
                if not annotations_are_current(after_annotations):
                    raise RuntimeError(f"annotation verification failed: {after_annotations!r}")
                bv.commit_undo_actions(undo)
                undo_closed = True
                snapshot_saved = bv.file.save_auto_snapshot()
            except Exception:
                if not undo_closed:
                    bv.revert_undo_actions(undo)
                    bv.update_analysis_and_wait()
                raise
            result = {
                "status": "repaired",
                "operation": "repair_annotations",
                "before": observed,
                "after": {
                    "prototype": str(fn.type),
                    "annotations": after_annotations,
                },
                "snapshot_saved": snapshot_saved,
                "dry_run": False,
            }
    else:
        old_type = fn.type
        old_platform = fn.platform
        old_user_vars = user_vars
        recreated = False

        def restore_old_function():
            current = bv.get_function_at(ADDRESS)
            if current is not None:
                bv.remove_function(current)
            restored = bv.add_function(
                ADDRESS,
                old_platform,
                auto_discovered=False,
                func_type=old_type,
            )
            if restored is None:
                raise RuntimeError("failed to recreate the original function during rollback")
            restored.name = NAME
            restored.set_user_type(old_type)
            bv.update_analysis_and_wait()
            for record in old_user_vars:
                var = find_variable(restored, record)
                var_type, _ = bv.parse_type_string(record["type"])
                restored.create_user_var(var, var_type, record["name"])
            restore_preserved_auto_tags(restored, preserved_auto_tags)
            bv.file.save_auto_snapshot()

        try:
            expected_type, _ = bv.parse_type_string(DECLARATION)
            bv.remove_function(fn)
            recreated = True
            repaired = bv.add_function(
                ADDRESS,
                old_platform,
                auto_discovered=False,
                func_type=expected_type,
            )
            if repaired is None:
                raise RuntimeError(f"failed to recreate {NAME}")
            repaired.name = NAME
            repaired.set_user_type(expected_type)
            bv.update_analysis_and_wait()
            apply_annotations(repaired)
            restore_preserved_auto_tags(repaired, preserved_auto_tags)

            after_annotations = annotations(repaired)
            after_prototype = str(repaired.type)
            if after_prototype != EXPECTED_PROTOTYPE:
                raise RuntimeError(
                    f"prototype verification failed: {after_prototype!r}"
                )
            if not annotations_are_current(after_annotations):
                raise RuntimeError(f"annotation verification failed: {after_annotations!r}")
            snapshot_saved = bv.file.save_auto_snapshot()
        except Exception as repair_error:
            if recreated:
                try:
                    restore_old_function()
                except Exception as rollback_error:
                    raise RuntimeError(
                        f"repair failed ({repair_error}); rollback also failed ({rollback_error})"
                    ) from repair_error
            raise

        result = {
            "status": "repaired",
            "operation": "recreate_function",
            "before": observed,
            "after": {
                "prototype": str(repaired.type),
                "annotations": after_annotations,
            },
            "snapshot_saved": snapshot_saved,
            "dry_run": False,
        }
'''
    embedded_spec = {
        **spec,
        "name": function_name,
        "variables": list(spec["variables"]),
    }
    return (
        template.replace("__SPEC__", repr(embedded_spec))
        .replace("__SUBGAME_RUNTIME_SIZE__", hex(SUBGAME_RUNTIME_SIZE))
        .replace("__APPLY__", repr(apply))
    )


def _unwrap_result(payload: object) -> dict[str, object]:
    if isinstance(payload, dict) and isinstance(payload.get("result"), dict):
        return payload["result"]
    if isinstance(payload, dict):
        return payload
    raise RuntimeError(f"unexpected Binary Ninja response: {payload!r}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Inspect or narrowly repair a cataloged subgame function when a stale "
            "Binary Ninja Game* named-type identity blocks its proven SubgameRuntime "
            "receiver."
        )
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector.",
    )
    parser.add_argument(
        "--function",
        dest="function_name",
        choices=tuple(FUNCTION_SPECS),
        default="initialize_subgame",
        help="Cataloged function to inspect or repair. Defaults to initialize_subgame.",
    )
    parser.add_argument(
        "--apply",
        action="store_true",
        help=(
            "Apply the guarded repair and save a snapshot. Without this flag the tool "
            "is read-only. Function recreation is used only for the exact known stale ABI."
        ),
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    spec = FUNCTION_SPECS[args.function_name]
    payload = run_bn(
        REPO_ROOT,
        "py",
        "exec",
        "--target",
        args.target,
        "--format",
        "json",
        "--code",
        _repair_code(
            function_name=args.function_name,
            spec=spec,
            apply=args.apply,
        ),
    )
    result = _unwrap_result(payload)
    json.dump(
        {
            "tool": "binary_ninja",
            "target": args.target,
            "function": args.function_name,
            "apply": args.apply,
            "result": result,
        },
        sys.stdout,
        indent=2,
        sort_keys=True,
    )
    sys.stdout.write("\n")
    return 1 if result.get("status") == "conflict" else 0


if __name__ == "__main__":
    raise SystemExit(main())
