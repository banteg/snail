"""Which recovered sources the modern port compiles, and how.

The port compiles `core` and `boundary` functions from `decomp/`, except the
boundary functions in `port/replaced.txt` (the shell reimplements them), plus the
`replaceable-platform` and `third-party` functions in `port/portable.txt`, whose
recovered bodies are portable C. Everything else from the platform and third-party scopes is
replaced by the shell. The result is committed as `port/sources.txt`, which
`port/build.zig` reads.
"""

import json
import subprocess
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

LAYOUT = Path("decomp/layout.json")
REPLACED = Path("port/replaced.txt")
PORTABLE = Path("port/portable.txt")
SOURCES = Path("port/sources.txt")
CFLAGS = Path("port/cflags.txt")
OBJECTS = Path("port/generated/objects")
COMPILED_SCOPES = {"core", "boundary"}
# Relative to port/, as in build.zig.
INCLUDE_DIRECTORIES = ("../tools/match/include", "compat")


def _listed(root: Path, path: Path) -> dict[str, str]:
    """`function [reason]` lines, ignoring comments."""
    listed = {}
    for line in (root / path).read_text().splitlines():
        if line.strip() and not line.startswith("#"):
            function, _, reason = line.partition(" ")
            listed[function] = reason.strip()
    return listed


def source_list(root: Path) -> list[str]:
    """Source paths relative to port/, one per compiled file, in link order."""
    layout = json.loads((root / LAYOUT).read_text())
    replaced, portable = _listed(root, REPLACED), _listed(root, PORTABLE)
    scope = {s["function"]: s["port_scope"] for unit in layout["units"] for s in unit["sources"]}
    for listing, names, expected in (
        (REPLACED, replaced, {"boundary"}),
        (PORTABLE, portable, {"replaceable-platform", "third-party"}),
    ):
        if wrong := sorted(name for name in names if scope.get(name) not in expected):
            raise ValueError(f"{listing} lists functions outside {sorted(expected)}: {', '.join(wrong)}")
    paths = []
    for unit in layout["units"]:
        for source in unit["sources"]:
            compiled = (
                source["port_scope"] in COMPILED_SCOPES and source["function"] not in replaced
            ) or source["function"] in portable
            path = f"../{source['path']}"
            if compiled and path not in paths:
                paths.append(path)
    return paths


def sources_text(root: Path) -> str:
    return "\n".join(source_list(root)) + "\n"


def compile_flags(root: Path) -> list[str]:
    flags = [
        line.strip()
        for line in (root / CFLAGS).read_text().splitlines()
        if line.strip() and not line.startswith("#")
    ]
    return [*flags, *(f"-I{directory}" for directory in INCLUDE_DIRECTORIES)]


def object_path(root: Path, source: str) -> Path:
    return (root / OBJECTS).resolve() / (source.removeprefix("../").replace("/", "_") + ".o")


def compile_objects(root: Path, sources: list[str], *, jobs: int = 10) -> dict[str, str]:
    """Compile sources (relative to port/) to wasm32 objects; return compiler errors."""
    (root / OBJECTS).mkdir(parents=True, exist_ok=True)
    flags = compile_flags(root)

    def build(source: str) -> tuple[str, str]:
        completed = subprocess.run(
            ["zig", "c++", "-target", "wasm32-wasi", "-c", *flags, source, "-o", str(object_path(root, source))],
            cwd=root / "port",
            capture_output=True,
            text=True,
            check=False,
        )
        return source, completed.stderr if completed.returncode else ""

    with ThreadPoolExecutor(jobs) as pool:
        return {source: error for source, error in pool.map(build, sources) if error}
