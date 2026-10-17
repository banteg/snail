"""Play the Android release's libsnailmail.so headless, as an oracle for the port's Ultimate profile.

The Java side is replaced at the JAVA* bridge: files come from the APK's assets
and a sandbox directory, images stay undecoded, sounds are recorded by name,
and time is a virtual clock that appRender steps one 16,666 us tick per frame.
Offsets are Android's (analysis/decompile/android/); see docs/port/README.md.
"""

from __future__ import annotations

import io
import struct
import zipfile
from dataclasses import dataclass, field
from pathlib import Path

from .android_emu import ArmLibrary
from .symbols import REPO_ROOT

APK = REPO_ROOT / "artifacts/android/unpacked/com.sandlotgames.snailmail.1"
LIBRARY = APK / "lib/armeabi-v7a/libsnailmail.so"
ASSETS = APK / "assets"
ARCHIVE = ASSETS / "asm.mp3"
TICK_US = 16_666

# JNI function table indices the bridge answers.
JNI_FIND_CLASS, JNI_NEW_GLOBAL_REF, JNI_GET_FIELD_ID, JNI_GET_INT_FIELD = 6, 21, 94, 100

# cRGame (the object `Game` points at)
GAME_FRONTEND_STATE = 0x15C  # players[0] at +0xd4, its frontend state at +0x88
GAME_TICK = 0x2D8
GAME_MOUSE = 0x228
GAME_BORDERS = 0xD14 + 0x678  # cRBorderManager, then its first cRBorder
GAME_SUBGAME = 0x718A0
BORDER_SIZE, BORDER_COUNT = 0x71C, 150
BORDER_FLAGS, BORDER_TEXT, BORDER_RECT = 0x194, 0x2C4, 0x22C  # rect: x, y at +0, +4; w, h at +0x10, +0x14
BORDER_HIDDEN, BORDER_KILL_PENDING, BORDER_TEARDOWN = 0x1000, 0x200, 0x400
# cRMouse: active flag at +0, press event at +0x19, x and y at +0x1c, frames since the last touch at +0x30
MOUSE_PRESS, MOUSE_XY, MOUSE_IDLE = 0x19, 0x1C, 0x30
# cRSubGame
SUBGAME_MODE, SUBGAME_ROWS, SUBGAME_COMPLETION, SUBGAME_SEGMENTS, SUBGAME_NAME = 0x60, 0x74, 0x78, 0xA0, 0x15A8
SUBGAME_ROW_FLAGS, SUBGAME_ROW_OWNER, ROW_SIZE = 0x20DEDC, 0x20DFB4, 0xDC
ROW_MIRRORED = 0x20
# gConfig
CONFIG_SLIDERS, CONFIG_TUTORIAL_DONE = 0x40, 0xC0


@dataclass
class LevelBuild:
    tick: int
    name: str
    mode: int
    rows: int
    completion: int
    segments: int
    seed: int
    draws: int
    tags: list[str] = field(default_factory=list)
    runs: list[tuple[int, int, bool]] = field(default_factory=list)  # (first row, rows, mirrored)


class AndroidGame:
    def __init__(self, sandbox: Path, library: Path = LIBRARY, archive: Path = ARCHIVE):
        sandbox.mkdir(parents=True, exist_ok=True)
        self.lib = ArmLibrary(library, sandbox)
        self.archive = archive
        self.clock_us = 1_000_000
        self.tick = 0
        self.samples: dict[int, str] = {}
        self.sounds: list[tuple[int, str]] = []
        self.builds: list[LevelBuild] = []
        self.forced_seed: int | None = None
        self._bridge()
        self._watch_levels()

    # --- the Java side
    def _bridge(self) -> None:
        lib = self.lib

        def found(name: str) -> Path | None:
            for path in (lib.host_path(name), ASSETS / name):
                if path.exists():
                    return path
            return None

        def find_file(lib):
            return int(found(lib.cstr(lib.arg(0))) is not None)

        def file_size(lib):
            path = found(lib.cstr(lib.arg(0)))
            return path.stat().st_size if path else 0

        def load_file(lib):
            path = found(lib.cstr(lib.arg(0)))
            if not path:
                return 0
            data = path.read_bytes()
            lib.write(lib.arg(1), data)
            return len(data)

        def save_file(lib):
            path = lib.host_path(lib.cstr(lib.arg(0)))
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(lib.read(lib.arg(1), lib.arg(2)))
            return 1

        def delete_file(lib):
            lib.host_path(lib.cstr(lib.arg(0))).unlink(missing_ok=True)
            return 1

        def unzip(lib):
            # Archive entries of kind 1 are single-member zip files (artifacts/android/extract_asm_mp3.py).
            with zipfile.ZipFile(io.BytesIO(lib.read(lib.arg(2), lib.arg(3)))) as zf:
                data = zf.read(zf.infolist()[0])
            lib.write(lib.arg(0), data[: lib.arg(1)])
            return 0

        def load_sample(lib):
            sample = len(self.samples) + 1
            self.samples[sample] = lib.cstr(lib.arg(0))
            return sample

        def play_sample(lib):
            self.sounds.append((self.tick, self.samples.get(lib.arg(0), str(lib.arg(0)))))
            return 0

        def time_us(lib):
            return (self.clock_us & 0xFFFFFFFF, self.clock_us >> 32)

        def nothing(lib):
            return 0

        bridge = {
            "_Z22JAVA_RegisterFunctionsP7_JNIEnvP8_jobject": nothing,
            "_Z13JAVACFindFilePc": find_file,
            "_Z13JAVACFileSizePc": file_size,
            "_Z13JAVACLoadFilePcPv": load_file,
            "_Z13JAVACSaveFilePcPvi": save_file,
            "_Z15JAVACDeleteFilePc": delete_file,
            "_Z11JAVAC_UnZipPviS_i": unzip,
            "_Z11JAVAC_UnPngPviS_iii": nothing,  # pixels only matter for drawing
            "_Z11JAVAC_UnJpgPviS_iii": nothing,
            "_Z14JAVALoadSamplePc": load_sample,
            "_Z14JAVAPlaySampleif": play_sample,
            "_Z8JAVATimev": time_us,  # GetTime: microseconds, 64-bit
        }
        for name in lib.sym:
            if name in bridge:
                lib.intercept(name, bridge[name])
            elif name.startswith("_ZN7_JNIEnv") or (name.startswith("_Z") and "JAVA" in name):
                lib.intercept(name, nothing)  # vibration, OpenFeint, music control
        # JNIDatInit reads the archive's file descriptor through JNI.
        lib.jni_answers = {
            JNI_FIND_CLASS: lambda: 1,
            JNI_NEW_GLOBAL_REF: lambda: lib.arg(1),
            JNI_GET_FIELD_ID: lambda: 1,
            JNI_GET_INT_FIELD: lambda: self.archive_handle,
        }

    # --- running
    def boot(self, max_frames: int = 2000) -> None:
        lib = self.lib
        for constructor in lib.init_array:
            lib.call(constructor)
        self.archive_handle = lib.open_file(self.archive, "rb")
        lib.call("Java_com_sandlotgames_snailmail_SnailMailActivity_JNIDatInit", lib.env, 0, 1, 0, self.archive.stat().st_size)
        lib.call("Java_com_sandlotgames_snailmail_ADRenderer_nativeInit", lib.env, 0)
        lib.put_u32(lib.sym["gJavaEnv"], lib.env)
        lib.put_u32(lib.sym["gJavaObj"], 1)
        lib.call("Java_com_sandlotgames_snailmail_ADRenderer_nativeResize", lib.env, 0, 480, 320)
        for _ in range(max_frames):
            self.clock_us += TICK_US
            if lib.call("AppInit"):
                return
        raise RuntimeError("AppInit did not finish")

    def frame(self, count: int = 1) -> None:
        for _ in range(count):
            self.clock_us += TICK_US
            self.tick += 1
            self.lib.call("appRender", 0)

    # --- state
    @property
    def game(self) -> int:
        return self.lib.u32(self.lib.sym["Game"])

    @property
    def subgame(self) -> int:
        return self.game + GAME_SUBGAME

    @property
    def frontend_state(self) -> int:
        return self.lib.i32(self.game + GAME_FRONTEND_STATE)

    def config(self, offset: int, data: bytes) -> None:
        self.lib.write(self.lib.sym["gConfig"] + offset, data)

    def widgets(self) -> list[dict]:
        lib, out = self.lib, []
        for i in range(BORDER_COUNT):
            border = self.game + GAME_BORDERS + i * BORDER_SIZE
            flags = lib.u32(border + BORDER_FLAGS)
            if not flags or flags & (BORDER_HIDDEN | BORDER_KILL_PENDING | BORDER_TEARDOWN):
                continue
            x, y = struct.unpack("<ff", lib.read(border + BORDER_RECT, 8))
            w, h = struct.unpack("<ff", lib.read(border + BORDER_RECT + 0x10, 8))
            out.append({"text": lib.cstr(border + BORDER_TEXT, 256), "x": x, "y": y, "w": w, "h": h})
        return out

    # --- touch, in the 640x480 frame the widgets use
    def touch(self, x: float, y: float, down: bool) -> None:
        # What cRMouse::ClickiPhone stores once ConvertScreenXY has mapped the device's pixels.
        mouse = self.game + GAME_MOUSE
        self.lib.call("_ZN7cRMouse9SetActiveEv", mouse)
        self.lib.put_u32(mouse + MOUSE_IDLE, 0)
        self.lib.write(mouse + MOUSE_PRESS, bytes([down]))
        self.lib.write(mouse + MOUSE_XY, struct.pack("<ff", x, y))

    def tap(self, x: float, y: float) -> None:
        # Hover, hold for three ticks (cRMouse::AI clears the press event every tick), lift.
        self.touch(x, y, False)
        self.frame(5)
        for _ in range(3):
            self.touch(x, y, True)
            self.frame()
        self.touch(x, y, False)
        self.frame(5)

    def find(self, text: str, frames: int = 600) -> dict:
        for _ in range(frames):
            for widget in self.widgets():
                if widget["text"].startswith(text):
                    return widget
            self.frame()
        raise RuntimeError(f"no widget {text!r}; showing {[w['text'] for w in self.widgets()]}")

    def press(self, text: str) -> None:
        widget = self.find(text)
        self.tap(widget["x"] + max(widget["w"], 20) / 2, widget["y"] + max(widget["h"], 20) / 2)

    # --- level builds: RandSeed, then every Rand() until cRSubGame::StartLevel returns
    def _watch_levels(self) -> None:
        lib = self.lib
        state = {"seed": None, "tags": []}

        def seed():
            if self.forced_seed is not None:
                lib.set_arg(0, self.forced_seed)
            state["seed"], state["tags"] = lib.arg(0), []

        def tagged():
            state["tags"].append(lib.cstr(lib.arg(1)) if lib.arg(1) else "-")

        def built():
            self.builds.append(self._build(state["seed"], state["tags"]))

        lib.on("_Z8RandSeedi", seed)
        lib.on("_Z4RANDfPc", tagged)
        lib.on("_Z5SRANDfPc", tagged)
        for site in self._call_sites("_ZN9cRSubGame2AIEv", "_ZN9cRSubGame10StartLevelEi"):
            lib.on(site, built)

    def _call_sites(self, caller: str, callee: str, span: int = 0x4000) -> list[int]:
        """Return addresses after each ARM `bl callee` in caller's first span bytes."""
        lib = self.lib
        start, target = lib.sym[caller], lib.sym[callee]
        code = lib.read(start, span)
        sites = []
        for offset in range(0, span, 4):
            word = struct.unpack_from("<I", code, offset)[0]
            if word & 0x0F000000 == 0x0B000000:
                delta = (word & 0xFFFFFF) - ((word & 0x800000) << 1)
                if start + offset + 8 + 4 * delta == target:
                    sites.append(start + offset + 4)
        return sites

    def _build(self, seed: int | None, tags: list[str]) -> LevelBuild:
        lib, sub = self.lib, self.subgame
        rows = lib.i32(sub + SUBGAME_ROWS)
        runs: list[tuple[int, int, bool]] = []
        previous = None
        for row in range(rows):
            owner = lib.i32(sub + SUBGAME_ROW_OWNER + row * ROW_SIZE)
            mirrored = bool(lib.u32(sub + SUBGAME_ROW_FLAGS + row * ROW_SIZE) & ROW_MIRRORED)
            if owner != previous:
                runs.append((row, 0, mirrored))
                previous = owner
            first, length, first_mirrored = runs[-1]
            runs[-1] = (first, length + 1, first_mirrored)
        return LevelBuild(
            tick=self.tick,
            name=lib.cstr(sub + SUBGAME_NAME, 64),
            mode=lib.i32(sub + SUBGAME_MODE),
            rows=rows,
            completion=lib.i32(sub + SUBGAME_COMPLETION),
            segments=lib.i32(sub + SUBGAME_SEGMENTS),
            seed=seed,
            draws=len(tags),
            tags=list(tags),
            runs=runs,
        )


def play(
    sandbox: Path,
    presses: list[str],
    *,
    ticks: int = 0,
    seed: int | None = None,
    tutorial_done: bool = False,
    sliders: tuple[int, float, int] | None = None,
) -> AndroidGame:
    """Boot, pass the intro, press each widget in turn, wait for a level build, then play `ticks`."""
    game = AndroidGame(sandbox)
    game.boot()
    game.forced_seed = seed
    if tutorial_done:
        game.config(CONFIG_TUTORIAL_DONE, b"\1")
    if sliders:
        game.config(CONFIG_SLIDERS, struct.pack("<ifi", *sliders))
    game.frame(120)
    game.tap(320, 240)  # the intro waits for a touch
    for text in presses:
        game.press(text)
        game.frame(60)
    for _ in range(600):
        if game.builds:
            break
        game.frame()
    game.frame(ticks)
    return game


def trace_lines(game: AndroidGame, segments: bool = False) -> list[str]:
    lines = []
    for build in game.builds:
        tags: dict[str, int] = {}
        for tag in build.tags:
            tags[tag] = tags.get(tag, 0) + 1
        lines.append(
            f'tick {build.tick}: level "{build.name}" mode {build.mode} rows {build.rows} '
            f"completion {build.completion} segments {build.segments} seed {build.seed} draws {build.draws}"
        )
        lines.append("  draws by tag: " + ", ".join(f"{tag} {n}" for tag, n in tags.items()))
        if segments:
            lines += [f"  row {first} rows {n}{' mirrored' if m else ''}" for first, n, m in build.runs]
    lines += [f"tick {tick}: sound {name}" for tick, name in game.sounds]
    return lines
