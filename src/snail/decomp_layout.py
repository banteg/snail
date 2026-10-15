"""Layout of the recovered source tree (`decomp/`), derived from Windows link order.

Every recovered function lives in its unit, `decomp/<sequence>/<unit>/`, normally as
`<function>.cpp`; functions the compiler emits from one definition (a global's
constructor and its registration thunk) share that definition's file.
Units follow `analysis/ownership/windows-link-order.json`: the game objects were
linked alphabetically, then the engine library, then d3dx8.lib. A unit is an
object attested by mobile labels in link order (Border, SubGame, ...), an object
or name candidate carrying its own recorded evidence (Png, G0, Joystick, ...), or
an unresolved run between two objects. Functions placed into an attested object
without a mobile label carry their evidence as placements. Matcher scratches
keep their configs and notes and point here with `SOURCE=`.
"""

import json
import os
from itertools import pairwise
from pathlib import Path

from .match import load_scratch_config
from .symbols import load_function_symbol_manifest

LINK_ORDER = Path("analysis/ownership/windows-link-order.json")
FUNCTIONS = Path("analysis/symbols/gameplay-functions.json")
SCRATCHES = Path("tools/match/scratches")
DECOMP = Path("decomp")
LAYOUT = DECOMP / "layout.json"


def _unit(entry: dict) -> tuple[str, str, str]:
    """Directory name, evidence kind and evidence text of one link-order object."""
    if "evidence" in entry:
        evidence = entry["evidence"]
        if entry["object"]:
            return Path(entry["object"]).stem, evidence["kind"], f"{entry['object']}: {evidence['note']}"
        before, after = entry["between"]
        return Path(entry["candidate"]).stem, evidence["kind"], (
            f"unnamed run between {before} and {after}; {evidence['note']}"
        )
    if entry["object"]:
        verified = entry["mobile_verified"]
        return Path(entry["object"]).stem, "link-order-object", (
            f"{entry['object']} in alphabetical link order; "
            f"{verified} of {entry['function_count']} functions carry a consistent mobile label"
        )
    before, after = (
        {"^": "start", "$": "end"}.get(side, Path(side).stem)
        for side in entry["between"]
    )
    return f"between-{before}-{after}", "unresolved-boundary", (
        f"functions between {entry['between'][0]} and {entry['between'][1]} "
        "with no object name in the binary"
    )


def _sequence(sequences: list[dict], start: int) -> dict:
    return [sequence for sequence in sequences if int(sequence["start"], 16) <= start][-1]


def _source_path(root: Path, function: str, directory: Path) -> str:
    """Where a function's scratch points, or the conventional file for a new one."""
    scratch = root / SCRATCHES / function
    if (scratch / "scratch.conf").exists():
        source = load_scratch_config(scratch).source_path
        if source.is_relative_to((root / DECOMP).resolve()):
            return source.relative_to(root.resolve()).as_posix()
    return (directory / f"{function}.cpp").as_posix()


def build_layout(root: Path) -> dict:
    link_order = json.loads((root / LINK_ORDER).read_text())
    manifest = load_function_symbol_manifest(root / FUNCTIONS)
    scope = {function.name: function.port_scope for function in manifest.functions}
    address = {function.name: function.address for function in manifest.functions}
    objects = link_order["objects"]
    units = []
    for index, entry in enumerate(objects):
        name, evidence_kind, evidence = _unit(entry)
        start = int(entry["start"], 16)
        end = int(objects[index + 1]["start"], 16) if index + 1 < len(objects) else None
        sequence = _sequence(link_order["sequences"], start)["name"]
        directory = DECOMP / sequence / name
        units.append(
            {
                "name": name,
                "sequence": sequence,
                "object": entry["object"],
                "layout_evidence": evidence_kind,
                "evidence": evidence,
                "placements": [
                    {key: placement[key] for key in ("functions", "evidence", "note")}
                    for placement in entry.get("placements", [])
                ],
                "range": [f"0x{start:x}", f"0x{end:x}" if end else None],
                "sources": [
                    {
                        "path": _source_path(root, function, directory),
                        "function": function,
                        "address": f"0x{address[function]:x}",
                        "port_scope": scope[function],
                        "config": (SCRATCHES / function).as_posix(),
                    }
                    for function in sorted(entry["functions"], key=address.__getitem__)
                ],
            }
        )
    return {
        "schema": 1,
        "kind": "snail-recovered-source-layout",
        "image": "SnailMail_unwrapped.exe",
        "target_sha256": link_order["target_sha256"],
        "link_order": LINK_ORDER.as_posix(),
        "units": units,
    }


def layout_text(layout: dict) -> str:
    return json.dumps(layout, indent=1) + "\n"


def source_reference(root: Path, config: str, path: str) -> str:
    """The SOURCE= value of a scratch config pointing at a tree file."""
    return Path(os.path.relpath(root / path, root / config)).as_posix()


def order_problems(link_order: dict) -> list[str]:
    """Named objects that break their sequence's alphabetical link order."""
    problems = []
    for sequence in link_order["sequences"]:
        if sequence["order"] != "alphabetical":
            continue
        names = [
            entry["object"] or entry.get("candidate")
            for entry in link_order["objects"]
            if _sequence(link_order["sequences"], int(entry["start"], 16)) is sequence
        ]
        names = [Path(name).stem for name in names if name]
        for before, after in pairwise(names):
            if before.casefold() >= after.casefold():
                problems.append(f"{after} does not sort after {before} in the {sequence['name']} link order")
    return problems


def layout_problems(root: Path) -> list[str]:
    """Differences between the committed tree, its layout and the scratch configs."""
    expected = build_layout(root)
    problems = order_problems(json.loads((root / LINK_ORDER).read_text()))
    if (root / LAYOUT).read_text() != layout_text(expected):
        problems.append(f"{LAYOUT} differs from the link-order layout; run snail decomp layout --write")
    listed = set()
    for unit in expected["units"]:
        directory = (DECOMP / unit["sequence"] / unit["name"]).as_posix()
        for source in unit["sources"]:
            listed.add(source["path"])
            if Path(source["path"]).parent.as_posix() != directory:
                problems.append(f"{source['function']} belongs in {directory}, not {source['path']}")
            if not (root / source["path"]).is_file():
                problems.append(f"missing {source['path']}")
            config = load_scratch_config(root / source["config"])
            if config.source_path != (root / source["path"]).resolve():
                problems.append(f"{source['config']} does not point at {source['path']}")
    for path in sorted((root / DECOMP).rglob("*.cpp")):
        relative = path.relative_to(root).as_posix()
        if relative not in listed:
            problems.append(f"{relative} is not in the layout")
    return problems
