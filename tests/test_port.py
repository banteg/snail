"""Port build inputs: source selection, generated data and link forwarders."""

import json
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
        ["node", str(runner), str(wasm), "--extras", "--ticks", "1"],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=False,
    )
    assert missing.returncode == 1
    assert "requires SnailMailExtras.dat" in missing.stderr

    (tmp_path / "SnailMailExtras.dat").symlink_to(REPO_ROOT / "artifacts/bin/SnailMailExtras.dat")
    cfg = bytearray(196)
    struct.pack_into("<ff", cfg, 0, 1.0, 1.0)
    cfg[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ifi", cfg, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", cfg, 0xA0, 50, 46)
    cfg[0xC0] = 1
    (tmp_path / "SnailMail.cfg").write_bytes(cfg)

    (tmp_path / "postal46.keys").write_text(
        "600 escape\n700 mouse 345 112\n720 click 3\n800 mouse 345 170\n820 click 3\n"
        "900 mouse 480 300\n920 click 3\n1000 mouse 320 300\n"
    )
    postal = subprocess.run(
        ["node", str(runner), str(wasm), "--extras", "--trace", "--keys", str(tmp_path / "postal46.keys")],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    assert 'level "70 Gph!" track_set 4 (Objects/World00/Track4.tga)' in postal.stderr

    (tmp_path / "SnailMail.cfg").write_bytes(cfg)
    (tmp_path / "challenge.keys").write_text(
        "600 escape\n700 mouse 345 112\n720 click 3\n800 mouse 345 310\n820 click 3\n"
        "900 mouse 320 320\n920 click 3\n1000 mouse 320 300\n"
    )
    challenge = subprocess.run(
        ["node", str(runner), str(wasm), "--extras", "--warmup", "0", "--trace", "--keys", str(tmp_path / "challenge.keys")],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    assert 'level "Challenge 0" track_set 6 (Objects/World00/Track6.tga) fringe (0.733, 0.000, 1.000)' in challenge.stderr
