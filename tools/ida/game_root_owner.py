from __future__ import annotations

import re

import ida_typeinf
import idc


GAME_ROOT_SIZE = 0x12E6FF4
GAME_ROOT_SUBGAME_OFFSET = 0x74618
GAME_ROOT_GLOBAL_ADDRESS = 0x4DF904

_REQUIRED_TYPE_SIZES = {
    "SubgameRuntime": 0x1272838,
    "HighScore": 0xF4,
    "TipManager": 0x98,
}

_CANONICAL_TAIL = (
    (0x74618, 0x1272838, "subgame", "SubgameRuntime"),
    (0x12E6E50, 0xF4, "high_score", "HighScore"),
    (0x12E6F44, 0x14, "_pad_12e6f44", "uint8_t[20]"),
    (0x12E6F58, 0x98, "tip_manager", "TipManager"),
    (0x12E6FF0, 0x4, "_pad_12e6ff0", "uint8_t[4]"),
)


def _normalize_type(value: str) -> str:
    normalized = re.sub(r"\b(?:struct|class|union)\s+", "", value)
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]", "]", normalized)
    return normalized.strip()


def _named_type(name: str) -> ida_typeinf.tinfo_t | None:
    tif = ida_typeinf.tinfo_t()
    return tif if tif.get_named_type(None, name) else None


def _tail_snapshot(root: ida_typeinf.tinfo_t) -> list[dict[str, object]] | None:
    udt = ida_typeinf.udt_type_data_t()
    if not root.get_udt_details(udt):
        return None
    return [
        {
            "index": index,
            "offset": int(member.offset) // 8,
            "size": int(member.size) // 8,
            "name": member.name,
            "type": _normalize_type(member.type.dstr()),
        }
        for index, member in enumerate(udt)
        if int(member.offset) // 8 >= GAME_ROOT_SUBGAME_OFFSET
    ]


def _readback(root: ida_typeinf.tinfo_t) -> dict[str, object]:
    snapshot = _tail_snapshot(root)
    return {
        "size": root.get_size(),
        "members": []
        if snapshot is None
        else [
            {
                "offset": hex(int(member["offset"])),
                "size": hex(int(member["size"])),
                "name": member["name"],
                "type": member["type"],
            }
            for member in snapshot
        ],
    }


def _is_canonical(root: ida_typeinf.tinfo_t) -> bool:
    snapshot = _tail_snapshot(root)
    if root.get_size() != GAME_ROOT_SIZE or snapshot is None:
        return False
    observed = tuple(
        (
            int(member["offset"]),
            int(member["size"]),
            str(member["name"]),
            str(member["type"]),
        )
        for member in snapshot
    )
    return observed == _CANONICAL_TAIL


def _error_text(code: int) -> str:
    return ida_typeinf.tinfo_errstr(code)


def _rebind_game_root_global() -> dict[str, object]:
    """Refresh the pointer snapshot after replacing members on GameRoot."""

    declaration = "GameRoot *g_game_base;"
    if not idc.SetType(GAME_ROOT_GLOBAL_ADDRESS, declaration):
        return {
            "status": "failed",
            "reason": "set_game_root_global_type_failed",
            "address": hex(GAME_ROOT_GLOBAL_ADDRESS),
        }
    observed = idc.get_type(GAME_ROOT_GLOBAL_ADDRESS)
    if _normalize_type(observed or "") != "GameRoot *":
        return {
            "status": "failed",
            "reason": "game_root_global_type_verification_failed",
            "address": hex(GAME_ROOT_GLOBAL_ADDRESS),
            "observed": observed,
        }
    return {
        "status": "rebound",
        "address": hex(GAME_ROOT_GLOBAL_ADDRESS),
        "type": observed,
    }


def sync_game_root_owner_graph(*, require: bool) -> dict[str, object]:
    """Compose recovered root owners without replacing the proved prefix."""

    required_names = ("GameRoot", *_REQUIRED_TYPE_SIZES)
    types = {name: _named_type(name) for name in required_names}
    missing = [name for name, tif in types.items() if tif is None]
    if missing:
        return {
            "status": "failed" if require else "deferred",
            "reason": "missing_named_types",
            "missing": missing,
        }

    root = types["GameRoot"]
    assert root is not None
    if _is_canonical(root):
        root_global = _rebind_game_root_global()
        if root_global["status"] == "failed":
            return root_global
        return {
            "status": "unchanged",
            "readback": _readback(root),
            "root_global": root_global,
        }

    if root.get_size() != GAME_ROOT_SIZE:
        return {
            "status": "failed",
            "reason": "unexpected_game_root_size",
            "observed": root.get_size(),
            "expected": GAME_ROOT_SIZE,
        }

    size_mismatches = {}
    for name, expected_size in _REQUIRED_TYPE_SIZES.items():
        tif = types[name]
        assert tif is not None
        if tif.get_size() != expected_size:
            size_mismatches[name] = {
                "observed": tif.get_size(),
                "expected": expected_size,
            }
    if size_mismatches:
        return {
            "status": "failed",
            "reason": "owner_size_mismatch",
            "types": size_mismatches,
        }

    snapshot = _tail_snapshot(root)
    if snapshot is None or not any(
        member["offset"] == GAME_ROOT_SUBGAME_OFFSET and member["name"] == "subgame"
        for member in snapshot
    ):
        return {
            "status": "failed",
            "reason": "missing_subgame_member",
            "readback": _readback(root),
        }

    try:
        for member in reversed(snapshot):
            code = root.del_udm(int(member["index"]))
            if code != ida_typeinf.TERR_OK:
                raise RuntimeError(f"delete {member['name']}: {_error_text(code)}")

        member_types: tuple[tuple[str, object, int], ...] = (
            ("subgame", types["SubgameRuntime"], 0x74618),
            ("high_score", types["HighScore"], 0x12E6E50),
            ("_pad_12e6f44", "uint8_t[0x14]", 0x12E6F44),
            ("tip_manager", types["TipManager"], 0x12E6F58),
            ("_pad_12e6ff0", "uint8_t[0x4]", 0x12E6FF0),
        )
        for name, member_type, offset in member_types:
            code = root.add_udm(ida_typeinf.udm_t(name, member_type, offset * 8))
            if code != ida_typeinf.TERR_OK:
                raise RuntimeError(f"add {name}: {_error_text(code)}")
    except (RuntimeError, ValueError) as exc:
        return {
            "status": "failed",
            "reason": "mutation_failed",
            "error": str(exc),
            "readback": _readback(root),
        }

    if not _is_canonical(root):
        return {
            "status": "failed",
            "reason": "verification_failed",
            "readback": _readback(root),
        }
    root_global = _rebind_game_root_global()
    if root_global["status"] == "failed":
        return root_global
    return {
        "status": "applied",
        "readback": _readback(root),
        "root_global": root_global,
    }
