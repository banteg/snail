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
