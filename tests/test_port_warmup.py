"""Original makes the startup warmup draws; Ultimate makes none, as Android's AppInit does."""

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
def test_warmup_moves_the_challenge_seed_only_in_original(tmp_path, profile):
    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        (tmp_path / name).symlink_to(ASSETS / name)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
    config[0xC0] = 1

    def run(warmup, keys, ticks):
        for name in ("SnailMail.cfg", "SnailMailMobile.cfg"):
            (tmp_path / name).write_bytes(config)
        (tmp_path / "challenge.keys").write_text(keys)
        return subprocess.run(
            ["node", str(REPO_ROOT / "port/shell/run.mjs"), str(WASM), "--profile", profile, "--trace",
             "--warmup", str(warmup), "--ticks", str(ticks), "--keys", str(tmp_path / "challenge.keys")],
            cwd=tmp_path, capture_output=True, text=True, check=True,
        ).stderr  # fmt: skip

    keys = "600 escape\n700 mouse 345 112\n720 click 3\n"
    menu = run(0, keys, 800)
    x, y, w, h = map(int, re.findall(r'at \((\d+), (\d+)\) size (\d+) x (\d+) .*"Challenge Mode"', menu)[-1])
    keys += f"780 mouse {x + w // 2} {y + h // 2}\n800 click 3\n900 mouse 320 320\n920 click 3\n"
    levels = [re.search(r'level "Challenge 0".*', run(warmup, keys, 1000))[0] for warmup in (0, 37)]
    # The Challenge seed is BuildLevel's RAND(32768), drawn after the warmup.
    assert (levels[0] != levels[1]) == (profile == "original")
