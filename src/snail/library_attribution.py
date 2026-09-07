"""Conservative identity selection from complete-body COFF candidate evidence.

This establishes names/ownership, not source-built matching or complete reference
proof. An unresolved reference remains explicit even on an attributed function.
"""
from __future__ import annotations

from collections import defaultdict
from typing import Any

# Independently inspected cluster boundaries, not blanket ownership assignments.
# Only functions with a body candidate and the checks below can be attributed.
PROBE_RANGES = {
    "d3dx8": (0x44e950, 0x47bdf4, "d3dx8"),
    "vc6-sp6-libcmt": (0x48b32c, 0x497000, "msvc6-crt"),
    "libpng-1.2.5": (0x47d900, 0x48b32c, "libpng-1.2.5"),
    "zlib-1.2.1": (0x47d900, 0x48b32c, "zlib-1.2.1"),
}
# Seven arguments, read-struct allocation, 1.2.5 checks, inflateInit("1.2.1"),
# read callback installation and the second setjmp identify this independently.
SOURCE_ANCHORS = {0x47d91e: {"_png_create_read_struct_2"}}
SOURCE_ANCHOR_REFERENCES = {
    0x48572d: "_png_create_struct_2", 0x482f9b: "_png_init_mmx_flags",
    0x4858e6: "_png_set_mem_fn", 0x485b9a: "_png_set_error_fn",
    0x485995: "_png_warning", 0x485909: "_png_error",
    0x4857d4: "_png_malloc", 0x482a24: "_png_zalloc", 0x482a99: "_png_zfree",
    0x4844c1: "_inflateInit_", 0x484375: "_png_set_read_fn",
}


def component(row: dict[str, Any]) -> str | None:
    for prefix, (start, end, label) in PROBE_RANGES.items():
        if (row["provider"] == prefix or row["provider"].startswith(prefix + "-")) and start <= row["address"] < end:
            return label
    return None


def inspect_references(row: dict[str, Any], possible: dict[int, set[str]], image: bytes,
                       image_base: int, imports: dict[int, str]) -> tuple[list[dict], list[dict], list[dict]]:
    good, bad, unresolved = [], [], []
    for ref in row["refs"]:
        target = (ref["target"] - (ref["addend"] or 0)) & 0xffffffff
        symbol = ref["symbol"]
        entry = {"symbol": symbol, "target": target}
        if ref["type"] not in {6, 20}:
            unresolved.append({**entry, "reason": "unsupported relocation type"})
        elif target in possible:
            if symbol in possible[target]:
                good.append({**entry, "kind": "function-candidate"})
            else:
                bad.append({**entry, "kind": "function-conflict", "alternatives": sorted(possible[target])})
        elif symbol.startswith("__imp_") and target in imports:
            undecorated = symbol.removeprefix("__imp_").lstrip("_").split("@")[0]
            if undecorated == imports[target]:
                good.append({**entry, "kind": "import"})
            else:
                bad.append({**entry, "kind": "import-conflict"})
        elif ref["data_hex"] and (symbol.startswith("??_C@") or (ref["readonly"] and len(ref["data_hex"]) <= 128)):
            data = bytes.fromhex(ref["data_hex"])
            offset = target - image_base
            if 0 <= offset < len(image) and image[offset:offset + len(data)] == data:
                good.append({**entry, "kind": "data"})
            else:
                bad.append({**entry, "kind": "data-conflict"})
        else:
            unresolved.append(entry)
    return good, bad, unresolved


def resolve(providers: list[dict], image: bytes, image_base: int,
            imports: dict[int, str], *, anchors: dict[int, set[str]] | None = None) -> dict[str, Any]:
    anchor_references = SOURCE_ANCHOR_REFERENCES if anchors is None else {}
    anchors = SOURCE_ANCHORS if anchors is None else anchors
    candidates: dict[int, list[dict]] = defaultdict(list)
    for provider in providers:
        for row in provider["matches"]:
            candidates[row["address"]].append({**row, "provider": provider["id"]})

    def possibilities() -> dict[int, set[str]]:
        result = {address: {r["symbol"] for r in rows} for address, rows in candidates.items() if rows}
        for address, symbols in anchors.items():
            result.setdefault(address, set()).update(symbols)
        return result

    possible = possibilities()
    rejected = []
    while True:
        old_count = sum(map(len, candidates.values()))
        updated = {}
        for address, rows in candidates.items():
            kept = []
            for row in rows:
                _, bad, _ = inspect_references(row, possible, image, image_base, imports)
                if bad:
                    rejected.append({"address": address, "provider": row["provider"], "symbol": row["symbol"], "conflicts": bad})
                else:
                    kept.append(row)
            updated[address] = kept
        candidates = updated
        possible = possibilities()
        if sum(map(len, candidates.values())) == old_count:
            break

    selected = {a: [r for r in rows if component(r)] for a, rows in candidates.items()}
    selected = {a: rows for a, rows in selected.items() if rows}
    accepted = {}

    def inspect(row: dict) -> tuple[list[dict], list[dict], list[dict]]:
        return inspect_references(row, possible, image, image_base, imports)

    for address, rows in selected.items():
        if len({r["symbol"] for r in rows}) == 1 and (rows[0]["size"] >= 32 or any(inspect(r)[0] for r in rows)):
            row = max(rows, key=lambda r: len(inspect(r)[0]))
            accepted[address] = {**row, "component": component(row), "basis": "unique-full-body-with-reference-checks"}
    while True:
        votes: dict[int, set[str]] = defaultdict(set)
        for address, symbol in anchor_references.items():
            votes[address].add(symbol)
        for row in accepted.values():
            for ref in row["refs"]:
                if ref["type"] in {6, 20}:
                    target = (ref["target"] - (ref["addend"] or 0)) & 0xffffffff
                    votes[target].add(ref["symbol"])
        old_count = len(accepted)
        for address, rows in selected.items():
            if address in accepted:
                continue
            supported = [r for r in rows if r["symbol"] in votes[address]]
            if supported and len({r["symbol"] for r in supported}) == 1:
                row = max(supported, key=lambda r: len(inspect(r)[0]))
                accepted[address] = {**row, "component": component(row), "basis": "full-body-and-named-incoming-reference"}
        if len(accepted) == old_count:
            break
    for row in accepted.values():
        good, _, unresolved = inspect(row)
        row["consistent_references"] = good
        row["unresolved_references"] = unresolved
        row["compatible_candidates"] = sorted({
            (r["provider"], r["member"], r["extent"])
            for r in selected[row["address"]] if r["symbol"] == row["symbol"]
        }) if "member" in row else []
    return {
        "accepted": sorted(accepted.values(), key=lambda r: r["address"]),
        "rejected_candidates": rejected,
        "remaining_candidates": {str(a): rows for a, rows in selected.items() if a not in accepted},
    }
