import importlib.util
import json
from pathlib import Path


BINJA_DIR = Path(__file__).parents[1] / "tools/binja"
IDA_DIR = Path(__file__).parents[1] / "tools/ida"
HEADER_DIR = Path(__file__).parents[1] / "analysis/headers"
MODULE_PATH = BINJA_DIR / "_narrow_sync.py"
MODULE_SPEC = importlib.util.spec_from_file_location("_narrow_sync", MODULE_PATH)
if MODULE_SPEC is None or MODULE_SPEC.loader is None:
    raise RuntimeError(f"unable to load {MODULE_PATH}")
_narrow_sync = importlib.util.module_from_spec(MODULE_SPEC)
MODULE_SPEC.loader.exec_module(_narrow_sync)


def test_binja_scripts_do_not_default_to_active_target() -> None:
    offenders = []
    for path in BINJA_DIR.glob("*.py"):
        source = path.read_text(encoding="utf-8")
        if 'default="active"' in source or 'TARGET = "active"' in source:
            offenders.append(path.name)

    assert offenders == []
    assert 'DEFAULT_TARGET = "SnailMail_unwrapped.exe.bndb"' in (
        BINJA_DIR / "_target.py"
    ).read_text(encoding="utf-8")


def test_parse_struct_layout_size() -> None:
    assert _narrow_sync.parse_struct_layout_size("struct Runtime // size=0x1272838") == 0x1272838
    assert _narrow_sync.parse_struct_layout_size("struct Tiny // size=1") == 1
    assert _narrow_sync.parse_struct_layout_size("struct Runtime") is None


def test_normalize_type_name_canonicalizes_array_dimensions() -> None:
    assert _narrow_sync.normalize_type_name(
        "struct TrackRowCell[0xc80][0x8]"
    ) == _narrow_sync.normalize_type_name("TrackRowCell[3200][8]")
    assert _narrow_sync.normalize_type_name(
        "struct PathPair[0x3f]"
    ) == _narrow_sync.normalize_type_name("PathPair[63]")


def test_normalize_prototype_treats_default_cdecl_as_equivalent() -> None:
    assert _narrow_sync.normalize_prototype(
        "void()", identifier="initialize_global_identity_matrix"
    ) == _narrow_sync.normalize_prototype(
        "void __cdecl initialize_global_identity_matrix()",
        identifier="initialize_global_identity_matrix",
    )


def test_current_struct_size_reads_layout(monkeypatch) -> None:
    monkeypatch.setattr(
        _narrow_sync,
        "run_bn",
        lambda *_args, **_kwargs: {
            "layout": "struct Sprite // size=0xb4\n0x0000: void* object_ref",
        },
    )

    assert (
        _narrow_sync.current_struct_size(
            Path("."), target="snail-mail.exe", struct_name="Sprite"
        )
        == 0xB4
    )


def test_current_type_widths_batches_readback(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {"result": {"Sprite": 0xB4, "TextureRef": None}}

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    assert _narrow_sync.current_type_widths(
        Path("."),
        target="snail-mail.exe",
        type_names=("Sprite", "TextureRef"),
    ) == {"Sprite": 0xB4, "TextureRef": None}
    assert len(calls) == 1
    assert calls[0][:2] == ("py", "exec")


def test_current_struct_fields_batch_reads_all_layouts(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {
            "result": {
                "SubgameRuntime": [
                    {
                        "offset": 0x3BFAC8,
                        "name": "runtime_cells",
                        "type": "struct TrackRowCell[0xc80][0x8]",
                    }
                ],
                "Player": [
                    {
                        "offset": 0x408,
                        "name": "game",
                        "type": "struct SubgameRuntime*",
                    }
                ],
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    assert _narrow_sync.current_struct_fields_batch(
        Path("."),
        target="snail-mail.exe",
        struct_names=("SubgameRuntime", "Player"),
    ) == {
        "SubgameRuntime": {0x3BFAC8: ("runtime_cells", "TrackRowCell[3200][8]")},
        "Player": {0x408: ("game", "SubgameRuntime*")},
    }
    assert len(calls) == 1
    assert calls[0][:2] == ("py", "exec")
    assert "current.members" in calls[0][-1]


def test_current_prototypes_batches_readback(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {
            "result": {
                "reset_subgame": "void __thiscall(struct SubgameRuntime* game)",
                "0x437eb0": None,
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    assert _narrow_sync.current_prototypes(
        Path("."),
        target="snail-mail.exe",
        identifiers=("reset_subgame", "0x437eb0"),
    ) == {
        "reset_subgame": "void __thiscall(struct SubgameRuntime* game)",
        "0x437eb0": None,
    }
    assert len(calls) == 1
    assert calls[0][:2] == ("py", "exec")
    assert "get_functions_by_name" in calls[0][-1]
    assert "get_function_at" in calls[0][-1]


def test_current_symbol_names_batches_readback(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {
            "result": {
                "0x4086d0": "initialize_player_presentation_controller",
                "old_symbol": None,
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    assert _narrow_sync.current_symbol_names(
        Path("."),
        target="snail-mail.exe",
        identifiers=("0x4086d0", "old_symbol"),
    ) == {
        "0x4086d0": "initialize_player_presentation_controller",
        "old_symbol": None,
    }
    assert len(calls) == 1
    assert calls[0][:2] == ("py", "exec")
    assert "get_symbol_at" in calls[0][-1]
    assert "get_symbols_by_name" in calls[0][-1]


def test_data_var_updates_skip_current_types(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {
            "result": [
                {
                    "address": "0x4ac5c8",
                    "requested_type": "TipData",
                    "before_type": "struct TipData",
                    "after_type": "struct TipData",
                    "changed": False,
                }
            ]
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    assert _narrow_sync.apply_data_var_updates(
        Path("."),
        target="snail-mail.exe",
        updates=(("0x4ac5c8", "TipData"),),
    ) == [
        {
            "op": "data_var_set",
            "address": "0x4ac5c8",
            "type": "TipData",
            "before_type": "struct TipData",
            "after_type": "struct TipData",
            "status": "skipped",
            "reason": "already current",
        }
    ]
    assert len(calls) == 1
    assert "if changed:" in calls[0][-1]


def test_run_bn_reads_failure_spill_before_raising(monkeypatch, tmp_path) -> None:
    spill_path = tmp_path / "batch-failure.json"
    spill_path.write_text(
        json.dumps(
            {
                "success": False,
                "preview": True,
                "committed": False,
                "message": "Preview verified and reverted.",
                "results": [
                    {
                        "op": "struct_field_set",
                        "status": "verified",
                        "struct_name": "SubgameRuntime",
                        "field_name": "runtime_cells",
                    },
                    {
                        "op": "set_prototype",
                        "status": "verification_failed",
                        "function": "initialize_subgame",
                        "address": "0x4374b0",
                        "before_prototype": "void __fastcall(struct Game* game)",
                        "expected_prototype": (
                            "void __thiscall(struct SubgameRuntime* game)"
                        ),
                        "message": "Live prototype verification failed at 0x4374b0",
                    },
                ],
            }
        ),
        encoding="utf-8",
    )
    monkeypatch.setattr(
        _narrow_sync.subprocess,
        "run",
        lambda *_args, **_kwargs: _narrow_sync.subprocess.CompletedProcess(
            args=["bn", "batch", "apply"],
            returncode=1,
            stdout=f"path: {spill_path}\n",
            stderr="",
        ),
    )

    try:
        _narrow_sync.run_bn(Path("."), "batch", "apply")
    except RuntimeError as error:
        message = str(error)
        assert str(spill_path) in message
        assert "initialize_subgame" in message
        assert "SubgameRuntime" in message
        assert "runtime_cells" not in message
    else:
        raise AssertionError("failed spilled mutation was accepted")


def test_struct_exists_rejects_forward_declaration(monkeypatch) -> None:
    monkeypatch.setattr(
        _narrow_sync,
        "run_bn",
        lambda *_args, **_kwargs: {
            "layout": "struct SubgameRuntime // size=0x0",
        },
    )

    assert not _narrow_sync.struct_exists(
        Path("."), target="snail-mail.exe", struct_name="SubgameRuntime"
    )


def test_struct_exists_accepts_complete_layout(monkeypatch) -> None:
    monkeypatch.setattr(
        _narrow_sync,
        "run_bn",
        lambda *_args, **_kwargs: {
            "layout": "struct SubgameRuntime // size=0x1272838\n0x0000: uint8_t state",
        },
    )

    assert _narrow_sync.struct_exists(
        Path("."), target="snail-mail.exe", struct_name="SubgameRuntime"
    )


def test_star_manager_sync_selectively_repairs_sprite_prerequisites() -> None:
    source = (BINJA_DIR / "sync_star_manager_types.py").read_text(encoding="utf-8")

    assert "types_declare_missing_only" in source
    assert "current_struct_size" in source
    assert '"Sprite": 0xB4' in source
    assert "types_declare(" not in source


def test_path_sync_owns_core_subgame_receiver_abis() -> None:
    source = (BINJA_DIR / "sync_path_template_types.py").read_text(encoding="utf-8")

    assert "CORE_SUBGAME_PROTO_UPDATES" in source
    assert "DEFERRED_SUBGAME_OWNER_PROTO_UPDATES" in source
    assert "proto_owner_deferred" in source
    assert "apply_struct_and_proto_updates" in source
    assert "apply_direct_proto_update" not in source
    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"' in source
    assert '"RingOrSpecialEffectPool"' not in source
    assert '"SubSpeedUp"' not in source
    assert '"SaltHazardSlot"' not in source
    stable_prototypes = source.split("CORE_SUBGAME_PROTO_UPDATES = (", 1)[1].split(
        "\n)\n\n# These five receivers", 1
    )[0]
    deferred_prototypes = source.split(
        "DEFERRED_SUBGAME_OWNER_PROTO_UPDATES = (", 1
    )[1].split("\n)\n\n\ndef report_deferred", 1)[0]
    for function_name in ("reset_subgame", "complete_subgame"):
        assert f'"{function_name}"' in stable_prototypes
    for function_name in (
        "initialize_subgame",
        "build_subgame_level",
        "destroy_subgame",
        "update_subgame",
        "remove_subgame_bods",
        "get_track_runtime_cell_at_world_z",
    ):
        assert f'"{function_name}"' in deferred_prototypes


def test_animation_ownership_stays_aligned_across_replay_lanes() -> None:
    binja_source = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    object_header = (HEADER_DIR / "object_render_types.h").read_text(
        encoding="utf-8"
    )
    path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )

    for source in (binja_source, ida_source):
        assert "set_weapon_animation" in source
        assert "dispatch_cutscene_animation" in source
        assert "int32_t mode_flags" in source
        assert "initial_frame" not in source

    for header in (object_header, path_header):
        assert "typedef enum ObjectAnimationFlag" in header
        assert "typedef enum ObjectAnimationModeOverride" in header
        assert "ObjectAnimationFlags flags;" in header
        assert "ObjectAnimationFrame** frames;" in header


def test_sub_loc_flag_ownership_stays_aligned_across_replay_lanes() -> None:
    repo_root = Path(__file__).parents[1]
    binja_source = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/track_attachment_types.h"
    ).read_text(encoding="utf-8")
    tile_view_header = (
        repo_root / "tools/match/include/track_row_cell_tile_views.h"
    ).read_text(encoding="utf-8")

    assert '("0x3d", "open_edge_mask", "uint8_t")' in binja_source
    assert '"SubLocOpenEdgeFlag",' in binja_source
    assert '"SubLocFlag",' in binja_source
    for header in (analysis_header, matcher_header):
        assert "SUBLOC_OPEN_PREVIOUS_ROW = 0x01" in header
        assert "SUBLOC_OPEN_NEXT_ROW = 0x02" in header
        assert "SUBLOC_FLAG_RANDOM_HAZARD_BLOCKED = 0x0018" in header
        assert "SUBLOC_FLAG_WARNING_CACHE_FAMILY = 0x0020" in header
        assert "SUBLOC_FLAG_CACHE_FAMILY_SWAPPED = 0x0040" in header
        assert "SUBLOC_MERGED_RUN_WIDTH_MASK = 0x0f00" in header
        assert "SUBLOC_FLAG_AI_ENABLED = 0x2000" in header
        assert "SUBLOC_FLAG_UNCACHED_BODY = 0x4000" in header
        assert "SUBLOC_FLAG_CORNER_OBJECT = 0x8000" in header
        assert "open_edge_mask" in header
        assert "tile_flags_3d" not in header

    assert "open_edge_mask" in tile_view_header
    assert "tile_flags_3d" not in tile_view_header


def test_sub_row_flag_ownership_stays_aligned_across_replay_lanes() -> None:
    repo_root = Path(__file__).parents[1]
    binja_source = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    analysis_segment_header = (HEADER_DIR / "segment_catalog_types.h").read_text(
        encoding="utf-8"
    )
    matcher_row_header = (
        repo_root / "tools/match/include/track_attachment_types.h"
    ).read_text(encoding="utf-8")
    matcher_segment_header = (
        repo_root / "tools/match/include/segment_catalog_types.h"
    ).read_text(encoding="utf-8")

    assert '"AuthoredSegmentRowFlag",' in binja_source
    assert '"SubRowFlag",' in binja_source

    for header in (
        analysis_path_header,
        analysis_segment_header,
        matcher_segment_header,
    ):
        assert "AUTHORED_SEGMENT_ROW_FLAG_PARCEL = 0x0001" in header
        assert "AUTHORED_SEGMENT_ROW_FLAG_STAR_MARKER = 0x0004" in header
        assert (
            "AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY = 0x0008" in header
        )
        assert "AUTHORED_SEGMENT_ROW_FLAG_NO_FALL = 0x0100" in header
        assert "AUTHORED_SEGMENT_ROW_FLAG_RING_POWER_UP = 0x2000" in header
        assert "AUTHORED_SEGMENT_ROW_FLAG_JETPACK_OFF = 0x8000" in header

    for header in (analysis_path_header, matcher_row_header):
        assert "SUBROW_FLAG_PARCEL_CANDIDATE = 0x0001" in header
        assert "SUBROW_FLAG_SUPPRESS_TRACK_RENDER = 0x0004" in header
        assert "SUBROW_FLAG_PATH_OR_MODEL_VELOCITY = 0x0008" in header
        assert "SUBROW_FLAG_PARCEL_SPAWN_REQUESTED = 0x0010" in header
        assert "SUBROW_ATTACHMENT_MASK = 0x00c0" in header
        assert "SUBROW_FLAG_NO_FALL = 0x0100" in header
        assert "SUBROW_FLAG_PARCEL_Z_IS_LOCAL = 0x4000" in header
        assert "SUBROW_FLAG_JETPACK_OFF = 0x8000" in header

    load_segment = (
        repo_root / "tools/match/scratches/load_segment_definitions/scratch.cpp"
    ).read_text(encoding="utf-8")
    update_subgoldy = (
        repo_root / "tools/match/scratches/update_subgoldy/scratch.cpp"
    ).read_text(encoding="utf-8")
    place_challenge = (
        repo_root
        / "tools/match/scratches/place_challenge_parcels_on_track/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY" in load_segment
    assert "SUBROW_FLAG_NO_FALL" in update_subgoldy
    assert "SUBROW_FLAG_PARCEL_Z_IS_LOCAL" in place_challenge


def test_subgame_runtime_flag_ownership_stays_aligned_across_replay_lanes() -> None:
    repo_root = Path(__file__).parents[1]
    binja_source = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in (
            "path_template_types.h",
            "bn_subgame_runtime_types.h",
            "ida_subgame_runtime_types.h",
        )
    )
    matcher_header = (repo_root / "tools/match/include/subgame_runtime.h").read_text(
        encoding="utf-8"
    )

    assert '"SubgameRuntimeFlag",' in binja_source
    assert '"SubgameRuntimeFlagPreset",' in binja_source
    for header in (*analysis_headers, matcher_header):
        assert "SUBGAME_RUNTIME_FLAG_AMBIENT_GARBAGE = 0x000002" in header
        assert "SUBGAME_RUNTIME_FLAG_DEFAULT_RAMP_RINGS = 0x000008" in header
        assert "SUBGAME_RUNTIME_FLAG_RING_LIFE_REWARD = 0x000010" in header
        assert "SUBGAME_RUNTIME_FLAG_SLUG_HAZARDS = 0x000080" in header
        assert "SUBGAME_RUNTIME_FLAG_ALLOW_FALLING = 0x000400" in header
        assert "SUBGAME_RUNTIME_FLAG_HEALTH_PICKUPS = 0x000800" in header
        assert "SUBGAME_RUNTIME_FLAG_AMBIENT_SALT = 0x010000" in header
        assert "SUBGAME_RUNTIME_FLAG_MOVEMENT_FIRE_EMITTERS = 0x400000" in header
        assert "SUBGAME_RUNTIME_FLAG_PARCEL_SPAWNS = 0x800000" in header
        assert "SUBGAME_RUNTIME_FLAGS_POSTAL_CHALLENGE = 0xf5cfff" in header
        assert "SUBGAME_RUNTIME_FLAGS_TIME_TRIAL = 0x75cfff" in header
        assert "SUBGAME_RUNTIME_FLAGS_TUTORIAL = 0xe4cfff" in header
        assert "SUBGAME_RUNTIME_FLAGS_TUTORIAL_INIT_OR_MASK = 0x600000" in header

    consumers = {
        "set_subgame_features": "SUBGAME_RUNTIME_FLAGS_POSTAL_CHALLENGE",
        "normalize_segment_glyph_for_track_flags": (
            "SUBGAME_RUNTIME_FLAG_PRESERVE_RAMP_GLYPHS"
        ),
        "initialize_tutorial": "SUBGAME_RUNTIME_FLAG_AMBIENT_GARBAGE",
        "update_subgame": "SUBGAME_RUNTIME_FLAG_PARCEL_SPAWNS",
        "update_subgoldy": "SUBGAME_RUNTIME_FLAG_MOVEMENT_FIRE_EMITTERS",
        "handle_subgoldy_collisions": "SUBGAME_RUNTIME_FLAG_RING_LIFE_REWARD",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_sub_ring_kind_and_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    pool_sync = (BINJA_DIR / "sync_subgame_pool_types.py").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("bn_subgame_pool_types.h", "path_template_types.h")
    )
    matcher_header = (
        repo_root / "tools/match/include/ring_special_effect_types.h"
    ).read_text(encoding="utf-8")

    assert '"SubRingState",' in pool_sync
    assert '"SubRingKind",' in pool_sync
    assert '("0x80", "state", "SubRingState")' in pool_sync
    assert '("0x88", "kind", "SubRingKind")' in pool_sync
    assert "SubRingKind requested_kind" in pool_sync
    assert '"SubRingState",' in path_sync
    assert '"SubRingKind",' in path_sync

    for header in (*analysis_headers, matcher_header):
        assert "SUB_RING_STATE_INACTIVE = 0" in header
        assert "SUB_RING_STATE_COLLECT_PENDING = 2" in header
        assert "SUB_RING_STATE_EXPANDING = 5" in header
        assert "SUB_RING_KIND_UNKNOWN_0 = 0" in header
        assert "SUB_RING_KIND_UNKNOWN_1 = 1" in header
        assert "SUB_RING_KIND_EXPLODE_RAMP = 2" in header
        assert "SUB_RING_KIND_SLOW_DEFAULT = 3" in header
        assert "SUB_RING_KIND_NORMAL_DEFAULT = 4" in header
        assert "SUB_RING_KIND_NORMAL_AUTHORED = 5" in header
        assert "SUB_RING_KIND_EXPLODE_AUTHORED = 6" in header
        assert "SUB_RING_KIND_SLOW_AUTHORED = 7" in header
        assert "SUB_RING_KIND_POWER_UP_AUTHORED = 8" in header

    consumers = {
        "spawn_track_ring_or_special_effect": "SUB_RING_KIND_NORMAL_DEFAULT",
        "initialize_ring_or_special_effect_particles": (
            "SUB_RING_KIND_POWER_UP_AUTHORED"
        ),
        "update_ring_or_special_effect_particle": "SUB_RING_KIND_SLOW_DEFAULT",
        "update_ring_or_special_effect_parent": "SUB_RING_STATE_EXPANDING",
        "handle_subgoldy_collisions": "SUB_RING_STATE_COLLECT_PENDING",
        "update_subgame": "SUB_RING_KIND_EXPLODE_RAMP",
        "reset_subgame": "SUB_RING_STATE_INACTIVE",
        "remove_subgame_bods": "SUB_RING_STATE_INACTIVE",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_parcel_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    runtime_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in (
            "path_template_types.h",
            "bn_subgame_runtime_types.h",
            "ida_subgame_runtime_types.h",
        )
    )
    matcher_header = (
        repo_root / "tools/match/include/track_parcel_runtime.h"
    ).read_text(encoding="utf-8")

    assert '"ParcelState",' in runtime_sync
    assert '("0x38", "state", "ParcelState")' in runtime_sync
    assert '"ParcelState",' in path_sync
    for header in (*analysis_headers, matcher_header):
        assert "PARCEL_STATE_INACTIVE = 0" in header
        assert "PARCEL_STATE_TRACK_ACTIVE = 1" in header
        assert "PARCEL_STATE_UNKNOWN_2 = 2" in header
        assert "PARCEL_STATE_UNKNOWN_3 = 3" in header
        assert "PARCEL_STATE_COLLECT_PENDING = 4" in header
        assert "PARCEL_STATE_COLLECTING = 5" in header
        assert "PARCEL_STATE_DELIVERY_PENDING = 6" in header
        assert "PARCEL_STATE_DELIVERING = 7" in header

    consumers = {
        "update_track_parcels": "PARCEL_STATE_INACTIVE",
        "initialize_track_parcel_slots": "PARCEL_STATE_INACTIVE",
        "allocate_track_parcel_slot": "PARCEL_STATE_INACTIVE",
        "update_track_parcel": "PARCEL_STATE_UNKNOWN_2",
        "spawn_track_parcel": "PARCEL_STATE_TRACK_ACTIVE",
        "handle_subgoldy_collisions": "PARCEL_STATE_COLLECT_PENDING",
        "update_row_event_display": "PARCEL_STATE_DELIVERY_PENDING",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_completion_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    runtime_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in (
            "completion_screen_types.h",
            "path_template_types.h",
            "bn_subgame_runtime_types.h",
            "ida_subgame_runtime_types.h",
        )
    )
    matcher_header = (repo_root / "tools/match/include/completion.h").read_text(
        encoding="utf-8"
    )

    assert '"CompletionState",' in runtime_sync
    assert '("0x14", "state", "CompletionState")' in runtime_sync
    assert '"CompletionState",' in path_sync
    for header in (*analysis_headers, matcher_header):
        assert "COMPLETION_STATE_INACTIVE = 0" in header
        assert "COMPLETION_STATE_STAGING_PARCELS = 1" in header
        assert "COMPLETION_STATE_WAITING_FOR_DELIVERIES = 2" in header
        assert "COMPLETION_STATE_SUMMARY_PENDING = 3" in header
        assert "COMPLETION_STATE_SUMMARY_ACTIVE = 4" in header
        assert "COMPLETION_STATE_CONTINUE_ACCEPTED = 5" in header
        assert "COMPLETION_STATE_EMPTY_DELIVERY_DELAY = 6" in header

    consumers = {
        "initialize_completion_screen": "COMPLETION_STATE_STAGING_PARCELS",
        "flush_row_event_display": "COMPLETION_STATE_INACTIVE",
        "update_row_event_display": "COMPLETION_STATE_EMPTY_DELIVERY_DELAY",
        "register_parcel_delivery": "COMPLETION_STATE_SUMMARY_PENDING",
        "initialize_subgoldy": "COMPLETION_STATE_INACTIVE",
        "update_subgoldy": "COMPLETION_STATE_CONTINUE_ACCEPTED",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_times_up_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    runtime_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in (
            "path_template_types.h",
            "bn_subgame_runtime_types.h",
            "ida_subgame_runtime_types.h",
        )
    )
    matcher_header = (repo_root / "tools/match/include/times_up.h").read_text(
        encoding="utf-8"
    )

    assert '"TimesUpState",' in runtime_sync
    assert '("0x00", "state", "TimesUpState")' in runtime_sync
    assert '"TimesUpState",' in path_sync
    for header in (*analysis_headers, matcher_header):
        assert "TIMES_UP_STATE_INACTIVE = 0" in header
        assert "TIMES_UP_STATE_DISPLAYING = 1" in header
        assert "TIMES_UP_STATE_EXPIRED = 2" in header

    consumers = {
        "update_times_up": "TIMES_UP_STATE_EXPIRED",
        "uninit_times_up": "TIMES_UP_STATE_INACTIVE",
        "show_times_up_message": "TIMES_UP_STATE_DISPLAYING",
        "initialize_subgame": "TIMES_UP_STATE_INACTIVE",
        "build_subgame_level": "TIMES_UP_STATE_INACTIVE",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_track_pickup_state_and_authored_owners_stay_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    pool_sync = (BINJA_DIR / "sync_subgame_pool_types.py").read_text(
        encoding="utf-8"
    )
    runtime_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in (
            "bn_subgame_pool_types.h",
            "path_template_types.h",
            "bn_subgame_runtime_types.h",
            "ida_subgame_runtime_types.h",
        )
    )
    matcher_header = (
        repo_root / "tools/match/include/track_pickup_state.h"
    ).read_text(encoding="utf-8")

    assert '"TrackPickupState"' in pool_sync
    assert '("0x80", "state", "TrackPickupState")' in pool_sync
    assert pool_sync.count('("0x38", "state", "TrackPickupState")') == 2
    assert '("0x1c", "render_arg_1c", "float")' in pool_sync
    assert '("0x355db0", "speedup_pickup", "SubSpeedUp")' in pool_sync
    assert '("0x356000", "health_pickups", "SubHealth[0x8]")' in pool_sync
    assert 'struct_name="JetPack"' in runtime_sync
    assert '("0x38", "state", "TrackPickupState")' in runtime_sync
    assert '"TrackPickupState",' in path_sync
    for function_name in (
        "initialize_track_speedup_runtime",
        "update_track_speedup",
        "initialize_track_health_pickup_runtime",
        "update_track_health_pickup",
    ):
        assert function_name in pool_sync
        assert function_name in ida_sync

    for header in (*analysis_headers, matcher_header):
        assert "TRACK_PICKUP_STATE_INACTIVE = 0" in header
        assert "TRACK_PICKUP_STATE_ACTIVE = 1" in header
        assert "TRACK_PICKUP_STATE_TEARDOWN_PENDING = 2" in header

    pool_header, path_header, *_ = analysis_headers
    for header in (pool_header, path_header):
        assert "typedef struct SubSpeedUp" in header
        assert "typedef struct SubHealth" in header
        assert "typedef SubHealth TrackHealthPickup" in header

    consumers = {
        "reset_subgame": "TRACK_PICKUP_STATE_INACTIVE",
        "remove_subgame_bods": "TRACK_PICKUP_STATE_INACTIVE",
        "spawn_track_health_pickup": "TRACK_PICKUP_STATE_ACTIVE",
        "spawn_track_jetpack_pickup": "TRACK_PICKUP_STATE_ACTIVE",
        "update_track_speedup": "TRACK_PICKUP_STATE_TEARDOWN_PENDING",
        "update_track_health_pickup": "TRACK_PICKUP_STATE_TEARDOWN_PENDING",
        "update_track_jetpack_pickup": "TRACK_PICKUP_STATE_TEARDOWN_PENDING",
        "handle_subgoldy_collisions": "TRACK_PICKUP_STATE_TEARDOWN_PENDING",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_warning_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/warning.h").read_text(
        encoding="utf-8"
    )

    assert '"WarningState",' in path_sync
    assert '("0x00", "state", "WarningState")' in path_sync
    for header in (analysis_header, matcher_header):
        assert "WARNING_STATE_INACTIVE = 0" in header
        assert "WARNING_STATE_OPAQUE = 1" in header
        assert "WARNING_STATE_FADING = 2" in header

    consumers = {
        "initialize_warning": "WARNING_STATE_INACTIVE",
        "start_warning": "WARNING_STATE_FADING",
        "stop_warning": "WARNING_STATE_INACTIVE",
        "update_warning": "WARNING_STATE_OPAQUE",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_damage_guage_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/damage_guage.h"
    ).read_text(encoding="utf-8")

    assert '"DamageGuageState",' in path_sync
    assert '("0x00", "state", "DamageGuageState")' in path_sync
    for header in (analysis_header, matcher_header):
        assert "DAMAGE_GUAGE_STATE_MONITORING = 0" in header
        assert "DAMAGE_GUAGE_STATE_WARNING_TRANSITION = 1" in header
        assert "DAMAGE_GUAGE_STATE_DRAINING = 2" in header

    consumers = {
        "initialize_damage_gauge": "DAMAGE_GUAGE_STATE_MONITORING",
        "update_damage_gauge": "DAMAGE_GUAGE_STATE_WARNING_TRANSITION",
        "apply_damage_gauge_delta": "DAMAGE_GUAGE_STATE_DRAINING",
        "calc_subgame_rate": "DAMAGE_GUAGE_STATE_DRAINING",
        "update_subgoldy": "DAMAGE_GUAGE_STATE_DRAINING",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_invincible_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/invincible.h").read_text(
        encoding="utf-8"
    )

    assert '"InvincibleState",' in path_sync
    assert '("0x80", "state", "InvincibleState")' in path_sync
    for header in (analysis_header, matcher_header):
        assert "INVINCIBLE_STATE_INACTIVE = 0" in header
        assert "INVINCIBLE_STATE_FADING_IN = 1" in header
        assert "INVINCIBLE_STATE_ACTIVE = 2" in header
        assert "INVINCIBLE_STATE_FADING_OUT = 3" in header

    consumers = {
        "initialize_invincible_shell": "INVINCIBLE_STATE_INACTIVE",
        "start_invincible_shell": "INVINCIBLE_STATE_FADING_IN",
        "update_invincible_shell": "INVINCIBLE_STATE_ACTIVE",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_types_declare_if_missing_previews_then_selectively_applies(monkeypatch) -> None:
    calls = []

    monkeypatch.setattr(
        _narrow_sync,
        "current_type_widths",
        lambda *_args, **_kwargs: {"SubgameRuntime": None},
    )

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        if args[:3] == ("types", "declare", "--preview"):
            return {
                "success": True,
                "preview": True,
                "committed": False,
                "message": "Preview verified and reverted.",
                "affected_types": ["SubgameRuntime"],
                "affected_functions": [],
            }
        return {"result": {"applied": [{"name": "SubgameRuntime", "verified": True}]}}

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    result = _narrow_sync.types_declare_if_missing(
        Path("."),
        target="snail-mail.exe",
        header_path=Path("runtime_types.h"),
        required_structs=("SubgameRuntime",),
    )

    assert result["op"] == "types_declare_missing_only"
    assert result["missing_structs"] == ("SubgameRuntime",)
    assert result["include_types"] == ("SubgameRuntime",)
    assert calls[0][:3] == ("types", "declare", "--preview")
    assert calls[1][:2] == ("py", "exec")
    assert "define_user_type" in calls[1][-1]


def test_types_declare_if_missing_skips_complete_structs(monkeypatch) -> None:
    monkeypatch.setattr(
        _narrow_sync,
        "current_type_widths",
        lambda *_args, **_kwargs: {"SubgameRuntime": 0x1272838},
    )
    monkeypatch.setattr(
        _narrow_sync,
        "run_bn",
        lambda *_args, **_kwargs: (_ for _ in ()).throw(AssertionError("unexpected replay")),
    )

    result = _narrow_sync.types_declare_if_missing(
        Path("."),
        target="snail-mail.exe",
        header_path=Path("runtime_types.h"),
        required_structs=("SubgameRuntime",),
    )

    assert result["status"] == "skipped"


def test_types_declare_if_missing_rejects_header_without_requested_type(monkeypatch) -> None:
    monkeypatch.setattr(
        _narrow_sync,
        "current_type_widths",
        lambda *_args, **_kwargs: {"SubgameRuntime": None},
    )

    def fake_run_bn(_repo_root, *args):
        if args[:3] == ("types", "declare", "--preview"):
            return {
                "success": True,
                "preview": True,
                "committed": False,
                "affected_types": [],
                "affected_functions": [],
            }
        return {"result": {"applied": []}}

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    try:
        _narrow_sync.types_declare_if_missing(
            Path("."),
            target="snail-mail.exe",
            header_path=Path("runtime_types.h"),
            required_structs=("SubgameRuntime",),
        )
    except RuntimeError as error:
        assert "does not provide complete definitions" in str(error)
        assert "SubgameRuntime" in str(error)
    else:
        raise AssertionError("missing requested header type was accepted")


def test_previewed_mutation_verifies_before_apply(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        if "--preview" in args:
            return {
                "success": True,
                "preview": True,
                "committed": False,
                "message": "Preview verified and reverted.",
                "affected_types": [],
                "affected_functions": ["update_sub_lazer_projectile"],
            }
        return {"success": True, "committed": True}

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    result = _narrow_sync.run_previewed_bn_mutation(
        Path("."), "proto", "set", "update_sub_lazer_projectile", "void callback()"
    )

    assert "--preview" in calls[0]
    assert "--preview" not in calls[1]
    assert result["preview"]["affected_function_count"] == 1
    assert result["apply"]["committed"] is True


def test_previewed_mutation_rejects_failed_apply(monkeypatch) -> None:
    responses = iter(
        (
            {
                "success": True,
                "preview": True,
                "committed": False,
                "affected_types": [],
                "affected_functions": [],
            },
            {"success": False, "committed": False},
        )
    )
    monkeypatch.setattr(_narrow_sync, "run_bn", lambda *_args, **_kwargs: next(responses))

    try:
        _narrow_sync.run_previewed_bn_mutation(Path("."), "proto", "set", "callback", "void f()")
    except RuntimeError as error:
        assert "mutation apply failed" in str(error)
    else:
        raise AssertionError("failed mutation apply was accepted")


def test_previewed_batch_uses_one_transactional_python_preview_and_apply(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        code = args[args.index("--code") + 1]
        preview = "preview = True" in code
        return {
            "result": {
                "success": True,
                "preview": preview,
                "committed": not preview,
                "message": (
                    "Preview verified and reverted." if preview else "Mutation committed."
                ),
                "affected_types": [],
                "affected_functions": [],
            },
            "stdout": "",
            "warnings": [],
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)
    operations = [
        {
            "op": "set_prototype",
            "identifier": "update_sub_lazer_projectile",
            "prototype": "void callback()",
        }
    ]

    result = _narrow_sync.run_previewed_bn_batch(
        Path("."), target="snail-mail.exe", operations=operations
    )

    assert len(calls) == 2
    assert all(call[:2] == ("py", "exec") for call in calls)
    assert all("update_sub_lazer_projectile" in call[call.index("--code") + 1] for call in calls)
    assert "preview = True" in calls[0][calls[0].index("--code") + 1]
    assert "preview = False" in calls[1][calls[1].index("--code") + 1]
    assert result["apply"]["committed"] is True


def test_apply_proto_updates_batches_only_stale_prototypes(monkeypatch) -> None:
    captured = []
    monkeypatch.setattr(
        _narrow_sync,
        "current_prototypes",
        lambda *_args, **_kwargs: {
            "current": "void __thiscall(struct Owner* owner)",
            "stale": "int32_t __thiscall(struct Owner* owner)",
        },
    )

    def fake_previewed_batch(_repo_root, *, target, operations):
        captured.append((target, operations))
        return {"preview": {"success": True}, "apply": {"committed": True}}

    monkeypatch.setattr(_narrow_sync, "run_previewed_bn_batch", fake_previewed_batch)
    result = _narrow_sync.apply_proto_updates(
        Path("."),
        target="snail-mail.exe",
        updates=(
            ("current", "void __thiscall current(Owner* owner)"),
            ("stale", "void __thiscall stale(Owner* owner)"),
        ),
    )

    assert result[0]["status"] == "skipped"
    assert result[1]["op"] == "proto_set_batch"
    assert captured == [
        (
            "snail-mail.exe",
            [
                {
                    "op": "set_prototype",
                    "identifier": "stale",
                    "prototype": "void __thiscall stale(Owner* owner)",
                }
            ],
        )
    ]
