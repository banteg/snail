from __future__ import annotations

import json
from pathlib import Path

import pytest

from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    load_function_symbol_manifest,
    summarize_function_symbol_manifest,
    write_function_symbol_manifest,
)


def test_default_function_symbol_manifest_loads() -> None:
    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    summary = summarize_function_symbol_manifest(
        manifest,
        path=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    )
    min_address = min(function.address for function in manifest.functions)

    assert manifest.primary_target.endswith("SnailMail_unwrapped.exe")
    assert manifest.reference_target.endswith("SnailMail.RWG")
    assert manifest.functions[0].address == min_address
    assert any(function.name == "file_exists" for function in manifest.functions)
    assert manifest.functions[8].description is not None
    assert any(function.name == "get_or_create_texture_ref" for function in manifest.functions)
    assert summary["function_count"] == len(manifest.functions)
    assert summary["port_relevant_function_count"] == (
        summary["core_function_count"] + summary["boundary_function_count"]
    )
    assert summary["replaceable_platform_function_count"] > 0
    assert summary["third_party_function_count"] == 3
    assert sum(
        summary[key]
        for key in (
            "core_function_count",
            "boundary_function_count",
            "replaceable_platform_function_count",
            "third_party_function_count",
        )
    ) == len(manifest.functions)
    assert summary["described_function_count"] >= 1
    assert summary["alias_count"] >= 2
    assert summary["mobile_candidate_rejection_count"] >= 1
    assert summary["address_range"]["start"] == f"0x{min_address:x}"
    by_name = {function.name: function for function in manifest.functions}
    assert by_name["update_intro_logo_renderable"].aliases == (
        "update_logo_row",
        "cRLogoLetter_AI",
    )
    assert by_name["initialize_translation_matrix"].port_scope == "third-party"
    assert by_name["game_window_proc"].port_scope == "replaceable-platform"
    assert by_name["load_high_scores_from_file"].source_object == "HighScore.o"
    assert (
        by_name["load_high_scores_from_file"].source_object_evidence
        == "windows-contiguous-source-run"
    )
    game_init = by_name["initialize_game_assets_and_world"]
    assert game_init.source_object == "Game.o"
    assert game_init.source_object_evidence == "windows-contiguous-source-run"
    for name, source_object in {
        "initialize_global_temp_colour_thunk": "RObject.o",
        "initialize_global_temp_colour": "RObject.o",
        "initialize_parcel_set_bucket_pool_thunk": "SubGame.o",
        "initialize_parcel_set_bucket_pool": "SubGame.o",
        "initialize_zero_parcel_bucket_pool_thunk": "SubGame.o",
        "initialize_zero_parcel_bucket_pool": "SubGame.o",
    }.items():
        assert by_name[name].source_object == source_object
        assert (
            by_name[name].source_object_evidence
            == "ios-global-source-object"
        )
    assert {
        rejection.symbol
        for rejection in game_init.mobile_candidate_rejections
    } == {
        "cRGame::cRGame()",
        "cRGame::Init0()",
        "cRGame::Init1()",
        "cRGame::Init2()",
        "cRGame::Init3()",
        "cRGame::Init4()",
        "cRGame::Init5()",
        "cRGame::LoadPaths()",
    }


def test_write_function_symbol_manifest_preserves_normalized_shape(tmp_path: Path) -> None:
    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    output_path = tmp_path / "symbols.json"
    first_function = manifest.functions[0]

    write_function_symbol_manifest(manifest, output_path)
    raw = json.loads(output_path.read_text(encoding="utf-8"))

    assert raw["image_base"] == "0x400000"
    assert raw["functions"][0]["address"] == f"0x{first_function.address:x}"
    assert raw["functions"][0]["name"] == first_function.name
    assert "description" in raw["functions"][8]
    aliased = next(function for function in raw["functions"] if "aliases" in function)
    assert aliased["aliases"]
    third_party = next(
        function
        for function in raw["functions"]
        if function["name"] == "initialize_translation_matrix"
    )
    assert third_party["port_scope"] == "third-party"
    assert "port_scope" not in raw["functions"][0]
    high_score_load = next(
        function
        for function in raw["functions"]
        if function["name"] == "load_high_scores_from_file"
    )
    assert high_score_load["source_object"] == "HighScore.o"
    assert (
        high_score_load["source_object_evidence"]
        == "windows-contiguous-source-run"
    )
    game_init = next(
        function
        for function in raw["functions"]
        if function["name"] == "initialize_game_assets_and_world"
    )
    assert {
        rejection["symbol"]
        for rejection in game_init["mobile_candidate_rejections"]
    } == {
        "cRGame::cRGame()",
        "cRGame::Init0()",
        "cRGame::Init1()",
        "cRGame::Init2()",
        "cRGame::Init3()",
        "cRGame::Init4()",
        "cRGame::Init5()",
        "cRGame::LoadPaths()",
    }


@pytest.mark.parametrize(
    ("field", "value", "error"),
    [
        ("port_scope", "ignore", "port_scope must be one of"),
        (
            "match_scope",
            "reference-only",
            "match_scope was replaced by port_scope",
        ),
    ],
)
def test_invalid_or_legacy_function_scope_is_rejected(
    tmp_path: Path,
    field: str,
    value: str,
    error: str,
) -> None:
    manifest_path = tmp_path / f"invalid-{field}.json"
    manifest_path.write_text(
        json.dumps(
            {
                "name": "bad manifest",
                "primary_target": "artifacts/bin/SnailMail_unwrapped.exe",
                "reference_target": "artifacts/bin/SnailMail.RWG",
                "image_base": "0x400000",
                "unwrapped_sha256": "0" * 64,
                "functions": [
                    {
                        "address": "0x405140",
                        "name": "file_exists",
                        field: value,
                    }
                ],
            }
        ),
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match=error):
        load_function_symbol_manifest(manifest_path)


def test_duplicate_symbol_addresses_are_rejected(tmp_path: Path) -> None:
    manifest_path = tmp_path / "duplicate-addresses.json"
    manifest_path.write_text(
        json.dumps(
            {
                "name": "bad manifest",
                "primary_target": "artifacts/bin/SnailMail_unwrapped.exe",
                "reference_target": "artifacts/bin/SnailMail.RWG",
                "image_base": "0x400000",
                "unwrapped_sha256": "d365acf3db5335dded4dfd944e876ee2f23156595503693e0bf1baee1c8c83e5",
                "functions": [
                    {"address": "0x405140", "name": "file_exists"},
                    {"address": "0x405140", "name": "rebuild_game_archive_if_needed"},
                ],
            }
        ),
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match="duplicate function address"):
        load_function_symbol_manifest(manifest_path)


def test_duplicate_function_aliases_are_rejected(tmp_path: Path) -> None:
    manifest_path = tmp_path / "duplicate-aliases.json"
    manifest_path.write_text(
        json.dumps(
            {
                "name": "bad manifest",
                "primary_target": "artifacts/bin/SnailMail_unwrapped.exe",
                "reference_target": "artifacts/bin/SnailMail.RWG",
                "image_base": "0x400000",
                "unwrapped_sha256": "d365acf3db5335dded4dfd944e876ee2f23156595503693e0bf1baee1c8c83e5",
                "functions": [
                    {
                        "address": "0x405140",
                        "name": "file_exists",
                        "aliases": ["shared_name"],
                    },
                    {
                        "address": "0x405370",
                        "name": "rebuild_game_archive_if_needed",
                        "aliases": ["shared_name"],
                    },
                ],
            }
        ),
        encoding="utf-8",
    )

    with pytest.raises(ValueError, match="duplicate function name or alias: shared_name"):
        load_function_symbol_manifest(manifest_path)
