"""Run the browser reactor to check mobile rules, dependencies, and save isolation."""

import json
import math
import re
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
def test_mobile_catalog_rules_swing_and_classic_save_isolation(tmp_path, port_layout_env):
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
    (tmp_path / "SnailMailMobile.cfg").write_bytes(config)
    score = (
        REPO_ROOT / "tests/fixtures/replays/ScoreA.windows-2026-04-17.dat"
    ).read_bytes()
    (tmp_path / "ScoreA.dat").write_bytes(score)
    # Tables from before Ultimate's score version: their replays belong to older
    # courses and rules, so Ultimate removes them and starts fresh v2 tables.
    (tmp_path / "ScoreMobileA.dat").write_bytes(score)
    (tmp_path / "ScoreMobileB-v2.dat").write_bytes(score)
    (tmp_path / "ScorePro.dat").write_bytes(score)
    result = subprocess.run(
        ["node", str(REPO_ROOT / "tests/port_mobile_rates.mjs"), str(WASM)],
        cwd=tmp_path,
        env=port_layout_env,
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
    assert not (tmp_path / "ScoreMobileA.dat").exists()
    assert not (tmp_path / "ScoreMobileB-v2.dat").exists()
    assert not (tmp_path / "ScorePro.dat").exists()
    assert (tmp_path / "ScoreMobileA-v3.dat").exists()


@pytest.mark.skipif(
    shutil.which("node") is None
    or not (REPO_ROOT / "port/zig-out/bin/snail.wasm").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMail.dat").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMailExtras.dat").exists(),
    reason="needs node, snail.wasm, SnailMail.dat and SnailMailExtras.dat",
)
def test_first_ultimate_launch_keeps_preferences_but_not_pc_progress(tmp_path):
    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        (tmp_path / name).symlink_to(REPO_ROOT / "artifacts/bin" / name)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 0.25, 0.75)
    struct.pack_into("<I", config, 0x1C, 0x1FE)
    struct.pack_into("<i", config, 0x34, 0)
    struct.pack_into("<ifi", config, 0x40, 90, 0.3, 10)
    config[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<iii", config, 0xA0, 50, 7, 1)
    config[0xC0] = 1
    (tmp_path / "SnailMail.cfg").write_bytes(config)
    subprocess.run(
        ["node", str(REPO_ROOT / "port/shell/run.mjs"), str(REPO_ROOT / "port/zig-out/bin/snail.wasm"),
         "--profile", "ultimate", "--ticks", "5"],
        cwd=tmp_path, capture_output=True, text=True, check=True,
    )  # fmt: skip
    mobile = (tmp_path / "SnailMailMobile.cfg").read_bytes()
    # Volumes and display settings carry over.
    assert struct.unpack_from("<ff", mobile, 0) == (0.25, 0.75)
    assert mobile[0x08] == 0
    assert struct.unpack_from("<I", mobile, 0x1C) == (0x1FE,)
    assert struct.unpack_from("<i", mobile, 0x34) == (0,)
    # Challenge settings, the high-score name and tab, the campaign routes and
    # the tutorial start from the defaults, as on Android.
    assert struct.unpack_from("<ifi", mobile, 0x40) == (40, pytest.approx(0.3), 40)
    assert mobile[0x60] == 0
    assert struct.unpack_from("<iii", mobile, 0xA0) == (1, 1, 0)
    assert mobile[0xC0] == 0
    assert (tmp_path / "SnailMail.cfg").read_bytes() == config


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
        "600 escape\n700 mouse 345 112\n720 click 3\n800 mouse 345 240\n820 click 3\n"
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
    level_text = read_archive_entry(archive, entry)
    name = re.search(rb"Name:'([^']+)'", level_text)[1].decode()
    background = re.search(rb"Background:(\w+)\.txt", level_text)[1].decode()
    # Android's random space backdrop is for Track: r alone; Pro 1-5 are Track: 5.
    assert re.search(
        rf'level "{re.escape(name)}" .* backdrop Backgrounds/{background}\.tga$',
        result.stderr,
        re.MULTILINE,
    ), result.stderr
    for error in ("too long", "Cannot find segment", "Unknown path"):
        assert error not in result.stderr


@pytest.mark.skipif(
    shutil.which("node") is None
    or not WASM.exists()
    or not all(
        (ASSETS / name).exists() for name in ("SnailMail.dat", "SnailMailExtras.dat")
    ),
    reason="needs browser WASM, node, and game archives",
)
def test_pro_state_ends_with_its_game_or_replay(tmp_path, port_layout_env):
    def scramble(data: bytes) -> bytearray:
        return bytearray(b ^ (i & 0xFF) for i, b in enumerate(data))

    def level_name(path: str) -> str:
        archive = ASSETS / "SnailMailExtras.dat"
        entry = parse_archive_index(archive).entry_by_path(path)
        return re.search(rb"Name:'([^']+)'", read_archive_entry(archive, entry))[1].decode()

    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        shutil.copyfile(ASSETS / name, tmp_path / name)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    struct.pack_into("<ii", config, 0xA0, 50, 7)
    config[0xC0] = 1
    (tmp_path / "SnailMailMobile.cfg").write_bytes(config)
    (tmp_path / "SnailMailPro.cfg").write_bytes(struct.pack("<ii", 10, 1))
    # The top postal record and a Pro record named ProChamp both replay level 3.
    scores = scramble(
        (REPO_ROOT / "tests/fixtures/replays/ScoreA.windows-2026-04-17.dat").read_bytes()
    )
    struct.pack_into("<i", scores, 0x2C, 3)
    (tmp_path / "ScoreMobileA-v3.dat").write_bytes(scramble(scores))
    pro = scores[: struct.unpack_from("<I", scores, 0)[0]]
    pro[0x5C : 0x5C + 20] = b"ProChamp".ljust(20, b"\x00")
    (tmp_path / "ScorePro-v3.dat").write_bytes(scramble(pro))
    result = subprocess.run(
        ["node", str(REPO_ROOT / "tests/port_pro_state.mjs"), str(WASM)],
        cwd=tmp_path,
        env=port_layout_env,
        capture_output=True,
        text=True,
        check=True,
    )
    report = json.loads(result.stdout.splitlines()[-1])
    # Leaving Pro, by its credits or Back, puts the postal records back under
    # the Postal title.
    assert report["afterCredits"] == "banteg"
    assert report["proView"] == "ProChamp"
    assert report["afterProReplay"] == "ProChamp"
    assert report["afterBack"] == "banteg"
    assert report["postalView"] == "banteg"
    # A Pro record replays on its Pro course, a postal one on the postal
    # course, and neither moves the Pro galaxy's saved selection.
    assert report["proReplay"] == level_name("LEVELS/ARCADEPRO003.TXT")
    assert report["postalReplay"] == level_name("LEVELS/ARCADE003.TXT")
    assert report["proProgressDuringReplay"] == [10, 1]
    assert report["proProgress"] == [10, 1]


@pytest.mark.skipif(
    shutil.which("node") is None
    or not WASM.exists()
    or not all(
        (ASSETS / name).exists() for name in ("SnailMail.dat", "SnailMailExtras.dat")
    ),
    reason="needs browser WASM, node, and game archives",
)
def test_ultimate_replay_caption_fade_exit_and_summary_cap(tmp_path, port_layout_env):
    def scramble(data: bytes) -> bytearray:
        return bytearray(b ^ (i & 0xFF) for i, b in enumerate(data))

    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        shutil.copyfile(ASSETS / name, tmp_path / name)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    config[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ii", config, 0xA0, 50, 7)
    config[0xC0] = 1
    (tmp_path / "SnailMailMobile.cfg").write_bytes(config)
    (tmp_path / "SnailMailPro.cfg").write_bytes(struct.pack("<ii", 10, 1))
    scores = scramble(
        (REPO_ROOT / "tests/fixtures/replays/ScoreA.windows-2026-04-17.dat").read_bytes()
    )
    struct.pack_into("<ii", scores, 0x4C, 65, 80)
    (tmp_path / "ScoreMobileA-v3.dat").write_bytes(scramble(scores))

    script = f"""
import {{ LAYOUT, openMobileGame }} from {json.dumps(str(REPO_ROOT / "tests/port_mobile_runtime.mjs"))};
const wasm = {json.dumps(str(WASM))};
const {{ e, root, sub, memory, step, click }} = await openMobileGame(wasm);
const fstate = () => memory().readInt32LE(root + LAYOUT.frontend_state);
const fadeState = () => memory().readInt32LE(root + LAYOUT.fade_state);
const text = (addr) => {{
  const m = memory();
  return m.toString("latin1", addr, m.indexOf(0, addr));
}};
const caption = () => text(e.snail_replay_caption());
const alpha = () => e.snail_replay_caption_alpha();
const wait = (done) => {{
  for (let i = 0; i < 120 && !done(); ++i) {{
    e.snail_key(1, 1); e.snail_frame(1 / 60); e.snail_key(1, 0);
    step(1);
  }}
}};

const m0 = memory();
m0.writeInt32LE(2, sub + LAYOUT.subgame_rebuild_selector);
m0.writeInt32LE(29, root + LAYOUT.saved_frontend_state);
m0.writeInt32LE(26, root + LAYOUT.frontend_state);
wait(() => fstate() === 5);
click(345, 180);
for (let i = 0; i < 60 && fstate() !== 19; ++i) step(1);

const launchReplay = (row = 0) => {{
  const m = memory();
  const widget = m.readUInt32LE(root + LAYOUT.high_score + LAYOUT.replay_row_widgets + 4 * row);
  m.writeUInt32LE(m.readUInt32LE(widget + LAYOUT.widget_flags) | LAYOUT.primary_action_triggered, widget + LAYOUT.widget_flags);
  for (let i = 0; i < 300 && !(fstate() === 11 && memory().readInt32LE(sub + LAYOUT.subgame_state) === 2); ++i) {{
    e.snail_frame(1 / 60);
  }}
}};

const tickHold = () => {{
  memory().writeFloatLE(4.0, sub + LAYOUT.sub_player_z);
  memory().writeInt32LE(0, sub + LAYOUT.replay_update_cursor);
  e.snail_frame(1 / 60);
}};
launchReplay(0);
const postalCaptions = [];
const postalAlphas = [];
for (let phase = 0; phase < 5; ++phase) {{
  for (let t = 0; t < 120; ++t) tickHold();
  postalCaptions.push(caption());
  postalAlphas.push(alpha());
  for (let t = 0; t < 120; ++t) tickHold();
}}

// Click during replay: starts fade-out without cutting away on the click tick.
while (fadeState() !== 0) e.snail_frame(1 / 60);
e.snail_button(0, 1);
e.snail_frame(1 / 60);
e.snail_button(0, 0);
const stateOnClickTick = fstate();
const fadeOnClickTick = fadeState();
let ticksToExit = 0;
while (fstate() === 11 && ticksToExit < 200) {{
  e.snail_frame(1 / 60);
  ++ticksToExit;
}}
for (let i = 0; i < 60 && fstate() !== 19; ++i) step(1);
const stateAfterClickExit = fstate();

// Launch again and test Time Trial caption cycle (mode 4) + 2 s summary cap.
launchReplay(0);
memory().writeInt32LE(4, sub + 0x40); // level_mode = 4 (Time Trial)
const ttCaptions = [];
for (let t = 0; t < 600; ++t) {{
  tickHold();
  const c = caption();
  if (c && ttCaptions[ttCaptions.length - 1] !== c) ttCaptions.push(c);
}}

while (fadeState() !== 0) tickHold();
memory().writeInt32LE(4, sub + LAYOUT.completion + LAYOUT.completion_state); // SUMMARY_ACTIVE
for (let t = 0; t < 119; ++t) tickHold();
const fadeAt119 = fadeState();
tickHold();
e.snail_frame(1 / 60);
const fadeAt120 = fadeState();
let summaryExitTicks = 0;
while (fstate() === 11 && summaryExitTicks < 200) {{
  e.snail_frame(1 / 60);
  ++summaryExitTicks;
}}
for (let i = 0; i < 60 && fstate() !== 19; ++i) step(1);
const stateAfterSummaryExit = fstate();

console.log(JSON.stringify({{
  postalCaptions,
  postalAlphas,
  stateOnClickTick,
  fadeOnClickTick,
  ticksToExit,
  stateAfterClickExit,
  ttCaptions,
  fadeAt119,
  fadeAt120,
  summaryExitTicks,
  stateAfterSummaryExit,
}}));
"""
    (tmp_path / "replay_overlay.mjs").write_text(script)
    result = subprocess.run(
        ["node", str(tmp_path / "replay_overlay.mjs")],
        cwd=tmp_path,
        env=port_layout_env,
        capture_output=True,
        text=True,
        check=True,
    )
    report = json.loads(result.stdout.splitlines()[-1])
    assert report["postalCaptions"] == [
        "Replay: Challenge",
        "Player: banteg",
        "Difficulty: 80%",
        "Speed: 65%",
        "Replay: Challenge",
    ]
    assert all(a == pytest.approx(0.8, abs=0.05) for a in report["postalAlphas"])
    assert report["stateOnClickTick"] == 11
    assert report["fadeOnClickTick"] != 0
    assert 10 < report["ticksToExit"] < 100
    assert report["stateAfterClickExit"] == 19
    assert set(report["ttCaptions"]) == {"Replay: Time Trial", "Player: banteg"}
    assert report["fadeAt119"] == 0
    assert report["fadeAt120"] != 0
    assert 10 < report["summaryExitTicks"] < 100
    assert report["stateAfterSummaryExit"] == 19


@pytest.mark.skipif(
    shutil.which("node") is None
    or not WASM.exists()
    or not all(
        (ASSETS / name).exists() for name in ("SnailMail.dat", "SnailMailExtras.dat")
    ),
    reason="needs browser WASM, node, and game archives",
)
def test_window_state_pause_and_freeze_rules(tmp_path, port_layout_env):
    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        shutil.copyfile(ASSETS / name, tmp_path / name)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    config[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ii", config, 0xA0, 50, 7)
    config[0xC0] = 1
    (tmp_path / "SnailMailMobile.cfg").write_bytes(config)

    script = f"""
import {{ LAYOUT, openMobileGame, startGame }} from {json.dumps(str(REPO_ROOT / "tests/port_mobile_runtime.mjs"))};
const wasm = {json.dumps(str(WASM))};

const ultPaused = [];
const ult = await openMobileGame(wasm, {{
  set_paused: (p) => ultPaused.push(p),
}});
const sub = ult.sub;
const state = (m, s = sub) => m.readInt32LE(s + LAYOUT.subgame_state);
const gate = (m, s = sub) => m.readUInt8(s + LAYOUT.subgame_pause_gate);
const playerZ = (m, s = sub) => m.readFloatLE(s + LAYOUT.sub_player_z);

const ultInitialState = state(ult.memory());
ult.e.snail_window_state(1, 0);
ult.e.snail_frame(1 / 60);
const ultBlurState = state(ult.memory());
const ultBlurGate = gate(ult.memory());
const ultBlurAudio = [...ultPaused];

ult.e.snail_window_state(1, 1);
ult.step(2);
ult.click(320, 330);
const ultResumedState = state(ult.memory());
ult.e.snail_frame(1 / 60);
const ultNextTickState = state(ult.memory());

ult.e.snail_window_state(0, 0);
ult.e.snail_frame(1 / 60);
const ultHiddenState = state(ult.memory());
const ultHiddenAudio = [...ultPaused];

const origPaused = [];
const origE = await startGame(wasm, {{
  set_paused: (p) => origPaused.push(p),
}}, 0);
const origStep = (n = 5) => {{ for (let i = 0; i < n; ++i) origE.snail_frame(0.4); }};
const origClick = (x, y) => {{
  origE.snail_pointer(x, y); origE.snail_frame(1 / 60);
  origE.snail_button(0, 1); origE.snail_frame(1 / 60);
  origE.snail_button(0, 0); origStep();
}};
origStep(25);
origE.snail_key(1, 1); origE.snail_frame(1 / 60); origE.snail_key(1, 0); origStep();
origClick(345, 112);
origClick(344, 102);
origStep(10);
origClick(320, 222);
origStep(2);
const origMem = () => Buffer.from(origE.memory.buffer);
let origSub = 0;
const needle = Buffer.from("Tutorial\\0");
for (let p = origMem().indexOf(needle); p >= 0; p = origMem().indexOf(needle, p + 1)) {{
  const candidate = p - LAYOUT.subgame - LAYOUT.level_definition - LAYOUT.level_display_name;
  if (candidate > 0 && origMem().readInt32LE(candidate + LAYOUT.subgame + LAYOUT.subgame_state) === 2) {{
    origSub = candidate + LAYOUT.subgame;
  }}
}}
const origInitialState = state(origMem(), origSub);
const zBeforeFreeze = playerZ(origMem(), origSub);
origE.snail_fullscreen_changed(0);
origE.snail_window_state(1, 0);
for (let i = 0; i < 10; ++i) origE.snail_frame(1 / 60);
const origWindowedBlurState = state(origMem(), origSub);
const origWindowedBlurGate = gate(origMem(), origSub);
const zDuringFreeze = playerZ(origMem(), origSub);
const origWindowedBlurAudio = [...origPaused];

origE.snail_window_state(1, 1);
for (let i = 0; i < 10; ++i) origE.snail_frame(1 / 60);
const zAfterUnfreeze = playerZ(origMem(), origSub);
const origRefocusAudio = [...origPaused];

origE.snail_fullscreen_changed(1);
origE.snail_window_state(1, 0);
origE.snail_frame(1 / 60);
const origFullscreenBlurState = state(origMem(), origSub);
const origFullscreenBlurGate = gate(origMem(), origSub);

console.log(JSON.stringify({{
  ultInitialState,
  ultBlurState,
  ultBlurGate,
  ultBlurAudio,
  ultResumedState,
  ultNextTickState,
  ultHiddenState,
  ultHiddenAudio,
  origInitialState,
  origWindowedBlurState,
  origWindowedBlurGate,
  zBeforeFreeze,
  zDuringFreeze,
  zAfterUnfreeze,
  origWindowedBlurAudio,
  origRefocusAudio,
  origFullscreenBlurState,
  origFullscreenBlurGate,
}}));
"""
    (tmp_path / "window_state.mjs").write_text(script)
    result = subprocess.run(
        ["node", str(tmp_path / "window_state.mjs")],
        cwd=tmp_path,
        env=port_layout_env,
        capture_output=True,
        text=True,
        check=True,
    )
    report = json.loads(result.stdout.splitlines()[-1])
    assert report["ultInitialState"] == 2
    assert report["ultBlurState"] == 3
    assert report["ultBlurGate"] == 1
    assert report["ultBlurAudio"] == []
    assert report["ultResumedState"] == 2
    assert report["ultNextTickState"] == 2
    assert report["ultHiddenState"] == 3
    assert report["ultHiddenAudio"] == [1]
    assert report["origInitialState"] == 2
    assert report["origWindowedBlurState"] == 2
    assert report["origWindowedBlurGate"] == 0
    assert report["zDuringFreeze"] == report["zBeforeFreeze"]
    assert report["zAfterUnfreeze"] > report["zBeforeFreeze"]
    assert report["origWindowedBlurAudio"] == [1]
    assert report["origRefocusAudio"] == [1, 0]
    assert report["origFullscreenBlurState"] == 3
    assert report["origFullscreenBlurGate"] == 1
