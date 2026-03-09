import json
import pathlib
import re
import sys

import ida_funcs
import ida_hexrays
import ida_name
import ida_pro
import idc


SAFE_NAME_RE = re.compile(r"[^A-Za-z0-9_.-]+")


def _safe_name(name):
    return SAFE_NAME_RE.sub("_", name).strip("_") or "function"


def _resolve_selector(selector):
    try:
        address = int(selector, 0)
    except ValueError:
        address = ida_name.get_name_ea(idc.BADADDR, selector)
        if address == idc.BADADDR:
            raise ValueError(f"could not resolve selector: {selector}") from None

    func = ida_funcs.get_func(address)
    if func is None:
        raise ValueError(f"no function found for selector: {selector}")
    return func.start_ea


def _export_function(out_dir, selector):
    start = _resolve_selector(selector)
    name = idc.get_func_name(start)
    try:
        pseudocode = str(ida_hexrays.decompile(start))
    except Exception as exc:  # pragma: no cover - IDA runtime dependent
        raise RuntimeError(f"failed to decompile {selector}: {exc}") from exc

    out_path = out_dir / f"{start:08x}-{_safe_name(name)}.c"
    out_path.write_text(
        (
            f"/* database: {idc.get_idb_path()} */\n"
            f"/* function: {name} @ {hex(start)} */\n"
            f"/* selector: {selector} */\n\n"
            f"{pseudocode}\n"
        ),
        encoding="utf-8",
    )
    return {
        "selector": selector,
        "address": hex(start),
        "name": name,
        "artifact": str(out_path),
    }


def main():
    argv = list(idc.ARGV)
    if len(argv) < 3:
        print(
            "usage: export_function_artifact.py <out-dir> <selector> [<selector> ...]",
            file=sys.stderr,
        )
        ida_pro.qexit(2)
        return

    out_dir = pathlib.Path(argv[1]).resolve()
    out_dir.mkdir(parents=True, exist_ok=True)

    exported = []
    failed = []
    for selector in argv[2:]:
        try:
            exported.append(_export_function(out_dir, selector))
        except Exception as exc:
            failed.append({"selector": selector, "reason": str(exc)})

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "out_dir": str(out_dir),
                "exported": exported,
                "failed": failed,
            },
            indent=2,
        )
    )
    ida_pro.qexit(1 if failed else 0)


if __name__ == "__main__":
    main()
