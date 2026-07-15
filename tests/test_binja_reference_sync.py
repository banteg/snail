from __future__ import annotations

import importlib.util
import json
from pathlib import Path
import sys


REPO_ROOT = Path(__file__).resolve().parents[1]
BINJA_DIR = REPO_ROOT / "tools/binja"
MODULE_PATH = BINJA_DIR / "sync_references.py"
if str(BINJA_DIR) not in sys.path:
    sys.path.insert(0, str(BINJA_DIR))
SPEC = importlib.util.spec_from_file_location("binja_sync_references", MODULE_PATH)
assert SPEC is not None and SPEC.loader is not None
SYNC_REFERENCES = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SYNC_REFERENCES)


def table_symbol(
    *,
    address: int = 0x402484,
    name: str = "initialize_frontend_widget_type_jump_table",
    kind: str = "jump_table",
) -> dict[str, object]:
    return {
        "address": address,
        "name": name,
        "kind": kind,
        "bn_kind": "data",
        "aliases": [],
        "description": "Compiler-emitted state table.",
    }


def test_load_references_includes_functions_and_compiler_tables(tmp_path: Path) -> None:
    manifest = tmp_path / "references.json"
    manifest.write_text(
        json.dumps(
            {
                "symbols": [
                    {
                        "address": "0x401000",
                        "name": "initialize_array",
                        "kind": "function",
                    },
                    {
                        "address": "0x402484",
                        "name": "widget_jump_table",
                        "kind": "jump_table",
                        "aliases": ["$L100"],
                    },
                    {
                        "address": "0x4024a0",
                        "name": "widget_lookup_table",
                        "kind": "lookup_table",
                    },
                    {
                        "address": "0x4df904",
                        "name": "g_game",
                        "kind": "global",
                    },
                ]
            }
        ),
        encoding="utf-8",
    )

    references = SYNC_REFERENCES._load_references(manifest)

    assert [reference["name"] for reference in references] == [
        "initialize_array",
        "widget_jump_table",
        "widget_lookup_table",
    ]
    assert [reference["bn_kind"] for reference in references] == [
        "function",
        "data",
        "data",
    ]


def test_auto_table_name_must_match_kind_and_address() -> None:
    symbol = table_symbol()

    assert SYNC_REFERENCES._is_auto_reference_name(symbol, "jump_table_402484")
    assert not SYNC_REFERENCES._is_auto_reference_name(symbol, "jump_table_402485")
    assert not SYNC_REFERENCES._is_auto_reference_name(symbol, "lookup_table_402484")
    assert not SYNC_REFERENCES._is_auto_reference_name(symbol, "curated_table")


def test_reference_sync_defaults_to_functions_scope(monkeypatch) -> None:
    monkeypatch.setattr(sys, "argv", ["sync_references.py"])

    args = SYNC_REFERENCES.parse_args()

    assert args.scope == "functions"


def test_load_live_table_symbols_uses_one_read_only_bn_query(monkeypatch) -> None:
    calls: list[list[str]] = []

    def run_bn(args: list[str]) -> dict[str, object]:
        calls.append(args)
        return {
            "result": [
                {
                    "address": "0x402484",
                    "name": "jump_table_402484",
                    "symbol_type": "SymbolType.DataSymbol",
                }
            ]
        }

    monkeypatch.setattr(SYNC_REFERENCES, "_run_bn_json", run_bn)
    symbols = [
        {
            "address": 0x401000,
            "kind": "function",
        },
        table_symbol(),
    ]

    live = SYNC_REFERENCES._load_live_table_symbols("snail.bndb", symbols)

    assert live[0x402484]["name"] == "jump_table_402484"
    assert len(calls) == 1
    assert calls[0][:5] == ["py", "exec", "--target", "snail.bndb", "--code"]
    assert "4203652" in calls[0][5]
    assert "4198400" not in calls[0][5]


def test_sync_table_reference_uses_data_symbol_and_address_comment(monkeypatch) -> None:
    calls: list[list[str]] = []

    def run_bn(args: list[str]) -> dict[str, bool]:
        calls.append(args)
        return {"success": True}

    monkeypatch.setattr(SYNC_REFERENCES, "_run_bn_json", run_bn)
    symbol = table_symbol()

    result = SYNC_REFERENCES._sync_reference(
        symbol=symbol,
        current_name="jump_table_402484",
        target="snail.bndb",
        dry_run=False,
        replace_existing=False,
        skip_comments=False,
    )

    assert result["status"] == "synced"
    assert calls == [
        [
            "symbol",
            "rename",
            "--target",
            "snail.bndb",
            "--kind",
            "data",
            "0x402484",
            "initialize_frontend_widget_type_jump_table",
        ],
        [
            "comment",
            "set",
            "--target",
            "snail.bndb",
            "--address",
            "0x402484",
            "Compiler-emitted state table.",
        ],
    ]


def test_sync_table_reference_preserves_unlisted_curated_name(monkeypatch) -> None:
    monkeypatch.setattr(
        SYNC_REFERENCES,
        "_run_bn_json",
        lambda _args: (_ for _ in ()).throw(AssertionError("must not mutate")),
    )

    result = SYNC_REFERENCES._sync_reference(
        symbol=table_symbol(),
        current_name="existing_curated_table",
        target="snail.bndb",
        dry_run=False,
        replace_existing=False,
        skip_comments=False,
    )

    assert result["status"] == "conflict"
    assert result["current"] == "existing_curated_table"


def test_main_preflights_all_conflicts_before_mutating(
    tmp_path: Path, monkeypatch, capsys
) -> None:
    manifest = tmp_path / "references.json"
    manifest.write_text(
        json.dumps(
            {
                "symbols": [
                    {
                        "address": "0x401000",
                        "name": "first_function",
                        "kind": "function",
                    },
                    {
                        "address": "0x401010",
                        "name": "second_function",
                        "kind": "function",
                    },
                ]
            }
        ),
        encoding="utf-8",
    )
    monkeypatch.setattr(
        SYNC_REFERENCES,
        "_load_live_functions",
        lambda _target: {
            0x401000: {"address": "0x401000", "name": "sub_401000"},
            0x401010: {"address": "0x401010", "name": "curated_second"},
        },
    )
    monkeypatch.setattr(
        SYNC_REFERENCES,
        "_run_bn_json",
        lambda _args: (_ for _ in ()).throw(AssertionError("must not mutate")),
    )
    monkeypatch.setattr(
        sys,
        "argv",
        ["sync_references.py", "--manifest", str(manifest)],
    )

    assert SYNC_REFERENCES.main() == 1
    report = json.loads(capsys.readouterr().out)
    assert report["renamed_count"] == 1
    assert report["conflict_count"] == 1
    assert report["apply_blocked_by_conflicts"] is True
