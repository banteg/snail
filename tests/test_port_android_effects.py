"""Runtime particle counts and random draws measured on the Android ARM and PC builds."""

import itertools
import json
import math
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
    reason="needs the browser port and both game archives",
)
@pytest.mark.parametrize("ultimate", [False, True], ids=["original", "ultimate"])
def test_actor_effects_and_star_rng(tmp_path, port_layout_env, ultimate):
    for name in ARCHIVES:
        shutil.copyfile(ASSETS / name, tmp_path / name)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    struct.pack_into("<I", config, 0x1C, 0x14)  # star field and particles
    config[0x60:0x65] = b"Probe"
    struct.pack_into("<ii", config, 0xA0, 1, 1)
    config[0xC0] = 1
    (tmp_path / ("SnailMailMobile.cfg" if ultimate else "SnailMail.cfg")).write_bytes(
        config
    )
    run = subprocess.run(
        [
            "node",
            str(REPO_ROOT / "tests/port_android_effects.mjs"),
            str(WASM),
            "ultimate" if ultimate else "original",
        ],
        cwd=tmp_path,
        env=port_layout_env,
        capture_output=True,
        text=True,
        check=False,
        timeout=60,
    )
    assert run.returncode == 0, run.stderr
    effects = json.loads(run.stdout.splitlines()[-1])

    # Both releases read the same 8191-entry MSVC table. Invert each blink
    # sample to recover the draw; ARM consumes a guard draw before the value.
    table = []
    seed = 1
    for _ in range(8191):
        seed = (seed * 214013 + 2531011) & 0xFFFFFFFF
        table.append(seed >> 16 & 0x7FFF)
    stride = 2 if ultimate else 1
    blinks = [round((1 / (60 * sample) - 1) * 32768) for sample in effects["blinks"]]
    assert blinks == table[stride : 25 * stride : stride]

    # A later star starts by drawing its alpha. Subsequent alphas are four
    # draws apart on ARM (one direction angle), five on PC (two components).
    alphas = [
        round((alpha - 0.4) * 16384 / 0.1 + 16384) for alpha, _, _ in effects["stars"]
    ]
    stride = 4 if ultimate else 5
    cycle = table + table[: 3 * stride]
    starts = [
        i for i in range(len(table)) if cycle[i : i + 3 * stride : stride] == alphas
    ]
    assert len(starts) == 1
    if ultimate:
        for n, (_, vx, vy) in enumerate(effects["stars"]):
            # Android uses one turn uniformly distributed over the circle.
            # Its sine/cosine lookup table has 32768 entries per turn.
            angle = cycle[starts[0] + stride * n + 1] * math.tau / 32768
            speed = math.hypot(vx, vy)
            assert (vx / speed, vy / speed) == pytest.approx(
                (math.sin(angle), math.cos(angle)), abs=math.tau / 32768
            )

    stars = sorted(effects["ring"], key=lambda s: s[1])
    count = 8 if ultimate else 10
    assert len(stars) == count
    assert [size for size, _ in stars] == pytest.approx(
        [0.9 if ultimate else 0.72] * count
    )
    spacing = [b[1] - a[1] for a, b in itertools.pairwise(stars)]
    assert spacing == pytest.approx([math.tau / count] * (count - 1), abs=1e-5)
    assert effects["slugs"] > 0
    assert effects["debris"] == effects["slugs"] * (20 if ultimate else 70)
    assert effects["jets"] == ([0] * 4 if ultimate else [3] * 4)
    assert effects["smoke"] == ([2, 0, 0, 0] if ultimate else [2] * 4)
    assert effects["ringSurvivors"] == 0
