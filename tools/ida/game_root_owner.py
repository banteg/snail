from __future__ import annotations

import re

import ida_typeinf
import idc


GAME_ROOT_SIZE = 0x12E6FF4
GAME_ROOT_CATALOG_OFFSET = 0x44100
GAME_ROOT_FRONTEND_OFFSET = 0x4EC10
GAME_ROOT_SUBGAME_OFFSET = 0x74618
GAME_ROOT_GLOBAL_ADDRESS = 0x4DF904
GAME_ROOT_ACTIVE_BOD_LIST_OFFSET = 0x5A8
GAME_ROOT_ACTIVE_BOD_LIST_SIZE = 0xC

_TAIL_TYPE_SIZES = {
    "SubgameRuntime": 0x1272838,
    "HighScore": 0xF4,
    "TipManager": 0x98,
}

_FRONTEND_TYPE_SIZES = {
    "Backdrop": 0x6CC,
    "Intro": 0x48,
    "MainMenu": 0x18,
    "StarManager": 0x4C,
    "Options": 0x24,
    "Exit": 0x1C,
    "BodBase": 0x38,
    "Logo": 0x25218,
}

_CATALOG_LOADER_TYPE_SIZES = {
    "RootBodCatalog": 0x4D00,
    "DirectXLoader": 0x5E10,
}

_CANONICAL_CATALOG_LOADER = (
    (0x44100, 0x4D00, "root_bod_catalog", "RootBodCatalog"),
    (0x48E00, 0x5E10, "directx_loader", "DirectXLoader"),
)

_CANONICAL_FRONTEND = (
    (0x4EC10, 0x6CC, "backdrop", "Backdrop"),
    (0x4F2DC, 0x48, "intro", "Intro"),
    (0x4F324, 0x18, "main_menu", "MainMenu"),
    (0x4F33C, 0x4C, "star_manager", "StarManager"),
    (0x4F388, 0x24, "options", "Options"),
    (0x4F3AC, 0x1C, "exit_controller", "Exit"),
    (0x4F3C8, 0x38, "root_bod_4f3c8", "BodBase"),
    (0x4F400, 0x25218, "logo", "Logo"),
)

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


def _member_snapshot(root: ida_typeinf.tinfo_t) -> list[dict[str, object]] | None:
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
    ]


def _region_snapshot(
    root: ida_typeinf.tinfo_t, start: int, *, include_overlap: bool = False
) -> list[dict[str, object]] | None:
    snapshot = _member_snapshot(root)
    if snapshot is None:
        return None
    if include_overlap:
        return [
            member
            for member in snapshot
            if int(member["offset"]) + int(member["size"]) > start
        ]
    return [member for member in snapshot if int(member["offset"]) >= start]


def _readback(root: ida_typeinf.tinfo_t, start: int) -> dict[str, object]:
    snapshot = _region_snapshot(root, start)
    return {
        "size": root.get_size(),
        "start": hex(start),
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


def _sync_active_bod_list_member(
    root: ida_typeinf.tinfo_t,
    bod_list_type: ida_typeinf.tinfo_t | None,
    *,
    require: bool,
) -> dict[str, object]:
    if bod_list_type is None:
        return {
            "status": "failed" if require else "deferred",
            "reason": "missing_named_type",
            "type": "BodList",
        }
    if bod_list_type.get_size() != GAME_ROOT_ACTIVE_BOD_LIST_SIZE:
        return {
            "status": "failed",
            "reason": "owner_size_mismatch",
            "type": "BodList",
            "observed": bod_list_type.get_size(),
            "expected": GAME_ROOT_ACTIVE_BOD_LIST_SIZE,
        }

    snapshot = _member_snapshot(root)
    candidates = (
        []
        if snapshot is None
        else [
            member
            for member in snapshot
            if int(member["offset"]) == GAME_ROOT_ACTIVE_BOD_LIST_OFFSET
        ]
    )
    if len(candidates) != 1:
        return {
            "status": "failed" if require else "deferred",
            "reason": "unexpected_active_bod_list_members",
            "candidate_count": len(candidates),
        }

    member = candidates[0]
    expected = {
        "offset": GAME_ROOT_ACTIVE_BOD_LIST_OFFSET,
        "size": GAME_ROOT_ACTIVE_BOD_LIST_SIZE,
        "name": "active_bod_list",
        "type": "BodList",
    }
    observed = {
        "offset": int(member["offset"]),
        "size": int(member["size"]),
        "name": str(member["name"]),
        "type": str(member["type"]),
    }
    if observed == expected:
        return {"status": "unchanged", "member": observed}
    if observed["name"] != expected["name"] or observed["size"] != expected["size"]:
        return {
            "status": "failed",
            "reason": "unexpected_active_bod_list_layout",
            "observed": observed,
            "expected": expected,
        }

    code = root.set_udm_type(int(member["index"]), bod_list_type)
    if code != ida_typeinf.TERR_OK:
        return {
            "status": "failed",
            "reason": "set_active_bod_list_type_failed",
            "error": _error_text(code),
        }

    verified_snapshot = _member_snapshot(root)
    verified_candidates = (
        []
        if verified_snapshot is None
        else [
            candidate
            for candidate in verified_snapshot
            if int(candidate["offset"]) == GAME_ROOT_ACTIVE_BOD_LIST_OFFSET
        ]
    )
    if len(verified_candidates) != 1:
        return {
            "status": "failed",
            "reason": "active_bod_list_readback_failed",
            "candidate_count": len(verified_candidates),
        }
    verified_member = verified_candidates[0]
    verified = {
        "offset": int(verified_member["offset"]),
        "size": int(verified_member["size"]),
        "name": str(verified_member["name"]),
        "type": str(verified_member["type"]),
    }
    if verified != expected:
        return {
            "status": "failed",
            "reason": "active_bod_list_verification_failed",
            "observed": verified,
            "expected": expected,
        }
    return {
        "status": "applied",
        "before": observed,
        "member": verified,
    }


def _is_canonical(
    root: ida_typeinf.tinfo_t,
    start: int,
    expected: tuple[tuple[int, int, str, str], ...],
) -> bool:
    snapshot = _region_snapshot(root, start)
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
    return observed == expected


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


def _is_replaceable_padding(member: dict[str, object]) -> bool:
    name = str(member["name"])
    type_name = str(member["type"])
    return (
        name.startswith(("unknown_", "_pad_"))
        and (type_name.startswith("uint8_t[") or type_name.startswith("unsigned char["))
    )


def _compose_owner_graph(
    root: ida_typeinf.tinfo_t,
    *,
    start: int,
    expected: tuple[tuple[int, int, str, str], ...],
    types: dict[str, ida_typeinf.tinfo_t | None],
) -> dict[str, object]:
    snapshot = _region_snapshot(root, start, include_overlap=True)
    if snapshot is None:
        return {
            "status": "failed",
            "reason": "missing_game_root_members",
            "readback": _readback(root, start),
        }

    prefix_fragments: list[tuple[int, int, str]] = []
    for member in snapshot:
        offset = int(member["offset"])
        if offset >= start:
            continue
        if not _is_replaceable_padding(member):
            return {
                "status": "failed",
                "reason": "owner_span_overlaps_proved_member",
                "member": member,
                "readback": _readback(root, start),
            }
        prefix_fragments.append((offset, start - offset, str(member["name"])))

    try:
        for member in reversed(snapshot):
            code = root.del_udm(int(member["index"]))
            if code != ida_typeinf.TERR_OK:
                raise RuntimeError(f"delete {member['name']}: {_error_text(code)}")

        for offset, size, name in prefix_fragments:
            code = root.add_udm(
                ida_typeinf.udm_t(name, f"uint8_t[{size:#x}]", offset * 8)
            )
            if code != ida_typeinf.TERR_OK:
                raise RuntimeError(f"restore {name}: {_error_text(code)}")

        for offset, _size, name, type_name in expected:
            member_type = types.get(type_name)
            if member_type is None:
                member_type = type_name
            code = root.add_udm(ida_typeinf.udm_t(name, member_type, offset * 8))
            if code != ida_typeinf.TERR_OK:
                raise RuntimeError(f"add {name}: {_error_text(code)}")
    except (RuntimeError, ValueError) as exc:
        return {
            "status": "failed",
            "reason": "mutation_failed",
            "error": str(exc),
            "readback": _readback(root, start),
        }

    if not _is_canonical(root, start, expected):
        return {
            "status": "failed",
            "reason": "verification_failed",
            "readback": _readback(root, start),
        }
    return {"status": "applied", "readback": _readback(root, start)}


def sync_game_root_owner_graph(*, require: bool) -> dict[str, object]:
    """Compose recovered root owners without replacing the proved prefix."""

    type_sizes = {
        **_TAIL_TYPE_SIZES,
        **_FRONTEND_TYPE_SIZES,
        **_CATALOG_LOADER_TYPE_SIZES,
    }
    types = {
        name: _named_type(name)
        for name in ("GameRoot", "BodList", *type_sizes)
    }
    missing_tail = [name for name in _TAIL_TYPE_SIZES if types[name] is None]
    missing_active = ["BodList"] if require and types["BodList"] is None else []
    if types["GameRoot"] is None or missing_tail or missing_active:
        missing = (["GameRoot"] if types["GameRoot"] is None else []) + missing_tail
        missing.extend(missing_active)
        return {
            "status": "failed" if require else "deferred",
            "reason": "missing_named_types",
            "missing": missing,
        }

    root = types["GameRoot"]
    assert root is not None
    if root.get_size() != GAME_ROOT_SIZE:
        return {
            "status": "failed",
            "reason": "unexpected_game_root_size",
            "observed": root.get_size(),
            "expected": GAME_ROOT_SIZE,
        }

    active_bod_list = _sync_active_bod_list_member(
        root,
        types["BodList"],
        require=require,
    )
    if active_bod_list["status"] == "failed":
        return active_bod_list

    size_mismatches = {}
    for name, expected_size in _TAIL_TYPE_SIZES.items():
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

    frontend_missing = [name for name in _FRONTEND_TYPE_SIZES if types[name] is None]
    frontend_size_mismatches = {}
    for name, expected_size in _FRONTEND_TYPE_SIZES.items():
        tif = types[name]
        if tif is not None and tif.get_size() != expected_size:
            frontend_size_mismatches[name] = {
                "observed": tif.get_size(),
                "expected": expected_size,
            }

    frontend_ready = not frontend_missing and not frontend_size_mismatches

    catalog_loader_missing = [
        name for name in _CATALOG_LOADER_TYPE_SIZES if types[name] is None
    ]
    catalog_loader_size_mismatches = {}
    for name, expected_size in _CATALOG_LOADER_TYPE_SIZES.items():
        tif = types[name]
        if tif is not None and tif.get_size() != expected_size:
            catalog_loader_size_mismatches[name] = {
                "observed": tif.get_size(),
                "expected": expected_size,
            }

    catalog_loader_ready = (
        not catalog_loader_missing and not catalog_loader_size_mismatches
    )
    if catalog_loader_ready and frontend_ready:
        start = GAME_ROOT_CATALOG_OFFSET
        expected = (
            *_CANONICAL_CATALOG_LOADER,
            *_CANONICAL_FRONTEND,
            *_CANONICAL_TAIL,
        )
        owner_scope = "catalog_loader_frontend_and_tail"
    elif frontend_ready:
        start = GAME_ROOT_FRONTEND_OFFSET
        expected = (*_CANONICAL_FRONTEND, *_CANONICAL_TAIL)
        owner_scope = "frontend_and_tail"
    else:
        start = GAME_ROOT_SUBGAME_OFFSET
        expected = _CANONICAL_TAIL
        owner_scope = "tail_only"

    if _is_canonical(root, start, expected):
        mutation = {"status": "unchanged", "readback": _readback(root, start)}
    else:
        mutation = _compose_owner_graph(
            root,
            start=start,
            expected=expected,
            types=types,
        )
    if mutation["status"] == "failed":
        return mutation

    root_global = _rebind_game_root_global()
    if root_global["status"] == "failed":
        return root_global
    status = (
        "applied"
        if "applied" in {mutation["status"], active_bod_list["status"]}
        else mutation["status"]
    )
    return {
        "status": status,
        "owner_scope": owner_scope,
        "active_bod_list": active_bod_list,
        "readback": mutation["readback"],
        "frontend_types": {
            "status": "ready" if frontend_ready else "deferred",
            "missing": frontend_missing,
            "size_mismatches": frontend_size_mismatches,
        },
        "catalog_loader_types": {
            "status": "ready" if catalog_loader_ready else "deferred",
            "missing": catalog_loader_missing,
            "size_mismatches": catalog_loader_size_mismatches,
        },
        "root_global": root_global,
    }
