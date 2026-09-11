#!/usr/bin/env python3
"""Replay the objdiff-guided dispatch lifetime controls without promoting source."""

import argparse
import itertools
import json
import subprocess
from collections import Counter
from pathlib import Path

import capstone

from snail import match as matcher
from snail import match_objdiff as exporter

ROOT = Path(__file__).resolve().parents[2]
SCRATCH = ROOT / "tools/match/scratches/update_subgame"
RECIPES = (
    "objdiff-backdrop-lifetimes-20260911.json",
    "objdiff-mode-snapshot-20260911.json",
)
OBJD_SHA = "98f8275c27900c4fe2248fce3af37617658be49648fa7dbb5b376371f046dfdb"


def variants(source, recipe):
    sites = recipe["sites"]
    for site in sites:
        if source.count(site["find"]) != 1:
            raise ValueError(f"Source changed: {site['name']} is not unique")
    choices = ([None, *site["replacements"]] for site in sites)
    for selection in itertools.product(*choices):
        if not any(selection):
            continue
        text = source
        labels = []
        for site, choice in zip(sites, selection, strict=True):
            if choice is not None:
                text = text.replace(site["find"], choice["text"], 1)
                labels.append(f"{site['name']}/{choice['name']}")
        yield "+".join(labels), text


def compare(directory, output, tool):
    receipt = exporter.export_snapshot(directory, output)
    result_path = output.parent / (output.name + "-diff.json")
    subprocess.run(
        [
            str(tool),
            "diff",
            "-p",
            str(output),
            "-u",
            "update_subgame",
            "-o",
            str(result_path),
        ],
        check=True,
        capture_output=True,
        text=True,
    )
    diff = json.loads(result_path.read_text())
    native = json.loads((output / "native-diagnostics.json").read_text())
    symbol = diff["left"]["symbols"][0]
    summary = {
        "source_sha256": exporter.sha((directory / "scratch.cpp").read_bytes()),
        "snapshot_receipt_sha256": exporter.sha((output / "receipt.json").read_bytes()),
        "snapshot": str(output),
        "candidate_function_sha256": receipt["objects"]["candidate"]["input_sha256"],
        "native_match": native["match_ratio"],
        "native_instructions": native["target_instructions"],
        "candidate_instructions": native["candidate_instructions"],
        "references": native["masked_references"],
        "frame": native["stack_frame"],
        "body_byte_exact": native["body_byte_exact"],
        "objects": receipt["objects"],
        "objdiff": {
            "percent": symbol["match_percent"],
            "rows": dict(
                Counter(row.get("diff_kind", "equal") for row in symbol["instructions"])
            ),
        },
    }
    return summary, diff


def certify_tail(snapshot):
    """Check raw bytes and strict positional references independently of objdiff."""
    receipt = json.loads((snapshot / "receipt.json").read_text())
    for name, digest in receipt["files"].items():
        if exporter.sha((snapshot / name).read_bytes()) != digest:
            raise ValueError(f"Changed snapshot file: {name}")
    config = matcher.load_scratch_config(SCRATCH)
    if matcher.scratch_experiment_epoch(config) != receipt["experiment_epoch"]:
        raise ValueError("Native matching inputs changed since the snapshot")
    results = []
    status = matcher.evaluate_scratch(config, on_match=results.append)
    if (
        status.error
        or status.candidate_object_sha256 != receipt["candidate_object_sha256"]
    ):
        raise ValueError("Canonical compiler output changed during certification")
    result = results[0]
    raw = {
        side: (snapshot / f"{side}.bin").read_bytes()
        for side in ("target", "candidate")
    }
    normalized = {side: bytearray(data) for side, data in raw.items()}
    refs = {
        side: json.loads((snapshot / f"{side}-refs.json").read_text()) for side in raw
    }
    shift = 8
    start, end = 0x4ED, 0xE64
    target_refs = {
        ref["offset"]: ref for ref in refs["target"] if start <= ref["offset"] < end
    }
    candidate_refs = {
        ref["offset"] + shift: ref
        for ref in refs["candidate"]
        if start - shift <= ref["offset"] < end - shift
    }
    assert target_refs.keys() == candidate_refs.keys()
    audited = []
    for entry in result.masked_operand_audit.entries:
        if entry.target_offset is None or not start <= entry.target_offset < end:
            continue
        assert entry.status == "ok"
        assert entry.candidate_offset == entry.target_offset - shift
        pairs = list(
            zip(entry.target_references, entry.candidate_references, strict=True)
        )
        assert all(
            (a.kind, a.operand_index, a.key) == (b.kind, b.operand_index, b.key)
            and a.explained
            and b.explained
            for a, b in pairs
        )
        audited.append(
            {
                "target_offset": entry.target_offset,
                "candidate_offset": entry.candidate_offset,
                "references": [
                    {"kind": a.kind, "operand_index": a.operand_index, "key": a.key}
                    for a, _ in pairs
                ],
            }
        )
    assert sum(len(row["references"]) for row in audited) == len(target_refs)
    for offset, target_ref in target_refs.items():
        candidate_ref = candidate_refs[offset]
        assert (target_ref["key"], target_ref["type"]) == (
            candidate_ref["key"],
            candidate_ref["type"],
        )
        assert target_ref["explained"] and candidate_ref["explained"]
        for side, ref in (("target", target_ref), ("candidate", candidate_ref)):
            off = ref["offset"]
            assert raw[side][off : off + 4].hex() == ref["original"]
            normalized[side][off : off + 4] = b"\0" * 4
    left = normalized["target"][start:end]
    right = normalized["candidate"][start - shift : end - shift]
    assert len(left) == len(right) == 2423
    differences = [
        start + i for i, (a, b) in enumerate(zip(left, right, strict=True)) if a != b
    ]
    assert differences == [0xCE4]
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    branch = {}
    for side, offset in (("target", 0xCE2), ("candidate", 0xCDA)):
        insn = next(decoder.disasm(raw[side][offset : offset + 6], offset))
        assert insn.size == 6 and insn.mnemonic == "jl"
        branch[side] = {
            "offset": offset,
            "bytes": insn.bytes.hex(),
            "instruction": insn.mnemonic + " " + insn.op_str,
        }
    regions = []
    for lo, hi in ((start, 0xCE2), (0xCE8, end)):
        a = normalized["target"][lo:hi]
        b = normalized["candidate"][lo - shift : hi - shift]
        assert a == b
        regions.append(
            {
                "target_offsets": [lo, hi],
                "candidate_offsets": [lo - shift, hi - shift],
                "bytes": len(a),
                "audited_encoded_sha256": exporter.sha(a),
                "target_bytes": raw["target"][lo:hi].hex(),
                "candidate_bytes": raw["candidate"][lo - shift : hi - shift].hex(),
            }
        )
    return {
        "purpose": "Existing partial-body evidence; no new native function credit",
        "target_offsets": [start, end],
        "candidate_offsets": [start - shift, end - shift],
        "covered_bytes": 2423,
        "encoded_equal_bytes": sum(r["bytes"] for r in regions),
        "reference_fields": len(target_refs),
        "positional_reference_audit": audited,
        "differing_byte_offsets": differences,
        "unmatched_backedge": branch,
        "regions": regions,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--out", type=Path, required=True, help="New evidence directory"
    )
    parser.add_argument(
        "--objdiff",
        type=Path,
        default=ROOT / "artifacts/differ-pilot/tools/objdiff-cli",
    )
    args = parser.parse_args()
    tool = args.objdiff.resolve()
    if exporter.sha(tool.read_bytes()) != OBJD_SHA:
        raise ValueError("Expected the pinned objdiff 3.8.1 macOS arm64 binary")
    output = args.out.resolve()
    output.mkdir(parents=True, exist_ok=False)
    baseline, diff = compare(SCRATCH, output / "baseline", tool)
    report = {
        "schema": 1,
        "purpose": "diagnostic source controls; no native matches claimed",
        "base_commit": subprocess.check_output(
            ["git", "rev-parse", "HEAD"], cwd=ROOT, text=True
        ).strip(),
        "script_sha256": exporter.sha(Path(__file__).read_bytes()),
        "exporter_sha256": exporter.sha(Path(exporter.__file__).read_bytes()),
        "objdiff_sha256": OBJD_SHA,
        "baseline": baseline,
        "recipes": {},
        "controls": [],
        "changed_rows": [],
        "tail_certificate": certify_tail(output / "baseline"),
    }
    left, right = (
        diff[side]["symbols"][0]["instructions"] for side in ("left", "right")
    )
    for target, candidate in zip(left, right, strict=True):
        if not target.get("diff_kind") and not candidate.get("diff_kind"):
            continue
        row = {"kind": target.get("diff_kind", candidate.get("diff_kind"))}
        for side, entry in (("target", target), ("candidate", candidate)):
            insn = entry.get("instruction")
            row[side] = (
                None
                if insn is None
                else {
                    "offset": int(insn.get("address", 0)),
                    "size": insn["size"],
                    "instruction": insn["formatted"],
                }
            )
        report["changed_rows"].append(row)
    source = (SCRATCH / "scratch.cpp").read_text()
    for filename in RECIPES:
        raw = (SCRATCH / filename).read_bytes()
        report["recipes"][filename] = exporter.sha(raw)
        for label, text in variants(source, json.loads(raw)):
            number = len(report["controls"]) + 1
            directory = output / "sources" / str(number)
            directory.mkdir(parents=True)
            (directory / "scratch.cpp").write_text(text)
            (directory / "scratch.conf").write_bytes(
                (SCRATCH / "scratch.conf").read_bytes()
            )
            summary, _ = compare(directory, output / f"control-{number}", tool)
            summary.update(
                {
                    "recipe": filename,
                    "label": label,
                    "same_function_bytes": summary["candidate_function_sha256"]
                    == baseline["candidate_function_sha256"],
                }
            )
            report["controls"].append(summary)
            print(
                label,
                f"native={summary['native_match']:.8%}",
                f"same bytes={summary['same_function_bytes']}",
                flush=True,
            )
    (output / "report.json").write_text(json.dumps(report, indent=2) + "\n")


if __name__ == "__main__":
    main()
