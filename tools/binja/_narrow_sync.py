from __future__ import annotations

import json
from pathlib import Path
import re
import subprocess
import sys
from typing import Iterable


SPILL_PATH_RE = re.compile(r"^path:\s+(?P<path>.+)$", re.MULTILINE)

FieldUpdate = tuple[str, str, str]
ProtoUpdate = tuple[str, str]


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


def apply_struct_field_updates(
    repo_root: Path,
    *,
    target: str,
    struct_name: str,
    updates: Iterable[FieldUpdate],
) -> list[dict[str, object]]:
    operations: list[dict[str, object]] = []
    for offset, name, field_type in updates:
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
