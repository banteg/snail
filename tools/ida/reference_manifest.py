from __future__ import annotations

import json
from pathlib import Path
from typing import Any


NON_ADDRESS_REFERENCE_KINDS = frozenset({"constant", "offset"})


def _parse_address(value: object) -> int:
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        return int(value, 0)
    raise TypeError(f"unsupported address value: {value!r}")


def load_address_backed_symbols(
    path: Path,
) -> tuple[list[tuple[int, str, str | None]], list[dict[str, Any]]]:
    raw = json.loads(path.read_text(encoding="utf-8"))
    symbols = raw.get("symbols")
    if not isinstance(symbols, list):
        raise ValueError("reference manifest field 'symbols' must be a list")

    entries: list[tuple[int, str, str | None]] = []
    skipped_non_address: list[dict[str, Any]] = []
    for index, symbol in enumerate(symbols):
        if not isinstance(symbol, dict):
            raise ValueError(f"symbol entry {index} must be an object")

        address = _parse_address(symbol.get("address"))
        name = symbol.get("name")
        if not isinstance(name, str) or not name:
            raise ValueError(f"symbol entry {index} has invalid name")
        kind = symbol.get("kind")
        if not isinstance(kind, str) or not kind:
            raise ValueError(f"symbol entry {index} has invalid kind")
        description = symbol.get("description")
        if description is not None and not isinstance(description, str):
            raise ValueError(f"symbol entry {index} has invalid description")

        if kind in NON_ADDRESS_REFERENCE_KINDS:
            skipped_non_address.append(
                {
                    "address": address,
                    "name": name,
                    "kind": kind,
                }
            )
            continue
        entries.append((address, name, description))

    return entries, skipped_non_address
