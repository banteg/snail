"""Asm matching harness for the matching-islands workflow.

Compares a function compiled from a candidate C++ scratch (VC6 COFF object)
against the same function in the original game image, after normalizing
addresses and relocations away. The score is a SequenceMatcher ratio over
normalized instruction text, so struct offsets, register choice, and
instruction scheduling all count toward the match. The harness also reports
the exact common instruction prefix before the first normalized mismatch.
"""

from __future__ import annotations

from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor
from dataclasses import dataclass, field
import difflib
import hashlib
import json
import os
from pathlib import Path
import re
import struct

import capstone

from .symbols import FunctionSymbol, FunctionSymbolManifest, REPO_ROOT

IMAGE_FILE_MACHINE_I386 = 0x14C
IMAGE_SYM_CLASS_EXTERNAL = 2
IMAGE_SYM_CLASS_STATIC = 3
IMAGE_SCN_CNT_CODE = 0x00000020
SYM_TYPE_FUNCTION = 0x20
# int3 between image functions, nop for section alignment inside objects
PADDING_BYTES = b"\xcc\x90"
BRANCH_TARGET_RE = re.compile(r"\bL([0-9a-f]+)\b")
DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH = (
    REPO_ROOT / "analysis/symbols/gameplay-references.json"
)
CONTENT_AUDITED_REFERENCE_KINDS = frozenset(("data_blob", "lookup_table"))
DEFAULT_MATCH_JOBS = min(8, max(1, os.cpu_count() or 1))
LOCAL_INCLUDE_RE = re.compile(r'^\s*#\s*include\s*"([^"\r\n]+)"', re.MULTILINE)


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
    raw_index: int
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
class ObjectRelocationReference:
    offset: int
    symbol_name: str
    text: str
    key: str | None
    explained: bool
    addend: int | None = None
    symbol_offset: int | None = None
    symbol_size: int | None = None
    symbol_data: bytes | None = None
    symbol_relocation_offsets: frozenset[int] = frozenset()


@dataclass(frozen=True, slots=True)
class ReferenceSymbol:
    address: int
    name: str
    kind: str
    aliases: tuple[str, ...] = ()
    description: str | None = None
    size: int | None = None
    allow_one_past: bool = False


@dataclass(frozen=True, slots=True)
class ReferenceSymbolManifest:
    name: str
    symbols: tuple[ReferenceSymbol, ...] = ()


def _parse_hex_or_int(value: object, *, field_name: str) -> int:
    if isinstance(value, int):
        return value
    if isinstance(value, str) and re.fullmatch(r"0x[0-9a-fA-F]+", value):
        return int(value, 16)
    raise ValueError(f"{field_name} must be an integer or hex string")


def load_reference_symbol_manifest(path: Path) -> ReferenceSymbolManifest:
    raw = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(raw, dict):
        raise ValueError("reference symbol manifest must be a JSON object")
    name = raw.get("name")
    if not isinstance(name, str) or not name:
        raise ValueError("reference symbol manifest field 'name' must be a string")
    raw_symbols = raw.get("symbols")
    if not isinstance(raw_symbols, list):
        raise ValueError("reference symbol manifest field 'symbols' must be a list")

    symbols: list[ReferenceSymbol] = []
    seen_names: dict[str, dict[str, str]] = {}
    for index, raw_symbol in enumerate(raw_symbols):
        if not isinstance(raw_symbol, dict):
            raise ValueError(f"symbols[{index}] must be an object")
        address = _parse_hex_or_int(
            raw_symbol.get("address"),
            field_name=f"symbols[{index}].address",
        )
        name_value = raw_symbol.get("name")
        kind = raw_symbol.get("kind", "data")
        if not isinstance(name_value, str) or not name_value:
            raise ValueError(f"symbols[{index}].name must be a non-empty string")
        if not isinstance(kind, str) or not kind:
            raise ValueError(f"symbols[{index}].kind must be a non-empty string")
        aliases_value = raw_symbol.get("aliases", [])
        if not isinstance(aliases_value, list) or not all(
            isinstance(alias, str) and alias for alias in aliases_value
        ):
            raise ValueError(f"symbols[{index}].aliases must be a list of strings")
        description = raw_symbol.get("description")
        if description is not None and not isinstance(description, str):
            raise ValueError(f"symbols[{index}].description must be a string")
        size_value = raw_symbol.get("size")
        size = None
        if size_value is not None:
            size = _parse_hex_or_int(
                size_value,
                field_name=f"symbols[{index}].size",
            )
            if size <= 0:
                raise ValueError(f"symbols[{index}].size must be positive")
        allow_one_past = raw_symbol.get("allow_one_past", False)
        if not isinstance(allow_one_past, bool):
            raise ValueError(f"symbols[{index}].allow_one_past must be a boolean")
        if allow_one_past and size is None:
            raise ValueError(f"symbols[{index}].allow_one_past requires size")
        for raw_name in (name_value, *aliases_value):
            checked_names = {raw_name}
            # A fully decorated C++ name carries its overload signature. Its
            # shortened display name does not, so different overloads may
            # legitimately share that canonical spelling.
            if not (raw_name.startswith("?") and "@" in raw_name):
                checked_names.add(_canonical_symbol_name(raw_name))
            for checked_name in checked_names:
                previous_symbols = seen_names.setdefault(checked_name, {})
                previous_symbol = previous_symbols.get(kind)
                if previous_symbol is not None and previous_symbol != name_value:
                    raise ValueError(
                        "duplicate reference symbol name or alias: "
                        f"{checked_name} ({previous_symbol}, {name_value})"
                    )
                if (
                    not checked_name.startswith("$L")
                    and previous_symbols
                    and name_value not in previous_symbols.values()
                ):
                    previous_symbol = next(iter(previous_symbols.values()))
                    raise ValueError(
                        "duplicate reference symbol name or alias: "
                        f"{checked_name} ({previous_symbol}, {name_value})"
                    )
                previous_symbols[kind] = name_value
        symbols.append(
            ReferenceSymbol(
                address=address,
                name=name_value,
                kind=kind,
                aliases=tuple(aliases_value),
                description=description,
                size=size,
                allow_one_past=allow_one_past,
            )
        )
    return ReferenceSymbolManifest(name=name, symbols=tuple(symbols))


def load_default_reference_symbol_manifest() -> ReferenceSymbolManifest:
    if not DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH.exists():
        return ReferenceSymbolManifest(name="empty")
    return load_reference_symbol_manifest(DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH)


@dataclass(frozen=True, slots=True)
class ObjectFunction:
    name: str
    data: bytes
    relocation_offsets: frozenset[int]
    relocation_references: tuple[ObjectRelocationReference, ...] = ()


@dataclass(frozen=True, slots=True)
class MaskedReference:
    operand_index: int
    kind: str
    source: str
    value: int | None
    text: str
    key: str | None
    explained: bool
    alternate_keys: tuple[str, ...] = ()
    jump_table_entries: tuple[int, ...] | None = None
    alternate_jump_table_entries: tuple[tuple[int, ...], ...] = ()
    audited_bytes: bytes | None = None
    local_data_bytes: bytes | None = None
    normalized_code: tuple[str, ...] | None = None


@dataclass(frozen=True, slots=True)
class MaskedOperandAuditEntry:
    target_index: int
    candidate_index: int
    target_offset: int
    candidate_offset: int
    target_address: int
    candidate_address: int
    instruction: str
    target_references: tuple[MaskedReference, ...]
    candidate_references: tuple[MaskedReference, ...]
    status: str


@dataclass(frozen=True, slots=True)
class MaskedOperandAudit:
    entries: tuple[MaskedOperandAuditEntry, ...] = ()

    @property
    def ok_count(self) -> int:
        return sum(entry.status == "ok" for entry in self.entries)

    @property
    def unresolved_count(self) -> int:
        return sum(entry.status == "unresolved" for entry in self.entries)

    @property
    def mismatch_count(self) -> int:
        return sum(entry.status == "mismatch" for entry in self.entries)

    @property
    def problem_count(self) -> int:
        return self.unresolved_count + self.mismatch_count


@dataclass(frozen=True, slots=True)
class MatchResult:
    ratio: float
    prefix_instructions: int
    target_lines: tuple[str, ...]
    candidate_lines: tuple[str, ...]
    target_disassembly: tuple["DisassemblyLine", ...] = ()
    candidate_disassembly: tuple["DisassemblyLine", ...] = ()
    masked_operand_audit: MaskedOperandAudit = field(default_factory=MaskedOperandAudit)

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
    masked_references: tuple[MaskedReference, ...] = ()


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
                raw_index=index,
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


def _read_u32(data: bytes, offset: int) -> int | None:
    if 0 <= offset <= len(data) - 4:
        return struct.unpack_from("<I", data, offset)[0]
    return None


def _read_bytes(data: bytes, offset: int, byte_count: int) -> bytes | None:
    if byte_count <= 0:
        return None
    if not (0 <= offset <= len(data) - byte_count):
        return None
    return data[offset : offset + byte_count]


def _read_image_jump_table_entries(
    image: LoadedImage,
    table_va: int,
    byte_count: int,
    *,
    relative_to: int,
) -> tuple[int, ...] | None:
    if byte_count <= 0 or byte_count % 4 != 0:
        return None
    table_offset = table_va - image.image_base
    entries: list[int] = []
    for entry_offset in range(table_offset, table_offset + byte_count, 4):
        value = _read_u32(image.mapped, entry_offset)
        if value is None:
            return None
        entries.append(value - relative_to)
    return tuple(entries)


def _read_object_jump_table_entries(
    data: bytes,
    table_offset: int,
    relocation_by_offset: dict[int, ObjectRelocationReference],
    byte_count: int | None = None,
) -> tuple[int, ...] | None:
    if byte_count is not None:
        if byte_count <= 0 or byte_count % 4 != 0:
            return None
        if not (0 <= table_offset <= len(data) - byte_count):
            return None
        end_offset = table_offset + byte_count
    else:
        end_offset = len(data)
    entries: list[int] = []
    for entry_offset in range(table_offset, end_offset, 4):
        reference = relocation_by_offset.get(entry_offset)
        if reference is None:
            if byte_count is not None:
                return None
            break
        if reference.symbol_offset is None:
            return None
        entries.append(reference.symbol_offset + (reference.addend or 0))
    return tuple(entries) or None


def _read_object_reference_bytes(
    data: bytes,
    reference: ObjectRelocationReference,
    byte_count: int,
) -> bytes | None:
    if reference.symbol_offset is None:
        return None
    return _read_bytes(data, reference.symbol_offset + (reference.addend or 0), byte_count)


def _read_printable_c_string(data: bytes, offset: int, *, limit: int = 160) -> str | None:
    if offset < 0 or offset >= len(data):
        return None
    end = data.find(b"\x00", offset, min(len(data), offset + limit + 1))
    if end == -1 or end == offset:
        return None
    raw = data[offset:end]
    if any(
        (byte < 0x20 and byte not in b"\t\n\r") or byte > 0x7e
        for byte in raw
    ):
        return None
    return raw.decode("ascii")


def _quote_reference_string(value: str) -> str:
    escaped = value.encode("unicode_escape").decode("ascii")
    return f'"{escaped}"'


def _canonical_symbol_name(name: str) -> str:
    name = name.removeprefix("__imp_")
    name = name.removeprefix("__imp__")
    if name.startswith("?"):
        match = re.match(r"^\?([^@]+)@", name)
        if match:
            return match.group(1)
    name = name.lstrip("_")
    return re.sub(r"@\d+$", "", name)


def _reference_symbol_by_address(
    reference_manifest: ReferenceSymbolManifest | None,
) -> dict[int, ReferenceSymbol]:
    if reference_manifest is None:
        return {}
    by_address: dict[int, ReferenceSymbol] = {}
    for symbol in reference_manifest.symbols:
        by_address.setdefault(symbol.address, symbol)
    return by_address


def _reference_symbols_for_address(
    reference_manifest: ReferenceSymbolManifest | None,
    value: int,
) -> tuple[ReferenceSymbol, ...]:
    if reference_manifest is None:
        return ()
    return tuple(symbol for symbol in reference_manifest.symbols if symbol.address == value)


def _reference_symbol_by_name(
    reference_manifest: ReferenceSymbolManifest | None,
) -> dict[str, ReferenceSymbol]:
    if reference_manifest is None:
        return {}
    by_name: dict[str, ReferenceSymbol] = {}
    # Populate canonical fallbacks first, then let exact manifest spellings
    # override them. This preserves convenient C-style aliases while allowing
    # decorated C++ overloads to resolve independently.
    for symbol in reference_manifest.symbols:
        for name in (symbol.name, *symbol.aliases):
            if name.startswith("$L"):
                continue
            by_name.setdefault(_canonical_symbol_name(name), symbol)
    for symbol in reference_manifest.symbols:
        for name in (symbol.name, *symbol.aliases):
            if name.startswith("$L"):
                continue
            by_name[name] = symbol
    return by_name


def _reference_symbol_by_local_label(
    reference_manifest: ReferenceSymbolManifest | None,
) -> dict[str, tuple[ReferenceSymbol, ...]]:
    if reference_manifest is None:
        return {}
    by_name_lists: dict[str, list[ReferenceSymbol]] = {}
    for symbol in reference_manifest.symbols:
        for alias in symbol.aliases:
            if alias.startswith("$L"):
                by_name_lists.setdefault(alias, []).append(symbol)
    return {name: tuple(symbols) for name, symbols in by_name_lists.items()}


def _reference_key_by_name(
    reference_manifest: ReferenceSymbolManifest | None,
) -> dict[str, str]:
    return {
        name: _format_reference_key(symbol)
        for name, symbol in _reference_symbol_by_name(reference_manifest).items()
    }


def _reference_key_for_symbol_name(
    reference_manifest: ReferenceSymbolManifest | None,
    name: str,
) -> str | None:
    by_name = _reference_key_by_name(reference_manifest)
    return by_name.get(name) or by_name.get(_canonical_symbol_name(name))


def _reference_symbol_for_symbol_name(
    reference_manifest: ReferenceSymbolManifest | None,
    name: str,
) -> ReferenceSymbol | None:
    by_name = _reference_symbol_by_name(reference_manifest)
    return by_name.get(name) or by_name.get(_canonical_symbol_name(name))


def _reference_symbol_for_local_label(
    reference_manifest: ReferenceSymbolManifest | None,
    name: str,
    *,
    kind: str | None = None,
) -> ReferenceSymbol | None:
    candidates = _reference_symbol_by_local_label(reference_manifest).get(name, ())
    if kind is not None:
        candidates = tuple(symbol for symbol in candidates if symbol.kind == kind)
    return candidates[0] if len(candidates) == 1 else None


def _format_addend_suffix(addend: int) -> str:
    if addend == 0:
        return ""
    return f"+0x{addend:x}"


def _format_reference_key(symbol: ReferenceSymbol, addend: int = 0) -> str:
    return f"ref:{symbol.name}{_format_addend_suffix(addend)}"


def _format_reference_symbol(symbol: ReferenceSymbol, addend: int = 0) -> tuple[str, str]:
    suffix = _format_addend_suffix(addend)
    return f"{symbol.kind}:{symbol.name}{suffix}", _format_reference_key(symbol, addend)


def _reference_offsets_for_address(
    reference_manifest: ReferenceSymbolManifest | None,
    value: int,
) -> tuple[tuple[ReferenceSymbol, int], ...]:
    if reference_manifest is None:
        return ()
    matches: list[tuple[ReferenceSymbol, int]] = []
    for symbol in reference_manifest.symbols:
        if symbol.size is None:
            continue
        offset = value - symbol.address
        if 0 < offset < symbol.size or (
            symbol.allow_one_past and offset == symbol.size
        ):
            matches.append((symbol, offset))
    return tuple(matches)


def _reference_alternate_keys_for_address(
    reference_manifest: ReferenceSymbolManifest | None,
    value: int,
    *,
    primary_key: str | None,
) -> tuple[str, ...]:
    alternate_keys: list[str] = []
    for symbol in _reference_symbols_for_address(reference_manifest, value):
        key = _format_reference_key(symbol)
        if key == primary_key or key in alternate_keys:
            continue
        alternate_keys.append(key)
    for symbol, offset in _reference_offsets_for_address(reference_manifest, value):
        key = _format_reference_key(symbol, offset)
        if key == primary_key or key in alternate_keys:
            continue
        alternate_keys.append(key)
    return tuple(alternate_keys)


def _function_symbols_by_name(
    manifest: FunctionSymbolManifest,
) -> dict[str, FunctionSymbol]:
    return {
        name: symbol
        for symbol in manifest.functions
        for name in (symbol.name, *symbol.aliases)
    }


def _format_f32_constant(data: bytes, offset: int, value: int | None = None) -> tuple[str, str] | None:
    if not (0 <= offset <= len(data) - 4):
        return None
    raw = data[offset : offset + 4]
    bits = struct.unpack("<I", raw)[0]
    number = struct.unpack("<f", raw)[0]
    suffix = f"@0x{value:x}" if value is not None else ""
    return f"const:f32:{number:.9g}{suffix}", f"const:f32:{bits:08x}"


def _u32_points_into_range(
    data: bytes,
    offset: int,
    address_range: tuple[int, int],
) -> bool:
    value = _read_u32(data, offset)
    return value is not None and address_range[0] <= value < address_range[1]


def _format_symbol_reference(name: str, addend: int = 0) -> tuple[str, str]:
    canonical = _canonical_symbol_name(name)
    suffix = _format_addend_suffix(addend)
    return f"sym:{canonical}{suffix}", f"name:{canonical}{suffix}"


def _resolve_object_relocation(
    obj: CoffObject,
    symbol: CoffSymbol,
    addend: int | None,
    *,
    reference_manifest: ReferenceSymbolManifest | None = None,
) -> tuple[str, str | None, bool]:
    reference_symbol = _reference_symbol_for_symbol_name(reference_manifest, symbol.name)
    if reference_symbol is None and symbol.name.startswith("$L"):
        local_reference_symbol = _reference_symbol_for_local_label(
            reference_manifest,
            symbol.name,
            kind="function_alias",
        )
        # A manifest alias only supplies the canonical identity here. The
        # masked-operand audit still requires the bounded local code body to
        # match after relocation normalization; private label spelling alone
        # never proves a function alias.
        if (
            local_reference_symbol is not None
            and local_reference_symbol.kind == "function_alias"
            and (addend or 0) == 0
        ):
            text, _key = _format_symbol_reference(symbol.name)
            return text, _format_reference_key(local_reference_symbol), True
    if reference_symbol is not None:
        offset = addend or 0
        text, key = _format_symbol_reference(symbol.name, offset)
        explained = offset == 0 or (
            reference_symbol.size is not None and 0 <= offset < reference_symbol.size
        ) or (
            reference_symbol.size is not None
            and reference_symbol.allow_one_past
            and offset == reference_symbol.size
        )
        if offset != 0:
            key = _format_reference_key(reference_symbol, offset)
        else:
            key = _format_reference_key(reference_symbol)
        return text, key, explained

    # VC6 gives compiler-generated local initializer/destructor helpers names
    # such as _$E1. They are real function symbols, and their leading opcode
    # can otherwise be misread as a one-character C string (for example,
    # push imm32 starts with ASCII 'h'). Keep the symbol identity here; the
    # masked-operand audit verifies bounded local helpers by normalized code.
    if _is_function_symbol(symbol):
        text, key = _format_symbol_reference(symbol.name, addend or 0)
        return text, key, bool(_canonical_symbol_name(symbol.name))

    if symbol.section_number > 0:
        section = obj.sections[symbol.section_number - 1]
        candidates = [symbol.value]
        if addend is not None:
            candidates.extend([symbol.value + addend, addend])
        seen_offsets: set[int] = set()
        for offset in candidates:
            if offset in seen_offsets:
                continue
            seen_offsets.add(offset)
            text = _read_printable_c_string(section.data, offset)
            if text is not None:
                return f"str:{_quote_reference_string(text)}", f"str:{text}", True
            if section.name.startswith(".rdata") and (
                constant := _format_f32_constant(section.data, offset)
            ) is not None:
                return constant[0], constant[1], True
        text, key = _format_symbol_reference(symbol.name, addend or 0)
        return text, key, bool(_canonical_symbol_name(symbol.name))

    text, key = _format_symbol_reference(symbol.name, addend or 0)
    return text, key, bool(_canonical_symbol_name(symbol.name))


def _is_function_symbol(symbol: CoffSymbol) -> bool:
    return (
        symbol.section_number > 0
        and symbol.symbol_type & SYM_TYPE_FUNCTION != 0
        and symbol.storage_class in (IMAGE_SYM_CLASS_EXTERNAL, IMAGE_SYM_CLASS_STATIC)
    )


def _symbol_matches(symbol_name: str, wanted: str) -> bool:
    return wanted in symbol_name


def extract_object_function(
    obj: CoffObject,
    name: str | None = None,
    *,
    reference_manifest: ReferenceSymbolManifest | None = None,
) -> ObjectFunction:
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
    symbols_by_raw_index = {symbol.raw_index: symbol for symbol in obj.symbols}
    relocation_references: list[ObjectRelocationReference] = []
    for relocation in section.relocations:
        if not (target.value <= relocation.virtual_address < end):
            continue
        offset = relocation.virtual_address - target.value
        symbol = symbols_by_raw_index.get(relocation.symbol_index)
        if symbol is None:
            relocation_references.append(
                ObjectRelocationReference(
                    offset=offset,
                    symbol_name=f"<symbol#{relocation.symbol_index}>",
                    text=f"sym:<symbol#{relocation.symbol_index}>",
                    key=None,
                    explained=False,
                    addend=None,
                    symbol_offset=None,
                )
            )
            continue
        addend = _read_u32(section.data, relocation.virtual_address)
        text, key, explained = _resolve_object_relocation(
            obj,
            symbol,
            addend,
            reference_manifest=reference_manifest,
        )
        symbol_section = (
            obj.sections[symbol.section_number - 1]
            if symbol.section_number > 0
            else None
        )
        symbol_end = (
            min(
                (
                    sibling.value
                    for sibling in obj.symbols
                    if sibling.section_number == symbol.section_number
                    and sibling.value > symbol.value
                ),
                default=len(symbol_section.data),
            )
            if symbol_section is not None
            else None
        )
        canonical_symbol_name = _canonical_symbol_name(symbol.name)
        retain_local_symbol = (
            canonical_symbol_name.startswith(("$L", "$E"))
            and symbol_end is not None
        )
        relocation_references.append(
            ObjectRelocationReference(
                offset=offset,
                symbol_name=symbol.name,
                text=text,
                key=key,
                explained=explained,
                addend=addend,
                symbol_offset=(
                    symbol.value - target.value
                    if symbol.section_number == target.section_number
                    else None
                ),
                symbol_size=(
                    symbol_end - symbol.value
                    if symbol_end is not None
                    else None
                ),
                symbol_data=(
                    symbol_section.data[symbol.value : symbol_end]
                    if retain_local_symbol and symbol_section is not None
                    else None
                ),
                symbol_relocation_offsets=(
                    frozenset(
                        sibling_relocation.virtual_address - symbol.value
                        for sibling_relocation in symbol_section.relocations
                        if symbol.value
                        <= sibling_relocation.virtual_address
                        < symbol_end
                    )
                    if retain_local_symbol
                    and symbol_section is not None
                    and symbol_end is not None
                    else frozenset()
                ),
            )
        )
    return ObjectFunction(
        name=target.name,
        data=section.data[target.value : end].rstrip(PADDING_BYTES),
        relocation_offsets=frozenset(reference.offset for reference in relocation_references),
        relocation_references=tuple(relocation_references),
    )


@dataclass(frozen=True, slots=True)
class ImageSection:
    name: str
    start: int
    end: int
    characteristics: int


@dataclass(frozen=True, slots=True)
class LoadedImage:
    mapped: bytes
    image_base: int
    size_of_image: int
    imports_by_va: dict[int, str] = field(default_factory=dict)
    sections: tuple[ImageSection, ...] = ()

    def function_bytes(self, start_va: int, end_va: int) -> bytes:
        data = self.mapped[start_va - self.image_base : end_va - self.image_base]
        return data.rstrip(PADDING_BYTES)

    def section_for_va(self, va: int) -> ImageSection | None:
        for section in self.sections:
            if section.start <= va < section.end:
                return section
        return None


def load_image(path: Path, image_base: int) -> LoadedImage:
    import pefile

    pe = pefile.PE(data=path.read_bytes(), fast_load=True)
    imports_by_va: dict[int, str] = {}
    try:
        pe.parse_data_directories(
            directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]]
        )
    except Exception:
        pass
    for entry in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        dll_name = entry.dll.decode("ascii", errors="replace")
        for imported in entry.imports:
            if imported.address is None:
                continue
            if imported.name is not None:
                name = imported.name.decode("ascii", errors="replace")
            else:
                name = f"ordinal_{imported.ordinal}"
            imports_by_va[imported.address] = f"{dll_name}!{name}"
    sections = tuple(
        ImageSection(
            name=section.Name.rstrip(b"\x00").decode("ascii", errors="replace"),
            start=image_base + section.VirtualAddress,
            end=image_base
            + section.VirtualAddress
            + max(section.Misc_VirtualSize, section.SizeOfRawData),
            characteristics=section.Characteristics,
        )
        for section in pe.sections
    )
    return LoadedImage(
        mapped=pe.get_memory_mapped_image(ImageBase=image_base),
        image_base=image_base,
        size_of_image=pe.OPTIONAL_HEADER.SizeOfImage,
        imports_by_va=imports_by_va,
        sections=sections,
    )


def _resolve_image_reference(
    value: int,
    *,
    image: LoadedImage | None = None,
    manifest: FunctionSymbolManifest | None = None,
    reference_manifest: ReferenceSymbolManifest | None = None,
    prefer_rdata_float: bool = False,
    function_base: int = 0,
) -> MaskedReference:
    text: str
    key: str | None
    explained = False
    reference_symbol = _reference_symbol_by_address(reference_manifest).get(value)
    if reference_symbol is not None:
        text, key = _format_reference_symbol(reference_symbol)
        jump_table_entries = None
        audited_bytes = None
        normalized_code = None
        if (
            reference_symbol.kind == "jump_table"
            and reference_symbol.size is not None
            and image is not None
        ):
            jump_table_entries = _read_image_jump_table_entries(
                image,
                value,
                reference_symbol.size,
                relative_to=function_base,
            )
        if (
            reference_symbol.kind in CONTENT_AUDITED_REFERENCE_KINDS
            and reference_symbol.size is not None
            and image is not None
        ):
            audited_bytes = _read_bytes(
                image.mapped,
                value - image.image_base,
                reference_symbol.size,
            )
        if (
            reference_symbol.kind == "function_alias"
            and reference_symbol.size is not None
            and image is not None
        ):
            alias_bytes = _read_bytes(
                image.mapped,
                value - image.image_base,
                reference_symbol.size,
            )
            if alias_bytes is not None:
                normalized_code = normalize_function(
                    alias_bytes,
                    address_range=(
                        image.image_base,
                        image.image_base + image.size_of_image,
                    ),
                    base_address=value,
                )
        return MaskedReference(
            0,
            "",
            "image",
            value,
            f"{text}@0x{value:x}",
            key,
            True,
            alternate_keys=_reference_alternate_keys_for_address(
                reference_manifest,
                value,
                primary_key=key,
            ),
            jump_table_entries=jump_table_entries,
            audited_bytes=audited_bytes,
            normalized_code=normalized_code,
        )
    if manifest is not None:
        by_address = {symbol.address: symbol for symbol in manifest.functions}
        if value in by_address:
            symbol = by_address[value]
            text = f"fn:{symbol.name}@0x{value:x}"
            key = f"name:{symbol.name}"
            explained = True
            return MaskedReference(
                0,
                "",
                "image",
                value,
                text,
                key,
                explained,
                alternate_keys=tuple(f"name:{alias}" for alias in symbol.aliases),
            )
    if image is not None and value in image.imports_by_va:
        name = image.imports_by_va[value]
        canonical = _canonical_symbol_name(name.rsplit("!", 1)[-1])
        return MaskedReference(
            0,
            "",
            "image",
            value,
            f"import:{name}@0x{value:x}",
            f"name:{canonical}",
            True,
        )
    if image is not None and image.image_base <= value < image.image_base + len(image.mapped):
        range_references = _reference_offsets_for_address(reference_manifest, value)
        if range_references:
            symbol, addend = range_references[0]
            text, key = _format_reference_symbol(symbol, addend)
            return MaskedReference(
                0,
                "",
                "image",
                value,
                f"{text}@0x{value:x}",
                key,
                True,
                alternate_keys=tuple(
                    _format_reference_key(other_symbol, other_addend)
                    for other_symbol, other_addend in range_references[1:]
                ),
            )
        offset = value - image.image_base
        section = image.section_for_va(value)
        address_range = (image.image_base, image.image_base + image.size_of_image)
        looks_like_rdata_pointer = (
            section is not None
            and section.name == ".rdata"
            and _u32_points_into_range(image.mapped, offset, address_range)
        )
        if (
            prefer_rdata_float
            and section is not None
            and section.name == ".rdata"
            and not looks_like_rdata_pointer
            and (constant := _format_f32_constant(image.mapped, offset, value)) is not None
        ):
            text, key = constant
            return MaskedReference(0, "", "image", value, text, key, True)
        string = None if looks_like_rdata_pointer else _read_printable_c_string(image.mapped, offset)
        if string is not None:
            return MaskedReference(
                0,
                "",
                "image",
                value,
                f"str:{_quote_reference_string(string)}@0x{value:x}",
                f"str:{string}",
                True,
            )
        if (
            section is not None
            and section.name == ".rdata"
            and not looks_like_rdata_pointer
            and (constant := _format_f32_constant(image.mapped, offset, value)) is not None
        ):
            text, key = constant
            return MaskedReference(0, "", "image", value, text, key, True)
        return MaskedReference(
            0,
            "",
            "image",
            value,
            f"image+0x{offset:x}@0x{value:x}",
            f"addr:0x{value:x}",
            False,
        )
    return MaskedReference(0, "", "image", value, f"0x{value:x}", f"addr:0x{value:x}", False)


_OPERAND_SIZE_NAMES = {1: "byte", 2: "word", 4: "dword", 8: "qword", 10: "tword"}
_X87_F32_MEMORY_MNEMONICS = frozenset(
    (
        "fadd",
        "fcom",
        "fcomp",
        "fdiv",
        "fdivr",
        "fld",
        "fmul",
        "fst",
        "fstp",
        "fsub",
        "fsubr",
    )
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
    size = _OPERAND_SIZE_NAMES.get(operand.size, str(operand.size))
    segment = f"{insn.reg_name(mem.segment)}:" if mem.segment != 0 else ""
    return f"{size} {segment}[{'+'.join(parts)}]"


def _prefers_rdata_f32(insn, operand) -> bool:
    return operand.size == 4 and insn.mnemonic in _X87_F32_MEMORY_MNEMONICS


def disassemble_normalized_function(
    data: bytes,
    *,
    relocation_offsets: frozenset[int] | None = None,
    relocation_references: tuple[ObjectRelocationReference, ...] = (),
    address_range: tuple[int, int] | None = None,
    base_address: int = 0,
    image: LoadedImage | None = None,
    manifest: FunctionSymbolManifest | None = None,
    reference_manifest: ReferenceSymbolManifest | None = None,
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
    relocation_by_offset = {reference.offset: reference for reference in relocation_references}
    size = len(data)

    def is_masked_value(value: int) -> bool:
        return address_range is not None and address_range[0] <= value < address_range[1]

    def relocation_in_span(start: int, byte_count: int) -> ObjectRelocationReference | None:
        for rel_offset in range(start, start + max(byte_count, 1)):
            if rel_offset in relocation_by_offset:
                return relocation_by_offset[rel_offset]
        return None

    def relocated_local_branch_target(reference: ObjectRelocationReference | None) -> int | None:
        if reference is None or reference.symbol_offset is None:
            return None
        target_offset = reference.symbol_offset + (reference.addend or 0)
        if 0 <= target_offset < size:
            return target_offset
        return None

    def relocated_reference(
        reference: ObjectRelocationReference | None,
        *,
        operand_index: int,
        kind: str,
    ) -> MaskedReference:
        jump_table_entries = None
        alternate_jump_table_entries: tuple[tuple[int, ...], ...] = ()
        audited_bytes = None
        local_data_bytes = None
        normalized_code = None
        reference_symbol = None
        local_reference_symbol = None
        if reference is not None:
            reference_symbol = _reference_symbol_for_symbol_name(
                reference_manifest,
                reference.symbol_name,
            )
            local_reference_symbol = _reference_symbol_for_local_label(
                reference_manifest,
                reference.symbol_name,
                kind="jump_table",
            )
        local_symbol_name = (
            _canonical_symbol_name(reference.symbol_name)
            if reference is not None
            else ""
        )
        if reference is not None and local_symbol_name.startswith(("$L", "$E")):
            symbol_addend = reference.addend or 0
            local_offset = (
                reference.symbol_offset + symbol_addend
                if reference.symbol_offset is not None
                else None
            )
            local_symbol_size = None
            if reference.symbol_size is not None:
                local_symbol_size = reference.symbol_size - symbol_addend
                if local_symbol_size <= 0:
                    local_symbol_size = None
            manifest_table_size = (
                local_reference_symbol.size
                if local_reference_symbol is not None
                and local_reference_symbol.kind == "jump_table"
                else None
            )
            table_sizes = tuple(
                dict.fromkeys(
                    size
                    for size in (local_symbol_size, manifest_table_size)
                    if size is not None
                )
            )
            if local_offset is not None and local_symbol_name.startswith("$L"):
                table_options: list[tuple[int, ...]] = []
                for table_size in table_sizes:
                    entries = _read_object_jump_table_entries(
                        data,
                        local_offset,
                        relocation_by_offset,
                        byte_count=table_size,
                    )
                    if entries is not None and entries not in table_options:
                        table_options.append(entries)
                unbounded_entries = _read_object_jump_table_entries(
                    data, local_offset, relocation_by_offset
                )
                if (
                    unbounded_entries is not None
                    and unbounded_entries not in table_options
                ):
                    table_options.append(unbounded_entries)
                if table_options:
                    jump_table_entries = table_options[0]
                    alternate_jump_table_entries = tuple(table_options[1:])
            if local_offset is not None and 0 <= local_offset < len(data):
                local_end = (
                    min(len(data), local_offset + local_symbol_size)
                    if local_symbol_size is not None
                    else len(data)
                )
                local_data_bytes = data[local_offset:local_end]
                if local_symbol_size is not None:
                    local_relocation_offsets = frozenset(
                        offset - local_offset
                        for offset in relocation_by_offset
                        if local_offset <= offset < local_end
                    )
                    normalized_code = normalize_function(
                        local_data_bytes,
                        relocation_offsets=local_relocation_offsets,
                        address_range=address_range,
                    )
            elif reference.symbol_data is not None and 0 <= symbol_addend < len(
                reference.symbol_data
            ):
                local_data_bytes = reference.symbol_data[symbol_addend:]
                local_relocation_offsets = frozenset(
                    offset - symbol_addend
                    for offset in reference.symbol_relocation_offsets
                    if offset >= symbol_addend
                )
                normalized_code = normalize_function(
                    local_data_bytes,
                    relocation_offsets=local_relocation_offsets,
                    address_range=address_range,
                )
        if reference is not None:
            if (
                reference_symbol is not None
                and reference_symbol.kind in CONTENT_AUDITED_REFERENCE_KINDS
                and reference_symbol.size is not None
            ):
                audited_bytes = _read_object_reference_bytes(
                    data,
                    reference,
                    reference_symbol.size,
                )
        if reference is None:
            return MaskedReference(
                operand_index=operand_index,
                kind=kind,
                source="reloc",
                value=None,
                text="sym:<unknown>",
                key=None,
                explained=False,
            )
        return MaskedReference(
            operand_index=operand_index,
            kind=kind,
            source="reloc",
            value=None,
            text=reference.text,
            key=reference.key,
            explained=reference.explained,
            jump_table_entries=jump_table_entries,
            alternate_jump_table_entries=alternate_jump_table_entries,
            audited_bytes=audited_bytes,
            local_data_bytes=local_data_bytes,
            normalized_code=normalized_code,
        )

    def image_reference(
        value: int,
        *,
        operand_index: int,
        kind: str,
        prefer_rdata_float: bool = False,
    ) -> MaskedReference:
        resolved = _resolve_image_reference(
            value,
            image=image,
            manifest=manifest,
            reference_manifest=reference_manifest,
            prefer_rdata_float=prefer_rdata_float,
            function_base=base_address,
        )
        return MaskedReference(
            operand_index=operand_index,
            kind=kind,
            source=resolved.source,
            value=value,
            text=resolved.text,
            key=resolved.key,
            explained=resolved.explained,
            alternate_keys=resolved.alternate_keys,
            jump_table_entries=resolved.jump_table_entries,
            alternate_jump_table_entries=resolved.alternate_jump_table_entries,
            audited_bytes=resolved.audited_bytes,
            local_data_bytes=resolved.local_data_bytes,
            normalized_code=resolved.normalized_code,
        )

    lines: list[DisassemblyLine] = []
    for insn in md.disasm(data, base_address):
        insn_offset = insn.address - base_address
        is_branch = capstone.CS_GRP_JUMP in insn.groups or capstone.CS_GRP_CALL in insn.groups
        imm_relocation = relocation_in_span(
            insn_offset + insn.imm_offset,
            insn.imm_size,
        ) if insn.imm_offset else None
        imm_masked = any(
            insn_offset + rel_offset in relocation_offsets
            for rel_offset in range(insn.imm_offset, insn.imm_offset + max(insn.imm_size, 1))
        ) if insn.imm_offset else False
        disp_relocation = relocation_in_span(
            insn_offset + insn.disp_offset,
            insn.disp_size,
        ) if insn.disp_offset else None
        disp_masked = any(
            insn_offset + rel_offset in relocation_offsets
            for rel_offset in range(insn.disp_offset, insn.disp_offset + max(insn.disp_size, 1))
        ) if insn.disp_offset else False

        operands: list[str] = []
        masked_references: list[MaskedReference] = []
        for operand_index, operand in enumerate(insn.operands):
            if operand.type == capstone.x86.X86_OP_REG:
                operands.append(insn.reg_name(operand.reg))
            elif operand.type == capstone.x86.X86_OP_IMM:
                value = operand.imm
                target_offset = value - base_address
                # a relocated branch target is external even when the zero
                # displacement happens to land inside the function
                if imm_masked:
                    local_target = (
                        relocated_local_branch_target(imm_relocation)
                        if is_branch
                        else None
                    )
                    if local_target is not None:
                        operands.append(f"L{local_target:x}")
                    else:
                        operands.append("ADDR")
                        masked_references.append(
                            relocated_reference(
                                imm_relocation,
                                operand_index=operand_index,
                                kind="imm",
                            )
                        )
                elif is_branch and 0 <= target_offset < size:
                    operands.append(f"L{target_offset:x}")
                elif is_masked_value(value):
                    operands.append("ADDR")
                    masked_references.append(
                        image_reference(value, operand_index=operand_index, kind="imm")
                    )
                else:
                    operands.append(f"0x{value:x}" if value >= 0 else f"-0x{-value:x}")
            elif operand.type == capstone.x86.X86_OP_MEM:
                masked = disp_masked or is_masked_value(operand.mem.disp)
                operands.append(_format_memory_operand(insn, operand, masked))
                if disp_masked:
                    masked_references.append(
                        relocated_reference(
                            disp_relocation,
                            operand_index=operand_index,
                            kind="disp",
                        )
                    )
                elif is_masked_value(operand.mem.disp):
                    masked_references.append(
                        image_reference(
                            operand.mem.disp,
                            operand_index=operand_index,
                            kind="disp",
                            prefer_rdata_float=_prefers_rdata_f32(insn, operand),
                        )
                    )
            else:
                operands.append("?")
        lines.append(
            DisassemblyLine(
                offset=insn_offset,
                address=insn.address,
                text=f"{insn.mnemonic} {', '.join(operands)}".strip(),
                masked_references=tuple(masked_references),
            )
        )
    return _strip_trailing_unreferenced_lines(tuple(lines))


def _strip_trailing_unreferenced_lines(
    lines: tuple[DisassemblyLine, ...],
) -> tuple[DisassemblyLine, ...]:
    """Drop non-code tail bytes after an untargeted terminal ret."""
    for index, candidate in enumerate(lines[:-1]):
        if not candidate.text.startswith("ret"):
            continue
        trim_start = index + 1
        tail_offsets = {line.offset for line in lines[trim_start:]}
        for line in lines[:trim_start]:
            targets = {int(match.group(1), 16) for match in BRANCH_TARGET_RE.finditer(line.text)}
            for reference in line.masked_references:
                targets.update(reference.jump_table_entries or ())
            if targets & tail_offsets:
                break
        else:
            return lines[:trim_start]
    return lines


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


def _reference_status(
    target_references: tuple[MaskedReference, ...],
    candidate_references: tuple[MaskedReference, ...],
) -> str:
    def reference_key_options(reference: MaskedReference) -> frozenset[str]:
        keys = [key for key in (reference.key, *reference.alternate_keys) if key is not None]
        return frozenset(keys)

    def is_local_jump_table(
        target: MaskedReference, candidate: MaskedReference
    ) -> bool:
        return (
            target.text.startswith("jump_table:")
            and candidate.source == "reloc"
            and candidate.text.startswith("sym:$L")
        )

    def is_content_audited_reference(
        target: MaskedReference, candidate: MaskedReference
    ) -> bool:
        return (
            target.text.startswith(("data_blob:", "lookup_table:"))
            and candidate.source == "reloc"
        )

    def is_local_function_alias(
        target: MaskedReference, candidate: MaskedReference
    ) -> bool:
        return (
            target.text.startswith("function_alias:")
            and candidate.source == "reloc"
            and candidate.text.startswith(("sym:$L", "sym:$E"))
        )

    def jump_table_entries_match(
        target: MaskedReference, candidate: MaskedReference
    ) -> bool:
        if not is_local_jump_table(target, candidate):
            return False
        target_options = (
            *((target.jump_table_entries,) if target.jump_table_entries is not None else ()),
            *target.alternate_jump_table_entries,
        )
        candidate_options = (
            *((candidate.jump_table_entries,) if candidate.jump_table_entries is not None else ()),
            *candidate.alternate_jump_table_entries,
        )
        return bool(set(target_options) & set(candidate_options))

    def audited_bytes_match(
        target: MaskedReference, candidate: MaskedReference
    ) -> bool:
        if not is_content_audited_reference(target, candidate):
            return False
        if target.audited_bytes is None:
            return False
        if candidate.audited_bytes is not None:
            return target.audited_bytes == candidate.audited_bytes
        if candidate.local_data_bytes is None:
            return False
        byte_count = len(target.audited_bytes)
        return (
            len(candidate.local_data_bytes) >= byte_count
            and target.audited_bytes == candidate.local_data_bytes[:byte_count]
        )

    def has_candidate_audited_bytes(candidate: MaskedReference, byte_count: int) -> bool:
        return candidate.audited_bytes is not None or (
            candidate.local_data_bytes is not None
            and len(candidate.local_data_bytes) >= byte_count
        )

    def function_alias_code_matches(
        target: MaskedReference, candidate: MaskedReference
    ) -> bool:
        return (
            is_local_function_alias(target, candidate)
            and target.normalized_code is not None
            and target.normalized_code == candidate.normalized_code
        )

    def references_match(target: MaskedReference, candidate: MaskedReference) -> bool:
        if is_local_jump_table(target, candidate):
            return jump_table_entries_match(target, candidate)
        if is_content_audited_reference(target, candidate):
            return audited_bytes_match(target, candidate)
        if is_local_function_alias(target, candidate):
            return function_alias_code_matches(target, candidate)
        target_keys = reference_key_options(target)
        candidate_keys = reference_key_options(candidate)
        return bool(target_keys & candidate_keys)

    target_keys = tuple(reference_key_options(reference) for reference in target_references)
    candidate_keys = tuple(reference_key_options(reference) for reference in candidate_references)
    all_explained = all(
        reference.explained for reference in (*target_references, *candidate_references)
    )
    if (
        len(target_keys) == len(candidate_keys)
        and all(
            references_match(target, candidate)
            for target, candidate in zip(target_references, candidate_references)
        )
        and all_explained
    ):
        return "ok"
    has_unverified_jump_table = any(
        is_local_jump_table(target, candidate)
        and not jump_table_entries_match(target, candidate)
        and (
            target.jump_table_entries is None
            or candidate.jump_table_entries is None
        )
        for target, candidate in zip(target_references, candidate_references)
    )
    has_unverified_content = any(
        is_content_audited_reference(target, candidate)
        and not audited_bytes_match(target, candidate)
        and (
            target.audited_bytes is None
            or not has_candidate_audited_bytes(candidate, len(target.audited_bytes))
        )
        for target, candidate in zip(target_references, candidate_references)
    )
    has_unverified_function_alias = any(
        is_local_function_alias(target, candidate)
        and not function_alias_code_matches(target, candidate)
        and (
            target.normalized_code is None
            or candidate.normalized_code is None
        )
        for target, candidate in zip(target_references, candidate_references)
    )
    if (
        not all_explained
        or any(not keys for keys in (*target_keys, *candidate_keys))
        or has_unverified_jump_table
        or has_unverified_content
        or has_unverified_function_alias
    ):
        return "unresolved"
    return "mismatch"


def audit_masked_operands(
    target_disassembly: tuple[DisassemblyLine, ...],
    candidate_disassembly: tuple[DisassemblyLine, ...],
) -> MaskedOperandAudit:
    matcher = difflib.SequenceMatcher(
        a=tuple(line.text for line in target_disassembly),
        b=tuple(line.text for line in candidate_disassembly),
        autojunk=False,
    )
    entries: list[MaskedOperandAuditEntry] = []
    for tag, a0, a1, b0, b1 in matcher.get_opcodes():
        if tag != "equal":
            continue
        for target_index, candidate_index in zip(range(a0, a1), range(b0, b1)):
            target_line = target_disassembly[target_index]
            candidate_line = candidate_disassembly[candidate_index]
            if not target_line.masked_references and not candidate_line.masked_references:
                continue
            entries.append(
                MaskedOperandAuditEntry(
                    target_index=target_index,
                    candidate_index=candidate_index,
                    target_offset=target_line.offset,
                    candidate_offset=candidate_line.offset,
                    target_address=target_line.address,
                    candidate_address=candidate_line.address,
                    instruction=target_line.text,
                    target_references=target_line.masked_references,
                    candidate_references=candidate_line.masked_references,
                    status=_reference_status(
                        target_line.masked_references,
                        candidate_line.masked_references,
                    ),
                )
            )
    return MaskedOperandAudit(tuple(entries))


def match_function(
    target_data: bytes,
    candidate: ObjectFunction,
    *,
    image: LoadedImage,
    target_va: int,
    manifest: FunctionSymbolManifest | None = None,
    reference_manifest: ReferenceSymbolManifest | None = None,
) -> MatchResult:
    address_range = (image.image_base, image.image_base + image.size_of_image)
    target_disassembly = disassemble_normalized_function(
        target_data,
        address_range=address_range,
        base_address=target_va,
        image=image,
        manifest=manifest,
        reference_manifest=reference_manifest,
    )
    candidate_disassembly = disassemble_normalized_function(
        candidate.data,
        relocation_offsets=candidate.relocation_offsets,
        relocation_references=candidate.relocation_references,
        address_range=address_range,
        image=image,
        manifest=manifest,
        reference_manifest=reference_manifest,
    )
    target_lines = tuple(line.text for line in target_disassembly)
    candidate_lines = tuple(line.text for line in candidate_disassembly)
    ratio = difflib.SequenceMatcher(a=target_lines, b=candidate_lines, autojunk=False).ratio()
    prefix_instructions = common_prefix_length(target_lines, candidate_lines)
    return MatchResult(
        ratio=ratio,
        prefix_instructions=prefix_instructions,
        target_lines=target_lines,
        candidate_lines=candidate_lines,
        target_disassembly=target_disassembly,
        candidate_disassembly=candidate_disassembly,
        masked_operand_audit=audit_masked_operands(target_disassembly, candidate_disassembly),
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
    by_name = _function_symbols_by_name(manifest)
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
    reference_manifest = load_default_reference_symbol_manifest()
    candidate = extract_object_function(
        obj,
        symbol_name or function_name,
        reference_manifest=reference_manifest,
    )
    start, end = resolve_function_extent(manifest, function_name, end_va)
    image = load_image(image_path, manifest.image_base)
    return match_function(
        image.function_bytes(start, end),
        candidate,
        image=image,
        target_va=start,
        manifest=manifest,
        reference_manifest=reference_manifest,
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
    reference_manifest = load_default_reference_symbol_manifest()
    candidate = extract_object_function(
        obj,
        symbol_name or function_name,
        reference_manifest=reference_manifest,
    )
    start, end = resolve_function_extent(manifest, function_name, end_va)
    image = load_image(image_path, manifest.image_base)
    target_data = image.function_bytes(start, end)
    address_range = (image.image_base, image.image_base + image.size_of_image)
    return MatchDump(
        target_lines=disassemble_normalized_function(
            target_data,
            address_range=address_range,
            base_address=start,
            image=image,
            manifest=manifest,
            reference_manifest=reference_manifest,
        ),
        candidate_lines=disassemble_normalized_function(
            candidate.data,
            relocation_offsets=candidate.relocation_offsets,
            relocation_references=candidate.relocation_references,
            address_range=address_range,
            image=image,
            manifest=manifest,
            reference_manifest=reference_manifest,
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
    masked_ok: int = 0
    masked_unresolved: int = 0
    masked_mismatches: int = 0
    error: str | None = None

    @property
    def state(self) -> str:
        if self.ratio is None:
            return "error"
        if (
            self.ratio == 1.0
            and self.masked_unresolved == 0
            and self.masked_mismatches == 0
        ):
            return "match"
        if self.ratio == 1.0:
            return "audit"
        return "wip"


@dataclass(frozen=True, slots=True)
class ScratchMaskedOperandIssue:
    config: ScratchConfig
    address: int
    ratio: float
    entry: MaskedOperandAuditEntry


@dataclass(frozen=True, slots=True)
class ScratchAuditFailure:
    config: ScratchConfig
    address: int
    error: str


def load_scratch_config(directory: Path) -> ScratchConfig:
    import shlex

    values: dict[str, str] = {}
    for token in shlex.split((directory / "scratch.conf").read_text()):
        key, _, value = token.partition("=")
        if value:
            values[key] = value
    if "FUNCTION" not in values:
        raise ValueError(f"{directory}/scratch.conf must set FUNCTION")
    if "MATCH_ARGS" in values:
        raise ValueError(
            f"{directory}/scratch.conf MATCH_ARGS is not supported; use END=... and SYMBOL=..."
        )
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


def _mtime_ns(path: Path) -> int | None:
    return path.stat().st_mtime_ns if path.exists() else None


class _ScratchIncludeResolver:
    """Resolve each local include edge once during a status or audit sweep."""

    def __init__(self, match_root: Path) -> None:
        self.include_dir = match_root / "include"
        self._direct_dependencies: dict[tuple[Path, bool], tuple[Path, ...]] = {}

    def direct_dependencies(
        self, including_path: Path, *, source: bool
    ) -> tuple[Path, ...]:
        cache_key = (including_path, source)
        if cache_key in self._direct_dependencies:
            return self._direct_dependencies[cache_key]

        try:
            text = including_path.read_text(encoding="latin1")
        except OSError:
            self._direct_dependencies[cache_key] = ()
            return ()

        dependencies: list[Path] = []
        seen: set[Path] = set()
        for match in LOCAL_INCLUDE_RE.finditer(text):
            include_name = Path(match.group(1).replace("\\", "/"))
            candidates = [self.include_dir / include_name]
            if not source:
                candidates.insert(0, including_path.parent / include_name)
            dependency = next((path for path in candidates if path.is_file()), None)
            if dependency is None:
                continue
            dependency = dependency.resolve()
            if dependency in seen:
                continue
            seen.add(dependency)
            dependencies.append(dependency)

        resolved = tuple(dependencies)
        self._direct_dependencies[cache_key] = resolved
        return resolved


def _scratch_include_headers(
    config: ScratchConfig,
    match_root: Path,
    *,
    resolver: _ScratchIncludeResolver | None = None,
) -> tuple[Path, ...]:
    """Return only local headers transitively included by one scratch.

    VC6 searches the directory of an included header before the configured
    project include directory. The scratch source itself is copied into its
    build directory, so its project headers resolve through ``match/include``.
    """
    resolver = resolver or _ScratchIncludeResolver(match_root)
    source = config.directory / "scratch.cpp"
    pending = [source]
    visited = {source}
    headers: set[Path] = set()

    while pending:
        including_path = pending.pop()
        for dependency in resolver.direct_dependencies(
            including_path, source=including_path == source
        ):
            if dependency in visited:
                continue
            visited.add(dependency)
            headers.add(dependency)
            pending.append(dependency)

    return tuple(sorted(headers))


def _scratch_compile_argv(config: ScratchConfig, match_root: Path) -> tuple[str, ...]:
    import shlex

    return (
        str(match_root / "cl.sh"),
        "/c",
        *shlex.split(config.cflags),
        "scratch.cpp",
    )


def _scratch_build_dependencies(
    config: ScratchConfig,
    match_root: Path,
    *,
    include_resolver: _ScratchIncludeResolver | None = None,
) -> tuple[Path, ...]:
    compiler_exe = match_root / "compilers" / config.compiler / "Bin" / "CL.EXE"
    return (
        config.directory / "scratch.cpp",
        config.directory / "scratch.conf",
        match_root / "cl.sh",
        compiler_exe,
        *_scratch_include_headers(config, match_root, resolver=include_resolver),
    )


def _scratch_build_key(
    config: ScratchConfig,
    match_root: Path,
    *,
    include_resolver: _ScratchIncludeResolver | None = None,
) -> dict:
    return {
        "compiler": config.compiler,
        "argv": list(_scratch_compile_argv(config, match_root)),
        "dependencies": [
            [str(path.relative_to(match_root) if path.is_relative_to(match_root) else path), _mtime_ns(path)]
            for path in _scratch_build_dependencies(
                config, match_root, include_resolver=include_resolver
            )
        ],
    }


def _scratch_object_is_current(
    obj_path: Path,
    config: ScratchConfig,
    match_root: Path,
    *,
    include_resolver: _ScratchIncludeResolver | None = None,
) -> bool:
    if not obj_path.exists():
        return False

    obj_mtime = obj_path.stat().st_mtime_ns
    for dependency in _scratch_build_dependencies(
        config, match_root, include_resolver=include_resolver
    ):
        dependency_mtime = _mtime_ns(dependency)
        if dependency_mtime is None or dependency_mtime > obj_mtime:
            return False

    build_key_path = obj_path.parent / "scratch-build.json"
    if not build_key_path.exists():
        return False

    try:
        cached = json.loads(build_key_path.read_text())
    except (json.JSONDecodeError, OSError):
        return False
    return cached.get("key") == _scratch_build_key(
        config, match_root, include_resolver=include_resolver
    )


def _store_scratch_build_key(
    obj_path: Path,
    config: ScratchConfig,
    match_root: Path,
    *,
    include_resolver: _ScratchIncludeResolver | None = None,
) -> None:
    (obj_path.parent / "scratch-build.json").write_text(
        json.dumps(
            {
                "key": _scratch_build_key(
                    config, match_root, include_resolver=include_resolver
                )
            }
        )
    )


def _format_cl_failure(
    *,
    returncode: int,
    stdout: str,
    stderr: str,
    obj_path: Path,
    source_name: str,
    context: str | None = None,
) -> str:
    """Explain CL failures, including VC6's diagnostic-free ICE path."""
    label = "cl failed" if context is None else f"cl failed for {context}"
    reasons: list[str] = []
    if returncode != 0:
        reasons.append(f"exit code {returncode}")
    if not obj_path.exists():
        reasons.append(f"{obj_path.name} was not produced")
    suffix = f" ({'; '.join(reasons)})" if reasons else ""

    output = f"{stdout}{stderr}".rstrip()
    output_lines = [line.strip() for line in output.splitlines() if line.strip()]
    meaningful_output = [line for line in output_lines if line != source_name]
    if meaningful_output:
        return f"{label}{suffix}:\n{output}"

    ice_hint = (
        "no compiler diagnostics beyond the source-file echo; VC6 may have hit "
        "an internal compiler error. Rerun the same cl.sh command with "
        "WIBO_DEBUG=1 to inspect the guest exception"
    )
    if output:
        return f"{label}{suffix}:\n{output}\n{ice_hint}"
    return f"{label}{suffix}:\n{ice_hint}"


def compile_scratch(
    config: ScratchConfig,
    match_root: Path = DEFAULT_MATCH_ROOT,
    *,
    include_resolver: _ScratchIncludeResolver | None = None,
) -> Path:
    """Compile scratch.cpp with cl.sh when the object is missing or stale."""
    import os
    import shutil
    import subprocess

    source = config.directory / "scratch.cpp"
    validate_scratch_source(source)
    build_dir = config.directory / "build"
    obj_path = build_dir / "scratch.obj"
    if _scratch_object_is_current(
        obj_path, config, match_root, include_resolver=include_resolver
    ):
        return obj_path

    build_dir.mkdir(exist_ok=True)
    shutil.copy(source, build_dir / "scratch.cpp")
    completed = subprocess.run(
        list(_scratch_compile_argv(config, match_root)),
        cwd=build_dir,
        env={**os.environ, "MSVC_VER": config.compiler},
        capture_output=True,
        text=True,
    )
    if completed.returncode != 0 or not obj_path.exists():
        raise RuntimeError(
            _format_cl_failure(
                returncode=completed.returncode,
                stdout=completed.stdout,
                stderr=completed.stderr,
                obj_path=obj_path,
                source_name=source.name,
            )
        )
    _store_scratch_build_key(
        obj_path, config, match_root, include_resolver=include_resolver
    )
    return obj_path


def run_scratch_match(
    *,
    directory: Path,
    image_path: Path,
    manifest: FunctionSymbolManifest,
    match_root: Path = DEFAULT_MATCH_ROOT,
) -> MatchResult:
    """Compile and match one scratch through the same path used by status."""
    config = load_scratch_config(directory)
    obj_path = compile_scratch(config, match_root)
    return run_match(
        obj_path=obj_path,
        function_name=config.function,
        image_path=image_path,
        manifest=manifest,
        symbol_name=config.symbol,
        end_va=config.end_va,
    )


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
        raise RuntimeError(
            _format_cl_failure(
                returncode=completed.returncode,
                stdout=completed.stdout,
                stderr=completed.stderr,
                obj_path=obj_path,
                source_name=source_path.name,
                context=case.name,
            )
        )
    obj = parse_coff_object(obj_path.read_bytes())
    function = extract_object_function(obj, case.symbol)
    return IdiomResult(
        case=case,
        object_path=obj_path,
        instructions=normalize_function(function.data, relocation_offsets=function.relocation_offsets),
    )


# bump when the cache schema changes; matcher source mtime handles scoring edits
CACHE_VERSION = 9


def _masked_reference_cache_payload(reference: MaskedReference) -> dict:
    return {
        "operand_index": reference.operand_index,
        "kind": reference.kind,
        "source": reference.source,
        "value": reference.value,
        "text": reference.text,
        "key": reference.key,
        "explained": reference.explained,
        "alternate_keys": list(reference.alternate_keys),
        "jump_table_entries": (
            list(reference.jump_table_entries)
            if reference.jump_table_entries is not None
            else None
        ),
        "alternate_jump_table_entries": [
            list(entries) for entries in reference.alternate_jump_table_entries
        ],
        "audited_bytes": (
            reference.audited_bytes.hex()
            if reference.audited_bytes is not None
            else None
        ),
        "local_data_bytes": (
            reference.local_data_bytes.hex()
            if reference.local_data_bytes is not None
            else None
        ),
        "normalized_code": (
            list(reference.normalized_code)
            if reference.normalized_code is not None
            else None
        ),
    }


def _masked_reference_from_cache(payload: dict) -> MaskedReference:
    return MaskedReference(
        operand_index=payload["operand_index"],
        kind=payload["kind"],
        source=payload["source"],
        value=payload["value"],
        text=payload["text"],
        key=payload["key"],
        explained=payload["explained"],
        alternate_keys=tuple(payload["alternate_keys"]),
        jump_table_entries=(
            tuple(payload["jump_table_entries"])
            if payload["jump_table_entries"] is not None
            else None
        ),
        alternate_jump_table_entries=tuple(
            tuple(entries) for entries in payload["alternate_jump_table_entries"]
        ),
        audited_bytes=(
            bytes.fromhex(payload["audited_bytes"])
            if payload["audited_bytes"] is not None
            else None
        ),
        local_data_bytes=(
            bytes.fromhex(payload["local_data_bytes"])
            if payload["local_data_bytes"] is not None
            else None
        ),
        normalized_code=(
            tuple(payload["normalized_code"])
            if payload["normalized_code"] is not None
            else None
        ),
    )


def _masked_audit_cache_payload(audit: MaskedOperandAudit) -> list[dict]:
    return [
        {
            "target_index": entry.target_index,
            "candidate_index": entry.candidate_index,
            "target_offset": entry.target_offset,
            "candidate_offset": entry.candidate_offset,
            "target_address": entry.target_address,
            "candidate_address": entry.candidate_address,
            "instruction": entry.instruction,
            "target_references": [
                _masked_reference_cache_payload(reference)
                for reference in entry.target_references
            ],
            "candidate_references": [
                _masked_reference_cache_payload(reference)
                for reference in entry.candidate_references
            ],
            "status": entry.status,
        }
        for entry in audit.entries
    ]


def _masked_audit_from_cache(payload: list[dict]) -> MaskedOperandAudit:
    return MaskedOperandAudit(
        tuple(
            MaskedOperandAuditEntry(
                target_index=entry["target_index"],
                candidate_index=entry["candidate_index"],
                target_offset=entry["target_offset"],
                candidate_offset=entry["candidate_offset"],
                target_address=entry["target_address"],
                candidate_address=entry["candidate_address"],
                instruction=entry["instruction"],
                target_references=tuple(
                    _masked_reference_from_cache(reference)
                    for reference in entry["target_references"]
                ),
                candidate_references=tuple(
                    _masked_reference_from_cache(reference)
                    for reference in entry["candidate_references"]
                ),
                status=entry["status"],
            )
            for entry in payload
        )
    )


def _function_manifest_cache_digest(manifest: FunctionSymbolManifest) -> str:
    """Hash the manifest fields that affect target extents and reference audits."""
    payload = {
        "image_base": manifest.image_base,
        "functions": [
            [symbol.address, symbol.name, list(symbol.aliases)]
            for symbol in manifest.functions
        ],
    }
    encoded = json.dumps(payload, separators=(",", ":"), sort_keys=True).encode()
    return hashlib.sha256(encoded).hexdigest()


def _scratch_cache_key(
    config: ScratchConfig,
    image_path: Path,
    match_root: Path = DEFAULT_MATCH_ROOT,
    *,
    manifest_digest: str,
    include_resolver: _ScratchIncludeResolver | None = None,
) -> dict:
    return {
        "version": CACHE_VERSION,
        "build": _scratch_build_key(
            config, match_root, include_resolver=include_resolver
        ),
        "match": {
            "function": config.function,
            "end_va": config.end_va,
            "symbol": config.symbol,
        },
        "image_mtime": _mtime_ns(image_path),
        "matcher_mtime": _mtime_ns(Path(__file__)),
        "function_manifest": manifest_digest,
        "reference_manifest_mtime": _mtime_ns(DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH),
    }


def _load_cached_match(
    config: ScratchConfig,
    image_path: Path,
    match_root: Path = DEFAULT_MATCH_ROOT,
    *,
    manifest_digest: str,
    include_resolver: _ScratchIncludeResolver | None = None,
) -> tuple[dict, MaskedOperandAudit] | None:
    import json

    cache_path = config.directory / "build/match-cache.json"
    if not cache_path.exists():
        return None
    try:
        cached = json.loads(cache_path.read_text())
    except (json.JSONDecodeError, OSError):
        return None
    if cached.get("key") != _scratch_cache_key(
        config,
        image_path,
        match_root,
        manifest_digest=manifest_digest,
        include_resolver=include_resolver,
    ):
        return None
    status = cached.get("status")
    audit_payload = cached.get("masked_operand_audit")
    if not isinstance(status, dict) or not isinstance(audit_payload, list):
        return None
    try:
        audit = _masked_audit_from_cache(audit_payload)
    except (KeyError, TypeError, ValueError):
        return None
    return status, audit


def _load_cached_status(
    config: ScratchConfig,
    image_path: Path,
    match_root: Path = DEFAULT_MATCH_ROOT,
    *,
    manifest_digest: str,
    include_resolver: _ScratchIncludeResolver | None = None,
) -> dict | None:
    cached = _load_cached_match(
        config,
        image_path,
        match_root,
        manifest_digest=manifest_digest,
        include_resolver=include_resolver,
    )
    return cached[0] if cached is not None else None


def _store_cached_status(
    config: ScratchConfig,
    image_path: Path,
    status: dict,
    match_root: Path = DEFAULT_MATCH_ROOT,
    *,
    manifest_digest: str,
    audit: MaskedOperandAudit | None = None,
    include_resolver: _ScratchIncludeResolver | None = None,
) -> None:
    import json

    cache_path = config.directory / "build/match-cache.json"
    cache_path.parent.mkdir(exist_ok=True)
    cache_path.write_text(
        json.dumps(
            {
                "key": _scratch_cache_key(
                    config,
                    image_path,
                    match_root,
                    manifest_digest=manifest_digest,
                    include_resolver=include_resolver,
                ),
                "status": status,
                "masked_operand_audit": _masked_audit_cache_payload(
                    audit or MaskedOperandAudit()
                ),
            }
        )
    )


def _match_precompiled_scratch_config(
    config: ScratchConfig,
    *,
    image: LoadedImage,
    manifest: FunctionSymbolManifest,
    reference_manifest: ReferenceSymbolManifest,
) -> tuple[int, MatchResult]:
    start, end = resolve_function_extent(manifest, config.function, config.end_va)
    target_data = image.function_bytes(start, end)
    obj_path = config.directory / "build/scratch.obj"
    obj = parse_coff_object(obj_path.read_bytes())
    candidate = extract_object_function(
        obj,
        config.symbol or config.function,
        reference_manifest=reference_manifest,
    )
    result = match_function(
        target_data,
        candidate,
        image=image,
        target_va=start,
        manifest=manifest,
        reference_manifest=reference_manifest,
    )
    return len(target_data), result


def _scratch_status_fields(target_size: int, result: MatchResult) -> dict:
    return {
        "target_size": target_size,
        "ratio": result.ratio,
        "prefix_instructions": result.prefix_instructions,
        "target_instructions": len(result.target_lines),
        "candidate_instructions": len(result.candidate_lines),
        "masked_ok": result.masked_operand_audit.ok_count,
        "masked_unresolved": result.masked_operand_audit.unresolved_count,
        "masked_mismatches": result.masked_operand_audit.mismatch_count,
        "error": None,
    }


@dataclass(frozen=True, slots=True)
class _ScratchMatchTask:
    config: ScratchConfig
    address: int


@dataclass(frozen=True, slots=True)
class _ScratchMatchOutcome:
    config: ScratchConfig
    address: int
    fields: dict | None = None
    audit: MaskedOperandAudit | None = None
    error: str | None = None


@dataclass(frozen=True, slots=True)
class _MatchWorkerContext:
    image: LoadedImage
    manifest: FunctionSymbolManifest
    reference_manifest: ReferenceSymbolManifest


_MATCH_WORKER_CONTEXT: _MatchWorkerContext | None = None


def _initialize_match_worker(context: _MatchWorkerContext) -> None:
    global _MATCH_WORKER_CONTEXT
    _MATCH_WORKER_CONTEXT = context


def _match_precompiled_task_with_context(
    task: _ScratchMatchTask,
    context: _MatchWorkerContext,
) -> _ScratchMatchOutcome:
    try:
        target_size, result = _match_precompiled_scratch_config(
            task.config,
            image=context.image,
            manifest=context.manifest,
            reference_manifest=context.reference_manifest,
        )
    except (OSError, RuntimeError, ValueError) as error:
        return _ScratchMatchOutcome(
            config=task.config,
            address=task.address,
            error=_summarize_error(error),
        )
    return _ScratchMatchOutcome(
        config=task.config,
        address=task.address,
        fields=_scratch_status_fields(target_size, result),
        audit=result.masked_operand_audit,
    )


def _match_precompiled_task(task: _ScratchMatchTask) -> _ScratchMatchOutcome:
    if _MATCH_WORKER_CONTEXT is None:
        raise RuntimeError("parallel match worker was not initialized")
    return _match_precompiled_task_with_context(task, _MATCH_WORKER_CONTEXT)


def _collect_uncached_match_outcomes(
    uncached: list[tuple[ScratchConfig, int]],
    *,
    image: LoadedImage,
    image_path: Path,
    manifest: FunctionSymbolManifest,
    reference_manifest: ReferenceSymbolManifest,
    match_root: Path,
    manifest_digest: str,
    jobs: int,
    include_resolver: _ScratchIncludeResolver,
) -> list[_ScratchMatchOutcome]:
    """Compile in threads, then perform CPU-heavy matching in worker processes."""
    tasks = [_ScratchMatchTask(config, address) for config, address in uncached]

    def compile_task(task: _ScratchMatchTask) -> _ScratchMatchTask | _ScratchMatchOutcome:
        try:
            compile_scratch(
                task.config,
                match_root,
                include_resolver=include_resolver,
            )
        except (OSError, RuntimeError, ValueError) as error:
            return _ScratchMatchOutcome(
                config=task.config,
                address=task.address,
                error=_summarize_error(error),
            )
        return task

    if jobs == 1 or len(tasks) == 1:
        compiled = list(map(compile_task, tasks))
    else:
        with ThreadPoolExecutor(max_workers=min(jobs, len(tasks))) as executor:
            compiled = list(executor.map(compile_task, tasks))

    outcomes_by_directory = {
        item.config.directory: item
        for item in compiled
        if isinstance(item, _ScratchMatchOutcome)
    }
    match_tasks = [item for item in compiled if isinstance(item, _ScratchMatchTask)]
    context = _MatchWorkerContext(image, manifest, reference_manifest)
    if jobs == 1 or len(match_tasks) == 1:
        matched = [
            _match_precompiled_task_with_context(task, context) for task in match_tasks
        ]
    elif match_tasks:
        try:
            with ProcessPoolExecutor(
                max_workers=min(jobs, len(match_tasks)),
                initializer=_initialize_match_worker,
                initargs=(context,),
            ) as executor:
                matched = list(executor.map(_match_precompiled_task, match_tasks))
        except (NotImplementedError, PermissionError):
            # Some restricted sandboxes cannot query/create POSIX semaphores.
            matched = [
                _match_precompiled_task_with_context(task, context)
                for task in match_tasks
            ]
    else:
        matched = []

    for outcome in matched:
        outcomes_by_directory[outcome.config.directory] = outcome
        if outcome.fields is not None and outcome.audit is not None:
            _store_cached_status(
                outcome.config,
                image_path,
                outcome.fields,
                match_root,
                manifest_digest=manifest_digest,
                audit=outcome.audit,
                include_resolver=include_resolver,
            )
    return [outcomes_by_directory[task.config.directory] for task in tasks]


def collect_scratch_statuses(
    manifest: FunctionSymbolManifest,
    image_path: Path,
    match_root: Path = DEFAULT_MATCH_ROOT,
    *,
    jobs: int = DEFAULT_MATCH_JOBS,
) -> list[ScratchStatus]:
    """Match every scratch, reusing cached results for unchanged ones.

    The cache keys on scratch source/conf, transitive shared headers, compiler inputs,
    image, function/reference manifests, and matcher mtimes. An unchanged
    scratch therefore costs a dependency-stat pass instead of a compile,
    disassembly, and diff while target-map or normalizer changes still
    invalidate old scores.
    """
    if jobs < 1:
        raise ValueError("jobs must be positive")

    reference_manifest = load_default_reference_symbol_manifest()
    manifest_digest = _function_manifest_cache_digest(manifest)
    include_resolver = _ScratchIncludeResolver(match_root)
    by_name = _function_symbols_by_name(manifest)
    ordered: list[tuple[ScratchConfig, int]] = []
    statuses_by_directory: dict[Path, ScratchStatus] = {}
    uncached: list[tuple[ScratchConfig, int]] = []
    for conf_path in sorted(match_root.glob("scratches/*/scratch.conf")):
        config = load_scratch_config(conf_path.parent)
        address = by_name[config.function].address if config.function in by_name else 0
        ordered.append((config, address))

        if (
            cached := _load_cached_status(
                config,
                image_path,
                match_root,
                manifest_digest=manifest_digest,
                include_resolver=include_resolver,
            )
        ) is not None:
            statuses_by_directory[config.directory] = ScratchStatus(
                config=config, address=address, **cached
            )
            continue
        uncached.append((config, address))

    if not uncached:
        return [statuses_by_directory[config.directory] for config, _ in ordered]

    image = load_image(image_path, manifest.image_base)

    matched = _collect_uncached_match_outcomes(
        uncached,
        image=image,
        image_path=image_path,
        manifest=manifest,
        reference_manifest=reference_manifest,
        match_root=match_root,
        manifest_digest=manifest_digest,
        jobs=jobs,
        include_resolver=include_resolver,
    )
    for outcome in matched:
        if outcome.fields is None:
            fields = {
                "target_size": 0,
                "ratio": None,
                "prefix_instructions": 0,
                "target_instructions": 0,
                "candidate_instructions": 0,
                "masked_ok": 0,
                "masked_unresolved": 0,
                "masked_mismatches": 0,
                "error": outcome.error or "unknown error",
            }
        else:
            fields = outcome.fields
        statuses_by_directory[outcome.config.directory] = ScratchStatus(
            config=outcome.config,
            address=outcome.address,
            **fields,
        )

    return [statuses_by_directory[config.directory] for config, _ in ordered]


def _summarize_error(error: Exception) -> str:
    """One-line error summary, preferring the first line that names an error."""
    lines = [line.strip() for line in str(error).splitlines() if line.strip()]
    if not lines:
        return "unknown error"
    for line in lines:
        if "error" in line.lower():
            return line
    return lines[0]


@dataclass(frozen=True, slots=True)
class MaskedOperandAuditReport:
    """Repo-wide masked-operand audit outcome.

    `issues` are audit entries from scratches that compiled and matched;
    `failures` are scratches that could not be audited at all. A report is
    only clean when both are empty.
    """

    issues: list[ScratchMaskedOperandIssue]
    failures: list[ScratchAuditFailure]

    @property
    def clean(self) -> bool:
        return not self.issues and not self.failures


def collect_masked_operand_issues(
    manifest: FunctionSymbolManifest,
    image_path: Path,
    match_root: Path = DEFAULT_MATCH_ROOT,
    *,
    statuses: frozenset[str] = frozenset(("unresolved", "mismatch")),
    exact_only: bool = False,
    jobs: int = DEFAULT_MATCH_JOBS,
) -> MaskedOperandAuditReport:
    """Collect detailed masked-operand audit issues across scratch matches.

    Detailed results share the status cache and uncached scratches are compiled
    and matched concurrently. Scratches that fail are reported instead of
    aborting the whole audit; one broken scratch must not hide the rest.
    """
    if jobs < 1:
        raise ValueError("jobs must be positive")

    manifest_digest = _function_manifest_cache_digest(manifest)
    include_resolver = _ScratchIncludeResolver(match_root)
    by_name = _function_symbols_by_name(manifest)
    ordered: list[tuple[ScratchConfig, int]] = []
    results_by_directory: dict[
        Path, tuple[dict, MaskedOperandAudit] | ScratchAuditFailure
    ] = {}
    uncached: list[tuple[ScratchConfig, int]] = []

    for conf_path in sorted(match_root.glob("scratches/*/scratch.conf")):
        config = load_scratch_config(conf_path.parent)
        address = by_name[config.function].address if config.function in by_name else 0
        ordered.append((config, address))
        cached = _load_cached_match(
            config,
            image_path,
            match_root,
            manifest_digest=manifest_digest,
            include_resolver=include_resolver,
        )
        if cached is not None:
            results_by_directory[config.directory] = cached
        else:
            uncached.append((config, address))

    if uncached:
        image = load_image(image_path, manifest.image_base)
        reference_manifest = load_default_reference_symbol_manifest()
        matched = _collect_uncached_match_outcomes(
            uncached,
            image=image,
            image_path=image_path,
            manifest=manifest,
            reference_manifest=reference_manifest,
            match_root=match_root,
            manifest_digest=manifest_digest,
            jobs=jobs,
            include_resolver=include_resolver,
        )
        for outcome in matched:
            if outcome.fields is None or outcome.audit is None:
                results_by_directory[outcome.config.directory] = ScratchAuditFailure(
                    config=outcome.config,
                    address=outcome.address,
                    error=outcome.error or "unknown error",
                )
            else:
                results_by_directory[outcome.config.directory] = (
                    outcome.fields,
                    outcome.audit,
                )

    issues: list[ScratchMaskedOperandIssue] = []
    failures: list[ScratchAuditFailure] = []
    for config, address in ordered:
        outcome = results_by_directory[config.directory]
        if isinstance(outcome, ScratchAuditFailure):
            failures.append(outcome)
            continue
        fields, audit = outcome
        ratio = fields["ratio"]
        if exact_only and ratio != 1.0:
            continue
        for entry in audit.entries:
            if entry.status not in statuses:
                continue
            issues.append(
                ScratchMaskedOperandIssue(
                    config=config,
                    address=address,
                    ratio=ratio,
                    entry=entry,
                )
            )
    return MaskedOperandAuditReport(issues=issues, failures=failures)


@dataclass(frozen=True, slots=True)
class ClusterTotals:
    function_count: int
    byte_total: int
    matched_functions: int
    matched_bytes: int
    scratched_functions: int = 0
    fuzzy_weighted_bytes: float = 0.0

    @property
    def byte_percentage(self) -> float:
        return self.matched_bytes / self.byte_total if self.byte_total else 0.0

    @property
    def scratch_percentage(self) -> float:
        return self.scratched_functions / self.function_count if self.function_count else 0.0

    @property
    def fuzzy_percentage(self) -> float:
        return self.fuzzy_weighted_bytes / self.byte_total if self.byte_total else 0.0


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
    functions = sorted(manifest.functions, key=lambda symbol: symbol.address)
    addresses = [symbol.address for symbol in functions]
    functions_by_name = _function_symbols_by_name(manifest)
    byte_total = 0
    for start, end in zip(addresses, addresses[1:]):
        byte_total += len(image.function_bytes(start, end))
    last = addresses[-1]
    padding_index = image.mapped.find(b"\xcc", last - image.image_base)
    if padding_index != -1:
        byte_total += len(image.function_bytes(last, image.image_base + padding_index))

    scratched_functions = {
        functions_by_name[status.config.function].name
        for status in statuses
        if status.config.function in functions_by_name
    }
    matched_bytes_by_function: dict[str, int] = {}
    fuzzy_bytes_by_function: dict[str, float] = {}
    for status in statuses:
        requested_function = status.config.function
        if requested_function not in functions_by_name:
            continue
        function = functions_by_name[requested_function].name
        if status.state == "match":
            matched_bytes_by_function[function] = max(
                status.target_size,
                matched_bytes_by_function.get(function, 0),
            )
        if status.ratio is not None:
            fuzzy_bytes_by_function[function] = max(
                status.target_size * status.ratio,
                fuzzy_bytes_by_function.get(function, 0.0),
            )
    return ClusterTotals(
        function_count=len(addresses),
        byte_total=byte_total,
        matched_functions=len(matched_bytes_by_function),
        matched_bytes=sum(matched_bytes_by_function.values()),
        scratched_functions=len(scratched_functions),
        fuzzy_weighted_bytes=sum(fuzzy_bytes_by_function.values()),
    )


STATE_ICONS = {"match": "✅", "audit": "⚠", "wip": "🚧", "error": "❌"}
MISSING_SCRATCH_ICON = "⬜"
STATUS_SECTION_ORDER = (
    "Proof Grade",
    "Audit Needed",
    "Near Match (95-99.99%)",
    "High Progress (80-94.99%)",
    "Mid Progress (50-79.99%)",
    "Early Progress (>0-49.99%)",
    "Zero Match (0%)",
    "No Scratch (0%)",
    "Errors",
)
# build column stays empty unless a scratch deviates from the project-wide
# toolchain assumption (msvc6.5 /O2 /G5 /W3 for all game code)
STATUS_HEADER = (
    "",
    "function",
    "address",
    "bytes",
    "insns",
    "match",
    "prefix",
    "masked",
    "build",
    "note",
)


def _format_masked_counts(status: ScratchStatus) -> str:
    parts: list[str] = []
    if status.masked_mismatches:
        parts.append(f"{status.masked_mismatches} mismatch")
    if status.masked_unresolved:
        parts.append(f"{status.masked_unresolved} unresolved")
    if status.masked_ok:
        parts.append(f"{status.masked_ok} ok")
    return ", ".join(parts) if parts else "-"


def _manifest_function_rows(
    manifest: FunctionSymbolManifest,
    image: LoadedImage,
    *,
    function_names: set[str] | None = None,
) -> list[tuple[int, int, str, int]]:
    reference_manifest = load_default_reference_symbol_manifest()
    functions = sorted(manifest.functions, key=lambda symbol: symbol.address)
    rows: list[tuple[int, int, str, int]] = []
    for index, symbol in enumerate(functions):
        if function_names is not None and symbol.name not in function_names:
            continue
        start = symbol.address
        if index + 1 < len(functions):
            end = functions[index + 1].address
        else:
            padding_index = image.mapped.find(b"\xcc", start - image.image_base)
            end = image.image_base + padding_index if padding_index != -1 else start
        target_data = image.function_bytes(start, end)
        target_lines = disassemble_normalized_function(
            target_data,
            address_range=(image.image_base, image.image_base + image.size_of_image),
            base_address=start,
            image=image,
            manifest=manifest,
            reference_manifest=reference_manifest,
        )
        rows.append((start, len(target_data), symbol.name, len(target_lines)))
    return rows


def _missing_scratch_status_rows(
    statuses: list[ScratchStatus],
    manifest: FunctionSymbolManifest | None,
    image_path: Path | None,
    image: LoadedImage | None,
) -> list[tuple[str, ...]]:
    if manifest is None:
        return []
    functions_by_name = _function_symbols_by_name(manifest)
    scratched_functions = {
        functions_by_name[status.config.function].name
        for status in statuses
        if status.config.function in functions_by_name
    }
    missing_functions = {
        symbol.name for symbol in manifest.functions if symbol.name not in scratched_functions
    }
    if not missing_functions:
        return []
    if image is None:
        if image_path is None:
            return []
        image = load_image(image_path, manifest.image_base)

    rows: list[tuple[str, ...]] = []
    for address, target_size, name, target_instructions in _manifest_function_rows(
        manifest,
        image,
        function_names=missing_functions,
    ):
        rows.append(
            (
                MISSING_SCRATCH_ICON,
                name,
                f"0x{address:x}",
                str(target_size),
                f"0/{target_instructions}",
                "0.00%",
                f"0/{target_instructions}",
                "-",
                "",
                "no scratch",
            )
        )
    return rows


def render_status_rows(
    statuses: list[ScratchStatus],
    *,
    manifest: FunctionSymbolManifest | None = None,
    image_path: Path | None = None,
    image: LoadedImage | None = None,
) -> list[tuple[str, ...]]:
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
                _format_masked_counts(status),
                "" if build == default_build else build,
                status.error or "",
            )
        )
    rows.extend(_missing_scratch_status_rows(statuses, manifest, image_path, image))
    rows.sort(key=lambda row: int(row[2], 16) if row[2].startswith("0x") else 0)
    return rows


def _row_match_ratio(row: tuple[str, ...]) -> float | None:
    match_text = row[5]
    if not match_text.endswith("%"):
        return None
    try:
        return float(match_text[:-1]) / 100.0
    except ValueError:
        return None


def _status_row_section(row: tuple[str, ...]) -> str:
    icon = row[0]
    if icon == "✅":
        return "Proof Grade"
    if icon == "⚠":
        return "Audit Needed"
    if icon == "❌":
        return "Errors"
    if icon == "⬜":
        return "No Scratch (0%)"
    if icon != "🚧":
        return "Other"

    ratio = _row_match_ratio(row)
    if ratio is None or ratio <= 0.0:
        return "Zero Match (0%)"
    if ratio >= 0.95:
        return "Near Match (95-99.99%)"
    if ratio >= 0.80:
        return "High Progress (80-94.99%)"
    if ratio >= 0.50:
        return "Mid Progress (50-79.99%)"
    return "Early Progress (>0-49.99%)"


def _section_status_rows(rows: list[tuple[str, ...]]) -> list[tuple[str, list[tuple[str, ...]]]]:
    rows_by_section: dict[str, list[tuple[str, ...]]] = {}
    for row in rows:
        rows_by_section.setdefault(_status_row_section(row), []).append(row)

    sections: list[tuple[str, list[tuple[str, ...]]]] = [
        (title, rows_by_section.pop(title))
        for title in STATUS_SECTION_ORDER
        if title in rows_by_section
    ]
    for title in sorted(rows_by_section):
        sections.append((title, rows_by_section[title]))
    return sections


def _cluster_summary(totals: ClusterTotals, statuses: list[ScratchStatus]) -> str:
    exact_scratches = sum(status.state == "match" for status in statuses)
    return (
        f"cluster: {totals.matched_functions}/{totals.function_count} functions proof-grade, "
        f"{totals.matched_bytes}/{totals.byte_total} bytes "
        f"({totals.byte_percentage:.2%}) proof-grade; "
        f"{totals.scratched_functions}/{totals.function_count} functions have scratches; "
        f"overall fuzzy {totals.fuzzy_percentage:.2%}; "
        f"{exact_scratches}/{len(statuses)} scratches at proof-grade 100%"
    )


def render_status_table(
    statuses: list[ScratchStatus],
    totals: ClusterTotals,
    type_findings: list[TypeConsolidationFinding] | None = None,
    manifest: FunctionSymbolManifest | None = None,
    image_path: Path | None = None,
    image: LoadedImage | None = None,
) -> str:
    rendered_rows = render_status_rows(statuses, manifest=manifest, image_path=image_path, image=image)
    lines: list[str] = []
    for title, section_rows in _section_status_rows(rendered_rows):
        rows = [STATUS_HEADER, *section_rows]
        widths = [max(len(row[column]) for row in rows) for column in range(len(STATUS_HEADER))]
        if lines:
            lines.append("")
        lines.append(f"{title} ({len(section_rows)})")
        lines.extend(
            "  ".join(cell.ljust(width) for cell, width in zip(row, widths)).rstrip()
            for row in rows
        )
    lines.append(f"\n{_cluster_summary(totals, statuses)}")
    if type_findings is not None:
        lines.append(_type_consolidation_console_summary(type_findings))
    return "\n".join(lines)


def render_status_markdown(
    statuses: list[ScratchStatus],
    totals: ClusterTotals,
    type_findings: list[TypeConsolidationFinding] | None = None,
    manifest: FunctionSymbolManifest | None = None,
    image_path: Path | None = None,
    image: LoadedImage | None = None,
) -> str:
    lines = [
        "# Matching Status",
        "",
        "Regenerate with `uv run snail match status --write tools/match/STATUS.md`.",
        "",
        f"**{totals.matched_functions}/{totals.function_count}** mapped gameplay "
        f"functions matched, **{totals.scratched_functions}/{totals.function_count}** "
        f"mapped gameplay functions have a scratch, **{totals.matched_bytes}/"
        f"{totals.byte_total}** bytes (**{totals.byte_percentage:.2%}**) are "
        f"proof-grade, and overall fuzzy is **{totals.fuzzy_percentage:.2%}**.",
    ]
    rendered_rows = render_status_rows(statuses, manifest=manifest, image_path=image_path, image=image)
    for title, section_rows in _section_status_rows(rendered_rows):
        lines.extend(
            [
                "",
                f"## {title} ({len(section_rows)})",
                "",
                "| | function | address | bytes | insns | match | prefix | masked | build |",
                "|---|---|---|---|---|---|---|---|---|",
            ]
        )
        for row in section_rows:
            lines.append("| " + " | ".join(row[:9]) + " |")
    lines.append("")
    if type_findings is not None:
        lines.extend(render_type_consolidation_markdown(type_findings))
    return "\n".join(lines)


@dataclass(frozen=True, slots=True)
class TypeDefinition:
    kind: str
    name: str
    path: Path
    signature: str
    layout_fields: tuple["TypeLayoutField", ...]
    method_signatures: tuple[str, ...]
    is_header: bool


@dataclass(frozen=True, slots=True)
class TypeLayoutField:
    offset: int
    width: int
    storage: str
    name: str


@dataclass(frozen=True, slots=True)
class TypeConsolidationFinding:
    name: str
    status: str
    scratch_count: int
    header_count: int
    signature_count: int
    paths: tuple[Path, ...]
    recommendation: str
    details: tuple[str, ...] = ()


_TYPE_DEFINITION_RE = re.compile(r"\b(struct|class)\s+([A-Za-z_][A-Za-z0-9_]*)\s*\{")
_TYPE_FIELD_RE = re.compile(
    r"^(?P<type>.+?)\s+(?P<name>[A-Za-z_][A-Za-z0-9_]*)(?P<arrays>(?:\s*\[[^\]]+\])*)\s*;$"
)
_TYPE_FUNCTION_POINTER_FIELD_RE = re.compile(
    r"^(?P<return_type>.+?)\s*"
    r"\(\s*(?P<callconv>__[A-Za-z0-9_]+)?\s*\*\s*"
    r"(?P<name>[A-Za-z_][A-Za-z0-9_]*)\s*\)\s*"
    r"\((?P<params>.*)\)\s*;$"
)
_TYPE_FUNCTION_POINTER_START_RE = re.compile(r"\(\s*(?:__[A-Za-z0-9_]+\s*)?\*")
_TYPE_OFFSET_COMMENT_RE = re.compile(r"\+\s*0x([0-9a-fA-F]+)")
_TYPE_ARRAY_RE = re.compile(r"\[([^\]]+)\]")
_BLOCK_COMMENT_RE = re.compile(r"/\*.*?\*/", re.DOTALL)
_LINE_COMMENT_RE = re.compile(r"//.*")
_SPACE_RE = re.compile(r"\s+")

_TYPE_ALIASES = {
    "AttachmentSample": "AttachmentSample",
    "PathAttachmentSample": "AttachmentSample",
    "PathTemplateSample": "AttachmentSample",
    "HighScoreRecord": "HighScoreRecord",
    "SelectedLevelRecord": "HighScoreRecord",
    "Vec3": "Vector3",
    "Vector3": "Vector3",
}

_KNOWN_TYPE_SIZES = {
    "ActiveRuntimeRow": 0xF4,
    "ArchiveEntry": 0x0C,
    "AttachmentTransform": 0x40,
    "BodNode": 0x10,
    "Color4f": 0x10,
    "ColorBGRA8": 0x04,
    "HighScoreRecord": 0x1FAC0,
    "ObjectUv": 0x08,
    "ReplayRunRecord": 0x06,
    "TimerCounters": 0x18,
    "TransformMatrix": 0x40,
    "TrackedAllocationRecord": 0x0C,
    "Vector4": 0x10,
    "Vector3": 0x0C,
    "Vec3": 0x0C,
}

_KNOWN_TYPE_MAX_EXTENTS = {
    "FollowState": 0x40,
}


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


def _canonical_type_name(name: str) -> str:
    return _TYPE_ALIASES.get(name, name)


def _eval_int_expr(expr: str) -> int | None:
    expr = expr.strip()
    if not expr or re.search(r"[^0-9a-fA-FxX()+\-*/\s]", expr):
        return None
    try:
        value = eval(expr, {"__builtins__": {}}, {})
    except Exception:
        return None
    return int(value) if isinstance(value, int | float) else None


def _normalized_field_type(field_type: str) -> str:
    field_type = field_type.replace("*", " * ").replace("&", " & ")
    words = [
        word
        for word in _SPACE_RE.sub(" ", field_type).strip().split(" ")
        if word not in {"const", "volatile", "static", "mutable", "class", "struct"}
    ]
    return " ".join(words)


def _field_storage_and_size(field_type: str) -> tuple[str, int | None]:
    normalized = _normalized_field_type(field_type)
    if "*" in normalized or "&" in normalized:
        return "ptr", 4

    unsigned = normalized.startswith("unsigned ")
    signed = normalized.startswith("signed ")
    base = normalized.removeprefix("unsigned ").removeprefix("signed ").strip()
    if base in {"char", "__int8", "int8_t", "uint8_t", "byte", "bool"}:
        return "word1", 1
    if base in {"short", "__int16", "int16_t", "uint16_t"}:
        return "word2", 2
    if base in {
        "int",
        "long",
        "__int32",
        "int32_t",
        "uint32_t",
        "DWORD",
        "BOOL",
        "HRESULT",
        "HWND",
        "LONG",
        "LPARAM",
        "LRESULT",
        "UINT",
        "ULONG",
        "WPARAM",
        "float",
    }:
        return "word4", 4
    if base in {"double", "__int64", "int64_t", "uint64_t"}:
        return "word8", 8
    if unsigned or signed:
        return "word4", 4
    if base in _KNOWN_TYPE_SIZES:
        return f"type:{base}", _KNOWN_TYPE_SIZES[base]
    return f"type:{base}", None


def _is_padding_field(name: str, storage: str, arrays: str) -> bool:
    lowered = name.lower()
    if not arrays or storage != "word1":
        return False
    return lowered.startswith(("unknown", "pad", "reserved", "unused", "before_"))


def _normalize_method_signature(statement: str) -> str:
    statement = _strip_cpp_comments(statement)
    statement = _SPACE_RE.sub(" ", statement).strip()
    return statement.rstrip(";")


def _split_parameter_list(params: str) -> list[str]:
    params = params.strip()
    if not params or params == "void":
        return []

    result: list[str] = []
    depth = 0
    start = 0
    for index, char in enumerate(params):
        if char in "([{":
            depth += 1
        elif char in ")]}":
            depth = max(depth - 1, 0)
        elif char == "," and depth == 0:
            result.append(params[start:index].strip())
            start = index + 1
    result.append(params[start:].strip())
    return [param for param in result if param]


def _parameter_type(param: str) -> str:
    param = param.strip()
    if param == "...":
        return param
    param = re.sub(r"\s*=\s*.*$", "", param).strip()
    param = re.sub(r"\s+[A-Za-z_][A-Za-z0-9_]*\s*(?:\[[^\]]*\])?$", "", param).strip()
    return param


def _abi_storage_category(field_type: str) -> str:
    if field_type == "...":
        return "variadic"
    if field_type == "void":
        return "void"
    storage, size = _field_storage_and_size(field_type)
    if storage == "ptr":
        return "ptr"
    if size is not None:
        return f"word{size}"
    return storage


def _method_name_and_abi(signature: str) -> tuple[str, str] | None:
    signature = signature.strip()
    if "[" in signature or "]" in signature:
        return None
    is_const = signature.endswith(" const")
    if is_const:
        signature = signature.removesuffix(" const").strip()
    signature = re.sub(r"\s*=\s*0$", "", signature).strip()
    open_paren = signature.find("(")
    close_paren = signature.rfind(")")
    if open_paren < 0 or close_paren < open_paren:
        return None

    head = signature[:open_paren].strip()
    params = signature[open_paren + 1 : close_paren]
    tokens = head.split()
    if not tokens:
        return None

    method_name = tokens[-1]
    if not re.fullmatch(r"~?[A-Za-z_][A-Za-z0-9_]*", method_name):
        return None
    prefix_tokens = tokens[:-1]
    is_virtual = "virtual" in prefix_tokens
    is_static = "static" in prefix_tokens
    callconv = next((token for token in prefix_tokens if token.startswith("__")), None)
    if callconv is None:
        callconv = "cdecl" if is_static else "thiscall"
    return_tokens = [
        token
        for token in prefix_tokens
        if token not in {"virtual", "static", "inline", "extern", "friend"}
        and not token.startswith("__")
    ]
    return_type = " ".join(return_tokens) or "void"
    return_category = _abi_storage_category(_normalized_field_type(return_type))
    param_categories = tuple(
        _abi_storage_category(_parameter_type(param))
        for param in _split_parameter_list(params)
    )
    abi = (
        f"{'virtual' if is_virtual else 'nonvirtual'}:"
        f"{'static' if is_static else 'member'}:"
        f"{callconv}:{return_category}({','.join(param_categories)})"
        f"{':const' if is_const else ''}"
    )
    return method_name, abi


def _function_pointer_field(statement: str) -> TypeLayoutField | None:
    match = _TYPE_FUNCTION_POINTER_FIELD_RE.match(statement)
    if not match:
        return None

    callconv = match.group("callconv") or "cdecl"
    return_category = _abi_storage_category(_normalized_field_type(match.group("return_type")))
    param_categories = tuple(
        _abi_storage_category(_parameter_type(param))
        for param in _split_parameter_list(match.group("params"))
    )
    storage = f"fnptr:{callconv}:{return_category}({','.join(param_categories)})"
    return TypeLayoutField(offset=0, width=4, storage=storage, name=match.group("name"))


def _analyze_type_body(body: str) -> tuple[tuple[TypeLayoutField, ...], tuple[str, ...]]:
    fields: list[TypeLayoutField] = []
    methods: list[str] = []
    current_offset = 0
    union_stack: list[tuple[int, int]] = []
    pending_statement: list[str] = []
    pending_offset: int | None = None

    for raw_line in body.splitlines():
        line = _LINE_COMMENT_RE.sub("", raw_line).strip()
        if pending_statement:
            pending_statement.append(line)
            if ";" not in line:
                continue
            statement = " ".join(pending_statement)
            explicit_offset = pending_offset
            pending_statement = []
            pending_offset = None
        else:
            offset_match = _TYPE_OFFSET_COMMENT_RE.search(raw_line)
            explicit_offset = int(offset_match.group(1), 16) if offset_match else None
            statement = line
            if _TYPE_FUNCTION_POINTER_START_RE.search(statement) and not statement.endswith(";"):
                pending_statement = [statement]
                pending_offset = explicit_offset
                continue
        if not statement or statement in {"public:", "private:", "protected:"}:
            continue
        if statement.startswith(("typedef ", "using ", "enum ")):
            continue
        if statement.startswith("union") and "{" in statement:
            union_stack.append((current_offset, 0))
            continue
        if statement in {"};", "}"} and union_stack:
            union_offset, union_width = union_stack.pop()
            current_offset = union_offset + union_width
            if union_stack:
                parent_offset, parent_width = union_stack.pop()
                union_stack.append((parent_offset, max(parent_width, union_width)))
            continue
        function_pointer_field = _function_pointer_field(statement)
        if function_pointer_field is not None:
            field_offset = explicit_offset
            if field_offset is None:
                field_offset = union_stack[-1][0] if union_stack else current_offset
            fields.append(
                TypeLayoutField(
                    field_offset,
                    function_pointer_field.width,
                    function_pointer_field.storage,
                    function_pointer_field.name,
                )
            )
            if union_stack:
                union_offset, union_width = union_stack.pop()
                union_stack.append((union_offset, max(union_width, function_pointer_field.width)))
            else:
                current_offset = field_offset + function_pointer_field.width
            continue
        if (
            "(" in statement
            and ")" in statement
            and "[" not in statement
            and "]" not in statement
            and statement.endswith(";")
        ):
            methods.append(_normalize_method_signature(statement))
            continue

        field_match = _TYPE_FIELD_RE.match(statement)
        if not field_match:
            continue

        field_type = field_match.group("type")
        name = field_match.group("name")
        arrays = field_match.group("arrays")
        storage, element_size = _field_storage_and_size(field_type)
        if element_size is None:
            continue
        count = 1
        for array_expr in _TYPE_ARRAY_RE.findall(arrays):
            array_count = _eval_int_expr(array_expr)
            if array_count is None:
                count = 0
                break
            count *= array_count
        if count <= 0:
            continue

        width = element_size * count
        field_offset = explicit_offset
        if field_offset is None:
            field_offset = union_stack[-1][0] if union_stack else current_offset
        field_storage = f"{storage}[{count}]" if arrays and not storage.startswith("type:") else storage
        if not _is_padding_field(name, storage, arrays):
            fields.append(TypeLayoutField(field_offset, width, field_storage, name))

        if union_stack:
            union_offset, union_width = union_stack.pop()
            union_stack.append((union_offset, max(union_width, width)))
        else:
            current_offset = field_offset + width

    unique_fields = sorted(
        {(field.offset, field.width, field.storage, field.name) for field in fields}
    )
    return (
        tuple(TypeLayoutField(offset, width, storage, name) for offset, width, storage, name in unique_fields),
        tuple(sorted(set(methods))),
    )


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
        layout_fields, method_signatures = _analyze_type_body(body)
        definitions.append(
            TypeDefinition(
                kind=kind,
                name=name,
                path=path,
                signature=normalize_type_signature(kind, name, body),
                layout_fields=layout_fields,
                method_signatures=method_signatures,
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


def _ranges_overlap(first: TypeLayoutField, second: TypeLayoutField) -> bool:
    return first.offset < second.offset + second.width and second.offset < first.offset + first.width


def _range_contains(outer: TypeLayoutField, inner: TypeLayoutField) -> bool:
    return outer.offset <= inner.offset and inner.offset + inner.width <= outer.offset + outer.width


def _storage_compatible(first: TypeLayoutField, second: TypeLayoutField) -> bool:
    if first.storage == second.storage:
        return True
    if first.storage.startswith("fnptr:") or second.storage.startswith("fnptr:"):
        return False
    if first.storage == "ptr" or second.storage == "ptr":
        return False
    return first.width == second.width


def _layout_fields_conflict(
    first_fields: tuple[TypeLayoutField, ...],
    second_fields: tuple[TypeLayoutField, ...],
) -> bool:
    for first in first_fields:
        for second in second_fields:
            if not _ranges_overlap(first, second):
                continue
            if first.offset == second.offset and first.width == second.width:
                if not _storage_compatible(first, second):
                    return True
                continue
            if first.storage.startswith("type:") and _range_contains(first, second):
                continue
            if second.storage.startswith("type:") and _range_contains(second, first):
                continue
            return True
    return False


def _layout_definitions_conflict(first: TypeDefinition, second: TypeDefinition) -> bool:
    if not first.layout_fields or not second.layout_fields:
        return False
    return _layout_fields_conflict(first.layout_fields, second.layout_fields)


def _definition_extent(definition: TypeDefinition) -> int | None:
    if not definition.layout_fields:
        return None
    return max(field.offset + field.width for field in definition.layout_fields)


def _has_overbroad_header(
    canonical_name: str,
    header_definitions: list[TypeDefinition],
) -> bool:
    max_extent = _KNOWN_TYPE_MAX_EXTENTS.get(canonical_name)
    if max_extent is None:
        return False
    for definition in header_definitions:
        extent = _definition_extent(definition)
        if extent is not None and extent > max_extent:
            return True
    return False


def _compatible_layout_groups(definitions: list[TypeDefinition]) -> list[list[TypeDefinition]]:
    field_definitions = [definition for definition in definitions if definition.layout_fields]
    groups: list[list[TypeDefinition]] = []
    for definition in field_definitions:
        for group in groups:
            if all(not _layout_definitions_conflict(definition, member) for member in group):
                group.append(definition)
                break
        else:
            groups.append([definition])
    return groups


def _has_layout_conflict(
    header_definitions: list[TypeDefinition],
    scratch_definitions: list[TypeDefinition],
) -> bool:
    field_headers = [definition for definition in header_definitions if definition.layout_fields]
    if not field_headers:
        return False
    for scratch in scratch_definitions:
        if not scratch.layout_fields:
            continue
        if any(_layout_definitions_conflict(header, scratch) for header in field_headers):
                return True
    return False


def _field_name_conflict_slots(
    definitions: list[TypeDefinition],
) -> tuple[tuple[int, int, tuple[str, ...]], ...]:
    slot_names: dict[tuple[int, int], set[str]] = {}
    slot_paths: dict[tuple[int, int], set[Path]] = {}
    for definition in definitions:
        for layout_field in definition.layout_fields:
            slot = (layout_field.offset, layout_field.width)
            slot_names.setdefault(slot, set()).add(layout_field.name)
            slot_paths.setdefault(slot, set()).add(definition.path)

    return tuple(
        (slot[0], slot[1], tuple(sorted(slot_names[slot])))
        for slot, paths in sorted(slot_paths.items())
        if len(slot_names[slot]) > 1 and len(paths) > 1
    )


def _field_name_conflict_details(
    definitions: list[TypeDefinition],
    *,
    limit: int = 8,
) -> tuple[str, ...]:
    slots = _field_name_conflict_slots(definitions)
    details = [
        f"+0x{offset:06x} w{width}: {', '.join(names)}"
        for offset, width, names in slots[:limit]
    ]
    omitted = len(slots) - limit
    if omitted > 0:
        details.append(f"... {omitted} more conflicting slot(s)")
    return tuple(details)


def _has_field_name_conflict(definitions: list[TypeDefinition]) -> bool:
    return bool(_field_name_conflict_slots(definitions))


def _method_abi_entries(definition: TypeDefinition) -> tuple[tuple[str, str], ...]:
    entries = [
        parsed
        for signature in definition.method_signatures
        if (parsed := _method_name_and_abi(signature)) is not None
    ]
    return tuple(sorted(set(entries)))


def _method_abi_map(definition: TypeDefinition) -> dict[str, set[str]]:
    method_abis: dict[str, set[str]] = {}
    for method_name, abi in _method_abi_entries(definition):
        method_abis.setdefault(method_name, set()).add(abi)
    return method_abis


def _has_method_abi_conflict(definitions: list[TypeDefinition]) -> bool:
    method_maps: list[dict[str, set[str]]] = []
    for definition in definitions:
        method_abis = _method_abi_map(definition)
        if not method_abis:
            continue
        method_maps.append(method_abis)

    for index, first_methods in enumerate(method_maps):
        first_names = set(first_methods)
        first_has_virtual = any(
            abi.startswith("virtual:") for abis in first_methods.values() for abi in abis
        )
        for second_methods in method_maps[index + 1 :]:
            second_names = set(second_methods)
            shared_names = first_names & second_names
            if shared_names:
                if any(first_methods[name].isdisjoint(second_methods[name]) for name in shared_names):
                    return True
                continue
            second_has_virtual = any(
                abi.startswith("virtual:") for abis in second_methods.values() for abi in abis
            )
            if first_has_virtual != second_has_virtual:
                return True
    return False


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
        by_name.setdefault(_canonical_type_name(definition.name), []).append(definition)

    findings: list[TypeConsolidationFinding] = []
    for canonical_name, named_definitions in sorted(by_name.items()):
        aliases = {definition.name for definition in named_definitions}
        if names is not None and canonical_name not in names and not aliases.intersection(names):
            continue
        scratch_definitions = [definition for definition in named_definitions if not definition.is_header]
        header_definitions = [definition for definition in named_definitions if definition.is_header]
        if len(scratch_definitions) < threshold and not header_definitions:
            continue

        scratch_layout_groups = _compatible_layout_groups(scratch_definitions)
        layout_group_count = len(scratch_layout_groups)
        paths = tuple(sorted({definition.path for definition in named_definitions}))
        details: tuple[str, ...] = ()
        if _has_method_abi_conflict(named_definitions):
            status = "ABI-conflict"
            recommendation = (
                "method declarations disagree by return, parameters, calling convention, or virtual status"
            )
        elif header_definitions and scratch_definitions:
            header_layout_definitions = [
                definition for definition in header_definitions if definition.layout_fields
            ]
            if not header_layout_definitions or layout_group_count == 0:
                status = "unresolved-layout"
                recommendation = "header or scratch definitions lack parsed fields; inspect manually"
            elif _has_overbroad_header(canonical_name, header_definitions):
                status = "overbroad-header"
                recommendation = "header fields exceed a known child extent; split parent-owned storage"
            elif _has_layout_conflict(header_definitions, scratch_definitions):
                status = "header-conflict"
                recommendation = (
                    "header exists but at least one scratch field layout conflicts; inspect before including"
                )
            elif _has_field_name_conflict(scratch_definitions):
                status = "name-conflict"
                recommendation = (
                    "compatible field slots use different names; align semantics before promoting"
                )
                details = _field_name_conflict_details(scratch_definitions)
            else:
                status = "header-compatible"
                recommendation = (
                    "header layout is compatible with scratch-local field slices; replace copies deliberately"
                )
        elif layout_group_count == 0 and len(scratch_definitions) >= threshold:
            status = "unresolved-layout"
            recommendation = "definitions are method-only or lack parsed fields; inspect manually"
        elif layout_group_count == 1 and len(scratch_definitions) >= threshold:
            scratch_signatures = {definition.signature for definition in scratch_definitions}
            if _has_field_name_conflict(scratch_definitions):
                status = "name-conflict"
                recommendation = (
                    "compatible field slots use different names; align semantics before promoting"
                )
                details = _field_name_conflict_details(scratch_definitions)
            elif len(scratch_signatures) == 1:
                status = "ready"
                recommendation = "same scratch-local layout appears repeatedly; consider a header"
            else:
                status = "partial-compatible"
                recommendation = (
                    "scratch-local field slices are layout-compatible; consider one shared header or alias"
                )
        elif layout_group_count > 1 and len(scratch_definitions) >= threshold:
            status = "divergent"
            recommendation = "same name has incompatible field layouts; do not consolidate yet"
        else:
            continue

        display_name = canonical_name
        if aliases != {canonical_name}:
            alias_text = ", ".join(sorted(aliases - {canonical_name}))
            display_name = f"{canonical_name} (aliases: {alias_text})"
        findings.append(
            TypeConsolidationFinding(
                name=display_name,
                status=status,
                scratch_count=len(scratch_definitions),
                header_count=len(header_definitions),
                signature_count=layout_group_count,
                paths=paths,
                recommendation=recommendation,
                details=details,
            )
        )
    return findings


TYPE_CONSOLIDATION_STATUS_ORDER = {
    "header-conflict": 0,
    "ABI-conflict": 1,
    "overbroad-header": 2,
    "divergent": 3,
    "name-conflict": 4,
    "unresolved-layout": 5,
    "header-compatible": 6,
    "partial-compatible": 7,
    "ready": 8,
}


def _type_consolidation_counts(findings: list[TypeConsolidationFinding]) -> dict[str, int]:
    counts = {status: 0 for status in TYPE_CONSOLIDATION_STATUS_ORDER}
    for finding in findings:
        counts[finding.status] = counts.get(finding.status, 0) + 1
    return counts


def _type_consolidation_sort_key(finding: TypeConsolidationFinding) -> tuple[int, int, int, str]:
    return (
        TYPE_CONSOLIDATION_STATUS_ORDER.get(finding.status, len(TYPE_CONSOLIDATION_STATUS_ORDER)),
        -finding.scratch_count,
        -finding.signature_count,
        finding.name.lower(),
    )


def _type_consolidation_console_summary(findings: list[TypeConsolidationFinding]) -> str:
    counts = _type_consolidation_counts(findings)
    rendered_counts = ", ".join(
        f"{counts[status]} {status}"
        for status in TYPE_CONSOLIDATION_STATUS_ORDER
        if counts.get(status, 0)
    )
    return (
        "types: "
        f"{rendered_counts or '0 findings'}; "
        "run `uv run snail match types --paths` for details"
    )


def render_type_consolidation_markdown(
    findings: list[TypeConsolidationFinding],
    *,
    per_status_limit: int | None = None,
) -> list[str]:
    lines = [
        "## Type Consolidation",
        "",
        "This is generated as part of `uv run snail match status --write "
        "tools/match/STATUS.md`. Keep types scratch-local until multiple "
        "scratches agree, then promote deliberately; divergent or conflicting "
        "names are semantic debt, not merge candidates.",
        "Run `uv run snail match types --paths` for the full path-level report.",
        "",
    ]
    if not findings:
        lines.extend(
            [
                "No consolidation candidates at the current threshold.",
                "",
            ]
        )
        return lines

    counts = _type_consolidation_counts(findings)
    for status in TYPE_CONSOLIDATION_STATUS_ORDER:
        if counts.get(status, 0):
            lines.append(f"- {status}: {counts[status]} type name(s)")
    lines.extend(
        [
            "",
            "| status | type | scratch | header | layouts | recommendation |",
            "|---|---|---:|---:|---:|---|",
        ]
    )
    for status in TYPE_CONSOLIDATION_STATUS_ORDER:
        status_findings = sorted(
            (finding for finding in findings if finding.status == status),
            key=_type_consolidation_sort_key,
        )
        rendered_findings = (
            status_findings
            if per_status_limit is None
            else status_findings[:per_status_limit]
        )
        for finding in rendered_findings:
            lines.append(
                "| "
                f"{finding.status} | {finding.name} | {finding.scratch_count} | "
                f"{finding.header_count} | {finding.signature_count} | "
                f"{finding.recommendation} |"
            )
        if per_status_limit is not None:
            omitted = len(status_findings) - per_status_limit
            if omitted > 0:
                lines.append(
                    f"| ... | {omitted} more {status} finding(s) |  |  |  | "
                    "`uv run snail match types --paths` prints the full list. |"
                )
    lines.append("")
    return lines


@dataclass(frozen=True, slots=True)
class ExternLintFinding:
    """One shared-address extern divergence across headers/scratches."""

    status: str  # "type-conflict" or "uncurated-alias"
    address: int
    name: str
    detail: str
    paths: tuple[Path, ...]


_EXTERN_DECL_PATTERN = re.compile(
    r"^extern\s+([^;=\n(]+?)\s*\b(g_\w+)\s*(\[\w*\])?\s*;"
    r"\s*//.*?\b(?:data|byte|word|dword|unk)_([0-9a-fA-F]{6,8})\b",
    re.M,
)


def lint_extern_declarations(
    match_root: Path = DEFAULT_MATCH_ROOT,
    reference_manifest: ReferenceSymbolManifest | None = None,
) -> list[ExternLintFinding]:
    """Lint extern globals annotated with a data_ address across the match tree.

    Flags two shared-address hazards before they become compile breaks or
    semantic drift:
    - type-conflict: the same identifier at the same address is declared with
      different types in different translation units. The moment header
      consolidation joins two such TUs, VC6 stops compiling (C2040/C2373).
    - uncurated-alias: the same address is used under multiple identifiers,
      and at least one name is not recorded as an alias in the reference
      manifest. Divergent names encode unverified ownership assumptions.
    """
    if reference_manifest is None:
        reference_manifest = load_default_reference_symbol_manifest()
    curated_names: dict[int, set[str]] = {}
    for symbol in reference_manifest.symbols:
        curated_names.setdefault(symbol.address, set()).update(
            (symbol.name, *symbol.aliases)
        )

    sources = sorted(match_root.glob("include/*.h")) + sorted(
        match_root.glob("scratches/*/scratch.cpp")
    )
    by_decl: dict[tuple[int, str], dict[str, list[Path]]] = {}
    names_by_address: dict[int, dict[str, list[Path]]] = {}
    for path in sources:
        for match in _EXTERN_DECL_PATTERN.finditer(path.read_text()):
            declared_type = match.group(1).strip() + (match.group(3) or "")
            name = match.group(2)
            address = int(match.group(4), 16)
            by_decl.setdefault((address, name), {}).setdefault(
                declared_type, []
            ).append(path)
            names_by_address.setdefault(address, {}).setdefault(name, []).append(path)

    findings: list[ExternLintFinding] = []
    for (address, name), types in sorted(by_decl.items()):
        if len(types) <= 1:
            continue
        paths = tuple(sorted({p for ps in types.values() for p in ps}))
        detail = ", ".join(
            f"`{declared_type}` ({len(ps)})" for declared_type, ps in sorted(types.items())
        )
        findings.append(
            ExternLintFinding(
                status="type-conflict",
                address=address,
                name=name,
                detail=detail,
                paths=paths,
            )
        )
    for address, names in sorted(names_by_address.items()):
        if len(names) <= 1:
            continue
        uncurated = set(names) - curated_names.get(address, set())
        if not uncurated:
            continue
        paths = tuple(sorted({p for ps in names.values() for p in ps}))
        findings.append(
            ExternLintFinding(
                status="uncurated-alias",
                address=address,
                name="/".join(sorted(names)),
                detail=f"uncurated: {', '.join(sorted(uncurated))}",
                paths=paths,
            )
        )
    return findings
