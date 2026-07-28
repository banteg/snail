import importlib.util
import json
from pathlib import Path
from types import SimpleNamespace

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
    ida_runtime_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/galaxy_route_types.h"
    ).read_text(encoding="utf-8")
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
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
    assert "void __thiscall draw_galaxy_line(Galaxy* galaxy," in runtime_sync
    assert "int32_t __thiscall draw_galaxy_line(Galaxy* galaxy," not in runtime_sync
    assert "void __thiscall open_galaxy_route(" in runtime_sync
    assert "void __thiscall galaxy_border_bound(" in runtime_sync
    assert "GALAXY_ROUTE_CURSOR_EXPECTED_SIZES" in runtime_sync
    assert '"GalaxyStar": 0x2A0' in runtime_sync
    assert '"Galaxy": 0x10FA8' in runtime_sync
    assert "GALAXY_ROUTE_CURSOR_USER_VAR_UPDATES" in runtime_sync
    assert (
        '"update_galaxy",\n'
        '        "RegisterVariableSourceType",\n'
        "        40,\n"
        "        69,\n"
        '        "route_slot_cursor",\n'
        '        "GalaxyStar*",'
    ) in runtime_sync
    assert "remove_user_var_updates" in runtime_sync
    assert "REJECTED_GALAXY_HIGHLIGHT_RESET_CURSOR_REMOVALS" in runtime_sync
    assert (
        '"update_galaxy",\n'
        '        "RegisterVariableSourceType",\n'
        "        1086,\n"
        "        67,\n"
        '        "highlight_reset_cursor",\n'
        '        "float*",'
    ) in runtime_sync
    assert (
        '"update_galaxy",\n'
        '        "RegisterVariableSourceType",\n'
        "        1352,\n"
        "        73,\n"
        '        "highlight_target_cursor",\n'
        '        "float*",'
    ) in runtime_sync
    assert "--galaxy-route-cursor-only" in runtime_sync
    assert "if args.galaxy_route_cursor_only:" in runtime_sync
    assert "require_galaxy_route_cursor_dependencies" in runtime_sync
    assert (
        '"struct GalaxyStar* route_slot_cursor = &galaxy->route_slots"'
        in health_checks
    )
    assert (
        '"update_galaxy_route_record(route_slot_cursor)"' in health_checks
    )
    assert '"star->record.route_tint_alpha"' in health_checks
    assert (
        '"void __thiscall update_galaxy_route_record(GalaxyStar *star)"'
        in health_checks
    )
    assert (
        '"float* highlight_target_cursor = '
        '&galaxy->route_slots[1].record.highlight_target"'
    ) in health_checks
    assert (
        '"int32_t* edi_2 = '
        '&galaxy->route_slots[1].record.highlight_target"'
    ) in health_checks
    assert '"struct GalaxyStar (*"' in health_checks

    for declaration in (
        "GalaxyRouteNameRecord* __thiscall initialize_galaxy_route_name_record(",
        "void __thiscall load_galaxy_layout(Galaxy* galaxy);",
        "void __thiscall destroy_galaxy(Galaxy* galaxy);",
        "void __thiscall initialize_galaxy(Galaxy* galaxy);",
        "int32_t __thiscall update_galaxy(Galaxy* galaxy);",
        "void __thiscall draw_galaxy_line(Galaxy* galaxy,",
        "void __thiscall update_galaxy_route_record(GalaxyStar* star);",
        "void __thiscall close_galaxy_route(Galaxy* galaxy);",
        "void __thiscall open_galaxy_route(Galaxy* galaxy,",
        "void __thiscall galaxy_border_bound(Galaxy* galaxy,",
    ):
        assert declaration in ida_runtime_sync
    assert "GalaxyPoint g_galaxy_group_points[10];" in ida_runtime_sync
    assert "GalaxyPoint g_galaxy_route_points[101];" in ida_runtime_sync
    assert "TRUSTED_DATA_DECLARATIONS" in ida_runtime_sync
    assert "GALAXY_ROUTE_POINT_OWNER_ADDRESS = 0x4A1D14" in ida_runtime_sync
    assert "GALAXY_ROUTE_POINT_OWNER_SIZE = 0x328" in ida_runtime_sync
    assert "GALAXY_ROUTE_POINT_NEXT_OWNER_ADDRESS = 0x4A203C" in ida_runtime_sync
    assert "GALAXY_OWNER_EXPECTED_SIZES" in ida_runtime_sync
    assert '"GalaxyStar": 0x2A0' in ida_runtime_sync
    assert '"Galaxy": 0x10FA8' in ida_runtime_sync
    assert '"GalaxyStar": _named_struct_size("GalaxyStar")' in ida_runtime_sync
    for stale_address, stale_name in (
        ("0x4A1D18", "g_galaxy_initial_map_y_bits"),
        ("0x4A1D1C", "g_galaxy_missing_level_map_x_table"),
        ("0x4A1D20", "g_galaxy_missing_level_map_y_table"),
    ):
        assert f'({stale_address}, "{stale_name}")' in ida_runtime_sync
    assert "_sync_galaxy_route_point_owner()" in ida_runtime_sync
    assert "_is_auto_data_name(interior_address, name)" in ida_runtime_sync
    assert "ida_name.del_global_name(" in ida_runtime_sync
    assert "ida_bytes.del_items(address, ida_bytes.DELIT_SIMPLE, size)" in (
        ida_runtime_sync
    )
    assert "0x4088E0,  # load_galaxy_layout" in ida_runtime_sync

    for header in analysis_headers:
        assert "typedef struct GalaxyPoint" in header
        assert "GalaxyStar route_slots[101]" in header
        assert "GalaxyRouteNameRecord route_names[10]" in header

    assert "extern GalaxyPoint g_galaxy_group_points[10];" in matcher_header
    assert "extern GalaxyPoint g_galaxy_route_points[101];" in matcher_header
    assert "void draw_galaxy_line(" in matcher_header
    assert "int draw_galaxy_line(" not in matcher_header


def test_mobile_galaxy_and_backdrop_evidence_preserves_windows_abi_boundaries() -> None:
    repo_root = Path(__file__).parents[1]
    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    functions_by_address = {
        entry["address"]: entry for entry in functions["functions"]
    }
    crosswalk_by_address = {
        entry["address"]: entry for entry in crosswalk["entries"]
    }

    assert "cRGalaxy_Line" in functions_by_address["0x409b00"]["aliases"]
    assert (
        crosswalk_by_address["0x409b00"]["android_symbol"]
        == "cRGalaxy::Line(int, float, float, float, float, float, tColour&)"
    )
    assert "ios_symbol" not in crosswalk_by_address["0x409b00"]
    assert (
        crosswalk_by_address["0x409bd0"]["android_symbol"]
        == "cRGalaxyStar::AI()"
    )
    assert "ios_symbol" not in crosswalk_by_address["0x409bd0"]
    assert "same 0x2a0 stride" in crosswalk_by_address["0x409bd0"]["notes"]

    for address, alias, symbol in (
        ("0x410d50", "cRBackdrop_Change", "cRBackdrop::Change(cRLandscape*, bool)"),
        ("0x410dc0", "cRBackdrop_ChangeReal", "cRBackdrop::ChangeReal()"),
        ("0x410e20", "cRBackdrop_Init", "cRBackdrop::Init(int)"),
        ("0x4112f0", "cRBackdrop_AI", "cRBackdrop::AI()"),
    ):
        assert alias in functions_by_address[address]["aliases"]
        assert crosswalk_by_address[address]["android_symbol"] == symbol

    assert (
        crosswalk_by_address["0x410d50"]["ios_symbol"]
        == "cRBackdrop::Change(cRLandscape*, bool)"
    )
    assert (
        crosswalk_by_address["0x410dc0"]["ios_symbol"]
        == "cRBackdrop::ChangeReal()"
    )
    assert "ios_symbol" not in crosswalk_by_address["0x410e20"]

    galaxy_header = (
        repo_root / "tools/match/include/galaxy_route_types.h"
    ).read_text(encoding="utf-8")
    assert "class GalaxyStar" in galaxy_header
    assert "typedef GalaxyStar GalaxyRouteSlot;" in galaxy_header
    backdrop_header = (repo_root / "tools/match/include/backdrop.h").read_text(
        encoding="utf-8"
    )
    font_header = (repo_root / "tools/match/include/font_system.h").read_text(
        encoding="utf-8"
    )
    assert "void draw_galaxy_line(" in galaxy_header
    assert "int update_backdrop();" in backdrop_header
    assert "int draw_split_backdrop();" in backdrop_header
    assert "int queue_axis_aligned_textured_quad(" in font_header
    assert "int queue_axis_aligned_textured_quad_uv(" in font_header
    assert "int queue_textured_quad_corners(" in font_header


def test_mobile_landscape_evidence_recovers_authored_lifecycle() -> None:
    repo_root = Path(__file__).parents[1]
    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    functions_by_address = {
        entry["address"]: entry for entry in functions["functions"]
    }
    crosswalk_by_address = {
        entry["address"]: entry for entry in crosswalk["entries"]
    }

    expected = (
        (
            "0x4182e0",
            "cRLandscapeManager_Open",
            "cRLandscapeManager::Open()",
        ),
        (
            "0x4182f0",
            "cRLandscapeManager_Import",
            "cRLandscapeManager::Import(char*)",
        ),
        (
            "0x418870",
            "cRLandscapeManager_Init",
            "cRLandscapeManager::Init(int)",
        ),
        (
            "0x418a30",
            "cRLandscapeManager_UnInit",
            "cRLandscapeManager::UnInit()",
        ),
    )
    for address, alias, mobile_symbol in expected:
        assert alias in functions_by_address[address]["aliases"]
        assert crosswalk_by_address[address]["android_symbol"] == mobile_symbol
        assert crosswalk_by_address[address]["ios_symbol"] == mobile_symbol
        assert crosswalk_by_address[address]["source_object"] == "Landscape.o"
        assert crosswalk_by_address[address]["confidence"] == "high"

    assert "mobile-only SpaceRed" in crosswalk_by_address["0x4182e0"]["notes"]
    assert "0x124-byte DirectX record" in (
        crosswalk_by_address["0x4182f0"]["notes"]
    )
    assert "ten repeated DirectX BOD slices" in (
        crosswalk_by_address["0x418870"]["notes"]
    )
    assert "Both mobile UnInit bodies are empty" in (
        crosswalk_by_address["0x418a30"]["notes"]
    )


def test_mobile_finalizer_high_score_and_tip_lifecycles_are_persisted() -> None:
    repo_root = Path(__file__).parents[1]
    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    functions_by_address = {
        entry["address"]: entry for entry in functions["functions"]
    }
    crosswalk_by_address = {
        entry["address"]: entry for entry in crosswalk["entries"]
    }

    for address, alias, symbol, source_object in (
        ("0x410720", "cRGame_InitLast", "cRGame::InitLast()", "Game.o"),
        (
            "0x417540",
            "cRSubHighScore_Init",
            "cRSubHighScore::Init()",
            "HighScore.o",
        ),
        ("0x4489e0", "cRTip_UnInit", "cRTip::UnInit()", None),
    ):
        assert alias in functions_by_address[address]["aliases"]
        assert crosswalk_by_address[address]["android_symbol"] == symbol
        assert crosswalk_by_address[address]["source_object"] == source_object
        assert crosswalk_by_address[address]["confidence"] == "high"

    assert (
        crosswalk_by_address["0x410720"]["ios_symbol"]
        == "cRGame::InitLast()"
    )
    assert (
        crosswalk_by_address["0x417540"]["ios_symbol"]
        == "cRSubHighScore::Init()"
    )
    assert "ios_symbol" not in crosswalk_by_address["0x4489e0"]
    assert "deliberately not mapped" in (
        crosswalk_by_address["0x417540"]["notes"]
    )
    assert "same cRTip field offsets" in (
        crosswalk_by_address["0x4489e0"]["notes"]
    )

    game_root_header = (repo_root / "tools/match/include/game_root.h").read_text(
        encoding="utf-8"
    )
    sub_high_score_header = (
        repo_root / "tools/match/include/sub_high_score.h"
    ).read_text(encoding="utf-8")
    tip_header = (repo_root / "tools/match/include/tip_manager.h").read_text(
        encoding="utf-8"
    )
    assert "cRGame::InitLast" in game_root_header
    assert "cRSubHighScore::Init" in sub_high_score_header
    assert "cRTip::UnInit" in tip_header


def test_android_root_constructor_recovers_inlined_game_owner() -> None:
    repo_root = Path(__file__).parents[1]
    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    functions_by_address = {
        entry["address"]: entry for entry in functions["functions"]
    }
    crosswalk_by_address = {
        entry["address"]: entry for entry in crosswalk["entries"]
    }

    root_constructor = crosswalk_by_address["0x407b60"]
    assert root_constructor["android_symbol"] == "cRGame::cRGame()"
    assert "ios_symbol" not in root_constructor
    assert root_constructor["source_object"] is None
    assert root_constructor["confidence"] == "high"
    assert "inlined cRGame constructor region" in root_constructor["notes"]
    assert "not to the wrapper's outer authored name" in (
        root_constructor["notes"]
    )
    assert "border manager with 150 records" in root_constructor["notes"]
    assert "128 cached object slots" in root_constructor["notes"]

    description = functions_by_address["0x407b60"]["description"]
    assert "inlined constructor" in description
    assert "wrapper-only work" in description
    assert "aliases" not in functions_by_address["0x407b60"]


def test_dual_mobile_object_geometry_owners_preserve_platform_boundaries() -> None:
    repo_root = Path(__file__).parents[1]
    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    functions_by_address = {
        entry["address"]: entry for entry in functions["functions"]
    }
    crosswalk_by_address = {
        entry["address"]: entry for entry in crosswalk["entries"]
    }

    for address, alias, symbol in (
        (
            "0x4303f0",
            "cRObject_CalcTextureGroups",
            "cRObject::CalcTextureGroups()",
        ),
        (
            "0x4305a0",
            "cRObject_AddEdge",
            "cRObject::AddEdge(int, int, int)",
        ),
        ("0x4308b0", "cRObject_CalcEdges", "cRObject::CalcEdges()"),
    ):
        assert alias in functions_by_address[address]["aliases"]
        entry = crosswalk_by_address[address]
        assert entry["android_symbol"] == symbol
        assert entry["ios_symbol"] == symbol
        assert entry["source_object"] == "RObject.o"
        assert entry["confidence"] == "high"

    assert "separate exact Windows face-reordering helper" in (
        crosswalk_by_address["0x4303f0"]["notes"]
    )
    assert "compact ten-byte index records" in (
        crosswalk_by_address["0x4305a0"]["notes"]
    )
    assert "0x30-byte triangle-or-quad facequads" in (
        crosswalk_by_address["0x4308b0"]["notes"]
    )

    object_header = (
        repo_root / "tools/match/include/object_render_types.h"
    ).read_text(encoding="utf-8")
    for method in (
        "cRObject::CalcTextureGroups",
        "cRObject::AddEdge",
        "cRObject::CalcEdges",
    ):
        assert method in object_header


def test_dual_mobile_texture_registry_recovers_authored_owner_and_record() -> None:
    repo_root = Path(__file__).parents[1]
    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    functions_by_address = {
        entry["address"]: entry for entry in functions["functions"]
    }
    crosswalk_by_address = {
        entry["address"]: entry for entry in crosswalk["entries"]
    }

    for address, alias, symbol in (
        ("0x44e800", "cRTextures_Init", "cRTextures::Init(int)"),
        (
            "0x44e810",
            "cRTextures_Add",
            "cRTextures::Add(char*, cTgaHeader*, int)",
        ),
    ):
        assert alias in functions_by_address[address]["aliases"]
        entry = crosswalk_by_address[address]
        assert entry["android_symbol"] == symbol
        assert entry["ios_symbol"] == symbol
        assert entry["source_object"] == "RTexture.o"
        assert entry["confidence"] == "high"

    init_notes = crosswalk_by_address["0x44e800"]["notes"]
    assert "exact Windows two-store initializer" in init_notes
    assert "port-only tail offset" in init_notes

    add_notes = crosswalk_by_address["0x44e810"]["notes"]
    for field_offset in ("+0x0c", "+0x8c", "+0x98", "+0xa0"):
        assert field_offset in add_notes
    assert "hash table" in add_notes

    sprite_header = (repo_root / "tools/match/include/sprite.h").read_text(
        encoding="utf-8"
    )
    assert "typedef TextureRef cRTexture;" in sprite_header
    assert "typedef TextureRefList cRTextures;" in sprite_header
    assert "cRTextures::Init" in sprite_header
    assert "cRTextures::Add" in sprite_header


def test_dual_mobile_texture_loaders_preserve_renderer_boundaries() -> None:
    repo_root = Path(__file__).parents[1]
    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    functions_by_address = {
        entry["address"]: entry for entry in functions["functions"]
    }
    crosswalk_by_address = {
        entry["address"]: entry for entry in crosswalk["entries"]
    }

    for address, alias, symbol in (
        ("0x412a00", "G0TextureSetLoad", "G0TextureSetLoad(int)"),
        ("0x412a70", "G0TextureLoad", "G0TextureLoad(int, int)"),
    ):
        assert alias in functions_by_address[address]["aliases"]
        entry = crosswalk_by_address[address]
        assert entry["android_symbol"] == symbol
        assert entry["ios_symbol"] == symbol
        assert entry["source_object"] is None
        assert entry["confidence"] == "high"

    set_load_notes = crosswalk_by_address["0x412a00"]["notes"]
    assert "renderer-owned four-byte slot" in set_load_notes
    assert "OpenGL residency bank" in set_load_notes
    assert "Direct3D texture-pointer bank" in set_load_notes

    load_notes = crosswalk_by_address["0x412a70"]["notes"]
    for field_offset in ("+0x0c", "+0x98", "+0x04", "+0x08"):
        assert field_offset in load_notes
    assert "legacy second argument is unread" in load_notes
    assert "Debug.tga fallback" in load_notes


def test_mobile_subgame_utility_evidence_recovers_authored_owners() -> None:
    repo_root = Path(__file__).parents[1]
    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    functions_by_address = {
        entry["address"]: entry for entry in functions["functions"]
    }
    crosswalk_by_address = {
        entry["address"]: entry for entry in crosswalk["entries"]
    }

    expected = (
        (
            "0x437b10",
            "cRSubGame_ReSet",
            "cRSubGame::ReSet()",
            None,
        ),
        (
            "0x437e80",
            "cRSubGame_CalcSliderToRate",
            "cRSubGame::CalcSliderToRate(float)",
            None,
        ),
        (
            "0x43af10",
            "cRSubGoldy_ShowLives",
            "cRSubGoldy::ShowLives()",
            None,
        ),
        (
            "0x43d3d0",
            "cRSubGoldy_GhostDraw",
            "cRSubGoldy::GhostDraw(float)",
            None,
        ),
        (
            "0x43d410",
            "cRSubGame_LocFromPos",
            "cRSubGame::LocFromPos(tVector)",
            "cRSubGame::LocFromPos(tVector)",
        ),
        (
            "0x43d480",
            "cRSubGame_RowFromPos",
            "cRSubGame::RowFromPos(tVector)",
            None,
        ),
        (
            "0x43d4d0",
            "cRSubGame_GetY",
            "cRSubGame::GetY(tVector)",
            "cRSubGame::GetY(tVector)",
        ),
        (
            "0x4403a0",
            "cRSubGoldy_ScoreStatsInit",
            "cRSubGoldy::ScoreStatsInit()",
            "cRSubGoldy::ScoreStatsInit()",
        ),
        (
            "0x4404d0",
            "cRSubGame_CalcRate",
            "cRSubGame::CalcRate()",
            None,
        ),
        (
            "0x4408a0",
            "cRSubGame_BlinkRand",
            "cRSubGame::BlinkRand()",
            None,
        ),
        (
            "0x4408c0",
            "cRSubGame_BlinkRandInit",
            "cRSubGame::BlinkRandInit()",
            "cRSubGame::BlinkRandInit()",
        ),
        (
            "0x445840",
            "cRSubGoldy_Kill",
            "cRSubGoldy::Kill()",
            None,
        ),
        (
            "0x445f10",
            "cRSubGame_HideScores",
            "cRSubGame::HideScores()",
            "cRSubGame::HideScores()",
        ),
        (
            "0x445f40",
            "cRSubGame_UnHideScores",
            "cRSubGame::UnHideScores()",
            None,
        ),
    )
    for address, alias, android_symbol, ios_symbol in expected:
        assert (
            sum(entry["address"] == address for entry in crosswalk["entries"]) == 1
        )
        assert alias in functions_by_address[address]["aliases"]
        assert crosswalk_by_address[address]["android_symbol"] == android_symbol
        if ios_symbol is None:
            assert "ios_symbol" not in crosswalk_by_address[address]
        else:
            assert crosswalk_by_address[address]["ios_symbol"] == ios_symbol

    assert (
        "initialize_score_stats"
        in functions_by_address["0x4403a0"]["aliases"]
    )
    assert (
        "initialize_score_stats"
        not in functions_by_address["0x444960"]["aliases"]
    )
    reset_notes = crosswalk_by_address["0x437b10"]["notes"]
    assert "all five Windows exits" in reset_notes
    assert "platform-specific" in reset_notes
    assert "cRSquidge_Init" in functions_by_address["0x444960"]["aliases"]
    kill_description = functions_by_address["0x445840"]["description"]
    assert "cRSubGoldy::Kill()" in kill_description
    assert "y = -8" in kill_description
    assert "ghost" not in kill_description.lower()

    matcher_header = (
        repo_root / "tools/match/include/subgame_runtime.h"
    ).read_text(encoding="utf-8")
    blink_source = (
        repo_root / "tools/match/scratches/initialize_blink_random/scratch.cpp"
    ).read_text(encoding="utf-8")
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")
    assert "void initialize_blink_random();" in matcher_header
    assert "void SubgameRuntime::initialize_blink_random()" in blink_source
    assert "return result;" not in blink_source
    assert '"00440909        return"' in health_checks
    assert '"return result"' in health_checks
    for health_check_name in (
        "ida_mobile_calc_slider_owner_abi",
        "ida_blink_random_void_owner_abi",
        "ida_hide_gameplay_scores_owner",
        "ida_unhide_gameplay_scores_owner",
    ):
        assert f'"name": "{health_check_name}"' in health_checks

    for source_path in (
        BINJA_DIR / "sync_subgame_runtime_types.py",
        BINJA_DIR / "sync_path_template_types.py",
        IDA_DIR / "apply_subgame_runtime_types.py",
        IDA_DIR / "apply_path_template_types.py",
        HEADER_DIR / "path_template_types.h",
    ):
        source = source_path.read_text(encoding="utf-8")
        assert (
            "float __thiscall calc_slider_to_rate(SubgameRuntime*" in source
        )
        assert (
            "void __thiscall initialize_blink_random(SubgameRuntime*" in source
        )
        assert "void __thiscall hide_gameplay_scores(SubgameRuntime*" in source
        assert (
            "void __thiscall unhide_gameplay_scores(SubgameRuntime*" in source
        )
        assert (
            "int32_t __thiscall initialize_blink_random(SubgameRuntime*"
            not in source
        )


def test_galaxy_layout_lifetime_replay_preserves_borrowed_cursors() -> None:
    repo_root = Path(__file__).parents[1]
    source = (BINJA_DIR / "sync_galaxy_layout_lifetimes.py").read_text(
        encoding="utf-8"
    )
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    for expected in (
        '"tColour": 0x10',
        '"GalaxyPoint": 0x08',
        '"GalaxyRouteNameRecord": 0xA0',
        '"Galaxy": 0x10FA8',
        '0x00: ("name", "char[128]")',
        '0x84: ("color", "tColour")',
        '0x10930: ("route_names", "GalaxyRouteNameRecord[10]")',
        "GALAXY_LAYOUT_USER_VAR_UPDATES",
        "current_struct_fields_batch",
        "apply_user_var_updates",
        "verify_galaxy_layout_owners",
    ):
        assert expected in source

    for index, storage, variable_name, variable_type in (
        (6, 66, "route_point_y_cursor", "float*"),
        (79, 66, "group_point_rescale_y_cursor", "float*"),
        (171, 71, "current_group_point_y_cursor", "float*"),
        (166, 66, "file_text", "char*"),
        (280, 68, "route_name_character_cursor", "char*"),
    ):
        update = (
            '"load_galaxy_layout",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{variable_name}",\n'
            f'        "{variable_type}",'
        )
        assert update in source

    for fragment in (
        "float* route_point_y_cursor = &g_galaxy_route_points[0].y",
        "float* group_point_rescale_y_cursor = &g_galaxy_group_points[0].y",
        "float* current_group_point_y_cursor",
        "char* file_text = load_file_bytes_from_archive_or_fs",
        "char* route_name_character_cursor",
        "*route_name_character_cursor = j",
        "route_name_character_cursor = &route_name_character_cursor[1]",
        '"struct GalaxyRouteNameRecord (* edx_1)[0xa]"',
        '"void* eax_3 = load_file_bytes_from_archive_or_fs"',
    ):
        assert fragment in health_checks


def test_voice_manager_replay_keeps_exact_owners_and_void_mutator_abis() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (BINJA_DIR / "sync_voice_manager_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_voice_manager_types.py").read_text(
        encoding="utf-8"
    )
    ida_runner = (IDA_DIR / "sync_voice_manager_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "voice_manager_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/voice_manager.h").read_text(
        encoding="utf-8"
    )
    references = (repo_root / "analysis/symbols/gameplay-references.json").read_text(
        encoding="utf-8"
    )

    for source in (binja_sync, ida_sync):
        assert "void __thiscall initialize_voice_set(VoiceSet* set, int32_t count)" in source
        assert "void __thiscall shuffle_voice_set(VoiceSet* set)" in source
        assert "void __thiscall initialize_voice_manager(VoiceManager* manager)" in source
        assert "void __thiscall update_voice_manager(VoiceManager* manager)" in source
        assert "bool __thiscall play_voice_manager(VoiceManager* manager" in source
        assert "bool __thiscall play_voice_set(VoiceSet* set" in source
        assert "int32_t __thiscall is_voice_playing(VoiceManager* manager)" in source

    assert '("0x751498", "g_voice_manager")' in binja_sync
    assert '("0x751498", "VoiceManager")' in binja_sync
    assert "VoiceSet sets[16];" in analysis_header
    assert "extern VoiceManager g_voice_manager;" in analysis_header
    assert "void initialize_voice_set(int count);" in matcher_header
    assert "void shuffle_voice_set();" in matcher_header
    assert '"size": "0x188"' in references
    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/voice_manager_types.h"' in ida_runner
    assert "apply_user_var_updates" in binja_sync
    assert "VOICE_MANAGER_USER_VAR_UPDATES" in binja_sync
    assert binja_sync.count('"cooldown_cursor"') == 1
    assert binja_sync.count('"set_cursor"') == 2
    assert '"RegisterVariableSourceType",\n        10,\n        66,' in binja_sync
    assert '"RegisterVariableSourceType",\n        5,\n        72,' in binja_sync
    assert '"RegisterVariableSourceType",\n        8,\n        73,' in binja_sync
    assert "VOICE_MANAGER_LVAR_SPECS" in ida_sync
    assert "VOICE_MANAGER_SPLIT_LVAR_SPECS" in ida_sync
    for definition_address in (
        "0x448ECB",
        "0x448EED",
        "0x448F04",
        "0x448F0D",
        "0x448F0F",
        "0x449082",
        "0x44915A",
        "0x449194",
        "0x4491A8",
        "0x4491E7",
        "0x4492A6",
        "0x449419",
    ):
        assert definition_address in ida_sync
    assert "info.set_split_lvar()" in ida_sync
    assert "split_lvar_readback_failed" in ida_sync


def test_cheat_state_replay_keeps_exact_global_owner_and_authored_abis() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (BINJA_DIR / "sync_cheat_state_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_cheat_state_types.py").read_text(
        encoding="utf-8"
    )
    ida_runner = (IDA_DIR / "sync_cheat_state_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "cheat_state_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/cheat_state.h").read_text(
        encoding="utf-8"
    )
    functions = (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
        encoding="utf-8"
    )
    references = (
        repo_root / "analysis/symbols/gameplay-references.json"
    ).read_text(encoding="utf-8")

    for source in (binja_sync, ida_sync):
        assert "void __thiscall initialize_cheat(CheatState* cheat)" in source
        assert "void __thiscall update_cheat(CheatState* cheat)" in source
        assert (
            "bool __thiscall match_cheat_text(CheatState* cheat, char* text)"
            in source
        )

    assert '("0x4b2f40", "g_cheat_state")' in binja_sync
    assert '("0x4b2f40", "CheatState")' in binja_sync
    assert "apply_user_var_updates" in binja_sync
    assert binja_sync.count('"recent_text_cursor"') == 2
    assert '"RegisterVariableSourceType",\n        33,\n        67,' in binja_sync
    assert '"RegisterVariableSourceType",\n        57,\n        68,' in binja_sync
    assert "CHEAT_STATE_ADDRESS = 0x4B2F40" in ida_sync
    assert "NEXT_OWNER_ADDRESS = 0x4B2F50" in ida_sync
    assert ida_sync.count('"recent_text_cursor"') >= 2
    assert "0x404772" in ida_sync
    assert "0x40480A" in ida_sync
    assert "unexpected_cursor_lvar_candidates" in ida_sync
    assert "cursor_lvar_readback_failed" in ida_sync
    assert "typedef union CheatTextBuffer" in analysis_header
    assert "char bytes[8];" in analysis_header
    assert "CheatTextBuffer recent_text;" in analysis_header
    assert "extern CheatState g_cheat_state;" in analysis_header
    assert "void initialize_cheat();" in matcher_header
    assert "void update_cheat();" in matcher_header
    assert "bool match_cheat_text(char* text);" in matcher_header
    assert "cRCheat::Init()" in functions
    assert '"gCheat"' in references
    assert (
        'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/cheat_state_types.h"'
        in ida_runner
    )


def test_snail_presentation_replay_keeps_exact_snail_weapon_and_subhover_owners() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (BINJA_DIR / "sync_snail_presentation_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_snail_presentation_types.py").read_text(
        encoding="utf-8"
    )
    ida_runner = (IDA_DIR / "sync_snail_presentation_types.py").read_text(
        encoding="utf-8"
    )
    broad_binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    broad_ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    sprite_header = (HEADER_DIR / "star_manager_types.h").read_text(
        encoding="utf-8"
    )
    matcher_invincible = (
        repo_root / "tools/match/include/invincible.h"
    ).read_text(encoding="utf-8")
    matcher_player = (repo_root / "tools/match/include/player.h").read_text(
        encoding="utf-8"
    )

    for source in (
        binja_sync,
        ida_sync,
        broad_binja_sync,
        broad_ida_sync,
        analysis_header,
    ):
        assert "void __thiscall release_snail_weapons(Snail* snail)" in source
        assert (
            "void __thiscall extract_snail_local_hotspots(Snail* snail)"
            in source
        )
        assert (
            "void __thiscall build_snail_world_hotspots(Snail* snail)"
            in source
        )
        assert (
            "void __thiscall dispatch_cutscene_animation(Snail* snail, "
            "int32_t animation_id, uint8_t immediate, int32_t mode_flags)"
            in source
        )
        assert (
            "void __thiscall set_weapon_animation(Weapon* weapon, "
            "int32_t animation_id, uint8_t immediate, int32_t mode_flags)"
            in source
        )
        assert (
            "void __thiscall set_snail_jetpack(Snail* snail, int32_t state)"
            in source
        )
        for declaration in (
            "void __thiscall initialize_invincible_shell(Invincible* invincible)",
            "void __thiscall start_invincible_shell(Invincible* invincible)",
            "void __thiscall update_invincible_shell(Invincible* invincible)",
            "void __thiscall initialize_snail_skin(SnailSkin* snail_skin)",
            "void __thiscall update_snail_skin_transition(SnailSkin* snail_skin)",
            "void __thiscall change_snail_skin(SnailSkin* snail_skin, int32_t slot_id, float duration_seconds)",
        ):
            assert declaration in source
        for declaration in (
            "void __thiscall update_jetpack_gauge(SubHover* sub_hover)",
            "void __thiscall uninit_jet_particles(SubHover* sub_hover)",
            "void __thiscall initialize_jet_particles(SubHover* sub_hover)",
            "void __thiscall update_jet_particles(SubHover* sub_hover)",
            "void __thiscall initialize_jetpack_gauge(SubHover* sub_hover, int32_t player_slot)",
            "void __thiscall arm_jetpack_gauge(SubHover* sub_hover)",
        ):
            assert declaration in source

    for source in (binja_sync, ida_sync):
        for owner, size in (
            ('"ObjectAnimation"', "0x14"),
            ('"Object"', "0xDC"),
            ('"Sprite"', "0xB4"),
            ('"RenderableBod"', "0x80"),
            ('"PresentationAnimationSlot"', "0x80"),
            ('"AnimManager"', "0x48"),
            ('"SubHover"', "0x214"),
            ('"Weapon"', "0x3DC"),
            ('"Invincible"', "0x98"),
            ('"SnailSkin"', "0x20"),
            ('"Snail"', "0x19B4"),
            ('"Player"', "0x4364"),
        ):
            assert f"{owner}: {size}" in source

    for offset, field_name, field_type in (
        ("0x192c", "cutscene_roll_progress", "float"),
        ("0x1930", "cutscene_roll_step", "float"),
        ("0x1934", "channel_release_steps_active", "uint8_t"),
    ):
        assert (
            f'("{offset}", "{field_name}", "{field_type}")'
            in broad_binja_sync
        )
    invincible_updates = broad_binja_sync.split(
        "INVINCIBLE_FIELD_UPDATES = (", maxsplit=1
    )[1].split("\n)\n", maxsplit=1)[0]
    for field_name in (
        "cutscene_roll_progress",
        "cutscene_roll_step",
        "channel_release_steps_active",
    ):
        assert field_name not in invincible_updates
        assert field_name not in matcher_invincible
        assert field_name in matcher_player
        assert field_name in analysis_header

    for marker in (
        "observed_invincible_size",
        "current_struct_fields",
        "expected_snail_boundary",
        'replace_types=("Invincible", "Snail")',
    ):
        assert marker in binja_sync

    assert "types_declare_if_missing" in binja_sync
    assert "bn_object_render_types.h" in binja_sync
    assert "star_manager_types.h" in binja_sync
    assert '"object_render_types.h"' in ida_sync
    assert '"star_manager_types.h"' in ida_sync
    assert "struct Sprite {" in sprite_header
    assert "SUBHOVER_PLAYER_ROOT_OFFSET_OPERAND = (0x43A953, 1, 0x42FD7C)" in ida_sync
    for operand in (
        "(0x444B72, 0, 0x4300B4)",
        "(0x444BCD, 0, 0x4300B4)",
        "(0x444BE4, 0, 0x4300B4)",
        "(0x444C3C, 0, 0x4300B4)",
        "(0x444CBD, 1, 0x432738)",
    ):
        assert operand in ida_sync
    assert "_normalize_invincible_root_offsets" in ida_sync
    assert "SUBHOVER_PLAYER_ROOT_OFFSET_OPERANDS = (" in broad_ida_sync
    assert "(0x43A953, 1, 0x42FD7C)" in broad_ida_sync
    assert "mark_cfunc_dirty" in ida_sync
    assert (
        'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"'
        in ida_runner
    )
    assert "TemporaryDirectory" in ida_runner
    assert "preview-snail-presentation-types" in ida_runner
    for marker in (
        "JETPACK_LVAR_SPECS = (",
        '"target_state"',
        '"selected_state"',
        '"transition_immediate"',
        "0x445871",
        "0x445880",
        "0x445886",
        "_sync_named_lvar",
        "jetpack_lvars",
    ):
        assert marker in ida_sync


def test_snail_presentation_replay_preserves_slot_element_cursors() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (BINJA_DIR / "sync_snail_presentation_types.py").read_text(
        encoding="utf-8"
    )
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    assert "SLOT_CURSOR_EXPECTED_SIZES" in binja_sync
    for owner, size in (
        ('"PresentationAnimationSlot"', "0x80"),
        ('"Weapon"', "0x3DC"),
        ('"Snail"', "0x19B4"),
    ):
        assert f"{owner}: {size}" in binja_sync
    assert "PRESENTATION_SLOT_CURSOR_USER_VAR_UPDATES" in binja_sync
    for index, storage, cursor_name in (
        (11, 73, "cutscene_slot_cursor"),
        (235, 69, "jetpack_slot_cursor"),
    ):
        update = (
            '"initialize_player_presentation_controller",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{cursor_name}",\n'
            '        "PresentationAnimationSlot*",'
        )
        assert update in binja_sync
    assert "--slot-cursor-only" in binja_sync
    assert "require_slot_cursor_dependencies" in binja_sync
    assert "apply_user_var_updates" in binja_sync
    for fragment in (
        "struct PresentationAnimationSlot* cutscene_slot_cursor",
        "initialize_renderable_bod(cutscene_slot_cursor)",
        "cutscene_slot_cursor = &cutscene_slot_cursor[1]",
        "struct PresentationAnimationSlot* jetpack_slot_cursor",
        "initialize_renderable_bod(jetpack_slot_cursor)",
        "jetpack_slot_cursor = &jetpack_slot_cursor[1]",
        '"struct PresentationAnimationSlot (*"',
    ):
        assert fragment in health_checks


def test_player_lifecycle_replay_keeps_exact_owners_and_stride_cursor() -> None:
    binja_sync = (BINJA_DIR / "sync_player_lifecycle_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_player_lifecycle_types.py").read_text(
        encoding="utf-8"
    )
    ida_runner = (IDA_DIR / "sync_player_lifecycle_types.py").read_text(
        encoding="utf-8"
    )
    broad_binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    broad_ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    health_checks = (
        Path(__file__).parents[1] / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    prototypes = (
        "void __thiscall health_collect_particles(Player* player, SubHealth* pickup)",
        "void __thiscall set_subgoldy_shoot_flags(Player* player)",
        "void __thiscall shoot_subgoldy(Player* owner, Player* shoot_source)",
        "void __thiscall end_jetpack_hover(SubHover* sub_hover)",
        "void __thiscall initialize_subgoldy(Player* player, int32_t player_slot)",
        "void __thiscall show_subgoldy_lives(Player* player)",
        "void __thiscall begin_post_follow_carryover(Player* player)",
        "void __thiscall play_subgoldy_shoot_sfx(Player* player)",
        "void __thiscall initialize_subgoldy_ghost(Player* player, int32_t owner)",
        "void __thiscall set_subgoldy_ghost_z(Player* player, float ghost_z)",
    )
    for source in (
        binja_sync,
        ida_sync,
        broad_binja_sync,
        broad_ida_sync,
        analysis_header,
    ):
        for declaration in prototypes:
            assert declaration in source

    for source in (binja_sync, ida_sync):
        for owner, size in (
            ('"ObjectAnimation"', "0x14"),
            ('"Object"', "0xDC"),
            ('"Sprite"', "0xB4"),
            ('"RuntimeConfig"', "0xC4"),
            ('"RenderableBod"', "0x80"),
            ('"AnimManager"', "0x48"),
            ('"SubHealth"', "0x74"),
            ('"SubHover"', "0x214"),
            ('"GolbShot"', "0x2E8"),
            ('"GolbShotFlightStrideCursor"', "0x2E8"),
            ('"GolbShotVapourObjectStrideCursor"', "0x2E8"),
            ('"Weapon"', "0x3DC"),
            ('"Invincible"', "0x98"),
            ('"Snail"', "0x19B4"),
            ('"Player"', "0x4364"),
            ('"SubgameRuntime"', "0x1272838"),
        ):
            assert f"{owner}: {size}" in source

    for address, name in (
        ("0x43a010", "health_collect_particles"),
        ("0x43a1a0", "set_subgoldy_shoot_flags"),
        ("0x43a300", "shoot_subgoldy"),
        ("0x43a370", "end_jetpack_hover"),
        ("0x43a9c0", "initialize_subgoldy"),
        ("0x43af10", "show_subgoldy_lives"),
        ("0x43af60", "begin_post_follow_carryover"),
        ("0x43afd0", "play_subgoldy_shoot_sfx"),
        ("0x43d230", "initialize_subgoldy_ghost"),
        ("0x43d3d0", "set_subgoldy_ghost_z"),
    ):
        assert f'("{address}", "{name}")' in binja_sync
        assert f'("{address}", "{name}")' in broad_binja_sync
        ida_address = address.upper().replace("0X", "0x")
        assert f'({ida_address}, "{name}")' in ida_sync
        assert f'({ida_address}, "{name}")' in broad_ida_sync

    assert "bn_object_render_types.h" in binja_sync
    assert "star_manager_types.h" in binja_sync
    assert "runtime_config_types.h" in binja_sync
    assert '"object_render_types.h"' in ida_sync
    assert '"star_manager_types.h"' in ida_sync
    assert '"runtime_config_types.h"' in ida_sync
    assert "typedef struct GolbShotFlightStrideCursor {" in analysis_header
    assert "uint8_t _stride_tail[0x238];" in analysis_header
    assert "typedef struct GolbShotVapourObjectStrideCursor {" in analysis_header
    assert "Object* vapour_object;" in analysis_header
    assert "uint8_t _pad_04[0x70];" in analysis_header
    assert "cRGolbRocket tertiary_body;" in analysis_header
    assert "uint8_t _stride_tail[0x1f4];" in analysis_header
    assert '"RegisterVariableSourceType",\n        1171,\n        73,' in binja_sync
    assert '"GolbShotFlightStrideCursor*"' in binja_sync
    assert '"RegisterVariableSourceType",\n        20215,\n        72,' in binja_sync
    assert (
        '"golb_shot_vapour_object_cursor",\n'
        '        "GolbShotVapourObjectStrideCursor*"'
    ) in binja_sync
    assert (
        'operation.get("op") == "user_var_batch" for operation in user_var_results'
        in binja_sync
    )
    assert '"RegisterVariableSourceType",\n        49,\n        73,' in binja_sync
    assert '"golb_shot_cursor",\n        "GolbShot*"' in binja_sync
    assert "0x43AE54" in ida_sync
    assert "GolbShotFlightStrideCursor *golb_shot_flight_cursor;" in ida_sync
    assert "GOLB_SHOT_ASSET_CURSOR_LVAR" in ida_sync
    assert "0x40FBE8" in ida_sync
    assert (
        "GolbShotVapourObjectStrideCursor *golb_shot_vapour_object_cursor;"
        in ida_sync
    )
    assert "INITIALIZE_SUBGOLDY_USER_VAR_UPDATES" in broad_binja_sync
    assert "MOVEMENT_FLAG_EMITTER_USER_VAR_UPDATES" in broad_binja_sync
    assert (
        "WORLD_INITIALIZER_GOLB_ASSET_CURSOR_USER_VAR_UPDATES"
        in broad_binja_sync
    )
    assert "verify_golb_shot_asset_cursor_sizes" in broad_binja_sync
    assert "INITIALIZE_SUBGOLDY_LVAR_SPECS" in broad_ida_sync
    assert "WORLD_INITIALIZER_GOLB_ASSET_LVAR_SPECS" in broad_ida_sync
    assert "GOLB_SHOT_ASSET_CURSOR_EXPECTED_SIZE = 0x2E8" in broad_ida_sync
    assert "0x43AF60,  # begin_post_follow_carryover" in broad_ida_sync
    assert "0x445840,  # kill_subgoldy" in broad_ida_sync
    assert '"name": "bn_world_assets_golb_nested_owners"' in health_checks
    assert '"name": "ida_world_assets_golb_nested_owners"' in health_checks
    assert (
        'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"'
        in ida_runner
    )


def test_sound_manager_replay_keeps_empty_owner_bank_and_void_init_abi() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (BINJA_DIR / "sync_sound_effect_manager_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_sound_effect_manager_types.py").read_text(
        encoding="utf-8"
    )
    ida_runner = (IDA_DIR / "sync_sound_effect_manager_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "sound_effect_manager_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/sound_effect_manager.h"
    ).read_text(encoding="utf-8")
    references = (repo_root / "analysis/symbols/gameplay-references.json").read_text(
        encoding="utf-8"
    )

    for source in (binja_sync, ida_sync):
        assert "void __thiscall initialize_sound_bank(SoundEffectManager* manager" in source
        assert "void __thiscall play_sound_effect_at_position(SoundEffectManager* manager" in source
        assert "void __thiscall play_sound_effect(SoundEffectManager* manager" in source
        assert "void __thiscall play_sound_effect_scaled(SoundEffectManager* manager" in source
        assert "int32_t __thiscall play_warning_sample_backend(SoundEffectManager* manager" in source
        assert "void __thiscall stop_warning_sample_handle(SoundEffectManager* manager" in source

    assert '("0x4a2140", "SoundBankEntry[52]")' in binja_sync
    assert '("0x78ff88", "SoundEffectManager")' in binja_sync
    assert "uint8_t empty_object;" in analysis_header
    assert "extern SoundBankEntry g_sound_bank_entries[52];" in analysis_header
    assert '(0x4A2140, 0x270, "g_sound_bank_entries", "SoundBankEntry[52]")' in ida_sync
    assert "ida_bytes.get_item_size" in ida_sync
    assert "void initialize_sound_bank(SoundBankEntry* entries);" in matcher_header
    assert "SoundEffectManager_must_be_0x01" in matcher_header
    assert '"size": "0x270"' in references
    assert '"size": "0x1"' in references
    assert (
        'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/sound_effect_manager_types.h"'
        in ida_runner
    )


def test_warning_replay_keeps_exact_owner_and_six_member_abis() -> None:
    binja_sync = (BINJA_DIR / "sync_warning_types.py").read_text(encoding="utf-8")
    ida_sync = (IDA_DIR / "apply_warning_types.py").read_text(encoding="utf-8")
    ida_runner = (IDA_DIR / "sync_warning_types.py").read_text(encoding="utf-8")
    analysis_header = (HEADER_DIR / "warning_types.h").read_text(encoding="utf-8")

    for source in (binja_sync, ida_sync):
        assert "void __thiscall initialize_warning(Warning* warning)" in source
        assert "void __thiscall uninit_warning(Warning* warning)" in source
        assert "void __thiscall start_warning(Warning* warning)" in source
        assert "void __thiscall stop_warning(Warning* warning)" in source
        assert "void __thiscall stop_warning_sample(Warning* warning)" in source
        assert "void __thiscall update_warning(Warning* warning)" in source

    assert '"Warning": 0x10' in binja_sync
    assert '"WarningState": 0x04' in binja_sync
    assert 'struct_updates=(("Warning", WARNING_FIELD_UPDATES),)' in binja_sync
    assert "typedef enum WarningState {" in analysis_header
    assert "struct FrontendWidget* border;" in analysis_header
    assert "Warning_must_be_0x10" in analysis_header
    assert 'EXPECTED_OWNER_SIZES = {\n    "Warning": 0x10,' in ida_sync
    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/warning_types.h"' in ida_runner


def test_frontend_tail_syncs_promote_proved_game_root_owners() -> None:
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(encoding="utf-8")
    high_score_sync = (BINJA_DIR / "sync_high_score_screen_types.py").read_text(
        encoding="utf-8"
    )

    assert '("0x12e6f58", "tip_manager", "TipManager")' in path_sync
    assert '("GameRoot", GAME_ROOT_FIELD_UPDATES)' in path_sync
    assert '("0x12e6e50", "high_score", "HighScore")' in high_score_sync
    assert 'struct_name="GameRoot"' in high_score_sync


def test_ida_replays_compose_the_complete_game_root_catalog_frontend_and_tail() -> None:
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
        '(0x44100, 0x4D00, "root_bod_catalog", "RootBodCatalog")',
        '(0x48E00, 0x5E10, "directx_loader", "DirectXLoader")',
    ):
        assert owner in owner_sync
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
    assert "GAME_ROOT_ACTIVE_BOD_LIST_OFFSET = 0x5A8" in owner_sync
    assert "def _sync_active_bod_list_member" in owner_sync
    assert "root.set_udm_type" in owner_sync
    assert "idc.SetType(GAME_ROOT_GLOBAL_ADDRESS, declaration)" in owner_sync
    assert '"root_global": root_global' in owner_sync
    assert '"active_bod_list": active_bod_list' in owner_sync
    assert "root.del_udm" in owner_sync
    assert "root.add_udm" in owner_sync
    assert 'owner_scope = "catalog_loader_frontend_and_tail"' in owner_sync
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
        assert "typedef struct BodList" in header
        assert "BodNode* first;" in header
        assert "BodList active_bod_list;" in header
        assert "FrameBodList active_bod_list;" not in header
        assert "uint8_t unknown_12727d8[0x1272838 - 0x12727d8];" in header
        assert "uint8_t unknown_12e6e50[0x12e6ff4 - 0x12e6e50];" in header
        assert "uint8_t unknown_000000[0x24];" not in header
        for field in (
            "uint8_t fog_enabled;",
            "float fog_start;",
            "float fog_end;",
            "float fog_density;",
            "tColour fog_color;",
            "uint8_t frontend_link_latch;",
            "FrameRenderableBod root_noop_renderable;",
        ):
            assert field in header
    assert "unknown_12e6df0" not in header

    bn_frame_sync = (BINJA_DIR / "sync_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    for update in (
        '("0x04", "fog_enabled", "uint8_t")',
        '("0x14", "fog_color", "tColour")',
        '("0x568", "frontend_link_latch", "uint8_t")',
        '("0x5a8", "active_bod_list", "BodList")',
        '("0xa60", "root_noop_renderable", "FrameRenderableBod")',
        '("0x14", "sprite", "Sprite*")',
        '("0x24", "draw_world", "uint8_t")',
    ):
        assert update in bn_frame_sync
    assert 'struct_name="Overlay"' in bn_frame_sync
    assert 'struct_name="RenderableBod"' in bn_frame_sync
    assert 'struct_name="Sprite"' in bn_frame_sync
    assert "RENDER_USER_VAR_UPDATES" in bn_frame_sync
    assert "ROOT_CONSTRUCTOR_USER_VAR_UPDATES" in bn_frame_sync
    assert (
        '"construct_game_runtime",\n        "RegisterVariableSourceType",\n        534,\n        72,'
        in bn_frame_sync
    )
    assert '"game",\n        "GameRoot*",' in bn_frame_sync
    assert '824,\n        73,\n        "root_bod_cursor",\n        "BodBase*",' in bn_frame_sync
    assert '("0x48ba3f", "operator_new")' in bn_frame_sync
    assert '"void* __cdecl operator_new(uint32_t size)"' in bn_frame_sync
    assert '"render_game_frame",\n        "RegisterVariableSourceType",\n        445,\n        72,' in bn_frame_sync
    assert '"bod",\n        "RenderableBod*",' in bn_frame_sync
    assert '912,\n        67,\n        "bucket_node",\n        "SpriteDepthNode*",' in bn_frame_sync
    assert '1280,\n        73,\n        "post_cursor",\n        "RenderableBod**",' in bn_frame_sync
    for marker in (
        '299,\n        -128,\n        "post_sprite_count",\n        "int32_t",',
        '303,\n        -124,\n        "rendered_bod_count",\n        "int32_t",',
        '321,\n        -116,\n        "camera_order_cursor",\n        "int32_t*",',
        '55,\n        -112,\n        "rendered_sprite_count",\n        "int32_t",',
        '317,\n        -104,\n        "remaining_camera_count",\n        "int32_t",',
    ):
        assert marker in bn_frame_sync
    assert '708,\n        -108,\n        "next_depth_node"' not in bn_frame_sync
    assert (
        '"int32_t __cdecl draw_sprite_quad(Vec3* position, Sprite* sprite)"'
        in bn_frame_sync
    )
    assert '"0x413670", "configure_sprite_render_state"' in bn_frame_sync
    assert (
        '"int32_t __cdecl configure_sprite_render_state(Sprite* sprite)"'
        in bn_frame_sync
    )
    assert '("0x4dfb10", "g_post_sprite_bods")' in bn_frame_sync
    assert '("0x4dfb10", "RenderableBod*")' in bn_frame_sync
    assert '("0x814c94", "g_sprite_active_heads")' in bn_frame_sync
    assert '("0x814c94", "Sprite*[5]")' in bn_frame_sync
    assert '"Sprite": 0xB4' in frame_sync
    assert '"ObjectRenderVertex": 0x18' in frame_sync
    assert '"SpriteDepthNode": 0x18' in frame_sync
    assert '"RenderableBod": 0x80' in frame_sync
    assert '"Object": 0xDC' in frame_sync
    assert '"ObjectAnimation": 0x14' in frame_sync
    assert '"BodBase": 0x38' in frame_sync
    assert '"AnimManager": 0x48' in frame_sync
    assert "DEPENDENCY_HEADER_NAMES = (" in frame_sync
    assert '"object_render_types.h"' in frame_sync
    assert '"path_template_types.h"' in frame_sync
    assert "def _invalidate_cfunc" in frame_sync
    assert "ida_hexrays.mark_cfunc_dirty(address, True)" in frame_sync
    for selector in (
        "configure_sprite_render_state",
        "draw_sprite_quad",
        "build_sprite_tail",
        "render_game_frame",
    ):
        assert f'"{selector}",' in frame_sync
    assert "def _sync_pointer_lvar" in frame_sync
    assert "ROOT_CONSTRUCTOR_POINTER_LVAR_SPECS" in frame_sync
    assert '(0x48BA3F, "operator_new")' in frame_sync
    assert '"void *__cdecl operator_new(uint32_t size);"' in frame_sync
    assert 'selector="construct_game_runtime"' in frame_sync
    assert '"root_constructor_pointer_lvars"' in frame_sync
    assert '"depth_bucket_cursor",\n        0x40A8C0,' in frame_sync
    assert '"depth_bucket_sprite",\n        0x40A8CB,' in frame_sync
    assert '"post_cursor",\n        0x40A991,' in frame_sync
    assert '"int __cdecl draw_sprite_quad(Vec3 *position, Sprite *sprite);"' in frame_sync
    assert '(0x413670, "configure_sprite_render_state")' in frame_sync
    assert (
        '"int __cdecl configure_sprite_render_state(Sprite *sprite);"'
        in frame_sync
    )
    assert "def _sync_draw_sprite_vertex_lvar" in frame_sync
    assert 'declaration = "ObjectRenderVertex *vertices;"' in frame_sync
    assert "split_definition_address = 0x413933" in frame_sync
    assert '(0x4DFB10, "g_post_sprite_bods")' in frame_sync
    assert '"RenderableBod *g_post_sprite_bods;"' in frame_sync
    assert "INTERIOR_OWNER_VIEWS" in frame_sync
    assert "0x814C94" in frame_sync
    assert "0x790F30" in frame_sync
    assert '"g_sprite_manager"' in frame_sync
    assert '"Sprite *[5]"' in frame_sync
    assert '"active_heads"' in frame_sync
    assert "interior_owner_view_mismatch" in frame_sync
    for header in frame_headers:
        assert "typedef struct Sprite Sprite;" in header
        assert "typedef struct ObjectRenderVertex {" in header
        assert "uint32_t diffuse;" in header
        assert "Sprite* sprite;" in header
        assert "void* sprite;" not in header
        assert "int32_t __cdecl configure_sprite_render_state(Sprite* sprite);" in header
    assert '"BodNode": 0x10' in frame_sync
    assert '"BodList": 0xC' in frame_sync

    bn_path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    assert "UPDATE_SUBGOLDY_USER_VAR_UPDATES" in bn_path_sync
    assert "UPDATE_SUBGOLDY_EVENT_VIEW_SPLIT_DEFINITIONS" in bn_path_sync
    assert "UPDATE_BANNER_USER_VAR_UPDATES" in bn_path_sync
    assert '"row_event_segment_view"' in bn_path_sync
    assert '"message_segment_view"' in bn_path_sync
    assert '"duration_segment_view"' in bn_path_sync
    assert '"sample_segment_view"' in bn_path_sync
    assert '"SubSegmentEventBiasView*"' in bn_path_sync
    assert "--update-subgoldy-only" in bn_path_sync
    assert "--update-subgame-only" in bn_path_sync
    assert "if args.update_subgame_only:" in bn_path_sync
    assert "--build-subgame-only" in bn_path_sync
    assert "if args.build_subgame_only:" in bn_path_sync
    assert "*UPDATE_SUBGOLDY_USER_VAR_UPDATES" in bn_path_sync
    assert "*UPDATE_BANNER_USER_VAR_UPDATES" in bn_path_sync


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
    assert "EXPECTED_BOD_BASE_SIZE = 0x38" in backdrop_apply
    assert "EXPECTED_BACKDROP_DISTORT_CELL_SIZE = 0x18" in backdrop_apply
    assert '"reason": "dependency_size_mismatch"' in backdrop_apply
    assert "EXPECTED_BACKDROP_SIZE = 0x6CC" in backdrop_apply
    assert '(0x410720, "initialize_game_last")' in backdrop_apply
    assert (
        "void __thiscall initialize_game_last(GameRoot* game);"
        in backdrop_apply
    )
    assert "ROOT_INITIALIZER_DIRTY_FUNCTIONS" in backdrop_apply
    assert "0x406DC0" in backdrop_apply
    assert "0x410720" in backdrop_apply
    assert '"target_name": "column_start"' in backdrop_apply
    assert '"target_name": "cell"' in backdrop_apply
    assert "DISTORT_CELL_LVARS" in backdrop_apply
    assert "void __thiscall render_backdrop(Backdrop* backdrop);" in backdrop_apply
    assert "int32_t __thiscall update_backdrop(Backdrop* backdrop);" in backdrop_apply
    assert 'analysis/headers/bn_backdrop_types.h' in backdrop_sync


def test_binja_backdrop_owner_abis_are_directly_replayed() -> None:
    source = (BINJA_DIR / "sync_backdrop_types.py").read_text(encoding="utf-8")
    header = (HEADER_DIR / "bn_backdrop_types.h").read_text(encoding="utf-8")

    assert "apply_proto_updates" in source
    assert "apply_user_var_updates" in source
    assert "types_declare_if_changed" in source
    assert "report_deferred_prototypes" not in source
    assert "proto_owner_deferred" not in source
    assert "typedef struct LandscapeScriptRecord {" in header
    assert "BodBase bod;" in header
    assert "uint8_t bod_base[0x38];" not in header
    assert "Backdrop_must_be_0x6cc" in header
    assert "uint32_t corner_index_buffer_handle;" in header
    assert "int32_t unknown_65c;" not in header
    assert "require_bod_base_dependency" in source
    assert 'struct_name="BodBase"' in source
    assert "size != 0x38" in source
    assert "BACKDROP_DISTORT_USER_VAR_UPDATES" in source
    assert "ROOT_INITIALIZER_REANALYSIS_FUNCTIONS" in source
    assert '"initialize_game_last"' in source
    assert '"game_startup_and_main_loop"' in source
    assert '"column_start"' in source
    assert '"cell"' in source
    assert "--distort-cursors-only" in source
    assert "if args.distort_cursors_only:" in source
    assert "int32_t backdrop_texture_id;" in header
    assert "uint8_t split_backdrop_texture_pair;" in header
    assert "float distort;" in header
    for prototype in (
        "void __thiscall initialize_game_last(GameRoot* game)",
        "void __thiscall set_backdrop_zoom(Backdrop* backdrop, float zoom)",
        "void __thiscall set_backdrop_distort(Backdrop* backdrop, float distort)",
        "void __thiscall change_backdrop(Backdrop* backdrop, LandscapeScriptRecord* record, uint8_t flip)",
        "void __thiscall change_backdrop_real(Backdrop* backdrop)",
        "void __thiscall initialize_backdrop(Backdrop* backdrop, int32_t last_mode)",
        "void __thiscall set_backdrop_texture_target(Backdrop* backdrop, int32_t world)",
        "int32_t __thiscall draw_split_backdrop(Backdrop* backdrop)",
        "void __thiscall render_backdrop(Backdrop* backdrop)",
        "int32_t __thiscall update_backdrop(Backdrop* backdrop)",
    ):
        assert prototype in source


def test_ida_catalog_and_loader_lanes_replay_the_shared_root_graph() -> None:
    catalog_header = (HEADER_DIR / "bn_root_bod_catalog_types.h").read_text(
        encoding="utf-8"
    )
    catalog_binja_sync = (
        BINJA_DIR / "sync_root_bod_catalog_types.py"
    ).read_text(encoding="utf-8")
    catalog_apply = (IDA_DIR / "apply_root_bod_catalog_types.py").read_text(
        encoding="utf-8"
    )
    catalog_sync = (IDA_DIR / "sync_root_bod_catalog_types.py").read_text(
        encoding="utf-8"
    )
    object_apply = (IDA_DIR / "apply_object_render_types.py").read_text(
        encoding="utf-8"
    )

    for source in (catalog_apply, object_apply):
        assert "from game_root_owner import sync_game_root_owner_graph" in source
        assert "sync_game_root_owner_graph(require=False)" in source
        assert '"game_root_owner_graph": game_root_owner_graph' in source

    assert "typedef struct Object Object;" in catalog_header
    assert "Object* object;" in catalog_header
    assert "void* object;" not in catalog_header
    assert "types_declare_if_missing" in catalog_binja_sync
    assert 'struct_name="Object"' in catalog_binja_sync
    assert "Object must be exactly 0xdc bytes" in catalog_binja_sync
    assert '("0x24", "object", "Object*")' in catalog_binja_sync
    assert '"RootBodCatalogEntry": 0x38' in catalog_binja_sync
    assert '"RootBodCatalog": 0x4D00' in catalog_binja_sync
    assert '"Object": 0xDC' in catalog_apply
    assert '"RootBodCatalogEntry": 0x38' in catalog_apply
    assert '"RootTrackFringeBodCatalog": 0x3F00' in catalog_apply
    assert '"RootBodCatalog": 0x4D00' in catalog_apply
    assert 'analysis/headers/bn_root_bod_catalog_types.h' in catalog_sync


def test_root_track_slice_triplet_stride_view_is_borrowed_and_fail_closed() -> None:
    repo_root = Path(__file__).parents[1]
    matcher_header = (
        repo_root / "tools/match/include/root_bod_catalog.h"
    ).read_text(encoding="utf-8")
    catalog_header = (HEADER_DIR / "bn_root_bod_catalog_types.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (
        BINJA_DIR / "sync_root_bod_catalog_types.py"
    ).read_text(encoding="utf-8")
    ida_sync = (IDA_DIR / "apply_root_bod_catalog_types.py").read_text(
        encoding="utf-8"
    )

    assert "RootTrackSliceTripletStrideView" not in matcher_header
    for bank in ("floor_slices", "warning_slices", "slide_slices"):
        assert f"TrackSliceBodBank {bank};" in matcher_header

    assert "typedef struct RootTrackSliceTripletStrideView {" in catalog_header
    assert "uint8_t root_to_floor_slice[0x44790];" in catalog_header
    assert "RootBodCatalogEntry floor_slice;" in catalog_header
    assert "uint8_t floor_to_warning_slice[0x188];" in catalog_header
    assert "RootBodCatalogEntry warning_slice;" in catalog_header
    assert "uint8_t warning_to_slide_slice[0x188];" in catalog_header
    assert "RootBodCatalogEntry slide_slice;" in catalog_header
    assert "RootBodCatalog remains the sole" in catalog_header

    assert "WORLD_INITIALIZER_USER_VAR_UPDATES" in binja_sync
    assert (
        '"RegisterVariableSourceType",\n'
        "        2681,\n"
        "        73,\n"
        '        "track_slice_triplet_stride_view",\n'
        '        "RootTrackSliceTripletStrideView*",'
    ) in binja_sync
    assert '"RootTrackSliceBodBank": 0x1C0' in binja_sync
    assert '"RootTrackSliceTripletStrideView": 0x44B48' in binja_sync
    assert "apply_user_var_updates" in binja_sync
    assert "reanalyze_functions" in binja_sync

    assert '"RootTrackSliceTripletStrideView": 0x44B48' in ida_sync
    assert '"definition_address": 0x40B76A' in ida_sync
    assert '"accepted_names": {"v18", "track_slice_triplet_stride_view"}' in ida_sync
    assert '"is_stack": False' in ida_sync
    assert "bool(lvar.is_stk_var()) == is_stack" in ida_sync
    assert "_sync_track_slice_triplet_lvar()" in ida_sync

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    bn_check = checks[
        "bn_game_initializer_track_slice_triplet_stride_ownership"
    ]
    ida_check = checks[
        "ida_game_initializer_track_slice_triplet_stride_ownership"
    ]
    assert (
        r"struct RootTrackSliceTripletStrideView\* "
        r"track_slice_triplet_stride_view = game \+ eax_[0-9]+ \* 0x38"
        in bn_check["required_regexes"]
    )
    assert (
        r"void\* edi_[0-9]+ = game \+ eax_[0-9]+ \* 0x38"
        in bn_check["forbidden_regexes"]
    )
    assert (
        "struct RootTrackSliceTripletStrideView "
        "*track_slice_triplet_stride_view;"
        in ida_check["required_substrings"]
    )
    assert "char *v18;" in ida_check["forbidden_substrings"]


def test_root_fringe_catalog_object_cursors_are_borrowed_and_fail_closed() -> None:
    repo_root = Path(__file__).parents[1]
    matcher_catalog_header = (
        repo_root / "tools/match/include/root_bod_catalog.h"
    ).read_text(encoding="utf-8")
    matcher_fringe_header = (
        repo_root / "tools/match/include/track_fringe_bod_catalog.h"
    ).read_text(encoding="utf-8")
    catalog_header = (HEADER_DIR / "bn_root_bod_catalog_types.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (
        BINJA_DIR / "sync_root_bod_catalog_types.py"
    ).read_text(encoding="utf-8")
    ida_sync = (IDA_DIR / "apply_root_bod_catalog_types.py").read_text(
        encoding="utf-8"
    )

    assert "RootFringeCatalogObjectStrideCursor" not in matcher_catalog_header
    assert "TrackFringeBodCatalog fringe_catalog;" in matcher_catalog_header
    assert "BodBase entries" in matcher_fringe_header
    for dimension in (
        "TRACK_FRINGE_FAMILY_COUNT",
        "TRACK_FRINGE_DIRECTION_COUNT",
        "TRACK_FRINGE_EDGE_VARIANT_COUNT",
    ):
        assert dimension in matcher_fringe_header

    assert (
        "typedef struct RootFringeCatalogObjectStrideCursor {"
        in catalog_header
    )
    assert "Object* object;" in catalog_header
    assert "RootBodCatalogColor4f color;" in catalog_header
    assert "uint8_t _stride_tail[0x24];" in catalog_header
    assert "288-entry fringe constructor" in catalog_header
    assert "it owns" in catalog_header
    assert "neither the catalog entry nor the referenced Object" in catalog_header

    assert '"RootFringeCatalogObjectStrideCursor": 0x38' in binja_sync
    for identity in (
        (
            "21231",
            "66",
            "fringe_orientation_object_cursor",
        ),
        (
            "21245",
            "72",
            "fringe_entry_object_cursor",
        ),
    ):
        index, storage, name = identity
        assert (
            '"RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            '        "RootFringeCatalogObjectStrideCursor*",'
        ) in binja_sync
    assert 'operation.get("op") == "user_var_batch"' in binja_sync

    assert '"RootFringeCatalogObjectStrideCursor": 0x38' in ida_sync
    assert "FRINGE_CATALOG_CURSOR_LVARS" in ida_sync
    for definition_address, target_name in (
        ("0x40FFE0", "fringe_orientation_object_cursor"),
        ("0x40FFEE", "fringe_entry_object_cursor"),
    ):
        assert f'"definition_address": {definition_address}' in ida_sync
        assert f'"target_name": "{target_name}"' in ida_sync
    assert '"Object **"' in ida_sync
    assert "_sync_exact_struct_pointer_lvar(spec)" in ida_sync
    assert "bool(lvar.is_stk_var()) == is_stack" in ida_sync

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    bn_check = checks[
        "bn_game_initializer_fringe_catalog_cursor_ownership"
    ]
    ida_check = checks[
        "ida_game_initializer_fringe_catalog_cursor_ownership"
    ]
    assert (
        "fringe_entry_object_cursor = &fringe_entry_object_cursor[1]"
        in bn_check["required_substrings"]
    )
    assert "esi_2 = &esi_2[0xe]" in bn_check["forbidden_substrings"]
    assert (
        "++fringe_entry_object_cursor;"
        in ida_check["required_substrings"]
    )
    assert "v296 += 14;" in ida_check["forbidden_substrings"]


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


def test_normalize_prototype_preserves_nondefault_calling_conventions() -> None:
    requested = "void* __thiscall noop_runtime_slot_constructor(void* slot)"
    assert _narrow_sync.normalize_prototype(
        "void* __thiscall(void* slot) __pure",
        identifier="noop_runtime_slot_constructor",
    ) == _narrow_sync.normalize_prototype(
        requested,
        identifier="noop_runtime_slot_constructor",
    )
    assert _narrow_sync.normalize_prototype(
        "void* __fastcall(void* slot) __pure",
        identifier="noop_runtime_slot_constructor",
    ) != _narrow_sync.normalize_prototype(
        requested,
        identifier="noop_runtime_slot_constructor",
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
    assert "fn.reanalyze()" in code
    assert "reanalysis_identifiers" in code
    assert 'return str(value).replace(" __pure", "")' in code


def test_crt_variadic_replay_covers_the_complete_sprintf_xref_set() -> None:
    source = Path("tools/binja/sync_crt_variadic_prototypes.py").read_text(
        encoding="utf-8"
    )
    header = Path("analysis/headers/bn_crt_variadic_prototypes.h").read_text(
        encoding="utf-8"
    )

    prototype = "int32_t __cdecl sprintf(char* buffer, const char* format, ...)"
    assert prototype in source
    assert prototype + ";" in header
    assert "apply_proto_updates(" in source
    assert "reanalyze_functions(" in source
    for caller in (
        "update_frontend_widget_interaction",
        "load_x_mesh",
        "load_x_animation_clip",
        "load_galaxy_layout",
        "load_landscape_script_by_name",
        "open_logo",
        "initialize_intro_screen",
        "build_subgame_level",
        "load_frontend_level_by_mode_and_index",
        "handle_subgoldy_collisions",
        "load_level_definition_file",
        "load_segment_definitions",
        "format_time_trial_string",
        "load_object_definition",
        "sub_46120b",
        "sub_47d91e",
        "sub_47f8dc",
        "sub_485cf8",
    ):
        assert f'"{caller}"' in source


def test_object_loader_replay_keeps_authored_abi_and_exact_frame_owners() -> None:
    owner_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    ida_owner_sync = (IDA_DIR / "apply_object_render_types.py").read_text(
        encoding="utf-8"
    )
    replay = (BINJA_DIR / "sync_object_loader_lifetimes.py").read_text(
        encoding="utf-8"
    )
    headers = [
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bn_object_render_types.h", "object_render_types.h")
    ]

    prototype = "void __cdecl load_object_definition(char* path, Object* object)"
    assert prototype in owner_sync
    assert f'"{prototype};"' in ida_owner_sync
    assert prototype in replay
    for header in headers:
        assert prototype + ";" in header
    assert '(0x44C420, "load_object_definition")' in ida_owner_sync
    assert "0x44C420,  # load_object_definition" in ida_owner_sync
    assert "apply_direct_proto_update(" in replay
    assert "apply_user_var_updates(" in replay
    assert "verify_object_loader_owner_layouts" in replay
    for (
        storage,
        definition_address,
        ida_stack_offset,
        name,
        variable_type,
        ida_declaration,
    ) in (
        (
            -572,
            "0x44C4D0",
            84,
            "line_cursor",
            "char*",
            "char *line_cursor;",
        ),
        (-568, "0x44C472", 88, "cursor", "char*", "char *cursor;"),
        (
            -516,
            "0x44C468",
            140,
            "byte_count",
            "int32_t",
            "int32_t byte_count;",
        ),
        (
            -512,
            "0x44C46E",
            144,
            "texture_name",
            "char[0x80]",
            "char texture_name[0x80];",
        ),
        (
            -384,
            "0x44C76F",
            272,
            "texture_path",
            "char[0x80]",
            "char texture_path[0x80];",
        ),
        (
            -256,
            "0x44C445",
            400,
            "object_file_path",
            "char[0x100]",
            "char object_file_path[0x100];",
        ),
    ):
        marker = (
            '        "StackVariableSourceType",\n'
            "        0,\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert marker in replay
        assert definition_address in ida_owner_sync
        assert f"        {ida_stack_offset}," in ida_owner_sync
        assert f'"{name}"' in ida_owner_sync
        assert f'"{ida_declaration}"' in ida_owner_sync
    assert "_sync_object_loader_lvars()" in ida_owner_sync
    assert "fallback_stack_offset=stack_offset" in ida_owner_sync
    assert (
        '"reason": "unexpected_owned_lvar_stack_candidates"' in ida_owner_sync
    )


def test_x_mesh_loader_replay_keeps_cache_and_parser_lifetimes() -> None:
    owner_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    replay = (BINJA_DIR / "sync_x_mesh_loader_lifetimes.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "bn_object_render_types.h").read_text(
        encoding="utf-8"
    )

    prototype = (
        "void __thiscall load_x_mesh("
        "DirectXLoader* loader, char* mesh_path, Object* object, "
        "int32_t options_flags)"
    )
    assert prototype in owner_sync
    for fragment in (
        "void __thiscall load_x_mesh(",
        "DirectXLoader* loader, char* mesh_path, Object* object, ",
        "int32_t options_flags)",
    ):
        assert fragment in replay
        assert fragment in header
    assert "apply_direct_proto_update(" in replay
    assert "apply_user_var_updates(" in replay
    assert "verify_x_mesh_loader_owner_layouts" in replay
    for prototype, fragments in (
        (
            "void __thiscall initialize_directx_loader(DirectXLoader* loader)",
            ("void __thiscall initialize_directx_loader(",),
        ),
        (
            (
                "int32_t __thiscall load_or_reuse_cached_x_mesh("
                "DirectXLoader* loader, char* mesh_name)"
            ),
            (
                "int32_t __thiscall load_or_reuse_cached_x_mesh(",
                "DirectXLoader* loader, char* mesh_name)",
            ),
        ),
    ):
        assert prototype in owner_sync
        assert prototype + ";" in header
        for fragment in fragments:
            assert fragment in replay
    for storage, name, variable_type in (
        (-564, "mesh_cursor", "char*"),
        (-556, "material_cursor", "char*"),
        (-548, "texcoord_cursor", "char*"),
        (-540, "material_header_cursor", "char*"),
        (-536, "duplicate_cursor", "char*"),
        (-516, "byte_count", "int32_t"),
        (-512, "mesh_file_path", "char[0x100]"),
        (-256, "texture_path", "char[0x100]"),
    ):
        marker = (
            '        "StackVariableSourceType",\n'
            "        0,\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert marker in replay
    for index, storage, name, variable_type in (
        (10, 73, "cached_slot_index", "int32_t"),
        (19, 69, "cached_name_cursor", "char*"),
        (80, 66, "new_object", "Object*"),
        (133, 66, "new_cached_x_mesh_count", "int32_t"),
    ):
        marker = (
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert marker in replay


def test_x_animation_loader_replay_keeps_keyframes_and_parser_lifetimes() -> None:
    owner_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    replay = (BINJA_DIR / "sync_x_animation_loader_lifetimes.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "bn_object_render_types.h").read_text(
        encoding="utf-8"
    )

    prototype = (
        "void __thiscall load_x_animation_clip("
        "DirectXLoader* loader, char* mesh_name, Object* object)"
    )
    assert prototype in owner_sync
    for fragment in (
        "void __thiscall load_x_animation_clip(",
        "DirectXLoader* loader, char* mesh_name, Object* object)",
    ):
        assert fragment in replay
        assert fragment in header
    assert "apply_direct_proto_update(" in replay
    assert "apply_split_user_var_update(" in replay
    assert "apply_user_var_updates(" in replay
    assert "verify_x_animation_loader_owner_layouts" in replay
    for definition in (
        '("0x405f16", "mlil", "RegisterVariableSourceType", 438, 66)',
        '("0x405f1b", "mlil", "RegisterVariableSourceType", 443, 72)',
        '("0x405f2e", "mlil", "RegisterVariableSourceType", 462, 66)',
        '("0x405f33", "mlil", "RegisterVariableSourceType", 467, 69)',
    ):
        assert definition in replay
    for index, storage, name, variable_type in (
        (0, -404, "cursor", "char*"),
        (511, -397, "saved_end_char", "char"),
        (575, -396, "progress_step", "float"),
        (0, -392, "keyframe_count", "int32_t"),
        (223, -388, "keyframes", "XAnimationKeyframe*"),
        (0, -384, "animation_tag", "char[0x80]"),
        (0, -256, "path_pattern", "char[0x100]"),
    ):
        marker = (
            '        "StackVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert marker in replay
    for index, storage, name, variable_type in (
        (209, 66, "allocated_keyframes", "XAnimationKeyframe*"),
        (214, 67, "loop_keyframe_count", "int32_t"),
        (221, 71, "keyframe_index", "int32_t"),
        (241, 72, "mesh_path", "char*"),
        (246, 73, "frame_number_cursor", "int32_t*"),
        (443, 72, "animation_block", "char*"),
        (467, 69, "animation_end", "char*"),
        (595, 73, "mode_flags", "int32_t"),
    ):
        marker = (
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert marker in replay


def test_object_texture_group_builder_replay_keeps_resource_and_stream_owners() -> None:
    owner_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    replay = (
        BINJA_DIR / "sync_object_texture_group_builder_lifetimes.py"
    ).read_text(encoding="utf-8")
    header = (HEADER_DIR / "bn_object_render_types.h").read_text(
        encoding="utf-8"
    )

    prototype = (
        "void __cdecl build_object_texture_group_buffers(Object* object)"
    )
    assert prototype in owner_sync
    assert prototype in replay
    assert prototype + ";" in header
    assert "apply_direct_proto_update(" in replay
    assert "apply_user_var_updates(" in replay
    assert "verify_object_texture_group_builder_owner_layouts" in replay
    for index, storage, name, variable_type in (
        (13, 73, "scan_face_byte_offset", "int32_t"),
        (80, 66, "allocated_group_index_starts", "int32_t*"),
        (103, 66, "allocated_group_texture_refs", "TextureRef**"),
        (150, 66, "index_scratch", "uint16_t*"),
        (168, 67, "group_face_index", "int32_t"),
        (191, 72, "source_vertex_index", "int32_t"),
        (217, 66, "scan_face", "ObjectFaceQuad*"),
        (347, 66, "group_index", "int32_t"),
        (385, 73, "face_byte_offset", "int32_t"),
        (424, 72, "index_0_cursor", "uint16_t*"),
        (435, 71, "index_2_cursor", "uint16_t*"),
        (441, 66, "index_count_base", "int32_t"),
        (472, 66, "face_for_vertex_0", "ObjectFaceQuad*"),
        (499, 66, "face_for_vertex_1", "ObjectFaceQuad*"),
        (532, 66, "face_for_vertex_2", "ObjectFaceQuad*"),
        (599, 66, "face_for_vertex_3", "ObjectFaceQuad*"),
        (690, 66, "next_primitive_count", "int32_t"),
        (874, 66, "allocated_index_buffer", "ObjectIndexBuffer*"),
        (896, 66, "locked_vertex_buffer", "ObjectVertexBuffer*"),
        (925, 68, "upload_index", "int32_t"),
        (931, 66, "locked_vertex_byte_offset", "int32_t"),
        (933, 67, "grouped_vertex_byte_offset", "int32_t"),
        (963, 72, "grouped_vertex_uv", "ObjectUv*"),
        (994, 72, "grouped_vertex_position", "Vec3*"),
        (996, 73, "locked_vertex", "ObjectRenderVertex*"),
        (1043, 66, "unlock_vertex_buffer", "ObjectVertexBuffer*"),
        (1058, 72, "index_byte_count", "int32_t"),
        (
            1063,
            66,
            "locked_index_buffer_resource",
            "ObjectIndexBufferResource*",
        ),
        (
            1108,
            66,
            "unlock_index_buffer_resource",
            "ObjectIndexBufferResource*",
        ),
    ):
        marker = (
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert marker in replay
    for index, storage, name, variable_type in (
        (172, -20, "face_index", "int32_t"),
        (204, -12, "scan_face_index", "int32_t"),
        (351, -12, "current_group_index", "int32_t"),
        (378, -28, "primitive_count", "int32_t"),
        (427, -24, "index_5_cursor", "uint16_t*"),
        (445, -32, "index_4_cursor", "uint16_t*"),
        (457, -36, "index_3_cursor", "uint16_t*"),
        (461, -40, "index_1_cursor", "uint16_t*"),
        (0, -16, "locked_vertices", "ObjectRenderVertex*"),
        (0, -4, "locked_indices", "uint16_t*"),
    ):
        marker = (
            '        "StackVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert marker in replay


def test_object_texture_group_builder_replay_keeps_helper_borrows_and_offsets() -> None:
    replay = (
        BINJA_DIR / "sync_object_texture_group_builder_lifetimes.py"
    ).read_text(encoding="utf-8")

    for struct_name, offset, field_name, field_type in (
        ("ObjectGroupedVertex", "0x04", "y", "float"),
        ("ObjectGroupedVertex", "0x08", "z", "float"),
        ("ObjectGroupedVertex", "0x14", "v", "float"),
        ("Object", "0x38", "vertices", "Vec3*"),
        ("Object", "0x48", "vertex_colours", "tColour*"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for index, storage, name, variable_type in (
        (35, 67, "source_vertices", "Vec3*"),
        (38, 66, "source_float_index", "int32_t"),
        (41, 72, "grouped_vertex_count", "int32_t"),
        (47, 68, "source_vertex", "Vec3*"),
        (50, 66, "source_x", "float"),
        (57, 67, "source_y", "float"),
        (64, 68, "source_z", "float"),
        (71, 68, "grouped_vertex_index", "int32_t"),
        (81, 66, "grouped_vertices", "ObjectGroupedVertex*"),
        (92, 67, "grouped_vertex_y_cursor", "float*"),
        (245, 72, "append_index_times_eight", "int32_t"),
        (252, 72, "append_index_times_seven", "int32_t"),
        (254, 72, "append_byte_offset", "int32_t"),
    ):
        marker = (
            '        "get_or_append_object_texture_group_vertex",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert marker in replay

    helper_replay = replay.index("updates=GROUPED_VERTEX_HELPER_USER_VAR_UPDATES")
    builder_replay = replay.index("updates=TEXTURE_GROUP_BUILDER_USER_VAR_UPDATES")
    assert helper_replay < builder_replay
    assert '"source_vertex",\n        "void*"' not in replay
    assert '"append_byte_offset",\n        "float*"' not in replay


def test_intro_logo_lifetime_replay_keeps_real_owners_and_staged_stride() -> None:
    source = (BINJA_DIR / "sync_intro_logo_lifetimes.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "bn_logo_types.h").read_text(encoding="utf-8")

    assert "typedef struct LogoLetterVelocityCursor {" in header
    assert "Vec3 velocity;" in header
    assert "uint8_t stride_tail[0x84];" in header
    assert '"LogoLetterVelocityCursor": 0x90' in source
    assert '"LogoLetter": 0x90' in source
    assert '"Logo": 0x25218' in source
    for index, storage, name, variable_type in (
        (128, 66, "loaded_script_bytes", "char*"),
        (261, 72, "script_bytes", "char*"),
        (369, 66, "image_name_write", "char*"),
        (560, 68, "active_first_link_image", "BodNode*"),
        (570, 68, "active_new_first_image", "BodNode*"),
        (1311, 68, "active_first_link_glyph", "BodNode*"),
        (1321, 68, "active_new_first_glyph", "BodNode*"),
        (1792, 66, "velocity_cursor", "LogoLetterVelocityCursor*"),
    ):
        marker = (
            f'        {index},\n'
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert marker in source
    for storage, name in ((-256, "image_name"), (-128, "texture_path")):
        marker = (
            '        "StackVariableSourceType",\n'
            "        0,\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            '        "char[0x80]",'
        )
        assert marker in source
    assert (
        '        1802,\n        68,\n        "current_velocity",\n        "Vec3*",'
        in source
    )
    direct_replay = source.index("updates=INTRO_LOGO_DIRECT_USER_VAR_UPDATES")
    derived_replay = source.index("updates=INTRO_LOGO_DERIVED_USER_VAR_UPDATES")
    assert direct_replay < derived_replay
    assert "partial-store" not in source


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


def test_current_enum_members_batches_exact_readback(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {
            "result": {
                "FrontendWidgetFlag": [
                    ["FRONTEND_WIDGET_FLAG_HIGHLIGHTED", 2],
                    ["FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED", 0x20],
                ],
                "MissingFlag": None,
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    assert _narrow_sync.current_enum_members(
        Path("."),
        target="snail-mail.exe",
        enum_names=("FrontendWidgetFlag", "MissingFlag"),
    ) == {
        "FrontendWidgetFlag": (
            ("FRONTEND_WIDGET_FLAG_HIGHLIGHTED", 2),
            ("FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED", 0x20),
        ),
        "MissingFlag": None,
    }
    assert len(calls) == 1
    assert calls[0][:2] == ("py", "exec")
    assert "member.value" in calls[0][-1]
    assert "int(member.value) & value_mask" in calls[0][-1]


def test_header_enum_members_previews_without_live_mutation(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {
            "result": {
                "PathTemplateKind": [
                    ["PATH_TEMPLATE_KIND_CAGE2", 0x0F],
                    ["PATH_TEMPLATE_KIND_DIP", 0x14],
                    ["PATH_TEMPLATE_KIND_SLALOMDOUBLE", 0x20],
                ]
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    assert _narrow_sync.header_enum_members(
        Path("."),
        target="snail-mail.exe",
        header_path=Path("path_template_types.h"),
        enum_names=("PathTemplateKind",),
    ) == {
        "PathTemplateKind": (
            ("PATH_TEMPLATE_KIND_CAGE2", 0x0F),
            ("PATH_TEMPLATE_KIND_DIP", 0x14),
            ("PATH_TEMPLATE_KIND_SLALOMDOUBLE", 0x20),
        )
    }
    assert len(calls) == 1
    assert calls[0][:2] == ("py", "exec")
    assert "parse_types_from_source" in calls[0][-1]
    assert "define_user_type" not in calls[0][-1]


def test_path_template_kind_replay_tracks_paired_mobile_owners() -> None:
    repo_root = Path(__file__).parents[1]
    header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")
    matcher_header = (
        repo_root / "tools/match/include/track_attachment_types.h"
    ).read_text(encoding="utf-8")
    replay = (BINJA_DIR / "sync_path_template_kind.py").read_text(
        encoding="utf-8"
    )
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")
    runtime_notes = (
        repo_root / "analysis/runtime/path-template-typing-2026-03-26.md"
    ).read_text(encoding="utf-8")
    crosswalk = json.loads(
        (
            repo_root / "analysis/symbols/windows-mobile-gameplay-crosswalk.json"
        ).read_text(encoding="utf-8")
    )
    crosswalk_entries = {
        entry["windows_name"]: entry for entry in crosswalk["entries"]
    }

    windows_kind_members = (
        ("PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY", "0x00"),
        ("PATH_TEMPLATE_KIND_LOOPTHELOOPW", "0x06"),
        ("PATH_TEMPLATE_KIND_CAGE2", "0x0f"),
        ("PATH_TEMPLATE_KIND_FAMILY_10", "0x10"),
        ("PATH_TEMPLATE_KIND_FAMILY_11", "0x11"),
        ("PATH_TEMPLATE_KIND_DIP", "0x14"),
        ("PATH_TEMPLATE_KIND_SCREW", "0x15"),
        ("PATH_TEMPLATE_KIND_SLALOM", "0x16"),
        ("PATH_TEMPLATE_KIND_SLALOMBIG", "0x17"),
        ("PATH_TEMPLATE_KIND_WORM", "0x18"),
        ("PATH_TEMPLATE_KIND_LOOPOUT", "0x19"),
        ("PATH_TEMPLATE_KIND_SWEEP", "0x1c"),
        ("PATH_TEMPLATE_KIND_SNAKE", "0x1d"),
        ("PATH_TEMPLATE_KIND_SUPERTRAMP", "0x1f"),
        ("PATH_TEMPLATE_KIND_SLALOMDOUBLE", "0x20"),
        ("PATH_TEMPLATE_KIND_START", "0x24"),
        ("PATH_TEMPLATE_KIND_TURNOVER", "0x25"),
        ("PATH_TEMPLATE_KIND_TURNOVERDOUBLE", "0x26"),
        ("PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY", "0x27"),
        ("PATH_TEMPLATE_KIND_WIBBLE", "0x28"),
        ("PATH_TEMPLATE_KIND_INVERT", "0x29"),
        ("PATH_TEMPLATE_KIND_NONLINEAR_42", "0x2a"),
        ("PATH_TEMPLATE_KIND_TWISTER", "0x2b"),
        ("PATH_TEMPLATE_KIND_TWISTER2", "0x2d"),
    )
    for name, value in windows_kind_members:
        assert f"{name} = {value}" in header
        assert f"{name} = {value}" in matcher_header
    assert "PathTemplateKind kind;" in matcher_header

    paired_mobile_owners = (
        ("PATH_TEMPLATE_KIND_CAGE2", "0x0f", "0x0F"),
        ("PATH_TEMPLATE_KIND_DIP", "0x14", "0x14"),
        ("PATH_TEMPLATE_KIND_SLALOMDOUBLE", "0x20", "0x20"),
    )
    for name, header_value, replay_value in paired_mobile_owners:
        assert f"{name} = {header_value}" in header
        assert f'("{name}", {replay_value})' in replay
        assert f"self->kind = {name}" in health_checks
        assert name in runtime_notes

    proven_consumers = {
        "update_sub_loc": "PATH_TEMPLATE_KIND_WORM",
        "update_subgoldy": "PATH_TEMPLATE_KIND_CAGE2",
        "update_track_attachment_follow_state": "PATH_TEMPLATE_KIND_SUPERTRAMP",
        "traverse_path_follow_golb": "PATH_TEMPLATE_KIND_NONLINEAR_42",
    }
    for scratch_name, enum_name in proven_consumers.items():
        scratch = (
            repo_root / "tools/match/scratches" / scratch_name / "scratch.cpp"
        ).read_text(encoding="utf-8")
        assert enum_name in scratch

    for windows_name, address, mobile_symbol in (
        (
            "initialize_cage2_path_template_pair",
            "0x42e720",
            "cRPath::BuildCage2(int, char*, char*)",
        ),
        (
            "initialize_dip_path_template_pair",
            "0x41e440",
            "cRPath::BuildDip(float, int, bool, char*, char*)",
        ),
        (
            "initialize_slalomdouble_path_template_pair",
            "0x425050",
            "cRPath::BuildSlalomDouble(int, int, bool, char*, char*)",
        ),
    ):
        evidence = crosswalk_entries[windows_name]
        assert evidence["address"] == address
        assert evidence["status"] == "verified"
        assert evidence["confidence"] == "high"
        assert evidence["source_object"] == "Path.o"
        assert evidence["android_symbol_evidence"] == "exact-demangled-symbol"
        assert evidence["android_symbol"] == mobile_symbol
        assert evidence["ios_symbol"] == mobile_symbol
        assert evidence["android_body_count"] == 1
        assert evidence["ios_body_count"] == 1

    assert "header_enum_members" in replay
    assert "LEGACY_ENUM_MEMBERS" in replay
    assert "EXPECTED_ENUM_MEMBERS" in replay
    assert "types_declare_missing_only" in replay
    assert "current_enum_members" in replay
    assert "reanalyze_functions" in replay
    for selector in (
        "initialize_cage2_path_template_pair",
        "initialize_dip_path_template_pair",
        "initialize_slalomdouble_path_template_pair",
        "update_subgoldy",
    ):
        assert f'"{selector}"' in replay
    assert "PATH_TEMPLATE_KIND_DETOUR =" not in header


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
            "result": {
                "success": True,
                "preview": True,
                "committed": False,
                "results": [
                    {
                        "address": "0x4ac5c8",
                        "requested_type": "TipData",
                        "before_type": "struct TipData",
                        "after_type": "struct TipData",
                        "changed": False,
                    }
                ],
                "snapshot_saved": False,
            }
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
    assert "preview = True" in calls[0][-1]
    assert "bv.begin_undo_actions()" in calls[0][-1]
    assert "bv.revert_undo_actions(state)" in calls[0][-1]
    assert "bv.update_analysis_and_wait()" not in calls[0][-1]
    assert "bv.update_analysis()" in calls[0][-1]
    assert 'entry["before_width"] in (None, 0)' in calls[0][-1]
    assert 'entry["restored_width"] in (None, 0)' in calls[0][-1]


def test_data_var_updates_preview_before_saved_apply(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        code = args[-1]
        preview = "preview = True" in code
        return {
            "result": {
                "success": True,
                "preview": preview,
                "committed": not preview,
                "results": [
                    {
                        "address": "0x53d190",
                        "requested_type": "ParcelBucket[0x800]",
                        "before_type": None,
                        "after_type": "struct ParcelBucket[2048]",
                        "changed": True,
                    }
                ],
                "snapshot_saved": not preview,
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    assert _narrow_sync.apply_data_var_updates(
        Path("."),
        target="snail-mail.exe",
        updates=(("0x53d190", "ParcelBucket[0x800]"),),
    ) == [
        {
            "op": "data_var_set",
            "address": "0x53d190",
            "type": "ParcelBucket[0x800]",
            "before_type": None,
            "after_type": "struct ParcelBucket[2048]",
            "status": "verified",
            "reason": None,
        }
    ]
    assert len(calls) == 2
    assert "preview = True" in calls[0][-1]
    assert "preview = False" in calls[1][-1]
    assert "bv.commit_undo_actions(state)" in calls[1][-1]
    assert "bv.file.save_auto_snapshot()" in calls[1][-1]
    assert "bv.update_analysis_and_wait()" not in calls[1][-1]
    assert "bv.update_analysis()" in calls[1][-1]


def test_data_var_removals_preview_before_saved_apply(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        code = args[-1]
        preview = "preview = True" in code
        return {
            "result": {
                "success": True,
                "preview": preview,
                "committed": not preview,
                "results": [
                    {
                        "address": "0x53d190",
                        "expected_type": "ParcelBucket[0x800]",
                        "replacement_type": "ParcelBucket",
                        "before_type": "struct ParcelBucket[2048]",
                        "after_type": None,
                        "changed": True,
                        "reason": None,
                    }
                ],
                "snapshot_saved": not preview,
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    assert _narrow_sync.apply_data_var_removals(
        Path("."),
        target="snail-mail.exe",
        removals=(("0x53d190", "ParcelBucket[0x800]"),),
        replacements=(("0x53d190", "ParcelBucket"),),
    ) == [
        {
            "op": "data_var_remove",
            "address": "0x53d190",
            "expected_type": "ParcelBucket[0x800]",
            "replacement_type": "ParcelBucket",
            "before_type": "struct ParcelBucket[2048]",
            "after_type": None,
            "status": "verified",
            "reason": None,
        }
    ]
    assert len(calls) == 2
    assert "preview = True" in calls[0][-1]
    assert "preview = False" in calls[1][-1]
    assert "bv.undefine_user_data_var(address)" in calls[0][-1]
    assert "refusing to remove unexpected data variable" in calls[0][-1]
    assert "bv.revert_undo_actions(state)" in calls[0][-1]
    assert "bv.commit_undo_actions(state)" in calls[1][-1]
    assert "bv.file.save_auto_snapshot()" in calls[1][-1]


def test_data_var_removals_accept_the_intended_replacement(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {
            "result": {
                "success": True,
                "preview": True,
                "committed": False,
                "results": [
                    {
                        "address": "0x53d190",
                        "expected_type": "ParcelBucket[0x800]",
                        "replacement_type": "ParcelBucket",
                        "before_type": "struct ParcelBucket",
                        "after_type": "struct ParcelBucket",
                        "changed": False,
                        "reason": "already replaced",
                    }
                ],
                "snapshot_saved": False,
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    assert _narrow_sync.apply_data_var_removals(
        Path("."),
        target="snail-mail.exe",
        removals=(("0x53d190", "ParcelBucket[0x800]"),),
        replacements=(("0x53d190", "ParcelBucket"),),
    )[0]["reason"] == "already replaced"
    assert len(calls) == 1
    assert "before_address = int(before.address)" in calls[0][-1]
    assert "bool(before.auto_discovered)" in calls[0][-1]
    assert 'entry["after_auto_discovered"] is True' in calls[0][-1]
    assert 'reason = "already covered by replacement"' in calls[0][-1]
    assert 'entry["after_address"] == entry["before_address"]' in calls[0][-1]


def test_data_var_removals_accept_a_covering_replacement(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {
            "result": {
                "success": True,
                "preview": True,
                "committed": False,
                "results": [
                    {
                        "address": "0x753c64",
                        "expected_type": "float",
                        "replacement_type": "AudioBackend",
                        "before_address": "0x753c58",
                        "before_type": "struct AudioBackend",
                        "after_address": "0x753c58",
                        "after_type": "struct AudioBackend",
                        "changed": False,
                        "reason": "already covered by replacement",
                    }
                ],
                "snapshot_saved": False,
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    result = _narrow_sync.apply_data_var_removals(
        Path("."),
        target="snail-mail.exe",
        removals=(("0x753c64", "float"),),
        replacements=(("0x753c64", "AudioBackend"),),
    )

    assert result[0]["status"] == "skipped"
    assert result[0]["reason"] == "already covered by replacement"
    assert len(calls) == 1


def test_data_var_removals_reject_unpaired_replacements() -> None:
    try:
        _narrow_sync.apply_data_var_removals(
            Path("."),
            target="snail-mail.exe",
            removals=(("0x53d190", "ParcelBucket[0x800]"),),
            replacements=(("0x6487e8", "ParcelBucket"),),
        )
    except ValueError as error:
        assert "replacements require matching removals" in str(error)
    else:
        raise AssertionError("unpaired data-variable replacement was accepted")


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
    sprite_matcher_header = (
        Path(__file__).parents[1] / "tools/match/include/sprite.h"
    ).read_text(encoding="utf-8")
    star_analysis_header = (HEADER_DIR / "star_manager_types.h").read_text(
        encoding="utf-8"
    )
    path_analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )

    assert "types_declare_missing_only" in source
    assert "current_struct_size" in source
    assert '"Sprite": 0xB4' in source
    assert 'MATRIX_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"' in source
    assert 'OBJECT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"' in source
    assert 'required_structs=("Object",)' in source
    assert "object_size != 0xDC" in source
    assert '("0x24", "object", "Object*")' in source
    assert 'required_structs=("TransformMatrix",)' in source
    assert "matrix_size != 0x40" in source
    assert '("0x44e410", "build_sprite_tail")' in source
    assert '("0x44e800", "initialize_texture_list")' in source
    assert '("0x44e810", "get_or_create_texture_ref")' in source
    assert '("0x4b7790", "g_texture_refs")' in source
    assert '("0x4b7790", "TextureRefList")' in source
    assert "apply_data_var_updates" in source
    assert "apply_user_var_updates" in source
    assert "types_declare(" not in source
    for declaration, ida_declaration in (
        (
            "void __thiscall initialize_texture_list(TextureRefList* texture_list, int32_t capacity)",
            "void __thiscall initialize_texture_list(TextureRefList *texture_list, int32_t capacity);",
        ),
        (
            "TextureRef* __thiscall get_or_create_texture_ref(TextureRefList* texture_list, char* texture_path, void* payload, int32_t flags)",
            "TextureRef *__thiscall get_or_create_texture_ref(TextureRefList *texture_list, char *texture_path, void *payload, int32_t flags);",
        ),
        (
            "void __thiscall initialize_sprite(Sprite* sprite)",
            "void __thiscall initialize_sprite(Sprite *sprite);",
        ),
        (
            "void __thiscall update_sprite(Sprite* sprite)",
            "void __thiscall update_sprite(Sprite *sprite);",
        ),
        (
            "TextureRef* __thiscall register_sprite_texture(SpriteManager* manager, char* texture_path, int32_t texture_id, int32_t flags)",
            "TextureRef *__thiscall register_sprite_texture(SpriteManager *manager, char *texture_path, int32_t texture_id, int32_t flags);",
        ),
        (
            "void __thiscall initialize_sprite_manager(SpriteManager* manager)",
            "void __thiscall initialize_sprite_manager(SpriteManager *manager);",
        ),
        (
            "Sprite* __thiscall allocate_sprite(SpriteManager* manager, int32_t owner, int32_t texture_id, int32_t texture_a, int32_t texture_b)",
            "Sprite *__thiscall allocate_sprite(SpriteManager *manager, int32_t owner, int32_t texture_id, int32_t texture_a, int32_t texture_b);",
        ),
        (
            "TextureRef* __thiscall get_sprite_texture(SpriteManager* manager, int32_t texture_id)",
            "TextureRef *__thiscall get_sprite_texture(SpriteManager *manager, int32_t texture_id);",
        ),
        (
            "TgaImageView* __thiscall get_sprite_tga(SpriteManager* manager, int32_t texture_id)",
            "TgaImageView *__thiscall get_sprite_tga(SpriteManager *manager, int32_t texture_id);",
        ),
        (
            "void __thiscall build_sprite_tail(Sprite* sprite, const TransformMatrix* matrix)",
            "void __thiscall build_sprite_tail("
            "Sprite *sprite, const struct TransformMatrix *matrix);",
        ),
    ):
        assert declaration in source
        assert ida_declaration in ida_source
    assert "TextureRef* __stdcall register_sprite_texture" not in source
    assert "TextureRef* __stdcall get_sprite_texture" not in source
    assert "TRUSTED_NAMES" in ida_source
    assert '(0x44DF30, "update_sprite")' in ida_source
    assert '(0x44E410, "build_sprite_tail")' in ida_source
    assert '(0x44E800, "initialize_texture_list")' in ida_source
    assert '(0x44E810, "get_or_create_texture_ref")' in ida_source
    assert '(0x4B7790, "g_texture_refs")' in ida_source
    assert "TRUSTED_DATA_DECLARATIONS" in ida_source
    assert '"path_template_types.h"' in ida_source
    assert '"object_render_types.h"' in ida_source
    assert '"Object": 0xDC' in ida_source
    assert '"BodBase": 0x38' in ida_source
    assert '"TransformMatrix": 0x40' in ida_source
    assert '"TgaImageView": 0x14' in source
    assert '"TgaImageView": 0x14' in ida_source
    assert '"TextureRefList": 0x14058' in source
    assert '"TextureRefList": 0x14058' in ida_source
    assert 're.sub(r"\\b(?:struct|union|enum)\\s+", "", normalized)' in ida_source
    assert "0x40A490" in ida_source
    assert "0x40ACF0" in ida_source
    assert "0x44E410" in ida_source
    assert "0x404580" in ida_source
    assert "0x44E580" in ida_source
    assert "0x44E800" in ida_source
    assert "0x44E810" in ida_source
    assert "0x434800" in ida_source
    assert '"border_mouse_test"' in source
    assert "STAR_MANAGER_REANALYSIS_FUNCTIONS" in source
    assert '"update_star_positions"' in source
    assert '"mask"' in source
    assert '"TgaImageView*"' in source
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
    assert "struct TransformMatrix;" in star_analysis_header
    assert "typedef struct Object Object;" in star_analysis_header
    assert "Object* object;" in star_analysis_header
    assert "void __thiscall build_sprite_tail(" in star_analysis_header
    assert "const struct TransformMatrix* matrix" in star_analysis_header
    assert "typedef struct TransformMatrix TransformMatrix;" not in star_analysis_header
    assert "#define TEXTURE_REF_LIST_CAPACITY 500" in star_analysis_header
    assert "typedef struct TgaImageView {" in star_analysis_header
    assert "uint8_t pixels[1];" in star_analysis_header
    assert "TgaImageView* __thiscall get_sprite_tga(" in star_analysis_header
    assert "TextureRef entries[TEXTURE_REF_LIST_CAPACITY];" in star_analysis_header
    assert "extern TextureRefList g_texture_refs;" in star_analysis_header
    assert "TEXTURE_REF_LIST_CAPACITY = 500" in sprite_matcher_header
    assert "void initialize_texture_list(int capacity);" in sprite_matcher_header
    assert "char* texture_path, void* payload, int flags" in sprite_matcher_header
    assert "TextureRef entries[TEXTURE_REF_LIST_CAPACITY];" in path_analysis_header
    assert "char* texture_path, void* payload," in path_analysis_header
    assert "int16_t arg4" not in path_analysis_header


def test_star_field_lifetime_replay_stays_guarded() -> None:
    replay = (BINJA_DIR / "sync_star_field_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for owner_name, expected_size in (
        ("Vec3", "0x0C"),
        ("tColour", "0x10"),
        ("Sprite", "0xB4"),
        ("StarManagerEntry", "0x2C"),
        ("StarManager", "0x4C"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("Vec3", "0x00", "x", "float"),
        ("tColour", "0x0C", "a", "float"),
        ("Sprite", "0x04", "flags", "SpriteFlag"),
        ("Sprite", "0x48", "position", "Vec3"),
        ("Sprite", "0x54", "velocity", "Vec3"),
        ("StarManagerEntry", "0x1C", "sprite", "Sprite*"),
        ("StarManagerEntry", "0x24", "travel_distance", "float"),
        ("StarManager", "0x3C", "entries", "StarManagerEntry*"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for index, storage, name, variable_type in (
        (245, 67, "entry_position", "Vec3*"),
        (318, 68, "entry_velocity", "Vec3*"),
        (392, 66, "scaled_velocity", "Vec3*"),
        (507, 66, "motion_entry", "StarManagerEntry*"),
        (616, 66, "sprite", "Sprite*"),
        (635, 68, "progress_sprite", "Sprite*"),
        (645, 67, "progress_step_sprite", "Sprite*"),
        (659, 66, "gravity_sprite", "Sprite*"),
        (674, 68, "color_sprite", "Sprite*"),
        (680, 68, "sprite_color", "tColour*"),
        (720, 66, "size_sprite", "Sprite*"),
        (706, 68, "size_start_sprite", "Sprite*"),
        (743, 66, "corner_entry", "StarManagerEntry*"),
        (752, 66, "corner_scale_sprite", "Sprite*"),
        (764, 66, "velocity_entry", "StarManagerEntry*"),
        (773, 66, "sprite_velocity", "Vec3*"),
        (795, 66, "position_entry", "StarManagerEntry*"),
        (803, 68, "sprite_position", "Vec3*"),
        (826, 66, "facing_refresh_sprite", "Sprite*"),
    ):
        expected = (
            '        "initialize_star_field",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}"'
        )
        assert expected in replay

    for index, storage, name, variable_type in (
        (24, 66, "distance_entry", "StarManagerEntry*"),
        (48, 72, "travel_distance", "float*"),
        (72, 66, "respawn_sprite", "Sprite*"),
        (184, 66, "respawn_position", "Vec3*"),
        (206, 66, "velocity_entry", "StarManagerEntry*"),
        (214, 66, "sprite_velocity", "Vec3*"),
        (236, 66, "motion_entry", "StarManagerEntry*"),
        (272, 66, "motion_position", "Vec3*"),
        (306, 66, "travel_entry", "StarManagerEntry*"),
        (326, 66, "alpha_entry", "StarManagerEntry*"),
    ):
        expected = (
            '        "update_star_positions",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}"'
        )
        assert expected in replay

    assert "Retyping that offset as an integer" in replay
    assert "cRStarManager::Init and cRStarManager::UpdateStars" in replay
    assert (
        '        176,\n'
        "        66,\n"
        '        "position_sprite"'
    ) not in replay
    assert "apply_user_var_updates" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay


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


def test_current_header_type_equivalence_uses_exact_parsed_type_comparison(
    monkeypatch,
) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        assert args[:2] == ("py", "exec")
        assert "current == parsed_type.type" in args[-1]
        assert "bv.type_container" in args[-1]
        assert "isolated_parsed, isolated_errors" in args[-1]
        assert "bv.platform,\n            None," in args[-1]
        return {
            "result": {
                "errors": [],
                "types": [
                    {"name": "SubTracks", "equivalent": True},
                    {"name": "LevelFileTextBuffer", "equivalent": False},
                ],
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)

    result = _narrow_sync.current_header_type_equivalence(
        Path("."),
        target="snail-mail.exe",
        header_path=Path("segment_catalog_types.h"),
    )

    assert result == {"SubTracks": True, "LevelFileTextBuffer": False}
    assert len(calls) == 1


def test_types_declare_if_changed_skips_exact_header(monkeypatch) -> None:
    monkeypatch.setattr(
        _narrow_sync,
        "current_header_type_equivalence",
        lambda *_args, **_kwargs: {"SubTracks": True, "LevelFileTextBuffer": True},
    )
    monkeypatch.setattr(
        _narrow_sync,
        "types_declare",
        lambda *_args, **_kwargs: (_ for _ in ()).throw(
            AssertionError("equivalent header should not be replayed")
        ),
    )

    result = _narrow_sync.types_declare_if_changed(
        Path("."),
        target="snail-mail.exe",
        header_path=Path("segment_catalog_types.h"),
    )

    assert result["status"] == "skipped"
    assert result["type_count"] == 2


def test_types_declare_if_changed_replays_semantic_drift(monkeypatch) -> None:
    monkeypatch.setattr(
        _narrow_sync,
        "current_header_type_equivalence",
        lambda *_args, **_kwargs: {"SubTracks": True, "LevelFileTextBuffer": False},
    )
    monkeypatch.setattr(
        _narrow_sync,
        "types_declare",
        lambda *_args, **_kwargs: {"op": "types_declare", "result": "applied"},
    )

    result = _narrow_sync.types_declare_if_changed(
        Path("."),
        target="snail-mail.exe",
        header_path=Path("segment_catalog_types.h"),
    )

    assert result["result"] == "applied"
    assert result["stale_types"] == ("LevelFileTextBuffer",)


def test_path_sync_owns_golb_follow_abis() -> None:
    source = (BINJA_DIR / "sync_path_template_types.py").read_text(encoding="utf-8")
    ida_source = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")
    compact_header = "".join(header.split())
    compact_ida_source = "".join(ida_source.split())
    golb_prototypes = source.split("GOLB_PROTO_UPDATES = (", 1)[1].split(
        "\n)\n\nCUT_SCENE_PROTO_UPDATES", 1
    )[0]

    declarations = (
        "int32_t __thiscall initialize_path_follow_golb("
        "GolbPathFollowState* state, TrackRowCell* source_cell, "
        "const Vec3* position, GolbShot* shot);",
        "int32_t __thiscall traverse_path_follow_golb("
        "GolbPathFollowState* state, float path_factor, "
        "Vec3* position, Vec3* velocity);",
    )
    for declaration in declarations:
        compact_declaration = "".join(declaration.split())
        assert declaration.removesuffix(";") in golb_prototypes
        assert compact_declaration in compact_header
        assert compact_declaration in compact_ida_source

    assert "Path* template_record;" in header
    assert "TrackRowCell* source_cell;" in header
    assert "GolbPathFollowState path_follow;" in header
    for symbol_update in (
        '("0x421770", "initialize_path_follow_golb")',
        '("0x4217b0", "traverse_path_follow_golb")',
    ):
        assert symbol_update in source
    for trusted_name in (
        '(0x421770, "initialize_path_follow_golb")',
        '(0x4217B0, "traverse_path_follow_golb")',
    ):
        assert trusted_name in ida_source
    for address in ("0x414820", "0x421770", "0x4217B0"):
        assert address in ida_source

    assert "GOLB_PATH_FOLLOW_DIRECTION_LVAR_DEFINITION = 0x421D22" in ida_source
    assert "_sync_golb_path_follow_copy_ownership" in ida_source
    assert '"Vec3 *direction_source;"' in ida_source
    assert "ida_hexrays.restore_user_lvar_settings" in ida_source
    assert '"state->shot->velocity = state->shot->direction;"' in ida_source
    assert '"shot->primary_body"' in ida_source
    assert '"golb_path_follow_copy_ownership"' in ida_source

    health = json.loads(
        (
            Path(__file__).parents[1]
            / "analysis/decompile/health_checks.json"
        ).read_text(encoding="utf-8")
    )
    ida_check = next(
        check
        for check in health["checks"]
        if check["name"] == "ida_golb_path_follow_owner_graph"
    )
    assert (
        ida_check["artifact"]
        == "analysis/decompile/ida/functions/004217b0-traverse_path_follow_golb.c"
    )
    assert (
        "state->shot->velocity = state->shot->direction;"
        in ida_check["required_substrings"]
    )
    assert "shot->primary_body" in ida_check["forbidden_substrings"]


def test_path_sync_owns_core_subgame_receiver_abis() -> None:
    source = (BINJA_DIR / "sync_path_template_types.py").read_text(encoding="utf-8")
    repair_source = (BINJA_DIR / "repair_initialize_subgame_owner.py").read_text(
        encoding="utf-8"
    )
    repair_entrypoint = (BINJA_DIR / "repair_subgame_receiver_owner.py").read_text(
        encoding="utf-8"
    )
    generic_repair_entrypoint = (
        BINJA_DIR / "repair_deferred_owner_abi.py"
    ).read_text(encoding="utf-8")
    ida_source = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")
    compact_header = "".join(header.split())
    compact_ida_source = "".join(ida_source.split())

    assert "CORE_SUBGAME_PROTO_UPDATES" in source
    assert "DEFERRED_SUBGAME_OWNER_PROTO_UPDATES" in source
    assert "REFINED_PATH_OWNER_PROTO_UPDATES" in source
    assert "DEFERRED_PATH_OWNER_PROTO_UPDATES" in source
    assert "proto_owner_deferred" in source
    assert "apply_struct_and_proto_updates" in source
    assert "apply_direct_proto_update" not in source
    assert "proto_owner_current" in source
    for symbol_update in (
        '("0x41b0a0", "get_path_nodes")',
        '("0x421dc0", "mirror_path")',
    ):
        assert symbol_update in source
    for trusted_name in (
        '(0x41B0A0, "get_path_nodes")',
        '(0x421DC0, "mirror_path")',
    ):
        assert trusted_name in ida_source
    assert "repair_deferred_owner_abi.py" in source
    assert 'f"--target {target} --function {identifier} --apply"' in source
    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"' in source
    assert '"SubRow",' in source
    assert '"TrackAttachmentRuntimeRow",' not in source
    assert "typedef struct SubRow {" in header
    assert "SubRow runtime_rows[3200];" in header
    assert "TrackAttachmentRuntimeRow" not in header
    assert '"RingOrSpecialEffectPool"' not in source
    assert '("SubSpeedUp", SUB_SPEED_UP_FIELD_UPDATES)' in source
    assert '"SaltHazardSlot"' not in source
    stable_prototypes = source.split("CORE_SUBGAME_PROTO_UPDATES = (", 1)[1].split(
        "\n)\n\n# These remaining lifecycle", 1
    )[0]
    normalization_prototypes = source.split(
        "TRACK_NORMALIZATION_VOID_PROTO_UPDATES = (", 1
    )[1].split("\n)\n\nPROTO_UPDATES", 1)[0]
    deferred_prototypes = source.split(
        "DEFERRED_SUBGAME_OWNER_PROTO_UPDATES = (", 1
    )[1].split("\n)\n\n\nDEFERRED_PATH_OWNER_PROTO_UPDATES", 1)[0]
    refined_path_prototypes = source.split(
        "REFINED_PATH_OWNER_PROTO_UPDATES = (", 1
    )[1].split("\n)\n\n\nDEFERRED_PATH_OWNER_PROTO_UPDATES", 1)[0]
    deferred_path_prototypes = source.split(
        "DEFERRED_PATH_OWNER_PROTO_UPDATES = (", 1
    )[1].split("\n)\n\n\ndef report_deferred_owner_prototypes", 1)[0]
    for function_name in ("reset_subgame", "complete_subgame"):
        assert f'"{function_name}"' in stable_prototypes
    for function_name in (
        "initialize_subgame",
        "build_subgame_level",
        "destroy_subgame",
        "update_subgame",
        "remove_subgame_bods",
        "build_track_fringe_objects",
        "get_track_grid_cell_at_world_position",
        "sample_track_floor_height_at_position",
        "spawn_track_health_pickup",
        "spawn_track_jetpack_pickup",
        "get_track_runtime_cell_at_world_z",
        "project_position_onto_track_attachment",
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
    for function_name in (
        "merge_track_tile_runs",
        "select_track_tile_edge_variants",
        "promote_track_tiles_to_fringe_variants",
        "harmonize_center_lane_floor_slide_variants",
    ):
        declaration = (
            f"void __thiscall {function_name}(SubgameRuntime* game)"
        )
        assert declaration in normalization_prototypes
        assert declaration + ";" in ida_source
        assert "".join((declaration + ";").split()) in compact_header
        repair_spec = repair_source.split(f'"{function_name}": {{', 1)[1].split(
            "\n    },", 1
        )[0]
        assert (
            '"expected_prototype": "void __thiscall(struct SubgameRuntime* game)"'
            in repair_spec
        )
        assert (
            '"stale_prototype": '
            '"int32_t __thiscall(struct SubgameRuntime* game)"'
            in repair_spec
        )
        assert '"int32_t __thiscall(struct Game* game)"' in repair_spec
        assert f'"void __thiscall {function_name}("' in repair_spec
        if function_name == "merge_track_tile_runs":
            for variable_name in (
                "row_attachment_flags",
                "seed_lane_flags",
                "cell_lane_flags",
                "cell",
                "floor_tile_cursor",
                "floor_cleanup_lane_flags",
                "slide_lane_flags_cursor",
                "slide_cleanup_lane_flags",
                "wall_tile_cursor",
                "wall_cleanup_lane_flags",
            ):
                assert f'"name": "{variable_name}"' in repair_spec
    assert "*TRACK_NORMALIZATION_VOID_PROTO_UPDATES" in source
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
        "project_position_onto_track_attachment",
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
        "0x4444B0",
    ):
        assert f'"address": {address}' in repair_source
    assert "from repair_initialize_subgame_owner import main" in repair_entrypoint
    assert "from repair_initialize_subgame_owner import main" in generic_repair_entrypoint
    assert '"legacy_prototypes": (' in repair_source
    assert '"struct SubRow* __thiscall("' in repair_source
    assert '"SubRow* __thiscall "' in repair_source
    assert "from sync_track_fringe_builder_lifetimes import (" in repair_source
    assert "TRACK_FRINGE_BUILDER_USER_VAR_UPDATES" in repair_source
    fringe_repair_spec = repair_source.split(
        '"build_track_fringe_objects": {', 1
    )[1].split("\n    },", 1)[0]
    assert "*_fringe_builder_repair_variables()" in fringe_repair_spec
    assert (
        '"SubRow* __thiscall get_track_runtime_cell_at_world_z('
        'SubgameRuntime* game, Vec3* position)"'
    ) in deferred_prototypes
    assert (
        '"SubRow* __thiscall get_track_runtime_cell_at_world_z('
        'SubgameRuntime* game, Vec3* position);"'
    ) in ida_source
    projection_declaration = (
        "void __thiscall project_position_onto_track_attachment("
        "SubgameRuntime* game, Vec3* position, float* out_angle);"
    )
    compact_projection_declaration = "".join(projection_declaration.split())
    assert compact_projection_declaration in compact_header
    assert compact_projection_declaration in compact_ida_source
    assert projection_declaration.removesuffix(";") in deferred_prototypes
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
    assert '"project_position_onto_track_attachment": 3' in ida_source
    assert "if stale and comments:" in repair_source
    assert "if stale and tags:" in repair_source
    assert '"allowed_auto_tag_types": ("Unresolved Stack Pointer Value",)' in repair_source
    assert "restore_preserved_auto_tags(repaired, preserved_auto_tags)" in repair_source
    assert "record[\"auto\"] and record[\"type\"] in ALLOWED_AUTO_TAG_TYPES" in repair_source
    assert "function_has_unpreserved_user_vars" in repair_source
    assert "stale_auto_variable_annotations" in repair_source
    assert '"user_defined": False' in repair_source
    assert "def restore_old_function():" in repair_source
    assert '"--apply"' in repair_source
    assert "Without this flag the tool" in repair_source
    assert '"is read-only. Function recreation' in repair_source
    for declaration in (
        "void __thiscall initialize_p_path_template_pair(Path* self, int32_t variant, float scale_arg, int32_t width_cells_, float start_x, float end_x, int32_t curve_segments, char* texture_a, char* texture_b, char* cap_texture)",
        "void __fastcall get_path_nodes(Path* self)",
        "void __fastcall calc_path_length_z(Path* self)",
        "void __thiscall initialize_worm_path_template_pair(Path* self, char* texture_path)",
        "void __thiscall initialize_cage2_path_template_pair(Path* self, int32_t width_cells_, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall mirror_path(Path* self, Path* source)",
    ):
        assert declaration in deferred_path_prototypes
        assert "".join(f"{declaration};".split()) in compact_header
        assert "".join(f'"{declaration};"'.split()) in compact_ida_source
    refined_prototypes = (
        (
            "void __thiscall initialize_looptheloop_path_template_pair(Path* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_looptheloop_path_template_pair(Path* self, float curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_looptheloopw_path_template_pair(Path* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_looptheloopw_path_template_pair(Path* self, float curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_loopout_path_template_pair(Path* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_loopout_path_template_pair(Path* self, float curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_hump_path_template_pair(Path* self, float curve_source, float height_scale, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_hump_path_template_pair(Path* self, float curve_source, float height_scale, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_dump_path_template_pair(Path* self, float curve_source, float height_scale, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_dump_path_template_pair(Path* self, float curve_source, float height_scale, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_halfpipe_path_template_pair(Path* self, float scale, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
            "void __thiscall initialize_halfpipe_path_template_pair(Path* self, float scale, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
        ),
        (
            "void __thiscall initialize_dip_path_template_pair(Path* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_dip_path_template_pair(Path* self, float curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_screw_path_template_pair(Path* self, int32_t curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_screw_path_template_pair(Path* self, int32_t curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_slalom_path_template_pair(Path* self, int32_t curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_slalom_path_template_pair(Path* self, int32_t curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_slalombig_path_template_pair(Path* self, int32_t curve_segments, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_slalombig_path_template_pair(Path* self, int32_t curve_segments, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_sweep_path_template_pair(Path* self, float scale_arg, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_sweep_path_template_pair(Path* self, float scale_arg, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_snake_path_template_pair(Path* self, float scale_arg, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_snake_path_template_pair(Path* self, float scale_arg, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_slalomdouble_path_template_pair(Path* self, int32_t curve_segments, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_slalomdouble_path_template_pair(Path* self, int32_t curve_segments, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_start_path_template_pair(Path* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_start_path_template_pair(Path* self, float length, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_turnover_path_template_pair(Path* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_turnover_path_template_pair(Path* self, float length, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_turnoverdouble_path_template_pair(Path* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
            "void __thiscall initialize_turnoverdouble_path_template_pair(Path* self, float length, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_turnunder_path_template_pair(Path* self, float turns, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
            "void __thiscall initialize_turnunder_path_template_pair(Path* self, float turns, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
        ),
        (
            "void __thiscall initialize_wibble_path_template_pair(Path* self, float radius, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
            "void __thiscall initialize_wibble_path_template_pair(Path* self, float radius, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
        ),
        (
            "void __thiscall initialize_invert_path_template_pair(Path* self, float radius, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
            "void __thiscall initialize_invert_path_template_pair(Path* self, float radius, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
        ),
        (
            "void __thiscall initialize_supertramp_path_template_pair(Path* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* unused_texture, char* cap_texture)",
            "void __thiscall initialize_supertramp_path_template_pair(Path* self, float length, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* unused_texture, char* cap_texture)",
        ),
        (
            "void __thiscall initialize_twister_path_template_pair(Path* self, float height, int32_t width_cells_, char handedness, char* texture_a, char* texture_b, char* vertical_texture)",
            "void __thiscall initialize_twister_path_template_pair(Path* self, float height, int32_t width_cells_, bool handedness, char* texture_a, char* texture_b, char* vertical_texture)",
        ),
        (
            "void __thiscall initialize_twister2_path_template_pair(Path* self, float height, int32_t width_cells_, char handedness, char* texture_a, char* texture_b, char* vertical_texture)",
            "void __thiscall initialize_twister2_path_template_pair(Path* self, float height, int32_t width_cells_, bool handedness, char* texture_a, char* texture_b, char* vertical_texture)",
        ),
        (
            "void __thiscall initialize_loopbow_path_template_pair(Path* self, float curve_scale, uint32_t width_cells_arg, char mode, char* texture_a, char* texture_b, char* vertical_texture)",
            "void __thiscall initialize_loopbow_path_template_pair(Path* self, float curve_scale, uint32_t width_cells_arg, bool mode, char* texture_a, char* texture_b, char* vertical_texture)",
        ),
        (
            "void __thiscall initialize_toad_path_template_pair(Path* self, char turn_left, char* texture_a, char* texture_b, char* vertical_texture)",
            "void __thiscall initialize_toad_path_template_pair(Path* self, bool turn_left, char* texture_a, char* texture_b, char* vertical_texture)",
        ),
        (
            "void __thiscall initialize_hill_valley_path_template_pair(Path* self, int32_t width_cells_, float height, float length, char centered, char* texture_a, char* texture_b, char* vertical_texture)",
            "void __thiscall initialize_hill_valley_path_template_pair(Path* self, int32_t width_cells_, float height, float length, bool centered, char* texture_a, char* texture_b, char* vertical_texture)",
        ),
        (
            "void __thiscall initialize_sbend_path_template_pair(Path* self, int32_t width_cells_, float height, float z_amplitude, char centered, char* texture_a, char* texture_b, char* vertical_texture)",
            "void __thiscall initialize_sbend_path_template_pair(Path* self, int32_t width_cells_, float height, float z_amplitude, bool centered, char* texture_a, char* texture_b, char* vertical_texture)",
        ),
    )
    for previous_prototype, desired_prototype in refined_prototypes:
        assert previous_prototype in refined_path_prototypes
        assert desired_prototype in refined_path_prototypes
        assert previous_prototype not in deferred_path_prototypes
        assert "".join(f"{desired_prototype};".split()) in compact_header
        assert "".join(f'"{desired_prototype};"'.split()) in compact_ida_source
    assert "def apply_refined_owner_prototypes(" in source
    assert "elif observed_normalized == previous_normalized:" in source
    assert "updates=((identifier, desired_prototype),)" in source
    assert '"owner ABI is not the exact previously recovered form; "' in source
    for function_name in (
        "initialize_looptheloop_path_template_pair",
        "initialize_looptheloopw_path_template_pair",
        "initialize_loopout_path_template_pair",
        "initialize_hump_path_template_pair",
        "initialize_dump_path_template_pair",
        "initialize_dip_path_template_pair",
        "initialize_screw_path_template_pair",
        "initialize_slalom_path_template_pair",
        "initialize_slalombig_path_template_pair",
        "initialize_sweep_path_template_pair",
        "initialize_snake_path_template_pair",
        "initialize_supertramp_path_template_pair",
        "initialize_slalomdouble_path_template_pair",
        "initialize_start_path_template_pair",
        "initialize_turnover_path_template_pair",
        "initialize_turnoverdouble_path_template_pair",
        "initialize_turnunder_path_template_pair",
        "initialize_wibble_path_template_pair",
        "initialize_invert_path_template_pair",
        "initialize_halfpipe_path_template_pair",
        "initialize_twister_path_template_pair",
        "initialize_twister2_path_template_pair",
        "initialize_p_path_template_pair",
        "initialize_loopbow_path_template_pair",
        "initialize_hill_valley_path_template_pair",
        "initialize_sbend_path_template_pair",
        "get_path_nodes",
        "calc_path_length_z",
        "initialize_worm_path_template_pair",
        "initialize_cage2_path_template_pair",
        "initialize_toad_path_template_pair",
        "mirror_path",
    ):
        assert f'"{function_name}": _path_function_spec(' in repair_source
    assert '"owner_type": "Path"' in repair_source
    assert '"owner_size": PATH_SIZE' in repair_source
    assert '"storage": 8' in repair_source
    assert '"name": "arg2"' in repair_source
    assert "DISCARD_VARIABLES = SPEC.get(\"discard_variables\", ())" in repair_source
    assert "STALE_PARAMETER_COUNTS = set(" in repair_source
    assert "STALE_VARIABLE_ANNOTATIONS = SPEC.get(" in repair_source
    assert "ALLOWED_MISSING_STALE_VARIABLE_KEYS = {" in repair_source
    assert 'stale_variable_annotations=((20, "arg5", "char*"),)' in repair_source
    assert 'stale_variable_annotations=((24, "arg6", "char*"),)' in repair_source
    assert 'missing_stale_variable_storages=(16,)' in repair_source
    assert 'missing_stale_variable_storages=(24,)' in repair_source
    assert 'before_annotations["parameter_count"] not in allowed_parameter_counts' in repair_source
    assert "stale_discard_variable_changed" in repair_source
    assert "stale_variable_annotation_changed" in repair_source
    assert "discarded_variable_survived_repair" in repair_source
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


def test_golb_replays_preserve_real_lifecycle_and_emitter_abis() -> None:
    binja_source = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )

    declarations = (
        "GolbShot* __thiscall initialize_golb_shot(GolbShot* shot)",
        "void __thiscall kill_golb(GolbShot* shot)",
        "void __thiscall update_golb_ai(GolbShot* shot)",
        "void __thiscall create_golb(GolbShot* shot, Player* player, int32_t spawn_selector, int32_t emitter_index)",
        "void __thiscall shoot_subgoldy(Player* owner, Player* shoot_source)",
        "Sprite* __thiscall spawn_golb_trail_sprite(GolbShot* shot, Vec3* position)",
        "void __thiscall spawn_golb_smoke(GolbShot* shot, Vec3* position)",
        "void __thiscall spawn_golb_impact_sprite(GolbShot* shot, Vec3* position)",
    )
    for declaration in declarations:
        assert declaration in binja_source
        assert f'"{declaration};"' in ida_source

    assert "no-argument auto prototype" not in binja_source


def test_golb_shot_nested_vapour_owner_is_replayed() -> None:
    repo_root = Path(__file__).parents[1]
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/golb.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )

    analysis_owner = (
        "typedef struct GolbShot {\n"
        "    RenderableBod primary_body;\n"
        "    Vapour vapour;\n"
        "    struct GolbShot* vapour_owner_shot;\n"
        "    cRGolbRocket tertiary_body;"
    )
    matcher_owner = (
        "    RenderableBod primary_body; // +0x000, projectile AI/list owner\n"
        "    Vapour vapour; // +0x080, complete kind-1 trail renderer\n"
        "    GolbShot* vapour_owner_shot; // +0x114, kind-1 embedded-body backlink\n"
        "    GolbRocket tertiary_body; // +0x118, authored cRGolbRocket owner"
    )
    assert analysis_owner in analysis_header
    assert matcher_owner in matcher_header
    analysis_golb_owner = analysis_header.split("typedef struct GolbShot {", 1)[
        1
    ].split("} GolbShot;", 1)[0]
    matcher_golb_owner = matcher_header.split("class GolbShot {", 1)[1].split(
        "typedef char GolbShot_must_be_0x2e8", 1
    )[0]
    for source in (analysis_golb_owner, matcher_golb_owner):
        assert "secondary_body" not in source
        assert "TransformMatrix live_matrix" not in source

    for update in (
        '("0x000", "primary_body", "RenderableBod")',
        '("0x080", "vapour", "Vapour")',
        '("0x114", "vapour_owner_shot", "GolbShot*")',
        '("0x118", "tertiary_body", "cRGolbRocket")',
    ):
        assert update in binja_sync
    assert "KILL_GOLB_OWNER_USER_VAR_UPDATES" in binja_sync
    assert '"shot_cursor",\n        "GolbShot*"' in binja_sync
    assert "*KILL_GOLB_OWNER_USER_VAR_UPDATES" in binja_sync

    for marker in (
        "GOLB_SHOT_EXPECTED_SIZE = 0x2E8",
        "GOLB_SHOT_PREFIX_END = 0x198",
        "GOLB_SHOT_PREFIX_MEMBERS",
        "_sync_golb_shot_prefix_owner(header_path)",
        '"golb_shot_prefix_owner": golb_shot_prefix_owner',
    ):
        assert marker in ida_sync
    for address in ("0x408690", "0x40ACF0", "0x414670", "0x415280"):
        assert address in ida_sync

    artifact_root = repo_root / "analysis/decompile"
    for lane in ("binja", "ida"):
        artifacts = {
            name: (artifact_root / lane / "functions" / filename).read_text(
                encoding="utf-8"
            )
            for name, filename in (
                ("constructor", "00408690-initialize_golb_shot.c"),
                ("kill", "00414670-kill_golb.c"),
                ("update", "00414820-update_golb_ai.c"),
                ("create", "00415280-create_golb.c"),
            )
        }
        for artifact in artifacts.values():
            assert "secondary_body" not in artifact
            assert "shot->live_matrix" not in artifact
        assert "shot->vapour" in artifacts["constructor"]
        assert "shot->tertiary_body" in artifacts["constructor"]
        assert "shot->primary_body" in artifacts["kill"]
        assert "shot->vapour.body" in artifacts["kill"]
        assert "shot->tertiary_body" in artifacts["kill"]
        assert "add_vapour_point(&shot->vapour" in artifacts["update"]
        assert "shot->tertiary_body.transform" in artifacts["update"]
        assert "shot->vapour_owner_shot = shot" in artifacts["create"]
        assert "shot->vapour.body" in artifacts["create"]
        assert "shot->tertiary_body" in artifacts["create"]


def test_runtime_pool_constructor_replay_preserves_nested_owners() -> None:
    binja_source = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")
    compact_header = "".join(header.split())

    declarations = (
        "RenderableBod* __thiscall initialize_noop_renderable_bod(RenderableBod* body)",
        "SubgameRuntime* __thiscall initialize_runtime_pools_and_path_template_bank(SubgameRuntime* game)",
        "SubRow* __thiscall initialize_track_row_runtime(SubRow* row)",
        "Fringe* __thiscall initialize_fringe_object(Fringe* fringe)",
        "Object* __thiscall initialize_object_constructor_thunk(Object* object)",
    )
    for declaration in declarations:
        assert declaration in binja_source
        assert declaration + ";" in ida_source
        assert "".join(declaration.split()) + ";" in compact_header

    for address, name in (
        ("0x408040", "initialize_noop_renderable_bod"),
        ("0x408060", "initialize_runtime_pools_and_path_template_bank"),
        ("0x408590", "initialize_track_row_runtime"),
        ("0x408650", "initialize_fringe_object"),
        ("0x42f6e0", "initialize_object_constructor_thunk"),
        ("0x4972b0", "g_noop_runtime_callback_table"),
        ("0x497330", "g_row_model_vtable"),
        ("0x497344", "g_fringe_vtable"),
    ):
        assert f'("{address}", "{name}")' in binja_source

    assert "typedef struct RowModel" in header
    assert "RenderableBod body;" in header
    assert "Vec3 velocity;" in header
    assert "RowModel row_model;" in header
    assert "BodBase bod;" in header
    assert '("RowModel", ROW_MODEL_FIELD_UPDATES)' in binja_source
    assert '("0x04", "row_model", "RowModel")' in binja_source
    assert '("0x4972b0", "void*")' in binja_source


def test_subgoldy_replays_preserve_void_lifecycle_abis() -> None:
    binja_source = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")
    compact_header = "".join(header.split())

    declarations = (
        "void __thiscall show_subgoldy_lives(Player* player)",
        "void __thiscall begin_post_follow_carryover(Player* player)",
        "void __thiscall initialize_subgoldy_ghost(Player* player, int32_t owner)",
        "void __thiscall update_subgoldy(Player* player)",
        "void __thiscall play_subgoldy_shoot_sfx(Player* player)",
        "void __thiscall set_subgoldy_ghost_z(Player* player, float ghost_z)",
        "void __thiscall add_subgoldy_score(Player* player, int32_t score_kind, int32_t bonus_score)",
        "void __thiscall clear_subgoldy_score_buckets(Player* player)",
        "void __thiscall display_score_stats(Player* player)",
        "void __thiscall initialize_subgoldy_resurrect(Player* player, int32_t final_loss)",
        "void __thiscall update_subgoldy_resurrect(Player* player)",
        "void __thiscall handle_subgoldy_collisions(Player* player)",
        "void __thiscall kill_subgoldy(Player* player)",
        "void __thiscall initialize_subgoldy_death(Player* player)",
    )
    for declaration in declarations:
        assert declaration in binja_source
        assert f'"{declaration};"' in ida_source
        assert "".join(f"{declaration};".split()) in compact_header

    for stale_declaration in (
        "int32_t __thiscall update_subgoldy(Player* player)",
        "int32_t __thiscall begin_post_follow_carryover(Player* player)",
        "Sprite* __thiscall set_subgoldy_ghost_z(Player* player, float ghost_z)",
        "int32_t __thiscall initialize_subgoldy_resurrect(Player* player, int32_t final_loss)",
        "void __fastcall update_subgoldy_resurrect(Player* player)",
        "int32_t __thiscall handle_subgoldy_collisions(Player* player)",
    ):
        assert stale_declaration not in binja_source
        assert stale_declaration not in ida_source
        assert stale_declaration not in header


def test_high_score_replays_preserve_void_insertion_abis() -> None:
    binja_source = (BINJA_DIR / "sync_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "bn_high_score_bank_types.h").read_text(
        encoding="utf-8"
    )
    compact_header = "".join(header.split())

    binja_declarations = (
        "void __thiscall add_arcade_high_score(SubHighScore* bank, SubSolution* record, int32_t level_arg)",
        "void __thiscall add_survival_high_score(SubHighScore* bank, SubSolution* record)",
        "void __thiscall save_high_scores_and_config(SubHighScore* bank, uint8_t save_mask)",
    )
    ida_declarations = (
        "void __thiscall add_arcade_high_score(SubHighScore* bank, SubSolution* record, int level_arg);",
        "void __thiscall add_survival_high_score(SubHighScore* bank, SubSolution* record);",
        "void __thiscall save_high_scores_and_config(SubHighScore* bank, unsigned char save_mask);",
    )
    for declaration in binja_declarations:
        assert declaration in binja_source
        assert "".join(f"{declaration};".split()) in compact_header
    for declaration in ida_declarations:
        assert f'"{declaration}"' in ida_source

    assert "int32_t __thiscall add_arcade_high_score" not in binja_source
    assert "int32_t __thiscall add_survival_high_score" not in binja_source
    assert "char* __thiscall save_high_scores_and_config" not in binja_source
    assert '"int __thiscall add_arcade_high_score' not in ida_source
    assert '"int __thiscall add_survival_high_score' not in ida_source
    assert '"char* __thiscall save_high_scores_and_config' not in ida_source


def test_ranked_high_score_replays_preserve_owned_record_cursors() -> None:
    binja_source = (BINJA_DIR / "sync_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )
    headers = tuple(
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in (
            "bn_high_score_bank_types.h",
            "ida_high_score_bank_types.h",
        )
    )

    for header in headers:
        assert "typedef struct SubHighScorePostalRankCursor" in header
        assert "uint8_t bank_prefix[0x8];" in header
        assert "} SubHighScorePostalRankCursor;" in header
        assert "typedef struct SubHighScoreSurvivalRankCursor" in header
        assert "uint8_t bank_prefix[0x15c648];" in header
        assert "} SubHighScoreSurvivalRankCursor;" in header

    assert '"RegisterVariableSourceType",\n        144,\n        68,' in binja_source
    assert '"postal_rank_cursor"' in binja_source
    assert '"SubHighScorePostalRankCursor*"' in binja_source
    assert '"RegisterVariableSourceType",\n        168,\n        69,' in binja_source
    assert '"survival_rank_cursor"' in binja_source
    assert '"SubHighScoreSurvivalRankCursor*"' in binja_source

    assert "def _sync_named_pointer_lvar(" in ida_source
    assert "and lvar.defea == definition_address" in ida_source
    assert "and candidate.defea == definition_address" in ida_source
    assert "_normalize_struct_pointer_type" in ida_source
    for expected in (
        "definition_address=0x417731",
        'target_name="postal_rank_cursor"',
        'target_struct_name="SubHighScorePostalRankCursor"',
        "definition_address=0x417829",
        'target_name="survival_rank_cursor"',
        'target_struct_name="SubHighScoreSurvivalRankCursor"',
    ):
        assert expected in ida_source
    assert 'accepted_types={"SubSolution * *",' in ida_source
    assert "store_address = 0x41787C" in ida_source
    assert 'expected_bytes = bytes.fromhex("89 aa e0 fa 6f 00")' in ida_source
    assert "idc.op_num(store_address, 0)" in ida_source
    assert 'expected_owner = "g_game_base->subgame.sub_high_score.active_record_bank"' in ida_source


def test_high_score_replay_preserves_embedded_record_element_borrows() -> None:
    repo_root = Path(__file__).parents[1]
    binja_source = (BINJA_DIR / "sync_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    assert "RECORD_CURSOR_EXPECTED_SIZES" in binja_source
    for expected_size in (
        '"SubSolution": 0x1FAC0',
        '"SubHighScore": 0x947648',
        '"SubgameRuntime": 0x1272838',
    ):
        assert expected_size in binja_source
    assert "SCALAR_SIZE_DISPLAY_UPDATES" in binja_source
    for scalar_display_fragment in (
        '"0x41794c"',
        '"68 40 4b 4c 00"',
        "0x4C4B40",
        "0xFFFFFFFF",
        '"UnsignedHexadecimalDisplayType"',
        'allocate_tracked_memory(0x4c4b40, "High Score Table")',
        '"allocate_tracked_memory(&(*(*g_texture_refs.entries)"',
        "apply_int_display_updates",
    ):
        assert scalar_display_fragment in binja_source
    assert "EMBEDDED_RECORD_CURSOR_USER_VAR_UPDATES" in binja_source
    for function_name, index, storage, cursor_name in (
        ("initialize_high_score_tables", 7, 73, "postal_record_cursor"),
        ("initialize_high_score_tables", 45, 73, "survival_record_cursor"),
        ("initialize_high_score_tables", 86, 73, "time_trial_record_cursor"),
        ("save_high_scores_and_config", 39, 73, "postal_record_cursor"),
        ("save_high_scores_and_config", 118, 73, "survival_record_cursor"),
        ("save_high_scores_and_config", 196, 73, "time_trial_record_cursor"),
        ("initialize_subgame", 175, 66, "selected_record"),
    ):
        update = (
            f'"{function_name}",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{cursor_name}",\n'
            '        "SubSolution*",'
        )
        assert update in binja_source

    assert "--record-cursor-only" in binja_source
    assert "if args.record_cursor_only:" in binja_source
    assert "require_record_cursor_dependencies" in binja_source
    for decompile_fragment in (
        "struct SubSolution* postal_record_cursor = &bank->postal_records",
        "struct SubSolution* survival_record_cursor = &bank->survival_records",
        "struct SubSolution* time_trial_record_cursor = "
        "&bank->time_trial_route_records",
        "struct SubSolution* selected_record",
        "game->sub_high_score.active_record_bank = selected_record",
        "allocate_tracked_memory(0x4c4b40",
        '"g_texture_refs"',
    ):
        assert decompile_fragment in health_checks
    assert '"struct SubSolution (*"' in health_checks


def test_subgame_life_stock_replay_preserves_pointer_slot_borrows() -> None:
    repo_root = Path(__file__).parents[1]
    source = (
        BINJA_DIR / "sync_subgame_life_stock_lifetimes.py"
    ).read_text(encoding="utf-8")
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    for expected in (
        '"FrontendWidget": 0x724',
        '"SubgameRuntime": 0x1272838',
        '0x35BB98: ("life_stock_widgets", "FrontendWidget*[9]")',
        "LIFE_STOCK_WIDGET_CURSOR_USER_VAR_UPDATES",
        "current_struct_fields_batch",
        "apply_user_var_updates",
        "verify_life_stock_widget_owner_layouts",
    ):
        assert expected in source
    for function_name, index in (
        ("initialize_subgame", 662),
        ("destroy_subgame", 790),
    ):
        update = (
            f'"{function_name}",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            "        72,\n"
            '        "life_stock_widget_cursor",\n'
            '        "FrontendWidget**",'
        )
        assert update in source
    for fragment in (
        "struct FrontendWidget** life_stock_widget_cursor",
        "life_stock_widget_cursor = &life_stock_widget_cursor[1]",
        '"struct FrontendWidget* (*"',
        "FrontendWidget **life_stock_widgets;",
        "++life_stock_widgets;",
        "*life_stock_widgets++",
    ):
        assert fragment in health_checks


def test_runtime_pool_constructor_replay_preserves_element_borrows() -> None:
    repo_root = Path(__file__).parents[1]
    source = (
        BINJA_DIR / "sync_runtime_pool_constructor_lifetimes.py"
    ).read_text(encoding="utf-8")
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    for expected in (
        '"SubgameRuntime": 0x1272838',
        '"SubHealth": 0x74',
        '"Slug": 0xEC',
        '"Banner": 0x60',
        '"SubGarbage": 0xC4',
        '"SubRing": 0x1F8',
        '"TrackRowCell": 0x54',
        '"Path": 0xA8',
        '0x356000: ("health_pickups", "SubHealth[8]")',
        '0x3BFAC8: ("runtime_cells", "TrackRowCell[3200][8]")',
        '0xFF2914: ("path_pairs", "PathPair[63]")',
        "RUNTIME_POOL_CONSTRUCTOR_CURSOR_USER_VAR_UPDATES",
        "current_struct_fields_batch",
        "apply_user_var_updates",
        "verify_runtime_pool_constructor_owner_layouts",
    ):
        assert expected in source
    for index, variable_name, variable_type in (
        (334, "health_pickup_cursor", "SubHealth*"),
        (358, "slug_cursor", "Slug*"),
        (433, "banner_cursor", "Banner*"),
        (463, "garbage_hazard_cursor", "SubGarbage*"),
        (490, "ring_effect_cursor", "SubRing*"),
        (628, "runtime_cell_cursor", "TrackRowCell*"),
        (679, "path_template_cursor", "Path*"),
    ):
        update = (
            '"initialize_runtime_pools_and_path_template_bank",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            "        73,\n"
            f'        "{variable_name}",\n'
            f'        "{variable_type}",'
        )
        assert update in source
    for fragment in (
        "struct SubHealth* health_pickup_cursor",
        "struct Slug* slug_cursor",
        "struct Banner* banner_cursor",
        "struct SubGarbage* garbage_hazard_cursor",
        "struct SubRing* ring_effect_cursor",
        "struct TrackRowCell* runtime_cell_cursor",
        "struct Path* path_template_cursor",
        '"struct SubHealth (*"',
        '"struct SubGarbage (*"',
        '"struct TrackRowCell (*"',
        '"struct PathPair (*"',
    ):
        assert fragment in health_checks


def test_blink_random_replay_preserves_sample_borrow() -> None:
    repo_root = Path(__file__).parents[1]
    source = (BINJA_DIR / "sync_blink_random_lifetimes.py").read_text(
        encoding="utf-8"
    )
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    for expected in (
        '"Player": 0x4364',
        '"SubgameRuntime": 0x1272838',
        '0x3BB700: ("blink_random_index", "int32_t")',
        '0x3BB704: ("blink_random_samples", "float[24]")',
        '0x3BB764: ("player", "Player")',
        "BLINK_RANDOM_SAMPLE_CURSOR_USER_VAR_UPDATES",
        "current_struct_fields_batch",
        "apply_user_var_updates",
        "verify_blink_random_owner_layout",
        '"initialize_blink_random",\n'
        '        "RegisterVariableSourceType",\n'
        "        13,\n"
        "        72,\n"
        '        "blink_sample_cursor",\n'
        '        "float*",',
    ):
        assert expected in source
    for fragment in (
        "float* blink_sample_cursor = &game->blink_random_samples",
        "blink_sample_cursor = &blink_sample_cursor[1]",
        "blink_sample_cursor[-1] =",
        '"float (*"',
        '"(blink_sample_cursor - 0x3bb704)"',
    ):
        assert fragment in health_checks


def test_snail_hotspot_replay_preserves_local_and_world_borrows() -> None:
    repo_root = Path(__file__).parents[1]
    source = (BINJA_DIR / "sync_snail_hotspot_lifetimes.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_snail_presentation_types.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    for expected in (
        '"Vec3": 0x0C',
        '"SnailHotspotLocalZCursorView": 0x0C',
        '"TransformMatrix": 0x40',
        '"ObjectFaceQuad": 0x30',
        '"ObjectFaceQuadTextureCursorView": 0x30',
        '"Object": 0xDC',
        '"RenderableBod": 0x80',
        '"Snail": 0x19B4',
        '0x02: ("vertex_0", "uint16_t")',
        '0x0C: ("texture_ref", "TextureRef*")',
        '0x38: ("vertices", "Vec3*")',
        '0x54: ("facequad_count", "int32_t")',
        '0x5C: ("facequads", "ObjectFaceQuad*")',
        '0x15CC: ("snail_hotspot_source_body", "RenderableBod")',
        '0x164C: ("snail_hotspot_body", "RenderableBod")',
        '0x16CC: ("snail_hotspots_local", "Vec3[19]")',
        '0x17B0: ("snail_hotspots_world", "Vec3[19]")',
        "ensure_hotspot_analysis_views",
        "current_header_type_equivalence",
        "types_declare_missing_only",
        "SNAIL_HOTSPOT_CURSOR_USER_VAR_UPDATES",
        "current_struct_fields_batch",
        "apply_user_var_updates",
        "verify_snail_hotspot_owner_layout",
    ):
        assert expected in source
    for index, storage, variable_name, variable_type in (
        (3, 71, "hotspot_model", "Object*"),
        (15, 69, "hotspot_name_cursor", "char**"),
        (
            20,
            72,
            "hotspot_local_z_cursor",
            "SnailHotspotLocalZCursorView*",
        ),
        (
            63,
            73,
            "hotspot_face_texture_cursor",
            "ObjectFaceQuadTextureCursorView*",
        ),
        (124, 66, "hotspot_source_vertex", "Vec3*"),
    ):
        update = (
            '"extract_snail_local_hotspots",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{variable_name}",\n'
            f'        "{variable_type}",'
        )
        assert update in source
    for index, storage, variable_name in (
        (13, 71, "hotspot_world_cursor"),
        (25, 66, "hotspot_local_slot"),
        (97, 67, "hotspot_world_slot"),
    ):
        update = (
            '"build_snail_world_hotspots",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{variable_name}",\n'
            '        "Vec3*",'
        )
        assert update in source
    for index, storage, variable_name, variable_type in (
        (11, 69, "hotspot_index", "int32_t"),
        (34, 72, "hotspot_transform", "TransformMatrix*"),
    ):
        update = (
            '"build_snail_world_hotspots",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{variable_name}",\n'
            f'        "{variable_type}",'
        )
        assert update in source
    for fragment in (
        "int32_t hotspot_index = 0",
        "struct Vec3* hotspot_world_cursor = &snail->snail_hotspots_world",
        "struct TransformMatrix* hotspot_transform",
        "(hotspot_world_cursor - 0xe4)->x",
        "struct Vec3* hotspot_world_slot = hotspot_world_cursor",
        "hotspot_world_cursor = &hotspot_world_cursor[1]",
        "hotspot_world_slot->x = vector.x",
        "struct Object* hotspot_model = snail->snail_hotspot_body.bod.object",
        "char** hotspot_name_cursor = &data_4a4aa0",
        "struct SnailHotspotLocalZCursorView* hotspot_local_z_cursor",
        "struct ObjectFaceQuadTextureCursorView* hotspot_face_texture_cursor",
        "hotspot_face_texture_cursor->texture_ref",
        "struct Vec3* hotspot_source_vertex",
        '"struct Vec3 (*"',
        '"__offset(0x16cc)"',
        '"(hotspot_world_slot - 0x17b0)"',
    ):
        assert fragment in health_checks
    for fragment in (
        "typedef struct __ptr_offset(0x08)",
        "__base(Vec3, 0x00) SnailHotspotLocalZCursorView",
        "SnailHotspotLocalZCursorView_must_be_0x0c",
        "typedef struct __ptr_offset(0x0c)",
        "__base(ObjectFaceQuad, 0x00) ObjectFaceQuadTextureCursorView",
        "ObjectFaceQuadTextureCursorView_must_be_0x30",
    ):
        assert fragment in header
    for fragment in (
        "HOTSPOT_LVAR_SPECS = (",
        '"hotspot_index"',
        '"hotspot_world_cursor"',
        '"hotspot_transform"',
        '"hotspot_world_slot"',
        '"hotspot_model"',
        '"hotspot_name_cursor"',
        '"hotspot_local_z_cursor"',
        '"hotspot_face_texture_cursor"',
        '"hotspot_source_vertex"',
        "0x445CDC",
        "0x445CDE",
        "0x445CF3",
        "0x445D32",
        "0x445D54",
        "0x445D60",
        "0x445D65",
        "0x445D90",
        "0x445DCD",
        "_sync_named_lvar",
        "named_lvar_readback_failed",
    ):
        assert fragment in ida_source


def test_contact_target_search_replay_preserves_entry_borrows() -> None:
    repo_root = Path(__file__).parents[1]
    source = (
        BINJA_DIR / "sync_contact_target_search_lifetimes.py"
    ).read_text(encoding="utf-8")
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    for expected in (
        '"Vec3": 0x0C',
        '"ContactTargetEntry": 0x18',
        '"EnemyManager": 0x1804',
        '0x04: ("position", "Vec3")',
        '0x04: ("entries", "ContactTargetEntry[256]")',
        "CONTACT_TARGET_SEARCH_USER_VAR_UPDATES",
        "current_struct_fields_batch",
        "apply_user_var_updates",
        "verify_contact_target_search_owner_layout",
    ):
        assert expected in source
    for source_type, index, storage, variable_name, variable_type in (
        (
            "RegisterVariableSourceType",
            39,
            72,
            "position_z_cursor",
            "float*",
        ),
        (
            "StackVariableSourceType",
            11,
            -28,
            "nearest_entry",
            "ContactTargetEntry*",
        ),
    ):
        update = (
            '"search_path_for_golb",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{variable_name}",\n'
            f'        "{variable_type}",'
        )
        assert update in source
    for fragment in (
        "float* position_z_cursor = &manager->entries[0].position.z",
        "struct ContactTargetEntry* nearest_entry",
        "position_z_cursor[-2]",
        "position_z_cursor[-1]",
        "nearest_entry = &position_z_cursor[-3]",
        "position_z_cursor = &position_z_cursor[6]",
        "return nearest_entry",
        '"struct ContactTargetEntry (*"',
        '"(position_z_cursor - 0x10)->entries"',
    ):
        assert fragment in health_checks


def test_anim_manager_replay_preserves_queue_and_slot_borrows() -> None:
    repo_root = Path(__file__).parents[1]
    source = (
        BINJA_DIR / "sync_anim_manager_queue_lifetimes.py"
    ).read_text(encoding="utf-8")
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    for expected in (
        '"ObjectAnimation": 0x14',
        '"Object": 0xDC',
        '"RenderableBod": 0x80',
        '"PresentationAnimationSlot": 0x80',
        '"AnimManager": 0x48',
        '0xBC: ("animation", "ObjectAnimation*")',
        '0x14: ("queued_animations", "int32_t[10]")',
        '0x40: ("target_model", "RenderableBod*")',
        '0x44: ("animation_slots", "PresentationAnimationSlot*")',
        "SAVED_MANAGER_DEFINITIONS",
        "NEXT_PROGRESS_VAR",
        "ANIM_MANAGER_QUEUE_USER_VAR_UPDATES",
        "current_struct_fields_batch",
        "apply_split_away_user_var_update",
        "apply_user_var_updates",
        "verify_anim_manager_queue_owner_layout",
        '("0x4447d0", "mlil", "StackVariableSourceType", 524288, -4)',
        '"StackVariableSourceType",\n    58,\n    -4,',
        'variable_name="next_progress"',
        'variable_type="float"',
    ):
        assert expected in source
    for index, storage, variable_name, variable_type in (
        (289, 66, "queue_cursor", "int32_t*"),
        (333, 72, "slot_object", "Object**"),
    ):
        update = (
            '"update_anim_manager",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{variable_name}",\n'
            f'        "{variable_type}",'
        )
        assert update in source
    for fragment in (
        "float next_progress =",
        "int32_t* queue_cursor = &manager->queued_animations",
        "struct Object** slot_object = &manager->animation_slots[*queue_cursor]",
        "struct ObjectAnimation* animation = (*slot_object)->animation",
        "manager->target_model->bod.object = *slot_object",
        "*queue_cursor = queue_cursor[1]",
        "queue_cursor = &queue_cursor[1]",
        '"manager_1 = fconvert.s"',
        '"int32_t (*"',
        '"int32_t* esi_4"',
        '"(queue_cursor - 0x14)->queued_animations"',
    ):
        assert fragment in health_checks


def test_high_score_screen_replays_preserve_record_and_widget_cursors() -> None:
    binja_source = (BINJA_DIR / "sync_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )

    for source_type, index, storage, name, type_name in (
        ("RegisterVariableSourceType", 451, 69, "row", "int32_t"),
        (
            "RegisterVariableSourceType",
            453,
            66,
            "record_offset_bytes",
            "int32_t",
        ),
        ("StackVariableSourceType", 456, -204, "saved_row", "int32_t"),
        (
            "StackVariableSourceType",
            460,
            -200,
            "saved_record_offset_bytes",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            464,
            72,
            "name_widget_cursor",
            "FrontendWidget**",
        ),
    ):
        update = (
            '"initialize_high_score_screen",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}",'
        )
        assert update in binja_source

    for expected in (
        "def _sync_high_score_screen_active_bank_operands()",
        '(0x416A89, 1, 0x6FFAE8, "8d 88 e8 fa 6f 00")',
        '(0x416A33, 0, 0x6FFAE0, "89 90 e0 fa 6f 00")',
        '(0x416F2C, 1, 0x6FFAE0, "8b 91 e0 fa 6f 00")',
        "idc.op_num(operand_address, operand_index)",
        '"byte_6FFAE0", "unk_6FFAE4", "g_parcel_set_buckets"',
        "def _sync_high_score_screen_loop_lvars()",
        "definition_address=0x416AD4",
        'target_name="row"',
        "definition_address=0x416AD6",
        'target_name="record_offset_bytes"',
        "definition_address=0x416AE1",
        'target_name="name_widget_cursor"',
        "definition_address=0x416AD9",
        'target_name="saved_row"',
        "definition_address=0x416ADD",
        'target_name="record_index"',
        '"high_score_screen_loop_lvars": high_score_screen_loop_lvars',
    ):
        assert expected in ida_source


def test_high_score_lifecycle_replays_complete_owner_graph() -> None:
    repo_root = Path(__file__).parents[1]
    binja_source = (
        BINJA_DIR / "sync_high_score_screen_types.py"
    ).read_text(encoding="utf-8")
    ida_source = (IDA_DIR / "apply_frontend_replay_types.py").read_text(
        encoding="utf-8"
    )
    operand_block = ida_source.split(
        "HIGH_SCORE_UPDATE_BANK_OFFSET_OPERANDS = (", 1
    )[1].split("\n)\n\nHIGH_SCORE_LIFECYCLE", 1)[0]

    assert operand_block.count("    (0x") == 6
    for operand_spec in (
        "(0x4172C5, 1, 0x6FFAE0)",
        "(0x417377, 1, 0x6FFAE0)",
        "(0x41744F, 1, 0x6FFAE4)",
        "(0x41746F, 1, 0x6FFAE0)",
        "(0x4174C6, 1, 0x6FFAE0)",
        "(0x417527, 1, 0x6FFAE4)",
    ):
        assert operand_spec in operand_block

    for selector, address in (
        ("destroy_high_score_screen", "0x417220"),
        ("update_high_score_screen", "0x417260"),
        ("exit_high_score_screen", "0x417B50"),
    ):
        assert f'"{selector}": {address}' in ida_source
        assert selector in binja_source.split(
            "HIGH_SCORE_LIFECYCLE_REANALYSIS_FUNCTIONS", 1
        )[1]

    assert "reanalyze_functions" in binja_source
    assert (
        "identifiers=HIGH_SCORE_LIFECYCLE_REANALYSIS_FUNCTIONS"
        in binja_source
    )
    for owner in (
        "g_game_base->subgame.sub_high_score.active_record_bank",
        "g_game_base->subgame.sub_high_score.active_record_count",
        "g_game_base->players[0].player_name",
        "g_game_base->players[0].frontend_state",
        "g_game_base->players[0].redispatch_requested",
        "g_game_base->subgame.selected_level_record",
        "g_game_base->subgame.selected_level_record_active",
        "g_game_base->subgame.selected_level_record_persistent",
        "g_game_base->subgame.selected_level_record_cursor",
        "g_game_base->subgame.subgame_rebuild_selector",
    ):
        assert owner in ida_source

    assert "idc.op_num(address, operand_index)" in ida_source
    assert "ida_hexrays.mark_cfunc_dirty(address, True)" in ida_source
    assert '"selector": "cRHighScore lifecycle"' in ida_source
    assert (
        '"high_score_lifecycle_owner_graph": (\n'
        "                    high_score_lifecycle_owner_graph\n"
        "                )"
    ) in ida_source

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    bn_destroy = checks["bn_high_score_destroy_root_owners"]
    bn_update = checks["bn_high_score_update_root_owners"]
    bn_exit_screen = checks["bn_high_score_exit_root_owners"]
    destroy = checks["ida_high_score_destroy_root_owners"]
    update = checks["ida_high_score_update_void_owner"]
    exit_screen = checks["ida_high_score_exit_root_owners"]

    assert (
        "kill_all_borders(&g_game_base->border_manager)"
        in bn_destroy["required_substrings"]
    )
    assert "g_game_base[" in bn_destroy["forbidden_substrings"]
    assert (
        "g_game_base->subgame.selected_level_record_cursor"
        in bn_update["required_substrings"]
    )
    assert "game_base_3 + 0x" in bn_update["forbidden_substrings"]
    assert (
        "g_game_base->subgame.subgame_rebuild_selector"
        in bn_exit_screen["required_substrings"]
    )
    assert "char* game_base_1" in bn_exit_screen["forbidden_substrings"]
    assert (
        "g_runtime_config.high_score_selected_bank = high_score->selected_bank"
        in destroy["required_substrings"]
    )
    assert (
        "g_game_base->subgame.sub_high_score.active_record_bank"
        in update["required_substrings"]
    )
    assert "g_parcel_set_buckets" in update["forbidden_substrings"]
    assert (
        "g_game_base->subgame.subgame_rebuild_selector"
        in exit_screen["required_substrings"]
    )
    assert "_DWORD *v1" in exit_screen["forbidden_substrings"]


def test_bind_subgame_owner_reanalysis_is_paired() -> None:
    repo_root = Path(__file__).parents[1]
    binja_source = (BINJA_DIR / "sync_overlay_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )

    assert "OVERLAY_REANALYSIS_FUNCTIONS" in binja_source
    assert '"bind_subgame_owner",' in binja_source.split(
        "OVERLAY_REANALYSIS_FUNCTIONS", 1
    )[1]
    assert "reanalyze_functions" in binja_source
    assert "identifiers=OVERLAY_REANALYSIS_FUNCTIONS" in binja_source
    assert "0x433FC0,  # bind_subgame_owner" in ida_source

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    bn_check = checks["bn_bind_subgame_owner_root_borrow"]
    ida_check = checks["ida_bind_subgame_owner_root_borrow"]
    assert (
        "struct SubgameRuntime* result = &g_game_base->subgame"
        in bn_check["required_substrings"]
    )
    assert "g_game_base + 0x74618" in bn_check["forbidden_substrings"]
    assert (
        "owner->game = &g_game_base->subgame;"
        in ida_check["required_substrings"]
    )
    assert "476696" in ida_check["forbidden_substrings"]


def test_time_trial_high_score_replays_preserve_route_record_cursor_owner() -> None:
    binja_source = (BINJA_DIR / "sync_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )
    headers = tuple(
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in (
            "bn_high_score_bank_types.h",
            "ida_high_score_bank_types.h",
        )
    )

    for header in headers:
        assert "typedef struct SubHighScoreTimeTrialRouteCursor" in header
        assert "uint8_t bank_prefix[0x2b8c88];" in header
        assert "SubSolution record;" in header
        assert "} SubHighScoreTimeTrialRouteCursor;" in header

    assert "PERSISTENCE_USER_VAR_UPDATES" in binja_source
    assert '"RegisterVariableSourceType",\n        81,\n        71,' in binja_source
    assert '"time_trial_route_cursor"' in binja_source
    assert '"SubHighScoreTimeTrialRouteCursor*"' in binja_source

    assert "_sync_add_time_trial_route_cursor_lvar" in ida_source
    assert "definition_address=0x417902" in ida_source
    assert 'target_name="time_trial_route_cursor"' in ida_source
    assert 'target_struct_name="SubHighScoreTimeTrialRouteCursor"' in ida_source


def test_mini_delete_high_score_replays_preserve_active_bank_cursors() -> None:
    binja_source = (BINJA_DIR / "sync_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )

    for index, storage, name, type_name in (
        (34, 66, "record_offset_bytes", "int32_t"),
        (37, 69, "source_cursor", "SubSolution*"),
        (1, 71, "row", "int32_t"),
        (51, 73, "destination", "SubSolution*"),
        (53, 72, "source", "SubSolution*"),
    ):
        update = (
            '"mini_delete_high_score_entry",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}",'
        )
        assert update in binja_source

    for expected in (
        "definition_address=0x417B16",
        'target_name="source_cursor"',
        "definition_address=0x417B24",
        'target_name="destination"',
        "definition_address=0x417B26",
        'target_name="source"',
        'target_struct_name="SubSolution"',
        '"mini_delete_cursor_lvars": mini_delete_cursor_lvars',
    ):
        assert expected in ida_source


def test_compact_high_score_replays_preserve_persistence_owners() -> None:
    binja_bank_source = (BINJA_DIR / "sync_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )
    ida_bank_source = (IDA_DIR / "apply_high_score_bank_types.py").read_text(
        encoding="utf-8"
    )
    binja_path_source = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_source = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    headers = tuple(
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in (
            "bn_high_score_bank_types.h",
            "ida_high_score_bank_types.h",
            "path_template_types.h",
        )
    )
    replay_headers = tuple(
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in (
            "bn_high_score_bank_types.h",
            "ida_high_score_bank_types.h",
            "frontend_replay_types.h",
            "bn_subgame_runtime_types.h",
            "ida_subgame_runtime_types.h",
            "path_template_types.h",
        )
    )

    binja_declarations = (
        "uint8_t __thiscall deserialize_compact_high_score_record(SubSolution* record, CompactHighScoreRecord* compact)",
        "int32_t __thiscall serialize_compact_high_score_record(SubSolution* record, CompactHighScoreRecord* compact)",
    )
    ida_declarations = (
        "unsigned char __thiscall deserialize_compact_high_score_record(SubSolution* record, CompactHighScoreRecord* compact);",
        "int __thiscall serialize_compact_high_score_record(SubSolution* record, CompactHighScoreRecord* compact);",
    )
    for declaration in binja_declarations:
        assert declaration in binja_bank_source
        assert declaration in binja_path_source
    for declaration in ida_declarations:
        assert f'"{declaration}"' in ida_bank_source
        assert f'"{declaration}"' in ida_path_source
    assert (
        'normalized.replace("unsigned __int8", "unsigned char")'
        in ida_path_source
    )
    for marker in (
        're.sub(r"\\buint8_t\\b", "unsigned char", normalized)',
        're.sub(r"\\bint32_t\\b", "int", normalized)',
        '"type_changes": type_changes',
    ):
        assert marker in ida_path_source

    for local_name in (
        "source_lateral",
        "lateral_run",
        "source_delta_z",
        "delta_z_destination",
        "flag_index",
        "flag_destination",
        "out_lateral",
        "out_delta_z",
        "delta_z_source",
        "out_flags",
        "flag_source",
    ):
        assert f'"{local_name}"' in binja_bank_source

    for local_name in ("flag_destination", "flag_source"):
        local_update = binja_bank_source.split(f'"{local_name}",', 1)[1]
        assert '"uint16_t*"' in local_update.split("),", 1)[0]

    assert (
        '"load_high_scores_from_file",\n'
        '        "RegisterVariableSourceType",\n'
        "        39,\n"
        "        72,\n"
        '        "compact",\n'
        '        "CompactHighScoreRecord*",'
    ) in binja_bank_source

    assert "_sync_load_compact_cursor_lvar" in ida_bank_source
    assert "definition_address=0x417608" in ida_bank_source
    assert 'accepted_names={"file_bytes", "compact"}' in ida_bank_source
    assert '.removeprefix("struct ")' in ida_bank_source
    assert 'target_name="compact"' in ida_bank_source
    assert 'target_struct_name="CompactHighScoreRecord"' in ida_bank_source

    for header in replay_headers:
        replay_record = header.split("typedef struct ReplayRunRecord {", 1)[1].split(
            "} ReplayRunRecord;", 1
        )[0]
        assert "uint16_t flags;" in replay_record
        assert "reserved_05" not in replay_record

    for header in headers:
        compact_header = "".join(header.split())
        assert "typedefstructCompactHighScoreRecord" in compact_header
        assert "int32_tbyte_count;" in compact_header
        assert "int32_tchecksum;" in compact_header
        assert "int32_treplay_sample_count;" in compact_header
        assert "uint8_treplay_payload[1];" in compact_header
        assert "typedefunionSubSolutionScalar" in compact_header
        assert "int32_tbits;" in compact_header
        assert "floatvalue;" in compact_header
        assert "SubSolutionScalargarbage_frequency;" in compact_header
        assert "SubSolutionScalarsalt_frequency;" in compact_header
        assert "0x88+replay_sample_count*5" in compact_header
        assert "HighScoreRecord*record" not in compact_header

    assert "REPLAY_RUN_RECORD_FIELD_UPDATES = (" in binja_path_source
    assert '("0x04", "flags", "uint16_t")' in binja_path_source
    assert (
        '("ReplayRunRecord", REPLAY_RUN_RECORD_FIELD_UPDATES)'
        in binja_path_source
    )


def test_archive_shell_replays_preserve_persistence_helper_abis() -> None:
    binja_source = (BINJA_DIR / "sync_archive_shell_types.py").read_text(
        encoding="utf-8"
    )
    ida_apply_source = (IDA_DIR / "apply_archive_shell_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync_source = (IDA_DIR / "sync_archive_shell_types.py").read_text(
        encoding="utf-8"
    )
    ida_lvar_inspector = (
        IDA_DIR / "inspect_function_lvar_uses.py"
    ).read_text(encoding="utf-8")
    headers = tuple(
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bn_archive_shell_types.h", "archive_shell_types.h")
    )

    binja_declarations = (
        "int32_t __cdecl fseek(File* stream, int32_t offset, int32_t origin)",
        "int32_t __cdecl ftell(File* stream)",
        "char* __cdecl xor_decode_buffer_with_index(char* bytes, int32_t byte_count)",
        "int32_t __cdecl write_file_bytes(char* path, void* bytes, int32_t byte_count)",
        "char* __cdecl save_config_file(char* path, void* bytes, int32_t byte_count)",
    )
    ida_declarations = (
        "unsigned int __cdecl fread(void* bytes, unsigned int element_size, unsigned int element_count, File* stream);",
        "int __cdecl fseek(File* stream, int offset, int origin);",
        "int __cdecl ftell(File* stream);",
        "char* __cdecl xor_decode_buffer_with_index(char* bytes, int byte_count);",
        "int __cdecl write_file_bytes(char* path, void* bytes, int byte_count);",
        "char* __cdecl save_config_file(char* path, void* bytes, int byte_count);",
    )
    for declaration in binja_declarations:
        assert declaration in binja_source
        assert any(f"{declaration};" in header for header in headers)
    for declaration in ida_declarations:
        assert f'"{declaration}"' in ida_apply_source
    assert (
        "uint32_t __cdecl fread(void* bytes, uint32_t element_size, uint32_t element_count, File* stream)"
        in binja_source
    )
    for header in headers:
        compact_header = "".join(header.split())
        assert (
            "uint32_t__cdeclfread(void*bytes,uint32_telement_size,"
            "uint32_telement_count,File*stream);"
        ) in compact_header

    for lvar_declaration in (
        '"char cwd_buffer[512];"',
        '"File* stream;"',
        '"char file_name[256];"',
        '"char original_directory[512];"',
    ):
        assert lvar_declaration in ida_apply_source
    assert "ARCHIVE_SHELL_LVAR_SPECS" in ida_apply_source
    assert "STALE_STACK_LVAR_OVERRIDE_SPECS" in ida_apply_source
    assert "_sync_lvar" in ida_apply_source
    assert "_clear_stale_stack_lvar_override" in ida_apply_source
    assert "restore_user_lvar_settings" in ida_apply_source
    assert "save_user_lvar_settings" in ida_apply_source

    assert "TRUSTED_SCALAR_DATA_ITEMS" in ida_apply_source
    assert "_ensure_scalar_data_item" in ida_apply_source
    assert "ida_bytes.create_dword(address, size, True)" in ida_apply_source
    assert '"reason": "unexpected_scalar_data_item"' in ida_apply_source
    assert '"phase": "data_item_guard"' in ida_apply_source
    for scalar_item in (
        "(0x5108B0, 4)",
        "(0x5108B4, 4)",
        "(0x5108B8, 4)",
    ):
        assert scalar_item in ida_apply_source

    for declaration in (
        "typedef struct FileSearchData",
        "char name[260];",
        "typedef struct TrackedAllocationRecord",
        "TrackedAllocationRecord records[1];",
        "typedef struct SerializedArchiveEntry",
        "int32_t path_offset;",
        "typedef struct SerializedArchiveIndex",
        "typedef struct SerializedArchiveHeader",
        "SerializedArchiveEntry entries[10];",
        "typedef struct Win32Rect",
        "int32_t bottom;",
        "typedef struct TgaImageView",
        "uint8_t pixels[1];",
        "typedef enum ArchiveEntryExtensionClass",
        "ARCHIVE_ENTRY_EXTENSION_MP3 = 3",
        "extern int32_t g_enumerated_entry_count;",
        "extern int32_t g_tracked_allocation_total_bytes;",
        "extern TrackedAllocationStack g_tracked_allocation_stack;",
    ):
        assert all(declaration in header for header in headers)
    for declaration in (
        "int32_t __cdecl findfirst(char* pattern, FileSearchData* find_data)",
        "int32_t __thiscall get_tracked_allocation_size(TrackedAllocationStack* stack, void* pointer)",
        "void __thiscall push_tracked_allocation(TrackedAllocationStack* stack, char* label, void* pointer, int32_t guarded_size)",
        "void __cdecl free_tracked_allocations_to_mark()",
        "void __cdecl set_tracked_allocation_mark()",
    ):
        assert declaration in binja_source
    assert "STALE_DATA_ITEM_SPECS" in ida_apply_source
    assert '"int[4]"' in ida_apply_source
    assert "(0x503320, 4)" in ida_apply_source
    assert "STALE_ARCHIVE_CURSOR_USER_VAR_REMOVALS" in binja_source
    assert "remove_user_var_updates" in binja_source
    assert "ARCHIVE_INDEX_SPLIT_DEFINITIONS" in binja_source
    assert "ARCHIVE_INDEX_SPLIT_TARGET_VAR" in binja_source
    assert "apply_split_user_var_update" in binja_source
    assert "ARCHIVE_CURSOR_USER_VAR_UPDATES" in binja_source
    assert "ARCHIVE_SERVICE_USER_VAR_UPDATES" in binja_source
    assert "ARCHIVE_REBUILD_USER_VAR_UPDATES" in binja_source
    assert "ARCHIVE_SERVICE_INT_DISPLAY_UPDATES" in binja_source
    assert 'allocate_tracked_memory(0x400000, "Scratch Pad")' in binja_source
    assert '("0x42f0a0", "load_png_image")' in binja_source
    assert '("0x48b614", "printf")' in binja_source
    assert '("0x48b8d5", "free")' in binja_source
    assert "ArchiveEntryExtensionClass __cdecl classify_archive_entry_extension" in binja_source
    assert "void __cdecl rebuild_game_archive_if_needed()" in binja_source
    assert "int32_t __cdecl load_png_image(char* png_path" in binja_source
    assert "void* __cdecl load_file_bytes_allocating(char* path" in binja_source
    assert "int32_t __cdecl save_file_bytes_with_optional_archive_scramble" in binja_source
    assert "char* __cdecl toggle_archive_high_bit_in_place" in binja_source
    assert "int32_t __cdecl printf(char* format, ...)" in binja_source
    assert "void __cdecl free(void* pointer)" in binja_source
    assert '(0x42F0A0, "load_png_image")' in ida_apply_source
    assert '(0x48B614, "printf")' in ida_apply_source
    assert '(0x48B8D5, "free")' in ida_apply_source
    assert "ArchiveEntryExtensionClass __cdecl classify_archive_entry_extension" in ida_apply_source
    assert "void __cdecl rebuild_game_archive_if_needed(void);" in ida_apply_source
    assert "int __cdecl load_png_image(char* png_path" in ida_apply_source
    assert "void* __cdecl load_file_bytes_allocating(char* path" in ida_apply_source
    assert "int __cdecl save_file_bytes_with_optional_archive_scramble" in ida_apply_source
    assert "char* __cdecl toggle_archive_high_bit_in_place" in ida_apply_source
    assert "int __cdecl printf(char* format, ...);" in ida_apply_source
    assert "void __cdecl free(void* pointer);" in ida_apply_source
    assert "strings_equal_case_insensitive" not in ida_apply_source
    assert "find_case_insensitive_substring" not in ida_apply_source
    assert "strings_equal_case_insensitive" not in binja_source
    assert "find_case_insensitive_substring" not in binja_source
    assert "apply_user_var_updates" in binja_source
    for owner_name in (
        '"serialized_header"',
        '"serialized_index"',
        '"index_byte_count"',
        '"slot_axis_y_cursor"',
        '"archive_index"',
        '"archive_entry_cursor"',
        '"archive_path_cursor"',
        '"requested_path_cursor"',
        '"basename_cursor"',
        '"archive_entry_offset"',
        '"filesystem_file"',
        '"filesystem_stream"',
        '"filesystem_output_buffer"',
        '"rebuilt_index"',
        '"source_index"',
        '"source_byte_count_cursor"',
        '"rebuilt_data_offset_cursor"',
        '"png_pixels"',
        '"entry_path"',
        '"entry_stem"',
    ):
        assert owner_name in binja_source or owner_name in ida_apply_source

    assert 'IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/apply_archive_shell_types.py"' in ida_sync_source
    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/archive_shell_types.h"' in ida_sync_source
    assert 'SYNC_FAILURE_SENTINEL = "ARCHIVE_SHELL_SYNC_FAILED"' in ida_apply_source
    assert 'SYNC_FAILURE_SENTINEL = "ARCHIVE_SHELL_SYNC_FAILED"' in ida_sync_source
    assert "if SYNC_FAILURE_SENTINEL in log_text:" in ida_sync_source
    assert "return exit_code or 1" in ida_sync_source
    for locator_field in (
        '"index": index',
        '"definition_address": _format_address(lvar.defea)',
        '"is_argument": lvar.is_arg_var',
        '"is_stack": lvar.is_stk_var()',
        '"stack_offset": lvar.get_stkoff() if lvar.is_stk_var() else None',
        '"locals": lvars',
    ):
        assert locator_field in ida_lvar_inspector


def test_archive_shell_replays_preserve_registered_sound_ownership() -> None:
    binja_source = (BINJA_DIR / "sync_archive_shell_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_archive_shell_types.py").read_text(
        encoding="utf-8"
    )
    binja_header = (HEADER_DIR / "bn_archive_shell_types.h").read_text(
        encoding="utf-8"
    )
    ida_header = (HEADER_DIR / "archive_shell_types.h").read_text(encoding="utf-8")
    headers = (binja_header, ida_header)
    binja_path_source = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_source = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )

    for declaration in (
        "typedef enum RegisteredSoundLimits {",
        "typedef char RegisteredSoundSampleName[RSHELL_SOUND_NAME_BYTES];",
        "typedef char CachedMusicPath[256];",
        "typedef int32_t (__stdcall* BassStreamPlayFn)(",
        "typedef BassHandle (__stdcall* BassSamplePlayExFn)(",
        "typedef BassHandle (__stdcall* BassSampleLoadFn)(",
        "typedef int32_t (__stdcall* BassFreeFn)(void);",
        "void __cdecl reset_registered_sound_sample_count(void);",
        "char __cdecl cache_music_file(",
        "int32_t __cdecl play_registered_warning_sample(int32_t sample_id);",
        "int32_t __cdecl stop_registered_warning_sample(int32_t sample_handle);",
        "void __cdecl play_sound_effect_backend(",
        "void __cdecl play_voice_backend(",
        "int32_t __cdecl register_sound_sample(char* path, int32_t normalization_class);",
        "int32_t __cdecl find_registered_sound_sample_id_by_name(char* sample_name);",
        "extern RegisteredSoundSampleName g_registered_sound_sample_names[RSHELL_SOUND_MAX];",
        "extern int32_t g_registered_sound_sample_count;",
        "extern int32_t g_registered_sound_sample_handles[RSHELL_SOUND_MAX];",
        "extern CachedMusicPath g_cached_music_path;",
        "extern BassStreamPlayFn g_bass_stream_play;",
        "extern BassSamplePlayExFn g_bass_sample_play_ex;",
        "extern BassSampleLoadFn g_bass_sample_load;",
        "extern BassFreeFn g_bass_free;",
    ):
        assert all(declaration in header for header in headers)

    for scalar_alias in (
        "extern float g_stream_volume_scale;",
        "extern float g_audio_backend_sfx_normalization_scale;",
        "extern float g_audio_backend_voice_normalization_scale;",
    ):
        assert all(scalar_alias not in header for header in headers)

    assert '("0x5088b0", "RegisteredSoundSampleName[256]")' in binja_source
    assert '("0x7516a0", "CachedMusicPath")' in binja_source
    assert '("0x7517a0", "BassStreamPlayFn")' in binja_source
    assert '("0x7527b4", "BassSamplePlayExFn")' in binja_source
    assert '("0x7537cc", "BassSampleLoadFn")' in binja_source
    assert '("0x7537d8", "BassFreeFn")' in binja_source
    assert '("0x7537e0", "int32_t[256]")' in binja_source
    assert '"char __cdecl cache_music_file(char* path, int32_t unused, char* unused_default_path)"' in binja_source
    assert '"int32_t __cdecl play_registered_warning_sample(int32_t sample_id)"' in binja_source
    assert '"int32_t __cdecl stop_registered_warning_sample(int32_t sample_handle)"' in binja_source
    assert '"void __cdecl play_sound_effect_backend(int32_t sample_id, float gain, float pitch, float pan)"' in binja_source
    assert '"void __cdecl play_voice_backend(int32_t sample_id, float gain, float pitch, float pan)"' in binja_source
    assert '"int32_t __cdecl register_sound_sample(char* path, int32_t normalization_class)"' in binja_source
    assert '"int32_t __cdecl find_registered_sound_sample_id_by_name(char* sample_name)"' in binja_source

    assert "TRUSTED_EXTENT_DATA_ITEMS" in ida_source
    assert "0x5088B0" in ida_source
    assert "0x8000" in ida_source
    assert '"char[32768]"' in ida_source
    assert "_ensure_extent_data_item" in ida_source
    assert "ida_bytes.create_byte(address, size, True)" in ida_source
    assert '"reason": "unexpected_extent_data_item"' in ida_source
    assert '"reason": "unexpected_stale_extent_data_item"' in ida_source
    assert 're.sub(r"\\s*\\[\\s*", "[", normalized)' in ida_source
    assert '"RegisteredSoundSampleName g_registered_sound_sample_names[256];"' in ida_source
    assert '"char g_cached_music_path[256];"' in ida_source
    assert '"BassStreamPlayFn g_bass_stream_play;"' in ida_source
    assert '"BassSamplePlayExFn g_bass_sample_play_ex;"' in ida_source
    assert '"BassSampleLoadFn g_bass_sample_load;"' in ida_source
    assert '"BassFreeFn g_bass_free;"' in ida_source
    assert '"int g_registered_sound_sample_handles[256];"' in ida_source
    assert '"char __cdecl cache_music_file(char* path, int unused, char* unused_default_path);"' in ida_source
    assert '"int __cdecl play_registered_warning_sample(int sample_id);"' in ida_source
    assert '"int __cdecl stop_registered_warning_sample(int sample_handle);"' in ida_source
    assert '"void __cdecl play_sound_effect_backend(int sample_id, float gain, float pitch, float pan);"' in ida_source
    assert '"void __cdecl play_voice_backend(int sample_id, float gain, float pitch, float pan);"' in ida_source
    assert '"int __cdecl register_sound_sample(char* path, int normalization_class);"' in ida_source
    assert '"int __cdecl find_registered_sound_sample_id_by_name(char* sample_name);"' in ida_source
    assert "0x7537E0" in ida_source
    assert "0x400" in ida_source
    assert '"int[257]"' in ida_source
    assert "0x7516A0" in ida_source
    assert "0x2140" in ida_source
    assert "0x100" in ida_source
    assert '"char[8512]"' in ida_source
    assert "REGISTERED_SOUND_SPLIT_LVAR_SPECS" in ida_source
    assert '"sample_size"' in ida_source
    assert "0x432F2B" in ida_source
    assert "_sync_split_lvar" in ida_source
    assert "info.set_split_lvar()" in ida_source
    assert "ida_hexrays.MLI_SET_FLAGS" in ida_source

    assert '(0x753C58, "g_audio_backend", "AudioBackend g_audio_backend;")' in ida_source
    assert "0x1C" in ida_source
    for stale_interior in ("0x753C64", "0x753C68", "0x753C6C"):
        assert stale_interior not in ida_source

    assert '("0x753c58", "AudioBackend")' in binja_source
    assert "LEGACY_AUDIO_BACKEND_DATA_VAR_REMOVALS" in binja_source
    assert "LEGACY_AUDIO_BACKEND_DATA_VAR_REPLACEMENTS" in binja_source
    assert "LEGACY_AUDIO_BACKEND_SYMBOL_REMOVALS" in binja_source
    assert "apply_data_var_removals" in binja_source
    assert "apply_symbol_removals" in binja_source

    assert "cache_music_file" not in binja_path_source
    assert "cache_music_file" not in ida_path_source
    assert "cache_music_file" not in path_header


def test_archive_shell_replays_preserve_exact_bass_dispatch_table() -> None:
    binja_source = (BINJA_DIR / "sync_archive_shell_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_archive_shell_types.py").read_text(
        encoding="utf-8"
    )
    headers = tuple(
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bn_archive_shell_types.h", "archive_shell_types.h")
    )
    import_headers = tuple(
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bass_min.h", "snail_bn_import.h")
    )

    for declaration in (
        "DWORD WINAPI BASS_SetConfig(DWORD option, DWORD value);",
        "BOOL WINAPI BASS_Update(void);",
        "void WINAPI BASS_StreamFree(HSTREAM stream);",
        "HCHANNEL WINAPI BASS_SamplePlayEx(HSAMPLE sample, DWORD start, INT freq, INT volume, INT pan, BOOL loop);",
        "float WINAPI BASS_ChannelBytes2Seconds(DWORD channel, QWORD position);",
        "HSYNC WINAPI BASS_ChannelSetSync(DWORD channel, DWORD sync_type, QWORD parameter, SYNCPROC *proc, DWORD user);",
        "QWORD WINAPI BASS_ChannelGetPosition(DWORD channel);",
    ):
        assert all(declaration in header for header in import_headers)

    dispatch = (
        ("0x75162c", "g_bass_channel_bytes2_seconds", "BassChannelBytes2SecondsFn"),
        ("0x75165c", "g_bass_channel_remove_sync", "BassChannelRemoveSyncFn"),
        ("0x751660", "g_bass_start", "BassStartFn"),
        ("0x751670", "g_bass_stream_prebuf", "BassStreamPreBufFn"),
        ("0x751674", "g_bass_error_get_code", "BassErrorGetCodeFn"),
        ("0x751698", "g_bass_update", "BassUpdateFn"),
        ("0x7517a0", "g_bass_stream_play", "BassStreamPlayFn"),
        ("0x7527b4", "g_bass_sample_play_ex", "BassSamplePlayExFn"),
        ("0x7537cc", "g_bass_sample_load", "BassSampleLoadFn"),
        ("0x7537d8", "g_bass_free", "BassFreeFn"),
        ("0x753be4", "g_bass_channel_stop", "BassChannelStopFn"),
        ("0x753bf8", "g_bass_stream_create_file", "BassStreamCreateFileFn"),
        ("0x753bfc", "g_bass_stop", "BassStopFn"),
        ("0x753c08", "g_bass_init", "BassInitFn"),
        ("0x753c18", "g_bass_channel_get_data", "BassChannelGetDataFn"),
        ("0x753c1c", "g_bass_set_config", "BassSetConfigFn"),
        ("0x753c94", "g_bass_sample_stop", "BassSampleStopFn"),
        ("0x753c98", "g_bass_channel_get_position", "BassChannelGetPositionFn"),
        ("0x753ca8", "g_bass_channel_is_active", "BassChannelIsActiveFn"),
        ("0x753cb0", "g_bass_stream_free", "BassStreamFreeFn"),
        ("0x753cbc", "g_bass_channel_get_level", "BassChannelGetLevelFn"),
        ("0x753cc0", "g_bass_pause", "BassPauseFn"),
        ("0x753cc4", "g_bass_channel_set_sync", "BassChannelSetSyncFn"),
    )
    for address, name, type_name in dispatch:
        assert f'("{address}", "{name}")' in binja_source
        assert f'("{address}", "{type_name}")' in binja_source
        assert all(f"extern {type_name} {name};" in header for header in headers)
        ida_address = address.upper().replace("0X", "0x")
        assert f'({ida_address}, "{name}"' in ida_source
        assert f'"{type_name} {name};"' in ida_source

    for declaration in (
        "typedef float (__stdcall* BassChannelBytes2SecondsFn)(",
        "BassHandle channel_handle, BassQword position);",
        "typedef void (__stdcall* BassStreamFreeFn)(BassHandle stream_handle);",
        "typedef int32_t (__stdcall* BassStreamPlayFn)(",
        "typedef BassQword (__stdcall* BassChannelGetPositionFn)(",
        "typedef BassHandle (__stdcall* BassChannelSetSyncFn)(",
        "BassQword parameter,",
        "BassSyncProc callback,",
    ):
        assert all(declaration in header for header in headers)

    for address, name, type_name in (
        ("0x751680", "g_active_music_stream_sync", "BassHandle"),
        ("0x753c20", "g_active_music_stream", "BassHandle"),
        ("0x753c90", "g_bass_module", "void*"),
    ):
        assert f'("{address}", "{name}")' in binja_source
        assert f'("{address}", "{type_name}")' in binja_source
        assert all(f"extern {type_name} {name};" in header for header in headers)

    for address, name, type_name in (
        ("0x49701c", "GetProcAddress", "Win32GetProcAddressFn"),
        ("0x497020", "LoadLibraryA", "Win32LoadLibraryAFn"),
        ("0x497024", "FreeLibrary", "Win32FreeLibraryFn"),
    ):
        assert f'("{address}", "{type_name}")' in binja_source
        assert all(f"extern {type_name} {name};" in header for header in headers)
        ida_address = address.upper().replace("0X", "0x")
        assert f'({ida_address}, "{name}", "{type_name} {name};")' in ida_source


def test_audio_system_header_owns_registered_audio_globals() -> None:
    audio_header = (
        Path(__file__).parents[1] / "tools/match/include/audio_system.h"
    ).read_text(encoding="utf-8")
    assert "extern char g_cached_music_path[0x100];" in audio_header
    assert "extern int g_registered_sound_sample_handles[RSHELL_SOUND_MAX];" in audio_header
    assert "extern float g_stream_volume_scale;" in audio_header
    assert "extern float g_audio_backend_sfx_normalization_scale;" in audio_header
    assert "extern float g_audio_backend_voice_normalization_scale;" in audio_header
    assert "typedef void (__stdcall* BassStreamFreeFn)(BassHandle stream_handle);" in audio_header
    assert "extern BassStreamPlayFn g_bass_stream_play;" in audio_header
    assert "extern BassChannelIsActiveFn g_bass_channel_is_active;" in audio_header
    assert "extern void* g_bass_module;" in audio_header

    scratch_names = (
        "load_registered_sound_sample_from_path",
        "load_registered_sound_sample_from_bytes",
        "play_registered_sound_sample_scaled",
        "stop_registered_sound_sample",
        "is_registered_sound_sample_playing",
        "play_registered_sound_sample_default",
        "play_registered_sound_sample_backend",
        "play_registered_sound_sample_scaled_panned",
    )
    scratch_root = Path(__file__).parents[1] / "tools/match/scratches"
    for scratch_name in scratch_names:
        source = (scratch_root / scratch_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert "#include \"audio_system.h\"" in source
        assert "extern int g_registered_sound_sample_handles[];" not in source

    for scratch_name in (
        "initialize_bass_audio_backend",
        "prepare_music_stream_reload_if_path_changed",
        "ensure_music_stream_from_path",
        "play_music_stream_from_bytes",
    ):
        source = (scratch_root / scratch_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert "#include \"audio_system.h\"" in source
        assert "extern char g_cached_music_path[];" not in source

    for scratch_name, stale_declaration in (
        (
            "apply_audio_config_volumes",
            "extern float g_stream_volume_scale;",
        ),
        (
            "play_sound_effect_backend",
            "extern float g_audio_backend_sfx_normalization_scale;",
        ),
        (
            "play_voice_backend",
            "extern float g_audio_backend_voice_normalization_scale;",
        ),
    ):
        source = (scratch_root / scratch_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert "#include \"audio_system.h\"" in source
        assert stale_declaration not in source

    for scratch_name in (
        "initialize_bass_audio_backend",
        "ensure_music_stream_from_path",
        "play_music_stream_from_bytes",
        "load_registered_sound_sample_from_path",
        "load_registered_sound_sample_from_bytes",
        "play_registered_sound_sample_scaled",
        "play_registered_sound_sample_default",
        "play_registered_sound_sample_backend",
        "play_registered_sound_sample_scaled_panned",
        "stop_sound_sample_handle",
        "stop_registered_sound_sample",
        "is_registered_sound_sample_playing",
        "stop_music_stream",
        "set_global_sample_volume_config",
        "set_global_stream_volume_config",
        "stop_audio_backend",
        "resume_audio_backend_if_paused",
        "pause_audio_backend_if_running",
        "uninitialize_bass_audio_backend",
    ):
        source = (scratch_root / scratch_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert "typedef " not in source
        assert "extern Bass" not in source


def test_ios_bass_symbols_recover_windows_audio_owner_without_fakematching() -> None:
    repo_root = Path(__file__).parents[1]
    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    references = json.loads(
        (repo_root / "analysis/symbols/gameplay-references.json").read_text(
            encoding="utf-8"
        )
    )
    functions_by_address = {
        entry["address"]: entry for entry in functions["functions"]
    }
    crosswalk_by_address = {
        entry["address"]: entry for entry in crosswalk["entries"]
    }

    for address, alias, symbol in (
        (
            "0x4499a0",
            "cRBass_PlaySample",
            "cRBass::PlaySample(int, float)",
        ),
        (
            "0x449a10",
            "cRBass_StopSampleLooped",
            "cRBass::StopSampleLooped(int)",
        ),
        ("0x449a20", "cRBass_StopSample", "cRBass::StopSample(int)"),
        (
            "0x449a40",
            "cRBass_SamplePlaying",
            "cRBass::SamplePlaying(int)",
        ),
        (
            "0x449a60",
            "cRBass_PlaySampleLooped",
            "cRBass::PlaySampleLooped(int)",
        ),
    ):
        assert alias in functions_by_address[address]["aliases"]
        entry = crosswalk_by_address[address]
        assert entry["ios_symbol"] == symbol
        assert "android_symbol" not in entry
        assert entry["source_object"] == "BassPlay.o"
        assert entry["confidence"] == "high"

    assert "raw-handle method" in crosswalk_by_address["0x449a10"]["notes"]
    assert "sample-ID call edge" in crosswalk_by_address["0x449a20"]["notes"]
    assert "disabled `mov r0, 0; bx lr`" in (
        crosswalk_by_address["0x449a60"]["notes"]
    )

    # iOS exposes no corresponding cRBass pitch/pan overloads. Keep those
    # renderer-specific Windows helpers out of the verified mobile crosswalk.
    assert "0x449a80" not in crosswalk_by_address
    assert "0x449ae0" not in crosswalk_by_address

    noop = crosswalk_by_address["0x407b50"]
    assert "cRBass::AI()" in noop["notes"]
    assert "cRBass_AI" in functions_by_address["0x407b50"]["aliases"]

    bass_global = next(
        entry
        for entry in references["symbols"]
        if entry["address"] == "0x753c58"
    )
    assert bass_global["name"] == "g_audio_backend"
    assert "gBass" in bass_global["aliases"]
    assert "Authored cRBass global" in bass_global["description"]

    for header_path in (
        repo_root / "tools/match/include/audio_system.h",
        HEADER_DIR / "bn_archive_shell_types.h",
        HEADER_DIR / "archive_shell_types.h",
    ):
        assert "typedef AudioBackend cRBass;" in header_path.read_text(
            encoding="utf-8"
        )


def test_mobile_noop_vtables_recover_distinct_folded_owners() -> None:
    repo_root = Path(__file__).parents[1]
    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    references = json.loads(
        (repo_root / "analysis/symbols/gameplay-references.json").read_text(
            encoding="utf-8"
        )
    )
    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    android = json.loads(
        (repo_root / "analysis/decompile/android/index.json").read_text(
            encoding="utf-8"
        )
    )
    ios = json.loads(
        (repo_root / "analysis/decompile/ios/index.json").read_text(
            encoding="utf-8"
        )
    )

    mobile_symbols = (
        "cRBod::AI()",
        "cRCamera::AI()",
        "cRGolbRocket::AI()",
        "cRSnail::AI()",
    )
    for corpus in (android, ios):
        by_symbol = {entry["demangled"]: entry for entry in corpus["functions"]}
        for symbol in mobile_symbols:
            assert by_symbol[symbol]["size"] == 4

    noop = next(
        entry for entry in functions["functions"] if entry["address"] == "0x407b50"
    )
    for alias in (
        "cRBod_AI",
        "cRCamera_AI",
        "cRGolbRocket_AI",
        "cRSnail_AI",
        "cRWeapon_AI",
    ):
        assert alias in noop["aliases"]

    representative = next(
        entry for entry in crosswalk["entries"] if entry["address"] == "0x407b50"
    )
    assert representative["ios_symbol"] == "cRWeapon::AI()"
    for owner in mobile_symbols:
        assert owner in representative["notes"]
    assert "without collapsing" in representative["notes"]

    references_by_address = {
        entry["address"]: entry for entry in references["symbols"]
    }
    expected_tables = {
        "0x4972b0": "cRCamera::AI()",
        "0x497350": "cRGolbRocket::AI()",
        "0x497354": "cRSnail::AI()",
        "0x4974fc": "cRBod::AI()",
        "0x497500": "cRBod::AI()",
    }
    for address, owner in expected_tables.items():
        assert owner in references_by_address[address]["description"]

    bod_header = (repo_root / "tools/match/include/bod_types.h").read_text(
        encoding="utf-8"
    )
    viewport_header = (repo_root / "tools/match/include/viewport.h").read_text(
        encoding="utf-8"
    )
    golb_header = (repo_root / "tools/match/include/golb.h").read_text(
        encoding="utf-8"
    )
    player_header = (repo_root / "tools/match/include/player.h").read_text(
        encoding="utf-8"
    )
    analysis_header = (
        repo_root / "analysis/headers/path_template_types.h"
    ).read_text(encoding="utf-8")

    assert "typedef BodBase cRBod;" in bod_header
    assert "typedef RenderableBod cRBodPos;" in bod_header
    assert "typedef RenderCamera cRCamera;" in viewport_header
    assert "typedef GolbRocket cRGolbRocket;" in golb_header
    assert "GolbRocket tertiary_body;" in golb_header
    assert "typedef Snail cRSnail;" in player_header
    assert "typedef RenderableBod cRGolbRocket;" in analysis_header
    assert "cRGolbRocket tertiary_body;" in analysis_header


def test_mobile_subgoldy_layout_recovers_folded_constructor_owners() -> None:
    repo_root = Path(__file__).parents[1]
    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    constructor = (
        repo_root
        / "tools/match/scratches/"
        "initialize_runtime_pools_and_path_template_bank/scratch.cpp"
    ).read_text(encoding="utf-8")
    cameraman_header = (
        repo_root / "tools/match/include/cameraman.h"
    ).read_text(encoding="utf-8")
    attachment_header = (
        repo_root / "tools/match/include/track_attachment_types.h"
    ).read_text(encoding="utf-8")
    analysis_header = (
        repo_root / "analysis/headers/path_template_types.h"
    ).read_text(encoding="utf-8")
    android_init = (
        repo_root
        / "analysis/decompile/android/functions/"
        "00079da8-_ZN10cRSubGoldy4InitEi.c"
    ).read_text(encoding="utf-8")
    android_ai = (
        repo_root
        / "analysis/decompile/android/functions/"
        "0007ac54-_ZN10cRSubGoldy2AIEv.c"
    ).read_text(encoding="utf-8")
    ios_ai = (
        repo_root
        / "analysis/decompile/ios/functions/"
        "000277f8-_ZN10cRSubGoldy2AIEv.c"
    ).read_text(encoding="utf-8")

    noop = next(
        entry for entry in functions["functions"] if entry["address"] == "0x408600"
    )
    assert "cRCameraman_ctor" in noop["aliases"]
    assert "cRPathFollowGoldy_ctor" in noop["aliases"]
    assert "subgoldy->cameraman.noop_runtime_slot_constructor();" in constructor
    assert "subgoldy->follow_state.noop_runtime_slot_constructor();" in constructor
    assert "typedef Cameraman cRCameraman;" in cameraman_header
    assert "typedef FollowState cRPathFollowGoldy;" in attachment_header
    assert "typedef Cameraman cRCameraman;" in analysis_header
    assert "typedef FollowState cRPathFollowGoldy;" in analysis_header

    # Port-specific offsets are evidence for the class identities only. The
    # Windows scratch continues to derive its own +0x200/+0x384 layout.
    assert "cRCameraman::Init((cRCameraman *)(this + 0x1e8));" in android_init
    assert "(cRPathFollowGoldy *)(in_r0 + 0x374)" in android_ai
    assert "(cRPathFollowGoldy *)(this + 0x374)" in ios_ai


def test_archive_shell_replays_preserve_audio_backend_member_abi() -> None:
    binja_source = (BINJA_DIR / "sync_archive_shell_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_archive_shell_types.py").read_text(
        encoding="utf-8"
    )
    headers = tuple(
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bn_archive_shell_types.h", "archive_shell_types.h")
    )

    for declaration in (
        "typedef struct AudioBackend {",
        "uint8_t music_stream_active;",
        "int32_t unknown_04;",
        "float unknown_08;",
        "float music_normalization_scale;",
        "float sfx_normalization_scale;",
        "float voice_normalization_scale;",
        "uint8_t is_paused;",
        "extern AudioBackend g_audio_backend;",
        "int32_t __cdecl shutdown_bass_audio_window(void);",
        "char __thiscall initialize_bass_audio_backend(",
        "void __thiscall uninitialize_bass_audio_backend(AudioBackend* backend);",
        "int32_t __thiscall ensure_music_stream_from_path(",
        "char __thiscall prepare_music_stream_reload_if_path_changed(",
        "int32_t __thiscall play_music_stream_from_bytes(",
        "void __thiscall stop_music_stream(AudioBackend* backend);",
        "int32_t __thiscall load_registered_sound_sample_from_path(",
        "void __thiscall load_registered_sound_sample_from_bytes(",
        "void __thiscall play_registered_sound_sample_scaled(",
        "int32_t __thiscall stop_sound_sample_handle(",
        "void __thiscall stop_registered_sound_sample(",
        "bool __thiscall is_registered_sound_sample_playing(",
        "int32_t __thiscall play_registered_sound_sample_default(",
        "void __thiscall play_registered_sound_sample_backend(",
        "void __thiscall play_registered_sound_sample_scaled_panned(",
        "int32_t __thiscall set_global_sample_volume_config(",
        "int32_t __thiscall set_global_stream_volume_config(",
        "int32_t __thiscall stop_audio_backend(AudioBackend* backend);",
        "void __thiscall resume_audio_backend_if_paused(AudioBackend* backend);",
        "char __thiscall pause_audio_backend_if_running(AudioBackend* backend);",
        "void __thiscall set_audio_normalization_scales(",
    ):
        assert all(declaration in header for header in headers)

    for address, name in (
        ("0x407b00", "shutdown_bass_audio_window"),
        ("0x449460", "initialize_bass_audio_backend"),
        ("0x4496d0", "uninitialize_bass_audio_backend"),
        ("0x449720", "ensure_music_stream_from_path"),
        ("0x4497e0", "prepare_music_stream_reload_if_path_changed"),
        ("0x449820", "play_music_stream_from_bytes"),
        ("0x4498d0", "stop_music_stream"),
        ("0x449920", "load_registered_sound_sample_from_path"),
        ("0x449960", "load_registered_sound_sample_from_bytes"),
        ("0x4499a0", "play_registered_sound_sample_scaled"),
        ("0x449a10", "stop_sound_sample_handle"),
        ("0x449a20", "stop_registered_sound_sample"),
        ("0x449a40", "is_registered_sound_sample_playing"),
        ("0x449a60", "play_registered_sound_sample_default"),
        ("0x449a80", "play_registered_sound_sample_backend"),
        ("0x449ae0", "play_registered_sound_sample_scaled_panned"),
        ("0x449b50", "set_global_sample_volume_config"),
        ("0x449b70", "set_global_stream_volume_config"),
        ("0x449b90", "stop_audio_backend"),
        ("0x449ba0", "resume_audio_backend_if_paused"),
        ("0x449bc0", "pause_audio_backend_if_running"),
        ("0x449be0", "set_audio_normalization_scales"),
    ):
        assert f'("{address}", "{name}")' in binja_source
        assert name in ida_source

    for marker in (
        "int32_t __cdecl shutdown_bass_audio_window()",
        "initialize_bass_audio_backend(AudioBackend* backend, void* hwnd)",
        "load_registered_sound_sample_from_path(AudioBackend* backend, char* path",
        "play_registered_sound_sample_scaled(AudioBackend* backend, int32_t sample_id",
        "set_global_sample_volume_config(AudioBackend* backend, float volume)",
        "stop_audio_backend(AudioBackend* backend)",
        "set_audio_normalization_scales(AudioBackend* backend, float music_scale",
    ):
        assert marker in binja_source

    for marker in (
        "int __cdecl shutdown_bass_audio_window(void);",
        "initialize_bass_audio_backend(AudioBackend* backend, void* hwnd);",
        "load_registered_sound_sample_from_path(AudioBackend* backend, char* path",
        "play_registered_sound_sample_scaled(AudioBackend* backend, int sample_id",
        "set_global_sample_volume_config(AudioBackend* backend, float volume);",
        "stop_audio_backend(AudioBackend* backend);",
        "set_audio_normalization_scales(AudioBackend* backend, float music_scale",
    ):
        assert marker in ida_source


def test_frame_replays_preserve_window_bootstrap_abi() -> None:
    binja_source = (BINJA_DIR / "sync_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )

    for address, name in (
        ("0x4119c0", "initialize_game_window_and_input_wrapper"),
        ("0x4119d0", "initialize_game_window_and_input"),
    ):
        assert f'("{address}", "{name}")' in binja_source
        assert name in ida_source

    for marker in (
        "int32_t __cdecl initialize_game_window_and_input_wrapper(char* window_name)",
        "int32_t __cdecl initialize_game_window_and_input(char* window_name)",
    ):
        assert marker in binja_source

    for marker in (
        "int __cdecl initialize_game_window_and_input_wrapper(char *window_name);",
        "int __cdecl initialize_game_window_and_input(char *window_name);",
    ):
        assert marker in ida_source

    symbol_update = binja_source.index("updates=FUNCTION_SYMBOL_UPDATES")
    prototype_update = binja_source.index("proto_updates=resolved_proto_updates")
    assert symbol_update < prototype_update
    assert '("0x44e410", "build_sprite_tail")' in binja_source
    assert 'OBJECT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"' in binja_source
    assert 'SPRITE_HEADER_PATH = REPO_ROOT / "analysis/headers/star_manager_types.h"' in binja_source
    assert '"RenderableBod"' in binja_source
    assert '"Sprite"' in binja_source
    assert '"star_manager_types.h"' in ida_source
    assert '"build_sprite_tail",' in ida_source
    assert 're.sub(r"\\b(?:struct|union|enum)\\s+", "", normalized)' in ida_source


def test_frontend_fade_and_color_overlay_owners_are_replayed_cross_decompiler() -> None:
    repo_root = Path(__file__).parents[1]
    binja_source = (BINJA_DIR / "sync_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    ida_source = (IDA_DIR / "apply_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("bn_frame_renderer_types.h", "frame_renderer_types.h")
    )
    fade_header = (
        repo_root / "tools/match/include/frontend_fade.h"
    ).read_text(encoding="utf-8")
    begin_fade_source = (
        repo_root
        / "tools/match/scratches/begin_frontend_fade_out/scratch.cpp"
    ).read_text(encoding="utf-8")
    delayed_action_source = (
        repo_root
        / "tools/match/scratches/queue_frontend_widget_flag_after_delay/scratch.cpp"
    ).read_text(encoding="utf-8")
    binja_joined_literals = binja_source.replace('"\n        "', "")
    ida_joined_literals = ida_source.replace('"\n        "', "")

    functions = (
        ("0x401030", "0x401030", "border_add_text_number"),
        ("0x404350", "0x404350", "initialize_border_stack"),
        ("0x404360", "0x404360", "apply_all_border_visibility_mode"),
        ("0x40ab00", "0x40AB00", "initialize_frontend_overlay_color_lerp"),
        ("0x40ab40", "0x40AB40", "draw_frontend_overlay_color_lerp"),
        ("0x40abc0", "0x40ABC0", "begin_frontend_fade_out"),
        ("0x40abe0", "0x40ABE0", "begin_frontend_fade_in"),
        ("0x40abf0", "0x40ABF0", "update_frontend_transition_overlay"),
    )
    for binja_address, ida_address, name in functions:
        assert f'("{binja_address}", "{name}")' in binja_source
        assert f'({ida_address}, "{name}")' in ida_source
        assert f'"{name}",' in binja_source
        assert f'"{name}",' in ida_source

    for binja_prototype, ida_prototype in (
        (
            "void __thiscall border_add_text_number("
            "FrontendWidget* border, int32_t value)",
            "void __thiscall border_add_text_number("
            "FrontendWidget *border, int32_t value);",
        ),
        (
            "void __thiscall initialize_border_stack(BorderStack* stack)",
            "void __thiscall initialize_border_stack(BorderStack *stack);",
        ),
        (
            "void __thiscall apply_all_border_visibility_mode("
            "BorderStack* stack, int32_t mode)",
            "void __thiscall apply_all_border_visibility_mode("
            "BorderStack *stack, int32_t mode);",
        ),
        (
            "void __thiscall initialize_frontend_overlay_color_lerp("
            "FrontendOverlayColorLerp* overlay, int32_t state)",
            "void __thiscall initialize_frontend_overlay_color_lerp("
            "FrontendOverlayColorLerp *overlay, int32_t state);",
        ),
        (
            "void __thiscall draw_frontend_overlay_color_lerp("
            "FrontendOverlayColorLerp* overlay)",
            "void __thiscall draw_frontend_overlay_color_lerp("
            "FrontendOverlayColorLerp *overlay);",
        ),
        (
            "void __thiscall begin_frontend_fade_out("
            "FrontendFade* fade, FrontendFadeCallback completion_callback)",
            "void __thiscall begin_frontend_fade_out("
            "FrontendFade *fade, FrontendFadeCallback completion_callback);",
        ),
        (
            "void __thiscall begin_frontend_fade_in(FrontendFade* fade)",
            "void __thiscall begin_frontend_fade_in(FrontendFade *fade);",
        ),
        (
            "void __thiscall update_frontend_transition_overlay(FrontendFade* fade)",
            "void __thiscall update_frontend_transition_overlay(FrontendFade *fade);",
        ),
    ):
        assert binja_prototype in binja_joined_literals
        assert ida_prototype in ida_joined_literals

    assert '"FrontendOverlayColorLerp": 0x24' in ida_source
    assert '"FrontendFadeCallback"' in binja_source
    assert '("FrontendFade", FRONTEND_FADE_FIELD_UPDATES)' in binja_source
    assert '"activate_landscape_entry",' in binja_source
    assert '"activate_landscape_entry",' in ida_source
    assert '("0x04", "alpha", "float")' in binja_source
    assert (
        '("0x10", "completion_callback", "FrontendFadeCallback")'
        in binja_source
    )
    for header in headers:
        assert "typedef void (__cdecl *FrontendFadeCallback)(void);" in header
        assert "typedef struct FrontendFade {" in header
        assert "float alpha;" in header
        assert "float hold_progress_step;" in header
        assert "FrontendFadeCallback completion_callback;" in header
        assert "typedef struct FrontendOverlayColorLerp {" in header
        assert "tColour target;" in header
        assert "tColour current;" in header
        assert "FrameColor4f" not in header

    assert "typedef void (*FrontendFadeCallback)();" in fade_header
    assert (
        "void begin_frontend_fade_out("
        "FrontendFadeCallback completion_callback);"
    ) in fade_header
    assert (
        "void FrontendFade::begin_frontend_fade_out("
        "FrontendFadeCallback completion_callback_)"
    ) in begin_fade_source
    assert "completion_callback = completion_callback_;" in begin_fade_source
    assert "hold_state" not in begin_fade_source
    assert "return completion_callback_" not in begin_fade_source

    assert (
        '"void __thiscall queue_frontend_widget_flag_after_delay("'
        in binja_source
    )
    assert (
        'f"{border_manager_type}* manager, FrontendWidget* widget, "'
        in binja_source
    )
    assert '"int32_t queued_flags)"' in binja_source
    assert (
        "void __thiscall queue_frontend_widget_flag_after_delay("
        "BorderManager *manager, FrontendWidget *widget, int32_t queued_flags);"
    ) in ida_joined_literals
    assert (
        "void BorderManager::queue_frontend_widget_flag_after_delay("
        in delayed_action_source
    )
    assert "result = g_game->fade.begin_frontend_fade_out" not in delayed_action_source
    assert "return result;" not in delayed_action_source


def test_viewport_owner_and_borrowed_camera_are_replayed_cross_decompiler() -> None:
    repo_root = Path(__file__).parents[1]
    matcher_header = (repo_root / "tools/match/include/viewport.h").read_text(
        encoding="utf-8"
    )
    game_root_header = (repo_root / "tools/match/include/game_root.h").read_text(
        encoding="utf-8"
    )
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("bn_frame_renderer_types.h", "frame_renderer_types.h")
    )
    binja_sync = (BINJA_DIR / "sync_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )

    assert "class Viewport" in matcher_header
    assert "RenderCamera* camera;" in matcher_header
    assert "int unknown_00;" in matcher_header
    assert "float unknown_1c;" in matcher_header
    assert "Viewport viewports[5];" in game_root_header

    for header in analysis_headers:
        assert "typedef struct Viewport {" in header
        assert "FrameRenderCamera* camera;" in header
        assert "Viewport viewports[5];" in header
        assert "FrameRenderCameraSlot" not in header

    for source in (binja_sync, ida_sync):
        assert "attach_render_camera_source" in source
        assert "initialize_render_camera_slot" in source
        assert "Viewport" in source
    assert '("0x5b4", "viewports", "Viewport[5]")' in binja_sync
    assert '("0x20", "camera", "FrameRenderCamera*")' in binja_sync
    assert "VIEWPORT_EXPECTED_MEMBERS" in ida_sync
    assert "GAME_ROOT_VIEWPORT_EXPECTED_MEMBERS" in ida_sync
    assert '"viewport_owner_readback": viewport_owner_readback' in ida_sync


def test_mouse_cursor_and_borrowed_input_owner_graph_is_replayed_cross_decompiler() -> None:
    repo_root = Path(__file__).parents[1]
    matcher_root = (repo_root / "tools/match/include/game_root.h").read_text(
        encoding="utf-8"
    )
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("bn_frame_renderer_types.h", "frame_renderer_types.h")
    )
    binja_sync = (BINJA_DIR / "sync_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}

    assert "GameInput* game_input; // +0x168" in matcher_root
    assert "MouseCursorState mouse_cursor; // +0x16c" in matcher_root
    for header in analysis_headers:
        assert "GameInput* game_input;" in header
        assert "MouseCursorState mouse_cursor;" in header

    for source in (binja_sync, ida_sync):
        for function in (
            "border_mouse_test",
            "resolve_uncaptured_cursor_sensitivity_scale",
            "click_mouse_screen",
            "get_sprite_tga",
        ):
            assert function in source
    assert "MOUSE_INPUT_OWNER_REANALYSIS_FUNCTIONS" in binja_sync
    assert "*MOUSE_INPUT_OWNER_REANALYSIS_FUNCTIONS" in binja_sync
    assert "MOUSE_INPUT_OWNER_FUNCTIONS" in ida_sync
    assert "_verify_mouse_input_owner_graph" in ida_sync
    assert '"mouse_input_owner_graph": mouse_input_owner_graph' in ida_sync
    for owner in (
        "g_game_base->players[0].mouse_cursor.saved_x",
        "g_game_base->players[0].mouse_cursor.saved_y",
        "->players[0].game_input->input.authored_x",
        "->players[0].game_input->input.authored_y",
    ):
        assert owner in ida_sync

    for name in (
        "bn_border_mouse_test_owner",
        "ida_border_mouse_test_owner",
        "bn_cursor_sensitivity_owner",
        "ida_cursor_sensitivity_owner",
        "bn_mouse_coordinate_globals",
        "ida_mouse_coordinate_globals",
    ):
        assert name in checks
    for name in ("bn_cursor_sensitivity_owner", "ida_cursor_sensitivity_owner"):
        assert (
            "is_mouse_captured(&g_game_base->players[0].mouse_cursor)"
            in checks[name]["required_substrings"]
        )
    for name in ("bn_mouse_coordinate_globals", "ida_mouse_coordinate_globals"):
        assert (
            "->players[0].game_input->input.authored_x"
            in checks[name]["required_substrings"]
        )
        assert (
            "->players[0].game_input->input.authored_y"
            in checks[name]["required_substrings"]
        )


def test_input_state_replays_preserve_portable_abi_and_text_input_repeat_ownership() -> None:
    repo_root = Path(__file__).parents[1]
    binja_source = (BINJA_DIR / "sync_input_state_types.py").read_text(
        encoding="utf-8"
    )
    binja_pointer_region_source = (
        BINJA_DIR / "sync_input_pointer_region_types.py"
    ).read_text(encoding="utf-8")
    ida_source = (IDA_DIR / "apply_input_state_types.py").read_text(
        encoding="utf-8"
    )
    headers = tuple(
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bn_input_state_types.h", "ida_input_state_types.h")
    )
    frame_headers = tuple(
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bn_frame_renderer_types.h", "frame_renderer_types.h")
    )
    matcher_controller_header = (
        repo_root / "tools/match/include/input_controller_state.h"
    ).read_text(encoding="utf-8")
    matcher_button_header = (
        repo_root / "tools/match/include/input_buttons.h"
    ).read_text(encoding="utf-8")

    assert "InputControllerSlot_must_be_0x20" in matcher_controller_header
    assert "INPUT_CONTROLLER_SLOT_STRIDE = 0x38" in matcher_controller_header
    assert "g_input_controller_slot0" in matcher_controller_header
    assert "g_input_controller_slot1" in matcher_controller_header
    assert "g_input_controller_slots[" not in matcher_controller_header
    assert "unknown_20" not in matcher_controller_header
    assert "void set_input_controller_slot0_button_axes(" in matcher_controller_header
    assert "void update_input_controller_slot_button_axes(" in matcher_controller_header
    assert "void copy_active_input_controller_state(" in matcher_controller_header
    assert "void update_input_controller_pointer_region(" in matcher_controller_header
    assert "types_declare_if_changed" in binja_source
    assert "types_declare(" not in binja_source
    assert "types_declare" not in binja_pointer_region_source

    for marker in (
        "INPUT_POINTER_REGION_FUNCTION_SYMBOL_UPDATES",
        "INPUT_POINTER_REGION_DATA_SYMBOL_UPDATES",
        "INPUT_POINTER_REGION_DATA_VAR_UPDATES",
        "INPUT_POINTER_REGION_PROTO_UPDATES",
        "apply_symbol_updates",
        "apply_data_var_updates",
        "apply_proto_updates",
    ):
        assert marker in binja_pointer_region_source

    for header in (*headers, *frame_headers):
        assert "typedef enum InputButtonFlag {" in header
        assert "INPUT_BUTTON_PRIMARY = 0x4000" in header
        assert "INPUT_BUTTON_SECONDARY = 0x8000" in header
        assert "INPUT_BUTTON_UNRESOLVED_00400000 = 0x00400000" in header
        assert "INPUT_BUTTON_UNRESOLVED_00800000 = 0x00800000" in header
        assert "InputButtonFlag pressed_buttons;" in header
        assert "InputButtonFlag current_buttons;" in header

    assert (
        "INPUT_BUTTON_UNRESOLVED_00400000 = 0x00400000"
        in matcher_button_header
    )
    assert (
        "INPUT_BUTTON_UNRESOLVED_00800000 = 0x00800000"
        in matcher_button_header
    )

    for header in headers:
        assert "typedef struct InputControllerSlot {" in header
        assert "InputButtonFlag buttons;" in header
        assert "float pointer_value;" in header
        assert "unknown_20" not in header

    for declaration in (
        "char __cdecl read_pressed_text_input_key_code(void);",
        "char __cdecl read_repeating_text_input_key_code(void);",
        "extern float g_text_input_repeat_step;",
        "extern float g_text_input_repeat_accumulator;",
        "extern uint8_t g_text_input_last_repeat_code;",
        "extern int32_t g_input_region_top[2];",
        "extern int32_t g_input_region_bottom[2];",
        "extern int32_t g_input_region_left[2];",
        "extern int32_t g_input_region_right[2];",
        "void __cdecl set_input_controller_slot0_button_axes(",
        "void __cdecl update_input_controller_slot_button_axes(",
        "void __cdecl copy_active_input_controller_state(",
        "void __cdecl update_input_controller_pointer_region(",
        "void __cdecl set_input_controller_pointer_authored_xy(",
        "uint8_t __cdecl is_key_pressed_edge(uint8_t key_code);",
        "uint8_t __cdecl is_key_down(uint8_t key_code);",
        "void __cdecl release_keyboard_input(void);",
        "void __cdecl click_mouse_screen(int32_t slot, int32_t x, int32_t y);",
        "extern uint8_t g_keyboard_previous_state[256];",
        "extern uint8_t g_keyboard_current_state[256];",
        "extern IDirectInput8A* g_keyboard_input;",
        "extern IDirectInputDevice8A* g_keyboard_device;",
        "void __thiscall initialize_input(InputState* state);",
        "void __thiscall update_input(InputState* state);",
        "void __thiscall update_game_input(GameInput* game_input);",
    ):
        assert all(declaration in header for header in headers)

    for marker in (
        '("0x50339c", "g_text_input_repeat_step")',
        '("0x50333c", "g_input_controller_slot0")',
        '("0x503374", "g_input_controller_slot1")',
        '("0x50333c", "InputControllerSlot")',
        '("0x503374", "InputControllerSlot")',
        '("0x08", "buttons", "InputButtonFlag")',
        "InputButtonFlag* out_buttons",
        "apply_symbol_removals",
        '("0x5108b8", "g_text_input_repeat_accumulator")',
        '("0x53c7f5", "g_text_input_last_repeat_code")',
        '"void __thiscall initialize_input(InputState* state)"',
        '"void __thiscall update_input(InputState* state)"',
        '"char __cdecl read_pressed_text_input_key_code()"',
        '"char __cdecl read_repeating_text_input_key_code()"',
        "RSHELL_INPUT_FUNCTION_SYMBOL_UPDATES",
        "GAME_INPUT_FUNCTION_SYMBOL_UPDATES",
        '("0x40aa50", "initialize_input")',
        '("0x40aa80", "update_input")',
        '("0x40aab0", "update_game_input")',
        "RSHELL_INPUT_PROTO_UPDATES",
        '("0x431fd0", "set_input_controller_slot0_button_axes")',
        '("0x431ff0", "update_input_controller_slot_button_axes")',
        '("0x4320f0", "copy_active_input_controller_state")',
        "INPUT_POINTER_REGION_FUNCTION_SYMBOL_UPDATES",
        "INPUT_POINTER_REGION_DATA_SYMBOL_UPDATES",
        "INPUT_POINTER_REGION_DATA_VAR_UPDATES",
        '("0x508890", "int32_t[2]")',
        '("0x508898", "int32_t[2]")',
        '("0x5088a0", "int32_t[2]")',
        '("0x5088a8", "int32_t[2]")',
        '"void __cdecl set_input_controller_slot0_button_axes(InputButtonFlag buttons, float axis_x, float axis_y)"',
        '"void __cdecl update_input_controller_slot_button_axes(int32_t slot, InputButtonFlag buttons, float axis_x, float axis_y)"',
        '"void __cdecl copy_active_input_controller_state(int32_t controller_slot, InputButtonFlag* out_buttons, float* out_axis_x, float* out_axis_y, float* out_authored_x, float* out_authored_y, float* out_pointer_value, float* out_pointer_x, float* out_pointer_y)"',
        '"void __cdecl update_input_controller_pointer_region(int32_t slot, int32_t left, int32_t top, int32_t right, int32_t bottom, int32_t x, int32_t y, int32_t pointer_value, char button_a, char button_b, char button_c, char capture_when_outside, char force_clamp)"',
        '"void __cdecl set_input_controller_pointer_authored_xy(int32_t slot, float authored_x, float authored_y)"',
        '"void __cdecl click_mouse_screen(int32_t slot, int32_t x, int32_t y)"',
        '"void __cdecl initialize_mouse_authored_scale_from_clip_rect()"',
        '"void __cdecl update_mouse_authored_scale(float authored_width, float authored_height)"',
        '"void __cdecl set_hide_system_cursor_flag(bool hidden)"',
        '"uint8_t __cdecl is_key_pressed_edge(uint8_t key_code)"',
        '"uint8_t __cdecl is_key_down(uint8_t key_code)"',
        '"void __cdecl release_keyboard_input()"',
        "KEYBOARD_DATA_SYMBOL_UPDATES",
        "KEYBOARD_DATA_VAR_UPDATES",
        "KEYBOARD_FUNCTION_SYMBOL_UPDATES",
        "KEYBOARD_FLAG_INT_DISPLAY_UPDATES",
        "apply_int_display_updates",
        '"81 ce 00 00 40 00"',
        '"81 ce 00 00 80 00"',
        '"buttons |= &__dos_header"',
        '"buttons |= &data_800000"',
        '("0x777b4c", "uint8_t[256]")',
        '("0x777c4c", "uint8_t[256]")',
        '("0x777d4c", "IDirectInput8A*")',
        '("0x777d50", "IDirectInputDevice8A*")',
        '"--target"',
    ):
        assert marker in binja_source

    assert '"int32_t __thiscall initialize_input(InputState* state)"' not in binja_source

    for marker in (
        '(0x50339C, 20, "g_text_input_repeat_step", "float[5]")',
        '(0x50333C, "g_input_controller_slot0")',
        '(0x503374, "g_input_controller_slot1")',
        '(0x40AA50, "initialize_input")',
        '(0x40AA80, "update_input")',
        '(0x40AAB0, "update_game_input")',
        '"InputControllerSlot g_input_controller_slot0;"',
        '"InputControllerSlot g_input_controller_slot1;"',
        "InputButtonFlag *out_buttons",
        "INPUT_CONTROLLER_INTERIOR_NAMES",
        "unexpected_input_controller_interior_name",
        '(0x53C7F5, 3, "g_text_input_last_repeat_code", "char[3]")',
        "STALE_DATA_ITEM_SPECS",
        "_clear_stale_data_item",
        '"reason": "unexpected_stale_data_item"',
        '"phase": "data_item_guard"',
        'r"\\buint8_t\\b|\\bunsigned __int8\\b"',
        '"char __cdecl read_repeating_text_input_key_code();"',
        '"void __thiscall initialize_input(InputState *state);"',
        '"void __thiscall update_input(InputState *state);"',
        '"float g_text_input_repeat_step;"',
        '"unsigned char g_text_input_last_repeat_code;"',
        '(0x508890, 8)',
        '(0x508898, 8)',
        '(0x5088A0, 8)',
        '(0x5088A8, 8)',
        '"int g_input_region_top[2];"',
        '"int g_input_region_bottom[2];"',
        '"int g_input_region_left[2];"',
        '"int g_input_region_right[2];"',
        '"void __cdecl set_input_controller_slot0_button_axes(InputButtonFlag buttons, float axis_x, float axis_y);"',
        '"void __cdecl update_input_controller_slot_button_axes(int slot, InputButtonFlag buttons, float axis_x, float axis_y);"',
        '"void __cdecl copy_active_input_controller_state(int controller_slot, InputButtonFlag *out_buttons, float *out_axis_x, float *out_axis_y, float *out_authored_x, float *out_authored_y, float *out_pointer_value, float *out_pointer_x, float *out_pointer_y);"',
        '"void __cdecl update_input_controller_pointer_region(int slot, int left, int top, int right, int bottom, int x, int y, int pointer_value, char button_a, char button_b, char button_c, char capture_when_outside, char force_clamp);"',
        '"void __cdecl set_input_controller_pointer_authored_xy(int slot, float authored_x, float authored_y);"',
        '"void __cdecl click_mouse_screen(int slot, int x, int y);"',
        '"void __cdecl initialize_mouse_authored_scale_from_clip_rect();"',
        '"void __cdecl update_mouse_authored_scale(float authored_width, float authored_height);"',
        '"void __cdecl set_hide_system_cursor_flag(bool hidden);"',
        '"uint8_t __cdecl is_key_pressed_edge(uint8_t key_code);"',
        '"uint8_t __cdecl is_key_down(uint8_t key_code);"',
        '"void __cdecl release_keyboard_input();"',
        '"uint8_t g_keyboard_previous_state[256];"',
        '"uint8_t g_keyboard_current_state[256];"',
        '"IDirectInput8A *g_keyboard_input;"',
        '"IDirectInputDevice8A *g_keyboard_device;"',
        "KEYBOARD_FLAG_NUMERIC_OPERANDS",
        "_normalize_keyboard_flag_numeric_operands",
        '"81 ce 00 00 40 00"',
        '"81 ce 00 00 80 00"',
        '"keyboard_flag_numeric_operands"',
        "(0x777B4C, 256)",
        "(0x777C4C, 256)",
    ):
        assert marker in ida_source

    assert '"int __thiscall initialize_input(InputState *state);"' not in ida_source

    references = json.loads(
        (repo_root / "analysis/symbols/gameplay-references.json").read_text(
            encoding="utf-8"
        )
    )
    aliases_by_address = {
        entry["address"]: set(entry.get("aliases", []))
        for entry in references["symbols"]
    }
    references_by_address = {
        entry["address"]: entry for entry in references["symbols"]
    }
    assert references_by_address["0x50333c"]["name"] == "g_input_controller_slot0"
    assert references_by_address["0x50333c"]["size"] == "0x20"
    assert references_by_address["0x503374"]["name"] == "g_input_controller_slot1"
    assert references_by_address["0x503374"]["size"] == "0x20"
    assert references_by_address["0x503340"]["kind"] == "offset"
    assert references_by_address["0x50339c"]["kind"] == "global"
    assert "RShellInput" in aliases_by_address["0x50333c"]
    assert "gMouseWY0" in aliases_by_address["0x508890"]
    assert "gMouseWY1" in aliases_by_address["0x508898"]
    assert "gMouseWX0" in aliases_by_address["0x5088a0"]
    assert "gMouseWX1" in aliases_by_address["0x5088a8"]
    assert "gRShellKeyRepeatLifeRate" in aliases_by_address["0x50339c"]
    assert "gRShellKeyRepeatLife" in aliases_by_address["0x5108b8"]
    assert "gRShellOldKey" in aliases_by_address["0x53c7f5"]
    assert "gG0ScreenHeight" in aliases_by_address["0x4b7760"]
    assert "gG0ScreenWidth" in aliases_by_address["0x4df85c"]
    assert "gWindowMouseState" in aliases_by_address["0x777d70"]

    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    entries_by_address = {
        entry["address"]: entry for entry in crosswalk["entries"]
    }
    assert (
        entries_by_address["0x431fd0"]["android_symbol"]
        == "RShellInputRegisterKeyboard(int, float, float)"
    )
    assert (
        entries_by_address["0x431ff0"]["android_symbol"]
        == "RShellInputRegister(int, int, float, float)"
    )
    assert entries_by_address["0x4320f0"]["android_symbol"].startswith(
        "RShellInputRetrieve("
    )
    assert entries_by_address["0x4320f0"]["ios_symbol"].startswith(
        "RShellInputRetrieve("
    )
    assert entries_by_address["0x4321c0"]["android_symbol"].startswith(
        "RShellInputRegisterMouse("
    )
    assert entries_by_address["0x4321c0"]["ios_symbol"].startswith(
        "RShellInputRegisterMouse("
    )
    assert entries_by_address["0x432440"]["ios_symbol"] == "RShellInkey()"
    assert (
        entries_by_address["0x4327e0"]["ios_symbol"]
        == "RShellInkeyInput()"
    )
    for address, android_symbol, ios_symbol in (
        (
            "0x4323a0",
            "RShellSetMouse(int, float, float)",
            "RShellSetMouse(int, float, float)",
        ),
        (
            "0x447290",
            "cLinkedList<cRBod>::Remove(cRBod*)",
            None,
        ),
        (
            "0x44b7d0",
            "KeyboardInit()",
            "KeyboardInit()",
        ),
        (
            "0x44b870",
            "KeyboardAI()",
            "KeyboardAI()",
        ),
        (
            "0x44bb10",
            "KeyPress(unsigned char)",
            "KeyPress(unsigned char)",
        ),
        (
            "0x44bb40",
            "KeyOn(unsigned char)",
            "KeyOn(unsigned char)",
        ),
        (
            "0x44bb60",
            "FreeDirectInputKeyboard()",
            None,
        ),
        (
            "0x44bbb0",
            "MouseGetDesktopSize()",
            None,
        ),
        (
            "0x44bbd0",
            "MouseCalcDesktopScale(float, float)",
            None,
        ),
        (
            "0x433030",
            "RShellGetScreenWidth()",
            "RShellGetScreenWidth()",
        ),
        (
            "0x433040",
            "RShellGetScreenHeight()",
            "RShellGetScreenHeight()",
        ),
        (
            "0x44bc20",
            "MouseCalcScale(float)",
            "MouseCalcScale(float)",
        ),
        (
            "0x44bc50",
            "ReadImmediateDataMouse()",
            None,
        ),
        (
            "0x44c050",
            "HideWindowMouse(bool)",
            "HideWindowMouse(bool)",
        ),
        (
            "0x44c060",
            "MouseSet(int, int, int)",
            "MouseSet(int, int, int)",
        ),
        (
            "0x44c100",
            "MouseRead(int, float*, float*)",
            None,
        ),
    ):
        assert entries_by_address[address]["android_symbol"] == android_symbol
        assert entries_by_address[address].get("ios_symbol") == ios_symbol
        assert entries_by_address[address]["confidence"] == "high"

    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    functions_by_address = {
        entry["address"]: entry for entry in functions["functions"]
    }
    assert "RShellInputRegisterKeyboard" in functions_by_address["0x431fd0"]["aliases"]
    assert "RShellInputRegister" in functions_by_address["0x431ff0"]["aliases"]
    assert "RShellInputRetrieve" in functions_by_address["0x4320f0"]["aliases"]
    assert "RShellInputRegisterMouse" in functions_by_address["0x4321c0"]["aliases"]
    assert "RShellSetMouse" in functions_by_address["0x4323a0"]["aliases"]
    assert "KeyboardInit" in functions_by_address["0x44b7d0"]["aliases"]
    assert "KeyboardAI" in functions_by_address["0x44b870"]["aliases"]
    assert "KeyPress" in functions_by_address["0x44bb10"]["aliases"]
    assert "KeyOn" in functions_by_address["0x44bb40"]["aliases"]
    assert (
        "FreeDirectInputKeyboard"
        in functions_by_address["0x44bb60"]["aliases"]
    )
    assert "RShellGetScreenWidth" in functions_by_address["0x433030"]["aliases"]
    assert "RShellGetScreenHeight" in functions_by_address["0x433040"]["aliases"]
    assert "MouseCalcScale" in functions_by_address["0x44bc20"]["aliases"]
    assert "MouseGetDesktopSize" in functions_by_address["0x44bbb0"]["aliases"]
    assert "MouseCalcDesktopScale" in functions_by_address["0x44bbd0"]["aliases"]
    assert "ReadImmediateDataMouse" in functions_by_address["0x44bc50"]["aliases"]
    assert "HideWindowMouse" in functions_by_address["0x44c050"]["aliases"]
    assert "MouseSet" in functions_by_address["0x44c060"]["aliases"]
    assert "MouseRead" in functions_by_address["0x44c100"]["aliases"]

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    check_names = {check["name"] for check in health["checks"]}
    for name in (
        "bn_keyboard_directinput_owner_graph",
        "ida_keyboard_directinput_owner_graph",
        "bn_keyboard_flag_immediate_ownership",
        "ida_keyboard_flag_immediate_ownership",
        "bn_keypress_mobile_argument_and_state_ownership",
        "ida_keypress_mobile_argument_and_state_ownership",
        "bn_keyon_mobile_argument_and_state_ownership",
        "ida_keyon_mobile_argument_and_state_ownership",
        "bn_keyboard_teardown_void_owner",
        "ida_keyboard_teardown_void_owner",
        "bn_hide_window_mouse_mobile_void_abi",
        "ida_hide_window_mouse_mobile_void_abi",
        "bn_mouse_desktop_scale_wrapper_void_abi",
        "ida_mouse_desktop_scale_wrapper_void_abi",
    ):
        assert name in check_names


def test_ida_lvar_inspector_reports_stable_local_identity() -> None:
    inspector = (IDA_DIR / "inspect_function_lvars.py").read_text(encoding="utf-8")
    wrapper = (IDA_DIR / "query_function_lvars.py").read_text(encoding="utf-8")

    for marker in (
        "cfunc.get_lvars()",
        '"definition_address"',
        '"location"',
        '"stack_offset"',
        "lvar.get_stkoff()",
        "re.compile(pattern, re.IGNORECASE)",
        'str(entry["name"])',
        'str(entry["type"])',
        'str(entry["definition_address"])',
        '"reason": "decompile_failed"',
        '"error": "Hex-Rays returned no cfunc"',
    ):
        assert marker in inspector
    assert 'IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/inspect_function_lvars.py"' in wrapper
    assert 'parser.add_argument(\n        "--match",' in wrapper
    assert 'script_args=[*args.selectors, "--", args.match]' in wrapper
    assert "if matcher is not None" in inspector


def test_ida_operand_inspector_reports_numeric_operand_identity() -> None:
    inspector = (IDA_DIR / "inspect_function_operands.py").read_text(
        encoding="utf-8"
    )
    wrapper = (IDA_DIR / "query_function_operands.py").read_text(encoding="utf-8")

    for marker in (
        "ida_funcs.get_func_start(address)",
        "idautils.FuncItems(function_start)",
        "idc.get_operand_type(address, operand_index)",
        "idc.get_operand_value(address, operand_index)",
        "idc.print_operand(address, operand_index)",
        '"disassembly"',
        '"operands"',
    ):
        assert marker in inspector
    assert 'IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/inspect_function_operands.py"' in wrapper
    assert 'script_args=[*args.selectors, "--", args.match]' in wrapper


def test_ida_94_function_presence_checks_avoid_deprecated_get_func() -> None:
    operand_inspector = (IDA_DIR / "inspect_function_operands.py").read_text(
        encoding="utf-8"
    )
    path_replay = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )

    assert "ida_funcs.get_func(" not in operand_inspector
    assert "ida_funcs.get_func(" not in path_replay


def test_ida_path_replay_verifies_player_shoot_members() -> None:
    repo_root = Path(__file__).parents[1]
    path_replay = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    binja_replay = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")

    for marker in (
        "PLAYER_SHOOT_EXPECTED_MEMBERS",
        '"name": "shooting_tier"',
        '"name": "shoot_flags"',
        '"name": "previous_shoot_flags"',
        '"name": "shoot_cooldown_progress"',
        '"name": "shoot_cooldown_step"',
        '"owner_group": "player_shoot_state"',
        '"player_shoot_members": player_shoot_members',
    ):
        assert marker in path_replay

    for field in (
        '("0x308", "shooting_tier", "int32_t")',
        '("0x338", "shoot_flags", "uint32_t")',
        '("0x33c", "previous_shoot_flags", "uint32_t")',
    ):
        assert field in binja_replay
    for declaration in (
        "int32_t shooting_tier;",
        "uint32_t shoot_flags;",
        "uint32_t previous_shoot_flags;",
    ):
        assert declaration in header

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    for check_name in (
        "bn_player_shoot_cooldown_step_owner",
        "ida_player_shoot_cooldown_step_owner",
    ):
        check = checks[check_name]
        for field in (
            "player->shooting_tier",
            "player->shoot_flags",
            "player->previous_shoot_flags",
        ):
            assert field in check["required_substrings"]
        assert "player->movement_flags" in check["forbidden_substrings"]


def test_ghidra_symbol_probe_is_versioned_bounded_and_persistent() -> None:
    repo_root = Path(__file__).parents[1]
    wrapper = (repo_root / "tools/ghidra/decompile_symbol.py").read_text(
        encoding="utf-8"
    )
    script = (repo_root / "tools/ghidra/DecompileSymbol.java").read_text(
        encoding="utf-8"
    )

    assert 'Path("/Applications/ghidra_12.1.2_PUBLIC")' in wrapper
    assert "-Duser.home=" in wrapper
    assert "locked_persistent_project(" in wrapper
    assert "temporary_fresh_project(" in wrapper
    assert '"--fresh"' in wrapper
    assert '"DecompileSymbol.java"' in wrapper
    assert '"selector"' in wrapper
    assert '"ELF, Mach-O, or PE artifact to import"' in wrapper
    assert "capture_output=True" in wrapper
    assert "FAILURE_LOG_LINES = 80" in wrapper
    assert 'output_path = project.root / "decompile.txt"' in wrapper
    assert "output_path.read_text" in wrapper
    assert "function.getName(true)" in script
    assert "ambiguous function fragment" in script
    assert 'selector.matches("0[xX][0-9a-fA-F]+")' in script
    assert "getFunctionAt(address)" in script
    assert '"no function at " + selector' in script
    assert "Files.writeString(outputPath" in script
    assert '"GHIDRA_VERSION="' in script


def test_ida_type_inspectors_report_function_and_data_ownership() -> None:
    function_inspector = (IDA_DIR / "inspect_function_types.py").read_text(
        encoding="utf-8"
    )
    function_wrapper = (IDA_DIR / "query_function_types.py").read_text(
        encoding="utf-8"
    )
    data_inspector = (IDA_DIR / "inspect_data_types.py").read_text(
        encoding="utf-8"
    )
    data_wrapper = (IDA_DIR / "query_data_types.py").read_text(encoding="utf-8")
    struct_inspector = (IDA_DIR / "inspect_named_structs.py").read_text(
        encoding="utf-8"
    )
    struct_wrapper = (IDA_DIR / "query_named_structs.py").read_text(
        encoding="utf-8"
    )

    for marker in (
        "ida_funcs.get_func_start(address)",
        '"type": idc.get_type(address)',
        '"name": idc.get_func_name(address)',
    ):
        assert marker in function_inspector
    assert 'IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/inspect_function_types.py"' in function_wrapper
    assert "script_args=list(args.selectors)" in function_wrapper
    lvar_inspector = (IDA_DIR / "inspect_function_lvars.py").read_text(
        encoding="utf-8"
    )
    assert '"stack_pointer_changes"' in lvar_inspector
    assert "idc.get_sp_delta(item_address)" in lvar_inspector
    assert "idc.get_spd(item_address)" in lvar_inspector

    for marker in (
        "ida_bytes.get_item_head(address)",
        '"item_head_type": idc.get_type(item_head)',
        '"item_size": ida_bytes.get_item_size(item_head)',
    ):
        assert marker in data_inspector
    assert 'IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/inspect_data_types.py"' in data_wrapper
    assert "script_args=list(args.selectors)" in data_wrapper
    for marker in (
        "owner.get_named_type(None, selector, ida_typeinf.BTF_STRUCT)",
        "owner.get_udt_details(members)",
        '"offset": hex(int(member.offset) // 8)',
        '"type": member.type.dstr()',
    ):
        assert marker in struct_inspector
    assert 'IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/inspect_named_structs.py"' in struct_wrapper
    assert "script_args=list(args.selectors)" in struct_wrapper


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
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
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
    assert '("Fringe", FRINGE_FIELD_UPDATES)' in path_sync
    assert '("FringeManager", FRINGE_MANAGER_FIELD_UPDATES)' in path_sync
    assert "Object* object;" in path_header
    assert "int set_bod_object(Object* object);" in matcher_header
    renderable_constructor = (
        "RenderableBod* __thiscall initialize_renderable_bod("
        "RenderableBod* body)"
    )
    assert renderable_constructor in path_sync
    assert renderable_constructor + ";" in path_header
    assert renderable_constructor + ";" in ida_path_sync
    assert "RenderableBod* initialize_renderable_bod();" in matcher_header
    assert "0x42F650" in ida_path_sync
    bod_constructor = "BodBase* __thiscall initialize_bod_base(BodBase* bod)"
    assert bod_constructor in path_sync
    assert bod_constructor + ";" in path_header
    assert bod_constructor + ";" in ida_path_sync
    for owner_name in (
        "g_bod_base_vtable",
        "g_renderable_bod_vtable",
        "g_bod_base_init_count",
    ):
        assert owner_name in path_sync
        assert owner_name in ida_path_sync
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
        "initialize_renderable_bod",
        "apply_bod_position",
        "build_track_fringe_mesh",
        "build_track_fringe_supertramp_mesh",
    ):
        assert f'"{function_name}"' in path_sync


def test_bod_intrusive_list_lifecycle_replay_owns_shared_layout() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    normalized_header = (
        " ".join(path_header.split()).replace("( ", "(").replace(" )", ")")
    )
    bod_list_header = (repo_root / "tools/match/include/bod_list.h").read_text(
        encoding="utf-8"
    )
    bod_types_header = (repo_root / "tools/match/include/bod_types.h").read_text(
        encoding="utf-8"
    )

    assert '"--bod-core-only"' in path_sync
    assert "verify_bod_core_owner_sizes" in path_sync
    assert "current_type_widths(" in path_sync
    for name, size in (
        ("BodNode", "0x10"),
        ("BodList", "0x0C"),
        ("BodBase", "0x38"),
        ("RenderableBod", "0x80"),
    ):
        assert f'"{name}": {size}' in path_sync
        assert f'"{name}": {size}' in ida_sync
        assert f"{name}_must_be_{size}".lower() in path_header.lower()

    declarations = (
        "void __thiscall add_bod_to_front(BodList* list, BodNode* node)",
        "void __thiscall append_bod_to_end(BodList* list, BodNode* node)",
        "bool __thiscall is_bod_after_sprites(BodBase* bod)",
        "int32_t __thiscall set_bod_object(BodBase* bod, Object* object)",
        "BodBase* __thiscall initialize_bod_base(BodBase* bod)",
        "Object* __thiscall apply_bod_position(BodBase* bod, TransformMatrix* matrix)",
        "void __thiscall recycle_bod_to_free_list(BodList* list, BodNode* node)",
    )
    for declaration in declarations:
        assert declaration in path_sync
        assert declaration + ";" in ida_sync
        assert declaration + ";" in normalized_header

    for address in (
        "0x4113B0",
        "0x411420",
        "0x40A490",
        "0x42F5C0",
        "0x42F5D0",
        "0x42F680",
        "0x447290",
    ):
        assert address in ida_sync

    assert "void add_bod_to_front(BodNode* node);" in bod_list_header
    assert "void append_bod_to_end(BodNode* node);" in bod_list_header
    assert "void recycle_bod_to_free_list(BodNode* node);" in bod_list_header
    assert "bool is_bod_after_sprites();" in bod_types_header
    assert "int set_bod_object(Object* object);" in bod_types_header
    assert "Object* apply_bod_position(TransformMatrix* matrix);" in bod_types_header


def test_fringe_replay_owns_authored_pool_and_callback_abi() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    normalized_header = (
        " ".join(path_header.split()).replace("( ", "(").replace(" )", ")")
    )
    fringe_header = (
        repo_root / "tools/match/include/fringe_object.h"
    ).read_text(encoding="utf-8")
    fringe_fwd = (repo_root / "tools/match/include/fringe_fwd.h").read_text(
        encoding="utf-8"
    )

    assert '"--fringe-only"' in path_sync
    assert "verify_fringe_owner_sizes" in path_sync
    assert "POPULATE_FRINGE_USER_VAR_UPDATES" in path_sync
    assert '"Fringe": 0x38' in path_sync
    assert '"FringeManager": 0x5FB44' in path_sync
    assert '"Fringe": 0x38' in ida_sync
    assert '"FringeManager": 0x5FB44' in ida_sync
    assert "Fringe_must_be_0x38" in path_header
    assert "FringeManager_must_be_0x5fb44" in path_header
    assert "Fringe objects[7000];" in path_header
    assert "Fringe[7000]" in path_sync

    declarations = (
        "Fringe* __thiscall initialize_fringe_object(Fringe* fringe)",
        "void __thiscall refresh_fringe_object_draw_list(Fringe* fringe)",
        "void __thiscall initialize_fringe_manager(FringeManager* manager)",
        "Fringe* __thiscall allocate_fringe_object(FringeManager* manager)",
    )
    for declaration in declarations:
        assert declaration in path_sync
        assert declaration + ";" in ida_sync
        assert declaration + ";" in normalized_header

    for field_name in ("fringe_front", "fringe_right", "fringe_left", "fringe_back"):
        assert f'"{field_name}", "Fringe*"' in path_sync
        assert f"Fringe* {field_name};" in path_header

    for address in ("0x408650", "0x434BE0", "0x439B00", "0x447090", "0x4470A0"):
        assert address in ida_sync

    assert "class Fringe : public BodBase" in fringe_header
    assert "Fringe objects[7000];" in fringe_header
    assert "FringeObject" not in fringe_fwd
    for canonical_text in (path_sync, ida_sync, path_header):
        assert "FringeObject" not in canonical_text


def test_track_render_cache_slot_owns_active_bod_lifecycle() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/segment_cache.h").read_text(
        encoding="utf-8"
    )
    frame_source = (
        repo_root / "tools/match/scratches/run_frame_update/scratch.cpp"
    ).read_text(encoding="utf-8")

    assert "class TrackRenderCacheSlot : public BodBase" in matcher_header
    assert "TrackRenderCacheSlot* initialize_active_bod();" in matcher_header
    assert "void update_active_bod();" in matcher_header
    assert not (repo_root / "tools/match/include/active_bod.h").exists()
    assert "BodNode* bod = active_bod_list.first;" in frame_source
    assert "((BodAiDispatch*)bod)->update_bod_ai();" in frame_source

    assert "typedef struct TrackRenderCacheSlot" in analysis_header
    assert "BodBase bod;" in analysis_header
    assert "float cache_row_base;" in analysis_header
    assert '"TrackRenderCacheSlot",' in path_sync
    assert "TRACK_RENDER_CACHE_SLOT_FIELD_UPDATES" in path_sync
    assert '"--track-cache-only"' in path_sync
    for marker in (
        "BOD_CORE_SYMBOL_UPDATES",
        "BOD_CORE_DATA_VAR_UPDATES",
        "BOD_CORE_PROTO_UPDATES",
        "TRACK_RENDER_CACHE_SYMBOL_UPDATES",
        "TRACK_RENDER_CACHE_DATA_VAR_UPDATES",
        "TRACK_RENDER_CACHE_PROTO_UPDATES",
    ):
        assert marker in path_sync
    for declaration in (
        "TrackRenderCacheSlot* __thiscall initialize_active_bod(TrackRenderCacheSlot* slot)",
        "void __thiscall update_active_bod(TrackRenderCacheSlot* slot)",
    ):
        assert declaration in path_sync
        assert declaration + ";" in ida_sync
        assert declaration + ";" in analysis_header


def test_click_start_and_landscape_lifecycle_replay_share_real_owners() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    click_matcher = (repo_root / "tools/match/include/click_start.h").read_text(
        encoding="utf-8"
    )
    landscape_matcher = (
        repo_root / "tools/match/include/active_landscape_entry.h"
    ).read_text(encoding="utf-8")

    assert '"ActiveLandscapeEntry",' in path_sync
    assert "ACTIVE_LANDSCAPE_ENTRY_FIELD_UPDATES" in path_sync
    assert '("0x88", "repeat_z_span", "float")' in path_sync
    assert '("0x8c", "reference_bod", "RenderableBod*")' in path_sync
    assert '"ActiveLandscapeEntry",\n                    ACTIVE_LANDSCAPE_ENTRY_FIELD_UPDATES' in path_sync
    assert '"--landscape-loader-only"' in path_sync

    declarations = (
        "ClickStart* __thiscall initialize_click_start_controller_runtime(ClickStart* click_start)",
        "void __thiscall initialize_click_start(ClickStart* click_start, Player* player)",
        "void __thiscall update_click_start(ClickStart* click_start)",
        "ActiveLandscapeEntry* __thiscall initialize_active_landscape_entry(ActiveLandscapeEntry* active_entry)",
        "void __thiscall reset_landscape_manager(LandscapeManager* manager)",
        "void __thiscall activate_landscape_entry(LandscapeManager* manager, int32_t script_index)",
        "void __thiscall clear_active_landscape_entries(LandscapeManager* manager)",
        "void __thiscall update_active_landscape_entry(ActiveLandscapeEntry* active_entry)",
        "int32_t __thiscall load_landscape_script_by_name(LandscapeManager* manager, char* script_name)",
    )
    for declaration in declarations:
        assert declaration in path_sync
        assert declaration + ";" in ida_sync

    for function_name in (
        "initialize_click_start_controller_runtime",
        "initialize_click_start",
        "update_click_start",
        "initialize_active_landscape_entry",
        "reset_landscape_manager",
        "activate_landscape_entry",
        "clear_active_landscape_entries",
        "update_active_landscape_entry",
        "load_landscape_script_by_name",
    ):
        assert function_name in path_header

    assert "class ClickStart : public RenderableBod" in click_matcher
    assert "Player* owner_player" in click_matcher
    assert "class ActiveLandscapeEntry : public RenderableBod" in landscape_matcher
    assert "RenderableBod* reference_bod" in landscape_matcher
    for address in (
        "0x408670",
        "0x408820",
        "0x4182E0",
        "0x4182F0",
        "0x418870",
        "0x418A30",
        "0x418AC0",
        "0x442170",
        "0x442290",
    ):
        assert address in ida_sync


def test_slug_voice_manager_replay_uses_embedded_owner() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/slug_voice_manager.h"
    ).read_text(encoding="utf-8")

    declarations = (
        "void __thiscall initialize_slug_voice_manager(SlugVoiceManager* manager)",
        "void __thiscall update_slug_voice_manager(SlugVoiceManager* manager)",
    )
    for declaration in declarations:
        assert declaration in binja_sync
        assert declaration + ";" in ida_sync

    assert "SLUG_VOICE_MANAGER_PROTO_UPDATES" in binja_sync
    assert 'typedef struct SlugVoiceManager {' in analysis_header
    assert "SlugVoiceManager slug_voice_manager;" in analysis_header
    assert "class SlugVoiceManager" in matcher_header
    for marker in (
        '(0x43F5C0, "initialize_slug_voice_manager")',
        '(0x43F5E0, "update_slug_voice_manager")',
        "0x437EB0,  # build_subgame_level",
        "0x438B90,  # update_subgame",
    ):
        assert marker in ida_sync


def test_object_list_replay_owns_global_lifecycle_and_allocation_consumers() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_object_render_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("bn_object_render_types.h", "object_render_types.h")
    )
    matcher_header = (
        repo_root / "tools/match/include/object_render_types.h"
    ).read_text(encoding="utf-8")

    for address, name in (
        ("0x42f990", "initialize_object_list"),
        ("0x42f9e0", "build_all_objects"),
        ("0x42fad0", "add_object_to_list"),
    ):
        assert f'("{address}", "{name}")' in binja_sync
        assert f'(0x{int(address, 0):X}, "{name}")' in ida_sync

    assert '("0x4b7648", "g_object_list")' in binja_sync
    assert '("0x4b7648", "ObjectList")' in binja_sync
    assert '(0x4B7648, "g_object_list")' in ida_sync
    assert '(0x4B7648, "g_object_list", "ObjectList g_object_list;")' in ida_sync
    assert '"ObjectList": 0xC' in ida_sync

    for header in (*analysis_headers, matcher_header):
        assert "ObjectList_must_be_0x0c" in header
        assert "extern ObjectList g_object_list;" in header

    for address in (
        "0x419110",  # open_logo
        "0x4246A0",  # build_track_fringe_mesh
        "0x424AD0",  # build_track_fringe_supertramp_mesh
        "0x42F990",  # initialize_object_list
        "0x42FAD0",  # add_object_to_list
        "0x430D90",  # replace_object_list_texture_refs
        "0x44AE10",  # initialize_font3d_objects
    ):
        assert address in ida_sync


def test_object_geometry_replay_keeps_owned_helpers_and_workspace_globals() -> None:
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

    for address, name, data_type in (
        ("0x503300", "g_object_edge_build_edges", "ObjectToonEdge*"),
        ("0x503318", "g_object_edge_build_count", "int32_t"),
    ):
        assert f'("{address}", "{name}")' in sync_source
        assert f'("{address}", "{data_type}")' in sync_source
        for header in analysis_headers:
            assert name in header

    for function_name in (
        "request_object_vertices",
        "request_object_vertices_copy",
        "request_object_facequad_normals",
        "request_object_facequads",
        "request_object_texture_groups",
        "request_object_edges",
        "calc_object_bounding_box",
        "calc_object_facequad_normals",
        "calc_object_facequad_normals_simple",
        "calc_object_texture_groups",
        "add_object_edge",
        "calc_object_edges",
    ):
        assert f'"{function_name}"' in sync_source

    for address, name, declaration in (
        (
            "0x42F710",
            "request_object_vertices",
            "void __thiscall request_object_vertices(Object* object, int32_t vertex_count);",
        ),
        (
            "0x42F7D0",
            "request_object_vertices_copy",
            "void __thiscall request_object_vertices_copy(Object* object);",
        ),
        (
            "0x42F800",
            "request_object_facequad_normals",
            "Vec3* __thiscall request_object_facequad_normals(Object* object);",
        ),
        (
            "0x42F8C0",
            "request_object_facequads",
            "void __thiscall request_object_facequads(Object* object, int32_t facequad_count);",
        ),
        (
            "0x430570",
            "request_object_edges",
            "void __thiscall request_object_edges(Object* object, int32_t edge_count);",
        ),
    ):
        assert f'({address}, "{name}")' in ida_sync_source
        assert f'"{declaration}"' in ida_sync_source

    for address, name in (
        ("0x405640", "load_x_mesh"),
        ("0x41aa50", "apply_distort_to_object"),
        ("0x42fb10", "calc_object_bounding_box"),
        ("0x42fcb0", "calc_object_facequad_normals"),
        ("0x430230", "calc_object_facequad_normals_simple"),
        ("0x4303f0", "calc_object_texture_groups"),
        ("0x4305a0", "add_object_edge"),
        ("0x4308b0", "calc_object_edges"),
    ):
        assert f'("{address}", "{name}")' in sync_source
        assert f'({address.upper().replace("0X", "0x")}, "{name}")' in ida_sync_source

    for address, name, declaration in (
        (
            "0x503300",
            "g_object_edge_build_edges",
            "ObjectToonEdge* g_object_edge_build_edges;",
        ),
        ("0x503318", "g_object_edge_build_count", "int32_t g_object_edge_build_count;"),
    ):
        assert f'({address}, "{name}")' in ida_sync_source
        assert declaration in ida_sync_source

    for owner_name, expected_size in (
        ("Vec3", "0xC"),
        ("TextureRef", "0xA4"),
        ("ObjectFaceQuad", "0x30"),
        ("ObjectToonEdge", "0x24"),
        ("ObjectDistort", "0x14"),
        ("Object", "0xDC"),
        ("DuplicateVertices", "0x8"),
        ("CachedXMeshSlot", "0xBC"),
        ("DirectXLoader", "0x5E10"),
    ):
        assert f'"{owner_name}": {expected_size}' in ida_sync_source

    for address in (
        "0x405640",
        "0x405CC0",
        "0x405D60",
        "0x40ACF0",
        "0x412250",
        "0x41AA50",
        "0x42F710",
        "0x42F7D0",
        "0x42F800",
        "0x42F8C0",
        "0x42F9E0",
        "0x42FB10",
        "0x42FCB0",
        "0x430230",
        "0x4303F0",
        "0x430570",
        "0x4305A0",
        "0x4308B0",
        "0x430A70",
    ):
        assert address in ida_sync_source

    for selector, definition_address, local_name, declaration in (
        (
            "calc_object_facequad_normals",
            "0x42FCD3",
            "normal_tally",
            "float *normal_tally;",
        ),
        ("add_object_edge", "0x4305E0", "edge_index", "int32_t edge_index;"),
        (
            "calc_object_edges",
            "0x4308CA",
            "build_edges",
            "ObjectToonEdge *build_edges;",
        ),
    ):
        assert selector in ida_sync_source
        assert definition_address in ida_sync_source
        assert local_name in ida_sync_source
        assert declaration in ida_sync_source
    assert "_sync_topology_lvars()" in ida_sync_source

    assert "idc.PT_FILE | idc.PT_REPLACE" in ida_sync_source
    assert "ida_hexrays.mark_cfunc_dirty(function.start_ea, True)" in ida_sync_source
    assert 're.sub(r"\\b(?:struct|union|enum)\\s+", "", normalized)' in ida_sync_source
    assert 'declaration = "ObjectRenderVertex *vertices;"' in ida_sync_source
    assert '("animated_vertices", 0x4122D0)' in ida_sync_source
    assert '("dynamic_vertices", 0x412350)' in ida_sync_source
    assert "info.set_split_lvar()" in ida_sync_source
    assert (
        "void __thiscall load_x_mesh(DirectXLoader* loader, char* mesh_path, "
        "Object* object, int32_t options_flags);"
    ) in ida_sync_source
    assert (
        "void __thiscall apply_distort_to_object(ObjectDistort* distort, "
        "Object* object);"
    ) in ida_sync_source

    assert "Vec3* __thiscall request_object_facequad_normals(Object* object)" in sync_source
    assert (
        "int32_t __thiscall calc_object_facequad_normals_simple(Object* object)"
        in sync_source
    )
    assert "Vector3* request_object_facequad_normals();" in matcher_header
    for header in analysis_headers:
        assert (
            "void __thiscall request_object_vertices("
            "Object* object, int32_t vertex_count);"
        ) in header
        assert (
            "void __thiscall request_object_vertices_copy(Object* object);"
            in header
        )
        assert "Vec3* __thiscall request_object_facequad_normals(Object* object);" in header
        assert (
            "void __thiscall request_object_facequads("
            "Object* object, int32_t facequad_count);"
        ) in header
        assert (
            "int32_t __thiscall calc_object_facequad_normals_simple(Object* object);"
            in header
        )
        assert "void __thiscall request_object_texture_groups(" in header
        assert (
            "void __thiscall request_object_edges("
            "Object* object, int32_t edge_count);"
        ) in header


def test_backdrop_quad_helper_replay_keeps_object_owners_and_void_abis() -> None:
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

    for function_name in (
        "initialize_textured_backdrop_quad",
        "raise_backdrop_quad_edge_pair",
        "initialize_backdrop_slice_quad",
        "initialize_backdrop_corner_quad",
        "initialize_backdrop_tile_quad",
        "rotate_object_facequad_uv_pairs",
    ):
        assert f'"{function_name}"' in binja_sync
        assert f'"{function_name}"' in ida_sync
        for header in analysis_headers:
            assert function_name in header

    for prototype in (
        "void __cdecl raise_backdrop_quad_edge_pair(int32_t selector, Object* object)",
        "void __cdecl initialize_backdrop_corner_quad(int32_t selector, Object* object, char* texture_path)",
        "void __thiscall rotate_object_facequad_uv_pairs(ObjectFaceQuad* quad)",
    ):
        assert prototype in binja_sync
        assert prototype + ";" in ida_sync

    for header in analysis_headers:
        assert (
            "void __thiscall rotate_object_facequad_uv_pairs("
            "ObjectFaceQuad* quad);"
        ) in header

    for address, name, data_type in (
        ("0x4a3c40", "g_backdrop_raise_first_vertex_index", "int32_t"),
        ("0x4a3c44", "g_backdrop_raise_second_vertex_index", "int32_t"),
        ("0x4a3ce0", "g_backdrop_corner_vertex_indices", "int32_t[4]"),
    ):
        assert f'("{address}", "{name}")' in binja_sync
        assert f'("{address}", "{data_type}")' in binja_sync
        for header in analysis_headers:
            assert name in header

    assert 're.sub(r"\\s*\\[\\s*", "[", normalized)' in ida_sync
    assert 're.sub(r"\\s*\\]\\s*", "]", normalized)' in ida_sync


def test_object_policy_flags_keep_producers_and_consumers_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_object_render_types.py").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/object_render_types.h"
    ).read_text(encoding="utf-8")
    analysis_headers = [
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bn_object_render_types.h", "object_render_types.h")
    ]

    object_flags = (
        "OBJECT_FLAG_BUILD_TOON_EDGES = 0x00000001",
        "OBJECT_FLAG_REFRESH_TINT_EACH_DRAW = 0x00000010",
        "OBJECT_FLAG_TINT_DIRTY = 0x00000040",
    )
    edge_flags = (
        "OBJECT_TOON_EDGE_FLAG_BOUNDARY = 0x1",
        "OBJECT_TOON_EDGE_FLAG_SHARED = 0x2",
    )
    for header in (matcher_header, *analysis_headers):
        for declaration in (*object_flags, *edge_flags):
            assert declaration in header
    for header in analysis_headers:
        assert "ObjectToonEdgeFlag flags;" in header
        assert (
            "void __cdecl render_object_toon(\n"
            "    Object* object, TransformMatrix* matrix);"
        ) in header

    assert (
        "void __cdecl render_object_toon(Object* object, "
        "TransformMatrix* matrix)"
    ) in binja_sync
    assert (
        "void __cdecl render_object_toon(Object* object, "
        "TransformMatrix* matrix);"
    ) in ida_sync
    assert (
        "void __cdecl render_object(Object* object, TransformMatrix* matrix, "
        "float texture_u, float texture_v, tColour* color, char after_sprites)"
    ) in binja_sync
    assert (
        "void __cdecl render_object(Object* object, TransformMatrix* matrix, "
        "float texture_u, float texture_v, tColour* color, char after_sprites);"
    ) in ida_sync

    scratch_root = repo_root / "tools/match/scratches"
    sources = {
        name: (scratch_root / name / "scratch.cpp").read_text(encoding="utf-8")
        for name in (
            "add_object_edge",
            "apply_object_toon",
            "build_track_fringe_mesh",
            "calc_object_edges",
            "initialize_font3d_objects",
            "render_object",
            "render_object_toon",
            "update_intro_logo_renderable",
        )
    }
    assert "OBJECT_FLAG_BUILD_TOON_EDGES" in sources["apply_object_toon"]
    assert "OBJECT_FLAG_BUILD_TOON_EDGES" in sources["calc_object_edges"]
    assert "OBJECT_TOON_EDGE_FLAG_SHARED" in sources["add_object_edge"]
    for name in ("add_object_edge", "calc_object_edges", "render_object_toon"):
        assert "OBJECT_TOON_EDGE_FLAG_BOUNDARY" in sources[name]
    assert "OBJECT_FLAG_TINT_DIRTY" in sources["build_track_fringe_mesh"]
    assert "OBJECT_FLAG_TINT_DIRTY" in sources["render_object"]
    for name in (
        "initialize_font3d_objects",
        "render_object",
        "update_intro_logo_renderable",
    ):
        assert "OBJECT_FLAG_REFRESH_TINT_EACH_DRAW" in sources[name]

    assert "OBJECT_FLAG_TOON_ENABLED | 1" not in sources["apply_object_toon"]
    assert "flags & 0x50" not in sources["render_object"]
    assert "flags &= ~0x40" not in sources["render_object"]


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
        "sort_object_faces_by_texture_group",
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
        "void __cdecl sort_object_faces_by_texture_group(Object* object)"
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
    assert (
        '"void __thiscall copy_object_vertices(Object* object);"'
    ) in ida_sync_source
    assert (
        '"void __fastcall request_object_vertex_colours(Object* object);"'
    ) in ida_sync_source
    for address, function_name in (
        ("0x42F790", "copy_object_vertices"),
        ("0x42F850", "request_object_vertex_colours"),
    ):
        assert f'({address}, "{function_name}")' in ida_sync_source
    assert (
        '"int32_t __cdecl get_or_append_object_texture_group_vertex(Object* object, '
        'int vertex_index, float u, float v);"'
    ) in ida_sync_source
    assert (
        '"void __cdecl sort_object_faces_by_texture_group(Object* object);"'
    ) in ida_sync_source
    assert '"ObjectGroupedVertex": 0x1C' in ida_sync_source
    assert 're.sub(r"\\(void\\)$", "()", normalized)' in ida_sync_source
    for header in analysis_headers:
        assert "typedef struct ObjectRenderVertex" in header
        assert "void __thiscall copy_object_vertices(Object* object);" in header
        assert (
            "void __fastcall request_object_vertex_colours(Object* object);"
            in header
        )
        assert "ObjectDistort* distort, Object* object);" in header
        assert "void __thiscall replace_object_list_texture_refs(" in header
        assert "extern int32_t g_object_grouped_vertex_cursor;" in header
        assert "extern ObjectGroupedVertex* g_object_grouped_vertex_scratch;" in header
        assert "void __cdecl sort_object_faces_by_texture_group(Object* object);" in header

    assert "int get_or_append_object_texture_group_vertex(" in matcher_header
    assert "void sort_object_faces_by_texture_group(Object* object);" in matcher_header
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

    for owner_name, expected_size in (
        ("ObjectRenderBuffers", "0xC"),
        ("ObjectIndexBuffer", "0x4"),
        ("VertexBufferFactory", "0x8CA4"),
        ("IndexBufferFactory", "0x2EE4"),
        ("Direct3DRenderer", "0xBCC0"),
    ):
        assert f'"{owner_name}": {expected_size}' in ida_sync

    assert "BUFFER_FACTORY_LVAR_SPECS" in ida_sync
    for selector, definition_address, expected_name in (
        ("create_vertex_buffer", "0x4115A8", "next_count"),
        ("create_index_buffer", "0x4115F9", "next_count"),
    ):
        assert (
            f'("{selector}", {definition_address}, "{expected_name}"'
            in ida_sync
        )

    for address in (
        "0x4114B0",
        "0x4115D0",
        "0x411630",
        "0x4116F0",
        "0x411700",
        "0x411730",
        "0x4118B0",
        "0x411960",
        "0x411D70",
        "0x4129C0",
        "0x4129F0",
        "0x412D00",
        "0x412E50",
        "0x413030",
        "0x413520",
        "0x414260",
        "0x414270",
        "0x4143C0",
        "0x414500",
        "0x414600",
        "0x414650",
        "0x418B50",
        "0x433060",
    ):
        assert address in ida_sync

    assert '"ObjectRenderVertex": 0x18' in ida_sync
    assert '"ImmediateQuadVertexBlock": 0x60' in ida_sync
    assert "IMMEDIATE_QUAD_LVAR_SPECS" in ida_sync
    assert '"draw_textured_quad_immediate"' in ida_sync
    assert "0x41308C" in ida_sync
    assert '"quad"' in ida_sync
    assert '"ImmediateQuadVertexBlock *quad;"' in ida_sync
    assert '"immediate_quad_lvars": immediate_quad_lvars' in ida_sync

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
        assert "typedef struct ImmediateQuadVertexBlock" in header
        assert "ObjectRenderVertex vertices[4];" in header
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


def test_backdrop_tile_vertex_cursor_stays_borrowed_and_guarded() -> None:
    repo_root = Path(__file__).parents[1]
    headers = [
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("bn_object_render_types.h", "object_render_types.h")
    ]
    binja_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_object_render_types.py").read_text(
        encoding="utf-8"
    )
    matcher_source = (
        repo_root
        / "tools/match/scratches/initialize_backdrop_tile_quad/scratch.cpp"
    ).read_text(encoding="utf-8")

    for header in headers:
        for marker in (
            "#define __ptr_offset(offset)",
            "typedef struct __ptr_offset(0x08) BackdropTileVertexCursorView {",
            "BackdropTileVertexCursorView_must_be_0x0c",
            "Object::vertices remains",
            "the sole owner of the four-record allocation.",
        ):
            assert marker in header

    assert "BackdropTileVertexCursorView" not in matcher_source
    assert "BACKDROP_TILE_VERTEX_CURSOR_USER_VAR_UPDATES" in binja_sync
    expected_binja_lvar = (
        '        "initialize_backdrop_tile_quad",\n'
        '        "RegisterVariableSourceType",\n'
        "        458,\n"
        "        67,\n"
        '        "vertex_z_cursor",\n'
        '        "BackdropTileVertexCursorView*"'
    )
    assert expected_binja_lvar in binja_sync
    assert "verify_backdrop_tile_vertex_cursor" in binja_sync
    assert "current_type_widths" in binja_sync
    assert "current_struct_fields_batch" in binja_sync

    assert '"BackdropTileVertexCursorView": 0xC' in ida_sync
    assert "BACKDROP_TILE_VERTEX_LVAR_SPECS" in ida_sync
    assert "0x41A69B" in ida_sync
    assert (
        '"float *__shifted(BackdropTileVertexCursorView, 0x08) "'
        in ida_sync
    )
    assert '"vertex_z_cursor;"' in ida_sync
    assert (
        '"backdrop_tile_vertex_lvars": backdrop_tile_vertex_lvars'
        in ida_sync
    )


def test_object_distort_vertex_cursors_stay_borrowed_and_guarded() -> None:
    repo_root = Path(__file__).parents[1]
    headers = [
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("bn_object_render_types.h", "object_render_types.h")
    ]
    binja_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_object_render_types.py").read_text(
        encoding="utf-8"
    )
    matcher_source = (
        repo_root
        / "tools/match/scratches/apply_distort_to_object/scratch.cpp"
    ).read_text(encoding="utf-8")

    for header in headers:
        for marker in (
            "typedef struct __ptr_offset(0x08) ObjectVertexZCursorView {",
            "ObjectVertexZCursorView_must_be_0x0c",
            "Object::vertices and",
            "Object::copied_vertices remain the storage owners.",
        ):
            assert marker in header

    assert "ObjectVertexZCursorView" not in matcher_source
    assert "OBJECT_DISTORT_VERTEX_CURSOR_USER_VAR_UPDATES" in binja_sync
    for index, storage, name in (
        (177, 69, "z_wave_source_cursor"),
        (562, 67, "xyz_scale_source_cursor"),
    ):
        expected_binja_lvar = (
            '        "apply_distort_to_object",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            '        "ObjectVertexZCursorView*"'
        )
        assert expected_binja_lvar in binja_sync
    assert "verify_object_distort_vertex_cursors" in binja_sync
    assert "y_squash_source_cursor" not in binja_sync

    assert '"ObjectVertexZCursorView": 0xC' in ida_sync
    assert "OBJECT_DISTORT_VERTEX_LVAR_SPECS" in ida_sync
    for definition_address, name in (
        ("0x41AB02", "z_wave_source_cursor"),
        ("0x41ABE0", "y_squash_source_cursor"),
        ("0x41AC83", "xyz_scale_source_cursor"),
    ):
        assert definition_address in ida_sync
        assert f'"{name}"' in ida_sync
        assert (
            '"float *__shifted(ObjectVertexZCursorView, 0x08) "'
            in ida_sync
        )
        assert f'"{name};"' in ida_sync
    assert (
        '"object_distort_vertex_lvars": object_distort_vertex_lvars'
        in ida_sync
    )


def test_vertex_buffer_factory_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_vertex_buffer_factory_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("ObjectRenderBuffers", "0x0C"),
        ("VertexBufferFactory", "0x8CA4"),
        ("Direct3DRenderer", "0xBCC0"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("ObjectRenderBuffers", "0x08", "vertex_buffer", "ObjectVertexBuffer*"),
        ("VertexBufferFactory", "0x04", "buffers", "ObjectRenderBuffers[3000]"),
        ("Direct3DRenderer", "0xBB94", "device", "Direct3DDevice8*"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for index, storage, name in (
        (80, 73, "create_result"),
        (247, 68, "next_count"),
    ):
        expected = (
            '        "create_vertex_buffer",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            '        "int32_t"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay


def test_render_camera_replay_owns_pipeline_without_splitting_device_alias() -> None:
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

    camera_prototype = (
        "void __cdecl render_camera(float viewport_x, float viewport_y, "
        "float viewport_width, float viewport_height, float fov_degrees, "
        "TransformMatrix* camera_matrix, TransformMatrix* view_matrix, "
        "char draw_world, char post_sprite_pass)"
    )
    projection_prototype = (
        "TransformMatrix* __stdcall build_perspective_projection_matrix("
        "TransformMatrix* matrix, float vertical_fov_radians, float aspect_ratio, "
        "float near_z, float far_z)"
    )
    view_prototype = (
        "TransformMatrix* __stdcall build_camera_view_matrix(TransformMatrix* matrix, "
        "const Vec3* eye, const Vec3* target, const Vec3* up)"
    )
    for source in (binja_sync, ida_sync):
        assert camera_prototype in source
        assert projection_prototype in source
        assert view_prototype in source
        assert "render_camera" in source
        assert "0X411FA0" in source.upper()

    for address, stale_delta, target_delta, call_name in (
        ("0x41201E", 12, 8, "SetViewport"),
        ("0x412229", 8, 12, "SetRenderState"),
    ):
        assert address in ida_sync
        assert f'({address}, {stale_delta}, {target_delta}, "{call_name}")' in ida_sync
    assert "_sync_render_camera_stack_points()" in ida_sync
    assert "unexpected_stack_point_delta" in ida_sync

    pipeline_globals = (
        ("0x50316c", "g_render_projection_param_b", "float"),
        ("0x5031b8", "g_render_camera_source_matrix", "TransformMatrix*"),
        ("0x5031cc", "g_render_projection_near_z", "float"),
        ("0x5031d0", "g_render_projection_far_z", "float"),
        ("0x5031d4", "g_render_projection_param_a", "float"),
        ("0x503218", "g_render_camera_view_matrix", "TransformMatrix*"),
        ("0x503260", "g_object_render_pass_filter", "uint8_t"),
    )
    for address, name, data_type in pipeline_globals:
        assert f'("{address}", "{name}")' in binja_sync
        assert f'("{address}", "{data_type}")' in binja_sync
        assert f'(0x{int(address, 0):X}, "{name}")' in ida_sync
        for header in analysis_headers:
            assert name in header

    for header in analysis_headers:
        assert "void __cdecl render_camera(" in header
        assert (
            "TransformMatrix* __stdcall build_perspective_projection_matrix("
            in header
        )
        assert "TransformMatrix* __stdcall build_camera_view_matrix(" in header
        assert "extern Direct3DDevice8* g_d3d_device;" not in header

    assert '("0x502fec",' not in binja_sync
    assert '(0x502FEC,' not in ida_sync

    references = json.loads(
        (repo_root / "analysis/symbols/gameplay-references.json").read_text(
            encoding="utf-8"
        )
    )
    aliases_by_address = {
        entry["address"]: set(entry.get("aliases", []))
        for entry in references["symbols"]
    }
    for address, alias in (
        ("0x5031b8", "G0Camera"),
        ("0x503218", "G0CameraInv"),
        ("0x503260", "G0AfterSprites"),
        ("0x503174", "gBindTextureRefLast"),
        ("0x5031c0", "gBindCount"),
    ):
        assert alias in aliases_by_address[address]

    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    entries_by_address = {
        entry["address"]: entry for entry in crosswalk["entries"]
    }
    for address, symbol in (
        ("0x411fa0", "G0RenderCamera("),
        ("0x4123e0", "G0RenderToon("),
        ("0x4126c0", "G0RenderObject("),
        ("0x414500", "G0BindTexture("),
    ):
        assert entries_by_address[address]["android_symbol"].startswith(symbol)
        assert entries_by_address[address]["ios_symbol"].startswith(symbol)

    functions = json.loads(
        (repo_root / "analysis/symbols/gameplay-functions.json").read_text(
            encoding="utf-8"
        )
    )
    functions_by_address = {
        entry["address"]: entry for entry in functions["functions"]
    }
    for address, alias in (
        ("0x411fa0", "G0RenderCamera"),
        ("0x4123e0", "G0RenderToon"),
        ("0x4126c0", "G0RenderObject"),
        ("0x414500", "G0BindTexture"),
    ):
        assert alias in functions_by_address[address]["aliases"]


def test_main_loop_replay_keeps_winmain_and_byte_fullscreen_abis() -> None:
    repo_root = Path(__file__).parents[1]
    main_header = (HEADER_DIR / "main_loop_types.h").read_text(encoding="utf-8")
    binja_main_sync = (BINJA_DIR / "sync_main_loop_types.py").read_text(
        encoding="utf-8"
    )
    ida_main_sync = (IDA_DIR / "apply_main_loop_types.py").read_text(
        encoding="utf-8"
    )
    object_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("bn_object_render_types.h", "object_render_types.h")
    )
    binja_object_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    ida_object_sync = (IDA_DIR / "apply_object_render_types.py").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/direct3d_renderer.h"
    ).read_text(encoding="utf-8")
    wrapper_scratch = (
        repo_root / "tools/match/scratches/set_fullscreen_mode/scratch.cpp"
    ).read_text(encoding="utf-8")
    renderer_scratch = (
        repo_root
        / "tools/match/scratches/direct3d_renderer_set_fullscreen_mode/scratch.cpp"
    ).read_text(encoding="utf-8")

    assert "int __stdcall game_startup_and_main_loop(" in main_header
    for argument in (
        "HINSTANCE hInstance",
        "HINSTANCE hPrevInstance",
        "LPSTR lpCmdLine",
        "int nShowCmd",
    ):
        assert argument in main_header
    for argument in (
        "void *hInstance",
        "void *hPrevInstance",
        "char *lpCmdLine",
        "int nShowCmd",
    ):
        assert argument in ida_main_sync
    assert "int32_t __stdcall game_startup_and_main_loop(" in binja_main_sync
    assert "LPSTR lpCmdLine, int32_t nShowCmd" in binja_main_sync
    assert '("0x4dfad8", "g_application_instance")' in binja_main_sync
    assert '("0x4dfad0", "int32_t[2]")' in binja_main_sync
    assert "_sync_application_instance_boundary" in ida_main_sync
    assert '"int g_mouse_wheel_delta[2];"' in ida_main_sync
    assert '"void *g_application_instance;"' in ida_main_sync
    assert "saved_lvar_overrides" in (
        IDA_DIR / "inspect_function_lvars.py"
    ).read_text(encoding="utf-8")
    assert "types_declare_if_changed" in binja_object_sync
    assert "types_declare(" not in binja_object_sync

    for source in (binja_object_sync, ida_object_sync, *object_headers):
        assert "set_fullscreen_mode(uint8_t enabled)" in source
        assert "direct3d_renderer_set_fullscreen_mode(" in source
        assert "Direct3DRenderer* renderer, uint8_t enabled)" in source.replace(
            "\n", " "
        )

    assert "direct3d_renderer_set_fullscreen_mode(char enabled)" in matcher_header
    assert "void set_fullscreen_mode(char enabled)" in wrapper_scratch
    assert (
        "void Direct3DRenderer::direct3d_renderer_set_fullscreen_mode(char enabled)"
        in renderer_scratch
    )


def test_main_loop_replay_recovers_process_scalar_boundaries() -> None:
    main_header = (HEADER_DIR / "main_loop_types.h").read_text(encoding="utf-8")
    binja_sync = (BINJA_DIR / "sync_main_loop_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_main_loop_types.py").read_text(
        encoding="utf-8"
    )

    scalar_globals = (
        ("0x4b7230", "g_right_mouse_button_latch", "uint8_t[2]"),
        ("0x4b7234", "g_left_mouse_button_state", "uint8_t[2]"),
        ("0x4b7236", "g_render_queue_active", "uint8_t"),
        ("0x4b7638", "g_mean_update_steps_per_frame", "float"),
        ("0x4b763c", "g_current_frame_update_steps", "float"),
        ("0x4b7640", "g_right_mouse_button_state", "uint8_t[2]"),
        ("0x4b7644", "g_estimated_texture_vram_bytes", "int32_t"),
        ("0x4b7654", "g_window_deactivated", "uint8_t"),
        ("0x4b7758", "g_fixed_update_abort_requested", "uint8_t"),
        ("0x4b7759", "g_frame_render_requested", "uint8_t"),
        ("0x4b775c", "g_current_display_height", "int32_t"),
        ("0x4b7760", "g_authored_view_height", "float"),
        ("0x4b7764", "g_left_mouse_button_latch", "uint8_t[2]"),
        ("0x4b7768", "g_main_loop_frame_count", "float"),
        ("0x4df858", "g_current_display_width", "int32_t"),
        ("0x4df85c", "g_authored_view_width", "float"),
        ("0x4df860", "g_pending_window_deactivate", "int32_t"),
        ("0x4df864", "g_main_loop_exit_requested", "uint8_t"),
        ("0x4df90c", "g_game_initialization_pending", "uint8_t"),
        ("0x4dfafc", "g_frame_time_accumulator", "float"),
        ("0x4dfb00", "g_previous_frame_timestamp_seconds", "float"),
        ("0x4dfb04", "g_current_frame_timestamp_seconds", "float"),
    )
    for address, name, data_type in scalar_globals:
        assert f'("{address}", "{name}")' in binja_sync
        assert f'("{address}", "{data_type}")' in binja_sync
        assert name in main_header
        assert name in ida_sync
        assert f"0x{int(address, 0):X}" in ida_sync

    assert "int* __cdecl read_current_display_resolution(" in main_header
    assert (
        "int32_t* __cdecl read_current_display_resolution("
        in binja_sync
    )
    assert "int *__cdecl read_current_display_resolution(" in ida_sync

    for side in ("left", "right"):
        function_name = f"read_{side}_mouse_button_state"
        assert (
            f"unsigned char __cdecl {function_name}(int slot);"
            in main_header
        )
        assert (
            f"uint8_t __cdecl {function_name}(int32_t slot)"
            in binja_sync
        )
        assert (
            f"unsigned char __cdecl {function_name}(int slot);"
            in ida_sync
        )

    assert "CURRENT_FRAME_UPDATE_SPLIT_ITEMS" in ida_sync
    assert '"float[3]"' in ida_sync
    assert "unexpected_current_frame_update_boundary" in ida_sync
    assert "MOUSE_BUTTON_DATA_ITEMS" in ida_sync
    assert "unexpected_mouse_button_boundary" in ida_sync
    assert "mouse_button_array_verification_failed" in ida_sync
    assert '"uint8_t g_right_mouse_button_state[2];"' in ida_sync
    assert '"int g_estimated_texture_vram_bytes;"' in ida_sync
    assert "WIDENED_SCALAR_DATA_ITEMS" in ida_sync
    assert "unexpected_widened_scalar_boundary" in ida_sync
    assert "ida_bytes.is_unknown" in ida_sync
    assert "ida_bytes.create_float" in ida_sync


def test_win32_window_state_replay_recovers_exact_owners_and_stack_records() -> None:
    header = (
        HEADER_DIR / "win32_window_state_types.h"
    ).read_text(encoding="utf-8")
    binja_sync = (
        BINJA_DIR / "sync_win32_window_state_types.py"
    ).read_text(encoding="utf-8")
    ida_sync = (
        IDA_DIR / "apply_win32_window_state_types.py"
    ).read_text(encoding="utf-8")
    ida_runner = (
        IDA_DIR / "sync_win32_window_state_types.py"
    ).read_text(encoding="utf-8")

    for owner, extent in (
        ("Rect", "0x10"),
        ("WndClassA", "0x28"),
        ("DevModeA", "0x9c"),
    ):
        assert f"{owner}_must_be_{extent}" in header
        assert owner in ida_sync

    data_owners = (
        ("0x4b776c", "g_controller_count_view", "int32_t"),
        ("0x4dfaec", "g_main_window_dc", "HDC"),
        ("0x4dfaf0", "g_main_window", "HWND"),
        ("0x4dfaf4", "g_fullscreen_active", "uint8_t"),
        ("0x4dfaf8", "g_bass_window", "HWND"),
        ("0x503268", "g_saved_window_rect", "RECT"),
        ("0x503278", "g_saved_window_rect_valid", "uint8_t"),
        ("0x50327c", "g_game_window_instance", "HINSTANCE"),
    )
    for address, name, data_type in data_owners:
        assert f'("{address}", "{name}")' in binja_sync
        assert f'("{address}", "{data_type}")' in binja_sync
        assert f"0x{int(address, 0):X}" in ida_sync
        assert name in header
        assert name in ida_sync

    for definition_address, stack_offset, target_name, target_type in (
        ("0x411B62", 80, "window_rect", "Rect"),
        ("0x411A7F", 96, "window_class", "WndClassA"),
        ("0x411B21", 136, "display_mode", "DevModeA"),
    ):
        assert definition_address in ida_sync
        assert f'"stack_offset": {stack_offset}' in ida_sync
        assert target_name in ida_sync
        assert target_type in ida_sync

    assert "(0x4DFAF5, 0x4DFAF8)" in ida_sync
    assert "(0x503279, 0x50327C)" in ida_sync
    assert "unexpected_window_owner_boundary" in ida_sync
    assert "window_owner_crosses_checked_extent" in ida_sync
    assert "unexpected_window_owner_interior_names" in ida_sync
    assert "_sync_data_item(spec, apply=False)" in ida_sync
    assert "_sync_data_item(spec, apply=True)" in ida_sync
    assert "data_item_preflight" in ida_sync
    assert "AnimationDispatchState" in ida_sync
    assert "DEPENDENT_FUNCTIONS = (" in binja_sync
    assert binja_sync.count('"direct3d_renderer_set_fullscreen_mode"') == 1
    assert binja_sync.count('"initialize_game_window_and_input"') >= 2
    assert "game_startup_and_main_loop" not in binja_sync
    assert "apply_win32_window_state_types.py" in ida_runner


def test_display_mode_replay_recovers_only_the_proven_owner_prefix() -> None:
    repo_root = Path(__file__).parents[1]
    analysis_header = (
        HEADER_DIR / "display_mode_types.h"
    ).read_text(encoding="utf-8")
    matcher_header = (
        repo_root / "tools/match/include/display_mode_state.h"
    ).read_text(encoding="utf-8")
    binja_sync = (
        BINJA_DIR / "sync_display_mode_types.py"
    ).read_text(encoding="utf-8")
    ida_sync = (
        IDA_DIR / "apply_display_mode_types.py"
    ).read_text(encoding="utf-8")
    ida_runner = (
        IDA_DIR / "sync_display_mode_types.py"
    ).read_text(encoding="utf-8")
    references = (
        repo_root / "analysis/symbols/gameplay-references.json"
    ).read_text(encoding="utf-8")

    for source in (analysis_header, matcher_header):
        assert "DisplayModeRecord" in source
        assert "DisplayModeViewSample" in source
        assert "DisplayModeState" in source
        assert "view_samples[1]" in source
        assert "DisplayModeState_minimum_prefix_must_be_0x1c" in source
        assert "view_samples[14]" not in source

    for source in (binja_sync, ida_sync):
        for function_name in (
            "initialize_main_loop_display_state",
            "clear_display_mode_state",
            "reset_display_mode_probe_count",
            "read_next_display_mode_view_sample",
            "update_display_mode_view_state",
            "render_game_frame_scene",
            "get_authored_view_width",
            "get_authored_view_height",
        ):
            assert function_name in source
        normalized_source = source.replace(
            "DisplayModeState *state",
            "DisplayModeState* state",
        )
        assert "DisplayModeState* state" in normalized_source
        assert "DisplayModeState" in source

    assert '("0x4df9e0", "g_display_mode_state")' in binja_sync
    assert '("0x4df9e0", "DisplayModeState")' in binja_sync
    assert "DISPLAY_MODE_STATE_MINIMUM_SIZE = 0x1C" in ida_sync
    assert "NEXT_KNOWN_OWNER_ADDRESS = 0x4DFAD0" in ida_sync
    assert "display_mode_state_minimum_extent_conflict" in ida_sync
    assert "unexpected_existing_display_mode_state_owner" in ida_sync
    assert "unclaimed_tail_boundary_verification_failed" in ida_sync
    assert '"_DWORD[60]"' in ida_sync
    assert "unclaimed_tail_start" in ida_sync
    assert "UPDATE_SAMPLE_LVAR_SPECS" in ida_sync
    for stack_offset, sample_name in (
        (24, "y"),
        (28, "height"),
        (32, "width"),
        (36, "x"),
    ):
        assert f'"{sample_name}", "float {sample_name};", 0x41297C, {stack_offset}' in ida_sync
    assert "unexpected_sample_lvar_candidates" in ida_sync
    assert "sample_lvar_readback_failed" in ida_sync
    assert (
        'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/display_mode_types.h"'
        in ida_runner
    )
    assert "remaining tail capacity" in references
    assert '"size": "0xf0"' not in references[
        references.index('"address": "0x4df9e0"'):
        references.index('"address": "0x4dfad0"')
    ]


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


def test_movie_ownership_stays_aligned_across_replay_lanes() -> None:
    repo_root = Path(__file__).parents[1]
    binja_object_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    ida_object_sync = (IDA_DIR / "apply_object_render_types.py").read_text(
        encoding="utf-8"
    )
    binja_path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = (
        (HEADER_DIR / "bn_object_render_types.h").read_text(encoding="utf-8"),
        (HEADER_DIR / "object_render_types.h").read_text(encoding="utf-8"),
    )
    path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/movie.h"
    ).read_text(encoding="utf-8")

    assert "MOVIE_FIELDS = (" in binja_object_sync
    assert '("0x00", "object", "Object")' in binja_object_sync
    assert '("0xec", "current_texture_ref", "TextureRef*")' in binja_object_sync
    for source in (
        binja_object_sync,
        ida_object_sync,
        binja_path_sync,
        ida_path_sync,
    ):
        assert "advance_frame_sequence" in source
        assert "Movie* movie" in source
    for source in (binja_path_sync, ida_path_sync):
        assert "update_smtracks" in source
        assert "Face* face" in source
        assert "sample_smtrack_heightmap" in source
        assert "TextureRef* replacement" in source
        assert "bool cubic" in source
    assert '("0x38", "movie", "Movie")' in binja_path_sync
    assert '"Movie",' in binja_path_sync
    assert "def _sync_face_movie_owner()" in ida_path_sync
    assert 'ida_typeinf.udm_t("movie", "Movie", 0x38 * 8)' in ida_path_sync

    for header in (*analysis_headers, path_header, matcher_header):
        assert "MOVIE_COMPLETE = 0x01" in header
        assert "MOVIE_LOOP = 0x02" in header
        assert "MOVIE_PING_PONG = 0x04" in header
        assert "MOVIE_REVERSE = 0x08" in header
        assert "MOVIE_PAUSED = 0x10" in header
    for header in analysis_headers:
        assert "typedef struct Movie" in header
        assert "Object object;" in header
        assert "TextureRef* current_texture_ref;" in header
        assert "int32_t heightmap_sample_count;" in header
        assert "float heightmap_sample_divisor;" in header
        assert "float heightmap_sample_scale;" in header
    assert '("0x1c", "heightmap_sample_count", "int32_t")' in binja_object_sync
    assert '("0x24", "heightmap_sample_divisor", "float")' in binja_object_sync
    assert '("0x28", "heightmap_sample_scale", "float")' in binja_object_sync
    assert "typedef struct MovieObjectView" in path_header
    assert "ObjectFaceQuad* facequads;" in path_header
    assert "MovieObjectView object;" in path_header
    assert "TextureRef* current_texture_ref;" in path_header
    assert "uint8_t _storage[0xf0];" not in path_header
    assert "FrameSequence" not in path_header
    assert "FrameSequence" not in matcher_header


def test_smtrack_heightmap_replay_preserves_borrowed_image_and_sample_cursors() -> None:
    replay = (
        BINJA_DIR / "sync_smtrack_heightmap_lifetimes.py"
    ).read_text(encoding="utf-8")
    health = (
        Path(__file__).parents[1] / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    for type_name, width in (
        ("TgaImageView", "0x14"),
        ("TextureRef", "0xA4"),
        ("Vec3", "0x0C"),
        ("Object", "0xDC"),
    ):
        assert f'"{type_name}": {width}' in replay

    for offset, field_name, field_type in (
        ("0x0C", "width", "uint16_t"),
        ("0x0E", "height", "uint16_t"),
        ("0x10", "bits_per_pixel", "uint8_t"),
        ("0x12", "pixels", "uint8_t[1]"),
        ("0x98", "texture_ref", "void*"),
        ("0x38", "vertices", "Vec3*"),
    ):
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for index, storage, name, variable_type in (
        (14, 72, "image", "TgaImageView*"),
        (84, 71, "sample_cursor", "Vec3*"),
    ):
        expected = (
            '        "sample_smtrack_heightmap",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert expected in replay

    for required in (
        "struct TgaImageView* image = replacement->texture_ref",
        "image->width",
        "image->height",
        "image->bits_per_pixel",
        "struct Vec3* sample_cursor = source_1->vertices",
        "sample_cursor = &sample_cursor[1]",
        "void* texture_ref",
        "struct Vec3* vertices =",
    ):
        assert required in health


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
    matcher_tile_ids = (
        repo_root / "tools/match/include/sub_loc_tile_ids.h"
    ).read_text(encoding="utf-8")
    tile_view_header = (
        repo_root / "tools/match/include/track_row_cell_tile_views.h"
    ).read_text(encoding="utf-8")

    assert '("0x3c", "tile_id", "SubLocTileId")' in binja_source
    assert '("0x3d", "open_edge_mask", "uint8_t")' in binja_source
    assert '"SubLocOpenEdgeFlag",' in binja_source
    assert '"SubLocTileId",' in binja_source
    assert '"SubLocFlag",' in binja_source
    ida_path_sync = (
        repo_root / "tools/ida/apply_path_template_types.py"
    ).read_text(encoding="utf-8")
    assert "track_row_cell_tile_owner" in ida_path_sync
    assert '"selector": "TrackRowCell.tile_id"' in ida_path_sync
    assert '"type": "SubLocTileId"' in ida_path_sync
    for header in (analysis_header, matcher_tile_ids):
        assert "typedef" in header and "SubLocTileId;" in header
        assert "SUBLOC_TILE_EMPTY = 0x00" in header
        assert "SUBLOC_TILE_WALL2 = 0x0e" in header
        assert "SUBLOC_TILE_TRAMPOLINE = 0x16" in header
        assert "SUBLOC_TILE_PATH_ENTRY_UPPERCASE = 0x1e" in header
        assert "SUBLOC_TILE_SALT_HAZARD = 0x22" in header
        assert "SUBLOC_TILE_RING_MARKER = 0x23" in header

    assert "typedef enum SubLocTileId : uint8_t" in analysis_header
    assert "enum SubLocTileIdValue" in matcher_tile_ids

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
        assert "SubLocTileId tile_id;" in header
        assert "_pad_3e" in header
        assert "open_edge_mask" in header
        assert "tile_flags_3d" not in header

    assert "SubLocTileId tile_id" in tile_view_header
    assert "_pad_02" in tile_view_header
    assert "open_edge_mask" in tile_view_header
    assert "tile_flags_3d" not in tile_view_header


def test_sub_loc_runtime_row_owner_replay_stays_guarded() -> None:
    repo_root = Path(__file__).parents[1]
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/subgame_runtime.h"
    ).read_text(encoding="utf-8")
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    health_checks = {
        check["name"]: check
        for check in json.loads(
            (repo_root / "analysis/decompile/health_checks.json").read_text(
                encoding="utf-8"
            )
        )["checks"]
    }

    assert "typedef struct GameRootRuntimeRowStrideAnchor {" in analysis_header
    assert "uint8_t root_prefix[0x6410e0];" in analysis_header
    assert "} GameRootRuntimeRowStrideAnchor;" in analysis_header
    assert "solely" in analysis_header
    assert "GameRootRuntimeRowStrideAnchor" not in matcher_header

    assert "REMOVE_SUB_LOC_RUNTIME_ROW_OFFSET_OPERANDS" in ida_sync
    for operand_spec in (
        "(0x439BF0, 1, 0x6410E0)",
        "(0x439BFF, 1, 0x641194)",
        "(0x439C0A, 1, 0x641194)",
        "(0x439C10, 1, 0x641190)",
    ):
        assert operand_spec in ida_sync
    assert "UPDATE_SUB_LOC_RUNTIME_ROW_OFFSET_OPERANDS" in ida_sync
    assert "(0x439FC2, 1, 0x6411B8)" in ida_sync
    for result_name in (
        "remove_sub_loc_runtime_row_offset_operands",
        "update_sub_loc_runtime_row_offset_operands",
    ):
        assert f"{result_name} = _normalize_root_offset_operands(" in ida_sync
        assert f'"{result_name}": {result_name}' in ida_sync

    assert "0x439D50,  # update_sub_loc" in ida_sync
    assert "REMOVE_SUB_LOC_RUNTIME_LVAR_SPECS" in ida_sync
    assert '"GameRootRuntimeRowStrideAnchor *runtime_row_anchor;"' in ida_sync
    assert "0x439BFB" in ida_sync
    assert "_sync_remove_sub_loc_runtime_lvars" in ida_sync
    assert '"remove_sub_loc_runtime_lvars": remove_sub_loc_runtime_lvars' in ida_sync

    ida_remove = health_checks["ida_remove_sub_loc_root_list_owner"]
    for marker in (
        "GameRootRuntimeRowStrideAnchor *runtime_row_anchor",
        "g_game_base->subgame.runtime_rows[v4].flags",
        "runtime_row_anchor->row.attachment_body.bod.list_flags",
        "p_attachment_body = &runtime_row_anchor->row.attachment_body",
    ):
        assert marker in ida_remove["required_substrings"]
    for old_shape in ("unk_6410E0", "unk_641190", "unk_641194", "void **v6"):
        assert old_shape in ida_remove["forbidden_substrings"]

    ida_update = health_checks["ida_update_sub_loc_root_runtime_owner"]
    assert (
        "g_game_base->subgame.runtime_rows[get_track_cell_row_index(cell)].attachment_body.color"
        in ida_update["required_substrings"]
    )
    assert "unk_6411B8" in ida_update["forbidden_substrings"]


def test_level_definition_parser_frame_ownership_stays_aligned() -> None:
    binja_sync = (
        BINJA_DIR / "sync_segment_catalog_types.py"
    ).read_text(encoding="utf-8")
    ida_sync = (IDA_DIR / "apply_segment_catalog_types.py").read_text(
        encoding="utf-8"
    )
    health_checks = {
        check["name"]: check
        for check in json.loads(
            (Path("analysis/decompile/health_checks.json")).read_text(
                encoding="utf-8"
            )
        )["checks"]
    }

    assert "LEVEL_PARSER_USER_VAR_UPDATES" in binja_sync
    assert "LEVEL_SEGMENTS_END_SPLIT_DEFINITIONS" in binja_sync
    assert "LEVEL_SEGMENTS_END_TARGET_VAR" in binja_sync
    assert "apply_split_user_var_update(" in binja_sync
    for definition in (
        '("0x447b72", "mlil", "RegisterVariableSourceType", 1778, 66)',
        '("0x447b77", "mlil", "RegisterVariableSourceType", 1783, 73)',
        '("0x447b7e", "mlil", "StackVariableSourceType", 1790, -1796)',
    ):
        assert definition in binja_sync
    for source_type, index, storage, name, variable_type in (
        ("RegisterVariableSourceType", 182, 71, "level_display_name_begin", "char*"),
        (
            "RegisterVariableSourceType",
            190,
            68,
            "level_display_name_cursor",
            "char*",
        ),
        ("RegisterVariableSourceType", 877, 67, "script_name_cursor", "char*"),
        ("RegisterVariableSourceType", 1867, 67, "segment_name_cursor", "char*"),
        ("RegisterVariableSourceType", 1957, 68, "line_options_cursor", "char*"),
        ("RegisterVariableSourceType", 2461, 68, "sample_name_cursor", "char*"),
        (
            "RegisterVariableSourceType",
            2783,
            67,
            "first_segment_name_cursor",
            "char*",
        ),
        (
            "RegisterVariableSourceType",
            2958,
            67,
            "last_segment_name_cursor",
            "char*",
        ),
        ("StackVariableSourceType", 0, -1804, "line_cursor", "char*"),
        ("StackVariableSourceType", 0, -1800, "parsed_int", "int32_t"),
        ("StackVariableSourceType", 1790, -1796, "segments_end", "char*"),
        ("StackVariableSourceType", 0, -1792, "level_path", "char[512]"),
        ("StackVariableSourceType", 0, -1280, "line_options", "char[128]"),
        ("StackVariableSourceType", 0, -1152, "sample_name", "char[128]"),
        ("StackVariableSourceType", 0, -1024, "segment_name", "char[512]"),
        ("StackVariableSourceType", 0, -512, "script_name", "char[512]"),
    ):
        fragment = (
            '        "load_level_definition_file",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert fragment in binja_sync

    assert "LEVEL_PARSER_LVAR_SPECS" in ida_sync
    for definition_address, stack_offset, name, declaration in (
        ("0x44753F", "None", "level_display_name_cursor", "char *"),
        ("0x4477EE", "None", "script_name_cursor", "char *"),
        ("0x447BCC", "None", "segment_name_cursor", "char *"),
        ("0x447C26", "None", "line_options_cursor", "char *"),
        ("0x447E1E", "None", "sample_name_cursor", "char *"),
        ("0x447F60", "None", "first_segment_name_cursor", "char *"),
        ("0x44800F", "None", "last_segment_name_cursor", "char *"),
        ("0x447C2D", "52", "line_cursor", "char *"),
        ("0x4478A4", "56", "parsed_int", "int32_t"),
        ("0x447B7F", "60", "segments_end", "char *"),
        ("0x4474A4", "64", "level_path", "char level_path[512]"),
        ("0x447C25", "576", "line_options", "char line_options[128]"),
        ("0x447E1D", "704", "sample_name", "char sample_name[128]"),
        ("0x447BCB", "832", "segment_name", "char segment_name[512]"),
        ("0x4477ED", "1344", "script_name", "char script_name[512]"),
    ):
        assert definition_address in ida_sync
        assert f"        {stack_offset}," in ida_sync
        assert f'"{name}"' in ida_sync
        assert declaration in ida_sync
    assert '"level_parser_lvars": level_parser_lvars' in ida_sync
    assert "level_parser_lvar_failures" in ida_sync

    bn_check = health_checks["bn_load_level_definition_owner_graph"]
    for marker in (
        "char* level_display_name_cursor = &tracks->level_display_name",
        "char* script_name_cursor = &script_name",
        "char* segment_name_cursor = &segment_name",
        "char* line_options_cursor = &line_options",
        "char* sample_name_cursor = &sample_name",
        "char* first_segment_name_cursor = &segment_name",
        "char* last_segment_name_cursor = &segment_name",
        "char level_path[0x200]",
        "char line_options[0x80]",
        "char sample_name[0x80]",
    ):
        assert marker in bn_check["required_substrings"]
    for old_shape in (
        "char var_700[0x200]",
        "void var_500",
        "(edx - 0x1a58dc)",
        "char (* ecx_10)[0x200]",
        "char (* ecx_16)[0x200]",
        "char (* edx_15)[0x80]",
        "char (* edx_34)[0x80]",
        "char (* ecx_50)[0x200]",
        "char (* ecx_55)[0x200]",
    ):
        assert old_shape in bn_check["forbidden_substrings"]

    ida_check = health_checks["ida_load_level_definition_owner_graph"]
    for marker in (
        "char *level_display_name_cursor",
        "char *script_name_cursor",
        "char *segment_name_cursor",
        "char *line_options_cursor",
        "char *sample_name_cursor",
        "char *first_segment_name_cursor",
        "char *last_segment_name_cursor",
        "char level_path[512]",
        "char line_options[128]",
        "char sample_name[128]",
    ):
        assert marker in ida_check["required_substrings"]
    for old_shape in (
        "char *v62;",
        "int v63;",
        "char *v64;",
        "char *v21;",
        "char *v38;",
        "char *v48;",
        "char *n;",
        "char *k;",
        "char *m;",
        "char Buffer[512]",
        "char v66[128]",
        "char ArgList[128]",
    ):
        assert old_shape in ida_check["forbidden_substrings"]


def test_segment_copy_borrowed_row_cursors_stay_replayable() -> None:
    repo_root = Path(__file__).parents[1]
    analysis_header = (HEADER_DIR / "segment_catalog_types.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (
        BINJA_DIR / "sync_segment_catalog_types.py"
    ).read_text(encoding="utf-8")
    ida_sync = (IDA_DIR / "apply_segment_catalog_types.py").read_text(
        encoding="utf-8"
    )
    health_checks = {
        check["name"]: check
        for check in json.loads(
            (repo_root / "analysis/decompile/health_checks.json").read_text(
                encoding="utf-8"
            )
        )["checks"]
    }

    for marker in (
        "#define __ptr_offset(offset)",
        (
            "typedef struct __ptr_offset(0x14) "
            "AuthoredSegmentRowObjectIdCursorView {"
        ),
        "AuthoredSegmentRowObjectIdCursorView_must_be_0x38",
        "SegmentCatalogEntry::rows and SubSegment::rows remain the sole owners.",
    ):
        assert marker in analysis_header
    assert (
        '"AuthoredSegmentRowObjectIdCursorView": 0x38'
        in binja_sync
    )
    assert (
        '"AuthoredSegmentRowObjectIdCursorView": 0x38'
        in ida_sync
    )

    assert "SEGMENT_COPY_USER_VAR_UPDATES" in binja_sync
    for index, storage, name, declaration in (
        ("13", "73", "catalog", "SMTracks*"),
        ("19", "72", "catalog_index", "int32_t"),
        ("26", "71", "catalog_filename_cursor", "char*"),
        ("91", "71", "destination_segment", "SubSegment*"),
        ("116", "73", "destination_glyph_row_cursor", "char*"),
        ("119", "67", "source_glyph_lane_cursor", "char*"),
        ("131", "66", "glyph_column_index", "int32_t"),
        ("137", "72", "source_glyph_column_cursor", "char*"),
        ("139", "69", "glyph", "char"),
        ("185", "72", "metadata_row_index", "int32_t"),
        (
            "218",
            "67",
            "destination_metadata_cursor",
            "AuthoredSegmentRowObjectIdCursorView*",
        ),
        (
            "224",
            "66",
            "source_metadata_cursor",
            "AuthoredSegmentRowObjectIdCursorView*",
        ),
        ("291", "73", "source_local_position", "Vec3*"),
        ("294", "69", "destination_local_position", "Vec3*"),
    ):
        assert f"        {index}," in binja_sync
        assert f"        {storage}," in binja_sync
        assert f'        "{name}",' in binja_sync
        assert f'        "{declaration}",' in binja_sync
    for definition in (
        '("0x447364", "mlil", "StackVariableSourceType", 100, 4)',
        '("0x44737d", "mlil_ssa", "StackVariableSourceType", 125, 4)',
        '("0x4473aa", "mlil", "StackVariableSourceType", 170, 4)',
    ):
        assert definition in binja_sync
    assert "SEGMENT_COPY_GLYPH_LANE_TARGET_VAR" in binja_sync
    assert 'variable_name="glyph_lane_remaining"' in binja_sync

    assert "SEGMENT_COPY_LVAR_SPECS" in ida_sync
    for definition_address, stack_offset, name, declaration in (
        ("0x44730E", "None", "catalog", "SMTracks *catalog;"),
        ("0x447314", "None", "catalog_index", "int32_t catalog_index;"),
        (
            "0x44731B",
            "None",
            "catalog_filename_cursor",
            "char *catalog_filename_cursor;",
        ),
        (
            "0x44735C",
            "None",
            "destination_segment",
            "SubSegment *destination_segment;",
        ),
        (
            "0x447365",
            "32",
            "glyph_lane_remaining",
            "int32_t glyph_lane_remaining;",
        ),
        (
            "0x447375",
            "None",
            "destination_glyph_row_cursor",
            "char *destination_glyph_row_cursor;",
        ),
        (
            "0x447378",
            "None",
            "source_glyph_lane_cursor",
            "char *source_glyph_lane_cursor;",
        ),
        (
            "0x44738A",
            "None",
            "source_glyph_column_cursor",
            "char *source_glyph_column_cursor;",
        ),
        (
            "0x4473DB",
            "None",
            "destination_metadata_cursor",
            "int32_t *__shifted(AuthoredSegmentRowObjectIdCursorView, 0x14)",
        ),
        (
            "0x4473E1",
            "None",
            "source_metadata_cursor",
            "int32_t *__shifted(AuthoredSegmentRowObjectIdCursorView, 0x14)",
        ),
        (
            "0x447424",
            "None",
            "source_local_position",
            "Vec3 *source_local_position;",
        ),
        (
            "0x447427",
            "None",
            "destination_local_position",
            "Vec3 *destination_local_position;",
        ),
    ):
        assert definition_address in ida_sync
        assert f"        {stack_offset}," in ida_sync
        assert f'"{name}"' in ida_sync
        assert declaration in ida_sync
    assert '"segment_copy_lvars": segment_copy_lvars' in ida_sync
    assert "segment_copy_lvar_failures" in ida_sync

    binja_check = health_checks["bn_copy_segment_definition_parser_context"]
    for marker in (
        "struct SMTracks* catalog",
        "int32_t glyph_lane_remaining = 8",
        "char* destination_glyph_row_cursor",
        "char* source_glyph_column_cursor",
        "AuthoredSegmentRowObjectIdCursorView* destination_metadata_cursor",
        "AuthoredSegmentRowObjectIdCursorView* source_metadata_cursor",
        "destination_metadata_cursor->flags = source_metadata_cursor->flags",
        "destination_metadata_cursor->object_position.x",
        "destination_metadata_cursor->object_velocity.x",
        "destination_metadata_cursor->parcel_set_id",
        "destination_segment->row_count",
        "destination_segment->message_sample_id",
    ):
        assert marker in binja_check["required_substrings"]
    for old_shape in (
        "segment_1->",
        "char (*)[0x8][0x100]",
        "char (*)[0x100][0x8]",
        "ecx_3 - 0x828",
        "eax_7 - 0x8a0",
        "entry.glyph_columns[0xff]",
        "glyph_rows[7][0xf8]",
    ):
        assert old_shape in binja_check["forbidden_substrings"]

    ida_check = health_checks["ida_copy_segment_definition_owner"]
    for marker in (
        "SMTracks *catalog",
        "int32_t glyph_lane_remaining",
        "char *destination_glyph_row_cursor",
        "char *source_glyph_column_cursor",
        (
            "int32_t *__shifted(AuthoredSegmentRowObjectIdCursorView,0x14) "
            "destination_metadata_cursor"
        ),
        (
            "int32_t *__shifted(AuthoredSegmentRowObjectIdCursorView,0x14) "
            "source_metadata_cursor"
        ),
        "ADJ(destination_metadata_cursor)->flags",
        "ADJ(destination_metadata_cursor)->object_position.x",
        "ADJ(destination_metadata_cursor)->object_velocity.x",
        "ADJ(destination_metadata_cursor)->parcel_set_id",
    ):
        assert any(
            marker in required
            for required in ida_check["required_substrings"]
        )
    for old_shape in (
        "SMTracks *p_sm_tracks",
        "int ArgList;",
        "int32_t *p_object_id",
        "int32_t *v15",
        "int32_t *v16",
        "int32_t *v17",
    ):
        assert old_shape in ida_check["forbidden_substrings"]


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
    ida_segment_sync = (IDA_DIR / "apply_segment_catalog_types.py").read_text(
        encoding="utf-8"
    )
    ida_segment_runner = (IDA_DIR / "sync_segment_catalog_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    binja_segment_sync = (
        BINJA_DIR / "sync_segment_catalog_types.py"
    ).read_text(encoding="utf-8")

    assert '"AuthoredSegmentRowFlag",' in binja_source
    assert '"SubRowFlag",' in binja_source

    for header in (
        analysis_path_header,
        analysis_segment_header,
        matcher_segment_header,
    ):
        assert "AUTHORED_SEGMENT_ROW_FLAG_PARCEL = 0x0001" in header
        assert (
            "AUTHORED_SEGMENT_ROW_FLAG_SUPPRESS_TRACK_RENDER = 0x0004"
            in header
        )
        assert (
            "AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY = 0x0008" in header
        )
        assert "AUTHORED_SEGMENT_ROW_FLAG_NO_FALL = 0x0100" in header
        assert "AUTHORED_SEGMENT_ROW_FLAG_RING_POWER_UP = 0x2000" in header
        assert "AUTHORED_SEGMENT_ROW_FLAG_JETPACK_OFF = 0x8000" in header

    for header in (analysis_segment_header, matcher_segment_header):
        assert "metadata_words[6]" in header
        assert "marker_row" in header
        assert "unknown_04" not in header
        assert "unknown_24" not in header

    for header in (analysis_path_header, analysis_segment_header):
        assert "typedef char LevelFileTextBuffer[0x2800];" in header
        assert "AuthoredFloatBits selected_speed;" in header
        assert "float selected_speed;" not in header

    for sync_source in (binja_segment_sync, ida_segment_sync):
        assert "g_current_level_definition_name" in sync_source
        assert "g_level_file_text_buffer" in sync_source
    assert "LevelFileTextBuffer" in binja_segment_sync
    assert "types_declare_if_changed" in binja_segment_sync
    assert "types_declare(" not in binja_segment_sync
    for sync_source in (binja_segment_sync, ida_segment_sync):
        assert "EXPECTED_OWNER_SIZES" in sync_source
        assert '"AuthoredSegmentRow": 0x38' in sync_source
        assert '"SegmentCatalogEntry": 0x4088' in sync_source
        assert '"SegmentCatalogEntryAnchor": 0x408C' in sync_source
        assert '"SegmentCatalogRowStrideAnchor": 0x8C4' in sync_source
        assert '"SMTracks": 0x25CFB4' in sync_source
        assert '"SubSegment": 0x4220' in sync_source
        assert '"SubTracks": 0x1A5978' in sync_source
        assert '"SubSegmentRaw": 0x48' in sync_source
    assert "current_type_widths" in binja_segment_sync
    assert '"op": "owner_size_verify"' in binja_segment_sync
    assert "SEGMENT_OWNER_MARKERS" in ida_segment_sync
    assert "owner_sizes" in ida_segment_sync
    assert "SEGMENT_USER_VAR_UPDATES" in binja_segment_sync
    assert '"selected_entry_anchor"' in binja_segment_sync
    assert '"SegmentCatalogEntryAnchor*"' in binja_segment_sync
    assert '"load_segment_definitions"' in binja_segment_sync
    assert '"RegisterVariableSourceType",\n        5,\n        67,' in binja_segment_sync
    assert '"tracks_after_stack_probe"' in binja_segment_sync
    assert '"SMTracks*"' in binja_segment_sync
    assert '"RegisterVariableSourceType",\n        469,\n        72,' in binja_segment_sync
    assert '"row_stride_anchor"' in binja_segment_sync
    assert '"SegmentCatalogRowStrideAnchor*"' in binja_segment_sync
    assert "BUILTIN_GRID_OFFSET_SPLIT_DEFINITIONS" in binja_segment_sync
    assert '("0x44809d", "mlil", "StackVariableSourceType", 61, 4)' in binja_segment_sync
    assert '("0x4480c2", "mlil_ssa", "StackVariableSourceType", 98, 4)' in binja_segment_sync
    assert '("0x448109", "mlil", "StackVariableSourceType", 169, 4)' in binja_segment_sync
    assert "apply_split_user_var_update" in binja_segment_sync
    assert 'variable_name="grid_offset"' in binja_segment_sync
    assert 'variable_type="int32_t"' in binja_segment_sync
    for header in (analysis_path_header, analysis_segment_header):
        assert "typedef struct SegmentCatalogEntryAnchor" in header
        assert "int32_t stride_prefix_word;" in header
        assert "SegmentCatalogEntry entry;" in header
        assert "typedef struct SegmentCatalogRowStrideAnchor" in header
        assert "uint8_t catalog_prefix[0x88c];" in header
        assert "AuthoredSegmentRow row;" in header
    assert '"char g_level_file_text_buffer[10240];"' in ida_segment_sync

    assert "POPULATE_RUNTIME_USER_VAR_UPDATES" in binja_source
    assert "POPULATE_RUNTIME_SPLIT_USER_VAR_UPDATES" in binja_source
    assert '("0x436165", "mlil", "RegisterVariableSourceType", 693, 67)' in binja_source
    assert '("0x43616a", "mlil_ssa", "RegisterVariableSourceType", 698, 67)' in binja_source
    assert '("0x436171", "mlil_ssa", "RegisterVariableSourceType", 705, 67)' in binja_source
    assert '("0x4361a1", "mlil", "RegisterVariableSourceType", 753, 67)' in binja_source
    assert '("0x4361ad", "mlil", "RegisterVariableSourceType", 765, 67)' in binja_source
    assert '("0x4361b3", "mlil_ssa", "RegisterVariableSourceType", 771, 67)' in binja_source
    assert '("0x4361bd", "mlil_ssa", "RegisterVariableSourceType", 781, 67)' in binja_source
    assert '("0x43714d", "mlil", "RegisterVariableSourceType", 4765, 67)' in binja_source
    assert '"visited_cursor"' in binja_source
    assert '"StackVariableSourceType",\n        1077,\n        -52,' in binja_source
    assert '"RegisterVariableSourceType",\n        1363,\n        72,' in binja_source
    assert '"RegisterVariableSourceType",\n        1448,\n        69,' in binja_source
    assert '"RegisterVariableSourceType",\n        2002,\n        72,' in binja_source
    assert '"RegisterVariableSourceType",\n        3857,\n        67,' in binja_source
    for identity in (
        '"StackVariableSourceType",\n        0,\n        -36,',
        '"StackVariableSourceType",\n        549,\n        -32,',
        '"StackVariableSourceType",\n        553,\n        -66,',
        '"StackVariableSourceType",\n        558,\n        -44,',
        '"StackVariableSourceType",\n        794,\n        -64,',
        '"StackVariableSourceType",\n        833,\n        -60,',
        '"StackVariableSourceType",\n        1921,\n        -65,',
        '"StackVariableSourceType",\n        1926,\n        -48,',
    ):
        assert identity in binja_source
    for identity in (
        '"RegisterVariableSourceType",\n        4697,\n        67,',
        '"RegisterVariableSourceType",\n        4692,\n        68,',
        '"RegisterVariableSourceType",\n        4697,\n        66,',
        '"RegisterVariableSourceType",\n        4714,\n        66,',
        '"RegisterVariableSourceType",\n        4718,\n        66,',
    ):
        assert identity in binja_source
    for name, type_name in (
        ("segment_cursor", "int32_t"),
        ("trampoline_counter", "int32_t"),
        ("first_or_last_row", "char"),
        ("row_event_owner", "int32_t"),
        ("build_row", "int32_t"),
        ("active_segment", "SubSegment*"),
        ("segment_row_index", "int32_t"),
        ("attachment_entry_installed", "char"),
        ("lane", "int32_t"),
        ("segment_row_anchor", "SubSegmentRowStrideAnchor*"),
        ("runtime_row_anchor", "RuntimeRowStrideAnchor*"),
        ("runtime_cell_anchor", "RuntimeCellStrideAnchor*"),
        ("stamped_row", "SubRow*"),
        ("fringe_slot", "Fringe**"),
        ("remaining_fringe_slots", "int32_t"),
        ("fringe_object", "Fringe*"),
        ("fringe_object_reloaded", "Fringe*"),
        ("fringe_position", "Vec3*"),
    ):
        assert f'"{name}"' in binja_source
        assert f'"{type_name}"' in binja_source

    assert "MERGE_RUNTIME_USER_VAR_UPDATES" in binja_source
    for identity in (
        '"StackVariableSourceType",\n        83,\n        -4,',
        '"RegisterVariableSourceType",\n        20,\n        66,',
        '"RegisterVariableSourceType",\n        87,\n        69,',
        '"RegisterVariableSourceType",\n        105,\n        73,',
        '"RegisterVariableSourceType",\n        155,\n        67,',
        '"RegisterVariableSourceType",\n        281,\n        66,',
        '"RegisterVariableSourceType",\n        365,\n        73,',
        '"RegisterVariableSourceType",\n        475,\n        66,',
        '"RegisterVariableSourceType",\n        613,\n        68,',
        '"RegisterVariableSourceType",\n        773,\n        66,',
    ):
        assert identity in binja_source
    for name, type_name in (
        ("row_attachment_flags", "uint32_t*"),
        ("seed_lane_flags", "uint32_t*"),
        ("cell_lane_flags", "uint32_t*"),
        ("cell", "TrackRowCell*"),
        ("floor_tile_cursor", "uint8_t*"),
        ("floor_cleanup_lane_flags", "uint32_t*"),
        ("slide_lane_flags_cursor", "uint32_t*"),
        ("slide_cleanup_lane_flags", "uint32_t*"),
        ("wall_tile_cursor", "uint8_t*"),
        ("wall_cleanup_lane_flags", "uint32_t*"),
    ):
        assert f'"{name}"' in binja_source
        assert f'"{type_name}"' in binja_source
    assert "*MERGE_RUNTIME_USER_VAR_UPDATES" in binja_source

    assert "FRINGE_RUNTIME_USER_VAR_UPDATES" in binja_source
    for identity in (
        '"RegisterVariableSourceType",\n        44,\n        68,',
        '"RegisterVariableSourceType",\n        52,\n        72,',
        '"StackVariableSourceType",\n        58,\n        -68,',
    ):
        assert identity in binja_source
    for name, type_name in (
        ("row", "SubRow*"),
        ("cell", "TrackRowCell*"),
        ("row_cursor", "SubRow*"),
    ):
        assert f'"{name}"' in binja_source
        assert f'"{type_name}"' in binja_source
    assert "*FRINGE_RUNTIME_USER_VAR_UPDATES" in binja_source
    for selector, declaration in (
        (
            "initialize_fringe_manager",
            "void __thiscall initialize_fringe_manager(FringeManager* manager)",
        ),
        (
            "allocate_fringe_object",
            "Fringe* __thiscall allocate_fringe_object(FringeManager* manager)",
        ),
    ):
        assert f'"{selector}"' in binja_source
        assert f'"{declaration}"' in binja_source

    assert "typedef struct SubSegmentRowStrideAnchor" in analysis_path_header
    assert "uint8_t segment_prefix[0x814];" in analysis_path_header
    assert "typedef struct SubSegmentParcelScanAnchor" in analysis_path_header
    assert "int32_t next_segment_row_base;" in analysis_path_header
    assert "typedef struct SubSegmentEventBiasView" in analysis_path_header
    assert "uint8_t subgame_prefix[0x6658];" in analysis_path_header
    assert "SubSegment segment_slots_one_based[101];" in analysis_path_header
    assert "SubSegmentEventBiasView_must_be_0x1a7cf8" in analysis_path_header
    assert "UPDATE_SUBGOLDY_EVENT_VIEW_SPLIT_DEFINITIONS" in binja_source
    assert (
        '("0x43b752", "mlil", "RegisterVariableSourceType", 1586, 66)'
        in binja_source
    )
    for identity in (
        '"RegisterVariableSourceType",\n        1520,\n        66,',
        '"RegisterVariableSourceType",\n        1628,\n        68,',
        '"RegisterVariableSourceType",\n        1688,\n        68,',
        '"RegisterVariableSourceType",\n        1794,\n        68,',
    ):
        assert identity in binja_source
    for name, type_name in (
        ("row_event_segment_view", "SubSegmentEventBiasView*"),
        ("message_segment_view", "SubSegmentEventBiasView*"),
        ("duration_segment_view", "SubSegmentEventBiasView*"),
        ("sample_segment_view", "SubSegmentEventBiasView*"),
    ):
        assert f'"{name}"' in binja_source
        assert f'"{type_name}"' in binja_source
    assert "--update-subgoldy-only" in binja_source
    assert "typedef struct RuntimeRowStrideAnchor" in analysis_path_header
    assert "uint8_t runtime_prefix[0x5ccac8];" in analysis_path_header
    assert "typedef struct RuntimeCellStrideAnchor" in analysis_path_header
    assert "TrackRowCell previous_row_same_lane;" in analysis_path_header
    assert (
        "uint8_t runtime_gap_previous_row_to_previous_lane[0x1f8];"
        in analysis_path_header
    )
    assert "TrackRowCell previous_lane_same_row;" in analysis_path_header
    assert "TrackRowCell next_lane_same_row;" in analysis_path_header
    assert (
        "uint8_t runtime_gap_next_lane_to_next_row[0x1f8];"
        in analysis_path_header
    )
    assert "TrackRowCell next_row_same_lane;" in analysis_path_header
    assert (
        "uint8_t runtime_gap_next_row_to_projected_row[0xccc];"
        in analysis_path_header
    )
    assert "TrackRowCell projected_row_six_ahead_same_lane;" in analysis_path_header
    assert "typedef struct TimeTrialRouteRecordCursor" in analysis_path_header
    assert "uint8_t subgame_prefix[0x944150];" in analysis_path_header
    assert "SubSolution record;" in analysis_path_header
    assert "} TimeTrialRouteRecordCursor;" in analysis_path_header

    assert "UPDATE_SUBGAME_RUNTIME_USER_VAR_UPDATES" in binja_source
    for identity in (
        '"RegisterVariableSourceType",\n        1188,\n        73,',
        '"RegisterVariableSourceType",\n        1384,\n        73,',
        '"RegisterVariableSourceType",\n        3386,\n        66,',
    ):
        assert identity in binja_source
    for name, type_name in (
        ("runtime_row_anchor", "RuntimeRowStrideAnchor*"),
        ("runtime_cell_anchor", "RuntimeCellStrideAnchor*"),
        ("time_trial_route_cursor", "TimeTrialRouteRecordCursor*"),
    ):
        assert f'"{name}"' in binja_source
        assert f'"{type_name}"' in binja_source
    assert "*UPDATE_SUBGAME_RUNTIME_USER_VAR_UPDATES" in binja_source

    assert "HARMONIZE_RUNTIME_USER_VAR_UPDATES" in binja_source
    assert '"RegisterVariableSourceType",\n        98,\n        72,' in binja_source
    assert '"RegisterVariableSourceType",\n        492,\n        72,' in binja_source
    assert '"forward_cell_anchor"' in binja_source
    assert '"backward_cell_anchor"' in binja_source
    assert "*HARMONIZE_RUNTIME_USER_VAR_UPDATES" in binja_source

    assert "POPULATE_RUNTIME_LVAR_SPECS" in ida_path_sync
    assert '("visited_cursor", "uint8_t *visited_cursor;", 0x4361AE, None)' in ida_path_sync
    for definition_address in (
        "0x436073",
        "0x4360EA",
        "0x4360EE",
        "0x4360F4",
        "0x4360FE",
        "0x43612A",
        "0x43612D",
        "0x43614E",
        "0x436162",
        "0x436166",
        "0x43616B",
    ):
        assert definition_address in ida_path_sync
    for name, declaration in (
        ("segment_row_count_cursor", "int32_t *segment_row_count_cursor;"),
        (
            "row_fringe_front_cursor",
            "TrackRowCellFringeFrontStrideCursor *row_fringe_front_cursor;",
        ),
        (
            "parcel_spawn_y_cursor",
            "SubRowParcelSpawnYStrideCursor *parcel_spawn_y_cursor;",
        ),
        ("rows_remaining", "int32_t rows_remaining;"),
        ("cell_lanes_remaining", "int32_t cell_lanes_remaining;"),
        (
            "lane_and_flags_cursor",
            "TrackRowCellLaneAndFlagsStrideCursor *lane_and_flags_cursor;",
        ),
        ("cell_lane_and_flags", "uint32_t cell_lane_and_flags;"),
        ("cell_list_flags", "uint32_t cell_list_flags;"),
        (
            "next_row_fringe_front_cursor",
            "TrackRowCellFringeFrontStrideCursor *next_row_fringe_front_cursor;",
        ),
        ("remaining_cell_lanes", "int32_t remaining_cell_lanes;"),
        (
            "cell_fringe_front_cursor",
            "TrackRowCellFringeFrontStrideCursor *cell_fringe_front_cursor;",
        ),
    ):
        assert f'"{name}"' in ida_path_sync
        assert f'"{declaration}"' in ida_path_sync
    assert "0x4362E6" in ida_path_sync
    assert "0x436404" in ida_path_sync
    assert "0x436459" in ida_path_sync
    assert "0x436683" in ida_path_sync
    assert "0x436DC2" in ida_path_sync
    assert '"stamped_row"' in ida_path_sync
    assert '"SubRow *stamped_row;"' in ida_path_sync
    for definition_address in (
        "0x435EB0",
        "0x4360D6",
        "0x4360DA",
        "0x4360DF",
        "0x4361CB",
        "0x4361F2",
        "0x436632",
        "0x436637",
    ):
        assert definition_address in ida_path_sync
    for name, declaration in (
        ("segment_cursor", "int32_t segment_cursor;"),
        ("trampoline_counter", "int32_t trampoline_counter;"),
        ("first_or_last_row", "char first_or_last_row;"),
        ("row_event_owner", "int32_t row_event_owner;"),
        ("build_row", "int32_t build_row;"),
        ("active_segment", "SubSegment *active_segment;"),
        ("attachment_entry_installed", "char attachment_entry_installed;"),
        ("lane", "int32_t lane;"),
    ):
        assert f'"{name}"' in ida_path_sync
        assert f'"{declaration}"' in ida_path_sync
    for definition_address in (
        "0x437101",
        "0x437105",
        "0x43710A",
        "0x43711F",
    ):
        assert definition_address in ida_path_sync
    for name, declaration in (
        ("fringe_slot", "Fringe **fringe_slot;"),
        ("remaining_fringe_slots", "int32_t remaining_fringe_slots;"),
        ("fringe_object", "Fringe *fringe_object;"),
        ("fringe_position", "Vec3 *fringe_position;"),
    ):
        assert f'"{name}"' in ida_path_sync
        assert f'"{declaration}"' in ida_path_sync
    assert "MERGE_RUNTIME_LVAR_SPECS" in ida_path_sync
    for definition_address in (
        "0x435195",
        "0x4351D8",
        "0x4351EA",
        "0x43521C",
        "0x43529A",
        "0x4352EE",
        "0x43535C",
        "0x4353E6",
        "0x435486",
        "0x4351D4",
    ):
        assert definition_address in ida_path_sync
    assert "FRINGE_RUNTIME_LVAR_SPECS" in ida_path_sync
    for definition_address in (
        "0x434C0D",
        "0x434C15",
        "0x434C1B",
        "0x434D44",
        "0x434E48",
        "0x434F4C",
        "0x435050",
    ):
        assert definition_address in ida_path_sync
    for name, declaration in (
        ("row", "SubRow *row;"),
        ("cell", "TrackRowCell *cell;"),
        ("row_cursor", "SubRow *row_cursor;"),
        ("fringe_front_new", "Fringe *fringe_front_new;"),
        ("fringe_right_new", "Fringe *fringe_right_new;"),
        ("fringe_left_new", "Fringe *fringe_left_new;"),
        ("fringe_back_new", "Fringe *fringe_back_new;"),
    ):
        assert f'"{name}"' in ida_path_sync
        assert f'"{declaration}"' in ida_path_sync
    assert "HARMONIZE_RUNTIME_LVAR_SPECS" in ida_path_sync
    assert "0x435753" in ida_path_sync
    assert "0x4358DD" in ida_path_sync
    assert "HARMONIZE_ROOT_OFFSET_OPERANDS" in ida_path_sync
    assert "(0x4357A0, 1, 0x447B4)" in ida_path_sync
    assert "(0x435A1F, 1, 0x4423C)" in ida_path_sync
    assert "FRINGE_RUNTIME_ROW_OFFSET_OPERANDS" in ida_path_sync
    assert "(0x434C0C, 1, 0x5CCAC8)" in ida_path_sync
    assert "fringe_runtime_row_offset_operands = _normalize_root_offset_operands(" in ida_path_sync
    assert "POPULATE_RUNTIME_ROW_OFFSET_OPERANDS" in ida_path_sync
    for operand_spec in (
        "(0x4360ED, 1, 0x5CCB5C)",
        "(0x43645C, 0, 0x5CCBB4)",
        "(0x4364D5, 1, 0x5CCB3C)",
        "(0x436565, 1, 0x5CCB58)",
        "(0x436D84, 1, 0x5CCB78)",
        "(0x436E30, 1, 0x5CCB58)",
        "(0x436FE2, 1, 0x5CCB9C)",
    ):
        assert operand_spec in ida_path_sync
    assert (
        "populate_runtime_row_offset_operands = _normalize_root_offset_operands("
        in ida_path_sync
    )
    assert '"populate_runtime_row_offset_operands"' in ida_path_sync
    assert "UPDATE_SUBGAME_RUNTIME_LVAR_SPECS" in ida_path_sync
    for definition_address in ("0x439035", "0x439038", "0x4390F9", "0x4398CB"):
        assert definition_address in ida_path_sync
    for name, declaration in (
        ("runtime_row_anchor", "RuntimeRowStrideAnchor *runtime_row_anchor;"),
        (
            "runtime_row_anchor_saved",
            "RuntimeRowStrideAnchor *runtime_row_anchor_saved;",
        ),
        ("runtime_cell_anchor", "RuntimeCellStrideAnchor *runtime_cell_anchor;"),
        (
            "time_trial_route_cursor",
            "TimeTrialRouteRecordCursor *time_trial_route_cursor;",
        ),
    ):
        assert f'"{name}"' in ida_path_sync
        assert f'"{declaration}"' in ida_path_sync
    assert "UPDATE_SUBGAME_RUNTIME_ROW_OFFSET_OPERANDS" in ida_path_sync
    for operand_spec in (
        "(0x43902B, 1, 0x5CCAC8)",
        "(0x43903D, 1, 0x5CCAD0)",
        "(0x439043, 1, 0x5CCACC)",
        "(0x43909F, 0, 0x5CCAC8)",
        "(0x4390B7, 1, 0x5CCB58)",
        "(0x4391D4, 1, 0x5CCB78)",
        "(0x439228, 1, 0x5CCB88)",
        "(0x439569, 1, 0x5CCAC8)",
        "(0x439827, 1, 0x5CCAC8)",
    ):
        assert operand_spec in ida_path_sync
    assert (
        "update_subgame_runtime_row_offset_operands = _normalize_root_offset_operands("
        in ida_path_sync
    )
    assert "UPDATE_SUBGAME_RUNTIME_FLAG_OPERANDS" in ida_path_sync
    assert "(0x4390A8, 1, 0x800000)" in ida_path_sync
    assert (
        "update_subgame_runtime_flag_operands = _normalize_root_offset_operands("
        in ida_path_sync
    )
    assert "UPDATE_SUBGOLDY_RUNTIME_ROW_OFFSET_OPERANDS" in ida_path_sync
    for operand_spec in (
        "(0x43B709, 1, 0x5CCAC8)",
        "(0x43B710, 1, 0x5CCBB8)",
        "(0x43BCF3, 1, 0x5CCAC8)",
        "(0x43BD44, 0, 0x5CCAC8)",
        "(0x43BD98, 1, 0x5CCB6C)",
        "(0x43BDE6, 1, 0x5CCB6C)",
        "(0x43BE19, 0, 0x5CCAC8)",
        "(0x43BE6D, 1, 0x5CCB70)",
        "(0x43BEBB, 1, 0x5CCB70)",
    ):
        assert operand_spec in ida_path_sync
    assert (
        "update_subgoldy_runtime_row_offset_operands = "
        "_normalize_root_offset_operands(" in ida_path_sync
    )
    assert '"update_subgoldy_runtime_row_offset_operands"' in ida_path_sync
    assert "INITIALIZE_SUBGAME_RECORD_BANK_OFFSET_OPERANDS" in ida_path_sync
    for operand_spec in (
        "(0x43757E, 1, 0x68B4D0)",
        "(0x437567, 1, 0x7E7B10)",
        "(0x43755F, 1, 0x944150)",
        "(0x43756D, 0, 0x68B4C8)",
        "(0x437584, 0, 0x68B4C8)",
    ):
        assert operand_spec in ida_path_sync
    assert "initialize_subgame_record_bank_offset_operands" in ida_path_sync
    assert "_sync_exact_lvars" in ida_path_sync
    assert "_sync_populate_runtime_lvars" in ida_path_sync
    assert "_sync_merge_runtime_lvars" in ida_path_sync
    assert "_sync_fringe_runtime_lvars" in ida_path_sync
    assert "_sync_harmonize_runtime_lvars" in ida_path_sync
    assert "_sync_update_subgame_runtime_lvars" in ida_path_sync
    assert "UPDATE_SUBGOLDY_LVAR_SPECS" in ida_path_sync
    assert "_sync_update_subgoldy_lvars" in ida_path_sync
    for definition_address in (
        "0x43B6EB",
        "0x43B6F0",
        "0x43B707",
        "0x43B70A",
        "0x43B711",
        "0x43B823",
        "0x43BCCE",
        "0x43BCDE",
        "0x43BDA4",
        "0x43BDD3",
        "0x43BE79",
        "0x43BEA8",
        "0x43CD08",
    ):
        assert definition_address in ida_path_sync
    for name, declaration in (
        ("row_event_cell", "TrackRowCell *row_event_cell;"),
        ("row_event_game", "SubgameRuntime *row_event_game;"),
        ("row_event_row_index", "int32_t row_event_row_index;"),
        ("runtime_row", "SubRow *runtime_row;"),
        ("row_event_id", "int32_t row_event_id;"),
        (
            "sample_segment_view",
            "SubSegmentEventBiasView *sample_segment_view;",
        ),
        ("current_cell", "TrackRowCell *current_cell;"),
        ("attachment_game", "SubgameRuntime *attachment_game;"),
        (
            "primary_attachment_cell",
            "TrackRowCell *primary_attachment_cell;",
        ),
        ("primary_row_index", "int32_t primary_row_index;"),
        (
            "secondary_attachment_cell",
            "TrackRowCell *secondary_attachment_cell;",
        ),
        ("secondary_row_index", "int32_t secondary_row_index;"),
        (
            "time_trial_route_cursor",
            "TimeTrialRouteRecordCursor *time_trial_route_cursor;",
        ),
    ):
        assert f'"{name}"' in ida_path_sync
        assert f'"{declaration}"' in ida_path_sync
    for address, name in (
        ("0x447090", "initialize_fringe_manager"),
        ("0x4470A0", "allocate_fringe_object"),
    ):
        assert f'({address}, "{name}")' in ida_path_sync
        assert f'"{name}"' in ida_path_sync
    for address in ("0x434BE0", "0x447090", "0x4470A0"):
        assert address in ida_path_sync

    assert "BUILD_SUBGAME_ACTIVE_BOD_USER_VAR_UPDATES" in binja_source
    assert "--build-subgame-only" in binja_source
    assert "if args.build_subgame_only:" in binja_source
    assert "updates=BUILD_SUBGAME_ACTIVE_BOD_USER_VAR_UPDATES" in binja_source
    assert "typedef struct BodList" in analysis_path_header
    assert "BodNode* first;" in analysis_path_header
    assert '"BodList"' in binja_source
    assert '("0x5a8", "active_bod_list", "BodList")' in binja_source
    for identity in (
        '"RegisterVariableSourceType",\n        1308,\n        67,',
        '"RegisterVariableSourceType",\n        1314,\n        68,',
        '"RegisterVariableSourceType",\n        1325,\n        68,',
        '"RegisterVariableSourceType",\n        1335,\n        68,',
        '"RegisterVariableSourceType",\n        1337,\n        71,',
        '"RegisterVariableSourceType",\n        1343,\n        68,',
        '"RegisterVariableSourceType",\n        1350,\n        68,',
        '"RegisterVariableSourceType",\n        1397,\n        66,',
        '"RegisterVariableSourceType",\n        1485,\n        66,',
        '"RegisterVariableSourceType",\n        1573,\n        66,',
        '"RegisterVariableSourceType",\n        1661,\n        66,',
        '"RegisterVariableSourceType",\n        1764,\n        66,',
        '"RegisterVariableSourceType",\n        1841,\n        66,',
        '"RegisterVariableSourceType",\n        1869,\n        68,',
    ):
        assert identity in binja_source
    for owner in (
        "jetpack",
        "weapon_0",
        "weapon_1",
        "weapon_2",
        "invincible_shell",
        "presentation",
        "player",
    ):
        assert f'"active_first_ref_{owner}"' in binja_source
    assert '"BodNode**"' in binja_source
    assert '"initialized_player"' not in binja_source
    assert '"RegisterVariableSourceType",\n        1261,\n        73,' not in binja_source
    for identity in (
        '"RegisterVariableSourceType",\n        1272,\n        66,',
        '"RegisterVariableSourceType",\n        1367,\n        67,',
        '"RegisterVariableSourceType",\n        1455,\n        67,',
        '"RegisterVariableSourceType",\n        1543,\n        67,',
        '"RegisterVariableSourceType",\n        1631,\n        67,',
        '"RegisterVariableSourceType",\n        1734,\n        67,',
        '"RegisterVariableSourceType",\n        1156,\n        73,',
    ):
        assert identity in binja_source
    for name, type_name in (
        ("jetpack_channel", "Weapon*"),
        ("weapon_channel_0", "Weapon*"),
        ("weapon_channel_1", "Weapon*"),
        ("weapon_channel_2", "Weapon*"),
        ("invincible_shell", "Invincible*"),
        ("presentation", "Snail*"),
        ("player", "Player*"),
    ):
        assert f'"{name}"' in binja_source
        assert f'"{type_name}"' in binja_source

    assert "RUNTIME_POOL_ROW_OFFSET_OPERANDS" in ida_path_sync
    assert "(0x4082EC, 1, 0x5CCAC8)" in ida_path_sync
    assert (
        "runtime_pool_row_offset_operands = _normalize_root_offset_operands("
        in ida_path_sync
    )
    assert "*BUILD_SUBGAME_ACTIVE_BOD_USER_VAR_UPDATES" in binja_source

    assert "--update-subgame-only" in binja_source
    assert "if args.update_subgame_only:" in binja_source
    for identity in (
        '"RegisterVariableSourceType",\n        1203,\n        67,',
        '"RegisterVariableSourceType",\n        1235,\n        66,',
        '"RegisterVariableSourceType",\n        1241,\n        68,',
        '"RegisterVariableSourceType",\n        1266,\n        68,',
        '"RegisterVariableSourceType",\n        1278,\n        68,',
    ):
        assert identity in binja_source
    for name, type_name in (
        ("row_model", "RowModel*"),
        ("active_first_ref_row", "BodNode**"),
        ("active_first_row", "BodNode*"),
        ("active_first_row_reload", "BodNode*"),
        ("active_new_first_row", "BodNode*"),
    ):
        assert f'"{name}"' in binja_source
        assert f'"{type_name}"' in binja_source

    assert "CREATE_GOLB_ACTIVE_BOD_USER_VAR_UPDATES" in binja_source
    for identity in (
        '"RegisterVariableSourceType",\n        52,\n        66,',
        '"RegisterVariableSourceType",\n        57,\n        67,',
        '"RegisterVariableSourceType",\n        78,\n        67,',
        '"RegisterVariableSourceType",\n        80,\n        73,',
        '"RegisterVariableSourceType",\n        86,\n        67,',
        '"RegisterVariableSourceType",\n        88,\n        67,',
        '"RegisterVariableSourceType",\n        1431,\n        67,',
        '"RegisterVariableSourceType",\n        1500,\n        66,',
        '"RegisterVariableSourceType",\n        1506,\n        68,',
        '"RegisterVariableSourceType",\n        1521,\n        66,',
        '"RegisterVariableSourceType",\n        1531,\n        68,',
        '"RegisterVariableSourceType",\n        1533,\n        71,',
        '"RegisterVariableSourceType",\n        1539,\n        68,',
        '"RegisterVariableSourceType",\n        1541,\n        68,',
    ):
        assert identity in binja_source
    for name in (
        "active_first_ref_primary",
        "active_first_link_primary",
        "tertiary_node",
        "active_first_ref_tertiary",
        "active_first_link_tertiary",
        "active_new_first_tertiary",
    ):
        assert f'"{name}"' in binja_source
    assert "*CREATE_GOLB_ACTIVE_BOD_USER_VAR_UPDATES" in binja_source

    assert "PLACE_PARCELS_RUNTIME_USER_VAR_UPDATES" in binja_source
    assert "PLACE_PARCELS_SCAN_USER_VAR_UPDATES" in binja_source
    for identity in (
        '"RegisterVariableSourceType",\n        114,\n        69,',
        '"StackVariableSourceType",\n        124,\n        -532,',
        '"StackVariableSourceType",\n        186,\n        -496,',
        '"StackVariableSourceType",\n        436,\n        -492,',
        '"RegisterVariableSourceType",\n        190,\n        73,',
    ):
        assert identity in binja_source
    for name, type_name in (
        ("segment_row_count_anchor", "SubSegmentParcelScanAnchor*"),
        ("saved_segment_row_count_anchor", "SubSegmentParcelScanAnchor*"),
        ("glyph_row_cursor", "char*"),
        ("glyph_lane_cursor", "char*"),
        (
            "authored_parcel_row",
            "AuthoredSegmentRowPositionCursorView*",
        ),
    ):
        assert f'"{name}"' in binja_source
        assert f'"{type_name}"' in binja_source
    assert "*PLACE_PARCELS_SCAN_USER_VAR_UPDATES" in binja_source
    assert "AUTHORED_ROW_CURSOR_SIZES" in binja_source
    assert "verify_authored_row_cursor_sizes" in binja_source
    assert '"AuthoredSegmentRowPositionCursorView": 0x38' in binja_source
    assert "typedef struct __ptr_offset(0x08)" in analysis_path_header
    assert (
        "__base(Vec3, 0x08) AuthoredSegmentRowPositionCursorView"
        in analysis_path_header
    )
    assert "__inherited Vec3 local_position;" in analysis_path_header
    assert (
        "AuthoredSegmentRowPositionCursorView_must_be_0x38"
        in analysis_path_header
    )
    for identity in (
        '"RegisterVariableSourceType",\n        1239,\n        72,',
        '"RegisterVariableSourceType",\n        1832,\n        73,',
        '"RegisterVariableSourceType",\n        2177,\n        72,',
    ):
        assert identity in binja_source
    for name, type_name in (
        ("parcel_set_runtime_row_anchor", "RuntimeRowStrideAnchor*"),
        ("zero_runtime_row_anchor", "RuntimeRowStrideAnchor*"),
        ("projection_row", "SubRow*"),
    ):
        assert f'"{name}"' in binja_source
        assert f'"{type_name}"' in binja_source
    assert "*PLACE_PARCELS_RUNTIME_USER_VAR_UPDATES" in binja_source

    assert "PLACE_PARCELS_RUNTIME_LVAR_SPECS" in ida_path_sync
    for definition_address in (
        "0x443953",
        "0x44399F",
        "0x443DB8",
        "0x444009",
        "0x444162",
    ):
        assert definition_address in ida_path_sync
    for name, declaration in (
        (
            "segment_row_count_anchor",
            "SubSegmentParcelScanAnchor *segment_row_count_anchor;",
        ),
        ("authored_parcel_position", "Vec3 *authored_parcel_position;"),
        (
            "parcel_set_runtime_row_anchor",
            "RuntimeRowStrideAnchor *parcel_set_runtime_row_anchor;",
        ),
        ("zero_runtime_row_anchor", "RuntimeRowStrideAnchor *zero_runtime_row_anchor;"),
        ("projection_row", "SubRow *projection_row;"),
    ):
        assert f'"{name}"' in ida_path_sync
        assert f'"{declaration}"' in ida_path_sync
    assert "PLACE_PARCELS_REJECTED_STACK_LVAR_OVERRIDES" in ida_path_sync
    for rejected_override in (
        '("saved_segment_row_count_anchor", 0x44395D, 36)',
        '("glyph_row_cursor", 0x44399B, 72)',
        '("glyph_lane_cursor", 0x443A95, 76)',
    ):
        assert rejected_override in ida_path_sync
    assert "_clear_exact_lvar_override" in ida_path_sync
    assert '"rejected_stack_overrides"' in ida_path_sync
    assert "_sync_place_parcels_runtime_lvars" in ida_path_sync
    assert "PLACE_PARCELS_RUNTIME_ROW_OFFSET_OPERANDS" in ida_path_sync
    for operand_spec in (
        "(0x443DBA, 0, 0x5CCAC8)",
        "(0x443DE6, 1, 0x5CCB58)",
        "(0x443FFF, 1, 0x5CCAC8)",
        "(0x44402A, 1, 0x5CCB58)",
        "(0x444161, 1, 0x5CCAC8)",
    ):
        assert operand_spec in ida_path_sync
    assert (
        "place_parcels_runtime_row_offset_operands = _normalize_root_offset_operands("
        in ida_path_sync
    )

    assert "CHALLENGE_PARCELS_RUNTIME_ANCHOR_SPLIT_DEFINITIONS" in binja_source
    assert (
        '("0x44432d", "mlil", "RegisterVariableSourceType", 237, 67)'
        in binja_source
    )
    assert "CHALLENGE_PARCELS_RUNTIME_ANCHOR_TARGET_VAR" in binja_source
    assert "CHALLENGE_PARCELS_RUNTIME_USER_VAR_UPDATES" in binja_source
    assert 'identifier="place_challenge_parcels_on_track"' in binja_source
    assert 'variable_name="challenge_runtime_row_anchor"' in binja_source
    assert 'variable_type="RuntimeRowStrideAnchor*"' in binja_source
    assert '"RegisterVariableSourceType",\n        407,\n        72,' in binja_source
    assert '"projection_row"' in binja_source
    assert '"SubRow*"' in binja_source
    assert "*CHALLENGE_PARCELS_RUNTIME_USER_VAR_UPDATES" in binja_source

    assert "CHALLENGE_PARCELS_RUNTIME_LVAR_SPECS" in ida_path_sync
    for definition_address in (
        "0x444276",
        "0x444290",
        "0x444292",
        "0x444294",
        "0x44429C",
        "0x4442A1",
        "0x4442D3",
        "0x4442DD",
        "0x44430F",
        "0x44432E",
        "0x44438C",
        "0x4443CA",
        "0x4443D8",
        "0x44440A",
    ):
        assert definition_address in ida_path_sync
    for name, declaration in (
        ("zero_bucket_count_lane", "int32_t *zero_bucket_count_lane;"),
        ("candidate_count", "int32_t candidate_count;"),
        ("runtime_row_index", "int32_t runtime_row_index;"),
        (
            "survival_row_index_write",
            "int32_t *survival_row_index_write;",
        ),
        ("parcel_set_id_cursor", "int32_t *parcel_set_id_cursor;"),
        (
            "remaining_candidate_count",
            "int32_t remaining_candidate_count;",
        ),
        ("placed_count", "int32_t placed_count;"),
        ("last_candidate_index", "int32_t last_candidate_index;"),
        (
            "selected_row_index_entry",
            "int32_t *selected_row_index_entry;",
        ),
        (
            "challenge_runtime_row_anchor",
            "RuntimeRowStrideAnchor *challenge_runtime_row_anchor;",
        ),
        ("entries_to_shift", "int32_t entries_to_shift;"),
        ("projection_row", "SubRow *projection_row;"),
        ("projection_scan_index", "int32_t projection_scan_index;"),
        ("path_node", "int32_t path_node;"),
    ):
        assert f'"{name}"' in ida_path_sync
        assert f'"{declaration}"' in ida_path_sync
    assert "_sync_challenge_parcels_runtime_lvars" in ida_path_sync
    assert "CHALLENGE_PARCELS_RUNTIME_ROW_OFFSET_OPERANDS" in ida_path_sync
    for operand_spec in (
        "(0x4442A0, 1, 0x5CCB64)",
        "(0x444323, 1, 0x5CCAC8)",
        "(0x444343, 1, 0x5CCB5C)",
        "(0x44435E, 1, 0x5CCB58)",
        "(0x44437F, 1, 0x5CCB60)",
        "(0x4443D7, 1, 0x5CCAC8)",
    ):
        assert operand_spec in ida_path_sync
    assert (
        "challenge_parcels_runtime_row_offset_operands = "
        "_normalize_root_offset_operands(" in ida_path_sync
    )
    for group_name, operand_spec in (
        ("RUNTIME_ROW_LOOKUP_OFFSET_OPERANDS", "(0x43D49E, 1, 0x5CCAC8)"),
        (
            "PROJECT_ATTACHMENT_RUNTIME_ROW_OFFSET_OPERANDS",
            "(0x4444D4, 1, 0x5CCAC8)",
        ),
        (
            "REMOVE_SUBGAME_BODS_RUNTIME_ROW_OFFSET_OPERANDS",
            "(0x44091F, 1, 0x5CCAD8)",
        ),
        ("MERGE_RUNTIME_ROW_OFFSET_OPERANDS", "(0x4351CB, 1, 0x5CCB7C)"),
    ):
        assert group_name in ida_path_sync
        assert operand_spec in ida_path_sync
    for result_name in (
        "runtime_row_lookup_offset_operands",
        "project_attachment_runtime_row_offset_operands",
        "remove_subgame_bods_runtime_row_offset_operands",
        "merge_runtime_row_offset_operands",
    ):
        assert result_name in ida_path_sync
        assert f'"{result_name}": {result_name}' in ida_path_sync
    assert "PROJECT_ATTACHMENT_LVAR_SPECS" in ida_path_sync
    for definition_address in (
        "0x4444D5",
        "0x4444EB",
        "0x4444F4",
        "0x44451E",
        "0x4445C9",
    ):
        assert definition_address in ida_path_sync
    for name, declaration in (
        ("runtime_row", "SubRow *runtime_row;"),
        (
            "primary_attachment_cell",
            "TrackRowCell *primary_attachment_cell;",
        ),
        (
            "attachment_template_record",
            "Path *attachment_template_record;",
        ),
        ("sample", "PathTemplateSample *sample;"),
        ("projected_position", "Vec3 projected_position;"),
    ):
        assert f'"{name}"' in ida_path_sync
        assert f'"{declaration}"' in ida_path_sync
    assert "_sync_project_attachment_lvars" in ida_path_sync
    assert '"project_attachment_lvars": project_attachment_lvars' in ida_path_sync

    assert "BUILD_SUBGAME_ACTIVE_BOD_LVAR_SPECS" in ida_path_sync
    for definition_address in (
        "0x438335",
        "0x4383A9",
        "0x4383CD",
        "0x4383D3",
        "0x4383F7",
        "0x438408",
        "0x438426",
        "0x43842B",
        "0x43844F",
        "0x438460",
        "0x43847E",
        "0x438483",
        "0x4384A7",
        "0x4384B8",
        "0x4384D6",
        "0x4384DB",
        "0x4384FF",
        "0x438510",
        "0x43852E",
        "0x438533",
        "0x438557",
        "0x438577",
        "0x438595",
        "0x43859A",
        "0x4385BE",
        "0x4385E2",
        "0x4385E7",
        "0x438606",
    ):
        assert definition_address in ida_path_sync
    for name, declaration in (
        ("player", "Player *player;"),
        ("jetpack_channel", "Weapon *jetpack_channel;"),
        ("weapon_channel_0", "Weapon *weapon_channel_0;"),
        ("weapon_channel_1", "Weapon *weapon_channel_1;"),
        ("weapon_channel_2", "Weapon *weapon_channel_2;"),
        ("invincible_shell", "Invincible *invincible_shell;"),
        ("presentation", "Snail *presentation;"),
    ):
        assert f'"{name}"' in ida_path_sync
        assert f'"{declaration}"' in ida_path_sync
    assert "_sync_build_subgame_active_bod_lvars" in ida_path_sync

    assert "_sync_segment_copy_entry_anchor_lvar" in ida_segment_sync
    assert "SEGMENT_COPY_ENTRY_ANCHOR_DEFEA = 0x447372" in ida_segment_sync
    assert '"SegmentCatalogEntryAnchor *selected_entry_anchor;"' in ida_segment_sync
    assert 'info.name = "selected_entry_anchor"' in ida_segment_sync
    assert "_sync_builtin_grid_offset_lvar" in ida_segment_sync
    assert '"int32_t grid_offset;"' in ida_segment_sync
    assert 'info.name = "grid_offset"' in ida_segment_sync
    assert "SEGMENT_IMPORT_LVAR_SPECS" in ida_segment_sync
    for definition_address, stack_offset, name, declaration in (
        ("0x448186", "64", "tracks_after_stack_probe", "SMTracks *"),
        ("0x4481D8", "60", "segment_file_name_cursor", "char *"),
        ("0x448301", "80", "row_index", "int32_t"),
        ("0x448387", "148", "option_text", "char option_text[512]"),
        ("0x4481FB", "788", "file_path", "char file_path[512]"),
        ("0x448223", "1300", "file_buffer", "char file_buffer[4096]"),
        (
            "0x44818B",
            "5396",
            "segment_files",
            "char segment_files[512][128]",
        ),
        (
            "0x448336",
            "None",
            "row_stride_anchor",
            "SegmentCatalogRowStrideAnchor *",
        ),
    ):
        assert definition_address in ida_segment_sync
        assert f"        {stack_offset}," in ida_segment_sync
        assert f'"{name}"' in ida_segment_sync
        assert declaration in ida_segment_sync
    assert "_sync_owned_lvar" in ida_segment_sync
    assert '"segment_import_lvars": segment_import_lvars' in ida_segment_sync
    assert "segment_import_lvar_failures" in ida_segment_sync
    assert "DIRTY_FUNCTIONS" in ida_segment_sync
    assert "ida_hexrays.mark_cfunc_dirty(address, True)" in ida_segment_sync
    for marker in (
        "TemporaryDirectory",
        "shutil.copy2",
        "preview-segment-catalog-types",
        "if preview_exit_code:",
    ):
        assert marker in ida_segment_runner

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
    populate_runtime_rows = (
        repo_root
        / "tools/match/scratches/populate_runtime_track_cells_from_segments/scratch.cpp"
    ).read_text(encoding="utf-8")
    merge_track_tile_runs = (
        repo_root / "tools/match/scratches/merge_track_tile_runs/scratch.cpp"
    ).read_text(encoding="utf-8")
    build_track_fringe_objects = (
        repo_root
        / "tools/match/scratches/build_track_fringe_objects/scratch.cpp"
    ).read_text(encoding="utf-8")
    update_subgoldy = (
        repo_root / "tools/match/scratches/update_subgoldy/scratch.cpp"
    ).read_text(encoding="utf-8")
    place_challenge = (
        repo_root
        / "tools/match/scratches/place_challenge_parcels_on_track/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY" in load_segment
    assert "AUTHORED_SEGMENT_ROW_FLAG_SUPPRESS_TRACK_RENDER" in load_segment
    assert (
        "AUTHORED_SEGMENT_ROW_FLAG_SUPPRESS_TRACK_RENDER"
        in populate_runtime_rows
    )
    assert "SUBROW_FLAG_SUPPRESS_TRACK_RENDER" in populate_runtime_rows
    assert "SUBROW_FLAG_SUPPRESS_TRACK_RENDER" in merge_track_tile_runs
    assert "SUBROW_FLAG_SUPPRESS_TRACK_RENDER" in build_track_fringe_objects
    assert "SUBROW_FLAG_NO_FALL" in update_subgoldy
    assert "SUBROW_FLAG_PARCEL_Z_IS_LOCAL" in place_challenge


def test_parcel_spawn_position_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    matcher_header = (
        repo_root / "tools/match/include/track_attachment_types.h"
    ).read_text(encoding="utf-8")
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    binja_path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    binja_clear_sync = (
        BINJA_DIR / "sync_runtime_grid_clear_lifetimes.py"
    ).read_text(encoding="utf-8")
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    populate_rows = (
        repo_root
        / "tools/match/scratches/populate_runtime_track_cells_from_segments/scratch.cpp"
    ).read_text(encoding="utf-8")
    place_parcels = (
        repo_root / "tools/match/scratches/place_parcels_on_track/scratch.cpp"
    ).read_text(encoding="utf-8")
    place_challenge = (
        repo_root
        / "tools/match/scratches/place_challenge_parcels_on_track/scratch.cpp"
    ).read_text(encoding="utf-8")
    update_subgame = (
        repo_root / "tools/match/scratches/update_subgame/scratch.cpp"
    ).read_text(encoding="utf-8")

    for header in (matcher_header, analysis_header):
        assert "parcel_spawn_position" in header
        assert "projection_payload" not in header

    assert '("0x90", "parcel_spawn_position", "Vec3")' in binja_path_sync
    assert '0x90: ("parcel_spawn_position", "Vec3")' in binja_clear_sync
    assert "runtime_rows[0].parcel_spawn_position.y" in ida_path_sync
    assert "offsetof(SubRow, parcel_spawn_position)" in populate_rows
    assert ".parcel_spawn_position" in place_parcels
    assert ".parcel_spawn_position" in place_challenge
    assert "&runtime_rows[cell_index].parcel_spawn_position" in update_subgame
    assert "spawn_track_parcel(" in update_subgame


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

    paired_consumers = {
        "border_input_text": "FRONTEND_WIDGET_FLAG_TEXT_INPUT_COMPLETE",
        "update_high_score_screen": "FRONTEND_WIDGET_FLAG_TEXT_INPUT_COMPLETE",
        "layout_frontend_widget": "FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN",
        "activate_all_borders": (
            "FRONTEND_WIDGET_FLAG_DISABLED_BEFORE_DEACTIVATION"
        ),
    }
    for function_name, constant in paired_consumers.items():
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
        assert "int32_t level_mode;" in header or "int level_mode;" in header
        assert "runtime_flags" in header
        assert "SubSolution* selected_level_record;" in header

    for sync in (path_sync, runtime_sync):
        assert '("0x00", "scan_reset", "uint8_t")' in sync
        assert '("0x01", "camera_snap_requested", "uint8_t")' in sync
        assert '("0x08", "resume_requested", "uint8_t")' in sync
        assert '("0x0c", "pause_fade", "float")' in sync
        assert '("0x10", "pause_fade_step", "float")' in sync
        assert '("0x14", "sub_pause", "SubPause")' in sync
        assert '("0x20", "runtime_row_scan_begin", "int32_t")' in sync
        assert '("0x24", "runtime_row_scan_end", "int32_t")' in sync

    for field_update in (
        '("0x40", "level_mode", "int32_t")',
        '("0x4c", "runtime_flags", "uint32_t")',
        '("0xff25d0", "selected_level_record_active", "uint8_t")',
        '("0xff25d4", "selected_level_record", "SubSolution*")',
    ):
        assert field_update in runtime_sync

    assert '("0x435df0", "set_subgame_features")' in runtime_sync
    ida_runtime_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    assert '(0x435DF0, "set_subgame_features")' in ida_runtime_sync
    assert "0x435DF0,  # set_subgame_features" in ida_runtime_sync
    assert '(0x437B10, "reset_subgame")' in ida_runtime_sync
    assert "0x437B10,  # reset_subgame" in ida_runtime_sync
    assert (
        "void __thiscall set_subgame_features(SubgameRuntime* runtime);"
        in ida_runtime_sync
    )
    assert (
        "void __thiscall reset_subgame(SubgameRuntime* game);"
        in ida_runtime_sync
    )

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


def test_segment_glyph_normalizer_replay_preserves_subgame_owner_abi() -> None:
    binja_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )

    expected = (
        "char __thiscall normalize_segment_glyph_for_track_flags("
        "SubgameRuntime* runtime, char glyph, int32_t row, char edge_row)"
    )
    assert expected in binja_sync
    assert expected + ";" in ida_sync
    assert "char __thiscall normalize_segment_glyph_for_track_flags(" in path_header
    assert "SubgameRuntime* runtime," in path_header
    assert "0x437270,  # normalize_segment_glyph_for_track_flags" in ida_sync


def test_pause_menu_lifecycle_replay_stays_with_subgame_owner() -> None:
    binja_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in (
            "bn_subgame_runtime_types.h",
            "ida_subgame_runtime_types.h",
        )
    )

    addresses = {
        "uninit_pause_menu": "0x440600",
        "initialize_pause_menu": "0x440660",
        "update_pause_menu": "0x4407a0",
    }
    for name, address in addresses.items():
        prototype = f"void __thiscall {name}(SubPause* pause)"
        assert f'("{address}", "{name}")' in binja_sync
        assert prototype in binja_sync
        assert prototype + ";" in ida_sync
        assert f"{address.upper().replace('X', 'x')},  # {name}" in ida_sync
        for header in headers:
            assert prototype + ";" in header


def test_sub_ring_kind_boundary_and_state_ownership_stay_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    pool_sync = (BINJA_DIR / "sync_subgame_pool_types.py").read_text(
        encoding="utf-8"
    )
    particle_lifetime_sync = (
        BINJA_DIR / "sync_ring_particle_lifetimes.py"
    ).read_text(encoding="utf-8")
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    collision_state_sync = (
        BINJA_DIR / "sync_collision_state_lifetimes.py"
    ).read_text(encoding="utf-8")
    ida_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
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
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    assert '"SubRingState",' in pool_sync
    assert '"SubRingKind",' in pool_sync
    assert '("0x00", "body", "RenderableBod")' in pool_sync
    assert '("0x80", "state", "SubRingState")' in pool_sync
    assert '("0x88", "kind", "SubRingKind")' in pool_sync
    assert "int32_t requested_kind" in pool_sync
    assert "current_type_widths" in particle_lifetime_sync
    assert "current_struct_fields_batch" in particle_lifetime_sync
    assert "RING_PARTICLE_USER_VAR_UPDATES" in particle_lifetime_sync
    assert '"Vec3": 0x0C' in particle_lifetime_sync
    assert '"TransformMatrix": 0x40' in particle_lifetime_sync
    assert '"RenderableBod": 0x80' in particle_lifetime_sync
    assert '"Sprite": 0xB4' in particle_lifetime_sync
    assert '0x48: ("position", "Vec3")' in particle_lifetime_sync
    assert '0x38: ("transform", "TransformMatrix")' in particle_lifetime_sync
    assert '"SubRingStar": 0x20' in particle_lifetime_sync
    assert '"SubRingStarPositionCursor": 0x18' in particle_lifetime_sync
    assert '0x0C: ("phase", "float")' in particle_lifetime_sync
    assert '0x10: ("phase_step", "float")' in particle_lifetime_sync
    assert '0x14: ("radius", "float")' in particle_lifetime_sync
    assert '"SubRing": 0x1F8' in particle_lifetime_sync
    assert '"SubRingPool": 0x3F0' in particle_lifetime_sync
    assert '0x90: ("particles", "SubRingStar[10]")' in particle_lifetime_sync
    for index, storage, name, type_name in (
        (91, 66, "parent_position", "Vec3*"),
        (94, 67, "sprite_position", "Vec3*"),
        (142, 66, "result_parent", "SubRing*"),
    ):
        expected = (
            '"update_ring_or_special_effect_particle",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in particle_lifetime_sync
    assert (
        '"initialize_ring_or_special_effect_particles",\n'
        '        "RegisterVariableSourceType",\n'
        '        44,\n'
        '        69,\n'
        '        "particle_position_cursor",\n'
        '        "SubRingStarPositionCursor*"'
        in particle_lifetime_sync
    )
    assert (
        '"initialize_ring_or_special_effect_particles",\n'
        '        "RegisterVariableSourceType",\n'
        '        34,\n'
        '        72,\n'
        '        "particle",\n'
        '        "SubRingStar*"'
        in particle_lifetime_sync
    )
    assert (
        '"initialize_ring_or_special_effect_particles",\n'
        '        "RegisterVariableSourceType",\n'
        '        427,\n'
        '        68,\n'
        '        "sprite_position",\n'
        '        "Vec3*"'
        in particle_lifetime_sync
    )
    for index, storage, name, type_name in (
        (199, 73, "active_particle_cursor", "SubRingStar*"),
        (356, 72, "active_cleanup_particle", "SubRingStar*"),
        (464, 73, "collect_particle_cursor", "SubRingStar*"),
        (630, 72, "collect_cleanup_particle", "SubRingStar*"),
        (797, 72, "collect_base_position", "Vec3*"),
        (875, 73, "expand_particle_cursor", "SubRingStar*"),
        (1041, 72, "expand_cleanup_particle", "SubRingStar*"),
        (1093, 72, "expand_base_position", "Vec3*"),
    ):
        expected = (
            '"update_ring_or_special_effect_parent",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in particle_lifetime_sync
    assert '"SubRingState",' in path_sync
    assert '"SubRingKind",' in path_sync
    for index, storage, name, type_name in (
        (2346, 67, "ring_state", "SubRingState"),
        (2516, 66, "ring_kind", "SubRingKind"),
        (2573, 66, "effect_kind", "SubRingKind"),
    ):
        expected = (
            '"handle_subgoldy_collisions",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in collision_state_sync

    for fragment in (
        "struct Vec3* sprite_position = &particle->sprite->position",
        "sprite_position->x = ring->body.transform.position.x",
        "sprite_position->y = ring->body.transform.position.y",
        "sprite_position->z = ring->body.transform.position.z",
        "SubRingPositionAdvanceCursor *parent_position_cursor",
        "parent_position_cursor->position_x_before_advance",
        "parent_position_cursor->position_y_after_advance",
        "parent_position_cursor->position_z_after_advance",
        '"int32_t* edx_10"',
        '"edx_10[1]"',
        '"edx_10[2]"',
    ):
        assert fragment in health_checks

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
    for header in analysis_headers:
        assert "RenderableBod body;" in header
    assert "SubRingPositionAdvanceCursor" in path_header
    assert "RING_PARTICLE_POSITION_CURSOR_LVAR_SPECS" in ida_path_sync
    assert "parent_position_cursor" in ida_path_sync
    assert "SubRingPool ring_effects;" in path_header
    for header in analysis_headers:
        assert "int32_t requested_kind" in header
    assert "int requested_kind" in (
        repo_root / "tools/match/include/subgame_runtime.h"
    ).read_text(encoding="utf-8")
    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"' in ida_runner
    for prototype in (
        "SubRing* __thiscall initialize_track_ring_or_special_effect_runtime",
        "void __thiscall spawn_track_ring_or_special_effect",
        "void __thiscall initialize_ring_or_special_effect_particles",
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


def test_crslug_owner_replays_across_analysis_lanes() -> None:
    repo_root = Path(__file__).parents[1]
    pool_sync = (BINJA_DIR / "sync_subgame_pool_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    collision_state_sync = (
        BINJA_DIR / "sync_collision_state_lifetimes.py"
    ).read_text(encoding="utf-8")
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("bn_subgame_pool_types.h", "path_template_types.h")
    )
    matcher_header = (
        repo_root / "tools/match/include/slug_hazard_types.h"
    ).read_text(encoding="utf-8")

    assert '"Slug",' in pool_sync
    assert '"SlugPool",' in pool_sync
    assert '("Slug", SLUG_FIELD_UPDATES)' in pool_sync
    assert '("0x00", "body", "RenderableBod")' in pool_sync
    assert "SlugHazardRuntime*" not in pool_sync
    assert "void __thiscall update_slug_hazard_ai(Slug* slug)" in pool_sync
    assert "void __fastcall update_slug_hazard_ai(Slug* slug)" not in pool_sync
    assert "DEFERRED_PROTO_UPDATES" not in pool_sync
    assert "report_deferred_prototypes" not in pool_sync
    assert "SPAWN_SLUG_HAZARD_USER_VAR_UPDATES" in pool_sync
    assert '"slug_state_cursor",\n        "SlugStateStrideCursor*"' in pool_sync
    assert '"slug_slot_cursor",\n        "SlugSlotCursor*"' in pool_sync
    assert '"blink_random_value",\n        "int32_t"' in pool_sync
    assert (
        '"handle_subgoldy_collisions",\n        "RegisterVariableSourceType",\n'
        '        821,\n        67,\n        "slug_state",\n        "SubSlugState"'
        in collision_state_sync
    )
    assert "apply_user_var_updates" in pool_sync
    assert "current_type_widths" in pool_sync
    assert "current_enum_members" in pool_sync
    assert "SLUG_ENUM_TYPE_REPLACEMENTS" in pool_sync
    assert "EXPECTED_SLUG_ENUM_MEMBERS" in pool_sync
    assert "struct_exists" not in pool_sync
    assert '("0x80", "state", "SubSlugState")' in pool_sync
    assert (
        '("0x84", "death_toss_direction", "SubSlugDeathTossDirection")'
        in pool_sync
    )
    for offset, name in (
        ("0x9c", "death_toss_progress"),
        ("0xa0", "death_toss_progress_step"),
        ("0xa4", "death_toss_secondary_progress"),
        ("0xa8", "death_toss_secondary_progress_step"),
    ):
        assert f'("{offset}", "{name}", "float")' in pool_sync
        assert f'("{offset}", "{name}", "float")' in path_sync
    assert '("SlugStateStrideCursor", SLUG_STATE_CURSOR_FIELD_UPDATES)' in pool_sync

    for header in (*analysis_headers, matcher_header):
        assert "Slug slots[SUB_SLUG_SLOT_CAPACITY]" in header
        assert "float death_toss_progress;" in header
        assert "float death_toss_progress_step;" in header
        assert "float death_toss_secondary_progress;" in header
        assert "float death_toss_secondary_progress_step;" in header
        assert "unknown_9c[0xac - 0x9c]" not in header
        assert "SUB_SLUG_STATE_INACTIVE = 0" in header
        assert "SUB_SLUG_STATE_ACTIVE = 1" in header
        assert "SUB_SLUG_STATE_DEATH_TOSS_PENDING = 2" in header
        assert "SUB_SLUG_STATE_TEARDOWN_PENDING = 3" in header
        assert "SUB_SLUG_STATE_LATERAL_ACTIVE = 4" in header
        assert "SUB_SLUG_DEATH_TOSS_RIGHT = 1" in header
        assert "SUB_SLUG_DEATH_TOSS_LEFT = 2" in header
        assert "SubSlugState state;" in header
        assert "SubSlugDeathTossDirection death_toss_direction;" in header

    for header in analysis_headers:
        assert "typedef struct Slug" in header
        assert "typedef enum SubSlugState" in header
        assert "typedef enum SubSlugDeathTossDirection" in header
        assert "RenderableBod body;" in header
        assert "typedef struct SlugHazardRuntime" not in header
        assert "typedef struct SlugStateStrideCursor" in header
        assert "uint8_t slot_stride_tail[0xe8];" in header
        assert (
            "typedef struct SlugStateStrideCursor {\n    SubSlugState state;"
            in header
        )
        assert "typedef struct SlugSlotCursor" in header
        assert "uint8_t subgame_prefix[0x3563a0];" in header
        assert "Slug slug;" in header

    for function_name in (
        "initialize_slug_hazard_runtime",
        "spawn_slug_hazard",
        "update_slug_voice_ai",
        "play_slug_voice",
        "hit_slug_hazard",
        "explode_slug_hazard",
        "kill_slug_hazard",
        "update_slug_hazard_ai",
    ):
        assert function_name in pool_sync
        assert function_name in ida_sync
    assert (
        "void __thiscall spawn_slug_hazard(SubgameRuntime* game, "
        "TrackRowCell* cell, Player* owner_player)"
        in pool_sync
    )
    assert (
        "void __thiscall spawn_slug_hazard(SubgameRuntime* game, "
        "TrackRowCell* cell, Player* owner_player);"
        in ida_sync
    )
    assert "void spawn_slug_hazard(SubLoc* cell, Player* owner_player);" in (
        repo_root / "tools/match/include/subgame_runtime.h"
    ).read_text(encoding="utf-8")
    assert "SPAWN_SLUG_HAZARD_LVAR_SPECS" in ida_sync
    assert "0x43DC89" in ida_sync
    assert "0x43DCBD" in ida_sync
    assert "0x43DDC8" in ida_sync
    assert '"slug_state_cursor"' in ida_sync
    assert '"SlugStateStrideCursor"' in ida_sync
    assert '"slug_slot_cursor"' in ida_sync
    assert '"SlugSlotCursor"' in ida_sync
    assert '"sprite"' in ida_sync
    assert '"Sprite"' in ida_sync
    assert "SlugHazardRuntime*" not in ida_sync
    assert "SLUG_OWNER_EXPECTED_SIZE = 0xEC" in ida_sync
    assert "SLUG_POOL_EXPECTED_SIZE = 0x760" in ida_sync
    assert "SLUG_STATE_CURSOR_EXPECTED_SIZE = 0xEC" in ida_sync
    assert '(0x80, 4, "state", "SubSlugState")' in ida_sync
    assert (
        '(0x84, 4, "death_toss_direction", "SubSlugDeathTossDirection")'
        in ida_sync
    )
    assert "slug_owner_readback = _slug_owner_readback()" in ida_sync
    for type_name in (
        "SubSlugState",
        "SubSlugDeathTossDirection",
        "Slug",
        "SlugStateStrideCursor",
    ):
        assert f'"{type_name}",' in path_sync
    assert '("Slug", SLUG_FIELD_UPDATES)' in path_sync
    assert (
        '("SlugStateStrideCursor", SLUG_STATE_CURSOR_FIELD_UPDATES)'
        in path_sync
    )
    assert (
        '"handle_subgoldy_collisions",\n        "RegisterVariableSourceType",\n'
        '        821,\n        67,\n        "slug_state",\n        "SubSlugState"'
        in collision_state_sync
    )
    collision_scratch = (
        repo_root
        / "tools/match/scratches/handle_subgoldy_collisions/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert (
        "SubSlugState state = game->slug_hazards.slots[m].state;"
        in collision_scratch
    )
    assert "Slug* slug =" not in collision_scratch
    assert "int state;" not in matcher_header
    assert "int death_toss_direction;" not in matcher_header


def test_parcel_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    runtime_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    collision_state_sync = (
        BINJA_DIR / "sync_collision_state_lifetimes.py"
    ).read_text(encoding="utf-8")
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
    assert (
        '"handle_subgoldy_collisions",\n'
        '        "RegisterVariableSourceType",\n'
        '        1388,\n'
        '        67,\n'
        '        "parcel_state",\n'
        '        "ParcelState"'
        in collision_state_sync
    )
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


def test_parcel_manager_replay_owns_fixed_pool_lifecycle_and_consumers() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in (
            "bn_subgame_runtime_types.h",
            "ida_subgame_runtime_types.h",
            "path_template_types.h",
        )
    )
    matcher_header = (
        repo_root / "tools/match/include/track_parcel_runtime.h"
    ).read_text(encoding="utf-8")

    lifecycle = (
        (0x408860, "initialize_track_parcel_runtime"),
        (0x443130, "update_track_parcels"),
        (0x443160, "initialize_track_parcel_slots"),
        (0x443190, "allocate_track_parcel_slot"),
        (0x4431D0, "update_track_parcel"),
        (0x443730, "spawn_track_parcel"),
    )
    for address, name in lifecycle:
        assert f'("{address:#x}", "{name}")' in binja_sync
        assert f'(0x{address:X}, "{name}")' in ida_sync

    for header in (*analysis_headers, matcher_header):
        assert "Parcel_must_be_0x8c" in header
        assert "ParcelManager_must_be_0x1b58" in header

    assert "current_struct_size" in binja_sync
    assert '"Parcel": 0x8C' in binja_sync
    assert '"ParcelManager": 0x1B58' in binja_sync
    assert "EXPECTED_PARCEL_OWNER_SIZES" in ida_sync
    assert '"Parcel": 0x8C' in ida_sync
    assert '"ParcelManager": 0x1B58' in ida_sync

    for address in (
        0x404CF0,  # update_row_event_display
        0x408060,  # initialize_runtime_pools_and_path_template_bank
        0x437EB0,  # build_subgame_level
        0x438B90,  # update_subgame
        0x43B120,  # update_subgoldy
        0x444CF0,  # handle_subgoldy_collisions
    ):
        assert f"0x{address:X}" in ida_sync


def test_parcel_bucket_banks_have_one_shared_cross_decompiler_owner() -> None:
    header = (HEADER_DIR / "parcel_bucket_types.h").read_text(encoding="utf-8")
    path_header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")
    binja_sync = (BINJA_DIR / "sync_parcel_bucket_types.py").read_text(
        encoding="utf-8"
    )
    ida_apply = (IDA_DIR / "apply_parcel_bucket_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "sync_parcel_bucket_types.py").read_text(
        encoding="utf-8"
    )
    path_binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    path_ida_apply = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )

    for declaration in (
        "#define PARCEL_BUCKET_CAPACITY 0x800",
        "#define PARCEL_CANDIDATE_CAPACITY 0x20",
        "#define SURVIVAL_PARCEL_GROUP_CAPACITY 0x1000",
        "typedef struct ParcelCandidate",
        "int32_t row;",
        "Vec3 position;",
        "typedef struct __ptr_offset(0x04)",
        "__base(Vec3, 0x04) ParcelCandidatePositionCursorView",
        "__inherited Vec3 position;",
        "typedef struct ParcelBucket",
        "ParcelCandidate candidates[PARCEL_CANDIDATE_CAPACITY];",
        "int32_t candidate_count;",
        "int32_t set_id;",
        "int32_t segment_index;",
        "typedef struct ParcelBucketCountLane",
        "char stride_overlap[0x208];",
    ):
        assert declaration in header

    for source in (binja_sync, ida_apply):
        for address, name in (
            ("53d190", "g_zero_parcel_buckets"),
            ("643390", "g_zero_parcel_bucket_count_lane_end"),
            ("6447e8", "g_parcel_group_survival_0"),
            ("6487e8", "g_parcel_set_buckets"),
        ):
            assert address.lower() in source.lower()
            assert name in source
        assert "ParcelBucket" in source
        assert "place_parcels_on_track" in source
        assert "place_challenge_parcels_on_track" in source

    assert 'LEGACY_WIDE_DATA_VAR_REMOVALS = (' in binja_sync
    assert '("0x53d190", "ParcelBucket[0x800]")' in binja_sync
    assert '("0x6487e8", "ParcelBucket[0x800]")' in binja_sync
    assert 'NARROW_PARCEL_DATA_VAR_UPDATES = (' in binja_sync
    assert '("0x53d190", "ParcelBucket")' in binja_sync
    assert '("0x6487e8", "ParcelBucket")' in binja_sync
    assert '("0x6447e8", "int32_t[0x1000]")' in binja_sync
    assert '"ParcelBucketCountLane": 0x20C' in binja_sync
    assert '"ParcelCandidatePositionCursorView": 0x10' in binja_sync
    assert "apply_data_var_removals" in binja_sync
    assert "apply_data_var_updates" in binja_sync
    assert "g_zero_parcel_bucket_count_lane_end" not in binja_sync.split(
        "DATA_VAR_UPDATES", 1
    )[1].split("PROTO_UPDATES", 1)[0]

    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/parcel_bucket_types.h"' in ida_sync
    assert "shutil.copy2(db_path, preview_db_path)" in ida_sync
    assert "if preview_exit_code:" in ida_sync
    assert "g_zero_parcel_bucket_count_lane_end" not in ida_apply.split(
        "TRUSTED_DATA_DECLARATIONS", 1
    )[1].split("TRUSTED_FUNCTION_DECLARATIONS", 1)[0]
    assert "CURSOR_LVAR_SPECS = (" in ida_apply
    assert '"parcel_set_candidate_position"' in ida_apply
    assert (
        "Vec3 *__shifted(ParcelCandidatePositionCursorView, 0x04)" in ida_apply
    )
    assert "0x443D80" in ida_apply

    for source in (binja_sync, path_binja_sync):
        assert (
            "void __thiscall place_parcels_on_track(SubgameRuntime* game)" in source
        )
        assert (
            "void __thiscall "
            "place_challenge_parcels_on_track(SubgameRuntime* game)" in source
        )
        assert "int32_t __thiscall place_parcels_on_track" not in source
        assert "int32_t __thiscall place_challenge_parcels_on_track" not in source

    assert (
        "void __thiscall place_parcels_on_track(SubgameRuntime* game);" in path_header
    )
    assert (
        "void __thiscall place_challenge_parcels_on_track(SubgameRuntime* game);"
        in path_header
    )
    assert "int32_t __thiscall place_parcels_on_track" not in path_header
    assert "int32_t __thiscall place_challenge_parcels_on_track" not in path_header

    for source in (ida_apply, path_ida_apply):
        assert "void __thiscall place_parcels_on_track(SubgameRuntime" in source
        assert (
            "void __thiscall place_challenge_parcels_on_track(SubgameRuntime"
            in source
        )
        assert "int32_t __thiscall place_parcels_on_track" not in source
        assert "int32_t __thiscall place_challenge_parcels_on_track" not in source


def test_parcel_bucket_lifetime_replay_stays_guarded() -> None:
    source = (BINJA_DIR / "sync_parcel_bucket_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("ParcelCandidate", "0x10"),
        ("ParcelCandidatePositionCursorView", "0x10"),
        ("ParcelBucket", "0x20C"),
        ("ParcelBucketCountLane", "0x20C"),
    ):
        assert f'"{type_name}": {width}' in source

    for owner, offset, field, field_type in (
        ("ParcelCandidate", "0x00", "row", "int32_t"),
        ("ParcelCandidate", "0x04", "position", "Vec3"),
        (
            "ParcelCandidatePositionCursorView",
            "0x00",
            "row",
            "int32_t",
        ),
        ("ParcelBucket", "0x000", "candidates", "ParcelCandidate[32]"),
        ("ParcelBucket", "0x200", "candidate_count", "int32_t"),
        ("ParcelBucket", "0x204", "set_id", "int32_t"),
        ("ParcelBucket", "0x208", "segment_index", "int32_t"),
        ("ParcelBucketCountLane", "0x000", "candidate_count", "int32_t"),
        ("ParcelBucketCountLane", "0x004", "stride_overlap", "char[520]"),
    ):
        assert f'"{owner}": {{' in source
        assert f'{offset}: ("{field}", "{field_type}")' in source

    for index, storage, name, var_type in (
        (
            1183,
            69,
            "parcel_set_candidate_position",
            "ParcelCandidatePositionCursorView*",
        ),
        (1494, 67, "destination_candidate", "ParcelCandidate*"),
        (1500, 72, "source_candidate", "ParcelCandidate*"),
        (1506, 73, "destination_candidate_write", "ParcelCandidate*"),
        (1875, 67, "zero_candidate_position", "Vec3*"),
        (1972, 66, "zero_destination_bucket", "ParcelBucket*"),
        (1986, 72, "zero_source_bucket", "ParcelBucket*"),
    ):
        expected = (
            '"place_parcels_on_track",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{var_type}",'
        )
        assert expected in source

    for source_type, index, storage, name, var_type in (
        (
            "RegisterVariableSourceType",
            53,
            66,
            "zero_bucket_count_lane",
            "ParcelBucketCountLane*",
        ),
        ("RegisterVariableSourceType", 79, 72, "candidate_count", "int32_t"),
        ("RegisterVariableSourceType", 81, 66, "runtime_row_index", "int32_t"),
        (
            "RegisterVariableSourceType",
            91,
            68,
            "survival_row_index_write",
            "int32_t*",
        ),
        (
            "StackVariableSourceType",
            83,
            -72,
            "remaining_candidate_count",
            "int32_t",
        ),
        ("RegisterVariableSourceType", 146, 73, "placed_count", "int32_t"),
        (
            "RegisterVariableSourceType",
            156,
            69,
            "last_candidate_index",
            "int32_t",
        ),
        ("RegisterVariableSourceType", 194, 66, "picked_index", "int32_t"),
        (
            "RegisterVariableSourceType",
            199,
            67,
            "selected_runtime_row_index",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            206,
            72,
            "selected_row_index_entry",
            "int32_t*",
        ),
        (
            "StackVariableSourceType",
            393,
            -72,
            "projection_scan_index",
            "int32_t",
        ),
    ):
        expected = (
            '"place_challenge_parcels_on_track",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{var_type}",'
        )
        assert expected in source

    assert "verify_owner_layouts(args.target)" in source
    assert "apply_user_var_updates(" in source
    assert "apply_split_user_var_update" not in source


def test_track_colour_banks_replay_semantic_owners_without_collapsing_slide() -> None:
    repo_root = Path(__file__).parents[1]
    header = (HEADER_DIR / "track_colour_bank_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/track_colour_banks.h"
    ).read_text(encoding="utf-8")
    binja_sync = (BINJA_DIR / "sync_track_colour_bank_types.py").read_text(
        encoding="utf-8"
    )
    ida_apply = (IDA_DIR / "apply_track_colour_bank_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "sync_track_colour_bank_types.py").read_text(
        encoding="utf-8"
    )
    references = json.loads(
        (repo_root / "analysis/symbols/gameplay-references.json").read_text(
            encoding="utf-8"
        )
    )["symbols"]
    by_address = {entry["address"].lower(): entry for entry in references}

    for source in (header, matcher_header):
        assert "TrackFloorSlideColourBanks" in source
        assert "floor[TRACK_COLOUR_BANK_CAPACITY]" in source
        assert "slide_0[TRACK_COLOUR_BANK_CAPACITY]" in source
        assert "g_loc_colour_lookup_floor_slide_0" in source
        assert "g_loc_colour_lookup_slide_1" in source

    expected_names = {
        "0x53c800": "g_loc_colour_lookup_path_worm",
        "0x53cb30": "g_loc_colour_lookup_slide_1",
        "0x53ce60": "g_loc_colour_lookup_wall",
        "0x643198": "g_loc_colour_lookup_path_warp",
        "0x6434c8": "g_loc_colour_lookup_trampoline",
        "0x6437f8": "g_loc_colour_lookup_floor_slide_0",
        "0x643b28": "g_loc_colour_lookup_slide_0",
        "0x643e58": "g_loc_colour_lookup_path",
        "0x644188": "g_loc_colour_lookup_empty",
        "0x6444b8": "g_loc_colour_lookup_ramp",
        "0x74e7e8": "g_loc_colour_lookup_check_black",
    }
    for address, name in expected_names.items():
        assert by_address[address]["name"] == name
        assert address.removeprefix("0x") in binja_sync.lower()
        assert address.removeprefix("0x") in ida_apply.lower()
        assert name in binja_sync
        assert name in ida_apply

    assert by_address["0x6437f8"]["size"] == "0x660"
    assert by_address["0x643b28"]["kind"] == "offset"
    assert by_address["0x643b28"]["size"] == "0x330"
    assert "FUNCTION_SYMBOL_UPDATES = (" in binja_sync
    assert '("0x434980", "initialize_track_colour_bank_a_thunk")' in binja_sync
    assert '("0x435d40", "build_track_colours")' in binja_sync
    assert "TRUSTED_FUNCTION_NAMES = (" in ida_apply
    assert '(0x434980, "initialize_track_colour_bank_a_thunk")' in ida_apply
    assert '(0x435D40, "build_track_colours")' in ida_apply
    for source in (binja_sync, ida_apply):
        assert "void __cdecl {name}" in source
        assert "void __thiscall build_track_colours(SubgameRuntime" in source
    assert "apply_struct_and_proto_updates" in binja_sync
    assert "TRUSTED_FUNCTION_DECLARATIONS = tuple(" in ida_apply
    assert 'FUNCTION_MANIFEST_PATH = REPO_ROOT / "analysis/symbols/gameplay-functions.json"' in ida_apply
    assert "ida_funcs.set_func_cmt(function, description, True)" in ida_apply
    assert '("0x6437f8", "TrackFloorSlideColourBanks")' in binja_sync
    assert '("0x643b28", "tColour")' not in binja_sync
    assert 'INTERIOR_FIELD = (0x643B28, "g_loc_colour_lookup_slide_0")' in ida_apply
    assert '(0x643B28, "g_loc_colour_lookup_slide_0"),' not in ida_apply.split(
        "TRUSTED_NAMES", 1
    )[1].split("INTERIOR_FIELD", 1)[0]
    assert "g_loc_colour_lookup_slide_0" not in ida_apply.split(
        "TRUSTED_DATA_DECLARATIONS", 1
    )[1].split("DIRTY_FUNCTIONS", 1)[0]
    assert "shutil.copy2(db_path, preview_db_path)" in ida_sync
    assert "if preview_exit_code:" in ida_sync

    for stale in (
        "extern tColour g_track_colour_bank_a",
        "extern tColour g_track_colour_banks_b_c",
        "extern tColour g_track_colour_bank_d",
    ):
        assert stale not in matcher_header


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
        assert "FrontendWidget* title_widget;" in header
        assert "FrontendWidget* delivered_count_widget;" in header
        assert "FrontendWidget* bonus_summary_widget;" in header
        assert "FrontendWidget* bonus_icon_widget;" in header
        assert "FrontendWidget* continue_widget;" in header
        assert "fast_forward_enabled" in header
        for stale_declaration in (
            "    FrontendWidget* widget_a;\n",
            "    FrontendWidget* bonus_widget;\n",
            "    FrontendWidget* widget_d;\n",
            "    uint8_t gate_18;\n",
            "        unsigned char gate_18;\n",
        ):
            assert stale_declaration not in header

    for offset, field_name, field_type in (
        ("0x00", "title_widget", "FrontendWidget*"),
        ("0x04", "delivered_count_widget", "FrontendWidget*"),
        ("0x08", "bonus_summary_widget", "FrontendWidget*"),
        ("0x0c", "bonus_icon_widget", "FrontendWidget*"),
        ("0x10", "continue_widget", "FrontendWidget*"),
        ("0x18", "fast_forward_enabled", "uint8_t"),
    ):
        assert (
            f'("{offset}", "{field_name}", "{field_type}")'
            in runtime_sync
        )

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


def test_completion_replay_uses_the_canonical_subgame_owner() -> None:
    binja_runtime_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_apply = (IDA_DIR / "apply_completion_screen_types.py").read_text(
        encoding="utf-8"
    )
    ida_runner = (IDA_DIR / "sync_completion_screen_types.py").read_text(
        encoding="utf-8"
    )

    assert not (HEADER_DIR / "completion_screen_types.h").exists()
    assert "path_template_types.h" in ida_runner
    assert "completion_screen_types.h" not in ida_runner
    assert "sync_game_root_owner_graph(require=True)" in ida_apply
    assert '"Completion": 0x50' in ida_apply
    assert '"SubSolution": 0x1FAC0' in ida_apply
    assert '"SubgameRuntime": 0x1272838' in ida_apply
    assert "ida_hexrays.mark_cfunc_dirty(address, True)" in ida_apply
    assert "idc.save_database(idc.get_idb_path(), 0)" in ida_apply
    assert "INITIALIZER_COLOR_DEFINITION_ADDRESS = 0x404A5F" in ida_apply
    assert "INITIALIZER_COLOR_STACK_OFFSET = 48" in ida_apply
    assert "_sync_initializer_color_lvar()" in ida_apply

    completion_methods = (
        "flush_row_event_display",
        "initialize_completion_screen",
        "update_row_event_display",
        "register_parcel_delivery",
    )
    for method in completion_methods:
        assert method in ida_apply
        assert method in binja_runtime_sync

    for unrelated_exit_method in (
        "destroy_completion_screen",
        "initialize_exit_prompt",
        "update_completion_screen",
    ):
        assert unrelated_exit_method not in ida_apply

    assert "COMPLETION_REANALYSIS_FUNCTIONS" in binja_runtime_sync
    assert "reanalyze_functions(" in binja_runtime_sync


def test_times_up_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    runtime_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_runtime_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
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
    for replay in (runtime_sync, ida_runtime_sync):
        assert "void __thiscall update_times_up(TimesUp* times_up)" in replay
        assert "void __thiscall uninit_times_up(TimesUp* times_up)" in replay
        assert "void __thiscall show_times_up_message(TimesUp* times_up)" in replay
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
    collision_state_sync = (
        BINJA_DIR / "sync_collision_state_lifetimes.py"
    ).read_text(encoding="utf-8")
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
    assert (
        'SUB_SPEEDUP_FIELD_UPDATES = (\n    ("0x00", "body", "RenderableBod")'
        in pool_sync
    )
    assert '("0x355db0", "speedup_pickup", "SubSpeedUp")' in pool_sync
    assert '("0x356000", "health_pickups", "SubHealth[0x8]")' in pool_sync
    assert '("JetPack", JETPACK_FIELD_UPDATES)' in runtime_sync
    assert '("0x38", "state", "TrackPickupState")' in runtime_sync
    assert '"TrackPickupState",' in path_sync
    assert (
        '"handle_subgoldy_collisions",\n'
        '        "RegisterVariableSourceType",\n'
        '        1666,\n'
        '        67,\n'
        '        "health_state",\n'
        '        "TrackPickupState"'
        in collision_state_sync
    )
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
        assert "typedef struct SubSpeedUp {\n    RenderableBod body;" in header
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


def test_pickup_list_replay_keeps_the_intrusive_owner_graph() -> None:
    replay = (BINJA_DIR / "sync_pickup_list_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for struct_name, offset, field_name, field_type in (
        ("BodNode", "0x04", "list_flags", "uint32_t"),
        ("BodNode", "0x08", "list_prev", "BodNode*"),
        ("BodNode", "0x0C", "list_next", "BodNode*"),
        ("BodList", "0x04", "first", "BodNode*"),
        ("GameRoot", "0x05A8", "active_bod_list", "BodList"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for function_name, index, storage, name, type_name in (
        (
            "spawn_track_health_pickup",
            168,
            67,
            "bod_list_first_ref",
            "BodNode**",
        ),
        ("spawn_track_health_pickup", 199, 68, "old_first", "BodNode*"),
        ("spawn_track_health_pickup", 201, 71, "inserted_node", "BodNode*"),
        ("spawn_track_health_pickup", 207, 68, "old_first_reload", "BodNode*"),
        (
            "spawn_track_health_pickup",
            213,
            68,
            "inserted_node_reload",
            "BodNode*",
        ),
        ("spawn_track_health_pickup", 189, 67, "installed_first", "BodNode*"),
        (
            "spawn_track_jetpack_pickup",
            233,
            66,
            "bod_list_first_ref",
            "BodNode**",
        ),
    ):
        expected = (
            f'        "{function_name}",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "apply_user_var_updates" in replay
    assert "current_struct_fields_batch" in replay
    assert "SubHealth**" not in replay
    assert "JetPack**" not in replay


def test_sub_lazer_and_salt_owner_replays_stay_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    hazard_sync = (BINJA_DIR / "sync_subgame_hazard_pool_types.py").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_runtime_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in (
            "bn_subgame_hazard_pool_types.h",
            "path_template_types.h",
        )
    )
    matcher_sub_lazer = (
        repo_root / "tools/match/include/sub_lazer_types.h"
    ).read_text(encoding="utf-8")
    matcher_salt = (
        repo_root / "tools/match/include/salt_hazard_types.h"
    ).read_text(encoding="utf-8")
    salt_scratches = {
        name: (
            repo_root / f"tools/match/scratches/{name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        for name in (
            "initialize_salt_hazard_pool",
            "spawn_salt_hazard",
            "update_salt_hazard",
            "handle_subgoldy_collisions",
        )
    }

    for header in analysis_headers:
        assert "typedef struct SubLazer {" in header
        assert "typedef SubLazer SubLazerSlot;" in header
        assert "typedef struct Salt {" in header
        assert "typedef Salt SaltHazardSlot;" in header
        assert header.count("RenderableBod body;") >= 2
        assert "SubLazer slots[SUB_LAZER_SLOT_CAPACITY];" in header
        assert "typedef enum SubLazerState {" in header
        assert "SUB_LAZER_STATE_INACTIVE = 0" in header
        assert "SUB_LAZER_STATE_ACTIVE = 1" in header
        assert "SUB_LAZER_STATE_RECYCLE_PENDING = 2" in header
        assert "SubLazerState state;" in header
        assert "Salt slots[40];" in header
        assert "typedef enum SaltState {" in header
        assert "SALT_STATE_INACTIVE = 0" in header
        assert "SALT_STATE_ACTIVE = 1" in header
        assert "SALT_STATE_RECYCLE_PENDING = 2" in header
        assert "SaltState state;" in header
        assert "typedef struct SaltStateStrideCursor {" in header
        assert "uint8_t slot_stride_tail[0x94];" in header
        assert "float fade_alpha;" in header
        assert "float spawn_velocity_y;" in header
        assert "uint8_t collision_armed;" in header

    assert '("0x00", "body", "RenderableBod")' in hazard_sync
    assert '("SubLazer", SUB_LAZER_FIELD_UPDATES)' in hazard_sync
    assert '("0x80", "state", "SubLazerState")' in hazard_sync
    assert '("Salt", SALT_FIELD_UPDATES)' in hazard_sync
    assert '("0x80", "state", "SaltState")' in hazard_sync
    assert (
        '("SaltStateStrideCursor", SALT_STATE_CURSOR_FIELD_UPDATES)'
        in hazard_sync
    )
    assert (
        'HAZARD_STATE_TYPE_REPLACEMENTS = ("SubLazerState", "SaltState")'
        in hazard_sync
    )
    assert 'HAZARD_CURSOR_TYPES = ("SaltStateStrideCursor",)' in hazard_sync
    assert "include_types=HAZARD_CURSOR_TYPES" in hazard_sync
    assert "apply_user_var_updates" in hazard_sync
    assert "HAZARD_USER_VAR_UPDATES" in hazard_sync
    assert (
        '"deactivate_sub_lazer_projectile",\n'
        '        "RegisterVariableSourceType",\n'
        "        6,\n"
        "        72,\n"
        '        "sub_lazer_1",\n'
        '        "SubLazer*",'
    ) in hazard_sync
    assert (
        '"spawn_salt_hazard",\n'
        '        "RegisterVariableSourceType",\n'
        "        3,\n"
        "        68,\n"
        '        "salt_state_cursor",\n'
        '        "SaltStateStrideCursor*",'
    ) in hazard_sync
    assert (
        '"spawn_salt_hazard",\n'
        '        "RegisterVariableSourceType",\n'
        "        37,\n"
        "        72,\n"
        '        "salt",\n'
        '        "Salt*",'
    ) in hazard_sync
    assert "SubLazer* sub_lazer" in hazard_sync
    assert "Salt* salt" in hazard_sync
    for ida_sync in (ida_runtime_sync, ida_path_sync):
        assert (
            "void __thiscall initialize_salt_hazard_pool("
            "SaltManager* manager);"
        ) in ida_sync
        assert (
            "void __thiscall spawn_salt_hazard("
            "SaltManager* manager, const Vec3* position);"
        ) in ida_sync
        assert "void __thiscall update_salt_hazard(Salt* salt);" in ida_sync
        assert (
            "void __thiscall clear_active_landscape_entries("
            "LandscapeManager* manager);"
        ) in ida_sync
        assert (
            "void __thiscall calc_subgame_rate(SubgameRuntime* game);"
            in ida_sync
        )
        assert "SaltHazardSlot* slot" not in ida_sync
        assert "salt_state_cursor" in ida_sync
        assert "SaltStateStrideCursor" in ida_sync
    assert "SALT_OWNER_EXPECTED_SIZE = 0x98" in ida_runtime_sync
    assert '(0x80, 4, "state", "SaltState")' in ida_runtime_sync
    assert "SALT_STATE_CURSOR_EXPECTED_SIZE = 0x98" in ida_runtime_sync
    assert '"state_stride_cursor",\n        0x441564,' in ida_runtime_sync
    assert '"salt_allocator_lvars": salt_allocator_lvars' in ida_runtime_sync
    assert 'salt_owner_readback = _salt_owner_readback()' in ida_runtime_sync
    assert "SUB_LAZER_OWNER_EXPECTED_SIZE = 0xB0" in ida_runtime_sync
    assert "SUB_LAZER_MANAGER_EXPECTED_SIZE = 0xDC0" in ida_runtime_sync
    assert '(0x80, 4, "state", "SubLazerState")' in ida_runtime_sync
    assert (
        "sub_lazer_owner_readback = _sub_lazer_owner_readback()"
        in ida_runtime_sync
    )
    assert (
        "int32_t debug_report_stub(char* format, ...);"
        in ida_runtime_sync
    )
    assert "UPDATE_SUB_LAZER_NAMED_LVAR_SPECS" in ida_runtime_sync
    for definition_address, target_name in (
        ("0x441808", "active_bod_list"),
        ("0x441880", "updated_list_flags"),
        ("0x4418A1", "next_bob_phase"),
        ("0x4418D5", "position"),
        ("0x441939", "grid_cell"),
        ("0x441946", "runtime_row"),
        ("0x441982", "primary_swept_motion"),
        ("0x4419C9", "primary_probe"),
        ("0x441A30", "secondary_swept_motion"),
        ("0x441A77", "secondary_probe"),
    ):
        assert definition_address in ida_runtime_sync
        assert f'"{target_name}"' in ida_runtime_sync
    assert '"sub_lazer_named_lvars": sub_lazer_named_lvars' in ida_runtime_sync
    assert '"SubLazer": _named_struct_size("SubLazer")' in ida_runtime_sync
    assert (
        '"SubLazerManager": _named_struct_size("SubLazerManager")'
        in ida_runtime_sync
    )
    assert '"SubLazerState",' in path_sync
    assert '"SaltStateStrideCursor",' in path_sync
    assert "SPAWN_SALT_HAZARD_USER_VAR_UPDATES" in path_sync
    for declaration in (
        "SubLazer* __thiscall initialize_sub_lazer_runtime(SubLazer* sub_lazer);",
        "void __thiscall update_sub_lazer_projectile(SubLazer* sub_lazer);",
        "void __thiscall deactivate_sub_lazer_projectile(SubLazer* sub_lazer);",
    ):
        assert declaration in ida_runtime_sync

    assert "class SubLazer : public RenderableBod" in matcher_sub_lazer
    assert "SubLazerState state;" in matcher_sub_lazer
    assert "int state;" not in matcher_sub_lazer
    assert "class Salt : public RenderableBod" in matcher_salt
    assert "enum SaltState {" in matcher_salt
    assert "SaltState state;" in matcher_salt
    assert "float fade_alpha;" in matcher_salt
    assert "float spawn_velocity_y;" in matcher_salt
    assert "unsigned char collision_armed;" in matcher_salt
    assert "Vector3 velocity;" not in matcher_salt
    assert "fade_alpha()" not in matcher_salt
    assert "collision_armed()" not in matcher_salt
    assert (
        "void SaltManager::initialize_salt_hazard_pool()"
        in salt_scratches["initialize_salt_hazard_pool"]
    )
    assert "SubLazerState* state" in (
        repo_root / "tools/match/scratches/initialize_sub_lazer_pool/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "int debug_report_stub(char* format, ...);" in (
        repo_root
        / "tools/match/scratches/update_sub_lazer_projectile/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "SALT_STATE_ACTIVE" in salt_scratches["spawn_salt_hazard"]
    assert (
        "void SaltManager::spawn_salt_hazard("
        in salt_scratches["spawn_salt_hazard"]
    )
    assert "slot->fade_alpha = 0.0f;" in salt_scratches["spawn_salt_hazard"]
    assert "slot->spawn_velocity_y" in salt_scratches["spawn_salt_hazard"]
    assert "slot->collision_armed = 1;" in salt_scratches["spawn_salt_hazard"]
    assert "SALT_STATE_RECYCLE_PENDING" in salt_scratches["update_salt_hazard"]
    assert "fade_alpha = alpha;" in salt_scratches["update_salt_hazard"]
    assert (
        "offsetof(Salt, collision_armed)"
        in salt_scratches["handle_subgoldy_collisions"]
    )


def test_banner_backlink_owner_survives_every_replay_lane() -> None:
    repo_root = Path(__file__).parents[1]
    matcher = (repo_root / "tools/match/include/banner.h").read_text(
        encoding="utf-8"
    )
    headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in (
            "bn_subgame_runtime_types.h",
            "ida_subgame_runtime_types.h",
            "path_template_types.h",
        )
    )
    syncs = tuple(
        (BINJA_DIR / name).read_text(encoding="utf-8")
        for name in (
            "sync_subgame_hazard_pool_types.py",
            "sync_subgame_runtime_types.py",
            "sync_path_template_types.py",
        )
    )
    ida_runtime_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )

    assert "SubgameRuntime* owner_game; // +0x48" in matcher
    for header in headers:
        banner = header.split("typedef struct Banner {", 1)[1].split(
            "} Banner;", 1
        )[0]
        assert "SubgameRuntime* owner_game;" in banner
        assert banner.index("owner_game") < banner.index("owner_player")
        assert "0x48 - 0x3c" in banner
        assert "0x54 - 0x4c" in banner
        assert "typedef struct BannerInitStrideView {" in header
        assert "uint8_t root_to_banner[0x3cd698];" in header
        assert "Banner banner;" in header
    for sync in syncs:
        assert '("0x48", "owner_game", "SubgameRuntime*")' in sync
        assert '("Banner", BANNER_FIELD_UPDATES)' in sync
    runtime_sync = syncs[1]
    path_sync = syncs[2]
    for sync in (runtime_sync, path_sync):
        assert "BANNER_INITIALIZER_USER_VAR_UPDATES" in sync
        assert (
            '"initialize_game_assets_and_world",\n'
            '        "StackVariableSourceType",\n'
            "        4535,\n"
            "        -296,\n"
            '        "banner_stride_view",\n'
            '        "BannerInitStrideView*",'
        ) in sync
    assert '"BannerInitStrideView": 0x3CD6F8' in runtime_sync
    assert "apply_user_var_updates already performs and verifies" in runtime_sync
    assert '"BannerInitStrideView",' in path_sync
    assert '"update_banner"' in path_sync
    assert '"list_flags"' in path_sync
    assert '"uint32_t"' in path_sync
    assert '"BannerInitStrideView": 0x3CD6F8' in ida_runtime_sync
    assert '"definition_address": 0x40BEA8' in ida_runtime_sync
    assert '"stack_offset": 84' in ida_runtime_sync
    assert "def _sync_world_initializer_stack_pointer_lvars()" in ida_runtime_sync
    assert '"banner_initializer_lvar": banner_initializer_lvar' in ida_runtime_sync

    health = json.loads(
        (
            repo_root / "analysis/decompile/health_checks.json"
        ).read_text(encoding="utf-8")
    )
    bn_initializer = next(
        check
        for check in health["checks"]
        if check["name"] == "bn_game_initializer_root_ownership"
    )
    ida_initializer = next(
        check
        for check in health["checks"]
        if check["name"] == "ida_initialize_game_assets_root_owner"
    )
    assert "struct BannerInitStrideView*" in bn_initializer["required_substrings"]
    assert "0x3cd698" in bn_initializer["forbidden_substrings"]
    assert (
        "struct BannerInitStrideView *banner_stride_view"
        in ida_initializer["required_substrings"]
    )
    assert "3987096" in ida_initializer["forbidden_substrings"]


def test_banner_update_replay_preserves_borrowed_player() -> None:
    repo_root = Path(__file__).parents[1]
    source = (BINJA_DIR / "sync_banner_update_lifetimes.py").read_text(
        encoding="utf-8"
    )
    health_checks = (
        repo_root / "analysis/decompile/health_checks.json"
    ).read_text(encoding="utf-8")

    for expected in (
        '"Vec3": 0x0C',
        '"TransformMatrix": 0x40',
        '"BodBase": 0x38',
        '"RenderableBod": 0x80',
        '"Banner": 0x60',
        '"Player": 0x4364',
        '0x38: ("visibility_mode", "int32_t")',
        '0x54: ("owner_player", "Player*")',
        '0x00: ("body", "RenderableBod")',
        "BANNER_OWNER_PLAYER_DEFINITIONS",
        "BANNER_OWNER_PLAYER_VAR",
        "BANNER_UPDATE_USER_VAR_UPDATES",
        "current_struct_fields_batch",
        "apply_split_user_var_update",
        "apply_user_var_updates",
        "verify_banner_update_owner_layout",
        '("0x441d5f", "mlil", "RegisterVariableSourceType", 31, 67)',
        'variable_name="owner_player"',
        'variable_type="Player*"',
    ):
        assert expected in source
    for fragment in (
        "int32_t visibility_mode = banner->visibility_mode",
        "fconvert.t(banner->owner_player->body.transform.position.z)",
        "fconvert.t(banner->bod.position.z) - fconvert.t(banner->owner_player",
        "banner->bod.position.y",
        '"banner_2"',
        '"banner->__offset(0x70)"',
        '"owner_player->__offset"',
    ):
        assert fragment in health_checks


def test_presentation_animation_object_cursor_survives_every_replay_lane() -> None:
    repo_root = Path(__file__).parents[1]
    headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in (
            "bn_subgame_runtime_types.h",
            "ida_subgame_runtime_types.h",
            "path_template_types.h",
        )
    )
    runtime_sync = (BINJA_DIR / "sync_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_runtime_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    matcher_weapon = (repo_root / "tools/match/include/weapon.h").read_text(
        encoding="utf-8"
    )
    matcher_player = (repo_root / "tools/match/include/player.h").read_text(
        encoding="utf-8"
    )

    for header in headers:
        assert "typedef struct PresentationAnimationObjectStrideCursor {" in header
        assert "Object* object;" in header
        assert "uint8_t slot_stride_tail[0x7c];" in header
        assert "it owns neither the slot nor the Object" in header

    assert "PresentationAnimationObjectStrideCursor" not in matcher_weapon
    assert "PresentationAnimationSlot animation_slots[5];" in matcher_weapon
    assert (
        "PresentationAnimationSlot cutscene_animation_slots[10];"
        in matcher_player
    )
    assert "Weapon jetpack_channel;" in matcher_player

    cursor_names = (
        "cutscene_animation_object_cursor",
        "jetpack_animation_object_cursor",
        "left_weapon_animation_object_cursor",
        "right_weapon_animation_object_cursor",
        "top_weapon_animation_object_cursor",
    )
    for sync in (runtime_sync, path_sync):
        assert "PRESENTATION_ANIMATION_CURSOR_USER_VAR_UPDATES" in sync
        assert '"PresentationAnimationObjectStrideCursor": 0x80' in sync
        for cursor_name in cursor_names:
            assert f'"{cursor_name}",' in sync

    for index in (18434, 18707, 19107, 19507, 19907):
        assert f"        {index}," in runtime_sync
        assert f"        {index}," in path_sync

    assert '"PresentationAnimationSlot": 0x80' in ida_runtime_sync
    assert '"PresentationAnimationObjectStrideCursor": 0x80' in ida_runtime_sync
    assert "PRESENTATION_ANIMATION_CURSOR_LVARS" in ida_runtime_sync
    assert "def _sync_world_initializer_stack_pointer_lvars()" in ida_runtime_sync
    assert '"presentation_animation_cursor_lvars": (' in ida_runtime_sync
    assert "presentation_animation_cursor_lvars" in ida_runtime_sync
    for definition_address in (0x40F4F3, 0x40F604, 0x40F794, 0x40F924, 0x40FAB4):
        assert f'"definition_address": 0x{definition_address:X}' in ida_runtime_sync
    for cursor_name in cursor_names:
        assert f'"target_name": "{cursor_name}"' in ida_runtime_sync

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    bn_check = checks["bn_game_initializer_animation_object_cursor_ownership"]
    ida_check = checks["ida_game_initializer_animation_object_cursor_ownership"]
    assert (
        "= cutscene_animation_object_cursor->object"
        in bn_check["required_substrings"]
    )
    assert "->flags |= OBJECT_FLAG_DYNAMIC_VERTICES" in bn_check[
        "required_substrings"
    ]
    assert "(var_12c - 0x432870)->subgame" in bn_check["forbidden_substrings"]
    assert (
        "cutscene_animation_object_cursor[-1].object->distort.y_squash = 0.0;"
        in ida_check["required_substrings"]
    )
    assert "x_offseta += 32" in ida_check["forbidden_substrings"]


def test_sub_lazer_asset_cursor_is_field_first_borrowed_and_fail_closed() -> None:
    repo_root = Path(__file__).parents[1]
    matcher_header = (
        repo_root / "tools/match/include/sub_lazer_types.h"
    ).read_text(encoding="utf-8")
    narrow_header = (
        HEADER_DIR / "bn_subgame_runtime_types.h"
    ).read_text(encoding="utf-8")
    canonical_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    bn_runtime_sync = (
        BINJA_DIR / "sync_subgame_runtime_types.py"
    ).read_text(encoding="utf-8")
    bn_path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_runtime_sync = (
        IDA_DIR / "apply_subgame_runtime_types.py"
    ).read_text(encoding="utf-8")
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )

    assert "SubLazerBodyObjectStrideCursor" not in matcher_header
    assert "SubLazer slots[SUB_LAZER_SLOT_CAPACITY]; // owned storage" in (
        matcher_header
    )
    for header in (narrow_header, canonical_header):
        assert "typedef struct SubLazerBodyObjectStrideCursor {" in header
        assert "Object* body_object;" in header
        assert "tColour body_color;" in header
        assert "uint8_t _pad_14[0x50];" in header
        assert "SubgameRuntime* owner_game;" in header
        assert "uint8_t _stride_tail[0x48];" in header
    assert "typedef struct tColour {" in narrow_header

    for sync in (bn_runtime_sync, bn_path_sync):
        assert '"SubLazerBodyObjectStrideCursor": 0xB0' in sync
        assert (
            '"RegisterVariableSourceType",\n'
            "        4267,\n"
            "        73,\n"
            '        "sub_lazer_body_object_cursor",\n'
            '        "SubLazerBodyObjectStrideCursor*"'
        ) in sync
    assert "SUB_LAZER_STARTUP_CURSOR_EXPECTED_SIZES" in bn_runtime_sync
    assert "SUB_LAZER_STARTUP_CURSOR_USER_VAR_UPDATES" in bn_runtime_sync
    assert (
        "WORLD_INITIALIZER_SUB_LAZER_ASSET_CURSOR_USER_VAR_UPDATES"
        in bn_path_sync
    )

    assert "SUB_LAZER_BODY_OBJECT_CURSOR_EXPECTED_SIZE = 0xB0" in (
        ida_runtime_sync
    )
    assert "SUB_LAZER_STARTUP_CURSOR_LVAR" in ida_runtime_sync
    assert '"definition_address": 0x40BD9C' in ida_runtime_sync
    assert '"target_name": "sub_lazer_body_object_cursor"' in ida_runtime_sync
    assert (
        '"target_struct_name": "SubLazerBodyObjectStrideCursor"'
        in ida_runtime_sync
    )
    assert "WORLD_INITIALIZER_SUB_LAZER_ASSET_LVAR_SPECS" in ida_path_sync
    assert (
        '"SubLazerBodyObjectStrideCursor '
        '*sub_lazer_body_object_cursor;",\n'
        "        0x40BD9C,\n"
        "        None,"
    ) in ida_path_sync

    health = json.loads(
        (
            repo_root / "analysis/decompile/health_checks.json"
        ).read_text(encoding="utf-8")
    )
    checks = {check["name"]: check for check in health["checks"]}
    bn_check = checks["bn_world_assets_sub_lazer_field_stride_owner"]
    ida_check = checks["ida_world_assets_sub_lazer_field_stride_owner"]
    assert (
        "sub_lazer_body_object_cursor->owner_game = &game->subgame"
        in bn_check["required_substrings"]
    )
    assert "edi_13 = &edi_13[0x2c]" in bn_check["forbidden_substrings"]
    assert (
        "(BodBase *)&sub_lazer_body_object_cursor[-1]._stride_tail[36],"
        in ida_check["required_substrings"]
    )
    assert "p_object += 44;" in ida_check["forbidden_substrings"]


def test_salt_asset_cursor_is_field_first_borrowed_and_fail_closed() -> None:
    repo_root = Path(__file__).parents[1]
    matcher_header = (
        repo_root / "tools/match/include/salt_hazard_types.h"
    ).read_text(encoding="utf-8")
    narrow_header = (
        HEADER_DIR / "bn_subgame_runtime_types.h"
    ).read_text(encoding="utf-8")
    canonical_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    bn_runtime_sync = (
        BINJA_DIR / "sync_subgame_runtime_types.py"
    ).read_text(encoding="utf-8")
    bn_path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_runtime_sync = (
        IDA_DIR / "apply_subgame_runtime_types.py"
    ).read_text(encoding="utf-8")
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )

    assert "SaltOwnerGameStrideCursor" not in matcher_header
    assert "Salt slots[40];" in matcher_header
    for header in (narrow_header, canonical_header):
        assert "typedef struct SaltOwnerGameStrideCursor {" in header
        assert "SubgameRuntime* owner_game;" in header
        assert "uint8_t _stride_tail[0x94];" in header
        assert "sole owner" in header or "owns neither slot" in header

    for sync in (bn_runtime_sync, bn_path_sync):
        assert '"SaltOwnerGameStrideCursor": 0x98' in sync
        assert (
            '"RegisterVariableSourceType",\n'
            "        4417,\n"
            "        73,\n"
            '        "salt_owner_game_cursor",\n'
            '        "SaltOwnerGameStrideCursor*"'
        ) in sync
    assert "SALT_STARTUP_CURSOR_EXPECTED_SIZES" in bn_runtime_sync
    assert "SALT_STARTUP_CURSOR_USER_VAR_UPDATES" in bn_runtime_sync
    assert "WORLD_INITIALIZER_SALT_ASSET_CURSOR_USER_VAR_UPDATES" in bn_path_sync

    assert "SALT_OWNER_GAME_CURSOR_EXPECTED_SIZE = 0x98" in ida_runtime_sync
    assert "SALT_STARTUP_CURSOR_LVAR" in ida_runtime_sync
    assert '"definition_address": 0x40BE32' in ida_runtime_sync
    assert '"target_name": "salt_owner_game_cursor"' in ida_runtime_sync
    assert (
        '"target_struct_name": "SaltOwnerGameStrideCursor"' in ida_runtime_sync
    )
    assert "WORLD_INITIALIZER_SALT_ASSET_LVAR_SPECS" in ida_path_sync
    assert "def _normalize_lvar_type_text(" in ida_path_sync
    assert (
        "_normalize_lvar_type_text(str(candidate.type()))"
        in ida_path_sync
    )
    assert (
        '"SaltOwnerGameStrideCursor *salt_owner_game_cursor;",\n'
        "        0x40BE32,\n"
        "        None,"
    ) in ida_path_sync

    health = json.loads(
        (
            repo_root / "analysis/decompile/health_checks.json"
        ).read_text(encoding="utf-8")
    )
    checks = {check["name"]: check for check in health["checks"]}
    bn_check = checks["bn_world_assets_salt_owner_game_field_stride_owner"]
    ida_check = checks["ida_world_assets_salt_owner_game_field_stride_owner"]
    assert (
        "salt_owner_game_cursor->owner_game = &game->subgame"
        in bn_check["required_substrings"]
    )
    assert "edi_14 = &edi_14[0x26]" in bn_check["forbidden_substrings"]
    assert (
        "(BodBase *)&salt_owner_game_cursor[-1]._stride_tail[12]"
        in ida_check["required_substrings"]
    )
    assert "p_owner_game += 38;" in ida_check["forbidden_substrings"]


def test_border_flags_stride_cursor_is_borrowed_and_fail_closed() -> None:
    repo_root = Path(__file__).parents[1]
    matcher_header = (
        repo_root / "tools/match/include/border_manager.h"
    ).read_text(encoding="utf-8")
    headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("bn_frame_renderer_types.h", "frame_renderer_types.h")
    )
    bn_sync = (BINJA_DIR / "sync_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )

    assert "BorderRecordFlagsStrideCursor" not in matcher_header
    assert "BorderRecord borders[BORDER_RECORD_COUNT];" in matcher_header
    assert "int flags; // +0x1a0" in matcher_header
    for header in headers:
        assert "typedef struct BorderRecordFlagsStrideCursor {" in header
        assert "int32_t flags;" in header
        assert "uint8_t _stride_tail[0x720];" in header
        assert "BorderManager::borders remains the sole owner" in header

    assert "WORLD_INITIALIZER_BORDER_FLAGS_CURSOR_USER_VAR_UPDATES" in bn_sync
    assert (
        '"RegisterVariableSourceType",\n'
        "        21924,\n"
        "        66,\n"
        '        "border_flags_cursor",\n'
        '        "BorderRecordFlagsStrideCursor*",'
    ) in bn_sync
    assert '"BorderRecordFlagsStrideCursor": 0x724' in bn_sync
    assert "verify_border_record_flags_stride_cursor" in bn_sync
    assert "FRAME_RENDERER_REANALYSIS_FUNCTIONS" in bn_sync
    assert "_changed_user_var_functions(user_var_results)" in bn_sync

    assert '"BorderRecordFlagsStrideCursor": 0x724' in ida_sync
    assert '"border_flags_cursor",\n        0x410295,' in ida_sync
    assert '{"p_flags", "border_flags_cursor"}' in ida_sync
    assert '{"int32_t *", "BorderRecordFlagsStrideCursor *"}' in ida_sync
    assert '"BorderRecordFlagsStrideCursor",\n        1,\n        False,' in ida_sync
    assert "is_stack=is_stack" in ida_sync

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    bn_check = checks["bn_world_assets_border_flags_stride_owner"]
    ida_check = checks["ida_world_assets_border_flags_stride_owner"]
    assert (
        "border_flags_cursor->flags = 0"
        in bn_check["required_substrings"]
    )
    assert (
        "border_flags_cursor = &border_flags_cursor[1]"
        in bn_check["required_substrings"]
    )
    assert "eax_361 = &eax_361[0x1c9]" in bn_check["forbidden_substrings"]
    assert "++border_flags_cursor;" in ida_check["required_substrings"]
    assert "p_flags += 457;" in ida_check["forbidden_substrings"]


def test_game_player_initializer_stride_view_is_borrowed_and_fail_closed() -> None:
    repo_root = Path(__file__).parents[1]
    matcher_header = (repo_root / "tools/match/include/game_root.h").read_text(
        encoding="utf-8"
    )
    headers = tuple(
        (HEADER_DIR / name).read_text(encoding="utf-8")
        for name in ("bn_frame_renderer_types.h", "frame_renderer_types.h")
    )
    bn_sync = (BINJA_DIR / "sync_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_frame_renderer_types.py").read_text(
        encoding="utf-8"
    )

    assert "GamePlayerInitStrideView" not in matcher_header
    assert (
        "GamePlayer players[GAME_ROOT_PLAYER_SLOT_COUNT]; // +0x124"
        in matcher_header
    )
    for header in headers:
        assert "typedef struct GamePlayerInitStrideView {" in header
        assert "uint8_t root_to_player[0x124];" in header
        assert "GamePlayer player;" in header
        assert "GameRoot::players remains the sole owner" in header

    assert "WORLD_INITIALIZER_USER_VAR_UPDATES" in bn_sync
    assert (
        '"RegisterVariableSourceType",\n'
        "        21460,\n"
        "        72,\n"
        '        "player_initializer_stride_view",\n'
        '        "GamePlayerInitStrideView*",'
    ) in bn_sync
    assert '"GamePlayer": 0x1F8' in bn_sync
    assert '"GamePlayerInitStrideView": 0x31C' in bn_sync
    assert "verify_game_player_initializer_stride_view" in bn_sync

    assert '"GamePlayer": 0x1F8' in ida_sync
    assert '"GamePlayerInitStrideView": 0x31C' in ida_sync
    assert "WORLD_INITIALIZER_POINTER_LVAR_SPECS" in ida_sync
    assert "0x4100C9" in ida_sync
    assert '{"edge_selectork", "player_initializer_stride_view"}' in ida_sync
    assert "bool(lvar.is_stk_var()) == is_stack" in ida_sync
    assert 'selector="initialize_game_assets_and_world"' in ida_sync
    assert '"GamePlayerInitStrideView",\n        1,\n        True,' in ida_sync
    assert "is_stack=is_stack" in ida_sync

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    bn_check = checks["bn_game_initializer_player_stride_ownership"]
    ida_check = checks["ida_game_initializer_player_stride_ownership"]
    assert (
        "struct GamePlayerInitStrideView* player_initializer_stride_view"
        in bn_check["required_substrings"][0]
    )
    assert "void* esi_4" in bn_check["forbidden_substrings"][0]
    assert (
        "struct GamePlayerInitStrideView *player_initializer_stride_view;"
        in ida_check["required_substrings"]
    )
    assert "char *edge_selectork;" in ida_check["forbidden_substrings"]


def test_ida_world_initializer_root_offsets_are_exact_and_fail_closed() -> None:
    repo_root = Path(__file__).parents[1]
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    operand_block = ida_sync.split(
        "WORLD_INITIALIZER_ROOT_OFFSET_OPERANDS = (", 1
    )[1].split("\n)\n\n# Three lifecycle", 1)[0]

    assert operand_block.count("    (0x") == 109
    for operand_spec in (
        "(0x40AEFC, 1, 0x42FF7C)",
        "(0x40F28F, 1, 0x43284C)",
        "(0x40F69A, 1, 0x432D4C)",
        "(0x40F720, 1, 0x432FC0)",
        "(0x40F749, 1, 0x433040)",
        "(0x40FB5C, 0, 0x43403C)",
        "(0x40FBC7, 1, 0x4302E4)",
        "(0x4101CB, 1, 0x6FFAE0)",
    ):
        assert operand_spec in operand_block

    assert (
        "world_initializer_root_offset_operands = _normalize_root_offset_operands(\n"
        "        WORLD_INITIALIZER_ROOT_OFFSET_OPERANDS\n"
        "    )"
    ) in ida_sync
    assert '"selector": "initialize_game_assets_and_world"' in ida_sync
    assert (
        '"world_initializer_root_offset_operands": '
        "world_initializer_root_offset_operands"
    ) in ida_sync

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    ida_check = checks["ida_game_initializer_player_presentation_root_ownership"]
    assert (
        "initialize_cameraman(&game->subgame.player.cameraman);"
        in ida_check["required_substrings"]
    )
    assert (
        "game->subgame.player.presentation.weapon_channels[0].animation_slots[2].body.bod.object"
        in ida_check["required_substrings"]
    )
    assert (
        "initialize_high_score_tables(&game->subgame.sub_high_score);"
        in ida_check["required_substrings"]
    )
    assert "loc_432" in ida_check["forbidden_substrings"]
    assert "g_parcel_set_buckets[1431]" in ida_check["forbidden_substrings"]


def test_ida_high_score_lifecycle_offsets_are_exact_and_fail_closed() -> None:
    repo_root = Path(__file__).parents[1]
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    operand_block = ida_sync.split(
        "HIGH_SCORE_LIFECYCLE_OFFSET_OPERANDS = (", 1
    )[1].split("\n)\n\n# These frontend", 1)[0]

    assert operand_block.count("    (0x") == 10
    for operand_spec in (
        "(0x407234, 1, 0x6FFAE0)",
        "(0x407247, 1, 0x6FFAE0)",
        "(0x407259, 1, 0x6FFAE0)",
        "(0x40726C, 1, 0x6FFAE0)",
        "(0x40727F, 1, 0x6FFAE0)",
        "(0x418219, 1, 0x6FFAE8)",
        "(0x418220, 1, 0x6FFAE8)",
        "(0x43880D, 1, 0x68B4C8)",
        "(0x43881E, 1, 0x68B4C8)",
        "(0x438831, 1, 0x68B4C8)",
    ):
        assert operand_spec in operand_block

    assert (
        "high_score_lifecycle_offset_operands = _normalize_root_offset_operands(\n"
        "        HIGH_SCORE_LIFECYCLE_OFFSET_OPERANDS\n"
        "    )"
    ) in ida_sync
    assert '"selector": "high-score lifecycle"' in ida_sync
    assert (
        '"high_score_lifecycle_offset_operands": '
        "high_score_lifecycle_offset_operands"
    ) in ida_sync

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    startup_check = checks["ida_game_shutdown_sub_high_score_owner"]
    complete_check = checks["ida_complete_subgame_high_score_owner"]
    menu_check = checks["ida_update_new_game_menu_intro_ownership"]

    assert (
        "save_high_scores_and_config(&g_game_base->subgame.sub_high_score, 1u);"
        in startup_check["required_substrings"]
    )
    assert (
        "add_arcade_high_score(&runtime->sub_high_score, "
        "&runtime->current_high_score_record"
    ) in complete_check["required_substrings"]
    assert (
        "g_game_base->subgame.sub_high_score.postal_records["
        in menu_check["required_substrings"]
    )
    for check in (startup_check, complete_check, menu_check):
        assert any(
            forbidden.startswith("g_parcel_set_buckets")
            for forbidden in check["forbidden_substrings"]
        )


def test_ida_player_root_borrows_are_exact_and_fail_closed() -> None:
    repo_root = Path(__file__).parents[1]
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    operand_block = ida_sync.split(
        "PLAYER_ROOT_BORROW_OFFSET_OPERANDS = (", 1
    )[1].split("\n)\n\n# These damage", 1)[0]

    assert operand_block.count("    (0x") == 10
    for operand_spec in (
        "(0x404853, 1, 0x42FD7C)",
        "(0x404881, 1, 0x42FD7C)",
        "(0x404D9A, 1, 0x42FD7C)",
        "(0x404E5D, 1, 0x42FD7C)",
        "(0x405057, 1, 0x42FD7C)",
        "(0x405092, 1, 0x42FD7C)",
        "(0x4189AD, 1, 0x42FD7C)",
        "(0x445E3A, 1, 0x42FD7C)",
        "(0x446142, 1, 0x42FD7C)",
        "(0x446168, 1, 0x42FD7C)",
    ):
        assert operand_spec in operand_block

    assert (
        "player_root_borrow_offset_operands = _normalize_root_offset_operands(\n"
        "        PLAYER_ROOT_BORROW_OFFSET_OPERANDS\n"
        "    )"
    ) in ida_sync
    assert '"selector": "Player root borrows"' in ida_sync
    assert (
        '"player_root_borrow_offset_operands": '
        "player_root_borrow_offset_operands"
    ) in ida_sync

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    for check_name in (
        "ida_flush_row_event_player_owner",
        "ida_update_row_event_player_owner",
        "ida_register_parcel_delivery_player_owner",
        "ida_activate_landscape_entry_directx_owner",
        "ida_times_up_ai_tail_owner",
        "ida_initialize_cutscene_player_owner",
        "ida_nested_subgame_initialize_cameraman_owner",
    ):
        check = checks[check_name]
        assert "g_player_block" in check["forbidden_substrings"]


def test_ida_player_state_gates_are_exact_and_fail_closed() -> None:
    repo_root = Path(__file__).parents[1]
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    operand_block = ida_sync.split(
        "PLAYER_STATE_GATE_OFFSET_OPERANDS = (", 1
    )[1].split("\n)\n\n# Tutorial", 1)[0]

    assert operand_block.count("    (0x") == 6
    for operand_spec in (
        "(0x441074, 1, 0x4301BC)",
        "(0x441114, 1, 0x4301BC)",
        "(0x441174, 1, 0x430199)",
        "(0x44117E, 1, 0x4301BC)",
        "(0x4413F9, 0, 0x4300B4)",
        "(0x4467B1, 0, 0x42FEC4)",
    ):
        assert operand_spec in operand_block

    assert (
        "player_state_gate_offset_operands = _normalize_root_offset_operands(\n"
        "        PLAYER_STATE_GATE_OFFSET_OPERANDS\n"
        "    )"
    ) in ida_sync
    assert '"selector": "Player state gates"' in ida_sync
    assert (
        '"player_state_gate_offset_operands": '
        "player_state_gate_offset_operands"
    ) in ida_sync
    for function_address in ("0x440FD0", "0x4413F0", "0x4466D0"):
        assert function_address in ida_sync.split(
            "PATH_OWNERSHIP_DIRTY_FUNCTIONS = (", 1
        )[1].split("\n)", 1)[0]

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    damage_update = checks["ida_damage_guage_ai_owner"]
    damage_take = checks["ida_damage_guage_take_bool_owner"]
    cutscene = checks["ida_update_cutscene_state_owner"]

    assert (
        "g_game_base->subgame.player.completion_handoff_active"
        in damage_update["required_substrings"]
    )
    assert (
        "g_player_attachment_exit_pending_offset"
        in damage_update["forbidden_substrings"]
    )
    assert (
        "g_follow_force_drain_offset"
        in damage_update["forbidden_substrings"]
    )
    assert (
        "SLOBYTE(g_game_base->subgame.player.shoot_flags) >= 0"
        in damage_take["required_substrings"]
    )
    assert (
        "g_invincible_damage_gate_flags_offset"
        in damage_take["forbidden_substrings"]
    )
    assert (
        "g_game_base->subgame.player.click_start.hide_prompt = 0"
        in cutscene["required_substrings"]
    )
    assert (
        "g_player_intro_cutscene_latch_offset"
        in cutscene["forbidden_substrings"]
    )


def test_cameraman_force_update_owner_survives_path_replay() -> None:
    repo_root = Path(__file__).parents[1]
    matcher = (repo_root / "tools/match/include/cameraman.h").read_text(
        encoding="utf-8"
    )
    path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    cameraman = path_header.split("typedef struct Cameraman {", 1)[1].split(
        "} Cameraman;", 1
    )[0]

    assert "unsigned char force_camera_update; // +0xcc" in matcher
    assert "uint8_t force_camera_update;" in cameraman
    assert "unresolved_cc" not in cameraman
    assert "CAMERAMAN_FIELD_UPDATES" in path_sync
    assert '("0xcc", "force_camera_update", "uint8_t")' in path_sync
    assert '("Cameraman", CAMERAMAN_FIELD_UPDATES)' in path_sync


def test_sub_garbage_owner_replays_stay_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    garbage_sync = (BINJA_DIR / "sync_garbage_hazard_types.py").read_text(
        encoding="utf-8"
    )
    garbage_lifetime_sync = (
        BINJA_DIR / "sync_garbage_allocator_lifetimes.py"
    ).read_text(encoding="utf-8")
    ida_runtime_sync = (IDA_DIR / "apply_subgame_runtime_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    garbage_header = (HEADER_DIR / "bn_garbage_hazard_types.h").read_text(
        encoding="utf-8"
    )
    path_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/garbage_hazard_slot.h"
    ).read_text(encoding="utf-8")

    for header in (garbage_header, path_header):
        assert "typedef struct SubGarbage SubGarbage;" in header
        assert "struct SubGarbage {" in header
        assert "RenderableBod body;" in header
        assert "typedef SubGarbage GarbageHazardSlot;" in header
        assert "typedef struct SubGarbagePool {" in header
        assert "SubGarbage* active_head;" in header
        assert "SubGarbage slots[" in header
        assert "typedef SubGarbagePool GarbageHazardPool;" in header
        assert "typedef struct SubGarbageSlotCursor {" in header
        assert "uint8_t subgame_prefix[0x359144];" in header
        assert "SubGarbage garbage;" in header
        assert "typedef enum SubGarbageState {" in header
        assert "SUB_GARBAGE_STATE_INACTIVE = 0" in header
        assert "SUB_GARBAGE_STATE_ACTIVE = 1" in header
        assert "SUB_GARBAGE_STATE_BURST_PENDING = 2" in header
        assert "SUB_GARBAGE_STATE_BURST = 3" in header
        assert "typedef enum SubGarbageCollisionSide {" in header
        assert "SUB_GARBAGE_COLLISION_SIDE_RIGHT = 1" in header
        assert "SUB_GARBAGE_COLLISION_SIDE_LEFT = 2" in header
        assert "SubGarbageState state;" in header
        assert "SubGarbageCollisionSide collision_side;" in header

    assert 'struct_name="SubGarbage"' in garbage_sync
    assert 'struct_name="SubGarbagePool"' in garbage_sync
    assert '("0x00", "body", "RenderableBod")' in garbage_sync
    assert '("0x84", "state", "SubGarbageState")' in garbage_sync
    assert (
        '("0x88", "collision_side", "SubGarbageCollisionSide")'
        in garbage_sync
    )
    assert "GARBAGE_ENUM_TYPE_REPLACEMENTS" in garbage_sync
    assert "EXPECTED_GARBAGE_ENUM_MEMBERS" in garbage_sync
    assert "current_enum_members" in garbage_sync
    assert "types_declare_missing_only" in garbage_sync
    assert '"SubGarbageSlotCursor",' in garbage_sync
    assert "apply_user_var_updates" not in garbage_sync
    assert "current_type_widths" in garbage_lifetime_sync
    assert "current_struct_fields_batch" in garbage_lifetime_sync
    assert "GARBAGE_ALLOCATOR_USER_VAR_UPDATES" in garbage_lifetime_sync
    assert '"SubGarbage": 0xC4' in garbage_lifetime_sync
    assert '"SubGarbagePool": 0x264C' in garbage_lifetime_sync
    assert '"SubGarbageSlotCursor": 0x359208' in garbage_lifetime_sync
    assert '0x359144: ("garbage", "SubGarbage")' in garbage_lifetime_sync
    assert (
        '"spawn_track_garbage_hazard",\n'
        '        "RegisterVariableSourceType",\n'
        '        68,\n'
        '        72,\n'
        '        "garbage_slot_cursor",\n'
        '        "SubGarbageSlotCursor*"'
        in garbage_lifetime_sync
    )
    assert "SubGarbage* sub_garbage" in garbage_sync
    assert "GarbageHazardRuntime" not in garbage_sync
    assert 'parser.add_argument("--target", default=DEFAULT_TARGET' in garbage_sync
    for ida_sync in (ida_runtime_sync, ida_path_sync):
        for declaration in (
            "SubGarbage* __thiscall initialize_garbage_hazard(SubGarbage* sub_garbage);",
            "void __thiscall update_garbage_hazard(SubGarbage* sub_garbage);",
            "SubGarbage* __thiscall destroy_garbage_hazard(SubGarbage* sub_garbage);",
            "void __thiscall spawn_garbage_smoke_particle(SubGarbage* sub_garbage, Vec3* position, Vec3* velocity, Player* owner_player);",
        ):
            assert declaration in ida_sync
        assert "GarbageHazardSlot* slot" not in ida_sync

    assert "SUB_GARBAGE_OWNER_EXPECTED_SIZE = 0xC4" in ida_runtime_sync
    assert "SUB_GARBAGE_POOL_EXPECTED_SIZE = 0x264C" in ida_runtime_sync
    assert "SUB_GARBAGE_SLOT_CURSOR_EXPECTED_SIZE = 0x359208" in ida_runtime_sync
    assert "SPAWN_GARBAGE_HAZARD_LVAR_SPECS" in ida_runtime_sync
    assert "0x43DAC5" in ida_runtime_sync
    assert '"garbage_slot_cursor"' in ida_runtime_sync
    assert '"SubGarbageSlotCursor"' in ida_runtime_sync
    assert '(0x84, 4, "state", "SubGarbageState")' in ida_runtime_sync
    assert (
        '(0x88, 4, "collision_side", "SubGarbageCollisionSide")'
        in ida_runtime_sync
    )
    assert (
        "sub_garbage_owner_readback = _sub_garbage_owner_readback()"
        in ida_runtime_sync
    )
    assert '"SubGarbage": _named_struct_size("SubGarbage")' in ida_runtime_sync
    assert (
        '"SubGarbagePool": _named_struct_size("SubGarbagePool")'
        in ida_runtime_sync
    )
    assert '"SubGarbageSlotCursor": _named_struct_size(' in ida_runtime_sync
    assert '"SubGarbageState",' in path_sync
    assert '"SubGarbageCollisionSide",' in path_sync
    assert '"SubGarbageSlotCursor",' in path_sync

    assert "class SubGarbage : public RenderableBod" in matcher_header
    assert "SubGarbageState state;" in matcher_header
    assert "SubGarbageCollisionSide collision_side;" in matcher_header
    assert "int state;" not in matcher_header
    assert "int collision_side;" not in matcher_header


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
    expected_flags = {
        "FRONTEND_WIDGET_FLAG_HIGHLIGHTED": 0x00000002,
        "FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED": 0x00000004,
        "FRONTEND_WIDGET_FLAG_HOVER_TEXT_EFFECT_ENABLED": 0x00000008,
        "FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED": 0x00000010,
        "FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED": 0x00000020,
        "FRONTEND_WIDGET_FLAG_SECONDARY_INPUT_ENABLED": 0x00000040,
        "FRONTEND_WIDGET_FLAG_SECONDARY_ACTION_TRIGGERED": 0x00000080,
        "FRONTEND_WIDGET_FLAG_KILL_PENDING": 0x00000200,
        "FRONTEND_WIDGET_FLAG_TEARDOWN_ACTIVE": 0x00000400,
        "FRONTEND_WIDGET_FLAG_SPRITE_MODE": 0x00000800,
        "FRONTEND_WIDGET_FLAG_HIDDEN": 0x00001000,
        "FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE": 0x00002000,
        "FRONTEND_WIDGET_FLAG_TEXT_INPUT_COMPLETE": 0x00004000,
        "FRONTEND_WIDGET_FLAG_DISABLED": 0x00008000,
        "FRONTEND_WIDGET_FLAG_USE_AUTHORED_RECT": 0x00010000,
        "FRONTEND_WIDGET_FLAG_POINTER_INSIDE": 0x00020000,
        "FRONTEND_WIDGET_FLAG_SNAP_VISUAL_STATE": 0x00040000,
        "FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED": 0x00080000,
        "FRONTEND_WIDGET_FLAG_SLIDER": 0x00100000,
        "FRONTEND_WIDGET_FLAG_FRAMELESS": 0x00400000,
        "FRONTEND_WIDGET_FLAG_SUPPRESS_ACTION_SOUND": 0x00800000,
        "FRONTEND_WIDGET_FLAG_IMMEDIATE_ACTION": 0x01000000,
        "FRONTEND_WIDGET_FLAG_TEXT_INPUT_SUBMIT_REQUESTED": 0x08000000,
        "FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN": 0x20000000,
        "FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION": 0x40000000,
        "FRONTEND_WIDGET_FLAG_DISABLED_BEFORE_DEACTIVATION": 0x80000000,
    }
    for name, value in expected_flags.items():
        assert f'("{name}", 0x{value:08X})' in frontend_sync
    for header in (*analysis_headers, matcher_header):
        for name, value in expected_flags.items():
            assert f"{name} = 0x{value:08X}" in header

    assert "current_enum_members" in frontend_sync
    assert "EXPECTED_FLAG_MEMBERS" in frontend_sync

    consumers = {
        "draw_frontend_widget": "FRONTEND_WIDGET_FLAG_FRAMELESS",
        "initialize_frontend_widget": "FRONTEND_WIDGET_FLAG_SUPPRESS_ACTION_SOUND",
        "initialize_frontend_sprite_button": "FRONTEND_WIDGET_FLAG_SPRITE_MODE",
        "update_frontend_widget_interaction": "FRONTEND_WIDGET_FLAG_IMMEDIATE_ACTION",
        "kill_border": "FRONTEND_WIDGET_FLAG_KILL_PENDING",
        "hide_border_init": "FRONTEND_WIDGET_FLAG_HIDDEN",
        "border_input_text": "FRONTEND_WIDGET_FLAG_TEXT_INPUT_SUBMIT_REQUESTED",
        "layout_frontend_widget": "FRONTEND_WIDGET_FLAG_USE_AUTHORED_RECT",
        "set_frontend_widget_shortcut_key": "FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED",
        "queue_frontend_widget_flag_after_delay": "FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION",
        "update_high_score_screen": "FRONTEND_WIDGET_FLAG_TEXT_INPUT_SUBMIT_REQUESTED",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch

    constructor_callers = (
        "initialize_challenge_setup_screen",
        "initialize_click_start",
        "initialize_completion_screen",
        "initialize_exit_prompt",
        "initialize_frontend_widget",
        "initialize_galaxy",
        "initialize_help_screen",
        "initialize_high_score_screen",
        "initialize_input_ok",
        "initialize_main_menu",
        "initialize_new_game_menu",
        "initialize_options_menu",
        "initialize_pause_menu",
        "initialize_subgame",
        "initialize_thanks_for_playing_screen",
        "initialize_tip",
        "initialize_warning",
        "show_times_up_message",
        "update_tooltip",
    )
    retired_composite_literals = (
        "0x100004",
        "0x400002",
        "0x400800",
        "0x400802",
        "0x900004",
        "0x20000014",
        "0x20400000",
        "0x20400002",
        "0x20400802",
        "0x20400814",
        "0x40000014",
        "0x40000016",
        "0x60000014",
    )
    for function_name in constructor_callers:
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert "FRONTEND_WIDGET_FLAG_" in scratch
        assert not any(
            literal in scratch for literal in retired_composite_literals
        )


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
    assert "DEFERRED_PROTO_UPDATES" not in frontend_sync
    assert "proto_owner_deferred" not in frontend_sync
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

    direct = frontend_sync.split("\nPROTO_UPDATES = (", 1)[1].split(
        "\nUSER_VAR_UPDATES = (", 1
    )[0]

    expected = (
        "void __thiscall initialize_exit_prompt(Exit* exit_prompt)",
        "void __thiscall draw_frontend_widget(FrontendWidget* widget)",
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
        assert prototype in direct
        if not prototype.startswith(
            (
                "void __thiscall initialize_exit_prompt",
                "void __thiscall draw_frontend_widget",
            )
        ):
            assert f'"{prototype};"' in ida_path_sync
    assert "DEFERRED_PROTO_UPDATES" not in frontend_sync
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


def test_sprite_and_texture_ownership_stays_aligned() -> None:
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
    texture_fields = (
        '("0x04", "loaded_width", "int32_t")',
        '("0x08", "loaded_height", "int32_t")',
        '("0x0c", "name", "char[0x80]")',
        '("0x8c", "slot_index", "int32_t")',
        '("0x90", "frame_count", "int32_t")',
        '("0x94", "frame_progress_step", "float")',
        '("0x98", "texture_ref", "void*")',
        '("0xa0", "mip_levels", "int32_t")',
    )
    for script_name in (
        "sync_object_render_types.py",
        "sync_path_template_types.py",
        "sync_star_manager_types.py",
    ):
        for field in texture_fields:
            assert field in sync_sources[script_name]

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
        assert "loaded_width;" in header
        assert "loaded_height;" in header
        assert "mip_levels;" in header
        assert "unknown_a0" not in header

    consumers = {
        "initialize_sprite": "SPRITE_FLAG_RENDER_ENABLED",
        "update_sprite": "SPRITE_FLAG_ANIMATION_PING_PONG",
        "build_sprite_tail": "SPRITE_FLAG_THROTTLE_FACING_REFRESH",
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
        assert "RUNTIME_RENDER_FONT_SHADOW = 0x00000100" in header
        assert "RUNTIME_RENDER_32_BIT_COLOR = 0x00000400" in header
        assert "RUNTIME_RENDER_FONT_SHADOW_BIT = 8" in header
        assert "RUNTIME_RENDER_FONT_WAVE" not in header
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
        "layout_frontend_widget": "RUNTIME_RENDER_FONT_SHADOW_BIT",
        "update_frontend_widget_interaction": "RUNTIME_RENDER_FONT_SHADOW_BIT",
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
        assert "float glyph_u0[" in header
        assert "float glyph_u1[" in header
        assert "float glyph_width[" in header
        assert "int32_t texture_page[0x80]" in header or "int texture_page[" in header
        assert "float glyph_v0" in header
        assert "float glyph_v1" in header
        assert "float width_scale" in header
        assert "float height_scale" in header
        assert "shadow_offset_pixels" in header
        assert "font_kind" not in header
        assert "struct cFontPrintBuffer {" in header
        for lane in ("z0", "z1", "z2", "z3"):
            assert f"float {lane}" in header
        for stale_lane in (
            "unknown_0c",
            "unknown_18",
            "unknown_24",
            "unknown_30",
        ):
            assert stale_lane not in header
        assert "text_wave_amplitude" in header
        assert "shadow_enabled" in header
        assert "text_wave_enabled" not in header
        assert "tColour color" in header
        assert "int32_t blend_mode" in header or "int blend_mode" in header
        assert "float rotation" in header

    assert "int32_t __cdecl register_font_texture_sheet(" in analysis_header
    assert "void __cdecl layout_and_queue_wrapped_font_text(" in analysis_header
    assert "int register_font_texture_sheet(" in matcher_header
    assert "void layout_and_queue_wrapped_font_text(" in matcher_header

    for source in (binja_sync, ida_sync):
        assert "g_render_queue_active" in source
        assert "g_font_text_buffer" in source
        assert "g_font_queue" in source
        assert "g_font3d_bods" in source
        assert "g_font3d_scales" in source
        assert "g_font_sheets" in source
        assert "g_registered_font_count" in source
        assert "initialize_font_wave_state" in source
        assert "update_font_wave_state" in source
        assert "measure_font_text_width" in source
        assert "register_font_texture_sheet" in source
        assert "sample_tga_pixel_rgb" in source
        assert "draw_font_text_instance" in source
        assert "draw_queued_font_quad_instance" in source
        assert "draw_font_text_queue" in source
        assert "queue_font_text_instance" in source
        assert "queue_axis_aligned_textured_quad" in source
        assert "queue_axis_aligned_textured_quad_uv" in source
        assert "queue_textured_quad_corners" in source
        assert "layout_and_queue_wrapped_font_text" in source
        assert "initialize_font3d_objects" in source
        assert "register_font_texture_sheet_wrapper" in source
        assert "shadow_offset_pixels" in source
        assert "shadow_enabled" in source
        assert "font_kind" not in source
        assert "text_wave_enabled" not in source
        assert "int32_t __cdecl register_font_texture_sheet" in source
        assert "void __cdecl layout_and_queue_wrapped_font_text" in source

    assert '("0x7544e8", "cFontPrintBuffer[0x400]")' in binja_sync
    assert '("0x7754e8", "BodBase[0x80]")' in binja_sync
    assert '("0x7770e8", "float[0x80]")' in binja_sync
    assert '("0x7772f8", "FontSheet[0x1]")' in binja_sync
    assert '("0x0c", "z0", "float")' in binja_sync
    assert '("0x18", "z1", "float")' in binja_sync
    assert '("0x24", "z2", "float")' in binja_sync
    assert '("0x30", "z3", "float")' in binja_sync
    assert '("0x6c", "color", "tColour")' in binja_sync
    assert '("0x7c", "blend_mode", "int32_t")' in binja_sync
    assert '("0x80", "rotation", "float")' in binja_sync
    assert "float __cdecl measure_font_text_width" in binja_sync
    assert (
        "int32_t __cdecl sample_tga_pixel_rgb(TgaImageView* image, "
        "int32_t x, int32_t y)"
    ) in binja_sync
    assert "float width_scale, float height_scale" in binja_sync
    assert "void __cdecl initialize_font3d_objects(int16_t font_id)" in binja_sync
    assert "void __cdecl initialize_font_wave_state()" in binja_sync
    assert "void __cdecl update_font_wave_state()" in binja_sync
    assert "void __cdecl draw_font_text_queue(uint32_t render_mask)" in binja_sync
    assert "void __cdecl queue_font_text_instance" in binja_sync
    assert "int32_t __cdecl queue_axis_aligned_textured_quad" in binja_sync
    assert "int32_t __cdecl queue_textured_quad_corners" in binja_sync
    assert "float unused_28, float unused_2c" in binja_sync
    assert "float unused_28, float unused_2c" in ida_sync
    assert "void __cdecl layout_and_queue_wrapped_font_text" in binja_sync
    assert "cFontPrintBuffer g_font_queue[0x400];" in ida_sync
    assert "FontSheet g_font_sheets[1];" in ida_sync
    assert "void __cdecl initialize_font_wave_state();" in ida_sync
    assert "void __cdecl update_font_wave_state();" in ida_sync
    assert "TgaImageView *image, int32_t x, int32_t y" in ida_sync
    assert "typedef struct TgaImageView {" in analysis_header
    assert "uint8_t pixels[1];" in analysis_header
    assert '"TgaImageView": 0x14' in binja_sync
    assert "ensure_function_analysis" in binja_sync
    assert "apply_split_user_var_update" in binja_sync
    assert "apply_user_var_updates" in binja_sync
    assert "reanalyze_functions" in binja_sync
    assert "FONT_OWNER_REANALYSIS_FUNCTIONS" in binja_sync
    assert '"register_font_texture_sheet"' in binja_sync
    assert '"draw_font_text_instance"' in binja_sync
    assert "FONT_DRAW_CURSOR_X_DEFINITIONS" in binja_sync
    assert binja_sync.count('"StackVariableSourceType", 12, 4') == 1
    assert "FONT_DRAW_CURSOR_X_VAR" in binja_sync
    assert '"0x44a36c"' in binja_sync
    assert '"0x44a39f"' in binja_sync
    assert '"0x44a3c9"' in binja_sync
    assert '"0x44a3f3"' in binja_sync
    assert '"0x44a3f9", "mlil_ssa"' in binja_sync
    assert '"0x44a414", "mlil_ssa"' in binja_sync
    assert '"0x44a6b1"' in binja_sync
    assert '"0x44a6c2", "mlil_ssa"' in binja_sync
    assert 'variable_name="cursor_x"' in binja_sync
    assert 'variable_type="float"' in binja_sync
    assert "FONT_DRAW_CURRENT_CHAR_DEFINITIONS" in binja_sync
    assert '"0x44a408", "mlil_ssa"' in binja_sync
    assert '"0x44a690", "mlil_ssa"' in binja_sync
    assert 'variable_name="current_char"' in binja_sync
    assert 'variable_type="char"' in binja_sync
    assert "FONT_DRAW_GLYPH_ADVANCE_DEFINITIONS" in binja_sync
    assert '"0x44a687", "mlil_ssa"' in binja_sync
    assert 'variable_name="glyph_advance"' in binja_sync
    assert 'variable_type="int32_t"' in binja_sync
    assert "FONT_DRAW_GLYPH_USER_VAR_UPDATES" in binja_sync
    assert '"text_cursor"' in binja_sync
    assert '"wave_index"' in binja_sync
    assert '"text_resume"' in binja_sync
    assert '"glyph_slot"' in binja_sync
    assert '"atlas_u0"' in binja_sync
    assert '"atlas_u1"' in binja_sync
    assert '"texture_page"' in binja_sync
    assert '"atlas_v0"' in binja_sync
    assert '"atlas_v1"' in binja_sync
    assert '"draw_x"' in binja_sync
    assert '"draw_y"' in binja_sync
    assert '"shadow_offset"' in binja_sync
    assert '"shadow_color"' in binja_sync
    assert '"wave_phase_x"' in binja_sync
    assert '"wave_phase_y"' in binja_sync
    assert '"wave_x"' in binja_sync
    assert '"shadow_texture"' in binja_sync
    assert '"glyph_texture"' in binja_sync
    assert '"image"' in binja_sync
    assert '"TgaImageView*"' in binja_sync
    assert "\n        45,\n        66," in binja_sync
    assert '"split_x"' in binja_sync
    assert '"path_char"' in binja_sync
    assert '"path_index"' in binja_sync
    assert '"run_width"' in binja_sync
    assert '"glyph_slot"' in binja_sync
    assert '"last_x"' in binja_sync
    assert '"glyph_run_width"' in binja_sync
    assert '"pixel_color"' in binja_sync
    assert '"glyph_left"' in binja_sync
    assert "STALE_FONT_TGA_USER_VAR_REMOVALS" in binja_sync
    assert "remove_user_var_updates" in binja_sync
    assert "\n        265,\n        67," in binja_sync
    assert '"centered_left"' in binja_sync
    assert '"centered_last"' in binja_sync
    assert '"line_marker_y"' in binja_sync
    assert '"page0_texture_ref"' in binja_sync
    assert '"flagged_texture_ref"' in binja_sync
    assert '"texture_path_0"' in binja_sync
    assert binja_sync.count('"texture_path_1"') == 1
    assert "FONT_QUEUE_COLOR_USER_VAR_UPDATES" in binja_sync
    assert binja_sync.count('"entry_color"') == 4
    assert binja_sync.count('"tColour*"') == 5
    assert "\n        134,\n        68," in binja_sync
    assert "\n        127,\n        72," in binja_sync
    assert "\n        124,\n        68," in binja_sync
    assert "\n        85,\n        72," in binja_sync
    assert "apply_type_renames" in binja_sync
    assert '("FontGlyphV0Cursor", "FontGlyphAtlasCursor")' in binja_sync
    assert '"FontGlyphAtlasCursor": 0x404' in binja_sync
    assert "FONT3D_GLYPH_CURSOR_USER_VAR_UPDATES" in binja_sync
    assert '"glyph_atlas_cursor"' in binja_sync
    assert '"FontGlyphAtlasCursor*"' in binja_sync
    assert '"glyph_index"' in binja_sync
    assert '"scale_cursor"' in binja_sync
    assert '"bod_object_cursor"' in binja_sync
    assert '"font_sheet_dword_offset"' in binja_sync
    assert "FONT3D_GLYPH_SCALE_DEFINITIONS" in binja_sync
    assert '"0x44ae71", "mlil_ssa", "StackVariableSourceType", 97, 4' in binja_sync
    assert "FONT3D_GLYPH_SCALE_VAR" in binja_sync
    assert 'variable_name="glyph_scale"' in binja_sync
    assert 'variable_type="float"' in binja_sync
    assert "\n        16,\n        -8," in binja_sync
    assert "\n        54,\n        71," in binja_sync
    assert "\n        62,\n        72," in binja_sync
    assert "\n        67,\n        66," in binja_sync
    assert "\n        73,\n        73," in binja_sync
    assert "float glyph_u0[0x80];" in analysis_header
    assert "float glyph_u1[0x80];" in analysis_header
    assert "float glyph_v0;" in analysis_header
    assert "float glyph_v1;" in analysis_header
    assert "typedef struct FontGlyphAtlasCursor {" in analysis_header
    assert "float next_glyph_u1;" in analysis_header
    assert "uint8_t _next_u1_to_glyph_width[0x1f8];" in analysis_header
    assert "uint8_t _glyph_width_to_texture_page[0x1fc];" in analysis_header
    assert "void __cdecl initialize_font_wave_state(void);" in analysis_header
    assert "void __cdecl update_font_wave_state(void);" in analysis_header

    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    crosswalk_by_address = {
        int(entry["address"], 0): entry for entry in crosswalk["entries"]
    }
    assert crosswalk_by_address[0x449F50]["android_symbol"] == (
        "FontLoad(char*, int, float, float)"
    )
    assert crosswalk_by_address[0x449F50]["ios_symbol"] == (
        "FontLoad(char*, int, float, float)"
    )
    assert crosswalk_by_address[0x44ABE0]["android_symbol"].startswith("FontType(")
    assert crosswalk_by_address[0x44ABE0]["ios_symbol"].startswith("FontType(")
    assert crosswalk_by_address[0x44AE10]["android_symbol"] == "FontMake3D(short)"
    assert crosswalk_by_address[0x44AE10]["ios_symbol"] == "FontMake3D(short)"

    for mobile_body in (
        "analysis/decompile/android/functions/00032d78-_Z8FontLoadPciff.c",
        "analysis/decompile/ios/functions/0000f09c-_Z8FontLoadPciff.c",
    ):
        body = (repo_root / mobile_body).read_text(encoding="utf-8")
        assert "void FontLoad(" in body
    for mobile_body in (
        "analysis/decompile/android/functions/"
        "00032174-_Z8FontTypePcifffPfS0_S0_S0_fbifi7tColourbb.c",
        "analysis/decompile/ios/functions/"
        "0000f444-_Z8FontTypePcifffPfS0_S0_S0_fbifi7tColourbb.c",
    ):
        body = (repo_root / mobile_body).read_text(encoding="utf-8")
        assert "void FontType(" in body
    assert crosswalk_by_address[0x44A8B0]["ios_symbol"].startswith("OSDPrint(")
    assert crosswalk_by_address[0x44A9B0]["ios_symbol"].startswith("OSDPrintUV(")
    assert (
        "float, float, float, float, float, float, float, float, float, float"
        in crosswalk_by_address[0x44AAC0]["ios_symbol"]
    )

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
        assert "typedef struct FrameRenderCamera" in header
        assert "typedef struct GamePlayer" in header
        assert header.count("FrameRenderableBod body;") == 2
        assert "FrameTransformMatrix completion_handoff_transform;" in header
        assert "typedef struct BorderStackEntry" in header
        assert "BorderStackEntry entries[200];" in header
        assert (
            "void __thiscall border_add_text_number(\n"
            "    FrontendWidget* border, int32_t value);"
        ) in header
        assert (
            "void __thiscall apply_all_border_visibility_mode(\n"
            "    BorderStack* stack, int32_t mode);"
        ) in header
        assert "typedef struct BorderRecord" in header
        assert "tColour color_06c;" in header
        assert "int32_t created_time;" in header
        assert "struct BorderManager" in header
        assert "BorderStack border_stack;" in header
        assert "BorderRecord borders[150];" in header
        assert "int32_t delayed_widget_flags;" in header
        assert "FrontendWidget* delayed_widget;" in header
        assert "float justify_centre;" in header
        assert "int32_t unknown_000b48;" in header
        assert "BorderManager border_manager;" in header
        assert "FrameBorderManager" not in header
        assert "uint8_t unknown_044100[0x74618 - 0x44100];" in header
        assert "unknown_000b48[0x74618 - 0xb48]" not in header

    assert "typedef struct FrameRenderableBod" in ida_header
    assert "typedef struct FrameOverlay" in ida_header
    assert "FrameOverlay overlay_0;" in ida_header
    assert "FrameOverlay overlay_1;" in ida_header
    assert "FrameOverlay overlay_2;" in ida_header
    assert "uint8_t unknown_00067c[0xb24 - 0x67c];" not in ida_header

    assert '("0x4df904", "GameRoot*")' in binja_sync
    assert '("0x4972f4", "g_game_player_callback_table")' in binja_sync
    assert '("0x4972f4", "void*")' in binja_sync
    assert "FRAME_RENDER_CAMERA_FIELD_UPDATES = (" in binja_sync
    assert '("0x00", "body", "FrameRenderableBod")' in binja_sync
    assert '("FrameRenderCamera", FRAME_RENDER_CAMERA_FIELD_UPDATES)' in binja_sync
    assert '("GamePlayer", GAME_PLAYER_FIELD_UPDATES)' in binja_sync
    assert "g_game_player_callback_table" in ida_sync
    assert (
        '("0x1a8", "completion_handoff_transform", "FrameTransformMatrix")'
        in binja_sync
    )
    assert '"BorderManager",' in binja_sync
    assert '("0xb48", "unknown_000b48", "int32_t")' in binja_sync
    assert '("0xb4c", "border_manager", "BorderManager")' in binja_sync
    assert 'BORDER_RECORD_FIELD_UPDATES = (' in binja_sync
    assert 'BORDER_MANAGER_FIELD_UPDATES = (' in binja_sync
    assert '("0x08", "list_prev", "FrameBodBase*")' in binja_sync
    assert '("0x38", "border_stack", "BorderStack")' in binja_sync
    assert '("0x684", "borders", "BorderRecord[150]")' in binja_sync
    assert '("0x435ac", "delayed_widget", "FrontendWidget*")' in binja_sync
    assert '("0x435b0", "justify_centre", "float")' in binja_sync
    assert "def resolved_border_manager_struct_name" in binja_sync
    assert 'struct_name="BorderManager"' in binja_sync
    assert 'return "BorderManager"' in binja_sync
    assert "0x4DF904" in ida_sync
    assert '"GameRoot *g_game_base;"' in ida_sync
    assert (
        '"FrontendWidget *__thiscall allocate_border(BorderManager *manager);"'
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
    assert "extern GameRoot* g_game; // data_4df904" in matcher_header
    for source in (update_source, resurrect_source):
        assert '#include "game_root.h"' in source
        assert "extern GameRoot* g_game;" not in source
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
        "update_snail_presentation": "CUT_SCENE_STATE_INACTIVE",
        "handle_subgoldy_collisions": "CUT_SCENE_STATE_DEATH_PENDING",
        "update_subgoldy": "CUT_SCENE_STATE_COMPLETION_PENDING",
        "update_cutscene": "CUT_SCENE_STATE_DEATH_HOLD",
    }
    for function_name, constant in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert constant in scratch


def test_presentation_wobble_view_stays_exact_and_replayable() -> None:
    repo_root = Path(__file__).parents[1]
    matcher_header = (repo_root / "tools/match/include/player.h").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )

    for header in (matcher_header, analysis_header):
        assert "struct PresentationWobbleController" in header
        assert "float roll_phase;" in header
        assert "float roll_phase_step;" in header
        assert "float lift_phase;" in header
        assert "float lift_phase_step;" in header
        assert "PresentationWobbleController wobble" in header

    assert "PresentationWobbleController_must_be_0x10" in matcher_header
    assert '"PresentationWobbleController",' in binja_sync
    assert '("0x15bc", "wobble", "PresentationWobbleController")' in binja_sync
    assert "ensure_path_analysis_views(" in binja_sync
    assert "current_header_type_equivalence(" in binja_sync
    assert '"RuntimeCellStrideAnchor"' in binja_sync
    assert "replace_types=stale_types" in binja_sync
    assert "PRESENTATION_WOBBLE_CONTROLLER_FIELD_UPDATES" in binja_sync

    consumers = {
        "initialize_subgoldy": "presentation.wobble.roll_phase_step",
        "update_snail_presentation": "wobble.lift_phase_step",
        "handle_subgoldy_collisions": "presentation.wobble.lift_phase_step",
    }
    for function_name, field in consumers.items():
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert field in scratch


def test_damage_guage_state_ownership_stays_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (
        repo_root / "tools/ida/apply_path_template_types.py"
    ).read_text(encoding="utf-8")
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/damage_guage.h"
    ).read_text(encoding="utf-8")

    assert '"DamageGuageState",' in path_sync
    assert '("0x00", "state", "DamageGuageState")' in path_sync
    bool_take = (
        "apply_damage_gauge_delta(DamageGuage* damage_guage, "
        "float delta, bool force)"
    )
    assert bool_take in path_sync
    assert f"{bool_take};" in ida_sync
    for function_name in (
        "initialize_damage_gauge",
        "update_damage_gauge",
        "apply_damage_gauge_delta",
    ):
        assert f'"{function_name}"' in ida_sync
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

    take_scratch = (
        repo_root / "tools/match/scratches/apply_damage_gauge_delta/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "float delta, bool force" in take_scratch
    assert take_scratch.count("state != DAMAGE_GUAGE_STATE_DRAINING") == 2


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
    assert '"--nuke-only"' in path_sync
    assert "NUKE_OWNER_SIZES" in path_sync
    assert "verify_nuke_owner_size" in path_sync
    assert "updates=NUKE_PROTO_UPDATES" in path_sync
    assert "updates=NUKE_USER_VAR_UPDATES" in path_sync
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    for address in ("0x4470E0", "0x447110", "0x4471E0"):
        assert address in ida_sync
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


def test_tip_manager_lifecycle_replay_keeps_exact_owner_graph() -> None:
    repo_root = Path(__file__).parents[1]
    path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/tip_manager.h").read_text(
        encoding="utf-8"
    )

    for header in (analysis_header, matcher_header):
        assert "TipData* definition" in header
        assert "FrontendWidget* widget_main" in header
        assert "FrontendWidget* widget_ok" in header
        assert "FrontendWidget* widget_disable" in header
        assert "Tip tips[" in header

    for marker in (
        '"--tip-only"',
        '"TipData": 0x14',
        '"Tip": 0x20',
        '"TipManager": 0x98',
        "TIP_DATA_FIELD_UPDATES",
        "TIP_FIELD_UPDATES",
        "TIP_MANAGER_FIELD_UPDATES",
        "TIP_PROTO_UPDATES",
        "TIP_MANAGER_USER_VAR_UPDATES",
        "verify_tip_owner_sizes",
        "updates=TIP_MANAGER_USER_VAR_UPDATES",
    ):
        assert marker in path_sync

    prototypes = (
        "void __thiscall kill_tip_widgets(Tip* tip)",
        "void __thiscall initialize_tip(Tip* tip, TipData* definition, int32_t hide_disable_button)",
        "void __thiscall update_tip(Tip* tip)",
        "void __thiscall initialize_tip_manager(TipManager* manager)",
        "void __thiscall uninit_tips(TipManager* manager)",
        "Tip* __thiscall enqueue_tip_message(TipManager* manager, TipData* definition, int32_t hide_disable_button)",
        "void __thiscall update_tip_manager(TipManager* manager)",
    )
    for prototype in prototypes:
        assert prototype in path_sync
        assert prototype + ";" in ida_sync
        assert prototype + ";" in analysis_header

    for address in (
        "0x4489E0",
        "0x448A40",
        "0x448C40",
        "0x448CF0",
        "0x448D10",
        "0x448D30",
        "0x448D80",
    ):
        assert address in ida_sync


def test_tutorial_lifecycle_replay_keeps_runtime_and_tip_manager_owners() -> None:
    repo_root = Path(__file__).parents[1]
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_tutorial = (repo_root / "tools/match/include/tutorial.h").read_text(
        encoding="utf-8"
    )
    matcher_subgame = (
        repo_root / "tools/match/include/subgame_runtime.h"
    ).read_text(encoding="utf-8")
    ida_root_owner = (IDA_DIR / "game_root_owner.py").read_text(encoding="utf-8")

    for header in (analysis_header, matcher_tutorial):
        assert "SubgameRuntime* game" in header
    for header in (analysis_header, matcher_subgame):
        assert "runtime_flags" in header
    assert '(0x12E6F58, 0x98, "tip_manager", "TipManager")' in ida_root_owner

    for marker in (
        "TUTORIAL_NUMERIC_OPERANDS",
        "(0x448DAB, 1, 0x74618)",
        "(0x448DB6, 1, 0x600000)",
        "(0x448DD5, 1, 0x12E6F58)",
        '"tutorial_numeric_operands": tutorial_numeric_operands',
    ):
        assert marker in ida_sync

    for address in ("0x448DA0", "0x448DD0", "0x448DE0"):
        assert address in ida_sync


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
        code = args[-1]
        preview = "preview = True" in code
        return {
            "result": {
                "success": True,
                "preview": preview,
                "committed": not preview,
                "applied": [{"name": "SubgameRuntime", "verified": True}],
                "restoration": (
                    [{"name": "SubgameRuntime", "verified": True}]
                    if preview
                    else []
                ),
                "snapshot_saved": not preview,
            }
        }

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
    assert len(calls) == 2
    assert calls[0][:2] == ("py", "exec")
    assert calls[1][:2] == ("py", "exec")
    assert "included_names = set([\"SubgameRuntime\"])" in calls[0][-1]
    assert "preview = True" in calls[0][-1]
    assert "begin_undo_actions" in calls[0][-1]
    assert "revert_undo_actions" in calls[0][-1]
    assert "preview = False" in calls[1][-1]
    assert "commit_undo_actions" in calls[1][-1]
    assert "save_auto_snapshot" in calls[1][-1]
    assert "define_user_type" in calls[1][-1]
    assert "def _structure_signature(type_)" in calls[0][-1]
    assert "member.type.type_class" in calls[0][-1]
    assert "member.type.alignment" in calls[0][-1]
    assert "str(member.type)" in calls[0][-1]
    assert "parsed_structure_signature is not None" in calls[0][-1]
    assert '"verified": direct_match or structural_match' in calls[0][-1]
    assert all(call[:2] != ("types", "declare") for call in calls)


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
        code = args[-1]
        preview = "preview = True" in code
        return {
            "result": {
                "success": True,
                "preview": preview,
                "committed": not preview,
                "applied": [],
                "restoration": [],
                "snapshot_saved": False,
            }
        }

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
    assert 'return str(value).replace(" __pure", "")' in calls[0][calls[0].index("--code") + 1]
    assert "function.reanalyze()" in calls[0][calls[0].index("--code") + 1]
    assert "prototype_reanalysis_identifiers" in calls[0][calls[0].index("--code") + 1]
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


def test_previewed_batch_can_transactionally_rename_a_type() -> None:
    code = _narrow_sync._batch_python_code(
        [
            {
                "op": "rename_type",
                "old_name": "FontGlyphV0Cursor",
                "new_name": "FontGlyphAtlasCursor",
            }
        ],
        preview=True,
    )

    assert "bv.rename_type(old_name, new_name)" in code
    assert "cannot rename missing type" in code
    assert "target type" in code
    assert "already exists" in code
    assert 'observed_old = bv.get_type_by_name(entry["old_name"])' in code
    assert "observed_old is None and observed_new is not None" in code
    assert "bv.revert_undo_actions(state)" in code


def test_type_rename_replay_skips_when_target_is_current(monkeypatch) -> None:
    monkeypatch.setattr(
        _narrow_sync,
        "current_type_widths",
        lambda *_args, **_kwargs: {
            "FontGlyphV0Cursor": None,
            "FontGlyphAtlasCursor": 0x404,
        },
    )
    monkeypatch.setattr(
        _narrow_sync,
        "run_previewed_bn_batch",
        lambda *_args, **_kwargs: (_ for _ in ()).throw(
            AssertionError("an idempotent type rename must not open a transaction")
        ),
    )

    result = _narrow_sync.apply_type_renames(
        Path("."),
        target="snail-mail.exe",
        renames=(("FontGlyphV0Cursor", "FontGlyphAtlasCursor"),),
    )

    assert result == [
        {
            "op": "rename_type",
            "status": "skipped",
            "reason": "already current",
            "old_name": "FontGlyphV0Cursor",
            "new_name": "FontGlyphAtlasCursor",
        }
    ]


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
    assert "variable_sources = [function.vars]" in code
    assert 'getattr(function, "hlil", None)' in code
    assert 'getattr(function, "mlil", None)' in code
    assert "for variable in function_variables(function)" in code
    assert "parsed_type_cache = {}" in code
    assert "expected_type, _ = parse_type_once(operation[\"variable_type\"])" in code
    assert '"user_defined": bool(function.is_var_user_defined(variable))' in code
    assert 'str(variable.source_type).split(".")[-1] == expected_source' in code
    assert 'entry["verified"] = observed == entry["expected"]' in code
    assert "user_var_reanalysis_identifiers.append" in code
    assert (
        "prototype_reanalysis_identifiers\n"
        "                + user_var_reanalysis_identifiers"
    ) in code
    assert "bv.revert_undo_actions(state)" in code


def test_previewed_batch_can_transactionally_delete_an_exact_user_variable() -> None:
    code = _narrow_sync._batch_python_code(
        [
            {
                "op": "user_var_delete",
                "identifier": "update_jet_particles",
                "source_type": "RegisterVariableSourceType",
                "index": 543,
                "storage": 67,
                "variable_name": "trail_velocity",
                "variable_type": "Vec3*",
            }
        ],
        preview=True,
    )

    assert "function.delete_user_var(variable)" in code
    assert "refusing to delete an unexpected user variable" in code
    assert 'entry["verified"] = observed["user_defined"] is False' in code
    assert "user_var_reanalysis_identifiers.append" in code
    assert '"already automatic"' in code
    assert "bv.revert_undo_actions(state)" in code


def test_previewed_batch_guards_analysis_for_current_user_variables() -> None:
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

    assert "analysis_changed = False" in code
    assert "function.create_user_var(variable, expected_type, expected_name)" in code
    assert "analysis_changed = True" in code
    assert "if analysis_changed:\n        bv.update_analysis_and_wait()" in code
    assert (
        "snapshot_saved = bv.file.save_auto_snapshot() if analysis_changed else False"
        in code
    )
    assert "if analysis_changed and snapshot_saved is not True:" in code
    assert "database snapshot; close duplicate views of the same .bndb " in code
    assert '"before retrying"' in code


def test_integer_display_batches_guard_instruction_bytes_and_hlil() -> None:
    code = _narrow_sync._batch_python_code(
        [
            {
                "op": "int_display_set",
                "identifier": "save_high_scores_and_config",
                "address": "0x41794c",
                "expected_bytes": "68 40 4b 4c 00",
                "value": 0x4C4B40,
                "operand": 0xFFFFFFFF,
                "display_type": "UnsignedHexadecimalDisplayType",
                "required_hlil": (
                    'allocate_tracked_memory(0x4c4b40, "High Score Table")'
                ),
                "forbidden_hlil": (
                    "allocate_tracked_memory(&(*(*g_texture_refs.entries)"
                ),
            }
        ],
        preview=True,
    )

    for expected in (
        'if kind == "int_display_set":',
        "if function not in bv.get_functions_containing(address):",
        "observed_bytes = bytes(bv.read(address, len(expected_bytes)))",
        "if observed_bytes != expected_bytes:",
        "expected_display_type = IntegerDisplayType[display_type_name]",
        "function.get_int_display_type(address, value, operand)",
        "function.set_int_display_type(",
        "required_hlil not in before_hlil",
        "forbidden_hlil in before_hlil",
        "+ int_display_reanalysis_identifiers",
    ):
        assert expected in code


def test_current_user_variable_preview_does_not_reanalyze() -> None:
    variable = SimpleNamespace(
        source_type="RegisterVariableSourceType",
        index=0,
        storage=67,
        name="widget",
        type="struct FrontendWidget*",
    )

    class FakeFunction:
        name = "draw_frontend_widget"
        start = 0x401130
        vars = [variable]
        create_calls = 0

        def is_var_user_defined(self, _variable) -> bool:
            return True

        def create_user_var(self, _variable, _type, _name) -> None:
            self.create_calls += 1

    class FakeBinaryView:
        update_calls = 0
        revert_calls = 0

        def begin_undo_actions(self) -> object:
            return object()

        def get_functions_by_name(self, name: str) -> list[FakeFunction]:
            assert name == "draw_frontend_widget"
            return [function]

        def parse_type_string(self, type_name: str) -> tuple[str, None]:
            assert type_name == "FrontendWidget*"
            return "struct FrontendWidget*", None

        def update_analysis_and_wait(self) -> None:
            self.update_calls += 1

        def revert_undo_actions(self, _state: object) -> None:
            self.revert_calls += 1

    function = FakeFunction()
    bv = FakeBinaryView()
    namespace = {"bv": bv}
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

    exec(code, namespace)

    assert namespace["result"]["results"][0]["changed"] is False
    assert function.create_calls == 0
    assert bv.update_calls == 0
    assert bv.revert_calls == 1


def test_previewed_batch_can_transactionally_reanalyze_functions() -> None:
    code = _narrow_sync._batch_python_code(
        [
            {
                "op": "reanalyze_function",
                "identifier": "initialize_completion_screen",
            }
        ],
        preview=True,
    )

    assert "function.reanalyze()" in code
    assert 'elif entry["op"] == "reanalyze_function"' in code
    assert 'entry["verified"] = observed == entry["before"]' in code
    assert "bv.update_analysis_and_wait()" in code
    assert "bv.revert_undo_actions(state)" in code


def test_function_reanalysis_uses_a_previewed_batch(monkeypatch) -> None:
    calls = []

    def fake_previewed_batch(_repo_root, *, target, operations):
        calls.append((target, operations))
        return {
            "preview": {"success": True},
            "apply": {"success": True, "committed": True},
        }

    monkeypatch.setattr(
        _narrow_sync,
        "run_previewed_bn_batch",
        fake_previewed_batch,
    )
    result = _narrow_sync.reanalyze_functions(
        Path("."),
        target="snail-mail.exe",
        identifiers=("initialize_completion_screen", "flush_row_event_display"),
    )

    assert calls == [
        (
            "snail-mail.exe",
            [
                {
                    "op": "reanalyze_function",
                    "identifier": "initialize_completion_screen",
                },
                {
                    "op": "reanalyze_function",
                    "identifier": "flush_row_event_display",
                },
            ],
        )
    ]
    assert result[0]["op"] == "function_reanalysis_batch"
    assert result[0]["operation_count"] == 2


def test_previewed_batch_can_pin_timed_out_function_analysis() -> None:
    code = _narrow_sync._batch_python_code(
        [
            {
                "op": "ensure_function_analysis",
                "identifier": "draw_textured_quad_immediate",
            }
        ],
        preview=True,
    )

    assert "FunctionAnalysisSkipOverride.NeverSkipFunctionAnalysis" in code
    assert "ExceedFunctionAnalysisTimeSkipReason" in code
    assert "refusing to override a non-timeout analysis skip" in code
    assert "function.analysis_skip_override = desired_override" in code
    assert "function.reanalyze()" in code
    assert 'observed["analysis_skipped"] is False' in code
    assert 'observed["has_hlil"] is True' in code
    assert "analysis_skip_override_restorations" in code
    assert "function.analysis_skip_override = original_override" in code
    assert '"analysis already pinned with HLIL"' in code


def test_function_analysis_guard_uses_a_previewed_batch(monkeypatch) -> None:
    calls = []

    def fake_previewed_batch(_repo_root, *, target, operations):
        calls.append((target, operations))
        return {
            "preview": {"success": True},
            "apply": {"success": True, "committed": True},
        }

    monkeypatch.setattr(
        _narrow_sync,
        "run_previewed_bn_batch",
        fake_previewed_batch,
    )
    result = _narrow_sync.ensure_function_analysis(
        Path("."),
        target="snail-mail.exe",
        identifiers=("draw_textured_quad_immediate",),
    )

    assert calls == [
        (
            "snail-mail.exe",
            [
                {
                    "op": "ensure_function_analysis",
                    "identifier": "draw_textured_quad_immediate",
                }
            ],
        )
    ]
    assert result[0]["op"] == "function_analysis_guard_batch"
    assert result[0]["operation_count"] == 1


def test_user_variable_replay_skips_apply_when_current(monkeypatch) -> None:
    calls = []

    def fake_run_bn_batch(_repo_root, *, target, operations, preview):
        calls.append((target, operations, preview))
        raise AssertionError("current user variables should not open a transaction")

    monkeypatch.setattr(_narrow_sync, "run_bn_batch", fake_run_bn_batch)
    monkeypatch.setattr(
        _narrow_sync,
        "current_user_var_states",
        lambda *_args, **_kwargs: [{"changed": False}],
    )
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

    assert calls == []
    assert result[0]["status"] == "skipped"
    assert result[0]["reason"] == "already current"


def test_user_variable_removal_skips_apply_when_already_automatic(
    monkeypatch,
) -> None:
    calls = []

    def fake_run_bn_batch(_repo_root, *, target, operations, preview):
        calls.append((target, operations, preview))
        raise AssertionError("automatic variables should not open a transaction")

    monkeypatch.setattr(_narrow_sync, "run_bn_batch", fake_run_bn_batch)
    monkeypatch.setattr(
        _narrow_sync,
        "current_user_var_states",
        lambda *_args, **_kwargs: [{"changed": False}],
    )
    result = _narrow_sync.remove_user_var_updates(
        Path("."),
        target="snail-mail.exe",
        removals=(
            (
                "update_jet_particles",
                "RegisterVariableSourceType",
                543,
                67,
                "trail_velocity",
                "Vec3*",
            ),
        ),
    )

    assert calls == []
    assert result[0]["status"] == "skipped"
    assert result[0]["reason"] == "already automatic"


def test_user_var_readback_skips_type_parsing(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        code = args[args.index("--code") + 1]
        assert "parse_type_string" not in code
        assert "variable_sources = [function.vars]" in code
        assert 'getattr(function, "hlil", None)' in code
        assert 'getattr(function, "mlil", None)' in code
        assert "for variable in function_variables(function)" in code
        return {
            "result": {
                "user_vars": [
                    {
                        "identifier": "request_object_animation",
                        "source_type": "RegisterVariableSourceType",
                        "index": 29,
                        "storage": 71,
                        "observed": {
                            "name": "validation_object",
                            "type": "struct Object*",
                            "user_defined": True,
                        },
                    }
                ],
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)
    operations = _narrow_sync.user_var_operations(
        (
            (
                "request_object_animation",
                "RegisterVariableSourceType",
                29,
                71,
                "validation_object",
                "Object*",
            ),
        )
    )

    states = _narrow_sync.current_user_var_states(
        Path("."),
        target="snail-mail.exe",
        operations=operations,
    )

    assert len(calls) == 1
    assert states[0]["changed"] is False


def test_user_var_removal_readback_accepts_an_already_absent_identity(
    monkeypatch,
) -> None:
    def fake_run_bn(_repo_root, *args):
        code = args[args.index("--code") + 1]
        assert "if not candidates and allow_missing:" in code
        assert "allow_missing=deleting" in code
        return {
            "result": {
                "user_vars": [
                    {
                        "identifier": "enumerate_matching_archive_or_fs_entries",
                        "source_type": "RegisterVariableSourceType",
                        "index": 49,
                        "storage": 66,
                        "observed": None,
                    }
                ]
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)
    operations = _narrow_sync.user_var_removal_operations(
        (
            (
                "enumerate_matching_archive_or_fs_entries",
                "RegisterVariableSourceType",
                49,
                66,
                "archive_index",
                "ArchiveIndex*",
            ),
        )
    )

    states = _narrow_sync.current_user_var_states(
        Path("."),
        target="snail-mail.exe",
        operations=operations,
    )

    assert states[0]["changed"] is False
    assert states[0]["missing"] is True
    assert states[0]["expected"]["user_defined"] is False


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
    monkeypatch.setattr(
        _narrow_sync,
        "current_user_var_states",
        lambda *_args, **_kwargs: [{"changed": True}],
    )
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


def test_user_variable_replay_batches_only_changed_updates(monkeypatch) -> None:
    calls = []

    def fake_run_bn_batch(_repo_root, *, target, operations, preview):
        calls.append((target, operations, preview))
        return {
            "success": True,
            "preview": preview,
            "committed": not preview,
            "message": "ok",
            "affected_functions": ["build_subgame_level"],
            "results": [{"changed": True}],
        }

    monkeypatch.setattr(_narrow_sync, "run_bn_batch", fake_run_bn_batch)
    monkeypatch.setattr(
        _narrow_sync,
        "current_user_var_states",
        lambda *_args, **_kwargs: [
            {"changed": False},
            {"changed": True},
            {"changed": False},
        ],
    )
    updates = (
        (
            "build_subgame_level",
            "RegisterVariableSourceType",
            1272,
            66,
            "jetpack_channel",
            "Weapon*",
        ),
        (
            "build_subgame_level",
            "RegisterVariableSourceType",
            1367,
            67,
            "weapon_channel_0",
            "Weapon*",
        ),
        (
            "build_subgame_level",
            "RegisterVariableSourceType",
            1455,
            67,
            "weapon_channel_1",
            "Weapon*",
        ),
    )

    result = _narrow_sync.apply_user_var_updates(
        Path("."),
        target="snail-mail.exe",
        updates=updates,
    )

    expected_pending = [_narrow_sync.user_var_operations(updates)[1]]
    assert calls == [
        ("snail-mail.exe", expected_pending, True),
        ("snail-mail.exe", expected_pending, False),
    ]
    assert [entry["op"] for entry in result] == [
        "user_var_set",
        "user_var_set",
        "user_var_batch",
    ]
    assert result[0]["status"] == "skipped"
    assert result[1]["status"] == "skipped"
    assert result[2]["operation_count"] == 1
    assert result[2]["operations"] == expected_pending


def test_split_user_variable_replay_previews_before_saved_apply(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        code = args[-1]
        preview = "preview = True" in code
        return {
            "result": {
                "success": True,
                "preview": preview,
                "committed": not preview,
                "changed": True,
                "snapshot_saved": not preview,
                "operation": {
                    "identifier": "load_builtin_segment_definitions",
                    "before_hlil": "raw_segments = nullptr",
                    "after_hlil": "int32_t grid_offset = 0",
                },
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)
    result = _narrow_sync.apply_split_user_var_update(
        Path("."),
        target="snail-mail.exe",
        identifier="load_builtin_segment_definitions",
        definitions=(
            ("0x44809d", "mlil", "StackVariableSourceType", 61, 4),
            ("0x4480c2", "mlil_ssa", "StackVariableSourceType", 98, 4),
            ("0x448109", "mlil", "StackVariableSourceType", 169, 4),
        ),
        target_var=("StackVariableSourceType", 61, 4),
        variable_name="grid_offset",
        variable_type="int32_t",
    )

    assert ["preview = True" in call[-1] for call in calls] == [True, False]
    assert result[0]["op"] == "split_user_var_set"
    assert result[0]["status"] == "verified"
    assert "instruction.get_split_var_for_definition" in calls[0][-1]
    assert 'getattr(instruction, "dest", None)' in calls[0][-1]
    assert "function.split_var(split_variable)" in calls[0][-1]
    assert "function.merge_vars(" in calls[0][-1]
    assert "source_keys.issubset(expected_source_keys)" in calls[0][-1]
    assert "for variable in function.split_vars" in calls[0][-1]
    assert "for merge_target, sources in function.merged_vars.items()" in calls[0][-1]
    assert "bv.file.save_auto_snapshot()" in calls[0][-1]


def test_split_user_variable_replay_skips_current_cluster(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {
            "result": {
                "success": True,
                "preview": True,
                "committed": False,
                "changed": False,
                "snapshot_saved": False,
                "operation": {
                    "identifier": "load_builtin_segment_definitions",
                },
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)
    result = _narrow_sync.apply_split_user_var_update(
        Path("."),
        target="snail-mail.exe",
        identifier="load_builtin_segment_definitions",
        definitions=(("0x44809d", "mlil", "StackVariableSourceType", 61, 4),),
        target_var=("StackVariableSourceType", 61, 4),
        variable_name="grid_offset",
        variable_type="int32_t",
    )

    assert len(calls) == 1
    assert result[0]["status"] == "skipped"
    assert result[0]["reason"] == "already current"
    assert "if changed_identifiers:" in calls[0][-1]
    assert "functions[identifier].reanalyze()" in calls[0][-1]


def test_split_user_variable_batch_replays_in_one_transaction(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        code = args[-1]
        preview = "preview = True" in code
        return {
            "result": {
                "success": True,
                "preview": preview,
                "committed": not preview,
                "changed": True,
                "snapshot_saved": not preview,
                "operation_results": [
                    {
                        "identifier": "initialize_slalom_path_template_pair",
                        "changed": True,
                    },
                    {
                        "identifier": "initialize_slalom_path_template_pair",
                        "changed": False,
                    },
                ],
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)
    result = _narrow_sync.apply_split_user_var_updates(
        Path("."),
        target="snail-mail.exe",
        updates=(
            (
                "initialize_slalom_path_template_pair",
                (
                    ("0x41f7ad", "mlil", "StackVariableSourceType", 77, 8),
                    ("0x41f7b3", "mlil_ssa", "StackVariableSourceType", 83, 8),
                ),
                ("StackVariableSourceType", 77, 8),
                "lead_sample_index",
                "int32_t",
            ),
            (
                "initialize_slalom_path_template_pair",
                (("0x41f8de", "mlil", "StackVariableSourceType", 382, 8),),
                ("StackVariableSourceType", 382, 8),
                "tail_sample_z",
                "float",
            ),
        ),
    )

    assert ["preview = True" in call[-1] for call in calls] == [True, False]
    assert [entry["status"] for entry in result] == ["verified", "skipped"]
    assert calls[0][-1].count("bv.begin_undo_actions()") == 1
    assert calls[0][-1].count("bv.file.save_auto_snapshot()") == 1
    assert "Resolve every definition against the same pre-mutation IL" in calls[0][-1]
    assert calls[0][-1].index("pending_splits.append(") < calls[0][-1].index(
        "function.split_var(split_variable)"
    )


def test_split_user_variable_batch_rejects_overlapping_identities() -> None:
    repeated_definition = (
        ("0x41f7ad", "mlil", "StackVariableSourceType", 77, 8),
    )
    with pytest.raises(ValueError, match="disjoint identities"):
        _narrow_sync.apply_split_user_var_updates(
            Path("."),
            target="snail-mail.exe",
            updates=(
                (
                    "initialize_slalom_path_template_pair",
                    repeated_definition,
                    ("StackVariableSourceType", 77, 8),
                    "lead_sample_index",
                    "int32_t",
                ),
                (
                    "initialize_slalom_path_template_pair",
                    repeated_definition,
                    ("StackVariableSourceType", 77, 8),
                    "other_owner",
                    "int32_t",
                ),
            ),
        )


def test_split_away_user_variable_replay_types_the_residual_lifetime(
    monkeypatch,
) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        code = args[-1]
        preview = "preview = True" in code
        return {
            "result": {
                "success": True,
                "preview": preview,
                "committed": not preview,
                "changed": True,
                "snapshot_saved": not preview,
                "operation": {
                    "identifier": "set_snail_weapon",
                    "before_hlil": "struct Snail* snail_1 = snail",
                    "after_hlil": "int32_t target_channel_2_state",
                },
            }
        }

    monkeypatch.setattr(_narrow_sync, "run_bn", fake_run_bn)
    result = _narrow_sync.apply_split_away_user_var_update(
        Path("."),
        target="snail-mail.exe",
        identifier="set_snail_weapon",
        detached_definitions=(
            ("0x445920", "mlil", "StackVariableSourceType", 524288, -4),
        ),
        residual_var=("StackVariableSourceType", 40, -4),
        variable_name="target_channel_2_state",
        variable_type="int32_t",
    )

    assert ["preview = True" in call[-1] for call in calls] == [True, False]
    assert result[0]["op"] == "split_away_user_var_set"
    assert result[0]["status"] == "verified"
    assert '"merge_definitions": false' in calls[0][-1]
    assert "definition_keys.issubset(split_keys)" in calls[0][-1]
    assert "residual target variable missing after split" in calls[0][-1]


def test_split_user_variable_replay_validates_definition_specs() -> None:
    with pytest.raises(ValueError, match="mlil or mlil_ssa"):
        _narrow_sync.apply_split_user_var_update(
            Path("."),
            target="snail-mail.exe",
            identifier="load_builtin_segment_definitions",
            definitions=(("0x44809d", "hlil", "StackVariableSourceType", 61, 4),),
            target_var=("StackVariableSourceType", 61, 4),
            variable_name="grid_offset",
            variable_type="int32_t",
        )


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


def test_track_cache_face_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_track_cache_face_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Vec3", "0x0C"),
        ("ObjectUv", "0x08"),
        ("ObjectFaceQuad", "0x30"),
        ("Object", "0xDC"),
        ("SegmentCache", "0xA7F8"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("ObjectFaceQuad", "0x02", "vertex_0", "uint16_t"),
        ("ObjectFaceQuad", "0x10", "uv", "ObjectUv[4]"),
        ("Object", "0x5C", "facequads", "ObjectFaceQuad*"),
        ("SegmentCache", "0x54", "owner_subgame", "SubgameRuntime*"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        ("RegisterVariableSourceType", 9, 71, "face_byte_offset", "int32_t"),
        ("StackVariableSourceType", 25, -16, "face_index", "int32_t"),
        ("StackVariableSourceType", 0, -12, "local_position", "Vec3"),
        (
            "RegisterVariableSourceType",
            71,
            66,
            "face_vertex_0",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            356,
            67,
            "source_vertex_3",
            "uint16_t",
        ),
        (
            "RegisterVariableSourceType",
            388,
            66,
            "next_index_count",
            "int32_t",
        ),
    ):
        expected = (
            '        "append_track_cache_object",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert "face_flag_bytes" not in replay


def test_track_cache_vertex_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_track_cache_vertex_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Vec3", "0x0C"),
        ("ObjectRenderVertex", "0x18"),
        ("Object", "0xDC"),
        ("SegmentCache", "0xA7F8"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("Vec3", "0x04", "y", "float"),
        ("ObjectRenderVertex", "0x0C", "diffuse", "uint32_t"),
        ("ObjectRenderVertex", "0x14", "v", "float"),
        ("Object", "0x38", "vertices", "Vec3*"),
        (
            "SegmentCache",
            "0x2C",
            "shared_vertex_buffers",
            "ObjectRenderVertex*[5]",
        ),
        ("SegmentCache", "0xA7EC", "build_cache_row_base", "float"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        ("StackVariableSourceType", 0, -12, "transformed", "Vec3"),
        (
            "RegisterVariableSourceType",
            20,
            66,
            "source_vertex",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            114,
            68,
            "existing_vertex_z_cursor",
            "float*",
        ),
        (
            "RegisterVariableSourceType",
            220,
            66,
            "staged_vertex",
            "ObjectRenderVertex*",
        ),
        (
            "RegisterVariableSourceType",
            252,
            68,
            "next_vertex_count",
            "int32_t",
        ),
    ):
        expected = (
            '        "add_track_cache_vertex",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert "x87_r7" not in replay


def test_immediate_quad_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_immediate_quad_lifetimes.py"
    ).read_text(encoding="utf-8")
    header = (HEADER_DIR / "bn_object_render_types.h").read_text(
        encoding="utf-8"
    )

    assert "typedef struct ImmediateQuadVertexBlock {" in header
    assert "ObjectRenderVertex vertices[4];" in header
    assert "borrowed 0x60-byte immediate-mode lock" in header

    for owner_name, expected_size in (
        ("ObjectRenderVertex", "0x18"),
        ("ImmediateQuadVertexBlock", "0x60"),
        ("ObjectVertexBuffer", "0x04"),
        ("ObjectRenderBuffers", "0x0C"),
        ("Direct3DRenderer", "0xBCC0"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("ObjectRenderVertex", "0x0C", "diffuse", "uint32_t"),
        ("ObjectRenderVertex", "0x14", "v", "float"),
        (
            "ImmediateQuadVertexBlock",
            "0x00",
            "vertices",
            "ObjectRenderVertex[4]",
        ),
        (
            "ObjectRenderBuffers",
            "0x08",
            "vertex_buffer",
            "ObjectVertexBuffer*",
        ),
        (
            "Direct3DRenderer",
            "0xBB88",
            "renderer_state",
            "ObjectRenderBuffers*",
        ),
        (
            "Direct3DRenderer",
            "0xBB94",
            "device",
            "Direct3DDevice8*",
        ),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    expected = (
        '        "draw_textured_quad_immediate",\n'
        '        "StackVariableSourceType",\n'
        "        0,\n"
        "        -8,\n"
        '        "quad",\n'
        '        "ImmediateQuadVertexBlock*"'
    )
    assert expected in replay
    assert 'include_types=("ImmediateQuadVertexBlock",)' in replay
    assert replay.index("types_declare_missing_only(") < replay.index(
        "ensure_function_analysis("
    )
    assert replay.index("ensure_function_analysis(") < replay.index(
        "apply_user_var_updates("
    )
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "float* data" not in replay


def test_track_cache_builder_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_track_cache_builder_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Vec3", "0x0C"),
        ("Fringe", "0x38"),
        ("TrackRowCell", "0x54"),
        ("TextureRef", "0xA4"),
        ("ObjectFaceQuad", "0x30"),
        ("ObjectRenderVertex", "0x18"),
        ("Object", "0xDC"),
        ("SegmentCache", "0xA7F8"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("BodBase", "0x24", "object", "Object*"),
        ("TrackRowCell", "0x40", "lane_and_flags", "uint32_t"),
        ("ObjectFaceQuad", "0x0C", "texture_ref", "TextureRef*"),
        ("Object", "0xC0", "render_buffers", "ObjectRenderBuffers*"),
        ("Object", "0xC8", "index_buffer", "ObjectIndexBuffer*"),
        ("SegmentCache", "0x54", "owner_subgame", "SubgameRuntime*"),
        ("SegmentCache", "0x58", "slots", "TrackRenderCacheSlot[143][5]"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        (
            "RegisterVariableSourceType",
            65,
            73,
            "cell_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            240,
            68,
            "fringe_object",
            "Fringe*",
        ),
        (
            "RegisterVariableSourceType",
            305,
            67,
            "fringe_texture_source",
            "Fringe*",
        ),
        (
            "RegisterVariableSourceType",
            311,
            68,
            "fringe_source_object",
            "Object*",
        ),
        (
            "RegisterVariableSourceType",
            459,
            66,
            "warning_source_object",
            "Object*",
        ),
        (
            "RegisterVariableSourceType",
            771,
            66,
            "floor_source_object",
            "Object*",
        ),
        (
            "RegisterVariableSourceType",
            466,
            67,
            "source_facequads",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            1042,
            71,
            "cache_object_ref",
            "Object**",
        ),
        (
            "RegisterVariableSourceType",
            1206,
            66,
            "index_buffer_unlock",
            "ObjectIndexBufferResource*",
        ),
        (
            "StackVariableSourceType",
            0,
            -52,
            "locked_vertices",
            "ObjectRenderVertex*",
        ),
        (
            "StackVariableSourceType",
            0,
            -48,
            "locked_indices",
            "uint16_t*",
        ),
        (
            "RegisterVariableSourceType",
            1122,
            72,
            "staged_vertices",
            "ObjectRenderVertex*",
        ),
        (
            "RegisterVariableSourceType",
            1156,
            72,
            "staged_indices",
            "uint16_t*",
        ),
        (
            "RegisterVariableSourceType",
            1386,
            66,
            "max_scan_object",
            "Object*",
        ),
    ):
        expected = (
            '        "build_track_render_caches",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert "apply_split_user_var_update" not in replay
    assert "cache_name" not in replay


def test_track_cache_manager_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_track_cache_manager_lifetimes.py"
    ).read_text(encoding="utf-8")
    track_sync = (BINJA_DIR / "sync_track_render_cache_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    narrow_header = (HEADER_DIR / "bn_track_render_cache_types.h").read_text(
        encoding="utf-8"
    )

    cursor_definition = (
        "typedef struct TrackRenderCacheSlotCursor {\n"
        "    uint8_t manager_prefix[0x58];\n"
        "    TrackRenderCacheSlot slot;\n"
        "} TrackRenderCacheSlotCursor;"
    )
    assert cursor_definition in analysis_header
    assert cursor_definition in narrow_header
    assert '"TrackRenderCacheSlotCursor",' in track_sync
    assert '0x58: ("slot", "TrackRenderCacheSlot")' in replay
    assert '"0x58", "slot", "TrackRenderCacheSlot"' in track_sync

    for owner_name, expected_size in (
        ("BodBase", "0x38"),
        ("TrackRenderCacheSlot", "0x3C"),
        ("TrackRenderCacheSlotCursor", "0x94"),
        ("ObjectRenderVertex", "0x18"),
        ("Object", "0xDC"),
        ("SegmentCache", "0xA7F8"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for source_type, index, storage, name, type_name in (
        ("StackVariableSourceType", 87, -8, "slot_base", "int32_t"),
        (
            "RegisterVariableSourceType",
            115,
            72,
            "slot_cursor",
            "TrackRenderCacheSlotCursor*",
        ),
        (
            "RegisterVariableSourceType",
            260,
            67,
            "group_index_zero_bytes",
            "uint8_t*",
        ),
        (
            "RegisterVariableSourceType",
            315,
            66,
            "skirt_object",
            "Object*",
        ),
        (
            "RegisterVariableSourceType",
            411,
            66,
            "shared_index_buffer",
            "uint16_t*",
        ),
    ):
        expected = (
            '        "initialize_track_render_cache_manager",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert "first_group_index" not in replay
    assert "shared_buffer_lane" not in replay
    assert '"slot_cursor",\n        "TrackRenderCacheSlot*"' not in replay


def test_track_cache_row_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_track_cache_row_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("BodNode", "0x10"),
        ("Vec3", "0x0C"),
        ("tColour", "0x10"),
        ("BodBase", "0x38"),
        ("TrackRenderCacheSlot", "0x3C"),
        ("SegmentCache", "0xA7F8"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("BodNode", "0x08", "list_prev", "BodNode*"),
        ("BodNode", "0x0C", "list_next", "BodNode*"),
        ("Vec3", "0x08", "z", "float"),
        ("tColour", "0x0C", "a", "float"),
        ("BodBase", "0x10", "position", "Vec3"),
        ("BodBase", "0x28", "color", "tColour"),
        ("TrackRenderCacheSlot", "0x00", "bod", "BodBase"),
        ("SegmentCache", "0x58", "slots", "TrackRenderCacheSlot[143][5]"),
        ("SegmentCache", "0xA7F4", "next_cache_row_index", "int32_t"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        (
            "RegisterVariableSourceType",
            56,
            67,
            "fringe_active_list",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            78,
            66,
            "fringe_slot",
            "TrackRenderCacheSlot*",
        ),
        (
            "RegisterVariableSourceType",
            149,
            66,
            "fringe_position",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            196,
            68,
            "fringe_color",
            "tColour*",
        ),
        (
            "StackVariableSourceType",
            0,
            -16,
            "skirt_color_out",
            "tColour",
        ),
        (
            "RegisterVariableSourceType",
            252,
            66,
            "floor_slot",
            "TrackRenderCacheSlot*",
        ),
        (
            "RegisterVariableSourceType",
            392,
            66,
            "slide_slot",
            "TrackRenderCacheSlot*",
        ),
        (
            "RegisterVariableSourceType",
            534,
            66,
            "ramp_slot",
            "TrackRenderCacheSlot*",
        ),
        (
            "RegisterVariableSourceType",
            676,
            66,
            "warning_slot",
            "TrackRenderCacheSlot*",
        ),
        (
            "RegisterVariableSourceType",
            742,
            66,
            "warning_position",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            772,
            67,
            "warning_color",
            "tColour*",
        ),
    ):
        expected = (
            '        "update_track_render_cache_rows",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert "row_index_pointer" not in replay


def test_object_facequad_normal_pair_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_object_facequad_normal_pair_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Vec3", "0x0C"),
        ("ObjectFaceQuad", "0x30"),
        ("Object", "0xDC"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("Vec3", "0x08", "z", "float"),
        ("ObjectFaceQuad", "0x00", "", "union"),
        ("ObjectFaceQuad", "0x02", "vertex_0", "uint16_t"),
        ("ObjectFaceQuad", "0x08", "vertex_3", "uint16_t"),
        ("Object", "0x38", "vertices", "Vec3*"),
        ("Object", "0x5C", "facequads", "ObjectFaceQuad*"),
        ("Object", "0x60", "facequad_normals", "Vec3*"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        (
            "RegisterVariableSourceType",
            31,
            69,
            "face_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            39,
            66,
            "face",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            50,
            73,
            "vertex_0_for_lhs",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            67,
            68,
            "vertex_1",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            144,
            66,
            "vertex_2",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            230,
            66,
            "output_normal_a",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            256,
            66,
            "quad_face",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            297,
            66,
            "vertex_3",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            385,
            67,
            "output_normal_b",
            "Vec3*",
        ),
    ):
        expected = (
            '        "calc_object_facequad_normals_simple",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '"face_byte_offset",\n        "ObjectFaceQuad*"' not in replay
    assert '"normal_byte_offset",\n        "Vec3*"' not in replay


def test_object_normal_rebuild_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_object_normal_rebuild_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Vec3", "0x0C"),
        ("ObjectFaceQuad", "0x30"),
        ("Object", "0xDC"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("Vec3", "0x08", "z", "float"),
        ("ObjectFaceQuad", "0x00", "", "union"),
        ("ObjectFaceQuad", "0x02", "vertex_0", "uint16_t"),
        ("ObjectFaceQuad", "0x08", "vertex_3", "uint16_t"),
        ("Object", "0x38", "vertices", "Vec3*"),
        ("Object", "0x44", "vertex_normals", "Vec3*"),
        ("Object", "0x5C", "facequads", "ObjectFaceQuad*"),
        ("Object", "0x60", "facequad_normals", "Vec3*"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        (
            "RegisterVariableSourceType",
            26,
            66,
            "allocated_normal_tally",
            "float*",
        ),
        (
            "RegisterVariableSourceType",
            34,
            69,
            "normal_tally",
            "float*",
        ),
        (
            "RegisterVariableSourceType",
            63,
            73,
            "geometry_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            87,
            66,
            "primary_face",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            116,
            68,
            "primary_vertex_1",
            "Vec3*",
        ),
        (
            "StackVariableSourceType",
            0,
            -84,
            "face_normal",
            "Vec3",
        ),
        (
            "RegisterVariableSourceType",
            518,
            68,
            "output_quad_normal",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            545,
            67,
            "accumulation_face",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            575,
            66,
            "quad_vertex_0_normal",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            1007,
            66,
            "primary_vertex_3_normal",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            1136,
            66,
            "validation_face",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            1240,
            71,
            "normal_tally_cursor",
            "float*",
        ),
        (
            "RegisterVariableSourceType",
            1253,
            66,
            "averaged_normal",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            1295,
            66,
            "inverted_normal",
            "Vec3*",
        ),
    ):
        expected = (
            '        "calc_object_facequad_normals",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '"geometry_byte_offset",\n        "Vec3*"' not in replay
    assert '"geometry_byte_offset",\n        "ObjectFaceQuad*"' not in replay


def test_object_edge_merge_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_object_edge_merge_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Vec3", "0x0C"),
        ("ObjectToonEdge", "0x24"),
        ("Object", "0xDC"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("Vec3", "0x08", "z", "float"),
        ("ObjectToonEdge", "0x00", "flags", "ObjectToonEdgeFlag"),
        ("ObjectToonEdge", "0x08", "vertex_b", "int32_t"),
        ("ObjectToonEdge", "0x10", "normal_b", "int32_t"),
        ("ObjectToonEdge", "0x14", "direction", "Vec3"),
        ("ObjectToonEdge", "0x20", "length", "float"),
        ("Object", "0x38", "vertices", "Vec3*"),
        ("Object", "0x60", "facequad_normals", "Vec3*"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    assert (
        '("0x4305f8", "mlil_ssa", "StackVariableSourceType", 88, 8)'
        in replay
    )
    assert "TARGET_VERTEX_VAR = (\n    \"StackVariableSourceType\",\n    88,\n    8," in replay
    assert 'variable_name="target_vertex"' in replay
    assert 'variable_type="Vec3*"' in replay

    for source_type, index, storage, name, type_name in (
        (
            "RegisterVariableSourceType",
            97,
            71,
            "edge_vertex_b_cursor",
            "int32_t*",
        ),
        (
            "RegisterVariableSourceType",
            109,
            73,
            "existing_vertex_a",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            177,
            69,
            "candidate_vertex_a",
            "Vec3*",
        ),
        (
            "StackVariableSourceType",
            0,
            -48,
            "direction",
            "Vec3",
        ),
        (
            "RegisterVariableSourceType",
            504,
            72,
            "edge_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            573,
            67,
            "face_normal_a",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            603,
            66,
            "face_normal_b",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            714,
            66,
            "shift_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            723,
            72,
            "shift_source_edge",
            "ObjectToonEdge*",
        ),
        (
            "RegisterVariableSourceType",
            727,
            73,
            "shift_destination_edge",
            "ObjectToonEdge*",
        ),
    ):
        expected = (
            '        "add_object_edge",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "apply_split_user_var_update" in replay
    assert "apply_user_var_updates" in replay
    assert '"edge_vertex_b_cursor",\n        "ObjectToonEdge*"' not in replay
    assert '"edge_byte_offset",\n        "ObjectToonEdge*"' not in replay
    assert '"shift_byte_offset",\n        "ObjectToonEdge*"' not in replay


def test_object_edge_builder_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_object_edge_builder_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Vec3", "0x0C"),
        ("TransformMatrix", "0x40"),
        ("ObjectFaceQuad", "0x30"),
        ("ObjectToonEdge", "0x24"),
        ("ObjectVertexBuffer", "0x04"),
        ("ObjectRenderBuffers", "0x0C"),
        ("ObjectIndexBufferResource", "0x04"),
        ("ObjectIndexBuffer", "0x04"),
        ("Object", "0xDC"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("Vec3", "0x08", "z", "float"),
        ("TransformMatrix", "0x30", "position", "Vec3"),
        ("ObjectFaceQuad", "0x08", "vertex_3", "uint16_t"),
        ("ObjectToonEdge", "0x00", "flags", "ObjectToonEdgeFlag"),
        ("ObjectToonEdge", "0x14", "direction", "Vec3"),
        ("ObjectToonEdge", "0x20", "length", "float"),
        ("ObjectVertexBuffer", "0x00", "vtbl", "ObjectVertexBufferVtbl*"),
        ("ObjectRenderBuffers", "0x08", "vertex_buffer", "ObjectVertexBuffer*"),
        (
            "ObjectIndexBufferResource",
            "0x00",
            "vtbl",
            "ObjectIndexBufferResourceVtbl*",
        ),
        (
            "ObjectIndexBuffer",
            "0x00",
            "buffer",
            "ObjectIndexBufferResource*",
        ),
        ("Object", "0x2C", "vertex_count", "int32_t"),
        ("Object", "0x38", "vertices", "Vec3*"),
        ("Object", "0x54", "facequad_count", "int32_t"),
        ("Object", "0x5C", "facequads", "ObjectFaceQuad*"),
        ("Object", "0x60", "facequad_normals", "Vec3*"),
        ("Object", "0x70", "edge_count", "int32_t"),
        ("Object", "0x74", "edges", "ObjectToonEdge*"),
        ("Object", "0xC0", "render_buffers", "ObjectRenderBuffers*"),
        ("Object", "0xC4", "grouped_vertex_count", "int32_t"),
        ("Object", "0xD8", "toon_index_buffer", "ObjectIndexBuffer*"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for definition in (
        '("0x4308dc", "mlil_ssa", "StackVariableSourceType", 44, -4)',
        '("0x4308ea", "mlil_ssa", "StackVariableSourceType", 58, -4)',
        '("0x430986", "mlil_ssa", "StackVariableSourceType", 214, -4)',
        '("0x4309ac", "mlil_ssa", "StackVariableSourceType", 252, -4)',
        '("0x4309b4", "mlil_ssa", "StackVariableSourceType", 260, -4)',
        '("0x4309f8", "mlil_ssa", "StackVariableSourceType", 328, -4)',
    ):
        assert definition in replay

    for variable_name, variable_type in (
        ("face_index", "int32_t"),
        ("edge_byte_offset_spill", "int32_t"),
    ):
        assert f'variable_name="{variable_name}"' in replay
        assert f'variable_type="{variable_type}"' in replay

    for source_type, index, storage, name, type_name in (
        (
            "RegisterVariableSourceType",
            16,
            72,
            "face_cursor",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            25,
            73,
            "build_edges",
            "ObjectToonEdge*",
        ),
        (
            "RegisterVariableSourceType",
            250,
            68,
            "edge_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            271,
            72,
            "shift_source_edge",
            "ObjectToonEdge*",
        ),
        (
            "RegisterVariableSourceType",
            275,
            73,
            "shift_destination_edge",
            "ObjectToonEdge*",
        ),
        (
            "RegisterVariableSourceType",
            347,
            72,
            "copy_source_edges",
            "ObjectToonEdge*",
        ),
        (
            "RegisterVariableSourceType",
            353,
            73,
            "copy_destination_edges",
            "ObjectToonEdge*",
        ),
        (
            "RegisterVariableSourceType",
            367,
            72,
            "copy_source_tail",
            "uint8_t*",
        ),
        (
            "RegisterVariableSourceType",
            367,
            73,
            "copy_destination_tail",
            "uint8_t*",
        ),
    ):
        expected = (
            '        "calc_object_edges",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    for source_type, index, storage, name, type_name in (
        (
            "StackVariableSourceType",
            0,
            -176,
            "toon_indices",
            "uint16_t*",
        ),
        (
            "StackVariableSourceType",
            271,
            -160,
            "edge_index",
            "int32_t",
        ),
        (
            "StackVariableSourceType",
            0,
            -156,
            "view_vector",
            "Vec3",
        ),
        (
            "StackVariableSourceType",
            461,
            -144,
            "side_b",
            "float",
        ),
        (
            "StackVariableSourceType",
            0,
            -140,
            "edge_delta",
            "Vec3",
        ),
        (
            "StackVariableSourceType",
            0,
            -128,
            "projection",
            "TransformMatrix",
        ),
        (
            "RegisterVariableSourceType",
            288,
            71,
            "edge_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            296,
            72,
            "emitted_index_count",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            303,
            66,
            "toon_index_buffer",
            "ObjectIndexBufferResource*",
        ),
        (
            "RegisterVariableSourceType",
            322,
            66,
            "edge",
            "ObjectToonEdge*",
        ),
        (
            "RegisterVariableSourceType",
            361,
            68,
            "normal_a_index",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            374,
            73,
            "normal_a",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            389,
            67,
            "normal_b",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            403,
            66,
            "vertex",
            "Vec3*",
        ),
        (
            "RegisterVariableSourceType",
            534,
            66,
            "toon_index_buffer_for_unlock",
            "ObjectIndexBufferResource*",
        ),
    ):
        expected = (
            '        "render_object_toon",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "apply_split_user_var_update" in replay
    assert "apply_user_var_updates" in replay
    assert '"edge_byte_offset",\n        "Object*"' not in replay
    assert '"edge_byte_offset",\n        "ObjectToonEdge*"' not in replay
    assert '"edge_byte_offset",\n        "Vec3*"' not in replay
    assert '"edge_byte_offset_spill",\n            variable_type="Object*"' not in replay


def test_object_list_texture_replace_lifetime_replay_stays_guarded() -> None:
    owner_sync = (BINJA_DIR / "sync_object_render_types.py").read_text(
        encoding="utf-8"
    )
    replay = (
        BINJA_DIR / "sync_object_list_texture_replace_lifetimes.py"
    ).read_text(encoding="utf-8")
    header = (HEADER_DIR / "bn_object_render_types.h").read_text(
        encoding="utf-8"
    )

    prototype = (
        "void __cdecl replace_object_group_texture_refs("
        "Object* object, TextureRef* new_texture, TextureRef* old_texture)"
    )
    assert prototype in owner_sync
    for fragment in (
        "void __cdecl replace_object_group_texture_refs(",
        "Object* object, TextureRef* new_texture, TextureRef* old_texture)",
    ):
        assert fragment in replay
    for fragment in (
        "void __cdecl replace_object_group_texture_refs(",
        "Object* object, TextureRef* new_texture, TextureRef* old_texture);",
    ):
        assert fragment in header

    for owner_name, expected_size in (
        ("ObjectFaceQuad", "0x30"),
        ("Object", "0xDC"),
        ("ObjectList", "0x0C"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("ObjectFaceQuad", "0x0C", "texture_ref", "TextureRef*"),
        ("Object", "0x10", "flags", "ObjectFlag"),
        ("Object", "0x2C", "vertex_count", "int32_t"),
        ("Object", "0x54", "facequad_count", "int32_t"),
        ("Object", "0x5C", "facequads", "ObjectFaceQuad*"),
        ("Object", "0x64", "texture_group_count", "int32_t"),
        ("Object", "0xD0", "group_texture_refs", "TextureRef**"),
        ("ObjectList", "0x00", "count", "int32_t"),
        ("ObjectList", "0x08", "objects", "Object*"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        (
            "RegisterVariableSourceType",
            6,
            66,
            "object_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            33,
            66,
            "current_object",
            "Object*",
        ),
        (
            "RegisterVariableSourceType",
            52,
            68,
            "face_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            54,
            67,
            "facequads",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            61,
            67,
            "texture_ref_slot",
            "TextureRef**",
        ),
        (
            "StackVariableSourceType",
            82,
            -36,
            "current_object_argument",
            "Object*",
        ),
    ):
        expected = (
            '        "replace_object_list_texture_refs",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    for index, storage, name, type_name in (
        (524288, 68, "object", "Object*"),
        (16, 67, "group_index", "int32_t"),
        (24, 72, "old_texture", "TextureRef*"),
        (29, 73, "new_texture", "TextureRef*"),
        (33, 66, "group_texture_refs", "TextureRef**"),
        (39, 69, "texture", "TextureRef*"),
        (42, 66, "texture_slot", "TextureRef**"),
    ):
        expected = (
            '        "replace_object_group_texture_refs",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_direct_proto_update" in replay
    assert "apply_user_var_updates" in replay
    assert '"object_byte_offset",\n        "Object*"' not in replay
    assert '"face_byte_offset",\n        "ObjectFaceQuad*"' not in replay


def test_object_texture_group_lifetime_replay_stays_guarded() -> None:
    replay = (BINJA_DIR / "sync_object_texture_group_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for owner_name, expected_size in (
        ("TransformMatrix", "0x40"),
        ("tColour", "0x10"),
        ("TextureRef", "0xA4"),
        ("ObjectFaceQuad", "0x30"),
        ("ObjectVertexBuffer", "0x04"),
        ("ObjectRenderBuffers", "0x0C"),
        ("ObjectIndexBufferResource", "0x04"),
        ("ObjectIndexBuffer", "0x04"),
        ("Object", "0xDC"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("tColour", "0x0C", "a", "float"),
        ("TextureRef", "0x00", "flags", "TextureRefFlags"),
        ("ObjectFaceQuad", "0x0C", "texture_ref", "TextureRef*"),
        ("ObjectVertexBuffer", "0x00", "vtbl", "ObjectVertexBufferVtbl*"),
        ("ObjectRenderBuffers", "0x08", "vertex_buffer", "ObjectVertexBuffer*"),
        (
            "ObjectIndexBufferResource",
            "0x00",
            "vtbl",
            "ObjectIndexBufferResourceVtbl*",
        ),
        (
            "ObjectIndexBuffer",
            "0x00",
            "buffer",
            "ObjectIndexBufferResource*",
        ),
        ("Object", "0x10", "flags", "ObjectFlag"),
        ("Object", "0x14", "blend_mode", "int32_t"),
        ("Object", "0x18", "override_texture_ref", "TextureRef*"),
        ("Object", "0x2C", "vertex_count", "int32_t"),
        ("Object", "0x54", "facequad_count", "int32_t"),
        ("Object", "0x5C", "facequads", "ObjectFaceQuad*"),
        ("Object", "0x64", "texture_group_count", "int32_t"),
        ("Object", "0x6C", "texture_group_ends", "int32_t*"),
        ("Object", "0xC0", "render_buffers", "ObjectRenderBuffers*"),
        ("Object", "0xC4", "grouped_vertex_count", "int32_t"),
        ("Object", "0xC8", "index_buffer", "ObjectIndexBuffer*"),
        ("Object", "0xCC", "group_index_starts", "int32_t*"),
        ("Object", "0xD0", "group_texture_refs", "TextureRef**"),
        ("Object", "0xD4", "group_primitive_counts", "int32_t*"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        (
            "StackVariableSourceType",
            0,
            -48,
            "swap_face",
            "ObjectFaceQuad",
        ),
        (
            "RegisterVariableSourceType",
            47,
            68,
            "texture_ref",
            "TextureRef*",
        ),
        (
            "StackVariableSourceType",
            51,
            -56,
            "retained_texture_ref",
            "TextureRef*",
        ),
        (
            "RegisterVariableSourceType",
            63,
            68,
            "scan_face_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            66,
            66,
            "insert_face_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            69,
            68,
            "scan_face",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            75,
            66,
            "insert_face",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            126,
            73,
            "insert_copy_destination",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            142,
            73,
            "scan_copy_destination",
            "ObjectFaceQuad*",
        ),
    ):
        expected = (
            '        "sort_object_faces_by_texture_group",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    for source_type, index, storage, name, type_name in (
        (
            "RegisterVariableSourceType",
            18,
            68,
            "current_texture",
            "TextureRef*",
        ),
        (
            "RegisterVariableSourceType",
            25,
            67,
            "face_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            31,
            66,
            "facequads",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            37,
            66,
            "active_facequads",
            "ObjectFaceQuad*",
        ),
        (
            "RegisterVariableSourceType",
            40,
            66,
            "active_texture",
            "TextureRef*",
        ),
        (
            "RegisterVariableSourceType",
            67,
            68,
            "texture_group_ends",
            "int32_t*",
        ),
    ):
        expected = (
            '        "calc_object_texture_groups",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    for source_type, index, storage, name, type_name in (
        (
            "StackVariableSourceType",
            0,
            -64,
            "world_matrix",
            "TransformMatrix",
        ),
        (
            "StackVariableSourceType",
            233,
            -84,
            "texture_to_bind",
            "TextureRef*",
        ),
        (
            "RegisterVariableSourceType",
            121,
            72,
            "texture_group_index",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            139,
            67,
            "render_pass_filter",
            "uint8_t",
        ),
        (
            "RegisterVariableSourceType",
            160,
            68,
            "opaque_pass_texture",
            "TextureRef*",
        ),
        (
            "RegisterVariableSourceType",
            192,
            68,
            "alpha_pass_texture",
            "TextureRef*",
        ),
        (
            "RegisterVariableSourceType",
            213,
            66,
            "group_texture_to_bind",
            "TextureRef*",
        ),
        (
            "RegisterVariableSourceType",
            356,
            66,
            "blend_gate_texture",
            "TextureRef*",
        ),
        (
            "RegisterVariableSourceType",
            449,
            67,
            "render_buffers",
            "ObjectRenderBuffers*",
        ),
        (
            "RegisterVariableSourceType",
            462,
            67,
            "vertex_buffer",
            "ObjectVertexBuffer*",
        ),
        (
            "RegisterVariableSourceType",
            496,
            68,
            "index_buffer",
            "ObjectIndexBuffer*",
        ),
        (
            "RegisterVariableSourceType",
            509,
            68,
            "index_buffer_resource",
            "ObjectIndexBufferResource*",
        ),
        (
            "RegisterVariableSourceType",
            521,
            68,
            "group_primitive_counts",
            "int32_t*",
        ),
        (
            "RegisterVariableSourceType",
            538,
            68,
            "group_index_starts",
            "int32_t*",
        ),
        (
            "RegisterVariableSourceType",
            566,
            66,
            "group_primitive_counts_for_stats",
            "int32_t*",
        ),
        (
            "RegisterVariableSourceType",
            578,
            67,
            "drawn_primitive_count",
            "int32_t",
        ),
    ):
        expected = (
            '        "render_object",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '"scan_face_byte_offset",\n        "ObjectFaceQuad*"' not in replay
    assert '"insert_face_byte_offset",\n        "ObjectFaceQuad*"' not in replay
    assert '"face_byte_offset",\n        "char*"' not in replay
    assert '"active_texture",\n        "int32_t*"' not in replay
    assert '"texture_group_index",\n        "TextureRef*"' not in replay
    assert '"opaque_pass_texture",\n        "int32_t*"' not in replay
    assert '"alpha_pass_texture",\n        "int32_t*"' not in replay


def test_object_list_lifetime_replay_keeps_array_owners_and_integer_offsets() -> None:
    replay = (BINJA_DIR / "sync_object_list_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for owner_name, expected_size in (
        ("ObjectList", "0x0C"),
        ("Object", "0xDC"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("ObjectList", "0x00", "count", "int32_t"),
        ("ObjectList", "0x04", "capacity", "int32_t"),
        ("ObjectList", "0x08", "objects", "Object*"),
        ("Object", "0x10", "flags", "ObjectFlag"),
        ("Object", "0x2C", "vertex_count", "int32_t"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for function_name, source_type, index, storage, name, type_name in (
        (
            "initialize_object_list",
            "RegisterVariableSourceType",
            35,
            66,
            "allocated_objects",
            "Object*",
        ),
        (
            "initialize_object_list",
            "RegisterVariableSourceType",
            51,
            69,
            "object_byte_offset",
            "int32_t",
        ),
        (
            "initialize_object_list",
            "RegisterVariableSourceType",
            58,
            67,
            "current_object",
            "Object*",
        ),
        (
            "build_all_objects",
            "RegisterVariableSourceType",
            16,
            73,
            "object_byte_offset",
            "int32_t",
        ),
        (
            "build_all_objects",
            "RegisterVariableSourceType",
            47,
            67,
            "current_object",
            "Object*",
        ),
        (
            "build_all_objects",
            "StackVariableSourceType",
            66,
            -16,
            "sort_object_argument",
            "Object*",
        ),
        (
            "build_all_objects",
            "RegisterVariableSourceType",
            88,
            67,
            "toon_object",
            "Object*",
        ),
        (
            "build_all_objects",
            "StackVariableSourceType",
            120,
            -16,
            "buffer_object_argument",
            "Object*",
        ),
        (
            "add_object_to_list",
            "RegisterVariableSourceType",
            37,
            68,
            "append_index_times_55",
            "int32_t",
        ),
        (
            "add_object_to_list",
            "RegisterVariableSourceType",
            43,
            73,
            "new_object",
            "Object*",
        ),
        (
            "add_object_to_list",
            "RegisterVariableSourceType",
            53,
            66,
            "result_object",
            "Object*",
        ),
    ):
        expected = (
            f'        "{function_name}",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '"object_byte_offset",\n        "Object*"' not in replay
    assert '"append_index_times_55",\n        "Object*"' not in replay


def test_object_vertex_storage_replay_keeps_banks_and_byte_offsets_distinct() -> None:
    replay = (BINJA_DIR / "sync_object_vertex_storage_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for owner_name, expected_size in (
        ("Vec3", "0x0C"),
        ("tColour", "0x10"),
        ("Object", "0xDC"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("Vec3", "0x00", "x", "float"),
        ("Vec3", "0x04", "y", "float"),
        ("Vec3", "0x08", "z", "float"),
        ("tColour", "0x00", "r", "float"),
        ("tColour", "0x04", "g", "float"),
        ("tColour", "0x08", "b", "float"),
        ("tColour", "0x0C", "a", "float"),
        ("Object", "0x2C", "vertex_count", "int32_t"),
        ("Object", "0x38", "vertices", "Vec3*"),
        ("Object", "0x3C", "copied_vertices", "Vec3*"),
        ("Object", "0x48", "vertex_colours", "tColour*"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for function_name, source_type, index, storage, name, type_name in (
        (
            "copy_object_vertices",
            "RegisterVariableSourceType",
            12,
            66,
            "vertex_byte_offset",
            "int32_t",
        ),
        (
            "copy_object_vertices",
            "RegisterVariableSourceType",
            19,
            72,
            "source_vertex",
            "Vec3*",
        ),
        (
            "copy_object_vertices",
            "RegisterVariableSourceType",
            24,
            73,
            "copied_vertex",
            "Vec3*",
        ),
        (
            "request_object_vertex_colours",
            "RegisterVariableSourceType",
            15,
            66,
            "allocated_colours",
            "tColour*",
        ),
        (
            "request_object_vertex_colours",
            "RegisterVariableSourceType",
            36,
            66,
            "colour_byte_offset",
            "int32_t",
        ),
        (
            "request_object_vertex_colours",
            "RegisterVariableSourceType",
            43,
            73,
            "red_colour_bank",
            "tColour*",
        ),
    ):
        expected = (
            f'        "{function_name}",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '"vertex_byte_offset",\n        "Vec3*"' not in replay
    assert '"source_vertex_byte_offset",\n        "Vec3*"' not in replay
    assert '"colour_byte_offset",\n        "tColour*"' not in replay


def test_object_vertex_upload_replay_keeps_cursors_and_streams_distinct() -> None:
    replay = (BINJA_DIR / "sync_object_vertex_upload_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for owner_name, expected_size in (
        ("Vec3", "0x0C"),
        ("ObjectRenderVertex", "0x18"),
        ("ObjectRenderBuffers", "0x0C"),
        ("ObjectVertexBuffer", "0x04"),
        ("Object", "0xDC"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    assert '0x0C: ("diffuse", "uint32_t")' in replay

    for function_name, source_type, index, storage, name, type_name in (
        (
            "set_object_color",
            "StackVariableSourceType",
            0,
            -4,
            "locked_vertices",
            "ObjectRenderVertex*",
        ),
        (
            "set_object_color",
            "RegisterVariableSourceType",
            90,
            67,
            "render_vertex_byte_offset",
            "int32_t",
        ),
        (
            "set_object_color",
            "RegisterVariableSourceType",
            92,
            73,
            "locked_vertices_base",
            "ObjectRenderVertex*",
        ),
        (
            "refresh_object_vertex_buffer",
            "RegisterVariableSourceType",
            143,
            68,
            "animated_render_vertex_byte_offset",
            "int32_t",
        ),
        (
            "refresh_object_vertex_buffer",
            "RegisterVariableSourceType",
            145,
            67,
            "animated_source_vertex_byte_offset",
            "int32_t",
        ),
        (
            "refresh_object_vertex_buffer",
            "RegisterVariableSourceType",
            154,
            69,
            "animated_vertices",
            "ObjectRenderVertex*",
        ),
        (
            "refresh_object_vertex_buffer",
            "RegisterVariableSourceType",
            152,
            73,
            "animated_source_vertex",
            "Vec3*",
        ),
        (
            "refresh_object_vertex_buffer",
            "RegisterVariableSourceType",
            158,
            69,
            "animated_vertex",
            "ObjectRenderVertex*",
        ),
        (
            "refresh_object_vertex_buffer",
            "RegisterVariableSourceType",
            271,
            73,
            "dynamic_render_vertex_byte_offset",
            "int32_t",
        ),
        (
            "refresh_object_vertex_buffer",
            "RegisterVariableSourceType",
            273,
            69,
            "dynamic_source_vertex_byte_offset",
            "int32_t",
        ),
        (
            "refresh_object_vertex_buffer",
            "RegisterVariableSourceType",
            282,
            66,
            "dynamic_vertices",
            "ObjectRenderVertex*",
        ),
        (
            "refresh_object_vertex_buffer",
            "RegisterVariableSourceType",
            280,
            68,
            "dynamic_source_vertex",
            "Vec3*",
        ),
        (
            "refresh_object_vertex_buffer",
            "RegisterVariableSourceType",
            286,
            66,
            "dynamic_vertex",
            "ObjectRenderVertex*",
        ),
    ):
        expected = (
            f'        "{function_name}",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '"render_vertex_byte_offset",\n        "ObjectRenderVertex*"' not in replay
    assert '"animated_source_vertex_byte_offset",\n        "Vec3*"' not in replay
    assert '"dynamic_source_vertex_byte_offset",\n        "Vec3*"' not in replay
    assert '"animated_render_vertex_byte_offset",\n        "ObjectRenderVertex*"' not in replay
    assert '"dynamic_render_vertex_byte_offset",\n        "ObjectRenderVertex*"' not in replay


def test_track_cache_teardown_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_track_cache_teardown_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("BodNode", "0x10"),
        ("BodList", "0x0C"),
        ("BodBase", "0x38"),
        ("TrackRenderCacheSlot", "0x3C"),
        ("SegmentCache", "0xA7F8"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("BodNode", "0x04", "list_flags", "uint32_t"),
        ("BodNode", "0x08", "list_prev", "BodNode*"),
        ("BodNode", "0x0C", "list_next", "BodNode*"),
        ("BodList", "0x04", "first", "BodNode*"),
        ("BodList", "0x08", "free_top", "BodNode*"),
        ("TrackRenderCacheSlot", "0x00", "bod", "BodBase"),
        ("SegmentCache", "0x58", "slots", "TrackRenderCacheSlot[143][5]"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        (
            "RegisterVariableSourceType",
            5,
            72,
            "next_ref",
            "BodNode**",
        ),
        (
            "StackVariableSourceType",
            8,
            -4,
            "rows_remaining",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            34,
            73,
            "families_remaining",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            41,
            67,
            "active_list",
            "BodList*",
        ),
        (
            "RegisterVariableSourceType",
            47,
            66,
            "list_flags",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            88,
            66,
            "list_next",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            100,
            66,
            "list_prev",
            "BodNode*",
        ),
    ):
        expected = (
            '        "remove_track_render_cache_bods",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert "TrackRenderCacheSlotCursor" not in replay


def test_track_fringe_builder_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_track_fringe_builder_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("SubRow", "0xF4"),
        ("TrackRowCell", "0x54"),
        ("Fringe", "0x38"),
        ("FringeManager", "0x5FB44"),
        ("RootTrackFringeBodCatalog", "0x3F00"),
        ("RootBodCatalog", "0x4D00"),
        ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("TrackRowCell", "0x44", "fringe_front", "Fringe*"),
        ("TrackRowCell", "0x48", "fringe_right", "Fringe*"),
        ("TrackRowCell", "0x4C", "fringe_left", "Fringe*"),
        ("TrackRowCell", "0x50", "fringe_back", "Fringe*"),
        ("Fringe", "0x00", "bod", "BodBase"),
        ("FringeManager", "0x00", "objects", "Fringe[7000]"),
        ("FringeManager", "0x5FB40", "count", "int32_t"),
        (
            "RootTrackFringeBodCatalog",
            "0x00",
            "entries",
            "RootBodCatalogEntry[8][4][3][3]",
        ),
        (
            "RootBodCatalog",
            "0xCB0",
            "fringe_catalog",
            "RootTrackFringeBodCatalog",
        ),
        (
            "SubgameRuntime",
            "0x35BBBC",
            "fringe_manager",
            "FringeManager",
        ),
        (
            "SubgameRuntime",
            "0x3BFAC8",
            "runtime_cells",
            "TrackRowCell[3200][8]",
        ),
        (
            "SubgameRuntime",
            "0x5CCAC8",
            "runtime_rows",
            "SubRow[3200]",
        ),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        ("RegisterVariableSourceType", 10, 71, "runtime", "SubgameRuntime*"),
        (
            "StackVariableSourceType",
            18,
            -80,
            "runtime_saved",
            "SubgameRuntime*",
        ),
        ("RegisterVariableSourceType", 30, 69, "edge_variant_a", "int32_t"),
        ("StackVariableSourceType", 34, -72, "row_index", "int32_t"),
        ("RegisterVariableSourceType", 44, 68, "row", "SubRow*"),
        ("RegisterVariableSourceType", 52, 72, "cell", "TrackRowCell*"),
        ("StackVariableSourceType", 58, -68, "row_cursor", "SubRow*"),
        (
            "StackVariableSourceType",
            70,
            -76,
            "cells_remaining",
            "int32_t",
        ),
        ("RegisterVariableSourceType", 73, 73, "fringe_family", "int32_t"),
        (
            "RegisterVariableSourceType",
            316,
            71,
            "front_edge_variant_b",
            "int32_t",
        ),
        ("RegisterVariableSourceType", 355, 66, "front_fringe", "Fringe*"),
        ("StackVariableSourceType", 0, -64, "front_color", "tColour"),
        (
            "RegisterVariableSourceType",
            576,
            71,
            "right_edge_variant_b",
            "int32_t",
        ),
        ("RegisterVariableSourceType", 615, 66, "right_fringe", "Fringe*"),
        ("StackVariableSourceType", 0, -48, "right_color", "tColour"),
        (
            "RegisterVariableSourceType",
            836,
            71,
            "left_edge_variant_b",
            "int32_t",
        ),
        ("RegisterVariableSourceType", 875, 66, "left_fringe", "Fringe*"),
        ("StackVariableSourceType", 0, -32, "left_color", "tColour"),
        (
            "RegisterVariableSourceType",
            1096,
            71,
            "back_edge_variant_b",
            "int32_t",
        ),
        ("RegisterVariableSourceType", 1135, 66, "back_fringe", "Fringe*"),
        ("StackVariableSourceType", 0, -16, "back_color", "tColour"),
    ):
        expected = (
            '        "build_track_fringe_objects",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert "FringeObject" not in replay


def test_subgame_bulk_teardown_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_subgame_bulk_teardown_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("BodNode", "0x10"),
        ("BodList", "0x0C"),
        ("RenderableBod", "0x80"),
        ("RowModel", "0x8C"),
        ("SubRow", "0xF4"),
        ("TrackRowCell", "0x54"),
        ("SubHealth", "0x74"),
        ("SubGarbage", "0xC4"),
        ("SubGarbagePool", "0x264C"),
        ("Slug", "0xEC"),
        ("SlugPool", "0x760"),
        ("SubRing", "0x1F8"),
        ("SubRingPool", "0x3F0"),
        ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("BodNode", "0x04", "list_flags", "uint32_t"),
        ("BodNode", "0x08", "list_prev", "BodNode*"),
        ("BodNode", "0x0C", "list_next", "BodNode*"),
        ("BodList", "0x04", "first", "BodNode*"),
        ("BodList", "0x08", "free_top", "BodNode*"),
        ("RowModel", "0x00", "body", "RenderableBod"),
        ("SubRow", "0x04", "row_model", "RowModel"),
        ("TrackRowCell", "0x00", "bod", "BodNode"),
        ("SubHealth", "0x38", "state", "TrackPickupState"),
        ("SubGarbagePool", "0x04", "slots", "SubGarbage[50]"),
        ("SlugPool", "0x00", "slots", "Slug[8]"),
        ("SubRingPool", "0x00", "slots", "SubRing[2]"),
        (
            "SubgameRuntime",
            "0x356000",
            "health_pickups",
            "SubHealth[8]",
        ),
        ("SubgameRuntime", "0x3563A0", "slug_hazards", "SlugPool"),
        (
            "SubgameRuntime",
            "0x359140",
            "garbage_hazards",
            "SubGarbagePool",
        ),
        ("SubgameRuntime", "0x35B78C", "ring_effects", "SubRingPool"),
        (
            "SubgameRuntime",
            "0x3BFAC8",
            "runtime_cells",
            "TrackRowCell[3200][8]",
        ),
        (
            "SubgameRuntime",
            "0x5CCAC8",
            "runtime_rows",
            "SubRow[3200]",
        ),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        ("RegisterVariableSourceType", 21, 71, "rows_remaining", "int32_t"),
        ("RegisterVariableSourceType", 39, 67, "row_active_list", "BodList*"),
        ("RegisterVariableSourceType", 45, 66, "row_list_flags", "uint32_t"),
        ("RegisterVariableSourceType", 87, 66, "row_list_next", "BodNode*"),
        ("RegisterVariableSourceType", 99, 66, "row_list_prev", "BodNode*"),
        ("RegisterVariableSourceType", 118, 68, "row_free_top", "BodNode*"),
        (
            "RegisterVariableSourceType",
            129,
            66,
            "row_flags_after_clear",
            "uint32_t",
        ),
        ("RegisterVariableSourceType", 138, 69, "cells_remaining", "int32_t"),
        (
            "RegisterVariableSourceType",
            187,
            73,
            "health_remaining",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            194,
            66,
            "health_list_flags",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            208,
            67,
            "health_active_list",
            "BodList*",
        ),
        (
            "RegisterVariableSourceType",
            253,
            66,
            "health_list_next",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            265,
            66,
            "health_list_prev",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            284,
            68,
            "health_free_top",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            295,
            66,
            "health_flags_after_clear",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            582,
            73,
            "garbage_remaining",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            604,
            66,
            "garbage_list_flags",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            610,
            67,
            "garbage_active_list",
            "BodList*",
        ),
        (
            "RegisterVariableSourceType",
            652,
            66,
            "garbage_list_next",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            664,
            66,
            "garbage_list_prev",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            683,
            68,
            "garbage_free_top",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            694,
            66,
            "garbage_flags_after_clear",
            "uint32_t",
        ),
        ("RegisterVariableSourceType", 718, 73, "slug_remaining", "int32_t"),
        ("RegisterVariableSourceType", 740, 66, "slug_list_flags", "uint32_t"),
        ("RegisterVariableSourceType", 743, 67, "slug_active_list", "BodList*"),
        ("RegisterVariableSourceType", 788, 66, "slug_list_next", "BodNode*"),
        ("RegisterVariableSourceType", 800, 66, "slug_list_prev", "BodNode*"),
        ("RegisterVariableSourceType", 819, 68, "slug_free_top", "BodNode*"),
        (
            "RegisterVariableSourceType",
            830,
            66,
            "slug_flags_after_clear",
            "uint32_t",
        ),
        ("RegisterVariableSourceType", 854, 73, "ring_remaining", "int32_t"),
        ("RegisterVariableSourceType", 870, 66, "ring_list_flags", "uint32_t"),
        ("RegisterVariableSourceType", 873, 67, "ring_active_list", "BodList*"),
        ("RegisterVariableSourceType", 918, 66, "ring_list_next", "BodNode*"),
        ("RegisterVariableSourceType", 930, 66, "ring_list_prev", "BodNode*"),
        ("RegisterVariableSourceType", 949, 68, "ring_free_top", "BodNode*"),
        (
            "RegisterVariableSourceType",
            960,
            66,
            "ring_flags_after_clear",
            "uint32_t",
        ),
    ):
        expected = (
            '        "remove_subgame_bods",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert "linked_flags_gate" not in replay


def test_subgame_pickup_teardown_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_subgame_pickup_teardown_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("BodNode", "0x10"),
        ("BodList", "0x0C"),
        ("BodBase", "0x38"),
        ("RenderableBod", "0x80"),
        ("SubSpeedUp", "0xB4"),
        ("JetPack", "0x19C"),
        ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("BodNode", "0x04", "list_flags", "uint32_t"),
        ("BodNode", "0x08", "list_prev", "BodNode*"),
        ("BodNode", "0x0C", "list_next", "BodNode*"),
        ("BodList", "0x04", "first", "BodNode*"),
        ("BodList", "0x08", "free_top", "BodNode*"),
        ("BodBase", "0x00", "bod", "BodNode"),
        ("RenderableBod", "0x00", "bod", "BodBase"),
        ("SubSpeedUp", "0x00", "body", "RenderableBod"),
        ("SubSpeedUp", "0x80", "state", "TrackPickupState"),
        ("JetPack", "0x00", "bod", "BodBase"),
        ("JetPack", "0x38", "state", "TrackPickupState"),
        (
            "SubgameRuntime",
            "0x355DB0",
            "speedup_pickup",
            "SubSpeedUp",
        ),
        ("SubgameRuntime", "0x355E64", "jetpack_pickup", "JetPack"),
        ("GameRoot", "0x05A8", "active_bod_list", "BodList"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        (
            "RegisterVariableSourceType",
            336,
            68,
            "speedup_active_list",
            "BodList*",
        ),
        (
            "RegisterVariableSourceType",
            342,
            67,
            "speedup_list_flags",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            385,
            67,
            "speedup_list_next",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            392,
            72,
            "speedup_list_prev_for_next",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            398,
            67,
            "speedup_list_prev",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            428,
            67,
            "speedup_flags_after_clear",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            460,
            67,
            "jetpack_list_flags",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            472,
            68,
            "jetpack_active_list",
            "BodList*",
        ),
        (
            "RegisterVariableSourceType",
            518,
            67,
            "jetpack_list_next",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            525,
            72,
            "jetpack_list_prev_for_next",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            531,
            67,
            "jetpack_list_prev",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            561,
            67,
            "jetpack_flags_after_clear",
            "uint32_t",
        ),
    ):
        expected = (
            '        "remove_subgame_bods",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay


def test_subgame_player_teardown_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_subgame_player_teardown_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("BodNode", "0x10"),
        ("BodList", "0x0C"),
        ("BodBase", "0x38"),
        ("RenderableBod", "0x80"),
        ("Weapon", "0x3DC"),
        ("Snail", "0x19B4"),
        ("Player", "0x4364"),
        ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("BodNode", "0x04", "list_flags", "uint32_t"),
        ("BodNode", "0x08", "list_prev", "BodNode*"),
        ("BodNode", "0x0C", "list_next", "BodNode*"),
        ("BodList", "0x04", "first", "BodNode*"),
        ("BodList", "0x08", "free_top", "BodNode*"),
        ("BodBase", "0x00", "bod", "BodNode"),
        ("RenderableBod", "0x00", "bod", "BodBase"),
        ("Weapon", "0x00", "body", "RenderableBod"),
        ("Snail", "0x00", "body", "RenderableBod"),
        ("Snail", "0x064C", "weapon_channels", "Weapon[3]"),
        ("Snail", "0x11E0", "jetpack_channel", "Weapon"),
        ("Player", "0x0000", "body", "RenderableBod"),
        ("Player", "0x2984", "presentation", "Snail"),
        ("SubgameRuntime", "0x3BB764", "player", "Player"),
        ("GameRoot", "0x05A8", "active_bod_list", "BodList"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        ("RegisterVariableSourceType", 1002, 66, "player_list_flags", "uint32_t"),
        ("RegisterVariableSourceType", 1014, 67, "player_active_list", "BodList*"),
        ("RegisterVariableSourceType", 1059, 66, "player_list_next", "BodNode*"),
        ("RegisterVariableSourceType", 1072, 66, "player_list_prev", "BodNode*"),
        ("RegisterVariableSourceType", 1093, 68, "player_free_top", "BodNode*"),
        (
            "RegisterVariableSourceType",
            1102,
            66,
            "player_flags_after_clear",
            "uint32_t",
        ),
        ("RegisterVariableSourceType", 1123, 68, "snail_active_list", "BodList*"),
        ("RegisterVariableSourceType", 1129, 67, "snail_list_flags", "uint32_t"),
        ("RegisterVariableSourceType", 1172, 67, "snail_list_next", "BodNode*"),
        (
            "RegisterVariableSourceType",
            1179,
            73,
            "snail_list_prev_for_next",
            "BodNode*",
        ),
        ("RegisterVariableSourceType", 1185, 67, "snail_list_prev", "BodNode*"),
        (
            "RegisterVariableSourceType",
            1215,
            67,
            "snail_flags_after_clear",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            1230,
            67,
            "jetpack_channel_list_flags",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            1242,
            68,
            "jetpack_channel_active_list",
            "BodList*",
        ),
        (
            "RegisterVariableSourceType",
            1288,
            67,
            "jetpack_channel_list_next",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            1295,
            73,
            "jetpack_channel_list_prev_for_next",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            1301,
            67,
            "jetpack_channel_list_prev",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            1331,
            67,
            "jetpack_channel_flags_after_clear",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            1346,
            67,
            "weapon_channel_0_list_flags",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            1358,
            68,
            "weapon_channel_0_active_list",
            "BodList*",
        ),
        (
            "RegisterVariableSourceType",
            1404,
            67,
            "weapon_channel_0_list_next",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            1411,
            73,
            "weapon_channel_0_list_prev_for_next",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            1417,
            67,
            "weapon_channel_0_list_prev",
            "BodNode*",
        ),
        (
            "RegisterVariableSourceType",
            1447,
            67,
            "weapon_channel_0_flags_after_clear",
            "uint32_t",
        ),
    ):
        expected = (
            '        "remove_subgame_bods",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay


def test_runtime_grid_builder_lifetime_replay_stays_guarded() -> None:
    replay = (BINJA_DIR / "sync_runtime_grid_clear_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for owner_name, expected_size in (
        ("BodNode", "0x10"),
        ("Vec3", "0x0C"),
        ("tColour", "0x10"),
        ("Fringe", "0x38"),
        ("SubSegment", "0x4220"),
            ("SubTracks", "0x1A5978"),
            ("TrackRowCell", "0x54"),
            ("TrackRowCellLaneAndFlagsStrideCursor", "0x54"),
            ("TrackRowCellFringeFrontStrideCursor", "0x54"),
            ("SubRow", "0xF4"),
            ("SubRowParcelSpawnYStrideCursor", "0xF4"),
            ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("SubSegment", "0x04", "row_count", "int32_t"),
        ("SubTracks", "0x04", "segment_slots", "SubSegment[100]"),
        ("TrackRowCell", "0x28", "color", "tColour"),
        ("TrackRowCell", "0x3D", "open_edge_mask", "uint8_t"),
            ("TrackRowCell", "0x40", "lane_and_flags", "uint32_t"),
            ("TrackRowCell", "0x44", "fringe_front", "Fringe*"),
            (
                "TrackRowCellLaneAndFlagsStrideCursor",
                "0x00",
                "lane_and_flags",
                "uint32_t",
            ),
            (
                "TrackRowCellLaneAndFlagsStrideCursor",
                "0x04",
                "fringe_front",
                "Fringe*",
            ),
            (
                "TrackRowCellFringeFrontStrideCursor",
                "0x00",
                "fringe_front",
                "Fringe*",
            ),
            ("SubRow", "0x90", "parcel_spawn_position", "Vec3"),
            ("SubRow", "0xA4", "primary_attachment_cell", "TrackRowCell*"),
            ("SubRow", "0xEC", "source_segment", "SubSegment*"),
            (
                "SubRowParcelSpawnYStrideCursor",
                "0x00",
                "parcel_spawn_y",
                "float",
            ),
            (
                "SubRowParcelSpawnYStrideCursor",
                "0x1C",
                "attachment_body",
                "BodBase",
            ),
            (
                "SubRowParcelSpawnYStrideCursor",
                "0x58",
                "source_segment",
                "SubSegment*",
            ),
        ("SubgameRuntime", "0xA874", "level_definition", "SubTracks"),
        (
            "SubgameRuntime",
            "0x3BFAC8",
            "runtime_cells",
            "TrackRowCell[3200][8]",
        ),
        (
            "SubgameRuntime",
            "0x5CCAC8",
            "runtime_rows",
            "SubRow[3200]",
        ),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, type_name in (
        ("RegisterVariableSourceType", 435, 66, "segment_slot_index", "int32_t"),
        (
            "RegisterVariableSourceType",
            450,
            67,
            "segment_row_count_cursor",
            "int32_t*",
        ),
        (
            "RegisterVariableSourceType",
            456,
            68,
            "segment_row_count",
            "int32_t",
        ),
        (
            "StackVariableSourceType",
                569,
                -40,
                "row_fringe_front_cursor",
                "TrackRowCellFringeFrontStrideCursor*",
        ),
        (
            "RegisterVariableSourceType",
                573,
                73,
                "parcel_spawn_y_cursor",
                "SubRowParcelSpawnYStrideCursor*",
        ),
        ("StackVariableSourceType", 579, -48, "rows_remaining", "int32_t"),
        (
            "RegisterVariableSourceType",
            636,
            71,
            "cell_lanes_remaining",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
                633,
                72,
                "lane_and_flags_cursor",
                "TrackRowCellLaneAndFlagsStrideCursor*",
        ),
        (
            "RegisterVariableSourceType",
            638,
            67,
            "cell_lane_and_flags",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            669,
            68,
            "cell_list_flags",
            "uint32_t",
        ),
        (
            "RegisterVariableSourceType",
            689,
            66,
            "next_row_fringe_front_cursor",
            "TrackRowCellFringeFrontStrideCursor*",
        ),
        (
            "RegisterVariableSourceType",
            698,
            72,
            "cell_fringe_front_cursor",
            "TrackRowCellFringeFrontStrideCursor*",
        ),
        (
            "StackVariableSourceType",
            0,
            -28,
            "authored_random_length",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            1948,
            72,
            "runtime_grid_owner",
            "SubgameRuntime*",
        ),
        (
            "RegisterVariableSourceType",
            2110,
            71,
            "authored_glyph_cursor",
            "char*",
        ),
        (
            "RegisterVariableSourceType",
            2114,
            68,
            "authored_glyph",
            "char",
        ),
        (
            "RegisterVariableSourceType",
            2118,
            66,
            "normalized_glyph",
            "char",
        ),
        (
            "RegisterVariableSourceType",
            4180,
            66,
            "tile_id",
            "SubLocTileId",
        ),
        ("StackVariableSourceType", 4256, -40, "cell_anchor_z", "float"),
        (
            "RegisterVariableSourceType",
            4562,
            71,
            "uv_lane",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            4573,
            67,
            "uv_row_index",
            "int32_t",
        ),
    ):
        expected = (
            '        "populate_runtime_track_cells_from_segments",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_split_user_var_update" in replay
    assert "apply_split_away_user_var_update" in replay
    assert "apply_user_var_updates" in replay
    for address, index, storage in (
        ("0x436657", 1959, 68),
        ("0x436664", 1972, 68),
        ("0x43666a", 1978, 68),
        ("0x436660", 1968, 71),
        ("0x436668", 1976, 71),
        ("0x43666a", 1978, 71),
        ("0x4366b6", 2054, -28),
        ("0x4366bf", 2063, -28),
        ("0x4366c4", 2068, -28),
        ("0x4366f2", 2114, 68),
    ):
        assert f'("{address}",' in replay
        assert f"{index}, {storage})" in replay
    assert '"runtime_lane"' in replay
    assert '"authored_lane"' in replay
    assert '"edge_row"' in replay
    assert '"glyph_segment"' in replay
    assert "remaining_cell_lanes" not in replay


def test_runtime_grid_clear_field_cursors_are_borrowed_and_fail_closed() -> None:
    repo_root = Path(__file__).parents[1]
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (
        repo_root / "tools/match/include/track_attachment_types.h"
    ).read_text(encoding="utf-8")
    canonical_binja = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    canonical_ida = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    health_checks = {
        check["name"]: check
        for check in json.loads(
            (repo_root / "analysis/decompile/health_checks.json").read_text(
                encoding="utf-8"
            )
        )["checks"]
    }

    for type_name, stride_tail, stride in (
        ("TrackRowCellLaneAndFlagsStrideCursor", "0x40", "0x54"),
        ("TrackRowCellFringeFrontStrideCursor", "0x44", "0x54"),
        ("SubRowParcelSpawnYStrideCursor", "0x94", "0xF4"),
    ):
        assert f"typedef struct {type_name} {{" in analysis_header
        assert f"uint8_t _stride_tail[{stride_tail}];" in analysis_header
        assert "sole owner" in analysis_header
        assert type_name not in matcher_header
        assert f'"{type_name}": {stride}' in canonical_binja

    for marker in (
        "uint32_t lane_and_flags;",
        "Fringe* fringe_front;",
        "float parcel_spawn_y;",
        "BodBase attachment_body;",
        "SubSegment* source_segment;",
    ):
        assert marker in analysis_header

    assert "POPULATE_RUNTIME_CLEAR_CURSOR_USER_VAR_UPDATES" in canonical_binja
    for source_type, index, storage, name, type_name in (
        (
            "StackVariableSourceType",
            569,
            -40,
            "row_fringe_front_cursor",
            "TrackRowCellFringeFrontStrideCursor*",
        ),
        (
            "RegisterVariableSourceType",
            573,
            73,
            "parcel_spawn_y_cursor",
            "SubRowParcelSpawnYStrideCursor*",
        ),
        (
            "RegisterVariableSourceType",
            633,
            72,
            "lane_and_flags_cursor",
            "TrackRowCellLaneAndFlagsStrideCursor*",
        ),
        (
            "RegisterVariableSourceType",
            689,
            66,
            "next_row_fringe_front_cursor",
            "TrackRowCellFringeFrontStrideCursor*",
        ),
        (
            "RegisterVariableSourceType",
            698,
            72,
            "cell_fringe_front_cursor",
            "TrackRowCellFringeFrontStrideCursor*",
        ),
    ):
        expected = (
            '        "populate_runtime_track_cells_from_segments",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in canonical_binja

    assert "RUNTIME_GRID_CLEAR_CURSOR_HEADER_MARKERS" in canonical_ida
    for name, declaration, definition_address in (
        (
            "row_fringe_front_cursor",
            "TrackRowCellFringeFrontStrideCursor *row_fringe_front_cursor;",
            "0x4360EA",
        ),
        (
            "parcel_spawn_y_cursor",
            "SubRowParcelSpawnYStrideCursor *parcel_spawn_y_cursor;",
            "0x4360EE",
        ),
        (
            "lane_and_flags_cursor",
            "TrackRowCellLaneAndFlagsStrideCursor *lane_and_flags_cursor;",
            "0x43612A",
        ),
        (
            "next_row_fringe_front_cursor",
            "TrackRowCellFringeFrontStrideCursor *next_row_fringe_front_cursor;",
            "0x436162",
        ),
        (
            "cell_fringe_front_cursor",
            "TrackRowCellFringeFrontStrideCursor *cell_fringe_front_cursor;",
            "0x43616B",
        ),
    ):
        assert f'"{name}"' in canonical_ida
        assert f'"{declaration}"' in canonical_ida
        assert definition_address in canonical_ida

    bn_health = health_checks["bn_runtime_grid_clear_owner_graph"]
    for marker in (
        "struct TrackRowCellFringeFrontStrideCursor* row_fringe_front_cursor",
        "struct SubRowParcelSpawnYStrideCursor* parcel_spawn_y_cursor",
        "struct TrackRowCellLaneAndFlagsStrideCursor* lane_and_flags_cursor",
        "lane_and_flags_cursor = &lane_and_flags_cursor[1]",
        "cell_fringe_front_cursor->fringe_front = 0",
        "parcel_spawn_y_cursor = &parcel_spawn_y_cursor[1]",
    ):
        assert any(marker in required for required in bn_health["required_substrings"])
    for old_shape in (
        "struct Fringe** row_fringe_front_cursor",
        "int32_t* parcel_spawn_y_cursor",
        "uint32_t* lane_and_flags_cursor",
        "lane_and_flags_cursor = &lane_and_flags_cursor[0x15]",
        "parcel_spawn_y_cursor = &parcel_spawn_y_cursor[0x3d]",
    ):
        assert old_shape in bn_health["forbidden_substrings"]

    ida_health = health_checks["ida_runtime_cell_stride_owner_graph"]
    for marker in (
        "TrackRowCellFringeFrontStrideCursor *row_fringe_front_cursor;",
        "SubRowParcelSpawnYStrideCursor *parcel_spawn_y_cursor;",
        "TrackRowCellLaneAndFlagsStrideCursor *lane_and_flags_cursor;",
        "cell_fringe_front_cursor->fringe_front = nullptr",
        "++parcel_spawn_y_cursor",
    ):
        assert any(marker in required for required in ida_health["required_substrings"])
    for old_shape in (
        "Fringe **row_fringe_front_cursor;",
        "int32_t *parcel_spawn_y_cursor;",
        "uint32_t *lane_and_flags_cursor;",
        "lane_and_flags_cursor += 21",
        "parcel_spawn_y_cursor += 61",
    ):
        assert old_shape in ida_health["forbidden_substrings"]


def test_subgame_level_activation_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_subgame_level_activation_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("BodNode", "0x10"),
        ("BodList", "0x0C"),
        ("BodBase", "0x38"),
        ("RenderableBod", "0x80"),
        ("Weapon", "0x3DC"),
        ("Invincible", "0x98"),
        ("Snail", "0x19B4"),
        ("Player", "0x4364"),
        ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("BodNode", "0x08", "list_prev", "BodNode*"),
        ("BodNode", "0x0C", "list_next", "BodNode*"),
        ("BodList", "0x04", "first", "BodNode*"),
        ("BodBase", "0x00", "bod", "BodNode"),
        ("RenderableBod", "0x00", "bod", "BodBase"),
        ("Weapon", "0x00", "body", "RenderableBod"),
        ("Invincible", "0x00", "body", "RenderableBod"),
        ("Snail", "0x064C", "weapon_channels", "Weapon[3]"),
        ("Snail", "0x11E0", "jetpack_channel", "Weapon"),
        ("Snail", "0x1894", "invincible_shell", "Invincible"),
        ("Player", "0x0000", "body", "RenderableBod"),
        ("Player", "0x2984", "presentation", "Snail"),
        ("SubgameRuntime", "0x3BB764", "player", "Player"),
        ("GameRoot", "0x05A8", "active_bod_list", "BodList"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for index, storage, name in (
        (1402, 68, "active_first_weapon_0"),
        (1423, 68, "active_first_link_weapon_0"),
        (1438, 68, "active_new_first_weapon_0"),
        (1490, 68, "active_first_weapon_1"),
        (1511, 68, "active_first_link_weapon_1"),
        (1526, 68, "active_new_first_weapon_1"),
        (1578, 68, "active_first_weapon_2"),
        (1599, 68, "active_first_link_weapon_2"),
        (1614, 68, "active_new_first_weapon_2"),
        (1666, 68, "active_first_invincible_shell"),
        (1687, 68, "active_first_link_invincible_shell"),
        (1702, 68, "active_new_first_invincible_shell"),
        (1769, 68, "active_first_presentation"),
        (1790, 68, "active_first_link_presentation"),
        (1805, 68, "active_new_first_presentation"),
        (1846, 67, "active_first_player"),
        (1867, 67, "active_first_link_player"),
        (1875, 67, "active_first_reload_player"),
        (1877, 67, "active_new_first_player_reloaded"),
    ):
        expected = (
            '        "build_subgame_level",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            '        "BodNode*"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    for hidden_ssa_name in ("edx_13", "edx_15", "ebp_1"):
        assert hidden_ssa_name not in replay


def test_update_subgame_frontend_root_split_stays_guarded() -> None:
    repo_root = Path(__file__).parents[1]
    replay = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )

    assert "UPDATE_SUBGAME_FRONTEND_ROOT_SPLIT_DEFINITIONS" in replay
    assert (
        '("0x4399b8", "mlil", "RegisterVariableSourceType", 3624, 66)'
        in replay
    )
    assert "UPDATE_SUBGAME_FRONTEND_ROOT_TARGET_VAR" in replay
    assert replay.count(
        "definitions=UPDATE_SUBGAME_FRONTEND_ROOT_SPLIT_DEFINITIONS"
    ) == 2
    assert replay.count(
        "target_var=UPDATE_SUBGAME_FRONTEND_ROOT_TARGET_VAR"
    ) == 2
    assert 'variable_name="frontend_game_base"' in replay
    assert 'variable_type="GameRoot*"' in replay

    health = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    bn_check = checks["bn_update_subgame_owner_graph"]
    ida_check = checks["ida_update_subgame_owner_graph"]
    assert (
        "g_game_base->players[0].frontend_state = 0x1b"
        in bn_check["required_substrings"]
    )
    assert "*(g_game_base + 0x1b8)" in bn_check["forbidden_substrings"]
    assert (
        "g_game_base->players[0].frontend_state = 27;"
        in ida_check["required_substrings"]
    )
    assert "(char *)g_game_base + 440" in ida_check["forbidden_substrings"]


def test_update_subgame_fringe_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_update_subgame_fringe_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("BodNode", "0x10"),
        ("BodBase", "0x38"),
        ("Fringe", "0x38"),
        ("tColour", "0x10"),
        ("TrackRowCell", "0x54"),
        ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("BodNode", "0x08", "list_prev", "BodNode*"),
        ("BodNode", "0x0C", "list_next", "BodNode*"),
        ("BodBase", "0x00", "bod", "BodNode"),
        ("BodBase", "0x28", "color", "tColour"),
        ("Fringe", "0x00", "bod", "BodBase"),
        ("tColour", "0x00", "r", "float"),
        ("tColour", "0x0C", "a", "float"),
        ("TrackRowCell", "0x44", "fringe_front", "Fringe*"),
        ("TrackRowCell", "0x50", "fringe_back", "Fringe*"),
        (
            "SubgameRuntime",
            "0x355B64",
            "fringe_attachment_list_head",
            "BodBase",
        ),
        (
            "SubgameRuntime",
            "0x3BFAC8",
            "runtime_cells",
            "TrackRowCell[3200][8]",
        ),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for source_type, index, storage, name, variable_type in (
        ("StackVariableSourceType", 1730, -56, "fringe_slots_remaining", "uint32_t"),
        ("RegisterVariableSourceType", 1738, 69, "fringe_slot_cursor", "Fringe**"),
        ("RegisterVariableSourceType", 1738, 66, "current_fringe", "Fringe*"),
        ("RegisterVariableSourceType", 1785, 67, "fringe_list_next", "BodNode*"),
        ("RegisterVariableSourceType", 1795, 67, "fringe_list_flags", "uint32_t"),
        ("RegisterVariableSourceType", 1821, 66, "skirt_color", "tColour*"),
        ("RegisterVariableSourceType", 1826, 68, "reloaded_fringe", "Fringe*"),
        ("RegisterVariableSourceType", 1830, 68, "fringe_color", "tColour*"),
    ):
        expected = (
            '        "update_subgame",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay


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
    assert "DEFERRED_PROTO_UPDATES" not in track_sync
    assert "report_deferred_prototypes" not in track_sync
    direct_track_prototypes = track_sync.split("\nPROTO_UPDATES = (", 1)[1].split(
        "\n)\n\n\ndef parse_args", 1
    )[0]
    assert "initialize_track_render_cache_manager" in direct_track_prototypes
    assert "build_track_render_caches" in direct_track_prototypes
    assert expected[0] + ";" in ida_path_sync
    assert expected[1] + ";" in ida_path_sync
    assert '"TrackRenderCacheSlot": 0x3C' in ida_path_sync
    assert '"SegmentCache": 0xA7F8' in ida_path_sync
    assert "TRACK_RENDER_CACHE_OWNER_MARKERS" in ida_path_sync
    assert "TRACK_RENDER_CACHE_OWNER_SIZES" in ida_path_sync
    assert "track_render_cache_owner_sizes" in ida_path_sync
    for address in (
        "0x433060",
        "0x433220",
        "0x433830",
        "0x433960",
        "0x433B30",
        "0x433F20",
    ):
        assert address in ida_path_sync
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
    assert '"kill_border"' in frame_sync
    assert "void __thiscall kill_border" in frame_sync
    assert 'f"{border_manager_type}* manager, FrontendWidget* widget)"' in frame_sync
    assert "void __thiscall kill_border" in ida_frame_sync
    assert "BorderManager *manager, FrontendWidget *widget" in ida_frame_sync
    assert "BORDER_KILL_REANALYSIS_FUNCTIONS" in frame_sync
    assert "BORDER_KILL_REANALYSIS_FUNCTIONS" in ida_frame_sync
    assert '"set_border_justify_centre"' in frame_sync
    assert "void __thiscall set_border_justify_centre" in frame_sync
    assert "float justify_centre" in frame_sync
    assert "void __thiscall set_border_justify_centre" in ida_frame_sync
    assert "float justify_centre" in ida_frame_sync
    for function_name in (
        "border_add_text_number",
        "allocate_border",
        "activate_all_borders",
        "hide_all_borders",
        "unhide_all_borders",
        "apply_all_border_visibility_mode",
        "queue_frontend_widget_flag_after_delay",
        "update_border_manager",
        "initialize_border_record",
    ):
        assert f'"{function_name}"' in frame_sync
        assert f'"{function_name}"' in ida_frame_sync
    assert "FrontendWidget* widget" in frame_sync
    assert "BorderManager *manager, FrontendWidget *widget" in ida_frame_sync
    assert "BorderRecord* record" in frame_sync
    assert "BorderRecord *record" in ida_frame_sync
    for prototype in (
        "void __thiscall initialize_help_screen(Help* help)",
        "void __thiscall destroy_help_screen(Help* help)",
        "void __thiscall update_help_screen(Help* help)",
    ):
        assert prototype in runtime_sync
        assert prototype + ";" in ida_path_sync
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
    assert "types_declare_if_changed" in loading_sync
    assert '"LoadingVertex": 0x14' in loading_sync
    assert '"LoadingQuadVertexView": 0x50' in loading_sync
    assert '"ObjectRenderBuffers": 0x0C' in loading_sync
    assert '"Direct3DTexture8Vtbl": 0x0C' in loading_sync
    assert '("0x503280", "g_loading_bar_on_texture")' in loading_sync
    assert '("0x503284", "g_loading_background_vertex_buffer")' in loading_sync
    assert '("0x503288", "g_loading_background_texture")' in loading_sync
    assert '("0x503290", "g_loading_bar")' in loading_sync
    assert '("0x5032a4", "g_loading_bar_vertex_buffer")' in loading_sync
    assert '("0x503280", "Direct3DTexture8*")' in loading_sync
    assert '("0x503284", "ObjectRenderBuffers*")' in loading_sync
    assert '("0x503288", "Direct3DTexture8*")' in loading_sync
    assert '("0x503290", "LoadingBar")' in loading_sync
    assert '("0x5032a4", "ObjectRenderBuffers*")' in loading_sync
    assert '"background_quad"' in loading_sync
    assert '"LoadingQuadVertexView*"' in loading_sync
    assert "typedef struct LoadingBar" in loading_header
    assert "typedef struct LoadingVertex" in loading_header
    assert "typedef struct LoadingQuadVertexView" in loading_header
    assert "typedef struct LoadingBar" in path_header
    assert "typedef struct LoadingVertex" in path_header
    assert "typedef struct LoadingQuadVertexView" in path_header
    assert "def _sync_loading_quad_lvars()" in ida_path_sync
    assert '"loading_quad_lvars"' in ida_path_sync
    assert "typedef struct Options" in path_header
    assert "LoadingBar g_loading_bar;" in ida_path_sync
    for resource_declaration in (
        "Direct3DTexture8 *g_loading_bar_on_texture;",
        "ObjectRenderBuffers *g_loading_background_vertex_buffer;",
        "Direct3DTexture8 *g_loading_background_texture;",
        "ObjectRenderBuffers *g_loading_bar_vertex_buffer;",
    ):
        assert resource_declaration in ida_path_sync
    for address, resource_name in (
        ("0x503280", "g_loading_bar_on_texture"),
        ("0x503284", "g_loading_background_vertex_buffer"),
        ("0x503288", "g_loading_background_texture"),
        ("0x5032A4", "g_loading_bar_vertex_buffer"),
    ):
        assert f'({address}, "{resource_name}")' in ida_path_sync
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

    # The matcher keeps an intentional result-shaped VC6 harness, while the
    # analysis databases persist the independently evidenced semantic void ABI.
    assert "int kill_border(FrontendWidget* border);" in matcher_border_header
    assert "void set_border_justify_centre(" in matcher_border_header
    assert "float justify_centre);" in matcher_border_header
    assert "int set_border_justify_centre" not in matcher_border_header
    assert "justify_centre_bits" not in matcher_border_header
    assert "int __thiscall kill_border" not in frame_sync
    assert "int __thiscall kill_border" not in ida_frame_sync


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


def test_embedded_subgame_ai_void_abis_are_persisted() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")
    tutorial_header = (repo_root / "tools/match/include/tutorial.h").read_text(
        encoding="utf-8"
    )
    barrier_header = (repo_root / "tools/match/include/barrier_actor.h").read_text(
        encoding="utf-8"
    )

    for prototype in (
        "void __thiscall update_tutorial(Tutorial* tutorial)",
        "void __thiscall update_barrier_ai(BarrierActor* barrier)",
    ):
        assert prototype in binja_sync
        assert prototype + ";" in ida_sync
        assert prototype + ";" in header

    assert '(0x440F80, "update_barrier_ai")' in ida_sync
    assert "void update_tutorial();" in tutorial_header
    assert "void update_barrier_ai();" in barrier_header

    for stale in (
        "TrackRowCell* __thiscall update_tutorial",
        "void* __thiscall update_barrier_ai",
    ):
        assert stale not in binja_sync
        assert stale not in ida_sync
        assert stale not in header


def test_input_ok_overlay_and_void_abis_are_persisted() -> None:
    repo_root = Path(__file__).parents[1]
    binja_frontend_sync = (
        BINJA_DIR / "sync_frontend_widget_types.py"
    ).read_text(encoding="utf-8")
    binja_path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_frontend_sync = (IDA_DIR / "apply_frontend_replay_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = [
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in (
            "bn_frontend_widget_types.h",
            "frontend_replay_types.h",
            "path_template_types.h",
        )
    ]
    matcher_header = (
        repo_root / "tools/match/include/input_ok_state.h"
    ).read_text(encoding="utf-8")

    for header in analysis_headers:
        assert "typedef struct InputOkState" in header
        assert "FrontendWidget* source_widget;" in header
        assert "FrontendWidget* ok_widget;" in header
        assert "InputOkState input_ok_state;" in header
        assert "FrontendWidget* owner_widget_38;" not in header

    assert '"InputOkState": 0x24' in binja_frontend_sync
    assert '("0x1c", "input_ok_state", "InputOkState")' in binja_frontend_sync
    assert '"InputOkState",' in binja_path_sync
    for prototype in (
        "void __thiscall update_input_ok(InputOkState* input_ok)",
        "void __thiscall initialize_input_ok(InputOkState* input_ok)",
    ):
        assert prototype in binja_frontend_sync
        assert prototype in binja_path_sync
        assert prototype + ";" in ida_frontend_sync
        assert prototype + ";" in ida_path_sync

    assert '(0x4034D0, "update_input_ok")' in ida_frontend_sync
    assert '(0x403560, "initialize_input_ok")' in ida_frontend_sync
    assert "void update_input_ok(); // @ 0x4034d0, Android cRInputOK::AI()" in matcher_header
    assert "void initialize_input_ok();" in matcher_header
    assert "typedef InputOkState cRInputOK;" in matcher_header

    for stale in (
        "FrontendWidget* update_input_ok()",
        "FrontendWidget* initialize_input_ok()",
        "void* __thiscall update_input_ok",
        "void* __thiscall initialize_input_ok",
    ):
        assert stale not in matcher_header
        assert stale not in binja_frontend_sync
        assert stale not in binja_path_sync
        assert stale not in ida_frontend_sync
        assert stale not in ida_path_sync


def test_twinkle_array_ownership_and_void_abis_are_persisted() -> None:
    repo_root = Path(__file__).parents[1]
    binja_frontend_sync = (
        BINJA_DIR / "sync_frontend_widget_types.py"
    ).read_text(encoding="utf-8")
    binja_path_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_frontend_sync = (IDA_DIR / "apply_frontend_replay_types.py").read_text(
        encoding="utf-8"
    )
    ida_path_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_headers = [
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in (
            "bn_frontend_widget_types.h",
            "frontend_replay_types.h",
            "path_template_types.h",
        )
    ]
    matcher_manager_header = (
        repo_root / "tools/match/include/twinkle_manager.h"
    ).read_text(encoding="utf-8")

    for header in analysis_headers:
        assert "typedef struct Twinkle" in header
        assert "float target_alpha;" in header
        assert "FrontendWidget* owner_widget;" in header
        assert "Twinkle twinkles[5];" in header
        assert "uint8_t twinkles[0xf0];" not in header

    assert '"Twinkle": 0x30' in binja_frontend_sync
    assert '("0x00", "twinkles", "Twinkle[5]")' in binja_frontend_sync
    assert '"Twinkle",' in binja_path_sync
    for prototype in (
        "void __thiscall update_twinkle_manager(TwinkleManager* manager)",
        "void __thiscall draw_twinkle(Twinkle* twinkle)",
        "void __thiscall update_twinkle(Twinkle* twinkle)",
    ):
        assert prototype in binja_frontend_sync
        assert prototype in binja_path_sync
        assert prototype + ";" in ida_frontend_sync
        assert prototype + ";" in ida_path_sync

    for address_name in (
        '(0x404030, "update_twinkle_manager")',
        '(0x404070, "draw_twinkle")',
        '(0x404080, "update_twinkle")',
    ):
        assert address_name in ida_frontend_sync
        assert address_name in ida_path_sync

    assert "void update_twinkle_manager();" in matcher_manager_header
    assert "int update_twinkle_manager();" not in matcher_manager_header


def test_path_sample_tail_and_follow_gate_ownership_stay_aligned() -> None:
    repo_root = Path(__file__).parents[1]
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    matcher_sample = (
        repo_root / "tools/match/include/attachment_sample.h"
    ).read_text(encoding="utf-8")
    matcher_follow = (
        repo_root / "tools/match/include/track_attachment_types.h"
    ).read_text(encoding="utf-8")

    sample_struct = analysis_header.split(
        "typedef struct PathTemplateSample {", 1
    )[1].split("} PathTemplateSample;", 1)[0]
    follow_struct = analysis_header.split("typedef struct FollowState {", 1)[1].split(
        "} FollowState;", 1
    )[0]

    for source in (sample_struct, matcher_sample):
        assert "TransformMatrix inverse_matrix;" in source
        assert "float lateral_source;" in source
    assert "_pad_40" not in sample_struct
    assert "_pad_a4" not in sample_struct
    assert '("0x40", "inverse_matrix", "TransformMatrix")' in binja_sync
    assert '("0xa4", "lateral_source", "float")' in binja_sync
    assert '("PathTemplateSample", PATH_TEMPLATE_SAMPLE_FIELD_UPDATES)' in binja_sync

    assert "PATH_SAMPLE_INVERSE_USER_VAR_UPDATES" in binja_sync
    for identity in (
        '"StackVariableSourceType",\n        74,\n        -32,',
        '"StackVariableSourceType",\n        89,\n        -32,',
        '"RegisterVariableSourceType",\n        69,\n        67,',
        '"RegisterVariableSourceType",\n        332,\n        67,',
    ):
        assert identity in binja_sync
    for variable_name in (
        "primary_sample",
        "secondary_sample",
        "sample",
        "swept_sample",
    ):
        assert f'"{variable_name}"' in binja_sync
    assert "*PATH_SAMPLE_INVERSE_USER_VAR_UPDATES" in binja_sync

    assert "uint8_t flag_3c;" in follow_struct
    assert "unsigned char flag_3c;" in matcher_follow
    assert "_pad_3c" not in follow_struct
    assert '("0x3c", "flag_3c", "uint8_t")' in binja_sync
    assert '("FollowState", FOLLOW_STATE_FIELD_UPDATES)' in binja_sync
    attachment_entry_prototype = (
        "void __thiscall try_enter_track_attachment_from_swept_motion("
        "Path* self, float world_x, float world_y, float world_z, "
        "float sweep_dx, float sweep_dy, float sweep_dz, "
        "TrackRowCell* source_cell)"
    )
    assert attachment_entry_prototype in binja_sync
    assert attachment_entry_prototype + ";" in ida_sync
    assert "void __thiscall try_enter_track_attachment_from_swept_motion(" in analysis_header
    assert "TrackRowCell* source_cell" in analysis_header

    attachment_search_prototype = (
        "bool __thiscall is_point_inside_track_attachment("
        "Path* self, Vec3 probe, Vec3 swept_motion, TrackRowCell* cell)"
    )
    assert attachment_search_prototype in binja_sync
    assert attachment_search_prototype + ";" in ida_sync
    assert "".join((attachment_search_prototype + ";").split()) in "".join(
        analysis_header.split()
    )

    path_position_prototype = (
        "void __thiscall get_path_position_at_node("
        "Path* self, Vec3* out, int32_t node, int32_t row_index, Vec3* local)"
    )
    assert path_position_prototype in binja_sync
    assert path_position_prototype + ";" in ida_sync
    assert "".join((path_position_prototype + ";").split()) in "".join(
        analysis_header.split()
    )

    follow_update_prototype = (
        "int32_t __thiscall update_track_attachment_follow_state("
        "FollowState* follow_state, float path_factor, Vec3* out_position, "
        "Vec3* motion)"
    )
    assert follow_update_prototype in binja_sync
    assert follow_update_prototype + ";" in ida_sync
    assert follow_update_prototype + ";" in analysis_header

    for address in (
        "0x420C40",
        "0x420CB0",
        "0x42B9C0",
        "0x42C600",
        "0x42C770",
        "0x42CA90",
        "0x435EB0",
        "0x43B120",
        "0x4417D0",
    ):
        assert address in ida_sync
    for address in (
        "0x42C98A",
        "0x42C99C",
        "0x42C9B4",
        "0x42CA18",
        "0x42CA3D",
        "0x42CA5B",
        "0x42CA7B",
    ):
        assert address in ida_sync
    for address in (
        "0x420C92",
        "0x4212A3",
        "0x4214DB",
        "0x420D6A",
        "0x420D8A",
        "0x420DB0",
        "0x420DF7",
        "0x420E1C",
        "0x420E3D",
        "0x420E63",
    ):
        assert address in ida_sync
    for variable_name in (
        "primary_attachment_cell_restore",
        "entry_base_template",
        "primary_attachment_cell_transition_flags",
        "entry_transition_template",
        "primary_attachment_cell_transition_alpha",
    ):
        assert variable_name in binja_sync
    assert "ATTACHMENT_FOLLOW_ROOT_SPLIT_DEFINITIONS" in binja_sync
    assert "ATTACHMENT_FOLLOW_ROOT_TARGET_VAR" in binja_sync
    for address in ("0x420dab", "0x420e5e"):
        assert f'"{address}"' in binja_sync
    assert 'variable_name="attachment_game_base"' in binja_sync
    assert "idc.op_num(address, operand_index)" in ida_sync
    assert "for address in PATH_OWNERSHIP_DIRTY_FUNCTIONS:" in ida_sync
    assert "ida_hexrays.mark_cfunc_dirty(address, True)" in ida_sync


def test_path_receiver_replay_keeps_exact_abis_and_reanalyzes_callers() -> None:
    binja_sync = (BINJA_DIR / "sync_path_receiver_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_receiver_types.py").read_text(
        encoding="utf-8"
    )
    ida_runner = (IDA_DIR / "sync_path_receiver_types.py").read_text(
        encoding="utf-8"
    )
    broad_binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    broad_ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )

    declarations = (
        "void __thiscall get_path_position_at_node(Path* self, Vec3* out, int32_t node, int32_t row_index, Vec3* local)",
        "bool __thiscall is_point_inside_track_attachment(Path* self, Vec3 probe, Vec3 swept_motion, TrackRowCell* cell)",
    )
    for source in (
        binja_sync,
        ida_sync,
        broad_binja_sync,
        broad_ida_sync,
    ):
        for declaration in declarations:
            assert declaration in source
    compact_analysis_header = "".join(analysis_header.split())
    for declaration in declarations:
        assert "".join((declaration + ";").split()) in compact_analysis_header

    for source in (binja_sync, ida_sync):
        for owner, size in (
            ('"Vec3"', "0xC"),
            ('"TrackRowCell"', "0x54"),
            ('"PathTemplateSample"', "0xA8"),
            ('"Path"', "0xA8"),
        ):
            assert f"{owner}: {size}" in source

    for address, name in (
        ("0x42b9c0", "get_path_position_at_node"),
        ("0x42ca90", "is_point_inside_track_attachment"),
    ):
        assert f'("{address}", "{name}")' in binja_sync
        assert f'("{address}", "{name}")' in broad_binja_sync
        ida_address = address.upper().replace("0X", "0x")
        assert f'({ida_address}, "{name}")' in ida_sync
        assert f'({ida_address}, "{name}")' in broad_ida_sync

    for address in (
        "0x42B9C0",
        "0x42CA90",
        "0x4417D0",
        "0x4438E0",
        "0x444240",
    ):
        assert address in ida_sync

    assert "types_declare_if_missing" in binja_sync
    assert "owner_size_mismatch" in ida_sync
    assert "missing_reanalysis_function" in ida_sync
    assert "ida_hexrays.mark_cfunc_dirty(address, True)" in ida_sync
    assert (
        'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"'
        in ida_runner
    )


def test_remove_subgame_bods_cursor_ownership_is_replayed() -> None:
    binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )

    assert "REMOVE_SUBGAME_BODS_CURSOR_USER_VAR_UPDATES" in binja_sync
    for index, storage in (
        (9, 73),
        (15, 72),
        (181, 72),
        (587, 72),
        (712, 72),
        (848, 72),
        (1562, 72),
    ):
        assert (
            f'"RegisterVariableSourceType",\n        {index},\n        {storage},'
            in binja_sync
        )
    for name, type_name in (
        ("runtime_cell_cursor", "TrackRowCell*"),
        ("row_list_next_cursor", "BodNode**"),
        ("health_list_next_cursor", "BodNode**"),
        ("garbage_list_next_cursor", "BodNode**"),
        ("slug_list_next_cursor", "BodNode**"),
        ("ring_list_next_cursor", "BodNode**"),
        ("golb_shot_cursor", "GolbShot*"),
    ):
        assert f'"{name}"' in binja_sync
        assert f'"{type_name}"' in binja_sync
    assert "*REMOVE_SUBGAME_BODS_CURSOR_USER_VAR_UPDATES" in binja_sync

    assert "REMOVE_SUBGAME_BODS_CURSOR_LVAR_SPECS" in ida_sync
    for definition_address in (
        "0x44091A",
        "0x440920",
        "0x4409C6",
        "0x440B51",
        "0x440BD9",
        "0x440C61",
        "0x440F15",
    ):
        assert definition_address in ida_sync
    for name, declaration in (
        ("runtime_cell_cursor", "TrackRowCell *runtime_cell_cursor;"),
        ("row_list_next_cursor", "BodNode **row_list_next_cursor;"),
        ("health_list_next_cursor", "BodNode **health_list_next_cursor;"),
        ("garbage_list_next_cursor", "BodNode **garbage_list_next_cursor;"),
        ("slug_list_next_cursor", "BodNode **slug_list_next_cursor;"),
        ("ring_list_next_cursor", "BodNode **ring_list_next_cursor;"),
        ("golb_shot_cursor", "GolbShot *golb_shot_cursor;"),
    ):
        assert f'"{name}"' in ida_sync
        assert f'"{declaration}"' in ida_sync
    assert "_sync_remove_subgame_bods_cursor_lvars" in ida_sync
    assert '"remove_subgame_bods_cursor_lvars"' in ida_sync


def test_spawn_track_ring_slot_and_list_ownership_is_replayed() -> None:
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )

    assert "typedef struct SubRingSlotCursor {" in analysis_header
    assert "uint8_t subgame_prefix[0x35b78c];" in analysis_header
    assert "SubRing ring;" in analysis_header
    assert "} SubRingSlotCursor;" in analysis_header
    assert '"SubRingSlotCursor"' in binja_sync

    assert "SPAWN_TRACK_RING_USER_VAR_UPDATES" in binja_sync
    for index, storage in (
        (3, 66),
        (11, 67),
        (76, 72),
        (123, 71),
        (1263, 66),
        (1268, 67),
        (1289, 67),
        (1291, 71),
        (1297, 67),
        (1299, 67),
    ):
        assert (
            f'"RegisterVariableSourceType",\n        {index},\n        {storage},'
            in binja_sync
        )
    assert '"StackVariableSourceType",\n        114,\n        -16,' in binja_sync
    for name, type_name in (
        ("slot_index", "int32_t"),
        ("state_cursor", "SubRingState*"),
        ("slot_cursor", "SubRingSlotCursor*"),
        ("default_phase_step", "float"),
        ("effective_kind", "int32_t"),
        ("active_head", "BodNode**"),
        ("active_first", "BodNode*"),
        ("first_for_link", "BodNode*"),
        ("linked_head", "BodNode*"),
        ("first_for_promote", "BodNode*"),
        ("promoted_head", "BodNode*"),
    ):
        assert f'"{name}"' in binja_sync
        assert f'"{type_name}"' in binja_sync
    assert "*SPAWN_TRACK_RING_USER_VAR_UPDATES" in binja_sync

    assert "SPAWN_TRACK_RING_LVAR_SPECS" in ida_sync
    for definition_address in (
        "0x43DF14",
        "0x43DF1C",
        "0x43DF5D",
        "0x43DF83",
        "0x43DF8C",
        "0x43E3DB",
        "0x43E400",
        "0x43E405",
        "0x43E424",
    ):
        assert definition_address in ida_sync
    for name, declaration in (
        ("slot_index", "int32_t slot_index;"),
        ("state_cursor", "SubRingState *state_cursor;"),
        ("slot_cursor", "SubRingSlotCursor *slot_cursor;"),
        ("default_phase_step", "float default_phase_step;"),
        ("effective_kind", "int32_t effective_kind;"),
        ("selected_ring", "SubRing *selected_ring;"),
        ("active_head", "BodNode **active_head;"),
        ("active_first", "BodNode *active_first;"),
        ("promoted_head", "BodNode *promoted_head;"),
    ):
        assert f'"{name}"' in ida_sync
        assert f'"{declaration}"' in ida_sync
    assert "_sync_spawn_track_ring_lvars" in ida_sync
    assert '"spawn_track_ring_lvars"' in ida_sync


def test_collision_pool_cursor_ownership_is_replayed() -> None:
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    collision_state_sync = (
        BINJA_DIR / "sync_collision_state_lifetimes.py"
    ).read_text(encoding="utf-8")

    for cursor_name, prefix, field_declaration in (
        ("SubHealthSlotCursor", "0x356000", "SubHealth health;"),
        ("SlugSlotCursor", "0x3563a0", "Slug slug;"),
        ("SubLazerSlotCursor", "0x356b00", "SubLazer sub_lazer;"),
        ("SaltSlotCursor", "0x3578c0", "Salt salt;"),
        ("ParcelSlotCursor", "0x125e480", "Parcel parcel;"),
    ):
        assert f"typedef struct {cursor_name} {{" in analysis_header
        assert f"uint8_t subgame_prefix[{prefix}];" in analysis_header
        assert field_declaration in analysis_header
        assert f"}} {cursor_name};" in analysis_header
        assert f'"{cursor_name}"' in binja_sync

    assert "COLLISION_POOL_CURSOR_USER_VAR_UPDATES" in binja_sync
    for index, storage in (
        (80, 66),
        (310, 66),
        (828, 66),
        (1385, 66),
        (1663, 66),
        (2353, 66),
    ):
        assert (
            f'"RegisterVariableSourceType",\n        {index},\n        {storage},'
            in binja_sync
        )
    for name, type_name in (
        ("salt_cursor", "SaltSlotCursor*"),
        ("sub_lazer_cursor", "SubLazerSlotCursor*"),
        ("slug_cursor", "SlugSlotCursor*"),
        ("parcel_cursor", "ParcelSlotCursor*"),
        ("health_cursor", "SubHealthSlotCursor*"),
        ("ring_cursor", "SubRingSlotCursor*"),
    ):
        assert f'"{name}"' in binja_sync
        assert f'"{type_name}"' in binja_sync
    assert "*COLLISION_POOL_CURSOR_USER_VAR_UPDATES" in binja_sync
    assert "apply_user_var_updates" in collision_state_sync
    for index, storage, name, type_name in (
        (821, 67, "slug_state", "SubSlugState"),
        (1388, 67, "parcel_state", "ParcelState"),
        (1666, 67, "health_state", "TrackPickupState"),
        (2346, 67, "ring_state", "SubRingState"),
        (2516, 66, "ring_kind", "SubRingKind"),
        (2573, 66, "effect_kind", "SubRingKind"),
    ):
        expected = (
            '"handle_subgoldy_collisions",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in collision_state_sync
    for enum_name in (
        "ParcelState",
        "TrackPickupState",
        "SubSlugState",
        "SubRingState",
        "SubRingKind",
    ):
        assert f'"{enum_name}": (' in collision_state_sync

    assert "COLLISION_POOL_CURSOR_LVAR_SPECS" in ida_sync
    for definition_address in (
        "0x444D41",
        "0x444E27",
        "0x44502D",
        "0x44525A",
        "0x445370",
        "0x445622",
        "0x4456C5",
        "0x4456FE",
    ):
        assert definition_address in ida_sync
    for name, declaration in (
        ("salt_cursor", "SaltSlotCursor *salt_cursor;"),
        ("sub_lazer_cursor", "SubLazerSlotCursor *sub_lazer_cursor;"),
        ("slug_cursor", "SlugSlotCursor *slug_cursor;"),
        ("parcel_cursor", "ParcelSlotCursor *parcel_cursor;"),
        ("health_cursor", "SubHealthSlotCursor *health_cursor;"),
        ("ring_cursor", "SubRingSlotCursor *ring_cursor;"),
        ("ring_kind", "SubRingKind ring_kind;"),
        ("effect_kind", "SubRingKind effect_kind;"),
    ):
        assert f'"{name}"' in ida_sync
        assert f'"{declaration}"' in ida_sync
    assert "_sync_collision_pool_cursor_lvars" in ida_sync
    assert '"collision_pool_cursor_lvars"' in ida_sync
    assert "0x444CF0,  # handle_subgoldy_collisions" in ida_sync


def test_collision_pool_offset_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_collision_pool_offset_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Salt", "0x98"),
        ("SaltManager", "0x17C0"),
        ("SubLazer", "0xB0"),
        ("SubLazerManager", "0xDC0"),
        ("Slug", "0xEC"),
        ("SlugPool", "0x760"),
        ("Parcel", "0x8C"),
        ("ParcelManager", "0x1B58"),
        ("SubHealth", "0x74"),
        ("SubGarbage", "0xC4"),
        ("SubGarbagePool", "0x264C"),
        ("SubRing", "0x1F8"),
        ("SubRingPool", "0x3F0"),
        ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("SaltManager", "0x00", "slots", "Salt[40]"),
        ("SubLazerManager", "0x00", "slots", "SubLazer[20]"),
        ("SlugPool", "0x00", "slots", "Slug[8]"),
        ("ParcelManager", "0x00", "slots", "Parcel[50]"),
        ("SubRingPool", "0x00", "slots", "SubRing[2]"),
        ("SubGarbagePool", "0x00", "active_head", "SubGarbage*"),
        ("SubGarbagePool", "0x04", "slots", "SubGarbage[50]"),
        ("SubgameRuntime", "0x356000", "health_pickups", "SubHealth[8]"),
        ("SubgameRuntime", "0x3563A0", "slug_hazards", "SlugPool"),
        ("SubgameRuntime", "0x356B00", "sub_lazers", "SubLazerManager"),
        ("SubgameRuntime", "0x3578C0", "salt_hazards", "SaltManager"),
        (
            "SubgameRuntime",
            "0x359140",
            "garbage_hazards",
            "SubGarbagePool",
        ),
        ("SubgameRuntime", "0x35B78C", "ring_effects", "SubRingPool"),
        ("SubgameRuntime", "0x125E480", "parcel_manager", "ParcelManager"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for index, name in (
        (67, "salt_pool_byte_offset"),
        (304, "sub_lazer_pool_byte_offset"),
        (490, "active_garbage"),
        (815, "slug_pool_byte_offset"),
        (1377, "parcel_pool_byte_offset"),
        (1657, "health_pool_byte_offset"),
        (2328, "ring_pool_byte_offset"),
    ):
        variable_type = "SubGarbage*" if name == "active_garbage" else "int32_t"
        expected = (
            '        "handle_subgoldy_collisions",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            "        73,\n"
            f'        "{name}",\n'
            f'        "{variable_type}"'
        )
        assert expected in replay

    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay


def test_jet_particle_bank_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_jet_particle_bank_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Vec3", "0xC"),
        ("tColour", "0x10"),
        ("JetParticleSlot", "0x10"),
        ("SubHover", "0x214"),
        ("RenderableBod", "0x80"),
        ("Weapon", "0x3DC"),
        ("Snail", "0x19B4"),
        ("Player", "0x4364"),
        ("Sprite", "0xB4"),
        ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("JetParticleSlot", "0x00", "sprite", "Sprite*"),
        ("SubHover", "0x10", "player", "Player*"),
        ("SubHover", "0x20", "particle_slots", "JetParticleSlot[30]"),
        ("SubHover", "0x200", "game", "SubgameRuntime*"),
        ("Player", "0x380", "player_slot", "int32_t"),
        ("Player", "0x410", "velocity", "Vec3"),
        ("Player", "0x2750", "sub_hover", "SubHover"),
        ("Player", "0x2984", "presentation", "Snail"),
        ("Snail", "0x11E0", "jetpack_channel", "Weapon"),
        ("Snail", "0x17B0", "snail_hotspots_world", "Vec3[19]"),
        ("Sprite", "0x48", "position", "Vec3"),
        ("Sprite", "0x54", "velocity", "Vec3"),
        ("Sprite", "0x78", "gravity_step", "float"),
        ("SubgameRuntime", "0x3BB764", "player", "Player"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for function_name, source_type, index, storage, name, type_name in (
        (
            "initialize_jet_particles",
            "RegisterVariableSourceType",
            7,
            72,
            "particle_slot_cursor",
            "JetParticleSlot*",
        ),
        (
            "uninit_jet_particles",
            "RegisterVariableSourceType",
            3,
            72,
            "particle_slot_cursor",
            "JetParticleSlot*",
        ),
        (
            "update_jet_particles",
            "StackVariableSourceType",
            74,
            -60,
            "random_back_seed",
            "float",
        ),
        (
            "update_jet_particles",
            "RegisterVariableSourceType",
            295,
            66,
            "particle_slot",
            "JetParticleSlot*",
        ),
        (
            "update_jet_particles",
            "RegisterVariableSourceType",
            429,
            66,
            "trail_puff",
            "Sprite*",
        ),
    ):
        expected = (
            f'        "{function_name}",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in replay

    assert "STALE_JET_PARTICLE_USER_VARS" in replay
    assert "remove_user_var_updates" in replay
    assert "apply_user_var_updates" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay


def test_snail_weapon_state_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_snail_weapon_state_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Weapon", "0x3DC"),
        ("Snail", "0x19B4"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("Weapon", "0x104", "selected_state", "int32_t"),
        ("Snail", "0x064C", "weapon_channels", "Weapon[3]"),
        ("Snail", "0x11E0", "jetpack_channel", "Weapon"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    assert '"0x445920", "mlil", "StackVariableSourceType", 524288, -4' in replay
    assert '"StackVariableSourceType",\n    40,\n    -4' in replay
    for name in (
        "target_channel_2_state",
        "channel_0_immediate",
        "channel_1_immediate",
        "channel_2_immediate",
        "any_channel_changed",
        "target_channel_0_state",
        "target_channel_1_state",
        "channel_0_selected_state",
        "channel_1_selected_state",
        "channel_2_selected_state",
        "target_state",
        "selected_state",
        "transition_immediate",
    ):
        assert f'"{name}"' in replay
    assert "apply_split_away_user_var_update" in replay
    assert "apply_split_user_var_update" in replay
    assert "apply_user_var_updates" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    for index, storage, variable_name, variable_type in (
        (16, 69, "target_state", "int32_t"),
        (31, 66, "selected_state", "int32_t"),
        (98, 66, "transition_immediate", "uint8_t"),
    ):
        update = (
            '"set_snail_jetpack",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{variable_name}",\n'
            f'        "{variable_type}",'
        )
        assert update in replay


def test_mobile_backed_owner_health_guards_are_registered() -> None:
    repo_root = Path(__file__).parents[1]
    checks = {
        check["name"]: check
        for check in json.loads(
            (repo_root / "analysis/decompile/health_checks.json").read_text(
                encoding="utf-8"
            )
        )["checks"]
    }

    expected = {
        "bn_input_update_mobile_owner_contract": "0040aa80-update_input.c",
        "ida_input_update_mobile_owner_contract": "0040aa80-update_input.c",
        "bn_rtext_copy_mobile_contract": "00431da0-copy_c_string.c",
        "ida_rtext_copy_mobile_contract": "00431da0-copy_c_string.c",
        "bn_rtext_comp_start_mobile_contract": (
            "00431dc0-strings_equal_case_insensitive.c"
        ),
        "ida_rtext_comp_start_mobile_contract": (
            "00431dc0-strings_equal_case_insensitive.c"
        ),
        "bn_rtext_new_line_mobile_contract": "00431e30-skip_to_next_line.c",
        "ida_rtext_new_line_mobile_contract": "00431e30-skip_to_next_line.c",
        "bn_rtext_append_mobile_contract": "00431e50-append_c_string.c",
        "ida_rtext_append_mobile_contract": "00431e50-append_c_string.c",
        "bn_rtext_extract_string_mobile_contract": (
            "00431e80-parse_next_space_delimited_token.c"
        ),
        "ida_rtext_extract_string_mobile_contract": (
            "00431e80-parse_next_space_delimited_token.c"
        ),
        "bn_rtext_extract_int_mobile_contract": (
            "00431ec0-parse_next_int32.c"
        ),
        "ida_rtext_extract_int_mobile_contract": (
            "00431ec0-parse_next_int32.c"
        ),
        "bn_rtext_extract_float_mobile_contract": (
            "00431f20-parse_next_float32.c"
        ),
        "ida_rtext_extract_float_mobile_contract": (
            "00431f20-parse_next_float32.c"
        ),
        "bn_snail_jetpack_mobile_state_ownership": (
            "00445860-set_snail_jetpack.c"
        ),
        "ida_snail_jetpack_mobile_state_ownership": (
            "00445860-set_snail_jetpack.c"
        ),
        "bn_rstrfind_mobile_argument_ownership": (
            "0044e600-find_case_insensitive_substring.c"
        ),
        "ida_rstrfind_mobile_argument_ownership": (
            "0044e600-find_case_insensitive_substring.c"
        ),
        "bn_rstrasc_mobile_contract": "0044e5a0-ascii_upper_if_lowercase.c",
        "ida_rstrasc_mobile_contract": "0044e5a0-ascii_upper_if_lowercase.c",
        "bn_rstrcpy_mobile_contract": "0044e5b0-rstrcpy_checked_ascii.c",
        "ida_rstrcpy_mobile_contract": "0044e5b0-rstrcpy_checked_ascii.c",
        "bn_rstrnewline_mobile_contract": (
            "0044e690-advance_to_next_crlf_line.c"
        ),
        "ida_rstrnewline_mobile_contract": (
            "0044e690-advance_to_next_crlf_line.c"
        ),
        "bn_rstrcmp_mobile_contract": (
            "0044e6c0-strings_equal_case_insensitive_path.c"
        ),
        "ida_rstrcmp_mobile_contract": (
            "0044e6c0-strings_equal_case_insensitive_path.c"
        ),
        "bn_rstrint_mobile_contract": "0044e710-parse_next_signed_int.c",
        "ida_rstrint_mobile_contract": "0044e710-parse_next_signed_int.c",
    }
    for name, artifact_name in expected.items():
        assert checks[name]["artifact"].endswith(artifact_name)
        assert checks[name]["required_substrings"]
        assert checks[name]["forbidden_substrings"]

    assert (
        "uint8_t transition_immediate"
        in checks["ida_snail_jetpack_mobile_state_ownership"][
            "required_substrings"
        ]
    )
    assert (
        "return *prefix_1 == 0"
        in checks["bn_rtext_comp_start_mobile_contract"][
            "required_substrings"
        ]
    )
    assert (
        "return (x87_r7 * x87_r5 * x87_r6).d"
        in checks["bn_rtext_extract_float_mobile_contract"][
            "required_substrings"
        ]
    )
    assert (
        "char* pattern_1 = pattern"
        in checks["bn_rstrfind_mobile_argument_ownership"]["required_substrings"]
    )
    assert (
        "return 1"
        in checks["bn_rstrcmp_mobile_contract"]["required_substrings"]
    )
    assert (
        "int __cdecl strings_equal_case_insensitive_path(char *left, char *right)"
        in checks["ida_rstrcmp_mobile_contract"]["required_substrings"]
    )


def test_subgoldy_position_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_subgoldy_position_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Vec3", "0xC"),
        ("TransformMatrix", "0x40"),
        ("RenderableBod", "0x80"),
        ("Player", "0x4364"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("TransformMatrix", "0x30", "position", "Vec3"),
        ("TransformMatrix", "0x3C", "position_w", "float"),
        ("RenderableBod", "0x38", "transform", "TransformMatrix"),
        ("Player", "0x00", "body", "RenderableBod"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for definition in (
        '"0x43b2c0", "mlil", "RegisterVariableSourceType", 416, 69',
        '"0x43b4f6", "mlil", "RegisterVariableSourceType", 982, 69',
    ):
        assert definition in replay
    assert 'variable_name="p_position"' in replay
    assert 'variable_type="Vec3*"' in replay
    assert (
        '        "RegisterVariableSourceType",\n'
        "        1396,\n"
        "        69,\n"
        '        "p_position",\n'
        '        "Vec3*"'
    ) in replay
    assert (
        '        "RegisterVariableSourceType",\n'
        "        3225,\n"
        "        67,\n"
        '        "swept_position",\n'
        '        "Vec3*"'
    ) in replay
    assert "apply_split_user_var_update" in replay
    assert "apply_user_var_updates" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay


def test_track_fringe_mesh_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_track_fringe_mesh_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Vec3", "0x0C"),
        ("BodBase", "0x38"),
        ("ObjectFaceQuad", "0x30"),
        ("FringeVertexRowCursorView", "0x30"),
        ("FringeFaceQuadPairCursorView", "0x60"),
        ("Object", "0xDC"),
        ("Path", "0xA8"),
    ):
        assert f'"{owner_name}": {expected_size}' in replay

    for struct_name, offset, field_name, field_type in (
        ("Vec3", "0x00", "x", "float"),
        ("BodBase", "0x24", "object", "Object*"),
        ("ObjectFaceQuad", "0x02", "vertex_0", "uint16_t"),
        ("ObjectFaceQuad", "0x0C", "texture_ref", "TextureRef*"),
        ("FringeVertexRowCursorView", "0x00", "outer_a", "Vec3"),
        ("FringeVertexRowCursorView", "0x18", "outer_b", "Vec3"),
        ("FringeFaceQuadPairCursorView", "0x30", "second_face", "ObjectFaceQuad"),
        ("Object", "0x38", "vertices", "Vec3*"),
        ("Object", "0x5C", "facequads", "ObjectFaceQuad*"),
        ("Path", "0x44", "segment_count", "uint32_t"),
        ("Path", "0x60", "fringe_mesh_bod", "BodBase"),
    ):
        assert f'"{struct_name}": {{' in replay
        assert f'{offset}: ("{field_name}", "{field_type}")' in replay

    for function_name, source_type, index, storage, name, variable_type in (
        (
            "build_track_fringe_mesh",
            "RegisterVariableSourceType",
            58,
            69,
            "generated_mesh",
            "Object*",
        ),
        (
            "build_track_fringe_mesh",
            "RegisterVariableSourceType",
            140,
            72,
            "generated_vertices",
            "Vec3*",
        ),
        (
            "build_track_fringe_mesh",
            "RegisterVariableSourceType",
            163,
            72,
            "row_cursor",
            "FringeVertexRowCursorView*",
        ),
        (
            "build_track_fringe_mesh",
            "RegisterVariableSourceType",
            221,
            69,
            "generated_row",
            "Vec3*",
        ),
        (
            "build_track_fringe_mesh",
            "StackVariableSourceType",
            143,
            -92,
            "generated_facequads",
            "ObjectFaceQuad*",
        ),
        (
            "build_track_fringe_mesh",
            "RegisterVariableSourceType",
            860,
            72,
            "face_pair_cursor",
            "FringeFaceQuadPairCursorView*",
        ),
        (
            "build_track_fringe_supertramp_mesh",
            "RegisterVariableSourceType",
            28,
            69,
            "generated_mesh",
            "Object*",
        ),
        (
            "build_track_fringe_supertramp_mesh",
            "RegisterVariableSourceType",
            89,
            73,
            "generated_vertices",
            "Vec3*",
        ),
        (
            "build_track_fringe_supertramp_mesh",
            "RegisterVariableSourceType",
            92,
            69,
            "generated_facequads",
            "ObjectFaceQuad*",
        ),
        (
            "build_track_fringe_supertramp_mesh",
            "RegisterVariableSourceType",
            109,
            73,
            "row_cursor",
            "FringeVertexRowCursorView*",
        ),
        (
            "build_track_fringe_supertramp_mesh",
            "RegisterVariableSourceType",
            614,
            73,
            "face_pair_cursor",
            "FringeFaceQuadPairCursorView*",
        ),
        (
            "build_track_fringe_supertramp_mesh",
            "RegisterVariableSourceType",
            836,
            66,
            "final_row_first_edge",
            "Vec3*",
        ),
        (
            "build_track_fringe_supertramp_mesh",
            "RegisterVariableSourceType",
            852,
            67,
            "first_cap_vertex",
            "Vec3*",
        ),
        (
            "build_track_fringe_supertramp_mesh",
            "RegisterVariableSourceType",
            959,
            66,
            "final_row_second_edge",
            "Vec3*",
        ),
        (
            "build_track_fringe_supertramp_mesh",
            "RegisterVariableSourceType",
            1086,
            68,
            "first_cap_vertex_copy",
            "Vec3*",
        ),
        (
            "build_track_fringe_supertramp_mesh",
            "RegisterVariableSourceType",
            1093,
            66,
            "final_row_copy",
            "Vec3*",
        ),
        (
            "build_track_fringe_supertramp_mesh",
            "RegisterVariableSourceType",
            1122,
            73,
            "final_generated_row",
            "Vec3*",
        ),
    ):
        expected = (
            f'        "{function_name}",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}"'
        )
        assert expected in replay

    assert "face_vertex_cursor" not in replay
    assert "apply_user_var_updates" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay


def test_track_fringe_mesh_cursor_views_stay_borrowed_and_replayable() -> None:
    repo_root = Path(__file__).parents[1]
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    canonical_binja = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    canonical_ida = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )
    matcher_sources = "\n".join(
        (
            (
                repo_root
                / "tools/match/scratches/build_track_fringe_mesh/scratch.cpp"
            ).read_text(encoding="utf-8"),
            (
                repo_root
                / (
                    "tools/match/scratches/"
                    "build_track_fringe_supertramp_mesh/scratch.cpp"
                )
            ).read_text(encoding="utf-8"),
        )
    )
    health_checks = {
        check["name"]: check
        for check in json.loads(
            (repo_root / "analysis/decompile/health_checks.json").read_text(
                encoding="utf-8"
            )
        )["checks"]
    }

    for marker in (
        "typedef struct __ptr_offset(0x14)",
        "__base(Vec3, 0x0c) FringeVertexRowCursorView {",
        "__inherited Vec3 inner_a;",
        "FringeVertexRowCursorView_must_be_0x30",
        "typedef struct __ptr_offset(0x02)",
        "__base(ObjectFaceQuad, 0x00) FringeFaceQuadPairCursorView {",
        "__inherited ObjectFaceQuad first_face;",
        "FringeFaceQuadPairCursorView_must_be_0x60",
        "The generated Object::vertices bank remains the",
        "Object::facequads remains the sole owner.",
    ):
        assert marker in analysis_header

    for type_name in (
        "FringeVertexRowCursorView",
        "FringeFaceQuadPairCursorView",
    ):
        assert type_name not in matcher_sources
        assert type_name in canonical_binja
        assert type_name in canonical_ida

    assert "FRINGE_MESH_CURSOR_SIZES" in canonical_binja
    assert "verify_fringe_mesh_cursor_sizes" in canonical_binja
    assert '"owner_group": "fringe_mesh_cursor"' in canonical_binja
    assert "FRINGE_MESH_CURSOR_HEADER_MARKERS" in canonical_ida
    assert "FRINGE_VERTEX_ROW_CURSOR_EXPECTED_SIZE = 0x30" in canonical_ida
    assert "FRINGE_FACE_PAIR_CURSOR_EXPECTED_SIZE = 0x60" in canonical_ida
    assert "FRINGE_MESH_LVAR_SPECS" in canonical_ida
    for name, declaration, definition_address in (
        (
            "row_cursor",
            (
                "float *__shifted("
                "FringeVertexRowCursorView, 0x14) row_cursor;"
            ),
            "0x424744",
        ),
        (
            "face_pair_cursor",
            (
                "uint16_t *__shifted("
                "FringeFaceQuadPairCursorView, 0x02) face_pair_cursor;"
            ),
            "0x4249FD",
        ),
        (
            "row_cursor",
            (
                "float *__shifted("
                "FringeVertexRowCursorView, 0x14) row_cursor;"
            ),
            "0x424B3E",
        ),
        (
            "face_pair_cursor",
            (
                "uint16_t *__shifted("
                "FringeFaceQuadPairCursorView, 0x02) face_pair_cursor;"
            ),
            "0x424D37",
        ),
    ):
        assert f'"{name}"' in canonical_ida
        assert f'"{declaration}"' in canonical_ida
        assert definition_address in canonical_ida

    assert "fringe_mesh_lvars = _sync_fringe_mesh_lvars()" in canonical_ida
    for address in ("0x4246A0", "0x424AD0"):
        assert address in canonical_ida

    for check_name in (
        "bn_track_fringe_mesh_object_owners",
        "bn_track_fringe_supertramp_object_owners",
    ):
        check = health_checks[check_name]
        for marker in (
            "struct FringeVertexRowCursorView* row_cursor",
            "struct FringeFaceQuadPairCursorView* face_pair_cursor",
            "face_pair_cursor->second_face.texture_ref",
        ):
            assert marker in check["required_substrings"]

    assert "__offset" in health_checks[
        "bn_track_fringe_mesh_object_owners"
    ]["forbidden_substrings"]
    assert "__offset" not in health_checks[
        "bn_track_fringe_supertramp_object_owners"
    ]["forbidden_substrings"]

    for check_name in (
        "ida_track_fringe_mesh_borrowed_cursors",
        "ida_track_fringe_supertramp_borrowed_cursors",
    ):
        check = health_checks[check_name]
        for marker in (
            "float *__shifted(FringeVertexRowCursorView,0x14) row_cursor",
            (
                "uint16_t *__shifted("
                "FringeFaceQuadPairCursorView,2) face_pair_cursor"
            ),
            "ADJ(row_cursor)->inner_a",
            "ADJ(face_pair_cursor)->second_face.vertex_0",
        ):
            assert marker in check["required_substrings"]
        assert "p_vertex_0" in check["forbidden_substrings"]


def test_vapour_and_track_pickup_base_owners_are_replayed() -> None:
    repo_root = Path(__file__).parents[1]
    analysis_header = (HEADER_DIR / "path_template_types.h").read_text(
        encoding="utf-8"
    )
    pool_header = (HEADER_DIR / "bn_subgame_pool_types.h").read_text(
        encoding="utf-8"
    )
    matcher_header = (repo_root / "tools/match/include/vapour.h").read_text(
        encoding="utf-8"
    )
    jetpack_scratch = (
        repo_root
        / "tools/match/scratches/initialize_track_jetpack_pickup_runtime/scratch.cpp"
    ).read_text(encoding="utf-8")
    vapour_scratch = (
        repo_root / "tools/match/scratches/update_vapour/scratch.cpp"
    ).read_text(encoding="utf-8")
    binja_sync = (BINJA_DIR / "sync_path_template_types.py").read_text(
        encoding="utf-8"
    )
    pool_sync = (BINJA_DIR / "sync_subgame_pool_types.py").read_text(
        encoding="utf-8"
    )
    ida_sync = (IDA_DIR / "apply_path_template_types.py").read_text(
        encoding="utf-8"
    )

    assert "class Vapour : public RenderableBod" in matcher_header
    assert "virtual void update_vapour" not in matcher_header
    assert "Object* owner;" not in matcher_header
    assert "typedef struct Vapour {\n    RenderableBod body;" in pool_header
    assert "Object* owner;" not in pool_header
    for declaration in (
        "typedef struct Vapour {\n    RenderableBod body;",
        "typedef struct JetPack {\n    BodBase bod;",
        "typedef struct SubHealth {\n    BodBase bod;",
        "typedef struct JetPackSlotCursor {\n    uint8_t subgame_prefix[0x355e64];\n    JetPack jetpack;",
    ):
        assert declaration in analysis_header

    assert "vapour_a.initialize_renderable_bod()" in jetpack_scratch
    assert "vapour_b.initialize_renderable_bod()" in jetpack_scratch
    assert "RenderableBod* vapour" not in jetpack_scratch
    assert "object->vertex_count" in vapour_scratch
    assert "owner->" not in vapour_scratch

    for address, name in (
        ("0x497314", "g_sub_speed_up_vtable"),
        ("0x497318", "g_jet_pack_vtable"),
        ("0x49731c", "g_vapour_vtable"),
        ("0x497320", "g_sub_health_vtable"),
    ):
        assert f'("{address}", "{name}")' in binja_sync
        assert f'("{address}", "void*")' in binja_sync
        assert name in ida_sync

    for update in (
        '("Vapour", VAPOUR_FIELD_UPDATES)',
        '("JetPack", JETPACK_FIELD_UPDATES)',
        '("SubHealth", SUB_HEALTH_FIELD_UPDATES)',
        '("SubSpeedUp", SUB_SPEED_UP_FIELD_UPDATES)',
    ):
        assert update in binja_sync
    assert '("0x00", "body", "RenderableBod")' in binja_sync
    assert '("0x00", "bod", "BodBase")' in binja_sync
    assert 'VAPOUR_FIELD_UPDATES = (\n    ("0x00", "body", "RenderableBod")' in pool_sync
    assert (
        'SUB_SPEEDUP_FIELD_UPDATES = (\n    ("0x00", "body", "RenderableBod")'
        in pool_sync
    )
    assert '("0x24", "owner", "Object*")' not in pool_sync
    assert '("0x10", "bod_position", "Vec3")' not in pool_sync
    assert '"JetPackSlotCursor",' in binja_sync
    for replay in (
        '"spawn_track_health_pickup",\n        "RegisterVariableSourceType",\n        60,\n        72,\n        "health_cursor",\n        "SubHealthSlotCursor*"',
        '"spawn_track_jetpack_pickup",\n        "RegisterVariableSourceType",\n        61,\n        72,\n        "jetpack_cursor",\n        "JetPackSlotCursor*"',
    ):
        assert replay in binja_sync
    for replay in (
        '"SubHealthSlotCursor *health_cursor;",\n        0x43D6FD',
        '"JetPackSlotCursor *jetpack_cursor;",\n        0x43D8CE',
        '("sprite", "Sprite *sprite;", 0x43D7C1, None)',
        '("sprite", "Sprite *sprite;", 0x43D9CC, None)',
        "_sync_spawn_track_health_lvars()",
        "_sync_spawn_track_jetpack_lvars()",
    ):
        assert replay in ida_sync


def test_landscape_activation_replay_preserves_stride_and_interior_borrows() -> None:
    header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")
    replay = (
        BINJA_DIR / "sync_landscape_activation_lifetimes.py"
    ).read_text(encoding="utf-8")

    assert "typedef struct LandscapeScriptStrideAnchor {" in header
    assert "uint8_t manager_prefix[0x5a4];" in header
    assert "LandscapeScriptRecord script;" in header
    assert "LandscapeScriptStrideAnchor_must_be_0x6c8" in header

    for type_name, width in (
        ("ActiveLandscapeEntry", "0x90"),
        ("LandscapeScriptRecord", "0x124"),
        ("LandscapeManager", "0x97A4"),
        ("LandscapeScriptStrideAnchor", "0x6C8"),
    ):
        assert f'"{type_name}": {width}' in replay

    assert "types_declare_if_missing" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert (
        '"activate_landscape_entry",\n'
        '        "RegisterVariableSourceType",\n'
        '        111,\n'
        '        73,\n'
        '        "selected_script_anchor",\n'
        '        "LandscapeScriptStrideAnchor*"'
        in replay
    )
    rejected_cursor = (
        '"activate_landscape_entry",\n'
        '        "RegisterVariableSourceType",\n'
        '        114,\n'
        '        72,\n'
        '        "active_entry_list_flags_cursor",\n'
        '        "uint32_t*"'
    )
    assert rejected_cursor in replay
    assert "remove_user_var_updates" in replay
    assert rejected_cursor not in replay.split(
        "LANDSCAPE_ACTIVATION_USER_VAR_UPDATES", 1
    )[1].split("REJECTED_ACTIVE_ENTRY_CURSOR_REMOVALS", 1)[0]
    assert "ActiveLandscapeEntry*" not in replay.split(
        "LANDSCAPE_ACTIVATION_USER_VAR_UPDATES", 1
    )[1].split("REJECTED_ACTIVE_ENTRY_CURSOR_REMOVALS", 1)[0]


def test_track_warning_replay_preserves_field_first_cell_borrows() -> None:
    header = (HEADER_DIR / "path_template_types.h").read_text(encoding="utf-8")
    replay = (BINJA_DIR / "sync_track_warning_lifetimes.py").read_text(
        encoding="utf-8"
    )

    assert "typedef struct TrackRowCellTileByteView {" in header
    assert "SubLocTileId tile_id;" in header
    assert "uint32_t lane_and_flags;" in header
    assert "uint8_t stride_tail[0x54 - 0x08];" in header
    assert "TrackRowCellTileByteView_must_stride_0x54" in header
    assert "typedef struct TrackRowCellObjectSlotView {" in header
    assert "void* object;" in header
    assert "uint8_t object_to_lane_and_flags[0x18];" in header
    assert "uint8_t stride_tail[0x54 - 0x20];" in header
    assert "TrackRowCellObjectSlotView_must_stride_0x54" in header

    for type_name, width in (
        ("TrackRowCell", "0x54"),
        ("TrackRowCellObjectSlotView", "0x54"),
        ("TrackRowCellTileByteView", "0x54"),
        ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{type_name}": {width}' in replay

    for index, storage, name in (
        (25, 66, "row_tile_cursor"),
        (39, 68, "cell_tile_cursor"),
        (35, -8, "saved_cell_tile_cursor"),
    ):
        expected = (
            '        "mark_track_warning_zones",\n'
            f'        "{"RegisterVariableSourceType" if storage >= 0 else "StackVariableSourceType"}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            '        "TrackRowCellTileByteView*"'
        )
        assert expected in replay

    assert "types_declare_if_missing" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert (
        '        "select_track_tile_edge_variants",\n'
        '        "RegisterVariableSourceType",\n'
        '        28,\n'
        '        72,\n'
        '        "tile_cursor",\n'
        '        "TrackRowCellTileByteView*"'
        in replay
    )
    assert "TRACK_TILE_EDGE_USER_VAR_UPDATES" in replay
    assert (
        '        "promote_track_tiles_to_fringe_variants",\n'
        '        "RegisterVariableSourceType",\n'
        '        31,\n'
        '        72,\n'
        '        "cell_object_cursor",\n'
        '        "TrackRowCellObjectSlotView*"'
        in replay
    )
    assert "TRACK_TILE_PROMOTION_USER_VAR_UPDATES" in replay
    assert "TrackRowCell*" not in replay.split("TRACK_WARNING_USER_VAR_UPDATES", 1)[1]


def test_twister_path_replay_preserves_sample_and_facequad_lifetimes() -> None:
    replay = (BINJA_DIR / "sync_twister_path_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    for function_name in (
        "initialize_twister_path_template_pair",
        "initialize_twister2_path_template_pair",
    ):
        assert f'        "{function_name}",' in replay

    for index, storage, name, variable_type in (
        (746, 68, "primary_up", "Vec3*"),
        (866, 66, "primary_sample_cursor", "PathTemplateSample*"),
        (963, 68, "secondary_up", "Vec3*"),
        (1083, 66, "secondary_sample_cursor", "PathTemplateSample*"),
        (1470, 67, "primary_terminal_delta", "Vec3*"),
        (1559, 66, "secondary_terminal_delta", "Vec3*"),
        (1718, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (2128, 71, "face_first", "ObjectFaceQuad*"),
        (2307, 71, "face_second", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "TWISTER_PATH_USER_VAR_UPDATES" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert "(1803, 66" not in replay


def test_hump_dump_path_replay_preserves_only_clean_owner_lifetimes() -> None:
    replay = (BINJA_DIR / "sync_hump_dump_path_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    for function_name in (
        "initialize_hump_path_template_pair",
        "initialize_dump_path_template_pair",
    ):
        assert f'("{function_name}", ' in replay

    for index, storage, name, variable_type in (
        (850, 68, "primary_right", "Vec3*"),
        (970, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1021, 66, "secondary_right", "Vec3*"),
        (1139, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1483, 68, "primary_terminal_delta", "Vec3*"),
        (1572, 67, "secondary_terminal_delta", "Vec3*"),
        (1731, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (2141, 71, "face_first", "ObjectFaceQuad*"),
        (2320, 71, "face_second", "ObjectFaceQuad*"),
        (860, 68, "primary_right", "Vec3*"),
        (980, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1031, 66, "secondary_right", "Vec3*"),
        (1149, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1493, 68, "primary_terminal_delta", "Vec3*"),
        (1582, 67, "secondary_terminal_delta", "Vec3*"),
        (1741, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (2151, 71, "face_first", "ObjectFaceQuad*"),
        (2330, 71, "face_second", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "HUMP_DUMP_PATH_USER_VAR_UPDATES" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    for rejected_index in (892, 1063, 902, 1073):
        assert f"({rejected_index}, 66," not in replay

    health = json.loads(
        (Path(__file__).parents[1] / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    aggregate_addresses = {
        "bn_hump_path_full_owner_abi": (
            "0041d39e",
            "0041d449",
            "0041d620",
            "0041d667",
        ),
        "bn_dump_path_full_owner_abi": (
            "0041dda8",
            "0041de53",
            "0041e02a",
            "0041e071",
        ),
    }
    for check_name, addresses in aggregate_addresses.items():
        check = checks[check_name]
        regexes = check["required_regexes"]
        for address in addresses:
            matching_regex = next(
                pattern for pattern in regexes if pattern.startswith(address)
            )
            for component in (r"\.x =", r"\.y =", r"\.z ="):
                assert component in matching_regex
        assert "struct Vec3* primary_right" not in check["required_substrings"]
        assert (
            "struct Vec3* primary_terminal_delta"
            not in check["required_substrings"]
        )


def test_slalom_path_replay_preserves_shared_owner_lifetimes() -> None:
    replay = (BINJA_DIR / "sync_slalom_path_lifetimes.py").read_text(
        encoding="utf-8"
    )
    slalombig_scratch = (
        Path(__file__).parents[1]
        / "tools/match/scratches/initialize_slalombig_path_template_pair/scratch.cpp"
    ).read_text(encoding="utf-8")

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    for function_name in (
        "initialize_slalom_path_template_pair",
        "initialize_slalombig_path_template_pair",
    ):
        assert f'        "{function_name}",' in replay

    for index, storage, name, variable_type in (
        (811, 66, "primary_forward", "Vec3*"),
        (929, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1010, 68, "secondary_forward", "Vec3*"),
        (1130, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1504, 67, "primary_terminal_delta", "Vec3*"),
        (1593, 66, "secondary_terminal_delta", "Vec3*"),
        (1754, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (2163, 73, "face", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "SLALOM_PATH_USER_VAR_UPDATES" in replay
    assert "SLALOM_CONTROL_USER_VAR_UPDATES" in replay
    assert "SLALOM_CONTROL_STACK_LIFETIME_SPLITS" in replay
    assert "SLALOM_MESH_STACK_LIFETIME_SPLITS" in replay
    assert "SLALOM_FACE_REGISTER_LIFETIME_SPLITS" in replay
    assert "apply_split_user_var_updates(" in replay
    assert '"mlil_ssa", "StackVariableSourceType", 1728, 4' in replay
    assert '"mlil_ssa", "StackVariableSourceType", 1728, 8' in replay
    assert '"mlil_ssa", "StackVariableSourceType", 2093, 4' in replay
    assert '"mlil_ssa", "StackVariableSourceType", 2093, -72' in replay
    assert '"mlil_ssa", "StackVariableSourceType", 2140, -72' in replay
    for name, variable_type in (
        ("lead_sample_z", "float"),
        ("curve_segments_f", "float"),
        ("curve_phase", "float"),
        ("center_distance_a", "float"),
        ("segment_count_value", "int32_t"),
        ("lead_sample_index", "int32_t"),
        ("tail_sample_index", "int32_t"),
        ("tail_sample_z", "float"),
        ("curve_index", "int32_t"),
        ("center_distance_b", "float"),
        ("curve_sample_index", "int32_t"),
        ("curve_sample_z", "float"),
    ):
        assert f'"{name}"' in replay
        assert f'"{variable_type}"' in replay
    for name, variable_type in (
        ("mesh_facequads", "ObjectFaceQuad*"),
        ("mesh_vertices", "Vec3*"),
        ("mesh_column", "int32_t"),
        ("mesh_width_cells", "int32_t"),
        ("face_column_for_uv", "int32_t"),
        ("v0_index", "int32_t"),
        ("v1_index", "int32_t"),
        ("v0", "float"),
        ("v1", "float"),
        ("u1_index", "int32_t"),
        ("face_pass", "int32_t"),
        ("u0", "float"),
        ("u1", "float"),
        ("face_width_plus_one", "int32_t"),
    ):
        assert f'        "{name}",' in replay
        assert f'        "{variable_type}",' in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    for rejected_index in (853, 962, 1052, 1845):
        assert f"({rejected_index}, 66," not in replay
    assert "if (curve_index == 0)" in slalombig_scratch
    assert "if (current_index <= 4)" not in slalombig_scratch


def test_sweep_snake_path_replay_preserves_clean_owner_lifetimes() -> None:
    replay = (BINJA_DIR / "sync_sweep_snake_path_lifetimes.py").read_text(
        encoding="utf-8"
    )
    repo_root = Path(__file__).parents[1]
    sweep_scratch = (
        repo_root
        / "tools/match/scratches/initialize_sweep_path_template_pair/scratch.cpp"
    ).read_text(encoding="utf-8")
    snake_scratch = (
        repo_root
        / "tools/match/scratches/initialize_snake_path_template_pair/scratch.cpp"
    ).read_text(encoding="utf-8")
    health = json.loads(
        (
            repo_root / "analysis/decompile/health_checks.json"
        ).read_text(encoding="utf-8")
    )
    sweep_health = next(
        check
        for check in health["checks"]
        if check["name"] == "bn_sweep_path_full_owner_abi"
    )
    snake_health = next(
        check
        for check in health["checks"]
        if check["name"] == "bn_snake_path_full_owner_abi"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    for function_name in (
        "initialize_sweep_path_template_pair",
        "initialize_snake_path_template_pair",
    ):
        assert f'("{function_name}", ' in replay

    for index, storage, name, variable_type in (
        (726, 67, "primary_forward", "Vec3*"),
        (841, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
        (893, 67, "secondary_forward", "Vec3*"),
        (1008, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1352, 68, "primary_terminal_delta", "Vec3*"),
        (1441, 67, "secondary_terminal_delta", "Vec3*"),
        (1600, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (2010, 71, "face_first", "ObjectFaceQuad*"),
        (2189, 71, "face_second", "ObjectFaceQuad*"),
        (727, 68, "primary_right", "Vec3*"),
        (847, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
        (898, 66, "secondary_right", "Vec3*"),
        (1016, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1360, 68, "primary_terminal_delta", "Vec3*"),
        (1449, 67, "secondary_terminal_delta", "Vec3*"),
        (1608, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (2018, 71, "face_first", "ObjectFaceQuad*"),
        (2197, 71, "face_second", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "SWEEP_SNAKE_PATH_USER_VAR_UPDATES" in replay
    assert "SWEEP_SNAKE_CONTROL_USER_VAR_UPDATES" in replay
    assert "SWEEP_CONTROL_STACK_LIFETIME_SPLITS" in replay
    assert "SNAKE_CONTROL_STACK_LIFETIME_SPLITS" in replay
    assert "SWEEP_MESH_STACK_LIFETIME_SPLITS" in replay
    assert "SNAKE_MESH_STACK_LIFETIME_SPLITS" in replay
    assert "SWEEP_FACE_REGISTER_LIFETIME_SPLITS" in replay
    assert "SNAKE_FACE_REGISTER_LIFETIME_SPLITS" in replay
    assert "apply_split_user_var_updates(" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '0x90: ("center_x", "float")' in replay
    for name, variable_type in (
        ("lead_sample_z", "float"),
        ("curve_phase", "float"),
        ("lead_sample_index", "int32_t"),
        ("tail_sample_index", "int32_t"),
        ("tail_sample_z", "float"),
        ("curve_index", "int32_t"),
        ("curve_sample_index", "int32_t"),
        ("curve_sample_z", "float"),
        ("mesh_facequads", "ObjectFaceQuad*"),
        ("mesh_vertices", "Vec3*"),
        ("mesh_column", "int32_t"),
        ("mesh_width_cells", "int32_t"),
        ("face_column_for_uv", "int32_t"),
        ("v0_index", "int32_t"),
        ("v1_index", "int32_t"),
        ("v0", "float"),
        ("v1", "float"),
        ("u1_index", "int32_t"),
        ("face_pass", "int32_t"),
        ("u0", "float"),
        ("u1", "float"),
        ("face_width_plus_one_eax", "int32_t"),
        ("face_width_plus_one_ecx", "int32_t"),
        ("face_width_plus_one_edx", "int32_t"),
    ):
        assert f'        "{name}",' in replay
        assert f'        "{variable_type}",' in replay
    for definition in (
        '("0x422c47", "mlil_ssa", "StackVariableSourceType", 71, 8)',
        '("0x422d10", "mlil_ssa", "StackVariableSourceType", 272, 8)',
        '("0x422dd6", "mlil_ssa", "StackVariableSourceType", 470, 8)',
        '("0x423226", "mlil_ssa", "StackVariableSourceType", 1574, 8)',
        '("0x423226", "mlil_ssa", "StackVariableSourceType", 1574, -76)',
        '("0x42338a", "mlil_ssa", "StackVariableSourceType", 1930, 8)',
        '("0x4233b9", "mlil_ssa", "StackVariableSourceType", 1977, -72)',
        '("0x4234bd", "mlil", "RegisterVariableSourceType", 2237, 67)',
        '("0x4235c7", "mlil_ssa", "StackVariableSourceType", 71, 8)',
        '("0x423670", "mlil_ssa", "StackVariableSourceType", 240, 8)',
        '("0x423736", "mlil_ssa", "StackVariableSourceType", 438, 8)',
        '("0x423bae", "mlil_ssa", "StackVariableSourceType", 1582, 8)',
        '("0x423bae", "mlil_ssa", "StackVariableSourceType", 1582, -76)',
        '("0x423d12", "mlil_ssa", "StackVariableSourceType", 1938, 8)',
        '("0x423d41", "mlil_ssa", "StackVariableSourceType", 1985, -72)',
        '("0x423e45", "mlil", "RegisterVariableSourceType", 2245, 67)',
    ):
        assert definition in replay
    for rejected_face_pass_phi in (
        "0x423346",
        "0x423552",
        "0x42355e",
        "0x423cce",
        "0x423eda",
        "0x423ee6",
    ):
        assert rejected_face_pass_phi not in replay
    for rejected_index in (760, 1685, 769, 1693):
        assert f"({rejected_index}, 66," not in replay
    assert "if (curve_index == 0)" in sweep_scratch
    assert "if (curve_index == 0)" in snake_scratch
    assert "if (current_index <= 3)" not in sweep_scratch
    assert "if (i <= 6)" not in snake_scratch
    for health_check, tail_owner in (
        (sweep_health, "int32_t tail_sample_index = 0x1b"),
        (snake_health, "int32_t tail_sample_index = 0x18"),
    ):
        assert tail_owner in health_check["required_substrings"]
        for rendered_owner in (
            "int32_t lead_sample_index = 0",
            "int32_t curve_index = 0",
            "float curve_phase",
            "struct Vec3* mesh_vertices = vertices",
            "int32_t mesh_column = 0",
            "int32_t mesh_width_cells = width_cells",
            "int32_t face_column_for_uv = 0",
            "float v0 =",
            "float v1 =",
            "int32_t face_pass = 0",
            "float u0 =",
            "float u1 =",
            "int32_t face_width_plus_one_eax",
            "int32_t face_width_plus_one_ecx",
            "int32_t face_width_plus_one_edx",
        ):
            assert rendered_owner in health_check["required_substrings"]
        for stale_width_alias in (
            "width_cells_ = 0",
            "width_cells_ += 1",
            "width_cells_ = j",
        ):
            assert stale_width_alias in health_check["forbidden_substrings"]


def test_slalomdouble_p_path_replay_preserves_clean_owner_lifetimes() -> None:
    replay = (BINJA_DIR / "sync_slalomdouble_p_path_lifetimes.py").read_text(
        encoding="utf-8"
    )
    slalomdouble_scratch = (
        Path(__file__).parents[1]
        / "tools/match/scratches/initialize_slalomdouble_path_template_pair/scratch.cpp"
    ).read_text(encoding="utf-8")
    p_scratch = (
        Path(__file__).parents[1]
        / "tools/match/scratches/initialize_p_path_template_pair/scratch.cpp"
    ).read_text(encoding="utf-8")
    health = json.loads(
        (
            Path(__file__).parents[1]
            / "analysis/decompile/health_checks.json"
        ).read_text(encoding="utf-8")
    )
    slalomdouble_health = next(
        check
        for check in health["checks"]
        if check["name"] == "bn_slalomdouble_path_full_owner_abi"
    )
    p_health = next(
        check
        for check in health["checks"]
        if check["name"] == "bn_p_path_full_owner_abi"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    for function_name in (
        "initialize_slalomdouble_path_template_pair",
        "initialize_p_path_template_pair",
    ):
        assert f'"{function_name}"' in replay

    for index, storage, name, variable_type in (
        (791, 67, "primary_forward", "Vec3*"),
        (906, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
        (987, 68, "secondary_forward", "Vec3*"),
        (1107, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1481, 67, "primary_terminal_delta", "Vec3*"),
        (1570, 66, "secondary_terminal_delta", "Vec3*"),
        (1729, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (2129, 73, "face", "ObjectFaceQuad*"),
        (784, 68, "primary_forward", "Vec3*"),
        (904, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
        (955, 66, "secondary_forward", "Vec3*"),
        (1073, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1412, 68, "primary_terminal_delta", "Vec3*"),
        (1501, 67, "secondary_terminal_delta", "Vec3*"),
        (1660, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (2070, 71, "face_first", "ObjectFaceQuad*"),
        (2249, 71, "face_second", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "SLALOMDOUBLE_P_PATH_USER_VAR_UPDATES" in replay
    assert "SLALOMDOUBLE_CONTROL_USER_VAR_UPDATES" in replay
    assert "SLALOMDOUBLE_CONTROL_STACK_LIFETIME_SPLITS" in replay
    assert "SLALOMDOUBLE_MESH_STACK_LIFETIME_SPLITS" in replay
    assert "SLALOMDOUBLE_FACE_REGISTER_LIFETIME_SPLITS" in replay
    assert "P_CONTROL_LIFETIME_SPLITS" in replay
    assert "P_MESH_LIFETIME_SPLITS" in replay
    assert "P_FACE_REGISTER_LIFETIME_SPLITS" in replay
    assert "SLALOMDOUBLE_P_SPLIT_LIFETIME_GROUPS" in replay
    assert "apply_split_user_var_updates(" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    for name, variable_type in (
        ("lead_sample_z", "float"),
        ("curve_phase", "float"),
        ("lead_sample_index", "int32_t"),
        ("tail_sample_index", "int32_t"),
        ("tail_sample_z", "float"),
        ("curve_index", "int32_t"),
        ("center_distance_a", "float"),
        ("center_distance_b", "float"),
        ("curve_sample_index", "int32_t"),
        ("curve_sample_z", "float"),
        ("mesh_facequads", "ObjectFaceQuad*"),
        ("mesh_vertices", "Vec3*"),
        ("mesh_column", "int32_t"),
        ("mesh_width_cells", "int32_t"),
        ("face_column_for_uv", "int32_t"),
        ("v0_index", "int32_t"),
        ("v1_index", "int32_t"),
        ("v0", "float"),
        ("v1", "float"),
        ("u1_index", "int32_t"),
        ("face_pass", "int32_t"),
        ("u0", "float"),
        ("u1", "float"),
        ("face_width_plus_one_ecx", "int32_t"),
        ("face_width_plus_one_edx", "int32_t"),
        ("sample_count", "int32_t"),
        ("last_sample_index", "int32_t"),
        ("terminal_sample_z", "float"),
        ("curve_segments_f", "float"),
        ("face_column", "int32_t"),
        ("face_width_plus_one_eax", "int32_t"),
    ):
        assert f'        "{name}",' in replay
        assert f'        "{variable_type}",' in replay
    for definition in (
        '("0x425097", "mlil_ssa", "StackVariableSourceType", 71, 8)',
        '("0x425151", "mlil_ssa", "StackVariableSourceType", 257, 8)',
        '("0x42520a", "mlil_ssa", "StackVariableSourceType", 442, 8)',
        '("0x425241", "mlil_ssa", "StackVariableSourceType", 497, -72)',
        '("0x4256f7", "mlil_ssa", "StackVariableSourceType", 1703, 8)',
        '("0x4256f7", "mlil_ssa", "StackVariableSourceType", 1703, -76)',
        '("0x42585b", "mlil_ssa", "StackVariableSourceType", 2059, 8)',
        '("0x42588a", "mlil_ssa", "StackVariableSourceType", 2106, -72)',
        '("0x425bc0", "mlil", "RegisterVariableSourceType", 384, 71)',
        '("0x425bf5", "mlil_ssa", "RegisterVariableSourceType", 437, 71)',
        '("0x425bf5", "mlil_ssa", "StackVariableSourceType", 437, 16)',
        '("0x4260a2", "mlil_ssa", "RegisterVariableSourceType", 1634, 73)',
        '("0x4260a2", "mlil_ssa", "StackVariableSourceType", 1634, 8)',
        '("0x426206", "mlil_ssa", "RegisterVariableSourceType", 1990, 73)',
        '("0x426206", "mlil_ssa", "StackVariableSourceType", 1990, 8)',
        '("0x426235", "mlil_ssa", "RegisterVariableSourceType", 2037, 67)',
        '("0x426235", "mlil_ssa", "StackVariableSourceType", 2037, 4)',
    ):
        assert definition in replay
    for rejected_face_pass_phi in (
        "0x425817",
        "0x42585b\", \"mlil_ssa\", \"StackVariableSourceType\", 2059, -72",
        "0x425a0e",
    ):
        assert rejected_face_pass_phi not in replay
    for rejected_index in (825, 939, 1745, 1814):
        assert f"({rejected_index}, 66," not in replay
    assert slalomdouble_scratch.count("if (curve_index == 0)") == 2
    assert "if (i <= 4)" not in slalomdouble_scratch
    assert "int curve_index = 0" in p_scratch
    assert "float angle = (float)curve_index" in p_scratch
    assert "int face_index;" in p_scratch
    assert "for (face_index = 0; face_index < 2; ++face_index)" in p_scratch
    for rendered_owner in (
        "int32_t lead_sample_index = 0",
        "int32_t tail_sample_index = 0x42",
        "int32_t curve_index = 0",
        "float curve_phase",
        "float center_distance_a",
        "struct Vec3* mesh_vertices",
        "int32_t mesh_column = 0",
        "int32_t mesh_width_cells = width_cells",
        "int32_t face_column_for_uv = 0",
        "float v0",
        "float v1",
        "int32_t face_pass = 0",
        "float u0",
        "float u1",
        "struct ObjectFaceQuad* face = &facequads[",
        "int32_t face_width_plus_one_ecx",
        "int32_t face_width_plus_one_edx",
    ):
        assert rendered_owner in slalomdouble_health["required_substrings"]
    for stale_width_alias in (
        "width_cells_ = 0",
        "width_cells_ += 1",
        "width_cells_ = j",
    ):
        assert stale_width_alias in slalomdouble_health["forbidden_substrings"]

    for rendered_owner in (
        "int32_t curve_index = 0",
        "float curve_phase =",
        "struct Vec3* mesh_vertices = vertices",
        "struct ObjectFaceQuad* facequads = object->facequads",
        "int32_t mesh_column = 0",
        "int32_t mesh_width_cells = width_cells",
        "int32_t face_column = 0",
        "float v0 =",
        "float v1 =",
        "int32_t face_pass = 0",
        "float u0 =",
        "float u1 =",
        "int32_t face_width_plus_one_eax",
        "int32_t face_width_plus_one_ecx",
        "int32_t face_width_plus_one_edx",
    ):
        assert rendered_owner in p_health["required_substrings"]
    for stale_argument_alias in (
        "start_x = 0f",
        "start_x = vertices",
        "width_cells_ = object->facequads",
        "scale_arg = 0f",
        "curve_segments = width_cells",
        "variant = 0",
        "int32_t j = 0",
    ):
        assert stale_argument_alias in p_health["forbidden_substrings"]



def test_supertramp_start_path_replay_preserves_mesh_owner_lifetimes() -> None:
    replay = (BINJA_DIR / "sync_supertramp_start_path_lifetimes.py").read_text(
        encoding="utf-8"
    )
    start_scratch = (
        Path(__file__).parents[1]
        / "tools/match/scratches/initialize_start_path_template_pair/scratch.cpp"
    ).read_text(encoding="utf-8")

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    for function_name in (
        "initialize_supertramp_path_template_pair",
        "initialize_start_path_template_pair",
    ):
        assert f'("{function_name}", ' in replay

    for index, storage, name, variable_type in (
        (187, 66, "primary_seed_sample", "PathTemplateSample*"),
        (637, 67, "primary_right", "Vec3*"),
        (744, 66, "secondary_right", "Vec3*"),
        (772, 66, "secondary_curve_sample", "PathTemplateSample*"),
        (1185, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1268, 67, "vertex", "Vec3*"),
        (1499, 71, "face_first", "ObjectFaceQuad*"),
        (1696, 71, "face_second", "ObjectFaceQuad*"),
        (660, 66, "primary_curve_sample", "PathTemplateSample*"),
        (831, 66, "primary_right", "Vec3*"),
        (949, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1001, 67, "secondary_right", "Vec3*"),
        (1116, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1517, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1596, 67, "vertex", "Vec3*"),
        (1820, 71, "face_first", "ObjectFaceQuad*"),
        (1988, 71, "face_second", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "SUPERTRAMP_START_PATH_USER_VAR_UPDATES" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '0x90: ("center_x", "float")' in replay
    assert "(1035, 66," not in replay
    assert "if (i <= 5)" in start_scratch
    assert "if (curve_index == 0)" not in start_scratch


def test_turnover_family_path_replay_preserves_mesh_owner_lifetimes() -> None:
    replay = (BINJA_DIR / "sync_turnover_family_path_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    for function_name in (
        "initialize_turnover_path_template_pair",
        "initialize_turnoverdouble_path_template_pair",
        "initialize_turnunder_path_template_pair",
    ):
        assert f'"{function_name}"' in replay

    for index, storage, name, variable_type in (
        (191, 66, "primary_seed_sample", "PathTemplateSample*"),
        (858, 67, "primary_up", "Vec3*"),
        (1044, 66, "secondary_position", "Vec3*"),
        (1358, 67, "primary_terminal_delta", "Vec3*"),
        (1446, 67, "secondary_terminal_delta", "Vec3*"),
        (1609, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1671, 66, "vertex", "Vec3*"),
        (2017, 69, "face_first", "ObjectFaceQuad*"),
        (2195, 69, "face_second", "ObjectFaceQuad*"),
        (191, 66, "primary_seed_sample", "PathTemplateSample*"),
        (892, 67, "primary_up", "Vec3*"),
        (1075, 66, "secondary_position", "Vec3*"),
        (1389, 67, "primary_terminal_delta", "Vec3*"),
        (1477, 67, "secondary_terminal_delta", "Vec3*"),
        (1640, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1702, 66, "vertex", "Vec3*"),
        (2048, 69, "face_first", "ObjectFaceQuad*"),
        (2226, 69, "face_second", "ObjectFaceQuad*"),
        (195, 66, "primary_seed_sample", "PathTemplateSample*"),
        (902, 66, "primary_up", "Vec3*"),
        (1098, 66, "secondary_position", "Vec3*"),
        (1412, 67, "primary_terminal_delta", "Vec3*"),
        (1500, 67, "secondary_terminal_delta", "Vec3*"),
        (1663, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1725, 66, "vertex", "Vec3*"),
        (2071, 69, "face_first", "ObjectFaceQuad*"),
        (2249, 69, "face_second", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "TURNOVER_FAMILY_PATH_USER_VAR_UPDATES" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '0x80: ("delta_dir_to_next", "Vec3")' in replay
    assert '0x8C: ("delta_length", "float")' in replay
    assert '0x90: ("center_x", "float")' in replay
    for rejected_index in (884, 918):
        assert f"({rejected_index}, 66," not in replay


def test_wibble_invert_halfpipe_replay_preserves_mesh_owner_lifetimes() -> None:
    replay = (
        BINJA_DIR / "sync_wibble_invert_halfpipe_path_lifetimes.py"
    ).read_text(encoding="utf-8")

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    for function_name in (
        "initialize_wibble_path_template_pair",
        "initialize_invert_path_template_pair",
        "initialize_halfpipe_path_template_pair",
    ):
        assert f'"{function_name}"' in replay

    for index, storage, name, variable_type in (
        (134, 66, "primary_seed_sample", "PathTemplateSample*"),
        (640, 68, "primary_up", "Vec3*"),
        (745, 67, "primary_right", "Vec3*"),
        (830, 66, "secondary_position", "Vec3*"),
        (1139, 67, "primary_terminal_delta", "Vec3*"),
        (1228, 66, "secondary_terminal_delta", "Vec3*"),
        (1389, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1451, 66, "vertex", "Vec3*"),
        (1797, 73, "face_first", "ObjectFaceQuad*"),
        (1975, 73, "face_second", "ObjectFaceQuad*"),
        (609, 68, "primary_up", "Vec3*"),
        (714, 67, "primary_right", "Vec3*"),
        (799, 66, "secondary_position", "Vec3*"),
        (1108, 67, "primary_terminal_delta", "Vec3*"),
        (1197, 66, "secondary_terminal_delta", "Vec3*"),
        (1358, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1420, 66, "vertex", "Vec3*"),
        (1766, 73, "face_first", "ObjectFaceQuad*"),
        (1944, 73, "face_second", "ObjectFaceQuad*"),
        (240, 66, "primary_leadin_sample", "PathTemplateSample*"),
        (873, 67, "primary_up", "Vec3*"),
        (974, 67, "primary_right", "Vec3*"),
        (1012, 66, "primary_up_reloaded", "Vec3*"),
        (1049, 66, "secondary_position", "Vec3*"),
        (1367, 67, "primary_terminal_delta", "Vec3*"),
        (1456, 66, "secondary_terminal_delta", "Vec3*"),
        (1626, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1692, 67, "vertex", "Vec3*"),
        (2167, 73, "face_first", "ObjectFaceQuad*"),
        (2351, 73, "face_second", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "WIBBLE_INVERT_HALFPIPE_PATH_USER_VAR_UPDATES" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '0x80: ("delta_dir_to_next", "Vec3")' in replay
    assert '0x8C: ("delta_length", "float")' in replay
    assert '0x90: ("center_x", "float")' in replay
    assert "(896, 66," not in replay

    health = json.loads(
        (Path(__file__).parents[1] / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    check = checks["bn_halfpipe_path_full_owner_abi"]
    regexes = check["required_regexes"]
    for address in ("00429e9a", "0042a09c", "0042a0e3"):
        matching_regex = next(
            pattern for pattern in regexes if pattern.startswith(address)
        )
        for component in (r"\.x =", r"\.y =", r"\.z ="):
            assert component in matching_regex
    for rendered_alias in (
        "struct Vec3* primary_up",
        "struct Vec3* primary_terminal_delta",
        "struct Vec3* secondary_terminal_delta",
    ):
        assert rendered_alias not in check["required_substrings"]


def test_toad_hill_sbend_replay_preserves_mesh_owner_lifetimes() -> None:
    replay = (BINJA_DIR / "sync_toad_hill_sbend_path_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    for function_name in (
        "initialize_toad_path_template_pair",
        "initialize_hill_valley_path_template_pair",
        "initialize_sbend_path_template_pair",
    ):
        assert f'"{function_name}"' in replay

    for source_type, index, storage, name, variable_type in (
        ("StackVariableSourceType", 61, -84, "lead_count", "int32_t"),
        ("StackVariableSourceType", 45, -80, "start_x", "float"),
        ("StackVariableSourceType", 65, -76, "tail_count", "int32_t"),
        ("StackVariableSourceType", 53, -72, "turn_sign", "float"),
        ("StackVariableSourceType", 56, -72, "steps", "int32_t"),
    ):
        assert (
            f'("{source_type}", {index}, {storage}, "{name}", "{variable_type}"),'
            in replay
        )

    assert (
        '("0x42cfd1", "mlil", "RegisterVariableSourceType", 993, 67),'
        in replay
    )
    assert (
        '("0x42cc7f", "mlil", "RegisterVariableSourceType", 143, 67),'
        in replay
    )
    assert '"lead_count_bound"' in replay
    assert '"primary_sample_bank"' in replay
    assert 'variable_type="PathTemplateSample*"' in replay

    for address, index, storage, name, variable_type in (
        ("0x42d59c", 44, 4, "steps", "int32_t"),
        ("0x42d664", 244, 16, "last_index", "int32_t"),
        ("0x42d6ef", 383, 16, "last_z", "float"),
        ("0x42d79f", 559, 16, "phase", "float"),
        ("0x42db8a", 1562, 4, "mesh_vertices", "Vec3*"),
        ("0x42dba1", 1585, 16, "mesh_column", "int32_t"),
        ("0x42dba5", 1589, 8, "mesh_width_cells", "int32_t"),
        ("0x42dd01", 1937, 8, "v0", "float"),
        ("0x42dd0f", 1951, 12, "v1", "float"),
        ("0x42dd2a", 1978, 16, "u0", "float"),
        ("0x42dd38", 1992, 4, "u1", "float"),
        ("0x42df42", 66, 4, "segment_count_value", "int32_t"),
        ("0x42dfdb", 219, 16, "sample_index", "int32_t"),
        ("0x42e072", 370, 4, "phase", "float"),
        ("0x42e3a7", 1191, 4, "mesh_vertices", "Vec3*"),
        ("0x42e3ba", 1210, 16, "mesh_column", "int32_t"),
        ("0x42e3be", 1214, 8, "mesh_width_cells", "int32_t"),
        ("0x42e518", 1560, 8, "v0", "float"),
        ("0x42e526", 1574, 12, "v1", "float"),
        ("0x42e541", 1601, 16, "u0", "float"),
        ("0x42e54f", 1615, 4, "u1", "float"),
    ):
        definition = (
            f'("{address}", "mlil", "StackVariableSourceType", '
            f"{index}, {storage})"
        )
        assert definition in replay
        assert f'        "{name}",\n        "{variable_type}",' in replay

    for first, second in (
        ("0x42d726", "0x42d9c7"),
        ("0x42dba1", "0x42dca6"),
        ("0x42dba5", "0x42dca0"),
        ("0x42dcd6", "0x42dece"),
        ("0x42dfdb", "0x42e1dd"),
        ("0x42e3ba", "0x42e4bd"),
        ("0x42e3be", "0x42e4b7"),
        ("0x42e4ed", "0x42e6e3"),
    ):
        assert first in replay
        assert second in replay

    for index, storage, name, variable_type in (
        (949, 67, "primary_right", "Vec3*"),
        (1036, 66, "secondary_position", "Vec3*"),
        (1351, 67, "primary_terminal_delta", "Vec3*"),
        (1440, 66, "secondary_terminal_delta", "Vec3*"),
        (1601, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1663, 66, "vertex", "Vec3*"),
        (2009, 73, "face_first", "ObjectFaceQuad*"),
        (2187, 73, "face_second", "ObjectFaceQuad*"),
        (173, 66, "primary_seed_sample", "PathTemplateSample*"),
        (753, 66, "primary_right", "Vec3*"),
        (923, 67, "secondary_right", "Vec3*"),
        (1377, 68, "primary_terminal_delta", "Vec3*"),
        (1466, 67, "secondary_terminal_delta", "Vec3*"),
        (1625, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1687, 66, "vertex", "Vec3*"),
        (2035, 71, "face_first", "ObjectFaceQuad*"),
        (2214, 71, "face_second", "ObjectFaceQuad*"),
        (179, 66, "primary_seed_sample", "PathTemplateSample*"),
        (499, 68, "primary_up", "Vec3*"),
        (603, 66, "primary_right", "Vec3*"),
        (684, 66, "secondary_position", "Vec3*"),
        (999, 68, "primary_terminal_delta", "Vec3*"),
        (1087, 68, "secondary_terminal_delta", "Vec3*"),
        (1250, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1312, 66, "vertex", "Vec3*"),
        (1658, 69, "face_first", "ObjectFaceQuad*"),
        (1836, 69, "face_second", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "TOAD_HILL_SBEND_PATH_USER_VAR_UPDATES" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_split_away_user_var_update" in replay
    assert "apply_split_user_var_update" in replay
    assert "apply_user_var_updates" in replay
    assert "for function_name, split_specs in (" in replay
    assert '0x80: ("delta_dir_to_next", "Vec3")' in replay
    assert '0x8C: ("delta_length", "float")' in replay
    assert '0x90: ("center_x", "float")' in replay
    for rejected_index in (798, 965, 533):
        assert f"({rejected_index}, 66," not in replay

    health = json.loads(
        (Path(__file__).parents[1] / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    for check_name in (
        "bn_hill_valley_path_full_owner_abi",
        "bn_sbend_path_full_owner_abi",
    ):
        check = checks[check_name]
        for owner in (
            "float phase =",
            "struct Vec3* mesh_vertices = vertices",
            "int32_t mesh_column = 0",
            "int32_t mesh_width_cells = width_cells",
            "int32_t face_column_for_uv = 0",
            "float v0 =",
            "float v1 =",
            "float u0 =",
            "float u1 =",
        ):
            assert owner in check["required_substrings"]
        for leaked_home in (
            "centered.d =",
            "width_cells_ = vertices",
            "height = width_cells",
        ):
            assert leaked_home in check["forbidden_substrings"]


def test_loop_family_replay_preserves_control_and_mesh_owner_lifetimes() -> None:
    replay = (BINJA_DIR / "sync_loop_family_path_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    for function_name in (
        "initialize_looptheloop_path_template_pair",
        "initialize_looptheloopw_path_template_pair",
        "initialize_loopout_path_template_pair",
    ):
        assert f'"{function_name}"' in replay

    for index, storage, name, variable_type in (
        (1047, 66, "primary_right", "Vec3*"),
        (1122, 66, "primary_right_reloaded", "Vec3*"),
        (1152, 68, "secondary_right", "Vec3*"),
        (1225, 66, "secondary_right_reloaded", "Vec3*"),
        (1524, 68, "primary_terminal_delta", "Vec3*"),
        (1613, 67, "secondary_terminal_delta", "Vec3*"),
        (1778, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1844, 67, "vertex", "Vec3*"),
        (1966, 68, "terminal_vertex", "Vec3*"),
        (2210, 71, "face_first", "ObjectFaceQuad*"),
        (2389, 71, "face_second", "ObjectFaceQuad*"),
        (1111, 66, "primary_right", "Vec3*"),
        (1181, 66, "primary_right_reloaded", "Vec3*"),
        (1224, 68, "secondary_right", "Vec3*"),
        (1301, 66, "secondary_right_reloaded", "Vec3*"),
        (1613, 68, "primary_terminal_delta", "Vec3*"),
        (1702, 67, "secondary_terminal_delta", "Vec3*"),
        (1867, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1933, 67, "vertex", "Vec3*"),
        (2055, 68, "terminal_vertex", "Vec3*"),
        (2299, 71, "face_first", "ObjectFaceQuad*"),
        (2484, 71, "face_second", "ObjectFaceQuad*"),
        (1025, 67, "primary_right", "Vec3*"),
        (1112, 66, "primary_right_reloaded", "Vec3*"),
        (1141, 66, "secondary_right", "Vec3*"),
        (1215, 66, "secondary_right_reloaded", "Vec3*"),
        (1515, 68, "primary_terminal_delta", "Vec3*"),
        (1604, 67, "secondary_terminal_delta", "Vec3*"),
        (1769, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1835, 67, "vertex", "Vec3*"),
        (1957, 68, "terminal_vertex", "Vec3*"),
        (2201, 71, "face_first", "ObjectFaceQuad*"),
        (2380, 71, "face_second", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "LOOP_FAMILY_PATH_USER_VAR_UPDATES" in replay
    assert "LOOPTHELOOP_CONTROL_USER_VAR_UPDATES" in replay
    assert "LOOPTHELOOP_CONTROL_LIFETIME_SPLITS" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_split_user_var_updates" in replay
    assert "apply_user_var_updates" in replay
    assert '0x80: ("delta_dir_to_next", "Vec3")' in replay
    assert '0x8C: ("delta_length", "float")' in replay
    assert '0x90: ("center_x", "float")' in replay

    for index, storage, name, variable_type in (
        (98, -72, "curve_count_f", "float"),
        (137, -76, "lead_sample_z", "float"),
        (711, -76, "secondary_radius", "float"),
        (764, -68, "angle", "float"),
    ):
        assert (
            f'        {index},\n'
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        ) in replay

    for name, variable_type in (
        ("loop_wiggle", "float"),
        ("curve_count", "int32_t"),
        ("total_segment_count", "int32_t"),
        ("loop_radius", "float"),
        ("lead_sample_index", "int32_t"),
        ("lead_sample_offset", "int32_t"),
        ("tail_index", "int32_t"),
        ("tail_sample_z", "float"),
        ("tail_sample_offset", "int32_t"),
        ("terminal_sample_offset", "int32_t"),
        ("curve_index", "int32_t"),
        ("curve_sample_offset", "int32_t"),
        ("delta_index", "int32_t"),
        ("delta_sample_offset", "int32_t"),
    ):
        assert f'        "{name}",\n        "{variable_type}",' in replay

    for address, view, source_type, index, storage in (
        ("0x41b105", "mlil", "StackVariableSourceType", 21, -84),
        ("0x41b116", "mlil_ssa", "StackVariableSourceType", 38, -84),
        ("0x41b12a", "mlil", "RegisterVariableSourceType", 58, 66),
        ("0x41b12f", "mlil", "StackVariableSourceType", 63, -80),
        ("0x41b15c", "mlil", "StackVariableSourceType", 108, 4),
        ("0x41b172", "mlil_ssa", "StackVariableSourceType", 130, 8),
        ("0x41b172", "mlil_ssa", "RegisterVariableSourceType", 130, 73),
        ("0x41b274", "mlil_ssa", "RegisterVariableSourceType", 388, 69),
        ("0x41b274", "mlil_ssa", "StackVariableSourceType", 388, 8),
        ("0x41b274", "mlil_ssa", "RegisterVariableSourceType", 388, 73),
        ("0x41b3d8", "mlil_ssa", "RegisterVariableSourceType", 744, 67),
        ("0x41b3d8", "mlil_ssa", "StackVariableSourceType", 744, 8),
        ("0x41b3d8", "mlil_ssa", "RegisterVariableSourceType", 744, 73),
        ("0x41b5f4", "mlil_ssa", "RegisterVariableSourceType", 1284, 69),
        ("0x41b5f4", "mlil_ssa", "RegisterVariableSourceType", 1284, 73),
    ):
        assert (
            f'("{address}", "{view}", "{source_type}", {index}, {storage})'
            in replay
        )

    health = json.loads(
        (Path(__file__).parents[1] / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks = {check["name"]: check for check in health["checks"]}
    aggregate_addresses = {
        "bn_looptheloop_path_full_owner_abi": (
            "0041b51b",
            "0041b57f",
            "0041b709",
            "0041b750",
            "0041b838",
            "0041b8b8",
        ),
        "bn_looptheloopw_path_full_owner_abi": (
            "0041bfa6",
            "0041c01b",
            "0041c1b2",
            "0041c1f9",
            "0041c2e1",
            "0041c361",
        ),
        "bn_loopout_path_full_owner_abi": (
            "0041ca09",
            "0041ca74",
            "0041cc00",
            "0041cc47",
            "0041cd2f",
            "0041cdaf",
        ),
    }
    for check_name, addresses in aggregate_addresses.items():
        check = checks[check_name]
        regexes = check["required_regexes"]
        for address in addresses:
            matching_regex = next(
                pattern for pattern in regexes if pattern.startswith(address)
            )
            for component in (r"\.x =", r"\.y =", r"\.z ="):
                assert component in matching_regex
        assert "struct Vec3* vertex" not in check["required_substrings"]


def test_dip_screw_replay_preserves_mesh_owner_lifetimes() -> None:
    replay = (BINJA_DIR / "sync_dip_screw_path_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    for function_name in (
        "initialize_dip_path_template_pair",
        "initialize_screw_path_template_pair",
    ):
        assert f'"{function_name}"' in replay

    for index, storage, name, variable_type in (
        (679, 66, "primary_right", "Vec3*"),
        (849, 67, "secondary_right", "Vec3*"),
        (1303, 68, "primary_terminal_delta", "Vec3*"),
        (1392, 67, "secondary_terminal_delta", "Vec3*"),
        (1553, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1619, 67, "vertex", "Vec3*"),
        (1740, 67, "terminal_vertex", "Vec3*"),
        (1976, 71, "face_first", "ObjectFaceQuad*"),
        (2155, 71, "face_second", "ObjectFaceQuad*"),
        (797, 67, "primary_up", "Vec3*"),
        (981, 68, "secondary_up", "Vec3*"),
        (1446, 68, "primary_terminal_delta", "Vec3*"),
        (1535, 67, "secondary_terminal_delta", "Vec3*"),
        (1694, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1756, 66, "vertex", "Vec3*"),
        (2094, 73, "face", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "DIP_SCREW_PATH_USER_VAR_UPDATES" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '0x80: ("delta_dir_to_next", "Vec3")' in replay
    assert '0x8C: ("delta_length", "float")' in replay
    assert '0x90: ("center_x", "float")' in replay
    for rejected_index in (724, 891, 842, 1061):
        assert f"({rejected_index}, 66," not in replay


def test_curve_family_aggregate_health_stays_address_anchored() -> None:
    health = json.loads(
        (
            Path(__file__).parents[1]
            / "analysis/decompile/health_checks.json"
        ).read_text(encoding="utf-8")
    )
    checks = {check["name"]: check for check in health["checks"]}
    aggregate_addresses = {
        "bn_dip_path_full_owner_abi": (
            "0041e703",
            "0041e7ad",
            "0041e97c",
            "0041e9c3",
            "0041eaa7",
            "0041eb28",
        ),
        "bn_screw_path_full_owner_abi": (
            "0041f0dc",
            "0041f194",
            "0041f36b",
            "0041f3b2",
        ),
        "bn_slalom_path_full_owner_abi": (
            "0041faa7",
            "0041fb6e",
            "0041fd65",
            "0041fdac",
        ),
        "bn_slalombig_path_full_owner_abi": (
            "00422537",
            "004225fe",
            "004227f5",
            "0042283c",
        ),
        "bn_sweep_path_full_owner_abi": (
            "00422ef2",
            "00422f99",
            "0042316d",
            "004231b4",
        ),
        "bn_snake_path_full_owner_abi": (
            "00423873",
            "0042391e",
            "00423af5",
            "00423b3c",
        ),
        "bn_slalomdouble_path_full_owner_abi": (
            "00425383",
            "00425447",
            "0042563e",
            "00425685",
        ),
        "bn_p_path_full_owner_abi": (
            "00425d6c",
            "00425e17",
            "00425fe9",
            "00426030",
        ),
    }
    for check_name, addresses in aggregate_addresses.items():
        check = checks[check_name]
        regexes = check["required_regexes"]
        assert len(regexes) == len(addresses)
        for address in addresses:
            matching_regex = next(
                pattern for pattern in regexes if pattern.startswith(address)
            )
            for component in (r"\.x =", r"\.y =", r"\.z ="):
                assert component in matching_regex
        for rendered_alias in (
            "struct Vec3* primary_terminal_delta",
            "struct Vec3* secondary_terminal_delta",
        ):
            assert rendered_alias not in check["required_substrings"]

    for check_name, rendered_aliases in {
        "bn_dip_path_full_owner_abi": (
            "struct Vec3* primary_right",
            "struct Vec3* secondary_right",
            "struct Vec3* vertex",
            "struct Vec3* terminal_vertex",
        ),
        "bn_screw_path_full_owner_abi": (
            "struct Vec3* primary_up",
            "struct Vec3* secondary_up",
        ),
        "bn_slalom_path_full_owner_abi": (
            "struct Vec3* primary_forward",
            "struct Vec3* secondary_forward",
        ),
        "bn_slalombig_path_full_owner_abi": (
            "struct Vec3* primary_forward",
            "struct Vec3* secondary_forward",
        ),
        "bn_sweep_path_full_owner_abi": (
            "struct Vec3* primary_forward",
            "struct Vec3* secondary_forward",
        ),
        "bn_snake_path_full_owner_abi": (
            "struct Vec3* primary_right",
            "struct Vec3* secondary_right",
        ),
        "bn_slalomdouble_path_full_owner_abi": (
            "struct Vec3* primary_forward",
            "struct Vec3* secondary_forward",
        ),
        "bn_p_path_full_owner_abi": (
            "struct Vec3* primary_forward",
            "struct Vec3* secondary_forward",
        ),
    }.items():
        for rendered_alias in rendered_aliases:
            assert (
                rendered_alias not in checks[check_name]["required_substrings"]
            )


def test_transition_family_aggregate_health_stays_address_anchored() -> None:
    health = json.loads(
        (
            Path(__file__).parents[1]
            / "analysis/decompile/health_checks.json"
        ).read_text(encoding="utf-8")
    )
    checks = {check["name"]: check for check in health["checks"]}
    aggregate_addresses = {
        "bn_start_path_full_owner_abi": (
            "0042675b",
            "00426805",
            "00426a50",
        ),
        "bn_turnover_path_full_owner_abi": (
            "0042701e",
            "0042722b",
            "0042726b",
        ),
        "bn_turnoverdouble_path_full_owner_abi": (
            "004279d0",
            "00427bda",
            "00427c1a",
        ),
        "bn_turnunder_path_full_owner_abi": (
            "0042837a",
            "00428591",
            "004285d1",
        ),
    }
    for check_name, addresses in aggregate_addresses.items():
        check = checks[check_name]
        regexes = check["required_regexes"]
        assert len(regexes) == len(addresses)
        for address in addresses:
            matching_regex = next(
                pattern for pattern in regexes if pattern.startswith(address)
            )
            for component in (r"\.x =", r"\.y =", r"\.z ="):
                assert component in matching_regex

    for check_name, rendered_aliases in {
        "bn_start_path_full_owner_abi": (
            "struct Vec3* primary_right",
            "struct Vec3* secondary_right",
            "struct Vec3* vertex",
        ),
        "bn_turnover_path_full_owner_abi": (
            "struct Vec3* primary_up",
            "struct Vec3* primary_terminal_delta",
            "struct Vec3* secondary_terminal_delta",
        ),
        "bn_turnoverdouble_path_full_owner_abi": (
            "struct Vec3* primary_up",
            "struct Vec3* primary_terminal_delta",
            "struct Vec3* secondary_terminal_delta",
        ),
        "bn_turnunder_path_full_owner_abi": (
            "struct Vec3* primary_up",
            "struct Vec3* primary_terminal_delta",
            "struct Vec3* secondary_terminal_delta",
        ),
    }.items():
        for rendered_alias in rendered_aliases:
            assert (
                rendered_alias not in checks[check_name]["required_substrings"]
            )


def test_wibble_twister_aggregate_health_stays_address_anchored() -> None:
    health = json.loads(
        (
            Path(__file__).parents[1]
            / "analysis/decompile/health_checks.json"
        ).read_text(encoding="utf-8")
    )
    checks = {check["name"]: check for check in health["checks"]}
    aggregate_addresses = {
        "bn_wibble_path_full_owner_abi": (
            "00428c34",
            "00428e38",
            "00428e7f",
        ),
        "bn_invert_path_full_owner_abi": (
            "004294c5",
            "004296c9",
            "00429710",
        ),
        "bn_twister_path_full_owner_abi": (
            "0042a846",
            "0042a91f",
            "0042ab23",
        ),
        "bn_twister2_path_full_owner_abi": (
            "0042b236",
            "0042b30f",
            "0042b513",
        ),
    }
    for check_name, addresses in aggregate_addresses.items():
        check = checks[check_name]
        regexes = check["required_regexes"]
        assert len(regexes) == len(addresses)
        for address in addresses:
            matching_regex = next(
                pattern for pattern in regexes if pattern.startswith(address)
            )
            for component in (r"\.x =", r"\.y =", r"\.z ="):
                assert component in matching_regex

    for check_name, rendered_aliases in {
        "bn_wibble_path_full_owner_abi": (
            "struct Vec3* primary_up",
            "struct Vec3* primary_terminal_delta",
            "struct Vec3* secondary_terminal_delta",
        ),
        "bn_invert_path_full_owner_abi": (
            "struct Vec3* primary_up",
            "struct Vec3* primary_terminal_delta",
            "struct Vec3* secondary_terminal_delta",
        ),
        "bn_twister_path_full_owner_abi": (
            "struct Vec3* primary_up",
            "struct Vec3* secondary_up",
            "struct Vec3* primary_terminal_delta",
        ),
        "bn_twister2_path_full_owner_abi": (
            "struct Vec3* primary_up",
            "struct Vec3* secondary_up",
            "struct Vec3* primary_terminal_delta",
        ),
    }.items():
        for rendered_alias in rendered_aliases:
            assert (
                rendered_alias not in checks[check_name]["required_substrings"]
            )


def test_transition_family_mobile_symbols_prove_boolean_side_exit() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = json.loads(
        (
            repo_root
            / "analysis/symbols/windows-ios-gameplay-crosswalk.json"
        ).read_text(encoding="utf-8")
    )
    entries = {entry["windows_name"]: entry for entry in crosswalk["entries"]}
    expected_symbols = {
        "initialize_start_path_template_pair": (
            "cRPath::BuildStart(float, int, bool, char*, char*)"
        ),
        "initialize_turnover_path_template_pair": (
            "cRPath::BuildTurnover(float, int, bool, char*, char*)"
        ),
        "initialize_turnoverdouble_path_template_pair": (
            "cRPath::BuildTurnoverDouble(float, int, bool, char*, char*)"
        ),
        "initialize_turnunder_path_template_pair": (
            "cRPath::BuildTurnunder(float, int, bool, char*, char*)"
        ),
    }
    for function_name, expected_symbol in expected_symbols.items():
        entry = entries[function_name]
        assert entry["android_symbol"] == expected_symbol
        assert entry["ios_symbol"] == expected_symbol
        assert entry["android_symbol_evidence"] == "exact-demangled-symbol"
        assert entry["confidence"] == "high"
        assert "bool side-exit input" in entry["notes"]
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert "bool side_exit" in scratch


def test_wibble_twister_mobile_symbols_prove_boolean_selectors() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = json.loads(
        (
            repo_root
            / "analysis/symbols/windows-ios-gameplay-crosswalk.json"
        ).read_text(encoding="utf-8")
    )
    entries = {entry["windows_name"]: entry for entry in crosswalk["entries"]}
    expected = {
        "initialize_wibble_path_template_pair": (
            "cRPath::BuildWibble(float, int, bool, char*, char*)",
            "high",
            "bool side_exit",
        ),
        "initialize_invert_path_template_pair": (
            "cRPath::BuildInvert(float, int, bool, char*, char*)",
            "medium",
            "bool side_exit",
        ),
        "initialize_twister_path_template_pair": (
            "cRPath::BuildTwisterA(float, int, bool, char*, char*)",
            "high",
            "bool handedness",
        ),
        "initialize_twister2_path_template_pair": (
            "cRPath::BuildTwister2A(float, int, bool, char*, char*)",
            "high",
            "bool handedness",
        ),
    }
    for function_name, (
        expected_symbol,
        expected_confidence,
        expected_declaration,
    ) in expected.items():
        entry = entries[function_name]
        assert entry["android_symbol"] == expected_symbol
        assert entry["ios_symbol"] == expected_symbol
        assert entry["android_symbol_evidence"] == "exact-demangled-symbol"
        assert entry["confidence"] == expected_confidence
        assert "authored bool" in entry["notes"]
        scratch = (
            repo_root / f"tools/match/scratches/{function_name}/scratch.cpp"
        ).read_text(encoding="utf-8")
        assert expected_declaration in scratch


def test_worm_replay_preserves_two_stage_mesh_owner_lifetimes() -> None:
    replay = (BINJA_DIR / "sync_worm_path_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    assert '"initialize_worm_path_template_pair"' in replay
    for index, storage, name, variable_type in (
        (668, 68, "primary_up", "Vec3*"),
        (788, 66, "primary_sample_cursor_first", "PathTemplateSample*"),
        (819, 66, "primary_sample_cursor_second", "PathTemplateSample*"),
        (870, 67, "secondary_up", "Vec3*"),
        (985, 66, "secondary_sample_cursor_first", "PathTemplateSample*"),
        (1017, 66, "secondary_sample_cursor_second", "PathTemplateSample*"),
        (1351, 68, "primary_terminal_delta", "Vec3*"),
        (1442, 66, "secondary_terminal_delta", "Vec3*"),
        (1663, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1754, 66, "primary_mesh_sample_reloaded", "PathTemplateSample*"),
        (1848, 66, "primary_position", "Vec3*"),
        (2008, 66, "vertex", "Vec3*"),
        (2091, 66, "previous_row_vertex", "Vec3*"),
        (2094, 68, "terminal_vertex", "Vec3*"),
        (2384, 73, "face", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "WORM_PATH_USER_VAR_UPDATES" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '0x9C: ("lateral_scale", "float")' in replay
    for rejected_index in (713, 912):
        assert f"({rejected_index}, 66," not in replay


def test_cage2_replay_splits_terminal_scalar_and_preserves_mesh_owners() -> None:
    replay = (BINJA_DIR / "sync_cage2_path_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    assert '"initialize_cage2_path_template_pair"' in replay
    assert (
        '("0x42eb3f", "mlil", "RegisterVariableSourceType", 1055, 67)'
        in replay
    )
    assert (
        '("0x42eb26", "mlil", "RegisterVariableSourceType", 1030, 67)'
        in replay
    )
    assert "CAGE2_TERMINAL_CENTER_VAR" in replay
    assert 'variable_name="terminal_center_x"' in replay
    assert 'variable_type="float"' in replay

    for index, storage, name, variable_type in (
        (614, 66, "primary_up", "Vec3*"),
        (732, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
        (835, 66, "secondary_up", "Vec3*"),
        (953, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
        (1352, 67, "primary_terminal_delta", "Vec3*"),
        (1441, 66, "secondary_terminal_delta", "Vec3*"),
        (1600, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (1662, 66, "vertex", "Vec3*"),
        (2010, 71, "face_first", "ObjectFaceQuad*"),
        (2189, 71, "face_second", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "apply_split_away_user_var_update" in replay
    assert "CAGE2_PATH_USER_VAR_UPDATES" in replay
    assert "apply_user_var_updates" in replay
    assert '0x90: ("center_x", "float")' in replay
    for rejected_index in (659, 880, 1685):
        assert f"({rejected_index}, 66," not in replay

    health = json.loads(
        (Path(__file__).parents[1] / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    check = next(
        check
        for check in health["checks"]
        if check["name"] == "bn_cage2_path_full_owner_abi"
    )
    regexes = check["required_regexes"]
    for address in ("0042e9a2", "0042ea7f", "0042ec8d", "0042ecd4"):
        matching_regex = next(
            pattern for pattern in regexes if pattern.startswith(address)
        )
        for component in (r"\.x =", r"\.y =", r"\.z ="):
            assert component in matching_regex
    for rendered_alias in (
        "struct Vec3* primary_up",
        "struct Vec3* secondary_up",
        "struct Vec3* primary_terminal_delta",
        "struct Vec3* secondary_terminal_delta",
    ):
        assert rendered_alias not in check["required_substrings"]


def test_loopbow_replay_preserves_control_staged_basis_and_mesh_owners() -> None:
    replay = (BINJA_DIR / "sync_loopbow_path_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("PathTemplateSample", "0xA8"),
        ("ObjectFaceQuad", "0x30"),
    ):
        assert f'"{type_name}": {width}' in replay

    assert '"initialize_loopbow_path_template_pair"' in replay
    for index, storage, name, variable_type in (
        (1091, 66, "primary_right", "Vec3*"),
        (1122, 66, "primary_sample_cursor_first", "PathTemplateSample*"),
        (1143, 66, "primary_sample_cursor_second", "PathTemplateSample*"),
        (1164, 66, "primary_sample", "PathTemplateSample*"),
        (1194, 68, "secondary_right", "Vec3*"),
        (1229, 66, "secondary_sample_cursor_first", "PathTemplateSample*"),
        (1248, 66, "secondary_sample_cursor_second", "PathTemplateSample*"),
        (1270, 66, "secondary_sample", "PathTemplateSample*"),
        (1490, 66, "primary_up", "Vec3*"),
        (1516, 66, "secondary_position", "Vec3*"),
        (1658, 67, "primary_delta_dir", "Vec3*"),
        (1749, 67, "secondary_delta_dir", "Vec3*"),
        (1832, 68, "primary_terminal_delta", "Vec3*"),
        (1921, 67, "secondary_terminal_delta", "Vec3*"),
        (2086, 66, "primary_mesh_sample", "PathTemplateSample*"),
        (2152, 67, "vertex", "Vec3*"),
        (2278, 67, "terminal_vertex", "Vec3*"),
        (2514, 69, "face_first", "ObjectFaceQuad*"),
        (2698, 69, "face_second", "ObjectFaceQuad*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "LOOPBOW_PATH_USER_VAR_UPDATES" in replay
    assert "LOOPBOW_CONTROL_USER_VAR_UPDATES" in replay
    assert "LOOPBOW_CONTROL_LIFETIME_SPLITS" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_split_user_var_updates" in replay
    assert "apply_user_var_updates" in replay
    assert '0x80: ("delta_dir_to_next", "Vec3")' in replay
    assert '0x8C: ("delta_length", "float")' in replay
    assert '0x90: ("center_x", "float")' in replay
    assert "(2180, 66," not in replay

    for index, storage, name, variable_type in (
        (27, -128, "center_offset", "float"),
        (107, -148, "curve_segment_count_f", "float"),
        (149, -144, "lead_sample_z", "float"),
        (540, -120, "tail_sample_z", "float"),
        (726, -144, "secondary_radius", "float"),
        (744, -120, "terminal_sample_offset", "int32_t"),
        (781, -116, "angle", "float"),
        (836, -152, "half_angle", "float"),
        (1305, -152, "half_sine", "float"),
    ):
        assert (
            f'        {index},\n'
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        ) in replay

    for name, variable_type in (
        ("curve_segment_count", "int32_t"),
        ("total_segment_count", "int32_t"),
        ("curve_radius", "float"),
        ("lead_sample_index", "int32_t"),
        ("lead_sample_offset", "int32_t"),
        ("tail_index", "int32_t"),
        ("tail_sample_offset", "int32_t"),
        ("curve_index", "int32_t"),
        ("curve_sample_offset", "int32_t"),
        ("delta_index", "int32_t"),
        ("delta_sample_offset", "int32_t"),
    ):
        assert f'        "{name}",\n        "{variable_type}",' in replay

    for address, view, source_type, index, storage in (
        ("0x42bac3", "mlil", "RegisterVariableSourceType", 67, 66),
        ("0x42bac8", "mlil", "StackVariableSourceType", 72, -124),
        ("0x42bacc", "mlil", "RegisterVariableSourceType", 76, 66),
        ("0x42bacf", "mlil", "StackVariableSourceType", 79, -116),
        ("0x42baf5", "mlil", "StackVariableSourceType", 117, 4),
        ("0x42bb0e", "mlil_ssa", "StackVariableSourceType", 142, -156),
        ("0x42bb0e", "mlil_ssa", "RegisterVariableSourceType", 142, 73),
        ("0x42bc10", "mlil_ssa", "RegisterVariableSourceType", 400, 69),
        ("0x42bc10", "mlil_ssa", "StackVariableSourceType", 400, -156),
        ("0x42bc10", "mlil_ssa", "RegisterVariableSourceType", 400, 73),
        ("0x42bd79", "mlil_ssa", "StackVariableSourceType", 761, -156),
        ("0x42bd79", "mlil_ssa", "RegisterVariableSourceType", 761, 69),
        ("0x42c0b5", "mlil_ssa", "RegisterVariableSourceType", 1589, 69),
        ("0x42c0b5", "mlil_ssa", "RegisterVariableSourceType", 1589, 73),
    ):
        assert (
            f'("{address}", "{view}", "{source_type}", {index}, {storage})'
            in replay
        )


def test_attachment_follow_replay_preserves_samples_and_player_matrix() -> None:
    replay = (BINJA_DIR / "sync_attachment_follow_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("TransformMatrix", "0x40"),
        ("PathTemplateSample", "0xA8"),
    ):
        assert f'"{type_name}": {width}' in replay

    assert '"update_track_attachment_follow_state"' in replay
    assert "apply_split_user_var_update" in replay
    for address, index in (
        ("0x420dab", 251),
        ("0x420e5e", 430),
    ):
        assert f'"{address}"' in replay
        assert (
            f'        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        66,"
        ) in replay
    assert "ATTACHMENT_FOLLOW_ROOT_SPLIT_DEFINITIONS" in replay
    assert "ATTACHMENT_FOLLOW_ROOT_TARGET_VAR" in replay
    assert 'variable_name="attachment_game_base"' in replay
    assert 'variable_type="GameRoot*"' in replay
    for index, storage, name, variable_type in (
        (1406, 66, "current_secondary_sample", "PathTemplateSample*"),
        (1596, 72, "secondary_sample", "PathTemplateSample*"),
        (1717, 72, "next_secondary_sample", "PathTemplateSample*"),
        (1491, 68, "player_right", "Vec3*"),
        (1523, 67, "player_up", "Vec3*"),
        (1554, 66, "player_forward", "Vec3*"),
        (2058, 66, "player_transform", "TransformMatrix*"),
        (2091, 68, "player_up_reloaded", "Vec3*"),
        (2123, 67, "player_forward_reloaded", "Vec3*"),
        (2538, 68, "output_position_copy", "Vec3*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "ATTACHMENT_FOLLOW_USER_VAR_UPDATES" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '0x00: ("basis_right", "Vec3")' in replay
    assert '0x20: ("basis_forward", "Vec3")' in replay
    for rejected_index in (559, 744):
        assert f"({rejected_index}," not in replay


def test_golb_path_follow_replay_preserves_sample_and_flight_owners() -> None:
    replay = (BINJA_DIR / "sync_golb_path_follow_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("TransformMatrix", "0x40"),
        ("PathTemplateSample", "0xA8"),
        ("TrackRowCell", "0x54"),
        ("GolbPathFollowState", "0x28"),
        ("GolbShot", "0x2E8"),
    ):
        assert f'"{type_name}": {width}' in replay

    assert '"traverse_path_follow_golb"' in replay
    for index, storage, name, variable_type in (
        (261, 68, "flight_position_overflow", "Vec3*"),
        (360, 68, "source_anchor_position", "Vec3*"),
        (468, 68, "flight_position_terminal", "Vec3*"),
        (827, 66, "current_secondary_sample", "PathTemplateSample*"),
        (836, 67, "output_position", "Vec3*"),
        (924, 72, "secondary_sample", "PathTemplateSample*"),
        (1185, 66, "output_position_write", "Vec3*"),
        (1313, 66, "flight_transform", "TransformMatrix*"),
        (1341, 66, "flight_up", "Vec3*"),
        (1369, 66, "flight_forward", "Vec3*"),
        (1476, 68, "flight_position_side_exit", "Vec3*"),
    ):
        assert (
            f'    ({index}, {storage}, "{name}", "{variable_type}"),' in replay
        )

    assert "GOLB_PATH_FOLLOW_USER_VAR_UPDATES" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '0x1C4: ("flight_transform", "TransformMatrix")' in replay
    assert '0x24C: ("velocity", "Vec3")' in replay
    assert '0x258: ("direction", "Vec3")' in replay
    for rejected_index in (193, 354):
        assert f"({rejected_index}," not in replay


def test_golb_ai_replay_preserves_collision_owner_lifetimes() -> None:
    replay = (BINJA_DIR / "sync_golb_ai_lifetimes.py").read_text(
        encoding="utf-8"
    )

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("Sprite", "0xB4"),
        ("TrackRowCellSameLaneCursorView", "0x2F4"),
        ("Slug", "0xEC"),
        ("SlugSlotCursor", "0x35648C"),
        ("SubGarbage", "0xC4"),
        ("GolbShot", "0x2E8"),
        ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{type_name}": {width}' in replay

    for source_type, index, storage, name, variable_type in (
        (
            "RegisterVariableSourceType",
            770,
            73,
            "same_lane_cursor",
            "TrackRowCellSameLaneCursorView*",
        ),
        ("RegisterVariableSourceType", 1119, 67, "render_sprite", "Sprite*"),
        ("RegisterVariableSourceType", 1133, 67, "render_position", "Vec3*"),
        (
            "RegisterVariableSourceType",
            1627,
            72,
            "active_garbage",
            "SubGarbage*",
        ),
        (
            "RegisterVariableSourceType",
            1862,
            69,
            "slug_pool_byte_offset",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            1864,
            72,
            "slug_slot_index",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            1870,
            66,
            "slug_slot_cursor",
            "SlugSlotCursor*",
        ),
        (
            "RegisterVariableSourceType",
            1872,
            67,
            "slug_state",
            "SubSlugState",
        ),
        (
            "RegisterVariableSourceType",
            2205,
            72,
            "splash_garbage",
            "SubGarbage*",
        ),
        ("StackVariableSourceType", 0, -12, "wall_impact", "Vec3"),
    ):
        expected = (
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert expected in replay

    assert "GOLB_AI_USER_VAR_UPDATES" in replay
    assert "GOLB_AI_USER_VAR_REMOVALS" in replay
    assert "ensure_path_cell_view" in replay
    assert "current_header_type_equivalence" in replay
    assert "types_declare_missing_only" in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert "remove_user_var_updates" in replay
    assert '0x48: ("position", "Vec3")' in replay
    assert '0x00: ("previous_row_same_lane", "TrackRowCell")' in replay
    assert '0x54: ("intervening_cells", "TrackRowCell[7]")' in replay
    assert '0x3563A0: ("slug", "Slug")' in replay
    assert '0x80: ("next_active", "SubGarbage*")' in replay

    analysis_header = (
        HEADER_DIR / "path_template_types.h"
    ).read_text(encoding="utf-8")
    assert "typedef struct __ptr_offset(0x2a0)" in analysis_header
    assert (
        "__base(TrackRowCell, 0x2a0) TrackRowCellSameLaneCursorView"
        in analysis_header
    )
    assert "TrackRowCell previous_row_same_lane;" in analysis_header
    assert "TrackRowCell intervening_cells[7];" in analysis_header
    assert "__inherited TrackRowCell current_cell;" in analysis_header
    assert "TrackRowCellSameLaneCursorView_must_be_0x2f4" in analysis_header
    assert '"TrackRowCellSameLaneCursorView",' in (
        BINJA_DIR / "sync_path_template_types.py"
    ).read_text(encoding="utf-8")
    assert (
        '"RegisterVariableSourceType",\n'
        "        765,\n"
        "        66,\n"
        '        "source_cell",\n'
        '        "TrackRowCell*",'
    ) in replay


def test_sprite_effect_replay_preserves_shared_sprite_owners() -> None:
    replay = (
        BINJA_DIR / "sync_sprite_effect_owner_lifetimes.py"
    ).read_text(encoding="utf-8")

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("tColour", "0x10"),
        ("Sprite", "0xB4"),
        ("FireWork", "0x01"),
        ("GolbShot", "0x2E8"),
        ("Player", "0x4364"),
        ("SubGarbage", "0xC4"),
        ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{type_name}": {width}' in replay

    for function_name, index, storage, name, variable_type in (
        ("spawn_golb_trail_sprite", 28, 66, "trail_sprite", "Sprite*"),
        ("spawn_golb_smoke", 34, 66, "smoke_sprite", "Sprite*"),
        (
            "spawn_golb_smoke",
            184,
            72,
            "sprite_motion_cursor",
            "uint8_t*",
        ),
        ("spawn_golb_impact_sprite", 41, 66, "impact_sprite", "Sprite*"),
        (
            "spawn_garbage_smoke_particle",
            42,
            66,
            "smoke_sprite",
            "Sprite*",
        ),
        (
            "spawn_garbage_smoke_particle",
            184,
            72,
            "sprite_motion_cursor",
            "uint8_t*",
        ),
        ("firework_shoot", 57, 66, "sprite", "Sprite*"),
        ("firework_shoot", 32, 69, "saved_texture_id", "int32_t"),
        ("firework_shoot", 37, 71, "saved_owner", "int32_t"),
        ("firework_shoot", 42, -16, "remaining", "int32_t"),
        ("firework_shoot", 181, -40, "green", "float"),
        ("firework_shoot", 322, -12, "velocity_x", "float"),
        ("firework_shoot", 342, 68, "source_position", "Vec3*"),
        ("firework_shoot", 346, 72, "sprite_position", "Vec3*"),
    ):
        source_type = (
            "StackVariableSourceType"
            if name in {"remaining", "green", "velocity_x"}
            else "RegisterVariableSourceType"
        )
        expected = (
            f'        "{function_name}",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert expected in replay

    assert "SPRITE_EFFECT_OWNER_USER_VAR_UPDATES" in replay
    assert "SPRITE_EFFECT_OWNER_USER_VAR_REMOVALS" in replay
    assert "remove_user_var_updates" in replay
    assert (
        '        "firework_shoot",\n'
        '        "RegisterVariableSourceType",\n'
        "        293,\n"
        "        66,\n"
        '        "sprite_velocity",\n'
        '        "Vec3*",'
    ) in replay
    for index, name in (
        (107, "duration"),
        (300, "velocity_x_centered"),
    ):
        assert (
            '        "firework_shoot",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            "        4103,\n"
            f'        "{name}",\n'
            '        "double",'
        ) in replay
    assert "apply_split_user_var_update" in replay
    assert "FIREWORK_RED_DEFINITIONS" in replay
    assert '("0x441e70", "mlil", "StackVariableSourceType", 160, 16)' in replay
    assert 'variable_name=variable_name' in replay
    assert "FIREWORK_VELOCITY_Z_DEFINITIONS" in replay
    assert '("0x441eb5", "mlil", "StackVariableSourceType", 229, 8)' in replay
    assert "FIREWORK_VELOCITY_Y_DEFINITIONS" in replay
    assert '("0x441ed8", "mlil", "StackVariableSourceType", 264, 12)' in replay
    assert "FIREWORK_VELOCITY_X_RANDOM_DEFINITIONS" in replay
    assert '("0x441ee1", "mlil", "StackVariableSourceType", 273, 16)' in replay
    assert "current_type_widths" in replay
    assert "current_struct_fields_batch" in replay
    assert "apply_user_var_updates" in replay
    assert '0x00: ("_empty", "uint8_t")' in replay
    assert '0x48: ("position", "Vec3")' in replay
    assert '0x54: ("velocity", "Vec3")' in replay
    assert '0x78: ("gravity_step", "float")' in replay
    assert '0x270: ("game", "SubgameRuntime*")' in replay
    assert '0x8C: ("owner_game", "SubgameRuntime*")' in replay
    assert "struct SpriteMotionTail" not in replay

    ida_replay = (
        IDA_DIR / "apply_path_template_types.py"
    ).read_text(encoding="utf-8")
    assert "FIREWORK_SHOOT_LVAR_SPECS" in ida_replay
    for name, declaration, definition_address, stack_offset in (
        ("sprite", "Sprite *sprite;", "0x441E0F", "None"),
        ("flags", "SpriteFlag flags;", "0x441E17", "None"),
        ("duration_random", "double duration_random;", "0x441E37", "None"),
        ("green", "float green;", "0x441E86", "8"),
        ("remaining", "int32_t remaining;", "0x441DFB", "32"),
        ("velocity_x", "float velocity_x;", "0x441F13", "36"),
        ("velocity_z", "float velocity_z;", "0x441EB6", "56"),
        ("velocity_y", "float velocity_y;", "0x441ED9", "60"),
        ("red", "float red;", "0x441E71", "64"),
    ):
        assert (
            f'("{name}", "{declaration}", {definition_address}, '
            f"{stack_offset})"
        ) in ida_replay
    assert '"velocity_x_random"' in ida_replay
    assert '"int32_t velocity_x_random;"' in ida_replay
    assert "0x441EE2" in ida_replay
    assert "def _sync_firework_shoot_lvars" in ida_replay
    assert '"firework_shoot_lvars": firework_shoot_lvars' in ida_replay

    health_checks = json.loads(
        (
            Path(__file__).parents[1]
            / "analysis/decompile/health_checks.json"
        ).read_text(encoding="utf-8")
    )["checks"]
    health_by_name = {check["name"]: check for check in health_checks}
    assert (
        health_by_name["bn_firework_sprite_and_stack_slot_owners"]["artifact"]
        == "analysis/decompile/binja/functions/00441dd0-firework_shoot.c"
    )
    assert (
        health_by_name["ida_firework_sprite_and_stack_slot_owners"]["artifact"]
        == "analysis/decompile/ida/functions/00441dd0-firework_shoot.c"
    )
    assert "int32_t remaining = count" in health_by_name[
        "bn_firework_sprite_and_stack_slot_owners"
    ]["required_substrings"]
    assert "sprite->position = *position;" in health_by_name[
        "ida_firework_sprite_and_stack_slot_owners"
    ]["required_substrings"]


def test_create_golb_replay_splits_real_pointer_owners() -> None:
    repo_root = Path(__file__).parents[1]
    replay = (
        BINJA_DIR / "sync_create_golb_owner_lifetimes.py"
    ).read_text(encoding="utf-8")

    for type_name, width in (
        ("Vec3", "0x0C"),
        ("tColour", "0x10"),
        ("BodNode", "0x10"),
        ("BodBase", "0x38"),
        ("Sprite", "0xB4"),
        ("ContactTargetObject", "0x08"),
        ("ContactTargetEntry", "0x18"),
        ("Snail", "0x19B4"),
        ("GolbShot", "0x2E8"),
        ("Player", "0x4364"),
        ("SubgameRuntime", "0x1272838"),
    ):
        assert f'"{type_name}": {width}' in replay

    for index, storage, name, variable_type in (
        (406, 66, "shot_velocity", "Vec3*"),
        (904, 68, "spawn_anchor", "Vec3*"),
        (1714, 66, "vapour_list_head", "BodBase*"),
        (1900, 66, "render_sprite", "Sprite*"),
        (1987, 67, "render_color", "tColour*"),
        (2043, 66, "render_position", "Vec3*"),
    ):
        expected = (
            '        "create_golb",\n'
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{variable_type}",'
        )
        assert expected in replay

    assert "apply_split_user_var_update" in replay
    assert "CREATE_GOLB_SPRITE_GAME_DEFINITIONS" in replay
    assert (
        '("0x415aae", "mlil", "RegisterVariableSourceType", 2094, 66)'
        in replay
    )
    assert "CREATE_GOLB_TARGET_ENTRY_DEFINITIONS" in replay
    assert (
        '("0x4158ad", "mlil", "RegisterVariableSourceType", 1581, 66)'
        in replay
    )
    assert 'variable_name="sprite_game"' in replay
    assert 'variable_type="SubgameRuntime*"' in replay
    assert 'variable_name="target_entry"' in replay
    assert 'variable_type="ContactTargetEntry*"' in replay
    assert '0x0248: ("render_sprite", "Sprite*")' in replay
    assert '0x17B0: ("snail_hotspots_world", "Vec3[19]")' in replay
    assert '0x1270FD4: ("enemy_manager", "EnemyManager")' in replay

    analysis_header = (
        repo_root / "analysis/headers/path_template_types.h"
    ).read_text(encoding="utf-8")
    match_header = (
        repo_root / "tools/match/include/golb.h"
    ).read_text(encoding="utf-8")
    catalog_replay = (
        BINJA_DIR / "sync_path_template_types.py"
    ).read_text(encoding="utf-8")
    for text in (analysis_header, match_header, catalog_replay):
        assert "render_body_owner" not in text
        assert "render_sprite" in text


def test_time_trial_replays_inline_course_record_ownership() -> None:
    repo_root = Path(__file__).parents[1]
    match_header = (
        repo_root / "tools/match/include/time_trial.h"
    ).read_text(encoding="utf-8")
    analysis_headers = [
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in (
            "bn_subgame_runtime_types.h",
            "ida_subgame_runtime_types.h",
            "path_template_types.h",
        )
    ]

    for header in (match_header, *analysis_headers):
        assert "TIME_TRIAL_COURSE_RECORD_COUNT = 51" in header
        assert "TimeTrialCourseRecord" in header
        assert "char* course_name;" in header
        assert "unknown_04[0x10 - 0x04]" in header
        assert "TimeTrialCourseRecord_must_be_0x10" in header
        assert "TimeTrial_must_be_0x330" in header

    for header in analysis_headers:
        assert (
            "TimeTrialCourseRecord course_records["
            "TIME_TRIAL_COURSE_RECORD_COUNT];"
        ) in header

    runtime_sync = (
        BINJA_DIR / "sync_subgame_runtime_types.py"
    ).read_text(encoding="utf-8")
    assert "ensure_time_trial_owner_types" in runtime_sync
    assert 'type_names = ("TimeTrialCourseRecord", "TimeTrial")' in runtime_sync
    assert "current_header_type_equivalence" in runtime_sync
    assert "types_declare_missing_only" in runtime_sync

    path_sync = (
        BINJA_DIR / "sync_path_template_types.py"
    ).read_text(encoding="utf-8")
    assert '"TimeTrialCourseRecord",' in path_sync
    assert '"TimeTrial",' in path_sync

    ida_sync = (
        IDA_DIR / "apply_subgame_runtime_types.py"
    ).read_text(encoding="utf-8")
    assert "TIME_TRIAL_COURSE_RECORD_EXPECTED_SIZE = 0x10" in ida_sync
    assert "TIME_TRIAL_EXPECTED_SIZE = 0x330" in ida_sync
    assert "_time_trial_owner_readback" in ida_sync


def test_help_lifecycle_owner_replays_cross_decompiler() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (
        BINJA_DIR / "sync_subgame_runtime_types.py"
    ).read_text(encoding="utf-8")
    ida_sync = (
        IDA_DIR / "apply_subgame_runtime_types.py"
    ).read_text(encoding="utf-8")
    path_sync = (
        IDA_DIR / "apply_path_template_types.py"
    ).read_text(encoding="utf-8")
    path_header = (
        HEADER_DIR / "path_template_types.h"
    ).read_text(encoding="utf-8")

    prototypes = (
        "void __thiscall initialize_help_screen(Help* help)",
        "void __thiscall destroy_help_screen(Help* help)",
        "void __thiscall update_help_screen(Help* help)",
    )
    for prototype in prototypes:
        assert prototype in binja_sync
        assert prototype + ";" in ida_sync
        assert prototype + ";" in path_sync
        assert prototype + ";" in path_header

    for address, selector in (
        ("0x416800", "initialize_help_screen"),
        ("0x4168c0", "destroy_help_screen"),
        ("0x4168d0", "update_help_screen"),
    ):
        assert f'("{address}", "{selector}")' in binja_sync
        assert selector in binja_sync.split("HELP_REANALYSIS_FUNCTIONS", 1)[1]
        assert selector in ida_sync.split("REANALYSIS_FUNCTIONS", 1)[1]

    assert '("Help", HELP_FIELD_UPDATES)' in binja_sync
    assert '("0x00", "back_button", "FrontendWidget*")' in binja_sync
    assert "HELP_EXPECTED_SIZE = 0x04" in binja_sync
    assert "HELP_OWNER_EXPECTED_SIZE = 0x04" in ida_sync
    assert "Help_must_be_0x04" in path_header
    for header_name in (
        "bn_subgame_runtime_types.h",
        "ida_subgame_runtime_types.h",
    ):
        assert "Help_must_be_0x04" in (
            HEADER_DIR / header_name
        ).read_text(encoding="utf-8")

    checks = json.loads(
        (repo_root / "analysis/decompile/health_checks.json").read_text(
            encoding="utf-8"
        )
    )
    checks_by_name = {check["name"]: check for check in checks["checks"]}
    for name in (
        "bn_initialize_help_screen_landscape_owner",
        "ida_initialize_help_screen_landscape_owner",
        "bn_help_update_owner",
        "ida_help_update_owner",
    ):
        assert name in checks_by_name


def test_runtime_segment_selection_owner_chain_replays_cross_decompiler() -> None:
    repo_root = Path(__file__).parents[1]
    canonical_binja = (
        BINJA_DIR / "sync_path_template_types.py"
    ).read_text(encoding="utf-8")
    focused_binja = (
        BINJA_DIR / "sync_runtime_grid_clear_lifetimes.py"
    ).read_text(encoding="utf-8")
    canonical_ida = (
        IDA_DIR / "apply_path_template_types.py"
    ).read_text(encoding="utf-8")

    assert "POPULATE_SEGMENT_SELECTION_USER_VAR_UPDATES" in canonical_binja
    assert "RUNTIME_SEGMENT_SELECTION_USER_VAR_UPDATES" in focused_binja
    for source_type, index, storage, name, type_name in (
        (
            "RegisterVariableSourceType",
            759,
            66,
            "visited_segment_index",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            810,
            73,
            "runtime_row_index",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            814,
            71,
            "build_runtime_owner",
            "SubgameRuntime*",
        ),
        (
            "RegisterVariableSourceType",
            822,
            72,
            "selected_segment",
            "SubSegment*",
        ),
        (
            "RegisterVariableSourceType",
            971,
            66,
            "random_segment_index",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            1012,
            66,
            "sequential_segment_index",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            1052,
            66,
            "selected_segment_row_count",
            "int32_t",
        ),
        (
            "RegisterVariableSourceType",
            1147,
            68,
            "source_segment",
            "SubSegment*",
        ),
    ):
        expected = (
            '        "populate_runtime_track_cells_from_segments",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in canonical_binja
        assert expected in focused_binja

    for name, declaration, definition_address in (
        (
            "visited_segment_index",
            "int32_t visited_segment_index;",
            "0x4361A8",
        ),
        ("runtime_row_index", "int32_t runtime_row_index;", "0x4361DB"),
        (
            "build_runtime_owner",
            "SubgameRuntime *build_runtime_owner;",
            "0x4361DF",
        ),
        ("selected_segment", "SubSegment *selected_segment;", "0x4361E7"),
        (
            "selected_segment_row_count",
            "int32_t selected_segment_row_count;",
            "0x4362CD",
        ),
        ("source_segment", "SubSegment *source_segment;", "0x43632C"),
    ):
        assert f'"{name}"' in canonical_ida
        assert f'"{declaration}"' in canonical_ida
        assert definition_address in canonical_ida

    health_checks = {
        check["name"]: check
        for check in json.loads(
            (repo_root / "analysis/decompile/health_checks.json").read_text(
                encoding="utf-8"
            )
        )["checks"]
    }
    for name in (
        "bn_runtime_cell_stride_owner_graph",
        "ida_runtime_cell_stride_owner_graph",
    ):
        required = health_checks[name]["required_substrings"]
        for marker in (
            "visited_segment_index",
            "runtime_row_index",
            "build_runtime_owner",
            "selected_segment",
            "selected_segment_row_count",
            "source_segment",
        ):
            assert any(marker in item for item in required)


def test_runtime_attachment_path_borrows_replay_cross_decompiler() -> None:
    repo_root = Path(__file__).parents[1]
    canonical_binja = (
        BINJA_DIR / "sync_path_template_types.py"
    ).read_text(encoding="utf-8")
    focused_binja = (
        BINJA_DIR / "sync_runtime_grid_clear_lifetimes.py"
    ).read_text(encoding="utf-8")
    canonical_ida = (
        IDA_DIR / "apply_path_template_types.py"
    ).read_text(encoding="utf-8")

    assert "POPULATE_ATTACHMENT_INSTALL_USER_VAR_UPDATES" in canonical_binja
    assert "RUNTIME_ATTACHMENT_INSTALL_USER_VAR_UPDATES" in focused_binja
    for source_type, index, storage, name, type_name in (
        (
            "RegisterVariableSourceType",
            3686,
            67,
            "selected_attachment_path",
            "Path*",
        ),
        (
            "RegisterVariableSourceType",
            3844,
            68,
            "attachment_span_index",
            "int32_t",
        ),
    ):
        expected = (
            '        "populate_runtime_track_cells_from_segments",\n'
            f'        "{source_type}",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}"'
        )
        assert expected in canonical_binja
        assert expected in focused_binja

    for replay, removal_name in (
        (canonical_binja, "REJECTED_POPULATE_RUNTIME_CELL_ALIAS_REMOVALS"),
        (focused_binja, "REJECTED_RUNTIME_CELL_ALIAS_REMOVALS"),
    ):
        assert removal_name in replay
        assert "remove_user_var_updates" in replay
        rejected_alias = (
            '        "populate_runtime_track_cells_from_segments",\n'
            '        "RegisterVariableSourceType",\n'
            "        2068,\n"
            "        73,\n"
            '        "runtime_cell",\n'
            '        "TrackRowCell*"'
        )
        assert rejected_alias in replay

    for name, declaration, definition_address in (
        ("runtime_cell", "TrackRowCell *runtime_cell;", "0x4366C5"),
        (
            "selected_attachment_path",
            "Path *selected_attachment_path;",
            "0x436D17",
        ),
        (
            "attachment_span_index",
            "int32_t attachment_span_index;",
            "0x436DB5",
        ),
    ):
        assert f'"{name}"' in canonical_ida
        assert f'"{declaration}"' in canonical_ida
        assert definition_address in canonical_ida

    health_checks = {
        check["name"]: check
        for check in json.loads(
            (repo_root / "analysis/decompile/health_checks.json").read_text(
                encoding="utf-8"
            )
        )["checks"]
    }
    bn_health = health_checks["bn_runtime_cell_stride_owner_graph"]
    for marker in (
        "struct Path* selected_attachment_path",
        "runtime_cell_anchor->cell.attachment_template_record = selected_attachment_path",
        "int32_t attachment_span_index = 0",
        "attachment_span_index += 1",
    ):
        assert marker in bn_health["required_substrings"]
    for marker in (
        "struct Path* ecx_98",
        "runtime_cell_anchor->cell.attachment_template_record = ecx_98",
        "int32_t k = 0",
    ):
        assert marker in bn_health["forbidden_substrings"]

    ida_health = health_checks["ida_runtime_cell_stride_owner_graph"]
    for marker in (
        "TrackRowCell *runtime_cell;",
        "Path *selected_attachment_path;",
        "int32_t attachment_span_index;",
        "runtime_cell_anchor->cell.attachment_template_record = selected_attachment_path",
        "stamped_row->primary_attachment_cell = runtime_cell",
        "stamped_row->secondary_attachment_cell = runtime_cell",
    ):
        assert marker in ida_health["required_substrings"]
    for marker in (
        "TrackRowCell *p_cell;",
        "PathPair *p_secondary;",
        "signed int v83;",
        "runtime_cell_anchor->cell.attachment_template_record = &p_secondary->primary",
    ):
        assert marker in ida_health["forbidden_substrings"]


def test_segment_import_cursor_lifetimes_replay_cross_decompiler() -> None:
    repo_root = Path(__file__).parents[1]
    binja_sync = (
        BINJA_DIR / "sync_segment_catalog_types.py"
    ).read_text(encoding="utf-8")
    ida_sync = (
        IDA_DIR / "apply_segment_catalog_types.py"
    ).read_text(encoding="utf-8")

    assert "SEGMENT_IMPORT_CURSOR_USER_VAR_UPDATES" in binja_sync
    for storage, name, type_name in (
        (0, "parse_cursor", "char*"),
        (4, "row_count_cursor", "int32_t*"),
        (8, "segment_file_name_saved", "EnumeratedEntryName*"),
        (12, "ring_speed_catalog_owner", "SMTracks*"),
        (16, "segment_index_spill", "int32_t"),
        (20, "glyph_row_base", "int32_t"),
        (24, "segment_row_base", "int32_t"),
        (28, "row_index", "int32_t"),
        (32, "path_name", "char[64]"),
        (96, "option_text", "char[512]"),
        (608, "mesh_name", "char[128]"),
        (736, "file_path", "char[512]"),
        (1248, "file_buffer", "char[4096]"),
        (5344, "segment_files", "EnumeratedEntryName[512]"),
    ):
        expected = (
            '        "StackVariableSourceType",\n'
            "        0,\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}",'
        )
        assert expected in binja_sync

    for index, storage, name, type_name in (
        (84, 71, "segment_index", "int32_t"),
        (98, 73, "segment_file_name_cursor", "EnumeratedEntryName*"),
        (390, 73, "data_line_cursor", "char*"),
        (452, 71, "flattened_row_index", "int32_t"),
        (468, 73, "glyph_cursor", "char*"),
        (472, 66, "lane_index", "int32_t"),
        (527, 73, "option_cursor", "char*"),
        (551, 67, "option_out_cursor", "char*"),
        (623, 67, "mesh_name_cursor", "char*"),
        (1089, 68, "path_name_cursor", "char*"),
    ):
        expected = (
            '        "RegisterVariableSourceType",\n'
            f"        {index},\n"
            f"        {storage},\n"
            f'        "{name}",\n'
            f'        "{type_name}",'
        )
        assert expected in binja_sync

    assert "SEGMENT_IMPORT_LVAR_SPECS" in ida_sync
    for definition_address, stack_offset, name, declaration in (
        ("0x4483B3", 52, "parse_cursor", "char *parse_cursor;"),
        ("0x4481DC", 56, "row_count_cursor", "int32_t *row_count_cursor;"),
        ("0x4481B9", 68, "segment_index_spill", "int32_t segment_index_spill;"),
        ("0x4481D4", 72, "glyph_row_base", "int32_t glyph_row_base;"),
        ("0x4481D0", 76, "segment_row_base", "int32_t segment_row_base;"),
    ):
        expected = (
            f"        {definition_address},\n"
            f"        {stack_offset},\n"
            f'        "{name}",\n'
            f'        "{declaration}",'
        )
        assert expected in ida_sync

    for definition_address, name, declaration in (
        ("0x4482E7", "data_line_cursor", "char *data_line_cursor;"),
        (
            "0x448325",
            "flattened_row_index",
            "int32_t flattened_row_index;",
        ),
        ("0x448335", "glyph_cursor", "char *glyph_cursor;"),
        ("0x448339", "lane_index", "int32_t lane_index;"),
        ("0x448370", "option_cursor", "char *option_cursor;"),
        ("0x448388", "option_out_cursor", "char *option_out_cursor;"),
        ("0x4483D0", "mesh_name_cursor", "char *mesh_name_cursor;"),
        ("0x4485A2", "path_name_cursor", "char *path_name_cursor;"),
    ):
        expected = (
            f"        {definition_address},\n"
            "        None,\n"
            f'        "{name}",\n'
            f'        "{declaration}",'
        )
        assert expected in ida_sync

    health_checks = {
        check["name"]: check
        for check in json.loads(
            (repo_root / "analysis/decompile/health_checks.json").read_text(
                encoding="utf-8"
            )
        )["checks"]
    }
    for check_name in (
        "bn_load_segment_definitions_catalog_owners",
        "ida_load_segment_definitions_catalog_owners",
    ):
        required = health_checks[check_name]["required_substrings"]
        for marker in (
            "segment_index_spill",
            "segment_row_base",
            "glyph_row_base",
            "data_line_cursor",
            "flattened_row_index",
            "glyph_cursor",
            "lane_index",
            "option_cursor",
            "option_out_cursor",
            "mesh_name_cursor",
            "path_name_cursor",
        ):
            assert any(marker in item for item in required)


def test_mobile_utility_abis_and_overlay_owners_are_persisted() -> None:
    repo_root = Path(__file__).parents[1]
    binja_object_sync = (
        BINJA_DIR / "sync_object_render_types.py"
    ).read_text(encoding="utf-8")
    ida_object_sync = (
        IDA_DIR / "apply_object_render_types.py"
    ).read_text(encoding="utf-8")
    binja_subgame_sync = (
        BINJA_DIR / "sync_subgame_runtime_types.py"
    ).read_text(encoding="utf-8")
    ida_subgame_sync = (
        IDA_DIR / "apply_subgame_runtime_types.py"
    ).read_text(encoding="utf-8")
    ida_frame_sync = (
        IDA_DIR / "apply_frame_renderer_types.py"
    ).read_text(encoding="utf-8")

    object_headers = (
        (HEADER_DIR / "bn_object_render_types.h").read_text(
            encoding="utf-8"
        ),
        (HEADER_DIR / "object_render_types.h").read_text(
            encoding="utf-8"
        ),
    )
    frame_headers = (
        (HEADER_DIR / "bn_frame_renderer_types.h").read_text(
            encoding="utf-8"
        ),
        (HEADER_DIR / "frame_renderer_types.h").read_text(
            encoding="utf-8"
        ),
    )
    matcher_duplicate_header = (
        repo_root / "tools/match/include/duplicate_vertices.h"
    ).read_text(encoding="utf-8")
    matcher_subgame_header = (
        repo_root / "tools/match/include/subgame_runtime.h"
    ).read_text(encoding="utf-8")

    clean_prototype = (
        "void __thiscall clean_duplicate_vertices("
        "DuplicateVertices* duplicate_vertices, int32_t unused)"
    )
    assert clean_prototype in binja_object_sync
    assert (
        "void __thiscall clean_duplicate_vertices("
        "DuplicateVertices* duplicate_vertices, int unused);"
    ) in ida_object_sync
    for header in object_headers:
        assert "void __thiscall clean_duplicate_vertices(" in header
        assert (
            "DuplicateVertices* duplicate_vertices, int32_t unused);"
            in header
        )
    assert "void clean_duplicate_vertices(int unused);" in (
        matcher_duplicate_header
    )

    switch_prototype = (
        "void __thiscall switch_track_mirror("
        "SubgameRuntime* runtime)"
    )
    assert switch_prototype in binja_subgame_sync
    assert switch_prototype + ";" in ida_subgame_sync
    assert "void switch_track_mirror();" in matcher_subgame_header
    assert "TRACK_MIRROR_REANALYSIS_FUNCTIONS" in binja_subgame_sync
    assert (
        '"populate_runtime_track_cells_from_segments",'
        in binja_subgame_sync
    )
    assert (
        '("0x355bd4", "barrier_sub_lazer_list_head", "BodBase")'
        in binja_subgame_sync
    )
    assert (
        '("0x355bd4", "sub_lazer_list_head", "BodBase")'
        not in binja_subgame_sync
    )

    for address, function_name in (
        ("0x40A1B0", "update_overlay"),
        ("0x40A240", "initialize_overlay"),
    ):
        assert f'({address}, "{function_name}")' in ida_frame_sync
        assert (
            f"void __thiscall {function_name}(FrameOverlay *overlay);"
            in ida_frame_sync
        )
    for header in frame_headers:
        assert "uint32_t render_mask;" in header
        assert "float overlay_rotation_angle;" in header
