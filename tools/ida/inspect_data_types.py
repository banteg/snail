from __future__ import annotations

import json

import ida_bytes
import ida_pro
import idc


def _resolve_address(selector: str) -> int | None:
    try:
        return int(selector, 0)
    except ValueError:
        address = idc.get_name_ea_simple(selector)
        return None if address == idc.BADADDR else address


def main() -> None:
    selectors = list(idc.ARGV[1:])
    if not selectors:
        print(json.dumps({"error": "missing data selector"}, indent=2))
        ida_pro.qexit(2)
        return

    data = []
    failed = []
    for selector in selectors:
        address = _resolve_address(selector)
        if address is None:
            failed.append({"selector": selector, "reason": "missing_address"})
            continue

        item_head = ida_bytes.get_item_head(address)
        data.append(
            {
                "selector": selector,
                "address": hex(address),
                "name": idc.get_name(address),
                "type": idc.get_type(address),
                "item_head": hex(item_head),
                "item_head_name": idc.get_name(item_head),
                "item_head_type": idc.get_type(item_head),
                "item_size": ida_bytes.get_item_size(item_head),
            }
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "data": data,
                "failed": failed,
            },
            indent=2,
        )
    )
    ida_pro.qexit(1 if failed else 0)


if __name__ == "__main__":
    main()
