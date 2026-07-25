from pathlib import Path
import runpy


GHIDRA_WRAPPER = (
    Path(__file__).parents[1] / "tools/ghidra/decompile_symbol.py"
)


def _failure_log_tail(*streams: str) -> str:
    namespace = runpy.run_path(str(GHIDRA_WRAPPER))
    return namespace["failure_log_tail"](*streams)


def test_failure_log_tail_prefers_script_error_block() -> None:
    stdout = "\n".join(
        (
            "INFO routine startup",
            "ERROR REPORT SCRIPT ERROR: java.lang.IllegalStateException",
            "\tat DecompileSymbol.run(DecompileSymbol.java:34)",
            "INFO ANALYZING changes made by post scripts",
            "INFO routine shutdown",
        )
    )

    assert _failure_log_tail(stdout, "WARNING unrelated") == "\n".join(
        (
            "ERROR REPORT SCRIPT ERROR: java.lang.IllegalStateException",
            "\tat DecompileSymbol.run(DecompileSymbol.java:34)",
        )
    )


def test_failure_log_tail_bounds_generic_diagnostics() -> None:
    diagnostics = "\n".join(f"line {index}" for index in range(100))

    result = _failure_log_tail(diagnostics)

    assert len(result.splitlines()) == 80
    assert result.startswith("line 20\n")
    assert result.endswith("line 99")
