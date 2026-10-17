"""Run the browser reactor to check the sounds Android plays differently from the PC."""

import hashlib
import json
import shutil
import struct
import subprocess

import pytest

from snail.archive import parse_archive_index, read_archive_entry, write_archive
from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
ASSETS = REPO_ROOT / "artifacts/bin"
# Pro 1 opens with ParcelTest after Start. Level ground for the warning and
# invincibility, then a raised ramp ('>' twice), a plain ramp and a SuperTramp.
PROBE_COURSE = (
    ["@........@"] * 150
    + ["@>>>>>>>>@"] * 2
    + ["@........@"] * 12
    + ["@<<<<<<<<@"]
    + ["@........@"] * 12
    + ["@pppPPppp@  Path=SuperTramp"]
    + ["@        @"] * 20
    + ["@........@"] * 60
)


@pytest.mark.skipif(
    shutil.which("node") is None
    or not WASM.exists()
    or not all(
        (ASSETS / name).exists() for name in ("SnailMail.dat", "SnailMailExtras.dat")
    ),
    reason="needs browser WASM, node, and game archives",
)
def test_warning_invincibility_and_ramp_sounds_follow_the_profile(tmp_path, port_layout_env):
    shutil.copyfile(ASSETS / "SnailMail.dat", tmp_path / "SnailMail.dat")
    extras = ASSETS / "SnailMailExtras.dat"
    files = {
        entry.path.upper(): read_archive_entry(extras, entry)
        for entry in parse_archive_index(extras).entries
    }
    rows = ["@@@@@@@@@@", *PROBE_COURSE, "@@@@@@@@@@"]
    files["SEGMENTS/PARCELTEST.TXT"] = ("ID:0\r\nName:'Probe'\r\nData:\r\n" + "\r\n".join(rows) + "\r\n").encode()
    write_archive(tmp_path / "SnailMailExtras.dat", files)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    config[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", config, 0xA0, 50, 7)
    config[0xC0] = 1
    (tmp_path / "SnailMailMobile.cfg").write_bytes(config)
    pc = ASSETS / "SnailMail.dat"
    pc_index = parse_archive_index(pc)
    samples = {
        "postalloop": read_archive_entry(pc, pc_index.entry_by_path("SFX2/POSTALLOOP.OGG")),
        "invincible": read_archive_entry(pc, pc_index.entry_by_path("SFX2/INVINCIBLE.OGG")),
        "upramp": files["SFX2/UPRAMP.OGG"],
    }
    named = {hashlib.md5(data).hexdigest(): name for name, data in samples.items()}
    result = subprocess.run(
        ["node", str(REPO_ROOT / "tests/port_mobile_sounds.mjs"), str(WASM), json.dumps(named)],
        cwd=tmp_path,
        env=port_layout_env,
        capture_output=True,
        text=True,
        check=True,
    )
    data = json.loads(result.stdout.splitlines()[-1])

    def plays(events, name, loop=0):
        return [event for event in events if event.get("play") == name and event["loop"] == loop]

    def ticks(events):
        return [event["tick"] for event in events]

    def launches(events):
        return [event for event in events if "launch" in event]

    # Started in Original, the port registers the PC sound bank, where
    # postalloop is 50, and the voices, and nothing else. Ultimate adds upramp
    # right after the bank and keeps every other sample in its order.
    registered = data["registered"]
    assert "upramp" not in registered["original"]
    assert registered["original"].index("postalloop") == 50
    assert registered["ultimate"].pop(51) == "upramp"
    assert registered["ultimate"] == registered["original"]

    # Pro 1 needs Ultimate's menus, so each play-through starts in Ultimate and
    # then sets the profile it checks. The harness fills the damage gauge
    # before tick 0 and empties it before tick 170; the warning shows from
    # tick 1.
    original, ultimate = data["original"], data["ultimate"]
    # Windows restarts postalloop at every 26-tick blink and cuts it off when
    # the warning stops (StopSample plays it looped, then stops the sample).
    assert ticks(plays(original, "postalloop")) == list(range(1, 170, 26))
    assert ticks(plays(original, "postalloop", loop=1)) == [170]
    assert ticks(event for event in original if event.get("stop") == "postalloop") == [170]
    # Android plays it every 72 ticks and lets the last one finish.
    assert ticks(plays(ultimate, "postalloop")) == list(range(1, 170, 72))
    assert not plays(ultimate, "postalloop", loop=1)
    assert not [event for event in ultimate if "stop" in event]

    # Tier 7 from tick 200 makes the snail invincible: Android starts it silently.
    assert ticks(plays(original, "invincible")) == [200]
    assert not plays(ultimate, "invincible")

    # The snail goes up the raised ramp, the plain ramp 14 rows on and off the
    # SuperTramp path. Once it lands past the raised ramp, the harness moves it
    # 3 rows back, as a new level or life moves it back to the start, and it
    # goes up the raised ramp again.
    def lifts(events):
        first = int(launches(events)[0]["launch"])
        return ["path" if event["riding"] else int(event["launch"]) - first for event in launches(events)]

    assert lifts(original) == lifts(ultimate) == [0, 0, 14, "path"]
    # Windows has no ramp sound. Android plays upramp each time but the second
    # time up the raised ramp: the snail is not more than 1.0 past the z where
    # upramp last played, and nothing resets that mark when the snail goes back.
    assert not plays(original, "upramp")
    played = ticks(plays(ultimate, "upramp"))
    assert [event["tick"] in played for event in launches(ultimate)] == [True, False, True, True]
    assert len(played) == 3
