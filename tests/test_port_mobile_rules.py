"""Drive a probe course in both profiles: Ultimate plays Android's rules, Original the PC's."""

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


def write_probe_course(directory):
    """Pro 1 rebuilt as a flat course: two hearts, sixteen rings beside the snail's line, two
    segment messages and no parcels, so the finish pays the 50,000 perfect-delivery bonus."""
    shutil.copyfile(ASSETS / "SnailMail.dat", directory / "SnailMail.dat")
    archive = ASSETS / "SnailMailExtras.dat"
    files = {entry.path.upper(): read_archive_entry(archive, entry) for entry in parse_archive_index(archive).entries}

    def segment(name, rows):
        return (f"ID:0\r\nName:'{name}'\r\nData:\r\n@@@@@@@@@@\r\n" + "".join(f"{row}\r\n" for row in rows) + "@@@@@@@@@@\r\n").encode()

    # The rings start beyond the spawn window the harness takes over in: the course
    # has two ring slots.
    rows = ["@________@"] * 40 + ["@___$$___@"] + ["@________@"] * 3
    for _ in range(16):
        rows += ["@R______R@ Ring=Normal"] + ["@________@"] * 3
    files["SEGMENTS/PROBERINGS.TXT"] = segment("ProbeRings", rows)
    files["SEGMENTS/PROBEMESSAGE.TXT"] = segment("ProbeMessage", ["@________@"] * 40)
    level = files["LEVELS/ARCADEPRO001.TXT"].decode("latin-1")
    for key, value in (("Parcels", 0), ("Garbage", 0), ("Salt", 0), ("Speed", 15)):
        level = re.sub(rf"{key}:\d+", f"{key}:{value}", level)
    messages = "".join(f'ProbeMessage.txt Duration=20.0 Message="Probe {n}"\r\n' for n in ("one", "two"))
    level = re.sub(
        r"(Segments Begin:[^\r\n]*\r?\n).*?(Segments End:)",
        lambda match: match[1] + "ProbeRings.txt\r\n" + messages + match[2],
        level,
        flags=re.DOTALL,
    )
    files["LEVELS/ARCADEPRO001.TXT"] = level.encode("latin-1")
    write_archive(directory / "SnailMailExtras.dat", files)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    config[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", config, 0xA0, 50, 7)
    config[0xC0] = 1
    (directory / "SnailMail.cfg").write_bytes(config)
    (directory / "SnailMailMobile.cfg").write_bytes(config)


def play(directory, port_layout_env, ultimate, tally):
    result = subprocess.run(
        ["node", str(REPO_ROOT / "tests/port_mobile_rules.mjs"), str(WASM), str(int(ultimate)), tally],
        cwd=directory,
        env=port_layout_env,
        capture_output=True,
        text=True,
        check=True,
    )
    return json.loads(result.stdout.splitlines()[-1])


@pytest.mark.skipif(
    shutil.which("node") is None
    or not WASM.exists()
    or not all((ASSETS / name).exists() for name in ("SnailMail.dat", "SnailMailExtras.dat")),
    reason="needs browser WASM, node, and game archives",
)
@pytest.mark.parametrize("tally", ["watch", "skip"])
def test_probe_course_plays_android_rules_only_in_ultimate(tmp_path, port_layout_env, tally):
    runs = {}
    for ultimate in (True, False):
        directory = tmp_path / ("ultimate" if ultimate else "original")
        directory.mkdir()
        write_probe_course(directory)
        # The reactor opens Pro 1 in Ultimate; the harness then picks the profile.
        runs[ultimate] = play(directory, port_layout_env, ultimate, tally)
    ultimate, original = runs[True], runs[False]

    # Android scores a health pickup 250 (cRSubGoldy::Collision); the snail takes both
    # hearts. The port files the points under the bonus kind.
    assert ultimate["before"]["buckets"][5] == 2 * 250
    assert original["before"]["buckets"][5] == 0
    assert ultimate["before"]["buckets"][:5] == original["before"]["buckets"][:5]

    # Android stops counting rings at 8, Windows at 10.
    assert ultimate["rings"] == original["rings"] >= 10
    assert ultimate["before"]["ringCounter"] == 8
    assert original["before"]["ringCounter"] == 10

    # Android looks up a segment's message 10 rows ahead and clears the tip still
    # showing (20 s) before the next one.
    assert len(ultimate["messages"]) == len(original["messages"]) == 2
    for early, late in zip(ultimate["messages"], original["messages"], strict=True):
        assert late["z"] - early["z"] == pytest.approx(10, abs=0.5)
    assert ultimate["messages"][1]["tips"] == 1
    assert original["messages"][1]["tips"] == 2

    if tally == "watch":
        # Android holds the replay cursor and sample count while the summary waits.
        for name in ("cursor", "samples"):
            assert ultimate["held"][name] == ultimate["summary"][name]
            assert original["held"][name] == original["summary"][name] + 120
        owed = 50000
    else:
        assert ultimate["skipped"]["buckets"][4] == original["skipped"]["buckets"][4] < 300
        owed = 300 + 50000
    # Both pay what the tally owes; only Android's UnInit pays the bonus through
    # ScoreAdd, so only Ultimate awards the 50,000-point extra life.
    for run in (ultimate, original):
        assert run["after"]["score"] == run["before"]["score"] + owed
    assert ultimate["after"]["lives"] == ultimate["before"]["lives"] + 1
    assert original["after"]["lives"] == original["before"]["lives"]
