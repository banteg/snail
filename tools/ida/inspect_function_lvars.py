from __future__ import annotations

import json

import ida_hexrays
import ida_pro
import idc


def main() -> None:
    selectors = list(idc.ARGV[1:])
    if not selectors:
        print(json.dumps({"error": "missing function selector"}, indent=2))
        ida_pro.qexit(2)
        return

    functions = []
    failed = []
    for selector in selectors:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR:
            failed.append({"selector": selector, "reason": "missing_function"})
            continue

        try:
            cfunc = ida_hexrays.decompile(address)
        except Exception as exc:
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "reason": "decompile_failed",
                    "error": str(exc),
                }
            )
            continue

        lvars = []
        for lvar in cfunc.get_lvars():
            entry = {
                "name": lvar.name,
                "type": str(lvar.type()),
                "width": lvar.width,
                "is_argument": bool(lvar.is_arg_var),
                "is_stack": bool(lvar.is_stk_var()),
                "definition_address": hex(lvar.defea),
                "location": str(lvar.location),
            }
            if lvar.is_stk_var():
                entry["stack_offset"] = lvar.get_stkoff()
            lvars.append(entry)

        functions.append(
            {
                "selector": selector,
                "address": hex(address),
                "lvars": lvars,
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
