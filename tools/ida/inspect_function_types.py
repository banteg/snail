from __future__ import annotations

import json

import ida_funcs
import ida_pro
import idc


def _resolve_function(selector: str) -> int | None:
    try:
        address = int(selector, 0)
    except ValueError:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR:
            return None

    function = ida_funcs.get_func(address)
    if function is None:
        return None
    return function.start_ea


def main() -> None:
    selectors = list(idc.ARGV[1:])
    if not selectors:
        print(json.dumps({"error": "missing function selector"}, indent=2))
        ida_pro.qexit(2)
        return

    functions = []
    failed = []
    for selector in selectors:
        address = _resolve_function(selector)
        if address is None:
            failed.append({"selector": selector, "reason": "missing_function"})
            continue

        functions.append(
            {
                "selector": selector,
                "address": hex(address),
                "name": idc.get_func_name(address),
                "type": idc.get_type(address),
            }
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "functions": functions,
                "failed": failed,
            },
            indent=2,
        )
    )
    ida_pro.qexit(1 if failed else 0)


if __name__ == "__main__":
    main()
