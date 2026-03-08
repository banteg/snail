from __future__ import annotations

from collections import Counter, defaultdict
from pathlib import Path

import msgspec

from .formats import LevelDefinition, SegmentDefinition, parse_text_asset


class TraceVec3(msgspec.Struct, frozen=True):
    x: float
    y: float
    z: float


class TraceCell(msgspec.Struct, frozen=True):
    ptr: str | None = None
    row: int | None = None
    tile_type: int | None = None
    world: TraceVec3 | None = None
    attachment: str | None = None
    attachment_kind: int | None = None


class RuntimeTraceEvent(msgspec.Struct, frozen=True):
    ts_ms: int
    pid: int
    tid: int
    event: str
    seq: int | None = None
    game: str | None = None
    level_descriptor: str | None = None
    retval: int | None = None
    selected_track_id: int | None = None
    active_level: str | None = None
    garbage_scalar: float | None = None
    salt_scalar: float | None = None
    path_name: str | None = None
    path_index: int | None = None
    template: str | None = None
    follow_state: str | None = None
    player: str | None = None
    slot_manager: str | None = None
    slot_result: int | None = None
    manager: str | None = None
    manager_sprite_bank: str | None = None
    sprite_id: int | None = None
    position: TraceVec3 | None = None
    velocity: TraceVec3 | None = None
    player_position: TraceVec3 | None = None
    cell: TraceCell | None = None
    hooks: dict[str, bool] | None = None
    module: str | None = None
    module_base: str | None = None
    module_path: str | None = None
    target_module: str | None = None
    limit: int | None = None


class LevelRuntimeSample(msgspec.Struct, frozen=True):
    seq: int | None = None
    selected_track_id: int | None = None
    garbage_scalar: float | None = None
    salt_scalar: float | None = None
    active_level: str | None = None


class PathIndexSummary(msgspec.Struct, frozen=True):
    path_index: int
    count: int
    names: tuple[str, ...]


class TraceBucketSummary(msgspec.Struct, frozen=True):
    count: int
    rows: dict[int, int]
    tile_types: dict[int, int]
    attachment_kinds: dict[int, int]
    positions_preview: tuple[TraceVec3, ...]


class RuntimeTraceSummary(msgspec.Struct, frozen=True):
    source: str
    total_events: int
    event_counts: dict[str, int]
    levels: tuple[LevelRuntimeSample, ...]
    path_lookups_by_name: dict[str, int]
    path_lookups_by_index: tuple[PathIndexSummary, ...]
    attachment_probes: TraceBucketSummary
    attachment_begins: TraceBucketSummary
    garbage_spawns: TraceBucketSummary
    salt_spawns: TraceBucketSummary
    slug_spawns: TraceBucketSummary


class SegmentTraceHint(msgspec.Struct, frozen=True):
    path: str
    name: str
    path_rows: int
    path_names: tuple[str, ...]
    slug_like_rows: int
    no_fall_rows: int
    jetpack_off_rows: int


class LevelTraceHint(msgspec.Struct, frozen=True):
    path: str
    name: str
    mode: str
    garbage: int | None
    salt: int | None
    segment_count: int
    path_segment_count: int
    path_row_count: int
    slug_like_row_count: int
    path_names: tuple[str, ...]
    segments_preview: tuple[str, ...]


class RuntimeTracePlan(msgspec.Struct, frozen=True):
    source: str
    path_segments: tuple[SegmentTraceHint, ...]
    slug_like_segments: tuple[SegmentTraceHint, ...]
    best_path_levels: tuple[LevelTraceHint, ...]
    best_garbage_levels: tuple[LevelTraceHint, ...]
    best_salt_levels: tuple[LevelTraceHint, ...]
    best_slug_like_levels: tuple[LevelTraceHint, ...]


def load_runtime_trace(path: Path) -> tuple[RuntimeTraceEvent, ...]:
    events: list[RuntimeTraceEvent] = []

    for line_number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), start=1):
        if not line.strip():
            continue
        raw = msgspec.json.decode(line)
        try:
            events.append(msgspec.convert(raw, type=RuntimeTraceEvent, strict=False))
        except msgspec.ValidationError as exc:
            raise ValueError(f"Invalid runtime trace event on line {line_number}: {exc}") from exc

    return tuple(events)


def summarize_runtime_trace(
    events: tuple[RuntimeTraceEvent, ...],
    *,
    source: str,
    preview_limit: int = 8,
) -> RuntimeTraceSummary:
    event_counts = Counter(event.event for event in events)
    levels = tuple(
        LevelRuntimeSample(
            seq=event.seq,
            selected_track_id=event.selected_track_id,
            garbage_scalar=event.garbage_scalar,
            salt_scalar=event.salt_scalar,
            active_level=event.active_level,
        )
        for event in events
        if event.event == "level_start"
    )

    path_name_counts: Counter[str] = Counter()
    path_index_counts: Counter[int] = Counter()
    path_index_names: dict[int, set[str]] = defaultdict(set)
    for event in events:
        if event.event != "path_lookup":
            continue
        if event.path_name:
            path_name_counts[event.path_name] += 1
        if event.path_index is not None and event.path_index >= 0:
            path_index_counts[event.path_index] += 1
            if event.path_name:
                path_index_names[event.path_index].add(event.path_name)

    return RuntimeTraceSummary(
        source=source,
        total_events=len(events),
        event_counts=dict(sorted(event_counts.items())),
        levels=levels,
        path_lookups_by_name=dict(sorted(path_name_counts.items())),
        path_lookups_by_index=tuple(
            PathIndexSummary(
                path_index=path_index,
                count=path_index_counts[path_index],
                names=tuple(sorted(path_index_names[path_index])),
            )
            for path_index in sorted(path_index_counts)
        ),
        attachment_probes=_summarize_bucket(
            (event for event in events if event.event == "attachment_probe"),
            preview_limit=preview_limit,
        ),
        attachment_begins=_summarize_bucket(
            (event for event in events if event.event == "attachment_begin"),
            preview_limit=preview_limit,
        ),
        garbage_spawns=_summarize_bucket(
            (event for event in events if event.event == "garbage_spawn"),
            preview_limit=preview_limit,
        ),
        salt_spawns=_summarize_bucket(
            (event for event in events if event.event == "salt_spawn"),
            preview_limit=preview_limit,
        ),
        slug_spawns=_summarize_bucket(
            (event for event in events if event.event == "slug_spawn"),
            preview_limit=preview_limit,
        ),
    )


def summarize_runtime_trace_file(path: Path, *, preview_limit: int = 8) -> RuntimeTraceSummary:
    events = load_runtime_trace(path)
    return summarize_runtime_trace(events, source=path.resolve().as_posix(), preview_limit=preview_limit)


def build_trace_capture_plan(extracted_root: Path, *, limit: int = 8) -> RuntimeTracePlan:
    root = extracted_root.resolve()
    segment_root = root / "SEGMENTS"
    level_root = root / "LEVELS"

    segment_defs: dict[str, tuple[SegmentDefinition, SegmentTraceHint]] = {}
    for path in sorted(segment_root.glob("*.TXT")):
        parsed = parse_text_asset(path, kind="segment")
        if not isinstance(parsed, SegmentDefinition):
            raise TypeError(f"Expected segment definition for {path}")
        hint = _build_segment_hint(path, parsed)
        segment_defs[path.name.lower()] = (parsed, hint)

    level_hints: list[LevelTraceHint] = []
    for path in sorted(level_root.glob("*.TXT")):
        parsed = parse_text_asset(path, kind="level")
        if not isinstance(parsed, LevelDefinition):
            raise TypeError(f"Expected level definition for {path}")
        level_hints.append(_build_level_hint(path, parsed, segment_defs))

    path_segments = sorted(
        (hint for _, hint in segment_defs.values() if hint.path_rows > 0),
        key=lambda hint: (-hint.path_rows, -hint.slug_like_rows, hint.name.lower()),
    )
    slug_like_segments = sorted(
        (hint for _, hint in segment_defs.values() if hint.slug_like_rows > 0),
        key=lambda hint: (-hint.slug_like_rows, -hint.path_rows, hint.name.lower()),
    )
    best_path_levels = sorted(
        (hint for hint in level_hints if hint.path_row_count > 0),
        key=lambda hint: (-hint.path_row_count, -hint.path_segment_count, hint.path.lower()),
    )
    best_garbage_levels = sorted(
        (hint for hint in level_hints if (hint.garbage or 0) > 0),
        key=lambda hint: (-(hint.garbage or 0), -hint.path_row_count, hint.path.lower()),
    )
    best_salt_levels = sorted(
        (hint for hint in level_hints if (hint.salt or 0) > 0),
        key=lambda hint: (-(hint.salt or 0), -hint.path_row_count, hint.path.lower()),
    )
    best_slug_like_levels = sorted(
        (hint for hint in level_hints if hint.slug_like_row_count > 0),
        key=lambda hint: (-hint.slug_like_row_count, -hint.path_row_count, hint.path.lower()),
    )

    return RuntimeTracePlan(
        source=root.as_posix(),
        path_segments=tuple(path_segments[:limit]),
        slug_like_segments=tuple(slug_like_segments[:limit]),
        best_path_levels=tuple(best_path_levels[:limit]),
        best_garbage_levels=tuple(best_garbage_levels[:limit]),
        best_salt_levels=tuple(best_salt_levels[:limit]),
        best_slug_like_levels=tuple(best_slug_like_levels[:limit]),
    )


def _summarize_bucket(
    events: tuple[RuntimeTraceEvent, ...] | list[RuntimeTraceEvent] | object,
    *,
    preview_limit: int,
) -> TraceBucketSummary:
    rows: Counter[int] = Counter()
    tile_types: Counter[int] = Counter()
    attachment_kinds: Counter[int] = Counter()
    positions_preview: list[TraceVec3] = []
    count = 0

    for event in events:
        count += 1
        if event.cell is not None:
            if event.cell.row is not None:
                rows[event.cell.row] += 1
            if event.cell.tile_type is not None:
                tile_types[event.cell.tile_type] += 1
            if event.cell.attachment_kind is not None:
                attachment_kinds[event.cell.attachment_kind] += 1
            if event.cell.world is not None and len(positions_preview) < preview_limit:
                positions_preview.append(event.cell.world)
        elif event.position is not None and len(positions_preview) < preview_limit:
            positions_preview.append(event.position)

    return TraceBucketSummary(
        count=count,
        rows=dict(sorted(rows.items())),
        tile_types=dict(sorted(tile_types.items())),
        attachment_kinds=dict(sorted(attachment_kinds.items())),
        positions_preview=tuple(positions_preview),
    )


def _build_segment_hint(path: Path, segment: SegmentDefinition) -> SegmentTraceHint:
    path_names = sorted(
        {
            row.annotation.value
            for row in segment.rows
            if row.annotation is not None and row.annotation.key == "Path" and row.annotation.value is not None
        }
    )
    path_rows = sum(1 for row in segment.rows if row.annotation is not None and row.annotation.key == "Path")
    slug_like_rows = sum(1 for row in segment.rows if "M" in row.cells)
    no_fall_rows = sum(
        1
        for row in segment.rows
        if row.annotation is not None and row.annotation.key.replace(" ", "").lower() == "nofall"
    )
    jetpack_off_rows = sum(
        1
        for row in segment.rows
        if row.annotation is not None
        and row.annotation.key.lower() == "jetpack"
        and (row.annotation.value or "").strip().lower() == "off"
    )

    return SegmentTraceHint(
        path=path.resolve().as_posix(),
        name=segment.name,
        path_rows=path_rows,
        path_names=tuple(path_names),
        slug_like_rows=slug_like_rows,
        no_fall_rows=no_fall_rows,
        jetpack_off_rows=jetpack_off_rows,
    )


def _build_level_hint(
    path: Path,
    level: LevelDefinition,
    segment_defs: dict[str, tuple[SegmentDefinition, SegmentTraceHint]],
) -> LevelTraceHint:
    referenced_segment_names = _referenced_segment_names(level)
    segment_hints: list[SegmentTraceHint] = []

    for segment_name in referenced_segment_names:
        entry = segment_defs.get(segment_name.lower())
        if entry is not None:
            segment_hints.append(entry[1])

    path_names = sorted({name for hint in segment_hints for name in hint.path_names})
    return LevelTraceHint(
        path=path.resolve().as_posix(),
        name=level.name,
        mode=level.mode,
        garbage=level.garbage,
        salt=level.salt,
        segment_count=len(segment_hints),
        path_segment_count=sum(1 for hint in segment_hints if hint.path_rows > 0),
        path_row_count=sum(hint.path_rows for hint in segment_hints),
        slug_like_row_count=sum(hint.slug_like_rows for hint in segment_hints),
        path_names=tuple(path_names),
        segments_preview=tuple(referenced_segment_names[:8]),
    )


def _referenced_segment_names(level: LevelDefinition) -> list[str]:
    names = list(level.first_segments)
    names.extend(entry.path for entry in level.segments)
    names.extend(level.last_segments)

    unique_names: list[str] = []
    seen: set[str] = set()
    for name in names:
        key = name.lower()
        if key not in seen:
            seen.add(key)
            unique_names.append(name)
    return unique_names
