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


def test_mobile_track_pipeline_keeps_warn_and_desalt_owners_distinct() -> None:
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

    warn = entries["promote_track_tiles_to_fringe_variants"]
    assert warn["status"] == "verified"
    assert warn["confidence"] == "high"
    assert warn["android_symbol"] == "cRSubGame::WarnTrack()"
    assert warn["android_body_count"] == 1
    assert "ios_symbol" not in warn
    assert "WarnTrack" in (
        functions_by_name["promote_track_tiles_to_fringe_variants"][
            "aliases"
        ]
    )

    desalt = entries["mark_track_warning_zones"]
    assert desalt["status"] == "verified"
    assert desalt["confidence"] == "high"
    assert desalt["android_symbol"] == "cRSubGame::DeSaltTrack()"
    assert desalt["android_body_count"] == 1
    assert "ios_symbol" not in desalt
    assert "DeSaltTrack" in (
        functions_by_name["mark_track_warning_zones"]["aliases"]
    )

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
