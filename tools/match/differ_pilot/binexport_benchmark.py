#!/usr/bin/env python3
"""Validate local BinExport inputs and benchmark name-blinded BinDiff mappings.

Requires the pinned BinDiff CLI, protoc-generated binexport2_pb2.py, protobuf,
and local Windows/Wii/Android exports. Never imports annotations into a database.
"""

import argparse
import hashlib
import json
import sqlite3
import struct
import subprocess
import sys
from collections import Counter, defaultdict
from pathlib import Path

from snail import match as m

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools/binja"))
from dol_loader.format import parse_header

BINDIFF_SHA = "e6ff9d1b491d2d3c1efba3d9d12217766ba7f08000a44aa917fbc3bf3868b09b"
PROTO_SHA = "e8e4943de00b37038b614bbd0515cb188caf3e4a2e20c6566544e791f93647d8"
BUILD_IDS = {
    "windows": "windows-reflexive-x86",
    "wii": "wii-usa-ppc",
    "android": "android-armv7",
}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def dump(path, value):
    path.write_text(json.dumps(value, indent=2) + "\n")


def segment_reader(blob, regions, bias=0):
    def read(address, size):
        address -= bias
        for start, offset, length in regions:
            if start <= address and address + size <= start + length:
                return blob[offset + address - start : offset + address - start + size]
        raise ValueError(
            f"Export instruction outside file-backed regions: {address:#x}"
        )

    return read


def load_input(name, path, builds, pb):
    raw = path.read_bytes()
    export = pb.BinExport2.FromString(raw)
    build = builds[BUILD_IDS[name]]
    binary_path = ROOT / build["binary"]["path"]
    binary = binary_path.read_bytes()
    if sha(binary) != build["binary"]["sha256"]:
        raise ValueError(f"{name}: unexpected source binary hash")
    bias = 0
    bias_evidence = {}
    if name == "windows":
        image = m.load_image(binary_path, 0x400000)
        read = lambda address, size: image.function_bytes(address, address + size)
    elif name == "wii":
        layout = parse_header(binary[:256], len(binary))
        read = segment_reader(
            binary, [(s.address, s.offset, s.size) for s in layout.sections]
        )
    else:
        symbols = json.loads((ROOT / build["symbol_index"]).read_text())
        if symbols["binary_sha256"] != sha(binary):
            raise ValueError("Android symbol index is stale")
        native = {f["mangled"]: int(f["address"], 16) for f in symbols["functions"]}
        offsets = Counter(
            v.address - native[v.mangled_name]
            for v in export.call_graph.vertex
            if v.mangled_name in native
        )
        if len(offsets) != 1:
            raise ValueError(f"Inconsistent Android analysis address bias: {offsets}")
        bias = next(iter(offsets))
        bias_evidence = {"bias": bias, "symbol_pairs": sum(offsets.values())}
        if binary[:6] != b"\x7fELF\x01\x01":
            raise ValueError("Expected ELF32 little-endian")
        phoff = struct.unpack_from("<I", binary, 28)[0]
        entsize, count = struct.unpack_from("<HH", binary, 42)
        regions = []
        for i in range(count):
            kind, offset, address, _, filesz, _, _, _ = struct.unpack_from(
                "<8I", binary, phoff + i * entsize
            )
            if kind == 1:
                regions.append((address, offset, filesz))
        read = segment_reader(binary, regions, bias)
    address = 0
    checked_bytes = 0
    empty = 0
    for instruction in export.instruction:
        if instruction.HasField("address"):
            address = instruction.address
        data = instruction.raw_bytes
        if data:
            if read(address, len(data)) != data:
                raise ValueError(f"{name}: exported bytes differ at {address:#x}")
            checked_bytes += len(data)
        else:
            empty += 1
        address += len(data)
    # The current BN exporter stores operands structurally, with no symbolic
    # expression names. Refuse a future exporter that could leak those names.
    if any(e.type == pb.BinExport2.Expression.SYMBOL for e in export.expression):
        raise ValueError("Unblinded symbolic expressions require an explicit policy")
    receipt = {
        "export_sha256": sha(raw),
        "binary": str(binary_path.relative_to(ROOT)),
        "binary_sha256": sha(binary),
        "exported_executable_id": export.meta_information.executable_id,
        "architecture": export.meta_information.architecture_name,
        "vertices": len(export.call_graph.vertex),
        "flow_graphs": len(export.flow_graph),
        "instructions": len(export.instruction),
        "checked_bytes": checked_bytes,
        "empty_instructions": empty,
        "bias_evidence": bias_evidence,
        "limitations": "Native bytes checked; function boundaries and CFG semantics remain analyzer output",
    }
    return export, receipt, bias


def blind(export, identity):
    # Preserve graph/code/strings. Remove all call-graph function names,
    # including recovered analyst names, before asking the differ to map them.
    for vertex in export.call_graph.vertex:
        vertex.ClearField("mangled_name")
        vertex.ClearField("demangled_name")
    export.meta_information.executable_id = identity
    return export.SerializeToString()


def run_diff(tool, primary, secondary, out):
    out.mkdir()
    command = [
        str(tool),
        f"--config={Path(__file__).with_name('bindiff-config.json')}",
        f"--primary={primary}",
        f"--secondary={secondary}",
        f"--output_dir={out}",
        "--output_format=bin,log",
    ]
    cp = subprocess.run(
        command, capture_output=True, text=True, check=True, timeout=120
    )
    (out / "run.log").write_text(cp.stdout + cp.stderr)
    paths = list(out.glob("*.BinDiff"))
    if len(paths) != 1:
        raise ValueError("Expected one BinDiff result database")
    with sqlite3.connect(f"file:{paths[0]}?mode=ro", uri=True) as conn:
        rows = conn.execute(
            "SELECT address1,address2,similarity,confidence FROM function"
        ).fetchall()
    return rows, {
        "command": command,
        "database_sha256": sha(paths[0].read_bytes()),
        "pairs": len(rows),
    }


def score(truth, rows, left_vertices, right_vertices):
    predictions = {row[0]: row[1:] for row in rows}
    counters = Counter()
    entries = []
    for name, source, expected in truth:
        counters["truth"] += 1
        if source not in left_vertices or not expected.intersection(right_vertices):
            counters["absent_from_export"] += 1
            entries.append(
                {
                    "name": name,
                    "source": source,
                    "expected": sorted(expected),
                    "outcome": "absent",
                }
            )
            continue
        counters["eligible"] += 1
        prediction = predictions.get(source)
        outcome = (
            "unmatched"
            if prediction is None
            else "correct"
            if prediction[0] in expected
            else "wrong"
        )
        counters[outcome] += 1
        entry = {
            "name": name,
            "source": source,
            "expected": sorted(expected),
            "outcome": outcome,
        }
        if prediction:
            entry.update(
                {
                    "predicted": prediction[0],
                    "similarity": prediction[1],
                    "confidence": prediction[2],
                }
            )
        entries.append(entry)
    thresholds = {
        str(threshold): dict(
            Counter(
                e["outcome"] for e in entries if e.get("confidence", -1) >= threshold
            )
        )
        for threshold in (0.0, 0.5, 0.9)
    }
    return {
        "counts": dict(counters),
        "confidence_thresholds": thresholds,
        "entries": entries,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--exports", type=Path, default=ROOT / "artifacts/differ-pilot")
    parser.add_argument(
        "--tools", type=Path, default=ROOT / "artifacts/differ-pilot/tools"
    )
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()
    tools, out = args.tools.resolve(), args.out.resolve()
    if (
        sha((tools / "bindiff").read_bytes()) != BINDIFF_SHA
        or sha((tools / "binexport2.proto").read_bytes()) != PROTO_SHA
    ):
        raise ValueError("Tool/schema differs from pinned benchmark")
    sys.path.insert(0, str(tools))
    import binexport2_pb2 as pb

    builds_path = ROOT / "analysis/ports/builds.json"
    builds = {b["id"]: b for b in json.loads(builds_path.read_text())["builds"]}
    out.mkdir(parents=True, exist_ok=False)
    report = {
        "script_sha256": sha(Path(__file__).read_bytes()),
        "config_sha256": sha(
            Path(__file__).with_name("bindiff-config.json").read_bytes()
        ),
        "tool_sha256": BINDIFF_SHA,
        "schema_sha256": PROTO_SHA,
        "build_manifest_sha256": sha(builds_path.read_bytes()),
        "inputs": {},
    }
    exports, biases = {}, {}
    for name in BUILD_IDS:
        export, receipt, bias = load_input(
            name, args.exports / f"{name}.BinExport", builds, pb
        )
        exports[name], biases[name] = export, bias
        blinded = blind(export, receipt["binary_sha256"])
        (out / f"{name}.BinExport").write_bytes(blinded)
        receipt["blinded_sha256"] = sha(blinded)
        report["inputs"][name] = receipt
    self_rows, self_run = run_diff(
        tools / "bindiff",
        out / "windows.BinExport",
        out / "windows.BinExport",
        out / "self",
    )
    self_run["off_diagonal_pairs"] = sum(a != b for a, b, _, _ in self_rows)
    if self_run["off_diagonal_pairs"] or len(self_rows) != len(
        exports["windows"].call_graph.vertex
    ):
        raise ValueError(
            "BinDiff self control did not recover every function at its own address"
        )
    report["self_control"] = self_run
    crosswalk_path = ROOT / "analysis/symbols/windows-mobile-gameplay-crosswalk.json"
    symbol_path = ROOT / builds["android-armv7"]["symbol_index"]
    symbols = defaultdict(set)
    for f in json.loads(symbol_path.read_text())["functions"]:
        symbols[f["demangled"]].add(int(f["address"], 16) + biases["android"])
    android_truth = [
        (e["windows_name"], int(e["address"], 16), symbols[e["android_symbol"]])
        for e in json.loads(crosswalk_path.read_text())["entries"]
        if e["status"] == "verified"
        and e.get("mapping_scope") != "interior-region"
        and e.get("android_symbol") in symbols
    ]
    relationships_path = ROOT / "analysis/ports/functions.json"
    manifest = m.load_function_symbol_manifest(m.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    wii_truth = []
    for entry in json.loads(relationships_path.read_text())["functions"]:
        for relation in entry["relationships"]:
            if relation["build_id"] == BUILD_IDS["wii"]:
                start, _ = m.resolve_function_extent(
                    manifest, entry["windows_id"], None
                )
                wii_truth.append(
                    (entry["windows_id"], start, {int(relation["address"], 16)})
                )
    report["truth_sha256"] = {
        str(p.relative_to(ROOT)): sha(p.read_bytes())
        for p in (crosswalk_path, symbol_path, relationships_path)
    }
    for name, truth in (("android", android_truth), ("wii", wii_truth)):
        rows, run = run_diff(
            tools / "bindiff",
            out / "windows.BinExport",
            out / f"{name}.BinExport",
            out / name,
        )
        evaluation = score(
            truth,
            rows,
            {v.address for v in exports["windows"].call_graph.vertex},
            {v.address for v in exports[name].call_graph.vertex},
        )
        report[name] = {"run": run, **evaluation}
        print(name, evaluation["counts"], evaluation["confidence_thresholds"])
    dump(out / "report.json", report)


if __name__ == "__main__":
    main()
