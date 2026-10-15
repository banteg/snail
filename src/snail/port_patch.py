"""Patched copies of the recovered sources for the port; `decomp/` stays untouched.

Each `port/patches/*.patch` is a unified diff against files named by their paths from the repository root. A hunk
matches by its exact old text, which must occur once; line numbers only say where it was written. A hunk that no
longer matches exactly once stops the build, so a decomp edit that moves a patched site is caught, not built around.

The port compiles every recovered source and header from `port/generated/patched/`, at the same paths, patched or
not, so a patched header is the one every file sees. `snail port link` and `zig build` both refresh the copies.
"""

import re
from pathlib import Path

PATCHES = Path("port/patches")
PATCHED = Path("port/generated/patched")
INCLUDE = Path("decomp/include")
_HUNK = re.compile(r"@@ -\d+(?:,(\d+))? \+\d+(?:,(\d+))? @@")

Hunks = dict[str, list[tuple[str, str, str]]]


def load(root: Path) -> Hunks:
    """(patch name, old text, new text) hunks by file path, in patch name order."""
    hunks: Hunks = {}
    for patch in sorted((root / PATCHES).glob("*.patch")):
        lines = patch.read_text(encoding="latin-1").splitlines(keepends=True)
        rel = None
        i = 0
        while i < len(lines):
            line = lines[i]
            i += 1
            if line.startswith("+++ "):
                rel = line[4:].split()[0].removeprefix("b/")
                continue
            match = _HUNK.match(line)
            if not match:
                continue
            if rel is None:
                raise ValueError(f"{patch.name}: hunk before a +++ header")
            old_count, new_count = (int(n) if n is not None else 1 for n in match.groups())
            old: list[str] = []
            new: list[str] = []
            while len(old) < old_count or len(new) < new_count:
                tag, body = lines[i][:1], lines[i][1:]
                i += 1
                if tag in " -":
                    old.append(body)
                if tag in " +":
                    new.append(body)
            hunks.setdefault(rel, []).append((patch.name, "".join(old), "".join(new)))
    return hunks


def apply(rel: str, text: str, hunks: Hunks) -> str:
    for name, old, new in hunks.get(rel, ()):
        if (count := text.count(old)) != 1:
            raise ValueError(f"{name}: hunk for {rel} matches {count} times; audit the patch")
        text = text.replace(old, new)
    return text


def write(root: Path, sources: list[str]) -> None:
    """Write the copies of the include directory and of `sources` (relative to port/), patched."""
    hunks = load(root)
    rels = [path.relative_to(root).as_posix() for path in sorted((root / INCLUDE).rglob("*")) if path.is_file()]
    rels += [source.removeprefix("../") for source in sources]
    if unknown := sorted(set(hunks) - set(rels)):
        raise ValueError(f"{PATCHES} patches files the port does not compile: {', '.join(unknown)}")
    out = root / PATCHED
    written = set()
    for rel in rels:
        target = out / rel
        text = apply(rel, (root / rel).read_text(encoding="latin-1"), hunks)
        # Unchanged copies keep their timestamps, so the build reuses what it compiled.
        if not target.is_file() or target.read_text(encoding="latin-1") != text:
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text(text, encoding="latin-1")
        written.add(target)
    for stale in [path for path in out.rglob("*") if path.is_file() and path not in written]:
        stale.unlink()


def compile_path(source: str) -> str:
    """Where the port compiles a source (relative to port/): recovered sources from their copies."""
    return f"generated/patched/{source.removeprefix('../')}" if source.startswith("../") else source
