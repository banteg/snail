"""Run the browser reactor to check mobile rules, dependencies, and save isolation."""

import json
import math
import shutil
import struct
import subprocess

import pytest

from snail.archive import parse_archive_index, read_archive_entry, write_archive
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
def test_mobile_catalog_rules_swing_and_classic_save_isolation(tmp_path):
    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        shutil.copyfile(ASSETS / name, tmp_path / name)
    # Put an authored moving ring on a safe platform so input automation
    # exercises its motion without needing to solve the Pro course.
    archive = tmp_path / "SnailMailExtras.dat"
    index = parse_archive_index(archive)
    files = {
        entry.path.upper(): read_archive_entry(archive, entry)
        for entry in index.entries
    }
    platform = "ID:0\r\nName:'ProbePlatform'\r\nData:\r\n@@@@@@@@@@\r\n"
    platform += "".join(
        ("@___R____@ Ring=Normal RingSpeed=0.5" if i == 30 else "@________@") + "\r\n"
        for i in range(100)
    )
    files["SEGMENTS/PARCELTEST.TXT"] = (platform + "@@@@@@@@@@\r\n").encode()
    write_archive(archive, files)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    config[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", config, 0xA0, 50, 7)
    config[0xC0] = 1
    (tmp_path / "SnailMail.cfg").write_bytes(config)
    score = (
        REPO_ROOT / "tests/fixtures/replays/ScoreA.windows-2026-04-17.dat"
    ).read_bytes()
    (tmp_path / "ScoreA.dat").write_bytes(score)
    result = subprocess.run(
        ["node", str(REPO_ROOT / "tests/port_mobile_rates.mjs"), str(WASM)],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    data = json.loads(result.stdout.splitlines()[-1])
    assert data["catalogCount"] == 176
    assert data["segments"] == {"CAGE2.TXT": 84, "FINISH.TXT": 160, "TWISTER2.TXT": 87}
    for sample in data["rates"]:
        mode = sample["mode"]
        fraction = min(1, max(0, sample["z"] / sample["end"]))
        # Coefficients from Android CalcRate, with PC values as switch controls.
        if sample["ultimate"]:
            slope = 0.3 if mode in (1, 3) else 0.2
            base_bonus = 0.0
            power = 0.3 if mode in (1, 4) else 0.4
        else:
            slope = 0.55 if mode in (1, 3) else 0.4 if mode == 4 else 0.2
            base_bonus = 0.2 if mode == 4 else 0.0
            power = 0.4 if mode in (1, 4) else 0.6
        expected = 1 + fraction * slope + base_bonus
        assert sample["boost"] == 2
        fill = sample["display"]
        if not 0.25 <= fill <= 0.75:
            power *= (1 - math.sin(fill * 4 * math.pi + math.pi / 2)) / 2
        expected += power
        if sample["hoverState"] == 1:
            expected += sample["intensity"] * 0.5
        assert sample["rate"] == pytest.approx(expected, abs=2e-4), sample
    assert len(data["swing"]) >= 5
    assert max(data["swing"]) - min(data["swing"]) > 1
    assert all(abs(x) <= 3 for x in data["swing"])
    assert (tmp_path / "SnailMail.cfg").read_bytes() == config
    assert (tmp_path / "ScoreA.dat").read_bytes() == score
    assert struct.unpack_from(
        "<ii", (tmp_path / "SnailMailMobile.cfg").read_bytes(), 0xA0
    ) == (1, 1)
    assert (tmp_path / "ScoreMobileA.dat").read_bytes() != score


@pytest.mark.skipif(
    shutil.which("node") is None
    or not (REPO_ROOT / "port/zig-out/bin/snail.wasm").exists()
    or not all(
        (ASSETS / name).exists() for name in ("SnailMail.dat", "SnailMailExtras.dat")
    ),
    reason="needs headless WASM, node, and game archives",
)
@pytest.mark.parametrize("level", range(1, 11))
def test_each_complete_mobile_pro_course_starts(tmp_path, level):
    import re

    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        (tmp_path / name).symlink_to(ASSETS / name)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    config[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", config, 0xA0, 1, 1)
    config[0xC0] = 1
    (tmp_path / "SnailMailMobile.cfg").write_bytes(config)
    (tmp_path / "SnailMailPro.cfg").write_bytes(struct.pack("<ii", 10, level))
    keys = tmp_path / "start.keys"
    menu = (
        "600 escape\n700 mouse 345 112\n720 click 3\n800 mouse 345 383\n820 click 3\n"
    )
    keys.write_text(menu)
    args = [
        "node",
        str(REPO_ROOT / "port/shell/run.mjs"),
        str(REPO_ROOT / "port/zig-out/bin/snail.wasm"),
        "--profile", "ultimate",
        "--trace",
        "--keys",
        str(keys),
    ]
    preview = subprocess.run(
        [*args, "--ticks", "900"],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    button = re.findall(
        r'widget \d+ at \(([-\d]+), ([-\d]+)\) size ([-\d]+) x ([-\d]+).*"Deliver!"',
        preview.stderr,
    )
    assert button, preview.stderr
    x, y, width, height = map(int, button[-1])
    keys.write_text(
        menu + f"920 mouse {x + width // 2} {y + height // 2}\n940 click 3\n"
    )
    result = subprocess.run(
        [*args, "--ticks", "1050"],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=True,
    )
    archive = ASSETS / "SnailMailExtras.dat"
    entry = parse_archive_index(archive).entry_by_path(
        f"LEVELS/ARCADEPRO{level:03}.TXT"
    )
    name = re.search(rb"Name:'([^']+)'", read_archive_entry(archive, entry))[1].decode()
    assert f'level "{name}"' in result.stderr
    for error in ("too long", "Cannot find segment", "Unknown path"):
        assert error not in result.stderr
