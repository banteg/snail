from __future__ import annotations

from collections import Counter, defaultdict
from pathlib import Path
import re

import msgspec

from .formats import LevelDefinition, SegmentDefinition, parse_text_asset


SEGMENT_PATH_INDEX_NAMES: tuple[str, ...] = (
    "LOOPTHELOOP",
    "LOOPTHELOOP2",
    "LOOPTHELOOP4",
    "LOOPTHELOOPT2",
    "LOOPTHELOOPT3",
    "LOOPTHELOOPT4",
    "LOOPTHELOOPW",
    "LOOPBOW",
    "HILL",
    "HILL4C",
    "HILL4",
    "VALLEY",
    "VALLEY4C",
    "VALLEY4",
    "SBEND",
    "CAGE2",
    "HUMP",
    "DUMP",
    "HUMPSMALL",
    "DUMPSMALL",
    "DIP",
    "SCREW",
    "SLALOM",
    "SLALOMBIG",
    "WORM",
    "LOOPOUT",
    "LOOPOUT3",
    "LOOPOUTBIG",
    "SWEEP",
    "SNAKE",
    "WARP",
    "SUPERTRAMP",
    "SLALOMDOUBLE",
    "P0",
    "P1",
    "P2",
    "START",
    "TURNOVER",
    "TURNOVERDOUBLE",
    "TURNUNDER",
    "WIBBLE",
    "INVERT",
    "HALFPIPE",
    "TWISTERA",
    "TWISTERB",
    "TWISTER2A",
    "TWISTER2B",
    "TOAD0",
    "TOAD1",
    "TOADPAIR0",
    "TOADPAIR1",
)
PATH_NAME_PREFIX_RE = re.compile(r"^[A-Za-z][A-Za-z0-9]*")


class TraceVec3(msgspec.Struct, frozen=True):
    x: float | None
    y: float | None
    z: float | None


class TraceCell(msgspec.Struct, frozen=True):
    ptr: str | None = None
    storage: str | None = None
    row: int | None = None
    lane: int | None = None
    flags: int | None = None
    tile_type: int | None = None
    floor_height: float | None = None
    row_scalar_a: float | None = None
    row_scalar_b: float | None = None
    payload: int | None = None
    world: TraceVec3 | None = None
    attachment: str | None = None
    attachment_kind: int | None = None


class TraceTemplate(msgspec.Struct, frozen=True):
    ptr: str | None = None
    header_30: float | None = None
    header_34: float | None = None
    kind: int | None = None
    mirror_or_variant: int | None = None
    terminal_flag: int | None = None
    sample_count: int | None = None
    sample_count_f32: float | None = None
    width_or_scale: float | None = None
    subdivision_count: int | None = None
    primary_points: str | None = None
    secondary_points: str | None = None
    sample_delta: TraceVec3 | None = None
    sample_length: float | None = None
    row_scalar_a: float | None = None
    row_scalar_b: float | None = None
    row_scalar_c: float | None = None
    row_scalar_d: float | None = None


class TraceFollowState(msgspec.Struct, frozen=True):
    ptr: str | None = None
    active: bool | None = None
    template: str | None = None
    template_summary: TraceTemplate | None = None
    cell: TraceCell | None = None
    sample_index: int | None = None
    progress: float | None = None
    offset_y: float | None = None
    orientation: TraceVec3 | None = None
    output_position: TraceVec3 | None = None
    player: str | None = None


class RuntimeTraceEvent(msgspec.Struct, frozen=True):
    ts_ms: int
    pid: int
    tid: int
    event: str
    seq: int | None = None
    game: str | None = None
    level_descriptor: str | None = None
    retval: int | None = None
    mode_before: int | None = None
    mode_after: int | None = None
    active_level_flag_0: int | None = None
    active_level_flag_1: int | None = None
    active_level_present: bool | None = None
    selected_track_id: int | None = None
    active_level: str | None = None
    build_flags: int | None = None
    track_row_start: int | None = None
    track_row_end: int | None = None
    garbage_scalar: float | None = None
    salt_scalar: float | None = None
    path_name: str | None = None
    path_name_raw: str | None = None
    path_name_sanitized: str | None = None
    path_name_from_index: str | None = None
    path_index: int | None = None
    template: str | None = None
    template_summary: TraceTemplate | None = None
    before_template: str | None = None
    before_template_summary: TraceTemplate | None = None
    follow_state: str | None = None
    follow_state_summary: TraceFollowState | None = None
    before_follow_state: str | None = None
    before_follow_state_summary: TraceFollowState | None = None
    attachment_active: bool | None = None
    attachment_active_before: bool | None = None
    follow_sample_index: int | None = None
    before_follow_sample_index: int | None = None
    follow_progress: float | None = None
    before_follow_progress: float | None = None
    player: str | None = None
    slot: str | None = None
    state: int | None = None
    movement_state: int | None = None
    movement_flag_selector: int | None = None
    movement_flags: int | None = None
    previous_movement_flags: int | None = None
    movement_rate_scalar: float | None = None
    movement_mode_selector: int | None = None
    attachment_exit_pending: bool | None = None
    attachment_exit_anchor_z: float | None = None
    post_follow_value_a: float | None = None
    post_follow_value_b: float | None = None
    attachment_exit_progress: float | None = None
    attachment_exit_progress_step: float | None = None
    follow_effect_gate_a: bool | None = None
    follow_effect_gate_b: bool | None = None
    pair_payload: float | None = None
    pair_cell_a: TraceCell | None = None
    pair_cell_b: TraceCell | None = None
    slot_manager: str | None = None
    slot_result: int | None = None
    manager: str | None = None
    manager_sprite_bank: str | None = None
    sprite_id: int | None = None
    effect_kind: int | None = None
    effect_scale: float | None = None
    position: TraceVec3 | None = None
    before_position: TraceVec3 | None = None
    velocity: TraceVec3 | None = None
    player_position: TraceVec3 | None = None
    cell: TraceCell | None = None
    before_cell: TraceCell | None = None
    raw_cell: TraceCell | None = None
    before_raw_cell: TraceCell | None = None
    hooks: dict[str, bool] | None = None
    module: str | None = None
    module_base: str | None = None
    module_path: str | None = None
    target_module: str | None = None
    limit: int | None = None


class LevelRuntimeSample(msgspec.Struct, frozen=True):
    seq: int | None = None
    mode_before: int | None = None
    mode_after: int | None = None
    active_level_flag_0: int | None = None
    active_level_flag_1: int | None = None
    active_level_present: bool | None = None
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
    level_modes: dict[int, int]
    levels: tuple[LevelRuntimeSample, ...]
    path_lookups_by_name: dict[str, int]
    path_lookups_by_index: tuple[PathIndexSummary, ...]
    player_updates: TraceBucketSummary
    attachment_probes: TraceBucketSummary
    attachment_begins: TraceBucketSummary
    attachment_updates: TraceBucketSummary
    attachment_ends: TraceBucketSummary
    garbage_spawns: TraceBucketSummary
    health_pickups: TraceBucketSummary
    jetpack_pickups: TraceBucketSummary
    ring_effects: TraceBucketSummary
    salt_spawns: TraceBucketSummary
    salt_updates: TraceBucketSummary
    salt_deactivations: TraceBucketSummary
    slug_spawns: TraceBucketSummary


class SegmentTraceHint(msgspec.Struct, frozen=True):
    path: str
    name: str
    path_rows: int
    path_names: tuple[str, ...]
    ring_rows: int
    ring_kinds: dict[str, int]
    salt_like_rows: int
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
    ring_row_count: int
    ring_kinds: dict[str, int]
    salt_like_row_count: int
    slug_like_row_count: int
    no_fall_row_count: int
    jetpack_off_row_count: int
    path_names: tuple[str, ...]
    segments_preview: tuple[str, ...]


class RuntimeTracePlan(msgspec.Struct, frozen=True):
    source: str
    path_segments: tuple[SegmentTraceHint, ...]
    ring_segments: tuple[SegmentTraceHint, ...]
    no_fall_segments: tuple[SegmentTraceHint, ...]
    jetpack_off_segments: tuple[SegmentTraceHint, ...]
    salt_segments: tuple[SegmentTraceHint, ...]
    slug_like_segments: tuple[SegmentTraceHint, ...]
    best_path_levels: tuple[LevelTraceHint, ...]
    best_ring_levels: tuple[LevelTraceHint, ...]
    best_no_fall_levels: tuple[LevelTraceHint, ...]
    best_jetpack_off_levels: tuple[LevelTraceHint, ...]
    best_garbage_levels: tuple[LevelTraceHint, ...]
    best_salt_levels: tuple[LevelTraceHint, ...]
    best_authored_salt_levels: tuple[LevelTraceHint, ...]
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
    level_modes: Counter[int] = Counter()
    levels = tuple(
        LevelRuntimeSample(
            seq=event.seq,
            mode_before=event.mode_before,
            mode_after=event.mode_after,
            active_level_flag_0=event.active_level_flag_0,
            active_level_flag_1=event.active_level_flag_1,
            active_level_present=event.active_level_present,
            selected_track_id=event.selected_track_id,
            garbage_scalar=event.garbage_scalar,
            salt_scalar=event.salt_scalar,
            active_level=event.active_level,
        )
        for event in events
        if event.event == "level_start"
    )
    for level in levels:
        mode = level.mode_after if level.mode_after is not None else level.mode_before
        if mode is not None:
            level_modes[mode] += 1

    path_name_counts: Counter[str] = Counter()
    path_index_counts: Counter[int] = Counter()
    path_index_names: dict[int, set[str]] = defaultdict(set)
    for event in events:
        if event.event != "path_lookup":
            continue
        preferred_path_name = _preferred_path_name(event)
        if preferred_path_name:
            path_name_counts[preferred_path_name] += 1
        if event.path_index is not None and event.path_index >= 0:
            path_index_counts[event.path_index] += 1
            if preferred_path_name:
                path_index_names[event.path_index].add(preferred_path_name)

    return RuntimeTraceSummary(
        source=source,
        total_events=len(events),
        event_counts=dict(sorted(event_counts.items())),
        level_modes=dict(sorted(level_modes.items())),
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
        player_updates=_summarize_bucket(
            (event for event in events if event.event == "player_update"),
            preview_limit=preview_limit,
        ),
        attachment_probes=_summarize_bucket(
            (event for event in events if event.event == "attachment_probe"),
            preview_limit=preview_limit,
        ),
        attachment_begins=_summarize_bucket(
            (event for event in events if event.event == "attachment_begin"),
            preview_limit=preview_limit,
        ),
        attachment_updates=_summarize_bucket(
            (event for event in events if event.event == "attachment_update"),
            preview_limit=preview_limit,
        ),
        attachment_ends=_summarize_bucket(
            (event for event in events if event.event == "attachment_end"),
            preview_limit=preview_limit,
        ),
        garbage_spawns=_summarize_bucket(
            (event for event in events if event.event == "garbage_spawn"),
            preview_limit=preview_limit,
        ),
        health_pickups=_summarize_bucket(
            (event for event in events if event.event == "health_pickup"),
            preview_limit=preview_limit,
        ),
        jetpack_pickups=_summarize_bucket(
            (event for event in events if event.event == "jetpack_pickup"),
            preview_limit=preview_limit,
        ),
        ring_effects=_summarize_bucket(
            (event for event in events if event.event == "ring_effect"),
            preview_limit=preview_limit,
        ),
        salt_spawns=_summarize_bucket(
            (event for event in events if event.event == "salt_spawn"),
            preview_limit=preview_limit,
        ),
        salt_updates=_summarize_bucket(
            (event for event in events if event.event == "salt_update"),
            preview_limit=preview_limit,
        ),
        salt_deactivations=_summarize_bucket(
            (event for event in events if event.event == "salt_deactivate"),
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


def _preferred_path_name(event: RuntimeTraceEvent) -> str | None:
    if event.path_name_from_index:
        return event.path_name_from_index
    if event.path_name_sanitized:
        return event.path_name_sanitized
    if event.path_index is not None:
        canonical = _canonical_path_name_from_index(event.path_index)
        if canonical is not None:
            return canonical
    return _sanitize_path_name(event.path_name_raw or event.path_name)


def _canonical_path_name_from_index(path_index: int) -> str | None:
    if 0 <= path_index < len(SEGMENT_PATH_INDEX_NAMES):
        return SEGMENT_PATH_INDEX_NAMES[path_index]
    return None


def _sanitize_path_name(value: str | None) -> str | None:
    if value is None:
        return None
    match = PATH_NAME_PREFIX_RE.match(value)
    return match.group(0) if match is not None else None


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
        key=lambda hint: (-hint.path_rows, -hint.salt_like_rows, -hint.slug_like_rows, hint.name.lower()),
    )
    ring_segments = sorted(
        (hint for _, hint in segment_defs.values() if hint.ring_rows > 0),
        key=lambda hint: (
            -hint.ring_rows,
            -len(hint.ring_kinds),
            -sum(count for kind, count in hint.ring_kinds.items() if kind not in {"None", "Normal"}),
            hint.name.lower(),
        ),
    )
    no_fall_segments = sorted(
        (hint for _, hint in segment_defs.values() if hint.no_fall_rows > 0),
        key=lambda hint: (-hint.no_fall_rows, -hint.slug_like_rows, hint.name.lower()),
    )
    jetpack_off_segments = sorted(
        (hint for _, hint in segment_defs.values() if hint.jetpack_off_rows > 0),
        key=lambda hint: (-hint.jetpack_off_rows, -hint.path_rows, hint.name.lower()),
    )
    salt_segments = sorted(
        (hint for _, hint in segment_defs.values() if hint.salt_like_rows > 0),
        key=lambda hint: (-hint.salt_like_rows, -hint.path_rows, hint.name.lower()),
    )
    slug_like_segments = sorted(
        (hint for _, hint in segment_defs.values() if hint.slug_like_rows > 0),
        key=lambda hint: (-hint.slug_like_rows, -hint.salt_like_rows, -hint.path_rows, hint.name.lower()),
    )
    best_path_levels = sorted(
        (hint for hint in level_hints if hint.path_row_count > 0),
        key=lambda hint: (-hint.path_row_count, -hint.path_segment_count, hint.path.lower()),
    )
    best_ring_levels = sorted(
        (hint for hint in level_hints if hint.ring_row_count > 0),
        key=lambda hint: (
            -hint.ring_row_count,
            -sum(count for kind, count in hint.ring_kinds.items() if kind not in {"None", "Normal"}),
            -hint.path_row_count,
            hint.path.lower(),
        ),
    )
    best_no_fall_levels = sorted(
        (hint for hint in level_hints if hint.no_fall_row_count > 0),
        key=lambda hint: (-hint.no_fall_row_count, -hint.slug_like_row_count, hint.path.lower()),
    )
    best_jetpack_off_levels = sorted(
        (hint for hint in level_hints if hint.jetpack_off_row_count > 0),
        key=lambda hint: (-hint.jetpack_off_row_count, -hint.no_fall_row_count, -hint.path_row_count, hint.path.lower()),
    )
    best_garbage_levels = sorted(
        (hint for hint in level_hints if (hint.garbage or 0) > 0),
        key=lambda hint: (-(hint.garbage or 0), -hint.path_row_count, hint.path.lower()),
    )
    best_salt_levels = sorted(
        (hint for hint in level_hints if (hint.salt or 0) > 0),
        key=lambda hint: (-(hint.salt or 0), -hint.path_row_count, hint.path.lower()),
    )
    best_authored_salt_levels = sorted(
        (hint for hint in level_hints if hint.salt_like_row_count > 0),
        key=lambda hint: (-hint.salt_like_row_count, -(hint.salt or 0), hint.path.lower()),
    )
    best_slug_like_levels = sorted(
        (hint for hint in level_hints if hint.slug_like_row_count > 0),
        key=lambda hint: (-hint.slug_like_row_count, -hint.path_row_count, hint.path.lower()),
    )

    return RuntimeTracePlan(
        source=root.as_posix(),
        path_segments=tuple(path_segments[:limit]),
        ring_segments=tuple(ring_segments[:limit]),
        no_fall_segments=tuple(no_fall_segments[:limit]),
        jetpack_off_segments=tuple(jetpack_off_segments[:limit]),
        salt_segments=tuple(salt_segments[:limit]),
        slug_like_segments=tuple(slug_like_segments[:limit]),
        best_path_levels=tuple(best_path_levels[:limit]),
        best_ring_levels=tuple(best_ring_levels[:limit]),
        best_no_fall_levels=tuple(best_no_fall_levels[:limit]),
        best_jetpack_off_levels=tuple(best_jetpack_off_levels[:limit]),
        best_garbage_levels=tuple(best_garbage_levels[:limit]),
        best_salt_levels=tuple(best_salt_levels[:limit]),
        best_authored_salt_levels=tuple(best_authored_salt_levels[:limit]),
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
        if event.player_position is not None and len(positions_preview) < preview_limit:
            positions_preview.append(event.player_position)
        elif event.position is not None and len(positions_preview) < preview_limit:
            positions_preview.append(event.position)
        if event.cell is not None:
            if event.cell.row is not None:
                rows[event.cell.row] += 1
            if event.cell.tile_type is not None:
                tile_types[event.cell.tile_type] += 1
            if event.cell.attachment_kind is not None:
                attachment_kinds[event.cell.attachment_kind] += 1
            if event.cell.world is not None and len(positions_preview) < preview_limit:
                positions_preview.append(event.cell.world)

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
    ring_kinds = _collect_segment_ring_counts(segment)
    ring_rows = sum(ring_kinds.values())
    salt_like_rows = sum(1 for row in segment.rows if "&" in row.cells)
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
        ring_rows=ring_rows,
        ring_kinds=dict(sorted(ring_kinds.items())),
        salt_like_rows=salt_like_rows,
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
    ring_kinds: Counter[str] = Counter()
    for hint in segment_hints:
        ring_kinds.update(hint.ring_kinds)
    return LevelTraceHint(
        path=path.resolve().as_posix(),
        name=level.name,
        mode=level.mode,
        garbage=level.garbage,
        salt=level.salt,
        segment_count=len(segment_hints),
        path_segment_count=sum(1 for hint in segment_hints if hint.path_rows > 0),
        path_row_count=sum(hint.path_rows for hint in segment_hints),
        ring_row_count=sum(hint.ring_rows for hint in segment_hints),
        ring_kinds=dict(sorted(ring_kinds.items())),
        salt_like_row_count=sum(hint.salt_like_rows for hint in segment_hints),
        slug_like_row_count=sum(hint.slug_like_rows for hint in segment_hints),
        no_fall_row_count=sum(hint.no_fall_rows for hint in segment_hints),
        jetpack_off_row_count=sum(hint.jetpack_off_rows for hint in segment_hints),
        path_names=tuple(path_names),
        segments_preview=tuple(referenced_segment_names[:8]),
    )


def _referenced_segment_names(level: LevelDefinition) -> list[str]:
    names = list(level.first_segments)
    names.extend(entry.path for entry in level.segments)
    names.extend(level.last_segments)
    return names


def _collect_segment_ring_counts(segment: SegmentDefinition) -> Counter[str]:
    ring_kinds: Counter[str] = Counter()
    for row in segment.rows:
        annotation = row.annotation
        if annotation is None or annotation.key.lower() != "ring" or annotation.value is None:
            continue
        ring_kinds[_canonicalize_ring_kind(annotation.value)] += 1
    return ring_kinds


def _canonicalize_ring_kind(value: str) -> str:
    normalized = value.strip().lower()
    if normalized == "powerup":
        return "PowerUp"
    if normalized in {"explode", "explosive"}:
        return "Explode"
    if normalized == "normal":
        return "Normal"
    if normalized == "slow":
        return "Slow"
    if normalized == "none":
        return "None"
    return value.strip()
