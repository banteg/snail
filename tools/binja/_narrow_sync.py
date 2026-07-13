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


def types_declare(repo_root: Path, *, target: str, header_path: Path) -> dict[str, object]:
    return {
        "op": "types_declare",
        "result": run_bn(repo_root, "types", "declare", "--target", target, "--file", str(header_path)),
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
    return {
        "op": "types_declare",
        "missing_structs": tuple(missing),
        "result": run_bn(repo_root, "types", "declare", "--target", target, "--file", str(header_path)),
    }


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
                "result": run_bn(
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
                "result": run_bn(
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
                "result": run_bn(repo_root, *command),
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
