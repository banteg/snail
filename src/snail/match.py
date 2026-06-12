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
        address_range=(image.image_base, image.image_base + image.size_of_image),
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


# bump when the normalizer or scoring changes so cached ratios recompute
CACHE_VERSION = 1


def _scratch_cache_key(config: ScratchConfig, image_path: Path) -> dict:
    def mtime(path: Path) -> float | None:
        return path.stat().st_mtime if path.exists() else None

    return {
        "version": CACHE_VERSION,
        "source_mtime": mtime(config.directory / "scratch.cpp"),
        "conf_mtime": mtime(config.directory / "scratch.conf"),
        "image_mtime": mtime(image_path),
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

    The cache keys on scratch source/conf and image mtimes, so an unchanged
    scratch costs one stat() pass instead of a compile + disassembly + diff.
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
                "target_instructions": len(result.target_lines),
                "candidate_instructions": len(result.candidate_lines),
                "error": None,
            }
        except (ValueError, RuntimeError) as error:
            fields = {
                "target_size": 0,
                "ratio": None,
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
STATUS_HEADER = ("", "function", "address", "bytes", "insns", "match", "build", "note")


def render_status_rows(statuses: list[ScratchStatus]) -> list[tuple[str, ...]]:
    rows = []
    for status in sorted(statuses, key=lambda item: item.address):
        ratio = f"{status.ratio:.2%}" if status.ratio is not None else "-"
        insns = (
            f"{status.candidate_instructions}/{status.target_instructions}"
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
        "| | function | address | bytes | insns | match | build |",
        "|---|---|---|---|---|---|---|",
    ]
    for row in render_status_rows(statuses):
        lines.append("| " + " | ".join(row[:7]) + " |")
    lines.append("")
    return "\n".join(lines)
