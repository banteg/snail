from __future__ import annotations

import importlib.util
import json
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[1]
MODULE_PATH = REPO_ROOT / "tools/ida/reference_manifest.py"
SPEC = importlib.util.spec_from_file_location("ida_reference_manifest", MODULE_PATH)
assert SPEC is not None and SPEC.loader is not None
REFERENCE_MANIFEST = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REFERENCE_MANIFEST)


def test_reference_manifest_skips_numeric_constants_and_offsets(tmp_path: Path) -> None:
    manifest_path = tmp_path / "references.json"
    manifest_path.write_text(
        json.dumps(
            {
                "symbols": [
                    {
                        "address": "0x401000",
                        "name": "real_global",
                        "kind": "global",
                        "description": "Address-backed storage.",
                    },
                    {
                        "address": "0x75cfff",
                        "name": "runtime_flag_preset",
                        "kind": "constant",
                    },
                    {
                        "address": "0x42fd7c",
                        "name": "player_block_offset",
                        "kind": "offset",
                    },
                ]
            }
        ),
        encoding="utf-8",
    )

    entries, skipped = REFERENCE_MANIFEST.load_address_backed_symbols(manifest_path)

    assert entries == [(0x401000, "real_global", "Address-backed storage.")]
    assert skipped == [
        {
            "address": 0x75CFFF,
            "name": "runtime_flag_preset",
            "kind": "constant",
        },
        {
            "address": 0x42FD7C,
            "name": "player_block_offset",
            "kind": "offset",
        },
    ]


def test_real_reference_manifest_keeps_numeric_preset_out_of_ida() -> None:
    manifest_path = REPO_ROOT / "analysis/symbols/gameplay-references.json"

    entries, skipped = REFERENCE_MANIFEST.load_address_backed_symbols(manifest_path)

    address_backed_names = {name for _, name, _ in entries}
    skipped_by_name = {entry["name"]: entry for entry in skipped}
    assert "k_runtime_flags_mode4" not in address_backed_names
    assert skipped_by_name["k_runtime_flags_mode4"] == {
        "address": 0x75CFFF,
        "name": "k_runtime_flags_mode4",
        "kind": "constant",
    }
    assert {entry["kind"] for entry in skipped} == {"constant", "offset"}
