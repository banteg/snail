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


def test_types_declare_if_missing_previews_then_selectively_applies(monkeypatch) -> None:
    calls = []

    monkeypatch.setattr(_narrow_sync, "struct_exists", lambda *_args, **_kwargs: False)

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
    assert calls[0][:3] == ("types", "declare", "--preview")
    assert calls[1][:2] == ("py", "exec")
    assert "define_user_type" in calls[1][-1]


def test_types_declare_if_missing_skips_complete_structs(monkeypatch) -> None:
    monkeypatch.setattr(_narrow_sync, "struct_exists", lambda *_args, **_kwargs: True)
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
