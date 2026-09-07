from __future__ import annotations

import hashlib
import io
import json
from dataclasses import replace
from pathlib import Path
from types import SimpleNamespace

import pytest

from snail import match as matchlib
from snail import match_export
from snail.cli import main
from snail.match import (
    ProbeResult,
    ScratchConfig,
    ScratchStatus,
    evaluate_source_probe,
    scratch_dependency_sha256,
    scratch_experiment_epoch,
)


def _config(directory: Path) -> ScratchConfig:
    return ScratchConfig(
        directory=directory,
        function="foo",
        compiler="msvc6.5",
        cflags="/O2",
        end_va=None,
        symbol=None,
    )


def _status(
    config: ScratchConfig,
    ratio: float,
    *,
    prefix: int,
    candidate_instructions: int = 10,
) -> ScratchStatus:
    return ScratchStatus(
        config=config,
        address=0x401000,
        target_size=100,
        ratio=ratio,
        prefix_instructions=prefix,
        target_instructions=10,
        candidate_instructions=candidate_instructions,
        masked_ok=4,
        first_target_mismatch_offset=0x10,
        first_candidate_mismatch_offset=0x10,
    )


def _baseline_match() -> matchlib.MatchResult:
    target = (matchlib.DisassemblyLine(0, 0x401000, "ret", 1),)
    baseline = (
        matchlib.DisassemblyLine(0, 0, "dec eax", 1),
        matchlib.DisassemblyLine(1, 1, "ret", 1),
    )
    return matchlib.MatchResult(
        2 / 3, 0, tuple(line.text for line in target),
        tuple(line.text for line in baseline), target, baseline,
    )


def test_source_probe_compares_one_baseline_and_overlay(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
) -> None:
    config = _config(tmp_path)
    (tmp_path / "scratch.cpp").write_text(
        "baseline source\n",
        encoding="utf-8",
    )
    calls: list[tuple[str, ScratchConfig]] = []
    baseline_match = _baseline_match()

    def fake_overlay(
        profile: ScratchConfig,
        source_text: str,
        **_kwargs,
    ) -> ScratchStatus:
        if source_text == "baseline source\n":
            calls.append(("baseline", profile))
            _kwargs["on_match"](baseline_match)
            return _status(
                replace(profile, directory=Path("/tmp/baseline-shadow")),
                0.5,
                prefix=2,
            )
        assert source_text == "alternate source\n"
        calls.append(("probe", profile))
        return _status(
            replace(profile, directory=Path("/tmp/probe-shadow")),
            0.75,
            prefix=4,
        )

    monkeypatch.setattr(
        "snail.match.evaluate_source_overlay",
        fake_overlay,
    )

    result = evaluate_source_probe(
        config,
        "alternate source\n",
        compiler="msvc6.5pp",
        cflags="/O2 /G5",
        label="same-tu",
    )

    assert [name for name, _profile in calls] == ["baseline", "probe"]
    assert all(profile.compiler == "msvc6.5pp" for _name, profile in calls)
    assert all(profile.cflags == "/O2 /G5" for _name, profile in calls)
    assert result.fuzzy_delta_bytes == 25
    assert result.ratio_delta == 0.25
    assert result.label == "same-tu"
    assert result.source_sha256 == hashlib.sha256(b"alternate source\n").hexdigest()
    assert result.baseline_source_text == "baseline source\n"
    assert result.baseline_match is baseline_match


def test_probe_cli_records_the_complete_result(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
    capsys: pytest.CaptureFixture[str],
) -> None:
    scratch = tmp_path / "scratch"
    scratch.mkdir()
    tracked_source = scratch / "scratch.cpp"
    tracked_source.write_text("baseline source\n", encoding="utf-8")
    (scratch / "scratch.conf").write_text(
        "FUNCTION=foo\n",
        encoding="utf-8",
    )
    probe_source = tmp_path / "probe.cpp"
    probe_source.write_text("probe source\n", encoding="utf-8")
    config = _config(scratch)
    result = ProbeResult(
        baseline=_status(config, 0.5, prefix=2),
        probe=_status(
            replace(config, directory=Path("/tmp/shadow")),
            0.75,
            prefix=4,
        ),
        source_sha256="probe-sha",
        label="same-tu",
    )
    monkeypatch.setattr(
        "snail.cli.evaluate_source_probe",
        lambda *args, **kwargs: result,
    )
    monkeypatch.setattr(
        "snail.cli.scratch_dependency_sha256",
        lambda *args, **kwargs: "d" * 64,
    )
    monkeypatch.setattr(
        "snail.cli.scratch_experiment_epoch",
        lambda *args, **kwargs: "e" * 64,
    )

    exit_code = main(
        [
            "match",
            "probe",
            str(scratch),
            "--source",
            str(probe_source),
            "--label",
            "same-tu",
            "--record",
            "--json",
        ]
    )

    assert exit_code == 0
    payload = json.loads(capsys.readouterr().out)
    assert payload["label"] == "same-tu"
    assert payload["delta"]["fuzzy_weighted_bytes"] == 25
    assert payload["recorded_to"] == str(scratch / "experiments.jsonl")
    record = json.loads((scratch / "experiments.jsonl").read_text(encoding="utf-8"))
    assert record["schema"] == 1
    assert record["kind"] == "probe"
    assert record["source_sha256"] == "probe-sha"
    assert record["dependency_sha256"] == "d" * 64
    assert record["baseline_epoch"] == "e" * 64
    assert "diagnostic_export" not in payload
    assert "diagnostic_export" not in record
    assert tracked_source.read_text(encoding="utf-8") == "baseline source\n"


@pytest.mark.parametrize("json_output", [False, True])
def test_probe_without_export_preserves_output_and_skips_receipts(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
    capsys: pytest.CaptureFixture[str],
    json_output: bool,
) -> None:
    (tmp_path / "scratch.conf").write_text("FUNCTION=foo\n")
    config = _config(tmp_path)
    result = ProbeResult(
        baseline=_status(config, 0.5, prefix=2),
        probe=_status(config, 0.75, prefix=4),
        source_sha256="source-hash",
    )
    monkeypatch.setattr("snail.cli.evaluate_source_probe", lambda *a, **kw: result)
    monkeypatch.setattr("sys.stdin", io.StringIO("source\n"))

    def unexpected(*_args, **_kwargs):
        pytest.fail("unrequested export or receipt work")

    monkeypatch.setattr("snail.cli.scratch_dependency_sha256", unexpected)
    monkeypatch.setattr("snail.cli.scratch_experiment_epoch", unexpected)
    monkeypatch.setattr(match_export, "export_probe", unexpected)
    args = ["match", "probe", str(tmp_path), "--stdin"]
    assert main(args + (["--json"] if json_output else [])) == 0
    output = capsys.readouterr().out
    if json_output:
        assert json.loads(output) == matchlib.probe_result_payload(result)
    else:
        assert output == matchlib.render_probe_result(result) + "\n"
    assert not (tmp_path / "experiments.jsonl").exists()


@pytest.fixture
def export_compiler(monkeypatch: pytest.MonkeyPatch):
    function = matchlib.ObjectFunction("foo", b"\x90\xc3", frozenset())
    digest = matchlib.object_function_fingerprint(function)
    builds: list[ScratchConfig] = []
    target = (matchlib.DisassemblyLine(0, 0x401000, "ret", 1),)
    candidate = (
        matchlib.DisassemblyLine(0, 0, "nop", 1),
        matchlib.DisassemblyLine(1, 1, "ret", 1),
    )
    diagnostic = matchlib.MatchResult(
        2 / 3, 0, tuple(line.text for line in target),
        tuple(line.text for line in candidate), target, candidate,
    )

    def compile_source(config: ScratchConfig, _match_root: Path) -> Path:
        builds.append(config)
        obj = config.directory / "scratch.obj"
        source = (config.directory / "scratch.cpp").read_text()
        obj.write_bytes(b"\x48\xc3" if source == "baseline source\n" else function.data)
        return obj

    monkeypatch.setattr(matchlib, "compile_scratch", compile_source)
    monkeypatch.setattr(matchlib, "parse_coff_object", lambda data: data)
    monkeypatch.setattr(
        matchlib, "extract_object_function",
        lambda data, *a, **kw: matchlib.ObjectFunction("foo", data, frozenset()),
    )
    monkeypatch.setattr(
        matchlib, "run_match", lambda obj_path, **_kwargs: (
            _baseline_match() if obj_path.read_bytes() == b"\x48\xc3" else diagnostic
        ),
    )
    return digest, builds, diagnostic


def test_probe_exports_baseline_from_original_evaluation_without_recompiling_it(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, export_compiler,
) -> None:
    digest, builds, _diagnostic = export_compiler
    scratch = tmp_path / "scratch"
    scratch.mkdir()
    (scratch / "scratch.conf").write_text("FUNCTION=foo\n")
    source = scratch / "scratch.cpp"
    source.write_text("baseline source\n")
    manifest = SimpleNamespace(image_base=0x400000)
    monkeypatch.setattr(matchlib, "resolve_function_extent", lambda *a: (0x401000, 0x401001))
    monkeypatch.setattr(
        matchlib, "load_image",
        lambda *a: SimpleNamespace(function_bytes=lambda *a: b"\xc3"),
    )
    match_calls = []
    run_match = matchlib.run_match

    def capture_match(**kwargs):
        match_calls.append(kwargs["obj_path"].read_bytes())
        return run_match(**kwargs)

    monkeypatch.setattr(matchlib, "run_match", capture_match)
    result = evaluate_source_probe(
        _config(scratch), "alternate source\n", match_root=tmp_path,
        image_path=tmp_path / "image", manifest=manifest,
    )
    assert result.baseline_match == _baseline_match()
    assert len(builds) == 2
    assert all(not config.directory.exists() for config in builds)
    assert result.probe.code_sha256 == digest
    assert result.baseline.code_sha256 != digest

    # Export must use the captured baseline even if the canonical source changed.
    source.write_text("changed after evaluation\n")
    destination = tmp_path / "export"
    match_export.export_probe(
        result, destination, source_text="alternate source\n", match_root=tmp_path,
        image_path=tmp_path / "image", manifest=manifest,
        baseline_epoch="epoch", dependency_sha256="dependencies",
    )
    assert len(builds) == 3  # baseline, candidate, verified export rebuild
    assert match_calls == [b"\x48\xc3", b"\x90\xc3", b"\x90\xc3"]
    assert (destination / "baseline.asm").read_text() == "0000  dec eax\n0001  ret\n"
    assert (destination / "baseline.diff").read_text() == (
        "--- baseline\n+++ candidate\n@@ -1,2 +1,2 @@\n-dec eax\n+nop\n ret\n"
    )
    assert "-baseline source\n" in (destination / "source.diff").read_text()
    assert source.read_text() == "changed after evaluation\n"


@pytest.mark.parametrize("compiler,cflags", [("msvc6.5", "/O2"), ("msvc6.6", "/O1")])
@pytest.mark.parametrize("export", [False, True])
def test_record_probe_after_temporary_builds_are_removed(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
    capsys: pytest.CaptureFixture[str],
    compiler: str,
    cflags: str,
    export: bool,
    export_compiler,
) -> None:
    digest, export_builds, diagnostic = export_compiler
    match_root = tmp_path / "match"
    scratch = match_root / "scratches" / "foo"
    scratch.mkdir(parents=True)
    (scratch / "scratch.conf").write_text("FUNCTION=foo\n")
    (scratch / "scratch.cpp").write_text("baseline source\n")
    build = scratch / "build"
    build.mkdir()
    canonical_object = build / "scratch.obj"
    canonical_object.write_bytes(b"preserve canonical build")
    (match_root / "cl.sh").write_text("compiler wrapper\n")
    compiler_exe = match_root / "compilers" / compiler / "Bin" / "CL.EXE"
    compiler_exe.parent.mkdir(parents=True)
    compiler_exe.write_bytes(b"compiler fixture")
    image_path = tmp_path / "target.exe"
    image_path.write_bytes(b"image fixture")
    overlay = tmp_path / "overlay.cpp"
    overlay.write_text("alternate source\n")
    temporary_directories: list[Path] = []

    def fake_compile_and_score(config: ScratchConfig, *_args, **_kwargs) -> ScratchStatus:
        assert config.directory != scratch
        temporary_directories.append(config.directory)
        source = (config.directory / "scratch.cpp").read_text()
        if callback := _kwargs.get("on_match"):
            assert source == "baseline source\n"
            callback(_baseline_match())
        return replace(
            _status(config, 0.5 if source == "baseline source\n" else 0.75, prefix=2),
            code_sha256=digest,
        )

    # Exercise real overlay lifetime, result identity, hashing, and CLI recording.
    # Only native compilation/scoring is replaced; no toolchain is needed in CI.
    monkeypatch.setattr("snail.match.evaluate_scratch", fake_compile_and_score)
    config = replace(_config(scratch), compiler=compiler, cflags=cflags)
    expected_dependencies = scratch_dependency_sha256(config, match_root)
    expected_epoch = scratch_experiment_epoch(config, match_root, image_path=image_path)
    destination = tmp_path / "export"

    assert main([
        "match", "probe", str(scratch), "--source", str(overlay),
        "--match-root", str(match_root), "--image", str(image_path),
        "--compiler", compiler, "--cflags", cflags, "--record", "--json",
    ] + (["--export-dir", str(destination)] if export else [])) == 0

    payload = json.loads(capsys.readouterr().out)
    record = json.loads((scratch / "experiments.jsonl").read_text())
    assert len(temporary_directories) == 2
    assert all(not path.exists() for path in temporary_directories)
    assert record["baseline"]["scratch"] == str(scratch)
    assert record["baseline"]["compiler"] == compiler
    assert record["baseline"]["cflags"] == cflags
    assert record["dependency_sha256"] == expected_dependencies
    assert record["baseline_epoch"] == expected_epoch
    assert payload["probe"]["scratch"] == "<shadow>"
    assert (scratch / "scratch.cpp").read_text() == "baseline source\n"
    assert canonical_object.read_bytes() == b"preserve canonical build"
    if export:
        assert len(export_builds) == 1
        assert export_builds[0].compiler == compiler
        assert export_builds[0].cflags == cflags
        assert not export_builds[0].directory.exists()
        assert {path.name for path in destination.iterdir()} == {
            "candidate.cpp", "source.diff", "assembly.diff", "target.asm",
            "candidate.asm", "report.json", "baseline.asm", "baseline.diff",
        }
        assert (destination / "candidate.cpp").read_text() == "alternate source\n"
        assert (destination / "source.diff").read_text() == (
            "--- baseline.cpp\n+++ candidate.cpp\n@@ -1 +1 @@\n"
            "-baseline source\n+alternate source\n"
        )
        assert (destination / "assembly.diff").read_text() == (
            "\n".join(diagnostic.diff_lines) + "\n"
        )
        assert (destination / "target.asm").read_text() == "0000  ret\n"
        assert (destination / "candidate.asm").read_text() == "0000  nop\n0001  ret\n"
        assert (destination / "baseline.asm").read_text() == "0000  dec eax\n0001  ret\n"
        assert (destination / "baseline.diff").read_text() == (
            "--- baseline\n+++ candidate\n@@ -1,2 +1,2 @@\n-dec eax\n+nop\n ret\n"
        )
        report = json.loads((destination / "report.json").read_text())
        assert report["kind"] == "probe-diagnostic"
        assert report["dependency_sha256"] == expected_dependencies
        assert report["baseline_epoch"] == expected_epoch
        assert report["baseline_source_sha256"] == hashlib.sha256(
            b"baseline source\n"
        ).hexdigest()
        assert report["evaluation"] == {
            key: value for key, value in payload.items()
            if key not in {"diagnostic_export", "recorded_to"}
        }
        assert report["diagnostic"] == matchlib.match_result_payload(diagnostic)
        assert report["reference_audit"] == {"entries": []}
        assert report["code_sha256"] == digest
        assert report["scratch_config"]["compiler"] == compiler
        assert report["scratch_config"]["cflags"] == cflags
        assert payload["diagnostic_export"] == str(destination)
        assert record["diagnostic_export"] == str(destination)
    else:
        assert export_builds == []
        assert not destination.exists()


@pytest.mark.parametrize(
    "failure", ["destination", "source", "code", "baseline", "baseline-assembly"]
)
def test_probe_export_refuses_incomplete_or_changed_evidence(
    tmp_path: Path,
    export_compiler,
    failure: str,
) -> None:
    digest, _builds, _diagnostic = export_compiler
    config = _config(tmp_path)
    source = "alternate source\n"
    result = ProbeResult(
        baseline=_status(config, 1.0, prefix=10),
        probe=replace(_status(config, 0.5, prefix=2), code_sha256=digest),
        source_sha256=hashlib.sha256(source.encode()).hexdigest(),
        baseline_source_text="baseline source\n",
        baseline_match=_baseline_match(),
    )
    destination = tmp_path / "export"
    messages = {
        "destination": "already exists",
        "source": "evaluated source identity",
        "code": "evaluated code identity",
        "baseline": "missing the evaluated baseline source",
        "baseline-assembly": "missing the evaluated baseline assembly",
    }
    if failure == "destination":
        destination.mkdir()
        (destination / "keep").write_text("preserve existing bundle")
    elif failure == "source":
        source += "// altered after evaluation\n"
    elif failure == "code":
        result = replace(result, probe=replace(result.probe, code_sha256="changed"))
    elif failure == "baseline":
        result = replace(result, baseline_source_text=None)
    else:
        result = replace(result, baseline_match=None)
    with pytest.raises(ValueError, match=messages[failure]):
        match_export.export_probe(
            result, destination, source_text=source, match_root=tmp_path,
            image_path=tmp_path / "image", manifest=None,
            baseline_epoch="epoch", dependency_sha256="dependencies",
        )
    if failure == "destination":
        assert {path.name for path in destination.iterdir()} == {"keep"}
        assert (destination / "keep").read_text() == "preserve existing bundle"
    else:
        assert not destination.exists()
    assert list(tmp_path.glob(".snail-export-*")) == []


@pytest.mark.parametrize("baseline_failed", [False, True])
def test_probe_cli_exports_compile_error_from_stdin_without_recording(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
    capsys: pytest.CaptureFixture[str],
    baseline_failed: bool,
) -> None:
    (tmp_path / "scratch.conf").write_text("FUNCTION=foo\n")
    config = _config(tmp_path)
    source = "invalid source\n"
    result = ProbeResult(
        baseline=_status(config, 1.0, prefix=10),
        probe=replace(
            _status(config, 0.0, prefix=0), ratio=None, error="compiler failed"
        ),
        source_sha256=hashlib.sha256(source.encode()).hexdigest(),
        baseline_source_text="baseline source\n",
        baseline_match=_baseline_match(),
    )
    if baseline_failed:
        result = replace(
            result,
            baseline=replace(result.baseline, ratio=None, error="baseline failed"),
            baseline_match=None,
        )
    monkeypatch.setattr("snail.cli.evaluate_source_probe", lambda *a, **kw: result)
    monkeypatch.setattr("snail.cli.scratch_dependency_sha256", lambda *a, **kw: "deps")
    monkeypatch.setattr("snail.cli.scratch_experiment_epoch", lambda *a, **kw: "epoch")
    monkeypatch.setattr("sys.stdin", io.StringIO(source))

    def unexpected(*_args, **_kwargs):
        pytest.fail("failed candidate must not be recompiled for export")

    monkeypatch.setattr(matchlib, "compile_scratch", unexpected)
    destination = tmp_path / "export"
    assert main([
        "match", "probe", str(tmp_path), "--stdin", "--export-dir", str(destination),
    ]) == 2
    assert f"diagnostic_export={destination}\n" in capsys.readouterr().out
    expected_files = {"candidate.cpp", "source.diff", "report.json"}
    if not baseline_failed:
        expected_files.add("baseline.asm")
        assert (destination / "baseline.asm").read_text() == "0000  dec eax\n0001  ret\n"
    assert {path.name for path in destination.iterdir()} == expected_files
    assert (destination / "candidate.cpp").read_text() == source
    report = json.loads((destination / "report.json").read_text())
    assert report["error"] == "compiler failed"
    assert report["diagnostic"] is None
    assert not (tmp_path / "experiments.jsonl").exists()


def test_probe_export_keeps_candidate_assembly_when_baseline_failed(
    tmp_path: Path, export_compiler,
) -> None:
    digest, builds, _diagnostic = export_compiler
    config = _config(tmp_path)
    source = "alternate source\n"
    result = ProbeResult(
        baseline=replace(_status(config, 0, prefix=0), ratio=None, error="baseline failed"),
        probe=replace(_status(config, 0.5, prefix=0), code_sha256=digest),
        source_sha256=hashlib.sha256(source.encode()).hexdigest(),
        baseline_source_text="baseline source\n",
    )
    destination = tmp_path / "export"
    report = match_export.export_probe(
        result, destination, source_text=source, match_root=tmp_path,
        image_path=tmp_path / "image", manifest=None,
        baseline_epoch="epoch", dependency_sha256="dependencies",
    )
    assert len(builds) == 1
    assert {path.name for path in destination.iterdir()} == {
        "candidate.cpp", "source.diff", "assembly.diff", "target.asm",
        "candidate.asm", "report.json",
    }
    assert report["evaluation"]["baseline"]["error"] == "baseline failed"
    assert report["diagnostic"] is not None
