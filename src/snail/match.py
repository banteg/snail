"""Asm matching harness for the matching-islands workflow.

Compares a function compiled from a candidate C++ scratch (VC6 COFF object)
against the same function in the original game image, after normalizing
addresses and relocations away. The score is a SequenceMatcher ratio over
normalized instruction text, so struct offsets, register choice, and
instruction scheduling all count toward the match.
"""

from __future__ import annotations

from dataclasses import dataclass
import difflib
from pathlib import Path
import struct

import capstone

from .symbols import FunctionSymbolManifest

IMAGE_FILE_MACHINE_I386 = 0x14C
IMAGE_SYM_CLASS_EXTERNAL = 2
IMAGE_SYM_CLASS_STATIC = 3
IMAGE_SCN_CNT_CODE = 0x00000020
SYM_TYPE_FUNCTION = 0x20
# int3 between image functions, nop for section alignment inside objects
PADDING_BYTES = b"\xcc\x90"


@dataclass(frozen=True, slots=True)
class CoffRelocation:
    virtual_address: int
    symbol_index: int
    relocation_type: int


@dataclass(frozen=True, slots=True)
class CoffSection:
    name: str
    data: bytes
    characteristics: int
    relocations: tuple[CoffRelocation, ...]


@dataclass(frozen=True, slots=True)
class CoffSymbol:
    name: str
    value: int
    section_number: int
    symbol_type: int
    storage_class: int


@dataclass(frozen=True, slots=True)
class CoffObject:
    sections: tuple[CoffSection, ...]
    symbols: tuple[CoffSymbol, ...]


@dataclass(frozen=True, slots=True)
class ObjectFunction:
    name: str
    data: bytes
    relocation_offsets: frozenset[int]


@dataclass(frozen=True, slots=True)
class MatchResult:
    ratio: float
    target_lines: tuple[str, ...]
    candidate_lines: tuple[str, ...]

    @property
    def diff_lines(self) -> list[str]:
        return list(
            difflib.unified_diff(
                self.target_lines,
                self.candidate_lines,
                fromfile="target",
                tofile="candidate",
                lineterm="",
            )
        )


def parse_coff_object(data: bytes) -> CoffObject:
    machine, section_count, _, symtab_offset, symbol_count, optional_header_size, _ = (
        struct.unpack_from("<HHIIIHH", data, 0)
    )
    if machine != IMAGE_FILE_MACHINE_I386:
        raise ValueError(f"expected i386 COFF object, got machine 0x{machine:x}")

    string_table_offset = symtab_offset + symbol_count * 18

    def symbol_name(raw: bytes) -> str:
        if raw[:4] == b"\x00\x00\x00\x00":
            offset = string_table_offset + struct.unpack_from("<I", raw, 4)[0]
            end = data.index(b"\x00", offset)
            return data[offset:end].decode("latin1")
        return raw.rstrip(b"\x00").decode("latin1")

    symbols: list[CoffSymbol] = []
    index = 0
    while index < symbol_count:
        record = data[symtab_offset + index * 18 : symtab_offset + (index + 1) * 18]
        value, section_number, symbol_type, storage_class, aux_count = struct.unpack_from(
            "<IhHBB", record, 8
        )
        symbols.append(
            CoffSymbol(
                name=symbol_name(record[:8]),
                value=value,
                section_number=section_number,
                symbol_type=symbol_type,
                storage_class=storage_class,
            )
        )
        index += 1 + aux_count

    sections: list[CoffSection] = []
    for section_index in range(section_count):
        header_offset = 20 + optional_header_size + section_index * 40
        name_raw = data[header_offset : header_offset + 8]
        (
            _virtual_size,
            _virtual_address,
            raw_size,
            raw_offset,
            reloc_offset,
            _lines_offset,
            reloc_count,
            _line_count,
            characteristics,
        ) = struct.unpack_from("<IIIIIIHHI", data, header_offset + 8)
        relocations = tuple(
            CoffRelocation(*struct.unpack_from("<IIH", data, reloc_offset + i * 10))
            for i in range(reloc_count)
        )
        sections.append(
            CoffSection(
                name=name_raw.rstrip(b"\x00").decode("latin1"),
                data=data[raw_offset : raw_offset + raw_size],
                characteristics=characteristics,
                relocations=relocations,
            )
        )

    return CoffObject(sections=tuple(sections), symbols=tuple(symbols))


def _is_function_symbol(symbol: CoffSymbol) -> bool:
    return (
        symbol.section_number > 0
        and symbol.symbol_type & SYM_TYPE_FUNCTION != 0
        and symbol.storage_class in (IMAGE_SYM_CLASS_EXTERNAL, IMAGE_SYM_CLASS_STATIC)
    )


def _symbol_matches(symbol_name: str, wanted: str) -> bool:
    return wanted in symbol_name


def extract_object_function(obj: CoffObject, name: str | None = None) -> ObjectFunction:
    """Pull one function's bytes and relocation offsets out of a COFF object.

    The function's extent runs from its symbol value to the next function
    symbol in the same section (or the section end).
    """
    candidates = [symbol for symbol in obj.symbols if _is_function_symbol(symbol)]
    if name is not None:
        candidates = [symbol for symbol in candidates if _symbol_matches(symbol.name, name)]
    if not candidates:
        raise ValueError(f"no matching function symbol (name={name!r})")
    if len(candidates) > 1 and name is not None:
        exact = [
            symbol
            for symbol in candidates
            if symbol.name == f"_{name}"
            or symbol.name.startswith((f"?{name}@@", f"_{name}@"))
        ]
        if len(exact) == 1:
            candidates = exact
    if len(candidates) > 1:
        names = ", ".join(symbol.name for symbol in candidates)
        raise ValueError(f"ambiguous function symbol, candidates: {names}")

    target = candidates[0]
    section = obj.sections[target.section_number - 1]
    if section.characteristics & IMAGE_SCN_CNT_CODE == 0:
        raise ValueError(f"symbol {target.name!r} is not in a code section")

    siblings = sorted(
        symbol.value
        for symbol in obj.symbols
        if _is_function_symbol(symbol)
        and symbol.section_number == target.section_number
        and symbol.value > target.value
    )
    end = siblings[0] if siblings else len(section.data)
    relocation_offsets = frozenset(
        relocation.virtual_address - target.value
        for relocation in section.relocations
        if target.value <= relocation.virtual_address < end
    )
    return ObjectFunction(
        name=target.name,
        data=section.data[target.value : end].rstrip(PADDING_BYTES),
        relocation_offsets=relocation_offsets,
    )


@dataclass(frozen=True, slots=True)
class LoadedImage:
    mapped: bytes
    image_base: int
    size_of_image: int

    def function_bytes(self, start_va: int, end_va: int) -> bytes:
        data = self.mapped[start_va - self.image_base : end_va - self.image_base]
        return data.rstrip(PADDING_BYTES)


def load_image(path: Path, image_base: int) -> LoadedImage:
    import pefile

    pe = pefile.PE(data=path.read_bytes(), fast_load=True)
    return LoadedImage(
        mapped=pe.get_memory_mapped_image(ImageBase=image_base),
        image_base=image_base,
        size_of_image=pe.OPTIONAL_HEADER.SizeOfImage,
    )


def _format_memory_operand(insn, operand, masked_disp: bool) -> str:
    mem = operand.mem
    parts: list[str] = []
    if mem.base != 0:
        parts.append(insn.reg_name(mem.base))
    if mem.index != 0:
        parts.append(f"{insn.reg_name(mem.index)}*{mem.scale}")
    if masked_disp:
        parts.append("ADDR")
    elif mem.disp != 0 or not parts:
        parts.append(f"0x{mem.disp:x}" if mem.disp >= 0 else f"-0x{-mem.disp:x}")
    return f"[{'+'.join(parts)}]"


def normalize_function(
    data: bytes,
    *,
    relocation_offsets: frozenset[int] | None = None,
    address_range: tuple[int, int] | None = None,
    base_address: int = 0,
) -> tuple[str, ...]:
    """Disassemble to normalized instruction lines.

    Object side: pass relocation_offsets so reloc'd immediates/displacements
    become ADDR. Image side: pass address_range so absolute VAs inside the
    image become ADDR. Intra-function branch targets become L<offset> labels
    on both sides, so layouts compare structurally.
    """
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    relocation_offsets = relocation_offsets or frozenset()
    size = len(data)

    def is_masked_value(value: int) -> bool:
        return address_range is not None and address_range[0] <= value < address_range[1]

    lines: list[str] = []
    for insn in md.disasm(data, base_address):
        insn_offset = insn.address - base_address
        is_branch = capstone.CS_GRP_JUMP in insn.groups or capstone.CS_GRP_CALL in insn.groups
        imm_masked = any(
            insn_offset + rel_offset in relocation_offsets
            for rel_offset in range(insn.imm_offset, insn.imm_offset + max(insn.imm_size, 1))
        ) if insn.imm_offset else False
        disp_masked = any(
            insn_offset + rel_offset in relocation_offsets
            for rel_offset in range(insn.disp_offset, insn.disp_offset + max(insn.disp_size, 1))
        ) if insn.disp_offset else False

        operands: list[str] = []
        for operand in insn.operands:
            if operand.type == capstone.x86.X86_OP_REG:
                operands.append(insn.reg_name(operand.reg))
            elif operand.type == capstone.x86.X86_OP_IMM:
                value = operand.imm
                target_offset = value - base_address
                if is_branch and 0 <= target_offset < size:
                    operands.append(f"L{target_offset:x}")
                elif imm_masked or is_masked_value(value):
                    operands.append("ADDR")
                else:
                    operands.append(f"0x{value:x}" if value >= 0 else f"-0x{-value:x}")
            elif operand.type == capstone.x86.X86_OP_MEM:
                masked = disp_masked or is_masked_value(operand.mem.disp)
                operands.append(_format_memory_operand(insn, operand, masked))
            else:
                operands.append("?")
        lines.append(f"{insn.mnemonic} {', '.join(operands)}".strip())
    return tuple(lines)


def match_function(
    target_data: bytes,
    candidate: ObjectFunction,
    *,
    image: LoadedImage,
    target_va: int,
) -> MatchResult:
    target_lines = normalize_function(
        target_data,
        address_range=(image.image_base, image.image_base + image.size_of_image),
        base_address=target_va,
    )
    candidate_lines = normalize_function(
        candidate.data,
        relocation_offsets=candidate.relocation_offsets,
    )
    ratio = difflib.SequenceMatcher(a=target_lines, b=candidate_lines, autojunk=False).ratio()
    return MatchResult(
        ratio=ratio,
        target_lines=target_lines,
        candidate_lines=candidate_lines,
    )


def resolve_function_extent(
    manifest: FunctionSymbolManifest,
    function_name: str,
    end_override: int | None = None,
) -> tuple[int, int]:
    """Start VA from the manifest; end VA from the next curated function.

    The next curated function is an upper bound: uncurated functions may sit
    in between, so trim padding and pass an explicit end when the diff shows
    an unrelated tail.
    """
    by_name = {symbol.name: symbol for symbol in manifest.functions}
    if function_name not in by_name:
        raise ValueError(f"function {function_name!r} not in manifest")
    start = by_name[function_name].address
    if end_override is not None:
        return start, end_override
    following = sorted(
        symbol.address for symbol in manifest.functions if symbol.address > start
    )
    if not following:
        raise ValueError(f"no following function after {function_name!r}; pass an explicit end")
    return start, following[0]


def run_match(
    *,
    obj_path: Path,
    function_name: str,
    image_path: Path,
    manifest: FunctionSymbolManifest,
    symbol_name: str | None = None,
    end_va: int | None = None,
) -> MatchResult:
    obj = parse_coff_object(obj_path.read_bytes())
    candidate = extract_object_function(obj, symbol_name or function_name)
    start, end = resolve_function_extent(manifest, function_name, end_va)
    image = load_image(image_path, manifest.image_base)
    return match_function(
        image.function_bytes(start, end),
        candidate,
        image=image,
        target_va=start,
    )
