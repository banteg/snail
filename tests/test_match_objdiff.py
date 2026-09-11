"""Exercise snapshot integrity and the CLI without a compiler or objdiff install."""

import json
from dataclasses import replace

import pytest

from snail import match as m
from snail import match_objdiff as exporter
from snail.cli import main
from snail.symbols import FunctionSymbol, FunctionSymbolManifest


@pytest.fixture
def snapshot_inputs(tmp_path, monkeypatch):
    directory = tmp_path / "match" / "scratches" / "example"
    directory.mkdir(parents=True)
    (directory / "scratch.conf").write_text(
        "FUNCTION=example COMPILER=vc6 CFLAGS=/O2 END=0x401006 SYMBOL=_example\n"
    )
    target = bytes.fromhex("b8 01000000 c3")
    image_path = tmp_path / "target.exe"
    image_path.write_bytes(target)
    manifest = FunctionSymbolManifest(
        name="test",
        primary_target=str(image_path),
        reference_target=str(image_path),
        image_base=0x401000,
        unwrapped_sha256=exporter.sha(target),
        source_database=None,
        functions=(FunctionSymbol(address=0x401000, name="example"),),
    )
    monkeypatch.setattr(m, "load_function_symbol_manifest", lambda _: manifest)
    monkeypatch.setattr(m, "load_default_reference_symbol_manifest", lambda: None)
    monkeypatch.setattr(m, "scratch_experiment_epoch", lambda *a, **k: "stable")
    image = m.LoadedImage(mapped=target, image_base=0x401000, size_of_image=len(target))
    monkeypatch.setattr(m, "load_image", lambda *a: image)
    compiled = tmp_path / "compiled.obj"
    # One real immediate mismatch, preserved by the display exporter.
    compiled.write_bytes(exporter.coff(bytes.fromhex("b8 02000000 c3"), [], "_example"))
    calls = []

    def compile_once(*args):
        calls.append(args)
        return compiled

    monkeypatch.setattr(m, "compile_scratch", compile_once)
    return directory, image_path, compiled, calls


def test_cli_exports_complete_snapshot_with_native_mismatch(
    snapshot_inputs, tmp_path, capsys
):
    directory, _, compiled, calls = snapshot_inputs
    output = tmp_path / "snapshot"
    assert (
        main(
            [
                "match",
                "objdiff",
                "example",
                "--match-root",
                str(directory.parents[1]),
                "--out",
                str(output),
                "--json",
            ]
        )
        == 0
    )
    payload = json.loads(capsys.readouterr().out)
    assert payload["unit"] == "example"
    assert len(calls) == 1
    assert (output / "compiled.obj").read_bytes() == compiled.read_bytes()
    project = json.loads((output / "objdiff.json").read_text())
    assert project == {
        "build_base": False,
        "build_target": False,
        "units": [
            {
                "name": "example",
                "target_path": "target.obj",
                "base_path": "candidate.obj",
            }
        ],
    }
    native = json.loads((output / "native-diagnostics.json").read_text())
    assert native["match_ratio"] < 1
    receipt = json.loads((output / "receipt.json").read_text())
    for name, expected in receipt["files"].items():
        assert exporter.sha((output / name).read_bytes()) == expected
    for side in ("target", "candidate"):
        obj = m.parse_coff_object((output / f"{side}.obj").read_bytes())
        assert obj.symbols[0].name == exporter.DISPLAY_SYMBOL
        assert obj.sections[0].data == (output / f"{side}.bin").read_bytes()


def test_existing_snapshot_is_preserved_before_compiling(snapshot_inputs, tmp_path):
    directory, _, _, calls = snapshot_inputs
    output = tmp_path / "snapshot"
    output.mkdir()
    (output / "keep").write_text("existing")
    with pytest.raises(FileExistsError, match="choose a new"):
        exporter.export_snapshot(directory, output)
    assert (output / "keep").read_text() == "existing"
    assert not calls


def test_cli_rejects_wrong_image_before_compiling(snapshot_inputs, tmp_path, capsys):
    directory, image_path, _, calls = snapshot_inputs
    image_path.write_bytes(b"wrong image")
    output = tmp_path / "snapshot"
    assert main(["match", "objdiff", str(directory), "--out", str(output)]) == 2
    assert "SHA-256" in capsys.readouterr().err
    assert not output.exists()
    assert not calls


def test_changed_inputs_abort_without_snapshot(snapshot_inputs, tmp_path, monkeypatch):
    directory, _, _, _ = snapshot_inputs
    epochs = iter(["before", "after"])
    monkeypatch.setattr(m, "scratch_experiment_epoch", lambda *a, **k: next(epochs))
    output = tmp_path / "snapshot"
    with pytest.raises(ValueError, match="inputs changed"):
        exporter.export_snapshot(directory, output)
    assert not output.exists()


def test_failed_write_removes_partial_snapshot(snapshot_inputs, tmp_path, monkeypatch):
    directory, _, _, _ = snapshot_inputs

    def fail(*a):
        raise OSError("write failed")

    monkeypatch.setattr(exporter, "write_json", fail)
    output = tmp_path / "snapshot"
    with pytest.raises(OSError, match="write failed"):
        exporter.export_snapshot(directory, output)
    assert not output.exists()


@pytest.mark.parametrize("mutation", ["negative", "past_end", "short_field"])
def test_invalid_reference_bounds_fail_closed(mutation):
    data = bytes.fromhex("e8 00000000 c3")
    ref = m.MaskedReference(0, "imm", "object", 0, "callee", "ref:callee", True)
    line = m.DisassemblyLine(0, 0, "call ADDR", 5, (ref,))
    if mutation == "negative":
        line = replace(line, offset=-1)
    elif mutation == "past_end":
        line = replace(line, size=7)
    else:
        data = bytes.fromhex("eb00")
        line = replace(line, size=2)
    with pytest.raises(ValueError):
        exporter.lift(data, (line,), 0)
