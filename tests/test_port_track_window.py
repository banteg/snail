"""Ultimate's slug pool and active track window follow Android; Original keeps the PC's."""

import json
import re
import shutil
import struct
import subprocess

import pytest

from snail.archive import parse_archive_index, read_archive_entry, write_archive
from snail.symbols import REPO_ROOT

ASSETS = REPO_ROOT / "artifacts/bin"
ARCHIVES = ("SnailMail.dat", "SnailMailExtras.dat")
HEADLESS = REPO_ROOT / "port/zig-out/bin/snail.wasm"
REACTOR = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
# The PC Start.txt rows; slugs spawn only after them.
START_ROWS = 31


def live_slugs(trace):
    """The most slugs alive at once."""
    return max(map(int, re.findall(r"tick \d+: slugs (\d+)", trace)), default=0)


@pytest.mark.skipif(
    shutil.which("node") is None or not HEADLESS.exists() or not all((ASSETS / name).exists() for name in ARCHIVES),
    reason="needs node, snail.wasm and both game archives",
)
@pytest.mark.parametrize(
    ("rows", "ultimate", "original"),
    [
        # Mobile formations need more than the PC's eight slug slots (Barrage, SlugLine).
        (["@MMMMMMMM@"] * 2, 16, 8),
        # From z = 4 the scan reaches row 43 on Android and row 41 on the PC; slugs on rows 41 and 43.
        (["@________@"] * (41 - START_ROWS) + ["@___M____@", "@________@", "@___M____@"], 2, 1),
    ],
    ids=["pool", "look-ahead"],
)
def test_slugs_alive_before_the_start(probe_course, rows, ultimate, original):
    assert live_slugs(probe_course(rows, ultimate=True)) == ultimate
    assert live_slugs(probe_course(rows, ultimate=False)) == original


@pytest.mark.skipif(
    shutil.which("node") is None or not REACTOR.exists() or not all((ASSETS / name).exists() for name in ARCHIVES),
    reason="needs node, snail-web.wasm and both game archives",
)
def test_track_window_ahead_and_past_the_finish(tmp_path, port_layout_env):
    for name in ARCHIVES:
        shutil.copyfile(ASSETS / name, tmp_path / name)
    # A plain first segment, so the snail runs without meeting anything.
    archive = tmp_path / "SnailMailExtras.dat"
    files = {entry.path.upper(): read_archive_entry(archive, entry) for entry in parse_archive_index(archive).entries}
    files["SEGMENTS/PARCELTEST.TXT"] = (
        "ID:0\r\nName:'ProbePlatform'\r\nData:\r\n@@@@@@@@@@\r\n" + "@________@\r\n" * 200 + "@@@@@@@@@@\r\n"
    ).encode()
    write_archive(archive, files)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    config[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", config, 0xA0, 1, 1)
    config[0xC0] = 1
    (tmp_path / "SnailMailMobile.cfg").write_bytes(config)
    result = subprocess.run(
        ["node", str(REPO_ROOT / "tests/port_track_window.mjs"), str(REACTOR)],
        cwd=tmp_path, env=port_layout_env, capture_output=True, text=True, check=True,
    )  # fmt: skip
    for sample in json.loads(result.stdout.splitlines()[-1]):
        ultimate = sample["ultimate"]
        running = sample["running"]
        # Rows are scanned up to the trailing edge (the snail's z - 8) plus 48, on the PC plus 46.
        assert running["window"] == pytest.approx(running["z"] - 8)
        assert running["scanEnd"] == int(running["window"]) + (48 if ultimate else 46)
        # The finish banner shows from 48 rows ahead, on the PC from 46.
        assert sample["banner"] == bool(ultimate)
        # Past the finish line the trailing edge keeps following the snail until 30 rows on,
        # and the scan stops 40 rows on; the PC holds the edge 30 rows before the line and
        # stops the scan 20 rows on.
        finished = sample["finished"]
        finish = finished["finish"]
        if ultimate:
            assert finished["window"] == pytest.approx(finished["z"] - 8)
            assert finished["scanEnd"] == finish + 40
        else:
            assert finished["window"] == finish - 30
            assert finished["scanEnd"] == finish + 20
