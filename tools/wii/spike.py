#!/usr/bin/env python3
"""Reproduce the bounded dtk/m2c Wii spike using pinned, locally staged tools."""

import argparse
import hashlib
import json
import re
import subprocess
import sys
import tarfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/binja"))
from dol_loader.format import parse_header

DOL_SHA = "523f848f2a0b8ef8c9dfe2714744bf0479a4feec79b25f0d1f5e035a6487c096"
DTK_SHA = "5ba1fd76adf937847277a1ebe2238b698df0020c3dbbde23ecb126f00fb10353"
M2C_REV = "1d1c4454a445326541305f83f2b0cb680a9ecb2d"
M2C_ARCHIVE_SHA = "dee566508729227925c0941cfcc6139ae8a0900640793f4706388946b7d76340"
TARGETS = {
    0x800092E0: 0x24,
    0x8000A968: 0x300,
    0x800444E8: 0x5B0,
    0x80052A00: 0x360,
    0x80075CC8: 0x5BC,
}
LINE = re.compile(
    r"/\* ([0-9A-F]{8}) [0-9A-F]{8}  ((?:[0-9A-F]{2} ){3}[0-9A-F]{2}) \*/\s*(.*)"
)


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def normalize_cror(text: str) -> tuple[str, list[str]]:
    """Convert only the observed cr0 spelling, checked against encoded operands."""
    changed = []
    output = []
    for line in text.splitlines(keepends=True):
        if "cror eq, gt, eq" in line:
            match = LINE.match(line)
            if match is None or bytes.fromhex(match[2]) != bytes.fromhex("4c411382"):
                raise ValueError("cror annotation does not encode cror 2, 1, 2")
            changed.append("0x" + match[1])
            line = line.replace("cror eq, gt, eq", "cror 2, 1, 2")
        output.append(line)
    return "".join(output), changed


def run(command: list[str], stem: Path) -> subprocess.CompletedProcess:
    completed = subprocess.run(
        command, cwd=ROOT, capture_output=True, text=True, check=False
    )
    stem.with_suffix(".stdout").write_text(completed.stdout)
    stem.with_suffix(".stderr").write_text(completed.stderr)
    return completed


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", type=Path, required=True, help="New output directory")
    parser.add_argument(
        "--tools", type=Path, default=ROOT / "artifacts/wii/spike-20260910/tools"
    )
    args = parser.parse_args()
    out, tools = args.out.resolve(), args.tools.resolve()
    if out.exists():
        raise ValueError("Use a new --out directory to preserve prior evidence")
    dtk, archive = tools / "dtk", tools / "m2c.tar.gz"
    m2c_root = tools / f"m2c-{M2C_REV}"
    if sha(dtk.read_bytes()) != DTK_SHA or sha(archive.read_bytes()) != M2C_ARCHIVE_SHA:
        raise ValueError("Staged tool hash differs from pinned spike")
    # Check the extracted source against the pinned archive; caches are ignored.
    with tarfile.open(archive) as tar:
        for member in tar:
            if member.isfile():
                relative = Path(member.name).relative_to(f"m2c-{M2C_REV}")
                if (m2c_root / relative).read_bytes() != tar.extractfile(member).read():
                    raise ValueError(f"m2c source drift: {relative}")
    dol = ROOT / "artifacts/wii/reference/SnailMail-USA.dol"
    blob = dol.read_bytes()
    if sha(blob) != DOL_SHA:
        raise ValueError("Unexpected Wii DOL")
    layout = parse_header(blob[:256], len(blob))

    def read(address: int, size: int) -> bytes:
        for section in layout.sections:
            if section.address <= address and address + size <= section.end:
                offset = section.offset + address - section.address
                return blob[offset : offset + size]
        raise ValueError(f"Unmapped address: {address:x}")

    out.mkdir(parents=True)
    version = subprocess.check_output([str(dtk), "--version"], text=True).strip()
    info = run([str(dtk), "dol", "info", str(dol)], out / "dtk-info")
    info.check_returncode()
    config = out / "config.yml"
    config.write_text(
        f"object: {json.dumps(str(dol))}\nhash: {hashlib.sha1(blob).hexdigest()}\n"
        f"symbols: {json.dumps(str(out / 'symbols.txt'))}\n"
        f"splits: {json.dumps(str(out / 'splits.txt'))}\n"
        "write_asm: true\ndetect_objects: true\ndetect_strings: true\n"
    )
    split = run(
        [str(dtk), "dol", "split", str(config), str(out / "split")], out / "dtk-split"
    )
    split.check_returncode()
    results = []

    def decompile(name: str, assembly: str, extra: list[str] | None = None) -> dict:
        source = out / f"{name}.s"
        source.write_text(assembly)
        command = [
            "uv",
            "run",
            "--no-project",
            str(m2c_root / "m2c.py"),
            "-t",
            "ppc-mwcc-c++",
        ]
        command += extra or []
        command.append(str(source))
        result = run(command, out / name)
        (out / f"{name}.c").write_text(result.stdout)
        return {
            "name": name,
            "command": command,
            "exit_code": result.returncode,
            "m2c_errors": result.stdout.count("M2C_ERROR"),
            "input_sha256": sha(assembly.encode()),
            "output_sha256": sha(result.stdout.encode()),
            "stderr": result.stderr,
        }

    for address, size in TARGETS.items():
        original = (out / f"split/asm/auto_fn_{address:08X}_text.s").read_text()
        instruction_rows = [
            m for line in original.splitlines() if (m := LINE.match(line))
        ]
        addresses = [int(m[1], 16) for m in instruction_rows]
        if addresses != list(range(address, address + size, 4)):
            raise ValueError(f"Unexpected annotated instruction range: {address:x}")
        for match in instruction_rows:
            if bytes.fromhex(match[2]) != read(int(match[1], 16), 4):
                raise ValueError(
                    f"Assembly byte annotation differs from DOL: {match[1]}"
                )
        normalized, changes = normalize_cror(original)
        raw = decompile(f"{address:08x}-raw", original)
        adapted = decompile(f"{address:08x}-adapted", normalized, ["--no-switches"])
        results.append(
            {
                "address": hex(address),
                "size": size,
                "verified_instruction_annotations": len(addresses),
                "cror_alias_addresses": changes,
                "raw": raw,
                "adapted": adapted,
            }
        )

    helper_source = (out / "80052a00-adapted.s").read_text()
    helper_control = re.sub(
        r"\b(_(?:save|rest)(?:gpr|fpr)_\d+)\b", r"unrecognized\1", helper_source
    )
    helper = decompile("helper-control", helper_control)
    paired = decompile(
        "paired-body-control",
        """.text
.global paired_load_probe
paired_load_probe:
    psq_l f1, 0(r3), 0, 0
    stfs f1, 0(r4)
    blr
.global paired_store_probe
paired_store_probe:
    psq_st f1, 0(r3), 0, 0
    blr
""",
    )
    symbol_lines = (out / "symbols.txt").read_text().splitlines()
    report = {
        "dol_sha256": DOL_SHA,
        "dtk_version": version,
        "dtk_sha256": DTK_SHA,
        "m2c_revision": M2C_REV,
        "m2c_archive_sha256": M2C_ARCHIVE_SHA,
        "m2c_source_verified_against_archive": True,
        "dtk_function_symbols": sum("type:function" in line for line in symbol_lines),
        "dtk_symbol_rows": len(symbol_lines),
        "samples": results,
        "helper_name_control": helper,
        "paired_body_control": paired,
        "limits": [
            "Byte annotations checked; split objects not relinked",
            "No compiler matching or runtime equivalence claim",
            "Exit zero and absence of M2C_ERROR do not establish semantic completeness",
        ],
    }
    (out / "report.json").write_text(json.dumps(report, indent=2) + "\n")
    print(
        json.dumps(
            {"report": str(out / "report.json"), "samples": len(results)}, indent=2
        )
    )


if __name__ == "__main__":
    main()
