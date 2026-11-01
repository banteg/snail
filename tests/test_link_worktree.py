from pathlib import Path
import subprocess

import pytest


SCRIPT = Path(__file__).resolve().parents[1] / "tools/link_worktree.sh"


@pytest.fixture
def checkouts(tmp_path):
    main = tmp_path / "main"
    worktree = tmp_path / "linked checkout"
    subprocess.run(["git", "init", "-q", main], check=True)
    subprocess.run(
        ["git", "-c", "user.name=test", "-c", "user.email=test@invalid", "-c", "core.hooksPath=/dev/null",
         "-c", "commit.gpgSign=false", "commit", "--allow-empty", "-qm", "initial"],
        check=True, cwd=main,
    )
    subprocess.run(["git", "worktree", "add", "-q", "--detach", worktree], check=True, cwd=main)
    return main, worktree


@pytest.mark.parametrize("legacy_links", [False, True])
def test_writable_asset_trees_are_isolated_and_reruns_preserve_local_files(checkouts, legacy_links):
    main, worktree = checkouts
    files = ("artifacts/bin/SnailMailExtras.dat", "artifacts/extracted/SnailMail.dat/manifest.json")
    for name in files:
        original = main / name
        original.parent.mkdir(parents=True)
        original.write_bytes(b"main")
    if legacy_links:
        (worktree / "artifacts").mkdir()
        for directory in ("artifacts/bin", "artifacts/extracted"):
            (worktree / directory).symlink_to(main / directory, target_is_directory=True)

    subprocess.run([SCRIPT], check=True, cwd=worktree)
    for name in files:
        local = worktree / name
        assert local.read_bytes() == b"main"
        local.write_bytes(b"worktree")
    subprocess.run([SCRIPT], check=True, cwd=worktree)
    for name in files:
        assert (main / name).read_bytes() == b"main"
        assert (worktree / name).read_bytes() == b"worktree"


@pytest.mark.parametrize("parent", ["artifacts", "tools", "tools/match", "tools/match/bin"])
def test_symlinked_destination_parents_are_rejected_before_writes(checkouts, parent):
    main, worktree = checkouts
    (main / "artifacts/bin").mkdir(parents=True)
    (main / "tools/match/bin").mkdir(parents=True)
    # An in-place refresh through the parent would replace these with self-links.
    artifact_link = main / "artifacts/input"
    artifact_link.symlink_to("bin")
    tool_link = main / "tools/match/bin/wibo"
    (tool_link.parent / "runner").touch()
    tool_link.symlink_to("runner")
    dest = worktree / parent
    dest.parent.mkdir(parents=True, exist_ok=True)
    dest.symlink_to(main / parent, target_is_directory=True)
    result = subprocess.run([SCRIPT], cwd=worktree, text=True, capture_output=True)
    assert result.returncode != 0
    assert "expected a local worktree directory" in result.stderr
    assert artifact_link.readlink() == Path("bin")
    assert tool_link.readlink() == Path("runner")
    if parent != "artifacts":
        assert not (worktree / "artifacts").exists()
    assert not (main / "artifacts/artifacts").exists()


@pytest.mark.parametrize("legacy_link", [False, True])
def test_recursive_artifacts_alias_is_skipped_and_legacy_link_removed(checkouts, legacy_link):
    main, worktree = checkouts
    (main / "artifacts").mkdir()
    source = main / "artifacts/artifacts"
    source.symlink_to(".", target_is_directory=True)
    dest = worktree / "artifacts/artifacts"
    if legacy_link:
        dest.parent.mkdir()
        dest.symlink_to(source, target_is_directory=True)
    subprocess.run([SCRIPT], check=True, cwd=worktree)
    assert source.readlink() == Path(".")
    assert not dest.is_symlink()
    assert not dest.exists()
