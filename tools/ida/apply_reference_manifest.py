import json
import pathlib
import sys

import ida_bytes
import ida_kernwin
import ida_name
import ida_pro
import idc


def _parse_address(value):
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        return int(value, 0)
    raise TypeError(f"unsupported address value: {value!r}")


def _load_manifest(path):
    raw = json.loads(path.read_text(encoding="utf-8"))
    symbols = raw.get("symbols")
    if not isinstance(symbols, list):
        raise ValueError("reference manifest field 'symbols' must be a list")
    entries = []
    for index, symbol in enumerate(symbols):
        if not isinstance(symbol, dict):
            raise ValueError(f"symbol entry {index} must be an object")
        entries.append(
            (
                _parse_address(symbol["address"]),
                symbol["name"],
                symbol.get("description"),
            )
        )
    return entries


def _sync_manifest(manifest_path):
    renamed = 0
    comments_updated = 0
    unchanged = 0
    skipped = []

    for address, name, description in _load_manifest(manifest_path):
        current_name = idc.get_name(address)
        if current_name != name:
            if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                skipped.append((address, name, "rename_failed"))
                continue
            renamed += 1
        else:
            unchanged += 1

        if description:
            current_comment = ida_bytes.get_cmt(address, True) or ""
            if current_comment != description:
                if not ida_bytes.set_cmt(address, description, True):
                    skipped.append((address, name, "comment_failed"))
                    continue
                comments_updated += 1

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "manifest": str(manifest_path),
                "renamed": renamed,
                "comments_updated": comments_updated,
                "unchanged": unchanged,
                "skipped": [
                    {"address": hex(address), "name": name, "reason": reason}
                    for address, name, reason in skipped
                ],
            },
            indent=2,
        )
    )

    return 0


def main():
    argv = list(idc.ARGV)
    if len(argv) < 2:
        print("usage: apply_reference_manifest.py <manifest-path>", file=sys.stderr)
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
