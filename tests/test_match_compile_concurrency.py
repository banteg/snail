from __future__ import annotations

import json
import os
import select
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from contextlib import contextmanager
from pathlib import Path
from threading import Event, Lock

import pytest

from snail import match as match_module


def _change_bytes(path: Path, contents: bytes) -> None:
    previous = path.stat()
    path.write_bytes(contents)
    current = path.stat()
    os.utime(
        path,
        ns=(current.st_atime_ns, max(previous.st_mtime_ns + 1, current.st_mtime_ns)),
    )


@pytest.fixture
def stale_scratch(tmp_path: Path) -> tuple[match_module.ScratchConfig, Path]:
    root = tmp_path / "match"
    scratch = root / "scratches/foo"
    build = scratch / "build"
    compiler = root / "compilers/msvc6.5/Bin"
    build.mkdir(parents=True)
    compiler.mkdir(parents=True)
    (root / "include").mkdir()
    (root / "cl.sh").write_text("#!/bin/sh\n")
    (compiler / "CL.EXE").write_bytes(b"compiler driver")
    (compiler / "C2.DLL").write_bytes(b"compiler backend")
    (root / "include/shared.h").write_text("#define VALUE 1\n")
    source = scratch / "scratch.cpp"
    source.write_text('#include "shared.h"\nint foo() { return VALUE; }\n')
    (build / "scratch.cpp").write_bytes(source.read_bytes())
    obj = build / "scratch.obj"
    obj.write_bytes(b"previous complete object")
    config = match_module.ScratchConfig(
        scratch, "foo", "msvc6.5", "/O2 /G5 /W3", None, None
    )
    match_module._store_scratch_build_key(obj, config, root)
    _change_bytes(source, source.read_bytes() + b"// candidate revision\n")
    assert not match_module._scratch_object_is_current(obj, config, root)
    return config, root


@pytest.mark.parametrize("dependency", ["scratches/foo/scratch.cpp", "include/shared.h", "compilers/msvc6.5/Bin/C2.DLL"])
def test_preserved_mtime_edits_recompile(
    stale_scratch: tuple[match_module.ScratchConfig, Path],
    monkeypatch: pytest.MonkeyPatch,
    dependency: str,
) -> None:
    config, root = stale_scratch
    obj = config.directory / "build/scratch.obj"
    match_module._store_scratch_build_key(obj, config, root)
    resolver = match_module._ScratchIncludeResolver(root)
    assert match_module._scratch_object_is_current(obj, config, root, include_resolver=resolver)
    changed = root / dependency
    previous = changed.stat()
    changed.write_bytes(changed.read_bytes().replace(b"1", b"2") + b"// edit\n")
    os.utime(changed, ns=(previous.st_atime_ns, previous.st_mtime_ns))
    assert not match_module._scratch_object_is_current(obj, config, root, include_resolver=resolver)
    calls = []

    def compile_changed(args, *, cwd, **kwargs):
        calls.append(args)
        (Path(cwd) / "scratch.obj").write_bytes(b"fresh object")
        return subprocess.CompletedProcess(args, 0, "", "")

    monkeypatch.setattr(subprocess, "run", compile_changed)
    assert match_module.compile_scratch(config, root) == obj
    assert len(calls) == 1
    assert obj.read_bytes() == b"fresh object"
    assert match_module._scratch_object_is_current(obj, config, root)


def test_match_context_detects_preserved_mtime_edits(tmp_path, monkeypatch) -> None:
    image = tmp_path / "image.exe"
    matcher = tmp_path / "match.py"
    references = tmp_path / "references.json"
    for path in (image, matcher, references):
        path.write_bytes(b"original")
    monkeypatch.setattr(match_module, "__file__", str(matcher))
    monkeypatch.setattr(match_module, "DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH", references)
    previous_key = match_module._scratch_context_key(image)
    for path in (image, matcher, references):
        stat = path.stat()
        path.write_bytes(b"modified")
        os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns))
        current_key = match_module._scratch_context_key(image)
        assert current_key != previous_key
        previous_key = current_key


def test_concurrent_compile_rechecks_cache_and_publishes_complete_files(
    stale_scratch: tuple[match_module.ScratchConfig, Path],
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    config, root = stale_scratch
    build = config.directory / "build"
    obj = build / "scratch.obj"
    receipt = build / "scratch-build.json"
    published_source = build / "scratch.cpp"
    previous = {path: path.read_bytes() for path in (obj, receipt, published_source)}
    compiler_entered = Event()
    compiler_release = Event()
    second_lock_attempt = Event()
    state_lock = Lock()
    original_lock = match_module._scratch_compile_lock
    lock_attempts = 0
    compiler_calls = 0
    compile_directories: list[Path] = []

    @contextmanager
    def observed_lock(build_dir: Path):
        nonlocal lock_attempts
        with state_lock:
            lock_attempts += 1
            if lock_attempts == 2:
                second_lock_attempt.set()
        with original_lock(build_dir):
            yield

    def fake_run(args, *, cwd: Path, **_kwargs) -> subprocess.CompletedProcess:
        nonlocal compiler_calls
        private_dir = Path(cwd)
        with state_lock:
            compiler_calls += 1
            compile_directories.append(private_dir)
        assert private_dir != build
        assert private_dir.parent == build
        assert (private_dir / "scratch.cpp").read_bytes() == (
            config.directory / "scratch.cpp"
        ).read_bytes()
        private_obj = private_dir / "scratch.obj"
        assert not private_obj.exists()
        private_obj.write_bytes(b"partial")
        compiler_entered.set()
        assert compiler_release.wait(10), "test did not release compiler"
        private_obj.write_bytes(b"fresh complete object")
        return subprocess.CompletedProcess(args, 0, "", "")

    monkeypatch.setattr(match_module, "_scratch_compile_lock", observed_lock)
    monkeypatch.setattr(subprocess, "run", fake_run)

    with obj.open("rb") as old_object, receipt.open("rb") as old_receipt:
        with ThreadPoolExecutor(max_workers=2) as executor:
            first = executor.submit(match_module.compile_scratch, config, root)
            try:
                assert compiler_entered.wait(10), "first compile did not start"
                second = executor.submit(match_module.compile_scratch, config, root)
                assert second_lock_attempt.wait(10), "second compile did not contend"
                assert not second.done()
                assert compiler_calls == 1
                for path, contents in previous.items():
                    assert path.read_bytes() == contents
            finally:
                compiler_release.set()
            assert first.result(timeout=10) == obj
            assert second.result(timeout=10) == obj

        # Open descriptors retain the prior generations only when publication
        # replaces files instead of truncating and rewriting them in place.
        assert old_object.read() == previous[obj]
        assert old_receipt.read() == previous[receipt]

    assert compiler_calls == 1
    assert obj.read_bytes() == b"fresh complete object"
    assert published_source.read_bytes() == (
        config.directory / "scratch.cpp"
    ).read_bytes()
    assert json.loads(receipt.read_text())["key"] == match_module._scratch_build_key(
        config, root
    )
    assert match_module._scratch_object_is_current(obj, config, root)
    assert all(not directory.exists() for directory in compile_directories)


@pytest.mark.parametrize(
    "changed_dependency",
    ["scratches/foo/scratch.cpp", "include/shared.h", "compilers/msvc6.5/Bin/C2.DLL"],
)
def test_changed_dependency_rejects_build_without_replacing_previous_publication(
    stale_scratch: tuple[match_module.ScratchConfig, Path],
    monkeypatch: pytest.MonkeyPatch,
    changed_dependency: str,
) -> None:
    config, root = stale_scratch
    build = config.directory / "build"
    obj = build / "scratch.obj"
    publication = (obj, build / "scratch-build.json", build / "scratch.cpp")
    previous = {path: path.read_bytes() for path in publication}
    calls = 0
    private_directories: list[Path] = []

    def fake_run(args, *, cwd: Path, **_kwargs) -> subprocess.CompletedProcess:
        nonlocal calls
        calls += 1
        private_dir = Path(cwd)
        private_directories.append(private_dir)
        (private_dir / "scratch.obj").write_bytes(f"object generation {calls}".encode())
        if calls == 1:
            dependency = root / changed_dependency
            _change_bytes(dependency, dependency.read_bytes() + b"\n// changed\n")
        return subprocess.CompletedProcess(args, 0, "", "")

    monkeypatch.setattr(subprocess, "run", fake_run)
    with pytest.raises(
        RuntimeError, match=r"(?i)(input|dependenc).*chang|chang.*(input|dependenc)"
    ):
        match_module.compile_scratch(config, root)

    for path, contents in previous.items():
        assert path.read_bytes() == contents
    assert not match_module._scratch_object_is_current(obj, config, root)
    assert all(not directory.exists() for directory in private_directories)

    assert match_module.compile_scratch(config, root) == obj
    assert calls == 2
    assert obj.read_bytes() == b"object generation 2"
    assert match_module._scratch_object_is_current(obj, config, root)
    assert (build / "scratch.cpp").read_bytes() == (
        config.directory / "scratch.cpp"
    ).read_bytes()
    assert all(not directory.exists() for directory in private_directories)


def test_compiler_failure_preserves_previous_publication(
    stale_scratch: tuple[match_module.ScratchConfig, Path],
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    config, root = stale_scratch
    build = config.directory / "build"
    publication = tuple(
        build / name for name in ("scratch.obj", "scratch-build.json", "scratch.cpp")
    )
    previous = {path: path.read_bytes() for path in publication}
    private_directories: list[Path] = []

    def fake_run(args, *, cwd: Path, **_kwargs) -> subprocess.CompletedProcess:
        private_dir = Path(cwd)
        private_directories.append(private_dir)
        (private_dir / "scratch.obj").write_bytes(b"incomplete compiler output")
        return subprocess.CompletedProcess(args, 1, "", "compiler failed")

    monkeypatch.setattr(subprocess, "run", fake_run)
    with pytest.raises(RuntimeError, match="compiler failed"):
        match_module.compile_scratch(config, root)
    for path, contents in previous.items():
        assert path.read_bytes() == contents
    assert all(not directory.exists() for directory in private_directories)


def test_compile_locks_for_different_scratches_are_independent(tmp_path: Path) -> None:
    first = tmp_path / "first/build"
    second = tmp_path / "second/build"
    first.mkdir(parents=True)
    second.mkdir(parents=True)
    acquired_second = Event()

    def acquire_second() -> None:
        with match_module._scratch_compile_lock(second):
            acquired_second.set()

    with ThreadPoolExecutor(max_workers=1) as executor:
        with match_module._scratch_compile_lock(first):
            other = executor.submit(acquire_second)
            assert acquired_second.wait(10), "unrelated scratch was blocked"
        other.result(timeout=10)


@pytest.mark.skipif(os.name != "posix", reason="scratch compilation uses POSIX flock")
def test_scratch_compile_lock_serializes_separate_processes(tmp_path: Path) -> None:
    build = tmp_path / "build"
    build.mkdir()
    child_code = """
import fcntl
from pathlib import Path
import sys
from snail.match import _scratch_compile_lock

original_flock = fcntl.flock
def observed_flock(fd, operation):
    if operation == fcntl.LOCK_EX:
        try:
            original_flock(fd, operation | fcntl.LOCK_NB)
        except BlockingIOError:
            print("blocked", flush=True)
        else:
            print("uncontended", flush=True)
            original_flock(fd, fcntl.LOCK_UN)
    return original_flock(fd, operation)

fcntl.flock = observed_flock
with _scratch_compile_lock(Path(sys.argv[1])):
    print("acquired", flush=True)
"""
    child_env = {
        **os.environ,
        "PYTHONPATH": os.pathsep.join(
            part
            for part in (
                str(Path(match_module.__file__).resolve().parents[1]),
                os.environ.get("PYTHONPATH", ""),
            )
            if part
        ),
    }
    process = None
    try:
        with match_module._scratch_compile_lock(build):
            process = subprocess.Popen(
                [sys.executable, "-c", child_code, str(build)],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                env=child_env,
            )
            assert process.stdout is not None
            readable, _, _ = select.select([process.stdout], [], [], 10)
            assert readable, "child did not attempt the file lock"
            assert process.stdout.readline().strip() == "blocked"
            assert process.poll() is None
        stdout, stderr = process.communicate(timeout=10)
        assert process.returncode == 0, stderr
        assert stdout.strip() == "acquired"
    finally:
        if process is not None and process.poll() is None:
            process.kill()
            process.communicate(timeout=10)


@pytest.mark.skipif(not hasattr(os, "fork"), reason="requires POSIX fork")
def test_fork_resets_inherited_compile_lock_and_registry_guard(tmp_path: Path) -> None:
    # Keep fork outside the pytest process: a vanished owner must not poison
    # either the per-scratch threading lock or the registry's threading lock.
    child_code = """
import fcntl
import os
from pathlib import Path
import select
import signal
import sys
from threading import Event, Thread
from snail import match as match_module

build = Path(sys.argv[1])
held = Event()
release = Event()
def hold_compile_lock():
    with match_module._scratch_compile_lock(build):
        held.set()
        assert release.wait(10), "parent was not released"

holder = Thread(target=hold_compile_lock)
holder.start()
assert held.wait(5), "parent did not acquire compile lock"
reader, writer = os.pipe()
child_pid = None
try:
    with match_module._SCRATCH_COMPILE_LOCKS_GUARD:
        child_pid = os.fork()
        if child_pid == 0:
            os.close(reader)
            original_flock = fcntl.flock
            def observed_flock(fd, operation):
                if operation == fcntl.LOCK_EX:
                    try:
                        original_flock(fd, operation | fcntl.LOCK_NB)
                    except BlockingIOError:
                        os.write(writer, b"blocked\\n")
                    else:
                        os.write(writer, b"uncontended\\n")
                        original_flock(fd, fcntl.LOCK_UN)
                return original_flock(fd, operation)
            fcntl.flock = observed_flock
            try:
                with match_module._scratch_compile_lock(build):
                    os.write(writer, b"acquired\\n")
            except BaseException:
                os._exit(1)
            os._exit(0)
    os.close(writer)
    readable, _, _ = select.select([reader], [], [], 5)
    assert readable, "child inherited a locked thread lock or registry guard"
    assert os.read(reader, 128) == b"blocked\\n"
    release.set()
    holder.join(5)
    assert not holder.is_alive(), "parent did not release compile lock"
    readable, _, _ = select.select([reader], [], [], 5)
    assert readable, "child did not acquire the released file lock"
    assert os.read(reader, 128) == b"acquired\\n"
    _, status = os.waitpid(child_pid, 0)
    child_pid = None
    assert os.waitstatus_to_exitcode(status) == 0
finally:
    release.set()
    holder.join(5)
    if child_pid:
        try:
            os.kill(child_pid, signal.SIGKILL)
        except ProcessLookupError:
            pass
        os.waitpid(child_pid, 0)
    os.close(reader)
"""
    env = {
        **os.environ,
        "PYTHONPATH": os.pathsep.join(
            part
            for part in (
                str(Path(match_module.__file__).resolve().parents[1]),
                os.environ.get("PYTHONPATH", ""),
            )
            if part
        ),
    }
    result = subprocess.run(
        [sys.executable, "-c", child_code, str(tmp_path / "build")],
        capture_output=True,
        text=True,
        check=False,
        timeout=20,
        env=env,
    )
    assert result.returncode == 0, result.stdout + result.stderr


def test_evaluation_scores_and_fingerprints_the_same_captured_object(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    from snail.symbols import FunctionSymbol, FunctionSymbolManifest

    obj = tmp_path / "scratch.obj"
    obj.write_bytes(b"object A")
    config = match_module.ScratchConfig(
        tmp_path, "foo", "msvc6.5", "/O2", None, None
    )
    manifest = FunctionSymbolManifest(
        name="test",
        primary_target="test.exe",
        reference_target="test.exe",
        image_base=0x1000,
        unwrapped_sha256="",
        source_database=None,
        functions=(FunctionSymbol(0x1000, "foo"), FunctionSymbol(0x1001, "next")),
    )
    references = match_module.ReferenceSymbolManifest("test")
    scored_objects: list[bytes] = []

    def fake_match(*, object_data: bytes, reference_manifest, **_kwargs):
        assert reference_manifest is references
        scored_objects.append(object_data)
        replacement = tmp_path / "replacement.obj"
        replacement.write_bytes(b"object B")
        os.replace(replacement, obj)
        return match_module.MatchResult(1.0, 1, ("ret",), ("ret",))

    def extract(data: bytes, name: str, *, reference_manifest):
        assert reference_manifest is references
        return match_module.ObjectFunction(name, data, frozenset())

    monkeypatch.setattr(match_module, "compile_scratch_data", lambda *_args: obj.read_bytes())
    monkeypatch.setattr(
        match_module,
        "load_image",
        lambda *_args: match_module.LoadedImage(b"\xc3", 0x1000, 1),
    )
    monkeypatch.setattr(
        match_module, "load_default_reference_symbol_manifest", lambda: references
    )
    monkeypatch.setattr(match_module, "parse_coff_object", lambda data: data)
    monkeypatch.setattr(match_module, "extract_object_function", extract)
    monkeypatch.setattr(match_module, "run_match", fake_match)

    status = match_module.evaluate_scratch(config, tmp_path, manifest=manifest)

    assert status.error is None
    assert status.ratio == 1.0
    assert scored_objects == [b"object A"]
    assert obj.read_bytes() == b"object B"
    assert status.code_sha256 == match_module.object_function_fingerprint(
        match_module.ObjectFunction("foo", b"object A", frozenset())
    )
    assert status.code_sha256 != match_module.object_function_fingerprint(
        match_module.ObjectFunction("foo", b"object B", frozenset())
    )


@pytest.mark.parametrize("changed_input", ["source", "header", "image"])
def test_status_cache_rejects_edits_after_measurement(
    stale_scratch, monkeypatch, tmp_path, changed_input,
):
    from test_match import build_object

    from snail.symbols import FunctionSymbol, FunctionSymbolManifest

    config, root = stale_scratch
    target = bytes.fromhex("b801000000c3")
    image_path = tmp_path / "image.bin"
    image_path.write_bytes(target)
    image = match_module.LoadedImage(bytes(0x1000) + target, 0x400000, 0x2000)
    manifest = FunctionSymbolManifest(
        "test", str(image_path), str(image_path), 0x400000, "0" * 64, None,
        (FunctionSymbol(0x401000, "foo"), FunctionSymbol(0x401006, "next")),
    )
    digest = match_module._function_manifest_cache_digest(manifest)

    def fake_compiler(args, *, cwd, **kwargs):
        (Path(cwd) / "scratch.obj").write_bytes(build_object(target, [("_foo", 0)], []))
        return subprocess.CompletedProcess(args, 0, "", "")

    original = match_module._match_precompiled_task_with_context

    def edit_after_measurement(task, context):
        outcome = original(task, context)
        assert outcome.fields["body_byte_exact"]
        changed = {
            "source": config.directory / "scratch.cpp",
            "header": root / "include/shared.h",
            "image": image_path,
        }[changed_input]
        _change_bytes(changed, changed.read_bytes() + b"changed")
        return outcome

    monkeypatch.setattr(subprocess, "run", fake_compiler)
    monkeypatch.setattr(match_module, "_match_precompiled_task_with_context", edit_after_measurement)
    outcomes = match_module._collect_uncached_match_outcomes(
        [(config, 0x401000)], image=image, image_path=image_path, manifest=manifest,
        reference_manifest=match_module.ReferenceSymbolManifest("test"),
        match_root=root, manifest_digest=digest, jobs=1,
        include_resolver=match_module._ScratchIncludeResolver(root),
    )
    assert outcomes[0].fields is None
    assert "inputs changed during matching" in outcomes[0].error
    assert match_module._load_cached_status(config, image_path, root, manifest_digest=digest) is None


def test_interrupt_after_object_publication_leaves_no_stale_key(
    stale_scratch: tuple[match_module.ScratchConfig, Path],
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    config, root = stale_scratch
    obj = config.directory / "build/scratch.obj"
    # The previous object is current for the default profile.
    _change_bytes(config.directory / "scratch.cpp", b'#include "shared.h"\nint foo() { return VALUE; }\n')
    match_module._store_scratch_build_key(obj, config, root)
    profile = match_module.ScratchConfig(
        config.directory, "foo", "msvc6.5", "/O1 /W3", None, None
    )

    def fake_run(args, *, cwd: Path, **_kwargs) -> subprocess.CompletedProcess:
        (Path(cwd) / "scratch.obj").write_bytes(b"other profile object")
        return subprocess.CompletedProcess(args, 0, "", "")

    def interrupted(*_args, **_kwargs):
        raise KeyboardInterrupt

    monkeypatch.setattr(subprocess, "run", fake_run)
    monkeypatch.setattr(match_module, "_store_scratch_build_key", interrupted)
    with pytest.raises(KeyboardInterrupt):
        match_module.compile_scratch(profile, root)
    assert obj.read_bytes() == b"other profile object"
    assert not match_module._scratch_object_is_current(obj, config, root)


def test_compile_scratch_data_reads_the_object_it_published(
    stale_scratch: tuple[match_module.ScratchConfig, Path],
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    config, root = stale_scratch

    def fake_run(args, *, cwd: Path, **_kwargs) -> subprocess.CompletedProcess:
        (Path(cwd) / "scratch.obj").write_bytes(b"fresh object")
        return subprocess.CompletedProcess(args, 0, "", "")

    monkeypatch.setattr(subprocess, "run", fake_run)
    assert match_module.compile_scratch_data(config, root) == b"fresh object"
