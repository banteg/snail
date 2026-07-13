from __future__ import annotations

import json
from pathlib import Path
import re
import subprocess
import sys
import tempfile
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


def run_bn(repo_root: Path, *args: str) -> object:
    completed = subprocess.run(
        ["bn", *args],
        cwd=repo_root,
        check=False,
        text=True,
        capture_output=True,
    )
    if completed.returncode != 0:
        raise RuntimeError(
            f"bn {' '.join(args)} failed with exit code {completed.returncode}:\n{completed.stderr.strip()}"
        )

    stdout = completed.stdout.strip()
    stderr = completed.stderr.strip()
    spill_match = SPILL_PATH_RE.search(stdout) or SPILL_PATH_RE.search(stderr)
    if spill_match is not None:
        spill_path = Path(spill_match.group("path")).expanduser()
        return json.loads(spill_path.read_text(encoding="utf-8"))
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


def run_bn_batch(
    repo_root: Path,
    *,
    target: str,
    operations: list[dict[str, object]],
    preview: bool,
) -> dict[str, object]:
    manifest = {"target": target, "ops": operations}
    with tempfile.TemporaryDirectory(prefix="snail-bn-batch-") as temp_dir:
        manifest_path = Path(temp_dir) / "manifest.json"
        manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")
        args = ["batch", "apply"]
        if preview:
            args.append("--preview")
        args.extend((str(manifest_path), "--format", "json"))
        result = run_bn(repo_root, *args)
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
    for identifier, prototype in update_list:
        observed = current_prototype(repo_root, target=target, identifier=identifier)
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
) -> dict[str, object]:
    replacement_names = tuple(replace_types)
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
    existing = bv.get_type_by_name(parsed_type.name)
    before_width = existing.width if existing is not None else None
    parsed_width = parsed_type.type.width
    should_replace = str(parsed_type.name) in replacement_names
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


def struct_exists(repo_root: Path, *, target: str, struct_name: str) -> bool:
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
        return False
    if not isinstance(result, dict):
        return False
    layout = result.get("layout")
    if not isinstance(layout, str):
        return False
    # Binary Ninja reports a forward declaration as a zero-sized struct. It is
    # not sufficient for replay: treating it as present causes the authoritative
    # header import to be skipped forever, leaving every owner pointer opaque.
    size = parse_struct_layout_size(layout)
    return size is not None and size > 0


def types_declare_if_missing(
    repo_root: Path,
    *,
    target: str,
    header_path: Path,
    required_structs: Iterable[str],
) -> dict[str, object]:
    missing = [
        struct_name
        for struct_name in required_structs
        if not struct_exists(repo_root, target=target, struct_name=struct_name)
    ]
    if not missing:
        return {
            "op": "types_declare",
            "status": "skipped",
            "reason": "required structs already present",
            "header": str(header_path),
            "required_structs": tuple(required_structs),
        }
    result = types_declare_missing_only(
        repo_root,
        target=target,
        header_path=header_path,
    )
    result["missing_structs"] = tuple(missing)
    return result


def normalize_type_name(type_name: str) -> str:
    normalized = re.sub(r"\b(?:struct|enum)\s+", "", type_name)
    normalized = re.sub(r"\b([A-Za-z_][A-Za-z0-9_:]*)\s+const\s*\*", r"const \1*", normalized)
    return normalized.replace(" ", "")


def normalize_prototype(prototype: str, *, identifier: str) -> str:
    normalized = re.sub(r"\s+", " ", prototype).strip()
    # Binary Ninja preserves its independently proven purity qualifier when a
    # user prototype is applied. Treat that additive analysis fact as
    # orthogonal to the ABI/type comparison so repeatable syncs do not try to
    # overwrite an already-correct pure function.
    normalized = re.sub(r"\s+__pure\b", "", normalized)
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
    operations: list[dict[str, object]] = []
    for identifier, prototype in updates:
        existing = current_prototype(repo_root, target=target, identifier=identifier)
        existing_normalized = (
            normalize_prototype(existing, identifier=identifier) if existing is not None else None
        )
        requested_normalized = normalize_prototype(prototype, identifier=identifier)
        if existing_normalized == requested_normalized:
            operations.append(
                {
                    "op": "proto_set",
                    "status": "skipped",
                    "reason": "already current",
                    "identifier": identifier,
                    "prototype": prototype,
                }
            )
            continue

        operations.append(
            {
                "op": "proto_set",
                "identifier": identifier,
                "prototype": prototype,
                "result": run_previewed_bn_mutation(
                    repo_root,
                    "proto",
                    "set",
                    identifier,
                    prototype,
                    "--target",
                    target,
                ),
            }
        )
    return operations


def apply_struct_and_proto_updates(
    repo_root: Path,
    *,
    target: str,
    struct_updates: Iterable[StructUpdateGroup],
    proto_updates: Iterable[ProtoUpdate],
) -> list[dict[str, object]]:
    batch_ops: list[dict[str, object]] = []
    skipped: list[dict[str, object]] = []

    for struct_name, updates in struct_updates:
        fields = current_struct_fields(repo_root, target=target, struct_name=struct_name)
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

    for identifier, prototype in proto_updates:
        existing = current_prototype(repo_root, target=target, identifier=identifier)
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


def apply_symbol_updates(
    repo_root: Path,
    *,
    target: str,
    updates: Iterable[SymbolUpdate],
    kind: str = "auto",
) -> list[dict[str, object]]:
    operations: list[dict[str, object]] = []
    for identifier, name in updates:
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
    bv.define_user_data_var(address, parsed_type)
    after = bv.get_data_var_at(address)
    out.append({{
        "address": hex(address),
        "requested_type": type_text,
        "before_type": before_type,
        "after_type": str(after.type) if after is not None else None,
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
