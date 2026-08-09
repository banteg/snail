from __future__ import annotations

import re
from pathlib import Path
from types import SimpleNamespace

from snail.cli import main
from snail.mobile import (
    DEFAULT_ANDROID_CORPUS_ROOT,
    DEFAULT_IOS_CORPUS_ROOT,
    DEFAULT_MOBILE_CROSSWALK_PATH,
    corpus_function_path,
    exact_cross_port_backfills,
    load_json,
    rank_mobile_symbols,
    resolve_corpus_symbol,
    resolve_corpus_symbols,
    signature_base,
)
from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    load_function_symbol_manifest,
)


def _index(*symbols: str) -> dict:
    return {
        "functions": [
            {
                "demangled": symbol,
                "path": f"functions/{index}.c",
                "status": "ok",
            }
            for index, symbol in enumerate(symbols)
        ]
    }


def test_signature_base_handles_call_operator() -> None:
    assert signature_base("Thing::operator()(int, float)") == (
        "Thing::operator()"
    )


def test_resolve_corpus_symbol_supports_unique_ellipsis_base() -> None:
    index = _index("cRSubGame::AddParcel(tVector*, cRSubGoldy*)")

    resolved = resolve_corpus_symbol(index, "cRSubGame::AddParcel(...)")

    assert resolved is not None
    assert resolved["demangled"] == (
        "cRSubGame::AddParcel(tVector*, cRSubGoldy*)"
    )


def test_resolve_corpus_symbols_preserves_constructor_variants() -> None:
    index = _index("cRBod::cRBod()", "cRBod::cRBod()")

    resolved = resolve_corpus_symbols(index, "cRBod::cRBod()")

    assert len(resolved) == 2


def test_rank_mobile_symbols_uses_path_family_shape() -> None:
    index = _index(
        "cRPath::BuildSlalomBig(int, int, bool, char*, char*)",
        "cRPath::BuildSlalom(int, int, bool, char*, char*)",
        "cRSubGoldy::AI()",
    )

    ranked = rank_mobile_symbols(
        "initialize_slalom_path_template_pair",
        None,
        index,
    )

    assert ranked[0].symbol == (
        "cRPath::BuildSlalom(int, int, bool, char*, char*)"
    )


def test_rank_mobile_symbols_uses_owner_for_ai_methods() -> None:
    index = _index(
        "cRSubGoldy::AI()",
        "cRSubGame::AI()",
        "cRBorder::AI()",
    )

    ranked = rank_mobile_symbols("update_subgoldy", None, index)

    assert ranked[0].symbol == "cRSubGoldy::AI()"


def test_rank_mobile_symbols_uses_exact_method_owner_identity() -> None:
    index = {
        "functions": [
            {
                "demangled": (
                    "cRSubGame::AddParcel(tVector*, cRSubGoldy*)"
                ),
                "size": 312,
                "status": "ok",
            },
            {
                "demangled": "cRSubGame::ReSet()",
                "size": 456,
                "status": "ok",
            },
        ]
    }

    ranked = rank_mobile_symbols(
        "reset_subgame",
        None,
        index,
        windows_size=304,
    )

    assert ranked[0].symbol == "cRSubGame::ReSet()"
    assert ranked[0].name_score == 1.0


def test_rank_mobile_symbols_uses_size_when_names_are_ambiguous() -> None:
    index = {
        "functions": [
            {
                "demangled": "cRAlpha::LoadArchive()",
                "size": 1400,
                "status": "ok",
            },
            {
                "demangled": "cRBeta::LoadArchive()",
                "size": 23072,
                "status": "ok",
            },
        ]
    }

    ranked = rank_mobile_symbols(
        "initialize_archive",
        None,
        index,
        windows_size=23072,
    )

    assert ranked[0].symbol == "cRBeta::LoadArchive()"


def test_rank_mobile_symbols_excludes_only_exact_audited_rejections() -> None:
    index = _index(
        "cRGame::LoadPaths()",
        "cRGame::LoadPaths(char*)",
        "cRGame::Init0()",
    )

    ranked = rank_mobile_symbols(
        "initialize_game_assets_and_world",
        None,
        index,
        rejected_symbols=("cRGame::LoadPaths()",),
    )

    symbols = {candidate.symbol for candidate in ranked}
    assert "cRGame::LoadPaths()" not in symbols
    assert "cRGame::LoadPaths(char*)" in symbols


def test_rank_mobile_symbols_prefers_exact_alias_over_platform_stub_size() -> None:
    index = {
        "functions": [
            {
                "demangled": (
                    "cRMouse::ConvertScreenXY(float, float, float*, float*)"
                ),
                "size": 288,
                "status": "ok",
            },
            {
                "demangled": "MouseRead(int, float*, float*)",
                "size": 4,
                "status": "ok",
            },
        ]
    }

    ranked = rank_mobile_symbols(
        "convert_mouse_screen_xy",
        "Windows cursor-position bridge.",
        index,
        windows_aliases=("MouseRead",),
        windows_size=448,
    )

    assert ranked[0].symbol == "MouseRead(int, float*, float*)"
    assert ranked[0].score == 1.0


def test_exact_cross_port_backfills_mark_name_evidence() -> None:
    crosswalk = {
        "entries": [
            {
                "windows_name": "update_subgoldy",
                "ios_symbol": "cRSubGoldy::AI()",
            }
        ]
    }

    changes = exact_cross_port_backfills(
        crosswalk,
        _index("cRSubGoldy::AI()"),
        _index("cRSubGoldy::AI()"),
    )

    assert changes == [
        ("update_subgoldy", "android", "cRSubGoldy::AI()")
    ]
    assert crosswalk["entries"][0]["android_symbol"] == (
        "cRSubGoldy::AI()"
    )
    assert crosswalk["entries"][0]["android_symbol_evidence"] == (
        "exact-demangled-symbol"
    )


def test_complete_crosswalk_covers_manifest_once() -> None:
    manifest = load_function_symbol_manifest(
        DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH
    )
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    names = [entry["windows_name"] for entry in crosswalk["entries"]]

    assert len(names) == len(set(names))
    assert set(names) == {function.name for function in manifest.functions}
    game_init = next(
        entry
        for entry in crosswalk["entries"]
        if entry["windows_name"] == "initialize_game_assets_and_world"
    )
    assert game_init["status"] == "unverified"
    rejected = {
        rejection["symbol"]
        for rejection in game_init["mobile_candidate_rejections"]
    }
    assert rejected == {
        "cRGame::cRGame()",
        "cRGame::Init0()",
        "cRGame::Init1()",
        "cRGame::Init2()",
        "cRGame::Init3()",
        "cRGame::Init4()",
        "cRGame::Init5()",
        "cRGame::LoadPaths()",
    }
    for port in ("android", "ios"):
        assert all(
            candidate["symbol"] not in rejected
            for candidate in game_init[f"{port}_candidates"]
        )
    for entry in crosswalk["entries"]:
        rejected = {
            rejection["symbol"]
            for rejection in entry.get("mobile_candidate_rejections", ())
        }
        for port in ("android", "ios"):
            assert all(
                candidate["symbol"] not in rejected
                for candidate in entry.get(f"{port}_candidates", ())
            )


def test_verified_mobile_symbols_resolve_to_tracked_bodies() -> None:
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    for port, root in (
        ("android", DEFAULT_ANDROID_CORPUS_ROOT),
        ("ios", DEFAULT_IOS_CORPUS_ROOT),
    ):
        index = load_json(root / "index.json")
        for entry in crosswalk["entries"]:
            symbol = entry.get(f"{port}_symbol")
            if not symbol:
                continue
            resolved = resolve_corpus_symbols(index, symbol)
            assert len(resolved) == entry[f"{port}_body_count"]
            for function in resolved:
                assert corpus_function_path(root, function).is_file()


def test_mobile_utility_owner_mappings_are_exact_and_verified() -> None:
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    expected = {
        "update_overlay": (
            "cROverlay::AI()",
            "cROverlay::AI()",
        ),
        "initialize_overlay": (
            "cROverlay::Init()",
            None,
        ),
        "clean_duplicate_vertices": (
            "cRDuplicateVertices::Clean(int)",
            None,
        ),
        "switch_track_mirror": (
            "cRSubGame::SwitchMirror()",
            None,
        ),
        "normalize_segment_glyph_for_track_flags": (
            "cRSubGame::LevelConvert(char, int, bool)",
            None,
        ),
    }

    for windows_name, (android_symbol, ios_symbol) in expected.items():
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["android_symbol"] == android_symbol
        assert entry["android_symbol_evidence"] == (
            "exact-demangled-symbol"
        )
        assert entry.get("ios_symbol") == ios_symbol

    input_ok = entries["update_input_ok"]
    assert input_ok["status"] == "verified"
    assert input_ok["confidence"] == "high"
    assert input_ok["android_symbol"] == "cRInputOK::AI()"
    assert "android_symbol_evidence" not in input_ok
    assert "ios_symbol" not in input_ok


def test_mobile_track_pipeline_recovers_authored_windows_members() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    expected_members = (
        (
            "set_subgame_features",
            "SetFeatures",
            "?SetFeatures@cRSubGame@@QAEXXZ",
            True,
        ),
        (
            "build_track_colours",
            "BuildColours",
            "?BuildColours@cRSubGame@@QAEXXZ",
            True,
        ),
        (
            "populate_runtime_track_cells_from_segments",
            "BuildLevel",
            "?BuildLevel@cRSubGame@@QAEXXZ",
            True,
        ),
        (
            "place_parcels_on_track",
            "PlaceParcels",
            "?PlaceParcels@cRSubGame@@QAEXXZ",
            True,
        ),
        (
            "select_track_tile_edge_variants",
            "SmoothTrack",
            "?SmoothTrack@cRSubGame@@QAEXXZ",
            True,
        ),
        (
            "promote_track_tiles_to_fringe_variants",
            "WarnTrack",
            "?WarnTrack@cRSubGame@@QAEXXZ",
            False,
        ),
        (
            "harmonize_center_lane_floor_slide_variants",
            "SlideSmoothTrack",
            "?SlideSmoothTrack@cRSubGame@@QAEXXZ",
            True,
        ),
        (
            "merge_track_tile_runs",
            "CondenseTrack",
            "?CondenseTrack@cRSubGame@@QAEXXZ",
            True,
        ),
        (
            "mark_track_warning_zones",
            "DeSaltTrack",
            "?DeSaltTrack@cRSubGame@@QAEXXZ",
            False,
        ),
        (
            "build_track_fringe_objects",
            "FringeEdgeTrack",
            "?FringeEdgeTrack@cRSubGame@@QAEXXZ",
            True,
        ),
    )
    matcher_header = (
        repo_root / "tools/match/include/subgame_runtime.h"
    ).read_text(encoding="utf-8")

    for windows_name, authored_name, symbol, has_ios_body in expected_members:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["android_symbol"] == f"cRSubGame::{authored_name}()"
        assert entry["android_body_count"] == 1
        if has_ios_body:
            assert entry["ios_symbol"] == f"cRSubGame::{authored_name}()"
            assert entry["ios_body_count"] == 1
        else:
            assert "ios_symbol" not in entry

        assert authored_name in functions_by_name[windows_name]["aliases"]
        assert f"void {authored_name}();" in matcher_header

        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert f"void cRSubGame::{authored_name}()" in scratch_source
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert f"FUNCTION={windows_name}\n" in scratch_config
        assert f"SYMBOL={symbol}\n" in scratch_config

    expected_lifecycle_members = (
        (
            "rebuild_track_runtime_from_segments",
            "GenerateLevel",
            "?GenerateLevel@cRSubGame@@QAEXH@Z",
        ),
        (
            "build_subgame_level",
            "StartLevel",
            "?StartLevel@cRSubGame@@QAEXH@Z",
        ),
    )
    for windows_name, authored_name, symbol in expected_lifecycle_members:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        expected_mobile_symbol = f"cRSubGame::{authored_name}(int)"
        assert entry["android_symbol"] == expected_mobile_symbol
        assert entry["ios_symbol"] == expected_mobile_symbol
        assert entry["android_body_count"] == 1
        assert entry["ios_body_count"] == 1
        assert authored_name in functions_by_name[windows_name]["aliases"]
        assert f"void {authored_name}(int level_index);" in matcher_header

        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert (
            f"void cRSubGame::{authored_name}(int level_index)"
            in scratch_source
        )
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert f"FUNCTION={windows_name}\n" in scratch_config
        assert f"SYMBOL={symbol}\n" in scratch_config

    generate_level = (
        repo_root
        / (
            "analysis/decompile/android/functions/"
            "00081744-_ZN9cRSubGame13GenerateLevelEi.c"
        )
    ).read_text(encoding="utf-8")
    ordered_calls = (
        "SmoothTrack(this);",
        "WarnTrack(this);",
        "SlideSmoothTrack(this);",
        "CondenseTrack(this);",
        "DeSaltTrack(this);",
        "FringeEdgeTrack(this);",
    )
    call_offsets = [generate_level.index(call) for call in ordered_calls]
    assert call_offsets == sorted(call_offsets)

    windows_dispatcher = (
        repo_root
        / (
            "tools/match/scratches/rebuild_track_runtime_from_segments/"
            "scratch.cpp"
        )
    ).read_text(encoding="utf-8")
    windows_calls = tuple(
        f"{authored_name}();"
        for _, authored_name, _, _ in expected_members
    )
    windows_offsets = [
        windows_dispatcher.index(call)
        for call in windows_calls
    ]
    assert windows_offsets == sorted(windows_offsets)


def test_mobile_subgame_lifecycle_recovers_authored_windows_members() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    matcher_header = (
        repo_root / "tools/match/include/subgame_runtime.h"
    ).read_text(encoding="utf-8")
    expected_members = (
        (
            "initialize_subgame",
            "Init",
            "?Init@cRSubGame@@QAEXXZ",
            True,
        ),
        (
            "reset_subgame",
            "ReSet",
            "?ReSet@cRSubGame@@QAEXXZ",
            False,
        ),
        (
            "destroy_subgame",
            "UnInit",
            "?UnInit@cRSubGame@@QAEXXZ",
            True,
        ),
        (
            "update_subgame",
            "AI",
            "?AI@cRSubGame@@QAEXXZ",
            True,
        ),
        (
            "remove_subgame_bods",
            "RemoveBods",
            "?RemoveBods@cRSubGame@@QAEXXZ",
            True,
        ),
        (
            "hide_gameplay_scores",
            "HideScores",
            "?HideScores@cRSubGame@@QAEXXZ",
            True,
        ),
        (
            "unhide_gameplay_scores",
            "UnHideScores",
            "?UnHideScores@cRSubGame@@QAEXXZ",
            False,
        ),
    )

    for windows_name, authored_name, symbol, has_ios_body in expected_members:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["android_symbol"] == f"cRSubGame::{authored_name}()"
        assert entry["android_body_count"] == 1
        if has_ios_body:
            assert entry["ios_symbol"] == f"cRSubGame::{authored_name}()"
            assert entry["ios_body_count"] == 1
        else:
            assert "ios_symbol" not in entry

        assert authored_name in functions_by_name[windows_name]["aliases"]
        assert f"void {authored_name}();" in matcher_header

        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert f"void cRSubGame::{authored_name}()" in scratch_source
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert f"FUNCTION={windows_name}\n" in scratch_config
        assert f"SYMBOL={symbol}\n" in scratch_config

    complete = entries["complete_subgame"]
    assert complete["status"] == "verified"
    assert complete["confidence"] == "high"
    assert complete["android_symbol"] == "cRSubGame::Complete(bool)"
    assert complete["ios_symbol"] == "cRSubGame::Complete(bool)"
    assert complete["android_body_count"] == 1
    assert complete["ios_body_count"] == 1
    assert "Complete" in functions_by_name["complete_subgame"]["aliases"]
    assert "void Complete(unsigned char completed);" in matcher_header

    complete_root = (
        repo_root / "tools/match/scratches/complete_subgame"
    )
    complete_source = (complete_root / "scratch.cpp").read_text(
        encoding="utf-8"
    )
    assert (
        "void cRSubGame::Complete(unsigned char completed)"
        in complete_source
    )
    complete_config = (complete_root / "scratch.conf").read_text(
        encoding="utf-8"
    )
    assert "FUNCTION=complete_subgame\n" in complete_config
    assert "SYMBOL=?Complete@cRSubGame@@QAEXE@Z\n" in complete_config

    windows_init = (
        repo_root / "tools/match/scratches/initialize_subgame/scratch.cpp"
    ).read_text(encoding="utf-8")
    android_init = (
        repo_root
        / (
            "analysis/decompile/android/functions/"
            "0007de9c-_ZN9cRSubGame4InitEv.c"
        )
    ).read_text(encoding="utf-8")
    assert "ReSet();" in windows_init
    assert "ReSet(this);" in android_init


def test_mobile_subgame_factories_recover_crsubgoldy_surface() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    matcher_header = (
        repo_root / "tools/match/include/subgame_runtime.h"
    ).read_text(encoding="utf-8")
    expected_factories = (
        (
            "spawn_track_health_pickup",
            "AddHealth",
            "cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)",
            0,
            "?AddHealth@cRSubGame@@QAEXPAUcRSubLoc@@PAVcRSubGoldy@@@Z",
        ),
        (
            "spawn_track_speedup",
            "AddSpeedUp",
            "cRSubGame::AddSpeedUp(cRSubLoc*, cRSubGoldy*)",
            0,
            "?AddSpeedUp@cRSubGame@@QAEXPAUcRSubLoc@@PAVcRSubGoldy@@@Z",
        ),
        (
            "spawn_track_jetpack_pickup",
            "AddJetPack",
            "cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)",
            1,
            "?AddJetPack@cRSubGame@@QAEXPAUcRSubLoc@@PAVcRSubGoldy@@@Z",
        ),
        (
            "spawn_track_garbage_hazard",
            "AddGarbage",
            "cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*)",
            1,
            "?AddGarbage@cRSubGame@@QAEXPAUcRSubLoc@@PAVcRSubGoldy@@@Z",
        ),
        (
            "spawn_slug_hazard",
            "AddSlug",
            "cRSubGame::AddSlug(cRSubLoc*, cRSubGoldy*)",
            1,
            "?AddSlug@cRSubGame@@QAEXPAUcRSubLoc@@PAVcRSubGoldy@@@Z",
        ),
        (
            "spawn_track_ring_or_special_effect",
            "AddRing",
            (
                "cRSubGame::AddRing("
                "cRSubLoc*, int, cRSubGoldy*, float)"
            ),
            1,
            "?AddRing@cRSubGame@@QAEXPAUcRSubLoc@@HPAVcRSubGoldy@@M@Z",
        ),
    )

    for (
        windows_name,
        authored_name,
        mobile_symbol,
        ios_body_count,
        object_symbol,
    ) in expected_factories:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["android_symbol"] == mobile_symbol
        assert entry["ios_symbol"] == mobile_symbol
        assert entry["android_body_count"] == 1
        assert entry["ios_body_count"] == ios_body_count
        assert authored_name in functions_by_name[windows_name]["aliases"]
        assert f"void {authored_name}(" in matcher_header

        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert f"void cRSubGame::{authored_name}(" in scratch_source
        assert "cRSubGoldy* " in scratch_source
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert f"FUNCTION={windows_name}\n" in scratch_config
        assert f"SYMBOL={object_symbol}\n" in scratch_config

    parcel = entries["spawn_track_parcel"]
    assert parcel["status"] == "verified"
    assert parcel["confidence"] == "high"
    assert parcel["android_symbol"] == (
        "cRSubGame::AddParcel(tVector*, cRSubGoldy*)"
    )
    assert parcel["ios_symbol"] == "cRSubGame::AddParcel(...)"
    assert parcel["android_body_count"] == 1
    assert parcel["ios_body_count"] == 1
    assert "AddParcel" in functions_by_name["spawn_track_parcel"]["aliases"]
    assert "Parcel* AddParcel(" in matcher_header

    parcel_root = repo_root / "tools/match/scratches/spawn_track_parcel"
    parcel_source = (parcel_root / "scratch.cpp").read_text(
        encoding="utf-8"
    )
    assert "Parcel* cRSubGame::AddParcel(" in parcel_source
    assert "cRSubGoldy*)" in parcel_source
    parcel_config = (parcel_root / "scratch.conf").read_text(
        encoding="utf-8"
    )
    assert "FUNCTION=spawn_track_parcel\n" in parcel_config
    assert (
        "SYMBOL=?AddParcel@cRSubGame@@QAEPAVParcel@@"
        "PAUtVector@@PAVcRSubGoldy@@@Z\n"
        in parcel_config
    )


def test_mobile_subgame_utilities_recover_authored_surface() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }
    subgame_header = (
        repo_root / "tools/match/include/subgame_runtime.h"
    ).read_text(encoding="utf-8")
    expected_methods = (
        (
            "is_neighbor_cell_solid",
            "TestLoc",
            "cRSubGame::TestLoc(cRSubLoc*, int, int)",
            "?TestLoc@cRSubGame@@QAE_NPAUcRSubLoc@@HH@Z",
        ),
        (
            "switch_track_mirror",
            "SwitchMirror",
            "cRSubGame::SwitchMirror()",
            "?SwitchMirror@cRSubGame@@QAEXXZ",
        ),
        (
            "normalize_segment_glyph_for_track_flags",
            "LevelConvert",
            "cRSubGame::LevelConvert(char, int, bool)",
            "?LevelConvert@cRSubGame@@QAEDDHD@Z",
        ),
        (
            "calc_slider_to_rate",
            "CalcSliderToRate",
            "cRSubGame::CalcSliderToRate(float)",
            "?CalcSliderToRate@cRSubGame@@QAEMM@Z",
        ),
        (
            "get_track_grid_cell_at_world_position",
            "LocFromPos",
            "cRSubGame::LocFromPos(tVector)",
            "?LocFromPos@cRSubGame@@QAEPAUcRSubLoc@@PAUtVector@@@Z",
        ),
        (
            "get_track_runtime_cell_at_world_z",
            "RowFromPos",
            "cRSubGame::RowFromPos(tVector)",
            "?RowFromPos@cRSubGame@@QAEPAUSubRow@@PAUtVector@@@Z",
        ),
        (
            "sample_track_floor_height_at_position",
            "GetY",
            "cRSubGame::GetY(tVector)",
            "?GetY@cRSubGame@@QAENPAUtVector@@@Z",
        ),
        (
            "set_subgame_rate",
            "SetRate",
            "cRSubGame::SetRate(float)",
            "?SetRate@cRSubGame@@QAEXM@Z",
        ),
        (
            "calc_subgame_rate",
            "CalcRate",
            "cRSubGame::CalcRate()",
            "?CalcRate@cRSubGame@@QAEXXZ",
        ),
        (
            "advance_blink_random",
            "BlinkRand",
            "cRSubGame::BlinkRand()",
            "?BlinkRand@cRSubGame@@QAENXZ",
        ),
        (
            "initialize_blink_random",
            "BlinkRandInit",
            "cRSubGame::BlinkRandInit()",
            "?BlinkRandInit@cRSubGame@@QAEXXZ",
        ),
        (
            "get_track_skirt_color",
            "GetSkirtColour",
            "cRSubGame::GetSkirtColour(tColourSmall*)",
            "?GetSkirtColour@cRSubGame@@QAEPAUtColour@@PAU2@@Z",
        ),
        (
            "place_challenge_parcels_on_track",
            "PlaceParcelsSurvival",
            "cRSubGame::PlaceParcelsSurvival()",
            "?PlaceParcelsSurvival@cRSubGame@@QAEXXZ",
        ),
        (
            "project_position_onto_track_attachment",
            "CalcRealPos",
            "cRSubGame::CalcRealPos(tVector&, float&)",
            "?CalcRealPos@cRSubGame@@QAEXPAUtVector@@PAM@Z",
        ),
    )

    for windows_name, authored_name, mobile_symbol, object_symbol in expected_methods:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert mobile_symbol in {
            entry.get("android_symbol"),
            entry.get("ios_symbol"),
        }
        assert f"cRSubGame_{authored_name}" in (
            functions_by_name[windows_name]["aliases"]
        )
        assert f"{authored_name}(" in subgame_header

        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert f"cRSubGame::{authored_name}(" in scratch_source
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert f"FUNCTION={windows_name}\n" in scratch_config
        assert f"SYMBOL={object_symbol}\n" in scratch_config
        assert object_symbol in references_by_name[windows_name]["aliases"]

    subgoldy = (
        repo_root / "tools/match/scratches/update_subgoldy/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "float sample_track_floor_height_at_position(" in subgoldy
    assert "SubgoldyFloorSamplerCallView" in subgoldy


def test_mobile_subloc_methods_recover_authored_surface() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }
    subloc_header = (
        repo_root / "tools/match/include/track_attachment_types.h"
    ).read_text(encoding="utf-8")
    expected_methods = (
        (
            "is_sub_loc_floor",
            "IsFloor",
            "cRSubLoc::IsFloor()",
            "bool IsFloor();",
            "?IsFloor@cRSubLoc@@QAE_NXZ",
        ),
        (
            "is_sub_loc_ramp",
            "IsRamp",
            "cRSubLoc::IsRamp()",
            "bool IsRamp();",
            "?IsRamp@cRSubLoc@@QAE_NXZ",
        ),
        (
            "is_sub_loc_empty",
            "IsEmpty",
            "cRSubLoc::IsEmpty()",
            "bool IsEmpty();",
            "?IsEmpty@cRSubLoc@@QAE_NXZ",
        ),
        (
            "is_sub_loc_slide",
            "IsSlide",
            "cRSubLoc::IsSlide()",
            "bool IsSlide();",
            "?IsSlide@cRSubLoc@@QAE_NXZ",
        ),
        (
            "remove_sub_loc",
            "Remove",
            "cRSubLoc::Remove()",
            "void Remove();",
            "?Remove@cRSubLoc@@QAEXXZ",
        ),
        (
            "update_sub_loc",
            "AI",
            "cRSubLoc::AI()",
            "void AI();",
            "?AI@cRSubLoc@@QAEXXZ",
        ),
        (
            "get_track_cell_row_index",
            "Yi",
            "cRSubLoc::Yi()",
            "int Yi();",
            "?Yi@cRSubLoc@@QAEHXZ",
        ),
    )

    for (
        windows_name,
        authored_name,
        mobile_symbol,
        header_declaration,
        object_symbol,
    ) in expected_methods:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert mobile_symbol in {
            entry.get("android_symbol"),
            entry.get("ios_symbol"),
        }
        assert f"cRSubLoc_{authored_name}" in (
            functions_by_name[windows_name]["aliases"]
        )
        assert header_declaration in subloc_header

        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert f"cRSubLoc::{authored_name}(" in scratch_source
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert f"FUNCTION={windows_name}\n" in scratch_config
        assert f"SYMBOL={object_symbol}\n" in scratch_config
        assert object_symbol in references_by_name[windows_name]["aliases"]

    for scratch_name in (
        "build_track_render_caches",
        "harmonize_center_lane_floor_slide_variants",
        "merge_track_tile_runs",
        "promote_track_tiles_to_fringe_variants",
    ):
        source = (
            repo_root
            / "tools/match/scratches"
            / scratch_name
            / "scratch.cpp"
        ).read_text(encoding="utf-8")
        assert "__fastcall is_sub_loc_" not in source


def test_mobile_tcolour_methods_recover_authored_surface() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }
    colour_header = (
        repo_root / "tools/match/include/sprite.h"
    ).read_text(encoding="utf-8")
    expected_methods = (
        (
            "set_color_rgba",
            "Set",
            "tColour::Set(float, float, float, float)",
            "tColour_SetRGBA",
            "?Set@tColour@@QAEPAU1@MMMM@Z",
        ),
        (
            "set_color_alpha",
            "Alpha",
            "tColour::Alpha(float)",
            "tColour_Alpha",
            "?Alpha@tColour@@QAEXM@Z",
        ),
        (
            "set_color_grayscale",
            "Grey",
            "tColour::Grey(float)",
            "tColour_Grey",
            "?Grey@tColour@@QAEXM@Z",
        ),
        (
            "set_color_rgb",
            "Set",
            "tColour::Set(float, float, float)",
            "tColour_SetRGB",
            "?Set@tColour@@QAEXMMM@Z",
        ),
        (
            "set_color_white",
            "White",
            "tColour::White()",
            "tColour_White",
            "?White@tColour@@QAEXXZ",
        ),
        (
            "set_color_black",
            "Black",
            "tColour::Black()",
            "tColour_Black",
            "?Black@tColour@@QAEXXZ",
        ),
    )

    for (
        windows_name,
        authored_name,
        mobile_symbol,
        alias,
        object_symbol,
    ) in expected_methods:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert mobile_symbol in {
            entry.get("android_symbol"),
            entry.get("ios_symbol"),
        }
        assert alias in functions_by_name[windows_name]["aliases"]
        assert f"{authored_name}(" in colour_header

        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert f"tColour::{authored_name}(" in scratch_source
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert f"FUNCTION={windows_name}\n" in scratch_config
        assert f"SYMBOL={object_symbol}\n" in scratch_config
        assert object_symbol in references_by_name[windows_name]["aliases"]

    old_names = (
        "set_color_rgba(",
        "set_color_alpha(",
        "set_color_grayscale(",
        "set_color_rgb(",
        "set_color_white(",
        "set_color_black(",
    )
    for path in (repo_root / "tools/match/scratches").rglob("*.cpp"):
        if "build" in path.parts:
            continue
        source = path.read_text(encoding="utf-8")
        assert not any(name in source for name in old_names)

    small_entry = entries["pack_color_rgba_u8"]
    assert small_entry["status"] == "verified"
    assert small_entry["confidence"] == "high"
    assert "tColourSmall::operator=(tColour const&)" in {
        small_entry.get("android_symbol"),
        small_entry.get("ios_symbol"),
    }
    assert (
        "tColourSmall_operator_assign_colour"
        in functions_by_name["pack_color_rgba_u8"]["aliases"]
    )
    assert "tColourSmall* operator=(const tColour& color);" in colour_header
    small_source = (
        repo_root / "tools/match/scratches/pack_color_rgba_u8/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert (
        "tColourSmall* tColourSmall::operator=(const tColour& color)"
        in small_source
    )
    small_config = (
        repo_root / "tools/match/scratches/pack_color_rgba_u8/scratch.conf"
    ).read_text(encoding="utf-8")
    small_symbol = "??4tColourSmall@@QAEPAU0@ABUtColour@@@Z"
    assert f"SYMBOL={small_symbol}\n" in small_config
    assert small_symbol in references_by_name["pack_color_rgba_u8"]["aliases"]
    for path in (repo_root / "tools/match/scratches").rglob("scratch.cpp"):
        if "build" in path.parts:
            continue
        assert "pack_color_rgba_u8(" not in path.read_text(encoding="utf-8")

    verified = load_json(
        repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json"
    )
    store_entry = next(
        entry
        for entry in verified["entries"]
        if entry["windows_name"] == "store_color4f"
    )
    store_source = (
        repo_root / "tools/match/scratches/store_color4f/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert store_entry["android_symbol"].startswith("tColour::tColour(")
    assert "not the exact Windows VC6 source shape" in store_entry["notes"]
    assert "void tColour::store_color4f(" in store_source
    assert "tColour::tColour(" not in store_source


def test_mobile_crobject_owners_recover_primary_structs() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }
    object_header = (
        repo_root / "tools/match/include/object_render_types.h"
    ).read_text(encoding="utf-8")
    object_fwd = (
        repo_root / "tools/match/include/object_fwd.h"
    ).read_text(encoding="utf-8")

    assert "struct cRObject {" in object_header
    assert "struct Object {" not in object_header
    assert "cRObject_must_be_0xdc" in object_header
    assert "struct cRObjects {" in object_header
    assert "struct ObjectList {" not in object_header
    assert "cRObjects_must_be_0x0c" in object_header
    assert "struct cRFaceQuad {" in object_header
    assert "struct ObjectFaceQuad {" not in object_header
    assert "cRFaceQuad_must_be_0x30" in object_header
    assert "ObjectFaceQuad_must_be_0x30" in object_header
    assert "cRFaceQuad* facequads;" in object_header
    assert "void RotateUVCCW();" in object_header
    assert "struct cRObject;" in object_fwd
    assert "typedef cRObject Object;" in object_fwd
    assert "struct cRObjects;" in object_fwd
    assert "typedef cRObjects ObjectList;" in object_fwd
    assert "struct cRFaceQuad;" in object_fwd
    assert "typedef cRFaceQuad ObjectFaceQuad;" in object_fwd

    authored_allocation_methods = (
        "void RequestVertices(int vertex_count);",
        "void RequestVerticesCopy();",
        "void CopyVertices();",
        "Vector3* RequestFaceQuadNormals();",
        "void RequestColours();",
        "void RequestFaceQuads(int facequad_count);",
        "void RequestFaceQuadTextureGroups(int group_count);",
        "void ApplyToon(int toon_flags);",
        "void RequestEdges(int edge_count);",
    )
    for declaration in authored_allocation_methods:
        assert declaration in object_header

    authored_geometry_methods = (
        "void CalcFaceQuadNormals();",
        "void CalcTextureGroups();",
        "void AddEdge(int vertex_a, int vertex_b, int normal_index);",
        "void CalcEdges();",
    )
    for declaration in authored_geometry_methods:
        assert declaration in object_header

    for descriptive_name in (
        "request_object_vertices",
        "request_object_vertices_copy",
        "copy_object_vertices",
        "request_object_facequad_normals",
        "request_object_vertex_colours",
        "request_object_facequads",
        "request_object_texture_groups",
        "apply_object_toon",
        "request_object_edges",
        "calc_object_facequad_normals",
        "calc_object_texture_groups",
        "add_object_edge",
        "calc_object_edges",
    ):
        assert f" {descriptive_name}(" not in object_header

    expected_owners = (
        (
            "initialize_object_constructor_thunk",
            "cRObject",
            "?initialize_object_constructor_thunk@cRObject@@QAEPAU1@XZ",
        ),
        (
            "initialize_object",
            "cRObject",
            "?initialize_object@cRObject@@QAEXXZ",
        ),
        (
            "request_object_vertices",
            "cRObject",
            "?RequestVertices@cRObject@@QAEXH@Z",
        ),
        (
            "copy_object_vertices",
            "cRObject",
            "?CopyVertices@cRObject@@QAEXXZ",
        ),
        (
            "request_object_vertices_copy",
            "cRObject",
            "?RequestVerticesCopy@cRObject@@QAEXXZ",
        ),
        (
            "request_object_facequad_normals",
            "cRObject",
            "?RequestFaceQuadNormals@cRObject@@QAEPAUtVector@@XZ",
        ),
        (
            "request_object_vertex_colours",
            "cRObject",
            "?RequestColours@cRObject@@QAEXXZ",
        ),
        (
            "request_object_facequads",
            "cRObject",
            "?RequestFaceQuads@cRObject@@QAEXH@Z",
        ),
        (
            "request_object_texture_groups",
            "cRObject",
            "?RequestFaceQuadTextureGroups@cRObject@@QAEXH@Z",
        ),
        (
            "apply_object_toon",
            "cRObject",
            "?ApplyToon@cRObject@@QAEXH@Z",
        ),
        (
            "calc_object_bounding_box",
            "cRObject",
            "?calc_object_bounding_box@cRObject@@QAEXXZ",
        ),
        (
            "calc_object_facequad_normals",
            "cRObject",
            "?CalcFaceQuadNormals@cRObject@@QAEXXZ",
        ),
        (
            "calc_object_facequad_normals_simple",
            "cRObject",
            "?calc_object_facequad_normals_simple@cRObject@@QAEHXZ",
        ),
        (
            "calc_object_texture_groups",
            "cRObject",
            "?CalcTextureGroups@cRObject@@QAEXXZ",
        ),
        (
            "request_object_edges",
            "cRObject",
            "?RequestEdges@cRObject@@QAEXH@Z",
        ),
        (
            "add_object_edge",
            "cRObject",
            "?AddEdge@cRObject@@QAEXHHH@Z",
        ),
        (
            "calc_object_edges",
            "cRObject",
            "?CalcEdges@cRObject@@QAEXXZ",
        ),
        (
            "request_object_animation",
            "cRObject",
            (
                "?RequestAnim@cRObject"
                "@@QAEXHPAVcRBodPos@@MH@Z"
            ),
        ),
        (
            "rotate_object_facequad_uv_pairs",
            "cRFaceQuad",
            "?RotateUVCCW@cRFaceQuad@@QAEXXZ",
        ),
        (
            "initialize_object_list",
            "cRObjects",
            "?Init@cRObjects@@QAEXH@Z",
        ),
        (
            "build_all_objects",
            "cRObjects",
            "?BuildObjects@cRObjects@@QAEXXZ",
        ),
        (
            "add_object_to_list",
            "cRObjects",
            "?Add@cRObjects@@QAEPAUcRObject@@XZ",
        ),
        (
            "replace_object_list_texture_refs",
            "cRObjects",
            (
                "?ReTextureObjects@cRObjects"
                "@@QAEXPAUcRTexture@@0@Z"
            ),
        ),
    )

    for windows_name, owner, object_symbol in expected_owners:
        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert f"{owner}::" in scratch_source
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert f"SYMBOL={object_symbol}\n" in scratch_config
        assert object_symbol in references_by_name[windows_name]["aliases"]

    verified_mobile_methods = {
        "initialize_object": "cRObject::cRObject()",
        "request_object_vertices": "cRObject::RequestVertices(int)",
        "copy_object_vertices": "cRObject::CopyVertices()",
        "request_object_vertices_copy": "cRObject::RequestVerticesCopy()",
        (
            "request_object_facequad_normals"
        ): "cRObject::RequestFaceQuadNormals()",
        "request_object_vertex_colours": "cRObject::RequestColours()",
        "request_object_facequads": "cRObject::RequestFaceQuads(int)",
        (
            "request_object_texture_groups"
        ): "cRObject::RequestFaceQuadTextureGroups(int)",
        "apply_object_toon": "cRObject::ApplyToon(int)",
        (
            "calc_object_facequad_normals"
        ): "cRObject::CalcFaceQuadNormals()",
        "calc_object_texture_groups": "cRObject::CalcTextureGroups()",
        "request_object_edges": "cRObject::RequestEdges(int)",
        "add_object_edge": "cRObject::AddEdge(int, int, int)",
        "calc_object_edges": "cRObject::CalcEdges()",
        (
            "rotate_object_facequad_uv_pairs"
        ): "cRFaceQuad::RotateUVCCW()",
        (
            "request_object_animation"
        ): "cRObject::RequestAnim(int, cRBodPos*, float, int)",
        "initialize_object_list": "cRObjects::Init(int)",
        "build_all_objects": "cRObjects::BuildObjects()",
        "add_object_to_list": "cRObjects::Add()",
        (
            "replace_object_list_texture_refs"
        ): "cRObjects::ReTextureObjects",
    }
    for windows_name, mobile_symbol in verified_mobile_methods.items():
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert mobile_symbol in {
            entry.get("android_symbol"),
            entry.get("ios_symbol"),
        }

    request_anim_source = (
        repo_root
        / "tools/match/scratches/request_object_animation/scratch.cpp"
    ).read_text(encoding="utf-8")
    animation_loader_source = (
        repo_root
        / "tools/match/scratches/load_x_animation_clip/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "void cRObject::RequestAnim(" in request_anim_source
    assert "object->RequestAnim(" in animation_loader_source
    assert "cRObject::request_object_animation" not in request_anim_source
    assert "object->request_object_animation" not in animation_loader_source

    rotate_facequad_source = (
        repo_root
        / "tools/match/scratches/rotate_object_facequad_uv_pairs/scratch.cpp"
    ).read_text(encoding="utf-8")
    backdrop_tile_source = (
        repo_root
        / "tools/match/scratches/initialize_backdrop_tile_quad/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "void cRFaceQuad::RotateUVCCW()" in rotate_facequad_source
    assert "rotate_object_facequad_uv_pairs(" not in rotate_facequad_source
    assert backdrop_tile_source.count("quad->RotateUVCCW();") == 6
    assert "quad->rotate_object_facequad_uv_pairs();" not in backdrop_tile_source

    object_manager_sources = {
        windows_name: (
            repo_root
            / "tools/match/scratches"
            / windows_name
            / "scratch.cpp"
        ).read_text(encoding="utf-8")
        for windows_name in (
            "initialize_object_list",
            "build_all_objects",
            "add_object_to_list",
            "replace_object_list_texture_refs",
        )
    }
    assert "void cRObjects::Init(int object_capacity)" in (
        object_manager_sources["initialize_object_list"]
    )
    assert "void cRObjects::BuildObjects()" in (
        object_manager_sources["build_all_objects"]
    )
    assert "cRObject* cRObjects::Add()" in (
        object_manager_sources["add_object_to_list"]
    )
    assert "void cRObjects::ReTextureObjects(" in (
        object_manager_sources["replace_object_list_texture_refs"]
    )

    constructor_source = (
        repo_root / "tools/match/scratches/initialize_object/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "void cRObject::initialize_object()" in constructor_source
    assert "cRObject::cRObject()" not in constructor_source

    gl_builder_source = (
        repo_root
        / "tools/match/scratches/build_object_texture_group_buffers/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "void build_object_texture_group_buffers(Object* object)" in (
        gl_builder_source
    )
    assert "cRObject::BuildGLVertexArray" not in gl_builder_source

    for header_name in (
        "bod_types.h",
        "object_animation_types.h",
        "player.h",
        "segment_cache.h",
        "vapour.h",
    ):
        header = (
            repo_root / "tools/match/include" / header_name
        ).read_text(encoding="utf-8")
        assert '#include "object_fwd.h"' in header
        assert "struct Object;" not in header


def test_mobile_crdistort_recovers_primary_owner_and_methods() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }
    object_header = (
        repo_root / "tools/match/include/object_render_types.h"
    ).read_text(encoding="utf-8")

    assert "struct cRDistort {" in object_header
    assert "struct Distort {" not in object_header
    assert "void Init();" in object_header
    assert "void Build(cRObject* object);" in object_header
    assert "cRDistort_must_be_0x14" in object_header
    assert "typedef cRDistort Distort;" in object_header
    assert "typedef cRDistort ObjectDistort;" in object_header
    assert "Distort_must_be_0x14" in object_header
    assert "cRDistort distort; // +0x80" in object_header

    expected_methods = (
        (
            "initialize_object_distort",
            "Init",
            "?Init@cRDistort@@QAEXXZ",
            "cRDistort::Init()",
        ),
        (
            "apply_distort_to_object",
            "Build",
            "?Build@cRDistort@@QAEXPAUcRObject@@@Z",
            "cRDistort::Build(cRObject*)",
        ),
    )
    for windows_name, method_name, windows_symbol, mobile_symbol in (
        expected_methods
    ):
        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        entry = entries[windows_name]

        assert f"cRDistort::{method_name}(" in scratch_source
        assert f"SYMBOL={windows_symbol}\n" in scratch_config
        assert windows_symbol in references_by_name[windows_name]["aliases"]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["android_symbol"] == mobile_symbol

    assert entries["initialize_object_distort"]["ios_symbol"] == (
        "cRDistort::Init()"
    )

    subgoldy_source = (
        repo_root
        / "tools/match/scratches/initialize_subgoldy/scratch.cpp"
    ).read_text(encoding="utf-8")
    refresh_source = (
        repo_root
        / "tools/match/scratches/refresh_object_vertex_buffer/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "presentation.object->distort.Init();" in subgoldy_source
    assert "object->distort.Build(object);" in refresh_source
    assert ".initialize_object_distort();" not in subgoldy_source
    assert ".apply_distort_to_object(object);" not in refresh_source


def test_mobile_crduplicatevertices_recovers_primary_owner_and_methods() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }
    duplicate_header = (
        repo_root / "tools/match/include/duplicate_vertices.h"
    ).read_text(encoding="utf-8")
    directx_header = (
        repo_root / "tools/match/include/directx_loader.h"
    ).read_text(encoding="utf-8")

    assert "class cRDuplicateVertices {" in duplicate_header
    assert "class DuplicateVertices {" not in duplicate_header
    assert "void* Init(int count);" in duplicate_header
    assert "void Clean(int unused);" in duplicate_header
    assert "typedef cRDuplicateVertices DuplicateVertices;" in (
        duplicate_header
    )
    assert "cRDuplicateVertices_must_be_0x8" in duplicate_header
    assert "DuplicateVertices_must_be_0x8" in duplicate_header
    assert "cRDuplicateVertices duplicate_vertices; // +0x5e08" in (
        directx_header
    )

    expected_methods = (
        (
            "initialize_duplicate_vertices",
            "Init",
            "?Init@cRDuplicateVertices@@QAEPAXH@Z",
            "cRDuplicateVertices::Init(int)",
        ),
        (
            "clean_duplicate_vertices",
            "Clean",
            "?Clean@cRDuplicateVertices@@QAEXH@Z",
            "cRDuplicateVertices::Clean(int)",
        ),
    )
    for windows_name, method_name, windows_symbol, mobile_symbol in (
        expected_methods
    ):
        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        entry = entries[windows_name]

        assert f"cRDuplicateVertices::{method_name}(" in scratch_source
        assert f"SYMBOL={windows_symbol}\n" in scratch_config
        assert windows_symbol in references_by_name[windows_name]["aliases"]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["android_symbol"] == mobile_symbol

    assert entries["initialize_duplicate_vertices"]["ios_symbol"] == (
        "cRDuplicateVertices::Init(int)"
    )

    directx_init_source = (
        repo_root
        / "tools/match/scratches/initialize_directx_loader/scratch.cpp"
    ).read_text(encoding="utf-8")
    animation_source = (
        repo_root
        / "tools/match/scratches/load_x_animation_clip/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "duplicate_vertices.Init(2000);" in directx_init_source
    assert "duplicate_vertices.Clean(keyframe_count);" in animation_source
    assert ".initialize_duplicate_vertices(" not in directx_init_source
    assert ".clean_duplicate_vertices(" not in animation_source


def test_mobile_tvector_methods_recover_authored_surface() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }
    vector_header = (
        repo_root / "tools/match/include/vector3.h"
    ).read_text(encoding="utf-8")
    expected_methods = (
        (
            "multiply_vector_by_matrix_copy",
            "tVector::operator*(tMatrix const&) const",
            "tVector_operator_multiply",
            "tVector::operator*(",
            "tVector operator*(const tMatrix& matrix) const;",
            "??DtVector@@QBE?AU0@ABUtMatrix@@@Z",
        ),
        (
            "dot_vectors",
            "tVector::Dot(tVector const&, tVector const&)",
            "tVector_DotStatic",
            "tVector::Dot(",
            "static double __stdcall Dot(",
            "?Dot@tVector@@SGNABU1@0@Z",
        ),
        (
            "dot_vector",
            "tVector::Dot(tVector const&)",
            "tVector_Dot",
            "tVector::Dot(",
            "float Dot(const tVector& rhs);",
            "?Dot@tVector@@QAEMABU1@@Z",
        ),
        (
            "multiply_vector_by_matrix",
            "tVector::operator*=(tMatrix)",
            "tVector_operator_multiply_assign",
            "tVector::operator*=(",
            "void operator*=(tMatrix matrix);",
            "??XtVector@@QAEXUtMatrix@@@Z",
        ),
        (
            "rotate_vector_by_matrix",
            "tVector::Rotate(tMatrix const&)",
            "tVector_Rotate",
            "tVector::Rotate(",
            "tVector& Rotate(const tMatrix& matrix);",
            "?Rotate@tVector@@QAEAAU1@ABUtMatrix@@@Z",
        ),
        (
            "normalize_vector",
            "tVector::Normalize()",
            "tVector_Normalize",
            "tVector::Normalize(",
            "float Normalize();",
            "?Normalize@tVector@@QAEMXZ",
        ),
        (
            "vector_magnitude",
            "tVector::Magnitude() const",
            "tVector_Magnitude",
            "tVector::Magnitude(",
            "float Magnitude() const;",
            "?Magnitude@tVector@@QBEMXZ",
        ),
        (
            "normalize_vector_from_source",
            "tVector::Normalize(tVector const&)",
            "tVector_NormalizeFromSource",
            "tVector::Normalize(",
            "float Normalize(const tVector& source);",
            "?Normalize@tVector@@QAEMABU1@@Z",
        ),
        (
            "cross_vectors",
            "tVector::Cross(tVector const&, tVector const&)",
            "tVector_Cross",
            "tVector::Cross(",
            "void Cross(const tVector& lhs, const tVector& rhs);",
            "?Cross@tVector@@QAEXABU1@0@Z",
        ),
    )

    for (
        windows_name,
        mobile_symbol,
        alias,
        source_spelling,
        header_declaration,
        object_symbol,
    ) in expected_methods:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert mobile_symbol in {
            entry.get("android_symbol"),
            entry.get("ios_symbol"),
        }
        assert alias in functions_by_name[windows_name]["aliases"]
        assert header_declaration in vector_header

        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert source_spelling in scratch_source
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert f"FUNCTION={windows_name}" in scratch_config
        assert f"SYMBOL={object_symbol}\n" in scratch_config
        assert object_symbol in references_by_name[windows_name]["aliases"]

    assert "struct tVector {" in vector_header
    assert "typedef tVector Vector3;" in vector_header
    assert "tVector_must_be_0x0c" in vector_header
    assert "struct Vector3 {" not in vector_header
    assert "void cross_vectors(const tVector* lhs, const tVector* rhs);" in (
        vector_header
    )

    old_member_names = (
        "dot_vectors",
        "dot_vector",
        "normalize_vector",
        "normalize_vector_from_source",
        "vector_magnitude",
        "rotate_vector_by_matrix",
    )
    for path in (repo_root / "tools/match/scratches").rglob("*.cpp"):
        if "build" in path.parts:
            continue
        source = path.read_text(encoding="utf-8")
        for name in old_member_names:
            assert f".{name}(" not in source
            assert f"->{name}(" not in source
            assert f"::{name}(" not in source

    zero_source = (
        repo_root / "tools/match/scratches/zero_vector3/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "int tVector::zero_vector3()" in zero_source
    assert entries["zero_vector3"]["status"] == "unverified"


def test_mobile_tmatrix_methods_recover_authored_surface() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }
    matrix_header = (
        repo_root / "tools/match/include/transform_matrix.h"
    ).read_text(encoding="utf-8")
    matrix_fwd = (
        repo_root / "tools/match/include/transform_matrix_fwd.h"
    ).read_text(encoding="utf-8")
    expected_methods = (
        (
            "initialize_uniform_scale_matrix",
            "tMatrix::tMatrix(float)",
            "tMatrix_ctor_scale",
            "tMatrix::tMatrix(",
            "tMatrix(float scale);",
            "??0tMatrix@@QAE@M@Z",
        ),
        (
            "rotate_matrix_world_x",
            "tMatrix::RotLocalX(float)",
            "tMatrix_RotLocalX",
            "tMatrix::RotLocalX(",
            "void RotLocalX(float angle);",
            "?RotLocalX@tMatrix@@QAEXM@Z",
        ),
        (
            "rotate_matrix_world_y",
            "tMatrix::RotLocalY(float)",
            "tMatrix_RotLocalY",
            "tMatrix::RotLocalY(",
            "void RotLocalY(float angle);",
            "?RotLocalY@tMatrix@@QAEXM@Z",
        ),
        (
            "rotate_matrix_world_z",
            "tMatrix::RotLocalZ(float)",
            "tMatrix_RotLocalZ",
            "tMatrix::RotLocalZ(",
            "void RotLocalZ(float angle);",
            "?RotLocalZ@tMatrix@@QAEXM@Z",
        ),
        (
            "initialize_matrix_from_values",
            (
                "tMatrix::tMatrix(float, float, float, float, float, "
                "float, float, float, float, float, float, float, "
                "float, float, float, float)"
            ),
            "tMatrix_ctor_values",
            "tMatrix::tMatrix(",
            "float m30, float m31, float m32, float m33); // @ 0x44cfe0",
            "??0tMatrix@@QAE@MMMMMMMMMMMMMMMM@Z",
        ),
        (
            "multiply_matrices",
            "tMatrix::Multiply(tMatrix const&, tMatrix const&)",
            "tMatrix_MultiplyPair",
            "tMatrix::Multiply(",
            "void Multiply(const tMatrix& lhs, const tMatrix& rhs);",
            "?Multiply@tMatrix@@QAEXABU1@0@Z",
        ),
        (
            "multiply_matrix_assign",
            "tMatrix::operator*=(tMatrix const&)",
            "tMatrix_operator_multiply_assign",
            "tMatrix::operator*=(",
            "void operator*=(const tMatrix& rhs);",
            "??XtMatrix@@QAEXABU0@@Z",
        ),
        (
            "multiply_matrix",
            "tMatrix::Multiply(tMatrix const&)",
            "tMatrix_Multiply",
            "tMatrix::Multiply(",
            "void Multiply(const tMatrix& rhs);",
            "?Multiply@tMatrix@@QAEXABU1@@Z",
        ),
        (
            "premultiply_matrix_in_place",
            "tMatrix::PreMultiply(tMatrix const&)",
            "tMatrix_PreMultiply",
            "tMatrix::PreMultiply(",
            "void PreMultiply(const tMatrix& lhs);",
            "?PreMultiply@tMatrix@@QAEXABU1@@Z",
        ),
        (
            "set_matrix_identity",
            "tMatrix::Identity()",
            "tMatrix_Identity",
            "tMatrix::Identity(",
            "void Identity();",
            "?Identity@tMatrix@@QAEXXZ",
        ),
        (
            "set_matrix_rotation_identity",
            "tMatrix::RotIdentity()",
            "tMatrix_RotIdentity",
            "tMatrix::RotIdentity(",
            "void RotIdentity();",
            "?RotIdentity@tMatrix@@QAEXXZ",
        ),
        (
            "invert_matrix_in_place",
            "tMatrix::Invert()",
            "tMatrix_Invert",
            "tMatrix::Invert(",
            "void Invert();",
            "?Invert@tMatrix@@QAEXXZ",
        ),
        (
            "invert_matrix_from_source",
            "tMatrix::Invert(tMatrix const&)",
            "tMatrix_InvertFromSource",
            "tMatrix::Invert(",
            "void Invert(const tMatrix& source);",
            "?Invert@tMatrix@@QAEXABU1@@Z",
        ),
        (
            "orthogonalize_matrix",
            "tMatrix::Orthoganalize()",
            "tMatrix_Orthoganalize",
            "tMatrix::Orthoganalize(",
            "void Orthoganalize();",
            "?Orthoganalize@tMatrix@@QAEXXZ",
        ),
        (
            "set_matrix_z_direction",
            "tMatrix::SetZDir(tVector const&)",
            "tMatrix_SetZDir",
            "tMatrix::SetZDir(",
            "void SetZDir(const tVector& direction);",
            "?SetZDir@tMatrix@@QAEXABUtVector@@@Z",
        ),
        (
            "look_at_point",
            "tMatrix::LookAt(tVector const&)",
            "tMatrix_LookAt",
            "tMatrix::LookAt(",
            "void LookAt(const tVector& target);",
            "?LookAt@tMatrix@@QAEXABUtVector@@@Z",
        ),
        (
            "initialize_matrix_from_quaternion",
            "tMatrix::tMatrix(tQuaternian const&)",
            "tMatrix_ctor_quaternion",
            "tMatrix::tMatrix(",
            "tMatrix(const tQuaternian& quaternion);",
            "??0tMatrix@@QAE@ABUtQuaternian@@@Z",
        ),
        (
            "interpolate_matrix_rotation",
            "tMatrix::Interpolate(float)",
            "tMatrix_Interpolate",
            "tMatrix::Interpolate(",
            "void Interpolate(float alpha);",
            "?Interpolate@tMatrix@@QAEXM@Z",
        ),
        (
            "linear_interpolate_matrix",
            (
                "tMatrix::LinearInterpolate("
                "tMatrix const&, tMatrix const&, float)"
            ),
            "tMatrix_LinearInterpolate",
            "tMatrix::LinearInterpolate(",
            "void LinearInterpolate(",
            "?LinearInterpolate@tMatrix@@QAEXABU1@0M@Z",
        ),
    )

    for (
        windows_name,
        mobile_symbol,
        alias,
        source_spelling,
        header_declaration,
        object_symbol,
    ) in expected_methods:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert mobile_symbol in {
            entry.get("android_symbol"),
            entry.get("ios_symbol"),
        }
        assert alias in functions_by_name[windows_name]["aliases"]
        assert header_declaration in matrix_header

        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert source_spelling in scratch_source
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert f"FUNCTION={windows_name}" in scratch_config
        assert f"SYMBOL={object_symbol}\n" in scratch_config
        assert object_symbol in references_by_name[windows_name]["aliases"]

    assert "struct tMatrix {" in matrix_header
    assert "struct TransformMatrix {" not in matrix_header
    assert "tMatrix_must_be_0x40" in matrix_header
    assert "struct tMatrix;" in matrix_fwd
    assert "typedef tMatrix TransformMatrix;" in matrix_fwd
    assert "authored spelling" in matrix_header

    old_member_names = (
        "rotate_matrix_local_x",
        "rotate_matrix_local_y",
        "rotate_matrix_local_z",
        "multiply_matrices",
        "multiply_matrix",
        "premultiply_matrix_in_place",
        "set_matrix_identity",
        "set_matrix_rotation_identity",
        "invert_matrix_in_place",
        "invert_matrix_from_source",
        "linear_interpolate_matrix",
        "interpolate_matrix_rotation",
        "orthogonalize_matrix",
        "set_matrix_z_direction",
        "look_at_point",
    )
    for path in (repo_root / "tools/match/scratches").rglob("*.cpp"):
        if "build" in path.parts:
            continue
        source = path.read_text(encoding="utf-8")
        for name in old_member_names:
            assert f".{name}(" not in source
            assert f"->{name}(" not in source
            assert f"::{name}(" not in source


def test_mobile_tquaternian_and_taxis_recover_authored_owners() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }
    quaternion_header = (
        repo_root / "tools/match/include/quaternion.h"
    ).read_text(encoding="utf-8")
    quaternion_fwd = (
        repo_root / "tools/match/include/quaternion_fwd.h"
    ).read_text(encoding="utf-8")
    axis_header = (
        repo_root / "tools/match/include/axis.h"
    ).read_text(encoding="utf-8")
    axis_fwd = (
        repo_root / "tools/match/include/axis_fwd.h"
    ).read_text(encoding="utf-8")

    assert "struct tQuaternian {" in quaternion_header
    assert "typedef tQuaternian Quaternion;" in quaternion_fwd
    assert "struct tAxis {" in axis_header
    assert "typedef tAxis AxisAngle;" in axis_fwd
    assert "typedef tAxis Axis;" in axis_fwd

    expected_methods = (
        (
            "initialize_quaternion_from_axis",
            "tQuaternian::tQuaternian(tAxis const&)",
            "tQuaternian_operator_assign_axis",
            "void tQuaternian::operator=(const tAxis& axis)",
            "void operator=(const tAxis& axis);",
            "??4tQuaternian@@QAEXABUtAxis@@@Z",
        ),
        (
            "initialize_axis_from_quaternion",
            "tAxis::operator=(tQuaternian const&)",
            "tAxis_operator_assign_quaternion",
            "void tAxis::operator=(const tQuaternian& quaternion)",
            "void operator=(const tQuaternian& quaternion);",
            "??4tAxis@@QAEXABUtQuaternian@@@Z",
        ),
        (
            "initialize_quaternion_from_matrix",
            "tQuaternian::tQuaternian(tMatrix const&)",
            "tQuaternian_ctor_matrix",
            "tQuaternian::tQuaternian(const tMatrix& matrix)",
            "tQuaternian(const tMatrix& matrix);",
            "??0tQuaternian@@QAE@ABUtMatrix@@@Z",
        ),
    )

    for (
        windows_name,
        mobile_symbol,
        alias,
        source_spelling,
        header_declaration,
        object_symbol,
    ) in expected_methods:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert mobile_symbol in {
            entry.get("android_symbol"),
            entry.get("ios_symbol"),
        }
        assert alias in functions_by_name[windows_name]["aliases"]
        assert object_symbol in references_by_name[windows_name]["aliases"]

        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert source_spelling in scratch_source
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert f"SYMBOL={object_symbol}\n" in scratch_config

        owner_header = (
            quaternion_header
            if windows_name != "initialize_axis_from_quaternion"
            else axis_header
        )
        assert header_declaration in owner_header

    quaternion_axis_source = (
        repo_root
        / "tools/match/scratches/initialize_quaternion_from_axis/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "void tQuaternian::operator=" in quaternion_axis_source
    assert "tQuaternian::tQuaternian(const tAxis&" not in quaternion_axis_source

    trivial_aliases = references_by_name["noop_this_constructor"]["aliases"]
    assert "??0tAxis@@QAE@XZ" in trivial_aliases
    assert "??0tQuaternian@@QAE@XZ" in trivial_aliases


def test_mobile_subgoldy_methods_recover_authored_surface() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }
    player_header = (
        repo_root / "tools/match/include/player.h"
    ).read_text(encoding="utf-8")
    expected_methods = (
        (
            "health_collect_particles",
            "HealthCollect",
            "cRSubGoldy::HealthCollect(cRSubHealth*)",
            "?HealthCollect@cRSubGoldy@@QAEXPAVcRSubHealth@@@Z",
        ),
        (
            "initialize_subgoldy",
            "Init",
            "cRSubGoldy::Init(int)",
            "?Init@cRSubGoldy@@QAEXH@Z",
        ),
        (
            "show_subgoldy_lives",
            "ShowLives",
            "cRSubGoldy::ShowLives()",
            "?ShowLives@cRSubGoldy@@QAEXXZ",
        ),
        (
            "update_subgoldy",
            "AI",
            "cRSubGoldy::AI()",
            "?AI@cRSubGoldy@@QAEXXZ",
        ),
        (
            "initialize_subgoldy_ghost",
            "GhostInit",
            "cRSubGoldy::GhostInit(int)",
            "?GhostInit@cRSubGoldy@@QAEXH@Z",
        ),
        (
            "set_subgoldy_ghost_z",
            "GhostDraw",
            "cRSubGoldy::GhostDraw(float)",
            "?GhostDraw@cRSubGoldy@@QAEXM@Z",
        ),
        (
            "add_subgoldy_score",
            "ScoreAdd",
            "cRSubGoldy::ScoreAdd(int, int)",
            "?ScoreAdd@cRSubGoldy@@QAEXHH@Z",
        ),
        (
            "clear_subgoldy_score_buckets",
            "ScoreStatsInit",
            "cRSubGoldy::ScoreStatsInit()",
            "?ScoreStatsInit@cRSubGoldy@@QAEXXZ",
        ),
        (
            "display_score_stats",
            "ScoreStatsDisplay",
            "cRSubGoldy::ScoreStatsDisplay()",
            "?ScoreStatsDisplay@cRSubGoldy@@QAEXXZ",
        ),
        (
            "initialize_subgoldy_resurrect",
            "RessurectInit",
            "cRSubGoldy::RessurectInit(int)",
            "?RessurectInit@cRSubGoldy@@QAEXH@Z",
        ),
        (
            "update_subgoldy_resurrect",
            "RessurectAI",
            "cRSubGoldy::RessurectAI()",
            "?RessurectAI@cRSubGoldy@@QAEXXZ",
        ),
        (
            "handle_subgoldy_collisions",
            "Collision",
            "cRSubGoldy::Collision()",
            "?Collision@cRSubGoldy@@QAEXXZ",
        ),
        (
            "kill_subgoldy",
            "Kill",
            "cRSubGoldy::Kill()",
            "?Kill@cRSubGoldy@@QAEXXZ",
        ),
        (
            "initialize_subgoldy_death",
            "DeathInit",
            "cRSubGoldy::DeathInit()",
            "?DeathInit@cRSubGoldy@@QAEXXZ",
        ),
    )

    for windows_name, authored_name, mobile_symbol, object_symbol in expected_methods:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert mobile_symbol in {
            entry.get("android_symbol"),
            entry.get("ios_symbol"),
        }
        assert f"cRSubGoldy_{authored_name}" in (
            functions_by_name[windows_name]["aliases"]
        )
        assert f"void {authored_name}(" in player_header

        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert f"void cRSubGoldy::{authored_name}(" in scratch_source
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert f"FUNCTION={windows_name}\n" in scratch_config
        assert f"SYMBOL={object_symbol}\n" in scratch_config
        assert object_symbol in references_by_name[windows_name]["aliases"]


def test_mobile_cutscene_and_subhover_recover_authored_owners() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {entry["windows_name"]: entry for entry in crosswalk["entries"]}
    functions = load_json(repo_root / "analysis/symbols/gameplay-functions.json")
    functions_by_name = {
        entry["name"]: entry for entry in functions["functions"]
    }
    references = load_json(repo_root / "analysis/symbols/gameplay-references.json")
    references_by_name = {
        entry["name"]: entry for entry in references["symbols"]
    }
    include_root = repo_root / "tools/match/include"
    scratch_root = repo_root / "tools/match/scratches"
    cutscene_header = (include_root / "cut_scene.h").read_text(encoding="utf-8")
    subhover_header = (include_root / "sub_hover.h").read_text(encoding="utf-8")
    player_header = (include_root / "player.h").read_text(encoding="utf-8")

    assert "class cRCutScene {" in cutscene_header
    assert "typedef cRCutScene CutScene;" in cutscene_header
    assert "class CutScene {" not in cutscene_header
    assert "void Init();" in cutscene_header
    assert "void AI();" in cutscene_header
    assert "cRCutScene cutscene;" in player_header

    assert "class cRSubHover {" in subhover_header
    assert "typedef cRSubHover SubHover;" in subhover_header
    assert "class SubHover {" not in subhover_header
    for declaration in (
        "void Init(int player_slot);",
        "void On();",
        "void End();",
        "void JetUnInit();",
        "void JetInit();",
        "void Jets();",
        "void AI();",
        "void Hover(Vector3& position, float progress);",
    ):
        assert declaration in subhover_header
    for retired_name in (
        "initialize_jetpack_gauge",
        "arm_jetpack_gauge",
        "end_jetpack_hover",
        "uninit_jet_particles",
        "initialize_jet_particles",
        "update_jet_particles",
        "update_jetpack_gauge",
        "spawn_track_speedup",
    ):
        assert retired_name not in subhover_header
    assert "cRSubHover sub_hover;" in player_header

    expected_methods = (
        ("initialize_cutscene_ai", "cRCutScene::Init()", "cRCutScene_Init",
         "void cRCutScene::Init()", "?Init@cRCutScene@@QAEXXZ"),
        ("update_cutscene", "cRCutScene::AI()", "cRCutScene_AI",
         "void cRCutScene::AI()", "?AI@cRCutScene@@QAEXXZ"),
        ("end_jetpack_hover", "cRSubHover::End()", "cRSubHover_End",
         "void cRSubHover::End()", "?End@cRSubHover@@QAEXXZ"),
        ("update_jetpack_gauge", "cRSubHover::AI()", "cRSubHover_AI",
         "void cRSubHover::AI()", "?AI@cRSubHover@@QAEXXZ"),
        ("uninit_jet_particles", "cRSubHover::JetUnInit()",
         "cRSubHover_JetUnInit", "void cRSubHover::JetUnInit()",
         "?JetUnInit@cRSubHover@@QAEXXZ"),
        ("initialize_jet_particles", "cRSubHover::JetInit()",
         "cRSubHover_JetInit", "void cRSubHover::JetInit()",
         "?JetInit@cRSubHover@@QAEXXZ"),
        ("update_jet_particles", "cRSubHover::Jets()", "cRSubHover_Jets",
         "void cRSubHover::Jets()", "?Jets@cRSubHover@@QAEXXZ"),
        ("initialize_jetpack_gauge", "cRSubHover::Init(int)",
         "cRSubHover_Init", "void cRSubHover::Init(int player_slot)",
         "?Init@cRSubHover@@QAEXH@Z"),
        ("arm_jetpack_gauge", "cRSubHover::On()", "cRSubHover_On",
         "void cRSubHover::On()", "?On@cRSubHover@@QAEXXZ"),
    )
    for windows_name, mobile_symbol, alias, definition, object_symbol in expected_methods:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["android_symbol"] == mobile_symbol
        assert alias in functions_by_name[windows_name]["aliases"]
        assert object_symbol in references_by_name[windows_name]["aliases"]
        source = (scratch_root / windows_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        config = (scratch_root / windows_name / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert definition in source
        assert f"SYMBOL={object_symbol}\n" in config

    folded_aliases = references_by_name["spawn_track_speedup"]["aliases"]
    assert "?AddSpeedUp@cRSubGame@@QAEXPAUcRSubLoc@@PAVcRSubGoldy@@@Z" in folded_aliases
    assert "?Hover@cRSubHover@@QAEXAAUtVector@@M@Z" in folded_aliases
    assert "cRSubHover_Hover" in functions_by_name["spawn_track_speedup"]["aliases"]

    caller_expectations = {
        "initialize_subgoldy": ("presentation.cutscene.Init();", "sub_hover.Init(gauge_slot);"),
        "update_snail_presentation": ("cutscene.AI();", "sub_hover.Jets();"),
        "handle_subgoldy_collisions": ("sub_hover.On();",),
        "release_snail_weapons": ("sub_hover.End();",),
        "update_subgoldy": ("sub_hover.End();", "sub_hover.AI();"),
        "update_jetpack_gauge": ("Hover(player->transform.position, progress);",),
    }
    for scratch_name, expected_calls in caller_expectations.items():
        source = (scratch_root / scratch_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        for expected_call in expected_calls:
            assert expected_call in source


def test_mobile_tip_family_recovers_authored_owners() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {entry["windows_name"]: entry for entry in crosswalk["entries"]}
    functions = load_json(repo_root / "analysis/symbols/gameplay-functions.json")
    functions_by_name = {
        entry["name"]: entry for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry for entry in references["symbols"]
    }
    include_root = repo_root / "tools/match/include"
    scratch_root = repo_root / "tools/match/scratches"
    header = (include_root / "tip_manager.h").read_text(encoding="utf-8")

    for declaration in (
        "struct cRTipData {",
        "class cRTip {",
        "class cRTipManager : public BodBase {",
        "typedef cRTipData TipData;",
        "typedef cRTip Tip;",
        "typedef cRTipManager TipManager;",
        "void Init(cRTipData* definition, int hide_disable_button);",
        "cRTip* TipNew(cRTipData* definition, int hide_disable_button);",
    ):
        assert declaration in header
    for retired_declaration in (
        "initialize_tip(",
        "kill_tip_widgets(",
        "update_tip(",
        "initialize_tip_manager(",
        "uninit_tips(",
        "enqueue_tip_message(",
        "update_tip_manager(",
    ):
        assert retired_declaration not in header

    expected_methods = (
        (
            "kill_tip_widgets",
            "cRTip::UnInit()",
            "cRTip_UnInit",
            "void cRTip::UnInit()",
            "?UnInit@cRTip@@QAEXXZ",
        ),
        (
            "initialize_tip",
            "cRTip::Init(cRTipData*, bool)",
            "cRTip_Init",
            "void cRTip::Init(",
            "?Init@cRTip@@QAEXPAUcRTipData@@H@Z",
        ),
        (
            "update_tip",
            "cRTip::AI()",
            "cRTip_AI",
            "void cRTip::AI()",
            "?AI@cRTip@@QAEXXZ",
        ),
        (
            "initialize_tip_manager",
            "cRTipManager::Init()",
            "cRTipManager_Init",
            "void cRTipManager::Init()",
            "?Init@cRTipManager@@QAEXXZ",
        ),
        (
            "uninit_tips",
            "cRTipManager::UnInitTips()",
            "cRTipManager_UnInitTips",
            "void cRTipManager::UnInitTips()",
            "?UnInitTips@cRTipManager@@QAEXXZ",
        ),
        (
            "enqueue_tip_message",
            "cRTipManager::TipNew(cRTipData*, bool)",
            "cRTipManager_TipNew",
            "cRTip* cRTipManager::TipNew(",
            "?TipNew@cRTipManager@@QAEPAVcRTip@@PAUcRTipData@@H@Z",
        ),
        (
            "update_tip_manager",
            "cRTipManager::AI()",
            "cRTipManager_AI",
            "void cRTipManager::AI()",
            "?AI@cRTipManager@@QAEXXZ",
        ),
    )
    for windows_name, mobile_symbol, alias, definition, object_symbol in (
        expected_methods
    ):
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["android_symbol"] == mobile_symbol
        assert alias in functions_by_name[windows_name]["aliases"]
        assert object_symbol in references_by_name[windows_name]["aliases"]
        source = (scratch_root / windows_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        config = (scratch_root / windows_name / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert definition in source
        assert f"SYMBOL={object_symbol}\n" in config

    shared_expectations = {
        "construct_game_runtime": "cRTipManager* tip_manager",
        "initialize_game_assets_and_world": "tip_manager.Init();",
        "uninit_tutorial": "tip_manager.UnInitTips();",
        "update_subgoldy": "tip_manager.TipNew(&row_event.definition, 1);",
    }
    for scratch_name, expected in shared_expectations.items():
        source = (scratch_root / scratch_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert expected in source

    assert "cRTipManager tip_manager;" in (
        include_root / "game_root.h"
    ).read_text(encoding="utf-8")
    assert "cRTipData definition;" in (
        include_root / "player.h"
    ).read_text(encoding="utf-8")
    tip_scratch = scratch_root / "initialize_tip"
    spec = (tip_scratch / "main-call-owner-interactions.json").read_text(
        encoding="utf-8"
    )
    assert "cRTipData*" in spec
    assert re.search(r"(?<!cR)\bTipData\*", spec) is None
    assert not (tip_scratch / "main-widget-lifetime-mutations.json").exists()


def test_mobile_gameplay_controllers_recover_authored_owners() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {entry["windows_name"]: entry for entry in crosswalk["entries"]}
    functions = load_json(repo_root / "analysis/symbols/gameplay-functions.json")
    functions_by_name = {
        entry["name"]: entry for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry for entry in references["symbols"]
    }
    include_root = repo_root / "tools/match/include"
    scratch_root = repo_root / "tools/match/scratches"
    invincible_header = (include_root / "invincible.h").read_text(
        encoding="utf-8"
    )
    damage_header = (include_root / "damage_guage.h").read_text(
        encoding="utf-8"
    )
    completion_header = (include_root / "completion.h").read_text(
        encoding="utf-8"
    )

    header_expectations = (
        (
            invincible_header,
            "class cRInvincible : public RenderableBod {",
            "typedef cRInvincible Invincible;",
            "class Invincible :",
            ("void Init();", "void Start();", "void AI();"),
            (
                "initialize_invincible_shell",
                "start_invincible_shell",
                "update_invincible_shell",
            ),
        ),
        (
            damage_header,
            "class cRDamageGuage {",
            "typedef cRDamageGuage DamageGuage;",
            "class DamageGuage {",
            ("void Init();", "void AI();", "void Take(float delta, bool force);"),
            (
                "initialize_damage_gauge",
                "update_damage_gauge",
                "apply_damage_gauge_delta",
            ),
        ),
        (
            completion_header,
            "class cRCompletion {",
            "typedef cRCompletion Completion;",
            "class Completion {",
            (
                "void UnInit();",
                "void Init(",
                "unsigned char perfect_delivery",
                "void AI();",
                "void RegisterParcel();",
            ),
            (
                "flush_row_event_display",
                "initialize_completion_screen",
                "update_row_event_display",
                "register_parcel_delivery",
            ),
        ),
    )
    for header, primary, compatibility, retired_class, methods, retired_methods in (
        header_expectations
    ):
        assert primary in header
        assert compatibility in header
        assert retired_class not in header
        for method in methods:
            assert method in header
        for retired_method in retired_methods:
            assert retired_method not in header

    player_header = (include_root / "player.h").read_text(encoding="utf-8")
    subgame_header = (include_root / "subgame_runtime.h").read_text(
        encoding="utf-8"
    )
    assert "cRInvincible invincible_shell;" in player_header
    assert "cRDamageGuage damage_gauge;" in player_header
    assert "cRCompletion completion;" in subgame_header

    expected_methods = (
        (
            "initialize_invincible_shell",
            "cRInvincible::Init()",
            "cRInvincible_Init",
            "void cRInvincible::Init()",
            "?Init@cRInvincible@@QAEXXZ",
        ),
        (
            "start_invincible_shell",
            "cRInvincible::Start()",
            "cRInvincible_Start",
            "void cRInvincible::Start()",
            "?Start@cRInvincible@@QAEXXZ",
        ),
        (
            "update_invincible_shell",
            "cRInvincible::AI()",
            "cRInvincible_AI",
            "void cRInvincible::AI()",
            "?AI@cRInvincible@@QAEXXZ",
        ),
        (
            "initialize_damage_gauge",
            "cRDamageGuage::Init()",
            "cRDamageGuage_Init",
            "void cRDamageGuage::Init()",
            "?Init@cRDamageGuage@@QAEXXZ",
        ),
        (
            "update_damage_gauge",
            "cRDamageGuage::AI()",
            "cRDamageGuage_AI",
            "void cRDamageGuage::AI()",
            "?AI@cRDamageGuage@@QAEXXZ",
        ),
        (
            "apply_damage_gauge_delta",
            "cRDamageGuage::Take(float, bool)",
            "cRDamageGuage_Take",
            "void cRDamageGuage::Take(float delta, bool force)",
            "?Take@cRDamageGuage@@QAEXM_N@Z",
        ),
        (
            "flush_row_event_display",
            "cRCompletion::UnInit()",
            "cRCompletion_UnInit",
            "void cRCompletion::UnInit()",
            "?UnInit@cRCompletion@@QAEXXZ",
        ),
        (
            "initialize_completion_screen",
            "cRCompletion::Init(int, bool)",
            "cRCompletion_Init",
            "void cRCompletion::Init(",
            "?Init@cRCompletion@@QAEXHE@Z",
        ),
        (
            "update_row_event_display",
            "cRCompletion::AI()",
            "cRCompletion_AI",
            "void cRCompletion::AI()",
            "?AI@cRCompletion@@QAEXXZ",
        ),
        (
            "register_parcel_delivery",
            "cRCompletion::RegisterParcel()",
            "cRCompletion_RegisterParcel",
            "void cRCompletion::RegisterParcel()",
            "?RegisterParcel@cRCompletion@@QAEXXZ",
        ),
    )
    for windows_name, mobile_symbol, alias, definition, object_symbol in (
        expected_methods
    ):
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["android_symbol"] == mobile_symbol
        assert alias in functions_by_name[windows_name]["aliases"]
        assert object_symbol in references_by_name[windows_name]["aliases"]
        source = (scratch_root / windows_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        config = (scratch_root / windows_name / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert definition in source
        assert f"FUNCTION={windows_name}\n" in config
        assert f"SYMBOL={object_symbol}\n" in config

    caller_expectations = {
        "initialize_subgoldy": (
            "presentation.invincible_shell.Init();",
            "damage_gauge.Init();",
        ),
        "build_subgame_level": ("damage_gauge.Init();",),
        "update_invincible_shell": ("Start();",),
        "update_damage_gauge": ("Take(-0.0016666667f, 1);",),
        "handle_subgoldy_collisions": ("damage_gauge.Take(",),
        "update_subgoldy": (
            "damage_gauge.AI();",
            "completion.AI();",
            "completion.UnInit();",
        ),
        "update_cutscene": ("completion.Init(",),
        "destroy_subgame": ("completion.UnInit();",),
        "update_track_parcel": ("completion.RegisterParcel();",),
        "construct_game_runtime": ("sizeof(cRCompletion)",),
    }
    for scratch_name, expected_calls in caller_expectations.items():
        source = (scratch_root / scratch_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        for expected_call in expected_calls:
            assert expected_call in source

    assert not (
        scratch_root
        / "handle_subgoldy_collisions/shared-pickup-vector-mutations.json"
    ).exists()
    for spec_name in (
        "completion-init-join-mutations.json",
        "perfect-delivery-default-mutations.json",
        "perfect-delivery-publication-mutations.json",
    ):
        spec = (scratch_root / "update_cutscene" / spec_name).read_text(
            encoding="utf-8"
        )
        assert "completion.Init" in spec
        assert "initialize_completion_screen" not in spec


def test_mobile_ring_and_health_recover_authored_owners() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {entry["windows_name"]: entry for entry in crosswalk["entries"]}
    functions = load_json(repo_root / "analysis/symbols/gameplay-functions.json")
    functions_by_name = {
        entry["name"]: entry for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry for entry in references["symbols"]
    }
    include_root = repo_root / "tools/match/include"
    scratch_root = repo_root / "tools/match/scratches"
    health_header = (include_root / "track_health_pickup.h").read_text(
        encoding="utf-8"
    )
    ring_header = (include_root / "ring_special_effect_types.h").read_text(
        encoding="utf-8"
    )

    assert "class cRSubHealth : public BodBase {" in health_header
    assert "typedef cRSubHealth SubHealth;" in health_header
    assert "class SubHealth :" not in health_header
    assert "cRSubHealth();" in health_header
    assert "void AI();" in health_header
    assert "class cRSubRingStar {" in ring_header
    assert "class cRSubRing : public RenderableBod {" in ring_header
    assert "typedef cRSubRingStar SubRingStar;" in ring_header
    assert "typedef cRSubRing SubRing;" in ring_header
    assert "class SubRingStar {" not in ring_header
    assert "class SubRing :" not in ring_header
    for declaration in (
        "cRSubRing();",
        "void Init(int unused_lives_snapshot);",
        "void AI();",
        "void Shower(cRSubGoldy* owner);",
    ):
        assert declaration in ring_header

    player_header = (include_root / "player.h").read_text(encoding="utf-8")
    subgame_header = (include_root / "subgame_runtime.h").read_text(
        encoding="utf-8"
    )
    assert "void HealthCollect(cRSubHealth* pickup);" in player_header
    assert "cRSubHealth health_pickups[8];" in subgame_header
    assert "cRSubRing slots[SUB_RING_POOL_CAPACITY];" in ring_header

    expected_methods = (
        (
            "initialize_track_health_pickup_runtime",
            "cRSubHealth_ctor",
            "cRSubHealth::cRSubHealth()",
            "??0cRSubHealth@@QAE@XZ",
        ),
        (
            "health_collect_particles",
            "cRSubGoldy_HealthCollect",
            "void cRSubGoldy::HealthCollect(cRSubHealth* pickup)",
            "?HealthCollect@cRSubGoldy@@QAEXPAVcRSubHealth@@@Z",
        ),
        (
            "update_track_health_pickup",
            "cRSubHealth_AI",
            "void cRSubHealth::AI()",
            "?AI@cRSubHealth@@QAEXXZ",
        ),
        (
            "initialize_track_ring_or_special_effect_runtime",
            "cRSubRing_ctor",
            "cRSubRing::cRSubRing()",
            "??0cRSubRing@@QAE@XZ",
        ),
        (
            "initialize_ring_or_special_effect_particles",
            "cRSubRing_Init",
            "void cRSubRing::Init(int)",
            "?Init@cRSubRing@@QAEXH@Z",
        ),
        (
            "emit_ring_star_shower",
            "cRSubRingStar_Shower",
            "void cRSubRingStar::Shower(cRSubGoldy* owner)",
            "?Shower@cRSubRingStar@@QAEXPAVcRSubGoldy@@@Z",
        ),
        (
            "update_ring_or_special_effect_particle",
            "cRSubRingStar_AI",
            "void cRSubRingStar::AI()",
            "?AI@cRSubRingStar@@QAEXXZ",
        ),
        (
            "update_ring_or_special_effect_parent",
            "cRSubRing_AI",
            "void cRSubRing::AI()",
            "?AI@cRSubRing@@QAEXXZ",
        ),
    )
    for windows_name, alias, definition, object_symbol in expected_methods:
        assert alias in functions_by_name[windows_name]["aliases"]
        assert object_symbol in references_by_name[windows_name]["aliases"]
        source = (scratch_root / windows_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        config = (scratch_root / windows_name / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert definition in source
        assert f"SYMBOL={object_symbol}\n" in config

    for windows_name in (
        "health_collect_particles",
        "update_track_health_pickup",
        "initialize_ring_or_special_effect_particles",
        "emit_ring_star_shower",
        "update_ring_or_special_effect_particle",
        "update_ring_or_special_effect_parent",
    ):
        assert entries[windows_name]["status"] == "verified"
        assert entries[windows_name]["confidence"] == "high"

    health_collect_aliases = references_by_name[
        "health_collect_particles"
    ]["aliases"]
    assert "?HealthCollect@cRSubGoldy@@QAEXPAVSubHealth@@@Z" in (
        health_collect_aliases
    )
    assert "?HealthCollect@cRSubGoldy@@QAEXPAVcRSubHealth@@@Z" in (
        health_collect_aliases
    )

    constructor_source = (
        scratch_root
        / "initialize_runtime_pools_and_path_template_bank/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "cRSubHealth* health_pickup = health_pickups;" in constructor_source
    assert (
        "((RuntimeSlot*)health_pickup)->initialize_track_health_pickup_runtime();"
        in constructor_source
    )
    assert "cRSubRing* ring = ring_effects.slots;" in constructor_source
    assert (
        "((RuntimeSlot*)ring)->initialize_track_ring_or_special_effect_runtime();"
        in constructor_source
    )
    assert "new (health_pickup)" not in constructor_source
    assert "new (ring)" not in constructor_source
    ring_spawn = (
        scratch_root / "spawn_track_ring_or_special_effect/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "slot->Init(player->lives);" in ring_spawn


def test_mobile_sub_lazer_and_salt_recover_authored_owners() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {entry["windows_name"]: entry for entry in crosswalk["entries"]}
    functions = load_json(repo_root / "analysis/symbols/gameplay-functions.json")
    functions_by_name = {
        entry["name"]: entry for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry for entry in references["symbols"]
    }
    include_root = repo_root / "tools/match/include"
    scratch_root = repo_root / "tools/match/scratches"
    sub_lazer_header = (include_root / "sub_lazer_types.h").read_text(
        encoding="utf-8"
    )
    salt_header = (include_root / "salt_hazard_types.h").read_text(
        encoding="utf-8"
    )

    assert "class cRSubLazer : public RenderableBod {" in sub_lazer_header
    assert "class cRSubLazerManager {" in sub_lazer_header
    assert "typedef cRSubLazer SubLazer;" in sub_lazer_header
    assert "typedef cRSubLazerManager SubLazerManager;" in sub_lazer_header
    assert "class SubLazer :" not in sub_lazer_header
    assert "class SubLazerManager {" not in sub_lazer_header
    for declaration in (
        "cRSubLazer();",
        "void Shoot(const Vector3* origin, const Vector3* direction);",
        "void Kill();",
        "void AI();",
        "void Init();",
        "void Shoot(Vector3* origin, const Vector3* direction);",
    ):
        assert declaration in sub_lazer_header

    assert "class cRSalt : public RenderableBod {" in salt_header
    assert "class cRSaltManager {" in salt_header
    assert "typedef cRSalt Salt;" in salt_header
    assert "typedef cRSaltManager SaltManager;" in salt_header
    assert "class Salt :" not in salt_header
    assert "class SaltManager {" not in salt_header
    for declaration in (
        "cRSalt();",
        "void AI();",
        "void Init();",
        "void Add(tVector& position);",
    ):
        assert declaration in salt_header

    subgame_header = (include_root / "subgame_runtime.h").read_text(
        encoding="utf-8"
    )
    assert "cRSubLazerManager sub_lazers;" in subgame_header
    assert "cRSaltManager salt_hazards;" in subgame_header

    expected_methods = (
        (
            "initialize_sub_lazer_runtime",
            "cRSubLazer_ctor",
            "cRSubLazer::cRSubLazer()",
            "??0cRSubLazer@@QAE@XZ",
            False,
        ),
        (
            "initialize_sub_lazer_pool",
            "cRSubLazerManager_Init",
            "void cRSubLazerManager::Init()",
            "?Init@cRSubLazerManager@@QAEXXZ",
            True,
        ),
        (
            "spawn_sub_lazer_projectile",
            "cRSubLazer_Shoot",
            "void cRSubLazer::Shoot(const Vector3* origin, const Vector3* direction)",
            "?Shoot@cRSubLazer@@QAEXPBUtVector@@0@Z",
            True,
        ),
        (
            "deactivate_sub_lazer_projectile",
            "cRSubLazer_Kill",
            "void cRSubLazer::Kill()",
            "?Kill@cRSubLazer@@QAEXXZ",
            True,
        ),
        (
            "update_sub_lazer_projectile",
            "cRSubLazer_AI",
            "void cRSubLazer::AI()",
            "?AI@cRSubLazer@@QAEXXZ",
            True,
        ),
        (
            "shoot_sub_lazer_pool",
            "cRSubLazerManager_Shoot",
            "void cRSubLazerManager::Shoot(Vector3* origin, const Vector3* direction)",
            "?Shoot@cRSubLazerManager@@QAEXPAUtVector@@PBU2@@Z",
            True,
        ),
        (
            "initialize_salt_hazard_runtime",
            "cRSalt_ctor",
            "cRSalt::cRSalt()",
            "??0cRSalt@@QAE@XZ",
            False,
        ),
        (
            "initialize_salt_hazard_pool",
            "cRSaltManager_Init",
            "void cRSaltManager::Init()",
            "?Init@cRSaltManager@@QAEXXZ",
            True,
        ),
        (
            "spawn_salt_hazard",
            "cRSaltManager_Add",
            "void cRSaltManager::Add(tVector& position)",
            "?Add@cRSaltManager@@QAEXAAUtVector@@@Z",
            True,
        ),
        (
            "update_salt_hazard",
            "cRSalt_AI",
            "void cRSalt::AI()",
            "?AI@cRSalt@@QAEXXZ",
            True,
        ),
    )
    for windows_name, alias, definition, object_symbol, has_crosswalk in (
        expected_methods
    ):
        assert alias in functions_by_name[windows_name]["aliases"]
        assert object_symbol in references_by_name[windows_name]["aliases"]
        source = (scratch_root / windows_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        config = (scratch_root / windows_name / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert definition in source
        assert f"FUNCTION={windows_name}\n" in config
        assert f"SYMBOL={object_symbol}\n" in config
        if has_crosswalk:
            assert entries[windows_name]["status"] == "verified"
            assert entries[windows_name]["confidence"] == "high"

    build_level = (scratch_root / "build_subgame_level/scratch.cpp").read_text(
        encoding="utf-8"
    )
    assert "sub_lazers.Init();" in build_level
    assert "salt_hazards.Init();" in build_level
    sub_loc = (scratch_root / "update_sub_loc/scratch.cpp").read_text(
        encoding="utf-8"
    )
    assert "sub_lazers.Shoot(&spawn, &direction);" in sub_loc
    subgame = (scratch_root / "update_subgame/scratch.cpp").read_text(
        encoding="utf-8"
    )
    assert subgame.count("salt_hazards.Add(cell_slot->cell.position);") == 2
    runtime_constructor = (
        scratch_root
        / "initialize_runtime_pools_and_path_template_bank/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "sizeof(cRSubLazer)" in runtime_constructor
    assert "sizeof(cRSalt)" in runtime_constructor


def test_mobile_slug_family_recovers_authored_owners() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {entry["windows_name"]: entry for entry in crosswalk["entries"]}
    functions = load_json(repo_root / "analysis/symbols/gameplay-functions.json")
    functions_by_name = {
        entry["name"]: entry for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry for entry in references["symbols"]
    }
    include_root = repo_root / "tools/match/include"
    scratch_root = repo_root / "tools/match/scratches"
    slug_header = (include_root / "slug_hazard_types.h").read_text(
        encoding="utf-8"
    )
    voice_header = (include_root / "slug_voice_manager.h").read_text(
        encoding="utf-8"
    )

    assert "class cRSlug : public RenderableBod {" in slug_header
    assert "typedef cRSlug Slug;" in slug_header
    assert "class Slug :" not in slug_header
    assert "cRSlug slots[SUB_SLUG_SLOT_CAPACITY];" in slug_header
    for declaration in (
        "cRSlug();",
        "void VoiceAI();",
        "void VoicePlay(int sample_index);",
        "void Hit(int damage);",
        "void Explode();",
        "void Kill();",
        "void AI();",
    ):
        assert declaration in slug_header
    assert "class cRSlugVoiceManager {" in voice_header
    assert "typedef cRSlugVoiceManager SlugVoiceManager;" in voice_header
    assert "class SlugVoiceManager {" not in voice_header
    assert "void Init();" in voice_header
    assert "void AI();" in voice_header

    subgame_header = (include_root / "subgame_runtime.h").read_text(
        encoding="utf-8"
    )
    assert "cRSlugVoiceManager slug_voice_manager;" in subgame_header

    expected_methods = (
        (
            "initialize_slug_hazard_runtime",
            "cRSlug_ctor",
            "cRSlug::cRSlug()",
            "??0cRSlug@@QAE@XZ",
            False,
        ),
        (
            "update_slug_voice_ai",
            "cRSlug_VoiceAI",
            "void cRSlug::VoiceAI()",
            "?VoiceAI@cRSlug@@QAEXXZ",
            True,
        ),
        (
            "play_slug_voice",
            "cRSlug_VoicePlay",
            "void cRSlug::VoicePlay(int sample_index)",
            "?VoicePlay@cRSlug@@QAEXH@Z",
            True,
        ),
        (
            "initialize_slug_voice_manager",
            "cRSlugVoiceManager_Init",
            "void cRSlugVoiceManager::Init()",
            "?Init@cRSlugVoiceManager@@QAEXXZ",
            True,
        ),
        (
            "update_slug_voice_manager",
            "cRSlugVoiceManager_AI",
            "void cRSlugVoiceManager::AI()",
            "?AI@cRSlugVoiceManager@@QAEXXZ",
            True,
        ),
        (
            "hit_slug_hazard",
            "cRSlug_Hit",
            "void cRSlug::Hit(int damage)",
            "?Hit@cRSlug@@QAEXH@Z",
            True,
        ),
        (
            "explode_slug_hazard",
            "cRSlug_Explode",
            "void cRSlug::Explode()",
            "?Explode@cRSlug@@QAEXXZ",
            True,
        ),
        (
            "kill_slug_hazard",
            "cRSlug_Kill",
            "void cRSlug::Kill()",
            "?Kill@cRSlug@@QAEXXZ",
            True,
        ),
        (
            "update_slug_hazard_ai",
            "cRSlug_AI",
            "void cRSlug::AI()",
            "?AI@cRSlug@@QAEXXZ",
            True,
        ),
    )
    for windows_name, alias, definition, object_symbol, has_crosswalk in (
        expected_methods
    ):
        assert alias in functions_by_name[windows_name]["aliases"]
        assert object_symbol in references_by_name[windows_name]["aliases"]
        source = (scratch_root / windows_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        config = (scratch_root / windows_name / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert definition in source
        assert f"FUNCTION={windows_name}\n" in config
        assert f"SYMBOL={object_symbol}\n" in config
        if has_crosswalk:
            assert entries[windows_name]["status"] == "verified"
            assert entries[windows_name]["confidence"] == "high"

    callers = {
        "build_subgame_level": ("slug_voice_manager.Init();",),
        "update_subgame": ("slug_voice_manager.AI();",),
        "handle_subgoldy_collisions": (".VoicePlay(", ".Kill();"),
        "update_golb_ai": ("->Hit(2);", "->Hit(4);"),
        "spawn_slug_hazard": ("cRSlug* scan = slug_hazards.slots;",),
        "reset_subgame": ("cRSlug* slug = slug_hazards.slots;",),
    }
    for scratch_name, expected_calls in callers.items():
        source = (scratch_root / scratch_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        for expected_call in expected_calls:
            assert expected_call in source

    constructor = (
        scratch_root
        / "initialize_runtime_pools_and_path_template_bank/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "cRSlug* slug = slug_hazards.slots;" in constructor
    assert (
        "((RuntimeSlot*)slug)->initialize_slug_hazard_runtime();" in constructor
    )
    assert "new (slug)" not in constructor


def test_mobile_warning_recovers_authored_owner() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {entry["windows_name"]: entry for entry in crosswalk["entries"]}
    functions = load_json(repo_root / "analysis/symbols/gameplay-functions.json")
    functions_by_name = {
        entry["name"]: entry for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry for entry in references["symbols"]
    }
    scratch_root = repo_root / "tools/match/scratches"
    warning_header = (repo_root / "tools/match/include/warning.h").read_text(
        encoding="utf-8"
    )

    assert "class cRWarning {" in warning_header
    assert "typedef cRWarning Warning;" in warning_header
    assert "class Warning {" not in warning_header
    for method in (
        "void Init();",
        "void UnInit();",
        "void Start();",
        "void Stop();",
        "void StopSample();",
        "void AI();",
    ):
        assert method in warning_header
    for retired_method in (
        "initialize_warning",
        "uninit_warning",
        "start_warning",
        "stop_warning",
        "stop_warning_sample",
        "update_warning",
    ):
        assert retired_method not in warning_header

    player_header = (repo_root / "tools/match/include/player.h").read_text(
        encoding="utf-8"
    )
    assert "cRWarning warning;" in player_header

    expected_methods = (
        (
            "initialize_warning",
            "cRWarning::Init()",
            "cRWarning_Init",
            "void cRWarning::Init()",
            "?Init@cRWarning@@QAEXXZ",
        ),
        (
            "uninit_warning",
            "cRWarning::UnInit()",
            "cRWarning_UnInit",
            "void cRWarning::UnInit()",
            "?UnInit@cRWarning@@QAEXXZ",
        ),
        (
            "start_warning",
            "cRWarning::Start()",
            "cRWarning_Start",
            "void cRWarning::Start()",
            "?Start@cRWarning@@QAEXXZ",
        ),
        (
            "stop_warning",
            "cRWarning::Stop()",
            "cRWarning_Stop",
            "void cRWarning::Stop()",
            "?Stop@cRWarning@@QAEXXZ",
        ),
        (
            "stop_warning_sample",
            "cRWarning::StopSample()",
            "cRWarning_StopSample",
            "void cRWarning::StopSample()",
            "?StopSample@cRWarning@@QAEXXZ",
        ),
        (
            "update_warning",
            "cRWarning::AI()",
            "cRWarning_AI",
            "void cRWarning::AI()",
            "?AI@cRWarning@@QAEXXZ",
        ),
    )
    for windows_name, mobile_symbol, alias, definition, object_symbol in (
        expected_methods
    ):
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["android_symbol"] == mobile_symbol
        assert alias in functions_by_name[windows_name]["aliases"]
        assert object_symbol in references_by_name[windows_name]["aliases"]
        source = (scratch_root / windows_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        config = (scratch_root / windows_name / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert definition in source
        assert f"FUNCTION={windows_name}\n" in config
        assert f"SYMBOL={object_symbol}\n" in config

    caller_expectations = {
        "initialize_subgame": ("warning.Init();",),
        "destroy_subgame": ("warning.UnInit();",),
        "update_damage_gauge": (
            "warning.Start();",
            "warning.Stop();",
            "warning.StopSample();",
        ),
        "update_subgoldy": ("warning.AI();",),
    }
    for scratch_name, expected_calls in caller_expectations.items():
        source = (scratch_root / scratch_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        for expected_call in expected_calls:
            assert expected_call in source


def test_mobile_high_score_recovers_authored_lifecycle() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {entry["windows_name"]: entry for entry in crosswalk["entries"]}
    functions = load_json(repo_root / "analysis/symbols/gameplay-functions.json")
    functions_by_name = {
        entry["name"]: entry for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry for entry in references["symbols"]
    }
    scratch_root = repo_root / "tools/match/scratches"
    high_score_header = (repo_root / "tools/match/include/high_score.h").read_text(
        encoding="utf-8"
    )

    assert "class cRHighScore {" in high_score_header
    assert "typedef cRHighScore HighScore;" in high_score_header
    assert "class HighScore {" not in high_score_header
    for method in (
        "void Init(int mode, int rank);",
        "void UnInit();",
        "void AI();",
        "void Exit();",
    ):
        assert method in high_score_header
    for retired_method in (
        "initialize_high_score_screen",
        "destroy_high_score_screen",
        "update_high_score_screen",
        "exit_high_score_screen",
    ):
        assert retired_method not in high_score_header

    game_root_header = (repo_root / "tools/match/include/game_root.h").read_text(
        encoding="utf-8"
    )
    assert "cRHighScore high_score;" in game_root_header

    expected_methods = (
        (
            "initialize_high_score_screen",
            "cRHighScore::Init(int, int)",
            "cRHighScore_Init",
            "void cRHighScore::Init(int mode_, int rank)",
            "?Init@cRHighScore@@QAEXHH@Z",
        ),
        (
            "destroy_high_score_screen",
            "cRHighScore::UnInit()",
            "cRHighScore_UnInit",
            "void cRHighScore::UnInit()",
            "?UnInit@cRHighScore@@QAEXXZ",
        ),
        (
            "update_high_score_screen",
            "cRHighScore::AI()",
            "cRHighScore_AI",
            "void cRHighScore::AI()",
            "?AI@cRHighScore@@QAEXXZ",
        ),
        (
            "exit_high_score_screen",
            "cRHighScore::Exit()",
            "cRHighScore_Exit",
            "void cRHighScore::Exit()",
            "?Exit@cRHighScore@@QAEXXZ",
        ),
    )
    for windows_name, mobile_symbol, alias, definition, object_symbol in (
        expected_methods
    ):
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["android_symbol"] == mobile_symbol
        assert alias in functions_by_name[windows_name]["aliases"]
        assert object_symbol in references_by_name[windows_name]["aliases"]
        source = (scratch_root / windows_name / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        config = (scratch_root / windows_name / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert definition in source
        assert f"FUNCTION={windows_name}\n" in config
        assert f"SYMBOL={object_symbol}\n" in config

    frontend = (
        scratch_root / "update_frontend_state_machine/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert frontend.count("high_score.Init(") == 2
    assert frontend.count("high_score.AI();") == 2
    assert "initialize_high_score_screen" not in frontend
    assert "update_high_score_screen" not in frontend


def test_mobile_initializers_recover_authored_owners_without_layout_transfer() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    verified = load_json(
        repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json"
    )
    verified_entries = {
        entry["windows_name"]: entry
        for entry in verified["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }

    sprite = entries["initialize_sprite"]
    assert sprite["status"] == "verified"
    assert sprite["confidence"] == "high"
    assert sprite["android_symbol"] == "cRSprite::Init()"
    assert sprite["android_body_count"] == 1
    assert "ios_symbol" not in sprite
    assert "0xb0" in verified_entries["initialize_sprite"]["notes"]
    assert "0xb4" in verified_entries["initialize_sprite"]["notes"]
    assert "cRSprite_Init" in functions_by_name["initialize_sprite"]["aliases"]
    assert "cRSprite_AI" in functions_by_name["update_sprite"]["aliases"]
    assert "cRSprite_Kill" in functions_by_name["kill_sprite"]["aliases"]
    assert "cRSprite_BuildTail" in (
        functions_by_name["build_sprite_tail"]["aliases"]
    )
    assert "cRSprite_SetTextureRef" in (
        functions_by_name["set_sprite_texture_ref"]["aliases"]
    )
    assert "?Init@cRSprite@@QAEXXZ" in (
        references_by_name["initialize_sprite"]["aliases"]
    )
    assert "?AI@cRSprite@@QAEXXZ" in (
        references_by_name["update_sprite"]["aliases"]
    )
    assert "?Kill@cRSprite@@QAEXXZ" in (
        references_by_name["kill_sprite"]["aliases"]
    )
    assert "?BuildTail@cRSprite@@QAEXPAUtMatrix@@@Z" in (
        references_by_name["build_sprite_tail"]["aliases"]
    )
    assert "?SetTextureRef@cRSprite@@QAEXHH@Z" in (
        references_by_name["set_sprite_texture_ref"]["aliases"]
    )

    ghost = entries["initialize_subgoldy_ghost"]
    assert ghost["status"] == "verified"
    assert ghost["confidence"] == "high"
    assert ghost["android_symbol"] == "cRSubGoldy::GhostInit(int)"
    assert ghost["ios_symbol"] == "cRSubGoldy::GhostInit(int)"
    assert ghost["android_body_count"] == 1
    assert ghost["ios_body_count"] == 1
    assert "cRSubGoldy_GhostInit" in (
        functions_by_name["initialize_subgoldy_ghost"]["aliases"]
    )

    sprite_header = (
        repo_root / "tools/match/include/sprite.h"
    ).read_text(encoding="utf-8")
    sprite_forward_header = (
        repo_root / "tools/match/include/sprite_fwd.h"
    ).read_text(encoding="utf-8")
    player_header = (
        repo_root / "tools/match/include/player.h"
    ).read_text(encoding="utf-8")
    player_forward_header = (
        repo_root / "tools/match/include/player_fwd.h"
    ).read_text(encoding="utf-8")
    assert '#include "sprite_fwd.h"' in sprite_header
    assert "class cRSprite {" in sprite_header
    assert "class cRSpriteManager {" in sprite_header
    assert "class Sprite {" not in sprite_header
    assert "class SpriteManager {" not in sprite_header
    assert "class cRSprite;" in sprite_forward_header
    assert "typedef cRSprite Sprite;" in sprite_forward_header
    assert "class cRSpriteManager;" in sprite_forward_header
    assert "typedef cRSpriteManager SpriteManager;" in sprite_forward_header
    assert "typedef char cRSprite_must_be_0xb4[" in sprite_header
    assert "typedef char cRSpriteManager_must_be_0x83d7c[" in sprite_header
    assert "extern cRSpriteManager g_sprite_manager;" in sprite_header
    assert "extern cRSprite g_sprite_sentinel;" in sprite_header
    assert "void Init();" in sprite_header
    assert "void AI();" in sprite_header
    assert "void Kill();" in sprite_header
    assert "void BuildTail(tMatrix* matrix);" in sprite_header
    assert "void SetTextureRef(int texture_id, int frame);" in sprite_header
    assert "initialize_sprite()" not in sprite_header
    assert "update_sprite()" not in sprite_header
    assert "kill_sprite()" not in sprite_header
    assert "build_sprite_tail(" not in sprite_header
    assert "set_sprite_texture_ref(" not in sprite_header
    authored_sprite_scratches = {
        "initialize_sprite": (
            "void cRSprite::Init()",
            "SYMBOL=?Init@cRSprite@@QAEXXZ",
        ),
        "update_sprite": (
            "void cRSprite::AI()",
            "SYMBOL=?AI@cRSprite@@QAEXXZ",
        ),
        "kill_sprite": (
            "void cRSprite::Kill()",
            "SYMBOL=?Kill@cRSprite@@QAEXXZ",
        ),
        "build_sprite_tail": (
            "void cRSprite::BuildTail(tMatrix* matrix)",
            "SYMBOL=?BuildTail@cRSprite@@QAEXPAUtMatrix@@@Z",
        ),
        "set_sprite_texture_ref": (
            "void cRSprite::SetTextureRef(int texture_id, int frame)",
            "SYMBOL=?SetTextureRef@cRSprite@@QAEXHH@Z",
        ),
    }
    for scratch_name, (definition, symbol) in authored_sprite_scratches.items():
        scratch_root = repo_root / "tools/match/scratches" / scratch_name
        assert definition in (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        assert symbol in (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
    assert "class cRSubGoldy : public RenderableBod" in player_header
    assert "typedef cRSubGoldy Player;" in player_forward_header
    assert "class Player;" not in player_header
    matcher_include_root = repo_root / "tools/match/include"
    for header_path in matcher_include_root.glob("*.h"):
        header_text = header_path.read_text(encoding="utf-8")
        if header_path.name != "player_fwd.h":
            assert re.search(
                r"\bPlayer\b",
                header_text,
            ) is None
        if header_path.name != "sprite_fwd.h":
            assert "class Sprite;" not in header_text
            assert "class SpriteManager;" not in header_text


def test_mobile_sprite_manager_recovers_authored_methods_and_contracts() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    verified = load_json(
        repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json"
    )
    verified_entries = {
        entry["windows_name"]: entry
        for entry in verified["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }
    expected_methods = (
        (
            "register_sprite_texture",
            "cRSpriteManager::Load(char*, int, int)",
            "medium",
            "cRSpriteManager_Load",
            "void cRSpriteManager::Load(char* texture_path, int texture_id, int flags)",
            "?Load@cRSpriteManager@@QAEXPADHH@Z",
        ),
        (
            "initialize_sprite_manager",
            "cRSpriteManager::Init()",
            "high",
            "cRSpriteManager_Init",
            "void cRSpriteManager::Init()",
            "?Init@cRSpriteManager@@QAEXXZ",
        ),
        (
            "allocate_sprite",
            "cRSpriteManager::New(int, int, int, int)",
            "high",
            "cRSpriteManager_New",
            "cRSprite* cRSpriteManager::New(int owner, int texture_id, int texture_a, int texture_b)",
            "?New@cRSpriteManager@@QAEPAVcRSprite@@HHHH@Z",
        ),
        (
            "kill_game_sprites",
            "cRSpriteManager::KillGame()",
            "high",
            "cRSpriteManager_KillGame",
            "void cRSpriteManager::KillGame()",
            "?KillGame@cRSpriteManager@@QAEXXZ",
        ),
        (
            "set_sprite_manager_paused",
            "cRSpriteManager::Pause(bool)",
            "high",
            "cRSpriteManager_Pause",
            "void cRSpriteManager::Pause(bool paused_)",
            "?Pause@cRSpriteManager@@QAEX_N@Z",
        ),
        (
            "get_sprite_texture",
            "cRSpriteManager::GetTexture(int)",
            "high",
            "cRSpriteManager_GetTexture",
            "cRTexture* cRSpriteManager::GetTexture(int texture_id)",
            "?GetTexture@cRSpriteManager@@QAEPAUcRTexture@@H@Z",
        ),
        (
            "get_sprite_tga",
            "cRSpriteManager::GetTga(int)",
            "high",
            "cRSpriteManager_GetTga",
            "TgaImageView* cRSpriteManager::GetTga(int texture_id)",
            "?GetTga@cRSpriteManager@@QAEPAUTgaImageView@@H@Z",
        ),
    )
    for (
        windows_name,
        mobile_symbol,
        confidence,
        semantic_alias,
        definition,
        object_symbol,
    ) in expected_methods:
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == confidence
        assert entry["android_symbol"] == mobile_symbol
        assert entry["ios_symbol"] == mobile_symbol
        assert entry["android_body_count"] == 1
        assert entry["ios_body_count"] == 1
        assert semantic_alias in functions_by_name[windows_name]["aliases"]
        assert object_symbol in references_by_name[windows_name]["aliases"]

        scratch_root = repo_root / "tools/match/scratches" / windows_name
        scratch_source = (scratch_root / "scratch.cpp").read_text(
            encoding="utf-8"
        )
        scratch_config = (scratch_root / "scratch.conf").read_text(
            encoding="utf-8"
        )
        assert definition in scratch_source
        assert f"SYMBOL={object_symbol}\n" in scratch_config

    sprite_header = (
        repo_root / "tools/match/include/sprite.h"
    ).read_text(encoding="utf-8")
    expected_declarations = (
        "void Load(char* texture_path, int texture_id, int flags);",
        "void Init();",
        "cRSprite* New(int owner, int texture_id, int texture_a, int texture_b);",
        "void KillGame();",
        "void Pause(bool paused_);",
        "cRTexture* GetTexture(int texture_id);",
        "TgaImageView* GetTga(int texture_id);",
    )
    for declaration in expected_declarations:
        assert declaration in sprite_header

    legacy_methods = (
        "register_sprite_texture",
        "initialize_sprite_manager",
        "allocate_sprite",
        "kill_game_sprites",
        "set_sprite_manager_paused",
        "get_sprite_texture",
        "get_sprite_tga",
    )
    matcher_sources = "\n".join(
        path.read_text(encoding="utf-8")
        for path in (repo_root / "tools/match/scratches").glob(
            "*/scratch.cpp"
        )
    )
    for legacy_method in legacy_methods:
        assert f".{legacy_method}(" not in matcher_sources
        assert f"::{legacy_method}(" not in matcher_sources
        assert f"{legacy_method}(" not in sprite_header

    load_source = (
        repo_root
        / "tools/match/scratches/register_sprite_texture/scratch.cpp"
    ).read_text(encoding="utf-8")
    pause_source = (
        repo_root
        / "tools/match/scratches/set_sprite_manager_paused/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "return result;" not in load_source
    assert "return paused_;" not in pause_source
    assert "all 69 direct Windows callsites discard EAX" in (
        verified_entries["register_sprite_texture"]["notes"]
    )
    assert "All six direct Windows callsites" in (
        verified_entries["set_sprite_manager_paused"]["notes"]
    )


def test_mobile_animation_keyframes_recover_crbodpos_tail_lane() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    request_anim = next(
        entry
        for entry in crosswalk["entries"]
        if entry["windows_name"] == "request_object_animation"
    )
    verified = load_json(
        repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json"
    )
    verified_request_anim = next(
        entry
        for entry in verified["entries"]
        if entry["windows_name"] == "request_object_animation"
    )
    assert request_anim["android_symbol"] == (
        "cRObject::RequestAnim(int, cRBodPos*, float, int)"
    )
    assert request_anim["ios_symbol"] == request_anim["android_symbol"]
    assert "raw 0x74-byte cRBodPos objects" in verified_request_anim["notes"]
    assert "final +0x7c lane" in verified_request_anim["notes"]

    android_loader = (
        repo_root
        / "analysis/decompile/android/functions/"
        "00089044-_ZN9cRDirectX8LoadAnimEPcP8cRObject.c"
    ).read_text(encoding="utf-8")
    ios_loader = (
        repo_root
        / "analysis/decompile/ios/functions/"
        "000681f8-_ZN9cRDirectX8LoadAnimEPcP8cRObject.c"
    ).read_text(encoding="utf-8")
    for loader, count_name in (
        (android_loader, "local_2bc"),
        (ios_loader, "local_30"),
    ):
        assert f"{count_name} * 0x74" in loader
        assert "*(undefined4 *)(this_00 + 0x70)" in loader
        assert "this_00 = this_00 + 0x74" in loader

    bod_header = (
        repo_root / "tools/match/include/bod_types.h"
    ).read_text(encoding="utf-8")
    animation_header = (
        repo_root / "tools/match/include/object_animation_types.h"
    ).read_text(encoding="utf-8")
    analysis_header = (
        repo_root / "analysis/headers/path_template_types.h"
    ).read_text(encoding="utf-8")
    assert "int frame_number; // +0x7c" in bod_header
    assert "unknown_07c" not in bod_header
    assert "typedef cRBodPos XAnimationKeyframe;" in animation_header
    assert "struct XAnimationKeyframe : public BodBase" not in animation_header
    assert "int32_t frame_number;" in analysis_header
    assert "unknown_7c" not in analysis_header


def test_mobile_crbod_owners_are_primary_without_faking_constructors() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_name = {
        entry["name"]: entry
        for entry in references["symbols"]
    }

    expected_mobile_symbols = {
        "is_bod_after_sprites": "cRBod::IsAfterSprites()",
        "set_bod_object": "cRBod::SetObject(cRObject*)",
        "initialize_bod_base": "cRBod::cRBod()",
        "initialize_renderable_bod": "cRBodPos::cRBodPos()",
        "apply_bod_position": "cRBod::ApplyPos(tMatrix&)",
    }
    for windows_name, mobile_symbol in expected_mobile_symbols.items():
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["android_symbol"] == mobile_symbol
        assert entry["ios_symbol"] == mobile_symbol
        assert entry["source_object"] == "RObject.o"

    bod_header = (
        repo_root / "tools/match/include/bod_types.h"
    ).read_text(encoding="utf-8")
    bod_forward_header = (
        repo_root / "tools/match/include/bod_fwd.h"
    ).read_text(encoding="utf-8")
    assert "class cRBod : public BodNode" in bod_header
    assert "class cRBodPos : public cRBod" in bod_header
    assert "class BodBase" not in bod_header
    assert "class RenderableBod" not in bod_header
    assert "typedef cRBod BodBase;" in bod_forward_header
    assert "typedef cRBodPos RenderableBod;" in bod_forward_header
    assert "cRBod_must_be_0x38" in bod_header
    assert "cRBodPos_must_be_0x80" in bod_header

    exact_symbols = {
        "is_bod_after_sprites": "?IsAfterSprites@cRBod@@QAE_NXZ",
        "set_bod_object": "?SetObject@cRBod@@QAEHPAUcRObject@@@Z",
        "initialize_bod_base": "?initialize_bod_base@cRBod@@QAEPAV1@XZ",
        "initialize_renderable_bod": (
            "?initialize_renderable_bod@cRBodPos@@QAEPAV1@XZ"
        ),
        "apply_bod_position": (
            "?ApplyPos@cRBod@@QAEPAUcRObject@@PAUtMatrix@@@Z"
        ),
        "initialize_noop_renderable_bod": (
            "?initialize_noop_renderable_bod@cRBodPos@@QAEPAV1@XZ"
        ),
    }
    for windows_name, symbol in exact_symbols.items():
        scratch_root = (
            repo_root / "tools/match/scratches" / windows_name
        )
        source = (scratch_root / "scratch.cpp").read_text(encoding="utf-8")
        config = (scratch_root / "scratch.conf").read_text(encoding="utf-8")
        assert f"SYMBOL={symbol}" in config
        assert symbol in references_by_name[windows_name]["aliases"]
        if windows_name in (
            "initialize_renderable_bod",
            "initialize_noop_renderable_bod",
        ):
            assert "cRBodPos::" in source
        else:
            assert "cRBod::" in source

    base_initializer = (
        repo_root
        / "tools/match/scratches/initialize_bod_base/scratch.cpp"
    ).read_text(encoding="utf-8")
    positioned_initializer = (
        repo_root
        / "tools/match/scratches/initialize_renderable_bod/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "cRBod* cRBod::initialize_bod_base()" in base_initializer
    assert "cRBodPos* cRBodPos::initialize_renderable_bod()" in (
        positioned_initializer
    )
    assert "bool cRBod::IsAfterSprites()" in (
        repo_root
        / "tools/match/scratches/is_bod_after_sprites/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "int cRBod::SetObject(Object* object_)" in (
        repo_root
        / "tools/match/scratches/set_bod_object/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "Object* cRBod::ApplyPos(TransformMatrix* matrix)" in (
        repo_root
        / "tools/match/scratches/apply_bod_position/scratch.cpp"
    ).read_text(encoding="utf-8")
    assert "cRBod::cRBod()" not in base_initializer
    assert "cRBodPos::cRBodPos()" not in positioned_initializer


def test_mobile_sprite_renderer_recovers_gl_owner_and_void_boundaries() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }

    expected = {
        "begin_sprite_depth_render_state": "G0RenderSprite3DStart()",
        "draw_sprite_quad": "G0RenderSprite3D(tVector*, cRSprite*)",
        "end_sprite_depth_render_state": "G0RenderSprite3DEnd()",
    }
    for windows_name, mobile_symbol in expected.items():
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["source_object"] == "GL.o"
        assert entry["android_symbol"] == mobile_symbol
        assert entry["ios_symbol"] == mobile_symbol
        assert entry["android_body_count"] == 1
        assert entry["ios_body_count"] == 1

    border = entries["initialize_frontend_sprite_button"]
    assert border["status"] == "verified"
    assert border["source_object"] == "Border.o"
    assert border["android_symbol"] == (
        "cRBorder::Init(int, int, float, float, tColour, float, int)"
    )
    assert border["ios_symbol"] == border["android_symbol"]
    assert "cRBorder_InitSprite" in (
        functions_by_name["initialize_frontend_sprite_button"]["aliases"]
    )

    renderer_aliases = {
        "begin_sprite_depth_render_state": "G0RenderSprite3DStart",
        "draw_sprite_quad": "G0RenderSprite3D",
        "end_sprite_depth_render_state": "G0RenderSprite3DEnd",
    }
    for windows_name, alias in renderer_aliases.items():
        assert alias in functions_by_name[windows_name]["aliases"]

    frontend_header = (
        repo_root / "tools/match/include/frontend_widget.h"
    ).read_text(encoding="utf-8")
    assert "typedef FrontendWidget cRBorder;" in frontend_header


def test_mobile_delay_click_recovers_border_manager_owner() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }

    delay_click = entries["queue_frontend_widget_flag_after_delay"]
    assert delay_click["status"] == "verified"
    assert delay_click["confidence"] == "high"
    assert delay_click["source_object"] == "Border.o"
    assert delay_click["android_symbol"] == (
        "cRBorderManager::DelayClick(cRBorder*, int)"
    )
    assert delay_click["android_body_count"] == 1
    assert "ios_symbol" not in delay_click
    assert "cRBorderManager_DelayClick" in (
        functions_by_name[
            "queue_frontend_widget_flag_after_delay"
        ]["aliases"]
    )

    android_body = (
        repo_root
        / (
            "analysis/decompile/android/functions/"
            "0005d05c-_ZN15cRBorderManager10DelayClickEP8cRBorderi.c"
        )
    ).read_text(encoding="utf-8")
    assert "0x40000000" in android_body
    assert "cRFade::Start" in android_body
    assert "0x3daaaaab" in android_body

    ios_border_ai = (
        repo_root
        / (
            "analysis/decompile/ios/functions/"
            "0003c410-_ZN8cRBorder2AIEv.c"
        )
    ).read_text(encoding="utf-8")
    assert ios_border_ai.count("cRFade::Start") == 3
    assert ios_border_ai.count("0x3daaaaab") == 3

    notes = (
        repo_root
        / "tools/match/scratches"
        / "queue_frontend_widget_flag_after_delay"
        / "NOTES.md"
    ).read_text(encoding="utf-8")
    assert "standalone authored" in notes
    assert "iOS independently inlines" in notes


def test_mobile_matrix_premultiply_recovers_authored_member() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }

    premultiply = entries["premultiply_matrix_in_place"]
    assert premultiply["status"] == "verified"
    assert premultiply["confidence"] == "high"
    assert premultiply["source_object"] == "RMaths.o"
    assert premultiply["android_symbol"] == (
        "tMatrix::PreMultiply(tMatrix const&)"
    )
    assert premultiply["android_body_count"] == 1
    assert "ios_symbol" not in premultiply
    assert "tMatrix_PreMultiply" in (
        functions_by_name["premultiply_matrix_in_place"]["aliases"]
    )

    android_body = (
        repo_root
        / (
            "analysis/decompile/android/functions/"
            "000276f8-_ZN7tMatrix11PreMultiplyERKS_.c"
        )
    ).read_text(encoding="utf-8")
    assert android_body.count("= *(undefined4 *)") == 16
    assert "Multiply(this,param_1,(tMatrix *)&uStack_50)" in android_body

    notes = (
        repo_root
        / "tools/match/scratches"
        / "premultiply_matrix_in_place"
        / "NOTES.md"
    ).read_text(encoding="utf-8")
    assert "standalone authored" in notes
    assert "four-byte" in notes
    assert "no standalone `PreMultiply` export" in notes


def test_mobile_object_text_loader_rejects_binary_object_owner() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }

    loader = entries["load_object_definition"]
    assert loader["status"] == "verified"
    assert loader["confidence"] == "high"
    assert loader["source_object"] == "ObjectProc.o"
    assert loader["android_symbol"] == (
        "ObjectTextLoad(char*, cRObject*)"
    )
    assert loader["ios_symbol"] == loader["android_symbol"]
    assert loader["android_body_count"] == 1
    assert loader["ios_body_count"] == 1
    assert "ObjectTextLoad" in (
        functions_by_name["load_object_definition"]["aliases"]
    )
    assert "separate binary object loader" in (
        functions_by_name["load_object_definition"]["description"]
    )

    for port, path in (
        (
            "android",
            (
                "analysis/decompile/android/functions/"
                "0003c7ec-_Z14ObjectTextLoadPcP8cRObject.c"
            ),
        ),
        (
            "ios",
            (
                "analysis/decompile/ios/functions/"
                "00016b78-_Z14ObjectTextLoadPcP8cRObject.c"
            ),
        ),
    ):
        body = (repo_root / path).read_text(encoding="utf-8")
        assert "%s/_Object.txt" in body, port
        assert "[VERTEX START]" in body, port
        assert "[FACEQUAD START]" in body, port
        assert "RTextExtractFloat" in body, port

    notes = (
        repo_root
        / "tools/match/scratches/load_object_definition/NOTES.md"
    ).read_text(encoding="utf-8")
    assert "`cRObject::Load(char*)` is a different" in notes
    assert "`ObjectProc.o` ownership" in notes


def test_mobile_rng_pair_recovers_authored_contract() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }

    expected = {
        "random_float_below": ("RAND(float, char*)", "RAND"),
        "random_signed_float_below": ("SRAND(float, char*)", "SRAND"),
    }
    for windows_name, (mobile_symbol, alias) in expected.items():
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["source_object"] == "RMaths.o"
        assert entry["android_symbol"] == mobile_symbol
        assert entry["ios_symbol"] == mobile_symbol
        assert entry["android_body_count"] == 1
        assert entry["ios_body_count"] == 1
        assert alias in functions_by_name[windows_name]["aliases"]

    rmath_init = entries["initialize_trigonometry_tables"]
    assert rmath_init["status"] == "verified"
    assert rmath_init["source_object"] == "RMaths.o"
    assert rmath_init["android_symbol"] == "RMathInit()"
    assert rmath_init["ios_symbol"] == "RMathInit()"
    assert rmath_init["android_body_count"] == 1
    assert rmath_init["ios_body_count"] == 1
    assert "RMathInit" in (
        functions_by_name["initialize_trigonometry_tables"]["aliases"]
    )

    random_init = entries["initialize_math_random_table"]
    assert random_init["status"] == "verified"
    assert random_init["android_symbol"] == "gRMathRand2Init()"
    assert random_init["android_body_count"] == 1
    assert "gRMathRand2Init" in (
        functions_by_name["initialize_math_random_table"]["aliases"]
    )

    random_header = (
        repo_root / "tools/match/include/rmath_random.h"
    ).read_text(encoding="utf-8")
    assert (
        "float __cdecl random_float_below(float upper_bound, char* tag);"
        in random_header
    )
    assert (
        "float __cdecl random_signed_float_below("
        "float upper_bound, char* tag);"
        in random_header
    )
    assert "void __cdecl initialize_math_random_table();" in random_header
    assert "void __cdecl initialize_trigonometry_tables();" in random_header


def test_mobile_rtext_family_recovers_rshell_ownership_and_real_abis() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }

    expected = {
        "copy_c_string": "RTextCopy(char*, char*)",
        "strings_equal_case_insensitive": "RTextCompStart(char*, char*)",
        "skip_to_next_line": "RTextNewLine(char**)",
        "append_c_string": "RTextAppend(char*, char*)",
        "parse_next_space_delimited_token": (
            "RTextExtractString(char**, char*)"
        ),
        "parse_next_int32": "RTextExtractInt(char**)",
        "parse_next_float32": "RTextExtractFloat(char**)",
    }
    for windows_name, mobile_symbol in expected.items():
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["source_object"] == "RShell.o"
        assert entry["android_symbol"] == mobile_symbol
        assert entry["ios_symbol"] == mobile_symbol
        assert entry["android_body_count"] == 1
        assert entry["ios_body_count"] == 1
        assert mobile_symbol.split("(", 1)[0] in (
            functions_by_name[windows_name]["aliases"]
        )

    assert "`Rstrcmp` is strict equality" in (
        functions_by_name["strings_equal_case_insensitive"]["description"]
    )
    assert "code-equivalent" in (
        functions_by_name["parse_next_float32"]["description"]
    )

    rtext_header = (
        repo_root / "tools/match/include/rtext.h"
    ).read_text(encoding="utf-8")
    for declaration in (
        "void __cdecl copy_c_string(char* destination, char* source);",
        "char* left, char* prefix",
        "void __cdecl skip_to_next_line(char** cursor);",
        "void __cdecl append_c_string(char* destination, char* source);",
        "void __cdecl parse_next_space_delimited_token(",
        "int __cdecl parse_next_int32(char** cursor);",
        "float __cdecl parse_next_float32(char** cursor);",
    ):
        assert declaration in rtext_header

    binja_replay = (
        repo_root / "tools/binja/sync_rtext_types.py"
    ).read_text(encoding="utf-8")
    ida_replay = (
        repo_root / "tools/ida/apply_rtext_types.py"
    ).read_text(encoding="utf-8")
    assert "double __cdecl parse_next_float32" not in binja_replay
    assert "double __cdecl parse_next_float32" not in ida_replay
    assert "float __cdecl parse_next_float32" in binja_replay
    assert "float __cdecl parse_next_float32" in ida_replay
    for string_name in (
        "g_object_text_definition_path_format",
        "g_object_text_vertex_start",
        "g_object_text_vertex_end",
        "g_object_text_facequad_start",
        "g_object_text_facequad_end",
        "g_object_text_tga_extension",
        "g_object_text_path_separator",
    ):
        assert string_name in ida_replay
    assert not (
        repo_root / "tools/binja/sync_parse_helper_prototypes.py"
    ).exists()
    assert not (
        repo_root / "analysis/headers/bn_parse_helper_prototypes.h"
    ).exists()

    binja_sync = (
        repo_root / "tools/binja/sync_rmath_types.py"
    ).read_text(encoding="utf-8")
    ida_apply = (
        repo_root / "tools/ida/apply_rmath_types.py"
    ).read_text(encoding="utf-8")
    ida_runner = (
        repo_root / "tools/ida/sync_rmath_types.py"
    ).read_text(encoding="utf-8")
    for source in (binja_sync, ida_apply):
        for address, windows_name in (
            ("44c8d0", "initialize_math_random_table"),
            ("44c930", "initialize_trigonometry_tables"),
            ("44dc70", "random_signed_float_below"),
            ("44dc90", "random_float_below"),
        ):
            assert address in source.lower()
            assert windows_name in source
        assert "float upper_bound, char" in source
        assert "void __cdecl initialize_math_random_table()" in source
        assert "void __cdecl initialize_trigonometry_tables()" in source
    assert "RNG_CALLERS" in binja_sync
    assert "DIRTY_FUNCTIONS" in ida_apply
    assert '(0x4A4C90, "g_rng_tag_mirror")' in ida_apply
    assert "literal `str:Mirror`" in ida_apply
    assert "find_ida_binary(args.ida_bin)" in ida_runner

    scratch_paths = (
        repo_root / "tools/match/scratches"
    ).glob("*/scratch.cpp")
    random_scratches = []
    for scratch_path in scratch_paths:
        scratch = scratch_path.read_text(encoding="utf-8")
        if (
            "random_float_below(" in scratch
            or "random_signed_float_below(" in scratch
        ):
            random_scratches.append(scratch_path)
            assert '#include "rmath_random.h"' in scratch
    assert random_scratches


def test_mobile_rstring_family_recovers_strict_comparator_and_windows_abi() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }

    expected = {
        "ascii_upper_if_lowercase": "RstrASC(char)",
        "rstrcpy_checked_ascii": "Rstrcpy(char*, char const*)",
        "find_case_insensitive_substring": "Rstrfind(char*, char*)",
        "advance_to_next_crlf_line": "Rstrnewline(char*)",
        "strings_equal_case_insensitive_path": "Rstrcmp(char*, char*)",
        "parse_next_signed_int": "Rstrint(char**)",
    }
    for windows_name, mobile_symbol in expected.items():
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["source_object"] == "RString.o"
        assert entry["android_symbol"] == mobile_symbol
        assert entry["ios_symbol"] == mobile_symbol
        assert entry["android_body_count"] == 1
        assert entry["ios_body_count"] == 1
        assert mobile_symbol.split("(", 1)[0] in (
            functions_by_name[windows_name]["aliases"]
        )

    comparator_description = functions_by_name[
        "strings_equal_case_insensitive_path"
    ]["description"]
    assert "strict ASCII-case-insensitive equality" in comparator_description
    assert "full int" in comparator_description
    assert "inferred bool ABI changes" in comparator_description

    rstring_header = (
        repo_root / "tools/match/include/rstring.h"
    ).read_text(encoding="utf-8")
    for declaration in (
        "char __cdecl ascii_upper_if_lowercase(char value);",
        "char* destination, const char* source",
        "char* pattern, char* searched",
        "char* __cdecl advance_to_next_crlf_line(char* cursor);",
        "int __cdecl strings_equal_case_insensitive_path(",
        "int __cdecl parse_next_signed_int(char** cursor);",
    ):
        assert declaration in rstring_header
    assert "bool __cdecl strings_equal_case_insensitive_path" not in rstring_header

    binja_replay = (
        repo_root / "tools/binja/sync_rstring_types.py"
    ).read_text(encoding="utf-8")
    ida_replay = (
        repo_root / "tools/ida/apply_rstring_types.py"
    ).read_text(encoding="utf-8")
    ida_runner = (
        repo_root / "tools/ida/sync_rstring_types.py"
    ).read_text(encoding="utf-8")
    for source in (binja_replay, ida_replay):
        for address, windows_name in (
            ("44e5a0", "ascii_upper_if_lowercase"),
            ("44e5b0", "rstrcpy_checked_ascii"),
            ("44e600", "find_case_insensitive_substring"),
            ("44e690", "advance_to_next_crlf_line"),
            ("44e6c0", "strings_equal_case_insensitive_path"),
            ("44e710", "parse_next_signed_int"),
        ):
            assert address in source.lower()
            assert windows_name in source
        assert "bool __cdecl strings_equal_case_insensitive_path" not in source
    for dependency in (
        "GALAXY_LAYOUT_USER_VAR_UPDATES",
        "verify_galaxy_layout_owners",
        "apply_user_var_updates",
    ):
        assert dependency in binja_replay
    assert "IDAPython RString sync script" in ida_runner
    assert "IDA 9.4" in ida_runner

    for archive_replay_path in (
        repo_root / "tools/binja/sync_archive_shell_types.py",
        repo_root / "tools/ida/apply_archive_shell_types.py",
    ):
        archive_replay = archive_replay_path.read_text(encoding="utf-8")
        assert "strings_equal_case_insensitive" not in archive_replay
        assert "find_case_insensitive_substring" not in archive_replay
    for archive_header_path in (
        repo_root / "analysis/headers/archive_shell_types.h",
        repo_root / "analysis/headers/bn_archive_shell_types.h",
    ):
        archive_header = archive_header_path.read_text(encoding="utf-8")
        assert "strings_equal_case_insensitive" not in archive_header
        assert "find_case_insensitive_substring" not in archive_header

    scratch_sources = "\n".join(
        path.read_text(encoding="utf-8")
        for path in (repo_root / "tools/match/scratches").glob("*/scratch.cpp")
    )
    for stale_declaration in (
        "void rstrcpy_checked_ascii(char* destination, char* source);",
        "char* find_case_insensitive_substring(char* needle, char* haystack);",
        "char* advance_to_next_crlf_line(char* cursor);",
        "int strings_equal_case_insensitive_path(char* left, char* right);",
        "int parse_next_signed_int(char** cursor);",
    ):
        assert stale_declaration not in scratch_sources
    assert '#include "rstring.h"' in (
        repo_root / "tools/match/include/high_score.h"
    ).read_text(encoding="utf-8")
    assert "regressed the focused match to 87.88%" in (
        repo_root
        / "tools/match/scratches/strings_equal_case_insensitive_path/NOTES.md"
    ).read_text(encoding="utf-8")
    galaxy_notes = (
        repo_root / "tools/match/scratches/load_galaxy_layout/NOTES.md"
    ).read_text(encoding="utf-8")
    assert "RString.o::Rstrint(char**)" in galaxy_notes
    assert "edi->r:-4.d" in galaxy_notes
    assert "rather than claiming a false owner" in galaxy_notes


def test_mobile_cli_prints_verified_cross_port_paths(capsys) -> None:
    result = main(
        [
            "match",
            "mobile",
            "initialize_slalom_path_template_pair",
            "--paths-only",
        ]
    )

    output = capsys.readouterr().out
    assert result == 0
    assert "mapping: verified" in output
    assert "windows/binja" in output
    assert "cRPath::BuildSlalom(" in output
    assert "android: verified" in output
    assert "ios: verified" in output


def test_mobile_cli_ranks_pending_verified_bodies(
    capsys,
    monkeypatch,
    tmp_path: Path,
) -> None:
    crosswalk = tmp_path / "crosswalk.json"
    crosswalk.write_text(
        """{
  "entries": [
    {
      "windows_name": "update_subgoldy",
      "status": "verified",
      "android_body_count": 1,
      "ios_body_count": 1,
      "confidence": "high",
      "source_object": "SubGoldy.o"
    },
    {
      "windows_name": "update_input",
      "status": "verified",
      "android_body_count": 1,
      "confidence": "high",
      "source_object": null
    },
    {
      "windows_name": "initialize_input_ok",
      "status": "verified",
      "android_body_count": 1,
      "confidence": "high",
      "source_object": null
    }
  ]
}
""",
        encoding="utf-8",
    )
    statuses = [
        SimpleNamespace(
            config=SimpleNamespace(function="update_subgoldy"),
            state="wip",
            ratio=0.75,
            target_size=800,
        ),
        SimpleNamespace(
            config=SimpleNamespace(function="update_input"),
            state="wip",
            ratio=0.5,
            target_size=40,
        ),
        SimpleNamespace(
            config=SimpleNamespace(function="initialize_input_ok"),
            state="match",
            ratio=1.0,
            target_size=64,
        ),
    ]
    monkeypatch.setattr(
        "snail.cli.collect_scratch_statuses",
        lambda manifest, image_path, jobs: statuses,
    )

    result = main(
        [
            "match",
            "mobile",
            "--pending",
            "--limit",
            "2",
            "--crosswalk",
            str(crosswalk),
        ]
    )

    output = capsys.readouterr().out
    assert result == 0
    assert "verified mobile bodies for non-proof Windows targets: 2" in output
    assert "200.0  75.00%    800  A1/I1" in output
    assert "SubGoldy.o" in output
    assert "update_subgoldy" in output
    assert "20.0  50.00%     40  A1" in output
    assert "update_input" in output
    assert "initialize_input_ok" not in output


def test_mobile_object_vertex_dedup_preserves_platform_layout_boundary() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }

    dedup = entries["get_or_append_object_texture_group_vertex"]
    assert dedup["status"] == "verified"
    assert dedup["confidence"] == "high"
    assert dedup["source_object"] == "RObject.o"
    assert dedup["android_symbol"] == (
        "AddVertexUV(cGLVertexUV*, int&, tVector*, float, float)"
    )
    assert dedup["android_body_count"] == 1
    assert "ios_symbol" not in dedup
    assert "AddVertexUV" in (
        functions_by_name[
            "get_or_append_object_texture_group_vertex"
        ]["aliases"]
    )

    notes = (
        repo_root
        / "tools/match/scratches"
        / "get_or_append_object_texture_group_vertex"
        / "NOTES.md"
    ).read_text(encoding="utf-8")
    assert "0x14-byte position/UV record" in notes
    assert "0x1c-byte `ObjectGroupedVertex`" in notes


def test_mobile_object_texture_join_recovers_authored_free_function() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }

    texture_join = entries["sort_object_faces_by_texture_group"]
    assert texture_join["status"] == "verified"
    assert texture_join["confidence"] == "high"
    assert texture_join["source_object"] == "ObjectProc.o"
    assert texture_join["android_symbol"] == (
        "ObjectProcJoinTextures(cRObject*)"
    )
    assert texture_join["ios_symbol"] == texture_join["android_symbol"]
    assert texture_join["android_body_count"] == 1
    assert texture_join["ios_body_count"] == 1
    assert "ObjectProcJoinTextures" in (
        functions_by_name["sort_object_faces_by_texture_group"]["aliases"]
    )

    notes = (
        repo_root
        / "tools/match/scratches"
        / "sort_object_faces_by_texture_group"
        / "NOTES.md"
    ).read_text(encoding="utf-8")
    assert "`ObjectProcJoinTextures(cRObject*)`" in notes
    assert "authored alias" in notes
    assert "does not turn the" in notes
    assert "operation into a `cRObject` member" in notes


def test_mobile_object_null_recovers_authored_free_function() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }

    object_null = entries["disable_object_rendering"]
    assert object_null["status"] == "verified"
    assert object_null["confidence"] == "high"
    assert object_null["source_object"] == "ObjectProc.o"
    assert object_null["android_symbol"] == "ObjectProcNull(cRObject*)"
    assert object_null["ios_symbol"] == object_null["android_symbol"]
    assert object_null["android_body_count"] == 1
    assert object_null["ios_body_count"] == 1
    assert "ObjectProcNull" in (
        functions_by_name["disable_object_rendering"]["aliases"]
    )

    notes = (
        repo_root
        / "tools/match/scratches"
        / "disable_object_rendering"
        / "NOTES.md"
    ).read_text(encoding="utf-8")
    assert "`ObjectProcNull(cRObject*)`" in notes
    assert "same pair of newly bound path objects" in notes
    assert "without importing a false field" in notes


def test_mobile_object_tile_helpers_recover_authored_free_functions() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    expected = {
        "initialize_textured_backdrop_quad": (
            "ObjectProcTileFast(cRObject*, char*, float)",
            "ObjectProcTileFast",
        ),
        "raise_backdrop_quad_edge_pair": (
            "ObjectProcTileFastRamp(int, cRObject*)",
            "ObjectProcTileFastRamp",
        ),
        "initialize_backdrop_slice_quad": (
            "ObjectProcTileFloorFast(cRObject*, char*, float)",
            "ObjectProcTileFloorFast",
        ),
        "initialize_backdrop_corner_quad": (
            "ObjectProcTileFloorCornerFast(int, cRObject*, char*)",
            "ObjectProcTileFloorCornerFast",
        ),
        "initialize_backdrop_tile_quad": (
            "ObjectProcFringe(cRObject*, int, int, int, int, char*)",
            "ObjectProcFringe",
        ),
    }

    for windows_name, (mobile_symbol, alias) in expected.items():
        entry = entries[windows_name]
        assert entry["status"] == "verified"
        assert entry["confidence"] == "high"
        assert entry["source_object"] == "ObjectProc.o"
        assert entry["android_symbol"] == mobile_symbol
        assert entry["ios_symbol"] == mobile_symbol
        assert entry["android_body_count"] == 1
        assert entry["ios_body_count"] == 1
        assert alias in functions_by_name[windows_name]["aliases"]

        notes = (
            repo_root
            / "tools/match/scratches"
            / windows_name
            / "NOTES.md"
        ).read_text(encoding="utf-8")
        assert f"`{mobile_symbol}`" in notes
        assert "ObjectProc.o" in notes


def test_mobile_face_heightmap_chain_recovers_authored_owner() -> None:
    repo_root = Path(__file__).parents[1]
    crosswalk = load_json(DEFAULT_MOBILE_CROSSWALK_PATH)
    entries = {
        entry["windows_name"]: entry
        for entry in crosswalk["entries"]
    }
    functions = load_json(
        repo_root / "analysis/symbols/gameplay-functions.json"
    )
    functions_by_name = {
        entry["name"]: entry
        for entry in functions["functions"]
    }
    references = load_json(
        repo_root / "analysis/symbols/gameplay-references.json"
    )
    references_by_address = {
        entry["address"]: entry
        for entry in references["symbols"]
    }

    sampler = entries["sample_smtrack_heightmap"]
    assert sampler["status"] == "verified"
    assert sampler["confidence"] == "high"
    assert sampler["android_symbol"] == (
        "ObjectProcLandScapeUpdate("
        "cRObject*, float, float, cRTexture*, bool)"
    )
    assert sampler["ios_symbol"] == sampler["android_symbol"]
    assert sampler["android_body_count"] == 1
    assert sampler["ios_body_count"] == 1

    face_ai = entries["update_smtracks"]
    assert face_ai["status"] == "verified"
    assert face_ai["android_symbol"] == "cRFace::AI()"
    assert face_ai["ios_symbol"] == "cRFace::AI()"
    assert face_ai["source_object"] == "SubGame.o"
    assert face_ai["android_body_count"] == 1
    assert face_ai["ios_body_count"] == 1

    movie_ai = entries["advance_frame_sequence"]
    assert movie_ai["status"] == "verified"
    assert movie_ai["confidence"] == "high"
    assert movie_ai["android_symbol"] == "cRMovie::AI()"
    assert movie_ai["ios_symbol"] == "cRMovie::AI()"
    assert movie_ai["source_object"] == "RObject.o"
    assert movie_ai["android_body_count"] == 1
    assert movie_ai["ios_body_count"] == 1

    assert "ObjectProcLandScapeUpdate" in (
        functions_by_name["sample_smtrack_heightmap"]["aliases"]
    )
    assert "cRFace_AI" in functions_by_name["update_smtracks"]["aliases"]
    assert "cRMovie_AI" in (
        functions_by_name["advance_frame_sequence"]["aliases"]
    )
    callback_table = references_by_address["0x4972f8"]
    assert callback_table["name"] == "g_face_callback_table"
    assert "g_smtracks_callback_table" in callback_table["aliases"]

    matcher_header = (
        repo_root / "tools/match/include/smtracks.h"
    ).read_text(encoding="utf-8")
    movie_header = (
        repo_root / "tools/match/include/movie.h"
    ).read_text(encoding="utf-8")
    assert "class Face : public BodBase" in matcher_header
    assert "Movie movie;" in matcher_header
    assert "class Movie : public Object" in movie_header
    assert "bool cubic" in matcher_header
    assert "SmtrackHeightfieldAnimator" not in matcher_header
    assert "FrameSequence" not in matcher_header
