"""The extras archive must provide a complete mobile level dependency graph."""

import re

import pytest

from snail.archive import parse_archive_index, read_archive_entry
from snail.port_extras import build_extras_files
from snail.symbols import REPO_ROOT

ANDROID = REPO_ROOT / "artifacts/android/asm_extracted"
PC_ARCHIVE = REPO_ROOT / "artifacts/bin/SnailMail.dat"


@pytest.mark.skipif(
    not (ANDROID / "LEVELS/ARCADEPRO010.TXT").exists() or not PC_ARCHIVE.exists(),
    reason="needs extracted mobile assets and SnailMail.dat",
)
def test_all_mobile_levels_and_segments_are_preserved():
    files = build_extras_files(ANDROID, PC_ARCHIVE)
    for directory in ("LEVELS", "SEGMENTS"):
        for path in (ANDROID / directory).glob("*.TXT"):
            if f"{directory}/{path.name}" != "LEVELS/TUTORIAL.TXT":
                assert files[f"{directory}/{path.name}"] == path.read_bytes()
    # Include the mobile revisions of shared names, not just added filenames.
    assert len([name for name in files if name.startswith("SEGMENTS/")]) == 176
    assert len([name for name in files if name.startswith("LEVELS/")]) == 65
    for name, contents in files.items():
        if not name.startswith("LEVELS/"):
            continue
        for match in re.finditer(
            rb"^([^:\r\n]+?\.txt)", contents, re.MULTILINE | re.IGNORECASE
        ):
            assert "SEGMENTS/" + match[1].decode().strip().upper() in files, (
                name,
                match[1],
            )


@pytest.mark.skipif(
    not (REPO_ROOT / "artifacts/bin/SnailMailExtras.dat").exists(),
    reason="needs extras archive",
)
def test_deployable_extras_include_mobile_shared_dependencies():
    archive = REPO_ROOT / "artifacts/bin/SnailMailExtras.dat"
    index = parse_archive_index(archive)
    for name in (
        "SEGMENTS/CAGE2.TXT",
        "SEGMENTS/FINISH.TXT",
        "SEGMENTS/TWISTER2.TXT",
        "LEVELS/ARCADE001.TXT",
        "LEVELS/ARCADE050.TXT",
        "LEVELS/TUTORIAL.TXT",
        "INTRO/CREDITS.TXT",
        "X/_ANIMATION.TXT",
    ):
        assert read_archive_entry(archive, index.entry_by_path(name))


@pytest.mark.skipif(
    not (ANDROID / "LEVELS/TUTORIAL.TXT").exists() or not PC_ARCHIVE.exists(),
    reason="needs extracted mobile assets and SnailMail.dat",
)
def test_mobile_tutorial_course_shows_the_pc_text_for_its_voice_clips():
    tutorial = build_extras_files(ANDROID, PC_ARCHIVE)["LEVELS/TUTORIAL.TXT"].decode("latin-1")
    mobile = (ANDROID / "LEVELS/TUTORIAL.TXT").read_bytes().decode("latin-1")
    # The mobile course: its speed and segment order stay.
    assert re.findall(r"^(Speed:.*|Tutorial \d+\.txt Duration=[\d.]+)", tutorial, re.MULTILINE) == re.findall(
        r"^(Speed:.*|Tutorial \d+\.txt Duration=[\d.]+)", mobile, re.MULTILINE
    )
    # The PC voice clips' words, for the mouse.
    assert 'Message="Hi! I\'m Turbo the Snail.>Steer } with the mouse!"' in tutorial
    assert 'Message="Asteroids slow me down.> Hold the Mouse Button> to shoot ]"' in tutorial
    assert "Tilt" not in tutorial.replace("MessageB", "")
    assert "Touch anywhere" not in tutorial


@pytest.mark.skipif(
    not (ANDROID / "X/_ANIMATION.TXT").exists() or not PC_ARCHIVE.exists(),
    reason="needs extracted mobile assets and SnailMail.dat",
)
def test_mobile_credits_and_fall_animation_replace_the_pc_scripts():
    files = build_extras_files(ANDROID, PC_ARCHIVE)
    pc_index = parse_archive_index(PC_ARCHIVE)

    def pc_file(name):
        return read_archive_entry(PC_ARCHIVE, pc_index.entry_by_path(name))

    # cRLogo::Init reads both crawls the same way; Android's lists the mobile
    # staff and runs for 45 s.
    assert files["INTRO/CREDITS.TXT"] == (ANDROID / "INTRO/CREDITS.TXT").read_bytes()
    assert b"Duration:35" in pc_file("Intro/Credits.txt")
    assert b"Duration:45" in files["INTRO/CREDITS.TXT"]

    # cRDirectX::LoadAnim reads only Duration and Mode. Only the fall differs:
    # Android ping-pongs it every second, as its baked O_TURBO-FALL-000.SMO does.
    def clips(script):
        return {
            name: (re.findall(rb"Duration:(\S+)", block), re.findall(rb"mode:(\S+)", block.lower()))
            for name, block in re.findall(rb"Anim:(\S+)(.*?)AnimEnd:", script, re.DOTALL)
        }

    pc = clips(pc_file("X/_Animation.txt"))
    mobile = clips(files["X/_ANIMATION.TXT"])
    assert pc.keys() == mobile.keys()
    assert {name for name in pc if pc[name] != mobile[name]} == {b"turbo-fall-000.x"}
    assert pc[b"turbo-fall-000.x"] == ([b"6"], [b"once"])
    assert mobile[b"turbo-fall-000.x"] == ([b"1"], [b"pingpong"])
