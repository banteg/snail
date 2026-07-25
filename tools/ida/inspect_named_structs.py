from __future__ import annotations

import json

import ida_pro
import ida_typeinf
import idc


def _inspect_named_struct(selector: str) -> dict[str, object] | None:
    owner = ida_typeinf.tinfo_t()
    if not owner.get_named_type(None, selector, ida_typeinf.BTF_STRUCT):
        return None

    members = ida_typeinf.udt_type_data_t()
    if not owner.get_udt_details(members):
        return None

    return {
        "selector": selector,
        "size": owner.get_size(),
        "members": [
            {
                "offset": hex(int(member.offset) // 8),
                "size": int(member.size) // 8,
                "name": member.name,
                "type": member.type.dstr(),
            }
            for member in members
        ],
    }


def main() -> None:
    selectors = list(idc.ARGV[1:])
    if not selectors:
        print(json.dumps({"error": "missing struct selector"}, indent=2))
        ida_pro.qexit(2)
        return

    structs = []
    failed = []
    for selector in selectors:
        result = _inspect_named_struct(selector)
        if result is None:
            failed.append({"selector": selector, "reason": "missing_struct"})
            continue
        structs.append(result)

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "structs": structs,
                "failed": failed,
            },
            indent=2,
        )
    )
    ida_pro.qexit(1 if failed else 0)


if __name__ == "__main__":
    main()
