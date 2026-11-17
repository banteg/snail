"""Short mouse presses through the reactor and elapsed time at both hosts' clock boundaries."""

import json
import shutil
import subprocess

import pytest

from snail.port_lockstep import layout_offsets
from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
ASSETS = REPO_ROOT / "artifacts/bin"
ARCHIVES = ("SnailMail.dat", "SnailMailExtras.dat")


def test_sdl_clock_at_long_uptime(tmp_path):
    if not shutil.which("c++"):
        pytest.skip("needs c++")
    source = tmp_path / "clock.cpp"
    source.write_text("""
#include "frame_clock.h"
#include <cassert>
#include <cmath>

int main() {
    const uint64_t starts[] = {8ULL * 86400 * 1000000000, ((1ULL << 32) - 16) * 1000000};
    for (uint64_t start : starts) {
        FrameClock clock{start};
        for (unsigned frame = 1; frame <= 60; ++frame)
            assert(std::fabs(clock.elapsed_seconds(start + frame * 16666667ULL) - 1.0f / 60) < 1e-7f);
        assert(clock.elapsed_seconds(start + 10000000000ULL) == 1);
    }
}
""")
    binary = tmp_path / "clock"
    subprocess.run(
        ["c++", "-std=c++17", "-I", REPO_ROOT / "port/native", source, "-o", binary],
        check=True,
    )
    subprocess.run([binary], check=True)


def test_animation_clock_at_long_uptime():
    if not shutil.which("node"):
        pytest.skip("needs node")
    script = """
import assert from 'node:assert/strict';
import { scheduleFrames } from './port/web/frame-clock.js';

for (const start of [8 * 86400_000, 2 ** 32 - 16]) {
  let now = start, next;
  const deltas = [];
  Object.defineProperty(globalThis, 'performance', {configurable: true, value: {now: () => now}});
  globalThis.requestAnimationFrame = cb => { next = cb; };
  const reset = scheduleFrames(delta => { deltas.push(delta); return true; });
  for (let i = 1; i <= 60; ++i) next(now = start + i * 1000 / 60);
  assert.equal(deltas.length, 60);
  assert(deltas.every(delta => Math.abs(delta - 1 / 60) < 1e-8));
  next(now += 5000);
  assert.equal(deltas.at(-1), 1);
  now += 5000; reset(); next(now += 16);
  assert.equal(deltas.at(-1), 0.016);
}
"""
    subprocess.run(
        ["node", "--input-type=module", "-e", script], cwd=REPO_ROOT, check=True
    )


@pytest.mark.skipif(
    not shutil.which("zig")
    or not shutil.which("node")
    or not WASM.is_file()
    or not all((ASSETS / archive).is_file() for archive in ARCHIVES),
    reason="needs zig, node, the browser WASM and game archives",
)
@pytest.mark.parametrize("ultimate", [False, True], ids=["original", "ultimate"])
def test_mouse_transitions_between_ticks(tmp_path, port_layout_env, ultimate):
    for name in ARCHIVES:
        shutil.copyfile(ASSETS / name, tmp_path / name)
    name = "ClickProbe"
    config = bytearray(196)
    config[0x60 : 0x60 + len(name)] = name.encode()
    config[0xA0] = config[0xA4] = config[0xC0] = 1
    (tmp_path / ("SnailMailMobile.cfg" if ultimate else "SnailMail.cfg")).write_bytes(
        config
    )
    layout = json.loads(port_layout_env["SNAIL_LAYOUT"])
    layout.update(
        layout_offsets(
            REPO_ROOT,
            (
                ("pressed", "offsetof(cRGame, game_inputs[0].input.pressed_buttons)"),
                ("held", "offsetof(cRGame, game_inputs[0].input.previous_buttons)"),
                ("click_state", "offsetof(cRSubGame, player.click_start.state)"),
            ),
            port=True,
        )
    )
    subprocess.run(
        [
            "node",
            REPO_ROOT / "tests/port_mouse_transitions.mjs",
            WASM,
            str(int(ultimate)),
            name,
        ],
        cwd=tmp_path,
        env={**port_layout_env, "SNAIL_LAYOUT": json.dumps(layout)},
        check=True,
        timeout=90,
    )
