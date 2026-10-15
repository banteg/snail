"""Compile decomp units as whole translation units and compare match results.

  uv run tools/match/whole_tu_experiment.py dump OUT.json
      Score every scratch (cached) and write per-function state.
  uv run tools/match/whole_tu_experiment.py units [UNIT ...]
      Add whole-unit groups from decomp/layout.json to translation_units.json
      (all units when none are named). Members follow address order; members whose
      build profile differs from the unit majority stay out. Existing groups that
      lie wholly inside the unit are absorbed; members of other groups stay out.
  uv run tools/match/whole_tu_experiment.py rename-helpers decomp/game/Path
      Suffix static helpers whose names collide across files in one unit.
  uv run tools/match/whole_tu_experiment.py compare BASE.json NEW.json
      Per-unit summary of compile errors and state changes.

Every command except `dump` and `compare` edits checked-in files; run it on a
scratch branch and restore with git afterwards.
"""

import collections
import json
import re
import sys
from pathlib import Path

from snail import match as m
from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    load_function_symbol_manifest,
)

REPO = m.DEFAULT_MATCH_ROOT.parents[1]
TRANSLATION_UNITS = m.DEFAULT_MATCH_ROOT / "translation_units.json"
STATIC_DEFINITION = re.compile(r"^static[^\n;{]*?\b(\w+)\s*\([^;{]*?\)\s*\{", re.MULTILINE | re.DOTALL)


def dump(out: Path) -> None:
    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    statuses = m.collect_scratch_statuses(manifest, REPO / manifest.primary_target)
    rows = {
        s.config.function: {
            "state": s.state,
            "ratio": s.ratio,
            "structural": s.structural_ratio,
            "size": s.target_size,
            "byte_exact": s.body_byte_exact,
            "error": s.error,
        }
        for s in statuses
    }
    out.write_text(json.dumps(rows, indent=1, sort_keys=True) + "\n")
    print(collections.Counter(row["state"] for row in rows.values()))


def units(names: list[str]) -> None:
    layout = json.loads((REPO / "decomp/layout.json").read_text())
    payload = json.loads(TRANSLATION_UNITS.read_text())
    for unit in layout["units"]:
        if names and unit["name"] not in names:
            continue
        configs = [
            m.load_scratch_config(REPO / source["config"])
            for source in sorted(unit["sources"], key=lambda s: int(s["address"], 16))
            if (REPO / source["config"] / "scratch.conf").exists()
        ]
        profiles = collections.Counter((c.compiler, c.cflags) for c in configs)
        if not profiles:
            continue
        majority = profiles.most_common(1)[0][0]
        members = []
        for config in configs:
            name = config.directory.name
            if (config.compiler, config.cflags) != majority:
                print(f"  {unit['name']}: excluded {name} ({config.cflags})")
            elif name not in members:
                members.append(name)
        # A smaller group inside this unit is absorbed; one reaching outside keeps its members.
        groups = payload["units"]
        absorbed = [g for g in groups if set(g["members"]) <= set(members)]
        kept = [g for g in groups if g not in absorbed]
        taken = {member for g in kept for member in g["members"]}
        members = [name for name in members if name not in taken]
        if len(members) < 2:
            continue
        for group in absorbed:
            print(f"  {unit['name']}: absorbed {group['name']}")
        payload["units"] = [*kept, {
            "name": re.sub(r"[^a-z0-9]+", "_", unit["name"].lower()).strip("_"),
            "source_object": f"{unit['name']}.o",
            "members": members,
        }]
    TRANSLATION_UNITS.write_text(json.dumps(payload, indent=2) + "\n")


def rename_helpers(unit: Path) -> None:
    owners = collections.defaultdict(list)
    for path in sorted(unit.glob("*.cpp")):
        for name in set(STATIC_DEFINITION.findall(path.read_text())):
            owners[name].append(path)
    for name, paths in owners.items():
        if len(paths) < 2:
            continue
        for path in paths:
            path.write_text(re.sub(rf"\b{name}\b", f"{name}__{path.stem}", path.read_text()))
        print(f"{name}: {len(paths)} files")


def compare(base_path: Path, new_path: Path) -> None:
    base = json.loads(base_path.read_text())
    new = json.loads(new_path.read_text())
    groups = json.loads(TRANSLATION_UNITS.read_text())["units"]
    for group in groups:
        members = group["members"]
        errors = [new[f]["error"] for f in members if new[f]["error"]]
        if errors:
            print(f"{group['name']:34s} {len(members):3d}  error  {errors[0].splitlines()[0][:140]}")
            continue
        before = sum(base[f]["state"] == "match" for f in members)
        after = sum(new[f]["state"] == "match" for f in members)
        print(f"{group['name']:34s} {len(members):3d}  match {before} -> {after}")
        for f in members:
            b, n = base[f], new[f]
            if (b["state"], b["ratio"], b["byte_exact"]) != (n["state"], n["ratio"], n["byte_exact"]):
                print(f"    {f}: {b['state']} {b['ratio']:.4f} -> {n['state']} {n['ratio']:.4f}")


if __name__ == "__main__":
    command, *rest = sys.argv[1:]
    if command == "dump":
        dump(Path(rest[0]))
    elif command == "units":
        units(rest)
    elif command == "rename-helpers":
        rename_helpers(Path(rest[0]))
    elif command == "compare":
        compare(Path(rest[0]), Path(rest[1]))
    else:
        raise SystemExit(__doc__)
