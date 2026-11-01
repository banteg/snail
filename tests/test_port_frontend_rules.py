"""Front-end rules: Ultimate plays Android's, Original the PC's (tests/port_frontend_rules.mjs)."""

import json
import shutil
import struct
import subprocess

import pytest

from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
ASSETS = REPO_ROOT / "artifacts/bin"

pytestmark = pytest.mark.skipif(
    shutil.which("node") is None
    or not WASM.exists()
    or not all((ASSETS / name).exists() for name in ("SnailMail.dat", "SnailMailExtras.dat")),
    reason="needs browser WASM, node, and game archives",
)

CHALLENGE_SETUP = 11
NAME_ENTRY = 21


def config_name(ultimate):
    return "SnailMailMobile.cfg" if ultimate else "SnailMail.cfg"


@pytest.fixture
def play(tmp_path, port_layout_env):
    """Run a scenario on a fresh save: the tutorial done, so every New Game mode is open."""

    def run(scenario, ultimate, arg="", *, name="Probe", routes=(1, 1), bank=0, pro=None, fullscreen=False):
        for archive in ("SnailMail.dat", "SnailMailExtras.dat"):
            shutil.copyfile(ASSETS / archive, tmp_path / archive)
        config = bytearray(196)
        struct.pack_into("<ff", config, 0, 1.0, 1.0)
        config[0x08] = fullscreen
        config[0x60 : 0x60 + len(name)] = name.encode()
        struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
        struct.pack_into("<iii", config, 0xA0, *routes, bank)
        config[0xC0] = 1
        (tmp_path / config_name(ultimate)).write_bytes(config)
        if pro:
            (tmp_path / "SnailMailPro.cfg").write_bytes(struct.pack("<ii", *pro))
        result = subprocess.run(
            ["node", str(REPO_ROOT / "tests/port_frontend_rules.mjs"), str(WASM), scenario, str(int(ultimate)), name, arg],
            cwd=tmp_path, env=port_layout_env, capture_output=True, text=True, check=True, timeout=90,
        )  # fmt: skip
        return json.loads(result.stdout.splitlines()[-1])

    return run


def saved_config(path, ultimate):
    """(highest route, selected route, High Scores bank) as the game saved them."""
    return struct.unpack_from("<iii", (path / config_name(ultimate)).read_bytes(), 0xA0)


def scramble_scores(data):
    return bytes(value ^ (index & 255) for index, value in enumerate(data))


def test_autosave_preserves_pro_route_controls(play):
    assert play("save-pro-map", True)["prompt"] == "Click to Start"


@pytest.mark.parametrize("ultimate", [False, True])
def test_idling_at_start_keeps_saved_replay_within_capacity(play, tmp_path, ultimate):
    result = play("idle-start", ultimate)
    if ultimate:
        assert result["waiting"] <= 9
    table = tmp_path / ("ScoreMobileA-v3.dat" if ultimate else "ScoreA.dat")
    record = scramble_scores(table.read_bytes())
    size, score = struct.unpack_from("<ii", record)
    samples = struct.unpack_from("<i", record, 0x74)[0]
    assert score > 0
    assert 0 < samples < 1000  # the actual run to the first parcel
    assert size == len(record) == 0x88 + samples * 5


def test_score_loader_bounds_records_and_recovers_legacy_samples(play, tmp_path):
    def row(index, samples, *, bank=0):
        record = bytearray(0x88 + samples * 5)
        score = 100 + index
        struct.pack_into("<ii", record, 0, len(record), score)
        struct.pack_into("<I", record, 0x28, (score * score) ^ 0xDEADBABE)
        struct.pack_into("<ii", record, 0x3C, bank, index)
        struct.pack_into("<i", record, 0x74, samples)
        return record

    capacity = 21600
    samples = capacity + 2500
    legacy = row(1, samples)
    planes = (b"\x23\x45" * samples, b"\x56\x78" * samples, b"\x08" * samples)
    legacy[0x88:] = b"".join(planes)
    bad_count = row(2, 1)
    struct.pack_into("<i", bad_count, 0x74, 2)
    bad_name = row(3, 1)
    bad_name[0x5C:0x70] = b"X" * 20
    bad_checksum = row(1, 1)
    struct.pack_into("<I", bad_checksum, 0x28, 0)
    table = tmp_path / "ScoreMobileA-v3.dat"
    # Skip invalid frames with known boundaries, then stop at an invalid
    # byte_count. The two valid neighbors must survive the next save.
    table.write_bytes(scramble_scores(
        row(-1, 0) + row(11, 0) + legacy + bad_count + bad_name + bad_checksum
        + row(4, 0, bank=1) + row(5, 1) + bytes(0x88)
    ))
    result = play("load-scores", True)
    assert result["postal"] == [None, 101, None, None, None, 105, *[None] * 5]
    assert result["challenge"] == [None] * 11
    restored = scramble_scores(table.read_bytes())
    assert struct.unpack_from("<i", restored, 0x74)[0] == capacity
    assert restored[0x88 : 0x88 + 5 * capacity] == b"".join(
        plane[: capacity * width] for plane, width in zip(planes, (2, 2, 1), strict=True)
    )


@pytest.mark.parametrize("ultimate", [False, True])
def test_click_to_start_recenters_steering(play, ultimate):
    assert play("recenter", ultimate) == 0


@pytest.mark.parametrize("enabled", [False, True])
def test_startup_applies_saved_fullscreen(play, enabled):
    assert play("fullscreen", False, fullscreen=enabled) == [int(enabled)]


@pytest.mark.parametrize("ultimate", [False, True])
def test_typed_cheats_work_only_in_the_original(play, ultimate):
    # Android's cRCheat::AI matches no words: after NEWTON (and AUTUMN), an
    # ended postal run still enters the table.
    assert (play("cheats", ultimate)["state"] == NAME_ENTRY) == ultimate


@pytest.mark.parametrize("ultimate", [False, True])
def test_ending_a_challenge_run_records_nothing_in_ultimate(play, ultimate):
    result = play("quit", ultimate, "Challenge Mode")
    if ultimate:
        assert result["state"] == CHALLENGE_SETUP
        assert result["survival"] == [None] * 11
    else:
        assert result["state"] == NAME_ENTRY
        assert result["survival"][0] == 4321


@pytest.mark.parametrize(
    "ultimate,galaxy", [(False, "Postal Mode"), (True, "Postal Mode"), (True, "Pro-Challenge")]
)
def test_cancelling_a_name_restores_the_table(play, tmp_path, ultimate, galaxy):
    result = play("cancel", ultimate, galaxy)
    assert result["state"] == NAME_ENTRY
    table = [30000, 20000, 10000, *[None] * 8]
    challenge = [9000 - 100 * row for row in range(10)] + [None]
    # The PC MiniDelete shifts Challenge rows into the cancelled table.
    assert result["postal"] == (table if ultimate else [30000, *challenge[2:], None])
    # A Pro name is entered on Android's bank 3, which High Scores reopens on.
    assert saved_config(tmp_path, ultimate)[2] == (3 if galaxy == "Pro-Challenge" else 0)


@pytest.mark.parametrize(
    "ultimate,galaxy,name",
    [
        (False, "Postal Mode", "Fluctuosa"),
        (True, "Postal Mode", "Fluctuosa"),
        (True, "Pro-Challenge", "fluctuosa"),
        (True, "Postal Mode", "Probe"),
    ],
)
def test_fluctuosa_opens_every_route_in_ultimate(play, tmp_path, ultimate, galaxy, name):
    play("galaxy", ultimate, galaxy, name=name, routes=(3, 2), pro=(2, 2))
    opened = ultimate and name.casefold() == "fluctuosa"
    assert saved_config(tmp_path, ultimate)[:2] == ((50, 2) if opened else (3, 2))
    pro = struct.unpack("<ii", (tmp_path / "SnailMailPro.cfg").read_bytes())
    assert pro == ((10, 2) if opened else (2, 2))


@pytest.mark.parametrize(
    "ultimate,bank,titles,saved",
    [
        (False, 0, ["Postal", "Challenge", "Postal", "Postal"], 0),
        (True, 0, ["Postal", "Challenge", "Pro", "Pro"], 3),
        (True, 3, ["Pro", "Postal", "Challenge", "Challenge"], 1),
    ],
)
def test_high_scores_remember_the_pro_table(play, tmp_path, ultimate, bank, titles, saved):
    # Opened, toggled twice, left and reopened.
    result = play("scores", ultimate, bank=bank)
    assert result["titles"] == [f"{title} High Scores" for title in titles]
    assert saved_config(tmp_path, ultimate)[2] == saved
    # Android fades out before a Challenge replay starts.
    assert result["replays"] == [ultimate] * 3


@pytest.mark.parametrize("ultimate,best", [(False, 0.0), (True, 0.0), (True, 0.1)])
def test_time_trial_finish_panel(play, ultimate, best):
    result = play("time-trial", ultimate, str(best))
    panel = {"NEW FASTEST TIME!", "Click to Continue"} & set(result["shown"])
    if not ultimate:
        assert panel == set()
    else:
        assert panel == ({"NEW FASTEST TIME!", "Click to Continue"} if best == 0.0 else {"Click to Continue"})
    assert not any(text.startswith("Delivery") or "Delivered" in text for text in result["shown"])
    # The record keeps the faster time; the panel adds no bonus left over from
    # an earlier finish to its score.
    if best:
        assert result["seconds"] == pytest.approx(best)
    else:
        assert result["seconds"] > 0
    assert result["score"] == 0
