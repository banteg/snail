"""The extras archive must provide a complete mobile level dependency graph."""

import io
import re

import pytest
from PIL import Image, ImageChops, ImageStat

from snail.archive import parse_archive_index, read_archive_entry
from snail.port_extras import (
    APK_ASSETS,
    IOS_ROOT,
    build_extras_files,
    hd_surface_tiles,
    match_surface_palette,
)
from snail.symbols import REPO_ROOT

ANDROID = REPO_ROOT / "artifacts/android/asm_extracted"
APK = REPO_ROOT / APK_ASSETS
PC_ARCHIVE = REPO_ROOT / "artifacts/bin/SnailMail.dat"
IOS = REPO_ROOT / IOS_ROOT


def image_bytes(image, format="TGA"):
    stream = io.BytesIO()
    image.save(stream, format=format)
    return stream.getvalue()


@pytest.mark.parametrize("mode", ["RGB", "RGBA"])
def test_hd_surface_decoding_handles_both_tga_depths_and_tile_boundaries(mode):
    atlas = Image.new(mode, (1024, 256))
    # The mobile TGA stores R/B in OpenGL order even in the 24-bit sets 5/6.
    atlas.paste((30, 20, 210), (0, 0, 256, 256))
    atlas.paste((150, 70, 10), (256, 0, 512, 256))
    atlas.paste((1, 2, 3), (0, 0, 16, 16))
    reference = Image.new("RGB", (512, 128))
    track, slide = [Image.open(io.BytesIO(raw)) for raw in hd_surface_tiles(
        image_bytes(atlas), image_bytes(reference, "PNG"), match_palette=False,
    )]
    assert track.size == slide.size == (256, 256)
    assert track.getpixel((32, 32)) == (210, 20, 30)
    assert track.getpixel((0, 0)) == (3, 2, 1)
    assert track.getpixel((0, 255)) == (210, 20, 30)
    assert slide.getpixel((0, 0)) == (10, 70, 150)


def test_palette_transfer_retains_detail_missing_from_the_reference():
    high = Image.new("RGB", (32, 32))
    high.putdata([(80 + (x + y) % 2 * 40, 80, 100) for y in range(32) for x in range(32)])
    reduced = high.resize((16, 16), Image.Resampling.LANCZOS)
    target = reduced.point(lambda value: value + 20)
    actual = match_surface_palette(high, target)
    assert ImageChops.difference(actual, high.point(lambda value: value + 20)).getbbox() is None
    # A plain enlarged reference cannot contain the original 1px alternating detail.
    assert actual.getpixel((16, 16))[0] == 100
    assert actual.getpixel((17, 16))[0] == 140


@pytest.mark.skipif(not (IOS / "objects_world00_hi_surface0.tga").exists() or not PC_ARCHIVE.exists(),
                    reason="needs iPhone 1.9 HD surfaces and SnailMail.dat")
def test_hd_surface_lineage_matches_all_original_pc_track_and_slide_pixels():
    pc_index = parse_archive_index(PC_ARCHIVE)
    reference = image_bytes(Image.new("RGB", (512, 128)), "PNG")
    for index in range(4):
        tiles = hd_surface_tiles(
            (IOS / f"objects_world00_hi_surface{index}.tga").read_bytes(), reference, match_palette=False,
        )
        for name, tile in zip(("TRACK", "SLIDE"), tiles, strict=True):
            original = read_archive_entry(PC_ARCHIVE, pc_index.entry_by_path(f"OBJECTS/WORLD00/{name}{index}.TGA"))
            assert ImageChops.difference(Image.open(io.BytesIO(tile)), Image.open(io.BytesIO(original))).getbbox() is None


@pytest.mark.skipif(not (IOS / "objects_world00_hi_surface6.tga").exists()
                    or not (ANDROID / "BACKGROUNDS/SPACEPRO.JPG").exists()
                    or not (APK / "upramp.ogg").exists() or not PC_ARCHIVE.exists(),
                    reason="needs Android/iPhone source assets and SnailMail.dat")
def test_extras_preserve_hd_tiles_android_red_palette_and_full_pro_skies():
    files = build_extras_files(ANDROID, PC_ARCHIVE, APK, IOS)
    for index in (4, 5, 6):
        source = Image.open(IOS / f"objects_world00_hi_surface{index}.tga").convert("RGB")
        source = Image.merge("RGB", source.split()[::-1])
        android = Image.open(ANDROID / f"OBJECTS/WORLD00/SURFACE{index}.PNG").convert("RGB")
        for column, name in enumerate(("TRACK", "SLIDE")):
            image = Image.open(io.BytesIO(files[f"OBJECTS/WORLD00/{name}{index}.TGA"]))
            assert image.size == (256, 256) and image.mode == "RGB"
            high = source.crop((column * 256, 0, (column + 1) * 256, 256))
            if index == 4:
                target = android.crop((column * 128, 0, (column + 1) * 128, 128))
                error = ImageStat.Stat(ImageChops.difference(image.resize(target.size, Image.Resampling.LANCZOS), target))
                assert max(error.mean) < 1.5
                assert ImageChops.difference(image, high).getbbox() is not None
            else:
                assert ImageChops.difference(image, high).getbbox() is None
    for name in ("SPACEPRO", "SPACEPRO2"):
        source = Image.open(ANDROID / f"BACKGROUNDS/{name}.JPG").convert("RGB")
        image = Image.open(io.BytesIO(files[f"BACKGROUNDS/{name}.TGA"]))
        assert image.size == (512, 512)
        assert ImageChops.difference(image, source).getbbox() is None
    # Only added colours get an overlay; Original and PC colours 0-3 keep their art.
    assert not any(f"OBJECTS/WORLD00/{name}{index}.TGA" in files for name in ("TRACK", "SLIDE") for index in range(4))


@pytest.mark.skipif(
    not (ANDROID / "LEVELS/ARCADEPRO010.TXT").exists()
    or not (IOS / "objects_world00_hi_surface6.tga").exists()
    or not (APK / "upramp.ogg").exists()
    or not PC_ARCHIVE.exists(),
    reason="needs extracted mobile assets, the unpacked APK assets and SnailMail.dat",
)
def test_all_mobile_levels_and_segments_are_preserved():
    files = build_extras_files(ANDROID, PC_ARCHIVE, APK, IOS)
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
        "SFX2/UPRAMP.OGG",
    ):
        assert read_archive_entry(archive, index.entry_by_path(name))


@pytest.mark.skipif(
    not (ANDROID / "LEVELS/TUTORIAL.TXT").exists()
    or not (IOS / "objects_world00_hi_surface6.tga").exists()
    or not (APK / "upramp.ogg").exists()
    or not PC_ARCHIVE.exists(),
    reason="needs extracted mobile assets, the unpacked APK assets and SnailMail.dat",
)
def test_mobile_tutorial_course_shows_the_pc_text_for_its_voice_clips():
    tutorial = build_extras_files(ANDROID, PC_ARCHIVE, APK, IOS)["LEVELS/TUTORIAL.TXT"].decode("latin-1")
    mobile = (ANDROID / "LEVELS/TUTORIAL.TXT").read_bytes().decode("latin-1")
    # The mobile course: its speed and segment order stay.
    assert re.findall(r"^(Speed:.*|Tutorial \d+\.txt Duration=[\d.]+)", tutorial, re.MULTILINE) == re.findall(
        r"^(Speed:.*|Tutorial \d+\.txt Duration=[\d.]+)", mobile, re.MULTILINE
    )
    # The PC voice clips' words, for the mouse.
    assert 'Message="Hi! I\'m Turbo the Snail.>Steer } with the mouse!"' in tutorial
    assert 'Message="Asteroids slow me down.> Hold the Mouse Button> to shoot ]"' in tutorial
    assert "Tilt" not in tutorial
    assert "SampleB" not in tutorial and "MessageB" not in tutorial
    assert "Touch anywhere" not in tutorial
    # Segment option tails must fit LevelDefinitionParseBuffers::line_options[128].
    option_lengths = [
        len(line.split(" ", 2)[2])
        for line in tutorial.splitlines()
        if line.startswith("Tutorial ") and len(line.split(" ", 2)) == 3
    ]
    assert option_lengths and max(option_lengths) < 128


@pytest.mark.skipif(
    not (ANDROID / "X/_ANIMATION.TXT").exists() or not PC_ARCHIVE.exists()
    or not (IOS / "objects_world00_hi_surface6.tga").exists(),
    reason="needs extracted mobile assets and SnailMail.dat",
)
def test_mobile_credits_and_fall_animation_replace_the_pc_scripts():
    files = build_extras_files(ANDROID, PC_ARCHIVE, APK, IOS)
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


@pytest.mark.skipif(
    not (ANDROID / "LEVELS/ARCADEPRO010.TXT").exists()
    or not (IOS / "objects_world00_hi_surface6.tga").exists()
    or not (APK / "upramp.ogg").exists()
    or not PC_ARCHIVE.exists(),
    reason="needs extracted mobile assets, the unpacked APK assets and SnailMail.dat",
)
def test_extras_add_the_mobile_ramp_sound_beside_the_pc_ones():
    files = build_extras_files(ANDROID, PC_ARCHIVE, APK, IOS)
    assert files["SFX2/UPRAMP.OGG"] == (APK / "upramp.ogg").read_bytes()
    # The PC archive has no ramp sound, so Ultimate replaces none of its sounds.
    pc_sounds = [entry.path for entry in parse_archive_index(PC_ARCHIVE).entries if entry.path.startswith("SFX2/")]
    assert pc_sounds and "SFX2/UPRAMP.OGG" not in pc_sounds
    assert [name for name in files if name.startswith("SFX2/")] == ["SFX2/UPRAMP.OGG"]
