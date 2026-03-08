from __future__ import annotations

from collections import Counter
import json
from pathlib import Path

from construct import Array, Int32ul, Struct as CStruct, this
import msgspec


ARCHIVE_PROBE_SIZE = 0x7C

ARCHIVE_PROBE = CStruct(
    "entry_count" / Int32ul,
    "first_path_offset" / Int32ul,
    "index_size" / Int32ul,
)
ARCHIVE_RECORD = CStruct(
    "path_offset" / Int32ul,
    "data_offset" / Int32ul,
    "size" / Int32ul,
)
ARCHIVE_INDEX = CStruct(
    "entry_count" / Int32ul,
    "records" / Array(this.entry_count, ARCHIVE_RECORD),
)
ARCHIVE_ENTRY_SIZE = ARCHIVE_RECORD.sizeof()


class ArchiveEntry(msgspec.Struct, frozen=True):
    path: str
    data_offset: int
    size: int


class ArchiveIndex(msgspec.Struct, frozen=True):
    source: Path
    entry_count: int
    index_size: int
    entries: tuple[ArchiveEntry, ...]

    def extension_counts(self) -> dict[str, int]:
        counts = Counter(Path(entry.path).suffix.lower() or "<none>" for entry in self.entries)
        return dict(sorted(counts.items(), key=lambda item: (-item[1], item[0])))

    def root_counts(self) -> dict[str, int]:
        counts = Counter(entry.path.split("/", 1)[0] for entry in self.entries)
        return dict(sorted(counts.items(), key=lambda item: (-item[1], item[0])))

    def entries_preview(self, limit: int = 20) -> list[dict[str, int | str]]:
        return [
            {
                "path": entry.path,
                "data_offset": entry.data_offset,
                "size": entry.size,
            }
            for entry in self.entries[:limit]
        ]

    def entry_by_path(self, path: str) -> ArchiveEntry:
        normalized = path.upper()
        for entry in self.entries:
            if entry.path.upper() == normalized:
                return entry
        raise KeyError(path)


def xor_mask(index: int) -> int:
    return ((index * index) & 0xFF) ^ ((index * 3) & 0xFF)


def xor_decode_in_place(buffer: bytearray, start_offset: int = 0) -> None:
    for offset, value in enumerate(buffer, start=start_offset):
        buffer[offset - start_offset] = value ^ xor_mask(offset)


def decode_bytes(data: bytes, start_offset: int = 0) -> bytes:
    buffer = bytearray(data)
    xor_decode_in_place(buffer, start_offset=start_offset)
    return bytes(buffer)


def _read_c_string(blob: bytes, offset: int) -> str:
    terminator = blob.find(b"\x00", offset)
    if terminator == -1:
        raise ValueError(f"Missing string terminator at archive offset {offset}")
    return blob[offset:terminator].decode("ascii")


def parse_archive_index(path: Path) -> ArchiveIndex:
    with path.open("rb") as handle:
        probe = bytearray(handle.read(ARCHIVE_PROBE_SIZE))
        if len(probe) < 12:
            raise ValueError(f"{path} is too small to be a Snail Mail archive")
        xor_decode_in_place(probe)

        probe_data = ARCHIVE_PROBE.parse(probe[: ARCHIVE_PROBE.sizeof()])
        entry_count = int(probe_data.entry_count)
        index_size = int(probe_data.index_size)
        minimum_size = 4 + entry_count * ARCHIVE_ENTRY_SIZE
        if entry_count == 0 or index_size < minimum_size:
            raise ValueError(f"{path} does not look like a valid Snail Mail archive")

        handle.seek(0)
        index_blob = bytearray(handle.read(index_size))
        if len(index_blob) != index_size:
            raise ValueError(f"{path} ended before the decoded index was fully read")
        xor_decode_in_place(index_blob)

    parsed_index = ARCHIVE_INDEX.parse(index_blob)
    entries: list[ArchiveEntry] = []
    for record in parsed_index.records:
        entries.append(
            ArchiveEntry(
                path=_read_c_string(index_blob, int(record.path_offset)),
                data_offset=int(record.data_offset),
                size=int(record.size),
            )
        )

    return ArchiveIndex(
        source=path.resolve(),
        entry_count=entry_count,
        index_size=index_size,
        entries=tuple(entries),
    )


def summarize_archive(index: ArchiveIndex, preview_limit: int = 20) -> dict[str, object]:
    return {
        "entry_count": index.entry_count,
        "index_size": index.index_size,
        "extensions": index.extension_counts(),
        "roots": index.root_counts(),
        "entries_preview": index.entries_preview(limit=preview_limit),
    }


def read_archive_entry(path: Path, entry: ArchiveEntry) -> bytes:
    with path.open("rb") as handle:
        handle.seek(entry.data_offset)
        data = bytearray(handle.read(entry.size))
        if len(data) != entry.size:
            raise ValueError(f"{entry.path} ended early inside {path}")
    xor_decode_in_place(data, start_offset=entry.data_offset)
    return bytes(data)


def extract_archive(
    archive_path: Path,
    output_dir: Path,
    prefix: str | None = None,
) -> dict[str, object]:
    index = parse_archive_index(archive_path)
    output_dir.mkdir(parents=True, exist_ok=True)

    normalized_prefix = prefix.upper() if prefix else None
    written_files = 0
    written_bytes = 0

    for entry in index.entries:
        if normalized_prefix is not None and not entry.path.upper().startswith(normalized_prefix):
            continue

        decoded = read_archive_entry(archive_path, entry)
        destination = output_dir / entry.path
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(decoded)
        written_files += 1
        written_bytes += len(decoded)

    manifest = summarize_archive(index)
    manifest["archive_path"] = archive_path.resolve().as_posix()
    manifest["output_dir"] = output_dir.resolve().as_posix()
    manifest["prefix"] = prefix
    manifest["written_files"] = written_files
    manifest["written_bytes"] = written_bytes

    manifest_path = output_dir / "manifest.json"
    manifest_path.write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    return manifest
