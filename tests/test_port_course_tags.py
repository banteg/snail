"""The four course-data corrections use the stock PC and mobile archives in their respective profiles."""

import json
import shutil
import struct
import subprocess

import pytest

from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
SCRIPT = REPO_ROOT / "tests/port_course_tags.mjs"
ASSETS = REPO_ROOT / "artifacts/bin"
ARCHIVES = ("SnailMail.dat", "SnailMailExtras.dat")
pytestmark = pytest.mark.skipif(
    not shutil.which("node")
    or not WASM.exists()
    or not all((ASSETS / name).exists() for name in ARCHIVES),
    reason="needs node, browser WASM and both game archives",
)


@pytest.fixture(params=["original", "ultimate"])
def course(request, tmp_path, port_layout_env):
    ultimate = request.param == "ultimate"
    for name in ARCHIVES:
        shutil.copyfile(ASSETS / name, tmp_path / name)

    def open_route(route, scenario="postal"):
        config = bytearray(196)
        struct.pack_into("<ff", config, 0, 1.0, 1.0)
        struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
        config[0x60:0x65] = b"Probe"
        struct.pack_into("<ii", config, 0xA0, 50, route)
        config[0xC0] = 1
        save = "SnailMailMobile.cfg" if ultimate else "SnailMail.cfg"
        (tmp_path / save).write_bytes(config)
        result = subprocess.run(
            ["node", str(SCRIPT), str(WASM), request.param, scenario],
            cwd=tmp_path,
            env=port_layout_env,
            capture_output=True,
            text=True,
            check=True,
            timeout=60,
        )
        return json.loads(result.stdout.splitlines()[-1])

    return ultimate, open_route


@pytest.mark.parametrize(
    ("route", "stock_first"), [(6, "parceltest.txt"), (7, "parceltest2.txt")]
)
def test_header_line_wibble(course, route, stock_first):
    ultimate, open_route = course
    result = open_route(route)
    # Android's VI already has the newline; VII still has the inline filename.
    assert (result["first"], result["count"]) == (
        ("wibble.txt", 13) if ultimate else (stock_first, 12)
    )


def test_loopy_ambient_garbage(course):
    ultimate, open_route = course
    assert open_route(3)["garbage"] == pytest.approx(0.1 if ultimate else -0.01)


def test_tutorial_explosive_ring(course):
    ultimate, open_route = course
    assert open_route(1, "tutorial")["explosive"] is ultimate


def test_supertramp_airborne_drag(course):
    ultimate, open_route = course
    result = open_route(47, "supertramp")
    assert result["noFall"] == (48 if ultimate else 0)
    assert result["speed"] == pytest.approx(0.349 if ultimate else 0.291, abs=0.001)
