"""Android's time-trial death fade and firework draws on the Ultimate course."""

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
    not shutil.which("node")
    or not WASM.exists()
    or not all((ASSETS / name).exists() for name in ARCHIVES),
    reason="needs browser WASM, Node and both game archives",
)
def test_time_trial_collision_matches_android(tmp_path, port_layout_env):
    for name in ARCHIVES:
        shutil.copyfile(ASSETS / name, tmp_path / name)
    config = bytearray(196)
    config[0x60:0x65] = b"Probe"
    struct.pack_into("<ii", config, 0xA0, 1, 1)
    config[0xC0] = 1
    draws = []
    for particles, cadence in (("off", "single"), ("on", "single"), ("on", "catch-up")):
        struct.pack_into("<I", config, 0x1C, 0x10 if particles == "on" else 0)
        (tmp_path / "SnailMailMobile.cfg").write_bytes(config)
        result = subprocess.run(
            ["node", str(REPO_ROOT / "tests/port_android_fade.mjs"), str(WASM), particles, cadence],
            cwd=tmp_path, env=port_layout_env, capture_output=True, text=True, check=True, timeout=90,
        )  # fmt: skip
        trace = json.loads(result.stdout.splitlines()[-1])
        # Both binaries request the fade 242 ticks after impact. Android is
        # black at 259, holds three ticks, and finishes fading in at 280.
        render_delay = 2 if cadence == "catch-up" else 0
        assert trace["transitions"] == [
            [242, 2],
            [259 + render_delay, 5],
            [262 + render_delay, 1],
            [280 + render_delay, 0],
        ]
        draws.append(trace["draws"])
    assert draws[0] == draws[1] == draws[2]
