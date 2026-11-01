"""Exercise Challenge digit heights and the Postal allocator through course construction."""

import json
import re
import shutil
import struct
import subprocess

import pytest

from snail.archive import parse_archive_index, read_archive_entry, write_archive
from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
ASSETS = REPO_ROOT / "artifacts/bin"
ARCHIVES = ("SnailMail.dat", "SnailMailExtras.dat")
pytestmark = pytest.mark.skipif(
    not shutil.which("node")
    or not WASM.is_file()
    or not all((ASSETS / name).is_file() for name in ARCHIVES),
    reason="needs the browser WASM and game archives",
)


@pytest.fixture(scope="module")
def postal_archives(tmp_path_factory):
    directory = tmp_path_factory.mktemp("parcel-courses")
    for archive in ARCHIVES:
        source = ASSETS / archive
        files = {
            entry.path.upper(): read_archive_entry(source, entry)
            for entry in parse_archive_index(source).entries
        }
        template = files["LEVELS/ARCADE001.TXT"]
        for route, (target, quota, markers) in enumerate(
            [
                (6, 3, ["0", "1", "1", "1", "2", "2", "2"]),
                (12, 6, ["00", "1", "1", "1", "2", "2", "2"]),
                (2, 1, ["0", "0", "0"]),
            ],
            start=1,
        ):
            # Either three-parcel group excludes the other on this segment. "00" declares
            # two singles on one row, where the runtime can issue only one spawn.
            name = f"ParcelProbe{route}.txt"
            rows = ["@________@"] * 40
            for marker in markers:
                rows += [f"@___{marker.ljust(5, '_')}@"] + ["@________@"] * 3
            segment = [
                "ID:0",
                "Name:'Probe'",
                "Data:",
                "@@@@@@@@@@",
                *rows,
                "@@@@@@@@@@",
                "",
            ]
            files[f"SEGMENTS/{name.upper()}"] = "\r\n".join(segment).encode()
            level = re.sub(rb"Parcels:\d+", f"Parcels:{target}".encode(), template)
            level = re.sub(rb"Quota:\d+", f"Quota:{quota}".encode(), level)
            files[f"LEVELS/ARCADE{route:03d}.TXT"] = re.sub(
                rb"(Segments Begin:[^\r\n]*\r?\n).*?(Segments End:)",
                rb"\g<1>" + name.encode() + b"\r\n" + rb"\g<2>",
                level,
                flags=re.DOTALL,
            )
        write_archive(directory / archive, files)
    return directory


def play(directory, port_layout_env, profile, scenario, source, route=1):
    for name in ARCHIVES:
        if not (directory / name).exists():
            shutil.copyfile(source / name, directory / name)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1, 1)
    struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", config, 0xA0, route, route)
    config[0x60:0x65] = b"Probe"
    config[0xC0] = 1
    (
        directory
        / ("SnailMailMobile.cfg" if profile == "ultimate" else "SnailMail.cfg")
    ).write_bytes(config)
    result = subprocess.run(
        [
            "node",
            REPO_ROOT / "tests/port_parcel_placement.mjs",
            WASM,
            profile,
            scenario,
        ],
        cwd=directory,
        env=port_layout_env,
        capture_output=True,
        text=True,
        check=True,
    )
    return json.loads(result.stdout.splitlines()[-1])


@pytest.mark.parametrize("profile", ["original", "ultimate"])
def test_challenge_parcels_use_this_courses_height(tmp_path, port_layout_env, profile):
    fresh = play(tmp_path, port_layout_env, profile, "fresh", ASSETS)["parcels"]
    stale = play(tmp_path, port_layout_env, profile, "stale", ASSETS)["parcels"]
    assert fresh and [(p["row"], p["x"], p["z"]) for p in stale] == [
        (p["row"], p["x"], p["z"]) for p in fresh
    ]
    assert {p["road"] for p in fresh + stale} == {0}
    assert {p["y"] for p in fresh} == {1}
    assert {p["y"] for p in stale} == ({-2} if profile == "original" else {1})


@pytest.mark.parametrize("profile", ["original", "ultimate"])
@pytest.mark.parametrize(
    "route,original,ultimate",
    [
        (1, (4, 8, 4), (6, 3, 6)),  # fill from unused authored rows
        (2, (5, 10, 4), (7, 3, 7)),  # impossible total and a duplicate row
        (3, (2, 1, 2), (2, 1, 2)),  # sufficient singles already
    ],
)
def test_postal_total_quota_and_usable_spawn_rows(
    tmp_path, port_layout_env, postal_archives, profile, route, original, ultimate
):
    course = play(tmp_path, port_layout_env, profile, "postal", postal_archives, route)
    parcels = course["parcels"]
    assert (course["count"], course["quota"], len(parcels)) == (
        original if profile == "original" else ultimate
    )
    assert all(p["z"] == p["row"] + 0.5 and p["y"] == p["road"] + 1 for p in parcels)
    assert {abs(p["x"]) for p in parcels} == {0.5}


@pytest.mark.parametrize(
    "profile,seed,count,quota",
    [("original", 32523, 39, 78), ("ultimate", 17673, 40, 20)],
)
def test_stock_loopsville_short_pattern(
    tmp_path, port_layout_env, profile, seed, count, quota
):
    # Windows and Android RNG differ. Both of these stock builds originally placed 39 of 40.
    course = play(tmp_path, port_layout_env, profile, "loopsville", ASSETS, route=13)
    assert (course["seed"], course["count"], course["quota"]) == (seed, count, quota)
    assert len(course["parcels"]) == count
