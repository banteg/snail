"""Map code offsets in a linked WebAssembly module to source lines.

V8 reports a trap as `wasm-function[N]:0xOFFSET`, a byte offset into the
module. DWARF line programs in wasm address code relative to the start of the
code section's payload. This module reads the debug sections the linker keeps
as custom sections and annotates such stack traces with `file:line`.
"""

import io
import re
from bisect import bisect_right
from dataclasses import dataclass
from pathlib import Path

from elftools.dwarf.dwarfinfo import DebugSectionDescriptor, DwarfConfig, DWARFInfo

SECTION_CUSTOM, SECTION_CODE = 0, 10
DEBUG_SECTIONS = (
    "debug_info", "debug_aranges", "debug_abbrev", "debug_str", "debug_loc", "debug_ranges",
    "debug_line", "debug_pubtypes", "debug_pubnames", "debug_addr", "debug_str_offsets",
    "debug_line_str", "debug_loclists", "debug_rnglists",
)  # fmt: skip
FRAME_OFFSET = re.compile(r"wasm-function\[\d+\]:(0x[0-9a-f]+)")


@dataclass(frozen=True)
class LineRow:
    address: int  # relative to the code section payload
    path: str
    line: int


def _uleb(data: bytes, pos: int) -> tuple[int, int]:
    result = shift = 0
    while True:
        byte = data[pos]
        pos += 1
        result |= (byte & 0x7F) << shift
        shift += 7
        if byte < 0x80:
            return result, pos


def read_sections(data: bytes) -> tuple[int, dict[str, bytes]]:
    """The code section payload's module offset and the custom sections by name."""
    pos, code, custom = 8, None, {}
    while pos < len(data):
        size, start = _uleb(data, pos + 1)
        if data[pos] == SECTION_CODE:
            code = start
        elif data[pos] == SECTION_CUSTOM:
            length, name_start = _uleb(data, start)
            custom[data[name_start : name_start + length].decode()] = data[name_start + length : start + size]
        pos = start + size
    if code is None:
        raise ValueError("module has no code section")
    return code, custom


class LineTable:
    def __init__(self, path: Path):
        self.code_offset, custom = read_sections(Path(path).read_bytes())
        if ".debug_line" not in custom:
            raise ValueError(f"{path} has no DWARF line table; build without stripping debug info")

        def section(name: str):
            raw = custom.get(f".{name}")
            return raw and DebugSectionDescriptor(io.BytesIO(raw), f".{name}", None, len(raw), 0)

        dwarf = DWARFInfo(
            config=DwarfConfig(little_endian=True, machine_arch="wasm", default_address_size=4),
            **{f"{name}_sec": section(name) for name in DEBUG_SECTIONS},
            debug_frame_sec=None, eh_frame_sec=None, debug_sup_sec=None, gnu_debugaltlink_sec=None,
            debug_types_sec=None,
        )  # fmt: skip
        rows: list[LineRow] = []
        for unit in dwarf.iter_CUs():
            program = dwarf.line_program_for_CU(unit)
            if program is None:
                continue
            files = program["file_entry"]
            first_file = 0 if program.header.version >= 5 else 1
            for entry in program.get_entries():
                state = entry.state
                if state is None:
                    continue
                path = "" if state.end_sequence else files[state.file - first_file].name.decode()
                rows.append(LineRow(state.address, path, state.line))
        # A sequence's end and the next sequence's start can share an address.
        rows.sort(key=lambda row: (row.address, row.path != ""))
        self.rows = rows
        self.addresses = [row.address for row in rows]

    def lookup(self, module_offset: int) -> LineRow | None:
        """The row covering a module byte offset, as V8 prints it."""
        index = bisect_right(self.addresses, module_offset - self.code_offset) - 1
        if index < 0 or not self.rows[index].path:
            return None
        return self.rows[index]


def annotate(text: str, table: LineTable) -> str:
    """Append `file:line` to every wasm frame of a stack trace."""

    def frame(match: re.Match) -> str:
        row = table.lookup(int(match.group(1), 16))
        return f"{match.group(0)} [{row.path}:{row.line}]" if row else match.group(0)

    return FRAME_OFFSET.sub(frame, text)
