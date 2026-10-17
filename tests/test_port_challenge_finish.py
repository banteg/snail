"""Ultimate lays a Challenge course's finish as Android does (port/patches/22-challenge-finish.patch)."""

import re
import shutil
import struct
import subprocess

import pytest

from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail.wasm"
ASSETS = REPO_ROOT / "artifacts/bin"


@pytest.mark.skipif(
    shutil.which("node") is None
    or not WASM.exists()
    or not all((ASSETS / name).exists() for name in ("SnailMail.dat", "SnailMailExtras.dat")),
    reason="needs node, snail.wasm and both game archives",
)
@pytest.mark.parametrize("profile", ["original", "ultimate"])
def test_challenge_finish_pieces(tmp_path, profile):
    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        (tmp_path / name).symlink_to(ASSETS / name)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
    config[0xC0] = 1
    for name in ("SnailMail.cfg", "SnailMailMobile.cfg"):
        (tmp_path / name).write_bytes(config)

    def run(keys, ticks):
        (tmp_path / "challenge.keys").write_text(keys)
        return subprocess.run(
            ["node", str(REPO_ROOT / "port/shell/run.mjs"), str(WASM), "--profile", profile, "--trace",
             "--ticks", str(ticks), "--keys", str(tmp_path / "challenge.keys")],
            cwd=tmp_path, capture_output=True, text=True, check=True,
        ).stderr  # fmt: skip

    keys = "600 escape\n700 mouse 345 112\n720 click 3\n"
    menu = run(keys, 800)
    x, y, w, h = map(int, re.findall(r'at \((\d+), (\d+)\) size (\d+) x (\d+) .*"Challenge Mode"', menu)[-1])
    trace = run(keys + f"780 mouse {x + w // 2} {y + h // 2}\n800 click 3\n900 mouse 320 320\n920 click 3\n", 1000)
    assert 'level "Challenge 0"' in trace
    pieces = int(re.search(r"finish rows \d+ pieces (\d+)", trace)[1])
    # Windows lays the Finish segment whole; Android lays it in pieces as long
    # as the random picks that carry on past the finish line.
    assert pieces == 1 if profile == "original" else pieces > 1
