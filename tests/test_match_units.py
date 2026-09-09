"""Shared native source context must survive caching, probes, and diagnostics."""

import json
import subprocess
from dataclasses import replace
from pathlib import Path

import pytest

from snail import match


@pytest.fixture
def grouped_scratches(tmp_path):
    root = tmp_path / "match"
    for name in ("first", "second"):
        directory = root / "scratches" / name
        directory.mkdir(parents=True)
        (directory / "scratch.conf").write_text(f"FUNCTION={name}\n")
        (directory / "scratch.cpp").write_text(f"int {name}() {{ return 1; }}\n")
    manifest = root / "translation_units.json"
    manifest.write_text(json.dumps({
        "schema": 1,
        "units": [{"name": "pair", "source_object": "Pair.o", "members": ["first", "second"]}],
    }))
    compiler = root / "compilers" / "msvc6.5" / "Bin"
    compiler.mkdir(parents=True)
    (compiler / "CL.EXE").write_bytes(b"fixture")
    (root / "cl.sh").write_text("fixture")
    return root, tuple(match.load_scratch_config(root / "scratches" / n) for n in ("first", "second"))


def test_unit_source_order_and_member_overlay(grouped_scratches):
    root, (first, second) = grouped_scratches
    expected = "int first() { return 1; }\n\nint second() { return 1; }\n"
    assert match.scratch_compilation_source(first, root) == expected
    assert match.scratch_compilation_source(second, root) == expected
    assert match.scratch_compilation_source(second, root, source_text="int second() { return 9; }\n") == (
        expected.replace("int second() { return 1; }", "int second() { return 9; }")
    )
    assert (second.directory / "scratch.cpp").read_text() == "int second() { return 1; }\n"


def test_unit_probe_uses_candidate_and_preserves_peer(grouped_scratches, monkeypatch):
    root, (_, second) = grouped_scratches

    def inspect_shadow(config, _root, **kwargs):
        assert match.scratch_translation_unit(config, root) is None
        return (config.directory / "scratch.cpp").read_text()

    monkeypatch.setattr(match, "evaluate_scratch", inspect_shadow)
    assert match.evaluate_source_overlay(second, "int second() { return 9; }\n", match_root=root) == (
        "int first() { return 1; }\n\nint second() { return 9; }\n"
    )


def test_one_physical_object_and_peer_cache_invalidation(grouped_scratches, monkeypatch):
    root, (first, second) = grouped_scratches
    compiled = []

    def compile_fixture(argv, *, cwd, **kwargs):
        compiled.append((Path(cwd) / "scratch.cpp").read_text())
        (Path(cwd) / "scratch.obj").write_bytes(b"fixture object")
        return subprocess.CompletedProcess(argv, 0, "", "")

    monkeypatch.setattr(subprocess, "run", compile_fixture)
    one = match.compile_scratch(first, root)
    two = match.compile_scratch(second, root)
    assert one == two
    assert len(compiled) == 1
    assert "int first()" in compiled[0] and "int second()" in compiled[0]
    before = match.scratch_dependency_sha256(second, root)
    (first.directory / "scratch.cpp").write_text("int first() { return 2; }\n")
    assert match.scratch_dependency_sha256(second, root) != before
    assert match.compile_scratch(second, root) == one
    assert len(compiled) == 2
    assert "return 2" in compiled[1]


def test_runner_override_and_binary_update_recompile_shared_object(grouped_scratches, monkeypatch):
    import os

    root, (first, second) = grouped_scratches
    runners = [root / "bin" / name for name in ("wibo", "patched-wibo")]
    runners[0].parent.mkdir()
    for runner in runners:
        runner.write_bytes(b"runner")
        runner.chmod(0o755)
    monkeypatch.delenv("WIBO", raising=False)
    compiled = []

    def compile_fixture(argv, *, cwd, **kwargs):
        compiled.append(kwargs["env"].get("WIBO"))
        (Path(cwd) / "scratch.obj").write_bytes(b"fixture object")
        return subprocess.CompletedProcess(argv, 0, "", "")

    monkeypatch.setattr(subprocess, "run", compile_fixture)
    obj = match.compile_scratch(first, root)
    original_digest = match.scratch_dependency_sha256(second, root)
    assert match.compile_scratch(second, root) == obj
    assert len(compiled) == 1

    # Both runners predate the object. Selection itself must invalidate it.
    monkeypatch.setenv("WIBO", str(runners[1]))
    assert match.scratch_dependency_sha256(second, root) != original_digest
    assert match.compile_scratch(second, root) == obj
    assert compiled == [None, str(runners[1])]
    patched_digest = match.scratch_dependency_sha256(second, root)
    previous = runners[1].stat()
    runners[1].write_bytes(b"updated runner")
    os.utime(runners[1], ns=(previous.st_atime_ns, previous.st_mtime_ns + 1))
    assert match.scratch_dependency_sha256(second, root) != patched_digest
    assert match.compile_scratch(first, root) == obj
    assert len(compiled) == 3


def test_runner_resolution_follows_launcher_precedence(tmp_path, monkeypatch):
    root = tmp_path / "match"
    bundled = root / "bin" / "wibo"
    path_runner = tmp_path / "path-bin" / "wibo"
    named_runner = path_runner.with_name("patched-wibo")
    for runner in (bundled, path_runner, named_runner):
        runner.parent.mkdir(parents=True, exist_ok=True)
        runner.write_bytes(b"runner")
        runner.chmod(0o755)
    monkeypatch.setenv("PATH", str(path_runner.parent))
    monkeypatch.delenv("WIBO", raising=False)
    assert match._scratch_wibo_path(root) == bundled
    bundled.chmod(0o644)
    assert match._scratch_wibo_path(root) == path_runner
    monkeypatch.setenv("WIBO", "patched-wibo")
    assert match._scratch_wibo_path(root) == named_runner
    monkeypatch.setenv("WIBO", str(bundled))
    assert match._scratch_wibo_path(root) == bundled
    monkeypatch.setenv("WIBO", "missing-runner")
    assert match._scratch_wibo_path(root) is None


def test_unit_order_is_a_cache_and_compilation_input(grouped_scratches):
    root, (first, _) = grouped_scratches
    before = match.scratch_dependency_sha256(first, root)
    path = root / "translation_units.json"
    payload = json.loads(path.read_text())
    payload["units"][0]["members"].reverse()
    path.write_text(json.dumps(payload))
    assert match.scratch_dependency_sha256(first, root) != before
    assert match.scratch_compilation_source(first, root).startswith("int second()")


def test_peer_headers_are_build_dependencies(grouped_scratches):
    root, (first, second) = grouped_scratches
    include = root / "include"
    include.mkdir()
    (include / "peer.h").write_text("#define PEER 1\n")
    (first.directory / "scratch.cpp").write_text('#include "peer.h"\nint first() { return PEER; }\n')
    dependencies = match._scratch_build_dependencies(second, root)
    assert include / "peer.h" in dependencies
    assert first.directory / "scratch.cpp" in dependencies
    assert first.directory / "scratch.conf" in dependencies
    assert root / "translation_units.json" in dependencies


def test_forbidden_source_in_peer_is_rejected(grouped_scratches):
    root, (first, second) = grouped_scratches
    (first.directory / "scratch.cpp").write_text("int first() { __asm nop }\n")
    with pytest.raises(ValueError, match="no fakematching"):
        match.compile_scratch(second, root)


def test_mixed_profiles_are_rejected(grouped_scratches):
    root, (first, second) = grouped_scratches
    (first.directory / "scratch.conf").write_text("FUNCTION=first\nCFLAGS='/O1'\n")
    with pytest.raises(ValueError, match="different build profiles"):
        match.scratch_translation_unit(second, root)


@pytest.mark.parametrize("member", ["first", "../escape", "/absolute"])
def test_invalid_or_duplicate_members_are_rejected(grouped_scratches, member):
    root, (_, second) = grouped_scratches
    path = root / "translation_units.json"
    payload = json.loads(path.read_text())
    payload["units"][0]["members"].append(member)
    path.write_text(json.dumps(payload))
    with pytest.raises(ValueError, match="invalid or duplicate member"):
        match.scratch_translation_unit(second, root)


def test_shadow_with_same_basename_is_not_registered(grouped_scratches, tmp_path):
    root, (_, second) = grouped_scratches
    assert match.scratch_translation_unit(replace(second, directory=tmp_path / "second"), root) is None


def test_listing_spans_select_one_function_in_unit():
    listing = """_first PROC NEAR
; 1 : int first() { return 1; }
  00000\tb8 01 00 00 00\tmov eax, 1
_first ENDP
_second PROC NEAR
; 4 : int second() { return 2; }
  00000\tb8 02 00 00 00\tmov eax, 2
_second ENDP
"""
    spans = match.parse_compiler_listing_spans(listing, symbol="second")
    assert len(spans) == 1
    assert spans[0].source_lines == (4,)
    assert spans[0].instruction_offsets == (0,)


def test_batch_matching_reads_the_compilers_actual_object(grouped_scratches, monkeypatch):
    root, (first, second) = grouped_scratches
    shared = first.directory / "build/scratch.obj"
    stale = second.directory / "build/scratch.obj"
    shared.parent.mkdir()
    stale.parent.mkdir()
    shared.write_bytes(b"shared object")
    stale.write_bytes(b"stale isolated object")
    seen = []

    def inspect_match(config, *, obj_path, **kwargs):
        seen.append((config.function, obj_path.read_bytes()))
        raise ValueError("inspection only")

    monkeypatch.setattr(match, "compile_scratch", lambda *args, **kwargs: shared)
    monkeypatch.setattr(match, "_match_precompiled_scratch_config", inspect_match)
    outcomes = match._collect_uncached_match_outcomes(
        [(second, 0x1000)], image=None, image_path=root / "image.exe",
        manifest=None, reference_manifest=None, match_root=root,
        manifest_digest="fixture", jobs=1,
        include_resolver=match._ScratchIncludeResolver(root),
    )
    assert seen == [("second", b"shared object")]
    assert outcomes[0].error == "inspection only"
