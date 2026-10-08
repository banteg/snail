"""Lockstep replay of sessions the original recorded, compared tick by tick.

A session directory comes from tools/frida/snailmail-lockstep.js
(docs/re/frida-lockstep-capture.md): tape.ndjson, the save files it started
from, and frames. This converts the tape for the headless port
(port/shell/lockstep_tape.cpp), replays it in a game directory staged with the
session's start files, and compares the port's state after every tick with
the original's: the snapshot fields, the RNG state, and cRGame::AI's result.
"""

import json
import math
import re
import shutil
import struct
import subprocess
import tempfile
from dataclasses import dataclass, field
from pathlib import Path

from .port_lockstep import SCRIPT

WASM = Path("port/zig-out/bin/snail.wasm")
RUNNER = Path("port/shell/run.mjs")
ARCHIVE = Path("artifacts/bin/SnailMail.dat")
TAPE_VERSION = 1
SLOT_BYTES = 0x20  # InputControllerSlot; the capture records the whole 0x38 stride
RECORD = struct.Struct("<B3x32s32s32s32sff4Bi I")
LAYOUT_BLOCK = re.compile(r"const LAYOUT = (\{.*?\n\});", re.DOTALL)


@dataclass
class Session:
    path: Path
    warmup: int
    startup_rng: tuple[int, int]
    fields: list[tuple[str, int, str]]  # name, offset into the game root, kind
    ticks: list[dict] = field(default_factory=list)
    renders_before: int = 0
    renders_after: list[int] = field(default_factory=list)


@dataclass
class Divergence:
    tick: int
    frontend_state: int
    differences: dict[str, tuple[float, float]]  # field: (original, port)


@dataclass
class Comparison:
    session: str
    ticks: int
    startup_rng_matches: bool
    divergent_ticks: int = 0
    first: Divergence | None = None
    first_by_field: dict[str, Divergence] = field(default_factory=dict)
    max_error: dict[str, float] = field(default_factory=dict)

    @property
    def matches(self) -> bool:
        return self.startup_rng_matches and self.divergent_ticks == 0


def capture_layout(root: Path) -> dict:
    """The capture script's generated layout: where each snapshot field lives."""
    block = LAYOUT_BLOCK.search((root / SCRIPT).read_text())
    return json.loads(re.sub(r",\n\}$", "\n}", block.group(1)))


def bitmap(codes: list[int]) -> bytes:
    bits = bytearray(32)
    for code in codes:
        bits[code >> 3] |= 1 << (code & 7)
    return bytes(bits)


def load_session(root: Path, path: Path) -> Session:
    layout = capture_layout(root)
    session = None
    for line in (path / "tape.ndjson").read_text().splitlines():
        row = json.loads(line)
        kind = row["t"]
        if kind == "startup":
            fields = [(name, int(offset, 16), kind_) for name, (offset, kind_) in layout["snapshot"].items()]
            session = Session(path, row["warmup"], (row["crt_rand_seed"], row["math_random_index"]), fields)
        elif session is None:
            continue
        elif kind == "tick":
            session.ticks.append(row)
            session.renders_after.append(0)
        elif kind == "render":
            if row["after"] == 0:
                session.renders_before += 1
            else:
                session.renders_after[row["after"] - 1] += 1
    if session is None:
        raise ValueError(f"{path}: the tape has no startup row; spawn the game under Frida with -f")
    return session


def tape_bytes(session: Session) -> bytes:
    out = bytearray(b"SNTP")
    out += struct.pack("<IiII", TAPE_VERSION, session.warmup, session.renders_before, len(session.fields))
    for _, offset, kind in session.fields:
        out += struct.pack("<II", offset, 1 if kind == "f32" else 0)
    out += struct.pack("<I", len(session.ticks))
    for tick, renders in zip(session.ticks, session.renders_after, strict=True):
        out += RECORD.pack(
            tick["rq"], bitmap(tick["k"]), bitmap(tick["kp"]),
            bytes.fromhex(tick["s0"])[:SLOT_BYTES], bytes.fromhex(tick["s1"])[:SLOT_BYTES],
            tick["mx"], tick["my"], *tick["lb"], *tick["rb"], tick["wh"], renders,
        )  # fmt: skip
    return bytes(out)


def stage(root: Path, session: Session, workdir: Path) -> None:
    (workdir / "SnailMail.dat").symlink_to((root / ARCHIVE).resolve())
    start = session.path / "start"
    if start.is_dir():
        for saved in start.iterdir():
            shutil.copy(saved, workdir / saved.name)


def as_float32(value: float) -> float:
    return struct.unpack("<f", struct.pack("<f", value))[0]


def compare(session: Session, states: bytes) -> Comparison:
    if states[:4] != b"SNTO":
        raise ValueError("the port wrote no lockstep states")
    seed, index, _ = struct.unpack_from("<IiI", states, 4)
    result = Comparison(session.path.name, len(session.ticks), (seed, index) == tuple(session.startup_rng))
    row = struct.Struct("<" + "".join({"f32": "f", "u8": "I"}.get(kind, "i") for _, _, kind in session.fields) + "Iii")
    offset = 16
    for tick in session.ticks:
        port = row.unpack_from(states, offset)
        offset += row.size
        differences = {}
        for (name, _, kind), value in zip(session.fields, port, strict=False):
            original = tick["s"].get(name)
            if original is None:  # captured by an older script
                continue
            if kind == "u8":
                value &= 0xFF
            if kind == "f32":
                original = as_float32(original)
                error = abs(original - value) if math.isfinite(original) and math.isfinite(value) else math.inf
                result.max_error[name] = max(result.max_error.get(name, 0.0), error)
                if original != value and not (math.isnan(original) and math.isnan(value)):
                    differences[name] = (original, value)
            elif original != value:
                differences[name] = (original, value)
        for name, original, value in zip(("crt_rand_seed", "math_random_index", "ai_result"),
                                         (*tick["rng"], tick["r"]), port[-3:], strict=True):  # fmt: skip
            if original != value:
                differences[name] = (original, value)
        if differences:
            result.divergent_ticks += 1
            divergence = Divergence(tick["n"], tick["s"]["frontend_state"], differences)
            result.first = result.first or divergence
            for name in differences:
                result.first_by_field.setdefault(name, divergence)
    return result


def run_session(root: Path, path: Path) -> Comparison:
    session = load_session(root, path)
    with tempfile.TemporaryDirectory(prefix="snail-lockstep-") as temp:
        workdir = Path(temp)
        stage(root, session, workdir)
        (workdir / "session.tape").write_bytes(tape_bytes(session))
        completed = subprocess.run(
            ["node", str(root / RUNNER), str(root / WASM), "--tape", "session.tape", "--tape-out", "states.bin"],
            cwd=workdir, capture_output=True, text=True, check=False,
        )  # fmt: skip
        if completed.returncode != 0:
            raise RuntimeError(f"{path.name}: the port failed:\n{completed.stderr[-2000:]}")
        return compare(session, (workdir / "states.bin").read_bytes())


def report_text(results: list[Comparison]) -> str:
    lines = []
    for r in results:
        verdict = "matches" if r.matches else f"{r.divergent_ticks} divergent ticks"
        lines.append(f"{r.session}: {r.ticks} ticks, startup RNG {'matches' if r.startup_rng_matches else 'differs'}; {verdict}")
        if r.first:
            lines.append(f"  first divergence at tick {r.first.tick} (frontend state {r.first.frontend_state}):")
            for name, (original, port) in sorted(r.first.differences.items()):
                lines.append(f"    {name}: original {original!r}, port {port!r}")
            errors = {name: error for name, error in r.max_error.items() if error > 0}
            if errors:
                lines.append("  max float error: " + ", ".join(f"{n} {e:.3g}" for n, e in sorted(errors.items())))
            exact = [name for name in r.first_by_field if name not in r.max_error]
            if exact:
                lines.append("  integer fields that diverge: " + ", ".join(f"{n} @ {r.first_by_field[n].tick}" for n in exact))
            later = {name: d.tick for name, d in r.first_by_field.items() if name not in r.first.differences}
            if later:
                lines.append("  first divergence of other fields: " + ", ".join(f"{n} @ {t}" for n, t in sorted(later.items(), key=lambda x: x[1])))
    matched = sum(r.matches for r in results)
    lines.append(f"{matched}/{len(results)} sessions match the original ({sum(r.ticks for r in results)} ticks)")
    return "\n".join(lines)
