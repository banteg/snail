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

    for declaration in (
        "GalaxyRouteNameRecord* __thiscall initialize_galaxy_route_name_record(",
        "void __thiscall load_galaxy_layout(Galaxy* galaxy);",
        "void __thiscall destroy_galaxy(Galaxy* galaxy);",
        "void __thiscall initialize_galaxy(Galaxy* galaxy);",
        "int32_t __thiscall update_galaxy(Galaxy* galaxy);",
        "int32_t __thiscall draw_galaxy_line(Galaxy* galaxy,",
        "void __thiscall update_galaxy_route_record(GalaxyRouteSlot* slot);",
        "void __thiscall close_galaxy_route(Galaxy* galaxy);",
        "void __thiscall open_galaxy_route(Galaxy* galaxy,",
        "void __thiscall galaxy_border_bound(Galaxy* galaxy,",
    ):
        assert declaration in ida_runtime_sync
    assert "GalaxyPoint g_galaxy_group_points[10];" in ida_runtime_sync
    assert "GalaxyPoint g_galaxy_route_points[101];" in ida_runtime_sync
    assert "TRUSTED_DATA_DECLARATIONS" in ida_runtime_sync

    for header in analysis_headers:
        assert "typedef struct GalaxyPoint" in header
        assert "GalaxyRouteSlot route_slots[101]" in header
        assert "GalaxyRouteNameRecord route_names[10]" in header

    assert "extern GalaxyPoint g_galaxy_group_points[10];" in matcher_header
    assert "extern GalaxyPoint g_galaxy_route_points[101];" in matcher_header


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

    for source in (
        binja_sync,
        ida_sync,
        broad_binja_sync,
        broad_ida_sync,
        analysis_header,
    ):
        assert "void __thiscall release_snail_weapons(Snail* snail)" in source
        assert "void __thiscall build_snail_hotspots(Snail* snail)" in source
        assert "void __thiscall update_snail_skin(Snail* snail)" in source
        assert (
            "int32_t __thiscall dispatch_cutscene_animation(Snail* snail, "
            "int32_t animation_id, uint8_t immediate, int32_t mode_flags)"
            in source
        )
        assert (
            "void __thiscall set_weapon_animation(Weapon* weapon, "
            "int32_t animation_id, uint8_t immediate, int32_t mode_flags)"
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
            ('"AnimManager"', "0x48"),
            ('"SubHover"', "0x214"),
            ('"Weapon"', "0x3DC"),
            ('"Invincible"', "0xA4"),
            ('"SnailSkin"', "0x20"),
            ('"Snail"', "0x19B4"),
            ('"Player"', "0x4364"),
        ):
            assert f"{owner}: {size}" in source

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

    prototypes = (
        "void __thiscall health_collect_particles(Player* player, SubHealth* pickup)",
        "void __thiscall update_movement_flag_emitters(Player* owner, Player* movement_source)",
        "void __thiscall end_jetpack_hover(SubHover* sub_hover)",
        "void __thiscall initialize_subgoldy(Player* player, int32_t player_slot)",
        "void __thiscall show_subgoldy_lives(Player* player)",
        "void __thiscall begin_post_follow_carryover(Player* player)",
        "void __thiscall play_movement_state_sound(Player* player)",
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
            ('"Weapon"', "0x3DC"),
            ('"Invincible"', "0xA4"),
            ('"Snail"', "0x19B4"),
            ('"Player"', "0x4364"),
            ('"SubgameRuntime"', "0x1272838"),
        ):
            assert f"{owner}: {size}" in source

    for address, name in (
        ("0x43a010", "health_collect_particles"),
        ("0x43a300", "update_movement_flag_emitters"),
        ("0x43a370", "end_jetpack_hover"),
        ("0x43a9c0", "initialize_subgoldy"),
        ("0x43af10", "show_subgoldy_lives"),
        ("0x43af60", "begin_post_follow_carryover"),
        ("0x43afd0", "play_movement_state_sound"),
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
    assert '"RegisterVariableSourceType",\n        1171,\n        73,' in binja_sync
    assert '"GolbShotFlightStrideCursor*"' in binja_sync
    assert '"RegisterVariableSourceType",\n        49,\n        73,' in binja_sync
    assert '"golb_shot_cursor",\n        "GolbShot*"' in binja_sync
    assert "0x43AE54" in ida_sync
    assert "GolbShotFlightStrideCursor *golb_shot_flight_cursor;" in ida_sync
    assert "INITIALIZE_SUBGOLDY_USER_VAR_UPDATES" in broad_binja_sync
    assert "MOVEMENT_FLAG_EMITTER_USER_VAR_UPDATES" in broad_binja_sync
    assert "INITIALIZE_SUBGOLDY_LVAR_SPECS" in broad_ida_sync
    assert "0x43AF60,  # begin_post_follow_carryover" in broad_ida_sync
    assert "0x445840,  # kill_subgoldy" in broad_ida_sync
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
            "FrameColor4f fog_color;",
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
        '("0x14", "fog_color", "FrameColor4f")',
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
        "update_sprite_facing_angle",
        "render_game_frame",
    ):
        assert f'"{selector}",' in frame_sync
    assert "def _sync_render_pointer_lvar" in frame_sync
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
    assert "UPDATE_BANNER_USER_VAR_UPDATES" in bn_path_sync
    assert '"game_bytes_for_message"' in bn_path_sync
    assert '"game_bytes_for_duration"' in bn_path_sync
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
    assert "EXPECTED_BACKDROP_SIZE = 0x6CC" in backdrop_apply
    assert "void __thiscall render_backdrop(Backdrop* backdrop);" in backdrop_apply
    assert "int32_t __thiscall update_backdrop(Backdrop* backdrop);" in backdrop_apply
    assert 'analysis/headers/bn_backdrop_types.h' in backdrop_sync


def test_binja_backdrop_owner_abis_are_directly_replayed() -> None:
    source = (BINJA_DIR / "sync_backdrop_types.py").read_text(encoding="utf-8")
    header = (HEADER_DIR / "bn_backdrop_types.h").read_text(encoding="utf-8")

    assert "apply_proto_updates" in source
    assert "types_declare_if_changed" in source
    assert "report_deferred_prototypes" not in source
    assert "proto_owner_deferred" not in source
    assert "typedef struct LandscapeScriptRecord {" in header
    assert "int32_t backdrop_texture_id;" in header
    assert "uint8_t split_backdrop_texture_pair;" in header
    assert "float distort;" in header
    for prototype in (
        "void __thiscall set_backdrop_progress_fraction(Backdrop* backdrop, float zoom)",
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
    assert 'return str(value).replace(" __pure", "")' in code


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
    assert '("0x44e410", "update_sprite_facing_angle")' in source
    assert '("0x44e800", "initialize_texture_list")' in source
    assert '("0x44e810", "get_or_create_texture_ref")' in source
    assert '("0x4b7790", "g_texture_refs")' in source
    assert '("0x4b7790", "TextureRefList")' in source
    assert "apply_data_var_updates" in source
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
            "void* __thiscall get_sprite_texture_ref(SpriteManager* manager, int32_t texture_id)",
            "void *__thiscall get_sprite_texture_ref(SpriteManager *manager, int32_t texture_id);",
        ),
        (
            "void __thiscall update_sprite_facing_angle(Sprite* sprite, const TransformMatrix* matrix)",
            "void __thiscall update_sprite_facing_angle("
            "Sprite *sprite, const struct TransformMatrix *matrix);",
        ),
    ):
        assert declaration in source
        assert ida_declaration in ida_source
    assert "TextureRef* __stdcall register_sprite_texture" not in source
    assert "TextureRef* __stdcall get_sprite_texture" not in source
    assert "TRUSTED_NAMES" in ida_source
    assert '(0x44DF30, "update_sprite")' in ida_source
    assert '(0x44E410, "update_sprite_facing_angle")' in ida_source
    assert '(0x44E800, "initialize_texture_list")' in ida_source
    assert '(0x44E810, "get_or_create_texture_ref")' in ida_source
    assert '(0x4B7790, "g_texture_refs")' in ida_source
    assert "TRUSTED_DATA_DECLARATIONS" in ida_source
    assert '"path_template_types.h"' in ida_source
    assert '"object_render_types.h"' in ida_source
    assert '"Object": 0xDC' in ida_source
    assert '"BodBase": 0x38' in ida_source
    assert '"TransformMatrix": 0x40' in ida_source
    assert '"TextureRefList": 0x14058' in source
    assert '"TextureRefList": 0x14058' in ida_source
    assert 're.sub(r"\\b(?:struct|union|enum)\\s+", "", normalized)' in ida_source
    assert "0x40A490" in ida_source
    assert "0x40ACF0" in ida_source
    assert "0x44E410" in ida_source
    assert "0x44E800" in ida_source
    assert "0x44E810" in ida_source
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
    assert "void __thiscall update_sprite_facing_angle(" in star_analysis_header
    assert "const struct TransformMatrix* matrix" in star_analysis_header
    assert "typedef struct TransformMatrix TransformMatrix;" not in star_analysis_header
    assert "#define TEXTURE_REF_LIST_CAPACITY 500" in star_analysis_header
    assert "TextureRef entries[TEXTURE_REF_LIST_CAPACITY];" in star_analysis_header
    assert "extern TextureRefList g_texture_refs;" in star_analysis_header
    assert "TEXTURE_REF_LIST_CAPACITY = 500" in sprite_matcher_header
    assert "void initialize_texture_list(int capacity);" in sprite_matcher_header
    assert "char* texture_path, void* payload, int flags" in sprite_matcher_header
    assert "TextureRef entries[TEXTURE_REF_LIST_CAPACITY];" in path_analysis_header
    assert "char* texture_path, void* payload," in path_analysis_header
    assert "int16_t arg4" not in path_analysis_header


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
        "int32_t __thiscall calc_path_length_z("
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
        '("0x4217b0", "calc_path_length_z")',
    ):
        assert symbol_update in source
    for trusted_name in (
        '(0x421770, "initialize_path_follow_golb")',
        '(0x4217B0, "calc_path_length_z")',
    ):
        assert trusted_name in ida_source
    for address in ("0x414820", "0x421770", "0x4217B0"):
        assert address in ida_source


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
    assert "DEFERRED_PATH_OWNER_PROTO_UPDATES" in source
    assert "proto_owner_deferred" in source
    assert "apply_struct_and_proto_updates" in source
    assert "apply_direct_proto_update" not in source
    assert "proto_owner_current" in source
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
        "void __thiscall initialize_looptheloop_path_template_pair(Path* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_looptheloopw_path_template_pair(Path* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_loopout_path_template_pair(Path* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_hump_path_template_pair(Path* self, float curve_source, float height_scale, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_dump_path_template_pair(Path* self, float curve_source, float height_scale, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_dip_path_template_pair(Path* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_screw_path_template_pair(Path* self, int32_t curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_slalom_path_template_pair(Path* self, int32_t curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_slalombig_path_template_pair(Path* self, int32_t curve_segments, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_sweep_path_template_pair(Path* self, float scale_arg, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_snake_path_template_pair(Path* self, float scale_arg, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_supertramp_path_template_pair(Path* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* unused_texture, char* cap_texture)",
        "void __thiscall initialize_slalomdouble_path_template_pair(Path* self, int32_t curve_segments, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_start_path_template_pair(Path* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_turnover_path_template_pair(Path* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_turnoverdouble_path_template_pair(Path* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_turnunder_path_template_pair(Path* self, float turns, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_wibble_path_template_pair(Path* self, float radius, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_invert_path_template_pair(Path* self, float radius, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_halfpipe_path_template_pair(Path* self, float scale, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_twister_path_template_pair(Path* self, float height, int32_t width_cells_, char handedness, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_twister2_path_template_pair(Path* self, float height, int32_t width_cells_, char handedness, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_p_path_template_pair(Path* self, int32_t variant, float scale_arg, int32_t width_cells_, float start_x, float end_x, int32_t curve_segments, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_loopbow_path_template_pair(Path* self, float curve_scale, uint32_t width_cells_arg, char mode, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_hill_valley_path_template_pair(Path* self, int32_t width_cells_, float height, float length, char centered, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_sbend_path_template_pair(Path* self, int32_t width_cells_, float height, float z_amplitude, char centered, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __fastcall allocate_path_template_samples(Path* self)",
        "void __fastcall finalize_path_template(Path* self)",
        "void __thiscall initialize_worm_path_template_pair(Path* self, char* texture_path)",
        "void __thiscall initialize_cage2_path_template_pair(Path* self, int32_t width_cells_, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_toad_path_template_pair(Path* self, char turn_left, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall mirror_path_template_pair_x(Path* self, Path* source)",
    ):
        assert declaration in deferred_path_prototypes
        assert "".join(f"{declaration};".split()) in compact_header
        assert "".join(f'"{declaration};"'.split()) in compact_ida_source
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
        "allocate_path_template_samples",
        "finalize_path_template",
        "initialize_worm_path_template_pair",
        "initialize_cage2_path_template_pair",
        "initialize_toad_path_template_pair",
        "mirror_path_template_pair_x",
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
        "void __thiscall update_movement_flag_emitters(Player* owner, Player* movement_source)",
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
        "    RenderableBod tertiary_body;"
    )
    matcher_owner = (
        "    RenderableBod primary_body; // +0x000, projectile AI/list owner\n"
        "    Vapour vapour; // +0x080, complete kind-1 trail renderer\n"
        "    GolbShot* vapour_owner_shot; // +0x114, kind-1 embedded-body backlink\n"
        "    RenderableBod tertiary_body; // +0x118, kind-2 rocket body"
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
        '("0x118", "tertiary_body", "RenderableBod")',
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
        "void __thiscall play_movement_state_sound(Player* player)",
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
    headers = tuple(
        (HEADER_DIR / header_name).read_text(encoding="utf-8")
        for header_name in ("bn_archive_shell_types.h", "archive_shell_types.h")
    )

    binja_declarations = (
        "char* __cdecl xor_decode_buffer_with_index(char* bytes, int32_t byte_count)",
        "int32_t __cdecl write_file_bytes(char* path, void* bytes, int32_t byte_count)",
        "char* __cdecl save_config_file(char* path, void* bytes, int32_t byte_count)",
    )
    ida_declarations = (
        "char* __cdecl xor_decode_buffer_with_index(char* bytes, int byte_count);",
        "int __cdecl write_file_bytes(char* path, void* bytes, int byte_count);",
        "char* __cdecl save_config_file(char* path, void* bytes, int byte_count);",
    )
    for declaration in binja_declarations:
        assert declaration in binja_source
        assert any(f"{declaration};" in header for header in headers)
    for declaration in ida_declarations:
        assert f'"{declaration}"' in ida_apply_source

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

    assert 'IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/apply_archive_shell_types.py"' in ida_sync_source
    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/archive_shell_types.h"' in ida_sync_source
    assert 'SYNC_FAILURE_SENTINEL = "ARCHIVE_SHELL_SYNC_FAILED"' in ida_apply_source
    assert 'SYNC_FAILURE_SENTINEL = "ARCHIVE_SHELL_SYNC_FAILED"' in ida_sync_source
    assert "if SYNC_FAILURE_SENTINEL in log_text:" in ida_sync_source
    assert "return exit_code or 1" in ida_sync_source


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
    assert '("0x44e410", "update_sprite_facing_angle")' in binja_source
    assert 'OBJECT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"' in binja_source
    assert 'SPRITE_HEADER_PATH = REPO_ROOT / "analysis/headers/star_manager_types.h"' in binja_source
    assert '"RenderableBod"' in binja_source
    assert '"Sprite"' in binja_source
    assert '"star_manager_types.h"' in ida_source
    assert '"update_sprite_facing_angle",' in ida_source
    assert 're.sub(r"\\b(?:struct|union|enum)\\s+", "", normalized)' in ida_source


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

    assert "InputControllerSlot_must_be_0x20" in matcher_controller_header
    assert "INPUT_CONTROLLER_SLOT_STRIDE = 0x38" in matcher_controller_header
    assert "g_input_controller_slot0" in matcher_controller_header
    assert "g_input_controller_slot1" in matcher_controller_header
    assert "g_input_controller_slots[" not in matcher_controller_header
    assert "unknown_20" not in matcher_controller_header
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
        assert "InputButtonFlag pressed_buttons;" in header
        assert "InputButtonFlag current_buttons;" in header

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
        "void __cdecl update_input_controller_pointer_region(",
        "void* __cdecl set_input_controller_pointer_authored_xy(",
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
        "INPUT_POINTER_REGION_FUNCTION_SYMBOL_UPDATES",
        "INPUT_POINTER_REGION_DATA_SYMBOL_UPDATES",
        "INPUT_POINTER_REGION_DATA_VAR_UPDATES",
        '("0x508890", "int32_t[2]")',
        '("0x508898", "int32_t[2]")',
        '("0x5088a0", "int32_t[2]")',
        '("0x5088a8", "int32_t[2]")',
        '"void __cdecl update_input_controller_pointer_region(int32_t slot, int32_t left, int32_t top, int32_t right, int32_t bottom, int32_t x, int32_t y, int32_t pointer_value, char button_a, char button_b, char button_c, char capture_when_outside, char force_clamp)"',
        '"void* __cdecl set_input_controller_pointer_authored_xy(int32_t slot, float authored_x, float authored_y)"',
    ):
        assert marker in binja_source

    assert '"int32_t __thiscall initialize_input(InputState* state)"' not in binja_source

    for marker in (
        '(0x50339C, 20, "g_text_input_repeat_step", "float[5]")',
        '(0x50333C, "g_input_controller_slot0")',
        '(0x503374, "g_input_controller_slot1")',
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
        '"void __cdecl update_input_controller_pointer_region(int slot, int left, int top, int right, int bottom, int x, int y, int pointer_value, char button_a, char button_b, char button_c, char capture_when_outside, char force_clamp);"',
        '"void *__cdecl set_input_controller_pointer_authored_xy(int slot, float authored_x, float authored_y);"',
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
    assert "gRShellKeyRepeatLifeRate" in aliases_by_address["0x50339c"]
    assert "gRShellKeyRepeatLife" in aliases_by_address["0x5108b8"]
    assert "gRShellOldKey" in aliases_by_address["0x53c7f5"]

    crosswalk = json.loads(
        (repo_root / "analysis/symbols/windows-ios-gameplay-crosswalk.json").read_text(
            encoding="utf-8"
        )
    )
    entries_by_address = {
        entry["address"]: entry for entry in crosswalk["entries"]
    }
    assert entries_by_address["0x432440"]["ios_symbol"] == "RShellInkey()"
    assert (
        entries_by_address["0x4327e0"]["ios_symbol"]
        == "RShellInkeyInput()"
    )


def test_ida_lvar_inspector_reports_stable_local_identity() -> None:
    inspector = (IDA_DIR / "inspect_function_lvars.py").read_text(encoding="utf-8")
    wrapper = (IDA_DIR / "query_function_lvars.py").read_text(encoding="utf-8")

    for marker in (
        "cfunc.get_lvars()",
        '"definition_address"',
        '"location"',
        '"stack_offset"',
        "lvar.get_stkoff()",
    ):
        assert marker in inspector
    assert 'IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/inspect_function_lvars.py"' in wrapper
    assert "script_args=list(args.selectors)" in wrapper


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

    for marker in (
        "ida_funcs.get_func(address)",
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
        "int32_t __thiscall recycle_bod_to_free_list(BodList* list, BodNode* node)",
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
    assert "int recycle_bod_to_free_list(BodNode* node);" in bod_list_header
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
        "request_object_facequad_normals",
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
        "0x42F9E0",
        "0x42FB10",
        "0x42FCB0",
        "0x430230",
        "0x4303F0",
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
        assert "Vec3* __thiscall request_object_facequad_normals(Object* object);" in header
        assert (
            "int32_t __thiscall calc_object_facequad_normals_simple(Object* object);"
            in header
        )
        assert "void __thiscall request_object_texture_groups(" in header


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
        "void __fastcall rotate_object_facequad_uv_pairs(ObjectFaceQuad* quad)",
    ):
        assert prototype in binja_sync
        assert prototype + ";" in ida_sync

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
            "int32_t __cdecl render_object_toon(\n"
            "    Object* object, TransformMatrix* matrix);"
        ) in header

    assert (
        "int32_t __cdecl render_object_toon(Object* object, "
        "TransformMatrix* matrix)"
    ) in binja_sync
    assert (
        "int __cdecl render_object_toon(Object* object, "
        "TransformMatrix* matrix);"
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
        "0x4129C0",
        "0x418B50",
        "0x433060",
    ):
        assert address in ida_sync

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
        "TransformMatrix* __cdecl render_camera(float viewport_x, float viewport_y, "
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
        assert "TransformMatrix* __cdecl render_camera(" in header
        assert (
            "TransformMatrix* __stdcall build_perspective_projection_matrix("
            in header
        )
        assert "TransformMatrix* __stdcall build_camera_view_matrix(" in header
        assert "extern Direct3DDevice8* g_d3d_device;" not in header

    assert '("0x502fec",' not in binja_sync
    assert '(0x502FEC,' not in ida_sync


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


def test_frame_sequence_ownership_stays_aligned_across_replay_lanes() -> None:
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
        repo_root / "tools/match/include/frame_sequence.h"
    ).read_text(encoding="utf-8")

    assert "FRAME_SEQUENCE_FIELDS = (" in binja_object_sync
    assert '("0x00", "object", "Object")' in binja_object_sync
    assert '("0xec", "current_texture_ref", "TextureRef*")' in binja_object_sync
    for source in (
        binja_object_sync,
        ida_object_sync,
        binja_path_sync,
        ida_path_sync,
    ):
        assert "advance_frame_sequence" in source
        assert "FrameSequence* sequence" in source
    for source in (binja_path_sync, ida_path_sync):
        assert "update_smtracks" in source
        assert "SmtrackHeightfieldAnimator* animator" in source
        assert "sample_smtrack_heightmap" in source
        assert "TextureRef* replacement" in source

    for header in (*analysis_headers, path_header, matcher_header):
        assert "FRAME_SEQUENCE_COMPLETE = 0x01" in header
        assert "FRAME_SEQUENCE_LOOP = 0x02" in header
        assert "FRAME_SEQUENCE_PING_PONG = 0x04" in header
        assert "FRAME_SEQUENCE_REVERSE = 0x08" in header
        assert "FRAME_SEQUENCE_PAUSED = 0x10" in header
    for header in analysis_headers:
        assert "typedef struct FrameSequence" in header
        assert "Object object;" in header
        assert "TextureRef* current_texture_ref;" in header
        assert "int32_t heightmap_sample_count;" in header
        assert "float heightmap_sample_divisor;" in header
        assert "float heightmap_sample_scale;" in header
    assert '("0x1c", "heightmap_sample_count", "int32_t")' in binja_object_sync
    assert '("0x24", "heightmap_sample_divisor", "float")' in binja_object_sync
    assert '("0x28", "heightmap_sample_scale", "float")' in binja_object_sync
    assert "typedef struct FrameSequenceObjectView" in path_header
    assert "ObjectFaceQuad* facequads;" in path_header
    assert "FrameSequenceObjectView object;" in path_header
    assert "TextureRef* current_texture_ref;" in path_header
    assert "uint8_t _storage[0xf0];" not in path_header


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
        assert "AUTHORED_SEGMENT_ROW_FLAG_STAR_MARKER = 0x0004" in header
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
    for address, name in (
        ("0x447090", "initialize_fringe_manager"),
        ("0x4470A0", "allocate_fringe_object"),
    ):
        assert f'({address}, "{name}")' in ida_path_sync
        assert f'"{name}"' in ida_path_sync
    for address in ("0x434BE0", "0x447090", "0x4470A0"):
        assert address in ida_path_sync

    assert "BUILD_SUBGAME_ACTIVE_BOD_USER_VAR_UPDATES" in binja_source
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

    assert "RUNTIME_POOL_ROW_OFFSET_OPERANDS" in ida_path_sync
    assert "(0x4082EC, 1, 0x5CCAC8)" in ida_path_sync
    assert (
        "runtime_pool_row_offset_operands = _normalize_root_offset_operands("
        in ida_path_sync
    )
    assert "*BUILD_SUBGAME_ACTIVE_BOD_USER_VAR_UPDATES" in binja_source

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
        "0x443DB8",
        "0x444009",
        "0x444162",
    ):
        assert definition_address in ida_path_sync
    for name, declaration in (
        (
            "parcel_set_runtime_row_anchor",
            "RuntimeRowStrideAnchor *parcel_set_runtime_row_anchor;",
        ),
        ("zero_runtime_row_anchor", "RuntimeRowStrideAnchor *zero_runtime_row_anchor;"),
        ("projection_row", "SubRow *projection_row;"),
    ):
        assert f'"{name}"' in ida_path_sync
        assert f'"{declaration}"' in ida_path_sync
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
    for definition_address in ("0x44432E", "0x4443D8"):
        assert definition_address in ida_path_sync
    for name, declaration in (
        (
            "challenge_runtime_row_anchor",
            "RuntimeRowStrideAnchor *challenge_runtime_row_anchor;",
        ),
        ("projection_row", "SubRow *projection_row;"),
    ):
        assert f'"{name}"' in ida_path_sync
        assert f'"{declaration}"' in ida_path_sync
    assert "_sync_challenge_parcels_runtime_lvars" in ida_path_sync
    assert "CHALLENGE_PARCELS_RUNTIME_ROW_OFFSET_OPERANDS" in ida_path_sync
    for operand_spec in (
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

    assert "BUILD_SUBGAME_ACTIVE_BOD_LVAR_SPECS" in ida_path_sync
    for definition_address in (
        "0x4383CD",
        "0x4383D3",
        "0x4383F7",
        "0x438426",
        "0x43842B",
        "0x43844F",
        "0x43847E",
        "0x438483",
        "0x4384A7",
        "0x4384D6",
        "0x4384DB",
        "0x4384FF",
        "0x43852E",
        "0x438533",
        "0x438557",
        "0x438595",
        "0x43859A",
        "0x4385BE",
        "0x4385E2",
        "0x4385E7",
        "0x438606",
    ):
        assert definition_address in ida_path_sync
    assert "_sync_build_subgame_active_bod_lvars" in ida_path_sync

    assert "_sync_segment_copy_entry_anchor_lvar" in ida_segment_sync
    assert "SEGMENT_COPY_ENTRY_ANCHOR_DEFEA = 0x447372" in ida_segment_sync
    assert '"SegmentCatalogEntryAnchor *selected_entry_anchor;"' in ida_segment_sync
    assert 'info.name = "selected_entry_anchor"' in ida_segment_sync
    assert "_sync_builtin_grid_offset_lvar" in ida_segment_sync
    assert '"int32_t grid_offset;"' in ida_segment_sync
    assert 'info.name = "grid_offset"' in ida_segment_sync
    assert "DIRTY_FUNCTIONS" in ida_segment_sync
    assert "ida_hexrays.mark_cfunc_dirty(address, True)" in ida_segment_sync

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
    assert (
        "int32_t __thiscall set_subgame_features(SubgameRuntime* runtime);"
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
    assert "int32_t requested_kind" in pool_sync
    assert "current_type_widths" in particle_lifetime_sync
    assert "current_struct_fields_batch" in particle_lifetime_sync
    assert "RING_PARTICLE_USER_VAR_UPDATES" in particle_lifetime_sync
    assert '"SubRingStar": 0x20' in particle_lifetime_sync
    assert '"SubRing": 0x1F8' in particle_lifetime_sync
    assert '"SubRingPool": 0x3F0' in particle_lifetime_sync
    assert '0x90: ("particles", "SubRingStar[10]")' in particle_lifetime_sync
    assert (
        '"initialize_ring_or_special_effect_particles",\n'
        '        "RegisterVariableSourceType",\n'
        '        34,\n'
        '        72,\n'
        '        "particle",\n'
        '        "SubRingStar*"'
        in particle_lifetime_sync
    )
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
    for header in analysis_headers:
        assert "int32_t requested_kind" in header
    assert "int requested_kind" in (
        repo_root / "tools/match/include/subgame_runtime.h"
    ).read_text(encoding="utf-8")
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
    assert '("SlugStateStrideCursor", SLUG_STATE_CURSOR_FIELD_UPDATES)' in pool_sync

    for header in (*analysis_headers, matcher_header):
        assert "Slug slots[SUB_SLUG_SLOT_CAPACITY]" in header
        assert "unknown_9c[0xac - 0x9c]" in header
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
    assert "SubSlugState state = slug->state;" in collision_scratch
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
        "typedef struct ParcelBucket",
        "ParcelCandidate candidates[PARCEL_CANDIDATE_CAPACITY];",
        "int32_t candidate_count;",
        "int32_t set_id;",
        "int32_t segment_index;",
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
        assert "FrontendWidget* delivered_count_widget;" in header
        assert "FrontendWidget* continue_widget;" in header

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
        assert "float fade_alpha;" in header
        assert "float spawn_velocity_y;" in header
        assert "uint8_t collision_armed;" in header

    assert '("0x00", "body", "RenderableBod")' in hazard_sync
    assert '("SubLazer", SUB_LAZER_FIELD_UPDATES)' in hazard_sync
    assert '("0x80", "state", "SubLazerState")' in hazard_sync
    assert '("Salt", SALT_FIELD_UPDATES)' in hazard_sync
    assert '("0x80", "state", "SaltState")' in hazard_sync
    assert (
        'HAZARD_STATE_TYPE_REPLACEMENTS = ("SubLazerState", "SaltState")'
        in hazard_sync
    )
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
            "int32_t __thiscall spawn_salt_hazard("
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
    assert "SALT_OWNER_EXPECTED_SIZE = 0x98" in ida_runtime_sync
    assert '(0x80, 4, "state", "SaltState")' in ida_runtime_sync
    assert 'salt_owner_readback = _salt_owner_readback()' in ida_runtime_sync
    assert "SUB_LAZER_OWNER_EXPECTED_SIZE = 0xB0" in ida_runtime_sync
    assert "SUB_LAZER_MANAGER_EXPECTED_SIZE = 0xDC0" in ida_runtime_sync
    assert '(0x80, 4, "state", "SubLazerState")' in ida_runtime_sync
    assert (
        "sub_lazer_owner_readback = _sub_lazer_owner_readback()"
        in ida_runtime_sync
    )
    assert '"SubLazer": _named_struct_size("SubLazer")' in ida_runtime_sync
    assert (
        '"SubLazerManager": _named_struct_size("SubLazerManager")'
        in ida_runtime_sync
    )
    assert '"SubLazerState",' in path_sync
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
    assert "SALT_STATE_ACTIVE" in salt_scratches["spawn_salt_hazard"]
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

    assert "SubgameRuntime* owner_game; // +0x48" in matcher
    for header in headers:
        banner = header.split("typedef struct Banner {", 1)[1].split(
            "} Banner;", 1
        )[0]
        assert "SubgameRuntime* owner_game;" in banner
        assert banner.index("owner_game") < banner.index("owner_player")
        assert "0x48 - 0x3c" in banner
        assert "0x54 - 0x4c" in banner
    for sync in syncs:
        assert '("0x48", "owner_game", "SubgameRuntime*")' in sync
        assert '("Banner", BANNER_FIELD_UPDATES)' in sync
    path_sync = syncs[2]
    assert '"update_banner"' in path_sync
    assert '"list_flags"' in path_sync
    assert '"uint32_t"' in path_sync


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
        assert "typedef struct FrameRenderCamera" in header
        assert "typedef struct GamePlayer" in header
        assert header.count("FrameRenderableBod body;") == 2
        assert "FrameTransformMatrix completion_handoff_transform;" in header
        assert "typedef struct BorderStackEntry" in header
        assert "BorderStackEntry entries[200];" in header
        assert "typedef struct BorderRecord" in header
        assert "FrameColor4f color_06c;" in header
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
        "initialize_cutscene": "wobble.lift_phase_step",
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
    assert "parsed_type_cache = {}" in code
    assert "expected_type, _ = parse_type_once(operation[\"variable_type\"])" in code
    assert '"user_defined": bool(function.is_var_user_defined(variable))' in code
    assert 'str(variable.source_type).split(".")[-1] == expected_source' in code
    assert 'entry["verified"] = observed == entry["expected"]' in code
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


def test_user_var_readback_skips_type_parsing(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        code = args[args.index("--code") + 1]
        assert "parse_type_string" not in code
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
    assert "function.split_var(split_variable)" in calls[0][-1]
    assert "function.merge_vars(" in calls[0][-1]
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


def test_track_cache_builder_lifetime_replay_stays_guarded() -> None:
    replay = (
        BINJA_DIR / "sync_track_cache_builder_lifetimes.py"
    ).read_text(encoding="utf-8")

    for owner_name, expected_size in (
        ("Vec3", "0x0C"),
        ("Fringe", "0x38"),
        ("TrackRowCell", "0x54"),
        ("ObjectFaceQuad", "0x30"),
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


def test_runtime_grid_clear_lifetime_replay_stays_guarded() -> None:
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
        ("SubRow", "0xF4"),
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
        ("SubRow", "0x90", "projection_payload", "Vec3"),
        ("SubRow", "0xA4", "primary_attachment_cell", "TrackRowCell*"),
        ("SubRow", "0xEC", "source_segment", "SubSegment*"),
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
            "Fringe**",
        ),
        (
            "RegisterVariableSourceType",
            573,
            73,
            "row_projection_y_cursor",
            "int32_t*",
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
            "uint32_t*",
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
            "Fringe**",
        ),
        (
            "RegisterVariableSourceType",
            698,
            72,
            "cell_fringe_front_cursor",
            "Fringe**",
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
    assert "apply_user_var_updates" in replay
    assert "remaining_cell_lanes" not in replay


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
        ("Invincible", "0xA4"),
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
        "allocate_border",
        "activate_all_borders",
        "hide_all_borders",
        "unhide_all_borders",
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
    assert "void update_input_ok();" in matcher_header
    assert "void initialize_input_ok();" in matcher_header

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
