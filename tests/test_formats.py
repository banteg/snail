from __future__ import annotations

from pathlib import Path

from snail.formats import (
    LevelDefinition,
    ObjectDefinition,
    SegmentDefinition,
    parse_text_asset,
)


EXTRACTED_ROOT = Path(__file__).resolve().parents[1] / "artifacts/extracted/SnailMail.dat"


def test_parse_font3d_object_definition() -> None:
    parsed = parse_text_asset(EXTRACTED_ROOT / "OBJECTS/FONT3D/_OBJECT.TXT")

    assert isinstance(parsed, ObjectDefinition)
    assert len(parsed.vertices) == 4
    assert len(parsed.faces) == 1
    assert parsed.texture_names == ("Letter",)
    assert parsed.vertices[0].position.z == 0.5
    assert parsed.faces[0].vertex_indices == (0, 1, 2, 3)
    assert parsed.faces[0].texture == "Letter"


def test_parse_start_segment_definition() -> None:
    parsed = parse_text_asset(EXTRACTED_ROOT / "SEGMENTS/START.TXT")

    assert isinstance(parsed, SegmentDefinition)
    assert parsed.segment_id == 1
    assert parsed.name == "Start"
    assert parsed.width == 10
    assert parsed.rows[5].cells == "@PPPPPPPP@"
    assert parsed.rows[5].annotation is not None
    assert parsed.rows[5].annotation.key == "Path"
    assert parsed.rows[5].annotation.value == "Start"


def test_parse_big_jump_segment_annotation() -> None:
    parsed = parse_text_asset(EXTRACTED_ROOT / "SEGMENTS/BIG JUMP.TXT")

    assert isinstance(parsed, SegmentDefinition)
    ring_row = next(row for row in parsed.rows if row.annotation and row.annotation.key == "Ring")
    assert ring_row.cells == "@  {}{}  @"
    assert ring_row.annotation is not None
    assert ring_row.annotation.value == "Explode"


def test_parse_arcade_level_definition() -> None:
    parsed = parse_text_asset(EXTRACTED_ROOT / "LEVELS/ARCADE000.TXT")

    assert isinstance(parsed, LevelDefinition)
    assert parsed.name == "Test"
    assert parsed.mode == "arcade"
    assert parsed.background == "SpacePurple.txt"
    assert parsed.fringe == (128, 24, 200)
    assert parsed.garbage == 65
    assert parsed.random is False
    assert parsed.length == 500
    assert [entry.path for entry in parsed.segments] == [
        "Wibble.txt",
        "Jump Over.txt",
        "Jump Over2.txt",
        "Explosive3.txt",
    ]
    assert parsed.first_segments == ("Start.txt",)
    assert parsed.last_segments == ("Finish.txt",)


def test_parse_tutorial_level_segment_metadata() -> None:
    parsed = parse_text_asset(EXTRACTED_ROOT / "LEVELS/TUTORIAL.TXT")

    assert isinstance(parsed, LevelDefinition)
    assert parsed.mode == "tutorial"
    assert parsed.track == 0
    assert parsed.garbage == 0
    assert parsed.segments[0].path == "Tutorial 0.txt"
    assert parsed.segments[0].duration == 5.5
    assert parsed.segments[0].sample == "Voice/tut1.ogg"
    assert "Turbo the Snail" in (parsed.segments[0].message or "")


def test_parse_level_segment_angle_metadata() -> None:
    parsed = parse_text_asset(EXTRACTED_ROOT / "LEVELS/ARCADE038.TXT")

    assert isinstance(parsed, LevelDefinition)
    worm = next(entry for entry in parsed.segments if entry.path == "Worm.txt")
    assert worm.angle == 360.0
    assert parsed.galaxy_text is not None
    assert "jetpack" in parsed.galaxy_text.lower()


def test_parse_challenge_level_random_track_alias() -> None:
    parsed = parse_text_asset(EXTRACTED_ROOT / "LEVELS/CHALLENGE000.TXT")

    assert isinstance(parsed, LevelDefinition)
    assert parsed.mode == "challenge"
    assert parsed.track == 5
