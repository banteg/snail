import json
import pathlib
import sys

import ida_funcs
import ida_kernwin
import ida_name
import ida_pro
import ida_bytes
import idc


def _parse_address(value):
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        return int(value, 0)
    raise TypeError(f"unsupported address value: {value!r}")


def _load_manifest(path):
    raw = json.loads(path.read_text(encoding="utf-8"))
    functions = raw.get("functions")
    if not isinstance(functions, list):
        raise ValueError("manifest field 'functions' must be a list")
    entries = []
    for index, function in enumerate(functions):
        if not isinstance(function, dict):
            raise ValueError(f"function entry {index} must be an object")
        entries.append(
            (
                _parse_address(function["address"]),
                function["name"],
                function.get("description"),
            )
        )
    return entries


def _sync_manifest(manifest_path):
    renamed = 0
    comments_updated = 0
    unchanged = 0
    functions_created = 0
    missing = []
    failed = []

    for address, name, description in _load_manifest(manifest_path):
        func = ida_funcs.get_func(address)
        if func is None:
            flags = ida_bytes.get_flags(address)
            if ida_bytes.is_code(flags) and ida_funcs.add_func(address):
                func = ida_funcs.get_func(address)
                functions_created += 1
            if func is None:
                missing.append((address, name))
                continue

        current_name = idc.get_func_name(address)
        if current_name != name:
            if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                failed.append((address, name, "rename_failed"))
                continue
            renamed += 1
        else:
            unchanged += 1

        if description:
            current_comment = ida_funcs.get_func_cmt(func, True) or ""
            if current_comment != description:
                if not ida_funcs.set_func_cmt(func, description, True):
                    failed.append((address, name, "comment_failed"))
                    continue
                comments_updated += 1

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "manifest": str(manifest_path),
                "renamed": renamed,
                "comments_updated": comments_updated,
                "functions_created": functions_created,
                "unchanged": unchanged,
                "missing": [
                    {"address": hex(address), "name": name} for address, name in missing
                ],
                "failed": [
                    {"address": hex(address), "name": name, "reason": reason}
                    for address, name, reason in failed
                ],
            },
            indent=2,
        )
    )

    if failed or missing:
        return 1
    return 0


def main():
    argv = list(idc.ARGV)
    if len(argv) < 2:
        print("usage: apply_symbol_manifest.py <manifest-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    manifest_path = pathlib.Path(argv[1]).resolve()
    exit_code = _sync_manifest(manifest_path)
    try:
        idc.save_database(idc.get_idb_path(), 0)
    except Exception as exc:  # pragma: no cover - IDA runtime dependent
        ida_kernwin.msg(f"warning: failed to save database explicitly: {exc}\n")
    ida_pro.qexit(exit_code)


if __name__ == "__main__":
    main()
