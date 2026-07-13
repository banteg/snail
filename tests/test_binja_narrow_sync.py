import importlib.util
import json
from pathlib import Path


BINJA_DIR = Path(__file__).parents[1] / "tools/binja"
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


def test_data_var_updates_skip_current_types(monkeypatch) -> None:
    calls = []

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        return {
            "result": [
                {
                    "address": "0x4ac5c8",
                    "requested_type": "TipData",
                    "before_type": "struct TipData",
                    "after_type": "struct TipData",
                    "changed": False,
                }
            ]
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
    assert "if changed:" in calls[0][-1]


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

    assert "types_declare_missing_only" in source
    assert "current_struct_size" in source
    assert '"Sprite": 0xB4' in source
    assert "types_declare(" not in source


def test_path_sync_owns_core_subgame_receiver_abis() -> None:
    source = (BINJA_DIR / "sync_path_template_types.py").read_text(encoding="utf-8")

    assert "CORE_SUBGAME_PROTO_UPDATES" in source
    assert "DEFERRED_SUBGAME_OWNER_PROTO_UPDATES" in source
    assert "proto_owner_deferred" in source
    assert "apply_struct_and_proto_updates" in source
    assert "apply_direct_proto_update" not in source
    assert 'DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"' in source
    assert '"RingOrSpecialEffectPool"' not in source
    assert '"SubSpeedUp"' not in source
    assert '"SaltHazardSlot"' not in source
    stable_prototypes = source.split("CORE_SUBGAME_PROTO_UPDATES = (", 1)[1].split(
        "\n)\n\n# These five receivers", 1
    )[0]
    deferred_prototypes = source.split(
        "DEFERRED_SUBGAME_OWNER_PROTO_UPDATES = (", 1
    )[1].split("\n)\n\n\ndef report_deferred", 1)[0]
    for function_name in ("reset_subgame", "complete_subgame"):
        assert f'"{function_name}"' in stable_prototypes
    for function_name in (
        "initialize_subgame",
        "build_subgame_level",
        "destroy_subgame",
        "update_subgame",
        "remove_subgame_bods",
        "get_track_runtime_cell_at_world_z",
    ):
        assert f'"{function_name}"' in deferred_prototypes


def test_types_declare_if_missing_previews_then_selectively_applies(monkeypatch) -> None:
    calls = []

    monkeypatch.setattr(
        _narrow_sync,
        "current_type_widths",
        lambda *_args, **_kwargs: {"SubgameRuntime": None},
    )

    def fake_run_bn(_repo_root, *args):
        calls.append(args)
        if args[:3] == ("types", "declare", "--preview"):
            return {
                "success": True,
                "preview": True,
                "committed": False,
                "message": "Preview verified and reverted.",
                "affected_types": ["SubgameRuntime"],
                "affected_functions": [],
            }
        return {"result": {"applied": [{"name": "SubgameRuntime", "verified": True}]}}

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
    assert calls[0][:3] == ("types", "declare", "--preview")
    assert calls[1][:2] == ("py", "exec")
    assert "define_user_type" in calls[1][-1]


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
        if args[:3] == ("types", "declare", "--preview"):
            return {
                "success": True,
                "preview": True,
                "committed": False,
                "affected_types": [],
                "affected_functions": [],
            }
        return {"result": {"applied": []}}

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


def test_previewed_batch_uses_one_preview_and_apply(monkeypatch) -> None:
    manifests = []

    def fake_run_bn(_repo_root, *args):
        manifest_path = Path(args[3] if args[2] == "--preview" else args[2])
        manifests.append(json.loads(manifest_path.read_text()))
        preview = "--preview" in args
        return {
            "success": True,
            "preview": preview,
            "committed": not preview,
            "message": "Preview verified and reverted." if preview else "Mutation committed.",
            "affected_types": [],
            "affected_functions": [],
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

    assert len(manifests) == 2
    assert manifests[0] == manifests[1]
    assert manifests[0]["ops"] == operations
    assert result["apply"]["committed"] is True
