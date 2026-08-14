from __future__ import annotations

import hashlib
import math
from collections import Counter
from datetime import UTC, datetime
from pathlib import Path
from typing import Any

import msgspec
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
RICH_DANS = 0x536E6144
RICH_MARKER = b"Rich"
UINT32_MASK = 0xFFFFFFFF


class SignatureHit(msgspec.Struct, frozen=True):
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


def _rotate_left_32(value: int, count: int) -> int:
    count &= 31
    value &= UINT32_MASK
    return ((value << count) | (value >> ((32 - count) & 31))) & UINT32_MASK


def summarize_rich_header(
    data: bytes,
    nt_header_offset: int,
) -> dict[str, Any] | None:
    """Return ordered, interpretation-free Rich-header evidence."""
    search_end = min(nt_header_offset, len(data))
    rich_offset = None
    start_offset = None
    xor_key = None
    for candidate in range(0x40, search_end - 7, 4):
        if data[candidate : candidate + 4] != RICH_MARKER:
            continue
        candidate_key = int.from_bytes(data[candidate + 4 : candidate + 8], "little")
        masked_dans = RICH_DANS ^ candidate_key
        for offset in range(candidate - 4, 0x3F, -4):
            if int.from_bytes(data[offset : offset + 4], "little") != masked_dans:
                continue
            rich_offset = candidate
            xor_key = candidate_key
            start_offset = offset
            break
        if start_offset is not None:
            break
    if rich_offset is None or start_offset is None or xor_key is None:
        return None

    payload_start = start_offset + 16
    payload_size = rich_offset - payload_start
    padding = data[start_offset + 4 : payload_start]
    expected_padding = xor_key.to_bytes(4, "little") * 3
    structure_valid = payload_size >= 0 and payload_size % 8 == 0
    structure_valid = structure_valid and padding == expected_padding

    entries: list[dict[str, int | str]] = []
    checksum_entries: list[tuple[int, int]] = []
    if payload_size >= 0:
        for offset in range(payload_start, rich_offset - 7, 8):
            component_id = int.from_bytes(data[offset : offset + 4], "little") ^ xor_key
            count = int.from_bytes(data[offset + 4 : offset + 8], "little") ^ xor_key
            checksum_entries.append((component_id, count))
            entries.append(
                {
                    "component_id": f"0x{component_id:08x}",
                    "product_id": component_id >> 16,
                    "build": component_id & 0xFFFF,
                    "count": count,
                }
            )

    # link.exe seeds the key with the Rich offset, rotates each pre-Rich DOS
    # byte by its file offset while skipping e_lfanew, then adds each component
    # ID rotated by its contribution count.
    calculated_checksum = start_offset
    for offset, value in enumerate(data[:start_offset]):
        if 0x3C <= offset < 0x40:
            continue
        calculated_checksum += _rotate_left_32(value, offset)
    for component_id, count in checksum_entries:
        calculated_checksum += _rotate_left_32(component_id, count)
    calculated_checksum &= UINT32_MASK

    clear_header = bytearray()
    key_bytes = xor_key.to_bytes(4, "little")
    for offset, value in enumerate(data[start_offset:rich_offset]):
        clear_header.append(value ^ key_bytes[offset % 4])

    return {
        "offset_start": start_offset,
        "offset_end": rich_offset + 8,
        "size": rich_offset + 8 - start_offset,
        "xor_key": f"0x{xor_key:08x}",
        "calculated_checksum": f"0x{calculated_checksum:08x}",
        "checksum_valid": structure_valid and calculated_checksum == xor_key,
        "structure_valid": structure_valid,
        "clear_header_sha256": sha256_bytes(bytes(clear_header)),
        "entry_count": len(entries),
        "entries": entries,
    }


def summarize_pe(path: Path, data: bytes | None = None) -> dict[str, Any]:
    image = data if data is not None else path.read_bytes()
    pe = pefile.PE(data=image, fast_load=True)
    pe.parse_data_directories(
        directories=[
            pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"],
            pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_EXPORT"],
        ]
    )

    imports: dict[str, list[str]] = {}
    import_counts: dict[str, dict[str, int]] = {}
    for entry in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        dll_name = entry.dll.decode("ascii", errors="replace")
        imports[dll_name] = [
            imp.name.decode("ascii", errors="replace")
            for imp in entry.imports
            if imp.name is not None
        ]
        named_count = sum(imp.name is not None for imp in entry.imports)
        import_counts[dll_name] = {
            "total": len(entry.imports),
            "named": named_count,
            "ordinal": len(entry.imports) - named_count,
        }

    exports = [
        symbol.name.decode("ascii", errors="replace")
        for symbol in getattr(
            getattr(pe, "DIRECTORY_ENTRY_EXPORT", None), "symbols", []
        )
        if symbol.name is not None
    ]

    sections = []
    for section in pe.sections:
        sections.append(
            {
                "name": section.Name.rstrip(b"\x00").decode("ascii", errors="replace"),
                "virtual_address": section.VirtualAddress,
                "virtual_size": section.Misc_VirtualSize,
                "raw_offset": section.PointerToRawData,
                "raw_size": section.SizeOfRawData,
                "characteristics": hex(section.Characteristics),
            }
        )

    data_directories = {}
    directory_names = {
        value: name.removeprefix("IMAGE_DIRECTORY_ENTRY_").lower()
        for name, value in pefile.DIRECTORY_ENTRY.items()
        if isinstance(name, str)
    }
    for index, directory in enumerate(pe.OPTIONAL_HEADER.DATA_DIRECTORY):
        name = directory_names.get(index, f"directory_{index}")
        data_directories[name] = {
            "virtual_address": directory.VirtualAddress,
            "size": directory.Size,
        }

    report: dict[str, Any] = {
        "arch": _machine_name(pe.FILE_HEADER.Machine),
        "bits": 32 if pe.PE_TYPE == pefile.OPTIONAL_HEADER_MAGIC_PE else 64,
        "coff_timestamp": {
            "raw": pe.FILE_HEADER.TimeDateStamp,
            "utc": datetime.fromtimestamp(
                pe.FILE_HEADER.TimeDateStamp, tz=UTC
            ).isoformat(),
        },
        "coff_characteristics": hex(pe.FILE_HEADER.Characteristics),
        "linker_version": {
            "major": pe.OPTIONAL_HEADER.MajorLinkerVersion,
            "minor": pe.OPTIONAL_HEADER.MinorLinkerVersion,
        },
        "entry_point": pe.OPTIONAL_HEADER.AddressOfEntryPoint,
        "image_base": pe.OPTIONAL_HEADER.ImageBase,
        "section_alignment": pe.OPTIONAL_HEADER.SectionAlignment,
        "file_alignment": pe.OPTIONAL_HEADER.FileAlignment,
        "imports": imports,
        "import_counts": import_counts,
        "export_count": len(exports),
        "exports_preview": exports[:25],
        "sections": sections,
        "data_directories": data_directories,
        "subsystem": _subsystem_name(pe.OPTIONAL_HEADER.Subsystem),
    }
    rich_header = summarize_rich_header(image, pe.DOS_HEADER.e_lfanew)
    if rich_header is not None:
        report["rich_header"] = rich_header
    return report


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
        report["signature_hits"] = {hit.name: hit.offsets for hit in signature_hits}

    if is_pe(data):
        report["kind"] = "pe"
        report["pe"] = summarize_pe(path, data=data)
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
