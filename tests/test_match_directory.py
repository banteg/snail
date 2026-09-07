from pathlib import Path

import pytest

from snail import cli
from snail.match import MatchResult, resolve_scratch_directory

DIRECTORY_COMMANDS = (
    ("scratch", ()),
    ("inspect", ()),
    ("listing", ("--output", "listing.cod")),
    ("probe", ("--stdin", "--record")),
    ("mutate", ("--spec", "plan.json", "--record")),
    ("contracts", ()),
    ("experiment-audit", ("--record", "1", "--reason", "reviewed plan")),
)


def _scratch(path: Path, *, function: str = "foo") -> Path:
    path.mkdir(parents=True)
    (path / "scratch.conf").write_text(f"FUNCTION={function}\n")
    (path / "scratch.cpp").write_text(f"void {function}() {{}}\n")
    return path.resolve()


def _snapshot(root: Path) -> dict[Path, bytes | None]:
    return {
        path.relative_to(root): path.read_bytes() if path.is_file() else None
        for path in root.rglob("*")
    }


def test_short_scratch_names_use_selected_root_and_preserve_existing_paths(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch,
) -> None:
    work = tmp_path / "work"
    work.mkdir()
    monkeypatch.chdir(work)
    first_root = tmp_path / "first"
    second_root = tmp_path / "second"
    first = _scratch(first_root / "scratches" / "foo")
    second = _scratch(second_root / "scratches" / "foo")

    assert resolve_scratch_directory("foo", first_root) == first
    assert resolve_scratch_directory("foo", second_root) == second
    assert resolve_scratch_directory("foo", Path("../first")) == first
    assert resolve_scratch_directory(first, second_root) == first
    assert resolve_scratch_directory("../first/scratches/foo", second_root) == first

    local = _scratch(work / "foo")
    assert resolve_scratch_directory("foo", first_root) == local
    assert resolve_scratch_directory("./foo", first_root) == local
    (work / "alias").symlink_to(local, target_is_directory=True)
    assert resolve_scratch_directory("alias", first_root) == local


@pytest.mark.parametrize("explicit", ["./foo", "foo/", "missing/foo", "../foo", Path("foo")])
def test_missing_explicit_paths_never_fall_back_to_short_names(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, explicit: str | Path,
) -> None:
    monkeypatch.chdir(tmp_path)
    root = tmp_path / "match"
    _scratch(root / "scratches" / "foo")
    with pytest.raises(NotADirectoryError, match="scratch directory not found"):
        resolve_scratch_directory(explicit, root)


@pytest.mark.parametrize("local_kind", ["directory", "file", "broken-symlink"])
def test_existing_local_entries_are_not_reinterpreted_as_scratch_names(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, local_kind: str,
) -> None:
    monkeypatch.chdir(tmp_path)
    root = tmp_path / "match"
    _scratch(root / "scratches" / "foo")
    local = tmp_path / "foo"
    if local_kind == "directory":
        local.mkdir()
        assert resolve_scratch_directory("foo", root) == local
        return
    elif local_kind == "file":
        local.write_text("keep local file")
    else:
        local.symlink_to(tmp_path / "missing")
    with pytest.raises(OSError) as caught:
        resolve_scratch_directory("foo", root)
    assert str(local.resolve()) in str(caught.value)
    assert str(root / "scratches") not in str(caught.value)


def test_unknown_names_do_not_search_manifest_function_aliases(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch,
) -> None:
    monkeypatch.chdir(tmp_path)
    _scratch(tmp_path / "scratches" / "first", function="shared_alias")
    _scratch(tmp_path / "scratches" / "second", function="shared_alias")
    with pytest.raises(FileNotFoundError, match="unknown scratch 'shared_alias'") as caught:
        resolve_scratch_directory("shared_alias", tmp_path)
    assert str(tmp_path / "scratches" / "shared_alias") in str(caught.value)


@pytest.mark.parametrize("command,extra", DIRECTORY_COMMANDS)
def test_directory_commands_preserve_explicit_argument_spelling(
    tmp_path: Path, command: str, extra: tuple[str, ...],
) -> None:
    args = cli.build_parser().parse_args([
        "match", command, "./foo", "--match-root", str(tmp_path), *extra,
    ])
    assert args.directory == "./foo"
    assert args.match_root == tmp_path


@pytest.mark.parametrize("command,extra", DIRECTORY_COMMANDS)
@pytest.mark.parametrize("directory", ["unknown", "./foo"])
def test_directory_commands_fail_before_creating_or_changing_artifacts(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch,
    capsys: pytest.CaptureFixture[str], command: str, extra: tuple[str, ...],
    directory: str,
) -> None:
    monkeypatch.chdir(tmp_path)
    root = tmp_path / "match"
    _scratch(root / "scratches" / "foo")
    before = _snapshot(tmp_path)
    assert cli.main([
        "match", command, directory, "--match-root", str(root), *extra,
    ]) == 2
    error = capsys.readouterr().err
    assert "scratch resolution failed:" in error
    if directory == "unknown":
        assert "unknown scratch 'unknown'" in error
        assert str(root / "scratches" / "unknown") in error
    else:
        assert f"scratch directory not found: {tmp_path / 'foo'}" in error
    assert _snapshot(tmp_path) == before


@pytest.mark.parametrize("options,message", [
    (("--min-changes", "2", "--max-changes", "1"), "--min-changes cannot exceed"),
    (("--time-budget", "0"), "--time-budget must be positive"),
    (("--export-candidate", "candidate"), "must be supplied together"),
])
def test_mutation_option_errors_precede_scratch_resolution(
    tmp_path: Path, capsys: pytest.CaptureFixture[str],
    options: tuple[str, ...], message: str,
) -> None:
    with pytest.raises(SystemExit) as caught:
        cli.main([
            "match", "mutate", str(tmp_path / "missing"),
            "--spec", "plan.json", *options,
        ])
    assert caught.value.code == 2
    assert message in capsys.readouterr().err


@pytest.mark.parametrize("command", ["scratch", "inspect"])
@pytest.mark.parametrize("custom_root", [False, True])
def test_compiling_commands_use_resolved_directory_and_selected_compiler_root(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch,
    capsys: pytest.CaptureFixture[str], command: str, custom_root: bool,
) -> None:
    monkeypatch.chdir(tmp_path)
    default = tmp_path / "default"
    custom = tmp_path / "custom"
    _scratch(default / "scratches" / "foo")
    _scratch(custom / "scratches" / "foo")
    monkeypatch.setattr(cli, "DEFAULT_MATCH_ROOT", default)
    selected = custom if custom_root else default
    calls = []

    def run_match(**kwargs):
        calls.append(kwargs)
        return MatchResult(1.0, 1, ("ret",), ("ret",))

    monkeypatch.setattr(cli, "run_scratch_match", run_match)
    before = _snapshot(tmp_path)
    args = ["match", command, "foo"]
    if custom_root:
        args += ["--match-root", str(custom)]
    assert cli.main(args) == 0
    capsys.readouterr()
    assert len(calls) == 1
    assert calls[0]["directory"] == selected / "scratches" / "foo"
    assert calls[0]["match_root"] == selected
    assert _snapshot(tmp_path) == before


def test_contract_lookup_by_short_name_remains_read_only(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch,
    capsys: pytest.CaptureFixture[str],
) -> None:
    monkeypatch.chdir(tmp_path)
    root = tmp_path / "match"
    scratch = _scratch(root / "scratches" / "foo")
    crosswalk = tmp_path / "crosswalk.json"
    crosswalk.write_text("{}")
    configs = []

    def audit(config, **_kwargs):
        configs.append(config)
        return {"function": config.function}

    monkeypatch.setattr(cli.match_contracts, "audit_contract", audit)
    before = _snapshot(tmp_path)
    assert cli.main([
        "match", "contracts", "foo", "--match-root", str(root),
        "--mobile-crosswalk", str(crosswalk), "--json",
    ]) == 0
    capsys.readouterr()
    assert len(configs) == 1 and configs[0].directory == scratch
    assert _snapshot(tmp_path) == before
