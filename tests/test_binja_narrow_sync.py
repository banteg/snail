import importlib.util
from pathlib import Path


MODULE_PATH = Path(__file__).parents[1] / "tools/binja/_narrow_sync.py"
MODULE_SPEC = importlib.util.spec_from_file_location("_narrow_sync", MODULE_PATH)
if MODULE_SPEC is None or MODULE_SPEC.loader is None:
    raise RuntimeError(f"unable to load {MODULE_PATH}")
_narrow_sync = importlib.util.module_from_spec(MODULE_SPEC)
MODULE_SPEC.loader.exec_module(_narrow_sync)


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
