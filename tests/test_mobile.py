from __future__ import annotations

from pathlib import Path

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

    sprite = entries["initialize_sprite"]
    assert sprite["status"] == "verified"
    assert sprite["confidence"] == "high"
    assert sprite["android_symbol"] == "cRSprite::Init()"
    assert sprite["android_body_count"] == 1
    assert "ios_symbol" not in sprite
    assert "0xb0" in verified_entries["initialize_sprite"]["notes"]
    assert "0xb4" in verified_entries["initialize_sprite"]["notes"]
    assert "cRSprite_Init" in functions_by_name["initialize_sprite"]["aliases"]

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
    player_header = (
        repo_root / "tools/match/include/player.h"
    ).read_text(encoding="utf-8")
    assert "typedef Sprite cRSprite;" in sprite_header
    assert "typedef Player cRSubGoldy;" in player_header


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
