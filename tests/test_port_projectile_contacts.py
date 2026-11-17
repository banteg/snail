"""Asteroid contacts in the real laser and homing-rocket actor updates."""

import json
import shutil
import struct
import subprocess

import pytest

from snail.port_lockstep import layout_offsets
from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
ASSETS = REPO_ROOT / "artifacts/bin"
ARCHIVES = ("SnailMail.dat", "SnailMailExtras.dat")
CONTACT_LAYOUT = (
    ("asteroid_tile", "SUBLOC_TILE_GARBAGE_HAZARD"),
    ("asteroid_head", "offsetof(cRSubGame, garbage_hazards.active_head)"),
    ("asteroid_next", "offsetof(cRSubGarbage, next_active)"),
    ("asteroid_state", "offsetof(cRSubGarbage, state)"),
    ("asteroid_radius", "offsetof(cRSubGarbage, radius)"),
    ("asteroid_pos", "offsetof(cRSubGarbage, transform.position)"),
    ("shot_pos", "offsetof(cRSubGolb, flight_transform.position)"),
    ("shot_prev", "offsetof(cRSubGolb, previous_flight_transform.position)"),
    ("shot_follow", "offsetof(cRSubGolb, path_follow.active)"),
    ("shot_velocity", "offsetof(cRSubGolb, velocity)"),
    ("shot_target", "offsetof(cRSubGolb, homing_target)"),
    ("shot_target_object", "offsetof(cRSubGolb, homing_target_object)"),
)


@pytest.fixture(scope="module")
def contact_env(port_layout_env):
    layout = json.loads(port_layout_env["SNAIL_LAYOUT"])
    layout.update(layout_offsets(REPO_ROOT, CONTACT_LAYOUT, port=True))
    return {**port_layout_env, "SNAIL_LAYOUT": json.dumps(layout)}


@pytest.mark.skipif(
    not shutil.which("node")
    or not WASM.exists()
    or not all((ASSETS / name).exists() for name in ARCHIVES),
    reason="needs the browser port and both game archives",
)
@pytest.mark.parametrize("ultimate", [False, True], ids=["original", "ultimate"])
def test_projectile_contacts(tmp_path, contact_env, ultimate):
    for name in ARCHIVES:
        shutil.copyfile(ASSETS / name, tmp_path / name)
    config = bytearray(196)
    config[0x60:0x65] = b"Probe"
    config[0xC0] = 1
    struct.pack_into("<ii", config, 0xA0, 1, 1)
    (tmp_path / ("SnailMailMobile.cfg" if ultimate else "SnailMail.cfg")).write_bytes(
        config
    )
    run = subprocess.run(
        [
            "node",
            str(REPO_ROOT / "tests/port_projectile_contacts.mjs"),
            str(WASM),
            str(int(ultimate)),
        ],
        cwd=tmp_path,
        env=contact_env,
        capture_output=True,
        text=True,
        timeout=60,
        check=False,
    )
    assert run.returncode == 0, run.stderr
    result = json.loads(run.stdout.splitlines()[-1])
    # A laser pierces an endpoint contact and continues. Only Ultimate also
    # bursts the asteroid between samples. The off-axis and past-end misses stay live.
    assert result["laser"] == {
        "hits": [ultimate, True, False, False],
        "score": 20 if ultimate else 10,
        "live": True,
    }
    # A real impact bursts the target and one neighbour in splash range.
    hit = {"hits": [True, True, False, False], "score": 20, "live": False}
    miss = {"hits": [False, False, False, False], "score": 0, "live": False}
    assert result["pointBlank"] == (hit if ultimate else miss)
    assert result["ordinary"] == hit
    assert result["stale"] == miss
