"""A seeded Challenge finish and a SLALOM edge sample in each profile."""

import json
import shutil
import struct
import subprocess

import pytest

from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
ASSETS = REPO_ROOT / "artifacts/bin"


@pytest.mark.skipif(
    shutil.which("node") is None
    or not WASM.exists()
    or not all((ASSETS / name).exists() for name in ("SnailMail.dat", "SnailMailExtras.dat")),
    reason="needs node, browser WASM and both game archives",
)
@pytest.mark.parametrize(
    ("profile", "seed", "finish", "center"),
    [("ultimate", 318, 1739, 0.915438354), ("original", 31141, 1755, 0.918967664)],
)
def test_course_math_at_segment_and_path_edges(tmp_path, port_layout_env, profile, seed, finish, center):
    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        shutil.copyfile(ASSETS / name, tmp_path / name)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    struct.pack_into("<ifi", config, 0x40, 40, 0.5, 40)
    config[0x60:0x65] = b"Probe"
    config[0xC0] = 1
    save = "SnailMailMobile.cfg" if profile == "ultimate" else "SnailMail.cfg"
    (tmp_path / save).write_bytes(config)
    result = subprocess.run(
        ["node", str(REPO_ROOT / "tests/port_course_math.mjs"), str(WASM), profile],
        cwd=tmp_path, env=port_layout_env, capture_output=True, text=True, check=True,
    )
    course = json.loads(result.stdout.splitlines()[-1])
    assert (course["seed"], course["finishRow"]) == (seed, finish)
    # At sample 19, x=2.988 is just inside Android's SLALOM traversal boundary.
    assert course["slalomCenter"] == pytest.approx(center, abs=1e-6)
