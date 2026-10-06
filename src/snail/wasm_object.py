"""Read symbols and function signatures from WebAssembly relocatable objects.

The port links the recovered source as wasm32. Its tools need each object's
function symbols with their wasm signatures (to declare function-pointer targets
in generated data) and its data symbols (to find undefined globals).
"""

from dataclasses import dataclass
from pathlib import Path

VALUE_TYPES = {0x7F: "i32", 0x7E: "i64", 0x7D: "f32", 0x7C: "f64"}

SYMBOL_FUNCTION, SYMBOL_DATA, SYMBOL_GLOBAL, SYMBOL_SECTION, SYMBOL_TAG, SYMBOL_TABLE = range(6)
FLAG_WEAK, FLAG_LOCAL, FLAG_UNDEFINED, FLAG_EXPLICIT_NAME = 0x1, 0x2, 0x10, 0x40


@dataclass(frozen=True)
class Signature:
    params: tuple[str, ...]
    results: tuple[str, ...]

    def functype(self) -> str:
        return f"({', '.join(self.params)}) -> ({', '.join(self.results)})"


@dataclass(frozen=True)
class WasmSymbol:
    name: str
    kind: int
    flags: int
    signature: Signature | None = None

    @property
    def defined(self) -> bool:
        return not self.flags & FLAG_UNDEFINED

    @property
    def strong_global(self) -> bool:
        return self.defined and not self.flags & (FLAG_WEAK | FLAG_LOCAL)


class _Reader:
    def __init__(self, data: bytes, pos: int = 0):
        self.data, self.pos = data, pos

    def byte(self) -> int:
        self.pos += 1
        return self.data[self.pos - 1]

    def uleb(self) -> int:
        result = shift = 0
        while True:
            b = self.byte()
            result |= (b & 0x7F) << shift
            shift += 7
            if b < 0x80:
                return result

    def name(self) -> str:
        n = self.uleb()
        self.pos += n
        return self.data[self.pos - n : self.pos].decode()


def read_symbols(path: Path) -> list[WasmSymbol]:
    data = path.read_bytes()
    if data[:4] != b"\0asm":
        raise ValueError(f"{path}: not a wasm object")
    r = _Reader(data, 8)
    types: list[Signature] = []
    function_imports: list[tuple[str, int]] = []
    function_types: list[int] = []
    symbols: list[WasmSymbol] = []
    while r.pos < len(data):
        section, size = r.byte(), r.uleb()
        end = r.pos + size
        if section == 1:
            for _ in range(r.uleb()):
                r.byte()  # 0x60 func
                params = tuple(VALUE_TYPES[r.byte()] for _ in range(r.uleb()))
                results = tuple(VALUE_TYPES[r.byte()] for _ in range(r.uleb()))
                types.append(Signature(params, results))
        elif section == 2:
            for _ in range(r.uleb()):
                r.name()
                field = r.name()
                kind = r.byte()
                if kind == 0:
                    function_imports.append((field, r.uleb()))
                elif kind == 1:  # table: reftype + limits
                    r.byte()
                    flags = r.uleb()
                    r.uleb()
                    if flags & 1:
                        r.uleb()
                elif kind == 2:  # memory limits
                    flags = r.uleb()
                    r.uleb()
                    if flags & 1:
                        r.uleb()
                elif kind == 3:  # global: valtype + mutability
                    r.pos += 2
                elif kind == 4:  # tag
                    r.byte()
                    r.uleb()
        elif section == 3:
            function_types = [r.uleb() for _ in range(r.uleb())]
        elif section == 0 and r.name() == "linking":
            r.uleb()  # version
            while r.pos < end:
                subsection, subsize = r.byte(), r.uleb()
                subend = r.pos + subsize
                if subsection == 8:
                    for _ in range(r.uleb()):
                        symbols.append(
                            _read_symbol(r, types, function_imports, function_types)
                        )
                r.pos = subend
        r.pos = end
    return symbols


def _read_symbol(r, types, function_imports, function_types) -> WasmSymbol:
    kind, flags = r.byte(), r.uleb()
    undefined = flags & FLAG_UNDEFINED
    if kind == SYMBOL_FUNCTION:
        index = r.uleb()
        name = r.name() if not undefined or flags & FLAG_EXPLICIT_NAME else None
        if index < len(function_imports):
            field, type_index = function_imports[index]
            name = name or field
        else:
            type_index = function_types[index - len(function_imports)]
        return WasmSymbol(name, kind, flags, types[type_index])
    if kind == SYMBOL_DATA:
        name = r.name()
        if not undefined:
            r.uleb()
            r.uleb()
            r.uleb()
        return WasmSymbol(name, kind, flags)
    if kind == SYMBOL_SECTION:
        r.uleb()
        return WasmSymbol("", kind, flags)
    r.uleb()  # global, tag or table index
    name = r.name() if not undefined or flags & FLAG_EXPLICIT_NAME else ""
    return WasmSymbol(name, kind, flags)
