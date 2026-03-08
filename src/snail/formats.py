from __future__ import annotations

import re
from pathlib import Path
from typing import Literal

import msgspec


BLOCK_COMMENT_RE = re.compile(r"/\*.*?\*/")
LEVEL_ATTRIBUTE_RE = re.compile(r'([A-Za-z]+)=("([^"]*)"|[^\s]+)')

FormatKind = Literal["auto", "object", "segment", "level"]


class Vec2(msgspec.Struct, frozen=True):
    x: float
    y: float


class Vec3(msgspec.Struct, frozen=True):
    x: float
    y: float
    z: float


class ObjectVertex(msgspec.Struct, frozen=True):
    index: int
    position: Vec3


class ObjectFaceQuad(msgspec.Struct, frozen=True):
    index: int
    vertex_indices: tuple[int, int, int, int]
    texcoords: tuple[Vec2, Vec2, Vec2, Vec2]
    texture: str


class ObjectDefinition(msgspec.Struct, frozen=True):
    source: str | None = None
    vertices: tuple[ObjectVertex, ...] = ()
    faces: tuple[ObjectFaceQuad, ...] = ()
    texture_names: tuple[str, ...] = ()


class SegmentAnnotation(msgspec.Struct, frozen=True):
    raw: str
    key: str
    value: str | None = None


class SegmentRow(msgspec.Struct, frozen=True):
    cells: str
    annotation: SegmentAnnotation | None = None


class SegmentDefinition(msgspec.Struct, frozen=True):
    source: str | None = None
    segment_id: int = 0
    name: str = ""
    width: int = 0
    height: int = 0
    rows: tuple[SegmentRow, ...] = ()


class LevelSegmentAttribute(msgspec.Struct, frozen=True):
    key: str
    value: str


class LevelSegmentEntry(msgspec.Struct, frozen=True):
    path: str
    duration: float | None = None
    sample: str | None = None
    message: str | None = None
    angle: float | None = None
    attributes: tuple[LevelSegmentAttribute, ...] = ()


class LevelDefinition(msgspec.Struct, frozen=True):
    source: str | None = None
    name: str = ""
    mode: str = ""
    track: int | None = None
    galaxy_text: str | None = None
    background: str | None = None
    fringe: tuple[int, int, int] | None = None
    parcels: int | None = None
    quota: int | None = None
    speed: int | None = None
    garbage: int | None = None
    salt: int | None = None
    flags: tuple[str, ...] = ()
    random: bool | None = None
    length: int | str | None = None
    segments: tuple[LevelSegmentEntry, ...] = ()
    first_segments: tuple[str, ...] = ()
    last_segments: tuple[str, ...] = ()


ParsedTextAsset = ObjectDefinition | SegmentDefinition | LevelDefinition


def parse_text_asset(path: Path, kind: FormatKind = "auto") -> ParsedTextAsset:
    source = path.resolve().as_posix()
    text = path.read_text(encoding="utf-8")
    detected_kind = detect_format_kind(path, text) if kind == "auto" else kind

    if detected_kind == "object":
        return parse_object_text(text, source=source)
    if detected_kind == "segment":
        return parse_segment_text(text, source=source)
    if detected_kind == "level":
        return parse_level_text(text, source=source)
    raise ValueError(f"Unsupported format kind: {detected_kind}")


def detect_format_kind(path: Path, text: str | None = None) -> Literal["object", "segment", "level"]:
    parts_upper = {part.upper() for part in path.parts}
    if path.name.upper() == "_OBJECT.TXT" or "OBJECTS" in parts_upper:
        return "object"
    if "SEGMENTS" in parts_upper:
        return "segment"
    if "LEVELS" in parts_upper:
        return "level"

    content = text if text is not None else path.read_text(encoding="utf-8")
    if "[VERTEX START]" in content:
        return "object"
    if "Segments Begin:" in content:
        return "level"
    if "Data:" in content and "Name:'" in content:
        return "segment"
    raise ValueError(f"Could not detect text format for {path}")


def parse_object_text(text: str, source: str | None = None) -> ObjectDefinition:
    lines = text.splitlines()
    vertices: list[ObjectVertex] = []
    faces: list[ObjectFaceQuad] = []
    in_vertices = False
    in_faces = False

    for raw_line in lines:
        line = raw_line.strip()
        if not line or line.startswith("*"):
            continue
        if line == "[VERTEX START]":
            in_vertices = True
            continue
        if line == "[VERTEX END]":
            in_vertices = False
            continue
        if line == "[FACEQUAD START]":
            in_faces = True
            continue
        if line == "[FACEQUAD END]":
            in_faces = False
            continue

        if in_vertices:
            parts = line.split()
            if len(parts) != 4:
                raise ValueError(f"Invalid object vertex line: {raw_line!r}")
            vertices.append(
                ObjectVertex(
                    index=int(parts[0]),
                    position=Vec3(
                        x=float(parts[1]),
                        y=float(parts[2]),
                        z=float(parts[3]),
                    ),
                )
            )
            continue

        if in_faces:
            parts = line.split()
            if len(parts) != 14:
                raise ValueError(f"Invalid object face line: {raw_line!r}")
            faces.append(
                ObjectFaceQuad(
                    index=int(parts[0]),
                    vertex_indices=tuple(int(value) for value in parts[1:5]),
                    texcoords=(
                        Vec2(x=float(parts[5]), y=float(parts[6])),
                        Vec2(x=float(parts[7]), y=float(parts[8])),
                        Vec2(x=float(parts[9]), y=float(parts[10])),
                        Vec2(x=float(parts[11]), y=float(parts[12])),
                    ),
                    texture=parts[13],
                )
            )

    return ObjectDefinition(
        source=source,
        vertices=tuple(vertices),
        faces=tuple(faces),
        texture_names=tuple(dict.fromkeys(face.texture for face in faces)),
    )


def parse_segment_text(text: str, source: str | None = None) -> SegmentDefinition:
    segment_id: int | None = None
    name: str | None = None
    rows: list[SegmentRow] = []
    in_data = False

    for raw_line in text.splitlines():
        if in_data:
            if not raw_line:
                continue
            cells = raw_line[:10]
            suffix = raw_line[10:].strip()
            rows.append(
                SegmentRow(
                    cells=cells,
                    annotation=_parse_segment_annotation(suffix) if suffix else None,
                )
            )
            continue

        line = _strip_inline_comments(raw_line).strip()
        if not line or line.startswith("//"):
            continue
        if line.startswith("ID:"):
            segment_id = int(line.split(":", 1)[1].strip())
        elif line.startswith("Name:"):
            name = _parse_single_quoted_value(line)
        elif line.startswith("Data:"):
            in_data = True

    if segment_id is None:
        raise ValueError("Segment ID is missing")
    if name is None:
        raise ValueError("Segment name is missing")

    width = max((len(row.cells) for row in rows), default=0)
    return SegmentDefinition(
        source=source,
        segment_id=segment_id,
        name=name,
        width=width,
        height=len(rows),
        rows=tuple(rows),
    )


def parse_level_text(text: str, source: str | None = None) -> LevelDefinition:
    name = ""
    mode = ""
    track: int | None = None
    galaxy_text: str | None = None
    background: str | None = None
    fringe: tuple[int, int, int] | None = None
    parcels: int | None = None
    quota: int | None = None
    speed: int | None = None
    garbage: int | None = None
    salt: int | None = None
    flags: tuple[str, ...] = ()
    random: bool | None = None
    length: int | str | None = None
    segments: list[LevelSegmentEntry] = []
    first_segments: list[str] = []
    last_segments: list[str] = []

    lines = text.splitlines()
    index = 0
    while index < len(lines):
        raw_line = lines[index]
        line = _strip_inline_comments(raw_line).strip()
        if not line:
            index += 1
            continue

        if line.startswith("GalaxyText:"):
            galaxy_text, index = _parse_braced_block(lines, index + 1)
            continue

        if line.startswith("Segments Begin:"):
            inline = line.partition(":")[2].strip()
            segments, index = _parse_level_segment_block(lines, index + 1, inline)
            continue

        if line.startswith("First:"):
            inline = line.partition(":")[2].strip()
            first_segments, index = _parse_level_path_block(lines, index + 1, inline)
            continue

        if line.startswith("Last:"):
            inline = line.partition(":")[2].strip()
            last_segments, index = _parse_level_path_block(lines, index + 1, inline)
            continue

        key, _, value = line.partition(":")
        key_lower = key.strip().lower()
        value = value.strip()

        if key_lower == "name":
            name = _parse_single_quoted_value(line)
        elif key_lower == "mode":
            mode = value
        elif key_lower == "track":
            track = _parse_track_value(value)
        elif key_lower == "background":
            background = value
        elif key_lower == "fringe":
            fringe = _parse_rgb_tuple(value)
        elif key_lower == "parcels":
            parcels = int(value)
        elif key_lower == "quota":
            quota = int(value)
        elif key_lower == "speed":
            speed = int(value)
        elif key_lower in {"slug", "garbage"}:
            garbage = int(value)
        elif key_lower == "salt":
            salt = int(value)
        elif key_lower == "flags":
            flags = tuple(part for part in re.split(r"[,\s]+", value) if part)
        elif key_lower == "random":
            random = value.lower() == "yes"
        elif key_lower == "length":
            length = int(value) if value.isdigit() else value

        index += 1

    return LevelDefinition(
        source=source,
        name=name,
        mode=mode,
        track=track,
        galaxy_text=galaxy_text,
        background=background,
        fringe=fringe,
        parcels=parcels,
        quota=quota,
        speed=speed,
        garbage=garbage,
        salt=salt,
        flags=flags,
        random=random,
        length=length,
        segments=tuple(segments),
        first_segments=tuple(first_segments),
        last_segments=tuple(last_segments),
    )


def _parse_segment_annotation(raw: str) -> SegmentAnnotation:
    if "=" in raw:
        key, value = raw.split("=", 1)
        return SegmentAnnotation(raw=raw, key=key.strip(), value=value.strip())
    return SegmentAnnotation(raw=raw, key=raw.strip(), value=None)


def _parse_level_segment_block(
    lines: list[str],
    start: int,
    inline: str = "",
) -> tuple[list[LevelSegmentEntry], int]:
    entries: list[LevelSegmentEntry] = []
    if inline:
        entries.append(_parse_level_segment_entry(inline))
    index = start
    while index < len(lines):
        line = _strip_inline_comments(lines[index]).strip()
        if not line:
            index += 1
            continue
        if line.startswith("Segments End:"):
            return entries, index + 1
        entries.append(_parse_level_segment_entry(line))
        index += 1
    return entries, index


def _parse_level_path_block(
    lines: list[str],
    start: int,
    inline: str = "",
) -> tuple[list[str], int]:
    values: list[str] = []
    if inline:
        values.append(inline)
    index = start
    while index < len(lines):
        line = _strip_inline_comments(lines[index]).strip()
        if not line:
            index += 1
            if values:
                break
            continue
        if _looks_like_field(line):
            break
        values.append(line)
        index += 1
    return values, index


def _parse_braced_block(lines: list[str], start: int) -> tuple[str | None, int]:
    index = start
    while index < len(lines) and _strip_inline_comments(lines[index]).strip() != "{":
        if _strip_inline_comments(lines[index]).strip():
            break
        index += 1
    if index >= len(lines) or _strip_inline_comments(lines[index]).strip() != "{":
        return None, index

    index += 1
    block_lines: list[str] = []
    while index < len(lines):
        if _strip_inline_comments(lines[index]).strip() == "}":
            return ("\n".join(block_lines).strip() or None), index + 1
        block_lines.append(lines[index].rstrip())
        index += 1
    return ("\n".join(block_lines).strip() or None), index


def _parse_level_segment_entry(line: str) -> LevelSegmentEntry:
    lower = line.lower()
    path_end = lower.find(".txt")
    if path_end == -1:
        raise ValueError(f"Invalid level segment entry: {line!r}")

    path = line[: path_end + 4].strip()
    remainder = line[path_end + 4 :].strip()

    duration: float | None = None
    sample: str | None = None
    message: str | None = None
    angle: float | None = None
    attributes: list[LevelSegmentAttribute] = []

    for match in LEVEL_ATTRIBUTE_RE.finditer(remainder):
        key = match.group(1)
        raw_value = match.group(2)
        value = raw_value[1:-1] if raw_value.startswith('"') and raw_value.endswith('"') else raw_value
        attributes.append(LevelSegmentAttribute(key=key, value=value))

        key_lower = key.lower()
        if key_lower == "duration":
            duration = float(value)
        elif key_lower == "sample":
            sample = value
        elif key_lower == "message":
            message = value
        elif key_lower == "angle":
            angle = float(value)

    return LevelSegmentEntry(
        path=path,
        duration=duration,
        sample=sample,
        message=message,
        angle=angle,
        attributes=tuple(attributes),
    )


def _parse_single_quoted_value(line: str) -> str:
    match = re.search(r"'([^']*)'", line)
    if not match:
        raise ValueError(f"Expected single-quoted value in: {line!r}")
    return match.group(1)


def _parse_rgb_tuple(value: str) -> tuple[int, int, int]:
    match = re.fullmatch(r"\(([-\d]+),([-\d]+),([-\d]+)\)", value)
    if match is None:
        raise ValueError(f"Invalid RGB tuple: {value!r}")
    return (int(match.group(1)), int(match.group(2)), int(match.group(3)))


def _parse_track_value(value: str) -> int:
    normalized = value.strip().lower()
    if normalized in {"r", "random"}:
        return 5
    return int(value)


def _strip_inline_comments(line: str) -> str:
    return BLOCK_COMMENT_RE.sub("", line)


def _looks_like_field(line: str) -> bool:
    return bool(re.match(r"[A-Za-z][A-Za-z0-9 ]*:", line))
