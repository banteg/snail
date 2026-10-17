"""The front end each profile shows: menu labels and order, route cards, credits, galaxy maps and endings."""

import hashlib
import io
import json
import re
import shutil
import struct
import subprocess

import pytest
from PIL import Image

from snail.archive import parse_archive_index, read_archive_entry
from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail.wasm"
WEB_WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
ASSETS = REPO_ROOT / "artifacts/bin"
ARCHIVES = ("SnailMail.dat", "SnailMailExtras.dat")


def _write_configs(directory, selected_route=46):
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    config[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", config, 0xA0, 50, selected_route)
    config[0xC0] = 1
    (directory / "SnailMail.cfg").write_bytes(config)
    (directory / "SnailMailMobile.cfg").write_bytes(config)


def _screens(stderr):
    """Each settled screen's widget labels, top to bottom, from --trace."""
    screens = []
    for block in stderr.split(": widgets\n")[1:]:
        rows = re.findall(r'^  widget \d+ at \(([-\d]+), ([-\d]+)\).*"(.*)"$', block, re.MULTILINE)
        screens.append([text for _, y, text in sorted(rows, key=lambda row: int(row[1]))])
    return screens


@pytest.mark.skipif(
    shutil.which("node") is None or not WASM.exists() or not all((ASSETS / name).exists() for name in ARCHIVES),
    reason="needs node, snail.wasm, SnailMail.dat and SnailMailExtras.dat",
)
@pytest.mark.parametrize("profile", ["original", "ultimate"])
def test_menus_and_route_cards_follow_the_profile(tmp_path, profile):
    for name in ARCHIVES:
        (tmp_path / name).symlink_to(ASSETS / name)
    _write_configs(tmp_path)
    keys = tmp_path / "postal.keys"
    keys.write_text("600 escape\n700 mouse 345 112\n720 click 3\n800 mouse 345 170\n820 click 3\n900 mouse 320 300\n")
    result = subprocess.run(
        ["node", str(REPO_ROOT / "port/shell/run.mjs"), str(WASM), "--profile", profile, "--trace", "--keys", str(keys)],
        cwd=tmp_path, capture_output=True, text=True, check=True,
    )  # fmt: skip
    screens = _screens(result.stderr)
    main_menu = next(screen for screen in screens if "Exit" in screen)
    new_game = next(screen for screen in screens if "Tutorial" in screen)
    galaxy = next(screen for screen in screens if "Deliver!" in screen)
    modes = [text for text in new_game if text not in ("Help", "Back")]
    if profile == "ultimate":
        # Android's labels and order (cRMainMenu::Init, cRIntro::Init); the PC keeps Exit.
        assert main_menu == ["Play", "High Scores", "Options", "Options", "Credits", "Exit"]
        assert modes == ["Tutorial", "Postal Adventure", "Pro-Challenge", "Time Trial", "Challenge Mode"]
        # Android's route card leads with the level numeral (cRGalaxy::BoxOn).
        assert "XLVI: Pomacea cuprina aurea" in galaxy
    else:
        assert main_menu == ["New Game", "High Scores", "Options", "Options", "Credits", "Exit"]
        assert modes == ["Tutorial", "Postal Mode", "Time Trial", "Challenge Mode"]
        assert "Pomacea cuprina aurea" in galaxy
    assert "Intergalactic Delivery Route" in galaxy


@pytest.mark.skipif(
    shutil.which("node") is None or not WASM.exists() or not all((ASSETS / name).exists() for name in ARCHIVES),
    reason="needs node, snail.wasm, SnailMail.dat and SnailMailExtras.dat",
)
@pytest.mark.parametrize(("profile", "seconds"), [("original", 35), ("ultimate", 45)])
def test_credits_roll_for_the_profiles_duration(tmp_path, profile, seconds):
    for name in ARCHIVES:
        (tmp_path / name).symlink_to(ASSETS / name)
    keys = tmp_path / "credits.keys"
    keys.write_text("600 escape\n700 mouse 345 323\n720 click 3\n3600 mouse 320 300\n")
    result = subprocess.run(
        ["node", str(REPO_ROOT / "port/shell/run.mjs"), str(WASM), "--profile", profile, "--trace", "--keys", str(keys)],
        cwd=tmp_path, capture_output=True, text=True, check=True,
    )  # fmt: skip
    states = [(int(tick), int(state)) for tick, state in re.findall(r"tick (\d+): frontend_state (\d+)", result.stderr)]
    start = next(tick for tick, state in states if state == 15)
    end = next(tick for tick, state in states if tick > start)
    # Intro/Credits.txt's Duration: the PC's 35 s, or Android's 45 s from the extras pack.
    assert seconds * 60 <= end - start < (seconds + 1) * 60


def _galaxy_sprite_hashes():
    """The PC Galaxy000-009 sprites as the port uploads them (rows top first, D3DX colour key applied)."""
    archive = ASSETS / "SnailMail.dat"
    index = parse_archive_index(archive)
    hashes = []
    for galaxy in range(10):
        data = read_archive_entry(archive, index.entry_by_path(f"Galaxy/Galaxy{galaxy:03}.tga"))
        pixels = bytearray(Image.open(io.BytesIO(data)).convert("RGBA").tobytes())
        if data[16] == 32:  # load_registered_texture_ref keys out transparent white
            for i in range(0, len(pixels), 4):
                if pixels[i : i + 4] == b"\xff\xff\xff\x00":
                    pixels[i : i + 4] = bytes(4)
        hashes.append(hashlib.sha1(pixels).hexdigest())
    return hashes


@pytest.mark.skipif(
    shutil.which("node") is None or not WEB_WASM.exists() or not all((ASSETS / name).exists() for name in ARCHIVES),
    reason="needs node, snail-web.wasm, SnailMail.dat and SnailMailExtras.dat",
)
@pytest.mark.parametrize(
    ("profile", "galaxy"), [("original", "postal"), ("ultimate", "postal"), ("ultimate", "pro")]
)
def test_galaxy_maps_and_endings(tmp_path, port_layout_env, profile, galaxy):
    for name in ARCHIVES:
        shutil.copyfile(ASSETS / name, tmp_path / name)
    _write_configs(tmp_path)
    menu_y, first_galaxy = (240, "Limax maximus") if galaxy == "pro" else (170, "Pomacea cuprina")
    result = subprocess.run(
        [
            "node", str(REPO_ROOT / "tests/port_frontend.mjs"), str(WEB_WASM), str(int(profile == "ultimate")),
            str(menu_y), first_galaxy, json.dumps(_galaxy_sprite_hashes()),
        ],
        cwd=tmp_path, env=port_layout_env, capture_output=True, text=True, check=True,
    )  # fmt: skip
    data = json.loads(result.stdout.splitlines()[-1])
    texts = [data["texts"][state] for state in ("0", "2", "4")]
    if galaxy == "pro":
        # Android paints both Pro galaxies into StarmapProbg and draws no galaxy
        # sprites (cRGalaxy::Render); its Pro ending has its own texts (cRSplash).
        assert data["visible"] == 0 and data["hidden"] > 0
        assert texts == ["Holy Flying Snails!", "That isn't humanly possible!", "You're totally awesome!"]
    else:
        assert data["visible"] > 0
        assert texts == [
            "Thanks For Playing!",
            "Test your reflexes in Challenge Mode!",
            "Improve your skills in Time Trial!",
        ]
