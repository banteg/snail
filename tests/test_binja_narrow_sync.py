import importlib.util
import json
from pathlib import Path

import pytest


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


def test_owner_syncs_keep_subgame_runtime_as_the_canonical_backlink() -> None:
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(encoding="utf-8")
    path_header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")

    assert 'TUTORIAL_FIELD_UPDATES = (\n    ("0x0c", "game", "SubgameRuntime*"),' in path_sync
    assert '("Tutorial", TUTORIAL_FIELD_UPDATES),' in path_sync
    assert "SubgameRuntime* game;" in path_header


def test_galaxy_replay_keeps_route_and_point_bank_ownership() -> None:
    repo_root = Path(__file__).parents[1]
    runtime_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/galaxy_route_types.h"
    ).read_text(encoding="utf-8")
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in (
            "bn_subgame_runtime_types.h",
            "ida_subgame_runtime_types.h",
            "path_template_types.h",
        )
    )

    assert '("0x408880", "initialize_galaxy_route_name_record")' in runtime_sync
    assert '("0x409bd0", "update_galaxy_route_record")' in runtime_sync
    assert '("0x4a1c4c", "g_galaxy_group_points")' in runtime_sync
    assert '("0x4a1d14", "g_galaxy_route_points")' in runtime_sync
    assert '("0x84", "color", "tColour")' in runtime_sync
    assert "int32_t __thiscall update_galaxy(Galaxy* galaxy)" in runtime_sync
    assert "void __thiscall open_galaxy_route(" in runtime_sync
    assert "void __thiscall galaxy_border_bound(" in runtime_sync

    for header in analysis_headers:
        assert "typedef struct GalaxyPoint" in header
        assert "GalaxyRouteSlot route_slots[101]" in header
        assert "GalaxyRouteNameRecord route_names[10]" in header

    assert "extern GalaxyPoint g_galaxy_group_points[10];" in matcher_header
    assert "extern GalaxyPoint g_galaxy_route_points[101];" in matcher_header


def test_frontend_tail_syncs_promote_proved_game_root_owners() -> None:
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(encoding="utf-8")
    high_score_sync = (BINJA_DIR / "sync_high_score_screen_types.py").read_text(
        encoding="utf-8"
    )

    assert '("0x12e6f58", "tip_manager", "TipManager")' in path_sync
    assert '("GameRoot", GAME_ROOT_FIELD_UPDATES)' in path_sync
    assert '("0x12e6e50", "high_score", "HighScore")' in high_score_sync
    assert 'struct_name="GameRoot"' in high_score_sync


def test_ida_replays_compose_the_complete_game_root_frontend_and_tail() -> None:
    owner_sync = (IDA_DIR / "game_root_owner.py").read_text(encoding="utf-8")
    path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    runtime_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    frame_sync = (IDA_DIR / "apply_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    frame_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("frame_renderer_types.h", "bn_frame_renderer_types.h")
    )

    assert '"SubgameRuntime": 0x1272838' in owner_sync
    for owner in (
        '(0x4EC10, 0x6CC, "backdrop", "Backdrop")',
        '(0x4F2DC, 0x48, "intro", "Intro")',
        '(0x4F324, 0x18, "main_menu", "MainMenu")',
        '(0x4F33C, 0x4C, "star_manager", "StarManager")',
        '(0x4F388, 0x24, "options", "Options")',
        '(0x4F3AC, 0x1C, "exit_controller", "Exit")',
        '(0x4F3C8, 0x38, "root_bod_4f3c8", "BodBase")',
        '(0x4F400, 0x25218, "logo", "Logo")',
    ):
        assert owner in owner_sync
    assert '(0x12E6E50, 0xF4, "high_score", "HighScore")' in owner_sync
    assert '(0x12E6F58, 0x98, "tip_manager", "TipManager")' in owner_sync
    assert "GAME_ROOT_GLOBAL_ADDRESS = 0x4DF904" in owner_sync
    assert "idc.SetType(GAME_ROOT_GLOBAL_ADDRESS, declaration)" in owner_sync
    assert '"root_global": root_global' in owner_sync
    assert "root.del_udm" in owner_sync
    assert "root.add_udm" in owner_sync
    assert 'owner_scope = "frontend_and_tail"' in owner_sync
    assert 'owner_scope = "tail_only"' in owner_sync
    assert '"owner_span_overlaps_proved_member"' in owner_sync
    assert (
        "uint8_t __thiscall initialize_game_assets_and_world(GameRoot *game);"
        in frame_sync
    )
    assert "typedef struct HighScore" in path_header
    assert "FrontendWidget* replay_row_widgets[10];" in path_header
    for source, required in (
        (path_sync, True),
        (runtime_sync, True),
        (frame_sync, False),
    ):
        assert "from game_root_owner import sync_game_root_owner_graph" in source
        assert f"sync_game_root_owner_graph(require={required})" in source
        assert '"game_root_owner_graph": game_root_owner_graph' in source
    for header in frame_headers:
        assert "uint8_t unknown_12727d8[0x1272838 - 0x12727d8];" in header
        assert "uint8_t unknown_12e6e50[0x12e6ff4 - 0x12e6e50];" in header
        assert "unknown_12e6df0" not in header

    bn_path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    assert "UPDATE_SUBGOLDY_USER_VAR_UPDATES" in bn_path_sync
    assert '"game_bytes_for_message"' in bn_path_sync
    assert '"game_bytes_for_duration"' in bn_path_sync
    assert "updates=UPDATE_SUBGOLDY_USER_VAR_UPDATES" in bn_path_sync


def test_ida_frontend_owner_lanes_replay_the_shared_root_graph() -> None:
    replay_sources = tuple(
        (IDA_DIR / name).read_text(encoding="utf-8")
        for name in (
            "apply_frontend_replay_types.py",
            "apply_star_manager_types.py",
            "apply_logo_types.py",
            "apply_frontend_menu_types.py",
            "apply_backdrop_types.py",
        )
    )
    for source in replay_sources:
        assert "from game_root_owner import sync_game_root_owner_graph" in source
        assert "sync_game_root_owner_graph(require=False)" in source
        assert '"game_root_owner_graph": game_root_owner_graph' in source

    menu_apply = (IDA_DIR / "apply_frontend_menu_types.py").read_text(
        encoding="utf-8"
    )
    menu_sync = (IDA_DIR / "sync_frontend_menu_types.py").read_text(
        encoding="utf-8"
    )
    backdrop_apply = (IDA_DIR / "apply_backdrop_types.py").read_text(
        encoding="utf-8"
    )
    backdrop_sync = (IDA_DIR / "sync_backdrop_types.py").read_text(
        encoding="utf-8"
    )

    assert '"MainMenu": 0x18' in menu_apply
    assert '"Options": 0x24' in menu_apply
    assert '"Exit": 0x1C' in menu_apply
    assert 'analysis/headers/bn_frontend_menu_types.h' in menu_sync
    assert "EXPECTED_BACKDROP_SIZE = 0x6CC" in backdrop_apply
    assert "void __thiscall render_backdrop(Backdrop* backdrop);" in backdrop_apply
    assert "int32_t __thiscall update_backdrop(Backdrop* backdrop);" in backdrop_apply
    assert 'analysis/headers/bn_backdrop_types.h' in backdrop_sync


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
    assert _narrow_sync.normalize_type_name(
        "union RuntimeRateOrLevelArg"
    ) == _narrow_sync.normalize_type_name("RuntimeRateOrLevelArg")


def test_normalize_prototype_treats_default_cdecl_as_equivalent() -> None:
    assert _narrow_sync.normalize_prototype(
        "void()", identifier="initialize_global_identity_matrix"
    ) == _narrow_sync.normalize_prototype(
        "void __cdecl initialize_global_identity_matrix()",
        identifier="initialize_global_identity_matrix",
    )

    assert _narrow_sync.normalize_prototype(
        "int32_t(char* url)", identifier="0x433050"
    ) == _narrow_sync.normalize_prototype(
        "int32_t __cdecl launch_alpha72_url(char* url)",
        identifier="0x433050",
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


def test_ensure_function_entry_verifies_created_boundary(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {
            "result": {
                "address": "0x406c20",
                "created": True,
                "observed_start": "0x406c20",
                "verified": True,
                "snapshot_saved": True,
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    assert _narrow_sync.ensure_function_entry(
        Path("."), target="snail-mail.exe", address=0x406C20
    ) == {
        "op": "function_entry_ensure",
        "address": "0x406c20",
        "status": "verified",
        "reason": None,
        "result": {
            "address": "0x406c20",
            "created": True,
            "observed_start": "0x406c20",
            "verified": True,
            "snapshot_saved": True,
        },
    }
    assert len(calls) == 1
    assert calls[0][:2] == ("py", "exec")
    assert "bv.add_function(address)" in calls[0][-1]


def test_direct_proto_batch_accepts_address_identifiers(monkeypatch) -> None:
    calls = []
    prototype = "int32_t __cdecl launch_alpha72_url(char* url)"

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {"result": {"applied": [], "snapshot_saved": True}}

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)
    monkeypatch.setattr(
        _narrow_sync,
        "current_prototypes",
        lambda *_args, **_kwargs: {"0x433050": "int32_t(char* url)"},
    )

    result = _narrow_sync.apply_direct_proto_updates_batch(
        Path("."),
        target="snail-mail.exe",
        updates=(("0x433050", prototype),),
    )

    assert result["operation_count"] == 1
    assert len(calls) == 1
    code = calls[0][-1]
    assert "address = int(text, 0)" in code
    assert "function = bv.get_function_at(address)" in code
    assert 'fn = find_function(identifier)' in code


def test_direct_proto_batch_requires_saved_snapshot(monkeypatch) -> None:
    monkeypatch.setattr(
        _narrow_sync,
        "run_bn",
        lambda *_args, **_kwargs: {
            "result": {"applied": [], "snapshot_saved": False}
        },
    )

    with pytest.raises(RuntimeError, match="without a saved snapshot"):
        _narrow_sync.apply_direct_proto_updates_batch(
            Path("."),
            target="snail-mail.exe",
            updates=(
                (
                    "layout_frontend_widget",
                    "void __thiscall layout_frontend_widget(FrontendWidget* widget)",
                ),
            ),
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


def test_symbol_removals_batch_only_the_expected_stale_alias(monkeypatch) -> None:
    captured = []
    monkeypatch.setattr(
        _narrow_sync,
        "current_symbol_names",
        lambda *_args, **_kwargs: {
            "0x5000fc": "g_object_index_buffer_factory",
            "0x502fec": None,
        },
    )

    def fake_previewed_batch(_repo_root, *, target, operations):
        captured.append((target, operations))
        return {"preview": {"success": True}, "apply": {"committed": True}}

    monkeypatch.setattr(_narrow_sync, "run_previewed_bn_batch", fake_previewed_batch)

    result = _narrow_sync.apply_symbol_removals(
        Path("."),
        target="snail-mail.exe",
        removals=(
            ("0x5000fc", "g_object_index_buffer_factory"),
            ("0x502fec", "g_d3d_device"),
        ),
    )

    assert result[0]["status"] == "skipped"
    assert result[0]["reason"] == "already absent"
    assert result[1]["op"] == "symbol_undefine_batch"
    assert captured == [
        (
            "snail-mail.exe",
            [
                {
                    "op": "undefine_symbol",
                    "address": "0x5000fc",
                    "expected_name": "g_object_index_buffer_factory",
                }
            ],
        )
    ]


def test_symbol_removals_refuse_an_unexpected_owner(monkeypatch) -> None:
    monkeypatch.setattr(
        _narrow_sync,
        "current_symbol_names",
        lambda *_args, **_kwargs: {"0x5000fc": "index_buffer_factory"},
    )

    try:
        _narrow_sync.apply_symbol_removals(
            Path("."),
            target="snail-mail.exe",
            removals=(("0x5000fc", "g_object_index_buffer_factory"),),
        )
    except RuntimeError as error:
        assert "refusing to undefine unexpected symbol" in str(error)
        assert "index_buffer_factory" in str(error)
    else:
        raise AssertionError("unexpected owner symbol was accepted for removal")


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
    ida_source = (IDA_DIR / "apply_star_manager_types.py").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        Path(__file__).parents[1] / "tools/match/include/star_manager.h"
    ).read_text(encoding="utf-8")

    assert "types_declare_missing_only" in source
    assert "current_struct_size" in source
    assert '"Sprite": 0xB4' in source
    assert "types_declare(" not in source
    for function_name in (
        "destroy_star_field",
        "initialize_star_field",
        "hide_star_field",
        "unhide_star_field",
    ):
        assert f"void __thiscall {function_name}(StarManager* manager)" in source
        assert f"void __thiscall {function_name}(StarManager *manager);" in ida_source
        assert f"void {function_name}();" in matcher_header
        assert f"int {function_name}();" not in matcher_header
    assert "virtual void update_star_field_callback();" in matcher_header
    assert "noncanonical_star_manager_header" in ida_source
    assert "EXPECTED_OWNER_SIZES" in ida_source
    assert "owner_size_mismatch" in ida_source
    star_analysis_header = (HEADER_DIR / "star_manager_types.h").read_text(
        encoding="utf-8"
    )
    assert "typedef struct TransformMatrix TransformMatrix;" not in star_analysis_header


def test_frontend_menu_sync_owns_the_contiguous_root_block() -> None:
    source = (BINJA_DIR / "sync_frontend_menu_types.py").read_text(encoding="utf-8")
    header = (HEADER_DIR / "bn_frontend_menu_types.h").read_text(encoding="utf-8")

    for owner in (
        '("0x4f324", "main_menu", "MainMenu")',
        '("0x4f388", "options", "Options")',
        '("0x4f3ac", "exit_controller", "Exit")',
        '("0x4f3c8", "root_bod_4f3c8", "BodBase")',
    ):
        assert owner in source
    for expected_size in (
        '"MainMenu": 0x18',
        '"Options": 0x24',
        '"Exit": 0x1C',
    ):
        assert expected_size in source
    for prototype in (
        "void __thiscall initialize_main_menu(MainMenu* menu)",
        "void __thiscall update_options_menu(Options* options)",
        "void __thiscall initialize_exit_prompt(Exit* exit_controller)",
    ):
        assert prototype in source
    assert "apply_struct_and_proto_updates" in source
    assert "types_declare_missing_only" in source
    assert 'BOD_BASE_EXPECTED_SIZE = 0x38' in source
    assert 'observed_widths.get("BodBase") != BOD_BASE_EXPECTED_SIZE' in source
    assert "types_declare(" not in source
    assert "typedef struct FrontendWidget FrontendWidget;" in header
    assert "typedef struct MainMenu" in header
    assert "typedef struct Options" in header
    assert "typedef struct Exit" in header


def test_broad_type_declaration_rejects_complete_to_forward_regression(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        if args[:3] == ("types", "declare", "--preview"):
            return {
                "success": True,
                "preview": True,
                "committed": False,
                "message": "Preview verified and reverted.",
                "affected_types": [
                    {
                        "type_name": "FrontendWidget",
                        "before_layout": "struct FrontendWidget // size=0x724",
                        "after_layout": "struct FrontendWidget // size=0x0",
                        "changed": True,
                    }
                ],
                "affected_functions": [],
            }
        raise AssertionError("unsafe declaration should not be committed")

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    try:
        _narrow_sync.types_declare(
            Path("."), target="snail-mail.exe", header_path=Path("intro_types.h")
        )
    except RuntimeError as exc:
        assert "erases complete owners" in str(exc)
        assert "FrontendWidget" in str(exc)
    else:
        raise AssertionError("expected a zero-width ownership regression to be rejected")

    assert len(calls) == 1


def test_path_sync_owns_core_subgame_receiver_abis() -> None:
    source = (BINJA_DIR / "sync_path_template_types.py").read_text(encoding="utf-8")
    repair_source = (BINJA_DIR / "repair_initialize_subgame_owner.py").read_text(
        encoding="utf-8"
    )
    repair_entrypoint = (BINJA_DIR / "repair_subgame_receiver_owner.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")

    assert "CORE_SUBGAME_PROTO_UPDATES" in source
    assert "DEFERRED_SUBGAME_OWNER_PROTO_UPDATES" in source
    assert "proto_owner_deferred" in source
    assert "apply_struct_and_proto_updates" in source
    assert "apply_direct_proto_update" not in source
    assert "proto_owner_current" in source
    assert "repair_subgame_receiver_owner.py" in source
    assert 'f"--function {identifier} --apply"' in source
    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"' in source
    assert '"SubRow",' in source
    assert '"TrackAttachmentRuntimeRow",' not in source
    assert "typedef struct SubRow {" in header
    assert "SubRow runtime_rows[3200];" in header
    assert "TrackAttachmentRuntimeRow" not in header
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
        "build_track_fringe_objects",
        "promote_track_tiles_to_fringe_variants",
        "harmonize_center_lane_floor_slide_variants",
        "select_track_tile_edge_variants",
        "get_track_grid_cell_at_world_position",
        "sample_track_floor_height_at_position",
        "spawn_track_health_pickup",
        "spawn_track_jetpack_pickup",
        "get_track_runtime_cell_at_world_z",
    ):
        assert f'"{function_name}"' in deferred_prototypes
    assert (
        '"initialize_subgame", "void __thiscall '
        'initialize_subgame(SubgameRuntime* game)"'
    ) in deferred_prototypes
    for function_name in (
        "destroy_subgame",
        "update_subgame",
        "remove_subgame_bods",
    ):
        assert (
            f'"{function_name}", "void __thiscall '
            f'{function_name}(SubgameRuntime* game)"'
        ) in deferred_prototypes
    assert '"address": 0x4374B0' in repair_source
    assert '"expected_prototype": "void __thiscall(struct SubgameRuntime* game)"' in repair_source
    assert '"stale_prototype": "void __fastcall(struct Game* game)"' in repair_source
    for function_name in (
        "initialize_subgame",
        "build_subgame_level",
        "destroy_subgame",
        "update_subgame",
        "remove_subgame_bods",
        "merge_track_tile_runs",
        "build_track_fringe_objects",
        "promote_track_tiles_to_fringe_variants",
        "harmonize_center_lane_floor_slide_variants",
        "select_track_tile_edge_variants",
        "get_track_grid_cell_at_world_position",
        "sample_track_floor_height_at_position",
        "spawn_track_health_pickup",
        "spawn_track_jetpack_pickup",
        "get_track_runtime_cell_at_world_z",
    ):
        assert f'"{function_name}": {{' in repair_source
    for address in (
        "0x4374B0",
        "0x437EB0",
        "0x438850",
        "0x438B90",
        "0x440910",
        "0x435180",
        "0x434BE0",
        "0x4355F0",
        "0x4356F0",
        "0x435A80",
        "0x43D410",
        "0x43D4D0",
        "0x43D6C0",
        "0x43D890",
        "0x43D480",
    ):
        assert f'"address": {address}' in repair_source
    assert "from repair_initialize_subgame_owner import main" in repair_entrypoint
    assert '"legacy_prototypes": (' in repair_source
    assert '"struct SubRow* __thiscall("' in repair_source
    assert '"SubRow* __thiscall "' in repair_source
    assert (
        '"SubRow* __thiscall get_track_runtime_cell_at_world_z('
        'SubgameRuntime* game, Vec3* position)"'
    ) in deferred_prototypes
    assert (
        '"SubRow* __thiscall get_track_runtime_cell_at_world_z('
        'SubgameRuntime* game, Vec3* position);"'
    ) in ida_source
    for function_name in (
        "spawn_track_health_pickup",
        "spawn_track_jetpack_pickup",
    ):
        declaration = (
            f"void __thiscall {function_name}(SubgameRuntime* game, "
            "TrackRowCell* cell, Player* player);"
        )
        assert declaration in header
        assert declaration in ida_source
        assert declaration.removesuffix(";") in deferred_prototypes
    assert '"spawn_track_health_pickup": 3' in ida_source
    assert '"spawn_track_jetpack_pickup": 3' in ida_source
    assert '"get_track_grid_cell_at_world_position": 2' in ida_source
    assert '"sample_track_floor_height_at_position": 2' in ida_source
    assert "if stale and comments:" in repair_source
    assert "if stale and tags:" in repair_source
    assert '"allowed_auto_tag_types": ("Unresolved Stack Pointer Value",)' in repair_source
    assert "restore_preserved_auto_tags(repaired, preserved_auto_tags)" in repair_source
    assert "record[\"auto\"] and record[\"type\"] in ALLOWED_AUTO_TAG_TYPES" in repair_source
    assert "function_has_unpreserved_user_vars" in repair_source
    assert "def restore_old_function():" in repair_source
    assert '"--apply"' in repair_source
    assert "Without this flag the tool" in repair_source
    assert '"is read-only. Function recreation' in repair_source
    assert "def _sync_subgame_receiver_lvar" in ida_source
    assert "ida_hexrays.mark_cfunc_dirty(address, True)" in ida_source
    for function_name in (
        "initialize_subgame",
        "destroy_subgame",
        "update_subgame",
        "remove_subgame_bods",
    ):
        declaration = f"void __thiscall {function_name}(SubgameRuntime* game);"
        assert declaration in header
        assert declaration in ida_source


def test_bod_object_ownership_replay_uses_canonical_object_type() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    object_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    object_headers = [
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bn_object_render_types.h", "object_render_types.h")
    ]
    matcher_header = (repo_root / "tools/match/include/bod_types.h").read_text(
        encoding="utf-8"
    )

    assert '("0x24", "object", "Object*")' in path_sync
    assert '("BodBase", BOD_BASE_FIELD_UPDATES)' in path_sync
    assert '("FringeObject", FRINGE_OBJECT_FIELD_UPDATES)' in path_sync
    assert "Object* object;" in path_header
    assert "int set_bod_object(Object* object);" in matcher_header
    for function_name in (
        "request_object_vertices",
        "request_object_vertex_colours",
        "request_object_facequads",
    ):
        assert f'"{function_name}"' in object_sync
        for header in object_headers:
            assert function_name in header
    for function_name in (
        "set_bod_object",
        "initialize_bod_base",
        "apply_bod_position",
        "build_track_fringe_mesh",
        "build_track_fringe_supertramp_mesh",
    ):
        assert f'"{function_name}"' in path_sync


def test_object_geometry_replay_keeps_owned_helpers_and_workspace_globals() -> None:
    repo_root = Path(__file__).parents[1]
    sync_source = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = [
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bn_object_render_types.h", "object_render_types.h")
    ]
    matcher_header = (
        repo_root / "tools/match/include/object_render_types.h"
    ).read_text(encoding="utf-8")

    for address, name, data_type in (
        ("0x503300", "g_object_edge_build_edges", "ObjectToonEdge*"),
        ("0x503318", "g_object_edge_build_count", "int32_t"),
    ):
        assert f'("{address}", "{name}")' in sync_source
        assert f'("{address}", "{data_type}")' in sync_source
        for header in analysis_headers:
            assert name in header

    for function_name in (
        "request_object_facequad_normals",
        "request_object_texture_groups",
        "request_object_edges",
        "calc_object_bounding_box",
        "calc_object_facequad_normals",
        "calc_object_texture_groups",
        "add_object_edge",
        "calc_object_edges",
    ):
        assert f'"{function_name}"' in sync_source

    assert "Vec3* __thiscall request_object_facequad_normals(Object* object)" in sync_source
    assert "Vector3* request_object_facequad_normals();" in matcher_header
    for header in analysis_headers:
        assert "Vec3* __thiscall request_object_facequad_normals(Object* object);" in header
        assert "void __thiscall request_object_texture_groups(" in header


def test_object_buffer_replay_keeps_copy_distort_and_workspace_owners() -> None:
    repo_root = Path(__file__).parents[1]
    sync_source = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync_source = (IDA_DIR / "apply_object_render_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = [
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bn_object_render_types.h", "object_render_types.h")
    ]
    matcher_header = (
        repo_root / "tools/match/include/object_render_types.h"
    ).read_text(encoding="utf-8")

    for function_name in (
        "copy_object_vertices",
        "request_object_vertices_copy",
        "apply_distort_to_object",
        "replace_object_list_texture_refs",
        "get_or_append_object_texture_group_vertex",
        "refresh_object_vertex_buffer",
        "build_object_texture_group_buffers",
    ):
        assert f'"{function_name}"' in sync_source

    assert (
        "void __thiscall apply_distort_to_object(ObjectDistort* distort, "
        "Object* object)"
    ) in sync_source
    assert (
        "int32_t __cdecl get_or_append_object_texture_group_vertex(Object* object, "
        "int32_t vertex_index, float u, float v)"
    ) in sync_source
    assert (
        "void __thiscall replace_object_list_texture_refs(ObjectList* object_list, "
        "TextureRef* new_texture, TextureRef* old_texture)"
    ) in sync_source
    assert (
        "void __thiscall replace_object_list_texture_refs(ObjectList* object_list, "
        "TextureRef* new_texture, TextureRef* old_texture);"
    ) in ida_sync_source
    assert '"void __thiscall initialize_object(Object* object);"' in ida_sync_source
    assert 're.sub(r"\\(void\\)$", "()", normalized)' in ida_sync_source
    for header in analysis_headers:
        assert "typedef struct ObjectRenderVertex" in header
        assert "void __thiscall copy_object_vertices(Object* object);" in header
        assert "ObjectDistort* distort, Object* object);" in header
        assert "void __thiscall replace_object_list_texture_refs(" in header
        assert "extern int32_t g_object_grouped_vertex_cursor;" in header
        assert "extern ObjectGroupedVertex* g_object_grouped_vertex_scratch;" in header

    assert "int get_or_append_object_texture_group_vertex(" in matcher_header
    assert "extern int g_object_grouped_vertex_cursor;" in matcher_header
    assert "extern ObjectGroupedVertex* g_object_grouped_vertex_scratch;" in matcher_header


def test_direct3d_renderer_replay_keeps_singleton_and_device_ownership() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_object_render_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = [
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bn_object_render_types.h", "object_render_types.h")
    ]
    matcher_header = (
        repo_root / "tools/match/include/direct3d_renderer.h"
    ).read_text(encoding="utf-8")
    matcher_device_header = (
        repo_root / "tools/match/include/direct3d_device8_view.h"
    ).read_text(encoding="utf-8")

    for address, name, data_type in (
        ("0x4f7450", "g_render_triangle_count", "int32_t"),
        ("0x4f7454", "g_render_successful_primitive_count", "int32_t"),
        ("0x4f7458", "g_direct3d_renderer", "Direct3DRenderer"),
        ("0x503170", "g_draw_primitive_call_count", "int32_t"),
        ("0x503174", "g_current_texture_ref", "TextureRef*"),
        ("0x5031c0", "g_texture_bind_call_count", "int32_t"),
        ("0x5031c8", "g_d3d_texture_slots", "Direct3DTexture8**"),
    ):
        assert f'("{address}", "{name}")' in binja_sync
        assert f'("{address}", "{data_type}")' in binja_sync

    assert '("0xbb90", "d3d", "Direct3D8*")' in binja_sync
    assert '("0xbb94", "device", "Direct3DDevice8*")' in binja_sync
    assert '("0xbb98", "present", "D3DPresentParameters")' in binja_sync
    assert '("0xbbcc", "device_caps", "D3DDeviceCaps8")' in binja_sync
    assert '("0x502fec",' not in binja_sync
    symbol_updates = binja_sync.split("SYMBOL_UPDATES = (", 1)[1].split(
        "\n)\n\nSYMBOL_REMOVALS", 1
    )[0]
    assert '"0x5000fc"' not in symbol_updates
    assert (
        'SYMBOL_REMOVALS = (\n'
        '    ("0x5000fc", "g_object_index_buffer_factory"),\n'
        ")"
    ) in binja_sync

    for function_name in (
        "create_vertex_buffer",
        "create_index_buffer",
        "release_direct3d_renderer_resources",
        "direct3d_renderer_set_cull_mode",
        "initialize_d3d8_device",
        "reset_direct3d_render_state",
        "release_direct3d_device_interfaces",
        "present_backbuffer",
        "set_fullscreen_mode",
        "restore_texture_ref_stage_states",
        "bind_texture_ref",
        "query_direct3d_device_caps",
        "set_blend_mode",
        "set_immediate_blend_mode",
        "draw_textured_quad_immediate",
    ):
        assert f'"{function_name}"' in binja_sync
        assert f'"{function_name}"' in ida_sync

    for header in analysis_headers:
        assert "typedef struct Direct3DRenderer" in header
        assert "VertexBufferFactory vertex_buffer_factory;" in header
        assert "IndexBufferFactory index_buffer_factory;" in header
        assert "Direct3DDevice8* device;" in header
        assert "D3DPresentParameters present;" in header
        assert "D3DDeviceCaps8 device_caps;" in header
        assert "extern Direct3DRenderer g_direct3d_renderer;" in header
        assert "extern Direct3DDevice8* g_d3d_device;" not in header
        assert "extern IndexBufferFactory g_object_index_buffer_factory;" not in header
        assert "extern int32_t g_render_successful_primitive_count;" in header
        assert "void __cdecl bind_texture_ref(TextureRef* texture);" in header
        assert "ObjectRenderBuffers* __thiscall create_vertex_buffer(" in header
        assert "ObjectIndexBuffer* __thiscall create_index_buffer(" in header
        assert "void __cdecl draw_textured_quad_immediate(" in header

    assert "VertexBufferFactory vertex_buffer_factory; // +0x0000" in matcher_header
    assert "IndexBufferFactory index_buffer_factory; // +0x8ca4" in matcher_header
    assert "Direct3DDevice8* device;" in matcher_header
    assert "D3DPresentParameters present;" in matcher_header
    assert "D3DDeviceCaps8 device_caps;" in matcher_header
    assert (
        "Matcher relocation alias for g_direct3d_renderer.device (+0xbb94)."
        in matcher_device_header
    )


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


def test_subgame_control_prefix_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
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
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    runtime_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    frame_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("bn_frame_renderer_types.h", "frame_renderer_types.h")
    )
    frame_sync = (BINJA_DIR / "sync_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )

    assert "apply_struct_and_proto_updates" in runtime_sync
    assert "apply_struct_field_updates" not in runtime_sync
    assert "apply_direct_proto_update" not in runtime_sync

    for header in (*analysis_headers, matcher_header):
        assert "scan_reset" in header
        assert "camera_snap_requested" in header
        assert "track_mirror_enabled" in header
        assert "track_mirror_repeat_count" in header
        assert "resume_requested" in header
        assert "subgame_pause_gate" in header
        assert "pause_fade" in header
        assert "pause_fade_step" in header
        assert "sub_pause" in header
        assert "runtime_row_scan_begin" in header
        assert "runtime_row_scan_end" in header

    for sync in (path_sync, runtime_sync):
        assert '("0x00", "scan_reset", "uint8_t")' in sync
        assert '("0x01", "camera_snap_requested", "uint8_t")' in sync
        assert '("0x08", "resume_requested", "uint8_t")' in sync
        assert '("0x0c", "pause_fade", "float")' in sync
        assert '("0x10", "pause_fade_step", "float")' in sync
        assert '("0x14", "sub_pause", "SubPause")' in sync
        assert '("0x20", "runtime_row_scan_begin", "int32_t")' in sync
        assert '("0x24", "runtime_row_scan_end", "int32_t")' in sync

    for header in frame_headers:
        assert "uint8_t scan_reset;" in header
        assert "uint8_t camera_snap_requested;" in header
        assert "int32_t track_mirror_repeat_count;" in header
        assert "uint8_t resume_requested;" in header
        assert "uint8_t subgame_pause_gate;" in header
        assert "float pause_fade;" in header
        assert "float pause_fade_step;" in header
        assert "int32_t subgame_state;" in header
        assert "int32_t level_mode;" in header
        assert "uint8_t unknown_000000[0x40];" not in header

    assert "FRAME_SUBGAME_RUNTIME_FIELD_UPDATES" in frame_sync
    assert '("0x08", "resume_requested", "uint8_t")' in frame_sync
    assert '("0x3c", "subgame_state", "int32_t")' in frame_sync
    assert "def resolved_game_root_field_updates" in frame_sync
    assert 'struct_name="SubgameRuntime"' in frame_sync
    assert 'else "FrameSubgameRuntime"' in frame_sync
    assert "apply_struct_and_proto_updates" in frame_sync
    assert "apply_struct_field_updates" not in frame_sync
    assert (
        '"void __thiscall update_subgame_camera(SubgameRuntime* runtime)"'
        in runtime_sync
    )
    assert (
        '"void __thiscall update_subgame_camera(SubgameRuntime* runtime);"'
        in ida_sync
    )
    assert "char __thiscall update_subgame_camera" not in ida_sync
    assert '("0x5c", "segment_cache", "SegmentCache")' in path_sync

    consumers = {
        "reset_subgame": ("scan_reset", "camera_snap_requested"),
        "update_subgame_camera": ("camera_snap_requested",),
        "update_pause_menu": ("resume_requested",),
        "initialize_subgame": ("pause_fade", "pause_fade_step"),
        "update_subgame": ("scan_reset", "resume_requested", "pause_fade"),
        "switch_track_mirror": (
            "track_mirror_enabled",
            "track_mirror_repeat_count",
        ),
    }
    for function_name, fields in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        for field in fields:
            assert field in scratch


def test_sub_ring_kind_and_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    pool_sync = (BINJA_DIR / "sync_subgame_pool_types.py").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_runner = (IDA_DIR / "sync_subgame_runtime_types.py").read_text(
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
        assert "SubRing* parent;" in header
        assert "SubRingStar particles[" in header
        assert "SubgameRuntime* rate_source;" in header
        assert "SubRing slots[" in header
        assert "RingEffectRateSource" not in header

    path_header = analysis_headers[1]
    assert "SubRingPool ring_effects;" in path_header
    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"' in ida_runner
    for prototype in (
        "SubRing* __thiscall initialize_track_ring_or_special_effect_runtime",
        "void __thiscall spawn_track_ring_or_special_effect",
        "int32_t __thiscall initialize_ring_or_special_effect_particles",
        "void __thiscall emit_ring_star_shower",
        "void __thiscall update_ring_or_special_effect_particle",
        "void __thiscall update_ring_or_special_effect_parent",
    ):
        assert prototype in path_header
        assert prototype in ida_sync

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
    assert '("JetPack", JETPACK_FIELD_UPDATES)' in runtime_sync
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


def test_frontend_widget_flag_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    frontend_sync = (BINJA_DIR / "sync_frontend_widget_types.py").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = [
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in (
            "bn_frontend_widget_types.h",
            "completion_screen_types.h",
            "frontend_replay_types.h",
            "path_template_types.h",
        )
    ]
    matcher_header = (
        repo_root / "tools/match/include/frontend_widget.h"
    ).read_text(encoding="utf-8")

    assert '("0x1a0", "widget_flags", "FrontendWidgetFlag")' in frontend_sync
    assert (
        '("0x1a4", "previous_widget_flags", "FrontendWidgetFlag")'
        in frontend_sync
    )
    assert '"FrontendWidgetFlag",' in path_sync
    for header in (*analysis_headers, matcher_header):
        assert "FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED = 0x00000020" in header
        assert "FRONTEND_WIDGET_FLAG_KILL_PENDING = 0x00000200" in header
        assert "FRONTEND_WIDGET_FLAG_TEARDOWN_ACTIVE = 0x00000400" in header
        assert "FRONTEND_WIDGET_FLAG_HIDDEN = 0x00001000" in header
        assert "FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE = 0x00002000" in header
        assert "FRONTEND_WIDGET_FLAG_DISABLED = 0x00008000" in header
        assert "FRONTEND_WIDGET_FLAG_POINTER_INSIDE = 0x00020000" in header
        assert "FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED = 0x00080000" in header
        assert "FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION = 0x40000000" in header

    consumers = {
        "kill_border": "FRONTEND_WIDGET_FLAG_KILL_PENDING",
        "hide_border_init": "FRONTEND_WIDGET_FLAG_HIDDEN",
        "border_input_text": "FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE",
        "update_frontend_widget_interaction": "FRONTEND_WIDGET_FLAG_POINTER_INSIDE",
        "set_frontend_widget_shortcut_key": "FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED",
        "queue_frontend_widget_flag_after_delay": "FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_frontend_widget_draw_owner_replay_stays_aligned() -> None:
    frontend_sync = (BINJA_DIR / "sync_frontend_widget_types.py").read_text(
        encoding="utf-8"
    )
    ida_frontend_sync = (
        IDA_DIR / "apply_frontend_replay_types.py"
    ).read_text(encoding="utf-8")

    expected = "void __thiscall draw_frontend_widget(FrontendWidget* widget)"
    assert expected in frontend_sync
    assert "EXPECTED_STRUCT_SIZES" in frontend_sync
    assert "types_declare_missing_only" in frontend_sync
    assert "apply_struct_and_proto_updates" in frontend_sync
    assert "apply_user_var_updates" in frontend_sync
    assert '"RegisterVariableSourceType"' in frontend_sync
    assert '"widget",\n        "FrontendWidget*"' in frontend_sync
    assert "proto_owner_deferred" in frontend_sync
    assert "stale explicit function type requires guarded recreation" in frontend_sync
    assert f'"{expected};"' in ida_frontend_sync
    assert '(0x401130, "draw_frontend_widget")' in ida_frontend_sync


def test_frontend_widget_input_text_owner_replay_stays_aligned() -> None:
    frontend_sync = (BINJA_DIR / "sync_frontend_widget_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )

    expected = "void __thiscall border_input_text(FrontendWidget* widget)"
    assert expected in frontend_sync
    assert f'"{expected};"' in ida_path_sync
    assert '"border_input_text",\n        "RegisterVariableSourceType"' in frontend_sync
    for field in (
        "input_cursor",
        "input_cursor_visible",
        "input_cursor_blink_progress",
        "input_cursor_blink_step",
        "input_flags",
        "input_length",
        "input_capacity",
    ):
        assert field in ida_path_header
    assert "_pad_6fc" not in ida_path_header


def test_frontend_widget_void_replays_stay_direct() -> None:
    frontend_sync = (BINJA_DIR / "sync_frontend_widget_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )

    deferred = frontend_sync.split("\nDEFERRED_PROTO_UPDATES = (", 1)[1].split(
        "\nPROTO_UPDATES = (", 1
    )[0]
    direct = frontend_sync.split("\nPROTO_UPDATES = (", 1)[1].split(
        "\nUSER_VAR_UPDATES = (", 1
    )[0]

    expected = (
        "void __thiscall initialize_frontend_widget(FrontendWidget* widget, uint32_t widget_flags, char* text, int32_t widget_type, float x, float y, tColour* color, int32_t text_alignment, float anchor_x)",
        "void __thiscall layout_frontend_widget(FrontendWidget* widget)",
        "void __thiscall set_frontend_widget_shortcut_key(FrontendWidget* widget, int32_t shortcut_key_code)",
        "void __thiscall stack_widget_below(FrontendWidget* widget, FrontendWidget* previous_widget)",
        "void __thiscall hide_border_init(FrontendWidget* widget)",
        "void __thiscall unhide_border_init(FrontendWidget* widget)",
        "void __thiscall unhighlight_border(FrontendWidget* widget)",
        "void __thiscall highlight_border(FrontendWidget* widget)",
        "void __thiscall border_sprite_extend(FrontendWidget* widget, int32_t sprite_a, int32_t sprite_c, int32_t sprite_b, uint8_t wobble_positive)",
        "void __thiscall border_input_text_init(FrontendWidget* widget, int32_t capacity, char* text, int32_t flags)",
        "void __thiscall reset_tooltip(FrontendWidgetTooltip* tooltip)",
        "void __thiscall update_tooltip(FrontendWidgetTooltip* tooltip)",
    )
    for prototype in expected:
        assert prototype not in deferred
        assert prototype in direct
        assert f'"{prototype};"' in ida_path_sync
    assert (
        '"initialize_frontend_widget",\n'
        '        "RegisterVariableSourceType",\n'
        "        851,\n"
        "        66,\n"
        '        "hot_text_color_source",\n'
        '        "tColour*",'
    ) in frontend_sync
    assert (
        '"initialize_frontend_widget",\n'
        '        "RegisterVariableSourceType",\n'
        "        1680,\n"
        "        66,\n"
        '        "slider_less_color",\n'
        '        "tColour*",'
    ) in frontend_sync


def test_sprite_and_texture_flag_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    sync_sources = {
        script_name: (BINJA_DIR / script_name).read_text(encoding="utf-8")
        for script_name in (
            "sync_garbage_hazard_types.py",
            "sync_object_render_types.py",
            "sync_path_template_types.py",
            "sync_star_manager_types.py",
        )
    }
    sprite_analysis_headers = [
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in (
            "bn_garbage_hazard_types.h",
            "star_manager_types.h",
        )
    ]
    texture_analysis_headers = [
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in (
            "bn_object_render_types.h",
            "object_render_types.h",
            "path_template_types.h",
            "star_manager_types.h",
        )
    ]
    matcher_header = (repo_root / "tools/match/include/sprite.h").read_text(
        encoding="utf-8"
    )

    assert '("0x04", "flags", "SpriteFlag")' in sync_sources[
        "sync_garbage_hazard_types.py"
    ]
    assert '("0x04", "flags", "SpriteFlag")' in sync_sources[
        "sync_star_manager_types.py"
    ]
    assert '("0x00", "flags", "TextureRefFlags")' in sync_sources[
        "sync_object_render_types.py"
    ]
    assert '("0x00", "flags", "TextureRefFlags")' in sync_sources[
        "sync_path_template_types.py"
    ]
    assert '("0x00", "flags", "TextureRefFlags")' in sync_sources[
        "sync_star_manager_types.py"
    ]

    sprite_constants = (
        "SPRITE_FLAG_ACTIVE = 0x0001",
        "SPRITE_FLAG_ORIENT_TO_MOTION = 0x0002",
        "SPRITE_FLAG_SKIP_INITIAL_PROGRESS = 0x0008",
        "SPRITE_FLAG_RENDER_ENABLED = 0x0040",
        "SPRITE_FLAG_PRESERVE_AT_PROGRESS_END = 0x0100",
        "SPRITE_FLAG_DELAYED_RENDER = 0x0200",
        "SPRITE_FLAG_THROTTLE_FACING_REFRESH = 0x0400",
        "SPRITE_FLAG_GAMEPLAY_OWNED = 0x0800",
        "SPRITE_FLAG_FORCE_OPAQUE = 0x1000",
        "SPRITE_FLAG_ANIMATED = 0x2000",
        "SPRITE_FLAG_ANIMATION_PING_PONG = 0x4000",
    )
    texture_constants = (
        "TEXTURE_REF_RETAIN_SOURCE_BYTES = 0x20",
        "TEXTURE_REF_REGISTERED = 0x400",
        "TEXTURE_REF_DISABLE_PATH_REUSE = 0x800",
        "TEXTURE_REF_WRAP_ADDRESSING = 0x1000",
        "TEXTURE_REF_ANIMATED = 0x2000",
        "TEXTURE_REF_ANIMATION_PING_PONG = 0x4000",
        "TEXTURE_REF_SKIP_RUNTIME_LOAD = 0x8000",
        "TEXTURE_REF_HAS_ALPHA = 0x10000",
    )
    for header in (*sprite_analysis_headers, matcher_header):
        for constant in sprite_constants:
            assert constant in header
    for header in (*texture_analysis_headers, matcher_header):
        for constant in texture_constants:
            assert constant in header

    consumers = {
        "initialize_sprite": "SPRITE_FLAG_RENDER_ENABLED",
        "update_sprite": "SPRITE_FLAG_ANIMATION_PING_PONG",
        "update_sprite_facing_angle": "SPRITE_FLAG_THROTTLE_FACING_REFRESH",
        "draw_sprite_quad": "SPRITE_FLAG_FORCE_OPAQUE",
        "get_or_create_texture_ref": "TEXTURE_REF_DISABLE_PATH_REUSE",
        "load_registered_texture_ref": "TEXTURE_REF_SKIP_RUNTIME_LOAD",
        "bind_texture_ref": "TEXTURE_REF_WRAP_ADDRESSING",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_runtime_config_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    analysis_header = (HEADER_DIR / "runtime_config_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/runtime_config.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (BINJA_DIR / "sync_runtime_config_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_runtime_config_types.py").read_text(
        encoding="utf-8"
    )

    for header in (analysis_header, matcher_header):
        assert "RUNTIME_RENDER_STAR_FIELD = 0x00000004" in header
        assert "RUNTIME_RENDER_PARTICLE_EFFECTS = 0x00000010" in header
        assert "RUNTIME_RENDER_TRACK_FRINGE = 0x00000020" in header
        assert "RUNTIME_RENDER_FONT_WAVE = 0x00000100" in header
        assert "RUNTIME_RENDER_32_BIT_COLOR = 0x00000400" in header
        assert "RUNTIME_RENDER_FONT_WAVE_BIT = 8" in header
        assert "last_entered_player_name[0x40]" in header
        assert "highest_galaxy_route_index" in header
        assert "new_game_tutorial_started" in header

    assert '("0x1c", "render_flags", "RuntimeRenderFlag")' in binja_sync
    assert '("0x4df918", "g_runtime_config")' in binja_sync
    assert '("0x4df918", "RuntimeConfig")' in binja_sync
    assert 'struct_name="RuntimeConfig"' in binja_sync
    assert 'initialize_default_runtime_config_thunk(void)' in analysis_header
    assert '(0x406C10, "initialize_default_runtime_config_thunk")' in ida_sync
    assert '(0x406C20, "initialize_default_runtime_config")' in ida_sync
    assert '(0x4DF918, "g_runtime_config")' in ida_sync
    assert 'RuntimeConfig g_runtime_config;' in ida_sync

    references = json.loads(
        (repo_root / "analysis/symbols/gameplay-references.json").read_text(
            encoding="utf-8"
        )
    )
    owner = next(
        entry
        for entry in references["symbols"]
        if int(entry["address"], 0) == 0x4DF918
    )
    assert owner["name"] == "g_runtime_config"
    assert "g_config_sample_volume" in owner["aliases"]
    assert owner["size"] == "0xc4"

    consumers = {
        "initialize_game_window_and_input": "RUNTIME_RENDER_32_BIT_COLOR",
        "open_star_field": "RUNTIME_RENDER_STAR_FIELD",
        "emit_ring_star_shower": "RUNTIME_RENDER_PARTICLE_EFFECTS",
        "build_track_fringe_objects": "RUNTIME_RENDER_TRACK_FRINGE",
        "layout_frontend_widget": "RUNTIME_RENDER_FONT_WAVE_BIT",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_font_system_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    analysis_header = (HEADER_DIR / "font_system_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/font_system.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (BINJA_DIR / "sync_font_system_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_font_system_types.py").read_text(
        encoding="utf-8"
    )

    for header in (analysis_header, matcher_header):
        assert "typedef struct FontSheet {" in header or "struct FontSheet {" in header
        assert "float glyph_width[" in header
        assert "int32_t texture_page[0x80]" in header or "int texture_page[" in header
        assert "float width_scale" in header
        assert "float height_scale" in header
        assert "struct cFontPrintBuffer {" in header
        assert "text_wave_amplitude" in header
        assert "text_wave_enabled" in header
        assert "tColour color" in header
        assert "int32_t blend_mode" in header or "int blend_mode" in header
        assert "float rotation" in header

    for source in (binja_sync, ida_sync):
        assert "g_render_queue_active" in source
        assert "g_font_text_buffer" in source
        assert "g_font_queue" in source
        assert "g_font3d_bods" in source
        assert "g_font3d_scales" in source
        assert "g_font_sheets" in source
        assert "g_registered_font_count" in source
        assert "measure_font_text_width" in source
        assert "register_font_texture_sheet" in source
        assert "draw_font_text_instance" in source
        assert "draw_queued_font_quad_instance" in source
        assert "draw_font_text_queue" in source
        assert "queue_font_text_instance" in source
        assert "queue_axis_aligned_textured_quad" in source
        assert "queue_axis_aligned_textured_quad_uv" in source
        assert "queue_textured_quad_corners" in source
        assert "layout_and_queue_wrapped_font_text" in source
        assert "initialize_font3d_objects" in source

    assert '("0x7544e8", "cFontPrintBuffer[0x400]")' in binja_sync
    assert '("0x7754e8", "BodBase[0x80]")' in binja_sync
    assert '("0x7770e8", "float[0x80]")' in binja_sync
    assert '("0x7772f8", "FontSheet[0x1]")' in binja_sync
    assert '("0x6c", "color", "tColour")' in binja_sync
    assert '("0x7c", "blend_mode", "int32_t")' in binja_sync
    assert '("0x80", "rotation", "float")' in binja_sync
    assert "float __cdecl measure_font_text_width" in binja_sync
    assert "float width_scale, float height_scale" in binja_sync
    assert "void __cdecl initialize_font3d_objects(int16_t font_id)" in binja_sync
    assert "void __cdecl draw_font_text_queue(uint32_t render_mask)" in binja_sync
    assert "void __cdecl queue_font_text_instance" in binja_sync
    assert "int32_t __cdecl queue_axis_aligned_textured_quad" in binja_sync
    assert "int32_t __cdecl queue_textured_quad_corners" in binja_sync
    assert "float* __cdecl layout_and_queue_wrapped_font_text" in binja_sync
    assert "cFontPrintBuffer g_font_queue[0x400];" in ida_sync
    assert "FontSheet g_font_sheets[1];" in ida_sync

    references = json.loads(
        (repo_root / "analysis/symbols/gameplay-references.json").read_text(
            encoding="utf-8"
        )
    )
    by_address = {
        int(entry["address"], 0): entry for entry in references["symbols"]
    }
    assert by_address[0x753CE8]["name"] == "g_font_text_buffer"
    assert by_address[0x7544E8]["name"] == "g_font_queue"
    assert by_address[0x7754E8]["name"] == "g_font3d_bods"
    assert by_address[0x7770E8]["name"] == "g_font3d_scales"
    assert by_address[0x7772F8]["name"] == "g_font_sheets"


def test_frontend_bridge_root_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    matcher_header = (repo_root / "tools/match/include/game_root.h").read_text(
        encoding="utf-8"
    )
    binja_header = (HEADER_DIR / "bn_frame_renderer_types.h").read_text(
        encoding="utf-8"
    )
    ida_header = (HEADER_DIR / "frame_renderer_types.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (BINJA_DIR / "sync_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    overlay_sync = (BINJA_DIR / "sync_overlay_types.py").read_text(
        encoding="utf-8"
    )
    object_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    root_catalog_sync = (
        BINJA_DIR / "sync_root_bod_catalog_types.py"
    ).read_text(encoding="utf-8")
    intro_sync = (BINJA_DIR / "sync_intro_types.py").read_text(encoding="utf-8")
    logo_sync = (BINJA_DIR / "sync_logo_types.py").read_text(encoding="utf-8")
    star_sync = (BINJA_DIR / "sync_star_manager_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )

    assert "TransformMatrix completion_handoff_transform; // +0x1a8" in matcher_header
    for header in (binja_header, ida_header):
        assert "FrameTransformMatrix completion_handoff_transform;" in header
        assert "typedef struct FrameBorderManager" in header
        assert "void* vtable;" in header
        assert "uint32_t list_flags;" in header
        assert "void* list_prev;" in header
        assert "void* list_next;" in header
        assert "uint8_t unknown_000010[0x435b0 - 0x10];" in header
        assert "float justify_centre;" in header
        assert "int32_t unknown_000b48;" in header
        assert "FrameBorderManager border_manager;" in header
        assert "uint8_t unknown_044100[0x74618 - 0x44100];" in header
        assert "unknown_000b48[0x74618 - 0xb48]" not in header

    assert "typedef struct FrameRenderableBod" in ida_header
    assert "typedef struct FrameOverlay" in ida_header
    assert "FrameOverlay overlay_0;" in ida_header
    assert "FrameOverlay overlay_1;" in ida_header
    assert "FrameOverlay overlay_2;" in ida_header
    assert "uint8_t unknown_00067c[0xb24 - 0x67c];" not in ida_header

    assert '("0x4df904", "GameRoot*")' in binja_sync
    assert (
        '("0x1a8", "completion_handoff_transform", "FrameTransformMatrix")'
        in binja_sync
    )
    assert '"FrameBorderManager",' in binja_sync
    assert '("0xb48", "unknown_000b48", "int32_t")' in binja_sync
    assert '("0xb4c", "border_manager", "FrameBorderManager")' in binja_sync
    assert 'BORDER_MANAGER_FIELD_UPDATES = (' in binja_sync
    assert '("0x08", "list_prev", "FrontendWidget*")' in binja_sync
    assert '("0x0c", "list_next", "FrontendWidget*")' in binja_sync
    assert '("0x435b0", "justify_centre", "float")' in binja_sync
    assert "def resolved_border_manager_struct_name" in binja_sync
    assert 'struct_name="BorderManager"' in binja_sync
    assert 'else "FrameBorderManager"' in binja_sync
    assert "0x4DF904" in ida_sync
    assert '"GameRoot *g_game_base;"' in ida_sync
    assert (
        '"FrontendWidget *__thiscall allocate_border(FrameBorderManager *manager);"'
        in ida_sync
    )
    assert "0x4df904" not in overlay_sync.lower()
    for field_update in (
        '("0x67c", "overlay_0", "Overlay")',
        '("0x7c8", "overlay_1", "Overlay")',
        '("0x914", "overlay_2", "Overlay")',
    ):
        assert field_update in overlay_sync
    assert "apply_struct_and_proto_updates" in overlay_sync
    assert 'DirectXLoader directx_loader; // +0x48e00' in matcher_header
    assert '("0x48e00", "directx_loader", "DirectXLoader")' in object_sync
    assert "apply_struct_and_proto_updates" in object_sync
    assert 'RootBodCatalog root_bod_catalog; // +0x44100' in matcher_header
    assert (
        '("0x44100", "root_bod_catalog", "RootBodCatalog")'
        in root_catalog_sync
    )
    assert "apply_struct_and_proto_updates" in root_catalog_sync
    for owner, sync_source in (
        ('("0x4f2dc", "intro", "Intro")', intro_sync),
        ('("0x4f33c", "star_manager", "StarManager")', star_sync),
        ('("0x4f400", "logo", "Logo")', logo_sync),
    ):
        assert owner in sync_source
        assert "apply_struct_and_proto_updates" in sync_source
    assert "types_declare_missing_only" in intro_sync
    assert "types_declare(" not in intro_sync
    assert "types_declare_missing_only" in logo_sync
    assert "types_declare(" not in logo_sync
    assert not (repo_root / "tools/match/include/app_shell.h").exists()
    assert "TransformMatrix transform;" in path_header
    assert "uint8_t transform[0x40];" not in path_header

    update_source = (
        repo_root / "tools/match/scratches/update_subgoldy/scratch.cpp"
    ).read_text(encoding="utf-8")
    resurrect_source = (
        repo_root / "tools/match/scratches/update_subgoldy_resurrect/scratch.cpp"
    ).read_text(encoding="utf-8")
    for source in (update_source, resurrect_source):
        assert "extern GameRoot* g_game;" in source
        assert "g_game->players[0].frontend_state" in source
        assert "g_app" not in source
        assert "AppShell" not in source

    assert "g_game->players[0].completion_handoff_transform =" in update_source
    assert "completion_handoff_transform.position.y" in update_source
    assert "g_game->players[0].redispatch_requested" in update_source
    assert "route_app->players[0].high_score_entry_pending" in resurrect_source


def test_cut_scene_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    matcher_header = (repo_root / "tools/match/include/cut_scene.h").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    constants = (
        "CUT_SCENE_STATE_INACTIVE = 0",
        "CUT_SCENE_STATE_INTRO_PENDING = 1",
        "CUT_SCENE_STATE_INTRO_ACTIVE = 2",
        "CUT_SCENE_STATE_COMPLETION_PENDING = 5",
        "CUT_SCENE_STATE_COMPLETION_BLEND = 6",
        "CUT_SCENE_STATE_COMPLETION_HOLD = 7",
        "CUT_SCENE_STATE_INTRO_RETURN_BLEND = 8",
        "CUT_SCENE_STATE_INTRO_FINISH = 9",
        "CUT_SCENE_STATE_DEATH_PENDING = 10",
        "CUT_SCENE_STATE_DEATH_BLEND = 11",
        "CUT_SCENE_STATE_DEATH_HOLD = 12",
    )
    for header in (matcher_header, analysis_header):
        assert "CutSceneState state" in header
        for constant in constants:
            assert constant in header
    assert '"CutSceneState",' in binja_sync
    assert '("0x0c", "state", "CutSceneState")' in binja_sync
    assert '"--cut-scene-only"' in binja_sync
    assert "updates=CUT_SCENE_PROTO_UPDATES" in binja_sync

    consumers = {
        "initialize_cutscene_ai": "CUT_SCENE_STATE_INACTIVE",
        "initialize_subgoldy": "CUT_SCENE_STATE_INTRO_PENDING",
        "update_subgame_camera": "CUT_SCENE_STATE_INACTIVE",
        "initialize_cutscene": "CUT_SCENE_STATE_INACTIVE",
        "handle_subgoldy_collisions": "CUT_SCENE_STATE_DEATH_PENDING",
        "update_subgoldy": "CUT_SCENE_STATE_COMPLETION_PENDING",
        "update_cutscene": "CUT_SCENE_STATE_DEATH_HOLD",
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


def test_click_start_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/click_start.h").read_text(
        encoding="utf-8"
    )

    assert '"ClickStartState",' in path_sync
    assert '("0x80", "state", "ClickStartState")' in path_sync
    assert '("0x98", "owner_player", "Player*")' in path_sync
    assert '("ClickStart", CLICK_START_FIELD_UPDATES)' in path_sync
    for header in (analysis_header, matcher_header):
        assert "CLICK_START_STATE_INACTIVE = 0" in header
        assert "CLICK_START_STATE_UNKNOWN_1 = 1" in header
        assert "CLICK_START_STATE_WAITING_FOR_START = 2" in header
        assert "CLICK_START_STATE_START_PENDING = 3" in header
        assert "CLICK_START_STATE_TEARDOWN = 4" in header

    consumers = {
        "initialize_click_start": "CLICK_START_STATE_WAITING_FOR_START",
        "update_click_start": "CLICK_START_STATE_UNKNOWN_1",
        "update_subgame": "CLICK_START_STATE_WAITING_FOR_START",
        "update_subgoldy": "CLICK_START_STATE_TEARDOWN",
        "remove_subgame_bods": "CLICK_START_STATE_INACTIVE",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_nuke_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/nuke.h").read_text(
        encoding="utf-8"
    )

    assert '"NukeState",' in path_sync
    assert '("0x00", "state", "NukeState")' in path_sync
    assert '("Nuke", NUKE_FIELD_UPDATES)' in path_sync
    for header in (analysis_header, matcher_header):
        assert "NUKE_STATE_INACTIVE = 0" in header
        assert "NUKE_STATE_ACTIVE = 1" in header

    consumers = {
        "initialize_subgoldy": "NUKE_STATE_INACTIVE",
        "initialize_nuke": "NUKE_STATE_ACTIVE",
        "update_nuke": "NUKE_STATE_ACTIVE",
        "uninit_nuke": "NUKE_STATE_INACTIVE",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_sub_hover_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/sub_hover.h").read_text(
        encoding="utf-8"
    )

    assert '"SubHoverState",' in path_sync
    assert '("0x0c", "state", "SubHoverState")' in path_sync
    for header in (analysis_header, matcher_header):
        assert "SUB_HOVER_STATE_INACTIVE = 0" in header
        assert "SUB_HOVER_STATE_ACTIVE = 1" in header

    consumers = {
        "initialize_jetpack_gauge": "SUB_HOVER_STATE_INACTIVE",
        "arm_jetpack_gauge": "SUB_HOVER_STATE_ACTIVE",
        "end_jetpack_hover": "SUB_HOVER_STATE_ACTIVE",
        "update_jetpack_gauge": "SUB_HOVER_STATE_INACTIVE",
        "update_jet_particles": "SUB_HOVER_STATE_ACTIVE",
        "update_track_attachment_follow_state": "SUB_HOVER_STATE_ACTIVE",
        "calc_subgame_rate": "SUB_HOVER_STATE_ACTIVE",
        "update_subgoldy": "SUB_HOVER_STATE_ACTIVE",
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


def test_previewed_batch_can_transactionally_undefine_an_exact_symbol() -> None:
    code = _narrow_sync._batch_python_code(
        [
            {
                "op": "undefine_symbol",
                "address": "0x5000fc",
                "expected_name": "g_object_index_buffer_factory",
            }
        ],
        preview=True,
    )

    assert "bv.undefine_user_symbol(symbol)" in code
    assert "refusing to undefine unexpected symbol" in code
    assert 'entry["verified"] = observed is None' in code
    assert "bv.revert_undo_actions(state)" in code


def test_previewed_batch_can_transactionally_set_a_user_variable() -> None:
    code = _narrow_sync._batch_python_code(
        [
            {
                "op": "user_var_set",
                "identifier": "draw_frontend_widget",
                "source_type": "RegisterVariableSourceType",
                "index": 0,
                "storage": 67,
                "variable_name": "widget",
                "variable_type": "FrontendWidget*",
            }
        ],
        preview=True,
    )

    assert "function.create_user_var(variable, expected_type, expected_name)" in code
    assert '"user_defined": bool(function.is_var_user_defined(variable))' in code
    assert 'str(variable.source_type).split(".")[-1] == expected_source' in code
    assert 'entry["verified"] = observed == entry["expected"]' in code
    assert "bv.revert_undo_actions(state)" in code


def test_user_variable_replay_skips_apply_when_current(monkeypatch) -> None:
    calls = []

    def fake_run_bn_batch(_repo_root, *, target, operations, preview):
        calls.append((target, operations, preview))
        return {
            "success": True,
            "preview": preview,
            "committed": not preview,
            "affected_functions": ["draw_frontend_widget"],
            "results": [{"changed": False}],
        }

    monkeypatch.setattr(_narrow_sync, "run_bn_batch", fake_run_bn_batch)
    result = _narrow_sync.apply_user_var_updates(
        Path("."),
        target="snail-mail.exe",
        updates=(
            (
                "draw_frontend_widget",
                "RegisterVariableSourceType",
                0,
                67,
                "widget",
                "FrontendWidget*",
            ),
        ),
    )

    assert len(calls) == 1
    assert calls[0][2] is True
    assert result[0]["status"] == "skipped"
    assert result[0]["reason"] == "already current"


def test_user_variable_replay_previews_before_apply(monkeypatch) -> None:
    calls = []

    def fake_run_bn_batch(_repo_root, *, target, operations, preview):
        calls.append((target, operations, preview))
        return {
            "success": True,
            "preview": preview,
            "committed": not preview,
            "message": "ok",
            "affected_functions": ["draw_frontend_widget"],
            "results": [{"changed": True}],
        }

    monkeypatch.setattr(_narrow_sync, "run_bn_batch", fake_run_bn_batch)
    result = _narrow_sync.apply_user_var_updates(
        Path("."),
        target="snail-mail.exe",
        updates=(
            (
                "draw_frontend_widget",
                "RegisterVariableSourceType",
                0,
                67,
                "widget",
                "FrontendWidget*",
            ),
        ),
    )

    assert [preview for _target, _operations, preview in calls] == [True, False]
    assert result[0]["op"] == "user_var_batch"
    assert result[0]["operation_count"] == 1


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


def test_segment_cache_and_generate_level_void_abis_are_persisted() -> None:
    track_sync = (BINJA_DIR / "sync_track_render_cache_types.py").read_text(
        encoding="utf-8"
    )
    runtime_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_runtime_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_runtime_runner = (IDA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")

    expected = (
        "void __thiscall initialize_track_render_cache_manager(SegmentCache* manager)",
        "void __thiscall build_track_render_caches(SegmentCache* manager, tColour skirt_color)",
        "void __thiscall rebuild_track_runtime_from_segments(SubgameRuntime* runtime, int32_t level_index)",
    )
    assert expected[0] in track_sync
    assert expected[1] in track_sync
    assert expected[2] in runtime_sync
    assert "DEFERRED_PROTO_UPDATES = (" in track_sync
    assert "report_deferred_prototypes" in track_sync
    direct_track_prototypes = track_sync.split("\nPROTO_UPDATES = (", 1)[1].split(
        "\n)\n\n\ndef report_deferred_prototypes", 1
    )[0]
    deferred_track_prototypes = track_sync.split(
        "DEFERRED_PROTO_UPDATES = (", 1
    )[1].split("\n)\n\nPROTO_UPDATES", 1)[0]
    assert "initialize_track_render_cache_manager" in direct_track_prototypes
    assert "build_track_render_caches" not in direct_track_prototypes
    assert "build_track_render_caches" in deferred_track_prototypes
    assert expected[0] + ";" in ida_path_sync
    assert expected[1] + ";" in ida_path_sync
    assert (
        "void __thiscall rebuild_track_runtime_from_segments(SubgameRuntime* game, int32_t level_index);"
        in ida_path_sync
    )
    assert (
        "void __thiscall rebuild_track_runtime_from_segments(SubgameRuntime* game, int32_t level_index);"
        in ida_runtime_sync
    )
    assert (
        'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"'
        in ida_runtime_runner
    )
    assert "REQUIRED_CANONICAL_OWNER_MARKERS = (" in ida_runtime_sync
    for marker in (
        "SegmentCache segment_cache;",
        "TrackRowCell runtime_cells[3200][8];",
        "SubRow runtime_rows[3200];",
    ):
        assert marker in ida_runtime_sync
    assert "noncanonical_subgame_runtime_header" in ida_runtime_sync
    assert expected[0] + ";" in header
    assert expected[1].split("(SegmentCache", 1)[0] in header
    assert "void __thiscall rebuild_track_runtime_from_segments(" in header

    for stale in (
        "void* __thiscall initialize_track_render_cache_manager",
        "int32_t __thiscall build_track_render_caches",
        "int32_t __thiscall rebuild_track_runtime_from_segments",
    ):
        assert stale not in track_sync
        assert stale not in runtime_sync
        assert stale not in ida_path_sync
        assert stale not in header


def test_frontend_lifecycle_void_abis_and_loading_owner_are_persisted() -> None:
    repo_root = Path(__file__).parents[1]
    frame_sync = (BINJA_DIR / "sync_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    runtime_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    menu_sync = (BINJA_DIR / "sync_frontend_menu_types.py").read_text(
        encoding="utf-8"
    )
    logo_sync = (BINJA_DIR / "sync_logo_types.py").read_text(encoding="utf-8")
    loading_sync = (BINJA_DIR / "sync_loading_bar_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_frame_sync = (IDA_DIR / "apply_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    ida_logo_sync = (IDA_DIR / "apply_logo_types.py").read_text(encoding="utf-8")
    ida_logo_runner = (IDA_DIR / "sync_logo_types.py").read_text(encoding="utf-8")
    path_header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")
    loading_header = (HEADER_DIR / "bn_loading_bar_types.h").read_text(
        encoding="utf-8"
    )
    matcher_border_header = (
        repo_root / "tools/match/include/border_manager.h"
    ).read_text(encoding="utf-8")

    assert '"kill_all_borders"' in frame_sync
    assert "void __thiscall kill_all_borders" in frame_sync
    assert "void __thiscall kill_all_borders" in ida_frame_sync
    assert '"set_border_justify_centre"' in frame_sync
    assert "void __thiscall set_border_justify_centre" in frame_sync
    assert "float justify_centre" in frame_sync
    assert "void __thiscall set_border_justify_centre" in ida_frame_sync
    assert "float justify_centre" in ida_frame_sync
    assert "void __thiscall destroy_help_screen(Help* help)" in runtime_sync
    assert "void __thiscall destroy_options_menu(Options* options)" in menu_sync
    assert "void __thiscall destroy_intro_screen(Logo* logo)" in logo_sync
    assert "void __thiscall destroy_intro_screen(Logo* logo);" in ida_logo_sync
    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/logo_types.h"' in ida_logo_runner
    assert 'IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/apply_logo_types.py"' in ida_logo_runner

    for prototype in (
        "void __thiscall initialize_loading_screen(LoadingBar* loading_bar)",
        "void __thiscall destroy_loading_screen(LoadingBar* loading_bar)",
        "void __thiscall update_loading_screen(LoadingBar* loading_bar)",
    ):
        assert prototype in loading_sync
        assert prototype + ";" in ida_path_sync

    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_loading_bar_types.h"' in loading_sync
    assert 'struct_name="LoadingBar"' in loading_sync
    assert 'replace_types=("LoadingBar",)' in loading_sync
    assert '("0x503290", "g_loading_bar")' in loading_sync
    assert '("0x503290", "LoadingBar")' in loading_sync
    assert "typedef struct LoadingBar" in loading_header
    assert "typedef struct LoadingBar" in path_header
    assert "typedef struct Options" in path_header
    assert "LoadingBar g_loading_bar;" in ida_path_sync
    loading_notes = (
        repo_root / "tools/match/scratches/initialize_loading_screen/NOTES.md"
    ).read_text(encoding="utf-8")
    for address, wrapper, cleanup in (
        ("0x4533C4", "d3dx_create_texture_from_file_in_memory_ex", "0x3c"),
        ("0x453404", "d3dx_create_texture_from_file_ex", "0x38"),
        ("0x453467", "d3dx_create_texture_from_file", "0x0c"),
    ):
        assert f'"{wrapper}"' in ida_path_sync
        assert f'({address}, "{wrapper}")' in ida_path_sync
        assert f"int32_t __stdcall {wrapper}" in ida_path_sync
        assert f"int32_t __stdcall {wrapper}" in path_header
        assert cleanup in loading_notes

    for stale in (
        "char* __thiscall destroy_options_menu",
        "int32_t __thiscall destroy_intro_screen",
        "int32_t __thiscall initialize_loading_screen",
        "int32_t __thiscall destroy_loading_screen",
        "int32_t __thiscall update_loading_screen",
    ):
        assert stale not in menu_sync
        assert stale not in logo_sync
        assert stale not in loading_sync
        assert stale not in ida_path_sync
        assert stale not in ida_logo_sync

    # kill_border has a separate VC6 recursion-shape constraint and is not
    # widened into this lifecycle proof.
    assert "int kill_border(FrontendWidget* border);" in matcher_border_header
    assert "void set_border_justify_centre(" in matcher_border_header
    assert "float justify_centre);" in matcher_border_header
    assert "int set_border_justify_centre" not in matcher_border_header
    assert "justify_centre_bits" not in matcher_border_header
    assert '"kill_border",' not in frame_sync


def test_challenge_gui_owner_and_void_initializer_are_persisted() -> None:
    binja_header = (HEADER_DIR / "bn_subgame_runtime_types.h").read_text(
        encoding="utf-8"
    )
    ida_header = (HEADER_DIR / "ida_subgame_runtime_types.h").read_text(
        encoding="utf-8"
    )
    ida_canonical_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_runner = (IDA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )

    for header in (binja_header, ida_header, ida_canonical_header):
        assert "typedef struct GUI" in header
        assert "SubgameRuntime* game;" in header
        for field in (
            "next_level_button",
            "previous_level_button",
            "level_name_widget",
            "play_button",
            "back_button",
            "speed_slider",
            "difficulty_slider",
            "replay_button",
        ):
            assert f"FrontendWidget* {field};" in header

    assert "GUI_FIELD_UPDATES = (" in binja_sync
    assert '("0x00", "game", "SubgameRuntime*")' in binja_sync
    assert '("0x24", "replay_button", "FrontendWidget*")' in binja_sync
    assert "void __thiscall initialize_challenge_setup_screen(GUI* gui)" in binja_sync
    assert "void __thiscall initialize_challenge_setup_screen(GUI* gui);" in ida_sync
    assert "int __thiscall initialize_challenge_setup_screen" not in ida_sync
    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"' in ida_runner
