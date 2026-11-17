"""Ultimate's salt draw opacity and route card quotation marks in the browser renderer."""

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
    reason="needs node, browser WASM, and the game archives",
)
@pytest.mark.parametrize("profile", ["original", "ultimate"])
def test_salt_draw_and_font_glyphs(tmp_path, port_layout_env, profile):
    for name in ARCHIVES:
        shutil.copyfile(ASSETS / name, tmp_path / name)
    cfg = bytearray(196)
    cfg[0x60:0x65] = b"Probe"
    struct.pack_into("<ii", cfg, 0xA0, 1, 1)
    cfg[0xC0] = 1
    config_name = "SnailMail.cfg" if profile == "original" else "SnailMailMobile.cfg"
    (tmp_path / config_name).write_bytes(cfg)
    run = subprocess.run(
        ["node", str(REPO_ROOT / "tests/port_salt_and_font.mjs"), str(WASM), profile],
        cwd=tmp_path,
        env=port_layout_env,
        capture_output=True,
        text=True,
        check=True,
    )
    result = json.loads(run.stdout.splitlines()[-1])
    # A double quote, an apostrophe and a space with font shadows off.
    assert result["glyphs"] == [int(profile == "ultimate"), 1, 0]
    assert result["pair"] == ([0, 229] if profile == "ultimate" else [255])
    samples = [result["spawn"], *result["samples"]]
    assert 0 < samples[0]["distance"] < 48
    for sample in samples:
        if profile == "ultimate":
            fade = min(1.0, max(0.0, 1.0 - sample["distance"] / 48.0))
            # The player can move during the same tick, after the salt update.
            assert sample["tint"] == pytest.approx(0.9 * fade, abs=0.005)
            assert sample["drawn"] == [int(sample["tint"] * 255)]
        else:
            assert sample["tint"] == pytest.approx(0.9)
            assert sample["drawn"] == [255]
