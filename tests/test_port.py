"""Port build inputs: source selection, generated data and link forwarders."""

import json
import re
import shutil
import subprocess

import pytest

from snail import port, port_extras
from snail.archive import parse_archive_index, read_archive_entry, write_archive
from snail.port_data import DataPlan, ImageSection, pointer_value, render, slot_adapter
from snail.port_link import forwarder, resolve
from snail.symbols import REPO_ROOT
from snail.wasm_debug import LineTable, annotate
from snail.wasm_object import SYMBOL_FUNCTION, Signature, read_symbols

I32 = ("i32",)


def test_committed_sources_are_current():
    assert (REPO_ROOT / port.SOURCES).read_text() == port.sources_text(REPO_ROOT)


def _layout_root(tmp_path, replaced="", portable="", wrapped=""):
    (tmp_path / "decomp").mkdir(exist_ok=True)
    (tmp_path / "port").mkdir(exist_ok=True)
    sources = [
        {"function": "update_world", "path": "decomp/game/A/update_world.cpp", "port_scope": "core"},
        {"function": "draw_world", "path": "decomp/game/A/draw_world.cpp", "port_scope": "boundary"},
        {"function": "open_window", "path": "decomp/game/A/open_window.cpp", "port_scope": "replaceable-platform"},
        {"function": "read_file", "path": "decomp/game/A/read_file.cpp", "port_scope": "replaceable-platform"},
    ]
    (tmp_path / port.LAYOUT).write_text(json.dumps({"units": [{"sources": sources}]}))
    (tmp_path / port.REPLACED).write_text(replaced)
    (tmp_path / port.PORTABLE).write_text(portable)
    if wrapped:
        (tmp_path / port.WRAPPED).write_text(wrapped)
    return tmp_path

def test_source_list_compiles_core_boundary_and_portable_platform(tmp_path):
    root = _layout_root(tmp_path, replaced="# shell\ndraw_world G0\n", portable="read_file\n")
    assert port.source_list(root) == ["../decomp/game/A/update_world.cpp", "../decomp/game/A/read_file.cpp"]


@pytest.mark.parametrize(
    ("replaced", "portable"), [("update_world\n", ""), ("open_window\n", ""), ("", "draw_world\n")]
)
def test_source_list_rejects_listings_outside_their_scope(tmp_path, replaced, portable):
    with pytest.raises(ValueError, match="lists functions outside"):
        port.source_list(_layout_root(tmp_path, replaced=replaced, portable=portable))



def test_wrapped_list_excludes_wrapped_sources_and_checks_paths(tmp_path):
    root = _layout_root(tmp_path, wrapped="update_world ../decomp/game/A/update_world.cpp Step\n")
    assert port.source_list(root) == ["../decomp/game/A/draw_world.cpp"]
    with pytest.raises(ValueError, match="paths disagree"):
        port.source_list(_layout_root(tmp_path, wrapped="update_world ../decomp/game/A/wrong.cpp Step\n"))


def test_split_surface_strip_and_archive_roundtrip(tmp_path):
    import io

    from PIL import Image

    strip = Image.new("RGB", (512, 128))
    strip.paste((200, 10, 20), (0, 0, 128, 128))
    strip.paste((180, 30, 40), (128, 0, 256, 128))
    buf = io.BytesIO()
    strip.save(buf, format="PNG")
    track_tga, slide_tga = port_extras.split_surface_strip(buf.getvalue())
    assert Image.open(io.BytesIO(track_tga)).getpixel((64, 64)) == (200, 10, 20)
    assert Image.open(io.BytesIO(slide_tga)).getpixel((64, 64)) == (180, 30, 40)

    archive = tmp_path / "SnailMailExtras.dat"
    write_archive(archive, {"Objects/World00/Track4.tga": track_tga, "Objects/World00/Slide4.tga": slide_tga})
    index = parse_archive_index(archive)
    assert read_archive_entry(archive, index.entry_by_path("objects/world00/track4.tga")) == track_tga

BASE, END = 0x400000, 0x500000


def _word(value):
    return value.to_bytes(4, "little")


def test_pointer_value_keeps_known_targets_and_drops_text():
    never = lambda address: False
    assert pointer_value(_word(0x401000), 0, BASE, END, {0x401000}, never) == 0x401000
    assert pointer_value(_word(0x401000), 0, BASE, END, set(), never) == 0x401000
    assert pointer_value(_word(0x600000), 0, BASE, END, set(), never) is None
    # "txt\0" reads as 0x00747874, an image address.
    assert pointer_value(b"txt\0", 0, BASE, END, set(), never) is None
    assert pointer_value(b"abcd" + _word(0x401000), 4, BASE, END, set(), never) is None


def test_pointer_value_keeps_textlike_words_that_start_strings():
    starts = {0x4A3E74}.__contains__
    assert pointer_value(_word(0x4A3E74), 0, BASE, END, set(), starts) == 0x4A3E74


def test_slot_adapter_only_when_the_signature_differs():
    assert slot_adapter("f", Signature(I32, ())) is None
    assert slot_adapter("f", Signature(I32, I32)) == ("slot_adapter_f", Signature(I32, ()))
    assert slot_adapter("noop", Signature((), ())) == ("slot_adapter_noop", Signature(I32, ()))


def test_render_keeps_the_zero_tail_in_the_initialized_section():
    section = ImageSection(".data", 0x4B0000, 0x4B0008, 0x4B0100, b"abcdefgh")
    plan = DataPlan(labels={0x4B0004: {"g_head"}, 0x4B0010: {"g_tail"}}, sizes={"g_tail": 8})
    plan.string_start = lambda address: False
    text = render(plan, [section], BASE, END)
    assert text.count(".section") == 1
    assert ".bss" not in text
    lines = text.splitlines()
    tail = lines.index("g_tail:")
    assert lines[tail - 2 : tail] == ["\t.skip\t8", "\t.weak\tg_tail"]
    assert lines[-1] == "\t.skip\t240"


def test_forwarder_rules():
    same = forwarder("a", Signature(I32, I32), "b", Signature(I32, I32))
    assert same[-3:] == ["\tlocal.get\t0", "\tcall\tb", "\tend_function"]
    prefix = forwarder("a", Signature(("i32", "f32"), ()), "b", Signature(I32, ()))
    assert "\tlocal.get\t1" not in prefix
    returns_this = forwarder("a", Signature(I32, I32), "b", Signature(I32, ()))
    assert returns_this[-3:] == ["\tcall\tb", "\tlocal.get\t0", "\tend_function"]
    assert forwarder("a", Signature(("f32",), ()), "b", Signature(I32, ())) is None
    assert forwarder("a", Signature(I32, ("f32",)), "b", Signature(I32, I32)) is None


def test_resolve_owner_spellings():
    index = {"cRSubGarbage_cRSubGarbage": "x", "initialize_garbage_hazard": "y"}
    assert resolve("cRSubGarbage::cRSubGarbage()", index) == "x"
    assert resolve("RuntimeSlot::initialize_garbage_hazard(int)", index) == "y"
    assert resolve("Missing::nothing()", index) is None


@pytest.mark.skipif(shutil.which("zig") is None, reason="zig is not installed")
def test_read_symbols_signatures(tmp_path):
    source = tmp_path / "unit.cpp"
    source.write_text("int callee(int, float);\nint caller(int x) { return callee(x, 1.0f); }\n")
    obj = tmp_path / "unit.o"
    subprocess.run(["zig", "c++", "-target", "wasm32-wasi", "-c", str(source), "-o", str(obj)], check=True)
    functions = {s.name: s for s in read_symbols(obj) if s.kind == SYMBOL_FUNCTION}
    caller, callee = functions["_Z6calleri"], functions["_Z6calleeif"]
    assert caller.strong_global and caller.signature == Signature(I32, I32)
    assert not callee.defined and callee.signature == Signature(("i32", "f32"), I32)


@pytest.mark.skipif(shutil.which("zig") is None, reason="zig is not installed")
def test_line_table_maps_trace_offsets_to_source_lines(tmp_path):
    source = tmp_path / "trap.c"
    source.write_text("int main(void) {\n    __builtin_trap();\n}\n")
    module = tmp_path / "trap.wasm"
    subprocess.run(["zig", "cc", "-target", "wasm32-wasi", "-g", "-O0", str(source), "-o", str(module)], check=True)
    table = LineTable(module)
    row = next(row for row in table.rows if row.path == "trap.c" and row.line == 2)
    offset = table.code_offset + row.address
    assert table.lookup(offset) == row
    trace = f"    at snail.wasm.main (wasm://wasm/x:wasm-function[3]:{offset:#x})"
    assert annotate(trace, table).endswith(f"{offset:#x} [trap.c:2])")


@pytest.mark.skipif(
    shutil.which("node") is None
    or not (REPO_ROOT / "port/zig-out/bin/snail.wasm").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMail.dat").exists(),
    reason="needs node, snail.wasm and SnailMail.dat",
)
def test_original_profile_keeps_upright_hazard_spawns(tmp_path):
    # The Original profile keeps the original's bugs: A1 draws a slug or garbage
    # upright on a tilted cell on three spawn ticks (docs/port/original-bugs.md),
    # and the replay still matches.
    (tmp_path / "SnailMail.dat").symlink_to(REPO_ROOT / "artifacts/bin/SnailMail.dat")
    shutil.copy2(REPO_ROOT / "tests/fixtures/replays/ScoreA.windows-2026-04-17.dat", tmp_path / "ScoreA.dat")
    replay = subprocess.run(
        [
            "node", str(REPO_ROOT / "port/shell/run.mjs"), str(REPO_ROOT / "port/zig-out/bin/snail.wasm"), "--trace",
            "--keys", str(REPO_ROOT / "port/scripts/high_scores.keys"),
            "--replay", "A1",
        ],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    assert replay.stderr.count("upright_hazards 1") == 3
    assert "matches the original" in replay.stderr
    # No Ultimate rule reaches the Original profile.
    assert "padding_segments" not in replay.stderr


@pytest.mark.skipif(
    shutil.which("node") is None
    or not (REPO_ROOT / "port/zig-out/bin/snail.wasm").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMail.dat").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMailExtras.dat").exists(),
    reason="needs node, snail.wasm, SnailMail.dat and SnailMailExtras.dat",
)
def test_ultimate_collects_parcels_within_the_mobile_radius(tmp_path):
    # A1's recorded input drives the mobile course (it diverges from the
    # Windows recording, as intended); Android collects parcels within 1.73,
    # Windows within 1.24.
    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        (tmp_path / name).symlink_to(REPO_ROOT / "artifacts/bin" / name)
    shutil.copy2(REPO_ROOT / "tests/fixtures/replays/ScoreA.windows-2026-04-17.dat", tmp_path / "ScoreMobileA.dat")
    replay = subprocess.run(
        [
            "node", str(REPO_ROOT / "port/shell/run.mjs"), str(REPO_ROOT / "port/zig-out/bin/snail.wasm"),
            "--profile", "ultimate", "--trace", "--keys", str(REPO_ROOT / "port/scripts/high_scores.keys"),
            "--replay", "A1",
        ],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=False,
    )
    # 1.24 to 1.73 from the snail on tick 1064: only the mobile radius takes it.
    assert "tick 1064: parcels 3" in replay.stderr


@pytest.mark.skipif(
    shutil.which("node") is None
    or not (REPO_ROOT / "port/zig-out/bin/snail.wasm").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMail.dat").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMailExtras.dat").exists(),
    reason="needs node, snail.wasm, SnailMail.dat and SnailMailExtras.dat",
)
def test_extras_track_colours_and_random_fringe(tmp_path):
    import struct

    wasm = REPO_ROOT / "port/zig-out/bin/snail.wasm"
    runner = REPO_ROOT / "port/shell/run.mjs"
    (tmp_path / "SnailMail.dat").symlink_to(REPO_ROOT / "artifacts/bin/SnailMail.dat")

    missing = subprocess.run(
        ["node", str(runner), str(wasm), "--profile", "ultimate", "--ticks", "1"],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=False,
    )
    assert missing.returncode == 1
    assert "the ultimate profile needs SnailMailExtras.dat" in missing.stderr

    (tmp_path / "SnailMailExtras.dat").symlink_to(REPO_ROOT / "artifacts/bin/SnailMailExtras.dat")
    cfg = bytearray(196)
    struct.pack_into("<ff", cfg, 0, 1.0, 1.0)
    cfg[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ifi", cfg, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", cfg, 0xA0, 50, 46)
    cfg[0xC0] = 1
    (tmp_path / "SnailMail.cfg").write_bytes(cfg)
    (tmp_path / "SnailMailMobile.cfg").write_bytes(cfg)

    (tmp_path / "postal46.keys").write_text(
        "600 escape\n700 mouse 345 112\n720 click 3\n800 mouse 345 170\n820 click 3\n"
        "900 mouse 210 300\n920 click 3\n1000 mouse 320 300\n"
    )
    postal = subprocess.run(
        ["node", str(runner), str(wasm), "--profile", "ultimate", "--trace", "--keys", str(tmp_path / "postal46.keys")],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    # Android's route card leads with the level numeral and stays on screen.
    assert 'at (50, 127) size 320 x 31 flags 0x20400003 "XLVI: Pomacea cuprina aurea"' in postal.stderr
    assert 'level "70 Gph!" track_set 4 (Objects/World00/Track4.tga)' in postal.stderr

    (tmp_path / "SnailMail.cfg").write_bytes(cfg)
    (tmp_path / "SnailMailMobile.cfg").write_bytes(cfg)
    (tmp_path / "challenge.keys").write_text(
        "600 escape\n700 mouse 345 112\n720 click 3\n800 mouse 345 383\n820 click 3\n"
        "900 mouse 320 320\n920 click 3\n1000 mouse 320 300\n"
    )
    challenge = subprocess.run(
        ["node", str(runner), str(wasm), "--profile", "ultimate", "--warmup", "0", "--trace", "--keys", str(tmp_path / "challenge.keys")],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    # Android lays Padding between each pair of random segments and skips
    # their RAND draws, so the random fringe that follows differs from a
    # build without it.
    assert 'level "Challenge 0" track_set 6 (Objects/World00/Track6.tga) fringe (0.910, 0.094, 1.000)' in challenge.stderr
    assert "padding_segments 35" in challenge.stderr


@pytest.mark.skipif(
    shutil.which("node") is None
    or not (REPO_ROOT / "port/zig-out/bin/snail.wasm").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMail.dat").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMailExtras.dat").exists()
    or not (REPO_ROOT / "artifacts/android/asm_extracted/DATA/O_HALFPOLE.SMO").exists(),
    reason="needs node, snail.wasm, SnailMail.dat, SnailMailExtras.dat and Android .SMO meshes",
)
def test_extras_mobile_path_meshes_and_rings(tmp_path):
    import json
    import struct
    from pathlib import Path

    def parse_smo_unique_verts(path: Path) -> list[tuple[float, float, float]]:
        data = path.read_bytes()
        pos = 0
        while pos + 8 <= len(data):
            tag, _size = struct.unpack_from("<II", data, pos)
            if tag == 0:
                pos += 16
            elif tag == 3:
                n_tex = struct.unpack_from("<I", data, pos + 8)[0]
                pos += 12 + n_tex * 32
            elif tag == 5:
                n_verts = struct.unpack_from("<I", data, pos + 8)[0]
                shorts = struct.unpack_from(f"<{n_verts * 5}h", data, pos + 12)
                seen: list[tuple[float, float, float]] = []
                for i in range(n_verts):
                    v = (
                        shorts[i * 5] * 0.0078125,
                        shorts[i * 5 + 1] * 0.0078125,
                        shorts[i * 5 + 2] * 0.0078125,
                    )
                    if v not in seen:
                        seen.append(v)
                return seen
            else:
                break
        return []

    wasm = REPO_ROOT / "port/zig-out/bin/snail.wasm"
    runner = REPO_ROOT / "port/shell/run.mjs"
    (tmp_path / "SnailMail.dat").symlink_to(REPO_ROOT / "artifacts/bin/SnailMail.dat")
    (tmp_path / "SnailMailExtras.dat").symlink_to(REPO_ROOT / "artifacts/bin/SnailMailExtras.dat")
    dump_script = tmp_path / "dump_paths.mjs"
    dump_script.write_text(
        f"""
import {{ readFile }} from "node:fs/promises";
import {{ WASI }} from "node:wasi";
const wasi = new WASI({{
    version: "preview1",
    args: ["snail.wasm", "--profile", "ultimate", "--ticks", "1"],
    env: {{ ...process.env, PWD: process.cwd() }},
    preopens: {{ "/": "/" }},
    returnOnExit: true,
}});
const bytes = await readFile({json.dumps(str(wasm.resolve()))});
const module = await WebAssembly.compile(bytes);
const instance = await WebAssembly.instantiate(module, wasi.getImportObject());
wasi.start(instance);
const dv = new DataView(instance.exports.memory.buffer);
const out = [];
for (let i = 0; i < 21; ++i) {{
    const pairPtr = instance.exports.snail_extra_path_pair(i);
    const primObj = dv.getUint32(pairPtr + 0x24, true);
    const secObj = dv.getUint32(pairPtr + 0xa8 + 0x24, true);
    const readVerts = (objPtr) => {{
        const count = dv.getInt32(objPtr + 0x2c, true);
        const vertsPtr = dv.getUint32(objPtr + 0x38, true);
        const verts = [];
        for (let v = 0; v < count; ++v) {{
            const base = vertsPtr + v * 12;
            verts.push([
                dv.getFloat32(base, true),
                dv.getFloat32(base + 4, true),
                dv.getFloat32(base + 8, true),
            ]);
        }}
        return verts;
    }};
    out.push({{ primary: readVerts(primObj), secondary: readVerts(secObj) }});
}}
console.log(JSON.stringify(out));
"""
    )
    dump_res = subprocess.run(
        ["node", str(dump_script)],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    dumped = json.loads(dump_res.stdout.splitlines()[-1])
    names = [
        "LOOPTHELOOP1", "SBEND1", "SBEND2", "SBEND4",
        "DETOUR2", "DETOUR3", "DETOUR",
        "SUPERTRAMPLEFT", "TURNOVER2", "TURNOVER3",
        "SHIMMY1", "SHIMMY2", "SHIMMY4", "SHIMMY",
        "INVERT1", "HALFPOLE",
        None, None, "CAGE2", "TWISTER2A", "TWISTER2B",
    ]
    data_dir = REPO_ROOT / "artifacts/android/asm_extracted/DATA"
    for i, name in enumerate(names):
        if name is None:  # entry transition meshes have separate topology
            continue
        prim_smo = parse_smo_unique_verts(data_dir / f"O_{name}.SMO")
        sec_smo = parse_smo_unique_verts(data_dir / f"O_{name}_M.SMO")
        prim_gen = dumped[i]["primary"]
        sec_gen = dumped[i]["secondary"]
        if name.startswith("TWISTER2"):
            # Mobile stores each row's two edges; the PC mesh subdivides its
            # three-cell width. Compare the same geometric boundary points.
            prim_gen = [v for j, v in enumerate(prim_gen) if j % 4 in (0, 3)]
            sec_gen = [v for j, v in enumerate(sec_gen) if j % 4 in (0, 3)]
        if name.startswith(("SBEND", "SHIMMY")):
            # Mobile .SMO bakes 1 quad (2 outer-edge vertices) per row with GL_REPEAT v-UVs,
            # whereas PC build_strip_mesh subdivides each flat row into width_cells unit-UV quads
            # (width_cells + 1 collinear vertices per row). Verify every generated vertex against
            # linear interpolation between the .SMO row's outer edges.
            n_rows = len(prim_smo) // 2
            w_plus_1 = len(prim_gen) // n_rows
            assert len(prim_gen) == len(sec_gen) == n_rows * w_plus_1
            for sign, smo, gen in ((1, prim_smo, prim_gen), (-1, sec_smo, sec_gen)):
                smo_sorted = sorted(smo, key=lambda v: (round(v[2], 2), sign * v[0]))
                for r in range(n_rows):
                    c0, cw = smo_sorted[r * 2], smo_sorted[r * 2 + 1]
                    for c in range(w_plus_1):
                        t = c / (w_plus_1 - 1)
                        gx, gy, gz = gen[r * w_plus_1 + c]
                        ex = c0[0] + t * (cw[0] - c0[0])
                        ey = c0[1] + t * (cw[1] - c0[1])
                        ez = c0[2] + t * (cw[2] - c0[2])
                        assert max(abs(gx - ex), abs(gy - ey), abs(gz - ez)) < 0.009, f"{name} row {r} col {c}"
        else:
            assert len(prim_gen) == len(prim_smo) == len(sec_gen) == len(sec_smo), f"{name} vertex count"
            for smo, gen in ((prim_smo, prim_gen), (sec_smo, sec_gen)):
                fwd = max(min(max(abs(a[0] - b[0]), abs(a[1] - b[1]), abs(a[2] - b[2])) for a in gen) for b in smo)
                rev = max(min(max(abs(a[0] - b[0]), abs(a[1] - b[1]), abs(a[2] - b[2])) for b in smo) for a in gen)
                assert fwd < 0.012 and rev < 0.012, f"{name} error fwd={fwd} rev={rev}"

    shutil.copy2(REPO_ROOT / "tests/fixtures/replays/ScoreA.windows-2026-04-17.dat", tmp_path / "ScoreA.dat")
    shutil.copy2(tmp_path / "ScoreA.dat", tmp_path / "ScoreMobileA.dat")
    replay = subprocess.run(
        [
            "node", str(runner), str(wasm), "--profile", "ultimate", "--trace",
            "--keys", str(REPO_ROOT / "port/scripts/high_scores.keys"),
            "--replay", "A4",
        ],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=False,
    )
    assert replay.returncode == 3
    assert "tramp_rings 1" in replay.stderr
    assert "tramp_rings 0" in replay.stderr
    # Slugfest!'s Trampolines segment lays three-lane trampolines on lanes 0-2
    # and 5-7; Android centres each ring on the middle lane (x = lane - 3.5).
    assert re.findall(r"tramp_rings 1, first at x (\S+)", replay.stderr) == ["-2.50", "2.50", "-2.50"]
    # A Windows replay is intentionally different under mobile pacing and
    # level data. Both ring effects must still run; classic playback stays exact.
    assert "tick 2583: sway_rings 1" in replay.stderr
    assert "first divergence at sample" in replay.stderr

    original = subprocess.run(
        [
            "node", str(runner), str(wasm), "--trace",
            "--keys", str(REPO_ROOT / "port/scripts/high_scores.keys"),
            "--replay", "A4",
        ],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    assert "sway_rings" not in original.stderr
    assert "matches the original" in original.stderr



@pytest.mark.skipif(
    shutil.which("node") is None
    or not (REPO_ROOT / "port/zig-out/bin/snail.wasm").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMail.dat").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMailExtras.dat").exists(),
    reason="needs node, snail.wasm, SnailMail.dat and SnailMailExtras.dat",
)
def test_extras_pro_challenge_galaxy_and_high_scores(tmp_path):
    import json
    import struct

    def scramble_score_bytes(data: bytes) -> bytearray:
        return bytearray(b ^ (i & 0xFF) for i, b in enumerate(data))

    wasm = REPO_ROOT / "port/zig-out/bin/snail.wasm"
    runner = REPO_ROOT / "port/shell/run.mjs"
    (tmp_path / "SnailMail.dat").symlink_to(REPO_ROOT / "artifacts/bin/SnailMail.dat")
    (tmp_path / "SnailMailExtras.dat").symlink_to(REPO_ROOT / "artifacts/bin/SnailMailExtras.dat")

    sprite_script = tmp_path / "check_sprites.mjs"
    sprite_script.write_text(
        f"""
import {{ readFile }} from "node:fs/promises";
import {{ WASI }} from "node:wasi";
const wasi = new WASI({{
    version: "preview1",
    args: ["snail.wasm", "--profile", "ultimate", "--ticks", "1"],
    env: {{ ...process.env, PWD: process.cwd() }},
    preopens: {{ "/": "/" }},
    returnOnExit: true,
}});
const bytes = await readFile({json.dumps(str(wasm.resolve()))});
const module = await WebAssembly.compile(bytes);
const instance = await WebAssembly.instantiate(module, wasi.getImportObject());
wasi.start(instance);
const mem = new Uint8Array(instance.exports.memory.buffer);
const cstr = (ptr) => {{
    let end = ptr;
    while (mem[end]) ++end;
    return new TextDecoder().decode(mem.subarray(ptr, end));
}};
const slots = [22, 27, 500, 502, 503, 504, 506];
console.log(JSON.stringify(Object.fromEntries(slots.map(s => [s, cstr(instance.exports.snail_sprite_texture_name(s))]))));
"""
    )
    sprite_res = subprocess.run(
        ["node", str(sprite_script)],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    sprites = json.loads(sprite_res.stdout.splitlines()[-1])
    assert sprites == {
        "22": "Sprites/Mouse.tga",
        "27": "Sprites/Play.tga",
        "500": "Backgrounds/StarmapProbg.tga",
        "502": "Backgrounds/SplashPro_A.tga",
        "503": "Backgrounds/SplashPro_B.tga",
        "504": "Backgrounds/SpacePro.tga",
        "506": "Backgrounds/SpacePro2.tga",
    }

    score_a_orig = (REPO_ROOT / "tests/fixtures/replays/ScoreA.windows-2026-04-17.dat").read_bytes()
    dec = scramble_score_bytes(score_a_orig)
    rec0_len = struct.unpack_from("<I", dec, 0)[0]
    rec0 = bytearray(dec[:rec0_len])
    struct.pack_into("<I", rec0, 0x2C, 1)
    rec0[0x5C : 0x5C + 20] = b"ProChamp\x00".ljust(20, b"\x00")
    score_pro_orig = bytes(scramble_score_bytes(rec0))
    (tmp_path / "ScoreA.dat").write_bytes(score_a_orig)
    (tmp_path / "ScoreMobileA.dat").write_bytes(score_a_orig)
    (tmp_path / "ScorePro.dat").write_bytes(score_pro_orig)

    cfg = bytearray(196)
    struct.pack_into("<ff", cfg, 0, 1.0, 1.0)
    cfg[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ifi", cfg, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", cfg, 0xA0, 50, 7)
    cfg[0xC0] = 1
    (tmp_path / "SnailMail.cfg").write_bytes(cfg)
    (tmp_path / "SnailMailMobile.cfg").write_bytes(cfg)

    (tmp_path / "pro1.keys").write_text(
        "600 escape\n700 mouse 345 112\n720 click 3\n"
        "800 mouse 345 240\n820 click 3\n"
        "900 mouse 289 287\n920 click 3\n"
    )
    pro1 = subprocess.run(
        ["node", str(runner), str(wasm), "--profile", "ultimate", "--trace", "--ticks", "1000", "--keys", str(tmp_path / "pro1.keys")],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    assert '"Pro-Challenge"' in pro1.stderr
    # Android keeps the postal map's title on the Pro map.
    assert '"Intergalactic Delivery Route"' in pro1.stderr
    assert "Special Assignment" not in pro1.stderr
    assert '"I: Limax maximus"' in pro1.stderr
    assert "lives 8" in pro1.stderr  # a new Pro game, as on Android
    assert 'level "Pros Only" track_set 5 (Objects/World00/Track5.tga) fringe (0.871, 1.000, 0.039)' in pro1.stderr
    # save_game() runs at the end of pro1 while g_pro_state_swapped == true inside "Pros Only"
    assert struct.unpack("<ii", (tmp_path / "SnailMailPro.cfg").read_bytes()) == (1, 1)
    assert struct.unpack_from("<ii", (tmp_path / "SnailMail.cfg").read_bytes(), 0xA0) == (50, 7)
    assert (tmp_path / "ScoreA.dat").read_bytes() == score_a_orig
    assert (tmp_path / "ScorePro.dat").read_bytes() == score_pro_orig
    (tmp_path / "SnailMailPro.cfg").write_bytes(struct.pack("<ii", 10, 10))
    (tmp_path / "pro10.keys").write_text(
        "600 escape\n700 mouse 345 112\n720 click 3\n"
        "800 mouse 345 240\n820 click 3\n"
        "900 mouse 248 414\n920 click 3\n"
    )
    pro10 = subprocess.run(
        ["node", str(runner), str(wasm), "--profile", "ultimate", "--trace", "--ticks", "1000", "--keys", str(tmp_path / "pro10.keys")],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    assert '"X: Ariolimax columbianus"' in pro10.stderr
    assert 'level "Eximius Ferreus" track_set 6 (Objects/World00/Track6.tga) fringe (1.000, 0.980, 0.196)' in pro10.stderr
    assert struct.unpack("<ii", (tmp_path / "SnailMailPro.cfg").read_bytes()) == (10, 10)
    assert struct.unpack_from("<ii", (tmp_path / "SnailMail.cfg").read_bytes(), 0xA0) == (50, 7)
    assert (tmp_path / "ScoreA.dat").read_bytes() == score_a_orig
    assert (tmp_path / "ScorePro.dat").read_bytes() == score_pro_orig
    (tmp_path / "hs_quit.keys").write_text(
        "600 escape\n700 mouse 345 180\n720 click 3\n"
        "800 mouse 420 400\n820 click 3\n"
        "900 mouse 420 400\n920 click 3\n"
        "1000 mouse 210 400\n1020 click 3\n"
        "1120 mouse 345 393\n1140 click 3\n"
        "1200 mouse 239 292\n1220 click 3\n"
    )
    hs = subprocess.run(
        ["node", str(runner), str(wasm), "--profile", "ultimate", "--trace", "--ticks", "1400", "--keys", str(tmp_path / "hs_quit.keys")],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    postal_view = hs.stderr.split("tick 833:")[0]
    pro_view = hs.stderr.split("tick 933:")[1]
    assert '"Postal High Scores"' in postal_view and '"banteg"' in postal_view and '"ProChamp"' not in postal_view
    assert '"Pro Scores"' in hs.stderr
    assert '"Pro High Scores"' in pro_view and '"ProChamp"' in pro_view
    assert "snail: quit requested" in hs.stderr
    assert (tmp_path / "ScoreA.dat").read_bytes() == score_a_orig
    assert (tmp_path / "ScorePro.dat").read_bytes() == score_pro_orig
    assert struct.unpack_from("<ii", (tmp_path / "SnailMail.cfg").read_bytes(), 0xA0) == (50, 7)
