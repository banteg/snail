from __future__ import annotations

import json
from pathlib import Path
import re
import subprocess
import sys
from typing import Iterable


SPILL_PATH_RE = re.compile(r"^path:\s+(?P<path>.+)$", re.MULTILINE)
STRUCT_FIELD_RE = re.compile(
    r"^(?P<offset>0x[0-9a-fA-F]+):\s+(?P<type>.+?)\s+(?P<name>[A-Za-z_][A-Za-z0-9_]*)$"
)
STRUCT_SIZE_RE = re.compile(r"^struct\s+\S+\s+//\s+size=(?P<size>0x[0-9a-fA-F]+|\d+)$", re.MULTILINE)

FieldUpdate = tuple[str, str, str]
ProtoUpdate = tuple[str, str]
SymbolUpdate = tuple[str, str]
SymbolRemoval = tuple[str, str]
DataVarUpdate = tuple[str, str]
DataVarRemoval = tuple[str, str]
IntDisplayUpdate = tuple[str, str, str, int, int, str, str, str]
InstructionCommentUpdate = tuple[str, str, str, str]
SplitVarSpec = tuple[str, int, int]
SplitVarDefinition = tuple[str, str, str, int, int]
SplitUserVarUpdate = tuple[
    str,
    Iterable[SplitVarDefinition],
    SplitVarSpec,
    str,
    str,
]
StructUpdateGroup = tuple[str, Iterable[FieldUpdate]]
UserVarUpdate = tuple[str, str, int, int, str, str]
UserVarRemoval = tuple[str, str, int, int, str, str]
TypeRename = tuple[str, str]


def _read_bn_spill(stdout: str, stderr: str) -> tuple[Path | None, object | None]:
    spill_match = SPILL_PATH_RE.search(stdout) or SPILL_PATH_RE.search(stderr)
    if spill_match is None:
        return None, None

    spill_path = Path(spill_match.group("path")).expanduser()
    try:
        return spill_path, json.loads(spill_path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return spill_path, None


def _summarize_bn_failure(payload: object) -> str:
    if not isinstance(payload, dict):
        return repr(payload)[:4000]

    summary = {
        key: payload[key]
        for key in ("success", "preview", "committed", "message")
        if key in payload
    }
    failure_keys = (
        "op",
        "status",
        "function",
        "identifier",
        "address",
        "struct_name",
        "old_name",
        "new_name",
        "offset",
        "field_name",
        "before_prototype",
        "expected_prototype",
        "observed",
        "message",
        "error",
    )
    failures = []
    results = payload.get("results")
    if isinstance(results, list):
        for entry in results:
            if not isinstance(entry, dict):
                continue
            if entry.get("status") not in {"verification_failed", "failed", "error"} and not entry.get(
                "error"
            ):
                continue
            failures.append({key: entry[key] for key in failure_keys if key in entry})
            if len(failures) == 10:
                break
    if failures:
        summary["failures"] = failures
    return json.dumps(summary, indent=2, sort_keys=True)


def run_bn(repo_root: Path, *args: str) -> object:
    completed = subprocess.run(
        ["bn", *args],
        cwd=repo_root,
        check=False,
        text=True,
        capture_output=True,
    )
    stdout = completed.stdout.strip()
    stderr = completed.stderr.strip()
    spill_path, spilled = _read_bn_spill(stdout, stderr)
    if completed.returncode != 0:
        if spilled is not None:
            detail = f"details from {spill_path}:\n{_summarize_bn_failure(spilled)}"
        else:
            detail = stderr or stdout or "no diagnostic output"
        raise RuntimeError(
            f"bn {' '.join(args)} failed with exit code {completed.returncode}:\n{detail}"
        )

    if spill_path is not None:
        if spilled is None:
            raise RuntimeError(f"unable to read Binary Ninja spill payload from {spill_path}")
        return spilled
    if not stdout:
        if not stderr:
            return {}
        return {"stderr": stderr}
    if stdout[0] in "[{":
        return json.loads(stdout)
    result: dict[str, object] = {"stdout": stdout}
    if stderr:
        result["stderr"] = stderr
    return result


def run_previewed_bn_mutation(repo_root: Path, *args: str) -> dict[str, object]:
    preview = run_bn(repo_root, *args, "--preview", "--format", "json")
    if (
        not isinstance(preview, dict)
        or preview.get("success") is not True
        or preview.get("preview") is not True
        or preview.get("committed") is not False
    ):
        raise RuntimeError(f"Binary Ninja mutation preview failed for {args!r}: {preview!r}")
    applied = run_bn(repo_root, *args, "--format", "json")
    if (
        not isinstance(applied, dict)
        or applied.get("success") is not True
        or applied.get("committed") is not True
    ):
        raise RuntimeError(f"Binary Ninja mutation apply failed for {args!r}: {applied!r}")
    return {
        "preview": {
            "success": preview.get("success"),
            "message": preview.get("message"),
            "affected_type_count": len(preview.get("affected_types", ())),
            "affected_function_count": len(preview.get("affected_functions", ())),
        },
        "apply": applied,
    }


def _batch_python_code(
    operations: list[dict[str, object]], *, preview: bool
) -> str:
    template = """
import json

operations = json.loads(__OPERATIONS_JSON__)
preview = __PREVIEW__


def find_function(identifier):
    text = str(identifier)
    try:
        address = int(text, 0)
    except ValueError:
        functions = list(bv.get_functions_by_name(text))
        if len(functions) != 1:
            raise RuntimeError(
                f"expected one function named {text}, found {len(functions)}"
            )
        return functions[0]
    function = bv.get_function_at(address)
    if function is None:
        raise RuntimeError(f"function not found at {address:#x}")
    return function


def normalize_function_type(value):
    return str(value).replace(" __pure", "")


def find_member(type_obj, offset):
    for member in list(getattr(type_obj, "members", ())):
        if int(getattr(member, "offset", -1)) == offset:
            return member
    return None


def function_variables(function):
    by_identity = {}
    variable_sources = [function.vars]
    for il in (
        getattr(function, "hlil", None),
        getattr(function, "mlil", None),
    ):
        if il is not None:
            variable_sources.append(il.vars)
    for variables in variable_sources:
        for variable in variables:
            identity = (
                str(variable.source_type).split(".")[-1],
                int(variable.index),
                int(variable.storage),
            )
            by_identity.setdefault(identity, variable)
    return list(by_identity.values())


def find_variable(function, operation):
    expected_source = str(operation["source_type"]).split(".")[-1]
    expected_index = int(operation["index"])
    expected_storage = int(operation["storage"])
    candidates = [
        variable
        for variable in function_variables(function)
        if str(variable.source_type).split(".")[-1] == expected_source
        and int(variable.index) == expected_index
        and int(variable.storage) == expected_storage
    ]
    if len(candidates) != 1:
        raise RuntimeError(
            f"expected one {expected_source} variable at index {expected_index}, "
            f"storage {expected_storage}, found {len(candidates)}"
        )
    return candidates[0]


parsed_type_cache = {}


def parse_type_once(type_text):
    key = str(type_text)
    if key not in parsed_type_cache:
        parsed_type_cache[key] = bv.parse_type_string(key)
    return parsed_type_cache[key]


state = bv.begin_undo_actions()
undo_closed = False
results = []
affected_functions = []
affected_types = []
prototype_reanalysis_identifiers = []
user_var_reanalysis_identifiers = []
int_display_reanalysis_identifiers = []
snapshot_saved = False
analysis_changed = False
analysis_skip_override_restorations = []
try:
    for operation in operations:
        kind = operation["op"]
        if kind == "rename_type":
            old_name = str(operation["old_name"])
            new_name = str(operation["new_name"])
            old_type = bv.get_type_by_name(old_name)
            new_type = bv.get_type_by_name(new_name)
            if old_type is None:
                raise RuntimeError(
                    f"cannot rename missing type {old_name} to {new_name}"
                )
            if new_type is not None:
                raise RuntimeError(
                    f"refusing to rename {old_name}: target type {new_name} "
                    "already exists"
                )
            analysis_changed = True
            bv.rename_type(old_name, new_name)
            results.append({
                "op": kind,
                "old_name": old_name,
                "new_name": new_name,
                "before": str(old_type),
                "changed": True,
            })
            affected_types.extend((old_name, new_name))
            continue

        if kind == "undefine_symbol":
            address = int(str(operation["address"]), 0)
            expected_name = str(operation["expected_name"])
            symbol = bv.get_symbol_at(address)
            before = str(symbol.name) if symbol is not None else None
            if symbol is not None and before != expected_name:
                raise RuntimeError(
                    f"refusing to undefine unexpected symbol at {address:#x}: "
                    f"expected {expected_name}, found {before}"
                )
            changed = symbol is not None
            if changed:
                analysis_changed = True
                bv.undefine_user_symbol(symbol)
            results.append({
                "op": kind,
                "address": hex(address),
                "expected_name": expected_name,
                "before": before,
                "changed": changed,
            })
            continue

        if kind == "set_prototype":
            function = find_function(operation["identifier"])
            expected_type, _ = parse_type_once(operation["prototype"])
            before = str(function.type)
            expected = str(expected_type)
            changed = before != expected
            if changed:
                analysis_changed = True
                try:
                    function.set_user_type(expected_type)
                except TypeError:
                    function.set_user_type(expected)
                # Binary Ninja can retain the previously materialized function
                # type until this function is explicitly queued again. This is
                # especially visible when changing a fixed CRT prototype to a
                # variadic one: update_analysis_and_wait() alone is not enough.
                function.reanalyze()
                prototype_reanalysis_identifiers.append(
                    str(operation["identifier"])
                )
            results.append({
                "op": kind,
                "identifier": str(operation["identifier"]),
                "function": str(function.name),
                "address": hex(int(function.start)),
                "before": before,
                "expected": expected,
                "changed": changed,
            })
            affected_functions.append(str(function.name))
            continue

        if kind == "user_var_set":
            function = find_function(operation["identifier"])
            variable = find_variable(function, operation)
            expected_type, _ = parse_type_once(operation["variable_type"])
            expected_name = str(operation["variable_name"])
            before = {
                "name": str(variable.name),
                "type": str(variable.type),
                "user_defined": bool(function.is_var_user_defined(variable)),
            }
            expected = {
                "name": expected_name,
                "type": str(expected_type),
                "user_defined": True,
            }
            changed = before != expected
            if changed:
                analysis_changed = True
                function.create_user_var(variable, expected_type, expected_name)
                user_var_reanalysis_identifiers.append(
                    str(operation["identifier"])
                )
            results.append({
                "op": kind,
                "identifier": str(operation["identifier"]),
                "function": str(function.name),
                "address": hex(int(function.start)),
                "source_type": str(operation["source_type"]),
                "index": int(operation["index"]),
                "storage": int(operation["storage"]),
                "variable_name": expected_name,
                "variable_type": str(expected_type),
                "before": before,
                "expected": expected,
                "changed": changed,
            })
            affected_functions.append(str(function.name))
            continue

        if kind == "user_var_delete":
            function = find_function(operation["identifier"])
            variable = find_variable(function, operation)
            expected_type, _ = parse_type_once(operation["variable_type"])
            expected_name = str(operation["variable_name"])
            before = {
                "name": str(variable.name),
                "type": str(variable.type),
                "user_defined": bool(function.is_var_user_defined(variable)),
            }
            if before["user_defined"] and before != {
                "name": expected_name,
                "type": str(expected_type),
                "user_defined": True,
            }:
                raise RuntimeError(
                    "refusing to delete an unexpected user variable: "
                    f"expected {expected_name} as {expected_type}, found {before}"
                )
            changed = before["user_defined"]
            if changed:
                analysis_changed = True
                function.delete_user_var(variable)
                user_var_reanalysis_identifiers.append(
                    str(operation["identifier"])
                )
            results.append({
                "op": kind,
                "identifier": str(operation["identifier"]),
                "function": str(function.name),
                "address": hex(int(function.start)),
                "source_type": str(operation["source_type"]),
                "index": int(operation["index"]),
                "storage": int(operation["storage"]),
                "variable_name": expected_name,
                "variable_type": str(expected_type),
                "before": before,
                "changed": changed,
            })
            affected_functions.append(str(function.name))
            continue

        if kind == "reanalyze_function":
            function = find_function(operation["identifier"])
            before = {
                "name": str(function.name),
                "address": hex(int(function.start)),
            }
            analysis_changed = True
            function.reanalyze()
            results.append({
                "op": kind,
                "identifier": str(operation["identifier"]),
                "function": str(function.name),
                "address": hex(int(function.start)),
                "before": before,
                "changed": True,
            })
            affected_functions.append(str(function.name))
            continue

        if kind == "ensure_function_analysis":
            from binaryninja import FunctionAnalysisSkipOverride

            function = find_function(operation["identifier"])
            before = {
                "name": str(function.name),
                "address": hex(int(function.start)),
                "analysis_skipped": bool(function.analysis_skipped),
                "analysis_skip_reason": str(function.analysis_skip_reason),
                "analysis_skip_override": str(function.analysis_skip_override),
                "has_hlil": function.hlil is not None,
            }
            if (
                before["analysis_skipped"]
                and "ExceedFunctionAnalysisTimeSkipReason"
                not in before["analysis_skip_reason"]
            ):
                raise RuntimeError(
                    "refusing to override a non-timeout analysis skip for "
                    f"{function.name}: {before['analysis_skip_reason']}"
                )
            desired_override = (
                FunctionAnalysisSkipOverride.NeverSkipFunctionAnalysis
            )
            override_changed = function.analysis_skip_override != desired_override
            needs_reanalysis = (
                before["analysis_skipped"] or not before["has_hlil"]
            )
            changed = override_changed or needs_reanalysis
            if override_changed:
                analysis_skip_override_restorations.append(
                    (function, function.analysis_skip_override)
                )
                function.analysis_skip_override = desired_override
            if needs_reanalysis:
                function.reanalyze()
            if changed:
                analysis_changed = True
            results.append({
                "op": kind,
                "identifier": str(operation["identifier"]),
                "function": str(function.name),
                "address": hex(int(function.start)),
                "before": before,
                "expected_override": str(desired_override),
                "changed": changed,
            })
            affected_functions.append(str(function.name))
            continue

        if kind == "int_display_set":
            from binaryninja import IntegerDisplayType

            function = find_function(operation["identifier"])
            address = int(str(operation["address"]), 0)
            if function not in bv.get_functions_containing(address):
                raise RuntimeError(
                    f"refusing integer display override outside "
                    f"{function.name}: {address:#x}"
                )
            expected_bytes = bytes.fromhex(str(operation["expected_bytes"]))
            observed_bytes = bytes(bv.read(address, len(expected_bytes)))
            if observed_bytes != expected_bytes:
                raise RuntimeError(
                    f"refusing integer display override at {address:#x}: "
                    f"expected {expected_bytes.hex(' ')}, found "
                    f"{observed_bytes.hex(' ')}"
                )
            value = int(operation["value"])
            operand = int(operation["operand"])
            display_type_name = str(operation["display_type"])
            try:
                expected_display_type = IntegerDisplayType[display_type_name]
            except KeyError as exc:
                raise RuntimeError(
                    f"unsupported integer display type: {display_type_name}"
                ) from exc
            required_hlil = str(operation["required_hlil"])
            forbidden_hlil = str(operation["forbidden_hlil"])
            before = function.get_int_display_type(address, value, operand)
            before_hlil = str(function.hlil) if function.hlil is not None else ""
            render_stale = (
                required_hlil not in before_hlil
                or forbidden_hlil in before_hlil
            )
            changed = before != expected_display_type or render_stale
            if changed:
                analysis_changed = True
                function.set_int_display_type(
                    address,
                    value,
                    operand,
                    expected_display_type,
                )
                function.reanalyze()
                int_display_reanalysis_identifiers.append(
                    str(operation["identifier"])
                )
            results.append({
                "op": kind,
                "identifier": str(operation["identifier"]),
                "function": str(function.name),
                "address": hex(address),
                "expected_bytes": expected_bytes.hex(" "),
                "value": value,
                "operand": operand,
                "display_type": display_type_name,
                "expected_display": str(expected_display_type),
                "required_hlil": required_hlil,
                "forbidden_hlil": forbidden_hlil,
                "before": str(before),
                "render_stale": render_stale,
                "changed": changed,
            })
            affected_functions.append(str(function.name))
            continue

        if kind == "instruction_comment_set":
            function = find_function(operation["identifier"])
            address = int(str(operation["address"]), 0)
            if function not in bv.get_functions_containing(address):
                raise RuntimeError(
                    f"refusing instruction comment outside "
                    f"{function.name}: {address:#x}"
                )
            expected_bytes = bytes.fromhex(str(operation["expected_bytes"]))
            observed_bytes = bytes(bv.read(address, len(expected_bytes)))
            if observed_bytes != expected_bytes:
                raise RuntimeError(
                    f"refusing instruction comment at {address:#x}: "
                    f"expected {expected_bytes.hex(' ')}, found "
                    f"{observed_bytes.hex(' ')}"
                )
            expected_comment = str(operation["comment"])
            before = str(bv.get_comment_at(address) or "")
            changed = before != expected_comment
            if changed:
                analysis_changed = True
                bv.set_comment_at(address, expected_comment)
            results.append({
                "op": kind,
                "identifier": str(operation["identifier"]),
                "function": str(function.name),
                "address": hex(address),
                "expected_bytes": expected_bytes.hex(" "),
                "comment": expected_comment,
                "before": before,
                "changed": changed,
            })
            affected_functions.append(str(function.name))
            continue

        if kind == "struct_field_set":
            struct_name = str(operation["struct_name"])
            type_obj = bv.get_type_by_name(struct_name)
            if type_obj is None:
                raise RuntimeError(f"struct not found: {struct_name}")
            builder = type_obj.mutable_copy()
            field_type, _ = parse_type_once(operation["field_type"])
            offset = int(str(operation["offset"]), 0)
            before_member = find_member(type_obj, offset)
            before = None
            if before_member is not None:
                before = {
                    "name": str(getattr(before_member, "name", "")),
                    "type": str(getattr(before_member, "type", "")),
                }
            builder.add_member_at_offset(
                str(operation["field_name"]), field_type, offset, True
            )
            try:
                builder.width = max(int(builder.width), offset + int(field_type.width))
            except Exception:
                pass
            analysis_changed = True
            bv.define_user_type(struct_name, builder)
            results.append({
                "op": kind,
                "struct_name": struct_name,
                "offset": hex(offset),
                "field_name": str(operation["field_name"]),
                "field_type": str(field_type),
                "before": before,
            })
            affected_types.append(struct_name)
            continue

        raise RuntimeError(f"unsupported batch operation: {kind}")

    if analysis_changed:
        bv.update_analysis_and_wait()
    for entry in results:
        if entry["op"] == "rename_type":
            observed_old = bv.get_type_by_name(entry["old_name"])
            observed_new = bv.get_type_by_name(entry["new_name"])
            entry["observed"] = {
                "old_exists": observed_old is not None,
                "new_exists": observed_new is not None,
            }
            entry["verified"] = (
                observed_old is None and observed_new is not None
            )
        elif entry["op"] == "undefine_symbol":
            symbol = bv.get_symbol_at(int(entry["address"], 0))
            observed = str(symbol.name) if symbol is not None else None
            entry["observed"] = observed
            entry["verified"] = observed is None
        elif entry["op"] == "set_prototype":
            function = find_function(entry["identifier"])
            observed = str(function.type)
            entry["observed"] = observed
            entry["verified"] = normalize_function_type(
                observed
            ) == normalize_function_type(entry["expected"])
        elif entry["op"] == "user_var_set":
            function = find_function(entry["identifier"])
            variable = find_variable(function, entry)
            observed = {
                "name": str(variable.name),
                "type": str(variable.type),
                "user_defined": bool(function.is_var_user_defined(variable)),
            }
            entry["observed"] = observed
            entry["verified"] = observed == entry["expected"]
        elif entry["op"] == "user_var_delete":
            function = find_function(entry["identifier"])
            variable = find_variable(function, entry)
            observed = {
                "name": str(variable.name),
                "type": str(variable.type),
                "user_defined": bool(function.is_var_user_defined(variable)),
            }
            entry["observed"] = observed
            entry["verified"] = observed["user_defined"] is False
        elif entry["op"] == "reanalyze_function":
            function = find_function(entry["identifier"])
            observed = {
                "name": str(function.name),
                "address": hex(int(function.start)),
            }
            entry["observed"] = observed
            entry["verified"] = observed == entry["before"]
        elif entry["op"] == "ensure_function_analysis":
            function = find_function(entry["identifier"])
            observed = {
                "analysis_skipped": bool(function.analysis_skipped),
                "analysis_skip_reason": str(function.analysis_skip_reason),
                "analysis_skip_override": str(function.analysis_skip_override),
                "has_hlil": function.hlil is not None,
            }
            entry["observed"] = observed
            entry["verified"] = (
                observed["analysis_skipped"] is False
                and observed["has_hlil"] is True
                and observed["analysis_skip_override"]
                == entry["expected_override"]
            )
        elif entry["op"] == "int_display_set":
            function = find_function(entry["identifier"])
            observed_display = function.get_int_display_type(
                int(entry["address"], 0),
                int(entry["value"]),
                int(entry["operand"]),
            )
            hlil = str(function.hlil) if function.hlil is not None else ""
            entry["observed"] = {
                "display": str(observed_display),
                "required_hlil_present": entry["required_hlil"] in hlil,
                "forbidden_hlil_absent": entry["forbidden_hlil"] not in hlil,
            }
            entry["verified"] = entry["observed"] == {
                "display": entry["expected_display"],
                "required_hlil_present": True,
                "forbidden_hlil_absent": True,
            }
        elif entry["op"] == "instruction_comment_set":
            observed = str(bv.get_comment_at(int(entry["address"], 0)) or "")
            entry["observed"] = observed
            entry["verified"] = observed == entry["comment"]
        else:
            type_obj = bv.get_type_by_name(entry["struct_name"])
            member = (
                find_member(type_obj, int(entry["offset"], 0))
                if type_obj is not None
                else None
            )
            observed = None
            if member is not None:
                observed = {
                    "name": str(getattr(member, "name", "")),
                    "type": str(getattr(member, "type", "")),
                }
            entry["observed"] = observed
            entry["verified"] = observed == {
                "name": entry["field_name"],
                "type": entry["field_type"],
            }
        if not entry["verified"]:
            raise RuntimeError(f"batch verification failed: {entry!r}")
        if entry["op"] in {
            "undefine_symbol",
            "ensure_function_analysis",
            "int_display_set",
            "instruction_comment_set",
            "user_var_set",
            "user_var_delete",
        } and not entry["changed"]:
            entry["status"] = "skipped"
            entry["reason"] = (
                "already absent"
                if entry["op"] == "undefine_symbol"
                else (
                    "analysis already pinned with HLIL"
                    if entry["op"] == "ensure_function_analysis"
                    else (
                        "already automatic"
                        if entry["op"] == "user_var_delete"
                        else "already current"
                    )
                )
            )
        else:
            entry["status"] = "verified"

    if preview:
        bv.revert_undo_actions(state)
        undo_closed = True
        if analysis_changed:
            # Reverting a user-variable mutation has the same stale-HLIL
            # failure mode as reverting a prototype mutation: a bare
            # update_analysis_and_wait() can leave the previewed owner visible
            # until some later action happens to queue the function.
            for identifier in dict.fromkeys(
                prototype_reanalysis_identifiers
                + user_var_reanalysis_identifiers
                + int_display_reanalysis_identifiers
            ):
                find_function(identifier).reanalyze()
            bv.update_analysis_and_wait()
        for function, original_override in analysis_skip_override_restorations:
            function.analysis_skip_override = original_override
    else:
        bv.commit_undo_actions(state)
        undo_closed = True
        snapshot_saved = bv.file.save_auto_snapshot() if analysis_changed else False
        if analysis_changed and snapshot_saved is not True:
            raise RuntimeError(
                "Binary Ninja committed the live batch but failed to save its "
                "database snapshot; close duplicate views of the same .bndb "
                "before retrying"
            )
except Exception:
    if not undo_closed:
        bv.revert_undo_actions(state)
        if analysis_changed:
            for identifier in dict.fromkeys(
                prototype_reanalysis_identifiers
                + user_var_reanalysis_identifiers
                + int_display_reanalysis_identifiers
            ):
                find_function(identifier).reanalyze()
            bv.update_analysis_and_wait()
        for function, original_override in analysis_skip_override_restorations:
            function.analysis_skip_override = original_override
    raise

result = {
    "success": True,
    "preview": preview,
    "committed": not preview,
    "message": "Preview verified and reverted." if preview else "Mutation committed.",
    "affected_types": sorted(set(affected_types)),
    "affected_functions": sorted(set(affected_functions)),
    "results": results,
    "snapshot_saved": snapshot_saved,
}
"""
    return template.replace(
        "__OPERATIONS_JSON__", repr(json.dumps(operations))
    ).replace("__PREVIEW__", repr(preview))


def run_bn_batch(
    repo_root: Path,
    *,
    target: str,
    operations: list[dict[str, object]],
    preview: bool,
) -> dict[str, object]:
    # `bn batch apply` was removed from the 0.14 CLI. Keep one transactional
    # bridge round trip by replaying narrow ownership mutations through
    # `bn py exec` instead of regressing to one process and analysis pass per
    # field.
    result = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        _batch_python_code(operations, preview=preview),
    )
    if (
        isinstance(result, dict)
        and isinstance(result.get("result"), dict)
        and "success" not in result
    ):
        result = result["result"]
    if (
        not isinstance(result, dict)
        or result.get("success") is not True
        or result.get("preview") is not preview
        or result.get("committed") is not (not preview)
    ):
        phase = "preview" if preview else "apply"
        raise RuntimeError(f"Binary Ninja batch {phase} failed: {result!r}")
    return result


def run_previewed_bn_batch(
    repo_root: Path, *, target: str, operations: list[dict[str, object]]
) -> dict[str, object]:
    preview = run_bn_batch(
        repo_root,
        target=target,
        operations=operations,
        preview=True,
    )
    applied = run_bn_batch(
        repo_root,
        target=target,
        operations=operations,
        preview=False,
    )
    return {
        "preview": {
            "success": preview.get("success"),
            "message": preview.get("message"),
            "affected_type_count": len(preview.get("affected_types", ())),
            "affected_function_count": len(preview.get("affected_functions", ())),
        },
        "apply": applied,
    }


def apply_type_renames(
    repo_root: Path,
    *,
    target: str,
    renames: Iterable[TypeRename],
) -> list[dict[str, object]]:
    rename_list = list(renames)
    type_names = tuple(
        dict.fromkeys(
            name
            for old_name, new_name in rename_list
            for name in (old_name, new_name)
        )
    )
    widths = current_type_widths(
        repo_root,
        target=target,
        type_names=type_names,
    )
    ambiguous_old_names = tuple(
        old_name
        for old_name, new_name in rename_list
        if widths.get(old_name) is not None
        and widths.get(new_name) is not None
    )
    alias_targets = current_type_alias_targets(
        repo_root,
        target=target,
        type_names=ambiguous_old_names,
    )
    skipped: list[dict[str, object]] = []
    pending: list[dict[str, object]] = []
    for old_name, new_name in rename_list:
        old_exists = widths.get(old_name) is not None
        new_exists = widths.get(new_name) is not None
        if not old_exists:
            skipped.append(
                {
                    "op": "rename_type",
                    "status": "skipped",
                    "reason": (
                        "already current"
                        if new_exists
                        else "source type absent"
                    ),
                    "old_name": old_name,
                    "new_name": new_name,
                }
            )
            continue
        if new_exists:
            if alias_targets.get(old_name) == new_name:
                skipped.append(
                    {
                        "op": "rename_type",
                        "status": "skipped",
                        "reason": "already current via compatibility alias",
                        "old_name": old_name,
                        "new_name": new_name,
                    }
                )
                continue
            raise RuntimeError(
                f"refusing ambiguous type rename {old_name} -> {new_name}: "
                "both names already exist"
            )
        pending.append(
            {
                "op": "rename_type",
                "old_name": old_name,
                "new_name": new_name,
            }
        )

    if not pending:
        return skipped
    return [
        *skipped,
        {
            "op": "type_rename_batch",
            "operation_count": len(pending),
            "operations": pending,
            "result": run_previewed_bn_batch(
                repo_root,
                target=target,
                operations=pending,
            ),
        },
    ]


def reanalyze_functions(
    repo_root: Path, *, target: str, identifiers: Iterable[str]
) -> list[dict[str, object]]:
    operations = [
        {
            "op": "reanalyze_function",
            "identifier": identifier,
        }
        for identifier in identifiers
    ]
    if not operations:
        return []
    return [
        {
            "op": "function_reanalysis_batch",
            "operation_count": len(operations),
            "operations": operations,
            "result": run_previewed_bn_batch(
                repo_root,
                target=target,
                operations=operations,
            ),
        }
    ]


def ensure_function_analysis(
    repo_root: Path, *, target: str, identifiers: Iterable[str]
) -> list[dict[str, object]]:
    """Persist per-function analysis for owners that can exceed the time limit."""
    operations = [
        {
            "op": "ensure_function_analysis",
            "identifier": identifier,
        }
        for identifier in identifiers
    ]
    if not operations:
        return []
    return [
        {
            "op": "function_analysis_guard_batch",
            "operation_count": len(operations),
            "operations": operations,
            "result": run_previewed_bn_batch(
                repo_root,
                target=target,
                operations=operations,
            ),
        }
    ]


def apply_direct_proto_updates_batch(
    repo_root: Path, *, target: str, updates: Iterable[ProtoUpdate]
) -> dict[str, object]:
    update_list = list(updates)
    code = f"""
updates = {json.dumps(update_list)}


def find_function(identifier):
    text = str(identifier)
    try:
        address = int(text, 0)
    except ValueError:
        functions = list(bv.get_functions_by_name(text))
        if len(functions) != 1:
            raise RuntimeError(
                f"expected one function named {{text}}, found {{len(functions)}}"
            )
        return functions[0]
    function = bv.get_function_at(address)
    if function is None:
        raise RuntimeError(f"function not found at {{address:#x}}")
    return function


def normalize_function_type(value):
    return str(value).replace(" __pure", "")


state = bv.begin_undo_actions()
applied = []
reanalysis_identifiers = []
try:
    for identifier, prototype in updates:
        fn = find_function(identifier)
        before = str(fn.type)
        parsed_type, _ = bv.parse_type_string(prototype)
        fn.set_user_type(parsed_type)
        fn.reanalyze()
        reanalysis_identifiers.append(identifier)
        applied.append({{
            "identifier": identifier,
            "before": before,
            "requested": str(parsed_type),
        }})
    bv.update_analysis_and_wait()
    for entry in applied:
        fn = find_function(entry["identifier"])
        entry["after"] = str(fn.type)
        entry["verified"] = normalize_function_type(
            entry["after"]
        ) == normalize_function_type(entry["requested"])
    if not all(entry["verified"] for entry in applied):
        raise RuntimeError(f"direct prototype verification failed: {{applied!r}}")
    bv.commit_undo_actions(state)
    snapshot_saved = bv.file.save_auto_snapshot()
except Exception:
    bv.revert_undo_actions(state)
    for identifier in reanalysis_identifiers:
        find_function(identifier).reanalyze()
    bv.update_analysis_and_wait()
    raise
result = {{"applied": applied, "snapshot_saved": snapshot_saved}}
"""
    result = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        code,
    )
    payload = result.get("result") if isinstance(result, dict) else None
    if not isinstance(payload, dict) or payload.get("snapshot_saved") is not True:
        raise RuntimeError(
            "direct prototype batch changed the live analysis without a saved snapshot"
        )
    observed_prototypes = current_prototypes(
        repo_root,
        target=target,
        identifiers=(identifier for identifier, _prototype in update_list),
    )
    for identifier, prototype in update_list:
        observed = observed_prototypes.get(identifier)
        if observed is None or normalize_prototype(
            observed, identifier=identifier
        ) != normalize_prototype(prototype, identifier=identifier):
            raise RuntimeError(
                f"direct prototype batch readback failed for {identifier}: {observed!r}"
            )
    return {
        "op": "proto_set_direct_batch",
        "operation_count": len(update_list),
        "result": result,
    }


def types_declare(repo_root: Path, *, target: str, header_path: Path) -> dict[str, object]:
    preview = run_bn(
        repo_root,
        "types",
        "declare",
        "--preview",
        "--target",
        target,
        "--file",
        str(header_path),
        "--format",
        "json",
    )
    if (
        not isinstance(preview, dict)
        or preview.get("success") is not True
        or preview.get("preview") is not True
        or preview.get("committed") is not False
    ):
        raise RuntimeError(f"type declaration preview failed for {header_path}: {preview!r}")

    zero_width_regressions = []
    for affected_type in preview.get("affected_types", ()):
        if not isinstance(affected_type, dict) or affected_type.get("changed") is not True:
            continue
        before_width = parse_struct_layout_size(str(affected_type.get("before_layout", "")))
        after_width = parse_struct_layout_size(str(affected_type.get("after_layout", "")))
        if before_width not in (None, 0) and after_width == 0:
            zero_width_regressions.append(
                {
                    "type_name": affected_type.get("type_name"),
                    "before_width": before_width,
                    "after_width": after_width,
                }
            )
    if zero_width_regressions:
        raise RuntimeError(
            f"refusing type declaration that erases complete owners: {zero_width_regressions!r}"
        )

    result = run_bn(repo_root, "types", "declare", "--target", target, "--file", str(header_path))
    return {
        "op": "types_declare",
        "preview": {
            "success": preview.get("success"),
            "message": preview.get("message"),
            "affected_type_count": len(preview.get("affected_types", ())),
            "affected_function_count": len(preview.get("affected_functions", ())),
        },
        "result": result,
    }


def current_header_type_equivalence(
    repo_root: Path, *, target: str, header_path: Path
) -> dict[str, bool]:
    """Compare every parsed header type with the live type without mutating analysis."""
    code = f"""
import binaryninja

header_path = {json.dumps(str(header_path.resolve()))}
with open(header_path, "r", encoding="utf-8") as header_file:
    header = header_file.read()
parsed, errors = binaryninja.TypeParser.default.parse_types_from_source(
    header,
    header_path,
    bv.platform,
    bv.type_container,
)
# Binary Ninja's pointer-offset/base extensions can make a complete,
# self-contained header report false "redefinition" errors when the live type
# container already holds its forward declarations. Retry in an isolated
# parser container before treating that as a malformed header. Partial headers
# that rely on live declarations still retain the first parse result when the
# isolated retry cannot resolve them.
if parsed is None or errors:
    isolated_parsed, isolated_errors = (
        binaryninja.TypeParser.default.parse_types_from_source(
            header,
            header_path,
            bv.platform,
            None,
        )
    )
    if isolated_parsed is not None and not isolated_errors:
        parsed, errors = isolated_parsed, isolated_errors
parse_errors = [str(error) for error in (errors or ())]
if parsed is None and not parse_errors:
    parse_errors.append("type parser returned no result")
if parsed is None or errors:
    result = {{
        "errors": parse_errors,
        "types": [],
    }}
else:
    def _structure_signature(type_):
        if (
            type_ is None
            or type_.type_class
            != binaryninja.TypeClass.StructureTypeClass
        ):
            return None
        return (
            type_.type_class,
            type_.width,
            type_.alignment,
            type_.packed,
            str(type_).split(" ", 1)[0],
            tuple(
                (
                    str(base.type),
                    base.offset,
                    base.width,
                )
                for base in type_.base_structures
            ),
            tuple(
                (
                    member.name,
                    member.offset,
                    member.type.type_class,
                    member.type.width,
                    member.type.alignment,
                    str(member.type),
                )
                for member in type_.members
            ),
        )

    def _equivalent(current, parsed_type):
        if current is None:
            return False
        if current == parsed_type:
            return True
        parsed_signature = _structure_signature(parsed_type)
        return (
            parsed_signature is not None
            and _structure_signature(current) == parsed_signature
        )

    result = {{
        "errors": [],
        "types": [
            {{
                "name": str(parsed_type.name),
                "equivalent": _equivalent(
                    bv.get_type_by_name(parsed_type.name),
                    parsed_type.type,
                ),
            }}
            for parsed_type in parsed.types
        ],
    }}
"""
    response = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        code,
    )
    payload = response.get("result") if isinstance(response, dict) else None
    if not isinstance(payload, dict):
        raise RuntimeError(f"Binary Ninja returned no type audit for {header_path}")
    errors = payload.get("errors")
    if not isinstance(errors, list) or any(not isinstance(error, str) for error in errors):
        raise RuntimeError(f"Binary Ninja returned an invalid type audit for {header_path}")
    if errors:
        raise RuntimeError(f"type parsing failed for {header_path}: {'; '.join(errors)}")
    entries = payload.get("types")
    if not isinstance(entries, list) or not entries:
        raise RuntimeError(f"header declares no types: {header_path}")

    equivalence: dict[str, bool] = {}
    for entry in entries:
        if (
            not isinstance(entry, dict)
            or not isinstance(entry.get("name"), str)
            or not isinstance(entry.get("equivalent"), bool)
        ):
            raise RuntimeError(f"Binary Ninja returned an invalid type entry for {header_path}")
        equivalence[entry["name"]] = entry["equivalent"]
    return equivalence


def types_declare_if_changed(
    repo_root: Path, *, target: str, header_path: Path
) -> dict[str, object]:
    """Skip the expensive declaration preview when the live header is exact."""
    equivalence = current_header_type_equivalence(
        repo_root,
        target=target,
        header_path=header_path,
    )
    stale_types = tuple(name for name, equivalent in equivalence.items() if not equivalent)
    if not stale_types:
        return {
            "op": "types_declare",
            "status": "skipped",
            "reason": "all parsed header types already equivalent",
            "header": str(header_path),
            "type_count": len(equivalence),
        }

    result = types_declare(
        repo_root,
        target=target,
        header_path=header_path,
    )
    result["stale_types"] = stale_types
    return result


def types_declare_missing_only(
    repo_root: Path,
    *,
    target: str,
    header_path: Path,
    replace_types: Iterable[str] = (),
    include_types: Iterable[str] = (),
) -> dict[str, object]:
    replacement_names = tuple(replace_types)
    included_names = tuple(include_types)
    def run_phase(*, preview: bool) -> tuple[dict[str, object], dict[str, object]]:
        code = f"""
import binaryninja

header_path = {json.dumps(str(header_path))}
replacement_names = set({json.dumps(replacement_names)})
included_names = set({json.dumps(included_names)})
preview = {preview!r}
with open(header_path, "r", encoding="utf-8") as header_file:
    header = header_file.read()
parsed, errors = binaryninja.TypeParser.default.parse_types_from_source(
    header,
    header_path,
    bv.platform,
    None,
)
if parsed is None or errors:
    raise RuntimeError("; ".join(str(error) for error in errors))


def _structure_signature(type_):
    if (
        type_ is None
        or type_.type_class != binaryninja.TypeClass.StructureTypeClass
    ):
        return None
    return (
        type_.type_class,
        type_.width,
        type_.alignment,
        type_.packed,
        str(type_).split(" ", 1)[0],
        tuple(
            (
                str(base.type),
                base.offset,
                base.width,
            )
            for base in type_.base_structures
        ),
        tuple(
            (
                member.name,
                member.offset,
                member.type.type_class,
                member.type.width,
                member.type.alignment,
                str(member.type),
            )
            for member in type_.members
        ),
    )


candidates = []
before_types = {{}}
for parsed_type in parsed.types:
    parsed_name = str(parsed_type.name)
    if included_names and parsed_name not in included_names:
        continue
    existing = bv.get_type_by_name(parsed_type.name)
    before_width = existing.width if existing is not None else None
    parsed_width = parsed_type.type.width
    should_replace = parsed_name in replacement_names
    if parsed_width > 0 and (before_width is None or before_width == 0 or should_replace):
        candidates.append((parsed_type, before_width))
        before_types[parsed_name] = existing

state = bv.begin_undo_actions()
undo_closed = False
snapshot_saved = False
try:
    for parsed_type, _before_width in sorted(
        candidates,
        key=lambda item: item[0].type.width,
    ):
        bv.define_user_type(parsed_type.name, parsed_type.type)

    if candidates:
        bv.update_analysis_and_wait()
    verification = []
    for parsed_type, before_width in candidates:
        parsed_name = str(parsed_type.name)
        observed = bv.get_type_by_name(parsed_type.name)
        observed_width = observed.width if observed is not None else None
        direct_match = observed == parsed_type.type
        parsed_structure_signature = _structure_signature(parsed_type.type)
        structural_match = (
            parsed_structure_signature is not None
            and _structure_signature(observed) == parsed_structure_signature
        )
        verification.append({{
            "name": parsed_name,
            "before_width": before_width,
            "after_width": parsed_type.type.width,
            "observed_width": observed_width,
            "verification_mode": (
                "direct" if direct_match
                else "structure" if structural_match
                else "mismatch"
            ),
            "verified": direct_match or structural_match,
        }})
    if not all(entry["verified"] for entry in verification):
        raise RuntimeError(
            f"selective type declaration verification failed: {{verification!r}}"
        )

    restoration = []
    if preview:
        bv.revert_undo_actions(state)
        undo_closed = True
        if candidates:
            bv.update_analysis_and_wait()
        for parsed_name, before_type in before_types.items():
            restored = bv.get_type_by_name(parsed_name)
            restoration.append({{
                "name": parsed_name,
                "verified": restored == before_type,
            }})
        if not all(entry["verified"] for entry in restoration):
            raise RuntimeError(
                f"selective type declaration rollback failed: {{restoration!r}}"
            )
    else:
        bv.commit_undo_actions(state)
        undo_closed = True
        if candidates:
            snapshot_saved = bv.file.save_auto_snapshot()
except Exception:
    if not undo_closed:
        bv.revert_undo_actions(state)
        bv.update_analysis_and_wait()
    raise

result = {{
    "success": True,
    "preview": preview,
    "committed": not preview,
    "applied": verification,
    "restoration": restoration,
    "snapshot_saved": snapshot_saved,
}}
"""
        response = run_bn(
            repo_root,
            "py",
            "exec",
            "--target",
            target,
            "--format",
            "json",
            "--code",
            code,
        )
        payload = response.get("result") if isinstance(response, dict) else None
        if (
            not isinstance(payload, dict)
            or payload.get("success") is not True
            or payload.get("preview") is not preview
            or payload.get("committed") is not (not preview)
            or not isinstance(payload.get("applied"), list)
        ):
            phase = "preview" if preview else "apply"
            raise RuntimeError(
                f"selective type declaration {phase} failed for {header_path}: "
                f"{response!r}"
            )
        return payload, response

    preview, _preview_response = run_phase(preview=True)
    applied, applied_response = run_phase(preview=False)
    if applied.get("applied") and applied.get("snapshot_saved") is not True:
        raise RuntimeError(
            f"selective type declaration changed {header_path} without a saved snapshot"
        )
    return {
        "op": "types_declare_missing_only",
        "header": str(header_path),
        "replace_types": replacement_names,
        "include_types": included_names,
        "preview": {
            "success": True,
            "message": "Selective preview verified and reverted.",
            "affected_type_count": len(preview.get("applied", ())),
            "affected_function_count": 0,
        },
        "result": applied_response,
    }


def parse_struct_layout_size(layout: str) -> int | None:
    match = STRUCT_SIZE_RE.search(layout)
    if match is None:
        return None
    return int(match.group("size"), 0)


def current_struct_size(repo_root: Path, *, target: str, struct_name: str) -> int | None:
    try:
        result = run_bn(
            repo_root,
            "struct",
            "show",
            struct_name,
            "--target",
            target,
            "--format",
            "json",
        )
    except RuntimeError:
        return None
    if not isinstance(result, dict):
        return None
    layout = result.get("layout")
    if not isinstance(layout, str):
        return None
    return parse_struct_layout_size(layout)


def ensure_function_entry(
    repo_root: Path, *, target: str, address: int
) -> dict[str, object]:
    code = f"""
address = {address}
before = bv.get_function_at(address)
created = before is None
if created:
    bv.add_function(address)
    bv.update_analysis_and_wait()
after = bv.get_function_at(address)
if after is None:
    raise RuntimeError(f"failed to create function entry at {{address:#x}}")
snapshot_saved = bv.file.save_auto_snapshot() if created else None
result = {{
    "address": hex(address),
    "created": created,
    "observed_start": hex(after.start),
    "verified": after.start == address,
    "snapshot_saved": snapshot_saved,
}}
"""
    response = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        code,
    )
    payload = response.get("result") if isinstance(response, dict) else None
    if not isinstance(payload, dict) or payload.get("verified") is not True:
        raise RuntimeError(
            f"function-entry verification failed at {address:#x}: {response!r}"
        )
    return {
        "op": "function_entry_ensure",
        "address": hex(address),
        "status": "verified" if payload.get("created") else "skipped",
        "reason": None if payload.get("created") else "already current",
        "result": payload,
    }


def current_type_widths(
    repo_root: Path, *, target: str, type_names: Iterable[str]
) -> dict[str, int | None]:
    names = tuple(type_names)
    code = f"""
names = {json.dumps(names)}
result = {{}}
for name in names:
    current = bv.get_type_by_name(name)
    result[name] = current.width if current is not None else None
"""
    response = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        code,
    )
    payload = response.get("result") if isinstance(response, dict) else None
    if not isinstance(payload, dict):
        return {name: None for name in names}
    return {
        name: value if isinstance(value := payload.get(name), int) else None
        for name in names
    }


def current_type_alias_targets(
    repo_root: Path, *, target: str, type_names: Iterable[str]
) -> dict[str, str | None]:
    names = tuple(type_names)
    if not names:
        return {}
    code = f"""
names = {json.dumps(names)}
result = {{}}
for name in names:
    current = bv.get_type_by_name(name)
    if current is None or not str(current.type_class).endswith("NamedTypeReferenceClass"):
        result[name] = None
        continue
    try:
        result[name] = str(current.name)
    except (AttributeError, NotImplementedError):
        result[name] = None
"""
    response = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        code,
    )
    payload = response.get("result") if isinstance(response, dict) else None
    if not isinstance(payload, dict):
        return {name: None for name in names}
    return {
        name: value if isinstance(value := payload.get(name), str) else None
        for name in names
    }


def current_enum_members(
    repo_root: Path, *, target: str, enum_names: Iterable[str]
) -> dict[str, tuple[tuple[str, int], ...] | None]:
    names = tuple(enum_names)
    code = f"""
names = {json.dumps(names)}
result = {{}}
for name in names:
    current = bv.get_type_by_name(name)
    if current is None:
        result[name] = None
        continue
    try:
        width = int(current.width)
        if width <= 0:
            raise ValueError("enum width must be positive")
        value_mask = (1 << (width * 8)) - 1
        result[name] = [
            [str(member.name), int(member.value) & value_mask]
            for member in current.members
        ]
    except (AttributeError, ValueError):
        result[name] = None
"""
    response = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        code,
    )
    payload = response.get("result") if isinstance(response, dict) else None
    if not isinstance(payload, dict):
        return {name: None for name in names}

    result: dict[str, tuple[tuple[str, int], ...] | None] = {}
    for name in names:
        members = payload.get(name)
        if not isinstance(members, list):
            result[name] = None
            continue
        normalized: list[tuple[str, int]] = []
        for member in members:
            if (
                not isinstance(member, list)
                or len(member) != 2
                or not isinstance(member[0], str)
                or not isinstance(member[1], int)
            ):
                normalized = []
                break
            normalized.append((member[0], member[1]))
        result[name] = tuple(normalized) if len(normalized) == len(members) else None
    return result


def header_enum_members(
    repo_root: Path,
    *,
    target: str,
    header_path: Path,
    enum_names: Iterable[str],
) -> dict[str, tuple[tuple[str, int], ...] | None]:
    """Parse enum members from a header without mutating the live database."""
    names = tuple(enum_names)
    code = f"""
import binaryninja

header_path = {json.dumps(str(header_path))}
names = {json.dumps(names)}
with open(header_path, "r", encoding="utf-8") as header_file:
    header = header_file.read()
parsed, errors = binaryninja.TypeParser.default.parse_types_from_source(
    header,
    header_path,
    bv.platform,
    None,
)
if parsed is None or errors:
    raise RuntimeError("; ".join(str(error) for error in errors))

parsed_types = {{
    str(parsed_type.name): parsed_type.type
    for parsed_type in parsed.types
}}
result = {{}}
for name in names:
    parsed_type = parsed_types.get(name)
    if parsed_type is None:
        result[name] = None
        continue
    try:
        width = int(parsed_type.width)
        if width <= 0:
            raise ValueError("enum width must be positive")
        value_mask = (1 << (width * 8)) - 1
        result[name] = [
            [str(member.name), int(member.value) & value_mask]
            for member in parsed_type.members
        ]
    except (AttributeError, ValueError):
        result[name] = None
"""
    response = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        code,
    )
    payload = response.get("result") if isinstance(response, dict) else None
    if not isinstance(payload, dict):
        return {name: None for name in names}

    result: dict[str, tuple[tuple[str, int], ...] | None] = {}
    for name in names:
        members = payload.get(name)
        if not isinstance(members, list):
            result[name] = None
            continue
        normalized: list[tuple[str, int]] = []
        for member in members:
            if (
                not isinstance(member, list)
                or len(member) != 2
                or not isinstance(member[0], str)
                or not isinstance(member[1], int)
            ):
                normalized = []
                break
            normalized.append((member[0], member[1]))
        result[name] = tuple(normalized) if len(normalized) == len(members) else None
    return result


def struct_exists(repo_root: Path, *, target: str, struct_name: str) -> bool:
    # Binary Ninja reports a forward declaration as a zero-sized struct. It is
    # not sufficient for replay: treating it as present causes the authoritative
    # header import to be skipped forever, leaving every owner pointer opaque.
    size = current_struct_size(repo_root, target=target, struct_name=struct_name)
    return size is not None and size > 0


def types_declare_if_missing(
    repo_root: Path,
    *,
    target: str,
    header_path: Path,
    required_structs: Iterable[str],
) -> dict[str, object]:
    required = tuple(required_structs)
    widths = current_type_widths(repo_root, target=target, type_names=required)
    missing = [name for name in required if not widths.get(name)]
    if not missing:
        return {
            "op": "types_declare",
            "status": "skipped",
            "reason": "required structs already present",
            "header": str(header_path),
            "required_structs": required,
        }
    result = types_declare_missing_only(
        repo_root,
        target=target,
        header_path=header_path,
        include_types=missing,
    )
    response = result.get("result")
    payload = response.get("result") if isinstance(response, dict) else None
    applied = payload.get("applied") if isinstance(payload, dict) else None
    applied_names = {
        entry.get("name")
        for entry in applied or ()
        if isinstance(entry, dict) and entry.get("verified") is True
    }
    unresolved = [name for name in missing if name not in applied_names]
    if unresolved:
        raise RuntimeError(
            f"{header_path} does not provide complete definitions for: "
            f"{', '.join(unresolved)}"
        )
    result["missing_structs"] = tuple(missing)
    return result


def normalize_type_name(type_name: str) -> str:
    normalized = re.sub(r"\b(?:struct|union|enum)\s+", "", type_name)
    normalized = re.sub(r"\b([A-Za-z_][A-Za-z0-9_:]*)\s+const\s*\*", r"const \1*", normalized)
    normalized = re.sub(
        r"\[(0x[0-9a-fA-F]+|\d+)\]",
        lambda match: f"[{int(match.group(1), 0)}]",
        normalized,
    )
    return normalized.replace(" ", "")


def normalize_prototype(prototype: str, *, identifier: str) -> str:
    normalized = re.sub(r"\s+", " ", prototype).strip()
    # Binary Ninja preserves its independently proven purity qualifier when a
    # user prototype is applied. Treat that additive analysis fact as
    # orthogonal to the ABI/type comparison so repeatable syncs do not try to
    # overwrite an already-correct pure function.
    normalized = re.sub(r"\s+__pure\b", "", normalized)
    # Binary Ninja omits the platform-default cdecl convention when rendering
    # a function type. Explicit __cdecl and no printed convention are the same
    # x86 ABI, so treating them as distinct makes an otherwise idempotent sync
    # reapply every ordinary C helper on each replay.
    normalized = re.sub(r"\s+__cdecl\b", "", normalized)
    normalized = normalized.replace(f" {identifier}(", "(")
    # Address-selected mutations cannot use the selector itself to remove the
    # declaration name. Binary Ninja readback prints only the function type,
    # so strip one remaining C/C++ declarator name immediately before `(`.
    normalized = re.sub(
        r"\s+(?!__)[A-Za-z_][A-Za-z0-9_:]*(?=\()",
        "",
        normalized,
        count=1,
    )
    return normalize_type_name(normalized)


def offset_to_int(offset: str) -> int:
    return int(offset, 0)


def current_struct_fields(repo_root: Path, *, target: str, struct_name: str) -> dict[int, tuple[str, str]]:
    result = run_bn(
        repo_root,
        "struct",
        "show",
        struct_name,
        "--target",
        target,
        "--format",
        "json",
    )
    if not isinstance(result, dict):
        return {}

    layout = result.get("layout")
    if not isinstance(layout, str):
        return {}

    fields: dict[int, tuple[str, str]] = {}
    for line in layout.splitlines():
        match = STRUCT_FIELD_RE.match(line)
        if match is None:
            continue
        fields[offset_to_int(match.group("offset"))] = (
            match.group("name"),
            normalize_type_name(match.group("type")),
        )
    return fields


def current_struct_fields_batch(
    repo_root: Path, *, target: str, struct_names: Iterable[str]
) -> dict[str, dict[int, tuple[str, str]]]:
    names = tuple(struct_names)
    code = f"""
names = {json.dumps(names)}
result = {{}}
for name in names:
    current = bv.get_type_by_name(name)
    if current is None or not hasattr(current, "members"):
        result[name] = None
        continue
    result[name] = [
        {{"offset": member.offset, "name": member.name, "type": str(member.type)}}
        for member in current.members
    ]
"""
    response = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        code,
    )
    payload = response.get("result") if isinstance(response, dict) else None
    if not isinstance(payload, dict):
        raise RuntimeError("Binary Ninja returned no batched struct layouts")

    layouts: dict[str, dict[int, tuple[str, str]]] = {}
    for name in names:
        members = payload.get(name)
        if not isinstance(members, list):
            raise RuntimeError(f"Type is not a struct-like type: {name}")
        layouts[name] = {
            entry["offset"]: (entry["name"], normalize_type_name(entry["type"]))
            for entry in members
            if isinstance(entry, dict)
            and isinstance(entry.get("offset"), int)
            and isinstance(entry.get("name"), str)
            and isinstance(entry.get("type"), str)
        }
    return layouts


def current_prototype(repo_root: Path, *, target: str, identifier: str) -> str | None:
    result = run_bn(
        repo_root,
        "proto",
        "get",
        identifier,
        "--target",
        target,
        "--format",
        "json",
    )
    if isinstance(result, dict):
        prototype = result.get("prototype")
        if isinstance(prototype, str):
            return prototype
    return None


def current_prototypes(
    repo_root: Path, *, target: str, identifiers: Iterable[str]
) -> dict[str, str | None]:
    names = tuple(identifiers)
    code = f"""
identifiers = {json.dumps(names)}
result = {{}}
for identifier in identifiers:
    functions = []
    try:
        address = int(identifier, 0)
    except ValueError:
        functions = list(bv.get_functions_by_name(identifier))
    else:
        function = bv.get_function_at(address)
        if function is not None:
            functions = [function]
    result[identifier] = str(functions[0].type) if len(functions) == 1 else None
"""
    response = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        code,
    )
    payload = response.get("result") if isinstance(response, dict) else None
    if not isinstance(payload, dict):
        return {identifier: None for identifier in names}
    return {
        identifier: value if isinstance(value := payload.get(identifier), str) else None
        for identifier in names
    }


def apply_direct_proto_update(
    repo_root: Path,
    *,
    target: str,
    identifier: str,
    prototype: str,
) -> dict[str, object]:
    existing = current_prototype(repo_root, target=target, identifier=identifier)
    requested_normalized = normalize_prototype(prototype, identifier=identifier)
    if existing is not None and normalize_prototype(
        existing, identifier=identifier
    ) == requested_normalized:
        return {
            "op": "proto_set_direct",
            "status": "skipped",
            "reason": "already current",
            "identifier": identifier,
            "prototype": prototype,
        }

    code = f"""
identifier = {json.dumps(identifier)}
functions = list(bv.get_functions_by_name(identifier))
if len(functions) != 1:
    raise RuntimeError(f"expected one function named {{identifier}}, found {{len(functions)}}")
fn = functions[0]
before = str(fn.type)
parsed_type, _ = bv.parse_type_string({json.dumps(prototype)})
fn.set_user_type(parsed_type)
fn.reanalyze()
bv.update_analysis_and_wait()
result = {{
    "function": identifier,
    "before": before,
    "requested": str(parsed_type),
    "after": str(fn.type),
}}
"""
    result = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        code,
    )
    observed = current_prototype(repo_root, target=target, identifier=identifier)
    if observed is None or normalize_prototype(
        observed, identifier=identifier
    ) != requested_normalized:
        raise RuntimeError(
            f"direct prototype verification failed for {identifier}: observed {observed!r}"
        )
    return {
        "op": "proto_set_direct",
        "status": "verified",
        "identifier": identifier,
        "prototype": prototype,
        "observed_prototype": observed,
        "result": result,
    }


def apply_struct_field_updates(
    repo_root: Path,
    *,
    target: str,
    struct_name: str,
    updates: Iterable[FieldUpdate],
) -> list[dict[str, object]]:
    operations: list[dict[str, object]] = []
    fields = current_struct_fields(repo_root, target=target, struct_name=struct_name)
    for offset, name, field_type in updates:
        existing = fields.get(offset_to_int(offset))
        if existing == (name, normalize_type_name(field_type)):
            operations.append(
                {
                    "op": "struct_field_set",
                    "status": "skipped",
                    "reason": "already current",
                    "struct_name": struct_name,
                    "offset": offset,
                    "field_name": name,
                    "field_type": field_type,
                }
            )
            continue

        operations.append(
            {
                "op": "struct_field_set",
                "struct_name": struct_name,
                "offset": offset,
                "field_name": name,
                "field_type": field_type,
                "result": run_previewed_bn_mutation(
                    repo_root,
                    "struct",
                    "field",
                    "set",
                    struct_name,
                    offset,
                    name,
                    field_type,
                    "--target",
                    target,
                ),
            }
        )
    return operations


def apply_proto_updates(
    repo_root: Path,
    *,
    target: str,
    updates: Iterable[ProtoUpdate],
) -> list[dict[str, object]]:
    update_list = list(updates)
    skipped: list[dict[str, object]] = []
    pending: list[dict[str, object]] = []
    existing_prototypes = current_prototypes(
        repo_root,
        target=target,
        identifiers=(identifier for identifier, _prototype in update_list),
    )
    for identifier, prototype in update_list:
        existing = existing_prototypes.get(identifier)
        existing_normalized = (
            normalize_prototype(existing, identifier=identifier) if existing is not None else None
        )
        requested_normalized = normalize_prototype(prototype, identifier=identifier)
        if existing_normalized == requested_normalized:
            skipped.append(
                {
                    "op": "proto_set",
                    "status": "skipped",
                    "reason": "already current",
                    "identifier": identifier,
                    "prototype": prototype,
                }
            )
            continue

        pending.append(
            {
                "op": "set_prototype",
                "identifier": identifier,
                "prototype": prototype,
            }
        )
    if not pending:
        return skipped
    return [
        *skipped,
        {
            "op": "proto_set_batch",
            "operation_count": len(pending),
            "operations": pending,
            "result": run_previewed_bn_batch(
                repo_root,
                target=target,
                operations=pending,
            ),
        },
    ]


def apply_struct_and_proto_updates(
    repo_root: Path,
    *,
    target: str,
    struct_updates: Iterable[StructUpdateGroup],
    proto_updates: Iterable[ProtoUpdate],
) -> list[dict[str, object]]:
    struct_update_list = [
        (struct_name, tuple(updates)) for struct_name, updates in struct_updates
    ]
    proto_update_list = list(proto_updates)
    batch_ops: list[dict[str, object]] = []
    skipped: list[dict[str, object]] = []

    existing_struct_fields = current_struct_fields_batch(
        repo_root,
        target=target,
        struct_names=(struct_name for struct_name, _updates in struct_update_list),
    )
    for struct_name, updates in struct_update_list:
        fields = existing_struct_fields[struct_name]
        for offset, name, field_type in updates:
            existing = fields.get(offset_to_int(offset))
            if existing == (name, normalize_type_name(field_type)):
                skipped.append(
                    {
                        "op": "struct_field_set",
                        "status": "skipped",
                        "reason": "already current",
                        "struct_name": struct_name,
                        "offset": offset,
                        "field_name": name,
                        "field_type": field_type,
                    }
                )
                continue
            batch_ops.append(
                {
                    "op": "struct_field_set",
                    "struct_name": struct_name,
                    "offset": offset,
                    "field_name": name,
                    "field_type": field_type,
                }
            )

    existing_prototypes = current_prototypes(
        repo_root,
        target=target,
        identifiers=(identifier for identifier, _prototype in proto_update_list),
    )
    for identifier, prototype in proto_update_list:
        existing = existing_prototypes.get(identifier)
        existing_normalized = (
            normalize_prototype(existing, identifier=identifier) if existing is not None else None
        )
        if existing_normalized == normalize_prototype(prototype, identifier=identifier):
            skipped.append(
                {
                    "op": "proto_set",
                    "status": "skipped",
                    "reason": "already current",
                    "identifier": identifier,
                    "prototype": prototype,
                }
            )
            continue
        batch_ops.append(
            {
                "op": "set_prototype",
                "identifier": identifier,
                "prototype": prototype,
            }
        )

    if not batch_ops:
        return skipped
    preview = run_bn_batch(
        repo_root,
        target=target,
        operations=batch_ops,
        preview=True,
    )
    field_ops = [operation for operation in batch_ops if operation["op"] == "struct_field_set"]
    direct_proto_updates = [
        (str(operation["identifier"]), str(operation["prototype"]))
        for operation in batch_ops
        if operation["op"] == "set_prototype"
    ]
    applied: list[dict[str, object]] = []
    if field_ops:
        applied.append(
            {
                "op": "struct_field_batch",
                "operation_count": len(field_ops),
                "result": run_bn_batch(
                    repo_root,
                    target=target,
                    operations=field_ops,
                    preview=False,
                ),
            }
        )
    if direct_proto_updates:
        applied.append(
            apply_direct_proto_updates_batch(
                repo_root,
                target=target,
                updates=direct_proto_updates,
            )
        )
    return [
        *skipped,
        {
            "op": "batch_apply",
            "operation_count": len(batch_ops),
            "operations": batch_ops,
            "preview": {
                "success": preview.get("success"),
                "message": preview.get("message"),
                "affected_type_count": len(preview.get("affected_types", ())),
                "affected_function_count": len(preview.get("affected_functions", ())),
            },
            "applied": applied,
        },
    ]


def int_display_operations(
    updates: Iterable[IntDisplayUpdate],
) -> list[dict[str, object]]:
    return [
        {
            "op": "int_display_set",
            "identifier": identifier,
            "address": address,
            "expected_bytes": expected_bytes,
            "value": value,
            "operand": operand,
            "display_type": display_type,
            "required_hlil": required_hlil,
            "forbidden_hlil": forbidden_hlil,
        }
        for (
            identifier,
            address,
            expected_bytes,
            value,
            operand,
            display_type,
            required_hlil,
            forbidden_hlil,
        ) in updates
    ]


def apply_int_display_updates(
    repo_root: Path,
    *,
    target: str,
    updates: Iterable[IntDisplayUpdate],
) -> list[dict[str, object]]:
    operations = int_display_operations(updates)
    if not operations:
        return []

    preview = run_bn_batch(
        repo_root,
        target=target,
        operations=operations,
        preview=True,
    )
    preview_results = preview.get("results")
    if (
        not isinstance(preview_results, list)
        or len(preview_results) != len(operations)
        or any(
            not isinstance(entry, dict)
            or not isinstance(entry.get("changed"), bool)
            for entry in preview_results
        )
    ):
        raise RuntimeError(
            f"Binary Ninja integer-display preview is malformed: {preview!r}"
        )
    if all(entry["changed"] is False for entry in preview_results):
        return [
            {
                **operation,
                "status": "skipped",
                "reason": "already current",
            }
            for operation in operations
        ]

    applied = run_bn_batch(
        repo_root,
        target=target,
        operations=operations,
        preview=False,
    )
    return [
        {
            "op": "int_display_batch",
            "operation_count": len(operations),
            "operations": operations,
            "preview": {
                "success": preview.get("success"),
                "message": preview.get("message"),
                "affected_function_count": len(
                    preview.get("affected_functions", ())
                ),
            },
            "result": applied,
        }
    ]


def instruction_comment_operations(
    updates: Iterable[InstructionCommentUpdate],
) -> list[dict[str, object]]:
    return [
        {
            "op": "instruction_comment_set",
            "identifier": identifier,
            "address": address,
            "expected_bytes": expected_bytes,
            "comment": comment,
        }
        for identifier, address, expected_bytes, comment in updates
    ]


def apply_instruction_comment_updates(
    repo_root: Path,
    *,
    target: str,
    updates: Iterable[InstructionCommentUpdate],
) -> list[dict[str, object]]:
    operations = instruction_comment_operations(updates)
    if not operations:
        return []

    preview = run_bn_batch(
        repo_root,
        target=target,
        operations=operations,
        preview=True,
    )
    preview_results = preview.get("results")
    if (
        not isinstance(preview_results, list)
        or len(preview_results) != len(operations)
        or any(
            not isinstance(entry, dict)
            or not isinstance(entry.get("changed"), bool)
            for entry in preview_results
        )
    ):
        raise RuntimeError(
            f"Binary Ninja instruction-comment preview is malformed: {preview!r}"
        )
    if all(entry["changed"] is False for entry in preview_results):
        return [
            {
                **operation,
                "status": "skipped",
                "reason": "already current",
            }
            for operation in operations
        ]

    applied = run_bn_batch(
        repo_root,
        target=target,
        operations=operations,
        preview=False,
    )
    return [
        {
            "op": "instruction_comment_batch",
            "operation_count": len(operations),
            "operations": operations,
            "preview": {
                "success": preview.get("success"),
                "message": preview.get("message"),
                "affected_function_count": len(
                    preview.get("affected_functions", ())
                ),
            },
            "result": applied,
        }
    ]


def user_var_operations(
    updates: Iterable[UserVarUpdate],
) -> list[dict[str, object]]:
    return [
        {
            "op": "user_var_set",
            "identifier": identifier,
            "source_type": source_type,
            "index": index,
            "storage": storage,
            "variable_name": variable_name,
            "variable_type": variable_type,
        }
        for (
            identifier,
            source_type,
            index,
            storage,
            variable_name,
            variable_type,
        ) in updates
    ]


def user_var_removal_operations(
    removals: Iterable[UserVarRemoval],
) -> list[dict[str, object]]:
    return [
        {
            "op": "user_var_delete",
            "identifier": identifier,
            "source_type": source_type,
            "index": index,
            "storage": storage,
            "variable_name": variable_name,
            "variable_type": variable_type,
        }
        for (
            identifier,
            source_type,
            index,
            storage,
            variable_name,
            variable_type,
        ) in removals
    ]


def current_user_var_states(
    repo_root: Path,
    *,
    target: str,
    operations: list[dict[str, object]],
) -> list[dict[str, object]]:
    code = """
import json

operations = json.loads(__OPERATIONS_JSON__)


def find_function(identifier):
    text = str(identifier)
    try:
        address = int(text, 0)
    except ValueError:
        functions = list(bv.get_functions_by_name(text))
        if len(functions) != 1:
            raise RuntimeError(
                f"expected one function named {text}, found {len(functions)}"
            )
        return functions[0]
    function = bv.get_function_at(address)
    if function is None:
        raise RuntimeError(f"function not found at {address:#x}")
    return function


def function_variables(function):
    by_identity = {}
    variable_sources = [function.vars]
    for il in (
        getattr(function, "hlil", None),
        getattr(function, "mlil", None),
    ):
        if il is not None:
            variable_sources.append(il.vars)
    for variables in variable_sources:
        for variable in variables:
            identity = (
                str(variable.source_type).split(".")[-1],
                int(variable.index),
                int(variable.storage),
            )
            by_identity.setdefault(identity, variable)
    return list(by_identity.values())


def find_variable(function, operation, *, allow_missing=False):
    expected_source = str(operation["source_type"]).split(".")[-1]
    expected_index = int(operation["index"])
    expected_storage = int(operation["storage"])
    candidates = [
        variable
        for variable in function_variables(function)
        if str(variable.source_type).split(".")[-1] == expected_source
        and int(variable.index) == expected_index
        and int(variable.storage) == expected_storage
    ]
    if not candidates and allow_missing:
        return None
    if len(candidates) != 1:
        raise RuntimeError(
            f"expected one {expected_source} variable at index {expected_index}, "
            f"storage {expected_storage}, found {len(candidates)}"
        )
    return candidates[0]


user_vars = []
for operation in operations:
    function = find_function(operation["identifier"])
    deleting = operation["op"] == "user_var_delete"
    variable = find_variable(function, operation, allow_missing=deleting)
    observed = (
        None
        if variable is None
        else {
            "name": str(variable.name),
            "type": str(variable.type),
            "user_defined": bool(function.is_var_user_defined(variable)),
        }
    )
    user_vars.append({
        "identifier": str(operation["identifier"]),
        "source_type": str(operation["source_type"]),
        "index": int(operation["index"]),
        "storage": int(operation["storage"]),
        "observed": observed,
    })

result = {"user_vars": user_vars}
""".replace("__OPERATIONS_JSON__", repr(json.dumps(operations)))
    response = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        code,
    )
    payload = response.get("result") if isinstance(response, dict) else None
    if not isinstance(payload, dict):
        raise RuntimeError(f"Binary Ninja analysis readback is malformed: {response!r}")

    user_vars = payload.get("user_vars")
    if not isinstance(user_vars, list) or len(user_vars) != len(operations):
        raise RuntimeError(
            f"Binary Ninja user-variable readback is malformed: {response!r}"
        )
    for operation, entry in zip(operations, user_vars, strict=True):
        observed = entry.get("observed") if isinstance(entry, dict) else None
        deleting = operation.get("op") == "user_var_delete"
        expected = {
            "name": str(operation["variable_name"]),
            "type": str(operation["variable_type"]),
            "user_defined": not deleting,
        }
        entry["expected"] = expected
        if observed is None and deleting:
            entry["changed"] = False
            entry["missing"] = True
            continue
        if (
            not isinstance(observed, dict)
            or not isinstance(observed.get("name"), str)
            or not isinstance(observed.get("type"), str)
            or not isinstance(observed.get("user_defined"), bool)
        ):
            raise RuntimeError(
                f"Binary Ninja user-variable readback has invalid entries: {response!r}"
            )
        if deleting:
            entry["changed"] = observed["user_defined"] is True
        else:
            entry["changed"] = (
                observed["name"] != expected["name"]
                or normalize_type_name(observed["type"])
                != normalize_type_name(expected["type"])
                or observed["user_defined"] is not True
            )
    return user_vars


def apply_user_var_updates(
    repo_root: Path,
    *,
    target: str,
    updates: Iterable[UserVarUpdate],
) -> list[dict[str, object]]:
    operations = user_var_operations(updates)
    if not operations:
        return []

    current_results = current_user_var_states(
        repo_root,
        target=target,
        operations=operations,
    )
    if len(current_results) != len(operations) or any(
        not isinstance(entry.get("changed"), bool) for entry in current_results
    ):
        raise RuntimeError("Binary Ninja user-variable preflight does not match updates")
    pending_operations = [
        operation
        for operation, current in zip(operations, current_results, strict=True)
        if current["changed"] is True
    ]
    skipped_operations = [
        {
            **operation,
            "status": "skipped",
            "reason": "already current",
        }
        for operation, current in zip(operations, current_results, strict=True)
        if current["changed"] is False
    ]
    if not pending_operations:
        return skipped_operations

    preview = run_bn_batch(
        repo_root,
        target=target,
        operations=pending_operations,
        preview=True,
    )
    preview_results = preview.get("results")
    if not isinstance(preview_results, list):
        raise RuntimeError(f"Binary Ninja user-variable preview is malformed: {preview!r}")
    if all(
        isinstance(entry, dict) and entry.get("changed") is False
        for entry in preview_results
    ):
        return [
            *skipped_operations,
            *[
                {
                    **operation,
                    "status": "skipped",
                    "reason": "already current",
                }
                for operation in pending_operations
            ],
        ]

    applied = run_bn_batch(
        repo_root,
        target=target,
        operations=pending_operations,
        preview=False,
    )
    return [
        *skipped_operations,
        {
            "op": "user_var_batch",
            "operation_count": len(pending_operations),
            "operations": pending_operations,
            "preview": {
                "success": preview.get("success"),
                "message": preview.get("message"),
                "affected_function_count": len(
                    preview.get("affected_functions", ())
                ),
            },
            "result": applied,
        }
    ]


def remove_user_var_updates(
    repo_root: Path,
    *,
    target: str,
    removals: Iterable[UserVarRemoval],
) -> list[dict[str, object]]:
    operations = user_var_removal_operations(removals)
    if not operations:
        return []

    current_results = current_user_var_states(
        repo_root,
        target=target,
        operations=operations,
    )
    if len(current_results) != len(operations) or any(
        not isinstance(entry.get("changed"), bool) for entry in current_results
    ):
        raise RuntimeError("Binary Ninja user-variable removal preflight is malformed")
    if all(entry["changed"] is False for entry in current_results):
        return [
            {
                **operation,
                "status": "skipped",
                "reason": "already automatic",
            }
            for operation in operations
        ]

    preview = run_bn_batch(
        repo_root,
        target=target,
        operations=operations,
        preview=True,
    )
    preview_results = preview.get("results")
    if not isinstance(preview_results, list):
        raise RuntimeError(
            f"Binary Ninja user-variable removal preview is malformed: {preview!r}"
        )
    if all(
        isinstance(entry, dict) and entry.get("changed") is False
        for entry in preview_results
    ):
        return [
            {
                **operation,
                "status": "skipped",
                "reason": "already automatic",
            }
            for operation in operations
        ]

    applied = run_bn_batch(
        repo_root,
        target=target,
        operations=operations,
        preview=False,
    )
    return [
        {
            "op": "user_var_delete_batch",
            "operation_count": len(operations),
            "operations": operations,
            "preview": {
                "success": preview.get("success"),
                "message": preview.get("message"),
                "affected_function_count": len(
                    preview.get("affected_functions", ())
                ),
            },
            "result": applied,
        }
    ]


def split_user_var_operations(
    updates: Iterable[SplitUserVarUpdate],
    *,
    merge_definitions: bool = True,
    operation_name: str = "split_user_var_set",
) -> list[dict[str, object]]:
    operations: list[dict[str, object]] = []
    relevant_keys_by_identifier: dict[str, set[SplitVarSpec]] = {}
    for identifier, definitions, target_var, variable_name, variable_type in updates:
        definition_list = [
            {
                "address": str(address),
                "view": view,
                "source_type": str(source_type).split(".")[-1],
                "index": int(index),
                "storage": int(storage),
            }
            for address, view, source_type, index, storage in definitions
        ]
        if not definition_list:
            continue
        if any(
            definition["view"] not in {"mlil", "mlil_ssa"}
            for definition in definition_list
        ):
            raise ValueError(
                "split-variable definitions require mlil or mlil_ssa views"
            )

        target_source_type, target_index, target_storage = target_var
        target_spec = {
            "source_type": str(target_source_type).split(".")[-1],
            "index": int(target_index),
            "storage": int(target_storage),
        }
        definition_keys = {
            (
                str(definition["source_type"]),
                int(definition["index"]),
                int(definition["storage"]),
            )
            for definition in definition_list
        }
        if len(definition_keys) != len(definition_list):
            raise ValueError(
                "split-variable definitions require unique variable identities"
            )
        target_key = (
            str(target_spec["source_type"]),
            int(target_spec["index"]),
            int(target_spec["storage"]),
        )
        if merge_definitions and target_key not in definition_keys:
            raise ValueError(
                "split-variable target must be one of the definition identities"
            )
        if not merge_definitions and target_key in definition_keys:
            raise ValueError(
                "split-away residual target must not be a detached definition"
            )

        identifier_text = str(identifier)
        relevant_keys = definition_keys | {target_key}
        prior_keys = relevant_keys_by_identifier.setdefault(identifier_text, set())
        overlapping_keys = prior_keys & relevant_keys
        if overlapping_keys:
            raise ValueError(
                "split-variable batch updates require disjoint identities per "
                f"function; {identifier_text!r} repeats {sorted(overlapping_keys)!r}"
            )
        prior_keys.update(relevant_keys)
        operations.append(
            {
                "op": operation_name,
                "identifier": identifier_text,
                "definitions": definition_list,
                "target_var": target_spec,
                "variable_name": variable_name,
                "variable_type": variable_type,
                "merge_definitions": merge_definitions,
            }
        )
    return operations


def _split_user_var_batch_python_code(
    operations: list[dict[str, object]], *, preview: bool
) -> str:
    template = """
import json

operations = json.loads(__OPERATIONS_JSON__)
preview = __PREVIEW__


def find_function(identifier):
    text = str(identifier)
    try:
        address = int(text, 0)
    except ValueError:
        functions = list(bv.get_functions_by_name(text))
        if len(functions) != 1:
            raise RuntimeError(
                f"expected one function named {text}, found {len(functions)}"
            )
        return functions[0]
    function = bv.get_function_at(address)
    if function is None:
        raise RuntimeError(f"function not found at {address:#x}")
    return function


def source_type_name(variable):
    return str(variable.source_type).split(".")[-1]


def variable_key(variable):
    return (
        source_type_name(variable),
        int(variable.index),
        int(variable.storage),
    )


def spec_key(spec):
    return (
        str(spec["source_type"]).split(".")[-1],
        int(spec["index"]),
        int(spec["storage"]),
    )


def known_variables(function):
    variables = {}
    for variable in function.vars:
        variables[variable_key(variable)] = variable
    for variable in function.split_vars:
        variables.setdefault(variable_key(variable), variable)
    for merge_target, sources in function.merged_vars.items():
        variables.setdefault(variable_key(merge_target), merge_target)
        for source in sources:
            variables.setdefault(variable_key(source), source)
    return variables


def find_current_variable(function, spec):
    return known_variables(function).get(spec_key(spec))


def find_definition_variable(function, spec):
    address = int(str(spec["address"]), 0)
    il = function.mlil.ssa_form if spec["view"] == "mlil_ssa" else function.mlil
    candidates = {}
    for instruction in il.instructions:
        if int(instruction.address) != address:
            continue
        definition_outputs = list(instruction.vars_written)
        destination = getattr(instruction, "dest", None)
        if destination is not None:
            definition_outputs.append(destination)
        for written in definition_outputs:
            base_variable = written.var if hasattr(written, "var") else written
            if not all(
                hasattr(base_variable, attribute)
                for attribute in ("source_type", "index", "storage")
            ):
                continue
            try:
                candidate = instruction.get_split_var_for_definition(base_variable)
            except Exception:
                continue
            if variable_key(candidate) == spec_key(spec):
                candidates[variable_key(candidate)] = candidate
    if len(candidates) != 1:
        raise RuntimeError(
            f"expected one split variable for {spec!r}, found {len(candidates)}"
        )
    return next(iter(candidates.values()))


def merge_snapshot(function):
    return sorted(
        (
            variable_key(merge_target),
            tuple(sorted(variable_key(source) for source in sources)),
        )
        for merge_target, sources in function.merged_vars.items()
    )


def state_snapshot(function, relevant_keys):
    relevant_variables = sorted(
        (
            variable_key(variable),
            str(variable.name),
            str(variable.type),
            bool(function.is_var_user_defined(variable)),
        )
        for variable in function.vars
        if variable_key(variable) in relevant_keys
    )
    return {
        "split_vars": sorted(variable_key(variable) for variable in function.split_vars),
        "merged_vars": merge_snapshot(function),
        "relevant_variables": relevant_variables,
        "hlil": str(function.hlil),
    }


def inspect_expected_state(function, operation, expected_type):
    definitions = operation["definitions"]
    target_spec = operation["target_var"]
    variable_name = operation["variable_name"]
    merge_definitions = bool(operation["merge_definitions"])
    definition_keys = {spec_key(spec) for spec in definitions}
    expected_target_key = spec_key(target_spec)
    relevant_keys = definition_keys | {expected_target_key}
    expected_source_keys = (
        definition_keys - {expected_target_key} if merge_definitions else set()
    )
    split_keys = {variable_key(variable) for variable in function.split_vars}
    variables = {
        variable_key(variable): variable
        for variable in function.vars
        if variable_key(variable) in relevant_keys
    }
    merge_entries = {
        variable_key(merge_target): {variable_key(source) for source in sources}
        for merge_target, sources in function.merged_vars.items()
    }
    for merge_target_key, source_keys in merge_entries.items():
        touched = ({merge_target_key} | source_keys) & relevant_keys
        safe_same_target_extension = (
            merge_definitions
            and merge_target_key == expected_target_key
            and source_keys.issubset(expected_source_keys)
        )
        if touched and not safe_same_target_extension:
            raise RuntimeError(
                "refusing to replace conflicting variable merge: "
                f"target={merge_target_key!r}, sources={sorted(source_keys)!r}"
            )
    target_variable = variables.get(expected_target_key)
    target_current = (
        target_variable is not None
        and str(target_variable.name) == variable_name
        and str(target_variable.type) == str(expected_type)
        and bool(function.is_var_user_defined(target_variable))
    )
    if merge_definitions:
        merge_current = (
            merge_entries.get(expected_target_key) == expected_source_keys
            if expected_source_keys
            else expected_target_key not in merge_entries
        )
    else:
        merge_current = not any(
            ({merge_target_key} | source_keys) & relevant_keys
            for merge_target_key, source_keys in merge_entries.items()
        )
    return {
        "all_split": definition_keys.issubset(split_keys),
        "merge_current": merge_current,
        "target_current": target_current,
        "expected_target_key": expected_target_key,
        "expected_source_keys": expected_source_keys,
    }


functions = {}
relevant_keys_by_identifier = {}
runtime_operations = []
for operation in operations:
    identifier = str(operation["identifier"])
    if identifier not in functions:
        functions[identifier] = find_function(identifier)
    function = functions[identifier]
    relevant_keys_by_identifier.setdefault(identifier, set()).update(
        {spec_key(spec) for spec in operation["definitions"]}
        | {spec_key(operation["target_var"])}
    )
    expected_type, _ = bv.parse_type_string(operation["variable_type"])
    runtime_operations.append((operation, function, expected_type))

before_by_identifier = {
    identifier: state_snapshot(
        function,
        relevant_keys_by_identifier[identifier],
    )
    for identifier, function in functions.items()
}
state = bv.begin_undo_actions()
undo_closed = False
snapshot_saved = False
changed_identifiers = []
try:
    expected_states = []
    changed_operations = []
    for operation, function, expected_type in runtime_operations:
        expected = inspect_expected_state(function, operation, expected_type)
        changed = not (
            expected["all_split"]
            and expected["merge_current"]
            and expected["target_current"]
        )
        expected_states.append(expected)
        changed_operations.append(changed)
        if changed:
            changed_identifiers.append(str(operation["identifier"]))

    # Resolve every definition against the same pre-mutation IL. Splitting one
    # lifetime can renumber later IL identities after analysis, so no lookup is
    # allowed after the first split until the single analysis pass completes.
    pending_splits = []
    for runtime, changed in zip(runtime_operations, changed_operations):
        operation, function, _ = runtime
        if not changed:
            continue
        current_split_keys = {
            variable_key(variable) for variable in function.split_vars
        }
        for definition in operation["definitions"]:
            if spec_key(definition) not in current_split_keys:
                pending_splits.append(
                    (function, find_definition_variable(function, definition))
                )
    for function, split_variable in pending_splits:
        function.split_var(split_variable)
    if pending_splits:
        bv.update_analysis_and_wait()

    resolved_by_operation = []
    for runtime, expected, changed in zip(
        runtime_operations,
        expected_states,
        changed_operations,
    ):
        operation, function, _ = runtime
        if not changed:
            resolved_by_operation.append({})
            continue
        resolved_variables = {}
        for definition in operation["definitions"]:
            variable = find_current_variable(function, definition)
            if variable is None:
                raise RuntimeError(
                    f"split variable missing after apply: {definition!r}"
                )
            resolved_variables[spec_key(definition)] = variable
        expected_target_key = expected["expected_target_key"]
        if expected_target_key not in resolved_variables:
            target_variable = find_current_variable(
                function,
                operation["target_var"],
            )
            if target_variable is None:
                raise RuntimeError(
                    "residual target variable missing after split: "
                    f"{operation['target_var']!r}"
                )
            resolved_variables[expected_target_key] = target_variable
        resolved_by_operation.append(resolved_variables)

    for runtime, expected, changed, resolved_variables in zip(
        runtime_operations,
        expected_states,
        changed_operations,
        resolved_by_operation,
    ):
        operation, function, expected_type = runtime
        if not changed:
            continue
        expected_target_key = expected["expected_target_key"]
        expected_source_keys = expected["expected_source_keys"]
        current_merge_entries = {
            variable_key(merge_target): {
                variable_key(source) for source in sources
            }
            for merge_target, sources in function.merged_vars.items()
        }
        if (
            operation["merge_definitions"]
            and expected_source_keys
            and current_merge_entries.get(expected_target_key)
            != expected_source_keys
        ):
            function.merge_vars(
                resolved_variables[expected_target_key],
                [
                    resolved_variables[key]
                    for key in sorted(expected_source_keys)
                ],
            )
        function.create_user_var(
            resolved_variables[expected_target_key],
            expected_type,
            operation["variable_name"],
        )
    if changed_identifiers:
        bv.update_analysis_and_wait()

    for operation, function, expected_type in runtime_operations:
        observed = inspect_expected_state(function, operation, expected_type)
        verified = (
            observed["all_split"]
            and observed["merge_current"]
            and observed["target_current"]
        )
        if not verified:
            raise RuntimeError(
                "split user-variable verification failed for "
                f"{operation['identifier']!r}:{operation['variable_name']!r}"
            )
    after_by_identifier = {
        identifier: state_snapshot(
            function,
            relevant_keys_by_identifier[identifier],
        )
        for identifier, function in functions.items()
    }

    if preview:
        bv.revert_undo_actions(state)
        undo_closed = True
        if changed_identifiers:
            for identifier in dict.fromkeys(changed_identifiers):
                functions[identifier].reanalyze()
            bv.update_analysis_and_wait()
        restored_by_identifier = {
            identifier: state_snapshot(
                function,
                relevant_keys_by_identifier[identifier],
            )
            for identifier, function in functions.items()
        }
        if restored_by_identifier != before_by_identifier:
            raise RuntimeError("split user-variable batch rollback failed")
    else:
        bv.commit_undo_actions(state)
        undo_closed = True
        if changed_identifiers:
            snapshot_saved = bv.file.save_auto_snapshot()
            if snapshot_saved is not True:
                raise RuntimeError(
                    "Binary Ninja committed split lifetimes without saving "
                    "the database snapshot"
                )
except Exception:
    if not undo_closed:
        bv.revert_undo_actions(state)
        if changed_identifiers:
            for identifier in dict.fromkeys(changed_identifiers):
                functions[identifier].reanalyze()
            bv.update_analysis_and_wait()
    raise

operation_results = []
for runtime, changed in zip(runtime_operations, changed_operations):
    operation, _, _ = runtime
    identifier = str(operation["identifier"])
    operation_results.append({
        **operation,
        "changed": changed,
        "before_hlil": before_by_identifier[identifier]["hlil"],
        "after_hlil": after_by_identifier[identifier]["hlil"],
    })
result = {
    "success": True,
    "preview": preview,
    "committed": not preview,
    "changed": any(changed_operations),
    "snapshot_saved": snapshot_saved,
    "operation_results": operation_results,
}
if len(operation_results) == 1:
    result["operation"] = operation_results[0]
"""
    return template.replace(
        "__OPERATIONS_JSON__", repr(json.dumps(operations))
    ).replace("__PREVIEW__", repr(preview))


def _run_split_user_var_batch(
    repo_root: Path,
    *,
    target: str,
    operations: list[dict[str, object]],
    preview: bool,
) -> dict[str, object]:
    response = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        _split_user_var_batch_python_code(operations, preview=preview),
    )
    payload = response.get("result") if isinstance(response, dict) else None
    if (
        not isinstance(payload, dict)
        or payload.get("success") is not True
        or payload.get("preview") is not preview
        or payload.get("committed") is not (not preview)
        or not isinstance(payload.get("changed"), bool)
    ):
        phase = "preview" if preview else "apply"
        raise RuntimeError(
            f"Binary Ninja split user-variable batch {phase} failed: {response!r}"
        )
    operation_results = payload.get("operation_results")
    if (
        not isinstance(operation_results, list)
        and len(operations) == 1
        and isinstance(payload.get("operation"), dict)
    ):
        operation_results = [
            {
                **payload["operation"],
                "changed": payload["changed"],
            }
        ]
        payload["operation_results"] = operation_results
    if (
        not isinstance(operation_results, list)
        or len(operation_results) != len(operations)
        or any(
            not isinstance(result, dict)
            or not isinstance(result.get("changed"), bool)
            for result in operation_results
        )
    ):
        raise RuntimeError(
            f"Binary Ninja split user-variable batch result is malformed: {payload!r}"
        )
    return payload


def apply_split_user_var_updates(
    repo_root: Path,
    *,
    target: str,
    updates: Iterable[SplitUserVarUpdate],
    _merge_definitions: bool = True,
    _operation_name: str = "split_user_var_set",
) -> list[dict[str, object]]:
    operations = split_user_var_operations(
        updates,
        merge_definitions=_merge_definitions,
        operation_name=_operation_name,
    )
    if not operations:
        return []

    preview_result = _run_split_user_var_batch(
        repo_root,
        target=target,
        operations=operations,
        preview=True,
    )
    if preview_result["changed"]:
        applied_result = _run_split_user_var_batch(
            repo_root,
            target=target,
            operations=operations,
            preview=False,
        )
        if applied_result.get("snapshot_saved") is not True:
            raise RuntimeError(
                "split user-variable batch changed live analysis without a "
                "saved snapshot"
            )
        payload = applied_result
    else:
        payload = preview_result

    operation_results = payload["operation_results"]
    return [
        {
            "op": operation["op"],
            "identifier": operation["identifier"],
            "definitions": operation["definitions"],
            "target_var": operation["target_var"],
            "variable_name": operation["variable_name"],
            "variable_type": operation["variable_type"],
            "status": "verified" if result["changed"] else "skipped",
            "reason": None if result["changed"] else "already current",
        }
        for operation, result in zip(operations, operation_results, strict=True)
    ]


def apply_split_user_var_update(
    repo_root: Path,
    *,
    target: str,
    identifier: str,
    definitions: Iterable[SplitVarDefinition],
    target_var: SplitVarSpec,
    variable_name: str,
    variable_type: str,
    _merge_definitions: bool = True,
    _operation_name: str = "split_user_var_set",
) -> list[dict[str, object]]:
    return apply_split_user_var_updates(
        repo_root,
        target=target,
        updates=(
            (
                identifier,
                definitions,
                target_var,
                variable_name,
                variable_type,
            ),
        ),
        _merge_definitions=_merge_definitions,
        _operation_name=_operation_name,
    )


def apply_split_away_user_var_update(
    repo_root: Path,
    *,
    target: str,
    identifier: str,
    detached_definitions: Iterable[SplitVarDefinition],
    residual_var: SplitVarSpec,
    variable_name: str,
    variable_type: str,
) -> list[dict[str, object]]:
    """Split dead definitions away before typing the residual physical lifetime."""
    return apply_split_user_var_update(
        repo_root,
        target=target,
        identifier=identifier,
        definitions=detached_definitions,
        target_var=residual_var,
        variable_name=variable_name,
        variable_type=variable_type,
        _merge_definitions=False,
        _operation_name="split_away_user_var_set",
    )


def current_symbol_names(
    repo_root: Path, *, target: str, identifiers: Iterable[str]
) -> dict[str, str | None]:
    names = tuple(identifiers)
    code = f"""
identifiers = {json.dumps(names)}
result = {{}}
for identifier in identifiers:
    symbols = []
    try:
        address = int(identifier, 0)
    except ValueError:
        symbols = list(bv.get_symbols_by_name(identifier))
    else:
        symbol = bv.get_symbol_at(address)
        if symbol is not None:
            symbols = [symbol]
    result[identifier] = symbols[0].name if len(symbols) == 1 else None
"""
    response = run_bn(
        repo_root,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        code,
    )
    payload = response.get("result") if isinstance(response, dict) else None
    if not isinstance(payload, dict):
        return {identifier: None for identifier in names}
    return {
        identifier: value if isinstance(value := payload.get(identifier), str) else None
        for identifier in names
    }


def apply_symbol_updates(
    repo_root: Path,
    *,
    target: str,
    updates: Iterable[SymbolUpdate],
    kind: str = "auto",
) -> list[dict[str, object]]:
    update_list = list(updates)
    operations: list[dict[str, object]] = []
    existing_names = current_symbol_names(
        repo_root,
        target=target,
        identifiers=(identifier for identifier, _name in update_list),
    )
    for identifier, name in update_list:
        if existing_names.get(identifier) == name:
            operations.append(
                {
                    "op": "symbol_rename",
                    "status": "skipped",
                    "reason": "already current",
                    "identifier": identifier,
                    "name": name,
                    "kind": kind,
                }
            )
            continue
        command = [
            "symbol",
            "rename",
            "--target",
            target,
        ]
        if kind != "auto":
            command.extend(["--kind", kind])
        command.extend([identifier, name])
        operations.append(
            {
                "op": "symbol_rename",
                "identifier": identifier,
                "name": name,
                "kind": kind,
                "result": run_previewed_bn_mutation(repo_root, *command),
            }
        )
    return operations


def apply_symbol_removals(
    repo_root: Path,
    *,
    target: str,
    removals: Iterable[SymbolRemoval],
) -> list[dict[str, object]]:
    removal_list = list(removals)
    if not removal_list:
        return []

    current_names = current_symbol_names(
        repo_root,
        target=target,
        identifiers=(identifier for identifier, _name in removal_list),
    )
    skipped: list[dict[str, object]] = []
    batch_ops: list[dict[str, object]] = []
    for identifier, expected_name in removal_list:
        current_name = current_names.get(identifier)
        if current_name is None:
            skipped.append(
                {
                    "op": "symbol_undefine",
                    "status": "skipped",
                    "reason": "already absent",
                    "address": identifier,
                    "expected_name": expected_name,
                }
            )
            continue
        if current_name != expected_name:
            raise RuntimeError(
                f"refusing to undefine unexpected symbol at {identifier}: "
                f"expected {expected_name}, found {current_name}"
            )
        batch_ops.append(
            {
                "op": "undefine_symbol",
                "address": identifier,
                "expected_name": expected_name,
            }
        )

    if not batch_ops:
        return skipped
    return [
        *skipped,
        {
            "op": "symbol_undefine_batch",
            "operation_count": len(batch_ops),
            "operations": batch_ops,
            "result": run_previewed_bn_batch(
                repo_root,
                target=target,
                operations=batch_ops,
            ),
        },
    ]


def apply_data_var_updates(
    repo_root: Path,
    *,
    target: str,
    updates: Iterable[DataVarUpdate],
) -> list[dict[str, object]]:
    update_list = list(updates)
    if not update_list:
        return []

    def run_batch(*, preview: bool) -> dict[str, object]:
        code = f"""
updates = {json.dumps(update_list)}
preview = {preview!r}
out = []
state = bv.begin_undo_actions()
undo_closed = False
snapshot_saved = False
try:
    for address_text, type_text in updates:
        address = int(address_text, 0)
        parsed_type, _ = bv.parse_type_string(type_text)
        before = bv.get_data_var_at(address)
        before_type = str(before.type) if before is not None else None
        before_width = int(before.type.width) if before is not None else None
        requested_type = str(parsed_type)
        changed = before_type != requested_type
        if changed:
            bv.define_user_data_var(address, parsed_type)
        out.append({{
            "address": hex(address),
            "requested_type": type_text,
            "before_type": before_type,
            "before_width": before_width,
            "requested_rendered_type": requested_type,
            "changed": changed,
        }})

    changed_any = any(entry["changed"] for entry in out)
    for entry in out:
        address = int(entry["address"], 0)
        after = bv.get_data_var_at(address)
        entry["after_type"] = str(after.type) if after is not None else None
        entry["verified"] = entry["after_type"] == entry["requested_rendered_type"]
    if not all(entry["verified"] for entry in out):
        raise RuntimeError(f"data-variable verification failed: {{out!r}}")

    if preview:
        bv.revert_undo_actions(state)
        undo_closed = True
        for entry in out:
            address = int(entry["address"], 0)
            restored = bv.get_data_var_at(address)
            entry["restored_type"] = str(restored.type) if restored is not None else None
            entry["restored_width"] = (
                int(restored.type.width) if restored is not None else None
            )
            entry["reverted"] = (
                entry["restored_type"] == entry["before_type"]
                or (
                    entry["before_width"] in (None, 0)
                    and entry["restored_width"] in (None, 0)
                )
            )
        if not all(entry["reverted"] for entry in out):
            raise RuntimeError(f"data-variable preview rollback failed: {{out!r}}")
    else:
        bv.commit_undo_actions(state)
        undo_closed = True
        snapshot_saved = bv.file.save_auto_snapshot()
        if changed_any:
            bv.update_analysis()
except Exception:
    if not undo_closed:
        bv.revert_undo_actions(state)
    raise

result = {{
    "success": True,
    "preview": preview,
    "committed": not preview,
    "analysis_scheduled": changed_any and not preview,
    "results": out,
    "snapshot_saved": snapshot_saved,
}}
"""
        response = run_bn(
            repo_root,
            "py",
            "exec",
            "--target",
            target,
            "--format",
            "json",
            "--code",
            code,
        )
        payload = response.get("result") if isinstance(response, dict) else None
        if (
            not isinstance(payload, dict)
            or payload.get("success") is not True
            or payload.get("preview") is not preview
            or payload.get("committed") is not (not preview)
        ):
            phase = "preview" if preview else "apply"
            raise RuntimeError(f"Binary Ninja data-variable {phase} failed: {response!r}")
        return payload

    preview_result = run_batch(preview=True)
    preview_entries = preview_result.get("results")
    if not isinstance(preview_entries, list):
        raise RuntimeError(f"Binary Ninja data-variable preview is malformed: {preview_result!r}")

    changed = any(
        isinstance(entry, dict) and entry.get("changed") is True
        for entry in preview_entries
    )
    if changed:
        applied_result = run_batch(preview=False)
        if applied_result.get("snapshot_saved") is not True:
            raise RuntimeError(
                "data-variable batch changed the live analysis without a saved snapshot"
            )
        payload = applied_result.get("results")
        if not isinstance(payload, list):
            raise RuntimeError(
                f"Binary Ninja data-variable apply is malformed: {applied_result!r}"
            )
    else:
        payload = preview_entries

    return [
        {
            "op": "data_var_set",
            "address": entry.get("address"),
            "type": entry.get("requested_type"),
            "before_type": entry.get("before_type"),
            "after_type": entry.get("after_type"),
            "status": "verified" if entry.get("changed") else "skipped",
            "reason": None if entry.get("changed") else "already current",
        }
        for entry in payload
        if isinstance(entry, dict)
    ]


def apply_data_var_removals(
    repo_root: Path,
    *,
    target: str,
    removals: Iterable[DataVarRemoval],
    replacements: Iterable[DataVarUpdate] = (),
) -> list[dict[str, object]]:
    removal_list = list(removals)
    if not removal_list:
        return []

    replacement_map = dict(replacements)
    unknown_replacements = set(replacement_map).difference(
        address for address, _expected_type in removal_list
    )
    if unknown_replacements:
        raise ValueError(
            "data-variable replacements require matching removals: "
            f"{sorted(unknown_replacements)!r}"
        )

    def run_batch(*, preview: bool) -> dict[str, object]:
        code = f"""
removals = {json.dumps(removal_list)}
replacements = {json.dumps(replacement_map)}
preview = {preview!r}
out = []
state = bv.begin_undo_actions()
undo_closed = False
snapshot_saved = False
try:
    for address_text, expected_type_text in removals:
        address = int(address_text, 0)
        expected_type, _ = bv.parse_type_string(expected_type_text)
        expected_rendered_type = str(expected_type)
        replacement_type_text = replacements.get(address_text)
        replacement_rendered_type = None
        if replacement_type_text is not None:
            replacement_type, _ = bv.parse_type_string(replacement_type_text)
            replacement_rendered_type = str(replacement_type)

        before = bv.get_data_var_at(address)
        before_address = int(before.address) if before is not None else None
        before_type = str(before.type) if before is not None else None
        before_width = int(before.type.width) if before is not None else None
        before_auto_discovered = (
            bool(before.auto_discovered) if before is not None else None
        )
        already_absent = (
            before_width in (None, 0)
            or before_auto_discovered is True
        )
        already_replaced = (
            replacement_rendered_type is not None
            and before_type == replacement_rendered_type
        )
        covered_by_replacement = (
            already_replaced
            and before_address is not None
            and before_address != address
        )
        if already_absent:
            changed = False
            reason = "already absent"
        elif covered_by_replacement:
            changed = False
            reason = "already covered by replacement"
        elif already_replaced:
            changed = False
            reason = "already replaced"
        elif before_type != expected_rendered_type:
            raise RuntimeError(
                f"refusing to remove unexpected data variable at {{hex(address)}}: "
                f"expected {{expected_rendered_type}}, found {{before_type}}"
            )
        else:
            bv.undefine_user_data_var(address)
            changed = True
            reason = None

        out.append({{
            "address": hex(address),
            "expected_type": expected_type_text,
            "expected_rendered_type": expected_rendered_type,
            "replacement_type": replacement_type_text,
            "replacement_rendered_type": replacement_rendered_type,
            "before_address": hex(before_address) if before_address is not None else None,
            "before_type": before_type,
            "before_width": before_width,
            "before_auto_discovered": before_auto_discovered,
            "changed": changed,
            "reason": reason,
        }})

    bv.update_analysis_and_wait()
    for entry in out:
        address = int(entry["address"], 0)
        after = bv.get_data_var_at(address)
        entry["after_address"] = hex(int(after.address)) if after is not None else None
        entry["after_type"] = str(after.type) if after is not None else None
        entry["after_width"] = int(after.type.width) if after is not None else None
        entry["after_auto_discovered"] = (
            bool(after.auto_discovered) if after is not None else None
        )
        entry["verified"] = (
            (
                entry["after_width"] in (None, 0)
                or entry["after_auto_discovered"] is True
            )
            if entry["changed"]
            else (
                entry["after_address"] == entry["before_address"]
                and entry["after_type"] == entry["before_type"]
                and entry["after_width"] == entry["before_width"]
                and entry["after_auto_discovered"]
                == entry["before_auto_discovered"]
            )
        )
    if not all(entry["verified"] for entry in out):
        raise RuntimeError(f"data-variable removal verification failed: {{out!r}}")

    if preview:
        bv.revert_undo_actions(state)
        undo_closed = True
        bv.update_analysis_and_wait()
        for entry in out:
            address = int(entry["address"], 0)
            restored = bv.get_data_var_at(address)
            entry["restored_address"] = (
                hex(int(restored.address)) if restored is not None else None
            )
            entry["restored_type"] = str(restored.type) if restored is not None else None
            entry["restored_width"] = (
                int(restored.type.width) if restored is not None else None
            )
            entry["restored_auto_discovered"] = (
                bool(restored.auto_discovered) if restored is not None else None
            )
            entry["reverted"] = (
                entry["restored_address"] == entry["before_address"]
                and entry["restored_type"] == entry["before_type"]
                and entry["restored_width"] == entry["before_width"]
                and entry["restored_auto_discovered"]
                == entry["before_auto_discovered"]
            )
        if not all(entry["reverted"] for entry in out):
            raise RuntimeError(f"data-variable removal rollback failed: {{out!r}}")
    else:
        bv.commit_undo_actions(state)
        undo_closed = True
        snapshot_saved = bv.file.save_auto_snapshot()
except Exception:
    if not undo_closed:
        bv.revert_undo_actions(state)
        bv.update_analysis_and_wait()
    raise

result = {{
    "success": True,
    "preview": preview,
    "committed": not preview,
    "results": out,
    "snapshot_saved": snapshot_saved,
}}
"""
        response = run_bn(
            repo_root,
            "py",
            "exec",
            "--target",
            target,
            "--format",
            "json",
            "--code",
            code,
        )
        payload = response.get("result") if isinstance(response, dict) else None
        if (
            not isinstance(payload, dict)
            or payload.get("success") is not True
            or payload.get("preview") is not preview
            or payload.get("committed") is not (not preview)
        ):
            phase = "preview" if preview else "apply"
            raise RuntimeError(
                f"Binary Ninja data-variable removal {phase} failed: {response!r}"
            )
        return payload

    preview_result = run_batch(preview=True)
    preview_entries = preview_result.get("results")
    if not isinstance(preview_entries, list):
        raise RuntimeError(
            f"Binary Ninja data-variable removal preview is malformed: {preview_result!r}"
        )

    changed = any(
        isinstance(entry, dict) and entry.get("changed") is True
        for entry in preview_entries
    )
    if changed:
        applied_result = run_batch(preview=False)
        if applied_result.get("snapshot_saved") is not True:
            raise RuntimeError(
                "data-variable removal changed the live analysis without a saved snapshot"
            )
        payload = applied_result.get("results")
        if not isinstance(payload, list):
            raise RuntimeError(
                f"Binary Ninja data-variable removal apply is malformed: {applied_result!r}"
            )
    else:
        payload = preview_entries

    return [
        {
            "op": "data_var_remove",
            "address": entry.get("address"),
            "expected_type": entry.get("expected_type"),
            "replacement_type": entry.get("replacement_type"),
            "before_type": entry.get("before_type"),
            "after_type": entry.get("after_type"),
            "status": "verified" if entry.get("changed") else "skipped",
            "reason": entry.get("reason"),
        }
        for entry in payload
        if isinstance(entry, dict)
    ]


def emit_summary(*, repo_root: Path, target: str, header_path: Path, operations: list[dict[str, object]]) -> int:
    json.dump(
        {
            "tool": "binary_ninja",
            "target": target,
            "header": str(header_path.relative_to(repo_root)),
            "operations": operations,
        },
        sys.stdout,
        indent=2,
        sort_keys=True,
    )
    sys.stdout.write("\n")
    return 0
