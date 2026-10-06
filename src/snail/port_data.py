"""Generate the port's data from the original image.

Matching recovered code, not data: globals, strings, tables and vtables exist in
the recovered source only as `extern` declarations. The port gets them from the
original executable instead. This module emits the image's `.rdata` and `.data`
sections (initialized bytes, then the zero-filled tail) as wasm32 assembly:

- every known data name (reference-manifest symbols and aliases, plus names whose
  `extern` declaration carries an address comment) is a weak label at its
  original address, so a definition in recovered code wins over the image copy;
- every aligned word whose value is an image address becomes a relocation: to a
  label inside the emitted sections, or to the recovered function at that address,
  declared with the exact wasm signature its compiled object defines;
- words that point anywhere else (library code the port does not compile) become
  zero and are listed in the report, with the nearest preceding name;
- a function pointer in a `vtable`-kind symbol is a callback slot the code calls
  as a void member (`(this, ...) -> ()`, e.g. BodAiDispatch::update_bod_ai). When
  the recovered target differs (an identical-code-folded empty body recovered as
  a free function, or a method whose matched shape returns a leftover `eax`),
  the slot points at a generated adapter that passes `this` and drops the result.

The output contains the original's data bytes, so it is generated locally from
the user's executable and never committed.
"""

import json
import re
import struct
import subprocess
import tempfile
from dataclasses import dataclass, field
from pathlib import Path

import pefile

from . import port
from .wasm_object import SYMBOL_FUNCTION, Signature, read_symbols

IMAGE = Path("artifacts/bin/SnailMail_unwrapped.exe")
FUNCTIONS = Path("analysis/symbols/gameplay-functions.json")
REFERENCES = Path("analysis/symbols/gameplay-references.json")
LAYOUT = Path("decomp/layout.json")
CFLAGS = Path("port/cflags.txt")
SOURCES = Path("port/sources.txt")
OUTPUT = Path("port/generated/image_data.s")
REPORT = Path("port/generated/image_data.json")
EMITTED_SECTIONS = (".rdata", ".data")
DATA_KINDS = {"global", "vtable", "string", "offset", "lookup_table", "constant", "function_pointer"}
IDENTIFIER = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
# `extern <type> name[...]; // ... 0x4a3e68` or `data_4a3e68` / `off_4a3e68`
EXTERN_WITH_ADDRESS = re.compile(
    r"^\s*extern\s+(?!\"C\")[^;(]*?\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])*\s*;[^\n]*?"
    r"(?:0x|data_|off_|unk_|dword_|byte_|stru_|flt_|word_)([0-9a-fA-F]{6,8})\b",
    re.MULTILINE,
)


@dataclass
class ImageSection:
    name: str
    start: int
    raw_end: int
    end: int
    data: bytes


@dataclass
class DataPlan:
    labels: dict[int, set[str]] = field(default_factory=dict)
    local_labels: set[int] = field(default_factory=set)
    sizes: dict[str, int] = field(default_factory=dict)
    function_targets: dict[int, tuple[str, Signature]] = field(default_factory=dict)
    vtable_slots: set[int] = field(default_factory=set)
    known_targets: set[int] = field(default_factory=set)
    string_start: object = None
    adapters: dict[str, tuple[str, Signature, Signature]] = field(default_factory=dict)
    unresolved: list[dict] = field(default_factory=list)


def _printable(byte: int) -> bool:
    return 0x20 <= byte <= 0x7E


def pointer_value(
    data: bytes, offset: int, base: int, end: int, known: set[int], string_start
) -> int | None:
    """The image address an aligned data word holds, or None if it is not a pointer.

    A word pointing at a known function or named label is a pointer. A word that
    reads as text (three printable bytes and a NUL, so "txt\0" is 0x00747874, an
    image address) or sits inside text (after four printable bytes) is a pointer
    only if its target starts a string in initialized data, as string tables'
    entries do; text's accidental targets land in zero-filled data instead.
    """
    value = struct.unpack_from("<I", data, offset)[0]
    if not base <= value < end:
        return None
    if value in known:
        return value
    textlike = data[offset + 3] == 0 and all(_printable(b) for b in data[offset : offset + 3])
    in_text = offset >= 4 and all(_printable(b) for b in data[offset - 4 : offset])
    if (textlike or in_text) and not string_start(value):
        return None
    return value


def load_sections(root: Path) -> tuple[int, int, list[ImageSection]]:
    pe = pefile.PE(str(root / IMAGE), fast_load=True)
    base = pe.OPTIONAL_HEADER.ImageBase
    sections = []
    for section in pe.sections:
        name = section.Name.rstrip(b"\0").decode()
        if name not in EMITTED_SECTIONS:
            continue
        start = base + section.VirtualAddress
        raw = min(section.SizeOfRawData, section.Misc_VirtualSize)
        sections.append(
            ImageSection(name, start, start + raw, start + section.Misc_VirtualSize, section.get_data()[:raw])
        )
    return base, base + pe.OPTIONAL_HEADER.SizeOfImage, sections


def vtable_slots(root: Path) -> set[int]:
    """Addresses of callback-table slots: each word of a `vtable`-kind symbol."""
    slots = set()
    for symbol in json.loads((root / REFERENCES).read_text())["symbols"]:
        if symbol["kind"] == "vtable":
            address = int(symbol["address"], 16)
            size = symbol.get("size", 4)
            size = int(size, 16) if isinstance(size, str) else size
            slots.update(range(address, address + size, 4))
    return slots


def slot_adapter(target: str, signature: Signature) -> tuple[str, Signature] | None:
    """The void-member signature a callback slot calls `target` with, if it differs."""
    slot = Signature(signature.params or ("i32",), ())
    return (None if slot == signature else (f"slot_adapter_{target}", slot))


def data_names(root: Path) -> tuple[dict[int, set[str]], dict[str, int]]:
    """Every name code may use for an image data address, and known sizes."""
    names: dict[int, set[str]] = {}
    sizes: dict[str, int] = {}
    for symbol in json.loads((root / REFERENCES).read_text())["symbols"]:
        if symbol["kind"] not in DATA_KINDS:
            continue
        address = int(symbol["address"], 16)
        for name in (symbol["name"], *symbol.get("aliases", ())):
            if IDENTIFIER.match(name):
                names.setdefault(address, set()).add(name)
                if "size" in symbol:
                    size = symbol["size"]
                    sizes[name] = int(size, 16) if isinstance(size, str) else size
    sources = [*sorted((root / "decomp").rglob("*.cpp")), *sorted((root / "tools/match/include").glob("*.h"))]
    for path in sources:
        for match in EXTERN_WITH_ADDRESS.finditer(path.read_text(encoding="utf-8", errors="replace")):
            names.setdefault(int(match.group(2), 16), set()).add(match.group(1))
    return names, sizes


def function_addresses(root: Path) -> dict[int, str]:
    return {
        int(function["address"], 16): function["name"]
        for function in json.loads((root / FUNCTIONS).read_text())["functions"]
    }


def port_sources(root: Path) -> dict[str, str]:
    """Function name -> source path, for functions the port compiles."""
    compiled = set((root / SOURCES).read_text().split())
    layout = json.loads((root / LAYOUT).read_text())
    return {
        source["function"]: source["path"]
        for unit in layout["units"]
        for source in unit["sources"]
        if f"../{source['path']}" in compiled
    }


def defined_function(root: Path, source: str, flags: list[str], cache: Path) -> tuple[str, Signature] | None:
    """The strong function symbol a recovered source defines, with its wasm signature."""
    obj = cache / (source.replace("/", "_") + ".o")
    if not obj.exists():
        subprocess.run(
            ["zig", "c++", "-target", "wasm32-wasi", "-c", *flags, source, "-o", str(obj)],
            cwd=root / "port",
            check=True,
            capture_output=True,
        )
    candidates = [s for s in read_symbols(obj) if s.kind == SYMBOL_FUNCTION and s.strong_global]
    # A constructor is emitted as complete- and base-object entry points (C1/C2).
    complete = [s for s in candidates if "C1E" in s.name] or candidates
    if not complete:
        # A C++ global's registration thunk: the port's compiler initializes the
        # global itself, so the slot has nothing to call.
        return None
    if len(complete) != 1:
        raise ValueError(f"{source}: expected one defined function, found {[s.name for s in candidates]}")
    return complete[0].name, complete[0].signature


def plan_data(root: Path, cache: Path) -> tuple[DataPlan, list[ImageSection]]:
    base, end, sections = load_sections(root)
    names, sizes = data_names(root)
    functions = function_addresses(root)
    sources = port_sources(root)
    flags = port.compile_flags(root)
    plan = DataPlan(sizes=sizes, vtable_slots=vtable_slots(root))

    def emitted(address: int) -> bool:
        return any(s.start <= address < s.end for s in sections)

    for address, label_names in names.items():
        if emitted(address):
            plan.labels.setdefault(address, set()).update(label_names)

    def nearest_name(address: int) -> str:
        below = [a for a in plan.labels if a <= address]
        if not below:
            return "?"
        a = max(below)
        return f"{min(plan.labels[a])}+0x{address - a:x}"

    plan.known_targets = set(plan.labels) | set(functions)

    def string_start(address: int) -> bool:
        for section in sections:
            if section.start <= address < section.raw_end:
                at = address - section.start
                return _printable(section.data[at]) and (at == 0 or section.data[at - 1] == 0)
        return False

    plan.string_start = string_start
    for section in sections:
        for offset in range(0, len(section.data) - 3, 4):
            value = pointer_value(section.data, offset, base, end, plan.known_targets, string_start)
            if value is None:
                continue
            if emitted(value):
                plan.local_labels.add(value)
            elif value in functions and functions[value] in sources and (
                value in plan.function_targets
                or (target := defined_function(root, f"../{sources[functions[value]]}", flags, cache))
            ):
                plan.function_targets.setdefault(value, target)
            else:
                plan.unresolved.append(
                    {
                        "at": f"0x{section.start + offset:x}",
                        "in": nearest_name(section.start + offset),
                        "value": f"0x{value:x}",
                        "function": functions.get(value),
                    }
                )
    return plan, sections


def _label_lines(plan: DataPlan, address: int) -> list[str]:
    lines = []
    for name in sorted(plan.labels.get(address, ())):
        lines += [f"\t.weak\t{name}", f"{name}:", f"\t.size\t{name}, {plan.sizes.get(name, 0)}"]
    if address in plan.local_labels:
        lines += [f"img_{address:x}:", f"\t.size\timg_{address:x}, 0"]
    return lines


def render(plan: DataPlan, sections: list[ImageSection], base: int, end: int) -> str:
    out = ["# Generated by `snail port data` from the original image. Do not edit or commit."]
    for address, (symbol, signature) in sorted(plan.function_targets.items()):
        out.append(f"\t.functype\t{symbol} {signature.functype()}")
    unresolved = {int(u["at"], 16) for u in plan.unresolved}
    run: list[str] = []

    def flush():
        if run:
            out.append("\t.ascii\t\"" + "".join(run) + "\"")
            run.clear()

    for section in sections:
        label = section.name.strip(".")
        out += [f"\t.section\t.data.image_{label},\"\",@", "\t.p2align\t4"]
        address = section.start
        while address < section.raw_end:
            if address in plan.labels or address in plan.local_labels:
                flush()
                out += _label_lines(plan, address)
            offset = address - section.start
            labelled = any(
                a in plan.labels or a in plan.local_labels for a in range(address + 1, address + 4)
            )
            if address % 4 == 0 and address + 4 <= section.raw_end and not labelled:
                value = pointer_value(section.data, offset, base, end, plan.known_targets, plan.string_start)
                if value is not None:
                    flush()
                    if value in plan.function_targets:
                        target, signature = plan.function_targets[value]
                        adapter = slot_adapter(target, signature) if address in plan.vtable_slots else None
                        if adapter:
                            plan.adapters[adapter[0]] = (target, signature, adapter[1])
                            target = adapter[0]
                        out.append(f"\t.int32\t{target}")
                    elif address in unresolved:
                        out.append("\t.int32\t0")
                    else:
                        out.append(f"\t.int32\timg_{value:x}")
                    address += 4
                    continue
            run.append(f"\\{section.data[offset]:03o}")
            if len(run) >= 64:
                flush()
            address += 1
        flush()
        # The zero-filled tail stays in the same section: the linker places
        # .bss sections apart, and arrays run across the raw end.
        cursor = section.raw_end
        for address in sorted(a for a in {*plan.labels, *plan.local_labels} if section.raw_end <= a < section.end):
            if address > cursor:
                out.append(f"\t.skip\t{address - cursor}")
                cursor = address
            out += _label_lines(plan, address)
        if section.end > cursor:
            out.append(f"\t.skip\t{section.end - cursor}")
    for name, (target, signature, slot) in sorted(plan.adapters.items()):
        taken = len(signature.params)
        out += [
            f"\t.section\t.text.{name},\"\",@",
            f"\t.type\t{name},@function",
            f"{name}:",
            f"\t.functype\t{name} {slot.functype()}",
            *(f"\tlocal.get\t{i}" for i in range(taken)),
            f"\tcall\t{target}",
            *("\tdrop" for _ in signature.results),
            "\tend_function",
        ]
    return "\n".join(out) + "\n"


def generate(root: Path) -> dict:
    base, end, _ = load_sections(root)
    with tempfile.TemporaryDirectory(prefix="snail-port-data-") as temp:
        plan, sections = plan_data(root, Path(temp))
    (root / OUTPUT).parent.mkdir(parents=True, exist_ok=True)
    (root / OUTPUT).write_text(render(plan, sections, base, end))
    report = {
        "labels": sum(len(v) for v in plan.labels.values()),
        "local_labels": len(plan.local_labels),
        "function_pointers": len(plan.function_targets),
        "slot_adapters": sorted(plan.adapters),
        "unresolved_pointers": plan.unresolved,
    }
    (root / REPORT).write_text(json.dumps(report, indent=1) + "\n")
    return report
