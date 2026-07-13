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
SELECTOR_DISPLAY_SEPARATOR = "@@"


def _safe_name(name):
    return SAFE_NAME_RE.sub("_", name).strip("_") or "function"


def _prune_same_address_artifacts(out_dir, start, keep_path):
    removed = []
    prefix = f"{start:08x}-"
    for path in sorted(out_dir.glob(f"{prefix}*.c")):
        if path == keep_path:
            continue
        path.unlink()
        removed.append(str(path))
    return removed


def _resolve_selector(selector):
    resolved_from_address = False
    try:
        address = int(selector, 0)
        resolved_from_address = True
    except ValueError:
        address = ida_name.get_name_ea(idc.BADADDR, selector)
        if address == idc.BADADDR:
            raise ValueError(f"could not resolve selector: {selector}") from None

    func = ida_funcs.get_func(address)
    if func is None:
        raise ValueError(f"no function found for selector: {selector}")
    if resolved_from_address and func.start_ea != address:
        raise ValueError(
            f"selector {selector} resolved inside {idc.get_func_name(func.start_ea)} "
            f"at {hex(func.start_ea)}; run the IDA symbol sync to repair function chunks"
        )
    return func.start_ea


def _split_selector(selector):
    if SELECTOR_DISPLAY_SEPARATOR not in selector:
        return selector, selector
    resolve_selector, display_selector = selector.split(SELECTOR_DISPLAY_SEPARATOR, 1)
    if not resolve_selector or not display_selector:
        raise ValueError(f"invalid selector/display pair: {selector}")
    return resolve_selector, display_selector


def _export_function(out_dir, selector):
    resolve_selector, display_selector = _split_selector(selector)
    start = _resolve_selector(resolve_selector)
    name = idc.get_func_name(start)
    try:
        ida_hexrays.mark_cfunc_dirty(start, True)
        failure = ida_hexrays.hexrays_failure_t()
        cfunc = ida_hexrays.decompile_func(ida_funcs.get_func(start), failure)
        if cfunc is None:
            raise RuntimeError(
                f"Hex-Rays returned no cfunc: {failure.desc()} at {hex(failure.errea)}"
            )
        pseudocode = str(cfunc)
    except Exception as exc:  # pragma: no cover - IDA runtime dependent
        raise RuntimeError(f"failed to decompile {selector}: {exc}") from exc

    out_path = out_dir / f"{start:08x}-{_safe_name(name)}.c"
    removed_stale_artifacts = _prune_same_address_artifacts(out_dir, start, out_path)
    out_path.write_text(
        (
            f"/* database: {idc.get_idb_path()} */\n"
            f"/* function: {name} @ {hex(start)} */\n"
            f"/* selector: {display_selector} */\n\n"
            f"{pseudocode}\n"
        ),
        encoding="utf-8",
    )
    return {
        "selector": display_selector,
        "address": hex(start),
        "name": name,
        "artifact": str(out_path),
        "removed_stale_artifacts": removed_stale_artifacts,
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
