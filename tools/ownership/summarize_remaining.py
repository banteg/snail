#!/usr/bin/env python3
"""Retain unresolved public code with candidate hints, never guessed ownership."""
import json
from collections import defaultdict

from snail.match_report import build_report
from snail.symbols import REPO_ROOT

root = REPO_ROOT
functions = json.loads((root / "analysis/progress/win32-reflexive.json").read_text())["functions"]
resolved = json.loads((root / "artifacts/ownership/resolved.json").read_text())
report = build_report(functions)
other = {r["address"] for r, unit in zip(functions, report["units"], strict=True)
         if unit["metadata"]["progress_categories"] == ["other"]}
references = defaultdict(lambda: defaultdict(set))
for row in resolved["accepted"]:
    for ref in row["refs"]:
        target = (ref["target"] - (ref["addend"] or 0)) & 0xffffffff
        if target in other and ref["type"] in {6, 20}:
            references[target][ref["symbol"]].add(row["address"])
rows = []
for function in functions:
    address = function["address"]
    if address not in other:
        continue
    if 0x44e950 <= address < 0x47bdf4:
        hint = "D3DX8 cluster; not yet attributed"
    elif 0x47d900 <= address < 0x48b32c:
        hint = "standalone PNG/zlib cluster; not yet attributed"
    elif address >= 0x48b32c:
        hint = "CRT cluster; not yet attributed"
    else:
        hint = "unassigned/import/boundary code; inspect individually"
    candidates = resolved["remaining_candidates"].get(str(address), [])
    rows.append({"address": address, "analyzer_name": function["name"], "owned_code_bytes": function["size"],
                 "ranges": function["ranges"], "is_function": function["is_function"], "cluster_hint": hint,
                 "unresolved_body_candidates": sorted({r["symbol"] for r in candidates}),
                 "incoming_symbol_hints": [{"symbol": symbol, "callers": sorted(callers)}
                                           for symbol,callers in sorted(references[address].items())]})
output = {"schema": 1, "policy": "Hints only. These entries have not been attributed or renamed by this pass.",
          "units": len(rows), "code_bytes": sum(r["owned_code_bytes"] for r in rows), "functions": rows}
(root / "analysis/ownership/remaining-code.json").write_text(json.dumps(output, indent=2) + "\n")
print(f"Recorded {len(rows)} unresolved units, {output['code_bytes']} disjoint code bytes")
