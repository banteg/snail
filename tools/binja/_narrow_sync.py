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
DataVarUpdate = tuple[str, str]
StructUpdateGroup = tuple[str, Iterable[FieldUpdate]]


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


def find_member(type_obj, offset):
    for member in list(getattr(type_obj, "members", ())):
        if int(getattr(member, "offset", -1)) == offset:
            return member
    return None


state = bv.begin_undo_actions()
undo_closed = False
results = []
affected_functions = []
affected_types = []
snapshot_saved = False
try:
    for operation in operations:
        kind = operation["op"]
        if kind == "set_prototype":
            function = find_function(operation["identifier"])
            expected_type, _ = bv.parse_type_string(str(operation["prototype"]))
            before = str(function.type)
            expected = str(expected_type)
            if before != expected:
                try:
                    function.set_user_type(expected_type)
                except TypeError:
                    function.set_user_type(expected)
            results.append({
                "op": kind,
                "identifier": str(operation["identifier"]),
                "function": str(function.name),
                "address": hex(int(function.start)),
                "before": before,
                "expected": expected,
            })
            affected_functions.append(str(function.name))
            continue

        if kind == "struct_field_set":
            struct_name = str(operation["struct_name"])
            type_obj = bv.get_type_by_name(struct_name)
            if type_obj is None:
                raise RuntimeError(f"struct not found: {struct_name}")
            builder = type_obj.mutable_copy()
            field_type, _ = bv.parse_type_string(str(operation["field_type"]))
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

    bv.update_analysis_and_wait()
    for entry in results:
        if entry["op"] == "set_prototype":
            function = find_function(entry["identifier"])
            observed = str(function.type)
            entry["observed"] = observed
            entry["verified"] = observed == entry["expected"]
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
        entry["status"] = "verified"

    if preview:
        bv.revert_undo_actions(state)
        undo_closed = True
        bv.update_analysis_and_wait()
    else:
        bv.commit_undo_actions(state)
        undo_closed = True
        snapshot_saved = bv.file.save_auto_snapshot()
except Exception:
    if not undo_closed:
        bv.revert_undo_actions(state)
        bv.update_analysis_and_wait()
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
    # bridge round trip by replaying the two narrow mutation kinds used by the
    # ownership sync scripts through `bn py exec` instead of regressing to one
    # process and analysis pass per field.
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


def apply_direct_proto_updates_batch(
    repo_root: Path, *, target: str, updates: Iterable[ProtoUpdate]
) -> dict[str, object]:
    update_list = list(updates)
    code = f"""
updates = {json.dumps(update_list)}
state = bv.begin_undo_actions()
applied = []
try:
    for identifier, prototype in updates:
        functions = list(bv.get_functions_by_name(identifier))
        if len(functions) != 1:
            raise RuntimeError(
                f"expected one function named {{identifier}}, found {{len(functions)}}"
            )
        fn = functions[0]
        before = str(fn.type)
        parsed_type, _ = bv.parse_type_string(prototype)
        fn.set_user_type(parsed_type)
        applied.append({{
            "identifier": identifier,
            "before": before,
            "requested": str(parsed_type),
        }})
    bv.update_analysis_and_wait()
    for entry in applied:
        fn = list(bv.get_functions_by_name(entry["identifier"]))[0]
        entry["after"] = str(fn.type)
        entry["verified"] = entry["after"] == entry["requested"]
    if not all(entry["verified"] for entry in applied):
        raise RuntimeError(f"direct prototype verification failed: {{applied!r}}")
    bv.commit_undo_actions(state)
    snapshot_saved = bv.file.save_auto_snapshot()
except Exception:
    bv.revert_undo_actions(state)
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
    return {
        "op": "types_declare",
        "result": run_bn(repo_root, "types", "declare", "--target", target, "--file", str(header_path)),
    }


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

    code = f"""
import binaryninja

header_path = {json.dumps(str(header_path))}
replacement_names = set({json.dumps(replacement_names)})
included_names = set({json.dumps(included_names)})
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

candidates = []
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

applied = []
for parsed_type, before_width in sorted(candidates, key=lambda item: item[0].type.width):
    bv.define_user_type(parsed_type.name, parsed_type.type)
    applied.append({{
        "name": str(parsed_type.name),
        "before_width": before_width,
        "after_width": parsed_type.type.width,
    }})

bv.update_analysis_and_wait()
verification = []
for entry in applied:
    observed = bv.get_type_by_name(entry["name"])
    observed_width = observed.width if observed is not None else None
    verification.append({{
        **entry,
        "observed_width": observed_width,
        "verified": observed_width == entry["after_width"],
    }})
if not all(entry["verified"] for entry in verification):
    raise RuntimeError(f"selective type declaration verification failed: {{verification!r}}")

snapshot_saved = bv.file.save_auto_snapshot()
result = {{
    "applied": verification,
    "snapshot_saved": snapshot_saved,
}}
"""
    applied = run_bn(
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
    return {
        "op": "types_declare_missing_only",
        "header": str(header_path),
        "replace_types": replacement_names,
        "include_types": included_names,
        "preview": {
            "success": preview.get("success"),
            "message": preview.get("message"),
            "affected_type_count": len(preview.get("affected_types", ())),
            "affected_function_count": len(preview.get("affected_functions", ())),
        },
        "result": applied,
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
    normalized = re.sub(r"\b(?:struct|enum)\s+", "", type_name)
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


def apply_data_var_updates(
    repo_root: Path,
    *,
    target: str,
    updates: Iterable[DataVarUpdate],
) -> list[dict[str, object]]:
    update_list = list(updates)
    if not update_list:
        return []

    code = f"""
updates = {json.dumps(update_list)}
out = []
for address_text, type_text in updates:
    address = int(address_text, 0)
    parsed_type, _ = bv.parse_type_string(type_text)
    before = bv.get_data_var_at(address)
    before_type = str(before.type) if before is not None else None
    requested_type = str(parsed_type)
    changed = before_type != requested_type
    if changed:
        bv.define_user_data_var(address, parsed_type)
    after = bv.get_data_var_at(address)
    out.append({{
        "address": hex(address),
        "requested_type": type_text,
        "before_type": before_type,
        "after_type": str(after.type) if after is not None else None,
        "changed": changed,
    }})
result = out
"""
    result = run_bn(repo_root, "py", "exec", "--target", target, "--format", "json", "--code", code)
    payload = result.get("result") if isinstance(result, dict) else None
    if not isinstance(payload, list):
        payload = []
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
