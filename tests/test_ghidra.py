import runpy
import sys
from pathlib import Path

import pytest

GHIDRA_DIR = Path(__file__).parents[1] / "tools/ghidra"
if str(GHIDRA_DIR) not in sys.path:
    sys.path.insert(0, str(GHIDRA_DIR))
GHIDRA_WRAPPER = GHIDRA_DIR / "decompile_symbol.py"
BATCH_WRAPPER = GHIDRA_DIR / "export_itanium_symbols.py"
PROJECT_HELPER = GHIDRA_DIR / "project.py"


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


def _project_namespace() -> dict:
    return runpy.run_path(str(PROJECT_HELPER))


def test_parse_nm_symbols_normalizes_macho_and_deduplicates() -> None:
    parse_nm_symbols = _batch_namespace()["parse_nm_symbols"]
    output = (
        "00046350 T _ZN6cRPath11BuildSlalomEiibPcS0_\n"
        "00014118 T _Z10G0SetBlendi\n"
        "00014118 - 01 0000 FUN __Z10G0SetBlendi\n"
        "00057c54 t __ZN6cRPath11BuildSlalomEiibPcS0_\n"
        "00057c54 - 01 0000 FUN __ZN6cRPath11BuildSlalomEiibPcS0_\n"
        "00020124 - 01 0000 FUN __ZN9cRSubGame12PlaceParcelsEv\n"
        "004e29b0 s __ZN10OFSettings16s_UniqueInstanceE\n"
        "0008acd8 D _ZTV10cRSubGoldy\n"
        "garbage"
    )

    assert parse_nm_symbols(output) == [
        (
            "_Z10G0SetBlendi",
            "_Z10G0SetBlendi",
        ),
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


def _write_ghidra_build(
    ghidra_dir: Path,
    *,
    version: str = "12.1.2",
    revision: str = "revision-a",
) -> None:
    properties = ghidra_dir / "Ghidra/application.properties"
    properties.parent.mkdir(parents=True, exist_ok=True)
    properties.write_text(
        f"application.version={version}\napplication.revision.ghidra={revision}\n",
        encoding="utf-8",
    )


def test_persistent_project_records_and_validates_provenance(
    tmp_path: Path,
) -> None:
    namespace = _project_namespace()
    fresh_project = namespace["fresh_project"]
    persistent_project = namespace["persistent_project"]
    prepare_project = namespace["prepare_project"]
    record_initialized_project = namespace["record_initialized_project"]
    metadata_error = namespace["ProjectMetadataError"]
    ghidra_dir = tmp_path / "ghidra"
    project_root = tmp_path / "projects"
    binary = tmp_path / "libsnailmail.so"
    binary.write_bytes(b"first binary")
    _write_ghidra_build(ghidra_dir)

    project = persistent_project(binary, ghidra_dir, project_root)

    assert not project.exists
    assert project.command_suffix() == []
    assert project.command_prefix(Path("analyzeHeadless"), binary)[-2:] == [
        "-import",
        str(binary),
    ]
    fresh = fresh_project(binary, ghidra_dir, tmp_path / "fresh")
    assert fresh.command_suffix() == ["-deleteProject"]
    prepare_project(project)
    project.project_file.write_text("database", encoding="utf-8")
    record_initialized_project(project)

    reopened = persistent_project(binary, ghidra_dir, project_root)
    assert reopened.exists
    assert reopened.command_prefix(Path("analyzeHeadless"), binary)[-2:] == [
        "-process",
        binary.name,
    ]
    assert reopened.expected_metadata["binary"]["sha256"]  # type: ignore[index]

    binary.write_bytes(b"changed binary")
    with pytest.raises(metadata_error, match="provenance mismatch"):
        persistent_project(binary, ghidra_dir, project_root)


def test_persistent_project_rejects_ghidra_build_drift(
    tmp_path: Path,
) -> None:
    namespace = _project_namespace()
    persistent_project = namespace["persistent_project"]
    prepare_project = namespace["prepare_project"]
    record_initialized_project = namespace["record_initialized_project"]
    metadata_error = namespace["ProjectMetadataError"]
    ghidra_dir = tmp_path / "ghidra"
    project_root = tmp_path / "projects"
    binary = tmp_path / "iSM"
    binary.write_bytes(b"ios binary")
    _write_ghidra_build(ghidra_dir)
    project = persistent_project(binary, ghidra_dir, project_root)
    prepare_project(project)
    project.project_file.write_text("database", encoding="utf-8")
    record_initialized_project(project)

    _write_ghidra_build(
        ghidra_dir,
        version="12.2.0",
        revision="revision-b",
    )

    with pytest.raises(metadata_error, match="provenance mismatch"):
        persistent_project(binary, ghidra_dir, project_root)


def test_persistent_project_lock_fails_closed(tmp_path: Path) -> None:
    namespace = _project_namespace()
    persistent_project = namespace["persistent_project"]
    project_lock = namespace["project_lock"]
    lock_error = namespace["ProjectLockError"]
    ghidra_dir = tmp_path / "ghidra"
    binary = tmp_path / "snail.exe"
    binary.write_bytes(b"windows binary")
    _write_ghidra_build(ghidra_dir)
    project = persistent_project(binary, ghidra_dir, tmp_path / "projects")

    with (
        project_lock(project),
        pytest.raises(lock_error, match="already in use"),
        project_lock(project),
    ):
        pass
