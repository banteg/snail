"""The extras archive must provide a complete mobile level dependency graph."""

import re

import pytest

from snail.archive import parse_archive_index, read_archive_entry
from snail.port_extras import APK_ASSETS, build_extras_files
from snail.symbols import REPO_ROOT

ANDROID = REPO_ROOT / "artifacts/android/asm_extracted"
APK = REPO_ROOT / APK_ASSETS
PC_ARCHIVE = REPO_ROOT / "artifacts/bin/SnailMail.dat"


@pytest.mark.skipif(
    not (ANDROID / "LEVELS/ARCADEPRO010.TXT").exists()
    or not (APK / "upramp.ogg").exists()
    or not PC_ARCHIVE.exists(),
    reason="needs extracted mobile assets, the unpacked APK assets and SnailMail.dat",
)
def test_all_mobile_levels_and_segments_are_preserved():
    files = build_extras_files(ANDROID, PC_ARCHIVE, APK)
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
        "SFX2/UPRAMP.OGG",
    ):
        assert read_archive_entry(archive, index.entry_by_path(name))


@pytest.mark.skipif(
    not (ANDROID / "LEVELS/TUTORIAL.TXT").exists()
    or not (APK / "upramp.ogg").exists()
    or not PC_ARCHIVE.exists(),
    reason="needs extracted mobile assets, the unpacked APK assets and SnailMail.dat",
)
def test_mobile_tutorial_course_shows_the_pc_text_for_its_voice_clips():
    tutorial = build_extras_files(ANDROID, PC_ARCHIVE, APK)["LEVELS/TUTORIAL.TXT"].decode("latin-1")
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
    not (ANDROID / "LEVELS/ARCADEPRO010.TXT").exists()
    or not (APK / "upramp.ogg").exists()
    or not PC_ARCHIVE.exists(),
    reason="needs extracted mobile assets, the unpacked APK assets and SnailMail.dat",
)
def test_extras_add_the_mobile_ramp_sound_beside_the_pc_ones():
    files = build_extras_files(ANDROID, PC_ARCHIVE, APK)
    assert files["SFX2/UPRAMP.OGG"] == (APK / "upramp.ogg").read_bytes()
    # The PC archive has no ramp sound, so Ultimate replaces none of its sounds.
    pc_sounds = [entry.path for entry in parse_archive_index(PC_ARCHIVE).entries if entry.path.startswith("SFX2/")]
    assert pc_sounds and "SFX2/UPRAMP.OGG" not in pc_sounds
    assert [name for name in files if name.startswith("SFX2/")] == ["SFX2/UPRAMP.OGG"]
