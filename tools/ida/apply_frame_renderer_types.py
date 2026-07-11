from __future__ import annotations

import json
import pathlib
import re
import sys

import ida_funcs
import ida_kernwin
import ida_name
import ida_pro
import idc


TRUSTED_NAMES = [
    (0x408000, "initialize_game_player"),
    (0x4107D0, "update_frontend_state_machine"),
    (0x44C3B0, "is_mouse_captured"),
    (0x44C3C0, "capture_mouse_cursor"),
    (0x44C400, "release_mouse_cursor"),
    (0x4E5510, "g_sprite_depth_nodes"),
    (0x4F7050, "g_sprite_depth_buckets"),
]

TRUSTED_FUNCTION_DECLARATIONS = [
    (
        "initialize_game_player",
        "GamePlayer *__thiscall initialize_game_player(GamePlayer *player);",
    ),
    (
        "update_frontend_state_machine",
        "int __thiscall update_frontend_state_machine(GamePlayer *player);",
    ),
    (
        "is_mouse_captured",
        "uint8_t __thiscall is_mouse_captured(MouseCursorState *mouse);",
    ),
    (
        "capture_mouse_cursor",
        "void __thiscall capture_mouse_cursor(MouseCursorState *mouse);",
    ),
    (
        "release_mouse_cursor",
        "void __thiscall release_mouse_cursor(MouseCursorState *mouse);",
    ),
    (
        "run_frame_update",
        "int __thiscall run_frame_update(GameRoot *game);",
    ),
    (
        "render_game_frame",
        "void __thiscall render_game_frame(GameRoot *game);",
    ),
]

TRUSTED_DATA_DECLARATIONS = [
    (
        0x4E5510,
        "g_sprite_depth_nodes",
        "SpriteDepthNode g_sprite_depth_nodes[3000];",
    ),
    (
        0x4F7050,
        "g_sprite_depth_buckets",
        "SpriteDepthNode *g_sprite_depth_buckets[256];",
    ),
]


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]", "]", normalized)
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\b", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)
    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    missing = []
    failed = []

    for address, name in TRUSTED_NAMES:
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append({"address": hex(address), "selector": name, "reason": "rename_failed"})
            continue
        renamed += 1

    for selector, declaration in TRUSTED_FUNCTION_DECLARATIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "reason": "missing_function"})
            continue

        expected = _declaration_to_observed_type(selector, declaration)
        if _normalize_type_text(idc.get_type(address)) == expected:
            unchanged += 1
            continue
        if not idc.SetType(address, declaration):
            failed.append({"selector": selector, "reason": "set_type_failed"})
            continue
        observed = idc.get_type(address)
        if _normalize_type_text(observed) != expected:
            failed.append(
                {
                    "selector": selector,
                    "reason": "verification_failed",
                    "observed": observed,
                    "expected": expected,
                }
            )
            continue
        applied += 1

    for address, selector, declaration in TRUSTED_DATA_DECLARATIONS:
        expected = _declaration_to_observed_type(selector, declaration)
        if _normalize_type_text(idc.get_type(address)) == expected:
            unchanged += 1
            continue
        if not idc.SetType(address, declaration):
            failed.append({"selector": selector, "reason": "set_data_type_failed"})
            continue
        observed = idc.get_type(address)
        if _normalize_type_text(observed) != expected:
            failed.append(
                {
                    "selector": selector,
                    "reason": "data_verification_failed",
                    "observed": observed,
                    "expected": expected,
                }
            )
            continue
        applied += 1

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )
    return 1 if parse_errors or missing or failed else 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) != 2:
        print("usage: apply_frame_renderer_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    exit_code = _sync_types(header_path)
    try:
        idc.save_database(idc.get_idb_path(), 0)
    except Exception as exc:  # pragma: no cover - IDA runtime dependent
        ida_kernwin.msg(f"warning: failed to save database explicitly: {exc}\n")
    ida_pro.qexit(exit_code)


if __name__ == "__main__":
    main()
