"""Exercise bracket mirroring and bobbing heart pickup on an authored course in each profile."""

import json
import re
import shutil
import struct
import subprocess

import pytest

from snail.archive import parse_archive_index, read_archive_entry, write_archive
from snail.port_lockstep import layout_offsets
from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
ASSETS = REPO_ROOT / "artifacts/bin"
ARCHIVES = ("SnailMail.dat", "SnailMailExtras.dat")

pytestmark = pytest.mark.skipif(
    not shutil.which("node")
    or not WASM.exists()
    or not all((ASSETS / name).exists() for name in ARCHIVES),
    reason="needs the browser port, node and both archives",
)


@pytest.fixture(scope="module")
def course(tmp_path_factory):
    directory = tmp_path_factory.mktemp("bracket-ramp-course")
    segment = (
        b"ID:0\r\nName:'Brackets'\r\nData:\r\n@@@@@@@@@@\r\n@[..]$...@\r\n"
        + b"@........@\r\n" * 16
        + b"@@@@@@@@@@\r\n"
    )
    for name in ARCHIVES:
        archive = ASSETS / name
        files = {
            e.path.upper(): read_archive_entry(archive, e)
            for e in parse_archive_index(archive).entries
        }
        level_path = "LEVELS/ARCADE001.TXT"
        if level_path in files:
            level = re.sub(
                rb"(Segments Begin:[^\r\n]*\r?\n).*?(Segments End:)",
                lambda match: match[1] + b"Brackets.txt\r\n" * 16 + match[2],
                files[level_path],
                flags=re.DOTALL,
            )
            files[level_path] = re.sub(
                rb"(Parcels|Salt|Garbage):\d+", rb"\g<1>:0", level
            )
        files["SEGMENTS/BRACKETS.TXT"] = segment
        write_archive(directory / name, files)
    config = bytearray(196)
    config[0x60:0x65] = b"Probe"
    config[0xC0] = 1
    struct.pack_into("<ii", config, 0xA0, 1, 1)
    for name in ("SnailMail.cfg", "SnailMailMobile.cfg"):
        (directory / name).write_bytes(config)
    return directory


@pytest.fixture(scope="module")
def probe_env(port_layout_env):
    fields = (
        ("mirrored", "SUBROW_FLAG_MIRRORED"),
        ("lean", "offsetof(cRSubGoldy, lane_lean_state)"),
        ("amplitude", "offsetof(cRSubGoldy, lane_lean_amplitude)"),
        ("hearts", "offsetof(cRSubGame, health_pickups)"),
        ("heart_size", "sizeof(cRSubHealth)"),
        ("heart_state", "offsetof(cRSubHealth, state)"),
        ("heart_position", "offsetof(cRSubHealth, position)"),
        ("heart_phase", "offsetof(cRSubHealth, bob_phase)"),
        ("heart_sprite", "offsetof(cRSubHealth, sprite)"),
        ("sprite_position", "offsetof(cRSprite, position)"),
        ("anchor", "offsetof(cRSubGoldy, track_z_anchor)"),
        ("offset", "offsetof(cRSubGoldy, track_z_offset)"),
    )
    return {
        **port_layout_env,
        "RAMP_HEART_LAYOUT": json.dumps(layout_offsets(REPO_ROOT, fields, port=True)),
    }


@pytest.mark.parametrize("ultimate", [False, True])
def test_bracket_hands_and_heart_volume(course, probe_env, ultimate):
    result = subprocess.run(
        [
            "node",
            str(REPO_ROOT / "tests/port_ramps_and_hearts.mjs"),
            str(WASM),
            str(int(ultimate)),
        ],
        cwd=course,
        env=probe_env,
        capture_output=True,
        text=True,
        check=True,
    )
    report = json.loads(result.stdout.splitlines()[-1])
    # Pairs are ordered by the original authored glyph, '[' then ']'.
    assert report["mirrored"] == ([7, 5] if ultimate else [5, 2])
    assert report["plain"][0] == 5
    assert (report["plain"][1] == 7) == ultimate
    assert report["plainRoll"][0] == 1
    if ultimate:
        assert report["plainRoll"][1] == -1
    assert report["mirroredRoll"] == ([-1, 1] if ultimate else [1, 1])
    assert report["heart"] == {"above": False, "raised": ultimate, "ground": True}
