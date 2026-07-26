import runpy
from pathlib import Path

GHIDRA_WRAPPER = (
    Path(__file__).parents[1] / "tools/ghidra/decompile_symbol.py"
)
BATCH_WRAPPER = (
    Path(__file__).parents[1] / "tools/ghidra/export_itanium_symbols.py"
)


def _failure_log_tail(*streams: str) -> str:
    namespace = runpy.run_path(str(GHIDRA_WRAPPER))
    return namespace["failure_log_tail"](*streams)


def test_failure_log_tail_prefers_script_error_block() -> None:
    stdout = (
        "INFO routine startup\n"
        "ERROR REPORT SCRIPT ERROR: java.lang.IllegalStateException\n"
        "\tat DecompileSymbol.run(DecompileSymbol.java:34)\n"
        "INFO ANALYZING changes made by post scripts\n"
        "INFO routine shutdown"
    )

    assert _failure_log_tail(stdout, "WARNING unrelated") == (
        "ERROR REPORT SCRIPT ERROR: java.lang.IllegalStateException\n"
        "\tat DecompileSymbol.run(DecompileSymbol.java:34)"
    )


def test_failure_log_tail_bounds_generic_diagnostics() -> None:
    diagnostics = "\n".join(f"line {index}" for index in range(100))

    result = _failure_log_tail(diagnostics)

    assert len(result.splitlines()) == 80
    assert result.startswith("line 20\n")
    assert result.endswith("line 99")


def _batch_namespace() -> dict:
    return runpy.run_path(str(BATCH_WRAPPER))


def test_parse_nm_symbols_normalizes_macho_and_deduplicates() -> None:
    parse_nm_symbols = _batch_namespace()["parse_nm_symbols"]
    output = (
        "00046350 T _ZN6cRPath11BuildSlalomEiibPcS0_\n"
            "00057c54 t __ZN6cRPath11BuildSlalomEiibPcS0_\n"
            "00057c54 - 01 0000 FUN __ZN6cRPath11BuildSlalomEiibPcS0_\n"
            "00020124 - 01 0000 FUN __ZN9cRSubGame12PlaceParcelsEv\n"
            "004e29b0 s __ZN10OFSettings16s_UniqueInstanceE\n"
            "0008acd8 D _ZTV10cRSubGoldy\n"
            "garbage"
        )

    assert parse_nm_symbols(output) == [
        (
            "_ZN6cRPath11BuildSlalomEiibPcS0_",
            "_ZN6cRPath11BuildSlalomEiibPcS0_",
        ),
        (
            "_ZN9cRSubGame12PlaceParcelsEv",
            "__ZN9cRSubGame12PlaceParcelsEv",
        ),
    ]


def test_install_corpus_replaces_tree_atomically(tmp_path: Path) -> None:
    install_corpus = _batch_namespace()["install_corpus"]
    output = tmp_path / "android"
    output.mkdir()
    (output / "old.txt").write_text("old", encoding="utf-8")
    staged = tmp_path / "staged"
    staged.mkdir()
    (staged / "index.json").write_text("{}\n", encoding="utf-8")

    install_corpus(staged, output)

    assert not staged.exists()
    assert not (tmp_path / ".android.previous").exists()
    assert not (output / "old.txt").exists()
    assert (output / "index.json").read_text(encoding="utf-8") == "{}\n"


def test_failure_lines_include_only_failed_symbols() -> None:
    failure_lines = _batch_namespace()["failure_lines"]
    index = {
        "functions": [
            {"mangled": "_ZN2OkEv", "status": "ok"},
            {
                "mangled": "_ZN4HugeEv",
                "status": "error",
                "error": "process: timeout",
            },
        ]
    }

    assert failure_lines(index) == ["_ZN4HugeEv: process: timeout"]
