from __future__ import annotations

import json

import ida_hexrays
import ida_idaapi
import ida_pro
import idc


def _format_address(address: int) -> str | None:
    if address == ida_idaapi.BADADDR:
        return None
    return hex(address)


class LvarUseVisitor(ida_hexrays.ctree_visitor_t):
    def __init__(
        self,
        cfunc: ida_hexrays.cfunc_t,
        selected_names: set[str],
    ) -> None:
        super().__init__(ida_hexrays.CV_FAST | ida_hexrays.CV_PARENTS)
        self._lvars = cfunc.get_lvars()
        self._selected_names = selected_names
        self.uses: list[dict[str, object]] = []

    def visit_expr(self, expression: ida_hexrays.cexpr_t) -> int:
        if expression.op != ida_hexrays.cot_var:
            return 0

        index = expression.v.idx
        lvar = self._lvars[index]
        if self._selected_names and lvar.name not in self._selected_names:
            return 0
        parent = self.parent_item()
        parent_expression = None
        parent_operation = None
        if parent is not None:
            if parent.is_expr():
                parent_expression = parent.cexpr.dstr()
                parent_operation = parent.cexpr.opname
            else:
                parent_operation = parent.cinsn.opname
        self.uses.append(
            {
                "index": index,
                "name": lvar.name,
                "type": str(lvar.type()),
                "definition_address": _format_address(lvar.defea),
                "use_address": _format_address(expression.ea),
                "expression": expression.dstr(),
                "parent_operation": parent_operation,
                "parent_address": (
                    None if parent is None else _format_address(parent.ea)
                ),
                "parent_expression": parent_expression,
            }
        )
        return 0


def main() -> None:
    arguments = list(idc.ARGV[1:])
    if "--" in arguments:
        separator = arguments.index("--")
        selectors = arguments[:separator]
        selected_names = set(arguments[separator + 1 :])
    else:
        selectors = arguments
        selected_names = set()
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

        visitor = LvarUseVisitor(cfunc, selected_names)
        visitor.apply_to(cfunc.body, None)
        functions.append(
            {
                "selector": selector,
                "address": hex(address),
                "selected_names": sorted(selected_names),
                "uses": visitor.uses,
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
