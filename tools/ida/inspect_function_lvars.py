from __future__ import annotations

import json

import ida_hexrays
import ida_pro
import idautils
import idc


def _saved_lvar_location(info: ida_hexrays.lvar_saved_info_t) -> dict[str, object]:
    locator = info.ll
    if locator.is_stk_var():
        return {"kind": "stack", "stack_offset": locator.get_stkoff()}
    if locator.is_reg1():
        width = info.size if info.size > 0 else 4
        register = locator.get_reg1()
        return {
            "kind": "register",
            "mreg": register,
            "register": ida_hexrays.get_mreg_name(register, width),
        }
    if locator.is_reg2():
        return {
            "kind": "register_pair",
            "mregs": [locator.get_reg1(), locator.get_reg2()],
        }
    if locator.is_scattered():
        return {"kind": "scattered"}
    return {"kind": "unknown", "location": str(locator.location)}


def _saved_lvar_overrides(address: int) -> list[dict[str, object]]:
    settings = ida_hexrays.lvar_uservec_t()
    if not ida_hexrays.restore_user_lvar_settings(settings, address):
        return []

    overrides = []
    for index in range(settings.lvvec.size()):
        info = settings.lvvec.at(index)
        overrides.append(
            {
                "name": info.name,
                "type": str(info.type),
                "size": info.size,
                "flags": info.flags,
                "definition_address": hex(info.ll.defea),
                "location": _saved_lvar_location(info),
            }
        )
    return overrides


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
                "saved_lvar_overrides": _saved_lvar_overrides(address),
                "stack_pointer_changes": [
                    {
                        "address": hex(item_address),
                        "delta": idc.get_sp_delta(item_address),
                        "cumulative_delta": idc.get_spd(item_address),
                    }
                    for item_address in idautils.FuncItems(address)
                    if idc.get_sp_delta(item_address)
                ],
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
