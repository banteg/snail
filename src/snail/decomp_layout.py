"""Layout of the recovered source tree (`decomp/`), derived from Windows link order.

Every recovered function lives in its unit, `decomp/<sequence>/<unit>/`, normally as
`<function>.cpp`; functions the compiler emits from one definition (a global's
constructor and its registration thunk) share that definition's file.
Units follow `analysis/ownership/windows-link-order.json`: the game objects were
linked alphabetically, then the engine library. A unit is either an attested
object (Border, SubGame, ...), an unnamed run with a name candidate read from the
binary (G0, GDX), or an unresolved run between two objects. Matcher scratches
keep their configs and notes and point here with `SOURCE=`.
"""

import json
import os
from pathlib import Path

from .match import load_scratch_config
from .symbols import load_function_symbol_manifest

LINK_ORDER = Path("analysis/ownership/windows-link-order.json")
FUNCTIONS = Path("analysis/symbols/gameplay-functions.json")
SCRATCHES = Path("tools/match/scratches")
DECOMP = Path("decomp")
LAYOUT = DECOMP / "layout.json"

# The engine library follows the game objects in the image.
ENGINE_LIBRARY_START = 0x449460
# Unnamed runs whose own strings name their source file (windows-link-order.md).
BINARY_NAME_CANDIDATES = {
    0x406BC0: ("G0", "the binary names G0.cpp where ObjectList/TextureList are initialized"),
    0x4114B0: ("GDX", "create_index_buffer reports DX_INDEXBUFFER_MAX in GDX.h"),
}


def _unit(entry: dict) -> tuple[str, str, str]:
    """Directory name, evidence kind and evidence text of one link-order object."""
    start = int(entry["start"], 16)
    if entry["object"]:
        name = entry["object"].removesuffix(".o")
        verified = entry["mobile_verified"]
        return name, "link-order-object", (
            f"{entry['object']} in alphabetical link order; "
            f"{verified} of {entry['function_count']} functions carry a consistent mobile label"
        )
    if start in BINARY_NAME_CANDIDATES:
        name, why = BINARY_NAME_CANDIDATES[start]
        before, after = entry["between"]
        return name, "binary-name-candidate", f"unnamed run between {before} and {after}; {why}"
    before, after = (
        {"^": "start", "$": "end"}.get(side, side.removesuffix(".o"))
        for side in entry["between"]
    )
    return f"between-{before}-{after}", "unresolved-boundary", (
        f"functions between {entry['between'][0]} and {entry['between'][1]} "
        "with no object name in the binary"
    )


def _source_path(root: Path, function: str, directory: Path) -> str:
    """Where a function's scratch points, or the conventional file for a new one."""
    scratch = root / SCRATCHES / function
    if (scratch / "scratch.conf").exists():
        source = load_scratch_config(scratch).source_path.resolve()
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
        sequence = "engine" if start >= ENGINE_LIBRARY_START else "game"
        directory = DECOMP / sequence / name
        units.append(
            {
                "name": name,
                "sequence": sequence,
                "object": entry["object"],
                "layout_evidence": evidence_kind,
                "evidence": evidence,
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


def layout_problems(root: Path) -> list[str]:
    """Differences between the committed tree, its layout and the scratch configs."""
    expected = build_layout(root)
    problems = []
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
            if config.source_path.resolve() != (root / source["path"]).resolve():
                problems.append(f"{source['config']} does not point at {source['path']}")
    for path in sorted((root / DECOMP).rglob("*.cpp")):
        relative = path.relative_to(root).as_posix()
        if relative not in listed:
            problems.append(f"{relative} is not in the layout")
    return problems
