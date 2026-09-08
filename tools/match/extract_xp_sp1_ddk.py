#!/usr/bin/env python3
"""Extract the pinned XP SP1 DDK compiler without running its installer."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import tempfile
from pathlib import Path

import pefile

ROOT = Path(__file__).resolve().parents[2]
ARCHIVE_URL = (
    "https://github.com/KunYi/WDK_DDKArchive/releases/download/DDK_5.1.2600.1106/"
    "Microsoft.Windows.XP.DDK.5.1.2600.1106.7z"
)
ARCHIVE_SHA256 = "32ff9a3936911f5ba6a2edc77eb7dc2ccf01b09eb79c86ab6a72ee6fbd438bee"
COMPONENTS = {
    "CL.EXE": "a99939878f19e0a6404e349824c163de8188a967a22e82867af935c040d1032c",
    "C1.DLL": "bb7ffe0357f4fca0d0607ac9f8a2b2df3dacbf1cf821eb502e1e5a323e5c66dd",
    "C1XX.DLL": "3a0cdfbccb2df87487da1d6c9e83ce781f7ef4eae025da35ec405cfebe7831a4",
    "C2.DLL": "99860f0499e637520df383ffac0845cf027cbecb82c9980844c76e1698579add",
    "MSPDB70.DLL": "636c6d5a7a57664796adc835203b905f98f4f3c64d8a4107d4e68efbe33b6795",
    "MSVCR70.DLL": "c0116e144dfe70bdc4b617240029c182875461d15de2ec5d79a9b1b94980b259",
}
BINARIES = set(COMPONENTS) | {"LINK.EXE", "LIB.EXE", "CVTRES.EXE", "MSOBJ10.DLL"}


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def run(*argv: str) -> None:
    subprocess.run(argv, check=True, capture_output=True, text=True)


def file_version(data: bytes) -> str:
    pe = pefile.PE(data=data)
    value = pe.VS_FIXEDFILEINFO[0]
    return ".".join(
        str(part)
        for word in (value.FileVersionMS, value.FileVersionLS)
        for part in (word >> 16, word & 0xFFFF)
    )


def extract(archive: Path, output: Path) -> dict:
    if sha256(archive.read_bytes()) != ARCHIVE_SHA256:
        raise ValueError("archive does not match the pinned XP SP1 DDK package")
    files: dict[str, bytes] = {}
    with tempfile.TemporaryDirectory(prefix="snail-ddk-") as temporary:
        temp = Path(temporary)
        run("7z", "x", "-y", f"-o{temp}", str(archive))
        iso = temp / "Microsoft Windows XP DDK (5.1.2600.1106)/winxp_ddk.2600.1106.iso"
        iso_sha256 = sha256(iso.read_bytes())
        cabinets = ("X86DBINS", "SDKINCS1", "SDKINCS2", "SDKINCS3")
        run(
            "7z",
            "x",
            "-y",
            f"-o{temp / 'media'}",
            str(iso),
            *(
                f"COMMON/{name}.{suffix}"
                for name in cabinets
                for suffix in ("CAB", "INF")
            ),
        )
        for name in cabinets:
            run(
                "cabextract",
                "-q",
                "-d",
                str(temp / "files"),
                str(temp / f"media/COMMON/{name}.CAB"),
            )
            inf = (temp / f"media/COMMON/{name}.INF").read_text()
            destinations = dict(
                re.findall(r'^(Files_\d+)=49000,"([^"\n]+)"', inf, re.MULTILINE)
            )
            for section, body in re.findall(
                r"\[(Files_\d+)\]\n(.*?)(?=\n\[|\Z)", inf, re.DOTALL
            ):
                destination = destinations[section]
                for filename, member in re.findall(
                    r"^([^,\n]+),([A-Za-z0-9_]+),,", body, re.MULTILINE
                ):
                    if name == "X86DBINS" and filename.upper() in BINARIES:
                        relative = f"Bin/{filename.upper()}"
                    elif destination.startswith("\\inc\\crt\\"):
                        tail = destination.removeprefix("\\inc\\crt\\").replace(
                            "\\", "/"
                        )
                        relative = f"Include/{tail}{filename}"
                    else:
                        continue
                    files[relative] = (temp / "files" / member).read_bytes()

    for name, expected in COMPONENTS.items():
        if sha256(files[f"Bin/{name}"]) != expected:
            raise ValueError(f"unexpected compiler component: {name}")
    if any(
        (output / name).exists() and (output / name).read_bytes() != data
        for name, data in files.items()
    ):
        raise ValueError(
            "output contains different files; choose a new output directory"
        )

    receipt = {
        "schema": 1,
        "source_url": ARCHIVE_URL,
        "archive_sha256": ARCHIVE_SHA256,
        "iso_sha256": iso_sha256,
        "files": {
            name: {
                "sha256": sha256(data),
                "size": len(data),
                **(
                    {"file_version": file_version(data)}
                    if name in {f"Bin/{component}" for component in COMPONENTS}
                    else {}
                ),
            }
            for name, data in sorted(files.items())
        },
    }
    for name, data in files.items():
        destination = output / name
        if not destination.exists():
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_bytes(data)
    (output / "provenance.json").write_text(json.dumps(receipt, indent=2) + "\n")
    return receipt


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("archive", type=Path)
    parser.add_argument(
        "--output", type=Path, default=ROOT / "tools/match/compilers/msvc7.0-ddk9178"
    )
    args = parser.parse_args()
    receipt = extract(args.archive.resolve(), args.output.resolve())
    print(f"Verified {len(receipt['files'])} files in {args.output}")


if __name__ == "__main__":
    main()
