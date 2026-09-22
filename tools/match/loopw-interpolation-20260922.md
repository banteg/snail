# LoopTheLoopW interpolation-bank ownership

The interpolation operation now borrows the actual `primary_samples` field
through a read-only pointer reference. This recovers one native addressing
byte without changing any other candidate byte, relocation, or reference.
LoopTheLoopW remains **partial**: 99.86577181%, 745/745 instructions, prefix
335, and 55 clean positional references. No normalized or encoded-body match
credit is added.

The retained helper performs the existing center interpolation, preserving its
accesses and arithmetic grouping. Passing the outer bank alias emits the old
encoding; passing the field emits the improved encoding. A local reference to
the field produces the same improvement. This supports operation-local bank
ownership, but does not establish an original helper name or unique source.

The [receipt](loopw-interpolation-20260922.json) contains 34 source controls,
40 pinned build inputs, complete before/after byte captures, relocation and
reference records, and all 28 literal local branches. Thirty-three controls
compile. The remaining control explicitly records the invalid attempt to bind
the existing const pointer reference to a mutable pointer-reference parameter.

| Control | Result |
| --- | --- |
| Previous source; helper borrowing outer bank alias | Original encoding |
| Local, guarded, or pre-loop reference to the field | One byte recovered |
| Interpolation helper borrowing the field | Same one byte recovered; retained |
| Bank passed by value | 93.48%, 742/745 instructions; rejected |
| Endpoint values instead of references | 99.20%, 747/745 instructions; rejected |
| Destination ownership variants | Neutral or regressive; no output-store recovery |
| Rotation helpers and matrix references | Neutral or regressive; no schedule recovery |

Both extracted candidate bodies and the native extent are 2,736 bytes. The
audited body is 2,725 bytes; the following 11 padding bytes remain separately
accounted for. Only candidate byte **835** changes, from `03` to native `18`.
The complete instruction at offsets **833–836** now agrees literally:
`d9 44 18 e8`, or `fld [eax + ebx - 0x18]`. All relocations and the entire
reference audit are unchanged. All 28 local jump encodings agree with native.

Five unequal body bytes remain after audited relocation handling: output-store
SIB byte **859**, and secondary rotation push/load ordering at **1317–1320**.
The equal effective address of the remaining SIB does not earn encoded credit.

## Replay

The generic replayer validates every source reconstruction before selecting a
control. Both the retained source and full reversal freshly reproduce their
recorded compiler, code fingerprint, counts, prefix, score, and reference audit:

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/loopw-interpolation-20260922.json \
  --function initialize_looptheloopw_path_template_pair \
  --batch retained-source-format --label canonical-format --replay
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/loopw-interpolation-20260922.json \
  --function initialize_looptheloopw_path_template_pair \
  --batch reversal --label previous-source --replay
```

The existing independent mesh checker also accepts these captured bodies. It
decodes each instruction, validates every relocation against its native target,
consumes all 55 positional references, and checks literal branch destinations.
Run this from the repository root:

```sh
uv run python - <<'PY'
import copy
import importlib.util
import json
from pathlib import Path

root = Path("tools/match")
spec = importlib.util.spec_from_file_location(
    "mesh_check", root / "check_mesh_owner_frontier_20260921.py"
)
checker = importlib.util.module_from_spec(spec)
spec.loader.exec_module(checker)
receipt = json.loads((root / "loopw-interpolation-20260922.json").read_text())
p = receipt["proof"]
assert p["before"]["references"] == p["after"]["references"]
proof = {
    "baseline": p["before"],
    "retained": dict(p["after"], target_instructions=[{"address": 0x41BB40}]),
}
result = checker.verify(proof)
assert result["changed_offsets"] == [835]
assert result["strict_positional_references"] == 55
assert result["literal_local_branches"] == 28
assert result["unequal_literal_offsets"] == [859, 1317, 1318, 1319, 1320]
for corrupt_reference in (False, True):
    bad = copy.deepcopy(proof)
    if corrupt_reference:
        bad["retained"]["references"]["entries"][0]["target_references"][0]["value"] ^= 1
    else:
        data = bytearray.fromhex(bad["retained"]["candidate_hex"])
        data[835] ^= 1
        bad["retained"]["candidate_hex"] = data.hex()
    try:
        checker.verify(bad)
    except AssertionError:
        pass
    else:
        raise AssertionError("Corruption was accepted")
print(json.dumps(result, indent=2))
PY
```

All 785 scratch checks and 1,140 tests pass. Extern lint and the strict
experiment/spec checks pass. The official reversal is recorded against the
new source epoch and reproduces the previous code fingerprint. The public
report refresh and separate saved-evidence check pass: all semantic function
rows and totals are unchanged, including 734 encoded matches. Report changes
are limited to COFF object identities, this source hash, and the prior-evidence
hash.
