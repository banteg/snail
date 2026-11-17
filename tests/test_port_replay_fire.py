"""Live shots and playback flags in the Ultimate and Original browser runtimes."""

import json
import shutil
import struct
import subprocess

import pytest

from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
ASSETS = REPO_ROOT / "artifacts/bin"
ARCHIVES = ("SnailMail.dat", "SnailMailExtras.dat")


@pytest.mark.skipif(
    not shutil.which("node") or not WASM.exists() or not all((ASSETS / name).exists() for name in ARCHIVES),
    reason="needs the browser port and both game archives",
)
@pytest.mark.parametrize("ultimate", [True, False], ids=["ultimate", "original"])
def test_live_and_replayed_shots(tmp_path, port_layout_env, ultimate):
    for archive in ARCHIVES:
        shutil.copyfile(ASSETS / archive, tmp_path / archive)
    config = bytearray(196)
    config[0x60:0x65] = b"Probe"
    config[0xC0] = 1
    struct.pack_into("<ii", config, 0xA0, 1, 1)
    (tmp_path / ("SnailMailMobile.cfg" if ultimate else "SnailMail.cfg")).write_bytes(config)
    run = subprocess.run(
        ["node", str(REPO_ROOT / "tests/port_replay_fire.mjs"), str(WASM), "ultimate" if ultimate else "original"],
        cwd=tmp_path, env=port_layout_env, capture_output=True, text=True, check=True, timeout=60,
    )
    result = json.loads(run.stdout.splitlines()[-1])
    live = result["live"]
    assert sum(frame["shot"] for frame in live) >= 2
    assert any(frame["flags"] & 3 and not frame["shot"] for frame in live)
    for frame in live:
        assert bool(frame["flags"] & 0x40) == (ultimate and frame["shot"])
    # A tap without a shot, a recorded shot, a shot during cooldown, and a
    # physically allocated slot just beyond the record's declared sample count.
    assert result["played"] == ([False, True, True, False] if ultimate else [True, True, False, True])
