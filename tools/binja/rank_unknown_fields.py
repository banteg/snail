#!/usr/bin/env python3
"""Rank unresolved Binary Ninja structure fields by cross-function use.

This is intentionally read-only.  It helps choose ownership-recovery targets
whose placeholder fields are referenced by multiple functions, instead of
guessing names from constructor constants.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path
import subprocess
import sys
import tempfile
from typing import Any

from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_NAME_PATTERN = r"(?i)(?:^|_)(?:unknown|unk|field)(?:_|$)"

QUERY_TEMPLATE = r"""
import json
import re

name_pattern = re.compile(__NAME_PATTERN__)
minimum_function_count = __MINIMUM_FUNCTION_COUNT__
minimum_reference_count = __MINIMUM_REFERENCE_COUNT__
rows = []


def walk_il(node):
    if not hasattr(node, "operation"):
        return
    yield node
    for operand in getattr(node, "operands", ()):
        if hasattr(operand, "operation"):
            yield from walk_il(operand)
        elif isinstance(operand, (list, tuple)):
            for item in operand:
                if hasattr(item, "operation"):
                    yield from walk_il(item)


def classify_access(function, address):
    try:
        instruction = function.get_llil_at(address)
    except Exception:
        return "address"
    if instruction is None:
        return "address"
    operation_names = {
        getattr(node.operation, "name", str(node.operation))
        for node in walk_il(instruction)
    }
    stores = any(name.startswith("LLIL_STORE") for name in operation_names)
    loads = any(name.startswith("LLIL_LOAD") for name in operation_names)
    if stores and loads:
        return "read_write"
    if stores:
        return "write"
    if loads:
        return "read"
    return "address"


for type_name, type_obj in bv.types.items():
    members = list(getattr(type_obj, "members", ()))
    if not members:
        continue

    for member in members:
        member_name = str(getattr(member, "name", ""))
        if not name_pattern.search(member_name):
            continue

        offset = int(getattr(member, "offset", -1))
        if offset < 0:
            continue

        try:
            references = list(bv.get_code_refs_for_type_field(type_name, offset))
        except Exception:
            continue

        functions = {}
        function_accesses = {}
        reference_rows = []
        seen_references = set()
        for reference in references:
            function = getattr(reference, "func", None)
            if function is None:
                continue
            function_start = int(function.start)
            function_name = str(function.name)
            reference_address = int(reference.address)
            reference_key = (function_start, reference_address)
            if reference_key in seen_references:
                continue
            seen_references.add(reference_key)

            access = classify_access(function, reference_address)
            functions[function_start] = function_name
            function_accesses.setdefault(function_start, set()).add(access)
            reference_rows.append(
                {
                    "address": reference_address,
                    "function_address": function_start,
                    "function_name": function_name,
                    "size": int(reference.size),
                    "access": access,
                }
            )

        if len(functions) < minimum_function_count:
            continue
        if len(reference_rows) < minimum_reference_count:
            continue

        read_functions = {
            address
            for address, accesses in function_accesses.items()
            if accesses & {"read", "read_write"}
        }
        write_functions = {
            address
            for address, accesses in function_accesses.items()
            if accesses & {"write", "read_write"}
        }
        rows.append(
            {
                "type_name": str(type_name),
                "type_width": int(getattr(type_obj, "width", 0)),
                "field_name": member_name,
                "field_offset": offset,
                "field_type": str(getattr(member, "type", "")),
                "function_count": len(functions),
                "reference_count": len(reference_rows),
                "read_function_count": len(read_functions),
                "write_function_count": len(write_functions),
                "functions": [
                    {
                        "address": address,
                        "name": functions[address],
                        "accesses": sorted(function_accesses[address]),
                    }
                    for address in sorted(functions)
                ],
                "references": sorted(
                    reference_rows,
                    key=lambda row: (
                        row["function_address"],
                        row["address"],
                    ),
                ),
            }
        )

rows.sort(
    key=lambda row: (
        -(row["read_function_count"] > 0 and row["write_function_count"] > 0),
        -row["read_function_count"],
        -row["function_count"],
        -row["reference_count"],
        row["type_name"],
        row["field_offset"],
    )
)
print(json.dumps(rows, separators=(",", ":")))
"""


def _parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help=f"Binary Ninja target selector (default: {DEFAULT_TARGET})",
    )
    parser.add_argument(
        "--name-pattern",
        default=DEFAULT_NAME_PATTERN,
        help="regular expression selecting unresolved field names",
    )
    parser.add_argument(
        "--min-functions",
        type=int,
        default=2,
        help="minimum number of distinct functions referencing a field",
    )
    parser.add_argument(
        "--min-references",
        type=int,
        default=2,
        help="minimum number of code references to a field",
    )
    parser.add_argument(
        "--limit",
        type=int,
        default=40,
        help="maximum number of ranked fields to print; 0 prints every field",
    )
    parser.add_argument(
        "--format",
        choices=("table", "json"),
        default="table",
        help="output format",
    )
    return parser


def _query_code(
    *,
    name_pattern: str,
    minimum_function_count: int,
    minimum_reference_count: int,
) -> str:
    return (
        QUERY_TEMPLATE.replace("__NAME_PATTERN__", repr(name_pattern))
        .replace("__MINIMUM_FUNCTION_COUNT__", str(minimum_function_count))
        .replace("__MINIMUM_REFERENCE_COUNT__", str(minimum_reference_count))
    )


def _run_query(
    *,
    target: str,
    name_pattern: str,
    minimum_function_count: int,
    minimum_reference_count: int,
) -> list[dict[str, Any]]:
    code = _query_code(
        name_pattern=name_pattern,
        minimum_function_count=minimum_function_count,
        minimum_reference_count=minimum_reference_count,
    )
    with tempfile.NamedTemporaryFile(suffix=".json", delete=False) as handle:
        output_path = Path(handle.name)
    try:
        completed = subprocess.run(
            [
                "bn",
                "py",
                "exec",
                "--target",
                target,
                "--format",
                "json",
                "--out",
                str(output_path),
                "--code",
                code,
            ],
            cwd=REPO_ROOT,
            check=False,
            text=True,
            capture_output=True,
        )
        if completed.returncode != 0:
            detail = completed.stderr.strip() or completed.stdout.strip()
            raise RuntimeError(
                f"Binary Ninja field query failed with exit code "
                f"{completed.returncode}:\n{detail}"
            )

        envelope = json.loads(output_path.read_text(encoding="utf-8"))
        stdout = envelope.get("stdout")
        if not isinstance(stdout, str):
            raise RuntimeError(f"unexpected Binary Ninja response: {envelope!r}")
        rows = json.loads(stdout)
        if not isinstance(rows, list):
            raise RuntimeError("Binary Ninja field query did not return a list")
        return rows
    finally:
        output_path.unlink(missing_ok=True)


def _format_address(value: object) -> str:
    return f"{int(value):#010x}"


def _print_table(rows: list[dict[str, Any]]) -> None:
    for rank, row in enumerate(rows, start=1):
        functions = ", ".join(
            f"{function['name']}@{_format_address(function['address'])}"
            f":{'/'.join(function['accesses'])}"
            for function in row["functions"]
        )
        print(
            f"{rank:>3}  {row['function_count']:>2} fn  "
            f"{row['reference_count']:>3} refs  "
            f"R{row['read_function_count']}/W{row['write_function_count']}  "
            f"{row['type_name']}.{row['field_name']}"
            f"+{_format_address(row['field_offset'])}  "
            f"{row['field_type']}  [{functions}]"
        )


def main() -> int:
    args = _parser().parse_args()
    if args.min_functions < 1:
        raise SystemExit("--min-functions must be at least 1")
    if args.min_references < 1:
        raise SystemExit("--min-references must be at least 1")
    if args.limit < 0:
        raise SystemExit("--limit cannot be negative")

    rows = _run_query(
        target=args.target,
        name_pattern=args.name_pattern,
        minimum_function_count=args.min_functions,
        minimum_reference_count=args.min_references,
    )
    selected_rows = rows if args.limit == 0 else rows[: args.limit]
    if args.format == "json":
        json.dump(selected_rows, sys.stdout, indent=2)
        sys.stdout.write("\n")
    else:
        _print_table(selected_rows)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
