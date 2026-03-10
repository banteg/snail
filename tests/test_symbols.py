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
    assert summary["described_function_count"] >= 1
    assert summary["address_range"]["start"] == f"0x{min_address:x}"


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
