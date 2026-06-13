"""Asm matching harness for the matching-islands workflow.

Compares a function compiled from a candidate C++ scratch (VC6 COFF object)
against the same function in the original game image, after normalizing
addresses and relocations away. The score is a SequenceMatcher ratio over
normalized instruction text, so struct offsets, register choice, and
instruction scheduling all count toward the match. The harness also reports
the exact common instruction prefix before the first normalized mismatch.
"""

from __future__ import annotations

from dataclasses import dataclass
import difflib
from pathlib import Path
import re
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
PADDING_LINE_TEXT = {
    "add byte [eax], al",
    "int3",
    "lea ecx, dword [ecx]",
    "nop",
}
BRANCH_TARGET_RE = re.compile(r"\bL([0-9a-f]+)\b")


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
    prefix_instructions: int
    target_lines: tuple[str, ...]
    candidate_lines: tuple[str, ...]

    @property
    def first_target_mismatch(self) -> str | None:
        if self.prefix_instructions >= len(self.target_lines):
            return None
        return self.target_lines[self.prefix_instructions]

    @property
    def first_candidate_mismatch(self) -> str | None:
        if self.prefix_instructions >= len(self.candidate_lines):
            return None
        return self.candidate_lines[self.prefix_instructions]

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


@dataclass(frozen=True, slots=True)
class DiffRegion:
    target_start: int
    target_end: int
    candidate_start: int
    candidate_end: int
    changed_target_instructions: int
    changed_candidate_instructions: int
    ratio: float
    prefix_instructions: int
    target_lines: tuple[str, ...]
    candidate_lines: tuple[str, ...]

    @property
    def target_span(self) -> str:
        return f"{self.target_start}:{self.target_end}"

    @property
    def candidate_span(self) -> str:
        return f"{self.candidate_start}:{self.candidate_end}"

    @property
    def instruction_delta(self) -> int:
        return (self.candidate_end - self.candidate_start) - (
            self.target_end - self.target_start
        )


@dataclass(frozen=True, slots=True)
class DisassemblyLine:
    offset: int
    address: int
    text: str


@dataclass(frozen=True, slots=True)
class MatchDump:
    target_lines: tuple[DisassemblyLine, ...]
    candidate_lines: tuple[DisassemblyLine, ...]


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


_OPERAND_SIZE_NAMES = {1: "byte", 2: "word", 4: "dword", 8: "qword", 10: "tword"}


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
    size = _OPERAND_SIZE_NAMES.get(operand.size, str(operand.size))
    return f"{size} [{'+'.join(parts)}]"


def disassemble_normalized_function(
    data: bytes,
    *,
    relocation_offsets: frozenset[int] | None = None,
    address_range: tuple[int, int] | None = None,
    base_address: int = 0,
) -> tuple[DisassemblyLine, ...]:
    """Disassemble to normalized instruction lines with offsets and addresses.

    Pass relocation_offsets so reloc'd immediates/displacements become ADDR.
    Pass address_range so absolute VAs inside the image range become ADDR.
    The same address_range is used for image and object code; otherwise
    immediate literals that merely look like image VAs encourage fake
    relocation symbols in scratches. Intra-function branch targets become
    L<offset> labels on both sides, so layouts compare structurally.
    """
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    relocation_offsets = relocation_offsets or frozenset()
    size = len(data)

    def is_masked_value(value: int) -> bool:
        return address_range is not None and address_range[0] <= value < address_range[1]

    lines: list[DisassemblyLine] = []
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
                # a relocated branch target is external even when the zero
                # displacement happens to land inside the function
                if imm_masked:
                    operands.append("ADDR")
                elif is_branch and 0 <= target_offset < size:
                    operands.append(f"L{target_offset:x}")
                elif is_masked_value(value):
                    operands.append("ADDR")
                else:
                    operands.append(f"0x{value:x}" if value >= 0 else f"-0x{-value:x}")
            elif operand.type == capstone.x86.X86_OP_MEM:
                masked = disp_masked or is_masked_value(operand.mem.disp)
                operands.append(_format_memory_operand(insn, operand, masked))
            else:
                operands.append("?")
        lines.append(
            DisassemblyLine(
                offset=insn_offset,
                address=insn.address,
                text=f"{insn.mnemonic} {', '.join(operands)}".strip(),
            )
        )
    return _strip_trailing_padding_lines(tuple(lines))


def _strip_trailing_padding_lines(
    lines: tuple[DisassemblyLine, ...],
) -> tuple[DisassemblyLine, ...]:
    """Drop section-alignment instructions after an untargeted terminal ret."""
    trim_start = len(lines)
    while trim_start > 0 and lines[trim_start - 1].text in PADDING_LINE_TEXT:
        trim_start -= 1
    if trim_start == len(lines) or trim_start == 0:
        return lines
    if not lines[trim_start - 1].text.startswith("ret"):
        return lines

    padding_offsets = {line.offset for line in lines[trim_start:]}
    for line in lines[:trim_start]:
        targets = {int(match.group(1), 16) for match in BRANCH_TARGET_RE.finditer(line.text)}
        if targets & padding_offsets:
            return lines
    return lines[:trim_start]


def normalize_function(
    data: bytes,
    *,
    relocation_offsets: frozenset[int] | None = None,
    address_range: tuple[int, int] | None = None,
    base_address: int = 0,
) -> tuple[str, ...]:
    """Disassemble to normalized instruction lines.

    Pass relocation_offsets so reloc'd immediates/displacements become ADDR.
    Pass address_range so absolute VAs inside the image range become ADDR.
    The same address_range is used for image and object code; otherwise
    immediate literals that merely look like image VAs encourage fake
    relocation symbols in scratches. Intra-function branch targets become
    L<offset> labels on both sides, so layouts compare structurally.
    """
    lines = disassemble_normalized_function(
        data,
        relocation_offsets=relocation_offsets,
        address_range=address_range,
        base_address=base_address,
    )
    return tuple(line.text for line in lines)


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
        address_range=(image.image_base, image.image_base + image.size_of_image),
    )
    ratio = difflib.SequenceMatcher(a=target_lines, b=candidate_lines, autojunk=False).ratio()
    prefix_instructions = common_prefix_length(target_lines, candidate_lines)
    return MatchResult(
        ratio=ratio,
        prefix_instructions=prefix_instructions,
        target_lines=target_lines,
        candidate_lines=candidate_lines,
    )


def common_prefix_length(target_lines: tuple[str, ...], candidate_lines: tuple[str, ...]) -> int:
    for index, (target, candidate_line) in enumerate(zip(target_lines, candidate_lines)):
        if target != candidate_line:
            return index
    return min(len(target_lines), len(candidate_lines))


def diff_regions(
    result: MatchResult,
    *,
    context: int = 4,
    max_regions: int | None = None,
) -> list[DiffRegion]:
    """Return localized mismatch regions from a normalized function diff.

    Region grouping is intentionally mechanical: adjacent non-equal opcodes are
    merged when the equal gap between them is no larger than the requested
    context. Each final region is then expanded by the same context so a human
    can see the local lead-in and fallout without reading the whole function.
    """
    if context < 0:
        raise ValueError("context must be non-negative")
    matcher = difflib.SequenceMatcher(
        a=result.target_lines,
        b=result.candidate_lines,
        autojunk=False,
    )
    groups: list[dict[str, int]] = []
    current: dict[str, int] | None = None
    pending_equal: tuple[int, int, int, int] | None = None
    for tag, a0, a1, b0, b1 in matcher.get_opcodes():
        if tag == "equal":
            if current is not None:
                pending_equal = (a0, a1, b0, b1)
            continue
        if current is None:
            current = {
                "a0": a0,
                "a1": a1,
                "b0": b0,
                "b1": b1,
                "changed_a": a1 - a0,
                "changed_b": b1 - b0,
            }
        elif pending_equal is not None and (
            (pending_equal[1] - pending_equal[0]) <= context
            or (pending_equal[3] - pending_equal[2]) <= context
        ):
            current["a1"] = a1
            current["b1"] = b1
            current["changed_a"] += a1 - a0
            current["changed_b"] += b1 - b0
        else:
            groups.append(current)
            current = {
                "a0": a0,
                "a1": a1,
                "b0": b0,
                "b1": b1,
                "changed_a": a1 - a0,
                "changed_b": b1 - b0,
            }
        pending_equal = None
    if current is not None:
        groups.append(current)

    regions: list[DiffRegion] = []
    for group in groups[:max_regions]:
        target_start = max(0, group["a0"] - context)
        target_end = min(len(result.target_lines), group["a1"] + context)
        candidate_start = max(0, group["b0"] - context)
        candidate_end = min(len(result.candidate_lines), group["b1"] + context)
        target_slice = result.target_lines[target_start:target_end]
        candidate_slice = result.candidate_lines[candidate_start:candidate_end]
        local_ratio = difflib.SequenceMatcher(
            a=target_slice,
            b=candidate_slice,
            autojunk=False,
        ).ratio()
        regions.append(
            DiffRegion(
                target_start=target_start,
                target_end=target_end,
                candidate_start=candidate_start,
                candidate_end=candidate_end,
                changed_target_instructions=group["changed_a"],
                changed_candidate_instructions=group["changed_b"],
                ratio=local_ratio,
                prefix_instructions=common_prefix_length(target_slice, candidate_slice),
                target_lines=target_slice,
                candidate_lines=candidate_slice,
            )
        )
    return regions


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


def run_match_dump(
    *,
    obj_path: Path,
    function_name: str,
    image_path: Path,
    manifest: FunctionSymbolManifest,
    symbol_name: str | None = None,
    end_va: int | None = None,
) -> MatchDump:
    obj = parse_coff_object(obj_path.read_bytes())
    candidate = extract_object_function(obj, symbol_name or function_name)
    start, end = resolve_function_extent(manifest, function_name, end_va)
    image = load_image(image_path, manifest.image_base)
    target_data = image.function_bytes(start, end)
    address_range = (image.image_base, image.image_base + image.size_of_image)
    return MatchDump(
        target_lines=disassemble_normalized_function(
            target_data,
            address_range=address_range,
            base_address=start,
        ),
        candidate_lines=disassemble_normalized_function(
            candidate.data,
            relocation_offsets=candidate.relocation_offsets,
            address_range=address_range,
        ),
    )


DEFAULT_MATCH_ROOT = Path(__file__).resolve().parents[2] / "tools/match"
DEFAULT_SCRATCH_COMPILER = "msvc6.5"
DEFAULT_SCRATCH_CFLAGS = "/O2 /G5 /W3"


@dataclass(frozen=True, slots=True)
class ScratchConfig:
    directory: Path
    function: str
    compiler: str
    cflags: str
    end_va: int | None
    symbol: str | None


@dataclass(frozen=True, slots=True)
class ScratchStatus:
    config: ScratchConfig
    address: int
    target_size: int
    ratio: float | None
    prefix_instructions: int
    target_instructions: int
    candidate_instructions: int
    error: str | None

    @property
    def state(self) -> str:
        if self.ratio is None:
            return "error"
        if self.ratio == 1.0:
            return "match"
        return "wip"


def load_scratch_config(directory: Path) -> ScratchConfig:
    import shlex

    values: dict[str, str] = {}
    for token in shlex.split((directory / "scratch.conf").read_text()):
        key, _, value = token.partition("=")
        if value:
            values[key] = value
    if "FUNCTION" not in values:
        raise ValueError(f"{directory}/scratch.conf must set FUNCTION")
    return ScratchConfig(
        directory=directory,
        function=values["FUNCTION"],
        compiler=values.get("COMPILER", DEFAULT_SCRATCH_COMPILER),
        cflags=values.get("CFLAGS", DEFAULT_SCRATCH_CFLAGS),
        end_va=int(values["END"], 0) if "END" in values else None,
        symbol=values.get("SYMBOL"),
    )


FORBIDDEN_SOURCE_TOKENS = ("__asm", "_asm", "__declspec(naked)")


def validate_scratch_source(source: Path) -> None:
    """Reject fakematching: a scratch must be plausible original C++.

    Inline assembly trivially reproduces any target bytes without recovering
    semantics, which defeats the entire purpose of matching.
    """
    text = source.read_text(encoding="latin1")
    for token in FORBIDDEN_SOURCE_TOKENS:
        if token in text:
            raise ValueError(f"{source}: {token!r} is not allowed in scratches (no fakematching)")


def compile_scratch(config: ScratchConfig, match_root: Path = DEFAULT_MATCH_ROOT) -> Path:
    """Compile scratch.cpp with cl.sh when the object is missing or stale."""
    import os
    import shlex
    import shutil
    import subprocess

    source = config.directory / "scratch.cpp"
    validate_scratch_source(source)
    build_dir = config.directory / "build"
    obj_path = build_dir / "scratch.obj"
    if obj_path.exists() and obj_path.stat().st_mtime >= source.stat().st_mtime:
        return obj_path

    build_dir.mkdir(exist_ok=True)
    shutil.copy(source, build_dir / "scratch.cpp")
    completed = subprocess.run(
        [str(match_root / "cl.sh"), "/c", *shlex.split(config.cflags), "scratch.cpp"],
        cwd=build_dir,
        env={**os.environ, "MSVC_VER": config.compiler},
        capture_output=True,
        text=True,
    )
    if completed.returncode != 0 or not obj_path.exists():
        raise RuntimeError(f"cl failed:\n{completed.stdout}{completed.stderr}")
    return obj_path


@dataclass(frozen=True, slots=True)
class IdiomCase:
    name: str
    description: str
    symbol: str
    source: str


@dataclass(frozen=True, slots=True)
class IdiomResult:
    case: IdiomCase
    object_path: Path
    instructions: tuple[str, ...]


IDIOM_CASES: tuple[IdiomCase, ...] = (
    IdiomCase(
        name="byte-array-stride6-or",
        description="Set bit 3 in the first byte of a 6-byte record via byte-array indexing.",
        symbol="probe",
        source="""\
extern "C" void probe(unsigned char* records, int cursor)
{
    records[cursor * 6] |= 8;
}
""",
    ),
    IdiomCase(
        name="byte-field-stride6-or",
        description="Set bit 3 in a named first-byte flags field of a 6-byte record.",
        symbol="probe",
        source="""\
struct RunRecord {
    unsigned char flags;
    char pad[5];
};

extern "C" void probe(RunRecord* records, int cursor)
{
    records[cursor].flags |= 8;
}
""",
    ),
    IdiomCase(
        name="bitfield-stride6-set",
        description="Set a named bitfield for bit 3 in the first byte of a 6-byte record.",
        symbol="probe",
        source="""\
struct RunRecord {
    unsigned char unknown_0 : 1;
    unsigned char unknown_1 : 1;
    unsigned char unknown_2 : 1;
    unsigned char completed : 1;
    unsigned char unknown_4_7 : 4;
    char pad[5];
};

extern "C" void probe(RunRecord* records, int cursor)
{
    records[cursor].completed = 1;
}
""",
    ),
    IdiomCase(
        name="block-scoped-pointer-call",
        description="Declare a destination pointer at block scope and reuse it for calls.",
        symbol="probe",
        source="""\
struct Record {
    int active;
    int value;
};

struct Bank {
    void add(Record* record, int value);
};

extern "C" void probe(Bank* bank, Record* record, int value, int gate)
{
    if (gate != 0) {
        Record* out = record;
        out->active = 1;
        out->value = value;
        bank->add(out, value);
    }
}
""",
    ),
    IdiomCase(
        name="sparse-switch-0-1-4",
        description="Sparse mode dispatch for cases 0, 1, and 4.",
        symbol="probe",
        source="""\
extern "C" int probe(int mode)
{
    switch (mode) {
    case 0:
        return 10;
    case 1:
        return 11;
    case 4:
        return 14;
    default:
        return 0;
    }
}
""",
    ),
    IdiomCase(
        name="six-dword-struct-copy",
        description="Copy a six-dword aggregate by assignment.",
        symbol="probe",
        source="""\
struct SixDwords {
    int values[6];
};

extern "C" void probe(SixDwords* dst, const SixDwords* src)
{
    *dst = *src;
}
""",
    ),
    IdiomCase(
        name="gated-tail-member-void",
        description="Member mutator with a final two-field global gate and void thiscall side effect.",
        symbol="probe",
        source="""\
extern char* g_game_base;

struct SoundEffectManager {
    void play_sound_effect(int sound_id);
};

extern SoundEffectManager g_sound_effect_manager;

struct Player {
    int total_score;
    int buckets[6];
    int visible_life_stock;

    void probe(int score_kind, int points);
};

void Player::probe(int score_kind, int points)
{
    buckets[score_kind] += points;
    int old_total = total_score;
    int new_total = old_total + points;
    total_score = new_total;

    if (old_total / 50000 != new_total / 50000) {
        int lives = visible_life_stock;
        if (lives < 9)
            visible_life_stock = lives + 1;
    }

    char* game = g_game_base;
    if (*(int*)(game + 0x74658) == 0 && *(int*)(game + 0x24) == 0)
        g_sound_effect_manager.play_sound_effect(0x2c);
}
""",
    ),
    IdiomCase(
        name="gated-tail-member-void-goto",
        description="Member mutator with explicit shared done label after a final global gate.",
        symbol="probe",
        source="""\
extern char* g_game_base;

struct SoundEffectManager {
    void play_sound_effect(int sound_id);
};

extern SoundEffectManager g_sound_effect_manager;

struct Player {
    int total_score;
    int buckets[6];
    int visible_life_stock;

    void probe(int score_kind, int points);
};

void Player::probe(int score_kind, int points)
{
    buckets[score_kind] += points;
    int old_total = total_score;
    int new_total = old_total + points;
    total_score = new_total;

    if (old_total / 50000 != new_total / 50000) {
        int lives = visible_life_stock;
        if (lives < 9)
            visible_life_stock = lives + 1;
    }

    char* game = g_game_base;
    if (*(int*)(game + 0x74658) != 0)
        goto done;
    if (*(int*)(game + 0x24) != 0)
        goto done;
    g_sound_effect_manager.play_sound_effect(0x2c);

done:
    return;
}
""",
    ),
    IdiomCase(
        name="gated-tail-member-int-preserve-game",
        description="Member function that returns the global pointer after an optional void thiscall side effect.",
        symbol="probe",
        source="""\
extern char* g_game_base;

struct SoundEffectManager {
    void play_sound_effect(int sound_id);
};

extern SoundEffectManager g_sound_effect_manager;

struct Player {
    int total_score;
    int buckets[6];
    int visible_life_stock;

    int probe(int score_kind, int points);
};

int Player::probe(int score_kind, int points)
{
    buckets[score_kind] += points;
    int old_total = total_score;
    int new_total = old_total + points;
    total_score = new_total;

    if (old_total / 50000 != new_total / 50000) {
        int lives = visible_life_stock;
        if (lives < 9)
            visible_life_stock = lives + 1;
    }

    char* game = g_game_base;
    if (*(int*)(game + 0x74658) == 0 && *(int*)(game + 0x24) == 0)
        g_sound_effect_manager.play_sound_effect(0x2c);
    return (int)game;
}
""",
    ),
    IdiomCase(
        name="gated-tail-member-int-call-result",
        description="Member function that returns either a global pointer or the final thiscall result.",
        symbol="probe",
        source="""\
extern char* g_game_base;

struct SoundEffectManager {
    int play_sound_effect(int sound_id);
};

extern SoundEffectManager g_sound_effect_manager;

struct Player {
    int total_score;
    int buckets[6];
    int visible_life_stock;

    int probe(int score_kind, int points);
};

int Player::probe(int score_kind, int points)
{
    buckets[score_kind] += points;
    int old_total = total_score;
    int new_total = old_total + points;
    total_score = new_total;

    if (old_total / 50000 != new_total / 50000) {
        int lives = visible_life_stock;
        if (lives < 9)
            visible_life_stock = lives + 1;
    }

    char* game = g_game_base;
    int result = (int)game;
    if (*(int*)(game + 0x74658) == 0 && *(int*)(game + 0x24) == 0)
        result = g_sound_effect_manager.play_sound_effect(0x2c);
    return result;
}
""",
    ),
)
IDIOM_CASES_BY_NAME = {case.name: case for case in IDIOM_CASES}


def compile_idiom_case(
    case: IdiomCase,
    *,
    match_root: Path = DEFAULT_MATCH_ROOT,
    compiler: str = DEFAULT_SCRATCH_COMPILER,
    cflags: str = DEFAULT_SCRATCH_CFLAGS,
) -> IdiomResult:
    import os
    import shlex
    import subprocess

    build_dir = match_root / "idioms/build" / case.name
    build_dir.mkdir(parents=True, exist_ok=True)
    source_path = build_dir / "scratch.cpp"
    obj_path = build_dir / "scratch.obj"
    source_path.write_text(case.source, encoding="latin1")
    validate_scratch_source(source_path)
    completed = subprocess.run(
        [str(match_root / "cl.sh"), "/c", *shlex.split(cflags), "scratch.cpp"],
        cwd=build_dir,
        env={**os.environ, "MSVC_VER": compiler},
        capture_output=True,
        text=True,
    )
    if completed.returncode != 0 or not obj_path.exists():
        raise RuntimeError(f"cl failed for {case.name}:\n{completed.stdout}{completed.stderr}")
    obj = parse_coff_object(obj_path.read_bytes())
    function = extract_object_function(obj, case.symbol)
    return IdiomResult(
        case=case,
        object_path=obj_path,
        instructions=normalize_function(function.data, relocation_offsets=function.relocation_offsets),
    )


# bump when the cache schema changes; matcher source mtime handles scoring edits
CACHE_VERSION = 3


def _scratch_cache_key(config: ScratchConfig, image_path: Path) -> dict:
    def mtime(path: Path) -> float | None:
        return path.stat().st_mtime if path.exists() else None

    return {
        "version": CACHE_VERSION,
        "source_mtime": mtime(config.directory / "scratch.cpp"),
        "conf_mtime": mtime(config.directory / "scratch.conf"),
        "image_mtime": mtime(image_path),
        "matcher_mtime": mtime(Path(__file__)),
    }


def _load_cached_status(config: ScratchConfig, image_path: Path) -> dict | None:
    import json

    cache_path = config.directory / "build/match-cache.json"
    if not cache_path.exists():
        return None
    try:
        cached = json.loads(cache_path.read_text())
    except (json.JSONDecodeError, OSError):
        return None
    if cached.get("key") != _scratch_cache_key(config, image_path):
        return None
    return cached.get("status")


def _store_cached_status(config: ScratchConfig, image_path: Path, status: dict) -> None:
    import json

    cache_path = config.directory / "build/match-cache.json"
    cache_path.parent.mkdir(exist_ok=True)
    cache_path.write_text(
        json.dumps({"key": _scratch_cache_key(config, image_path), "status": status})
    )


def collect_scratch_statuses(
    manifest: FunctionSymbolManifest,
    image_path: Path,
    match_root: Path = DEFAULT_MATCH_ROOT,
) -> list[ScratchStatus]:
    """Match every scratch, reusing cached results for unchanged ones.

    The cache keys on scratch source/conf, image, and matcher mtimes, so an
    unchanged scratch costs one stat() pass instead of a compile + disassembly
    + diff while normalizer changes still invalidate old scores.
    """
    image: LoadedImage | None = None
    by_name = {symbol.name: symbol for symbol in manifest.functions}
    statuses: list[ScratchStatus] = []
    for conf_path in sorted(match_root.glob("scratches/*/scratch.conf")):
        config = load_scratch_config(conf_path.parent)
        address = by_name[config.function].address if config.function in by_name else 0

        if (cached := _load_cached_status(config, image_path)) is not None:
            statuses.append(ScratchStatus(config=config, address=address, **cached))
            continue

        if image is None:
            image = load_image(image_path, manifest.image_base)
        try:
            start, end = resolve_function_extent(manifest, config.function, config.end_va)
            target_data = image.function_bytes(start, end)
            obj_path = compile_scratch(config, match_root)
            obj = parse_coff_object(obj_path.read_bytes())
            candidate = extract_object_function(obj, config.symbol or config.function)
            result = match_function(target_data, candidate, image=image, target_va=start)
            fields = {
                "target_size": len(target_data),
                "ratio": result.ratio,
                "prefix_instructions": result.prefix_instructions,
                "target_instructions": len(result.target_lines),
                "candidate_instructions": len(result.candidate_lines),
                "error": None,
            }
        except (ValueError, RuntimeError) as error:
            fields = {
                "target_size": 0,
                "ratio": None,
                "prefix_instructions": 0,
                "target_instructions": 0,
                "candidate_instructions": 0,
                "error": str(error).splitlines()[0] if str(error) else "unknown error",
            }
        else:
            _store_cached_status(config, image_path, fields)
        statuses.append(ScratchStatus(config=config, address=address, **fields))
    return statuses


@dataclass(frozen=True, slots=True)
class ClusterTotals:
    function_count: int
    byte_total: int
    matched_functions: int
    matched_bytes: int

    @property
    def byte_percentage(self) -> float:
        return self.matched_bytes / self.byte_total if self.byte_total else 0.0


def manifest_cluster_totals(
    manifest: FunctionSymbolManifest,
    image_path: Path,
    statuses: list[ScratchStatus],
) -> ClusterTotals:
    """Totals over the whole mapped gameplay cluster, not just touched scratches.

    Each curated function's extent runs to the next curated address (padding
    trimmed); the last function ends at the next int3 padding byte.
    """
    image = load_image(image_path, manifest.image_base)
    addresses = sorted(symbol.address for symbol in manifest.functions)
    byte_total = 0
    for start, end in zip(addresses, addresses[1:]):
        byte_total += len(image.function_bytes(start, end))
    last = addresses[-1]
    padding_index = image.mapped.find(b"\xcc", last - image.image_base)
    if padding_index != -1:
        byte_total += len(image.function_bytes(last, image.image_base + padding_index))

    matched = [status for status in statuses if status.state == "match"]
    return ClusterTotals(
        function_count=len(addresses),
        byte_total=byte_total,
        matched_functions=len(matched),
        matched_bytes=sum(status.target_size for status in matched),
    )


STATE_ICONS = {"match": "✅", "wip": "🚧", "error": "❌"}
# build column stays empty unless a scratch deviates from the project-wide
# toolchain assumption (msvc6.5 /O2 /G5 /W3 for all game code)
STATUS_HEADER = ("", "function", "address", "bytes", "insns", "match", "prefix", "build", "note")


def render_status_rows(statuses: list[ScratchStatus]) -> list[tuple[str, ...]]:
    rows = []
    for status in sorted(statuses, key=lambda item: item.address):
        ratio = f"{status.ratio:.2%}" if status.ratio is not None else "-"
        insns = (
            f"{status.candidate_instructions}/{status.target_instructions}"
            if status.ratio is not None
            else "-"
        )
        prefix = (
            f"{status.prefix_instructions}/{status.target_instructions}"
            if status.ratio is not None
            else "-"
        )
        build = f"{status.config.compiler} {status.config.cflags}"
        default_build = f"{DEFAULT_SCRATCH_COMPILER} {DEFAULT_SCRATCH_CFLAGS}"
        rows.append(
            (
                STATE_ICONS[status.state],
                status.config.function,
                f"0x{status.address:x}",
                str(status.target_size),
                insns,
                ratio,
                prefix,
                "" if build == default_build else build,
                status.error or "",
            )
        )
    return rows


def _cluster_summary(totals: ClusterTotals, statuses: list[ScratchStatus]) -> str:
    return (
        f"cluster: {totals.matched_functions}/{totals.function_count} functions, "
        f"{totals.matched_bytes}/{totals.byte_total} bytes "
        f"({totals.byte_percentage:.1%}) matched; "
        f"{totals.matched_functions}/{len(statuses)} scratches at 100%"
    )


def render_status_table(statuses: list[ScratchStatus], totals: ClusterTotals) -> str:
    rows = [STATUS_HEADER, *render_status_rows(statuses)]
    widths = [max(len(row[column]) for row in rows) for column in range(len(STATUS_HEADER))]
    lines = [
        "  ".join(cell.ljust(width) for cell, width in zip(row, widths)).rstrip()
        for row in rows
    ]
    lines.append(f"\n{_cluster_summary(totals, statuses)}")
    return "\n".join(lines)


def render_status_markdown(statuses: list[ScratchStatus], totals: ClusterTotals) -> str:
    lines = [
        "# Matching Status",
        "",
        "Regenerate with `uv run snail match status --write tools/match/STATUS.md`.",
        "",
        f"**{totals.matched_functions}/{totals.function_count}** mapped gameplay "
        f"functions matched, **{totals.matched_bytes}/{totals.byte_total}** bytes "
        f"(**{totals.byte_percentage:.1%}**). Byte totals are curated-extent "
        "upper bounds: uncurated code between manifest functions counts toward "
        "the preceding extent.",
        "",
        "| | function | address | bytes | insns | match | prefix | build |",
        "|---|---|---|---|---|---|---|---|",
    ]
    for row in render_status_rows(statuses):
        lines.append("| " + " | ".join(row[:8]) + " |")
    lines.append("")
    return "\n".join(lines)


@dataclass(frozen=True, slots=True)
class TypeDefinition:
    kind: str
    name: str
    path: Path
    signature: str
    is_header: bool


@dataclass(frozen=True, slots=True)
class TypeConsolidationFinding:
    name: str
    status: str
    scratch_count: int
    header_count: int
    signature_count: int
    paths: tuple[Path, ...]
    recommendation: str


_TYPE_DEFINITION_RE = re.compile(r"\b(struct|class)\s+([A-Za-z_][A-Za-z0-9_]*)\s*\{")
_BLOCK_COMMENT_RE = re.compile(r"/\*.*?\*/", re.DOTALL)
_LINE_COMMENT_RE = re.compile(r"//.*")
_SPACE_RE = re.compile(r"\s+")


def _strip_cpp_comments(text: str) -> str:
    return _LINE_COMMENT_RE.sub("", _BLOCK_COMMENT_RE.sub("", text))


def _find_matching_brace(text: str, open_brace: int) -> int:
    depth = 0
    for index in range(open_brace, len(text)):
        char = text[index]
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0:
                return index
    raise ValueError("unclosed type definition")


def normalize_type_signature(kind: str, name: str, body: str) -> str:
    body = _strip_cpp_comments(body)
    body = _SPACE_RE.sub(" ", body).strip()
    return f"{kind} {name} {{ {body} }}"


def find_type_definitions(path: Path, *, is_header: bool = False) -> list[TypeDefinition]:
    text = path.read_text(encoding="latin1")
    definitions: list[TypeDefinition] = []
    for match in _TYPE_DEFINITION_RE.finditer(text):
        open_brace = match.end() - 1
        try:
            close_brace = _find_matching_brace(text, open_brace)
        except ValueError:
            continue
        kind, name = match.group(1), match.group(2)
        body = text[open_brace + 1 : close_brace]
        definitions.append(
            TypeDefinition(
                kind=kind,
                name=name,
                path=path,
                signature=normalize_type_signature(kind, name, body),
                is_header=is_header,
            )
        )
    return definitions


def scan_match_type_definitions(match_root: Path = DEFAULT_MATCH_ROOT) -> list[TypeDefinition]:
    definitions: list[TypeDefinition] = []
    for header in sorted((match_root / "include").glob("*.h")):
        definitions.extend(find_type_definitions(header, is_header=True))
    for scratch in sorted(match_root.glob("scratches/*/scratch.cpp")):
        definitions.extend(find_type_definitions(scratch, is_header=False))
    return definitions


def type_consolidation_findings(
    match_root: Path = DEFAULT_MATCH_ROOT,
    *,
    threshold: int = 2,
    names: set[str] | None = None,
) -> list[TypeConsolidationFinding]:
    if threshold < 1:
        raise ValueError("threshold must be at least 1")
    definitions = scan_match_type_definitions(match_root)
    by_name: dict[str, list[TypeDefinition]] = {}
    for definition in definitions:
        by_name.setdefault(definition.name, []).append(definition)

    findings: list[TypeConsolidationFinding] = []
    for name, named_definitions in sorted(by_name.items()):
        if names is not None and name not in names:
            continue
        scratch_definitions = [definition for definition in named_definitions if not definition.is_header]
        header_definitions = [definition for definition in named_definitions if definition.is_header]
        if len(scratch_definitions) < threshold and not header_definitions:
            continue

        scratch_signatures = {definition.signature for definition in scratch_definitions}
        paths = tuple(sorted({definition.path for definition in named_definitions}))
        if header_definitions and scratch_definitions:
            status = "covered"
            recommendation = (
                "header exists; consider replacing matching scratch-local copies with includes"
            )
        elif len(scratch_signatures) == 1 and len(scratch_definitions) >= threshold:
            status = "ready"
            recommendation = "same scratch-local definition appears repeatedly; consider a header"
        elif len(scratch_signatures) > 1 and len(scratch_definitions) >= threshold:
            status = "divergent"
            recommendation = "same name has multiple scratch-local shapes; do not consolidate yet"
        else:
            continue

        findings.append(
            TypeConsolidationFinding(
                name=name,
                status=status,
                scratch_count=len(scratch_definitions),
                header_count=len(header_definitions),
                signature_count=len(scratch_signatures),
                paths=paths,
                recommendation=recommendation,
            )
        )
    return findings
