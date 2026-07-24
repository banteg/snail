from __future__ import annotations

import json
import re

import ida_funcs
import ida_lines
import ida_pro
import idautils
import idc


def _resolve_function(selector: str):
    try:
        address = int(selector, 0)
    except ValueError:
        address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return None
    return ida_funcs.get_func(address)


def main() -> None:
    arguments = list(idc.ARGV[1:])
    if "--" in arguments:
        separator = arguments.index("--")
        selectors = arguments[:separator]
        pattern = arguments[separator + 1] if separator + 1 < len(arguments) else ""
    else:
        selectors = arguments
        pattern = ""
    if not selectors:
        print(json.dumps({"error": "missing function selector"}, indent=2))
        ida_pro.qexit(2)
        return

    matcher = re.compile(pattern, re.IGNORECASE) if pattern else None
    functions = []
    failed = []
    for selector in selectors:
        function = _resolve_function(selector)
        if function is None:
            failed.append({"selector": selector, "reason": "missing_function"})
            continue

        instructions = []
        for address in idautils.FuncItems(function.start_ea):
            disassembly = ida_lines.tag_remove(
                idc.generate_disasm_line(address, 0) or ""
            )
            operands = []
            for operand_index in range(8):
                operand_type = idc.get_operand_type(address, operand_index)
                if operand_type == 0:
                    continue
                operands.append(
                    {
                        "index": operand_index,
                        "text": ida_lines.tag_remove(
                            idc.print_operand(address, operand_index)
                        ),
                        "type": operand_type,
                        "value": idc.get_operand_value(address, operand_index),
                    }
                )
            searchable = " ".join(
                [disassembly, *(operand["text"] for operand in operands)]
            )
            if matcher is not None and matcher.search(searchable) is None:
                continue
            instructions.append(
                {
                    "address": hex(address),
                    "disassembly": disassembly,
                    "operands": operands,
                }
            )

        functions.append(
            {
                "selector": selector,
                "address": hex(function.start_ea),
                "instructions": instructions,
            }
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "pattern": pattern,
                "functions": functions,
                "failed": failed,
            },
            indent=2,
        )
    )
    ida_pro.qexit(1 if failed else 0)


if __name__ == "__main__":
    main()
