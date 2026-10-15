"""The extras archive must provide a complete mobile level dependency graph."""

import re

import pytest

from snail.archive import parse_archive_index, read_archive_entry
from snail.port_extras import build_extras_files
from snail.symbols import REPO_ROOT

ANDROID = REPO_ROOT / "artifacts/android/asm_extracted"


@pytest.mark.skipif(
    not (ANDROID / "LEVELS/ARCADEPRO010.TXT").exists(),
    reason="needs extracted mobile assets",
)
def test_all_mobile_levels_and_segments_are_preserved():
    files = build_extras_files(ANDROID)
    for directory in ("LEVELS", "SEGMENTS"):
        for path in (ANDROID / directory).glob("*.TXT"):
            assert files[f"{directory}/{path.name}"] == path.read_bytes()
    # Include the mobile revisions of shared names, not just added filenames.
    assert len([name for name in files if name.startswith("SEGMENTS/")]) == 176
    assert len([name for name in files if name.startswith("LEVELS/")]) == 65
    for name, contents in files.items():
        if not name.startswith("LEVELS/"):
            continue
        for match in re.finditer(
            rb"^([^:\r\n]+?\.txt)", contents, re.MULTILINE | re.IGNORECASE
        ):
            assert "SEGMENTS/" + match[1].decode().strip().upper() in files, (
                name,
                match[1],
            )


@pytest.mark.skipif(
    not (REPO_ROOT / "artifacts/bin/SnailMailExtras.dat").exists(),
    reason="needs extras archive",
)
def test_deployable_extras_include_mobile_shared_dependencies():
    archive = REPO_ROOT / "artifacts/bin/SnailMailExtras.dat"
    index = parse_archive_index(archive)
    for name in (
        "SEGMENTS/CAGE2.TXT",
        "SEGMENTS/FINISH.TXT",
        "SEGMENTS/TWISTER2.TXT",
        "LEVELS/ARCADE001.TXT",
        "LEVELS/ARCADE050.TXT",
        "LEVELS/TUTORIAL.TXT",
    ):
        assert read_archive_entry(archive, index.entry_by_path(name))
