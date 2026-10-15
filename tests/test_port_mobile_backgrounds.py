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
def test_mobile_skies_use_whole_image_and_flip_correctly(tmp_path):
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
        capture_output=True,
        text=True,
        check=True,
    )
    draws = json.loads(result.stdout.splitlines()[-1])
    assert len(draws) == 6
    for draw in draws:
        assert draw["count"] == 49 * 6
        if draw["ultimate"] and draw["name"] in ("SpacePro", "SpacePro2"):
            assert [draw[k] for k in ("minU", "maxU", "minV", "maxV")] == pytest.approx(
                [0, 1, 0, 1]
            )
            assert [draw["leftU"], draw["rightU"]] == pytest.approx(
                [1, 0] if draw["flip"] else [0, 1]
            )
        else:
            # Controls retain the original PC padded-image UV contract.
            assert [draw[k] for k in ("minU", "maxU", "minV", "maxV")] == pytest.approx(
                [0, 0.625, 0, 0.9375]
            )
