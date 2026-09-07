"""Run via bn py in the Snail Mail view; default is a read-only preview.

Apply with APPLY=True in the bn Python scope. Names and comments only; existing
non-placeholder names are preserved by the reviewed attribution map.
"""
import hashlib
import json
from pathlib import Path

view = globals()["bv"]
root = Path(view.file.filename).resolve().parents[2]
if Path(view.file.filename).name != "SnailMail_unwrapped.exe.bndb":
    raise ValueError("select the Snail Mail database explicitly")
path = root / "analysis/ownership/library-attribution.json"
attribution = json.loads(path.read_text())
if hashlib.sha256((root / "artifacts/bin/SnailMail_unwrapped.exe").read_bytes()).hexdigest() != attribution["target_sha256"]:
    raise ValueError("original executable identity mismatch")
plan = []
for row in attribution["functions"]:
    function = view.get_function_at(row["address"])
    if function is None:
        raise ValueError(f"missing function at {row['address']:#x}")
    code = b"".join(view.read(a, b-a) for a,b in row["body_ranges"])
    if hashlib.sha256(code).hexdigest() != row["body_sha256"]:
        raise ValueError(f"live code differs from reviewed evidence at {row['address']:#x}")
    if function.name not in {row["original_binja_name"], row["name"]}:
        raise ValueError(f"unexpected existing name at {row['address']:#x}: {function.name}")
    note = f"[Snail ownership 2026-09-08] {row['component']}: {row.get('symbol', row['name'])}. Evidence: {row['basis']}."
    if "compatible_candidates" in row:
        note += f" Compatible COFF candidates: {len(row['compatible_candidates'])}; representative {row['provider']} / {row['member']}."
        note += f" Unresolved references: {len(row['unresolved_references'])}."
    if "notes" in row:
        note += " " + row["notes"]
    note += " Identity/ownership only; see analysis/ownership/library-attribution.json."
    comment = function.comment or ""
    if note not in comment:
        comment = (comment.rstrip() + "\n\n" + note).lstrip()
    plan.append((function, row, comment))

apply_changes = bool(globals().get("APPLY", False))
renames = [{"address": row["address"], "old": function.name, "new": row["name"]}
           for function,row,_ in plan if function.name != row["name"]]
comment_count = sum(comment != (function.comment or "") for function,_,comment in plan)
snapshot_saved = False
if apply_changes and (renames or comment_count):
    transaction = view.begin_undo_actions()
    try:
        for function,row,comment in plan:
            if function.name != row["name"]:
                function.name = row["name"]
            function.comment = comment
        for function,row,comment in plan:
            if function.name != row["name"] or function.comment != comment:
                raise RuntimeError(f"readback failed at {row['address']:#x}")
    except Exception:
        view.revert_undo_actions(transaction)
        raise
    view.commit_undo_actions(transaction)
    snapshot_saved = view.file.save_auto_snapshot()
    if snapshot_saved is not True:
        raise RuntimeError("live changes verified, but database snapshot save failed")
    receipt = {"target": view.file.filename, "snapshot_saved": snapshot_saved,
               "renames": renames, "comments_updated": comment_count,
               "attribution_sha256": hashlib.sha256(path.read_bytes()).hexdigest()}
    (root / "artifacts/ownership/binja-update.json").write_text(json.dumps(receipt, indent=2) + "\n")
result = {"apply": apply_changes, "names": len(renames), "comments": comment_count,
          "verified_functions": len(plan), "snapshot_saved": snapshot_saved}
