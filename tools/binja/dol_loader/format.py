"""Validated DOL memory layout, independent of Binary Ninja.

The format has no magic. Detection therefore checks every populated slot,
backing-file bounds, memory ranges, overlaps, and the executable entry point.
We map exactly the declared sizes, not the apploader's rounded DMA transfers.
"""

import struct
from dataclasses import dataclass
from itertools import pairwise

HEADER_SIZE = 0x100
# Cached and uncached aliases of GameCube/Wii MEM1 and Wii MEM2.
MEMORY_RANGES = (
    (0x80000000, 0x81800000),
    (0x90000000, 0x94000000),
    (0xC0000000, 0xC1800000),
    (0xD0000000, 0xD4000000),
)


class InvalidDOL(ValueError):
    """The file cannot be safely interpreted as a supported Nintendo DOL."""


@dataclass(frozen=True)
class Section:
    name: str
    address: int
    size: int
    offset: int | None = None
    executable: bool = False

    @property
    def end(self) -> int:
        return self.address + self.size


@dataclass(frozen=True)
class Layout:
    sections: tuple[Section, ...]
    bss: tuple[Section, ...]
    entry_point: int
    bss_address: int
    bss_size: int


def _check_memory(address: int, size: int, name: str) -> None:
    if not any(lo <= address < address + size <= hi for lo, hi in MEMORY_RANGES):
        raise InvalidDOL(f"{name}: extent outside supported MEM1/MEM2 ranges")


def _check_disjoint(ranges: list[tuple[int, int, str]], kind: str) -> None:
    ordered = sorted(ranges)
    for (_, end, left), (start, _, right) in pairwise(ordered):
        if end > start:
            raise InvalidDOL(f"{left} overlaps {right} in {kind}")


def parse_header(header: bytes, file_size: int) -> Layout:
    """Parse only the 256-byte header; never allocate from untrusted sizes.

    Empty slots are identified by size and do not terminate the table. BSS is
    a broad extent in some retail files, containing initialized small data;
    only the uncovered intervals become zero-filled segments.
    """
    if len(header) < HEADER_SIZE or not HEADER_SIZE <= file_size <= 0xFFFFFFFF:
        raise InvalidDOL("truncated header or unsupported file size")
    words = struct.unpack_from(">57I", header)
    sections = []
    for kind, count, offsets, addresses, sizes in (
        ("text", 7, 0, 18, 36),
        ("data", 11, 7, 25, 43),
    ):
        for index in range(count):
            size = words[sizes + index]
            if not size:
                continue
            offset, address = words[offsets + index], words[addresses + index]
            name = f".{kind}{index}"
            if offset < HEADER_SIZE or offset + size > file_size:
                raise InvalidDOL(f"{name}: backing bytes outside file payload")
            _check_memory(address, size, name)
            executable = kind == "text"
            if executable and (address % 4 or size % 4):
                raise InvalidDOL(f"{name}: unaligned PowerPC instructions")
            sections.append(Section(name, address, size, offset, executable))

    entry_point = words[56]
    if entry_point % 4 or not any(
        s.executable and s.address <= entry_point < s.end for s in sections
    ):
        raise InvalidDOL("entry point is not an aligned instruction in a text section")
    _check_disjoint([(s.address, s.end, s.name) for s in sections], "memory")
    _check_disjoint([(s.offset, s.offset + s.size, s.name) for s in sections], "file")

    bss_address, bss_size = words[54:56]
    bss = []
    if bss_size:
        _check_memory(bss_address, bss_size, "BSS")
        cursor, end = bss_address, bss_address + bss_size
        for section in sorted(sections, key=lambda s: s.address):
            if section.end <= cursor:
                continue
            if section.address >= end:
                break
            if cursor < section.address:
                bss.append(Section(f".bss{len(bss)}", cursor, section.address - cursor))
            cursor = min(end, section.end)
            if cursor == end:
                break
        if cursor < end:
            bss.append(Section(f".bss{len(bss)}", cursor, end - cursor))
    return Layout(tuple(sections), tuple(bss), entry_point, bss_address, bss_size)
