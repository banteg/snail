"""Check the actual GPU-bound UVs for full-image mobile skies."""

import io
import json
import shutil
import struct
import subprocess

import pytest
from PIL import Image

from snail.archive import parse_archive_index, read_archive_entry
from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
ASSETS = REPO_ROOT / "artifacts/bin"


@pytest.mark.skipif(
    shutil.which("node") is None
    or not WASM.exists()
    or not all(
        (ASSETS / name).exists() for name in ("SnailMail.dat", "SnailMailExtras.dat")
    ),
    reason="needs browser WASM, node, and game archives",
)
def test_mobile_skies_match_android_zoom_distortion_and_rng(tmp_path, port_layout_env):
    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        shutil.copyfile(ASSETS / name, tmp_path / name)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    config[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", config, 0xA0, 1, 1)
    config[0xC0] = 1
    (tmp_path / "SnailMailMobile.cfg").write_bytes(config)
    signatures = {}
    for name in ("SpacePro", "SpacePro2", "SpacePurple"):
        archive = ASSETS / (
            "SnailMail.dat" if name == "SpacePurple" else "SnailMailExtras.dat"
        )
        entry = parse_archive_index(archive).entry_by_path(f"Backgrounds/{name}.tga")
        image = Image.open(io.BytesIO(read_archive_entry(archive, entry))).convert(
            "RGBA"
        )
        signatures[name] = image.tobytes()[:64].hex()
    result = subprocess.run(
        [
            "node",
            str(REPO_ROOT / "tests/port_mobile_backgrounds.mjs"),
            str(WASM),
            json.dumps(signatures),
        ],
        cwd=tmp_path,
        env=port_layout_env,
        capture_output=True,
        text=True,
        check=False,
    )
    assert result.returncode == 0, result.stderr[-1400:]
    data = json.loads(result.stdout.splitlines()[-1])
    assert data["course"]["target"] == pytest.approx(data["course"]["z"] / 36000)
    assert data["worm"]["target"] == pytest.approx(0.1, abs=2e-4)
    draws = data["draws"]
    assert len(draws) == 10
    # ARM cRBackdrop::SetDistort(10), gRMathRand2Index=123, then one AI tick.
    # The oracle sends bottom-up JPEG V; the port uploads its TGA top-first.
    android_centers = {640: (0.49786076, 0.51019654), 320: (0.50558132, 0.49995208)}
    for draw in draws:
        pro = draw["name"] != "SpacePurple"
        assert draw["size"] == ([512, 512] if pro else [512, 256])
        if not draw["ultimate"]:
            assert draw["count"] == 49 * 6
            assert draw["seedDraws"] == 144
            assert draw["left"] == pytest.approx([0, 0])
            assert draw["right"] == pytest.approx([0.625, 0.9375])
            continue
        width = draw["screenWidth"]
        n = 8 if width == 320 else 20
        assert draw["count"] == 6 * n * n
        assert (draw["xCount"], draw["yCount"]) == (n + 1, n + 1)
        assert draw["seedDraws"] == 5 * (n - 1) ** 2
        us, vs = (1.0, 1.0) if pro else (0.625, 0.9375)
        u, v = android_centers[width]
        assert draw["center"] == pytest.approx([u * us, v * vs], abs=2e-5)
        # Zoom eases from the course's near-zero starting zoom toward 0.05.
        left, top = draw["left"]
        assert left / us == pytest.approx(0.015, abs=0.001)
        assert top / vs == pytest.approx(left / us, abs=1e-6)
        assert draw["right"] == pytest.approx([us - left, vs - top], abs=1e-6)
