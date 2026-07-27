from __future__ import annotations

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
