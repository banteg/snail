#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys

from _narrow_sync import run_bn
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
FUNCTION_ADDRESS = 0x4374B0
FUNCTION_NAME = "initialize_subgame"
EXPECTED_PROTOTYPE = "void __thiscall(struct SubgameRuntime* game)"
STALE_PROTOTYPE = "void __fastcall(struct Game* game)"
SUBGAME_RUNTIME_SIZE = 0x1272838


def _repair_code(*, apply: bool) -> str:
    template = r'''
ADDRESS = __ADDRESS__
NAME = __NAME__
EXPECTED_PROTOTYPE = __EXPECTED_PROTOTYPE__
STALE_PROTOTYPE = __STALE_PROTOTYPE__
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
    receiver = variable_record(fn, parameters[0]) if len(parameters) == 1 else None
    color_candidates = [
        var
        for var in fn.vars
        if str(var.source_type).endswith("StackVariableSourceType")
        and int(var.index) == 0
        and int(var.storage) == -24
    ]
    color = variable_record(fn, color_candidates[0]) if len(color_candidates) == 1 else None
    return {
        "parameter_count": len(parameters),
        "receiver": receiver,
        "color_candidate_count": len(color_candidates),
        "color": color,
    }


def annotations_are_current(value):
    receiver = value["receiver"]
    color = value["color"]
    return (
        value["parameter_count"] == 1
        and receiver is not None
        and receiver["name"] == "game"
        and receiver["type"] == "struct SubgameRuntime*"
        and value["color_candidate_count"] == 1
        and color is not None
        and color["name"] == "color"
        and color["type"] == "struct tColour"
    )


def apply_annotations(fn):
    value = annotations(fn)
    if value["parameter_count"] != 1 or value["receiver"] is None:
        raise RuntimeError(f"unexpected receiver candidates: {value!r}")
    if value["color_candidate_count"] != 1 or value["color"] is None:
        raise RuntimeError(f"unexpected color candidates: {value!r}")

    receiver = list(fn.parameter_vars)[0]
    receiver_type, _ = bv.parse_type_string("SubgameRuntime*")
    fn.create_user_var(receiver, receiver_type, "game")

    color_var = find_variable(fn, value["color"])
    color_type, _ = bv.parse_type_string("tColour")
    fn.create_user_var(color_var, color_type, "color")
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
    tags = [str(tag) for tag in fn.tags]
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
    if observed_prototype not in {EXPECTED_PROTOTYPE, STALE_PROTOTYPE}:
        conflicts.append("unexpected_prototype")

    stale = observed_prototype == STALE_PROTOTYPE
    allowed_user_var_keys = {
        ("VariableSourceType.RegisterVariableSourceType", 0, 67),
        ("VariableSourceType.StackVariableSourceType", 0, -24),
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
        conflicts.append("function_has_tags")
    if stale and unexpected_user_vars:
        conflicts.append("function_has_unpreserved_user_vars")
    if before_annotations["parameter_count"] != 1:
        conflicts.append("unexpected_receiver_candidates")
    if before_annotations["color_candidate_count"] != 1:
        conflicts.append("unexpected_color_candidates")

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
            bv.update_analysis_and_wait()
            bv.file.save_auto_snapshot()

        try:
            expected_type, _ = bv.parse_type_string(
                "void __thiscall initialize_subgame(SubgameRuntime* game)"
            )
            bv.remove_function(fn)
            recreated = True
            repaired = bv.add_function(
                ADDRESS,
                old_platform,
                auto_discovered=False,
                func_type=expected_type,
            )
            if repaired is None:
                raise RuntimeError("failed to recreate initialize_subgame")
            repaired.name = NAME
            repaired.set_user_type(expected_type)
            bv.update_analysis_and_wait()
            apply_annotations(repaired)

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
    return (
        template.replace("__ADDRESS__", hex(FUNCTION_ADDRESS))
        .replace("__NAME__", repr(FUNCTION_NAME))
        .replace("__EXPECTED_PROTOTYPE__", repr(EXPECTED_PROTOTYPE))
        .replace("__STALE_PROTOTYPE__", repr(STALE_PROTOTYPE))
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
            "Inspect or narrowly repair initialize_subgame when a stale Binary Ninja "
            "Game* named-type identity blocks the proven SubgameRuntime receiver."
        )
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector.",
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
    payload = run_bn(
        REPO_ROOT,
        "py",
        "exec",
        "--target",
        args.target,
        "--format",
        "json",
        "--code",
        _repair_code(apply=args.apply),
    )
    result = _unwrap_result(payload)
    json.dump(
        {
            "tool": "binary_ninja",
            "target": args.target,
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
