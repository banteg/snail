from __future__ import annotations

from collections import Counter
from dataclasses import dataclass
from datetime import UTC, datetime
import hashlib
import math
from pathlib import Path
from typing import Any

import pefile

from .archive import parse_archive_index, summarize_archive


COMMON_SIGNATURES: dict[str, bytes] = {
    "bmp": b"BM",
    "dds": b"DDS ",
    "jpeg": b"\xff\xd8\xff",
    "ogg": b"OggS",
    "png": b"\x89PNG\r\n\x1a\n",
    "riff": b"RIFF",
    "zip": b"PK\x03\x04",
    "zlib_78_9c": b"\x78\x9c",
    "zlib_78_da": b"\x78\xda",
}

PE_PREFIX = b"MZ"


@dataclass(frozen=True)
class SignatureHit:
    name: str
    offsets: list[int]


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def shannon_entropy(data: bytes) -> float:
    if not data:
        return 0.0
    size = len(data)
    entropy = 0.0
    for count in Counter(data).values():
        probability = count / size
        entropy -= probability * math.log2(probability)
    return entropy


def find_signature_offsets(
    data: bytes,
    signatures: dict[str, bytes] | None = None,
    limit: int = 8,
) -> list[SignatureHit]:
    hits: list[SignatureHit] = []
    for name, pattern in (signatures or COMMON_SIGNATURES).items():
        offsets: list[int] = []
        start = 0
        while len(offsets) < limit:
            index = data.find(pattern, start)
            if index == -1:
                break
            offsets.append(index)
            start = index + 1
        if offsets:
            hits.append(SignatureHit(name=name, offsets=offsets))
    return hits


def is_pe(data: bytes) -> bool:
    return data.startswith(PE_PREFIX)


def _machine_name(value: int) -> str:
    return pefile.MACHINE_TYPE.get(value, hex(value))


def _subsystem_name(value: int) -> str:
    return pefile.SUBSYSTEM_TYPE.get(value, str(value))


def summarize_pe(path: Path) -> dict[str, Any]:
    pe = pefile.PE(str(path), fast_load=True)
    pe.parse_data_directories(
        directories=[
            pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"],
            pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_EXPORT"],
        ]
    )

    imports: dict[str, list[str]] = {}
    for entry in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        dll_name = entry.dll.decode("ascii", errors="replace")
        imports[dll_name] = [
            imp.name.decode("ascii", errors="replace")
            for imp in entry.imports
            if imp.name is not None
        ]

    exports = [
        symbol.name.decode("ascii", errors="replace")
        for symbol in getattr(getattr(pe, "DIRECTORY_ENTRY_EXPORT", None), "symbols", [])
        if symbol.name is not None
    ]

    sections = []
    for section in pe.sections:
        sections.append(
            {
                "name": section.Name.rstrip(b"\x00").decode("ascii", errors="replace"),
                "virtual_address": section.VirtualAddress,
                "virtual_size": section.Misc_VirtualSize,
                "raw_size": section.SizeOfRawData,
                "characteristics": hex(section.Characteristics),
            }
        )

    return {
        "arch": _machine_name(pe.FILE_HEADER.Machine),
        "bits": 32 if pe.PE_TYPE == pefile.OPTIONAL_HEADER_MAGIC_PE else 64,
        "compile_time": datetime.fromtimestamp(
            pe.FILE_HEADER.TimeDateStamp, tz=UTC
        ).isoformat(),
        "entry_point": pe.OPTIONAL_HEADER.AddressOfEntryPoint,
        "image_base": pe.OPTIONAL_HEADER.ImageBase,
        "imports": imports,
        "export_count": len(exports),
        "exports_preview": exports[:25],
        "sections": sections,
        "subsystem": _subsystem_name(pe.OPTIONAL_HEADER.Subsystem),
    }


def summarize_file(path: Path, signature_limit: int = 8) -> dict[str, Any]:
    data = path.read_bytes()
    report: dict[str, Any] = {
        "path": path.as_posix(),
        "size": len(data),
        "sha256": sha256_bytes(data),
        "entropy": round(shannon_entropy(data), 4),
        "prefix_hex": data[:16].hex(" "),
    }

    signature_hits = find_signature_offsets(data, limit=signature_limit)
    if signature_hits:
        report["signature_hits"] = {
            hit.name: hit.offsets for hit in signature_hits
        }

    if is_pe(data):
        report["kind"] = "pe"
        report["pe"] = summarize_pe(path)
    else:
        report["kind"] = "blob"
        if path.name.lower() == "snailmail.dat":
            report["archive"] = summarize_archive(parse_archive_index(path))

    return report


def inspect_path(path: Path, signature_limit: int = 8) -> dict[str, Any]:
    if not path.exists():
        raise FileNotFoundError(path)

    resolved = path.resolve()
    if resolved.is_dir():
        files = sorted(child for child in resolved.rglob("*") if child.is_file())
        return {
            "path": resolved.as_posix(),
            "kind": "directory",
            "file_count": len(files),
            "files": [
                summarize_file(file_path, signature_limit=signature_limit)
                for file_path in files
            ],
        }

    return summarize_file(resolved, signature_limit=signature_limit)
