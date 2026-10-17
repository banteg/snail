"""Run an Android armeabi-v7a shared library headless under Unicorn.

The library loads at 0x10000, so its addresses equal the Ghidra exports in
analysis/decompile/android/. Its imports (bionic libc and libm, GL ES 1.x, the
C++ runtime) are Python stubs; the JNI environment is a table of stubs that
answer the few calls the game makes (android_game.py).
"""

from __future__ import annotations

import bisect
import math
import re
import struct
from collections.abc import Callable
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection
from unicorn import UC_ARCH_ARM, UC_HOOK_CODE, UC_MODE_ARM, Uc, UcError
from unicorn.arm_const import (
    UC_ARM_REG_C1_C0_2,
    UC_ARM_REG_FPEXC,
    UC_ARM_REG_LR,
    UC_ARM_REG_PC,
    UC_ARM_REG_R0,
    UC_ARM_REG_R1,
    UC_ARM_REG_R2,
    UC_ARM_REG_R3,
    UC_ARM_REG_SP,
    UC_CPU_ARM_CORTEX_A9,
)

BASE = 0x10000
STUB, STUB_SIZE = 0x08000000, 0x10000
DATA, DATA_SIZE = 0x0A000000, 0x100000
STACK, STACK_SIZE = 0x0F000000, 0x400000
HEAP, HEAP_SIZE = 0x20000000, 0x30000000
BX_LR = struct.pack("<I", 0xE12FFF1E)
ARGS = (UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3)
R_ARM_ABS32, R_ARM_GLOB_DAT, R_ARM_JUMP_SLOT, R_ARM_RELATIVE = 2, 21, 22, 23
PRINTF_SPEC = re.compile(r"%([-+ #0]*)(\d+|\*)?(?:\.(\d+|\*))?(?:hh|h|ll|l)?([diouxXfFeEgGcsp%])")
JNI_TABLE_SIZE = 300


class Stopped(Exception):
    """The library called abort, exit or an import nothing implements."""


class ArmLibrary:
    def __init__(self, path: Path, sandbox: Path):
        self.sandbox = sandbox
        self.uc = Uc(UC_ARCH_ARM, UC_MODE_ARM)
        self.uc.ctl_set_cpu_model(UC_CPU_ARM_CORTEX_A9)
        self.log: list[str] = []
        self.files: dict[int, object] = {}
        self.next_file = DATA + 0x1000
        self.heap_top = HEAP
        self.gl_ids = 1
        self.lrand48 = 0
        self.jni_answers: dict[int, Callable[[], int]] = {}
        self.stubs: dict[int, str] = {}
        self.intercepts: dict[int, Callable[[ArmLibrary], int | tuple[int, int] | None]] = {}
        self._load(path)

    # --- memory and registers
    def read(self, addr: int, n: int) -> bytes:
        return bytes(self.uc.mem_read(addr, n))

    def write(self, addr: int, data: bytes) -> None:
        self.uc.mem_write(addr, bytes(data))

    def u32(self, addr: int) -> int:
        return struct.unpack("<I", self.read(addr, 4))[0]

    def i32(self, addr: int) -> int:
        return struct.unpack("<i", self.read(addr, 4))[0]

    def f32(self, addr: int) -> float:
        return struct.unpack("<f", self.read(addr, 4))[0]

    def put_u32(self, addr: int, value: int) -> None:
        self.write(addr, struct.pack("<I", value & 0xFFFFFFFF))

    def cstr(self, addr: int, limit: int = 1 << 20) -> str:
        out = bytearray()
        while len(out) < limit:
            chunk = self.read(addr + len(out), 64)
            end = chunk.find(b"\0")
            if end >= 0:
                return (out + chunk[:end]).decode("latin-1")
            out += chunk
        return out.decode("latin-1")

    def arg(self, i: int) -> int:
        return self.uc.reg_read(ARGS[i])

    def set_arg(self, i: int, value: int) -> None:
        self.uc.reg_write(ARGS[i], value & 0xFFFFFFFF)

    def arg_float(self, i: int) -> float:
        return struct.unpack("<f", struct.pack("<I", self.arg(i)))[0]

    def arg_double(self, i: int) -> float:
        return struct.unpack("<d", struct.pack("<II", self.arg(i), self.arg(i + 1)))[0]

    def lr(self) -> int:
        return self.uc.reg_read(UC_ARM_REG_LR) & ~1

    # --- loading
    def _load(self, path: Path) -> None:
        uc = self.uc
        image = path.read_bytes()
        with open(path, "rb") as f:
            elf = ELFFile(f)
            loads = [seg for seg in elf.iter_segments() if seg["p_type"] == "PT_LOAD"]
            end = max(seg["p_vaddr"] + seg["p_memsz"] for seg in loads)
            uc.mem_map(BASE, (end + 0xFFFF) & ~0xFFFF)
            for seg in loads:
                uc.mem_write(BASE + seg["p_vaddr"], image[seg["p_offset"] : seg["p_offset"] + seg["p_filesz"]])
            for start, size in ((STUB, STUB_SIZE), (DATA, DATA_SIZE), (STACK, STACK_SIZE), (HEAP, HEAP_SIZE)):
                uc.mem_map(start, size)

            self.sym: dict[str, int] = {}
            for name in (".symtab", ".dynsym"):
                for s in elf.get_section_by_name(name).iter_symbols():
                    if s["st_value"] and s.name and not s.name.startswith("$"):
                        self.sym.setdefault(s.name, BASE + (s["st_value"] & ~1))
            self._names = sorted((addr, name) for name, addr in self.sym.items())
            self._starts = [addr for addr, _ in self._names]

            dynsym = elf.get_section_by_name(".dynsym")
            imports: dict[str, int] = {}
            for section in elf.iter_sections():
                if not isinstance(section, RelocationSection):
                    continue
                for rel in section.iter_relocations():
                    kind, where = rel["r_info_type"], BASE + rel["r_offset"]
                    if kind == R_ARM_RELATIVE:
                        self.put_u32(where, self.u32(where) + BASE)
                        continue
                    s = dynsym.get_symbol(rel["r_info_sym"])
                    if s["st_shndx"] != "SHN_UNDEF":
                        target = BASE + s["st_value"]
                    else:
                        if s.name not in imports:
                            if s["st_info"]["type"] == "STT_OBJECT":
                                imports[s.name] = DATA + 0x100 * len(imports)
                            else:
                                imports[s.name] = self._stub(s.name)
                        target = imports[s.name]
                    if kind == R_ARM_ABS32:
                        self.put_u32(where, self.u32(where) + target)
                    elif kind in (R_ARM_GLOB_DAT, R_ARM_JUMP_SLOT):
                        self.put_u32(where, target)
                    else:
                        raise ValueError(f"unsupported relocation type {kind}")
            init = elf.get_section_by_name(".init_array")
            raw = self.read(BASE + init["sh_addr"], init["sh_size"])
            self.init_array = [x for x in struct.unpack(f"<{len(raw) // 4}I", raw) if x not in (0, 0xFFFFFFFF)]

        if "__stack_chk_guard" in imports:
            self.put_u32(imports["__stack_chk_guard"], 0xC0FFEE00)
        # JNIEnv points at a function table; each entry is a stub named jni_<index>.
        table = DATA + 0x8000
        for index in range(JNI_TABLE_SIZE):
            self.put_u32(table + 4 * index, self._stub(f"jni_{index}"))
        self.env = DATA + 0x7FF0
        self.put_u32(self.env, table)
        self.return_address = self._stub("return")
        self.stack_top = STACK + STACK_SIZE - 0x100
        # The game uses VFP: enable cp10/cp11 and FPEXC.EN.
        uc.reg_write(UC_ARM_REG_C1_C0_2, uc.reg_read(UC_ARM_REG_C1_C0_2) | (0xF << 20))
        uc.reg_write(UC_ARM_REG_FPEXC, 0x40000000)
        uc.hook_add(UC_HOOK_CODE, self._on_stub, begin=STUB, end=STUB + STUB_SIZE - 1)

    def _stub(self, name: str) -> int:
        addr = STUB + 4 * len(self.stubs)
        self.uc.mem_write(addr, BX_LR)
        self.stubs[addr] = name
        return addr

    def where(self, addr: int) -> str:
        i = bisect.bisect_right(self._starts, addr) - 1
        if i < 0:
            return hex(addr)
        start, name = self._names[i]
        return f"{name}+{addr - start:#x}"

    # --- hooks and calls
    def on(self, name: str, fn: Callable[[], None]) -> None:
        """Run fn whenever execution reaches the function or address, without changing it."""
        addr = self.sym[name] if isinstance(name, str) else name
        self.uc.hook_add(UC_HOOK_CODE, lambda uc, a, size, user: fn(), begin=addr, end=addr)

    def intercept(self, name: str, fn: Callable[[ArmLibrary], int | tuple[int, int] | None]) -> None:
        """Replace a library function with fn; fn's result goes to r0 (or r0:r1)."""
        addr = self.sym[name]
        self.intercepts[addr] = fn
        self.uc.hook_add(UC_HOOK_CODE, self._on_intercept, begin=addr, end=addr)

    def _on_intercept(self, uc, address, size, user):
        self._set_result(self.intercepts[address](self))
        uc.reg_write(UC_ARM_REG_PC, uc.reg_read(UC_ARM_REG_LR))

    def _set_result(self, value) -> None:
        if value is None:
            return
        if isinstance(value, tuple):
            self.set_arg(0, value[0])
            self.set_arg(1, value[1])
        else:
            self.set_arg(0, value)

    def call(self, target: str | int, *args: int) -> int:
        addr = self.sym[target] if isinstance(target, str) else target
        uc = self.uc
        sp = (self.stack_top - 4 * max(0, len(args) - 4)) & ~7
        for i, value in enumerate(args[4:]):
            self.put_u32(sp + 4 * i, value)
        for i, value in enumerate(args[:4]):
            self.set_arg(i, value)
        uc.reg_write(UC_ARM_REG_SP, sp)
        uc.reg_write(UC_ARM_REG_LR, self.return_address)
        try:
            uc.emu_start(addr, self.return_address)
        except UcError as e:
            pc = uc.reg_read(UC_ARM_REG_PC)
            raise RuntimeError(f"{e} at {self.where(pc)} (lr {self.where(self.lr())})") from None
        return uc.reg_read(UC_ARM_REG_R0)

    def _on_stub(self, uc, address, size, user):
        name = self.stubs[address]
        if name == "return":
            return
        if name.startswith("jni_"):
            answer = self.jni_answers.get(int(name[4:]))
            self.set_arg(0, answer() if answer else 0)
            return
        fn = getattr(self, "imp_" + name, None)
        if fn is None:
            if not name.startswith("gl"):
                uc.emu_stop()
                raise Stopped(f"unimplemented import {name} (from {self.where(self.lr())})")
            fn = self.imp_gl
        self._set_result(fn())

    # --- printf family (softfp AAPCS varargs)
    def _format(self, fmt: str, word: Callable[[], int], double: Callable[[], float]) -> str:
        out, i = [], 0
        for m in PRINTF_SPEC.finditer(fmt):
            out.append(fmt[i : m.start()])
            flags, width, precision, conv = m.groups()
            width = str(word()) if width == "*" else width or ""
            precision = str(word()) if precision == "*" else precision
            spec = "%" + flags + width + ("." + precision if precision is not None else "")
            if conv == "%":
                out.append("%")
            elif conv in "di":
                out.append((spec + "d") % struct.unpack("<i", struct.pack("<I", word()))[0])
            elif conv in "ouxX":
                out.append((spec + conv) % word())
            elif conv == "p":
                out.append(f"{word():#x}")
            elif conv == "c":
                out.append((spec + "c") % chr(word() & 0xFF))
            elif conv == "s":
                p = word()
                out.append((spec + "s") % (self.cstr(p) if p else "(null)"))
            else:
                out.append((spec + conv) % double())
            i = m.end()
        out.append(fmt[i:])
        return "".join(out)

    def _varargs(self, first: int):
        state = {"reg": first, "stack": self.uc.reg_read(UC_ARM_REG_SP)}

        def word():
            if state["reg"] < 4:
                state["reg"] += 1
                return self.arg(state["reg"] - 1)
            state["stack"] += 4
            return self.u32(state["stack"] - 4)

        def double():
            state["reg"] += state["reg"] % 2
            if state["reg"] <= 2:
                state["reg"] += 2
                return self.arg_double(state["reg"] - 2)
            state["reg"] = 4
            state["stack"] = ((state["stack"] + 7) & ~7) + 8
            return struct.unpack("<d", self.read(state["stack"] - 8, 8))[0]

        return word, double

    def _va_list(self, pointer: int):
        state = {"p": pointer}

        def word():
            state["p"] += 4
            return self.u32(state["p"] - 4)

        def double():
            state["p"] = ((state["p"] + 7) & ~7) + 8
            return struct.unpack("<d", self.read(state["p"] - 8, 8))[0]

        return word, double

    def imp_printf(self):
        self.log.append(self._format(self.cstr(self.arg(0)), *self._varargs(1)))
        return 0

    def imp_fprintf(self):
        self.log.append(self._format(self.cstr(self.arg(1)), *self._varargs(2)))
        return 0

    def imp_sprintf(self):
        text = self._format(self.cstr(self.arg(1)), *self._varargs(2)).encode("latin-1")
        self.write(self.arg(0), text + b"\0")
        return len(text)

    def imp_vsprintf(self):
        text = self._format(self.cstr(self.arg(1)), *self._va_list(self.arg(2))).encode("latin-1")
        self.write(self.arg(0), text + b"\0")
        return len(text)

    def imp_putchar(self):
        self.log.append(chr(self.arg(0) & 0xFF))
        return self.arg(0)

    imp_fputc = imp_putchar

    # --- memory and strings
    def malloc(self, size: int) -> int:
        addr = self.heap_top
        self.heap_top += max(16, (size + 15) & ~15)
        if self.heap_top > HEAP + HEAP_SIZE:
            raise Stopped("heap exhausted")
        return addr

    def imp_malloc(self):
        return self.malloc(self.arg(0))

    imp__Znwj = imp_malloc

    def imp_free(self):
        return None

    def imp_memcpy(self):
        if self.arg(2):
            self.write(self.arg(0), self.read(self.arg(1), self.arg(2)))
        return self.arg(0)

    imp_memmove = imp_memcpy

    def imp_memset(self):
        if self.arg(2):
            self.write(self.arg(0), bytes([self.arg(1) & 0xFF]) * self.arg(2))
        return self.arg(0)

    def imp_strlen(self):
        return len(self.cstr(self.arg(0)))

    def imp_strcpy(self):
        self.write(self.arg(0), self.cstr(self.arg(1)).encode("latin-1") + b"\0")
        return self.arg(0)

    def imp_strcat(self):
        end = self.arg(0) + len(self.cstr(self.arg(0)))
        self.write(end, self.cstr(self.arg(1)).encode("latin-1") + b"\0")
        return self.arg(0)

    def imp_atoi(self):
        m = re.match(r"\s*([+-]?\d+)", self.cstr(self.arg(0)))
        return int(m.group(1)) if m else 0

    def imp_strtod(self):
        text = self.cstr(self.arg(0))
        m = re.match(r"\s*[+-]?(\d+\.?\d*|\.\d+)([eE][+-]?\d+)?", text)
        if self.arg(1):
            self.put_u32(self.arg(1), self.arg(0) + (m.end() if m else 0))
        return self._double(float(m.group(0)) if m else 0.0)

    # --- libm (doubles in r0:r1, floats in r0); the host's libm, not bionic's
    @staticmethod
    def _double(value: float) -> tuple[int, int]:
        return struct.unpack("<II", struct.pack("<d", value))

    @staticmethod
    def _float(value: float) -> int:
        return struct.unpack("<I", struct.pack("<f", value))[0]

    def imp_sin(self):
        return self._double(math.sin(self.arg_double(0)))

    def imp_cos(self):
        return self._double(math.cos(self.arg_double(0)))

    def imp_sqrt(self):
        x = self.arg_double(0)
        return self._double(math.sqrt(x) if x >= 0 else math.nan)

    def imp_exp(self):
        return self._double(math.exp(self.arg_double(0)))

    def imp_floor(self):
        return self._double(math.floor(self.arg_double(0)))

    def imp_atan(self):
        return self._double(math.atan(self.arg_double(0)))

    def imp_acos(self):
        x = self.arg_double(0)
        return self._double(math.acos(x) if -1 <= x <= 1 else math.nan)

    def imp_pow(self):
        return self._double(math.pow(self.arg_double(0), self.arg_double(2)))

    def imp_floorf(self):
        return self._float(math.floor(self.arg_float(0)))

    def imp_tanf(self):
        return self._float(math.tan(self.arg_float(0)))

    # bionic's rand48, which only gRegisterInit draws from
    def imp_srand48(self):
        self.lrand48 = (self.arg(0) << 16) | 0x330E

    def imp_lrand48(self):
        self.lrand48 = (0x5DEECE66D * self.lrand48 + 0xB) & ((1 << 48) - 1)
        return self.lrand48 >> 17

    # --- C++ runtime and process
    def imp___cxa_guard_acquire(self):
        return 0 if self.read(self.arg(0), 1)[0] & 1 else 1

    def imp___cxa_guard_release(self):
        self.write(self.arg(0), b"\1")

    def imp_abort(self):
        raise Stopped("abort")

    def imp_exit(self):
        raise Stopped(f"exit({self.arg(0)})")

    def imp___stack_chk_fail(self):
        raise Stopped("stack protector")

    def imp_gettimeofday(self):
        raise Stopped("gettimeofday: the game's clock is JAVATime")

    # --- files: FILE* is an address the library only passes back
    def host_path(self, name: str) -> Path:
        """name inside the sandbox, matched case-insensitively like the device's storage."""
        path = self.sandbox
        for part in name.replace("\\", "/").strip("/").split("/"):
            matches = [c for c in path.iterdir() if c.name.lower() == part.lower()] if path.is_dir() else []
            path = matches[0] if matches else path / part
        return path

    def open_file(self, path: Path, mode: str) -> int:
        handle = self.next_file
        self.next_file += 0x60
        self.files[handle] = open(path, mode)  # noqa: SIM115 - closed by fclose
        return handle

    def imp_fopen(self):
        mode = self.cstr(self.arg(1)).replace("t", "")
        mode += "" if "b" in mode else "b"
        path = self.host_path(self.cstr(self.arg(0)))
        if "r" in mode and not path.exists():
            return 0
        path.parent.mkdir(parents=True, exist_ok=True)
        return self.open_file(path, mode)

    def imp_dup(self):
        return self.arg(0)

    imp_fdopen = imp_dup

    def imp_fclose(self):
        handle = self.files.pop(self.arg(0), None)
        if handle:
            handle.close()
        return 0

    def imp_fread(self):
        buf, size, count, handle = (self.arg(i) for i in range(4))
        data = self.files[handle].read(size * count)
        self.write(buf, data)
        return len(data) // size if size else 0

    def imp_fwrite(self):
        buf, size, count, handle = (self.arg(i) for i in range(4))
        data = self.read(buf, size * count)
        if handle in self.files:
            self.files[handle].write(data)
        else:
            self.log.append(data.decode("latin-1"))
        return count

    def imp_fseek(self):
        self.files[self.arg(0)].seek(struct.unpack("<i", struct.pack("<I", self.arg(1)))[0], self.arg(2))
        return 0

    def imp_ftell(self):
        return self.files[self.arg(0)].tell()

    def imp_chdir(self):
        return 0

    def imp_getcwd(self):
        self.write(self.arg(0), b"/\0")
        return self.arg(0)

    # --- GL ES: nothing is drawn; generated names count up
    def imp_gl(self):
        return 0

    def imp_glGenTextures(self):
        for i in range(self.arg(0)):
            self.put_u32(self.arg(1) + 4 * i, self.gl_ids)
            self.gl_ids += 1

    imp_glGenBuffers = imp_glGenTextures
